#include "rt_stream_pkg.h"
#include "server/video_server.h"//app_struct
#include "server/video_dec_server.h"//dec_struct
#include "app_config.h"
#include "asm/debug.h"
#include "asm/osd.h"
#include "asm/isc.h"
#include "os/os_api.h"
#include "stream_protocol.h"
#include "server/net_server.h"
#include "wifi/wifi_connect.h"
#include "syscfg/syscfg_id.h"

#define RAW_STREAM_SEND //打开这个宏作为数据发送端，关闭宏作为接收端

#define jl_ntohl(x) (u32)((((u32)(x))>>24) | ((((u32)(x))>>8)&0xff00) | (((u32)(x))<<24) | ((((u32)(x))&0xff00)<<8))

#define JL_ENDF     	jl_ntohl(0x56185719)
#define JPEG_HEAD 		0xE0FFD8FF
#define JPEG_HEAD1 		0xC0FFD8FF
#define JL_000DC		jl_ntohl(0x30306463)
#define JL_001WB		jl_ntohl(0x30317762)

struct user_video_hdl {
    u8 state;
    u8 page_turning;
    u8 req_send;
    u8 *user_isc_buf;
    u8 *user_video_buf;
    /* u8 *user_audio_buf; */
    struct server *user_video_rec;
    u32(*video_rt_cb)(void *, u8 *, u32);
    void *cb_priv;
};
#define WIFI_TX_MAX_DATA_LEN 2490//单次发包最大值
#define JPG_MAX_SIZE 100*1024
enum wifi_tx_rate rate = WIFI_TXRATE_11M;//发送速率
static u32 seq = 1;
char send_buf[JPG_MAX_SIZE];

#define CHECK_CODE 0x88
#define CHECK_CODE_NUM 32
#define JPG_MAX_SIZE 100*1024
struct video_photo_handler {
    struct server *quick_preview;
};
struct video_photo_handler photo1;
#define __this  (&photo1)

static u8 jpg_buf[100 * 1024];
static u32 old_seq = 0;
static u32 jpeg_total_payload_len = 0;
static u8 jpeg_finish = 0;
/*接收数据*/
//打开解码设备
static int video_dec_init(void)
{
    if (!__this->quick_preview) {
        struct video_dec_arg arg = {0};
        arg.dev_name = "video_dec";
        arg.video_buf_size = JPG_MAX_SIZE;
        __this->quick_preview = server_open("video_dec_server", &arg);
        if (!__this->quick_preview) {
            printf("open video_dec_server fail");
            return -EFAULT;
        }
    }
}
//推屏函数
static void out_to_lcd(u8 *buf, u32 size)
{
    int err = 0;
    union video_dec_req dec_req;
    dec_req.dec.fb = "fb2";
    dec_req.dec.left = 0;
    dec_req.dec.top = 0;
    dec_req.dec.width = 800;//屏幕的宽高
    dec_req.dec.height = 480;
    dec_req.dec.thm_first = 0;
    dec_req.dec.pctl = NULL;
    dec_req.dec.preview = 1;
    dec_req.dec.image.buf = buf;
    dec_req.dec.image.size = size;
    err = server_request(__this->quick_preview, VIDEO_REQ_DEC_IMAGE, &dec_req);
    if (err) {
        printf("\n [ERROR] %s - %d\n", __FUNCTION__, __LINE__);
    }
}



static int bytecmp(unsigned char *p, unsigned char ch, unsigned int num)
{
    while (num-- > 0) {
        if (*p++ != ch) {
            return -1;
        }
    }
    return 0;
}
/*接收数据端的mac地址、数据源的mac地址、发送端的mac地址*/
static const u8 pkg_head_fill_magic[] = {
    /*dst*/ 0x7c, 0xfe, 0x85, 0xab, 0x03, 0xa8,/*src*/ 0xf8, 0xe2, 0xbd, 0xe9, 0xd6, 0xb9,/*BSSID*/ 0xf8, 0xe2, 0xbd, 0xe9, 0xd6, 0xb9,
};

