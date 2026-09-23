#include "system/includes.h"
#include "app_config.h"
#include "app_msg.h"
#include "music/music_player.h"
#include "music/breakpoint.h"
#include "app_tone.h"
#include "tone_player.h"
#include "audio_config.h"
#include "net_file_player.h"
#include "event/event.h"
#include "event/key_event.h"
#include "scene_switch.h"
#include "asm/crc16.h"
#include "effect/effects_default_param.h"
#if TCFG_LRC_LYRICS_ENABLE
#include "lyrics/lyrics_api.h"
#endif
#if TCFG_LOCAL_TWS_ENABLE
#include "local_tws.h"
#endif
#include "wireless_trans.h"
#if TCFG_LE_AUDIO_STREAM_ENABLE
#include "le_audio_recorder.h"
#include "app_le_broadcast.h"
#include "le_audio_player.h"
#endif

#if TCFG_APP_NET_MUSIC_EN

#define LOG_TAG             "[APP_NET_MUSIC]"
#define LOG_ERROR_ENABLE
#define LOG_DEBUG_ENABLE
#define LOG_INFO_ENABLE
/* #define LOG_DUMP_ENABLE */
#define LOG_CLI_ENABLE
#include "debug.h"


//切歌切模式是否保持倍速播放的状态
#define MUSIC_PLAYBACK_SPEED_KEEP            0

//切歌切模式是否保持变调的状态
#define MUSIC_PLAYBACK_PITCH_KEEP            0

typedef struct {
    void *ai_server;
    const char *ai_name;
    const char *tts_ai_name;
    const char *url;
    breakpoint_t *breakpoint;
    struct net_file_player *player;
    void *lrc_info;
    speed_level_t speed_mode;
    pitch_level_t pitch_mode;
    u32 play_time;
#if TCFG_LE_AUDIO_STREAM_ENABLE
    void *le_audio;
    struct stream_enc_fmt enc_fmt;
#endif

    u8 listening;
    u8 ai_connected : 1;
    u8 wechat_flag : 1;
    u8 suspend_flag : 1;
    u8 music_net_audio_resume_onoff : 1;
} net_music_t;

static net_music_t net_music_hdl = {
    .speed_mode = PLAY_SPEED_1,
    .pitch_mode = PITCH_0,
};

#define __this (&net_music_hdl)


#include "ai.c"


int get_app_music_playtime(void)
{
    int play_time = net_file_get_cur_time(__this->player);
    if (play_time < 0) {
        return __this->play_time;
    }

    __this->play_time = play_time;

    return play_time;
}

int get_app_music_total_time(void)
{
    return net_file_get_total_time(__this->player);
}

int get_app_music_volume(void)
{
    return app_audio_get_volume(APP_AUDIO_STATE_MUSIC);
}

static int net_music_msg_handler(struct application *app, int *msg);

//*---------------------------------------------------------------------------*/
/**@brief    提示音结束处理
*/
/*----------------------------------------------------------------------------*/
static int music_tone_play_end_callback(void *priv, enum stream_event event)
{
    switch (event) {
    case STREAM_EVENT_NONE:
    case STREAM_EVENT_STOP:
        ///提示音播放结束，启动播放器播放
        app_send_message(APP_MSG_NET_MUSIC_PLAY_START, 1, 0);
        break;
    default:
        break;
    }

    return 0;
}

static void net_music_player_save_breakpoint(void)
{
    if (__this->player && __this->url) {
        if (net_file_get_breakpoints(&__this->breakpoint->dbp, __this->player) == 0) {
            /* breakpoint_vm_write(__this->breakpoint, "net"); */
        }
    }
}

static void __net_music_player_play_stop(void)
{
    if (__this->player) {
#if (defined(TCFG_LRC_LYRICS_ENABLE) && (TCFG_LRC_LYRICS_ENABLE))
        lrc_set_analysis_flag(__this->lrc_info, 0);
#endif
        net_file_player_stop(__this->player);
        __this->player = NULL;
    }
}

static void net_music_player_play_stop(void)
{
    __net_music_player_play_stop();
#if TCFG_LE_AUDIO_STREAM_ENABLE
    /* le_audio_scene_deal(LE_AUDIO_MUSIC_STOP); */
#endif
    __this->suspend_flag = 0;
}

