#include "app_config.h"
#include "app_tone.h"
#include "app_msg.h"
#include "app_core.h"
#include "tone_player.h"
#include "event/key_event.h"
#include "event/device_event.h"
#include "audio_config.h"
#include "scene_switch.h"
#include "linein_dev.h"
#include "linein_player.h"
#include "effect/effects_default_param.h"
#include "file_player.h"
#if TCFG_LOCAL_TWS_ENABLE
#include "local_tws.h"
#endif
#include "wireless_trans.h"
#if TCFG_LE_AUDIO_STREAM_ENABLE
#include "le_broadcast.h"
#include "le_audio_recorder.h"
#include "app_le_broadcast.h"
#include "le_audio_player.h"
#endif
#if (TCFG_LE_AUDIO_APP_CONFIG & (LE_AUDIO_AURACAST_SOURCE_EN | LE_AUDIO_AURACAST_SINK_EN))
#include "app_le_auracast.h"
#endif


#if TCFG_APP_LINEIN_EN

#define LOG_TAG             "[APP_LINEIN_MUSIC]"
#define LOG_ERROR_ENABLE
#define LOG_DEBUG_ENABLE
#define LOG_INFO_ENABLE
/* #define LOG_DUMP_ENABLE */
#define LOG_CLI_ENABLE
#include "debug.h"


//开关linein后，是否保持变调状态
#define LINEIN_PLAYBACK_PITCH_KEEP          0

typedef struct {
    u8 onoff;
    u8 suspend_flag;
    u8 audio_state; /*判断linein模式使用模拟音量还是数字音量*/
    u8 volume;
    pitch_level_t pitch_mode;
#if TCFG_LE_AUDIO_STREAM_ENABLE
    //以下两个变量都是为了解决问题：固定为接收端时，关闭广播恢复播放状态的问题
    u8 onoff_as_broadcast_receive;  //在接收模式下记录的linein状态
    u8 last_run_local_audio_close;  //上一次是否有跑 local_audio_close 函数
#if (TCFG_LEA_BIG_FIX_ROLE==1)
    //固定为发送端
    //暂停中开广播再关闭：暂停。暂停中开广播点击pp后关闭：播放。播歌开广播点击pp后关闭广播：暂停. 该变量为1时表示关闭广播时需要本地音频需要是播放状态
    u8 linein_local_audio_resume_onoff;
#endif
#endif
    struct linein_player *player;
} linein_music_t;

static linein_music_t linein_hdl = {
    .pitch_mode = PITCH_0,
};

#define __this 	(&linein_hdl)


static int linein_start(void)
{
    if (__this->onoff) {
        return 0;
    }

    __this->player = linein_player_open();
    if (!__this->player) {
        return -1;
    }

#if LINEIN_PLAYBACK_PITCH_KEEP
    audio_pitch_default_parm_set(__this->pitch_mode);
    linein_file_pitch_mode_init(__this->player, __this->pitch_mode);
#endif
#if TCFG_VOCAL_REMOVER_NODE_ENABLE
    musci_vocal_remover_update_parm();
#endif
    __this->audio_state = APP_AUDIO_STATE_MUSIC;
    __this->onoff = 1;

    return 0;
}

static void linein_stop(void)
{
    if (!__this->onoff) {
        return;
    }
    linein_player_close(__this->player);
    __this->player = NULL;
    __this->onoff = 0;
}

static int linein_pp(void)
{
    if (__this->onoff) {
        linein_stop();
    } else {
        linein_start();
    }

    log_info("pp : %d", __this->onoff);

    return __this->onoff;
}

bool linein_get_status(void)
{
    return __this->onoff;
}

static int linein_tone_play_end_callback(void *priv, enum stream_event event)
{
    switch (event) {
    case STREAM_EVENT_NONE:
    case STREAM_EVENT_STOP:
        app_send_message(APP_MSG_LINEIN_MUSIC_PLAY, 1, 1);
        break;
    default:
        break;
    }
    return 0;
}

static void linein_music_pp_handler(int need_resume);

static void linein_music_app_suspend(void)
{
    if (__this->onoff) {
        linein_music_pp_handler(1);
        __this->suspend_flag = 1;
    }
}

static void linein_music_app_resume(void)
{
    if (!__this->suspend_flag) {
        return;
    }

    if (!__this->onoff) {
        linein_music_pp_handler(0);
    }

    __this->suspend_flag = 0;
}

static void linein_music_app_stop(void)
{
    linein_stop();

    __this->suspend_flag = 0;
}

