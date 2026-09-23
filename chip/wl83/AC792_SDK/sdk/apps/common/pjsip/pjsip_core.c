/**
 * @file pjsip_core.c
 * @brief Core SIP service, state machine, and call control
 *
 * Responsibilities:
 * - Own the SIP service lifecycle and worker thread loop.
 * - Handle REGISTER, incoming/outgoing INVITE, answer, hangup, and keepalive.
 * - Bridge low-level PJSIP callbacks to application-visible states.
 * - Keep the one-shot verification path used for bring-up.
 *
 * Boundaries:
 * - Does not own board/network readiness discovery logic.
 * - Does not implement pjmedia RTP generation or codec payload building.
 * - Uses low-level PJSIP APIs only; it is not a full pjsua application layer.
 */

#include "app_config.h"

#if TCFG_PJSIP_ENABLE

#define LOG_TAG             "[SIP]"
#define LOG_ERROR_ENABLE
#define LOG_INFO_ENABLE
#define LOG_DEBUG_ENABLE
#include "debug.h"

#include "pjsip_internal.h"

const struct pjsip_test_config *g_pjsip_test_cfg;

pj_caching_pool cp;
pjsip_endpoint *sip_endpt = NULL;
pjsip_transport *udp_transport = NULL;
pjsip_regc *live_regc = NULL;
pjsip_inv_session *live_inv = NULL;
pjmedia_transport *live_media_transport = NULL;
pjmedia_endpt *med_endpt = NULL;
pj_pool_t *pool = NULL;

struct live_reg_test_state live_reg_test;
struct live_sip_test_state live_sip_test;
struct live_audio_tx_state live_audio_tx;
struct live_audio_rx_state live_audio_rx;

unsigned live_rand_seq;

enum pjsip_test_command_type {
    PJSIP_TEST_CMD_NONE = 0,
    PJSIP_TEST_CMD_REGISTER,
    PJSIP_TEST_CMD_MAKE_CALL,
    PJSIP_TEST_CMD_ANSWER_CALL,
    PJSIP_TEST_CMD_HANGUP_CALL,
};

enum pjsip_test_call_dir {
    PJSIP_TEST_CALL_DIR_NONE = 0,
    PJSIP_TEST_CALL_DIR_OUTGOING,
    PJSIP_TEST_CALL_DIR_INCOMING,
};

struct pjsip_test_command {
    enum pjsip_test_command_type type;
    char target_uri[PJSIP_MAX_URL_SIZE];
    pj_bool_t pending;
    pj_bool_t dispatched;
};

struct pjsip_test_service {
    pj_bool_t thread_started;
    pj_bool_t ready;
    pj_bool_t initialized;
    pj_bool_t init_done;
    pj_status_t init_status;
    int thread_pid;
    enum pjsip_test_reg_state reg_state;
    enum pjsip_test_call_state call_state;
    enum pjsip_test_call_dir call_dir;
    pj_bool_t call_cleanup_pending;
    char current_peer_uri[PJSIP_MAX_URL_SIZE];
    unsigned long next_audio_tick_ms;
    unsigned long next_keepalive_tick_ms;
    pjsip_transport *ka_transport;
    pj_sockaddr ka_target;
    int ka_target_len;
    OS_SEM ready_sem;
    OS_SEM done_sem;
    OS_MUTEX api_mutex;
    struct pjsip_test_command cmd;
    pj_status_t last_cmd_status;
};

static struct pjsip_test_service g_pjsip_test_service;
static struct pjsip_test_config g_pjsip_test_runtime_cfg;

static pj_bool_t pjsip_test_on_rx_request(pjsip_rx_data *rdata);
static pj_bool_t pjsip_test_on_rx_response(pjsip_rx_data *rdata);
static pj_status_t pjsip_test_on_tx_request(pjsip_tx_data *tdata);
static void live_reg_on_complete(struct pjsip_regc_cbparam *param);
static void live_reg_on_tsx(struct pjsip_regc_tsx_cb_param *param);
static void live_sip_reset(void);
static void live_inv_on_state_changed(pjsip_inv_session *inv, pjsip_event *e);
static void live_inv_on_media_update(pjsip_inv_session *inv_ses,
                                     pj_status_t status);
static void live_inv_on_tsx_state_changed(pjsip_inv_session *inv,
        pjsip_transaction *tsx,
        pjsip_event *e);
static void pjsip_test_service_task(void *priv);
static pj_status_t pjsip_test_service_init(const struct pjsip_test_config *cfg);
static void pjsip_test_service_loop(void);
static pj_status_t service_submit_command(enum pjsip_test_command_type type,
        const char *target_uri,
        unsigned timeout_ms);
static void service_complete_command(pj_status_t status);
static void service_set_reg_state(enum pjsip_test_reg_state state);
static void service_set_call_state(enum pjsip_test_call_state state);
static void service_set_peer_uri(const char *uri);
static void service_reset_call_session(void);
static void service_release_keepalive(void);
static void service_release_call_media(void);
static pj_status_t service_send_udp_keepalive(void);
static void service_update_keepalive(struct pjsip_regc_cbparam *param);
static pj_status_t service_handle_register_command(void);
static pj_status_t service_handle_make_call(const char *target_uri);
static pj_status_t service_handle_answer_call(void);
static pj_status_t service_handle_hangup_call(void);
static void service_process_pending_command(void);
static pj_status_t service_handle_incoming_invite(pjsip_rx_data *rdata);
static pj_status_t get_live_register_result(void);
static pj_status_t wait_for_live_register_final(void);

static pjsip_module pjsip_test_module = {
    NULL, NULL,
    { "mod-pjsip-test", 14 },
    -1,
    PJSIP_MOD_PRIORITY_APPLICATION,
    NULL,
    NULL,
    NULL,
    NULL,
    &pjsip_test_on_rx_request,
    &pjsip_test_on_rx_response,
    &pjsip_test_on_tx_request,
    NULL,
    NULL
};

const char *pjsip_test_reg_state_name(enum pjsip_test_reg_state state)
{
    switch (state) {
    case PJSIP_TEST_REG_IDLE:
        return "IDLE";
    case PJSIP_TEST_REG_REGISTERING:
        return "REGISTERING";
    case PJSIP_TEST_REG_REGISTERED:
        return "REGISTERED";
    case PJSIP_TEST_REG_FAILED:
        return "FAILED";
    default:
        return "UNKNOWN";
    }
}

const char *pjsip_test_call_state_name(enum pjsip_test_call_state state)
{
    switch (state) {
    case PJSIP_TEST_CALL_IDLE:
        return "IDLE";
    case PJSIP_TEST_CALL_OUTGOING:
        return "OUTGOING";
    case PJSIP_TEST_CALL_INCOMING:
        return "INCOMING";
    case PJSIP_TEST_CALL_RINGING:
        return "RINGING";
    case PJSIP_TEST_CALL_CONNECTING:
        return "CONNECTING";
    case PJSIP_TEST_CALL_ESTABLISHED:
        return "ESTABLISHED";
    case PJSIP_TEST_CALL_DISCONNECTED:
        return "DISCONNECTED";
    default:
        return "UNKNOWN";
    }
}

enum pjsip_test_reg_state pjsip_test_get_reg_state(void)
{
    return g_pjsip_test_service.reg_state;
}

enum pjsip_test_call_state pjsip_test_get_call_state(void)
{
    return g_pjsip_test_service.call_state;
}

const char *pjsip_test_get_current_peer_uri(void)
{
    return g_pjsip_test_service.current_peer_uri;
}

static void service_set_reg_state(enum pjsip_test_reg_state state)
{
    if (g_pjsip_test_service.reg_state == state) {
        return;
    }

    g_pjsip_test_service.reg_state = state;
    log_info("reg_state=%s", pjsip_test_reg_state_name(state));
}

static void service_set_call_state(enum pjsip_test_call_state state)
{
    if (g_pjsip_test_service.call_state == state) {
        return;
    }

    g_pjsip_test_service.call_state = state;
    log_info("call_state=%s", pjsip_test_call_state_name(state));
}

static void service_set_peer_uri(const char *uri)
{
    if (!uri) {
        g_pjsip_test_service.current_peer_uri[0] = '\0';
        return;
    }

    pj_ansi_strncpy(g_pjsip_test_service.current_peer_uri,
                    uri,
                    sizeof(g_pjsip_test_service.current_peer_uri) - 1);
    g_pjsip_test_service
    .current_peer_uri[sizeof(g_pjsip_test_service.current_peer_uri) - 1] =
        '\0';
}

static void service_complete_command(pj_status_t status)
{
    g_pjsip_test_service.last_cmd_status = status;
    g_pjsip_test_service.cmd.pending = PJ_FALSE;
    g_pjsip_test_service.cmd.dispatched = PJ_FALSE;
    g_pjsip_test_service.cmd.type = PJSIP_TEST_CMD_NONE;
    g_pjsip_test_service.cmd.target_uri[0] = '\0';
    os_sem_post(&g_pjsip_test_service.done_sem);
}

static void service_release_keepalive(void)
{
    if (g_pjsip_test_service.ka_transport) {
        pjsip_transport_dec_ref(g_pjsip_test_service.ka_transport);
        g_pjsip_test_service.ka_transport = NULL;
    }

    pj_bzero(&g_pjsip_test_service.ka_target,
             sizeof(g_pjsip_test_service.ka_target));
    g_pjsip_test_service.ka_target_len = 0;
    g_pjsip_test_service.next_keepalive_tick_ms = 0;
}

static void service_release_call_media(void)
{
    if (live_media_transport) {
        pjmedia_transport_detach(live_media_transport, &live_audio_tx);
        pjmedia_transport_media_stop(live_media_transport);
        pjmedia_transport_close(live_media_transport);
        live_media_transport = NULL;
    }

    release_live_audio_tx();
}

static void service_reset_call_session(void)
{
    live_inv = NULL;
    service_release_call_media();
    live_sip_reset();
    g_pjsip_test_service.call_dir = PJSIP_TEST_CALL_DIR_NONE;
    g_pjsip_test_service.call_cleanup_pending = PJ_FALSE;
    g_pjsip_test_service.next_audio_tick_ms = 0;
    service_set_peer_uri(NULL);
    service_set_call_state(PJSIP_TEST_CALL_IDLE);
}

