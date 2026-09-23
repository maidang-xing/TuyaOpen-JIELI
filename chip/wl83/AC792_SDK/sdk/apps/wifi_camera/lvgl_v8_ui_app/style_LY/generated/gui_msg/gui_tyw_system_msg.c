#include "app_config.h"
#ifdef CONFIG_UI_STYLE_LY_ENABLE
/*Generate Code, Do NOT Edit!*/
#include "./gui_tyw_system_msg.h"
#if LV_USE_OBSERVER

static lv_ll_t subs_ll;

#if LV_USE_GUIBUILDER_SIMULATOR
_gui_msg_entry_t gui_tyw_system_msg_entry_table[] = {
    { GUI_TYW_SYSTEM_MSG_ID_BT_CONN, gui_tyw_system_msg_bt_conn_cb, VALUE_INT },
    { GUI_TYW_SYSTEM_MSG_ID_BT_DISCONN, gui_tyw_system_msg_bt_disconn_cb, VALUE_INT },
    { GUI_TYW_SYSTEM_MSG_ID_PHONE_INCOME, gui_tyw_system_msg_phone_income_cb, VALUE_INT },
    { GUI_TYW_SYSTEM_MSG_ID_PHONE_HANGUP, gui_tyw_system_msg_phone_hangup_cb, VALUE_INT },
    { GUI_TYW_SYSTEM_MSG_ID_PHONE_NUMBER, gui_tyw_system_msg_phone_number_cb, VALUE_STRING },
    { GUI_TYW_SYSTEM_MSG_ID_MUSIC_INFO, gui_tyw_system_msg_music_info_cb, VALUE_INT },
};
#endif


GUI_WEAK int gui_tyw_system_msg_bt_conn_cb(gui_msg_action_t access, gui_msg_data_t *data, gui_msg_data_type_t type)
{
    static int32_t bt_conn_var = 1;
    _gui_msg_int32_cb(&bt_conn_var, access, data);
    return 0;
}
GUI_WEAK int gui_tyw_system_msg_bt_disconn_cb(gui_msg_action_t access, gui_msg_data_t *data, gui_msg_data_type_t type)
{
    static int32_t bt_disconn_var = 1;
    _gui_msg_int32_cb(&bt_disconn_var, access, data);
    return 0;
}
GUI_WEAK int gui_tyw_system_msg_phone_income_cb(gui_msg_action_t access, gui_msg_data_t *data, gui_msg_data_type_t type)
{
    static int32_t phone_income_var = 0;
    _gui_msg_int32_cb(&phone_income_var, access, data);
    return 0;
}
GUI_WEAK int gui_tyw_system_msg_phone_hangup_cb(gui_msg_action_t access, gui_msg_data_t *data, gui_msg_data_type_t type)
{
    static int32_t phone_hangup_var = 1;
    _gui_msg_int32_cb(&phone_hangup_var, access, data);
    return 0;
}
GUI_WEAK int gui_tyw_system_msg_phone_number_cb(gui_msg_action_t access, gui_msg_data_t *data, gui_msg_data_type_t type)
{
    char phone_number_init_var[] = "";
    static bool phone_number_is_init = false;
    static char *phone_number_var = NULL;
    _gui_msg_char_array_cb(&phone_number_var, phone_number_init_var, &phone_number_is_init, access, data);
    return 0;
}
GUI_WEAK int gui_tyw_system_msg_music_info_cb(gui_msg_action_t access, gui_msg_data_t *data, gui_msg_data_type_t type)
{
    static int32_t music_info_var = 1;
    _gui_msg_int32_cb(&music_info_var, access, data);
    return 0;
}

