#include "usb/device/usb_stack.h"
#include "usb/device/hid.h"
#include "tone_player.h"
#include "app_tone.h"
#include "app_core.h"
#include "app_msg.h"
#include "event/device_event.h"
#include "event/key_event.h"
#include "usb_host_spk_player.h"
#include "pc_mic_recorder.h"
#include "usb/device/uac_audio.h"
#include "effect/effects_default_param.h"
#include "audio_base.h"
#include "volume_node.h"
#include "audio_config.h"
#include "audio_def.h"
#include "system/timer.h"
#include "wireless_trans.h"
#include "device/uac_stream.h"
#include "system/init.h"


#define LOG_TAG             "[APP_USB_HOST]"
#define LOG_ERROR_ENABLE
#define LOG_DEBUG_ENABLE
#define LOG_INFO_ENABLE
/* #define LOG_DUMP_ENABLE */
#define LOG_CLI_ENABLE
#include "debug.h"

#if TCFG_HOST_AUDIO_ENABLE

typedef struct {
    int pre_value[USB_MAX_HW_NUM];
    s16 volume;
    u16 key_timer;
    u16 resume_play_timer;
    u8 key_cnt;
    u8 onoff[USB_MAX_HW_NUM];
    u8 run_flag[USB_MAX_HW_NUM];
    u8 curr_usb_id;
    u8 le_audio_flag;
    u8 suspend_flag;
    u8 suspend_play_flag;
    u8 pp_wait_release;
    u8 check_hangup;
    pitch_level_t pitch_mode;
    struct stream_fmt fmt[USB_MAX_HW_NUM];
    struct usb_host_spk_player *player[USB_MAX_HW_NUM];
    struct usb_host_mic_recorder *recorder[USB_MAX_HW_NUM];
} usb_host_music_t;

static usb_host_music_t usb_host_hdl = {
    .pitch_mode = PITCH_0,
};

#define __this 	(&usb_host_hdl)

#if !USB_HOST_NO_APP_MODE

static void usb_host_task_start(int usb_id)
{
    log_info("usb_host_task_start id:%d", usb_id);
    struct device_event usb_host_event = {0};
    u32 state;

    if (usb_id == 0xff) {
        for (u8 i = 0; i < USB_MAX_HW_NUM; ++i) {
            if (__this->onoff[i]) {
                log_info("USB_HOST%d is start", i);
                continue;
            }
            state = usb_otg_online(i);
            if (state == HOST_MODE) {
                usb_host_event.value = "audio";
                usb_host_event.arg = i ? (void *)"usb_host1" : (void *)"usb_host0";
                usb_host_event.event = DEVICE_EVENT_ONLINE;
                device_event_notify(DEVICE_EVENT_FROM_USB_HOST, &usb_host_event);
                __this->onoff[i] = 1;
            } else {
                log_error("host usb_otg_online mode:%d", state);
            }
        }
    } else {
        if (__this->onoff[usb_id]) {
            log_info("USB_HOST%d is start", usb_id);
            return;
        }

        state = usb_otg_online(usb_id);
        if (state == HOST_MODE) {
            usb_host_event.value = "audio";
            usb_host_event.arg = usb_id ? (void *)"usb_host1" : (void *)"usb_host0";
            usb_host_event.event = DEVICE_EVENT_ONLINE;
            device_event_notify(DEVICE_EVENT_FROM_USB_HOST, &usb_host_event);
            __this->onoff[usb_id] = 1;
        } else {
            log_error("host usb_otg_online mode:%d", state);
        }
    }
}

