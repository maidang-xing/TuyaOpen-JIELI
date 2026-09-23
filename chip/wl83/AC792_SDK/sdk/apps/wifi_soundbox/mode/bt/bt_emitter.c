#include "app_config.h"
#include "app_msg.h"
#include "btstack/avctp_user.h"
#include "event/bt_event.h"
#include "event/key_event.h"
#include "key/key_driver.h"
#include "hci_event.h"
#include "classic/hci_lmp.h"
#include "asm/rf_coexistence_config.h"
#include "system/timer.h"
#include "os/os_api.h"
#include "syscfg_id.h"

#define LOG_TAG             "[BT_EMITTER]"
#define LOG_ERROR_ENABLE
#define LOG_DEBUG_ENABLE
#define LOG_INFO_ENABLE
#define LOG_CLI_ENABLE
#include "debug.h"

#if TCFG_USER_EMITTER_ENABLE

#define BT_EMITTER_TEST         0
#define BT_EMITTER_PAGE_CNT_MAX 30

#define SEARCH_BD_ADDR_LIMITED 0
#define SEARCH_BD_NAME_LIMITED 1
#define SEARCH_CUSTOM_LIMITED  2
#define SEARCH_NULL_LIMITED    3

#define SEARCH_LIMITED_MODE  SEARCH_BD_NAME_LIMITED

#define REMOTE_SUP_HFP_HF   BIT(4)
#define REMOTE_SUP_HFP_AG   BIT(0)
#define REMOTE_SUP_AUDIO_SINK     BIT(5)
#define REMOTE_SUP_AUDIO_SOURCE   BIT(1)

typedef enum {
    AVCTP_OPID_VOLUME_UP   = 0x41,
    AVCTP_OPID_VOLUME_DOWN = 0x42,
    AVCTP_OPID_MUTE        = 0x43,
    AVCTP_OPID_PLAY        = 0x44,
    AVCTP_OPID_STOP        = 0x45,
    AVCTP_OPID_PAUSE       = 0x46,
    AVCTP_OPID_NEXT        = 0x4B,
    AVCTP_OPID_PREV        = 0x4C,
} AVCTP_CMD_TYPE;

static struct list_head inquiry_noname_list;

struct inquiry_noname_remote {
    struct list_head entry;
    u8 match;
    s8 rssi;
    u8 addr[6];
    u32 class;
};

u8 connect_last_sink_device_from_vm(void);
u8 connect_last_source_device_from_vm(void);
u8 restore_remote_device_info_profile(bd_addr_t mac_addr, u8 device_num, u8 id, u8 profile);
int get_support_profile(bd_addr_t bd_addr, u8 id);
bool get_bt_connction_enable_status(void);

static OS_MUTEX mutex;
static u8 esco_pp_flag;
static u8 bt_search_busy;
static u8 read_name_start;
static u8 a2dp_source_open_flag;
static u16 bt_search_device_timer;
static u16 bt_emitter_page_timer;

extern void dual_conn_user_bt_connect(u8 *addr);

u8 bt_search_status(void)
{
    return bt_search_busy;
}

void bt_search_device(void)
{
    if (bt_search_busy) {
        log_info("bt search busy");
        return;
    }

    if (!get_bt_connction_enable_status()) {
        log_info("bt disbale");
        return;
    }

    bt_cmd_prepare(USER_CTRL_WRITE_CONN_DISABLE, 0, NULL);
    bt_cmd_prepare(USER_CTRL_WRITE_SCAN_DISABLE, 0, NULL);

    log_info("bt_search_start");

#if TCFG_WIFI_ENABLE
    if (bt_get_total_connect_dev() == 0) {
        rf_coexistence_scene_enter(RF_COEXISTENCE_SCENE_INQUIRY_DEVICE, 1300);
    }
#endif

    esco_pp_flag = 0;
    read_name_start = 0;
    bt_search_busy = 1;

    //在同时打开wifi的场景下，搜索设备的时间不宜过长，一般不超过12秒，否则容易出现wifi断开的情况，建议分多次搜索
    u8 inquiry_length = 10;   // inquiry_length * 1.28s
    bt_cmd_prepare(USER_CTRL_SEARCH_DEVICE, 1, &inquiry_length);
}

