#include "btstack/avctp_user.h"
#include "btstack/btstack_task.h"
#include "btstack/a2dp_media_codec.h"
#include "btstack/bluetooth.h"
#include "btctrler/btctrler_task.h"
#include "btctrler/btcontroller_modules.h"
#include "classic/hci_lmp.h"
#include "classic/tws_event.h"
#include "bt_tws.h"
#include "app_tone.h"
#include "a2dp_player.h"
#include "esco_player.h"
#include "esco_recoder.h"
#include "tts_player.h"
#include "vol_sync.h"
#include "audio_config.h"
#include "app_config.h"
#include "mic_effect.h"
#if TCFG_SMART_VOICE_ENABLE
#include "asr/jl_kws.h"
#include "smart_voice/smart_voice.h"
#endif
#if TCFG_KWS_VOICE_RECOGNITION_ENABLE
#include "jl_kws/jl_kws_api.h"
#endif
#if (TCFG_LEA_BIG_CTRLER_TX_EN || TCFG_LEA_BIG_CTRLER_RX_EN || TCFG_LEA_CIG_CENTRAL_EN || TCFG_LEA_CIG_PERIPHERAL_EN)
#include "app_le_broadcast.h"
#include "app_le_connected.h"
#endif
#include "wireless_trans.h"


#if TCFG_APP_BT_EN && TCFG_USER_TWS_ENABLE


/*配置通话时前面丢掉的数据包包数*/
#define ESCO_DUMP_PACKET_ADJUST		1	/*配置使能*/
#define ESCO_DUMP_PACKET_DEFAULT	0
#define ESCO_DUMP_PACKET_CALL		60 /*0~0xFF*/
#define SYNC_TONE_PHONE_RING_TIME   300

static u8 esco_dump_packet = ESCO_DUMP_PACKET_CALL;

static void phone_income_num_check(void *priv);
static void tws_phone_call_send_cmd(u8 cmd, u8 *btaddr, u8 bt_value, u8 tx_do_action);

enum {
    CMD_OPEN_ESCO_PLAYER = 1,
    CMD_CLOSE_ESCO_PLAYER,
    CMD_PHONE_INCOME,
    CMD_PHONE_OUT,
    CMD_PHONE_HANGUP,
    CMD_PHONE_ACTIVE,
    CMD_PHONE_LASET_CALL_TYPE,
    CMD_PHONE_SIRI,
    CMD_PHONE_SYNC_VOL,
};

#if ESCO_DUMP_PACKET_ADJUST
u8 get_esco_packet_dump(void)
{
    //log_info("esco_dump_packet:%d\n", esco_dump_packet);
    return esco_dump_packet;
}
#endif

bool is_siri_open(void)
{
    if (__this->siri_stu == 1 || __this->siri_stu == 2) {
        return TRUE;
    }

    return FALSE;
}

static int bt_dual_phone_call_event_handler(void *event)
{
    struct bt_event *bt = (struct bt_event *)event;

    u8 phone_event = bt->event;
    if (phone_event != BT_CALL_INCOMING &&
        phone_event != BT_CALL_OUTGOING &&
        phone_event != BT_STATUS_SCO_CONNECTION_REQ) {
        return FALSE;
    }

    if (tws_api_get_role_async() == TWS_ROLE_SLAVE) {
        return FALSE;
    }

    /*
     * device_a为当前发生事件的设备, device_b为另外一个设备
     */
    void *device_a, *device_b;
    bt_get_btstack_device(bt->args, &device_a, &device_b);
    if (!device_a || !device_b) {
        return FALSE;
    }

    u8 *addr_a = bt->args;
    u8 *addr_b = btstack_get_device_mac_addr(device_b);

    int status_a = btstack_bt_get_call_status(device_a);
    int status_b = btstack_bt_get_call_status(device_b);

    if (phone_event == BT_STATUS_SCO_CONNECTION_REQ) {
        log_info("BT_STATUS_SCO_CONNECTION_REQ: status_a = %d, status_b = %d", status_a, status_b);
        if (status_a == BT_CALL_INCOMING) {
            phone_event = BT_STATUS_PHONE_INCOME;
        } else if (status_a == BT_CALL_OUTGOING) {
            phone_event = BT_STATUS_PHONE_OUT;
        }
    }

    switch (phone_event) {
    case BT_STATUS_PHONE_INCOME:
        log_info("BT_STATUS_PHONE_INCOME: status_a = %d, status_b = %d", status_a, status_b);
        if (status_b == BT_CALL_INCOMING &&
            btstack_get_call_esco_status(device_b) == BT_ESCO_STATUS_OPEN) {
            // 先来电的优先级高于后来电
            log_info("disconn_sco-a1");
            btstack_device_control(device_a, USER_CTRL_DISCONN_SCO);
        } else if (status_b == BT_CALL_OUTGOING) {
            // 去电的优先级高于来电
            log_info("disconn_sco-a2");
            btstack_device_control(device_a, USER_CTRL_DISCONN_SCO);
        } else if (status_b == BT_CALL_ACTIVE &&
                   btstack_get_call_esco_status(device_b) == BT_ESCO_STATUS_OPEN) {
            // 通话的优先级高于来电
            log_info("disconn_sco-a3");
            btstack_device_control(device_a, USER_CTRL_DISCONN_SCO);
        }
        break;
    case BT_STATUS_PHONE_OUT:
        log_info("BT_STATUS_PHONE_OUT: status_a = %d, status_b = %d", status_a, status_b);
        if (status_b == BT_CALL_ACTIVE &&
            btstack_get_call_esco_status(device_b) == BT_ESCO_STATUS_OPEN) {
            log_info("disconn_sco-a");
            btstack_device_control(device_a, USER_CTRL_DISCONN_SCO);
            break;
        }
        if (status_b == BT_CALL_OUTGOING) {
            log_info("disconn_sco-b1");
            btstack_device_control(device_b, USER_CTRL_DISCONN_SCO);
        } else if (status_b == BT_CALL_INCOMING) {
            log_info("disconn_sco-b2");
            btstack_device_control(device_b, USER_CTRL_DISCONN_SCO);
        }
        break;
    case BT_STATUS_SCO_CONNECTION_REQ:
        log_info("BT_STATUS_SCO_CONNECTION_REQ: status_a = %d, status_b = %d", status_a, status_b);
        if (status_a == BT_CALL_ACTIVE) {
            // 设备A切声卡, 抢占设备B的去电
            if (status_b == BT_CALL_OUTGOING &&
                btstack_get_call_esco_status(device_b) == BT_ESCO_STATUS_OPEN) {
                log_info("disconn_sco-b1");
                btstack_device_control(device_b, USER_CTRL_DISCONN_SCO);
                break;
            }
            if (status_b == BT_CALL_ACTIVE &&
                btstack_get_call_esco_status(device_b) == BT_ESCO_STATUS_OPEN) {
                log_info("disconn_sco-b2");
#if 1
                // 设备A切声卡, 不抢占设备B的通话
                btstack_device_control(device_a, USER_CTRL_DISCONN_SCO);
#else
                // 设备A切声卡, 抢占设备B的通话
                btstack_device_control(device_b, USER_CTRL_DISCONN_SCO);
#endif
                break;
            }
        }
        break;
    }

    return FALSE;
}

