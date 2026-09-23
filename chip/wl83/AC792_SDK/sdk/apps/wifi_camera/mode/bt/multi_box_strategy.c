#if TCFG_USER_TWS_ENABLE

#if (THIRD_PARTY_PROTOCOLS_SEL & MULTI_BOX_ADV_EN)

#define ROLE_PRIORITY_BIS_EXIST BIT(7)
#define ROLE_PRIORITY_MASTER    BIT(6)
#define ROLE_PRIORITY_ESCO      BIT(5)
#define ROLE_PRIORITY_A2DP      BIT(4)
#define ROLE_PRIORITY_1T2       BIT(3)
#define ROLE_PRIORITY_SINGLE    BIT(2)

#define MULTI_BOX_ADV_TIMER_DETECT_MS           5000
#define MULTI_BOX_ADV_TIMER_CALLBACK_MAX_CNT    3

static void bt_connction_disable(void);
int bt_get_unactive_remote_addr(bd_addr_t addr);

u8 get_bt_multi_box_role(void)
{
    return __this->multi_box_role;
}

void multi_box_bis_change_volume_notify(void)
{
    if (!__this->le_audio_enable || __this->multi_box_role != MULTI_BOX_ROLE_MASTER) {
        return;
    }
    multi_box_adv_all_exit();
    set_multi_box_adv_volume_data(app_audio_get_volume(APP_AUDIO_STATE_MUSIC));
    multi_box_adv_all_init();
}

void multi_box_adv_volume_change(u8 *adv_address, u8 adv_data, u8 volume)
{
    if (!(adv_data & ROLE_PRIORITY_MASTER) || !(adv_data & ROLE_PRIORITY_BIS_EXIST)) {
        return;
    }

    static u8 prev_adv_address[6], prev_volume;

    if (memcmp(prev_adv_address, adv_address, sizeof(prev_adv_address)) || prev_volume != volume) {
        memcpy(prev_adv_address, adv_address,  sizeof(prev_adv_address));
        prev_volume = volume;
        app_audio_set_volume(APP_AUDIO_STATE_MUSIC, volume, 1);
    }
}

static void multi_box_in_bis_notify(u8 role)
{
    u8 adv_data = ROLE_PRIORITY_BIS_EXIST;
    if (role == MULTI_BOX_ROLE_MASTER) {
        adv_data |= ROLE_PRIORITY_MASTER;
        set_multi_box_adv_volume_data(app_audio_get_volume(APP_AUDIO_STATE_MUSIC));
    }
    set_multi_box_adv_data(adv_data);
    set_multi_box_adv_interval_min(500);
    multi_box_adv_all_init();
}

static void multi_box_in_bis_start_notify(u8 role)
{
    multi_box_in_bis_notify(role);

    if (role == MULTI_BOX_ROLE_SLAVE) {
        set_multi_box_scan_param(24, 48);
        multi_box_scan_all_init();
    }
}

void multi_box_bis_role_change(u8 role)
{
    if (!__this->le_audio_enable || __this->multi_box_role_lock ||
        __this->multi_box_role == role || __this->multi_box_role == MULTI_BOX_ROLE_UNKNOWN) {
        return;
    }

    __this->multi_box_role = role;
    syscfg_write(VM_MULTI_BOX_ROLE_INDEX, &__this->multi_box_role, sizeof(__this->multi_box_role));

    multi_box_adv_all_exit();
    multi_box_scan_all_exit();
    clear_multi_box_mac_list();
    multi_box_in_bis_start_notify(role);
}

static void bt_tws_disconnect_1T2_inactive_device(void)
{
    bd_addr_t bt_addr;

    if (bt_get_total_connect_dev() > 1) {
        if (0 == bt_get_unactive_remote_addr(bt_addr)) {
            bt_cmd_prepare(USER_CTRL_DISCONNECTION_HCI, 6, bt_addr);
        }
    }
}