static void service_update_keepalive(struct pjsip_regc_cbparam *param)
{
    pjsip_transaction *tsx;
    pjsip_tx_data *req;

    service_release_keepalive();

    if (!param || !param->rdata || LIVE_SIP_KEEPALIVE_INTERVAL_SEC == 0 ||
        !LIVE_SIP_KEEPALIVE_DATA || LIVE_SIP_KEEPALIVE_DATA[0] == '\0') {
        return;
    }

    if ((param->rdata->tp_info.transport->key.type & ~PJSIP_TRANSPORT_IPV6) !=
        PJSIP_TRANSPORT_UDP) {
        return;
    }

    tsx = pjsip_rdata_get_tsx(param->rdata);
    if (!tsx || !tsx->last_tx) {
        return;
    }

    req = tsx->last_tx;
    g_pjsip_test_service.ka_transport = param->rdata->tp_info.transport;
    pjsip_transport_add_ref(g_pjsip_test_service.ka_transport);
    pj_memcpy(&g_pjsip_test_service.ka_target,
              &req->tp_info.dst_addr,
              req->tp_info.dst_addr_len);
    g_pjsip_test_service.ka_target_len = req->tp_info.dst_addr_len;
    g_pjsip_test_service.next_keepalive_tick_ms =
        timer_get_ms() + (LIVE_SIP_KEEPALIVE_INTERVAL_SEC * 1000UL);

    log_info("keepalive: enabled interval=%d s",
             LIVE_SIP_KEEPALIVE_INTERVAL_SEC);
}

static pj_status_t service_send_udp_keepalive(void)
{
    pjsip_tpselector tp_sel;
    pj_status_t status;
    unsigned long now_ms;

    if (!g_pjsip_test_service.ka_transport ||
        g_pjsip_test_service.ka_target_len == 0 ||
        LIVE_SIP_KEEPALIVE_INTERVAL_SEC == 0 ||
        !LIVE_SIP_KEEPALIVE_DATA || LIVE_SIP_KEEPALIVE_DATA[0] == '\0') {
        return PJ_EINVALIDOP;
    }

    now_ms = timer_get_ms();
    if (now_ms < g_pjsip_test_service.next_keepalive_tick_ms) {
        return PJ_SUCCESS;
    }

    pj_bzero(&tp_sel, sizeof(tp_sel));
    tp_sel.type = PJSIP_TPSELECTOR_TRANSPORT;
    tp_sel.u.transport = g_pjsip_test_service.ka_transport;

    status = pjsip_tpmgr_send_raw(pjsip_endpt_get_tpmgr(sip_endpt),
                                  g_pjsip_test_service.ka_transport->key.type,
                                  &tp_sel,
                                  NULL,
                                  LIVE_SIP_KEEPALIVE_DATA,
                                  pj_ansi_strlen(LIVE_SIP_KEEPALIVE_DATA),
                                  &g_pjsip_test_service.ka_target,
                                  g_pjsip_test_service.ka_target_len,
                                  NULL,
                                  NULL);
    if (status == PJ_SUCCESS || status == PJ_EPENDING) {
        g_pjsip_test_service.next_keepalive_tick_ms =
            now_ms + (LIVE_SIP_KEEPALIVE_INTERVAL_SEC * 1000UL);
        log_debug("keepalive: TX");
        return PJ_SUCCESS;
    }

    g_pjsip_test_service.next_keepalive_tick_ms =
        now_ms + (LIVE_SIP_KEEPALIVE_INTERVAL_SEC * 1000UL);
    log_pj_status("keepalive send", status);
    return status;
}

static void live_sip_reset(void)
{
    pj_bzero(&live_sip_test, sizeof(live_sip_test));
    pj_bzero(&live_audio_tx, sizeof(live_audio_tx));
    live_audio_tx.payload_type = -1;
}

static void live_reg_set_call_id(const pj_str_t *call_id)
{
    unsigned len;

    if (!call_id || call_id->slen <= 0) {
        live_reg_test.call_id[0] = '\0';
        return;
    }

    len = (unsigned)call_id->slen;
    if (len >= sizeof(live_reg_test.call_id)) {
        len = sizeof(live_reg_test.call_id) - 1;
    }

    pj_memcpy(live_reg_test.call_id, call_id->ptr, len);
    live_reg_test.call_id[len] = '\0';
}

static pj_bool_t live_reg_match_call_id(const pj_str_t *call_id)
{
    unsigned len;

    if (!live_reg_test.call_id[0] || !call_id || call_id->slen <= 0) {
        return PJ_FALSE;
    }

    len = (unsigned)pj_ansi_strlen(live_reg_test.call_id);
    return (len == (unsigned)call_id->slen &&
            pj_memcmp(live_reg_test.call_id, call_id->ptr, len) == 0);
}

static void live_sip_set_call_id(const pj_str_t *call_id)
{
    unsigned len;

    if (!call_id || call_id->slen <= 0) {
        live_sip_test.call_id[0] = '\0';
        return;
    }

    len = (unsigned)call_id->slen;
    if (len >= sizeof(live_sip_test.call_id)) {
        len = sizeof(live_sip_test.call_id) - 1;
    }

    pj_memcpy(live_sip_test.call_id, call_id->ptr, len);
    live_sip_test.call_id[len] = '\0';
}

static pj_bool_t live_sip_match_call_id(const pj_str_t *call_id)
{
    unsigned len;

    if (!live_sip_test.active || !call_id || call_id->slen <= 0) {
        return PJ_FALSE;
    }

    len = (unsigned)pj_ansi_strlen(live_sip_test.call_id);
    return (len == (unsigned)call_id->slen &&
            pj_memcmp(live_sip_test.call_id, call_id->ptr, len) == 0);
}

static pj_status_t build_proxy_route_set(pj_pool_t *tmp_pool,
        pjsip_route_hdr *route_set)
{
    pj_str_t hname;
    pj_str_t route_src;
    pj_str_t route_buf;
    pjsip_route_hdr *route;

    PJ_ASSERT_RETURN(tmp_pool && route_set, PJ_EINVAL);

    pj_list_init(route_set);
    pj_cstr(&hname, "Route");
    pj_cstr(&route_src, LIVE_SIP_PROXY_URI);
    pj_strdup_with_null(tmp_pool, &route_buf, &route_src);

    route = (pjsip_route_hdr *)pjsip_parse_hdr(tmp_pool, &hname,
            route_buf.ptr,
            route_buf.slen, NULL);
    if (!route) {
        return PJ_EINVAL;
    }

    pj_list_push_back(route_set, route);
    return PJ_SUCCESS;
}

static void init_live_auth_cred(pjsip_cred_info *cred)
{
    pj_bzero(cred, sizeof(*cred));
    pj_cstr(&cred->realm, LIVE_SIP_AUTH_REALM);
    pj_cstr(&cred->scheme, "digest");
    pj_cstr(&cred->username, LIVE_SIP_AUTH_USER);
    cred->data_type = PJSIP_CRED_DATA_PLAIN_PASSWD;
    pj_cstr(&cred->data, LIVE_SIP_AUTH_PASS);
}

static void live_reg_reset(void)
{
    pj_bzero(&live_reg_test, sizeof(live_reg_test));
}

static void live_reg_on_complete(struct pjsip_regc_cbparam *param)
{
    struct live_reg_test_state *state;
    char reason_buf[64];
    pj_status_t reg_result;

    if (!param) {
        return;
    }

    state = (struct live_reg_test_state *)param->token;
    if (!state) {
        return;
    }

    state->done = PJ_TRUE;
    state->status = param->status;
    state->final_code = param->code;
    state->expiration = param->expiration;
    format_reason_text(&param->reason, reason_buf, sizeof(reason_buf));

    log_info("live_reg: final code=%d reason=%s pj_status=%d expires=%u",
             param->code,
             reason_buf[0] ? reason_buf : "-",
             param->status,
             param->expiration);

    reg_result = get_live_register_result();
    if (reg_result == PJ_SUCCESS && param->expiration > 0 && !param->is_unreg) {
        service_set_reg_state(PJSIP_TEST_REG_REGISTERED);
        service_update_keepalive(param);
    } else {
        service_release_keepalive();
        service_set_reg_state((reg_result == PJ_SUCCESS) ?
                              PJSIP_TEST_REG_IDLE :
                              PJSIP_TEST_REG_FAILED);
    }

    if (g_pjsip_test_service.cmd.pending &&
        g_pjsip_test_service.cmd.type == PJSIP_TEST_CMD_REGISTER) {
        service_complete_command(reg_result);
    }
}

static void live_reg_on_tsx(struct pjsip_regc_tsx_cb_param *param)
{
    struct live_reg_test_state *state;
    char reason_buf[64];

    if (!param) {
        return;
    }

    state = (struct live_reg_test_state *)param->cbparam.token;
    if (state) {
        state->response_cnt++;
    }
    format_reason_text(&param->cbparam.reason, reason_buf, sizeof(reason_buf));

    log_debug("live_reg: RX %d %s",
              param->cbparam.code,
              reason_buf[0] ? reason_buf : "-");

    if (param->cbparam.rdata && param->cbparam.rdata->msg_info.msg) {
        dump_sip_msg("live_reg: RX_RAW",
                     param->cbparam.rdata->tp_info.pool,
                     param->cbparam.rdata->msg_info.msg);
    }
}

static pj_status_t get_live_register_result(void)
{
    if (!live_reg_test.done) {
        return PJ_EPENDING;
    }

    if (live_reg_test.final_code / 100 == 2) {
        return PJ_SUCCESS;
    }

    if (live_reg_test.status != PJ_SUCCESS) {
        return live_reg_test.status;
    }

    if (live_reg_test.final_code > 0) {
        return PJSIP_ERRNO_FROM_SIP_STATUS(live_reg_test.final_code);
    }

    return PJ_EUNKNOWN;
}

static pj_status_t wait_for_live_register_final(void)
{
    int waited_ms = 0;

    while (waited_ms < LIVE_SIP_RESPONSE_TIMEOUT_MS) {
        pj_time_val timeout = {0, 0};
        pj_status_t status;

        if (live_reg_test.done) {
            log_debug("live_reg: observed final code=%d responses=%u expires=%u",
                      live_reg_test.final_code,
                      live_reg_test.response_cnt,
                      live_reg_test.expiration);
            return get_live_register_result();
        }

        status = pjsip_endpt_handle_events(sip_endpt, &timeout);
        if (status != PJ_SUCCESS) {
            log_pj_status("live_reg handle_events", status);
            return status;
        }

        if (live_reg_test.done) {
            log_debug("live_reg: observed final code=%d responses=%u expires=%u",
                      live_reg_test.final_code,
                      live_reg_test.response_cnt,
                      live_reg_test.expiration);
            return get_live_register_result();
        }

        pj_thread_sleep(LIVE_SIP_POLL_INTERVAL_MS);
        waited_ms += LIVE_SIP_POLL_INTERVAL_MS;
    }

    log_error("live_reg: no final response within %d ms",
              LIVE_SIP_RESPONSE_TIMEOUT_MS);
    return PJ_ETIMEDOUT;
}