REGISTER_APP_EVENT_HANDLER(bt_dual_phone_call_event) = {
    .event      = SYS_BT_EVENT,
    .from       = BT_EVENT_FROM_CON,
    .handler    = bt_dual_phone_call_event_handler,
};

static void tone_ring_player_stop(void)
{
    tone_player_stop();
    ring_player_stop();
}

static bool phone_ring_play_start(void)
{
    log_info("%s, %d", __FUNCTION__, __this->inband_ringtone);
    /* check if support inband ringtone */
    if (BT_CALL_INCOMING != bt_get_call_status_for_addr(__this->phone_ring_addr)) {
        return FALSE;
    }
    if (!__this->inband_ringtone) {
        if (a2dp_player_get_btaddr(__this->phone_ring_addr)) {
#if TCFG_USER_TWS_ENABLE
            tws_a2dp_slience_detect(__this->phone_ring_addr, 1);
#else
            a2dp_play_slience_detect(__this->phone_ring_addr);
#endif
        }
        if (bt_get_total_connect_dev() > 1 && BT_CALL_HANGUP != bt_get_call_status_for_addr(btstack_get_other_dev_addr(__this->phone_ring_addr))) {
            tws_play_ring_file(get_tone_files()->phone_in, SYNC_TONE_PHONE_RING_TIME);
        } else {
            tws_play_ring_file_alone(get_tone_files()->phone_in, SYNC_TONE_PHONE_RING_TIME);
        }
        return TRUE;
    }
    return FALSE;
}

static void phone_check_inband_ring_play_timer(void *priv)
{
#if TCFG_BT_INBAND_RING
    void *device = btstack_get_conn_device(__this->phone_ring_addr);
    if (__this->inband_ringtone && __this->phone_ring_flag && device && BT_CALL_INCOMING == btstack_bt_get_call_status(device)) {
        if (bt_check_esco_state_via_addr(__this->phone_ring_addr) == BT_ESCO_STATUS_CLOSE) {
            log_info("phone_check_inband_ring_play_timer play");
            __this->inband_ringtone = 0;
            phone_ring_play_start();
        }
    }
#endif
}

static void phone_second_call_ring_play_start(void *priv)
{
//音频设计只有在ESCO工作的时候，播嘟嘟声才能叠加
//两种情况，一是先有嘟嘟声，然后来了ESCO铃声，要先关嘟嘟再开。
//二是两个都是ESCO铃声，第二个打断了第一个之后，第一个的铃声变成嘟嘟叠加。指示有两个来电
    log_info("%s", __FUNCTION__);

    u8 *other_addr = NULL;

    if (priv) {
        other_addr = btstack_get_other_dev_addr((u8 *)priv);
        /* put_buf(priv, 6); */
        log_info("bt_get_call_status_for_addr=%d, %d", bt_get_call_status_for_addr(priv), bt_get_call_status_for_addr(other_addr));
    }

    if (bt_stack_get_incoming_call_num() > 1 || (priv && bt_get_call_status_for_addr(priv) == BT_CALL_INCOMING && bt_get_call_status_for_addr(other_addr) != BT_CALL_OUTGOING)) {
        tws_play_ring_file_alone(get_tone_files()->phone_in, SYNC_TONE_PHONE_RING_TIME);
    }
}

