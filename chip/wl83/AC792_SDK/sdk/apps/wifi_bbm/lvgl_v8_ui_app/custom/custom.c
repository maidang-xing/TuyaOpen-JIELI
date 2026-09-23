/**
 * @file custom.c
 *
 */

/*********************
 *      INCLUDES
 *********************/
#include <stdio.h>
#include "lvgl.h"
#include "custom.h"
#include <time.h>

/*********************
 *      DEFINES
 *********************/
#if !LV_USE_GUIBUILDER_SIMULATOR
#include "app_config.h"
#include "event/key_event.h"
//Baby Monitor RX端LVGL按键映射

//返回1时，则将按键信息交给app core处理
//这里不做处理，统一交给页面注册key_handler处理
int ui_scr_key_event_handler_ext(struct key_event *event)
{
    //KEY1/2/3/4/5...........
    return 0;
}

//LVGL按键映射
void lvgl_key_value_remap(u8 key_value, uint32_t *key_remap)
{
    switch (key_value) {
    case KEY_POWER:
        //KEY1
        *key_remap = LV_KEY_PREV;
        break;
    case KEY_MENU:
        //KEY1
        *key_remap = LV_KEY_NEXT;
        break;
    case KEY_UP:
        //KEY3
        *key_remap = LV_KEY_ENTER;
        break;
    case KEY_DOWN:
        //KEY4
        *key_remap = LV_KEY_UP;
        break;
    case KEY_OK:
        //KEY5
        *key_remap = LV_KEY_DOWN;
        break;
    }
}
#endif


/**********************
 *      TYPEDEFS
 **********************/

/**********************
 *  STATIC PROTOTYPES
 **********************/

/**********************
 *  STATIC VARIABLES
 **********************/

/**
 * Create a demo application
 */

void custom_init(lv_ui *ui)
{
    /* Add your codes here */
}