void bt_search_stop(void)
{
    log_info("bt_search_stop");

    if (bt_search_device_timer) {
        sys_timeout_del(bt_search_device_timer);
        bt_search_device_timer = 0;
    }

    bt_emitter_cmd_prepare(USER_CTRL_INQUIRY_CANCEL, 0, NULL);

    bt_search_busy = 0;
    esco_pp_flag = 0;
}

static void bt_search_device_timer_callback(void *p)
{
    bt_search_device_timer = 0;

    bt_search_device();
}

void emitter_bt_connect(u8 *mac)
{
    if (!get_bt_connction_enable_status()) {
        log_info("bt disbale");
        return;
    }

    lmp_set_sniff_establish_by_remote(1);
    bt_emitter_set_enable_flag(1);

    dual_conn_user_bt_connect(mac);
}


#if (SEARCH_LIMITED_MODE == SEARCH_BD_ADDR_LIMITED)
static const u8 bd_addr_filt[][6] = {
    {0x8E, 0xA7, 0xCA, 0x0A, 0x5E, 0xC8}, /*S10_H*/
    {0xA7, 0xDD, 0x05, 0xDD, 0x1F, 0x00}, /*ST-001*/
    {0xE9, 0x73, 0x13, 0xC0, 0x1F, 0x00}, /*HBS 730*/
    {0x38, 0x7C, 0x78, 0x1C, 0xFC, 0x02}, /*Bluetooth*/
};

/*----------------------------------------------------------------------------*/
/**@brief    蓝牙发射搜索通过地址过滤
   @param    无
   @return   无
   @note
*/
/*----------------------------------------------------------------------------*/
static u8 search_bd_addr_filt(const u8 *addr)
{
    log_info("bd_addr:");
    log_info_hexdump(addr, 6);

    for (u8 i = 0; i < (sizeof(bd_addr_filt) / sizeof(bd_addr_filt[0])); i++) {
        if (memcmp(addr, bd_addr_filt[i], 6) == 0) {
            log_info("bd_addr match: %d", i);
            lmp_set_sniff_establish_by_remote(1);
            bt_emitter_set_enable_flag(1);
            return TRUE;
        }
    }
    /*log_info("bd_addr not match"); */
    return FALSE;
}
#endif

#if (SEARCH_LIMITED_MODE == SEARCH_BD_NAME_LIMITED)
static const char *bd_name_filt[] = {
    "wifi_soundbox_487B",
    "JL-AC79XX-AF0B",
    "Xiaomi Speaker Portable-0025",
    "CAR MULTIMEDIA",
    "MTU-Android",
    "GEELY_BT",
    "Audi_MMI_0303",
    "Clancey",
    "BC8-Android",
    "QCY-T13",
    "T28",
    "Bluetooth music",
    "S16",
    "887",
    "Mi True Wireless Earphones",
    "Redmi AirDots 3 Pro",
    "NSVE T6 Pro",
};

/*----------------------------------------------------------------------------*/
/**@brief    蓝牙发射搜索通过名字过滤
   @param    无
   @return   无
   @note
*/
/*----------------------------------------------------------------------------*/
static u8 search_bd_name_filt(char *data, u8 len, u32 dev_class, char rssi)
{
    char bd_name[64] = {0};

    if ((len > (sizeof(bd_name))) || (len == 0) || !data) {
        log_error("bd_name_len error: %d", len);
        return FALSE;
    }

    memcpy(bd_name, data, len);

    log_info("search_bd_name_filt name: %s, len: %d, class 0x%x, rssi %d", bd_name, len, dev_class, rssi);

    for (u8 i = 0; i < (sizeof(bd_name_filt) / sizeof(bd_name_filt[0])); i++) {
        if (memcmp(data, bd_name_filt[i], len) == 0) {
            log_info("*****find dev ok******");
            lmp_set_sniff_establish_by_remote(1);
            bt_emitter_set_enable_flag(1);
            return TRUE;
        }
    }

    return FALSE;
}
#endif

