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

static const char *video_dec_imglist_1_imgs[2] = {
#if LV_USE_GUIBUILDER_SIMULATOR
    "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\LY_UI\\dec\\video.png",
    "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\LY_UI\\dec\\photo.png"
#else
    "mnt/sdfile/EXT_RESERVED/uipackres/ui/4b000070.zip",
    "mnt/sdfile/EXT_RESERVED/uipackres/ui/4b000071.zip"
#endif
};
static const char *video_dec_imglist_2_imgs[2] = {
#if LV_USE_GUIBUILDER_SIMULATOR
    "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\LY_UI\\rec\\rec_scan\\card_offline.png",
    "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\LY_UI\\rec\\rec_scan\\card_online.png"
#else
    "mnt/sdfile/EXT_RESERVED/uipackres/ui/4b000072.zip",
    "mnt/sdfile/EXT_RESERVED/uipackres/ui/4b00002b.zip"
#endif
};
static const char *video_dec_imglist_3_imgs[2] = {
#if LV_USE_GUIBUILDER_SIMULATOR
    "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\LY_UI\\dec\\play.png",
    "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\LY_UI\\dec\\pause.png"
#else
    "mnt/sdfile/EXT_RESERVED/uipackres/ui/4b000073.zip",
    "mnt/sdfile/EXT_RESERVED/uipackres/ui/4b000074.zip"
#endif
};

