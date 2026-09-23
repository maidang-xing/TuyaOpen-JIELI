#include "system/timer.h"
#include "key/key_driver.h"
#include "event/bt_event.h"
#include "event/device_event.h"
#include "app_tone.h"
#include "a2dp_player.h"
#include "btstack/avctp_user.h"
#include "classic/hci_lmp.h"
#include "bt_tws.h"
#include "app_power_manage.h"
#include "syscfg/syscfg_id.h"
#include "user_cfg_id.h"
#include "bt_slience_detect.h"
#include "esco_recoder.h"
#include "update.h"
#include "audio_config.h"
#include "app_config.h"
#if TCFG_LOCAL_TWS_ENABLE
#include "local_tws.h"
#endif


#if (TCFG_USER_TWS_ENABLE && TCFG_APP_BT_EN)

#if TCFG_LOCAL_TWS_ENABLE
#define CONFIG_BT_TWS_SNIFF                  0       //[WIP]
#else
#define CONFIG_BT_TWS_SNIFF                  0       //[WIP]
#endif

#define BT_TWS_UNPAIRED                      0x0001
#define BT_TWS_PAIRED                        0x0002
#define BT_TWS_WAIT_SIBLING_SEARCH           0x0004
#define BT_TWS_SEARCH_SIBLING                0x0008
#define BT_TWS_CONNECT_SIBLING               0x0010
#define BT_TWS_SIBLING_CONNECTED             0x0020
#define BT_TWS_PHONE_CONNECTED               0x0040
#define BT_TWS_POWER_ON                      0x0080
#define BT_TWS_TIMEOUT                       0x0100
#define BT_TWS_AUDIO_PLAYING                 0x0200
#define BT_TWS_DISCON_DLY_TIMEOUT            0x0400
#define BT_TWS_REMOVE_PAIRS                  0x0800

struct tws_user_var {
    u8 addr[6];
    u16 state;
    u8  active;
    u8  device_role;  //tws 记录那个是active device 活动设备，音源控制端
    u16 sniff_timer;
    u16 ble_try_switch_timer;
    u16 tws_device_indicate;    /*设置对箱搜索标识，inquiry时候用,搜索到相应的标识才允许连接*/
};

static struct tws_user_var gtws;

static void multiple_bt_pair_remove(void);
static void tws_sniff_controle_check_enable(void);
static void tws_sniff_controle_check_disable(void);
void get_random_number(u8 *ptr, u8 len);

u8 bt_tws_active(void)
{
    return gtws.active;
}

void bt_tws_set_active(u8 status)
{
    gtws.active = status;
}

u16 bt_tws_get_state(void)
{
    return gtws.state;
}

void tws_set_search_sbiling_state(u8 state)
{
    if (state) {
        gtws.state |= BT_TWS_SEARCH_SIBLING;
    } else {
        gtws.state &= ~BT_TWS_SEARCH_SIBLING;
    }
}

u16 tws_host_get_battery_voltage(void)
{
    u16 get_vbat_value(void);
    return get_vbat_value();
}

bool tws_host_role_switch_by_power_balance(u16 m_voltage, u16 s_voltage)
{
    if (m_voltage + 100 <= s_voltage) {
        return TRUE;
    }

    return FALSE;
}

int tws_host_role_switch_by_power_update_time(void)
{
    return (60 * 1000);
}

void bt_get_tws_local_addr(u8 *addr)
{
    u8 mac_addr[6];
    int len = syscfg_read(CFG_TWS_LOCAL_ADDR, mac_addr, sizeof(mac_addr));
    if (len != sizeof(mac_addr)) {
        get_random_number(mac_addr, sizeof(mac_addr));
        syscfg_write(CFG_TWS_LOCAL_ADDR, mac_addr, sizeof(mac_addr));
    }

    log_info("tws_local_mac:");
    put_buf(mac_addr, sizeof(mac_addr));

    if (addr) {
        memcpy(addr, mac_addr, sizeof(mac_addr));
    }
}

/*
 * 获取左右耳信息
 * 'L': 左耳
 * 'R': 右耳
 * 'U': 未知
 */
static char bt_tws_get_local_channel(void)
{
    return __this->tws_channel;
}

int tws_host_channel_match(char remote_channel)
{
    /*r_printf("tws_host_channel_match: %c, %c\n", remote_channel,
             bt_tws_get_local_channel());*/
#if TCFG_BT_TWS_CHANNEL_SELECT == CONFIG_TWS_START_PAIR_AS_LEFT || \
    TCFG_BT_TWS_CHANNEL_SELECT == CONFIG_TWS_START_PAIR_AS_RIGHT || \
    TCFG_BT_TWS_CHANNEL_SELECT == CONFIG_TWS_MASTER_AS_LEFT || \
    TCFG_BT_TWS_CHANNEL_SELECT == CONFIG_TWS_MASTER_AS_RIGHT || \
    TCFG_BT_TWS_CHANNEL_SELECT == CONFIG_TWS_CHANNEL_SELECT_BY_BOX
    return 1;
#else
    if (remote_channel != bt_tws_get_local_channel()) {
        return 1;
    }
#endif

    return 0;
}

char tws_host_get_local_channel(void)
{
    char channel;

#if (TCFG_BT_TWS_CHANNEL_SELECT == CONFIG_TWS_START_PAIR_AS_RIGHT)
    if (gtws.state & BT_TWS_SEARCH_SIBLING) {
        return 'R';
    }
#elif (TCFG_BT_TWS_CHANNEL_SELECT == CONFIG_TWS_START_PAIR_AS_LEFT)
    if (gtws.state & BT_TWS_SEARCH_SIBLING) {
        return 'L';
    }
#endif
    channel = bt_tws_get_local_channel();
    if (channel != 'R') {
        channel = 'L';
    }
    /*y_printf("tws_host_get_local_channel: %c\n", channel);*/

    return channel;
}

