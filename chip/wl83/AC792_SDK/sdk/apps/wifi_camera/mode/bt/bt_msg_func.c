#include "btstack/avctp_user.h"

static int bt_get_phone_state(void *device)
{
    int state = btstack_bt_get_call_status(device);
    if (state == BT_SIRI_STATE &&
        btstack_get_call_esco_status(device) != BT_ESCO_STATUS_OPEN) {
        state = BT_CALL_HANGUP;
    }
    return state;
}

static void bt_get_btstack_device(u8 *addr_a, void **device_a, void **device_b)
{
    void *device[2] = { NULL, NULL };
    btstack_get_conn_devices(device, 2);

    *device_a = btstack_get_conn_device(addr_a);
    *device_b = *device_a == device[0] ? device[1] : device[0];
}

static void volume_up(void)
{
    u8 test_box_vol_up = 0x41;
    s8 cur_vol = 0;
    u8 call_status = bt_get_call_status();
    u8 addr[6];
    int play_status = a2dp_player_get_btaddr(addr);

    if ((tone_player_runing() || ring_player_runing())) {
        if (bt_get_call_status() == BT_CALL_INCOMING) {
            volume_up_down_direct(1);
        }
        return;
    }

    /*打电话出去彩铃要可以调音量大小*/
    if ((call_status == BT_CALL_ACTIVE) || (call_status == BT_CALL_OUTGOING)) {
        cur_vol = app_audio_get_volume(APP_AUDIO_STATE_CALL);
    } else {
        cur_vol = app_audio_get_volume(APP_AUDIO_STATE_MUSIC);
    }

    if (bt_get_remote_test_flag()) {
        bt_cmd_prepare(USER_CTRL_TEST_KEY, 1, &test_box_vol_up); //音量加
    }

    if (cur_vol >= app_audio_get_max_volume()) {
        /* audio_event_to_user(AUDIO_EVENT_VOL_MAX);	//触发vol max事件 */

#if TCFG_MAX_VOL_PROMPT
        play_tone_file_alone(get_tone_files()->max_vol);
#endif
        if (bt_get_call_status() != BT_CALL_HANGUP) {
            /*本地音量最大，如果手机音量还没最大，继续加，以防显示不同步*/
            if (__this->phone_vol < 15) {
                if (bt_get_curr_channel_state() & HID_CH) {
                    bt_cmd_prepare(USER_CTRL_HID_VOL_UP, 0, NULL);
                } else {
                    bt_cmd_prepare(USER_CTRL_HFP_CALL_VOLUME_UP, 0, NULL);
                }
            }
            return;
        }
#if TCFG_BT_VOL_SYNC_ENABLE
        if (bt_get_call_status() == BT_CALL_HANGUP) {
            s16 music_volume_value = get_music_volume();
            opid_play_vol_sync_fun(&music_volume_value, 1);
            set_music_volume(music_volume_value);
            if (play_status) {
                bt_cmd_prepare_for_addr(addr, USER_CTRL_CMD_SYNC_VOL_INC, 0, NULL);
            } else {
                bt_cmd_prepare(USER_CTRL_CMD_SYNC_VOL_INC, 0, NULL);
            }
        }
#endif/* TCFG_BT_VOL_SYNC_ENABLE */
        return;
    }

#if TCFG_BT_VOL_SYNC_ENABLE
    if (bt_get_call_status() == BT_CALL_HANGUP) {
        s16 music_volume_value = get_music_volume();
        opid_play_vol_sync_fun(&music_volume_value, 1);
        set_music_volume(music_volume_value);
        app_audio_set_volume(APP_AUDIO_STATE_MUSIC, get_music_volume(), 1);
    }
#else
    if (app_audio_get_state() == APP_AUDIO_STATE_IDLE) {
        app_audio_state_switch(APP_AUDIO_STATE_MUSIC, app_audio_volume_max_query(AppVol_BT_MUSIC), NULL);
    }
    app_audio_volume_up(1);
#endif/*TCFG_BT_VOL_SYNC_ENABLE*/

    log_info("vol+: %d", app_audio_get_volume(APP_AUDIO_CURRENT_STATE));

    if (bt_get_call_status() != BT_CALL_HANGUP) {
        if (bt_get_curr_channel_state() & HID_CH) {
            bt_cmd_prepare(USER_CTRL_HID_VOL_UP, 0, NULL);
        } else {
            bt_cmd_prepare(USER_CTRL_HFP_CALL_VOLUME_UP, 0, NULL);
        }
    } else {
#if TCFG_BT_VOL_SYNC_ENABLE
        if (play_status) {
            bt_cmd_prepare_for_addr(addr, USER_CTRL_CMD_SYNC_VOL_INC, 0, NULL);
        } else {
            bt_cmd_prepare(USER_CTRL_CMD_SYNC_VOL_INC, 0, NULL);
        }
#endif
    }
}

