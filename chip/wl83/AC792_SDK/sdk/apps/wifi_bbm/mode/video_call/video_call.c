#include "system/includes.h"
#include "app_config.h"
#include "action.h"
#include "event/key_event.h"
#include "event/device_event.h"
#include "event/net_event.h"
#include "ctp_server.h"
#include "app_msg.h"
#include "online_manager.h"
#include "wifi_raw.h"
#include "wifi_ap_sta.h"
#include "video_stream_send.h"
#include "video_stream_recv.h"
#include "multi_media_renderer.h"
#include "ctp_cmd_handle.h"
#include "ctp_client.h"
#include "video_stream_common.h"
#include "video_window_manager.h"
#include "wifi/wifi_connect.h"

#define LOG_TAG_CONST       VIDEO_CALL
#define LOG_TAG             "[VIDEO_CALL]"
#define LOG_ERROR_ENABLE
#define LOG_INFO_ENABLE
#define LOG_DUMP_ENABLE
#include "debug.h"

enum {
    WIFI_RAW_MODE,
    WIFI_AP_STA_MODE,
};

struct video_call_handler {
    struct video_stream_send_hdl *stream_send;
    struct video_stream_recv_hdl *stream_recv;
    struct multi_media_renderer *renderer;
    char net_path[32];

    struct list_head device_list;
    int online_ip_count;

    int render_table[10];
    int render_count;
    int render_layout_mode;
    int recv_stream_count;

    int wifi_mode;
};
struct video_call_handler g_video_call_hdl = {0};

static struct video_stream_info default_stream_info = {
    .img_width = STREAM_VIDEO_WIDTH,
    .img_height = STREAM_VIDEO_HEIGHT,
    .fps = STREAM_VIDEO_FPS,
    .bitrate_kbps = STREAM_VIDEO_ABR_KBPS,
    .device_id = STREAM_VIDEO_DEVICE,
    .online = STREAM_VIDEO_ONLINE,
    .osd_enable = STREAM_VIDEO_OSD_ENABLE,
    .audio_enable = STREAM_AUDIO_ENABLE,
    .sample_rate = STREAM_AUDIO_SAMPLE_RATE,
    .channel = STREAM_AUDIO_CHANNEL,
    .volume = STREAM_AUDIO_VOLUME,
    .aud_interval_size = STREAM_AUDIO_INTERVAL_SIZE,
};

static void video_call_add_stream_device_cb(u32 ip_addr);
static void video_call_del_stream_device_cb(u32 ip_addr);
static int video_call_is_render_device(u32 ip_addr);


static int video_call_wifi_raw_init(void)
{
    INIT_LIST_HEAD(&g_video_call_hdl.device_list);

    wifi_raw_init();
    ctp_init(0);
    online_manager_init();
    g_video_call_hdl.wifi_mode = WIFI_RAW_MODE;
    return 0;
}
static void video_call_wifi_raw_exit(void)
{
    online_manager_exit();
    ctp_exit();
    wifi_raw_exit();
}

static int video_call_wifi_init(void)
{
    wifi_ap_init();
    ctp_init(0);
    g_video_call_hdl.wifi_mode = WIFI_AP_STA_MODE;
}

static int video_call_open_stream_send(void)
{
    int ret = 0;

    if (g_video_call_hdl.stream_send) {
        log_info("video call stream send already started \n");
        return 0;
    }

    snprintf(g_video_call_hdl.net_path, sizeof(g_video_call_hdl.net_path),
             "udp://%s:%d", VIDEO_STREAM_BROADCAST_ADDR, VIDEO_STREAM_BROADCAST_PORT);
    ret = video_stream_send_create(&g_video_call_hdl.stream_send);
    if (ret != 0) {
        log_error("video stream send create err \n");
        return -1;
    }
    ret = video_stream_send_init(g_video_call_hdl.stream_send, &default_stream_info, g_video_call_hdl.net_path);
    if (ret != 0) {
        log_error("video stream send init err \n");
        video_stream_send_destroy(&g_video_call_hdl.stream_send);
        return -1;
    }
    ret = video_stream_send_start(g_video_call_hdl.stream_send);
    if (ret != 0) {
        log_error("video stream send start err \n");
        video_stream_send_destroy(&g_video_call_hdl.stream_send);
        return -1;
    }

    log_info("video stream send opened successfully\n");
    return 0;
}

