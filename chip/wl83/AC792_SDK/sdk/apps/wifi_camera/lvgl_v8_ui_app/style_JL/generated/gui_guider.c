#include "app_config.h"
#ifdef CONFIG_UI_STYLE_JL_ENABLE
/*Generate Code, Do NOT Edit!*/
#include "lvgl.h"
#if LV_USE_GUIBUILDER_SIMULATOR
#include <stdio.h>
#endif
#include "./gui_guider.h"
#include "./gui_timelines/gui_timelines.h"
#include "./gui_group/gui_group.h"
#include "./gui_events/events_init.h"

void scr_push_stack_loaded_handler(lv_event_t *e)
{
    int32_t scr_id = (int32_t)lv_event_get_user_data(e);
    lv_obj_t *src = lv_event_get_target(e);
    gui_scr_t *scr = ui_get_scr(scr_id);
    if (scr != NULL) {
        gui_scr_stack_push(scr);
    }
}
void ui_load_scr_anim(lv_ui *ui, gui_scr_t *screen, lv_scr_load_anim_t anim_type,	uint32_t time,
                      uint32_t delay, bool is_clean, bool auto_del, bool is_push_satck)
{
    if (screen == NULL) {
        return;
    }

    gui_scr_t *act_screen = gui_scr_get_act();
    if (act_screen == screen) {
        return;
    }

    gui_timelines_delete();
    gui_scr_set_act_anim(screen, ui, anim_type, time, delay, is_clean, auto_del);

    if (is_push_satck) {
        if (screen == gui_scr_get_act()) {
            gui_scr_stack_push(act_screen);
        } else {
            lv_obj_remove_event_cb(screen->scr, scr_push_stack_loaded_handler);
            lv_obj_add_event_cb(screen->scr, scr_push_stack_loaded_handler, LV_EVENT_SCREEN_LOADED, (void *)act_screen->id);
        }
    }
}

void ui_scr_stack_pop_anim(lv_ui *ui, lv_scr_load_anim_t anim_type, uint32_t time, uint32_t delay,
                           bool is_clean, bool auto_del, bool is_push_satck)
{
    gui_scr_t *screen = gui_scr_stack_pop();
    if (screen == NULL) {
        return;
    }

    ui_load_scr_anim(ui, screen, anim_type, time, delay, is_clean, auto_del, is_push_satck);
}

gui_scr_t *ui_get_scr(int32_t scr_id)
{
    gui_scr_t *screen = gui_scr_get(scr_id);
    if (screen != NULL) {
        return screen;
    }

    if (scr_id == GUI_SCREEN_USB_SLAVE) {
        return gui_scr_create(GUI_SCREEN_USB_SLAVE, "usb_slave", NULL, (gui_scr_setup_cb_t)setup_scr_usb_slave, (gui_scr_unload_cb_t)unload_scr_usb_slave);
    }
    if (scr_id == GUI_SCREEN_VIDEO_REC) {
        return gui_scr_create(GUI_SCREEN_VIDEO_REC, "video_rec", NULL, (gui_scr_setup_cb_t)setup_scr_video_rec, (gui_scr_unload_cb_t)unload_scr_video_rec);
    }
    if (scr_id == GUI_SCREEN_HOME_PAGE) {
        return gui_scr_create(GUI_SCREEN_HOME_PAGE, "home_page", NULL, (gui_scr_setup_cb_t)setup_scr_home_page, (gui_scr_unload_cb_t)unload_scr_home_page);
    }
    if (scr_id == GUI_SCREEN_SYS_PROMPT) {
        return gui_scr_create(GUI_SCREEN_SYS_PROMPT, "sys_prompt", NULL, (gui_scr_setup_cb_t)setup_scr_sys_prompt, (gui_scr_unload_cb_t)unload_scr_sys_prompt);
    }
    if (scr_id == GUI_SCREEN_SYS_SETTING) {
        return gui_scr_create(GUI_SCREEN_SYS_SETTING, "sys_setting", NULL, (gui_scr_setup_cb_t)setup_scr_sys_setting, (gui_scr_unload_cb_t)unload_scr_sys_setting);
    }
    if (scr_id == GUI_SCREEN_VIDEO_PHOTO) {
        return gui_scr_create(GUI_SCREEN_VIDEO_PHOTO, "video_photo", NULL, (gui_scr_setup_cb_t)setup_scr_video_photo, (gui_scr_unload_cb_t)unload_scr_video_photo);
    }
    if (scr_id == GUI_SCREEN_VIDEO_PLAY) {
        return gui_scr_create(GUI_SCREEN_VIDEO_PLAY, "video_play", NULL, (gui_scr_setup_cb_t)setup_scr_video_play, (gui_scr_unload_cb_t)unload_scr_video_play);
    }
    if (scr_id == GUI_SCREEN_VIDEO_FILE) {
        return gui_scr_create(GUI_SCREEN_VIDEO_FILE, "video_file", NULL, (gui_scr_setup_cb_t)setup_scr_video_file, (gui_scr_unload_cb_t)unload_scr_video_file);
    }
    if (scr_id == GUI_SCREEN_VIDEO_DIR) {
        return gui_scr_create(GUI_SCREEN_VIDEO_DIR, "video_dir", NULL, (gui_scr_setup_cb_t)setup_scr_video_dir, (gui_scr_unload_cb_t)unload_scr_video_dir);
    }
    if (scr_id == GUI_SCREEN_CAR_PARKING) {
        return gui_scr_create(GUI_SCREEN_CAR_PARKING, "car_parking", NULL, (gui_scr_setup_cb_t)setup_scr_car_parking, (gui_scr_unload_cb_t)unload_scr_car_parking);
    }
    if (scr_id == GUI_SCREEN_LINE_DRIFT) {
        return gui_scr_create(GUI_SCREEN_LINE_DRIFT, "line_drift", NULL, (gui_scr_setup_cb_t)setup_scr_line_drift, (gui_scr_unload_cb_t)unload_scr_line_drift);
    }
    if (scr_id == GUI_SCREEN_SYS_POPWIN) {
        return gui_scr_create(GUI_SCREEN_SYS_POPWIN, "sys_popwin", NULL, (gui_scr_setup_cb_t)setup_scr_sys_popwin, (gui_scr_unload_cb_t)unload_scr_sys_popwin);
    }
    return NULL;
}

