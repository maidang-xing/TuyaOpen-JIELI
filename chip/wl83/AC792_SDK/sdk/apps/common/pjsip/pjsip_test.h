#ifndef APPS_COMMON_PJSIP_PJSIP_TEST_H
#define APPS_COMMON_PJSIP_PJSIP_TEST_H

#include "app_config.h"

#include <pjlib.h>

/*
 * Public API for the SIP service built on top of PJSIP.
 *
 * Module layout:
 * - Public entry/header: apps/common/pjsip/pjsip_test.[ch]
 * - Internal implementation: apps/common/pjsip/pjsip_*.c
 * - Compatibility wrapper: apps/demo/demo_wifi/pjsip_test.h
 *
 * Build and enable rules:
 * - The Makefiles compile the module unconditionally.
 * - CONFIG_PJSIP_ENABLE controls whether the PJSIP code is compiled in.
 * - When CONFIG_PJSIP_ENABLE is 0, this header exposes stub APIs so
 *   application code can still include it without extra #ifdef blocks.
 *
 * Typical usage:
 * 1. Call pjsip_test_service_start_default() once during system init.
 * 2. After network is ready, call pjsip_test_register_account().
 * 3. Check registration state with pjsip_test_get_reg_state().
 * 4. Make an outgoing call with pjsip_test_make_call(), or wait for
 *    incoming call logs and then answer with pjsip_test_answer_call().
 * 5. Hang up or reject a call with pjsip_test_hangup_call().
 *
 * Notes:
 * - The module creates and owns the SIP worker thread internally.
 * - REGISTER refresh and UDP keepalive are maintained automatically
 *   after successful registration.
 * - The current implementation supports only one active call at a time.
 */

/* Runtime configuration passed to pjsip_test_service_start(). */
struct pjsip_test_config {
    /* Local SIP listen port. Usually 5060. */
    unsigned sip_port;
    /* RTP port used by the basic media self test. */
    unsigned basic_rtp_port;
    /* Stack size of the internal SIP worker thread. */
    unsigned thread_stack_size;
    /* Max retry count when starting UDP SIP transport. */
    unsigned udp_start_retry_max;
    /* Delay tick between UDP transport start retries. */
    unsigned udp_start_retry_dly_tick;
    /* Max wait tick for network readiness during startup. */
    unsigned net_ready_wait_timeout_tick;
    /* Poll step tick while waiting for network readiness. */
    unsigned net_ready_wait_step_tick;
    /* Local account URI, for example "sip:3000@test.uc". */
    const char *account_uri;
    /* Registrar URI, for example "sip:test.uc". */
    const char *registrar_uri;
    /* Registrar host name used only for diagnostics. */
    const char *registrar_host;
    /* Outbound proxy URI, usually with lr parameter. */
    const char *proxy_uri;
    /* Proxy host name used only for diagnostics. */
    const char *proxy_host;
    /* Digest auth realm. */
    const char *auth_realm;
    /* Digest auth user name. */
    const char *auth_user;
    /* Digest auth password. */
    const char *auth_pass;
    /* Default target URI used by the legacy one-shot test API. */
    const char *target_uri;
    /* Default target host used only for diagnostics. */
    const char *target_host;
    /* REGISTER expires value, in seconds. */
    unsigned register_expires;
    /* Refresh margin before registration expires, in seconds. */
    unsigned register_refresh_margin;
    /* Timeout for waiting REGISTER final response, in milliseconds. */
    unsigned response_timeout_ms;
    /* Timeout for outgoing INVITE setup, in milliseconds. */
    unsigned invite_timeout_ms;
    /* Event loop poll interval of the SIP worker thread, in milliseconds. */
    unsigned poll_interval_ms;
    /* Hold duration after connect in legacy one-shot mode, in milliseconds. */
    unsigned call_hold_ms;
    /* Duration of simulated outgoing audio, in milliseconds. */
    unsigned audio_duration_ms;
    /* Timeout for waiting BYE completion in legacy one-shot mode. */
    unsigned bye_timeout_ms;
    /* Base RTP port used for live media session allocation. */
    unsigned rtp_port_base;
    /* Retry count when allocating RTP transport. */
    unsigned rtp_port_retry;
    /* UDP keepalive interval after registration, in seconds. Zero disables it. */
    unsigned keepalive_interval_sec;
    /* Raw keepalive payload. For UDP NAT keepalive, usually "\r\n". */
    const char *keepalive_data;
};

/* Registration state exposed to the application layer. */
enum pjsip_test_reg_state {
    /* Service is idle and has not registered yet. */
    PJSIP_TEST_REG_IDLE = 0,
    /* REGISTER request has been sent and final response is pending. */
    PJSIP_TEST_REG_REGISTERING,
    /* Registration is valid and auto refresh or keepalive are active. */
    PJSIP_TEST_REG_REGISTERED,
    /* Last registration attempt failed. */
    PJSIP_TEST_REG_FAILED,
};

/* Single-call state exposed to the application layer. */
enum pjsip_test_call_state {
    /* No active or pending call. */
    PJSIP_TEST_CALL_IDLE = 0,
    /* Outgoing INVITE has been sent. */
    PJSIP_TEST_CALL_OUTGOING,
    /* Incoming INVITE has been received. */
    PJSIP_TEST_CALL_INCOMING,
    /* Remote side is ringing, or local side is presenting incoming ringing. */
    PJSIP_TEST_CALL_RINGING,
    /* 200 OK has been sent or received and the call is moving to confirmed. */
    PJSIP_TEST_CALL_CONNECTING,
    /* Call is established. */
    PJSIP_TEST_CALL_ESTABLISHED,
    /* Call has been terminated and will return to IDLE. */
    PJSIP_TEST_CALL_DISCONNECTED,
};

