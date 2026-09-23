#include "app_config.h"
#ifdef CONFIG_UI_STYLE_LY_ENABLE
/*Generate Code, Do NOT Edit!*/
#include "lvgl.h"
#if LV_USE_GUIBUILDER_SIMULATOR
#include <stdio.h>
#endif
#include <stdlib.h>
#include "../gui_guider.h"
#include "../gui_events/events_init.h"
#include "../gui_events/callback_handler.h"
#include "../gui_events/i18n_handler.h"
#include "../gui_timelines/gui_timelines.h"
#include "../../custom/custom.h"


lv_obj_t *setup_scr_video_dir(lv_ui *ui)
{
    lv_ui_video_dir *ui_scr = ui_get_scr_ptr(ui, GUI_SCREEN_VIDEO_DIR);
    if (ui_scr == NULL) {
        ui_scr = lv_mem_alloc(sizeof(lv_ui_video_dir));
        if (ui_scr == NULL) {
            return NULL;
        }
        memset(ui_scr, 0, sizeof(lv_ui_video_dir));
        ui->video_dir = ui_scr;
    }

    //Write codes video_dir
    ui_scr->video_dir = lv_obj_create(NULL);
    lv_obj_set_scrollbar_mode(ui_scr->video_dir, LV_SCROLLBAR_MODE_OFF);
    ui_style_set(ui_scr->video_dir, GUI_CTRL_SCR);

    //Set style for video_dir. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
    lv_obj_set_style_bg_opa(ui_scr->video_dir, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui_scr->video_dir, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

    //Write codes video_dir_view_1
    ui_scr->video_dir_view_1 = lv_obj_create(ui_scr->video_dir);
    lv_obj_set_pos(ui_scr->video_dir_view_1, 0, 0);
    lv_obj_set_size(ui_scr->video_dir_view_1, 800, 480);
    lv_obj_set_scrollbar_mode(ui_scr->video_dir_view_1, LV_SCROLLBAR_MODE_OFF);
    ui_style_set(ui_scr->video_dir_view_1, GUI_CTRL_CONT);

    //Set style for video_dir_view_1. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
    lv_obj_set_style_border_opa(ui_scr->video_dir_view_1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_outline_opa(ui_scr->video_dir_view_1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

    //Delete extra default style for video_dir_view_1
    lv_obj_remove_style(ui_scr->video_dir_view_1, &gui_cont_main_focus_key_style, LV_PART_MAIN | LV_STATE_FOCUS_KEY);

    //Write codes video_dir_lbl_path
    ui_scr->video_dir_lbl_path = lv_label_create(ui_scr->video_dir_view_1);
    lv_label_set_text(ui_scr->video_dir_lbl_path, "storage/sd0/C/DCIM/");
    lv_label_set_long_mode(ui_scr->video_dir_lbl_path, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui_scr->video_dir_lbl_path, 60, 10);
    lv_obj_set_size(ui_scr->video_dir_lbl_path, 666, 38);
    lv_obj_set_scrollbar_mode(ui_scr->video_dir_lbl_path, LV_SCROLLBAR_MODE_OFF);
    ui_style_set(ui_scr->video_dir_lbl_path, GUI_CTRL_LABEL);

    //Set style for video_dir_lbl_path. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
    lv_obj_set_style_text_color(ui_scr->video_dir_lbl_path, lv_color_make(0xFF, 0xFF, 0xFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_scr->video_dir_lbl_path, &lv_font_montserratMedium_22, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui_scr->video_dir_lbl_path, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui_scr->video_dir_lbl_path, 10, LV_PART_MAIN | LV_STATE_DEFAULT);

    lv_obj_update_layout(ui_scr->video_dir);
    ui_scr->video_dir_del = false;
    i18n_refresh_texts(GUI_SCREEN_VIDEO_DIR);

    //Init events for screen
    events_init_video_dir(ui);
    return ui_scr->video_dir;
}
void unload_scr_video_dir(lv_ui *ui)
{
    ui_free_scr_ptr(ui, GUI_SCREEN_VIDEO_DIR);
}

#endif
