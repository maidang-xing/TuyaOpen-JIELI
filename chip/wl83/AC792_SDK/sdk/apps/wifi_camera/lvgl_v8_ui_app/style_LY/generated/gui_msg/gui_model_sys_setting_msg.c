#include "app_config.h"
#ifdef CONFIG_UI_STYLE_LY_ENABLE
/*Generate Code, Do NOT Edit!*/
#include "./gui_model_sys_setting_msg.h"
#if LV_USE_OBSERVER

static lv_ll_t subs_ll;

#if LV_USE_GUIBUILDER_SIMULATOR
_gui_msg_entry_t gui_model_sys_setting_msg_entry_table[] = {
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
};
#endif


GUI_WEAK int gui_model_sys_setting_msg_funkey4_cb(gui_msg_action_t access, gui_msg_data_t *data, gui_msg_data_type_t type)
{
    char funkey4_init_var[] = "关闭";
    static bool funkey4_is_init = false;
    static char *funkey4_var = NULL;
    _gui_msg_char_array_cb(&funkey4_var, funkey4_init_var, &funkey4_is_init, access, data);
    return 0;
}
GUI_WEAK int gui_model_sys_setting_msg_funkey5_cb(gui_msg_action_t access, gui_msg_data_t *data, gui_msg_data_type_t type)
{
    char funkey5_init_var[] = "30s";
    static bool funkey5_is_init = false;
    static char *funkey5_var = NULL;
    _gui_msg_char_array_cb(&funkey5_var, funkey5_init_var, &funkey5_is_init, access, data);
    return 0;
}
GUI_WEAK int gui_model_sys_setting_msg_funkey6_cb(gui_msg_action_t access, gui_msg_data_t *data, gui_msg_data_type_t type)
{
    char funkey6_init_var[] = "60s";
    static bool funkey6_is_init = false;
    static char *funkey6_var = NULL;
    _gui_msg_char_array_cb(&funkey6_var, funkey6_init_var, &funkey6_is_init, access, data);
    return 0;
}
GUI_WEAK int gui_model_sys_setting_msg_funkey7_cb(gui_msg_action_t access, gui_msg_data_t *data, gui_msg_data_type_t type)
{
    char funkey7_init_var[] = "120s";
    static bool funkey7_is_init = false;
    static char *funkey7_var = NULL;
    _gui_msg_char_array_cb(&funkey7_var, funkey7_init_var, &funkey7_is_init, access, data);
    return 0;
}
GUI_WEAK int gui_model_sys_setting_msg_subpage_warning_cb(gui_msg_action_t access, gui_msg_data_t *data, gui_msg_data_type_t type)
{
    char subpage_warning_init_var[] = "warning";
    static bool subpage_warning_is_init = false;
    static char *subpage_warning_var = NULL;
    _gui_msg_char_array_cb(&subpage_warning_var, subpage_warning_init_var, &subpage_warning_is_init, access, data);
    return 0;
}
GUI_WEAK int gui_model_sys_setting_msg_hide_viewdate_cb(gui_msg_action_t access, gui_msg_data_t *data, gui_msg_data_type_t type)
{
    static lv_obj_flag_t hide_viewdate_var = LV_OBJ_FLAG_HIDDEN;
    _gui_msg_obj_flag_cb(&hide_viewdate_var, access, data);
    return 0;
}
GUI_WEAK int gui_model_sys_setting_msg_hide_viewcarnum_cb(gui_msg_action_t access, gui_msg_data_t *data, gui_msg_data_type_t type)
{
    static lv_obj_flag_t hide_viewcarnum_var = LV_OBJ_FLAG_HIDDEN;
    _gui_msg_obj_flag_cb(&hide_viewcarnum_var, access, data);
    return 0;
}
GUI_WEAK int gui_model_sys_setting_msg_hide_viewlist_cb(gui_msg_action_t access, gui_msg_data_t *data, gui_msg_data_type_t type)
{
    static lv_obj_flag_t hide_viewlist_var = LV_OBJ_FLAG_HIDDEN;
    _gui_msg_obj_flag_cb(&hide_viewlist_var, access, data);
    return 0;
}
GUI_WEAK int gui_model_sys_setting_msg_hide_subpagewarning_cb(gui_msg_action_t access, gui_msg_data_t *data, gui_msg_data_type_t type)
{
    static lv_obj_flag_t hide_subpagewarning_var = LV_OBJ_FLAG_HIDDEN;
    _gui_msg_obj_flag_cb(&hide_subpagewarning_var, access, data);
    return 0;
}
GUI_WEAK int gui_model_sys_setting_msg_show_viewdate_cb(gui_msg_action_t access, gui_msg_data_t *data, gui_msg_data_type_t type)
{
    static lv_obj_flag_t show_viewdate_var = 0;
    _gui_msg_obj_flag_cb(&show_viewdate_var, access, data);
    return 0;
}
GUI_WEAK int gui_model_sys_setting_msg_show_viewcarnum_cb(gui_msg_action_t access, gui_msg_data_t *data, gui_msg_data_type_t type)
{
    static lv_obj_flag_t show_viewcarnum_var = 0;
    _gui_msg_obj_flag_cb(&show_viewcarnum_var, access, data);
    return 0;
}
GUI_WEAK int gui_model_sys_setting_msg_show_viewlist_cb(gui_msg_action_t access, gui_msg_data_t *data, gui_msg_data_type_t type)
{
    static lv_obj_flag_t show_viewlist_var = 0;
    _gui_msg_obj_flag_cb(&show_viewlist_var, access, data);
    return 0;
}
GUI_WEAK int gui_model_sys_setting_msg_show_subpagewarning_cb(gui_msg_action_t access, gui_msg_data_t *data, gui_msg_data_type_t type)
{
    static lv_obj_flag_t show_subpagewarning_var = 0;
    _gui_msg_obj_flag_cb(&show_subpagewarning_var, access, data);
    return 0;
}
GUI_WEAK int gui_model_sys_setting_msg_hide_funkey5_cb(gui_msg_action_t access, gui_msg_data_t *data, gui_msg_data_type_t type)
{
    static lv_obj_flag_t hide_funkey5_var = LV_OBJ_FLAG_HIDDEN;
    _gui_msg_obj_flag_cb(&hide_funkey5_var, access, data);
    return 0;
}
GUI_WEAK int gui_model_sys_setting_msg_hide_funkey6_cb(gui_msg_action_t access, gui_msg_data_t *data, gui_msg_data_type_t type)
{
    static lv_obj_flag_t hide_funkey6_var = LV_OBJ_FLAG_HIDDEN;
    _gui_msg_obj_flag_cb(&hide_funkey6_var, access, data);
    return 0;
}
GUI_WEAK int gui_model_sys_setting_msg_hide_funkey7_cb(gui_msg_action_t access, gui_msg_data_t *data, gui_msg_data_type_t type)
{
    static lv_obj_flag_t hide_funkey7_var = LV_OBJ_FLAG_HIDDEN;
    _gui_msg_obj_flag_cb(&hide_funkey7_var, access, data);
    return 0;
}
GUI_WEAK int gui_model_sys_setting_msg_show_funkey4_cb(gui_msg_action_t access, gui_msg_data_t *data, gui_msg_data_type_t type)
{
    static lv_obj_flag_t show_funkey4_var = 0;
    _gui_msg_obj_flag_cb(&show_funkey4_var, access, data);
    return 0;
}
GUI_WEAK int gui_model_sys_setting_msg_show_funkey5_cb(gui_msg_action_t access, gui_msg_data_t *data, gui_msg_data_type_t type)
{
    static lv_obj_flag_t show_funkey5_var = 0;
    _gui_msg_obj_flag_cb(&show_funkey5_var, access, data);
    return 0;
}
GUI_WEAK int gui_model_sys_setting_msg_show_funkey6_cb(gui_msg_action_t access, gui_msg_data_t *data, gui_msg_data_type_t type)
{
    static lv_obj_flag_t show_funkey6_var = 0;
    _gui_msg_obj_flag_cb(&show_funkey6_var, access, data);
    return 0;
}
GUI_WEAK int gui_model_sys_setting_msg_show_funkey7_cb(gui_msg_action_t access, gui_msg_data_t *data, gui_msg_data_type_t type)
{
    static lv_obj_flag_t show_funkey7_var = 0;
    _gui_msg_obj_flag_cb(&show_funkey7_var, access, data);
    return 0;
}
GUI_WEAK int gui_model_sys_setting_msg_state_funkey4_cb(gui_msg_action_t access, gui_msg_data_t *data, gui_msg_data_type_t type)
{
    static lv_state_t state_funkey4_var = LV_STATE_DEFAULT;
    _gui_msg_state_cb(&state_funkey4_var, access, data);
    return 0;
}
GUI_WEAK int gui_model_sys_setting_msg_state_funkey5_cb(gui_msg_action_t access, gui_msg_data_t *data, gui_msg_data_type_t type)
{
    static lv_state_t state_funkey5_var = LV_STATE_DEFAULT;
    _gui_msg_state_cb(&state_funkey5_var, access, data);
    return 0;
}
GUI_WEAK int gui_model_sys_setting_msg_state_funkey6_cb(gui_msg_action_t access, gui_msg_data_t *data, gui_msg_data_type_t type)
{
    static lv_state_t state_funkey6_var = LV_STATE_DEFAULT;
    _gui_msg_state_cb(&state_funkey6_var, access, data);
    return 0;
}
GUI_WEAK int gui_model_sys_setting_msg_state_funkey7_cb(gui_msg_action_t access, gui_msg_data_t *data, gui_msg_data_type_t type)
{
    static lv_state_t state_funkey7_var = LV_STATE_DEFAULT;
    _gui_msg_state_cb(&state_funkey7_var, access, data);
    return 0;
}
GUI_WEAK int gui_model_sys_setting_msg_hide_funkey4_cb(gui_msg_action_t access, gui_msg_data_t *data, gui_msg_data_type_t type)
{
    static lv_obj_flag_t hide_funkey4_var = LV_OBJ_FLAG_HIDDEN;
    _gui_msg_obj_flag_cb(&hide_funkey4_var, access, data);
    return 0;
}
GUI_WEAK int gui_model_sys_setting_msg_subpage_warning_state_cb(gui_msg_action_t access, gui_msg_data_t *data, gui_msg_data_type_t type)
{
    static bool subpage_warning_state_var = false;
    _gui_msg_bool_cb(&subpage_warning_state_var, access, data);
    return 0;
}

