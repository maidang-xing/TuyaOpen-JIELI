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
    GUI_PLAYER_MSG_ID = 1,
    GUI_SONGS_MSG_ID,
    GUI_SYS_MODEL_MSG_ID = 0xF000,
} gui_msg_id_t;

enum {
    GUI_MSG_ID_CUSTOM_START = 0x3,

    GUI_PLAYER_MSG_ID_EQ_1 = 0x3,
    GUI_PLAYER_MSG_ID_EQ_2 = 0x4,
    GUI_PLAYER_MSG_ID_EQ_3 = 0x5,
    GUI_PLAYER_MSG_ID_EQ_4 = 0x6,
    GUI_PLAYER_MSG_ID_EQ_5 = 0x7,
    GUI_PLAYER_MSG_ID_EQ_6 = 0x8,
    GUI_PLAYER_MSG_ID_EQ_7 = 0x9,
    GUI_PLAYER_MSG_ID_EQ_8 = 0xa,
    GUI_PLAYER_MSG_ID_EQ_9 = 0xb,
    GUI_PLAYER_MSG_ID_EQ_10 = 0xc,
    GUI_PLAYER_MSG_ID_EQ_MODE = 0xd,
    GUI_PLAYER_MSG_ID_SAVE_MODE = 0xe,

    GUI_SONGS_MSG_ID_TOL_TIME = 0xf,
    GUI_SONGS_MSG_ID_CUR_TIME = 0x10,
    GUI_SONGS_MSG_ID_PLAYER_STATE = 0x11,
    GUI_SONGS_MSG_ID_MUSIC_STATE = 0x12,
    GUI_SONGS_MSG_ID_MUSIC_PROCESS = 0x13,
    GUI_SONGS_MSG_ID_MUSIC_NAME = 0x14,
    GUI_SONGS_MSG_ID_MUSIC_ARTIST = 0x15,
    GUI_SONGS_MSG_ID_MUSIC_ARTIST_AND_NAME = 0x16,
    GUI_SONGS_MSG_ID_PLAYER_VOLUME = 0x17,
    GUI_SONGS_MSG_ID_MUSIC_LYRICS = 0x18,
    GUI_SONGS_MSG_ID_LYRICS_SHOW = 0x19,
    GUI_SONGS_MSG_ID_ALBUM_PIC_SHOW = 0x1a,

    GUI_SYS_MODEL_MSG_ID_SYS_TIME = 0xF001,