static int net_music_player_decode_event_callback(void *priv, int parm, enum stream_event event)
{
    switch (event) {
    case STREAM_EVENT_START:
        break;
    case STREAM_EVENT_STOP:
        app_send_message(APP_MSG_NET_MUSIC_PLAY_STOP, 0);
        break;
    case STREAM_EVENT_END:
        app_send_message(APP_MSG_NET_MUSIC_PLAY_END, 0);
        break;
    default:
        break;
    }

    return 0;
}

static int net_music_play_by_url(const char *url)
{
    struct audio_dec_breakpoint *dbp = &__this->breakpoint->dbp;

    if (!__this->url && !url) {
        return -1;
    }

    net_music_player_play_stop();

    if (__this->url && url && strcmp(__this->url, url)) {
        //重置断点数据
        __this->breakpoint->dbp.len = 0;
        __this->breakpoint->dbp.fptr = 0;
    }

#if TCFG_LE_AUDIO_STREAM_ENABLE
    le_audio_scene_deal(LE_AUDIO_MUSIC_START);
#endif

    if (url) {
#if TCFG_LE_AUDIO_STREAM_ENABLE
        if (__this->le_audio) {
            __this->player = le_audio_net_file_play_callback(url, NULL, net_music_player_decode_event_callback, dbp, __this->le_audio, &__this->enc_fmt);
        } else
#endif
        {
            __this->player = net_file_play_callback(url, NULL, net_music_player_decode_event_callback, dbp);
        }
        if (!__this->player) {
            free((void *)url);
            return -1;
        }
        free((void *)__this->url);
        __this->url = url;
    } else {
#if TCFG_LE_AUDIO_STREAM_ENABLE
        if (__this->le_audio) {
            __this->player = le_audio_net_file_play_callback(url, NULL, net_music_player_decode_event_callback, dbp, __this->le_audio, &__this->enc_fmt);
        } else
#endif
        {
            __this->player = net_file_play_callback(__this->url, NULL, net_music_player_decode_event_callback, dbp);
        }
        if (!__this->player) {
            return -1;
        }
        /* if (TRUE == breakpoint_vm_read(__this->breakpoint, "net")) { */
        /* err = music_player_play_by_breakpoint(__this->player_hd, logo, __this->breakpoint); */
        /* } */
    }

    return 0;
}

static void net_music_player_play_pause(int notify)
{
    int ret = 0;

#if (TCFG_LEA_BIG_CTRLER_TX_EN || TCFG_LEA_BIG_CTRLER_RX_EN) || \
    (TCFG_LE_AUDIO_APP_CONFIG & (LE_AUDIO_AURACAST_SOURCE_EN | LE_AUDIO_JL_AURACAST_SOURCE_EN)) || \
    (TCFG_LE_AUDIO_APP_CONFIG & (LE_AUDIO_AURACAST_SINK_EN | LE_AUDIO_JL_AURACAST_SINK_EN))
#if (TCFG_LEA_BIG_FIX_ROLE==2)
    //固定为接收端
    u8 music_volume_mute_mark = app_audio_get_mute_state(APP_AUDIO_STATE_MUSIC);
    if (get_broadcast_role() == BROADCAST_ROLE_RECEIVER || music_volume_mute_mark == 1) {
        //接收端已连上
        music_volume_mute_mark ^= 1;
        audio_app_mute_en(music_volume_mute_mark);
        return;
    }
#endif
#endif

    if (__this->player) {
        net_file_player_pp(__this->player);
        if (notify) {
            ai_app_event_notify_value(AI_EVENT_PLAY_PAUSE, net_file_get_player_status(__this->player) == FILE_PLAYER_START ? 0 : 1);
        }
        if (strcmp(__this->ai_name, __this->tts_ai_name)) {
            main_ai_app_event_notify_value(AI_EVENT_LOCAL_PP, net_file_get_player_status(__this->player) == FILE_PLAYER_START ? 0 : 2);
        }
#if TCFG_LE_AUDIO_STREAM_ENABLE
        le_audio_scene_deal(net_file_get_player_status(__this->player) == FILE_PLAYER_START ? LE_AUDIO_MUSIC_START : LE_AUDIO_MUSIC_STOP);
#endif
        app_send_message(APP_MSG_NET_MUSIC_PLAY_STATUS, 1, net_file_get_player_status(__this->player));
    } else if (__this->url) {
#if TCFG_LE_AUDIO_STREAM_ENABLE
        __this->music_net_audio_resume_onoff = 1;
        ret = le_audio_scene_deal(LE_AUDIO_MUSIC_START);
        __this->music_net_audio_resume_onoff = 0;
        if (ret) {
            if (notify) {
                ai_app_event_notify_value(AI_EVENT_PLAY_PAUSE, FILE_PLAYER_START);
            }
            if (strcmp(__this->ai_name, __this->tts_ai_name)) {
                main_ai_app_event_notify_value(AI_EVENT_LOCAL_PP, 0);
            }
            app_send_message(APP_MSG_NET_MUSIC_PLAY_STATUS, 1, FILE_PLAYER_START);
        }
#endif
        if (!ret && 0 == net_music_play_by_url(NULL)) {
            app_send_message(APP_MSG_NET_MUSIC_PLAY_STATUS, 1, FILE_PLAYER_START);
        }
    }
}

