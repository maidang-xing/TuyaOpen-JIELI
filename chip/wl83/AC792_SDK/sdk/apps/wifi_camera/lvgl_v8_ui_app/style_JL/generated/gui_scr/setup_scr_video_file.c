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


lv_obj_t *setup_scr_video_file(lv_ui *ui)
{
    lv_ui_video_file *ui_scr = ui_get_scr_ptr(ui, GUI_SCREEN_VIDEO_FILE);
    if (ui_scr == NULL) {
        ui_scr = lv_mem_alloc(sizeof(lv_ui_video_file));
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
    lv_obj_set_style_bg_color(ui_scr->video_file, lv_color_make(0x00, 0x00, 0x00), LV_PART_MAIN | LV_STATE_DEFAULT);
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

    //Write codes video_file_imgbtn_4
    ui_scr->video_file_imgbtn_4 = lv_imgbtn_create(ui_scr->video_file_view_1);
    lv_obj_set_pos(ui_scr->video_file_imgbtn_4, 16, 37);
    lv_obj_set_size(ui_scr->video_file_imgbtn_4, 48, 48);
    lv_obj_set_scrollbar_mode(ui_scr->video_file_imgbtn_4, LV_SCROLLBAR_MODE_OFF);
    lv_group_add_obj(def_group, ui_scr->video_file_imgbtn_4);
    ui_style_set(ui_scr->video_file_imgbtn_4, GUI_CTRL_IMGBTN);
    lv_imgbtn_set_src(ui_scr->video_file_imgbtn_4, LV_IMGBTN_STATE_RELEASED, NULL, gui_get_res_path(GUI_RES_RETURN_PNG), NULL);
    lv_imgbtn_set_src(ui_scr->video_file_imgbtn_4, LV_IMGBTN_STATE_PRESSED, NULL, gui_get_res_path(GUI_RES_RETURN_ON_PNG), NULL);
    lv_imgbtn_set_src(ui_scr->video_file_imgbtn_4, LV_IMGBTN_STATE_CHECKED_RELEASED, NULL, gui_get_res_path(GUI_RES_RETURN_PNG), NULL);
    lv_imgbtn_set_src(ui_scr->video_file_imgbtn_4, LV_IMGBTN_STATE_CHECKED_PRESSED, NULL, gui_get_res_path(GUI_RES_RETURN_ON_PNG), NULL);
    lv_obj_add_flag(ui_scr->video_file_imgbtn_4, LV_OBJ_FLAG_CHECKABLE);
    ui_scr->video_file_imgbtn_4_label = lv_label_create(ui_scr->video_file_imgbtn_4);
    lv_label_set_text(ui_scr->video_file_imgbtn_4_label, "");
    lv_obj_set_style_pad_all(ui_scr->video_file_imgbtn_4, 0, LV_STATE_DEFAULT);
    lv_obj_align(ui_scr->video_file_imgbtn_4_label, LV_ALIGN_CENTER, 0, 0);

    //Write codes video_file_img_1
    ui_scr->video_file_img_1 = lv_img_create(ui_scr->video_file_view_1);
    lv_img_set_src(ui_scr->video_file_img_1, gui_get_res_path(GUI_RES_UP_PNG));
    lv_img_set_pivot(ui_scr->video_file_img_1, 0, 0);
    lv_img_set_angle(ui_scr->video_file_img_1, 0);
    lv_img_set_zoom(ui_scr->video_file_img_1, 256);
    lv_obj_set_pos(ui_scr->video_file_img_1, 8, 139);
    lv_obj_set_size(ui_scr->video_file_img_1, 64, 64);
    lv_group_add_obj(def_group, ui_scr->video_file_img_1);
    lv_obj_add_flag(ui_scr->video_file_img_1, LV_OBJ_FLAG_CLICKABLE);
    ui_style_set(ui_scr->video_file_img_1, GUI_CTRL_IMG);

    //Write codes video_file_img_2
    ui_scr->video_file_img_2 = lv_img_create(ui_scr->video_file_view_1);
    lv_img_set_src(ui_scr->video_file_img_2, gui_get_res_path(GUI_RES_DOWN_PNG));
    lv_img_set_pivot(ui_scr->video_file_img_2, 0, 0);
    lv_img_set_angle(ui_scr->video_file_img_2, 0);
    lv_img_set_zoom(ui_scr->video_file_img_2, 256);
    lv_obj_set_pos(ui_scr->video_file_img_2, 8, 287);
    lv_obj_set_size(ui_scr->video_file_img_2, 64, 64);
    lv_group_add_obj(def_group, ui_scr->video_file_img_2);
    lv_obj_add_flag(ui_scr->video_file_img_2, LV_OBJ_FLAG_CLICKABLE);
    ui_style_set(ui_scr->video_file_img_2, GUI_CTRL_IMG);

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

    //Write codes video_file_imgbtn_3
    ui_scr->video_file_imgbtn_3 = lv_imgbtn_create(ui_scr->video_file_view_8);
    lv_obj_set_pos(ui_scr->video_file_imgbtn_3, 16, 37);
    lv_obj_set_size(ui_scr->video_file_imgbtn_3, 48, 48);
    lv_obj_set_scrollbar_mode(ui_scr->video_file_imgbtn_3, LV_SCROLLBAR_MODE_OFF);
    lv_group_add_obj(def_group, ui_scr->video_file_imgbtn_3);
    ui_style_set(ui_scr->video_file_imgbtn_3, GUI_CTRL_IMGBTN);
    lv_imgbtn_set_src(ui_scr->video_file_imgbtn_3, LV_IMGBTN_STATE_RELEASED, NULL, gui_get_res_path(GUI_RES_EDIT_PNG), NULL);
    lv_imgbtn_set_src(ui_scr->video_file_imgbtn_3, LV_IMGBTN_STATE_PRESSED, NULL, gui_get_res_path(GUI_RES_EDITOR_ON_PNG), NULL);
    lv_imgbtn_set_src(ui_scr->video_file_imgbtn_3, LV_IMGBTN_STATE_CHECKED_RELEASED, NULL, gui_get_res_path(GUI_RES_EDIT_PNG), NULL);
    lv_imgbtn_set_src(ui_scr->video_file_imgbtn_3, LV_IMGBTN_STATE_CHECKED_PRESSED, NULL, gui_get_res_path(GUI_RES_EDITOR_ON_PNG), NULL);
    lv_obj_add_flag(ui_scr->video_file_imgbtn_3, LV_OBJ_FLAG_CHECKABLE);
    ui_scr->video_file_imgbtn_3_label = lv_label_create(ui_scr->video_file_imgbtn_3);
    lv_label_set_text(ui_scr->video_file_imgbtn_3_label, "");
    lv_obj_set_style_pad_all(ui_scr->video_file_imgbtn_3, 0, LV_STATE_DEFAULT);
    lv_obj_align(ui_scr->video_file_imgbtn_3_label, LV_ALIGN_CENTER, 0, 0);

    //Write codes video_file_imgbtn_1
    ui_scr->video_file_imgbtn_1 = lv_imgbtn_create(ui_scr->video_file_view_8);
    lv_obj_set_pos(ui_scr->video_file_imgbtn_1, 16, 204);
    lv_obj_set_size(ui_scr->video_file_imgbtn_1, 48, 48);
    lv_obj_set_scrollbar_mode(ui_scr->video_file_imgbtn_1, LV_SCROLLBAR_MODE_OFF);
    lv_group_add_obj(def_group, ui_scr->video_file_imgbtn_1);
    ui_style_set(ui_scr->video_file_imgbtn_1, GUI_CTRL_IMGBTN);
    lv_imgbtn_set_src(ui_scr->video_file_imgbtn_1, LV_IMGBTN_STATE_RELEASED, NULL, gui_get_res_path(GUI_RES_LOCK_1_PNG), NULL);
    lv_imgbtn_set_src(ui_scr->video_file_imgbtn_1, LV_IMGBTN_STATE_PRESSED, NULL, gui_get_res_path(GUI_RES_LOCK_ON_PNG), NULL);
    lv_imgbtn_set_src(ui_scr->video_file_imgbtn_1, LV_IMGBTN_STATE_CHECKED_RELEASED, NULL, gui_get_res_path(GUI_RES_LOCK_1_PNG), NULL);
    lv_imgbtn_set_src(ui_scr->video_file_imgbtn_1, LV_IMGBTN_STATE_CHECKED_PRESSED, NULL, gui_get_res_path(GUI_RES_LOCK_ON_PNG), NULL);
    lv_obj_add_flag(ui_scr->video_file_imgbtn_1, LV_OBJ_FLAG_CHECKABLE);
    ui_scr->video_file_imgbtn_1_label = lv_label_create(ui_scr->video_file_imgbtn_1);
    lv_label_set_text(ui_scr->video_file_imgbtn_1_label, "");
    lv_obj_set_style_pad_all(ui_scr->video_file_imgbtn_1, 0, LV_STATE_DEFAULT);
    lv_obj_align(ui_scr->video_file_imgbtn_1_label, LV_ALIGN_CENTER, 0, 0);

    //Write codes video_file_imgbtn_5
    ui_scr->video_file_imgbtn_5 = lv_imgbtn_create(ui_scr->video_file_view_8);
    lv_obj_set_pos(ui_scr->video_file_imgbtn_5, 16, 367);
    lv_obj_set_size(ui_scr->video_file_imgbtn_5, 48, 56);
    lv_obj_set_scrollbar_mode(ui_scr->video_file_imgbtn_5, LV_SCROLLBAR_MODE_OFF);
    lv_obj_clear_flag(ui_scr->video_file_imgbtn_5, LV_OBJ_FLAG_HIDDEN);
    lv_group_add_obj(def_group, ui_scr->video_file_imgbtn_5);
    ui_style_set(ui_scr->video_file_imgbtn_5, GUI_CTRL_IMGBTN);
    lv_imgbtn_set_src(ui_scr->video_file_imgbtn_5, LV_IMGBTN_STATE_RELEASED, NULL, gui_get_res_path(GUI_RES_HOME_1_PNG), NULL);
    lv_imgbtn_set_src(ui_scr->video_file_imgbtn_5, LV_IMGBTN_STATE_PRESSED, NULL, gui_get_res_path(GUI_RES_HOME_ON_PNG), NULL);
    lv_imgbtn_set_src(ui_scr->video_file_imgbtn_5, LV_IMGBTN_STATE_CHECKED_RELEASED, NULL, gui_get_res_path(GUI_RES_HOME_1_PNG), NULL);
    lv_imgbtn_set_src(ui_scr->video_file_imgbtn_5, LV_IMGBTN_STATE_CHECKED_PRESSED, NULL, gui_get_res_path(GUI_RES_HOME_ON_PNG), NULL);
    lv_obj_add_flag(ui_scr->video_file_imgbtn_5, LV_OBJ_FLAG_CHECKABLE);
    ui_scr->video_file_imgbtn_5_label = lv_label_create(ui_scr->video_file_imgbtn_5);
    lv_label_set_text(ui_scr->video_file_imgbtn_5_label, "");
    lv_obj_set_style_pad_all(ui_scr->video_file_imgbtn_5, 0, LV_STATE_DEFAULT);
    lv_obj_align(ui_scr->video_file_imgbtn_5_label, LV_ALIGN_CENTER, 0, 0);

    //Write codes video_file_imgbtn_2
    ui_scr->video_file_imgbtn_2 = lv_imgbtn_create(ui_scr->video_file_view_8);
    lv_obj_set_pos(ui_scr->video_file_imgbtn_2, 16, 367);
    lv_obj_set_size(ui_scr->video_file_imgbtn_2, 48, 56);
    lv_obj_set_scrollbar_mode(ui_scr->video_file_imgbtn_2, LV_SCROLLBAR_MODE_OFF);
    lv_group_add_obj(def_group, ui_scr->video_file_imgbtn_2);

    //Hidden for widget video_file_imgbtn_2
    lv_obj_add_flag(ui_scr->video_file_imgbtn_2, LV_OBJ_FLAG_HIDDEN);
    ui_style_set(ui_scr->video_file_imgbtn_2, GUI_CTRL_IMGBTN);
    lv_imgbtn_set_src(ui_scr->video_file_imgbtn_2, LV_IMGBTN_STATE_RELEASED, NULL, gui_get_res_path(GUI_RES_DELETE_PNG), NULL);
    lv_imgbtn_set_src(ui_scr->video_file_imgbtn_2, LV_IMGBTN_STATE_PRESSED, NULL, gui_get_res_path(GUI_RES_DELETE_ON_PNG), NULL);
    lv_imgbtn_set_src(ui_scr->video_file_imgbtn_2, LV_IMGBTN_STATE_CHECKED_RELEASED, NULL, gui_get_res_path(GUI_RES_DELETE_PNG), NULL);
    lv_imgbtn_set_src(ui_scr->video_file_imgbtn_2, LV_IMGBTN_STATE_CHECKED_PRESSED, NULL, gui_get_res_path(GUI_RES_DELETE_ON_PNG), NULL);
    lv_obj_add_flag(ui_scr->video_file_imgbtn_2, LV_OBJ_FLAG_CHECKABLE);
    ui_scr->video_file_imgbtn_2_label = lv_label_create(ui_scr->video_file_imgbtn_2);
    lv_label_set_text(ui_scr->video_file_imgbtn_2_label, "");
    lv_obj_set_style_pad_all(ui_scr->video_file_imgbtn_2, 0, LV_STATE_DEFAULT);
    lv_obj_align(ui_scr->video_file_imgbtn_2_label, LV_ALIGN_CENTER, 0, 0);

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

    //Write codes video_file_view_3
    ui_scr->video_file_view_3 = lv_obj_create(ui_scr->video_file);
    lv_obj_set_pos(ui_scr->video_file_view_3, 85, 50);
    lv_obj_set_size(ui_scr->video_file_view_3, 630, 424);
    lv_obj_set_scrollbar_mode(ui_scr->video_file_view_3, LV_SCROLLBAR_MODE_ON);
    lv_obj_clear_flag(ui_scr->video_file_view_3, LV_OBJ_FLAG_SCROLL_ELASTIC);
    lv_group_add_obj(def_group, ui_scr->video_file_view_3);
    ui_style_set(ui_scr->video_file_view_3, GUI_CTRL_CONT);

    //Set style for video_file_view_3. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
    lv_obj_set_style_bg_opa(ui_scr->video_file_view_3, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui_scr->video_file_view_3, 2, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui_scr->video_file_view_3, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_side(ui_scr->video_file_view_3, LV_BORDER_SIDE_NONE, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_outline_width(ui_scr->video_file_view_3, 2, LV_PART_MAIN | LV_STATE_DEFAULT);

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

    lv_obj_update_layout(ui_scr->video_file);
    ui_scr->video_file_del = false;
    i18n_refresh_texts("video_file");

    //Init events for screen
    events_init_video_file(ui);
    return ui_scr->video_file;
}
void unload_scr_video_file(lv_ui *ui)
{
    ui_free_scr_ptr(ui, GUI_SCREEN_VIDEO_FILE);
}

#endif