static int bt_phone_income(u8 after_conn, u8 *bt_addr)
{
    le_audio_scene_deal(LE_AUDIO_PHONE_START);

#if TCFG_BT_INBAND_RING
#else
    lmp_private_esco_suspend_resume(3);
#endif
    tone_ring_player_stop();

    __this->phone_ring_sync_tws = 1;
    memcpy(__this->phone_ring_addr, bt_addr, 6);
    put_buf(__this->phone_ring_addr, 6);

    if (tws_api_get_role() == TWS_ROLE_SLAVE) {
        __this->phone_ring_flag = 1;
        __this->phone_income_flag = 1;
        log_info("bt_phone_income sync call");
    } else {
        void *device = btstack_get_conn_device(bt_addr);
        if (!device || BT_CALL_HANGUP == btstack_bt_get_call_status(device)) {
            log_error("bt_phone_income err");
            return 1;
        }
#if TCFG_BT_INBAND_RING
        __this->inband_ringtone = btstack_get_inband_ringtone_flag_for_addr(bt_addr);
#else
        __this->inband_ringtone = 0 ;
#endif

        log_info("inband_ringtone=0x%x", __this->inband_ringtone);
        __this->phone_ring_flag = 1;
        __this->phone_income_flag = 1;

        if (current_app_in_mode(APP_MODE_BT) == FALSE) {
            app_mode_change(APP_MODE_BT);
            __this->back_to_prev_app = 1;
        }

#ifdef CONFIG_NET_ENABLE
        tts_player_stop();
#endif

        if (bt_stack_get_incoming_call_num() > 1) {
            //第一次来电被置上一次。第二次再来就有值了
            sys_timeout_add(__this->phone_ring_addr, phone_second_call_ring_play_start, 2000);
        } else {
            if (__this->inband_ringtone) {
                if (after_conn == 2) { //强制播本地铃声
                    sys_timeout_add(__this->phone_ring_addr, phone_second_call_ring_play_start, 2000);
                }
            } else {
#if TCFG_BT_PHONE_NUMBER_ENABLE
                if (after_conn) {
                    phone_ring_play_start();
                } else {
                    phone_income_num_check(NULL);
                }
#else
                phone_ring_play_start();
#endif
            }
        }
    }

    return 0;
}

#define TWS_PHONE_CALL_AEC_DATA_TO_SD 0

static void bt_phone_hangup(u8 *bt_addr)
{
    log_info("phone_handup");

    esco_dump_packet = ESCO_DUMP_PACKET_CALL;

    if (__this->phone_ring_flag) {
        __this->phone_ring_flag = 0;
        tone_ring_player_stop();
        if (__this->phone_timer_id) {
            sys_timeout_del(__this->phone_timer_id);
            __this->phone_timer_id = 0;
        }
    }

    __this->phone_income_flag = 0;
    __this->phone_num_flag = 0;
    __this->phone_ring_sync_tws = 0;
    lmp_private_esco_suspend_resume(4);

    /*
     * 挂断的时候会清除了一些标识并且会stop了提示音
     * 判断如果另一个手机还在来电并且不支持inband ring，那就恢复一个嘟嘟声提示音
     */
    if (tws_api_get_role() == TWS_ROLE_MASTER) {
        u8 *addr = btstack_get_other_dev_addr(bt_addr);
        if (addr && bt_get_call_status_for_addr(bt_addr) != BT_CALL_OUTGOING) {
            //有另一个连接存在
            u8 call_status = bt_get_call_status_for_addr(addr);
            u8 inband_ring_flag = btstack_get_inband_ringtone_flag_for_addr(addr);
            log_info("other connect call sta:%d-%d-%d", call_status,
                     inband_ring_flag, bt_check_esco_state_via_addr(addr));
            if (call_status == BT_CALL_INCOMING) {
                memcpy(__this->phone_ring_addr, addr, 6);
                __this->phone_ring_sync_tws = 1;
                if ((inband_ring_flag == 0) || (inband_ring_flag && bt_check_esco_state_via_addr(__this->phone_ring_addr) == BT_ESCO_STATUS_CLOSE)) {
                    tws_phone_call_send_cmd(CMD_PHONE_INCOME, __this->phone_ring_addr, 2, 1);
                }
            } else {
                //play_tone_file(get_tone_files()->phone_hangup);
            }
        } else {
            //play_tone_file(get_tone_files()->phone_hangup);
        }
    } else {
        //play_tone_file(get_tone_files()->phone_hangup);
    }

#if TWS_PHONE_CALL_AEC_DATA_TO_SD
    aec_data_to_sd_close();
#endif
    le_audio_scene_deal(LE_AUDIO_PHONE_STOP);

    if (__this->back_to_prev_app) {
        app_core_back_to_prev_app();
        __this->back_to_prev_app = 0;
    }
}

