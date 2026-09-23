#include "usb/device/usb_stack.h"
#include "usb/device/hid.h"
#include "tone_player.h"
#include "app_tone.h"
#include "app_core.h"
#include "app_msg.h"
#include "event/device_event.h"
#include "event/key_event.h"
#include "pc_spk_player.h"
#include "pc_mic_recorder.h"
#include "usb/device/uac_audio.h"
#include "effect/effects_default_param.h"
#include "audio_base.h"
#include "volume_node.h"
#include "audio_config.h"
#include "audio_def.h"
#include "system/timer.h"
#if TCFG_LOCAL_TWS_ENABLE
#include "local_tws.h"
#endif
#include "wireless_trans.h"
#if TCFG_LE_AUDIO_STREAM_ENABLE
#include "le_audio_recorder.h"
#include "app_le_broadcast.h"
#include "app_le_auracast.h"
#include "le_broadcast.h"
#include "le_audio_player.h"
#endif


#define LOG_TAG             "[APP_PC]"
#define LOG_ERROR_ENABLE
#define LOG_DEBUG_ENABLE
#define LOG_INFO_ENABLE
/* #define LOG_DUMP_ENABLE */
#define LOG_CLI_ENABLE
#include "debug.h"

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
    struct pc_spk_player *player[USB_MAX_HW_NUM];
    struct pc_mic_recorder *recorder[USB_MAX_HW_NUM];
} pc_music_t;

static pc_music_t pc_hdl = {
    .pitch_mode = PITCH_0,
};

#define __this 	(&pc_hdl)


#if TCFG_APP_PC_EN && !USB_PC_NO_APP_MODE

static void pc_task_start(int usb_id)
{
    struct device_event pc_event = {0};
    u32 state;

    if (usb_id == 0xff) {
        for (u8 i = 0; i < USB_MAX_HW_NUM; ++i) {
            if (__this->onoff[i]) {
                log_info("PC%d is start", i);
                continue;
            }
            state = usb_otg_online(i);
            if ((state == SLAVE_MODE) || (state == SLAVE_MODE_WAIT_CONFIRMATION)) {
                pc_event.value = i;
                pc_event.event = DEVICE_EVENT_ONLINE;
                device_event_notify(DEVICE_EVENT_FROM_PC, &pc_event);
                __this->onoff[i] = 1;
            }
        }
    } else {
        if (__this->onoff[usb_id]) {
            log_info("PC%d is start", usb_id);
            return;
        }

        state = usb_otg_online(usb_id);
        if ((state == SLAVE_MODE) || (state == SLAVE_MODE_WAIT_CONFIRMATION)) {
            pc_event.value = usb_id;
            pc_event.event = DEVICE_EVENT_ONLINE;
            device_event_notify(DEVICE_EVENT_FROM_PC, &pc_event);
            __this->onoff[usb_id] = 1;
            log_info("pc%d app start", usb_id);
        }
    }
}

static bool pc_task_stop(int usb_id)
{
    struct device_event pc_event = {0};
    u32 state;
    bool ret = FALSE;

    if (usb_id == 0xff) {
        for (u8 i = 0; i < USB_MAX_HW_NUM; ++i) {
            if (!__this->onoff[i]) {
                log_info("PC%d is stop", i);
                continue;
            }
            state = usb_otg_online(i);
            if ((state == SLAVE_MODE) || (state == SLAVE_MODE_WAIT_CONFIRMATION)) {
                pc_event.value = i;
                pc_event.event = DEVICE_EVENT_OFFLINE;
                device_event_notify(DEVICE_EVENT_FROM_PC, &pc_event);
                ret = TRUE;
            }
            __this->onoff[i] = 0;
        }
    } else {
        if (!__this->onoff[usb_id]) {
            log_info("PC%d is stop", usb_id);
            return ret;
        }

        state = usb_otg_online(usb_id);
        if ((state == SLAVE_MODE) || (state == SLAVE_MODE_WAIT_CONFIRMATION)) {
            pc_event.value = usb_id;
            pc_event.event = DEVICE_EVENT_OFFLINE;
            device_event_notify(DEVICE_EVENT_FROM_PC, &pc_event);
            log_info("pc%d app stop", usb_id);
            ret = TRUE;
        }
        __this->onoff[usb_id] = 0;
    }

    return ret;
}