static void net_music_player_play_success(void *priv, int parm)
{
#if MUSIC_PLAYBACK_SPEED_KEEP
    net_file_set_speed(net_file_player, __this->speed_mode); //设置播放速度
#endif

#if MUSIC_PLAYBACK_PITCH_KEEP
    struct net_file_player *net_file_player = get_music_file_player();
    net_file_set_pitch(net_file_player, __this->pitch_mode);
#endif

#if TCFG_VOCAL_REMOVER_NODE_ENABLE
    musci_vocal_remover_update_parm();
#endif
}

static int net_music_init(void)
{
    int ret;

#if TCFG_LRC_LYRICS_ENABLE
    if (!__this->lrc_info) {
        __this->lrc_info = lyric_init();
    }
#endif

    __this->breakpoint = breakpoint_handle_creat(); //获取断点句柄， 后面所有断点读/写都需要用到

#if TCFG_LOCAL_TWS_ENABLE
    ret = local_tws_enter_mode(get_tone_files()->net_mode, APP_MODE_NET, NULL);
    if (ret)
#endif
    {
        tone_player_stop(); //停止播放当前提示音并清空播放队列
        //播放单个提示音文件，支持播放事件回调
        ret = play_tone_file_callback(get_tone_files()->net_mode, NULL, music_tone_play_end_callback);
        if (ret) {
            music_tone_play_end_callback(NULL, STREAM_EVENT_NONE);  //提示音结束处理
            ///该行代码传递参数-》提示音播放结束， 启动播放器播放-music_player_play_start();
        }
    }

    /* app_send_message(APP_MSG_ENTER_MODE, APP_MODE_NET_MUSIC); */

    return 0;
}

static int net_music_exit(void)
{
    net_music_player_play_stop();

    breakpoint_handle_destroy(&__this->breakpoint);

#if TCFG_LRC_LYRICS_ENABLE
    if (__this->lrc_info) {
        lyric_exit(__this->lrc_info);
        __this->lrc_info = NULL;
    }
#endif

    /* app_send_message(APP_MSG_EXIT_MODE, APP_MODE_NET_MUSIC); */

    return 0;
}

static void net_music_player_err_deal(int err)
{

}