static int video_call_open_stream_recv(void)
{
    int ret = 0;

    if (g_video_call_hdl.stream_recv) {
        log_info("video call stream recv already started \n");
        return 0;
    }

    snprintf(g_video_call_hdl.net_path, sizeof(g_video_call_hdl.net_path),
             "%s:%d", VIDEO_STREAM_BROADCAST_ADDR, VIDEO_STREAM_BROADCAST_PORT);
    ret = video_stream_recv_create(&g_video_call_hdl.stream_recv);
    if (ret != 0) {
        log_error("video stream recv create err \n");
        return -1;
    }
    ret = video_stream_recv_init(g_video_call_hdl.stream_recv, g_video_call_hdl.net_path);
    if (ret != 0) {
        log_error("video stream recv init err \n");
        video_stream_recv_destroy(&g_video_call_hdl.stream_recv);
        return -1;
    }
    //注册接收设备添加删除回调
    video_stream_recv_set_dev_notify(g_video_call_hdl.stream_recv, video_call_add_stream_device_cb, video_call_del_stream_device_cb);

    ret = video_stream_recv_start(g_video_call_hdl.stream_recv);
    if (ret != 0) {
        log_error("video stream recv start err \n");
        video_stream_recv_destroy(&g_video_call_hdl.stream_recv);
        return -1;
    }

    log_info("video stream recv opened successfully\n");
    return 0;
}

static int video_call_open_stream_render(void)
{
    int ret = 0;

    if (g_video_call_hdl.renderer) {
        log_info("video call renderer already started \n");
        return 0;
    }

    snprintf(g_video_call_hdl.net_path, sizeof(g_video_call_hdl.net_path),
             "%s:%d", VIDEO_STREAM_BROADCAST_ADDR, VIDEO_STREAM_BROADCAST_PORT);
    ret = multi_media_renderer_create(&g_video_call_hdl.renderer);
    if (ret != 0) {
        log_error("multi media renderer create err \n");
        return -1;
    }

    ret = multi_media_renderer_init(g_video_call_hdl.renderer, g_video_call_hdl.net_path);
    if (ret != 0) {
        log_error("multi media renderer init err \n");
        multi_media_renderer_destroy(&g_video_call_hdl.renderer);
        return -1;
    }
    ret = multi_media_renderer_start(g_video_call_hdl.renderer);
    if (ret != 0) {
        log_error("multi media renderer start err \n");
        multi_media_renderer_destroy(&g_video_call_hdl.renderer);
        return -1;
    }

    log_info("multi media renderer opened successfully\n");
    return 0;
}

static int video_call_open_stream_main(int device_num)
{
    int ret = 0;
    ret = video_call_open_stream_send();
    if (ret != 0) {
        return -1;
    }
    ret = video_call_open_stream_recv();
    if (ret != 0) {
        return -1;
    }
    ret = video_call_open_stream_render();
    if (ret != 0) {
        return -1;
    }

    video_window_manager_init();
    if (g_video_call_hdl.render_layout_mode != device_num) {
        g_video_call_hdl.render_layout_mode = device_num;
        video_window_manager_update_layout_mode(g_video_call_hdl.render_layout_mode);
    }
    if (video_call_is_render_device(0)) {
        log_info("Local device already in render list\n");
        return 0;
    }

    struct video_window *local_window = video_window_manager_get_window_next();
    if (local_window) {
        video_call_add_render(0, local_window);
    }

    return 0;
}

static void video_call_close_stream_main(void)
{
    if (g_video_call_hdl.stream_send) {
        video_stream_send_destroy(&g_video_call_hdl.stream_send);
        g_video_call_hdl.stream_send = NULL;
    }
    if (g_video_call_hdl.renderer) {
        multi_media_renderer_destroy(&g_video_call_hdl.renderer);
        g_video_call_hdl.renderer = NULL;
    }
    if (g_video_call_hdl.stream_recv) {
        video_stream_recv_destroy(&g_video_call_hdl.stream_recv);
        g_video_call_hdl.stream_recv = NULL;
    }
}