static void bt_phone_out(u8 *bt_addr)
{
    le_audio_scene_deal(LE_AUDIO_PHONE_START);

    esco_dump_packet = ESCO_DUMP_PACKET_CALL;
    __this->phone_income_flag = 0;
}

static void esco_audio_open(u8 *bt_addr)
{
#if TWS_PHONE_CALL_AEC_DATA_TO_SD
    aec_data_to_sd_open();
#endif
    esco_player_open(bt_addr);
#if TCFG_TWS_POWER_BALANCE_ENABLE && TCFG_USER_TWS_ENABLE
    if (tws_api_get_role() == TWS_ROLE_MASTER) {
        log_info("tws_master open esco recoder");
        esco_recoder_open(COMMON_SCO, bt_addr);
    } else {
        log_info("tws_slave don't open esco recoder");
    }
#else
    esco_recoder_open(COMMON_SCO, bt_addr);
#endif
}

static void bt_phone_active(u8 *bt_addr)
{
    if (__this->phone_call_dec_begin) {
        log_info("call_active, dump_packet clear");
        esco_dump_packet = ESCO_DUMP_PACKET_DEFAULT;
    }
    if (__this->phone_ring_flag) {
        __this->phone_ring_flag = 0;
        tone_ring_player_stop();
        if (__this->phone_timer_id) {
            sys_timeout_del(__this->phone_timer_id);
            __this->phone_timer_id = 0;
        }
    }

    lmp_private_esco_suspend_resume(4);
    __this->phone_income_flag = 0;
    __this->phone_num_flag = 0;
    __this->phone_ring_sync_tws = 0;
    /* __this->phone_con_sync_ring = 0; */
    bt_tws_sync_volume();

    log_info("phone_active: %d", app_audio_get_volume(APP_AUDIO_STATE_CALL));
    app_audio_set_volume(APP_AUDIO_STATE_CALL, app_audio_get_volume(APP_AUDIO_STATE_CALL), 1);
}

static void esco_smart_voice_detect_handler(void)
{
#if TCFG_SMART_VOICE_ENABLE
#if TCFG_CALL_KWS_SWITCH_ENABLE
    if (is_siri_open() || (bt_get_call_status() != BT_CALL_INCOMING)) {
        audio_smart_voice_detect_close();
    }
#else
    audio_smart_voice_detect_close();
#endif
#endif
}

static void esco_play_delay(void *p)
{
#if TCFG_AUDIO_DAC_NOISEGATE_ENABLE
    audio_dac_noisefloor_optimize_onoff(0);
#endif
    lmp_private_esco_suspend_resume(4);
    esco_audio_open(__this->esco_play_delay_addr);
}

static int bt_phone_esco_play(u8 *bt_addr)
{
    log_info("esco_dec_start");

    u8 temp_btaddr[6];
    if (esco_player_get_btaddr(temp_btaddr)) {
        //已经有设备在用了，不能重复初始化
        return -1;
    }

#if TCFG_WIFI_ENABLE
    rf_coexistence_scene_enter(RF_COEXISTENCE_SCENE_PHONE_CALL, -1);
    wl_set_beaconlosttime(0);
#endif

    le_audio_scene_deal(LE_AUDIO_PHONE_START);

    if (current_app_in_mode(APP_MODE_BT) == FALSE) {
        app_mode_change(APP_MODE_BT);
        __this->back_to_prev_app = 1;
    }

#ifdef CONFIG_NET_ENABLE
    tts_player_stop();
#endif

#if TCFG_SMART_VOICE_ENABLE
    esco_smart_voice_detect_handler();
#endif

    a2dp_player_close(bt_addr);
    bt_stop_a2dp_slience_detect(bt_addr);
    a2dp_media_close(bt_addr);
#if 0   //debug
    void mic_capless_feedback_toggle(u8 toggle);
    mic_capless_feedback_toggle(0);
#endif
#if TCFG_BT_INBAND_RING
    tone_ring_player_stop();
#else
    if (BT_CALL_INCOMING == bt_get_call_status_for_addr(bt_addr)) {
        lmp_private_esco_suspend_resume(3);
    } else {
        tone_ring_player_stop();
    }
#endif
    bt_api_esco_status(bt_addr, BT_ESCO_STATUS_OPEN);

    if (__this->back_to_prev_app) {
        memcpy(__this->esco_play_delay_addr, bt_addr, 6);
        __this->esco_play_delay_timer = sys_timeout_add(NULL, esco_play_delay, 80);
        lmp_private_esco_suspend_resume(3);
    } else {
#if TCFG_AUDIO_DAC_NOISEGATE_ENABLE
        audio_dac_noisefloor_optimize_onoff(0);
#endif
        esco_audio_open(bt_addr);
    }

    __this->phone_call_dec_begin = 1;

    if (bt_get_call_status() == BT_CALL_ACTIVE) {
        log_info("dec_begin, dump_packet clear");
        esco_dump_packet = ESCO_DUMP_PACKET_DEFAULT;
    }

    tws_page_scan_deal_by_esco(1);
    /* pbg_user_mic_fixed_deal(1); */

    return 0;
}