static void volume_down(void)
{
    u8 test_box_vol_down = 0x42;
    u8 addr[6];
    int play_status = a2dp_player_get_btaddr(addr);

    if ((tone_player_runing() || ring_player_runing())) {
        if (bt_get_call_status() == BT_CALL_INCOMING) {
            volume_up_down_direct(-1);
        }
        return;
    }

    if (bt_get_remote_test_flag()) {
        bt_cmd_prepare(USER_CTRL_TEST_KEY, 1, &test_box_vol_down); //音量减
    }

    if (app_audio_get_volume(APP_AUDIO_CURRENT_STATE) <= 0) {
        /* audio_event_to_user(AUDIO_EVENT_VOL_MIN);	//触发vol mix事件 */
        if (bt_get_call_status() != BT_CALL_HANGUP) {
            /*
             *本地音量最小，如果手机音量还没最小，继续减
             *注意：有些手机通话最小音量是1(GREE G0245D)
             */
            if (__this->phone_vol > 1) {
                if (bt_get_curr_channel_state() & HID_CH) {
                    bt_cmd_prepare(USER_CTRL_HID_VOL_DOWN, 0, NULL);
                } else {
                    bt_cmd_prepare(USER_CTRL_HFP_CALL_VOLUME_DOWN, 0, NULL);
                }
            }
            return;
        }
#if TCFG_BT_VOL_SYNC_ENABLE
        if (bt_get_call_status() == BT_CALL_HANGUP) {
            s16 music_volume_value = get_music_volume();
            opid_play_vol_sync_fun(&music_volume_value, 0);
            set_music_volume(music_volume_value);
            if (play_status) {
                bt_cmd_prepare_for_addr(addr, USER_CTRL_CMD_SYNC_VOL_DEC, 0, NULL);
            } else {
                bt_cmd_prepare(USER_CTRL_CMD_SYNC_VOL_DEC, 0, NULL);
            }
        }
#endif
        return;
    }

#if TCFG_BT_VOL_SYNC_ENABLE
    if (bt_get_call_status() == BT_CALL_HANGUP) {
        s16 music_volume_value = get_music_volume();
        opid_play_vol_sync_fun(&music_volume_value, 0);
        set_music_volume(music_volume_value);
        app_audio_set_volume(APP_AUDIO_STATE_MUSIC, get_music_volume(), 1);
    }
#else
    if (app_audio_get_state() == APP_AUDIO_STATE_IDLE) {
        app_audio_state_switch(APP_AUDIO_STATE_MUSIC, app_audio_volume_max_query(AppVol_BT_MUSIC), NULL);
    }
    app_audio_volume_down(1);
#endif/*TCFG_BT_VOL_SYNC_ENABLE*/

    log_info("vol-: %d", app_audio_get_volume(APP_AUDIO_CURRENT_STATE));

    if (bt_get_call_status() != BT_CALL_HANGUP) {
        if (bt_get_curr_channel_state() & HID_CH) {
            bt_cmd_prepare(USER_CTRL_HID_VOL_DOWN, 0, NULL);
        } else {
            bt_cmd_prepare(USER_CTRL_HFP_CALL_VOLUME_DOWN, 0, NULL);
        }
    } else {
#if TCFG_BT_VOL_SYNC_ENABLE
        /* opid_play_vol_sync_fun(&get_music_volume(), 0); */
        if (app_audio_get_volume(APP_AUDIO_CURRENT_STATE) == 0) {
            app_audio_volume_down(0);
        }
        if (play_status) {
            bt_cmd_prepare_for_addr(addr, USER_CTRL_CMD_SYNC_VOL_DEC, 0, NULL);
        } else {
            bt_cmd_prepare(USER_CTRL_CMD_SYNC_VOL_DEC, 0, NULL);
        }
#endif
    }
}