static pj_bool_t pjsip_test_on_rx_response(pjsip_rx_data *rdata)
{
    pjsip_msg *msg;
    int status_code;

    if (!rdata || !rdata->msg_info.cid ||
        !live_sip_match_call_id(&rdata->msg_info.cid->id)) {
        return PJ_FALSE;
    }

    msg = rdata->msg_info.msg;
    status_code = msg->line.status.code;
    live_sip_test.got_response = PJ_TRUE;
    live_sip_test.response_cnt++;

    log_debug("live_sip: RX %d %.*s from %s:%d",
              status_code,
              (int)msg->line.status.reason.slen,
              msg->line.status.reason.ptr,
              rdata->pkt_info.src_name,
              rdata->pkt_info.src_port);

    if (status_code / 100 == 1 &&
        g_pjsip_test_service.call_dir == PJSIP_TEST_CALL_DIR_OUTGOING) {
        service_set_call_state(PJSIP_TEST_CALL_RINGING);
    }

    if (status_code >= 200 &&
        status_code != PJSIP_SC_UNAUTHORIZED &&
        status_code != PJSIP_SC_PROXY_AUTHENTICATION_REQUIRED) {
        live_sip_test.got_final = PJ_TRUE;
        live_sip_test.final_status = status_code;
    }

    return PJ_FALSE;
}

static void live_inv_on_state_changed(pjsip_inv_session *inv, pjsip_event *e)
{
    char reason_buf[64];

    PJ_UNUSED_ARG(e);

    if (!inv || !inv->dlg || !inv->dlg->call_id ||
        !live_sip_match_call_id(&inv->dlg->call_id->id)) {
        return;
    }

    format_reason_text(&inv->cause_text, reason_buf, sizeof(reason_buf));
    log_info("live_sip: inv_state=%s cause=%d %s",
             pjsip_inv_state_name(inv->state),
             inv->cause,
             reason_buf[0] ? reason_buf : "-");

    if (inv->state == PJSIP_INV_STATE_INCOMING) {
        service_set_call_state(PJSIP_TEST_CALL_INCOMING);
    } else if (inv->state == PJSIP_INV_STATE_EARLY) {
        service_set_call_state(PJSIP_TEST_CALL_RINGING);
    } else if (inv->state == PJSIP_INV_STATE_CONNECTING) {
        service_set_call_state(PJSIP_TEST_CALL_CONNECTING);
    } else if (inv->state == PJSIP_INV_STATE_CONFIRMED) {
        live_sip_test.call_established = PJ_TRUE;
        live_sip_test.got_final = PJ_TRUE;
        live_sip_test.final_status = 200;
        service_set_call_state(PJSIP_TEST_CALL_ESTABLISHED);
        g_pjsip_test_service.next_audio_tick_ms = timer_get_ms();
    } else if (inv->state == PJSIP_INV_STATE_DISCONNECTED) {
        live_sip_test.call_disconnected = PJ_TRUE;
        live_sip_test.disconnect_code = inv->cause;
        g_pjsip_test_service.call_cleanup_pending = PJ_TRUE;
        service_set_call_state(PJSIP_TEST_CALL_DISCONNECTED);
        if (live_inv == inv) {
            live_inv = NULL;
        }
    }
}

static void live_inv_on_media_update(pjsip_inv_session *inv_ses,
                                     pj_status_t status)
{
    if (!inv_ses || !inv_ses->dlg || !inv_ses->dlg->call_id ||
        !live_sip_match_call_id(&inv_ses->dlg->call_id->id)) {
        return;
    }

    if (status == PJ_SUCCESS) {
        log_info("live_sip: media_update OK");
        live_audio_tx.media_negotiated = PJ_TRUE;
    } else {
        log_pj_status("live_sip media_update", status);
    }
}

static void live_inv_on_tsx_state_changed(pjsip_inv_session *inv,
        pjsip_transaction *tsx,
        pjsip_event *e)
{
    if (!inv || !tsx || !e || !inv->dlg || !inv->dlg->call_id ||
        !live_sip_match_call_id(&inv->dlg->call_id->id)) {
        return;
    }

    if (tsx->role == PJSIP_ROLE_UAC &&
        (tsx->status_code == PJSIP_SC_UNAUTHORIZED ||
         tsx->status_code == PJSIP_SC_PROXY_AUTHENTICATION_REQUIRED) &&
        tsx->last_tx && tsx->last_tx->auth_retry) {
        return;
    }

    if (e->body.tsx_state.type == PJSIP_EVENT_RX_MSG &&
        e->body.tsx_state.src.rdata &&
        e->body.tsx_state.src.rdata->msg_info.msg &&
        e->body.tsx_state.src.rdata->msg_info.msg->type == PJSIP_RESPONSE_MSG) {
        int code = e->body.tsx_state.src.rdata->msg_info.msg->line.status.code;

        live_sip_test.got_response = PJ_TRUE;
        if (code >= 200 &&
            code != PJSIP_SC_UNAUTHORIZED &&
            code != PJSIP_SC_PROXY_AUTHENTICATION_REQUIRED) {
            live_sip_test.got_final = PJ_TRUE;
            live_sip_test.final_status = code;
        }

        if (code / 100 == 1 &&
            g_pjsip_test_service.call_dir == PJSIP_TEST_CALL_DIR_OUTGOING) {
            service_set_call_state(PJSIP_TEST_CALL_RINGING);
        }

        if (code >= 300) {
            dump_sip_msg("live_sip: RX_RAW",
                         e->body.tsx_state.src.rdata->tp_info.pool,
                         e->body.tsx_state.src.rdata->msg_info.msg);
        }
        // if (param->cbparam.rdata && param->cbparam.rdata->msg_info.msg) {  //RX print
        // dump_sip_msg("live_reg: RX_RAW",
        //              param->cbparam.rdata->tp_info.pool,
        //              param->cbparam.rdata->msg_info.msg);
        //}
    }
}

static pj_status_t pjsip_test_on_tx_request(pjsip_tx_data *tdata)
{
    pjsip_cid_hdr *cid;
    pjsip_method *method;
    pj_bool_t reg_match;
    pj_bool_t sip_match;

    if (!tdata || !tdata->msg) {
        return PJ_SUCCESS;
    }

    cid = (pjsip_cid_hdr *)pjsip_msg_find_hdr(tdata->msg, PJSIP_H_CALL_ID, NULL);
    if (!cid) {
        return PJ_SUCCESS;
    }

    reg_match = live_reg_match_call_id(&cid->id);
    sip_match = live_sip_match_call_id(&cid->id);
    if (!reg_match && !sip_match) {
        return PJ_SUCCESS;
    }

    method = &tdata->msg->line.req.method;
    if (reg_match && pjsip_method_cmp(method, &pjsip_register_method) == 0) {
        log_debug("live_reg: TX %s", pjsip_tx_data_get_info(tdata));
        dump_sip_msg("live_reg: TX_RAW", tdata->pool, tdata->msg);
    }

    if (sip_match) {
        log_debug("live_sip: TX %s", pjsip_tx_data_get_info(tdata));
    }

    if (sip_match &&
        (pjsip_method_cmp(method, &pjsip_invite_method) == 0 ||
         pjsip_method_cmp(method, &pjsip_ack_method) == 0)) {
        dump_sip_msg("live_sip: TX_RAW", tdata->pool, tdata->msg);
    }

    return PJ_SUCCESS;
}

/**
 * Initialize PJSIP endpoint
 */
static pj_status_t init_pjsip(void)
{
    pj_status_t status;
    pjsip_ua_init_param ua_param;
    pjsip_inv_callback inv_cb;

    /* Create PJSIP endpoint */
    status = pjsip_endpt_create(&cp.factory, "pjsip_test", &sip_endpt);
    if (status != PJ_SUCCESS) {
        log_pj_status("pjsip_endpt_create", status);
        return status;
    }

    status = pjsip_tsx_layer_init_module(sip_endpt);
    if (status != PJ_SUCCESS) {
        log_pj_status("pjsip_tsx_layer_init_module", status);
        return status;
    }

    pj_bzero(&ua_param, sizeof(ua_param));
    status = pjsip_ua_init_module(sip_endpt, &ua_param);
    if (status != PJ_SUCCESS) {
        log_pj_status("pjsip_ua_init_module", status);
        return status;
    }

    status = pjsip_100rel_init_module(sip_endpt);
    if (status != PJ_SUCCESS) {
        log_pj_status("pjsip_100rel_init_module", status);
        return status;
    }

    if (pjsip_inv_usage_instance()->id == -1) {
        pj_bzero(&inv_cb, sizeof(inv_cb));
        inv_cb.on_state_changed = &live_inv_on_state_changed;
        inv_cb.on_media_update = &live_inv_on_media_update;
        inv_cb.on_tsx_state_changed = &live_inv_on_tsx_state_changed;

        status = pjsip_inv_usage_init(sip_endpt, &inv_cb);
        if (status != PJ_SUCCESS) {
            log_pj_status("pjsip_inv_usage_init", status);
            return status;
        }
    }

    status = pjsip_endpt_register_module(sip_endpt, &pjsip_test_module);
    if (status != PJ_SUCCESS) {
        log_pj_status("pjsip_endpt_register_module(pjsip_test_module)", status);
        return status;
    }

    return PJ_SUCCESS;
}

/**
 * Create UDP transport
 */
static pj_status_t create_transport(void)
{
    pj_status_t status;
    pj_sockaddr_in addr;
    pjsip_host_port published_name;
    pjsip_transport *transport;
    int retry;
    char local_ip[32];
    pj_str_t local_ip_str;

    /* Initialize address */
    pj_sockaddr_in_init(&addr, NULL, (pj_uint16_t)SIP_PORT);
    published_name.host.ptr = NULL;
    published_name.host.slen = 0;
    published_name.port = SIP_PORT;

    status = get_local_ip_string(local_ip, sizeof(local_ip));
    if (status == PJ_SUCCESS) {
        local_ip_str = pj_str(local_ip);
        published_name.host = local_ip_str;
        log_debug("create_transport: local_ip=%s", local_ip);
    } else {
        log_info("[WARN] create_transport: local ip unavailable, use default published address");
    }

    /* Create UDP transport */
    for (retry = 0; retry < UDP_START_RETRY_MAX; retry++) {
        status = pjsip_udp_transport_start(sip_endpt, &addr,
                                           (published_name.host.slen > 0) ? &published_name : NULL,
                                           1, &transport);
        if (status == PJ_SUCCESS) {
            break;
        }

        log_info("[WARN] udp start retry %d/%d, status=%d, os=%d",
                 retry + 1, UDP_START_RETRY_MAX, status,
                 (status >= PJ_ERRNO_START_SYS && status < PJ_ERRNO_START_USER) ?
                 PJ_STATUS_TO_OS(status) : -1);
        os_time_dly(UDP_START_RETRY_DLY_TICK);
    }

    if (status != PJ_SUCCESS) {
        log_pj_status("pjsip_udp_transport_start", status);
        return status;
    }

    udp_transport = transport;
    return PJ_SUCCESS;
}

static pj_status_t test_pjsip_event_poll(void)
{
    pj_time_val timeout = {0, 10};
    int event_cnt;

    event_cnt = pjsip_endpt_handle_events(sip_endpt, &timeout);
    if (event_cnt < 0) {
        log_error("pjsip_endpt_handle_events returned %d", event_cnt);
        return PJ_EUNKNOWN;
    }

    log_debug("event_poll: events=%d", event_cnt);
    return PJ_SUCCESS;
}