#if (TCFG_LEA_BIG_CTRLER_TX_EN || TCFG_LEA_BIG_CTRLER_RX_EN || TCFG_LEA_CIG_CENTRAL_EN || TCFG_LEA_CIG_PERIPHERAL_EN) || \
    (TCFG_LE_AUDIO_APP_CONFIG & (LE_AUDIO_AURACAST_SOURCE_EN | LE_AUDIO_JL_AURACAST_SOURCE_EN)) || \
    (TCFG_LE_AUDIO_APP_CONFIG & (LE_AUDIO_AURACAST_SINK_EN | LE_AUDIO_JL_AURACAST_SINK_EN)) || \
    (TCFG_LE_AUDIO_APP_CONFIG & (LE_AUDIO_UNICAST_SOURCE_EN | LE_AUDIO_JL_UNICAST_SOURCE_EN)) || \
    (TCFG_LE_AUDIO_APP_CONFIG & (LE_AUDIO_UNICAST_SINK_EN | LE_AUDIO_JL_UNICAST_SINK_EN))

/* --------------------------------------------------------------------------*/
/**
 * @brief 获取pc模式广播音频流开启标志
 *
 * @return 广播音频流开启标志
 */
/* ----------------------------------------------------------------------------*/
static u8 get_pc_le_audio_flag(void)
{
    return __this->le_audio_flag;
}

static int get_pc_play_status(void)
{
    if (get_le_audio_app_mode_exit_flag()) {
        return LOCAL_AUDIO_PLAYER_STATUS_STOP;
    }

    for (u8 i = 0; i < USB_MAX_HW_NUM; ++i) {
        if (__this->run_flag[i]) {
            return LOCAL_AUDIO_PLAYER_STATUS_PLAY;
        }
    }

    return LOCAL_AUDIO_PLAYER_STATUS_STOP;
}

static int pc_local_audio_open(void)
{
#if TCFG_USB_SLAVE_AUDIO_SPK_ENABLE
    u8 usb_id = __this->curr_usb_id;
    __this->player[usb_id] = pc_spk_player_open(&(__this->fmt[usb_id]));
#endif
    return 0;
}

static int pc_local_audio_close(void)
{
#if TCFG_USB_SLAVE_AUDIO_SPK_ENABLE
    u8 usb_id = __this->curr_usb_id;

    if (__this->player[usb_id]) {
        //关闭本地播放
        pc_spk_player_close(__this->player[usb_id]);
        __this->player[usb_id] = NULL;
    }
#endif
    return 0;
}

static void *pc_tx_le_audio_open(void *args)
{
#if TCFG_USB_SLAVE_AUDIO_SPK_ENABLE
    __this->le_audio_flag = 1;
    u8 usb_id = __this->curr_usb_id;
    //打开广播音频播放
    struct le_audio_stream_params *params = (struct le_audio_stream_params *)args;
    void *le_audio = le_audio_stream_create(params->conn, &params->fmt);
    int err = le_audio_pc_recorder_open((void *)&params->fmt, le_audio, params->latency, &(__this->fmt[usb_id]));
    if (err != 0) {
        ASSERT(0, "recorder open fail");
    }
#if TCFG_LEA_LOCAL_SYNC_PLAY_EN
    err = le_audio_player_open(le_audio, params);
    if (err != 0) {
        ASSERT(0, "player open fail");
    }
#endif

    u16 l_vol = 0, r_vol = 0;
    uac_speaker_stream_get_volume(usb_id, &l_vol, &r_vol);
    app_audio_set_volume(APP_AUDIO_STATE_MUSIC, (r_vol + l_vol) / 2, 1);

    //update_le_audio_deal_scene(LE_AUDIO_MUSIC_START);

    return le_audio;

#else
    return NULL;
#endif
}

