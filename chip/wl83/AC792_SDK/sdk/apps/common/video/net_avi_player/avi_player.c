#include "jlstream.h"
#include "audio_def.h"
#include "vir_dev_player.h"
#include "file_player.h"
#include "avi_player.h"
#include "lcd_config.h"
#include "pipeline_jpeg_dec.h"

struct avi_player {
    //音频渲染
    void *audio_player;
    int audio_exit;
    struct avi_frame_lbuf_node *current_audio_node;
    u32 current_offset;
    u32 audio_pts;
    OS_SEM audio_pause_sem;

    int player_state;

    //视频渲染
    void *video_player;
    int video_task_exit;
    int video_task_pid;
    float video_pts;
    OS_SEM video_pause_sem;

    struct avi_info info;
    struct avi_frame_queue frame_queue;

    avi_player_event_callback_t event_callback;
    void *event_priv;
    u8 play_end;
};

static int virtual_dev_seek(void *file, int offset, int fromwhere);
static int virtual_dev_close(void *file);
static int virtual_dev_read(void *file, u8 *buf, int len);
static int virtual_dev_get_fmt(void *file, struct stream_fmt *fmt);
static void avi_video_play_task(void *priv);
static int avi_video_init(struct avi_player *avi);
static void avi_video_exit(struct avi_player *avi);
static int avi_audio_init(struct avi_player *avi);
static void avi_audio_exit(struct avi_player *avi);

static const struct stream_file_ops virtual_dev_ops = {
    .read       = virtual_dev_read,
    .seek       = virtual_dev_seek,
    .close      = virtual_dev_close,
    .get_fmt    = virtual_dev_get_fmt,
};


struct avi_player *avi_player_init(struct avi_info *info, struct avi_frame_queue *frame_queue,
                                   avi_player_event_callback_t event_callback,
                                   void *event_priv)
{
    struct avi_player *avi = NULL;
    avi = malloc(sizeof(struct avi_player));
    if (!avi) {
        printf("avi_player malloc fail");
        return NULL;
    }
    memset(avi, 0, sizeof(struct avi_player));

    memcpy(&avi->info, info, sizeof(struct avi_info));
    memcpy(&avi->frame_queue, frame_queue, sizeof(struct avi_frame_queue));

    avi->player_state = AVI_PLAYER_STATE_PLAYING;
    avi->event_callback = event_callback;
    avi->event_priv = event_priv;

    if (avi->info.has_video) {
        if (avi_video_init(avi) != 0) {
            free(avi);
            return NULL;
        }
    }

    if (avi->info.has_audio) {
        if (avi_audio_init(avi) != 0) {
            avi_video_exit(avi);
            free(avi);
            return NULL;
        }
    }

    return avi;
}

int avi_player_exit(struct avi_player *avi)
{
    if (!avi) {
        return -1;
    }

    if (avi->info.has_audio) {
        avi_audio_exit(avi);
    }

    if (avi->info.has_video) {
        avi_video_exit(avi);
    }

    free(avi);
    return 0;
}

int avi_player_control(struct avi_player *avi, int cmd, int arg)
{
    if (!avi) {
        printf("avi_player_control avi is NULL\n");
        return -1;
    }
    switch (cmd) {
    case AVI_PLAYER_CMD_PLAY:
        if (avi->player_state != AVI_PLAYER_STATE_PLAYING) {
            avi->player_state = AVI_PLAYER_STATE_PLAYING;
            if (avi->info.has_audio) {
                os_sem_post(&avi->audio_pause_sem);
            }
            if (avi->info.has_video) {
                os_sem_post(&avi->video_pause_sem);
            }
        }
        break;
    case AVI_PLAYER_CMD_PAUSE:
        if (avi->player_state != AVI_PLAYER_STATE_PAUSED) {
            avi->player_state = AVI_PLAYER_STATE_PAUSED;
            if (avi->info.has_audio) {
                os_sem_set(&avi->audio_pause_sem, 0);
            }
            if (avi->info.has_video) {
                os_sem_set(&avi->video_pause_sem, 0);
            }
        }
        break;
    case AVI_PLAYER_CMD_SEEK:
        avi->video_pts = arg;
        avi->audio_pts = arg;
        avi->current_offset = 0;
        if (avi->current_audio_node) {
            lbuf_free(avi->current_audio_node);
            avi->current_audio_node = NULL;
        }
        break;
    default:
        printf("avi_player_control unknown cmd %d\n", cmd);
        return -1;
    }
    return 0;
}