/**
 * Test basic PJSIP functionality
 */
static pj_status_t test_basic_sip(void)
{
    pj_status_t status;
    pjsip_tx_data *tdata;
    pj_str_t target;
    pj_str_t from;
    pj_str_t to;

    /* Create a simple OPTIONS request */
    pj_cstr(&target, LIVE_SIP_TARGET_URI);
    pj_cstr(&from, LIVE_SIP_ACCOUNT_URI);
    pj_cstr(&to, LIVE_SIP_TARGET_URI);

    status = pjsip_endpt_create_request(sip_endpt, &pjsip_options_method,
                                        &target, &from, &to, NULL, NULL, -1,
                                        NULL, &tdata);
    if (status != PJ_SUCCESS) {
        log_pj_status("pjsip_endpt_create_request", status);
        return status;
    }

    log_debug("basic_sip: request method=%.*s",
              (int)tdata->msg->line.req.method.name.slen,
              tdata->msg->line.req.method.name.ptr);

    /* Clean up */
    pjsip_tx_data_dec_ref(tdata);

    return PJ_SUCCESS;
}

static void build_local_contact_uri(const char *local_ip,
                                    char *buf,
                                    unsigned buf_size)
{
    PJ_ASSERT_ON_FAIL(local_ip && buf && buf_size > 0, return);

    pj_ansi_snprintf(buf, buf_size,
                     "<sip:%s@%s:%d;transport=udp>",
                     LIVE_SIP_AUTH_USER, local_ip, SIP_PORT);
}

static void capture_peer_uri_from_hdr(const pjsip_fromto_hdr *hdr)
{
    char uri_buf[PJSIP_MAX_URL_SIZE];
    int len;

    if (!hdr || !hdr->uri) {
        service_set_peer_uri(NULL);
        return;
    }

    len = pjsip_uri_print(PJSIP_URI_IN_FROMTO_HDR,
                          hdr->uri,
                          uri_buf,
                          sizeof(uri_buf));
    if (len < 0) {
        service_set_peer_uri(NULL);
        return;
    }

    uri_buf[len] = '\0';
    service_set_peer_uri(uri_buf);
}

static pj_bool_t service_call_is_busy(void)
{
    return (g_pjsip_test_service.call_state != PJSIP_TEST_CALL_IDLE &&
            g_pjsip_test_service.call_state != PJSIP_TEST_CALL_DISCONNECTED);
}

static pj_status_t service_handle_register_command(void)
{
    pj_status_t status;
    char local_ip[32];
    char contact_uri[128];
    pj_str_t registrar_uri;
    pj_str_t aor;
    pj_str_t contact;
    pjsip_tpselector tp_sel;
    pjsip_route_hdr route_set;
    pjsip_cred_info cred;
    pjsip_tx_data *tdata = NULL;
    pjsip_cid_hdr *cid = NULL;

    live_reg_reset();
    seed_pj_random("live_register");

    status = get_local_ip_string(local_ip, sizeof(local_ip));
    if (status != PJ_SUCCESS) {
        log_pj_status("get_local_ip_string", status);
        return status;
    }

    log_debug("live_reg: local_ip=%s", local_ip);
    log_routed_target_probe("live_reg: registrar",
                            LIVE_SIP_REGISTRAR_URI,
                            LIVE_SIP_REGISTRAR_HOST);
    log_host_resolution("live_reg: proxy", LIVE_SIP_PROXY_HOST);

    build_local_contact_uri(local_ip, contact_uri, sizeof(contact_uri));
    pj_cstr(&registrar_uri, LIVE_SIP_REGISTRAR_URI);
    pj_cstr(&aor, LIVE_SIP_ACCOUNT_URI);
    pj_cstr(&contact, contact_uri);

    if (!live_regc) {
        status = pjsip_regc_create(sip_endpt,
                                   &live_reg_test,
                                   &live_reg_on_complete,
                                   &live_regc);
        if (status != PJ_SUCCESS) {
            log_pj_status("pjsip_regc_create", status);
            return status;
        }

        status = pjsip_regc_set_reg_tsx_cb(live_regc, &live_reg_on_tsx);
        if (status != PJ_SUCCESS) {
            log_pj_status("pjsip_regc_set_reg_tsx_cb", status);
            return status;
        }

        status = pjsip_regc_init(live_regc, &registrar_uri, &aor, &aor, 1,
                                 &contact, LIVE_SIP_REGISTER_EXPIRES);
        if (status != PJ_SUCCESS) {
            log_pj_status("pjsip_regc_init", status);
            return status;
        }

        status = pjsip_regc_set_delay_before_refresh(
                     live_regc, LIVE_SIP_REGISTER_REFRESH_MARGIN);
        if (status != PJ_SUCCESS) {
            log_pj_status("pjsip_regc_set_delay_before_refresh", status);
            return status;
        }

        status = init_udp_transport_selector(&tp_sel);
        if (status != PJ_SUCCESS) {
            log_pj_status("init_udp_transport_selector", status);
            return status;
        }

        status = pjsip_regc_set_transport(live_regc, &tp_sel);
        if (status != PJ_SUCCESS) {
            log_pj_status("pjsip_regc_set_transport", status);
            return status;
        }

        status = build_proxy_route_set(pool, &route_set);
        if (status != PJ_SUCCESS) {
            log_pj_status("build_proxy_route_set", status);
            return status;
        }

        status = pjsip_regc_set_route_set(live_regc, &route_set);
        if (status != PJ_SUCCESS) {
            log_pj_status("pjsip_regc_set_route_set", status);
            return status;
        }

        init_live_auth_cred(&cred);
        status = pjsip_regc_set_credentials(live_regc, 1, &cred);
        if (status != PJ_SUCCESS) {
            log_pj_status("pjsip_regc_set_credentials", status);
            return status;
        }
    }

    service_release_keepalive();
    service_set_reg_state(PJSIP_TEST_REG_REGISTERING);

    status = pjsip_regc_register(live_regc, PJ_TRUE, &tdata);
    if (status != PJ_SUCCESS) {
        log_pj_status("pjsip_regc_register", status);
        return status;
    }

    log_info("live_reg: REGISTER %s via %s",
             LIVE_SIP_ACCOUNT_URI, LIVE_SIP_PROXY_URI);

    cid = (pjsip_cid_hdr *)pjsip_msg_find_hdr(tdata->msg, PJSIP_H_CALL_ID, NULL);
    if (cid) {
        live_reg_set_call_id(&cid->id);
        log_debug("live_reg: Call-ID=%s", live_reg_test.call_id);
    } else {
        live_reg_set_call_id(NULL);
    }

    status = pjsip_regc_send(live_regc, tdata);
    if (status != PJ_SUCCESS) {
        log_pj_status("pjsip_regc_send", status);
        service_set_reg_state(PJSIP_TEST_REG_FAILED);
        return status;
    }

    return PJ_EPENDING;
}

static pj_status_t service_handle_make_call(const char *target_uri)
{
    pj_status_t status;
    char local_ip[32];
    char contact_uri[128];
    pj_str_t local_aor;
    pj_str_t target;
    pj_str_t contact;
    pjsip_dialog *dlg = NULL;
    pjsip_inv_session *inv = NULL;
    pjsip_tx_data *tdata = NULL;
    pjsip_cid_hdr *cid;
    pjsip_tpselector tp_sel;
    pjsip_cred_info cred;
    pjsip_route_hdr route_set;
    pjmedia_transport *media_tp = NULL;
    pjmedia_sdp_session *local_sdp = NULL;
    pj_bool_t dlg_locked = PJ_FALSE;

    PJ_ASSERT_RETURN(target_uri && *target_uri, PJ_EINVAL);

    if (g_pjsip_test_service.reg_state != PJSIP_TEST_REG_REGISTERED) {
        return PJ_EINVALIDOP;
    }
    if (service_call_is_busy()) {
        return PJ_EBUSY;
    }

    seed_pj_random("live_invite");

    status = get_local_ip_string(local_ip, sizeof(local_ip));
    if (status != PJ_SUCCESS) {
        log_pj_status("get_local_ip_string", status);
        return status;
    }

    log_debug("live_sip: local_ip=%s", local_ip);
    log_host_resolution("live_invite: proxy", LIVE_SIP_PROXY_HOST);
    if (LIVE_SIP_PROXY_URI[0] != '\0') {
        log_debug("live_invite: target: %s via proxy, skip host pre-resolve",
                  target_uri);
    }

    service_reset_call_session();
    g_pjsip_test_service.call_dir = PJSIP_TEST_CALL_DIR_OUTGOING;
    service_set_peer_uri(target_uri);

    build_local_contact_uri(local_ip, contact_uri, sizeof(contact_uri));
    pj_cstr(&local_aor, LIVE_SIP_ACCOUNT_URI);
    pj_cstr(&target, target_uri);
    pj_cstr(&contact, contact_uri);

    status = pjsip_dlg_create_uac(pjsip_ua_instance(), &local_aor, &contact,
                                  &target, NULL, &dlg);
    if (status != PJ_SUCCESS) {
        log_pj_status("pjsip_dlg_create_uac(INVITE)", status);
        goto on_return;
    }

    pjsip_dlg_inc_lock(dlg);
    dlg_locked = PJ_TRUE;

    status = init_udp_transport_selector(&tp_sel);
    if (status != PJ_SUCCESS) {
        log_pj_status("init_udp_transport_selector", status);
        goto on_return;
    }

    status = pjsip_dlg_set_transport(dlg, &tp_sel);
    if (status != PJ_SUCCESS) {
        log_pj_status("pjsip_dlg_set_transport", status);
        goto on_return;
    }

    status = build_proxy_route_set(pool, &route_set);
    if (status != PJ_SUCCESS) {
        log_pj_status("build_proxy_route_set", status);
        goto on_return;
    }

    status = pjsip_dlg_set_route_set(dlg, &route_set);
    if (status != PJ_SUCCESS) {
        log_pj_status("pjsip_dlg_set_route_set", status);
        goto on_return;
    }

    init_live_auth_cred(&cred);
    status = pjsip_auth_clt_set_credentials(&dlg->auth_sess, 1, &cred);
    if (status != PJ_SUCCESS) {
        log_pj_status("pjsip_auth_clt_set_credentials", status);
        goto on_return;
    }

    status = create_live_media_transport(local_ip, &media_tp);
    if (status != PJ_SUCCESS) {
        log_pj_status("create_live_media_transport", status);
        goto on_return;
    }

    status = create_live_offer_sdp(dlg->pool, media_tp, &local_sdp);
    if (status != PJ_SUCCESS) {
        goto on_return;
    }

    status = pjsip_inv_create_uac(dlg, local_sdp, 0, &inv);
    if (status != PJ_SUCCESS) {
        log_pj_status("pjsip_inv_create_uac", status);
        goto on_return;
    }

    status = pjsip_inv_invite(inv, &tdata);
    if (status != PJ_SUCCESS) {
        log_pj_status("pjsip_inv_invite", status);
        goto on_return;
    }

    cid = (pjsip_cid_hdr *)pjsip_msg_find_hdr(tdata->msg, PJSIP_H_CALL_ID, NULL);
    if (!cid) {
        status = PJ_EBUG;
        log_pj_status("find Call-ID header", status);
        goto on_return;
    }

    live_sip_reset();
    live_sip_test.active = PJ_TRUE;
    live_sip_set_call_id(&cid->id);
    live_inv = inv;
    live_media_transport = media_tp;
    media_tp = NULL;

    log_info("live_sip: INVITE(with SDP) %s via %s",
             target_uri, LIVE_SIP_PROXY_URI);
    log_debug("live_sip: Call-ID=%s", live_sip_test.call_id);

    status = pjsip_inv_send_msg(inv, tdata);
    tdata = NULL;
    if (status != PJ_SUCCESS) {
        log_pj_status("pjsip_inv_send_msg(INVITE)", status);
        goto on_return;
    }

    service_set_call_state(PJSIP_TEST_CALL_OUTGOING);

on_return:
    if (dlg_locked && dlg) {
        pjsip_dlg_dec_lock(dlg);
    }
    if (tdata) {
        pjsip_tx_data_dec_ref(tdata);
    }
    if (status != PJ_SUCCESS) {
        if (media_tp) {
            pjmedia_transport_close(media_tp);
        }
        service_reset_call_session();
    }
    return status;
}

