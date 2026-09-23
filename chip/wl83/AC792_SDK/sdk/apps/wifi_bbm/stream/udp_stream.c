#include "sys_common.h"
#include "system/spinlock.h"
#include "os/os_api.h"
#include "server/rt_stream_pkg.h"
#include "app_config.h"
#include "lwip.h"
#include "lwip/sockets.h"
#include "sock_api/sock_api.h"
#include "os/os_api.h"
#include "stream_core.h"
#include "udp_stream.h"


#define UDP_SEND_BUF_SIZE  (44*1460)
#define MAX_PAYLOAD (1460-sizeof(struct frm_head))

struct lbuf_data_head {
    int len;
    u8 type;
    u8 data[0];
};

struct stream_info {
    void *fd;
    u8 task_exit;
    char task_name[32];
    int task_pid;

    u8 *audio_lbuf_ptr;
    u8 *video_lbuf_ptr;
    struct lbuff_head *audio_lbuf_handle;
    struct lbuff_head *video_lbuf_handle;

    u8 *udp_send_buf;  //udp发送缓冲
    u32 seq;//seq自加

    struct sockaddr_in addr;
};

static struct stream_info *g_stream_info = NULL;

static int net_write_data(struct stream_info *info, char *buffer, size_t len, u8 type);
static int path_analyze(struct stream_info *info, const *path);


static void video_pkg_send_task(void *priv)
{
    struct stream_info *info  = priv;

    while (!info->task_exit) {
        u8 send_something = 0;

        struct lbuf_data_head *lbuf_data = lbuf_pop(info->audio_lbuf_handle, BIT(0));
        if (lbuf_data) {
            //write

            if (net_write_data(info, lbuf_data->data, lbuf_data->len, lbuf_data->type) != lbuf_data->len) {
                printf("net write data err\n");
            }

            send_something = 1;
            lbuf_free(lbuf_data);
            continue;
        }

        lbuf_data = lbuf_pop(info->video_lbuf_handle, BIT(0));
        if (lbuf_data) {
            u8 *data_ptr = lbuf_data->data;
            u32 remain_len = lbuf_data->len;
            //head offset
            if (data_ptr[0] != 0xFF || data_ptr[1] != 0xD8) {
                data_ptr += 8;
                remain_len -= 8;
            }
            //write
            if (net_write_data(info, data_ptr, remain_len, lbuf_data->type) != remain_len) {
                printf("net write data err\n");
            }

            send_something = 1;
            lbuf_free(lbuf_data);
        }

        if (!send_something) {
            os_time_dly(5);
        }
    }
}

static int sock_cb_func(enum sock_api_msg_type type, void *priv)
{
    struct stream_info *info  = priv;
    if (info->task_exit) {
        return -1;
    }

    return 0;
}

int net_rt_vpkg_open(const char *path, struct net_stream_info *s_info)
{
    int flags = 0;
    int err;

    if (g_stream_info) {
        printf("stream already opened \n");
        return 0;
    }

    struct stream_info *info = (struct stream_info *)calloc(1, sizeof(struct stream_info));

    if (info == NULL) {
        printf("%s %d->Error in malloc()\n", __func__, __LINE__);
        return -1;
    }

    if (path_analyze(info, path)) {
        printf("%s %d->Error in path_analyze\n", __func__, __LINE__);
        goto err;
    }

    info->fd = sock_reg(AF_INET, SOCK_DGRAM, 0, sock_cb_func, (void *)info);
    if (!info->fd) {
        printf("%s %d->Error in sock_reg\n", __func__, __LINE__);
        goto err;
    }

    int sample_rate = s_info->sample_rate;
    int abr = s_info->abr_kbps * 1024;
    int fps = s_info->fps;

    int audio_lbuf_size = sample_rate * 2;          //1s
    int video_lbuf_size = abr / fps / 8 * 3;        //3frame

    info->audio_lbuf_ptr = malloc(audio_lbuf_size);
    info->video_lbuf_ptr = malloc(video_lbuf_size);
    if (!info->audio_lbuf_ptr || !info->video_lbuf_ptr) {
        printf("%s %d->Error in lbuf malloc\n", __func__, __LINE__);
        goto err;
    }
    printf("lbuf size audio:%d video:%d \n", audio_lbuf_size, video_lbuf_size);

    info->audio_lbuf_handle = lbuf_init(info->audio_lbuf_ptr, audio_lbuf_size, 4, sizeof(struct lbuf_data_head));
    info->video_lbuf_handle = lbuf_init(info->video_lbuf_ptr, video_lbuf_size, 4, sizeof(struct lbuf_data_head));

    info->udp_send_buf = (char *)malloc(UDP_SEND_BUF_SIZE);
    if (info->udp_send_buf == NULL) {
        printf("%s %d->Error in malloc()\n", __func__, __LINE__);
        goto err;
    }

    snprintf(info->task_name, sizeof(info->task_name), "video_pkg_send_task");

    if (thread_fork(info->task_name, 15, 2048, 2048, &info->task_pid, video_pkg_send_task, (void *)info)) {
        printf("%s %d->Error in thread_fork\n", __func__, __LINE__);
        goto err;
    }

    g_stream_info = info;

    return 0;
err:
    if (info->fd) {
        sock_unreg(info->fd);
    }
    if (info->audio_lbuf_ptr) {
        free(info->audio_lbuf_ptr);
    }
    if (info->video_lbuf_ptr) {
        free(info->video_lbuf_ptr);
    }
    if (info->udp_send_buf) {
        free(info->udp_send_buf);
    }
    free(info);

    return -1;
}