static int pc_tx_le_audio_close(void *le_audio)
{
    if (!le_audio) {
        return -EPERM;
    }
#if TCFG_USB_SLAVE_AUDIO_SPK_ENABLE
    //关闭广播音频播放
#if TCFG_LEA_LOCAL_SYNC_PLAY_EN
    le_audio_player_close(le_audio);
#endif
    le_audio_pc_recorder_close();
    le_audio_stream_free(le_audio);
    __this->le_audio_flag = 0;
#endif
    return 0;
}

const struct le_audio_mode_ops le_audio_pc_ops = {
    .local_audio_open = pc_local_audio_open,
    .local_audio_close = pc_local_audio_close,
    .tx_le_audio_open = pc_tx_le_audio_open,
    .tx_le_audio_close = pc_tx_le_audio_close,
    .rx_le_audio_open = default_rx_le_audio_open,
    .rx_le_audio_close = default_rx_le_audio_close,
    .play_status = get_pc_play_status,
};
#endif

#if TCFG_USB_SLAVE_HID_ENABLE

static void pc_hid_pp_long_press_release(void *priv)
{
    hid_key_handler_send_one_packet(__this->curr_usb_id, USB_AUDIO_NONE);
    __this->pp_wait_release = 0;
}

static void pc_call_reject_or_hand_up(void)
{
    if (__this->pp_wait_release) {
        //HID按键未释放不允许再次发送
        return;
    }
    //来电：
    //android   短按接听，长按拒接
    //ios       短按接听，长按拒接
    //通话中：
    //android   短按toggle mic mute，长按挂断
    //ios       短按挂断
    hid_key_handler_send_one_packet(__this->curr_usb_id, USB_AUDIO_PP);
    sys_timeout_add(NULL, pc_hid_pp_long_press_release, 1200);
    __this->pp_wait_release = 1;
}

static void pc_music_pp_handler(void)
{
#if ((TCFG_LEA_BIG_CTRLER_TX_EN || TCFG_LEA_BIG_CTRLER_RX_EN) || \
    (TCFG_LE_AUDIO_APP_CONFIG & (LE_AUDIO_AURACAST_SOURCE_EN | LE_AUDIO_AURACAST_SINK_EN))) && (TCFG_LEA_BIG_FIX_ROLE==2)
    //在pc模式下作为接收端时，控制mute（即播放暂停响应）
    u8 pc_volume_mute_mark = app_audio_get_mute_state(APP_AUDIO_STATE_MUSIC);
#if (TCFG_LEA_BIG_CTRLER_TX_EN || TCFG_LEA_BIG_CTRLER_RX_EN)
    if (get_broadcast_role() == 0) {
#else
    if (get_auracast_role() == 0) {
#endif
        hid_key_handler(__this->curr_usb_id, USB_AUDIO_PP);
    } else {
        //作为广播接收端播歌中
        pc_volume_mute_mark ^= 1;
        audio_app_mute_en(pc_volume_mute_mark);
    }
#else
    if (__this->key_timer) {
        return;
    }
    if (usb_get_host_type(__this->curr_usb_id) == HOST_TYPE_ANDROID && pc_mic_recorder_runing()) {
        pc_call_reject_or_hand_up();
    } else {
        hid_key_handler(__this->curr_usb_id, USB_AUDIO_PP);
    }
#endif
}

static void pc_music_key_timer(void *p)
{
    hid_key_handler(__this->curr_usb_id, USB_AUDIO_PP);

    if (--__this->key_cnt > 0) {
        sys_timer_del(__this->key_timer);
        __this->key_timer = 0;
        __this->key_cnt = 0;

        if (__this->check_hangup) {
            __this->check_hangup = 0;
            if (usb_get_host_type(__this->curr_usb_id) == HOST_TYPE_IOS) {
                return;
            }
            os_time_dly(2);
            pc_call_reject_or_hand_up();
        }
    }
}

static void pc_music_resume_play_timer_callback(void *p)
{
    __this->resume_play_timer = 0;

    hid_key_handler(__this->curr_usb_id, USB_AUDIO_PP);
}

#endif

