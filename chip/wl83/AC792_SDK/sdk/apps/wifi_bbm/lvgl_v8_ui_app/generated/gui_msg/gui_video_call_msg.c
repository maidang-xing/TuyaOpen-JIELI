/*Generate Code, Do NOT Edit!*/
#include "./gui_video_call_msg.h"
#if LV_USE_OBSERVER

static lv_ll_t subs_ll;
static lv_ll_t timer_ll;

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
void gui_video_call_msg_wifi_rssi_timer_cb(lv_timer_t *timer)
{
    gui_msg_action_change(GUI_VIDEO_CALL_MSG_ID_WIFI_RSSI, GUI_MSG_ACCESS_GET, &guider_msg_data, VALUE_INT);
    lv_subject_t *subject = gui_msg_get_subject(GUI_VIDEO_CALL_MSG_ID_WIFI_RSSI);
    if (subject == NULL) {
        return;
    }
    lv_subject_set_pointer(subject, &guider_msg_data);
}
void gui_video_call_msg_wifi_stats_debug_timer_cb(lv_timer_t *timer)
{
    gui_msg_action_change(GUI_VIDEO_CALL_MSG_ID_WIFI_STATS_DEBUG, GUI_MSG_ACCESS_GET, &guider_msg_data, VALUE_STRING);
    lv_subject_t *subject = gui_msg_get_subject(GUI_VIDEO_CALL_MSG_ID_WIFI_STATS_DEBUG);
    if (subject == NULL) {
        return;
    }
    lv_subject_set_pointer(subject, &guider_msg_data);
}


GUI_WEAK int gui_video_call_msg_wifi_rssi_cb(gui_msg_action_t access, gui_msg_data_t *data, gui_msg_data_type_t type)
{
    static int32_t wifi_rssi_var = 0;
    if (access == GUI_MSG_ACCESS_SET) {
        wifi_rssi_var = data->value_int;
    }
    data->value_int = wifi_rssi_var;
    return 0;
}
GUI_WEAK int gui_video_call_msg_video_fps_debug_cb(gui_msg_action_t access, gui_msg_data_t *data, gui_msg_data_type_t type)
{
    char video_fps_debug_init_var[] = "";
    static bool video_fps_debug_is_init = false;
    static char *video_fps_debug_var = NULL;
    if (video_fps_debug_is_init == false) {
        video_fps_debug_var = lv_mem_alloc(strlen(video_fps_debug_init_var) + 1);
        strcpy(video_fps_debug_var, video_fps_debug_init_var);
        video_fps_debug_is_init = true;
    }
    if (access == GUI_MSG_ACCESS_SET) {
        lv_mem_free(video_fps_debug_var);
        video_fps_debug_var = lv_mem_alloc(strlen(data->value_string) + 1);
        strcpy(video_fps_debug_var, data->value_string);
    }
    data->value_string = video_fps_debug_var;
    return 0;
}
GUI_WEAK int gui_video_call_msg_wifi_stats_debug_cb(gui_msg_action_t access, gui_msg_data_t *data, gui_msg_data_type_t type)
{
    char wifi_stats_debug_init_var[] = "";
    static bool wifi_stats_debug_is_init = false;
    static char *wifi_stats_debug_var = NULL;
    if (wifi_stats_debug_is_init == false) {
        wifi_stats_debug_var = lv_mem_alloc(strlen(wifi_stats_debug_init_var) + 1);
        strcpy(wifi_stats_debug_var, wifi_stats_debug_init_var);
        wifi_stats_debug_is_init = true;
    }
    if (access == GUI_MSG_ACCESS_SET) {
        lv_mem_free(wifi_stats_debug_var);
        wifi_stats_debug_var = lv_mem_alloc(strlen(data->value_string) + 1);
        strcpy(wifi_stats_debug_var, data->value_string);
    }
    data->value_string = wifi_stats_debug_var;
    return 0;
}

