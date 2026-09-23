#include "system/includes.h"
#include "app_config.h"
#include "app_tone.h"
#include "app_msg.h"
#include "dev_manager.h"
#include "file_recorder.h"
#include "event/key_event.h"
#include "event/device_event.h"


#if TCFG_APP_RECORD_EN

#define LOG_TAG             "[APP_RECORDER]"
#define LOG_ERROR_ENABLE
#define LOG_DEBUG_ENABLE
#define LOG_INFO_ENABLE
/* #define LOG_DUMP_ENABLE */
#define LOG_CLI_ENABLE
#include "debug.h"


#define PIPELINE_RECODER    0x49EC


typedef struct {
    void *recorder;
    const char *logo;
    int suspend_flag;
} recorder_t;

static recorder_t recorder_hdl;

#define __this 	(&recorder_hdl)

static int recorder_tone_play_end_callback(void *priv, enum stream_event event)
{
    return 0;
}

static void file_recorder_callback(void *priv, enum stream_event event)
{

}

static void recorder_start(void)
{
    int err;
    const char *suffix;

    void *recorder = file_recorder_open(PIPELINE_RECODER, NODE_UUID_ADC);
    //void *recorder = file_recorder_open(PIPELINE_RECODER, NODE_UUID_PDM_MIC);
    //void *recorder = file_recorder_open(PIPELINE_RECODER, NODE_UUID_IIS0_RX);
    //void *recorder = file_recorder_open(PIPELINE_RECODER, NODE_UUID_MULTI_CH_IIS0_RX);
    /* recorder = file_recorder_open(PIPELINE_RECODER, NODE_UUID_ZERO_ACTIVE); */
    if (!recorder) {
        log_error("file recorder open faild");
        return;
    }

    struct stream_enc_fmt fmt;
    err = file_recorder_get_fmt(recorder, &fmt);
    if (err) {
        file_recorder_close(recorder, 0);
        return;
    }

    log_info("recorder_fmt: ch %d, sample rate %d", fmt.channel, fmt.sample_rate);

    switch (fmt.coding_type) {
    case AUDIO_CODING_PCM:
    case AUDIO_CODING_WAV:
        suffix = "wav";
        break;
    case AUDIO_CODING_MP3:
        suffix = "mp3";
        break;
    default:
        suffix = "bin";
        break;
    }

    //普通设备录音，获取最后活动设备
    const char *logo = dev_manager_get_phy_logo(dev_manager_find_active(0));
    if (!logo || !strcmp(logo, "sdfile")) {
        file_recorder_close(recorder, 0);
        return;
    }

    const char *root_path = dev_manager_get_root_path_by_logo(logo);
    char path[64];

    snprintf(path, sizeof(path), "%s%s/%s.%s", root_path, TCFG_REC_FOLDER_NAME, TCFG_REC_FILE_NAME, suffix);

    FILE *file = file_recorder_open_file(recorder, path);
    if (!file) {
        file_recorder_close(recorder, 0);
        return;
    }
    file_recorder_set_callback(recorder, NULL, file_recorder_callback);

    err = file_recorder_start(recorder);
    if (err) {
        log_error("file_recorder_err: %d", err);
        file_recorder_close(recorder, 1);
        return;
    }

    __this->logo = logo;
    __this->recorder = recorder;
}

static void recorder_stop(void)
{
    file_recorder_close(__this->recorder, 1);
    __this->recorder = NULL;
}

static void recorder_device_offline_check(const char *logo)
{
    if (__this->recorder && !strcmp(__this->logo, logo)) {
        ///当前录音正在使用的设备掉线， 应该停掉录音
        log_info("is the recording dev = %s", logo);
        file_recorder_close(__this->recorder, 0);
        __this->recorder = NULL;
    }
}

static int recorder_init(void)
{
    tone_player_stop();

    play_tone_file_callback(get_tone_files()->record_mode, NULL,
                            recorder_tone_play_end_callback);

    /* app_send_message(APP_MSG_ENTER_MODE, APP_MODE_RECORD); */

    return 0;
}

static int recorder_exit(void)
{
    recorder_stop();

    /* app_send_message(APP_MSG_EXIT_MODE, APP_MODE_RECORD); */

    return 0;
}

static int recorder_msg_handler(struct application *app, int *msg)
{
    switch (msg[0]) {
    case APP_MSG_RECORDER_PP:
        if (!__this->recorder) {
            recorder_start();
        } else {
            recorder_stop();
        }
        break;
    default:
        break;
    }

    return 0;
}

static void recorder_app_suspend(void)
{
    if (__this->recorder) {
        recorder_stop();
        __this->suspend_flag = 1;
    }
}

static void recorder_app_resume(void)
{
    if (!__this->suspend_flag) {
        return;
    }

    recorder_start();

    __this->suspend_flag = 0;
}

static void recorder_app_stop(void)
{
    recorder_stop();

    __this->suspend_flag = 0;
}

static int recorder_key_click(struct key_event *key)
{
    int ret = true;

    switch (key->value) {
    case KEY_OK:
        app_send_message(APP_MSG_RECORDER_PP, 0);
        break;
    default:
        ret = false;
        break;
    }

    return ret;
}

static int recorder_key_long(struct key_event *key)
{
    return false;
}

static int recorder_key_hold(struct key_event *key)
{
    return false;
}

static int recorder_key_event_handler(struct key_event *key)
{
    int ret = false;

    switch (key->action) {
    case KEY_EVENT_CLICK:
        ret = recorder_key_click(key);
        break;
    case KEY_EVENT_LONG:
        ret = recorder_key_long(key);
        break;
    case KEY_EVENT_HOLD:
        ret = recorder_key_hold(key);
        break;
    default:
        break;
    }

    return ret;
}

static int recorder_device_event_handler(enum device_event_from from, struct device_event *device_event)
{
    switch (from) {
    case DEVICE_EVENT_FROM_SD:
    case DEVICE_EVENT_FROM_UDISK:
        if (device_event->event == DEVICE_EVENT_OUT) {
            recorder_device_offline_check((const char *)device_event->arg);
        }
        break;
    default:
        break;
    }

    return false;
}

static int recorder_event_handler(struct application *app, struct sys_event *event)
{
    switch (event->type) {
    case SYS_KEY_EVENT:
        return recorder_key_event_handler((struct key_event *)event->payload);
    case SYS_DEVICE_EVENT:
        return recorder_device_event_handler(event->from, (struct device_event *)event->payload);
    default:
        return false;
    }
}

static int recorder_state_machine(struct application *app, enum app_state state,
                                  struct intent *it)
{
    switch (state) {
    case APP_STA_CREATE:
        recorder_init();
        break;
    case APP_STA_START:
        break;
    case APP_STA_PAUSE:
        recorder_app_suspend();
        break;
    case APP_STA_RESUME:
        recorder_app_resume();
        break;
    case APP_STA_STOP:
        break;
    case APP_STA_DESTROY:
        recorder_exit();
        break;
    case APP_STA_COMPLETE:
        break;
    }

    return 0;
}

static const struct application_operation recorder_ops = {
    .state_machine  = recorder_state_machine,
    .event_handler 	= recorder_event_handler,
    .msg_handler 	= recorder_msg_handler,
};

REGISTER_APPLICATION(recorder) = {
    .name   = "recorder",
    .ops    = &recorder_ops,
    .state  = APP_STA_DESTROY,
};

#endif

