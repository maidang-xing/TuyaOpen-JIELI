#include "app_config.h"
#ifdef CONFIG_UI_STYLE_LY_ENABLE
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
    // Screen usb_slave
    lv_obj_t *usb_slave;
    bool      usb_slave_del;
    lv_obj_t *usb_slave_img_icon_pccam;
    lv_obj_t *usb_slave_img_icon_masstorage;
    lv_obj_t *usb_slave_view_btnlist;
    lv_obj_t *usb_slave_btn_usb_msd;
    lv_obj_t *usb_slave_btn_usb_msd_label;
    lv_obj_t *usb_slave_btn_pc_cam;
    lv_obj_t *usb_slave_btn_pc_cam_label;
    lv_obj_t *usb_slave_btn_video_rec;
    lv_obj_t *usb_slave_btn_video_rec_label;
    lv_obj_t *usb_slave_btn_1;
    lv_obj_t *usb_slave_btn_1_label;
} lv_ui_usb_slave;

typedef struct {
    // Screen video_rec
    lv_obj_t *video_rec;
    bool      video_rec_del;
    lv_obj_t *video_rec_view_scan;
    lv_obj_t *video_rec_img_1;
    lv_obj_t *video_rec_img_cyc_state;
    lv_obj_t *video_rec_img_exp_state;
    lv_obj_t *video_rec_img_mot_state;
    lv_obj_t *video_rec_img_gap_state;
    lv_obj_t *video_rec_img_mic_state;
    lv_obj_t *video_rec_img_hdr_state;
    lv_obj_t *video_rec_img_gra_state;
    lv_obj_t *video_rec_img_par_state;
    lv_obj_t *video_rec_lbl_reso;
    lv_obj_t *video_rec_digitclock_1;
    lv_obj_t *video_rec_img_bat;
    lv_obj_t *video_rec_img_sd;
    lv_obj_t *video_rec_digitclock_2;
    lv_obj_t *video_rec_img_rec_state;
    lv_obj_t *video_rec_lbl_num;
    lv_obj_t *video_rec_img_headlight;
    lv_obj_t *video_rec_img_key_state;
    lv_timer_t *video_rec_timer_1;
    lv_obj_t *video_rec_view_menu_b;
    lv_obj_t *video_rec_view_menu;
    lv_obj_t *video_rec_view_reso;
    lv_obj_t *video_rec_img_2;
    lv_obj_t *video_rec_lbl_1;
    lv_obj_t *video_rec_view_two_rec;
    lv_obj_t *video_rec_img_3;
    lv_obj_t *video_rec_lbl_3;
    lv_obj_t *video_rec_view_cyc_rec;
    lv_obj_t *video_rec_img_4;
    lv_obj_t *video_rec_lbl_4;
    lv_obj_t *video_rec_view_gap;
    lv_obj_t *video_rec_img_5;
    lv_obj_t *video_rec_lbl_5;
    lv_obj_t *video_rec_view_hdr;
    lv_obj_t *video_rec_img_6;
    lv_obj_t *video_rec_lbl_6;
    lv_obj_t *video_rec_view_exp;
    lv_obj_t *video_rec_img_7;
    lv_obj_t *video_rec_lbl_7;
    lv_obj_t *video_rec_view_motd;
    lv_obj_t *video_rec_img_8;
    lv_obj_t *video_rec_lbl_8;
    lv_obj_t *video_rec_view_mic;
    lv_obj_t *video_rec_img_9;
    lv_obj_t *video_rec_lbl_9;
    lv_obj_t *video_rec_view_date;
    lv_obj_t *video_rec_img_10;
    lv_obj_t *video_rec_lbl_10;
    lv_obj_t *video_rec_view_gra;
    lv_obj_t *video_rec_img_11;
    lv_obj_t *video_rec_lbl_11;
    lv_obj_t *video_rec_view_par;
    lv_obj_t *video_rec_img_12;
    lv_obj_t *video_rec_lbl_12;
    lv_obj_t *video_rec_view_num;
    lv_obj_t *video_rec_img_13;
    lv_obj_t *video_rec_lbl_13;
    lv_obj_t *video_rec_view_hlw;
    lv_obj_t *video_rec_img_14;
    lv_obj_t *video_rec_lbl_14;
    lv_obj_t *video_rec_img_15;
    lv_obj_t *video_rec_img_16;
    lv_obj_t *video_rec_img_17;
    lv_obj_t *video_rec_img_18;
    lv_obj_t *video_rec_img_19;
    lv_obj_t *video_rec_img_20;
    lv_obj_t *video_rec_img_21;
    lv_obj_t *video_rec_img_22;
    lv_obj_t *video_rec_view_submenu;
    lv_obj_t *video_rec_rec_submenu_btn_1;
    lv_obj_t *video_rec_rec_submenu_btn_1_label;
    lv_obj_t *video_rec_rec_submenu_btn_2;
    lv_obj_t *video_rec_rec_submenu_btn_2_label;
    lv_obj_t *video_rec_rec_submenu_btn_3;
    lv_obj_t *video_rec_rec_submenu_btn_3_label;
    lv_obj_t *video_rec_rec_submenu_btn_4;
    lv_obj_t *video_rec_rec_submenu_btn_4_label;
    lv_obj_t *video_rec_roller_mutifunc;
    lv_obj_t *video_rec_view_carnum;
    lv_obj_t *video_rec_ddlist_1;
    lv_obj_t *video_rec_ddlist_2;
    lv_obj_t *video_rec_ddlist_3;
    lv_obj_t *video_rec_ddlist_4;
    lv_obj_t *video_rec_ddlist_5;
    lv_obj_t *video_rec_ddlist_6;
    lv_obj_t *video_rec_ddlist_7;
} lv_ui_video_rec;

