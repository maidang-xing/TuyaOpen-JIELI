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


lv_obj_t *setup_scr_home_page(lv_ui *ui)
{
    lv_ui_home_page *ui_scr = ui_get_scr_ptr(ui, GUI_SCREEN_HOME_PAGE);
    if (ui_scr == NULL) {
        ui_scr = lv_mem_alloc(sizeof(lv_ui_home_page));
        memset(ui_scr, 0, sizeof(lv_ui_home_page));
        ui->home_page = ui_scr;
    }

    //Write codes home_page
    ui_scr->home_page = lv_obj_create(NULL);
    lv_group_t *def_group = lv_group_get_default();
    lv_obj_set_scrollbar_mode(ui_scr->home_page, LV_SCROLLBAR_MODE_OFF);
    ui_style_set(ui_scr->home_page, GUI_CTRL_SCR);

    //Set style for home_page. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
    lv_obj_set_style_bg_color(ui_scr->home_page, lv_color_make(0x00, 0x00, 0x00), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_scr->home_page, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    //Write codes home_page_imgbtn_1
    ui_scr->home_page_imgbtn_1 = lv_imgbtn_create(ui_scr->home_page);
    lv_obj_set_pos(ui_scr->home_page_imgbtn_1, 163, 189);
    lv_obj_set_size(ui_scr->home_page_imgbtn_1, 128, 220);
    lv_obj_set_scrollbar_mode(ui_scr->home_page_imgbtn_1, LV_SCROLLBAR_MODE_OFF);
    lv_group_add_obj(def_group, ui_scr->home_page_imgbtn_1);
    ui_style_set(ui_scr->home_page_imgbtn_1, GUI_CTRL_IMGBTN);

    //Set style for home_page_imgbtn_1. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
    lv_obj_set_style_outline_width(ui_scr->home_page_imgbtn_1, 2, LV_PART_MAIN | LV_STATE_DEFAULT);

    //Set style for home_page_imgbtn_1. Part: LV_PART_MAIN, State: LV_STATE_PRESSED
    lv_obj_set_style_bg_opa(ui_scr->home_page_imgbtn_1, 255, LV_PART_MAIN | LV_STATE_PRESSED);

    //Set style for home_page_imgbtn_1. Part: LV_PART_MAIN, State: LV_STATE_CHECKED
    lv_obj_set_style_bg_opa(ui_scr->home_page_imgbtn_1, 255, LV_PART_MAIN | LV_STATE_CHECKED);

    //Set style for home_page_imgbtn_1. Part: LV_PART_MAIN, State: LV_STATE_FOCUS_KEY
    lv_obj_set_style_bg_color(ui_scr->home_page_imgbtn_1, lv_color_make(0xB1, 0x3E, 0x3E), LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_outline_width(ui_scr->home_page_imgbtn_1, 5, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_img_recolor(ui_scr->home_page_imgbtn_1, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_img_recolor_opa(ui_scr->home_page_imgbtn_1, 0, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_imgbtn_set_src(ui_scr->home_page_imgbtn_1, LV_IMGBTN_STATE_RELEASED, NULL, gui_get_res_path(GUI_RES_VIDEO_1_PNG), NULL);
    lv_imgbtn_set_src(ui_scr->home_page_imgbtn_1, LV_IMGBTN_STATE_PRESSED, NULL, gui_get_res_path(GUI_RES_VIDEO__ON_PNG), NULL);
    lv_imgbtn_set_src(ui_scr->home_page_imgbtn_1, LV_IMGBTN_STATE_CHECKED_RELEASED, NULL, gui_get_res_path(GUI_RES_VIDEO_1_PNG), NULL);
    lv_imgbtn_set_src(ui_scr->home_page_imgbtn_1, LV_IMGBTN_STATE_CHECKED_PRESSED, NULL, gui_get_res_path(GUI_RES_VIDEO__ON_PNG), NULL);
    lv_obj_add_flag(ui_scr->home_page_imgbtn_1, LV_OBJ_FLAG_CHECKABLE);
    ui_scr->home_page_imgbtn_1_label = lv_label_create(ui_scr->home_page_imgbtn_1);
    lv_label_set_text(ui_scr->home_page_imgbtn_1_label, "");
    lv_obj_set_style_pad_all(ui_scr->home_page_imgbtn_1, 0, LV_STATE_DEFAULT);
    lv_obj_align(ui_scr->home_page_imgbtn_1_label, LV_ALIGN_CENTER, 0, 0);

    //Write codes home_page_imgbtn_2
    ui_scr->home_page_imgbtn_2 = lv_imgbtn_create(ui_scr->home_page);
    lv_obj_set_pos(ui_scr->home_page_imgbtn_2, 337, 189);
    lv_obj_set_size(ui_scr->home_page_imgbtn_2, 128, 220);
    lv_obj_set_scrollbar_mode(ui_scr->home_page_imgbtn_2, LV_SCROLLBAR_MODE_OFF);
    lv_group_add_obj(def_group, ui_scr->home_page_imgbtn_2);
    ui_style_set(ui_scr->home_page_imgbtn_2, GUI_CTRL_IMGBTN);

    //Set style for home_page_imgbtn_2. Part: LV_PART_MAIN, State: LV_STATE_PRESSED
    lv_obj_set_style_bg_opa(ui_scr->home_page_imgbtn_2, 255, LV_PART_MAIN | LV_STATE_PRESSED);

    //Set style for home_page_imgbtn_2. Part: LV_PART_MAIN, State: LV_STATE_CHECKED
    lv_obj_set_style_bg_opa(ui_scr->home_page_imgbtn_2, 255, LV_PART_MAIN | LV_STATE_CHECKED);

    //Set style for home_page_imgbtn_2. Part: LV_PART_MAIN, State: LV_STATE_FOCUS_KEY
    lv_obj_set_style_bg_color(ui_scr->home_page_imgbtn_2, lv_color_make(0x00, 0x09, 0x99), LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_outline_width(ui_scr->home_page_imgbtn_2, 5, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_img_recolor(ui_scr->home_page_imgbtn_2, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_img_recolor_opa(ui_scr->home_page_imgbtn_2, 0, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_imgbtn_set_src(ui_scr->home_page_imgbtn_2, LV_IMGBTN_STATE_RELEASED, NULL, gui_get_res_path(GUI_RES_FILE_PNG), NULL);
    lv_imgbtn_set_src(ui_scr->home_page_imgbtn_2, LV_IMGBTN_STATE_PRESSED, NULL, gui_get_res_path(GUI_RES_FILE_ON_PNG), NULL);
    lv_imgbtn_set_src(ui_scr->home_page_imgbtn_2, LV_IMGBTN_STATE_CHECKED_RELEASED, NULL, gui_get_res_path(GUI_RES_FILE_PNG), NULL);
    lv_imgbtn_set_src(ui_scr->home_page_imgbtn_2, LV_IMGBTN_STATE_CHECKED_PRESSED, NULL, gui_get_res_path(GUI_RES_FILE_ON_PNG), NULL);
    lv_obj_add_flag(ui_scr->home_page_imgbtn_2, LV_OBJ_FLAG_CHECKABLE);
    ui_scr->home_page_imgbtn_2_label = lv_label_create(ui_scr->home_page_imgbtn_2);
    lv_label_set_text(ui_scr->home_page_imgbtn_2_label, "");
    lv_obj_set_style_pad_all(ui_scr->home_page_imgbtn_2, 0, LV_STATE_DEFAULT);
    lv_obj_align(ui_scr->home_page_imgbtn_2_label, LV_ALIGN_CENTER, 0, 0);

    //Write codes home_page_imgbtn_3
    ui_scr->home_page_imgbtn_3 = lv_imgbtn_create(ui_scr->home_page);
    lv_obj_set_pos(ui_scr->home_page_imgbtn_3, 513, 189);
    lv_obj_set_size(ui_scr->home_page_imgbtn_3, 128, 220);
    lv_obj_set_scrollbar_mode(ui_scr->home_page_imgbtn_3, LV_SCROLLBAR_MODE_OFF);
    lv_group_add_obj(def_group, ui_scr->home_page_imgbtn_3);
    ui_style_set(ui_scr->home_page_imgbtn_3, GUI_CTRL_IMGBTN);

    //Set style for home_page_imgbtn_3. Part: LV_PART_MAIN, State: LV_STATE_PRESSED
    lv_obj_set_style_bg_opa(ui_scr->home_page_imgbtn_3, 255, LV_PART_MAIN | LV_STATE_PRESSED);

    //Set style for home_page_imgbtn_3. Part: LV_PART_MAIN, State: LV_STATE_CHECKED
    lv_obj_set_style_bg_opa(ui_scr->home_page_imgbtn_3, 255, LV_PART_MAIN | LV_STATE_CHECKED);

    //Set style for home_page_imgbtn_3. Part: LV_PART_MAIN, State: LV_STATE_FOCUS_KEY
    lv_obj_set_style_bg_color(ui_scr->home_page_imgbtn_3, lv_color_make(0xf9, 0x99, 0x99), LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_outline_width(ui_scr->home_page_imgbtn_3, 5, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_img_recolor(ui_scr->home_page_imgbtn_3, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_img_recolor_opa(ui_scr->home_page_imgbtn_3, 0, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_imgbtn_set_src(ui_scr->home_page_imgbtn_3, LV_IMGBTN_STATE_RELEASED, NULL, gui_get_res_path(GUI_RES_SETTING_1_PNG), NULL);
    lv_imgbtn_set_src(ui_scr->home_page_imgbtn_3, LV_IMGBTN_STATE_PRESSED, NULL, gui_get_res_path(GUI_RES_SETTING_ON_PNG), NULL);
    lv_imgbtn_set_src(ui_scr->home_page_imgbtn_3, LV_IMGBTN_STATE_CHECKED_RELEASED, NULL, gui_get_res_path(GUI_RES_SETTING_1_PNG), NULL);
    lv_imgbtn_set_src(ui_scr->home_page_imgbtn_3, LV_IMGBTN_STATE_CHECKED_PRESSED, NULL, gui_get_res_path(GUI_RES_SETTING_ON_PNG), NULL);
    lv_obj_add_flag(ui_scr->home_page_imgbtn_3, LV_OBJ_FLAG_CHECKABLE);
    ui_scr->home_page_imgbtn_3_label = lv_label_create(ui_scr->home_page_imgbtn_3);
    lv_label_set_text(ui_scr->home_page_imgbtn_3_label, "");
    lv_obj_set_style_pad_all(ui_scr->home_page_imgbtn_3, 0, LV_STATE_DEFAULT);
    lv_obj_align(ui_scr->home_page_imgbtn_3_label, LV_ALIGN_CENTER, 0, 0);

    //Write codes home_page_img_1
    ui_scr->home_page_img_1 = lv_img_create(ui_scr->home_page);
    lv_img_set_src(ui_scr->home_page_img_1, gui_get_res_path(GUI_RES_FULL_PNG));
    lv_img_set_pivot(ui_scr->home_page_img_1, 0, 0);
    lv_img_set_angle(ui_scr->home_page_img_1, 0);
    lv_img_set_zoom(ui_scr->home_page_img_1, 256);
    lv_obj_set_pos(ui_scr->home_page_img_1, 28, 21);
    lv_obj_set_size(ui_scr->home_page_img_1, 48, 48);
    lv_obj_add_flag(ui_scr->home_page_img_1, LV_OBJ_FLAG_CLICKABLE);
    ui_style_set(ui_scr->home_page_img_1, GUI_CTRL_IMG);

    //Delete extra default style for home_page_img_1
    lv_obj_remove_style(ui_scr->home_page_img_1, &gui_img_main_focus_key_style, LV_PART_MAIN | LV_STATE_FOCUS_KEY);

    static bool timer_home_page_digitclock_1_enabled = false;
    //Write codes home_page_digitclock_1
    ui_scr->home_page_digitclock_1 = lv_label_create(ui_scr->home_page);
    lv_label_set_text_fmt(ui_scr->home_page_digitclock_1, "%04d-%02d-%02d %02d:%02d:%02d", 2024, 06, 13, 21 % 12, 25, 50);
    lv_obj_set_style_text_align(ui_scr->home_page_digitclock_1, LV_TEXT_ALIGN_CENTER, 0);
    lv_obj_set_pos(ui_scr->home_page_digitclock_1, 92, 14);
    lv_obj_set_size(ui_scr->home_page_digitclock_1, 613, 75);
    ui_style_set(ui_scr->home_page_digitclock_1, GUI_CTRL_DIGITALCLOCK);

    //Set style for home_page_digitclock_1. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
    lv_obj_set_style_text_font(ui_scr->home_page_digitclock_1, &lv_font_FangZhengKaiTiJianTi_1_54, LV_PART_MAIN | LV_STATE_DEFAULT);

    //Delete extra default style for home_page_digitclock_1
    lv_obj_remove_style(ui_scr->home_page_digitclock_1, &gui_digitclock_main_disabled_style, LV_PART_MAIN | LV_STATE_DISABLED);

    //Write codes home_page_lbl_3
    ui_scr->home_page_lbl_3 = lv_label_create(ui_scr->home_page);
    lv_label_set_long_mode(ui_scr->home_page_lbl_3, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui_scr->home_page_lbl_3, 515, 93);
    lv_obj_set_size(ui_scr->home_page_lbl_3, 131, 67);
    lv_obj_set_scrollbar_mode(ui_scr->home_page_lbl_3, LV_SCROLLBAR_MODE_OFF);
    ui_style_set(ui_scr->home_page_lbl_3, GUI_CTRL_LABEL);

    //Write codes home_page_lbl_1
    ui_scr->home_page_lbl_1 = lv_label_create(ui_scr->home_page);
    lv_label_set_long_mode(ui_scr->home_page_lbl_1, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui_scr->home_page_lbl_1, 167, 93);
    lv_obj_set_size(ui_scr->home_page_lbl_1, 197, 67);
    lv_obj_set_scrollbar_mode(ui_scr->home_page_lbl_1, LV_SCROLLBAR_MODE_OFF);
    ui_style_set(ui_scr->home_page_lbl_1, GUI_CTRL_LABEL);

    lv_obj_update_layout(ui_scr->home_page);
    ui_scr->home_page_del = false;
    i18n_refresh_texts("home_page");

    //Init events for screen
    events_init_home_page(ui);
    return ui_scr->home_page;
}
void unload_scr_home_page(lv_ui *ui)
{
    ui_free_scr_ptr(ui, GUI_SCREEN_HOME_PAGE);
}

#endif