static void net_music_app_suspend(void)
{
    if (__this->player && __this->url) {
        __this->suspend_flag = 1;

#if (TCFG_LEA_BIG_CTRLER_TX_EN || TCFG_LEA_BIG_CTRLER_RX_EN) || \
    (TCFG_LE_AUDIO_APP_CONFIG & (LE_AUDIO_AURACAST_SOURCE_EN | LE_AUDIO_JL_AURACAST_SOURCE_EN)) || \
    (TCFG_LE_AUDIO_APP_CONFIG & (LE_AUDIO_AURACAST_SINK_EN | LE_AUDIO_JL_AURACAST_SINK_EN))
#if (TCFG_LEA_BIG_FIX_ROLE==2)
        //固定为接收端
        u8 music_volume_mute_mark = app_audio_get_mute_state(APP_AUDIO_STATE_MUSIC);
        if (get_broadcast_role() == BROADCAST_ROLE_RECEIVER || music_volume_mute_mark == 1) {
            //接收端已连上
            music_volume_mute_mark ^= 1;
            audio_app_mute_en(music_volume_mute_mark);
            return;
        }
#endif
#endif

        if (net_file_get_player_status(__this->player) == FILE_PLAYER_START) {
            net_file_player_pp(__this->player);
            if (strcmp(__this->ai_name, __this->tts_ai_name)) {
                ai_app_event_notify_value(AI_EVENT_PLAY_PAUSE, 1);
                main_ai_app_event_notify_value(AI_EVENT_LOCAL_PP, 1);
            }
#if TCFG_LE_AUDIO_STREAM_ENABLE
            le_audio_scene_deal(net_file_get_player_status(__this->player) == FILE_PLAYER_START ? LE_AUDIO_MUSIC_START : LE_AUDIO_MUSIC_STOP);
#endif
            app_send_message(APP_MSG_NET_MUSIC_PLAY_STATUS, 1, net_file_get_player_status(__this->player));
        }
    }
}

static void net_music_app_resume(void)
{
    if (!__this->suspend_flag) {
        return;
    }

#if (TCFG_LEA_BIG_CTRLER_TX_EN || TCFG_LEA_BIG_CTRLER_RX_EN) || \
    (TCFG_LE_AUDIO_APP_CONFIG & (LE_AUDIO_AURACAST_SOURCE_EN | LE_AUDIO_JL_AURACAST_SOURCE_EN)) || \
    (TCFG_LE_AUDIO_APP_CONFIG & (LE_AUDIO_AURACAST_SINK_EN | LE_AUDIO_JL_AURACAST_SINK_EN))
#if (TCFG_LEA_BIG_FIX_ROLE==2)
    //固定为接收端
    u8 music_volume_mute_mark = app_audio_get_mute_state(APP_AUDIO_STATE_MUSIC);
    if (get_broadcast_role() == BROADCAST_ROLE_RECEIVER || music_volume_mute_mark == 1) {
        //接收端已连上
        music_volume_mute_mark ^= 1;
        audio_app_mute_en(music_volume_mute_mark);
        __this->suspend_flag = 0;
        return;
    }
#endif
#endif

    if (__this->player && __this->url) {
        if (net_file_get_player_status(__this->player) != FILE_PLAYER_START) {
            net_file_player_pp(__this->player);
            if (strcmp(__this->ai_name, __this->tts_ai_name)) {
                ai_app_event_notify_value(AI_EVENT_PLAY_PAUSE, 0);
                main_ai_app_event_notify_value(AI_EVENT_LOCAL_PP, 0);
            }
            app_send_message(APP_MSG_NET_MUSIC_PLAY_STATUS, 1, net_file_get_player_status(__this->player));
        }
    }
#if TCFG_LE_AUDIO_STREAM_ENABLE
    else if (__this->url) {
        __this->music_net_audio_resume_onoff = 1;
        int ret = le_audio_scene_deal(LE_AUDIO_MUSIC_START);
        __this->music_net_audio_resume_onoff = 0;
        if (ret) {
            if (strcmp(__this->ai_name, __this->tts_ai_name)) {
                ai_app_event_notify_value(AI_EVENT_PLAY_PAUSE, 0);
                main_ai_app_event_notify_value(AI_EVENT_LOCAL_PP, 0);
            }
            app_send_message(APP_MSG_NET_MUSIC_PLAY_STATUS, 1, FILE_PLAYER_START);
        }
    }
#endif

    __this->suspend_flag = 0;
}

static void net_music_app_stop(void)
{
    tts_player_stop();
    net_music_player_play_stop();
}