/*接收到数据的回调函数*/
static void wifi_rx_cb(void *rxwi, struct ieee80211_frame *wh, void *data, u32 len, void *reserve)
{
    u32 position = 0;
    u32 jpg_position = 0;
    u32 frame_head_size = sizeof(struct frm_head);
    u8 frame_type;
    u32 cur_frame_seq;
    u32 frame_offset;
    u32 slice_data_len;
    u32 frame_size;
    //判断数据mac地址是否正确
    if (len < 25 || memcmp(&((u8 *)data)[28], pkg_head_fill_magic, sizeof(pkg_head_fill_magic))) {
        return;
    }

    u8 *payload = &((u8 *)data)[48];
    u32 payload_len = len - 24;
    do {
        struct frm_head *head = (struct frm_head *)(payload + position);
        frame_type = head->type & 0x7F;
        cur_frame_seq = head->seq;
        frame_offset = head->offset;
        slice_data_len = head->payload_size;
        frame_size = head->frm_sz;
        payload_len -= (frame_head_size + slice_data_len);
        if (frame_offset + slice_data_len > JPG_MAX_SIZE) {
            printf("\n%s %d->large data pcm buf too small\n", __func__, __LINE__);
            return;
        }

        if (cur_frame_seq < old_seq) { //如果当前的seq小于旧的seq,说明是旧的数据包,跳过不处理
            printf("\n%s %d->jpeg_recv old seq\n", __func__, __LINE__);
            goto continue_deal;

        } else if (cur_frame_seq > old_seq) { //如果当前seq大于旧的seq,认为是新的数据包,接收包初始化
            old_seq = cur_frame_seq;
            jpeg_total_payload_len = 0;
            memset(jpg_buf, CHECK_CODE, 100 * 1024);
        }

        if (bytecmp((unsigned char *)jpg_buf + frame_offset, CHECK_CODE, CHECK_CODE_NUM) != 0) {
            //printf("\n%s %d->jpeg_repeat seq\n", __func__, __LINE__);
            goto continue_deal;

        }

        memcpy(jpg_buf + frame_offset, payload + frame_head_size, slice_data_len);//对应数据放置到对应的位置

        jpeg_total_payload_len += slice_data_len;//累加总长度
        if (jpeg_total_payload_len == frame_size) { //如果数据量相等,说明帧数据接收完成
            //printf("seq = %d",cur_frame_seq);
            out_to_lcd(jpg_buf, jpeg_total_payload_len);
        }

continue_deal:
        position += (frame_head_size + slice_data_len);
        break;

    } while (payload_len > 0);
}

