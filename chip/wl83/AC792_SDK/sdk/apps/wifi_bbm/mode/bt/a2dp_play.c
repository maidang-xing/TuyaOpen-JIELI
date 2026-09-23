#include "btstack/avctp_user.h"
#include "btstack/btstack_task.h"
#include "classic/tws_api.h"
#include "os/os_api.h"
#include "bt_slience_detect.h"
#include "a2dp_player.h"
#include "esco_player.h"
#include "vol_sync.h"
#include "audio_config.h"
#include "btstack/a2dp_media_codec.h"
#include "scene_switch.h"
#include "effect/effects_default_param.h"
#include "app_msg.h"
#include "app_config.h"
#if TCFG_LE_AUDIO_STREAM_ENABLE
#include "le_audio_recorder.h"
#include "app_le_broadcast.h"
#include "le_audio_player.h"
#endif
#include "wireless_trans.h"


#if TCFG_APP_BT_EN && !TCFG_USER_TWS_ENABLE

//开关a2dp后，是否保持变调状态
#define A2DP_PLAYBACK_PITCH_KEEP          0

enum {
    CMD_A2DP_PLAY = 1,
    CMD_A2DP_SLIENCE_DETECT,
    CMD_A2DP_CLOSE,
    CMD_SET_A2DP_VOL,
    CMD_A2DP_SWITCH,
    CMD_A2DP_MUTE,
    CMD_A2DP_MUTE_BY_CALL,
};

static u8 g_play_addr[6];
static u8 g_slience_addr[6];
static u8 g_closing_addr[6];
static u8 a2dp_preempted_addr[6];
static u8 a2dp_energy_detect_addr[6];
static u8 a2dp_drop_packet_detect_addr[6];
static u8 g_a2dp_slience_detect;
static u32 g_a2dp_slience_time;
static u32 g_a2dp_play_time;
#if TCFG_A2DP_PREEMPTED_ENABLE
u8 a2dp_avrcp_play_cmd_addr[6];
#endif

static u8 *get_g_play_addr(void)
{
    return g_play_addr;
}

static void a2dp_play_close(u8 *bt_addr)
{
    log_info("a2dp_play_close");
    /* put_buf(bt_addr, 6); */
    rf_coexistence_scene_exit(RF_COEXISTENCE_SCENE_A2DP_PLAY);
    a2dp_player_close(bt_addr);
    bt_stop_a2dp_slience_detect(bt_addr);
    a2dp_media_unmute(bt_addr);
    a2dp_media_close(bt_addr);
}

static bool bt_not_in_phone_call_state(void *device)
{
    if (!device) {
        return TRUE;
    }
    int state = btstack_bt_get_call_status(device);
    if (state == BT_CALL_HANGUP) {
        return TRUE;
    }
    if (state == BT_SIRI_STATE &&
        btstack_get_call_esco_status(device) == BT_ESCO_STATUS_CLOSE) {
        return TRUE;
    }
    return FALSE;
}

