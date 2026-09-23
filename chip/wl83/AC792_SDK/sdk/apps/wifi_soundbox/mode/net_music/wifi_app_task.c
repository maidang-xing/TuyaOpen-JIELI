#include "system/init.h"
#include "system/timer.h"
#include "wifi/wifi_connect.h"
#include "lwip/sockets.h"
#include "lwip/netdb.h"
#include "lwip/dns.h"
#include "lwip/ip.h"
#include "os/os_api.h"
#include "lwip.h"
#include "app_config.h"
#include "event/net_event.h"
#include "syscfg/syscfg_id.h"
#include "asm/rf_coexistence_config.h"

#ifdef CONFIG_NET_ENABLE

#define LOG_TAG             "[WIFI]"
#define LOG_ERROR_ENABLE
#define LOG_WARN_ENABLE
#define LOG_DEBUG_ENABLE
#define LOG_INFO_ENABLE
#define LOG_CLI_ENABLE
#include "debug.h"


#ifdef CONFIG_ASSIGN_MACADDR_ENABLE
#include "net/assign_macaddr.h"
#include "net/config_network.h"
#endif

#define CONNECT_TIMEOUT_SEC 60

static struct {
    u8 use_static_ipaddr_flag : 1;
    u8 net_app_init_flag : 1;
    u8 request_connect_flag : 1;
    u8 save_ssid_flag : 1;
    u8 mac_addr_succ_flag : 1;
    u8 udp_recv_test_exit_flag : 1;
    u16 psm_timer;
} wifi_app_hdl;

#define __this	(&wifi_app_hdl)

extern void airkiss_ssid_check(void);

static int wifi_force_set_lan_setting_info(void)
{
    return 0;
}

static void soft_ap_set_lan_setting_info(void)
{
    struct lan_setting lan_setting_info = {
        .WIRELESS_IP_ADDR0  = 192,
        .WIRELESS_IP_ADDR1  = 168,
        .WIRELESS_IP_ADDR2  = 0,
        .WIRELESS_IP_ADDR3  = 1,

        .WIRELESS_NETMASK0  = 255,
        .WIRELESS_NETMASK1  = 255,
        .WIRELESS_NETMASK2  = 255,
        .WIRELESS_NETMASK3  = 0,

        .WIRELESS_GATEWAY0  = 192,
        .WIRELESS_GATEWAY1  = 168,
        .WIRELESS_GATEWAY2  = 0,
        .WIRELESS_GATEWAY3  = 1,

        .SERVER_IPADDR1  = 192,
        .SERVER_IPADDR2  = 168,
        .SERVER_IPADDR3  = 0,
        .SERVER_IPADDR4  = 1,

        .CLIENT_IPADDR1  = 192,
        .CLIENT_IPADDR2  = 168,
        .CLIENT_IPADDR3  = 0,
        .CLIENT_IPADDR4  = 2,

        .SUB_NET_MASK1   = 255,
        .SUB_NET_MASK2   = 255,
        .SUB_NET_MASK3   = 255,
        .SUB_NET_MASK4   = 0,
    };

    net_set_lan_info_ext(&lan_setting_info, WIFI_NETIF);
}

#ifdef CONFIG_STATIC_IPADDR_ENABLE

struct sta_ip_info {
    char ssid[33];
    u32 ip;
    u32 gw;
    u32 netmask;
    u32 dns;
    u8 gw_mac[6];
    u8 local_mac[6];
    u8 chanel;
};