typedef struct {
    // Screen sys_prompt
    lv_obj_t *sys_prompt;
    bool      sys_prompt_del;
    lv_obj_t *sys_prompt_img_warn;
    lv_obj_t *sys_prompt_lbl_warn;
    lv_obj_t *sys_prompt_img_2;
    lv_obj_t *sys_prompt_lbl_1;
} lv_ui_sys_prompt;

typedef struct {
    // Screen sys_setting
    lv_obj_t *sys_setting;
    bool      sys_setting_del;
    lv_obj_t *sys_setting_view_menu_b;
    lv_obj_t *sys_setting_view_menu;
    lv_obj_t *sys_setting_view_pro;
    lv_obj_t *sys_setting_img_1;
    lv_obj_t *sys_setting_lbl_1;
    lv_obj_t *sys_setting_view_autof;
    lv_obj_t *sys_setting_img_2;
    lv_obj_t *sys_setting_lbl_2;
    lv_obj_t *sys_setting_view_hz;
    lv_obj_t *sys_setting_img_3;
    lv_obj_t *sys_setting_lbl_3;
    lv_obj_t *sys_setting_view_kvo;
    lv_obj_t *sys_setting_img_4;
    lv_obj_t *sys_setting_lbl_4;
    lv_obj_t *sys_setting_view_lag;
    lv_obj_t *sys_setting_img_5;
    lv_obj_t *sys_setting_lbl_5;
    lv_obj_t *sys_setting_view_time;
    lv_obj_t *sys_setting_img_6;
    lv_obj_t *sys_setting_lbl_6;
    lv_obj_t *sys_setting_view_tv;
    lv_obj_t *sys_setting_img_7;
    lv_obj_t *sys_setting_lbl_7;
    lv_obj_t *sys_setting_view_format;
    lv_obj_t *sys_setting_img_8;
    lv_obj_t *sys_setting_lbl_8;
    lv_obj_t *sys_setting_view_reset;
    lv_obj_t *sys_setting_img_9;
    lv_obj_t *sys_setting_lbl_9;
    lv_obj_t *sys_setting_view_ver;
    lv_obj_t *sys_setting_img_10;
    lv_obj_t *sys_setting_lbl_10;
    lv_obj_t *sys_setting_img_11;
    lv_obj_t *sys_setting_img_12;
    lv_obj_t *sys_setting_img_13;
    lv_obj_t *sys_setting_img_14;
    lv_obj_t *sys_setting_img_15;
    lv_obj_t *sys_setting_img_16;
    lv_obj_t *sys_setting_img_17;
    lv_obj_t *sys_setting_img_18;
    lv_obj_t *sys_setting_view_submenu;
    lv_obj_t *sys_setting_submenu_btn_1;
    lv_obj_t *sys_setting_submenu_btn_1_label;
    lv_obj_t *sys_setting_submenu_btn_2;
    lv_obj_t *sys_setting_submenu_btn_2_label;
    lv_obj_t *sys_setting_submenu_btn_3;
    lv_obj_t *sys_setting_submenu_btn_3_label;
    lv_obj_t *sys_setting_submenu_btn_4;
    lv_obj_t *sys_setting_submenu_btn_4_label;
    lv_obj_t *sys_setting_roller_mutifunc;
    lv_obj_t *sys_setting_lbl_submenu_warning;
    lv_obj_t *sys_setting_view_time_mun;
    lv_obj_t *sys_setting_ddlist_year;
    lv_obj_t *sys_setting_ddlist_month;
    lv_obj_t *sys_setting_ddlist_day;
    lv_obj_t *sys_setting_ddlist_hour;
    lv_obj_t *sys_setting_ddlist_min;
    lv_obj_t *sys_setting_ddlist_sec;
    lv_obj_t *sys_setting_img_19;
    lv_obj_t *sys_setting_img_20;
    lv_obj_t *sys_setting_img_21;
    lv_obj_t *sys_setting_img_22;
} lv_ui_sys_setting;

