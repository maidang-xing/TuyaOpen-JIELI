/*Generate Code, Do NOT Edit!*/
#include "./gui_msg.h"

gui_msg_data_t guider_msg_data = {0};
gui_msg_send_status_t gui_msg_send_status = GUI_MSG_SEND_DONE;
static lv_ll_t subs_ll;

void gui_msg_init(lv_ui *ui)
{
#if LV_USE_OBSERVER
    _lv_ll_init(&subs_ll, sizeof(gui_msg_sub_t));
    gui_player_msg_init(ui);
    gui_songs_msg_init(ui);
    gui_sys_model_msg_init(ui);
#endif
}
void gui_msg_init_ui()
{
#if LV_USE_OBSERVER
    gui_player_msg_init_ui();
    gui_songs_msg_init_ui();
    gui_sys_model_msg_init_ui();
#endif
}
void gui_msg_init_events()
{
#if LV_USE_OBSERVER
    gui_player_msg_init_events();
    gui_songs_msg_init_events();
    gui_sys_model_msg_init_events();
#endif
}
void gui_msg_unsubscribe()
{
#if LV_USE_OBSERVER
    gui_player_msg_unsubscribe();
    gui_songs_msg_unsubscribe();
    gui_sys_model_msg_unsubscribe();
#endif
}
gui_msg_status_t gui_msg_send(int32_t msg_id, void *value, int32_t len)
{
#if LV_USE_OBSERVER
    gui_msg_send_status = GUI_MSG_SENDING;
    gui_msg_status_t ret;
    switch (msg_id) {
    case GUI_PLAYER_MSG_ID_EQ_1:
    case GUI_PLAYER_MSG_ID_EQ_2:
    case GUI_PLAYER_MSG_ID_EQ_3:
    case GUI_PLAYER_MSG_ID_EQ_4:
    case GUI_PLAYER_MSG_ID_EQ_5:
    case GUI_PLAYER_MSG_ID_EQ_6:
    case GUI_PLAYER_MSG_ID_EQ_7:
    case GUI_PLAYER_MSG_ID_EQ_8:
    case GUI_PLAYER_MSG_ID_EQ_9:
    case GUI_PLAYER_MSG_ID_EQ_10:
    case GUI_PLAYER_MSG_ID_EQ_MODE:
    case GUI_PLAYER_MSG_ID_SAVE_MODE:
        ret = gui_player_msg_send(msg_id, value, len);
        gui_msg_send_status = GUI_MSG_SEND_DONE;
        return ret;

    case GUI_SONGS_MSG_ID_TOL_TIME:
    case GUI_SONGS_MSG_ID_CUR_TIME:
    case GUI_SONGS_MSG_ID_PLAYER_STATE:
    case GUI_SONGS_MSG_ID_MUSIC_STATE:
    case GUI_SONGS_MSG_ID_MUSIC_PROCESS:
    case GUI_SONGS_MSG_ID_MUSIC_NAME:
    case GUI_SONGS_MSG_ID_MUSIC_ARTIST:
    case GUI_SONGS_MSG_ID_MUSIC_ARTIST_AND_NAME:
    case GUI_SONGS_MSG_ID_PLAYER_VOLUME:
    case GUI_SONGS_MSG_ID_MUSIC_LYRICS:
    case GUI_SONGS_MSG_ID_LYRICS_SHOW:
    case GUI_SONGS_MSG_ID_ALBUM_PIC_SHOW:
        ret = gui_songs_msg_send(msg_id, value, len);
        gui_msg_send_status = GUI_MSG_SEND_DONE;
        return ret;

    case GUI_SYS_MODEL_MSG_ID_SYS_TIME:
        ret = gui_sys_model_msg_send(msg_id, value, len);
        gui_msg_send_status = GUI_MSG_SEND_DONE;
        return ret;

    default:
        break;
    }
    gui_msg_send_status = GUI_MSG_SEND_DONE;
    return GUI_MSG_STATUS_NO_FOUND_ID;
#else
    return GUI_MSG_STATUS_ERROR;
#endif
}
gui_msg_send_status_t gui_msg_get_send_status()
{
    return gui_msg_send_status;
}
GUI_WEAK gui_msg_data_t *gui_msg_get(int32_t msg_id)
{
    return gui_msg_get_guider(msg_id);
}
gui_msg_data_t *gui_msg_get_guider(int32_t msg_id)
{
#if LV_USE_OBSERVER
#if !LV_USE_GUIBUILDER_SIMULATOR
    if (msg_id >= GUI_MSG_ID_CUSTOM_START && msg_id <= GUI_MSG_ID_CUSTOM_END) {
        int32_t index = msg_id - GUI_MSG_ID_CUSTOM_START;
        gui_msg_entry_table[index].cb(GUI_MSG_ACCESS_GET, &guider_msg_data, gui_msg_entry_table[index].type);
        return &guider_msg_data;
    } else {
        for (int i = GUI_MSG_ID_CUSTOM_END - GUI_MSG_ID_CUSTOM_START + 1; i < sizeof(gui_msg_entry_table) / sizeof(gui_msg_entry_table[0]); i++) {
            if (msg_id == gui_msg_entry_table[i].msg_id) {
                gui_msg_entry_table[i].cb(GUI_MSG_ACCESS_GET, &guider_msg_data, gui_msg_entry_table[i].type);
                return &guider_msg_data;
            }
        }
    }
    return NULL;
#else
    if (msg_id >= GUI_PLAYER_MSG_ID_EQ_1 && msg_id <= GUI_PLAYER_MSG_ID_SAVE_MODE) {
        int32_t index = msg_id - GUI_PLAYER_MSG_ID_EQ_1;
        gui_player_msg_entry_table[index].cb(GUI_MSG_ACCESS_GET, &guider_msg_data, gui_player_msg_entry_table[index].type);
        return &guider_msg_data;
    } else if (msg_id >= GUI_SONGS_MSG_ID_TOL_TIME && msg_id <= GUI_SONGS_MSG_ID_ALBUM_PIC_SHOW) {
        int32_t index = msg_id - GUI_SONGS_MSG_ID_TOL_TIME;
        gui_songs_msg_entry_table[index].cb(GUI_MSG_ACCESS_GET, &guider_msg_data, gui_songs_msg_entry_table[index].type);
        return &guider_msg_data;
    } else {
        for (int i = 0; i < 1; i++) {
            if (msg_id == gui_sys_model_msg_entry_table[i].msg_id) {
                gui_sys_model_msg_entry_table[i].cb(GUI_MSG_ACCESS_GET, &guider_msg_data, gui_sys_model_msg_entry_table[i].type);
                return &guider_msg_data;
            }
        }
    }
    return NULL;
#endif
#endif
}
GUI_WEAK void gui_msg_action_change(int32_t msg_id, gui_msg_action_t access, gui_msg_data_t *data, gui_msg_data_type_t type)
{
    gui_msg_action_change_guider(msg_id, access, data, type);
}
void gui_msg_action_change_guider(int32_t msg_id, gui_msg_action_t access, gui_msg_data_t *data, gui_msg_data_type_t type)
{
#if LV_USE_OBSERVER
#if !LV_USE_GUIBUILDER_SIMULATOR
    if (msg_id >= GUI_MSG_ID_CUSTOM_START && msg_id <= GUI_MSG_ID_CUSTOM_END) {
        int32_t index = msg_id - GUI_MSG_ID_CUSTOM_START;
        gui_msg_entry_table[index].cb(access, data, type);
    } else {
        for (int i = GUI_MSG_ID_CUSTOM_END - GUI_MSG_ID_CUSTOM_START + 1; i < sizeof(gui_msg_entry_table) / sizeof(gui_msg_entry_table[0]); i++) {
            if (msg_id == gui_msg_entry_table[i].msg_id) {
                gui_msg_entry_table[i].cb(access, data, type);
                return;
            }
        }
    }
#else
    if (msg_id >= GUI_PLAYER_MSG_ID_EQ_1 && msg_id <= GUI_PLAYER_MSG_ID_SAVE_MODE) {
        int32_t index = msg_id - GUI_PLAYER_MSG_ID_EQ_1;
        gui_player_msg_entry_table[index].cb(access, data, type);
    } else if (msg_id >= GUI_SONGS_MSG_ID_TOL_TIME && msg_id <= GUI_SONGS_MSG_ID_ALBUM_PIC_SHOW) {
        int32_t index = msg_id - GUI_SONGS_MSG_ID_TOL_TIME;
        gui_songs_msg_entry_table[index].cb(access, data, type);
    } else {
        for (int i = 0; i < 1; i++) {
            if (msg_id == gui_sys_model_msg_entry_table[i].msg_id) {
                gui_sys_model_msg_entry_table[i].cb(access, data, type);
                return;
            }
        }
    }
#endif
#endif
}
GUI_WEAK void gui_msg_subscribe_change(int32_t msg_id, gui_msg_subscribe_t sub_type)
{
    gui_msg_subscribe_change_guider(msg_id, sub_type);
}
void gui_msg_subscribe_change_guider(int32_t msg_id, gui_msg_subscribe_t sub_type)
{
}
lv_subject_t *gui_msg_get_subject(int32_t msg_id)
{
    gui_msg_sub_t *sub = gui_msg_get_sub(msg_id);
    if (sub != NULL) {
        return sub->subject;
    }
    return NULL;
}
gui_msg_sub_t *gui_msg_get_sub(int32_t msg_id)
{
    gui_msg_sub_t *head = _lv_ll_get_head(&subs_ll);
    while (head != NULL) {
        if (head->msg_id == msg_id) {
            return head;
        }
        head = _lv_ll_get_next(&subs_ll, head);
    }
    return NULL;
}
gui_msg_sub_t *gui_msg_create_sub(int32_t msg_id)
{
    gui_msg_sub_t *sub = gui_msg_get_sub(msg_id);
    if (sub == NULL) {
        sub = _lv_ll_ins_tail(&subs_ll);
        sub->msg_id = msg_id;
        sub->subject = lv_mem_alloc(sizeof(lv_subject_t));
        if (sub->subject == NULL) {
            return NULL;
        }
    }
    return sub;
}
gui_msg_data_t *gui_msg_get_data()
{
    return &guider_msg_data;
}
char *gui_msg_get_name(int32_t msg_id)
{
    switch (msg_id) {
    case GUI_PLAYER_MSG_ID:
        return "PLAYER";
    case GUI_PLAYER_MSG_ID_EQ_1:
        return "PLAYER_EQ_1";
    case GUI_PLAYER_MSG_ID_EQ_2:
        return "PLAYER_EQ_2";
    case GUI_PLAYER_MSG_ID_EQ_3:
        return "PLAYER_EQ_3";
    case GUI_PLAYER_MSG_ID_EQ_4:
        return "PLAYER_EQ_4";
    case GUI_PLAYER_MSG_ID_EQ_5:
        return "PLAYER_EQ_5";
    case GUI_PLAYER_MSG_ID_EQ_6:
        return "PLAYER_EQ_6";
    case GUI_PLAYER_MSG_ID_EQ_7:
        return "PLAYER_EQ_7";
    case GUI_PLAYER_MSG_ID_EQ_8:
        return "PLAYER_EQ_8";
    case GUI_PLAYER_MSG_ID_EQ_9:
        return "PLAYER_EQ_9";
    case GUI_PLAYER_MSG_ID_EQ_10:
        return "PLAYER_EQ_10";
    case GUI_PLAYER_MSG_ID_EQ_MODE:
        return "PLAYER_EQ_MODE";
    case GUI_PLAYER_MSG_ID_SAVE_MODE:
        return "PLAYER_SAVE_MODE";

    case GUI_SONGS_MSG_ID:
        return "SONGS";
    case GUI_SONGS_MSG_ID_TOL_TIME:
        return "SONGS_TOL_TIME";
    case GUI_SONGS_MSG_ID_CUR_TIME:
        return "SONGS_CUR_TIME";
    case GUI_SONGS_MSG_ID_PLAYER_STATE:
        return "SONGS_PLAYER_STATE";
    case GUI_SONGS_MSG_ID_MUSIC_STATE:
        return "SONGS_MUSIC_STATE";
    case GUI_SONGS_MSG_ID_MUSIC_PROCESS:
        return "SONGS_MUSIC_PROCESS";
    case GUI_SONGS_MSG_ID_MUSIC_NAME:
        return "SONGS_MUSIC_NAME";
    case GUI_SONGS_MSG_ID_MUSIC_ARTIST:
        return "SONGS_MUSIC_ARTIST";
    case GUI_SONGS_MSG_ID_MUSIC_ARTIST_AND_NAME:
        return "SONGS_MUSIC_ARTIST_AND_NAME";
    case GUI_SONGS_MSG_ID_PLAYER_VOLUME:
        return "SONGS_PLAYER_VOLUME";
    case GUI_SONGS_MSG_ID_MUSIC_LYRICS:
        return "SONGS_MUSIC_LYRICS";
    case GUI_SONGS_MSG_ID_LYRICS_SHOW:
        return "SONGS_LYRICS_SHOW";
    case GUI_SONGS_MSG_ID_ALBUM_PIC_SHOW:
        return "SONGS_ALBUM_PIC_SHOW";

    case GUI_SYS_MODEL_MSG_ID:
        return "SYS_MODEL";
    case GUI_SYS_MODEL_MSG_ID_SYS_TIME:
        return "SYS_MODEL_SYS_TIME";

    default:
        break;
    }
    return NULL;
}
gui_msg_data_type_t gui_msg_get_data_type(int32_t msg_id)
{
#if !LV_USE_GUIBUILDER_SIMULATOR
    if (msg_id >= GUI_MSG_ID_CUSTOM_START && msg_id <= GUI_MSG_ID_CUSTOM_END) {
        return gui_msg_entry_table[msg_id - GUI_MSG_ID_CUSTOM_START].type;
    } else {
        for (int i = GUI_MSG_ID_CUSTOM_END - GUI_MSG_ID_CUSTOM_START + 1; i < sizeof(gui_msg_entry_table) / sizeof(gui_msg_entry_table[0]); i++) {
            if (msg_id == gui_msg_entry_table[i].msg_id) {
                return gui_msg_entry_table[i].type;
            }
        }
    }
    return VALUE_UNKNOWN;
#else
    if (msg_id >= GUI_PLAYER_MSG_ID_EQ_1 && msg_id <= GUI_PLAYER_MSG_ID_SAVE_MODE) {
        return gui_player_msg_entry_table[msg_id - GUI_PLAYER_MSG_ID_EQ_1].type;
    } else if (msg_id >= GUI_SONGS_MSG_ID_TOL_TIME && msg_id <= GUI_SONGS_MSG_ID_ALBUM_PIC_SHOW) {
        return gui_songs_msg_entry_table[msg_id - GUI_SONGS_MSG_ID_TOL_TIME].type;
    } else {
        for (int i = 0; i < 1; i++) {
            if (msg_id == gui_sys_model_msg_entry_table[i].msg_id) {
                return gui_sys_model_msg_entry_table[i].type;
            }
        }
    }
    return VALUE_UNKNOWN;
#endif
}
gui_msg_array_type_t gui_msg_get_data_array_type(int32_t msg_id)
{
    switch (msg_id) {
    default:
        return GUI_MSG_ARRAY_TYPE_INVALID;
    }
}
bool gui_msg_has_observer(lv_subject_t *subject, lv_observer_cb_t cb, lv_obj_t *obj, void *user_data)
{
    if (subject == NULL || subject->type == LV_SUBJECT_TYPE_INVALID) {
        return false;
    }
    lv_observer_t *observer = _lv_ll_get_head(&(subject->subs_ll));
    while (observer != NULL) {
        if (observer->cb == cb && observer->target == obj && observer->user_data == user_data) {
            return true;
        }
        observer = _lv_ll_get_next(&(subject->subs_ll), observer);
    }
    return false;
}
void gui_msg_setup_component(bool subscribe_enabled, bool event_enabled, lv_subject_t *subject, lv_obj_t *target_obj, gui_msg_data_t *msg_data, lv_observer_cb_t observer_cb, int32_t msg_id, gui_msg_action_t msg_action, gui_msg_data_type_t data_type, lv_event_cb_t event_cb)
{
    if (subject == NULL || subject->type == LV_SUBJECT_TYPE_INVALID) {
        return;
    }

    if (subscribe_enabled) {
        if (!gui_msg_has_observer(subject, observer_cb, target_obj, msg_data)) {
            gui_msg_action_change(msg_id, msg_action, msg_data, data_type);
            lv_subject_add_observer_obj(subject, observer_cb, target_obj, msg_data);
        }
    }

    if (event_enabled) {
        lv_obj_remove_event_cb(target_obj, event_cb);
        lv_obj_add_event_cb(target_obj, event_cb, LV_EVENT_VALUE_CHANGED, (void *)msg_id);
    }
}

