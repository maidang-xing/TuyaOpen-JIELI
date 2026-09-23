/*Generate Code, Do NOT Edit!*/
#include "./gui_songs_msg.h"

#if LV_USE_OBSERVER

static lv_ll_t subs_ll;

#if LV_USE_GUIBUILDER_SIMULATOR
_gui_msg_entry_t gui_songs_msg_entry_table[] = {
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
};
#endif


GUI_WEAK int gui_songs_msg_tol_time_cb(gui_msg_action_t access, gui_msg_data_t *data, gui_msg_data_type_t type)
{
    char tol_time_init_var[] = "03:54";
    static bool tol_time_is_init = false;
    static char *tol_time_var = NULL;
    _gui_msg_char_array_cb(&tol_time_var, tol_time_init_var, &tol_time_is_init, access, data);
    return 0;
}
GUI_WEAK int gui_songs_msg_cur_time_cb(gui_msg_action_t access, gui_msg_data_t *data, gui_msg_data_type_t type)
{
    char cur_time_init_var[] = "00:00";
    static bool cur_time_is_init = false;
    static char *cur_time_var = NULL;
    _gui_msg_char_array_cb(&cur_time_var, cur_time_init_var, &cur_time_is_init, access, data);
    return 0;
}
GUI_WEAK int gui_songs_msg_player_state_cb(gui_msg_action_t access, gui_msg_data_t *data, gui_msg_data_type_t type)
{
    static int32_t player_state_var = 1;
    _gui_msg_int32_cb(&player_state_var, access, data);
    return 0;
}
GUI_WEAK int gui_songs_msg_music_state_cb(gui_msg_action_t access, gui_msg_data_t *data, gui_msg_data_type_t type)
{
    static lv_state_t music_state_var = LV_STATE_DEFAULT;
    _gui_msg_state_cb(&music_state_var, access, data);
    return 0;
}
GUI_WEAK int gui_songs_msg_music_process_cb(gui_msg_action_t access, gui_msg_data_t *data, gui_msg_data_type_t type)
{
    static int32_t music_process_var = 0;
    _gui_msg_int32_cb(&music_process_var, access, data);
    return 0;
}
GUI_WEAK int gui_songs_msg_music_name_cb(gui_msg_action_t access, gui_msg_data_t *data, gui_msg_data_type_t type)
{
    char music_name_init_var[] = "歌名";
    static bool music_name_is_init = false;
    static char *music_name_var = NULL;
    _gui_msg_char_array_cb(&music_name_var, music_name_init_var, &music_name_is_init, access, data);
    return 0;
}
GUI_WEAK int gui_songs_msg_music_artist_cb(gui_msg_action_t access, gui_msg_data_t *data, gui_msg_data_type_t type)
{
    char music_artist_init_var[] = "歌手";
    static bool music_artist_is_init = false;
    static char *music_artist_var = NULL;
    _gui_msg_char_array_cb(&music_artist_var, music_artist_init_var, &music_artist_is_init, access, data);
    return 0;
}
GUI_WEAK int gui_songs_msg_music_artist_and_name_cb(gui_msg_action_t access, gui_msg_data_t *data, gui_msg_data_type_t type)
{
    char music_artist_and_name_init_var[] = "歌手-歌名";
    static bool music_artist_and_name_is_init = false;
    static char *music_artist_and_name_var = NULL;
    _gui_msg_char_array_cb(&music_artist_and_name_var, music_artist_and_name_init_var, &music_artist_and_name_is_init, access, data);
    return 0;
}
GUI_WEAK int gui_songs_msg_player_volume_cb(gui_msg_action_t access, gui_msg_data_t *data, gui_msg_data_type_t type)
{
    static int32_t player_volume_var = 50;
    _gui_msg_int32_cb(&player_volume_var, access, data);
    return 0;
}
GUI_WEAK int gui_songs_msg_music_lyrics_cb(gui_msg_action_t access, gui_msg_data_t *data, gui_msg_data_type_t type)
{
    char music_lyrics_init_var[] = "歌词";
    static bool music_lyrics_is_init = false;
    static char *music_lyrics_var = NULL;
    _gui_msg_char_array_cb(&music_lyrics_var, music_lyrics_init_var, &music_lyrics_is_init, access, data);
    return 0;
}
GUI_WEAK int gui_songs_msg_lyrics_show_cb(gui_msg_action_t access, gui_msg_data_t *data, gui_msg_data_type_t type)
{
    static bool lyrics_show_var = false;
    _gui_msg_bool_cb(&lyrics_show_var, access, data);
    return 0;
}
GUI_WEAK int gui_songs_msg_album_pic_show_cb(gui_msg_action_t access, gui_msg_data_t *data, gui_msg_data_type_t type)
{
    static bool album_pic_show_var = true;
    _gui_msg_bool_cb(&album_pic_show_var, access, data);
    return 0;
}