lv_obj_t *setup_scr_video_dec(lv_ui *ui)
{
    lv_ui_video_dec *ui_scr = ui_get_scr_ptr(ui, GUI_SCREEN_VIDEO_DEC);
    if (ui_scr == NULL) {
        ui_scr = lv_mem_alloc(sizeof(lv_ui_video_dec));
        if (ui_scr == NULL) {
            return NULL;
        }
        memset(ui_scr, 0, sizeof(lv_ui_video_dec));
        ui->video_dec = ui_scr;
    }

    //Write codes video_dec
    ui_scr->video_dec = lv_obj_create(NULL);
    lv_group_t *def_group = lv_group_get_default();
    lv_obj_set_scrollbar_mode(ui_scr->video_dec, LV_SCROLLBAR_MODE_OFF);
    ui_style_set(ui_scr->video_dec, GUI_CTRL_SCR);

    //Set style for video_dec. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
    lv_obj_set_style_bg_color(ui_scr->video_dec, lv_color_make(0x55, 0xaa, 0xa5), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui_scr->video_dec, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

    //Write codes video_dec_view_scan
    ui_scr->video_dec_view_scan = lv_obj_create(ui_scr->video_dec);
    lv_obj_set_pos(ui_scr->video_dec_view_scan, 0, 0);
    lv_obj_set_size(ui_scr->video_dec_view_scan, 800, 480);
    lv_obj_set_scrollbar_mode(ui_scr->video_dec_view_scan, LV_SCROLLBAR_MODE_OFF);
    lv_group_add_obj(def_group, ui_scr->video_dec_view_scan);
    ui_style_set(ui_scr->video_dec_view_scan, GUI_CTRL_CONT);

    //Set style for video_dec_view_scan. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
    lv_obj_set_style_shadow_opa(ui_scr->video_dec_view_scan, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui_scr->video_dec_view_scan, 2, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui_scr->video_dec_view_scan, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_outline_opa(ui_scr->video_dec_view_scan, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

    //Delete extra default style for video_dec_view_scan
    lv_obj_remove_style(ui_scr->video_dec_view_scan, &gui_cont_main_focus_key_style, LV_PART_MAIN | LV_STATE_FOCUS_KEY);

    //Write codes video_dec_imglist_1
    ui_scr->video_dec_imglist_1 = lv_imglist_create(ui_scr->video_dec_view_scan);
    lv_obj_set_pos(ui_scr->video_dec_imglist_1, 12, 10);
    lv_obj_set_size(ui_scr->video_dec_imglist_1, 30, 29);
    lv_obj_set_scrollbar_mode(ui_scr->video_dec_imglist_1, LV_SCROLLBAR_MODE_OFF);
    ui_style_set(ui_scr->video_dec_imglist_1, GUI_CTRL_IMGLIST);

    //Set style for video_dec_imglist_1. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
    lv_obj_set_style_outline_opa(ui_scr->video_dec_imglist_1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_imglist_set_src(ui_scr->video_dec_imglist_1, (const void **) video_dec_imglist_1_imgs, 2);
    lv_imglist_set_act(ui_scr->video_dec_imglist_1, 0);

    //Write codes video_dec_edit_2
    ui_scr->video_dec_edit_2 = lv_textarea_create(ui_scr->video_dec_view_scan);
    lv_obj_set_pos(ui_scr->video_dec_edit_2, 545, 24);
    lv_obj_set_size(ui_scr->video_dec_edit_2, 282, 37);
    lv_obj_set_scrollbar_mode(ui_scr->video_dec_edit_2, LV_SCROLLBAR_MODE_OFF);
    lv_obj_add_flag(ui_scr->video_dec_edit_2, LV_OBJ_FLAG_CLICKABLE | LV_OBJ_FLAG_CHECKABLE | LV_OBJ_FLAG_CLICK_FOCUSABLE);
    lv_group_remove_obj(ui_scr->video_dec_edit_2);
    ui_style_set(ui_scr->video_dec_edit_2, GUI_CTRL_TEXTAREA);
    lv_textarea_set_text(ui_scr->video_dec_edit_2, "VID_0001.AVI");
    lv_textarea_set_one_line(ui_scr->video_dec_edit_2, false);

    //Write codes video_dec_edit_3
    ui_scr->video_dec_edit_3 = lv_textarea_create(ui_scr->video_dec_view_scan);
    lv_obj_set_pos(ui_scr->video_dec_edit_3, 545, 62);
    lv_obj_set_size(ui_scr->video_dec_edit_3, 282, 36);
    lv_obj_set_scrollbar_mode(ui_scr->video_dec_edit_3, LV_SCROLLBAR_MODE_OFF);
    lv_obj_add_flag(ui_scr->video_dec_edit_3, LV_OBJ_FLAG_CHECKABLE | LV_OBJ_FLAG_CLICKABLE | LV_OBJ_FLAG_CLICK_FOCUSABLE);
    lv_group_remove_obj(ui_scr->video_dec_edit_3);
    ui_style_set(ui_scr->video_dec_edit_3, GUI_CTRL_TEXTAREA);
    lv_textarea_set_text(ui_scr->video_dec_edit_3, "720P");
    lv_textarea_set_one_line(ui_scr->video_dec_edit_3, false);

    //Write codes video_dec_imglist_2
    ui_scr->video_dec_imglist_2 = lv_imglist_create(ui_scr->video_dec_view_scan);
    lv_obj_set_pos(ui_scr->video_dec_imglist_2, 738, 407);
    lv_obj_set_size(ui_scr->video_dec_imglist_2, 29, 29);
    lv_obj_set_scrollbar_mode(ui_scr->video_dec_imglist_2, LV_SCROLLBAR_MODE_OFF);
    ui_style_set(ui_scr->video_dec_imglist_2, GUI_CTRL_IMGLIST);

    //Set style for video_dec_imglist_2. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
    lv_obj_set_style_outline_opa(ui_scr->video_dec_imglist_2, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_imglist_set_src(ui_scr->video_dec_imglist_2, (const void **) video_dec_imglist_2_imgs, 2);
    lv_imglist_set_act(ui_scr->video_dec_imglist_2, 0);

    //Write codes video_dec_view_1
    ui_scr->video_dec_view_1 = lv_obj_create(ui_scr->video_dec_view_scan);
    lv_obj_set_pos(ui_scr->video_dec_view_1, 1, 398);
    lv_obj_set_size(ui_scr->video_dec_view_1, 468, 63);
    lv_obj_set_scrollbar_mode(ui_scr->video_dec_view_1, LV_SCROLLBAR_MODE_OFF);

    //Hidden for widget video_dec_view_1
    lv_obj_add_flag(ui_scr->video_dec_view_1, LV_OBJ_FLAG_HIDDEN);
    ui_style_set(ui_scr->video_dec_view_1, GUI_CTRL_CONT);

    //Set style for video_dec_view_1. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
    lv_obj_set_style_shadow_opa(ui_scr->video_dec_view_1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui_scr->video_dec_view_1, 2, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui_scr->video_dec_view_1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_outline_opa(ui_scr->video_dec_view_1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

    //Delete extra default style for video_dec_view_1
    lv_obj_remove_style(ui_scr->video_dec_view_1, &gui_cont_main_focus_key_style, LV_PART_MAIN | LV_STATE_FOCUS_KEY);

    //Write codes video_dec_imglist_3
    ui_scr->video_dec_imglist_3 = lv_imglist_create(ui_scr->video_dec_view_1);
    lv_obj_set_pos(ui_scr->video_dec_imglist_3, 93, 15);
    lv_obj_set_size(ui_scr->video_dec_imglist_3, 24, 24);
    lv_obj_set_scrollbar_mode(ui_scr->video_dec_imglist_3, LV_SCROLLBAR_MODE_OFF);
    ui_style_set(ui_scr->video_dec_imglist_3, GUI_CTRL_IMGLIST);

    //Set style for video_dec_imglist_3. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
    lv_obj_set_style_outline_opa(ui_scr->video_dec_imglist_3, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_imglist_set_src(ui_scr->video_dec_imglist_3, (const void **) video_dec_imglist_3_imgs, 2);
    lv_imglist_set_act(ui_scr->video_dec_imglist_3, 0);

    //Write codes video_dec_edit_1
    ui_scr->video_dec_edit_1 = lv_textarea_create(ui_scr->video_dec_view_1);
    lv_obj_set_pos(ui_scr->video_dec_edit_1, 124, 7);
    lv_obj_set_size(ui_scr->video_dec_edit_1, 204, 40);
    lv_obj_set_scrollbar_mode(ui_scr->video_dec_edit_1, LV_SCROLLBAR_MODE_OFF);
    lv_obj_add_flag(ui_scr->video_dec_edit_1, LV_OBJ_FLAG_CHECKABLE | LV_OBJ_FLAG_CLICKABLE | LV_OBJ_FLAG_CLICK_FOCUSABLE);
    lv_group_remove_obj(ui_scr->video_dec_edit_1);
    ui_style_set(ui_scr->video_dec_edit_1, GUI_CTRL_TEXTAREA);

    //Set style for video_dec_edit_1. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
    lv_obj_set_style_text_font(ui_scr->video_dec_edit_1, &lv_font_montserratMedium_20, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_textarea_set_text(ui_scr->video_dec_edit_1, "00:00 / 03:00");
    lv_textarea_set_one_line(ui_scr->video_dec_edit_1, false);

    //Write codes video_dec_img_1
    ui_scr->video_dec_img_1 = lv_img_create(ui_scr->video_dec_view_scan);
    lv_img_set_src(ui_scr->video_dec_img_1, gui_get_res_path(GUI_RES_PROTECT_PNG));
    lv_img_set_pivot(ui_scr->video_dec_img_1, 0, 0);
    lv_img_set_angle(ui_scr->video_dec_img_1, 0);
    lv_img_set_zoom(ui_scr->video_dec_img_1, 256);
    lv_obj_set_pos(ui_scr->video_dec_img_1, 74, 10);
    lv_obj_set_size(ui_scr->video_dec_img_1, 29, 29);
    lv_obj_add_flag(ui_scr->video_dec_img_1, LV_OBJ_FLAG_CLICKABLE);

    //Hidden for widget video_dec_img_1
    lv_obj_add_flag(ui_scr->video_dec_img_1, LV_OBJ_FLAG_HIDDEN);
    ui_style_set(ui_scr->video_dec_img_1, GUI_CTRL_IMG);

    //Set style for video_dec_img_1. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
    lv_obj_set_style_outline_opa(ui_scr->video_dec_img_1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

    //Write codes video_dec_view_5
    ui_scr->video_dec_view_5 = lv_obj_create(ui_scr->video_dec);
    lv_obj_set_pos(ui_scr->video_dec_view_5, 0, 0);
    lv_obj_set_size(ui_scr->video_dec_view_5, 800, 480);
    lv_obj_set_scrollbar_mode(ui_scr->video_dec_view_5, LV_SCROLLBAR_MODE_OFF);
    lv_obj_add_flag(ui_scr->video_dec_view_5, LV_OBJ_FLAG_HIDDEN);
    ui_style_set(ui_scr->video_dec_view_5, GUI_CTRL_CONT);

    //Delete extra default style for video_dec_view_5
    lv_obj_remove_style(ui_scr->video_dec_view_5, &gui_cont_main_focus_key_style, LV_PART_MAIN | LV_STATE_FOCUS_KEY);

    //Write codes video_dec_view_4
    ui_scr->video_dec_view_4 = lv_obj_create(ui_scr->video_dec_view_5);
    lv_obj_set_pos(ui_scr->video_dec_view_4, 0, 40);
    lv_obj_set_size(ui_scr->video_dec_view_4, 800, 400);
    lv_obj_set_scrollbar_mode(ui_scr->video_dec_view_4, LV_SCROLLBAR_MODE_OFF);
    lv_obj_add_flag(ui_scr->video_dec_view_4, LV_OBJ_FLAG_EVENT_BUBBLE);
    ui_style_set(ui_scr->video_dec_view_4, GUI_CTRL_CONT);

    //Set style for video_dec_view_4. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
    lv_obj_set_style_bg_color(ui_scr->video_dec_view_4, lv_color_make(0x61, 0x61, 0x61), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_scr->video_dec_view_4, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui_scr->video_dec_view_4, lv_color_make(0x21, 0x95, 0xF6), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui_scr->video_dec_view_4, 2, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui_scr->video_dec_view_4, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_outline_color(ui_scr->video_dec_view_4, lv_color_make(0x21, 0x95, 0xF6), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_outline_opa(ui_scr->video_dec_view_4, 91, LV_PART_MAIN | LV_STATE_DEFAULT);

    //Delete extra default style for video_dec_view_4
    lv_obj_remove_style(ui_scr->video_dec_view_4, &gui_cont_main_focus_key_style, LV_PART_MAIN | LV_STATE_FOCUS_KEY);

    //Write codes video_dec_view_2
    ui_scr->video_dec_view_2 = lv_obj_create(ui_scr->video_dec_view_4);
    lv_obj_set_pos(ui_scr->video_dec_view_2, 0, 0);
    lv_obj_set_size(ui_scr->video_dec_view_2, 800, 43);
    lv_obj_set_scrollbar_mode(ui_scr->video_dec_view_2, LV_SCROLLBAR_MODE_OFF);
    lv_obj_add_flag(ui_scr->video_dec_view_2, LV_OBJ_FLAG_EVENT_BUBBLE | LV_OBJ_FLAG_SCROLL_ON_FOCUS);
    lv_group_add_obj(def_group, ui_scr->video_dec_view_2);
    ui_style_set(ui_scr->video_dec_view_2, GUI_CTRL_CONT);

    //Write codes video_dec_img_2
    ui_scr->video_dec_img_2 = lv_img_create(ui_scr->video_dec_view_2);
    lv_img_set_src(ui_scr->video_dec_img_2, gui_get_res_path(GUI_RES_DELET_PNG));
    lv_img_set_pivot(ui_scr->video_dec_img_2, 0, 0);
    lv_img_set_angle(ui_scr->video_dec_img_2, 0);
    lv_img_set_zoom(ui_scr->video_dec_img_2, 256);
    lv_obj_set_pos(ui_scr->video_dec_img_2, 8, 6);
    lv_obj_set_size(ui_scr->video_dec_img_2, 29, 29);
    lv_obj_add_flag(ui_scr->video_dec_img_2, LV_OBJ_FLAG_CLICKABLE);
    ui_style_set(ui_scr->video_dec_img_2, GUI_CTRL_IMG);

    //Set style for video_dec_img_2. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
    lv_obj_set_style_bg_color(ui_scr->video_dec_img_2, lv_color_make(0xFF, 0xFF, 0xFF), LV_PART_MAIN | LV_STATE_DEFAULT);

    //Write codes video_dec_lbl_1
    ui_scr->video_dec_lbl_1 = lv_label_create(ui_scr->video_dec_view_2);
    lv_label_set_long_mode(ui_scr->video_dec_lbl_1, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui_scr->video_dec_lbl_1, 50, 6);
    lv_obj_set_size(ui_scr->video_dec_lbl_1, 200, 32);
    lv_obj_set_scrollbar_mode(ui_scr->video_dec_lbl_1, LV_SCROLLBAR_MODE_OFF);
    ui_style_set(ui_scr->video_dec_lbl_1, GUI_CTRL_LABEL);

    //Write codes video_dec_view_3
    ui_scr->video_dec_view_3 = lv_obj_create(ui_scr->video_dec_view_4);
    lv_obj_set_pos(ui_scr->video_dec_view_3, 0, 45);
    lv_obj_set_size(ui_scr->video_dec_view_3, 800, 43);
    lv_obj_set_scrollbar_mode(ui_scr->video_dec_view_3, LV_SCROLLBAR_MODE_OFF);
    lv_obj_add_flag(ui_scr->video_dec_view_3, LV_OBJ_FLAG_EVENT_BUBBLE | LV_OBJ_FLAG_SCROLL_ON_FOCUS);
    lv_group_add_obj(def_group, ui_scr->video_dec_view_3);
    ui_style_set(ui_scr->video_dec_view_3, GUI_CTRL_CONT);

    //Write codes video_dec_img_3
    ui_scr->video_dec_img_3 = lv_img_create(ui_scr->video_dec_view_3);
    lv_img_set_src(ui_scr->video_dec_img_3, gui_get_res_path(GUI_RES_PROTECT_PNG));
    lv_img_set_pivot(ui_scr->video_dec_img_3, 0, 0);
    lv_img_set_angle(ui_scr->video_dec_img_3, 0);
    lv_img_set_zoom(ui_scr->video_dec_img_3, 256);
    lv_obj_set_pos(ui_scr->video_dec_img_3, 8, 6);
    lv_obj_set_size(ui_scr->video_dec_img_3, 29, 29);
    lv_obj_add_flag(ui_scr->video_dec_img_3, LV_OBJ_FLAG_CLICKABLE);
    ui_style_set(ui_scr->video_dec_img_3, GUI_CTRL_IMG);

    //Set style for video_dec_img_3. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
    lv_obj_set_style_bg_color(ui_scr->video_dec_img_3, lv_color_make(0xFF, 0xFF, 0xFF), LV_PART_MAIN | LV_STATE_DEFAULT);

    //Write codes video_dec_lbl_2
    ui_scr->video_dec_lbl_2 = lv_label_create(ui_scr->video_dec_view_3);
    lv_label_set_long_mode(ui_scr->video_dec_lbl_2, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui_scr->video_dec_lbl_2, 50, 6);
    lv_obj_set_size(ui_scr->video_dec_lbl_2, 200, 32);
    lv_obj_set_scrollbar_mode(ui_scr->video_dec_lbl_2, LV_SCROLLBAR_MODE_OFF);
    ui_style_set(ui_scr->video_dec_lbl_2, GUI_CTRL_LABEL);

    //Write codes video_dec_img_4
    ui_scr->video_dec_img_4 = lv_img_create(ui_scr->video_dec_view_5);
    lv_img_set_src(ui_scr->video_dec_img_4, gui_get_res_path(GUI_RES_MENU_STA_PNG));
    lv_img_set_pivot(ui_scr->video_dec_img_4, 0, 0);
    lv_img_set_angle(ui_scr->video_dec_img_4, 0);
    lv_img_set_zoom(ui_scr->video_dec_img_4, 256);
    lv_obj_set_pos(ui_scr->video_dec_img_4, 0, 0);
    lv_obj_set_size(ui_scr->video_dec_img_4, 800, 40);
    lv_obj_add_flag(ui_scr->video_dec_img_4, LV_OBJ_FLAG_CLICKABLE);
    ui_style_set(ui_scr->video_dec_img_4, GUI_CTRL_IMG);

    //Set style for video_dec_img_4. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
    lv_obj_set_style_outline_opa(ui_scr->video_dec_img_4, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

    //Write codes video_dec_img_5
    ui_scr->video_dec_img_5 = lv_img_create(ui_scr->video_dec_view_5);
    lv_img_set_src(ui_scr->video_dec_img_5, gui_get_res_path(GUI_RES_MENU_STA_PNG));
    lv_img_set_pivot(ui_scr->video_dec_img_5, 0, 0);
    lv_img_set_angle(ui_scr->video_dec_img_5, 0);
    lv_img_set_zoom(ui_scr->video_dec_img_5, 256);
    lv_obj_set_pos(ui_scr->video_dec_img_5, 0, 440);
    lv_obj_set_size(ui_scr->video_dec_img_5, 800, 40);
    lv_obj_add_flag(ui_scr->video_dec_img_5, LV_OBJ_FLAG_CLICKABLE);
    ui_style_set(ui_scr->video_dec_img_5, GUI_CTRL_IMG);

    //Set style for video_dec_img_5. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
    lv_obj_set_style_outline_opa(ui_scr->video_dec_img_5, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

    //Write codes video_dec_img_6
    ui_scr->video_dec_img_6 = lv_img_create(ui_scr->video_dec_view_5);
    lv_img_set_src(ui_scr->video_dec_img_6, gui_get_res_path(GUI_RES_PLAY_PNG));
    lv_img_set_pivot(ui_scr->video_dec_img_6, 0, 0);
    lv_img_set_angle(ui_scr->video_dec_img_6, 0);
    lv_img_set_zoom(ui_scr->video_dec_img_6, 256);
    lv_obj_set_pos(ui_scr->video_dec_img_6, 9, 0);
    lv_obj_set_size(ui_scr->video_dec_img_6, 39, 39);
    lv_obj_add_flag(ui_scr->video_dec_img_6, LV_OBJ_FLAG_CLICKABLE);
    ui_style_set(ui_scr->video_dec_img_6, GUI_CTRL_IMG);

    //Set style for video_dec_img_6. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
    lv_obj_set_style_bg_color(ui_scr->video_dec_img_6, lv_color_make(0x42, 0xA5, 0xF5), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_scr->video_dec_img_6, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_outline_color(ui_scr->video_dec_img_6, lv_color_make(0x42, 0xA5, 0xF5), LV_PART_MAIN | LV_STATE_DEFAULT);

    //Write codes video_dec_img_7
    ui_scr->video_dec_img_7 = lv_img_create(ui_scr->video_dec_view_5);
    lv_img_set_src(ui_scr->video_dec_img_7, gui_get_res_path(GUI_RES_SET_PNG));
    lv_img_set_pivot(ui_scr->video_dec_img_7, 0, 0);
    lv_img_set_angle(ui_scr->video_dec_img_7, 0);
    lv_img_set_zoom(ui_scr->video_dec_img_7, 256);
    lv_obj_set_pos(ui_scr->video_dec_img_7, 70, 1);
    lv_obj_set_size(ui_scr->video_dec_img_7, 37, 37);
    lv_obj_add_flag(ui_scr->video_dec_img_7, LV_OBJ_FLAG_CLICKABLE);
    ui_style_set(ui_scr->video_dec_img_7, GUI_CTRL_IMG);

    //Set style for video_dec_img_7. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
    lv_obj_set_style_bg_color(ui_scr->video_dec_img_7, lv_color_make(0x42, 0xA5, 0xF5), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_outline_color(ui_scr->video_dec_img_7, lv_color_make(0x42, 0xA5, 0xF5), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_outline_opa(ui_scr->video_dec_img_7, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    //Write codes video_dec_img_8
    ui_scr->video_dec_img_8 = lv_img_create(ui_scr->video_dec_view_5);
    lv_img_set_src(ui_scr->video_dec_img_8, gui_get_res_path(GUI_RES_LEFT_PNG));
    lv_img_set_pivot(ui_scr->video_dec_img_8, 0, 0);
    lv_img_set_angle(ui_scr->video_dec_img_8, 0);
    lv_img_set_zoom(ui_scr->video_dec_img_8, 256);
    lv_obj_set_pos(ui_scr->video_dec_img_8, 200, 445);
    lv_obj_set_size(ui_scr->video_dec_img_8, 21, 29);
    lv_obj_add_flag(ui_scr->video_dec_img_8, LV_OBJ_FLAG_CLICKABLE);
    ui_style_set(ui_scr->video_dec_img_8, GUI_CTRL_IMG);

    //Write codes video_dec_img_9
    ui_scr->video_dec_img_9 = lv_img_create(ui_scr->video_dec_view_5);
    lv_img_set_src(ui_scr->video_dec_img_9, gui_get_res_path(GUI_RES_UP_PNG));
    lv_img_set_pivot(ui_scr->video_dec_img_9, 0, 0);
    lv_img_set_angle(ui_scr->video_dec_img_9, 0);
    lv_img_set_zoom(ui_scr->video_dec_img_9, 256);
    lv_obj_set_pos(ui_scr->video_dec_img_9, 321, 448);
    lv_obj_set_size(ui_scr->video_dec_img_9, 29, 21);
    lv_obj_add_flag(ui_scr->video_dec_img_9, LV_OBJ_FLAG_CLICKABLE);
    ui_style_set(ui_scr->video_dec_img_9, GUI_CTRL_IMG);

    //Write codes video_dec_img_10
    ui_scr->video_dec_img_10 = lv_img_create(ui_scr->video_dec_view_5);
    lv_img_set_src(ui_scr->video_dec_img_10, gui_get_res_path(GUI_RES_DOWN_PNG));
    lv_img_set_pivot(ui_scr->video_dec_img_10, 0, 0);
    lv_img_set_angle(ui_scr->video_dec_img_10, 0);
    lv_img_set_zoom(ui_scr->video_dec_img_10, 256);
    lv_obj_set_pos(ui_scr->video_dec_img_10, 450, 448);
    lv_obj_set_size(ui_scr->video_dec_img_10, 29, 21);
    lv_obj_add_flag(ui_scr->video_dec_img_10, LV_OBJ_FLAG_CLICKABLE);
    ui_style_set(ui_scr->video_dec_img_10, GUI_CTRL_IMG);

    //Write codes video_dec_img_11
    ui_scr->video_dec_img_11 = lv_img_create(ui_scr->video_dec_view_5);
    lv_img_set_src(ui_scr->video_dec_img_11, gui_get_res_path(GUI_RES_RIGHT_PNG));
    lv_img_set_pivot(ui_scr->video_dec_img_11, 0, 0);
    lv_img_set_angle(ui_scr->video_dec_img_11, 0);
    lv_img_set_zoom(ui_scr->video_dec_img_11, 256);
    lv_obj_set_pos(ui_scr->video_dec_img_11, 579, 445);
    lv_obj_set_size(ui_scr->video_dec_img_11, 21, 29);
    lv_obj_add_flag(ui_scr->video_dec_img_11, LV_OBJ_FLAG_CLICKABLE);
    ui_style_set(ui_scr->video_dec_img_11, GUI_CTRL_IMG);

    lv_obj_update_layout(ui_scr->video_dec);
    ui_scr->video_dec_del = false;
    i18n_refresh_texts(GUI_SCREEN_VIDEO_DEC);

    //Init events for screen
    events_init_video_dec(ui);
    return ui_scr->video_dec;
}
void unload_scr_video_dec(lv_ui *ui)
{
    ui_free_scr_ptr(ui, GUI_SCREEN_VIDEO_DEC);
}

#endif
