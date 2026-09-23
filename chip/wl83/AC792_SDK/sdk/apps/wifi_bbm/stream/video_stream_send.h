#ifndef VIDEO_STREAM_SEND_H
#define VIDEO_STREAM_SEND_H

#include "system/includes.h"
#include "video_stream_common.h"

// 发送缓存配置
#define STREAM_SEND_OSD_BUF_SIZE         64                  //发送水印缓存
#define STREAM_SEND_VIDEO_BUF_SIZE       200*1024            //发送视频缓存
#define STREAM_SEND_AUDIO_BUF_SIZE       0 //video_server音频才需要buff                  //发送音频缓存

struct video_config {
    int fps;
    int width;
    int height;
    int online;
    int abr_kbps;
    int osd_enable;
    int device_id;
};

struct audio_config {
    int sample_rate;
    int channel;
    int volume;
    int interval_size;
    int audio_enable;
};

struct stream_buffer_config {
    int video_buf_size;
    int audio_buf_size;
    int osd_buf_size;
    char *video_buf;
    char *audio_buf;
    char *video_osd_buf;
};

struct video_stream_send_hdl {
    char *net_path;
    void *video_server;
    void *audio_recoder;

    struct stream_buffer_config buffer_cfg;
    struct video_config video_cfg;
    struct audio_config audio_cfg;
};

int video_stream_send_create(struct video_stream_send_hdl **hdl);
int video_stream_send_destroy(struct video_stream_send_hdl **hdl);
int video_stream_send_init(struct video_stream_send_hdl *stream_hdl,
                           struct video_stream_info *stream_info, char *net_path);
int video_stream_send_start(struct video_stream_send_hdl *hdl);
int video_stream_send_stop(struct video_stream_send_hdl *hdl);


#endif // VIDEO_STREAM_SEND_H