gui_scr_t *ui_get_setup_scr(int32_t scr_id)
{
    gui_scr_t *screen = ui_get_scr(scr_id);
    if (screen == NULL) {
        return NULL;
    }

    if (screen->scr == NULL || lv_obj_is_valid(screen->scr) == false) {
        if (screen->setup_cb != NULL) {
            screen->scr = screen->setup_cb(&guider_ui);
            screen->is_del = false;
            if (screen->scr == NULL || lv_obj_is_valid(screen->scr) == false) {
                screen->is_del = true;
                return NULL;
            }
        }
    }
    return screen;
}

lv_obj_t *ui_get_setup_scr_obj(int32_t scr_id)
{
    gui_scr_t *screen = ui_get_setup_scr(scr_id);
    if (screen == NULL) {
        return NULL;
    }

    return screen->scr;
}


void *ui_get_scr_ptr(lv_ui *ui, int32_t scr_id)
{
    if (ui == NULL) {
        return NULL;
    }

    if (scr_id == GUI_SCREEN_USB_SLAVE) {
        return ui->usb_slave;
    }
    if (scr_id == GUI_SCREEN_VIDEO_REC) {
        return ui->video_rec;
    }
    if (scr_id == GUI_SCREEN_HOME_PAGE) {
        return ui->home_page;
    }
    if (scr_id == GUI_SCREEN_SYS_PROMPT) {
        return ui->sys_prompt;
    }
    if (scr_id == GUI_SCREEN_SYS_SETTING) {
        return ui->sys_setting;
    }
    if (scr_id == GUI_SCREEN_VIDEO_PHOTO) {
        return ui->video_photo;
    }
    if (scr_id == GUI_SCREEN_VIDEO_PLAY) {
        return ui->video_play;
    }
    if (scr_id == GUI_SCREEN_VIDEO_FILE) {
        return ui->video_file;
    }
    if (scr_id == GUI_SCREEN_VIDEO_DIR) {
        return ui->video_dir;
    }
    if (scr_id == GUI_SCREEN_CAR_PARKING) {
        return ui->car_parking;
    }
    if (scr_id == GUI_SCREEN_LINE_DRIFT) {
        return ui->line_drift;
    }
    if (scr_id == GUI_SCREEN_SYS_POPWIN) {
        return ui->sys_popwin;
    }
    return NULL;
}

