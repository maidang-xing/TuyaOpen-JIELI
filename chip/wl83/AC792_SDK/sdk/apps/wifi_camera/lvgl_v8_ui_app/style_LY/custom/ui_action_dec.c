#include "app_config.h"
#ifdef CONFIG_UI_STYLE_LY_ENABLE
#include "lvgl.h"
#include "custom.h"

#if !LV_USE_GUIBUILDER_SIMULATOR
#include "ui.h"
#include "sys_time.h"
#include "system/includes.h"
#include "asm/includes.h"
#include "syscfg/syscfg_id.h"
#include "action.h"

struct action_dec_hdl {
    u8 is_menu_show;
    u8 is_playing;
    u8 is_lock;
    u8 is_del_file;
};
static struct action_dec_hdl hdl = {0};
#define __this  (&hdl)

static lv_group_t *top_level_group;

extern void sys_prompt_show_ctl(int32_t show_time, void *tips);
static void dec_play_pause(void);

void gui_show_video_dec_options(void)
{
    lv_ui_video_dec_options *ui_scr = ui_get_scr_ptr(&guider_ui, GUI_SCREEN_VIDEO_DEC_OPTIONS);
    if (!ui_scr) {
        return;
    }
    if (ui_scr->video_dec_options_del == false && lv_obj_is_valid(ui_scr->video_dec_options)) {
        lv_obj_clear_flag(ui_scr->video_dec_options, LV_OBJ_FLAG_HIDDEN);
    } else {
        setup_scr_video_dec_options(&guider_ui);
        gui_msg_init_ui();
        gui_msg_init_events();
        delete_gui_timelines();
    }

    //按键导航
    top_level_group = lv_group_create();
    if (top_level_group) {
        lv_group_add_obj(top_level_group, ui_scr->video_dec_options_btn_1);
        lv_group_add_obj(top_level_group, ui_scr->video_dec_options_btn_2);
        lv_indev_t *indev = lv_indev_get_next(NULL);
        if (indev != NULL) {
            lv_indev_set_group(indev, top_level_group);
        }
    }
}

void gui_hide_video_dec_options(void)
{
    lv_ui_video_dec_options *ui_scr = ui_get_scr_ptr(&guider_ui, GUI_SCREEN_VIDEO_DEC_OPTIONS);
    if (!ui_scr) {
        return;
    }
    if (ui_scr->video_dec_options_del == false && lv_obj_is_valid(ui_scr->video_dec_options)) {
        lv_obj_add_flag(ui_scr->video_dec_options, LV_OBJ_FLAG_HIDDEN);
    }


    if (top_level_group) {
        lv_indev_t *indev = lv_indev_get_next(NULL);
        if (indev != NULL) {
            lv_indev_set_group(indev, lv_group_get_default());
        }

        lv_group_del(top_level_group);
        top_level_group = NULL;
    }

}

static void gui_set_options_lab(const char *lab)
{
    int ptr_size = 256;
    char *ptr = lvgl_module_msg_get_ptr(GUI_MODEL_VIDEO_DEC_MSG_ID_VIDEO_DEC_OPTIONS_LAB, ptr_size);
    if (ptr) {
        strcpy(ptr, lab);
        lvgl_module_msg_send_ptr(ptr, 0);
    }
}


void gui_video_dec_set_menu_show(void)
{
    __this->is_menu_show = 1;

    if (__this->is_playing) {
        dec_play_pause();
    }
}

void gui_video_dec_set_menu_hide(void)
{
    __this->is_menu_show = 0;
}

static void gui_video_dec_hide_menu(void)
{
    gui_hide_video_dec_options();
    lv_ui_video_dec *ui_scr = ui_get_scr_ptr(&guider_ui, GUI_SCREEN_VIDEO_DEC);
    if (!ui_scr) {
        return;
    }
    if (lv_obj_is_valid(ui_scr->video_dec_view_5)) {
        lv_obj_add_flag(ui_scr->video_dec_view_5, LV_OBJ_FLAG_HIDDEN);
        if (lv_obj_is_valid(ui_scr->video_dec_view_scan)) {
            lv_obj_clear_flag(ui_scr->video_dec_view_scan, LV_OBJ_FLAG_HIDDEN);
            lv_group_focus_obj(ui_scr->video_dec_view_scan);
        }
    }

    gui_video_dec_set_menu_hide();

}