static int avi_audio_init(struct avi_player *avi)
{
    os_sem_create(&avi->audio_pause_sem, 0);
    //音频初始化
    avi->audio_exit = 0;
    avi->audio_player = vir_source_player_open(avi, &virtual_dev_ops);
    if (!avi->audio_player) {
        os_sem_del(&avi->audio_pause_sem, OS_DEL_ALWAYS);
        printf("avi audio player init fail");
        return -1;
    }
    vir_source_player_start(avi->audio_player);

    return 0;
}

static void avi_audio_exit(struct avi_player *avi)
{
    if (avi->audio_player) {
        avi->audio_exit = 1;

        if (avi->player_state != AVI_PLAYER_STATE_PLAYING) {
            os_sem_post(&avi->audio_pause_sem);
            os_sem_del(&avi->audio_pause_sem, OS_DEL_ALWAYS);
        }

        vir_source_player_close(avi->audio_player);
        avi->audio_player = NULL;

        if (avi->current_audio_node) {
            lbuf_free(avi->current_audio_node);
            avi->current_audio_node = NULL;
        }

    }
}

static int avi_video_init(struct avi_player *avi)
{
    //视频初始化
    struct video_format f = {0};
    struct video_window window = {0};
    window.left = 0;
    window.top = 0;
    window.width = LCD_W;
    window.height = LCD_H;
    window.combine = 1;

    int src_width = avi->info.width;
    int src_height = avi->info.height;

    os_sem_create(&avi->video_pause_sem, 0);

    pipeline_jpeg_dec_format_init(&f, &window, src_width, src_height, NULL);
    pipeline_jpeg_dec_init(&avi->video_player, &f);
    if (!avi->video_player) {
        os_sem_del(&avi->video_pause_sem, OS_DEL_ALWAYS);
        printf("avi video player init fail");
        return -1;
    }

    //视频播放线程
    avi->video_task_exit = 0;
    if (thread_fork("avi_video_play", 15, 2048, 2048,
                    &avi->video_task_pid,
                    avi_video_play_task, avi) != 0) {
        printf("avi video play thread fork fail");
        pipeline_jpeg_dec_exit(&avi->video_player);
        os_sem_del(&avi->video_pause_sem, OS_DEL_ALWAYS);
        return -1;
    }
    return 0;
}

static void avi_video_exit(struct avi_player *avi)
{
    //停止视频播放线程
    if (avi->video_task_pid) {
        avi->video_task_exit = 1;

        if (avi->player_state != AVI_PLAYER_STATE_PLAYING) {
            os_sem_post(&avi->video_pause_sem);
        }

        thread_kill(&avi->video_task_pid, KILL_WAIT);
        avi->video_task_exit = 0;
    }

    os_sem_del(&avi->video_pause_sem, OS_DEL_ALWAYS);

    //释放视频解码资源
    if (avi->video_player) {
        pipeline_jpeg_dec_exit(&avi->video_player);
        avi->video_player = NULL;
    }
}

static void avi_video_play_task(void *priv)
{
    struct avi_player *avi = (struct avi_player *)priv;
    struct lbuf_head *video_lbuf = avi->frame_queue.video_lbuf_handle;
    float duration_per_frame = 1000.0 / avi->info.fps;

    int threshold = duration_per_frame / 2;
    int sec = 0;
    while (!avi->video_task_exit) {


        if (avi->event_callback) {
            int seconds = avi->video_pts / 1000;
            if (seconds != sec) {
                sec = seconds;
                avi->event_callback(AVI_PLAYER_EVENT_CURRENT_TIME_MS, avi->video_pts, avi->event_priv);
            }
            if (avi->video_pts >= avi->info.total_time_ms && !avi->play_end) {
                avi->play_end = 1;
                avi->event_callback(AVI_PLAYER_EVENT_END, 0, avi->event_priv);
            }
        }

        if (avi->player_state != AVI_PLAYER_STATE_PLAYING) {
            //暂停状态，等待
            os_sem_pend(&avi->video_pause_sem, 0);
            continue;
        }

        if (avi->info.has_audio) {
            if (avi->video_pts + threshold < avi->audio_pts) {
                //视频落后音频较多，跳过当前帧
                struct avi_frame_lbuf_node *video_node = lbuf_pop(video_lbuf, BIT(0));
                if (video_node) {
                    printf("avi video frame skip pts=%.2f ms, audio_pts=%d ms\n", avi->video_pts, avi->audio_pts);
                    lbuf_free(video_node);
                } else {
                    //无视频帧可跳过，等待
                    os_time_dly(2);
                }
                avi->video_pts += duration_per_frame;
                continue;
            } else if (avi->video_pts > avi->audio_pts + threshold) {
                //视频超前音频较多，等待
                os_time_dly(2);
                continue;
            } else {
                struct avi_frame_lbuf_node *video_node = lbuf_pop(video_lbuf, BIT(0));
                if (video_node) {
                    //printf("avi video play pts=%.2f ms", avi->video_pts);
                    //解码视频帧
                    if (pipeline_jpeg_dec_one_frame(avi->video_player, video_node->data, video_node->len) < 0) {
                        printf("avi video decode one frame fail\n");
                    }
                    avi->video_pts += duration_per_frame;
                    lbuf_free(video_node);
                    continue;
                } else {
                    //无视频帧可解码，等待
                    os_time_dly(2);
                    continue;
                }
            }
        } else {
            struct avi_frame_lbuf_node *video_node = lbuf_pop(video_lbuf, BIT(0));
            if (video_node) {
                //printf("avi video play pts=%.2f ms", avi->video_pts);
                //解码视频帧
                if (pipeline_jpeg_dec_one_frame(avi->video_player, video_node->data, video_node->len) < 0) {
                    printf("avi video decode one frame fail\n");
                }
                avi->video_pts += duration_per_frame;
                lbuf_free(video_node);
                continue;
            }

            int tick = duration_per_frame / 10;
            os_time_dly(tick);
        }
    }
    printf("avi video play task exited\n");
}

