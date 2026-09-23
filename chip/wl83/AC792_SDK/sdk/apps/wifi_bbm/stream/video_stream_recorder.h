#ifndef VIDEO_STREAM_RECORDER_H
#define VIDEO_STREAM_RECORDER_H
#include "system/includes.h"

enum {
    VIDEO_REC_OK = 0,
    VIDEO_REC_ERR_OPEN_FILE = -1,
    VIDEO_REC_ERR_NO_MEM = -2,
    VIDEO_REC_ERR_ALREADY_REC = -3,
    VIDEO_REC_ERR_NOT_RECORDING = -4,
};

/**
 * video_stream_recorder 模块: 将 video_stream_recv 收到的音视频帧通过 avilib
 * 封装为 AVI 文件。在接收线程上下文中直接写入，不创建额外线程。
 */

/**
 * 录像上下文（per-device），挂在 stream_dev 中
 */
struct video_rec_ctx {
    void *avi;                      // avi_t * 句柄
    u8 is_recording;                // 是否正在录像
    u8 rec_writing;                 // 是否正在写入（用于 stop 同步）
    int video_width;                // 视频宽度
    int video_height;               // 视频高度
    double video_fps;               // 视频帧率
    int audio_sample_rate;          // 音频采样率
    int audio_channels;             // 音频通道数
    int audio_bits;                 // 音频位深
    char file_path[128];            // AVI 文件完整路径
};

/* 初始化录像上下文 */
void video_rec_ctx_init(struct video_rec_ctx *ctx);

/* 开始录像 */
int video_stream_rec_start(struct video_rec_ctx *ctx, const char *file_path);

/* 停止录像 */
int video_stream_rec_stop(struct video_rec_ctx *ctx);

/* 写入一帧（在接收线程中调用） */
void video_stream_recorder_write_frame(struct video_rec_ctx *ctx,
                                       const u8 *data, int len, int frame_type);

#endif // VIDEO_STREAM_RECORDER_H