void a2dp_energy_detect_handler(int *arg)
{
    int energy = arg[0];
    int time = arg[1];  // msec * 10

    g_a2dp_play_time += time;

    /*
     * 恢复被通话打断的a2dp,前面100ms做能量检测, 如果没有能量可能是播放器已暂停,
     * 需要发送播放命令
     */
    if (a2dp_player_is_playing(a2dp_energy_detect_addr)) {
        if (energy < 10) {
            g_a2dp_slience_time += time;
        } else {
            g_a2dp_slience_time = 0;
        }
        if (g_a2dp_slience_time >= 1000) {
            int msg[2];
            memcpy(msg, a2dp_energy_detect_addr, 6);
            memset(a2dp_energy_detect_addr, 0xff, 6);
            app_send_message(APP_MSG_BT_SEND_A2DP_PLAY_CMD, 2, msg[0], msg[1]);
        } else if (g_a2dp_play_time >= 1000) {
            memset(a2dp_energy_detect_addr, 0xff, 6);
        }
    }
#if !TCFG_A2DP_PREEMPTED_ENABLE
    if (bt_a2dp_slience_detect_num() < 1) {
        // 无后台待播放设备
        return;
    }
#endif
    if (g_a2dp_slience_detect == 0 && g_a2dp_play_time >= 10000) {
        /* 播放1s后开启静音检测 */
        g_a2dp_slience_detect = 1;
        g_a2dp_slience_time = 0;
    }

    if (energy < 10) {
        if (g_a2dp_slience_detect == 1) {
            g_a2dp_slience_time += time;
            if (g_a2dp_slience_time >= 50000) {
                /* 静音超过5s, 切换到后台静音设备播放,
                 * 时间设置过短容易导致切歌过程中切换到后台设备播放
                 * */
                int msg[2];
                a2dp_player_get_btaddr((u8 *)msg);
                app_send_message(APP_MSG_BT_A2DP_NO_ENERGY, 2, msg[0], msg[1]);
                g_a2dp_slience_detect = 2;
            }
        }
    } else {
        if (g_a2dp_slience_detect == 1) {
            g_a2dp_slience_time = 0;
        }
    }
}

static void a2dp_play_send_cmd(u8 cmd, u8 *data, u8 len)
{
    u8 btaddr[6];
    u8 dev_vol;
    u8 *bt_addr = data;

    switch (cmd) {
    case CMD_A2DP_SLIENCE_DETECT:
        log_info("CMD_A2DP_SLIENCT_DETECE");
        le_audio_scene_deal(LE_AUDIO_A2DP_STOP);
        /* put_buf(bt_addr, 6); */
        a2dp_player_close(bt_addr);
        bt_start_a2dp_slience_detect(bt_addr, 50);    //丢掉50包(约1s)之后才开始能量检测,过滤掉提示音，避免提示音引起抢占
        memset(g_slience_addr, 0xff, 6);
        break;
    case CMD_A2DP_MUTE:
        log_info("CMD_A2DP_MUTE");
        /* put_buf(bt_addr, 6); */
        a2dp_player_close(bt_addr);
        memset(g_slience_addr, 0xff, 6);
        a2dp_media_mute(bt_addr);
        bt_start_a2dp_slience_detect(bt_addr, 0);
        break;
    case CMD_A2DP_MUTE_BY_CALL:
        log_info("CMD_A2DP_MUTE_BY_CALL");
        /* put_buf(bt_addr, 6); */
        a2dp_player_close(bt_addr);
        a2dp_media_mute(bt_addr);
        if (!bt_slience_get_detect_addr(bt_addr)) {
            bt_start_a2dp_slience_detect(bt_addr, 0);
        }
        memcpy(a2dp_preempted_addr, bt_addr, 6);
        memset(a2dp_energy_detect_addr, 0xff, 6);
        break;
    case CMD_A2DP_PLAY:
        log_info("CMD_A2DP_PLAY : %d", data[6]);
        /* put_buf(bt_addr, 6); */
        dev_vol = data[6];
        //更新一下音量再开始播放
        app_audio_state_switch(APP_AUDIO_STATE_MUSIC, app_audio_volume_max_query(AppVol_BT_MUSIC), NULL);
        //更新一下音量再开始播放
        if (dev_vol > 127) {    //返回值0xff说明不支持音量同步
            log_info("device no support sync vol, use sys volume:%d", app_audio_get_volume(APP_AUDIO_STATE_MUSIC));
            app_audio_set_volume(APP_AUDIO_STATE_MUSIC, app_audio_get_volume(APP_AUDIO_STATE_MUSIC), 1);
            app_audio_set_volume_def_state(0);
        } else if (!__this->vol_sync_timer) {
            bt_set_music_device_volume(dev_vol);
        }

        a2dp_media_unmute(bt_addr);
        bt_stop_a2dp_slience_detect(bt_addr);

        a2dp_player_low_latency_enable(a2dp_file_get_low_latency_status());

        rf_coexistence_scene_enter(RF_COEXISTENCE_SCENE_A2DP_PLAY, -1);

        if (memcmp(a2dp_preempted_addr, bt_addr, 6) == 0) {
            memset(a2dp_preempted_addr, 0xff, 6);
        }
        if (memcmp(a2dp_drop_packet_detect_addr, bt_addr, 6) == 0) {
            memset(a2dp_drop_packet_detect_addr, 0xff, 6);
        }

        memcpy(g_play_addr, bt_addr, 6);
        if (le_audio_scene_deal(LE_AUDIO_A2DP_START) > 0) {
            break;
        }
        if (a2dp_player_open(bt_addr) == -EBUSY) {
            bt_start_a2dp_slience_detect(bt_addr, 50); //丢掉50包(约1s)之后才开始能量检测,过滤掉提示音，避免提示音引起抢占
        }
        /* memset(g_play_addr, 0xff, 6); */

#if TCFG_VOCAL_REMOVER_NODE_ENABLE
        musci_vocal_remover_update_parm();
#endif
        break;
    case CMD_A2DP_CLOSE:
        log_info("CMD_A2DP_CLOSE");
#if TCFG_LE_AUDIO_STREAM_ENABLE
        //当前正在进行广播的设备地址跟蓝牙音频暂停地址一致时才处理（1T2逻辑）
        if (le_audio_scene_deal(LE_AUDIO_A2DP_STOP) > 0) {
            /* memset(g_play_addr, 0xff, 6); */
            a2dp_media_unmute(bt_addr);
            a2dp_media_close(bt_addr);
            break;
        }
#endif
        a2dp_play_close(bt_addr);
        if (bt_slience_get_detect_addr(btaddr)) {
            bt_stop_a2dp_slience_detect(btaddr);
            a2dp_media_unmute(btaddr);
            a2dp_media_close(btaddr);
        }
        if (memcmp(bt_addr, g_closing_addr, 6) == 0) {
            memset(g_closing_addr, 0xff, 6);
        }
        break;
    case CMD_A2DP_SWITCH:
        log_info("CMD_A2DP_SWITCH");
        if (!bt_slience_get_detect_addr(btaddr)) {
            break;
        }
        a2dp_player_close(bt_addr);
        a2dp_media_mute(bt_addr);
        bt_start_a2dp_slience_detect(bt_addr, 0);
        bt_stop_a2dp_slience_detect(btaddr);
        a2dp_media_unmute(btaddr);
        a2dp_media_close(btaddr);
        break;
    case CMD_SET_A2DP_VOL:
        if (!__this->vol_sync_timer) {
            dev_vol = data[6];
            bt_set_music_device_volume(dev_vol);
        }
        break;
    }
}

