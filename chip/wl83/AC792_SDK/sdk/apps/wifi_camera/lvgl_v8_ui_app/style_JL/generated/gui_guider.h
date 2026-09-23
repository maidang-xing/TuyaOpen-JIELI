#include "app_config.h"
#ifdef CONFIG_UI_STYLE_JL_ENABLE
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
#include "./i18n/lv_i18n.h"

#ifdef JL_GUI_KERNEL_VERSION_MAJOR
#if GUI_CORE_VERSION_MAJOR != JL_GUI_KERNEL_VERSION_MAJOR
#error "Current Kernel Version is not compatible, please replace or upgrade the kernel!"
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
    // Screen usb_slave
    lv_obj_t *usb_slave;
    bool      usb_slave_del;
    lv_obj_t *usb_slave_img_icon_pccam;
    lv_obj_t *usb_slave_img_icon_masstorage;
    lv_obj_t *usb_slave_view_btnlist;
    lv_obj_t *usb_slave_imgbtn_videorec;
    lv_obj_t *usb_slave_imgbtn_videorec_label;
    lv_obj_t *usb_slave_imgbtn_masstorage;
    lv_obj_t *usb_slave_imgbtn_masstorage_label;
    lv_obj_t *usb_slave_imgbtn_pccam;
    lv_obj_t *usb_slave_imgbtn_pccam_label;
} lv_ui_usb_slave;

typedef struct {
    // Screen video_rec
    lv_obj_t *video_rec;
    bool      video_rec_del;
    lv_obj_t *video_rec_imgbtn_1;
    lv_obj_t *video_rec_imgbtn_1_label;
    lv_obj_t *video_rec_digitclock_2;
    lv_obj_t *video_rec_img_4;
    lv_obj_t *video_rec_img_5;
    lv_obj_t *video_rec_img_6;
    lv_obj_t *video_rec_img_7;
    lv_obj_t *video_rec_img_8;
    lv_obj_t *video_rec_img_9;
    lv_obj_t *video_rec_img_lock_icon;
    lv_obj_t *video_rec_img_11;
    lv_obj_t *video_rec_img_app;
    lv_obj_t *video_rec_img_12;
    lv_obj_t *video_rec_lbl_2;
    lv_obj_t *video_rec_lbl_3;
    lv_obj_t *video_rec_lbl_4;
    lv_obj_t *video_rec_view_1;
    lv_obj_t *video_rec_img_video_set;
    lv_obj_t *video_rec_img_15;
    lv_obj_t *video_rec_img_home;
    lv_obj_t *video_rec_imgbtn_lock_set;
    lv_obj_t *video_rec_imgbtn_lock_set_label;
    lv_obj_t *video_rec_imgbtn_sw_window;
    lv_obj_t *video_rec_imgbtn_sw_window_label;
    lv_obj_t *video_rec_digitclock_remain_time;
    lv_obj_t *video_rec_digitclock_record_time;
    lv_obj_t *video_rec_view_video_set;
    lv_obj_t *video_rec_img_resolution;
    lv_obj_t *video_rec_img_19;
    lv_obj_t *video_rec_img_20;
    lv_obj_t *video_rec_img_21;
    lv_obj_t *video_rec_lbl_5;
    lv_obj_t *video_rec_lbl_6;
    lv_obj_t *video_rec_lbl_7;
    lv_obj_t *video_rec_lbl_8;
    lv_obj_t *video_rec_img_1;
    lv_obj_t *video_rec_img_10;
    lv_obj_t *video_rec_img_17;
    lv_obj_t *video_rec_img_18;
    lv_obj_t *video_rec_lbl_13;
    lv_obj_t *video_rec_lbl_14;
    lv_obj_t *video_rec_img_3;
    lv_obj_t *video_rec_img_22;
    lv_obj_t *video_rec_img_23;
    lv_obj_t *video_rec_img_24;
    lv_obj_t *video_rec_lbl_15;
    lv_obj_t *video_rec_lbl_16;
    lv_obj_t *video_rec_lbl_17;
    lv_obj_t *video_rec_lbl_18;
    lv_obj_t *video_rec_lbl_19;
    lv_obj_t *video_rec_lbl_20;
    lv_obj_t *video_rec_view_subpage;
    lv_obj_t *video_rec_img_16;
    lv_obj_t *video_rec_lbl_menu_title;
    lv_obj_t *video_rec_lbl_funkey1;
    lv_obj_t *video_rec_lbl_funkey1_label;
    lv_obj_t *video_rec_lbl_funkey2;
    lv_obj_t *video_rec_lbl_funkey2_label;
    lv_obj_t *video_rec_lbl_funkey3;
    lv_obj_t *video_rec_lbl_funkey3_label;
    lv_obj_t *video_rec_lbl_funkey4;
    lv_obj_t *video_rec_lbl_funkey4_label;
    lv_obj_t *video_rec_roller_mutifunc;
    lv_obj_t *video_rec_headlight;
    lv_timer_t *video_rec_timer_1;
} lv_ui_video_rec;

