#include "lwip/sockets.h"
#include "lwip.h"
#include "sock_api/sock_api.h"
#include "ctp/ctp.h"
#include "cdp/cdp.h"
#include "cdp_client.h"

#define LOG_TAG_CONST       CDP_CLIENT
#define LOG_TAG             "[CDP_CLIENT]"
#define LOG_ERROR_ENABLE
#define LOG_INFO_ENABLE
#define LOG_DUMP_ENABLE
#include "debug.h"

#define CDP_CMD_PORT            2228    //CDP命令端口

struct cdp_hdl {
    void *sock;
    u32 ip_addr;
    char thread_name[32];
    int thread_pid;
    u8 thread_kill;
    int (*cb_func)(void *hdl, char *topic, char *content, void *priv);
    void *priv;
    u8 *sock_send_buf;
    int sock_send_buf_len;
    u8 *sock_recv_buf;
    int sock_buf_len;
    OS_SEM sync_sem;
    char sync_topic[64];
};

static int thread_name_id = 0;

static void recv_cdp_msg(u8 *recv_buf, int len, struct cdp_hdl *hdl)
{
    if (len < (CDP_PREFIX_LEN + CDP_TOPIC_LEN + CDP_TOPIC_CONTENT_LEN)) {
        return;
    }
    if (strncmp(CDP_PREFIX, (const char *)recv_buf, CDP_PREFIX_LEN)) {
        return;
    }

    u16 cdp_topic_len;
    u32 cdp_ct_len;

    u16 max_topic_len = 512;
    u32 max_content_slice_len = 1024;

    char *topic = malloc(max_topic_len);
    char *topic_ct = malloc(max_content_slice_len);
    if (!topic || !topic_ct) {
        return;
    }

    memcpy((char *)&cdp_topic_len, recv_buf + CDP_PREFIX_LEN, CDP_TOPIC_LEN);
    memcpy((char *)&cdp_ct_len, recv_buf + CDP_PREFIX_LEN + CDP_TOPIC_LEN + cdp_topic_len, CDP_TOPIC_CONTENT_LEN);
    /* printf("\ncdp_topic_len is %d cdp_ct_len is %d\n", cdp_topic_len, cdp_ct_len); */

    if (cdp_topic_len >= max_topic_len || cdp_ct_len >= max_content_slice_len) {
        log_error(">>>cdp_topic_len or cdp_ct_len is too large \n");
    }

    memcpy(topic, recv_buf + CDP_PREFIX_LEN + CDP_TOPIC_LEN, cdp_topic_len);
    topic[cdp_topic_len] = '\0';
    memcpy(topic_ct, recv_buf + CDP_PREFIX_LEN + CDP_TOPIC_LEN + cdp_topic_len + CDP_TOPIC_CONTENT_LEN, cdp_ct_len);
    topic_ct[cdp_ct_len] = '\0';
    /* printf("\n topic is %s topic_ct is %s\n", topic, topic_ct); */

    if (hdl->cb_func) {
        hdl->cb_func((void *)hdl, topic, topic_ct, hdl->priv);
    }

    free(topic);
    free(topic_ct);
}

static void cdp_sock_recv_thread(void *priv)
{
    struct cdp_hdl *hdl = (struct cdp_hdl *)priv;
    int ret = 0;
    log_debug("cdp sock recv thread start \n");

    while (!hdl->thread_kill) {

        ret = sock_recv(hdl->sock, hdl->sock_recv_buf, hdl->sock_buf_len, 0);
        if (ret <= 0) {
            continue;
        }
        log_debug("cdp recv len:%d \n", ret);
        put_buf(hdl->sock_recv_buf, ret);
        recv_cdp_msg(hdl->sock_recv_buf, ret, hdl);
    }

    log_debug("cdp sock recv thread exit \n");
}

static int recv_sock_cb_func(enum sock_api_msg_type type, void *priv)
{
    struct cdp_hdl *hdl = (struct cdp_hdl *)priv;
    if (hdl->thread_kill) {
        log_debug("cb func task exit\n");
        return -1;
    }
    return 0;
}

static void *cdp_sock_create(u32 ip_addr, struct cdp_hdl *hdl)
{
    void *sock = sock_reg(AF_INET, SOCK_DGRAM, 0, recv_sock_cb_func, (void *)hdl);
    if (sock == NULL) {
        log_error("cdp sock reg fail \n");
        return NULL;
    }


    return sock;
}

static int cdp_send(struct cdp_hdl *hdl, const char *topic, const char *content)
{
    if (!topic || !hdl) {
        return -1;
    }

    u16 topic_len = strlen(topic);
    u32 content_len = content ? strlen(content) : 0;

    // 构造数据总长度
    u16 packet_size = CDP_PREFIX_LEN + CDP_TOPIC_LEN  + topic_len
                      + (content ? (CDP_TOPIC_CONTENT_LEN + content_len) : CDP_TOPIC_CONTENT_LEN);
    if (packet_size > hdl->sock_send_buf_len) {
        log_error("cdp send buf too small  need size:%d  \n", packet_size);
        return -1;
    }
    char *packet = (char *)hdl->sock_send_buf;

    char *p = packet;

    // 拷贝 "CDP:"
    memcpy(p, CDP_PREFIX, CDP_PREFIX_LEN);
    p += CDP_PREFIX_LEN;

    // 拷贝 topic 长度（2 字节，网络字节序）
    /* u16 net_topic_len = htons(topic_len); */
    memcpy(p, &topic_len, CDP_TOPIC_LEN);
    p += CDP_TOPIC_LEN;

    // 拷贝 topic
    memcpy(p, topic, topic_len);
    p += topic_len;

    // 拷贝 content 长度（4 字节，网络字节序）
    /* u32 net_content_len = htonl(content_len); */
    memcpy(p, &content_len, CDP_TOPIC_CONTENT_LEN);
    p += CDP_TOPIC_CONTENT_LEN;

    if (content) {
        // 拷贝 content
        memcpy(p, content, content_len);
        p += content_len;
    }

    // 发送数据包
    struct sockaddr_in dest_addr = {0};
    dest_addr.sin_family = AF_INET;
    dest_addr.sin_addr.s_addr = hdl->ip_addr;
    dest_addr.sin_port = htons(CDP_CMD_PORT);

    int sent = sock_sendto(hdl->sock, packet, p - packet, 0,
                           (struct sockaddr *)&dest_addr, sizeof(dest_addr));

    if (!(sent == (p - packet))) {
        log_error("cdp sock send fail \n");
        return -3;
    }

    return 0;
}

