#include "wifi/wifi_connect.h"
#include "lwip/sockets.h"
#include "lwip/netdb.h"
#include "os/os_api.h"
#include "system/init.h"
#include "lwip.h"
#include "dhcp_srv/dhcp_srv.h"
#include "lwip/dns.h"
#include "device/device.h"
#include "system/app_core.h"
#include "server/server_core.h"
#include "system/timer.h"
#include "asm/debug.h"
#include "app_config.h"
#include "wifi_ap_sta.h"

#define LOG_TAG_CONST       WIFI_AP_STA
#define LOG_TAG             "[WIFI_AP_STA]"
#define LOG_ERROR_ENABLE
#define LOG_INFO_ENABLE
#define LOG_DUMP_ENABLE
#include "debug.h"

#define WIFI_AP_SSID       "wl83_wifi_bbm_ap"
#define WIFI_AP_PWD        "12345678"

#if BBM_WIFI_PA_ENABLE
#define WIFI_MAX_PWR            6                   // 最大发射功率
#else
#define WIFI_MAX_PWR            9                   // 最大发射功率
#endif


static int wifi_event_callback(void *network_ctx, enum WIFI_EVENT event);
static void wifi_net_state_timer_cb(void *p);
static void wifi_set_lan_setting_info(void);
static u16 net_state_timer = 0;


void wifi_ap_init(void)
{
    log_info("\n========== WiFi Ap Init ==========\n");

    wifi_set_event_callback(wifi_event_callback);

    wifi_on();
    wifi_set_pwr(WIFI_MAX_PWR);

    net_state_timer = sys_timer_add(NULL, wifi_net_state_timer_cb, 5000);
}

void wifi_sta_connect(void)
{
    wifi_set_sta_connect_best_ssid(0);
    wifi_enter_sta_mode(WIFI_AP_SSID, WIFI_AP_PWD);
}

static void wifi_net_state_timer_cb(void *p)
{
    printf("WIFI U= %d KB/s, D= %d KB/s\r\n",
           wifi_get_upload_rate() / 1024, wifi_get_download_rate() / 1024);

    malloc_stats();
}

