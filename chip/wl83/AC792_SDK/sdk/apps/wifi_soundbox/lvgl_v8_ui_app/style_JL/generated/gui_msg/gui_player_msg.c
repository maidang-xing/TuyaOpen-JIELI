/*Generate Code, Do NOT Edit!*/
#include "./gui_player_msg.h"

#if LV_USE_OBSERVER

static lv_ll_t subs_ll;

#if LV_USE_GUIBUILDER_SIMULATOR
_gui_msg_entry_t gui_player_msg_entry_table[] = {
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
};
#endif


GUI_WEAK int gui_player_msg_eq_1_cb(gui_msg_action_t access, gui_msg_data_t *data, gui_msg_data_type_t type)
{
    static int32_t eq_1_var = 1;
    _gui_msg_int32_cb(&eq_1_var, access, data);
    return 0;
}
GUI_WEAK int gui_player_msg_eq_2_cb(gui_msg_action_t access, gui_msg_data_t *data, gui_msg_data_type_t type)
{
    static int32_t eq_2_var = 1;
    _gui_msg_int32_cb(&eq_2_var, access, data);
    return 0;
}
GUI_WEAK int gui_player_msg_eq_3_cb(gui_msg_action_t access, gui_msg_data_t *data, gui_msg_data_type_t type)
{
    static int32_t eq_3_var = 1;
    _gui_msg_int32_cb(&eq_3_var, access, data);
    return 0;
}
GUI_WEAK int gui_player_msg_eq_4_cb(gui_msg_action_t access, gui_msg_data_t *data, gui_msg_data_type_t type)
{
    static int32_t eq_4_var = 1;
    _gui_msg_int32_cb(&eq_4_var, access, data);
    return 0;
}
GUI_WEAK int gui_player_msg_eq_5_cb(gui_msg_action_t access, gui_msg_data_t *data, gui_msg_data_type_t type)
{
    static int32_t eq_5_var = 1;
    _gui_msg_int32_cb(&eq_5_var, access, data);
    return 0;
}
GUI_WEAK int gui_player_msg_eq_6_cb(gui_msg_action_t access, gui_msg_data_t *data, gui_msg_data_type_t type)
{
    static int32_t eq_6_var = 1;
    _gui_msg_int32_cb(&eq_6_var, access, data);
    return 0;
}
GUI_WEAK int gui_player_msg_eq_7_cb(gui_msg_action_t access, gui_msg_data_t *data, gui_msg_data_type_t type)
{
    static int32_t eq_7_var = 1;
    _gui_msg_int32_cb(&eq_7_var, access, data);
    return 0;
}
GUI_WEAK int gui_player_msg_eq_8_cb(gui_msg_action_t access, gui_msg_data_t *data, gui_msg_data_type_t type)
{
    static int32_t eq_8_var = 1;
    _gui_msg_int32_cb(&eq_8_var, access, data);
    return 0;
}
GUI_WEAK int gui_player_msg_eq_9_cb(gui_msg_action_t access, gui_msg_data_t *data, gui_msg_data_type_t type)
{
    static int32_t eq_9_var = 1;
    _gui_msg_int32_cb(&eq_9_var, access, data);
    return 0;
}
GUI_WEAK int gui_player_msg_eq_10_cb(gui_msg_action_t access, gui_msg_data_t *data, gui_msg_data_type_t type)
{
    static int32_t eq_10_var = 1;
    _gui_msg_int32_cb(&eq_10_var, access, data);
    return 0;
}
GUI_WEAK int gui_player_msg_eq_mode_cb(gui_msg_action_t access, gui_msg_data_t *data, gui_msg_data_type_t type)
{
    static int32_t eq_mode_var = 1;
    _gui_msg_int32_cb(&eq_mode_var, access, data);
    return 0;
}
GUI_WEAK int gui_player_msg_save_mode_cb(gui_msg_action_t access, gui_msg_data_t *data, gui_msg_data_type_t type)
{
    static lv_state_t save_mode_var = LV_STATE_DISABLED;
    _gui_msg_state_cb(&save_mode_var, access, data);
    return 0;
}

void gui_player_msg_init(lv_ui *ui)
{
    int32_t ids[12] = {
        GUI_PLAYER_MSG_ID_EQ_1,
        GUI_PLAYER_MSG_ID_EQ_2,
        GUI_PLAYER_MSG_ID_EQ_3,
        GUI_PLAYER_MSG_ID_EQ_4,
        GUI_PLAYER_MSG_ID_EQ_5,
        GUI_PLAYER_MSG_ID_EQ_6,
        GUI_PLAYER_MSG_ID_EQ_7,
        GUI_PLAYER_MSG_ID_EQ_8,
        GUI_PLAYER_MSG_ID_EQ_9,
        GUI_PLAYER_MSG_ID_EQ_10,
        GUI_PLAYER_MSG_ID_EQ_MODE,
        GUI_PLAYER_MSG_ID_SAVE_MODE,
    };
    for (int i = 0; i < 12; i++) {
        gui_msg_sub_t *sub = gui_msg_create_sub(ids[i]);
        if (sub != NULL) {
            lv_subject_init_pointer(sub->subject, &guider_msg_data);
        }
    }
}