typedef struct {
    // Screen home_page
    lv_obj_t *home_page;
    bool      home_page_del;
    lv_obj_t *home_page_imgbtn_1;
    lv_obj_t *home_page_imgbtn_1_label;
    lv_obj_t *home_page_imgbtn_2;
    lv_obj_t *home_page_imgbtn_2_label;
    lv_obj_t *home_page_imgbtn_3;
    lv_obj_t *home_page_imgbtn_3_label;
    lv_obj_t *home_page_img_1;
    lv_obj_t *home_page_digitclock_1;
    lv_obj_t *home_page_lbl_3;
    lv_obj_t *home_page_lbl_1;
} lv_ui_home_page;

typedef struct {
    // Screen sys_prompt
    lv_obj_t *sys_prompt;
    bool      sys_prompt_del;
    lv_obj_t *sys_prompt_img_warn;
    lv_obj_t *sys_prompt_lbl_warn;
    lv_obj_t *sys_prompt_img_2;
    lv_obj_t *sys_prompt_img_1;
    lv_obj_t *sys_prompt_lbl_1;
} lv_ui_sys_prompt;

typedef struct {
    // Screen sys_setting
    lv_obj_t *sys_setting;
    bool      sys_setting_del;
    lv_obj_t *sys_setting_view_menupage;
    lv_obj_t *sys_setting_img_saver;
    lv_obj_t *sys_setting_img_2;
    lv_obj_t *sys_setting_img_3;
    lv_obj_t *sys_setting_img_4;
    lv_obj_t *sys_setting_lbl_1;
    lv_obj_t *sys_setting_lbl_2;
    lv_obj_t *sys_setting_lbl_3;
    lv_obj_t *sys_setting_lbl_4;
    lv_obj_t *sys_setting_img_5;
    lv_obj_t *sys_setting_img_7;
    lv_obj_t *sys_setting_img_9;
    lv_obj_t *sys_setting_img_8;
    lv_obj_t *sys_setting_lbl_5;
    lv_obj_t *sys_setting_lbl_6;
    lv_obj_t *sys_setting_img_6;
    lv_obj_t *sys_setting_img_10;
    lv_obj_t *sys_setting_img_11;
    lv_obj_t *sys_setting_img_12;
    lv_obj_t *sys_setting_lbl_7;
    lv_obj_t *sys_setting_lbl_8;
    lv_obj_t *sys_setting_lbl_9;
    lv_obj_t *sys_setting_lbl_10;
    lv_obj_t *sys_setting_lbl_11;
    lv_obj_t *sys_setting_lbl_12;
    lv_obj_t *sys_setting_view_subpage;
    lv_obj_t *sys_setting_img_icon;
    lv_obj_t *sys_setting_lbl_menu_title;
    lv_obj_t *sys_setting_view_3;
    lv_obj_t *sys_setting_img_15;
    lv_obj_t *sys_setting_img_14;
    lv_obj_t *sys_setting_img_16;
    lv_obj_t *sys_setting_view_list;
    lv_obj_t *sys_setting_lbl_funkey4;
    lv_obj_t *sys_setting_lbl_funkey5;
    lv_obj_t *sys_setting_lbl_funkey6;
    lv_obj_t *sys_setting_lbl_funkey7;
    lv_obj_t *sys_setting_lbl_subpage_warning;
    lv_obj_t *sys_setting_view_date;
    lv_obj_t *sys_setting_roller_hour;
    lv_obj_t *sys_setting_roller_min;
    lv_obj_t *sys_setting_datetext_subpage;
    lv_obj_t *sys_setting_view_carmun;
    lv_obj_t *sys_setting_ddlist_1;
    lv_obj_t *sys_setting_ddlist_2;
    lv_obj_t *sys_setting_ddlist_3;
    lv_obj_t *sys_setting_ddlist_4;
    lv_obj_t *sys_setting_ddlist_5;
    lv_obj_t *sys_setting_ddlist_6;
    lv_obj_t *sys_setting_ddlist_7;
    lv_obj_t *sys_setting_lbl_funkey1;
    lv_obj_t *sys_setting_lbl_funkey1_label;
    lv_obj_t *sys_setting_lbl_funkey2;
    lv_obj_t *sys_setting_lbl_funkey2_label;
    lv_obj_t *sys_setting_lbl_funkey3;
    lv_obj_t *sys_setting_lbl_funkey3_label;
} lv_ui_sys_setting;