static void bt_phone_esco_stop(u8 *bt_addr)
{
    log_info("esco_dec_stop");

#if TCFG_KWS_VOICE_RECOGNITION_ENABLE
    /* 处理来电时挂断电话，先跑释放资源再收到handup命令的情况
     * 避免先开smart voice，再关闭"yes/no"，导致出错*/
    jl_kws_speech_recognition_close();
#endif /*TCFG_KWS_VOICE_RECOGNITION_ENABLE*/

    if (!esco_player_is_playing(bt_addr)) {
        log_info("esco_player_is_close");
        return;
    }

    __this->phone_call_dec_begin = 0;
    esco_dump_packet = ESCO_DUMP_PACKET_CALL;

    if (__this->esco_play_delay_timer) {
        sys_timeout_del(__this->esco_play_delay_timer);
        __this->esco_play_delay_timer = 0;
    }

    bt_api_esco_status(bt_addr, BT_ESCO_STATUS_CLOSE);
    esco_recoder_close();
    esco_player_close();

#if TCFG_AUDIO_DAC_NOISEGATE_ENABLE
    audio_dac_noisefloor_optimize_onoff(1);
#endif

#if TCFG_SMART_VOICE_ENABLE
    audio_smart_voice_detect_open(JL_KWS_COMMAND_KEYWORD);
#endif

    le_audio_scene_deal(LE_AUDIO_PHONE_STOP);

    if (__this->back_to_prev_app) {
        app_core_back_to_prev_app();
        __this->back_to_prev_app = 0;
    }

    tws_page_scan_deal_by_esco(0);
    /* pbg_user_mic_fixed_deal(0); */

#if TCFG_WIFI_ENABLE
    rf_coexistence_scene_exit(RF_COEXISTENCE_SCENE_PHONE_CALL);
    wl_set_beaconlosttime(-1);
#endif
}

static void bt_phone_last_call_type(u8 *bt_addr, u8 bt_value)
{
    __this->last_call_type = bt_value;
}

static void bt_phone_siri(u8 *bt_addr, u8 bt_value)
{
    if (bt_value) {
        le_audio_scene_deal(LE_AUDIO_PHONE_START);
    }

    __this->siri_stu = bt_value;
    esco_dump_packet = ESCO_DUMP_PACKET_DEFAULT;

    if (!bt_value) {
        le_audio_scene_deal(LE_AUDIO_PHONE_STOP);
    }
}

static void bt_phone_sync_vol(u8 *bt_addr)
{
    bt_cmd_prepare_for_addr(bt_addr, USER_CTRL_HFP_CALL_SET_VOLUME, 1, &__this->phone_vol);
}

static void bt_phone_sync_vol_timer_callback(void *p)
{
    u8 *ptr = (u8 *)p;

    if (ptr == NULL) {
        return;
    }

    log_info("%s : %d", __func__, ptr[6]);
    bt_cmd_prepare_for_addr(ptr, USER_CTRL_HFP_CALL_SET_VOLUME, 1, &ptr[6]);
    free(ptr);
}

static void tws_esco_play_in_task(u8 *data)
{
    u8 *bt_addr = data + 2;
    u8 bt_value = data[8];

    log_info("tws_esco_play_in_task = %d", data[0]);

    switch (data[0]) {
    case CMD_OPEN_ESCO_PLAYER:
        log_info("CMD_OPEN_ESCO_PLAYER");
#if 0
        lmp_private_esco_suspend_resume(1);
#else

#if TCFG_MIC_EFFECT_ENABLE
        mic_effect_player_pause(1);
#endif
        /*tws通话，仅主机出声*/
#if ((defined TCFG_TWS_ESCO_MODE) && (TCFG_TWS_ESCO_MODE == TWS_ESCO_ONLY_MASTER))
        if (tws_api_get_role() == TWS_ROLE_SLAVE) {
            log_info("tws role slave,esco player disable");
            lmp_private_esco_suspend_resume(1);
            break;
        }
#endif
        bt_phone_esco_play(bt_addr);
#endif
        break;
    case CMD_CLOSE_ESCO_PLAYER:
        log_info("CMD_CLOSE_ESCO_PLAYER");
        bt_phone_esco_stop(bt_addr);
#if TCFG_MIC_EFFECT_ENABLE
        mic_effect_player_pause(0);
#endif
        break;
    case CMD_PHONE_HANGUP:
        log_info("CMD_PHONE_HANGUP");
        bt_phone_hangup(bt_addr);
        break;
    case CMD_PHONE_ACTIVE:
        log_info("CMD_PHONE_ACTIVE");
        bt_phone_active(bt_addr);
        break;
    case CMD_PHONE_INCOME:
        log_info("CMD_PHONE_INCOME");
        bt_phone_income(bt_value, bt_addr);
        break;
    case CMD_PHONE_OUT:
        log_info("CMD_PHONE_OUT");
        bt_phone_out(bt_addr);
        break;
    case CMD_PHONE_LASET_CALL_TYPE:
        log_info("CMD_PHONE_LASET_CALL_TYPE");
        bt_phone_last_call_type(bt_addr, bt_value);
        break;
    case CMD_PHONE_SIRI:
        log_info("CMD_PHONE_SIRI");
        bt_phone_siri(bt_addr, bt_value);
        break;
    default:
        break;
    }

    if (data[1] != 2) {
        free(data);
    }
}

