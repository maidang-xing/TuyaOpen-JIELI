#include "lwip/sockets.h"
#include "lwip.h"
#include "sock_api/sock_api.h"
#include "app_msg.h"
#include "cdp_client.h"
#include "wifi/online_manager.h"
#include "action.h"
#include "wifi_raw.h"
#include "app_config.h"

#define LOG_TAG_CONST       ONLINE_MANAGER
#define LOG_TAG             "[ONLINE_MANAGER]"
#define LOG_ERROR_ENABLE
#define LOG_INFO_ENABLE
#define LOG_DUMP_ENABLE
#include "debug.h"

#define ONLINE_BROADCAST_TASK_NAME    "online_broadcast_task"
#define ONLINE_RECV_TASK_NAME         "online_recv_task"

#define ONLINE_BROADCAST_ADDR              "238.238.238.238"
#define ONLINE_BROADCAST_PORT               12345
#define ONLINE_PKG_MAGIC                    0xA5A5A5A5

#define DEVICE_TIMEOUT_MS                   5 * 1000
#define CLEANUP_INTERVAL_MS                 1 * 1000

struct online_pkg {
    u32 magic;
    u32 active_cnt;
    char rssi;
};

struct online_task_manager {
    int broadcast_task_pid;
    int broadcast_task_exit;
    u32 broadcast_active_cnt;
    int recv_task_pid;
    int recv_task_exit;
};

struct online_device_manager {
    struct list_head device_list;   // 在线设备链表
    int device_count;               // 在线设备数量
    OS_MUTEX mutex;                    // 互斥锁
    u16 cleanup_timer_id;           // 清理定时器ID
};

struct online_handler {
    struct online_task_manager task_mgr;
    struct online_device_manager device_mgr;
};

static struct online_handler g_online_hdl;

static int online_broadcast_task_create(void);
static int online_recv_task_create(void);
static void online_broadcast_task(void *priv);
static void online_recv_task(void *priv);
static int online_app_init(void);
static void online_app_exit(void);
static int sock_cb(enum sock_api_msg_type type, void *priv);
static void online_broadcast_task_destroy(void);
static void online_recv_task_destroy(void);
static void online_manager_cleanup_timeout(void *priv);
static int online_manager_add_device(u32 ip_addr, u32 active_cnt);
static online_device_t *alloc_device_node(u32 ip_addr, u32 active_cnt);
static void free_device_node(online_device_t *dev);
static void ip_to_string(u32 ip, char *str);
static int online_task_init(void);
static void online_task_exit(void);
static void adjust_tx_power_based_on_rssi(char rssi);

int online_manager_init(void)
{
    int ret = 0;
    struct online_handler *hdl = &g_online_hdl;
    struct online_device_manager *device_mgr = &hdl->device_mgr;
    memset(device_mgr, 0, sizeof(struct online_device_manager));

    INIT_LIST_HEAD(&device_mgr->device_list);
    os_mutex_create(&device_mgr->mutex);

    device_mgr->cleanup_timer_id = sys_timer_add(NULL, online_manager_cleanup_timeout, CLEANUP_INTERVAL_MS);
    if (device_mgr->cleanup_timer_id == 0) {
        log_error("Failed to start cleanup timer\n");
        os_mutex_del(&device_mgr->mutex, 0);
        return -1;
    }

    ret = online_task_init();
    if (ret != 0) {
        sys_timer_del(device_mgr->cleanup_timer_id);
        os_mutex_del(&device_mgr->mutex, OS_DEL_ALWAYS);
        return -1;
    }

    return 0;
}

void online_manager_exit(void)
{
    struct online_handler *hdl = &g_online_hdl;
    struct online_device_manager *device_mgr = &hdl->device_mgr;

    online_task_exit();

    if (device_mgr->cleanup_timer_id != 0) {
        sys_timer_del(device_mgr->cleanup_timer_id);
        device_mgr->cleanup_timer_id = 0;
    }

    os_mutex_pend(&device_mgr->mutex, 0);

    online_device_t *dev, *tmp;
    list_for_each_entry_safe(dev, tmp, &device_mgr->device_list, entry) {
        free_device_node(dev);
    }

    os_mutex_post(&device_mgr->mutex);
    os_mutex_del(&device_mgr->mutex, OS_DEL_ALWAYS);
}