/*----------------------------------------------------------------------------*/
/**@brief    蓝牙发射搜索结果回调处理
   @param    name : 设备名字
			 name_len: 设备名字长度
			 addr:   设备地址
			 dev_class: 设备类型
			 rssi:   设备信号强度
   @return   无
   @note
 			蓝牙设备搜索结果，可以做名字/地址过滤，也可以保存搜到的所有设备
 			在选择一个进行连接，获取其他你想要的操作。
 			返回TRUE，表示搜到指定的想要的设备，搜索结束，直接连接当前设备
 			返回FALSE，则继续搜索，直到搜索完成或者超时
*/
/*----------------------------------------------------------------------------*/
u8 emitter_search_result(char *name, u8 name_len, u8 *addr, u32 dev_class, char rssi)
{
    if (name) {
        log_info("emitter_search_result name:%s, len:%d, class 0x%x, rssi %d", name, name_len, dev_class, rssi);
    } else {
        log_info("emitter_search_result len:%d, class 0x%x, rssi %d", name_len, dev_class, rssi);
    }

#if (SEARCH_LIMITED_MODE == SEARCH_BD_NAME_LIMITED)
    if (name == NULL) {
        struct inquiry_noname_remote *remote = zalloc(sizeof(struct inquiry_noname_remote));
        if (remote) {
            remote->match = 0;
            remote->class = dev_class;
            remote->rssi = rssi;
            memcpy(remote->addr, addr, 6);
            os_mutex_pend(&mutex, 0);
            list_add_tail(&remote->entry, &inquiry_noname_list);
            if (read_name_start == 0) {
                read_name_start = 1;
                bt_cmd_prepare(USER_CTRL_READ_REMOTE_NAME, 6, addr);
            }
            os_mutex_post(&mutex);
        }
        return FALSE;
    }

    return search_bd_name_filt(name, name_len, dev_class, rssi);
#endif

#if (SEARCH_LIMITED_MODE == SEARCH_BD_ADDR_LIMITED)
    return search_bd_addr_filt(addr);
#endif

#if (SEARCH_LIMITED_MODE == SEARCH_CUSTOM_LIMITED)
    /*以下为搜索结果自定义处理*/
    char bt_name[63] = {0};
    u8 len;
    if (name_len == 0) {
        log_info("No_eir");
    } else {
        len = (name_len > 63) ? 63 : name_len;
        /* display bd_name */
        memcpy(bt_name, name, len);
        log_info("name:%s, len:%d, class 0x%x ,rssi %d", bt_name, name_len, dev_class, rssi);
    }

    /* display bd_addr */
    log_debug_hexdump(addr, 6);

    /* You can connect the specified bd_addr by below api      */
    /* dual_conn_user_bt_connect(addr); */

    return FALSE;
#endif

#if (SEARCH_LIMITED_MODE == SEARCH_NULL_LIMITED)
    lmp_set_sniff_establish_by_remote(1);
    bt_emitter_set_enable_flag(1);
    /*没有指定限制，则搜到什么就连接什么*/
    return TRUE;
#endif
}