#if CONFIG_TWS_COMMON_ADDR_SELECT == CONFIG_TWS_COMMON_ADDR_USED_LEFT
void tws_host_get_common_addr(u8 *remote_mac_addr, u8 *common_addr, char channel)
{
    if (channel == 'L') {
        memcpy(common_addr, bt_get_mac_addr(), 6);
    } else {
        memcpy(common_addr, remote_mac_addr, 6);
    }
}
#endif

#if TCFG_TWS_USE_COMMMON_ADDR == 0
void tws_host_get_common_addr(u8 *remote_mac_addr, u8 *common_addr, char channel)
{
    log_info("gtws_state:%x", gtws.state);

    memcpy(common_addr, bt_get_mac_addr(), 6);
    /* if ((gtws.state & BT_TWS_PHONE_CONNECTED)) {          //如果开了CONFIG_TWS_PAIR_ALWAYS,则手机连接的情况使用跟手机端连接的设备的地址作为公共地址 */
    /*     memcpy(common_addr, bt_get_mac_addr(), 6); */
    /* } else if (gtws.state & BT_TWS_PAIRED) { */
    /*     syscfg_read(CFG_TWS_COMMON_ADDR, common_addr, 6); */
    /* } else if (gtws.state & BT_TWS_SEARCH_SIBLING){ */
    /*     memcpy(common_addr, bt_get_mac_addr(), 6); */
    /* } */
    log_info("host_get_common_addr:");
    put_buf(common_addr, 6);
}

int tws_host_get_local_role(void)
{
    return __this->tws_role | tws_api_get_tws_state() << 8;
}

/*从机跑这里，返回ture为需要进行role_switch变成主机*/
bool tws_host_role_switch(int remote_info, int local_info)
{
    u8 remote_want_role = remote_info & 0xff;
    u16 remote_gtws_state = remote_info >> 8;
    u8 local_want_role = local_info & 0xff;
    u16 local_gtws_state = local_info >> 8;

    log_info("remote_role :0x%x current_role:0x%x remote_state:%x local_state:%x", remote_want_role, local_want_role, remote_gtws_state, local_gtws_state);

    /*主从角色分配顺序: 连接手机  > 发起配对 > VM记录*/

    /*1、判断哪边连了手机*/
    if (remote_gtws_state & TWS_STA_PHONE_CONNECTED && !(local_gtws_state & TWS_STA_PHONE_CONNECTED)) {       /*对方连手机， 本地没连手机*/
        return FALSE;
    } else if (!(remote_gtws_state & TWS_STA_PHONE_CONNECTED) && (local_gtws_state & TWS_STA_PHONE_CONNECTED)) { /*对方没连手机，本地连手机*/
        return TRUE;
    } else if (remote_gtws_state & TWS_STA_PHONE_CONNECTED && (local_gtws_state & TWS_STA_PHONE_CONNECTED)) { /*对方连手机，本地连手机, 需要断开*/
        //do detach
        return FALSE;
    }

    if (gtws.state & BT_TWS_SEARCH_SIBLING) {
        return TRUE;
    }
    /*3、最后再判断VM记录*/
    if (local_want_role == TWS_ROLE_MASTER && remote_want_role == TWS_ROLE_SLAVE) {
        return TRUE;
    }

    return FALSE;
}
#endif

bool get_bt_tws_connect_status(void)
{
    if (gtws.state & BT_TWS_SIBLING_CONNECTED) {
        return TRUE;
    }

    return FALSE;
}

bool bt_tws_is_paired(void)
{
    return gtws.state & BT_TWS_PAIRED;
}

static int tws_get_sibling_addr(u8 *addr, int *result)
{
    u8 all_ff[6] = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF};

    int len = syscfg_read(CFG_TWS_REMOTE_ADDR, addr, 6);
    if (len != 6 || !memcmp(addr, all_ff, 6)) {
        *result = len;
        return -ENOENT;
    }

    return 0;
}

static void send_tws_event(int argc, u8 *argv)
{
    ASSERT(((u32)argv & 0x3) == 0);

    sys_event_notify(SYS_BT_EVENT, BT_EVENT_FROM_TWS, argv, argc);
}

static u8 set_channel_by_code_or_res(void)
{
    u8 count = 0;
    char channel = 0;
    char last_channel = 0;

#if (TCFG_BT_TWS_CHANNEL_SELECT == CONFIG_TWS_EXTERN_UP_AS_LEFT) || \
    (TCFG_BT_TWS_CHANNEL_SELECT == CONFIG_TWS_EXTERN_UP_AS_RIGHT)
    if (TCFG_TWS_CHANNEL_CHECK_IO != -1) {
        gpio_set_mode(TCFG_TWS_CHANNEL_CHECK_IO, GPIO_INPUT_PULL_DOWN_10K);
        for (int i = 0; i < 5; i++) {
            os_time_dly(2);
            if (gpio_read(TCFG_TWS_CHANNEL_CHECK_IO)) {
                count++;
            }
        }
        gpio_set_mode(TCFG_TWS_CHANNEL_CHECK_IO, GPIO_HIGHZ);
    }
#if (TCFG_BT_TWS_CHANNEL_SELECT == CONFIG_TWS_EXTERN_UP_AS_LEFT)
    channel = (count >= 3) ? 'L' : 'R';
#else
    channel = (count >= 3) ? 'R' : 'L';
#endif
#elif (TCFG_BT_TWS_CHANNEL_SELECT == CONFIG_TWS_EXTERN_DOWN_AS_LEFT) || \
    (TCFG_BT_TWS_CHANNEL_SELECT == CONFIG_TWS_EXTERN_DOWN_AS_RIGHT)
    if (TCFG_TWS_CHANNEL_CHECK_IO != -1) {
        gpio_set_mode(TCFG_TWS_CHANNEL_CHECK_IO, GPIO_INPUT_PULL_UP_10K);
        for (int i = 0; i < 5; i++) {
            os_time_dly(2);
            if (gpio_read(TCFG_TWS_CHANNEL_CHECK_IO)) {
                count++;
            }
        }
        gpio_set_mode(TCFG_TWS_CHANNEL_CHECK_IO, GPIO_INPUT_PULL_UP_10K);
    }
#if (TCFG_BT_TWS_CHANNEL_SELECT == CONFIG_TWS_EXTERN_DOWN_AS_LEFT)
    channel = (count >= 3) ? 'R' : 'L';
#else
    channel = (count >= 3) ? 'L' : 'R';
#endif
#elif (TCFG_BT_TWS_CHANNEL_SELECT == CONFIG_TWS_AS_LEFT)
    channel = 'L';
#elif (TCFG_BT_TWS_CHANNEL_SELECT == CONFIG_TWS_AS_RIGHT)
    channel = 'R';
#endif

#if (THIRD_PARTY_PROTOCOLS_SEL & MULTI_BOX_ADV_EN) && (TCFG_BT_TWS_CHANNEL_SELECT == CONFIG_TWS_MASTER_AS_LEFT)
    if (__this->multi_box_role == MULTI_BOX_ROLE_MASTER) {
        channel = 'L';
    } else if (__this->multi_box_role == MULTI_BOX_ROLE_SLAVE) {
        channel = 'R';
    }
#endif

    // cppcheck-suppress knownConditionTrueFalse
    if (channel) {
        syscfg_read(CFG_TWS_CHANNEL, &last_channel, 1);
        if (channel != last_channel) {
            __this->tws_channel = channel;
            syscfg_write(CFG_TWS_CHANNEL, &channel, 1);
        }
        tws_api_set_local_channel(channel);
        return 1;
    }

    return 0;
}