static int pc_music_msg_handler(struct application *app, int *msg)
{
    if (__this->resume_play_timer) {
        sys_timeout_del(__this->resume_play_timer);
        __this->resume_play_timer = 0;
    }

#if TCFG_USB_SLAVE_HID_ENABLE
    if (__this->pp_wait_release && (msg[0] >= APP_MSG_PC_MUSIC_PP && msg[0] <= APP_MSG_PC_MUSIC_VOL_DOWN)) {
        return 0;
    }
#endif

    switch (msg[0]) {
#if TCFG_USB_SLAVE_HID_ENABLE
    case APP_MSG_PC_MUSIC_CALL_HANGUP:
        log_info("hang up");
        if (usb_get_host_type(__this->curr_usb_id) == HOST_TYPE_ANDROID || usb_get_host_type(__this->curr_usb_id) == HOST_TYPE_IOS) {
            if (__this->key_timer) {
                __this->check_hangup = 1;
            } else {
                if (usb_get_host_type(__this->curr_usb_id) == HOST_TYPE_IOS && pc_mic_recorder_runing()) {
                    hid_key_handler(__this->curr_usb_id, USB_AUDIO_PP);
                } else {
                    pc_call_reject_or_hand_up();
                }
            }
        }
        break;
    case APP_MSG_PC_MUSIC_PP:
        log_info("pp");
        pc_music_pp_handler();
        break;
    case APP_MSG_PC_MUSIC_PREV:
        log_info("play prev");
        //android和ios三击PP上一曲，windows发标准的PREV，小米手机系统要反过来
        if (usb_get_host_type(__this->curr_usb_id) == HOST_TYPE_ANDROID || usb_get_host_type(__this->curr_usb_id) == HOST_TYPE_IOS) {
            if (__this->key_timer) {
                break;
            }
            __this->key_cnt = 1;
            hid_key_handler(__this->curr_usb_id, USB_AUDIO_PP);
            __this->key_timer = sys_timer_add(NULL, pc_music_key_timer, 6);
        } else {
            hid_key_handler(__this->curr_usb_id, USB_AUDIO_PREFILE);
        }
        break;
    case APP_MSG_PC_MUSIC_NEXT:
        log_info("play next");
        //android和ios双击PP下一曲，windows发标准的NEXT，小米手机系统要反过来
        if (usb_get_host_type(__this->curr_usb_id) == HOST_TYPE_ANDROID || usb_get_host_type(__this->curr_usb_id) == HOST_TYPE_IOS) {
            if (__this->key_timer) {
                break;
            }
            __this->key_cnt = 2;
            __this->check_hangup = 1;
            hid_key_handler(__this->curr_usb_id, USB_AUDIO_PP);
            __this->key_timer = sys_timer_add(NULL, pc_music_key_timer, 6);
        } else {
            hid_key_handler(__this->curr_usb_id, USB_AUDIO_NEXTFILE);
        }
        break;
    case APP_MSG_PC_MUSIC_VOL_UP:
        log_info("vol up");
        hid_key_handler(__this->curr_usb_id, USB_AUDIO_VOLUP);
        break;
    case APP_MSG_PC_MUSIC_VOL_DOWN:
        log_info("vol down");
        hid_key_handler(__this->curr_usb_id, USB_AUDIO_VOLDOWN);
        break;
    case APP_MSG_PC_MUSIC_PLAY:
        log_info("play");
        if (!__this->player[__this->curr_usb_id] && !__this->le_audio_flag) {
            pc_music_pp_handler();
        }
        break;
    case APP_MSG_PC_MUSIC_PAUSE:
        log_info("pause");
        if (__this->player[__this->curr_usb_id] || __this->le_audio_flag) {
            pc_music_pp_handler();
        }
        break;
#else
    case APP_MSG_PC_MUSIC_PP:
        log_info("pp");
        for (u8 i = 0; i < USB_MAX_HW_NUM; ++i) {
            if (__this->onoff[i]) {
                pc_task_stop(0xff);
                return 0;
            }
        }
        pc_task_start(0xff);
        break;
    case APP_MSG_PC_MUSIC_PLAY:
        log_info("play");
        pc_task_start(0xff);
        break;
    case APP_MSG_PC_MUSIC_PAUSE:
        log_info("pause");
        pc_task_stop(0xff);
        break;
#endif
    case APP_MSG_RESUME:
        if (!__this->suspend_flag) {
            break;
        }
        pc_task_start(0xff);
        __this->suspend_flag = 0;
#if TCFG_USB_SLAVE_HID_ENABLE
        if (__this->suspend_play_flag) {
            __this->resume_play_timer = sys_timeout_add(NULL, pc_music_resume_play_timer_callback, 2500);
            __this->suspend_play_flag = 0;
        }
#endif
        break;
    case APP_MSG_SUSPEND:
#if TCFG_USB_SLAVE_HID_ENABLE
        if (pc_spk_player_runing()) {
            hid_key_handler(__this->curr_usb_id, USB_AUDIO_PP);
            os_time_dly(5);
            __this->suspend_play_flag = 1;
        }
#endif
        __this->suspend_flag = pc_task_stop(0xff);
        break;
    case APP_MSG_STOP:
        __this->suspend_flag = 0;
        __this->suspend_play_flag = 0;
        break;
    case APP_MSG_PC_MUSIC_MOUNT:
        log_info("mount");
        pc_task_start(0xff);
        break;
    case APP_MSG_PC_MUSIC_PITCH_DOWN:
        log_info("pitch down");
        if (__this->player[__this->curr_usb_id]) {
            pc_spk_player_pitch_down(__this->player[__this->curr_usb_id]);
        }
        break;
    case APP_MSG_PC_MUSIC_PITCH_UP:
        log_info("pitch up");
        if (__this->player[__this->curr_usb_id]) {
            pc_spk_player_pitch_up(__this->player[__this->curr_usb_id]);
        }
        break;
    default:
        break;
    }

    return 0;
}

