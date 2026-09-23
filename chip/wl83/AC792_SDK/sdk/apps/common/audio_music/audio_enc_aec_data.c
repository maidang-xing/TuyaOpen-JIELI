#include "os/os_api.h"
#include "fs/fs.h"
#include "generic/circular_buf.h"
#include "app_config.h"

#if defined CONFIG_AUDIO_ENC_AEC_DATA_CHECK

#ifdef CONFIG_MEDIA_ENABLE
#include "jlstream_node_cfg.h"
#define READSIZE 256
#else
#define READSIZE 128
#endif

#if defined TCFG_AUDIO_CVP_DMS_ANS_MODE && (TCFG_AUDIO_CVP_DMS_ANS_MODE)
#define MIX_DATA_LEN (READSIZE*4*2)  //DMS AEC READSIZE = 128, 4:channel, 2:s16
#else
#define MIX_DATA_LEN (READSIZE*3*2)  //AEC READSIZE = 128, 3:channel, 2:s16
#endif
#define DAC_DATA_LEN (READSIZE*2*3)  //dac_sr/aec_sr*aec_points*channel  48000/16000 * 128 * 2

static struct {
    u8 stop_flag;
    FILE *fd;
    FILE *fd1;
    void *dac_orig_buf;
    void *cache_buf;
    OS_SEM w_sem;
    cbuffer_t save_cbuf;
    cbuffer_t dac_save_cbuf;
    s16 cache[READSIZE * 3];
    s16 dac_obuf[READSIZE * 3];
} audio_aec_to_sd;

#define __this (&audio_aec_to_sd)

static void check_aec_mix_data_to_sd(void *priv)
{
    u8 data[MIX_DATA_LEN];
    u8 dac_data[DAC_DATA_LEN];

    while (1) {
        os_sem_pend(&__this->w_sem, 0);
        if (__this->stop_flag == 1) {
            os_sem_del(&__this->w_sem, OS_DEL_ALWAYS);
            __this->stop_flag++;
            break;
        }
        if (MIX_DATA_LEN == cbuf_read(&__this->save_cbuf, data, MIX_DATA_LEN)) {
            fwrite(data, MIX_DATA_LEN, 1, __this->fd);
        }
        if (DAC_DATA_LEN == cbuf_read(&__this->dac_save_cbuf, dac_data, DAC_DATA_LEN)) {
            fwrite(dac_data, DAC_DATA_LEN, 1, __this->fd1);
        }
    }
}

void aec_mix_data_set_cb(s16 *data, int step)
{
    if (__this->fd) {
        if (step == 1) { // !ch_data_exchange
            for (u32 i = 0; i < READSIZE; ++i) {
                __this->cache[3 * i] = data[2 * i];
                __this->cache[3 * i + 1] = data[2 * i + 1];
            }
        } else if (step == 2) { //ch_data_exchange
            for (u32 i = 0; i < READSIZE; ++i) {
                __this->cache[3 * i] = data[2 * i + 1];
                __this->cache[3 * i + 1] = data[2 * i];
            }
        }


        if (step == 3) { //aec_data
            for (u32 i = 0; i < READSIZE; ++i) {
                __this->cache[3 * i + 2] = data[i];
            }

            if (0 == cbuf_write(&__this->save_cbuf, __this->cache, MIX_DATA_LEN)) {
                cbuf_clear(&__this->save_cbuf);
            }

            os_sem_set(&__this->w_sem, 0);
            os_sem_post(&__this->w_sem);

            memset(__this->cache, 0, sizeof(__this->cache));
        }
    }
}

void dms_aec_soft_mix_data_set_cb(s16 *data, int step)
{
    if (__this->fd) {
        // talk mic data
        if (step == 1) {
            for (u32 i = 0; i < READSIZE; ++i) {
                __this->cache[4 * i] = data[i];
            }
        }
        //ref mic data
        if (step == 2) {
            for (u32 i = 0; i < READSIZE; ++i) {
                __this->cache[4 * i + 1] = data[i];
            }
        }

        //dac data
        if (step == 3) {
            for (u32 i = 0; i < READSIZE; ++i) {
                __this->cache[4 * i + 2] = data[i];
            }
        }

        //aec_data
        if (step == 4) {
            for (u32 i = 0; i < READSIZE; ++i) {
                __this->cache[4 * i + 3] = data[i];
            }

            if (0 == cbuf_write(&__this->save_cbuf, __this->cache, MIX_DATA_LEN)) {
                printf("error jlkws aec_data cbuf write full!");
                cbuf_clear(&__this->save_cbuf);
            }

            os_sem_set(&__this->w_sem, 0);
            os_sem_post(&__this->w_sem);

            memset(__this->cache, 0, sizeof(__this->cache));
        }
    }

    if (__this->fd1) {
        if (step == 5) {
            for (u32 i = 0; i < DAC_DATA_LEN / 2; ++i) {
                __this->dac_obuf[i] = data[i];
            }

            if (0 == cbuf_write(&__this->dac_save_cbuf, __this->dac_obuf, DAC_DATA_LEN)) {
                printf("error jlkws dac_data cbuf write full!");
                cbuf_clear(&__this->dac_save_cbuf);
            }
        }
    }
}

