/**
 * @file pjsip_test.c
 * @brief User-facing PJSIP configuration and startup entry
 *
 * Responsibilities:
 * - Own the built-in default SIP account/runtime configuration.
 * - Expose the SDK init hook used by late_initcall().
 * - Start the background bootstrap thread for the PJSIP service.
 *
 * Boundaries:
 * - Does not implement REGISTER/call state machines.
 * - Does not handle network probing, transport bring-up, or RTP details.
 * - Delegates all runtime SIP/media work to pjsip_core.c and helpers.
 */

#include "app_config.h"

#if TCFG_PJSIP_ENABLE

#include "system/includes.h"
#include "os/os_api.h"
#include "pjsip_internal.h"


#define LOG_TAG             "[SIP]"
#define LOG_ERROR_ENABLE
#define LOG_INFO_ENABLE
#include "debug.h"

#define PJSIP_TEST_THREAD_STACK 4096
#define PJSIP_TEST_START_THREAD_STACK 2048
#define PJSIP_TEST_START_THREAD_PRIO 10

static volatile int g_pjsip_start_pid = -1;
static volatile u8 g_pjsip_start_pending;
static OS_MUTEX g_pjsip_start_mutex;

static const struct pjsip_test_config g_pjsip_test_default_cfg = {
    .sip_port = 5060,
    .basic_rtp_port = 4000,
    .thread_stack_size = PJSIP_TEST_THREAD_STACK,
    .udp_start_retry_max = 100,
    .udp_start_retry_dly_tick = 10,
    .net_ready_wait_timeout_tick = (60 * 100),
    .net_ready_wait_step_tick = 10,

    .account_uri = "sip:xxx@sip2sip.info",
    .registrar_uri = "sip:sip2sip.info",
    .registrar_host = "sip2sip.info",
    .proxy_uri = "<sip:proxy.sipthor.net;lr>",
    .proxy_host = "proxy.sipthor.net",
    .auth_realm = "sip2sip.info",
    .auth_user = "xxx",
    .auth_pass = "xxx",
    .target_uri = "sip:xxx@sip2sip.info",
    .target_host = "sip2sip.info",

    .register_expires = 600,
    .register_refresh_margin = 60,
    .response_timeout_ms = 15000,
    .invite_timeout_ms = 30000,
    .poll_interval_ms = 20,
    .call_hold_ms = 2000,
    .audio_duration_ms = 4000,
    .bye_timeout_ms = 5000,
    .rtp_port_base = 6000,
    .rtp_port_retry = 16,
    .keepalive_interval_sec = 45,
    .keepalive_data = "\r\n",
};

const struct pjsip_test_config *pjsip_test_get_default_config(void)
{
    return &g_pjsip_test_default_cfg;
}

static void pjsip_test_start_done(void)
{
    if (os_mutex_valid(&g_pjsip_start_mutex)) {
        os_mutex_pend(&g_pjsip_start_mutex, 0);
        g_pjsip_start_pending = 0;
        g_pjsip_start_pid = -1;
        os_mutex_post(&g_pjsip_start_mutex);
    } else {
        g_pjsip_start_pending = 0;
        g_pjsip_start_pid = -1;
    }
}

static void pjsip_test_start_task(void *priv)
{
    const struct pjsip_test_config *cfg = pjsip_test_get_default_config();
    pj_status_t status;

    PJ_UNUSED_ARG(priv);

    g_pjsip_test_cfg = cfg;

    log_info("starting SIP service");
    if (wait_network_ready() != 0) {
        log_info("network not ready for SIP start, wait for next connect event");
        pjsip_test_start_done();
        return;
    }

    status = pjsip_test_service_start_default();
    if (status != PJ_SUCCESS) {
        log_error("pjsip_test_service_start_default=%d", status);
        pjsip_test_start_done();
        return;
    }

    log_info("start register account");
    status = pjsip_test_register_account();
    if (status != PJ_SUCCESS) {
        log_error("pjsip_test_register_account=%d", status);
        pjsip_test_start_done();
        return;
    }

    log_info("start call %s", cfg->target_uri);
    status = pjsip_test_make_call(cfg->target_uri);
    if (status != PJ_SUCCESS) {
        log_error("pjsip_test_make_call(%s)=%d",
                  cfg->target_uri,
                  status);
    }
    pjsip_test_start_done();
}

int pjsip_test_main(void)
{
    if (!os_mutex_valid(&g_pjsip_start_mutex)) {
        os_mutex_create(&g_pjsip_start_mutex);
    }

    os_mutex_pend(&g_pjsip_start_mutex, 0);
    if (g_pjsip_start_pending) {
        os_mutex_post(&g_pjsip_start_mutex);
        return 0;
    }
    g_pjsip_start_pending = 1;
    g_pjsip_start_pid = -1;
    os_mutex_post(&g_pjsip_start_mutex);

    if (thread_fork("pjsip_start",
                    PJSIP_TEST_START_THREAD_PRIO,
                    PJSIP_TEST_START_THREAD_STACK,
                    0,
                    (int *)&g_pjsip_start_pid,
                    pjsip_test_start_task,
                    NULL) != OS_NO_ERR) {
        pjsip_test_start_done();
        log_error("create start task failed");
    }

    return 0;
}

late_initcall(pjsip_test_main);

#endif