void gui_songs_msg_init(lv_ui *ui)
{
    int32_t ids[12] = {
        GUI_SONGS_MSG_ID_TOL_TIME,
        GUI_SONGS_MSG_ID_CUR_TIME,
        GUI_SONGS_MSG_ID_PLAYER_STATE,
        GUI_SONGS_MSG_ID_MUSIC_STATE,
        GUI_SONGS_MSG_ID_MUSIC_PROCESS,
        GUI_SONGS_MSG_ID_MUSIC_NAME,
        GUI_SONGS_MSG_ID_MUSIC_ARTIST,
        GUI_SONGS_MSG_ID_MUSIC_ARTIST_AND_NAME,
        GUI_SONGS_MSG_ID_PLAYER_VOLUME,
        GUI_SONGS_MSG_ID_MUSIC_LYRICS,
        GUI_SONGS_MSG_ID_LYRICS_SHOW,
        GUI_SONGS_MSG_ID_ALBUM_PIC_SHOW,
    };
    for (int i = 0; i < 12; i++) {
        gui_msg_sub_t *sub = gui_msg_create_sub(ids[i]);
        if (sub != NULL) {
            lv_subject_init_pointer(sub->subject, &guider_msg_data);
        }
    }
}

void gui_songs_msg_init_ui()
{
}