void gui_player_msg_init_ui()
{
}

void gui_player_msg_init_events()
{
    void *res = NULL;
    _gui_msg_status_t status[12] = {
        {GUI_PLAYER_MSG_ID_EQ_1, 0, 0},
        {GUI_PLAYER_MSG_ID_EQ_2, 0, 0},
        {GUI_PLAYER_MSG_ID_EQ_3, 0, 0},
        {GUI_PLAYER_MSG_ID_EQ_4, 0, 0},
        {GUI_PLAYER_MSG_ID_EQ_5, 0, 0},
        {GUI_PLAYER_MSG_ID_EQ_6, 0, 0},
        {GUI_PLAYER_MSG_ID_EQ_7, 0, 0},
        {GUI_PLAYER_MSG_ID_EQ_8, 0, 0},
        {GUI_PLAYER_MSG_ID_EQ_9, 0, 0},
        {GUI_PLAYER_MSG_ID_EQ_10, 0, 0},
        {GUI_PLAYER_MSG_ID_EQ_MODE, 0, 0},
        {GUI_PLAYER_MSG_ID_SAVE_MODE, 0, 0},
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

    lv_subject_t *subject_eq_1 = gui_msg_get_subject(GUI_PLAYER_MSG_ID_EQ_1);
    lv_subject_t *subject_eq_2 = gui_msg_get_subject(GUI_PLAYER_MSG_ID_EQ_2);
    lv_subject_t *subject_eq_3 = gui_msg_get_subject(GUI_PLAYER_MSG_ID_EQ_3);
    lv_subject_t *subject_eq_4 = gui_msg_get_subject(GUI_PLAYER_MSG_ID_EQ_4);
    lv_subject_t *subject_eq_5 = gui_msg_get_subject(GUI_PLAYER_MSG_ID_EQ_5);
    lv_subject_t *subject_eq_6 = gui_msg_get_subject(GUI_PLAYER_MSG_ID_EQ_6);
    lv_subject_t *subject_eq_7 = gui_msg_get_subject(GUI_PLAYER_MSG_ID_EQ_7);
    lv_subject_t *subject_eq_8 = gui_msg_get_subject(GUI_PLAYER_MSG_ID_EQ_8);
    lv_subject_t *subject_eq_9 = gui_msg_get_subject(GUI_PLAYER_MSG_ID_EQ_9);
    lv_subject_t *subject_eq_10 = gui_msg_get_subject(GUI_PLAYER_MSG_ID_EQ_10);
    lv_subject_t *subject_save_mode = gui_msg_get_subject(GUI_PLAYER_MSG_ID_SAVE_MODE);
    if (guider_ui.eq_modify) {
        lv_ui_eq_modify *ui_scr = ui_get_scr_ptr(&guider_ui, GUI_SCREEN_EQ_MODIFY);
        gui_msg_setup_component(true, true, subject_eq_1, ui_scr->eq_modify_slider_1, &guider_msg_data, gui_msg_set_slider_starting_value_by_int32_cb, GUI_PLAYER_MSG_ID_EQ_1, GUI_MSG_ACCESS_GET, VALUE_INT, gui_msg_change_slider_starting_value_cb);

        gui_msg_setup_component(true, true, subject_eq_2, ui_scr->eq_modify_slider_2, &guider_msg_data, gui_msg_set_slider_starting_value_by_int32_cb, GUI_PLAYER_MSG_ID_EQ_2, GUI_MSG_ACCESS_GET, VALUE_INT, gui_msg_change_slider_starting_value_cb);

        gui_msg_setup_component(true, true, subject_eq_3, ui_scr->eq_modify_slider_3, &guider_msg_data, gui_msg_set_slider_starting_value_by_int32_cb, GUI_PLAYER_MSG_ID_EQ_3, GUI_MSG_ACCESS_GET, VALUE_INT, gui_msg_change_slider_starting_value_cb);

        gui_msg_setup_component(true, true, subject_eq_4, ui_scr->eq_modify_slider_4, &guider_msg_data, gui_msg_set_slider_starting_value_by_int32_cb, GUI_PLAYER_MSG_ID_EQ_4, GUI_MSG_ACCESS_GET, VALUE_INT, gui_msg_change_slider_starting_value_cb);

        gui_msg_setup_component(true, true, subject_eq_5, ui_scr->eq_modify_slider_5, &guider_msg_data, gui_msg_set_slider_starting_value_by_int32_cb, GUI_PLAYER_MSG_ID_EQ_5, GUI_MSG_ACCESS_GET, VALUE_INT, gui_msg_change_slider_starting_value_cb);

        gui_msg_setup_component(true, true, subject_eq_6, ui_scr->eq_modify_slider_6, &guider_msg_data, gui_msg_set_slider_starting_value_by_int32_cb, GUI_PLAYER_MSG_ID_EQ_6, GUI_MSG_ACCESS_GET, VALUE_INT, gui_msg_change_slider_starting_value_cb);

        gui_msg_setup_component(true, true, subject_eq_7, ui_scr->eq_modify_slider_7, &guider_msg_data, gui_msg_set_slider_starting_value_by_int32_cb, GUI_PLAYER_MSG_ID_EQ_7, GUI_MSG_ACCESS_GET, VALUE_INT, gui_msg_change_slider_starting_value_cb);

        gui_msg_setup_component(true, true, subject_eq_8, ui_scr->eq_modify_slider_8, &guider_msg_data, gui_msg_set_slider_starting_value_by_int32_cb, GUI_PLAYER_MSG_ID_EQ_8, GUI_MSG_ACCESS_GET, VALUE_INT, gui_msg_change_slider_starting_value_cb);

        gui_msg_setup_component(true, true, subject_eq_9, ui_scr->eq_modify_slider_9, &guider_msg_data, gui_msg_set_slider_starting_value_by_int32_cb, GUI_PLAYER_MSG_ID_EQ_9, GUI_MSG_ACCESS_GET, VALUE_INT, gui_msg_change_slider_starting_value_cb);

        gui_msg_setup_component(true, true, subject_eq_10, ui_scr->eq_modify_slider_10, &guider_msg_data, gui_msg_set_slider_starting_value_by_int32_cb, GUI_PLAYER_MSG_ID_EQ_10, GUI_MSG_ACCESS_GET, VALUE_INT, gui_msg_change_slider_starting_value_cb);

        gui_msg_setup_component(true, false, subject_save_mode, ui_scr->eq_modify_btn_1, &guider_msg_data, gui_msg_set_control_state_by_int32_cb, GUI_PLAYER_MSG_ID_SAVE_MODE, GUI_MSG_ACCESS_GET, VALUE_INT, NULL);


        for (int i = 0; i < 12; i++) {
            if (status[i].msg_id == GUI_PLAYER_MSG_ID_EQ_1) {
                status[i].is_subscribe = 1;
            }
            if (status[i].msg_id == GUI_PLAYER_MSG_ID_EQ_2) {
                status[i].is_subscribe = 1;
            }
            if (status[i].msg_id == GUI_PLAYER_MSG_ID_EQ_3) {
                status[i].is_subscribe = 1;
            }
            if (status[i].msg_id == GUI_PLAYER_MSG_ID_EQ_4) {
                status[i].is_subscribe = 1;
            }
            if (status[i].msg_id == GUI_PLAYER_MSG_ID_EQ_5) {
                status[i].is_subscribe = 1;
            }
            if (status[i].msg_id == GUI_PLAYER_MSG_ID_EQ_6) {
                status[i].is_subscribe = 1;
            }
            if (status[i].msg_id == GUI_PLAYER_MSG_ID_EQ_7) {
                status[i].is_subscribe = 1;
            }
            if (status[i].msg_id == GUI_PLAYER_MSG_ID_EQ_8) {
                status[i].is_subscribe = 1;
            }
            if (status[i].msg_id == GUI_PLAYER_MSG_ID_EQ_9) {
                status[i].is_subscribe = 1;
            }
            if (status[i].msg_id == GUI_PLAYER_MSG_ID_EQ_10) {
                status[i].is_subscribe = 1;
            }
            if (status[i].msg_id == GUI_PLAYER_MSG_ID_SAVE_MODE) {
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

void gui_player_msg_unsubscribe()
{
    _gui_msg_status_t status[12] = {
        {GUI_PLAYER_MSG_ID_EQ_1, 0, 0},
        {GUI_PLAYER_MSG_ID_EQ_2, 0, 0},
        {GUI_PLAYER_MSG_ID_EQ_3, 0, 0},
        {GUI_PLAYER_MSG_ID_EQ_4, 0, 0},
        {GUI_PLAYER_MSG_ID_EQ_5, 0, 0},
        {GUI_PLAYER_MSG_ID_EQ_6, 0, 0},
        {GUI_PLAYER_MSG_ID_EQ_7, 0, 0},
        {GUI_PLAYER_MSG_ID_EQ_8, 0, 0},
        {GUI_PLAYER_MSG_ID_EQ_9, 0, 0},
        {GUI_PLAYER_MSG_ID_EQ_10, 0, 0},
        {GUI_PLAYER_MSG_ID_EQ_MODE, 0, 0},
        {GUI_PLAYER_MSG_ID_SAVE_MODE, 0, 0},
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

gui_msg_status_t gui_player_msg_send(int32_t msg_id, void *value, int32_t len)
{
    if (msg_id == GUI_PLAYER_MSG_ID) {
    } else {
        gui_msg_data_type_t data_type = VALUE_INT;
        switch (msg_id) {
        case GUI_PLAYER_MSG_ID_SAVE_MODE: {
            data_type = VALUE_INT;
            guider_msg_data.value_array.ptr = value;
            guider_msg_data.value_array.len = len;
        }
        break;
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
        case GUI_PLAYER_MSG_ID_EQ_MODE: {
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