static void video_call_add_online_device(online_device_t *dev)
{
    //避免重复添加
    online_device_t *exist_dev = NULL;
    list_for_each_entry(exist_dev, &g_video_call_hdl.device_list, entry) {
        if (exist_dev->ip_addr == dev->ip_addr) {
            log_info("Device already in online list\n");
            return;
        }
    }
    online_device_t *copy_dev = malloc(sizeof(online_device_t));
    if (!copy_dev) {
        log_error("Failed to allocate memory for online device\n");
        return;
    }
    memcpy(copy_dev, dev, sizeof(online_device_t));

    list_add_tail(&copy_dev->entry, &g_video_call_hdl.device_list);
    g_video_call_hdl.online_ip_count++;
}

static void video_call_remove_offline_device(online_device_t *dev)
{
    online_device_t *exist_dev, *tmp;
    list_for_each_entry_safe(exist_dev, tmp, &g_video_call_hdl.device_list, entry) {
        if (exist_dev->ip_addr == dev->ip_addr) {
            list_del(&exist_dev->entry);
            free(exist_dev);
            g_video_call_hdl.online_ip_count--;
            return;
        }
    }
}

static void video_call_add_render_device(u32 ip_addr)
{
    //避免重复添加
    for (int i = 0; i < g_video_call_hdl.render_count; i++) {
        if (g_video_call_hdl.render_table[i] == ip_addr) {
            return;
        }
    }

    if (g_video_call_hdl.render_count < sizeof(g_video_call_hdl.render_table) / sizeof(g_video_call_hdl.render_table[0])) {
        g_video_call_hdl.render_table[g_video_call_hdl.render_count++] = ip_addr;
    }
}

static int video_call_is_render_device(u32 ip_addr)
{
    for (int i = 0; i < g_video_call_hdl.render_count; i++) {
        if (g_video_call_hdl.render_table[i] == ip_addr) {
            return 1;
        }
    }
    return 0;
}

static void video_call_remove_render_device(u32 ip_addr)
{
    for (int i = 0; i < g_video_call_hdl.render_count; i++) {
        if (g_video_call_hdl.render_table[i] == ip_addr) {
            //移除该IP地址
            for (int j = i; j < g_video_call_hdl.render_count - 1; j++) {
                g_video_call_hdl.render_table[j] = g_video_call_hdl.render_table[j + 1];
            }
            g_video_call_hdl.render_count--;
            return;
        }
    }
}

static void video_call_add_stream_device_cb(u32 ip_addr)
{
    app_send_message(APP_MSG_VIDEO_CALL_ADD_STREAM_RECV, 1, ip_addr);
}

static void video_call_del_stream_device_cb(u32 ip_addr)
{
    app_send_message(APP_MSG_VIDEO_CALL_DEL_STREAM_RECV, 1, ip_addr);
}

static int video_call_add_render(u32 ip_addr, struct video_window *window)
{
    int ret = 0;
    struct video_render_info render_info = {0};

    if (ip_addr && (!g_video_call_hdl.renderer || !g_video_call_hdl.stream_recv)) {
        log_error("renderer or stream_recv not initialized\n");
        return -1;
    }
    render_info.src_width = default_stream_info.img_width;
    render_info.src_height = default_stream_info.img_height;
    render_info.target_fps = default_stream_info.fps;
    render_info.window = *window;
    if (ip_addr == 0) {
        render_info.is_local = 1;
        render_info.local_camera_id = default_stream_info.device_id;
    } else {
        render_info.is_local = 0;
    }

    ret = renderer_add_channel(g_video_call_hdl.renderer, g_video_call_hdl.stream_recv, &render_info, ip_addr);
    if (ret != 0) {
        log_error("add remote render channel failed\n");
        return -1;
    }

    video_call_add_render_device(ip_addr);

    log_info("render channels added successfully\n");
    return 0;
}

static int video_call_remove_render(u32 ip_addr)
{
    int ret = 0;

    if (!g_video_call_hdl.renderer) {
        log_error("renderer not initialized\n");
        return -1;
    }

    ret = renderer_remove_channel(g_video_call_hdl.renderer, ip_addr);
    if (ret != 0) {
        log_error("remove remote render channel failed\n");
        return -1;
    }

    video_call_remove_render_device(ip_addr);

    log_info("render channels removed successfully\n");
    return 0;
}