static void wifi_set_lan_setting_info(void)
{
    struct sta_ip_info  sta_ip_info;
    syscfg_read(VM_STA_IPADDR_INDEX, (char *) &sta_ip_info, sizeof(struct sta_ip_info));

    struct lan_setting lan_setting_info = {
        .WIRELESS_IP_ADDR0  = (u8)(sta_ip_info.ip >> 0),
        .WIRELESS_IP_ADDR1  = (u8)(sta_ip_info.ip >> 8),
        .WIRELESS_IP_ADDR2  = (u8)(sta_ip_info.ip >> 16),
        .WIRELESS_IP_ADDR3  = (u8)(sta_ip_info.ip >> 24),

        .WIRELESS_NETMASK0  = (u8)(sta_ip_info.netmask >> 0),
        .WIRELESS_NETMASK1  = (u8)(sta_ip_info.netmask >> 8),
        .WIRELESS_NETMASK2  = (u8)(sta_ip_info.netmask >> 16),
        .WIRELESS_NETMASK3  = (u8)(sta_ip_info.netmask >> 24),

        .WIRELESS_GATEWAY0   = (u8)(sta_ip_info.gw >> 0),
        .WIRELESS_GATEWAY1   = (u8)(sta_ip_info.gw >> 8),
        .WIRELESS_GATEWAY2   = (u8)(sta_ip_info.gw >> 16),
        .WIRELESS_GATEWAY3   = (u8)(sta_ip_info.gw >> 24),
    };

    net_set_lan_info(&lan_setting_info);
}

static int compare_dhcp_ipaddr(void)
{
    __this->use_static_ipaddr_flag = 0;

    u8 local_mac[6];
    u8 gw_mac[6];
    struct sta_ip_info sta_ip_info;
    struct netif_info netif_info;

    int ret = syscfg_read(VM_STA_IPADDR_INDEX, (char *) &sta_ip_info, sizeof(struct sta_ip_info));
    if (ret < 0) {
        log_info("compare_dhcp_ipaddr NO VM_STA_IPADDR_INDEX");
        return -1;
    }

    lwip_get_netif_info(WIFI_NETIF, &netif_info);

    struct wifi_mode_info info;
    info.mode = STA_MODE;
    wifi_get_mode_cur_info(&info);

    wifi_get_bssid(gw_mac);
    wifi_get_mac(local_mac);

    if (!strcmp(info.ssid, sta_ip_info.ssid)
        && !memcmp(local_mac, sta_ip_info.local_mac, 6)
        && !memcmp(gw_mac, sta_ip_info.gw_mac, 6)
        /*&& sta_ip_info.gw==sta_ip_info.dns//如果路由器没接网线/没联网,每次连接都去重新获取DHCP*/
       ) {
        __this->use_static_ipaddr_flag = 1;
        log_info("compare_dhcp_ipaddr Match");
        return 0;
    }

    log_info("compare_dhcp_ipaddr not Match!!! [%s][%s],[0x%x,0x%x][0x%x,0x%x],[0x%x]", info.ssid, sta_ip_info.ssid, local_mac[0], local_mac[5], sta_ip_info.local_mac[0], sta_ip_info.local_mac[5], sta_ip_info.dns);

    return -1;
}

static void store_dhcp_ipaddr(void)
{
    struct sta_ip_info sta_ip_info = {0};
    u8 sta_channel;
    u8 local_mac[6];
    u8 gw_mac[6];

    if (__this->use_static_ipaddr_flag) { //记忆IP匹配成功,不需要重新保存
        return;
    }

    struct netif_info netif_info;
    lwip_get_netif_info(WIFI_NETIF, &netif_info);

    struct wifi_mode_info info;
    info.mode = STA_MODE;
    wifi_get_mode_cur_info(&info);

    sta_channel = wifi_get_channel();
    wifi_get_mac(local_mac);
    wifi_get_bssid(gw_mac);

    strcpy(sta_ip_info.ssid, info.ssid);
    memcpy(sta_ip_info.gw_mac, gw_mac, 6);
    memcpy(sta_ip_info.local_mac, local_mac, 6);
    sta_ip_info.ip =  netif_info.ip;
    sta_ip_info.netmask =  netif_info.netmask;
    sta_ip_info.gw =  netif_info.gw;
    sta_ip_info.chanel = sta_channel;
    sta_ip_info.dns = *(u32 *)dns_getserver(0);

    syscfg_write(VM_STA_IPADDR_INDEX, (char *) &sta_ip_info, sizeof(struct sta_ip_info));

    log_info("store_dhcp_ipaddr");
}

void dns_set_server(u32 *dnsserver)
{
    struct sta_ip_info  sta_ip_info;
    if (syscfg_read(VM_STA_IPADDR_INDEX, (char *) &sta_ip_info, sizeof(struct sta_ip_info)) < 0) {
        *dnsserver = 0;
    } else {
        *dnsserver = sta_ip_info.dns;
    }
}

