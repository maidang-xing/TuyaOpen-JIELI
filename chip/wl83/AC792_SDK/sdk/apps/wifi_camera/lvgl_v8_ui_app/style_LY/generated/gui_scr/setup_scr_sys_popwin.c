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


lv_obj_t *setup_scr_sys_popwin(lv_ui *ui)
{
    lv_ui_sys_popwin *ui_scr = ui_get_scr_ptr(ui, GUI_SCREEN_SYS_POPWIN);
    if (ui_scr == NULL) {
        ui_scr = lv_mem_alloc(sizeof(lv_ui_sys_popwin));
        if (ui_scr == NULL) {
            return NULL;
        }
        memset(ui_scr, 0, sizeof(lv_ui_sys_popwin));
        ui->sys_popwin = ui_scr;
    }

    //Write codes sys_popwin
    ui_scr->sys_popwin = lv_obj_create(NULL);
    lv_obj_set_scrollbar_mode(ui_scr->sys_popwin, LV_SCROLLBAR_MODE_OFF);
    lv_obj_clear_flag(ui_scr->sys_popwin, LV_OBJ_FLAG_CLICKABLE);
    ui_style_set(ui_scr->sys_popwin, GUI_CTRL_SCR);

    //Set style for sys_popwin. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
    lv_obj_set_style_bg_color(ui_scr->sys_popwin, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui_scr->sys_popwin, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

    //Write codes sys_popwin_view_1
    ui_scr->sys_popwin_view_1 = lv_obj_create(ui_scr->sys_popwin);
    lv_obj_set_pos(ui_scr->sys_popwin_view_1, 199, 100);
    lv_obj_set_size(ui_scr->sys_popwin_view_1, 390, 250);
    lv_obj_set_scrollbar_mode(ui_scr->sys_popwin_view_1, LV_SCROLLBAR_MODE_OFF);
    ui_style_set(ui_scr->sys_popwin_view_1, GUI_CTRL_CONT);

    //Set style for sys_popwin_view_1. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
    lv_obj_set_style_radius(ui_scr->sys_popwin_view_1, 10, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui_scr->sys_popwin_view_1, lv_color_make(0x3D, 0x3B, 0x3B), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_scr->sys_popwin_view_1, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui_scr->sys_popwin_view_1, lv_color_make(0x3D, 0x3B, 0x3B), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui_scr->sys_popwin_view_1, 1, LV_PART_MAIN | LV_STATE_DEFAULT);

    //Delete extra default style for sys_popwin_view_1
    lv_obj_remove_style(ui_scr->sys_popwin_view_1, &gui_cont_main_focus_key_style, LV_PART_MAIN | LV_STATE_FOCUS_KEY);

    //Write codes sys_popwin_lbl_1
    ui_scr->sys_popwin_lbl_1 = lv_label_create(ui_scr->sys_popwin_view_1);
    lv_label_set_long_mode(ui_scr->sys_popwin_lbl_1, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui_scr->sys_popwin_lbl_1, 15, 0);
    lv_obj_set_size(ui_scr->sys_popwin_lbl_1, 360, 165);
    lv_obj_set_scrollbar_mode(ui_scr->sys_popwin_lbl_1, LV_SCROLLBAR_MODE_OFF);
    ui_style_set(ui_scr->sys_popwin_lbl_1, GUI_CTRL_LABEL);

    //Set style for sys_popwin_lbl_1. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
    lv_obj_set_style_bg_color(ui_scr->sys_popwin_lbl_1, lv_color_make(0xFF, 0xFF, 0xFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_scr->sys_popwin_lbl_1, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui_scr->sys_popwin_lbl_1, lv_color_make(0x00, 0x00, 0x00), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui_scr->sys_popwin_lbl_1, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui_scr->sys_popwin_lbl_1, 50, LV_PART_MAIN | LV_STATE_DEFAULT);

    //Write codes sys_popwin_btn_1
    ui_scr->sys_popwin_btn_1 = lv_btn_create(ui_scr->sys_popwin_view_1);
    lv_obj_set_pos(ui_scr->sys_popwin_btn_1, 14, 132);
    lv_obj_set_size(ui_scr->sys_popwin_btn_1, 181, 72);
    lv_obj_set_scrollbar_mode(ui_scr->sys_popwin_btn_1, LV_SCROLLBAR_MODE_OFF);
    ui_style_set(ui_scr->sys_popwin_btn_1, GUI_CTRL_BUTTON);

    //Set style for sys_popwin_btn_1. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
    lv_obj_set_style_bg_color(ui_scr->sys_popwin_btn_1, lv_color_make(0x74, 0x72, 0x72), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui_scr->sys_popwin_btn_1, lv_color_make(0x74, 0x72, 0x72), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui_scr->sys_popwin_btn_1, 1, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_side(ui_scr->sys_popwin_btn_1, LV_BORDER_SIDE_BOTTOM | LV_BORDER_SIDE_RIGHT, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui_scr->sys_popwin_btn_1, lv_color_make(0xFF, 0xFF, 0xFF), LV_PART_MAIN | LV_STATE_DEFAULT);

    //Set style for sys_popwin_btn_1. Part: LV_PART_MAIN, State: LV_STATE_FOCUSED
    lv_obj_add_style(ui_scr->sys_popwin_btn_1, &gui_btn_main_focused_style, LV_PART_MAIN | LV_STATE_FOCUSED);

    //Delete extra default style for sys_popwin_btn_1
    lv_obj_remove_style(ui_scr->sys_popwin_btn_1, &gui_btn_main_focus_key_style, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    ui_scr->sys_popwin_btn_1_label = lv_label_create(ui_scr->sys_popwin_btn_1);
    lv_obj_set_style_pad_all(ui_scr->sys_popwin_btn_1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_align(ui_scr->sys_popwin_btn_1_label, LV_ALIGN_CENTER, 0, 0);

    //Write codes sys_popwin_btn_2
    ui_scr->sys_popwin_btn_2 = lv_btn_create(ui_scr->sys_popwin_view_1);
    lv_obj_set_pos(ui_scr->sys_popwin_btn_2, 195, 132);
    lv_obj_set_size(ui_scr->sys_popwin_btn_2, 181, 72);
    lv_obj_set_scrollbar_mode(ui_scr->sys_popwin_btn_2, LV_SCROLLBAR_MODE_OFF);
    ui_style_set(ui_scr->sys_popwin_btn_2, GUI_CTRL_BUTTON);

    //Set style for sys_popwin_btn_2. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
    lv_obj_set_style_bg_color(ui_scr->sys_popwin_btn_2, lv_color_make(0x74, 0x72, 0x72), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui_scr->sys_popwin_btn_2, lv_color_make(0x74, 0x72, 0x72), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui_scr->sys_popwin_btn_2, 1, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_side(ui_scr->sys_popwin_btn_2, LV_BORDER_SIDE_BOTTOM | LV_BORDER_SIDE_RIGHT, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui_scr->sys_popwin_btn_2, lv_color_make(0xFF, 0xFF, 0xFF), LV_PART_MAIN | LV_STATE_DEFAULT);

    //Set style for sys_popwin_btn_2. Part: LV_PART_MAIN, State: LV_STATE_FOCUSED
    lv_obj_add_style(ui_scr->sys_popwin_btn_2, &gui_btn_main_focused_style, LV_PART_MAIN | LV_STATE_FOCUSED);

    //Delete extra default style for sys_popwin_btn_2
    lv_obj_remove_style(ui_scr->sys_popwin_btn_2, &gui_btn_main_focus_key_style, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    ui_scr->sys_popwin_btn_2_label = lv_label_create(ui_scr->sys_popwin_btn_2);
    lv_obj_set_style_pad_all(ui_scr->sys_popwin_btn_2, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_align(ui_scr->sys_popwin_btn_2_label, LV_ALIGN_CENTER, 0, 0);

    lv_obj_update_layout(ui_scr->sys_popwin);
    ui_scr->sys_popwin_del = false;
    i18n_refresh_texts(GUI_SCREEN_SYS_POPWIN);

    //Init events for screen
    events_init_sys_popwin(ui);
    return ui_scr->sys_popwin;
}
void unload_scr_sys_popwin(lv_ui *ui)
{
    ui_free_scr_ptr(ui, GUI_SCREEN_SYS_POPWIN);
}

#endif