static bool usb_host_task_stop(int usb_id)
{
    log_info("usb_host_task_stop");
    struct device_event usb_host_event = {0};
    u32 state;
    bool ret = FALSE;

    if (usb_id == 0xff) {
        for (u8 i = 0; i < USB_MAX_HW_NUM; ++i) {
            if (!__this->onoff[i]) {
                log_info("USB_HOST%d is stop", i);
                continue;
            }
            state = usb_otg_online(i);
            if (state == HOST_MODE || state == DISCONN_MODE) {
                usb_host_event.value = "audio";
                usb_host_event.arg = i ? (void *)"usb_host1" : (void *)"usb_host0";
                usb_host_event.event = DEVICE_EVENT_OFFLINE;
                device_event_notify(DEVICE_EVENT_FROM_USB_HOST, &usb_host_event);
                __this->onoff[i] = 0;
            }
        }
    } else {
        if (!__this->onoff[usb_id]) {
            log_info("USB_HOST%d is stop", usb_id);
            return ret;
        }

        state = usb_otg_online(usb_id);
        if (state == HOST_MODE || state == DISCONN_MODE) {
            usb_host_event.value = "audio";
            usb_host_event.arg = usb_id ? (void *)"usb_host1" : (void *)"usb_host0";
            usb_host_event.event = DEVICE_EVENT_OFFLINE;
            device_event_notify(DEVICE_EVENT_FROM_USB_HOST, &usb_host_event);
            __this->onoff[usb_id] = 0;
        }
    }

    return ret;
}

static int usb_host_music_msg_handler(struct application *app, int *msg)
{
    if (__this->resume_play_timer) {
        sys_timeout_del(__this->resume_play_timer);
        __this->resume_play_timer = 0;
    }

    switch (msg[0]) {
    case 0:
        break;
    default:
        break;
    }

    return 0;
}

static int usb_host_tone_play_end_callback(void *priv, enum stream_event event)
{
    int usb_id;
    u32 state;

    switch (event) {
    case STREAM_EVENT_NONE:
    case STREAM_EVENT_STOP:
        break;
    default:
        break;
    }
    return 0;
}

static int usb_host_music_init(void)
{
    tone_player_stop();

    __this->volume = app_audio_get_volume(APP_AUDIO_STATE_MUSIC);//记录下当前音量

#if 0
    int ret;
    ret = play_tone_file_callback(get_tone_files()->host_mode, NULL, usb_host_tone_play_end_callback);
    if (ret) {
        usb_host_task_start(0xff);
    }
#else
    usb_host_task_start(0xff);
#endif

    return 0;
}

u8 get_host_uac_spk_def_vol(void)
{
    return app_audio_get_volume(APP_AUDIO_STATE_MUSIC);
}

static void usb_host_music_exit(void)
{
    __this->suspend_flag = 0;
    __this->suspend_play_flag = 0;

    if (__this->resume_play_timer) {
        sys_timeout_del(__this->resume_play_timer);
        __this->resume_play_timer = 0;
    }

    usb_host_task_stop(0xff);

    app_audio_set_volume(APP_AUDIO_STATE_MUSIC, __this->volume, 1);
}

static int usb_host_music_key_click(struct key_event *key)
{
    int ret = FALSE;

    switch (key->value) {
    case KEY_OK:
        ret = TRUE;
        break;
    case KEY_VOLUME_DEC:
    case KEY_UP:
    case KEY_PREV:
        break;
    case KEY_VOLUME_INC:
    case KEY_DOWN:
    case KEY_NEXT:
        break;
    case KEY_PLAY:
        break;
    case KEY_PAUSE:
        break;
    default:
        break;
    }

    return ret;
}

static int usb_host_music_key_long(struct key_event *key)
{
    int ret = TRUE;

    switch (key->value) {
    case KEY_VOLUME_DEC:
    case KEY_UP:
    case KEY_PREV:
        break;
    case KEY_VOLUME_INC:
    case KEY_DOWN:
    case KEY_NEXT:
        break;
    default:
        ret = FALSE;
        break;
    }

    return ret;
}

static int usb_host_music_key_event_handler(struct key_event *key)
{
    int ret = FALSE;

    switch (key->action) {
    case KEY_EVENT_CLICK:
        ret = usb_host_music_key_click(key);
        break;
    case KEY_EVENT_LONG:
        ret = usb_host_music_key_long(key);
        break;
    case KEY_EVENT_HOLD:
        break;
    default:
        break;
    }

    return ret;
}

static int usb_host_music_event_handler(struct application *app, struct sys_event *event)
{
    switch (event->type) {
    case SYS_KEY_EVENT:
        return usb_host_music_key_event_handler((struct key_event *)event->payload);
    default:
        return FALSE;
    }
}