static int dev_online_notify_action(online_device_t *dev)
{
    struct intent it;
    init_intent(&it);

    int ret;
    it.name	= "video_call";
    it.data = (void *)dev;
    it.action = ACTION_VIDEO_CALL_DEV_ONLINE;
    ret = start_app_async(&it, NULL, NULL);

    if (ret != 0) {
        log_error("video call dev online action start app fail :%d \n", ret);
        return -1;
    }

    return 0;
}

static void offline_free_device_cb(void *p, int err)
{
    log_info("offline free device cb \n");
    struct online_handler *hdl = &g_online_hdl;
    struct online_device_manager *device_mgr = &hdl->device_mgr;
    online_device_t *dev = (online_device_t *)p;
    free_device_node(dev);
    device_mgr->device_count--;
}

static int dev_offline_notify_action(online_device_t *dev)
{
    struct intent it;
    init_intent(&it);

    int ret;
    it.name	= "video_call";
    it.data = (void *)dev;
    it.action = ACTION_VIDEO_CALL_DEV_OFFLINE;
    ret = start_app_async(&it, offline_free_device_cb, dev);
    if (ret != 0) {
        log_error("video call dev offline action start app fail :%d \n", ret);
        return -1;
    }

    return 0;
}


static void online_manager_cleanup_timeout(void *priv)
{
    struct online_handler *hdl = &g_online_hdl;
    struct online_device_manager *device_mgr = &hdl->device_mgr;
    os_mutex_pend(&device_mgr->mutex, 0);

    u32 current_time = timer_get_ms();

    online_device_t *dev, *tmp;
    list_for_each_entry_safe(dev, tmp, &device_mgr->device_list, entry) {
        u32 elapsed = current_time - dev->last_seen_time;
        if (elapsed > DEVICE_TIMEOUT_MS) {
            log_info("Device timeout removed: %s, elapsed=%u ms\n", dev->ip_str, elapsed);
            //TODO 失败处理
            dev_offline_notify_action(dev);
        }
    }
    os_mutex_post(&device_mgr->mutex);
}

static int online_manager_add_device(u32 ip_addr, u32 active_cnt)
{
    struct online_handler *hdl = &g_online_hdl;
    struct online_device_manager *device_mgr = &hdl->device_mgr;

    os_mutex_pend(&device_mgr->mutex, 0);

    online_device_t *dev = NULL;
    list_for_each_entry(dev, &device_mgr->device_list, entry) {
        if (dev->ip_addr == ip_addr) {
            dev->active_cnt = active_cnt;
            dev->last_seen_time = timer_get_ms();
            dev->status = DEVICE_STATUS_ONLINE;
            os_mutex_post(&device_mgr->mutex);
            return 0;
        }
    }

    // 添加新设备
    dev = alloc_device_node(ip_addr, active_cnt);
    if (!dev) {
        os_mutex_post(&device_mgr->mutex);
        return -1;
    }

    dev_online_notify_action(dev);

    list_add_tail(&dev->entry, &device_mgr->device_list);
    device_mgr->device_count++;

    log_info("Device added: %s, count=%d\n", dev->ip_str, device_mgr->device_count);

    os_mutex_post(&device_mgr->mutex);
    return 0;
}

static online_device_t *alloc_device_node(u32 ip_addr, u32 active_cnt)
{
    online_device_t *dev = (online_device_t *)malloc(sizeof(online_device_t));
    if (!dev) {
        log_error("Failed to alloc device node\n");
        return NULL;
    }

    memset(dev, 0, sizeof(online_device_t));
    dev->ip_addr = ip_addr;
    dev->active_cnt = active_cnt;
    dev->last_seen_time = timer_get_ms();
    dev->status = DEVICE_STATUS_ONLINE;
    ip_to_string(ip_addr, dev->ip_str);

    dev->cdp_hdl = cdp_cli_reg(ip_addr, NULL);
    if (!dev->cdp_hdl) {
        log_error("Failed to register cdp client for device: %s\n", dev->ip_str);
        free(dev);
        return NULL;
    }

    INIT_LIST_HEAD(&dev->entry);

    return dev;
}