static void volume_set(s16 volume)
{
    s8 cur_vol = 0;
    u8 call_status = bt_get_call_status();
    u8 addr[6];
    int play_status = a2dp_player_get_btaddr(addr);

    if ((tone_player_runing() || ring_player_runing())) {
        return;
    }

    /*打电话出去彩铃要可以调音量大小*/
    if ((call_status == BT_CALL_ACTIVE) || (call_status == BT_CALL_OUTGOING)) {
        cur_vol = app_audio_get_volume(APP_AUDIO_STATE_CALL);
    } else {
        cur_vol = app_audio_get_volume(APP_AUDIO_STATE_MUSIC);
    }

    u8 vol_lev = (u8)volume * 16 / app_audio_volume_max_query(AppVol_BT_MUSIC);
    u8 cur_lev = cur_vol * 16 / app_audio_volume_max_query(AppVol_BT_MUSIC);

    if (cur_vol >= app_audio_get_max_volume() && vol_lev >= cur_lev) {
        /* audio_event_to_user(AUDIO_EVENT_VOL_MAX);	//触发vol max事件 */
#if TCFG_MAX_VOL_PROMPT
        play_tone_file_alone(get_tone_files()->max_vol);
#endif
        if (bt_get_call_status() != BT_CALL_HANGUP) {
            /*本地音量最大，如果手机音量还没最大，继续加，以防显示不同步*/
            if (__this->phone_vol < 15) {
                if (bt_get_curr_channel_state() & HID_CH) {
                    bt_cmd_prepare(USER_CTRL_HID_VOL_UP, 0, NULL);
                } else {
                    bt_cmd_prepare(USER_CTRL_HFP_CALL_VOLUME_UP, 0, NULL);
                }
            }
            return;
        }
#if TCFG_BT_VOL_SYNC_ENABLE
        if (bt_get_call_status() == BT_CALL_HANGUP) {
            s16 music_volume_value = get_music_volume();
            opid_play_vol_sync_fun(&music_volume_value, 1);
            set_music_volume(music_volume_value);
            if (play_status) {
                bt_cmd_prepare_for_addr(addr, USER_CTRL_HFP_CALL_SET_VOLUME, 1, &vol_lev);
            } else {
                bt_cmd_prepare(USER_CTRL_HFP_CALL_SET_VOLUME, 1, &vol_lev);
            }
        }
#endif/* TCFG_BT_VOL_SYNC_ENABLE */
        return;
    } else if (app_audio_get_volume(APP_AUDIO_CURRENT_STATE) <= 0 &&
               volume <= app_audio_get_volume(APP_AUDIO_CURRENT_STATE)) {
        /* audio_event_to_user(AUDIO_EVENT_VOL_MIN);	//触发vol mix事件 */
        if (bt_get_call_status() != BT_CALL_HANGUP) {
            /*
             *本地音量最小，如果手机音量还没最小，继续减
             *注意：有些手机通话最小音量是1(GREE G0245D)
             */
            if (__this->phone_vol > 1) {
                if (bt_get_curr_channel_state() & HID_CH) {
                    bt_cmd_prepare(USER_CTRL_HID_VOL_DOWN, 0, NULL);
                } else {
                    bt_cmd_prepare(USER_CTRL_HFP_CALL_VOLUME_DOWN, 0, NULL);
                }
            }
            return;
        }
#if TCFG_BT_VOL_SYNC_ENABLE
        if (bt_get_call_status() == BT_CALL_HANGUP) {
            s16 music_volume_value = get_music_volume();
            opid_play_vol_sync_fun(&music_volume_value, 0);
            set_music_volume(music_volume_value);
            if (play_status) {
                bt_cmd_prepare_for_addr(addr, USER_CTRL_CMD_SYNC_VOL_DEC, 0, NULL);
            } else {
                bt_cmd_prepare(USER_CTRL_CMD_SYNC_VOL_DEC, 0, NULL);
            }
        }
#endif
        return;
    }

#if TCFG_BT_VOL_SYNC_ENABLE
    if (bt_get_call_status() == BT_CALL_HANGUP) {
        opid_play_vol_sync_fun(&volume, 3);
        set_music_volume(volume);
        app_audio_set_volume(APP_AUDIO_STATE_MUSIC, get_music_volume(), 1);
    }
#else
    if (app_audio_get_state() == APP_AUDIO_STATE_IDLE) {
        app_audio_state_switch(APP_AUDIO_STATE_MUSIC, app_audio_volume_max_query(AppVol_BT_MUSIC), NULL);
    }
    app_audio_set_volume(APP_AUDIO_CURRENT_STATE, volume, 1);
#endif/*TCFG_BT_VOL_SYNC_ENABLE*/

    log_info("vol-: %d", app_audio_get_volume(APP_AUDIO_CURRENT_STATE));

    if (bt_get_call_status() != BT_CALL_HANGUP) {
        if (bt_get_curr_channel_state() & HID_CH) {
            //
        } else {
            if (play_status) {
                bt_cmd_prepare_for_addr(addr, USER_CTRL_HFP_CALL_SET_VOLUME, 1, &vol_lev);
            } else {
                bt_cmd_prepare(USER_CTRL_HFP_CALL_SET_VOLUME, 1, &vol_lev);
            }
        }
    } else {
#if TCFG_BT_VOL_SYNC_ENABLE
        /* opid_play_vol_sync_fun(&get_music_volume(), 0); */
        if (play_status) {
            bt_cmd_prepare_for_addr(addr, USER_CTRL_CMD_SYNC_VOL_DEC, 0, NULL);
        } else {
            bt_cmd_prepare(USER_CTRL_CMD_SYNC_VOL_DEC, 0, NULL);
        }
#endif
    }
}

