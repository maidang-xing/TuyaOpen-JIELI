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


lv_obj_t *setup_scr_music_player(lv_ui *ui)
{
    lv_ui_music_player *ui_scr = ui_get_scr_ptr(ui, GUI_SCREEN_MUSIC_PLAYER);
    if (ui_scr == NULL) {
        ui_scr = lv_mem_alloc(sizeof(lv_ui_music_player));
        if (ui_scr == NULL) {
            return NULL;
        }
        memset(ui_scr, 0, sizeof(lv_ui_music_player));
        ui->music_player = ui_scr;
    }

    //Write codes music_player
    ui_scr->music_player = lv_obj_create(NULL);
    lv_obj_set_scrollbar_mode(ui_scr->music_player, LV_SCROLLBAR_MODE_OFF);
    ui_style_set(ui_scr->music_player, GUI_CTRL_SCR);

    //Set style for music_player. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
    lv_obj_set_style_bg_grad_color(ui_scr->music_player, lv_color_make(0x80, 0x81, 0xDB), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_scr->music_player, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

    //Write codes music_player_imgbtn_1
    ui_scr->music_player_imgbtn_1 = lv_imgbtn_create(ui_scr->music_player);
    lv_obj_set_pos(ui_scr->music_player_imgbtn_1, 369, 399);
    lv_obj_set_size(ui_scr->music_player_imgbtn_1, 64, 64);
    lv_obj_set_scrollbar_mode(ui_scr->music_player_imgbtn_1, LV_SCROLLBAR_MODE_OFF);
    ui_style_set(ui_scr->music_player_imgbtn_1, GUI_CTRL_IMGBTN);

    //Set style for music_player_imgbtn_1. Part: LV_PART_MAIN, State: LV_STATE_FOCUSED
    lv_obj_add_style(ui_scr->music_player_imgbtn_1, &gui_imgbtn_main_focused_style, LV_PART_MAIN | LV_STATE_FOCUSED);

    //Set style for music_player_imgbtn_1. Part: LV_PART_MAIN, State: LV_STATE_PRESSED
    lv_obj_set_style_text_font(ui_scr->music_player_imgbtn_1, &lv_font_FangZhengKaiTiJianTi_1_24, LV_PART_MAIN | LV_STATE_PRESSED);
    lv_obj_set_style_img_recolor(ui_scr->music_player_imgbtn_1, lv_color_make(0x00, 0x00, 0x00), LV_PART_MAIN | LV_STATE_PRESSED);
    lv_obj_set_style_img_recolor_opa(ui_scr->music_player_imgbtn_1, 0, LV_PART_MAIN | LV_STATE_PRESSED);

    //Set style for music_player_imgbtn_1. Part: LV_PART_MAIN, State: LV_STATE_CHECKED
    lv_obj_set_style_text_font(ui_scr->music_player_imgbtn_1, &lv_font_FangZhengKaiTiJianTi_1_24, LV_PART_MAIN | LV_STATE_CHECKED);
    lv_imgbtn_set_src(ui_scr->music_player_imgbtn_1, LV_IMGBTN_STATE_RELEASED, NULL, gui_get_res_path(GUI_RES_IMAGE_4225207_0_PNG), NULL);
    lv_imgbtn_set_src(ui_scr->music_player_imgbtn_1, LV_IMGBTN_STATE_PRESSED, NULL, gui_get_res_path(GUI_RES_IMAGE_4225207_0_PNG), NULL);
    lv_imgbtn_set_src(ui_scr->music_player_imgbtn_1, LV_IMGBTN_STATE_CHECKED_RELEASED, NULL, gui_get_res_path(GUI_RES_IMAGE_4225207_1_PNG), NULL);
    lv_imgbtn_set_src(ui_scr->music_player_imgbtn_1, LV_IMGBTN_STATE_CHECKED_PRESSED, NULL, gui_get_res_path(GUI_RES_IMAGE_4225207_1_PNG), NULL);
    lv_obj_add_flag(ui_scr->music_player_imgbtn_1, LV_OBJ_FLAG_CHECKABLE);
    ui_scr->music_player_imgbtn_1_label = lv_label_create(ui_scr->music_player_imgbtn_1);
    lv_label_set_text(ui_scr->music_player_imgbtn_1_label, "");
    lv_obj_set_style_pad_all(ui_scr->music_player_imgbtn_1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_align(ui_scr->music_player_imgbtn_1_label, LV_ALIGN_CENTER, 0, 0);

    //Write codes music_player_imgbtn_2
    ui_scr->music_player_imgbtn_2 = lv_imgbtn_create(ui_scr->music_player);
    lv_obj_set_pos(ui_scr->music_player_imgbtn_2, 445, 399);
    lv_obj_set_size(ui_scr->music_player_imgbtn_2, 64, 64);
    lv_obj_set_scrollbar_mode(ui_scr->music_player_imgbtn_2, LV_SCROLLBAR_MODE_OFF);
    ui_style_set(ui_scr->music_player_imgbtn_2, GUI_CTRL_IMGBTN);

    //Set style for music_player_imgbtn_2. Part: LV_PART_MAIN, State: LV_STATE_PRESSED
    lv_obj_set_style_bg_color(ui_scr->music_player_imgbtn_2, lv_color_make(0xAA, 0xAA, 0xAA), LV_PART_MAIN | LV_STATE_PRESSED);
    lv_imgbtn_set_src(ui_scr->music_player_imgbtn_2, LV_IMGBTN_STATE_RELEASED, NULL, gui_get_res_path(GUI_RES_IMAGE_4225207_2_PNG), NULL);
    lv_imgbtn_set_src(ui_scr->music_player_imgbtn_2, LV_IMGBTN_STATE_PRESSED, NULL, gui_get_res_path(GUI_RES_IMAGE_4225207_2_PNG), NULL);
    lv_imgbtn_set_src(ui_scr->music_player_imgbtn_2, LV_IMGBTN_STATE_CHECKED_RELEASED, NULL, gui_get_res_path(GUI_RES_IMAGE_4225207_2_PNG), NULL);
    lv_imgbtn_set_src(ui_scr->music_player_imgbtn_2, LV_IMGBTN_STATE_CHECKED_PRESSED, NULL, gui_get_res_path(GUI_RES_IMAGE_4225207_2_PNG), NULL);
    lv_obj_add_flag(ui_scr->music_player_imgbtn_2, LV_OBJ_FLAG_CHECKABLE);
    ui_scr->music_player_imgbtn_2_label = lv_label_create(ui_scr->music_player_imgbtn_2);
    lv_label_set_text(ui_scr->music_player_imgbtn_2_label, "");
    lv_obj_set_style_pad_all(ui_scr->music_player_imgbtn_2, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_align(ui_scr->music_player_imgbtn_2_label, LV_ALIGN_CENTER, 0, 0);

    //Write codes music_player_imgbtn_3
    ui_scr->music_player_imgbtn_3 = lv_imgbtn_create(ui_scr->music_player);
    lv_obj_set_pos(ui_scr->music_player_imgbtn_3, 280, 399);
    lv_obj_set_size(ui_scr->music_player_imgbtn_3, 64, 64);
    lv_obj_set_scrollbar_mode(ui_scr->music_player_imgbtn_3, LV_SCROLLBAR_MODE_OFF);
    ui_style_set(ui_scr->music_player_imgbtn_3, GUI_CTRL_IMGBTN);
    lv_imgbtn_set_src(ui_scr->music_player_imgbtn_3, LV_IMGBTN_STATE_RELEASED, NULL, gui_get_res_path(GUI_RES_IMAGE_4225207_3_PNG), NULL);
    lv_imgbtn_set_src(ui_scr->music_player_imgbtn_3, LV_IMGBTN_STATE_PRESSED, NULL, gui_get_res_path(GUI_RES_IMAGE_4225207_3_PNG), NULL);
    lv_imgbtn_set_src(ui_scr->music_player_imgbtn_3, LV_IMGBTN_STATE_CHECKED_RELEASED, NULL, gui_get_res_path(GUI_RES_IMAGE_4225207_3_PNG), NULL);
    lv_imgbtn_set_src(ui_scr->music_player_imgbtn_3, LV_IMGBTN_STATE_CHECKED_PRESSED, NULL, gui_get_res_path(GUI_RES_IMAGE_4225207_3_PNG), NULL);
    lv_obj_add_flag(ui_scr->music_player_imgbtn_3, LV_OBJ_FLAG_CHECKABLE);
    ui_scr->music_player_imgbtn_3_label = lv_label_create(ui_scr->music_player_imgbtn_3);
    lv_label_set_text(ui_scr->music_player_imgbtn_3_label, "");
    lv_obj_set_style_pad_all(ui_scr->music_player_imgbtn_3, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_align(ui_scr->music_player_imgbtn_3_label, LV_ALIGN_CENTER, 0, 0);

    //Write codes music_player_slider_1
    ui_scr->music_player_slider_1 = lv_slider_create(ui_scr->music_player);
    lv_obj_set_pos(ui_scr->music_player_slider_1, 13, 333);
    lv_obj_set_size(ui_scr->music_player_slider_1, 751, 13);
    lv_obj_set_scrollbar_mode(ui_scr->music_player_slider_1, LV_SCROLLBAR_MODE_OFF);
    lv_group_remove_obj(ui_scr->music_player_slider_1);
    ui_style_set(ui_scr->music_player_slider_1, GUI_CTRL_SLIDER);

    //Set style for music_player_slider_1. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
    lv_obj_set_style_bg_color(ui_scr->music_player_slider_1, lv_color_make(0xE9, 0xE9, 0xE9), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_scr->music_player_slider_1, 204, LV_PART_MAIN | LV_STATE_DEFAULT);

    //Set style for music_player_slider_1. Part: LV_PART_INDICATOR, State: LV_STATE_DEFAULT
    lv_obj_set_style_bg_color(ui_scr->music_player_slider_1, lv_color_make(0x21, 0x95, 0xf6), LV_PART_INDICATOR | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_scr->music_player_slider_1, 153, LV_PART_INDICATOR | LV_STATE_DEFAULT);

    //Set style for music_player_slider_1. Part: LV_PART_KNOB, State: LV_STATE_DEFAULT
    lv_obj_set_style_bg_color(ui_scr->music_player_slider_1, lv_color_make(0xFF, 0xFF, 0xFF), LV_PART_KNOB | LV_STATE_DEFAULT);
    lv_slider_set_range(ui_scr->music_player_slider_1, 0, 100);
    lv_slider_set_mode(ui_scr->music_player_slider_1, LV_SLIDER_MODE_NORMAL);
    lv_slider_set_value(ui_scr->music_player_slider_1, 50, LV_ANIM_OFF);
    lv_slider_set_left_value(ui_scr->music_player_slider_1, 0, LV_ANIM_OFF);

    //Write codes music_player_img_2
    ui_scr->music_player_img_2 = lv_img_create(ui_scr->music_player);
    lv_img_set_src(ui_scr->music_player_img_2, gui_get_res_path(GUI_RES_IMAGE_4225532_4_PNG));
    lv_img_set_pivot(ui_scr->music_player_img_2, 0, 0);
    lv_img_set_angle(ui_scr->music_player_img_2, 0);
    lv_img_set_zoom(ui_scr->music_player_img_2, 256);
    lv_obj_set_pos(ui_scr->music_player_img_2, 699, 415);
    lv_obj_set_size(ui_scr->music_player_img_2, 48, 48);
    lv_obj_add_flag(ui_scr->music_player_img_2, LV_OBJ_FLAG_CLICKABLE);
    ui_style_set(ui_scr->music_player_img_2, GUI_CTRL_IMG);

    //Set style for music_player_img_2. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
    lv_obj_set_style_img_recolor(ui_scr->music_player_img_2, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_img_recolor_opa(ui_scr->music_player_img_2, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

    //Write codes music_player_lbl_2
    ui_scr->music_player_lbl_2 = lv_label_create(ui_scr->music_player);
    lv_label_set_text(ui_scr->music_player_lbl_2, "01:27");
    lv_label_set_long_mode(ui_scr->music_player_lbl_2, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui_scr->music_player_lbl_2, 13, 353);
    lv_obj_set_size(ui_scr->music_player_lbl_2, 125, 49);
    lv_obj_set_scrollbar_mode(ui_scr->music_player_lbl_2, LV_SCROLLBAR_MODE_OFF);
    ui_style_set(ui_scr->music_player_lbl_2, GUI_CTRL_LABEL);

    //Set style for music_player_lbl_2. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
    lv_obj_set_style_text_color(ui_scr->music_player_lbl_2, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_scr->music_player_lbl_2, &lv_font_FangZhengKaiTiJianTi_1_32, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui_scr->music_player_lbl_2, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN | LV_STATE_DEFAULT);

    //Write codes music_player_lbl_3
    ui_scr->music_player_lbl_3 = lv_label_create(ui_scr->music_player);
    lv_label_set_text(ui_scr->music_player_lbl_3, "03:54");
    lv_label_set_long_mode(ui_scr->music_player_lbl_3, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui_scr->music_player_lbl_3, 680, 353);
    lv_obj_set_size(ui_scr->music_player_lbl_3, 103, 49);
    lv_obj_set_scrollbar_mode(ui_scr->music_player_lbl_3, LV_SCROLLBAR_MODE_OFF);
    ui_style_set(ui_scr->music_player_lbl_3, GUI_CTRL_LABEL);

    //Set style for music_player_lbl_3. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
    lv_obj_set_style_text_color(ui_scr->music_player_lbl_3, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_scr->music_player_lbl_3, &lv_font_FangZhengKaiTiJianTi_1_32, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui_scr->music_player_lbl_3, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN | LV_STATE_DEFAULT);

    // Write Timer music_player_timer_1
    if (ui_scr->music_player_timer_1 != NULL) {
        lv_timer_del(ui_scr->music_player_timer_1);
    }
    ui_scr->music_player_timer_1 = lv_timer_create(music_player_timer_1_timer_cb, 300, "");
    lv_timer_set_repeat_count(ui_scr->music_player_timer_1, -1);
    lv_timer_pause(ui_scr->music_player_timer_1);

    //Write codes music_player_view_lyrics
    ui_scr->music_player_view_lyrics = lv_obj_create(ui_scr->music_player);
    lv_obj_set_pos(ui_scr->music_player_view_lyrics, 0, 10);
    lv_obj_set_size(ui_scr->music_player_view_lyrics, 800, 319);
    lv_obj_set_scrollbar_mode(ui_scr->music_player_view_lyrics, LV_SCROLLBAR_MODE_OFF);

    //Hidden for widget music_player_view_lyrics
    lv_obj_add_flag(ui_scr->music_player_view_lyrics, LV_OBJ_FLAG_HIDDEN);
    ui_style_set(ui_scr->music_player_view_lyrics, GUI_CTRL_CONT);

    //Set style for music_player_view_lyrics. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
    lv_obj_set_style_radius(ui_scr->music_player_view_lyrics, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui_scr->music_player_view_lyrics, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_scr->music_player_view_lyrics, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

    //Write codes music_player_view_1
    ui_scr->music_player_view_1 = lv_obj_create(ui_scr->music_player);
    lv_obj_set_pos(ui_scr->music_player_view_1, 0, 0);
    lv_obj_set_size(ui_scr->music_player_view_1, 800, 321);
    lv_obj_set_scrollbar_mode(ui_scr->music_player_view_1, LV_SCROLLBAR_MODE_OFF);

    //Hidden for widget music_player_view_1
    lv_obj_add_flag(ui_scr->music_player_view_1, LV_OBJ_FLAG_HIDDEN);
    ui_style_set(ui_scr->music_player_view_1, GUI_CTRL_CONT);

    //Set style for music_player_view_1. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
    lv_obj_set_style_radius(ui_scr->music_player_view_1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui_scr->music_player_view_1, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_scr->music_player_view_1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui_scr->music_player_view_1, lv_color_make(0xFF, 0xFF, 0xFF), LV_PART_MAIN | LV_STATE_DEFAULT);

    //Write codes music_player_img_1
    ui_scr->music_player_img_1 = lv_img_create(ui_scr->music_player_view_1);
    lv_obj_set_pos(ui_scr->music_player_img_1, 301, 62);
    lv_obj_set_size(ui_scr->music_player_img_1, 200, 200);
    lv_obj_add_flag(ui_scr->music_player_img_1, LV_OBJ_FLAG_EVENT_BUBBLE | LV_OBJ_FLAG_CLICKABLE);
    ui_style_set(ui_scr->music_player_img_1, GUI_CTRL_IMG);

    //Set style for music_player_img_1. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
    lv_obj_set_style_img_recolor(ui_scr->music_player_img_1, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_img_recolor_opa(ui_scr->music_player_img_1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

    lv_obj_update_layout(ui_scr->music_player);
    ui_scr->music_player_del = false;

    //Init events for screen
    events_init_music_player(ui);
    return ui_scr->music_player;
}
void unload_scr_music_player(lv_ui *ui)
{
    lv_ui_music_player *ui_scr = ui_get_scr_ptr(ui, GUI_SCREEN_MUSIC_PLAYER);
    if (ui_scr->music_player_timer_1 != NULL) {
        lv_timer_del(ui_scr->music_player_timer_1);
        ui_scr->music_player_timer_1 = NULL;
    }
    ui_free_scr_ptr(ui, GUI_SCREEN_MUSIC_PLAYER);
}