/*发送数据*/
static int raw_sen_data(u8 *buf, u32 size)
{
    u16 payload_len = 0;
    u32 total_udp_send = 0;
    struct frm_head frame_head = {0};
    u32 remain_len = size;
    frame_head.offset = 0;
    frame_head.frm_sz = size;
    frame_head.type &= ~LAST_FREG_MAKER;
    frame_head.type |= JPEG_TYPE_VIDEO;//设置发送数据的包头

    frame_head.seq = seq++;

    while (remain_len) {

        if (remain_len < WIFI_TX_MAX_DATA_LEN) {
            payload_len = remain_len;
            frame_head.type |= LAST_FREG_MAKER;
        } else {
            payload_len = WIFI_TX_MAX_DATA_LEN;
        }

        frame_head.payload_size = payload_len;
        total_udp_send = 0;
        memcpy(send_buf + total_udp_send, &frame_head, sizeof(struct frm_head));
        total_udp_send += sizeof(struct frm_head);

        memcpy(send_buf + total_udp_send, buf + frame_head.offset, payload_len);

        total_udp_send += payload_len;

        if (total_udp_send <= (WIFI_TX_MAX_DATA_LEN + 20)) {
            u8 *pos = wifi_get_payload_ptr();
            memcpy(pos, send_buf, total_udp_send);
            wifi_send_data(total_udp_send, rate);

        } else {
            printf("total_udp_send over limit !!! \n");
            break;
        }
        remain_len -= payload_len;
        frame_head.offset += payload_len;
        memset(send_buf, 0, JPG_MAX_SIZE);
    }
    return 0;
}
//设置码率
static int raw_video_get_abr(u32 width)
{
    if (width <= 640) {
        return 3000;
    } else {
        return 4000;
    }
}
//接收摄像头帧的回调函数
static int raw_callback(u8 type, u8 *buf, u32 size)
{
    u32 *head = (u32 *)buf;
    if (type == JPEG_TYPE_VIDEO) {
        if ((*head == JL_000DC && *(head + 2) == JPEG_HEAD) || *(head + 2) == JPEG_HEAD ||
            (*head == JL_000DC && *(head + 2) == JPEG_HEAD1) || *(head + 2) == JPEG_HEAD1) {
            buf += 8;
            size -= 8;
        }
        raw_sen_data(buf, size);
    }
    return 0;
}
//打开摄像头
static void raw_video_open(void)
{
    int err = 0;
    union video_req req = {0};
    char path[48];

    struct user_video_hdl *handle = (struct user_video_hdl *)zalloc(sizeof(struct user_video_hdl));
    if (!handle) {
        printf("user_video open fail\n");
        return;
    }

    handle->user_video_buf = malloc(CONFIG_USER_VIDEO_SBUF_SIZE);
    if (!handle->user_video_buf) {
        printf("no mem");
        goto __exit;
    }

    handle->user_isc_buf = malloc(CONFIG_USER_VIDEO_ISC_SBUF_SIZE);
    if (!handle->user_isc_buf) {
        printf("no mem");
        goto __exit;
    }

    handle->user_video_rec = server_open("video_server",  "video0.1");//使用的是mipi摄像头
    if (!handle->user_video_rec) {
        goto __exit;
    }

    req.rec.camera_type = VIDEO_CAMERA_NORMAL;
    req.rec.channel = 1;
    req.rec.width   = CONFIG_USER_VIDEO_WIDTH;
    req.rec.src_w   = CONFIG_USER_VIDEO_WIDTH;
    req.rec.height  = CONFIG_USER_VIDEO_HEIGHT;
    req.rec.src_h   = CONFIG_USER_VIDEO_HEIGHT;
    req.rec.state   = VIDEO_STATE_START;
    req.rec.format  = USER_VIDEO_FMT_AVI;
    req.rec.quality = VIDEO_LOW_Q;//VIDEO_MID_Q;
    req.rec.fps     = CONFIG_USER_VIDEO_REC_FPS;
    req.rec.enable_dri = 0;
    req.rec.online = 1;

    req.rec.real_fps = 15;//摄像头帧率
    req.rec.cycle_time = 60;
    //需要音频：请写audio.sample_rate和audio.buf、audio.buf_len
    req.rec.audio.sample_rate = CONFIG_USER_VIDEO_REC_AUDIO_SAMPLE_RATE;//音频采样率
    req.rec.audio.channel = 1;
    req.rec.audio.volume = 100;//音频增益0-100
    req.rec.audio.buf = NULL;//音频BUFF
    req.rec.audio.buf_len = 0;//音频BUFF长度
    req.rec.audio.aud_interval_size = 1024;
    req.rec.abr_kbps = raw_video_get_abr(req.rec.width);//JPEG图片码率
    req.rec.buf = handle->user_video_buf;
    req.rec.buf_len = CONFIG_USER_VIDEO_SBUF_SIZE;


    err = server_request(handle->user_video_rec, VIDEO_REQ_REC, &req);
    if (err != 0) {
        printf("user start rec err");
        goto __exit;
    }

    req.rec.packet_cb = raw_callback;//注册数据包回调函数进行协议转发

    err = server_request(handle->user_video_rec, VIDEO_REQ_SET_PACKET_CALLBACK, &req);
    if (err != 0) {
        printf("stream_packet_cb set err");//xsend设置了不需要再次设置回调
    }


    handle->state = true;

    printf("user video rec open ok");

    return;
__exit:
    if (handle->user_video_rec) {
        memset(&req, 0, sizeof(req));
        req.rec.channel = 1;
        req.rec.state = VIDEO_STATE_STOP;
        server_request(handle->user_video_rec, VIDEO_REQ_REC, &req);
        server_close(handle->user_video_rec);
        handle->user_video_rec = NULL;
    }
    if (handle->user_video_buf) {
        free(handle->user_video_buf);
        handle->user_video_buf = NULL;
    }
    if (handle->user_isc_buf) {
        free(handle->user_isc_buf);
        handle->user_isc_buf = NULL;
    }

    free(handle);
    return;

}

//使用的时候可以注释掉wifi_app_task线程，还有app_main里面的lvgl_v8的代码避免冲突。可以直接在main里面使用
void wifi_raw_tx_rx_test_task(void)
{
    //打开video设备
#ifndef RAW_STREAM_SEND
    video_dec_init();
#endif

    wifi_raw_on(0);
    wifi_set_rts_threshold(0xffff);//配置即使长包也不发送RTS
    u8 *addr = wifi_get_wifi_send_pkg_ptr();
    u8 *aim_addr = addr + 24;
    memcpy(aim_addr, pkg_head_fill_magic, 20);
    wifi_set_long_retry(0);
    wifi_set_short_retry(0);
    wifi_set_channel(14);
    wifi_set_frame_cb(wifi_rx_cb, NULL);//设置接收数据的回调函数
#ifdef RAW_STREAM_SEND
    raw_video_open();
#endif
}
