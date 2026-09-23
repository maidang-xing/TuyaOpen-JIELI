#include "app_config.h"
#ifdef CONFIG_UI_STYLE_JL_ENABLE
/*Generate Code, Do NOT Edit!*/
#include "./gui_model_msg.h"
#if LV_USE_OBSERVER

static lv_ll_t subs_ll;

void gui_model_msg_video_play_img_prev_file_set_img_path_cb(lv_observer_t *observer, lv_subject_t *subject)
{
    lv_obj_t *obj = lv_observer_get_target_obj(observer);
    if (obj == NULL || lv_obj_is_valid(obj) == false) {
        return;
    }

    gui_msg_data_t *data = (gui_msg_data_t *)observer->user_data;
    lv_img_set_src(obj, gui_get_res_path(data->value_int));
}
void gui_model_msg_video_play_img_next_file_set_img_path_cb(lv_observer_t *observer, lv_subject_t *subject)
{
    lv_obj_t *obj = lv_observer_get_target_obj(observer);
    if (obj == NULL || lv_obj_is_valid(obj) == false) {
        return;
    }

    gui_msg_data_t *data = (gui_msg_data_t *)observer->user_data;
    lv_img_set_src(obj, gui_get_res_path(data->value_int));
}

GUI_WEAK int gui_model_msg_cur_time_cb(gui_msg_action_t access, gui_msg_data_t *data, gui_msg_data_type_t type)
{
    char cur_time_init_var[] = "00:00";
    static bool cur_time_is_init = false;
    static char *cur_time_var = NULL;
    if (cur_time_is_init == false) {
        cur_time_var = lv_mem_alloc(strlen(cur_time_init_var) + 1);
        strcpy(cur_time_var, cur_time_init_var);
        cur_time_is_init = true;
    }
    if (access == GUI_MSG_ACCESS_SET) {
        lv_mem_free(cur_time_var);
        cur_time_var = lv_mem_alloc(strlen(data->value_string) + 1);
        strcpy(cur_time_var, data->value_string);
    }
    data->value_string = cur_time_var;
    return 0;
}
GUI_WEAK int gui_model_msg_prev_file_cb(gui_msg_action_t access, gui_msg_data_t *data, gui_msg_data_type_t type)
{
    static int32_t prev_file_var = RES_SKIP_PREVIOUS;
    if (access == GUI_MSG_ACCESS_SET) {
        prev_file_var = data->value_int;
    }
    data->value_int = prev_file_var;
    return 0;
}
GUI_WEAK int gui_model_msg_next_file_cb(gui_msg_action_t access, gui_msg_data_t *data, gui_msg_data_type_t type)
{
    static int32_t next_file_var = RES_SKIP_NEXT;
    if (access == GUI_MSG_ACCESS_SET) {
        next_file_var = data->value_int;
    }
    data->value_int = next_file_var;
    return 0;
}
GUI_WEAK int gui_model_msg_video_pause_cb(gui_msg_action_t access, gui_msg_data_t *data, gui_msg_data_type_t type)
{
    static lv_state_t video_pause_var = LV_STATE_DEFAULT;
    if (access == GUI_MSG_ACCESS_SET) {
        video_pause_var = data->value_int;
    }
    data->value_int = video_pause_var;
    return 0;
}
GUI_WEAK int gui_model_msg_cur_time_process_cb(gui_msg_action_t access, gui_msg_data_t *data, gui_msg_data_type_t type)
{
    static int32_t cur_time_process_var = 20;
    if (access == GUI_MSG_ACCESS_SET) {
        cur_time_process_var = data->value_int;
    }
    data->value_int = cur_time_process_var;
    return 0;
}
GUI_WEAK int gui_model_msg_file_name_cb(gui_msg_action_t access, gui_msg_data_t *data, gui_msg_data_type_t type)
{
    char file_name_init_var[] = "正在播放 xxx.avi";
    static bool file_name_is_init = false;
    static char *file_name_var = NULL;
    if (file_name_is_init == false) {
        file_name_var = lv_mem_alloc(strlen(file_name_init_var) + 1);
        strcpy(file_name_var, file_name_init_var);
        file_name_is_init = true;
    }
    if (access == GUI_MSG_ACCESS_SET) {
        lv_mem_free(file_name_var);
        file_name_var = lv_mem_alloc(strlen(data->value_string) + 1);
        strcpy(file_name_var, data->value_string);
    }
    data->value_string = file_name_var;
    return 0;
}
GUI_WEAK int gui_model_msg_total_time_cb(gui_msg_action_t access, gui_msg_data_t *data, gui_msg_data_type_t type)
{
    char total_time_init_var[] = "/02:40";
    static bool total_time_is_init = false;
    static char *total_time_var = NULL;
    if (total_time_is_init == false) {
        total_time_var = lv_mem_alloc(strlen(total_time_init_var) + 1);
        strcpy(total_time_var, total_time_init_var);
        total_time_is_init = true;
    }
    if (access == GUI_MSG_ACCESS_SET) {
        lv_mem_free(total_time_var);
        total_time_var = lv_mem_alloc(strlen(data->value_string) + 1);
        strcpy(total_time_var, data->value_string);
    }
    data->value_string = total_time_var;
    return 0;
}
GUI_WEAK int gui_model_msg_file_path_cb(gui_msg_action_t access, gui_msg_data_t *data, gui_msg_data_type_t type)
{
    char file_path_init_var[] = "storage/sd0/C/DCIM/1/";
    static bool file_path_is_init = false;
    static char *file_path_var = NULL;
    if (file_path_is_init == false) {
        file_path_var = lv_mem_alloc(strlen(file_path_init_var) + 1);
        strcpy(file_path_var, file_path_init_var);
        file_path_is_init = true;
    }
    if (access == GUI_MSG_ACCESS_SET) {
        lv_mem_free(file_path_var);
        file_path_var = lv_mem_alloc(strlen(data->value_string) + 1);
        strcpy(file_path_var, data->value_string);
    }
    data->value_string = file_path_var;
    return 0;
}
GUI_WEAK int gui_model_msg_file_num_cb(gui_msg_action_t access, gui_msg_data_t *data, gui_msg_data_type_t type)
{
    char file_num_init_var[] = "";
    static bool file_num_is_init = false;
    static char *file_num_var = NULL;
    if (file_num_is_init == false) {
        file_num_var = lv_mem_alloc(strlen(file_num_init_var) + 1);
        strcpy(file_num_var, file_num_init_var);
        file_num_is_init = true;
    }
    if (access == GUI_MSG_ACCESS_SET) {
        lv_mem_free(file_num_var);
        file_num_var = lv_mem_alloc(strlen(data->value_string) + 1);
        strcpy(file_num_var, data->value_string);
    }
    data->value_string = file_num_var;
    return 0;
}

