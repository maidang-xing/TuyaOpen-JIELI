#include "btstack/avctp_user.h"
#include "classic/hci_lmp.h"
#include "generic/list.h"
#include "system/timer.h"
#include "event/bt_event.h"
#include "hci_event.h"
#include "app_msg.h"
#include "app_config.h"
#if TCFG_LE_AUDIO_STREAM_ENABLE
#include "wireless_trans.h"
#include "le_audio_recorder.h"
#include "le_broadcast.h"
#include "le_connected.h"
#include "le_audio_player.h"
#endif


#if TCFG_USER_BT_CLASSIC_ENABLE && !TCFG_USER_TWS_ENABLE

#define LOG_TAG             "[DUAL_CONN]"
#define LOG_ERROR_ENABLE
#define LOG_WARN_ENABLE
#define LOG_DEBUG_ENABLE
#define LOG_INFO_ENABLE
#define LOG_CLI_ENABLE
#include "debug.h"


struct page_device_info {
    struct list_head entry;
    u32 timeout;
    u16 timer;
    u8 mac_addr[6];
};

struct dual_conn_handle {
    u16 timer;
    u16 page_scan_timer;
    u16 close_inquiry_scan_timer;
    u8 device_num_recorded;
    u8 remote_addr[3][6];
    u8 page_head_inited;
    u8 page_scan_auto_disable;
    u8 inquiry_scan_disable;
    u8 page_mode_active;
    struct list_head page_head;
};

static struct dual_conn_handle g_dual_conn;

static bool page_list_empty(void)
{
    return list_empty(&g_dual_conn.page_head);
}

static void auto_close_page_scan(void *p)
{
    log_info("auto_close_page_scan");
    g_dual_conn.page_scan_timer = 0;
    g_dual_conn.page_scan_auto_disable = 1;
    lmp_hci_write_scan_enable((0 << 1) | 0);
}

static void write_scan_conn_enable(bool scan_enable, bool conn_enable)
{
    if (g_dual_conn.page_scan_auto_disable) {
        if (!scan_enable && conn_enable) {
            return;
        }
    }

#if (TCFG_BT_DUAL_CONN_ENABLE == 0)
    if (bt_get_total_connect_dev()) {
        return;
    }
#endif

#if ((TCFG_LEA_BIG_CTRLER_TX_EN || TCFG_LEA_BIG_CTRLER_RX_EN) && TCFG_LEA_BIG_RX_CLOSE_EDR_EN)
    if (get_broadcast_role() == BROADCAST_ROLE_RECEIVER) {
        return;
    }
#endif
#if (TCFG_LEA_CIG_CENTRAL_EN || TCFG_LEA_CIG_PERIPHERAL_EN)
#if TCFG_LEA_CIG_CENTRAL_CLOSE_EDR_CONN
    if ((get_connected_role() & CONNECTED_ROLE_CENTRAL) == CONNECTED_ROLE_CENTRAL) {
        return;
    }
#endif
#if TCFG_LEA_CIG_PERIPHERAL_CLOSE_EDR_CONN
    if ((get_connected_role() & CONNECTED_ROLE_PERIP) == CONNECTED_ROLE_PERIP) {
        return;
    }
#endif
#endif

    lmp_hci_write_scan_enable((conn_enable << 1) | scan_enable);

    if ((scan_enable || conn_enable) && page_list_empty()) {
        app_send_message(APP_MSG_BT_IN_PAIRING_MODE, 1, bt_get_total_connect_dev());
    }

#if TCFG_DUAL_CONN_PAGE_SCAN_TIME
    if (conn_enable && !scan_enable) {
        if (g_dual_conn.page_scan_timer) {
            sys_timer_modify(g_dual_conn.page_scan_timer,
                             TCFG_DUAL_CONN_PAGE_SCAN_TIME * 1000);
        } else {
            g_dual_conn.page_scan_timer = sys_timeout_add(NULL, auto_close_page_scan,
                                          TCFG_DUAL_CONN_PAGE_SCAN_TIME * 1000);
        }
    } else {
        if (g_dual_conn.page_scan_timer) {
            sys_timeout_del(g_dual_conn.page_scan_timer);
            g_dual_conn.page_scan_timer = 0;
        }
    }
#endif
}