#endif

#if IP_NAPT_EXT
/* #define INIT_MODE STA_MODE */
#define INIT_MODE AP_MODE
#define FORCE_DEFAULT_MODE 1
#define INIT_SSID "GJ0"
#define INIT_PWD  ""
#else
#define INIT_MODE SMP_CFG_MODE
/* #define INIT_MODE STA_MODE */
#define FORCE_DEFAULT_MODE 0 //配置wifi_on之后的模式,0为使用最后记忆的模式, 1为强制默认模式, 3-200为连接超时时间多少秒,如果超时都连接不上就连接最后记忆的或者最优网络
#define INIT_SSID "WL84"
#define INIT_PWD  "88888888"
/* #define INIT_SSID "1F设备间" */
/* #define INIT_PWD  "jielikeji" */
#endif
#define INIT_STORED_SSID (INIT_MODE==STA_MODE)//配置STA模式情况下,把默认配置SSID也存储起来, 以后即使保存过其他SSID,也不会覆盖丢失,使用连接最优信号SSID策略的情况下可以匹配连接
#define INIT_CONNECT_BEST_SSID 1 //配置如果啟動WIFI后在STA模式下, 是否挑选连接记忆过的信号最优WIFI

#define WIFI_FORCE_DEFAULT_MODE  FORCE_DEFAULT_MODE
#define WIFI_INIT_MODE  INIT_MODE
#define WIFI_INIT_SSID INIT_SSID
#define WIFI_INIT_PWD INIT_PWD
#define WIFI_INIT_CONNECT_BEST_SSID  INIT_CONNECT_BEST_SSID
#define WIFI_INIT_STORED_SSID  INIT_STORED_SSID

static void net_app_init(void);

void wifi_return_sta_mode(void)
{
    struct wifi_mode_info info;
    info.mode = STA_MODE;
    int ret = wifi_get_mode_stored_info(&info);
    if (ret || info.mode == SMP_CFG_MODE) {//如果没保存过SSID
#if 1
        if (wifi_is_on()) {
            wifi_off();
        }
        return;
#endif
        info.ssid = WIFI_INIT_SSID;
        info.pwd = WIFI_INIT_PWD;
    }
    if (!wifi_is_on()) {
        wifi_on();
        net_app_init();
    }
    wifi_clear_scan_result(); //根据扫描结果连接信号最优ssid之前先清除之前结果,防止之前最优信号的ssid已下线
    wifi_set_sta_connect_best_ssid(1);
    __this->save_ssid_flag = 0;
    __this->request_connect_flag = 1;
    wifi_enter_sta_mode(info.ssid, info.pwd);
}

static int wifi_is_in_smp_cfg_mode(void)
{
    struct wifi_mode_info info;
    info.mode = NONE_MODE;
    wifi_get_mode_cur_info(&info);
    return info.mode == SMP_CFG_MODE;
}

static void wifi_sta_save_ssid(void)
{
    if (__this->save_ssid_flag) {
        __this->save_ssid_flag = 0;

        struct wifi_mode_info info;
        info.mode = STA_MODE;
        wifi_get_mode_cur_info(&info);
        wifi_store_mode_info(STA_MODE, info.ssid, info.pwd);
    }
}

static void wifi_event_module_init(void)
{
    struct wifi_store_info wifi_default_mode_parm;
    memset(&wifi_default_mode_parm, 0, sizeof(struct wifi_store_info));

#if WIFI_INIT_MODE == AP_MODE
    soft_ap_set_lan_setting_info();
#endif

    wifi_default_mode_parm.mode = WIFI_INIT_MODE;
    if (wifi_default_mode_parm.mode == AP_MODE || wifi_default_mode_parm.mode == STA_MODE) {
        strncpy((char *)wifi_default_mode_parm.ssid[wifi_default_mode_parm.mode - STA_MODE], (const char *)WIFI_INIT_SSID, sizeof(wifi_default_mode_parm.ssid[wifi_default_mode_parm.mode - STA_MODE]) - 1);
        strncpy((char *)wifi_default_mode_parm.pwd[wifi_default_mode_parm.mode - STA_MODE], (const char *)WIFI_INIT_PWD, sizeof(wifi_default_mode_parm.pwd[wifi_default_mode_parm.mode - STA_MODE]) - 1);
    }
    wifi_default_mode_parm.connect_best_network = WIFI_INIT_CONNECT_BEST_SSID;
    wifi_set_default_mode(&wifi_default_mode_parm, WIFI_FORCE_DEFAULT_MODE, WIFI_INIT_STORED_SSID);
}

