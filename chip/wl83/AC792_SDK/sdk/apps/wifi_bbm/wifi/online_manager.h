#ifndef ONLINE_MANAGER_H
#define ONLINE_MANAGER_H

#include "system/includes.h"

typedef enum {
    DEVICE_STATUS_OFFLINE = 0,  // 离线
    DEVICE_STATUS_ONLINE = 1,   // 在线
} device_status_e;

typedef struct online_device {
    u32 ip_addr;                    // 设备IP地址
    char ip_str[16];                // IP字符串
    u32 last_seen_time;             // 最后一次在线时间(ms)
    u32 active_cnt;                 // 活动计数
    device_status_e status;         // 设备状态
    void *cdp_hdl;                 // CDP句柄
    struct list_head entry;         // 链表节点
} online_device_t;

int online_manager_init(void);
void online_manager_exit(void);


#endif // ONLINE_MANAGER_H


