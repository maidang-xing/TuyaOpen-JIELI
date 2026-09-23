#include "app_config.h"
#ifdef CONFIG_UI_STYLE_LY_ENABLE
/*Generate Code, Do NOT Edit!*/
#include "./gui_model_main_msg.h"
#if LV_USE_OBSERVER

static lv_ll_t subs_ll;
static lv_ll_t timer_ll;

#if LV_USE_GUIBUILDER_SIMULATOR
_gui_msg_entry_t gui_model_main_msg_entry_table[] = {
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
};
#endif

typedef struct {
    lv_timer_t *timer;
} timer_dsc_t;
static void delete_all_timer()
{
    timer_dsc_t *head = _lv_ll_get_head(&timer_ll);
    while (head != NULL) {
        timer_dsc_t *next = _lv_ll_get_next(&timer_ll, head);
        if (head->timer != NULL) {
            lv_timer_del(head->timer);
        }
        _lv_ll_remove(&timer_ll, head);
        lv_mem_free(head);
        head = next;
    }
}
static timer_dsc_t *insert_timer(lv_ll_t *ll_p, lv_timer_t *timer)
{
    timer_dsc_t *tail = _lv_ll_ins_tail(ll_p);
    tail->timer = timer;
    return tail;
}
void gui_model_main_msg_systime_timer_cb(lv_timer_t *timer)
{
    gui_msg_action_change(GUI_MODEL_MAIN_MSG_ID_SYSTIME, GUI_MSG_ACCESS_GET, &guider_msg_data, VALUE_TIME);
    lv_subject_t *subject = gui_msg_get_subject(GUI_MODEL_MAIN_MSG_ID_SYSTIME);
    if (subject == NULL) {
        return;
    }
    lv_subject_set_pointer(subject, &guider_msg_data);
}

void gui_model_main_msg_video_rec_digitclock_1_set_digit_clock_time_cb(lv_observer_t *observer, lv_subject_t *subject)
{
    lv_obj_t *obj = lv_observer_get_target_obj(observer);
    if (obj == NULL || lv_obj_is_valid(obj) == false) {
        return;
    }

    gui_msg_data_t *data = (gui_msg_data_t *)observer->user_data;
    struct tm time = data->value_time;
    lv_label_set_text_fmt(obj, "%04d-%02d-%02d %02d:%02d:%02d", time.tm_year + 1900, GUI_TM_MON(time.tm_mon), time.tm_mday, time.tm_hour, time.tm_min, time.tm_sec);
}
void gui_model_main_msg_video_rec_img_bat_set_img_path_cb(lv_observer_t *observer, lv_subject_t *subject)
{
    lv_obj_t *obj = lv_observer_get_target_obj(observer);
    if (obj == NULL || lv_obj_is_valid(obj) == false) {
        return;
    }

    gui_msg_data_t *data = (gui_msg_data_t *)observer->user_data;
    lv_img_set_src(obj, gui_get_res_path(data->value_int));
}
void gui_model_main_msg_video_photo_img_bat_icon_set_img_path_cb(lv_observer_t *observer, lv_subject_t *subject)
{
    lv_obj_t *obj = lv_observer_get_target_obj(observer);
    if (obj == NULL || lv_obj_is_valid(obj) == false) {
        return;
    }

    gui_msg_data_t *data = (gui_msg_data_t *)observer->user_data;
    lv_img_set_src(obj, gui_get_res_path(data->value_int));
}
void gui_model_main_msg_video_photo_digitclock_1_set_digit_clock_time_cb(lv_observer_t *observer, lv_subject_t *subject)
{
    lv_obj_t *obj = lv_observer_get_target_obj(observer);
    if (obj == NULL || lv_obj_is_valid(obj) == false) {
        return;
    }

    gui_msg_data_t *data = (gui_msg_data_t *)observer->user_data;
    struct tm time = data->value_time;
    lv_label_set_text_fmt(obj, "%04d-%02d-%02d %02d:%02d:%02d", time.tm_year + 1900, GUI_TM_MON(time.tm_mon), time.tm_mday, time.tm_hour, time.tm_min, time.tm_sec);
}