static int pc_tone_play_end_callback(void *priv, enum stream_event event)
{
    int usb_id;
    u32 state;

    switch (event) {
    case STREAM_EVENT_NONE:
    case STREAM_EVENT_STOP:
        app_send_message(APP_MSG_PC_MUSIC_MOUNT, 0);
        break;
    default:
        break;
    }
    return 0;
}

static int pc_music_init(void)
{
#if TCFG_LE_AUDIO_STREAM_ENABLE
    le_audio_scene_deal(LE_AUDIO_APP_MODE_EXIT);
#endif

    tone_player_stop();

    __this->volume = app_audio_get_volume(APP_AUDIO_STATE_MUSIC);//记录下当前音量

    int ret;
#if TCFG_LOCAL_TWS_ENABLE
    ret = local_tws_enter_mode(get_tone_files()->pc_mode, APP_MODE_PC, NULL);
    if (ret)
#endif
    {
        ret = play_tone_file_callback(get_tone_files()->pc_mode, NULL, pc_tone_play_end_callback);
        if (ret) {
            pc_task_start(0xff);
        }
    }

    /* app_send_message(APP_MSG_ENTER_MODE, APP_MODE_PC); */

    return 0;
}

static void pc_music_exit(void)
{
    __this->suspend_flag = 0;
    __this->suspend_play_flag = 0;

    if (__this->resume_play_timer) {
        sys_timeout_del(__this->resume_play_timer);
        __this->resume_play_timer = 0;
    }

#if TCFG_LOCAL_TWS_ENABLE
    local_tws_exit_mode();
#endif
    pc_task_stop(0xff);

    app_audio_set_volume(APP_AUDIO_STATE_MUSIC, __this->volume, 1);

#if (TCFG_DEC2TWS_ENABLE)
    bt_tws_sync_volume();
#endif

#if TCFG_LE_AUDIO_STREAM_ENABLE
    le_audio_scene_deal(LE_AUDIO_APP_MODE_EXIT);
#endif
    /* app_send_message(APP_MSG_EXIT_MODE, APP_MODE_PC); */
}

