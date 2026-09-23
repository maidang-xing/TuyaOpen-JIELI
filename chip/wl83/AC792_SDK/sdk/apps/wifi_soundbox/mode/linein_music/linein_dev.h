#ifndef _LINEIN_DEV_H_
#define _LINEIN_DEV_H_

#include "generic/typedef.h"
#include "device/device.h"

struct linein_dev_data {
    u8 up;
    u8 down;
    u16 ad_vol;
    int port;
    int ad_channel;
};

int linein_is_online(void);
void linein_set_online(u8 online);
void linein_detect_timer_add(void);
void linein_detect_timer_del(void);

extern const struct device_operations linein_detect_dev_ops;

#endif