static int wifi_event_callback(void *network_ctx, enum WIFI_EVENT event)
{
    int ret = 0;
    switch (event) {
    case WIFI_EVENT_MODULE_INIT:
        log_info("|network_user_callback->WIFI_EVENT_MODULE_INIT\n");
        wifi_set_sta_connect_timeout(30);   //配置STA模式连接超时后事件回调通知时间
        wifi_set_smp_cfg_timeout(30);       //配置MONITOR模式超时后事件回调通知时间
        wifi_set_lan_setting_info();
        struct wifi_store_info wifi_default_mode_parm = {0};
        wifi_default_mode_parm.mode = AP_MODE;
        strcpy(wifi_default_mode_parm.ssid[wifi_default_mode_parm.mode - STA_MODE], WIFI_AP_SSID);
        strcpy(wifi_default_mode_parm.pwd[wifi_default_mode_parm.mode - STA_MODE], WIFI_AP_PWD);
        wifi_set_default_mode(&wifi_default_mode_parm, 1, 1);
        break;
    case WIFI_EVENT_MODULE_START:
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
        break;
    case WIFI_EVENT_MODULE_STOP:
        log_info("|network_user_callback->WIFI_EVENT_MODULE_STOP\n");
        break;
    case WIFI_EVENT_AP_START:
        log_info("|network_user_callback->WIFI_EVENT_AP_START,CH=%d\n", wifi_get_channel());
        break;
    case WIFI_EVENT_AP_STOP:
        log_info("|network_user_callback->WIFI_EVENT_AP_STOP\n");
        break;
    case WIFI_EVENT_STA_START:
        log_info("|network_user_callback->WIFI_EVENT_STA_START\n");
        break;
    case WIFI_EVENT_MODULE_START_ERR:
        log_info("|network_user_callback->WIFI_EVENT_MODULE_START_ERR\n");
        break;
    case WIFI_EVENT_STA_STOP:
        log_info("|network_user_callback->WIFI_EVENT_STA_STOP\n");
        break;
    case WIFI_EVENT_STA_DISCONNECT:
        log_info("|network_user_callback->WIFI_STA_DISCONNECT\n");
        break;
    case WIFI_EVENT_STA_SCAN_COMPLETED:
        log_info("|network_user_callback->WIFI_STA_SCAN_COMPLETED\n");
        break;
    case WIFI_EVENT_STA_CONNECT_SUCC:
        log_info("|network_user_callback->WIFI_STA_CONNECT_SUCC,CH=%d\r\n", wifi_get_channel());
        break;
    case WIFI_EVENT_MP_TEST_START:
        log_info("|network_user_callback->WIFI_EVENT_MP_TEST_START\n");
        break;
    case WIFI_EVENT_MP_TEST_STOP:
        log_info("|network_user_callback->WIFI_EVENT_MP_TEST_STOP\n");
        break;
    case WIFI_EVENT_STA_CONNECT_TIMEOUT_NOT_FOUND_SSID:
        log_info("|network_user_callback->WIFI_STA_CONNECT_TIMEOUT_NOT_FOUND_SSID\n");
        break;
    case WIFI_EVENT_STA_CONNECT_ASSOCIAT_FAIL:
        log_info("|network_user_callback->WIFI_STA_CONNECT_ASSOCIAT_FAIL .....\n");
        break;
    case WIFI_EVENT_STA_CONNECT_ASSOCIAT_TIMEOUT:
        log_info("|network_user_callback->WIFI_STA_CONNECT_ASSOCIAT_TIMEOUT .....\n");
        break;
    case WIFI_EVENT_STA_NETWORK_STACK_DHCP_SUCC:
        log_info("|network_user_callback->WIFI_EVENT_STA_NETWPRK_STACK_DHCP_SUCC\n");
        break;
    case WIFI_EVENT_STA_NETWORK_STACK_DHCP_TIMEOUT:
        log_info("|network_user_callback->WIFI_EVENT_STA_NETWPRK_STACK_DHCP_TIMEOUT\n");
        break;
    case WIFI_EVENT_P2P_START:
        log_info("|network_user_callback->WIFI_EVENT_P2P_START\n");
        break;
    case WIFI_EVENT_P2P_STOP:
        log_info("|network_user_callback->WIFI_EVENT_P2P_STOP\n");
        break;
    case WIFI_EVENT_P2P_GC_DISCONNECTED:
        log_info("|network_user_callback->WIFI_EVENT_P2P_GC_DISCONNECTED\n");
        break;
    case WIFI_EVENT_P2P_GC_NETWORK_STACK_DHCP_SUCC:
        log_info("|network_user_callback->WIFI_EVENT_P2P_GC_NETWORK_STACK_DHCP_SUCC\n");
        break;
    case WIFI_EVENT_P2P_GC_NETWORK_STACK_DHCP_TIMEOUT:
        log_info("|network_user_callback->WIFI_EVENT_P2P_GC_NETWORK_STACK_DHCP_TIMEOUT\n");
        break;
    case WIFI_EVENT_SMP_CFG_START:
        log_info("|network_user_callback->WIFI_EVENT_SMP_CFG_START\n");
        break;
    case WIFI_EVENT_SMP_CFG_STOP:
        log_info("|network_user_callback->WIFI_EVENT_SMP_CFG_STOP\n");
        break;
    case WIFI_EVENT_SMP_CFG_TIMEOUT:
        log_info("|network_user_callback->WIFI_EVENT_SMP_CFG_TIMEOUT\n");
        break;
    case WIFI_EVENT_SMP_CFG_COMPLETED:
        log_info("|network_user_callback->WIFI_EVENT_SMP_CFG_COMPLETED\n");
        break;
    case WIFI_EVENT_PM_SUSPEND:
        log_info("|network_user_callback->WIFI_EVENT_PM_SUSPEND\n");
        break;
    case WIFI_EVENT_PM_RESUME:
        log_info("|network_user_callback->WIFI_EVENT_PM_RESUME\n");
        break;
    case WIFI_EVENT_AP_ON_ASSOC:
#ifdef TCFG_WIFI_ENABLE
        lwip_set_default_netif(WIFI_NETIF);   //设置本地网卡为默认模块,兼容双网卡
#endif
        struct eth_addr *hwaddr = (struct eth_addr *)network_ctx;
        log_info("WIFI_EVENT_AP_ON_ASSOC hwaddr = %02x:%02x:%02x:%02x:%02x:%02x \r\n\r\n",
                 hwaddr->addr[0], hwaddr->addr[1], hwaddr->addr[2], hwaddr->addr[3], hwaddr->addr[4], hwaddr->addr[5]);
        break;
    case WIFI_EVENT_AP_ON_DISCONNECTED:
        hwaddr = (struct eth_addr *)network_ctx;
        struct ip4_addr ipaddr;
        dhcps_get_ipaddr(hwaddr->addr, &ipaddr);
        log_info("WIFI_EVENT_AP_ON_DISCONNECTED hwaddr = %02x:%02x:%02x:%02x:%02x:%02x, ipaddr = [%d.%d.%d.%d] \r\n\r\n",
                 hwaddr->addr[0], hwaddr->addr[1], hwaddr->addr[2], hwaddr->addr[3], hwaddr->addr[4], hwaddr->addr[5],
                 ip4_addr1(&ipaddr), ip4_addr2(&ipaddr), ip4_addr3(&ipaddr), ip4_addr4(&ipaddr));
        break;
    case WIFI_EVENT_STA_IP_GOT_IPV6_SUCC:
        log_info("network_user_callback->WIFI_EVENT_STA_IP_GOT_IPV6_SUCC");
        break;
    default:
        break;
    }

    return ret;
}


static void wifi_set_lan_setting_info(void)
{
    struct lan_setting lan_setting_info = {
        .WIRELESS_IP_ADDR0  = 192,
        .WIRELESS_IP_ADDR1  = 168,
        .WIRELESS_IP_ADDR2  = 1,
        .WIRELESS_IP_ADDR3  = 1,

        .WIRELESS_NETMASK0  = 255,
        .WIRELESS_NETMASK1  = 255,
        .WIRELESS_NETMASK2  = 255,
        .WIRELESS_NETMASK3  = 0,

        .WIRELESS_GATEWAY0  = 192,
        .WIRELESS_GATEWAY1  = 168,
        .WIRELESS_GATEWAY2  = 1,
        .WIRELESS_GATEWAY3  = 1,

        .SERVER_IPADDR1  = 192,
        .SERVER_IPADDR2  = 168,
        .SERVER_IPADDR3  = 1,
        .SERVER_IPADDR4  = 1,

        .CLIENT_IPADDR1  = 192,
        .CLIENT_IPADDR2  = 168,
        .CLIENT_IPADDR3  = 1,
        .CLIENT_IPADDR4  = 2,

        .SUB_NET_MASK1   = 255,
        .SUB_NET_MASK2   = 255,
        .SUB_NET_MASK3   = 255,
        .SUB_NET_MASK4   = 0,
    };
    net_set_lan_info(&lan_setting_info);
}

__attribute__((weak)) void clear_wpa_scan_record(void)
{

}