static void multi_box_adv_timer_callback(void *p)
{
    u8 role = get_multi_box_role();
    if (__this->multi_box_role == MULTI_BOX_ROLE_UNKNOWN && role == MULTI_BOX_ROLE_SLAVE) {
        __this->multi_box_role = role;
        syscfg_write(VM_MULTI_BOX_ROLE_INDEX, &__this->multi_box_role, sizeof(__this->multi_box_role));

        log_info("get_multi_box_number : %d, %d", get_multi_box_number(), __LINE__);

        if (get_multi_box_number() == 1 && !check_multi_box_bis_is_exist()) {
#if !TCFG_BT_CONNECTION_CLOSE_ALL
            bt_connction_disable();
#endif
            bt_tws_enable();
        } else {
            __this->le_audio_enable = TRUE;
            syscfg_write(VM_LE_AUDIO_ONOFF_INDEX, &__this->le_audio_enable, sizeof(__this->le_audio_enable));
            multi_box_scan_all_exit();
            clear_multi_box_mac_list();
            if (check_multi_box_bis_is_exist()) {
                if (__this->multi_box_adv_timer) {
                    sys_timer_del(__this->multi_box_adv_timer);
                    __this->multi_box_adv_timer = 0;
                }
                multi_box_adv_all_exit();
                multi_box_in_bis_notify(__this->multi_box_role);
            }
            le_audio_switch_onoff();
            set_multi_box_scan_param(24, 48);
            multi_box_scan_all_init();
        }
    } else if (__this->multi_box_role == MULTI_BOX_ROLE_UNKNOWN && role == MULTI_BOX_ROLE_MASTER) {
        u8 adv_data = get_multi_box_adv_data() | ROLE_PRIORITY_MASTER;

        __this->multi_box_role = role;
        syscfg_write(VM_MULTI_BOX_ROLE_INDEX, &__this->multi_box_role, sizeof(__this->multi_box_role));

        log_info("get_multi_box_number : %d, %d", get_multi_box_number(), __LINE__);

        if (get_multi_box_number() == 1) {
            bt_tws_enable();
        } else {
            __this->le_audio_enable = TRUE;
            syscfg_write(VM_LE_AUDIO_ONOFF_INDEX, &__this->le_audio_enable, sizeof(__this->le_audio_enable));
            adv_data |= ROLE_PRIORITY_BIS_EXIST;
            multi_box_scan_all_exit();
            clear_multi_box_mac_list();
            bt_tws_disconnect_1T2_inactive_device();
            __this->multi_box_role_lock = TRUE;
            le_audio_switch_onoff();
            __this->multi_box_role_lock = FALSE;
        }

        multi_box_adv_all_exit();

        if (__this->multi_box_adv_cnt < MULTI_BOX_ADV_TIMER_CALLBACK_MAX_CNT - 1) {
            if (__this->le_audio_enable) {
                set_multi_box_adv_volume_data(app_audio_get_volume(APP_AUDIO_STATE_MUSIC));
            }
            set_multi_box_adv_data(adv_data);
            multi_box_adv_all_init();
        }

        if (APP_MODE_PC == get_current_app_mode()) {
            app_msg_handler("pc_music", APP_MSG_RESUME);
        }
    } else if (__this->multi_box_role != MULTI_BOX_ROLE_UNKNOWN) {
        if (gtws.active && get_multi_box_number() > 1) {
            log_info("get_multi_box_number : %d, %d", get_multi_box_number(), __LINE__);
            bt_tws_detach_and_remove_pairs();
            bt_tws_disable();
            if (__this->multi_box_role == MULTI_BOX_ROLE_SLAVE) {
                multi_box_scan_all_exit();
                multi_box_adv_all_exit();
                clear_multi_box_mac_list();
                set_multi_box_scan_param(24, 48);
                multi_box_scan_all_init();
            } else if (__this->multi_box_adv_cnt < MULTI_BOX_ADV_TIMER_CALLBACK_MAX_CNT - 1) {
                multi_box_scan_all_exit();
                multi_box_adv_all_exit();
                clear_multi_box_mac_list();
                u8 adv_data = get_multi_box_adv_data() | ROLE_PRIORITY_BIS_EXIST;
                set_multi_box_adv_data(adv_data);
                multi_box_adv_all_init();
            }
            if (__this->multi_box_role == MULTI_BOX_ROLE_MASTER) {
                bt_tws_disconnect_1T2_inactive_device();
                __this->multi_box_role_lock = TRUE;
            }
            __this->le_audio_enable = TRUE;
            syscfg_write(VM_LE_AUDIO_ONOFF_INDEX, &__this->le_audio_enable, sizeof(__this->le_audio_enable));
            le_audio_switch_onoff();
            __this->multi_box_role_lock = FALSE;
        }
    }

    if (++__this->multi_box_adv_cnt >= MULTI_BOX_ADV_TIMER_CALLBACK_MAX_CNT) {
        if (__this->multi_box_adv_timer) {
            sys_timer_del(__this->multi_box_adv_timer);
            __this->multi_box_adv_timer = 0;
        }

        if (__this->multi_box_role == MULTI_BOX_ROLE_UNKNOWN) {
            //配对超时
            multi_box_scan_all_exit();
            multi_box_adv_all_exit();
            clear_multi_box_mac_list();
            __this->pair_enable = FALSE;
            lmp_hci_write_scan_enable(BIT(1));

            if (APP_MODE_PC == get_current_app_mode()) {
                app_msg_handler("pc_music", APP_MSG_RESUME);
            }
        } else {
            multi_box_adv_all_exit();
            if (gtws.active || __this->multi_box_role == MULTI_BOX_ROLE_MASTER) {
                multi_box_scan_all_exit();
                clear_multi_box_mac_list();
            }
            if (__this->le_audio_enable) {
                multi_box_in_bis_notify(__this->multi_box_role);
            }
        }
    }
}