static pj_status_t service_handle_answer_call(void)
{
    pj_status_t status;
    pjsip_tx_data *tdata = NULL;

    if (!live_inv) {
        return PJ_EINVALIDOP;
    }

    if (g_pjsip_test_service.call_dir != PJSIP_TEST_CALL_DIR_INCOMING ||
        (g_pjsip_test_service.call_state != PJSIP_TEST_CALL_INCOMING &&
         g_pjsip_test_service.call_state != PJSIP_TEST_CALL_RINGING)) {
        return PJ_EINVALIDOP;
    }

    status = pjsip_inv_answer(live_inv, 200, NULL, NULL, &tdata);
    if (status != PJ_SUCCESS) {
        log_pj_status("pjsip_inv_answer(200)", status);
        return status;
    }

    status = pjsip_inv_send_msg(live_inv, tdata);
    if (status != PJ_SUCCESS) {
        log_pj_status("pjsip_inv_send_msg(200)", status);
        return status;
    }

    log_info("incoming call answered");
    service_set_call_state(PJSIP_TEST_CALL_CONNECTING);
    return PJ_SUCCESS;
}

static pj_status_t service_handle_hangup_call(void)
{
    pj_status_t status;
    pjsip_tx_data *tdata = NULL;
    pj_str_t reason;

    if (!live_inv) {
        return PJ_EINVALIDOP;
    }

    if (g_pjsip_test_service.call_state == PJSIP_TEST_CALL_INCOMING ||
        g_pjsip_test_service.call_state == PJSIP_TEST_CALL_RINGING) {
        pj_cstr(&reason, "Busy Here");
        status = pjsip_inv_end_session(live_inv,
                                       PJSIP_SC_BUSY_HERE,
                                       &reason,
                                       &tdata);
    } else {
        status = pjsip_inv_end_session(live_inv,
                                       PJSIP_SC_OK,
                                       NULL,
                                       &tdata);
    }

    if (status != PJ_SUCCESS) {
        log_pj_status("pjsip_inv_end_session", status);
        return status;
    }

    if (tdata) {
        status = pjsip_inv_send_msg(live_inv, tdata);
        if (status != PJ_SUCCESS) {
            log_pj_status("pjsip_inv_send_msg(end_session)", status);
            return status;
        }
    }

    return PJ_SUCCESS;
}

static pj_status_t service_handle_incoming_invite(pjsip_rx_data *rdata)
{
    pj_status_t status;
    char local_ip[32];
    char contact_uri[128];
    pj_str_t contact;
    pjsip_dialog *dlg = NULL;
    pjsip_inv_session *inv = NULL;
    pjsip_tx_data *tdata = NULL;
    unsigned options = 0;
    pjmedia_transport *media_tp = NULL;
    pjmedia_sdp_session *local_sdp = NULL;

    if (!rdata || !rdata->msg_info.msg ||
        rdata->msg_info.msg->type != PJSIP_REQUEST_MSG ||
        rdata->msg_info.msg->line.req.method.id != PJSIP_INVITE_METHOD) {
        return PJ_EINVAL;
    }

    if (service_call_is_busy()) {
        pjsip_endpt_respond_stateless(sip_endpt, rdata, PJSIP_SC_BUSY_HERE,
                                      NULL, NULL, NULL);
        return PJ_EBUSY;
    }

    status = get_local_ip_string(local_ip, sizeof(local_ip));
    if (status != PJ_SUCCESS) {
        pjsip_endpt_respond_stateless(sip_endpt, rdata,
                                      PJSIP_SC_INTERNAL_SERVER_ERROR,
                                      NULL, NULL, NULL);
        return status;
    }

    build_local_contact_uri(local_ip, contact_uri, sizeof(contact_uri));
    pj_cstr(&contact, contact_uri);

    status = create_live_media_transport(local_ip, &media_tp);
    if (status != PJ_SUCCESS) {
        pjsip_endpt_respond_stateless(sip_endpt, rdata,
                                      PJSIP_SC_INTERNAL_SERVER_ERROR,
                                      NULL, NULL, NULL);
        return status;
    }

    status = create_live_offer_sdp(pool, media_tp, &local_sdp);
    if (status != PJ_SUCCESS) {
        pjmedia_transport_close(media_tp);
        pjsip_endpt_respond_stateless(sip_endpt, rdata,
                                      PJSIP_SC_NOT_ACCEPTABLE_HERE,
                                      NULL, NULL, NULL);
        return status;
    }

    status = pjsip_inv_verify_request(rdata, &options, local_sdp, NULL,
                                      sip_endpt, NULL);
    if (status != PJ_SUCCESS) {
        pjmedia_transport_close(media_tp);
        pjsip_endpt_respond_stateless(sip_endpt, rdata,
                                      PJSIP_SC_NOT_ACCEPTABLE_HERE,
                                      NULL, NULL, NULL);
        return status;
    }

    status = pjsip_dlg_create_uas_and_inc_lock(pjsip_ua_instance(),
             rdata,
             &contact,
             &dlg);
    if (status != PJ_SUCCESS) {
        pjmedia_transport_close(media_tp);
        pjsip_endpt_respond_stateless(sip_endpt, rdata,
                                      PJSIP_SC_INTERNAL_SERVER_ERROR,
                                      NULL, NULL, NULL);
        return status;
    }

    status = pjsip_inv_create_uas(dlg, rdata, local_sdp, options, &inv);
    if (status != PJ_SUCCESS) {
        pjsip_dlg_dec_lock(dlg);
        pjmedia_transport_close(media_tp);
        pjsip_endpt_respond_stateless(sip_endpt, rdata,
                                      PJSIP_SC_INTERNAL_SERVER_ERROR,
                                      NULL, NULL, NULL);
        return status;
    }
    pjsip_dlg_dec_lock(dlg);

    service_reset_call_session();
    g_pjsip_test_service.call_dir = PJSIP_TEST_CALL_DIR_INCOMING;
    live_sip_test.active = PJ_TRUE;
    live_inv = inv;
    live_media_transport = media_tp;
    capture_peer_uri_from_hdr(rdata->msg_info.from);
    if (inv->dlg && inv->dlg->call_id) {
        live_sip_set_call_id(&inv->dlg->call_id->id);
    }

    log_info("incoming call: from=%s",
             g_pjsip_test_service.current_peer_uri[0] ?
             g_pjsip_test_service.current_peer_uri : "<unknown>");
    service_set_call_state(PJSIP_TEST_CALL_INCOMING);

    status = pjsip_inv_initial_answer(inv, rdata, 180, NULL, NULL, &tdata);
    if (status != PJ_SUCCESS) {
        log_pj_status("pjsip_inv_initial_answer(180)", status);
        service_reset_call_session();
        return status;
    }

    status = pjsip_inv_send_msg(inv, tdata);
    if (status != PJ_SUCCESS) {
        log_pj_status("pjsip_inv_send_msg(180)", status);
        service_reset_call_session();
        return status;
    }

    log_info("incoming call ringing, waiting answer API");
    service_set_call_state(PJSIP_TEST_CALL_RINGING);
    //pjsip_test_answer_call(); //接听
    return PJ_SUCCESS;
}

static void service_process_pending_command(void)
{
    pj_status_t status;

    if (!g_pjsip_test_service.cmd.pending ||
        g_pjsip_test_service.cmd.dispatched) {
        return;
    }

    g_pjsip_test_service.cmd.dispatched = PJ_TRUE;

    switch (g_pjsip_test_service.cmd.type) {
    case PJSIP_TEST_CMD_REGISTER:
        status = service_handle_register_command();
        if (status != PJ_EPENDING) {
            service_complete_command(status);
        }
        break;
    case PJSIP_TEST_CMD_MAKE_CALL:
        status = service_handle_make_call(g_pjsip_test_service.cmd.target_uri);
        service_complete_command(status);
        break;
    case PJSIP_TEST_CMD_ANSWER_CALL:
        status = service_handle_answer_call();
        service_complete_command(status);
        break;
    case PJSIP_TEST_CMD_HANGUP_CALL:
        status = service_handle_hangup_call();
        service_complete_command(status);
        break;
    default:
        service_complete_command(PJ_EINVAL);
        break;
    }
}

static pj_bool_t pjsip_test_on_rx_request(pjsip_rx_data *rdata)
{
    pjsip_method *method;

    if (!rdata || !rdata->msg_info.msg ||
        rdata->msg_info.msg->type != PJSIP_REQUEST_MSG) {
        return PJ_FALSE;
    }

    method = &rdata->msg_info.msg->line.req.method;

    if (pjsip_method_cmp(method, &pjsip_options_method) == 0) {
        pjsip_endpt_respond_stateless(sip_endpt, rdata, 200, NULL, NULL, NULL);
        return PJ_TRUE;
    }

    if (pjsip_method_cmp(method, &pjsip_invite_method) != 0) {
        return PJ_FALSE;
    }

    if (rdata->msg_info.to && rdata->msg_info.to->tag.slen > 0) {
        return PJ_FALSE;
    }

    service_handle_incoming_invite(rdata);
    return PJ_TRUE;
}

