#include "app_config.h"

#if TCFG_PJSIP_ENABLE

#define LOG_TAG             "[SIP]"
#define LOG_ERROR_ENABLE
#define LOG_INFO_ENABLE
#define LOG_DEBUG_ENABLE
#include "debug.h"

#include "pjsip_internal.h"
#include "jlstream.h"
#include "encoder_fmt.h"
#include "audio_base.h"
#include "audio_config_def.h"

#define PJSIP_AUDIO_MIC_ACTIVE_PEAK_THR     128
#define PJSIP_AUDIO_MIC_LOG_INTERVAL_FRAMES 50
#define PJSIP_AUDIO_MIC_SILENT_WARN_FRAMES  100

struct pjsip_audio_capture {
    struct jlstream *stream;
    struct pjsip_audio_capture_param param;
    unsigned frame_cnt;
    unsigned total_bytes;
    unsigned active_frame_cnt;
    unsigned silent_frame_streak;
    unsigned empty_frame_cnt;
};

static void pjsip_audio_capture_callback(void *private_data, int event)
{
    PJ_UNUSED_ARG(private_data);

    switch (event) {
    case STREAM_EVENT_START:
        break;
    }
}

static unsigned pjsip_audio_pcm_peak_abs(const s16 *pcm,
        unsigned samples,
        unsigned *non_zero_samples)
{
    unsigned i;
    unsigned peak = 0;
    unsigned nz = 0;

    for (i = 0; i < samples; ++i) {
        int sample = pcm[i];
        unsigned abs_val =
            (sample < 0) ? (unsigned)(-sample) : (unsigned)sample;

        if (abs_val != 0) {
            ++nz;
        }
        if (abs_val > peak) {
            peak = abs_val;
        }
    }

    if (non_zero_samples) {
        *non_zero_samples = nz;
    }
    return peak;
}

static int pjsip_audio_capture_data_output(void *priv, u8 *buf, int len)
{
    //printf("%s, %d, len: %d-----\n", __FUNCTION__, __LINE__, len);
    struct pjsip_audio_capture *capture = (struct pjsip_audio_capture *)priv;
    unsigned peak = 0;
    unsigned non_zero_samples = 0;
    unsigned samples;
    const char *state = "data";

    if (!buf || len <= 0) {
        ++capture->empty_frame_cnt;
        if (capture->empty_frame_cnt <= 3 ||
            (capture->empty_frame_cnt % PJSIP_AUDIO_MIC_LOG_INTERVAL_FRAMES) == 0) {
            log_info("[WARN] pjsip_audio: mic empty callback cnt=%u len=%d",
                     capture->empty_frame_cnt,
                     len);
        }
        return len;
    }

    ++capture->frame_cnt;
    capture->total_bytes += len;

    if (capture->param.coding_type == AUDIO_CODING_PCM &&
        capture->param.bit_wide == 16) {
        samples = (unsigned)len / 2;
        peak = pjsip_audio_pcm_peak_abs((const s16 *)buf,
                                        samples,
                                        &non_zero_samples);
        if (peak >= PJSIP_AUDIO_MIC_ACTIVE_PEAK_THR) {
            ++capture->active_frame_cnt;
            capture->silent_frame_streak = 0;
            state = "active";
        } else {
            ++capture->silent_frame_streak;
            state = (peak == 0) ? "zero" : "quiet";
        }

        if (capture->frame_cnt <= 3 ||
            (capture->frame_cnt % PJSIP_AUDIO_MIC_LOG_INTERVAL_FRAMES) == 0) {
            log_info("pjsip_audio: mic frame=%u len=%d peak=%u nz=%u state=%s",
                     capture->frame_cnt,
                     len,
                     peak,
                     non_zero_samples,
                     state);
        } else if (capture->silent_frame_streak == PJSIP_AUDIO_MIC_SILENT_WARN_FRAMES) {
            log_info("[WARN] pjsip_audio: mic stayed quiet for %u frames len=%d peak=%u",
                     capture->silent_frame_streak,
                     len,
                     peak);
        }
    } else if (capture->frame_cnt <= 3 ||
               (capture->frame_cnt % PJSIP_AUDIO_MIC_LOG_INTERVAL_FRAMES) == 0) {
        log_info("pjsip_audio: mic frame=%u len=%d coding=0x%x",
                 capture->frame_cnt,
                 len,
                 capture->param.coding_type);
    }

    if (capture->param.output) {
        capture->param.output(capture->param.priv, buf, len);
    }

    return len;
}

static const struct stream_file_ops pjsip_audio_tx_ops = {
    .write = pjsip_audio_capture_data_output,
};