static void a2dp_play(u8 *bt_addr)
{
    u8 data[7];
    memcpy(data, bt_addr, 6);
    data[6] = bt_get_music_volume(bt_addr);
    /* if (data[6] > 127) { */
    /*     data[6] = app_audio_bt_volume_update(bt_addr, APP_AUDIO_STATE_MUSIC); */
    /* } */

    if (current_app_in_mode(APP_MODE_BT) == FALSE) {
        app_msg_handler(NULL, APP_MSG_STOP);
        app_mode_change_replace(APP_MODE_BT);
    }

    ai_app_local_event_notify(FILE_PLAYER_START);

    a2dp_play_send_cmd(CMD_A2DP_PLAY, data, 7);
}

static void a2dp_play_slience_detect(u8 *bt_addr)
{
    a2dp_play_send_cmd(CMD_A2DP_SLIENCE_DETECT, bt_addr, 6);
}

static void try_play_preempted_a2dp(void *p)
{
    void *device = btstack_get_conn_device(a2dp_preempted_addr);
    if (!device) {
        memset(a2dp_preempted_addr, 0xff, 6);
        return;
    }
    if (bt_get_call_status() != BT_CALL_HANGUP) {
        sys_timeout_add(NULL, try_play_preempted_a2dp, 500);
        return;
    }
    if (!a2dp_player_is_playing(a2dp_preempted_addr)) {
        btstack_device_control(device, USER_CTRL_AVCTP_OPID_PLAY);
    }
}