static void bt_set_pair_code_en(u8 en)
{
    if (en) {
        tws_api_set_pair_code(gtws.tws_device_indicate);
    } else {
        tws_api_set_pair_code(gtws.tws_device_indicate + 1);
    }
}

static void bt_tws_enable(void)
{
    if (gtws.active) {
        return;
    }

    gtws.state = BT_TWS_POWER_ON;

    int result = 0;
    u8 addr[6];
    int err = tws_get_sibling_addr(addr, &result);
    if (err == 0) {
        /* 获取到对方地址, 开始连接 */
        log_info("have tws info:");
        put_buf(addr, 6);

        gtws.state |= BT_TWS_PAIRED;

        app_send_message(APP_MSG_TWS_PAIRED, 0);

        tws_api_set_sibling_addr(addr);

        if (set_channel_by_code_or_res() == 0) {
            char channel = bt_tws_get_local_channel();
            tws_api_set_local_channel(channel);
        }

        syscfg_read(CFG_TWS_COMMON_ADDR, addr, 6);

        tws_api_set_quick_connect_addr(addr);
    } else {
        log_info("no tws info");

        app_send_message(APP_MSG_TWS_UNPAIRED, 0);

        gtws.state |= BT_TWS_UNPAIRED;

#if (THIRD_PARTY_PROTOCOLS_SEL & MULTI_BOX_ADV_EN) && (TCFG_BT_TWS_CHANNEL_SELECT == CONFIG_TWS_MASTER_AS_LEFT)
        if (__this->multi_box_role == MULTI_BOX_ROLE_MASTER) {
            log_info("multi box role is master");
            __this->tws_role = TWS_ROLE_MASTER;
            syscfg_write(VM_TWS_ROLE_INDEX, &__this->tws_role, 1);
        } else if (__this->multi_box_role == MULTI_BOX_ROLE_SLAVE) {
            log_info("multi box role is slave");
            __this->tws_role = TWS_ROLE_SLAVE;
            syscfg_write(VM_TWS_ROLE_INDEX, &__this->tws_role, 1);
        }
#endif

        if (set_channel_by_code_or_res() == 0) {
            tws_api_set_local_channel('U');
        }

#if ((TCFG_BT_TWS_PAIR_MODE == CONFIG_TWS_PAIR_BY_CLICK) && (TCFG_TWS_PAIR_BY_BOTH_SIDES == 0))
        app_send_message(APP_MSG_TWS_START_PAIR, 0);
#endif
    }

    gtws.active = TRUE;

    syscfg_write(VM_TWS_ONOFF_INDEX, &gtws.active, sizeof(gtws.active));
}

static void bt_tws_disable(void)
{
    if (!gtws.active) {
        return;
    }

    gtws.active = FALSE;

    tws_delete_pair_timer();
    tws_api_cancel_all();
    tws_api_cancle_create_connection();
    tws_api_cancle_wait_pair();

    if (tws_api_get_role() == TWS_ROLE_MASTER) {
        send_page_device_addr_2_sibling();

        tws_api_detach((TCFG_TWS_USE_COMMMON_ADDR) ? TWS_DETACH_BY_POWEROFF : TWS_DETACH_BY_LOCAL, 5000);   //这里不等完全断开的话，退出蓝牙模式把资源全部释放之后如果还没断完，底层的状态就乱了,这里是应用BY_LOCAL是为了不进行主从切换
    } else {
        tws_api_detach(TWS_DETACH_BY_POWEROFF, 5000);   //这里不等完全断开的话，退出蓝牙模式把资源全部释放之后如果还没断完，底层的状态就乱了
    }

    gtws.state = 0;

    gtws.active = FALSE;

    syscfg_write(VM_TWS_ONOFF_INDEX, &gtws.active, sizeof(gtws.active));
}

