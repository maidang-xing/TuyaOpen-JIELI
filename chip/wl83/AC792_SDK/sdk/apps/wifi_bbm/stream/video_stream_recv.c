#include "video_stream_recv.h"
#include "video_stream_recorder.h"
#include "sock_api/sock_api.h"
#include "rt_stream_pkg.h"

#define LOG_TAG_CONST       VIDEO_STREAM_RECV
#define LOG_TAG             "[VIDEO_STREAM_RECV]"
#define LOG_ERROR_ENABLE
#define LOG_INFO_ENABLE
#define LOG_DUMP_ENABLE
#include "debug.h"

#define STREAM_RECV_TASK_NAME       "video_stream_recv_task"
#define offsetof(type, memb) \
    ((unsigned long)(&((type *)0)->memb))

typedef enum  {
    VIDEO_TYPE_PACKET = 10,
    AUDIO_TYPE_PACKET,
    CONTINUE_PARSE_TYPE_PACKET,
    UNKNOW_TYPE_PACKET,
} PACKET_TYPE;

struct lbuf_data_head {
    int len;
    u8 data[0];
};

struct parse_info {
    u8 *data_buf;        //解析出来的数据缓存
    int data_len;
    PACKET_TYPE packet_type;     //解析出的数据类型(视频/音频)
    u32 old_frame_seq;  //媒体包序列
    u32 total_payload_len;
};

struct stream_dev {
    struct list_head entry;
    struct parse_info parse_info;
    u32 ip_addr;
    struct lbuf_head *video_lbuf_handle;
    char *video_lbuf_ptr;
    OS_SEM video_sem;
    struct lbuf_head *audio_lbuf_handle;
    char *audio_lbuf_ptr;
    OS_SEM audio_sem;
    u8 received_video_frame;
    u8 received_audio_frame;
    struct video_rec_ctx rec_ctx;
};


static int parse_net_path(char *net_path, u32 *ip_addr, u16 *port);

static void stream_recv_task(void *priv);
static int parse_data_enqueue(struct video_stream_recv_hdl *recv_hdl, u8 *buf, int len, u32 ip_addr);
static int parse_recv_data(u8 *recv_buf, int recv_len, struct parse_info *parse_info);
static struct stream_dev *find_stream_dev_by_ip(struct video_stream_recv_hdl *recv_hdl, u32 ip_addr);
static struct stream_dev *stream_dev_create(u32 ip_addr);
static int stream_dev_packet_enqueue(struct stream_dev *dev, u8 *buf, int len, PACKET_TYPE type);
static int stream_dev_video_queue_init(struct stream_dev *dev);
static int stream_dev_audio_queue_init(struct stream_dev *dev);
static void stream_dev_queue_deinit(struct stream_dev *dev);
static void stream_dev_destroy(struct stream_dev *dev);
static int video_queue_push(struct stream_dev *dev, u8 *buf, int len);
static int audio_queue_push(struct stream_dev *dev, u8 *buf, int len);
static int video_queue_pop(struct stream_dev *dev, u8 **buf, int *len, int timeout_ms);
static int audio_queue_pop(struct stream_dev *dev, u8 **buf, int *len, int timeout_ms);


int video_stream_recv_create(struct video_stream_recv_hdl **hdl)
{
    struct video_stream_recv_hdl *recv_hdl;
    recv_hdl = malloc(sizeof(struct video_stream_recv_hdl));
    if (!recv_hdl) {
        log_error(" stream recv hdl alloc err \n");
        return -1;
    }
    memset(recv_hdl, 0x00, sizeof(struct video_stream_recv_hdl));

    *hdl = recv_hdl;
    return 0;
}