void gui_model_sys_setting_msg_init(lv_ui *ui)
{
    int32_t ids[26] = {
        GUI_MODEL_SYS_SETTING_MSG_ID_FUNKEY4,
        GUI_MODEL_SYS_SETTING_MSG_ID_FUNKEY5,
        GUI_MODEL_SYS_SETTING_MSG_ID_FUNKEY6,
        GUI_MODEL_SYS_SETTING_MSG_ID_FUNKEY7,
        GUI_MODEL_SYS_SETTING_MSG_ID_SUBPAGE_WARNING,
        GUI_MODEL_SYS_SETTING_MSG_ID_HIDE_VIEWDATE,
        GUI_MODEL_SYS_SETTING_MSG_ID_HIDE_VIEWCARNUM,
        GUI_MODEL_SYS_SETTING_MSG_ID_HIDE_VIEWLIST,
        GUI_MODEL_SYS_SETTING_MSG_ID_HIDE_SUBPAGEWARNING,
        GUI_MODEL_SYS_SETTING_MSG_ID_SHOW_VIEWDATE,
        GUI_MODEL_SYS_SETTING_MSG_ID_SHOW_VIEWCARNUM,
        GUI_MODEL_SYS_SETTING_MSG_ID_SHOW_VIEWLIST,
        GUI_MODEL_SYS_SETTING_MSG_ID_SHOW_SUBPAGEWARNING,
        GUI_MODEL_SYS_SETTING_MSG_ID_HIDE_FUNKEY5,
        GUI_MODEL_SYS_SETTING_MSG_ID_HIDE_FUNKEY6,
        GUI_MODEL_SYS_SETTING_MSG_ID_HIDE_FUNKEY7,
        GUI_MODEL_SYS_SETTING_MSG_ID_SHOW_FUNKEY4,
        GUI_MODEL_SYS_SETTING_MSG_ID_SHOW_FUNKEY5,
        GUI_MODEL_SYS_SETTING_MSG_ID_SHOW_FUNKEY6,
        GUI_MODEL_SYS_SETTING_MSG_ID_SHOW_FUNKEY7,
        GUI_MODEL_SYS_SETTING_MSG_ID_STATE_FUNKEY4,
        GUI_MODEL_SYS_SETTING_MSG_ID_STATE_FUNKEY5,
        GUI_MODEL_SYS_SETTING_MSG_ID_STATE_FUNKEY6,
        GUI_MODEL_SYS_SETTING_MSG_ID_STATE_FUNKEY7,
        GUI_MODEL_SYS_SETTING_MSG_ID_HIDE_FUNKEY4,
        GUI_MODEL_SYS_SETTING_MSG_ID_SUBPAGE_WARNING_STATE,
    };
    for (int i = 0; i < 26; i++) {
        gui_msg_sub_t *sub = gui_msg_create_sub(ids[i]);
        if (sub != NULL) {
            lv_subject_init_pointer(sub->subject, &guider_msg_data);
        }
    }
}

