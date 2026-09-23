#include "multi_media_renderer.h"
#include "video_stream_recv.h"
#include "video_pipeline.h"
#include "audio_player.h"

#define LOG_TAG_CONST       MULTI_MEDIA_RENDERER
#define LOG_TAG             "[MULTI_MEDIA_RENDERER]"
#define LOG_ERROR_ENABLE
#define LOG_INFO_ENABLE
#define LOG_DUMP_ENABLE
#include "debug.h"

static void video_render_task(void *priv);
static void audio_render_task(void *priv);
static int video_renderer_init(struct render_channel *channel);
static void video_renderer_exit(struct render_channel *channel);
static int audio_renderer_init(struct render_channel *channel);
static void audio_renderer_exit(struct render_channel *channel);

static int video_decode_and_display(struct render_channel *channel, u8 *frame_data, u32 frame_size);
static int audio_decode_and_play(struct render_channel *channel, u8 *frame_data, u32 frame_size);
static int video_renderer_pipeline_init(struct render_channel *channel);
static int audio_renderer_player_init(struct render_channel *channel);
static void video_renderer_pipeline_exit(struct render_channel *channel);
static void audio_renderer_player_exit(struct render_channel *channel);
static void deinit_channel(struct render_channel *channel);

int multi_media_renderer_create(struct multi_media_renderer **renderer)
{
    struct multi_media_renderer *r;

    r = malloc(sizeof(struct multi_media_renderer));
    if (!r) {
        log_error("Failed to allocate renderer memory\n");
        return -1;
    }

    memset(r, 0, sizeof(struct multi_media_renderer));

    for (int i = 0; i < MAX_RENDER_CHANNELS; i++) {
        struct render_channel *ch = &r->channels[i];
        ch->channel_id = i;
        ch->state = RENDER_STATE_IDLE;
    }

    *renderer = r;

    log_debug("Multi-media renderer created successfully\n");
    return 0;
}

int multi_media_renderer_init(struct multi_media_renderer *renderer, char *net_path)
{
    // TODO
    return 0;
}

int multi_media_renderer_start(struct multi_media_renderer *renderer)
{
    // TODO
    return 0;
}

int multi_media_renderer_stop(struct multi_media_renderer *renderer)
{
    if (!renderer) {
        return -1;
    }

    // video_stream_recv_stop(renderer->stream_recv);

    for (int i = 0; i < MAX_RENDER_CHANNELS; i++) {
        if (renderer->channels[i].state != RENDER_STATE_IDLE) {
            deinit_channel(&renderer->channels[i]);
        }
    }

    log_debug("Multi-media renderer stopped\n");
    return 0;
}

int multi_media_renderer_destroy(struct multi_media_renderer **renderer)
{
    if (!renderer || !*renderer) {
        return -1;
    }

    struct multi_media_renderer *r = *renderer;

    multi_media_renderer_stop(r);

    if (r->stream_recv) {
        video_stream_recv_destroy(&r->stream_recv);
    }

    free(r);
    *renderer = NULL;

    log_debug("Multi-media renderer destroyed\n");
    return 0;
}

static int video_renderer_init(struct render_channel *channel)
{
    int ret;

    if (video_renderer_pipeline_init(channel) != 0) {
        log_error("Failed to init video renderer for device %x\n", channel->device_ip);
        channel->state = RENDER_STATE_IDLE;
        return -1;
    }
    if (channel->render_info.is_local) {
        log_debug("Render video channel %d using local camera %d\n",
                  channel->channel_id, channel->render_info.local_camera_id);
        return 0;
    }

    snprintf(channel->video_task_name, sizeof(channel->video_task_name),
             "video_render_ch_%d", channel->channel_id);
    channel->video_task_exit = 0;
    ret = thread_fork(channel->video_task_name, 11, 2048, 2048,
                      &channel->video_task_pid, video_render_task, channel);
    if (ret) {
        log_error("Failed to create video render task\n");
        video_renderer_pipeline_exit(channel);
        return -1;
    }

    return 0;
}
static void video_renderer_exit(struct render_channel *channel)
{
    if (channel->video_task_pid) {
        channel->video_task_exit = 1;
        thread_kill(&channel->video_task_pid, KILL_WAIT);
        channel->video_task_exit = 0;
    }
    video_renderer_pipeline_exit(channel);
}