static int video_call_request_stream_open(void)
{
    int ret = -1;
    if (g_video_call_hdl.wifi_mode == WIFI_RAW_MODE) {
        int device_num = g_video_call_hdl.online_ip_count + 1; // TODO? 告诉对方即将接收多少路流
        online_device_t *dev;
        list_for_each_entry(dev, &g_video_call_hdl.device_list, entry) {
            int err = video_stream_open_request(dev->cdp_hdl, &default_stream_info, device_num);
            if (err) {
                device_num--;
                log_error("request stream open failed for device ip:%s \n", dev->ip_str);
                continue;
            }
        }
        log_info("request success count:%d ", device_num - 1);

        if (device_num > 1) {
            ret = video_call_open_stream_main(device_num);
        }
    } else if (g_video_call_hdl.wifi_mode == WIFI_AP_STA_MODE) {
        // int device_num = 2;
        // const char *ip_addr = "192.168.1.1";
        // int err = video_stream_open_request(NULL, &default_stream_info, device_num, ipaddr_addr(ip_addr));
        // if (err) {
        //     log_error("request stream open failed for device ip:%s \n", ip_addr);
        //     return -1;
        // }
        // ret = video_call_open_stream_main(device_num);

    }

    return ret;
}

static int video_call_switch_render_window(void)
{
    int ret = 0;
    if (!g_video_call_hdl.renderer) {
        log_error("renderer not initialized\n");
        return -1;
    }
    if (g_video_call_hdl.render_layout_mode != 2 || g_video_call_hdl.render_count != 2) {
        log_warn("only support layout mode 2 switch\n");
        return -1;
    }

    //获取当前两个渲染设备的IP地址
    u32 ip_addr1 = g_video_call_hdl.render_table[0];
    u32 ip_addr2 = g_video_call_hdl.render_table[1];
    struct video_window *window1 = renderer_get_window_by_device_ip(g_video_call_hdl.renderer, ip_addr1);
    struct video_window *window2 = renderer_get_window_by_device_ip(g_video_call_hdl.renderer, ip_addr2);
    if (!window1 || !window2) {
        log_error("get render window failed\n");
        return -1;
    }
    struct video_window addr1_new_win = *window2;
    struct video_window addr2_new_win = *window1;

    //大的窗口需要先创建
    if (addr1_new_win.width >= addr2_new_win.width) {
        ret = video_call_remove_render(ip_addr1);
        if (ret != 0) {
            log_error("remove render failed for ip:%s \n", ipaddr_ntoa((const ip_addr_t *)&ip_addr1));
            return -1;
        }
        ret = video_call_add_render(ip_addr1, &addr1_new_win);
        if (ret != 0) {
            log_error("add render failed for ip:%s \n", ipaddr_ntoa((const ip_addr_t *)&ip_addr1));
            return -1;
        }
        ret = video_call_remove_render(ip_addr2);
        if (ret != 0) {
            log_error("remove render failed for ip:%s \n", ipaddr_ntoa((const ip_addr_t *)&ip_addr2));
            return -1;
        }
        ret = video_call_add_render(ip_addr2, &addr2_new_win);
        if (ret != 0) {
            log_error("add render failed for ip:%s \n", ipaddr_ntoa((const ip_addr_t *)&ip_addr2));
            return -1;
        }
    } else {
        ret = video_call_remove_render(ip_addr2);
        if (ret != 0) {
            log_error("remove render failed for ip:%s \n", ipaddr_ntoa((const ip_addr_t *)&ip_addr2));
            return -1;
        }
        ret = video_call_add_render(ip_addr2, &addr2_new_win);
        if (ret != 0) {
            log_error("add render failed for ip:%s \n", ipaddr_ntoa((const ip_addr_t *)&ip_addr2));
            return -1;
        }
        ret = video_call_remove_render(ip_addr1);
        if (ret != 0) {
            log_error("remove render failed for ip:%s \n", ipaddr_ntoa((const ip_addr_t *)&ip_addr1));
            return -1;
        }
        ret = video_call_add_render(ip_addr1, &addr1_new_win);
        if (ret != 0) {
            log_error("add render failed for ip:%s \n", ipaddr_ntoa((const ip_addr_t *)&ip_addr1));
            return -1;
        }
    }

    return 0;
}

