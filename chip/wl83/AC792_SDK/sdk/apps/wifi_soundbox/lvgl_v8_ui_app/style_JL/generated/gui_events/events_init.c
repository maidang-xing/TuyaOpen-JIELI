/*Generate Code, Do NOT Edit!*/
#include "./events_init.h"
#if LV_USE_GUIBUILDER_SIMULATOR
#include <stdio.h>
#endif
#include "lvgl.h"
#include "./callback_handler.h"
#include "../gui_timelines/gui_timelines.h"
#include "../gui_group/gui_group.h"

void scr_loaded_handler(lv_event_t *e)
{
    lv_obj_t *src = lv_event_get_target(e);
    gui_msg_init_ui();
    gui_msg_init_events();
}

void events_init(lv_ui *ui)
{
}

static void music_player_event_handler(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_GESTURE: {
        lv_dir_t dir = lv_indev_get_gesture_dir(lv_indev_get_act());
        if (dir & LV_DIR_LEFT) {
            gui_scr_t *screen = ui_get_scr(GUI_SCREEN_SYS_MENU);
            if (screen != NULL) {
                ui_load_scr_anim(&guider_ui, screen, LV_SCR_LOAD_ANIM_FADE_IN, 0, 0, false, true, false);
            }
        }
    }
    break;
    default:
        break;
    }
}

static void music_player_imgbtn_1_event_handler(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_CLICKED: {
        gui_get_event_cb(RES_EVENT_PAUSE_OR_PLAY_ID)(e);
    }
    break;
    default:
        break;
    }
}

static void music_player_imgbtn_2_event_handler(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_CLICKED: {
        gui_get_event_cb(RES_EVENT_NEXT_SONG_ID)(e);
    }
    break;
    default:
        break;
    }
}

static void music_player_imgbtn_3_event_handler(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_CLICKED: {
        gui_get_event_cb(RES_EVENT_PREV_SONG_ID)(e);
    }
    break;
    default:
        break;
    }
}

static void music_player_slider_1_event_handler(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_VALUE_CHANGED: {
        gui_get_event_cb(RES_EVENT_MUSIC_PROCESS_CHANGE_ID)(e);
    }
    break;
    default:
        break;
    }
}

static void music_player_img_2_event_handler(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_CLICKED: {
    }
    break;
    default:
        break;
    }
}

static void music_player_view_lyrics_event_handler(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_CLICKED: {
        gui_get_event_cb(RES_EVENT_LYRICS_ALBUM_VIEW_CHANGE_ID)(e);
    }
    break;
    default:
        break;
    }
}

static void music_player_view_1_event_handler(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_CLICKED: {
        gui_get_event_cb(RES_EVENT_LYRICS_ALBUM_VIEW_CHANGE_ID)(e);
    }
    break;
    default:
        break;
    }
}
static void music_player_screen_event_handler(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_SCREEN_LOAD_START: {
        gui_scr_action_cb(GUI_SCREEN_MUSIC_PLAYER, GUI_SCREEN_ACTION_LOAD);
        break;
    }
    case LV_EVENT_SCREEN_UNLOADED: {
        gui_scr_action_cb(GUI_SCREEN_MUSIC_PLAYER, GUI_SCREEN_ACTION_UNLOAD);
        break;
    }
    }
}

void events_init_music_player(lv_ui *ui)
{
    lv_ui_music_player *ui_scr = ui_get_scr_ptr(ui, GUI_SCREEN_MUSIC_PLAYER);
    lv_obj_add_event_cb(ui_scr->music_player, scr_loaded_handler, LV_EVENT_SCREEN_LOADED, ui);
    lv_obj_add_event_cb(ui_scr->music_player, music_player_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui_scr->music_player_imgbtn_1, music_player_imgbtn_1_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui_scr->music_player_imgbtn_2, music_player_imgbtn_2_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui_scr->music_player_imgbtn_3, music_player_imgbtn_3_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui_scr->music_player_slider_1, music_player_slider_1_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui_scr->music_player_img_2, music_player_img_2_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui_scr->music_player_view_lyrics, music_player_view_lyrics_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui_scr->music_player_view_1, music_player_view_1_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui_scr->music_player, music_player_screen_event_handler, LV_EVENT_ALL, ui);
}

