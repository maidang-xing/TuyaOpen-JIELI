#ifndef MULTI_MEDIA_RENDERER_H
#define MULTI_MEDIA_RENDERER_H

#include "system/includes.h"
#include "video_stream_recv.h"
#include "video_pipeline.h"

#define MAX_RENDER_CHANNELS         4           // 最大渲染通道数

// 渲染器状态
typedef enum {
    RENDER_STATE_IDLE = 0,
    RENDER_STATE_RUNNING,
    RENDER_STATE_PAUSED,
    RENDER_STATE_ERROR
} render_state_t;

struct video_render_info {
    int src_width;
    int src_height;
    int target_fps;
    u8 is_local;
    u8 local_camera_id;
    struct video_window window;
};

// 渲染通道
struct render_channel {
    char audio_task_name[32];
    char video_task_name[32];
    int audio_task_pid;
    int video_task_pid;
    u8 audio_task_exit;
    u8 video_task_exit;

    u32 channel_id;
    u32 device_ip;
    render_state_t state;

    struct video_stream_recv_hdl *stream_recv;

    struct video_render_info render_info;

    // 视频
    void *video_pipeline;
    // 音频
    void *audio_player;
    // 统计信息
    u32 video_frame_count;
    u32 audio_frame_count;
};

// 多媒体渲染器主结构
struct multi_media_renderer {
    struct render_channel channels[MAX_RENDER_CHANNELS];
    struct video_stream_recv_hdl *stream_recv;
    int active_channel_count;
};


int multi_media_renderer_create(struct multi_media_renderer **renderer);
int multi_media_renderer_init(struct multi_media_renderer *renderer, char *net_path);
int renderer_add_channel(struct multi_media_renderer *renderer, struct video_stream_recv_hdl *stream_recv,
                         struct video_render_info *video_info, u32 device_ip);
int renderer_remove_channel(struct multi_media_renderer *renderer, u32 device_ip);
struct video_window *renderer_get_window_by_device_ip(struct multi_media_renderer *renderer, u32 device_ip);


#endif // MULTI_MEDIA_RENDERER_H