static int bt_tws_poweron(void)
{
    if (gtws.state & BT_TWS_POWER_ON) {
        return 0;
    }

#if TCFG_NORMAL_SET_DUT_MODE
    bt_cmd_prepare(USER_CTRL_WRITE_SCAN_ENABLE, 0, NULL);
    bt_cmd_prepare(USER_CTRL_WRITE_CONN_ENABLE, 0, NULL);
    return 0;
#endif

    tws_api_set_event_handler(send_tws_event);

#if TCFG_TWS_USE_COMMMON_ADDR == 0
    tws_api_common_addr_en(0);
#endif

    gtws.state = BT_TWS_POWER_ON;

    u16 pair_code = 0xAABB;
    syscfg_read(CFG_TWS_PAIR_CODE_ID, &pair_code, 2);
    tws_api_set_pair_code(pair_code);
    gtws.tws_device_indicate = pair_code;

    __this->tws_role = 0xff;
    syscfg_read(VM_TWS_ROLE_INDEX, &__this->tws_role, sizeof(__this->tws_role));

    __this->tws_channel = 'U';
    syscfg_read(CFG_TWS_CHANNEL, &__this->tws_channel, sizeof(__this->tws_channel));

    syscfg_read(VM_TWS_ONOFF_INDEX, &gtws.active, sizeof(gtws.active));

    __this->pair_enable = gtws.active;

    bt_get_mac_addr();

#if TCFG_TWS_AUTO_ROLE_SWITCH_ENABLE
    tws_api_auto_role_switch_enable();
#else
    tws_api_auto_role_switch_disable();
#endif

#if TCFG_TWS_PAIR_BY_BOTH_SIDES
    bt_set_pair_code_en(0);
#endif

    /* tws_api_auto_role_switch_disable(); */
    /* bt_set_low_latency_mode(1,1);//开机默认低延时模式设置 */

    int result = 0;
    u8 addr[6];
    int err = tws_get_sibling_addr(addr, &result);
    if (err == 0) {
        /* 获取到对方地址, 开始连接 */
        log_info("have tws info:");
        put_buf(addr, 6);

        gtws.state |= BT_TWS_PAIRED;

        app_send_message(APP_MSG_TWS_PAIRED, 0);

        tws_api_set_sibling_addr(addr);

        if (set_channel_by_code_or_res() == 0) {
            char channel = bt_tws_get_local_channel();
            tws_api_set_local_channel(channel);
        }

        syscfg_read(CFG_TWS_COMMON_ADDR, addr, 6);

        tws_api_set_quick_connect_addr(addr);
    } else {
        log_info("no tws info");

        app_send_message(APP_MSG_TWS_UNPAIRED, 0);

        gtws.state |= BT_TWS_UNPAIRED;

        if (set_channel_by_code_or_res() == 0) {
            tws_api_set_local_channel('U');
        }
    }

    return 0;
}

static int bt_tws_phone_connected(void)
{
    log_info("bt_tws_phone_connected: %x", gtws.state);

    gtws.state |= BT_TWS_PHONE_CONNECTED;
    app_send_message(APP_MSG_BT_CLOSE_PAGE_SCAN, 0);

    return 0;
}

static void bt_tws_phone_disconnected(void)
{
    gtws.state &= ~BT_TWS_PHONE_CONNECTED;

    log_info("bt_tws_phone_disconnected: %x", gtws.state);

    app_send_message(APP_MSG_BT_OPEN_PAGE_SCAN, 0);
}

static void bt_tws_phone_page_timeout(void)
{
    log_info("bt_tws_phone_page_timeout: %x", gtws.state);

    bt_tws_phone_disconnected();

    app_send_message(APP_MSG_BT_OPEN_PAGE_SCAN, 0);
}

static void bt_tws_phone_connect_timeout(void)
{
    log_info("bt_tws_phone_connect_timeout: %x", gtws.state);

    gtws.state &= ~BT_TWS_PHONE_CONNECTED;

    app_send_message(APP_MSG_BT_OPEN_PAGE_SCAN, 0);
}

static int bt_tws_poweroff(void)
{
    log_info("bt_tws_poweroff");

    if (tws_api_get_role() == TWS_ROLE_MASTER) {
        send_page_device_addr_2_sibling();

        tws_api_detach((TCFG_TWS_USE_COMMMON_ADDR) ? TWS_DETACH_BY_POWEROFF : TWS_DETACH_BY_LOCAL, 5000);   //这里不等完全断开的话，退出蓝牙模式把资源全部释放之后如果还没断完，底层的状态就乱了,这里是应用BY_LOCAL是为了不进行主从切换
    } else {
        tws_api_detach(TWS_DETACH_BY_POWEROFF, 5000);   //这里不等完全断开的话，退出蓝牙模式把资源全部释放之后如果还没断完，底层的状态就乱了
    }

    tws_profile_exit();

    gtws.state = 0;
    gtws.active = FALSE;

    if (tws_api_get_tws_state() & TWS_STA_SIBLING_DISCONNECTED) {
        return 1;
    }

    return 0;
}

static void tws_page_scan_deal_by_esco(u8 esco_flag)
{
    if (gtws.state & BT_TWS_UNPAIRED || ((gtws.state & BT_TWS_POWER_ON) == 0)) {
        return;
    }

    if (esco_flag) {
        gtws.state &= ~BT_TWS_CONNECT_SIBLING;
        tws_api_cancle_create_connection();
        tws_api_connect_in_esco();
        log_info("close scan");
    }

    if (!esco_flag && !(gtws.state & BT_TWS_SIBLING_CONNECTED)) {
        log_info("open scan");
        tws_api_cancle_connect_in_esco();
        tws_dual_conn_state_handler();
    }
}

/*
 * 解除配对，清掉对方地址信息和本地声道信息
 */
static void bt_tws_remove_pairs(void)
{
    u8 mac_addr[6];
    char channel = 'U';
    char tws_channel = 0;
    u8 role = 0xff;

    gtws.state &= ~BT_TWS_REMOVE_PAIRS;

    memset(mac_addr, 0xFF, 6);
    __this->tws_role = role;
    syscfg_write(CFG_TWS_COMMON_ADDR, mac_addr, 6);
    syscfg_write(CFG_TWS_REMOTE_ADDR, mac_addr, 6);
    syscfg_write(VM_TWS_ROLE_INDEX, &role, 1);
    syscfg_read(CFG_BT_MAC_ADDR, mac_addr, 6);
    lmp_hci_write_local_address(mac_addr);
#if TCFG_TWS_USE_COMMMON_ADDR != 0
    bt_update_mac_addr(mac_addr);
#endif

#if (TCFG_BT_TWS_CHANNEL_SELECT == CONFIG_TWS_START_PAIR_AS_LEFT) ||\
    (TCFG_BT_TWS_CHANNEL_SELECT == CONFIG_TWS_START_PAIR_AS_RIGHT) ||\
    (TCFG_BT_TWS_CHANNEL_SELECT == CONFIG_TWS_MASTER_AS_LEFT) || \
    (TCFG_BT_TWS_CHANNEL_SELECT == CONFIG_TWS_MASTER_AS_RIGHT)

    // cppcheck-suppress knownConditionTrueFalse
    if ((tws_channel != 'L') && (tws_channel != 'R')) {
        __this->tws_channel = channel;
        syscfg_write(CFG_TWS_CHANNEL, &channel, 1);
        tws_api_set_local_channel(channel);
    }
#endif
}