static void wifi_event_module_start(void)
{
    struct net_event net = {0};
    struct wifi_mode_info info;

    info.mode = NONE_MODE;
    wifi_get_mode_cur_info(&info);
    if (info.mode == SMP_CFG_MODE) {
        net.event = NET_EVENT_SMP_CFG_FIRST;
        net_event_notify(NET_EVENT_FROM_WIFI, &net);
    }

#if 1
    u32  tx_rate_control_tab = // 不需要哪个速率就删除掉,可以动态设定
        0
        | BIT(0) //0:CCK 1M
        | BIT(1) //1:CCK 2M
        | BIT(2) //2:CCK 5.5M
        | BIT(3) //3:OFDM 6M
        | BIT(4) //4:MCS0/7.2M
        | BIT(5) //5:OFDM 9M
        | BIT(6) //6:CCK 11M
        | BIT(7) //7:OFDM 12M
        | BIT(8) //8:MCS1/14.4M
        | BIT(9) //9:OFDM 18M
        | BIT(10) //10:MCS2/21.7M
        | BIT(11) //11:OFDM 24M
        | BIT(12) //12:MCS3/28.9M
        | BIT(13) //13:OFDM 36M
        | BIT(14) //14:MCS4/43.3M
        | BIT(15) //15:OFDM 48M
        | BIT(16) //16:OFDM 54M
        | BIT(17) //17:MCS5/57.8M
        | BIT(18) //18:MCS6/65.0M
        | BIT(19) //19:MCS7/72.2M
        ;
    wifi_set_tx_rate_control_tab(tx_rate_control_tab);
#endif
}

static int wifi_event_sta_connect_succ(void)
{
    int ret = 0;
    /*wifi_rxfilter_cfg(3);    //过滤not_my_bssid,如果需要使用扫描空中SSID就不要过滤*/

    if (wifi_force_set_lan_setting_info()) {
        ret = 1;
    } else {
#ifdef CONFIG_STATIC_IPADDR_ENABLE
        if (0 == compare_dhcp_ipaddr()) {
            wifi_set_lan_setting_info();
            ret = 1;
        }
#endif
    }

    return ret;
}

static void wifi_event_sta_network_stack_dhcp_succ(void)
{
    struct net_event net = {0};

    wifi_sta_save_ssid();

    config_network_broadcast();

#ifdef CONFIG_ASSIGN_MACADDR_ENABLE
    if (!is_server_assign_macaddr_ok()) { //如果使用服务器分配MAC地址的情况,需要确认MAC地址有效才发送连接成功事件到APP层,否则先访问服务器分配mac地址
        server_assign_macaddr(wifi_return_sta_mode);
        return;
    }
    __this->mac_addr_succ_flag = 1;
#endif

#ifdef CONFIG_STATIC_IPADDR_ENABLE
    store_dhcp_ipaddr();
#endif

    wifi_set_sta_connect_best_ssid(0);

    __this->request_connect_flag = 0;

    net.event = NET_EVENT_CONNECTED;
    net_event_notify(NET_EVENT_FROM_WIFI, &net);
}

static void wifi_event_sta_disconnect(void)
{
    struct net_event net = {0};

    /*wifi_rxfilter_cfg(0);*/

#ifdef CONFIG_ASSIGN_MACADDR_ENABLE
    if (!__this->mac_addr_succ_flag) {
        return;
    }
#endif

    net.event = NET_EVENT_DISCONNECTED;
    net_event_notify(NET_EVENT_FROM_WIFI, &net);

    if (!wifi_is_in_smp_cfg_mode() && !__this->request_connect_flag) {
        memset(&net, 0, sizeof(net));
        net.event = NET_EVENT_DISCONNECTED_AND_REQ_CONNECT;
        net_event_notify(NET_EVENT_FROM_WIFI, &net);
    }
}

