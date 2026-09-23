#include "app_config.h"
#include "system/includes.h"
#include "os/os_api.h"

#include "tkl_init.h"
#include "tkl_output.h"

const struct irq_info irq_info_table[] = {
    { -1, -1, -1 },
};

const struct task_info task_info_table[] = {
    { "app_core", 15, 2048, 1024 },
    { "sys_event", 29, 512, 0 },
    { "systimer", 14, 256, 0 },
    { "sys_timer", 9, 512, 128 },
    { 0, 0, 0, 0 },
};

static void jieli_hello_task(void *arg)
{
    (void)arg;
    while (1) {
        os_time_dly(200);
        tkl_log_output("TuyaOpen Jieli UART heartbeat\r\n");
    }
}

void app_main(void)
{
    tkl_init();
#if defined(CONFIG_CPU_WL83)
    tkl_log_output("TuyaOpen Jieli AC792N_Develop_Board (wl83)\r\n");
#else
    tkl_log_output("TuyaOpen Jieli AC79_DevKitBoard (wl82)\r\n");
#endif
    os_task_create(jieli_hello_task, NULL, 10, 1000, 0, "tuya_hello");
}
