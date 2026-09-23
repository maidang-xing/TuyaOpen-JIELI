/**
 * @file pjsip_platform.c
 * @brief OS/PJLIB related helpers for the PJSIP service
 *
 * Responsibilities:
 * - Initialize the PJLIB caching pool/runtime glue used by this module.
 * - Provide shared formatting and logging helpers for SIP diagnostics.
 * - Build the transport selector objects needed by UDP send paths.
 *
 * Boundaries:
 * - Does not run the SIP worker loop or own application state.
 * - Does not probe Wi-Fi readiness or resolve network topology.
 * - Does not negotiate SDP or generate RTP media payloads.
 */

#include "app_config.h"

#if TCFG_PJSIP_ENABLE

#define LOG_TAG             "[SIP]"
#define LOG_ERROR_ENABLE
#define LOG_INFO_ENABLE
#define LOG_DEBUG_ENABLE
#include "debug.h"

#include "pjsip_internal.h"

void format_reason_text(const pj_str_t *reason, char *buf, unsigned buf_size)
{
    unsigned i;
    unsigned limit;

    PJ_ASSERT_ON_FAIL(buf && buf_size > 0, return);

    buf[0] = '\0';

    if (!reason || !reason->ptr || reason->slen <= 0) {
        return;
    }

    limit = (unsigned)reason->slen;
    if (limit > buf_size - 1) {
        limit = buf_size - 1;
    }

    for (i = 0; i < limit; ++i) {
        char ch = reason->ptr[i];

        if (ch == '\r' || ch == '\n' || ch == '\0') {
            break;
        }

        if ((unsigned char)ch < 0x20 || (unsigned char)ch > 0x7e) {
            ch = '?';
        }

        buf[i] = ch;
    }

    buf[i] = '\0';
}

void dump_sip_msg(const char *tag, pj_pool_t *tmp_pool, pjsip_msg *msg)
{
    char *buf;
    int len;

    if (!tag || !tmp_pool || !msg) {
        return;
    }

    buf = (char *)pj_pool_alloc(tmp_pool, 4096);
    if (!buf) {
        return;
    }

    len = pjsip_msg_print(msg, buf, 4096);
    if (len <= 0) {
        log_error("%s: <print failed>", tag);
        return;
    }

    if (len >= 4096) {
        len = 4095;
    }
    buf[len] = '\0';

    log_debug("%s:\n%s", tag, buf);
}

void log_pj_status(const char *stage, pj_status_t status)
{
    char errbuf[PJ_ERR_MSG_SIZE];
    int os_code = -1;

    if (status >= PJ_ERRNO_START_SYS && status < PJ_ERRNO_START_USER) {
        os_code = PJ_STATUS_TO_OS(status);
    }

    pj_strerror(status, errbuf, sizeof(errbuf));
    log_error("%s failed: %d (%s), os=%d",
              stage, status, errbuf, os_code);
}

void seed_pj_random(const char *tag)
{
    unsigned seed;

    seed = (unsigned)timer_get_ms();
    seed ^= (unsigned)(++live_rand_seq * 0x9e3779b1UL);
    seed ^= (unsigned)(unsigned long)&live_rand_seq;
    pj_srand(seed);

    if (tag) {
        log_debug("%s: pj_srand seed=%u", tag, seed);
    }
}

pj_status_t init_udp_transport_selector(pjsip_tpselector *tp_sel)
{
    PJ_ASSERT_RETURN(tp_sel, PJ_EINVAL);

    if (!udp_transport) {
        return PJ_ENOTFOUND;
    }

    pj_bzero(tp_sel, sizeof(*tp_sel));
    tp_sel->type = PJSIP_TPSELECTOR_TRANSPORT;
    tp_sel->u.transport = udp_transport;
    return PJ_SUCCESS;
}

pj_status_t init_pjlib(void)
{
    pj_status_t status;

    log_info("init_pjlib: version=%s, PJ_HAS_THREADS=%d, PJ_LOG_MAX_LEVEL=%d",
             pj_get_version(), PJ_HAS_THREADS, PJ_LOG_MAX_LEVEL);
    log_info("init_pjlib: pj_init");

    status = pj_init();
    if (status != PJ_SUCCESS) {
        log_pj_status("pj_init", status);
        return status;
    }

    pj_log_set_level(PJ_LOG_MAX_LEVEL);

    log_info("init_pjlib: pjlib_util_init");
    status = pjlib_util_init();
    if (status != PJ_SUCCESS) {
        log_pj_status("pjlib_util_init", status);
        return status;
    }

    log_info("init_pjlib: caching_pool_init");
    pj_caching_pool_init(&cp, &pj_pool_factory_default_policy, 0);

    log_info("init_pjlib: pool_create");
    pool = pj_pool_create(&cp.factory, "pjsip_test", 4000, 4000, NULL);
    if (!pool) {
        log_error("pj_pool_create returned NULL");
        return PJ_ENOMEM;
    }

    log_info("init_pjlib: done");
    return PJ_SUCCESS;
}

#endif