#define SECOND_CALL_CCWA_COME   BIT(0)
#define SECOND_CALL_IN          BIT(1)
#define SECOND_CALL_OUT         BIT(2)
#define SECOND_CALL_HELD        BIT(3)

u8 get_second_call_status_for_addr(u8 *addr);

static void bt_app_msg_music_pp(void)
{
    void *devices[2];
    void *active_device = NULL;
    void *incoming_device = NULL;
    void *outgoing_device = NULL;
    void *siri_device = NULL;

    int num = btstack_get_conn_devices(devices, 2);
    for (int i = 0; i < num; i++) {
        int state = bt_get_phone_state(devices[i]);
        if (state == BT_CALL_ACTIVE) {
            active_device = devices[i];
        } else if (state == BT_CALL_INCOMING) {
            incoming_device = devices[i];
        } else if (state == BT_CALL_OUTGOING || state == BT_CALL_ALERT) {
            outgoing_device = devices[i];
        } else if (state == BT_SIRI_STATE) {
            siri_device = devices[i];
        }
    }

    if (incoming_device) {
        bt_cmd_prepare_for_addr(btstack_get_device_mac_addr(incoming_device), USER_CTRL_HFP_CALL_ANSWER, 0, NULL);
    } else if (outgoing_device) {
        bt_cmd_prepare_for_addr(btstack_get_device_mac_addr(outgoing_device), USER_CTRL_HFP_CALL_HANGUP, 0, NULL);
    } else if (active_device) {
        if (get_second_call_status_for_addr(btstack_get_device_mac_addr(active_device)) & SECOND_CALL_IN) {
            bt_cmd_prepare_for_addr(btstack_get_device_mac_addr(active_device), USER_CTRL_HFP_THREE_WAY_ANSWER2, 0, NULL);
        } else {
            bt_cmd_prepare_for_addr(btstack_get_device_mac_addr(active_device), USER_CTRL_HFP_CALL_HANGUP, 0, NULL);
        }
    } else if (siri_device) {
        bt_cmd_prepare_for_addr(btstack_get_device_mac_addr(siri_device), USER_CTRL_HFP_CALL_HANGUP, 0, NULL);
    } else {
        u8 addr[6];
        if (a2dp_player_get_btaddr(addr)) {
            bt_cmd_prepare_for_addr(addr, USER_CTRL_AVCTP_OPID_PLAY, 0, NULL);
        } else {
            bt_cmd_prepare(USER_CTRL_AVCTP_OPID_PLAY, 0, NULL);
        }
    }
}