/*tws断开并清除配对信息(配对信息在TWS_EVENT_REMOVE_PAIRS删除)*/
void bt_tws_detach_and_remove_pairs(void)
{
#if TCFG_TWS_USE_COMMMON_ADDR
#if CONFIG_TWS_COMMON_ADDR_SELECT == CONFIG_TWS_COMMON_ADDR_USED_LEFT && TCFG_BT_TWS_CHANNEL_SELECT == CONFIG_TWS_MASTER_AS_LEFT
    if (tws_api_get_role() == TWS_ROLE_SLAVE && (tws_api_get_tws_state() & TWS_STA_PHONE_CONNECTED)) {
        return;
    }
#else
    //使用公共地址，连接手机无法取消配对
    if (tws_api_get_tws_state() & TWS_STA_PHONE_CONNECTED) {
        return;
    }
#endif
#endif
    tws_api_remove_pairs();
}

int bt_tws_start_pair(void)
{
    int tws_state = tws_api_get_tws_state();

    log_info("bt_tws_start_pair : 0x%x", tws_state);

    if (!(gtws.state & BT_TWS_POWER_ON)) {  //还没执行bt_tws_poweron不能发起配对
        return -1;
    }

#if TCFG_TWS_USE_COMMMON_ADDR
    if ((tws_api_get_tws_state() & TWS_STA_PHONE_CONNECTED)) { //连接手机无法发起配对
        log_error("start pair failed because connect with phone");
        return -1;
    }
#endif

#if TCFG_TWS_PAIR_BY_BOTH_SIDES
    //两边都按下按键发起开始配对才能进行配对
    if (!(tws_api_get_tws_state() & TWS_STA_TWS_PAIRED)) {
        bt_set_pair_code_en(1);
        tws_api_cancle_wait_pair();
        if (bt_get_total_connect_dev()) {
            tws_api_wait_pair_when_phone_connect(0);
        } else {
            tws_api_auto_pair(TCFG_TWS_PAIR_TIMEOUT * 1000);
        }
    }
#else
    tws_api_search_sibling_by_code();
    tws_set_search_sbiling_state(1);            //设置标志，发起配对的做主机
#endif

    return 0;
}

#define TWS_FUNC_ID_VOL_SYNC    TWS_FUNC_ID('V', 'O', 'L', 'S')

static void bt_tws_vol_sync(void *_data, u16 len, bool rx)
{
    if (rx && current_app_in_mode(APP_MODE_BT)) {
        u8 *data = (u8 *)_data;
        app_audio_set_volume(APP_AUDIO_STATE_MUSIC, data[0], 1);
        app_audio_set_volume(APP_AUDIO_STATE_CALL, data[1], 1);
        log_info("vol_sync: %d, %d", data[0], data[1]);
    }
}

REGISTER_TWS_FUNC_STUB(app_vol_sync_stub) = {
    .func_id = TWS_FUNC_ID_VOL_SYNC,
    .func    = bt_tws_vol_sync,
};

void bt_tws_sync_volume(void)
{
    if (current_app_in_mode(APP_MODE_BT) == FALSE) {
        return;
    }

    u8 data[2];
    data[0] = app_audio_get_volume(APP_AUDIO_STATE_MUSIC);
    data[1] = app_audio_get_volume(APP_AUDIO_STATE_CALL);

    tws_api_send_data_to_slave(data, 2, TWS_FUNC_ID_VOL_SYNC);
}

static void bt_tws_tx_jiffies_offset(void)
{
    int clkn = (jiffies_msec() + log_get_time_offset()) / 5 * 8;
    int offset = tws_api_get_mclkn() - clkn;
    tws_api_send_data_to_sibling(&offset, 4, 0x1E782CEB);
}

static void bt_tws_jiffies_sync(void *_data, u16 len, bool rx)
{
    if (!rx) {
        return;
    }

    int offset = *(int *)_data;
    int a_jiffies = (tws_api_get_mclkn() - offset) / 8 * 5;
    int b_jiffies = jiffies_msec() + log_get_time_offset();

    if (time_after(a_jiffies, b_jiffies)) {
        log_set_time_offset(a_jiffies - jiffies_msec());
    } else {
        bt_tws_tx_jiffies_offset();
    }
}

REGISTER_TWS_FUNC_STUB(jiffies_sync_stub) = {
    .func_id = 0x1E782CEB,
    .func    = bt_tws_jiffies_sync,
};

static void tws_sync_bat_level(void)
{
#if TCFG_BT_DISPLAY_BAT_ENABLE
    u8 battery_level = get_self_battery_level();
#if CONFIG_DISPLAY_DETAIL_BAT
    u8 percent_level = get_vbat_percent();
#else
    u8 percent_level = get_self_battery_level() * 10 + 10;
#endif

    if (sys_power_is_charging()) {
        percent_level |= BIT(7);
    }

    u8 data[2];
    data[0] = battery_level;
    data[1] = percent_level;
    tws_api_send_data_to_sibling(data, 2, TWS_FUNC_ID_VBAT_SYNC);

    log_info("tws_sync_bat_level: %d,%d", battery_level, percent_level);
#endif
}

static u8 tws_sibling_bat_level = 0xff;
static u8 tws_sibling_bat_percent_level = 0xff;

u8 get_tws_sibling_bat_level(void)
{
    return tws_sibling_bat_level & 0x7f;
}

u8 get_tws_sibling_bat_persent(void)
{
    return tws_sibling_bat_percent_level;
}

