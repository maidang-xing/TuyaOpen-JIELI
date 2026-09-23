#include "app_config.h"
#ifdef CONFIG_UI_STYLE_JL_ENABLE
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
    GUI_MODEL_MSG_ID = 0x0001,
    GUI_MODEL_GLOBAL_SUBPAGE_MSG_ID = 0x000B,
    GUI_MODEL_MAIN_MSG_ID = 0x0020,
    GUI_MODEL_SYS_SETTING_MSG_ID = 0x002E,
    GUI_MODEL_UPDATE_MSG_ID = 0x004C,
    GUI_MODEL_VIDEO_PHOTO_MSG_ID = 0x004f,
    GUI_MODEL_VIDEO_PLAY_MSG_ID = 0x005D,
    GUI_MODEL_VIDEO_REC_MSG_ID = 0x0061,
    GUI_SYS_MODEL_MSG_ID = 0xf000,
} gui_msg_id_t;

typedef struct {
    lv_subject_t *subject;
    int32_t msg_id;
} gui_msg_sub_t;

typedef struct {
    int32_t msg_id;
    char is_subscribe;
    char is_unsubscribe;
} _gui_msg_status_t;

extern void gui_msg_init(lv_ui *ui);
extern void gui_msg_init_ui();
extern void gui_msg_init_events();
extern void gui_msg_unsubscribe();
extern gui_msg_status_t gui_msg_send(int32_t msg_id, void *value, int32_t len);
extern gui_msg_send_status_t gui_msg_get_send_status();
extern GUI_WEAKREF gui_msg_data_t *gui_msg_get(int32_t msg_id);
extern gui_msg_data_t *gui_msg_get_guider(int32_t msg_id);
extern GUI_WEAKREF void gui_msg_action_change(int32_t msg_id, gui_msg_action_t access, gui_msg_data_t *data, gui_msg_data_type_t type);
extern void gui_msg_action_change_guider(int32_t msg_id, gui_msg_action_t access, gui_msg_data_t *data, gui_msg_data_type_t type);
extern GUI_WEAKREF void gui_msg_subscribe_change(int32_t msg_id, gui_msg_subscribe_t sub_type);
extern void gui_msg_subscribe_change_guider(int32_t msg_id, gui_msg_subscribe_t sub_type);
extern lv_subject_t *gui_msg_get_subject(int32_t msg_id);
extern gui_msg_sub_t *gui_msg_get_sub(int32_t msg_id);
extern gui_msg_sub_t *gui_msg_create_sub(int32_t msg_id);
extern gui_msg_data_t *gui_msg_get_data();
extern bool gui_msg_has_observer(lv_subject_t *subject, lv_observer_cb_t cb, lv_obj_t *obj, void *user_data);
extern void gui_msg_setup_component(bool subscribe_enabled, bool event_enabled, lv_subject_t *subject, lv_obj_t *target_obj, gui_msg_data_t *msg_data, lv_observer_cb_t observer_cb, int32_t msg_id, gui_msg_action_t msg_action, gui_msg_data_type_t data_type, lv_event_cb_t event_cb);

extern void gui_msg_set_control_state_by_int32_cb(lv_observer_t *observer, lv_subject_t *subject);
extern void gui_msg_set_clear_flag_by_int32_cb(lv_observer_t *observer, lv_subject_t *subject);
extern void gui_msg_set_flag_by_int32_cb(lv_observer_t *observer, lv_subject_t *subject);
extern void gui_msg_set_label_text_by_string_cb(lv_observer_t *observer, lv_subject_t *subject);
extern void gui_msg_set_roller_roller_name_by_string_cb(lv_observer_t *observer, lv_subject_t *subject);
extern void gui_msg_set_visible_by_bool_cb(lv_observer_t *observer, lv_subject_t *subject);
extern void gui_msg_set_digital_clock_clock_time_by_time_cb(lv_observer_t *observer, lv_subject_t *subject);
extern void gui_msg_set_bar_bar_value_by_int32_cb(lv_observer_t *observer, lv_subject_t *subject);
#if LV_USE_OBSERVER
#include "./gui_model_msg.h"
#include "./gui_model_global_subpage_msg.h"
#include "./gui_model_main_msg.h"
#include "./gui_model_sys_setting_msg.h"
#include "./gui_model_update_msg.h"
#include "./gui_model_video_photo_msg.h"
#include "./gui_model_video_play_msg.h"
#include "./gui_model_video_rec_msg.h"
#include "./gui_sys_model_msg.h"
#define GUI_MSG_MAX_ID GUI_SYS_MODEL_MSG_ID_SYS_TIME
#endif

extern gui_msg_data_t guider_msg_data;

#ifdef __cplusplus
}
#endif
#endif /* GUI_MSG_H_ */

#endif
