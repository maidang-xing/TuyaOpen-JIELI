#include "app_config.h"
#if CONFIG_WIFI_IMAGE_TRANSMIT_ENABLE

#include "server/rt_stream_pkg.h"   //head info .h
#include "server/video_server.h"//app_struct
#include "server/video_dec_server.h"//dec_struct
#include "server/ctp_server.h"//enum ctp_cli_msg_type
#include "server/rt_stream_pkg.h"   //head info .h
#include "wifi/wifi_connect.h"
#include "sock_api/sock_api.h"
#include "system/includes.h"
#include "lwip/sockets.h"

#define DEST_PORT 3333  //发送命令端口
#define CONN_PORT 2224  //接收数据端口
#define DEST_IP_SERVER "192.168.1.1" //主机IP
#define USER_IP_SERVER "192.168.1.2" //本机IP

#define JPG_MAX_SIZE 100*1024
#define JPG_FPS 20 //
#define JPG_SRC_W 640 //输出显示的大小 程序会根据屏幕大小合理的显示出来  分辨率不对会引起花屏现象
#define JPG_SRC_H 480
#define SOCK_RECV_SIZE 8*1024
#define HEAD_DATA 20

#define CHECK_CODE 0x88 //填充数据值
#define CHECK_CODE_NUM 32 //检查填充量

struct __JPG_INFO {
    u32 src_w;
    u32 src_h;
    u32 buf_len;
    u8  buf[];
};

struct ctp_hdl {
    struct list_head entry;
    int id;
    int recv_thread_pid;
    void *sock_hdl;
    struct sockaddr_in dest_addr;
    int (*cb_func)(void *hdl, enum ctp_cli_msg_type type, const char *topic, const char *content, void *priv);
    void *priv;
    char *topic;
    unsigned int timeout;
    unsigned int timehdl;
    unsigned int timecheck;
    unsigned int timecheckout;
};

struct __NET_CTP_INFO {
    u8 state;
    void *video_dec;
};


static struct ctp_hdl *hdl = {0};
static struct __NET_CTP_INFO  net_ctp_info = {0};

static void *sockfd = NULL; //udp通信套接字
static char recv_buf[SOCK_RECV_SIZE];//单次接收数据的缓存
static u32 old_frame_seq = 0; //上一次接收数据的序列号
static int recv_task_pid = 0; //接收线程的线程pid


static int ctp_callback(void *hdl, enum ctp_cli_msg_type type, const char *topic, const char *parm_list, void *priv)
{
    static u16 time_out = 0;
    static u16 close_time = 0;

    const char topic_0[] = {"KEEP_ALIVE_INTERVAL"};//命令名保持间隔活动
    const char content_0[] = {"{\"op\":\"GET\"}"};

    time_out++;


    if (time_out == 100) { //接收到合适的数量后发送一次ALIVE命令
        time_out = 0 ;

        if (ctp_cli_send(hdl, (char *)topic_0, (char *)&content_0) == 0) {
        } else {
            printf("\n [ERROR] %s - %d\n", __FUNCTION__, __LINE__);
        }
    }

    close_time++;

    return 0;
}
/*显示图片到屏幕的函数*/
static void out_to_lcd1(struct __JPG_INFO *info)
{
    int err;
    union video_dec_req dec_req = {0};
    dec_req.dec.fb = "fb2";
    dec_req.dec.left = 0;
    dec_req.dec.top = 0;
    dec_req.dec.width = 800;//指定分辨率显示
    dec_req.dec.height = JPG_SRC_H;
    dec_req.dec.preview = 1;
    dec_req.dec.image.buf = info->buf;
    dec_req.dec.image.size = info->buf_len;

    err = server_request(net_ctp_info.video_dec, VIDEO_REQ_DEC_IMAGE, &dec_req);

    if (err) {
        printf("\n [ERROR] %s - %d\n", __FUNCTION__, __LINE__);
    }
}

