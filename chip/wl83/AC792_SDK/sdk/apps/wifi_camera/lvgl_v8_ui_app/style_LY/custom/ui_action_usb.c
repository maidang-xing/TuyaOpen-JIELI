#include "app_config.h"
#ifdef CONFIG_UI_STYLE_LY_ENABLE
/*********************
 *      INCLUDES
 *********************/
#include "custom.h"
#if !LV_USE_GUIBUILDER_SIMULATOR
#include "ui.h"
#include "lvgl.h"
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

bool get_usb_app_flag(void)
{
    return usb_flag;
}

/**********************
 *  STATIC FUNCTION
 **********************/
//注册页面加载卸载回调
int gui_src_action_usb(int action)
{
    struct intent it;
    init_intent(&it);

    printf("--->%s()----->%d, action: %d\n", __func__, __LINE__, action);
    switch (action) {
    case GUI_SCREEN_ACTION_LOAD:
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
        gui_scr_t *screen = ui_get_scr(GUI_SCREEN_USB_SLAVE);
        ui_load_scr_anim(&guider_ui, screen, LV_SCR_LOAD_ANIM_NONE, 0, 0, true, true, false);//不压栈

    }
}

/*
*
* USB界面隐藏、录像界面
*
*/
void usb_page_hide(int arg)
{
    printf("[chili]: %s %d, usb_flag: %d\n", __func__, __LINE__, usb_flag);
    if (usb_flag) {
        usb_flag = false;
        gui_scr_t *screen = ui_get_scr(GUI_SCREEN_VIDEO_REC);
        ui_load_scr_anim(&guider_ui, screen, LV_SCR_LOAD_ANIM_NONE, 0, 0, true, true, false);
    }
}

#endif


#endif