static void tws_esco_play_callback(u8 *data)
{
    int msg[4];

    u8 *buf = malloc(9);
    if (!buf) {
        return;
    }
    memcpy(buf, data, 9);

    msg[0] = (int)tws_esco_play_in_task;
    msg[1] = 1;
    msg[2] = (int)buf;

    os_taskq_post_type("app_core", Q_CALLBACK, 3, msg);
}

static void tws_esco_player_data_in_irq(void *_data, u16 len, bool rx)
{
    u8 *data = (u8 *)_data;

    if (data[1] == 0 && !rx) {
        return;
    }

    tws_esco_play_callback(data);
}

REGISTER_TWS_FUNC_STUB(tws_esco_player_stub) = {
    .func_id = 0x183C0528,
    .func = tws_esco_player_data_in_irq,
};

static void tws_phone_call_send_cmd(u8 cmd, u8 *btaddr, u8 bt_value, u8 tx_do_action)
{
    u8 data[9];
    data[0] = cmd;
    data[1] = tx_do_action;
    memcpy(data + 2, btaddr, 6);
    data[8] = bt_value;
    int err = tws_api_send_data_to_sibling(data, 9, 0x183C0528);
    if (err) {
        data[1] = 2;
        tws_esco_play_in_task(data);
    }
}

static void bt_tws_phone_num_callback(int priv, enum stream_event event)
{
    if (event == STREAM_EVENT_STOP) {
        if (tws_api_get_role() == TWS_ROLE_MASTER &&
            __this->phone_ring_flag && __this->inband_ringtone == 0) {
            tws_play_ring_file_alone(get_tone_files()->phone_in, SYNC_TONE_PHONE_RING_TIME);
        }
    }
}

REGISTER_TWS_TONE_CALLBACK(phone_num_stub) = {
    .func_uuid  = 0x763A8D10,
    .callback   = bt_tws_phone_num_callback,
};

static int bt_phone_num_to_file_list(const char *file_list[], int max_file_num)
{
    int i;
    char *num = (char *)(__this->income_phone_num);

    log_info("phone_num: %s", num);

    for (i = 0; i < max_file_num && num[i] != '\0'; i++) {
        file_list[i] = get_tone_files()->num[num[i] - '0'];
    }
    return i;
}

void phone_income_num_check(void *priv)
{
    const char *file_list[20];
    __this->phone_timer_id = 0;

    if (__this->phone_num_flag) {
        if (tws_api_get_role() == TWS_ROLE_MASTER) {
            if (__this->phone_ring_flag) {
                tone_ring_player_stop();
                int file_num = bt_phone_num_to_file_list(file_list, ARRAY_SIZE(file_list));
                tws_play_tone_files_alone_callback(file_list, file_num, 300, 0x763A8D10);
            }
        }
    } else {
        /*电话号码还没有获取到，定时查询*/
        __this->phone_timer_id = sys_timeout_add(NULL, phone_income_num_check, 200);
    }
}