static void a2dp_suspend_by_call(u8 *play_addr, void *play_device)
{
    if (play_addr && play_device && (a2dp_player_is_playing(play_addr) || bt_slience_get_detect_addr(play_addr))) {
        memcpy(a2dp_preempted_addr, play_addr, 6);
        memset(a2dp_energy_detect_addr, 0xff, 6);
        btstack_device_control(play_device, USER_CTRL_AVCTP_OPID_PAUSE);
        a2dp_play_send_cmd(CMD_A2DP_MUTE_BY_CALL, play_addr, 6);
    }
}

static void bt_app_msg_a2dp_start(u8 *bt_addr)
{
#if TCFG_A2DP_PREEMPTED_ENABLE
    u8 addr[6];

    if (a2dp_player_get_btaddr(addr)) {
        /* 后台设备a2dp有能量,转为前台播放,
         * 前台设备转为后台静音, 不做能量检测, 防止抖音这种无法暂停的播放器又抢回来
         */
        void *device = btstack_get_conn_device(addr);
        if (device) {
            btstack_device_control(device, USER_CTRL_AVCTP_OPID_PAUSE);
        }
        a2dp_play_send_cmd(CMD_A2DP_MUTE, addr, 6);
    }
    a2dp_play(bt_addr);
#endif
}