//循环设置wifi发送速率,调试使用
static void video_call_txrate_loop_set(void)
{
    static u8 txrate = WIFI_TXRATE_1M;
    wifi_raw_set_txrate_val(txrate);

    txrate++;
    if (txrate > WIFI_TXRATE_72M) {
        txrate = WIFI_TXRATE_1M;
    }
}

//循环设置wifi重发次数,调试使用
static void video_call_wifi_retry_loop_set(void)
{
    static u8 short_retry = 0;
    static u8 long_retry = 0;
    wifi_raw_set_short_retry(short_retry);
    wifi_raw_set_long_retry(long_retry);

    short_retry++;
    long_retry++;
    if (short_retry > 10) {
        short_retry = 0;
    }
    if (long_retry > 10) {
        long_retry = 0;
    }
}

static int video_call_msg_handler(struct application *app, int *msg)
{
    u32 ip_addr;
    switch (msg[0]) {
    case APP_MSG_VIDEO_CALL_MAIN:
        log_debug("APP_MSG_VIDEO_CALL_MAIN\n");
        video_call_wifi_raw_init();
        // video_call_wifi_init();
        break;
    case APP_MSG_VIDEO_CALL_ADD_STREAM_RECV:
        ip_addr = msg[1];
        log_debug("Stream Recv Device Added: IP=%s\n", ipaddr_ntoa((const ip_addr_t *)&ip_addr));
        if (video_call_is_render_device(ip_addr)) {
            log_info("Device %s already in render list\n", ipaddr_ntoa((const ip_addr_t *)&ip_addr));
            break;
        }
        struct video_window *window = video_window_manager_get_window_next();
        if (window) {
            video_call_add_render(ip_addr, window);
        }
        break;
    case APP_MSG_VIDEO_CALL_DEL_STREAM_RECV:
        ip_addr = msg[1];
        log_debug("Stream Recv Device Removed: IP=%s\n", ipaddr_ntoa((const ip_addr_t *)&ip_addr));
        break;
    default:
        break;
    }
    return 0;
}

static u32 g_recording_ip = 0;

static void test_rec_start(void)
{
    const char *file_path = "storage/sd0/C/VID_****.avi";
    log_debug("KEY2 CLICK: rec_start\n");
    if (g_recording_ip != 0) {
        log_info("already recording ip:%s\n", inet_ntoa(g_recording_ip));
    }
    /* 找一个远端设备 */
    u32 target_ip = 0;
    for (int i = 0; i < g_video_call_hdl.render_count; i++) {
        if (g_video_call_hdl.render_table[i] != 0) {
            target_ip = g_video_call_hdl.render_table[i];
            break;
        }
    }
    if (target_ip == 0) {
        log_info("no remote device to record\n");
    }
    if (!g_video_call_hdl.stream_recv) {
        log_info("stream_recv not ready\n");
    }
    int ret = video_stream_recv_rec_start(g_video_call_hdl.stream_recv, target_ip,
                                          file_path,
                                          STREAM_VIDEO_WIDTH, STREAM_VIDEO_HEIGHT,
                                          STREAM_VIDEO_FPS,
                                          STREAM_AUDIO_SAMPLE_RATE,
                                          STREAM_AUDIO_CHANNEL, 16);
    if (ret == 0) {
        g_recording_ip = target_ip;
        log_info("rec_start success, ip:%s, file:%s\n", inet_ntoa(target_ip), file_path);
    } else {
        log_error("rec_start failed, ret:%d\n", ret);
    }
}

static void test_rec_stop(void)
{
    log_debug("KEY3 CLICK: rec_stop\n");
    if (g_recording_ip == 0) {
        log_info("not recording\n");
    }
    if (!g_video_call_hdl.stream_recv) {
        log_info("stream_recv not ready\n");
    }
    int ret = video_stream_recv_rec_stop(g_video_call_hdl.stream_recv, g_recording_ip);
    if (ret == 0) {
        log_info("rec_stop success, ip:%s\n", inet_ntoa(g_recording_ip));
    } else {
        log_error("rec_stop failed, ret:%d\n", ret);
    }
    g_recording_ip = 0;
}