static int bt_phone_status_event_handler(void *event)
{
    struct bt_event *bt = (struct bt_event *)event;

    if (tws_api_get_role_async() == TWS_ROLE_SLAVE) {
        return FALSE;
    }

    switch (bt->event) {
    case BT_STATUS_PHONE_INCOME:
        log_info("BT_STATUS_PHONE_INCOME");
#if TCFG_MIX_RECORD_ENABLE
        // 来电，结束录音
        if (get_mix_recorder_status()) {
            log_info("BT_STATUS_PHONE_INCOME, Stop recoder!");
            mix_recorder_stop();
        }
#endif
        esco_dump_packet = ESCO_DUMP_PACKET_CALL;
        /*
         *(1)1t2有一台通话的时候，另一台如果来电会叠加
         */
        __this->phone_ring_sync_tws = 1;
        tws_phone_call_send_cmd(CMD_PHONE_INCOME, bt->args, 0, 1);
        /* bt_phone_income(0, 0, tmp_bd_addr); */
#if TCFG_BT_PHONE_NUMBER_ENABLE
        bt_cmd_prepare(USER_CTRL_HFP_CALL_CURRENT, 0, NULL); //发命令获取电话号码
#endif
        break;
    case BT_STATUS_PHONE_OUT:
        log_info("BT_STATUS_PHONE_OUT");
        bt_phone_out(bt->args);
        tws_phone_call_send_cmd(CMD_PHONE_OUT, bt->args, 0, 0);
#if TCFG_BT_PHONE_NUMBER_ENABLE
        bt_cmd_prepare(USER_CTRL_HFP_CALL_CURRENT, 0, NULL); //发命令获取电话号码
#endif
        break;
    case BT_STATUS_PHONE_ACTIVE:
        log_info("BT_STATUS_PHONE_ACTIVE");
        tws_phone_call_send_cmd(CMD_PHONE_ACTIVE, bt->args, 0, 1);
        //play_tone_file_alone(get_tone_files()->phone_active);
        //play_tone_file(get_tone_files()->phone_active);
        void esco_set_tx_drop_packet_num(u16 num);
        //esco_set_tx_drop_packet_num(300);
        break;
    case BT_STATUS_PHONE_HANGUP:
        log_info("BT_STATUS_PHONE_HANGUP");
#if TCFG_MIX_RECORD_ENABLE
        // 挂断电话, 结束录音
        if (get_mix_recorder_status()) {
            log_info("BT_STATUS_PHONE_HANGUP, Stop recoder!");
            mix_recorder_stop();
        }
#endif
        tws_phone_call_send_cmd(CMD_PHONE_HANGUP, bt->args, 0, 1);
        break;
    case BT_STATUS_PHONE_NUMBER:
        log_info("BT_STATUS_PHONE_NUMBER");
        u8 *phone_number = (u8 *)bt->value;
        if (__this->phone_num_flag == 1) {
            break;
        }
        __this->income_phone_len = 0;
        memset(__this->income_phone_num, '\0', sizeof(__this->income_phone_num));

        for (int i = 0; i < strlen((const char *)phone_number); i++) {
            if (phone_number[i] >= '0' && phone_number[i] <= '9') {
                //过滤，只有数字才能报号
                __this->income_phone_num[__this->income_phone_len++] = phone_number[i];
                if (__this->income_phone_len >= sizeof(__this->income_phone_num)) {
                    break;    /*buffer 空间不够，后面不要了*/
                }
            }
        }
        if (__this->income_phone_len > 0) {
            __this->phone_num_flag = 1;
        } else {
            log_error("phone number len err");
        }
        break;
    case BT_STATUS_INBAND_RINGTONE:
        log_info("BT_STATUS_INBAND_RINGTONE");
#if TCFG_BT_INBAND_RING
        __this->inband_ringtone = bt->value;
#else
        __this->inband_ringtone = 0;
#endif
        log_info("inband_ringtone=0x%x", __this->inband_ringtone);
        break;
    case BT_STATUS_SCO_STATUS_CHANGE:
        log_info("BT_STATUS_SCO_STATUS_CHANGE len:%d, type:%d",
                 (bt->value >> 16), (bt->value & 0x0000ffff));
        if (bt->value != 0xff) {
            //为了解决两个手机都在通话，在手机上轮流切声卡的音量问题
            u8 call_vol = bt_get_call_vol_for_addr(bt->args);
            //log_info("bt_get_call_vol_for_addr--%d", call_vol);
            app_audio_state_switch(APP_AUDIO_STATE_CALL, BT_CALL_VOL_LEAVE_MAX, NULL);
            app_audio_set_volume(APP_AUDIO_STATE_CALL, call_vol, 1);
            bt_phone_sync_vol(bt->args);
            if (call_vol != __this->phone_vol) {
                u8 *buf = malloc(7);
                if (buf) {
                    memcpy(buf, bt->args, 6);
                    buf[6] = __this->phone_vol;
                    sys_timeout_add(buf, bt_phone_sync_vol_timer_callback, 1200);
                }
            }
#if TCFG_MIC_EFFECT_ENABLE
            mic_effect_player_pause(1);
#endif
            bt_tws_sync_volume();
            tws_phone_call_send_cmd(CMD_OPEN_ESCO_PLAYER, bt->args, 0, 1);
        } else {
            u8 bt_esco_play[6];
            int ret = esco_player_get_btaddr(bt_esco_play);
            if (ret && memcmp(bt_esco_play, bt->args, 6) != 0) {
                //如果有地址在是用esco音频，但跟传出来的值地址不一致，就不更新了。
                log_warn("bt_esco_stop err, check addr");
                break;
            }

            bt_phone_esco_stop(bt->args);
            tws_phone_call_send_cmd(CMD_CLOSE_ESCO_PLAYER, bt->args, 0, 1);
#if TCFG_MIC_EFFECT_ENABLE
            mic_effect_player_pause(0);
#endif
        }
        break;
    case BT_STATUS_CALL_VOL_CHANGE:
        //判断是当前地址的音量值才更新
        u8 bt_esco_play[6];
        int ret = esco_player_get_btaddr(bt_esco_play);
        if (ret && memcmp(bt_esco_play, bt->args, 6) != 0) {
            //如果有地址在是用esco音频，但跟传出来的值地址不一致，就不更新了。
            break;
        }
        log_info("call_vol: %d", bt->value);
        u8 volume = bt->value;
        u8 call_status = bt_get_call_status_for_addr(bt->args);

#if TCFG_BT_INBAND_RING
        if ((call_status != BT_CALL_ACTIVE) && (bt->value == 0)) {
            log_info("not set vol");
            break;
        }
#endif

        if (ret) {
            __this->phone_vol = bt->value;
            syscfg_write(CFG_BT_CALL_VOLUME, &__this->phone_vol, sizeof(__this->phone_vol));
        }

        if ((call_status == BT_CALL_ACTIVE) ||
            (call_status == BT_CALL_OUTGOING) || __this->siri_stu) {
            app_audio_set_volume(APP_AUDIO_STATE_CALL, volume, 1);
            bt_tws_sync_volume();
        } else {
            /*
             *只保存，不设置到dac
             *微信语音通话的时候，会更新音量到app，但是此时的call status可能是hangup
             */
            void audio_app_volume_set_direct(u8 state, s16 volume);
            audio_app_volume_set_direct(APP_AUDIO_STATE_CALL, volume);
        }
        break;
    case BT_STATUS_LAST_CALL_TYPE_CHANGE:
        log_info("BT_STATUS_LAST_CALL_TYPE_CHANGE: %d", bt->value);
        __this->last_call_type = bt->value;
        tws_phone_call_send_cmd(CMD_PHONE_LASET_CALL_TYPE, bt->args, bt->value, 0);
        break;
    case BT_STATUS_CONN_HFP_CH:
        log_info("BT_STATUS_CONN_HFP_CH");
        break;
    case BT_STATUS_DISCON_HFP_CH:
        log_info("BT_STATUS_DISCON_HFP_CH");
        break;
    case BT_STATUS_PHONE_MANUFACTURER:
        log_info("BT_STATUS_PHONE_MANUFACTURER: %d", bt->value);
        __this->remote_dev_company = bt->value;
        break;
    case BT_STATUS_SIRI_OPEN:
    case BT_STATUS_SIRI_CLOSE:
    case BT_STATUS_SIRI_GET_STATE:
        log_info("BT_STATUS_SIRI_RECOGNITION: %d", bt->value);
        __this->siri_stu = bt->value;
        esco_dump_packet = ESCO_DUMP_PACKET_DEFAULT;
        tws_phone_call_send_cmd(CMD_PHONE_SIRI, bt->args, bt->value, 0);
        break;
    case BT_STATUS_SCO_CONNECTION_REQ :
        log_info(" BT_STATUS_SCO_CONNECTION_REQ");
        break;
    default:
        break;
    }

    return FALSE;
}