static int a2dp_bt_status_event_handler(void *evt)
{
    int ret;
    u8 data[8];
    u8 btaddr[6];
    struct bt_event *bt = (struct bt_event *)evt;

    void *device_a, *device_b;
    bt_get_btstack_device(bt->args, &device_a, &device_b);
    u8 *addr_b = device_b ? btstack_get_device_mac_addr(device_b) : NULL;

    switch (bt->event) {
    case BT_STATUS_A2DP_MEDIA_START:
        log_info("BT_STATUS_A2DP_MEDIA_START");
        /* put_buf(bt->args, 6); */
        if (device_b &&
            btstack_get_call_esco_status(device_b) == BT_ESCO_STATUS_OPEN) {
            a2dp_media_mute(bt->args);
            bt_start_a2dp_slience_detect(bt->args, 0);
            btstack_device_control(device_a, USER_CTRL_AVCTP_OPID_PAUSE);
            break;
        }
        if (bt_get_call_status_for_addr(bt->args) == BT_CALL_INCOMING) {
            //小米11来电挂断偶现没有hungup过来，hfp链路异常，重新断开hfp再连接
            log_warn("a2dp start hfp_incoming");
            bt_cmd_prepare_for_addr(bt->args, USER_CTRL_HFP_DISCONNECT, 0, NULL);
            bt_cmd_prepare_for_addr(bt->args, USER_CTRL_HFP_CMD_CONN, 0, NULL);
        }
        if (esco_player_runing()) {
            a2dp_media_close(bt->args);
            break;
        }
        if (memcmp(a2dp_drop_packet_detect_addr, bt->args, 6) == 0) {
            log_info("bt_action_is_drop_flag");
            if (addr_b && ((memcmp(a2dp_energy_detect_addr, addr_b, 6) == 0) ||
                           (memcmp(a2dp_preempted_addr, addr_b, 6) == 0))) {
                a2dp_play_send_cmd(CMD_A2DP_MUTE, bt->args, 6);
                break;
            }
            memset(a2dp_drop_packet_detect_addr, 0xff, 6);
        }
        if (a2dp_player_get_btaddr(btaddr)) {
            if (memcmp(btaddr, bt->args, 6) == 0) {
                a2dp_play(bt->args);
            } else {
#if TCFG_A2DP_PREEMPTED_ENABLE
                a2dp_play_slience_detect(bt->args);
#else
                if (memcmp(btaddr, g_closing_addr, 6) == 0) {
                    a2dp_media_close(bt->args);
                } else {
                    a2dp_play_send_cmd(CMD_A2DP_MUTE, bt->args, 6);
                    if (device_b && btstack_get_device_a2dp_state(device_b) == BT_MUSIC_STATUS_SUSPENDING) {
                        a2dp_play_send_cmd(CMD_A2DP_SWITCH, addr_b, 6);
                    }
                }
#endif
                break;
            }
        } else {
            a2dp_play(bt->args);
        }
#if A2DP_PLAYBACK_PITCH_KEEP
        audio_pitch_default_parm_set(__this->pitch_mode);
        a2dp_file_pitch_mode_init(__this->pitch_mode);
#endif
        break;
    case BT_STATUS_A2DP_MEDIA_STOP:
        log_info("BT_STATUS_A2DP_MEDIA_STOP");
        if (memcmp(a2dp_energy_detect_addr, bt->args, 6) == 0) {
            memcpy(a2dp_preempted_addr, bt->args, 6);
            memset(a2dp_energy_detect_addr, 0xff, 6);
            sys_timeout_add(NULL, try_play_preempted_a2dp, 500);
        }
        a2dp_play_send_cmd(CMD_A2DP_CLOSE, bt->args, 6);
        break;
    case BT_STATUS_AVRCP_VOL_CHANGE:
        //判断是当前地址的音量值才更新
        ret = a2dp_player_get_btaddr(data);
        if (ret && memcmp(data, bt->args, 6) == 0) {
            data[6] = bt->value;
            a2dp_play_send_cmd(CMD_SET_A2DP_VOL, data, 7);
        }
        break;
    case BT_STATUS_AVDTP_START:
        log_info("BT_STATUS_AVDTP_START");
        /* put_buf(bt->args, 6); */
        break;
    case BT_STATUS_AVDTP_SUSPEND:
        log_info("BT_STATUS_AVDTP_SUSPEND");
        /* put_buf(bt->args, 6); */
        a2dp_media_unmute(bt->args);
        break;
    case BT_STATUS_AVRCP_INCOME_OPID:
        log_info("BT_STATUS_AVRCP_INCOME_OPID: 0x%x", bt->value);
        /* put_buf(bt->args, 6); */
#if TCFG_A2DP_PREEMPTED_ENABLE
        if (bt->value == AVC_PLAY) {
            memcpy(a2dp_avrcp_play_cmd_addr, bt->args, 6);
        }
#endif
        if ((bt->value == AVC_PAUSE || bt->value == AVC_STOP) &&
            a2dp_player_is_playing(bt->args) && addr_b && bt_slience_get_detect_addr(addr_b)) {
            a2dp_play_send_cmd(CMD_A2DP_SWITCH, bt->args, 6);
            break;
        }
        if (bt->value == AVC_PLAY && device_b &&
            btstack_get_call_esco_status(device_b) == BT_ESCO_STATUS_OPEN) {
            a2dp_media_mute(bt->args);
            btstack_device_control(device_a, USER_CTRL_AVCTP_OPID_PAUSE);
            break;
        }
        break;
    case BT_STATUS_SCO_CONNECTION_REQ:
        log_info("A2DP BT_STATUS_SCO_CONNECTION_REQ");
        /* put_buf(bt->args, 6); */
        a2dp_suspend_by_call(addr_b, device_b);
        break;
    case BT_STATUS_SCO_DISCON:
        log_info("BT_STATUS_SCO_DISCON");
        if (addr_b && device_b && bt_not_in_phone_call_state(device_b)) {
            if (memcmp(a2dp_preempted_addr, addr_b, 6) == 0) {
                if (a2dp_media_is_mute(addr_b)) {
                    if (btstack_get_device_a2dp_state(device_b) == BT_MUSIC_STATUS_SUSPENDING) {
                        btstack_device_control(device_b, USER_CTRL_AVCTP_OPID_PLAY);
                    }
                    a2dp_media_unmute(addr_b);
                    a2dp_media_close(addr_b);
                    memcpy(a2dp_energy_detect_addr, addr_b, 6);
                    memset(a2dp_preempted_addr, 0xff, 6);
                } else {
                    sys_timeout_add(NULL, try_play_preempted_a2dp, 500);
                }
                memcpy(a2dp_drop_packet_detect_addr, bt->args, 6);
                break;
            }
            /* 手机A通话中,点击2次手机B的音频播放或打开抖音导致无法暂停
             * 这里取消静音和能量检查，等待协议栈重新发送MEDIA_START消息
             * 此处无法区分是否为没播放完的提示音，所以不走上面的流程，
             * 防止发送PLAY命令把手机B的播放器拉起
             */
            if (a2dp_media_is_mute(addr_b)) {
                bt_stop_a2dp_slience_detect(addr_b);
                a2dp_media_unmute(addr_b);
                a2dp_media_close(addr_b);
            }
        }
        if (memcmp(a2dp_preempted_addr, bt->args, 6) == 0) {
            sys_timeout_add(NULL, try_play_preempted_a2dp, 500);
        }
        break;
    case BT_STATUS_SCO_STATUS_CHANGE:
        log_info("A2DP BT_STATUS_SCO_STATUS_CHANGE len:%d, type:%d",
                 (bt->value >> 16), (bt->value & 0x0000ffff));
        if (bt->value != 0xff) {
            a2dp_suspend_by_call(addr_b, device_b);
        }
        break;
    case BT_STATUS_FIRST_CONNECTED:
    case BT_STATUS_SECOND_CONNECTED:
        if (memcmp(a2dp_preempted_addr, bt->args, 6) == 0) {
            memset(a2dp_preempted_addr, 0xff, 6);
        }
        break;
    }

    return FALSE;
}