static void close_inquiry_scan(void *p)
{
    g_dual_conn.inquiry_scan_disable = 1;
    if (g_dual_conn.device_num_recorded == 1 && bt_get_total_connect_dev() == 1) {
        write_scan_conn_enable(0, 0);
    }
    g_dual_conn.close_inquiry_scan_timer = 0;
}

static bool add_device_2_page_list(u8 *mac_addr, u32 timeout)
{
    struct page_device_info *info;

    log_info("add_device_2_page_list: %d", timeout);
    put_buf(mac_addr, 6);

    if (!g_dual_conn.page_head_inited) {
        return 0;
    }

    list_for_each_entry(info, &g_dual_conn.page_head, entry) {
        if (memcmp(info->mac_addr, mac_addr, 6) == 0) {
            if (info->timer) {
                sys_timeout_del(info->timer);
                info->timer = 0;
            }
            info->timeout = jiffies + msecs_to_jiffies(timeout);
            __list_del_entry(&info->entry);
            list_add_tail(&info->entry, &g_dual_conn.page_head);
            return TRUE;
        }
    }

    info = malloc(sizeof(*info));
    if (!info) {
        return FALSE;
    }
    info->timer = 0;
    info->timeout = jiffies + msecs_to_jiffies(timeout);
    memcpy(info->mac_addr, mac_addr, 6);
    list_add_tail(&info->entry, &g_dual_conn.page_head);

    return FALSE;
}

static void del_device_from_page_list(u8 *mac_addr)
{
    struct page_device_info *info;

    if (!g_dual_conn.page_head_inited) {
        return;
    }

    list_for_each_entry(info, &g_dual_conn.page_head, entry) {
        if (memcmp(info->mac_addr, mac_addr, 6) == 0) {
            log_info("del_device");
            put_buf(mac_addr, 6);
            __list_del_entry(&info->entry);
            if (info->timer) {
                sys_timeout_del(info->timer);
            }
            free(info);
            return;
        }
    }
}

static void clr_device_in_page_list(void)
{
    struct page_device_info *info, *n;

    if (!g_dual_conn.page_head_inited) {
        return;
    }

    list_for_each_entry_safe(info, n, &g_dual_conn.page_head, entry) {
        __list_del_entry(&info->entry);
        if (info->timer) {
            sys_timeout_del(info->timer);
        }
        free(info);
    }
}

static u8 *get_device_addr_in_page_list(void)
{
    struct page_device_info *info, *n;
    list_for_each_entry_safe(info, n, &g_dual_conn.page_head, entry) {
        return info->mac_addr;
    }
    return NULL;
}

void dual_conn_state_handler(void)
{
    int connect_device = bt_get_total_connect_dev();
    int have_page_device = page_list_empty() ? FALSE : TRUE;

    log_info("page_state: %d, %d", connect_device, have_page_device);

    if (g_dual_conn.timer) {
        sys_timeout_del(g_dual_conn.timer);
        g_dual_conn.timer = 0;
    }
    if (connect_device == 0) {
        write_scan_conn_enable(1, 1);
    } else if (connect_device == 1) {
#if TCFG_BT_DUAL_CONN_ENABLE
        if (g_dual_conn.device_num_recorded > 1) {
            write_scan_conn_enable(0, 1);
        }
#endif
    }
}

static void page_next_device(void *p);

