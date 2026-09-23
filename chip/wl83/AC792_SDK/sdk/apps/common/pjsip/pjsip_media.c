/**
 * @file pjsip_media.c
 * @brief Audio/media related helpers for the PJSIP service
 *
 * Responsibilities:
 * - Initialize pjmedia endpoint objects used by the SIP service.
 * - Create RTP/SDP helpers for call setup and media negotiation.
 * - Capture live MIC PCM and packetize it into G.711 RTP frames.
 *
 * Boundaries:
 * - Does not own SIP dialog/register/call state transitions.
 * - Current scope is uplink only; downlink playback is still handled later.
 * - Uses the existing WL83 recorder pipeline and keeps RTP pacing in SIP code.
 */


/*代码流程：
 *上行链路：
 *创建media endpoint: init_pjmedia()->创建tansport(socket的上层封装)：create_live_media_transport()->
 *创建本地音频SDP offer： create_live_offer_sdp()->对端应答后准备发数据： prepare_live_audio_tx()->
 *发送音频数据： send_live_audio_frame()。
 *会话管理如连接、保持等在pjsip_core.c中实现。
 */
#include "app_config.h"

#if TCFG_PJSIP_ENABLE

#define LOG_TAG             "[SIP]"
#define LOG_ERROR_ENABLE
#define LOG_INFO_ENABLE
#define LOG_DEBUG_ENABLE
#include "debug.h"

#include "pjsip_internal.h"
#include "jlstream.h"
#include "audio_config_def.h"

struct stream_file_ops;

extern void *virtual_dev_play_callback(void *file,
                                       const struct stream_file_ops *ops,
                                       void *arg,
                                       int (*evt_cb)(void *priv, int parm, enum stream_event event),
                                       void *evt_priv,
                                       u32 dec_type);

extern void virtual_dev_player_stop(void *player);

static pj_int16_t live_audio_pcm_buf[LIVE_SIP_AUDIO_SPF];   //一帧原始pcm缓冲
static pj_uint8_t live_audio_payload_buf[LIVE_SIP_AUDIO_SPF];    //G711编码后的一帧payload
static pj_uint8_t live_audio_packet_buf[sizeof(pjmedia_rtp_hdr) +
                                                                LIVE_SIP_AUDIO_SPF];     //RTP包缓存
static pj_uint8_t live_audio_ring_buf[LIVE_SIP_AUDIO_RING_BYTES];  //缓存


static pj_int16_t live_audio_rx_pcm_buf[LIVE_SIP_AUDIO_SPF];
static pj_uint8_t live_audio_spk_ring_buf[LIVE_SIP_AUDIO_RING_BYTES];

static void live_audio_log_buffer_event(const char *tag, unsigned count)
{
    if (count <= 3 || (count % 50) == 0) {
        log_info("[WARN] live_audio: %s=%u", tag, count);
    }
}

//param.output注册函数，MIC获取到数据时回调到这里， 把PCM数据写入live_audio_tx.mic_cbuf（发送缓存）。
static void live_audio_mic_output(void *priv, u8 *buf, u32 len)
{
    unsigned write_len;

    PJ_UNUSED_ARG(priv);

    if (!buf || !len || !live_audio_tx.media_ready) {
        return;
    }

    printf("====== MIC AUDIO DATA LEN: %d ======\n", len);
    if (len >= LIVE_SIP_AUDIO_RING_BYTES) {   //长度过大，要后面以截
        buf += len - LIVE_SIP_AUDIO_RING_BYTES;
        len = LIVE_SIP_AUDIO_RING_BYTES;
        cbuf_clear(&live_audio_tx.mic_cbuf);
    }

    write_len = cbuf_write(&live_audio_tx.mic_cbuf, buf, len);
    if (write_len == len) {    //一次性读完
        return;
    }

    cbuf_clear(&live_audio_tx.mic_cbuf);    //没读完清空重读试试
    write_len = cbuf_write(&live_audio_tx.mic_cbuf, buf, len);
    ++live_audio_tx.mic_overflow_cnt;
    live_audio_log_buffer_event("mic_overflow", live_audio_tx.mic_overflow_cnt);

    if (write_len != len) {    //还是读不完，算了
        log_error("live_audio: mic cache write failed len=%u write=%u",
                  len,
                  write_len);
    }
}