static void wifi_event_ap_on_assoc(void *priv)
{
    struct eth_addr *hwaddr = (struct eth_addr *)priv;
    log_info("WIFI_EVENT_AP_ON_ASSOC hwaddr = %02x:%02x:%02x:%02x:%02x:%02x",
             hwaddr->addr[0], hwaddr->addr[1], hwaddr->addr[2], hwaddr->addr[3], hwaddr->addr[4], hwaddr->addr[5]);
#if IP_NAPT_EXT
    extern void check_dhcps_client_ipaddr(u8 * hwaddr);
    check_dhcps_client_ipaddr(hwaddr->addr);
#endif
}

static void wifi_event_ap_on_disconnected(void *priv)
{
    struct eth_addr *hwaddr = (struct eth_addr *)priv;
    log_info("WIFI_EVENT_AP_ON_DISCONNECTED hwaddr = %02x:%02x:%02x:%02x:%02x:%02x",
             hwaddr->addr[0], hwaddr->addr[1], hwaddr->addr[2], hwaddr->addr[3], hwaddr->addr[4], hwaddr->addr[5]);
}

static int wifi_event_callback(void *network_ctx, enum WIFI_EVENT event)
{
    int ret = 0;
    struct net_event net = {0};

    switch (event) {

    case WIFI_EVENT_MODULE_INIT:
        wifi_event_module_init();
        break;
    case WIFI_EVENT_MODULE_START:
        log_info("network_user_callback->WIFI_EVENT_MODULE_START");
        wifi_event_module_start();
        break;
    case WIFI_EVENT_MODULE_STOP:
        log_info("network_user_callback->WIFI_EVENT_MODULE_STOP");
        break;
    case WIFI_EVENT_AP_START:
        log_info("network_user_callback->WIFI_EVENT_AP_START");
        break;
    case WIFI_EVENT_AP_STOP:
        log_info("network_user_callback->WIFI_EVENT_AP_STOP");
        break;
    case WIFI_EVENT_STA_START:
        log_info("network_user_callback->WIFI_EVENT_STA_START");
        break;
    case WIFI_EVENT_MODULE_START_ERR:
        log_info("network_user_callback->WIFI_EVENT_MODULE_START_ERR");
        break;
    case WIFI_EVENT_STA_STOP:
        log_info("network_user_callback->WIFI_EVENT_STA_STOP");
        break;
    case WIFI_EVENT_STA_SCAN_COMPLETED:
        log_info("network_user_callback->WIFI_STA_SCAN_COMPLETED");
#ifdef CONFIG_AIRKISS_NET_CFG
        airkiss_ssid_check();
#endif
        break;
    case WIFI_EVENT_STA_CONNECT_SUCC:
        log_info("network_user_callback->WIFI_STA_CONNECT_SUCC, ch=%d", wifi_get_channel());
        ret = wifi_event_sta_connect_succ();
        break;
    case WIFI_EVENT_STA_CONNECT_TIMEOUT_NOT_FOUND_SSID:
        log_info("network_user_callback->WIFI_STA_CONNECT_TIMEOUT_NOT_FOUND_SSID");
        net.event = NET_CONNECT_TIMEOUT_NOT_FOUND_SSID;
        net_event_notify(NET_EVENT_FROM_WIFI, &net);
        break;
    case WIFI_EVENT_STA_CONNECT_ASSOCIAT_FAIL:
        log_info("network_user_callback->WIFI_STA_CONNECT_ASSOCIAT_FAIL");
        net.event = NET_CONNECT_ASSOCIAT_FAIL;
        net_event_notify(NET_EVENT_FROM_WIFI, &net);
        break;
    case WIFI_EVENT_STA_CONNECT_ASSOCIAT_TIMEOUT:
        log_info("network_user_callback->WIFI_STA_CONNECT_ASSOCIAT_TIMEOUT");
        break;
    case WIFI_EVENT_STA_NETWORK_STACK_DHCP_SUCC:
        log_info("network_user_callback->WIFI_EVENT_STA_NETWPRK_STACK_DHCP_SUCC");
        wifi_event_sta_network_stack_dhcp_succ();
        break;
    case WIFI_EVENT_STA_DISCONNECT:
        log_info("network_user_callback->WIFI_STA_DISCONNECT");
        wifi_event_sta_disconnect();
        break;
    case WIFI_EVENT_STA_NETWORK_STACK_DHCP_TIMEOUT:
        log_info("network_user_callback->WIFI_EVENT_STA_NETWPRK_STACK_DHCP_TIMEOUT");
        break;
    case WIFI_EVENT_SMP_CFG_START:
        log_info("network_user_callback->WIFI_EVENT_SMP_CFG_START");
        break;
    case WIFI_EVENT_SMP_CFG_STOP:
        log_info("network_user_callback->WIFI_EVENT_SMP_CFG_STOP");
        break;
    case WIFI_EVENT_SMP_CFG_TIMEOUT:
        log_info("network_user_callback->WIFI_EVENT_SMP_CFG_TIMEOUT");
        net.event = NET_EVENT_SMP_CFG_TIMEOUT;
        net_event_notify(NET_EVENT_FROM_WIFI, &net);
        break;
    case WIFI_EVENT_SMP_CFG_COMPLETED:
        log_info("network_user_callback->WIFI_EVENT_SMP_CFG_COMPLETED");
        net.event = NET_SMP_CFG_COMPLETED;
        net_event_notify(NET_EVENT_FROM_WIFI, &net);
        break;
    case WIFI_EVENT_MP_TEST_START:
        log_info("network_user_callback->WIFI_EVENT_MP_TEST_START");
        break;
    case WIFI_EVENT_MP_TEST_STOP:
        log_info("network_user_callback->WIFI_EVENT_MP_TEST_STOP");
        break;
    case WIFI_EVENT_AP_ON_ASSOC:
        wifi_event_ap_on_assoc(network_ctx);
        break;
    case WIFI_EVENT_AP_ON_DISCONNECTED:
        wifi_event_ap_on_disconnected(network_ctx);
        break;
    default:
        break;
    }

    return ret;
}