void gui_songs_msg_init_events()
{
    void *res = NULL;
    _gui_msg_status_t status[12] = {
        {GUI_SONGS_MSG_ID_TOL_TIME, 0, 0},
        {GUI_SONGS_MSG_ID_CUR_TIME, 0, 0},
        {GUI_SONGS_MSG_ID_PLAYER_STATE, 0, 0},
        {GUI_SONGS_MSG_ID_MUSIC_STATE, 0, 0},
        {GUI_SONGS_MSG_ID_MUSIC_PROCESS, 0, 0},
        {GUI_SONGS_MSG_ID_MUSIC_NAME, 0, 0},
        {GUI_SONGS_MSG_ID_MUSIC_ARTIST, 0, 0},
        {GUI_SONGS_MSG_ID_MUSIC_ARTIST_AND_NAME, 0, 0},
        {GUI_SONGS_MSG_ID_PLAYER_VOLUME, 0, 0},
        {GUI_SONGS_MSG_ID_MUSIC_LYRICS, 0, 0},
        {GUI_SONGS_MSG_ID_LYRICS_SHOW, 0, 0},
        {GUI_SONGS_MSG_ID_ALBUM_PIC_SHOW, 0, 0},
    };

    for (int i = 0; i < 12; i++) {
        lv_subject_t *subject = gui_msg_get_subject(status[i].msg_id);
        if (subject == NULL) {
            continue;
        }
        lv_ll_t subject_ll = subject->subs_ll;
        gui_msg_sub_t *head = _lv_ll_get_head(&subject_ll);
        if (head != NULL) {
            status[i].is_unsubscribe = 1;
        }
    }

    lv_subject_t *subject_music_state = gui_msg_get_subject(GUI_SONGS_MSG_ID_MUSIC_STATE);
    lv_subject_t *subject_music_process = gui_msg_get_subject(GUI_SONGS_MSG_ID_MUSIC_PROCESS);
    lv_subject_t *subject_cur_time = gui_msg_get_subject(GUI_SONGS_MSG_ID_CUR_TIME);
    lv_subject_t *subject_tol_time = gui_msg_get_subject(GUI_SONGS_MSG_ID_TOL_TIME);
    lv_subject_t *subject_lyrics_show = gui_msg_get_subject(GUI_SONGS_MSG_ID_LYRICS_SHOW);
    lv_subject_t *subject_album_pic_show = gui_msg_get_subject(GUI_SONGS_MSG_ID_ALBUM_PIC_SHOW);
    lv_subject_t *subject_player_volume = gui_msg_get_subject(GUI_SONGS_MSG_ID_PLAYER_VOLUME);
    if (guider_ui.music_player) {
        lv_ui_music_player *ui_scr = ui_get_scr_ptr(&guider_ui, GUI_SCREEN_MUSIC_PLAYER);
        gui_msg_setup_component(true, false, subject_music_state, ui_scr->music_player_imgbtn_1, &guider_msg_data, gui_msg_set_control_state_by_int32_cb, GUI_SONGS_MSG_ID_MUSIC_STATE, GUI_MSG_ACCESS_GET, VALUE_INT, NULL);

        gui_msg_setup_component(true, true, subject_music_process, ui_scr->music_player_slider_1, &guider_msg_data, gui_msg_set_slider_starting_value_by_int32_cb, GUI_SONGS_MSG_ID_MUSIC_PROCESS, GUI_MSG_ACCESS_GET, VALUE_INT, gui_msg_change_slider_starting_value_cb);

        gui_msg_setup_component(true, false, subject_cur_time, ui_scr->music_player_lbl_2, &guider_msg_data, gui_msg_set_label_text_by_string_cb, GUI_SONGS_MSG_ID_CUR_TIME, GUI_MSG_ACCESS_GET, VALUE_STRING, NULL);

        gui_msg_setup_component(true, false, subject_tol_time, ui_scr->music_player_lbl_3, &guider_msg_data, gui_msg_set_label_text_by_string_cb, GUI_SONGS_MSG_ID_TOL_TIME, GUI_MSG_ACCESS_GET, VALUE_STRING, NULL);

        gui_msg_setup_component(true, false, subject_lyrics_show, ui_scr->music_player_view_lyrics, &guider_msg_data, gui_msg_set_visible_by_bool_cb, GUI_SONGS_MSG_ID_LYRICS_SHOW, GUI_MSG_ACCESS_GET, VALUE_BOOL, NULL);

        gui_msg_setup_component(true, false, subject_album_pic_show, ui_scr->music_player_view_1, &guider_msg_data, gui_msg_set_visible_by_bool_cb, GUI_SONGS_MSG_ID_ALBUM_PIC_SHOW, GUI_MSG_ACCESS_GET, VALUE_BOOL, NULL);


        for (int i = 0; i < 12; i++) {
            if (status[i].msg_id == GUI_SONGS_MSG_ID_MUSIC_STATE) {
                status[i].is_subscribe = 1;
            }
            if (status[i].msg_id == GUI_SONGS_MSG_ID_MUSIC_PROCESS) {
                status[i].is_subscribe = 1;
            }
            if (status[i].msg_id == GUI_SONGS_MSG_ID_CUR_TIME) {
                status[i].is_subscribe = 1;
            }
            if (status[i].msg_id == GUI_SONGS_MSG_ID_TOL_TIME) {
                status[i].is_subscribe = 1;
            }
            if (status[i].msg_id == GUI_SONGS_MSG_ID_LYRICS_SHOW) {
                status[i].is_subscribe = 1;
            }
            if (status[i].msg_id == GUI_SONGS_MSG_ID_ALBUM_PIC_SHOW) {
                status[i].is_subscribe = 1;
            }
        }
    }
    if (guider_ui.sys_menu) {
        lv_ui_sys_menu *ui_scr = ui_get_scr_ptr(&guider_ui, GUI_SCREEN_SYS_MENU);
        gui_msg_setup_component(true, true, subject_player_volume, ui_scr->sys_menu_slider_1, &guider_msg_data, gui_msg_set_slider_starting_value_by_int32_cb, GUI_SONGS_MSG_ID_PLAYER_VOLUME, GUI_MSG_ACCESS_GET, VALUE_INT, gui_msg_change_slider_starting_value_cb);

        gui_msg_setup_component(true, false, subject_music_state, ui_scr->sys_menu_imgbtn_4, &guider_msg_data, gui_msg_set_control_state_by_int32_cb, GUI_SONGS_MSG_ID_MUSIC_STATE, GUI_MSG_ACCESS_GET, VALUE_INT, NULL);


        for (int i = 0; i < 12; i++) {
            if (status[i].msg_id == GUI_SONGS_MSG_ID_PLAYER_VOLUME) {
                status[i].is_subscribe = 1;
            }
            if (status[i].msg_id == GUI_SONGS_MSG_ID_MUSIC_STATE) {
                status[i].is_subscribe = 1;
            }
        }
    }

    for (int i = 0; i < 12; i++) {
        if (status[i].is_subscribe == 0 && status[i].is_unsubscribe == 1) {
            gui_msg_subscribe_change(status[i].msg_id, GUI_MSG_UNSUBSCRIBE);
        } else if (status[i].is_subscribe == 1 && status[i].is_unsubscribe == 0) {
            gui_msg_subscribe_change(status[i].msg_id, GUI_MSG_SUBSCRIBE);
        }
    }
}