int video_stream_recv_init(struct video_stream_recv_hdl *recv_hdl, char *net_path)
{
    int ret = 0;
    u32 ip_addr;
    u16 port;

    INIT_LIST_HEAD(&recv_hdl->dev_list);

    recv_hdl->net_path = net_path;
    recv_hdl->recv_buf_size = STREAM_RECV_BUF_SIZE;
    recv_hdl->recv_buf = malloc(recv_hdl->recv_buf_size);
    if (!recv_hdl->recv_buf) {
        log_error(" stream recv buf alloc err \n");
        return -1;
    }

    ret = parse_net_path(net_path, &ip_addr, &port);
    if (ret != 0) {
        log_error(" parse net path:%s err !\n", net_path);
        goto err;
    }

    struct sockaddr_in recv_addr;
    recv_addr.sin_family = AF_INET;
    recv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    recv_addr.sin_port = htons(port);
    recv_hdl->stream_recv_sockfd = sock_reg(AF_INET, SOCK_DGRAM, 0, NULL, recv_hdl);
    if (recv_hdl->stream_recv_sockfd == NULL) {
        log_error(" sock reg err \n");
        goto err;
    }
    ret = sock_bind(recv_hdl->stream_recv_sockfd, (struct sockaddr *)&recv_addr, sizeof(struct sockaddr));
    if (ret) {
        log_error(" sock bind err :%d \n", ret);
        goto err;
    }
    struct ip_mreq mreq;
    mreq.imr_multiaddr.s_addr = htonl(ip_addr);
    mreq.imr_interface.s_addr = htonl(INADDR_ANY);
    ret = sock_setsockopt(recv_hdl->stream_recv_sockfd, IPPROTO_IP, IP_ADD_MEMBERSHIP, &mreq, sizeof(mreq));
    if (ret) {
        log_error(" sock setsockopt err :%d \n", ret);
        goto err;
    }

    return 0;
err:
    if (recv_hdl->recv_buf) {
        free(recv_hdl->recv_buf);
        recv_hdl->recv_buf = NULL;
    }

    if (recv_hdl->stream_recv_sockfd) {
        sock_unreg(recv_hdl->stream_recv_sockfd);
        recv_hdl->stream_recv_sockfd = NULL;
    }
    return -1;
}

int video_stream_recv_start(struct video_stream_recv_hdl *recv_hdl)
{
    int ret = 0;
    if (recv_hdl->stream_recv_task_pid) {
        log_error(" video stream recv task already start !\n");
        return -1;
    }

    recv_hdl->stream_recv_task_exit = 0;
    ret = thread_fork(STREAM_RECV_TASK_NAME, 10, 2048, 2048, &recv_hdl->stream_recv_task_pid,
                      stream_recv_task, recv_hdl);
    if (ret) {
        log_error(" video stream recv task create err :%d \n", ret);
        return -1;
    }

    return 0;
}

void video_stream_recv_set_dev_notify(struct video_stream_recv_hdl *recv_hdl, void (*add_dev_notify)(u32), void (*del_dev_notify)(u32))
{
    recv_hdl->add_dev_notify = add_dev_notify;
    recv_hdl->del_dev_notify = del_dev_notify;
}

int video_stream_recv_stop(struct video_stream_recv_hdl *recv_hdl)
{
    if (recv_hdl->stream_recv_task_pid) {
        recv_hdl->stream_recv_task_exit = 1;
        thread_kill(&recv_hdl->stream_recv_task_pid, KILL_WAIT);
    }
    return 0;
}

int video_stream_recv_destroy(struct video_stream_recv_hdl **hdl)
{
    struct video_stream_recv_hdl *recv_hdl = *hdl;
    struct stream_dev *dev, *n;
    if (!recv_hdl) {
        return -1;
    }

    if (recv_hdl->stream_recv_sockfd) {
        sock_unreg(recv_hdl->stream_recv_sockfd);
        recv_hdl->stream_recv_sockfd = NULL;
    }

    if (recv_hdl->recv_buf) {
        free(recv_hdl->recv_buf);
        recv_hdl->recv_buf = NULL;
    }

    list_for_each_entry_safe(dev, n, &recv_hdl->dev_list, entry) {
        stream_dev_destroy(dev);
    }

    free(recv_hdl);
    *hdl = NULL;

    return 0;
}

int video_stream_recv_acquire_frame(struct video_stream_recv_hdl *recv_hdl, u32 ip_addr,
                                    u8 **frame_buf, int *frame_len, FRAME_TYPE frame_type)
{

    if (!recv_hdl || !frame_buf || !frame_len) {
        return -1;
    }
    struct stream_dev *dev;
    dev = find_stream_dev_by_ip(recv_hdl, ip_addr);
    if (!dev) {
        log_error(" stream dev not found for ip:%s \n", inet_ntoa(ip_addr));
        return -1;
    }

    if (frame_type == VIDEO_FRAME) {
        struct lbuf_data_head *head = lbuf_pop(dev->video_lbuf_handle, BIT(0));
        if (!head) {
            log_error(" stream video frame lbuf get null \n");
            return -1;
        }
        *frame_buf = head->data;
        *frame_len = head->len;
        return 0;
    } else if (frame_type == AUDIO_FRAME) {
        struct lbuf_data_head *head = lbuf_pop(dev->audio_lbuf_handle, BIT(0));
        if (!head) {
            log_error(" stream audio frame lbuf get null \n");
            return -1;
        }
        *frame_buf = head->data;
        *frame_len = head->len;
        return 0;
    } else {
        log_error(" acquire frame unknow type :%d \n", frame_type);
        return -1;
    }

    return 0;
}