void gui_video_call_msg_init(lv_ui *ui)
{
    gui_msg_sub_t *sub;
    sub = gui_msg_create_sub(GUI_VIDEO_CALL_MSG_ID_WIFI_RSSI);
    if (sub != NULL) {
        lv_subject_init_pointer(sub->subject, &guider_msg_data);
    }
    sub = gui_msg_create_sub(GUI_VIDEO_CALL_MSG_ID_VIDEO_FPS_DEBUG);
    if (sub != NULL) {
        lv_subject_init_pointer(sub->subject, &guider_msg_data);
    }
    sub = gui_msg_create_sub(GUI_VIDEO_CALL_MSG_ID_WIFI_STATS_DEBUG);
    if (sub != NULL) {
        lv_subject_init_pointer(sub->subject, &guider_msg_data);
    }
    _lv_ll_init(&timer_ll, sizeof(timer_dsc_t));
}

void gui_video_call_msg_init_ui()
{
}

void gui_video_call_msg_init_events()
{
    void *res = NULL;
    _gui_msg_status_t status[3] = {
        {GUI_VIDEO_CALL_MSG_ID_WIFI_RSSI, 0, 0},
        {GUI_VIDEO_CALL_MSG_ID_VIDEO_FPS_DEBUG, 0, 0},
        {GUI_VIDEO_CALL_MSG_ID_WIFI_STATS_DEBUG, 0, 0},
    };
    lv_timer_t *timer = NULL;
    bool wifi_rssi_timer_enable = false;
    bool wifi_stats_debug_timer_enable = false;
    delete_all_timer();

    for (int i = 0; i < 3; i++) {
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

    lv_subject_t *subject_wifi_rssi = gui_msg_get_subject(GUI_VIDEO_CALL_MSG_ID_WIFI_RSSI);
    lv_subject_t *subject_video_fps_debug = gui_msg_get_subject(GUI_VIDEO_CALL_MSG_ID_VIDEO_FPS_DEBUG);
    lv_subject_t *subject_wifi_stats_debug = gui_msg_get_subject(GUI_VIDEO_CALL_MSG_ID_WIFI_STATS_DEBUG);
    if (guider_ui.video_call) {
        lv_ui_video_call *ui_scr = ui_get_scr_ptr(&guider_ui, GUI_SCREEN_VIDEO_CALL);
        gui_msg_setup_component(true, false, subject_video_fps_debug, ui_scr->video_call_lbl_1, &guider_msg_data, gui_msg_set_label_text_by_string_cb, GUI_VIDEO_CALL_MSG_ID_VIDEO_FPS_DEBUG, GUI_MSG_ACCESS_GET, VALUE_STRING, NULL);

        gui_msg_setup_component(true, false, subject_wifi_stats_debug, ui_scr->video_call_lbl_2, &guider_msg_data, gui_msg_set_label_text_by_string_cb, GUI_VIDEO_CALL_MSG_ID_WIFI_STATS_DEBUG, GUI_MSG_ACCESS_GET, VALUE_STRING, NULL);

        gui_msg_setup_component(true, false, subject_wifi_rssi, ui_scr->video_call_imglist_1, &guider_msg_data, gui_msg_set_imglist_selected_index_by_int32_cb, GUI_VIDEO_CALL_MSG_ID_WIFI_RSSI, GUI_MSG_ACCESS_GET, VALUE_INT, NULL);


        for (int i = 0; i < 3; i++) {
            if (status[i].msg_id == GUI_VIDEO_CALL_MSG_ID_VIDEO_FPS_DEBUG) {
                status[i].is_subscribe = 1;
            }
            if (status[i].msg_id == GUI_VIDEO_CALL_MSG_ID_WIFI_STATS_DEBUG) {
                status[i].is_subscribe = 1;
            }
            if (status[i].msg_id == GUI_VIDEO_CALL_MSG_ID_WIFI_RSSI) {
                status[i].is_subscribe = 1;
            }
        }

        wifi_stats_debug_timer_enable = true;
        wifi_rssi_timer_enable = true;
    }

    for (int i = 0; i < 3; i++) {
        if (status[i].is_subscribe == 0 && status[i].is_unsubscribe == 1) {
            gui_msg_subscribe_change(status[i].msg_id, GUI_MSG_UNSUBSCRIBE);
        } else if (status[i].is_subscribe == 1 && status[i].is_unsubscribe == 0) {
            gui_msg_subscribe_change(status[i].msg_id, GUI_MSG_SUBSCRIBE);
        }
    }
    if (wifi_rssi_timer_enable) {
        timer = lv_timer_create(gui_video_call_msg_wifi_rssi_timer_cb, 1000, NULL);
        insert_timer(&timer_ll, timer);
    }
    if (wifi_stats_debug_timer_enable) {
        timer = lv_timer_create(gui_video_call_msg_wifi_stats_debug_timer_cb, 1000, NULL);
        insert_timer(&timer_ll, timer);
    }
}

void gui_video_call_msg_unsubscribe()
{
    _gui_msg_status_t status[3] = {
        {GUI_VIDEO_CALL_MSG_ID_WIFI_RSSI, 0, 0},
        {GUI_VIDEO_CALL_MSG_ID_VIDEO_FPS_DEBUG, 0, 0},
        {GUI_VIDEO_CALL_MSG_ID_WIFI_STATS_DEBUG, 0, 0},
    };
    for (int i = 0; i < 3; i++) {
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

    for (int i = 0; i < 3; i++) {
        if (status[i].is_unsubscribe == 1) {
            gui_msg_subscribe_change(status[i].msg_id, GUI_MSG_UNSUBSCRIBE);
        }
    }
}

gui_msg_data_t *gui_video_call_msg_get(int32_t msg_id)
{
    switch (msg_id) {
    case GUI_VIDEO_CALL_MSG_ID_WIFI_RSSI: {
        gui_video_call_msg_wifi_rssi_cb(GUI_MSG_ACCESS_GET, &guider_msg_data, VALUE_INT);
        break;
    }
    case GUI_VIDEO_CALL_MSG_ID_VIDEO_FPS_DEBUG: {
        gui_video_call_msg_video_fps_debug_cb(GUI_MSG_ACCESS_GET, &guider_msg_data, VALUE_STRING);
        break;
    }
    case GUI_VIDEO_CALL_MSG_ID_WIFI_STATS_DEBUG: {
        gui_video_call_msg_wifi_stats_debug_cb(GUI_MSG_ACCESS_GET, &guider_msg_data, VALUE_STRING);
        break;
    }
    default:
        return NULL;
    }
    return &guider_msg_data;
}

void gui_video_call_msg_action_change(int32_t msg_id, gui_msg_action_t access, gui_msg_data_t *data, gui_msg_data_type_t type)
{
    switch (msg_id) {
    case GUI_VIDEO_CALL_MSG_ID_WIFI_RSSI: {
        gui_video_call_msg_wifi_rssi_cb(access, data, type);
        break;
    }
    case GUI_VIDEO_CALL_MSG_ID_VIDEO_FPS_DEBUG: {
        gui_video_call_msg_video_fps_debug_cb(access, data, type);
        break;
    }
    case GUI_VIDEO_CALL_MSG_ID_WIFI_STATS_DEBUG: {
        gui_video_call_msg_wifi_stats_debug_cb(access, data, type);
        break;
    }
    default: {
        break;
    }
    }
}

gui_msg_status_t gui_video_call_msg_send(int32_t msg_id, void *value, int32_t len)
{
    if (msg_id == GUI_VIDEO_CALL_MSG_ID) {
    } else {
        gui_msg_data_type_t data_type = VALUE_INT;
        switch (msg_id) {
        case GUI_VIDEO_CALL_MSG_ID_WIFI_RSSI: {
            data_type = VALUE_INT;
            guider_msg_data.value_array.ptr = value;
            guider_msg_data.value_array.len = len;
            break;
        }
        case GUI_VIDEO_CALL_MSG_ID_VIDEO_FPS_DEBUG: {
            data_type = VALUE_STRING;
            guider_msg_data.value_array.ptr = value;
            guider_msg_data.value_array.len = len;
            break;
        }
        case GUI_VIDEO_CALL_MSG_ID_WIFI_STATS_DEBUG: {
            data_type = VALUE_STRING;
            guider_msg_data.value_array.ptr = value;
            guider_msg_data.value_array.len = len;
            break;
        }
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