#if (TCFG_LEA_BIG_CTRLER_TX_EN || TCFG_LEA_BIG_CTRLER_RX_EN || TCFG_LEA_CIG_CENTRAL_EN || TCFG_LEA_CIG_PERIPHERAL_EN) || \
    (TCFG_LE_AUDIO_APP_CONFIG & (LE_AUDIO_AURACAST_SOURCE_EN | LE_AUDIO_JL_AURACAST_SOURCE_EN)) || \
    (TCFG_LE_AUDIO_APP_CONFIG & (LE_AUDIO_AURACAST_SINK_EN | LE_AUDIO_JL_AURACAST_SINK_EN)) || \
    (TCFG_LE_AUDIO_APP_CONFIG & (LE_AUDIO_UNICAST_SOURCE_EN | LE_AUDIO_JL_UNICAST_SOURCE_EN)) || \
    (TCFG_LE_AUDIO_APP_CONFIG & (LE_AUDIO_UNICAST_SINK_EN | LE_AUDIO_JL_UNICAST_SINK_EN))

static int get_net_music_play_status(void)
{
    if (get_le_audio_app_mode_exit_flag()) {
        return LOCAL_AUDIO_PLAYER_STATUS_STOP;
    }

#if (TCFG_LEA_BIG_CTRLER_TX_EN || TCFG_LEA_BIG_CTRLER_RX_EN) || \
    (TCFG_LE_AUDIO_APP_CONFIG & (LE_AUDIO_AURACAST_SOURCE_EN | LE_AUDIO_JL_AURACAST_SOURCE_EN)) || \
    (TCFG_LE_AUDIO_APP_CONFIG & (LE_AUDIO_AURACAST_SINK_EN | LE_AUDIO_JL_AURACAST_SINK_EN))
    if (__this->music_net_audio_resume_onoff) {
        return LOCAL_AUDIO_PLAYER_STATUS_PLAY;
    }
#endif

    if (net_file_get_player_status(get_net_file_player()) == FILE_PLAYER_START) {
        return LOCAL_AUDIO_PLAYER_STATUS_PLAY;
    } else {
        return LOCAL_AUDIO_PLAYER_STATUS_STOP;
    }
}

static int net_music_local_audio_open(void)
{
    if (__this->player) {
        return 0;
    }

    /* breakpoint_vm_read(__this->breakpoint, "net"); */
    if (__this->url) {
        __this->player = net_file_play_callback(__this->url, NULL, net_music_player_decode_event_callback, &__this->breakpoint->dbp);
    }

    if (!__this->player) {
        return -1;
    }

    return 0;
}

static int net_music_local_audio_close(void)
{
    struct net_file_player *player = get_net_file_player();

    __net_music_player_play_stop();

    return 0;
}

static void *net_music_tx_le_audio_open(void *fmt)
{
    //打开广播音频播放
    struct le_audio_stream_params *params = (struct le_audio_stream_params *)fmt;
    struct le_audio_stream_format stream_fmt = params->fmt;
    void *le_audio = le_audio_stream_create(params->conn, &params->fmt);

    __this->le_audio = le_audio;
    __this->enc_fmt.coding_type = stream_fmt.coding_type;
    __this->enc_fmt.channel = stream_fmt.nch;
    __this->enc_fmt.bit_rate = stream_fmt.bit_rate;
    __this->enc_fmt.sample_rate = stream_fmt.sample_rate;
    __this->enc_fmt.frame_dms = stream_fmt.frame_dms;

    if (__this->url) {
        __this->player = le_audio_net_file_play_callback(__this->url, NULL, net_music_player_decode_event_callback, &__this->breakpoint->dbp, le_audio, &__this->enc_fmt);
    }

    return le_audio;
}

static int net_music_tx_le_audio_close(void *le_audio)
{
    if (!le_audio) {
        return -EPERM;
    }

    __this->le_audio = NULL;

    __net_music_player_play_stop();

    //关闭广播音频播放
#if TCFG_LEA_LOCAL_SYNC_PLAY_EN
    le_audio_player_close(le_audio);
#endif
    le_audio_stream_free(le_audio);

    return 0;
}

const struct le_audio_mode_ops le_audio_net_music_ops = {
    .local_audio_open   = net_music_local_audio_open,
    .local_audio_close  = net_music_local_audio_close,
    .tx_le_audio_open   = net_music_tx_le_audio_open,
    .tx_le_audio_close  = net_music_tx_le_audio_close,
    .rx_le_audio_open   = default_rx_le_audio_open,
    .rx_le_audio_close  = default_rx_le_audio_close,
    .play_status        = get_net_music_play_status,
};
#endif

