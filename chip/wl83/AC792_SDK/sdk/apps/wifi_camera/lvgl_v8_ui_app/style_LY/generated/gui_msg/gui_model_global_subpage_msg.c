#include "app_config.h"
#ifdef CONFIG_UI_STYLE_LY_ENABLE
/*Generate Code, Do NOT Edit!*/
#include "./gui_model_global_subpage_msg.h"
#if LV_USE_OBSERVER

static lv_ll_t subs_ll;

#if LV_USE_GUIBUILDER_SIMULATOR
_gui_msg_entry_t gui_model_global_subpage_msg_entry_table[] = {
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
};
#endif


GUI_WEAK int gui_model_global_subpage_msg_subpage_icon_cb(gui_msg_action_t access, gui_msg_data_t *data, gui_msg_data_type_t type)
{
    static int32_t subpage_icon_var = RES_RESOLUTION_RATIO;
    _gui_msg_int32_cb(&subpage_icon_var, access, data);
    return 0;
}
GUI_WEAK int gui_model_global_subpage_msg_funckey1_cb(gui_msg_action_t access, gui_msg_data_t *data, gui_msg_data_type_t type)
{
    char funckey1_init_var[] = "funckey1";
    static bool funckey1_is_init = false;
    static char *funckey1_var = NULL;
    _gui_msg_char_array_cb(&funckey1_var, funckey1_init_var, &funckey1_is_init, access, data);
    return 0;
}
GUI_WEAK int gui_model_global_subpage_msg_funckey2_cb(gui_msg_action_t access, gui_msg_data_t *data, gui_msg_data_type_t type)
{
    char funckey2_init_var[] = "funckey2";
    static bool funckey2_is_init = false;
    static char *funckey2_var = NULL;
    _gui_msg_char_array_cb(&funckey2_var, funckey2_init_var, &funckey2_is_init, access, data);
    return 0;
}
GUI_WEAK int gui_model_global_subpage_msg_funckey3_cb(gui_msg_action_t access, gui_msg_data_t *data, gui_msg_data_type_t type)
{
    char funckey3_init_var[] = "funckey3";
    static bool funckey3_is_init = false;
    static char *funckey3_var = NULL;
    _gui_msg_char_array_cb(&funckey3_var, funckey3_init_var, &funckey3_is_init, access, data);
    return 0;
}
GUI_WEAK int gui_model_global_subpage_msg_funckey4_cb(gui_msg_action_t access, gui_msg_data_t *data, gui_msg_data_type_t type)
{
    char funckey4_init_var[] = "funckey4";
    static bool funckey4_is_init = false;
    static char *funckey4_var = NULL;
    _gui_msg_char_array_cb(&funckey4_var, funckey4_init_var, &funckey4_is_init, access, data);
    return 0;
}
GUI_WEAK int gui_model_global_subpage_msg_title_cb(gui_msg_action_t access, gui_msg_data_t *data, gui_msg_data_type_t type)
{
    char title_init_var[] = "title";
    static bool title_is_init = false;
    static char *title_var = NULL;
    _gui_msg_char_array_cb(&title_var, title_init_var, &title_is_init, access, data);
    return 0;
}
GUI_WEAK int gui_model_global_subpage_msg_hide_funckey1_cb(gui_msg_action_t access, gui_msg_data_t *data, gui_msg_data_type_t type)
{
    static lv_obj_flag_t hide_funckey1_var = LV_OBJ_FLAG_HIDDEN;
    _gui_msg_obj_flag_cb(&hide_funckey1_var, access, data);
    return 0;
}
GUI_WEAK int gui_model_global_subpage_msg_hide_funckey2_cb(gui_msg_action_t access, gui_msg_data_t *data, gui_msg_data_type_t type)
{
    static lv_obj_flag_t hide_funckey2_var = LV_OBJ_FLAG_HIDDEN;
    _gui_msg_obj_flag_cb(&hide_funckey2_var, access, data);
    return 0;
}
GUI_WEAK int gui_model_global_subpage_msg_hide_funckey3_cb(gui_msg_action_t access, gui_msg_data_t *data, gui_msg_data_type_t type)
{
    static lv_obj_flag_t hide_funckey3_var = LV_OBJ_FLAG_HIDDEN;
    _gui_msg_obj_flag_cb(&hide_funckey3_var, access, data);
    return 0;
}
GUI_WEAK int gui_model_global_subpage_msg_hide_funckey4_cb(gui_msg_action_t access, gui_msg_data_t *data, gui_msg_data_type_t type)
{
    static lv_obj_flag_t hide_funckey4_var = LV_OBJ_FLAG_HIDDEN;
    _gui_msg_obj_flag_cb(&hide_funckey4_var, access, data);
    return 0;
}
GUI_WEAK int gui_model_global_subpage_msg_show_funckey1_cb(gui_msg_action_t access, gui_msg_data_t *data, gui_msg_data_type_t type)
{
    static lv_obj_flag_t show_funckey1_var = 0;
    _gui_msg_obj_flag_cb(&show_funckey1_var, access, data);
    return 0;
}
GUI_WEAK int gui_model_global_subpage_msg_show_funckey2_cb(gui_msg_action_t access, gui_msg_data_t *data, gui_msg_data_type_t type)
{
    static lv_obj_flag_t show_funckey2_var = 0;
    _gui_msg_obj_flag_cb(&show_funckey2_var, access, data);
    return 0;
}
GUI_WEAK int gui_model_global_subpage_msg_show_funckey3_cb(gui_msg_action_t access, gui_msg_data_t *data, gui_msg_data_type_t type)
{
    static lv_obj_flag_t show_funckey3_var = 0;
    _gui_msg_obj_flag_cb(&show_funckey3_var, access, data);
    return 0;
}
GUI_WEAK int gui_model_global_subpage_msg_show_funckey4_cb(gui_msg_action_t access, gui_msg_data_t *data, gui_msg_data_type_t type)
{
    static lv_obj_flag_t show_funckey4_var = 0;
    _gui_msg_obj_flag_cb(&show_funckey4_var, access, data);
    return 0;
}
GUI_WEAK int gui_model_global_subpage_msg_roller_opt_cb(gui_msg_action_t access, gui_msg_data_t *data, gui_msg_data_type_t type)
{
    char roller_opt_init_var[] = "1\n2\n3\n";
    static bool roller_opt_is_init = false;
    static char *roller_opt_var = NULL;
    _gui_msg_char_array_cb(&roller_opt_var, roller_opt_init_var, &roller_opt_is_init, access, data);
    return 0;
}
GUI_WEAK int gui_model_global_subpage_msg_show_roller_cb(gui_msg_action_t access, gui_msg_data_t *data, gui_msg_data_type_t type)
{
    static lv_obj_flag_t show_roller_var = LV_OBJ_FLAG_HIDDEN;
    _gui_msg_obj_flag_cb(&show_roller_var, access, data);
    return 0;
}
GUI_WEAK int gui_model_global_subpage_msg_hide_roller_cb(gui_msg_action_t access, gui_msg_data_t *data, gui_msg_data_type_t type)
{
    static lv_obj_flag_t hide_roller_var = LV_OBJ_FLAG_HIDDEN;
    _gui_msg_obj_flag_cb(&hide_roller_var, access, data);
    return 0;
}
GUI_WEAK int gui_model_global_subpage_msg_state_funkey1_cb(gui_msg_action_t access, gui_msg_data_t *data, gui_msg_data_type_t type)
{
    static lv_state_t state_funkey1_var = LV_STATE_DEFAULT;
    _gui_msg_state_cb(&state_funkey1_var, access, data);
    return 0;
}
GUI_WEAK int gui_model_global_subpage_msg_state_funkey2_cb(gui_msg_action_t access, gui_msg_data_t *data, gui_msg_data_type_t type)
{
    static lv_state_t state_funkey2_var = LV_STATE_DEFAULT;
    _gui_msg_state_cb(&state_funkey2_var, access, data);
    return 0;
}
GUI_WEAK int gui_model_global_subpage_msg_state_funkey3_cb(gui_msg_action_t access, gui_msg_data_t *data, gui_msg_data_type_t type)
{
    static lv_state_t state_funkey3_var = LV_STATE_DEFAULT;
    _gui_msg_state_cb(&state_funkey3_var, access, data);
    return 0;
}
GUI_WEAK int gui_model_global_subpage_msg_state_funkey4_cb(gui_msg_action_t access, gui_msg_data_t *data, gui_msg_data_type_t type)
{
    static lv_state_t state_funkey4_var = LV_STATE_DEFAULT;
    _gui_msg_state_cb(&state_funkey4_var, access, data);
    return 0;
}

