#include "platform_timer.h"

int os_timer_create(TIMER_T *handler, uint32_t time_interval_ms, bool is_auto_reset, os_timer_callback func, void *arg)
{
    OS_Timer_t *timer = (OS_Timer_t *)zalloc(sizeof(OS_Timer_t));
    if (!timer) {
        *handler = NULL;
        return -1;
    }

    timer->cb = func;
    timer->priv = arg;

    if (time_interval_ms > 0 && time_interval_ms < 10) {
        time_interval_ms = 10;
    }

    timer->msec = time_interval_ms;
    timer->oneshort = !is_auto_reset;
    *handler = timer;

    return 0;
}

int os_timer_start(TIMER_T *handler)
{
    OS_Timer_t *timer = (OS_Timer_t *)*handler;
    if (timer->oneshort) {
        timer->id = sys_timeout_add_to_task("sys_timer", timer->priv, timer->cb, timer->msec);
    } else {
        timer->id = sys_timer_add_to_task("sys_timer", timer->priv, timer->cb, timer->msec);
    }

    return 0;
}

int os_timer_stop(TIMER_T *handler)
{
    OS_Timer_t *timer = (OS_Timer_t *)*handler;
    if (timer->id) {
        sys_timeout_del(timer->id);
        timer->id = 0;
    }
    return 0;
}

int os_timer_destroy(TIMER_T *handler)
{
    os_timer_stop(handler);
    free(*handler);
    return 0;
}

void *os_timer_get_arg(TIMER_T *handler)
{
    OS_Timer_t *timer = (OS_Timer_t *)*handler;
    return timer->priv;
}