typedef struct {
    // Screen video_photo
    lv_obj_t *video_photo;
    bool      video_photo_del;
    lv_obj_t *video_photo_view_scan;
    lv_obj_t *video_photo_img_taking_photo;
    lv_obj_t *video_photo_img_photo_icon;
    lv_obj_t *video_photo_img_exp_icon;
    lv_obj_t *video_photo_img_awb_icon;
    lv_obj_t *video_photo_img_iso_icon;
    lv_obj_t *video_photo_img_qua_icon;
    lv_obj_t *video_photo_img_delay_icon;
    lv_obj_t *video_photo_img_shake_icon;
    lv_obj_t *video_photo_img_repeat_icon;
    lv_obj_t *video_photo_img_sd_icon;
    lv_obj_t *video_photo_img_bat_icon;
    lv_obj_t *video_photo_lbl_photo_reso;
    lv_obj_t *video_photo_lbl_remain_pnum;
    lv_obj_t *video_photo_digitclock_1;
    lv_obj_t *video_photo_view_menu_b;
    lv_obj_t *video_photo_view_menu;
    lv_obj_t *video_photo_view_phm;
    lv_obj_t *video_photo_img_1;
    lv_obj_t *video_photo_lbl_1;
    lv_obj_t *video_photo_view_reso;
    lv_obj_t *video_photo_img_2;
    lv_obj_t *video_photo_lbl_2;
    lv_obj_t *video_photo_view_cyt;
    lv_obj_t *video_photo_img_3;
    lv_obj_t *video_photo_lbl_3;
    lv_obj_t *video_photo_view_qua;
    lv_obj_t *video_photo_img_4;
    lv_obj_t *video_photo_lbl_4;
    lv_obj_t *video_photo_view_acu;
    lv_obj_t *video_photo_img_5;
    lv_obj_t *video_photo_lbl_5;
    lv_obj_t *video_photo_view_wbl;
    lv_obj_t *video_photo_img_6;
    lv_obj_t *video_photo_lbl_6;
    lv_obj_t *video_photo_view_col;
    lv_obj_t *video_photo_img_7;
    lv_obj_t *video_photo_lbl_7;
    lv_obj_t *video_photo_view_iso;
    lv_obj_t *video_photo_img_8;
    lv_obj_t *video_photo_lbl_8;
    lv_obj_t *video_photo_view_pexp;
    lv_obj_t *video_photo_img_9;
    lv_obj_t *video_photo_lbl_9;
    lv_obj_t *video_photo_view_sok;
    lv_obj_t *video_photo_img_10;
    lv_obj_t *video_photo_lbl_10;
    lv_obj_t *video_photo_view_sca;
    lv_obj_t *video_photo_img_11;
    lv_obj_t *video_photo_lbl_11;
    lv_obj_t *video_photo_view_pdat;
    lv_obj_t *video_photo_img_12;
    lv_obj_t *video_photo_lbl_12;
    lv_obj_t *video_photo_img_14;
    lv_obj_t *video_photo_img_15;
    lv_obj_t *video_photo_img_16;
    lv_obj_t *video_photo_img_17;
    lv_obj_t *video_photo_img_18;
    lv_obj_t *video_photo_img_19;
    lv_obj_t *video_photo_img_20;
    lv_obj_t *video_photo_img_21;
    lv_obj_t *video_photo_view_submenu;
    lv_obj_t *video_photo_submenu_btn_1;
    lv_obj_t *video_photo_submenu_btn_1_label;
    lv_obj_t *video_photo_submenu_btn_2;
    lv_obj_t *video_photo_submenu_btn_2_label;
    lv_obj_t *video_photo_submenu_btn_3;
    lv_obj_t *video_photo_submenu_btn_3_label;
    lv_obj_t *video_photo_submenu_btn_4;
    lv_obj_t *video_photo_submenu_btn_4_label;
    lv_obj_t *video_photo_roller_mutifunc;
} lv_ui_video_photo;