static int video_call_state_machine(struct application *app, enum app_state state, struct intent *it)
{
    int ret = 0;
    online_device_t *dev = NULL;

    switch (state) {
    case APP_STA_CREATE:
        log_debug("\n >>>>>>> VIDEO_CALL APP_STA_CREATE\n");
        break;
    case APP_STA_START:
        if (!it) {
            break;
        }
        switch (it->action) {
        case ACTION_VIDEO_CALL_OPEN_STREAM:
            log_debug("ACTION_VIDEO_CALL_OPEN_STREAM\n");
            //TODO: use stream_info ?
            struct video_stream_info *stream_info = (struct video_stream_info *)it->data;
            int device_num = it->exdata;
            ret = video_call_open_stream_main(device_num);
            break;
        case ACTION_VIDEO_CALL_CLOSE_STREAM:
            log_debug("ACTION_VIDEO_CALL_CLOSE_STREAM\n");
            video_call_close_stream_main();
            break;
        case ACTION_VIDEO_CALL_DEV_ONLINE:
            log_debug("ACTION_VIDEO_CALL_DEV_ONLINE\n");
            dev = (online_device_t *)it->data;
            video_call_add_online_device(dev);
            break;
        case ACTION_VIDEO_CALL_DEV_OFFLINE:
            log_debug("ACTION_VIDEO_CALL_DEV_OFFLINE\n");
            dev = (online_device_t *)it->data;
            video_call_remove_offline_device(dev);
            break;
        default:
            break;
        }
        break;
    case APP_STA_PAUSE:
        log_debug("--------VIDEO_CALL APP_STA_PAUSE\n");
        break;
    case APP_STA_RESUME:
        log_debug("--------VIDEO_CALL APP_STA_RESUME\n");
        break;
    case APP_STA_STOP:
        log_debug("--------VIDEO_CALL APP_STA_STOP\n");
        break;
    case APP_STA_DESTROY:
        break;
    }

    return ret;
}


static int video_call_key_event_handler(struct key_event *key)
{
    int ret = false;
    log_debug("key->action:%d key->value:%d \n", key->action, key->value);

    switch (key->value) {
    case KEY_POWER:
        ret = true;
        if (key->action == KEY_EVENT_CLICK) {
            log_debug("KEY1 CLICK\n");
            video_call_wifi_retry_loop_set();
        }
        break;
    case KEY_MENU:
        ret = true;
        if (key->action == KEY_EVENT_CLICK) {
            log_debug("KEY2 CLICK\n");
            //video_call_txrate_loop_set();
            test_rec_start();
        }
        break;
    case KEY_UP:
        ret = true;
        if (key->action == KEY_EVENT_CLICK) {
            log_debug("KEY3 CLICK\n");
            // video_call_switch_render_window();
            test_rec_stop();
        }
        break;
    case KEY_DOWN:
        ret = true;
        if (key->action == KEY_EVENT_CLICK) {
            log_debug("KEY4 CLICK\n");
            //发起视频请求
            video_call_request_stream_open();
        }
        break;
    case KEY_OK:
        ret = true;
        if (key->action == KEY_EVENT_CLICK) {
            log_debug("KEY5 CLICK\n");
        }
        break;
    default:
        break;
    }

    return ret;
}

static int video_call_device_event_handler(struct sys_event *e)
{
    int ret = false;
    return ret;
}

int video_call_net_event_handler(void *e)
{
    struct net_event *event = (struct net_event *)e;
    struct ctp_arg *event_arg = (struct ctp_arg *)event->arg;

    switch (event->event) {
    default:
        break;
    }
    return false;
}

static int video_call_event_handler(struct application *app, struct sys_event *event)
{
    switch (event->type) {
    case SYS_KEY_EVENT:
        return video_call_key_event_handler((struct key_event *)event->payload);
    case SYS_DEVICE_EVENT:
        return video_call_device_event_handler(event);
    case SYS_NET_EVENT:
        return video_call_net_event_handler((void *)event->payload);
    default:
        return false;
    }
}



static const struct application_operation video_call_ops = {
    .state_machine  = video_call_state_machine,
    .event_handler 	= video_call_event_handler,
    .msg_handler    = video_call_msg_handler,
};

REGISTER_APPLICATION(app_video_call) = {
    .name 	= "video_call",
    .action	= ACTION_VIDEO_CALL_MAIN,
    .ops 	= &video_call_ops,
    .state  = APP_STA_DESTROY,
};