void gui_songs_msg_unsubscribe()
{
    _gui_msg_status_t status[12] = {
        {GUI_SONGS_MSG_ID_TOL_TIME, 0, 0},
        {GUI_SONGS_MSG_ID_CUR_TIME, 0, 0},
        {GUI_SONGS_MSG_ID_PLAYER_STATE, 0, 0},
        {GUI_SONGS_MSG_ID_MUSIC_STATE, 0, 0},
        {GUI_SONGS_MSG_ID_MUSIC_PROCESS, 0, 0},
        {GUI_SONGS_MSG_ID_MUSIC_NAME, 0, 0},
        {GUI_SONGS_MSG_ID_MUSIC_ARTIST, 0, 0},
        {GUI_SONGS_MSG_ID_MUSIC_ARTIST_AND_NAME, 0, 0},
        {GUI_SONGS_MSG_ID_PLAYER_VOLUME, 0, 0},
        {GUI_SONGS_MSG_ID_MUSIC_LYRICS, 0, 0},
        {GUI_SONGS_MSG_ID_LYRICS_SHOW, 0, 0},
        {GUI_SONGS_MSG_ID_ALBUM_PIC_SHOW, 0, 0},
    };
    for (int i = 0; i < 12; i++) {
        lv_subject_t *subject = gui_msg_get_subject(status[i].msg_id);
        if (subject == NULL) {
            continue;
        }
        lv_ll_t subject_ll = subject->subs_ll;
        lv_observer_t *head = _lv_ll_get_head(&subject_ll);
        if (head != NULL) {
            status[i].is_unsubscribe = 1;
        }
        while (head != NULL) {
            lv_obj_t *obj = head->target;
            if (obj != NULL && lv_obj_is_valid(obj) == true) {
                lv_subject_remove_all_obj(subject, obj);
            }
            head = _lv_ll_get_head(&subject_ll);
        }
    }

    for (int i = 0; i < 12; i++) {
        if (status[i].is_unsubscribe == 1) {
            gui_msg_subscribe_change(status[i].msg_id, GUI_MSG_UNSUBSCRIBE);
        }
    }
}

gui_msg_status_t gui_songs_msg_send(int32_t msg_id, void *value, int32_t len)
{
    if (msg_id == GUI_SONGS_MSG_ID) {
    } else {
        gui_msg_data_type_t data_type = VALUE_INT;
        switch (msg_id) {
        case GUI_SONGS_MSG_ID_MUSIC_STATE: {
            data_type = VALUE_INT;
            guider_msg_data.value_array.ptr = value;
            guider_msg_data.value_array.len = len;
        }
        break;
        case GUI_SONGS_MSG_ID_LYRICS_SHOW:
        case GUI_SONGS_MSG_ID_ALBUM_PIC_SHOW: {
            data_type = VALUE_BOOL;
            guider_msg_data.value_array.ptr = value;
            guider_msg_data.value_array.len = len;
        }
        break;
        case GUI_SONGS_MSG_ID_TOL_TIME:
        case GUI_SONGS_MSG_ID_CUR_TIME:
        case GUI_SONGS_MSG_ID_MUSIC_NAME:
        case GUI_SONGS_MSG_ID_MUSIC_ARTIST:
        case GUI_SONGS_MSG_ID_MUSIC_ARTIST_AND_NAME:
        case GUI_SONGS_MSG_ID_MUSIC_LYRICS: {
            data_type = VALUE_STRING;
            guider_msg_data.value_array.ptr = value;
            guider_msg_data.value_array.len = len;
        }
        break;
        case GUI_SONGS_MSG_ID_PLAYER_STATE:
        case GUI_SONGS_MSG_ID_MUSIC_PROCESS:
        case GUI_SONGS_MSG_ID_PLAYER_VOLUME: {
            data_type = VALUE_INT;
            guider_msg_data.value_array.ptr = value;
            guider_msg_data.value_array.len = len;
        }
        break;
        default:
            break;
        }
        gui_msg_action_change(msg_id, GUI_MSG_ACCESS_SET, &guider_msg_data, data_type);
        lv_subject_t *subject = gui_msg_get_subject(msg_id);
        if (subject == NULL) {
            return GUI_MSG_STATUS_NO_SUBSCRIBE;
        }
        lv_subject_set_pointer(subject, &guider_msg_data);
    }
    return GUI_MSG_STATUS_SUCCESS;
}

#endif