REGISTER_APP_EVENT_HANDLER(a2dp_bt_status_event) = {
    .event      = SYS_BT_EVENT,
    .from       = BT_EVENT_FROM_CON,
    .handler    = a2dp_bt_status_event_handler,
};

static int a2dp_bt_hci_event_handler(void *evt)
{
    struct bt_event *event = (struct bt_event *)evt;

    switch (event->event) {
    case HCI_EVENT_DISCONNECTION_COMPLETE:
        a2dp_play_close(event->args);
        break;
    }

    return FALSE;
}

REGISTER_APP_EVENT_HANDLER(a2dp_bt_hci_event) = {
    .event      = SYS_BT_EVENT,
    .from       = BT_EVENT_FROM_HCI,
    .handler    = a2dp_bt_hci_event_handler,
};


static void bt_set_low_latency_mode(int enable, u8 tone_play_enable, int delay_ms)
{
    /*
     * 未连接手机,操作无效
     */
    if (bt_get_total_connect_dev() == 0) {
        return;
    }

    //不在蓝牙模式不操作
    if (current_app_in_mode(APP_MODE_BT) == FALSE) {
        return;
    }

    const char *fname = enable ? get_tone_files()->low_latency_in : get_tone_files()->low_latency_out;

    log_info("bt_set_low_latency_mode=%d", enable);

    play_tone_file_alone(fname);

    a2dp_player_low_latency_enable(enable);

#if TCFG_BT_DUAL_CONN_ENABLE
    if (enable) {
        if (bt_get_total_connect_dev()) {
            lmp_hci_write_scan_enable(0);
        }
    } else {
        void dual_conn_state_handler(void);
        dual_conn_state_handler();
    }
#endif
}

static int bt_get_low_latency_mode(void)
{
    return a2dp_file_get_low_latency_status();
}


