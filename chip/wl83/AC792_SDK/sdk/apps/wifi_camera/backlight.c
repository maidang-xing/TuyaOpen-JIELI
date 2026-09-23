#include "system/includes.h"
#include "video_rec.h"
#include "event/key_event.h"
#include "event/touch_event.h"
#include "event/device_event.h"
#include "event/event.h"

static u8 lcd_pro_flag = 0; /* 屏保触发标志，1：已经触发 */
static u16 lcd_protect_time = 0; /* 屏保触发时间，单位秒 */
static u16 lcd_pro_cnt = 0;
static int timer = 0;


static void ui_lcd_light_on(void)
{
    puts("====ui_lcd_light_on====\n");
#if TCFG_LCD_ENABLE
    lcd_backlight_ctrl(true);
#endif
    touch_event_produce();
}

static void ui_lcd_light_off(void)
{
    puts("====ui_lcd_light_off====\n");
#if TCFG_LCD_ENABLE
    lcd_backlight_ctrl(false);
#endif
    touch_event_consume();
}


/*
 * 屏幕保护计时器
 */
static void lcd_pro_kick(void *priv)
{
    if (get_parking_status()) {
        //倒车不屏保
        lcd_pro_cnt = 0;
        return;
    }
    if (lcd_protect_time && lcd_pro_flag == 0) {
        lcd_pro_cnt++;
        if (lcd_pro_cnt >= lcd_protect_time) {
            puts("\n\n\n********lcd_pro_kick********\n\n\n");
            lcd_pro_cnt = 0;
            lcd_pro_flag = 1;
            ui_lcd_light_off();
        }
    } else {
        lcd_pro_cnt = 0;
    }
}

void ui_lcd_light_time_set(int sec)
{
    printf("ui_lcd_light_time_set sec:%d\n", sec);

    if (sec) {
        lcd_protect_time = sec;
        if (!timer) {
            timer = sys_timer_add(NULL, lcd_pro_kick, 1000);
        }
    } else {
        lcd_protect_time = 0;
    }
}

static int backlight_event_handler(struct sys_event *e)
{

    struct key_event *key = (struct key_event *)e->payload;
    lcd_pro_cnt = 0;
    /* if (key->action != KEY_EVENT_UP) { */
    /* return 0; */
    /* } */

    if (lcd_pro_flag) {
        /* if (event->type == SYS_KEY_EVENT) { */
        ui_lcd_light_on();
        lcd_pro_flag = 0;
        /* sys_key_event_consume(&(event->u.key)); [> 背光关闭时，按键只是打开背光 <] */
        /* } else if (event->type == SYS_TOUCH_EVENT) { */
        /* sys_touch_event_consume(&(event->u.touch)); [> 背光关闭时，触摸只是打开背光 <] */
        /* if (event->u.touch.event == ELM_EVENT_TOUCH_UP) { */
        /* ui_lcd_light_on(); */
        /* lcd_pro_flag = 0; */
        /* } */
        /* } */
        return -EINVAL;
    } else if (key->action == KEY_EVENT_UP
               && key->value == KEY_POWER) {
        /* lcd_pro_flag = 1; */
        /* ui_lcd_light_off(); */
        /* sys_key_event_consume(&(event->u.key)); */
        /*return -EINVAL;*/
    }
    return 0;
}

SYS_EVENT_STATIC_HANDLER_REGISTER(key_handler, 1) = {
    .event_type = SYS_KEY_EVENT,
    .prob_handler = backlight_event_handler,
    .post_handler = NULL,
};


static int backlight_touch_event_handler(struct sys_event *e)
{

    struct touch_event *touch = (struct touch_event *)e->payload;
    lcd_pro_cnt = 0;
    if (lcd_pro_flag) {
        if (touch->action == TOUCH_EVENT_UP) {
            ui_lcd_light_on();
            lcd_pro_flag = 0;
            touch_event_produce();
        }
    }
    return -EINVAL;
}

SYS_EVENT_STATIC_HANDLER_REGISTER(touch_handler, 0) = {
    .event_type = SYS_TOUCH_EVENT,
    .prob_handler = backlight_touch_event_handler,
    .post_handler = NULL,
};





static int backlight_charge_event_handler(struct sys_event *sys_eve)
{

    struct device_event *device_eve = (struct device_event *)sys_eve->payload;
    if (sys_eve->from == DEVICE_EVENT_FROM_POWER) {
#if 0
        if (device_eve->event == DEVICE_EVENT_POWER_CHARGER_IN) {
            if (lcd_pro_flag) {
                ui_lcd_light_on();
                lcd_pro_flag = 0;
            }

        } else if (device_eve->event == DEVICE_EVENT_POWER_CHARGER_OUT) {
            if (lcd_pro_flag) {
                ui_lcd_light_on();
                lcd_pro_flag = 0;
            }
        }
#endif

    } else if (sys_eve->from == DEVICE_EVENT_FROM_VIDEO && !strncmp((const char *)device_eve->arg, "parking", 7)) {
        switch (device_eve->event) {
        case DEVICE_EVENT_IN:
            ui_lcd_light_on();
            lcd_pro_flag = 0;

            break;
        case DEVICE_EVENT_OUT:
            if (lcd_pro_flag) {
                ui_lcd_light_on();
                lcd_pro_flag = 0;
            }

            break;
        }


    } else if (sys_eve->from == DEVICE_EVENT_FROM_VIDEO && !strncmp((const char *)device_eve->arg, "mot", 3)) {

        switch (device_eve->event) {
        case DEVICE_EVENT_CHANGE:
            if (device_eve->value == true) {
                ui_lcd_light_on();
                lcd_pro_flag = 0;


            } else {
                if (lcd_pro_flag) {
                    ui_lcd_light_off();
                    lcd_pro_flag = 0;
                }


            }

            break;
        }


    }
    return 0;
}

SYS_EVENT_STATIC_HANDLER_REGISTER(dev_handler, 0) = {
    .event_type = SYS_DEVICE_EVENT,
    .prob_handler = backlight_charge_event_handler,
    .post_handler = NULL,
};