static pj_status_t test_live_invite(void)
{
    pj_status_t status;
    char local_ip[32];
    char contact_uri[128];
    pj_str_t local_aor;
    pj_str_t target;
    pj_str_t contact;
    pjsip_dialog *dlg = NULL;
    pjsip_inv_session *inv = NULL;
    pjsip_tx_data *tdata = NULL;
    pjsip_tx_data *bye_tdata = NULL;
    pjsip_cid_hdr *cid;
    pjsip_tpselector tp_sel;
    pjsip_cred_info cred;
    pjsip_route_hdr route_set;
    pjmedia_transport *media_tp = NULL;
    pjmedia_sdp_session *local_sdp = NULL;
    int waited_ms = 0;
    int established_ms = 0;
    pj_bool_t dlg_locked = PJ_FALSE;
    pj_bool_t bye_sent = PJ_FALSE;

    status = get_live_register_result();
    if (status == PJ_EPENDING) {
        log_error("live_invite requires REGISTER final response first");
        return PJ_EINVALIDOP;
    }
    if (status != PJ_SUCCESS) {
        log_error("live_invite skipped because REGISTER failed, final_code=%d pj_status=%d",
                  live_reg_test.final_code, status);
        return status;
    }
    log_info("live_reg: INVITE proceeds after successful REGISTER final code=%d",
             live_reg_test.final_code);

    seed_pj_random("live_invite");

    status = get_local_ip_string(local_ip, sizeof(local_ip));
    if (status != PJ_SUCCESS) {
        log_pj_status("get_local_ip_string", status);
        return status;
    }

    log_debug("live_sip: local_ip=%s", local_ip);
    log_host_resolution("live_invite: proxy", LIVE_SIP_PROXY_HOST);
    log_routed_target_probe("live_invite: target",
                            LIVE_SIP_TARGET_URI,
                            LIVE_SIP_TARGET_HOST);

    pj_ansi_snprintf(contact_uri, sizeof(contact_uri),
                     "<sip:%s@%s:%d;transport=udp>",
                     LIVE_SIP_AUTH_USER, local_ip, SIP_PORT);

    pj_cstr(&local_aor, LIVE_SIP_ACCOUNT_URI);
    pj_cstr(&target, LIVE_SIP_TARGET_URI);
    pj_cstr(&contact, contact_uri);

    status = pjsip_dlg_create_uac(pjsip_ua_instance(), &local_aor, &contact,
                                  &target, NULL, &dlg);
    if (status != PJ_SUCCESS) {
        log_pj_status("pjsip_dlg_create_uac(INVITE)", status);
        goto on_return;
    }

    pjsip_dlg_inc_lock(dlg);
    dlg_locked = PJ_TRUE;

    status = init_udp_transport_selector(&tp_sel);
    if (status != PJ_SUCCESS) {
        log_pj_status("init_udp_transport_selector", status);
        goto on_return;
    }

    status = pjsip_dlg_set_transport(dlg, &tp_sel);
    if (status != PJ_SUCCESS) {
        log_pj_status("pjsip_dlg_set_transport", status);
        goto on_return;
    }

    status = build_proxy_route_set(pool, &route_set);
    if (status != PJ_SUCCESS) {
        log_pj_status("build_proxy_route_set", status);
        goto on_return;
    }

    status = pjsip_dlg_set_route_set(dlg, &route_set);
    if (status != PJ_SUCCESS) {
        log_pj_status("pjsip_dlg_set_route_set", status);
        goto on_return;
    }

    init_live_auth_cred(&cred);
    status = pjsip_auth_clt_set_credentials(&dlg->auth_sess, 1, &cred);
    if (status != PJ_SUCCESS) {
        log_pj_status("pjsip_auth_clt_set_credentials", status);
        goto on_return;
    }

    status = create_live_media_transport(local_ip, &media_tp);
    if (status != PJ_SUCCESS) {
        log_pj_status("create_live_media_transport", status);
        goto on_return;
    }

    status = create_live_offer_sdp(dlg->pool, media_tp, &local_sdp);
    if (status != PJ_SUCCESS) {
        goto on_return;
    }

    status = pjsip_inv_create_uac(dlg, local_sdp, 0, &inv);
    if (status != PJ_SUCCESS) {
        log_pj_status("pjsip_inv_create_uac", status);
        goto on_return;
    }

    status = pjsip_inv_invite(inv, &tdata);
    if (status != PJ_SUCCESS) {
        log_pj_status("pjsip_inv_invite", status);
        goto on_return;
    }

    cid = (pjsip_cid_hdr *)pjsip_msg_find_hdr(tdata->msg, PJSIP_H_CALL_ID, NULL);
    if (!cid) {
        status = PJ_EBUG;
        log_pj_status("find Call-ID header", status);
        goto on_return;
    }

    live_sip_reset();
    live_sip_test.active = PJ_TRUE;
    live_sip_set_call_id(&cid->id);
    live_inv = inv;
    live_media_transport = media_tp;
    media_tp = NULL;

    log_info("live_sip: INVITE(with SDP) %s via %s",
             LIVE_SIP_TARGET_URI, LIVE_SIP_PROXY_URI);
    log_debug("live_sip: Call-ID=%s", live_sip_test.call_id);
    log_debug("live_sip: wait_response timeout=%d ms",
              LIVE_SIP_INVITE_TIMEOUT_MS);

    status = pjsip_inv_send_msg(inv, tdata);
    tdata = NULL;
    if (status != PJ_SUCCESS) {
        log_pj_status("pjsip_inv_send_msg(INVITE)", status);
        goto on_return;
    }

    pjsip_dlg_dec_lock(dlg);
    dlg_locked = PJ_FALSE;

    while (waited_ms < LIVE_SIP_INVITE_TIMEOUT_MS) {
        pj_time_val timeout = {0, 0};
        int event_cnt = pjsip_endpt_handle_events(sip_endpt, &timeout);

        if (event_cnt < 0) {
            status = PJ_EUNKNOWN;
            log_error("live_sip: handle_events=%d", event_cnt);
            goto on_return;
        }

        if (live_sip_test.call_established) {
            break;
        }

        if (live_sip_test.got_final && live_sip_test.final_status >= 300) {
            break;
        }

        pj_thread_sleep(LIVE_SIP_POLL_INTERVAL_MS);
        waited_ms += LIVE_SIP_POLL_INTERVAL_MS;
    }

    if (live_sip_test.call_established) {
        int call_window_ms = LIVE_SIP_CALL_HOLD_MS;

        if (call_window_ms < LIVE_SIP_AUDIO_DURATION_MS) {
            call_window_ms = LIVE_SIP_AUDIO_DURATION_MS;
        }

        if (live_audio_tx.media_negotiated &&
            !live_audio_tx.media_ready &&
            live_media_transport &&
            live_inv) {
            status = prepare_live_audio_tx(live_inv);
            if (status != PJ_SUCCESS) {
                log_pj_status("prepare_live_audio_tx", status);
                live_audio_tx.media_negotiated = PJ_FALSE;
            }
        }

        log_info("live_sip: call established, hold window=%d ms",
                 call_window_ms);

        while (established_ms < call_window_ms) {
            pj_time_val timeout = {0, 0};
            int event_cnt = pjsip_endpt_handle_events(sip_endpt, &timeout);

            if (event_cnt < 0) {
                status = PJ_EUNKNOWN;
                log_error("live_sip: handle_events=%d during call",
                          event_cnt);
                goto on_return;
            }

            if (live_sip_test.call_disconnected) {
                break;
            }

            if (live_audio_tx.media_ready) {
                status = send_live_audio_frame();
                if (status != PJ_SUCCESS) {
                    log_pj_status("send_live_audio_frame", status);
                    live_audio_tx.media_ready = PJ_FALSE;
                }
            }

            pj_thread_sleep(LIVE_SIP_AUDIO_FRAME_MS);
            established_ms += LIVE_SIP_AUDIO_FRAME_MS;
        }

        if (!live_sip_test.call_disconnected && live_inv) {
            status = pjsip_inv_end_session(live_inv, PJSIP_SC_OK, NULL, &bye_tdata);
            if (status != PJ_SUCCESS) {
                log_pj_status("pjsip_inv_end_session", status);
                goto on_return;
            }

            if (bye_tdata) {
                status = pjsip_inv_send_msg(live_inv, bye_tdata);
                bye_tdata = NULL;
                if (status != PJ_SUCCESS) {
                    log_pj_status("pjsip_inv_send_msg(BYE)", status);
                    goto on_return;
                }
                bye_sent = PJ_TRUE;
                log_info("live_sip: BYE sent");
            }
        }

        waited_ms = 0;
        while (bye_sent && waited_ms < LIVE_SIP_BYE_TIMEOUT_MS &&
               !live_sip_test.call_disconnected) {
            pj_time_val timeout = {0, 0};
            int event_cnt = pjsip_endpt_handle_events(sip_endpt, &timeout);

            if (event_cnt < 0) {
                status = PJ_EUNKNOWN;
                log_error("live_sip: handle_events=%d while waiting BYE",
                          event_cnt);
                goto on_return;
            }

            pj_thread_sleep(LIVE_SIP_POLL_INTERVAL_MS);
            waited_ms += LIVE_SIP_POLL_INTERVAL_MS;
        }

        log_info("live_sip: call connected, responses=%u disconnected=%d code=%d",
                 live_sip_test.response_cnt,
                 live_sip_test.call_disconnected,
                 live_sip_test.disconnect_code);
        status = PJ_SUCCESS;
        goto on_return;
    }

    if (!live_sip_test.got_response && !live_sip_test.got_final) {
        status = PJ_ETIMEDOUT;
        log_error("live_sip: no response within %d ms (actual_wait=%d ms)",
                  LIVE_SIP_INVITE_TIMEOUT_MS, waited_ms);
        goto on_return;
    }

    if (live_sip_test.got_final) {
        log_info("live_sip: final_status=%d, responses=%u",
                 live_sip_test.final_status, live_sip_test.response_cnt);
    } else {
        log_debug("live_sip: provisional response received, responses=%u",
                  live_sip_test.response_cnt);
    }

    status = PJ_SUCCESS;

on_return:
    live_sip_test.active = PJ_FALSE;
    if (tdata) {
        pjsip_tx_data_dec_ref(tdata);
    }
    if (bye_tdata) {
        pjsip_tx_data_dec_ref(bye_tdata);
    }
    if (dlg_locked && dlg) {
        pjsip_dlg_dec_lock(dlg);
    }
    if (status != PJ_SUCCESS && media_tp) {
        pjmedia_transport_close(media_tp);
    }
    return status;
}