static int usb_host_music_state_machine(struct application *app, enum app_state state,
                                        struct intent *it)
{
    switch (state) {
    case APP_STA_CREATE:
        usb_host_music_init();
        break;
    case APP_STA_START:
        break;
    case APP_STA_PAUSE:
        break;
    case APP_STA_RESUME:
        break;
    case APP_STA_STOP:
        break;
    case APP_STA_DESTROY:
        usb_host_music_exit();
        break;
    case APP_STA_COMPLETE:
        break;
    }

    return 0;
}

static const struct application_operation usb_host_music_ops = {
    .state_machine  = usb_host_music_state_machine,
    .event_handler 	= usb_host_music_event_handler,
    .msg_handler 	= usb_host_music_msg_handler,

};

REGISTER_APPLICATION(usb_host_music) = {
    .name   = "usb_host_music",
    .ops    = &usb_host_music_ops,
    .state  = APP_STA_DESTROY,
};

static int usb_host_music_device_event_handler(void *evt)
{
    struct device_event *event = (struct device_event *)evt;

    if (usb_host_music.state != APP_STA_START && usb_host_music.state != APP_STA_PAUSE) {
        return FALSE;
    }

    u8 usb_id;
    if (!strncmp((const char *)event->value, "audio0", 6)) {
        usb_id = 0;
    } else if (!strncmp((const char *)event->value, "audio1", 6)) {
        usb_id = 1;
    }

    if (event->event == DEVICE_EVENT_IN) {
        usb_host_task_start(usb_id);
    } else if (event->event == DEVICE_EVENT_OUT) {
        usb_host_task_stop(usb_id);
    }

    return FALSE;
}

REGISTER_APP_EVENT_HANDLER(usb_host_music_device_event) = {
    .event      = SYS_DEVICE_EVENT,
    .from       = DEVICE_EVENT_FROM_USB_HOST,
    .handler    = usb_host_music_device_event_handler,
};

#endif


static int usb_host_audio_play_put_buf(const usb_dev usb_id, void *buf, u32 len, u8 channel, u32 sample_rate)
{
    if (channel == 0 && sample_rate == 0) {
        if (__this->player[usb_id]) {
            usb_host_spk_player_close(__this->player[usb_id]);
            __this->player[usb_id] = NULL;
            return 0;
        }
    }

    if (!__this->player[usb_id]) {
        if (channel & BIT(7)) {
            channel = 1;
        }
        log_info("usb host spk usb_id:%d,channel:%d,sr:%d", usb_id, channel, sample_rate);
        struct stream_fmt fmt = {0};
        fmt.chconfig_id = usb_id;
        fmt.sample_rate = sample_rate;
        fmt.bit_wide = DATA_BIT_WIDE_16BIT;
        fmt.channel_mode = (channel == 2) ? AUDIO_CH_LR : AUDIO_CH_L;
        __this->player[usb_id] = usb_host_spk_player_open(&fmt);
    }

    usb_host_spk_player_put_buf(usb_id, buf, len);

    return len;
}

static int usb_host_audio_record_get_buf(const usb_dev usb_id, void *buf, u32 len, u8 channel, u32 sample_rate)
{
    if (channel == 0 && sample_rate == 0) {
        if (__this->recorder[usb_id]) {
            usb_host_mic_recorder_close(__this->recorder[usb_id]);
            __this->recorder[usb_id] = NULL;
            return 0;
        }
    }

    if (!__this->recorder[usb_id]) {
        log_info("usb host mic usb_id:%d,channel:%d,sr:%d", usb_id, channel, sample_rate);
        struct stream_fmt fmt = {0};
        fmt.chconfig_id = usb_id;
        fmt.sample_rate = sample_rate;
        fmt.bit_wide = DATA_BIT_WIDE_16BIT;
        fmt.channel_mode = (channel == 2) ? AUDIO_CH_LR : AUDIO_CH_L;
        __this->recorder[usb_id] = usb_host_mic_recorder_open(&fmt);
    }

    usb_host_mic_recorder_get_buf(usb_id, buf, len);

    return len;
}

static int usb_host_audio_api_init(void)
{
    usb_host_audio_init(0, usb_host_audio_play_put_buf, usb_host_audio_record_get_buf);
#if USB_MAX_HW_NUM > 1
    usb_host_audio_init(1, usb_host_audio_play_put_buf, usb_host_audio_record_get_buf);
#endif
    return 0;
}
late_initcall(usb_host_audio_api_init);

#endif