int video_stream_recv_acquire_frame_block(struct video_stream_recv_hdl *recv_hdl, u32 ip_addr,
        u8 **frame_buf, int *frame_len, FRAME_TYPE frame_type, int timeout_ms)
{
    int ret;
    struct stream_dev *dev;
    if (!recv_hdl || !frame_buf || !frame_len) {
        return -1;
    }

    *frame_buf = NULL;
    *frame_len = 0;

    dev = find_stream_dev_by_ip(recv_hdl, ip_addr);
    if (!dev) {
        log_error(" stream dev not found for ip:%s \n", inet_ntoa(ip_addr));
        return -1;
    }

    if (frame_type == VIDEO_FRAME) {
        ret = video_queue_pop(dev, frame_buf, frame_len, timeout_ms);
    } else if (frame_type == AUDIO_FRAME) {
        ret = audio_queue_pop(dev, frame_buf, frame_len, timeout_ms);
    } else {
        log_error(" acquire frame unknow type :%d \n", frame_type);
        return -1;
    }

    return ret;
}

void video_stream_recv_release_frame(struct video_stream_recv_hdl *recv_hdl, u8 *frame_buf)
{
    if (!recv_hdl || !frame_buf) {
        return;
    }

    //偏移得到lbuf头
    struct lbuf_data_head *head = frame_buf - offsetof(struct lbuf_data_head, data);
    lbuf_free(head);
}

int video_stream_recv_rec_start(struct video_stream_recv_hdl *recv_hdl, u32 ip_addr,
                                const char *file_path, int video_width, int video_height,
                                double fps, int audio_sample_rate, int audio_channels, int audio_bits)
{
    if (!recv_hdl || !file_path) {
        log_error("rec_start: invalid params\n");
        return -1;
    }

    struct stream_dev *dev = find_stream_dev_by_ip(recv_hdl, ip_addr);
    if (!dev) {
        log_error("rec_start: device not found for ip:%s\n", inet_ntoa(ip_addr));
        return -1;
    }

    /* 设置录制参数 */
    dev->rec_ctx.video_width = video_width;
    dev->rec_ctx.video_height = video_height;
    dev->rec_ctx.video_fps = fps;
    dev->rec_ctx.audio_sample_rate = audio_sample_rate;
    dev->rec_ctx.audio_channels = audio_channels;
    dev->rec_ctx.audio_bits = audio_bits;

    return video_stream_rec_start(&dev->rec_ctx, file_path);
}

int video_stream_recv_rec_stop(struct video_stream_recv_hdl *recv_hdl, u32 ip_addr)
{
    if (!recv_hdl) {
        log_error("rec_stop: invalid params\n");
        return -1;
    }

    struct stream_dev *dev = find_stream_dev_by_ip(recv_hdl, ip_addr);
    if (!dev) {
        log_error("rec_stop: device not found for ip:%s\n", inet_ntoa(ip_addr));
        return -1;
    }

    return video_stream_rec_stop(&dev->rec_ctx);
}

static void stream_recv_task(void *priv)
{
    struct video_stream_recv_hdl *recv_hdl = (struct video_stream_recv_hdl *)priv;
    int ret, recv_len;
    struct sockaddr_in from_addr;
    socklen_t addr_len = sizeof(struct sockaddr_in);

    while (!recv_hdl->stream_recv_task_exit) {
        recv_len = sock_recvfrom(recv_hdl->stream_recv_sockfd, recv_hdl->recv_buf, recv_hdl->recv_buf_size,
                                 0, (struct sockaddr *)&from_addr, &addr_len);
        if (recv_len <= 0) {
            continue;
        }
        parse_data_enqueue(recv_hdl, recv_hdl->recv_buf, recv_len, from_addr.sin_addr.s_addr);
    }
}