//audio id 开始测试前挂断电话、音乐等
static void bt_app_msg_music_stop(void)
{
    void *devices[2];
    void *active_device = NULL;
    void *incoming_device = NULL;
    void *outgoing_device = NULL;
    void *siri_device = NULL;

    int num = btstack_get_conn_devices(devices, 2);
    for (int i = 0; i < num; i++) {
        int state = bt_get_phone_state(devices[i]);
        if (state == BT_CALL_ACTIVE) {
            active_device = devices[i];
        } else if (state == BT_CALL_INCOMING) {
            incoming_device = devices[i];
        } else if (state == BT_CALL_OUTGOING || state == BT_CALL_ALERT) {
            outgoing_device = devices[i];
        } else if (state == BT_SIRI_STATE) {
            siri_device = devices[i];
        }
    }
    printf("bt_app_msg_music_stop: active_device = %p, incoming_device = %p, outgoing_device = %p, siri_device = %p\n", active_device, incoming_device, outgoing_device, siri_device);
    if (incoming_device) {
        bt_cmd_prepare_for_addr(btstack_get_device_mac_addr(incoming_device), USER_CTRL_HFP_CALL_ANSWER, 0, NULL);
    } else if (outgoing_device) {
        bt_cmd_prepare_for_addr(btstack_get_device_mac_addr(outgoing_device), USER_CTRL_HFP_CALL_HANGUP, 0, NULL);
    } else if (active_device) {
        if (get_second_call_status_for_addr(btstack_get_device_mac_addr(active_device)) & SECOND_CALL_IN) {
            bt_cmd_prepare_for_addr(btstack_get_device_mac_addr(active_device), USER_CTRL_HFP_THREE_WAY_ANSWER2, 0, NULL);
        } else {
            bt_cmd_prepare_for_addr(btstack_get_device_mac_addr(active_device), USER_CTRL_HFP_CALL_HANGUP, 0, NULL);
        }
    } else if (siri_device) {
        bt_cmd_prepare_for_addr(btstack_get_device_mac_addr(siri_device), USER_CTRL_HFP_CALL_HANGUP, 0, NULL);
    } else {
        u8 addr[6];
        if (a2dp_player_get_btaddr(addr)) {
            //  printf("bt_app_msg_music_stop: addr = %p\n", addr);
            //a2dp_player_close(addr);
            bt_cmd_prepare_for_addr(addr, USER_CTRL_AVCTP_OPID_STOP, 0, NULL);
        } else {
            if (bt_a2dp_get_status() == BT_MUSIC_STATUS_STARTING) {
                bt_cmd_prepare(USER_CTRL_AVCTP_OPID_STOP, 0, NULL);
                //    printf("bt_app_msg_music_stop: 11\n");
            }
            // bt_cmd_prepare(USER_CTRL_AVCTP_OPID_STOP, 0, NULL);
        }
        //  printf("bt_app_msg_music_stop: 22\n");
    }
}

static void bt_app_msg_music_play(void)
{
    if (bt_get_call_status() == BT_CALL_INCOMING) {
        bt_cmd_prepare(USER_CTRL_HFP_CALL_ANSWER, 0, NULL);
    } else if (bt_a2dp_get_status() == BT_MUSIC_STATUS_SUSPENDING) {
        bt_cmd_prepare(USER_CTRL_AVCTP_OPID_PLAY, 0, NULL);
    }
}

static void bt_app_msg_music_pause(void)
{
    if ((bt_get_call_status() == BT_CALL_OUTGOING) ||
        (bt_get_call_status() == BT_CALL_ALERT)) {
        bt_cmd_prepare(USER_CTRL_HFP_CALL_HANGUP, 0, NULL);
    } else if (bt_get_call_status() == BT_CALL_ACTIVE) {
        bt_cmd_prepare(USER_CTRL_HFP_CALL_HANGUP, 0, NULL);
    } else if (bt_a2dp_get_status() == BT_MUSIC_STATUS_STARTING) {
        bt_cmd_prepare(USER_CTRL_AVCTP_OPID_PAUSE, 0, NULL);
    }
}

static void bt_app_msg_music_next(void)
{
    u8 addr[6];

    if (a2dp_player_get_btaddr(addr)) {
        bt_cmd_prepare_for_addr(addr, USER_CTRL_AVCTP_OPID_NEXT, 0, NULL);
    } else {
        bt_cmd_prepare(USER_CTRL_AVCTP_OPID_NEXT, 0, NULL);
    }
}

static void bt_app_msg_music_prev(void)
{
    u8 addr[6];

    if (a2dp_player_get_btaddr(addr)) {
        bt_cmd_prepare_for_addr(addr, USER_CTRL_AVCTP_OPID_PREV, 0, NULL);
    } else {
        bt_cmd_prepare(USER_CTRL_AVCTP_OPID_PREV, 0, NULL);
    }
}