static pj_status_t test_live_register(void)
{
    pj_status_t status;
    char local_ip[32];
    char contact_uri[128];
    pj_str_t registrar_uri;
    pj_str_t aor;
    pj_str_t contact;
    pjsip_tpselector tp_sel;
    pjsip_route_hdr route_set;
    pjsip_cred_info cred;
    pjsip_regc *regc = NULL;
    pjsip_tx_data *tdata = NULL;
    pjsip_cid_hdr *cid = NULL;

    live_reg_reset();
    seed_pj_random("live_register");

    status = get_local_ip_string(local_ip, sizeof(local_ip));
    if (status != PJ_SUCCESS) {
        log_pj_status("get_local_ip_string", status);
        return status;
    }

    log_debug("live_reg: local_ip=%s", local_ip);
    log_routed_target_probe("live_reg: registrar",
                            LIVE_SIP_REGISTRAR_URI,
                            LIVE_SIP_REGISTRAR_HOST);
    log_host_resolution("live_reg: proxy", LIVE_SIP_PROXY_HOST);

    pj_ansi_snprintf(contact_uri, sizeof(contact_uri),
                     "<sip:%s@%s:%d;transport=udp>",
                     LIVE_SIP_AUTH_USER, local_ip, SIP_PORT);
    pj_cstr(&registrar_uri, LIVE_SIP_REGISTRAR_URI);
    pj_cstr(&aor, LIVE_SIP_ACCOUNT_URI);
    pj_cstr(&contact, contact_uri);

    status = pjsip_regc_create(sip_endpt, &live_reg_test, &live_reg_on_complete,
                               &regc);
    if (status != PJ_SUCCESS) {
        log_pj_status("pjsip_regc_create", status);
        goto on_return;
    }

    status = pjsip_regc_set_reg_tsx_cb(regc, &live_reg_on_tsx);
    if (status != PJ_SUCCESS) {
        log_pj_status("pjsip_regc_set_reg_tsx_cb", status);
        goto on_return;
    }

    status = pjsip_regc_init(regc, &registrar_uri, &aor, &aor, 1, &contact,
                             LIVE_SIP_REGISTER_EXPIRES);
    if (status != PJ_SUCCESS) {
        log_pj_status("pjsip_regc_init", status);
        goto on_return;
    }

    status = pjsip_regc_set_delay_before_refresh(
                 regc, LIVE_SIP_REGISTER_REFRESH_MARGIN);
    if (status != PJ_SUCCESS) {
        log_pj_status("pjsip_regc_set_delay_before_refresh", status);
        goto on_return;
    }

    status = init_udp_transport_selector(&tp_sel);
    if (status != PJ_SUCCESS) {
        log_pj_status("init_udp_transport_selector", status);
        goto on_return;
    }

    status = pjsip_regc_set_transport(regc, &tp_sel);
    if (status != PJ_SUCCESS) {
        log_pj_status("pjsip_regc_set_transport", status);
        goto on_return;
    }

    status = build_proxy_route_set(pool, &route_set);
    if (status != PJ_SUCCESS) {
        log_pj_status("build_proxy_route_set", status);
        goto on_return;
    }

    status = pjsip_regc_set_route_set(regc, &route_set);
    if (status != PJ_SUCCESS) {
        log_pj_status("pjsip_regc_set_route_set", status);
        goto on_return;
    }

    init_live_auth_cred(&cred);
    status = pjsip_regc_set_credentials(regc, 1, &cred);
    if (status != PJ_SUCCESS) {
        log_pj_status("pjsip_regc_set_credentials", status);
        goto on_return;
    }

    status = pjsip_regc_register(regc, PJ_TRUE, &tdata);
    if (status != PJ_SUCCESS) {
        log_pj_status("pjsip_regc_register", status);
        goto on_return;
    }

    log_info("live_reg: REGISTER %s via %s",
             LIVE_SIP_ACCOUNT_URI, LIVE_SIP_PROXY_URI);

    cid = (pjsip_cid_hdr *)pjsip_msg_find_hdr(tdata->msg, PJSIP_H_CALL_ID, NULL);
    if (cid) {
        live_reg_set_call_id(&cid->id);
        log_debug("live_reg: Call-ID=%s", live_reg_test.call_id);
    } else {
        live_reg_set_call_id(NULL);
    }

    status = pjsip_regc_send(regc, tdata);
    tdata = NULL;
    if (status != PJ_SUCCESS) {
        log_pj_status("pjsip_regc_send", status);
        goto on_return;
    }
    log_debug("live_reg: request started, waiting for final response in step8");
    live_regc = regc;
    regc = NULL;
    status = PJ_SUCCESS;

on_return:
    if (tdata) {
        pjsip_tx_data_dec_ref(tdata);
    }
    if (regc) {
        pjsip_regc_destroy(regc);
    }
    return status;
}

/**
 * Cleanup resources
 */
static void cleanup(void)
{
    live_inv = NULL;
    service_release_keepalive();

    if (live_media_transport) {
        pjmedia_transport_detach(live_media_transport, &live_audio_tx);
        pjmedia_transport_media_stop(live_media_transport);
        pjmedia_transport_close(live_media_transport);
        live_media_transport = NULL;
    }
    release_live_audio_tx();

    /* Destroy media endpoint */
    if (med_endpt) {
        pjmedia_endpt_destroy2(med_endpt);
        med_endpt = NULL;
    }

    if (live_regc) {
        pjsip_regc_destroy(live_regc);
        live_regc = NULL;
    }

    if (udp_transport) {
        pjsip_transport_dec_ref(udp_transport);
        udp_transport = NULL;
    }

    /* Destroy SIP endpoint */
    if (sip_endpt) {
        if (pjsip_test_module.id != -1) {
            pjsip_endpt_unregister_module(sip_endpt, &pjsip_test_module);
        }
        pjsip_endpt_destroy(sip_endpt);
        sip_endpt = NULL;
    }

    /* Release pool */
    if (pool) {
        pj_pool_release(pool);
        pool = NULL;
    }

    /* Destroy caching pool */
    pj_caching_pool_destroy(&cp);

    /* Shutdown PJLIB */
    pj_shutdown();
}

static pj_status_t service_submit_command(enum pjsip_test_command_type type,
        const char *target_uri,
        unsigned timeout_ms)
{
    pj_status_t status = PJ_SUCCESS;
    int os_status;
    unsigned timeout_tick;

    if (!g_pjsip_test_service.thread_started || !g_pjsip_test_service.ready) {
        return PJ_EINVALIDOP;
    }

    os_mutex_pend(&g_pjsip_test_service.api_mutex, 0);

    if (g_pjsip_test_service.cmd.pending) {
        status = PJ_EBUSY;
        goto on_return;
    }

    os_sem_set(&g_pjsip_test_service.done_sem, 0);
    g_pjsip_test_service.last_cmd_status = PJ_EPENDING;
    g_pjsip_test_service.cmd.type = type;
    g_pjsip_test_service.cmd.pending = PJ_TRUE;
    g_pjsip_test_service.cmd.dispatched = PJ_FALSE;
    g_pjsip_test_service.cmd.target_uri[0] = '\0';
    if (target_uri && *target_uri) {
        pj_ansi_strncpy(g_pjsip_test_service.cmd.target_uri,
                        target_uri,
                        sizeof(g_pjsip_test_service.cmd.target_uri) - 1);
        g_pjsip_test_service
        .cmd.target_uri[sizeof(g_pjsip_test_service.cmd.target_uri) - 1] =
            '\0';
    }

    timeout_tick = timeout_ms ? ((timeout_ms + 9) / 10) : 0;
    os_status = os_sem_pend(&g_pjsip_test_service.done_sem, timeout_tick);
    if (os_status == OS_NO_ERR) {
        status = g_pjsip_test_service.last_cmd_status;
    } else {
        status = PJ_ETIMEDOUT;
    }

on_return:
    os_mutex_post(&g_pjsip_test_service.api_mutex);
    return status;
}

static pj_status_t pjsip_test_service_init(const struct pjsip_test_config *cfg)
{
    pj_status_t status;
    pj_thread_desc thread_desc;
    pj_thread_t *registered_thread = NULL;

    g_pjsip_test_cfg = cfg;

    status = init_pjlib();
    if (status != PJ_SUCCESS) {
        return status;
    }

    status = pj_thread_register("pjsip_task", thread_desc, &registered_thread);
    if (status != PJ_SUCCESS) {
        log_pj_status("pj_thread_register", status);
        return status;
    }

    status = init_pjsip();
    if (status != PJ_SUCCESS) {
        return status;
    }

    status = create_transport();
    if (status != PJ_SUCCESS) {
        return status;
    }

    status = init_pjmedia();
    if (status != PJ_SUCCESS) {
        return status;
    }

    service_set_reg_state(PJSIP_TEST_REG_IDLE);
    service_set_call_state(PJSIP_TEST_CALL_IDLE);
    return PJ_SUCCESS;
}

static void pjsip_test_service_loop(void)
{
    while (g_pjsip_test_service.thread_started) {
        pj_time_val timeout = {0, 0};
        int event_cnt;

        service_process_pending_command();

        event_cnt = pjsip_endpt_handle_events(sip_endpt, &timeout);
        if (event_cnt < 0) {
            log_error("service handle_events=%d", event_cnt);
        }

        if (live_inv && live_sip_test.call_established &&
            live_audio_tx.media_negotiated && !live_audio_tx.media_ready) {
            pj_status_t status = prepare_live_audio_tx(live_inv);
            if (status != PJ_SUCCESS) {
                log_pj_status("prepare_live_audio_tx", status);
            } else {
                log_info("live_sip: call established, audio armed");
                g_pjsip_test_service.next_audio_tick_ms = timer_get_ms();
            }
        }

        while (live_audio_tx.media_ready &&
               timer_get_ms() >= g_pjsip_test_service.next_audio_tick_ms) {
            pj_status_t status = send_live_audio_frame();
            if (status != PJ_SUCCESS) {
                log_pj_status("send_live_audio_frame", status);
                break;
            }
            g_pjsip_test_service.next_audio_tick_ms += LIVE_SIP_AUDIO_FRAME_MS;
        }

        if (g_pjsip_test_service.reg_state == PJSIP_TEST_REG_REGISTERED &&
            g_pjsip_test_service.ka_transport) {
            service_send_udp_keepalive();
        }

        if (g_pjsip_test_service.call_cleanup_pending &&
            g_pjsip_test_service.call_state == PJSIP_TEST_CALL_DISCONNECTED) {
            service_release_call_media();
            live_sip_reset();
            g_pjsip_test_service.call_dir = PJSIP_TEST_CALL_DIR_NONE;
            g_pjsip_test_service.call_cleanup_pending = PJ_FALSE;
            g_pjsip_test_service.next_audio_tick_ms = 0;
        }

        pj_thread_sleep(LIVE_SIP_POLL_INTERVAL_MS);
    }
}

static void pjsip_test_service_task(void *priv)
{
    PJ_UNUSED_ARG(priv);

    g_pjsip_test_service.init_status =
        pjsip_test_service_init(&g_pjsip_test_runtime_cfg);
    g_pjsip_test_service.init_done = PJ_TRUE;
    g_pjsip_test_service.ready =
        (g_pjsip_test_service.init_status == PJ_SUCCESS);
    g_pjsip_test_service.initialized = g_pjsip_test_service.ready;
    os_sem_post(&g_pjsip_test_service.ready_sem);

    if (g_pjsip_test_service.init_status == PJ_SUCCESS) {
        log_info("service ready");
        pjsip_test_service_loop();
        cleanup();
    } else {
        if (pool || sip_endpt || med_endpt || live_regc || udp_transport) {
            cleanup();
        }
    }

    g_pjsip_test_service.ready = PJ_FALSE;
    g_pjsip_test_service.initialized = PJ_FALSE;
    g_pjsip_test_service.thread_started = PJ_FALSE;
    g_pjsip_test_service.call_dir = PJSIP_TEST_CALL_DIR_NONE;
    g_pjsip_test_service.call_cleanup_pending = PJ_FALSE;
    service_set_peer_uri(NULL);
    g_pjsip_test_cfg = NULL;
}