static int pc_music_key_click(struct key_event *key)
{
    int ret = FALSE;

    switch (key->value) {
    case KEY_OK:
        app_send_message(APP_MSG_PC_MUSIC_PP, 0);
        ret = TRUE;
        break;
    case KEY_VOLUME_DEC:
    case KEY_UP:
    case KEY_PREV:
        app_send_message(APP_MSG_PC_MUSIC_VOL_DOWN, 0);
        break;
    case KEY_VOLUME_INC:
    case KEY_DOWN:
    case KEY_NEXT:
        app_send_message(APP_MSG_PC_MUSIC_VOL_UP, 0);
        break;
    case KEY_PLAY:
        app_send_message(APP_MSG_PC_MUSIC_PLAY, 0);
        break;
    case KEY_PAUSE:
        app_send_message(APP_MSG_PC_MUSIC_PAUSE, 0);
        break;
    default:
        break;
    }

    return ret;
}

static int pc_music_key_long(struct key_event *key)
{
    int ret = TRUE;

    switch (key->value) {
    case KEY_VOLUME_DEC:
    case KEY_UP:
    case KEY_PREV:
#if TCFG_USB_SLAVE_HID_ENABLE
        app_send_message(APP_MSG_PC_MUSIC_PREV, 0);
#else
        app_send_message(APP_MSG_PC_MUSIC_PITCH_DOWN, 0);
#endif
        break;
    case KEY_VOLUME_INC:
    case KEY_DOWN:
    case KEY_NEXT:
#if TCFG_USB_SLAVE_HID_ENABLE
        app_send_message(APP_MSG_PC_MUSIC_NEXT, 0);
#else
        app_send_message(APP_MSG_PC_MUSIC_PITCH_UP, 0);
#endif
        break;
    default:
        ret = FALSE;
        break;
    }

    return ret;
}

static int pc_music_key_event_handler(struct key_event *key)
{
    int ret = FALSE;

    switch (key->action) {
    case KEY_EVENT_CLICK:
        ret = pc_music_key_click(key);
        break;
    case KEY_EVENT_LONG:
        ret = pc_music_key_long(key);
        break;
    case KEY_EVENT_HOLD:
        break;
    default:
        break;
    }

    return ret;
}

static int pc_music_event_handler(struct application *app, struct sys_event *event)
{
    switch (event->type) {
    case SYS_KEY_EVENT:
        return pc_music_key_event_handler((struct key_event *)event->payload);
    default:
        return FALSE;
    }
}

static int pc_music_state_machine(struct application *app, enum app_state state,
                                  struct intent *it)
{
    switch (state) {
    case APP_STA_CREATE:
        pc_music_init();
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
        pc_music_exit();
        break;
    case APP_STA_COMPLETE:
#if TCFG_LE_AUDIO_STREAM_ENABLE
        le_audio_scene_deal(LE_AUDIO_APP_MODE_ENTER);
#endif
        break;
    }

    return 0;
}

static const struct application_operation pc_music_ops = {
    .state_machine  = pc_music_state_machine,
    .event_handler 	= pc_music_event_handler,
    .msg_handler 	= pc_music_msg_handler,
};

REGISTER_APPLICATION(pc_music) = {
    .name   = "pc_music",
    .ops    = &pc_music_ops,
    .state  = APP_STA_DESTROY,
};

static int pc_music_device_event_handler(void *evt)
{
    struct device_event *event = (struct device_event *)evt;

    if (pc_music.state != APP_STA_START && pc_music.state != APP_STA_PAUSE) {
        return FALSE;
    }

    if (event->event == DEVICE_EVENT_IN) {
        pc_task_start(event->value);
    } else if (event->event == DEVICE_EVENT_OUT) {
        pc_task_stop(event->value);
    }

    return FALSE;
}

REGISTER_APP_EVENT_HANDLER(pc_music_device_event) = {
    .event      = SYS_DEVICE_EVENT,
    .from       = DEVICE_EVENT_FROM_PC,
    .handler    = pc_music_device_event_handler,
};

#if TCFG_LOCAL_TWS_ENABLE
static void local_tws_pc_music_start(void *priv)
{
    app_send_message(APP_MSG_PC_MUSIC_MOUNT, 0);
}

REGISTER_LOCAL_TWS_OPS(tws_pc_music) = {
    .mode = APP_MODE_PC,
    .name = "pc_music",
    .audio_open = local_tws_pc_music_start,
    .get_play_status = pc_spk_player_runing,
};
#endif

#endif


