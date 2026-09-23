#include "app_config.h"
#ifdef CONFIG_UI_STYLE_JL_ENABLE
#if !LV_USE_GUIBUILDER_SIMULATOR

#include "lvgl.h"
#include "ui.h"
#include "custom.h"
#include "app_config.h"
#include "app_msg.h"
#include "sys_time.h"
#include "system/includes.h"
#include "asm/includes.h"
#include "syscfg/syscfg_id.h"
#include "action.h"

lv_group_t *def_group;
lv_group_t *group_list;
extern void sys_prompt_show_ctl(int32_t show_time, void *tips);
//注册页面加载卸载回调
int gui_src_action_setting(int action)
{
    struct intent it;
    struct application *app;

    init_intent(&it);
    app = get_current_app();

    printf("[chili] %s %d   \n", __func__, __LINE__);

    switch (action) {
    case GUI_SCREEN_ACTION_LOAD:
        def_group = lv_group_get_default();
        group_list = lv_group_create();
        lv_ui_sys_setting *ui_scr = ui_get_scr_ptr(&guider_ui, GUI_SCREEN_SYS_SETTING);
        if (!ui_scr) {
            return -1;
        }
        lv_group_add_obj(group_list, ui_scr->sys_setting_lbl_funkey4);
        lv_group_add_obj(group_list, ui_scr->sys_setting_lbl_funkey5);
        lv_group_add_obj(group_list, ui_scr->sys_setting_lbl_funkey6);
        lv_group_add_obj(group_list, ui_scr->sys_setting_lbl_funkey7);
        if (app) {
            printf("[chili] %s %d   \n", app->name, __LINE__);
            it.name = app->name;
            it.action = ACTION_BACK;
            start_app(&it);
        }
        it.name = "video_system";
        it.action = ACTION_SYSTEM_MAIN;
        start_app(&it);
        break;
    case GUI_SCREEN_ACTION_UNLOAD:
        group_list = NULL;

        break;
    }
}
REGISTER_UI_SCREEN_ACTION_HANDLER(GUI_SCREEN_SYS_SETTING)
.onchange = gui_src_action_setting,
};
extern void sys_prompt_show_ctl(int32_t show_time, void *tips);
void format_callback(void *p, int err)
{
    lv_ui_sys_prompt *ui_scr = ui_get_scr_ptr(&guider_ui, GUI_SCREEN_SYS_PROMPT);
    if (!ui_scr) {
        return;
    }
    lv_obj_add_flag(ui_scr->sys_prompt_img_warn, LV_OBJ_FLAG_CLICKABLE);
    if (err == 0) {
        lvgl_rpc_post_func(sys_prompt_show_ctl, 2, 3000, (void *)_("format_succ"));
    } else {
        lvgl_rpc_post_func(sys_prompt_show_ctl, 2, 3000, (void *)_("format_failed"));
    }
}
void video_system_format(void)
{
    //必须使用异步操作!!! 否则在格式化512GB大卡时，将卡住UI
    struct intent it;
    init_intent(&it);
    it.name = "video_system";
    it.action = ACTION_SYSTEM_SD_CARD_FORMAT;
    start_app_async(&it, format_callback, NULL);
}
#endif


#endif
