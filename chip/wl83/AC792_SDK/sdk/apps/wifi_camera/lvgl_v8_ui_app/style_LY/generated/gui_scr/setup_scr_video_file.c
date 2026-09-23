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


lv_obj_t *setup_scr_video_file(lv_ui *ui)
{
    lv_ui_video_file *ui_scr = ui_get_scr_ptr(ui, GUI_SCREEN_VIDEO_FILE);
    if (ui_scr == NULL) {
        ui_scr = lv_mem_alloc(sizeof(lv_ui_video_file));
        if (ui_scr == NULL) {
            return NULL;
        }
        memset(ui_scr, 0, sizeof(lv_ui_video_file));
        ui->video_file = ui_scr;
    }

    //Write codes video_file
    ui_scr->video_file = lv_obj_create(NULL);
    lv_group_t *def_group = lv_group_get_default();
    lv_obj_set_scrollbar_mode(ui_scr->video_file, LV_SCROLLBAR_MODE_ON);
    lv_obj_clear_flag(ui_scr->video_file, LV_OBJ_FLAG_SCROLLABLE);
    ui_style_set(ui_scr->video_file, GUI_CTRL_SCR);

    //Set style for video_file. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
    lv_obj_set_style_bg_opa(ui_scr->video_file, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui_scr->video_file, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

    //Write codes video_file_view_1
    ui_scr->video_file_view_1 = lv_obj_create(ui_scr->video_file);
    lv_obj_set_pos(ui_scr->video_file_view_1, 0, 0);
    lv_obj_set_size(ui_scr->video_file_view_1, 80, 480);
    lv_obj_set_scrollbar_mode(ui_scr->video_file_view_1, LV_SCROLLBAR_MODE_OFF);
    ui_style_set(ui_scr->video_file_view_1, GUI_CTRL_CONT);

    //Set style for video_file_view_1. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
    lv_obj_set_style_bg_color(ui_scr->video_file_view_1, lv_color_make(0x63, 0x61, 0x61), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_scr->video_file_view_1, 153, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui_scr->video_file_view_1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

    //Delete extra default style for video_file_view_1
    lv_obj_remove_style(ui_scr->video_file_view_1, &gui_cont_main_focus_key_style, LV_PART_MAIN | LV_STATE_FOCUS_KEY);

    //Write codes video_file_img_1
    ui_scr->video_file_img_1 = lv_img_create(ui_scr->video_file_view_1);
    lv_img_set_src(ui_scr->video_file_img_1, gui_get_res_path(GUI_RES_UP_1_PNG));
    lv_img_set_pivot(ui_scr->video_file_img_1, 0, 0);
    lv_img_set_angle(ui_scr->video_file_img_1, 0);
    lv_img_set_zoom(ui_scr->video_file_img_1, 256);
    lv_obj_set_pos(ui_scr->video_file_img_1, 8, 139);
    lv_obj_set_size(ui_scr->video_file_img_1, 64, 64);
    lv_obj_add_flag(ui_scr->video_file_img_1, LV_OBJ_FLAG_CLICKABLE);
    ui_style_set(ui_scr->video_file_img_1, GUI_CTRL_IMG);

    //Set style for video_file_img_1. Part: LV_PART_MAIN, State: LV_STATE_FOCUS_KEY
    lv_obj_add_style(ui_scr->video_file_img_1, &gui_img_main_focus_key_style, LV_PART_MAIN | LV_STATE_FOCUS_KEY);

    //Write codes video_file_img_2
    ui_scr->video_file_img_2 = lv_img_create(ui_scr->video_file_view_1);
    lv_img_set_src(ui_scr->video_file_img_2, gui_get_res_path(GUI_RES_DOWN_1_PNG));
    lv_img_set_pivot(ui_scr->video_file_img_2, 0, 0);
    lv_img_set_angle(ui_scr->video_file_img_2, 0);
    lv_img_set_zoom(ui_scr->video_file_img_2, 256);
    lv_obj_set_pos(ui_scr->video_file_img_2, 8, 287);
    lv_obj_set_size(ui_scr->video_file_img_2, 64, 64);
    lv_obj_add_flag(ui_scr->video_file_img_2, LV_OBJ_FLAG_CLICKABLE);
    ui_style_set(ui_scr->video_file_img_2, GUI_CTRL_IMG);

    //Set style for video_file_img_2. Part: LV_PART_MAIN, State: LV_STATE_FOCUS_KEY
    lv_obj_add_style(ui_scr->video_file_img_2, &gui_img_main_focus_key_style, LV_PART_MAIN | LV_STATE_FOCUS_KEY);

    //Write codes video_file_view_8
    ui_scr->video_file_view_8 = lv_obj_create(ui_scr->video_file);
    lv_obj_set_pos(ui_scr->video_file_view_8, 720, 0);
    lv_obj_set_size(ui_scr->video_file_view_8, 80, 480);
    lv_obj_set_scrollbar_mode(ui_scr->video_file_view_8, LV_SCROLLBAR_MODE_OFF);
    ui_style_set(ui_scr->video_file_view_8, GUI_CTRL_CONT);

    //Set style for video_file_view_8. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
    lv_obj_set_style_bg_color(ui_scr->video_file_view_8, lv_color_make(0x63, 0x61, 0x61), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_scr->video_file_view_8, 153, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui_scr->video_file_view_8, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

    //Delete extra default style for video_file_view_8
    lv_obj_remove_style(ui_scr->video_file_view_8, &gui_cont_main_focus_key_style, LV_PART_MAIN | LV_STATE_FOCUS_KEY);

    //Write codes video_file_lbl_path
    ui_scr->video_file_lbl_path = lv_label_create(ui_scr->video_file);
    lv_label_set_text(ui_scr->video_file_lbl_path, "storage/sd0/C/DCIM/1/");
    lv_label_set_long_mode(ui_scr->video_file_lbl_path, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui_scr->video_file_lbl_path, 60, 10);
    lv_obj_set_size(ui_scr->video_file_lbl_path, 666, 38);
    lv_obj_set_scrollbar_mode(ui_scr->video_file_lbl_path, LV_SCROLLBAR_MODE_OFF);
    ui_style_set(ui_scr->video_file_lbl_path, GUI_CTRL_LABEL);

    //Set style for video_file_lbl_path. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
    lv_obj_set_style_text_color(ui_scr->video_file_lbl_path, lv_color_make(0xFF, 0xFF, 0xFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_scr->video_file_lbl_path, &lv_font_montserratMedium_22, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui_scr->video_file_lbl_path, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui_scr->video_file_lbl_path, 8, LV_PART_MAIN | LV_STATE_DEFAULT);

    //Write codes video_file_view_3
    ui_scr->video_file_view_3 = lv_obj_create(ui_scr->video_file);
    lv_obj_set_pos(ui_scr->video_file_view_3, 85, 49);
    lv_obj_set_size(ui_scr->video_file_view_3, 630, 424);
    lv_obj_set_scrollbar_mode(ui_scr->video_file_view_3, LV_SCROLLBAR_MODE_ON);
    ui_style_set(ui_scr->video_file_view_3, GUI_CTRL_CONT);

    //Set style for video_file_view_3. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
    lv_obj_set_style_border_width(ui_scr->video_file_view_3, 2, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui_scr->video_file_view_3, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_side(ui_scr->video_file_view_3, LV_BORDER_SIDE_NONE, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_outline_width(ui_scr->video_file_view_3, 2, LV_PART_MAIN | LV_STATE_DEFAULT);

    //Delete extra default style for video_file_view_3
    lv_obj_remove_style(ui_scr->video_file_view_3, &gui_cont_main_focus_key_style, LV_PART_MAIN | LV_STATE_FOCUS_KEY);

    //Write codes video_file_lbl_1
    ui_scr->video_file_lbl_1 = lv_label_create(ui_scr->video_file);
    lv_label_set_text(ui_scr->video_file_lbl_1, "100\n/\n99999");
    lv_label_set_long_mode(ui_scr->video_file_lbl_1, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui_scr->video_file_lbl_1, 0, 210);
    lv_obj_set_size(ui_scr->video_file_lbl_1, 80, 78);
    lv_obj_set_scrollbar_mode(ui_scr->video_file_lbl_1, LV_SCROLLBAR_MODE_OFF);
    ui_style_set(ui_scr->video_file_lbl_1, GUI_CTRL_LABEL);

    //Set style for video_file_lbl_1. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
    lv_obj_set_style_shadow_opa(ui_scr->video_file_lbl_1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui_scr->video_file_lbl_1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_outline_opa(ui_scr->video_file_lbl_1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_scr->video_file_lbl_1, &lv_font_montserratMedium_18, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui_scr->video_file_lbl_1, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui_scr->video_file_lbl_1, 8, LV_PART_MAIN | LV_STATE_DEFAULT);

    //Write codes video_file_view_menu_b
    ui_scr->video_file_view_menu_b = lv_obj_create(ui_scr->video_file);
    lv_obj_set_pos(ui_scr->video_file_view_menu_b, 0, 0);
    lv_obj_set_size(ui_scr->video_file_view_menu_b, 800, 480);
    lv_obj_set_scrollbar_mode(ui_scr->video_file_view_menu_b, LV_SCROLLBAR_MODE_OFF);
    lv_obj_add_flag(ui_scr->video_file_view_menu_b, LV_OBJ_FLAG_HIDDEN);
    ui_style_set(ui_scr->video_file_view_menu_b, GUI_CTRL_CONT);

    //Delete extra default style for video_file_view_menu_b
    lv_obj_remove_style(ui_scr->video_file_view_menu_b, &gui_cont_main_focus_key_style, LV_PART_MAIN | LV_STATE_FOCUS_KEY);

    //Write codes video_file_view_menu
    ui_scr->video_file_view_menu = lv_obj_create(ui_scr->video_file_view_menu_b);
    lv_obj_set_pos(ui_scr->video_file_view_menu, 0, 40);
    lv_obj_set_size(ui_scr->video_file_view_menu, 800, 400);
    lv_obj_set_scrollbar_mode(ui_scr->video_file_view_menu, LV_SCROLLBAR_MODE_OFF);
    ui_style_set(ui_scr->video_file_view_menu, GUI_CTRL_CONT);

    //Set style for video_file_view_menu. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
    lv_obj_set_style_bg_color(ui_scr->video_file_view_menu, lv_color_make(0x61, 0x61, 0x61), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_scr->video_file_view_menu, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui_scr->video_file_view_menu, lv_color_make(0x21, 0x95, 0xF6), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui_scr->video_file_view_menu, 2, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui_scr->video_file_view_menu, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_outline_color(ui_scr->video_file_view_menu, lv_color_make(0x21, 0x95, 0xF6), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_outline_opa(ui_scr->video_file_view_menu, 91, LV_PART_MAIN | LV_STATE_DEFAULT);

    //Delete extra default style for video_file_view_menu
    lv_obj_remove_style(ui_scr->video_file_view_menu, &gui_cont_main_focus_key_style, LV_PART_MAIN | LV_STATE_FOCUS_KEY);

    //Write codes video_file_view_del
    ui_scr->video_file_view_del = lv_obj_create(ui_scr->video_file_view_menu);
    lv_obj_set_pos(ui_scr->video_file_view_del, 0, 0);
    lv_obj_set_size(ui_scr->video_file_view_del, 800, 43);
    lv_obj_set_scrollbar_mode(ui_scr->video_file_view_del, LV_SCROLLBAR_MODE_OFF);
    lv_obj_add_flag(ui_scr->video_file_view_del, LV_OBJ_FLAG_EVENT_BUBBLE | LV_OBJ_FLAG_SCROLL_ON_FOCUS);
    lv_group_add_obj(def_group, ui_scr->video_file_view_del);
    ui_style_set(ui_scr->video_file_view_del, GUI_CTRL_CONT);

    //Write codes video_file_img_3
    ui_scr->video_file_img_3 = lv_img_create(ui_scr->video_file_view_del);
    lv_img_set_src(ui_scr->video_file_img_3, gui_get_res_path(GUI_RES_DELET_PNG));
    lv_img_set_pivot(ui_scr->video_file_img_3, 0, 0);
    lv_img_set_angle(ui_scr->video_file_img_3, 0);
    lv_img_set_zoom(ui_scr->video_file_img_3, 256);
    lv_obj_set_pos(ui_scr->video_file_img_3, 8, 6);
    lv_obj_set_size(ui_scr->video_file_img_3, 29, 29);
    lv_obj_add_flag(ui_scr->video_file_img_3, LV_OBJ_FLAG_CLICKABLE);
    ui_style_set(ui_scr->video_file_img_3, GUI_CTRL_IMG);

    //Set style for video_file_img_3. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
    lv_obj_set_style_bg_color(ui_scr->video_file_img_3, lv_color_make(0xFF, 0xFF, 0xFF), LV_PART_MAIN | LV_STATE_DEFAULT);

    //Write codes video_file_lbl_2
    ui_scr->video_file_lbl_2 = lv_label_create(ui_scr->video_file_view_del);
    lv_label_set_long_mode(ui_scr->video_file_lbl_2, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui_scr->video_file_lbl_2, 50, 6);
    lv_obj_set_size(ui_scr->video_file_lbl_2, 200, 32);
    lv_obj_set_scrollbar_mode(ui_scr->video_file_lbl_2, LV_SCROLLBAR_MODE_OFF);
    ui_style_set(ui_scr->video_file_lbl_2, GUI_CTRL_LABEL);

    //Write codes video_file_view_pro
    ui_scr->video_file_view_pro = lv_obj_create(ui_scr->video_file_view_menu);
    lv_obj_set_pos(ui_scr->video_file_view_pro, 0, 45);
    lv_obj_set_size(ui_scr->video_file_view_pro, 800, 43);
    lv_obj_set_scrollbar_mode(ui_scr->video_file_view_pro, LV_SCROLLBAR_MODE_OFF);
    lv_obj_add_flag(ui_scr->video_file_view_pro, LV_OBJ_FLAG_EVENT_BUBBLE | LV_OBJ_FLAG_SCROLL_ON_FOCUS);
    lv_group_add_obj(def_group, ui_scr->video_file_view_pro);
    ui_style_set(ui_scr->video_file_view_pro, GUI_CTRL_CONT);

    //Write codes video_file_img_4
    ui_scr->video_file_img_4 = lv_img_create(ui_scr->video_file_view_pro);
    lv_img_set_src(ui_scr->video_file_img_4, gui_get_res_path(GUI_RES_PROTECT_PNG));
    lv_img_set_pivot(ui_scr->video_file_img_4, 0, 0);
    lv_img_set_angle(ui_scr->video_file_img_4, 0);
    lv_img_set_zoom(ui_scr->video_file_img_4, 256);
    lv_obj_set_pos(ui_scr->video_file_img_4, 8, 6);
    lv_obj_set_size(ui_scr->video_file_img_4, 29, 29);
    lv_obj_add_flag(ui_scr->video_file_img_4, LV_OBJ_FLAG_CLICKABLE);
    ui_style_set(ui_scr->video_file_img_4, GUI_CTRL_IMG);

    //Set style for video_file_img_4. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
    lv_obj_set_style_bg_color(ui_scr->video_file_img_4, lv_color_make(0xFF, 0xFF, 0xFF), LV_PART_MAIN | LV_STATE_DEFAULT);

    //Write codes video_file_lbl_3
    ui_scr->video_file_lbl_3 = lv_label_create(ui_scr->video_file_view_pro);
    lv_label_set_long_mode(ui_scr->video_file_lbl_3, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui_scr->video_file_lbl_3, 50, 6);
    lv_obj_set_size(ui_scr->video_file_lbl_3, 200, 32);
    lv_obj_set_scrollbar_mode(ui_scr->video_file_lbl_3, LV_SCROLLBAR_MODE_OFF);
    ui_style_set(ui_scr->video_file_lbl_3, GUI_CTRL_LABEL);

    //Write codes video_file_img_13
    ui_scr->video_file_img_13 = lv_img_create(ui_scr->video_file_view_menu_b);
    lv_img_set_src(ui_scr->video_file_img_13, gui_get_res_path(GUI_RES_MENU_STA_PNG));
    lv_img_set_pivot(ui_scr->video_file_img_13, 0, 0);
    lv_img_set_angle(ui_scr->video_file_img_13, 0);
    lv_img_set_zoom(ui_scr->video_file_img_13, 256);
    lv_obj_set_pos(ui_scr->video_file_img_13, 0, 0);
    lv_obj_set_size(ui_scr->video_file_img_13, 800, 40);
    lv_obj_add_flag(ui_scr->video_file_img_13, LV_OBJ_FLAG_CLICKABLE);
    ui_style_set(ui_scr->video_file_img_13, GUI_CTRL_IMG);

    //Set style for video_file_img_13. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
    lv_obj_set_style_outline_opa(ui_scr->video_file_img_13, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

    //Write codes video_file_img_14
    ui_scr->video_file_img_14 = lv_img_create(ui_scr->video_file_view_menu_b);
    lv_img_set_src(ui_scr->video_file_img_14, gui_get_res_path(GUI_RES_MENU_STA_PNG));
    lv_img_set_pivot(ui_scr->video_file_img_14, 0, 0);
    lv_img_set_angle(ui_scr->video_file_img_14, 0);
    lv_img_set_zoom(ui_scr->video_file_img_14, 256);
    lv_obj_set_pos(ui_scr->video_file_img_14, 0, 440);
    lv_obj_set_size(ui_scr->video_file_img_14, 800, 40);
    lv_obj_add_flag(ui_scr->video_file_img_14, LV_OBJ_FLAG_CLICKABLE);
    ui_style_set(ui_scr->video_file_img_14, GUI_CTRL_IMG);

    //Set style for video_file_img_14. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
    lv_obj_set_style_outline_opa(ui_scr->video_file_img_14, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

    //Write codes video_file_img_15
    ui_scr->video_file_img_15 = lv_img_create(ui_scr->video_file_view_menu_b);
    lv_img_set_src(ui_scr->video_file_img_15, gui_get_res_path(GUI_RES_PLAY_PNG));
    lv_img_set_pivot(ui_scr->video_file_img_15, 0, 0);
    lv_img_set_angle(ui_scr->video_file_img_15, 0);
    lv_img_set_zoom(ui_scr->video_file_img_15, 256);
    lv_obj_set_pos(ui_scr->video_file_img_15, 9, 0);
    lv_obj_set_size(ui_scr->video_file_img_15, 39, 39);
    lv_obj_add_flag(ui_scr->video_file_img_15, LV_OBJ_FLAG_CLICKABLE);
    ui_style_set(ui_scr->video_file_img_15, GUI_CTRL_IMG);

    //Set style for video_file_img_15. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
    lv_obj_set_style_bg_color(ui_scr->video_file_img_15, lv_color_make(0x42, 0xA5, 0xF5), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_scr->video_file_img_15, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_outline_color(ui_scr->video_file_img_15, lv_color_make(0x42, 0xA5, 0xF5), LV_PART_MAIN | LV_STATE_DEFAULT);

    //Write codes video_file_img_16
    ui_scr->video_file_img_16 = lv_img_create(ui_scr->video_file_view_menu_b);
    lv_img_set_src(ui_scr->video_file_img_16, gui_get_res_path(GUI_RES_SET_PNG));
    lv_img_set_pivot(ui_scr->video_file_img_16, 0, 0);
    lv_img_set_angle(ui_scr->video_file_img_16, 0);
    lv_img_set_zoom(ui_scr->video_file_img_16, 256);
    lv_obj_set_pos(ui_scr->video_file_img_16, 70, 1);
    lv_obj_set_size(ui_scr->video_file_img_16, 37, 37);
    lv_obj_add_flag(ui_scr->video_file_img_16, LV_OBJ_FLAG_CLICKABLE);
    ui_style_set(ui_scr->video_file_img_16, GUI_CTRL_IMG);

    //Set style for video_file_img_16. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
    lv_obj_set_style_bg_color(ui_scr->video_file_img_16, lv_color_make(0x42, 0xA5, 0xF5), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_outline_color(ui_scr->video_file_img_16, lv_color_make(0x42, 0xA5, 0xF5), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_outline_opa(ui_scr->video_file_img_16, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    //Write codes video_file_img_17
    ui_scr->video_file_img_17 = lv_img_create(ui_scr->video_file_view_menu_b);
    lv_img_set_src(ui_scr->video_file_img_17, gui_get_res_path(GUI_RES_LEFT_PNG));
    lv_img_set_pivot(ui_scr->video_file_img_17, 0, 0);
    lv_img_set_angle(ui_scr->video_file_img_17, 0);
    lv_img_set_zoom(ui_scr->video_file_img_17, 256);
    lv_obj_set_pos(ui_scr->video_file_img_17, 200, 445);
    lv_obj_set_size(ui_scr->video_file_img_17, 21, 29);
    lv_obj_add_flag(ui_scr->video_file_img_17, LV_OBJ_FLAG_CLICKABLE);
    ui_style_set(ui_scr->video_file_img_17, GUI_CTRL_IMG);

    //Write codes video_file_img_18
    ui_scr->video_file_img_18 = lv_img_create(ui_scr->video_file_view_menu_b);
    lv_img_set_src(ui_scr->video_file_img_18, gui_get_res_path(GUI_RES_UP_PNG));
    lv_img_set_pivot(ui_scr->video_file_img_18, 0, 0);
    lv_img_set_angle(ui_scr->video_file_img_18, 0);
    lv_img_set_zoom(ui_scr->video_file_img_18, 256);
    lv_obj_set_pos(ui_scr->video_file_img_18, 321, 448);
    lv_obj_set_size(ui_scr->video_file_img_18, 29, 21);
    lv_obj_add_flag(ui_scr->video_file_img_18, LV_OBJ_FLAG_CLICKABLE);
    ui_style_set(ui_scr->video_file_img_18, GUI_CTRL_IMG);

    //Write codes video_file_img_19
    ui_scr->video_file_img_19 = lv_img_create(ui_scr->video_file_view_menu_b);
    lv_img_set_src(ui_scr->video_file_img_19, gui_get_res_path(GUI_RES_DOWN_PNG));
    lv_img_set_pivot(ui_scr->video_file_img_19, 0, 0);
    lv_img_set_angle(ui_scr->video_file_img_19, 0);
    lv_img_set_zoom(ui_scr->video_file_img_19, 256);
    lv_obj_set_pos(ui_scr->video_file_img_19, 450, 448);
    lv_obj_set_size(ui_scr->video_file_img_19, 29, 21);
    lv_obj_add_flag(ui_scr->video_file_img_19, LV_OBJ_FLAG_CLICKABLE);
    ui_style_set(ui_scr->video_file_img_19, GUI_CTRL_IMG);

    //Write codes video_file_img_20
    ui_scr->video_file_img_20 = lv_img_create(ui_scr->video_file_view_menu_b);
    lv_img_set_src(ui_scr->video_file_img_20, gui_get_res_path(GUI_RES_RIGHT_PNG));
    lv_img_set_pivot(ui_scr->video_file_img_20, 0, 0);
    lv_img_set_angle(ui_scr->video_file_img_20, 0);
    lv_img_set_zoom(ui_scr->video_file_img_20, 256);
    lv_obj_set_pos(ui_scr->video_file_img_20, 579, 445);
    lv_obj_set_size(ui_scr->video_file_img_20, 21, 29);
    lv_obj_add_flag(ui_scr->video_file_img_20, LV_OBJ_FLAG_CLICKABLE);
    ui_style_set(ui_scr->video_file_img_20, GUI_CTRL_IMG);

    //Write codes video_file_view_submenu
    ui_scr->video_file_view_submenu = lv_obj_create(ui_scr->video_file);
    lv_obj_set_pos(ui_scr->video_file_view_submenu, 111, 83);
    lv_obj_set_size(ui_scr->video_file_view_submenu, 590, 314);
    lv_obj_set_scrollbar_mode(ui_scr->video_file_view_submenu, LV_SCROLLBAR_MODE_OFF);
    lv_obj_add_flag(ui_scr->video_file_view_submenu, LV_OBJ_FLAG_HIDDEN);
    ui_style_set(ui_scr->video_file_view_submenu, GUI_CTRL_CONT);

    //Set style for video_file_view_submenu. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
    lv_obj_set_style_bg_color(ui_scr->video_file_view_submenu, lv_color_make(0x75, 0x75, 0x75), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_scr->video_file_view_submenu, 250, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui_scr->video_file_view_submenu, 2, LV_PART_MAIN | LV_STATE_DEFAULT);

    //Delete extra default style for video_file_view_submenu
    lv_obj_remove_style(ui_scr->video_file_view_submenu, &gui_cont_main_focus_key_style, LV_PART_MAIN | LV_STATE_FOCUS_KEY);

    //Write codes video_file_submenu_btn_1
    ui_scr->video_file_submenu_btn_1 = lv_btn_create(ui_scr->video_file_view_submenu);
    lv_obj_set_pos(ui_scr->video_file_submenu_btn_1, 83, 44);
    lv_obj_set_size(ui_scr->video_file_submenu_btn_1, 438, 37);
    lv_obj_set_scrollbar_mode(ui_scr->video_file_submenu_btn_1, LV_SCROLLBAR_MODE_OFF);
    lv_obj_add_flag(ui_scr->video_file_submenu_btn_1, LV_OBJ_FLAG_EVENT_BUBBLE | LV_OBJ_FLAG_CLICKABLE);
    ui_style_set(ui_scr->video_file_submenu_btn_1, GUI_CTRL_BUTTON);

    //Set style for video_file_submenu_btn_1. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
    lv_obj_set_style_bg_opa(ui_scr->video_file_submenu_btn_1, 203, LV_PART_MAIN | LV_STATE_DEFAULT);
    ui_scr->video_file_submenu_btn_1_label = lv_label_create(ui_scr->video_file_submenu_btn_1);
    lv_label_set_text(ui_scr->video_file_submenu_btn_1_label, "button1");
    lv_obj_set_style_pad_all(ui_scr->video_file_submenu_btn_1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_align(ui_scr->video_file_submenu_btn_1_label, LV_ALIGN_CENTER, 0, 0);

    //Write codes video_file_submenu_btn_2
    ui_scr->video_file_submenu_btn_2 = lv_btn_create(ui_scr->video_file_view_submenu);
    lv_obj_set_pos(ui_scr->video_file_submenu_btn_2, 83, 111);
    lv_obj_set_size(ui_scr->video_file_submenu_btn_2, 438, 37);
    lv_obj_set_scrollbar_mode(ui_scr->video_file_submenu_btn_2, LV_SCROLLBAR_MODE_OFF);
    lv_obj_add_flag(ui_scr->video_file_submenu_btn_2, LV_OBJ_FLAG_EVENT_BUBBLE | LV_OBJ_FLAG_CLICKABLE);
    ui_style_set(ui_scr->video_file_submenu_btn_2, GUI_CTRL_BUTTON);

    //Set style for video_file_submenu_btn_2. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
    lv_obj_set_style_bg_opa(ui_scr->video_file_submenu_btn_2, 215, LV_PART_MAIN | LV_STATE_DEFAULT);
    ui_scr->video_file_submenu_btn_2_label = lv_label_create(ui_scr->video_file_submenu_btn_2);
    lv_label_set_text(ui_scr->video_file_submenu_btn_2_label, "button2");
    lv_obj_set_style_pad_all(ui_scr->video_file_submenu_btn_2, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_align(ui_scr->video_file_submenu_btn_2_label, LV_ALIGN_CENTER, 0, 0);

    //Write codes video_file_submenu_btn_3
    ui_scr->video_file_submenu_btn_3 = lv_btn_create(ui_scr->video_file_view_submenu);
    lv_obj_set_pos(ui_scr->video_file_submenu_btn_3, 83, 171);
    lv_obj_set_size(ui_scr->video_file_submenu_btn_3, 438, 37);
    lv_obj_set_scrollbar_mode(ui_scr->video_file_submenu_btn_3, LV_SCROLLBAR_MODE_OFF);
    lv_obj_add_flag(ui_scr->video_file_submenu_btn_3, LV_OBJ_FLAG_EVENT_BUBBLE | LV_OBJ_FLAG_CLICKABLE);
    ui_style_set(ui_scr->video_file_submenu_btn_3, GUI_CTRL_BUTTON);

    //Set style for video_file_submenu_btn_3. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
    lv_obj_set_style_bg_opa(ui_scr->video_file_submenu_btn_3, 205, LV_PART_MAIN | LV_STATE_DEFAULT);
    ui_scr->video_file_submenu_btn_3_label = lv_label_create(ui_scr->video_file_submenu_btn_3);
    lv_label_set_text(ui_scr->video_file_submenu_btn_3_label, "button3");
    lv_obj_set_style_pad_all(ui_scr->video_file_submenu_btn_3, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_align(ui_scr->video_file_submenu_btn_3_label, LV_ALIGN_CENTER, 0, 0);

    //Write codes video_file_submenu_btn_4
    ui_scr->video_file_submenu_btn_4 = lv_btn_create(ui_scr->video_file_view_submenu);
    lv_obj_set_pos(ui_scr->video_file_submenu_btn_4, 83, 233);
    lv_obj_set_size(ui_scr->video_file_submenu_btn_4, 438, 37);
    lv_obj_set_scrollbar_mode(ui_scr->video_file_submenu_btn_4, LV_SCROLLBAR_MODE_OFF);
    lv_obj_add_flag(ui_scr->video_file_submenu_btn_4, LV_OBJ_FLAG_EVENT_BUBBLE | LV_OBJ_FLAG_CLICKABLE);
    ui_style_set(ui_scr->video_file_submenu_btn_4, GUI_CTRL_BUTTON);

    //Set style for video_file_submenu_btn_4. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
    lv_obj_set_style_bg_opa(ui_scr->video_file_submenu_btn_4, 205, LV_PART_MAIN | LV_STATE_DEFAULT);
    ui_scr->video_file_submenu_btn_4_label = lv_label_create(ui_scr->video_file_submenu_btn_4);
    lv_label_set_text(ui_scr->video_file_submenu_btn_4_label, "button4");
    lv_obj_set_style_pad_all(ui_scr->video_file_submenu_btn_4, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_align(ui_scr->video_file_submenu_btn_4_label, LV_ALIGN_CENTER, 0, 0);

    //Write codes video_file_lbl_submenu_warning
    ui_scr->video_file_lbl_submenu_warning = lv_label_create(ui_scr->video_file_view_submenu);
    lv_label_set_text(ui_scr->video_file_lbl_submenu_warning, "删除当前文件？");
    lv_label_set_long_mode(ui_scr->video_file_lbl_submenu_warning, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui_scr->video_file_lbl_submenu_warning, 79, 40);
    lv_obj_set_size(ui_scr->video_file_lbl_submenu_warning, 445, 112);
    lv_obj_set_scrollbar_mode(ui_scr->video_file_lbl_submenu_warning, LV_SCROLLBAR_MODE_OFF);
    lv_obj_add_flag(ui_scr->video_file_lbl_submenu_warning, LV_OBJ_FLAG_HIDDEN);
    ui_style_set(ui_scr->video_file_lbl_submenu_warning, GUI_CTRL_LABEL);

    //Set style for video_file_lbl_submenu_warning. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
    lv_obj_set_style_text_align(ui_scr->video_file_lbl_submenu_warning, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui_scr->video_file_lbl_submenu_warning, 8, LV_PART_MAIN | LV_STATE_DEFAULT);

    lv_obj_update_layout(ui_scr->video_file);
    ui_scr->video_file_del = false;
    i18n_refresh_texts(GUI_SCREEN_VIDEO_FILE);

    //Init events for screen
    events_init_video_file(ui);
    return ui_scr->video_file;
}
void unload_scr_video_file(lv_ui *ui)
{
    ui_free_scr_ptr(ui, GUI_SCREEN_VIDEO_FILE);
}

#endif
