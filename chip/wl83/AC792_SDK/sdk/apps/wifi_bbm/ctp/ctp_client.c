#include "ctp_client.h"
#include "server/ctp_server.h"
#include "sock_api/sock_api.h"
#include "json_c/json.h"
#include "json_c/json_tokener.h"
#include "action.h"

#define LOG_TAG_CONST       CTP_CLIENT
#define LOG_TAG             "[CTP_CLIENT]"
#define LOG_ERROR_ENABLE
#define LOG_INFO_ENABLE
#define LOG_DUMP_ENABLE
#include "debug.h"

#define CTP_CMD_PORT            3333    //CTP命令端口

struct ctp_client_handler {
    void *ctp_cli_hdl;
    void *priv;
    OS_SEM sync_sem;
    char sync_topic[64];
};

static int ctp_client_recv_callback(void *hdl, enum ctp_cli_msg_type type,
                                    const char *topic, const char *content, void *priv);


int ctp_client_init(void **client_hdl, u32 ip_addr, void *priv)
{
    int ret;
    struct sockaddr_in dest_addr = {0};
    static u32 client_id = 1;

    struct ctp_client_handler *hdl = malloc(sizeof(struct ctp_client_handler));
    if (!hdl) {
        log_error("ctp client hdl alloc err \n");
        return -1;
    }

    dest_addr.sin_family = AF_INET;
    dest_addr.sin_addr.s_addr = ip_addr;
    dest_addr.sin_port = htons(CTP_CMD_PORT);

    os_sem_create(&hdl->sync_sem, 0);
    hdl->priv = priv;

    hdl->ctp_cli_hdl = ctp_cli_reg(client_id++, &dest_addr, ctp_client_recv_callback, hdl);
    if (hdl->ctp_cli_hdl == NULL) {
        log_error("ctp client reg err \n");
        goto err;
    }

    *client_hdl = (void *)hdl;

    return 0;

err:
    if (hdl) {
        os_sem_del(&hdl->sync_sem, OS_DEL_ALWAYS);
        free(hdl);
    }
    *client_hdl = NULL;
    return -1;
}

void ctp_client_exit(void *client_hdl)
{
    struct ctp_client_handler *hdl = (struct ctp_client_handler *)client_hdl;
    if (!hdl) {
        return;
    }

    if (hdl->ctp_cli_hdl) {
        ctp_cli_unreg(hdl->ctp_cli_hdl);
        hdl->ctp_cli_hdl = NULL;
    }

    os_sem_del(&hdl->sync_sem, OS_DEL_ALWAYS);
    free(hdl);
}

int ctp_client_send_sync(void *client_hdl, const char *topic, const char *content, int timeout_ms)
{
    int ret;
    struct ctp_client_handler *hdl = (struct ctp_client_handler *)client_hdl;
    if (!hdl) {
        log_error("ctp client hdl null \n");
        return -1;
    }


    strncpy(hdl->sync_topic, topic, sizeof(hdl->sync_topic) - 1);
    hdl->sync_topic[sizeof(hdl->sync_topic) - 1] = '\0';

    os_sem_set(&hdl->sync_sem, 0);

    ret = ctp_cli_send(hdl->ctp_cli_hdl, topic, content);
    if (ret) {
        log_error("ctp client send err:%d topic:%s\n", ret, topic);
        hdl->sync_topic[0] = '\0';
        return -1;
    }

    if (timeout_ms < 10) {
        timeout_ms = 10;
    }
    int timeout_tick = timeout_ms / 10;
    if (os_sem_pend(&hdl->sync_sem, timeout_tick) != 0) {
        log_error("ctp client sync cmd timeout: %s (waited %dms)\n", topic, timeout_ms);
        hdl->sync_topic[0] = '\0';
        return -1;
    }

    log_debug("ctp client sync success: %s\n", topic);
    return 0;
}

int ctp_client_send_async(void *client_hdl, const char *topic, const char *content)
{
    int ret;
    struct ctp_client_handler *hdl = (struct ctp_client_handler *)client_hdl;
    if (!hdl) {
        log_error("ctp client hdl null \n");
        return -1;
    }
    ret = ctp_cli_send(hdl->ctp_cli_hdl, topic, content);
    if (ret) {
        log_error("ctp client send err:%d topic:%s\n", ret, topic);
        return -1;
    }

    return 0;
}


static int ctp_client_recv_callback(void *hdl, enum ctp_cli_msg_type type,
                                    const char *topic, const char *content, void *priv)
{
    struct ctp_client_handler *client_hdl = (struct ctp_client_handler *)priv;
    if (!client_hdl) {
        log_error("ctp client recv callback: hdl null\n");
        return -1;
    }

    if (type == CTP_CLI_RECV_MSG) {
        log_debug("ctp client recv: topic=%s, content=%s\n", topic, content);
        if (client_hdl->sync_topic[0] != '\0' &&
            strncmp(topic, client_hdl->sync_topic, strlen(client_hdl->sync_topic)) == 0) {
            // 收到期待的响应，释放信号量
            log_debug("ctp client sync response received for topic: %s\n", topic);
            client_hdl->sync_topic[0] = '\0';
            os_sem_post(&client_hdl->sync_sem);
        }
    }

    return 0;
}
