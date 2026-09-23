#include "app_config.h"
#include "system/includes.h"
#include "os/os_api.h"
#include "lvgl.h"

/*中断列表 */
const struct irq_info irq_info_table[] = {
    //中断号   //优先级0-7   //注册的cpu(0或1)
#if CPU_CORE_NUM == 1
    { IRQ_SOFT5_IDX,    6,  0 }, //此中断强制注册到cpu0
    { IRQ_SOFT4_IDX,    6,  1 }, //此中断强制注册到cpu1
    { -2,              -2, -2 }, //如果加入了该行, 那么只有该行之前的中断注册到对应核, 其他所有中断强制注册到CPU0
#endif
    { -1,              -1, -1 },
};

/*任务列表 */
const struct task_info task_info_table[] = {
    {"app_core",            15,     2048,	  1024 },
    {"sys_event",           29,     512,	   0 },
    {"systimer",            14,     256, 	   0 },
    {"sys_timer",            9,     512,	  128 },

    {0, 0, 0, 0, 0},
};


#ifdef USE_LVGL_V8_UI_DEMO
#include "lvgl.h"
void jl_gui_init(void)
{
#if LV_USE_MONKEY != 0
    /*Create pointer monkey test*/
    lv_monkey_config_t monkey_pointer_config;
    monkey_pointer_config.type = LV_INDEV_TYPE_POINTER;
    monkey_pointer_config.period_range.min = 20;
    monkey_pointer_config.period_range.max = 20;
    lv_monkey_set_enable(lv_monkey_create(&monkey_pointer_config), true);

    /*Create keypad monkey test*/
    lv_monkey_config_t monkey_keypad_config;
    monkey_keypad_config.type = LV_INDEV_TYPE_KEYPAD;
    monkey_keypad_config.period_range.min = 20;
    monkey_keypad_config.period_range.max = 20;
    lv_monkey_set_enable(lv_monkey_create(&monkey_keypad_config), true);

    /*Create encoder monkey test*/
    lv_monkey_config_t monkey_encode_config;
    monkey_encode_config.type = LV_INDEV_TYPE_ENCODER;
    monkey_encode_config.period_range.min = 20;
    monkey_encode_config.period_range.max = 20;
    monkey_encode_config.input_range.min = -5;
    monkey_encode_config.input_range.max = 5;
    lv_monkey_set_enable(lv_monkey_create(&monkey_encode_config), true);
#endif

#if LV_USE_DEMO_BENCHMARK
    lv_demo_benchmark();
#elif LV_USE_DEMO_WIDGETS
    lv_demo_widgets();
#else
    puts("\r\n\r\n LVGL APP NOT DEFINE...");
#endif
}
#endif


void app_main(void)
{
    printf("\n\n\n ------------demo ui run %s-------------\n\n\n", __TIME__);
    int lvgl_main_task_init(void);
    lvgl_main_task_init();
}