static void dual_conn_page_device_timeout(void *p)
{
    struct page_device_info *info;

    if (!g_dual_conn.page_head_inited) {
        return;
    }

#if ((TCFG_LEA_BIG_CTRLER_TX_EN || TCFG_LEA_BIG_CTRLER_RX_EN) && TCFG_LEA_BIG_RX_CLOSE_EDR_EN)
    if (get_broadcast_role() == BROADCAST_ROLE_RECEIVER) {
        return;
    }
#endif

#if (TCFG_LEA_CIG_CENTRAL_EN || TCFG_LEA_CIG_PERIPHERAL_EN)

#if TCFG_LEA_CIG_CENTRAL_CLOSE_EDR_CONN
    if ((get_connected_role() & CONNECTED_ROLE_CENTRAL) == CONNECTED_ROLE_CENTRAL) {
        return;
    }
#endif

#if TCFG_LEA_CIG_PERIPHERAL_CLOSE_EDR_CONN
    if ((get_connected_role() & CONNECTED_ROLE_PERIP) == CONNECTED_ROLE_PERIP) {
        return;
    }
#endif

#endif

    /* 参数有效性检查 */
    list_for_each_entry(info, &g_dual_conn.page_head, entry) {
        if (info == p) {
            log_info("page_device_timeout: %lu, %d", jiffies, info->timeout);
            info->timer = 0;
            list_del(&info->entry);
            if (time_after(jiffies, info->timeout)) {
                del_device_from_page_list(info->mac_addr);
                free(info);
            } else {
                list_add_tail(&info->entry, &g_dual_conn.page_head);
            }
            bt_cmd_prepare(USER_CTRL_PAGE_CANCEL, 0, NULL);
            if (!page_list_empty()) {
                if (g_dual_conn.timer) {
                    sys_timeout_del(g_dual_conn.timer);
                    g_dual_conn.timer = 0;
                }
                g_dual_conn.timer = sys_timeout_add(NULL, page_next_device, 2000);
                //增加2s可发现可连接
                write_scan_conn_enable(1, 1);
                g_dual_conn.page_mode_active = 0;
                return;
            }
            g_dual_conn.page_mode_active = 0;
            dual_conn_state_handler();
            break;
        }
    }
}

static void dual_conn_page_device(void)
{
    struct page_device_info *info, *n;

    if (!g_dual_conn.page_head_inited) {
        return;
    }

#if (TCFG_BT_DUAL_CONN_ENABLE == 0)
    if (bt_get_total_connect_dev()) {
        return;
    }
#endif

    list_for_each_entry_safe(info, n, &g_dual_conn.page_head, entry) {
        if (info->timer) {
            return;
        }
        log_info("start_page_device: %lu, %d", jiffies, info->timeout);
        put_buf(info->mac_addr, 6);
        info->timer = sys_timeout_add(info, dual_conn_page_device_timeout,
                                      TCFG_BT_PAGE_TIMEOUT * 1000);
        bt_cmd_prepare(USER_CTRL_START_CONNEC_VIA_ADDR, 6, info->mac_addr);
        g_dual_conn.page_mode_active = 1;
        return;
    }

    dual_conn_state_handler();
}

static void dual_conn_page_devices_init(void)
{
    u8 mac_addr[6];

    INIT_LIST_HEAD(&g_dual_conn.page_head);
    g_dual_conn.page_head_inited = 1;
    g_dual_conn.page_scan_auto_disable = 0;

    int num = btstack_get_num_of_remote_device_recorded();
    for (int i = num - 1; i >= 0 && i + 2 >= num ; i--) {
        btstack_get_remote_addr(mac_addr, i);
        add_device_2_page_list(mac_addr, TCFG_BT_POWERON_PAGE_TIME * 1000);
    }
    g_dual_conn.device_num_recorded = num;
    if (num == 1) {
        memcpy(g_dual_conn.remote_addr[2], mac_addr, 6);
    }

#if TCFG_DUAL_CONN_INQUIRY_SCAN_TIME
    g_dual_conn.inquiry_scan_disable = 0;
    g_dual_conn.close_inquiry_scan_timer = sys_timeout_add(NULL, close_inquiry_scan, TCFG_DUAL_CONN_INQUIRY_SCAN_TIME * 1000);
#else
    g_dual_conn.inquiry_scan_disable = 1;
#endif

    dual_conn_page_device();
}

static void page_next_device(void *p)
{
    g_dual_conn.timer = 0;
    dual_conn_page_device();
}

static void dual_conn_bt_connect_timeout(struct bt_event *bt)
{
    add_device_2_page_list(bt->args, TCFG_BT_TIMEOUT_PAGE_TIME * 1000);

    if (g_dual_conn.timer) {
        sys_timeout_del(g_dual_conn.timer);
        g_dual_conn.timer = 0;
    }
    dual_conn_page_device();
}

