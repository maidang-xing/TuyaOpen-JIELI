#include "video_stream_recorder.h"
#include "video_stream_recv.h"
#include "system/includes.h"

#define LOG_TAG_CONST       VIDEO_STREAM_RECV
#define LOG_TAG             "[VIDEO_STREAM_REC]"
#define LOG_ERROR_ENABLE
#define LOG_INFO_ENABLE
#include "debug.h"

/* avilib 头文件在 apps/wifi_bbm/avilib/ 目录下 */
#include "avilib.h"

void video_rec_ctx_init(struct video_rec_ctx *ctx)
{
    if (!ctx) {
        return;
    }
    memset(ctx, 0, sizeof(struct video_rec_ctx));
}

int video_stream_rec_start(struct video_rec_ctx *ctx, const char *file_path)
{
    if (!ctx || !file_path) {
        log_error("rec_start: invalid params\n");
        return VIDEO_REC_ERR_OPEN_FILE;
    }

    if (ctx->is_recording) {
        log_error("rec_start: already recording\n");
        return VIDEO_REC_ERR_ALREADY_REC;
    }

    /* 打开 AVI 输出文件 */
    ctx->avi = AVI_open_output_file(file_path);
    if (!ctx->avi) {
        log_error("rec_start: AVI_open_output_file failed, path:%s\n", file_path);
        return VIDEO_REC_ERR_OPEN_FILE;
    }

    /* 设置视频参数: MJPG (Motion JPEG) */
    AVI_set_video(ctx->avi, ctx->video_width, ctx->video_height,
                  ctx->video_fps, "MJPG");

    /* 设置音频参数: PCM */
    if (ctx->audio_sample_rate > 0) {
        AVI_set_audio(ctx->avi, ctx->audio_channels, ctx->audio_sample_rate,
                      ctx->audio_bits, WAVE_FORMAT_PCM, 0);
    }

    strncpy(ctx->file_path, file_path, sizeof(ctx->file_path) - 1);
    ctx->file_path[sizeof(ctx->file_path) - 1] = '\0';
    ctx->is_recording = 1;
    ctx->rec_writing = 0;

    log_info("rec_start: recording started, file:%s, video:%dx%d@%.0ffps MJPG, audio:%dHz/%dch/%dbits PCM\n",
             file_path, ctx->video_width, ctx->video_height, ctx->video_fps,
             ctx->audio_sample_rate, ctx->audio_channels, ctx->audio_bits);

    return VIDEO_REC_OK;
}

int video_stream_rec_stop(struct video_rec_ctx *ctx)
{
    int ret;
    if (!ctx) {
        return VIDEO_REC_ERR_NOT_RECORDING;
    }

    if (!ctx->is_recording) {
        log_error("rec_stop: not recording\n");
        return VIDEO_REC_ERR_NOT_RECORDING;
    }

    /* 先关开关，阻止新帧写入 */
    ctx->is_recording = 0;

    /* 等待正在写入的帧完成 */
    while (ctx->rec_writing) {
        os_time_dly(1);
    }

    /* 关闭 AVI 文件（写入头部和索引） */
    ret = AVI_close(ctx->avi);
    if (ret != 0) {
        log_error("rec_stop: AVI_close failed, ret:%d\n", ret);
    }

    ctx->avi = NULL;
    log_info("rec_stop: recording stopped, file:%s\n", ctx->file_path);

    (void)ret;
    return VIDEO_REC_OK;
}

void video_stream_recorder_write_frame(struct video_rec_ctx *ctx,
                                       const u8 *data, int len, int frame_type)
{
    if (!ctx || !data || len <= 0) {
        return;
    }

    if (!ctx->is_recording) {
        return;
    }

    ctx->rec_writing = 1;

    if (frame_type == VIDEO_FRAME) {
        /* JPEG 每一帧都是关键帧 */
        int ret = AVI_write_frame(ctx->avi, (const char *)data, len, 1);
        if (ret != 0) {
            log_error("AVI_write_frame failed, len:%d, ret:%d\n", len, ret);
        }
    } else if (frame_type == AUDIO_FRAME) {
        int ret = AVI_write_audio(ctx->avi, (const char *)data, len);
        if (ret != 0) {
            log_error("AVI_write_audio failed, len:%d, ret:%d\n", len, ret);
        }
    } else {
        log_error("unknown frame_type:%d\n", frame_type);
    }

    ctx->rec_writing = 0;
}
