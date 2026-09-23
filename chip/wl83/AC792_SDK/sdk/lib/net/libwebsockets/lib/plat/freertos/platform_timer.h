//
// Created by Administrator on 25-4-16.
//

#ifndef PLATFORM_TIME_H
#define PLATFORM_TIME_H

#include "system/timer.h"

typedef void (*os_timer_callback)(void *arg);
typedef void *TIMER_T;

typedef struct {
    unsigned short id;
    unsigned char oneshort;
    os_timer_callback cb;
    u32 msec;
    void *priv;
} OS_Timer_t;

int os_timer_create(TIMER_T *handler, uint32_t time_interval_ms, bool is_auto_reset, os_timer_callback func, void *arg);
int os_timer_start(TIMER_T *handler);
int os_timer_stop(TIMER_T *handler);
int os_timer_delete(TIMER_T *handler);
int os_timer_destroy(TIMER_T *handler);
void *os_timer_get_arg(TIMER_T *handler);

#endif //PLATFORM_TIME_H