static int dual_conn_btstack_event_handler(void *evt)
{
    struct bt_event *event = (struct bt_event *)evt;

    switch (event->event) {
    case BT_STATUS_INIT_OK:
        log_info("DUAL_CONN_BT_STATUS_INIT_OK");
        dual_conn_page_devices_init();
        return 0;
    case BT_STATUS_FIRST_CONNECTED:
        log_info("DUAL_CONN_BT_STATUS_FIRST_CONNECTED");
        if (g_dual_conn.timer) {
            sys_timeout_del(g_dual_conn.timer);
            g_dual_conn.timer = 0;
        }
        del_device_from_page_list(event->args);
        memcpy(g_dual_conn.remote_addr[0], event->args, 6);
        if (!page_list_empty()) {
            g_dual_conn.timer = sys_timeout_add(NULL, page_next_device, 500);
            break;
        }

        g_dual_conn.page_mode_active = 0;
        if (g_dual_conn.device_num_recorded == 0) {
            g_dual_conn.device_num_recorded++;
            memcpy(g_dual_conn.remote_addr[2], event->args, 6);
            break;
        }
        if (g_dual_conn.device_num_recorded == 1) {
            if (memcmp(event->args, g_dual_conn.remote_addr[2], 6) == 0) {
                break;
            }
            g_dual_conn.device_num_recorded++;
        }
#if TCFG_BT_DUAL_CONN_ENABLE
        write_scan_conn_enable(0, 1);
#else
        write_scan_conn_enable(0, 0);
#endif
        break;
    case BT_STATUS_SECOND_CONNECTED:
        log_info("DUAL_CONN_BT_STATUS_SECOND_CONNECTED");
        if (g_dual_conn.device_num_recorded == 1) {
            g_dual_conn.device_num_recorded++;
        }
        if (g_dual_conn.timer) {
            sys_timeout_del(g_dual_conn.timer);
            g_dual_conn.timer = 0;
        }
        clr_device_in_page_list();
        memcpy(g_dual_conn.remote_addr[1], event->args, 6);
        break;
    }

    return FALSE;
}

REGISTER_APP_EVENT_HANDLER(dual_conn_btstack_status_event) = {
    .event      = SYS_BT_EVENT,
    .from       = BT_EVENT_FROM_CON,
    .handler    = dual_conn_btstack_event_handler,
};