REGISTER_APP_EVENT_HANDLER(bt_phone_status_event) = {
    .event      = SYS_BT_EVENT,
    .from       = BT_EVENT_FROM_CON,
    .handler    = bt_phone_status_event_handler,
};

static int bt_phone_hci_event_handler(void *event)
{
    struct bt_event *bt = (struct bt_event *)event;

    switch (bt->event) {
    case HCI_EVENT_DISCONNECTION_COMPLETE:
        if (esco_player_is_playing(bt->args)) {
            bt_phone_esco_stop(bt->args);
        }
        break;
    }

    return FALSE;
}

REGISTER_APP_EVENT_HANDLER(bt_phone_hci_event) = {
    .event      = SYS_BT_EVENT,
    .from       = BT_EVENT_FROM_HCI,
    .handler    = bt_phone_hci_event_handler,
};

static int bt_phone_tws_event_handler(void *evt)
{
    struct tws_event *tws = (struct tws_event *)evt;
    u8 *bt_addr = &tws->args[3];

    switch (tws->event) {
    case TWS_EVENT_MONITOR_START:
        log_info("TWS_EVENT_MONITOR_START");

        if (tws_api_get_role() == TWS_ROLE_MASTER) {
            void *device = btstack_get_conn_device(bt_addr);
            if (device) {
                log_info("__this->phone_income_flag=%d, %d", __this->phone_income_flag, btstack_bt_get_call_status(device));
                /* put_buf(__this->phone_ring_addr, 6); */
                if (BT_CALL_INCOMING == btstack_bt_get_call_status(device) && (!__this->phone_ring_sync_tws)
                    /*&& (memcmp(__this->phone_ring_addr, bt_addr, 6) == 0)*/) { //phone_ring_sync_tws 手机来电过程中连接，已同步过一次，这里不在发起同步播铃声。只有tws后加入才同步播
                    __this->phone_ring_sync_tws = 1;
                    tws_phone_call_send_cmd(CMD_PHONE_INCOME, bt_addr, 1, 1);
                }
            }
        }
        break;
    case TWS_EVENT_MONITOR_M_START_ENTER_ESCO:
        log_info("TWS_EVENT_MONITOR_M_START_ENTER_ESCO");
        /* sys_timeout_add(NULL, auto_role_switch_test, 5 * 1000); */
        break;
    case TWS_EVENT_MONITOR_S_START_ENTER_ESCO:
        log_info("TWS_EVENT_MONITOR_S_START_ENTER_ESCO");
#if ((defined TCFG_TWS_ESCO_MODE) && (TCFG_TWS_ESCO_MODE == TWS_ESCO_ONLY_MASTER))
        if (tws_api_get_role() == TWS_ROLE_SLAVE) {
            log_info("tws role slave,esco player disable");
            lmp_private_esco_suspend_resume(1);
            break;
        }
#endif
#if TCFG_MIC_EFFECT_ENABLE
        mic_effect_player_pause(1);
#endif
        bt_phone_esco_play(bt_addr);
        break;
    case TWS_EVENT_PHONE_LINK_DETACH:
        if (esco_player_is_playing(bt_addr)) {
            bt_phone_esco_stop(bt_addr);
        }
        break;
    }

    return 0;
}

REGISTER_APP_EVENT_HANDLER(bt_phone_tws_event) = {
    .event      = SYS_BT_EVENT,
    .from       = BT_EVENT_FROM_TWS,
    .handler    = bt_phone_tws_event_handler,
};

#endif