#if (TCFG_LEA_BIG_CTRLER_TX_EN || TCFG_LEA_BIG_CTRLER_RX_EN || TCFG_LEA_CIG_CENTRAL_EN || TCFG_LEA_CIG_PERIPHERAL_EN) || \
    (TCFG_LE_AUDIO_APP_CONFIG & (LE_AUDIO_AURACAST_SOURCE_EN | LE_AUDIO_JL_AURACAST_SOURCE_EN)) || \
    (TCFG_LE_AUDIO_APP_CONFIG & (LE_AUDIO_AURACAST_SINK_EN | LE_AUDIO_JL_AURACAST_SINK_EN)) || \
    (TCFG_LE_AUDIO_APP_CONFIG & (LE_AUDIO_UNICAST_SOURCE_EN | LE_AUDIO_JL_UNICAST_SOURCE_EN)) || \
    (TCFG_LE_AUDIO_APP_CONFIG & (LE_AUDIO_UNICAST_SINK_EN | LE_AUDIO_JL_UNICAST_SINK_EN))
static int get_a2dp_play_status(void)
{
    if (get_le_audio_app_mode_exit_flag()) {
        return LOCAL_AUDIO_PLAYER_STATUS_ERR;
    }

    if (bt_get_call_status() != BT_CALL_HANGUP) {
        return LOCAL_AUDIO_PLAYER_STATUS_ERR;
    }
    if ((bt_a2dp_get_status() == BT_MUSIC_STATUS_STARTING) ||
        get_a2dp_decoder_status() ||
        a2dp_player_runing()) {
        return LOCAL_AUDIO_PLAYER_STATUS_PLAY;
    } else {
        return LOCAL_AUDIO_PLAYER_STATUS_ERR;
    }

    return 0;
}

static int a2dp_local_audio_open(void)
{
    if (get_a2dp_play_status() == LOCAL_AUDIO_PLAYER_STATUS_PLAY) {
        //打开本地播放
        int err = a2dp_player_open(get_g_play_addr());
        if (err == -EBUSY) {
            bt_start_a2dp_slience_detect(get_g_play_addr(), 50); //丢掉50包(约1s)之后才开始能量检测,过滤掉提示音，避免提示音引起抢占
        }
    }
    return 0;
}

static int a2dp_local_audio_close(void)
{
    if (get_a2dp_play_status() == LOCAL_AUDIO_PLAYER_STATUS_PLAY) {
        //关闭本地播放
        a2dp_player_close(get_g_play_addr());
    }
    return 0;
}

static void *a2dp_tx_le_audio_open(void *args)
{
    void *le_audio = NULL;

    if (get_a2dp_play_status() == LOCAL_AUDIO_PLAYER_STATUS_PLAY) {
        //打开广播音频播放
        struct le_audio_stream_params *params = (struct le_audio_stream_params *)args;
        le_audio = le_audio_stream_create(params->conn, &params->fmt);
        int err = le_audio_a2dp_recorder_open(get_g_play_addr(), (void *)&params->fmt, le_audio);
        if (err != 0) {
            ASSERT(0, "le audio a2dp recorder open fail");
        }
#if TCFG_LEA_LOCAL_SYNC_PLAY_EN
        err = le_audio_player_open(le_audio, params);
        if (err != 0) {
            ASSERT(0, "le audio player open fail");
        }
#endif
    }

    return le_audio;
}

static int a2dp_tx_le_audio_close(void *le_audio)
{
    if (!le_audio) {
        return -EPERM;
    }

    //关闭广播音频播放
#if TCFG_LEA_LOCAL_SYNC_PLAY_EN
    le_audio_player_close(le_audio);
#endif
    le_audio_a2dp_recorder_close(get_g_play_addr());
    le_audio_stream_free(le_audio);

    return 0;
}

const struct le_audio_mode_ops le_audio_a2dp_ops = {
    .local_audio_open = a2dp_local_audio_open,
    .local_audio_close = a2dp_local_audio_close,
    .tx_le_audio_open = a2dp_tx_le_audio_open,
    .tx_le_audio_close = a2dp_tx_le_audio_close,
    .rx_le_audio_open = default_rx_le_audio_open,
    .rx_le_audio_close = default_rx_le_audio_close,
    .play_status = get_a2dp_play_status,
};

#endif

#endif