void gui_video_dec_confirm_btn(void)
{
    struct intent *it = NULL;
    it = malloc(sizeof(struct intent));
    init_intent(it);

    it->exdata = video_dec_get_file_fd();

    if (__this->is_del_file) {
        it->data = "del:cur";
    } else {
        if (__this->is_lock) {
            //unlock
            it->data = "unlock:cur";
            __this->is_lock = 0;

        } else {
            //lock
            __this->is_lock = 1;
            it->data = "lock:cur";
        }
        lvgl_module_msg_send_value(GUI_MODEL_VIDEO_DEC_MSG_ID_FILE_LOCK_SHOW, __this->is_lock, 0);
    }

    app_send_message(APP_MSG_DEC_SET_CONFIG, 1, it);

    lvgl_rpc_post_func(gui_video_dec_hide_menu, 0);
}

void gui_video_dec_cancel_btn(void)
{
    lvgl_rpc_post_func(gui_hide_video_dec_options, 0);
}

void gui_video_dec_del_file(void)
{
    if (__this->is_lock) {
        sys_prompt_show_ctl(1500, (void *)_("file_is_lock"));
        return;
    }

    __this->is_del_file = 1;
    gui_set_options_lab((void *)_("del_file"));

    lvgl_rpc_post_func(gui_show_video_dec_options, 0);
}

void gui_video_dec_prot_file(void)
{
    __this->is_del_file = 0;

    if (__this->is_lock) {
        gui_set_options_lab((void *)_("unlock_file"));
    } else {
        gui_set_options_lab((void *)_("lock_file"));
    }

    lvgl_rpc_post_func(gui_show_video_dec_options, 0);
}

void gui_switch_video_dec_page(void)
{
#ifdef CONFIG_FILE_PREVIEW_ENABLE
    printf("load video dir page \n");
    gui_scr_t *screen = gui_scr_get(GUI_SCREEN_VIDEO_DIR);
    if (screen == NULL) {
        screen = gui_scr_create(GUI_SCREEN_VIDEO_DIR, "video_dir", guider_ui.video_dir, (gui_scr_setup_cb_t)setup_scr_video_dir, (gui_scr_unload_cb_t)unload_scr_video_dir);
    }
    ui_load_scr_anim(&guider_ui, screen, LV_SCR_LOAD_ANIM_NONE, 0, 0, true, true, false);
#else
    printf("load video dec page \n");
    gui_scr_t *screen = gui_scr_get(GUI_SCREEN_VIDEO_DEC);
    if (screen == NULL) {
        screen = gui_scr_create(GUI_SCREEN_VIDEO_DEC, "video_dec", guider_ui.video_dec, (gui_scr_setup_cb_t)setup_scr_video_dec, (gui_scr_unload_cb_t)unload_scr_video_dec);
    }
    ui_load_scr_anim(&guider_ui, screen, LV_SCR_LOAD_ANIM_NONE, 0, 0, true, true, false);


#endif /* CONFIG_FILE_PREVIEW_ENABLE */

}

static void video_dec_prev_next(u32 mode)
{
#if FILE_DISP_REVERSE_ORDER
    if (mode == FSEL_NEXT_FILE) {
        mode = FSEL_PREV_FILE;
    } else {
        mode = FSEL_NEXT_FILE;
    }
#endif
    struct intent *it = NULL;
    it = malloc(sizeof(struct intent));
    printf("it:%p", it);
    init_intent(it);
    it->exdata = mode;
    app_send_message(APP_MSG_DEC_PREV_NEXT_CONTROL, 1, it);
}

static void dec_play_pause(void)
{
    app_send_message(APP_MSG_DEC_CONTROL, 0);
}

static int fname_handler(const char *type, u32 arg)
{
    const char *fname = (const char *)arg;
    if (strstr(type, "ascii")) {
        char *ptr = lvgl_module_msg_get_ptr(GUI_MODEL_VIDEO_DEC_MSG_ID_FILE_NAME_LAB, strlen(fname) + 1);
        if (ptr) {
            strcpy(ptr, fname);
            lvgl_module_msg_send_ptr(ptr, 0);
        } else {
            return -1;
        }
    } else if (strstr(type, "utf16")) {
        return -1;
    }
    return 0;
}

static int no_card_handler(const char *type, u32 arg)
{
    lvgl_module_msg_send_value(GUI_MODEL_VIDEO_DEC_MSG_ID_SD_STATUS_IMG, 0, 0);
    lvgl_rpc_post_func(sys_prompt_show_ctl, 2, 3000, (void *)_("nosd"));

    if (__this->is_menu_show) {
        lvgl_rpc_post_func(gui_video_dec_hide_menu, 0);
    }
    return 0;
}

