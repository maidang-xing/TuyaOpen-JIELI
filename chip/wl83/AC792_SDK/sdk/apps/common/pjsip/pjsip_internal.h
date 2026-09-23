#ifndef APPS_COMMON_PJSIP_PJSIP_INTERNAL_H
#define APPS_COMMON_PJSIP_PJSIP_INTERNAL_H

#include "app_config.h"

#if TCFG_PJSIP_ENABLE

#include <pjsip.h>
#include <pjsip/sip_parser.h>
#include <pjmedia.h>
#include <pjmedia-codec.h>
#include <pjmedia/rtp.h>
#include <pjsip_ua.h>
#include <pjsip-ua/sip_inv.h>
#include <pjsip-ua/sip_100rel.h>
#include <pjlib-util.h>
#include <pjlib.h>

#include "system/includes.h"
#include "generic/circular_buf.h"
#include "os/os_api.h"
#include "wifi/wifi_connect.h"
#include "lwip.h"
#include "lwip/inet.h"
#include "pjsip_test.h"

extern u32 timer_get_ms(void);

/* Shared runtime configuration */
extern const struct pjsip_test_config *g_pjsip_test_cfg;

#define SIP_PORT        ((pj_uint16_t)g_pjsip_test_cfg->sip_port)
#define RTP_PORT        ((pj_uint16_t)g_pjsip_test_cfg->basic_rtp_port)
#define UDP_START_RETRY_MAX         ((int)g_pjsip_test_cfg->udp_start_retry_max)
#define UDP_START_RETRY_DLY_TICK    ((int)g_pjsip_test_cfg->udp_start_retry_dly_tick)
#define NET_READY_WAIT_TIMEOUT_TICK ((int)g_pjsip_test_cfg->net_ready_wait_timeout_tick)
#define NET_READY_WAIT_STEP_TICK    ((int)g_pjsip_test_cfg->net_ready_wait_step_tick)
#define LIVE_SIP_ACCOUNT_URI        (g_pjsip_test_cfg->account_uri)
#define LIVE_SIP_REGISTRAR_URI      (g_pjsip_test_cfg->registrar_uri)
#define LIVE_SIP_REGISTRAR_HOST     (g_pjsip_test_cfg->registrar_host)
#define LIVE_SIP_PROXY_URI          (g_pjsip_test_cfg->proxy_uri)
#define LIVE_SIP_PROXY_HOST         (g_pjsip_test_cfg->proxy_host)
#define LIVE_SIP_AUTH_REALM         (g_pjsip_test_cfg->auth_realm)
#define LIVE_SIP_AUTH_USER          (g_pjsip_test_cfg->auth_user)
#define LIVE_SIP_AUTH_PASS          (g_pjsip_test_cfg->auth_pass)
#define LIVE_SIP_TARGET_URI         (g_pjsip_test_cfg->target_uri)
#define LIVE_SIP_TARGET_HOST        (g_pjsip_test_cfg->target_host)
#define LIVE_SIP_REGISTER_EXPIRES   ((int)g_pjsip_test_cfg->register_expires)
#define LIVE_SIP_REGISTER_REFRESH_MARGIN \
    ((int)g_pjsip_test_cfg->register_refresh_margin)
#define LIVE_SIP_RESPONSE_TIMEOUT_MS ((int)g_pjsip_test_cfg->response_timeout_ms)
#define LIVE_SIP_INVITE_TIMEOUT_MS   ((int)g_pjsip_test_cfg->invite_timeout_ms)
#define LIVE_SIP_POLL_INTERVAL_MS    ((int)g_pjsip_test_cfg->poll_interval_ms)
#define LIVE_SIP_CALL_ID_MAX          128
#define LIVE_SIP_CALL_HOLD_MS        ((int)g_pjsip_test_cfg->call_hold_ms)
#define LIVE_SIP_AUDIO_FRAME_MS        20
#define LIVE_SIP_AUDIO_DURATION_MS   ((int)g_pjsip_test_cfg->audio_duration_ms)
#define LIVE_SIP_AUDIO_SPF           320
#define LIVE_SIP_AUDIO_SAMPLE_RATE   8000
#define LIVE_SIP_AUDIO_CAPTURE_RATE  16000
#define LIVE_SIP_AUDIO_SAMPLE_BYTES    2
#define LIVE_SIP_AUDIO_FRAME_BYTES \
    (LIVE_SIP_AUDIO_SPF * LIVE_SIP_AUDIO_SAMPLE_BYTES)
#define LIVE_SIP_AUDIO_RING_FRAMES    50
#define LIVE_SIP_AUDIO_RING_BYTES \
    (LIVE_SIP_AUDIO_FRAME_BYTES * LIVE_SIP_AUDIO_RING_FRAMES)