static int net_music_msg_handler(struct application *app, int *msg)
{
    struct net_file_player *net_file_player = get_net_file_player();
    int err = MUSIC_PLAYER_ERR_NULL;

    switch (msg[0]) {
    case APP_MSG_SUSPEND:
        net_music_app_suspend();
        break;
    case APP_MSG_RESUME:
        net_music_app_resume();
        break;
    case APP_MSG_STOP:
        net_music_app_stop();
        break;
    case APP_MSG_NET_MUSIC_PP:
        log_info("pp");
        net_music_player_play_pause(msg[1]);
        break;
    case APP_MSG_NET_MUSIC_PLAY:
        log_info("play");
        if (net_file_get_player_status(net_file_player) != FILE_PLAYER_START) {
            net_music_player_play_pause(msg[1]);
        }
        break;
    case APP_MSG_NET_MUSIC_PAUSE:
        log_info("pause");
        if (net_file_get_player_status(net_file_player) == FILE_PLAYER_START) {
            net_music_player_play_pause(msg[1]);
        }
        break;
    case APP_MSG_NET_MUSIC_VOL_SET:
        app_audio_set_volume(APP_AUDIO_STATE_MUSIC, msg[1], 1);
        break;
    case APP_MSG_NET_MUSIC_VOL_CHANGED:
        ai_app_event_notify_value(AI_EVENT_VOLUME_CHANGE, app_audio_get_volume(APP_AUDIO_STATE_MUSIC));
        break;
    case APP_MSG_NET_MUSIC_SPEED_UP:
        log_info("speed up");
        __this->speed_mode = net_file_speed_up(net_file_player);
        break;
    case APP_MSG_NET_MUSIC_SPEED_DOWN:
        log_info("speed down");
        __this->speed_mode = net_file_speed_down(net_file_player);
        break;
    case APP_MSG_NET_MUSIC_PITCH_UP:
        log_info("pitch up");
        __this->pitch_mode = net_file_pitch_up(net_file_player);
        break;
    case APP_MSG_NET_MUSIC_PITCH_DOWN:
        log_info("pitch down");
        __this->pitch_mode = net_file_pitch_down(net_file_player);
        break;
    case APP_MSG_NET_MUSIC_PLAYER_AB_REPEAT_SWITCH:
        log_info("ab repeat switch");
#if FILE_DEC_AB_REPEAT_EN
        net_file_ab_repeat_switch(net_file_player);
#endif
        break;
    case APP_MSG_NET_MUSIC_NEXT:
        log_info("play next");
        ai_app_event_notify(AI_EVENT_NEXT_SONG);
        break;
    case APP_MSG_NET_MUSIC_PREV:
        log_info("play prev");
        ai_app_event_notify(AI_EVENT_PREVIOUS_SONG);
        break;
    case APP_MSG_NET_MUSIC_PLAY_START:
        log_info("play start");
        err = net_music_play_by_url((const char *)msg[1]);
        break;
    case APP_MSG_NET_MUSIC_PLAY_END:
        log_info("play end");
        ai_app_event_notify(AI_EVENT_MEDIA_END);
        if (strcmp(__this->ai_name, __this->tts_ai_name)) {
            main_ai_app_event_notify_value(AI_EVENT_MEDIA_STOP, 1);
        }
        break;
    case APP_MSG_NET_MUSIC_PLAY_STOP:
        log_info("play stop");
        net_music_player_save_breakpoint();
        net_music_player_play_stop();
        break;
    case APP_MSG_NET_MUSIC_FR:
        log_info("play fr");
        net_file_player_fr(3, net_file_player);
        break;
    case APP_MSG_NET_MUSIC_FF:
        log_info("play ff");
        net_file_player_ff(3, net_file_player);
        break;
    case APP_MSG_NET_MUSIC_PLAY_START_AT_DEST_TIME:
#if FILE_DEC_DEST_PLAY
        if (net_player_runing()) {
            //for test 测试MP3定点播放功能
            log_info("play start at %dms", msg[1]);
            net_file_dec_set_start_play(msg[1], AUDIO_CODING_MP3);
        }
#endif
        break;
    case APP_MSG_NET_MUSIC_DEC_ERR:
        //TODO
        break;
    default:
        break;
    }

    net_music_player_err_deal(err);

    return 0;
}