static void free_device_node(online_device_t *dev)
{
    if (dev) {
        list_del(&dev->entry);
        if (dev->cdp_hdl) {
            cdp_cli_unreg(dev->cdp_hdl);
            dev->cdp_hdl = NULL;
        }
        free(dev);
    }
}

static void ip_to_string(u32 ip, char *str)
{
    sprintf(str, "%d.%d.%d.%d",
            (ip >> 0) & 0xFF,
            (ip >> 8) & 0xFF,
            (ip >> 16) & 0xFF,
            (ip >> 24) & 0xFF);
}

static int online_task_init(void)
{
    int ret = 0;
    struct online_handler *hdl = &g_online_hdl;
    struct online_task_manager *task_mgr = &hdl->task_mgr;
    memset(task_mgr, 0, sizeof(struct online_task_manager));
    // 创建广播线程
    ret = online_broadcast_task_create();
    if (ret != 0) {
        log_error("wifi raw broadcast task create err:%d \n", ret);
        return -1;
    }
    // 创建接收线程
    ret = online_recv_task_create();
    if (ret != 0) {
        log_error("wifi raw recv task create err:%d \n", ret);
        return -1;
    }
    return 0;
}

static void online_task_exit(void)
{
    //销毁广播线程
    online_broadcast_task_destroy();
    //销毁接收线程
    online_recv_task_destroy();
}

static int online_broadcast_task_create(void)
{
    struct online_handler *hdl = &g_online_hdl;
    struct online_task_manager *task_mgr = &hdl->task_mgr;
    task_mgr->broadcast_task_exit = 0;
    return thread_fork(ONLINE_BROADCAST_TASK_NAME, 15, 2048, 2048, &task_mgr->broadcast_task_pid, online_broadcast_task, task_mgr);
}
static int online_recv_task_create(void)
{
    struct online_handler *hdl = &g_online_hdl;
    struct online_task_manager *task_mgr = &hdl->task_mgr;
    return thread_fork(ONLINE_RECV_TASK_NAME, 15, 2048, 2048, &task_mgr->recv_task_pid, online_recv_task, task_mgr);
}

static void online_broadcast_task_destroy(void)
{
    struct online_handler *hdl = &g_online_hdl;
    struct online_task_manager *task_mgr = &hdl->task_mgr;
    task_mgr->broadcast_task_exit = 1;
    thread_kill(&task_mgr->broadcast_task_pid, KILL_WAIT);
    task_mgr->broadcast_task_exit = 0;
}
static void online_recv_task_destroy(void)
{
    struct online_handler *hdl = &g_online_hdl;
    struct online_task_manager *task_mgr = &hdl->task_mgr;
    task_mgr->recv_task_exit = 1;
    thread_kill(&task_mgr->recv_task_pid, KILL_WAIT);
    task_mgr->recv_task_exit = 0;
}

static void online_broadcast_task(void *priv)
{
    log_debug("wifi raw broadcast task start \n");
    struct online_task_manager *task_mgr = (struct online_task_manager *)priv;
    void *sockfd;
    sockfd = sock_reg(AF_INET, SOCK_DGRAM, 0, sock_cb, &task_mgr->broadcast_task_exit);
    if (sockfd == NULL) {
        log_error(" wifi raw broadcast sock reg err \n");
        return;
    }
    struct sockaddr_in dest_addr;
    dest_addr.sin_family = AF_INET;
    dest_addr.sin_addr.s_addr = inet_addr(ONLINE_BROADCAST_ADDR);
    dest_addr.sin_port = htons(ONLINE_BROADCAST_PORT);

    struct online_pkg online_pkg;
    while (!task_mgr->broadcast_task_exit) {
        online_pkg.magic = ONLINE_PKG_MAGIC;
        online_pkg.active_cnt = task_mgr->broadcast_active_cnt++;
        online_pkg.rssi = wifi_raw_rssi_get();
        int ret = sock_sendto(sockfd, (char *)&online_pkg, sizeof(online_pkg), 0, (struct sockaddr *)&dest_addr, sizeof(dest_addr));
        if (ret <= 0) {
            log_error(" wifi raw broadcast sock sendto err :%d \n", ret);
        }

        os_time_dly(50);
    }
    log_debug("wifi raw broadcast task exit \n");
}

