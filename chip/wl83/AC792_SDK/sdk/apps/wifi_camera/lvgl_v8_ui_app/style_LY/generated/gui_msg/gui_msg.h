#include "app_config.h"
#ifdef CONFIG_UI_STYLE_LY_ENABLE
/*Generate Code, Do NOT Edit!*/
#ifndef GUI_MSG_H_
#define GUI_MSG_H_
#ifdef __cplusplus
extern "C" {
#endif
#include <stdlib.h>
#include "../gui_guider.h"
#include "lvgl.h"
#include "../../custom/custom.h"
#include "time.h"

typedef enum {
    GUI_MSG_ACCESS_GET = 0,
    GUI_MSG_ACCESS_SET,
} gui_msg_action_t;

typedef enum {
    GUI_MSG_SUBSCRIBE = 0,
    GUI_MSG_UNSUBSCRIBE,
} gui_msg_subscribe_t;

typedef enum {
    VALUE_INT = 1,
    VALUE_CHAR,
    VALUE_SHORT,
    VALUE_COORD,
    VALUE_BOOL,
    VALUE_STRING,
    VALUE_COLOR,
    VALUE_DATE,
    VALUE_POINT,
    VALUE_TIME,
    VALUE_ARRAY,
    VALUE_UNKNOWN = 0,
} gui_msg_data_type_t;

typedef enum {
    GUI_MSG_ARRAY_TYPE_INVALID = 0,
    GUI_MSG_ARRAY_TYPE_STRING,
    GUI_MSG_ARRAY_TYPE_INT32,
    GUI_MSG_ARRAY_TYPE_COORD,
    GUI_MSG_ARRAY_TYPE_BOOL,
    GUI_MSG_ARRAY_TYPE_COLOR,
    GUI_MSG_ARRAY_TYPE_DATE,
    GUI_MSG_ARRAY_TYPE_POINT,
    GUI_MSG_ARRAY_TYPE_TIME,
} gui_msg_array_type_t;

typedef enum {
    GUI_MSG_STATUS_SUCCESS = 0,
    GUI_MSG_STATUS_ERROR = -1,
    GUI_MSG_STATUS_NO_SUBSCRIBE = -2,
    GUI_MSG_STATUS_NO_FOUND_ID = -3,
} gui_msg_status_t;

typedef enum {
    GUI_MSG_SEND_DONE = 0,
    GUI_MSG_SENDING,
} gui_msg_send_status_t;

typedef union {
    int32_t value_int;
    lv_coord_t value_coord;
    bool value_bool;
    char *value_string;
    lv_color_t value_color;
    lv_calendar_date_t value_date;
    lv_point_t value_point;
    struct tm value_time;
    struct {
        void *ptr;
        int32_t len;
    } value_array;
} gui_msg_data_t;

typedef enum {
    GUI_MODEL_MSG_ID = 1,
    GUI_MODEL_GLOBAL_SUBPAGE_MSG_ID,
    GUI_MODEL_MAIN_MSG_ID,
    GUI_MODEL_SYS_SETTING_MSG_ID,
    GUI_MODEL_UPDATE_MSG_ID,
    GUI_MODEL_VIDEO_DEC_MSG_ID,
    GUI_MODEL_VIDEO_PHOTO_MSG_ID,
    GUI_MODEL_VIDEO_REC_MSG_ID,
    GUI_SPEED_NUM_MSG_ID,
    GUI_TYW_SYSTEM_MSG_ID,
    GUI_SYS_MODEL_MSG_ID = 0xf000,
} gui_msg_id_t;

enum {
    GUI_MSG_ID_CUSTOM_START = 0xb,

    GUI_MODEL_MSG_ID_CUR_TIME = 0xb,
    GUI_MODEL_MSG_ID_PREV_FILE = 0xc,
    GUI_MODEL_MSG_ID_NEXT_FILE = 0xd,
    GUI_MODEL_MSG_ID_VIDEO_PAUSE = 0xe,
    GUI_MODEL_MSG_ID_CUR_TIME_PROCESS = 0xf,
    GUI_MODEL_MSG_ID_FILE_NAME = 0x10,
    GUI_MODEL_MSG_ID_TOTAL_TIME = 0x11,
    GUI_MODEL_MSG_ID_FILE_PATH = 0x12,
    GUI_MODEL_MSG_ID_FILE_NUM = 0x13,
    GUI_MODEL_MSG_ID_MUSIC_STATE = 0x14,

    GUI_MODEL_GLOBAL_SUBPAGE_MSG_ID_SUBPAGE_ICON = 0x15,
    GUI_MODEL_GLOBAL_SUBPAGE_MSG_ID_FUNCKEY1 = 0x16,
    GUI_MODEL_GLOBAL_SUBPAGE_MSG_ID_FUNCKEY2 = 0x17,
    GUI_MODEL_GLOBAL_SUBPAGE_MSG_ID_FUNCKEY3 = 0x18,
    GUI_MODEL_GLOBAL_SUBPAGE_MSG_ID_FUNCKEY4 = 0x19,
    GUI_MODEL_GLOBAL_SUBPAGE_MSG_ID_TITLE = 0x1a,
    GUI_MODEL_GLOBAL_SUBPAGE_MSG_ID_HIDE_FUNCKEY1 = 0x1b,
    GUI_MODEL_GLOBAL_SUBPAGE_MSG_ID_HIDE_FUNCKEY2 = 0x1c,
    GUI_MODEL_GLOBAL_SUBPAGE_MSG_ID_HIDE_FUNCKEY3 = 0x1d,
    GUI_MODEL_GLOBAL_SUBPAGE_MSG_ID_HIDE_FUNCKEY4 = 0x1e,
    GUI_MODEL_GLOBAL_SUBPAGE_MSG_ID_SHOW_FUNCKEY1 = 0x1f,
    GUI_MODEL_GLOBAL_SUBPAGE_MSG_ID_SHOW_FUNCKEY2 = 0x20,
    GUI_MODEL_GLOBAL_SUBPAGE_MSG_ID_SHOW_FUNCKEY3 = 0x21,
    GUI_MODEL_GLOBAL_SUBPAGE_MSG_ID_SHOW_FUNCKEY4 = 0x22,
    GUI_MODEL_GLOBAL_SUBPAGE_MSG_ID_ROLLER_OPT = 0x23,
    GUI_MODEL_GLOBAL_SUBPAGE_MSG_ID_SHOW_ROLLER = 0x24,
    GUI_MODEL_GLOBAL_SUBPAGE_MSG_ID_HIDE_ROLLER = 0x25,
    GUI_MODEL_GLOBAL_SUBPAGE_MSG_ID_STATE_FUNKEY1 = 0x26,
    GUI_MODEL_GLOBAL_SUBPAGE_MSG_ID_STATE_FUNKEY2 = 0x27,
    GUI_MODEL_GLOBAL_SUBPAGE_MSG_ID_STATE_FUNKEY3 = 0x28,
    GUI_MODEL_GLOBAL_SUBPAGE_MSG_ID_STATE_FUNKEY4 = 0x29,

    GUI_MODEL_MAIN_MSG_ID_SYSTIME = 0x2a,
    GUI_MODEL_MAIN_MSG_ID_SD_ICON = 0x2b,
    GUI_MODEL_MAIN_MSG_ID_BATTERY = 0x2c,
    GUI_MODEL_MAIN_MSG_ID_SYS_PROMPT = 0x2d,
    GUI_MODEL_MAIN_MSG_ID_HEADLAMP = 0x2e,
    GUI_MODEL_MAIN_MSG_ID_SYS_PROMPT_SHOW = 0x2f,
    GUI_MODEL_MAIN_MSG_ID_SHOW_DEL_BTN = 0x30,
    GUI_MODEL_MAIN_MSG_ID_HIDE_DEL_BTN = 0x31,
    GUI_MODEL_MAIN_MSG_ID_SHOW_HOME_BTN = 0x32,
    GUI_MODEL_MAIN_MSG_ID_HIDE_HOME_BTN = 0x33,

    GUI_MODEL_SYS_SETTING_MSG_ID_FUNKEY4 = 0x34,
    GUI_MODEL_SYS_SETTING_MSG_ID_FUNKEY5 = 0x35,
    GUI_MODEL_SYS_SETTING_MSG_ID_FUNKEY6 = 0x36,
    GUI_MODEL_SYS_SETTING_MSG_ID_FUNKEY7 = 0x37,
    GUI_MODEL_SYS_SETTING_MSG_ID_SUBPAGE_WARNING = 0x38,
    GUI_MODEL_SYS_SETTING_MSG_ID_HIDE_VIEWDATE = 0x39,
    GUI_MODEL_SYS_SETTING_MSG_ID_HIDE_VIEWCARNUM = 0x3a,
    GUI_MODEL_SYS_SETTING_MSG_ID_HIDE_VIEWLIST = 0x3b,
    GUI_MODEL_SYS_SETTING_MSG_ID_HIDE_SUBPAGEWARNING = 0x3c,
    GUI_MODEL_SYS_SETTING_MSG_ID_SHOW_VIEWDATE = 0x3d,
    GUI_MODEL_SYS_SETTING_MSG_ID_SHOW_VIEWCARNUM = 0x3e,
    GUI_MODEL_SYS_SETTING_MSG_ID_SHOW_VIEWLIST = 0x3f,
    GUI_MODEL_SYS_SETTING_MSG_ID_SHOW_SUBPAGEWARNING = 0x40,
    GUI_MODEL_SYS_SETTING_MSG_ID_HIDE_FUNKEY5 = 0x41,
    GUI_MODEL_SYS_SETTING_MSG_ID_HIDE_FUNKEY6 = 0x42,
    GUI_MODEL_SYS_SETTING_MSG_ID_HIDE_FUNKEY7 = 0x43,
    GUI_MODEL_SYS_SETTING_MSG_ID_SHOW_FUNKEY4 = 0x44,
    GUI_MODEL_SYS_SETTING_MSG_ID_SHOW_FUNKEY5 = 0x45,
    GUI_MODEL_SYS_SETTING_MSG_ID_SHOW_FUNKEY6 = 0x46,
    GUI_MODEL_SYS_SETTING_MSG_ID_SHOW_FUNKEY7 = 0x47,
    GUI_MODEL_SYS_SETTING_MSG_ID_STATE_FUNKEY4 = 0x48,
    GUI_MODEL_SYS_SETTING_MSG_ID_STATE_FUNKEY5 = 0x49,
    GUI_MODEL_SYS_SETTING_MSG_ID_STATE_FUNKEY6 = 0x4a,
    GUI_MODEL_SYS_SETTING_MSG_ID_STATE_FUNKEY7 = 0x4b,
    GUI_MODEL_SYS_SETTING_MSG_ID_HIDE_FUNKEY4 = 0x4c,
    GUI_MODEL_SYS_SETTING_MSG_ID_SUBPAGE_WARNING_STATE = 0x4d,

    GUI_MODEL_UPDATE_MSG_ID_UPDATE_TIPS = 0x4e,
    GUI_MODEL_UPDATE_MSG_ID_UPDATE_PROCE = 0x4f,

    GUI_MODEL_VIDEO_DEC_MSG_ID_FILE_TYPE_IMG = 0x50,
    GUI_MODEL_VIDEO_DEC_MSG_ID_VIDEO_TIME_LAB = 0x51,
    GUI_MODEL_VIDEO_DEC_MSG_ID_FILE_NAME_LAB = 0x52,
    GUI_MODEL_VIDEO_DEC_MSG_ID_MEDIA_INFO_LAB = 0x53,
    GUI_MODEL_VIDEO_DEC_MSG_ID_SD_STATUS_IMG = 0x54,
    GUI_MODEL_VIDEO_DEC_MSG_ID_PLAY_STATUS_IMG = 0x55,
    GUI_MODEL_VIDEO_DEC_MSG_ID_VIDEO_CONT_SHOW = 0x56,
    GUI_MODEL_VIDEO_DEC_MSG_ID_FILE_LOCK_SHOW = 0x57,
    GUI_MODEL_VIDEO_DEC_MSG_ID_VIDEO_DEC_OPTIONS_LAB = 0x58,

    GUI_MODEL_VIDEO_PHOTO_MSG_ID_RESOLUTION_ICON = 0x59,
    GUI_MODEL_VIDEO_PHOTO_MSG_ID_AWB_ICON = 0x5a,
    GUI_MODEL_VIDEO_PHOTO_MSG_ID_QUALITY_ICON = 0x5b,
    GUI_MODEL_VIDEO_PHOTO_MSG_ID_SHOT_MODE_ICON = 0x5c,
    GUI_MODEL_VIDEO_PHOTO_MSG_ID_SHOW_HANDSHAKE = 0x5d,
    GUI_MODEL_VIDEO_PHOTO_MSG_ID_HIDE_HANDSHAKE = 0x5e,
    GUI_MODEL_VIDEO_PHOTO_MSG_ID_SHOW_SHOTS = 0x5f,
    GUI_MODEL_VIDEO_PHOTO_MSG_ID_HIDE_SHOTS = 0x60,
    GUI_MODEL_VIDEO_PHOTO_MSG_ID_SHOW_SHOTS_MODE = 0x61,
    GUI_MODEL_VIDEO_PHOTO_MSG_ID_HIDE_SHOTS_MODE = 0x62,
    GUI_MODEL_VIDEO_PHOTO_MSG_ID_PHOTO_REMAIN = 0x63,
    GUI_MODEL_VIDEO_PHOTO_MSG_ID_PEXP_ICON = 0x64,
    GUI_MODEL_VIDEO_PHOTO_MSG_ID_ISO_ICON = 0x65,
    GUI_MODEL_VIDEO_PHOTO_MSG_ID_DELAY_SATE = 0x66,
    GUI_MODEL_VIDEO_PHOTO_MSG_ID_DELAY_ICON = 0x67,
    GUI_MODEL_VIDEO_PHOTO_MSG_ID_HANDSHAKE_ICON = 0x68,
    GUI_MODEL_VIDEO_PHOTO_MSG_ID_SHOTS_ICON = 0x69,
    GUI_MODEL_VIDEO_PHOTO_MSG_ID_PHOTO_RESO = 0x6a,

    GUI_MODEL_VIDEO_REC_MSG_ID_CYCREC_ICON = 0x6b,
    GUI_MODEL_VIDEO_REC_MSG_ID_DELAYREC_ICON = 0x6c,
    GUI_MODEL_VIDEO_REC_MSG_ID_CAR_NUNBER = 0x6d,
    GUI_MODEL_VIDEO_REC_MSG_ID_REC_RESO = 0x6e,
    GUI_MODEL_VIDEO_REC_MSG_ID_REC_BTN = 0x6f,
    GUI_MODEL_VIDEO_REC_MSG_ID_SHOW_GSENSOR_ICON = 0x70,
    GUI_MODEL_VIDEO_REC_MSG_ID_HIDE_GSENSOR_ICON = 0x71,
    GUI_MODEL_VIDEO_REC_MSG_ID_SHOW_GUARD_ICON = 0x72,
    GUI_MODEL_VIDEO_REC_MSG_ID_HIDE_GUARD_ICON = 0x73,
    GUI_MODEL_VIDEO_REC_MSG_ID_SHOW_MOTION_ICON = 0x74,
    GUI_MODEL_VIDEO_REC_MSG_ID_HIDE_MOTION_ICON = 0x75,
    GUI_MODEL_VIDEO_REC_MSG_ID_SHOW_HDR_ICON = 0x76,
    GUI_MODEL_VIDEO_REC_MSG_ID_HIDE_HDR_ICON = 0x77,
    GUI_MODEL_VIDEO_REC_MSG_ID_REC_REMAIN_TIME = 0x78,
    GUI_MODEL_VIDEO_REC_MSG_ID_REC_TIME_STATE = 0x79,
    GUI_MODEL_VIDEO_REC_MSG_ID_VIDEO_REC_MENU = 0x7a,
    GUI_MODEL_VIDEO_REC_MSG_ID_MIC_ICON = 0x7b,
    GUI_MODEL_VIDEO_REC_MSG_ID_GSENSOR_ICON = 0x7c,
    GUI_MODEL_VIDEO_REC_MSG_ID_SD_ICON = 0x7d,
    GUI_MODEL_VIDEO_REC_MSG_ID_GUARD_STATE = 0x7e,
    GUI_MODEL_VIDEO_REC_MSG_ID_CYC_STATE = 0x7f,
    GUI_MODEL_VIDEO_REC_MSG_ID_MOTION_STATE = 0x80,
    GUI_MODEL_VIDEO_REC_MSG_ID_GAP_STATE = 0x81,
    GUI_MODEL_VIDEO_REC_MSG_ID_HDR_STATE = 0x82,
    GUI_MODEL_VIDEO_REC_MSG_ID_GRA_STATE = 0x83,
    GUI_MODEL_VIDEO_REC_MSG_ID_EXP_ICON = 0x84,
    GUI_MODEL_VIDEO_REC_MSG_ID_CAR_NUM = 0x85,
    GUI_MODEL_VIDEO_REC_MSG_ID_FLASH_HEADLIGHT = 0x86,
    GUI_MODEL_VIDEO_REC_MSG_ID_REC_ICON_STATE = 0x87,
    GUI_MODEL_VIDEO_REC_MSG_ID_KEY_STATE = 0x88,

    GUI_SPEED_NUM_MSG_ID_PROP = 0x89,

    GUI_TYW_SYSTEM_MSG_ID_BT_CONN = 0x8a,
    GUI_TYW_SYSTEM_MSG_ID_BT_DISCONN = 0x8b,
    GUI_TYW_SYSTEM_MSG_ID_PHONE_INCOME = 0x8c,
    GUI_TYW_SYSTEM_MSG_ID_PHONE_HANGUP = 0x8d,
    GUI_TYW_SYSTEM_MSG_ID_PHONE_NUMBER = 0x8e,
    GUI_TYW_SYSTEM_MSG_ID_MUSIC_INFO = 0x8f,

    GUI_SYS_MODEL_MSG_ID_SYS_TIME = 0xf001,

    GUI_MSG_ID_CUSTOM_END = 0x8f
};

typedef struct {
    lv_subject_t *subject;
    int32_t msg_id;
} gui_msg_sub_t;

typedef struct {
    int32_t msg_id;
    char is_subscribe;
    char is_unsubscribe;
} _gui_msg_status_t;

typedef int (*gui_msg_action_cb_t)(gui_msg_action_t, gui_msg_data_t *, gui_msg_data_type_t);

typedef struct {
    int32_t msg_id;
    gui_msg_action_cb_t cb;
    int32_t type;
} _gui_msg_entry_t;

extern void gui_msg_init(lv_ui *ui);
extern void gui_msg_init_ui();
extern void gui_msg_init_events();
extern void gui_msg_unsubscribe();
extern gui_msg_status_t gui_msg_send(int32_t msg_id, void *value, int32_t len);
extern gui_msg_send_status_t gui_msg_get_send_status();
#if LV_USE_GUIBUILDER_SIMULATOR && LV_USE_CUSTOM_MSG_GET
extern gui_msg_data_t *gui_msg_get(int32_t msg_id);
#else
extern GUI_WEAKREF gui_msg_data_t *gui_msg_get(int32_t msg_id);
#endif
extern gui_msg_data_t *gui_msg_get_guider(int32_t msg_id);
#if LV_USE_GUIBUILDER_SIMULATOR && LV_USE_CUSTOM_MSG_ACTION_CHANGE
extern void gui_msg_action_change(int32_t msg_id, gui_msg_action_t access, gui_msg_data_t *data, gui_msg_data_type_t type);
#else
extern GUI_WEAKREF void gui_msg_action_change(int32_t msg_id, gui_msg_action_t access, gui_msg_data_t *data, gui_msg_data_type_t type);
#endif
extern void gui_msg_action_change_guider(int32_t msg_id, gui_msg_action_t access, gui_msg_data_t *data, gui_msg_data_type_t type);
#if LV_USE_GUIBUILDER_SIMULATOR && LV_USE_CUSTOM_MSG_SUBSCRIBE_CHANGE
extern void gui_msg_subscribe_change(int32_t msg_id, gui_msg_subscribe_t sub_type);
#else
extern GUI_WEAKREF void gui_msg_subscribe_change(int32_t msg_id, gui_msg_subscribe_t sub_type);
#endif
extern void gui_msg_subscribe_change_guider(int32_t msg_id, gui_msg_subscribe_t sub_type);
extern lv_subject_t *gui_msg_get_subject(int32_t msg_id);
extern gui_msg_sub_t *gui_msg_get_sub(int32_t msg_id);
extern gui_msg_sub_t *gui_msg_create_sub(int32_t msg_id);
extern gui_msg_data_t *gui_msg_get_data();
extern gui_msg_data_type_t gui_msg_get_data_type(int32_t msg_id);
extern gui_msg_array_type_t gui_msg_get_data_array_type(int32_t msg_id);
extern char *gui_msg_get_name(int32_t msg_id);
extern bool gui_msg_has_observer(lv_subject_t *subject, lv_observer_cb_t cb, lv_obj_t *obj, void *user_data);
extern void gui_msg_setup_component(bool subscribe_enabled, bool event_enabled, lv_subject_t *subject, lv_obj_t *target_obj, gui_msg_data_t *msg_data, lv_observer_cb_t observer_cb, int32_t msg_id, gui_msg_action_t msg_action, gui_msg_data_type_t data_type, lv_event_cb_t event_cb);

extern void gui_msg_set_visible_by_bool_cb(lv_observer_t *observer, lv_subject_t *subject);
extern void gui_msg_set_label_text_by_string_cb(lv_observer_t *observer, lv_subject_t *subject);
extern void gui_msg_set_control_state_by_int32_cb(lv_observer_t *observer, lv_subject_t *subject);
extern void gui_msg_set_roller_roller_name_by_string_cb(lv_observer_t *observer, lv_subject_t *subject);
extern void gui_msg_set_bar_bar_value_by_int32_cb(lv_observer_t *observer, lv_subject_t *subject);
extern void gui_msg_set_imglist_selected_index_by_int32_cb(lv_observer_t *observer, lv_subject_t *subject);
extern void gui_msg_set_textarea_text_by_string_cb(lv_observer_t *observer, lv_subject_t *subject);
extern void gui_msg_change_textarea_text_cb(lv_event_t *e);
extern void _gui_msg_char_array_cb(char **var_ptr, const char *init_value, bool *is_init, gui_msg_action_t access, gui_msg_data_t *data);
extern void _gui_msg_int32_cb(int32_t *var_ptr, gui_msg_action_t access, gui_msg_data_t *data);
extern void _gui_msg_state_cb(lv_state_t *var_ptr, gui_msg_action_t access, gui_msg_data_t *data);
extern void _gui_msg_obj_flag_cb(lv_obj_flag_t *var_ptr, gui_msg_action_t access, gui_msg_data_t *data);
extern void _gui_msg_tm_cb(struct tm *var_ptr, bool is_systime, gui_msg_action_t access, gui_msg_data_t *data);
extern void _gui_msg_bool_cb(bool *var_ptr, gui_msg_action_t access, gui_msg_data_t *data);
#if LV_USE_OBSERVER
#include "./gui_model_msg.h"
#include "./gui_model_global_subpage_msg.h"
#include "./gui_model_main_msg.h"
#include "./gui_model_sys_setting_msg.h"
#include "./gui_model_update_msg.h"
#include "./gui_model_video_dec_msg.h"
#include "./gui_model_video_photo_msg.h"
#include "./gui_model_video_rec_msg.h"
#include "./gui_speed_num_msg.h"
#include "./gui_sys_model_msg.h"
#include "./gui_tyw_system_msg.h"
#define GUI_MSG_MAX_ID GUI_SYS_MODEL_MSG_ID_SYS_TIME

extern int gui_model_msg_cur_time_cb(gui_msg_action_t access, gui_msg_data_t *data, gui_msg_data_type_t type);
extern int gui_model_msg_prev_file_cb(gui_msg_action_t access, gui_msg_data_t *data, gui_msg_data_type_t type);
extern int gui_model_msg_next_file_cb(gui_msg_action_t access, gui_msg_data_t *data, gui_msg_data_type_t type);
extern int gui_model_msg_video_pause_cb(gui_msg_action_t access, gui_msg_data_t *data, gui_msg_data_type_t type);
extern int gui_model_msg_cur_time_process_cb(gui_msg_action_t access, gui_msg_data_t *data, gui_msg_data_type_t type);
extern int gui_model_msg_file_name_cb(gui_msg_action_t access, gui_msg_data_t *data, gui_msg_data_type_t type);
extern int gui_model_msg_total_time_cb(gui_msg_action_t access, gui_msg_data_t *data, gui_msg_data_type_t type);
extern int gui_model_msg_file_path_cb(gui_msg_action_t access, gui_msg_data_t *data, gui_msg_data_type_t type);
extern int gui_model_msg_file_num_cb(gui_msg_action_t access, gui_msg_data_t *data, gui_msg_data_type_t type);
extern int gui_model_msg_music_state_cb(gui_msg_action_t access, gui_msg_data_t *data, gui_msg_data_type_t type);

extern int gui_model_global_subpage_msg_subpage_icon_cb(gui_msg_action_t access, gui_msg_data_t *data, gui_msg_data_type_t type);
extern int gui_model_global_subpage_msg_funckey1_cb(gui_msg_action_t access, gui_msg_data_t *data, gui_msg_data_type_t type);
extern int gui_model_global_subpage_msg_funckey2_cb(gui_msg_action_t access, gui_msg_data_t *data, gui_msg_data_type_t type);
extern int gui_model_global_subpage_msg_funckey3_cb(gui_msg_action_t access, gui_msg_data_t *data, gui_msg_data_type_t type);
extern int gui_model_global_subpage_msg_funckey4_cb(gui_msg_action_t access, gui_msg_data_t *data, gui_msg_data_type_t type);
extern int gui_model_global_subpage_msg_title_cb(gui_msg_action_t access, gui_msg_data_t *data, gui_msg_data_type_t type);
extern int gui_model_global_subpage_msg_hide_funckey1_cb(gui_msg_action_t access, gui_msg_data_t *data, gui_msg_data_type_t type);
extern int gui_model_global_subpage_msg_hide_funckey2_cb(gui_msg_action_t access, gui_msg_data_t *data, gui_msg_data_type_t type);
extern int gui_model_global_subpage_msg_hide_funckey3_cb(gui_msg_action_t access, gui_msg_data_t *data, gui_msg_data_type_t type);
extern int gui_model_global_subpage_msg_hide_funckey4_cb(gui_msg_action_t access, gui_msg_data_t *data, gui_msg_data_type_t type);
extern int gui_model_global_subpage_msg_show_funckey1_cb(gui_msg_action_t access, gui_msg_data_t *data, gui_msg_data_type_t type);
extern int gui_model_global_subpage_msg_show_funckey2_cb(gui_msg_action_t access, gui_msg_data_t *data, gui_msg_data_type_t type);
extern int gui_model_global_subpage_msg_show_funckey3_cb(gui_msg_action_t access, gui_msg_data_t *data, gui_msg_data_type_t type);
extern int gui_model_global_subpage_msg_show_funckey4_cb(gui_msg_action_t access, gui_msg_data_t *data, gui_msg_data_type_t type);
extern int gui_model_global_subpage_msg_roller_opt_cb(gui_msg_action_t access, gui_msg_data_t *data, gui_msg_data_type_t type);
extern int gui_model_global_subpage_msg_show_roller_cb(gui_msg_action_t access, gui_msg_data_t *data, gui_msg_data_type_t type);
extern int gui_model_global_subpage_msg_hide_roller_cb(gui_msg_action_t access, gui_msg_data_t *data, gui_msg_data_type_t type);
extern int gui_model_global_subpage_msg_state_funkey1_cb(gui_msg_action_t access, gui_msg_data_t *data, gui_msg_data_type_t type);
extern int gui_model_global_subpage_msg_state_funkey2_cb(gui_msg_action_t access, gui_msg_data_t *data, gui_msg_data_type_t type);
extern int gui_model_global_subpage_msg_state_funkey3_cb(gui_msg_action_t access, gui_msg_data_t *data, gui_msg_data_type_t type);
extern int gui_model_global_subpage_msg_state_funkey4_cb(gui_msg_action_t access, gui_msg_data_t *data, gui_msg_data_type_t type);

extern int gui_model_main_msg_systime_cb(gui_msg_action_t access, gui_msg_data_t *data, gui_msg_data_type_t type);
extern int gui_model_main_msg_sd_icon_cb(gui_msg_action_t access, gui_msg_data_t *data, gui_msg_data_type_t type);
extern int gui_model_main_msg_battery_cb(gui_msg_action_t access, gui_msg_data_t *data, gui_msg_data_type_t type);
extern int gui_model_main_msg_sys_prompt_cb(gui_msg_action_t access, gui_msg_data_t *data, gui_msg_data_type_t type);
extern int gui_model_main_msg_headlamp_cb(gui_msg_action_t access, gui_msg_data_t *data, gui_msg_data_type_t type);
extern int gui_model_main_msg_sys_prompt_show_cb(gui_msg_action_t access, gui_msg_data_t *data, gui_msg_data_type_t type);
extern int gui_model_main_msg_show_del_btn_cb(gui_msg_action_t access, gui_msg_data_t *data, gui_msg_data_type_t type);
extern int gui_model_main_msg_hide_del_btn_cb(gui_msg_action_t access, gui_msg_data_t *data, gui_msg_data_type_t type);
extern int gui_model_main_msg_show_home_btn_cb(gui_msg_action_t access, gui_msg_data_t *data, gui_msg_data_type_t type);
extern int gui_model_main_msg_hide_home_btn_cb(gui_msg_action_t access, gui_msg_data_t *data, gui_msg_data_type_t type);

extern int gui_model_sys_setting_msg_funkey4_cb(gui_msg_action_t access, gui_msg_data_t *data, gui_msg_data_type_t type);
extern int gui_model_sys_setting_msg_funkey5_cb(gui_msg_action_t access, gui_msg_data_t *data, gui_msg_data_type_t type);
extern int gui_model_sys_setting_msg_funkey6_cb(gui_msg_action_t access, gui_msg_data_t *data, gui_msg_data_type_t type);
extern int gui_model_sys_setting_msg_funkey7_cb(gui_msg_action_t access, gui_msg_data_t *data, gui_msg_data_type_t type);
extern int gui_model_sys_setting_msg_subpage_warning_cb(gui_msg_action_t access, gui_msg_data_t *data, gui_msg_data_type_t type);
extern int gui_model_sys_setting_msg_hide_viewdate_cb(gui_msg_action_t access, gui_msg_data_t *data, gui_msg_data_type_t type);
extern int gui_model_sys_setting_msg_hide_viewcarnum_cb(gui_msg_action_t access, gui_msg_data_t *data, gui_msg_data_type_t type);
extern int gui_model_sys_setting_msg_hide_viewlist_cb(gui_msg_action_t access, gui_msg_data_t *data, gui_msg_data_type_t type);
extern int gui_model_sys_setting_msg_hide_subpagewarning_cb(gui_msg_action_t access, gui_msg_data_t *data, gui_msg_data_type_t type);
extern int gui_model_sys_setting_msg_show_viewdate_cb(gui_msg_action_t access, gui_msg_data_t *data, gui_msg_data_type_t type);
extern int gui_model_sys_setting_msg_show_viewcarnum_cb(gui_msg_action_t access, gui_msg_data_t *data, gui_msg_data_type_t type);
extern int gui_model_sys_setting_msg_show_viewlist_cb(gui_msg_action_t access, gui_msg_data_t *data, gui_msg_data_type_t type);
extern int gui_model_sys_setting_msg_show_subpagewarning_cb(gui_msg_action_t access, gui_msg_data_t *data, gui_msg_data_type_t type);
extern int gui_model_sys_setting_msg_hide_funkey5_cb(gui_msg_action_t access, gui_msg_data_t *data, gui_msg_data_type_t type);
extern int gui_model_sys_setting_msg_hide_funkey6_cb(gui_msg_action_t access, gui_msg_data_t *data, gui_msg_data_type_t type);
extern int gui_model_sys_setting_msg_hide_funkey7_cb(gui_msg_action_t access, gui_msg_data_t *data, gui_msg_data_type_t type);
extern int gui_model_sys_setting_msg_show_funkey4_cb(gui_msg_action_t access, gui_msg_data_t *data, gui_msg_data_type_t type);
extern int gui_model_sys_setting_msg_show_funkey5_cb(gui_msg_action_t access, gui_msg_data_t *data, gui_msg_data_type_t type);
extern int gui_model_sys_setting_msg_show_funkey6_cb(gui_msg_action_t access, gui_msg_data_t *data, gui_msg_data_type_t type);
extern int gui_model_sys_setting_msg_show_funkey7_cb(gui_msg_action_t access, gui_msg_data_t *data, gui_msg_data_type_t type);
extern int gui_model_sys_setting_msg_state_funkey4_cb(gui_msg_action_t access, gui_msg_data_t *data, gui_msg_data_type_t type);
extern int gui_model_sys_setting_msg_state_funkey5_cb(gui_msg_action_t access, gui_msg_data_t *data, gui_msg_data_type_t type);
extern int gui_model_sys_setting_msg_state_funkey6_cb(gui_msg_action_t access, gui_msg_data_t *data, gui_msg_data_type_t type);
extern int gui_model_sys_setting_msg_state_funkey7_cb(gui_msg_action_t access, gui_msg_data_t *data, gui_msg_data_type_t type);
extern int gui_model_sys_setting_msg_hide_funkey4_cb(gui_msg_action_t access, gui_msg_data_t *data, gui_msg_data_type_t type);
extern int gui_model_sys_setting_msg_subpage_warning_state_cb(gui_msg_action_t access, gui_msg_data_t *data, gui_msg_data_type_t type);

extern int gui_model_update_msg_update_tips_cb(gui_msg_action_t access, gui_msg_data_t *data, gui_msg_data_type_t type);
extern int gui_model_update_msg_update_proce_cb(gui_msg_action_t access, gui_msg_data_t *data, gui_msg_data_type_t type);

extern int gui_model_video_dec_msg_file_type_img_cb(gui_msg_action_t access, gui_msg_data_t *data, gui_msg_data_type_t type);
extern int gui_model_video_dec_msg_video_time_lab_cb(gui_msg_action_t access, gui_msg_data_t *data, gui_msg_data_type_t type);
extern int gui_model_video_dec_msg_file_name_lab_cb(gui_msg_action_t access, gui_msg_data_t *data, gui_msg_data_type_t type);
extern int gui_model_video_dec_msg_media_info_lab_cb(gui_msg_action_t access, gui_msg_data_t *data, gui_msg_data_type_t type);
extern int gui_model_video_dec_msg_sd_status_img_cb(gui_msg_action_t access, gui_msg_data_t *data, gui_msg_data_type_t type);
extern int gui_model_video_dec_msg_play_status_img_cb(gui_msg_action_t access, gui_msg_data_t *data, gui_msg_data_type_t type);
extern int gui_model_video_dec_msg_video_cont_show_cb(gui_msg_action_t access, gui_msg_data_t *data, gui_msg_data_type_t type);
extern int gui_model_video_dec_msg_file_lock_show_cb(gui_msg_action_t access, gui_msg_data_t *data, gui_msg_data_type_t type);
extern int gui_model_video_dec_msg_video_dec_options_lab_cb(gui_msg_action_t access, gui_msg_data_t *data, gui_msg_data_type_t type);

extern int gui_model_video_photo_msg_resolution_icon_cb(gui_msg_action_t access, gui_msg_data_t *data, gui_msg_data_type_t type);
extern int gui_model_video_photo_msg_awb_icon_cb(gui_msg_action_t access, gui_msg_data_t *data, gui_msg_data_type_t type);
extern int gui_model_video_photo_msg_quality_icon_cb(gui_msg_action_t access, gui_msg_data_t *data, gui_msg_data_type_t type);
extern int gui_model_video_photo_msg_shot_mode_icon_cb(gui_msg_action_t access, gui_msg_data_t *data, gui_msg_data_type_t type);
extern int gui_model_video_photo_msg_show_handshake_cb(gui_msg_action_t access, gui_msg_data_t *data, gui_msg_data_type_t type);
extern int gui_model_video_photo_msg_hide_handshake_cb(gui_msg_action_t access, gui_msg_data_t *data, gui_msg_data_type_t type);
extern int gui_model_video_photo_msg_show_shots_cb(gui_msg_action_t access, gui_msg_data_t *data, gui_msg_data_type_t type);
extern int gui_model_video_photo_msg_hide_shots_cb(gui_msg_action_t access, gui_msg_data_t *data, gui_msg_data_type_t type);
extern int gui_model_video_photo_msg_show_shots_mode_cb(gui_msg_action_t access, gui_msg_data_t *data, gui_msg_data_type_t type);
extern int gui_model_video_photo_msg_hide_shots_mode_cb(gui_msg_action_t access, gui_msg_data_t *data, gui_msg_data_type_t type);
extern int gui_model_video_photo_msg_photo_remain_cb(gui_msg_action_t access, gui_msg_data_t *data, gui_msg_data_type_t type);
extern int gui_model_video_photo_msg_pexp_icon_cb(gui_msg_action_t access, gui_msg_data_t *data, gui_msg_data_type_t type);
extern int gui_model_video_photo_msg_iso_icon_cb(gui_msg_action_t access, gui_msg_data_t *data, gui_msg_data_type_t type);
extern int gui_model_video_photo_msg_delay_sate_cb(gui_msg_action_t access, gui_msg_data_t *data, gui_msg_data_type_t type);
extern int gui_model_video_photo_msg_delay_icon_cb(gui_msg_action_t access, gui_msg_data_t *data, gui_msg_data_type_t type);
extern int gui_model_video_photo_msg_handshake_icon_cb(gui_msg_action_t access, gui_msg_data_t *data, gui_msg_data_type_t type);
extern int gui_model_video_photo_msg_shots_icon_cb(gui_msg_action_t access, gui_msg_data_t *data, gui_msg_data_type_t type);
extern int gui_model_video_photo_msg_photo_reso_cb(gui_msg_action_t access, gui_msg_data_t *data, gui_msg_data_type_t type);

extern int gui_model_video_rec_msg_cycrec_icon_cb(gui_msg_action_t access, gui_msg_data_t *data, gui_msg_data_type_t type);
extern int gui_model_video_rec_msg_delayrec_icon_cb(gui_msg_action_t access, gui_msg_data_t *data, gui_msg_data_type_t type);
extern int gui_model_video_rec_msg_car_nunber_cb(gui_msg_action_t access, gui_msg_data_t *data, gui_msg_data_type_t type);
extern int gui_model_video_rec_msg_rec_reso_cb(gui_msg_action_t access, gui_msg_data_t *data, gui_msg_data_type_t type);
extern int gui_model_video_rec_msg_rec_btn_cb(gui_msg_action_t access, gui_msg_data_t *data, gui_msg_data_type_t type);
extern int gui_model_video_rec_msg_show_gsensor_icon_cb(gui_msg_action_t access, gui_msg_data_t *data, gui_msg_data_type_t type);
extern int gui_model_video_rec_msg_hide_gsensor_icon_cb(gui_msg_action_t access, gui_msg_data_t *data, gui_msg_data_type_t type);
extern int gui_model_video_rec_msg_show_guard_icon_cb(gui_msg_action_t access, gui_msg_data_t *data, gui_msg_data_type_t type);
extern int gui_model_video_rec_msg_hide_guard_icon_cb(gui_msg_action_t access, gui_msg_data_t *data, gui_msg_data_type_t type);
extern int gui_model_video_rec_msg_show_motion_icon_cb(gui_msg_action_t access, gui_msg_data_t *data, gui_msg_data_type_t type);
extern int gui_model_video_rec_msg_hide_motion_icon_cb(gui_msg_action_t access, gui_msg_data_t *data, gui_msg_data_type_t type);
extern int gui_model_video_rec_msg_show_hdr_icon_cb(gui_msg_action_t access, gui_msg_data_t *data, gui_msg_data_type_t type);
extern int gui_model_video_rec_msg_hide_hdr_icon_cb(gui_msg_action_t access, gui_msg_data_t *data, gui_msg_data_type_t type);
extern int gui_model_video_rec_msg_rec_remain_time_cb(gui_msg_action_t access, gui_msg_data_t *data, gui_msg_data_type_t type);
extern int gui_model_video_rec_msg_rec_time_state_cb(gui_msg_action_t access, gui_msg_data_t *data, gui_msg_data_type_t type);
extern int gui_model_video_rec_msg_video_rec_menu_cb(gui_msg_action_t access, gui_msg_data_t *data, gui_msg_data_type_t type);
extern int gui_model_video_rec_msg_mic_icon_cb(gui_msg_action_t access, gui_msg_data_t *data, gui_msg_data_type_t type);
extern int gui_model_video_rec_msg_gsensor_icon_cb(gui_msg_action_t access, gui_msg_data_t *data, gui_msg_data_type_t type);
extern int gui_model_video_rec_msg_sd_icon_cb(gui_msg_action_t access, gui_msg_data_t *data, gui_msg_data_type_t type);
extern int gui_model_video_rec_msg_guard_state_cb(gui_msg_action_t access, gui_msg_data_t *data, gui_msg_data_type_t type);
extern int gui_model_video_rec_msg_cyc_state_cb(gui_msg_action_t access, gui_msg_data_t *data, gui_msg_data_type_t type);
extern int gui_model_video_rec_msg_motion_state_cb(gui_msg_action_t access, gui_msg_data_t *data, gui_msg_data_type_t type);
extern int gui_model_video_rec_msg_gap_state_cb(gui_msg_action_t access, gui_msg_data_t *data, gui_msg_data_type_t type);
extern int gui_model_video_rec_msg_hdr_state_cb(gui_msg_action_t access, gui_msg_data_t *data, gui_msg_data_type_t type);
extern int gui_model_video_rec_msg_gra_state_cb(gui_msg_action_t access, gui_msg_data_t *data, gui_msg_data_type_t type);
extern int gui_model_video_rec_msg_exp_icon_cb(gui_msg_action_t access, gui_msg_data_t *data, gui_msg_data_type_t type);
extern int gui_model_video_rec_msg_car_num_cb(gui_msg_action_t access, gui_msg_data_t *data, gui_msg_data_type_t type);
extern int gui_model_video_rec_msg_flash_headlight_cb(gui_msg_action_t access, gui_msg_data_t *data, gui_msg_data_type_t type);
extern int gui_model_video_rec_msg_rec_icon_state_cb(gui_msg_action_t access, gui_msg_data_t *data, gui_msg_data_type_t type);
extern int gui_model_video_rec_msg_key_state_cb(gui_msg_action_t access, gui_msg_data_t *data, gui_msg_data_type_t type);

extern int gui_speed_num_msg_prop_cb(gui_msg_action_t access, gui_msg_data_t *data, gui_msg_data_type_t type);

extern int gui_tyw_system_msg_bt_conn_cb(gui_msg_action_t access, gui_msg_data_t *data, gui_msg_data_type_t type);
extern int gui_tyw_system_msg_bt_disconn_cb(gui_msg_action_t access, gui_msg_data_t *data, gui_msg_data_type_t type);
extern int gui_tyw_system_msg_phone_income_cb(gui_msg_action_t access, gui_msg_data_t *data, gui_msg_data_type_t type);
extern int gui_tyw_system_msg_phone_hangup_cb(gui_msg_action_t access, gui_msg_data_t *data, gui_msg_data_type_t type);
extern int gui_tyw_system_msg_phone_number_cb(gui_msg_action_t access, gui_msg_data_t *data, gui_msg_data_type_t type);
extern int gui_tyw_system_msg_music_info_cb(gui_msg_action_t access, gui_msg_data_t *data, gui_msg_data_type_t type);

extern int gui_sys_model_msg_sys_time_cb(gui_msg_action_t access, gui_msg_data_t *data, gui_msg_data_type_t type);

#if !LV_USE_GUIBUILDER_SIMULATOR
static const _gui_msg_entry_t gui_msg_entry_table[] = {
    { GUI_MODEL_MSG_ID_CUR_TIME, gui_model_msg_cur_time_cb, VALUE_STRING },
    { GUI_MODEL_MSG_ID_PREV_FILE, gui_model_msg_prev_file_cb, VALUE_INT },
    { GUI_MODEL_MSG_ID_NEXT_FILE, gui_model_msg_next_file_cb, VALUE_INT },
    { GUI_MODEL_MSG_ID_VIDEO_PAUSE, gui_model_msg_video_pause_cb, VALUE_INT },
    { GUI_MODEL_MSG_ID_CUR_TIME_PROCESS, gui_model_msg_cur_time_process_cb, VALUE_INT },
    { GUI_MODEL_MSG_ID_FILE_NAME, gui_model_msg_file_name_cb, VALUE_STRING },
    { GUI_MODEL_MSG_ID_TOTAL_TIME, gui_model_msg_total_time_cb, VALUE_STRING },
    { GUI_MODEL_MSG_ID_FILE_PATH, gui_model_msg_file_path_cb, VALUE_STRING },
    { GUI_MODEL_MSG_ID_FILE_NUM, gui_model_msg_file_num_cb, VALUE_STRING },
    { GUI_MODEL_MSG_ID_MUSIC_STATE, gui_model_msg_music_state_cb, VALUE_INT },

    { GUI_MODEL_GLOBAL_SUBPAGE_MSG_ID_SUBPAGE_ICON, gui_model_global_subpage_msg_subpage_icon_cb, VALUE_INT },
    { GUI_MODEL_GLOBAL_SUBPAGE_MSG_ID_FUNCKEY1, gui_model_global_subpage_msg_funckey1_cb, VALUE_STRING },
    { GUI_MODEL_GLOBAL_SUBPAGE_MSG_ID_FUNCKEY2, gui_model_global_subpage_msg_funckey2_cb, VALUE_STRING },
    { GUI_MODEL_GLOBAL_SUBPAGE_MSG_ID_FUNCKEY3, gui_model_global_subpage_msg_funckey3_cb, VALUE_STRING },
    { GUI_MODEL_GLOBAL_SUBPAGE_MSG_ID_FUNCKEY4, gui_model_global_subpage_msg_funckey4_cb, VALUE_STRING },
    { GUI_MODEL_GLOBAL_SUBPAGE_MSG_ID_TITLE, gui_model_global_subpage_msg_title_cb, VALUE_STRING },
    { GUI_MODEL_GLOBAL_SUBPAGE_MSG_ID_HIDE_FUNCKEY1, gui_model_global_subpage_msg_hide_funckey1_cb, VALUE_INT },
    { GUI_MODEL_GLOBAL_SUBPAGE_MSG_ID_HIDE_FUNCKEY2, gui_model_global_subpage_msg_hide_funckey2_cb, VALUE_INT },
    { GUI_MODEL_GLOBAL_SUBPAGE_MSG_ID_HIDE_FUNCKEY3, gui_model_global_subpage_msg_hide_funckey3_cb, VALUE_INT },
    { GUI_MODEL_GLOBAL_SUBPAGE_MSG_ID_HIDE_FUNCKEY4, gui_model_global_subpage_msg_hide_funckey4_cb, VALUE_INT },
    { GUI_MODEL_GLOBAL_SUBPAGE_MSG_ID_SHOW_FUNCKEY1, gui_model_global_subpage_msg_show_funckey1_cb, VALUE_INT },
    { GUI_MODEL_GLOBAL_SUBPAGE_MSG_ID_SHOW_FUNCKEY2, gui_model_global_subpage_msg_show_funckey2_cb, VALUE_INT },
    { GUI_MODEL_GLOBAL_SUBPAGE_MSG_ID_SHOW_FUNCKEY3, gui_model_global_subpage_msg_show_funckey3_cb, VALUE_INT },
    { GUI_MODEL_GLOBAL_SUBPAGE_MSG_ID_SHOW_FUNCKEY4, gui_model_global_subpage_msg_show_funckey4_cb, VALUE_INT },
    { GUI_MODEL_GLOBAL_SUBPAGE_MSG_ID_ROLLER_OPT, gui_model_global_subpage_msg_roller_opt_cb, VALUE_STRING },
    { GUI_MODEL_GLOBAL_SUBPAGE_MSG_ID_SHOW_ROLLER, gui_model_global_subpage_msg_show_roller_cb, VALUE_INT },
    { GUI_MODEL_GLOBAL_SUBPAGE_MSG_ID_HIDE_ROLLER, gui_model_global_subpage_msg_hide_roller_cb, VALUE_INT },
    { GUI_MODEL_GLOBAL_SUBPAGE_MSG_ID_STATE_FUNKEY1, gui_model_global_subpage_msg_state_funkey1_cb, VALUE_INT },
    { GUI_MODEL_GLOBAL_SUBPAGE_MSG_ID_STATE_FUNKEY2, gui_model_global_subpage_msg_state_funkey2_cb, VALUE_INT },
    { GUI_MODEL_GLOBAL_SUBPAGE_MSG_ID_STATE_FUNKEY3, gui_model_global_subpage_msg_state_funkey3_cb, VALUE_INT },
    { GUI_MODEL_GLOBAL_SUBPAGE_MSG_ID_STATE_FUNKEY4, gui_model_global_subpage_msg_state_funkey4_cb, VALUE_INT },

    { GUI_MODEL_MAIN_MSG_ID_SYSTIME, gui_model_main_msg_systime_cb, VALUE_TIME },
    { GUI_MODEL_MAIN_MSG_ID_SD_ICON, gui_model_main_msg_sd_icon_cb, VALUE_INT },
    { GUI_MODEL_MAIN_MSG_ID_BATTERY, gui_model_main_msg_battery_cb, VALUE_INT },
    { GUI_MODEL_MAIN_MSG_ID_SYS_PROMPT, gui_model_main_msg_sys_prompt_cb, VALUE_STRING },
    { GUI_MODEL_MAIN_MSG_ID_HEADLAMP, gui_model_main_msg_headlamp_cb, VALUE_BOOL },
    { GUI_MODEL_MAIN_MSG_ID_SYS_PROMPT_SHOW, gui_model_main_msg_sys_prompt_show_cb, VALUE_BOOL },
    { GUI_MODEL_MAIN_MSG_ID_SHOW_DEL_BTN, gui_model_main_msg_show_del_btn_cb, VALUE_INT },
    { GUI_MODEL_MAIN_MSG_ID_HIDE_DEL_BTN, gui_model_main_msg_hide_del_btn_cb, VALUE_INT },
    { GUI_MODEL_MAIN_MSG_ID_SHOW_HOME_BTN, gui_model_main_msg_show_home_btn_cb, VALUE_INT },
    { GUI_MODEL_MAIN_MSG_ID_HIDE_HOME_BTN, gui_model_main_msg_hide_home_btn_cb, VALUE_INT },

    { GUI_MODEL_SYS_SETTING_MSG_ID_FUNKEY4, gui_model_sys_setting_msg_funkey4_cb, VALUE_STRING },
    { GUI_MODEL_SYS_SETTING_MSG_ID_FUNKEY5, gui_model_sys_setting_msg_funkey5_cb, VALUE_STRING },
    { GUI_MODEL_SYS_SETTING_MSG_ID_FUNKEY6, gui_model_sys_setting_msg_funkey6_cb, VALUE_STRING },
    { GUI_MODEL_SYS_SETTING_MSG_ID_FUNKEY7, gui_model_sys_setting_msg_funkey7_cb, VALUE_STRING },
    { GUI_MODEL_SYS_SETTING_MSG_ID_SUBPAGE_WARNING, gui_model_sys_setting_msg_subpage_warning_cb, VALUE_STRING },
    { GUI_MODEL_SYS_SETTING_MSG_ID_HIDE_VIEWDATE, gui_model_sys_setting_msg_hide_viewdate_cb, VALUE_INT },
    { GUI_MODEL_SYS_SETTING_MSG_ID_HIDE_VIEWCARNUM, gui_model_sys_setting_msg_hide_viewcarnum_cb, VALUE_INT },
    { GUI_MODEL_SYS_SETTING_MSG_ID_HIDE_VIEWLIST, gui_model_sys_setting_msg_hide_viewlist_cb, VALUE_INT },
    { GUI_MODEL_SYS_SETTING_MSG_ID_HIDE_SUBPAGEWARNING, gui_model_sys_setting_msg_hide_subpagewarning_cb, VALUE_INT },
    { GUI_MODEL_SYS_SETTING_MSG_ID_SHOW_VIEWDATE, gui_model_sys_setting_msg_show_viewdate_cb, VALUE_INT },
    { GUI_MODEL_SYS_SETTING_MSG_ID_SHOW_VIEWCARNUM, gui_model_sys_setting_msg_show_viewcarnum_cb, VALUE_INT },
    { GUI_MODEL_SYS_SETTING_MSG_ID_SHOW_VIEWLIST, gui_model_sys_setting_msg_show_viewlist_cb, VALUE_INT },
    { GUI_MODEL_SYS_SETTING_MSG_ID_SHOW_SUBPAGEWARNING, gui_model_sys_setting_msg_show_subpagewarning_cb, VALUE_INT },
    { GUI_MODEL_SYS_SETTING_MSG_ID_HIDE_FUNKEY5, gui_model_sys_setting_msg_hide_funkey5_cb, VALUE_INT },
    { GUI_MODEL_SYS_SETTING_MSG_ID_HIDE_FUNKEY6, gui_model_sys_setting_msg_hide_funkey6_cb, VALUE_INT },
    { GUI_MODEL_SYS_SETTING_MSG_ID_HIDE_FUNKEY7, gui_model_sys_setting_msg_hide_funkey7_cb, VALUE_INT },
    { GUI_MODEL_SYS_SETTING_MSG_ID_SHOW_FUNKEY4, gui_model_sys_setting_msg_show_funkey4_cb, VALUE_INT },
    { GUI_MODEL_SYS_SETTING_MSG_ID_SHOW_FUNKEY5, gui_model_sys_setting_msg_show_funkey5_cb, VALUE_INT },
    { GUI_MODEL_SYS_SETTING_MSG_ID_SHOW_FUNKEY6, gui_model_sys_setting_msg_show_funkey6_cb, VALUE_INT },
    { GUI_MODEL_SYS_SETTING_MSG_ID_SHOW_FUNKEY7, gui_model_sys_setting_msg_show_funkey7_cb, VALUE_INT },
    { GUI_MODEL_SYS_SETTING_MSG_ID_STATE_FUNKEY4, gui_model_sys_setting_msg_state_funkey4_cb, VALUE_INT },
    { GUI_MODEL_SYS_SETTING_MSG_ID_STATE_FUNKEY5, gui_model_sys_setting_msg_state_funkey5_cb, VALUE_INT },
    { GUI_MODEL_SYS_SETTING_MSG_ID_STATE_FUNKEY6, gui_model_sys_setting_msg_state_funkey6_cb, VALUE_INT },
    { GUI_MODEL_SYS_SETTING_MSG_ID_STATE_FUNKEY7, gui_model_sys_setting_msg_state_funkey7_cb, VALUE_INT },
    { GUI_MODEL_SYS_SETTING_MSG_ID_HIDE_FUNKEY4, gui_model_sys_setting_msg_hide_funkey4_cb, VALUE_INT },
    { GUI_MODEL_SYS_SETTING_MSG_ID_SUBPAGE_WARNING_STATE, gui_model_sys_setting_msg_subpage_warning_state_cb, VALUE_BOOL },

    { GUI_MODEL_UPDATE_MSG_ID_UPDATE_TIPS, gui_model_update_msg_update_tips_cb, VALUE_STRING },
    { GUI_MODEL_UPDATE_MSG_ID_UPDATE_PROCE, gui_model_update_msg_update_proce_cb, VALUE_INT },

    { GUI_MODEL_VIDEO_DEC_MSG_ID_FILE_TYPE_IMG, gui_model_video_dec_msg_file_type_img_cb, VALUE_INT },
    { GUI_MODEL_VIDEO_DEC_MSG_ID_VIDEO_TIME_LAB, gui_model_video_dec_msg_video_time_lab_cb, VALUE_STRING },
    { GUI_MODEL_VIDEO_DEC_MSG_ID_FILE_NAME_LAB, gui_model_video_dec_msg_file_name_lab_cb, VALUE_STRING },
    { GUI_MODEL_VIDEO_DEC_MSG_ID_MEDIA_INFO_LAB, gui_model_video_dec_msg_media_info_lab_cb, VALUE_STRING },
    { GUI_MODEL_VIDEO_DEC_MSG_ID_SD_STATUS_IMG, gui_model_video_dec_msg_sd_status_img_cb, VALUE_INT },
    { GUI_MODEL_VIDEO_DEC_MSG_ID_PLAY_STATUS_IMG, gui_model_video_dec_msg_play_status_img_cb, VALUE_INT },
    { GUI_MODEL_VIDEO_DEC_MSG_ID_VIDEO_CONT_SHOW, gui_model_video_dec_msg_video_cont_show_cb, VALUE_BOOL },
    { GUI_MODEL_VIDEO_DEC_MSG_ID_FILE_LOCK_SHOW, gui_model_video_dec_msg_file_lock_show_cb, VALUE_BOOL },
    { GUI_MODEL_VIDEO_DEC_MSG_ID_VIDEO_DEC_OPTIONS_LAB, gui_model_video_dec_msg_video_dec_options_lab_cb, VALUE_STRING },

    { GUI_MODEL_VIDEO_PHOTO_MSG_ID_RESOLUTION_ICON, gui_model_video_photo_msg_resolution_icon_cb, VALUE_STRING },
    { GUI_MODEL_VIDEO_PHOTO_MSG_ID_AWB_ICON, gui_model_video_photo_msg_awb_icon_cb, VALUE_INT },
    { GUI_MODEL_VIDEO_PHOTO_MSG_ID_QUALITY_ICON, gui_model_video_photo_msg_quality_icon_cb, VALUE_INT },
    { GUI_MODEL_VIDEO_PHOTO_MSG_ID_SHOT_MODE_ICON, gui_model_video_photo_msg_shot_mode_icon_cb, VALUE_INT },
    { GUI_MODEL_VIDEO_PHOTO_MSG_ID_SHOW_HANDSHAKE, gui_model_video_photo_msg_show_handshake_cb, VALUE_INT },
    { GUI_MODEL_VIDEO_PHOTO_MSG_ID_HIDE_HANDSHAKE, gui_model_video_photo_msg_hide_handshake_cb, VALUE_INT },
    { GUI_MODEL_VIDEO_PHOTO_MSG_ID_SHOW_SHOTS, gui_model_video_photo_msg_show_shots_cb, VALUE_INT },
    { GUI_MODEL_VIDEO_PHOTO_MSG_ID_HIDE_SHOTS, gui_model_video_photo_msg_hide_shots_cb, VALUE_INT },
    { GUI_MODEL_VIDEO_PHOTO_MSG_ID_SHOW_SHOTS_MODE, gui_model_video_photo_msg_show_shots_mode_cb, VALUE_INT },
    { GUI_MODEL_VIDEO_PHOTO_MSG_ID_HIDE_SHOTS_MODE, gui_model_video_photo_msg_hide_shots_mode_cb, VALUE_INT },
    { GUI_MODEL_VIDEO_PHOTO_MSG_ID_PHOTO_REMAIN, gui_model_video_photo_msg_photo_remain_cb, VALUE_STRING },
    { GUI_MODEL_VIDEO_PHOTO_MSG_ID_PEXP_ICON, gui_model_video_photo_msg_pexp_icon_cb, VALUE_INT },
    { GUI_MODEL_VIDEO_PHOTO_MSG_ID_ISO_ICON, gui_model_video_photo_msg_iso_icon_cb, VALUE_INT },
    { GUI_MODEL_VIDEO_PHOTO_MSG_ID_DELAY_SATE, gui_model_video_photo_msg_delay_sate_cb, VALUE_BOOL },
    { GUI_MODEL_VIDEO_PHOTO_MSG_ID_DELAY_ICON, gui_model_video_photo_msg_delay_icon_cb, VALUE_INT },
    { GUI_MODEL_VIDEO_PHOTO_MSG_ID_HANDSHAKE_ICON, gui_model_video_photo_msg_handshake_icon_cb, VALUE_INT },
    { GUI_MODEL_VIDEO_PHOTO_MSG_ID_SHOTS_ICON, gui_model_video_photo_msg_shots_icon_cb, VALUE_BOOL },
    { GUI_MODEL_VIDEO_PHOTO_MSG_ID_PHOTO_RESO, gui_model_video_photo_msg_photo_reso_cb, VALUE_STRING },

    { GUI_MODEL_VIDEO_REC_MSG_ID_CYCREC_ICON, gui_model_video_rec_msg_cycrec_icon_cb, VALUE_INT },
    { GUI_MODEL_VIDEO_REC_MSG_ID_DELAYREC_ICON, gui_model_video_rec_msg_delayrec_icon_cb, VALUE_INT },
    { GUI_MODEL_VIDEO_REC_MSG_ID_CAR_NUNBER, gui_model_video_rec_msg_car_nunber_cb, VALUE_STRING },
    { GUI_MODEL_VIDEO_REC_MSG_ID_REC_RESO, gui_model_video_rec_msg_rec_reso_cb, VALUE_STRING },
    { GUI_MODEL_VIDEO_REC_MSG_ID_REC_BTN, gui_model_video_rec_msg_rec_btn_cb, VALUE_INT },
    { GUI_MODEL_VIDEO_REC_MSG_ID_SHOW_GSENSOR_ICON, gui_model_video_rec_msg_show_gsensor_icon_cb, VALUE_INT },
    { GUI_MODEL_VIDEO_REC_MSG_ID_HIDE_GSENSOR_ICON, gui_model_video_rec_msg_hide_gsensor_icon_cb, VALUE_INT },
    { GUI_MODEL_VIDEO_REC_MSG_ID_SHOW_GUARD_ICON, gui_model_video_rec_msg_show_guard_icon_cb, VALUE_INT },
    { GUI_MODEL_VIDEO_REC_MSG_ID_HIDE_GUARD_ICON, gui_model_video_rec_msg_hide_guard_icon_cb, VALUE_INT },
    { GUI_MODEL_VIDEO_REC_MSG_ID_SHOW_MOTION_ICON, gui_model_video_rec_msg_show_motion_icon_cb, VALUE_INT },
    { GUI_MODEL_VIDEO_REC_MSG_ID_HIDE_MOTION_ICON, gui_model_video_rec_msg_hide_motion_icon_cb, VALUE_INT },
    { GUI_MODEL_VIDEO_REC_MSG_ID_SHOW_HDR_ICON, gui_model_video_rec_msg_show_hdr_icon_cb, VALUE_INT },
    { GUI_MODEL_VIDEO_REC_MSG_ID_HIDE_HDR_ICON, gui_model_video_rec_msg_hide_hdr_icon_cb, VALUE_INT },
    { GUI_MODEL_VIDEO_REC_MSG_ID_REC_REMAIN_TIME, gui_model_video_rec_msg_rec_remain_time_cb, VALUE_TIME },
    { GUI_MODEL_VIDEO_REC_MSG_ID_REC_TIME_STATE, gui_model_video_rec_msg_rec_time_state_cb, VALUE_INT },
    { GUI_MODEL_VIDEO_REC_MSG_ID_VIDEO_REC_MENU, gui_model_video_rec_msg_video_rec_menu_cb, VALUE_BOOL },
    { GUI_MODEL_VIDEO_REC_MSG_ID_MIC_ICON, gui_model_video_rec_msg_mic_icon_cb, VALUE_INT },
    { GUI_MODEL_VIDEO_REC_MSG_ID_GSENSOR_ICON, gui_model_video_rec_msg_gsensor_icon_cb, VALUE_INT },
    { GUI_MODEL_VIDEO_REC_MSG_ID_SD_ICON, gui_model_video_rec_msg_sd_icon_cb, VALUE_INT },
    { GUI_MODEL_VIDEO_REC_MSG_ID_GUARD_STATE, gui_model_video_rec_msg_guard_state_cb, VALUE_BOOL },
    { GUI_MODEL_VIDEO_REC_MSG_ID_CYC_STATE, gui_model_video_rec_msg_cyc_state_cb, VALUE_BOOL },
    { GUI_MODEL_VIDEO_REC_MSG_ID_MOTION_STATE, gui_model_video_rec_msg_motion_state_cb, VALUE_BOOL },
    { GUI_MODEL_VIDEO_REC_MSG_ID_GAP_STATE, gui_model_video_rec_msg_gap_state_cb, VALUE_BOOL },
    { GUI_MODEL_VIDEO_REC_MSG_ID_HDR_STATE, gui_model_video_rec_msg_hdr_state_cb, VALUE_BOOL },
    { GUI_MODEL_VIDEO_REC_MSG_ID_GRA_STATE, gui_model_video_rec_msg_gra_state_cb, VALUE_BOOL },
    { GUI_MODEL_VIDEO_REC_MSG_ID_EXP_ICON, gui_model_video_rec_msg_exp_icon_cb, VALUE_INT },
    { GUI_MODEL_VIDEO_REC_MSG_ID_CAR_NUM, gui_model_video_rec_msg_car_num_cb, VALUE_BOOL },
    { GUI_MODEL_VIDEO_REC_MSG_ID_FLASH_HEADLIGHT, gui_model_video_rec_msg_flash_headlight_cb, VALUE_BOOL },
    { GUI_MODEL_VIDEO_REC_MSG_ID_REC_ICON_STATE, gui_model_video_rec_msg_rec_icon_state_cb, VALUE_BOOL },
    { GUI_MODEL_VIDEO_REC_MSG_ID_KEY_STATE, gui_model_video_rec_msg_key_state_cb, VALUE_BOOL },

    { GUI_SPEED_NUM_MSG_ID_PROP, gui_speed_num_msg_prop_cb, VALUE_INT },

    { GUI_TYW_SYSTEM_MSG_ID_BT_CONN, gui_tyw_system_msg_bt_conn_cb, VALUE_INT },
    { GUI_TYW_SYSTEM_MSG_ID_BT_DISCONN, gui_tyw_system_msg_bt_disconn_cb, VALUE_INT },
    { GUI_TYW_SYSTEM_MSG_ID_PHONE_INCOME, gui_tyw_system_msg_phone_income_cb, VALUE_INT },
    { GUI_TYW_SYSTEM_MSG_ID_PHONE_HANGUP, gui_tyw_system_msg_phone_hangup_cb, VALUE_INT },
    { GUI_TYW_SYSTEM_MSG_ID_PHONE_NUMBER, gui_tyw_system_msg_phone_number_cb, VALUE_STRING },
    { GUI_TYW_SYSTEM_MSG_ID_MUSIC_INFO, gui_tyw_system_msg_music_info_cb, VALUE_INT },

    { GUI_SYS_MODEL_MSG_ID_SYS_TIME, gui_sys_model_msg_sys_time_cb, VALUE_TIME },
};
#endif

#endif

extern gui_msg_data_t guider_msg_data;

#ifdef __cplusplus
}
#endif
#endif /* GUI_MSG_H_ */

#endif