static void net_app_init(void)
{
    if (__this->net_app_init_flag) {
        return;
    }
    __this->net_app_init_flag = 1;

#ifdef CONFIG_IPERF_ENABLE
//网络测试工具，使用iperf
    extern void iperf_test(void);
    iperf_test();
#endif
}

static void net_app_uninit(void)
{

}

void wifi_and_network_on(void)
{
    if (wifi_is_on()) {
        return;
    }
    wifi_on();
    net_app_init();
}

void wifi_and_network_off(void)
{
    if (wifi_is_on() == 0) {
        return;
    }
    net_app_uninit();
    wifi_off();
}

void wifi_sta_connect(char *ssid, char *pwd, char save)
{
    if (!wifi_is_on()) {
        wifi_on();
        net_app_init();
    }

    if (save) {
        struct wifi_mode_info info;
        info.mode = STA_MODE;
        wifi_get_mode_cur_info(&info);
        if (strcmp(info.ssid, ssid) || strcmp(info.pwd, pwd)) {
            __this->save_ssid_flag = 1;    //防止输错密码还保存ssid, 等待确保连接上路由器再保存
        }
    }

    __this->request_connect_flag = 1;

    if (save) {
        /* wifi_store_mode_info(STA_MODE,ssid,pwd); */
    }

    wifi_enter_sta_mode(ssid, pwd);

    rf_coexistence_scene_enter(RF_COEXISTENCE_SCENE_WIFI_CONNECT, 10000);
}

int get_wifi_scan_ssid_info(struct wifi_scan_ssid_info **ssid_info)
{
    struct wifi_scan_ssid_info *sta_ssid_info;
    u32 sta_ssid_num = 0;
    sta_ssid_info = wifi_get_scan_result(&sta_ssid_num);
    wifi_clear_scan_result();

    for (u32 i = 0; i < sta_ssid_num; i++) {
        log_info("find scan ssid = [%s]", sta_ssid_info[i].ssid);
    }

    *ssid_info = sta_ssid_info;
    return sta_ssid_num;
}