static void bt_app_msg_vol_up(void)
{
    if (bt_get_call_status() == BT_CALL_ACTIVE && bt_sco_state() == 0) {
        return;
    }

    if (!bt_get_total_connect_dev()) {
        return;
    }

    volume_up();

    u8 call_status = bt_get_call_status();
    u8 vol;

    if ((call_status == BT_CALL_ACTIVE) || (call_status == BT_CALL_OUTGOING)) {
        vol = app_audio_get_volume(APP_AUDIO_STATE_CALL);
    } else {
        vol = app_audio_get_volume(APP_AUDIO_STATE_MUSIC);
    }

    log_info("music_vol:vol=%d, state:%d", vol, app_audio_get_state());

#if (THIRD_PARTY_PROTOCOLS_SEL & MULTI_BOX_ADV_EN)
    multi_box_bis_change_volume_notify();
#endif
#if TCFG_USER_TWS_ENABLE
    bt_tws_sync_volume();
#endif
}

static void bt_app_msg_vol_down(void)
{
    if (bt_get_call_status() == BT_CALL_ACTIVE && bt_sco_state() == 0) {
        return;
    }

    if (!bt_get_total_connect_dev()) {
        return;
    }

    volume_down();

    u8 call_status = bt_get_call_status();
    u8 vol;

    if ((call_status == BT_CALL_ACTIVE) || (call_status == BT_CALL_OUTGOING)) {
        vol = app_audio_get_volume(APP_AUDIO_STATE_CALL);
    } else {
        vol = app_audio_get_volume(APP_AUDIO_STATE_MUSIC);
    }

    log_info("music_vol:vol=%d, state:%d", vol, app_audio_get_state());

#if (THIRD_PARTY_PROTOCOLS_SEL & MULTI_BOX_ADV_EN)
    multi_box_bis_change_volume_notify();
#endif
#if TCFG_USER_TWS_ENABLE
    bt_tws_sync_volume();
#endif
}

static void bt_app_msg_vol_set(u8 volume)
{
    if (bt_get_call_status() == BT_CALL_ACTIVE && bt_sco_state() == 0) {
        return;
    }

    if (!bt_get_total_connect_dev()) {
        return;
    }

    volume_set((s16)volume);

    u8 call_status = bt_get_call_status();
    u8 vol;

    if ((call_status == BT_CALL_ACTIVE) || (call_status == BT_CALL_OUTGOING)) {
        vol = app_audio_get_volume(APP_AUDIO_STATE_CALL);
    } else {
        vol = app_audio_get_volume(APP_AUDIO_STATE_MUSIC);
    }

    log_info("music_vol:vol=%d, state:%d", vol, app_audio_get_state());

#if (THIRD_PARTY_PROTOCOLS_SEL & MULTI_BOX_ADV_EN)
    multi_box_bis_change_volume_notify();
#endif
#if TCFG_USER_TWS_ENABLE
    bt_tws_sync_volume();
#endif
}

static void bt_app_msg_call_last_on(void)
{
    if (bt_get_call_status() == BT_CALL_INCOMING) {
        bt_cmd_prepare(USER_CTRL_HFP_CALL_HANGUP, 0, NULL);
        return;
    }

    if ((bt_get_call_status() == BT_CALL_ACTIVE) ||
        (bt_get_call_status() == BT_CALL_OUTGOING) ||
        (bt_get_call_status() == BT_CALL_ALERT) ||
        (bt_get_call_status() == BT_CALL_INCOMING)) {
        return;//通话过程不允许回拨
    }

    if (__this->last_call_type ==  BT_STATUS_PHONE_INCOME) {
        bt_cmd_prepare(USER_CTRL_HFP_DIAL_NUMBER, __this->income_phone_len,
                       __this->income_phone_num);
    } else {
        bt_cmd_prepare(USER_CTRL_HFP_CALL_LAST_NO, 0, NULL);
    }
}

static void bt_app_msg_call_answer(void)
{
    u8 temp_btaddr[6];
    if (esco_player_get_btaddr(temp_btaddr)) {
        if (bt_get_call_status() == BT_CALL_INCOMING) {
            log_info("APP_MSG_CALL_ANSWER: esco playing, device_addr");
            put_buf(temp_btaddr, 6);
            bt_cmd_prepare_for_addr(temp_btaddr, USER_CTRL_HFP_CALL_ANSWER, 0, NULL);
        }
    } else {
        if (bt_get_call_status() == BT_CALL_INCOMING) {
            log_info("APP_MSG_CALL_ANSWER: esco no playing");
            bt_cmd_prepare(USER_CTRL_HFP_CALL_ANSWER, 0, NULL);
        }
    }
}

