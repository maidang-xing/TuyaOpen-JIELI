#include "app_config.h"
#ifdef CONFIG_UI_STYLE_LY_ENABLE
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


void exit_sys_setting_menu(void)
{
    struct intent it;
    struct application *app;

    init_intent(&it);
    app = get_current_app();
    printf("current app name: %s\n", app->name);
    if (app && !strcmp(app->name, "video_rec")) {
        // printf("back video_rec\n");
        gui_scr_t *screen = gui_scr_get(GUI_SCREEN_VIDEO_REC);
        if (screen == NULL) {
            screen = gui_scr_create(GUI_SCREEN_VIDEO_REC, "video_rec", guider_ui.video_rec, (gui_scr_setup_cb_t)setup_scr_video_rec, (gui_scr_unload_cb_t)unload_scr_video_rec);
        }
        ui_load_scr_anim(&guider_ui, screen, LV_SCR_LOAD_ANIM_NONE, 0, 0, true, true, false);
    } else if (app && !strcmp(app->name, "video_photo")) {
        // printf("back video_photo\n");
        gui_scr_t *screen = gui_scr_get(GUI_SCREEN_VIDEO_PHOTO);
        if (screen == NULL) {
            screen = gui_scr_create(GUI_SCREEN_VIDEO_PHOTO, "video_photo", guider_ui.video_photo, (gui_scr_setup_cb_t)setup_scr_video_photo, (gui_scr_unload_cb_t)unload_scr_video_photo);
        }
        ui_load_scr_anim(&guider_ui, screen, LV_SCR_LOAD_ANIM_NONE, 0, 0, true, true, false);
    } else if (app && !strcmp(app->name, "video_dec")) {
#ifndef CONFIG_FILE_PREVIEW_ENABLE
        printf("load video dec page \n");
        gui_scr_t *screen = gui_scr_get(GUI_SCREEN_VIDEO_DEC);
        if (screen == NULL) {
            screen = gui_scr_create(GUI_SCREEN_VIDEO_DEC, "video_dec", guider_ui.video_dec, (gui_scr_setup_cb_t)setup_scr_video_dec, (gui_scr_unload_cb_t)unload_scr_video_dec);
        }
        ui_load_scr_anim(&guider_ui, screen, LV_SCR_LOAD_ANIM_NONE, 0, 0, true, true, false);
#endif /* CONFIG_FILE_PREVIEW_ENABLE */

    }
}

//注册页面加载卸载回调
int gui_src_action_setting(int action)
{
    switch (action) {
    case GUI_SCREEN_ACTION_LOAD:
        lv_ui_sys_setting *ui_scr = ui_get_scr_ptr(&guider_ui, GUI_SCREEN_SYS_SETTING);
        if (!ui_scr) {
            return -1;
        }
#if LV_DISP_UI_FB_NUM
        lv_obj_set_style_bg_opa(ui_scr->sys_setting, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
#else
        lv_obj_set_style_bg_opa(ui_scr->sys_setting, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
#endif
        break;
    case GUI_SCREEN_ACTION_UNLOAD:

        break;
    }
}
REGISTER_UI_SCREEN_ACTION_HANDLER(GUI_SCREEN_SYS_SETTING)
.onchange = gui_src_action_setting,
};


static int sys_app_back(void)
{

    struct intent it;
    int err;

    init_intent(&it);
    it.name	= "video_system";
    it.action = ACTION_BACK;
    it.data = NULL;
    err = start_app(&it);
    if (err) {
        printf("sys app back err! %d\n", err);
        /* ASSERT(err == 0, "sys back app fail.\n"); */
        return -1;
    }
    return 0;
}

static void format_cllback(void/* *priv, int err*/)
{
    sys_app_back();
    // printf("---->err: %d\n", err);
    // if (!err) {
    sys_prompt_show_ctl(200, (void *)_("format_succ"));
    // } else {
    // sys_prompt_show_ctl(200, (void *)_("format_failed"));
    // }
}

static void sys_menu_format(void)
{
    printf("------>%s()----->%d\n", __func__, __LINE__);
    struct intent it;
    init_intent(&it);

    it.name = "video_system";
    it.data = "frm";
    it.action = ACTION_SYSTEM_SET_CONFIG;
    // start_app_async(&it, format_cllback, NULL);
    start_app(&it);
    format_cllback();
}

#endif

void format_sdcard(void)
{
#if !LV_USE_GUIBUILDER_SIMULATOR

    if (!dev_online(SDX_DEV)) {
        sys_prompt_show_ctl(3000, (void *)_("nosd"));
        return;
    }

    if (fget_err_code(CONFIG_ROOT_PATH) == -EIO) {
        sys_prompt_show_ctl(3000, (void *)_("fs_err"));
    } else {

        extern unsigned char rec_running;
        printf(">>>>>>rec_running: %d\n", rec_running);
        if (rec_running) {
            rec_control_ontouch();
        }

#if 1
        int format_err = 0;
#if defined CONFIG_ENABLE_VLIST
        FILE_LIST_EXIT();
#endif

        format_err = sdcard_storage_device_format(SDX_DEV);
#if defined CONFIG_ENABLE_VLIST
        FILE_LIST_IN_MEM(1);
#endif
#ifdef CONFIG_WIFI_ENABLE
        net_video_rec_fmt_notify();
#endif

        if (format_err == 0) {
            sys_prompt_show_ctl(2000, (void *)_("format_succ"));
        } else {
            sys_prompt_show_ctl(3000, (void *)_("format_failed"));
        }
#else

        sys_prompt_show_ctl(10000, (void *)_("being_formatted"));
        sys_menu_format();
#endif

    }

#endif
}





#endif
