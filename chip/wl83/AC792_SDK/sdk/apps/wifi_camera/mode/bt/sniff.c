#include "btstack/avctp_user.h"
#include "classic/tws_api.h"
#include "classic/tws_event.h"
#include "classic/hci_lmp.h"
#include "system/timer.h"
#include "event/bt_event.h"
#include "app_msg.h"
#include "app_config.h"

#define LOG_TAG             "[SNIFF]"
#define LOG_ERROR_ENABLE
#define LOG_DEBUG_ENABLE
#define LOG_INFO_ENABLE
#define LOG_CLI_ENABLE
#include "debug.h"

#if TCFG_USER_BT_CLASSIC_ENABLE

static u16 sniff_timer;
static u8 sniff_ready_status; //0:sniff_ready 1:sniff_not_ready

#if TCFG_BT_SNIFF_ENABLE
static u8 sniff_enable = 1;
#else
static u8 sniff_enable = 0;
#endif

#define SNIFF_CNT_TIME                  TCFG_BT_SNIFF_CHECK_TIME  //空闲6S之后进入sniff模式
#define SNIFF_MAX_INTERVALSLOT          800
#define SNIFF_MIN_INTERVALSLOT          100
#define SNIFF_ATTEMPT_SLOT              4
#define SNIFF_TIMEOUT_SLOT              1


bool bt_is_sniff_close(void)
{
    return sniff_timer == 0;
}

static void bt_check_exit_sniff(void)
{
    if (tws_api_get_role() == TWS_ROLE_SLAVE) {
        return;
    }
    bt_cmd_prepare(USER_CTRL_ALL_SNIFF_EXIT, 0, NULL);
}

void bt_sniff_ready_clean(void)
{
    sniff_ready_status = 1;
}

static void bt_check_enter_sniff(void *p)
{
#if TCFG_BT_SNIFF_ENABLE

#if (RCSP_ADV_EN)
    if (get_ble_adv_modify() || get_ble_adv_notify()) {
        return;
    }
#endif

    if (sniff_ready_status) {
        sniff_ready_status = 0;
        return;
    }

#if TCFG_BT_DUAL_CONN_ENABLE
    if (bt_get_esco_coder_busy_flag()) {
        return;
    }
#endif

#if (TCFG_LE_AUDIO_APP_CONFIG & LE_AUDIO_AURACAST_SINK_EN)
    u8 check_local_not_accept_sniff_by_remote(void);
    if (check_local_not_accept_sniff_by_remote()) {
        return;
    }
#endif

    struct sniff_ctrl_config_t config;
    u8 addr[12];
    int conn_cnt = bt_api_enter_sniff_status_check(SNIFF_CNT_TIME, addr);
    ASSERT(conn_cnt <= 2);
    for (int i = 0; i < conn_cnt; i++) {
        log_info("-----USER SEND SNIFF IN %d %d", i, conn_cnt);
        config.sniff_max_interval = SNIFF_MAX_INTERVALSLOT;
        config.sniff_mix_interval = SNIFF_MIN_INTERVALSLOT;
        config.sniff_attemp = SNIFF_ATTEMPT_SLOT;
        config.sniff_timeout  = SNIFF_TIMEOUT_SLOT;
        memcpy(config.sniff_addr, addr + i * 6, 6);
        bt_cmd_prepare(USER_CTRL_SNIFF_IN, sizeof(config), (u8 *)&config);
    }
#endif
}

static void sys_auto_sniff_controle(u8 enable, u8 *addr)
{
    if (addr) {
        if (bt_api_conn_mode_check(enable, addr) == 0) {
            log_info("sniff ctr not change");
            return;
        }
    }

    if (enable) {
        if (!sniff_enable) {
            //sniff_enable为0时不启动定时器去检测进入sniff
            return;
        }

        if (tws_api_get_role_async() == TWS_ROLE_SLAVE) {
            return;
        }
        if (sniff_timer == 0) {
            log_info("check_sniff_enable");
            sniff_timer = sys_timer_add(NULL, bt_check_enter_sniff, 1000);
        }
    } else {
        if (sniff_timer) {
            log_info("check_sniff_disable");
            sys_timeout_del(sniff_timer);
            sniff_timer = 0;
        }
    }
}

void bt_sniff_enable(void)
{
    sniff_enable = 1;
    sys_auto_sniff_controle(1, NULL);
}

void bt_sniff_disable(void)
{
    sys_auto_sniff_controle(0, NULL);
    bt_check_exit_sniff();
    sniff_enable = 0;
}

void bt_sniff_feature_init(void)
{
#if !TCFG_BT_SNIFF_ENABLE
    u8 feature = lmp_hci_read_local_supported_features(0);
    feature &= ~BIT(7); //BIT_SNIFF_MODE;
    lmp_hci_write_local_supported_features(feature, 0);
#endif
}

static int sniff_btstack_event_handler(void *evt)
{
    struct bt_event *event = (struct bt_event *)evt;

    switch (event->event) {
    case BT_STATUS_SECOND_CONNECTED:
    case BT_STATUS_FIRST_CONNECTED:
        sys_auto_sniff_controle(1, event->args);
        break;
    case BT_STATUS_SNIFF_STATE_UPDATE:
        log_info("BT_STATUS_SNIFF_STATE_UPDATE %d", event->value);
        if (event->value == 0) {
            sys_auto_sniff_controle(1, event->args);
            bt_event_notify(BT_EVENT_FROM_USER, event);
        } else {
            sys_auto_sniff_controle(0, event->args);
            bt_event_notify(BT_EVENT_FROM_USER, event);
        }
        break;
    }

    return FALSE;
}

REGISTER_APP_EVENT_HANDLER(sniff_btstack_event) = {
    .event      = SYS_BT_EVENT,
    .from       = BT_EVENT_FROM_CON,
    .handler    = sniff_btstack_event_handler,
};


#if TCFG_USER_TWS_ENABLE

static int sniff_tws_event_handler(void *evt)
{
    struct tws_event *event = (struct tws_event *)evt;

    switch (event->event) {
    case TWS_EVENT_CONNECTION_DETACH:
        break;
    case TWS_EVENT_ROLE_SWITCH:
        if (event->args[0] == TWS_ROLE_MASTER) {
            sys_auto_sniff_controle(1, NULL);
        } else {
            sys_auto_sniff_controle(0, NULL);
        }
        break;
    }

    return FALSE;
}

REGISTER_APP_EVENT_HANDLER(sniff_tws_event) = {
    .event      = SYS_BT_EVENT,
    .from       = BT_EVENT_FROM_TWS,
    .handler    = sniff_tws_event_handler,
};

#endif

#endif