#define LIVE_SIP_BYE_TIMEOUT_MS      ((int)g_pjsip_test_cfg->bye_timeout_ms)
#define LIVE_RTP_PORT_BASE           ((int)g_pjsip_test_cfg->rtp_port_base)
#define LIVE_RTP_PORT_RETRY          ((int)g_pjsip_test_cfg->rtp_port_retry)
#define LIVE_SIP_KEEPALIVE_INTERVAL_SEC \
    ((int)g_pjsip_test_cfg->keepalive_interval_sec)
#define LIVE_SIP_KEEPALIVE_DATA      (g_pjsip_test_cfg->keepalive_data)

/* Shared runtime state */
struct live_reg_test_state {
    pj_bool_t done;
    pj_status_t status;
    int final_code;
    unsigned response_cnt;
    unsigned expiration;
    char call_id[LIVE_SIP_CALL_ID_MAX];
};

struct live_sip_test_state {
    pj_bool_t active;
    pj_bool_t got_response;
    pj_bool_t got_final;
    int final_status;
    pj_bool_t call_established;
    pj_bool_t call_disconnected;
    int disconnect_code;
    unsigned response_cnt;
    char call_id[LIVE_SIP_CALL_ID_MAX];
};

struct live_audio_tx_state {
    pj_bool_t media_negotiated;
    pj_bool_t media_ready;
    int payload_type;
    pj_bool_t use_alaw;
    unsigned frames_sent;
    unsigned total_frames;
    pjmedia_rtp_session rtp;
    pj_sockaddr rem_rtp;
    void *mic_recorder;
    cbuffer_t mic_cbuf;
    unsigned mic_overflow_cnt;
    unsigned mic_underrun_cnt;
};

struct live_audio_rx_state {
    pj_bool_t media_negotiated;
    pj_bool_t media_ready;
    int payload_type;
    pj_bool_t use_alaw;

    void *player;
    cbuffer_t spk_cbuf;

    unsigned frames_recv;
    unsigned decode_err_cnt;
    unsigned spk_overflow_cnt;
    unsigned spk_underrun_cnt;
};

struct pjsip_audio_capture_param {
    u32 sample_rate;
    u32 coding_type;
    u8 channel_mode;
    u8 bit_wide;
    u16 source_irq_points;
    u16 encoder_frame_dms;
    void *priv;
    void (*output)(void *priv, u8 *buf, u32 len);
};

extern pj_caching_pool cp;
extern pjsip_endpoint *sip_endpt;
extern pjsip_transport *udp_transport;
extern pjsip_regc *live_regc;
extern pjsip_inv_session *live_inv;
extern pjmedia_transport *live_media_transport;
extern pjmedia_endpt *med_endpt;
extern pj_pool_t *pool;
extern struct live_reg_test_state live_reg_test;
extern struct live_sip_test_state live_sip_test;
extern struct live_audio_tx_state live_audio_tx;
extern struct live_audio_rx_state live_audio_rx;
extern unsigned live_rand_seq;

/* OS/PJLIB helpers */
void format_reason_text(const pj_str_t *reason, char *buf, unsigned buf_size);
void dump_sip_msg(const char *tag, pj_pool_t *tmp_pool, pjsip_msg *msg);
void log_pj_status(const char *stage, pj_status_t status);
void seed_pj_random(const char *tag);
pj_status_t init_pjlib(void);
pj_status_t init_udp_transport_selector(pjsip_tpselector *tp_sel);

/* lwIP/network helpers */
pj_status_t get_local_ip_string(char *buf, unsigned buf_size);
void log_host_resolution(const char *label, const char *host);
void log_routed_target_probe(const char *label,
                             const char *uri,
                             const char *host);
int wait_network_ready(void);

/* Media/audio helpers */
pj_status_t init_pjmedia(void);
pj_status_t test_basic_media(void);
pj_status_t create_live_offer_sdp(pj_pool_t *sdp_pool,
                                  pjmedia_transport *media_tp,
                                  pjmedia_sdp_session **p_sdp);
pj_status_t create_live_media_transport(const char *local_ip,
                                        pjmedia_transport **p_media_tp);
pj_status_t prepare_live_audio_tx(pjsip_inv_session *inv);
pj_status_t send_live_audio_frame(void);
void release_live_audio_tx(void);
void pjsip_audio_capture_init_param(struct pjsip_audio_capture_param *param);
void *pjsip_audio_capture_open(const struct pjsip_audio_capture_param *param);
int pjsip_audio_capture_close(void *priv);

#endif
#endif