static void sys_menu_event_handler(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_GESTURE: {
        lv_dir_t dir = lv_indev_get_gesture_dir(lv_indev_get_act());
        if (dir & LV_DIR_RIGHT) {
            gui_scr_t *screen = ui_get_scr(GUI_SCREEN_MUSIC_PLAYER);
            if (screen != NULL) {
                ui_load_scr_anim(&guider_ui, screen, LV_SCR_LOAD_ANIM_FADE_IN, 0, 0, false, true, false);
            }
        }
    }
    break;
    default:
        break;
    }
}

static void sys_menu_view_1_event_handler(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_CLICKED: {
        gui_scr_t *screen = ui_get_scr(GUI_SCREEN_MUSIC_PLAYER);
        if (screen != NULL) {
            ui_load_scr_anim(&guider_ui, screen, LV_SCR_LOAD_ANIM_NONE, 0, 0, false, true, false);
        }
    }
    break;
    default:
        break;
    }
}

static void sys_menu_view_5_event_handler(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_CLICKED: {
        gui_scr_t *screen = ui_get_scr(GUI_SCREEN_EQ_MODIFY);
        if (screen != NULL) {
            ui_load_scr_anim(&guider_ui, screen, LV_SCR_LOAD_ANIM_NONE, 0, 0, true, true, false);
        }
    }
    break;
    default:
        break;
    }
}

static void sys_menu_slider_1_event_handler(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_VALUE_CHANGED: {
        gui_get_event_cb(RES_EVENT_MUSIC_VOLUME_CHANGE_ID)(e);
    }
    break;
    default:
        break;
    }
}

static void sys_menu_view_6_event_handler(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_CLICKED: {
        gui_scr_t *screen = ui_get_scr(GUI_SCREEN_MUSIC_PLAYER);
        if (screen != NULL) {
            ui_load_scr_anim(&guider_ui, screen, LV_SCR_LOAD_ANIM_NONE, 0, 0, false, true, false);
        }
    }
    break;
    default:
        break;
    }
}

static void sys_menu_imgbtn_4_event_handler(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_CLICKED: {
        gui_get_event_cb(RES_EVENT_PAUSE_OR_PLAY_ID)(e);
    }
    break;
    default:
        break;
    }
}

static void sys_menu_imgbtn_5_event_handler(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_CLICKED: {
        gui_get_event_cb(RES_EVENT_NEXT_SONG_ID)(e);
    }
    break;
    default:
        break;
    }
}

static void sys_menu_imgbtn_6_event_handler(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_CLICKED: {
        gui_get_event_cb(RES_EVENT_PAUSE_OR_PLAY_ID)(e);
    }
    break;
    default:
        break;
    }
}
static void sys_menu_screen_event_handler(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_SCREEN_LOAD_START: {
        gui_scr_action_cb(GUI_SCREEN_SYS_MENU, GUI_SCREEN_ACTION_LOAD);
        break;
    }
    case LV_EVENT_SCREEN_UNLOADED: {
        gui_scr_action_cb(GUI_SCREEN_SYS_MENU, GUI_SCREEN_ACTION_UNLOAD);
        break;
    }
    }
}

void events_init_sys_menu(lv_ui *ui)
{
    lv_ui_sys_menu *ui_scr = ui_get_scr_ptr(ui, GUI_SCREEN_SYS_MENU);
    lv_obj_add_event_cb(ui_scr->sys_menu, scr_loaded_handler, LV_EVENT_SCREEN_LOADED, ui);
    lv_obj_add_event_cb(ui_scr->sys_menu, sys_menu_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui_scr->sys_menu_view_1, sys_menu_view_1_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui_scr->sys_menu_view_5, sys_menu_view_5_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui_scr->sys_menu_slider_1, sys_menu_slider_1_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui_scr->sys_menu_view_6, sys_menu_view_6_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui_scr->sys_menu_imgbtn_4, sys_menu_imgbtn_4_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui_scr->sys_menu_imgbtn_5, sys_menu_imgbtn_5_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui_scr->sys_menu_imgbtn_6, sys_menu_imgbtn_6_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui_scr->sys_menu, sys_menu_screen_event_handler, LV_EVENT_ALL, ui);
}

static void eq_modify_event_handler(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_GESTURE: {
        lv_dir_t dir = lv_indev_get_gesture_dir(lv_indev_get_act());
        if (dir & LV_DIR_RIGHT) {
            gui_scr_t *screen = ui_get_scr(GUI_SCREEN_SYS_MENU);
            if (screen != NULL) {
                ui_load_scr_anim(&guider_ui, screen, LV_SCR_LOAD_ANIM_NONE, 0, 0, true, true, false);
            }
        }
    }
    break;
    default:
        break;
    }
}