void gui_model_global_subpage_msg_init(lv_ui *ui)
{
    int32_t ids[21] = {
        GUI_MODEL_GLOBAL_SUBPAGE_MSG_ID_SUBPAGE_ICON,
        GUI_MODEL_GLOBAL_SUBPAGE_MSG_ID_FUNCKEY1,
        GUI_MODEL_GLOBAL_SUBPAGE_MSG_ID_FUNCKEY2,
        GUI_MODEL_GLOBAL_SUBPAGE_MSG_ID_FUNCKEY3,
        GUI_MODEL_GLOBAL_SUBPAGE_MSG_ID_FUNCKEY4,
        GUI_MODEL_GLOBAL_SUBPAGE_MSG_ID_TITLE,
        GUI_MODEL_GLOBAL_SUBPAGE_MSG_ID_HIDE_FUNCKEY1,
        GUI_MODEL_GLOBAL_SUBPAGE_MSG_ID_HIDE_FUNCKEY2,
        GUI_MODEL_GLOBAL_SUBPAGE_MSG_ID_HIDE_FUNCKEY3,
        GUI_MODEL_GLOBAL_SUBPAGE_MSG_ID_HIDE_FUNCKEY4,
        GUI_MODEL_GLOBAL_SUBPAGE_MSG_ID_SHOW_FUNCKEY1,
        GUI_MODEL_GLOBAL_SUBPAGE_MSG_ID_SHOW_FUNCKEY2,
        GUI_MODEL_GLOBAL_SUBPAGE_MSG_ID_SHOW_FUNCKEY3,
        GUI_MODEL_GLOBAL_SUBPAGE_MSG_ID_SHOW_FUNCKEY4,
        GUI_MODEL_GLOBAL_SUBPAGE_MSG_ID_ROLLER_OPT,
        GUI_MODEL_GLOBAL_SUBPAGE_MSG_ID_SHOW_ROLLER,
        GUI_MODEL_GLOBAL_SUBPAGE_MSG_ID_HIDE_ROLLER,
        GUI_MODEL_GLOBAL_SUBPAGE_MSG_ID_STATE_FUNKEY1,
        GUI_MODEL_GLOBAL_SUBPAGE_MSG_ID_STATE_FUNKEY2,
        GUI_MODEL_GLOBAL_SUBPAGE_MSG_ID_STATE_FUNKEY3,
        GUI_MODEL_GLOBAL_SUBPAGE_MSG_ID_STATE_FUNKEY4,
    };
    for (int i = 0; i < 21; i++) {
        gui_msg_sub_t *sub = gui_msg_create_sub(ids[i]);
        if (sub != NULL) {
            lv_subject_init_pointer(sub->subject, &guider_msg_data);
        }
    }
}