static int audio_renderer_init(struct render_channel *channel)
{
    int ret;

    if (audio_renderer_player_init(channel) != 0) {
        log_error("Failed to init audio renderer for device %x\n", channel->device_ip);
        channel->state = RENDER_STATE_IDLE;
        return -1;
    }
    if (channel->render_info.is_local) {
        log_debug("Render audio channel %d using local camera %d\n",
                  channel->channel_id, channel->render_info.local_camera_id);
        return 0;
    }

    snprintf(channel->audio_task_name, sizeof(channel->audio_task_name),
             "audio_render_ch_%d", channel->channel_id);
    channel->audio_task_exit = 0;
    ret = thread_fork(channel->audio_task_name, 12, 2048, 2048,
                      &channel->audio_task_pid, audio_render_task, channel);
    if (ret) {
        log_error("Failed to create audio render task\n");
        audio_renderer_player_exit(channel);
        return -1;
    }

    return 0;
}

static void audio_renderer_exit(struct render_channel *channel)
{
    if (channel->audio_task_pid) {
        channel->audio_task_exit = 1;
        thread_kill(&channel->audio_task_pid, KILL_WAIT);
        channel->audio_task_exit = 0;
    }
    audio_renderer_player_exit(channel);
}

int renderer_add_channel(struct multi_media_renderer *renderer, struct video_stream_recv_hdl *stream_recv,
                         struct video_render_info *video_info, u32 device_ip)
{
    int ret;

    if (!renderer || !video_info) {
        return -1;
    }

    for (int i = 0; i < MAX_RENDER_CHANNELS; i++) {
        if (renderer->channels[i].device_ip == device_ip &&
            renderer->channels[i].state != RENDER_STATE_IDLE) {
            log_info("Render channel for device %x already exists\n", device_ip);
            return 0;
        }
    }

    struct render_channel *channel = NULL;
    for (int i = 0; i < MAX_RENDER_CHANNELS; i++) {
        if (renderer->channels[i].state == RENDER_STATE_IDLE) {
            channel = &renderer->channels[i];
            break;
        }
    }
    if (!channel) {
        log_error("No available render channel for device %x\n", device_ip);
        return -1;
    }
    channel->device_ip = device_ip;
    channel->stream_recv = stream_recv;
    channel->render_info = *video_info;

    if (video_renderer_init(channel) != 0) {
        goto error;
    }
    if (audio_renderer_init(channel) != 0) {
        goto error;
    }

    channel->state = RENDER_STATE_RUNNING;

    renderer->active_channel_count++;

    log_debug("Added render channel for device %x at window %d\n", device_ip);
    return 0;
error:
    deinit_channel(channel);
    return -1;
}

int renderer_remove_channel(struct multi_media_renderer *renderer, u32 device_ip)
{
    if (!renderer) {
        return -1;
    }

    for (int i = 0; i < MAX_RENDER_CHANNELS; i++) {
        struct render_channel *ch = &renderer->channels[i];
        if (ch->device_ip == device_ip && ch->state != RENDER_STATE_IDLE) {
            deinit_channel(ch);

            if (renderer->active_channel_count > 0) {
                renderer->active_channel_count--;
            }

            log_debug("Removed render channel for device %x\n", device_ip);
            return 0;
        }
    }
    log_error("Device %x not found in render channels\n", device_ip);
    return -1;
}

struct video_window *renderer_get_window_by_device_ip(struct multi_media_renderer *renderer, u32 device_ip)
{
    if (!renderer) {
        return NULL;
    }
    for (int i = 0; i < MAX_RENDER_CHANNELS; i++) {
        struct render_channel *ch = &renderer->channels[i];
        if (ch->device_ip == device_ip && ch->state != RENDER_STATE_IDLE) {
            return &ch->render_info.window;
        }
    }
    log_warn("Device %x not found in render channels\n", device_ip);
    return NULL;
}