#if (TCFG_LEA_BIG_CTRLER_TX_EN || TCFG_LEA_BIG_CTRLER_RX_EN || TCFG_LEA_CIG_CENTRAL_EN || TCFG_LEA_CIG_PERIPHERAL_EN) || \
    (TCFG_LE_AUDIO_APP_CONFIG & (LE_AUDIO_AURACAST_SOURCE_EN | LE_AUDIO_JL_AURACAST_SOURCE_EN)) || \
    (TCFG_LE_AUDIO_APP_CONFIG & (LE_AUDIO_AURACAST_SINK_EN | LE_AUDIO_JL_AURACAST_SINK_EN)) || \
    (TCFG_LE_AUDIO_APP_CONFIG & (LE_AUDIO_UNICAST_SOURCE_EN | LE_AUDIO_JL_UNICAST_SOURCE_EN)) || \
    (TCFG_LE_AUDIO_APP_CONFIG & (LE_AUDIO_UNICAST_SINK_EN | LE_AUDIO_JL_UNICAST_SINK_EN))

static int get_linein_play_status(void)
{
    if (get_le_audio_app_mode_exit_flag()) {
        return LOCAL_AUDIO_PLAYER_STATUS_STOP;
    }

#if (TCFG_LEA_BIG_CTRLER_TX_EN || TCFG_LEA_BIG_CTRLER_RX_EN) || \
    (TCFG_LE_AUDIO_APP_CONFIG & (LE_AUDIO_AURACAST_SOURCE_EN | LE_AUDIO_AURACAST_SINK_EN))
#if (TCFG_LEA_BIG_CTRLER_TX_EN || TCFG_LEA_BIG_CTRLER_RX_EN)
    if (get_broadcast_role() == BROADCAST_ROLE_RECEIVER) {
#else
    if (get_auracast_role() == APP_AURACAST_AS_SINK) {
#endif
        //如果是作为接收端
        if (__this->last_run_local_audio_close) {
            if (__this->onoff_as_broadcast_receive == 1) {
                return LOCAL_AUDIO_PLAYER_STATUS_PLAY;
            } else {
                return LOCAL_AUDIO_PLAYER_STATUS_STOP;
            }
            __this->last_run_local_audio_close = 0;
        }
    }
#if (TCFG_LEA_BIG_FIX_ROLE==1)
#if (TCFG_LEA_BIG_CTRLER_TX_EN || TCFG_LEA_BIG_CTRLER_RX_EN)
    if (get_broadcast_role()) {
#else
    if (get_auracast_role()) {
#endif
        if (__this->last_run_local_audio_close) {
            __this->last_run_local_audio_close = 0;
            if (__this->linein_local_audio_resume_onoff) {
                __this->linein_local_audio_resume_onoff = 0;
                return LOCAL_AUDIO_PLAYER_STATUS_PLAY;
            } else {
                return LOCAL_AUDIO_PLAYER_STATUS_STOP;
            }
        }
    }
#endif
#endif

    if (__this->onoff) {
        return LOCAL_AUDIO_PLAYER_STATUS_PLAY;
    } else {
        return LOCAL_AUDIO_PLAYER_STATUS_STOP;
    }
}

static int linein_local_audio_open(void)
{
    return linein_start();
}

static int linein_local_audio_close(void)
{
#if (TCFG_LEA_BIG_CTRLER_TX_EN || TCFG_LEA_BIG_CTRLER_RX_EN) || \
    (TCFG_LE_AUDIO_APP_CONFIG & (LE_AUDIO_AURACAST_SOURCE_EN | LE_AUDIO_AURACAST_SINK_EN))
#if (TCFG_LEA_BIG_CTRLER_TX_EN || TCFG_LEA_BIG_CTRLER_RX_EN)
    if (get_broadcast_role() == 2) {
#else
    if (get_auracast_role() == 2) {
#endif
        //作为接收端的情况
        if (linein_get_status()) {
            linein_stop();
            __this->onoff_as_broadcast_receive = 1;
        } else {
            __this->onoff_as_broadcast_receive = 0;
        }
        __this->last_run_local_audio_close = 1;
        return 0;
    }
#if (TCFG_LEA_BIG_FIX_ROLE==1)
#if (TCFG_LEA_BIG_CTRLER_TX_EN || TCFG_LEA_BIG_CTRLER_RX_EN)
    if (get_broadcast_role()) {
#else
    if (get_auracast_role()) {
#endif
        //固定为发送端
        if (linein_get_status()) {
            linein_stop();
            __this->linein_local_audio_resume_onoff = 1;
        } else {
            __this->linein_local_audio_resume_onoff = 0;
        }
        __this->last_run_local_audio_close = 1;
        return 0;
    }
#endif
#endif

    //作为非接收端的情况
    if (get_linein_play_status() == LOCAL_AUDIO_PLAYER_STATUS_PLAY) {
        //关闭本地播放
        linein_stop();
    }

    return 0;
}

static void *linein_tx_le_audio_open(void *args)
{
    struct le_audio_stream_params *params = (struct le_audio_stream_params *)args;
    void *le_audio = le_audio_stream_create(params->conn, &params->fmt);
    int err = le_audio_linein_recorder_open((void *)&params->fmt, le_audio, params->latency);
    if (err != 0) {
        ASSERT(0, "recorder open fail");
    }
#if TCFG_LEA_LOCAL_SYNC_PLAY_EN
    err = le_audio_player_open(le_audio, params);
    if (err != 0) {
        ASSERT(0, "player open fail");
    }
#endif
    __this->audio_state = APP_AUDIO_STATE_MUSIC;
    __this->volume = app_audio_get_volume(__this->audio_state);
    __this->onoff = 1;

#if (TCFG_LEA_BIG_CTRLER_TX_EN || TCFG_LEA_BIG_CTRLER_RX_EN) || \
    (TCFG_LE_AUDIO_APP_CONFIG & (LE_AUDIO_AURACAST_SOURCE_EN | LE_AUDIO_AURACAST_SINK_EN))
    update_le_audio_deal_scene(LE_AUDIO_MUSIC_START);
#endif

    return le_audio;
}

static int linein_tx_le_audio_close(void *le_audio)
{
    if (!le_audio) {
        return -EPERM;
    }

    //关闭广播音频播放
#if TCFG_LEA_LOCAL_SYNC_PLAY_EN
    le_audio_player_close(le_audio);
#endif
    le_audio_linein_recorder_close();
    le_audio_stream_free(le_audio);

    app_audio_set_volume(APP_AUDIO_STATE_MUSIC, __this->volume, 1);
    __this->onoff = 0;

#if (TCFG_LEA_BIG_CTRLER_TX_EN || TCFG_LEA_BIG_CTRLER_RX_EN) || \
    (TCFG_LE_AUDIO_APP_CONFIG & (LE_AUDIO_AURACAST_SOURCE_EN | LE_AUDIO_AURACAST_SINK_EN))
    update_le_audio_deal_scene(LE_AUDIO_MUSIC_STOP);
#endif

    return 0;
}

static int le_audio_linein_volume_pp(void)
{
    int ret;

    if (__this->onoff == 0) {
        __this->onoff = 1;
        ret = le_audio_scene_deal(LE_AUDIO_MUSIC_START);
#if (TCFG_LEA_BIG_FIX_ROLE==1)
        //固定为发送端，播歌中开广播点击pp键关广播(广播下最终的状态为暂停状态)，本地音频为暂停状态
        if (__this->linein_local_audio_resume_onoff == 0) {
            __this->linein_local_audio_resume_onoff = 1;
        }
#endif
    } else {
        __this->onoff = 0;
        ret = le_audio_scene_deal(LE_AUDIO_MUSIC_STOP);
#if (TCFG_LEA_BIG_FIX_ROLE==1)
        //固定为发送端，播歌中开广播点击pp键关广播(广播下最终的状态为暂停状态)，本地音频为暂停状态
        if (__this->linein_local_audio_resume_onoff) {
            __this->linein_local_audio_resume_onoff = 0;
        }
#endif
    }

    return ret;
}

const struct le_audio_mode_ops le_audio_linein_ops = {
    .local_audio_open = linein_local_audio_open,
    .local_audio_close = linein_local_audio_close,
    .tx_le_audio_open = linein_tx_le_audio_open,
    .tx_le_audio_close = linein_tx_le_audio_close,
    .rx_le_audio_open = default_rx_le_audio_open,
    .rx_le_audio_close = default_rx_le_audio_close,
    .play_status = get_linein_play_status,
};
#endif

static void linein_music_pp_handler(int need_resume)
{
    int ret = 0;

#if ((TCFG_LEA_BIG_CTRLER_TX_EN || TCFG_LEA_BIG_CTRLER_RX_EN) || \
    (TCFG_LE_AUDIO_APP_CONFIG & (LE_AUDIO_AURACAST_SOURCE_EN | LE_AUDIO_AURACAST_SINK_EN))) && (TCFG_LEA_BIG_FIX_ROLE==2)
    //固定为接收端
    u8 linein_volume_mute_mark = app_audio_get_mute_state(APP_AUDIO_STATE_MUSIC);
#if TCFG_LEA_BIG_CTRLER_TX_EN || TCFG_LEA_BIG_CTRLER_RX_EN
    if (get_broadcast_role() == 2) {
#else
    if (get_auracast_role() == 2) {
#endif
        //接收端已连上
        linein_volume_mute_mark ^= 1;
        audio_app_mute_en(linein_volume_mute_mark);
    } else {
        if (linein_volume_mute_mark == 1) {
            //没有连接情况下，如果之前是mute住了，那么先解mute
            linein_volume_mute_mark ^= 1;
            audio_app_mute_en(linein_volume_mute_mark);
            return 0;
        }
    }
#endif

#if (TCFG_LEA_BIG_CTRLER_TX_EN || TCFG_LEA_BIG_CTRLER_RX_EN) || \
    (TCFG_LEA_CIG_CENTRAL_EN || TCFG_LEA_CIG_PERIPHERAL_EN) || \
    (TCFG_LE_AUDIO_APP_CONFIG & (LE_AUDIO_AURACAST_SOURCE_EN | LE_AUDIO_AURACAST_SINK_EN))
#if (TCFG_LEA_BIG_CTRLER_TX_EN || TCFG_LEA_BIG_CTRLER_RX_EN)
    if (get_broadcast_role()) {
#elif (TCFG_LEA_CIG_CENTRAL_EN || TCFG_LEA_CIG_PERIPHERAL_EN)
    if ((app_get_connected_role() == APP_CONNECTED_ROLE_TRANSMITTER) ||
        (app_get_connected_role() == APP_CONNECTED_ROLE_DUPLEX)) {
#else
    if (get_auracast_role()) {
#endif
        ret = le_audio_linein_volume_pp();
    } else {
        __this->onoff ? update_le_audio_deal_scene(LE_AUDIO_MUSIC_STOP) : update_le_audio_deal_scene(LE_AUDIO_MUSIC_START);
    }
#endif

    if (ret <= 0) {
        linein_pp();
    }
    app_send_message(APP_MSG_LINEIN_PLAY_STATUS, __this->onoff);
    ai_app_local_event_notify(linein_get_status() ? FILE_PLAYER_START : (need_resume ? FILE_PLAYER_PAUSE : FILE_PLAYER_STOP));
}

static int linein_music_msg_handler(struct application *app, int *msg)
{
    switch (msg[0]) {
    case APP_MSG_SUSPEND:
        linein_music_app_suspend();
        break;
    case APP_MSG_RESUME:
        linein_music_app_resume();
        break;
    case APP_MSG_STOP:
        linein_music_app_stop();
        break;
    case APP_MSG_LINEIN_MUSIC_PLAY:
        log_info("play");
#if TCFG_LE_AUDIO_STREAM_ENABLE
        if (msg[1]) {
            le_audio_scene_deal(LE_AUDIO_APP_MODE_ENTER);
        }
#endif
        if (!__this->onoff) {
            linein_music_pp_handler(0);
        }
        break;
    case APP_MSG_LINEIN_MUSIC_PAUSE:
        log_info("pause");
        if (__this->onoff) {
            linein_music_pp_handler(0);
        }
        break;
    case APP_MSG_LINEIN_MUSIC_PP:
        log_info("pp");
        linein_music_pp_handler(0);
        break;
    case APP_MSG_LINEIN_MUSIC_PITCH_UP:
        log_info("pitch up");
        if (__this->player) {
            linein_file_pitch_up(__this->player);
        }
        break;
    case APP_MSG_LINEIN_MUSIC_PITCH_DOWN:
        log_info("pitch down");
        if (__this->player) {
            linein_file_pitch_down(__this->player);
        }
        break;
    default:
        break;
    }

    return 0;
}

static int linein_music_init(void)
{
#if TCFG_LE_AUDIO_STREAM_ENABLE
    le_audio_scene_deal(LE_AUDIO_APP_MODE_EXIT);
#endif

    tone_player_stop();

    int ret;
#if TCFG_LOCAL_TWS_ENABLE
    ret = local_tws_enter_mode(get_tone_files()->linein_mode, APP_MODE_LINEIN, NULL);
    if (ret)
#endif
    {
        ret = play_tone_file_callback(get_tone_files()->linein_mode, NULL, linein_tone_play_end_callback);
        if (ret) {
            linein_tone_play_end_callback(NULL, STREAM_EVENT_NONE); //提示音播放失败就直接调用
        }
    }

    /* app_send_message(APP_MSG_ENTER_MODE, APP_MODE_LINEIN); */

    return 0;
}

static void linein_music_exit(void)
{
#if TCFG_LOCAL_TWS_ENABLE
    local_tws_exit_mode();
#endif
    linein_stop();

    ai_app_local_event_notify(FILE_PLAYER_STOP);

#if TCFG_LE_AUDIO_STREAM_ENABLE
    le_audio_scene_deal(LE_AUDIO_APP_MODE_EXIT);
#endif
    /* app_send_message(APP_MSG_EXIT_MODE, APP_MODE_LINEIN); */
}

static int linein_music_key_click(struct key_event *key)
{
    int ret = FALSE;

    switch (key->value) {
    case KEY_OK:
        app_send_message(APP_MSG_LINEIN_MUSIC_PP, 0);
        break;
    case KEY_PLAY:
        app_send_message(APP_MSG_LINEIN_MUSIC_PLAY, 1, 0);
        break;
    case KEY_PAUSE:
        app_send_message(APP_MSG_LINEIN_MUSIC_PAUSE, 0);
        break;
    default:
        ret = FALSE;
        break;
    }

    return ret;
}

static int linein_music_key_long(struct key_event *key)
{
    int ret = TRUE;

    switch (key->value) {
    case KEY_VOLUME_DEC:
    case KEY_UP:
    case KEY_PREV:
        app_send_message(APP_MSG_LINEIN_MUSIC_PITCH_DOWN, 0);
        break;
    case KEY_VOLUME_INC:
    case KEY_DOWN:
    case KEY_NEXT:
        app_send_message(APP_MSG_LINEIN_MUSIC_PITCH_UP, 0);
        break;
    default:
        ret = FALSE;
        break;
    }

    return ret;
}

static int linein_music_key_hold(struct key_event *key)
{
    return FALSE;
}

static int linein_music_key_event_handler(struct key_event *key)
{
    int ret = FALSE;

    switch (key->action) {
    case KEY_EVENT_CLICK:
        ret = linein_music_key_click(key);
        break;
    case KEY_EVENT_LONG:
        ret = linein_music_key_long(key);
        break;
    case KEY_EVENT_HOLD:
        ret = linein_music_key_hold(key);
        break;
    default:
        break;
    }

    return ret;
}

static int linein_music_event_handler(struct application *app, struct sys_event *event)
{
    switch (event->type) {
    case SYS_KEY_EVENT:
        return linein_music_key_event_handler((struct key_event *)event->payload);
    default:
        return FALSE;
    }
}

static int linein_music_state_machine(struct application *app, enum app_state state,
                                      struct intent *it)
{
    switch (state) {
    case APP_STA_CREATE:
        linein_music_init();
        break;
    case APP_STA_START:
        break;
    case APP_STA_PAUSE:
        linein_music_app_suspend();
        break;
    case APP_STA_RESUME:
        linein_music_app_resume();
        break;
    case APP_STA_STOP:
        break;
    case APP_STA_DESTROY:
        linein_music_exit();
        break;
    case APP_STA_COMPLETE:
        break;
    }

    return 0;
}

static const struct application_operation linein_music_ops = {
    .state_machine  = linein_music_state_machine,
    .event_handler 	= linein_music_event_handler,
    .msg_handler 	= linein_music_msg_handler,
};

REGISTER_APPLICATION(linein_music) = {
    .name   = "linein_music",
    .ops    = &linein_music_ops,
    .state  = APP_STA_DESTROY,
};


//linein插入检测触发app切换动作
static int linein_detect_event_handler(void *evt)
{
    struct device_event *event = (struct device_event *)evt;

    if (event->event == DEVICE_EVENT_IN) {
        if (current_app_in_mode(APP_MODE_LINEIN) == FALSE) {
            os_taskq_del_type("app_core", MSG_FROM_APP);
            app_mode_change(APP_MODE_LINEIN);
        }
    } else {
        if (current_app_in_mode(APP_MODE_LINEIN) == TRUE) {
            os_taskq_del_type("app_core", MSG_FROM_APP);
            app_mode_go_back();
        }
    }

    return FALSE;
}

REGISTER_APP_EVENT_HANDLER(linein_detect_event) = {
    .event      = SYS_DEVICE_EVENT,
    .from       = DEVICE_EVENT_FROM_LINEIN,
    .handler    = linein_detect_event_handler,
};

#if TCFG_LOCAL_TWS_ENABLE
static void local_tws_linein_music_start(void *priv)
{
    app_send_message(APP_MSG_LINEIN_MUSIC_PLAY, 1, 1);
}

REGISTER_LOCAL_TWS_OPS(tws_linein_music) = {
    .mode = APP_MODE_LINEIN,
    .name = "linein_music",
    .audio_open = local_tws_linein_music_start,
    .get_play_status = linein_get_status,
};
#endif

#endif
