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


lv_obj_t *setup_scr_video_rec(lv_ui *ui)
{
    lv_ui_video_rec *ui_scr = ui_get_scr_ptr(ui, GUI_SCREEN_VIDEO_REC);
    if (ui_scr == NULL) {
        ui_scr = lv_mem_alloc(sizeof(lv_ui_video_rec));
        memset(ui_scr, 0, sizeof(lv_ui_video_rec));
        ui->video_rec = ui_scr;
    }

    //Write codes video_rec
    ui_scr->video_rec = lv_obj_create(NULL);
    lv_group_t *def_group = lv_group_get_default();
    lv_obj_set_scrollbar_mode(ui_scr->video_rec, LV_SCROLLBAR_MODE_OFF);
    lv_obj_clear_flag(ui_scr->video_rec, LV_OBJ_FLAG_SCROLLABLE);
    ui_style_set(ui_scr->video_rec, GUI_CTRL_SCR);

    //Write codes video_rec_imgbtn_1
    ui_scr->video_rec_imgbtn_1 = lv_imgbtn_create(ui_scr->video_rec);
    lv_obj_set_pos(ui_scr->video_rec_imgbtn_1, 602, 202);
    lv_obj_set_size(ui_scr->video_rec_imgbtn_1, 88, 88);
    lv_obj_set_scrollbar_mode(ui_scr->video_rec_imgbtn_1, LV_SCROLLBAR_MODE_OFF);
    lv_group_add_obj(def_group, ui_scr->video_rec_imgbtn_1);
    //Effect attention attention_flash
    lv_anim_effect_args_t video_rec_imgbtn_1_effect_args;
    video_rec_imgbtn_1_effect_args.delay = 0;
    video_rec_imgbtn_1_effect_args.duration = 1500;
    lv_anim_effect_attention_flash(ui_scr->video_rec_imgbtn_1, &video_rec_imgbtn_1_effect_args);
    ui_style_set(ui_scr->video_rec_imgbtn_1, GUI_CTRL_IMGBTN);

    //Set style for video_rec_imgbtn_1. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
    lv_obj_set_style_radius(ui_scr->video_rec_imgbtn_1, 44, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui_scr->video_rec_imgbtn_1, true, LV_PART_MAIN | LV_STATE_DEFAULT);

    //Set style for video_rec_imgbtn_1. Part: LV_PART_MAIN, State: LV_STATE_FOCUS_KEY
    lv_obj_set_style_radius(ui_scr->video_rec_imgbtn_1, 44, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_clip_corner(ui_scr->video_rec_imgbtn_1, true, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_bg_opa(ui_scr->video_rec_imgbtn_1, 255, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_imgbtn_set_src(ui_scr->video_rec_imgbtn_1, LV_IMGBTN_STATE_RELEASED, NULL, gui_get_res_path(GUI_RES_VIDEO_BUTTO_PNG), NULL);
    lv_imgbtn_set_src(ui_scr->video_rec_imgbtn_1, LV_IMGBTN_STATE_PRESSED, NULL, gui_get_res_path(GUI_RES_VIDEO_BUTTO_FLASH1_ON_PNG), NULL);
    lv_imgbtn_set_src(ui_scr->video_rec_imgbtn_1, LV_IMGBTN_STATE_CHECKED_RELEASED, NULL, gui_get_res_path(GUI_RES_VIDEO_BUTTO_FLASH2_PNG), NULL);
    lv_imgbtn_set_src(ui_scr->video_rec_imgbtn_1, LV_IMGBTN_STATE_CHECKED_PRESSED, NULL, gui_get_res_path(GUI_RES_VIDEO_BUTTO_FLASH2_ON_PNG), NULL);
    lv_obj_add_flag(ui_scr->video_rec_imgbtn_1, LV_OBJ_FLAG_CHECKABLE);
    ui_scr->video_rec_imgbtn_1_label = lv_label_create(ui_scr->video_rec_imgbtn_1);
    lv_label_set_text(ui_scr->video_rec_imgbtn_1_label, "");
    lv_obj_set_style_pad_all(ui_scr->video_rec_imgbtn_1, 0, LV_STATE_DEFAULT);
    lv_obj_align(ui_scr->video_rec_imgbtn_1_label, LV_ALIGN_CENTER, 0, 0);

    static bool timer_video_rec_digitclock_2_enabled = false;
    //Write codes video_rec_digitclock_2
    ui_scr->video_rec_digitclock_2 = lv_label_create(ui_scr->video_rec);
    lv_label_set_text_fmt(ui_scr->video_rec_digitclock_2, "%04d-%02d-%02d %02d:%02d:%02d", 2022, 07, 28, 21 % 12, 25, 50);
    lv_obj_set_style_text_align(ui_scr->video_rec_digitclock_2, LV_TEXT_ALIGN_CENTER, 0);
    lv_obj_set_pos(ui_scr->video_rec_digitclock_2, 222, 420);
    lv_obj_set_size(ui_scr->video_rec_digitclock_2, 343, 49);
    ui_style_set(ui_scr->video_rec_digitclock_2, GUI_CTRL_DIGITALCLOCK);

    //Delete extra default style for video_rec_digitclock_2
    lv_obj_remove_style(ui_scr->video_rec_digitclock_2, &gui_digitclock_main_disabled_style, LV_PART_MAIN | LV_STATE_DISABLED);

    //Write codes video_rec_img_4
    ui_scr->video_rec_img_4 = lv_img_create(ui_scr->video_rec);
    lv_img_set_src(ui_scr->video_rec_img_4, gui_get_res_path(GUI_RES_CYCLIC_VIDEO_CLOSE_PNG));
    lv_img_set_pivot(ui_scr->video_rec_img_4, 0, 0);
    lv_img_set_angle(ui_scr->video_rec_img_4, 0);
    lv_img_set_zoom(ui_scr->video_rec_img_4, 256);
    lv_obj_set_pos(ui_scr->video_rec_img_4, 438, 16);
    lv_obj_set_size(ui_scr->video_rec_img_4, 48, 48);
    lv_obj_add_flag(ui_scr->video_rec_img_4, LV_OBJ_FLAG_CLICKABLE);
    ui_style_set(ui_scr->video_rec_img_4, GUI_CTRL_IMG);

    //Delete extra default style for video_rec_img_4
    lv_obj_remove_style(ui_scr->video_rec_img_4, &gui_img_main_focus_key_style, LV_PART_MAIN | LV_STATE_FOCUS_KEY);

    //Write codes video_rec_img_5
    ui_scr->video_rec_img_5 = lv_img_create(ui_scr->video_rec);
    lv_img_set_src(ui_scr->video_rec_img_5, gui_get_res_path(GUI_RES_GRAVITY_SENSOR_LOW_PNG));
    lv_img_set_pivot(ui_scr->video_rec_img_5, 0, 0);
    lv_img_set_angle(ui_scr->video_rec_img_5, 0);
    lv_img_set_zoom(ui_scr->video_rec_img_5, 256);
    lv_obj_set_pos(ui_scr->video_rec_img_5, 159, 16);
    lv_obj_set_size(ui_scr->video_rec_img_5, 48, 48);
    lv_obj_add_flag(ui_scr->video_rec_img_5, LV_OBJ_FLAG_CLICKABLE);
    ui_style_set(ui_scr->video_rec_img_5, GUI_CTRL_IMG);

    //Delete extra default style for video_rec_img_5
    lv_obj_remove_style(ui_scr->video_rec_img_5, &gui_img_main_focus_key_style, LV_PART_MAIN | LV_STATE_FOCUS_KEY);

    //Write codes video_rec_img_6
    ui_scr->video_rec_img_6 = lv_img_create(ui_scr->video_rec);
    lv_img_set_src(ui_scr->video_rec_img_6, gui_get_res_path(GUI_RES_SOUND_CLOSE_PNG));
    lv_img_set_pivot(ui_scr->video_rec_img_6, 0, 0);
    lv_img_set_angle(ui_scr->video_rec_img_6, 0);
    lv_img_set_zoom(ui_scr->video_rec_img_6, 256);
    lv_obj_set_pos(ui_scr->video_rec_img_6, 495, 16);
    lv_obj_set_size(ui_scr->video_rec_img_6, 48, 48);
    lv_obj_add_flag(ui_scr->video_rec_img_6, LV_OBJ_FLAG_CLICKABLE);
    ui_style_set(ui_scr->video_rec_img_6, GUI_CTRL_IMG);

    //Delete extra default style for video_rec_img_6
    lv_obj_remove_style(ui_scr->video_rec_img_6, &gui_img_main_focus_key_style, LV_PART_MAIN | LV_STATE_FOCUS_KEY);

    //Write codes video_rec_img_7
    ui_scr->video_rec_img_7 = lv_img_create(ui_scr->video_rec);
    lv_img_set_src(ui_scr->video_rec_img_7, gui_get_res_path(GUI_RES_STOPPING_MONITOR_PNG));
    lv_img_set_pivot(ui_scr->video_rec_img_7, 0, 0);
    lv_img_set_angle(ui_scr->video_rec_img_7, 0);
    lv_img_set_zoom(ui_scr->video_rec_img_7, 256);
    lv_obj_set_pos(ui_scr->video_rec_img_7, 216, 16);
    lv_obj_set_size(ui_scr->video_rec_img_7, 45, 45);
    lv_obj_add_flag(ui_scr->video_rec_img_7, LV_OBJ_FLAG_CLICKABLE);
    ui_style_set(ui_scr->video_rec_img_7, GUI_CTRL_IMG);

    //Delete extra default style for video_rec_img_7
    lv_obj_remove_style(ui_scr->video_rec_img_7, &gui_img_main_focus_key_style, LV_PART_MAIN | LV_STATE_FOCUS_KEY);

    //Write codes video_rec_img_8
    ui_scr->video_rec_img_8 = lv_img_create(ui_scr->video_rec);
    lv_img_set_src(ui_scr->video_rec_img_8, gui_get_res_path(GUI_RES_CHECK_SPORT_PNG));
    lv_img_set_pivot(ui_scr->video_rec_img_8, 0, 0);
    lv_img_set_angle(ui_scr->video_rec_img_8, 0);
    lv_img_set_zoom(ui_scr->video_rec_img_8, 256);
    lv_obj_set_pos(ui_scr->video_rec_img_8, 270, 16);
    lv_obj_set_size(ui_scr->video_rec_img_8, 48, 48);
    lv_obj_add_flag(ui_scr->video_rec_img_8, LV_OBJ_FLAG_CLICKABLE);
    ui_style_set(ui_scr->video_rec_img_8, GUI_CTRL_IMG);

    //Set style for video_rec_img_8. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
    lv_obj_set_style_bg_color(ui_scr->video_rec_img_8, lv_color_make(0x16, 0x48, 0xD1), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_img_recolor(ui_scr->video_rec_img_8, lv_color_make(0x36, 0x56, 0xDB), LV_PART_MAIN | LV_STATE_DEFAULT);

    //Delete extra default style for video_rec_img_8
    lv_obj_remove_style(ui_scr->video_rec_img_8, &gui_img_main_focus_key_style, LV_PART_MAIN | LV_STATE_FOCUS_KEY);

    //Write codes video_rec_img_9
    ui_scr->video_rec_img_9 = lv_img_create(ui_scr->video_rec);
    lv_img_set_src(ui_scr->video_rec_img_9, gui_get_res_path(GUI_RES_SD_PNG));
    lv_img_set_pivot(ui_scr->video_rec_img_9, 0, 0);
    lv_img_set_angle(ui_scr->video_rec_img_9, 0);
    lv_img_set_zoom(ui_scr->video_rec_img_9, 256);
    lv_obj_set_pos(ui_scr->video_rec_img_9, 327, 16);
    lv_obj_set_size(ui_scr->video_rec_img_9, 45, 45);
    lv_obj_add_flag(ui_scr->video_rec_img_9, LV_OBJ_FLAG_CLICKABLE);
    ui_style_set(ui_scr->video_rec_img_9, GUI_CTRL_IMG);

    //Delete extra default style for video_rec_img_9
    lv_obj_remove_style(ui_scr->video_rec_img_9, &gui_img_main_focus_key_style, LV_PART_MAIN | LV_STATE_FOCUS_KEY);

    //Write codes video_rec_img_lock_icon
    ui_scr->video_rec_img_lock_icon = lv_img_create(ui_scr->video_rec);
    lv_img_set_src(ui_scr->video_rec_img_lock_icon, gui_get_res_path(GUI_RES_LOCK_PNG));
    lv_img_set_pivot(ui_scr->video_rec_img_lock_icon, 0, 0);
    lv_img_set_angle(ui_scr->video_rec_img_lock_icon, 0);
    lv_img_set_zoom(ui_scr->video_rec_img_lock_icon, 256);
    lv_obj_set_pos(ui_scr->video_rec_img_lock_icon, 381, 16);
    lv_obj_set_size(ui_scr->video_rec_img_lock_icon, 48, 48);
    lv_obj_add_flag(ui_scr->video_rec_img_lock_icon, LV_OBJ_FLAG_HIDDEN);
    lv_obj_add_flag(ui_scr->video_rec_img_lock_icon, LV_OBJ_FLAG_CLICKABLE);
    ui_style_set(ui_scr->video_rec_img_lock_icon, GUI_CTRL_IMG);

    //Delete extra default style for video_rec_img_lock_icon
    lv_obj_remove_style(ui_scr->video_rec_img_lock_icon, &gui_img_main_focus_key_style, LV_PART_MAIN | LV_STATE_FOCUS_KEY);

    //Write codes video_rec_img_11
    ui_scr->video_rec_img_11 = lv_img_create(ui_scr->video_rec);
    lv_img_set_src(ui_scr->video_rec_img_11, gui_get_res_path(GUI_RES_INTERVAL_VIDEO_CLOSE_PNG));
    lv_img_set_pivot(ui_scr->video_rec_img_11, 0, 0);
    lv_img_set_angle(ui_scr->video_rec_img_11, 0);
    lv_img_set_zoom(ui_scr->video_rec_img_11, 256);
    lv_obj_set_pos(ui_scr->video_rec_img_11, 552, 16);
    lv_obj_set_size(ui_scr->video_rec_img_11, 48, 48);
    lv_obj_add_flag(ui_scr->video_rec_img_11, LV_OBJ_FLAG_CLICKABLE);
    ui_style_set(ui_scr->video_rec_img_11, GUI_CTRL_IMG);

    //Delete extra default style for video_rec_img_11
    lv_obj_remove_style(ui_scr->video_rec_img_11, &gui_img_main_focus_key_style, LV_PART_MAIN | LV_STATE_FOCUS_KEY);

    //Write codes video_rec_img_app
    ui_scr->video_rec_img_app = lv_img_create(ui_scr->video_rec);
    lv_img_set_src(ui_scr->video_rec_img_app, gui_get_res_path(GUI_RES_DISCONNECT_PNG));
    lv_img_set_pivot(ui_scr->video_rec_img_app, 0, 0);
    lv_img_set_angle(ui_scr->video_rec_img_app, 0);
    lv_img_set_zoom(ui_scr->video_rec_img_app, 256);
    lv_obj_set_pos(ui_scr->video_rec_img_app, 617, 18);
    lv_obj_set_size(ui_scr->video_rec_img_app, 45, 45);
    lv_obj_add_flag(ui_scr->video_rec_img_app, LV_OBJ_FLAG_CLICKABLE);
    ui_style_set(ui_scr->video_rec_img_app, GUI_CTRL_IMG);

    //Delete extra default style for video_rec_img_app
    lv_obj_remove_style(ui_scr->video_rec_img_app, &gui_img_main_focus_key_style, LV_PART_MAIN | LV_STATE_FOCUS_KEY);

    //Write codes video_rec_img_12
    ui_scr->video_rec_img_12 = lv_img_create(ui_scr->video_rec);
    lv_img_set_src(ui_scr->video_rec_img_12, gui_get_res_path(GUI_RES_FULL_PNG));
    lv_img_set_pivot(ui_scr->video_rec_img_12, 0, 0);
    lv_img_set_angle(ui_scr->video_rec_img_12, 0);
    lv_img_set_zoom(ui_scr->video_rec_img_12, 256);
    lv_obj_set_pos(ui_scr->video_rec_img_12, 22, 420);
    lv_obj_set_size(ui_scr->video_rec_img_12, 48, 48);
    lv_obj_add_flag(ui_scr->video_rec_img_12, LV_OBJ_FLAG_CLICKABLE);
    ui_style_set(ui_scr->video_rec_img_12, GUI_CTRL_IMG);

    //Delete extra default style for video_rec_img_12
    lv_obj_remove_style(ui_scr->video_rec_img_12, &gui_img_main_focus_key_style, LV_PART_MAIN | LV_STATE_FOCUS_KEY);

    //Write codes video_rec_lbl_2
    ui_scr->video_rec_lbl_2 = lv_label_create(ui_scr->video_rec);
    lv_label_set_text(ui_scr->video_rec_lbl_2, "720P");
    lv_label_set_long_mode(ui_scr->video_rec_lbl_2, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui_scr->video_rec_lbl_2, 24, 61);
    lv_obj_set_size(ui_scr->video_rec_lbl_2, 60, 60);
    lv_obj_set_scrollbar_mode(ui_scr->video_rec_lbl_2, LV_SCROLLBAR_MODE_OFF);
    ui_style_set(ui_scr->video_rec_lbl_2, GUI_CTRL_LABEL);

    //Set style for video_rec_lbl_2. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
    lv_obj_set_style_radius(ui_scr->video_rec_lbl_2, 35, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui_scr->video_rec_lbl_2, lv_color_make(0xEA, 0xEE, 0xF1), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_scr->video_rec_lbl_2, 77, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_scr->video_rec_lbl_2, &lv_font_FangZhengKaiTiJianTi_1_19, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui_scr->video_rec_lbl_2, 15, LV_PART_MAIN | LV_STATE_DEFAULT);

    //Write codes video_rec_lbl_3
    ui_scr->video_rec_lbl_3 = lv_label_create(ui_scr->video_rec);
    lv_label_set_text(ui_scr->video_rec_lbl_3, "HDR");
    lv_label_set_long_mode(ui_scr->video_rec_lbl_3, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui_scr->video_rec_lbl_3, 24, 136);
    lv_obj_set_size(ui_scr->video_rec_lbl_3, 60, 60);
    lv_obj_set_scrollbar_mode(ui_scr->video_rec_lbl_3, LV_SCROLLBAR_MODE_OFF);
    ui_style_set(ui_scr->video_rec_lbl_3, GUI_CTRL_LABEL);

    //Set style for video_rec_lbl_3. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
    lv_obj_set_style_radius(ui_scr->video_rec_lbl_3, 35, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui_scr->video_rec_lbl_3, lv_color_make(0xEA, 0xEE, 0xF1), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_scr->video_rec_lbl_3, 77, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_scr->video_rec_lbl_3, &lv_font_FangZhengKaiTiJianTi_1_19, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui_scr->video_rec_lbl_3, 1, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui_scr->video_rec_lbl_3, 15, LV_PART_MAIN | LV_STATE_DEFAULT);

    //Write codes video_rec_lbl_4
    ui_scr->video_rec_lbl_4 = lv_label_create(ui_scr->video_rec);
    lv_label_set_text(ui_scr->video_rec_lbl_4, "京 AAAAAA\n\n京津晋冀蒙辽吉黑苏浙皖闽赣鲁豫鄂湘粤桂琼川贵滇渝藏陕甘青宁新台港澳");
    lv_label_set_long_mode(ui_scr->video_rec_lbl_4, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui_scr->video_rec_lbl_4, 78, 420);
    lv_obj_set_size(ui_scr->video_rec_lbl_4, 161, 52);
    lv_obj_set_scrollbar_mode(ui_scr->video_rec_lbl_4, LV_SCROLLBAR_MODE_OFF);
    ui_style_set(ui_scr->video_rec_lbl_4, GUI_CTRL_LABEL);

    //Set style for video_rec_lbl_4. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
    lv_obj_set_style_text_font(ui_scr->video_rec_lbl_4, &lv_font_FangZhengKaiTiJianTi_1_24, LV_PART_MAIN | LV_STATE_DEFAULT);

    //Write codes video_rec_view_1
    ui_scr->video_rec_view_1 = lv_obj_create(ui_scr->video_rec);
    lv_obj_set_pos(ui_scr->video_rec_view_1, 725, 0);
    lv_obj_set_size(ui_scr->video_rec_view_1, 80, 480);
    lv_obj_set_scrollbar_mode(ui_scr->video_rec_view_1, LV_SCROLLBAR_MODE_OFF);
    ui_style_set(ui_scr->video_rec_view_1, GUI_CTRL_CONT);

    //Set style for video_rec_view_1. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
    lv_obj_set_style_bg_color(ui_scr->video_rec_view_1, lv_color_make(0x31, 0x2B, 0x2B), LV_PART_MAIN | LV_STATE_DEFAULT);

    //Write codes video_rec_img_video_set
    ui_scr->video_rec_img_video_set = lv_img_create(ui_scr->video_rec);
    lv_img_set_src(ui_scr->video_rec_img_video_set, gui_get_res_path(GUI_RES_SETTING_PNG));
    lv_img_set_pivot(ui_scr->video_rec_img_video_set, 0, 0);
    lv_img_set_angle(ui_scr->video_rec_img_video_set, 0);
    lv_img_set_zoom(ui_scr->video_rec_img_video_set, 256);
    lv_obj_set_pos(ui_scr->video_rec_img_video_set, 742, 125);
    lv_obj_set_size(ui_scr->video_rec_img_video_set, 48, 48);
    lv_group_add_obj(def_group, ui_scr->video_rec_img_video_set);
    lv_obj_add_flag(ui_scr->video_rec_img_video_set, LV_OBJ_FLAG_CLICKABLE);
    ui_style_set(ui_scr->video_rec_img_video_set, GUI_CTRL_IMG);

    //Set style for video_rec_img_video_set. Part: LV_PART_MAIN, State: LV_STATE_FOCUSED
    lv_obj_add_style(ui_scr->video_rec_img_video_set, &gui_img_main_focused_style, LV_PART_MAIN | LV_STATE_FOCUSED);

    //Set style for video_rec_img_video_set. Part: LV_PART_MAIN, State: LV_STATE_FOCUS_KEY
    lv_obj_set_style_img_opa(ui_scr->video_rec_img_video_set, 253, LV_PART_MAIN | LV_STATE_FOCUS_KEY);

    //Write codes video_rec_img_15
    ui_scr->video_rec_img_15 = lv_img_create(ui_scr->video_rec);
    lv_img_set_src(ui_scr->video_rec_img_15, gui_get_res_path(GUI_RES_CAMERA_PNG));
    lv_img_set_pivot(ui_scr->video_rec_img_15, 0, 0);
    lv_img_set_angle(ui_scr->video_rec_img_15, 0);
    lv_img_set_zoom(ui_scr->video_rec_img_15, 256);
    lv_obj_set_pos(ui_scr->video_rec_img_15, 742, 231);
    lv_obj_set_size(ui_scr->video_rec_img_15, 48, 48);
    lv_group_add_obj(def_group, ui_scr->video_rec_img_15);
    lv_obj_add_flag(ui_scr->video_rec_img_15, LV_OBJ_FLAG_CLICKABLE);
    ui_style_set(ui_scr->video_rec_img_15, GUI_CTRL_IMG);

    //Set style for video_rec_img_15. Part: LV_PART_MAIN, State: LV_STATE_FOCUSED
    lv_obj_add_style(ui_scr->video_rec_img_15, &gui_img_main_focused_style, LV_PART_MAIN | LV_STATE_FOCUSED);

    //Write codes video_rec_img_home
    ui_scr->video_rec_img_home = lv_img_create(ui_scr->video_rec);
    lv_img_set_src(ui_scr->video_rec_img_home, gui_get_res_path(GUI_RES_HOME_PNG));
    lv_img_set_pivot(ui_scr->video_rec_img_home, 0, 0);
    lv_img_set_angle(ui_scr->video_rec_img_home, 0);
    lv_img_set_zoom(ui_scr->video_rec_img_home, 256);
    lv_obj_set_pos(ui_scr->video_rec_img_home, 742, 338);
    lv_obj_set_size(ui_scr->video_rec_img_home, 48, 48);
    lv_group_add_obj(def_group, ui_scr->video_rec_img_home);
    lv_obj_add_flag(ui_scr->video_rec_img_home, LV_OBJ_FLAG_CLICKABLE);
    ui_style_set(ui_scr->video_rec_img_home, GUI_CTRL_IMG);

    //Set style for video_rec_img_home. Part: LV_PART_MAIN, State: LV_STATE_FOCUSED
    lv_obj_add_style(ui_scr->video_rec_img_home, &gui_img_main_focused_style, LV_PART_MAIN | LV_STATE_FOCUSED);

    //Write codes video_rec_imgbtn_lock_set
    ui_scr->video_rec_imgbtn_lock_set = lv_imgbtn_create(ui_scr->video_rec);
    lv_obj_set_pos(ui_scr->video_rec_imgbtn_lock_set, 613, 364);
    lv_obj_set_size(ui_scr->video_rec_imgbtn_lock_set, 64, 64);
    lv_obj_set_scrollbar_mode(ui_scr->video_rec_imgbtn_lock_set, LV_SCROLLBAR_MODE_OFF);
    lv_group_add_obj(def_group, ui_scr->video_rec_imgbtn_lock_set);
    ui_style_set(ui_scr->video_rec_imgbtn_lock_set, GUI_CTRL_IMGBTN);
    lv_imgbtn_set_src(ui_scr->video_rec_imgbtn_lock_set, LV_IMGBTN_STATE_RELEASED, NULL, gui_get_res_path(GUI_RES_BTN_LOCK_PNG), NULL);
    lv_imgbtn_set_src(ui_scr->video_rec_imgbtn_lock_set, LV_IMGBTN_STATE_PRESSED, NULL, gui_get_res_path(GUI_RES_BTN_LOCK_ON_PNG), NULL);
    lv_imgbtn_set_src(ui_scr->video_rec_imgbtn_lock_set, LV_IMGBTN_STATE_CHECKED_RELEASED, NULL, gui_get_res_path(GUI_RES_BTN_LOCK_PNG), NULL);
    lv_imgbtn_set_src(ui_scr->video_rec_imgbtn_lock_set, LV_IMGBTN_STATE_CHECKED_PRESSED, NULL, gui_get_res_path(GUI_RES_BTN_LOCK_ON_PNG), NULL);
    lv_obj_add_flag(ui_scr->video_rec_imgbtn_lock_set, LV_OBJ_FLAG_CHECKABLE);
    ui_scr->video_rec_imgbtn_lock_set_label = lv_label_create(ui_scr->video_rec_imgbtn_lock_set);
    lv_label_set_text(ui_scr->video_rec_imgbtn_lock_set_label, "");
    lv_obj_set_style_pad_all(ui_scr->video_rec_imgbtn_lock_set, 0, LV_STATE_DEFAULT);
    lv_obj_align(ui_scr->video_rec_imgbtn_lock_set_label, LV_ALIGN_CENTER, 0, 0);

    //Write codes video_rec_imgbtn_sw_window
    ui_scr->video_rec_imgbtn_sw_window = lv_imgbtn_create(ui_scr->video_rec);
    lv_obj_set_pos(ui_scr->video_rec_imgbtn_sw_window, 613, 91);
    lv_obj_set_size(ui_scr->video_rec_imgbtn_sw_window, 64, 64);
    lv_obj_set_scrollbar_mode(ui_scr->video_rec_imgbtn_sw_window, LV_SCROLLBAR_MODE_OFF);
    lv_obj_add_flag(ui_scr->video_rec_imgbtn_sw_window, LV_OBJ_FLAG_HIDDEN);
    lv_group_add_obj(def_group, ui_scr->video_rec_imgbtn_sw_window);
    ui_style_set(ui_scr->video_rec_imgbtn_sw_window, GUI_CTRL_IMGBTN);
    lv_imgbtn_set_src(ui_scr->video_rec_imgbtn_sw_window, LV_IMGBTN_STATE_RELEASED, NULL, gui_get_res_path(GUI_RES_SWITCH_PNG), NULL);
    lv_imgbtn_set_src(ui_scr->video_rec_imgbtn_sw_window, LV_IMGBTN_STATE_PRESSED, NULL, gui_get_res_path(GUI_RES_SWITCH_ON_PNG), NULL);
    lv_imgbtn_set_src(ui_scr->video_rec_imgbtn_sw_window, LV_IMGBTN_STATE_CHECKED_RELEASED, NULL, gui_get_res_path(GUI_RES_SWITCH_PNG), NULL);
    lv_imgbtn_set_src(ui_scr->video_rec_imgbtn_sw_window, LV_IMGBTN_STATE_CHECKED_PRESSED, NULL, gui_get_res_path(GUI_RES_SWITCH_ON_PNG), NULL);
    lv_obj_add_flag(ui_scr->video_rec_imgbtn_sw_window, LV_OBJ_FLAG_CHECKABLE);
    ui_scr->video_rec_imgbtn_sw_window_label = lv_label_create(ui_scr->video_rec_imgbtn_sw_window);
    lv_label_set_text(ui_scr->video_rec_imgbtn_sw_window_label, "");
    lv_obj_set_style_pad_all(ui_scr->video_rec_imgbtn_sw_window, 0, LV_STATE_DEFAULT);
    lv_obj_align(ui_scr->video_rec_imgbtn_sw_window_label, LV_ALIGN_CENTER, 0, 0);

    static bool timer_video_rec_digitclock_remain_time_enabled = false;
    //Write codes video_rec_digitclock_remain_time
    ui_scr->video_rec_digitclock_remain_time = lv_label_create(ui_scr->video_rec);
    lv_label_set_text_fmt(ui_scr->video_rec_digitclock_remain_time, "%02d:%02d:%02d", 21 % 12, 25, 50);
    lv_obj_set_style_text_align(ui_scr->video_rec_digitclock_remain_time, LV_TEXT_ALIGN_CENTER, 0);
    lv_obj_set_pos(ui_scr->video_rec_digitclock_remain_time, 270, 62);
    lv_obj_set_size(ui_scr->video_rec_digitclock_remain_time, 186, 52);
    ui_style_set(ui_scr->video_rec_digitclock_remain_time, GUI_CTRL_DIGITALCLOCK);

    //Set style for video_rec_digitclock_remain_time. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
    lv_obj_set_style_text_color(ui_scr->video_rec_digitclock_remain_time, lv_color_make(0xFF, 0xFF, 0xFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_scr->video_rec_digitclock_remain_time, &lv_font_FangZhengKaiTiJianTi_1_32, LV_PART_MAIN | LV_STATE_DEFAULT);

    static bool timer_video_rec_digitclock_record_time_enabled = false;
    //Write codes video_rec_digitclock_record_time
    ui_scr->video_rec_digitclock_record_time = lv_label_create(ui_scr->video_rec);
    lv_label_set_text_fmt(ui_scr->video_rec_digitclock_record_time, "%02d:%02d:%02d", 00 % 12, 00, 00);
    lv_obj_set_style_text_align(ui_scr->video_rec_digitclock_record_time, LV_TEXT_ALIGN_CENTER, 0);
    lv_obj_set_pos(ui_scr->video_rec_digitclock_record_time, 270, 62);
    lv_obj_set_size(ui_scr->video_rec_digitclock_record_time, 186, 52);
    lv_obj_add_flag(ui_scr->video_rec_digitclock_record_time, LV_OBJ_FLAG_HIDDEN);

    //Hidden for widget video_rec_digitclock_record_time
    lv_obj_add_flag(ui_scr->video_rec_digitclock_record_time, LV_OBJ_FLAG_HIDDEN);
    ui_style_set(ui_scr->video_rec_digitclock_record_time, GUI_CTRL_DIGITALCLOCK);

    //Set style for video_rec_digitclock_record_time. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
    lv_obj_set_style_text_color(ui_scr->video_rec_digitclock_record_time, lv_color_make(0xFF, 0xFF, 0xFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_scr->video_rec_digitclock_record_time, &lv_font_FangZhengKaiTiJianTi_1_32, LV_PART_MAIN | LV_STATE_DEFAULT);

    //Write codes video_rec_view_video_set
    ui_scr->video_rec_view_video_set = lv_obj_create(ui_scr->video_rec);
    lv_obj_set_pos(ui_scr->video_rec_view_video_set, 295, 0);
    lv_obj_set_size(ui_scr->video_rec_view_video_set, 430, 480);
    lv_obj_set_scrollbar_mode(ui_scr->video_rec_view_video_set, LV_SCROLLBAR_MODE_OFF);
    lv_obj_add_flag(ui_scr->video_rec_view_video_set, LV_OBJ_FLAG_HIDDEN);
    ui_style_set(ui_scr->video_rec_view_video_set, GUI_CTRL_CONT);

    //Set style for video_rec_view_video_set. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
    lv_obj_set_style_bg_color(ui_scr->video_rec_view_video_set, lv_color_make(0x00, 0x00, 0x00), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_scr->video_rec_view_video_set, 179, LV_PART_MAIN | LV_STATE_DEFAULT);

    //Write codes video_rec_img_resolution
    ui_scr->video_rec_img_resolution = lv_img_create(ui_scr->video_rec_view_video_set);
    lv_img_set_src(ui_scr->video_rec_img_resolution, gui_get_res_path(GUI_RES_RESOLUTION_RATIO_PNG));
    lv_img_set_pivot(ui_scr->video_rec_img_resolution, 0, 0);
    lv_img_set_angle(ui_scr->video_rec_img_resolution, 0);
    lv_img_set_zoom(ui_scr->video_rec_img_resolution, 256);
    lv_obj_set_pos(ui_scr->video_rec_img_resolution, 31, 36);
    lv_obj_set_size(ui_scr->video_rec_img_resolution, 80, 80);
    lv_obj_add_flag(ui_scr->video_rec_img_resolution, LV_OBJ_FLAG_EVENT_BUBBLE);
    lv_group_add_obj(def_group, ui_scr->video_rec_img_resolution);
    lv_obj_add_flag(ui_scr->video_rec_img_resolution, LV_OBJ_FLAG_CLICKABLE);
    ui_style_set(ui_scr->video_rec_img_resolution, GUI_CTRL_IMG);

    //Write codes video_rec_img_19
    ui_scr->video_rec_img_19 = lv_img_create(ui_scr->video_rec_view_video_set);
    lv_img_set_src(ui_scr->video_rec_img_19, gui_get_res_path(GUI_RES_DOUBLE_VIDEO_PNG));
    lv_img_set_pivot(ui_scr->video_rec_img_19, 0, 0);
    lv_img_set_angle(ui_scr->video_rec_img_19, 0);
    lv_img_set_zoom(ui_scr->video_rec_img_19, 256);
    lv_obj_set_pos(ui_scr->video_rec_img_19, 133, 36);
    lv_obj_set_size(ui_scr->video_rec_img_19, 80, 80);
    lv_obj_add_flag(ui_scr->video_rec_img_19, LV_OBJ_FLAG_EVENT_BUBBLE);
    lv_group_add_obj(def_group, ui_scr->video_rec_img_19);
    lv_obj_add_flag(ui_scr->video_rec_img_19, LV_OBJ_FLAG_CLICKABLE);
    ui_style_set(ui_scr->video_rec_img_19, GUI_CTRL_IMG);

    //Write codes video_rec_img_20
    ui_scr->video_rec_img_20 = lv_img_create(ui_scr->video_rec_view_video_set);
    lv_img_set_src(ui_scr->video_rec_img_20, gui_get_res_path(GUI_RES_CYCLIC_VIDEO_PNG));
    lv_img_set_pivot(ui_scr->video_rec_img_20, 0, 0);
    lv_img_set_angle(ui_scr->video_rec_img_20, 0);
    lv_img_set_zoom(ui_scr->video_rec_img_20, 256);
    lv_obj_set_pos(ui_scr->video_rec_img_20, 235, 36);
    lv_obj_set_size(ui_scr->video_rec_img_20, 80, 80);
    lv_obj_add_flag(ui_scr->video_rec_img_20, LV_OBJ_FLAG_EVENT_BUBBLE);
    lv_group_add_obj(def_group, ui_scr->video_rec_img_20);
    lv_obj_add_flag(ui_scr->video_rec_img_20, LV_OBJ_FLAG_CLICKABLE);
    ui_style_set(ui_scr->video_rec_img_20, GUI_CTRL_IMG);

    //Set style for video_rec_img_20. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
    lv_obj_set_style_img_recolor(ui_scr->video_rec_img_20, lv_color_make(0xFF, 0xFF, 0xFF), LV_PART_MAIN | LV_STATE_DEFAULT);

    //Write codes video_rec_img_21
    ui_scr->video_rec_img_21 = lv_img_create(ui_scr->video_rec_view_video_set);
    lv_img_set_src(ui_scr->video_rec_img_21, gui_get_res_path(GUI_RES_INTERVAL_VIDEO_PNG));
    lv_img_set_pivot(ui_scr->video_rec_img_21, 0, 0);
    lv_img_set_angle(ui_scr->video_rec_img_21, 0);
    lv_img_set_zoom(ui_scr->video_rec_img_21, 256);
    lv_obj_set_pos(ui_scr->video_rec_img_21, 338, 36);
    lv_obj_set_size(ui_scr->video_rec_img_21, 80, 80);
    lv_obj_add_flag(ui_scr->video_rec_img_21, LV_OBJ_FLAG_EVENT_BUBBLE);
    lv_group_add_obj(def_group, ui_scr->video_rec_img_21);
    lv_obj_add_flag(ui_scr->video_rec_img_21, LV_OBJ_FLAG_CLICKABLE);
    ui_style_set(ui_scr->video_rec_img_21, GUI_CTRL_IMG);

    //Set style for video_rec_img_21. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
    lv_obj_set_style_img_recolor(ui_scr->video_rec_img_21, lv_color_make(0xFF, 0xFF, 0xFF), LV_PART_MAIN | LV_STATE_DEFAULT);

    //Write codes video_rec_lbl_5
    ui_scr->video_rec_lbl_5 = lv_label_create(ui_scr->video_rec_view_video_set);
    lv_label_set_long_mode(ui_scr->video_rec_lbl_5, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui_scr->video_rec_lbl_5, 31, 123);
    lv_obj_set_size(ui_scr->video_rec_lbl_5, 78, 53);
    lv_obj_set_scrollbar_mode(ui_scr->video_rec_lbl_5, LV_SCROLLBAR_MODE_OFF);
    ui_style_set(ui_scr->video_rec_lbl_5, GUI_CTRL_LABEL);

    //Write codes video_rec_lbl_6
    ui_scr->video_rec_lbl_6 = lv_label_create(ui_scr->video_rec_view_video_set);
    lv_label_set_long_mode(ui_scr->video_rec_lbl_6, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui_scr->video_rec_lbl_6, 133, 123);
    lv_obj_set_size(ui_scr->video_rec_lbl_6, 78, 53);
    lv_obj_set_scrollbar_mode(ui_scr->video_rec_lbl_6, LV_SCROLLBAR_MODE_OFF);
    ui_style_set(ui_scr->video_rec_lbl_6, GUI_CTRL_LABEL);

    //Write codes video_rec_lbl_7
    ui_scr->video_rec_lbl_7 = lv_label_create(ui_scr->video_rec_view_video_set);
    lv_label_set_long_mode(ui_scr->video_rec_lbl_7, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui_scr->video_rec_lbl_7, 235, 123);
    lv_obj_set_size(ui_scr->video_rec_lbl_7, 78, 53);
    lv_obj_set_scrollbar_mode(ui_scr->video_rec_lbl_7, LV_SCROLLBAR_MODE_OFF);
    ui_style_set(ui_scr->video_rec_lbl_7, GUI_CTRL_LABEL);

    //Write codes video_rec_lbl_8
    ui_scr->video_rec_lbl_8 = lv_label_create(ui_scr->video_rec_view_video_set);
    lv_label_set_long_mode(ui_scr->video_rec_lbl_8, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui_scr->video_rec_lbl_8, 342, 123);
    lv_obj_set_size(ui_scr->video_rec_lbl_8, 78, 53);
    lv_obj_set_scrollbar_mode(ui_scr->video_rec_lbl_8, LV_SCROLLBAR_MODE_OFF);
    ui_style_set(ui_scr->video_rec_lbl_8, GUI_CTRL_LABEL);

    //Write codes video_rec_img_1
    ui_scr->video_rec_img_1 = lv_img_create(ui_scr->video_rec_view_video_set);
    lv_img_set_src(ui_scr->video_rec_img_1, gui_get_res_path(GUI_RES_HDR_PNG));
    lv_img_set_pivot(ui_scr->video_rec_img_1, 0, 0);
    lv_img_set_angle(ui_scr->video_rec_img_1, 0);
    lv_img_set_zoom(ui_scr->video_rec_img_1, 256);
    lv_obj_set_pos(ui_scr->video_rec_img_1, 31, 183);
    lv_obj_set_size(ui_scr->video_rec_img_1, 80, 80);
    lv_obj_add_flag(ui_scr->video_rec_img_1, LV_OBJ_FLAG_EVENT_BUBBLE);
    lv_group_add_obj(def_group, ui_scr->video_rec_img_1);
    lv_obj_add_flag(ui_scr->video_rec_img_1, LV_OBJ_FLAG_CLICKABLE);
    ui_style_set(ui_scr->video_rec_img_1, GUI_CTRL_IMG);

    //Write codes video_rec_img_10
    ui_scr->video_rec_img_10 = lv_img_create(ui_scr->video_rec_view_video_set);
    lv_img_set_src(ui_scr->video_rec_img_10, gui_get_res_path(GUI_RES_EXPOSURE_PNG));
    lv_img_set_pivot(ui_scr->video_rec_img_10, 0, 0);
    lv_img_set_angle(ui_scr->video_rec_img_10, 0);
    lv_img_set_zoom(ui_scr->video_rec_img_10, 256);
    lv_obj_set_pos(ui_scr->video_rec_img_10, 133, 183);
    lv_obj_set_size(ui_scr->video_rec_img_10, 80, 80);
    lv_obj_add_flag(ui_scr->video_rec_img_10, LV_OBJ_FLAG_EVENT_BUBBLE);
    lv_group_add_obj(def_group, ui_scr->video_rec_img_10);
    lv_obj_add_flag(ui_scr->video_rec_img_10, LV_OBJ_FLAG_CLICKABLE);
    ui_style_set(ui_scr->video_rec_img_10, GUI_CTRL_IMG);

    //Write codes video_rec_img_17
    ui_scr->video_rec_img_17 = lv_img_create(ui_scr->video_rec_view_video_set);
    lv_img_set_src(ui_scr->video_rec_img_17, gui_get_res_path(GUI_RES_CHECK_SPORT_1_PNG));
    lv_img_set_pivot(ui_scr->video_rec_img_17, 0, 0);
    lv_img_set_angle(ui_scr->video_rec_img_17, 0);
    lv_img_set_zoom(ui_scr->video_rec_img_17, 256);
    lv_obj_set_pos(ui_scr->video_rec_img_17, 235, 183);
    lv_obj_set_size(ui_scr->video_rec_img_17, 80, 80);
    lv_obj_add_flag(ui_scr->video_rec_img_17, LV_OBJ_FLAG_EVENT_BUBBLE);
    lv_group_add_obj(def_group, ui_scr->video_rec_img_17);
    lv_obj_add_flag(ui_scr->video_rec_img_17, LV_OBJ_FLAG_CLICKABLE);
    ui_style_set(ui_scr->video_rec_img_17, GUI_CTRL_IMG);

    //Write codes video_rec_img_18
    ui_scr->video_rec_img_18 = lv_img_create(ui_scr->video_rec_view_video_set);
    lv_img_set_src(ui_scr->video_rec_img_18, gui_get_res_path(GUI_RES_DATE_PNG));
    lv_img_set_pivot(ui_scr->video_rec_img_18, 0, 0);
    lv_img_set_angle(ui_scr->video_rec_img_18, 0);
    lv_img_set_zoom(ui_scr->video_rec_img_18, 256);
    lv_obj_set_pos(ui_scr->video_rec_img_18, 337, 183);
    lv_obj_set_size(ui_scr->video_rec_img_18, 80, 80);
    lv_obj_add_flag(ui_scr->video_rec_img_18, LV_OBJ_FLAG_EVENT_BUBBLE);
    lv_group_add_obj(def_group, ui_scr->video_rec_img_18);
    lv_obj_add_flag(ui_scr->video_rec_img_18, LV_OBJ_FLAG_CLICKABLE);
    ui_style_set(ui_scr->video_rec_img_18, GUI_CTRL_IMG);

    //Write codes video_rec_lbl_13
    ui_scr->video_rec_lbl_13 = lv_label_create(ui_scr->video_rec_view_video_set);
    lv_label_set_text(ui_scr->video_rec_lbl_13, "HDR");
    lv_label_set_long_mode(ui_scr->video_rec_lbl_13, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui_scr->video_rec_lbl_13, 22, 264);
    lv_obj_set_size(ui_scr->video_rec_lbl_13, 90, 34);
    lv_obj_set_scrollbar_mode(ui_scr->video_rec_lbl_13, LV_SCROLLBAR_MODE_OFF);
    ui_style_set(ui_scr->video_rec_lbl_13, GUI_CTRL_LABEL);

    //Write codes video_rec_lbl_14
    ui_scr->video_rec_lbl_14 = lv_label_create(ui_scr->video_rec_view_video_set);
    lv_label_set_long_mode(ui_scr->video_rec_lbl_14, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui_scr->video_rec_lbl_14, 31, 413);
    lv_obj_set_size(ui_scr->video_rec_lbl_14, 78, 53);
    lv_obj_set_scrollbar_mode(ui_scr->video_rec_lbl_14, LV_SCROLLBAR_MODE_OFF);
    ui_style_set(ui_scr->video_rec_lbl_14, GUI_CTRL_LABEL);

    //Write codes video_rec_img_3
    ui_scr->video_rec_img_3 = lv_img_create(ui_scr->video_rec_view_video_set);
    lv_img_set_src(ui_scr->video_rec_img_3, gui_get_res_path(GUI_RES_GRAVITY_SENSOR_PNG));
    lv_img_set_pivot(ui_scr->video_rec_img_3, 0, 0);
    lv_img_set_angle(ui_scr->video_rec_img_3, 0);
    lv_img_set_zoom(ui_scr->video_rec_img_3, 256);
    lv_obj_set_pos(ui_scr->video_rec_img_3, 31, 330);
    lv_obj_set_size(ui_scr->video_rec_img_3, 80, 80);
    lv_obj_add_flag(ui_scr->video_rec_img_3, LV_OBJ_FLAG_EVENT_BUBBLE);
    lv_group_add_obj(def_group, ui_scr->video_rec_img_3);
    lv_obj_add_flag(ui_scr->video_rec_img_3, LV_OBJ_FLAG_CLICKABLE);
    ui_style_set(ui_scr->video_rec_img_3, GUI_CTRL_IMG);

    //Write codes video_rec_img_22
    ui_scr->video_rec_img_22 = lv_img_create(ui_scr->video_rec_view_video_set);
    lv_img_set_src(ui_scr->video_rec_img_22, gui_get_res_path(GUI_RES_SOUND_PNG));
    lv_img_set_pivot(ui_scr->video_rec_img_22, 0, 0);
    lv_img_set_angle(ui_scr->video_rec_img_22, 0);
    lv_img_set_zoom(ui_scr->video_rec_img_22, 256);
    lv_obj_set_pos(ui_scr->video_rec_img_22, 132, 330);
    lv_obj_set_size(ui_scr->video_rec_img_22, 80, 80);
    lv_obj_add_flag(ui_scr->video_rec_img_22, LV_OBJ_FLAG_EVENT_BUBBLE);
    lv_group_add_obj(def_group, ui_scr->video_rec_img_22);
    lv_obj_add_flag(ui_scr->video_rec_img_22, LV_OBJ_FLAG_CLICKABLE);
    ui_style_set(ui_scr->video_rec_img_22, GUI_CTRL_IMG);

    //Write codes video_rec_img_23
    ui_scr->video_rec_img_23 = lv_img_create(ui_scr->video_rec_view_video_set);
    lv_img_set_src(ui_scr->video_rec_img_23, gui_get_res_path(GUI_RES_STOPPING_MONITOR_1_PNG));
    lv_img_set_pivot(ui_scr->video_rec_img_23, 0, 0);
    lv_img_set_angle(ui_scr->video_rec_img_23, 0);
    lv_img_set_zoom(ui_scr->video_rec_img_23, 256);
    lv_obj_set_pos(ui_scr->video_rec_img_23, 233, 330);
    lv_obj_set_size(ui_scr->video_rec_img_23, 80, 80);
    lv_obj_add_flag(ui_scr->video_rec_img_23, LV_OBJ_FLAG_EVENT_BUBBLE);
    lv_group_add_obj(def_group, ui_scr->video_rec_img_23);
    lv_obj_add_flag(ui_scr->video_rec_img_23, LV_OBJ_FLAG_CLICKABLE);
    ui_style_set(ui_scr->video_rec_img_23, GUI_CTRL_IMG);

    //Write codes video_rec_img_24
    ui_scr->video_rec_img_24 = lv_img_create(ui_scr->video_rec_view_video_set);
    lv_img_set_src(ui_scr->video_rec_img_24, gui_get_res_path(GUI_RES_CAR_NUM_PNG));
    lv_img_set_pivot(ui_scr->video_rec_img_24, 0, 0);
    lv_img_set_angle(ui_scr->video_rec_img_24, 0);
    lv_img_set_zoom(ui_scr->video_rec_img_24, 256);
    lv_obj_set_pos(ui_scr->video_rec_img_24, 337, 330);
    lv_obj_set_size(ui_scr->video_rec_img_24, 80, 80);
    lv_obj_add_flag(ui_scr->video_rec_img_24, LV_OBJ_FLAG_EVENT_BUBBLE);
    lv_group_add_obj(def_group, ui_scr->video_rec_img_24);
    lv_obj_add_flag(ui_scr->video_rec_img_24, LV_OBJ_FLAG_CLICKABLE);
    ui_style_set(ui_scr->video_rec_img_24, GUI_CTRL_IMG);

    //Write codes video_rec_lbl_15
    ui_scr->video_rec_lbl_15 = lv_label_create(ui_scr->video_rec_view_video_set);
    lv_label_set_long_mode(ui_scr->video_rec_lbl_15, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui_scr->video_rec_lbl_15, 129, 264);
    lv_obj_set_size(ui_scr->video_rec_lbl_15, 90, 53);
    lv_obj_set_scrollbar_mode(ui_scr->video_rec_lbl_15, LV_SCROLLBAR_MODE_OFF);
    ui_style_set(ui_scr->video_rec_lbl_15, GUI_CTRL_LABEL);

    //Write codes video_rec_lbl_16
    ui_scr->video_rec_lbl_16 = lv_label_create(ui_scr->video_rec_view_video_set);
    lv_label_set_long_mode(ui_scr->video_rec_lbl_16, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui_scr->video_rec_lbl_16, 230, 264);
    lv_obj_set_size(ui_scr->video_rec_lbl_16, 90, 53);
    lv_obj_set_scrollbar_mode(ui_scr->video_rec_lbl_16, LV_SCROLLBAR_MODE_OFF);
    ui_style_set(ui_scr->video_rec_lbl_16, GUI_CTRL_LABEL);

    //Write codes video_rec_lbl_17
    ui_scr->video_rec_lbl_17 = lv_label_create(ui_scr->video_rec_view_video_set);
    lv_label_set_long_mode(ui_scr->video_rec_lbl_17, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui_scr->video_rec_lbl_17, 332, 264);
    lv_obj_set_size(ui_scr->video_rec_lbl_17, 90, 53);
    lv_obj_set_scrollbar_mode(ui_scr->video_rec_lbl_17, LV_SCROLLBAR_MODE_OFF);
    ui_style_set(ui_scr->video_rec_lbl_17, GUI_CTRL_LABEL);

    //Write codes video_rec_lbl_18
    ui_scr->video_rec_lbl_18 = lv_label_create(ui_scr->video_rec_view_video_set);
    lv_label_set_long_mode(ui_scr->video_rec_lbl_18, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui_scr->video_rec_lbl_18, 133, 413);
    lv_obj_set_size(ui_scr->video_rec_lbl_18, 76, 53);
    lv_obj_set_scrollbar_mode(ui_scr->video_rec_lbl_18, LV_SCROLLBAR_MODE_OFF);
    ui_style_set(ui_scr->video_rec_lbl_18, GUI_CTRL_LABEL);

    //Write codes video_rec_lbl_19
    ui_scr->video_rec_lbl_19 = lv_label_create(ui_scr->video_rec_view_video_set);
    lv_label_set_long_mode(ui_scr->video_rec_lbl_19, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui_scr->video_rec_lbl_19, 225, 413);
    lv_obj_set_size(ui_scr->video_rec_lbl_19, 90, 53);
    lv_obj_set_scrollbar_mode(ui_scr->video_rec_lbl_19, LV_SCROLLBAR_MODE_OFF);
    ui_style_set(ui_scr->video_rec_lbl_19, GUI_CTRL_LABEL);

    //Write codes video_rec_lbl_20
    ui_scr->video_rec_lbl_20 = lv_label_create(ui_scr->video_rec_view_video_set);
    lv_label_set_long_mode(ui_scr->video_rec_lbl_20, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui_scr->video_rec_lbl_20, 327, 413);
    lv_obj_set_size(ui_scr->video_rec_lbl_20, 90, 53);
    lv_obj_set_scrollbar_mode(ui_scr->video_rec_lbl_20, LV_SCROLLBAR_MODE_OFF);
    ui_style_set(ui_scr->video_rec_lbl_20, GUI_CTRL_LABEL);

    //Write codes video_rec_view_subpage
    ui_scr->video_rec_view_subpage = lv_obj_create(ui_scr->video_rec);
    lv_obj_set_pos(ui_scr->video_rec_view_subpage, 186, 240);
    lv_obj_set_size(ui_scr->video_rec_view_subpage, 539, 237);
    lv_obj_set_scrollbar_mode(ui_scr->video_rec_view_subpage, LV_SCROLLBAR_MODE_OFF);
    lv_obj_add_flag(ui_scr->video_rec_view_subpage, LV_OBJ_FLAG_HIDDEN);
    ui_style_set(ui_scr->video_rec_view_subpage, GUI_CTRL_CONT);

    //Set style for video_rec_view_subpage. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
    lv_obj_set_style_bg_color(ui_scr->video_rec_view_subpage, lv_color_make(0x00, 0x00, 0x00), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_scr->video_rec_view_subpage, 204, LV_PART_MAIN | LV_STATE_DEFAULT);

    //Write codes video_rec_img_16
    ui_scr->video_rec_img_16 = lv_img_create(ui_scr->video_rec_view_subpage);
    lv_img_set_src(ui_scr->video_rec_img_16, gui_get_res_path(GUI_RES_RESOLUTION_RATIO_PNG));
    lv_img_set_pivot(ui_scr->video_rec_img_16, 0, 0);
    lv_img_set_angle(ui_scr->video_rec_img_16, 0);
    lv_img_set_zoom(ui_scr->video_rec_img_16, 256);
    lv_obj_set_pos(ui_scr->video_rec_img_16, 28, 7);
    lv_obj_set_size(ui_scr->video_rec_img_16, 80, 80);
    lv_obj_add_flag(ui_scr->video_rec_img_16, LV_OBJ_FLAG_EVENT_BUBBLE);
    lv_obj_add_flag(ui_scr->video_rec_img_16, LV_OBJ_FLAG_CLICKABLE);
    lv_obj_add_flag(ui_scr->video_rec_img_16, LV_OBJ_FLAG_CLICKABLE);
    ui_style_set(ui_scr->video_rec_img_16, GUI_CTRL_IMG);

    //Delete extra default style for video_rec_img_16
    lv_obj_remove_style(ui_scr->video_rec_img_16, &gui_img_main_focus_key_style, LV_PART_MAIN | LV_STATE_FOCUS_KEY);

    //Write codes video_rec_lbl_menu_title
    ui_scr->video_rec_lbl_menu_title = lv_label_create(ui_scr->video_rec_view_subpage);
    lv_label_set_long_mode(ui_scr->video_rec_lbl_menu_title, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui_scr->video_rec_lbl_menu_title, 111, 7);
    lv_obj_set_size(ui_scr->video_rec_lbl_menu_title, 201, 53);
    lv_obj_set_scrollbar_mode(ui_scr->video_rec_lbl_menu_title, LV_SCROLLBAR_MODE_OFF);
    ui_style_set(ui_scr->video_rec_lbl_menu_title, GUI_CTRL_LABEL);

    //Set style for video_rec_lbl_menu_title. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
    lv_obj_set_style_text_align(ui_scr->video_rec_lbl_menu_title, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui_scr->video_rec_lbl_menu_title, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

    //Write codes video_rec_lbl_funkey1
    ui_scr->video_rec_lbl_funkey1 = lv_btn_create(ui_scr->video_rec_view_subpage);
    lv_obj_set_pos(ui_scr->video_rec_lbl_funkey1, 18, 172);
    lv_obj_set_size(ui_scr->video_rec_lbl_funkey1, 121, 60);
    lv_obj_set_scrollbar_mode(ui_scr->video_rec_lbl_funkey1, LV_SCROLLBAR_MODE_OFF);
    lv_obj_add_flag(ui_scr->video_rec_lbl_funkey1, LV_OBJ_FLAG_CLICKABLE);
    lv_obj_add_flag(ui_scr->video_rec_lbl_funkey1, LV_OBJ_FLAG_EVENT_BUBBLE);
    ui_style_set(ui_scr->video_rec_lbl_funkey1, GUI_CTRL_BUTTON);

    //Set style for video_rec_lbl_funkey1. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
    lv_obj_set_style_radius(ui_scr->video_rec_lbl_funkey1, 20, LV_PART_MAIN | LV_STATE_DEFAULT);

    //Set style for video_rec_lbl_funkey1. Part: LV_PART_MAIN, State: LV_STATE_FOCUSED
    lv_obj_set_style_radius(ui_scr->video_rec_lbl_funkey1, 20, LV_PART_MAIN | LV_STATE_FOCUSED);

    //Set style for video_rec_lbl_funkey1. Part: LV_PART_MAIN, State: LV_STATE_FOCUS_KEY
    lv_obj_set_style_radius(ui_scr->video_rec_lbl_funkey1, 20, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    ui_scr->video_rec_lbl_funkey1_label = lv_label_create(ui_scr->video_rec_lbl_funkey1);
    lv_obj_set_style_pad_all(ui_scr->video_rec_lbl_funkey1, 0, LV_STATE_DEFAULT);
    lv_obj_align(ui_scr->video_rec_lbl_funkey1_label, LV_ALIGN_CENTER, 0, 0);

    //Write codes video_rec_lbl_funkey2
    ui_scr->video_rec_lbl_funkey2 = lv_btn_create(ui_scr->video_rec_view_subpage);
    lv_obj_set_pos(ui_scr->video_rec_lbl_funkey2, 149, 172);
    lv_obj_set_size(ui_scr->video_rec_lbl_funkey2, 121, 60);
    lv_obj_set_scrollbar_mode(ui_scr->video_rec_lbl_funkey2, LV_SCROLLBAR_MODE_OFF);
    lv_obj_add_flag(ui_scr->video_rec_lbl_funkey2, LV_OBJ_FLAG_CLICKABLE);
    lv_obj_add_flag(ui_scr->video_rec_lbl_funkey2, LV_OBJ_FLAG_EVENT_BUBBLE);
    ui_style_set(ui_scr->video_rec_lbl_funkey2, GUI_CTRL_BUTTON);

    //Set style for video_rec_lbl_funkey2. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
    lv_obj_set_style_radius(ui_scr->video_rec_lbl_funkey2, 20, LV_PART_MAIN | LV_STATE_DEFAULT);

    //Set style for video_rec_lbl_funkey2. Part: LV_PART_MAIN, State: LV_STATE_FOCUSED
    lv_obj_set_style_radius(ui_scr->video_rec_lbl_funkey2, 20, LV_PART_MAIN | LV_STATE_FOCUSED);

    //Set style for video_rec_lbl_funkey2. Part: LV_PART_MAIN, State: LV_STATE_FOCUS_KEY
    lv_obj_set_style_radius(ui_scr->video_rec_lbl_funkey2, 20, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    ui_scr->video_rec_lbl_funkey2_label = lv_label_create(ui_scr->video_rec_lbl_funkey2);
    lv_obj_set_size(ui_scr->video_rec_lbl_funkey2_label, 120, 32);
    lv_label_set_long_mode(ui_scr->video_rec_lbl_funkey2_label, LV_LABEL_LONG_SCROLL);
    lv_obj_set_style_pad_all(ui_scr->video_rec_lbl_funkey2, 0, LV_STATE_DEFAULT);
    lv_obj_align(ui_scr->video_rec_lbl_funkey2_label, LV_ALIGN_CENTER, 0, 0);

    //Write codes video_rec_lbl_funkey3
    ui_scr->video_rec_lbl_funkey3 = lv_btn_create(ui_scr->video_rec_view_subpage);
    lv_obj_set_pos(ui_scr->video_rec_lbl_funkey3, 280, 172);
    lv_obj_set_size(ui_scr->video_rec_lbl_funkey3, 121, 60);
    lv_obj_set_scrollbar_mode(ui_scr->video_rec_lbl_funkey3, LV_SCROLLBAR_MODE_OFF);
    lv_obj_add_flag(ui_scr->video_rec_lbl_funkey3, LV_OBJ_FLAG_CLICKABLE);
    lv_obj_add_flag(ui_scr->video_rec_lbl_funkey3, LV_OBJ_FLAG_EVENT_BUBBLE);
    ui_style_set(ui_scr->video_rec_lbl_funkey3, GUI_CTRL_BUTTON);

    //Set style for video_rec_lbl_funkey3. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
    lv_obj_set_style_radius(ui_scr->video_rec_lbl_funkey3, 20, LV_PART_MAIN | LV_STATE_DEFAULT);

    //Set style for video_rec_lbl_funkey3. Part: LV_PART_MAIN, State: LV_STATE_FOCUSED
    lv_obj_set_style_radius(ui_scr->video_rec_lbl_funkey3, 20, LV_PART_MAIN | LV_STATE_FOCUSED);

    //Set style for video_rec_lbl_funkey3. Part: LV_PART_MAIN, State: LV_STATE_FOCUS_KEY
    lv_obj_set_style_radius(ui_scr->video_rec_lbl_funkey3, 20, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    ui_scr->video_rec_lbl_funkey3_label = lv_label_create(ui_scr->video_rec_lbl_funkey3);
    lv_obj_set_size(ui_scr->video_rec_lbl_funkey3_label, 120, 32);
    lv_label_set_long_mode(ui_scr->video_rec_lbl_funkey3_label, LV_LABEL_LONG_SCROLL);
    lv_obj_set_style_pad_all(ui_scr->video_rec_lbl_funkey3, 0, LV_STATE_DEFAULT);
    lv_obj_align(ui_scr->video_rec_lbl_funkey3_label, LV_ALIGN_CENTER, 0, 0);

    //Write codes video_rec_lbl_funkey4
    ui_scr->video_rec_lbl_funkey4 = lv_btn_create(ui_scr->video_rec_view_subpage);
    lv_obj_set_pos(ui_scr->video_rec_lbl_funkey4, 411, 172);
    lv_obj_set_size(ui_scr->video_rec_lbl_funkey4, 121, 60);
    lv_obj_set_scrollbar_mode(ui_scr->video_rec_lbl_funkey4, LV_SCROLLBAR_MODE_OFF);
    lv_obj_add_flag(ui_scr->video_rec_lbl_funkey4, LV_OBJ_FLAG_CLICKABLE);
    lv_obj_add_flag(ui_scr->video_rec_lbl_funkey4, LV_OBJ_FLAG_EVENT_BUBBLE);
    ui_style_set(ui_scr->video_rec_lbl_funkey4, GUI_CTRL_BUTTON);

    //Set style for video_rec_lbl_funkey4. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
    lv_obj_set_style_radius(ui_scr->video_rec_lbl_funkey4, 20, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui_scr->video_rec_lbl_funkey4, lv_color_make(0xFF, 0xFF, 0xFF), LV_PART_MAIN | LV_STATE_DEFAULT);

    //Set style for video_rec_lbl_funkey4. Part: LV_PART_MAIN, State: LV_STATE_FOCUSED
    lv_obj_set_style_radius(ui_scr->video_rec_lbl_funkey4, 20, LV_PART_MAIN | LV_STATE_FOCUSED);

    //Set style for video_rec_lbl_funkey4. Part: LV_PART_MAIN, State: LV_STATE_FOCUS_KEY
    lv_obj_set_style_radius(ui_scr->video_rec_lbl_funkey4, 20, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    ui_scr->video_rec_lbl_funkey4_label = lv_label_create(ui_scr->video_rec_lbl_funkey4);
    lv_obj_set_size(ui_scr->video_rec_lbl_funkey4_label, 120, 32);
    lv_label_set_long_mode(ui_scr->video_rec_lbl_funkey4_label, LV_LABEL_LONG_SCROLL);
    lv_obj_set_style_pad_all(ui_scr->video_rec_lbl_funkey4, 0, LV_STATE_DEFAULT);
    lv_obj_align(ui_scr->video_rec_lbl_funkey4_label, LV_ALIGN_CENTER, 0, 0);

    //Write codes video_rec_roller_mutifunc
    ui_scr->video_rec_roller_mutifunc = lv_roller_create(ui_scr->video_rec_view_subpage);
    lv_obj_set_pos(ui_scr->video_rec_roller_mutifunc, 149, 55);
    lv_obj_set_size(ui_scr->video_rec_roller_mutifunc, 247, 110);
    lv_obj_set_scrollbar_mode(ui_scr->video_rec_roller_mutifunc, LV_SCROLLBAR_MODE_OFF);
    ui_style_set(ui_scr->video_rec_roller_mutifunc, GUI_CTRL_ROLLER);
    lv_roller_set_options(ui_scr->video_rec_roller_mutifunc, "VGA\n1M\n2M\n3M\n5M\n8M\n10M\n12M\n64M", LV_ROLLER_MODE_INFINITE);
    lv_roller_set_visible_row_count(ui_scr->video_rec_roller_mutifunc, 3);

    //Write codes video_rec_headlight
    ui_scr->video_rec_headlight = lv_img_create(ui_scr->video_rec);
    lv_img_set_src(ui_scr->video_rec_headlight, gui_get_res_path(GUI_RES_HEADLIGHT_PNG));
    lv_img_set_pivot(ui_scr->video_rec_headlight, 0, 0);
    lv_img_set_angle(ui_scr->video_rec_headlight, 0);
    lv_img_set_zoom(ui_scr->video_rec_headlight, 256);
    lv_obj_set_pos(ui_scr->video_rec_headlight, 300, 140);
    lv_obj_set_size(ui_scr->video_rec_headlight, 200, 200);
    lv_obj_add_flag(ui_scr->video_rec_headlight, LV_OBJ_FLAG_HIDDEN);
    lv_obj_add_flag(ui_scr->video_rec_headlight, LV_OBJ_FLAG_CLICKABLE);
    ui_style_set(ui_scr->video_rec_headlight, GUI_CTRL_IMG);

    //Delete extra default style for video_rec_headlight
    lv_obj_remove_style(ui_scr->video_rec_headlight, &gui_img_main_focus_key_style, LV_PART_MAIN | LV_STATE_FOCUS_KEY);

    // Write Timer video_rec_timer_1
    if (ui_scr->video_rec_timer_1 != NULL) {
        lv_timer_del(ui_scr->video_rec_timer_1);
    }
    ui_scr->video_rec_timer_1 = lv_timer_create(video_rec_timer_1_timer_cb, 1000, "");
    lv_timer_set_repeat_count(ui_scr->video_rec_timer_1, -1);
    lv_timer_pause(ui_scr->video_rec_timer_1);

    lv_obj_update_layout(ui_scr->video_rec);
    ui_scr->video_rec_del = false;
    i18n_refresh_texts("video_rec");

    //Init events for screen
    events_init_video_rec(ui);
    return ui_scr->video_rec;
}
void unload_scr_video_rec(lv_ui *ui)
{
    lv_ui_video_rec *ui_scr = ui_get_scr_ptr(ui, GUI_SCREEN_VIDEO_REC);
    if (ui_scr->video_rec_timer_1 != NULL) {
        lv_timer_del(ui_scr->video_rec_timer_1);
        ui_scr->video_rec_timer_1 = NULL;
    }
    ui_free_scr_ptr(ui, GUI_SCREEN_VIDEO_REC);
}

#endif