void pjsip_audio_capture_init_param(struct pjsip_audio_capture_param *param)
{
    if (!param) {
        return;
    }

    memset(param, 0, sizeof(*param));
    param->sample_rate = LIVE_SIP_AUDIO_CAPTURE_RATE;//LIVE_SIP_AUDIO_SAMPLE_RATE;
    param->coding_type = AUDIO_CODING_PCM;
    param->channel_mode = AUDIO_CH_L;
    param->bit_wide = 16;
    param->source_irq_points = AUDIO_ADC_IRQ_POINTS_MUSIC_MODE;
    param->encoder_frame_dms = 1024;
}

void *pjsip_audio_capture_open(const struct pjsip_audio_capture_param *param)
{
    struct pjsip_audio_capture *capture;
    struct stream_fmt fmt = {0};
    struct encoder_fmt enc_fmt = {0};
    struct stream_file_info info;
    u16 uuid;
    int err;

    if (!param || !param->output || param->sample_rate == 0) {
        return NULL;
    }

    uuid = jlstream_event_notify(STREAM_EVENT_GET_PIPELINE_UUID,
                                 (int)"vir_voice");
    if (uuid == 0) {
        log_error("pjsip_audio: pipeline uuid not found");
        return NULL;
    }

    capture = zalloc(sizeof(*capture));
    if (!capture) {
        return NULL;
    }

    memcpy(&capture->param, param, sizeof(*param));

    capture->stream = jlstream_pipeline_parse(uuid, NODE_UUID_ADC);
    if (!capture->stream) {
        log_error("pjsip_audio: pipeline parse failed");
        goto __exit0;
    }

    enc_fmt.sample_rate = capture->param.sample_rate;
    enc_fmt.frame_dms = capture->param.encoder_frame_dms;

    fmt.sample_rate = capture->param.sample_rate;
    fmt.coding_type = capture->param.coding_type;
    fmt.channel_mode = capture->param.channel_mode;
    fmt.bit_wide = capture->param.bit_wide;
    fmt.frame_dms = LIVE_SIP_AUDIO_FRAME_MS * 10;

    printf("%s====%d, fmt.sample_rate: %d\n", __func__, __LINE__, fmt.sample_rate);
    err = jlstream_node_ioctl(capture->stream,
                              NODE_UUID_ENCODER,
                              NODE_IOC_SET_FMT,
                              (int)(&enc_fmt));

    if (err) {
        log_error("pjsip_audio: set encoder fmt err=%d", err);
        goto __exit1;
    }

    err = jlstream_node_ioctl(capture->stream,
                              NODE_UUID_VIR_DATA_TX,
                              NODE_IOC_SET_FMT,
                              (int)(&fmt));
    if (err) {
        log_error("pjsip_audio: set tx fmt err=%d", err);
        goto __exit1;
    }

    err = jlstream_node_ioctl(capture->stream,
                              NODE_UUID_SOURCE,
                              NODE_IOC_SET_PRIV_FMT,
                              capture->param.source_irq_points);
    if (err) {
        log_error("pjsip_audio: set source priv err=%d", err);
        goto __exit1;
    }

    info.file = (void *)capture;
    info.fname = NULL;
    info.ops = &pjsip_audio_tx_ops;
    info.dbp = NULL;
    info.scene = STREAM_SCENE_VIR_DATA_TX;
    info.coding_type = capture->param.coding_type;
    err = stream_node_ioctl((struct stream_node *)capture->stream->snode,
                            NODE_UUID_VIR_DATA_TX,
                            NODE_IOC_SET_FILE,
                            (int)&info);
    if (err) {
        log_error("pjsip_audio: set tx file err=%d", err);
        goto __exit1;
    }

    jlstream_set_callback(capture->stream, capture, pjsip_audio_capture_callback);
    jlstream_set_scene(capture->stream, STREAM_SCENE_VIR_DATA_TX);

    err = jlstream_start(capture->stream);
    if (err) {
        log_error("pjsip_audio: start err=%d", err);
        goto __exit1;
    }

    log_info("pjsip_audio: capture started sr=%u irq=%u",
             capture->param.sample_rate,
             capture->param.source_irq_points);
    return capture;

__exit1:
    jlstream_release(capture->stream);
__exit0:
    free(capture);
    return NULL;
}

int pjsip_audio_capture_close(void *priv)
{
    struct pjsip_audio_capture *capture = (struct pjsip_audio_capture *)priv;

    if (!capture) {
        return 0;
    }

    jlstream_stop(capture->stream, 0);
    jlstream_release(capture->stream);
    log_info("pjsip_audio: capture stopped frames=%u active=%u bytes=%u empty=%u",
             capture->frame_cnt,
             capture->active_frame_cnt,
             capture->total_bytes,
             capture->empty_frame_cnt);
    free(capture);

    jlstream_event_notify(STREAM_EVENT_CLOSE_RECORDER, (int)"pjsip_audio");
    return 0;
}

#endif