void gui_tyw_system_msg_init(lv_ui *ui)
{
    int32_t ids[6] = {
        GUI_TYW_SYSTEM_MSG_ID_BT_CONN,
        GUI_TYW_SYSTEM_MSG_ID_BT_DISCONN,
        GUI_TYW_SYSTEM_MSG_ID_PHONE_INCOME,
        GUI_TYW_SYSTEM_MSG_ID_PHONE_HANGUP,
        GUI_TYW_SYSTEM_MSG_ID_PHONE_NUMBER,
        GUI_TYW_SYSTEM_MSG_ID_MUSIC_INFO,
    };
    for (int i = 0; i < 6; i++) {
        gui_msg_sub_t *sub = gui_msg_create_sub(ids[i]);
        if (sub != NULL) {
            lv_subject_init_pointer(sub->subject, &guider_msg_data);
        }
    }
}

void gui_tyw_system_msg_init_ui()
{
}

void gui_tyw_system_msg_init_events()
{
    void *res = NULL;
    _gui_msg_status_t status[6] = {
        {GUI_TYW_SYSTEM_MSG_ID_BT_CONN, 0, 0},
        {GUI_TYW_SYSTEM_MSG_ID_BT_DISCONN, 0, 0},
        {GUI_TYW_SYSTEM_MSG_ID_PHONE_INCOME, 0, 0},
        {GUI_TYW_SYSTEM_MSG_ID_PHONE_HANGUP, 0, 0},
        {GUI_TYW_SYSTEM_MSG_ID_PHONE_NUMBER, 0, 0},
        {GUI_TYW_SYSTEM_MSG_ID_MUSIC_INFO, 0, 0},
    };

    for (int i = 0; i < 6; i++) {
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


    for (int i = 0; i < 6; i++) {
        if (status[i].is_subscribe == 0 && status[i].is_unsubscribe == 1) {
            gui_msg_subscribe_change(status[i].msg_id, GUI_MSG_UNSUBSCRIBE);
        } else if (status[i].is_subscribe == 1 && status[i].is_unsubscribe == 0) {
            gui_msg_subscribe_change(status[i].msg_id, GUI_MSG_SUBSCRIBE);
        }
    }
}

void gui_tyw_system_msg_unsubscribe()
{
    _gui_msg_status_t status[6] = {
        {GUI_TYW_SYSTEM_MSG_ID_BT_CONN, 0, 0},
        {GUI_TYW_SYSTEM_MSG_ID_BT_DISCONN, 0, 0},
        {GUI_TYW_SYSTEM_MSG_ID_PHONE_INCOME, 0, 0},
        {GUI_TYW_SYSTEM_MSG_ID_PHONE_HANGUP, 0, 0},
        {GUI_TYW_SYSTEM_MSG_ID_PHONE_NUMBER, 0, 0},
        {GUI_TYW_SYSTEM_MSG_ID_MUSIC_INFO, 0, 0},
    };
    for (int i = 0; i < 6; i++) {
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

    for (int i = 0; i < 6; i++) {
        if (status[i].is_unsubscribe == 1) {
            gui_msg_subscribe_change(status[i].msg_id, GUI_MSG_UNSUBSCRIBE);
        }
    }
}

gui_msg_status_t gui_tyw_system_msg_send(int32_t msg_id, void *value, int32_t len)
{
    if (msg_id == GUI_TYW_SYSTEM_MSG_ID) {
    } else {
        gui_msg_data_type_t data_type = VALUE_INT;
        switch (msg_id) {
        case GUI_TYW_SYSTEM_MSG_ID_PHONE_NUMBER: {
            data_type = VALUE_STRING;
            guider_msg_data.value_array.ptr = value;
            guider_msg_data.value_array.len = len;
        }
        break;
        case GUI_TYW_SYSTEM_MSG_ID_BT_CONN:
        case GUI_TYW_SYSTEM_MSG_ID_BT_DISCONN:
        case GUI_TYW_SYSTEM_MSG_ID_PHONE_INCOME:
        case GUI_TYW_SYSTEM_MSG_ID_PHONE_HANGUP:
        case GUI_TYW_SYSTEM_MSG_ID_MUSIC_INFO: {
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

#endif