static void app_power_set_tws_sibling_bat_level(u8 vbat, u8 percent)
{
    tws_sibling_bat_level = vbat;
    tws_sibling_bat_percent_level = percent;
    /*
     ** 发出电量同步事件进行进一步处理
     **/
    power_event_to_user(POWER_EVENT_SYNC_TWS_VBAT_LEVEL);

    log_info("set_sibling_bat_level: %d, %d", vbat, percent);
}

u8 get_cur_battery_level(void)
{
    u8 bat_lev = tws_sibling_bat_level & (~BIT(7));
    if (bat_lev == 0x7f) {
        return get_self_battery_level();
    }

#if (CONFIG_DISPLAY_TWS_BAT_TYPE == CONFIG_DISPLAY_TWS_BAT_LOWER)
    return get_self_battery_level() < bat_lev ? get_self_battery_level() : bat_lev;
#elif (CONFIG_DISPLAY_TWS_BAT_TYPE == CONFIG_DISPLAY_TWS_BAT_HIGHER)
    return get_self_battery_level() < bat_lev ? bat_lev : get_self_battery_level();
#elif (CONFIG_DISPLAY_TWS_BAT_TYPE == CONFIG_DISPLAY_TWS_BAT_LEFT)
    return tws_api_get_local_channel() == 'L' ? get_self_battery_level() : bat_lev;
#elif (CONFIG_DISPLAY_TWS_BAT_TYPE == CONFIG_DISPLAY_TWS_BAT_RIGHT)
    return tws_api_get_local_channel() == 'R' ? get_self_battery_level() : bat_lev;
#else
    return get_self_battery_level();
#endif
}

static void set_tws_sibling_bat_level(void *_data, u16 len, bool rx)
{
    u8 *data = (u8 *)_data;

    if (rx) {
        app_power_set_tws_sibling_bat_level(data[0], data[1]);
    }
}

REGISTER_TWS_FUNC_STUB(vbat_sync_stub) = {
    .func_id = TWS_FUNC_ID_VBAT_SYNC,
    .func    = set_tws_sibling_bat_level,
};

static int bt_tws_power_manage_event_handler(void *evt)
{
    struct device_event *event = (struct device_event *)evt;

    switch (event->event) {
    case POWER_EVENT_POWER_CHANGE:
        if (tws_api_get_tws_state() & TWS_STA_SIBLING_CONNECTED) {
            if (tws_api_get_tws_state() & TWS_STA_ESCO_OPEN) {
                break;
            }
            tws_sync_bat_level();
        }
        bt_cmd_prepare(USER_CTRL_HFP_CMD_UPDATE_BATTARY, 0, NULL);
        break;
    case POWER_EVENT_SYNC_TWS_VBAT_LEVEL:
        if (tws_api_get_role() == TWS_ROLE_MASTER) {
            bt_cmd_prepare(USER_CTRL_HFP_CMD_UPDATE_BATTARY, 0, NULL);
        }
        break;
    }

    return FALSE;
}

REGISTER_APP_EVENT_HANDLER(bt_tws_power_manage_event) = {
    .event      = SYS_DEVICE_EVENT,
    .from       = DEVICE_EVENT_FROM_POWER,
    .handler    = bt_tws_power_manage_event_handler,
};

static void bt_tws_event_connected_handler(int role, int reason)
{
    int pair_suss = 0;
    u8 addr[4][6];

    log_info("tws_event_pair_suss: 0x%x", gtws.state);

    __this->phone_ring_sync_tws = 0;

    gtws.state &= ~BT_TWS_WAIT_SIBLING_SEARCH;

#if TCFG_TWS_PAIR_BY_BOTH_SIDES
    bt_set_pair_code_en(0);
#endif

    syscfg_read(CFG_TWS_REMOTE_ADDR, addr[0], 6);
    syscfg_read(CFG_TWS_COMMON_ADDR, addr[1], 6);
    tws_api_get_sibling_addr(addr[2]);
    tws_api_get_local_addr(addr[3]);

    /* 记录对方地址 */
    if (memcmp(addr[0], addr[2], 6)) {
        syscfg_write(CFG_TWS_REMOTE_ADDR, addr[2], 6);
        pair_suss = 1;
        log_info("rec tws addr");
        put_buf(addr[2], 6);
    }
    if (memcmp(addr[1], addr[3], 6)) {
        syscfg_write(CFG_TWS_COMMON_ADDR, addr[3], 6);
        pair_suss = 1;
        log_info("rec comm addr");
        put_buf(addr[3], 6);
    }

    /* 记录左右声道 */
    char channel = tws_api_get_local_channel();
    if (channel != bt_tws_get_local_channel()) {
        __this->tws_channel = channel;
        syscfg_write(CFG_TWS_CHANNEL, &channel, 1);
    }

    log_info("tws_local_channel: %c", channel);

    tws_api_set_quick_connect_addr(addr[3]);

#if((TCFG_BT_TWS_PAIR_MODE == CONFIG_TWS_PAIR_BY_CLICK) && (TCFG_TWS_PAIR_BY_BOTH_SIDES == 0))
    //固定发起方为主机不进行role_switch
    tws_api_auto_role_switch_disable();
    __this->tws_role = role;
    syscfg_write(VM_TWS_ROLE_INDEX, &role, 1);
#endif

    if (pair_suss) {
        gtws.state |= BT_TWS_PAIRED;
#if TCFG_TWS_USE_COMMMON_ADDR != 0
        bt_update_mac_addr((void *)addr[3]);
#endif
        app_send_message(APP_MSG_TWS_PAIR_SUSS, 0);
    } else {
        app_send_message(APP_MSG_TWS_CONNECTED, 0);
    }

    if (role == TWS_ROLE_MASTER) {
#if TCFG_LOCAL_TWS_ENABLE
        local_tws_connect_mode_report();
#endif
        bt_tws_tx_jiffies_offset();
    }

    if (reason & (TWS_STA_ESCO_OPEN | TWS_STA_SBC_OPEN)) {
        if (role == TWS_ROLE_SLAVE) {
            gtws.state |= BT_TWS_AUDIO_PLAYING;
        }
    }

    gtws.state &= ~BT_TWS_TIMEOUT;
    gtws.state |= BT_TWS_SIBLING_CONNECTED;

    tws_sync_bat_level(); //同步电量到对耳

    bt_tws_sync_volume();

    tws_sniff_controle_check_enable();
}