static int bytecmp1(unsigned char *p, unsigned char ch, unsigned int num)
{
    while (num-- > 0) {
        if (*p++ != ch) {
            return -1;
        }
    }

    return 0;
}
/*组装jpg图片的函数*/
static int get_jpg_packet(char *buf, int len, struct __JPG_INFO *jpg)
{
    static u32 total_payload_len = 0;
    static u8 finish = 0;
    u32 position = 0;
    u8 frame_type;
    u32 cur_frame_seq, frame_offset, slice_data_len, frame_size;
    u32 frame_head_size = sizeof(struct frm_head);//一个帧头的大小

    if (len < frame_head_size) {
        printf("\n[ERROR] recv_len err\n");
        goto ERROR;
    }

    do {

        struct frm_head  *head_info = (struct frm_head *)(buf + position);
        frame_type = head_info->type & 0x7F; //获取当前包携带的数据的类型
        cur_frame_seq = head_info->seq;
        frame_offset = head_info->offset;
        slice_data_len = head_info->payload_size; //当前包中数据的实际长度
        frame_size = head_info->frm_sz;
        //图片大小大于缓冲buf，不处理
        if (frame_size > JPG_MAX_SIZE) {
            printf("\n [MSG] frame_size too large\n");
            goto ERROR;
        }
        len -= (frame_head_size + slice_data_len);
        if (len < 0) {
            printf("\n[ERROR] remain len err\n");
            goto ERROR;
        }

        switch (frame_type) {

        case JPEG_TYPE_VIDEO:
            //如果当前的seq小于旧的seq,说明是旧的数据包,跳过不处理
            if (cur_frame_seq < old_frame_seq) {
                //printf("\n [MSG] recv old packet");
                goto continue_deal;
            }
            //如果当前seq大于旧的seq,认为是新的数据包,组包重新初始
            if (cur_frame_seq > old_frame_seq) {
                if (total_payload_len && (finish == 0)) {
                    //printf("\n [MSG] lose packet or disorder packet\n");
                }
                old_frame_seq = cur_frame_seq;
                total_payload_len = 0;
                finish = 0;
                memset(jpg->buf, CHECK_CODE, JPG_MAX_SIZE);

            }
            //校验是不是接收到重复的包
            if (bytecmp((char *)jpg->buf + frame_offset, CHECK_CODE, CHECK_CODE_NUM) != 0) {
                //printf("\n [MSG] repeat the packet\n");
                goto continue_deal;

            }
            memcpy(jpg->buf + frame_offset, (buf + position) + frame_head_size, slice_data_len);
            total_payload_len += slice_data_len;
            if (total_payload_len == frame_size) { //如果数据量相等,说明帧数据接收完成
                jpg->buf_len = total_payload_len;
                finish = 1;
                return 0;//返回0表示完成
            }
continue_deal:
            //position是剩余数据的偏移量
            position += (frame_head_size + slice_data_len);
            break;

        default:
            printf("\n [WARING] %s - %d\n", __FUNCTION__, __LINE__);
            break;

        }
    } while (len > 0);


ERROR:
    return -1;
}
/*接收udp数据的线程函数*/
void jpg_recv_thread(void *sockfd)
{
    int recv_len = 0;
    int finish_flag;


    struct __JPG_INFO *jpg = (struct __JPG_INFO *) calloc(1, sizeof(struct __JPG_INFO) + sizeof(u8) * JPG_MAX_SIZE);
    if (!jpg) {
        printf("\n[ERROR]  jpg calloc \n");
    }

    jpg->src_w = JPG_SRC_W;//接收到的图片的长宽
    jpg->src_h = JPG_SRC_H;
    while (1) {

        recv_len = sock_recvfrom(sockfd, recv_buf, sizeof(recv_buf), 0, NULL, NULL);
        if (recv_len < 0) {
            free(jpg);
            break;
        }
        finish_flag = get_jpg_packet(recv_buf, recv_len, jpg);

        if (!finish_flag) {

            finish_flag = -1;
            out_to_lcd1(jpg);

            os_time_dly(3);
        }
    }
EXIT:
    printf("\n[MSG] %s EXIT\n", __func__);
}