static int card_in_handler(const char *type, u32 arg)
{
    lvgl_module_msg_send_value(GUI_MODEL_VIDEO_DEC_MSG_ID_SD_STATUS_IMG, 1, 0);
    return 0;
}

static int no_file_handler(const char *type, u32 arg)
{
    lvgl_rpc_post_func(sys_prompt_show_ctl, 2, 1000, (void *)_("nofile"));
    return 0;
}

static int file_err_handler(const char *type, u32 arg)
{
    lvgl_rpc_post_func(sys_prompt_show_ctl, 2, 3000, (void *)_("fileerr"));
    return 0;
}

static void format_time(int total, int cur, char *str, size_t len)
{
    int cur_minutes = (cur % 3600) / 60;
    int cur_seconds = cur % 60;

    int minutes = (total % 3600) / 60;
    int seconds = total % 60;
    snprintf(str, len, "%02d:%02d / %02d:%02d", cur_minutes, cur_seconds, minutes, seconds);
}

static int info_handler(const char *type, int total_time, int w, int h, int file_type, int lock)
{
    printf("media info: total_time:%d w:%d h:%d type:%d lock:%d \n",
           total_time, w, h, file_type, lock);
    int lab_size = 32;
    char *video_time_ptr = lvgl_module_msg_get_ptr(GUI_MODEL_VIDEO_DEC_MSG_ID_VIDEO_TIME_LAB, lab_size);
    char *media_info_ptr = lvgl_module_msg_get_ptr(GUI_MODEL_VIDEO_DEC_MSG_ID_MEDIA_INFO_LAB, lab_size);

    __this->is_lock = lock;
    lvgl_module_msg_send_value(GUI_MODEL_VIDEO_DEC_MSG_ID_FILE_LOCK_SHOW, lock, 0);

    if (!video_time_ptr || !media_info_ptr) {
        printf("lvgl module err \n");
        return -1;
    }

    snprintf(media_info_ptr, lab_size, "%dx%d", w, h);

    if (file_type) {
        //jpeg
        lvgl_module_msg_send_value(GUI_MODEL_VIDEO_DEC_MSG_ID_FILE_TYPE_IMG, 1, 0);
        lvgl_module_msg_send_value(GUI_MODEL_VIDEO_DEC_MSG_ID_VIDEO_CONT_SHOW, 0, 0);
        memset(video_time_ptr, '\0', lab_size);
    } else {
        //avi
        lvgl_module_msg_send_value(GUI_MODEL_VIDEO_DEC_MSG_ID_FILE_TYPE_IMG, 0, 0);
        lvgl_module_msg_send_value(GUI_MODEL_VIDEO_DEC_MSG_ID_VIDEO_CONT_SHOW, 1, 0);
        format_time(total_time, 0, video_time_ptr, lab_size);
    }

    lvgl_module_msg_send_ptr(video_time_ptr, 0);
    lvgl_module_msg_send_ptr(media_info_ptr, 0);

    return 0;
}

static int play_time_handler(const char *type, int arg)
{
    int lab_size = 32;
    int total_time = video_dec_get_file_toltime();

    char *video_time_ptr = lvgl_module_msg_get_ptr(GUI_MODEL_VIDEO_DEC_MSG_ID_VIDEO_TIME_LAB, lab_size);

    if (!video_time_ptr) {
        printf("lvgl module err \n");
        return -1;
    }

    format_time(total_time, arg, video_time_ptr, lab_size);
    lvgl_module_msg_send_ptr(video_time_ptr, 0);
    return 0;
}

static int play_handler(const char *type, int arg)
{
    __this->is_playing = 1;
    lvgl_module_msg_send_value(GUI_MODEL_VIDEO_DEC_MSG_ID_PLAY_STATUS_IMG, 1, 0);
    return 0;
}

static int pause_handler(const char *type, int arg)
{
    __this->is_playing = 0;
    lvgl_module_msg_send_value(GUI_MODEL_VIDEO_DEC_MSG_ID_PLAY_STATUS_IMG, 0, 0);
    return 0;
}