//播放回调，占位无实际功能。
static int live_audio_player_event_callback(void *priv, int parm, enum stream_event event)
{
    PJ_UNUSED_ARG(priv);
    PJ_UNUSED_ARG(parm);

    switch (event) {
    case STREAM_EVENT_START:
        log_info("live_audio_rx: player start");
        break;
    case STREAM_EVENT_STOP:
        log_info("live_audio_rx: player stop");
        break;
    case STREAM_EVENT_END:
        log_info("live_audio_rx: player end");
        break;
    default:
        break;
    }

    return 0;
}

//.read
static int live_audio_spk_read(void *file, u8 *buf, int len)
{
    unsigned read_len;

    PJ_UNUSED_ARG(file);

    if (!buf || len <= 0) {
        return 0;
    }

    read_len = cbuf_read(&live_audio_rx.spk_cbuf, buf, len);
    if (read_len < (unsigned)len) {
        pj_bzero(buf + read_len, len - read_len);
        ++live_audio_rx.spk_underrun_cnt;
        live_audio_log_buffer_event("spk_underrun", live_audio_rx.spk_underrun_cnt);
        return len;
    }

    return len;
}

//.seek
static int live_audio_spk_seek(void *file, int offset, int fromwhere)
{
    PJ_UNUSED_ARG(file);
    PJ_UNUSED_ARG(offset);
    PJ_UNUSED_ARG(fromwhere);
    return -EINVAL;
}

//.close
static int live_audio_spk_close(void *file)
{
    PJ_UNUSED_ARG(file);
    return 0;
}

//.get_fmt
static int live_audio_spk_get_fmt(void *file, struct stream_fmt *fmt)
{
    PJ_UNUSED_ARG(file);

    if (!fmt) {
        return -EINVAL;
    }

    fmt->coding_type   = AUDIO_CODING_PCM;
    fmt->sample_rate   = LIVE_SIP_AUDIO_SAMPLE_RATE;
    fmt->channel_mode  = AUDIO_CH_L;
    fmt->pcm_file_mode = 1;
    return 0;
}

//下行链路
static const struct stream_file_ops live_audio_spk_ops = {
    .read    = live_audio_spk_read,
    .seek    = live_audio_spk_seek,
    .close   = live_audio_spk_close,
    .get_fmt = live_audio_spk_get_fmt,
};

//播放音频
static pj_status_t start_live_audio_playback(void)
{
    if (live_audio_rx.player) {
        return PJ_SUCCESS;
    }

    cbuf_init(&live_audio_rx.spk_cbuf,
              live_audio_spk_ring_buf,
              sizeof(live_audio_spk_ring_buf));

    live_audio_rx.player = virtual_dev_play_callback(&live_audio_rx,
                           &live_audio_spk_ops,
                           NULL,
                           live_audio_player_event_callback,
                           NULL,
                           AUDIO_CODING_PCM);
    if (!live_audio_rx.player) {
        log_error("live_audio_rx: player open failed");
        return PJ_EUNKNOWN;
    }

    log_info("live_audio_rx: playback started sr=%d frame=%dms",
             LIVE_SIP_AUDIO_SAMPLE_RATE,
             LIVE_SIP_AUDIO_FRAME_MS);
    return PJ_SUCCESS;
}

static void stop_live_audio_playback(void)
{
    if (live_audio_rx.player) {
        virtual_dev_player_stop(live_audio_rx.player);
        live_audio_rx.player = NULL;
    }
}

//下行PCM写ring
static void live_audio_spk_write_pcm(const pj_int16_t *pcm, unsigned samples)
{
    unsigned bytes;
    unsigned write_len;

    if (!pcm || !samples || !live_audio_rx.media_ready) {
        return;
    }

    bytes = samples * sizeof(pj_int16_t);

    if (bytes >= LIVE_SIP_AUDIO_RING_BYTES) {
        pcm = (const pj_int16_t *)((const u8 *)pcm +
                                   (bytes - LIVE_SIP_AUDIO_RING_BYTES));
        bytes = LIVE_SIP_AUDIO_RING_BYTES;
        cbuf_clear(&live_audio_rx.spk_cbuf);
    }

    write_len = cbuf_write(&live_audio_rx.spk_cbuf, pcm, bytes);
    if (write_len == bytes) {
        return;
    }

    cbuf_clear(&live_audio_rx.spk_cbuf);
    write_len = cbuf_write(&live_audio_rx.spk_cbuf, pcm, bytes);
    ++live_audio_rx.spk_overflow_cnt;
    live_audio_log_buffer_event("spk_overflow", live_audio_rx.spk_overflow_cnt);

    if (write_len != bytes) {
        log_error("live_audio_rx: spk cache write failed bytes=%u write=%u",
                  bytes,
                  write_len);
    }
}