static int parse_data_enqueue(struct video_stream_recv_hdl *recv_hdl,
                              u8 *buf, int len, u32 ip_addr)
{
    struct stream_dev *dev;
    dev = find_stream_dev_by_ip(recv_hdl, ip_addr);
    if (!dev) {
        dev = stream_dev_create(ip_addr);
        if (!dev) {
            log_error(" stream dev create err \n");
            return -1;
        }
        list_add_tail(&dev->entry, &recv_hdl->dev_list);
        if (recv_hdl->add_dev_notify) {
            recv_hdl->add_dev_notify(ip_addr);
        }
    }

    int ret = parse_recv_data(buf, len, &dev->parse_info);
    if (ret) {
        log_error(" parse recv packet err :%d \n", ret);
        return -1;
    }
    PACKET_TYPE type = dev->parse_info.packet_type;

    if (type == VIDEO_TYPE_PACKET || type == AUDIO_TYPE_PACKET) {
        stream_dev_packet_enqueue(dev, dev->parse_info.data_buf, dev->parse_info.data_len, type);
    } else if (type == CONTINUE_PARSE_TYPE_PACKET) {
        //do nothing
    } else {
        log_error(" stream packet enter dev queue unknow type :%d \n", type);
        return -1;
    }

    return 0;
}

static int stream_dev_video_queue_init(struct stream_dev *dev)
{
    dev->video_lbuf_ptr = malloc(STREAM_PACKET_VIDEO_QUEUE_SIZE);
    if (!dev->video_lbuf_ptr) {
        log_error(" stream dev video lbuf ptr alloc err \n");
        return -1;
    }
    os_sem_create(&dev->video_sem, 0);
    dev->received_video_frame = 1;
    dev->video_lbuf_handle = lbuf_init(dev->video_lbuf_ptr,
                                       STREAM_PACKET_VIDEO_QUEUE_SIZE,
                                       8, sizeof(struct lbuf_data_head));
    if (!dev->video_lbuf_handle) {
        log_error(" stream dev video lbuf handle init err \n");
        free(dev->video_lbuf_ptr);
        dev->video_lbuf_ptr = NULL;
        return -1;
    }

    return 0;
}

static int stream_dev_audio_queue_init(struct stream_dev *dev)
{
    dev->audio_lbuf_ptr = malloc(STREAM_PACKET_AUDIO_QUEUE_SIZE);
    if (!dev->audio_lbuf_ptr) {
        log_error(" stream dev audio lbuf ptr alloc err \n");
        return -1;
    }
    os_sem_create(&dev->audio_sem, 0);
    dev->received_audio_frame = 1;
    dev->audio_lbuf_handle = lbuf_init(dev->audio_lbuf_ptr,
                                       STREAM_PACKET_AUDIO_QUEUE_SIZE,
                                       8, sizeof(struct lbuf_data_head));
    if (!dev->audio_lbuf_handle) {
        log_error(" stream dev audio lbuf handle init err \n");
        free(dev->audio_lbuf_ptr);
        dev->audio_lbuf_ptr = NULL;
        return -1;
    }

    return 0;
}
static void stream_dev_queue_deinit(struct stream_dev *dev)
{
    if (dev->video_lbuf_ptr) {
        free(dev->video_lbuf_ptr);
        dev->video_lbuf_ptr = NULL;
        os_sem_del(&dev->video_sem, OS_DEL_ALWAYS);
    }
    if (dev->audio_lbuf_ptr) {
        free(dev->audio_lbuf_ptr);
        dev->audio_lbuf_ptr = NULL;
        os_sem_del(&dev->audio_sem, OS_DEL_ALWAYS);
    }
}

static int stream_dev_packet_enqueue(struct stream_dev *dev, u8 *buf, int len, PACKET_TYPE type)
{
    if (type == VIDEO_TYPE_PACKET) {
        if (!dev->video_lbuf_handle) {
            if (stream_dev_video_queue_init(dev) != 0) {
                return -1;
            }
        }
        video_queue_push(dev, buf, len);
    } else if (type == AUDIO_TYPE_PACKET) {
        if (!dev->audio_lbuf_handle) {
            if (stream_dev_audio_queue_init(dev) != 0) {
                return -1;
            }
        }
        audio_queue_push(dev, buf, len);
    } else {
        log_error(" stream dev enqueue unknow type :%d \n", type);
        return -1;
    }

    return 0;
}

