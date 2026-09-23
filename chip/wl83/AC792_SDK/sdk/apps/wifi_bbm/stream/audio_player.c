#include "jlstream.h"
#include "audio_def.h"
#include "audio_player.h"
#include "vir_dev_player.h"
#include "file_player.h"
#include "app_config.h"

#define LOG_TAG_CONST       AUDIO_PLAYER
#define LOG_TAG             "[AUDIO_PLAYER]"
#define LOG_ERROR_ENABLE
#define LOG_INFO_ENABLE
#define LOG_DUMP_ENABLE
#include "debug.h"

#if BBM_AUDIO_OPUS_ENABLE
#define AUDIO_PLAY_CBUF_SIZE           8 * 1024   //解码音频缓存
#else
#define AUDIO_PLAY_CBUF_SIZE           64 * 1024   //解码音频缓存
#endif

static u8 *audio_play_buf;
static cbuffer_t audio_play_cbuf;
static int ref = 0;
static struct vir_player *player;
static OS_SEM data_sem;
static u8 play_exit;


static int virtual_audio_player_decode_event_callback(void *priv, int parm, enum stream_event event)
{
    switch (event) {
    case STREAM_EVENT_START:
        log_info("STREAM_EVENT_START");
        break;
    case STREAM_EVENT_STOP:
        log_info("STREAM_EVENT_STOP");
        virtual_dev_player_stop(player);
        player = NULL;
        break;
    case STREAM_EVENT_END:
        log_info("STREAM_EVENT_END");
        break;
    default:
        break;
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

static int virtual_dev_read(void *file, u8 *buf, int len)
{
    int rlen;
    while ((rlen = cbuf_get_data_size(&audio_play_cbuf)) == 0) {
        os_sem_pend(&data_sem, 100);
        if (play_exit) {
            return 0;
        }
    }

    if (rlen > len) {
#if BBM_AUDIO_OPUS_ENABLE
        rlen = 0;
#else
        rlen = len;
#endif
    }

    return cbuf_read(&audio_play_cbuf, buf, rlen);
}

static int virtual_dev_get_fmt(void *file, struct stream_fmt *fmt)
{
    fmt->sample_rate = 16000;
    fmt->channel_mode = AUDIO_CH_L;
    fmt->coding_type = AUDIO_CODING_PCM;

#if BBM_AUDIO_OPUS_ENABLE
    fmt->coding_type = AUDIO_CODING_OPUS;
#endif

    if (fmt->coding_type == AUDIO_CODING_OPUS) {
        fmt->quality = AUDIO_ATTR_OPUS_CBR_PKTLEN_TYPE;//CONFIG_OPUS_DEC_FILE_TYPE;
        if (fmt->quality == AUDIO_ATTR_OPUS_CBR_PKTLEN_TYPE) {
            fmt->opus_pkt_len = 80;//CONFIG_OPUS_DEC_PACKET_LEN;
        }
        return -EINVAL;
    }

    if (fmt->coding_type == AUDIO_CODING_PCM) {
        fmt->pcm_file_mode = 1;
        return 0;
    }

    return 0;
}

static const struct stream_file_ops virtual_dev_ops = {
    .read       = virtual_dev_read,
    .seek       = virtual_dev_seek,
    .close      = virtual_dev_close,
    .get_fmt    = virtual_dev_get_fmt,
};


int audio_player_one_frame(u8 *buf, u32 size)
{
    u32 cur_size;
    cur_size =  cbuf_get_data_size(&audio_play_cbuf);

    if (cur_size + size >= AUDIO_PLAY_CBUF_SIZE) {
        log_info("auido player cbuf full  clean  ! \n");
        cbuf_clear(&audio_play_cbuf);
    }

    cbuf_write(&audio_play_cbuf, buf, size);

    os_sem_post(&data_sem);

    if (!player) {
        //需要有数据才初始化
        u32 coding_type = AUDIO_CODING_PCM;

#if BBM_AUDIO_OPUS_ENABLE
        coding_type = AUDIO_CODING_OPUS;
#endif
        player = virtual_dev_play_callback(&audio_play_cbuf, &virtual_dev_ops, NULL, virtual_audio_player_decode_event_callback, NULL, coding_type);
        /* void app_audio_set_volume(u8 state, s16 volume, u8 fade); */
        /* app_audio_set_volume(app_audio_get_state(), 70, 0); */
    }

    return 0;
}

int audio_player_init(void)
{
    int err;
    ref++;

    if (ref > 1) {
        log_debug("audio player init ref:%d \n", ref);
        return 0;
    }

    audio_play_buf = (u8 *)malloc(AUDIO_PLAY_CBUF_SIZE);
    if (audio_play_buf == NULL) {
        log_error("audio_play_buf malloc fail");
        goto __err;

    }
    cbuf_init(&audio_play_cbuf, audio_play_buf, AUDIO_PLAY_CBUF_SIZE);

    os_sem_create(&data_sem, 0);

    //先初始化buf,等有音频数据进来 才继续初始化音频解码器

    play_exit = 0;

    return 0;

__err:
    if (audio_play_buf) {
        free(audio_play_buf);
        audio_play_buf = NULL;
    }
    ref = 0;
    return -1;
}

int audio_player_exit(void)
{
    ref--;

    if (ref > 0) {
        log_debug("audio_player_exit ref:%d \n", ref);
        return 0;
    }

    play_exit = 1;
    os_sem_post(&data_sem);

    if (player) {
        virtual_dev_player_stop(player);
    }

    os_sem_del(&data_sem, OS_DEL_ALWAYS);

    if (audio_play_buf) {
        free(audio_play_buf);
        audio_play_buf = NULL;
    }

    return 0;
}