/*
 * 注意：
 * 不同 pjproject 版本里 transport RTP 回调签名可能略有差异。
 * 你当前如果编译报形参不匹配，只需要按本地头文件把参数列表对齐即可。
 */
//RTP接收回调



static int save_G711_data(void *data, unsigned data_len)
{
    FILE *fd = NULL;

    if (!data || data_len == 0) {
        return -1;
    }

    fd = fopen(CONFIG_ROOT_PATH "image******.g711", "ab");
    if (!fd) {
        return -1;
    }

    fwrite(data, 1, data_len, fd);
    fclose(fd);
    return 0;
}

static void live_audio_on_rx_rtp(void *user_data, void *pkt, pj_ssize_t size)
{
    printf("%s=====%d\n", __func__, __LINE__);
    pjmedia_rtp_hdr *hdr;
    unsigned hdr_len;
    unsigned payload_len;
    unsigned pt;
    pj_uint8_t *payload;

    PJ_UNUSED_ARG(user_data);

    if (!pkt || size <= (pj_ssize_t)sizeof(pjmedia_rtp_hdr) ||
        !live_audio_rx.media_ready) {
        return;
    }

    hdr = (pjmedia_rtp_hdr *)pkt;

    if (hdr->v != 2) {
        ++live_audio_rx.decode_err_cnt;
        live_audio_log_buffer_event("rx_bad_ver", live_audio_rx.decode_err_cnt);
        return;
    }

    hdr_len = sizeof(pjmedia_rtp_hdr) + (hdr->cc * 4);

    /* 当前先不处理 RTP extension */
    if (hdr->x) {
        ++live_audio_rx.decode_err_cnt;
        live_audio_log_buffer_event("rx_ext_drop", live_audio_rx.decode_err_cnt);
        return;
    }

    if ((unsigned)size <= hdr_len) {
        ++live_audio_rx.decode_err_cnt;
        live_audio_log_buffer_event("rx_short", live_audio_rx.decode_err_cnt);
        return;
    }

    pt = hdr->pt & 0x7F;
    if ((int)pt != live_audio_rx.payload_type) {
        return;
    }

    payload = ((pj_uint8_t *)pkt) + hdr_len;
    payload_len = (unsigned)size - hdr_len;
    printf("====== RTP Payload len : %d =======\n", payload_len);
    //put_buf(payload, payload_len);

    /*
     * 对 G.711 来说，1 字节对应 1 个 sample。
     * 通常 20ms@8k 是 160 字节，但这里按实际收到长度解码。
     */
    if (payload_len > LIVE_SIP_AUDIO_SPF) {
        payload_len = LIVE_SIP_AUDIO_SPF;
    }

    if (live_audio_rx.use_alaw) {
        pjmedia_alaw_decode(live_audio_rx_pcm_buf, payload, payload_len);
    } else {
        pjmedia_ulaw_decode(live_audio_rx_pcm_buf, payload, payload_len);
    }


    live_audio_spk_write_pcm(live_audio_rx_pcm_buf, payload_len);

    ++live_audio_rx.frames_recv;
    if (live_audio_rx.frames_recv == 1) {
        log_info("live_audio_rx: first rtp received pt=%u codec=%s",
                 pt,
                 live_audio_rx.use_alaw ? "PCMA" : "PCMU");
    }
}

//RTCP不管先
static void live_audio_on_rx_rtcp(void *user_data, void *pkt, pj_ssize_t size)
{
    PJ_UNUSED_ARG(user_data);
    PJ_UNUSED_ARG(pkt);
    PJ_UNUSED_ARG(size);
}