/*----------------------------------------------------------------------------*/
/**@brief    蓝牙发射搜索设备没有名字的设备，放进需要获取名字链表
   @param    status : 获取成功     0：获取失败
  			 addr:设备地址
		     name：设备名字
   @return   无
   @note
*/
/*----------------------------------------------------------------------------*/
void emitter_search_noname(u8 status, u8 *addr, char *name)
{
    struct inquiry_noname_remote *remote, *n;

    if (!bt_search_busy) {
        return;
    }

    os_mutex_pend(&mutex, 0);

    if (status) {
        list_for_each_entry_safe(remote, n, &inquiry_noname_list, entry) {
            if (!memcmp(addr, remote->addr, 6)) {
                list_del(&remote->entry);
                free(remote);
            }
        }
        goto __find_next;
    }

    list_for_each_entry_safe(remote, n, &inquiry_noname_list, entry) {
        if (!memcmp(addr, remote->addr, 6)) {
            u8 res = emitter_search_result(name, strlen(name), addr, remote->class, remote->rssi);
            if (res) {
                read_name_start = 0;
                remote->match = 1;
                bt_cmd_prepare(USER_CTRL_INQUIRY_CANCEL, 0, NULL);
                os_mutex_post(&mutex);
                return;
            }
            list_del(&remote->entry);
            free(remote);
        }
    }

__find_next:

    read_name_start = 0;
    remote = NULL;
    if (!list_empty(&inquiry_noname_list)) {
        remote = list_first_entry(&inquiry_noname_list, struct inquiry_noname_remote, entry);
    }

    if (remote) {
        read_name_start = 1;
        bt_cmd_prepare(USER_CTRL_READ_REMOTE_NAME, 6, remote->addr);
    }

    os_mutex_post(&mutex);
}

static void bt_emitter_conn_page_timeout(void *priv)
{
    static u8 page_cnt = 0;

    putchar('e');
    if (bt_emitter_get_connect_status() != BT_STATUS_WAITINT_CONN) {
        //发射器已回连成功，清除
        if (bt_emitter_page_timer) {
            sys_timer_del(bt_emitter_page_timer);
            bt_emitter_page_timer = 0;
        }
        page_cnt = 0;
        return;
    }

    page_cnt++;
    if (page_cnt > BT_EMITTER_PAGE_CNT_MAX) {
        log_info("BT_EMITTER connect last_sink_device fail. Open WRITE_CONN");
        bt_emitter_cmd_prepare(USER_CTRL_WRITE_CONN_ENABLE, 0, NULL);
        if (bt_emitter_page_timer) {
            sys_timer_del(bt_emitter_page_timer);
            bt_emitter_page_timer = 0;
        }
        page_cnt = 0;
    }
}

static void bt_emitter_init(void)
{
    os_mutex_create(&mutex);
    INIT_LIST_HEAD(&inquiry_noname_list);
    bt_inquiry_result_handle_register(emitter_search_result);
    bt_a2dp_source_init(NULL, 0, 1);
#if TCFG_BT_SUPPORT_PROFILE_HFP_AG
    bt_hfp_ag_buf_init(NULL, 0, 1);
#endif
    bt_set_emitter_pin_code_flag(0);
#if TCFG_POWER_ON_ENABLE_EMITTER
    lmp_set_sniff_establish_by_remote(1);
    bt_emitter_set_enable_flag(1);

    if (!connect_last_sink_device_from_vm()) {
        //无连接记录
        bt_search_device();
    } else {
        //有连接记录，创建连接超时函数
        if (!bt_emitter_page_timer) {
            bt_emitter_page_timer = sys_timer_add(NULL, bt_emitter_conn_page_timeout, 1000);
        }
    }
#endif
}

void emitter_search_stop(u8 result)
{
    log_info("%s %d", __func__, result);

    struct inquiry_noname_remote *remote, *n;
    u8 wait_connect_flag = 1;

    os_mutex_pend(&mutex, 0);

    if (!list_empty(&inquiry_noname_list)) {
        bt_cmd_prepare(USER_CTRL_PAGE_CANCEL, 0, NULL);
    }

#if TCFG_WIFI_ENABLE
    rf_coexistence_scene_exit(RF_COEXISTENCE_SCENE_INQUIRY_DEVICE);
#endif

    if (!result) {
        list_for_each_entry_safe(remote, n, &inquiry_noname_list, entry) {
            if (remote->match) {
                lmp_set_sniff_establish_by_remote(1);
                bt_emitter_set_enable_flag(1);
                dual_conn_user_bt_connect(remote->addr);
                wait_connect_flag = 0;
            }
            list_del(&remote->entry);
            free(remote);
        }
    }

    read_name_start = 0;

    if (wait_connect_flag) {
        if (!result) {
            if (!bt_search_device_timer && bt_emitter_get_connect_status() == BT_STATUS_WAITINT_CONN) {
                bt_search_device_timer = sys_timeout_add(NULL, bt_search_device_timer_callback, 1500);
            }
        }
    }

    bt_search_busy = 0;

    os_mutex_post(&mutex);
}