#ifndef CONFIG_FILE_PREVIEW_ENABLE
void video_dec_post_msg(const char *msg, ...)
{
#ifdef USE_LVGL_V8_UI_DEMO
    va_list argptr;

    printf("[chili] %s %s   \n", __func__, msg);

    va_start(argptr, msg);

    if (strstr(msg, "noCard")) {
        no_card_handler(msg, va_arg(argptr, int));
    } else if (strstr(msg, "cardIn")) {
        card_in_handler(msg, va_arg(argptr, int));
    } else if (strstr(msg, "noFile")) {
        no_file_handler(msg, va_arg(argptr, int));
    } else if (strstr(msg, "fileErr")) {
        file_err_handler(msg, va_arg(argptr, int));
    } else if (strstr(msg, "end") || strstr(msg, "pause")) {
        pause_handler(msg, va_arg(argptr, int));
    } else if (strstr(msg, "play")) {
        play_handler(msg, va_arg(argptr, int));
    } else if (strstr(msg, "plyTime")) {
        play_time_handler(msg, va_arg(argptr, int));
    } else if (strstr(msg, "fname")) {
        fname_handler(msg, va_arg(argptr, int));
    } else if (strstr(msg, "fileInfo")) {
        int total_time = va_arg(argptr, int);
        int w = va_arg(argptr, int);
        int h = va_arg(argptr, int);
        int type = va_arg(argptr, int);
        int lock = va_arg(argptr, int);
        info_handler(msg, total_time, w, h, type, lock);
    } else {
        printf("[chili] %s your msg [%s] no callback! \n", __func__, msg, __LINE__);
    }

    va_end(argptr);

#endif
}

#endif /* !CONFIG_FILE_PREVIEW_ENABLE */


int gui_src_action_video_dec(int action)
{
    struct intent it;
    struct application *app;
    init_intent(&it);
    lv_ui_video_dec *ui_scr = ui_get_scr_ptr(&guider_ui, GUI_SCREEN_VIDEO_DEC);
    if (!ui_scr) {
        return -1;
    }
    switch (action) {
    case GUI_SCREEN_ACTION_LOAD: {
#if LV_DISP_UI_FB_NUM
        lv_obj_set_style_bg_opa(ui_scr->video_dec, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
#else
        lv_obj_set_style_bg_opa(ui_scr->video_dec, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
#endif
        app = get_current_app();
        if (app) {
            printf("[chili] %s %d   \n", app->name, __LINE__);
            key_event_disable();
            app_mode_go_back();
        } else {
            break;
        }
        app_mode_change_replace(APP_MODE_DEC);
        app_send_message(APP_MSG_DEC_MAIN, 0);

        key_event_enable();
    }
    break;
    case GUI_SCREEN_ACTION_UNLOAD:

        break;
    }
}
REGISTER_UI_SCREEN_ACTION_HANDLER(GUI_SCREEN_VIDEO_DEC)
.onchange = gui_src_action_video_dec,
};

int video_dec_key_handler(struct key_event *key)
{
    switch (key->action) {
    case KEY_EVENT_CLICK:
        switch (key->value) {
        case KEY_MENU:
            //K1
            break;
        case KEY_MODE:
            //K2
            break;
        case KEY_UP:
            //K3
            if (!__this->is_menu_show) {
                //play prev file
                //反序
                /* video_dec_prev_next(FSEL_NEXT_FILE); */
                return 1;
            }
            break;
        case KEY_DOWN:
            //K4
            if (!__this->is_menu_show) {
                //play next file
                //反序
                /* video_dec_prev_next(FSEL_PREV_FILE); */
                return 1;
            }
            break;
        case KEY_OK:
            //K5
            if (!__this->is_menu_show) {
                //play/pause
                /* video_dec_paly_pause(); */
                return 1;
            }
            break;
        default:
            break;
        }
    default:
        break;
    }

    return 0;
}
REGISTER_UI_KEY_EVENT_HANDLER(GUI_SCREEN_VIDEO_DEC)
.key_onchange = video_dec_key_handler,
};

int gui_model_video_dec_msg_sd_status_img_cb(gui_msg_action_t access, gui_msg_data_t *data, gui_msg_data_type_t type)
{
    if (access == GUI_MSG_ACCESS_SET) {

    } else if (access == GUI_MSG_ACCESS_GET) {
        data->value_int = storage_device_ready();
    }
    return 0;
}

REGISTER_UI_MODULE_EVENT_HANDLER(GUI_MODEL_VIDEO_DEC_MSG_ID_SD_STATUS_IMG)
.onchange = gui_model_video_dec_msg_sd_status_img_cb,
};




#endif /* LV_USE_GUIBUILDER_SIMULATOR */



#endif