void gui_msg_set_control_state_by_int32_cb(lv_observer_t *observer, lv_subject_t *subject)
{
    lv_obj_t *obj = lv_observer_get_target_obj(observer);
    if (obj == NULL || lv_obj_is_valid(obj) == false) {
        return;
    }

    gui_msg_data_t *data = (gui_msg_data_t *)observer->user_data;
    lv_obj_clear_state(obj, LV_STATE_ANY);
    lv_obj_add_state(obj, data->value_int);
}
void gui_msg_set_slider_starting_value_by_int32_cb(lv_observer_t *observer, lv_subject_t *subject)
{
    lv_obj_t *obj = lv_observer_get_target_obj(observer);
    if (obj == NULL || lv_obj_is_valid(obj) == false) {
        return;
    }

    gui_msg_data_t *data = (gui_msg_data_t *)observer->user_data;
    lv_slider_set_value(obj, data->value_int, LV_ANIM_OFF);
}
void gui_msg_change_slider_starting_value_cb(lv_event_t *e)
{
    lv_obj_t *obj = lv_event_get_target(e);
    if (obj == NULL || lv_obj_is_valid(obj) == false) {
        return;
    }

    int32_t msg_id = (int32_t)lv_event_get_user_data(e);
    int32_t var = lv_slider_get_value(obj);
    gui_msg_send(msg_id, (void *)var, 1);
}
void gui_msg_set_label_text_by_string_cb(lv_observer_t *observer, lv_subject_t *subject)
{
    lv_obj_t *obj = lv_observer_get_target_obj(observer);
    if (obj == NULL || lv_obj_is_valid(obj) == false) {
        return;
    }

    gui_msg_data_t *data = (gui_msg_data_t *)observer->user_data;
    lv_label_set_text(obj, data->value_string);
}
void gui_msg_set_visible_by_bool_cb(lv_observer_t *observer, lv_subject_t *subject)
{
    lv_obj_t *obj = lv_observer_get_target_obj(observer);
    if (obj == NULL || lv_obj_is_valid(obj) == false) {
        return;
    }

    gui_msg_data_t *data = (gui_msg_data_t *)observer->user_data;
    if (data->value_bool) {
        lv_obj_clear_flag(obj, LV_OBJ_FLAG_HIDDEN);
    } else {
        lv_obj_add_flag(obj, LV_OBJ_FLAG_HIDDEN);
    }
}
void _gui_msg_int32_cb(int32_t *var_ptr, gui_msg_action_t access, gui_msg_data_t *data)
{
    if (access == GUI_MSG_ACCESS_SET) {
        *var_ptr = data->value_int;
    }
    data->value_int = *var_ptr;
    return;
}
void _gui_msg_state_cb(lv_state_t *var_ptr, gui_msg_action_t access, gui_msg_data_t *data)
{
    if (access == GUI_MSG_ACCESS_SET) {
        *var_ptr = (lv_state_t)data->value_int;
    }
    data->value_int = (int32_t) * var_ptr;
    return;
}
void _gui_msg_char_array_cb(char **var_ptr, const char *init_value, bool *is_init, gui_msg_action_t access, gui_msg_data_t *data)
{
    if (*is_init == false) {
        *var_ptr = lv_mem_alloc(strlen(init_value) + 1);
        if (*var_ptr == NULL) {
            return;
        }
        strcpy(*var_ptr, init_value);
        *is_init = true;
    }
    if (access == GUI_MSG_ACCESS_SET) {
        lv_mem_free(*var_ptr);
        *var_ptr = lv_mem_alloc(strlen(data->value_string) + 1);
        if (*var_ptr == NULL) {
            return;
        }
        strcpy(*var_ptr, data->value_string);
    }
    data->value_string = *var_ptr;
    return;
}
void _gui_msg_bool_cb(bool *var_ptr, gui_msg_action_t access, gui_msg_data_t *data)
{
    if (access == GUI_MSG_ACCESS_SET) {
        *var_ptr = data->value_bool;
    }
    data->value_bool = *var_ptr;
    return;
}
void _gui_msg_tm_cb(struct tm *var_ptr, bool is_systime, gui_msg_action_t access, gui_msg_data_t *data)
{
    if (access == GUI_MSG_ACCESS_SET) {
        *var_ptr = data->value_time;
    } else {
        if (is_systime) {
            time_t now = time(NULL);
            struct tm *tm = localtime(&now);
            if (tm != NULL) {
                *var_ptr = *tm;
            }
        }
    }
    data->value_time = *var_ptr;
    return;
}
