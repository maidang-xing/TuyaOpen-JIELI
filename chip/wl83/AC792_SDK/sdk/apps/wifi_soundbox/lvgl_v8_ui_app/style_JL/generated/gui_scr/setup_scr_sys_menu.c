/*Generate Code, Do NOT Edit!*/
#include "lvgl.h"
#if LV_USE_GUIBUILDER_SIMULATOR
#include <stdio.h>
#endif
#include <stdlib.h>
#include "../gui_guider.h"
#include "../gui_events/events_init.h"
#include "../gui_events/callback_handler.h"
#include "../gui_timelines/gui_timelines.h"
#include "../../custom/custom.h"


lv_obj_t *setup_scr_sys_menu(lv_ui *ui)
{
    lv_ui_sys_menu *ui_scr = ui_get_scr_ptr(ui, GUI_SCREEN_SYS_MENU);
    if (ui_scr == NULL) {
        ui_scr = lv_mem_alloc(sizeof(lv_ui_sys_menu));
        if (ui_scr == NULL) {
            return NULL;
        }
        memset(ui_scr, 0, sizeof(lv_ui_sys_menu));
        ui->sys_menu = ui_scr;
    }

    //Write codes sys_menu
    ui_scr->sys_menu = lv_obj_create(NULL);
    lv_obj_set_scrollbar_mode(ui_scr->sys_menu, LV_SCROLLBAR_MODE_OFF);
    ui_style_set(ui_scr->sys_menu, GUI_CTRL_SCR);

    //Set style for sys_menu. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
    lv_obj_set_style_bg_color(ui_scr->sys_menu, lv_color_make(0xFF, 0xFF, 0xFF), LV_PART_MAIN | LV_STATE_DEFAULT);

    //Write codes sys_menu_view_1
    ui_scr->sys_menu_view_1 = lv_obj_create(ui_scr->sys_menu);
    lv_obj_set_pos(ui_scr->sys_menu_view_1, 12, 58);
    lv_obj_set_size(ui_scr->sys_menu_view_1, 100, 158);
    lv_obj_set_scrollbar_mode(ui_scr->sys_menu_view_1, LV_SCROLLBAR_MODE_OFF);
    ui_style_set(ui_scr->sys_menu_view_1, GUI_CTRL_CONT);

    //Write codes sys_menu_img_1
    ui_scr->sys_menu_img_1 = lv_img_create(ui_scr->sys_menu_view_1);
    lv_img_set_src(ui_scr->sys_menu_img_1, gui_get_res_path(GUI_RES_IMAGE_4150274_3_PNG));
    lv_img_set_pivot(ui_scr->sys_menu_img_1, 0, 0);
    lv_img_set_angle(ui_scr->sys_menu_img_1, 0);
    lv_img_set_zoom(ui_scr->sys_menu_img_1, 256);
    lv_obj_set_pos(ui_scr->sys_menu_img_1, 17, 23);
    lv_obj_set_size(ui_scr->sys_menu_img_1, 64, 64);
    lv_obj_add_flag(ui_scr->sys_menu_img_1, LV_OBJ_FLAG_CLICKABLE | LV_OBJ_FLAG_EVENT_BUBBLE);
    ui_style_set(ui_scr->sys_menu_img_1, GUI_CTRL_IMG);

    //Write codes sys_menu_lbl_1
    ui_scr->sys_menu_lbl_1 = lv_label_create(ui_scr->sys_menu_view_1);
    lv_label_set_text(ui_scr->sys_menu_lbl_1, "首页");
    lv_label_set_long_mode(ui_scr->sys_menu_lbl_1, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui_scr->sys_menu_lbl_1, 3, 105);
    lv_obj_set_size(ui_scr->sys_menu_lbl_1, 97, 49);
    lv_obj_set_scrollbar_mode(ui_scr->sys_menu_lbl_1, LV_SCROLLBAR_MODE_OFF);
    lv_obj_add_flag(ui_scr->sys_menu_lbl_1, LV_OBJ_FLAG_EVENT_BUBBLE);
    ui_style_set(ui_scr->sys_menu_lbl_1, GUI_CTRL_LABEL);

    //Set style for sys_menu_lbl_1. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
    lv_obj_set_style_text_color(ui_scr->sys_menu_lbl_1, lv_color_make(0x7E, 0x7E, 0x7E), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui_scr->sys_menu_lbl_1, 8, LV_PART_MAIN | LV_STATE_DEFAULT);

    //Write codes sys_menu_view_2
    ui_scr->sys_menu_view_2 = lv_obj_create(ui_scr->sys_menu);
    lv_obj_set_pos(ui_scr->sys_menu_view_2, 122, 58);
    lv_obj_set_size(ui_scr->sys_menu_view_2, 100, 158);
    lv_obj_set_scrollbar_mode(ui_scr->sys_menu_view_2, LV_SCROLLBAR_MODE_OFF);
    ui_style_set(ui_scr->sys_menu_view_2, GUI_CTRL_CONT);

    //Write codes sys_menu_img_2
    ui_scr->sys_menu_img_2 = lv_img_create(ui_scr->sys_menu_view_2);
    lv_img_set_src(ui_scr->sys_menu_img_2, gui_get_res_path(GUI_RES_WIFI_PNG));
    lv_img_set_pivot(ui_scr->sys_menu_img_2, 0, 0);
    lv_img_set_angle(ui_scr->sys_menu_img_2, 0);
    lv_img_set_zoom(ui_scr->sys_menu_img_2, 256);
    lv_obj_set_pos(ui_scr->sys_menu_img_2, 21, 23);
    lv_obj_set_size(ui_scr->sys_menu_img_2, 64, 64);
    lv_obj_add_flag(ui_scr->sys_menu_img_2, LV_OBJ_FLAG_EVENT_BUBBLE | LV_OBJ_FLAG_CLICKABLE);
    ui_style_set(ui_scr->sys_menu_img_2, GUI_CTRL_IMG);

    //Write codes sys_menu_lbl_2
    ui_scr->sys_menu_lbl_2 = lv_label_create(ui_scr->sys_menu_view_2);
    lv_label_set_text(ui_scr->sys_menu_lbl_2, "WIFI名称");
    lv_label_set_long_mode(ui_scr->sys_menu_lbl_2, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui_scr->sys_menu_lbl_2, 3, 97);
    lv_obj_set_size(ui_scr->sys_menu_lbl_2, 97, 57);
    lv_obj_set_scrollbar_mode(ui_scr->sys_menu_lbl_2, LV_SCROLLBAR_MODE_OFF);
    lv_obj_add_flag(ui_scr->sys_menu_lbl_2, LV_OBJ_FLAG_EVENT_BUBBLE);
    ui_style_set(ui_scr->sys_menu_lbl_2, GUI_CTRL_LABEL);

    //Set style for sys_menu_lbl_2. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
    lv_obj_set_style_text_color(ui_scr->sys_menu_lbl_2, lv_color_make(0x7E, 0x7E, 0x7E), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui_scr->sys_menu_lbl_2, 8, LV_PART_MAIN | LV_STATE_DEFAULT);

    //Write codes sys_menu_view_3
    ui_scr->sys_menu_view_3 = lv_obj_create(ui_scr->sys_menu);
    lv_obj_set_pos(ui_scr->sys_menu_view_3, 232, 58);
    lv_obj_set_size(ui_scr->sys_menu_view_3, 100, 158);
    lv_obj_set_scrollbar_mode(ui_scr->sys_menu_view_3, LV_SCROLLBAR_MODE_OFF);
    ui_style_set(ui_scr->sys_menu_view_3, GUI_CTRL_CONT);

    //Write codes sys_menu_img_3
    ui_scr->sys_menu_img_3 = lv_img_create(ui_scr->sys_menu_view_3);
    lv_img_set_src(ui_scr->sys_menu_img_3, gui_get_res_path(GUI_RES_IMAGE_4150274_5_PNG));
    lv_img_set_pivot(ui_scr->sys_menu_img_3, 0, 0);
    lv_img_set_angle(ui_scr->sys_menu_img_3, 0);
    lv_img_set_zoom(ui_scr->sys_menu_img_3, 256);
    lv_obj_set_pos(ui_scr->sys_menu_img_3, 16, 23);
    lv_obj_set_size(ui_scr->sys_menu_img_3, 64, 64);
    lv_obj_add_flag(ui_scr->sys_menu_img_3, LV_OBJ_FLAG_CLICKABLE | LV_OBJ_FLAG_EVENT_BUBBLE);
    ui_style_set(ui_scr->sys_menu_img_3, GUI_CTRL_IMG);

    //Write codes sys_menu_lbl_3
    ui_scr->sys_menu_lbl_3 = lv_label_create(ui_scr->sys_menu_view_3);
    lv_label_set_text(ui_scr->sys_menu_lbl_3, "麦克风");
    lv_label_set_long_mode(ui_scr->sys_menu_lbl_3, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui_scr->sys_menu_lbl_3, 3, 105);
    lv_obj_set_size(ui_scr->sys_menu_lbl_3, 95, 49);
    lv_obj_set_scrollbar_mode(ui_scr->sys_menu_lbl_3, LV_SCROLLBAR_MODE_OFF);
    lv_obj_add_flag(ui_scr->sys_menu_lbl_3, LV_OBJ_FLAG_EVENT_BUBBLE);
    ui_style_set(ui_scr->sys_menu_lbl_3, GUI_CTRL_LABEL);

    //Set style for sys_menu_lbl_3. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
    lv_obj_set_style_text_color(ui_scr->sys_menu_lbl_3, lv_color_make(0x7E, 0x7E, 0x7E), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui_scr->sys_menu_lbl_3, 8, LV_PART_MAIN | LV_STATE_DEFAULT);

    //Write codes sys_menu_view_4
    ui_scr->sys_menu_view_4 = lv_obj_create(ui_scr->sys_menu);
    lv_obj_set_pos(ui_scr->sys_menu_view_4, 342, 58);
    lv_obj_set_size(ui_scr->sys_menu_view_4, 100, 158);
    lv_obj_set_scrollbar_mode(ui_scr->sys_menu_view_4, LV_SCROLLBAR_MODE_OFF);
    ui_style_set(ui_scr->sys_menu_view_4, GUI_CTRL_CONT);

    //Write codes sys_menu_img_4
    ui_scr->sys_menu_img_4 = lv_img_create(ui_scr->sys_menu_view_4);
    lv_img_set_src(ui_scr->sys_menu_img_4, gui_get_res_path(GUI_RES_IMAGE_4150274_8_PNG));
    lv_img_set_pivot(ui_scr->sys_menu_img_4, 0, 0);
    lv_img_set_angle(ui_scr->sys_menu_img_4, 0);
    lv_img_set_zoom(ui_scr->sys_menu_img_4, 256);
    lv_obj_set_pos(ui_scr->sys_menu_img_4, 20, 23);
    lv_obj_set_size(ui_scr->sys_menu_img_4, 64, 64);
    lv_obj_add_flag(ui_scr->sys_menu_img_4, LV_OBJ_FLAG_CLICKABLE | LV_OBJ_FLAG_EVENT_BUBBLE);
    ui_style_set(ui_scr->sys_menu_img_4, GUI_CTRL_IMG);

    //Write codes sys_menu_lbl_4
    ui_scr->sys_menu_lbl_4 = lv_label_create(ui_scr->sys_menu_view_4);
    lv_label_set_text(ui_scr->sys_menu_lbl_4, "搜索");
    lv_label_set_long_mode(ui_scr->sys_menu_lbl_4, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui_scr->sys_menu_lbl_4, 3, 105);
    lv_obj_set_size(ui_scr->sys_menu_lbl_4, 92, 49);
    lv_obj_set_scrollbar_mode(ui_scr->sys_menu_lbl_4, LV_SCROLLBAR_MODE_OFF);
    lv_obj_add_flag(ui_scr->sys_menu_lbl_4, LV_OBJ_FLAG_EVENT_BUBBLE);
    ui_style_set(ui_scr->sys_menu_lbl_4, GUI_CTRL_LABEL);

    //Set style for sys_menu_lbl_4. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
    lv_obj_set_style_text_color(ui_scr->sys_menu_lbl_4, lv_color_make(0x7E, 0x7E, 0x7E), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui_scr->sys_menu_lbl_4, 8, LV_PART_MAIN | LV_STATE_DEFAULT);

    //Write codes sys_menu_view_5
    ui_scr->sys_menu_view_5 = lv_obj_create(ui_scr->sys_menu);
    lv_obj_set_pos(ui_scr->sys_menu_view_5, 452, 58);
    lv_obj_set_size(ui_scr->sys_menu_view_5, 100, 158);
    lv_obj_set_scrollbar_mode(ui_scr->sys_menu_view_5, LV_SCROLLBAR_MODE_OFF);
    ui_style_set(ui_scr->sys_menu_view_5, GUI_CTRL_CONT);

    //Write codes sys_menu_img_5
    ui_scr->sys_menu_img_5 = lv_img_create(ui_scr->sys_menu_view_5);
    lv_img_set_src(ui_scr->sys_menu_img_5, gui_get_res_path(GUI_RES_SHEZHI_PNG));
    lv_img_set_pivot(ui_scr->sys_menu_img_5, 0, 0);
    lv_img_set_angle(ui_scr->sys_menu_img_5, 0);
    lv_img_set_zoom(ui_scr->sys_menu_img_5, 256);
    lv_obj_set_pos(ui_scr->sys_menu_img_5, 16, 23);
    lv_obj_set_size(ui_scr->sys_menu_img_5, 64, 64);
    lv_obj_add_flag(ui_scr->sys_menu_img_5, LV_OBJ_FLAG_CLICKABLE | LV_OBJ_FLAG_EVENT_BUBBLE);
    ui_style_set(ui_scr->sys_menu_img_5, GUI_CTRL_IMG);

    //Write codes sys_menu_lbl_5
    ui_scr->sys_menu_lbl_5 = lv_label_create(ui_scr->sys_menu_view_5);
    lv_label_set_text(ui_scr->sys_menu_lbl_5, "设置");
    lv_label_set_long_mode(ui_scr->sys_menu_lbl_5, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui_scr->sys_menu_lbl_5, 0, 105);
    lv_obj_set_size(ui_scr->sys_menu_lbl_5, 100, 49);
    lv_obj_set_scrollbar_mode(ui_scr->sys_menu_lbl_5, LV_SCROLLBAR_MODE_OFF);
    lv_obj_add_flag(ui_scr->sys_menu_lbl_5, LV_OBJ_FLAG_EVENT_BUBBLE);
    ui_style_set(ui_scr->sys_menu_lbl_5, GUI_CTRL_LABEL);

    //Set style for sys_menu_lbl_5. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
    lv_obj_set_style_text_color(ui_scr->sys_menu_lbl_5, lv_color_make(0x7E, 0x7E, 0x7E), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui_scr->sys_menu_lbl_5, 8, LV_PART_MAIN | LV_STATE_DEFAULT);

    //Write codes sys_menu_slider_2
    ui_scr->sys_menu_slider_2 = lv_slider_create(ui_scr->sys_menu);
    lv_obj_set_pos(ui_scr->sys_menu_slider_2, 562, 65);
    lv_obj_set_size(ui_scr->sys_menu_slider_2, 230, 58);
    lv_obj_set_scrollbar_mode(ui_scr->sys_menu_slider_2, LV_SCROLLBAR_MODE_OFF);
    ui_style_set(ui_scr->sys_menu_slider_2, GUI_CTRL_SLIDER);

    //Set style for sys_menu_slider_2. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
    lv_obj_set_style_radius(ui_scr->sys_menu_slider_2, 15, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui_scr->sys_menu_slider_2, lv_color_make(0xE9, 0xE9, 0xE9), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_color(ui_scr->sys_menu_slider_2, lv_color_make(0x21, 0x95, 0xF6), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_opa(ui_scr->sys_menu_slider_2, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_outline_color(ui_scr->sys_menu_slider_2, lv_color_make(0x21, 0x95, 0xF6), LV_PART_MAIN | LV_STATE_DEFAULT);

    //Set style for sys_menu_slider_2. Part: LV_PART_INDICATOR, State: LV_STATE_DEFAULT
    lv_obj_set_style_radius(ui_scr->sys_menu_slider_2, 15, LV_PART_INDICATOR | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui_scr->sys_menu_slider_2, lv_color_make(0x7E, 0x7E, 0x7E), LV_PART_INDICATOR | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_scr->sys_menu_slider_2, 77, LV_PART_INDICATOR | LV_STATE_DEFAULT);

    //Set style for sys_menu_slider_2. Part: LV_PART_KNOB, State: LV_STATE_DEFAULT
    lv_obj_set_style_radius(ui_scr->sys_menu_slider_2, 15, LV_PART_KNOB | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui_scr->sys_menu_slider_2, lv_color_make(0x7E, 0x7E, 0x7E), LV_PART_KNOB | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_scr->sys_menu_slider_2, 0, LV_PART_KNOB | LV_STATE_DEFAULT);
    lv_slider_set_range(ui_scr->sys_menu_slider_2, 0, 100);
    lv_slider_set_mode(ui_scr->sys_menu_slider_2, LV_SLIDER_MODE_NORMAL);
    lv_slider_set_value(ui_scr->sys_menu_slider_2, 50, LV_ANIM_OFF);
    lv_slider_set_left_value(ui_scr->sys_menu_slider_2, 0, LV_ANIM_OFF);

    //Write codes sys_menu_slider_1
    ui_scr->sys_menu_slider_1 = lv_slider_create(ui_scr->sys_menu);
    lv_obj_set_pos(ui_scr->sys_menu_slider_1, 562, 149);
    lv_obj_set_size(ui_scr->sys_menu_slider_1, 230, 58);
    lv_obj_set_scrollbar_mode(ui_scr->sys_menu_slider_1, LV_SCROLLBAR_MODE_OFF);
    lv_obj_clear_flag(ui_scr->sys_menu_slider_1, LV_OBJ_FLAG_EVENT_BUBBLE);
    ui_style_set(ui_scr->sys_menu_slider_1, GUI_CTRL_SLIDER);

    //Set style for sys_menu_slider_1. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
    lv_obj_set_style_radius(ui_scr->sys_menu_slider_1, 15, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui_scr->sys_menu_slider_1, lv_color_make(0xE9, 0xE9, 0xE9), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_color(ui_scr->sys_menu_slider_1, lv_color_make(0x21, 0x95, 0xF6), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_opa(ui_scr->sys_menu_slider_1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_outline_color(ui_scr->sys_menu_slider_1, lv_color_make(0x21, 0x95, 0xF6), LV_PART_MAIN | LV_STATE_DEFAULT);

    //Set style for sys_menu_slider_1. Part: LV_PART_INDICATOR, State: LV_STATE_DEFAULT
    lv_obj_set_style_radius(ui_scr->sys_menu_slider_1, 15, LV_PART_INDICATOR | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui_scr->sys_menu_slider_1, lv_color_make(0x7E, 0x7E, 0x7E), LV_PART_INDICATOR | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_scr->sys_menu_slider_1, 77, LV_PART_INDICATOR | LV_STATE_DEFAULT);

    //Set style for sys_menu_slider_1. Part: LV_PART_KNOB, State: LV_STATE_DEFAULT
    lv_obj_set_style_radius(ui_scr->sys_menu_slider_1, 15, LV_PART_KNOB | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui_scr->sys_menu_slider_1, lv_color_make(0x7E, 0x7E, 0x7E), LV_PART_KNOB | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_scr->sys_menu_slider_1, 0, LV_PART_KNOB | LV_STATE_DEFAULT);
    lv_slider_set_range(ui_scr->sys_menu_slider_1, 0, 100);
    lv_slider_set_mode(ui_scr->sys_menu_slider_1, LV_SLIDER_MODE_NORMAL);
    lv_slider_set_value(ui_scr->sys_menu_slider_1, 50, LV_ANIM_OFF);
    lv_slider_set_left_value(ui_scr->sys_menu_slider_1, 0, LV_ANIM_OFF);

    //Write codes sys_menu_img_6
    ui_scr->sys_menu_img_6 = lv_img_create(ui_scr->sys_menu);
    lv_img_set_src(ui_scr->sys_menu_img_6, gui_get_res_path(GUI_RES_IMAGE_4161193_1_PNG));
    lv_img_set_pivot(ui_scr->sys_menu_img_6, 0, 0);
    lv_img_set_angle(ui_scr->sys_menu_img_6, 0);
    lv_img_set_zoom(ui_scr->sys_menu_img_6, 256);
    lv_obj_set_pos(ui_scr->sys_menu_img_6, 576, 71);
    lv_obj_set_size(ui_scr->sys_menu_img_6, 48, 48);
    lv_obj_add_flag(ui_scr->sys_menu_img_6, LV_OBJ_FLAG_CLICKABLE);
    ui_style_set(ui_scr->sys_menu_img_6, GUI_CTRL_IMG);

    //Write codes sys_menu_img_7
    ui_scr->sys_menu_img_7 = lv_img_create(ui_scr->sys_menu);
    lv_img_set_src(ui_scr->sys_menu_img_7, gui_get_res_path(GUI_RES_IMAGE_4161390_0_PNG));
    lv_img_set_pivot(ui_scr->sys_menu_img_7, 0, 0);
    lv_img_set_angle(ui_scr->sys_menu_img_7, 0);
    lv_img_set_zoom(ui_scr->sys_menu_img_7, 200);
    lv_obj_set_pos(ui_scr->sys_menu_img_7, 583, 160);
    lv_obj_set_size(ui_scr->sys_menu_img_7, 49, 48);
    lv_obj_add_flag(ui_scr->sys_menu_img_7, LV_OBJ_FLAG_CLICKABLE);
    ui_style_set(ui_scr->sys_menu_img_7, GUI_CTRL_IMG);

    //Write codes sys_menu_view_6
    ui_scr->sys_menu_view_6 = lv_obj_create(ui_scr->sys_menu);
    lv_obj_set_pos(ui_scr->sys_menu_view_6, 20, 343);
    lv_obj_set_size(ui_scr->sys_menu_view_6, 760, 91);
    lv_obj_set_scrollbar_mode(ui_scr->sys_menu_view_6, LV_SCROLLBAR_MODE_OFF);
    ui_style_set(ui_scr->sys_menu_view_6, GUI_CTRL_CONT);

    //Write codes sys_menu_lbl_6
    ui_scr->sys_menu_lbl_6 = lv_label_create(ui_scr->sys_menu_view_6);
    lv_label_set_text(ui_scr->sys_menu_lbl_6, "正在播放：");
    lv_label_set_long_mode(ui_scr->sys_menu_lbl_6, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui_scr->sys_menu_lbl_6, 108, 31);
    lv_obj_set_size(ui_scr->sys_menu_lbl_6, 134, 49);
    lv_obj_set_scrollbar_mode(ui_scr->sys_menu_lbl_6, LV_SCROLLBAR_MODE_OFF);
    lv_obj_add_flag(ui_scr->sys_menu_lbl_6, LV_OBJ_FLAG_EVENT_BUBBLE);
    ui_style_set(ui_scr->sys_menu_lbl_6, GUI_CTRL_LABEL);

    //Set style for sys_menu_lbl_6. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
    lv_obj_set_style_text_color(ui_scr->sys_menu_lbl_6, lv_color_make(0x00, 0x00, 0x00), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui_scr->sys_menu_lbl_6, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui_scr->sys_menu_lbl_6, 8, LV_PART_MAIN | LV_STATE_DEFAULT);

    //Write codes sys_menu_lbl_8
    ui_scr->sys_menu_lbl_8 = lv_label_create(ui_scr->sys_menu_view_6);
    lv_label_set_text(ui_scr->sys_menu_lbl_8, "退出");
    lv_label_set_long_mode(ui_scr->sys_menu_lbl_8, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui_scr->sys_menu_lbl_8, 698, 22);
    lv_obj_set_size(ui_scr->sys_menu_lbl_8, 55, 49);
    lv_obj_set_scrollbar_mode(ui_scr->sys_menu_lbl_8, LV_SCROLLBAR_MODE_OFF);
    lv_obj_add_flag(ui_scr->sys_menu_lbl_8, LV_OBJ_FLAG_EVENT_BUBBLE);
    ui_style_set(ui_scr->sys_menu_lbl_8, GUI_CTRL_LABEL);

    //Set style for sys_menu_lbl_8. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
    lv_obj_set_style_text_color(ui_scr->sys_menu_lbl_8, lv_color_make(0x00, 0x00, 0x00), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui_scr->sys_menu_lbl_8, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui_scr->sys_menu_lbl_8, 8, LV_PART_MAIN | LV_STATE_DEFAULT);

    //Write codes sys_menu_imgbtn_4
    ui_scr->sys_menu_imgbtn_4 = lv_imgbtn_create(ui_scr->sys_menu_view_6);
    lv_obj_set_pos(ui_scr->sys_menu_imgbtn_4, 536, 14);
    lv_obj_set_size(ui_scr->sys_menu_imgbtn_4, 64, 64);
    lv_obj_set_scrollbar_mode(ui_scr->sys_menu_imgbtn_4, LV_SCROLLBAR_MODE_OFF);
    ui_style_set(ui_scr->sys_menu_imgbtn_4, GUI_CTRL_IMGBTN);

    //Set style for sys_menu_imgbtn_4. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
    lv_obj_set_style_img_recolor(ui_scr->sys_menu_imgbtn_4, lv_color_make(0x00, 0x00, 0x00), LV_PART_MAIN | LV_STATE_DEFAULT);

    //Set style for sys_menu_imgbtn_4. Part: LV_PART_MAIN, State: LV_STATE_FOCUSED
    lv_obj_add_style(ui_scr->sys_menu_imgbtn_4, &gui_imgbtn_main_focused_style, LV_PART_MAIN | LV_STATE_FOCUSED);

    //Set style for sys_menu_imgbtn_4. Part: LV_PART_MAIN, State: LV_STATE_PRESSED
    lv_obj_set_style_text_font(ui_scr->sys_menu_imgbtn_4, &lv_font_FangZhengKaiTiJianTi_1_24, LV_PART_MAIN | LV_STATE_PRESSED);
    lv_obj_set_style_img_recolor(ui_scr->sys_menu_imgbtn_4, lv_color_make(0x00, 0x00, 0x00), LV_PART_MAIN | LV_STATE_PRESSED);
    lv_obj_set_style_img_recolor_opa(ui_scr->sys_menu_imgbtn_4, 0, LV_PART_MAIN | LV_STATE_PRESSED);

    //Set style for sys_menu_imgbtn_4. Part: LV_PART_MAIN, State: LV_STATE_CHECKED
    lv_obj_set_style_text_font(ui_scr->sys_menu_imgbtn_4, &lv_font_FangZhengKaiTiJianTi_1_24, LV_PART_MAIN | LV_STATE_CHECKED);
    lv_imgbtn_set_src(ui_scr->sys_menu_imgbtn_4, LV_IMGBTN_STATE_RELEASED, NULL, gui_get_res_path(GUI_RES_IMAGE_4225207_0_PNG), NULL);
    lv_imgbtn_set_src(ui_scr->sys_menu_imgbtn_4, LV_IMGBTN_STATE_PRESSED, NULL, gui_get_res_path(GUI_RES_IMAGE_4225207_0_PNG), NULL);
    lv_imgbtn_set_src(ui_scr->sys_menu_imgbtn_4, LV_IMGBTN_STATE_CHECKED_RELEASED, NULL, gui_get_res_path(GUI_RES_IMAGE_4225207_1_PNG), NULL);
    lv_imgbtn_set_src(ui_scr->sys_menu_imgbtn_4, LV_IMGBTN_STATE_CHECKED_PRESSED, NULL, gui_get_res_path(GUI_RES_IMAGE_4225207_1_PNG), NULL);
    lv_obj_add_flag(ui_scr->sys_menu_imgbtn_4, LV_OBJ_FLAG_CHECKABLE);
    ui_scr->sys_menu_imgbtn_4_label = lv_label_create(ui_scr->sys_menu_imgbtn_4);
    lv_label_set_text(ui_scr->sys_menu_imgbtn_4_label, "");
    lv_obj_set_style_pad_all(ui_scr->sys_menu_imgbtn_4, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_align(ui_scr->sys_menu_imgbtn_4_label, LV_ALIGN_CENTER, 0, 0);

    //Write codes sys_menu_imgbtn_5
    ui_scr->sys_menu_imgbtn_5 = lv_imgbtn_create(ui_scr->sys_menu_view_6);
    lv_obj_set_pos(ui_scr->sys_menu_imgbtn_5, 613, 16);
    lv_obj_set_size(ui_scr->sys_menu_imgbtn_5, 64, 64);
    lv_obj_set_scrollbar_mode(ui_scr->sys_menu_imgbtn_5, LV_SCROLLBAR_MODE_OFF);
    ui_style_set(ui_scr->sys_menu_imgbtn_5, GUI_CTRL_IMGBTN);

    //Set style for sys_menu_imgbtn_5. Part: LV_PART_MAIN, State: LV_STATE_PRESSED
    lv_obj_set_style_bg_color(ui_scr->sys_menu_imgbtn_5, lv_color_make(0xAA, 0xAA, 0xAA), LV_PART_MAIN | LV_STATE_PRESSED);
    lv_imgbtn_set_src(ui_scr->sys_menu_imgbtn_5, LV_IMGBTN_STATE_RELEASED, NULL, gui_get_res_path(GUI_RES_IMAGE_4225207_2_PNG), NULL);
    lv_imgbtn_set_src(ui_scr->sys_menu_imgbtn_5, LV_IMGBTN_STATE_PRESSED, NULL, gui_get_res_path(GUI_RES_IMAGE_4225207_2_PNG), NULL);
    lv_imgbtn_set_src(ui_scr->sys_menu_imgbtn_5, LV_IMGBTN_STATE_CHECKED_RELEASED, NULL, gui_get_res_path(GUI_RES_IMAGE_4225207_2_PNG), NULL);
    lv_imgbtn_set_src(ui_scr->sys_menu_imgbtn_5, LV_IMGBTN_STATE_CHECKED_PRESSED, NULL, gui_get_res_path(GUI_RES_IMAGE_4225207_2_PNG), NULL);
    lv_obj_add_flag(ui_scr->sys_menu_imgbtn_5, LV_OBJ_FLAG_CHECKABLE);
    ui_scr->sys_menu_imgbtn_5_label = lv_label_create(ui_scr->sys_menu_imgbtn_5);
    lv_label_set_text(ui_scr->sys_menu_imgbtn_5_label, "");
    lv_obj_set_style_pad_all(ui_scr->sys_menu_imgbtn_5, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_align(ui_scr->sys_menu_imgbtn_5_label, LV_ALIGN_CENTER, 0, 0);

    //Write codes sys_menu_imgbtn_6
    ui_scr->sys_menu_imgbtn_6 = lv_imgbtn_create(ui_scr->sys_menu_view_6);
    lv_obj_set_pos(ui_scr->sys_menu_imgbtn_6, 447, 14);
    lv_obj_set_size(ui_scr->sys_menu_imgbtn_6, 64, 64);
    lv_obj_set_scrollbar_mode(ui_scr->sys_menu_imgbtn_6, LV_SCROLLBAR_MODE_OFF);
    ui_style_set(ui_scr->sys_menu_imgbtn_6, GUI_CTRL_IMGBTN);
    lv_imgbtn_set_src(ui_scr->sys_menu_imgbtn_6, LV_IMGBTN_STATE_RELEASED, NULL, gui_get_res_path(GUI_RES_IMAGE_4225207_3_PNG), NULL);
    lv_imgbtn_set_src(ui_scr->sys_menu_imgbtn_6, LV_IMGBTN_STATE_PRESSED, NULL, gui_get_res_path(GUI_RES_IMAGE_4225207_3_PNG), NULL);
    lv_imgbtn_set_src(ui_scr->sys_menu_imgbtn_6, LV_IMGBTN_STATE_CHECKED_RELEASED, NULL, gui_get_res_path(GUI_RES_IMAGE_4225207_3_PNG), NULL);
    lv_imgbtn_set_src(ui_scr->sys_menu_imgbtn_6, LV_IMGBTN_STATE_CHECKED_PRESSED, NULL, gui_get_res_path(GUI_RES_IMAGE_4225207_3_PNG), NULL);
    lv_obj_add_flag(ui_scr->sys_menu_imgbtn_6, LV_OBJ_FLAG_CHECKABLE);
    ui_scr->sys_menu_imgbtn_6_label = lv_label_create(ui_scr->sys_menu_imgbtn_6);
    lv_label_set_text(ui_scr->sys_menu_imgbtn_6_label, "");
    lv_obj_set_style_pad_all(ui_scr->sys_menu_imgbtn_6, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_align(ui_scr->sys_menu_imgbtn_6_label, LV_ALIGN_CENTER, 0, 0);

    //Write codes sys_menu_img_8
    ui_scr->sys_menu_img_8 = lv_img_create(ui_scr->sys_menu_view_6);
    lv_obj_set_pos(ui_scr->sys_menu_img_8, 18, 7);
    lv_obj_set_size(ui_scr->sys_menu_img_8, 200, 200);
    lv_obj_add_flag(ui_scr->sys_menu_img_8, LV_OBJ_FLAG_CLICKABLE);
    ui_style_set(ui_scr->sys_menu_img_8, GUI_CTRL_IMG);

    //Set style for sys_menu_img_8. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
    lv_obj_set_style_img_recolor(ui_scr->sys_menu_img_8, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_img_recolor_opa(ui_scr->sys_menu_img_8, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

    //Write codes sys_menu_view_song_info
    ui_scr->sys_menu_view_song_info = lv_obj_create(ui_scr->sys_menu_view_6);
    lv_obj_set_pos(ui_scr->sys_menu_view_song_info, 233, 24);
    lv_obj_set_size(ui_scr->sys_menu_view_song_info, 218, 59);
    lv_obj_set_scrollbar_mode(ui_scr->sys_menu_view_song_info, LV_SCROLLBAR_MODE_OFF);
    ui_style_set(ui_scr->sys_menu_view_song_info, GUI_CTRL_CONT);

    //Set style for sys_menu_view_song_info. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
    lv_obj_set_style_radius(ui_scr->sys_menu_view_song_info, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui_scr->sys_menu_view_song_info, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_scr->sys_menu_view_song_info, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

    lv_obj_update_layout(ui_scr->sys_menu);
    ui_scr->sys_menu_del = false;

    //Init events for screen
    events_init_sys_menu(ui);
    return ui_scr->sys_menu;
}
void unload_scr_sys_menu(lv_ui *ui)
{
    ui_free_scr_ptr(ui, GUI_SCREEN_SYS_MENU);
}