typedef struct {
    // Screen video_photo
    lv_obj_t *video_photo;
    bool      video_photo_del;
    lv_obj_t *video_photo_digitclock_1;
    lv_obj_t *video_photo_imgbtn_2;
    lv_obj_t *video_photo_imgbtn_2_label;
    lv_obj_t *video_photo_imgbtn_1;
    lv_obj_t *video_photo_imgbtn_1_label;
    lv_obj_t *video_photo_img_5;
    lv_obj_t *video_photo_img_7;
    lv_obj_t *video_photo_img_8;
    lv_obj_t *video_photo_img_9;
    lv_obj_t *video_photo_img_12;
    lv_obj_t *video_photo_lbl_2;
    lv_obj_t *video_photo_lbl_3;
    lv_obj_t *video_photo_lbl_4;
    lv_obj_t *video_photo_view_1;
    lv_obj_t *video_photo_img_video_set;
    lv_obj_t *video_photo_img_15;
    lv_obj_t *video_photo_img_home;
    lv_obj_t *video_photo_view_video_set;
    lv_obj_t *video_photo_img_resolution;
    lv_obj_t *video_photo_img_19;
    lv_obj_t *video_photo_img_20;
    lv_obj_t *video_photo_img_21;
    lv_obj_t *video_photo_lbl_5;
    lv_obj_t *video_photo_lbl_6;
    lv_obj_t *video_photo_lbl_7;
    lv_obj_t *video_photo_lbl_8;
    lv_obj_t *video_photo_img_1;
    lv_obj_t *video_photo_img_10;
    lv_obj_t *video_photo_img_17;
    lv_obj_t *video_photo_img_18;
    lv_obj_t *video_photo_lbl_13;
    lv_obj_t *video_photo_lbl_14;
    lv_obj_t *video_photo_img_3;
    lv_obj_t *video_photo_img_22;
    lv_obj_t *video_photo_img_23;
    lv_obj_t *video_photo_img_24;
    lv_obj_t *video_photo_lbl_15;
    lv_obj_t *video_photo_lbl_16;
    lv_obj_t *video_photo_lbl_17;
    lv_obj_t *video_photo_lbl_18;
    lv_obj_t *video_photo_lbl_19;
    lv_obj_t *video_photo_lbl_20;
    lv_obj_t *video_photo_img_25;
    lv_obj_t *video_photo_img_4;
    lv_obj_t *video_photo_view_subpage;
    lv_obj_t *video_photo_img_16;
    lv_obj_t *video_photo_lbl_menu_title;
    lv_obj_t *video_photo_roller_mutifunc;
    lv_obj_t *video_photo_lbl_funkey1;
    lv_obj_t *video_photo_lbl_funkey1_label;
    lv_obj_t *video_photo_lbl_funkey2;
    lv_obj_t *video_photo_lbl_funkey2_label;
    lv_obj_t *video_photo_lbl_funkey3;
    lv_obj_t *video_photo_lbl_funkey3_label;
    lv_obj_t *video_photo_lbl_funkey4;
    lv_obj_t *video_photo_lbl_funkey4_label;
    lv_obj_t *video_photo_show_capture_time;
} lv_ui_video_photo;

