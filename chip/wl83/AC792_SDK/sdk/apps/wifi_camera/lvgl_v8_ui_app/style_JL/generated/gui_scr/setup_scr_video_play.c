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


lv_obj_t *setup_scr_video_play(lv_ui *ui)
{
    lv_ui_video_play *ui_scr = ui_get_scr_ptr(ui, GUI_SCREEN_VIDEO_PLAY);
    if (ui_scr == NULL) {
        ui_scr = lv_mem_alloc(sizeof(lv_ui_video_play));
        memset(ui_scr, 0, sizeof(lv_ui_video_play));
        ui->video_play = ui_scr;
    }

    //Write codes video_play
    ui_scr->video_play = lv_obj_create(NULL);
    lv_group_t *def_group = lv_group_get_default();
    lv_obj_set_scrollbar_mode(ui_scr->video_play, LV_SCROLLBAR_MODE_OFF);
    ui_style_set(ui_scr->video_play, GUI_CTRL_SCR);

    //Set style for video_play. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
    lv_obj_set_style_border_opa(ui_scr->video_play, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

    //Write codes video_play_view_1
    ui_scr->video_play_view_1 = lv_obj_create(ui_scr->video_play);
    lv_obj_set_pos(ui_scr->video_play_view_1, 0, 367);
    lv_obj_set_size(ui_scr->video_play_view_1, 799, 111);
    lv_obj_set_scrollbar_mode(ui_scr->video_play_view_1, LV_SCROLLBAR_MODE_OFF);
    lv_obj_add_flag(ui_scr->video_play_view_1, LV_OBJ_FLAG_EVENT_BUBBLE);
    lv_obj_clear_flag(ui_scr->video_play_view_1, LV_OBJ_FLAG_SCROLLABLE);
    ui_style_set(ui_scr->video_play_view_1, GUI_CTRL_CONT);

    //Set style for video_play_view_1. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
    lv_obj_set_style_bg_opa(ui_scr->video_play_view_1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_side(ui_scr->video_play_view_1, LV_BORDER_SIDE_NONE, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_outline_opa(ui_scr->video_play_view_1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

    //Write codes video_play_lbl_cur_time
    ui_scr->video_play_lbl_cur_time = lv_label_create(ui_scr->video_play_view_1);
    lv_label_set_text(ui_scr->video_play_lbl_cur_time, "00:00");
    lv_label_set_long_mode(ui_scr->video_play_lbl_cur_time, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui_scr->video_play_lbl_cur_time, 219, 52);
    lv_obj_set_size(ui_scr->video_play_lbl_cur_time, 106, 47);
    lv_obj_set_scrollbar_mode(ui_scr->video_play_lbl_cur_time, LV_SCROLLBAR_MODE_OFF);
    ui_style_set(ui_scr->video_play_lbl_cur_time, GUI_CTRL_LABEL);

    //Set style for video_play_lbl_cur_time. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
    lv_obj_set_style_bg_color(ui_scr->video_play_lbl_cur_time, lv_color_make(0x00, 0x00, 0x00), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_scr->video_play_lbl_cur_time, &lv_font_montserratMedium_24, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui_scr->video_play_lbl_cur_time, 3, LV_PART_MAIN | LV_STATE_DEFAULT);

    //Write codes video_play_imgbtn_pause
    ui_scr->video_play_imgbtn_pause = lv_imgbtn_create(ui_scr->video_play_view_1);
    lv_obj_set_pos(ui_scr->video_play_imgbtn_pause, 85, 48);
    lv_obj_set_size(ui_scr->video_play_imgbtn_pause, 48, 48);
    lv_obj_set_scrollbar_mode(ui_scr->video_play_imgbtn_pause, LV_SCROLLBAR_MODE_OFF);
    lv_obj_add_flag(ui_scr->video_play_imgbtn_pause, LV_OBJ_FLAG_EVENT_BUBBLE);
    lv_group_add_obj(def_group, ui_scr->video_play_imgbtn_pause);
    ui_style_set(ui_scr->video_play_imgbtn_pause, GUI_CTRL_IMGBTN);
    lv_imgbtn_set_src(ui_scr->video_play_imgbtn_pause, LV_IMGBTN_STATE_RELEASED, NULL, gui_get_res_path(GUI_RES_VIDEO_PLAY_PNG), NULL);
    lv_imgbtn_set_src(ui_scr->video_play_imgbtn_pause, LV_IMGBTN_STATE_CHECKED_RELEASED, NULL, gui_get_res_path(GUI_RES_VIDEO_PAUSE_PNG), NULL);
    lv_obj_add_flag(ui_scr->video_play_imgbtn_pause, LV_OBJ_FLAG_CHECKABLE);
    ui_scr->video_play_imgbtn_pause_label = lv_label_create(ui_scr->video_play_imgbtn_pause);
    lv_label_set_text(ui_scr->video_play_imgbtn_pause_label, "");
    lv_obj_set_style_pad_all(ui_scr->video_play_imgbtn_pause, 0, LV_STATE_DEFAULT);
    lv_obj_align(ui_scr->video_play_imgbtn_pause_label, LV_ALIGN_CENTER, 0, 0);

    //Write codes video_play_imgbtn_loud
    ui_scr->video_play_imgbtn_loud = lv_imgbtn_create(ui_scr->video_play_view_1);
    lv_obj_set_pos(ui_scr->video_play_imgbtn_loud, 600, 48);
    lv_obj_set_size(ui_scr->video_play_imgbtn_loud, 48, 48);
    lv_obj_set_scrollbar_mode(ui_scr->video_play_imgbtn_loud, LV_SCROLLBAR_MODE_OFF);
    lv_obj_add_flag(ui_scr->video_play_imgbtn_loud, LV_OBJ_FLAG_EVENT_BUBBLE);
    lv_group_add_obj(def_group, ui_scr->video_play_imgbtn_loud);
    ui_style_set(ui_scr->video_play_imgbtn_loud, GUI_CTRL_IMGBTN);
    lv_imgbtn_set_src(ui_scr->video_play_imgbtn_loud, LV_IMGBTN_STATE_RELEASED, NULL, gui_get_res_path(GUI_RES_VOLUMELOUDER_SOLID_1_PNG), NULL);
    lv_imgbtn_set_src(ui_scr->video_play_imgbtn_loud, LV_IMGBTN_STATE_CHECKED_RELEASED, NULL, gui_get_res_path(GUI_RES_VOLUMEMUTE_SOLID_1_PNG), NULL);
    lv_obj_add_flag(ui_scr->video_play_imgbtn_loud, LV_OBJ_FLAG_CHECKABLE);
    ui_scr->video_play_imgbtn_loud_label = lv_label_create(ui_scr->video_play_imgbtn_loud);
    lv_label_set_text(ui_scr->video_play_imgbtn_loud_label, "");
    lv_obj_set_style_pad_all(ui_scr->video_play_imgbtn_loud, 0, LV_STATE_DEFAULT);
    lv_obj_align(ui_scr->video_play_imgbtn_loud_label, LV_ALIGN_CENTER, 0, 0);

    //Write codes video_play_lbl_total_time
    ui_scr->video_play_lbl_total_time = lv_label_create(ui_scr->video_play_view_1);
    lv_label_set_text(ui_scr->video_play_lbl_total_time, "/02:40");
    lv_label_set_long_mode(ui_scr->video_play_lbl_total_time, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui_scr->video_play_lbl_total_time, 316, 52);
    lv_obj_set_size(ui_scr->video_play_lbl_total_time, 106, 47);
    lv_obj_set_scrollbar_mode(ui_scr->video_play_lbl_total_time, LV_SCROLLBAR_MODE_OFF);
    ui_style_set(ui_scr->video_play_lbl_total_time, GUI_CTRL_LABEL);

    //Set style for video_play_lbl_total_time. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
    lv_obj_set_style_bg_color(ui_scr->video_play_lbl_total_time, lv_color_make(0x00, 0x00, 0x00), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_scr->video_play_lbl_total_time, &lv_font_montserratMedium_24, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui_scr->video_play_lbl_total_time, 3, LV_PART_MAIN | LV_STATE_DEFAULT);

    //Write codes video_play_ddlist_multi_spped
    ui_scr->video_play_ddlist_multi_spped = lv_dropdown_create(ui_scr->video_play_view_1);
    lv_dropdown_set_options(ui_scr->video_play_ddlist_multi_spped, "list1\nlist2\nlist3");
    lv_dropdown_set_dir(ui_scr->video_play_ddlist_multi_spped, LV_DIR_TOP);
    lv_dropdown_set_symbol(ui_scr->video_play_ddlist_multi_spped, LV_SYMBOL_UP);
    lv_dropdown_set_symbol(ui_scr->video_play_ddlist_multi_spped, NULL);
    lv_dropdown_set_selected(ui_scr->video_play_ddlist_multi_spped, 1);
    lv_obj_set_pos(ui_scr->video_play_ddlist_multi_spped, 674, 48);
    lv_obj_set_size(ui_scr->video_play_ddlist_multi_spped, 101, 48);
    lv_obj_set_scrollbar_mode(ui_scr->video_play_ddlist_multi_spped, LV_SCROLLBAR_MODE_OFF);
    lv_obj_add_flag(ui_scr->video_play_ddlist_multi_spped, LV_OBJ_FLAG_EVENT_BUBBLE);
    ui_style_set(ui_scr->video_play_ddlist_multi_spped, GUI_CTRL_DROPDOWN);

    //Set style for video_play_ddlist_multi_spped. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
    lv_obj_set_style_radius(ui_scr->video_play_ddlist_multi_spped, 16, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui_scr->video_play_ddlist_multi_spped, lv_color_make(0x21, 0x95, 0xf6), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_color(ui_scr->video_play_ddlist_multi_spped, lv_color_make(0x00, 0x00, 0x00), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_scr->video_play_ddlist_multi_spped, 153, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_side(ui_scr->video_play_ddlist_multi_spped, LV_BORDER_SIDE_NONE, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui_scr->video_play_ddlist_multi_spped, lv_color_make(0xFF, 0xFF, 0xFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_scr->video_play_ddlist_multi_spped, &lv_font_montserratMedium_24, LV_PART_MAIN | LV_STATE_DEFAULT);

    //Set style for video_play_ddlist_multi_spped. Part: LV_PART_MAIN, State: LV_STATE_FOCUS_KEY
    lv_obj_set_style_radius(ui_scr->video_play_ddlist_multi_spped, 15, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_bg_color(ui_scr->video_play_ddlist_multi_spped, lv_color_make(0x21, 0x95, 0xf6), LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_bg_opa(ui_scr->video_play_ddlist_multi_spped, 153, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_border_side(ui_scr->video_play_ddlist_multi_spped, LV_BORDER_SIDE_NONE, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_outline_width(ui_scr->video_play_ddlist_multi_spped, 3, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_text_color(ui_scr->video_play_ddlist_multi_spped, lv_color_make(0xFF, 0xFF, 0xFF), LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_text_font(ui_scr->video_play_ddlist_multi_spped, &lv_font_montserratMedium_24, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_pad_top(ui_scr->video_play_ddlist_multi_spped, 12, LV_PART_MAIN | LV_STATE_FOCUS_KEY);

    //Set style state: LV_STATE_CHECKED for style_video_play_ddlist_multi_spped_extra_list_selected_checked
    static lv_style_t style_video_play_ddlist_multi_spped_extra_list_selected_checked;
    ui_init_style(&style_video_play_ddlist_multi_spped_extra_list_selected_checked);
    lv_style_set_bg_color(&style_video_play_ddlist_multi_spped_extra_list_selected_checked, lv_color_make(0x21, 0x95, 0xf6));
    lv_style_set_bg_opa(&style_video_play_ddlist_multi_spped_extra_list_selected_checked, 153);
    lv_style_set_border_color(&style_video_play_ddlist_multi_spped_extra_list_selected_checked, lv_color_make(0x00, 0x00, 0x00));
    lv_style_set_border_width(&style_video_play_ddlist_multi_spped_extra_list_selected_checked, 0);
    lv_style_set_border_side(&style_video_play_ddlist_multi_spped_extra_list_selected_checked, LV_BORDER_SIDE_NONE);
    lv_style_set_text_font(&style_video_play_ddlist_multi_spped_extra_list_selected_checked, &lv_font_montserratMedium_24);
    lv_obj_add_style(lv_dropdown_get_list(ui_scr->video_play_ddlist_multi_spped), &gui_ddlist_selected_checked_style, LV_PART_SELECTED | LV_STATE_CHECKED);
    lv_obj_add_style(lv_dropdown_get_list(ui_scr->video_play_ddlist_multi_spped), &style_video_play_ddlist_multi_spped_extra_list_selected_checked, LV_PART_SELECTED | LV_STATE_CHECKED);

    //Set style state: LV_STATE_DEFAULT for style_video_play_ddlist_multi_spped_extra_list_main_default
    static lv_style_t style_video_play_ddlist_multi_spped_extra_list_main_default;
    ui_init_style(&style_video_play_ddlist_multi_spped_extra_list_main_default);
    lv_style_set_bg_color(&style_video_play_ddlist_multi_spped_extra_list_main_default, lv_color_make(0x21, 0x95, 0xf6));
    lv_style_set_bg_opa(&style_video_play_ddlist_multi_spped_extra_list_main_default, 153);
    lv_style_set_border_side(&style_video_play_ddlist_multi_spped_extra_list_main_default, LV_BORDER_SIDE_NONE);
    lv_style_set_text_color(&style_video_play_ddlist_multi_spped_extra_list_main_default, lv_color_make(0xFF, 0xFF, 0xFF));
    lv_style_set_text_font(&style_video_play_ddlist_multi_spped_extra_list_main_default, &lv_font_montserratMedium_24);
    lv_style_set_max_height(&style_video_play_ddlist_multi_spped_extra_list_main_default, 190);
    lv_obj_add_style(lv_dropdown_get_list(ui_scr->video_play_ddlist_multi_spped), &gui_ddlist_dropdown_list_default_style, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_add_style(lv_dropdown_get_list(ui_scr->video_play_ddlist_multi_spped), &style_video_play_ddlist_multi_spped_extra_list_main_default, LV_PART_MAIN | LV_STATE_DEFAULT);

    //Set style state: LV_STATE_DEFAULT for style_video_play_ddlist_multi_spped_extra_list_scrollbar_default
    static lv_style_t style_video_play_ddlist_multi_spped_extra_list_scrollbar_default;
    ui_init_style(&style_video_play_ddlist_multi_spped_extra_list_scrollbar_default);
    lv_style_set_bg_opa(&style_video_play_ddlist_multi_spped_extra_list_scrollbar_default, 0);
    lv_obj_add_style(lv_dropdown_get_list(ui_scr->video_play_ddlist_multi_spped), &gui_ddlist_scrollbar_default_style, LV_PART_SCROLLBAR | LV_STATE_DEFAULT);
    lv_obj_add_style(lv_dropdown_get_list(ui_scr->video_play_ddlist_multi_spped), &style_video_play_ddlist_multi_spped_extra_list_scrollbar_default, LV_PART_SCROLLBAR | LV_STATE_DEFAULT);

    //Delete extra default style for video_play_ddlist_multi_spped
    lv_obj_remove_style(ui_scr->video_play_ddlist_multi_spped, &gui_ddlist_selected_checked_style, LV_PART_SELECTED | LV_STATE_CHECKED);
    lv_obj_remove_style(ui_scr->video_play_ddlist_multi_spped, &gui_ddlist_dropdown_list_default_style, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_remove_style(ui_scr->video_play_ddlist_multi_spped, &gui_ddlist_scrollbar_default_style, LV_PART_SCROLLBAR | LV_STATE_DEFAULT);

    //Write codes video_play_bar_process
    ui_scr->video_play_bar_process = lv_bar_create(ui_scr->video_play_view_1);
    lv_obj_set_pos(ui_scr->video_play_bar_process, 0, 13);
    lv_obj_set_size(ui_scr->video_play_bar_process, 800, 16);
    lv_obj_set_scrollbar_mode(ui_scr->video_play_bar_process, LV_SCROLLBAR_MODE_OFF);
    ui_style_set(ui_scr->video_play_bar_process, GUI_CTRL_BAR);
    lv_obj_set_style_anim_time(ui_scr->video_play_bar_process, 1000, 0);
    lv_bar_set_mode(ui_scr->video_play_bar_process, LV_BAR_MODE_NORMAL);
    lv_bar_set_range(ui_scr->video_play_bar_process, 0, 100);
    lv_bar_set_value(ui_scr->video_play_bar_process, 20.0004, LV_ANIM_ON);

    //Write codes video_play_imgbtn_1
    ui_scr->video_play_imgbtn_1 = lv_imgbtn_create(ui_scr->video_play);
    lv_obj_set_pos(ui_scr->video_play_imgbtn_1, 724, 135);
    lv_obj_set_size(ui_scr->video_play_imgbtn_1, 48, 48);
    lv_obj_set_scrollbar_mode(ui_scr->video_play_imgbtn_1, LV_SCROLLBAR_MODE_OFF);
    lv_group_add_obj(def_group, ui_scr->video_play_imgbtn_1);
    ui_style_set(ui_scr->video_play_imgbtn_1, GUI_CTRL_IMGBTN);
    lv_imgbtn_set_src(ui_scr->video_play_imgbtn_1, LV_IMGBTN_STATE_RELEASED, NULL, gui_get_res_path(GUI_RES_PHOTO_PNG), NULL);
    lv_imgbtn_set_src(ui_scr->video_play_imgbtn_1, LV_IMGBTN_STATE_PRESSED, NULL, gui_get_res_path(GUI_RES_PHOTO_ON_PNG), NULL);
    lv_imgbtn_set_src(ui_scr->video_play_imgbtn_1, LV_IMGBTN_STATE_CHECKED_RELEASED, NULL, gui_get_res_path(GUI_RES_PHOTO_PNG), NULL);
    lv_imgbtn_set_src(ui_scr->video_play_imgbtn_1, LV_IMGBTN_STATE_CHECKED_PRESSED, NULL, gui_get_res_path(GUI_RES_PHOTO_ON_PNG), NULL);
    lv_obj_add_flag(ui_scr->video_play_imgbtn_1, LV_OBJ_FLAG_CHECKABLE);
    ui_scr->video_play_imgbtn_1_label = lv_label_create(ui_scr->video_play_imgbtn_1);
    lv_label_set_text(ui_scr->video_play_imgbtn_1_label, "");
    lv_obj_set_style_pad_all(ui_scr->video_play_imgbtn_1, 0, LV_STATE_DEFAULT);
    lv_obj_align(ui_scr->video_play_imgbtn_1_label, LV_ALIGN_CENTER, 0, 0);

    //Write codes video_play_imgbtn_2
    ui_scr->video_play_imgbtn_2 = lv_imgbtn_create(ui_scr->video_play);
    lv_obj_set_pos(ui_scr->video_play_imgbtn_2, 726, 260);
    lv_obj_set_size(ui_scr->video_play_imgbtn_2, 48, 48);
    lv_obj_set_scrollbar_mode(ui_scr->video_play_imgbtn_2, LV_SCROLLBAR_MODE_OFF);
    lv_group_add_obj(def_group, ui_scr->video_play_imgbtn_2);
    ui_style_set(ui_scr->video_play_imgbtn_2, GUI_CTRL_IMGBTN);
    lv_imgbtn_set_src(ui_scr->video_play_imgbtn_2, LV_IMGBTN_STATE_RELEASED, NULL, gui_get_res_path(GUI_RES_RETURN_PNG), NULL);
    lv_imgbtn_set_src(ui_scr->video_play_imgbtn_2, LV_IMGBTN_STATE_PRESSED, NULL, gui_get_res_path(GUI_RES_RETURN_ON_PNG), NULL);
    lv_imgbtn_set_src(ui_scr->video_play_imgbtn_2, LV_IMGBTN_STATE_CHECKED_RELEASED, NULL, gui_get_res_path(GUI_RES_RETURN_PNG), NULL);
    lv_imgbtn_set_src(ui_scr->video_play_imgbtn_2, LV_IMGBTN_STATE_CHECKED_PRESSED, NULL, gui_get_res_path(GUI_RES_RETURN_ON_PNG), NULL);
    lv_obj_add_flag(ui_scr->video_play_imgbtn_2, LV_OBJ_FLAG_CHECKABLE);
    ui_scr->video_play_imgbtn_2_label = lv_label_create(ui_scr->video_play_imgbtn_2);
    lv_label_set_text(ui_scr->video_play_imgbtn_2_label, "");
    lv_obj_set_style_pad_all(ui_scr->video_play_imgbtn_2, 0, LV_STATE_DEFAULT);
    lv_obj_align(ui_scr->video_play_imgbtn_2_label, LV_ALIGN_CENTER, 0, 0);

    //Write codes video_play_lbl_msg
    ui_scr->video_play_lbl_msg = lv_label_create(ui_scr->video_play);
    lv_label_set_text(ui_scr->video_play_lbl_msg, "正在播放 xxx.avi");
    lv_label_set_long_mode(ui_scr->video_play_lbl_msg, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui_scr->video_play_lbl_msg, 159, 278);
    lv_obj_set_size(ui_scr->video_play_lbl_msg, 527, 59);
    lv_obj_set_scrollbar_mode(ui_scr->video_play_lbl_msg, LV_SCROLLBAR_MODE_OFF);
    lv_obj_add_flag(ui_scr->video_play_lbl_msg, LV_OBJ_FLAG_HIDDEN);
    ui_style_set(ui_scr->video_play_lbl_msg, GUI_CTRL_LABEL);

    //Set style for video_play_lbl_msg. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
    lv_obj_set_style_text_font(ui_scr->video_play_lbl_msg, &lv_font_FangZhengKaiTiJianTi_1_26, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui_scr->video_play_lbl_msg, 10, LV_PART_MAIN | LV_STATE_DEFAULT);

    // Write Timer video_play_hide_bar
    if (ui_scr->video_play_hide_bar != NULL) {
        lv_timer_del(ui_scr->video_play_hide_bar);
    }
    ui_scr->video_play_hide_bar = lv_timer_create(video_play_hide_bar_timer_cb, 3000, "");
    lv_timer_set_repeat_count(ui_scr->video_play_hide_bar, -1);

    //Write codes video_play_img_prev_file
    ui_scr->video_play_img_prev_file = lv_img_create(ui_scr->video_play);
    lv_img_set_src(ui_scr->video_play_img_prev_file, gui_get_res_path(GUI_RES_SKIP_PREVIOUS_PNG));
    lv_img_set_pivot(ui_scr->video_play_img_prev_file, 0, 0);
    lv_img_set_angle(ui_scr->video_play_img_prev_file, 0);
    lv_img_set_zoom(ui_scr->video_play_img_prev_file, 256);
    lv_obj_set_pos(ui_scr->video_play_img_prev_file, 25, 416);
    lv_obj_set_size(ui_scr->video_play_img_prev_file, 57, 54);
    lv_group_add_obj(def_group, ui_scr->video_play_img_prev_file);
    lv_obj_add_flag(ui_scr->video_play_img_prev_file, LV_OBJ_FLAG_CLICKABLE);
    ui_style_set(ui_scr->video_play_img_prev_file, GUI_CTRL_IMG);

    //Write codes video_play_img_next_file
    ui_scr->video_play_img_next_file = lv_img_create(ui_scr->video_play);
    lv_img_set_src(ui_scr->video_play_img_next_file, gui_get_res_path(GUI_RES_SKIP_NEXT_PNG));
    lv_img_set_pivot(ui_scr->video_play_img_next_file, 0, 0);
    lv_img_set_angle(ui_scr->video_play_img_next_file, 0);
    lv_img_set_zoom(ui_scr->video_play_img_next_file, 256);
    lv_obj_set_pos(ui_scr->video_play_img_next_file, 150, 416);
    lv_obj_set_size(ui_scr->video_play_img_next_file, 57, 54);
    lv_group_add_obj(def_group, ui_scr->video_play_img_next_file);
    lv_obj_add_flag(ui_scr->video_play_img_next_file, LV_OBJ_FLAG_CLICKABLE);
    ui_style_set(ui_scr->video_play_img_next_file, GUI_CTRL_IMG);

    // Write Timer video_play_hide_label
    if (ui_scr->video_play_hide_label != NULL) {
        lv_timer_del(ui_scr->video_play_hide_label);
    }
    ui_scr->video_play_hide_label = lv_timer_create(video_play_hide_label_timer_cb, 100, "");
    lv_timer_set_repeat_count(ui_scr->video_play_hide_label, -1);

    lv_obj_update_layout(ui_scr->video_play);
    ui_scr->video_play_del = false;
    i18n_refresh_texts("video_play");

    //Init events for screen
    events_init_video_play(ui);
    return ui_scr->video_play;
}
void unload_scr_video_play(lv_ui *ui)
{
    lv_ui_video_play *ui_scr = ui_get_scr_ptr(ui, GUI_SCREEN_VIDEO_PLAY);
    if (ui_scr->video_play_hide_bar != NULL) {
        lv_timer_del(ui_scr->video_play_hide_bar);
        ui_scr->video_play_hide_bar = NULL;
    }
    if (ui_scr->video_play_hide_label != NULL) {
        lv_timer_del(ui_scr->video_play_hide_label);
        ui_scr->video_play_hide_label = NULL;
    }
    ui_free_scr_ptr(ui, GUI_SCREEN_VIDEO_PLAY);
}

#endif
