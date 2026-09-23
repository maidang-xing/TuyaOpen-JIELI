#include "server/video_server.h"
#include "vrec_osd.h"
#include "app_config.h"
#include "stream_core.h"
#include "video_stream_send.h"
#include "vir_audio_recoder.h"
#include "udp_stream.h"


#define LOG_TAG_CONST       VIDEO_STREAM_SEND
#define LOG_TAG             "[VIDEO_STREAM_SEND]"
#define LOG_ERROR_ENABLE
#define LOG_INFO_ENABLE
#define LOG_DUMP_ENABLE
#include "debug.h"


static void video_server_event_handler(void *priv, int argc, int *argv);

static void default_stream_buffer_config(struct stream_buffer_config *buffer_cfg)
{
    buffer_cfg->video_buf_size = STREAM_SEND_VIDEO_BUF_SIZE;
    buffer_cfg->audio_buf_size = STREAM_SEND_AUDIO_BUF_SIZE;
    buffer_cfg->osd_buf_size   = STREAM_SEND_OSD_BUF_SIZE;
}
static void default_video_config(struct video_config *video_cfg, struct video_stream_info *stream_info)
{
    video_cfg->fps        = stream_info->fps;
    video_cfg->width      = stream_info->img_width;
    video_cfg->height     = stream_info->img_height;
    video_cfg->abr_kbps   = stream_info->bitrate_kbps;
    video_cfg->online     = stream_info->online;
    video_cfg->osd_enable = stream_info->osd_enable;
    video_cfg->device_id  = stream_info->device_id;
}
static void default_audio_config(struct audio_config *audio_cfg, struct video_stream_info *stream_info)
{
    audio_cfg->sample_rate   = stream_info->sample_rate;
    audio_cfg->channel       = stream_info->channel;
    audio_cfg->volume        = stream_info->volume;
    audio_cfg->interval_size = stream_info->aud_interval_size;
    audio_cfg->audio_enable  = stream_info->audio_enable;
}

static void stream_buffer_free(struct stream_buffer_config *buf_cfg)
{
    if (buf_cfg->video_buf) {
        free(buf_cfg->video_buf);
        buf_cfg->video_buf = NULL;
    }
    if (buf_cfg->video_osd_buf) {
        free(buf_cfg->video_osd_buf);
        buf_cfg->video_osd_buf = NULL;
    }
    if (buf_cfg->audio_buf) {
        free(buf_cfg->audio_buf);
        buf_cfg->audio_buf = NULL;
    }
}

static int stream_buffer_alloc(struct stream_buffer_config *buf_cfg,
                               struct audio_config *audio_cfg,
                               struct video_config *video_cfg)
{
    if (buf_cfg->video_buf_size > 0) {
        buf_cfg->video_buf = malloc(buf_cfg->video_buf_size);
        if (!buf_cfg->video_buf) {
            log_error("malloc server video buffer err ! size:%d \n", buf_cfg->video_buf_size);
            goto err;
        }
    }

    if (video_cfg->osd_enable && buf_cfg->osd_buf_size > 0) {
        buf_cfg->video_osd_buf = malloc(buf_cfg->osd_buf_size);
        if (!buf_cfg->video_osd_buf) {
            log_error("malloc server osd buffer err ! size:%d \n", buf_cfg->osd_buf_size);
            goto err;
        }
        memset(buf_cfg->video_osd_buf, 0x00, buf_cfg->osd_buf_size);
    }

    if (audio_cfg->audio_enable && buf_cfg->audio_buf_size > 0) {
        buf_cfg->audio_buf = malloc(buf_cfg->audio_buf_size);
        if (!buf_cfg->audio_buf) {
            log_error("malloc server audio buffer err ! size:%d \n", buf_cfg->audio_buf_size);
            goto err;
        }
    }
    return 0;

err:
    stream_buffer_free(buf_cfg);
    return -1;
}

static void video_text_osd_init(struct video_text_osd *text_osd, char *osd_buf, int width, int height)
{
    memset(osd_buf, ' ', 8);
    osd_buf[8] = '\\';
    memcpy(osd_buf + 9, osd_str_buf, strlen(osd_str_buf));
    text_osd->font_w = 16;
    text_osd->font_h = 32;
    int max_one_line_strnum = strlen(osd_buf);
    int osd_line_num = 1;
    int osd_max_heigh = (height == 1088) ? 1080 : height ;
    text_osd->x = (width - max_one_line_strnum * text_osd->font_w) / 64 * 64;
    text_osd->y = (osd_max_heigh - text_osd->font_h * osd_line_num) / 16 * 16;
    text_osd->color[0] = 0x057d88;
    text_osd->color[1] = 0xe20095;
    text_osd->color[2] = 0xe20095;
    text_osd->bit_mode = 2;
    text_osd->text_format = osd_buf;
    text_osd->font_matrix_table = osd_str_total;
    text_osd->font_matrix_base = osd2_str_matrix;
    text_osd->font_matrix_len = sizeof(osd2_str_matrix);
    text_osd->direction = 1;

}

static void audio_recoder_data_cb(void *priv, u8 *data, u32 len)
{
    //log_debug("audio len:%d \n", len);
    u8 type = 1;
    net_rt_send_frame(data, len, type);
}

static void video_recoder_data_cb(u8 type, u8 *data, u32 len)
{
    //log_debug("audio len:%d \n", len);
    net_rt_send_frame(data, len, type);
}