int net_rt_vpkg_close(void)
{
    if (!g_stream_info) {
        printf("stream already close \n");
        return 0;
    }

    struct stream_info *info  = g_stream_info;

    if (info->task_pid) {
        info->task_exit = 1;
        thread_kill(&info->task_pid, KILL_WAIT);
    }

    if (info->fd) {
        sock_unreg(info->fd);
    }
    if (info->audio_lbuf_ptr) {
        free(info->audio_lbuf_ptr);
    }
    if (info->video_lbuf_ptr) {
        free(info->video_lbuf_ptr);
    }
    if (info->udp_send_buf) {
        free(info->udp_send_buf);
    }

    return 0;
}

int net_rt_send_frame(char *buffer, size_t len, u8 type)
{
    struct lbuf_data_head *lbuf_data = NULL;
    u8 timeout = 0;

    if (!g_stream_info) {
        printf("stream info null \n");
        return -1;
    }

    struct stream_info *info = (struct stream_info *)g_stream_info;

    if (type == 1) {
        //audio
        lbuf_data = lbuf_alloc(info->audio_lbuf_handle, len);
        while (!lbuf_data && ++timeout < 10) {
            //保证音频传输
            os_time_dly(5);
            lbuf_data = lbuf_alloc(info->audio_lbuf_handle, len);
        }
    } else {
        //video
        if (len < 512) {
            return len;
        }
        lbuf_data = lbuf_alloc(info->video_lbuf_handle, len);
    }

    if (lbuf_data) {
        lbuf_data->len = len;
        lbuf_data->type = type;
        memcpy(lbuf_data->data, buffer, len);
        lbuf_push(lbuf_data, BIT(0));
    } else {
        /* printf("drop frame \n"); */
        putchar('b');
    }

    return len;
}

static int path_analyze(struct stream_info *info, const *path)
{

    char *tmp = NULL;
    char *tmp2 = NULL;
    char ip[16] = {0};
    u16 port = 0;
    tmp = strstr(path, "udp://");
    if (!tmp) {
        return -1;
    }

    tmp += strlen("udp://");

    tmp2 = strchr(tmp, ':');
    printf("tmp=%s  len=%d\n", tmp, tmp2 - tmp);
    strncpy(ip, tmp, tmp2 - tmp);
    ip[tmp2 - tmp] = 0;
    port = atoi(tmp2 + 1);

    printf("remote ip:%s  port:%d\n", ip, port);


    info->addr.sin_family = AF_INET;
    info->addr.sin_addr.s_addr = inet_addr(ip);
    info->addr.sin_port = htons(port);
    return 0;

}

static int net_rt_vpkg_write(struct stream_info *info, char *buffer, size_t len, struct sockaddr *addr, int addrlen)
{
    int ret;
    ret = sock_sendto(info->fd, buffer, len, 0, addr, addrlen);

    return ret;
}

static int net_write_data(struct stream_info *info, char *buffer, size_t len, u8 type)
{
    u16 payload_len = 0;
    u32 total_udp_send = 0;
    struct frm_head frame_head = {0};
    int ret;

    if (len == 512) {
        if (buffer[8] == 0xab & buffer[9] == 0x56) {
            return len;
        }
    }

    frame_head.offset = 0;
    frame_head.frm_sz = len;
    frame_head.type &= ~LAST_FREG_MAKER;
    frame_head.type |=  type;
    frame_head.timestamp = 0;
    frame_head.seq = info->seq++;

    u32 remain_len = len;
    while (remain_len) {
        if (remain_len < MAX_PAYLOAD) {
            payload_len = remain_len;
            frame_head.type |= LAST_FREG_MAKER;
        } else {
            payload_len = MAX_PAYLOAD;
        }

        frame_head.payload_size = payload_len;
        memcpy(info->udp_send_buf + total_udp_send, &frame_head, sizeof(struct frm_head));
        total_udp_send += sizeof(struct frm_head);

        memcpy(info->udp_send_buf + total_udp_send, buffer + frame_head.offset, payload_len);

        total_udp_send += payload_len;

        if ((total_udp_send == UDP_SEND_BUF_SIZE) || (payload_len < MAX_PAYLOAD)) {
            if ((ret = net_rt_vpkg_write(info, info->udp_send_buf, total_udp_send, (struct sockaddr *)&info->addr, sizeof(struct sockaddr_in))) != total_udp_send) {
                puts("rt_stream_sent error!\n");
                return -1;
            }
            total_udp_send = 0;
        }

        remain_len -= payload_len;
        frame_head.offset += payload_len;
    }

    return len;
}