void aec_soft_mix_data_set_cb(s16 *data, int step)
{
    if (__this->fd) {
        // mic data
        if (step == 1) {
            for (u32 i = 0; i < READSIZE; ++i) {
                __this->cache[3 * i] = data[i];
            }
        }

        //dac data
        if (step == 2) {
            for (u32 i = 0; i < READSIZE; ++i) {
                __this->cache[3 * i + 1] = data[i];
            }
        }

        //aec_data
        if (step == 3) {
            for (u32 i = 0; i < READSIZE; ++i) {
                __this->cache[3 * i + 2] = data[i];
            }

            if (0 == cbuf_write(&__this->save_cbuf, __this->cache, MIX_DATA_LEN)) {
                printf("error jlkws aec_data cbuf write full!");
                cbuf_clear(&__this->save_cbuf);
            }

            os_sem_set(&__this->w_sem, 0);
            os_sem_post(&__this->w_sem);

            memset(__this->cache, 0, sizeof(__this->cache));
        }
    }

    if (__this->fd1) {
        if (step == 4) {
            for (u32 i = 0; i < DAC_DATA_LEN / 2; ++i) {
                __this->dac_obuf[i] = data[i];
            }

            if (0 == cbuf_write(&__this->dac_save_cbuf, __this->dac_obuf, DAC_DATA_LEN)) {
                printf("error jlkws dac_data cbuf write full!");
                cbuf_clear(&__this->dac_save_cbuf);
            }
        }
    }
}

static void audio_aec_enc_data_to_sd(void *p)
{
    extern int storage_device_ready(void);
    while (!storage_device_ready()) {//等待sd文件系统挂载完成
        os_time_dly(1);
    }

    if (__this->cache_buf) {
        return;
    }

    __this->stop_flag = 0;
    os_sem_create(&__this->w_sem, 0);

    __this->fd = fopen("storage/sd0/C/aec.pcm", "w+");
    __this->fd1 = fopen("storage/sd0/C/dac.pcm", "w+");

    if (!__this->fd || !__this->fd1) {
        return;
    }

    __this->cache_buf = malloc(1024 * 128);
    if (__this->cache_buf == NULL) {
        printf("aec_data_to_sd_malloc_fail!");
        return;
    }
    __this->dac_orig_buf = malloc(1024 * 128);
    if (__this->dac_orig_buf == NULL) {
        printf("aec_data_to_sd_malloc_fail!");
        return;
    }

    cbuf_init(&__this->save_cbuf, __this->cache_buf, 1024 * 128);
    cbuf_init(&__this->dac_save_cbuf, __this->dac_orig_buf, 1024 * 128);

    thread_fork("check_aec_mix_data_to_sd", 4, 4 * 1024, 0, 0, check_aec_mix_data_to_sd, NULL);
}

void aec_data_to_sd_open(void)
{
    thread_fork("audio_aec_enc_data_to_sd", 4, 1024, 0, 0, audio_aec_enc_data_to_sd, NULL);
}

void aec_data_to_sd_close(void)
{
    if (__this->stop_flag == 2) {
        return;
    }

    __this->stop_flag = 1;
    os_sem_set(&__this->w_sem, 0);
    os_sem_post(&__this->w_sem);

    if (__this->fd) {
        fclose(__this->fd);
        __this->fd = NULL;
    }

    if (__this->fd1) {
        fclose(__this->fd1);
        __this->fd1 = NULL;
    }

    if (__this->cache_buf) {
        free(__this->cache_buf);
        __this->cache_buf = NULL;
    }

    if (__this->dac_orig_buf) {
        free(__this->dac_orig_buf);
        __this->dac_orig_buf = NULL;
    }
}

#else

void aec_data_to_sd_open(void)
{

}

void aec_data_to_sd_close(void)
{

}

#endif //CONFIG_AEC_ENC_ENABLE && CONFIG_AUDIO_ENC_AEC_DATA_CHECK
