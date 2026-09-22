#include "tkl_sleep.h"

#include "tuya_error_code.h"
#include "system/os/os_api.h"

void tkl_system_sleep(uint32_t num_ms)
{
    os_time_dly((int)((num_ms + 9u) / 10u));
}

void tkl_system_delay(uint32_t num_ms)
{
    os_time_dly((int)((num_ms + 9u) / 10u));
}

OPERATE_RET tkl_cpu_sleep_mode_set(BOOL_T enable, TUYA_CPU_SLEEP_MODE_E mode)
{
    (void)enable;
    (void)mode;
    return OPRT_NOT_SUPPORTED;
}

OPERATE_RET tkl_cpu_sleep_callback_register(TUYA_SLEEP_CB_T *sleep_cb)
{
    (void)sleep_cb;
    return OPRT_NOT_SUPPORTED;
}

void tkl_cpu_allow_sleep(void)
{
}

void tkl_cpu_force_wakeup(void)
{
}