static void bt_app_msg_call_hang_up(void)
{
    u8 temp_btaddr[6];
    u8 *other_addr = NULL;

    if (bt_get_total_connect_dev() > 1 && get_unactive_device_call_status() != BT_CALL_HANGUP) {
        other_addr = btstack_get_other_dev_addr(bt_get_current_remote_addr());
    }

    if (esco_player_get_btaddr(temp_btaddr)) {
        if (other_addr) {
            other_addr = bt_get_current_remote_addr();
            log_info("APP_MSG_CALL_HANGUP: other incoming");
            put_buf(other_addr, 6);
            bt_cmd_prepare_for_addr(other_addr, USER_CTRL_HFP_THREE_WAY_REJECT, 0, NULL);
        } else {
            log_info("APP_MSG_CALL_HANGUP: current esco playing");
            put_buf(temp_btaddr, 6);
            bt_cmd_prepare_for_addr(temp_btaddr, USER_CTRL_HFP_CALL_HANGUP, 0, NULL);
        }
    } else {
        u8 *addr = bt_get_current_remote_addr();
        if (addr) {
            memcpy(temp_btaddr, addr, 6);
            u8 call_status = bt_get_call_status_for_addr(temp_btaddr);
            if ((call_status >= BT_CALL_INCOMING) && (call_status <= BT_CALL_ACTIVE)) {
                log_info("APP_MSG_CALL_HANGUP: current addr");
                put_buf(temp_btaddr, 6);
                bt_cmd_prepare_for_addr(temp_btaddr, USER_CTRL_HFP_CALL_HANGUP, 0, NULL);
                return;
            }
            addr = btstack_get_other_dev_addr(addr);
            if (addr) {
                log_info("APP_MSG_CALL_HANGUP: other addr");
                memcpy(temp_btaddr, addr, 6);
                put_buf(temp_btaddr, 6);
                call_status = bt_get_call_status_for_addr(temp_btaddr);
                if ((call_status >= BT_CALL_INCOMING) && (call_status <= BT_CALL_ACTIVE)) {
                    bt_cmd_prepare_for_addr(temp_btaddr, USER_CTRL_HFP_CALL_HANGUP, 0, NULL);
                }
            }
        }
    }
}

static bool bt_app_msg_call_incomming_hangup(void)
{
    void *devices[2];
    int num = btstack_get_conn_devices(devices, 2);
    for (int i = 0; i < num; i++) {
        if (bt_get_phone_state(devices[i]) == BT_CALL_INCOMING) {
            bt_cmd_prepare_for_addr(btstack_get_device_mac_addr(devices[i]), USER_CTRL_HFP_CALL_HANGUP, 0, NULL);
            return TRUE;
        } else if (bt_get_phone_state(devices[i]) == BT_CALL_ACTIVE || bt_get_phone_state(devices[i]) == BT_CALL_OUTGOING) {
            if (get_second_call_status_for_addr(btstack_get_device_mac_addr(devices[i])) & SECOND_CALL_IN) {
                bt_cmd_prepare_for_addr(btstack_get_device_mac_addr(devices[i]), USER_CTRL_HFP_THREE_WAY_REJECT, 0, NULL);
                return TRUE;
            }
        }
    }

    return FALSE;
}

static void bt_app_msg_call_siri(void)
{
    bt_cmd_prepare(USER_CTRL_HFP_GET_SIRI_OPEN, 0, NULL);
}

static void bt_app_msg_hid_control(void)
{
    if (bt_get_curr_channel_state() & HID_CH) {
        bt_cmd_prepare(USER_CTRL_HID_IOS, 0, NULL);
    }
}

//蓝牙模式 三方通话 挂断当前去听另一个（未接听或者在保留状态都可以）
static void bt_app_msg_call_three_way_answer1(void)
{
    bt_cmd_prepare(USER_CTRL_HFP_THREE_WAY_ANSWER1, 0, NULL);
}

//蓝牙模式 三方通话 保留当前去接听, 或者用于两个通话的切换
static void bt_app_msg_call_three_way_answer2(void)
{
    bt_cmd_prepare(USER_CTRL_HFP_THREE_WAY_ANSWER2, 0, NULL);
}

