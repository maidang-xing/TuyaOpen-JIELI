#include "app_config.h"

#if TCFG_ETH_ENABLE

#include "system/init.h"
#include "device/device.h"
#include "lwip.h"
#include "eth/eth_phy.h"
#include "event/device_event.h"
#include "os/os_api.h"

#define LOG_TAG             "[ETH]"
#define LOG_ERROR_ENABLE
#define LOG_DEBUG_ENABLE
#define LOG_INFO_ENABLE
#define LOG_DUMP_ENABLE
#define LOG_CLI_ENABLE
#include "debug.h"


int eth_lwip_event_cb(void *lwip_ctx, enum LWIP_EVENT event)
{
    char ip_addr[32];
    char gw_addr[32];

    switch (event) {
    case LWIP_WIRE_DHCP_BOUND_TIMEOUT:
        break;

    case LWIP_WIRE_DHCP_BOUND_SUCC:
        Get_IPAddress(ETH_NETIF, ip_addr);
        get_gateway(ETH_NETIF, gw_addr);
        log_info("ETH DHCP SUCC, IP:[%s] , GW:[%s]", ip_addr, gw_addr);
        lwip_set_default_netif(ETH_NETIF);
        break;

    default:
        break;
    }

    return 0;
}

static int eth_state_cb(void *priv, eth_event_t event)
{
    switch (event) {
    case ETH_EVENT_LINK_ON:
        log_info("ETH_EVENT_LINK_ON");
        break;

    case ETH_EVENT_LINK_OFF:
        log_info("ETH_EVENT_LINK_OFF");
        break;

    default:
        return -1;
    }

    return 0;
}

static void eth_set_lan_setting_info(void *device)
{
    struct lan_setting lan_setting_info = {
        .WIRELESS_IP_ADDR0  = 172,
        .WIRELESS_IP_ADDR1  = 16,
        .WIRELESS_IP_ADDR2  = 109,
        .WIRELESS_IP_ADDR3  = 152,

        .WIRELESS_NETMASK0  = 255,
        .WIRELESS_NETMASK1  = 255,
        .WIRELESS_NETMASK2  = 255,
        .WIRELESS_NETMASK3  = 0,

        .WIRELESS_GATEWAY0  = 172,
        .WIRELESS_GATEWAY1  = 16,
        .WIRELESS_GATEWAY2  = 109,
        .WIRELESS_GATEWAY3  = 254,

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

    dev_ioctl(device, IOCTL_ETH_SET_LAN_SETTING, (u32)&lan_setting_info);
}

static void eth_net_task(void *arg)
{
    char mac_addr[6] = {0x9c, 0x37, 0xf4, 0x0e, 0x4d, 0xc9};

    while (1) {
        void *dev = dev_open("eth", NULL);
        if (!dev) {
            return;
        }

        dev_ioctl(dev, IOCTL_ETH_SET_MAC_ADDR, (int)mac_addr);

        eth_set_lan_setting_info(dev);

        dev_ioctl(dev, IOCTL_ETH_EVENT_CB_FUNC, (u32)eth_state_cb);

        dev_ioctl(dev, IOCTL_ETH_NETWORK_START, 0);

        os_time_dly(6000 * 60);

        dev_ioctl(dev, IOCTL_ETH_NETWORK_STOP, 0);

        dev_close(dev);

        os_time_dly(500);
    }
}

static int wire_net_init(void)//主要是有线网卡线程的
{
    return thread_fork("eth_net_task", 10, 512, 0, 0, eth_net_task, NULL);
}
late_initcall(wire_net_init);

#endif