static struct stream_dev *stream_dev_create(u32 ip_addr)
{
    struct stream_dev *dev;
    dev = malloc(sizeof(struct stream_dev));
    if (!dev) {
        log_error(" stream dev alloc err \n");
        return NULL;
    }
    memset(dev, 0x00, sizeof(struct stream_dev));

    dev->parse_info.data_buf = malloc(STREAM_PARSE_BUF_SIZE);
    if (!dev->parse_info.data_buf) {
        log_error(" stream dev parse buf alloc err \n");
        free(dev);
        return NULL;
    }

    dev->ip_addr = ip_addr;
    INIT_LIST_HEAD(&dev->entry);
    video_rec_ctx_init(&dev->rec_ctx);
    return dev;
}

static void stream_dev_destroy(struct stream_dev *dev)
{
    if (!dev) {
        return;
    }

    /* 如果正在录像，先停止 */
    if (dev->rec_ctx.is_recording) {
        video_stream_rec_stop(&dev->rec_ctx);
    }

    list_del(&dev->entry);
    stream_dev_queue_deinit(dev);

    if (dev->parse_info.data_buf) {
        free(dev->parse_info.data_buf);
        dev->parse_info.data_buf = NULL;
    }

    free(dev);
}

static int video_queue_push(struct stream_dev *dev, u8 *buf, int len)
{
    struct lbuf_data_head *head = NULL;
    do {
        head = lbuf_alloc(dev->video_lbuf_handle, len);
        if (!head) {
            log_debug(" stream video lbuf full , drop frame \n");
            //decrease sem count
            if (os_sem_pend(&dev->video_sem, 1) != OS_NO_ERR) {
                log_error(" video queue pend err \n");
                return -1;
            }
            //drop frame
            struct lbuf_data_head *temp_head = lbuf_pop(dev->video_lbuf_handle, BIT(0));
            if (temp_head) {
                lbuf_free(temp_head);
            }
        }
    } while (!head);

    head->len = len;
    memcpy(head->data, buf, len);
    lbuf_push(head, BIT(0));
    os_sem_post(&dev->video_sem);

    /* 录像钩子: 将视频帧写入 AVI 文件 */
    if (dev->rec_ctx.is_recording) {
        video_stream_recorder_write_frame(&dev->rec_ctx, buf, len, VIDEO_FRAME);
    }

    return 0;
}

static int audio_queue_push(struct stream_dev *dev, u8 *buf, int len)
{
    struct lbuf_data_head *head = NULL;
    do {
        head = lbuf_alloc(dev->audio_lbuf_handle, len);
        if (!head) {
            log_debug(" stream audio lbuf full , drop frame \n");
            //decrease sem count
            if (os_sem_pend(&dev->audio_sem, 1) != OS_NO_ERR) {
                log_error(" audio queue pend err \n");
                return -1;
            }
            //drop frame
            struct lbuf_data_head *temp_head = lbuf_pop(dev->audio_lbuf_handle, BIT(0));
            if (temp_head) {
                lbuf_free(temp_head);
            }
        }
    } while (!head);

    head->len = len;
    memcpy(head->data, buf, len);
    lbuf_push(head, BIT(0));
    os_sem_post(&dev->audio_sem);

    /* 录像钩子: 将音频帧写入 AVI 文件 */
    if (dev->rec_ctx.is_recording) {
        video_stream_recorder_write_frame(&dev->rec_ctx, buf, len, AUDIO_FRAME);
    }

    return 0;
}

static int video_queue_pop(struct stream_dev *dev, u8 **buf, int *len, int timeout_ms)
{
    int ret = 0;
    int timeout_tick = timeout_ms / 10;

    if (dev->received_video_frame == 0) {
        log_debug(" no video frame received yet !\n");
        os_time_dly(timeout_tick);          //TODO: no block ?
        return -1;
    }

    ret = os_sem_pend(&dev->video_sem, timeout_tick);
    if (ret != OS_NO_ERR) {
        log_debug(" video queue pop timeout %d ms \n", timeout_ms);
        return -1;
    }

    struct lbuf_data_head *head = lbuf_pop(dev->video_lbuf_handle, BIT(0));
    if (!head) {
        log_error(" stream video frame lbuf get null \n");
        return -1;
    }
    *buf = head->data;
    *len = head->len;
    return 0;
}