#if TCFG_USB_SLAVE_AUDIO_ENABLE && (TCFG_USB_SLAVE_AUDIO_SPK_ENABLE || TCFG_USB_SLAVE_AUDIO_MIC_ENABLE)

#include "uac_stream.h"

u8 get_uac_spk_def_vol(void)
{
    return app_audio_get_volume(APP_AUDIO_STATE_MUSIC);
}

static int usb_audio_event_handler(void *evt)
{
    struct device_event *event = (struct device_event *)evt;
    int value = event->value;
    int usb_id = (int)event->arg;
    struct stream_fmt fmt = {0};

    switch (event->event) {
#if TCFG_USB_SLAVE_AUDIO_MIC_ENABLE
    case USB_AUDIO_MIC_OPEN:
        log_info("USB_AUDIO_SET_MIC%d_OPEN: 0x%x", usb_id, value);
        ASSERT(__this->recorder[usb_id] == NULL);
        fmt.chconfig_id = usb_id;
        fmt.sample_rate = value & 0xfffff;
        fmt.bit_wide = (((value >> 20) & 0xff) == 24) ? DATA_BIT_WIDE_24BIT : DATA_BIT_WIDE_16BIT;
        fmt.channel_mode = ((value >> 28) == 2) ? AUDIO_CH_LR : AUDIO_CH_L;
        __this->recorder[usb_id] = pc_mic_recorder_open(&fmt);
        break;
    case USB_AUDIO_MIC_CLOSE:
        log_info("USB_AUDIO_SET_MIC%d_CLOSE", usb_id);
        if (__this->recorder[usb_id]) {
            pc_mic_recorder_close(__this->recorder[usb_id]);
            __this->recorder[usb_id] = NULL;
        }
        break;
    case USB_AUDIO_MIC_RESTART:
        log_info("USB_AUDIO_SET_MIC%d_RESTART: 0x%x", usb_id, value);
        if (__this->recorder[usb_id]) {
            pc_mic_recorder_close(__this->recorder[usb_id]);
            __this->recorder[usb_id] = NULL;
        }
        fmt.chconfig_id = usb_id;
        fmt.sample_rate = value & 0xfffff;
        fmt.bit_wide = (((value >> 20) & 0xff) == 24) ? DATA_BIT_WIDE_24BIT : DATA_BIT_WIDE_16BIT;
        fmt.channel_mode = ((value >> 28) == 2) ? AUDIO_CH_LR : AUDIO_CH_L;
        __this->recorder[usb_id] = pc_mic_recorder_open(&fmt);
        break;
    case USB_AUDIO_SET_MIC_VOL:
        log_info("USB_AUDIO_SET_MIC%d_VOL : %d", usb_id, value & 0xffff);
        if (current_app_in_mode(APP_MODE_PC) == TRUE) {
            s16 volume = value & 0xffff;
            struct volume_cfg cfg = {0};
            cfg.bypass = VOLUME_NODE_CMD_SET_VOL;
            cfg.cur_vol = volume;
            int err = jlstream_set_node_param(NODE_UUID_VOLUME_CTRLER, "Vol_PcMic", (void *)&cfg, sizeof(struct volume_cfg));
            log_debug("pc mic vol: %d, ret: %d", volume, err);
        }
        break;
#endif
#if TCFG_USB_SLAVE_AUDIO_SPK_ENABLE
    case USB_AUDIO_SET_PLAY_VOL:
        log_info("USB_AUDIO_SET_PLAY%d_VOL : %d %d", usb_id, value & 0xffff, (value >> 16) & 0xffff);
        if (current_app_in_mode(APP_MODE_PC) == TRUE) {
            u16 l_vol = value & 0xffff, r_vol = (value >> 16) & 0xffff;
            s16 cur_vol = app_audio_get_volume(APP_AUDIO_STATE_MUSIC);
            if (cur_vol != ((u32)l_vol + r_vol) / 2) {
                app_audio_set_volume(APP_AUDIO_STATE_MUSIC, (l_vol + r_vol) / 2, 1);
                log_info("pc spk vol: %d", app_audio_get_volume(APP_AUDIO_CURRENT_STATE));
            }
        }
        break;
    case USB_AUDIO_PLAY_OPEN:
        log_info("USB_AUDIO_SET_PLAY%d_OPEN: 0x%x", usb_id, value);
        if (__this->run_flag[usb_id] && value == 0) {
            break;
        }
        ASSERT(__this->run_flag[usb_id] == 0);
        if (value) {
            __this->pre_value[usb_id] = value;
        } else {
            if (__this->pre_value[usb_id]) {
                value = __this->pre_value[usb_id];
            } else {
                log_error("value and pre_value is NULL!!!");
                ASSERT(0);
            }
        }
        fmt.chconfig_id = usb_id;
        fmt.sample_rate = value & 0xfffff;
        fmt.bit_wide = (((value >> 20) & 0xff) == 24) ? DATA_BIT_WIDE_24BIT : DATA_BIT_WIDE_16BIT;
        fmt.channel_mode = ((value >> 28) == 2) ? AUDIO_CH_LR : AUDIO_CH_L;
        __this->curr_usb_id = usb_id;

        if (usb_get_host_type(__this->curr_usb_id) == HOST_TYPE_ANDROID) {
            app_audio_set_volume(APP_AUDIO_STATE_MUSIC, 100, 1);
        }

        memcpy(&(__this->fmt[usb_id]), &fmt, sizeof(struct stream_fmt));
        __this->run_flag[usb_id] = 1;
#if TCFG_LE_AUDIO_STREAM_ENABLE
#if (TCFG_LEA_BIG_CTRLER_TX_EN || TCFG_LEA_BIG_CTRLER_RX_EN)
        if (get_broadcast_role()) {
#elif (TCFG_LEA_CIG_CENTRAL_EN || TCFG_LEA_CIG_PERIPHERAL_EN)
        if ((app_get_connected_role() == APP_CONNECTED_ROLE_TRANSMITTER) ||
            (app_get_connected_role() == APP_CONNECTED_ROLE_DUPLEX)) {
#else
        if (get_auracast_role()) {
#endif
            le_audio_scene_deal(LE_AUDIO_MUSIC_START);
        } else
#endif
        {
            __this->player[usb_id] = pc_spk_player_open(&fmt);
        }
        break;
    case USB_AUDIO_PLAY_CLOSE:
        log_info("USB_AUDIO_SET_PLAY%d_CLOSE", usb_id);
        if (!__this->run_flag[usb_id]) {
            break;
        }
        __this->run_flag[usb_id] = 0;
        if (__this->player[usb_id]) {
            pc_spk_player_close(__this->player[usb_id]);
            __this->player[usb_id] = NULL;
        }
#if TCFG_LE_AUDIO_STREAM_ENABLE
        le_audio_scene_deal(LE_AUDIO_MUSIC_STOP);
#endif
        if (__this->player[!usb_id]) {
            __this->curr_usb_id = !usb_id;    //可能会影响le audio TODO
        }
        break;
    case USB_AUDIO_PLAY_RESTART:
        log_info("USB_AUDIO_SET_PLAY%d_RESTART: 0x%x", usb_id, value);
        if (__this->player[usb_id]) {
            pc_spk_player_close(__this->player[usb_id]);
            __this->player[usb_id] = NULL;
        }
        fmt.chconfig_id = usb_id;
        fmt.sample_rate = value & 0xfffff;
        fmt.bit_wide = (((value >> 20) & 0xff) == 24) ? DATA_BIT_WIDE_24BIT : DATA_BIT_WIDE_16BIT;
        fmt.channel_mode = ((value >> 28) == 2) ? AUDIO_CH_LR : AUDIO_CH_L;
        __this->player[usb_id] = pc_spk_player_open(&fmt);
        __this->curr_usb_id = usb_id;
        memcpy(&(__this->fmt[usb_id]), &fmt, sizeof(struct stream_fmt));
        break;
#endif
    default:
        break;
    }

    return FALSE;
}

REGISTER_APP_EVENT_HANDLER(usb_audio_event) = {
    .event      = SYS_DEVICE_EVENT,
    .from       = DEVICE_EVENT_FROM_UAC,
    .handler    = usb_audio_event_handler,
};

#endif