int video_stream_send_create(struct video_stream_send_hdl **hdl)
{
    struct video_stream_send_hdl *stream_hdl;
    stream_hdl = malloc(sizeof(struct video_stream_send_hdl));
    if (!stream_hdl) {
        log_error(" stream send hdl alloc err \n");
        return -1;
    }
    memset(stream_hdl, 0x00, sizeof(struct video_stream_send_hdl));

    *hdl = stream_hdl;
    return 0;
}

int video_stream_send_init(struct video_stream_send_hdl *stream_hdl,
                           struct video_stream_info *stream_info, char *net_path)
{
    stream_hdl->net_path = net_path;

    default_stream_buffer_config(&stream_hdl->buffer_cfg);
    default_video_config(&stream_hdl->video_cfg, stream_info);
    default_audio_config(&stream_hdl->audio_cfg, stream_info);

    if (stream_buffer_alloc(&stream_hdl->buffer_cfg,
                            &stream_hdl->audio_cfg,
                            &stream_hdl->video_cfg) != 0) {
        return -1;
    }
    return 0;
}

int video_stream_send_destroy(struct video_stream_send_hdl **hdl)
{
    struct video_stream_send_hdl *stream_hdl = *hdl;
    if (!stream_hdl) {
        return -1;
    }

    if (stream_hdl->video_server) {
        server_close(stream_hdl->video_server);
        stream_hdl->video_server = NULL;
    }

    stream_buffer_free(&stream_hdl->buffer_cfg);

    free(stream_hdl);
    *hdl = NULL;

    return 0;
}

int video_stream_send_start(struct video_stream_send_hdl *hdl)
{
    int ret = 0;
    char dev_name[16];
    union video_req req = {0};
    struct video_text_osd text_osd;
    struct video_config *video_cfg = &hdl->video_cfg;
    struct audio_config *audio_cfg = &hdl->audio_cfg;
    struct stream_buffer_config *buffer_cfg = &hdl->buffer_cfg;

    snprintf(dev_name, sizeof(dev_name), "video%d.%d", video_cfg->device_id, 0);
    hdl->video_server = server_open("video_server", dev_name);
    if (!hdl->video_server) {
        log_error("video server open err dev_name:%s !\n", dev_name);
        return -1;
    }
    server_register_event_handler(hdl->video_server, hdl, video_server_event_handler);

    //video
    req.rec.channel     = 0;
    req.rec.state       = VIDEO_STATE_START;
    req.rec.quality     = VIDEO_MID_Q;

    req.rec.width       = video_cfg->width;
    req.rec.height      = video_cfg->height;
    req.rec.real_fps    = video_cfg->fps;
    req.rec.abr_kbps    = video_cfg->abr_kbps;
    req.rec.online      = video_cfg->online;
    req.rec.buf         = buffer_cfg->video_buf;
    req.rec.buf_len     = buffer_cfg->video_buf_size;
    //osd
    if (video_cfg->osd_enable) {
        video_text_osd_init(&text_osd, buffer_cfg->video_osd_buf, video_cfg->width, video_cfg->height);
        req.rec.text_osd = &text_osd;
    }

    struct net_stream_info s_info = {0};
    s_info.sample_rate = audio_cfg->sample_rate;
    s_info.fps = video_cfg->fps;
    s_info.abr_kbps = video_cfg->abr_kbps;

    ret = net_rt_vpkg_open(hdl->net_path, &s_info);
    if (ret) {
        log_error("open udp stream fail \n");
        return -1;
    }

    req.rec.format  = USER_VIDEO_FMT_AVI;
    req.rec.packet_cb = video_recoder_data_cb;      //视频数据回调
    req.rec.cycle_time = 5 * 60;

    //audio
    if (audio_cfg->audio_enable) {
        u32 coding_type = AUDIO_CODING_PCM;

#if BBM_AUDIO_OPUS_ENABLE
        coding_type = AUDIO_CODING_OPUS;
#endif

        hdl->audio_recoder = vir_audio_recoder_open(audio_cfg->sample_rate,
                             coding_type,
                             NULL,
                             audio_recoder_data_cb);    //音频数据回调
    }

    ret = server_request(hdl->video_server, VIDEO_REQ_REC, &req);
    if (ret) {
        log_error("start video stream send err :%d \n", ret);
        return -1;
    }

    return 0;
}

int video_stream_send_stop(struct video_stream_send_hdl *hdl)
{
    int ret = 0;
    union video_req req = {0};

    if (!hdl->video_server) {
        return -1;
    }

    if (hdl->audio_recoder) {
        vir_audio_recoder_close(hdl->audio_recoder);
        hdl->audio_recoder = NULL;
    }

    req.rec.channel = 0;
    req.rec.state = VIDEO_STATE_STOP;
    ret = server_request(hdl->video_server, VIDEO_REQ_REC, &req);
    if (ret) {
        log_error("stop video stream send err :%d \n", ret);
        return -1;
    }

    net_rt_vpkg_close();

    return 0;
}

static void video_server_event_handler(void *priv, int argc, int *argv)
{
    switch (argv[0]) {
    case VIDEO_SERVER_UVM_ERR:
        log_error("APP_UVM_DEAL_ERR\n");
        break;
    case VIDEO_SERVER_PKG_ERR:
        log_error("VIDEO_SERVER_PKG_ERR\n");
        break;
    case VIDEO_SERVER_PKG_END:
        log_error("VIDEO_SERVER_PKG_END\n");
        break;
    case VIDEO_SERVER_NET_ERR:
        log_error("VIDEO_SERVER_NET_ERR\n");
        break;
    default :
        log_error("unknow rec server cmd %x , %x!\n", argv[0], (int)priv);
        break;
    }
}