typedef struct {
    // Screen video_play
    lv_obj_t *video_play;
    bool      video_play_del;
    lv_obj_t *video_play_view_1;
    lv_obj_t *video_play_lbl_cur_time;
    lv_obj_t *video_play_imgbtn_pause;
    lv_obj_t *video_play_imgbtn_pause_label;
    lv_obj_t *video_play_imgbtn_loud;
    lv_obj_t *video_play_imgbtn_loud_label;
    lv_obj_t *video_play_lbl_total_time;
    lv_obj_t *video_play_ddlist_multi_spped;
    lv_obj_t *video_play_bar_process;
    lv_obj_t *video_play_imgbtn_1;
    lv_obj_t *video_play_imgbtn_1_label;
    lv_obj_t *video_play_imgbtn_2;
    lv_obj_t *video_play_imgbtn_2_label;
    lv_obj_t *video_play_lbl_msg;
    lv_timer_t *video_play_hide_bar;
    lv_obj_t *video_play_img_prev_file;
    lv_obj_t *video_play_img_next_file;
    lv_timer_t *video_play_hide_label;
} lv_ui_video_play;

typedef struct {
    // Screen video_file
    lv_obj_t *video_file;
    bool      video_file_del;
    lv_obj_t *video_file_view_1;
    lv_obj_t *video_file_imgbtn_4;
    lv_obj_t *video_file_imgbtn_4_label;
    lv_obj_t *video_file_img_1;
    lv_obj_t *video_file_img_2;
    lv_obj_t *video_file_view_8;
    lv_obj_t *video_file_imgbtn_3;
    lv_obj_t *video_file_imgbtn_3_label;
    lv_obj_t *video_file_imgbtn_1;
    lv_obj_t *video_file_imgbtn_1_label;
    lv_obj_t *video_file_imgbtn_5;
    lv_obj_t *video_file_imgbtn_5_label;
    lv_obj_t *video_file_imgbtn_2;
    lv_obj_t *video_file_imgbtn_2_label;
    lv_obj_t *video_file_lbl_path;
    lv_obj_t *video_file_view_3;
    lv_obj_t *video_file_lbl_1;
} lv_ui_video_file;

typedef struct {
    // Screen video_dir
    lv_obj_t *video_dir;
    bool      video_dir_del;
    lv_obj_t *video_dir_view_7;
    lv_obj_t *video_dir_imgbtn_4;
    lv_obj_t *video_dir_imgbtn_4_label;
    lv_obj_t *video_dir_img_17;
    lv_obj_t *video_dir_lbl_path;
    lv_obj_t *video_dir_view_8;
    lv_obj_t *video_dir_imgbtn_1;
    lv_obj_t *video_dir_imgbtn_1_label;
    lv_obj_t *video_dir_imgbtn_3;
    lv_obj_t *video_dir_imgbtn_3_label;
    lv_obj_t *video_dir_imgbtn_5;
    lv_obj_t *video_dir_imgbtn_5_label;
    lv_obj_t *video_dir_imgbtn_2;
    lv_obj_t *video_dir_imgbtn_2_label;
} lv_ui_video_dir;