void gui_model_sys_setting_msg_init_ui()
{
}

void gui_model_sys_setting_msg_init_events()
{
    void *res = NULL;
    _gui_msg_status_t status[26] = {
        {GUI_MODEL_SYS_SETTING_MSG_ID_FUNKEY4, 0, 0},
        {GUI_MODEL_SYS_SETTING_MSG_ID_FUNKEY5, 0, 0},
        {GUI_MODEL_SYS_SETTING_MSG_ID_FUNKEY6, 0, 0},
        {GUI_MODEL_SYS_SETTING_MSG_ID_FUNKEY7, 0, 0},
        {GUI_MODEL_SYS_SETTING_MSG_ID_SUBPAGE_WARNING, 0, 0},
        {GUI_MODEL_SYS_SETTING_MSG_ID_HIDE_VIEWDATE, 0, 0},
        {GUI_MODEL_SYS_SETTING_MSG_ID_HIDE_VIEWCARNUM, 0, 0},
        {GUI_MODEL_SYS_SETTING_MSG_ID_HIDE_VIEWLIST, 0, 0},
        {GUI_MODEL_SYS_SETTING_MSG_ID_HIDE_SUBPAGEWARNING, 0, 0},
        {GUI_MODEL_SYS_SETTING_MSG_ID_SHOW_VIEWDATE, 0, 0},
        {GUI_MODEL_SYS_SETTING_MSG_ID_SHOW_VIEWCARNUM, 0, 0},
        {GUI_MODEL_SYS_SETTING_MSG_ID_SHOW_VIEWLIST, 0, 0},
        {GUI_MODEL_SYS_SETTING_MSG_ID_SHOW_SUBPAGEWARNING, 0, 0},
        {GUI_MODEL_SYS_SETTING_MSG_ID_HIDE_FUNKEY5, 0, 0},
        {GUI_MODEL_SYS_SETTING_MSG_ID_HIDE_FUNKEY6, 0, 0},
        {GUI_MODEL_SYS_SETTING_MSG_ID_HIDE_FUNKEY7, 0, 0},
        {GUI_MODEL_SYS_SETTING_MSG_ID_SHOW_FUNKEY4, 0, 0},
        {GUI_MODEL_SYS_SETTING_MSG_ID_SHOW_FUNKEY5, 0, 0},
        {GUI_MODEL_SYS_SETTING_MSG_ID_SHOW_FUNKEY6, 0, 0},
        {GUI_MODEL_SYS_SETTING_MSG_ID_SHOW_FUNKEY7, 0, 0},
        {GUI_MODEL_SYS_SETTING_MSG_ID_STATE_FUNKEY4, 0, 0},
        {GUI_MODEL_SYS_SETTING_MSG_ID_STATE_FUNKEY5, 0, 0},
        {GUI_MODEL_SYS_SETTING_MSG_ID_STATE_FUNKEY6, 0, 0},
        {GUI_MODEL_SYS_SETTING_MSG_ID_STATE_FUNKEY7, 0, 0},
        {GUI_MODEL_SYS_SETTING_MSG_ID_HIDE_FUNKEY4, 0, 0},
        {GUI_MODEL_SYS_SETTING_MSG_ID_SUBPAGE_WARNING_STATE, 0, 0},
    };

    for (int i = 0; i < 26; i++) {
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


    for (int i = 0; i < 26; i++) {
        if (status[i].is_subscribe == 0 && status[i].is_unsubscribe == 1) {
            gui_msg_subscribe_change(status[i].msg_id, GUI_MSG_UNSUBSCRIBE);
        } else if (status[i].is_subscribe == 1 && status[i].is_unsubscribe == 0) {
            gui_msg_subscribe_change(status[i].msg_id, GUI_MSG_SUBSCRIBE);
        }
    }
}

void gui_model_sys_setting_msg_unsubscribe()
{
    _gui_msg_status_t status[26] = {
        {GUI_MODEL_SYS_SETTING_MSG_ID_FUNKEY4, 0, 0},
        {GUI_MODEL_SYS_SETTING_MSG_ID_FUNKEY5, 0, 0},
        {GUI_MODEL_SYS_SETTING_MSG_ID_FUNKEY6, 0, 0},
        {GUI_MODEL_SYS_SETTING_MSG_ID_FUNKEY7, 0, 0},
        {GUI_MODEL_SYS_SETTING_MSG_ID_SUBPAGE_WARNING, 0, 0},
        {GUI_MODEL_SYS_SETTING_MSG_ID_HIDE_VIEWDATE, 0, 0},
        {GUI_MODEL_SYS_SETTING_MSG_ID_HIDE_VIEWCARNUM, 0, 0},
        {GUI_MODEL_SYS_SETTING_MSG_ID_HIDE_VIEWLIST, 0, 0},
        {GUI_MODEL_SYS_SETTING_MSG_ID_HIDE_SUBPAGEWARNING, 0, 0},
        {GUI_MODEL_SYS_SETTING_MSG_ID_SHOW_VIEWDATE, 0, 0},
        {GUI_MODEL_SYS_SETTING_MSG_ID_SHOW_VIEWCARNUM, 0, 0},
        {GUI_MODEL_SYS_SETTING_MSG_ID_SHOW_VIEWLIST, 0, 0},
        {GUI_MODEL_SYS_SETTING_MSG_ID_SHOW_SUBPAGEWARNING, 0, 0},
        {GUI_MODEL_SYS_SETTING_MSG_ID_HIDE_FUNKEY5, 0, 0},
        {GUI_MODEL_SYS_SETTING_MSG_ID_HIDE_FUNKEY6, 0, 0},
        {GUI_MODEL_SYS_SETTING_MSG_ID_HIDE_FUNKEY7, 0, 0},
        {GUI_MODEL_SYS_SETTING_MSG_ID_SHOW_FUNKEY4, 0, 0},
        {GUI_MODEL_SYS_SETTING_MSG_ID_SHOW_FUNKEY5, 0, 0},
        {GUI_MODEL_SYS_SETTING_MSG_ID_SHOW_FUNKEY6, 0, 0},
        {GUI_MODEL_SYS_SETTING_MSG_ID_SHOW_FUNKEY7, 0, 0},
        {GUI_MODEL_SYS_SETTING_MSG_ID_STATE_FUNKEY4, 0, 0},
        {GUI_MODEL_SYS_SETTING_MSG_ID_STATE_FUNKEY5, 0, 0},
        {GUI_MODEL_SYS_SETTING_MSG_ID_STATE_FUNKEY6, 0, 0},
        {GUI_MODEL_SYS_SETTING_MSG_ID_STATE_FUNKEY7, 0, 0},
        {GUI_MODEL_SYS_SETTING_MSG_ID_HIDE_FUNKEY4, 0, 0},
        {GUI_MODEL_SYS_SETTING_MSG_ID_SUBPAGE_WARNING_STATE, 0, 0},
    };
    for (int i = 0; i < 26; i++) {
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

    for (int i = 0; i < 26; i++) {
        if (status[i].is_unsubscribe == 1) {
            gui_msg_subscribe_change(status[i].msg_id, GUI_MSG_UNSUBSCRIBE);
        }
    }
}

gui_msg_status_t gui_model_sys_setting_msg_send(int32_t msg_id, void *value, int32_t len)
{
    if (msg_id == GUI_MODEL_SYS_SETTING_MSG_ID) {
    } else {
        gui_msg_data_type_t data_type = VALUE_INT;
        switch (msg_id) {
        case GUI_MODEL_SYS_SETTING_MSG_ID_HIDE_VIEWDATE:
        case GUI_MODEL_SYS_SETTING_MSG_ID_HIDE_VIEWCARNUM:
        case GUI_MODEL_SYS_SETTING_MSG_ID_HIDE_VIEWLIST:
        case GUI_MODEL_SYS_SETTING_MSG_ID_HIDE_SUBPAGEWARNING:
        case GUI_MODEL_SYS_SETTING_MSG_ID_SHOW_VIEWDATE:
        case GUI_MODEL_SYS_SETTING_MSG_ID_SHOW_VIEWCARNUM:
        case GUI_MODEL_SYS_SETTING_MSG_ID_SHOW_VIEWLIST:
        case GUI_MODEL_SYS_SETTING_MSG_ID_SHOW_SUBPAGEWARNING:
        case GUI_MODEL_SYS_SETTING_MSG_ID_HIDE_FUNKEY5:
        case GUI_MODEL_SYS_SETTING_MSG_ID_HIDE_FUNKEY6:
        case GUI_MODEL_SYS_SETTING_MSG_ID_HIDE_FUNKEY7:
        case GUI_MODEL_SYS_SETTING_MSG_ID_SHOW_FUNKEY4:
        case GUI_MODEL_SYS_SETTING_MSG_ID_SHOW_FUNKEY5:
        case GUI_MODEL_SYS_SETTING_MSG_ID_SHOW_FUNKEY6:
        case GUI_MODEL_SYS_SETTING_MSG_ID_SHOW_FUNKEY7:
        case GUI_MODEL_SYS_SETTING_MSG_ID_HIDE_FUNKEY4: {
            data_type = VALUE_INT;
            guider_msg_data.value_array.ptr = value;
            guider_msg_data.value_array.len = len;
        }
        break;
        case GUI_MODEL_SYS_SETTING_MSG_ID_STATE_FUNKEY4:
        case GUI_MODEL_SYS_SETTING_MSG_ID_STATE_FUNKEY5:
        case GUI_MODEL_SYS_SETTING_MSG_ID_STATE_FUNKEY6:
        case GUI_MODEL_SYS_SETTING_MSG_ID_STATE_FUNKEY7: {
            data_type = VALUE_INT;
            guider_msg_data.value_array.ptr = value;
            guider_msg_data.value_array.len = len;
        }
        break;
        case GUI_MODEL_SYS_SETTING_MSG_ID_SUBPAGE_WARNING_STATE: {
            data_type = VALUE_BOOL;
            guider_msg_data.value_array.ptr = value;
            guider_msg_data.value_array.len = len;
        }
        break;
        case GUI_MODEL_SYS_SETTING_MSG_ID_FUNKEY4:
        case GUI_MODEL_SYS_SETTING_MSG_ID_FUNKEY5:
        case GUI_MODEL_SYS_SETTING_MSG_ID_FUNKEY6:
        case GUI_MODEL_SYS_SETTING_MSG_ID_FUNKEY7:
        case GUI_MODEL_SYS_SETTING_MSG_ID_SUBPAGE_WARNING: {
            data_type = VALUE_STRING;
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