//启动录音
static pj_status_t start_live_audio_capture(void)
{
    struct pjsip_audio_capture_param param;

    if (live_audio_tx.mic_recorder) {
        return PJ_SUCCESS;
    }

    cbuf_init(&live_audio_tx.mic_cbuf,
              live_audio_ring_buf,
              sizeof(live_audio_ring_buf));

    pjsip_audio_capture_init_param(&param);
    param.priv = NULL;
    param.output = live_audio_mic_output;

    live_audio_tx.mic_recorder = pjsip_audio_capture_open(&param);
    if (!live_audio_tx.mic_recorder) {
        log_error("live_audio: mic recorder open failed");
        return PJ_EUNKNOWN;
    }

    log_info("live_audio: mic started sr=%d frame=%dms",
             LIVE_SIP_AUDIO_SAMPLE_RATE,
             LIVE_SIP_AUDIO_FRAME_MS);
    return PJ_SUCCESS;
}

//关mic_recorder，清空live_audio_tx结构体。
void release_live_audio_tx(void)
{
    if (live_audio_tx.mic_recorder) {
        pjsip_audio_capture_close(live_audio_tx.mic_recorder);
        live_audio_tx.mic_recorder = NULL;
    }

    if (live_audio_rx.player) {
        stop_live_audio_playback();
    }

    pj_bzero(&live_audio_tx, sizeof(live_audio_tx));
    live_audio_tx.payload_type = -1;

    pj_bzero(&live_audio_rx, sizeof(live_audio_rx));
    live_audio_rx.payload_type = -1;
}

//从SDP中选择音频类型PCMA/PCMU
static pj_status_t select_live_audio_payload_type(
    const pjmedia_sdp_session *remote_sdp,
    unsigned media_index,
    int *payload_type,
    pj_bool_t *use_alaw)
{
    const pjmedia_sdp_media *media;
    unsigned i;
    int fallback_pt = -1;
    pj_bool_t fallback_use_alaw = PJ_FALSE;

    PJ_ASSERT_RETURN(remote_sdp && payload_type && use_alaw, PJ_EINVAL);
    PJ_ASSERT_RETURN(media_index < remote_sdp->media_count, PJ_EINVAL);

    media = remote_sdp->media[media_index];
    PJ_ASSERT_RETURN(media != NULL, PJ_EINVAL);

    for (i = 0; i < media->desc.fmt_count; ++i) {
        int pt;

        if (!media->desc.fmt[i].ptr || media->desc.fmt[i].slen <= 0 ||
            !pj_isdigit((unsigned char)media->desc.fmt[i].ptr[0])) {
            continue;
        }

        pt = (int)pj_strtoul(&media->desc.fmt[i]);
        if (pt == 8) {      //优先PCMA
            *payload_type = pt;
            *use_alaw = PJ_TRUE;
            return PJ_SUCCESS;
        }
        if (pt == 0 && fallback_pt < 0) {
            fallback_pt = pt;
            fallback_use_alaw = PJ_FALSE;
        }
    }

    if (fallback_pt >= 0) {
        *payload_type = fallback_pt;
        *use_alaw = fallback_use_alaw;
        return PJ_SUCCESS;
    }

    return PJ_ENOTSUP;
}

//把远端 SDP 中的音频目标地址解析成 pj_sockaddr
static pj_status_t build_live_remote_rtp_addr(
    const pjmedia_sdp_session *remote_sdp,
    unsigned media_index,
    pj_sockaddr *rem_rtp)
{
    const pjmedia_sdp_media *media;
    const pjmedia_sdp_conn *conn;
    int af;
    pj_status_t status;

    PJ_ASSERT_RETURN(remote_sdp && rem_rtp, PJ_EINVAL);
    PJ_ASSERT_RETURN(media_index < remote_sdp->media_count, PJ_EINVAL);

    media = remote_sdp->media[media_index];
    PJ_ASSERT_RETURN(media != NULL, PJ_EINVAL);

    conn = media->conn ? media->conn : remote_sdp->conn;
    PJ_ASSERT_RETURN(conn != NULL, PJ_EINVAL);
    PJ_ASSERT_RETURN(media->desc.port != 0, PJ_EINVAL);

    if (pj_stricmp2(&conn->net_type, "IN") != 0) {
        return PJ_EAFNOTSUP;
    }

    if (pj_stricmp2(&conn->addr_type, "IP6") == 0) {
        af = pj_AF_INET6();
    } else if (pj_stricmp2(&conn->addr_type, "IP4") == 0) {
        af = pj_AF_INET();
    } else {
        return PJ_EAFNOTSUP;
    }

    status = pj_sockaddr_init(af, rem_rtp, &conn->addr, media->desc.port);
    if (status != PJ_SUCCESS) {
        return status;
    }

    if (!pj_sockaddr_has_addr(rem_rtp)) {
        return PJ_ENOTFOUND;
    }

    return PJ_SUCCESS;
}