typedef struct {
    // Screen car_parking
    lv_obj_t *car_parking;
    bool      car_parking_del;
    lv_obj_t *car_parking_img_1;
} lv_ui_car_parking;

typedef struct {
    // Screen line_drift
    lv_obj_t *line_drift;
    bool      line_drift_del;
    lv_obj_t *line_drift_lbl_3;
    lv_obj_t *line_drift_view_2;
    lv_obj_t *line_drift_btn_horizon;
    lv_obj_t *line_drift_btn_horizon_label;
    lv_obj_t *line_drift_btn_carhead;
    lv_obj_t *line_drift_btn_carhead_label;
    lv_obj_t *line_drift_lbl_7;
    lv_obj_t *line_drift_lbl_6;
} lv_ui_line_drift;

typedef struct {
    // Screen sys_popwin
    lv_obj_t *sys_popwin;
    bool      sys_popwin_del;
    lv_obj_t *sys_popwin_view_1;
    lv_obj_t *sys_popwin_lbl_1;
    lv_obj_t *sys_popwin_btn_1;
    lv_obj_t *sys_popwin_btn_1_label;
    lv_obj_t *sys_popwin_btn_2;
    lv_obj_t *sys_popwin_btn_2_label;
} lv_ui_sys_popwin;

// generate lv_ui gui_guider
typedef struct {
    lv_ui_usb_slave *usb_slave;
    lv_ui_video_rec *video_rec;
    lv_ui_home_page *home_page;
    lv_ui_sys_prompt *sys_prompt;
    lv_ui_sys_setting *sys_setting;
    lv_ui_video_photo *video_photo;
    lv_ui_video_play *video_play;
    lv_ui_video_file *video_file;
    lv_ui_video_dir *video_dir;
    lv_ui_car_parking *car_parking;
    lv_ui_line_drift *line_drift;
    lv_ui_sys_popwin *sys_popwin;

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
extern lv_ui guider_ui;// Screen usb_slave
lv_obj_t *setup_scr_usb_slave(lv_ui *ui);
void unload_scr_usb_slave(lv_ui *ui);
// Screen video_rec
lv_obj_t *setup_scr_video_rec(lv_ui *ui);
void unload_scr_video_rec(lv_ui *ui);
/*DigitalClock*/
void clock_count_with_year(int *year, int *month, int *day, int *hour, int *min, int *sec);
// Screen home_page
lv_obj_t *setup_scr_home_page(lv_ui *ui);
void unload_scr_home_page(lv_ui *ui);
// Screen sys_prompt
lv_obj_t *setup_scr_sys_prompt(lv_ui *ui);
void unload_scr_sys_prompt(lv_ui *ui);
// Screen sys_setting
lv_obj_t *setup_scr_sys_setting(lv_ui *ui);
void unload_scr_sys_setting(lv_ui *ui);
// Screen video_photo
lv_obj_t *setup_scr_video_photo(lv_ui *ui);
void unload_scr_video_photo(lv_ui *ui);
// Screen video_play
lv_obj_t *setup_scr_video_play(lv_ui *ui);
void unload_scr_video_play(lv_ui *ui);
// Screen video_file
lv_obj_t *setup_scr_video_file(lv_ui *ui);
void unload_scr_video_file(lv_ui *ui);
// Screen video_dir
lv_obj_t *setup_scr_video_dir(lv_ui *ui);
void unload_scr_video_dir(lv_ui *ui);
// Screen car_parking
lv_obj_t *setup_scr_car_parking(lv_ui *ui);
void unload_scr_car_parking(lv_ui *ui);
// Screen line_drift
lv_obj_t *setup_scr_line_drift(lv_ui *ui);
void unload_scr_line_drift(lv_ui *ui);
// Screen sys_popwin
lv_obj_t *setup_scr_sys_popwin(lv_ui *ui);
void unload_scr_sys_popwin(lv_ui *ui);
#ifdef __cplusplus
}
#endif
#endif

#endif