    GUI_MSG_ID_CUSTOM_END = 0x1a
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

extern void gui_msg_set_control_state_by_int32_cb(lv_observer_t *observer, lv_subject_t *subject);
extern void gui_msg_set_slider_starting_value_by_int32_cb(lv_observer_t *observer, lv_subject_t *subject);
extern void gui_msg_change_slider_starting_value_cb(lv_event_t *e);
extern void gui_msg_set_label_text_by_string_cb(lv_observer_t *observer, lv_subject_t *subject);
extern void gui_msg_set_visible_by_bool_cb(lv_observer_t *observer, lv_subject_t *subject);
extern void _gui_msg_int32_cb(int32_t *var_ptr, gui_msg_action_t access, gui_msg_data_t *data);
extern void _gui_msg_state_cb(lv_state_t *var_ptr, gui_msg_action_t access, gui_msg_data_t *data);
extern void _gui_msg_char_array_cb(char **var_ptr, const char *init_value, bool *is_init, gui_msg_action_t access, gui_msg_data_t *data);
extern void _gui_msg_bool_cb(bool *var_ptr, gui_msg_action_t access, gui_msg_data_t *data);
extern void _gui_msg_tm_cb(struct tm *var_ptr, bool is_systime, gui_msg_action_t access, gui_msg_data_t *data);
#if LV_USE_OBSERVER
#include "./gui_player_msg.h"
#include "./gui_songs_msg.h"
#include "./gui_sys_model_msg.h"
#define GUI_MSG_MAX_ID 0xf001

extern int gui_player_msg_eq_1_cb(gui_msg_action_t access, gui_msg_data_t *data, gui_msg_data_type_t type);
extern int gui_player_msg_eq_2_cb(gui_msg_action_t access, gui_msg_data_t *data, gui_msg_data_type_t type);
extern int gui_player_msg_eq_3_cb(gui_msg_action_t access, gui_msg_data_t *data, gui_msg_data_type_t type);
extern int gui_player_msg_eq_4_cb(gui_msg_action_t access, gui_msg_data_t *data, gui_msg_data_type_t type);
extern int gui_player_msg_eq_5_cb(gui_msg_action_t access, gui_msg_data_t *data, gui_msg_data_type_t type);
extern int gui_player_msg_eq_6_cb(gui_msg_action_t access, gui_msg_data_t *data, gui_msg_data_type_t type);
extern int gui_player_msg_eq_7_cb(gui_msg_action_t access, gui_msg_data_t *data, gui_msg_data_type_t type);
extern int gui_player_msg_eq_8_cb(gui_msg_action_t access, gui_msg_data_t *data, gui_msg_data_type_t type);
extern int gui_player_msg_eq_9_cb(gui_msg_action_t access, gui_msg_data_t *data, gui_msg_data_type_t type);
extern int gui_player_msg_eq_10_cb(gui_msg_action_t access, gui_msg_data_t *data, gui_msg_data_type_t type);
extern int gui_player_msg_eq_mode_cb(gui_msg_action_t access, gui_msg_data_t *data, gui_msg_data_type_t type);
extern int gui_player_msg_save_mode_cb(gui_msg_action_t access, gui_msg_data_t *data, gui_msg_data_type_t type);

extern int gui_songs_msg_tol_time_cb(gui_msg_action_t access, gui_msg_data_t *data, gui_msg_data_type_t type);
extern int gui_songs_msg_cur_time_cb(gui_msg_action_t access, gui_msg_data_t *data, gui_msg_data_type_t type);
extern int gui_songs_msg_player_state_cb(gui_msg_action_t access, gui_msg_data_t *data, gui_msg_data_type_t type);
extern int gui_songs_msg_music_state_cb(gui_msg_action_t access, gui_msg_data_t *data, gui_msg_data_type_t type);
extern int gui_songs_msg_music_process_cb(gui_msg_action_t access, gui_msg_data_t *data, gui_msg_data_type_t type);
extern int gui_songs_msg_music_name_cb(gui_msg_action_t access, gui_msg_data_t *data, gui_msg_data_type_t type);
extern int gui_songs_msg_music_artist_cb(gui_msg_action_t access, gui_msg_data_t *data, gui_msg_data_type_t type);
extern int gui_songs_msg_music_artist_and_name_cb(gui_msg_action_t access, gui_msg_data_t *data, gui_msg_data_type_t type);
extern int gui_songs_msg_player_volume_cb(gui_msg_action_t access, gui_msg_data_t *data, gui_msg_data_type_t type);
extern int gui_songs_msg_music_lyrics_cb(gui_msg_action_t access, gui_msg_data_t *data, gui_msg_data_type_t type);
extern int gui_songs_msg_lyrics_show_cb(gui_msg_action_t access, gui_msg_data_t *data, gui_msg_data_type_t type);
extern int gui_songs_msg_album_pic_show_cb(gui_msg_action_t access, gui_msg_data_t *data, gui_msg_data_type_t type);

extern int gui_sys_model_msg_sys_time_cb(gui_msg_action_t access, gui_msg_data_t *data, gui_msg_data_type_t type);

#if !LV_USE_GUIBUILDER_SIMULATOR
static const _gui_msg_entry_t gui_msg_entry_table[] = {
    { GUI_PLAYER_MSG_ID_EQ_1, gui_player_msg_eq_1_cb, VALUE_INT },
    { GUI_PLAYER_MSG_ID_EQ_2, gui_player_msg_eq_2_cb, VALUE_INT },
    { GUI_PLAYER_MSG_ID_EQ_3, gui_player_msg_eq_3_cb, VALUE_INT },
    { GUI_PLAYER_MSG_ID_EQ_4, gui_player_msg_eq_4_cb, VALUE_INT },
    { GUI_PLAYER_MSG_ID_EQ_5, gui_player_msg_eq_5_cb, VALUE_INT },
    { GUI_PLAYER_MSG_ID_EQ_6, gui_player_msg_eq_6_cb, VALUE_INT },
    { GUI_PLAYER_MSG_ID_EQ_7, gui_player_msg_eq_7_cb, VALUE_INT },
    { GUI_PLAYER_MSG_ID_EQ_8, gui_player_msg_eq_8_cb, VALUE_INT },
    { GUI_PLAYER_MSG_ID_EQ_9, gui_player_msg_eq_9_cb, VALUE_INT },
    { GUI_PLAYER_MSG_ID_EQ_10, gui_player_msg_eq_10_cb, VALUE_INT },
    { GUI_PLAYER_MSG_ID_EQ_MODE, gui_player_msg_eq_mode_cb, VALUE_INT },
    { GUI_PLAYER_MSG_ID_SAVE_MODE, gui_player_msg_save_mode_cb, VALUE_INT },

    { GUI_SONGS_MSG_ID_TOL_TIME, gui_songs_msg_tol_time_cb, VALUE_STRING },
    { GUI_SONGS_MSG_ID_CUR_TIME, gui_songs_msg_cur_time_cb, VALUE_STRING },
    { GUI_SONGS_MSG_ID_PLAYER_STATE, gui_songs_msg_player_state_cb, VALUE_INT },
    { GUI_SONGS_MSG_ID_MUSIC_STATE, gui_songs_msg_music_state_cb, VALUE_INT },
    { GUI_SONGS_MSG_ID_MUSIC_PROCESS, gui_songs_msg_music_process_cb, VALUE_INT },
    { GUI_SONGS_MSG_ID_MUSIC_NAME, gui_songs_msg_music_name_cb, VALUE_STRING },
    { GUI_SONGS_MSG_ID_MUSIC_ARTIST, gui_songs_msg_music_artist_cb, VALUE_STRING },
    { GUI_SONGS_MSG_ID_MUSIC_ARTIST_AND_NAME, gui_songs_msg_music_artist_and_name_cb, VALUE_STRING },
    { GUI_SONGS_MSG_ID_PLAYER_VOLUME, gui_songs_msg_player_volume_cb, VALUE_INT },
    { GUI_SONGS_MSG_ID_MUSIC_LYRICS, gui_songs_msg_music_lyrics_cb, VALUE_STRING },
    { GUI_SONGS_MSG_ID_LYRICS_SHOW, gui_songs_msg_lyrics_show_cb, VALUE_BOOL },
    { GUI_SONGS_MSG_ID_ALBUM_PIC_SHOW, gui_songs_msg_album_pic_show_cb, VALUE_BOOL },

    { GUI_SYS_MODEL_MSG_ID_SYS_TIME, gui_sys_model_msg_sys_time_cb, VALUE_TIME },
};
#endif

#endif

extern gui_msg_data_t guider_msg_data;

#ifdef __cplusplus
}
#endif
#endif /* GUI_MSG_H_ */