static void bt_tws_event_connection_detach_handler(int phone_link_connection, int reason, int work_state)
{
    log_info("tws_event_connection_detach state: %x, %x", gtws.state, work_state);

    __this->phone_ring_sync_tws = 0;

    app_power_set_tws_sibling_bat_level(0xff, 0xff);

#if TCFG_LOCAL_TWS_ENABLE
    local_tws_disconnect_deal();
#endif

    if (phone_link_connection) {
        //对耳断开后如果手机还连着，主动推一次电量给手机
        power_event_to_user(POWER_EVENT_POWER_CHANGE);
        bt_cmd_prepare(USER_CTRL_HFP_CMD_UPDATE_BATTARY, 0, NULL);
    }

    tws_sniff_controle_check_disable();

    gtws.state &= ~BT_TWS_SIBLING_CONNECTED;

    if (reason & TWS_DETACH_BY_REMOVE_PAIRS) {
        gtws.state &= ~BT_TWS_PAIRED;
        gtws.state |= BT_TWS_UNPAIRED;
        if (phone_link_connection == 0) {
            gtws.state &= ~BT_TWS_PHONE_CONNECTED;
#if TCFG_TWS_USE_COMMMON_ADDR == 0
            lmp_hci_write_local_address(bt_get_mac_addr());
#endif
        }

        log_info("tws detach by remove pairs: %x", gtws.state);

#if TCFG_TWS_PAIR_ALWAYS && !TCFG_TWS_PAIR_BY_BOTH_SIDES    //打开TWS_PAIR_ALWAYS,在手机连接之后仍然可以进行配对
        /* if (phone_link_connection)  */   //这里手机回连过程马上取消配对值会是0, 不判断应该也没问题
        {
            tws_api_wait_pair_when_phone_connect(0);    //调用这个接口只打开TWS PageScan
        }
#endif

        bt_tws_disable();

#if (THIRD_PARTY_PROTOCOLS_SEL & MULTI_BOX_ADV_EN)
        multiple_bt_pair_remove();
#endif

        __this->pair_enable = FALSE;

        return;
    }

    if (bt_get_esco_coder_busy_flag()) {
        tws_api_connect_in_esco();
        return;
    }

    //非测试盒在仓测试，直连蓝牙
    if (reason & TWS_DETACH_BY_TESTBOX_CON) {
        log_info("tws_detach_by_testbox_con");

        gtws.state &= ~BT_TWS_PAIRED;
        gtws.state |= BT_TWS_UNPAIRED;

        if (!phone_link_connection) {
            u8 mac_addr[6];
            get_random_number(mac_addr, 6);
            lmp_hci_write_local_address(mac_addr);
        }
    }
}

static void bt_tws_event_role_switch_handler(int role)
{
#if TCFG_TWS_POWER_BALANCE_ENABLE && TCFG_BT_SUPPORT_PROFILE_HFP
    if (role == TWS_ROLE_SLAVE) {
        esco_recoder_switch(0);
    } else {
        esco_recoder_switch(1);
    }
#endif
    if (!(tws_api_get_tws_state() & TWS_STA_PHONE_CONNECTED)) {
        if (role == TWS_ROLE_MASTER) {
            os_time_dly(2);
            tws_sniff_controle_check_enable();
        }
    }
}

/*
 * tws事件状态处理函数
 */
static int bt_tws_connction_status_event_handler(void *msg)
{
    struct tws_event *evt = (struct tws_event *)msg;
    int role = evt->args[0];
    int phone_link_connection = evt->args[1];
    int reason = evt->args[2];
    u16 random_num = 0;

    log_info("tws-user: role = %d, phone_link_connection %d, reason = %d,event = %d",
             role, phone_link_connection, reason, evt->event);

    switch (evt->event) {
    case TWS_EVENT_CONNECTED:
        bt_tws_event_connected_handler(role, reason);
        break;
    case TWS_EVENT_CONNECTION_DETACH:
        bt_tws_event_connection_detach_handler(phone_link_connection, reason, evt->args[3]);
        break;
    case TWS_EVENT_PHONE_LINK_DETACH:
        /*
         * 跟手机的链路LMP层已完全断开, 只有tws在连接状态才会收到此事件
         */
        log_info("tws_event_phone_link_detach: %x", gtws.state);
        tws_sniff_controle_check_enable();
        break;
    case TWS_EVENT_REMOVE_PAIRS:
        log_info("tws_event_remove_pairs");
        bt_tws_remove_pairs();
        app_power_set_tws_sibling_bat_level(0xff, 0xff);
        bt_tws_disable();
        break;
    case TWS_EVENT_ROLE_SWITCH:
        log_info("tws_event_role_switch = %d", role);
        bt_tws_event_role_switch_handler(role);
        break;
    case TWS_EVENT_ESCO_ROLE_SWITCH_START:
        log_info("tws_event_esco_role_switch_start = %d", role);
#if TCFG_TWS_POWER_BALANCE_ENABLE && TCFG_BT_SUPPORT_PROFILE_HFP
        if (role == TWS_ROLE_SLAVE) {
            esco_recoder_switch(1);
        }
#endif
        break;
    case TWS_EVENT_ESCO_ADD_CONNECT:
        bt_tws_sync_volume();
        break;
    case TWS_EVENT_MODE_CHANGE:
        log_info("tws_event_mode_change : %d", role);
        if (role == TWS_ROLE_MASTER) {
            tws_sniff_controle_check_enable();
        }
        break;
    case TWS_EVENT_TONE_TEST:
        log_info("tws_event_test : %d", role);
        break;
    }

#if TCFG_BT_SUPPORT_PROFILE_A2DP
    a2dp_player_tws_event_handler((int *)evt);
#endif

    return FALSE;
}

REGISTER_APP_EVENT_HANDLER(bt_tws_connction_status_event) = {
    .event      = SYS_BT_EVENT,
    .from       = BT_EVENT_FROM_TWS,
    .handler    = bt_tws_connction_status_event_handler,
};