//上行链路参数解析
pj_status_t prepare_live_audio_tx(pjsip_inv_session *inv)
{
    const pjmedia_sdp_session *local_sdp = NULL;
    const pjmedia_sdp_session *remote_sdp = NULL;
    pj_sockaddr rem_rtp;
    char addr_buf[64];
    pj_bool_t tp_attached = PJ_FALSE;
    pj_bool_t media_started = PJ_FALSE;
    pj_status_t status;

    PJ_ASSERT_RETURN(inv && inv->neg && live_media_transport, PJ_EINVAL);

    //从 inv->neg 取当前 local/remote SDP
    status = pjmedia_sdp_neg_get_active_local(inv->neg, &local_sdp);
    if (status != PJ_SUCCESS) {
        log_pj_status("pjmedia_sdp_neg_get_active_local", status);
        return status;
    }

    status = pjmedia_sdp_neg_get_active_remote(inv->neg, &remote_sdp);
    if (status != PJ_SUCCESS) {
        log_pj_status("pjmedia_sdp_neg_get_active_remote", status);
        return status;
    }

    //选对端支持的 payload type
    status = select_live_audio_payload_type(remote_sdp, 0,
                                            &live_audio_tx.payload_type,
                                            &live_audio_tx.use_alaw);
    if (status != PJ_SUCCESS) {
        log_pj_status("select_live_audio_payload_type", status);
        return status;
    }

    //解析远端 RTP 地址
    status = build_live_remote_rtp_addr(remote_sdp, 0, &rem_rtp);
    if (status != PJ_SUCCESS) {
        log_pj_status("build_live_remote_rtp_addr", status);
        return status;
    }

    //把 transport 、audio_tx、rtp_cb绑定到这个远端
    status = pjmedia_transport_attach(live_media_transport,
                                      &live_audio_tx,
                                      &rem_rtp,
                                      NULL,
                                      pj_sockaddr_get_len(&rem_rtp),
                                      //NULL,          //rtp_cb，收到RTP报文时调用该回调
                                      //NULL);
                                      &live_audio_on_rx_rtp,
                                      &live_audio_on_rx_rtcp);
    if (status != PJ_SUCCESS) {
        log_pj_status("pjmedia_transport_attach", status);
        return status;
    }
    tp_attached = PJ_TRUE;

    /*return (*tp->op->media_start)(tp, tmp_pool, sdp_local, sdp_remote,
                                    media_index);*/
    status = pjmedia_transport_media_start(live_media_transport,
                                           inv->pool ? inv->pool : pool,
                                           local_sdp,
                                           remote_sdp,
                                           0);
    if (status != PJ_SUCCESS) {
        log_pj_status("pjmedia_transport_media_start", status);
        goto on_error;
    }
    media_started = PJ_TRUE;

    pj_bzero(&live_audio_rx, sizeof(live_audio_rx));
    live_audio_rx.payload_type = live_audio_tx.payload_type;
    live_audio_rx.use_alaw = live_audio_tx.use_alaw;
    cbuf_init(&live_audio_rx.spk_cbuf,
              live_audio_spk_ring_buf,
              sizeof(live_audio_spk_ring_buf));

    //保存rem_rtp地址到live_audio_tx，方便其他位置调用
    pj_sockaddr_cp(&live_audio_tx.rem_rtp, &rem_rtp);
    live_audio_tx.frames_sent = 0;
    live_audio_tx.total_frames = (unsigned) - 1;
    live_audio_tx.mic_overflow_cnt = 0;
    live_audio_tx.mic_underrun_cnt = 0;
    cbuf_init(&live_audio_tx.mic_cbuf,
              live_audio_ring_buf,
              sizeof(live_audio_ring_buf));

    //初始化本地RTP会话
    status = pjmedia_rtp_session_init(&live_audio_tx.rtp,
                                      live_audio_tx.payload_type,
                                      pj_rand());
    if (status != PJ_SUCCESS) {
        log_pj_status("pjmedia_rtp_session_init", status);
        goto on_error;
    }

    //打开MIC音频捕获
    status = start_live_audio_capture();
    if (status != PJ_SUCCESS) {
        goto on_error;
    }

    //打开player
    status = start_live_audio_playback();
    if (status != PJ_SUCCESS) {
        goto on_error;
    }

    live_audio_tx.media_ready = PJ_TRUE;     //ALL ready
    live_audio_rx.media_ready = PJ_TRUE;
    pj_sockaddr_print(&rem_rtp, addr_buf, sizeof(addr_buf), 0);
    log_info("live_audio: target=%s pt=%d codec=%s mode=mic",
             addr_buf,
             live_audio_tx.payload_type,
             live_audio_tx.use_alaw ? "PCMA" : "PCMU");
    return PJ_SUCCESS;

on_error:
    if (live_audio_tx.mic_recorder) {
        pjsip_audio_capture_close(live_audio_tx.mic_recorder);
        live_audio_tx.mic_recorder = NULL;
    }
    if (live_audio_rx.player) {
        stop_live_audio_playback();
    }
    if (media_started) {
        pjmedia_transport_media_stop(live_media_transport);
    }
    if (tp_attached) {
        pjmedia_transport_detach(live_media_transport, &live_audio_tx);
    }
    live_audio_tx.media_ready = PJ_FALSE;
    live_audio_rx.media_ready = PJ_FALSE;
    return status;
}