static void bt_app_msg_call_switch(void)
{
    if (bt_get_call_status() == BT_CALL_ACTIVE) {
        bt_cmd_prepare(USER_CTRL_SCO_LINK, 0, NULL);
    }
}

static void *get_the_other_device(u8 *addr)
{
    void *devices[2] = {NULL, NULL};
    int num = btstack_get_conn_devices(devices, 2);
    /*printf("bt_device: %p, %p\n", devices[0], devices[1]);
    put_buf(btstack_get_device_mac_addr(devices[0]), 6);
    put_buf(btstack_get_device_mac_addr(devices[1]), 6);*/
    for (int i = 0; i < num; i++) {
        if (memcmp(btstack_get_device_mac_addr(devices[i]), addr, 6)) {
            return devices[i];
        }
    }

    return NULL;
}

static void bt_action_a2dp_play(void *device, u8 *bt_addr)
{
    int slience = bt_slience_detect_get_result(bt_addr);
    int playing = a2dp_player_is_playing(bt_addr);

    log_info("a2dp_play: %d, %d", playing, slience);
    put_buf(bt_addr, 6);

    if (slience == BT_SLIENCE_NO_DETECTING) {
        if (!playing) {
            btstack_device_control(device, USER_CTRL_AVCTP_OPID_PLAY);
        }
    } else if (slience == BT_SLIENCE_NO_ENERGY) {
        btstack_device_control(device, USER_CTRL_AVCTP_OPID_PLAY);
    } else {
        int msg[3];
        msg[0] = APP_MSG_BT_A2DP_PLAY;
        memcpy(msg + 1, bt_addr, 6);
        app_send_message(MSG_FROM_APP, 3, msg);
    }
}

static void bt_action_a2dp_pause(void *device, u8 *bt_addr)
{
    int slience = bt_slience_detect_get_result(bt_addr);
    int playing = a2dp_player_is_playing(bt_addr);

    log_info("a2dp_pause: %d, %d", playing, slience);
    put_buf(bt_addr, 6);

    if (playing) {
        btstack_device_control(device, USER_CTRL_AVCTP_PAUSE_MUSIC);
    } else {
        if (slience == BT_SLIENCE_HAVE_ENERGY) {
            btstack_device_control(device, USER_CTRL_AVCTP_PAUSE_MUSIC);
        }
    }
    int msg[3];
    msg[0] = APP_MSG_BT_A2DP_PAUSE;
    memcpy(msg + 1, bt_addr, 6);
    app_send_message(MSG_FROM_APP, 3, msg);
}

static void bt_app_msg_a2dp_start(u8 *bt_addr)
{
#if TCFG_A2DP_PREEMPTED_ENABLE && TCFG_BT_SUPPORT_PROFILE_A2DP
    /*这里处理有些设备切到后台一直不推a2dp stop，手动切到蓝牙模式后能量检测还在跑，这时候点击设备播放按钮之后，
      能量检测有数据之后结束推APP_MSG_BT_A2DP_START，这种情况需要在这里打开解码*/
#if TCFG_BT_DUAL_CONN_ENABLE
    void *device = get_the_other_device(bt_addr);
    if (device) {
        if (a2dp_player_is_playing(btstack_get_device_mac_addr(device))) {
            bt_action_a2dp_pause(device, btstack_get_device_mac_addr(device));
            bt_action_a2dp_play(btstack_get_conn_device(bt_addr), bt_addr);
            return;
        }
    }
#endif
    app_audio_state_switch(APP_AUDIO_STATE_MUSIC, app_audio_volume_max_query(AppVol_BT_MUSIC), NULL);
    u8 dev_vol = bt_get_music_volume(bt_addr);
    if (dev_vol > 127) {
        dev_vol = app_audio_bt_volume_update(bt_addr, APP_AUDIO_STATE_MUSIC);
    }
    bt_set_music_device_volume(dev_vol);
    rf_coexistence_scene_enter(RF_COEXISTENCE_SCENE_A2DP_PLAY, -1);
    int err = a2dp_player_open(bt_addr);
    if (err == -EBUSY) {
        log_error("bt_app_msg_handler open a2dp_player failed");
        bt_start_a2dp_slience_detect(bt_addr, 50);
    }
#endif
}