static int cdp_msg_func(void *hdl, char *topic, char *content, void *priv)
{
    log_debug("cdp msg recv: topic is %s topic_ct is %s\n", topic, content);

    if (strstr(content, "PUT")) {

    } else if (strstr(content, "GET")) {

    } else if (strstr(content, "NOTIFY")) {
        struct cdp_hdl *_hdl = (struct cdp_hdl *)hdl;
        if (_hdl->sync_topic[0] != '\0' && strncmp(topic, _hdl->sync_topic, strlen(_hdl->sync_topic)) == 0) {
            log_debug("cdp sync topic recv notify: %s\n", topic);
            os_sem_post(&_hdl->sync_sem);
            _hdl->sync_topic[0] = '\0';
        }

    } else {

    }

    return 0;
}


void *cdp_cli_reg(u32 ip_addr,  void *priv)
{
    int ret = 0;
    struct cdp_hdl *hdl = malloc(sizeof(struct cdp_hdl));
    if (!hdl) {
        log_error("cdp hdl malloc fail \n");
        return NULL;
    }
    memset(hdl, 0x00, sizeof(struct cdp_hdl));

    void *sock = cdp_sock_create(ip_addr, hdl);
    if (!sock) {
        log_error("cdp sock create fail \n");
        free(hdl);
        return NULL;
    }

    hdl->sock_buf_len = 1024;
    hdl->sock_recv_buf = malloc(hdl->sock_buf_len);
    if (!hdl->sock_recv_buf) {
        log_error(" cdp recv malloc fail \n");
        sock_unreg(sock);
        free(hdl);
        return NULL;
    }

    hdl->sock_send_buf_len = 512;
    hdl->sock_send_buf = malloc(hdl->sock_send_buf_len);
    if (!hdl->sock_send_buf) {
        log_error(" cdp send malloc fail \n");
        free(hdl->sock_recv_buf);
        sock_unreg(sock);
        free(hdl);
        return NULL;
    }

    snprintf(hdl->thread_name, sizeof(hdl->thread_name), "cdp_sock_recv_thread%d", thread_name_id++);

    ret = thread_fork(hdl->thread_name, 15, 2048, 2048, &hdl->thread_pid, cdp_sock_recv_thread, (void *)hdl);
    if (ret != 0) {
        log_error("cdp recv thread fork fail \n");
        free(hdl->sock_recv_buf);
        sock_unreg(sock);
        free(hdl);
        return NULL;
    }

    hdl->ip_addr = ip_addr;
    hdl->sock = sock;
    hdl->cb_func = cdp_msg_func;
    hdl->priv = priv;
    os_sem_create(&hdl->sync_sem, 0);

    return hdl;
}

void cdp_cli_unreg(void *hdl)
{
    if (!hdl) {
        log_error("cdp hdl null \n");
        return;
    }

    struct cdp_hdl *_hdl = (struct cdp_hdl *)hdl;

    char topic[24] = {"CDP_CLI_DISCONNECT"};
    char content[24] = {"{\"op\":\"PUT\"}"};
    cdp_send(_hdl, topic, content);

    _hdl->thread_kill = 1;
    sock_unreg(_hdl->sock);

    thread_kill(&_hdl->thread_pid, KILL_WAIT);

    free(_hdl->sock_recv_buf);
    free(_hdl->sock_send_buf);
    free(hdl);
}

int cdp_client_send_async(void *hdl, const char *topic, const char *content)
{
    struct cdp_hdl *_hdl = (struct cdp_hdl *)hdl;
    if (!_hdl) {
        log_error("cdp hdl null \n");
        return -1;
    }

    return cdp_send(_hdl, topic, content);
}


int cdp_client_send_sync(void *hdl, const char *topic, const char *content, int timeout_ms)
{
    int ret;
    struct cdp_hdl *_hdl = (struct cdp_hdl *)hdl;
    if (!_hdl) {
        log_error("cdp hdl null \n");
        return -1;
    }
    strncpy(_hdl->sync_topic, topic, sizeof(_hdl->sync_topic) - 1);
    _hdl->sync_topic[sizeof(_hdl->sync_topic) - 1] = '\0';

    ret = cdp_send(hdl, topic, content);
    if (ret != 0) {
        log_error("cdp client send async err:%d topic:%s\n", ret, topic);
        return -1;
    }

    if (timeout_ms < 10) {
        timeout_ms = 10;
    }
    int timeout_tick = timeout_ms / 10;

    if (os_sem_pend(&_hdl->sync_sem, timeout_tick) != 0) {
        log_error("cdp client sync cmd timeout: %s (waited %dms)\n", topic, timeout_ms);
        _hdl->sync_topic[0] = '\0';
        return -1;
    }

    log_debug("cdp client sync success: %s\n", topic);

    return 0;
}