static int net_music_key_click(struct key_event *key)
{
    int ret = FALSE;

    switch (key->value) {
    case KEY_OK:
        app_send_message(APP_MSG_NET_MUSIC_PP, 1, 1);
        break;
    case KEY_PLAY:
        app_send_message(APP_MSG_NET_MUSIC_PLAY, 1, 1);
        break;
    case KEY_PAUSE:
        app_send_message(APP_MSG_NET_MUSIC_PAUSE, 1, 1);
        break;
    case KEY_VOLUME_DEC:
    case KEY_UP:
    case KEY_PREV:
    case KEY_VOLUME_INC:
    case KEY_DOWN:
    case KEY_NEXT:
        app_send_message(APP_MSG_NET_MUSIC_VOL_CHANGED, 0);
        break;
    default:
        break;
    }

    return ret;
}

static int net_music_key_long(struct key_event *key)
{
    int ret = FALSE;
    int msg = APP_MSG_NET_MUSIC_PLAY_STOP;

    switch (key->value) {
    case KEY_VOLUME_DEC:
    case KEY_UP:
    case KEY_PREV:
        app_send_message(APP_MSG_NET_MUSIC_PREV, 0);
        break;
    case KEY_VOLUME_INC:
    case KEY_DOWN:
    case KEY_NEXT:
        app_send_message(APP_MSG_NET_MUSIC_NEXT, 0);
        break;
    case KEY_MODE:
        //此处需要马上停止解码器，不用队列消息传递
        msg = APP_MSG_NET_MUSIC_PLAY_STOP;
        net_music_msg_handler(get_current_app(), &msg);
        break;
    default:
        break;
    }

    return ret;
}

static int net_music_key_hold(struct key_event *key)
{
    return FALSE;
}

static int net_music_key_event_handler(struct key_event *key)
{
    int ret = FALSE;

    switch (key->action) {
    case KEY_EVENT_CLICK:
        ret = net_music_key_click(key);
        break;
    case KEY_EVENT_LONG:
        ret = net_music_key_long(key);
        break;
    case KEY_EVENT_HOLD:
        ret = net_music_key_hold(key);
        break;
    default:
        break;
    }

    return ret;
}

static int net_music_event_handler(struct application *app, struct sys_event *event)
{
    switch (event->type) {
    case SYS_KEY_EVENT:
        return net_music_key_event_handler((struct key_event *)event->payload);
    default:
        return FALSE;
    }
}

static int net_music_state_machine(struct application *app, enum app_state state,
                                   struct intent *it)
{
    switch (state) {
    case APP_STA_CREATE:
        net_music_init();
        break;
    case APP_STA_START:
        break;
    case APP_STA_PAUSE:
        net_music_app_suspend();
        break;
    case APP_STA_RESUME:
#if TCFG_LE_AUDIO_STREAM_ENABLE
        le_audio_scene_deal(LE_AUDIO_APP_MODE_EXIT);    //退出上一个模式
#endif
#if TCFG_LOCAL_TWS_ENABLE
        local_tws_enter_mode(NULL, APP_MODE_NET, NULL);
#endif
        net_music_app_resume();
        break;
    case APP_STA_STOP:
        break;
    case APP_STA_DESTROY:
        net_music_exit();
        break;
    case APP_STA_COMPLETE:
#if TCFG_LE_AUDIO_STREAM_ENABLE
        le_audio_scene_deal(LE_AUDIO_APP_MODE_ENTER);
#endif
        break;
    }

    return 0;
}

static const struct application_operation net_music_ops = {
    .state_machine  = net_music_state_machine,
    .event_handler 	= net_music_event_handler,
    .msg_handler 	= net_music_msg_handler,
};

REGISTER_APPLICATION(net_music) = {
    .name   = "net_music",
    .ops    = &net_music_ops,
    .state  = APP_STA_DESTROY,
};

#endif