//把一帧 PCM 编成 RTP 发出去
pj_status_t send_live_audio_frame(void)
{
    const void *rtphdr = NULL;
    int hdrlen = 0;
    unsigned read_len;
    pj_status_t status;

    if (!live_audio_tx.media_ready || !live_media_transport) {
        return PJ_EINVALIDOP;
    }

    pj_bzero(live_audio_pcm_buf, sizeof(live_audio_pcm_buf));
    read_len = cbuf_read(&live_audio_tx.mic_cbuf,
                         live_audio_pcm_buf,
                         LIVE_SIP_AUDIO_FRAME_BYTES);
    if (read_len < LIVE_SIP_AUDIO_FRAME_BYTES) {
        ++live_audio_tx.mic_underrun_cnt;
        live_audio_log_buffer_event("mic_underrun", live_audio_tx.mic_underrun_cnt);
    }

    if (live_audio_tx.use_alaw) {
        pjmedia_alaw_encode(live_audio_payload_buf, live_audio_pcm_buf,
                            LIVE_SIP_AUDIO_SPF);
    } else {
        pjmedia_ulaw_encode(live_audio_payload_buf, live_audio_pcm_buf,
                            LIVE_SIP_AUDIO_SPF);
    }

    // * Create the RTP header based on arguments and current state of the RTP session.
    status = pjmedia_rtp_encode_rtp(&live_audio_tx.rtp,
                                    live_audio_tx.payload_type,
                                    live_audio_tx.frames_sent == 0,
                                    LIVE_SIP_AUDIO_SPF,
                                    LIVE_SIP_AUDIO_SPF,
                                    &rtphdr,
                                    &hdrlen);
    if (status != PJ_SUCCESS) {
        return status;
    }

    //拼包
    pj_memcpy(live_audio_packet_buf, rtphdr, hdrlen);
    pj_memcpy(live_audio_packet_buf + hdrlen, live_audio_payload_buf,
              sizeof(live_audio_payload_buf));

    //发包
    //printf("%s======%d\n", __func__, __LINE__);
    status = pjmedia_transport_send_rtp(live_media_transport,
                                        live_audio_packet_buf,
                                        hdrlen + sizeof(live_audio_payload_buf));
    if (status != PJ_SUCCESS) {
        return status;
    }

    if (live_audio_tx.frames_sent == 0) {
        log_info("live_audio: tx started");
    }

    ++live_audio_tx.frames_sent;

    return PJ_SUCCESS;
}

//初始化pjmedia endpoint
pj_status_t init_pjmedia(void)
{
    pj_status_t status;

    status = pjmedia_endpt_create2(&cp.factory, NULL, 1, &med_endpt);
    if (status != PJ_SUCCESS) {
        log_error("pjmedia_endpt_create failed: %d", status);
        return status;
    }
    return PJ_SUCCESS;
}

