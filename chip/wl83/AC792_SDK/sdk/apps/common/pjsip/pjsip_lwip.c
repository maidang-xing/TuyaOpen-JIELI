/**
 * @file pjsip_lwip.c
 * @brief lwIP/network related helpers for the PJSIP service
 *
 * Responsibilities:
 * - Query local IP information from the WL83/lwIP stack.
 * - Wait until the Wi-Fi data path is ready before SIP bring-up.
 * - Print DNS and target routing diagnostics used during SIP debugging.
 *
 * Boundaries:
 * - Does not manage Wi-Fi association or DHCP policy.
 * - Does not create SIP transports or parse SIP messages.
 * - Serves only as a thin network environment helper for the SIP module.
 */

#include "app_config.h"

#if TCFG_PJSIP_ENABLE

#define LOG_TAG             "[SIP]"
#define LOG_ERROR_ENABLE
#define LOG_INFO_ENABLE
#define LOG_DEBUG_ENABLE
#include "debug.h"

#include "pjsip_internal.h"


static int query_sta_network_ready(struct netif_info *netif_info,
                                   struct wifi_mode_info *mode_info,
                                   enum wifi_sta_connect_state *sta_state)
{
    struct netif_info local_netif_info;
    struct wifi_mode_info local_mode_info;
    enum wifi_sta_connect_state local_sta_state;

    if (!netif_info) {
        netif_info = &local_netif_info;
    }
    if (!mode_info) {
        mode_info = &local_mode_info;
    }
    if (!sta_state) {
        sta_state = &local_sta_state;
    }

    pj_bzero(netif_info, sizeof(*netif_info));
    lwip_get_netif_info(WIFI_NETIF, netif_info);

    mode_info->mode = NONE_MODE;
    mode_info->ssid = NULL;
    mode_info->pwd = NULL;
    wifi_get_mode_cur_info(mode_info);

    *sta_state = wifi_get_sta_connect_state();

    return (mode_info->mode == STA_MODE &&
            netif_info->ip != 0 &&
            *sta_state == WIFI_STA_NETWORK_STACK_DHCP_SUCC);
}

pj_status_t get_local_ip_string(char *buf, unsigned buf_size)
{
    struct netif_info netif_info;
    struct wifi_mode_info mode_info;
    enum wifi_sta_connect_state sta_state;

    PJ_ASSERT_RETURN(buf && buf_size >= 16, PJ_EINVAL);

    if (!query_sta_network_ready(&netif_info, &mode_info, &sta_state)) {
        log_debug("get_local_ip_string: network not ready (mode=%d, sta_state=%d, ip=0x%08x)",
                  mode_info.mode,
                  sta_state,
                  (unsigned int)netif_info.ip);
        return PJ_ENOTFOUND;
    }

    if (!inet_ntoa_r(netif_info.ip, buf, (int)buf_size)) {
        return PJ_EUNKNOWN;
    }

    return PJ_SUCCESS;
}

void log_host_resolution(const char *label, const char *host)
{
    pj_status_t status;
    pj_str_t host_str;
    pj_addrinfo ai[2];
    unsigned count = PJ_ARRAY_SIZE(ai);
    char addr_buf[64];

    pj_cstr(&host_str, host);
    status = pj_getaddrinfo(pj_AF_INET(), &host_str, &count, ai);
    if (status != PJ_SUCCESS || count == 0) {
        if (status == PJ_SUCCESS) {
            status = PJ_ERESOLVE;
        }
        log_pj_status(label, status);
        return;
    }

    pj_sockaddr_print(&ai[0].ai_addr, addr_buf, sizeof(addr_buf), 0);
    log_debug("%s: %s -> %s", label, host, addr_buf);
}

void log_routed_target_probe(const char *label,
                             const char *uri,
                             const char *host)
{
    PJ_ASSERT_ON_FAIL(label && uri && host, return);

    if (LIVE_SIP_PROXY_URI[0] != '\0') {
        log_debug("%s: %s via proxy, skip host pre-resolve (%s)",
                  label, uri, host);
        return;
    }

    log_host_resolution(label, host);
}

int wait_network_ready(void)
{
    struct netif_info netif_info;
    struct wifi_mode_info mode_info;
    enum wifi_sta_connect_state sta_state;
    int wait_tick = 0;

    log_debug("wait_network: begin");

    while (wait_tick < NET_READY_WAIT_TIMEOUT_TICK) {

        if (query_sta_network_ready(&netif_info, &mode_info, &sta_state)) {
            log_debug("wait_network: ready (mode=%d, sta_state=%d, ip=0x%08x)",
                      mode_info.mode, sta_state, (unsigned int)netif_info.ip);
            return 0;
        }

        os_time_dly(NET_READY_WAIT_STEP_TICK);
        wait_tick += NET_READY_WAIT_STEP_TICK;
    }

    query_sta_network_ready(&netif_info, &mode_info, &sta_state);
    log_info("[WARN] wait_network timeout (mode=%d, sta_state=%d, ip=0x%08x)",
             mode_info.mode,
             sta_state,
             (unsigned int)netif_info.ip);
    return -1;
}

#endif