typedef struct {
    // Screen video_play
    lv_obj_t *video_play;
    bool      video_play_del;
    lv_obj_t *video_play_view_1;
    lv_obj_t *video_play_lbl_cur_time;
    lv_obj_t *video_play_imgbtn_pause;
    lv_obj_t *video_play_imgbtn_pause_label;
    lv_obj_t *video_play_img_prev_file;
    lv_obj_t *video_play_img_next_file;
    lv_obj_t *video_play_imgbtn_loud;
    lv_obj_t *video_play_imgbtn_loud_label;
    lv_obj_t *video_play_lbl_total_time;
    lv_obj_t *video_play_ddlist_multi_spped;
    lv_obj_t *video_play_bar_process;
    lv_obj_t *video_play_imgbtn_1;
    lv_obj_t *video_play_imgbtn_1_label;
    lv_obj_t *video_play_lbl_msg;
} lv_ui_video_play;

typedef struct {
    // Screen video_file
    lv_obj_t *video_file;
    bool      video_file_del;
    lv_obj_t *video_file_view_1;
    lv_obj_t *video_file_img_1;
    lv_obj_t *video_file_img_2;
    lv_obj_t *video_file_view_8;
    lv_obj_t *video_file_lbl_path;
    lv_obj_t *video_file_view_3;
    lv_obj_t *video_file_lbl_1;
    lv_obj_t *video_file_view_menu_b;
    lv_obj_t *video_file_view_menu;
    lv_obj_t *video_file_view_del;
    lv_obj_t *video_file_img_3;
    lv_obj_t *video_file_lbl_2;
    lv_obj_t *video_file_view_pro;
    lv_obj_t *video_file_img_4;
    lv_obj_t *video_file_lbl_3;
    lv_obj_t *video_file_img_13;
    lv_obj_t *video_file_img_14;
    lv_obj_t *video_file_img_15;
    lv_obj_t *video_file_img_16;
    lv_obj_t *video_file_img_17;
    lv_obj_t *video_file_img_18;
    lv_obj_t *video_file_img_19;
    lv_obj_t *video_file_img_20;
    lv_obj_t *video_file_view_submenu;
    lv_obj_t *video_file_submenu_btn_1;
    lv_obj_t *video_file_submenu_btn_1_label;
    lv_obj_t *video_file_submenu_btn_2;
    lv_obj_t *video_file_submenu_btn_2_label;
    lv_obj_t *video_file_submenu_btn_3;
    lv_obj_t *video_file_submenu_btn_3_label;
    lv_obj_t *video_file_submenu_btn_4;
    lv_obj_t *video_file_submenu_btn_4_label;
    lv_obj_t *video_file_lbl_submenu_warning;
} lv_ui_video_file;

