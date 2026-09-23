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


lv_obj_t *setup_scr_video_photo(lv_ui *ui)
{
    lv_ui_video_photo *ui_scr = ui_get_scr_ptr(ui, GUI_SCREEN_VIDEO_PHOTO);
    if (ui_scr == NULL) {
        ui_scr = lv_mem_alloc(sizeof(lv_ui_video_photo));
        if (ui_scr == NULL) {
            return NULL;
        }
        memset(ui_scr, 0, sizeof(lv_ui_video_photo));
        ui->video_photo = ui_scr;
    }

    //Write codes video_photo
    ui_scr->video_photo = lv_obj_create(NULL);
    lv_group_t *def_group = lv_group_get_default();
    lv_obj_set_scrollbar_mode(ui_scr->video_photo, LV_SCROLLBAR_MODE_OFF);
    ui_style_set(ui_scr->video_photo, GUI_CTRL_SCR);

    //Set style for video_photo. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
    lv_obj_set_style_bg_color(ui_scr->video_photo, lv_color_make(0x55, 0xaa, 0xa5), LV_PART_MAIN | LV_STATE_DEFAULT);

    //Write codes video_photo_view_scan
    ui_scr->video_photo_view_scan = lv_obj_create(ui_scr->video_photo);
    lv_obj_set_pos(ui_scr->video_photo_view_scan, 0, 0);
    lv_obj_set_size(ui_scr->video_photo_view_scan, 800, 480);
    lv_obj_set_scrollbar_mode(ui_scr->video_photo_view_scan, LV_SCROLLBAR_MODE_OFF);
    lv_group_add_obj(def_group, ui_scr->video_photo_view_scan);
    ui_style_set(ui_scr->video_photo_view_scan, GUI_CTRL_CONT);

    //Delete extra default style for video_photo_view_scan
    lv_obj_remove_style(ui_scr->video_photo_view_scan, &gui_cont_main_focus_key_style, LV_PART_MAIN | LV_STATE_FOCUS_KEY);

    //Write codes video_photo_img_taking_photo
    ui_scr->video_photo_img_taking_photo = lv_img_create(ui_scr->video_photo_view_scan);
    lv_img_set_src(ui_scr->video_photo_img_taking_photo, gui_get_res_path(GUI_RES_TP_3_PNG));
    lv_img_set_pivot(ui_scr->video_photo_img_taking_photo, 0, 0);
    lv_img_set_angle(ui_scr->video_photo_img_taking_photo, 0);
    lv_img_set_zoom(ui_scr->video_photo_img_taking_photo, 256);
    lv_obj_set_pos(ui_scr->video_photo_img_taking_photo, 12, 10);
    lv_obj_set_size(ui_scr->video_photo_img_taking_photo, 29, 29);
    lv_obj_add_flag(ui_scr->video_photo_img_taking_photo, LV_OBJ_FLAG_HIDDEN);
    lv_obj_add_state(ui_scr->video_photo_img_taking_photo, LV_STATE_FOCUS_KEY);
    lv_obj_add_flag(ui_scr->video_photo_img_taking_photo, LV_OBJ_FLAG_CLICKABLE);
    ui_style_set(ui_scr->video_photo_img_taking_photo, GUI_CTRL_IMG);

    //Write codes video_photo_img_photo_icon
    ui_scr->video_photo_img_photo_icon = lv_img_create(ui_scr->video_photo_view_scan);
    lv_img_set_src(ui_scr->video_photo_img_photo_icon, gui_get_res_path(GUI_RES_TP_PNG));
    lv_img_set_pivot(ui_scr->video_photo_img_photo_icon, 0, 0);
    lv_img_set_angle(ui_scr->video_photo_img_photo_icon, 0);
    lv_img_set_zoom(ui_scr->video_photo_img_photo_icon, 256);
    lv_obj_set_pos(ui_scr->video_photo_img_photo_icon, 12, 10);
    lv_obj_set_size(ui_scr->video_photo_img_photo_icon, 29, 29);
    lv_obj_add_state(ui_scr->video_photo_img_photo_icon, LV_STATE_FOCUS_KEY);
    lv_obj_add_flag(ui_scr->video_photo_img_photo_icon, LV_OBJ_FLAG_CLICKABLE);
    ui_style_set(ui_scr->video_photo_img_photo_icon, GUI_CTRL_IMG);

    //Write codes video_photo_img_exp_icon
    ui_scr->video_photo_img_exp_icon = lv_img_create(ui_scr->video_photo_view_scan);
    lv_img_set_src(ui_scr->video_photo_img_exp_icon, gui_get_res_path(GUI_RES_EXP_A0_PNG));
    lv_img_set_pivot(ui_scr->video_photo_img_exp_icon, 0, 0);
    lv_img_set_angle(ui_scr->video_photo_img_exp_icon, 0);
    lv_img_set_zoom(ui_scr->video_photo_img_exp_icon, 256);
    lv_obj_set_pos(ui_scr->video_photo_img_exp_icon, 12, 54);
    lv_obj_set_size(ui_scr->video_photo_img_exp_icon, 29, 29);
    lv_obj_add_flag(ui_scr->video_photo_img_exp_icon, LV_OBJ_FLAG_CLICKABLE);
    ui_style_set(ui_scr->video_photo_img_exp_icon, GUI_CTRL_IMG);

    //Write codes video_photo_img_awb_icon
    ui_scr->video_photo_img_awb_icon = lv_img_create(ui_scr->video_photo_view_scan);
    lv_img_set_src(ui_scr->video_photo_img_awb_icon, gui_get_res_path(GUI_RES_AWB_AUTO_PNG));
    lv_img_set_pivot(ui_scr->video_photo_img_awb_icon, 0, 0);
    lv_img_set_angle(ui_scr->video_photo_img_awb_icon, 0);
    lv_img_set_zoom(ui_scr->video_photo_img_awb_icon, 256);
    lv_obj_set_pos(ui_scr->video_photo_img_awb_icon, 12, 98);
    lv_obj_set_size(ui_scr->video_photo_img_awb_icon, 29, 29);
    lv_obj_add_flag(ui_scr->video_photo_img_awb_icon, LV_OBJ_FLAG_CLICKABLE);
    ui_style_set(ui_scr->video_photo_img_awb_icon, GUI_CTRL_IMG);

    //Write codes video_photo_img_iso_icon
    ui_scr->video_photo_img_iso_icon = lv_img_create(ui_scr->video_photo_view_scan);
    lv_img_set_src(ui_scr->video_photo_img_iso_icon, gui_get_res_path(GUI_RES_ISO_AUTO_PNG));
    lv_img_set_pivot(ui_scr->video_photo_img_iso_icon, 0, 0);
    lv_img_set_angle(ui_scr->video_photo_img_iso_icon, 0);
    lv_img_set_zoom(ui_scr->video_photo_img_iso_icon, 256);
    lv_obj_set_pos(ui_scr->video_photo_img_iso_icon, 12, 144);
    lv_obj_set_size(ui_scr->video_photo_img_iso_icon, 29, 29);
    lv_obj_add_flag(ui_scr->video_photo_img_iso_icon, LV_OBJ_FLAG_CLICKABLE);
    ui_style_set(ui_scr->video_photo_img_iso_icon, GUI_CTRL_IMG);

    //Write codes video_photo_img_qua_icon
    ui_scr->video_photo_img_qua_icon = lv_img_create(ui_scr->video_photo_view_scan);
    lv_img_set_src(ui_scr->video_photo_img_qua_icon, gui_get_res_path(GUI_RES_Q1_PNG));
    lv_img_set_pivot(ui_scr->video_photo_img_qua_icon, 0, 0);
    lv_img_set_angle(ui_scr->video_photo_img_qua_icon, 0);
    lv_img_set_zoom(ui_scr->video_photo_img_qua_icon, 256);
    lv_obj_set_pos(ui_scr->video_photo_img_qua_icon, 12, 192);
    lv_obj_set_size(ui_scr->video_photo_img_qua_icon, 29, 29);
    lv_obj_add_flag(ui_scr->video_photo_img_qua_icon, LV_OBJ_FLAG_CLICKABLE);
    ui_style_set(ui_scr->video_photo_img_qua_icon, GUI_CTRL_IMG);

    //Write codes video_photo_img_delay_icon
    ui_scr->video_photo_img_delay_icon = lv_img_create(ui_scr->video_photo_view_scan);
    lv_img_set_src(ui_scr->video_photo_img_delay_icon, gui_get_res_path(GUI_RES_DL2_PNG));
    lv_img_set_pivot(ui_scr->video_photo_img_delay_icon, 0, 0);
    lv_img_set_angle(ui_scr->video_photo_img_delay_icon, 0);
    lv_img_set_zoom(ui_scr->video_photo_img_delay_icon, 256);
    lv_obj_set_pos(ui_scr->video_photo_img_delay_icon, 97, 10);
    lv_obj_set_size(ui_scr->video_photo_img_delay_icon, 29, 29);
    lv_obj_add_flag(ui_scr->video_photo_img_delay_icon, LV_OBJ_FLAG_CLICKABLE);
    ui_style_set(ui_scr->video_photo_img_delay_icon, GUI_CTRL_IMG);

    //Write codes video_photo_img_shake_icon
    ui_scr->video_photo_img_shake_icon = lv_img_create(ui_scr->video_photo_view_scan);
    lv_img_set_src(ui_scr->video_photo_img_shake_icon, gui_get_res_path(GUI_RES_SHAKE_OFF_PNG));
    lv_img_set_pivot(ui_scr->video_photo_img_shake_icon, 0, 0);
    lv_img_set_angle(ui_scr->video_photo_img_shake_icon, 0);
    lv_img_set_zoom(ui_scr->video_photo_img_shake_icon, 256);
    lv_obj_set_pos(ui_scr->video_photo_img_shake_icon, 146, 10);
    lv_obj_set_size(ui_scr->video_photo_img_shake_icon, 29, 29);
    lv_obj_add_flag(ui_scr->video_photo_img_shake_icon, LV_OBJ_FLAG_CLICKABLE);
    ui_style_set(ui_scr->video_photo_img_shake_icon, GUI_CTRL_IMG);

    //Write codes video_photo_img_repeat_icon
    ui_scr->video_photo_img_repeat_icon = lv_img_create(ui_scr->video_photo_view_scan);
    lv_img_set_src(ui_scr->video_photo_img_repeat_icon, gui_get_res_path(GUI_RES_LIANP_PNG));
    lv_img_set_pivot(ui_scr->video_photo_img_repeat_icon, 0, 0);
    lv_img_set_angle(ui_scr->video_photo_img_repeat_icon, 0);
    lv_img_set_zoom(ui_scr->video_photo_img_repeat_icon, 256);
    lv_obj_set_pos(ui_scr->video_photo_img_repeat_icon, 200, 10);
    lv_obj_set_size(ui_scr->video_photo_img_repeat_icon, 29, 29);
    lv_obj_add_flag(ui_scr->video_photo_img_repeat_icon, LV_OBJ_FLAG_CLICKABLE);
    ui_style_set(ui_scr->video_photo_img_repeat_icon, GUI_CTRL_IMG);

    //Write codes video_photo_img_sd_icon
    ui_scr->video_photo_img_sd_icon = lv_img_create(ui_scr->video_photo_view_scan);
    lv_img_set_src(ui_scr->video_photo_img_sd_icon, gui_get_res_path(GUI_RES_CARD_ONLINE_PNG));
    lv_img_set_pivot(ui_scr->video_photo_img_sd_icon, 0, 0);
    lv_img_set_angle(ui_scr->video_photo_img_sd_icon, 0);
    lv_img_set_zoom(ui_scr->video_photo_img_sd_icon, 256);
    lv_obj_set_pos(ui_scr->video_photo_img_sd_icon, 758, 410);
    lv_obj_set_size(ui_scr->video_photo_img_sd_icon, 29, 29);
    lv_obj_add_flag(ui_scr->video_photo_img_sd_icon, LV_OBJ_FLAG_CLICKABLE);
    ui_style_set(ui_scr->video_photo_img_sd_icon, GUI_CTRL_IMG);

    //Write codes video_photo_img_bat_icon
    ui_scr->video_photo_img_bat_icon = lv_img_create(ui_scr->video_photo_view_scan);
    lv_img_set_src(ui_scr->video_photo_img_bat_icon, gui_get_res_path(GUI_RES_BAT_FULL_PNG));
    lv_img_set_pivot(ui_scr->video_photo_img_bat_icon, 0, 0);
    lv_img_set_angle(ui_scr->video_photo_img_bat_icon, 0);
    lv_img_set_zoom(ui_scr->video_photo_img_bat_icon, 256);
    lv_obj_set_pos(ui_scr->video_photo_img_bat_icon, 762, 454);
    lv_obj_set_size(ui_scr->video_photo_img_bat_icon, 25, 15);
    lv_obj_add_flag(ui_scr->video_photo_img_bat_icon, LV_OBJ_FLAG_CLICKABLE);
    ui_style_set(ui_scr->video_photo_img_bat_icon, GUI_CTRL_IMG);

    //Write codes video_photo_lbl_photo_reso
    ui_scr->video_photo_lbl_photo_reso = lv_label_create(ui_scr->video_photo_view_scan);
    lv_label_set_text(ui_scr->video_photo_lbl_photo_reso, "1M");
    lv_label_set_long_mode(ui_scr->video_photo_lbl_photo_reso, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui_scr->video_photo_lbl_photo_reso, 701, 10);
    lv_obj_set_size(ui_scr->video_photo_lbl_photo_reso, 70, 35);
    lv_obj_set_scrollbar_mode(ui_scr->video_photo_lbl_photo_reso, LV_SCROLLBAR_MODE_OFF);
    ui_style_set(ui_scr->video_photo_lbl_photo_reso, GUI_CTRL_LABEL);

    //Set style for video_photo_lbl_photo_reso. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
    lv_obj_set_style_text_font(ui_scr->video_photo_lbl_photo_reso, &lv_font_FangZhengKaiTiJianTi_1_26, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui_scr->video_photo_lbl_photo_reso, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);

    //Write codes video_photo_lbl_remain_pnum
    ui_scr->video_photo_lbl_remain_pnum = lv_label_create(ui_scr->video_photo_view_scan);
    lv_label_set_text(ui_scr->video_photo_lbl_remain_pnum, "99999");
    lv_label_set_long_mode(ui_scr->video_photo_lbl_remain_pnum, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui_scr->video_photo_lbl_remain_pnum, 687, 42);
    lv_obj_set_size(ui_scr->video_photo_lbl_remain_pnum, 100, 35);
    lv_obj_set_scrollbar_mode(ui_scr->video_photo_lbl_remain_pnum, LV_SCROLLBAR_MODE_OFF);
    ui_style_set(ui_scr->video_photo_lbl_remain_pnum, GUI_CTRL_LABEL);

    //Set style for video_photo_lbl_remain_pnum. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
    lv_obj_set_style_text_font(ui_scr->video_photo_lbl_remain_pnum, &lv_font_FangZhengKaiTiJianTi_1_26, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui_scr->video_photo_lbl_remain_pnum, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);

    //Write codes video_photo_digitclock_1
    ui_scr->video_photo_digitclock_1 = lv_label_create(ui_scr->video_photo_view_scan);
    lv_label_set_text_fmt(ui_scr->video_photo_digitclock_1, "%04d-%02d-%02d %02d:%02d:%02d", 2022, 07, 28, 21 % 12, 25, 50);
    lv_obj_set_style_text_align(ui_scr->video_photo_digitclock_1, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_pos(ui_scr->video_photo_digitclock_1, 20, 439);
    lv_obj_set_size(ui_scr->video_photo_digitclock_1, 300, 35);
    ui_style_set(ui_scr->video_photo_digitclock_1, GUI_CTRL_DIGITALCLOCK);

    //Delete extra default style for video_photo_digitclock_1
    lv_obj_remove_style(ui_scr->video_photo_digitclock_1, &gui_digitclock_main_disabled_style, LV_PART_MAIN | LV_STATE_DISABLED);

    //Write codes video_photo_view_menu_b
    ui_scr->video_photo_view_menu_b = lv_obj_create(ui_scr->video_photo);
    lv_obj_set_pos(ui_scr->video_photo_view_menu_b, 0, 0);
    lv_obj_set_size(ui_scr->video_photo_view_menu_b, 800, 480);
    lv_obj_set_scrollbar_mode(ui_scr->video_photo_view_menu_b, LV_SCROLLBAR_MODE_OFF);
    lv_obj_add_flag(ui_scr->video_photo_view_menu_b, LV_OBJ_FLAG_HIDDEN);
    ui_style_set(ui_scr->video_photo_view_menu_b, GUI_CTRL_CONT);

    //Set style for video_photo_view_menu_b. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
    lv_obj_set_style_border_opa(ui_scr->video_photo_view_menu_b, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

    //Delete extra default style for video_photo_view_menu_b
    lv_obj_remove_style(ui_scr->video_photo_view_menu_b, &gui_cont_main_focus_key_style, LV_PART_MAIN | LV_STATE_FOCUS_KEY);

    //Write codes video_photo_view_menu
    ui_scr->video_photo_view_menu = lv_obj_create(ui_scr->video_photo_view_menu_b);
    lv_obj_set_pos(ui_scr->video_photo_view_menu, 0, 40);
    lv_obj_set_size(ui_scr->video_photo_view_menu, 800, 400);
    lv_obj_set_scrollbar_mode(ui_scr->video_photo_view_menu, LV_SCROLLBAR_MODE_OFF);
    ui_style_set(ui_scr->video_photo_view_menu, GUI_CTRL_CONT);

    //Set style for video_photo_view_menu. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
    lv_obj_set_style_bg_color(ui_scr->video_photo_view_menu, lv_color_make(0x61, 0x61, 0x61), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_scr->video_photo_view_menu, 205, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui_scr->video_photo_view_menu, lv_color_make(0x21, 0x95, 0xF6), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui_scr->video_photo_view_menu, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_outline_color(ui_scr->video_photo_view_menu, lv_color_make(0x21, 0x95, 0xF6), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_outline_opa(ui_scr->video_photo_view_menu, 91, LV_PART_MAIN | LV_STATE_DEFAULT);

    //Delete extra default style for video_photo_view_menu
    lv_obj_remove_style(ui_scr->video_photo_view_menu, &gui_cont_main_focus_key_style, LV_PART_MAIN | LV_STATE_FOCUS_KEY);

    //Write codes video_photo_view_phm
    ui_scr->video_photo_view_phm = lv_obj_create(ui_scr->video_photo_view_menu);
    lv_obj_set_pos(ui_scr->video_photo_view_phm, 0, 0);
    lv_obj_set_size(ui_scr->video_photo_view_phm, 800, 43);
    lv_obj_set_scrollbar_mode(ui_scr->video_photo_view_phm, LV_SCROLLBAR_MODE_OFF);
    lv_obj_add_flag(ui_scr->video_photo_view_phm, LV_OBJ_FLAG_EVENT_BUBBLE | LV_OBJ_FLAG_SCROLL_ON_FOCUS);
    lv_group_add_obj(def_group, ui_scr->video_photo_view_phm);
    ui_style_set(ui_scr->video_photo_view_phm, GUI_CTRL_CONT);

    //Write codes video_photo_img_1
    ui_scr->video_photo_img_1 = lv_img_create(ui_scr->video_photo_view_phm);
    lv_img_set_src(ui_scr->video_photo_img_1, gui_get_res_path(GUI_RES_PAIZ_PNG));
    lv_img_set_pivot(ui_scr->video_photo_img_1, 0, 0);
    lv_img_set_angle(ui_scr->video_photo_img_1, 0);
    lv_img_set_zoom(ui_scr->video_photo_img_1, 256);
    lv_obj_set_pos(ui_scr->video_photo_img_1, 8, 6);
    lv_obj_set_size(ui_scr->video_photo_img_1, 29, 29);
    lv_obj_add_flag(ui_scr->video_photo_img_1, LV_OBJ_FLAG_CLICKABLE);
    ui_style_set(ui_scr->video_photo_img_1, GUI_CTRL_IMG);

    //Set style for video_photo_img_1. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
    lv_obj_set_style_bg_color(ui_scr->video_photo_img_1, lv_color_make(0xFF, 0xFF, 0xFF), LV_PART_MAIN | LV_STATE_DEFAULT);

    //Write codes video_photo_lbl_1
    ui_scr->video_photo_lbl_1 = lv_label_create(ui_scr->video_photo_view_phm);
    lv_label_set_long_mode(ui_scr->video_photo_lbl_1, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui_scr->video_photo_lbl_1, 50, 6);
    lv_obj_set_size(ui_scr->video_photo_lbl_1, 200, 32);
    lv_obj_set_scrollbar_mode(ui_scr->video_photo_lbl_1, LV_SCROLLBAR_MODE_OFF);
    ui_style_set(ui_scr->video_photo_lbl_1, GUI_CTRL_LABEL);

    //Write codes video_photo_view_reso
    ui_scr->video_photo_view_reso = lv_obj_create(ui_scr->video_photo_view_menu);
    lv_obj_set_pos(ui_scr->video_photo_view_reso, 0, 45);
    lv_obj_set_size(ui_scr->video_photo_view_reso, 800, 43);
    lv_obj_set_scrollbar_mode(ui_scr->video_photo_view_reso, LV_SCROLLBAR_MODE_OFF);
    lv_obj_add_flag(ui_scr->video_photo_view_reso, LV_OBJ_FLAG_EVENT_BUBBLE | LV_OBJ_FLAG_SCROLL_ON_FOCUS);
    lv_group_add_obj(def_group, ui_scr->video_photo_view_reso);
    ui_style_set(ui_scr->video_photo_view_reso, GUI_CTRL_CONT);

    //Write codes video_photo_img_2
    ui_scr->video_photo_img_2 = lv_img_create(ui_scr->video_photo_view_reso);
    lv_img_set_src(ui_scr->video_photo_img_2, gui_get_res_path(GUI_RES_M_SOLU_PNG));
    lv_img_set_pivot(ui_scr->video_photo_img_2, 0, 0);
    lv_img_set_angle(ui_scr->video_photo_img_2, 0);
    lv_img_set_zoom(ui_scr->video_photo_img_2, 256);
    lv_obj_set_pos(ui_scr->video_photo_img_2, 8, 6);
    lv_obj_set_size(ui_scr->video_photo_img_2, 29, 29);
    lv_obj_add_flag(ui_scr->video_photo_img_2, LV_OBJ_FLAG_CLICKABLE);
    ui_style_set(ui_scr->video_photo_img_2, GUI_CTRL_IMG);

    //Set style for video_photo_img_2. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
    lv_obj_set_style_bg_color(ui_scr->video_photo_img_2, lv_color_make(0xFF, 0xFF, 0xFF), LV_PART_MAIN | LV_STATE_DEFAULT);

    //Write codes video_photo_lbl_2
    ui_scr->video_photo_lbl_2 = lv_label_create(ui_scr->video_photo_view_reso);
    lv_label_set_long_mode(ui_scr->video_photo_lbl_2, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui_scr->video_photo_lbl_2, 50, 6);
    lv_obj_set_size(ui_scr->video_photo_lbl_2, 200, 32);
    lv_obj_set_scrollbar_mode(ui_scr->video_photo_lbl_2, LV_SCROLLBAR_MODE_OFF);
    ui_style_set(ui_scr->video_photo_lbl_2, GUI_CTRL_LABEL);

    //Write codes video_photo_view_cyt
    ui_scr->video_photo_view_cyt = lv_obj_create(ui_scr->video_photo_view_menu);
    lv_obj_set_pos(ui_scr->video_photo_view_cyt, 0, 90);
    lv_obj_set_size(ui_scr->video_photo_view_cyt, 800, 43);
    lv_obj_set_scrollbar_mode(ui_scr->video_photo_view_cyt, LV_SCROLLBAR_MODE_OFF);
    lv_obj_add_flag(ui_scr->video_photo_view_cyt, LV_OBJ_FLAG_EVENT_BUBBLE | LV_OBJ_FLAG_SCROLL_ON_FOCUS);
    lv_group_add_obj(def_group, ui_scr->video_photo_view_cyt);
    ui_style_set(ui_scr->video_photo_view_cyt, GUI_CTRL_CONT);

    //Write codes video_photo_img_3
    ui_scr->video_photo_img_3 = lv_img_create(ui_scr->video_photo_view_cyt);
    lv_img_set_src(ui_scr->video_photo_img_3, gui_get_res_path(GUI_RES_LIANP_1_PNG));
    lv_img_set_pivot(ui_scr->video_photo_img_3, 0, 0);
    lv_img_set_angle(ui_scr->video_photo_img_3, 0);
    lv_img_set_zoom(ui_scr->video_photo_img_3, 256);
    lv_obj_set_pos(ui_scr->video_photo_img_3, 8, 6);
    lv_obj_set_size(ui_scr->video_photo_img_3, 29, 29);
    lv_obj_add_flag(ui_scr->video_photo_img_3, LV_OBJ_FLAG_CLICKABLE);
    ui_style_set(ui_scr->video_photo_img_3, GUI_CTRL_IMG);

    //Set style for video_photo_img_3. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
    lv_obj_set_style_bg_color(ui_scr->video_photo_img_3, lv_color_make(0xFF, 0xFF, 0xFF), LV_PART_MAIN | LV_STATE_DEFAULT);

    //Write codes video_photo_lbl_3
    ui_scr->video_photo_lbl_3 = lv_label_create(ui_scr->video_photo_view_cyt);
    lv_label_set_long_mode(ui_scr->video_photo_lbl_3, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui_scr->video_photo_lbl_3, 50, 6);
    lv_obj_set_size(ui_scr->video_photo_lbl_3, 200, 32);
    lv_obj_set_scrollbar_mode(ui_scr->video_photo_lbl_3, LV_SCROLLBAR_MODE_OFF);
    ui_style_set(ui_scr->video_photo_lbl_3, GUI_CTRL_LABEL);

    //Write codes video_photo_view_qua
    ui_scr->video_photo_view_qua = lv_obj_create(ui_scr->video_photo_view_menu);
    lv_obj_set_pos(ui_scr->video_photo_view_qua, 0, 135);
    lv_obj_set_size(ui_scr->video_photo_view_qua, 800, 43);
    lv_obj_set_scrollbar_mode(ui_scr->video_photo_view_qua, LV_SCROLLBAR_MODE_OFF);
    lv_obj_add_flag(ui_scr->video_photo_view_qua, LV_OBJ_FLAG_EVENT_BUBBLE | LV_OBJ_FLAG_SCROLL_ON_FOCUS);
    lv_group_add_obj(def_group, ui_scr->video_photo_view_qua);
    ui_style_set(ui_scr->video_photo_view_qua, GUI_CTRL_CONT);

    //Write codes video_photo_img_4
    ui_scr->video_photo_img_4 = lv_img_create(ui_scr->video_photo_view_qua);
    lv_img_set_src(ui_scr->video_photo_img_4, gui_get_res_path(GUI_RES_IMG_Q_PNG));
    lv_img_set_pivot(ui_scr->video_photo_img_4, 0, 0);
    lv_img_set_angle(ui_scr->video_photo_img_4, 0);
    lv_img_set_zoom(ui_scr->video_photo_img_4, 256);
    lv_obj_set_pos(ui_scr->video_photo_img_4, 8, 6);
    lv_obj_set_size(ui_scr->video_photo_img_4, 29, 29);
    lv_obj_add_flag(ui_scr->video_photo_img_4, LV_OBJ_FLAG_CLICKABLE);
    ui_style_set(ui_scr->video_photo_img_4, GUI_CTRL_IMG);

    //Set style for video_photo_img_4. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
    lv_obj_set_style_bg_color(ui_scr->video_photo_img_4, lv_color_make(0xFF, 0xFF, 0xFF), LV_PART_MAIN | LV_STATE_DEFAULT);

    //Write codes video_photo_lbl_4
    ui_scr->video_photo_lbl_4 = lv_label_create(ui_scr->video_photo_view_qua);
    lv_label_set_long_mode(ui_scr->video_photo_lbl_4, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui_scr->video_photo_lbl_4, 50, 6);
    lv_obj_set_size(ui_scr->video_photo_lbl_4, 200, 32);
    lv_obj_set_scrollbar_mode(ui_scr->video_photo_lbl_4, LV_SCROLLBAR_MODE_OFF);
    ui_style_set(ui_scr->video_photo_lbl_4, GUI_CTRL_LABEL);

    //Write codes video_photo_view_acu
    ui_scr->video_photo_view_acu = lv_obj_create(ui_scr->video_photo_view_menu);
    lv_obj_set_pos(ui_scr->video_photo_view_acu, 0, 180);
    lv_obj_set_size(ui_scr->video_photo_view_acu, 800, 43);
    lv_obj_set_scrollbar_mode(ui_scr->video_photo_view_acu, LV_SCROLLBAR_MODE_OFF);
    lv_obj_add_flag(ui_scr->video_photo_view_acu, LV_OBJ_FLAG_EVENT_BUBBLE | LV_OBJ_FLAG_SCROLL_ON_FOCUS);
    lv_group_add_obj(def_group, ui_scr->video_photo_view_acu);
    ui_style_set(ui_scr->video_photo_view_acu, GUI_CTRL_CONT);

    //Write codes video_photo_img_5
    ui_scr->video_photo_img_5 = lv_img_create(ui_scr->video_photo_view_acu);
    lv_img_set_src(ui_scr->video_photo_img_5, gui_get_res_path(GUI_RES_RUIDU_PNG));
    lv_img_set_pivot(ui_scr->video_photo_img_5, 0, 0);
    lv_img_set_angle(ui_scr->video_photo_img_5, 0);
    lv_img_set_zoom(ui_scr->video_photo_img_5, 256);
    lv_obj_set_pos(ui_scr->video_photo_img_5, 8, 6);
    lv_obj_set_size(ui_scr->video_photo_img_5, 29, 29);
    lv_obj_add_flag(ui_scr->video_photo_img_5, LV_OBJ_FLAG_CLICKABLE);
    ui_style_set(ui_scr->video_photo_img_5, GUI_CTRL_IMG);

    //Set style for video_photo_img_5. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
    lv_obj_set_style_bg_color(ui_scr->video_photo_img_5, lv_color_make(0xFF, 0xFF, 0xFF), LV_PART_MAIN | LV_STATE_DEFAULT);

    //Write codes video_photo_lbl_5
    ui_scr->video_photo_lbl_5 = lv_label_create(ui_scr->video_photo_view_acu);
    lv_label_set_long_mode(ui_scr->video_photo_lbl_5, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui_scr->video_photo_lbl_5, 50, 6);
    lv_obj_set_size(ui_scr->video_photo_lbl_5, 200, 32);
    lv_obj_set_scrollbar_mode(ui_scr->video_photo_lbl_5, LV_SCROLLBAR_MODE_OFF);
    ui_style_set(ui_scr->video_photo_lbl_5, GUI_CTRL_LABEL);

    //Write codes video_photo_view_wbl
    ui_scr->video_photo_view_wbl = lv_obj_create(ui_scr->video_photo_view_menu);
    lv_obj_set_pos(ui_scr->video_photo_view_wbl, 0, 225);
    lv_obj_set_size(ui_scr->video_photo_view_wbl, 800, 43);
    lv_obj_set_scrollbar_mode(ui_scr->video_photo_view_wbl, LV_SCROLLBAR_MODE_OFF);
    lv_obj_add_flag(ui_scr->video_photo_view_wbl, LV_OBJ_FLAG_EVENT_BUBBLE | LV_OBJ_FLAG_SCROLL_ON_FOCUS);
    lv_group_add_obj(def_group, ui_scr->video_photo_view_wbl);
    ui_style_set(ui_scr->video_photo_view_wbl, GUI_CTRL_CONT);

    //Write codes video_photo_img_6
    ui_scr->video_photo_img_6 = lv_img_create(ui_scr->video_photo_view_wbl);
    lv_img_set_src(ui_scr->video_photo_img_6, gui_get_res_path(GUI_RES_AWB_AUTO_PNG));
    lv_img_set_pivot(ui_scr->video_photo_img_6, 0, 0);
    lv_img_set_angle(ui_scr->video_photo_img_6, 0);
    lv_img_set_zoom(ui_scr->video_photo_img_6, 256);
    lv_obj_set_pos(ui_scr->video_photo_img_6, 8, 6);
    lv_obj_set_size(ui_scr->video_photo_img_6, 29, 29);
    lv_obj_add_flag(ui_scr->video_photo_img_6, LV_OBJ_FLAG_CLICKABLE);
    ui_style_set(ui_scr->video_photo_img_6, GUI_CTRL_IMG);

    //Set style for video_photo_img_6. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
    lv_obj_set_style_bg_color(ui_scr->video_photo_img_6, lv_color_make(0xFF, 0xFF, 0xFF), LV_PART_MAIN | LV_STATE_DEFAULT);

    //Write codes video_photo_lbl_6
    ui_scr->video_photo_lbl_6 = lv_label_create(ui_scr->video_photo_view_wbl);
    lv_label_set_long_mode(ui_scr->video_photo_lbl_6, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui_scr->video_photo_lbl_6, 50, 6);
    lv_obj_set_size(ui_scr->video_photo_lbl_6, 200, 32);
    lv_obj_set_scrollbar_mode(ui_scr->video_photo_lbl_6, LV_SCROLLBAR_MODE_OFF);
    ui_style_set(ui_scr->video_photo_lbl_6, GUI_CTRL_LABEL);

    //Write codes video_photo_view_col
    ui_scr->video_photo_view_col = lv_obj_create(ui_scr->video_photo_view_menu);
    lv_obj_set_pos(ui_scr->video_photo_view_col, 0, 270);
    lv_obj_set_size(ui_scr->video_photo_view_col, 800, 43);
    lv_obj_set_scrollbar_mode(ui_scr->video_photo_view_col, LV_SCROLLBAR_MODE_OFF);
    lv_obj_add_flag(ui_scr->video_photo_view_col, LV_OBJ_FLAG_EVENT_BUBBLE | LV_OBJ_FLAG_SCROLL_ON_FOCUS);
    lv_group_add_obj(def_group, ui_scr->video_photo_view_col);
    ui_style_set(ui_scr->video_photo_view_col, GUI_CTRL_CONT);

    //Write codes video_photo_img_7
    ui_scr->video_photo_img_7 = lv_img_create(ui_scr->video_photo_view_col);
    lv_img_set_src(ui_scr->video_photo_img_7, gui_get_res_path(GUI_RES_COLOR_PNG));
    lv_img_set_pivot(ui_scr->video_photo_img_7, 0, 0);
    lv_img_set_angle(ui_scr->video_photo_img_7, 0);
    lv_img_set_zoom(ui_scr->video_photo_img_7, 256);
    lv_obj_set_pos(ui_scr->video_photo_img_7, 8, 6);
    lv_obj_set_size(ui_scr->video_photo_img_7, 29, 29);
    lv_obj_add_flag(ui_scr->video_photo_img_7, LV_OBJ_FLAG_CLICKABLE);
    ui_style_set(ui_scr->video_photo_img_7, GUI_CTRL_IMG);

    //Set style for video_photo_img_7. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
    lv_obj_set_style_bg_color(ui_scr->video_photo_img_7, lv_color_make(0xFF, 0xFF, 0xFF), LV_PART_MAIN | LV_STATE_DEFAULT);

    //Write codes video_photo_lbl_7
    ui_scr->video_photo_lbl_7 = lv_label_create(ui_scr->video_photo_view_col);
    lv_label_set_long_mode(ui_scr->video_photo_lbl_7, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui_scr->video_photo_lbl_7, 50, 6);
    lv_obj_set_size(ui_scr->video_photo_lbl_7, 200, 32);
    lv_obj_set_scrollbar_mode(ui_scr->video_photo_lbl_7, LV_SCROLLBAR_MODE_OFF);
    ui_style_set(ui_scr->video_photo_lbl_7, GUI_CTRL_LABEL);

    //Write codes video_photo_view_iso
    ui_scr->video_photo_view_iso = lv_obj_create(ui_scr->video_photo_view_menu);
    lv_obj_set_pos(ui_scr->video_photo_view_iso, 0, 315);
    lv_obj_set_size(ui_scr->video_photo_view_iso, 800, 43);
    lv_obj_set_scrollbar_mode(ui_scr->video_photo_view_iso, LV_SCROLLBAR_MODE_OFF);
    lv_obj_add_flag(ui_scr->video_photo_view_iso, LV_OBJ_FLAG_EVENT_BUBBLE | LV_OBJ_FLAG_SCROLL_ON_FOCUS);
    lv_group_add_obj(def_group, ui_scr->video_photo_view_iso);
    ui_style_set(ui_scr->video_photo_view_iso, GUI_CTRL_CONT);

    //Write codes video_photo_img_8
    ui_scr->video_photo_img_8 = lv_img_create(ui_scr->video_photo_view_iso);
    lv_img_set_src(ui_scr->video_photo_img_8, gui_get_res_path(GUI_RES_ISO_PNG));
    lv_img_set_pivot(ui_scr->video_photo_img_8, 0, 0);
    lv_img_set_angle(ui_scr->video_photo_img_8, 0);
    lv_img_set_zoom(ui_scr->video_photo_img_8, 256);
    lv_obj_set_pos(ui_scr->video_photo_img_8, 8, 6);
    lv_obj_set_size(ui_scr->video_photo_img_8, 29, 29);
    lv_obj_add_flag(ui_scr->video_photo_img_8, LV_OBJ_FLAG_CLICKABLE);
    ui_style_set(ui_scr->video_photo_img_8, GUI_CTRL_IMG);

    //Set style for video_photo_img_8. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
    lv_obj_set_style_bg_color(ui_scr->video_photo_img_8, lv_color_make(0xFF, 0xFF, 0xFF), LV_PART_MAIN | LV_STATE_DEFAULT);

    //Write codes video_photo_lbl_8
    ui_scr->video_photo_lbl_8 = lv_label_create(ui_scr->video_photo_view_iso);
    lv_label_set_long_mode(ui_scr->video_photo_lbl_8, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui_scr->video_photo_lbl_8, 50, 6);
    lv_obj_set_size(ui_scr->video_photo_lbl_8, 200, 32);
    lv_obj_set_scrollbar_mode(ui_scr->video_photo_lbl_8, LV_SCROLLBAR_MODE_OFF);
    ui_style_set(ui_scr->video_photo_lbl_8, GUI_CTRL_LABEL);

    //Write codes video_photo_view_pexp
    ui_scr->video_photo_view_pexp = lv_obj_create(ui_scr->video_photo_view_menu);
    lv_obj_set_pos(ui_scr->video_photo_view_pexp, 0, 360);
    lv_obj_set_size(ui_scr->video_photo_view_pexp, 800, 43);
    lv_obj_set_scrollbar_mode(ui_scr->video_photo_view_pexp, LV_SCROLLBAR_MODE_OFF);
    lv_obj_add_flag(ui_scr->video_photo_view_pexp, LV_OBJ_FLAG_EVENT_BUBBLE | LV_OBJ_FLAG_SCROLL_ON_FOCUS);
    lv_group_add_obj(def_group, ui_scr->video_photo_view_pexp);
    ui_style_set(ui_scr->video_photo_view_pexp, GUI_CTRL_CONT);

    //Write codes video_photo_img_9
    ui_scr->video_photo_img_9 = lv_img_create(ui_scr->video_photo_view_pexp);
    lv_img_set_src(ui_scr->video_photo_img_9, gui_get_res_path(GUI_RES_M_EXP_PNG));
    lv_img_set_pivot(ui_scr->video_photo_img_9, 0, 0);
    lv_img_set_angle(ui_scr->video_photo_img_9, 0);
    lv_img_set_zoom(ui_scr->video_photo_img_9, 256);
    lv_obj_set_pos(ui_scr->video_photo_img_9, 8, 6);
    lv_obj_set_size(ui_scr->video_photo_img_9, 29, 29);
    lv_obj_add_flag(ui_scr->video_photo_img_9, LV_OBJ_FLAG_CLICKABLE);
    ui_style_set(ui_scr->video_photo_img_9, GUI_CTRL_IMG);

    //Set style for video_photo_img_9. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
    lv_obj_set_style_bg_color(ui_scr->video_photo_img_9, lv_color_make(0xFF, 0xFF, 0xFF), LV_PART_MAIN | LV_STATE_DEFAULT);

    //Write codes video_photo_lbl_9
    ui_scr->video_photo_lbl_9 = lv_label_create(ui_scr->video_photo_view_pexp);
    lv_label_set_long_mode(ui_scr->video_photo_lbl_9, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui_scr->video_photo_lbl_9, 50, 6);
    lv_obj_set_size(ui_scr->video_photo_lbl_9, 200, 32);
    lv_obj_set_scrollbar_mode(ui_scr->video_photo_lbl_9, LV_SCROLLBAR_MODE_OFF);
    ui_style_set(ui_scr->video_photo_lbl_9, GUI_CTRL_LABEL);

    //Write codes video_photo_view_sok
    ui_scr->video_photo_view_sok = lv_obj_create(ui_scr->video_photo_view_menu);
    lv_obj_set_pos(ui_scr->video_photo_view_sok, 0, 405);
    lv_obj_set_size(ui_scr->video_photo_view_sok, 800, 43);
    lv_obj_set_scrollbar_mode(ui_scr->video_photo_view_sok, LV_SCROLLBAR_MODE_OFF);
    lv_obj_add_flag(ui_scr->video_photo_view_sok, LV_OBJ_FLAG_EVENT_BUBBLE | LV_OBJ_FLAG_SCROLL_ON_FOCUS);
    lv_group_add_obj(def_group, ui_scr->video_photo_view_sok);
    ui_style_set(ui_scr->video_photo_view_sok, GUI_CTRL_CONT);

    //Write codes video_photo_img_10
    ui_scr->video_photo_img_10 = lv_img_create(ui_scr->video_photo_view_sok);
    lv_img_set_src(ui_scr->video_photo_img_10, gui_get_res_path(GUI_RES_SHAKE_PNG));
    lv_img_set_pivot(ui_scr->video_photo_img_10, 0, 0);
    lv_img_set_angle(ui_scr->video_photo_img_10, 0);
    lv_img_set_zoom(ui_scr->video_photo_img_10, 256);
    lv_obj_set_pos(ui_scr->video_photo_img_10, 8, 6);
    lv_obj_set_size(ui_scr->video_photo_img_10, 29, 29);
    lv_obj_add_flag(ui_scr->video_photo_img_10, LV_OBJ_FLAG_CLICKABLE);
    ui_style_set(ui_scr->video_photo_img_10, GUI_CTRL_IMG);

    //Set style for video_photo_img_10. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
    lv_obj_set_style_bg_color(ui_scr->video_photo_img_10, lv_color_make(0xFF, 0xFF, 0xFF), LV_PART_MAIN | LV_STATE_DEFAULT);

    //Write codes video_photo_lbl_10
    ui_scr->video_photo_lbl_10 = lv_label_create(ui_scr->video_photo_view_sok);
    lv_label_set_long_mode(ui_scr->video_photo_lbl_10, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui_scr->video_photo_lbl_10, 50, 6);
    lv_obj_set_size(ui_scr->video_photo_lbl_10, 200, 32);
    lv_obj_set_scrollbar_mode(ui_scr->video_photo_lbl_10, LV_SCROLLBAR_MODE_OFF);
    ui_style_set(ui_scr->video_photo_lbl_10, GUI_CTRL_LABEL);

    //Write codes video_photo_view_sca
    ui_scr->video_photo_view_sca = lv_obj_create(ui_scr->video_photo_view_menu);
    lv_obj_set_pos(ui_scr->video_photo_view_sca, 0, 450);
    lv_obj_set_size(ui_scr->video_photo_view_sca, 800, 43);
    lv_obj_set_scrollbar_mode(ui_scr->video_photo_view_sca, LV_SCROLLBAR_MODE_OFF);
    lv_obj_add_flag(ui_scr->video_photo_view_sca, LV_OBJ_FLAG_EVENT_BUBBLE | LV_OBJ_FLAG_SCROLL_ON_FOCUS);
    lv_group_add_obj(def_group, ui_scr->video_photo_view_sca);
    ui_style_set(ui_scr->video_photo_view_sca, GUI_CTRL_CONT);

    //Write codes video_photo_img_11
    ui_scr->video_photo_img_11 = lv_img_create(ui_scr->video_photo_view_sca);
    lv_img_set_src(ui_scr->video_photo_img_11, gui_get_res_path(GUI_RES_SCAN_PNG));
    lv_img_set_pivot(ui_scr->video_photo_img_11, 0, 0);
    lv_img_set_angle(ui_scr->video_photo_img_11, 0);
    lv_img_set_zoom(ui_scr->video_photo_img_11, 256);
    lv_obj_set_pos(ui_scr->video_photo_img_11, 8, 6);
    lv_obj_set_size(ui_scr->video_photo_img_11, 29, 29);
    lv_obj_add_flag(ui_scr->video_photo_img_11, LV_OBJ_FLAG_CLICKABLE);
    ui_style_set(ui_scr->video_photo_img_11, GUI_CTRL_IMG);

    //Set style for video_photo_img_11. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
    lv_obj_set_style_bg_color(ui_scr->video_photo_img_11, lv_color_make(0xFF, 0xFF, 0xFF), LV_PART_MAIN | LV_STATE_DEFAULT);

    //Write codes video_photo_lbl_11
    ui_scr->video_photo_lbl_11 = lv_label_create(ui_scr->video_photo_view_sca);
    lv_label_set_long_mode(ui_scr->video_photo_lbl_11, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui_scr->video_photo_lbl_11, 50, 6);
    lv_obj_set_size(ui_scr->video_photo_lbl_11, 200, 32);
    lv_obj_set_scrollbar_mode(ui_scr->video_photo_lbl_11, LV_SCROLLBAR_MODE_OFF);
    ui_style_set(ui_scr->video_photo_lbl_11, GUI_CTRL_LABEL);

    //Write codes video_photo_view_pdat
    ui_scr->video_photo_view_pdat = lv_obj_create(ui_scr->video_photo_view_menu);
    lv_obj_set_pos(ui_scr->video_photo_view_pdat, 0, 495);
    lv_obj_set_size(ui_scr->video_photo_view_pdat, 800, 43);
    lv_obj_set_scrollbar_mode(ui_scr->video_photo_view_pdat, LV_SCROLLBAR_MODE_OFF);
    lv_obj_add_flag(ui_scr->video_photo_view_pdat, LV_OBJ_FLAG_EVENT_BUBBLE | LV_OBJ_FLAG_SCROLL_ON_FOCUS);
    lv_group_add_obj(def_group, ui_scr->video_photo_view_pdat);
    ui_style_set(ui_scr->video_photo_view_pdat, GUI_CTRL_CONT);

    //Write codes video_photo_img_12
    ui_scr->video_photo_img_12 = lv_img_create(ui_scr->video_photo_view_pdat);
    lv_img_set_src(ui_scr->video_photo_img_12, gui_get_res_path(GUI_RES_M_DAT_PNG));
    lv_img_set_pivot(ui_scr->video_photo_img_12, 0, 0);
    lv_img_set_angle(ui_scr->video_photo_img_12, 0);
    lv_img_set_zoom(ui_scr->video_photo_img_12, 256);
    lv_obj_set_pos(ui_scr->video_photo_img_12, 8, 6);
    lv_obj_set_size(ui_scr->video_photo_img_12, 29, 29);
    lv_obj_add_flag(ui_scr->video_photo_img_12, LV_OBJ_FLAG_CLICKABLE);
    ui_style_set(ui_scr->video_photo_img_12, GUI_CTRL_IMG);

    //Set style for video_photo_img_12. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
    lv_obj_set_style_bg_color(ui_scr->video_photo_img_12, lv_color_make(0xFF, 0xFF, 0xFF), LV_PART_MAIN | LV_STATE_DEFAULT);

    //Write codes video_photo_lbl_12
    ui_scr->video_photo_lbl_12 = lv_label_create(ui_scr->video_photo_view_pdat);
    lv_label_set_long_mode(ui_scr->video_photo_lbl_12, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui_scr->video_photo_lbl_12, 50, 6);
    lv_obj_set_size(ui_scr->video_photo_lbl_12, 200, 32);
    lv_obj_set_scrollbar_mode(ui_scr->video_photo_lbl_12, LV_SCROLLBAR_MODE_OFF);
    ui_style_set(ui_scr->video_photo_lbl_12, GUI_CTRL_LABEL);

    //Write codes video_photo_img_14
    ui_scr->video_photo_img_14 = lv_img_create(ui_scr->video_photo_view_menu_b);
    lv_img_set_src(ui_scr->video_photo_img_14, gui_get_res_path(GUI_RES_MENU_STA_PNG));
    lv_img_set_pivot(ui_scr->video_photo_img_14, 0, 0);
    lv_img_set_angle(ui_scr->video_photo_img_14, 0);
    lv_img_set_zoom(ui_scr->video_photo_img_14, 256);
    lv_obj_set_pos(ui_scr->video_photo_img_14, 0, 0);
    lv_obj_set_size(ui_scr->video_photo_img_14, 800, 40);
    lv_obj_add_flag(ui_scr->video_photo_img_14, LV_OBJ_FLAG_CLICKABLE);
    ui_style_set(ui_scr->video_photo_img_14, GUI_CTRL_IMG);

    //Set style for video_photo_img_14. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
    lv_obj_set_style_outline_opa(ui_scr->video_photo_img_14, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

    //Write codes video_photo_img_15
    ui_scr->video_photo_img_15 = lv_img_create(ui_scr->video_photo_view_menu_b);
    lv_img_set_src(ui_scr->video_photo_img_15, gui_get_res_path(GUI_RES_MENU_STA_PNG));
    lv_img_set_pivot(ui_scr->video_photo_img_15, 0, 0);
    lv_img_set_angle(ui_scr->video_photo_img_15, 0);
    lv_img_set_zoom(ui_scr->video_photo_img_15, 256);
    lv_obj_set_pos(ui_scr->video_photo_img_15, 0, 440);
    lv_obj_set_size(ui_scr->video_photo_img_15, 800, 40);
    lv_obj_add_flag(ui_scr->video_photo_img_15, LV_OBJ_FLAG_CLICKABLE);
    ui_style_set(ui_scr->video_photo_img_15, GUI_CTRL_IMG);

    //Set style for video_photo_img_15. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
    lv_obj_set_style_outline_opa(ui_scr->video_photo_img_15, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

    //Write codes video_photo_img_16
    ui_scr->video_photo_img_16 = lv_img_create(ui_scr->video_photo_view_menu_b);
    lv_img_set_src(ui_scr->video_photo_img_16, gui_get_res_path(GUI_RES_PHOTO_PNG));
    lv_img_set_pivot(ui_scr->video_photo_img_16, 0, 0);
    lv_img_set_angle(ui_scr->video_photo_img_16, 0);
    lv_img_set_zoom(ui_scr->video_photo_img_16, 256);
    lv_obj_set_pos(ui_scr->video_photo_img_16, 9, 5);
    lv_obj_set_size(ui_scr->video_photo_img_16, 40, 30);
    lv_obj_add_flag(ui_scr->video_photo_img_16, LV_OBJ_FLAG_CLICKABLE);
    ui_style_set(ui_scr->video_photo_img_16, GUI_CTRL_IMG);

    //Set style for video_photo_img_16. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
    lv_obj_set_style_bg_color(ui_scr->video_photo_img_16, lv_color_make(0x42, 0xA5, 0xF5), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_scr->video_photo_img_16, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_outline_color(ui_scr->video_photo_img_16, lv_color_make(0x42, 0xA5, 0xF5), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_outline_width(ui_scr->video_photo_img_16, 4, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_outline_opa(ui_scr->video_photo_img_16, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    //Write codes video_photo_img_17
    ui_scr->video_photo_img_17 = lv_img_create(ui_scr->video_photo_view_menu_b);
    lv_img_set_src(ui_scr->video_photo_img_17, gui_get_res_path(GUI_RES_SET_PNG));
    lv_img_set_pivot(ui_scr->video_photo_img_17, 0, 0);
    lv_img_set_angle(ui_scr->video_photo_img_17, 0);
    lv_img_set_zoom(ui_scr->video_photo_img_17, 256);
    lv_obj_set_pos(ui_scr->video_photo_img_17, 70, 1);
    lv_obj_set_size(ui_scr->video_photo_img_17, 37, 37);
    lv_obj_add_flag(ui_scr->video_photo_img_17, LV_OBJ_FLAG_CLICKABLE);
    ui_style_set(ui_scr->video_photo_img_17, GUI_CTRL_IMG);

    //Write codes video_photo_img_18
    ui_scr->video_photo_img_18 = lv_img_create(ui_scr->video_photo_view_menu_b);
    lv_img_set_src(ui_scr->video_photo_img_18, gui_get_res_path(GUI_RES_LEFT_PNG));
    lv_img_set_pivot(ui_scr->video_photo_img_18, 0, 0);
    lv_img_set_angle(ui_scr->video_photo_img_18, 0);
    lv_img_set_zoom(ui_scr->video_photo_img_18, 256);
    lv_obj_set_pos(ui_scr->video_photo_img_18, 200, 445);
    lv_obj_set_size(ui_scr->video_photo_img_18, 21, 29);
    lv_obj_add_flag(ui_scr->video_photo_img_18, LV_OBJ_FLAG_CLICKABLE);
    ui_style_set(ui_scr->video_photo_img_18, GUI_CTRL_IMG);

    //Write codes video_photo_img_19
    ui_scr->video_photo_img_19 = lv_img_create(ui_scr->video_photo_view_menu_b);
    lv_img_set_src(ui_scr->video_photo_img_19, gui_get_res_path(GUI_RES_UP_PNG));
    lv_img_set_pivot(ui_scr->video_photo_img_19, 0, 0);
    lv_img_set_angle(ui_scr->video_photo_img_19, 0);
    lv_img_set_zoom(ui_scr->video_photo_img_19, 256);
    lv_obj_set_pos(ui_scr->video_photo_img_19, 321, 448);
    lv_obj_set_size(ui_scr->video_photo_img_19, 29, 21);
    lv_obj_add_flag(ui_scr->video_photo_img_19, LV_OBJ_FLAG_CLICKABLE);
    ui_style_set(ui_scr->video_photo_img_19, GUI_CTRL_IMG);

    //Write codes video_photo_img_20
    ui_scr->video_photo_img_20 = lv_img_create(ui_scr->video_photo_view_menu_b);
    lv_img_set_src(ui_scr->video_photo_img_20, gui_get_res_path(GUI_RES_DOWN_PNG));
    lv_img_set_pivot(ui_scr->video_photo_img_20, 0, 0);
    lv_img_set_angle(ui_scr->video_photo_img_20, 0);
    lv_img_set_zoom(ui_scr->video_photo_img_20, 256);
    lv_obj_set_pos(ui_scr->video_photo_img_20, 450, 448);
    lv_obj_set_size(ui_scr->video_photo_img_20, 29, 21);
    lv_obj_add_flag(ui_scr->video_photo_img_20, LV_OBJ_FLAG_CLICKABLE);
    ui_style_set(ui_scr->video_photo_img_20, GUI_CTRL_IMG);

    //Write codes video_photo_img_21
    ui_scr->video_photo_img_21 = lv_img_create(ui_scr->video_photo_view_menu_b);
    lv_img_set_src(ui_scr->video_photo_img_21, gui_get_res_path(GUI_RES_RIGHT_PNG));
    lv_img_set_pivot(ui_scr->video_photo_img_21, 0, 0);
    lv_img_set_angle(ui_scr->video_photo_img_21, 0);
    lv_img_set_zoom(ui_scr->video_photo_img_21, 256);
    lv_obj_set_pos(ui_scr->video_photo_img_21, 579, 445);
    lv_obj_set_size(ui_scr->video_photo_img_21, 21, 29);
    lv_obj_add_flag(ui_scr->video_photo_img_21, LV_OBJ_FLAG_CLICKABLE);
    ui_style_set(ui_scr->video_photo_img_21, GUI_CTRL_IMG);

    //Write codes video_photo_view_submenu
    ui_scr->video_photo_view_submenu = lv_obj_create(ui_scr->video_photo);
    lv_obj_set_pos(ui_scr->video_photo_view_submenu, 111, 83);
    lv_obj_set_size(ui_scr->video_photo_view_submenu, 590, 314);
    lv_obj_set_scrollbar_mode(ui_scr->video_photo_view_submenu, LV_SCROLLBAR_MODE_OFF);
    lv_obj_add_flag(ui_scr->video_photo_view_submenu, LV_OBJ_FLAG_HIDDEN);
    ui_style_set(ui_scr->video_photo_view_submenu, GUI_CTRL_CONT);

    //Set style for video_photo_view_submenu. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
    lv_obj_set_style_bg_color(ui_scr->video_photo_view_submenu, lv_color_make(0x75, 0x75, 0x75), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_scr->video_photo_view_submenu, 250, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui_scr->video_photo_view_submenu, 2, LV_PART_MAIN | LV_STATE_DEFAULT);

    //Delete extra default style for video_photo_view_submenu
    lv_obj_remove_style(ui_scr->video_photo_view_submenu, &gui_cont_main_focus_key_style, LV_PART_MAIN | LV_STATE_FOCUS_KEY);

    //Write codes video_photo_submenu_btn_1
    ui_scr->video_photo_submenu_btn_1 = lv_btn_create(ui_scr->video_photo_view_submenu);
    lv_obj_set_pos(ui_scr->video_photo_submenu_btn_1, 83, 44);
    lv_obj_set_size(ui_scr->video_photo_submenu_btn_1, 438, 37);
    lv_obj_set_scrollbar_mode(ui_scr->video_photo_submenu_btn_1, LV_SCROLLBAR_MODE_OFF);
    lv_obj_add_flag(ui_scr->video_photo_submenu_btn_1, LV_OBJ_FLAG_EVENT_BUBBLE);
    ui_style_set(ui_scr->video_photo_submenu_btn_1, GUI_CTRL_BUTTON);

    //Set style for video_photo_submenu_btn_1. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
    lv_obj_set_style_bg_opa(ui_scr->video_photo_submenu_btn_1, 203, LV_PART_MAIN | LV_STATE_DEFAULT);
    ui_scr->video_photo_submenu_btn_1_label = lv_label_create(ui_scr->video_photo_submenu_btn_1);
    lv_label_set_text(ui_scr->video_photo_submenu_btn_1_label, "button1");
    lv_obj_set_style_pad_all(ui_scr->video_photo_submenu_btn_1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_align(ui_scr->video_photo_submenu_btn_1_label, LV_ALIGN_CENTER, 0, 0);

    //Write codes video_photo_submenu_btn_2
    ui_scr->video_photo_submenu_btn_2 = lv_btn_create(ui_scr->video_photo_view_submenu);
    lv_obj_set_pos(ui_scr->video_photo_submenu_btn_2, 83, 111);
    lv_obj_set_size(ui_scr->video_photo_submenu_btn_2, 438, 37);
    lv_obj_set_scrollbar_mode(ui_scr->video_photo_submenu_btn_2, LV_SCROLLBAR_MODE_OFF);
    lv_obj_add_flag(ui_scr->video_photo_submenu_btn_2, LV_OBJ_FLAG_EVENT_BUBBLE);
    ui_style_set(ui_scr->video_photo_submenu_btn_2, GUI_CTRL_BUTTON);

    //Set style for video_photo_submenu_btn_2. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
    lv_obj_set_style_bg_opa(ui_scr->video_photo_submenu_btn_2, 215, LV_PART_MAIN | LV_STATE_DEFAULT);
    ui_scr->video_photo_submenu_btn_2_label = lv_label_create(ui_scr->video_photo_submenu_btn_2);
    lv_label_set_text(ui_scr->video_photo_submenu_btn_2_label, "button2");
    lv_obj_set_style_pad_all(ui_scr->video_photo_submenu_btn_2, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_align(ui_scr->video_photo_submenu_btn_2_label, LV_ALIGN_CENTER, 0, 0);

    //Write codes video_photo_submenu_btn_3
    ui_scr->video_photo_submenu_btn_3 = lv_btn_create(ui_scr->video_photo_view_submenu);
    lv_obj_set_pos(ui_scr->video_photo_submenu_btn_3, 83, 171);
    lv_obj_set_size(ui_scr->video_photo_submenu_btn_3, 438, 37);
    lv_obj_set_scrollbar_mode(ui_scr->video_photo_submenu_btn_3, LV_SCROLLBAR_MODE_OFF);
    lv_obj_add_flag(ui_scr->video_photo_submenu_btn_3, LV_OBJ_FLAG_EVENT_BUBBLE);
    ui_style_set(ui_scr->video_photo_submenu_btn_3, GUI_CTRL_BUTTON);

    //Set style for video_photo_submenu_btn_3. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
    lv_obj_set_style_bg_opa(ui_scr->video_photo_submenu_btn_3, 205, LV_PART_MAIN | LV_STATE_DEFAULT);
    ui_scr->video_photo_submenu_btn_3_label = lv_label_create(ui_scr->video_photo_submenu_btn_3);
    lv_label_set_text(ui_scr->video_photo_submenu_btn_3_label, "button3");
    lv_obj_set_style_pad_all(ui_scr->video_photo_submenu_btn_3, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_align(ui_scr->video_photo_submenu_btn_3_label, LV_ALIGN_CENTER, 0, 0);

    //Write codes video_photo_submenu_btn_4
    ui_scr->video_photo_submenu_btn_4 = lv_btn_create(ui_scr->video_photo_view_submenu);
    lv_obj_set_pos(ui_scr->video_photo_submenu_btn_4, 83, 233);
    lv_obj_set_size(ui_scr->video_photo_submenu_btn_4, 438, 37);
    lv_obj_set_scrollbar_mode(ui_scr->video_photo_submenu_btn_4, LV_SCROLLBAR_MODE_OFF);
    lv_obj_add_flag(ui_scr->video_photo_submenu_btn_4, LV_OBJ_FLAG_EVENT_BUBBLE);
    ui_style_set(ui_scr->video_photo_submenu_btn_4, GUI_CTRL_BUTTON);

    //Set style for video_photo_submenu_btn_4. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
    lv_obj_set_style_bg_opa(ui_scr->video_photo_submenu_btn_4, 205, LV_PART_MAIN | LV_STATE_DEFAULT);
    ui_scr->video_photo_submenu_btn_4_label = lv_label_create(ui_scr->video_photo_submenu_btn_4);
    lv_label_set_text(ui_scr->video_photo_submenu_btn_4_label, "button4");
    lv_obj_set_style_pad_all(ui_scr->video_photo_submenu_btn_4, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_align(ui_scr->video_photo_submenu_btn_4_label, LV_ALIGN_CENTER, 0, 0);

    //Write codes video_photo_roller_mutifunc
    ui_scr->video_photo_roller_mutifunc = lv_roller_create(ui_scr->video_photo_view_submenu);
    lv_obj_set_pos(ui_scr->video_photo_roller_mutifunc, 223, 55);
    lv_obj_set_size(ui_scr->video_photo_roller_mutifunc, 148, 174);
    lv_obj_set_scrollbar_mode(ui_scr->video_photo_roller_mutifunc, LV_SCROLLBAR_MODE_OFF);
    lv_obj_add_flag(ui_scr->video_photo_roller_mutifunc, LV_OBJ_FLAG_EVENT_BUBBLE);
    ui_style_set(ui_scr->video_photo_roller_mutifunc, GUI_CTRL_ROLLER);
    lv_roller_set_options(ui_scr->video_photo_roller_mutifunc, "1\n2\n3\n4\n5", LV_ROLLER_MODE_INFINITE);
    lv_roller_set_visible_row_count(ui_scr->video_photo_roller_mutifunc, 5);

    lv_obj_update_layout(ui_scr->video_photo);
    ui_scr->video_photo_del = false;
    i18n_refresh_texts(GUI_SCREEN_VIDEO_PHOTO);

    //Init events for screen
    events_init_video_photo(ui);
    return ui_scr->video_photo;
}
void unload_scr_video_photo(lv_ui *ui)
{
    ui_free_scr_ptr(ui, GUI_SCREEN_VIDEO_PHOTO);
}

#endif