static void online_recv_task(void *priv)
{
    log_debug("wifi raw recv task start \n");
    struct online_task_manager *task_mgr = (struct online_task_manager *)priv;
    void *sockfd;
    sockfd = sock_reg(AF_INET, SOCK_DGRAM, 0, sock_cb, &task_mgr->recv_task_exit);
    if (sockfd == NULL) {
        log_error(" wifi raw recv sock reg err \n");
        return;
    }
    struct sockaddr_in recv_addr;
    recv_addr.sin_family = AF_INET;
    recv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    recv_addr.sin_port = htons(ONLINE_BROADCAST_PORT);
    int ret = sock_bind(sockfd, (struct sockaddr *)&recv_addr, sizeof(struct sockaddr));
    if (ret) {
        log_error(" wifi raw recv sock bind err :%d \n", ret);
        sock_unreg(sockfd);
        return;
    }
    struct ip_mreq mreq;
    mreq.imr_multiaddr.s_addr = inet_addr(ONLINE_BROADCAST_ADDR);
    mreq.imr_interface.s_addr = htonl(INADDR_ANY);
    ret = sock_setsockopt(sockfd, IPPROTO_IP, IP_ADD_MEMBERSHIP, &mreq, sizeof(mreq));
    if (ret) {
        log_error(" wifi raw recv sock setsockopt err :%d \n", ret);
        sock_unreg(sockfd);
        return;
    }

    struct online_pkg online_pkg;
    struct sockaddr_in src_addr;
    socklen_t addrlen = sizeof(src_addr);

    while (!task_mgr->recv_task_exit) {
        int recv_len = sock_recvfrom(sockfd, (char *)&online_pkg, sizeof(online_pkg), 0, (struct sockaddr *)&src_addr, &addrlen);
        if (recv_len <= 0) {
            log_error(" wifi raw recv sock recvfrom err :%d \n", recv_len);
            continue;
        }
        if (recv_len != sizeof(online_pkg)) {
            log_error(" wifi raw recv sock recvfrom len err :%d \n", recv_len);
            continue;
        }
        if (online_pkg.magic != ONLINE_PKG_MAGIC) {
            log_error(" wifi raw recv sock recvfrom magic err :%x \n", online_pkg.magic);
            continue;
        }
        log_debug(" online recv ip:%s active_cnt:%d \n", inet_ntoa(src_addr.sin_addr), online_pkg.active_cnt);

        online_manager_add_device(src_addr.sin_addr.s_addr, online_pkg.active_cnt);

        //根据对端的RSSI值，调整本地的发送功率
        adjust_tx_power_based_on_rssi(online_pkg.rssi);
    }
    log_debug("wifi raw recv task exit \n");
}

static void adjust_tx_power_based_on_rssi(char rssi)
{
    const char rssi_high_threshold = -20; // RSSI高阈值
    const char rssi_low_threshold = -40;  // RSSI低阈值
    const u8 tx_power_step = 1;           // 每次调整的功率

    u8 current_tx_power = wifi_raw_get_pwr();
    if (rssi > rssi_high_threshold) {
        // RSSI较高，降低发送功率
        if (current_tx_power > WIFI_MIN_PWR) {
            current_tx_power -= tx_power_step;
            wifi_raw_set_pwr(current_tx_power);
            log_debug("Decreased TX power to %d due to high RSSI %d\n", current_tx_power, rssi);
        }
    } else if (rssi < rssi_low_threshold) {
        // RSSI较低，增加发送功率
        if (current_tx_power < WIFI_MAX_PWR) {
            current_tx_power += tx_power_step;
            wifi_raw_set_pwr(current_tx_power);
            log_debug("Increased TX power to %d due to low RSSI %d\n", current_tx_power, rssi);
        }
    }
}

static int sock_cb(enum sock_api_msg_type type, void *priv)
{
    int *exit_flag = priv;
    if (*exit_flag) {
        log_debug("wifi raw sock cb func exit \n");
        return -1;
    }
    return 0;
}