//pin code 轮询功能
static const char pin_code_list[][4] = {
    {'0', '0', '0', '0'},
    {'1', '2', '3', '4'},
    {'8', '8', '8', '8'},
    {'1', '3', '1', '4'},
    {'4', '3', '2', '1'},
    {'1', '1', '1', '1'},
    {'2', '2', '2', '2'},
    {'3', '3', '3', '3'},
    {'5', '6', '7', '8'},
    {'5', '5', '5', '5'},
    {'5', '5', '6', '6'},
};

/*----------------------------------------------------------------------------*/
/**@brief    蓝牙发射链接pincode 轮询
   @param    无
   @return   无
   @note
*/
/*----------------------------------------------------------------------------*/
const char *bt_get_emitter_pin_code(u8 flag)
{
    static u8 index_flag = 0;
    int pincode_num = sizeof(pin_code_list) / sizeof(pin_code_list[0]);
    if (flag == 1) {
        //reset index
        index_flag = 0;
    } else if (flag == 2) {
        //查询是否要开始继续回连尝试pin code。
        if (index_flag + 1 >= pincode_num) {
            //之前已经遍历完了
            return NULL;
        } else {
            index_flag++; //准备使用下一个
        }
    } else {
        log_info("get pin code index %d", index_flag);
    }
    return &pin_code_list[index_flag][0];
}

u8 get_a2dp_source_open_flag(void)
{
    return a2dp_source_open_flag;
}

u8 bt_emitter_stu_set(u8 *addr, u8 pp)
{
    if (pp && (bt_get_total_connect_dev() == 0) && !(bt_emitter_get_curr_channel_state() & A2DP_SRC_CH)) {
        pp = 0;
    }

    log_info("total con dev: %d, pp: %d", bt_get_total_connect_dev(), pp);

    if (pp) {
        //开音频编码
        a2dp_source_open_flag = 1;
        /* sys_timer_add(NULL, printf_malloc, 300); */
        bt_emitter_cmd_prepare(USER_CTRL_AVCTP_OPID_SEND_VOL, 0, NULL);
    } else {
        //关音频编码
        a2dp_source_open_flag = 0;
    }

    bt_emitter_send_media_toggle(NULL, pp);

    return pp;
}

u8 bt_emitter_pp(u8 pp)
{
    return bt_emitter_stu_set(NULL, pp);
}

void emitter_open(void)
{
    bt_emitter_pp(1);
}

void emitter_close(void)
{
    bt_emitter_pp(0);
}