pj_status_t test_basic_media(void)
{
    pj_status_t status;
    pjmedia_transport_info info;
    pjmedia_transport *transport = NULL;

    status = pjmedia_transport_udp_create(med_endpt, NULL, RTP_PORT, 0, &transport);
    if (status != PJ_SUCCESS) {
        log_pj_status("pjmedia_transport_udp_create", status);
        return status;
    }

    pjmedia_transport_info_init(&info);
    pjmedia_transport_get_info(transport, &info);

    log_debug("basic_media: rtp_sock=%d, rtcp_sock=%d",
              info.sock_info.rtp_sock, info.sock_info.rtcp_sock);

    pjmedia_transport_close(transport);
    return PJ_SUCCESS;
}

//创建本端SDP offer
pj_status_t create_live_offer_sdp(pj_pool_t *sdp_pool,
                                  pjmedia_transport *media_tp,
                                  pjmedia_sdp_session **p_sdp)
{
    static const pj_str_t STR_AUDIO = { "audio", 5 };
    static const pj_str_t STR_IN_LOCAL = { "IN", 2 };
    static const pj_str_t STR_IP4_LOCAL = { "IP4", 3 };
    static const pj_str_t STR_IP6_LOCAL = { "IP6", 3 };
    static const pj_str_t STR_RTP_AVP = { "RTP/AVP", 7 };
    pjmedia_transport_info tpinfo;
    pjmedia_sdp_session *sdp;
    pjmedia_sdp_media *media;
    pjmedia_sdp_conn *conn;
    pjmedia_sdp_attr *attr;
    pjmedia_sdp_rtpmap rtpmap;
    pj_status_t status;
    char rtp_addr[64];
    char fmt_buf[16];
    pj_str_t ptime_value;
    pj_str_t fmtp_value;

    PJ_ASSERT_RETURN(sdp_pool && media_tp && p_sdp, PJ_EINVAL);

    status = pjmedia_transport_media_create(media_tp, sdp_pool, 0, NULL, 0);
    if (status != PJ_SUCCESS) {
        log_pj_status("pjmedia_transport_media_create", status);
        return status;
    }

    pjmedia_transport_info_init(&tpinfo);
    pjmedia_transport_get_info(media_tp, &tpinfo);

    pj_sockaddr_print(&tpinfo.sock_info.rtp_addr_name, rtp_addr, sizeof(rtp_addr), 0);
    log_debug("live_sip: media_offer rtp=%s rtp_sock=%d rtcp_sock=%d",
              rtp_addr,
              tpinfo.sock_info.rtp_sock,
              tpinfo.sock_info.rtcp_sock);

    status = pjmedia_endpt_create_base_sdp(med_endpt, sdp_pool, NULL,
                                           &tpinfo.sock_info.rtp_addr_name, &sdp);
    if (status != PJ_SUCCESS) {
        log_pj_status("pjmedia_endpt_create_base_sdp", status);
        return status;
    }

    media = PJ_POOL_ZALLOC_T(sdp_pool, pjmedia_sdp_media);
    media->desc.media = STR_AUDIO;
    media->conn = PJ_POOL_ZALLOC_T(sdp_pool, pjmedia_sdp_conn);
    conn = media->conn;
    conn->net_type = STR_IN_LOCAL;
    if (tpinfo.sock_info.rtp_addr_name.addr.sa_family == pj_AF_INET6()) {
        conn->addr_type = STR_IP6_LOCAL;
    } else {
        conn->addr_type = STR_IP4_LOCAL;
    }
    pj_strdup2(sdp_pool, &conn->addr, rtp_addr);
    media->desc.port =
        (pj_uint16_t)pj_sockaddr_get_port(&tpinfo.sock_info.rtp_addr_name);
    media->desc.port_count = 1;
    media->desc.transport = STR_RTP_AVP;
    media->desc.fmt_count = 3;
    media->desc.fmt[0] = pj_str("8");
    media->desc.fmt[1] = pj_str("0");
    media->desc.fmt[2] = pj_str("101");  //支持8 0 101. m=audio <port> RTP/AVP 8 0 101

    attr = pjmedia_sdp_attr_create(sdp_pool, "sendrecv", NULL);
    media->attr[media->attr_count++] = attr;
    pj_cstr(&ptime_value, "20");
    attr = pjmedia_sdp_attr_create(sdp_pool, "ptime", &ptime_value);
    media->attr[media->attr_count++] = attr;
    attr = pjmedia_sdp_attr_create_rtcp(sdp_pool, &tpinfo.sock_info.rtcp_addr_name);
    media->attr[media->attr_count++] = attr;

    pj_bzero(&rtpmap, sizeof(rtpmap));
    pj_ansi_snprintf(fmt_buf, sizeof(fmt_buf), "%d", 8);
    pj_cstr(&rtpmap.pt, fmt_buf);
    rtpmap.enc_name = pj_str("PCMA");
    rtpmap.clock_rate = 16000;//8000;
    rtpmap.param = pj_str("1");
    status = pjmedia_sdp_rtpmap_to_attr(sdp_pool, &rtpmap, &attr);
    if (status != PJ_SUCCESS) {
        log_pj_status("pjmedia_sdp_rtpmap_to_attr(PCMA)", status);
        return status;
    }
    media->attr[media->attr_count++] = attr;

    pj_bzero(&rtpmap, sizeof(rtpmap));
    pj_ansi_snprintf(fmt_buf, sizeof(fmt_buf), "%d", 0);
    pj_cstr(&rtpmap.pt, fmt_buf);
    rtpmap.enc_name = pj_str("PCMU");
    rtpmap.clock_rate = 8000;
    rtpmap.param = pj_str("1");
    status = pjmedia_sdp_rtpmap_to_attr(sdp_pool, &rtpmap, &attr);
    if (status != PJ_SUCCESS) {
        log_pj_status("pjmedia_sdp_rtpmap_to_attr(PCMU)", status);
        return status;
    }
    media->attr[media->attr_count++] = attr;

    pj_bzero(&rtpmap, sizeof(rtpmap));
    pj_ansi_snprintf(fmt_buf, sizeof(fmt_buf), "%d", 101);
    pj_cstr(&rtpmap.pt, fmt_buf);
    rtpmap.enc_name = pj_str("telephone-event");
    rtpmap.clock_rate = 8000;
    rtpmap.param = pj_str("1");
    status = pjmedia_sdp_rtpmap_to_attr(sdp_pool, &rtpmap, &attr);
    if (status != PJ_SUCCESS) {
        log_pj_status("pjmedia_sdp_rtpmap_to_attr(telephone-event)", status);
        return status;
    }
    media->attr[media->attr_count++] = attr;

    pj_cstr(&fmtp_value, "101 0-15");
    attr = pjmedia_sdp_attr_create(sdp_pool, "fmtp", &fmtp_value);
    media->attr[media->attr_count++] = attr;

    sdp->media[sdp->media_count++] = media;

    status = pjmedia_transport_encode_sdp(media_tp, sdp_pool, sdp, NULL, 0);
    if (status != PJ_SUCCESS) {
        log_pj_status("pjmedia_transport_encode_sdp", status);
        return status;
    }

    *p_sdp = sdp;
    return PJ_SUCCESS;
}