void ui_free_scr_ptr(lv_ui *ui, int32_t scr_id)
{
    if (ui == NULL) {
        return;
    }

    if (scr_id == GUI_SCREEN_USB_SLAVE) {
        if (ui->usb_slave != NULL) {
            lv_mem_free(ui->usb_slave);
        }
        ui->usb_slave = NULL;
    }
    if (scr_id == GUI_SCREEN_VIDEO_REC) {
        if (ui->video_rec != NULL) {
            lv_mem_free(ui->video_rec);
        }
        ui->video_rec = NULL;
    }
    if (scr_id == GUI_SCREEN_HOME_PAGE) {
        if (ui->home_page != NULL) {
            lv_mem_free(ui->home_page);
        }
        ui->home_page = NULL;
    }
    if (scr_id == GUI_SCREEN_SYS_PROMPT) {
        if (ui->sys_prompt != NULL) {
            lv_mem_free(ui->sys_prompt);
        }
        ui->sys_prompt = NULL;
    }
    if (scr_id == GUI_SCREEN_SYS_SETTING) {
        if (ui->sys_setting != NULL) {
            lv_mem_free(ui->sys_setting);
        }
        ui->sys_setting = NULL;
    }
    if (scr_id == GUI_SCREEN_VIDEO_PHOTO) {
        if (ui->video_photo != NULL) {
            lv_mem_free(ui->video_photo);
        }
        ui->video_photo = NULL;
    }
    if (scr_id == GUI_SCREEN_VIDEO_PLAY) {
        if (ui->video_play != NULL) {
            lv_mem_free(ui->video_play);
        }
        ui->video_play = NULL;
    }
    if (scr_id == GUI_SCREEN_VIDEO_FILE) {
        if (ui->video_file != NULL) {
            lv_mem_free(ui->video_file);
        }
        ui->video_file = NULL;
    }
    if (scr_id == GUI_SCREEN_VIDEO_DIR) {
        if (ui->video_dir != NULL) {
            lv_mem_free(ui->video_dir);
        }
        ui->video_dir = NULL;
    }
    if (scr_id == GUI_SCREEN_CAR_PARKING) {
        if (ui->car_parking != NULL) {
            lv_mem_free(ui->car_parking);
        }
        ui->car_parking = NULL;
    }
    if (scr_id == GUI_SCREEN_LINE_DRIFT) {
        if (ui->line_drift != NULL) {
            lv_mem_free(ui->line_drift);
        }
        ui->line_drift = NULL;
    }
    if (scr_id == GUI_SCREEN_SYS_POPWIN) {
        if (ui->sys_popwin != NULL) {
            lv_mem_free(ui->sys_popwin);
        }
        ui->sys_popwin = NULL;
    }
    gui_scr_t *scr = gui_scr_get(scr_id);
    if (scr != NULL) {
        scr->scr = NULL;
    }
}

bool ui_is_act_scr(int32_t scr_id)
{
    return gui_scr_is_act(ui_get_scr(scr_id));
}

void ui_init_style(lv_style_t *style)
{
    if (style->prop_cnt > 1) {
        lv_style_reset(style);
    } else {
        lv_style_init(style);
    }
}


void setup_ui(lv_ui *ui)
{
    lv_i18n_init(lv_i18n_language_pack);
    lv_i18n_set_locale(lv_i18n_get_default_locale());
    init_gui_fonts();
    ui_style_init();
#if LV_USE_MSG
    gui_msg_init(ui);
#endif
    gui_group_init();
    ui_scr_manager_init();
    gui_scr_t *scr = ui_get_scr(GUI_SCREEN_VIDEO_REC);
    ui_load_scr_anim(ui, scr, LV_SCR_LOAD_ANIM_NONE, 0, 0, false, false, false);
    events_init(ui);
    gui_timelines_init(ui);
}
void clock_count_with_year(int *year, int *month, int *day, int *hour, int *min, int *sec)
{
    int days_in_month[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    if ((*year % 4 == 0 && *year % 100 != 0) || (*year % 400 == 0)) {
        days_in_month[1] = 29;
    }
    (*sec)++;
    if (*sec >= 60) {
        *sec = 0;
        (*min)++;
    }
    if (*min >= 60) {
        *min = 0;
        (*hour)++;
    }
    if (*hour >= 24) {
        *hour = 0;
        (*day)++;
    }
    if (*day > days_in_month[*month - 1]) {
        *day = 1;
        (*month)++;
        if (*month > 12) {
            *month = 1;
            (*year)++;
        }
    }
}

#endif