GUI_WEAK int gui_model_main_msg_systime_cb(gui_msg_action_t access, gui_msg_data_t *data, gui_msg_data_type_t type)
{
    static struct tm systime_var = {
        .tm_year = 124,
        .tm_mon = 5,
        .tm_mday = 24,
        .tm_hour = 20,
        .tm_min = 52,
        .tm_sec = 7,
    };
    _gui_msg_tm_cb(&systime_var, false, access, data);
    return 0;
}
GUI_WEAK int gui_model_main_msg_sd_icon_cb(gui_msg_action_t access, gui_msg_data_t *data, gui_msg_data_type_t type)
{
    static int32_t sd_icon_var = RES_SD_CLOSE;
    _gui_msg_int32_cb(&sd_icon_var, access, data);
    return 0;
}
GUI_WEAK int gui_model_main_msg_battery_cb(gui_msg_action_t access, gui_msg_data_t *data, gui_msg_data_type_t type)
{
    static int32_t battery_var = RES_CHAR;
    _gui_msg_int32_cb(&battery_var, access, data);
    return 0;
}
GUI_WEAK int gui_model_main_msg_sys_prompt_cb(gui_msg_action_t access, gui_msg_data_t *data, gui_msg_data_type_t type)
{
    char sys_prompt_init_var[] = "";
    static bool sys_prompt_is_init = false;
    static char *sys_prompt_var = NULL;
    _gui_msg_char_array_cb(&sys_prompt_var, sys_prompt_init_var, &sys_prompt_is_init, access, data);
    return 0;
}
GUI_WEAK int gui_model_main_msg_headlamp_cb(gui_msg_action_t access, gui_msg_data_t *data, gui_msg_data_type_t type)
{
    static bool headlamp_var = false;
    _gui_msg_bool_cb(&headlamp_var, access, data);
    return 0;
}
GUI_WEAK int gui_model_main_msg_sys_prompt_show_cb(gui_msg_action_t access, gui_msg_data_t *data, gui_msg_data_type_t type)
{
    static bool sys_prompt_show_var = false;
    _gui_msg_bool_cb(&sys_prompt_show_var, access, data);
    return 0;
}
GUI_WEAK int gui_model_main_msg_show_del_btn_cb(gui_msg_action_t access, gui_msg_data_t *data, gui_msg_data_type_t type)
{
    static lv_obj_flag_t show_del_btn_var = 0;
    _gui_msg_obj_flag_cb(&show_del_btn_var, access, data);
    return 0;
}
GUI_WEAK int gui_model_main_msg_hide_del_btn_cb(gui_msg_action_t access, gui_msg_data_t *data, gui_msg_data_type_t type)
{
    static lv_obj_flag_t hide_del_btn_var = 0;
    _gui_msg_obj_flag_cb(&hide_del_btn_var, access, data);
    return 0;
}
GUI_WEAK int gui_model_main_msg_show_home_btn_cb(gui_msg_action_t access, gui_msg_data_t *data, gui_msg_data_type_t type)
{
    static lv_obj_flag_t show_home_btn_var = 0;
    _gui_msg_obj_flag_cb(&show_home_btn_var, access, data);
    return 0;
}
GUI_WEAK int gui_model_main_msg_hide_home_btn_cb(gui_msg_action_t access, gui_msg_data_t *data, gui_msg_data_type_t type)
{
    static lv_obj_flag_t hide_home_btn_var = 0;
    _gui_msg_obj_flag_cb(&hide_home_btn_var, access, data);
    return 0;
}

void gui_model_main_msg_init(lv_ui *ui)
{
    int32_t ids[10] = {
        GUI_MODEL_MAIN_MSG_ID_SYSTIME,
        GUI_MODEL_MAIN_MSG_ID_SD_ICON,
        GUI_MODEL_MAIN_MSG_ID_BATTERY,
        GUI_MODEL_MAIN_MSG_ID_SYS_PROMPT,
        GUI_MODEL_MAIN_MSG_ID_HEADLAMP,
        GUI_MODEL_MAIN_MSG_ID_SYS_PROMPT_SHOW,
        GUI_MODEL_MAIN_MSG_ID_SHOW_DEL_BTN,
        GUI_MODEL_MAIN_MSG_ID_HIDE_DEL_BTN,
        GUI_MODEL_MAIN_MSG_ID_SHOW_HOME_BTN,
        GUI_MODEL_MAIN_MSG_ID_HIDE_HOME_BTN,
    };
    for (int i = 0; i < 10; i++) {
        gui_msg_sub_t *sub = gui_msg_create_sub(ids[i]);
        if (sub != NULL) {
            lv_subject_init_pointer(sub->subject, &guider_msg_data);
        }
    }
    _lv_ll_init(&timer_ll, sizeof(timer_dsc_t));
}

void gui_model_main_msg_init_ui()
{
}

