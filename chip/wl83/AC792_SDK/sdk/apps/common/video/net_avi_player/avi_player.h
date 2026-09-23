#ifndef AVI_PLAYER_H
#define AVI_PLAYER_H

#include "system/includes.h"

enum {
    AVI_PLAYER_STATE_PAUSED = 0,
    AVI_PLAYER_STATE_PLAYING,
};

enum {
    AVI_PLAYER_CMD_SET_VOLUME = 1,
    AVI_PLAYER_CMD_GET_VOLUME,
    AVI_PLAYER_CMD_PLAY,
    AVI_PLAYER_CMD_PAUSE,
    AVI_PLAYER_CMD_SEEK,
};

enum {
    AVI_PLAYER_EVENT_END = 10,
    AVI_PLAYER_EVENT_CURRENT_TIME_MS,
};

typedef void (*avi_player_event_callback_t)(int event, int arg, void *priv);

struct avi_info {
    int width;
    int height;
    int fps;
    int video_coding_type;
    int audio_coding_type;
    int audio_channels;
    int audio_sample_rate;
    int has_video;
    int has_audio;
    int total_time_ms;
};

struct avi_frame_lbuf_node {
    int len;
    u8 data[0];
};

struct avi_frame_queue {
    void *video_buf_ptr;
    void *audio_buf_ptr;
    int video_buf_size;
    int audio_buf_size;

    struct lbuf_head *video_lbuf_handle;
    struct lbuf_head *audio_lbuf_handle;
};

struct avi_player *avi_player_init(struct avi_info *info, struct avi_frame_queue *frame_queue,
                                   avi_player_event_callback_t event_callback,
                                   void *event_priv);
int avi_player_exit(struct avi_player *avi);
int avi_player_control(struct avi_player *avi, int cmd, int arg);

#endif /* AVI_PLAYER_H */

