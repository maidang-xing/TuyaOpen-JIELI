#include "app_config.h"
#ifdef CONFIG_UI_STYLE_JL_ENABLE
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


lv_obj_t *setup_scr_video_photo(lv_ui *ui)
{
    lv_ui_video_photo *ui_scr = ui_get_scr_ptr(ui, GUI_SCREEN_VIDEO_PHOTO);
    if (ui_scr == NULL) {
        ui_scr = lv_mem_alloc(sizeof(lv_ui_video_photo));
        memset(ui_scr, 0, sizeof(lv_ui_video_photo));
        ui->video_photo = ui_scr;
    }

    //Write codes video_photo
    ui_scr->video_photo = lv_obj_create(NULL);
    lv_group_t *def_group = lv_group_get_default();
    lv_obj_set_scrollbar_mode(ui_scr->video_photo, LV_SCROLLBAR_MODE_OFF);
    lv_obj_clear_flag(ui_scr->video_photo, LV_OBJ_FLAG_SCROLLABLE);
    ui_style_set(ui_scr->video_photo, GUI_CTRL_SCR);

    static bool timer_video_photo_digitclock_1_enabled = false;
    //Write codes video_photo_digitclock_1
    ui_scr->video_photo_digitclock_1 = lv_label_create(ui_scr->video_photo);
    lv_label_set_text_fmt(ui_scr->video_photo_digitclock_1, "%04d-%02d-%02d %02d:%02d:%02d", 2022, 07, 28, 21 % 12, 25, 50);
    lv_obj_set_style_text_align(ui_scr->video_photo_digitclock_1, LV_TEXT_ALIGN_CENTER, 0);
    lv_obj_set_pos(ui_scr->video_photo_digitclock_1, 60, 420);
    lv_obj_set_size(ui_scr->video_photo_digitclock_1, 343, 42);
    ui_style_set(ui_scr->video_photo_digitclock_1, GUI_CTRL_DIGITALCLOCK);

    //Delete extra default style for video_photo_digitclock_1
    lv_obj_remove_style(ui_scr->video_photo_digitclock_1, &gui_digitclock_main_disabled_style, LV_PART_MAIN | LV_STATE_DISABLED);

    //Write codes video_photo_imgbtn_2
    ui_scr->video_photo_imgbtn_2 = lv_imgbtn_create(ui_scr->video_photo);
    lv_obj_set_pos(ui_scr->video_photo_imgbtn_2, 604, 202);
    lv_obj_set_size(ui_scr->video_photo_imgbtn_2, 89, 86);
    lv_obj_set_scrollbar_mode(ui_scr->video_photo_imgbtn_2, LV_SCROLLBAR_MODE_OFF);
    lv_group_add_obj(def_group, ui_scr->video_photo_imgbtn_2);
    ui_style_set(ui_scr->video_photo_imgbtn_2, GUI_CTRL_IMGBTN);

    //Set style for video_photo_imgbtn_2. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
    lv_obj_set_style_radius(ui_scr->video_photo_imgbtn_2, 44, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui_scr->video_photo_imgbtn_2, true, LV_PART_MAIN | LV_STATE_DEFAULT);

    //Set style for video_photo_imgbtn_2. Part: LV_PART_MAIN, State: LV_STATE_FOCUS_KEY
    lv_obj_set_style_radius(ui_scr->video_photo_imgbtn_2, 44, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_clip_corner(ui_scr->video_photo_imgbtn_2, true, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_outline_width(ui_scr->video_photo_imgbtn_2, 4, LV_PART_MAIN | LV_STATE_FOCUS_KEY);

    //Set style for video_photo_imgbtn_2. Part: LV_PART_MAIN, State: LV_STATE_PRESSED
    lv_obj_set_style_radius(ui_scr->video_photo_imgbtn_2, 44, LV_PART_MAIN | LV_STATE_PRESSED);
    lv_obj_set_style_clip_corner(ui_scr->video_photo_imgbtn_2, true, LV_PART_MAIN | LV_STATE_PRESSED);

    //Set style for video_photo_imgbtn_2. Part: LV_PART_MAIN, State: LV_STATE_CHECKED
    lv_obj_set_style_radius(ui_scr->video_photo_imgbtn_2, 44, LV_PART_MAIN | LV_STATE_CHECKED);
    lv_obj_set_style_clip_corner(ui_scr->video_photo_imgbtn_2, true, LV_PART_MAIN | LV_STATE_CHECKED);
    lv_imgbtn_set_src(ui_scr->video_photo_imgbtn_2, LV_IMGBTN_STATE_RELEASED, NULL, gui_get_res_path(GUI_RES_PHOTO_BUTTON_PNG), NULL);
    lv_imgbtn_set_src(ui_scr->video_photo_imgbtn_2, LV_IMGBTN_STATE_PRESSED, NULL, gui_get_res_path(GUI_RES_PHOTO_BUTTON_ON_PNG), NULL);
    lv_imgbtn_set_src(ui_scr->video_photo_imgbtn_2, LV_IMGBTN_STATE_CHECKED_RELEASED, NULL, gui_get_res_path(GUI_RES_PHOTO_BUTTON_PNG), NULL);
    lv_imgbtn_set_src(ui_scr->video_photo_imgbtn_2, LV_IMGBTN_STATE_CHECKED_PRESSED, NULL, gui_get_res_path(GUI_RES_PHOTO_BUTTON_ON_PNG), NULL);
    lv_obj_add_flag(ui_scr->video_photo_imgbtn_2, LV_OBJ_FLAG_CHECKABLE);
    ui_scr->video_photo_imgbtn_2_label = lv_label_create(ui_scr->video_photo_imgbtn_2);
    lv_label_set_text(ui_scr->video_photo_imgbtn_2_label, "");
    lv_obj_set_style_pad_all(ui_scr->video_photo_imgbtn_2, 0, LV_STATE_DEFAULT);
    lv_obj_align(ui_scr->video_photo_imgbtn_2_label, LV_ALIGN_CENTER, 0, 0);

    //Write codes video_photo_imgbtn_1
    ui_scr->video_photo_imgbtn_1 = lv_imgbtn_create(ui_scr->video_photo);
    lv_obj_set_pos(ui_scr->video_photo_imgbtn_1, 615, 70);
    lv_obj_set_size(ui_scr->video_photo_imgbtn_1, 64, 64);
    lv_obj_set_scrollbar_mode(ui_scr->video_photo_imgbtn_1, LV_SCROLLBAR_MODE_OFF);
    lv_obj_add_flag(ui_scr->video_photo_imgbtn_1, LV_OBJ_FLAG_HIDDEN);
    lv_group_add_obj(def_group, ui_scr->video_photo_imgbtn_1);
    ui_style_set(ui_scr->video_photo_imgbtn_1, GUI_CTRL_IMGBTN);
    lv_imgbtn_set_src(ui_scr->video_photo_imgbtn_1, LV_IMGBTN_STATE_RELEASED, NULL, gui_get_res_path(GUI_RES_SWITCH_PNG), NULL);
    lv_imgbtn_set_src(ui_scr->video_photo_imgbtn_1, LV_IMGBTN_STATE_PRESSED, NULL, gui_get_res_path(GUI_RES_SWITCH_ON_PNG), NULL);
    lv_imgbtn_set_src(ui_scr->video_photo_imgbtn_1, LV_IMGBTN_STATE_CHECKED_RELEASED, NULL, gui_get_res_path(GUI_RES_SWITCH_PNG), NULL);
    lv_imgbtn_set_src(ui_scr->video_photo_imgbtn_1, LV_IMGBTN_STATE_CHECKED_PRESSED, NULL, gui_get_res_path(GUI_RES_SWITCH_ON_PNG), NULL);
    lv_obj_add_flag(ui_scr->video_photo_imgbtn_1, LV_OBJ_FLAG_CHECKABLE);
    ui_scr->video_photo_imgbtn_1_label = lv_label_create(ui_scr->video_photo_imgbtn_1);
    lv_label_set_text(ui_scr->video_photo_imgbtn_1_label, "");
    lv_obj_set_style_pad_all(ui_scr->video_photo_imgbtn_1, 0, LV_STATE_DEFAULT);
    lv_obj_align(ui_scr->video_photo_imgbtn_1_label, LV_ALIGN_CENTER, 0, 0);

    //Write codes video_photo_img_5
    ui_scr->video_photo_img_5 = lv_img_create(ui_scr->video_photo);
    lv_img_set_src(ui_scr->video_photo_img_5, gui_get_res_path(GUI_RES_TIMING_PHOTO_2_PNG));
    lv_img_set_pivot(ui_scr->video_photo_img_5, 0, 0);
    lv_img_set_angle(ui_scr->video_photo_img_5, 0);
    lv_img_set_zoom(ui_scr->video_photo_img_5, 256);
    lv_obj_set_pos(ui_scr->video_photo_img_5, 23, 15);
    lv_obj_set_size(ui_scr->video_photo_img_5, 48, 48);
    lv_obj_add_flag(ui_scr->video_photo_img_5, LV_OBJ_FLAG_HIDDEN);
    lv_obj_add_flag(ui_scr->video_photo_img_5, LV_OBJ_FLAG_CLICKABLE);
    ui_style_set(ui_scr->video_photo_img_5, GUI_CTRL_IMG);

    //Delete extra default style for video_photo_img_5
    lv_obj_remove_style(ui_scr->video_photo_img_5, &gui_img_main_focus_key_style, LV_PART_MAIN | LV_STATE_FOCUS_KEY);

    //Write codes video_photo_img_7
    ui_scr->video_photo_img_7 = lv_img_create(ui_scr->video_photo);
    lv_img_set_src(ui_scr->video_photo_img_7, gui_get_res_path(GUI_RES_CONTINUOUS_PNG));
    lv_img_set_pivot(ui_scr->video_photo_img_7, 0, 0);
    lv_img_set_angle(ui_scr->video_photo_img_7, 0);
    lv_img_set_zoom(ui_scr->video_photo_img_7, 256);
    lv_obj_set_pos(ui_scr->video_photo_img_7, 80, 15);
    lv_obj_set_size(ui_scr->video_photo_img_7, 48, 48);
    lv_obj_add_flag(ui_scr->video_photo_img_7, LV_OBJ_FLAG_CLICKABLE);
    ui_style_set(ui_scr->video_photo_img_7, GUI_CTRL_IMG);

    //Delete extra default style for video_photo_img_7
    lv_obj_remove_style(ui_scr->video_photo_img_7, &gui_img_main_focus_key_style, LV_PART_MAIN | LV_STATE_FOCUS_KEY);

    //Write codes video_photo_img_8
    ui_scr->video_photo_img_8 = lv_img_create(ui_scr->video_photo);
    lv_img_set_src(ui_scr->video_photo_img_8, gui_get_res_path(GUI_RES_HAND_SHAKE_PNG));
    lv_img_set_pivot(ui_scr->video_photo_img_8, 0, 0);
    lv_img_set_angle(ui_scr->video_photo_img_8, 0);
    lv_img_set_zoom(ui_scr->video_photo_img_8, 256);
    lv_obj_set_pos(ui_scr->video_photo_img_8, 134, 15);
    lv_obj_set_size(ui_scr->video_photo_img_8, 48, 48);
    lv_obj_add_flag(ui_scr->video_photo_img_8, LV_OBJ_FLAG_CLICKABLE);
    ui_style_set(ui_scr->video_photo_img_8, GUI_CTRL_IMG);

    //Delete extra default style for video_photo_img_8
    lv_obj_remove_style(ui_scr->video_photo_img_8, &gui_img_main_focus_key_style, LV_PART_MAIN | LV_STATE_FOCUS_KEY);

    //Write codes video_photo_img_9
    ui_scr->video_photo_img_9 = lv_img_create(ui_scr->video_photo);
    lv_img_set_src(ui_scr->video_photo_img_9, gui_get_res_path(GUI_RES_SD_PNG));
    lv_img_set_pivot(ui_scr->video_photo_img_9, 0, 0);
    lv_img_set_angle(ui_scr->video_photo_img_9, 0);
    lv_img_set_zoom(ui_scr->video_photo_img_9, 256);
    lv_obj_set_pos(ui_scr->video_photo_img_9, 191, 15);
    lv_obj_set_size(ui_scr->video_photo_img_9, 45, 45);
    lv_obj_add_flag(ui_scr->video_photo_img_9, LV_OBJ_FLAG_CLICKABLE);
    ui_style_set(ui_scr->video_photo_img_9, GUI_CTRL_IMG);

    //Delete extra default style for video_photo_img_9
    lv_obj_remove_style(ui_scr->video_photo_img_9, &gui_img_main_focus_key_style, LV_PART_MAIN | LV_STATE_FOCUS_KEY);

    //Write codes video_photo_img_12
    ui_scr->video_photo_img_12 = lv_img_create(ui_scr->video_photo);
    lv_img_set_src(ui_scr->video_photo_img_12, gui_get_res_path(GUI_RES_FULL_PNG));
    lv_img_set_pivot(ui_scr->video_photo_img_12, 0, 0);
    lv_img_set_angle(ui_scr->video_photo_img_12, 0);
    lv_img_set_zoom(ui_scr->video_photo_img_12, 256);
    lv_obj_set_pos(ui_scr->video_photo_img_12, 22, 420);
    lv_obj_set_size(ui_scr->video_photo_img_12, 48, 48);
    lv_obj_add_flag(ui_scr->video_photo_img_12, LV_OBJ_FLAG_CLICKABLE);
    ui_style_set(ui_scr->video_photo_img_12, GUI_CTRL_IMG);

    //Delete extra default style for video_photo_img_12
    lv_obj_remove_style(ui_scr->video_photo_img_12, &gui_img_main_focus_key_style, LV_PART_MAIN | LV_STATE_FOCUS_KEY);

    //Write codes video_photo_lbl_2
    ui_scr->video_photo_lbl_2 = lv_label_create(ui_scr->video_photo);
    lv_label_set_text(ui_scr->video_photo_lbl_2, "1M");
    lv_label_set_long_mode(ui_scr->video_photo_lbl_2, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui_scr->video_photo_lbl_2, 22, 136);
    lv_obj_set_size(ui_scr->video_photo_lbl_2, 48, 48);
    lv_obj_set_scrollbar_mode(ui_scr->video_photo_lbl_2, LV_SCROLLBAR_MODE_OFF);
    ui_style_set(ui_scr->video_photo_lbl_2, GUI_CTRL_LABEL);

    //Set style for video_photo_lbl_2. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
    lv_obj_set_style_radius(ui_scr->video_photo_lbl_2, 24, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui_scr->video_photo_lbl_2, lv_color_make(0xEA, 0xEE, 0xF1), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_scr->video_photo_lbl_2, 77, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui_scr->video_photo_lbl_2, 15, LV_PART_MAIN | LV_STATE_DEFAULT);

    //Write codes video_photo_lbl_3
    ui_scr->video_photo_lbl_3 = lv_label_create(ui_scr->video_photo);
    lv_label_set_text(ui_scr->video_photo_lbl_3, "ISO\n100");
    lv_label_set_long_mode(ui_scr->video_photo_lbl_3, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui_scr->video_photo_lbl_3, 22, 202);
    lv_obj_set_size(ui_scr->video_photo_lbl_3, 48, 48);
    lv_obj_set_scrollbar_mode(ui_scr->video_photo_lbl_3, LV_SCROLLBAR_MODE_OFF);
    ui_style_set(ui_scr->video_photo_lbl_3, GUI_CTRL_LABEL);

    //Set style for video_photo_lbl_3. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
    lv_obj_set_style_radius(ui_scr->video_photo_lbl_3, 24, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui_scr->video_photo_lbl_3, lv_color_make(0xEA, 0xEE, 0xF1), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_scr->video_photo_lbl_3, 77, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_scr->video_photo_lbl_3, &lv_font_FangZhengKaiTiJianTi_1_14, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui_scr->video_photo_lbl_3, 1, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui_scr->video_photo_lbl_3, 10, LV_PART_MAIN | LV_STATE_DEFAULT);

    //Write codes video_photo_lbl_4
    ui_scr->video_photo_lbl_4 = lv_label_create(ui_scr->video_photo);
    lv_label_set_text(ui_scr->video_photo_lbl_4, "remain");
    lv_label_set_long_mode(ui_scr->video_photo_lbl_4, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui_scr->video_photo_lbl_4, 269, 15);
    lv_obj_set_size(ui_scr->video_photo_lbl_4, 269, 52);
    lv_obj_set_scrollbar_mode(ui_scr->video_photo_lbl_4, LV_SCROLLBAR_MODE_OFF);
    ui_style_set(ui_scr->video_photo_lbl_4, GUI_CTRL_LABEL);

    //Set style for video_photo_lbl_4. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
    lv_obj_set_style_text_font(ui_scr->video_photo_lbl_4, &lv_font_FangZhengKaiTiJianTi_1_24, LV_PART_MAIN | LV_STATE_DEFAULT);

    //Write codes video_photo_view_1
    ui_scr->video_photo_view_1 = lv_obj_create(ui_scr->video_photo);
    lv_obj_set_pos(ui_scr->video_photo_view_1, 725, 0);
    lv_obj_set_size(ui_scr->video_photo_view_1, 80, 480);
    lv_obj_set_scrollbar_mode(ui_scr->video_photo_view_1, LV_SCROLLBAR_MODE_OFF);
    ui_style_set(ui_scr->video_photo_view_1, GUI_CTRL_CONT);

    //Set style for video_photo_view_1. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
    lv_obj_set_style_bg_color(ui_scr->video_photo_view_1, lv_color_make(0x31, 0x2B, 0x2B), LV_PART_MAIN | LV_STATE_DEFAULT);

    //Write codes video_photo_img_video_set
    ui_scr->video_photo_img_video_set = lv_img_create(ui_scr->video_photo);
    lv_img_set_src(ui_scr->video_photo_img_video_set, gui_get_res_path(GUI_RES_SETTING_PNG));
    lv_img_set_pivot(ui_scr->video_photo_img_video_set, 0, 0);
    lv_img_set_angle(ui_scr->video_photo_img_video_set, 0);
    lv_img_set_zoom(ui_scr->video_photo_img_video_set, 256);
    lv_obj_set_pos(ui_scr->video_photo_img_video_set, 742, 124);
    lv_obj_set_size(ui_scr->video_photo_img_video_set, 48, 48);
    lv_group_add_obj(def_group, ui_scr->video_photo_img_video_set);
    lv_obj_add_flag(ui_scr->video_photo_img_video_set, LV_OBJ_FLAG_CLICKABLE);
    ui_style_set(ui_scr->video_photo_img_video_set, GUI_CTRL_IMG);

    //Set style for video_photo_img_video_set. Part: LV_PART_MAIN, State: LV_STATE_FOCUSED
    lv_obj_add_style(ui_scr->video_photo_img_video_set, &gui_img_main_focused_style, LV_PART_MAIN | LV_STATE_FOCUSED);

    //Write codes video_photo_img_15
    ui_scr->video_photo_img_15 = lv_img_create(ui_scr->video_photo);
    lv_img_set_src(ui_scr->video_photo_img_15, gui_get_res_path(GUI_RES_VIDEO_3_PNG));
    lv_img_set_pivot(ui_scr->video_photo_img_15, 0, 0);
    lv_img_set_angle(ui_scr->video_photo_img_15, 0);
    lv_img_set_zoom(ui_scr->video_photo_img_15, 256);
    lv_obj_set_pos(ui_scr->video_photo_img_15, 742, 232);
    lv_obj_set_size(ui_scr->video_photo_img_15, 48, 48);
    lv_group_add_obj(def_group, ui_scr->video_photo_img_15);
    lv_obj_add_flag(ui_scr->video_photo_img_15, LV_OBJ_FLAG_CLICKABLE);
    ui_style_set(ui_scr->video_photo_img_15, GUI_CTRL_IMG);

    //Set style for video_photo_img_15. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
    lv_obj_set_style_img_recolor(ui_scr->video_photo_img_15, lv_color_make(0xFF, 0xEB, 0x3D), LV_PART_MAIN | LV_STATE_DEFAULT);

    //Set style for video_photo_img_15. Part: LV_PART_MAIN, State: LV_STATE_FOCUSED
    lv_obj_add_style(ui_scr->video_photo_img_15, &gui_img_main_focused_style, LV_PART_MAIN | LV_STATE_FOCUSED);

    //Write codes video_photo_img_home
    ui_scr->video_photo_img_home = lv_img_create(ui_scr->video_photo);
    lv_img_set_src(ui_scr->video_photo_img_home, gui_get_res_path(GUI_RES_HOME_PNG));
    lv_img_set_pivot(ui_scr->video_photo_img_home, 0, 0);
    lv_img_set_angle(ui_scr->video_photo_img_home, 0);
    lv_img_set_zoom(ui_scr->video_photo_img_home, 256);
    lv_obj_set_pos(ui_scr->video_photo_img_home, 742, 339);
    lv_obj_set_size(ui_scr->video_photo_img_home, 48, 48);
    lv_group_add_obj(def_group, ui_scr->video_photo_img_home);
    lv_obj_add_flag(ui_scr->video_photo_img_home, LV_OBJ_FLAG_CLICKABLE);
    ui_style_set(ui_scr->video_photo_img_home, GUI_CTRL_IMG);

    //Set style for video_photo_img_home. Part: LV_PART_MAIN, State: LV_STATE_FOCUSED
    lv_obj_add_style(ui_scr->video_photo_img_home, &gui_img_main_focused_style, LV_PART_MAIN | LV_STATE_FOCUSED);
    lv_obj_set_style_outline_pad(ui_scr->video_photo_img_home, 0, LV_PART_MAIN | LV_STATE_FOCUSED);

    //Write codes video_photo_view_video_set
    ui_scr->video_photo_view_video_set = lv_obj_create(ui_scr->video_photo);
    lv_obj_set_pos(ui_scr->video_photo_view_video_set, 295, 0);
    lv_obj_set_size(ui_scr->video_photo_view_video_set, 430, 480);
    lv_obj_set_scrollbar_mode(ui_scr->video_photo_view_video_set, LV_SCROLLBAR_MODE_OFF);
    lv_obj_add_flag(ui_scr->video_photo_view_video_set, LV_OBJ_FLAG_HIDDEN);
    ui_style_set(ui_scr->video_photo_view_video_set, GUI_CTRL_CONT);

    //Set style for video_photo_view_video_set. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
    lv_obj_set_style_bg_color(ui_scr->video_photo_view_video_set, lv_color_make(0x00, 0x00, 0x00), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_scr->video_photo_view_video_set, 179, LV_PART_MAIN | LV_STATE_DEFAULT);

    //Write codes video_photo_img_resolution
    ui_scr->video_photo_img_resolution = lv_img_create(ui_scr->video_photo_view_video_set);
    lv_img_set_src(ui_scr->video_photo_img_resolution, gui_get_res_path(GUI_RES_RESOLUTION_RATIO_PNG));
    lv_img_set_pivot(ui_scr->video_photo_img_resolution, 0, 0);
    lv_img_set_angle(ui_scr->video_photo_img_resolution, 0);
    lv_img_set_zoom(ui_scr->video_photo_img_resolution, 256);
    lv_obj_set_pos(ui_scr->video_photo_img_resolution, 31, 36);
    lv_obj_set_size(ui_scr->video_photo_img_resolution, 80, 80);
    lv_obj_add_flag(ui_scr->video_photo_img_resolution, LV_OBJ_FLAG_EVENT_BUBBLE);
    lv_group_add_obj(def_group, ui_scr->video_photo_img_resolution);
    lv_obj_add_flag(ui_scr->video_photo_img_resolution, LV_OBJ_FLAG_CLICKABLE);
    ui_style_set(ui_scr->video_photo_img_resolution, GUI_CTRL_IMG);

    //Write codes video_photo_img_19
    ui_scr->video_photo_img_19 = lv_img_create(ui_scr->video_photo_view_video_set);
    lv_img_set_src(ui_scr->video_photo_img_19, gui_get_res_path(GUI_RES_TIMING_PHOTO_PNG));
    lv_img_set_pivot(ui_scr->video_photo_img_19, 0, 0);
    lv_img_set_angle(ui_scr->video_photo_img_19, 0);
    lv_img_set_zoom(ui_scr->video_photo_img_19, 256);
    lv_obj_set_pos(ui_scr->video_photo_img_19, 133, 36);
    lv_obj_set_size(ui_scr->video_photo_img_19, 80, 80);
    lv_obj_add_flag(ui_scr->video_photo_img_19, LV_OBJ_FLAG_EVENT_BUBBLE);
    lv_group_add_obj(def_group, ui_scr->video_photo_img_19);
    lv_obj_add_flag(ui_scr->video_photo_img_19, LV_OBJ_FLAG_CLICKABLE);
    ui_style_set(ui_scr->video_photo_img_19, GUI_CTRL_IMG);

    //Write codes video_photo_img_20
    ui_scr->video_photo_img_20 = lv_img_create(ui_scr->video_photo_view_video_set);
    lv_img_set_src(ui_scr->video_photo_img_20, gui_get_res_path(GUI_RES_CONTINUOUS_PHOTO_PNG));
    lv_img_set_pivot(ui_scr->video_photo_img_20, 0, 0);
    lv_img_set_angle(ui_scr->video_photo_img_20, 0);
    lv_img_set_zoom(ui_scr->video_photo_img_20, 256);
    lv_obj_set_pos(ui_scr->video_photo_img_20, 235, 36);
    lv_obj_set_size(ui_scr->video_photo_img_20, 80, 80);
    lv_obj_add_flag(ui_scr->video_photo_img_20, LV_OBJ_FLAG_EVENT_BUBBLE);
    lv_group_add_obj(def_group, ui_scr->video_photo_img_20);
    lv_obj_add_flag(ui_scr->video_photo_img_20, LV_OBJ_FLAG_CLICKABLE);
    ui_style_set(ui_scr->video_photo_img_20, GUI_CTRL_IMG);

    //Write codes video_photo_img_21
    ui_scr->video_photo_img_21 = lv_img_create(ui_scr->video_photo_view_video_set);
    lv_img_set_src(ui_scr->video_photo_img_21, gui_get_res_path(GUI_RES_PHOTO_QUALITY_PNG));
    lv_img_set_pivot(ui_scr->video_photo_img_21, 0, 0);
    lv_img_set_angle(ui_scr->video_photo_img_21, 0);
    lv_img_set_zoom(ui_scr->video_photo_img_21, 256);
    lv_obj_set_pos(ui_scr->video_photo_img_21, 338, 36);
    lv_obj_set_size(ui_scr->video_photo_img_21, 80, 80);
    lv_obj_add_flag(ui_scr->video_photo_img_21, LV_OBJ_FLAG_EVENT_BUBBLE);
    lv_group_add_obj(def_group, ui_scr->video_photo_img_21);
    lv_obj_add_flag(ui_scr->video_photo_img_21, LV_OBJ_FLAG_CLICKABLE);
    ui_style_set(ui_scr->video_photo_img_21, GUI_CTRL_IMG);

    //Write codes video_photo_lbl_5
    ui_scr->video_photo_lbl_5 = lv_label_create(ui_scr->video_photo_view_video_set);
    lv_label_set_long_mode(ui_scr->video_photo_lbl_5, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui_scr->video_photo_lbl_5, 31, 123);
    lv_obj_set_size(ui_scr->video_photo_lbl_5, 72, 53);
    lv_obj_set_scrollbar_mode(ui_scr->video_photo_lbl_5, LV_SCROLLBAR_MODE_OFF);
    ui_style_set(ui_scr->video_photo_lbl_5, GUI_CTRL_LABEL);

    //Write codes video_photo_lbl_6
    ui_scr->video_photo_lbl_6 = lv_label_create(ui_scr->video_photo_view_video_set);
    lv_label_set_long_mode(ui_scr->video_photo_lbl_6, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui_scr->video_photo_lbl_6, 133, 123);
    lv_obj_set_size(ui_scr->video_photo_lbl_6, 72, 53);
    lv_obj_set_scrollbar_mode(ui_scr->video_photo_lbl_6, LV_SCROLLBAR_MODE_OFF);
    ui_style_set(ui_scr->video_photo_lbl_6, GUI_CTRL_LABEL);

    //Write codes video_photo_lbl_7
    ui_scr->video_photo_lbl_7 = lv_label_create(ui_scr->video_photo_view_video_set);
    lv_label_set_long_mode(ui_scr->video_photo_lbl_7, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui_scr->video_photo_lbl_7, 235, 123);
    lv_obj_set_size(ui_scr->video_photo_lbl_7, 72, 53);
    lv_obj_set_scrollbar_mode(ui_scr->video_photo_lbl_7, LV_SCROLLBAR_MODE_OFF);
    ui_style_set(ui_scr->video_photo_lbl_7, GUI_CTRL_LABEL);

    //Write codes video_photo_lbl_8
    ui_scr->video_photo_lbl_8 = lv_label_create(ui_scr->video_photo_view_video_set);
    lv_label_set_long_mode(ui_scr->video_photo_lbl_8, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui_scr->video_photo_lbl_8, 342, 123);
    lv_obj_set_size(ui_scr->video_photo_lbl_8, 72, 53);
    lv_obj_set_scrollbar_mode(ui_scr->video_photo_lbl_8, LV_SCROLLBAR_MODE_OFF);
    ui_style_set(ui_scr->video_photo_lbl_8, GUI_CTRL_LABEL);

    //Write codes video_photo_img_1
    ui_scr->video_photo_img_1 = lv_img_create(ui_scr->video_photo_view_video_set);
    lv_img_set_src(ui_scr->video_photo_img_1, gui_get_res_path(GUI_RES_ACUITY_PNG));
    lv_img_set_pivot(ui_scr->video_photo_img_1, 0, 0);
    lv_img_set_angle(ui_scr->video_photo_img_1, 0);
    lv_img_set_zoom(ui_scr->video_photo_img_1, 256);
    lv_obj_set_pos(ui_scr->video_photo_img_1, 31, 183);
    lv_obj_set_size(ui_scr->video_photo_img_1, 80, 80);
    lv_obj_add_flag(ui_scr->video_photo_img_1, LV_OBJ_FLAG_EVENT_BUBBLE);
    lv_group_add_obj(def_group, ui_scr->video_photo_img_1);
    lv_obj_add_flag(ui_scr->video_photo_img_1, LV_OBJ_FLAG_CLICKABLE);
    ui_style_set(ui_scr->video_photo_img_1, GUI_CTRL_IMG);

    //Write codes video_photo_img_10
    ui_scr->video_photo_img_10 = lv_img_create(ui_scr->video_photo_view_video_set);
    lv_img_set_src(ui_scr->video_photo_img_10, gui_get_res_path(GUI_RES_AWB_PNG));
    lv_img_set_pivot(ui_scr->video_photo_img_10, 0, 0);
    lv_img_set_angle(ui_scr->video_photo_img_10, 0);
    lv_img_set_zoom(ui_scr->video_photo_img_10, 256);
    lv_obj_set_pos(ui_scr->video_photo_img_10, 133, 183);
    lv_obj_set_size(ui_scr->video_photo_img_10, 80, 80);
    lv_obj_add_flag(ui_scr->video_photo_img_10, LV_OBJ_FLAG_EVENT_BUBBLE);
    lv_group_add_obj(def_group, ui_scr->video_photo_img_10);
    lv_obj_add_flag(ui_scr->video_photo_img_10, LV_OBJ_FLAG_CLICKABLE);
    ui_style_set(ui_scr->video_photo_img_10, GUI_CTRL_IMG);

    //Write codes video_photo_img_17
    ui_scr->video_photo_img_17 = lv_img_create(ui_scr->video_photo_view_video_set);
    lv_img_set_src(ui_scr->video_photo_img_17, gui_get_res_path(GUI_RES_COLOR_PNG));
    lv_img_set_pivot(ui_scr->video_photo_img_17, 0, 0);
    lv_img_set_angle(ui_scr->video_photo_img_17, 0);
    lv_img_set_zoom(ui_scr->video_photo_img_17, 256);
    lv_obj_set_pos(ui_scr->video_photo_img_17, 235, 183);
    lv_obj_set_size(ui_scr->video_photo_img_17, 80, 80);
    lv_obj_add_flag(ui_scr->video_photo_img_17, LV_OBJ_FLAG_EVENT_BUBBLE);
    lv_group_add_obj(def_group, ui_scr->video_photo_img_17);
    lv_obj_add_flag(ui_scr->video_photo_img_17, LV_OBJ_FLAG_CLICKABLE);
    ui_style_set(ui_scr->video_photo_img_17, GUI_CTRL_IMG);

    //Write codes video_photo_img_18
    ui_scr->video_photo_img_18 = lv_img_create(ui_scr->video_photo_view_video_set);
    lv_img_set_src(ui_scr->video_photo_img_18, gui_get_res_path(GUI_RES_ISO_PNG));
    lv_img_set_pivot(ui_scr->video_photo_img_18, 0, 0);
    lv_img_set_angle(ui_scr->video_photo_img_18, 0);
    lv_img_set_zoom(ui_scr->video_photo_img_18, 256);
    lv_obj_set_pos(ui_scr->video_photo_img_18, 338, 183);
    lv_obj_set_size(ui_scr->video_photo_img_18, 80, 80);
    lv_obj_add_flag(ui_scr->video_photo_img_18, LV_OBJ_FLAG_EVENT_BUBBLE);
    lv_group_add_obj(def_group, ui_scr->video_photo_img_18);
    lv_obj_add_flag(ui_scr->video_photo_img_18, LV_OBJ_FLAG_CLICKABLE);
    ui_style_set(ui_scr->video_photo_img_18, GUI_CTRL_IMG);

    //Write codes video_photo_lbl_13
    ui_scr->video_photo_lbl_13 = lv_label_create(ui_scr->video_photo_view_video_set);
    lv_label_set_long_mode(ui_scr->video_photo_lbl_13, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui_scr->video_photo_lbl_13, 22, 264);
    lv_obj_set_size(ui_scr->video_photo_lbl_13, 90, 53);
    lv_obj_set_scrollbar_mode(ui_scr->video_photo_lbl_13, LV_SCROLLBAR_MODE_OFF);
    ui_style_set(ui_scr->video_photo_lbl_13, GUI_CTRL_LABEL);

    //Write codes video_photo_lbl_14
    ui_scr->video_photo_lbl_14 = lv_label_create(ui_scr->video_photo_view_video_set);
    lv_label_set_long_mode(ui_scr->video_photo_lbl_14, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui_scr->video_photo_lbl_14, 31, 413);
    lv_obj_set_size(ui_scr->video_photo_lbl_14, 72, 53);
    lv_obj_set_scrollbar_mode(ui_scr->video_photo_lbl_14, LV_SCROLLBAR_MODE_OFF);
    ui_style_set(ui_scr->video_photo_lbl_14, GUI_CTRL_LABEL);

    //Write codes video_photo_img_3
    ui_scr->video_photo_img_3 = lv_img_create(ui_scr->video_photo_view_video_set);
    lv_img_set_src(ui_scr->video_photo_img_3, gui_get_res_path(GUI_RES_EXPOSURE_PNG));
    lv_img_set_pivot(ui_scr->video_photo_img_3, 0, 0);
    lv_img_set_angle(ui_scr->video_photo_img_3, 0);
    lv_img_set_zoom(ui_scr->video_photo_img_3, 256);
    lv_obj_set_pos(ui_scr->video_photo_img_3, 31, 330);
    lv_obj_set_size(ui_scr->video_photo_img_3, 80, 80);
    lv_obj_add_flag(ui_scr->video_photo_img_3, LV_OBJ_FLAG_EVENT_BUBBLE);
    lv_group_add_obj(def_group, ui_scr->video_photo_img_3);
    lv_obj_add_flag(ui_scr->video_photo_img_3, LV_OBJ_FLAG_CLICKABLE);
    ui_style_set(ui_scr->video_photo_img_3, GUI_CTRL_IMG);

    //Write codes video_photo_img_22
    ui_scr->video_photo_img_22 = lv_img_create(ui_scr->video_photo_view_video_set);
    lv_img_set_src(ui_scr->video_photo_img_22, gui_get_res_path(GUI_RES_HAND_SHAKE_1_PNG));
    lv_img_set_pivot(ui_scr->video_photo_img_22, 0, 0);
    lv_img_set_angle(ui_scr->video_photo_img_22, 0);
    lv_img_set_zoom(ui_scr->video_photo_img_22, 256);
    lv_obj_set_pos(ui_scr->video_photo_img_22, 132, 330);
    lv_obj_set_size(ui_scr->video_photo_img_22, 80, 80);
    lv_obj_add_flag(ui_scr->video_photo_img_22, LV_OBJ_FLAG_EVENT_BUBBLE);
    lv_group_add_obj(def_group, ui_scr->video_photo_img_22);
    lv_obj_add_flag(ui_scr->video_photo_img_22, LV_OBJ_FLAG_CLICKABLE);
    ui_style_set(ui_scr->video_photo_img_22, GUI_CTRL_IMG);

    //Write codes video_photo_img_23
    ui_scr->video_photo_img_23 = lv_img_create(ui_scr->video_photo_view_video_set);
    lv_img_set_src(ui_scr->video_photo_img_23, gui_get_res_path(GUI_RES_QUICK_SCAN_PNG));
    lv_img_set_pivot(ui_scr->video_photo_img_23, 0, 0);
    lv_img_set_angle(ui_scr->video_photo_img_23, 0);
    lv_img_set_zoom(ui_scr->video_photo_img_23, 256);
    lv_obj_set_pos(ui_scr->video_photo_img_23, 233, 330);
    lv_obj_set_size(ui_scr->video_photo_img_23, 80, 80);
    lv_obj_add_flag(ui_scr->video_photo_img_23, LV_OBJ_FLAG_EVENT_BUBBLE);
    lv_group_add_obj(def_group, ui_scr->video_photo_img_23);
    lv_obj_add_flag(ui_scr->video_photo_img_23, LV_OBJ_FLAG_CLICKABLE);
    ui_style_set(ui_scr->video_photo_img_23, GUI_CTRL_IMG);

    //Write codes video_photo_img_24
    ui_scr->video_photo_img_24 = lv_img_create(ui_scr->video_photo_view_video_set);
    lv_img_set_src(ui_scr->video_photo_img_24, gui_get_res_path(GUI_RES_DATE_PNG));
    lv_img_set_pivot(ui_scr->video_photo_img_24, 0, 0);
    lv_img_set_angle(ui_scr->video_photo_img_24, 0);
    lv_img_set_zoom(ui_scr->video_photo_img_24, 256);
    lv_obj_set_pos(ui_scr->video_photo_img_24, 337, 330);
    lv_obj_set_size(ui_scr->video_photo_img_24, 80, 80);
    lv_obj_add_flag(ui_scr->video_photo_img_24, LV_OBJ_FLAG_EVENT_BUBBLE);
    lv_group_add_obj(def_group, ui_scr->video_photo_img_24);
    lv_obj_add_flag(ui_scr->video_photo_img_24, LV_OBJ_FLAG_CLICKABLE);
    ui_style_set(ui_scr->video_photo_img_24, GUI_CTRL_IMG);

    //Write codes video_photo_lbl_15
    ui_scr->video_photo_lbl_15 = lv_label_create(ui_scr->video_photo_view_video_set);
    lv_label_set_long_mode(ui_scr->video_photo_lbl_15, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui_scr->video_photo_lbl_15, 129, 264);
    lv_obj_set_size(ui_scr->video_photo_lbl_15, 90, 53);
    lv_obj_set_scrollbar_mode(ui_scr->video_photo_lbl_15, LV_SCROLLBAR_MODE_OFF);
    ui_style_set(ui_scr->video_photo_lbl_15, GUI_CTRL_LABEL);

    //Write codes video_photo_lbl_16
    ui_scr->video_photo_lbl_16 = lv_label_create(ui_scr->video_photo_view_video_set);
    lv_label_set_long_mode(ui_scr->video_photo_lbl_16, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui_scr->video_photo_lbl_16, 230, 264);
    lv_obj_set_size(ui_scr->video_photo_lbl_16, 90, 53);
    lv_obj_set_scrollbar_mode(ui_scr->video_photo_lbl_16, LV_SCROLLBAR_MODE_OFF);
    ui_style_set(ui_scr->video_photo_lbl_16, GUI_CTRL_LABEL);

    //Write codes video_photo_lbl_17
    ui_scr->video_photo_lbl_17 = lv_label_create(ui_scr->video_photo_view_video_set);
    lv_label_set_text(ui_scr->video_photo_lbl_17, "ISO");
    lv_label_set_long_mode(ui_scr->video_photo_lbl_17, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui_scr->video_photo_lbl_17, 333, 264);
    lv_obj_set_size(ui_scr->video_photo_lbl_17, 90, 53);
    lv_obj_set_scrollbar_mode(ui_scr->video_photo_lbl_17, LV_SCROLLBAR_MODE_OFF);
    ui_style_set(ui_scr->video_photo_lbl_17, GUI_CTRL_LABEL);

    //Write codes video_photo_lbl_18
    ui_scr->video_photo_lbl_18 = lv_label_create(ui_scr->video_photo_view_video_set);
    lv_label_set_long_mode(ui_scr->video_photo_lbl_18, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui_scr->video_photo_lbl_18, 128, 413);
    lv_obj_set_size(ui_scr->video_photo_lbl_18, 90, 53);
    lv_obj_set_scrollbar_mode(ui_scr->video_photo_lbl_18, LV_SCROLLBAR_MODE_OFF);
    ui_style_set(ui_scr->video_photo_lbl_18, GUI_CTRL_LABEL);

    //Write codes video_photo_lbl_19
    ui_scr->video_photo_lbl_19 = lv_label_create(ui_scr->video_photo_view_video_set);
    lv_label_set_long_mode(ui_scr->video_photo_lbl_19, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui_scr->video_photo_lbl_19, 225, 413);
    lv_obj_set_size(ui_scr->video_photo_lbl_19, 90, 53);
    lv_obj_set_scrollbar_mode(ui_scr->video_photo_lbl_19, LV_SCROLLBAR_MODE_OFF);
    ui_style_set(ui_scr->video_photo_lbl_19, GUI_CTRL_LABEL);

    //Write codes video_photo_lbl_20
    ui_scr->video_photo_lbl_20 = lv_label_create(ui_scr->video_photo_view_video_set);
    lv_label_set_long_mode(ui_scr->video_photo_lbl_20, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui_scr->video_photo_lbl_20, 332, 413);
    lv_obj_set_size(ui_scr->video_photo_lbl_20, 90, 53);
    lv_obj_set_scrollbar_mode(ui_scr->video_photo_lbl_20, LV_SCROLLBAR_MODE_OFF);
    ui_style_set(ui_scr->video_photo_lbl_20, GUI_CTRL_LABEL);

    //Write codes video_photo_img_25
    ui_scr->video_photo_img_25 = lv_img_create(ui_scr->video_photo);
    lv_img_set_src(ui_scr->video_photo_img_25, gui_get_res_path(GUI_RES_HIGH_PNG));
    lv_img_set_pivot(ui_scr->video_photo_img_25, 0, 0);
    lv_img_set_angle(ui_scr->video_photo_img_25, 0);
    lv_img_set_zoom(ui_scr->video_photo_img_25, 256);
    lv_obj_set_pos(ui_scr->video_photo_img_25, 22, 70);
    lv_obj_set_size(ui_scr->video_photo_img_25, 48, 48);
    lv_obj_add_flag(ui_scr->video_photo_img_25, LV_OBJ_FLAG_CLICKABLE);
    ui_style_set(ui_scr->video_photo_img_25, GUI_CTRL_IMG);

    //Set style for video_photo_img_25. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
    lv_obj_set_style_radius(ui_scr->video_photo_img_25, 24, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui_scr->video_photo_img_25, true, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_scr->video_photo_img_25, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    //Delete extra default style for video_photo_img_25
    lv_obj_remove_style(ui_scr->video_photo_img_25, &gui_img_main_focus_key_style, LV_PART_MAIN | LV_STATE_FOCUS_KEY);

    //Write codes video_photo_img_4
    ui_scr->video_photo_img_4 = lv_img_create(ui_scr->video_photo);
    lv_img_set_src(ui_scr->video_photo_img_4, gui_get_res_path(GUI_RES_AWB_1_PNG));
    lv_img_set_pivot(ui_scr->video_photo_img_4, 0, 0);
    lv_img_set_angle(ui_scr->video_photo_img_4, 0);
    lv_img_set_zoom(ui_scr->video_photo_img_4, 256);
    lv_obj_set_pos(ui_scr->video_photo_img_4, 23, 263);
    lv_obj_set_size(ui_scr->video_photo_img_4, 48, 48);
    lv_obj_add_flag(ui_scr->video_photo_img_4, LV_OBJ_FLAG_CLICKABLE);
    ui_style_set(ui_scr->video_photo_img_4, GUI_CTRL_IMG);

    //Set style for video_photo_img_4. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
    lv_obj_set_style_radius(ui_scr->video_photo_img_4, 24, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui_scr->video_photo_img_4, true, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_scr->video_photo_img_4, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    //Delete extra default style for video_photo_img_4
    lv_obj_remove_style(ui_scr->video_photo_img_4, &gui_img_main_focus_key_style, LV_PART_MAIN | LV_STATE_FOCUS_KEY);

    //Write codes video_photo_view_subpage
    ui_scr->video_photo_view_subpage = lv_obj_create(ui_scr->video_photo);
    lv_obj_set_pos(ui_scr->video_photo_view_subpage, 186, 232);
    lv_obj_set_size(ui_scr->video_photo_view_subpage, 539, 244);
    lv_obj_set_scrollbar_mode(ui_scr->video_photo_view_subpage, LV_SCROLLBAR_MODE_OFF);
    lv_obj_add_flag(ui_scr->video_photo_view_subpage, LV_OBJ_FLAG_HIDDEN);
    ui_style_set(ui_scr->video_photo_view_subpage, GUI_CTRL_CONT);

    //Set style for video_photo_view_subpage. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
    lv_obj_set_style_bg_color(ui_scr->video_photo_view_subpage, lv_color_make(0x00, 0x00, 0x00), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_scr->video_photo_view_subpage, 204, LV_PART_MAIN | LV_STATE_DEFAULT);

    //Write codes video_photo_img_16
    ui_scr->video_photo_img_16 = lv_img_create(ui_scr->video_photo_view_subpage);
    lv_img_set_src(ui_scr->video_photo_img_16, gui_get_res_path(GUI_RES_RESOLUTION_RATIO_PNG));
    lv_img_set_pivot(ui_scr->video_photo_img_16, 0, 0);
    lv_img_set_angle(ui_scr->video_photo_img_16, 0);
    lv_img_set_zoom(ui_scr->video_photo_img_16, 256);
    lv_obj_set_pos(ui_scr->video_photo_img_16, 28, 7);
    lv_obj_set_size(ui_scr->video_photo_img_16, 80, 80);
    lv_obj_add_flag(ui_scr->video_photo_img_16, LV_OBJ_FLAG_EVENT_BUBBLE);
    lv_obj_add_flag(ui_scr->video_photo_img_16, LV_OBJ_FLAG_CLICKABLE);
    lv_obj_add_flag(ui_scr->video_photo_img_16, LV_OBJ_FLAG_CLICKABLE);
    ui_style_set(ui_scr->video_photo_img_16, GUI_CTRL_IMG);

    //Delete extra default style for video_photo_img_16
    lv_obj_remove_style(ui_scr->video_photo_img_16, &gui_img_main_focus_key_style, LV_PART_MAIN | LV_STATE_FOCUS_KEY);

    //Write codes video_photo_lbl_menu_title
    ui_scr->video_photo_lbl_menu_title = lv_label_create(ui_scr->video_photo_view_subpage);
    lv_label_set_long_mode(ui_scr->video_photo_lbl_menu_title, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui_scr->video_photo_lbl_menu_title, 111, 7);
    lv_obj_set_size(ui_scr->video_photo_lbl_menu_title, 201, 53);
    lv_obj_set_scrollbar_mode(ui_scr->video_photo_lbl_menu_title, LV_SCROLLBAR_MODE_OFF);
    ui_style_set(ui_scr->video_photo_lbl_menu_title, GUI_CTRL_LABEL);

    //Set style for video_photo_lbl_menu_title. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
    lv_obj_set_style_text_align(ui_scr->video_photo_lbl_menu_title, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui_scr->video_photo_lbl_menu_title, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

    //Write codes video_photo_roller_mutifunc
    ui_scr->video_photo_roller_mutifunc = lv_roller_create(ui_scr->video_photo_view_subpage);
    lv_obj_set_pos(ui_scr->video_photo_roller_mutifunc, 159, 58);
    lv_obj_set_size(ui_scr->video_photo_roller_mutifunc, 243, 126);
    lv_obj_set_scrollbar_mode(ui_scr->video_photo_roller_mutifunc, LV_SCROLLBAR_MODE_OFF);
    ui_style_set(ui_scr->video_photo_roller_mutifunc, GUI_CTRL_ROLLER);

    //Set style for video_photo_roller_mutifunc. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
    lv_obj_set_style_text_font(ui_scr->video_photo_roller_mutifunc, &lv_font_FangZhengKaiTiJianTi_1_24, LV_PART_MAIN | LV_STATE_DEFAULT);

    //Set style for video_photo_roller_mutifunc. Part: LV_PART_SELECTED, State: LV_STATE_DEFAULT
    lv_obj_set_style_text_font(ui_scr->video_photo_roller_mutifunc, &lv_font_FangZhengKaiTiJianTi_1_24, LV_PART_SELECTED | LV_STATE_DEFAULT);

    //Set style for video_photo_roller_mutifunc. Part: LV_PART_MAIN, State: LV_STATE_FOCUS_KEY
    lv_obj_set_style_outline_width(ui_scr->video_photo_roller_mutifunc, 2, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_text_font(ui_scr->video_photo_roller_mutifunc, &lv_font_FangZhengKaiTiJianTi_1_24, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_roller_set_options(ui_scr->video_photo_roller_mutifunc, "VGA\n1M\n2M\n3M\n5M\n8M\n10M\n12M\n64M", LV_ROLLER_MODE_INFINITE);
    lv_roller_set_visible_row_count(ui_scr->video_photo_roller_mutifunc, 3);

    //Write codes video_photo_lbl_funkey1
    ui_scr->video_photo_lbl_funkey1 = lv_btn_create(ui_scr->video_photo_view_subpage);
    lv_obj_set_pos(ui_scr->video_photo_lbl_funkey1, 28, 190);
    lv_obj_set_size(ui_scr->video_photo_lbl_funkey1, 117, 50);
    lv_obj_set_scrollbar_mode(ui_scr->video_photo_lbl_funkey1, LV_SCROLLBAR_MODE_OFF);
    lv_obj_add_flag(ui_scr->video_photo_lbl_funkey1, LV_OBJ_FLAG_CLICKABLE);
    lv_obj_add_flag(ui_scr->video_photo_lbl_funkey1, LV_OBJ_FLAG_EVENT_BUBBLE);
    ui_style_set(ui_scr->video_photo_lbl_funkey1, GUI_CTRL_BUTTON);

    //Set style for video_photo_lbl_funkey1. Part: LV_PART_MAIN, State: LV_STATE_FOCUSED
    lv_obj_set_style_outline_width(ui_scr->video_photo_lbl_funkey1, 0, LV_PART_MAIN | LV_STATE_FOCUSED);
    lv_obj_set_style_text_color(ui_scr->video_photo_lbl_funkey1, lv_color_make(0xFF, 0xEB, 0x3B), LV_PART_MAIN | LV_STATE_FOCUSED);
    ui_scr->video_photo_lbl_funkey1_label = lv_label_create(ui_scr->video_photo_lbl_funkey1);
    lv_obj_set_style_pad_all(ui_scr->video_photo_lbl_funkey1, 0, LV_STATE_DEFAULT);
    lv_obj_align(ui_scr->video_photo_lbl_funkey1_label, LV_ALIGN_CENTER, 0, 0);

    //Write codes video_photo_lbl_funkey2
    ui_scr->video_photo_lbl_funkey2 = lv_btn_create(ui_scr->video_photo_view_subpage);
    lv_obj_set_pos(ui_scr->video_photo_lbl_funkey2, 159, 190);
    lv_obj_set_size(ui_scr->video_photo_lbl_funkey2, 117, 50);
    lv_obj_set_scrollbar_mode(ui_scr->video_photo_lbl_funkey2, LV_SCROLLBAR_MODE_OFF);
    lv_obj_add_flag(ui_scr->video_photo_lbl_funkey2, LV_OBJ_FLAG_CLICKABLE);
    lv_obj_add_flag(ui_scr->video_photo_lbl_funkey2, LV_OBJ_FLAG_EVENT_BUBBLE);
    ui_style_set(ui_scr->video_photo_lbl_funkey2, GUI_CTRL_BUTTON);

    //Set style for video_photo_lbl_funkey2. Part: LV_PART_MAIN, State: LV_STATE_FOCUSED
    lv_obj_set_style_outline_width(ui_scr->video_photo_lbl_funkey2, 0, LV_PART_MAIN | LV_STATE_FOCUSED);
    lv_obj_set_style_text_color(ui_scr->video_photo_lbl_funkey2, lv_color_make(0xFF, 0xEB, 0x3B), LV_PART_MAIN | LV_STATE_FOCUSED);
    ui_scr->video_photo_lbl_funkey2_label = lv_label_create(ui_scr->video_photo_lbl_funkey2);
    lv_obj_set_size(ui_scr->video_photo_lbl_funkey2_label, 120, 32);
    lv_label_set_long_mode(ui_scr->video_photo_lbl_funkey2_label, LV_LABEL_LONG_SCROLL);
    lv_obj_set_style_pad_all(ui_scr->video_photo_lbl_funkey2, 0, LV_STATE_DEFAULT);
    lv_obj_align(ui_scr->video_photo_lbl_funkey2_label, LV_ALIGN_CENTER, 0, 0);

    //Write codes video_photo_lbl_funkey3
    ui_scr->video_photo_lbl_funkey3 = lv_btn_create(ui_scr->video_photo_view_subpage);
    lv_obj_set_pos(ui_scr->video_photo_lbl_funkey3, 286, 190);
    lv_obj_set_size(ui_scr->video_photo_lbl_funkey3, 117, 50);
    lv_obj_set_scrollbar_mode(ui_scr->video_photo_lbl_funkey3, LV_SCROLLBAR_MODE_OFF);
    lv_obj_add_flag(ui_scr->video_photo_lbl_funkey3, LV_OBJ_FLAG_CLICKABLE);
    lv_obj_add_flag(ui_scr->video_photo_lbl_funkey3, LV_OBJ_FLAG_EVENT_BUBBLE);
    ui_style_set(ui_scr->video_photo_lbl_funkey3, GUI_CTRL_BUTTON);

    //Set style for video_photo_lbl_funkey3. Part: LV_PART_MAIN, State: LV_STATE_FOCUSED
    lv_obj_set_style_outline_width(ui_scr->video_photo_lbl_funkey3, 0, LV_PART_MAIN | LV_STATE_FOCUSED);
    lv_obj_set_style_text_color(ui_scr->video_photo_lbl_funkey3, lv_color_make(0xFF, 0xEB, 0x3B), LV_PART_MAIN | LV_STATE_FOCUSED);
    ui_scr->video_photo_lbl_funkey3_label = lv_label_create(ui_scr->video_photo_lbl_funkey3);
    lv_obj_set_size(ui_scr->video_photo_lbl_funkey3_label, 120, 32);
    lv_label_set_long_mode(ui_scr->video_photo_lbl_funkey3_label, LV_LABEL_LONG_SCROLL);
    lv_obj_set_style_pad_all(ui_scr->video_photo_lbl_funkey3, 0, LV_STATE_DEFAULT);
    lv_obj_align(ui_scr->video_photo_lbl_funkey3_label, LV_ALIGN_CENTER, 0, 0);

    //Write codes video_photo_lbl_funkey4
    ui_scr->video_photo_lbl_funkey4 = lv_btn_create(ui_scr->video_photo_view_subpage);
    lv_obj_set_pos(ui_scr->video_photo_lbl_funkey4, 415, 190);
    lv_obj_set_size(ui_scr->video_photo_lbl_funkey4, 117, 50);
    lv_obj_set_scrollbar_mode(ui_scr->video_photo_lbl_funkey4, LV_SCROLLBAR_MODE_OFF);
    lv_obj_add_flag(ui_scr->video_photo_lbl_funkey4, LV_OBJ_FLAG_CLICKABLE);
    lv_obj_add_flag(ui_scr->video_photo_lbl_funkey4, LV_OBJ_FLAG_EVENT_BUBBLE);
    ui_style_set(ui_scr->video_photo_lbl_funkey4, GUI_CTRL_BUTTON);

    //Set style for video_photo_lbl_funkey4. Part: LV_PART_MAIN, State: LV_STATE_FOCUSED
    lv_obj_set_style_outline_width(ui_scr->video_photo_lbl_funkey4, 0, LV_PART_MAIN | LV_STATE_FOCUSED);
    lv_obj_set_style_text_color(ui_scr->video_photo_lbl_funkey4, lv_color_make(0xFF, 0xEB, 0x3B), LV_PART_MAIN | LV_STATE_FOCUSED);
    ui_scr->video_photo_lbl_funkey4_label = lv_label_create(ui_scr->video_photo_lbl_funkey4);
    lv_obj_set_size(ui_scr->video_photo_lbl_funkey4_label, 120, 32);
    lv_label_set_long_mode(ui_scr->video_photo_lbl_funkey4_label, LV_LABEL_LONG_SCROLL);
    lv_obj_set_style_pad_all(ui_scr->video_photo_lbl_funkey4, 0, LV_STATE_DEFAULT);
    lv_obj_align(ui_scr->video_photo_lbl_funkey4_label, LV_ALIGN_CENTER, 0, 0);

    //Write codes video_photo_show_capture_time
    ui_scr->video_photo_show_capture_time = lv_label_create(ui_scr->video_photo);
    lv_label_set_text(ui_scr->video_photo_show_capture_time, "3");
    lv_label_set_long_mode(ui_scr->video_photo_show_capture_time, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui_scr->video_photo_show_capture_time, 300, 140);
    lv_obj_set_size(ui_scr->video_photo_show_capture_time, 200, 200);
    lv_obj_set_scrollbar_mode(ui_scr->video_photo_show_capture_time, LV_SCROLLBAR_MODE_OFF);
    lv_obj_add_flag(ui_scr->video_photo_show_capture_time, LV_OBJ_FLAG_HIDDEN);
    ui_style_set(ui_scr->video_photo_show_capture_time, GUI_CTRL_LABEL);

    //Set style for video_photo_show_capture_time. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
    lv_obj_set_style_border_opa(ui_scr->video_photo_show_capture_time, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_outline_opa(ui_scr->video_photo_show_capture_time, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_scr->video_photo_show_capture_time, &lv_font_montserratMedium_160, LV_PART_MAIN | LV_STATE_DEFAULT);

    lv_obj_update_layout(ui_scr->video_photo);
    ui_scr->video_photo_del = false;
    i18n_refresh_texts("video_photo");

    //Init events for screen
    events_init_video_photo(ui);
    return ui_scr->video_photo;
}
void unload_scr_video_photo(lv_ui *ui)
{
    ui_free_scr_ptr(ui, GUI_SCREEN_VIDEO_PHOTO);
}

#endif