void gui_model_main_msg_init_events()
{
    void *res = NULL;
    _gui_msg_status_t status[10] = {
        {GUI_MODEL_MAIN_MSG_ID_SYSTIME, 0, 0},
        {GUI_MODEL_MAIN_MSG_ID_SD_ICON, 0, 0},
        {GUI_MODEL_MAIN_MSG_ID_BATTERY, 0, 0},
        {GUI_MODEL_MAIN_MSG_ID_SYS_PROMPT, 0, 0},
        {GUI_MODEL_MAIN_MSG_ID_HEADLAMP, 0, 0},
        {GUI_MODEL_MAIN_MSG_ID_SYS_PROMPT_SHOW, 0, 0},
        {GUI_MODEL_MAIN_MSG_ID_SHOW_DEL_BTN, 0, 0},
        {GUI_MODEL_MAIN_MSG_ID_HIDE_DEL_BTN, 0, 0},
        {GUI_MODEL_MAIN_MSG_ID_SHOW_HOME_BTN, 0, 0},
        {GUI_MODEL_MAIN_MSG_ID_HIDE_HOME_BTN, 0, 0},
    };
    lv_timer_t *timer = NULL;
    bool systime_timer_enable = false;
    delete_all_timer();

    for (int i = 0; i < 10; i++) {
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

    lv_subject_t *subject_systime = gui_msg_get_subject(GUI_MODEL_MAIN_MSG_ID_SYSTIME);
    lv_subject_t *subject_battery = gui_msg_get_subject(GUI_MODEL_MAIN_MSG_ID_BATTERY);
    lv_subject_t *subject_sys_prompt = gui_msg_get_subject(GUI_MODEL_MAIN_MSG_ID_SYS_PROMPT);
    if (guider_ui.video_rec) {
        lv_ui_video_rec *ui_scr = ui_get_scr_ptr(&guider_ui, GUI_SCREEN_VIDEO_REC);
        gui_msg_setup_component(true, false, subject_systime, ui_scr->video_rec_digitclock_1, &guider_msg_data, gui_model_main_msg_video_rec_digitclock_1_set_digit_clock_time_cb, GUI_MODEL_MAIN_MSG_ID_SYSTIME, GUI_MSG_ACCESS_GET, VALUE_TIME, NULL);

        gui_msg_setup_component(true, false, subject_battery, ui_scr->video_rec_img_bat, &guider_msg_data, gui_model_main_msg_video_rec_img_bat_set_img_path_cb, GUI_MODEL_MAIN_MSG_ID_BATTERY, GUI_MSG_ACCESS_GET, VALUE_INT, NULL);


        for (int i = 0; i < 10; i++) {
            if (status[i].msg_id == GUI_MODEL_MAIN_MSG_ID_SYSTIME) {
                status[i].is_subscribe = 1;
            }
            if (status[i].msg_id == GUI_MODEL_MAIN_MSG_ID_BATTERY) {
                status[i].is_subscribe = 1;
            }
        }

        systime_timer_enable = true;
    }
    if (guider_ui.sys_prompt) {
        lv_ui_sys_prompt *ui_scr = ui_get_scr_ptr(&guider_ui, GUI_SCREEN_SYS_PROMPT);
        gui_msg_setup_component(true, false, subject_sys_prompt, ui_scr->sys_prompt_lbl_warn, &guider_msg_data, gui_msg_set_label_text_by_string_cb, GUI_MODEL_MAIN_MSG_ID_SYS_PROMPT, GUI_MSG_ACCESS_GET, VALUE_STRING, NULL);


        for (int i = 0; i < 10; i++) {
            if (status[i].msg_id == GUI_MODEL_MAIN_MSG_ID_SYS_PROMPT) {
                status[i].is_subscribe = 1;
            }
        }
    }
    if (guider_ui.video_photo) {
        lv_ui_video_photo *ui_scr = ui_get_scr_ptr(&guider_ui, GUI_SCREEN_VIDEO_PHOTO);
        gui_msg_setup_component(true, false, subject_battery, ui_scr->video_photo_img_bat_icon, &guider_msg_data, gui_model_main_msg_video_photo_img_bat_icon_set_img_path_cb, GUI_MODEL_MAIN_MSG_ID_BATTERY, GUI_MSG_ACCESS_GET, VALUE_INT, NULL);

        gui_msg_setup_component(true, false, subject_systime, ui_scr->video_photo_digitclock_1, &guider_msg_data, gui_model_main_msg_video_photo_digitclock_1_set_digit_clock_time_cb, GUI_MODEL_MAIN_MSG_ID_SYSTIME, GUI_MSG_ACCESS_GET, VALUE_TIME, NULL);


        for (int i = 0; i < 10; i++) {
            if (status[i].msg_id == GUI_MODEL_MAIN_MSG_ID_BATTERY) {
                status[i].is_subscribe = 1;
            }
            if (status[i].msg_id == GUI_MODEL_MAIN_MSG_ID_SYSTIME) {
                status[i].is_subscribe = 1;
            }
        }

        systime_timer_enable = true;
    }
    if (guider_ui.sys_popwin) {
        lv_ui_sys_popwin *ui_scr = ui_get_scr_ptr(&guider_ui, GUI_SCREEN_SYS_POPWIN);
        gui_msg_setup_component(true, false, subject_sys_prompt, ui_scr->sys_popwin_lbl_1, &guider_msg_data, gui_msg_set_label_text_by_string_cb, GUI_MODEL_MAIN_MSG_ID_SYS_PROMPT, GUI_MSG_ACCESS_GET, VALUE_STRING, NULL);


        for (int i = 0; i < 10; i++) {
            if (status[i].msg_id == GUI_MODEL_MAIN_MSG_ID_SYS_PROMPT) {
                status[i].is_subscribe = 1;
            }
        }
    }

    for (int i = 0; i < 10; i++) {
        if (status[i].is_subscribe == 0 && status[i].is_unsubscribe == 1) {
            gui_msg_subscribe_change(status[i].msg_id, GUI_MSG_UNSUBSCRIBE);
        } else if (status[i].is_subscribe == 1 && status[i].is_unsubscribe == 0) {
            gui_msg_subscribe_change(status[i].msg_id, GUI_MSG_SUBSCRIBE);
        }
    }
    if (systime_timer_enable) {
        timer = lv_timer_create(gui_model_main_msg_systime_timer_cb, 1000, NULL);
        insert_timer(&timer_ll, timer);
    }
}

void gui_model_main_msg_unsubscribe()
{
    _gui_msg_status_t status[10] = {
        {GUI_MODEL_MAIN_MSG_ID_SYSTIME, 0, 0},
        {GUI_MODEL_MAIN_MSG_ID_SD_ICON, 0, 0},
        {GUI_MODEL_MAIN_MSG_ID_BATTERY, 0, 0},
        {GUI_MODEL_MAIN_MSG_ID_SYS_PROMPT, 0, 0},
        {GUI_MODEL_MAIN_MSG_ID_HEADLAMP, 0, 0},
        {GUI_MODEL_MAIN_MSG_ID_SYS_PROMPT_SHOW, 0, 0},
        {GUI_MODEL_MAIN_MSG_ID_SHOW_DEL_BTN, 0, 0},
        {GUI_MODEL_MAIN_MSG_ID_HIDE_DEL_BTN, 0, 0},
        {GUI_MODEL_MAIN_MSG_ID_SHOW_HOME_BTN, 0, 0},
        {GUI_MODEL_MAIN_MSG_ID_HIDE_HOME_BTN, 0, 0},
    };
    for (int i = 0; i < 10; i++) {
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

    for (int i = 0; i < 10; i++) {
        if (status[i].is_unsubscribe == 1) {
            gui_msg_subscribe_change(status[i].msg_id, GUI_MSG_UNSUBSCRIBE);
        }
    }
}

gui_msg_status_t gui_model_main_msg_send(int32_t msg_id, void *value, int32_t len)
{
    if (msg_id == GUI_MODEL_MAIN_MSG_ID) {
    } else {
        gui_msg_data_type_t data_type = VALUE_INT;
        switch (msg_id) {
        case GUI_MODEL_MAIN_MSG_ID_SHOW_DEL_BTN:
        case GUI_MODEL_MAIN_MSG_ID_HIDE_DEL_BTN:
        case GUI_MODEL_MAIN_MSG_ID_SHOW_HOME_BTN:
        case GUI_MODEL_MAIN_MSG_ID_HIDE_HOME_BTN: {
            data_type = VALUE_INT;
            guider_msg_data.value_array.ptr = value;
            guider_msg_data.value_array.len = len;
        }
        break;
        case GUI_MODEL_MAIN_MSG_ID_HEADLAMP:
        case GUI_MODEL_MAIN_MSG_ID_SYS_PROMPT_SHOW: {
            data_type = VALUE_BOOL;
            guider_msg_data.value_array.ptr = value;
            guider_msg_data.value_array.len = len;
        }
        break;
        case GUI_MODEL_MAIN_MSG_ID_SD_ICON:
        case GUI_MODEL_MAIN_MSG_ID_BATTERY: {
            data_type = VALUE_INT;
            guider_msg_data.value_array.ptr = value;
            guider_msg_data.value_array.len = len;
        }
        break;
        case GUI_MODEL_MAIN_MSG_ID_SYS_PROMPT: {
            data_type = VALUE_STRING;
            guider_msg_data.value_array.ptr = value;
            guider_msg_data.value_array.len = len;
        }
        break;
        case GUI_MODEL_MAIN_MSG_ID_SYSTIME: {
            data_type = VALUE_TIME;
            if (value) {
                guider_msg_data.value_time = *((struct tm *)value);
            }
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