static int dual_conn_hci_event_handler(void *evt)
{
    struct bt_event *event = (struct bt_event *)evt;

    switch (event->event) {
    case HCI_EVENT_VENDOR_NO_RECONN_ADDR:
        break;
    case HCI_EVENT_DISCONNECTION_COMPLETE:
        if (event->value == ERROR_CODE_CONNECTION_TIMEOUT) {
            log_info("DUAL_CONN_ERROR_CODE_CONNECTION_TIMEOUT");
            /* put_buf(event->args, 7); */
            if (bt_get_remote_test_flag() == 0) {
                dual_conn_bt_connect_timeout(event);
            }
        }
        break;
    case HCI_EVENT_CONNECTION_COMPLETE:
        switch (event->value) {
        case ERROR_CODE_SUCCESS:
            if (g_dual_conn.timer) {
                sys_timeout_del(g_dual_conn.timer);
                g_dual_conn.timer = 0;
            }
            del_device_from_page_list(event->args);
            return FALSE;
        case ERROR_CODE_CONNECTION_REJECTED_DUE_TO_UNACCEPTABLE_BD_ADDR:
        case ERROR_CODE_CONNECTION_ACCEPT_TIMEOUT_EXCEEDED:
        case ERROR_CODE_CONNECTION_REJECTED_DUE_TO_LIMITED_RESOURCES:
            if (!list_empty(&g_dual_conn.page_head)) {
                struct page_device_info *info;
                info = list_first_entry(&g_dual_conn.page_head,
                                        struct page_device_info, entry);
                list_del(&info->entry);
                list_add_tail(&info->entry, &g_dual_conn.page_head);
            }
            break;
        case ERROR_CODE_PIN_OR_KEY_MISSING:
        case ERROR_CODE_SYNCHRONOUS_CONNECTION_LIMIT_TO_A_DEVICE_EXCEEDED:
        case ERROR_CODE_REMOTE_USER_TERMINATED_CONNECTION:
        case ERROR_CODE_CONNECTION_TERMINATED_BY_LOCAL_HOST:
        case ERROR_CODE_AUTHENTICATION_FAILURE:
            break;
        case ERROR_CODE_PAGE_TIMEOUT:
            break;
        case ERROR_CODE_CONNECTION_TIMEOUT:
            log_info("DUAL_CONN ERROR_CODE_CONNECTION_TIMEOUT 2");
            /* put_buf(event->args, 7); */
            dual_conn_bt_connect_timeout(event);
            break;
        case ERROR_CODE_ACL_CONNECTION_ALREADY_EXISTS:
            if (bt_get_remote_test_flag() == 0) {
                add_device_2_page_list(event->args, TCFG_BT_TIMEOUT_PAGE_TIME * 1000);
                if (g_dual_conn.timer) {
                    sys_timeout_del(g_dual_conn.timer);
                    g_dual_conn.timer = 0;
                }
                dual_conn_page_device();
            }
            break;
        default:
            return FALSE;
        }
        break;
    default:
        return FALSE;
    }

    g_dual_conn.page_scan_auto_disable = 0;
    for (int i = 0; i < 2; i++) {
        if (memcmp(event->args, g_dual_conn.remote_addr[i], 6) == 0) {
            memset(g_dual_conn.remote_addr[i], 0xff, 6);
        }
    }

    bool get_bt_connction_enable_status(void);
    if (get_bt_connction_enable_status()) {
        dual_conn_state_handler();
    }

    return 0;
}

REGISTER_APP_EVENT_HANDLER(dual_conn_hci_event) = {
    .event      = SYS_BT_EVENT,
    .from       = BT_EVENT_FROM_HCI,
    .handler    = dual_conn_hci_event_handler,
};

void dual_conn_page_device_msg_handler(void)
{
    u8 mac_addr[6];
    struct page_device_info *info;
    int device_num = bt_get_total_connect_dev();

    if (!g_dual_conn.page_head_inited) {
        return;
    }

    list_for_each_entry(info, &g_dual_conn.page_head, entry) {
        device_num++;
    }
    if (device_num >= 2) {
        return;
    }

    int num = btstack_get_num_of_remote_device_recorded();
    for (int i = num - 1; i >= 0; i--) {
        btstack_get_remote_addr(mac_addr, i);
        if (memcmp(mac_addr, g_dual_conn.remote_addr[0], 6) == 0) {
            continue;
        }
        if (memcmp(mac_addr, g_dual_conn.remote_addr[1], 6) == 0) {
            continue;
        }
        int ret = add_device_2_page_list(mac_addr, TCFG_BT_POWERON_PAGE_TIME * 1000);
        if (ret == 0) {
            if (++device_num >= 2) {
                break;
            }
        }
    }

    if (g_dual_conn.timer) {
        sys_timeout_del(g_dual_conn.timer);
        g_dual_conn.timer = 0;
    }

    write_scan_conn_enable(0, 0);
    dual_conn_page_device();
}

void dual_conn_close(void)
{
    if (g_dual_conn.timer) {
        sys_timeout_del(g_dual_conn.timer);
        g_dual_conn.timer = 0;
    }
#if TCFG_DUAL_CONN_INQUIRY_SCAN_TIME
    if (g_dual_conn.close_inquiry_scan_timer) {
        sys_timeout_del(g_dual_conn.close_inquiry_scan_timer);
        g_dual_conn.close_inquiry_scan_timer = 0;
    }
#endif
    clr_device_in_page_list();
    write_scan_conn_enable(0, 0);
    bt_cmd_prepare(USER_CTRL_PAGE_CANCEL, 0, NULL);
}

bool check_page_mode_active(void)
{
    return (g_dual_conn.page_mode_active) ? TRUE : FALSE;
}

#endif