//创建通话用的RTP transport
pj_status_t create_live_media_transport(const char *local_ip,
                                        pjmedia_transport **p_media_tp)
{
    pj_status_t status = PJ_EUNKNOWN;
    int attempt;
    int port;
    pj_str_t local_addr;

    PJ_ASSERT_RETURN(local_ip && *local_ip && p_media_tp, PJ_EINVAL);

    pj_cstr(&local_addr, local_ip);

    for (attempt = 0; attempt < LIVE_RTP_PORT_RETRY; ++attempt) {
        port = LIVE_RTP_PORT_BASE + (attempt * 2);
        status = pjmedia_transport_udp_create2(med_endpt, NULL, &local_addr,  //绑定本地ip，创建transport
                                               port, 0, p_media_tp);          //底层为创建udp sock,
        //即sock_reg/sock_bind for wl83
        if (status == PJ_SUCCESS) {
            log_debug("live_sip: media_transport ip=%s local_port=%d",
                      local_ip, port);
            return PJ_SUCCESS;
        }

        log_info("[WARN] live_sip: media_transport retry %d/%d port=%d status=%d os=%d",
                 attempt + 1,
                 LIVE_RTP_PORT_RETRY,
                 port,
                 status,
                 (status >= PJ_ERRNO_START_SYS && status < PJ_ERRNO_START_USER) ?
                 PJ_STATUS_TO_OS(status) : -1);
    }

    return status;
}

#endif