pj_status_t pjsip_test_service_start(const struct pjsip_test_config *cfg)
{
    int os_status;

    PJ_ASSERT_RETURN(cfg != NULL, PJ_EINVAL);

    if (!os_sem_valid(&g_pjsip_test_service.ready_sem)) {
        os_sem_create(&g_pjsip_test_service.ready_sem, 0);
    }
    if (!os_sem_valid(&g_pjsip_test_service.done_sem)) {
        os_sem_create(&g_pjsip_test_service.done_sem, 0);
    }
    if (!os_mutex_valid(&g_pjsip_test_service.api_mutex)) {
        os_mutex_create(&g_pjsip_test_service.api_mutex);
    }

    os_mutex_pend(&g_pjsip_test_service.api_mutex, 0);
    if (g_pjsip_test_service.thread_started) {
        os_mutex_post(&g_pjsip_test_service.api_mutex);
        return PJ_SUCCESS;
    }

    g_pjsip_test_runtime_cfg = *cfg;
    g_pjsip_test_service.init_done = PJ_FALSE;
    g_pjsip_test_service.init_status = PJ_EPENDING;
    g_pjsip_test_service.ready = PJ_FALSE;
    g_pjsip_test_service.initialized = PJ_FALSE;
    g_pjsip_test_service.thread_started = PJ_TRUE;
    g_pjsip_test_service.thread_pid = -1;
    g_pjsip_test_service.reg_state = PJSIP_TEST_REG_IDLE;
    g_pjsip_test_service.call_state = PJSIP_TEST_CALL_IDLE;
    g_pjsip_test_service.call_dir = PJSIP_TEST_CALL_DIR_NONE;
    g_pjsip_test_service.call_cleanup_pending = PJ_FALSE;
    g_pjsip_test_service.current_peer_uri[0] = '\0';
    g_pjsip_test_service.next_audio_tick_ms = 0;
    g_pjsip_test_service.next_keepalive_tick_ms = 0;
    g_pjsip_test_service.cmd.type = PJSIP_TEST_CMD_NONE;
    g_pjsip_test_service.cmd.pending = PJ_FALSE;
    g_pjsip_test_service.cmd.dispatched = PJ_FALSE;
    g_pjsip_test_service.last_cmd_status = PJ_SUCCESS;
    os_sem_set(&g_pjsip_test_service.ready_sem, 0);
    os_sem_set(&g_pjsip_test_service.done_sem, 0);

    if (thread_fork("pjsip_task", 25,
                    cfg->thread_stack_size,
                    0,
                    &g_pjsip_test_service.thread_pid,
                    pjsip_test_service_task,
                    NULL) != OS_NO_ERR) {
        g_pjsip_test_service.thread_started = PJ_FALSE;
        os_mutex_post(&g_pjsip_test_service.api_mutex);
        return PJ_EUNKNOWN;
    }
    os_mutex_post(&g_pjsip_test_service.api_mutex);

    os_status = os_sem_pend(&g_pjsip_test_service.ready_sem, 0);
    if (os_status != OS_NO_ERR) {
        return PJ_EUNKNOWN;
    }

    return g_pjsip_test_service.init_status;
}

pj_status_t pjsip_test_service_start_default(void)
{
    const struct pjsip_test_config *cfg = pjsip_test_get_default_config();

    PJ_ASSERT_RETURN(cfg != NULL, PJ_EINVAL);
    return pjsip_test_service_start(cfg);
}

pj_status_t pjsip_test_register_account(void)
{
    return service_submit_command(PJSIP_TEST_CMD_REGISTER,
                                  NULL,
                                  LIVE_SIP_RESPONSE_TIMEOUT_MS + 5000U);
}

pj_status_t pjsip_test_make_call(const char *target_uri)
{
    return service_submit_command(PJSIP_TEST_CMD_MAKE_CALL,
                                  target_uri,
                                  LIVE_SIP_RESPONSE_TIMEOUT_MS);
}

pj_status_t pjsip_test_answer_call(void)
{
    return service_submit_command(PJSIP_TEST_CMD_ANSWER_CALL,
                                  NULL,
                                  3000);
}

pj_status_t pjsip_test_hangup_call(void)
{
    return service_submit_command(PJSIP_TEST_CMD_HANGUP_CALL,
                                  NULL,
                                  3000);
}

/**
 * Run minimal PJSIP test
 */
static pj_status_t run_minimal_test(void)
{
    pj_status_t status;
    pj_status_t reg_status = PJ_SUCCESS;
    pj_status_t invite_status = PJ_SUCCESS;
    pj_thread_desc thread_desc;
    pj_thread_t *registered_thread = NULL;
    u8 pjlib_ready = 0;

    log_info("run_minimal_test enter");

    /* Initialize PJLIB */
    log_info("step1: init_pjlib");
    status = init_pjlib();
    if (status != PJ_SUCCESS) {
        log_pj_status("init_pjlib", status);
        goto on_return;
    }
    pjlib_ready = 1;
    log_info("step1: OK");

    status = pj_thread_register("pjsip_task", thread_desc, &registered_thread);
    if (status != PJ_SUCCESS) {
        log_pj_status("pj_thread_register", status);
        goto on_return;
    }
    log_info("step1b: thread_register OK (%s)",
             pj_thread_get_name(registered_thread));

    /* Initialize PJSIP */
    log_info("step2: init_pjsip");
    status = init_pjsip();
    if (status != PJ_SUCCESS) {
        log_pj_status("init_pjsip", status);
        goto on_return;
    }
    log_info("step2: OK");

    if (wait_network_ready() != 0) {
        status = PJ_ETIMEDOUT;
        log_info("[WARN] network not ready for minimal SIP test");
        goto on_return;
    }

    /* Create transport */
    log_info("step3: create_transport");
    status = create_transport();
    if (status != PJ_SUCCESS) {
        log_pj_status("create_transport", status);
        goto on_return;
    }
    log_info("step3: OK");

    log_info("step4: event_poll");
    status = test_pjsip_event_poll();
    if (status != PJ_SUCCESS) {
        log_pj_status("test_pjsip_event_poll", status);
        goto on_return;
    }
    log_info("step4: OK");

    /* Initialize PJMEDIA */
    log_info("step5: init_pjmedia");
    status = init_pjmedia();
    if (status != PJ_SUCCESS) {
        log_pj_status("init_pjmedia", status);
        goto on_return;
    }
    log_info("step5: OK");

    /* Test basic SIP functionality */
    log_info("step6: basic_sip");
    status = test_basic_sip();
    if (status != PJ_SUCCESS) {
        log_pj_status("test_basic_sip", status);
        goto on_return;
    }
    log_info("step6: OK");

    /* Test basic PJMEDIA functionality */
    log_info("step7: basic_media");
    status = test_basic_media();
    if (status != PJ_SUCCESS) {
        log_pj_status("test_basic_media", status);
        goto on_return;
    }
    log_info("step7: OK");

    log_info("step8: live_register");
    reg_status = test_live_register();
    if (reg_status != PJ_SUCCESS) {
        log_pj_status("test_live_register", reg_status);
        status = reg_status;
        goto on_return;
    }
    reg_status = wait_for_live_register_final();
    if (reg_status != PJ_SUCCESS) {
        log_pj_status("wait_for_live_register_final", reg_status);
        status = reg_status;
        goto on_return;
    }
    log_info("step8: OK");

    log_info("step9: live_invite");
    invite_status = test_live_invite();
    if (invite_status != PJ_SUCCESS) {
        log_pj_status("test_live_invite", invite_status);
        status = invite_status;
        goto on_return;
    }
    log_info("step9: OK");
    log_info("PJSIP signaling verification: PASS");

    status = PJ_SUCCESS;

on_return:
    if (pjlib_ready) {
        log_info("cleanup");
        cleanup();
    }

    log_info("run_minimal_test exit");
    return status;
}

/**
 * Core test entry point
 */
pj_status_t pjsip_test_run(const struct pjsip_test_config *cfg)
{
    pj_status_t status;

//等待WiFi连接
    PJ_ASSERT_RETURN(cfg != NULL, PJ_EINVAL);
    PJ_ASSERT_RETURN(cfg->sip_port != 0, PJ_EINVAL);
    PJ_ASSERT_RETURN(cfg->basic_rtp_port != 0, PJ_EINVAL);
    PJ_ASSERT_RETURN(cfg->udp_start_retry_max != 0, PJ_EINVAL);
    PJ_ASSERT_RETURN(cfg->net_ready_wait_step_tick != 0, PJ_EINVAL);
    PJ_ASSERT_RETURN(cfg->poll_interval_ms != 0, PJ_EINVAL);
    PJ_ASSERT_RETURN(cfg->audio_duration_ms != 0, PJ_EINVAL);
    PJ_ASSERT_RETURN(cfg->register_expires != 0, PJ_EINVAL);
    PJ_ASSERT_RETURN(cfg->rtp_port_retry != 0, PJ_EINVAL);
    PJ_ASSERT_RETURN(cfg->account_uri != NULL, PJ_EINVAL);
    PJ_ASSERT_RETURN(cfg->registrar_uri != NULL, PJ_EINVAL);
    PJ_ASSERT_RETURN(cfg->registrar_host != NULL, PJ_EINVAL);
    PJ_ASSERT_RETURN(cfg->proxy_uri != NULL, PJ_EINVAL);
    PJ_ASSERT_RETURN(cfg->proxy_host != NULL, PJ_EINVAL);
    PJ_ASSERT_RETURN(cfg->auth_realm != NULL, PJ_EINVAL);
    PJ_ASSERT_RETURN(cfg->auth_user != NULL, PJ_EINVAL);
    PJ_ASSERT_RETURN(cfg->auth_pass != NULL, PJ_EINVAL);
    PJ_ASSERT_RETURN(cfg->target_uri != NULL, PJ_EINVAL);
    PJ_ASSERT_RETURN(cfg->target_host != NULL, PJ_EINVAL);
    g_pjsip_test_cfg = cfg;
    log_info("run with target=%s proxy=%s register_expires=%u",
             cfg->target_uri,
             cfg->proxy_uri,
             cfg->register_expires);

    status = run_minimal_test();
    g_pjsip_test_cfg = NULL;
    return status;
}

pj_status_t pjsip_test_run_default(void)
{
    const struct pjsip_test_config *cfg = pjsip_test_get_default_config();

    PJ_ASSERT_RETURN(cfg != NULL, PJ_EINVAL);
    return pjsip_test_run(cfg);
}

#endif