static void wifi_app_task(void *priv)  //主要是create wifi 线程的
{
    wifi_set_store_ssid_cnt(NETWORK_SSID_INFO_CNT);

#ifdef CONFIG_DUER_SDK_ENABLE
    u8 airkiss_aes_key[16] = {
        0x65, 0x31, 0x63, 0x33, 0x36, 0x31, 0x63, 0x63,
        0x32, 0x39, 0x65, 0x34, 0x33, 0x66, 0x62, 0x38
    };
    wifi_set_airkiss_key(airkiss_aes_key);
#endif

#if 0
    wifi_set_smp_cfg_scan_all_channel(1);
    wifi_set_smp_cfg_airkiss_recv_ssid(1);
#endif

    wifi_set_sta_connect_timeout(CONNECT_TIMEOUT_SEC);

    wifi_set_event_callback(wifi_event_callback);

#if !IP_NAPT_EXT
    struct wifi_mode_info info;
    if (0 == wifi_get_mode_stored_info(&info)) {
        wifi_and_network_on();
        rf_coexistence_scene_enter(RF_COEXISTENCE_SCENE_WIFI_FAST_CONNECT, 5000);
    }
#endif
}

#if TCFG_USER_EMITTER_ENABLE
struct wifi_store_info *get_cur_wifi_info(void);

static void wifi_psm_fast_rsp_task(void *p)
{
    int msg[32];

    while (1) {
        os_task_pend("taskq", msg, ARRAY_SIZE(msg));
    }
}

static void __wifi_psm_run_callback(int power_save)
{
    __this->psm_timer = 0;

    if (get_cur_wifi_info()->mode == STA_MODE && wifi_get_sta_connect_state() == WIFI_STA_NETWORK_STACK_DHCP_SUCC) {
        void RTMPSTAPowerSave(int power_save);
        RTMPSTAPowerSave(power_save);
    } else if (get_cur_wifi_info()->mode == P2P_MODE && wifi_get_sta_connect_state() == WIFI_STA_NETWORK_STACK_DHCP_SUCC) {
        void RTMPP2PPowerSave(int power_save);
        /* RTMPP2PPowerSave(power_save); */
    }
}

static void wifi_psm_run_callback(int power_save)
{
    if (get_cur_wifi_info()->mode == STA_MODE && wifi_get_sta_connect_state() == WIFI_STA_NETWORK_STACK_DHCP_SUCC) {
        void RTMPSTAPowerSave(int power_save);
        RTMPSTAPowerSave(power_save);
    } else if (get_cur_wifi_info()->mode == P2P_MODE && wifi_get_sta_connect_state() == WIFI_STA_NETWORK_STACK_DHCP_SUCC) {
        void RTMPP2PPowerSave(int power_save);
        /* RTMPP2PPowerSave(power_save); */
    }
}

void wifi_psm_run_notify(int power_save)
{
    int msg[3] = {(int)wifi_psm_run_callback, 1, power_save};
    int err = os_taskq_post_type("wifi_psm_fast_rsp", Q_CALLBACK, ARRAY_SIZE(msg), msg);
    if (err) {
        if (power_save == 0 && !__this->psm_timer) {
            __this->psm_timer = sys_timeout_add_to_task("wifi_psm_fast_rsp", NULL, (void (*)(void *))__wifi_psm_run_callback, 50);
        }
        log_error("psm notify error");
    }
}
#endif

#if TCFG_WIFI_ENABLE
static int wireless_net_init(void)   //主要是create wifi 线程的
{
    log_info("wireless_net_init");

#if TCFG_USER_EMITTER_ENABLE
    thread_fork("wifi_psm_fast_rsp", 29, 256, 32, 0, wifi_psm_fast_rsp_task, NULL);
#endif

    return thread_fork("wifi_app_task", 10, 1792, 0, 0, wifi_app_task, NULL);
}
late_initcall(wireless_net_init);
#endif

#endif
