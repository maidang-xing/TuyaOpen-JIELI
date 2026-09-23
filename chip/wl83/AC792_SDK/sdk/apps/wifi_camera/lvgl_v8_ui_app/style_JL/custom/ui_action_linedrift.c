#include "app_config.h"
#ifdef CONFIG_UI_STYLE_JL_ENABLE
/*********************
 *      INCLUDES
 *********************/

#include "lvgl.h"
#include "custom.h"

#if !LV_USE_GUIBUILDER_SIMULATOR
#include "app_config.h"
#include "system/includes.h"
#include "asm/includes.h"
#include "syscfg/syscfg_id.h"
#include "action.h"
#include "ui.h"
#include "sys_time.h"
#endif


#if !LV_USE_GUIBUILDER_SIMULATOR

//注册页面加载卸载回调
int gui_src_action_lane(int action)
{
    lv_ui_line_drift *ui_scr = ui_get_scr_ptr(&guider_ui, GUI_SCREEN_LINE_DRIFT);
    if (!ui_scr) {
        return -1;
    }
    printf("[chili] %s %d   \n", __func__, __LINE__);

    switch (action) {
    case GUI_SCREEN_ACTION_LOAD:
#if LV_DISP_UI_FB_NUM
        lv_obj_set_style_bg_opa(ui_scr->line_drift, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
#else
        lv_obj_set_style_bg_opa(ui_scr->line_drift, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
#endif

        if (FALSE == current_app_in_mode(APP_MODE_REC)) {
            app_msg_handler(NULL, APP_MSG_STOP);
            app_mode_change_replace(APP_MODE_REC);
        }
        app_send_message(APP_MSG_REC_MAIN, 0);
        break;
    case GUI_SCREEN_ACTION_UNLOAD:
        app_mode_go_back();
        break;
    }
}
REGISTER_UI_SCREEN_ACTION_HANDLER(GUI_SCREEN_LINE_DRIFT)
.onchange = gui_src_action_lane,
};

#endif

/*
* 显示车道偏移设置页面
*
*/
void line_drift_page_show(int arg)
{
    printf("[chili]: %s %d\n", __func__, __LINE__);
    gui_scr_t *screen = gui_scr_get(GUI_SCREEN_LINE_DRIFT);
    if (screen == NULL) {
        printf("[chili]: %s %d\n", __func__, __LINE__);
        screen = gui_scr_create(GUI_SCREEN_LINE_DRIFT, "line_drift", guider_ui.line_drift, (gui_scr_setup_cb_t)setup_scr_line_drift, (gui_scr_unload_cb_t)unload_scr_line_drift);
    }
    ui_load_scr_anim(&guider_ui, screen, LV_SCR_LOAD_ANIM_NONE, 100, 100, true, true, false);//不压栈


}

/*
*
* 隐藏车道偏移设置页面跳转到系统设置页面
*
*/
void line_drift_page_hide(int arg)
{

    printf("[chili]: %s %d\n", __func__, __LINE__);

    gui_scr_t *screen = gui_scr_get(GUI_SCREEN_SYS_SETTING);
    if (screen == NULL) {
        printf("[chili]: %s %d\n", __func__, __LINE__);
        screen = gui_scr_create(GUI_SCREEN_SYS_SETTING, "sys_setting", guider_ui.sys_setting, (gui_scr_setup_cb_t)setup_scr_sys_setting, (gui_scr_unload_cb_t)unload_scr_sys_setting);
    }
    ui_load_scr_anim(&guider_ui, screen, LV_SCR_LOAD_ANIM_NONE, 100, 100, true, true, false);

}

#endif
