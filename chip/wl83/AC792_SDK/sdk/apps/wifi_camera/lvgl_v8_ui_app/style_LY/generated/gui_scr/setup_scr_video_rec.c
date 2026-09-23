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


lv_obj_t *setup_scr_video_rec(lv_ui *ui)
{
    lv_ui_video_rec *ui_scr = ui_get_scr_ptr(ui, GUI_SCREEN_VIDEO_REC);
    if (ui_scr == NULL) {
        ui_scr = lv_mem_alloc(sizeof(lv_ui_video_rec));
        if (ui_scr == NULL) {
            return NULL;
        }
        memset(ui_scr, 0, sizeof(lv_ui_video_rec));
        ui->video_rec = ui_scr;
    }

    //Write codes video_rec
    ui_scr->video_rec = lv_obj_create(NULL);
    lv_group_t *def_group = lv_group_get_default();
    lv_obj_set_scrollbar_mode(ui_scr->video_rec, LV_SCROLLBAR_MODE_OFF);
    ui_style_set(ui_scr->video_rec, GUI_CTRL_SCR);

    //Set style for video_rec. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
    lv_obj_set_style_bg_color(ui_scr->video_rec, lv_color_make(0x55, 0xaa, 0xa5), LV_PART_MAIN | LV_STATE_DEFAULT);

    //Write codes video_rec_view_scan
    ui_scr->video_rec_view_scan = lv_obj_create(ui_scr->video_rec);
    lv_obj_set_pos(ui_scr->video_rec_view_scan, 0, 0);
    lv_obj_set_size(ui_scr->video_rec_view_scan, 800, 480);
    lv_obj_set_scrollbar_mode(ui_scr->video_rec_view_scan, LV_SCROLLBAR_MODE_OFF);
    lv_group_add_obj(def_group, ui_scr->video_rec_view_scan);
    ui_style_set(ui_scr->video_rec_view_scan, GUI_CTRL_CONT);

    //Set style for video_rec_view_scan. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
    lv_obj_set_style_shadow_color(ui_scr->video_rec_view_scan, lv_color_make(0x21, 0x95, 0xF6), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_opa(ui_scr->video_rec_view_scan, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui_scr->video_rec_view_scan, lv_color_make(0x21, 0x95, 0xF6), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui_scr->video_rec_view_scan, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_outline_color(ui_scr->video_rec_view_scan, lv_color_make(0x21, 0x95, 0xF6), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_outline_opa(ui_scr->video_rec_view_scan, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

    //Delete extra default style for video_rec_view_scan
    lv_obj_remove_style(ui_scr->video_rec_view_scan, &gui_cont_main_focus_key_style, LV_PART_MAIN | LV_STATE_FOCUS_KEY);

    //Write codes video_rec_img_1
    ui_scr->video_rec_img_1 = lv_img_create(ui_scr->video_rec_view_scan);
    lv_img_set_src(ui_scr->video_rec_img_1, gui_get_res_path(GUI_RES_I_REC_PNG));
    lv_img_set_pivot(ui_scr->video_rec_img_1, 0, 0);
    lv_img_set_angle(ui_scr->video_rec_img_1, 0);
    lv_img_set_zoom(ui_scr->video_rec_img_1, 256);
    lv_obj_set_pos(ui_scr->video_rec_img_1, 12, 10);
    lv_obj_set_size(ui_scr->video_rec_img_1, 29, 29);
    lv_obj_add_flag(ui_scr->video_rec_img_1, LV_OBJ_FLAG_CLICKABLE);
    ui_style_set(ui_scr->video_rec_img_1, GUI_CTRL_IMG);

    //Write codes video_rec_img_cyc_state
    ui_scr->video_rec_img_cyc_state = lv_img_create(ui_scr->video_rec_view_scan);
    lv_img_set_src(ui_scr->video_rec_img_cyc_state, gui_get_res_path(GUI_RES_CYCLIC_VIDEO_3_PNG));
    lv_img_set_pivot(ui_scr->video_rec_img_cyc_state, 0, 0);
    lv_img_set_angle(ui_scr->video_rec_img_cyc_state, 0);
    lv_img_set_zoom(ui_scr->video_rec_img_cyc_state, 256);
    lv_obj_set_pos(ui_scr->video_rec_img_cyc_state, 13, 54);
    lv_obj_set_size(ui_scr->video_rec_img_cyc_state, 29, 31);
    lv_obj_add_flag(ui_scr->video_rec_img_cyc_state, LV_OBJ_FLAG_CLICKABLE);
    ui_style_set(ui_scr->video_rec_img_cyc_state, GUI_CTRL_IMG);

    //Write codes video_rec_img_exp_state
    ui_scr->video_rec_img_exp_state = lv_img_create(ui_scr->video_rec_view_scan);
    lv_img_set_src(ui_scr->video_rec_img_exp_state, gui_get_res_path(GUI_RES_EXP_A0_PNG));
    lv_img_set_pivot(ui_scr->video_rec_img_exp_state, 0, 0);
    lv_img_set_angle(ui_scr->video_rec_img_exp_state, 0);
    lv_img_set_zoom(ui_scr->video_rec_img_exp_state, 256);
    lv_obj_set_pos(ui_scr->video_rec_img_exp_state, 12, 95);
    lv_obj_set_size(ui_scr->video_rec_img_exp_state, 29, 29);
    lv_obj_add_flag(ui_scr->video_rec_img_exp_state, LV_OBJ_FLAG_CLICKABLE);
    ui_style_set(ui_scr->video_rec_img_exp_state, GUI_CTRL_IMG);

    //Write codes video_rec_img_mot_state
    ui_scr->video_rec_img_mot_state = lv_img_create(ui_scr->video_rec_view_scan);
    lv_img_set_src(ui_scr->video_rec_img_mot_state, gui_get_res_path(GUI_RES_I_MOT_PNG));
    lv_img_set_pivot(ui_scr->video_rec_img_mot_state, 0, 0);
    lv_img_set_angle(ui_scr->video_rec_img_mot_state, 0);
    lv_img_set_zoom(ui_scr->video_rec_img_mot_state, 256);
    lv_obj_set_pos(ui_scr->video_rec_img_mot_state, 14, 138);
    lv_obj_set_size(ui_scr->video_rec_img_mot_state, 22, 25);
    lv_obj_add_flag(ui_scr->video_rec_img_mot_state, LV_OBJ_FLAG_CLICKABLE);
    ui_style_set(ui_scr->video_rec_img_mot_state, GUI_CTRL_IMG);

    //Write codes video_rec_img_gap_state
    ui_scr->video_rec_img_gap_state = lv_img_create(ui_scr->video_rec_view_scan);
    lv_img_set_src(ui_scr->video_rec_img_gap_state, gui_get_res_path(GUI_RES_I_TEAR_PNG));
    lv_img_set_pivot(ui_scr->video_rec_img_gap_state, 0, 0);
    lv_img_set_angle(ui_scr->video_rec_img_gap_state, 0);
    lv_img_set_zoom(ui_scr->video_rec_img_gap_state, 256);
    lv_obj_set_pos(ui_scr->video_rec_img_gap_state, 13, 180);
    lv_obj_set_size(ui_scr->video_rec_img_gap_state, 29, 31);
    lv_obj_add_flag(ui_scr->video_rec_img_gap_state, LV_OBJ_FLAG_CLICKABLE);
    ui_style_set(ui_scr->video_rec_img_gap_state, GUI_CTRL_IMG);

    //Write codes video_rec_img_mic_state
    ui_scr->video_rec_img_mic_state = lv_img_create(ui_scr->video_rec_view_scan);
    lv_img_set_src(ui_scr->video_rec_img_mic_state, gui_get_res_path(GUI_RES_MIC_ON_PNG));
    lv_img_set_pivot(ui_scr->video_rec_img_mic_state, 0, 0);
    lv_img_set_angle(ui_scr->video_rec_img_mic_state, 0);
    lv_img_set_zoom(ui_scr->video_rec_img_mic_state, 256);
    lv_obj_set_pos(ui_scr->video_rec_img_mic_state, 12, 440);
    lv_obj_set_size(ui_scr->video_rec_img_mic_state, 26, 29);
    lv_obj_add_flag(ui_scr->video_rec_img_mic_state, LV_OBJ_FLAG_CLICKABLE);
    ui_style_set(ui_scr->video_rec_img_mic_state, GUI_CTRL_IMG);

    //Write codes video_rec_img_hdr_state
    ui_scr->video_rec_img_hdr_state = lv_img_create(ui_scr->video_rec_view_scan);
    lv_img_set_src(ui_scr->video_rec_img_hdr_state, gui_get_res_path(GUI_RES_I_HDR_PNG));
    lv_img_set_pivot(ui_scr->video_rec_img_hdr_state, 0, 0);
    lv_img_set_angle(ui_scr->video_rec_img_hdr_state, 0);
    lv_img_set_zoom(ui_scr->video_rec_img_hdr_state, 256);
    lv_obj_set_pos(ui_scr->video_rec_img_hdr_state, 177, 10);
    lv_obj_set_size(ui_scr->video_rec_img_hdr_state, 29, 29);
    lv_obj_add_flag(ui_scr->video_rec_img_hdr_state, LV_OBJ_FLAG_CLICKABLE);
    ui_style_set(ui_scr->video_rec_img_hdr_state, GUI_CTRL_IMG);

    //Write codes video_rec_img_gra_state
    ui_scr->video_rec_img_gra_state = lv_img_create(ui_scr->video_rec_view_scan);
    lv_img_set_src(ui_scr->video_rec_img_gra_state, gui_get_res_path(GUI_RES_I_GRA_L_PNG));
    lv_img_set_pivot(ui_scr->video_rec_img_gra_state, 0, 0);
    lv_img_set_angle(ui_scr->video_rec_img_gra_state, 0);
    lv_img_set_zoom(ui_scr->video_rec_img_gra_state, 256);
    lv_obj_set_pos(ui_scr->video_rec_img_gra_state, 226, 12);
    lv_obj_set_size(ui_scr->video_rec_img_gra_state, 34, 31);
    lv_obj_add_flag(ui_scr->video_rec_img_gra_state, LV_OBJ_FLAG_CLICKABLE);
    ui_style_set(ui_scr->video_rec_img_gra_state, GUI_CTRL_IMG);

    //Write codes video_rec_img_par_state
    ui_scr->video_rec_img_par_state = lv_img_create(ui_scr->video_rec_view_scan);
    lv_img_set_src(ui_scr->video_rec_img_par_state, gui_get_res_path(GUI_RES_PARK_PNG));
    lv_img_set_pivot(ui_scr->video_rec_img_par_state, 0, 0);
    lv_img_set_angle(ui_scr->video_rec_img_par_state, 0);
    lv_img_set_zoom(ui_scr->video_rec_img_par_state, 256);
    lv_obj_set_pos(ui_scr->video_rec_img_par_state, 762, 223);
    lv_obj_set_size(ui_scr->video_rec_img_par_state, 27, 22);
    lv_obj_add_flag(ui_scr->video_rec_img_par_state, LV_OBJ_FLAG_CLICKABLE);
    ui_style_set(ui_scr->video_rec_img_par_state, GUI_CTRL_IMG);

    //Write codes video_rec_lbl_reso
    ui_scr->video_rec_lbl_reso = lv_label_create(ui_scr->video_rec_view_scan);
    lv_label_set_text(ui_scr->video_rec_lbl_reso, "720P");
    lv_label_set_long_mode(ui_scr->video_rec_lbl_reso, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui_scr->video_rec_lbl_reso, 478, 12);
    lv_obj_set_size(ui_scr->video_rec_lbl_reso, 80, 35);
    lv_obj_set_scrollbar_mode(ui_scr->video_rec_lbl_reso, LV_SCROLLBAR_MODE_OFF);
    ui_style_set(ui_scr->video_rec_lbl_reso, GUI_CTRL_LABEL);

    //Set style for video_rec_lbl_reso. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
    lv_obj_set_style_text_font(ui_scr->video_rec_lbl_reso, &lv_font_FangZhengKaiTiJianTi_1_26, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui_scr->video_rec_lbl_reso, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);

    //Write codes video_rec_digitclock_1
    ui_scr->video_rec_digitclock_1 = lv_label_create(ui_scr->video_rec_view_scan);
    lv_label_set_text_fmt(ui_scr->video_rec_digitclock_1, "%04d-%02d-%02d %02d:%02d:%02d", 2022, 07, 28, 21 % 12, 25, 50);
    lv_obj_set_style_text_align(ui_scr->video_rec_digitclock_1, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_pos(ui_scr->video_rec_digitclock_1, 50, 438);
    lv_obj_set_size(ui_scr->video_rec_digitclock_1, 300, 35);
    ui_style_set(ui_scr->video_rec_digitclock_1, GUI_CTRL_DIGITALCLOCK);

    //Delete extra default style for video_rec_digitclock_1
    lv_obj_remove_style(ui_scr->video_rec_digitclock_1, &gui_digitclock_main_disabled_style, LV_PART_MAIN | LV_STATE_DISABLED);

    //Write codes video_rec_img_bat
    ui_scr->video_rec_img_bat = lv_img_create(ui_scr->video_rec_view_scan);
    lv_img_set_src(ui_scr->video_rec_img_bat, gui_get_res_path(GUI_RES_BAT_FULL_PNG));
    lv_img_set_pivot(ui_scr->video_rec_img_bat, 0, 0);
    lv_img_set_angle(ui_scr->video_rec_img_bat, 0);
    lv_img_set_zoom(ui_scr->video_rec_img_bat, 256);
    lv_obj_set_pos(ui_scr->video_rec_img_bat, 762, 454);
    lv_obj_set_size(ui_scr->video_rec_img_bat, 25, 15);
    lv_obj_add_flag(ui_scr->video_rec_img_bat, LV_OBJ_FLAG_CLICKABLE);
    ui_style_set(ui_scr->video_rec_img_bat, GUI_CTRL_IMG);

    //Write codes video_rec_img_sd
    ui_scr->video_rec_img_sd = lv_img_create(ui_scr->video_rec_view_scan);
    lv_img_set_src(ui_scr->video_rec_img_sd, gui_get_res_path(GUI_RES_CARD_ONLINE_PNG));
    lv_img_set_pivot(ui_scr->video_rec_img_sd, 0, 0);
    lv_img_set_angle(ui_scr->video_rec_img_sd, 0);
    lv_img_set_zoom(ui_scr->video_rec_img_sd, 256);
    lv_obj_set_pos(ui_scr->video_rec_img_sd, 758, 410);
    lv_obj_set_size(ui_scr->video_rec_img_sd, 29, 29);
    lv_obj_add_flag(ui_scr->video_rec_img_sd, LV_OBJ_FLAG_CLICKABLE);
    ui_style_set(ui_scr->video_rec_img_sd, GUI_CTRL_IMG);

    //Write codes video_rec_digitclock_2
    ui_scr->video_rec_digitclock_2 = lv_label_create(ui_scr->video_rec_view_scan);
    lv_label_set_text_fmt(ui_scr->video_rec_digitclock_2, "%02d:%02d:%02d", 21 % 12, 25, 50);
    lv_obj_set_style_text_align(ui_scr->video_rec_digitclock_2, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_pos(ui_scr->video_rec_digitclock_2, 666, 10);
    lv_obj_set_size(ui_scr->video_rec_digitclock_2, 120, 32);
    ui_style_set(ui_scr->video_rec_digitclock_2, GUI_CTRL_DIGITALCLOCK);

    //Write codes video_rec_img_rec_state
    ui_scr->video_rec_img_rec_state = lv_img_create(ui_scr->video_rec_view_scan);
    lv_img_set_src(ui_scr->video_rec_img_rec_state, gui_get_res_path(GUI_RES_RED_CIRCLE_PNG));
    lv_img_set_pivot(ui_scr->video_rec_img_rec_state, 0, 0);
    lv_img_set_angle(ui_scr->video_rec_img_rec_state, 0);
    lv_img_set_zoom(ui_scr->video_rec_img_rec_state, 256);
    lv_obj_set_pos(ui_scr->video_rec_img_rec_state, 65, 12);
    lv_obj_set_size(ui_scr->video_rec_img_rec_state, 27, 27);
    lv_obj_add_flag(ui_scr->video_rec_img_rec_state, LV_OBJ_FLAG_HIDDEN);
    lv_obj_add_flag(ui_scr->video_rec_img_rec_state, LV_OBJ_FLAG_CLICKABLE);
    ui_style_set(ui_scr->video_rec_img_rec_state, GUI_CTRL_IMG);

    //Write codes video_rec_lbl_num
    ui_scr->video_rec_lbl_num = lv_label_create(ui_scr->video_rec_view_scan);
    lv_label_set_text(ui_scr->video_rec_lbl_num, "京 AAAAAA\n\n京津晋冀蒙辽吉黑苏浙皖闽赣鲁豫鄂湘粤桂琼川贵滇渝藏陕甘青宁新台港澳");
    lv_label_set_long_mode(ui_scr->video_rec_lbl_num, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui_scr->video_rec_lbl_num, 93, 391);
    lv_obj_set_size(ui_scr->video_rec_lbl_num, 180, 42);
    lv_obj_set_scrollbar_mode(ui_scr->video_rec_lbl_num, LV_SCROLLBAR_MODE_OFF);
    lv_obj_add_flag(ui_scr->video_rec_lbl_num, LV_OBJ_FLAG_HIDDEN);
    ui_style_set(ui_scr->video_rec_lbl_num, GUI_CTRL_LABEL);

    //Set style for video_rec_lbl_num. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
    lv_obj_set_style_text_font(ui_scr->video_rec_lbl_num, &lv_font_FangZhengKaiTiJianTi_1_26, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui_scr->video_rec_lbl_num, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui_scr->video_rec_lbl_num, 8, LV_PART_MAIN | LV_STATE_DEFAULT);

    //Write codes video_rec_img_headlight
    ui_scr->video_rec_img_headlight = lv_img_create(ui_scr->video_rec_view_scan);
    lv_img_set_src(ui_scr->video_rec_img_headlight, gui_get_res_path(GUI_RES_FLIG_ON_PNG));
    lv_img_set_pivot(ui_scr->video_rec_img_headlight, 0, 0);
    lv_img_set_angle(ui_scr->video_rec_img_headlight, 0);
    lv_img_set_zoom(ui_scr->video_rec_img_headlight, 256);
    lv_obj_set_pos(ui_scr->video_rec_img_headlight, 363, 203);
    lv_obj_set_size(ui_scr->video_rec_img_headlight, 75, 75);
    lv_obj_add_flag(ui_scr->video_rec_img_headlight, LV_OBJ_FLAG_HIDDEN);
    lv_obj_add_flag(ui_scr->video_rec_img_headlight, LV_OBJ_FLAG_CLICKABLE);
    ui_style_set(ui_scr->video_rec_img_headlight, GUI_CTRL_IMG);

    //Write codes video_rec_img_key_state
    ui_scr->video_rec_img_key_state = lv_img_create(ui_scr->video_rec_view_scan);
    lv_img_set_src(ui_scr->video_rec_img_key_state, gui_get_res_path(GUI_RES_KEY_PNG));
    lv_img_set_pivot(ui_scr->video_rec_img_key_state, 0, 0);
    lv_img_set_angle(ui_scr->video_rec_img_key_state, 0);
    lv_img_set_zoom(ui_scr->video_rec_img_key_state, 256);
    lv_obj_set_pos(ui_scr->video_rec_img_key_state, 122, 12);
    lv_obj_set_size(ui_scr->video_rec_img_key_state, 29, 29);
    lv_obj_add_flag(ui_scr->video_rec_img_key_state, LV_OBJ_FLAG_CLICKABLE);
    ui_style_set(ui_scr->video_rec_img_key_state, GUI_CTRL_IMG);

    // Write Timer video_rec_timer_1
    if (ui_scr->video_rec_timer_1 != NULL) {
        lv_timer_del(ui_scr->video_rec_timer_1);
    }
    ui_scr->video_rec_timer_1 = lv_timer_create(video_rec_timer_1_timer_cb, 1000, "");
    lv_timer_set_repeat_count(ui_scr->video_rec_timer_1, -1);
    lv_timer_pause(ui_scr->video_rec_timer_1);

    //Write codes video_rec_view_menu_b
    ui_scr->video_rec_view_menu_b = lv_obj_create(ui_scr->video_rec);
    lv_obj_set_pos(ui_scr->video_rec_view_menu_b, 0, 0);
    lv_obj_set_size(ui_scr->video_rec_view_menu_b, 800, 480);
    lv_obj_set_scrollbar_mode(ui_scr->video_rec_view_menu_b, LV_SCROLLBAR_MODE_OFF);
    lv_obj_add_flag(ui_scr->video_rec_view_menu_b, LV_OBJ_FLAG_HIDDEN);
    ui_style_set(ui_scr->video_rec_view_menu_b, GUI_CTRL_CONT);

    //Set style for video_rec_view_menu_b. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
    lv_obj_set_style_border_opa(ui_scr->video_rec_view_menu_b, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

    //Delete extra default style for video_rec_view_menu_b
    lv_obj_remove_style(ui_scr->video_rec_view_menu_b, &gui_cont_main_focus_key_style, LV_PART_MAIN | LV_STATE_FOCUS_KEY);

    //Write codes video_rec_view_menu
    ui_scr->video_rec_view_menu = lv_obj_create(ui_scr->video_rec_view_menu_b);
    lv_obj_set_pos(ui_scr->video_rec_view_menu, 0, 40);
    lv_obj_set_size(ui_scr->video_rec_view_menu, 800, 400);
    lv_obj_set_scrollbar_mode(ui_scr->video_rec_view_menu, LV_SCROLLBAR_MODE_OFF);
    ui_style_set(ui_scr->video_rec_view_menu, GUI_CTRL_CONT);

    //Set style for video_rec_view_menu. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
    lv_obj_set_style_bg_color(ui_scr->video_rec_view_menu, lv_color_make(0x61, 0x61, 0x61), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_scr->video_rec_view_menu, 205, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui_scr->video_rec_view_menu, lv_color_make(0x21, 0x95, 0xF6), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui_scr->video_rec_view_menu, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_outline_color(ui_scr->video_rec_view_menu, lv_color_make(0x21, 0x95, 0xF6), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_outline_opa(ui_scr->video_rec_view_menu, 91, LV_PART_MAIN | LV_STATE_DEFAULT);

    //Delete extra default style for video_rec_view_menu
    lv_obj_remove_style(ui_scr->video_rec_view_menu, &gui_cont_main_focus_key_style, LV_PART_MAIN | LV_STATE_FOCUS_KEY);

    //Write codes video_rec_view_reso
    ui_scr->video_rec_view_reso = lv_obj_create(ui_scr->video_rec_view_menu);
    lv_obj_set_pos(ui_scr->video_rec_view_reso, 0, 0);
    lv_obj_set_size(ui_scr->video_rec_view_reso, 800, 43);
    lv_obj_set_scrollbar_mode(ui_scr->video_rec_view_reso, LV_SCROLLBAR_MODE_OFF);
    lv_obj_add_flag(ui_scr->video_rec_view_reso, LV_OBJ_FLAG_EVENT_BUBBLE | LV_OBJ_FLAG_SCROLL_ON_FOCUS);
    lv_group_add_obj(def_group, ui_scr->video_rec_view_reso);
    ui_style_set(ui_scr->video_rec_view_reso, GUI_CTRL_CONT);

    //Write codes video_rec_img_2
    ui_scr->video_rec_img_2 = lv_img_create(ui_scr->video_rec_view_reso);
    lv_img_set_src(ui_scr->video_rec_img_2, gui_get_res_path(GUI_RES_M_SOLU_PNG));
    lv_img_set_pivot(ui_scr->video_rec_img_2, 0, 0);
    lv_img_set_angle(ui_scr->video_rec_img_2, 0);
    lv_img_set_zoom(ui_scr->video_rec_img_2, 256);
    lv_obj_set_pos(ui_scr->video_rec_img_2, 8, 6);
    lv_obj_set_size(ui_scr->video_rec_img_2, 29, 29);
    lv_obj_add_flag(ui_scr->video_rec_img_2, LV_OBJ_FLAG_CLICKABLE);
    ui_style_set(ui_scr->video_rec_img_2, GUI_CTRL_IMG);

    //Set style for video_rec_img_2. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
    lv_obj_set_style_bg_color(ui_scr->video_rec_img_2, lv_color_make(0xFF, 0xFF, 0xFF), LV_PART_MAIN | LV_STATE_DEFAULT);

    //Write codes video_rec_lbl_1
    ui_scr->video_rec_lbl_1 = lv_label_create(ui_scr->video_rec_view_reso);
    lv_label_set_long_mode(ui_scr->video_rec_lbl_1, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui_scr->video_rec_lbl_1, 50, 6);
    lv_obj_set_size(ui_scr->video_rec_lbl_1, 200, 32);
    lv_obj_set_scrollbar_mode(ui_scr->video_rec_lbl_1, LV_SCROLLBAR_MODE_OFF);
    ui_style_set(ui_scr->video_rec_lbl_1, GUI_CTRL_LABEL);

    //Write codes video_rec_view_two_rec
    ui_scr->video_rec_view_two_rec = lv_obj_create(ui_scr->video_rec_view_menu);
    lv_obj_set_pos(ui_scr->video_rec_view_two_rec, 0, 45);
    lv_obj_set_size(ui_scr->video_rec_view_two_rec, 800, 43);
    lv_obj_set_scrollbar_mode(ui_scr->video_rec_view_two_rec, LV_SCROLLBAR_MODE_OFF);
    lv_obj_add_flag(ui_scr->video_rec_view_two_rec, LV_OBJ_FLAG_EVENT_BUBBLE | LV_OBJ_FLAG_SCROLL_ON_FOCUS);
    lv_group_add_obj(def_group, ui_scr->video_rec_view_two_rec);
    ui_style_set(ui_scr->video_rec_view_two_rec, GUI_CTRL_CONT);

    //Write codes video_rec_img_3
    ui_scr->video_rec_img_3 = lv_img_create(ui_scr->video_rec_view_two_rec);
    lv_img_set_src(ui_scr->video_rec_img_3, gui_get_res_path(GUI_RES_M_TWO_REC_PNG));
    lv_img_set_pivot(ui_scr->video_rec_img_3, 0, 0);
    lv_img_set_angle(ui_scr->video_rec_img_3, 0);
    lv_img_set_zoom(ui_scr->video_rec_img_3, 256);
    lv_obj_set_pos(ui_scr->video_rec_img_3, 8, 6);
    lv_obj_set_size(ui_scr->video_rec_img_3, 29, 29);
    lv_obj_add_flag(ui_scr->video_rec_img_3, LV_OBJ_FLAG_CLICKABLE);
    ui_style_set(ui_scr->video_rec_img_3, GUI_CTRL_IMG);

    //Set style for video_rec_img_3. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
    lv_obj_set_style_bg_color(ui_scr->video_rec_img_3, lv_color_make(0xFF, 0xFF, 0xFF), LV_PART_MAIN | LV_STATE_DEFAULT);

    //Write codes video_rec_lbl_3
    ui_scr->video_rec_lbl_3 = lv_label_create(ui_scr->video_rec_view_two_rec);
    lv_label_set_long_mode(ui_scr->video_rec_lbl_3, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui_scr->video_rec_lbl_3, 50, 6);
    lv_obj_set_size(ui_scr->video_rec_lbl_3, 200, 32);
    lv_obj_set_scrollbar_mode(ui_scr->video_rec_lbl_3, LV_SCROLLBAR_MODE_OFF);
    ui_style_set(ui_scr->video_rec_lbl_3, GUI_CTRL_LABEL);

    //Write codes video_rec_view_cyc_rec
    ui_scr->video_rec_view_cyc_rec = lv_obj_create(ui_scr->video_rec_view_menu);
    lv_obj_set_pos(ui_scr->video_rec_view_cyc_rec, 0, 90);
    lv_obj_set_size(ui_scr->video_rec_view_cyc_rec, 800, 43);
    lv_obj_set_scrollbar_mode(ui_scr->video_rec_view_cyc_rec, LV_SCROLLBAR_MODE_OFF);
    lv_obj_add_flag(ui_scr->video_rec_view_cyc_rec, LV_OBJ_FLAG_EVENT_BUBBLE | LV_OBJ_FLAG_SCROLL_ON_FOCUS);
    lv_group_add_obj(def_group, ui_scr->video_rec_view_cyc_rec);
    ui_style_set(ui_scr->video_rec_view_cyc_rec, GUI_CTRL_CONT);

    //Write codes video_rec_img_4
    ui_scr->video_rec_img_4 = lv_img_create(ui_scr->video_rec_view_cyc_rec);
    lv_img_set_src(ui_scr->video_rec_img_4, gui_get_res_path(GUI_RES_M_CYC_PNG));
    lv_img_set_pivot(ui_scr->video_rec_img_4, 0, 0);
    lv_img_set_angle(ui_scr->video_rec_img_4, 0);
    lv_img_set_zoom(ui_scr->video_rec_img_4, 256);
    lv_obj_set_pos(ui_scr->video_rec_img_4, 8, 6);
    lv_obj_set_size(ui_scr->video_rec_img_4, 29, 29);
    lv_obj_add_flag(ui_scr->video_rec_img_4, LV_OBJ_FLAG_CLICKABLE);
    ui_style_set(ui_scr->video_rec_img_4, GUI_CTRL_IMG);

    //Set style for video_rec_img_4. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
    lv_obj_set_style_bg_color(ui_scr->video_rec_img_4, lv_color_make(0xFF, 0xFF, 0xFF), LV_PART_MAIN | LV_STATE_DEFAULT);

    //Write codes video_rec_lbl_4
    ui_scr->video_rec_lbl_4 = lv_label_create(ui_scr->video_rec_view_cyc_rec);
    lv_label_set_long_mode(ui_scr->video_rec_lbl_4, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui_scr->video_rec_lbl_4, 50, 6);
    lv_obj_set_size(ui_scr->video_rec_lbl_4, 200, 32);
    lv_obj_set_scrollbar_mode(ui_scr->video_rec_lbl_4, LV_SCROLLBAR_MODE_OFF);
    ui_style_set(ui_scr->video_rec_lbl_4, GUI_CTRL_LABEL);

    //Write codes video_rec_view_gap
    ui_scr->video_rec_view_gap = lv_obj_create(ui_scr->video_rec_view_menu);
    lv_obj_set_pos(ui_scr->video_rec_view_gap, 0, 135);
    lv_obj_set_size(ui_scr->video_rec_view_gap, 800, 43);
    lv_obj_set_scrollbar_mode(ui_scr->video_rec_view_gap, LV_SCROLLBAR_MODE_OFF);
    lv_obj_add_flag(ui_scr->video_rec_view_gap, LV_OBJ_FLAG_EVENT_BUBBLE | LV_OBJ_FLAG_SCROLL_ON_FOCUS);
    lv_group_add_obj(def_group, ui_scr->video_rec_view_gap);
    ui_style_set(ui_scr->video_rec_view_gap, GUI_CTRL_CONT);

    //Write codes video_rec_img_5
    ui_scr->video_rec_img_5 = lv_img_create(ui_scr->video_rec_view_gap);
    lv_img_set_src(ui_scr->video_rec_img_5, gui_get_res_path(GUI_RES_REC_NOCYC_PNG));
    lv_img_set_pivot(ui_scr->video_rec_img_5, 0, 0);
    lv_img_set_angle(ui_scr->video_rec_img_5, 0);
    lv_img_set_zoom(ui_scr->video_rec_img_5, 256);
    lv_obj_set_pos(ui_scr->video_rec_img_5, 8, 6);
    lv_obj_set_size(ui_scr->video_rec_img_5, 29, 29);
    lv_obj_add_flag(ui_scr->video_rec_img_5, LV_OBJ_FLAG_CLICKABLE);
    ui_style_set(ui_scr->video_rec_img_5, GUI_CTRL_IMG);

    //Set style for video_rec_img_5. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
    lv_obj_set_style_bg_color(ui_scr->video_rec_img_5, lv_color_make(0xFF, 0xFF, 0xFF), LV_PART_MAIN | LV_STATE_DEFAULT);

    //Write codes video_rec_lbl_5
    ui_scr->video_rec_lbl_5 = lv_label_create(ui_scr->video_rec_view_gap);
    lv_label_set_long_mode(ui_scr->video_rec_lbl_5, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui_scr->video_rec_lbl_5, 50, 6);
    lv_obj_set_size(ui_scr->video_rec_lbl_5, 200, 32);
    lv_obj_set_scrollbar_mode(ui_scr->video_rec_lbl_5, LV_SCROLLBAR_MODE_OFF);
    ui_style_set(ui_scr->video_rec_lbl_5, GUI_CTRL_LABEL);

    //Write codes video_rec_view_hdr
    ui_scr->video_rec_view_hdr = lv_obj_create(ui_scr->video_rec_view_menu);
    lv_obj_set_pos(ui_scr->video_rec_view_hdr, 0, 180);
    lv_obj_set_size(ui_scr->video_rec_view_hdr, 800, 43);
    lv_obj_set_scrollbar_mode(ui_scr->video_rec_view_hdr, LV_SCROLLBAR_MODE_OFF);
    lv_obj_add_flag(ui_scr->video_rec_view_hdr, LV_OBJ_FLAG_EVENT_BUBBLE | LV_OBJ_FLAG_SCROLL_ON_FOCUS);
    lv_group_add_obj(def_group, ui_scr->video_rec_view_hdr);
    ui_style_set(ui_scr->video_rec_view_hdr, GUI_CTRL_CONT);

    //Write codes video_rec_img_6
    ui_scr->video_rec_img_6 = lv_img_create(ui_scr->video_rec_view_hdr);
    lv_img_set_src(ui_scr->video_rec_img_6, gui_get_res_path(GUI_RES_M_HDR_PNG));
    lv_img_set_pivot(ui_scr->video_rec_img_6, 0, 0);
    lv_img_set_angle(ui_scr->video_rec_img_6, 0);
    lv_img_set_zoom(ui_scr->video_rec_img_6, 256);
    lv_obj_set_pos(ui_scr->video_rec_img_6, 8, 6);
    lv_obj_set_size(ui_scr->video_rec_img_6, 29, 29);
    lv_obj_add_flag(ui_scr->video_rec_img_6, LV_OBJ_FLAG_CLICKABLE);
    ui_style_set(ui_scr->video_rec_img_6, GUI_CTRL_IMG);

    //Set style for video_rec_img_6. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
    lv_obj_set_style_bg_color(ui_scr->video_rec_img_6, lv_color_make(0xFF, 0xFF, 0xFF), LV_PART_MAIN | LV_STATE_DEFAULT);

    //Write codes video_rec_lbl_6
    ui_scr->video_rec_lbl_6 = lv_label_create(ui_scr->video_rec_view_hdr);
    lv_label_set_long_mode(ui_scr->video_rec_lbl_6, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui_scr->video_rec_lbl_6, 50, 6);
    lv_obj_set_size(ui_scr->video_rec_lbl_6, 200, 32);
    lv_obj_set_scrollbar_mode(ui_scr->video_rec_lbl_6, LV_SCROLLBAR_MODE_OFF);
    ui_style_set(ui_scr->video_rec_lbl_6, GUI_CTRL_LABEL);

    //Write codes video_rec_view_exp
    ui_scr->video_rec_view_exp = lv_obj_create(ui_scr->video_rec_view_menu);
    lv_obj_set_pos(ui_scr->video_rec_view_exp, 0, 225);
    lv_obj_set_size(ui_scr->video_rec_view_exp, 800, 43);
    lv_obj_set_scrollbar_mode(ui_scr->video_rec_view_exp, LV_SCROLLBAR_MODE_OFF);
    lv_obj_add_flag(ui_scr->video_rec_view_exp, LV_OBJ_FLAG_EVENT_BUBBLE | LV_OBJ_FLAG_SCROLL_ON_FOCUS);
    lv_group_add_obj(def_group, ui_scr->video_rec_view_exp);
    ui_style_set(ui_scr->video_rec_view_exp, GUI_CTRL_CONT);

    //Write codes video_rec_img_7
    ui_scr->video_rec_img_7 = lv_img_create(ui_scr->video_rec_view_exp);
    lv_img_set_src(ui_scr->video_rec_img_7, gui_get_res_path(GUI_RES_M_EXP_PNG));
    lv_img_set_pivot(ui_scr->video_rec_img_7, 0, 0);
    lv_img_set_angle(ui_scr->video_rec_img_7, 0);
    lv_img_set_zoom(ui_scr->video_rec_img_7, 256);
    lv_obj_set_pos(ui_scr->video_rec_img_7, 8, 6);
    lv_obj_set_size(ui_scr->video_rec_img_7, 29, 29);
    lv_obj_add_flag(ui_scr->video_rec_img_7, LV_OBJ_FLAG_CLICKABLE);
    ui_style_set(ui_scr->video_rec_img_7, GUI_CTRL_IMG);

    //Set style for video_rec_img_7. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
    lv_obj_set_style_bg_color(ui_scr->video_rec_img_7, lv_color_make(0xFF, 0xFF, 0xFF), LV_PART_MAIN | LV_STATE_DEFAULT);

    //Write codes video_rec_lbl_7
    ui_scr->video_rec_lbl_7 = lv_label_create(ui_scr->video_rec_view_exp);
    lv_label_set_long_mode(ui_scr->video_rec_lbl_7, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui_scr->video_rec_lbl_7, 50, 6);
    lv_obj_set_size(ui_scr->video_rec_lbl_7, 200, 32);
    lv_obj_set_scrollbar_mode(ui_scr->video_rec_lbl_7, LV_SCROLLBAR_MODE_OFF);
    ui_style_set(ui_scr->video_rec_lbl_7, GUI_CTRL_LABEL);

    //Write codes video_rec_view_motd
    ui_scr->video_rec_view_motd = lv_obj_create(ui_scr->video_rec_view_menu);
    lv_obj_set_pos(ui_scr->video_rec_view_motd, 0, 270);
    lv_obj_set_size(ui_scr->video_rec_view_motd, 800, 43);
    lv_obj_set_scrollbar_mode(ui_scr->video_rec_view_motd, LV_SCROLLBAR_MODE_OFF);
    lv_obj_add_flag(ui_scr->video_rec_view_motd, LV_OBJ_FLAG_EVENT_BUBBLE | LV_OBJ_FLAG_SCROLL_ON_FOCUS);
    lv_group_add_obj(def_group, ui_scr->video_rec_view_motd);
    ui_style_set(ui_scr->video_rec_view_motd, GUI_CTRL_CONT);

    //Write codes video_rec_img_8
    ui_scr->video_rec_img_8 = lv_img_create(ui_scr->video_rec_view_motd);
    lv_img_set_src(ui_scr->video_rec_img_8, gui_get_res_path(GUI_RES_M_MOT_PNG));
    lv_img_set_pivot(ui_scr->video_rec_img_8, 0, 0);
    lv_img_set_angle(ui_scr->video_rec_img_8, 0);
    lv_img_set_zoom(ui_scr->video_rec_img_8, 256);
    lv_obj_set_pos(ui_scr->video_rec_img_8, 8, 6);
    lv_obj_set_size(ui_scr->video_rec_img_8, 29, 29);
    lv_obj_add_flag(ui_scr->video_rec_img_8, LV_OBJ_FLAG_CLICKABLE);
    ui_style_set(ui_scr->video_rec_img_8, GUI_CTRL_IMG);

    //Set style for video_rec_img_8. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
    lv_obj_set_style_bg_color(ui_scr->video_rec_img_8, lv_color_make(0xFF, 0xFF, 0xFF), LV_PART_MAIN | LV_STATE_DEFAULT);

    //Write codes video_rec_lbl_8
    ui_scr->video_rec_lbl_8 = lv_label_create(ui_scr->video_rec_view_motd);
    lv_label_set_long_mode(ui_scr->video_rec_lbl_8, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui_scr->video_rec_lbl_8, 50, 6);
    lv_obj_set_size(ui_scr->video_rec_lbl_8, 200, 32);
    lv_obj_set_scrollbar_mode(ui_scr->video_rec_lbl_8, LV_SCROLLBAR_MODE_OFF);
    ui_style_set(ui_scr->video_rec_lbl_8, GUI_CTRL_LABEL);

    //Write codes video_rec_view_mic
    ui_scr->video_rec_view_mic = lv_obj_create(ui_scr->video_rec_view_menu);
    lv_obj_set_pos(ui_scr->video_rec_view_mic, 0, 315);
    lv_obj_set_size(ui_scr->video_rec_view_mic, 800, 43);
    lv_obj_set_scrollbar_mode(ui_scr->video_rec_view_mic, LV_SCROLLBAR_MODE_OFF);
    lv_obj_add_flag(ui_scr->video_rec_view_mic, LV_OBJ_FLAG_EVENT_BUBBLE | LV_OBJ_FLAG_SCROLL_ON_FOCUS);
    lv_group_add_obj(def_group, ui_scr->video_rec_view_mic);
    ui_style_set(ui_scr->video_rec_view_mic, GUI_CTRL_CONT);

    //Write codes video_rec_img_9
    ui_scr->video_rec_img_9 = lv_img_create(ui_scr->video_rec_view_mic);
    lv_img_set_src(ui_scr->video_rec_img_9, gui_get_res_path(GUI_RES_M_AUD_PNG));
    lv_img_set_pivot(ui_scr->video_rec_img_9, 0, 0);
    lv_img_set_angle(ui_scr->video_rec_img_9, 0);
    lv_img_set_zoom(ui_scr->video_rec_img_9, 256);
    lv_obj_set_pos(ui_scr->video_rec_img_9, 8, 6);
    lv_obj_set_size(ui_scr->video_rec_img_9, 29, 29);
    lv_obj_add_flag(ui_scr->video_rec_img_9, LV_OBJ_FLAG_CLICKABLE);
    ui_style_set(ui_scr->video_rec_img_9, GUI_CTRL_IMG);

    //Set style for video_rec_img_9. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
    lv_obj_set_style_bg_color(ui_scr->video_rec_img_9, lv_color_make(0xFF, 0xFF, 0xFF), LV_PART_MAIN | LV_STATE_DEFAULT);

    //Write codes video_rec_lbl_9
    ui_scr->video_rec_lbl_9 = lv_label_create(ui_scr->video_rec_view_mic);
    lv_label_set_long_mode(ui_scr->video_rec_lbl_9, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui_scr->video_rec_lbl_9, 50, 6);
    lv_obj_set_size(ui_scr->video_rec_lbl_9, 200, 32);
    lv_obj_set_scrollbar_mode(ui_scr->video_rec_lbl_9, LV_SCROLLBAR_MODE_OFF);
    ui_style_set(ui_scr->video_rec_lbl_9, GUI_CTRL_LABEL);

    //Write codes video_rec_view_date
    ui_scr->video_rec_view_date = lv_obj_create(ui_scr->video_rec_view_menu);
    lv_obj_set_pos(ui_scr->video_rec_view_date, 0, 360);
    lv_obj_set_size(ui_scr->video_rec_view_date, 800, 43);
    lv_obj_set_scrollbar_mode(ui_scr->video_rec_view_date, LV_SCROLLBAR_MODE_OFF);
    lv_obj_add_flag(ui_scr->video_rec_view_date, LV_OBJ_FLAG_EVENT_BUBBLE | LV_OBJ_FLAG_SCROLL_ON_FOCUS);
    lv_group_add_obj(def_group, ui_scr->video_rec_view_date);
    ui_style_set(ui_scr->video_rec_view_date, GUI_CTRL_CONT);

    //Write codes video_rec_img_10
    ui_scr->video_rec_img_10 = lv_img_create(ui_scr->video_rec_view_date);
    lv_img_set_src(ui_scr->video_rec_img_10, gui_get_res_path(GUI_RES_M_DAT_PNG));
    lv_img_set_pivot(ui_scr->video_rec_img_10, 0, 0);
    lv_img_set_angle(ui_scr->video_rec_img_10, 0);
    lv_img_set_zoom(ui_scr->video_rec_img_10, 256);
    lv_obj_set_pos(ui_scr->video_rec_img_10, 8, 6);
    lv_obj_set_size(ui_scr->video_rec_img_10, 29, 29);
    lv_obj_add_flag(ui_scr->video_rec_img_10, LV_OBJ_FLAG_CLICKABLE);
    ui_style_set(ui_scr->video_rec_img_10, GUI_CTRL_IMG);

    //Set style for video_rec_img_10. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
    lv_obj_set_style_bg_color(ui_scr->video_rec_img_10, lv_color_make(0xFF, 0xFF, 0xFF), LV_PART_MAIN | LV_STATE_DEFAULT);

    //Write codes video_rec_lbl_10
    ui_scr->video_rec_lbl_10 = lv_label_create(ui_scr->video_rec_view_date);
    lv_label_set_long_mode(ui_scr->video_rec_lbl_10, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui_scr->video_rec_lbl_10, 50, 6);
    lv_obj_set_size(ui_scr->video_rec_lbl_10, 200, 32);
    lv_obj_set_scrollbar_mode(ui_scr->video_rec_lbl_10, LV_SCROLLBAR_MODE_OFF);
    ui_style_set(ui_scr->video_rec_lbl_10, GUI_CTRL_LABEL);

    //Write codes video_rec_view_gra
    ui_scr->video_rec_view_gra = lv_obj_create(ui_scr->video_rec_view_menu);
    lv_obj_set_pos(ui_scr->video_rec_view_gra, 0, 405);
    lv_obj_set_size(ui_scr->video_rec_view_gra, 800, 43);
    lv_obj_set_scrollbar_mode(ui_scr->video_rec_view_gra, LV_SCROLLBAR_MODE_OFF);
    lv_obj_add_flag(ui_scr->video_rec_view_gra, LV_OBJ_FLAG_EVENT_BUBBLE | LV_OBJ_FLAG_SCROLL_ON_FOCUS);
    lv_group_add_obj(def_group, ui_scr->video_rec_view_gra);
    ui_style_set(ui_scr->video_rec_view_gra, GUI_CTRL_CONT);

    //Write codes video_rec_img_11
    ui_scr->video_rec_img_11 = lv_img_create(ui_scr->video_rec_view_gra);
    lv_img_set_src(ui_scr->video_rec_img_11, gui_get_res_path(GUI_RES_M_GRA_PNG));
    lv_img_set_pivot(ui_scr->video_rec_img_11, 0, 0);
    lv_img_set_angle(ui_scr->video_rec_img_11, 0);
    lv_img_set_zoom(ui_scr->video_rec_img_11, 256);
    lv_obj_set_pos(ui_scr->video_rec_img_11, 8, 6);
    lv_obj_set_size(ui_scr->video_rec_img_11, 29, 29);
    lv_obj_add_flag(ui_scr->video_rec_img_11, LV_OBJ_FLAG_CLICKABLE);
    ui_style_set(ui_scr->video_rec_img_11, GUI_CTRL_IMG);

    //Set style for video_rec_img_11. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
    lv_obj_set_style_bg_color(ui_scr->video_rec_img_11, lv_color_make(0xFF, 0xFF, 0xFF), LV_PART_MAIN | LV_STATE_DEFAULT);

    //Write codes video_rec_lbl_11
    ui_scr->video_rec_lbl_11 = lv_label_create(ui_scr->video_rec_view_gra);
    lv_label_set_long_mode(ui_scr->video_rec_lbl_11, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui_scr->video_rec_lbl_11, 50, 6);
    lv_obj_set_size(ui_scr->video_rec_lbl_11, 200, 32);
    lv_obj_set_scrollbar_mode(ui_scr->video_rec_lbl_11, LV_SCROLLBAR_MODE_OFF);
    ui_style_set(ui_scr->video_rec_lbl_11, GUI_CTRL_LABEL);

    //Write codes video_rec_view_par
    ui_scr->video_rec_view_par = lv_obj_create(ui_scr->video_rec_view_menu);
    lv_obj_set_pos(ui_scr->video_rec_view_par, 0, 450);
    lv_obj_set_size(ui_scr->video_rec_view_par, 800, 43);
    lv_obj_set_scrollbar_mode(ui_scr->video_rec_view_par, LV_SCROLLBAR_MODE_OFF);
    lv_obj_add_flag(ui_scr->video_rec_view_par, LV_OBJ_FLAG_EVENT_BUBBLE | LV_OBJ_FLAG_SCROLL_ON_FOCUS);
    lv_group_add_obj(def_group, ui_scr->video_rec_view_par);
    ui_style_set(ui_scr->video_rec_view_par, GUI_CTRL_CONT);

    //Write codes video_rec_img_12
    ui_scr->video_rec_img_12 = lv_img_create(ui_scr->video_rec_view_par);
    lv_img_set_src(ui_scr->video_rec_img_12, gui_get_res_path(GUI_RES_M_PARK_PNG));
    lv_img_set_pivot(ui_scr->video_rec_img_12, 0, 0);
    lv_img_set_angle(ui_scr->video_rec_img_12, 0);
    lv_img_set_zoom(ui_scr->video_rec_img_12, 256);
    lv_obj_set_pos(ui_scr->video_rec_img_12, 8, 6);
    lv_obj_set_size(ui_scr->video_rec_img_12, 29, 29);
    lv_obj_add_flag(ui_scr->video_rec_img_12, LV_OBJ_FLAG_CLICKABLE);
    ui_style_set(ui_scr->video_rec_img_12, GUI_CTRL_IMG);

    //Set style for video_rec_img_12. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
    lv_obj_set_style_bg_color(ui_scr->video_rec_img_12, lv_color_make(0xFF, 0xFF, 0xFF), LV_PART_MAIN | LV_STATE_DEFAULT);

    //Write codes video_rec_lbl_12
    ui_scr->video_rec_lbl_12 = lv_label_create(ui_scr->video_rec_view_par);
    lv_label_set_long_mode(ui_scr->video_rec_lbl_12, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui_scr->video_rec_lbl_12, 50, 6);
    lv_obj_set_size(ui_scr->video_rec_lbl_12, 200, 32);
    lv_obj_set_scrollbar_mode(ui_scr->video_rec_lbl_12, LV_SCROLLBAR_MODE_OFF);
    ui_style_set(ui_scr->video_rec_lbl_12, GUI_CTRL_LABEL);

    //Write codes video_rec_view_num
    ui_scr->video_rec_view_num = lv_obj_create(ui_scr->video_rec_view_menu);
    lv_obj_set_pos(ui_scr->video_rec_view_num, 0, 495);
    lv_obj_set_size(ui_scr->video_rec_view_num, 800, 43);
    lv_obj_set_scrollbar_mode(ui_scr->video_rec_view_num, LV_SCROLLBAR_MODE_OFF);
    lv_obj_add_flag(ui_scr->video_rec_view_num, LV_OBJ_FLAG_EVENT_BUBBLE | LV_OBJ_FLAG_SCROLL_ON_FOCUS);
    lv_group_add_obj(def_group, ui_scr->video_rec_view_num);
    ui_style_set(ui_scr->video_rec_view_num, GUI_CTRL_CONT);

    //Write codes video_rec_img_13
    ui_scr->video_rec_img_13 = lv_img_create(ui_scr->video_rec_view_num);
    lv_img_set_src(ui_scr->video_rec_img_13, gui_get_res_path(GUI_RES_M_NUM_PNG));
    lv_img_set_pivot(ui_scr->video_rec_img_13, 0, 0);
    lv_img_set_angle(ui_scr->video_rec_img_13, 0);
    lv_img_set_zoom(ui_scr->video_rec_img_13, 256);
    lv_obj_set_pos(ui_scr->video_rec_img_13, 8, 6);
    lv_obj_set_size(ui_scr->video_rec_img_13, 29, 29);
    lv_obj_add_flag(ui_scr->video_rec_img_13, LV_OBJ_FLAG_CLICKABLE);
    ui_style_set(ui_scr->video_rec_img_13, GUI_CTRL_IMG);

    //Set style for video_rec_img_13. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
    lv_obj_set_style_bg_color(ui_scr->video_rec_img_13, lv_color_make(0xFF, 0xFF, 0xFF), LV_PART_MAIN | LV_STATE_DEFAULT);

    //Write codes video_rec_lbl_13
    ui_scr->video_rec_lbl_13 = lv_label_create(ui_scr->video_rec_view_num);
    lv_label_set_long_mode(ui_scr->video_rec_lbl_13, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui_scr->video_rec_lbl_13, 50, 6);
    lv_obj_set_size(ui_scr->video_rec_lbl_13, 200, 32);
    lv_obj_set_scrollbar_mode(ui_scr->video_rec_lbl_13, LV_SCROLLBAR_MODE_OFF);
    ui_style_set(ui_scr->video_rec_lbl_13, GUI_CTRL_LABEL);

    //Write codes video_rec_view_hlw
    ui_scr->video_rec_view_hlw = lv_obj_create(ui_scr->video_rec_view_menu);
    lv_obj_set_pos(ui_scr->video_rec_view_hlw, 0, 540);
    lv_obj_set_size(ui_scr->video_rec_view_hlw, 800, 43);
    lv_obj_set_scrollbar_mode(ui_scr->video_rec_view_hlw, LV_SCROLLBAR_MODE_OFF);
    lv_obj_add_flag(ui_scr->video_rec_view_hlw, LV_OBJ_FLAG_EVENT_BUBBLE | LV_OBJ_FLAG_SCROLL_ON_FOCUS);
    lv_group_add_obj(def_group, ui_scr->video_rec_view_hlw);
    ui_style_set(ui_scr->video_rec_view_hlw, GUI_CTRL_CONT);

    //Write codes video_rec_img_14
    ui_scr->video_rec_img_14 = lv_img_create(ui_scr->video_rec_view_hlw);
    lv_img_set_src(ui_scr->video_rec_img_14, gui_get_res_path(GUI_RES_M_FLIG_PNG));
    lv_img_set_pivot(ui_scr->video_rec_img_14, 0, 0);
    lv_img_set_angle(ui_scr->video_rec_img_14, 0);
    lv_img_set_zoom(ui_scr->video_rec_img_14, 256);
    lv_obj_set_pos(ui_scr->video_rec_img_14, 8, 6);
    lv_obj_set_size(ui_scr->video_rec_img_14, 29, 29);
    lv_obj_add_flag(ui_scr->video_rec_img_14, LV_OBJ_FLAG_CLICKABLE);
    ui_style_set(ui_scr->video_rec_img_14, GUI_CTRL_IMG);

    //Set style for video_rec_img_14. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
    lv_obj_set_style_bg_color(ui_scr->video_rec_img_14, lv_color_make(0xFF, 0xFF, 0xFF), LV_PART_MAIN | LV_STATE_DEFAULT);

    //Write codes video_rec_lbl_14
    ui_scr->video_rec_lbl_14 = lv_label_create(ui_scr->video_rec_view_hlw);
    lv_label_set_long_mode(ui_scr->video_rec_lbl_14, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui_scr->video_rec_lbl_14, 50, 6);
    lv_obj_set_size(ui_scr->video_rec_lbl_14, 200, 32);
    lv_obj_set_scrollbar_mode(ui_scr->video_rec_lbl_14, LV_SCROLLBAR_MODE_OFF);
    ui_style_set(ui_scr->video_rec_lbl_14, GUI_CTRL_LABEL);

    //Write codes video_rec_img_15
    ui_scr->video_rec_img_15 = lv_img_create(ui_scr->video_rec_view_menu_b);
    lv_img_set_src(ui_scr->video_rec_img_15, gui_get_res_path(GUI_RES_MENU_STA_PNG));
    lv_img_set_pivot(ui_scr->video_rec_img_15, 0, 0);
    lv_img_set_angle(ui_scr->video_rec_img_15, 0);
    lv_img_set_zoom(ui_scr->video_rec_img_15, 256);
    lv_obj_set_pos(ui_scr->video_rec_img_15, 0, 0);
    lv_obj_set_size(ui_scr->video_rec_img_15, 800, 40);
    lv_obj_add_flag(ui_scr->video_rec_img_15, LV_OBJ_FLAG_CLICKABLE);
    ui_style_set(ui_scr->video_rec_img_15, GUI_CTRL_IMG);

    //Set style for video_rec_img_15. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
    lv_obj_set_style_outline_opa(ui_scr->video_rec_img_15, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

    //Write codes video_rec_img_16
    ui_scr->video_rec_img_16 = lv_img_create(ui_scr->video_rec_view_menu_b);
    lv_img_set_src(ui_scr->video_rec_img_16, gui_get_res_path(GUI_RES_MENU_STA_PNG));
    lv_img_set_pivot(ui_scr->video_rec_img_16, 0, 0);
    lv_img_set_angle(ui_scr->video_rec_img_16, 0);
    lv_img_set_zoom(ui_scr->video_rec_img_16, 256);
    lv_obj_set_pos(ui_scr->video_rec_img_16, 0, 440);
    lv_obj_set_size(ui_scr->video_rec_img_16, 800, 40);
    lv_obj_add_flag(ui_scr->video_rec_img_16, LV_OBJ_FLAG_CLICKABLE);
    ui_style_set(ui_scr->video_rec_img_16, GUI_CTRL_IMG);

    //Set style for video_rec_img_16. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
    lv_obj_set_style_outline_opa(ui_scr->video_rec_img_16, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

    //Write codes video_rec_img_17
    ui_scr->video_rec_img_17 = lv_img_create(ui_scr->video_rec_view_menu_b);
    lv_img_set_src(ui_scr->video_rec_img_17, gui_get_res_path(GUI_RES_REC_PNG));
    lv_img_set_pivot(ui_scr->video_rec_img_17, 0, 0);
    lv_img_set_angle(ui_scr->video_rec_img_17, 0);
    lv_img_set_zoom(ui_scr->video_rec_img_17, 256);
    lv_obj_set_pos(ui_scr->video_rec_img_17, 9, 5);
    lv_obj_set_size(ui_scr->video_rec_img_17, 40, 30);
    lv_obj_add_flag(ui_scr->video_rec_img_17, LV_OBJ_FLAG_CLICKABLE);
    ui_style_set(ui_scr->video_rec_img_17, GUI_CTRL_IMG);

    //Set style for video_rec_img_17. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
    lv_obj_set_style_outline_color(ui_scr->video_rec_img_17, lv_color_make(0x42, 0xA5, 0xF5), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_outline_width(ui_scr->video_rec_img_17, 4, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_outline_opa(ui_scr->video_rec_img_17, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    //Write codes video_rec_img_18
    ui_scr->video_rec_img_18 = lv_img_create(ui_scr->video_rec_view_menu_b);
    lv_img_set_src(ui_scr->video_rec_img_18, gui_get_res_path(GUI_RES_SET_PNG));
    lv_img_set_pivot(ui_scr->video_rec_img_18, 0, 0);
    lv_img_set_angle(ui_scr->video_rec_img_18, 0);
    lv_img_set_zoom(ui_scr->video_rec_img_18, 256);
    lv_obj_set_pos(ui_scr->video_rec_img_18, 70, 1);
    lv_obj_set_size(ui_scr->video_rec_img_18, 37, 37);
    lv_obj_add_flag(ui_scr->video_rec_img_18, LV_OBJ_FLAG_CLICKABLE);
    ui_style_set(ui_scr->video_rec_img_18, GUI_CTRL_IMG);

    //Write codes video_rec_img_19
    ui_scr->video_rec_img_19 = lv_img_create(ui_scr->video_rec_view_menu_b);
    lv_img_set_src(ui_scr->video_rec_img_19, gui_get_res_path(GUI_RES_LEFT_PNG));
    lv_img_set_pivot(ui_scr->video_rec_img_19, 0, 0);
    lv_img_set_angle(ui_scr->video_rec_img_19, 0);
    lv_img_set_zoom(ui_scr->video_rec_img_19, 256);
    lv_obj_set_pos(ui_scr->video_rec_img_19, 200, 445);
    lv_obj_set_size(ui_scr->video_rec_img_19, 21, 29);
    lv_obj_add_flag(ui_scr->video_rec_img_19, LV_OBJ_FLAG_CLICKABLE);
    ui_style_set(ui_scr->video_rec_img_19, GUI_CTRL_IMG);

    //Write codes video_rec_img_20
    ui_scr->video_rec_img_20 = lv_img_create(ui_scr->video_rec_view_menu_b);
    lv_img_set_src(ui_scr->video_rec_img_20, gui_get_res_path(GUI_RES_UP_PNG));
    lv_img_set_pivot(ui_scr->video_rec_img_20, 0, 0);
    lv_img_set_angle(ui_scr->video_rec_img_20, 0);
    lv_img_set_zoom(ui_scr->video_rec_img_20, 256);
    lv_obj_set_pos(ui_scr->video_rec_img_20, 321, 448);
    lv_obj_set_size(ui_scr->video_rec_img_20, 29, 21);
    lv_obj_add_flag(ui_scr->video_rec_img_20, LV_OBJ_FLAG_CLICKABLE);
    ui_style_set(ui_scr->video_rec_img_20, GUI_CTRL_IMG);

    //Write codes video_rec_img_21
    ui_scr->video_rec_img_21 = lv_img_create(ui_scr->video_rec_view_menu_b);
    lv_img_set_src(ui_scr->video_rec_img_21, gui_get_res_path(GUI_RES_DOWN_PNG));
    lv_img_set_pivot(ui_scr->video_rec_img_21, 0, 0);
    lv_img_set_angle(ui_scr->video_rec_img_21, 0);
    lv_img_set_zoom(ui_scr->video_rec_img_21, 256);
    lv_obj_set_pos(ui_scr->video_rec_img_21, 450, 448);
    lv_obj_set_size(ui_scr->video_rec_img_21, 29, 21);
    lv_obj_add_flag(ui_scr->video_rec_img_21, LV_OBJ_FLAG_CLICKABLE);
    ui_style_set(ui_scr->video_rec_img_21, GUI_CTRL_IMG);

    //Write codes video_rec_img_22
    ui_scr->video_rec_img_22 = lv_img_create(ui_scr->video_rec_view_menu_b);
    lv_img_set_src(ui_scr->video_rec_img_22, gui_get_res_path(GUI_RES_RIGHT_PNG));
    lv_img_set_pivot(ui_scr->video_rec_img_22, 0, 0);
    lv_img_set_angle(ui_scr->video_rec_img_22, 0);
    lv_img_set_zoom(ui_scr->video_rec_img_22, 256);
    lv_obj_set_pos(ui_scr->video_rec_img_22, 579, 445);
    lv_obj_set_size(ui_scr->video_rec_img_22, 21, 29);
    lv_obj_add_flag(ui_scr->video_rec_img_22, LV_OBJ_FLAG_CLICKABLE);
    ui_style_set(ui_scr->video_rec_img_22, GUI_CTRL_IMG);

    //Write codes video_rec_view_submenu
    ui_scr->video_rec_view_submenu = lv_obj_create(ui_scr->video_rec);
    lv_obj_set_pos(ui_scr->video_rec_view_submenu, 111, 83);
    lv_obj_set_size(ui_scr->video_rec_view_submenu, 590, 314);
    lv_obj_set_scrollbar_mode(ui_scr->video_rec_view_submenu, LV_SCROLLBAR_MODE_OFF);
    lv_obj_add_flag(ui_scr->video_rec_view_submenu, LV_OBJ_FLAG_HIDDEN);
    ui_style_set(ui_scr->video_rec_view_submenu, GUI_CTRL_CONT);

    //Set style for video_rec_view_submenu. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
    lv_obj_set_style_bg_color(ui_scr->video_rec_view_submenu, lv_color_make(0x75, 0x75, 0x75), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_scr->video_rec_view_submenu, 250, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui_scr->video_rec_view_submenu, 2, LV_PART_MAIN | LV_STATE_DEFAULT);

    //Delete extra default style for video_rec_view_submenu
    lv_obj_remove_style(ui_scr->video_rec_view_submenu, &gui_cont_main_focus_key_style, LV_PART_MAIN | LV_STATE_FOCUS_KEY);

    //Write codes video_rec_rec_submenu_btn_1
    ui_scr->video_rec_rec_submenu_btn_1 = lv_btn_create(ui_scr->video_rec_view_submenu);
    lv_obj_set_pos(ui_scr->video_rec_rec_submenu_btn_1, 83, 44);
    lv_obj_set_size(ui_scr->video_rec_rec_submenu_btn_1, 438, 37);
    lv_obj_set_scrollbar_mode(ui_scr->video_rec_rec_submenu_btn_1, LV_SCROLLBAR_MODE_OFF);
    lv_obj_add_flag(ui_scr->video_rec_rec_submenu_btn_1, LV_OBJ_FLAG_EVENT_BUBBLE);
    ui_style_set(ui_scr->video_rec_rec_submenu_btn_1, GUI_CTRL_BUTTON);

    //Set style for video_rec_rec_submenu_btn_1. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
    lv_obj_set_style_bg_opa(ui_scr->video_rec_rec_submenu_btn_1, 203, LV_PART_MAIN | LV_STATE_DEFAULT);
    ui_scr->video_rec_rec_submenu_btn_1_label = lv_label_create(ui_scr->video_rec_rec_submenu_btn_1);
    lv_label_set_text(ui_scr->video_rec_rec_submenu_btn_1_label, "button1");
    lv_obj_set_style_pad_all(ui_scr->video_rec_rec_submenu_btn_1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_align(ui_scr->video_rec_rec_submenu_btn_1_label, LV_ALIGN_CENTER, 0, 0);

    //Write codes video_rec_rec_submenu_btn_2
    ui_scr->video_rec_rec_submenu_btn_2 = lv_btn_create(ui_scr->video_rec_view_submenu);
    lv_obj_set_pos(ui_scr->video_rec_rec_submenu_btn_2, 83, 111);
    lv_obj_set_size(ui_scr->video_rec_rec_submenu_btn_2, 438, 37);
    lv_obj_set_scrollbar_mode(ui_scr->video_rec_rec_submenu_btn_2, LV_SCROLLBAR_MODE_OFF);
    lv_obj_add_flag(ui_scr->video_rec_rec_submenu_btn_2, LV_OBJ_FLAG_EVENT_BUBBLE);
    ui_style_set(ui_scr->video_rec_rec_submenu_btn_2, GUI_CTRL_BUTTON);

    //Set style for video_rec_rec_submenu_btn_2. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
    lv_obj_set_style_bg_opa(ui_scr->video_rec_rec_submenu_btn_2, 215, LV_PART_MAIN | LV_STATE_DEFAULT);
    ui_scr->video_rec_rec_submenu_btn_2_label = lv_label_create(ui_scr->video_rec_rec_submenu_btn_2);
    lv_label_set_text(ui_scr->video_rec_rec_submenu_btn_2_label, "button2");
    lv_obj_set_style_pad_all(ui_scr->video_rec_rec_submenu_btn_2, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_align(ui_scr->video_rec_rec_submenu_btn_2_label, LV_ALIGN_CENTER, 0, 0);

    //Write codes video_rec_rec_submenu_btn_3
    ui_scr->video_rec_rec_submenu_btn_3 = lv_btn_create(ui_scr->video_rec_view_submenu);
    lv_obj_set_pos(ui_scr->video_rec_rec_submenu_btn_3, 83, 171);
    lv_obj_set_size(ui_scr->video_rec_rec_submenu_btn_3, 438, 37);
    lv_obj_set_scrollbar_mode(ui_scr->video_rec_rec_submenu_btn_3, LV_SCROLLBAR_MODE_OFF);
    lv_obj_add_flag(ui_scr->video_rec_rec_submenu_btn_3, LV_OBJ_FLAG_EVENT_BUBBLE);
    ui_style_set(ui_scr->video_rec_rec_submenu_btn_3, GUI_CTRL_BUTTON);

    //Set style for video_rec_rec_submenu_btn_3. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
    lv_obj_set_style_bg_opa(ui_scr->video_rec_rec_submenu_btn_3, 205, LV_PART_MAIN | LV_STATE_DEFAULT);
    ui_scr->video_rec_rec_submenu_btn_3_label = lv_label_create(ui_scr->video_rec_rec_submenu_btn_3);
    lv_label_set_text(ui_scr->video_rec_rec_submenu_btn_3_label, "button3");
    lv_obj_set_style_pad_all(ui_scr->video_rec_rec_submenu_btn_3, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_align(ui_scr->video_rec_rec_submenu_btn_3_label, LV_ALIGN_CENTER, 0, 0);

    //Write codes video_rec_rec_submenu_btn_4
    ui_scr->video_rec_rec_submenu_btn_4 = lv_btn_create(ui_scr->video_rec_view_submenu);
    lv_obj_set_pos(ui_scr->video_rec_rec_submenu_btn_4, 83, 233);
    lv_obj_set_size(ui_scr->video_rec_rec_submenu_btn_4, 438, 37);
    lv_obj_set_scrollbar_mode(ui_scr->video_rec_rec_submenu_btn_4, LV_SCROLLBAR_MODE_OFF);
    lv_obj_add_flag(ui_scr->video_rec_rec_submenu_btn_4, LV_OBJ_FLAG_EVENT_BUBBLE);
    ui_style_set(ui_scr->video_rec_rec_submenu_btn_4, GUI_CTRL_BUTTON);

    //Set style for video_rec_rec_submenu_btn_4. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
    lv_obj_set_style_bg_opa(ui_scr->video_rec_rec_submenu_btn_4, 205, LV_PART_MAIN | LV_STATE_DEFAULT);
    ui_scr->video_rec_rec_submenu_btn_4_label = lv_label_create(ui_scr->video_rec_rec_submenu_btn_4);
    lv_label_set_text(ui_scr->video_rec_rec_submenu_btn_4_label, "button4");
    lv_obj_set_style_pad_all(ui_scr->video_rec_rec_submenu_btn_4, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_align(ui_scr->video_rec_rec_submenu_btn_4_label, LV_ALIGN_CENTER, 0, 0);

    //Write codes video_rec_roller_mutifunc
    ui_scr->video_rec_roller_mutifunc = lv_roller_create(ui_scr->video_rec_view_submenu);
    lv_obj_set_pos(ui_scr->video_rec_roller_mutifunc, 223, 55);
    lv_obj_set_size(ui_scr->video_rec_roller_mutifunc, 148, 214);
    lv_obj_set_scrollbar_mode(ui_scr->video_rec_roller_mutifunc, LV_SCROLLBAR_MODE_OFF);
    lv_obj_add_flag(ui_scr->video_rec_roller_mutifunc, LV_OBJ_FLAG_EVENT_BUBBLE);
    ui_style_set(ui_scr->video_rec_roller_mutifunc, GUI_CTRL_ROLLER);
    lv_roller_set_options(ui_scr->video_rec_roller_mutifunc, "1\n2\n3\n4\n5", LV_ROLLER_MODE_INFINITE);
    lv_roller_set_visible_row_count(ui_scr->video_rec_roller_mutifunc, 5);

    //Write codes video_rec_view_carnum
    ui_scr->video_rec_view_carnum = lv_obj_create(ui_scr->video_rec_view_submenu);
    lv_obj_set_pos(ui_scr->video_rec_view_carnum, 77, 42);
    lv_obj_set_size(ui_scr->video_rec_view_carnum, 450, 164);
    lv_obj_set_scrollbar_mode(ui_scr->video_rec_view_carnum, LV_SCROLLBAR_MODE_OFF);
    ui_style_set(ui_scr->video_rec_view_carnum, GUI_CTRL_CONT);

    //Delete extra default style for video_rec_view_carnum
    lv_obj_remove_style(ui_scr->video_rec_view_carnum, &gui_cont_main_focus_key_style, LV_PART_MAIN | LV_STATE_FOCUS_KEY);

    //Write codes video_rec_ddlist_1
    ui_scr->video_rec_ddlist_1 = lv_dropdown_create(ui_scr->video_rec_view_carnum);
    lv_dropdown_set_options(ui_scr->video_rec_ddlist_1, "京\n津\n晋\n冀\n蒙\n辽\n吉\n黑\n苏\n浙\n皖\n闽\n赣\n鲁\n豫\n鄂\n湘\n粤\n桂\n琼\n川\n贵\n滇\n渝\n藏\n陕\n甘\n青\n宁\n新\n台\n港\n澳");
    lv_dropdown_set_dir(ui_scr->video_rec_ddlist_1, LV_DIR_BOTTOM);
    lv_dropdown_set_symbol(ui_scr->video_rec_ddlist_1, LV_SYMBOL_DOWN);
    lv_dropdown_set_symbol(ui_scr->video_rec_ddlist_1, NULL);
    lv_dropdown_set_selected(ui_scr->video_rec_ddlist_1, 0);
    lv_obj_set_pos(ui_scr->video_rec_ddlist_1, 102, 38);
    lv_obj_set_size(ui_scr->video_rec_ddlist_1, 60, 31);
    lv_obj_set_scrollbar_mode(ui_scr->video_rec_ddlist_1, LV_SCROLLBAR_MODE_OFF);
    lv_obj_add_flag(ui_scr->video_rec_ddlist_1, LV_OBJ_FLAG_EVENT_BUBBLE);
    ui_style_set(ui_scr->video_rec_ddlist_1, GUI_CTRL_DROPDOWN);

    //Set style for video_rec_ddlist_1. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
    lv_obj_set_style_text_font(ui_scr->video_rec_ddlist_1, &lv_font_FangZhengKaiTiJianTi_1_18, LV_PART_MAIN | LV_STATE_DEFAULT);

    //Set style for video_rec_ddlist_1. Part: LV_PART_MAIN, State: LV_STATE_FOCUS_KEY
    lv_obj_set_style_text_font(ui_scr->video_rec_ddlist_1, &lv_font_FangZhengKaiTiJianTi_1_18, LV_PART_MAIN | LV_STATE_FOCUS_KEY);

    //Set style state: LV_STATE_CHECKED for style_video_rec_ddlist_1_extra_list_selected_checked
    static lv_style_t style_video_rec_ddlist_1_extra_list_selected_checked;
    ui_init_style(&style_video_rec_ddlist_1_extra_list_selected_checked);
    lv_style_set_text_font(&style_video_rec_ddlist_1_extra_list_selected_checked, &lv_font_FangZhengKaiTiJianTi_1_18);
    lv_obj_add_style(lv_dropdown_get_list(ui_scr->video_rec_ddlist_1), &gui_ddlist_selected_checked_style, LV_PART_SELECTED | LV_STATE_CHECKED);
    lv_obj_add_style(lv_dropdown_get_list(ui_scr->video_rec_ddlist_1), &style_video_rec_ddlist_1_extra_list_selected_checked, LV_PART_SELECTED | LV_STATE_CHECKED);

    //Set style state: LV_STATE_DEFAULT for style_video_rec_ddlist_1_extra_list_main_default
    static lv_style_t style_video_rec_ddlist_1_extra_list_main_default;
    ui_init_style(&style_video_rec_ddlist_1_extra_list_main_default);
    lv_style_set_text_font(&style_video_rec_ddlist_1_extra_list_main_default, &lv_font_FangZhengKaiTiJianTi_1_18);
    lv_obj_add_style(lv_dropdown_get_list(ui_scr->video_rec_ddlist_1), &gui_ddlist_dropdown_list_default_style, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_add_style(lv_dropdown_get_list(ui_scr->video_rec_ddlist_1), &style_video_rec_ddlist_1_extra_list_main_default, LV_PART_MAIN | LV_STATE_DEFAULT);

    //Set style state: LV_STATE_DEFAULT for style_video_rec_ddlist_1_extra_list_scrollbar_default
    static lv_style_t style_video_rec_ddlist_1_extra_list_scrollbar_default;
    ui_init_style(&style_video_rec_ddlist_1_extra_list_scrollbar_default);
    lv_obj_add_style(lv_dropdown_get_list(ui_scr->video_rec_ddlist_1), &gui_ddlist_scrollbar_default_style, LV_PART_SCROLLBAR | LV_STATE_DEFAULT);
    lv_obj_add_style(lv_dropdown_get_list(ui_scr->video_rec_ddlist_1), &style_video_rec_ddlist_1_extra_list_scrollbar_default, LV_PART_SCROLLBAR | LV_STATE_DEFAULT);

    //Delete extra default style for video_rec_ddlist_1
    lv_obj_remove_style(ui_scr->video_rec_ddlist_1, &gui_ddlist_selected_checked_style, LV_PART_SELECTED | LV_STATE_CHECKED);
    lv_obj_remove_style(ui_scr->video_rec_ddlist_1, &gui_ddlist_dropdown_list_default_style, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_remove_style(ui_scr->video_rec_ddlist_1, &gui_ddlist_scrollbar_default_style, LV_PART_SCROLLBAR | LV_STATE_DEFAULT);

    //Write codes video_rec_ddlist_2
    ui_scr->video_rec_ddlist_2 = lv_dropdown_create(ui_scr->video_rec_view_carnum);
    lv_dropdown_set_options(ui_scr->video_rec_ddlist_2, "A\nB\nC\nD\nE\nF\nG\nH\nI\nJ\nK\nL\nM\nN\nO\nP\nQ\nR\nS\nT\nU\nV\nW\nX\nY\nZ");
    lv_dropdown_set_dir(ui_scr->video_rec_ddlist_2, LV_DIR_BOTTOM);
    lv_dropdown_set_symbol(ui_scr->video_rec_ddlist_2, LV_SYMBOL_DOWN);
    lv_dropdown_set_symbol(ui_scr->video_rec_ddlist_2, NULL);
    lv_dropdown_set_selected(ui_scr->video_rec_ddlist_2, 0);
    lv_obj_set_pos(ui_scr->video_rec_ddlist_2, 288, 38);
    lv_obj_set_size(ui_scr->video_rec_ddlist_2, 60, 31);
    lv_obj_set_scrollbar_mode(ui_scr->video_rec_ddlist_2, LV_SCROLLBAR_MODE_OFF);
    lv_obj_add_flag(ui_scr->video_rec_ddlist_2, LV_OBJ_FLAG_EVENT_BUBBLE);
    ui_style_set(ui_scr->video_rec_ddlist_2, GUI_CTRL_DROPDOWN);

    //Set style state: LV_STATE_CHECKED for style_video_rec_ddlist_2_extra_list_selected_checked
    static lv_style_t style_video_rec_ddlist_2_extra_list_selected_checked;
    ui_init_style(&style_video_rec_ddlist_2_extra_list_selected_checked);
    lv_obj_add_style(lv_dropdown_get_list(ui_scr->video_rec_ddlist_2), &gui_ddlist_selected_checked_style, LV_PART_SELECTED | LV_STATE_CHECKED);
    lv_obj_add_style(lv_dropdown_get_list(ui_scr->video_rec_ddlist_2), &style_video_rec_ddlist_2_extra_list_selected_checked, LV_PART_SELECTED | LV_STATE_CHECKED);

    //Set style state: LV_STATE_DEFAULT for style_video_rec_ddlist_2_extra_list_main_default
    static lv_style_t style_video_rec_ddlist_2_extra_list_main_default;
    ui_init_style(&style_video_rec_ddlist_2_extra_list_main_default);
    lv_obj_add_style(lv_dropdown_get_list(ui_scr->video_rec_ddlist_2), &gui_ddlist_dropdown_list_default_style, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_add_style(lv_dropdown_get_list(ui_scr->video_rec_ddlist_2), &style_video_rec_ddlist_2_extra_list_main_default, LV_PART_MAIN | LV_STATE_DEFAULT);

    //Set style state: LV_STATE_DEFAULT for style_video_rec_ddlist_2_extra_list_scrollbar_default
    static lv_style_t style_video_rec_ddlist_2_extra_list_scrollbar_default;
    ui_init_style(&style_video_rec_ddlist_2_extra_list_scrollbar_default);
    lv_obj_add_style(lv_dropdown_get_list(ui_scr->video_rec_ddlist_2), &gui_ddlist_scrollbar_default_style, LV_PART_SCROLLBAR | LV_STATE_DEFAULT);
    lv_obj_add_style(lv_dropdown_get_list(ui_scr->video_rec_ddlist_2), &style_video_rec_ddlist_2_extra_list_scrollbar_default, LV_PART_SCROLLBAR | LV_STATE_DEFAULT);

    //Delete extra default style for video_rec_ddlist_2
    lv_obj_remove_style(ui_scr->video_rec_ddlist_2, &gui_ddlist_selected_checked_style, LV_PART_SELECTED | LV_STATE_CHECKED);
    lv_obj_remove_style(ui_scr->video_rec_ddlist_2, &gui_ddlist_dropdown_list_default_style, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_remove_style(ui_scr->video_rec_ddlist_2, &gui_ddlist_scrollbar_default_style, LV_PART_SCROLLBAR | LV_STATE_DEFAULT);

    //Write codes video_rec_ddlist_3
    ui_scr->video_rec_ddlist_3 = lv_dropdown_create(ui_scr->video_rec_view_carnum);
    lv_dropdown_set_options(ui_scr->video_rec_ddlist_3, "0\n1\n2\n3\n4\n5\n6\n7\n8\n9\nA\nB\nC\nD\nE\nF\nG\nH\nI\nJ\nK\nL\nM\nN\nO\nP\nQ\nR\nS\nT\nU\nV\nW\nX\nY\nZ");
    lv_dropdown_set_dir(ui_scr->video_rec_ddlist_3, LV_DIR_BOTTOM);
    lv_dropdown_set_symbol(ui_scr->video_rec_ddlist_3, LV_SYMBOL_DOWN);
    lv_dropdown_set_symbol(ui_scr->video_rec_ddlist_3, NULL);
    lv_dropdown_set_selected(ui_scr->video_rec_ddlist_3, 0);
    lv_obj_set_pos(ui_scr->video_rec_ddlist_3, 28, 102);
    lv_obj_set_size(ui_scr->video_rec_ddlist_3, 60, 31);
    lv_obj_set_scrollbar_mode(ui_scr->video_rec_ddlist_3, LV_SCROLLBAR_MODE_OFF);
    lv_obj_add_flag(ui_scr->video_rec_ddlist_3, LV_OBJ_FLAG_EVENT_BUBBLE);
    ui_style_set(ui_scr->video_rec_ddlist_3, GUI_CTRL_DROPDOWN);

    //Set style state: LV_STATE_CHECKED for style_video_rec_ddlist_3_extra_list_selected_checked
    static lv_style_t style_video_rec_ddlist_3_extra_list_selected_checked;
    ui_init_style(&style_video_rec_ddlist_3_extra_list_selected_checked);
    lv_obj_add_style(lv_dropdown_get_list(ui_scr->video_rec_ddlist_3), &gui_ddlist_selected_checked_style, LV_PART_SELECTED | LV_STATE_CHECKED);
    lv_obj_add_style(lv_dropdown_get_list(ui_scr->video_rec_ddlist_3), &style_video_rec_ddlist_3_extra_list_selected_checked, LV_PART_SELECTED | LV_STATE_CHECKED);

    //Set style state: LV_STATE_DEFAULT for style_video_rec_ddlist_3_extra_list_main_default
    static lv_style_t style_video_rec_ddlist_3_extra_list_main_default;
    ui_init_style(&style_video_rec_ddlist_3_extra_list_main_default);
    lv_obj_add_style(lv_dropdown_get_list(ui_scr->video_rec_ddlist_3), &gui_ddlist_dropdown_list_default_style, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_add_style(lv_dropdown_get_list(ui_scr->video_rec_ddlist_3), &style_video_rec_ddlist_3_extra_list_main_default, LV_PART_MAIN | LV_STATE_DEFAULT);

    //Set style state: LV_STATE_DEFAULT for style_video_rec_ddlist_3_extra_list_scrollbar_default
    static lv_style_t style_video_rec_ddlist_3_extra_list_scrollbar_default;
    ui_init_style(&style_video_rec_ddlist_3_extra_list_scrollbar_default);
    lv_obj_add_style(lv_dropdown_get_list(ui_scr->video_rec_ddlist_3), &gui_ddlist_scrollbar_default_style, LV_PART_SCROLLBAR | LV_STATE_DEFAULT);
    lv_obj_add_style(lv_dropdown_get_list(ui_scr->video_rec_ddlist_3), &style_video_rec_ddlist_3_extra_list_scrollbar_default, LV_PART_SCROLLBAR | LV_STATE_DEFAULT);

    //Delete extra default style for video_rec_ddlist_3
    lv_obj_remove_style(ui_scr->video_rec_ddlist_3, &gui_ddlist_selected_checked_style, LV_PART_SELECTED | LV_STATE_CHECKED);
    lv_obj_remove_style(ui_scr->video_rec_ddlist_3, &gui_ddlist_dropdown_list_default_style, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_remove_style(ui_scr->video_rec_ddlist_3, &gui_ddlist_scrollbar_default_style, LV_PART_SCROLLBAR | LV_STATE_DEFAULT);

    //Write codes video_rec_ddlist_4
    ui_scr->video_rec_ddlist_4 = lv_dropdown_create(ui_scr->video_rec_view_carnum);
    lv_dropdown_set_options(ui_scr->video_rec_ddlist_4, "0\n1\n2\n3\n4\n5\n6\n7\n8\n9\nA\nB\nC\nD\nE\nF\nG\nH\nI\nJ\nK\nL\nM\nN\nO\nP\nQ\nR\nS\nT\nU\nV\nW\nX\nY\nZ");
    lv_dropdown_set_dir(ui_scr->video_rec_ddlist_4, LV_DIR_BOTTOM);
    lv_dropdown_set_symbol(ui_scr->video_rec_ddlist_4, LV_SYMBOL_DOWN);
    lv_dropdown_set_symbol(ui_scr->video_rec_ddlist_4, NULL);
    lv_dropdown_set_selected(ui_scr->video_rec_ddlist_4, 0);
    lv_obj_set_pos(ui_scr->video_rec_ddlist_4, 111, 102);
    lv_obj_set_size(ui_scr->video_rec_ddlist_4, 60, 31);
    lv_obj_set_scrollbar_mode(ui_scr->video_rec_ddlist_4, LV_SCROLLBAR_MODE_OFF);
    lv_obj_add_flag(ui_scr->video_rec_ddlist_4, LV_OBJ_FLAG_EVENT_BUBBLE);
    ui_style_set(ui_scr->video_rec_ddlist_4, GUI_CTRL_DROPDOWN);

    //Set style state: LV_STATE_CHECKED for style_video_rec_ddlist_4_extra_list_selected_checked
    static lv_style_t style_video_rec_ddlist_4_extra_list_selected_checked;
    ui_init_style(&style_video_rec_ddlist_4_extra_list_selected_checked);
    lv_obj_add_style(lv_dropdown_get_list(ui_scr->video_rec_ddlist_4), &gui_ddlist_selected_checked_style, LV_PART_SELECTED | LV_STATE_CHECKED);
    lv_obj_add_style(lv_dropdown_get_list(ui_scr->video_rec_ddlist_4), &style_video_rec_ddlist_4_extra_list_selected_checked, LV_PART_SELECTED | LV_STATE_CHECKED);

    //Set style state: LV_STATE_DEFAULT for style_video_rec_ddlist_4_extra_list_main_default
    static lv_style_t style_video_rec_ddlist_4_extra_list_main_default;
    ui_init_style(&style_video_rec_ddlist_4_extra_list_main_default);
    lv_obj_add_style(lv_dropdown_get_list(ui_scr->video_rec_ddlist_4), &gui_ddlist_dropdown_list_default_style, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_add_style(lv_dropdown_get_list(ui_scr->video_rec_ddlist_4), &style_video_rec_ddlist_4_extra_list_main_default, LV_PART_MAIN | LV_STATE_DEFAULT);

    //Set style state: LV_STATE_DEFAULT for style_video_rec_ddlist_4_extra_list_scrollbar_default
    static lv_style_t style_video_rec_ddlist_4_extra_list_scrollbar_default;
    ui_init_style(&style_video_rec_ddlist_4_extra_list_scrollbar_default);
    lv_obj_add_style(lv_dropdown_get_list(ui_scr->video_rec_ddlist_4), &gui_ddlist_scrollbar_default_style, LV_PART_SCROLLBAR | LV_STATE_DEFAULT);
    lv_obj_add_style(lv_dropdown_get_list(ui_scr->video_rec_ddlist_4), &style_video_rec_ddlist_4_extra_list_scrollbar_default, LV_PART_SCROLLBAR | LV_STATE_DEFAULT);

    //Delete extra default style for video_rec_ddlist_4
    lv_obj_remove_style(ui_scr->video_rec_ddlist_4, &gui_ddlist_selected_checked_style, LV_PART_SELECTED | LV_STATE_CHECKED);
    lv_obj_remove_style(ui_scr->video_rec_ddlist_4, &gui_ddlist_dropdown_list_default_style, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_remove_style(ui_scr->video_rec_ddlist_4, &gui_ddlist_scrollbar_default_style, LV_PART_SCROLLBAR | LV_STATE_DEFAULT);

    //Write codes video_rec_ddlist_5
    ui_scr->video_rec_ddlist_5 = lv_dropdown_create(ui_scr->video_rec_view_carnum);
    lv_dropdown_set_options(ui_scr->video_rec_ddlist_5, "0\n1\n2\n3\n4\n5\n6\n7\n8\n9\nA\nB\nC\nD\nE\nF\nG\nH\nI\nJ\nK\nL\nM\nN\nO\nP\nQ\nR\nS\nT\nU\nV\nW\nX\nY\nZ");
    lv_dropdown_set_dir(ui_scr->video_rec_ddlist_5, LV_DIR_BOTTOM);
    lv_dropdown_set_symbol(ui_scr->video_rec_ddlist_5, LV_SYMBOL_DOWN);
    lv_dropdown_set_symbol(ui_scr->video_rec_ddlist_5, NULL);
    lv_dropdown_set_selected(ui_scr->video_rec_ddlist_5, 0);
    lv_obj_set_pos(ui_scr->video_rec_ddlist_5, 194, 102);
    lv_obj_set_size(ui_scr->video_rec_ddlist_5, 60, 31);
    lv_obj_set_scrollbar_mode(ui_scr->video_rec_ddlist_5, LV_SCROLLBAR_MODE_OFF);
    lv_obj_add_flag(ui_scr->video_rec_ddlist_5, LV_OBJ_FLAG_EVENT_BUBBLE);
    ui_style_set(ui_scr->video_rec_ddlist_5, GUI_CTRL_DROPDOWN);

    //Set style state: LV_STATE_CHECKED for style_video_rec_ddlist_5_extra_list_selected_checked
    static lv_style_t style_video_rec_ddlist_5_extra_list_selected_checked;
    ui_init_style(&style_video_rec_ddlist_5_extra_list_selected_checked);
    lv_obj_add_style(lv_dropdown_get_list(ui_scr->video_rec_ddlist_5), &gui_ddlist_selected_checked_style, LV_PART_SELECTED | LV_STATE_CHECKED);
    lv_obj_add_style(lv_dropdown_get_list(ui_scr->video_rec_ddlist_5), &style_video_rec_ddlist_5_extra_list_selected_checked, LV_PART_SELECTED | LV_STATE_CHECKED);

    //Set style state: LV_STATE_DEFAULT for style_video_rec_ddlist_5_extra_list_main_default
    static lv_style_t style_video_rec_ddlist_5_extra_list_main_default;
    ui_init_style(&style_video_rec_ddlist_5_extra_list_main_default);
    lv_obj_add_style(lv_dropdown_get_list(ui_scr->video_rec_ddlist_5), &gui_ddlist_dropdown_list_default_style, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_add_style(lv_dropdown_get_list(ui_scr->video_rec_ddlist_5), &style_video_rec_ddlist_5_extra_list_main_default, LV_PART_MAIN | LV_STATE_DEFAULT);

    //Set style state: LV_STATE_DEFAULT for style_video_rec_ddlist_5_extra_list_scrollbar_default
    static lv_style_t style_video_rec_ddlist_5_extra_list_scrollbar_default;
    ui_init_style(&style_video_rec_ddlist_5_extra_list_scrollbar_default);
    lv_obj_add_style(lv_dropdown_get_list(ui_scr->video_rec_ddlist_5), &gui_ddlist_scrollbar_default_style, LV_PART_SCROLLBAR | LV_STATE_DEFAULT);
    lv_obj_add_style(lv_dropdown_get_list(ui_scr->video_rec_ddlist_5), &style_video_rec_ddlist_5_extra_list_scrollbar_default, LV_PART_SCROLLBAR | LV_STATE_DEFAULT);

    //Delete extra default style for video_rec_ddlist_5
    lv_obj_remove_style(ui_scr->video_rec_ddlist_5, &gui_ddlist_selected_checked_style, LV_PART_SELECTED | LV_STATE_CHECKED);
    lv_obj_remove_style(ui_scr->video_rec_ddlist_5, &gui_ddlist_dropdown_list_default_style, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_remove_style(ui_scr->video_rec_ddlist_5, &gui_ddlist_scrollbar_default_style, LV_PART_SCROLLBAR | LV_STATE_DEFAULT);

    //Write codes video_rec_ddlist_6
    ui_scr->video_rec_ddlist_6 = lv_dropdown_create(ui_scr->video_rec_view_carnum);
    lv_dropdown_set_options(ui_scr->video_rec_ddlist_6, "0\n1\n2\n3\n4\n5\n6\n7\n8\n9\nA\nB\nC\nD\nE\nF\nG\nH\nI\nJ\nK\nL\nM\nN\nO\nP\nQ\nR\nS\nT\nU\nV\nW\nX\nY\nZ");
    lv_dropdown_set_dir(ui_scr->video_rec_ddlist_6, LV_DIR_BOTTOM);
    lv_dropdown_set_symbol(ui_scr->video_rec_ddlist_6, LV_SYMBOL_DOWN);
    lv_dropdown_set_symbol(ui_scr->video_rec_ddlist_6, NULL);
    lv_dropdown_set_selected(ui_scr->video_rec_ddlist_6, 0);
    lv_obj_set_pos(ui_scr->video_rec_ddlist_6, 277, 102);
    lv_obj_set_size(ui_scr->video_rec_ddlist_6, 60, 31);
    lv_obj_set_scrollbar_mode(ui_scr->video_rec_ddlist_6, LV_SCROLLBAR_MODE_OFF);
    lv_obj_add_flag(ui_scr->video_rec_ddlist_6, LV_OBJ_FLAG_EVENT_BUBBLE);
    ui_style_set(ui_scr->video_rec_ddlist_6, GUI_CTRL_DROPDOWN);

    //Set style state: LV_STATE_CHECKED for style_video_rec_ddlist_6_extra_list_selected_checked
    static lv_style_t style_video_rec_ddlist_6_extra_list_selected_checked;
    ui_init_style(&style_video_rec_ddlist_6_extra_list_selected_checked);
    lv_obj_add_style(lv_dropdown_get_list(ui_scr->video_rec_ddlist_6), &gui_ddlist_selected_checked_style, LV_PART_SELECTED | LV_STATE_CHECKED);
    lv_obj_add_style(lv_dropdown_get_list(ui_scr->video_rec_ddlist_6), &style_video_rec_ddlist_6_extra_list_selected_checked, LV_PART_SELECTED | LV_STATE_CHECKED);

    //Set style state: LV_STATE_DEFAULT for style_video_rec_ddlist_6_extra_list_main_default
    static lv_style_t style_video_rec_ddlist_6_extra_list_main_default;
    ui_init_style(&style_video_rec_ddlist_6_extra_list_main_default);
    lv_obj_add_style(lv_dropdown_get_list(ui_scr->video_rec_ddlist_6), &gui_ddlist_dropdown_list_default_style, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_add_style(lv_dropdown_get_list(ui_scr->video_rec_ddlist_6), &style_video_rec_ddlist_6_extra_list_main_default, LV_PART_MAIN | LV_STATE_DEFAULT);

    //Set style state: LV_STATE_DEFAULT for style_video_rec_ddlist_6_extra_list_scrollbar_default
    static lv_style_t style_video_rec_ddlist_6_extra_list_scrollbar_default;
    ui_init_style(&style_video_rec_ddlist_6_extra_list_scrollbar_default);
    lv_obj_add_style(lv_dropdown_get_list(ui_scr->video_rec_ddlist_6), &gui_ddlist_scrollbar_default_style, LV_PART_SCROLLBAR | LV_STATE_DEFAULT);
    lv_obj_add_style(lv_dropdown_get_list(ui_scr->video_rec_ddlist_6), &style_video_rec_ddlist_6_extra_list_scrollbar_default, LV_PART_SCROLLBAR | LV_STATE_DEFAULT);

    //Delete extra default style for video_rec_ddlist_6
    lv_obj_remove_style(ui_scr->video_rec_ddlist_6, &gui_ddlist_selected_checked_style, LV_PART_SELECTED | LV_STATE_CHECKED);
    lv_obj_remove_style(ui_scr->video_rec_ddlist_6, &gui_ddlist_dropdown_list_default_style, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_remove_style(ui_scr->video_rec_ddlist_6, &gui_ddlist_scrollbar_default_style, LV_PART_SCROLLBAR | LV_STATE_DEFAULT);

    //Write codes video_rec_ddlist_7
    ui_scr->video_rec_ddlist_7 = lv_dropdown_create(ui_scr->video_rec_view_carnum);
    lv_dropdown_set_options(ui_scr->video_rec_ddlist_7, "0\n1\n2\n3\n4\n5\n6\n7\n8\n9\nA\nB\nC\nD\nE\nF\nG\nH\nI\nJ\nK\nL\nM\nN\nO\nP\nQ\nR\nS\nT\nU\nV\nW\nX\nY\nZ");
    lv_dropdown_set_dir(ui_scr->video_rec_ddlist_7, LV_DIR_BOTTOM);
    lv_dropdown_set_symbol(ui_scr->video_rec_ddlist_7, LV_SYMBOL_DOWN);
    lv_dropdown_set_symbol(ui_scr->video_rec_ddlist_7, NULL);
    lv_dropdown_set_selected(ui_scr->video_rec_ddlist_7, 0);
    lv_obj_set_pos(ui_scr->video_rec_ddlist_7, 361, 102);
    lv_obj_set_size(ui_scr->video_rec_ddlist_7, 60, 31);
    lv_obj_set_scrollbar_mode(ui_scr->video_rec_ddlist_7, LV_SCROLLBAR_MODE_OFF);
    lv_obj_add_flag(ui_scr->video_rec_ddlist_7, LV_OBJ_FLAG_EVENT_BUBBLE);
    ui_style_set(ui_scr->video_rec_ddlist_7, GUI_CTRL_DROPDOWN);

    //Set style state: LV_STATE_CHECKED for style_video_rec_ddlist_7_extra_list_selected_checked
    static lv_style_t style_video_rec_ddlist_7_extra_list_selected_checked;
    ui_init_style(&style_video_rec_ddlist_7_extra_list_selected_checked);
    lv_obj_add_style(lv_dropdown_get_list(ui_scr->video_rec_ddlist_7), &gui_ddlist_selected_checked_style, LV_PART_SELECTED | LV_STATE_CHECKED);
    lv_obj_add_style(lv_dropdown_get_list(ui_scr->video_rec_ddlist_7), &style_video_rec_ddlist_7_extra_list_selected_checked, LV_PART_SELECTED | LV_STATE_CHECKED);

    //Set style state: LV_STATE_DEFAULT for style_video_rec_ddlist_7_extra_list_main_default
    static lv_style_t style_video_rec_ddlist_7_extra_list_main_default;
    ui_init_style(&style_video_rec_ddlist_7_extra_list_main_default);
    lv_obj_add_style(lv_dropdown_get_list(ui_scr->video_rec_ddlist_7), &gui_ddlist_dropdown_list_default_style, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_add_style(lv_dropdown_get_list(ui_scr->video_rec_ddlist_7), &style_video_rec_ddlist_7_extra_list_main_default, LV_PART_MAIN | LV_STATE_DEFAULT);

    //Set style state: LV_STATE_DEFAULT for style_video_rec_ddlist_7_extra_list_scrollbar_default
    static lv_style_t style_video_rec_ddlist_7_extra_list_scrollbar_default;
    ui_init_style(&style_video_rec_ddlist_7_extra_list_scrollbar_default);
    lv_obj_add_style(lv_dropdown_get_list(ui_scr->video_rec_ddlist_7), &gui_ddlist_scrollbar_default_style, LV_PART_SCROLLBAR | LV_STATE_DEFAULT);
    lv_obj_add_style(lv_dropdown_get_list(ui_scr->video_rec_ddlist_7), &style_video_rec_ddlist_7_extra_list_scrollbar_default, LV_PART_SCROLLBAR | LV_STATE_DEFAULT);

    //Delete extra default style for video_rec_ddlist_7
    lv_obj_remove_style(ui_scr->video_rec_ddlist_7, &gui_ddlist_selected_checked_style, LV_PART_SELECTED | LV_STATE_CHECKED);
    lv_obj_remove_style(ui_scr->video_rec_ddlist_7, &gui_ddlist_dropdown_list_default_style, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_remove_style(ui_scr->video_rec_ddlist_7, &gui_ddlist_scrollbar_default_style, LV_PART_SCROLLBAR | LV_STATE_DEFAULT);

    lv_obj_update_layout(ui_scr->video_rec);
    ui_scr->video_rec_del = false;
    i18n_refresh_texts(GUI_SCREEN_VIDEO_REC);

    //Init events for screen
    events_init_video_rec(ui);
    return ui_scr->video_rec;
}
void unload_scr_video_rec(lv_ui *ui)
{
    ui_free_scr_ptr(ui, GUI_SCREEN_VIDEO_REC);
}

#endif
