#include "app_config.h"
#ifdef CONFIG_UI_STYLE_JL_ENABLE
/*********************
 *      INCLUDES
 *********************/
#if !LV_USE_GUIBUILDER_SIMULATOR

#include "lvgl.h"
#include "ui.h"
#include "custom.h"
#include "app_config.h"
#include "sys_time.h"
#include "system/includes.h"
#include "asm/includes.h"
#include "syscfg/syscfg_id.h"
#include "action.h"
/*********************
 *      DEFINES
 *********************/
extern bool usb_flag;
/**********************
 *  STATIC FUNCTION
 **********************/
//注册页面加载卸载回调
bool get_usb_app_flag(void)
{
    return usb_flag;
}
int gui_src_action_usb(int action)
{
    printf("[chili] %s %d   \n", __func__, __LINE__);
    switch (action) {
    case GUI_SCREEN_ACTION_LOAD:
        app_mode_go_back();

        //usb_start();
        break;
    case GUI_SCREEN_ACTION_UNLOAD:
#if USB_PC_NO_APP_MODE && TCFG_PC_ENABLE == 1
        /* usb_stop(); */
#endif
        break;
    }

}

REGISTER_UI_SCREEN_ACTION_HANDLER(GUI_SCREEN_USB_SLAVE)
.onchange = gui_src_action_usb,
};



/*
* 显示USB界面
*
*/
void usb_page_show(int arg)
{
    printf("[chili]: %s %d\n", __func__, __LINE__);

    //跳转显示USB界面
    if (!usb_flag) {
        usb_flag = true;
        gui_scr_t *screen = gui_scr_get(GUI_SCREEN_USB_SLAVE);
        if (screen == NULL) {
            printf("[chili]: %s %d\n", __func__, __LINE__);
            screen = gui_scr_create(GUI_SCREEN_USB_SLAVE, "usb_slave", guider_ui.usb_slave, (gui_scr_setup_cb_t)setup_scr_usb_slave, (gui_scr_unload_cb_t)unload_scr_usb_slave);
        }
        ui_load_scr_anim(&guider_ui, screen, LV_SCR_LOAD_ANIM_NONE, 100, 100, true, true, false);//不压栈

    }
}

/*
*
* USB界面隐藏、显示主界面
*
*/
void usb_page_hide(int arg)
{

    printf("[chili]: %s %d\n", __func__, __LINE__);
    if (usb_flag) {
        gui_scr_t *screen = gui_scr_get(GUI_SCREEN_HOME_PAGE);
        if (screen == NULL) {
            printf("[chili]: %s %d\n", __func__, __LINE__);
            screen = gui_scr_create(GUI_SCREEN_HOME_PAGE, "home_page", guider_ui.home_page, (gui_scr_setup_cb_t)setup_scr_home_page, (gui_scr_unload_cb_t)unload_scr_home_page);
        }
        ui_load_scr_anim(&guider_ui, screen, LV_SCR_LOAD_ANIM_NONE, 100, 100, true, true, false);
        usb_flag = false;
    }
}
#endif


#endif