/*----------------------------------------------------------------------------*/
/**@brief    蓝牙发射接收到设备按键消息
   @param    cmd:按键命令
   @return   无
   @note
 			发射器收到接收器发过来的控制命令处理
 			根据实际需求可以在收到控制命令之后做相应的处理
 			蓝牙库里面定义的是weak函数，直接再定义一个同名可获取信息
*/
/*----------------------------------------------------------------------------*/
void emitter_rx_avctp_opid_deal(u8 cmd, u8 id) //属于库的弱函数重写
{
    log_debug("avctp_rx_cmd: 0x%x", cmd);

    struct key_event key = {0};
    key.type = KEY_DRIVER_TYPE_AVCTP;

    switch (cmd) {
    case AVCTP_OPID_NEXT:
        log_info("AVCTP_OPID_NEXT");
        key.action = KEY_EVENT_LONG;
        key.value = KEY_NEXT;
        key_event_notify_no_filter(KEY_EVENT_FROM_KEY, &key);
        break;
    case AVCTP_OPID_PREV:
        log_info("AVCTP_OPID_PREV");
        key.action = KEY_EVENT_LONG;
        key.value = KEY_PREV;
        key_event_notify_no_filter(KEY_EVENT_FROM_KEY, &key);
        break;
    case AVCTP_OPID_PAUSE:
    case AVCTP_OPID_STOP:
        log_info("AVCTP_OPID_PAUSE");
        key.action = KEY_EVENT_CLICK;
        key.value = KEY_PAUSE;
        key_event_notify_no_filter(KEY_EVENT_FROM_KEY, &key);
        break;
    case AVCTP_OPID_PLAY:
        log_info("AVCTP_OPID_PP");
        key.action = KEY_EVENT_CLICK;
        key.value = KEY_PLAY;
        key_event_notify_no_filter(KEY_EVENT_FROM_KEY, &key);
        break;
    case AVCTP_OPID_VOLUME_UP:
        log_info("AVCTP_OPID_VOLUME_UP");
        key.action = KEY_EVENT_CLICK;
        key.value = KEY_VOLUME_INC;
        key_event_notify_no_filter(KEY_EVENT_FROM_KEY, &key);
        break;
    case AVCTP_OPID_VOLUME_DOWN:
        log_info("AVCTP_OPID_VOLUME_DOWN");
        key.action = KEY_EVENT_CLICK;
        key.value = KEY_VOLUME_DEC;
        key_event_notify_no_filter(KEY_EVENT_FROM_KEY, &key);
        break;
    default:
        break;
    }
}

/*----------------------------------------------------------------------------*/
/**@brief    蓝牙发射接收设备同步音量
   @param    vol:接收到设备同步音量
   @return   无
   @note
*/
/*----------------------------------------------------------------------------*/
void emitter_rx_vol_change(u8 vol) //属于库的弱函数重写
{
    log_info("vol_change: %d", vol);
}

////回链耳机音箱
u8 connect_last_sink_device_from_vm(void)
{
    bd_addr_t mac_addr = {0};
    u8 flag = 0;
    flag = restore_remote_device_info_profile(mac_addr, 1, get_remote_dev_info_index(), REMOTE_SINK);
    if (flag && bt_get_connect_state_for_addr(mac_addr) != BT_STATUS_CONNECTING) {
        //connect last conn
        log_info("last source device addr from vm:");
        log_info_hexdump(mac_addr, 6);
        bt_emitter_cmd_prepare(USER_CTRL_START_CONNEC_VIA_ADDR, 6, mac_addr);
    }

    return flag;
}

////回链手机
u8 connect_last_source_device_from_vm(void)
{
    bd_addr_t mac_addr = {0};
    u8 flag = restore_remote_device_info_profile(mac_addr, 1, get_remote_dev_info_index(), REMOTE_SOURCE);

    if (flag && bt_get_connect_state_for_addr(mac_addr) != BT_STATUS_CONNECTING) {
        //connect last conn
        log_info("last source device addr from vm:");
        put_buf(mac_addr, 6);
        dual_conn_user_bt_connect(mac_addr);
    }
    return flag;
}

static int bt_emitter_btstack_event_handler(void *msg)
{
    struct bt_event *bt = (struct bt_event *)msg;

    switch (bt->event) {
    case BT_STATUS_INIT_OK:
        log_info("BT EMITTER INIT");
        bt_emitter_init();
        break;
    case BT_STATUS_CONN_A2DP_CH:
        log_info("EMITTER BT_STATUS_CONN_A2DP_CH :0x%x", bt->value);
        if (bt->value & A2DP_SRC_CH) {
            if (!current_app_in_mode(APP_MODE_BT) && !current_app_in_mode(APP_MODE_SINK)) {
                bt_emitter_pp(1);
            }
        }
        break;
    case BT_STATUS_FIRST_CONNECTED:
#if TCFG_BT_DUAL_CONN_ENABLE && TCFG_POWER_ON_ENABLE_EMITTER
        log_info("EMITTER BT_STATUS_FIRST_CONNECTED");
        int profile = get_support_profile(bt->args, get_remote_dev_info_index());
        if (profile & (REMOTE_SUP_AUDIO_SINK | REMOTE_SUP_HFP_HF)) { //耳机音箱端
            sys_timeout_add(NULL, (void (*)(void *))connect_last_source_device_from_vm, 2000);
        } else if (profile & (REMOTE_SUP_AUDIO_SOURCE | REMOTE_SUP_HFP_AG)) { //手机端
            sys_timeout_add(NULL, (void (*)(void *))connect_last_sink_device_from_vm, 2000);
        }
#endif
        break;
    }
    return 0;
}