#endif

static void multiple_bt_pair_start(void)
{
#if (THIRD_PARTY_PROTOCOLS_SEL & MULTI_BOX_ADV_EN)
    u8 adv_data = 0;

    if (esco_player_runing()) {
        adv_data |= ROLE_PRIORITY_ESCO;
    }
    if (a2dp_player_runing()) {
        adv_data |= ROLE_PRIORITY_A2DP;
    }
    if (bt_get_total_connect_dev() > 1) {
        adv_data |= ROLE_PRIORITY_1T2;
    }
    if (bt_get_total_connect_dev() > 0) {
        adv_data |= ROLE_PRIORITY_SINGLE;
    }

    app_mode_t mode = get_current_app_mode();
    if (mode == APP_MODE_BT) {
        adv_data |= BIT(1) | BIT(0);
    } else if (mode == APP_MODE_NET) {
        adv_data |= BIT(1);
    } else if (mode == APP_MODE_LOCAL) {
        adv_data |= BIT(0);
    }

    reset_multi_box_number();
    clear_multi_box_mac_list();
    set_multi_box_role(MULTI_BOX_ROLE_UNKNOWN);
    set_multi_box_adv_data(adv_data);
    set_multi_box_adv_interval_min(100);
    set_multi_box_scan_param(16, 24);

    app_msg_handler(NULL, APP_MSG_SUSPEND);

    lmp_hci_write_scan_enable(0);

    multi_box_adv_all_init();

    multi_box_scan_all_init();

    __this->pair_enable = TRUE;
    __this->multi_box_role = MULTI_BOX_ROLE_UNKNOWN;
    __this->multi_box_adv_cnt = 0;
    __this->multi_box_adv_timer = sys_timer_add(NULL, multi_box_adv_timer_callback, MULTI_BOX_ADV_TIMER_DETECT_MS);

    return;
#endif

    app_msg_handler(NULL, APP_MSG_SUSPEND);

    bt_tws_enable();

    lmp_hci_write_scan_enable(0);

    __this->pair_enable = TRUE;
}

static void multiple_bt_pair_remove(void)
{
#if (THIRD_PARTY_PROTOCOLS_SEL & MULTI_BOX_ADV_EN)
    if (__this->multi_box_adv_timer) {
        sys_timer_del(__this->multi_box_adv_timer);
        __this->multi_box_adv_timer = 0;
    }
    multi_box_scan_all_exit();
    clear_multi_box_mac_list();
    reset_multi_box_number();
    multi_box_adv_all_exit();
#endif

    if (gtws.active) {
        u8 page_device = tws_api_get_tws_state() & TWS_STA_SIBLING_CONNECTED ? 0 : 1;

        bt_tws_detach_and_remove_pairs();

        bt_tws_disable();

        if (page_device) {
            app_send_message(APP_MSG_BT_PAGE_DEVICE, 0);
        }

        __this->pair_enable = FALSE;
#if (THIRD_PARTY_PROTOCOLS_SEL & MULTI_BOX_ADV_EN)
    } else {
        __this->pair_enable = FALSE;
        if (__this->le_audio_enable) {
            __this->le_audio_enable = FALSE;
            le_audio_switch_onoff();
            syscfg_write(VM_LE_AUDIO_ONOFF_INDEX, &__this->le_audio_enable, sizeof(__this->le_audio_enable));
        }
        lmp_hci_write_scan_enable(BIT(1));
#endif
    }

#if (THIRD_PARTY_PROTOCOLS_SEL & MULTI_BOX_ADV_EN)
    __this->multi_box_role = MULTI_BOX_ROLE_UNKNOWN;
    syscfg_write(VM_MULTI_BOX_ROLE_INDEX, &__this->multi_box_role, sizeof(__this->multi_box_role));
#endif
}
#endif