int tws_host_get_phone_income_state(void)
{
    if (bt_get_call_status() == BT_CALL_INCOMING) {
        return 1;
    }
    return 0;
}

void tws_cancle_all_noconn(void)
{
    tws_api_cancle_wait_pair();
    tws_api_cancle_create_connection();
    bt_cmd_prepare(USER_CTRL_PAGE_CANCEL, 0, NULL);
}

bool get_tws_sibling_connect_state(void)
{
    if (gtws.state & BT_TWS_SIBLING_CONNECTED) {
        return TRUE;
    }
    return FALSE;
}

#define TWS_SNIFF_CNT_TIME      5000    //ms

static void bt_tws_enter_sniff(void *parm)
{
    int interval;

    int state = tws_api_get_tws_state();
    if (state & TWS_STA_PHONE_DISCONNECTED) {
        interval = 400;
    } else if (state & TWS_STA_PHONE_SNIFF) {
        interval = 96 * 8;
    } else {
        goto __exit;
    }

    int err = tws_api_tx_sniff_req(interval, 8);
    if (err == 0) {
        sys_timer_del(gtws.sniff_timer);
        gtws.sniff_timer = 0;
        return;
    }

__exit:
    sys_timer_modify(gtws.sniff_timer, TWS_SNIFF_CNT_TIME);
}

static void tws_sniff_controle_check_reset(void)
{
    if (gtws.sniff_timer) {
        sys_timer_modify(gtws.sniff_timer, TWS_SNIFF_CNT_TIME);
    }
}

static void tws_sniff_controle_check_enable(void)
{
#if (CONFIG_BT_TWS_SNIFF == 0)
    return;
#endif

    int update_check_sniff_en(void);
    if (update_check_sniff_en() == 0) {
        return;
    }

    if (gtws.sniff_timer == 0) {
        gtws.sniff_timer = sys_timer_add(NULL, bt_tws_enter_sniff, TWS_SNIFF_CNT_TIME);
    }

    log_info("tws_sniff_check_enable");
}

static void tws_sniff_controle_check_disable(void)
{
#if (CONFIG_BT_TWS_SNIFF == 0)
    return;
#endif

    if (gtws.sniff_timer) {
        sys_timer_del(gtws.sniff_timer);
        gtws.sniff_timer = 0;
    }

    log_info("tws_sniff_check_disable");
}

static void tws_phone_ble_link_try_switch(void *p)
{
    //等待退出tws sniff
    if (!tws_in_sniff_state()) {
        //开始启动ble controller检查,满足切换条件进行链路切换;
        sys_timeout_del(gtws.ble_try_switch_timer);
        gtws.ble_try_switch_timer = 0;
    }
}

void bt_tws_ble_link_switch(void)
{
#if CONFIG_BT_TWS_SNIFF
    tws_sniff_controle_check_disable();
    tws_api_tx_unsniff_req();
#endif
    gtws.ble_try_switch_timer = sys_timer_add(NULL, tws_phone_ble_link_try_switch, 20);
}

//未连接手机时的TWS主从切换
void bt_tws_role_switch(void)
{
#if 0
    if (!(gtws.state & BT_TWS_SIBLING_CONNECTED)) {
        return;
    }
#endif

    if (tws_api_get_role() == TWS_ROLE_SLAVE) {
        return;
    }

    log_info("bt_tws_role_switch");

    tws_api_cancle_wait_pair();

#if CONFIG_BT_TWS_SNIFF
    tws_sniff_controle_check_disable();
    tws_api_tx_unsniff_req();
    for (int i = 0; i < 20; i++) {
        if (!tws_in_sniff_state()) {
            tws_api_role_switch();
            break;
        }
        os_time_dly(4);
    }
#else
    tws_api_role_switch();
#endif
}

static void tws_key_msg_sync_callback(int msg, int ret)
{
    struct key_event event = {0};

    event.type   = KEY_DRIVER_TYPE_SOFTKEY;
    event.value  = msg & 0xff;
    event.action = (msg >> 8) & 0xff;

    if (ret == TWS_SYNC_CALL_RX) {
        sys_event_notify(SYS_KEY_EVENT, KEY_EVENT_FROM_TWS, &event, sizeof(event));
    } else {
        ASSERT(0, "TWS_SYNC_CALL_TX");
    }
}

TWS_SYNC_CALL_REGISTER(tws_key_msg_sync_entry) = {
    .uuid = 0x8097ADF1,
    .func = tws_key_msg_sync_callback,
};

void bt_tws_key_msg_sync(u8 action, u8 value)
{
    tws_api_sync_call_by_uuid(0x8097ADF1, ((u32)action << 8) | value, (20 << 16) | 200);
}

static void bt_event_rx_handler_in_irq(void *data, u16 len, bool rx)
{
    struct bt_event evt = {0};

    if (rx) {
        memcpy(&evt, data, sizeof(evt));
        int from = evt.args[6] == 0 ? BT_EVENT_FROM_CON : BT_EVENT_FROM_HCI;
        bt_event_notify(from, &evt);
    }
}

REGISTER_TWS_FUNC_STUB(bt_event_sync_stub) = {
    .func_id = 0xC9073872,
    .func = bt_event_rx_handler_in_irq,
};


__attribute__((weak))
void bt_event_update_to_user(u8 *addr, u8 from, u8 event, u32 value)
{
    struct bt_event evt = {0};

    if (addr != NULL) {
        memcpy(evt.args, addr, 6);
    }
    evt.event = event;
    evt.value = value;

    if (tws_api_get_tws_state() & TWS_STA_SIBLING_CONNECTED) {
        if (tws_api_get_role_async() == TWS_ROLE_SLAVE) {
            return;
        }

        evt.args[6] = from == BT_EVENT_FROM_CON ? 0  : 1;
        tws_api_send_data_to_sibling(&evt, sizeof(evt), 0xC9073872);
    }

    bt_event_notify(from, &evt);

    /* 防止短时间内太多事件,app_core处理不过来导致qfull */
    os_time_dly(1);
}

#endif
