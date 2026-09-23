#include "tkl_timer.h"

#include "tuya_error_code.h"
#include "system/timer.h"

#include <string.h>

typedef struct {
    TUYA_TIMER_BASE_CFG_T cfg;
    uint16_t native_id;
    uint32_t period_ms;
    uint32_t start_ms;
    uint8_t initialized;
    uint8_t running;
    uint8_t timeout;
} jieli_timer_slot_t;

static jieli_timer_slot_t s_jieli_timer_slots[TUYA_TIMER_NUM_MAX];

static uint32_t jieli_timer_us_to_ms(uint32_t us)
{
    return (us + 999U) / 1000U;
}

static void jieli_timer_callback(void *priv)
{
    jieli_timer_slot_t *slot = (jieli_timer_slot_t *)priv;
    if (slot == NULL || !slot->running) {
        return;
    }
    if (slot->cfg.cb != NULL) {
        slot->cfg.cb(slot->cfg.args);
    }
    if (slot->timeout) {
        slot->running = 0;
        slot->native_id = 0;
    }
}

static void jieli_timer_stop_slot(jieli_timer_slot_t *slot)
{
    if (slot == NULL || !slot->running) {
        return;
    }
    if (slot->timeout) {
        sys_timeout_del(slot->native_id);
    } else {
        sys_timer_del(slot->native_id);
    }
    slot->native_id = 0;
    slot->running = 0;
}

OPERATE_RET tkl_timer_init(TUYA_TIMER_NUM_E timer_id, TUYA_TIMER_BASE_CFG_T *cfg)
{
    if (timer_id >= TUYA_TIMER_NUM_MAX || cfg == NULL || cfg->cb == NULL) {
        return OPRT_INVALID_PARM;
    }
    (void)tkl_timer_deinit(timer_id);
    memset(&s_jieli_timer_slots[timer_id], 0, sizeof(s_jieli_timer_slots[timer_id]));
    s_jieli_timer_slots[timer_id].cfg = *cfg;
    s_jieli_timer_slots[timer_id].initialized = 1;
    return OPRT_OK;
}

OPERATE_RET tkl_timer_start(TUYA_TIMER_NUM_E timer_id, uint32_t us)
{
    jieli_timer_slot_t *slot;
    uint32_t period_ms;
    if (timer_id >= TUYA_TIMER_NUM_MAX || us == 0) {
        return OPRT_INVALID_PARM;
    }
    slot = &s_jieli_timer_slots[timer_id];
    if (!slot->initialized) {
        return OPRT_INVALID_PARM;
    }
    period_ms = jieli_timer_us_to_ms(us);
    if (period_ms == 0) {
        return OPRT_INVALID_PARM;
    }
    jieli_timer_stop_slot(slot);
    slot->period_ms = period_ms;
    slot->start_ms = sys_timer_get_ms();
    slot->timeout = slot->cfg.mode == TUYA_TIMER_MODE_ONCE;
    if (slot->timeout) {
        slot->native_id = sys_timeout_add(slot, jieli_timer_callback, period_ms);
    } else {
        slot->native_id = sys_timer_add(slot, jieli_timer_callback, period_ms);
    }
    slot->running = 1;
    return OPRT_OK;
}

OPERATE_RET tkl_timer_stop(TUYA_TIMER_NUM_E timer_id)
{
    if (timer_id >= TUYA_TIMER_NUM_MAX) {
        return OPRT_INVALID_PARM;
    }
    if (!s_jieli_timer_slots[timer_id].initialized) {
        return OPRT_INVALID_PARM;
    }
    jieli_timer_stop_slot(&s_jieli_timer_slots[timer_id]);
    return OPRT_OK;
}

OPERATE_RET tkl_timer_deinit(TUYA_TIMER_NUM_E timer_id)
{
    if (timer_id >= TUYA_TIMER_NUM_MAX) {
        return OPRT_INVALID_PARM;
    }
    jieli_timer_stop_slot(&s_jieli_timer_slots[timer_id]);
    memset(&s_jieli_timer_slots[timer_id], 0, sizeof(s_jieli_timer_slots[timer_id]));
    return OPRT_OK;
}

OPERATE_RET tkl_timer_get_current_value(TUYA_TIMER_NUM_E timer_id, uint32_t *us)
{
    uint32_t elapsed_ms;
    jieli_timer_slot_t *slot;
    if (timer_id >= TUYA_TIMER_NUM_MAX || us == NULL) {
        return OPRT_INVALID_PARM;
    }
    slot = &s_jieli_timer_slots[timer_id];
    if (!slot->initialized) {
        return OPRT_INVALID_PARM;
    }
    if (!slot->running || slot->period_ms == 0) {
        *us = 0;
        return OPRT_OK;
    }
    elapsed_ms = sys_timer_get_ms() - slot->start_ms;
    if (slot->timeout && elapsed_ms > slot->period_ms) {
        elapsed_ms = slot->period_ms;
    } else if (!slot->timeout) {
        elapsed_ms %= slot->period_ms;
    }
    *us = elapsed_ms * 1000U;
    return OPRT_OK;
}

OPERATE_RET tkl_timer_get(TUYA_TIMER_NUM_E timer_id, uint32_t *us)
{
    if (timer_id >= TUYA_TIMER_NUM_MAX || us == NULL) {
        return OPRT_INVALID_PARM;
    }
    if (!s_jieli_timer_slots[timer_id].initialized) {
        return OPRT_INVALID_PARM;
    }
    *us = s_jieli_timer_slots[timer_id].period_ms * 1000U;
    return OPRT_OK;
}

