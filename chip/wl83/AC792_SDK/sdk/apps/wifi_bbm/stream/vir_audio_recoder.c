#ifdef MEDIA_SUPPORT_MS_EXTENSIONS
#pragma bss_seg(".vir_audio_recoder.data.bss")
#pragma data_seg(".vir_audio_recoder.data")
#pragma const_seg(".vir_audio_recoder.text.const")
#pragma code_seg(".vir_audio_recoder.text")
#endif
#include "jlstream.h"
#include "encoder_fmt.h"
#include "vad_node.h"
#include "vir_audio_recoder.h"

#define LOG_TAG_CONST       VIR_AUDIO_RECODER
#define LOG_TAG             "[VIR_AUDIO_RECODER]"
#define LOG_ERROR_ENABLE
#define LOG_INFO_ENABLE
#define LOG_DUMP_ENABLE
#include "debug.h"

struct vir_audio_recoder {
    struct jlstream *stream;
    void *priv;
    void (* cb)(void *, u8 *, u32);
};

static void vir_audio_recoder_callback(void *private_data, int event)
{
    struct jlstream *stream = (struct jlstream *)private_data;

    switch (event) {
    case STREAM_EVENT_START:
        break;
    }
}

static int recorder_data_output(void *priv, u8 *buf, int len)
{
    struct vir_audio_recoder *recorder = (struct vir_audio_recoder *)priv;
    if (recorder->cb) {
        recorder->cb(recorder->priv, buf, len);
    }
    return len;
}

static const struct stream_file_ops vir_audio_tx_ops = {
    .write = recorder_data_output,
};

void *vir_audio_recoder_open(u16 sample_rate, u32 code_type, void *priv, void (*cb)(void *, u8 *, u32))
{
    int err;
    struct stream_fmt fmt = {0};
    struct encoder_fmt enc_fmt = {0};

    u16 uuid = jlstream_event_notify(STREAM_EVENT_GET_PIPELINE_UUID, (int)"vir_voice");
    if (uuid == 0) {
        log_error("get vir voice uuid err \n");
        return NULL;
    }
    struct vir_audio_recoder *recorder = zalloc(sizeof(*recorder));
    if (!recorder) {
        log_error("vir audio recorder alloc err \n");
        return NULL;
    }

    recorder->cb   = cb;
    recorder->priv = priv;


    recorder->stream = jlstream_pipeline_parse(uuid, NODE_UUID_ADC);
    if (!recorder->stream) {
        log_error("vir audio recorder pipeline parse err \n");
        goto __exit0;
    }

    fmt.sample_rate = sample_rate;

    if (!code_type || code_type == AUDIO_CODING_PCM) {
        log_info("vir audio recorder use PCM encoder \n");
        fmt.coding_type = AUDIO_CODING_PCM;

        enc_fmt.quality = 0;
        enc_fmt.sample_rate = sample_rate;
        enc_fmt.frame_dms = 1024;
    } else if (code_type == AUDIO_CODING_OPUS) {
        log_info("vir audio recorder use OPUS encoder \n");
        fmt.coding_type = AUDIO_CODING_OPUS;

        enc_fmt.complexity = 3;
        enc_fmt.format = 0;
        enc_fmt.frame_dms = 20 * 10;
    }

    if (code_type == AUDIO_CODING_OPUS) {
        err = jlstream_node_ioctl(recorder->stream, NODE_UUID_ENCODER, NODE_IOC_SET_PRIV_FMT, (int)(&enc_fmt));
        if (err) {
            log_error("vir audio recorder set encoder fmt err \n");
            goto __exit1;
        }
    } else if (code_type == AUDIO_CODING_PCM) {
        err = jlstream_node_ioctl(recorder->stream, NODE_UUID_ENCODER, NODE_IOC_SET_FMT, (int)(&enc_fmt));
        if (err) {
            goto __exit1;
        }
        err = jlstream_node_ioctl(recorder->stream, NODE_UUID_VIR_DATA_TX, NODE_IOC_SET_FMT, (int)(&fmt));
        if (err) {
            goto __exit1;
        }
    }

    err = jlstream_node_ioctl(recorder->stream, NODE_UUID_SOURCE, NODE_IOC_SET_PRIV_FMT, 256);
    if (err) {
        log_error("vir audio recorder set vad fmt err \n");
        goto __exit1;
    }

    struct stream_file_info info = {
        .file = (void *)recorder,
        .ops = &vir_audio_tx_ops
    };
    err = stream_node_ioctl((struct stream_node *)recorder->stream->snode, NODE_UUID_VIR_DATA_TX, NODE_IOC_SET_FILE, (int)&info);
    if (err) {
        log_error("vir audio recorder set file ops err \n");
        goto __exit1;
    }

    jlstream_set_callback(recorder->stream, recorder->stream, vir_audio_recoder_callback);
    jlstream_set_scene(recorder->stream, STREAM_SCENE_VIR_DATA_TX);

    err = jlstream_start(recorder->stream);
    if (err) {
        log_error("vir audio recorder start err \n");
        goto __exit1;
    }
    return recorder;

__exit1:
    jlstream_release(recorder->stream);
__exit0:
    free(recorder);
    return NULL;

}

int vir_audio_recoder_close(void *priv)
{
    struct vir_audio_recoder *recorder = (struct vir_audio_recoder *)priv;

    if (!recorder) {
        log_error("vir audio recorder hdl null \n");
        return 0;
    }

    jlstream_stop(recorder->stream, 0);
    jlstream_release(recorder->stream);

    free(recorder);

    jlstream_event_notify(STREAM_EVENT_CLOSE_RECORDER, (int)"vir_voice");

    return 0;
}