REGISTER_APP_EVENT_HANDLER(bt_emitter_btstack_event) = {
    .event      = SYS_BT_EVENT,
    .from       = BT_EVENT_FROM_CON,
    .handler    = bt_emitter_btstack_event_handler,
};

static int bt_emitter_hci_event_handler(void *msg)
{
    struct bt_event *bt = (struct bt_event *)msg;

    switch (bt->event) {
    case HCI_EVENT_INQUIRY_COMPLETE:
        log_info("HCI_EVENT_INQUIRY_COMPLETE");
        emitter_search_stop(bt->value);
        break;
    case HCI_EVENT_USER_CONFIRMATION_REQUEST:
        u8 en = 1;
        bt_emitter_cmd_prepare(USER_CTRL_PAIR, 1, &en);
        break;
    case HCI_EVENT_CONNECTION_COMPLETE:
        switch (bt->value) {
        case ERROR_CODE_SUCCESS:
            log_info("CONNECTION SUCCESS");
            break;
        default:
            break;
        }
    default:
        break;
    }

    return 0;
}

REGISTER_APP_EVENT_HANDLER(bt_emitter_hci_event) = {
    .event      = SYS_BT_EVENT,
    .from       = BT_EVENT_FROM_HCI,
    .handler    = bt_emitter_hci_event_handler,
};

void bt_emitter_esco_pp(void)
{
    if (bt_get_total_connect_dev() == 0) {
        return;
    }
    if (!(bt_emitter_get_curr_channel_state() & HFP_AG_CH)) {
        return;
    }
    if (!esco_pp_flag) {
        esco_pp_flag = 1;
        if (bt_get_call_status() == BT_CALL_HANGUP) {
            bt_emitter_pp(0);
            bt_emitter_cmd_prepare(USER_CTRL_HFP_CALL_LAST_NO, 0, NULL);
            os_time_dly(5);
            bt_emitter_cmd_prepare(USER_CTRL_HFP_CALL_ANSWER, 0, NULL);
        }
    } else {
        esco_pp_flag = 0;
        if (bt_get_call_status() == BT_CALL_INCOMING) {
            bt_emitter_pp(0);
            bt_emitter_cmd_prepare(USER_CTRL_HFP_CALL_ANSWER, 0, NULL);
        } else if (bt_get_call_status() != BT_CALL_HANGUP) {
            bt_emitter_cmd_prepare(USER_CTRL_HFP_CALL_HANGUP, 0, NULL);
        }
    }
}

static int bt_emitter_key_triple_click_event(struct key_event *key)
{
    int ret = FALSE;

    switch (key->value) {
    case KEY_OK:
        bt_search_busy ? bt_search_stop() : bt_search_device();
        ret = TRUE;
        break;
    case KEY_ENC:
    case KEY_POWER:
        bt_emitter_esco_pp();
        ret = TRUE;
        break;
    default:
        break;
    }

    return ret;
}

static int bt_emitter_key_event_handler(void *evt)
{
    struct key_event *key = (struct key_event *)evt;
    int ret = FALSE;

    switch (key->action) {
    case KEY_EVENT_TRIPLE_CLICK:
        ret = bt_emitter_key_triple_click_event(key);
        break;
    default:
        break;
    }

    return ret;
}

REGISTER_APP_EVENT_HANDLER(bt_emitter_key_event) = {
    .event      = SYS_KEY_EVENT,
    .from       = KEY_EVENT_FROM_KEY,
    .handler    = bt_emitter_key_event_handler,
};

#endif