void gui_model_msg_init(lv_ui *ui)
{
    gui_msg_sub_t *sub;
    sub = gui_msg_create_sub(GUI_MODEL_MSG_ID_CUR_TIME);
    if (sub != NULL) {
        lv_subject_init_pointer(sub->subject, &guider_msg_data);
    }
    sub = gui_msg_create_sub(GUI_MODEL_MSG_ID_PREV_FILE);
    if (sub != NULL) {
        lv_subject_init_pointer(sub->subject, &guider_msg_data);
    }
    sub = gui_msg_create_sub(GUI_MODEL_MSG_ID_NEXT_FILE);
    if (sub != NULL) {
        lv_subject_init_pointer(sub->subject, &guider_msg_data);
    }
    sub = gui_msg_create_sub(GUI_MODEL_MSG_ID_VIDEO_PAUSE);
    if (sub != NULL) {
        lv_subject_init_pointer(sub->subject, &guider_msg_data);
    }
    sub = gui_msg_create_sub(GUI_MODEL_MSG_ID_CUR_TIME_PROCESS);
    if (sub != NULL) {
        lv_subject_init_pointer(sub->subject, &guider_msg_data);
    }
    sub = gui_msg_create_sub(GUI_MODEL_MSG_ID_FILE_NAME);
    if (sub != NULL) {
        lv_subject_init_pointer(sub->subject, &guider_msg_data);
    }
    sub = gui_msg_create_sub(GUI_MODEL_MSG_ID_TOTAL_TIME);
    if (sub != NULL) {
        lv_subject_init_pointer(sub->subject, &guider_msg_data);
    }
    sub = gui_msg_create_sub(GUI_MODEL_MSG_ID_FILE_PATH);
    if (sub != NULL) {
        lv_subject_init_pointer(sub->subject, &guider_msg_data);
    }
    sub = gui_msg_create_sub(GUI_MODEL_MSG_ID_FILE_NUM);
    if (sub != NULL) {
        lv_subject_init_pointer(sub->subject, &guider_msg_data);
    }
}