static void eq_modify_slider_1_event_handler(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_VALUE_CHANGED: {
        gui_get_event_cb(RES_EVENT_MUSIC_EQ_SAVE_ENABLE_ID)(e);
    }
    break;
    default:
        break;
    }
}

static void eq_modify_slider_2_event_handler(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_VALUE_CHANGED: {
        gui_get_event_cb(RES_EVENT_MUSIC_EQ_SAVE_ENABLE_ID)(e);
    }
    break;
    default:
        break;
    }
}

static void eq_modify_slider_4_event_handler(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_VALUE_CHANGED: {
        gui_get_event_cb(RES_EVENT_MUSIC_EQ_SAVE_ENABLE_ID)(e);
    }
    break;
    default:
        break;
    }
}

static void eq_modify_slider_5_event_handler(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_VALUE_CHANGED: {
        gui_get_event_cb(RES_EVENT_MUSIC_EQ_SAVE_ENABLE_ID)(e);
    }
    break;
    default:
        break;
    }
}

static void eq_modify_slider_6_event_handler(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_VALUE_CHANGED: {
        gui_get_event_cb(RES_EVENT_MUSIC_EQ_SAVE_ENABLE_ID)(e);
    }
    break;
    default:
        break;
    }
}

static void eq_modify_slider_7_event_handler(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_VALUE_CHANGED: {
        gui_get_event_cb(RES_EVENT_MUSIC_EQ_SAVE_ENABLE_ID)(e);
    }
    break;
    default:
        break;
    }
}

static void eq_modify_slider_8_event_handler(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_VALUE_CHANGED: {
        gui_get_event_cb(RES_EVENT_MUSIC_EQ_SAVE_ENABLE_ID)(e);
    }
    break;
    default:
        break;
    }
}

static void eq_modify_slider_9_event_handler(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_VALUE_CHANGED: {
        gui_get_event_cb(RES_EVENT_MUSIC_EQ_SAVE_ENABLE_ID)(e);
    }
    break;
    default:
        break;
    }
}

static void eq_modify_slider_10_event_handler(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_VALUE_CHANGED: {
        gui_get_event_cb(RES_EVENT_MUSIC_EQ_SAVE_ENABLE_ID)(e);
    }
    break;
    default:
        break;
    }
}

static void eq_modify_ddlist_1_event_handler(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_VALUE_CHANGED: {
        gui_get_event_cb(RES_EVENT_MUSIC_EQ_MODE_SET_ID)(e);
    }
    break;
    default:
        break;
    }
}

static void eq_modify_btn_1_event_handler(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_CLICKED: {
        gui_get_event_cb(RES_EVENT_MUSIC_EQ_GAIN_CHANGE_CUSTOM_ID)(e);
    }
    break;
    default:
        break;
    }
}
static void eq_modify_screen_event_handler(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_SCREEN_LOAD_START: {
        gui_scr_action_cb(GUI_SCREEN_EQ_MODIFY, GUI_SCREEN_ACTION_LOAD);
        break;
    }
    case LV_EVENT_SCREEN_UNLOADED: {
        gui_scr_action_cb(GUI_SCREEN_EQ_MODIFY, GUI_SCREEN_ACTION_UNLOAD);
        break;
    }
    }
}

void events_init_eq_modify(lv_ui *ui)
{
    lv_ui_eq_modify *ui_scr = ui_get_scr_ptr(ui, GUI_SCREEN_EQ_MODIFY);
    lv_obj_add_event_cb(ui_scr->eq_modify, scr_loaded_handler, LV_EVENT_SCREEN_LOADED, ui);
    lv_obj_add_event_cb(ui_scr->eq_modify, eq_modify_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui_scr->eq_modify_slider_1, eq_modify_slider_1_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui_scr->eq_modify_slider_2, eq_modify_slider_2_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui_scr->eq_modify_slider_4, eq_modify_slider_4_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui_scr->eq_modify_slider_5, eq_modify_slider_5_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui_scr->eq_modify_slider_6, eq_modify_slider_6_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui_scr->eq_modify_slider_7, eq_modify_slider_7_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui_scr->eq_modify_slider_8, eq_modify_slider_8_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui_scr->eq_modify_slider_9, eq_modify_slider_9_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui_scr->eq_modify_slider_10, eq_modify_slider_10_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui_scr->eq_modify_ddlist_1, eq_modify_ddlist_1_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui_scr->eq_modify_btn_1, eq_modify_btn_1_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui_scr->eq_modify, eq_modify_screen_event_handler, LV_EVENT_ALL, ui);
}