static int audio_queue_pop(struct stream_dev *dev, u8 **buf, int *len, int timeout_ms)
{
    int ret = 0;
    int timeout_tick = timeout_ms / 10;

    if (dev->received_audio_frame == 0) {
        log_debug(" no audio frame received yet !\n");
        os_time_dly(timeout_tick);          //TODO: no block ?
        return -1;
    }

    ret = os_sem_pend(&dev->audio_sem, timeout_tick);
    if (ret != OS_NO_ERR) {
        log_debug(" audio queue pop timeout %d ms \n", timeout_ms);
        return -1;
    }

    struct lbuf_data_head *head = lbuf_pop(dev->audio_lbuf_handle, BIT(0));
    if (!head) {
        log_error(" stream audio frame lbuf get null \n");
        return -1;
    }
    *buf = head->data;
    *len = head->len;
    return 0;
}


static struct stream_dev *find_stream_dev_by_ip(struct video_stream_recv_hdl *recv_hdl, u32 ip_addr)
{
    struct stream_dev *dev;
    list_for_each_entry(dev, &recv_hdl->dev_list, entry) {
        if (dev->ip_addr == ip_addr) {
            return dev;
        }
    }
    return NULL;
}

static int parse_recv_data(u8 *recv_buf, int recv_len, struct parse_info *parse_info)
{
    u32 position = 0;
    struct frm_head  *head_info;
    u32 frame_head_size = sizeof(struct frm_head);

    if (recv_len < frame_head_size) {
        log_error(" recv_recv_len err\n");
        return -1;
    }

    do {
        head_info = (struct frm_head *)(recv_buf + position);

        if ((head_info->type & JPEG_TYPE_VIDEO) || (head_info->type & PCM_TYPE_AUDIO)) {
            if (head_info->frm_sz > STREAM_PARSE_BUF_SIZE) {
                log_error("jpeg frame size too large :%d \n", head_info->frm_sz);
                return -1;
            }
            recv_len = recv_len - (frame_head_size + head_info->payload_size);
            if (recv_len < 0) {
                log_error("remain recv_len err:%d \n", recv_len);
                return -1;
            }

            //如果当前的seq小于旧的seq,说明是旧的数据包,跳过不处理
            // if (head_info->seq < parse_info->old_frame_seq) {
            //     log_error("old frame \n");
            //     goto continue_deal;
            // }

            //如果当前seq大于旧的seq,认为是新的数据包,组包重新初始
            if (head_info->seq > parse_info->old_frame_seq) {
                parse_info->old_frame_seq = head_info->seq;
                parse_info->total_payload_len = 0;
            }

            memcpy(parse_info->data_buf + head_info->offset,
                   (recv_buf + position) + frame_head_size,
                   head_info->payload_size);

            parse_info->total_payload_len += head_info->payload_size;

            //接收到完整一帧
            if (parse_info->total_payload_len == head_info->frm_sz) {
                parse_info->data_len = parse_info->total_payload_len;
                parse_info->total_payload_len = 0;

                if (head_info->type & JPEG_TYPE_VIDEO) {
                    parse_info->packet_type =  VIDEO_TYPE_PACKET;
                } else {
                    parse_info->packet_type =  AUDIO_TYPE_PACKET;
                }
                return 0;
            }
        } else {
            log_error("recv type err:%d \n", head_info->type);
            parse_info->packet_type = UNKNOW_TYPE_PACKET;
            return 0;
        }

continue_deal:
        position += (frame_head_size + head_info->payload_size);

    } while (recv_len > 0);

    parse_info->packet_type = CONTINUE_PARSE_TYPE_PACKET;
    return 0;
}

static int parse_net_path(char *net_path, u32 *ip_addr, u16 *port)
{
    char ip_str[16];
    char *p1, *p2;
    int len;

    if (!net_path) {
        log_error(" net path is null !\n");
        return -1;
    }

    p1 = net_path;
    p2 = strchr(net_path, ':');
    if (!p2) {
        return -1;
    }
    len = p2 - p1;
    if (len >= sizeof(ip_str)) {
        return -1;
    }
    memcpy(ip_str, p1, len);
    ip_str[len] = 0;

    *ip_addr = inet_addr(ip_str);
    *port = atoi(p2 + 1);

    return 0;
}