void gui_model_msg_init_ui()
{
}

void gui_model_msg_init_events()
{
    void *res = NULL;
    _gui_msg_status_t status[9] = {
        {GUI_MODEL_MSG_ID_CUR_TIME, 0, 0},
        {GUI_MODEL_MSG_ID_PREV_FILE, 0, 0},
        {GUI_MODEL_MSG_ID_NEXT_FILE, 0, 0},
        {GUI_MODEL_MSG_ID_VIDEO_PAUSE, 0, 0},
        {GUI_MODEL_MSG_ID_CUR_TIME_PROCESS, 0, 0},
        {GUI_MODEL_MSG_ID_FILE_NAME, 0, 0},
        {GUI_MODEL_MSG_ID_TOTAL_TIME, 0, 0},
        {GUI_MODEL_MSG_ID_FILE_PATH, 0, 0},
        {GUI_MODEL_MSG_ID_FILE_NUM, 0, 0},
    };

    for (int i = 0; i < 9; i++) {
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

    lv_subject_t *subject_cur_time = gui_msg_get_subject(GUI_MODEL_MSG_ID_CUR_TIME);
    lv_subject_t *subject_prev_file = gui_msg_get_subject(GUI_MODEL_MSG_ID_PREV_FILE);
    lv_subject_t *subject_next_file = gui_msg_get_subject(GUI_MODEL_MSG_ID_NEXT_FILE);
    lv_subject_t *subject_video_pause = gui_msg_get_subject(GUI_MODEL_MSG_ID_VIDEO_PAUSE);
    lv_subject_t *subject_cur_time_process = gui_msg_get_subject(GUI_MODEL_MSG_ID_CUR_TIME_PROCESS);
    lv_subject_t *subject_file_name = gui_msg_get_subject(GUI_MODEL_MSG_ID_FILE_NAME);
    lv_subject_t *subject_total_time = gui_msg_get_subject(GUI_MODEL_MSG_ID_TOTAL_TIME);
    lv_subject_t *subject_file_path = gui_msg_get_subject(GUI_MODEL_MSG_ID_FILE_PATH);
    lv_subject_t *subject_file_num = gui_msg_get_subject(GUI_MODEL_MSG_ID_FILE_NUM);
    if (guider_ui.video_play) {
        lv_ui_video_play *ui_scr = ui_get_scr_ptr(&guider_ui, GUI_SCREEN_VIDEO_PLAY);
        gui_msg_setup_component(true, false, subject_cur_time, ui_scr->video_play_lbl_cur_time, &guider_msg_data, gui_msg_set_label_text_by_string_cb, GUI_MODEL_MSG_ID_CUR_TIME, GUI_MSG_ACCESS_GET, VALUE_STRING, NULL);

        gui_msg_setup_component(true, false, subject_video_pause, ui_scr->video_play_imgbtn_pause, &guider_msg_data, gui_msg_set_control_state_by_int32_cb, GUI_MODEL_MSG_ID_VIDEO_PAUSE, GUI_MSG_ACCESS_GET, VALUE_INT, NULL);

        gui_msg_setup_component(true, false, subject_total_time, ui_scr->video_play_lbl_total_time, &guider_msg_data, gui_msg_set_label_text_by_string_cb, GUI_MODEL_MSG_ID_TOTAL_TIME, GUI_MSG_ACCESS_GET, VALUE_STRING, NULL);

        gui_msg_setup_component(true, false, subject_cur_time_process, ui_scr->video_play_bar_process, &guider_msg_data, gui_msg_set_bar_bar_value_by_int32_cb, GUI_MODEL_MSG_ID_CUR_TIME_PROCESS, GUI_MSG_ACCESS_GET, VALUE_INT, NULL);

        gui_msg_setup_component(true, false, subject_file_name, ui_scr->video_play_lbl_msg, &guider_msg_data, gui_msg_set_label_text_by_string_cb, GUI_MODEL_MSG_ID_FILE_NAME, GUI_MSG_ACCESS_GET, VALUE_STRING, NULL);

        gui_msg_setup_component(true, false, subject_prev_file, ui_scr->video_play_img_prev_file, &guider_msg_data, gui_model_msg_video_play_img_prev_file_set_img_path_cb, GUI_MODEL_MSG_ID_PREV_FILE, GUI_MSG_ACCESS_GET, VALUE_INT, NULL);

        gui_msg_setup_component(true, false, subject_next_file, ui_scr->video_play_img_next_file, &guider_msg_data, gui_model_msg_video_play_img_next_file_set_img_path_cb, GUI_MODEL_MSG_ID_NEXT_FILE, GUI_MSG_ACCESS_GET, VALUE_INT, NULL);


        for (int i = 0; i < 9; i++) {
            if (status[i].msg_id == GUI_MODEL_MSG_ID_CUR_TIME) {
                status[i].is_subscribe = 1;
            }
            if (status[i].msg_id == GUI_MODEL_MSG_ID_VIDEO_PAUSE) {
                status[i].is_subscribe = 1;
            }
            if (status[i].msg_id == GUI_MODEL_MSG_ID_TOTAL_TIME) {
                status[i].is_subscribe = 1;
            }
            if (status[i].msg_id == GUI_MODEL_MSG_ID_CUR_TIME_PROCESS) {
                status[i].is_subscribe = 1;
            }
            if (status[i].msg_id == GUI_MODEL_MSG_ID_FILE_NAME) {
                status[i].is_subscribe = 1;
            }
            if (status[i].msg_id == GUI_MODEL_MSG_ID_PREV_FILE) {
                status[i].is_subscribe = 1;
            }
            if (status[i].msg_id == GUI_MODEL_MSG_ID_NEXT_FILE) {
                status[i].is_subscribe = 1;
            }
        }
    }
    if (guider_ui.video_file) {
        lv_ui_video_file *ui_scr = ui_get_scr_ptr(&guider_ui, GUI_SCREEN_VIDEO_FILE);
        gui_msg_setup_component(true, false, subject_file_path, ui_scr->video_file_lbl_path, &guider_msg_data, gui_msg_set_label_text_by_string_cb, GUI_MODEL_MSG_ID_FILE_PATH, GUI_MSG_ACCESS_GET, VALUE_STRING, NULL);

        gui_msg_setup_component(true, false, subject_file_num, ui_scr->video_file_lbl_1, &guider_msg_data, gui_msg_set_label_text_by_string_cb, GUI_MODEL_MSG_ID_FILE_NUM, GUI_MSG_ACCESS_GET, VALUE_STRING, NULL);


        for (int i = 0; i < 9; i++) {
            if (status[i].msg_id == GUI_MODEL_MSG_ID_FILE_PATH) {
                status[i].is_subscribe = 1;
            }
            if (status[i].msg_id == GUI_MODEL_MSG_ID_FILE_NUM) {
                status[i].is_subscribe = 1;
            }
        }
    }
    if (guider_ui.video_dir) {
        lv_ui_video_dir *ui_scr = ui_get_scr_ptr(&guider_ui, GUI_SCREEN_VIDEO_DIR);
        gui_msg_setup_component(true, false, subject_file_path, ui_scr->video_dir_lbl_path, &guider_msg_data, gui_msg_set_label_text_by_string_cb, GUI_MODEL_MSG_ID_FILE_PATH, GUI_MSG_ACCESS_GET, VALUE_STRING, NULL);


        for (int i = 0; i < 9; i++) {
            if (status[i].msg_id == GUI_MODEL_MSG_ID_FILE_PATH) {
                status[i].is_subscribe = 1;
            }
        }
    }

    for (int i = 0; i < 9; i++) {
        if (status[i].is_subscribe == 0 && status[i].is_unsubscribe == 1) {
            gui_msg_subscribe_change(status[i].msg_id, GUI_MSG_UNSUBSCRIBE);
        } else if (status[i].is_subscribe == 1 && status[i].is_unsubscribe == 0) {
            gui_msg_subscribe_change(status[i].msg_id, GUI_MSG_SUBSCRIBE);
        }
    }
}

void gui_model_msg_unsubscribe()
{
    _gui_msg_status_t status[9] = {
        {GUI_MODEL_MSG_ID_CUR_TIME, 0, 0},
        {GUI_MODEL_MSG_ID_PREV_FILE, 0, 0},
        {GUI_MODEL_MSG_ID_NEXT_FILE, 0, 0},
        {GUI_MODEL_MSG_ID_VIDEO_PAUSE, 0, 0},
        {GUI_MODEL_MSG_ID_CUR_TIME_PROCESS, 0, 0},
        {GUI_MODEL_MSG_ID_FILE_NAME, 0, 0},
        {GUI_MODEL_MSG_ID_TOTAL_TIME, 0, 0},
        {GUI_MODEL_MSG_ID_FILE_PATH, 0, 0},
        {GUI_MODEL_MSG_ID_FILE_NUM, 0, 0},
    };
    for (int i = 0; i < 9; i++) {
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

    for (int i = 0; i < 9; i++) {
        if (status[i].is_unsubscribe == 1) {
            gui_msg_subscribe_change(status[i].msg_id, GUI_MSG_UNSUBSCRIBE);
        }
    }
}

gui_msg_data_t *gui_model_msg_get(int32_t msg_id)
{
    switch (msg_id) {
    case GUI_MODEL_MSG_ID_CUR_TIME: {
        gui_model_msg_cur_time_cb(GUI_MSG_ACCESS_GET, &guider_msg_data, VALUE_STRING);
        break;
    }
    case GUI_MODEL_MSG_ID_PREV_FILE: {
        gui_model_msg_prev_file_cb(GUI_MSG_ACCESS_GET, &guider_msg_data, VALUE_INT);
        break;
    }
    case GUI_MODEL_MSG_ID_NEXT_FILE: {
        gui_model_msg_next_file_cb(GUI_MSG_ACCESS_GET, &guider_msg_data, VALUE_INT);
        break;
    }
    case GUI_MODEL_MSG_ID_VIDEO_PAUSE: {
        gui_model_msg_video_pause_cb(GUI_MSG_ACCESS_GET, &guider_msg_data, VALUE_INT);
        break;
    }
    case GUI_MODEL_MSG_ID_CUR_TIME_PROCESS: {
        gui_model_msg_cur_time_process_cb(GUI_MSG_ACCESS_GET, &guider_msg_data, VALUE_INT);
        break;
    }
    case GUI_MODEL_MSG_ID_FILE_NAME: {
        gui_model_msg_file_name_cb(GUI_MSG_ACCESS_GET, &guider_msg_data, VALUE_STRING);
        break;
    }
    case GUI_MODEL_MSG_ID_TOTAL_TIME: {
        gui_model_msg_total_time_cb(GUI_MSG_ACCESS_GET, &guider_msg_data, VALUE_STRING);
        break;
    }
    case GUI_MODEL_MSG_ID_FILE_PATH: {
        gui_model_msg_file_path_cb(GUI_MSG_ACCESS_GET, &guider_msg_data, VALUE_STRING);
        break;
    }
    case GUI_MODEL_MSG_ID_FILE_NUM: {
        gui_model_msg_file_num_cb(GUI_MSG_ACCESS_GET, &guider_msg_data, VALUE_STRING);
        break;
    }
    default:
        return NULL;
    }
    return &guider_msg_data;
}

void gui_model_msg_action_change(int32_t msg_id, gui_msg_action_t access, gui_msg_data_t *data, gui_msg_data_type_t type)
{
    switch (msg_id) {
    case GUI_MODEL_MSG_ID_CUR_TIME: {
        gui_model_msg_cur_time_cb(access, data, type);
        break;
    }
    case GUI_MODEL_MSG_ID_PREV_FILE: {
        gui_model_msg_prev_file_cb(access, data, type);
        break;
    }
    case GUI_MODEL_MSG_ID_NEXT_FILE: {
        gui_model_msg_next_file_cb(access, data, type);
        break;
    }
    case GUI_MODEL_MSG_ID_VIDEO_PAUSE: {
        gui_model_msg_video_pause_cb(access, data, type);
        break;
    }
    case GUI_MODEL_MSG_ID_CUR_TIME_PROCESS: {
        gui_model_msg_cur_time_process_cb(access, data, type);
        break;
    }
    case GUI_MODEL_MSG_ID_FILE_NAME: {
        gui_model_msg_file_name_cb(access, data, type);
        break;
    }
    case GUI_MODEL_MSG_ID_TOTAL_TIME: {
        gui_model_msg_total_time_cb(access, data, type);
        break;
    }
    case GUI_MODEL_MSG_ID_FILE_PATH: {
        gui_model_msg_file_path_cb(access, data, type);
        break;
    }
    case GUI_MODEL_MSG_ID_FILE_NUM: {
        gui_model_msg_file_num_cb(access, data, type);
        break;
    }
    default: {
        break;
    }
    }
}

gui_msg_status_t gui_model_msg_send(int32_t msg_id, void *value, int32_t len)
{
    if (msg_id == GUI_MODEL_MSG_ID) {
    } else {
        gui_msg_data_type_t data_type = VALUE_INT;
        switch (msg_id) {
        case GUI_MODEL_MSG_ID_CUR_TIME: {
            data_type = VALUE_STRING;
            guider_msg_data.value_array.ptr = value;
            guider_msg_data.value_array.len = len;
            break;
        }
        case GUI_MODEL_MSG_ID_PREV_FILE: {
            data_type = VALUE_INT;
            guider_msg_data.value_array.ptr = value;
            guider_msg_data.value_array.len = len;
            break;
        }
        case GUI_MODEL_MSG_ID_NEXT_FILE: {
            data_type = VALUE_INT;
            guider_msg_data.value_array.ptr = value;
            guider_msg_data.value_array.len = len;
            break;
        }
        case GUI_MODEL_MSG_ID_VIDEO_PAUSE: {
            data_type = VALUE_INT;
            guider_msg_data.value_array.ptr = value;
            guider_msg_data.value_array.len = len;
            break;
        }
        case GUI_MODEL_MSG_ID_CUR_TIME_PROCESS: {
            data_type = VALUE_INT;
            guider_msg_data.value_array.ptr = value;
            guider_msg_data.value_array.len = len;
            break;
        }
        case GUI_MODEL_MSG_ID_FILE_NAME: {
            data_type = VALUE_STRING;
            guider_msg_data.value_array.ptr = value;
            guider_msg_data.value_array.len = len;
            break;
        }
        case GUI_MODEL_MSG_ID_TOTAL_TIME: {
            data_type = VALUE_STRING;
            guider_msg_data.value_array.ptr = value;
            guider_msg_data.value_array.len = len;
            break;
        }
        case GUI_MODEL_MSG_ID_FILE_PATH: {
            data_type = VALUE_STRING;
            guider_msg_data.value_array.ptr = value;
            guider_msg_data.value_array.len = len;
            break;
        }
        case GUI_MODEL_MSG_ID_FILE_NUM: {
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

#endif