typedef struct {
    // Screen video_dir
    lv_obj_t *video_dir;
    bool      video_dir_del;
    lv_obj_t *video_dir_view_1;
    lv_obj_t *video_dir_lbl_path;
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

typedef struct {
    // Screen video_dec
    lv_obj_t *video_dec;
    bool      video_dec_del;
    lv_obj_t *video_dec_view_scan;
    lv_obj_t *video_dec_imglist_1;
    lv_obj_t *video_dec_edit_2;
    lv_obj_t *video_dec_edit_3;
    lv_obj_t *video_dec_imglist_2;
    lv_obj_t *video_dec_view_1;
    lv_obj_t *video_dec_imglist_3;
    lv_obj_t *video_dec_edit_1;
    lv_obj_t *video_dec_img_1;
    lv_obj_t *video_dec_view_5;
    lv_obj_t *video_dec_view_4;
    lv_obj_t *video_dec_view_2;
    lv_obj_t *video_dec_img_2;
    lv_obj_t *video_dec_lbl_1;
    lv_obj_t *video_dec_view_3;
    lv_obj_t *video_dec_img_3;
    lv_obj_t *video_dec_lbl_2;
    lv_obj_t *video_dec_img_4;
    lv_obj_t *video_dec_img_5;
    lv_obj_t *video_dec_img_6;
    lv_obj_t *video_dec_img_7;
    lv_obj_t *video_dec_img_8;
    lv_obj_t *video_dec_img_9;
    lv_obj_t *video_dec_img_10;
    lv_obj_t *video_dec_img_11;
} lv_ui_video_dec;

typedef struct {
    // Screen video_dec_options
    lv_obj_t *video_dec_options;
    bool      video_dec_options_del;
    lv_obj_t *video_dec_options_view_1;
    lv_obj_t *video_dec_options_lbl_1;
    lv_obj_t *video_dec_options_btn_1;
    lv_obj_t *video_dec_options_btn_1_label;
    lv_obj_t *video_dec_options_btn_2;
    lv_obj_t *video_dec_options_btn_2_label;
} lv_ui_video_dec_options;

typedef struct {
    // Screen page_map
    lv_obj_t *page_map;
    bool      page_map_del;
    lv_obj_t *page_map_view_1;
    lv_obj_t *page_map_imgList_gear_mode;
    lv_obj_t *page_map_lbl_time;
    lv_obj_t *page_map_img_weather;
    lv_obj_t *page_map_lbl_temp;
    lv_obj_t *page_map_imgList_bluetooth;
    lv_obj_t *page_map_imgList_phone_bl;
    lv_obj_t *page_map_imgList_gps;
    lv_obj_t *page_map_imgList_networksignal;
    lv_obj_t *page_map_img_ready;
    lv_obj_t *page_map_view_2;
    lv_obj_t *page_map_lbl_endurance;
    lv_obj_t *page_map_img_charge;
    lv_obj_t *page_map_imgList_soc_beam;
    lv_obj_t *page_map_lbl_bat;
    lv_obj_t *page_map_imglist_bat;
    lv_obj_t *page_map_lbl_odo_num;
    lv_timer_t *page_map_timer_1;
    lv_obj_t *page_map_view_3;
    lv_obj_t *page_map_lbl_1;
    lv_obj_t *page_map_lbl_2;
    lv_obj_t *page_map_lbl_3;
    lv_obj_t *page_map_lbl_4;
    lv_obj_t *page_map_img_1;
    lv_timer_t *page_map_timer_2;
    lv_obj_t *page_map_btn_1;
    lv_obj_t *page_map_btn_1_label;
    lv_obj_t *page_map_btn_2;
    lv_obj_t *page_map_btn_2_label;
    lv_obj_t *page_map_view_4;
    lv_obj_t *page_map_lbl_5;
    lv_obj_t *page_map_lbl_6;
    lv_obj_t *page_map_lbl_7;
    lv_obj_t *page_map_lbl_8;
    lv_obj_t *page_map_lbl_9;
    lv_obj_t *page_map_lbl_10;
    lv_obj_t *page_map_img_2;
} lv_ui_page_map;

typedef struct {
    // Screen page_music
    lv_obj_t *page_music;
    bool      page_music_del;
    lv_obj_t *page_music_img_1;
    lv_obj_t *page_music_img_2;
    lv_timer_t *page_music_timer_1;
    lv_obj_t *page_music_slider_1;
    lv_obj_t *page_music_img_3;
    lv_obj_t *page_music_btn_1;
    lv_obj_t *page_music_btn_1_label;
} lv_ui_page_music;

typedef struct {
    // Screen page_meter
    lv_obj_t *page_meter;
    bool      page_meter_del;
    lv_obj_t *page_meter_img_road_eco;
    lv_obj_t *page_meter_img_arrow_eco;
    lv_obj_t *page_meter_img_bat_d;
    lv_obj_t *page_meter_img_position;
    lv_obj_t *page_meter_img_force_touch;
    lv_obj_t *page_meter_img_right_turn;
    lv_obj_t *page_meter_img_hdc;
    lv_obj_t *page_meter_img_auto;
    lv_obj_t *page_meter_img_box_open;
    lv_obj_t *page_meter_img_side_support;
    lv_obj_t *page_meter_img_tcs;
    lv_obj_t *page_meter_img_abs;
    lv_obj_t *page_meter_img_limping;
    lv_obj_t *page_meter_img_tapLoc;
    lv_obj_t *page_meter_img_car_fault;
    lv_obj_t *page_meter_img_P_mode;
    lv_obj_t *page_meter_img_brake_system_fault;
    lv_obj_t *page_meter_img_cruisework;
    lv_obj_t *page_meter_lbl_temp;
    lv_obj_t *page_meter_lbl_time;
    lv_obj_t *page_meter_lbl_odo_num;
    lv_obj_t *page_meter_lbl_odo;
    lv_obj_t *page_meter_lbl_bat;
    lv_obj_t *page_meter_lbl_endurance;
    lv_obj_t *page_meter_imglist_speed_ones;
    lv_obj_t *page_meter_imglist_speed_tens;
    lv_obj_t *page_meter_lbl_km;
    lv_obj_t *page_meter_imgList_high_low_beam;
    lv_obj_t *page_meter_anim_pwr_l;
    lv_obj_t *page_meter_anim_pwr_r;
    lv_obj_t *page_meter_view_call_in;
    lv_obj_t *page_meter_lbl_3;
    lv_obj_t *page_meter_lbl_phone_num;
    lv_obj_t *page_meter_img_1;
    lv_obj_t *page_meter_img_2;
    lv_obj_t *page_meter_lbl_2;
    lv_obj_t *page_meter_lbl_4;
    lv_timer_t *page_meter_timer_1;
    lv_timer_t *page_meter_timer_2;
    lv_timer_t *page_meter_timer_3;
    lv_obj_t *page_meter_imglist_1;
    lv_obj_t *page_meter_img_4;
    lv_obj_t *page_meter_img_5;
    lv_obj_t *page_meter_imglist_2;
    lv_obj_t *page_meter_imglist_3;
    lv_obj_t *page_meter_imglist_4;
    lv_obj_t *page_meter_imglist_5;
    lv_obj_t *page_meter_imglist_6;
    lv_obj_t *page_meter_img_6;
    lv_obj_t *page_meter_img_left_turn;
    lv_obj_t *page_meter_imglist_bat;
} lv_ui_page_meter;

typedef struct {
    // Screen power_on
    lv_obj_t *power_on;
    bool      power_on_del;
    lv_obj_t *power_on_img_1;
    lv_timer_t *power_on_timer_1;
} lv_ui_power_on;

// generate lv_ui gui_guider
typedef struct {
    lv_ui_usb_slave *usb_slave;
    lv_ui_video_rec *video_rec;
    lv_ui_sys_prompt *sys_prompt;
    lv_ui_sys_setting *sys_setting;
    lv_ui_video_photo *video_photo;
    lv_ui_video_play *video_play;
    lv_ui_video_file *video_file;
    lv_ui_video_dir *video_dir;
    lv_ui_car_parking *car_parking;
    lv_ui_line_drift *line_drift;
    lv_ui_sys_popwin *sys_popwin;
    lv_ui_video_dec *video_dec;
    lv_ui_video_dec_options *video_dec_options;
    lv_ui_page_map *page_map;
    lv_ui_page_music *page_music;
    lv_ui_page_meter *page_meter;
    lv_ui_power_on *power_on;

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
// Screen video_dec
lv_obj_t *setup_scr_video_dec(lv_ui *ui);
void unload_scr_video_dec(lv_ui *ui);



// Screen video_dec_options
lv_obj_t *setup_scr_video_dec_options(lv_ui *ui);
void unload_scr_video_dec_options(lv_ui *ui);
// Screen page_map
lv_obj_t *setup_scr_page_map(lv_ui *ui);
void unload_scr_page_map(lv_ui *ui);







// Screen page_music
lv_obj_t *setup_scr_page_music(lv_ui *ui);
void unload_scr_page_music(lv_ui *ui);
// Screen page_meter
lv_obj_t *setup_scr_page_meter(lv_ui *ui);
void unload_scr_page_meter(lv_ui *ui);












// Screen power_on
lv_obj_t *setup_scr_power_on(lv_ui *ui);
void unload_scr_power_on(lv_ui *ui);
#ifdef __cplusplus
}
#endif
#endif

#endif