void gui_model_global_subpage_msg_init_ui()
{
}

void gui_model_global_subpage_msg_init_events()
{
    void *res = NULL;
    _gui_msg_status_t status[21] = {
        {GUI_MODEL_GLOBAL_SUBPAGE_MSG_ID_SUBPAGE_ICON, 0, 0},
        {GUI_MODEL_GLOBAL_SUBPAGE_MSG_ID_FUNCKEY1, 0, 0},
        {GUI_MODEL_GLOBAL_SUBPAGE_MSG_ID_FUNCKEY2, 0, 0},
        {GUI_MODEL_GLOBAL_SUBPAGE_MSG_ID_FUNCKEY3, 0, 0},
        {GUI_MODEL_GLOBAL_SUBPAGE_MSG_ID_FUNCKEY4, 0, 0},
        {GUI_MODEL_GLOBAL_SUBPAGE_MSG_ID_TITLE, 0, 0},
        {GUI_MODEL_GLOBAL_SUBPAGE_MSG_ID_HIDE_FUNCKEY1, 0, 0},
        {GUI_MODEL_GLOBAL_SUBPAGE_MSG_ID_HIDE_FUNCKEY2, 0, 0},
        {GUI_MODEL_GLOBAL_SUBPAGE_MSG_ID_HIDE_FUNCKEY3, 0, 0},
        {GUI_MODEL_GLOBAL_SUBPAGE_MSG_ID_HIDE_FUNCKEY4, 0, 0},
        {GUI_MODEL_GLOBAL_SUBPAGE_MSG_ID_SHOW_FUNCKEY1, 0, 0},
        {GUI_MODEL_GLOBAL_SUBPAGE_MSG_ID_SHOW_FUNCKEY2, 0, 0},
        {GUI_MODEL_GLOBAL_SUBPAGE_MSG_ID_SHOW_FUNCKEY3, 0, 0},
        {GUI_MODEL_GLOBAL_SUBPAGE_MSG_ID_SHOW_FUNCKEY4, 0, 0},
        {GUI_MODEL_GLOBAL_SUBPAGE_MSG_ID_ROLLER_OPT, 0, 0},
        {GUI_MODEL_GLOBAL_SUBPAGE_MSG_ID_SHOW_ROLLER, 0, 0},
        {GUI_MODEL_GLOBAL_SUBPAGE_MSG_ID_HIDE_ROLLER, 0, 0},
        {GUI_MODEL_GLOBAL_SUBPAGE_MSG_ID_STATE_FUNKEY1, 0, 0},
        {GUI_MODEL_GLOBAL_SUBPAGE_MSG_ID_STATE_FUNKEY2, 0, 0},
        {GUI_MODEL_GLOBAL_SUBPAGE_MSG_ID_STATE_FUNKEY3, 0, 0},
        {GUI_MODEL_GLOBAL_SUBPAGE_MSG_ID_STATE_FUNKEY4, 0, 0},
    };

    for (int i = 0; i < 21; i++) {
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

    lv_subject_t *subject_roller_opt = gui_msg_get_subject(GUI_MODEL_GLOBAL_SUBPAGE_MSG_ID_ROLLER_OPT);
    if (guider_ui.video_rec) {
        lv_ui_video_rec *ui_scr = ui_get_scr_ptr(&guider_ui, GUI_SCREEN_VIDEO_REC);
        gui_msg_setup_component(true, false, subject_roller_opt, ui_scr->video_rec_roller_mutifunc, &guider_msg_data, gui_msg_set_roller_roller_name_by_string_cb, GUI_MODEL_GLOBAL_SUBPAGE_MSG_ID_ROLLER_OPT, GUI_MSG_ACCESS_GET, VALUE_STRING, NULL);


        for (int i = 0; i < 21; i++) {
            if (status[i].msg_id == GUI_MODEL_GLOBAL_SUBPAGE_MSG_ID_ROLLER_OPT) {
                status[i].is_subscribe = 1;
            }
        }
    }
    if (guider_ui.sys_setting) {
        lv_ui_sys_setting *ui_scr = ui_get_scr_ptr(&guider_ui, GUI_SCREEN_SYS_SETTING);
        gui_msg_setup_component(true, false, subject_roller_opt, ui_scr->sys_setting_roller_mutifunc, &guider_msg_data, gui_msg_set_roller_roller_name_by_string_cb, GUI_MODEL_GLOBAL_SUBPAGE_MSG_ID_ROLLER_OPT, GUI_MSG_ACCESS_GET, VALUE_STRING, NULL);


        for (int i = 0; i < 21; i++) {
            if (status[i].msg_id == GUI_MODEL_GLOBAL_SUBPAGE_MSG_ID_ROLLER_OPT) {
                status[i].is_subscribe = 1;
            }
        }
    }
    if (guider_ui.video_photo) {
        lv_ui_video_photo *ui_scr = ui_get_scr_ptr(&guider_ui, GUI_SCREEN_VIDEO_PHOTO);
        gui_msg_setup_component(true, false, subject_roller_opt, ui_scr->video_photo_roller_mutifunc, &guider_msg_data, gui_msg_set_roller_roller_name_by_string_cb, GUI_MODEL_GLOBAL_SUBPAGE_MSG_ID_ROLLER_OPT, GUI_MSG_ACCESS_GET, VALUE_STRING, NULL);


        for (int i = 0; i < 21; i++) {
            if (status[i].msg_id == GUI_MODEL_GLOBAL_SUBPAGE_MSG_ID_ROLLER_OPT) {
                status[i].is_subscribe = 1;
            }
        }
    }

    for (int i = 0; i < 21; i++) {
        if (status[i].is_subscribe == 0 && status[i].is_unsubscribe == 1) {
            gui_msg_subscribe_change(status[i].msg_id, GUI_MSG_UNSUBSCRIBE);
        } else if (status[i].is_subscribe == 1 && status[i].is_unsubscribe == 0) {
            gui_msg_subscribe_change(status[i].msg_id, GUI_MSG_SUBSCRIBE);
        }
    }
}

void gui_model_global_subpage_msg_unsubscribe()
{
    _gui_msg_status_t status[21] = {
        {GUI_MODEL_GLOBAL_SUBPAGE_MSG_ID_SUBPAGE_ICON, 0, 0},
        {GUI_MODEL_GLOBAL_SUBPAGE_MSG_ID_FUNCKEY1, 0, 0},
        {GUI_MODEL_GLOBAL_SUBPAGE_MSG_ID_FUNCKEY2, 0, 0},
        {GUI_MODEL_GLOBAL_SUBPAGE_MSG_ID_FUNCKEY3, 0, 0},
        {GUI_MODEL_GLOBAL_SUBPAGE_MSG_ID_FUNCKEY4, 0, 0},
        {GUI_MODEL_GLOBAL_SUBPAGE_MSG_ID_TITLE, 0, 0},
        {GUI_MODEL_GLOBAL_SUBPAGE_MSG_ID_HIDE_FUNCKEY1, 0, 0},
        {GUI_MODEL_GLOBAL_SUBPAGE_MSG_ID_HIDE_FUNCKEY2, 0, 0},
        {GUI_MODEL_GLOBAL_SUBPAGE_MSG_ID_HIDE_FUNCKEY3, 0, 0},
        {GUI_MODEL_GLOBAL_SUBPAGE_MSG_ID_HIDE_FUNCKEY4, 0, 0},
        {GUI_MODEL_GLOBAL_SUBPAGE_MSG_ID_SHOW_FUNCKEY1, 0, 0},
        {GUI_MODEL_GLOBAL_SUBPAGE_MSG_ID_SHOW_FUNCKEY2, 0, 0},
        {GUI_MODEL_GLOBAL_SUBPAGE_MSG_ID_SHOW_FUNCKEY3, 0, 0},
        {GUI_MODEL_GLOBAL_SUBPAGE_MSG_ID_SHOW_FUNCKEY4, 0, 0},
        {GUI_MODEL_GLOBAL_SUBPAGE_MSG_ID_ROLLER_OPT, 0, 0},
        {GUI_MODEL_GLOBAL_SUBPAGE_MSG_ID_SHOW_ROLLER, 0, 0},
        {GUI_MODEL_GLOBAL_SUBPAGE_MSG_ID_HIDE_ROLLER, 0, 0},
        {GUI_MODEL_GLOBAL_SUBPAGE_MSG_ID_STATE_FUNKEY1, 0, 0},
        {GUI_MODEL_GLOBAL_SUBPAGE_MSG_ID_STATE_FUNKEY2, 0, 0},
        {GUI_MODEL_GLOBAL_SUBPAGE_MSG_ID_STATE_FUNKEY3, 0, 0},
        {GUI_MODEL_GLOBAL_SUBPAGE_MSG_ID_STATE_FUNKEY4, 0, 0},
    };
    for (int i = 0; i < 21; i++) {
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

    for (int i = 0; i < 21; i++) {
        if (status[i].is_unsubscribe == 1) {
            gui_msg_subscribe_change(status[i].msg_id, GUI_MSG_UNSUBSCRIBE);
        }
    }
}

gui_msg_status_t gui_model_global_subpage_msg_send(int32_t msg_id, void *value, int32_t len)
{
    if (msg_id == GUI_MODEL_GLOBAL_SUBPAGE_MSG_ID) {
    } else {
        gui_msg_data_type_t data_type = VALUE_INT;
        switch (msg_id) {
        case GUI_MODEL_GLOBAL_SUBPAGE_MSG_ID_HIDE_FUNCKEY1:
        case GUI_MODEL_GLOBAL_SUBPAGE_MSG_ID_HIDE_FUNCKEY2:
        case GUI_MODEL_GLOBAL_SUBPAGE_MSG_ID_HIDE_FUNCKEY3:
        case GUI_MODEL_GLOBAL_SUBPAGE_MSG_ID_HIDE_FUNCKEY4:
        case GUI_MODEL_GLOBAL_SUBPAGE_MSG_ID_SHOW_FUNCKEY1:
        case GUI_MODEL_GLOBAL_SUBPAGE_MSG_ID_SHOW_FUNCKEY2:
        case GUI_MODEL_GLOBAL_SUBPAGE_MSG_ID_SHOW_FUNCKEY3:
        case GUI_MODEL_GLOBAL_SUBPAGE_MSG_ID_SHOW_FUNCKEY4:
        case GUI_MODEL_GLOBAL_SUBPAGE_MSG_ID_SHOW_ROLLER:
        case GUI_MODEL_GLOBAL_SUBPAGE_MSG_ID_HIDE_ROLLER: {
            data_type = VALUE_INT;
            guider_msg_data.value_array.ptr = value;
            guider_msg_data.value_array.len = len;
        }
        break;
        case GUI_MODEL_GLOBAL_SUBPAGE_MSG_ID_STATE_FUNKEY1:
        case GUI_MODEL_GLOBAL_SUBPAGE_MSG_ID_STATE_FUNKEY2:
        case GUI_MODEL_GLOBAL_SUBPAGE_MSG_ID_STATE_FUNKEY3:
        case GUI_MODEL_GLOBAL_SUBPAGE_MSG_ID_STATE_FUNKEY4: {
            data_type = VALUE_INT;
            guider_msg_data.value_array.ptr = value;
            guider_msg_data.value_array.len = len;
        }
        break;
        case GUI_MODEL_GLOBAL_SUBPAGE_MSG_ID_SUBPAGE_ICON: {
            data_type = VALUE_INT;
            guider_msg_data.value_array.ptr = value;
            guider_msg_data.value_array.len = len;
        }
        break;
        case GUI_MODEL_GLOBAL_SUBPAGE_MSG_ID_FUNCKEY1:
        case GUI_MODEL_GLOBAL_SUBPAGE_MSG_ID_FUNCKEY2:
        case GUI_MODEL_GLOBAL_SUBPAGE_MSG_ID_FUNCKEY3:
        case GUI_MODEL_GLOBAL_SUBPAGE_MSG_ID_FUNCKEY4:
        case GUI_MODEL_GLOBAL_SUBPAGE_MSG_ID_TITLE:
        case GUI_MODEL_GLOBAL_SUBPAGE_MSG_ID_ROLLER_OPT: {
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
