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


lv_obj_t *setup_scr_eq_modify(lv_ui *ui)
{
    lv_ui_eq_modify *ui_scr = ui_get_scr_ptr(ui, GUI_SCREEN_EQ_MODIFY);
    if (ui_scr == NULL) {
        ui_scr = lv_mem_alloc(sizeof(lv_ui_eq_modify));
        if (ui_scr == NULL) {
            return NULL;
        }
        memset(ui_scr, 0, sizeof(lv_ui_eq_modify));
        ui->eq_modify = ui_scr;
    }

    //Write codes eq_modify
    ui_scr->eq_modify = lv_obj_create(NULL);
    lv_obj_set_scrollbar_mode(ui_scr->eq_modify, LV_SCROLLBAR_MODE_OFF);
    ui_style_set(ui_scr->eq_modify, GUI_CTRL_SCR);

    //Set style for eq_modify. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
    lv_obj_set_style_bg_color(ui_scr->eq_modify, lv_color_make(0xf7, 0xf9, 0xfc), LV_PART_MAIN | LV_STATE_DEFAULT);

    //Write codes eq_modify_slider_1
    ui_scr->eq_modify_slider_1 = lv_slider_create(ui_scr->eq_modify);
    lv_obj_set_pos(ui_scr->eq_modify_slider_1, 166, 93);
    lv_obj_set_size(ui_scr->eq_modify_slider_1, 12, 301);
    lv_obj_set_scrollbar_mode(ui_scr->eq_modify_slider_1, LV_SCROLLBAR_MODE_OFF);
    lv_obj_clear_flag(ui_scr->eq_modify_slider_1, LV_OBJ_FLAG_EVENT_BUBBLE);
    lv_obj_set_user_data(ui_scr->eq_modify_slider_1, "0");
    ui_style_set(ui_scr->eq_modify_slider_1, GUI_CTRL_SLIDER);
    lv_slider_set_range(ui_scr->eq_modify_slider_1, -18, 18);
    lv_slider_set_mode(ui_scr->eq_modify_slider_1, LV_SLIDER_MODE_NORMAL);
    lv_slider_set_value(ui_scr->eq_modify_slider_1, 0, LV_ANIM_OFF);
    lv_slider_set_left_value(ui_scr->eq_modify_slider_1, 0, LV_ANIM_OFF);

    //Write codes eq_modify_slider_2
    ui_scr->eq_modify_slider_2 = lv_slider_create(ui_scr->eq_modify);
    lv_obj_set_pos(ui_scr->eq_modify_slider_2, 230, 93);
    lv_obj_set_size(ui_scr->eq_modify_slider_2, 12, 301);
    lv_obj_set_scrollbar_mode(ui_scr->eq_modify_slider_2, LV_SCROLLBAR_MODE_OFF);
    lv_obj_clear_flag(ui_scr->eq_modify_slider_2, LV_OBJ_FLAG_EVENT_BUBBLE);
    lv_obj_set_user_data(ui_scr->eq_modify_slider_2, "1");
    ui_style_set(ui_scr->eq_modify_slider_2, GUI_CTRL_SLIDER);
    lv_slider_set_range(ui_scr->eq_modify_slider_2, -18, 18);
    lv_slider_set_mode(ui_scr->eq_modify_slider_2, LV_SLIDER_MODE_NORMAL);
    lv_slider_set_value(ui_scr->eq_modify_slider_2, 0, LV_ANIM_OFF);
    lv_slider_set_left_value(ui_scr->eq_modify_slider_2, 0, LV_ANIM_OFF);

    //Write codes eq_modify_slider_3
    ui_scr->eq_modify_slider_3 = lv_slider_create(ui_scr->eq_modify);
    lv_obj_set_pos(ui_scr->eq_modify_slider_3, 294, 93);
    lv_obj_set_size(ui_scr->eq_modify_slider_3, 12, 301);
    lv_obj_set_scrollbar_mode(ui_scr->eq_modify_slider_3, LV_SCROLLBAR_MODE_OFF);
    lv_obj_clear_flag(ui_scr->eq_modify_slider_3, LV_OBJ_FLAG_EVENT_BUBBLE);
    lv_obj_set_user_data(ui_scr->eq_modify_slider_3, "2");
    ui_style_set(ui_scr->eq_modify_slider_3, GUI_CTRL_SLIDER);
    lv_slider_set_range(ui_scr->eq_modify_slider_3, -18, 18);
    lv_slider_set_mode(ui_scr->eq_modify_slider_3, LV_SLIDER_MODE_NORMAL);
    lv_slider_set_value(ui_scr->eq_modify_slider_3, 0, LV_ANIM_OFF);
    lv_slider_set_left_value(ui_scr->eq_modify_slider_3, 0, LV_ANIM_OFF);

    //Write codes eq_modify_slider_4
    ui_scr->eq_modify_slider_4 = lv_slider_create(ui_scr->eq_modify);
    lv_obj_set_pos(ui_scr->eq_modify_slider_4, 358, 93);
    lv_obj_set_size(ui_scr->eq_modify_slider_4, 12, 301);
    lv_obj_set_scrollbar_mode(ui_scr->eq_modify_slider_4, LV_SCROLLBAR_MODE_OFF);
    lv_obj_clear_flag(ui_scr->eq_modify_slider_4, LV_OBJ_FLAG_EVENT_BUBBLE);
    lv_obj_set_user_data(ui_scr->eq_modify_slider_4, "3");
    ui_style_set(ui_scr->eq_modify_slider_4, GUI_CTRL_SLIDER);
    lv_slider_set_range(ui_scr->eq_modify_slider_4, -18, 18);
    lv_slider_set_mode(ui_scr->eq_modify_slider_4, LV_SLIDER_MODE_NORMAL);
    lv_slider_set_value(ui_scr->eq_modify_slider_4, 0, LV_ANIM_OFF);
    lv_slider_set_left_value(ui_scr->eq_modify_slider_4, 0, LV_ANIM_OFF);

    //Write codes eq_modify_slider_5
    ui_scr->eq_modify_slider_5 = lv_slider_create(ui_scr->eq_modify);
    lv_obj_set_pos(ui_scr->eq_modify_slider_5, 422, 93);
    lv_obj_set_size(ui_scr->eq_modify_slider_5, 12, 301);
    lv_obj_set_scrollbar_mode(ui_scr->eq_modify_slider_5, LV_SCROLLBAR_MODE_OFF);
    lv_obj_clear_flag(ui_scr->eq_modify_slider_5, LV_OBJ_FLAG_EVENT_BUBBLE);
    lv_obj_set_user_data(ui_scr->eq_modify_slider_5, "4");
    ui_style_set(ui_scr->eq_modify_slider_5, GUI_CTRL_SLIDER);
    lv_slider_set_range(ui_scr->eq_modify_slider_5, -18, 18);
    lv_slider_set_mode(ui_scr->eq_modify_slider_5, LV_SLIDER_MODE_NORMAL);
    lv_slider_set_value(ui_scr->eq_modify_slider_5, 0, LV_ANIM_OFF);
    lv_slider_set_left_value(ui_scr->eq_modify_slider_5, 0, LV_ANIM_OFF);

    //Write codes eq_modify_slider_6
    ui_scr->eq_modify_slider_6 = lv_slider_create(ui_scr->eq_modify);
    lv_obj_set_pos(ui_scr->eq_modify_slider_6, 486, 93);
    lv_obj_set_size(ui_scr->eq_modify_slider_6, 12, 301);
    lv_obj_set_scrollbar_mode(ui_scr->eq_modify_slider_6, LV_SCROLLBAR_MODE_OFF);
    lv_obj_clear_flag(ui_scr->eq_modify_slider_6, LV_OBJ_FLAG_EVENT_BUBBLE);
    lv_obj_set_user_data(ui_scr->eq_modify_slider_6, "5");
    ui_style_set(ui_scr->eq_modify_slider_6, GUI_CTRL_SLIDER);
    lv_slider_set_range(ui_scr->eq_modify_slider_6, -18, 18);
    lv_slider_set_mode(ui_scr->eq_modify_slider_6, LV_SLIDER_MODE_NORMAL);
    lv_slider_set_value(ui_scr->eq_modify_slider_6, 0, LV_ANIM_OFF);
    lv_slider_set_left_value(ui_scr->eq_modify_slider_6, 0, LV_ANIM_OFF);

    //Write codes eq_modify_slider_7
    ui_scr->eq_modify_slider_7 = lv_slider_create(ui_scr->eq_modify);
    lv_obj_set_pos(ui_scr->eq_modify_slider_7, 550, 93);
    lv_obj_set_size(ui_scr->eq_modify_slider_7, 12, 301);
    lv_obj_set_scrollbar_mode(ui_scr->eq_modify_slider_7, LV_SCROLLBAR_MODE_OFF);
    lv_obj_clear_flag(ui_scr->eq_modify_slider_7, LV_OBJ_FLAG_EVENT_BUBBLE);
    lv_obj_set_user_data(ui_scr->eq_modify_slider_7, "6");
    ui_style_set(ui_scr->eq_modify_slider_7, GUI_CTRL_SLIDER);
    lv_slider_set_range(ui_scr->eq_modify_slider_7, -18, 18);
    lv_slider_set_mode(ui_scr->eq_modify_slider_7, LV_SLIDER_MODE_NORMAL);
    lv_slider_set_value(ui_scr->eq_modify_slider_7, 0, LV_ANIM_OFF);
    lv_slider_set_left_value(ui_scr->eq_modify_slider_7, 0, LV_ANIM_OFF);

    //Write codes eq_modify_slider_8
    ui_scr->eq_modify_slider_8 = lv_slider_create(ui_scr->eq_modify);
    lv_obj_set_pos(ui_scr->eq_modify_slider_8, 614, 93);
    lv_obj_set_size(ui_scr->eq_modify_slider_8, 12, 301);
    lv_obj_set_scrollbar_mode(ui_scr->eq_modify_slider_8, LV_SCROLLBAR_MODE_OFF);
    lv_obj_clear_flag(ui_scr->eq_modify_slider_8, LV_OBJ_FLAG_EVENT_BUBBLE);
    lv_obj_set_user_data(ui_scr->eq_modify_slider_8, "7");
    ui_style_set(ui_scr->eq_modify_slider_8, GUI_CTRL_SLIDER);
    lv_slider_set_range(ui_scr->eq_modify_slider_8, -18, 18);
    lv_slider_set_mode(ui_scr->eq_modify_slider_8, LV_SLIDER_MODE_NORMAL);
    lv_slider_set_value(ui_scr->eq_modify_slider_8, 0, LV_ANIM_OFF);
    lv_slider_set_left_value(ui_scr->eq_modify_slider_8, 0, LV_ANIM_OFF);

    //Write codes eq_modify_slider_9
    ui_scr->eq_modify_slider_9 = lv_slider_create(ui_scr->eq_modify);
    lv_obj_set_pos(ui_scr->eq_modify_slider_9, 679, 93);
    lv_obj_set_size(ui_scr->eq_modify_slider_9, 12, 301);
    lv_obj_set_scrollbar_mode(ui_scr->eq_modify_slider_9, LV_SCROLLBAR_MODE_OFF);
    lv_obj_clear_flag(ui_scr->eq_modify_slider_9, LV_OBJ_FLAG_EVENT_BUBBLE);
    lv_obj_set_user_data(ui_scr->eq_modify_slider_9, "8");
    ui_style_set(ui_scr->eq_modify_slider_9, GUI_CTRL_SLIDER);
    lv_slider_set_range(ui_scr->eq_modify_slider_9, -18, 18);
    lv_slider_set_mode(ui_scr->eq_modify_slider_9, LV_SLIDER_MODE_NORMAL);
    lv_slider_set_value(ui_scr->eq_modify_slider_9, 0, LV_ANIM_OFF);
    lv_slider_set_left_value(ui_scr->eq_modify_slider_9, 0, LV_ANIM_OFF);

    //Write codes eq_modify_slider_10
    ui_scr->eq_modify_slider_10 = lv_slider_create(ui_scr->eq_modify);
    lv_obj_set_pos(ui_scr->eq_modify_slider_10, 743, 93);
    lv_obj_set_size(ui_scr->eq_modify_slider_10, 12, 301);
    lv_obj_set_scrollbar_mode(ui_scr->eq_modify_slider_10, LV_SCROLLBAR_MODE_OFF);
    lv_obj_clear_flag(ui_scr->eq_modify_slider_10, LV_OBJ_FLAG_EVENT_BUBBLE);
    lv_obj_set_user_data(ui_scr->eq_modify_slider_10, "9");
    ui_style_set(ui_scr->eq_modify_slider_10, GUI_CTRL_SLIDER);
    lv_slider_set_range(ui_scr->eq_modify_slider_10, -18, 18);
    lv_slider_set_mode(ui_scr->eq_modify_slider_10, LV_SLIDER_MODE_NORMAL);
    lv_slider_set_value(ui_scr->eq_modify_slider_10, 0, LV_ANIM_OFF);
    lv_slider_set_left_value(ui_scr->eq_modify_slider_10, 0, LV_ANIM_OFF);

    //Write codes eq_modify_lbl_1
    ui_scr->eq_modify_lbl_1 = lv_label_create(ui_scr->eq_modify);
    lv_label_set_text(ui_scr->eq_modify_lbl_1, "31");
    lv_label_set_long_mode(ui_scr->eq_modify_lbl_1, LV_LABEL_LONG_SCROLL);
    lv_obj_set_pos(ui_scr->eq_modify_lbl_1, 153, 422);
    lv_obj_set_size(ui_scr->eq_modify_lbl_1, 40, 29);
    lv_obj_set_scrollbar_mode(ui_scr->eq_modify_lbl_1, LV_SCROLLBAR_MODE_OFF);
    ui_style_set(ui_scr->eq_modify_lbl_1, GUI_CTRL_LABEL);

    //Write codes eq_modify_lbl_2
    ui_scr->eq_modify_lbl_2 = lv_label_create(ui_scr->eq_modify);
    lv_label_set_text(ui_scr->eq_modify_lbl_2, "63");
    lv_label_set_long_mode(ui_scr->eq_modify_lbl_2, LV_LABEL_LONG_SCROLL);
    lv_obj_set_pos(ui_scr->eq_modify_lbl_2, 213, 422);
    lv_obj_set_size(ui_scr->eq_modify_lbl_2, 40, 29);
    lv_obj_set_scrollbar_mode(ui_scr->eq_modify_lbl_2, LV_SCROLLBAR_MODE_OFF);
    ui_style_set(ui_scr->eq_modify_lbl_2, GUI_CTRL_LABEL);

    //Write codes eq_modify_lbl_3
    ui_scr->eq_modify_lbl_3 = lv_label_create(ui_scr->eq_modify);
    lv_label_set_text(ui_scr->eq_modify_lbl_3, "125");
    lv_label_set_long_mode(ui_scr->eq_modify_lbl_3, LV_LABEL_LONG_SCROLL);
    lv_obj_set_pos(ui_scr->eq_modify_lbl_3, 276, 422);
    lv_obj_set_size(ui_scr->eq_modify_lbl_3, 40, 29);
    lv_obj_set_scrollbar_mode(ui_scr->eq_modify_lbl_3, LV_SCROLLBAR_MODE_OFF);
    ui_style_set(ui_scr->eq_modify_lbl_3, GUI_CTRL_LABEL);

    //Write codes eq_modify_lbl_4
    ui_scr->eq_modify_lbl_4 = lv_label_create(ui_scr->eq_modify);
    lv_label_set_text(ui_scr->eq_modify_lbl_4, "250");
    lv_label_set_long_mode(ui_scr->eq_modify_lbl_4, LV_LABEL_LONG_SCROLL);
    lv_obj_set_pos(ui_scr->eq_modify_lbl_4, 346, 422);
    lv_obj_set_size(ui_scr->eq_modify_lbl_4, 40, 29);
    lv_obj_set_scrollbar_mode(ui_scr->eq_modify_lbl_4, LV_SCROLLBAR_MODE_OFF);
    ui_style_set(ui_scr->eq_modify_lbl_4, GUI_CTRL_LABEL);

    //Write codes eq_modify_lbl_5
    ui_scr->eq_modify_lbl_5 = lv_label_create(ui_scr->eq_modify);
    lv_label_set_text(ui_scr->eq_modify_lbl_5, "500");
    lv_label_set_long_mode(ui_scr->eq_modify_lbl_5, LV_LABEL_LONG_SCROLL);
    lv_obj_set_pos(ui_scr->eq_modify_lbl_5, 406, 422);
    lv_obj_set_size(ui_scr->eq_modify_lbl_5, 49, 29);
    lv_obj_set_scrollbar_mode(ui_scr->eq_modify_lbl_5, LV_SCROLLBAR_MODE_OFF);
    lv_obj_add_state(ui_scr->eq_modify_lbl_5, LV_STATE_DISABLED);
    ui_style_set(ui_scr->eq_modify_lbl_5, GUI_CTRL_LABEL);

    //Write codes eq_modify_lbl_6
    ui_scr->eq_modify_lbl_6 = lv_label_create(ui_scr->eq_modify);
    lv_label_set_text(ui_scr->eq_modify_lbl_6, "1k");
    lv_label_set_long_mode(ui_scr->eq_modify_lbl_6, LV_LABEL_LONG_SCROLL);
    lv_obj_set_pos(ui_scr->eq_modify_lbl_6, 476, 422);
    lv_obj_set_size(ui_scr->eq_modify_lbl_6, 40, 29);
    lv_obj_set_scrollbar_mode(ui_scr->eq_modify_lbl_6, LV_SCROLLBAR_MODE_OFF);
    ui_style_set(ui_scr->eq_modify_lbl_6, GUI_CTRL_LABEL);

    //Write codes eq_modify_lbl_7
    ui_scr->eq_modify_lbl_7 = lv_label_create(ui_scr->eq_modify);
    lv_label_set_text(ui_scr->eq_modify_lbl_7, "2k");
    lv_label_set_long_mode(ui_scr->eq_modify_lbl_7, LV_LABEL_LONG_SCROLL);
    lv_obj_set_pos(ui_scr->eq_modify_lbl_7, 540, 422);
    lv_obj_set_size(ui_scr->eq_modify_lbl_7, 40, 31);
    lv_obj_set_scrollbar_mode(ui_scr->eq_modify_lbl_7, LV_SCROLLBAR_MODE_OFF);
    ui_style_set(ui_scr->eq_modify_lbl_7, GUI_CTRL_LABEL);

    //Write codes eq_modify_lbl_8
    ui_scr->eq_modify_lbl_8 = lv_label_create(ui_scr->eq_modify);
    lv_label_set_text(ui_scr->eq_modify_lbl_8, "4k");
    lv_label_set_long_mode(ui_scr->eq_modify_lbl_8, LV_LABEL_LONG_SCROLL);
    lv_obj_set_pos(ui_scr->eq_modify_lbl_8, 600, 422);
    lv_obj_set_size(ui_scr->eq_modify_lbl_8, 40, 29);
    lv_obj_set_scrollbar_mode(ui_scr->eq_modify_lbl_8, LV_SCROLLBAR_MODE_OFF);
    ui_style_set(ui_scr->eq_modify_lbl_8, GUI_CTRL_LABEL);

    //Write codes eq_modify_lbl_9
    ui_scr->eq_modify_lbl_9 = lv_label_create(ui_scr->eq_modify);
    lv_label_set_text(ui_scr->eq_modify_lbl_9, "8k");
    lv_label_set_long_mode(ui_scr->eq_modify_lbl_9, LV_LABEL_LONG_SCROLL);
    lv_obj_set_pos(ui_scr->eq_modify_lbl_9, 665, 422);
    lv_obj_set_size(ui_scr->eq_modify_lbl_9, 40, 29);
    lv_obj_set_scrollbar_mode(ui_scr->eq_modify_lbl_9, LV_SCROLLBAR_MODE_OFF);
    ui_style_set(ui_scr->eq_modify_lbl_9, GUI_CTRL_LABEL);

    //Write codes eq_modify_lbl_10
    ui_scr->eq_modify_lbl_10 = lv_label_create(ui_scr->eq_modify);
    lv_label_set_text(ui_scr->eq_modify_lbl_10, "16k");
    lv_label_set_long_mode(ui_scr->eq_modify_lbl_10, LV_LABEL_LONG_SCROLL);
    lv_obj_set_pos(ui_scr->eq_modify_lbl_10, 725, 422);
    lv_obj_set_size(ui_scr->eq_modify_lbl_10, 45, 29);
    lv_obj_set_scrollbar_mode(ui_scr->eq_modify_lbl_10, LV_SCROLLBAR_MODE_OFF);
    ui_style_set(ui_scr->eq_modify_lbl_10, GUI_CTRL_LABEL);

    //Write codes eq_modify_lbl_11
    ui_scr->eq_modify_lbl_11 = lv_label_create(ui_scr->eq_modify);
    lv_label_set_text(ui_scr->eq_modify_lbl_11, "+18dB");
    lv_label_set_long_mode(ui_scr->eq_modify_lbl_11, LV_LABEL_LONG_SCROLL);
    lv_obj_set_pos(ui_scr->eq_modify_lbl_11, 26, 93);
    lv_obj_set_size(ui_scr->eq_modify_lbl_11, 97, 30);
    lv_obj_set_scrollbar_mode(ui_scr->eq_modify_lbl_11, LV_SCROLLBAR_MODE_OFF);
    ui_style_set(ui_scr->eq_modify_lbl_11, GUI_CTRL_LABEL);

    //Write codes eq_modify_lbl_12
    ui_scr->eq_modify_lbl_12 = lv_label_create(ui_scr->eq_modify);
    lv_label_set_text(ui_scr->eq_modify_lbl_12, "0dB");
    lv_label_set_long_mode(ui_scr->eq_modify_lbl_12, LV_LABEL_LONG_SCROLL);
    lv_obj_set_pos(ui_scr->eq_modify_lbl_12, 26, 229);
    lv_obj_set_size(ui_scr->eq_modify_lbl_12, 97, 30);
    lv_obj_set_scrollbar_mode(ui_scr->eq_modify_lbl_12, LV_SCROLLBAR_MODE_OFF);
    ui_style_set(ui_scr->eq_modify_lbl_12, GUI_CTRL_LABEL);

    //Write codes eq_modify_lbl_13
    ui_scr->eq_modify_lbl_13 = lv_label_create(ui_scr->eq_modify);
    lv_label_set_text(ui_scr->eq_modify_lbl_13, "-18dB");
    lv_label_set_long_mode(ui_scr->eq_modify_lbl_13, LV_LABEL_LONG_SCROLL);
    lv_obj_set_pos(ui_scr->eq_modify_lbl_13, 26, 372);
    lv_obj_set_size(ui_scr->eq_modify_lbl_13, 97, 30);
    lv_obj_set_scrollbar_mode(ui_scr->eq_modify_lbl_13, LV_SCROLLBAR_MODE_OFF);
    ui_style_set(ui_scr->eq_modify_lbl_13, GUI_CTRL_LABEL);

    //Write codes eq_modify_lbl_14
    ui_scr->eq_modify_lbl_14 = lv_label_create(ui_scr->eq_modify);
    lv_label_set_text(ui_scr->eq_modify_lbl_14, "均衡器");
    lv_label_set_long_mode(ui_scr->eq_modify_lbl_14, LV_LABEL_LONG_SCROLL);
    lv_obj_set_pos(ui_scr->eq_modify_lbl_14, 26, 22);
    lv_obj_set_size(ui_scr->eq_modify_lbl_14, 121, 39);
    lv_obj_set_scrollbar_mode(ui_scr->eq_modify_lbl_14, LV_SCROLLBAR_MODE_OFF);
    ui_style_set(ui_scr->eq_modify_lbl_14, GUI_CTRL_LABEL);

    //Write codes eq_modify_sw_1
    ui_scr->eq_modify_sw_1 = lv_switch_create(ui_scr->eq_modify);
    lv_obj_set_pos(ui_scr->eq_modify_sw_1, 704, 21);
    lv_obj_set_size(ui_scr->eq_modify_sw_1, 73, 40);
    lv_obj_set_scrollbar_mode(ui_scr->eq_modify_sw_1, LV_SCROLLBAR_MODE_OFF);
    lv_obj_add_state(ui_scr->eq_modify_sw_1, LV_STATE_CHECKED);
    lv_group_remove_obj(ui_scr->eq_modify_sw_1);
    ui_style_set(ui_scr->eq_modify_sw_1, GUI_CTRL_SWITCH);

    //Write codes eq_modify_lbl_15
    ui_scr->eq_modify_lbl_15 = lv_label_create(ui_scr->eq_modify);
    lv_label_set_text(ui_scr->eq_modify_lbl_15, "音效：均衡器");
    lv_label_set_long_mode(ui_scr->eq_modify_lbl_15, LV_LABEL_LONG_SCROLL);
    lv_obj_set_pos(ui_scr->eq_modify_lbl_15, 524, 25);
    lv_obj_set_size(ui_scr->eq_modify_lbl_15, 166, 30);
    lv_obj_set_scrollbar_mode(ui_scr->eq_modify_lbl_15, LV_SCROLLBAR_MODE_OFF);
    ui_style_set(ui_scr->eq_modify_lbl_15, GUI_CTRL_LABEL);

    //Write codes eq_modify_ddlist_1
    ui_scr->eq_modify_ddlist_1 = lv_dropdown_create(ui_scr->eq_modify);
    lv_dropdown_set_options(ui_scr->eq_modify_ddlist_1, "普通模式\n摇滚模式\n流行模式\n古典模式\n爵士模式\n乡村模式\n自定义模式");
    lv_dropdown_set_dir(ui_scr->eq_modify_ddlist_1, LV_DIR_BOTTOM);
    lv_dropdown_set_symbol(ui_scr->eq_modify_ddlist_1, LV_SYMBOL_DOWN);
    lv_dropdown_set_symbol(ui_scr->eq_modify_ddlist_1, NULL);
    lv_dropdown_set_selected(ui_scr->eq_modify_ddlist_1, 6);
    lv_obj_set_pos(ui_scr->eq_modify_ddlist_1, 147, 22);
    lv_obj_set_size(ui_scr->eq_modify_ddlist_1, 137, 39);
    lv_obj_set_scrollbar_mode(ui_scr->eq_modify_ddlist_1, LV_SCROLLBAR_MODE_OFF);
    ui_style_set(ui_scr->eq_modify_ddlist_1, GUI_CTRL_DROPDOWN);

    //Set style state: LV_STATE_CHECKED for style_eq_modify_ddlist_1_extra_list_selected_checked
    static lv_style_t style_eq_modify_ddlist_1_extra_list_selected_checked;
    ui_init_style(&style_eq_modify_ddlist_1_extra_list_selected_checked);
    lv_obj_add_style(lv_dropdown_get_list(ui_scr->eq_modify_ddlist_1), &gui_ddlist_selected_checked_style, LV_PART_SELECTED | LV_STATE_CHECKED);
    lv_obj_add_style(lv_dropdown_get_list(ui_scr->eq_modify_ddlist_1), &style_eq_modify_ddlist_1_extra_list_selected_checked, LV_PART_SELECTED | LV_STATE_CHECKED);

    //Set style state: LV_STATE_DEFAULT for style_eq_modify_ddlist_1_extra_list_main_default
    static lv_style_t style_eq_modify_ddlist_1_extra_list_main_default;
    ui_init_style(&style_eq_modify_ddlist_1_extra_list_main_default);
    lv_obj_add_style(lv_dropdown_get_list(ui_scr->eq_modify_ddlist_1), &gui_ddlist_dropdown_list_default_style, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_add_style(lv_dropdown_get_list(ui_scr->eq_modify_ddlist_1), &style_eq_modify_ddlist_1_extra_list_main_default, LV_PART_MAIN | LV_STATE_DEFAULT);

    //Set style state: LV_STATE_DEFAULT for style_eq_modify_ddlist_1_extra_list_scrollbar_default
    static lv_style_t style_eq_modify_ddlist_1_extra_list_scrollbar_default;
    ui_init_style(&style_eq_modify_ddlist_1_extra_list_scrollbar_default);
    lv_obj_add_style(lv_dropdown_get_list(ui_scr->eq_modify_ddlist_1), &gui_ddlist_scrollbar_default_style, LV_PART_SCROLLBAR | LV_STATE_DEFAULT);
    lv_obj_add_style(lv_dropdown_get_list(ui_scr->eq_modify_ddlist_1), &style_eq_modify_ddlist_1_extra_list_scrollbar_default, LV_PART_SCROLLBAR | LV_STATE_DEFAULT);

    //Delete extra default style for eq_modify_ddlist_1
    lv_obj_remove_style(ui_scr->eq_modify_ddlist_1, &gui_ddlist_selected_checked_style, LV_PART_SELECTED | LV_STATE_CHECKED);
    lv_obj_remove_style(ui_scr->eq_modify_ddlist_1, &gui_ddlist_dropdown_list_default_style, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_remove_style(ui_scr->eq_modify_ddlist_1, &gui_ddlist_scrollbar_default_style, LV_PART_SCROLLBAR | LV_STATE_DEFAULT);

    //Write codes eq_modify_btn_1
    ui_scr->eq_modify_btn_1 = lv_btn_create(ui_scr->eq_modify);
    lv_obj_set_pos(ui_scr->eq_modify_btn_1, 294, 18);
    lv_obj_set_size(ui_scr->eq_modify_btn_1, 98, 45);
    lv_obj_set_scrollbar_mode(ui_scr->eq_modify_btn_1, LV_SCROLLBAR_MODE_OFF);
    lv_obj_add_state(ui_scr->eq_modify_btn_1, LV_STATE_DISABLED);
    lv_group_remove_obj(ui_scr->eq_modify_btn_1);
    ui_style_set(ui_scr->eq_modify_btn_1, GUI_CTRL_BUTTON);
    ui_scr->eq_modify_btn_1_label = lv_label_create(ui_scr->eq_modify_btn_1);
    lv_label_set_text(ui_scr->eq_modify_btn_1_label, "保存");
    lv_obj_set_style_pad_all(ui_scr->eq_modify_btn_1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_align(ui_scr->eq_modify_btn_1_label, LV_ALIGN_CENTER, 0, 0);

    lv_obj_update_layout(ui_scr->eq_modify);
    ui_scr->eq_modify_del = false;

    //Init events for screen
    events_init_eq_modify(ui);
    return ui_scr->eq_modify;
}
void unload_scr_eq_modify(lv_ui *ui)
{
    ui_free_scr_ptr(ui, GUI_SCREEN_EQ_MODIFY);
}
