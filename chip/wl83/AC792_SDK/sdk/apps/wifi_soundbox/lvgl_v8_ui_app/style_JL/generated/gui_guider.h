/*Generate Code, Do NOT Edit!*/
#ifndef GUI_GUIDER_H
#define GUI_GUIDER_H
#ifdef __cplusplus
extern "C" {
#endif

#include "lvgl.h"
#include "./common.h"
#include "./gui_fonts/gui_fonts.h"
#include "./gui_images/gui_images.h"
#include "./gui_scr/ui_scr_manager.h"
#include "./gui_scr/ui_style.h"

#ifdef JL_GUI_KERNEL_VERSION_MAJOR
#if GUI_CORE_VERSION_MAJOR > JL_GUI_KERNEL_VERSION_MAJOR
#error "Current SDK Version is older than the kernel version. Please update the SDK version!"
#endif
#if GUI_CORE_VERSION_MAJOR < JL_GUI_KERNEL_VERSION_MAJOR
#error "Current SDK Version is newer than the kernel version. Please update the kernel version!"
#endif
#if GUI_CORE_VERSION_MINOR > JL_GUI_KERNEL_VERSION_MINOR
#warning "Current Kernel Version is too low, some features may not be available, please update the kernel version!"
#endif
#else
#error "Current Kernel Version is not defined, please replace or upgrade the kernel!"
#endif

#ifndef LV_USE_GUIBUILDER_SIMULATOR
#if defined(COMPATIBLE_UI_PRJ_TEMPLATE_VERSION_MIN_MAJOR) && defined(COMPATIBLE_UI_PRJ_TEMPLATE_VERSION_MAX_MAJOR)
#if GUI_TEMPLATE_VERSION_MAJOR < COMPATIBLE_UI_PRJ_TEMPLATE_VERSION_MIN_MAJOR || GUI_TEMPLATE_VERSION_MAJOR > COMPATIBLE_UI_PRJ_TEMPLATE_VERSION_MAX_MAJOR
#error "Current Project Template Version is not compatible with the SDK version. Please select a compatible SDK version!"
#endif
#if GUI_TEMPLATE_VERSION_MINOR < COMPATIBLE_UI_PRJ_TEMPLATE_VERSION_MIN_MINOR || GUI_TEMPLATE_VERSION_MINOR > COMPATIBLE_UI_PRJ_TEMPLATE_VERSION_MAX_MINOR
#warning "Current Project Template Version has minor incompatibilities with the SDK. Some features may not be available. Consider updating the SDK version."
#endif
#endif
#endif

typedef struct {
    // Screen music_player
    lv_obj_t *music_player;
    bool      music_player_del;
    lv_obj_t *music_player_imgbtn_1;
    lv_obj_t *music_player_imgbtn_1_label;
    lv_obj_t *music_player_imgbtn_2;
    lv_obj_t *music_player_imgbtn_2_label;
    lv_obj_t *music_player_imgbtn_3;
    lv_obj_t *music_player_imgbtn_3_label;
    lv_obj_t *music_player_slider_1;
    lv_obj_t *music_player_img_2;
    lv_obj_t *music_player_lbl_2;
    lv_obj_t *music_player_lbl_3;
    lv_timer_t *music_player_timer_1;
    lv_obj_t *music_player_view_lyrics;
    lv_obj_t *music_player_view_1;
    lv_obj_t *music_player_img_1;
} lv_ui_music_player;

typedef struct {
    // Screen sys_menu
    lv_obj_t *sys_menu;
    bool      sys_menu_del;
    lv_obj_t *sys_menu_view_1;
    lv_obj_t *sys_menu_img_1;
    lv_obj_t *sys_menu_lbl_1;
    lv_obj_t *sys_menu_view_2;
    lv_obj_t *sys_menu_img_2;
    lv_obj_t *sys_menu_lbl_2;
    lv_obj_t *sys_menu_view_3;
    lv_obj_t *sys_menu_img_3;
    lv_obj_t *sys_menu_lbl_3;
    lv_obj_t *sys_menu_view_4;
    lv_obj_t *sys_menu_img_4;
    lv_obj_t *sys_menu_lbl_4;
    lv_obj_t *sys_menu_view_5;
    lv_obj_t *sys_menu_img_5;
    lv_obj_t *sys_menu_lbl_5;
    lv_obj_t *sys_menu_slider_2;
    lv_obj_t *sys_menu_slider_1;
    lv_obj_t *sys_menu_img_6;
    lv_obj_t *sys_menu_img_7;
    lv_obj_t *sys_menu_view_6;
    lv_obj_t *sys_menu_lbl_6;
    lv_obj_t *sys_menu_lbl_8;
    lv_obj_t *sys_menu_imgbtn_4;
    lv_obj_t *sys_menu_imgbtn_4_label;
    lv_obj_t *sys_menu_imgbtn_5;
    lv_obj_t *sys_menu_imgbtn_5_label;
    lv_obj_t *sys_menu_imgbtn_6;
    lv_obj_t *sys_menu_imgbtn_6_label;
    lv_obj_t *sys_menu_img_8;
    lv_obj_t *sys_menu_view_song_info;
} lv_ui_sys_menu;

typedef struct {
    // Screen eq_modify
    lv_obj_t *eq_modify;
    bool      eq_modify_del;
    lv_obj_t *eq_modify_slider_1;
    lv_obj_t *eq_modify_slider_2;
    lv_obj_t *eq_modify_slider_3;
    lv_obj_t *eq_modify_slider_4;
    lv_obj_t *eq_modify_slider_5;
    lv_obj_t *eq_modify_slider_6;
    lv_obj_t *eq_modify_slider_7;
    lv_obj_t *eq_modify_slider_8;
    lv_obj_t *eq_modify_slider_9;
    lv_obj_t *eq_modify_slider_10;
    lv_obj_t *eq_modify_lbl_1;
    lv_obj_t *eq_modify_lbl_2;
    lv_obj_t *eq_modify_lbl_3;
    lv_obj_t *eq_modify_lbl_4;
    lv_obj_t *eq_modify_lbl_5;
    lv_obj_t *eq_modify_lbl_6;
    lv_obj_t *eq_modify_lbl_7;
    lv_obj_t *eq_modify_lbl_8;
    lv_obj_t *eq_modify_lbl_9;
    lv_obj_t *eq_modify_lbl_10;
    lv_obj_t *eq_modify_lbl_11;
    lv_obj_t *eq_modify_lbl_12;
    lv_obj_t *eq_modify_lbl_13;
    lv_obj_t *eq_modify_lbl_14;
    lv_obj_t *eq_modify_sw_1;
    lv_obj_t *eq_modify_lbl_15;
    lv_obj_t *eq_modify_ddlist_1;
    lv_obj_t *eq_modify_btn_1;
    lv_obj_t *eq_modify_btn_1_label;
} lv_ui_eq_modify;

// generate lv_ui gui_guider
typedef struct {
    lv_ui_music_player *music_player;
    lv_ui_sys_menu *sys_menu;
    lv_ui_eq_modify *eq_modify;

    lv_group_t *default_group;
} lv_ui;

void ui_load_scr_anim(lv_ui *ui, gui_scr_t *screen, lv_scr_load_anim_t anim_type,	uint32_t time,
                      uint32_t delay, bool is_clean, bool auto_del, bool is_push_satck);

void ui_scr_stack_pop_anim(lv_ui *ui, lv_scr_load_anim_t anim_type, uint32_t time, uint32_t delay,
                           bool is_clean, bool auto_del, bool is_push_satck);

gui_scr_t *ui_get_scr(int32_t scr_id);
gui_scr_t *ui_get_setup_scr(int32_t scr_id);
lv_obj_t *ui_get_setup_scr_obj(int32_t scr_id);
void *ui_get_scr_ptr(lv_ui *ui, int32_t scr_id);
void ui_free_scr_ptr(lv_ui *ui, int32_t scr_id);
bool ui_is_act_scr(int32_t scr_id);
void ui_init_style(lv_style_t *style);
void setup_ui(lv_ui *ui);
#include "./gui_msg/gui_msg.h"
extern lv_ui guider_ui;// Screen music_player
lv_obj_t *setup_scr_music_player(lv_ui *ui);
void unload_scr_music_player(lv_ui *ui);
// Screen sys_menu
lv_obj_t *setup_scr_sys_menu(lv_ui *ui);
void unload_scr_sys_menu(lv_ui *ui);
// Screen eq_modify
lv_obj_t *setup_scr_eq_modify(lv_ui *ui);
void unload_scr_eq_modify(lv_ui *ui);
#ifdef __cplusplus
}
#endif
#endif