static void video_render_task(void *priv)
{
    struct render_channel *ch = (struct render_channel *)priv;
    struct video_render_info *render_info = &ch->render_info;
    u8 frame_duration_ms = 1000 / render_info->target_fps;
    u8 delay_tick  = frame_duration_ms / 10;
    u8 *frame_buf;
    u32 display_time_ms = 0;
    int frame_count = 0;
    int frame_kbps = 0;
    int frame_len;
    int ret;

    log_debug("Video render task started for device %x\n", ch->device_ip);

    while (!ch->video_task_exit) {
        if (ch->state != RENDER_STATE_RUNNING) {
            os_time_dly(delay_tick);
            continue;
        }

        ret = video_stream_recv_acquire_frame_block(ch->stream_recv, ch->device_ip,
                &frame_buf, &frame_len, VIDEO_FRAME, 1000);
        if (ret == 0 && frame_len > 0) {
            video_decode_and_display(ch, frame_buf, frame_len);
            video_stream_recv_release_frame(ch->stream_recv, frame_buf);
            ch->video_frame_count++;
            frame_count++;
            frame_kbps += frame_len * 8 / 1024;

            if (timer_get_ms() - display_time_ms > 1000) {
                log_debug("channel[%d] fps:%d kbps:%d\n", ch->channel_id, frame_count, frame_kbps);
                //UI DEBUG
                void gui_video_call_set_video_fps_label(int fps);
                gui_video_call_set_video_fps_label(frame_count);
                display_time_ms = timer_get_ms();
                frame_count = 0;
                frame_kbps = 0;
            }

        } else {
            os_time_dly(delay_tick);
        }
    }

    log_debug("Video render task exited\n");
}

static void audio_render_task(void *priv)
{
    struct render_channel *ch = (struct render_channel *)priv;
    u8 *frame_buf;
    int frame_len;
    int ret;
    int data_size = 0;
    u32 render_time_ms = 0;

    log_debug("Audio render task started for device %x\n", ch->device_ip);

    while (!ch->audio_task_exit) {
        if (ch->state != RENDER_STATE_RUNNING) {
            os_time_dly(2);
            continue;
        }

        ret = video_stream_recv_acquire_frame_block(ch->stream_recv, ch->device_ip,
                &frame_buf, &frame_len, AUDIO_FRAME, 1000);
        if (ret == 0 && frame_len > 0) {
            audio_decode_and_play(ch, frame_buf, frame_len);
            video_stream_recv_release_frame(ch->stream_recv, frame_buf);
            data_size += frame_len;

            if (timer_get_ms() - render_time_ms > 1000) {
                log_debug("channel[%d] audio data:%dByte/s\n", ch->channel_id, data_size);
                render_time_ms = timer_get_ms();
                data_size = 0;
            }

            ch->audio_frame_count++;
        } else {
            os_time_dly(2);
        }
    }
    log_debug("Audio render task exited\n");
}

static int video_decode_and_display(struct render_channel *channel, u8 *frame_data, u32 frame_size)
{
    return pipeline_dec_one_frame(channel->video_pipeline, frame_data, frame_size);
}

static int audio_decode_and_play(struct render_channel *channel, u8 *frame_data, u32 frame_size)
{
    return audio_player_one_frame(frame_data, frame_size);
}

static int video_renderer_pipeline_init(struct render_channel *channel)
{
    if (!channel) {
        return -1;
    }

    struct video_format f = {0};
    struct video_window *window = &channel->render_info.window;
    int src_width = channel->render_info.src_width;
    int src_height = channel->render_info.src_height;
    u8 camera_id = channel->render_info.local_camera_id;

    //本地设备
    if (channel->render_info.is_local) {
        //摄像头自动读取源头宽高
        src_width = 0;
        src_height = 0;
        pipeline_format_init(&f, window, src_width, src_height, NULL);
        pipeline_camera_init(&channel->video_pipeline, &f, camera_id);
    } else {
        //远程设备
        pipeline_format_init(&f, window, src_width, src_height, NULL);
        pipeline_dec_init(&channel->video_pipeline, &f);
    }

    return 0;
}

static void video_renderer_pipeline_exit(struct render_channel *channel)
{
    if (!channel || !channel->video_pipeline) {
        return;
    }
    pipeline_exit(&channel->video_pipeline);
}

static int audio_renderer_player_init(struct render_channel *channel)
{
    return audio_player_init();
}

static void audio_renderer_player_exit(struct render_channel *channel)
{
    audio_player_exit();
}



static void deinit_channel(struct render_channel *channel)
{
    channel->state = RENDER_STATE_IDLE;
    channel->device_ip = 0;
    channel->video_frame_count = 0;
    channel->audio_frame_count = 0;

    video_renderer_exit(channel);
    audio_renderer_exit(channel);

    log_debug("Channel %d deinitialized\n", channel->channel_id);
}