#if TCFG_PJSIP_ENABLE

/* Returns the built-in default configuration. Do not modify it in place. */
const struct pjsip_test_config *pjsip_test_get_default_config(void);

/* Converts a registration state enum value to readable text. */
const char *pjsip_test_reg_state_name(enum pjsip_test_reg_state state);

/* Converts a call state enum value to readable text. */
const char *pjsip_test_call_state_name(enum pjsip_test_call_state state);

/* Returns current registration state. This call is non-blocking. */
enum pjsip_test_reg_state pjsip_test_get_reg_state(void);

/* Returns current call state. This call is non-blocking. */
enum pjsip_test_call_state pjsip_test_get_call_state(void);

/*
 * Returns current peer URI.
 * - For incoming call: caller URI.
 * - For outgoing call: callee URI.
 * - Returns an empty string when there is no valid call context.
 */
const char *pjsip_test_get_current_peer_uri(void);

/*
 * Starts the internal SIP service with caller-provided configuration.
 *
 * Usage:
 * - Call once during system init.
 * - Repeated calls after startup are ignored.
 * - This API starts the service only. It does not send REGISTER by itself.
 */
pj_status_t pjsip_test_service_start(const struct pjsip_test_config *cfg);

/* Starts the SIP service with pjsip_test_get_default_config(). */
pj_status_t pjsip_test_service_start_default(void);

/*
 * Sends REGISTER and waits for completion.
 *
 * On success:
 * - final response 200 OK has been received
 * - state becomes PJSIP_TEST_REG_REGISTERED
 * - automatic REGISTER refresh and keepalive remain active
 */
pj_status_t pjsip_test_register_account(void);

/*
 * Starts an outgoing call to the specified SIP URI.
 *
 * Preconditions:
 * - service has already been started
 * - registration state is PJSIP_TEST_REG_REGISTERED
 * - there is no active call
 *
 * This API only starts the call. Call progress must be checked through
 * pjsip_test_get_call_state().
 */
pj_status_t pjsip_test_make_call(const char *target_uri);

/*
 * Answers the current incoming call with 200 OK.
 *
 * Valid when call state is PJSIP_TEST_CALL_INCOMING or
 * PJSIP_TEST_CALL_RINGING.
 */
pj_status_t pjsip_test_answer_call(void);

/*
 * Hangs up or rejects the current call.
 *
 * Behavior:
 * - For an incoming ringing call: reject the call.
 * - For an outgoing or established call: send normal hangup.
 */
pj_status_t pjsip_test_hangup_call(void);

/*
 * Legacy one-shot self-test API.
 *
 * This API performs:
 * init -> register -> make one call -> send test audio -> cleanup -> exit
 *
 * Use it only for bring-up or lab verification. It is not the persistent
 * service-mode API.
 */
pj_status_t pjsip_test_run(const struct pjsip_test_config *cfg);

/* Legacy one-shot self-test using the default configuration. */
pj_status_t pjsip_test_run_default(void);

/* SDK init hook. Usually no need to call it manually when using late_initcall. */
int pjsip_test_main(void);

#else

static inline const struct pjsip_test_config *pjsip_test_get_default_config(void)
{
    return NULL;
}

static inline const char *pjsip_test_reg_state_name(enum pjsip_test_reg_state state)
{
    PJ_UNUSED_ARG(state);
    return "disabled";
}

static inline const char *pjsip_test_call_state_name(enum pjsip_test_call_state state)
{
    PJ_UNUSED_ARG(state);
    return "disabled";
}

static inline enum pjsip_test_reg_state pjsip_test_get_reg_state(void)
{
    return PJSIP_TEST_REG_IDLE;
}

static inline enum pjsip_test_call_state pjsip_test_get_call_state(void)
{
    return PJSIP_TEST_CALL_IDLE;
}

static inline const char *pjsip_test_get_current_peer_uri(void)
{
    return "";
}

static inline pj_status_t pjsip_test_service_start(const struct pjsip_test_config *cfg)
{
    PJ_UNUSED_ARG(cfg);
    return PJ_ENOTSUP;
}

static inline pj_status_t pjsip_test_service_start_default(void)
{
    return PJ_ENOTSUP;
}

static inline pj_status_t pjsip_test_register_account(void)
{
    return PJ_ENOTSUP;
}

static inline pj_status_t pjsip_test_make_call(const char *target_uri)
{
    PJ_UNUSED_ARG(target_uri);
    return PJ_ENOTSUP;
}

static inline pj_status_t pjsip_test_answer_call(void)
{
    return PJ_ENOTSUP;
}

static inline pj_status_t pjsip_test_hangup_call(void)
{
    return PJ_ENOTSUP;
}

static inline pj_status_t pjsip_test_run(const struct pjsip_test_config *cfg)
{
    PJ_UNUSED_ARG(cfg);
    return PJ_ENOTSUP;
}

static inline pj_status_t pjsip_test_run_default(void)
{
    return PJ_ENOTSUP;
}

static inline int pjsip_test_main(void)
{
    return 0;
}

#endif

#endif