static int virtual_dev_read(void *file, u8 *buf, int len)
{
    struct avi_player *avi = (struct avi_player *)file;

    struct lbuf_head *audio_lbuf = avi->frame_queue.audio_lbuf_handle;
    struct avi_frame_lbuf_node *node = NULL;
    int rlen = 0;

    if (avi->player_state != AVI_PLAYER_STATE_PLAYING && !avi->audio_exit) {
        //暂停状态，等待
        os_sem_pend(&avi->audio_pause_sem, 0);
    }

    if (avi->audio_exit) {
        return 0;
    }

    //控制最大读取长度，防止音频数据过多导致延时过大
    int max_audio_interval = 40; //ms
    int max_len = (avi->info.audio_sample_rate * avi->info.audio_channels * 2 * max_audio_interval) / 1000; //16位采样
    if (len > max_len) {
        len = max_len;
    }

    while ((rlen < len) && !avi->audio_exit) {
        if (!avi->current_audio_node) {
            node = lbuf_pop(audio_lbuf, BIT(0));
            if (!node) {
                //音频数据不足，等待
                os_time_dly(2);
                continue;
            }
            avi->current_audio_node = node;
        }
        int copy_len = len - rlen;
        int lbuf_remain = avi->current_audio_node->len - avi->current_offset;
        if (copy_len > lbuf_remain) {
            copy_len = lbuf_remain;
        }
        memcpy(buf + rlen, avi->current_audio_node->data + avi->current_offset, copy_len);
        rlen += copy_len;
        avi->current_offset += copy_len;

        //当前音频节点数据读完，释放节点
        if (avi->current_offset >= avi->current_audio_node->len) {
            lbuf_free(avi->current_audio_node);
            avi->current_offset = 0;
            avi->current_audio_node = NULL;
        }
    }

    //计算PTS
    avi->audio_pts += (rlen * 1000) / (avi->info.audio_sample_rate * avi->info.audio_channels * 2); //16位采样
    //printf("audio_pts=%d ms\n", avi->audio_pts);

    //一秒一次
    static int sec = 0;
    if (!avi->info.has_video) {
        if (avi->event_callback) {
            int seconds = avi->audio_pts / 1000;
            if (seconds != sec) {
                sec = seconds;
                avi->event_callback(AVI_PLAYER_EVENT_CURRENT_TIME_MS, avi->audio_pts, avi->event_priv);
            }

            if (avi->audio_pts >= avi->info.total_time_ms && !avi->play_end) {
                avi->play_end = 1;
                avi->event_callback(AVI_PLAYER_EVENT_END, 0, avi->event_priv);
            }
        }
    }

    return rlen;
}

static int virtual_dev_get_fmt(void *file, struct stream_fmt *fmt)
{
    struct avi_player *avi = (struct avi_player *)file;
    fmt->coding_type = avi->info.audio_coding_type;

    if (fmt->coding_type == AUDIO_CODING_PCM) {
        fmt->sample_rate   = avi->info.audio_sample_rate;
        fmt->channel_mode  = AUDIO_CH_L;
    }

    return 0;
}

static int virtual_dev_seek(void *file, int offset, int fromwhere)
{
    return 0;
}

static int virtual_dev_close(void *file)
{
    return 0;
}