/*打开video设备*/
static int net_ctp_video_dec_init(void)
{
    struct video_dec_arg arg_recv = {0};

    arg_recv.dev_name = "video_dec";
    arg_recv.video_buf_size = JPG_MAX_SIZE;//解码图片大小不能超过100kb
    net_ctp_info.video_dec = server_open("video_dec_server", &arg_recv);

    if (net_ctp_info.video_dec == NULL) {
        printf("\n [ERROR] video_dec_server open err\n");
        goto EXIT;
    }

    return 0;

EXIT:

    if (net_ctp_info.video_dec) {
        server_close(net_ctp_info.video_dec);
        net_ctp_info.video_dec = NULL;
    }

    return -1;
}
/*创建udp套接字接收数据*/
static void net_ctp_recv(void)
{
    struct sockaddr_in conn_addr;
    int ret;

    sockfd = sock_reg(AF_INET, SOCK_DGRAM, 0, NULL, NULL);
    if (sockfd == NULL) {
        printf("\n [ERROR] %s - %d\n", __func__, __LINE__);
    }

    if (sock_set_reuseaddr(sockfd)) {
        printf("\n [ERROR] %s - %d\n", __func__, __LINE__);
    }

    conn_addr.sin_family = AF_INET;
    conn_addr.sin_addr.s_addr = inet_addr(USER_IP_SERVER) ;
    conn_addr.sin_port = htons(CONN_PORT);

    ret = net_ctp_video_dec_init();
    if (ret == 0) {
        printf("\n-----net_ctp_dev_init_sueccess----\n");
    }

    if (sock_bind(sockfd, (struct sockaddr *)&conn_addr, sizeof(struct sockaddr)) == -1) {
        printf("\n [ERROR] %s - %d\n",  __func__, __LINE__);
    } else {
        if ((thread_fork("thread_socket_recv", 15, 2 * 1024, 0, &recv_task_pid, jpg_recv_thread, sockfd))) {
            printf("\n [ERROR] %s - %d\n", __func__, __LINE__);
        }
    }
}
/*创建ctp客户端连接服务器并发送命令打开实时流*/
static void net_ctp_init(void)
{
    struct sockaddr_in dest_addr;

    /* 定义命令数组 */
    const char topic_1[] = {"APP_ACCESS"};//app创建命令
    const char topic_2[] = {"DATE_TIME"};//时间命令
    const char topic_3[] = {"OPEN_RT_STREAM"};//打开数据流命令 包括音频视频
    const char topic_4[] = {"VIDEO_CTRL"};//打开数据流命令 包括音频视频

    /* 各个命令的参数 */
    const char content_0[] = {"{\"op\":\"GET\"}"};
    /*const char content_1[] = {"{\"op\":\"PUT\",\"param\":{\"type\":\"1\",\"ver\":\"1.0\"}}"};*/
    const char content_1[] = {"{\"op\":\"PUT\",\"param\":{\"type\":\"0\",\"ver\":\"20700\"}}"};

    //选择摄像头传输的视频数据是什么大小
    /*const char content_3[] = {"{\"op\":\"PUT\",\"param\":{\"rate\":\"8000\",\"w\":\"1280\",\"fps\":\"20\",\"h\":\"720\",\"format\":\"1\"}}"};*/
    const char content_3[] = {"{\"op\":\"PUT\",\"param\":{\"rate\":\"8000\",\"w\":\"640\",\"fps\":\"20\",\"h\":\"480\",\"format\":\"1\"}}"};

    const char content_4[] = {"{\"op\":\"GET\",\"param\":{}"};

    enum wifi_sta_connect_state state;

    while (1) {
        printf("Connecting to the network...\n");
        state = wifi_get_sta_connect_state() ;
        if (WIFI_STA_NETWORK_STACK_DHCP_SUCC == state) {
            printf("Network connection is successful!\n");
            break;
        }
        os_time_dly(1000);
    }

    memset(&dest_addr, 0x0, sizeof(dest_addr));


    net_ctp_recv();//建立sock并创建接收数据线程

    ctp_cli_init();//CTP连接初始化
    /* 建立CTP连接 */
    memset(&dest_addr, 0x0, sizeof(dest_addr)); //对server_info初始化操作，全部清零
    dest_addr.sin_family = AF_INET;
    dest_addr.sin_addr.s_addr = inet_addr(DEST_IP_SERVER) ;
    dest_addr.sin_port = htons(DEST_PORT);
    //建立连接并创建消息回调函数

    hdl = ctp_cli_reg(1, &dest_addr, ctp_callback, NULL);

    if (hdl == NULL) {
        printf("\n--------------CTP_CMD_cli connect failed----------------\n");
    } else {
        printf("\n--------------CTP_CMD_cli connect success---------------\n");
    }


    if (ctp_cli_send(hdl, (char *)&topic_1, (char *)&content_1) == 0) {
    } else {
        printf("\n [ERROR] %s - %d\n", __FUNCTION__, __LINE__);

    }


    if (ctp_cli_send(hdl, (char *)&topic_4, (char *)&content_4) == 0) {
    } else {
        printf("\n [ERROR] %s - %d\n", __FUNCTION__, __LINE__);

    }


    if (ctp_cli_send(hdl, (char *)&topic_3, (char *)&content_3) == 0) {
    } else {
        printf("\n [ERROR] %s - %d\n", __FUNCTION__, __LINE__);

    }


}
/*启动双机图传的线程*/
static image_transmit(void)
{
    printf("\n----------TWO START----------\n");
    return thread_fork("transmit_jpeg_task", 10, 0x1000, 64, 0, net_ctp_init, NULL);
}
late_initcall(image_transmit);
#endif
