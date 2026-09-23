#include "app_config.h"
#ifdef CONFIG_UI_STYLE_LY_ENABLE
/*Generate Code, Do NOT Edit!*/
#include "./gui_model_video_rec_msg.h"
#if LV_USE_OBSERVER

static lv_ll_t subs_ll;

#if LV_USE_GUIBUILDER_SIMULATOR
_gui_msg_entry_t gui_model_video_rec_msg_entry_table[] = {
    { GUI_MODEL_VIDEO_REC_MSG_ID_CYCREC_ICON, gui_model_video_rec_msg_cycrec_icon_cb, VALUE_INT },
    { GUI_MODEL_VIDEO_REC_MSG_ID_DELAYREC_ICON, gui_model_video_rec_msg_delayrec_icon_cb, VALUE_INT },
    { GUI_MODEL_VIDEO_REC_MSG_ID_CAR_NUNBER, gui_model_video_rec_msg_car_nunber_cb, VALUE_STRING },
    { GUI_MODEL_VIDEO_REC_MSG_ID_REC_RESO, gui_model_video_rec_msg_rec_reso_cb, VALUE_STRING },
    { GUI_MODEL_VIDEO_REC_MSG_ID_REC_BTN, gui_model_video_rec_msg_rec_btn_cb, VALUE_INT },
    { GUI_MODEL_VIDEO_REC_MSG_ID_SHOW_GSENSOR_ICON, gui_model_video_rec_msg_show_gsensor_icon_cb, VALUE_INT },
    { GUI_MODEL_VIDEO_REC_MSG_ID_HIDE_GSENSOR_ICON, gui_model_video_rec_msg_hide_gsensor_icon_cb, VALUE_INT },
    { GUI_MODEL_VIDEO_REC_MSG_ID_SHOW_GUARD_ICON, gui_model_video_rec_msg_show_guard_icon_cb, VALUE_INT },
    { GUI_MODEL_VIDEO_REC_MSG_ID_HIDE_GUARD_ICON, gui_model_video_rec_msg_hide_guard_icon_cb, VALUE_INT },
    { GUI_MODEL_VIDEO_REC_MSG_ID_SHOW_MOTION_ICON, gui_model_video_rec_msg_show_motion_icon_cb, VALUE_INT },
    { GUI_MODEL_VIDEO_REC_MSG_ID_HIDE_MOTION_ICON, gui_model_video_rec_msg_hide_motion_icon_cb, VALUE_INT },
    { GUI_MODEL_VIDEO_REC_MSG_ID_SHOW_HDR_ICON, gui_model_video_rec_msg_show_hdr_icon_cb, VALUE_INT },
    { GUI_MODEL_VIDEO_REC_MSG_ID_HIDE_HDR_ICON, gui_model_video_rec_msg_hide_hdr_icon_cb, VALUE_INT },
    { GUI_MODEL_VIDEO_REC_MSG_ID_REC_REMAIN_TIME, gui_model_video_rec_msg_rec_remain_time_cb, VALUE_TIME },
    { GUI_MODEL_VIDEO_REC_MSG_ID_REC_TIME_STATE, gui_model_video_rec_msg_rec_time_state_cb, VALUE_INT },
    { GUI_MODEL_VIDEO_REC_MSG_ID_VIDEO_REC_MENU, gui_model_video_rec_msg_video_rec_menu_cb, VALUE_BOOL },
    { GUI_MODEL_VIDEO_REC_MSG_ID_MIC_ICON, gui_model_video_rec_msg_mic_icon_cb, VALUE_INT },
    { GUI_MODEL_VIDEO_REC_MSG_ID_GSENSOR_ICON, gui_model_video_rec_msg_gsensor_icon_cb, VALUE_INT },
    { GUI_MODEL_VIDEO_REC_MSG_ID_SD_ICON, gui_model_video_rec_msg_sd_icon_cb, VALUE_INT },
    { GUI_MODEL_VIDEO_REC_MSG_ID_GUARD_STATE, gui_model_video_rec_msg_guard_state_cb, VALUE_BOOL },
    { GUI_MODEL_VIDEO_REC_MSG_ID_CYC_STATE, gui_model_video_rec_msg_cyc_state_cb, VALUE_BOOL },
    { GUI_MODEL_VIDEO_REC_MSG_ID_MOTION_STATE, gui_model_video_rec_msg_motion_state_cb, VALUE_BOOL },
    { GUI_MODEL_VIDEO_REC_MSG_ID_GAP_STATE, gui_model_video_rec_msg_gap_state_cb, VALUE_BOOL },
    { GUI_MODEL_VIDEO_REC_MSG_ID_HDR_STATE, gui_model_video_rec_msg_hdr_state_cb, VALUE_BOOL },
    { GUI_MODEL_VIDEO_REC_MSG_ID_GRA_STATE, gui_model_video_rec_msg_gra_state_cb, VALUE_BOOL },
    { GUI_MODEL_VIDEO_REC_MSG_ID_EXP_ICON, gui_model_video_rec_msg_exp_icon_cb, VALUE_INT },
    { GUI_MODEL_VIDEO_REC_MSG_ID_CAR_NUM, gui_model_video_rec_msg_car_num_cb, VALUE_BOOL },
    { GUI_MODEL_VIDEO_REC_MSG_ID_FLASH_HEADLIGHT, gui_model_video_rec_msg_flash_headlight_cb, VALUE_BOOL },
    { GUI_MODEL_VIDEO_REC_MSG_ID_REC_ICON_STATE, gui_model_video_rec_msg_rec_icon_state_cb, VALUE_BOOL },
    { GUI_MODEL_VIDEO_REC_MSG_ID_KEY_STATE, gui_model_video_rec_msg_key_state_cb, VALUE_BOOL },
};
#endif

void gui_model_video_rec_msg_video_rec_img_cyc_state_set_img_path_cb(lv_observer_t *observer, lv_subject_t *subject)
{
    lv_obj_t *obj = lv_observer_get_target_obj(observer);
    if (obj == NULL || lv_obj_is_valid(obj) == false) {
        return;
    }

    gui_msg_data_t *data = (gui_msg_data_t *)observer->user_data;
    lv_img_set_src(obj, gui_get_res_path(data->value_int));
}
void gui_model_video_rec_msg_video_rec_img_exp_state_set_img_path_cb(lv_observer_t *observer, lv_subject_t *subject)
{
    lv_obj_t *obj = lv_observer_get_target_obj(observer);
    if (obj == NULL || lv_obj_is_valid(obj) == false) {
        return;
    }

    gui_msg_data_t *data = (gui_msg_data_t *)observer->user_data;
    lv_img_set_src(obj, gui_get_res_path(data->value_int));
}
void gui_model_video_rec_msg_video_rec_img_mic_state_set_img_path_cb(lv_observer_t *observer, lv_subject_t *subject)
{
    lv_obj_t *obj = lv_observer_get_target_obj(observer);
    if (obj == NULL || lv_obj_is_valid(obj) == false) {
        return;
    }

    gui_msg_data_t *data = (gui_msg_data_t *)observer->user_data;
    lv_img_set_src(obj, gui_get_res_path(data->value_int));
}
void gui_model_video_rec_msg_video_rec_img_gra_state_set_img_path_cb(lv_observer_t *observer, lv_subject_t *subject)
{
    lv_obj_t *obj = lv_observer_get_target_obj(observer);
    if (obj == NULL || lv_obj_is_valid(obj) == false) {
        return;
    }

    gui_msg_data_t *data = (gui_msg_data_t *)observer->user_data;
    lv_img_set_src(obj, gui_get_res_path(data->value_int));
}
void gui_model_video_rec_msg_video_rec_img_sd_set_img_path_cb(lv_observer_t *observer, lv_subject_t *subject)
{
    lv_obj_t *obj = lv_observer_get_target_obj(observer);
    if (obj == NULL || lv_obj_is_valid(obj) == false) {
        return;
    }

    gui_msg_data_t *data = (gui_msg_data_t *)observer->user_data;
    lv_img_set_src(obj, gui_get_res_path(data->value_int));
}
void gui_model_video_rec_msg_video_rec_digitclock_2_set_digit_clock_time_cb(lv_observer_t *observer, lv_subject_t *subject)
{
    lv_obj_t *obj = lv_observer_get_target_obj(observer);
    if (obj == NULL || lv_obj_is_valid(obj) == false) {
        return;
    }

    gui_msg_data_t *data = (gui_msg_data_t *)observer->user_data;
    struct tm time = data->value_time;
    lv_label_set_text_fmt(obj, "%02d:%02d:%02d", time.tm_hour, time.tm_min, time.tm_sec);
}
void gui_model_video_rec_msg_video_photo_img_sd_icon_set_img_path_cb(lv_observer_t *observer, lv_subject_t *subject)
{
    lv_obj_t *obj = lv_observer_get_target_obj(observer);
    if (obj == NULL || lv_obj_is_valid(obj) == false) {
        return;
    }

    gui_msg_data_t *data = (gui_msg_data_t *)observer->user_data;
    lv_img_set_src(obj, gui_get_res_path(data->value_int));
}

GUI_WEAK int gui_model_video_rec_msg_cycrec_icon_cb(gui_msg_action_t access, gui_msg_data_t *data, gui_msg_data_type_t type)
{
    static int32_t cycrec_icon_var = RES_CYCLIC_VIDEO_3;
    _gui_msg_int32_cb(&cycrec_icon_var, access, data);
    return 0;
}
GUI_WEAK int gui_model_video_rec_msg_delayrec_icon_cb(gui_msg_action_t access, gui_msg_data_t *data, gui_msg_data_type_t type)
{
    static int32_t delayrec_icon_var = RES_INTERVAL_VIDEO_CLOSE;
    _gui_msg_int32_cb(&delayrec_icon_var, access, data);
    return 0;
}
GUI_WEAK int gui_model_video_rec_msg_car_nunber_cb(gui_msg_action_t access, gui_msg_data_t *data, gui_msg_data_type_t type)
{
    char car_nunber_init_var[] = "京A11111";
    static bool car_nunber_is_init = false;
    static char *car_nunber_var = NULL;
    _gui_msg_char_array_cb(&car_nunber_var, car_nunber_init_var, &car_nunber_is_init, access, data);
    return 0;
}
GUI_WEAK int gui_model_video_rec_msg_rec_reso_cb(gui_msg_action_t access, gui_msg_data_t *data, gui_msg_data_type_t type)
{
    char rec_reso_init_var[] = "720P";
    static bool rec_reso_is_init = false;
    static char *rec_reso_var = NULL;
    _gui_msg_char_array_cb(&rec_reso_var, rec_reso_init_var, &rec_reso_is_init, access, data);
    return 0;
}
GUI_WEAK int gui_model_video_rec_msg_rec_btn_cb(gui_msg_action_t access, gui_msg_data_t *data, gui_msg_data_type_t type)
{
    static lv_state_t rec_btn_var = LV_STATE_DEFAULT;
    _gui_msg_state_cb(&rec_btn_var, access, data);
    return 0;
}
GUI_WEAK int gui_model_video_rec_msg_show_gsensor_icon_cb(gui_msg_action_t access, gui_msg_data_t *data, gui_msg_data_type_t type)
{
    static lv_obj_flag_t show_gsensor_icon_var = 0;
    _gui_msg_obj_flag_cb(&show_gsensor_icon_var, access, data);
    return 0;
}
GUI_WEAK int gui_model_video_rec_msg_hide_gsensor_icon_cb(gui_msg_action_t access, gui_msg_data_t *data, gui_msg_data_type_t type)
{
    static lv_obj_flag_t hide_gsensor_icon_var = 0;
    _gui_msg_obj_flag_cb(&hide_gsensor_icon_var, access, data);
    return 0;
}
GUI_WEAK int gui_model_video_rec_msg_show_guard_icon_cb(gui_msg_action_t access, gui_msg_data_t *data, gui_msg_data_type_t type)
{
    static lv_obj_flag_t show_guard_icon_var = 0;
    _gui_msg_obj_flag_cb(&show_guard_icon_var, access, data);
    return 0;
}
GUI_WEAK int gui_model_video_rec_msg_hide_guard_icon_cb(gui_msg_action_t access, gui_msg_data_t *data, gui_msg_data_type_t type)
{
    static lv_obj_flag_t hide_guard_icon_var = 0;
    _gui_msg_obj_flag_cb(&hide_guard_icon_var, access, data);
    return 0;
}
GUI_WEAK int gui_model_video_rec_msg_show_motion_icon_cb(gui_msg_action_t access, gui_msg_data_t *data, gui_msg_data_type_t type)
{
    static lv_obj_flag_t show_motion_icon_var = 0;
    _gui_msg_obj_flag_cb(&show_motion_icon_var, access, data);
    return 0;
}
GUI_WEAK int gui_model_video_rec_msg_hide_motion_icon_cb(gui_msg_action_t access, gui_msg_data_t *data, gui_msg_data_type_t type)
{
    static lv_obj_flag_t hide_motion_icon_var = 0;
    _gui_msg_obj_flag_cb(&hide_motion_icon_var, access, data);
    return 0;
}
GUI_WEAK int gui_model_video_rec_msg_show_hdr_icon_cb(gui_msg_action_t access, gui_msg_data_t *data, gui_msg_data_type_t type)
{
    static lv_obj_flag_t show_hdr_icon_var = 0;
    _gui_msg_obj_flag_cb(&show_hdr_icon_var, access, data);
    return 0;
}
GUI_WEAK int gui_model_video_rec_msg_hide_hdr_icon_cb(gui_msg_action_t access, gui_msg_data_t *data, gui_msg_data_type_t type)
{
    static lv_obj_flag_t hide_hdr_icon_var = 0;
    _gui_msg_obj_flag_cb(&hide_hdr_icon_var, access, data);
    return 0;
}
GUI_WEAK int gui_model_video_rec_msg_rec_remain_time_cb(gui_msg_action_t access, gui_msg_data_t *data, gui_msg_data_type_t type)
{
    static struct tm rec_remain_time_var = {
        .tm_year = 124,
        .tm_mon = 6,
        .tm_mday = 2,
        .tm_hour = 0,
        .tm_min = 0,
        .tm_sec = 0,
    };
    _gui_msg_tm_cb(&rec_remain_time_var, false, access, data);
    return 0;
}
GUI_WEAK int gui_model_video_rec_msg_rec_time_state_cb(gui_msg_action_t access, gui_msg_data_t *data, gui_msg_data_type_t type)
{
    static lv_state_t rec_time_state_var = LV_STATE_DEFAULT;
    _gui_msg_state_cb(&rec_time_state_var, access, data);
    return 0;
}
GUI_WEAK int gui_model_video_rec_msg_video_rec_menu_cb(gui_msg_action_t access, gui_msg_data_t *data, gui_msg_data_type_t type)
{
    static bool video_rec_menu_var = false;
    _gui_msg_bool_cb(&video_rec_menu_var, access, data);
    return 0;
}
GUI_WEAK int gui_model_video_rec_msg_mic_icon_cb(gui_msg_action_t access, gui_msg_data_t *data, gui_msg_data_type_t type)
{
    static int32_t mic_icon_var = RES_MIC_ON;
    _gui_msg_int32_cb(&mic_icon_var, access, data);
    return 0;
}
GUI_WEAK int gui_model_video_rec_msg_gsensor_icon_cb(gui_msg_action_t access, gui_msg_data_t *data, gui_msg_data_type_t type)
{
    static int32_t gsensor_icon_var = RES_I_GRA_L;
    _gui_msg_int32_cb(&gsensor_icon_var, access, data);
    return 0;
}
GUI_WEAK int gui_model_video_rec_msg_sd_icon_cb(gui_msg_action_t access, gui_msg_data_t *data, gui_msg_data_type_t type)
{
    static int32_t sd_icon_var = RES_CARD_OFFLINE;
    _gui_msg_int32_cb(&sd_icon_var, access, data);
    return 0;
}
GUI_WEAK int gui_model_video_rec_msg_guard_state_cb(gui_msg_action_t access, gui_msg_data_t *data, gui_msg_data_type_t type)
{
    static bool guard_state_var = false;
    _gui_msg_bool_cb(&guard_state_var, access, data);
    return 0;
}
GUI_WEAK int gui_model_video_rec_msg_cyc_state_cb(gui_msg_action_t access, gui_msg_data_t *data, gui_msg_data_type_t type)
{
    static bool cyc_state_var = false;
    _gui_msg_bool_cb(&cyc_state_var, access, data);
    return 0;
}
GUI_WEAK int gui_model_video_rec_msg_motion_state_cb(gui_msg_action_t access, gui_msg_data_t *data, gui_msg_data_type_t type)
{
    static bool motion_state_var = false;
    _gui_msg_bool_cb(&motion_state_var, access, data);
    return 0;
}
GUI_WEAK int gui_model_video_rec_msg_gap_state_cb(gui_msg_action_t access, gui_msg_data_t *data, gui_msg_data_type_t type)
{
    static bool gap_state_var = false;
    _gui_msg_bool_cb(&gap_state_var, access, data);
    return 0;
}
GUI_WEAK int gui_model_video_rec_msg_hdr_state_cb(gui_msg_action_t access, gui_msg_data_t *data, gui_msg_data_type_t type)
{
    static bool hdr_state_var = false;
    _gui_msg_bool_cb(&hdr_state_var, access, data);
    return 0;
}
GUI_WEAK int gui_model_video_rec_msg_gra_state_cb(gui_msg_action_t access, gui_msg_data_t *data, gui_msg_data_type_t type)
{
    static bool gra_state_var = false;
    _gui_msg_bool_cb(&gra_state_var, access, data);
    return 0;
}
GUI_WEAK int gui_model_video_rec_msg_exp_icon_cb(gui_msg_action_t access, gui_msg_data_t *data, gui_msg_data_type_t type)
{
    static int32_t exp_icon_var = RES_EXP_A0;
    _gui_msg_int32_cb(&exp_icon_var, access, data);
    return 0;
}
GUI_WEAK int gui_model_video_rec_msg_car_num_cb(gui_msg_action_t access, gui_msg_data_t *data, gui_msg_data_type_t type)
{
    static bool car_num_var = false;
    _gui_msg_bool_cb(&car_num_var, access, data);
    return 0;
}
GUI_WEAK int gui_model_video_rec_msg_flash_headlight_cb(gui_msg_action_t access, gui_msg_data_t *data, gui_msg_data_type_t type)
{
    static bool flash_headlight_var = false;
    _gui_msg_bool_cb(&flash_headlight_var, access, data);
    return 0;
}
GUI_WEAK int gui_model_video_rec_msg_rec_icon_state_cb(gui_msg_action_t access, gui_msg_data_t *data, gui_msg_data_type_t type)
{
    static bool rec_icon_state_var = false;
    _gui_msg_bool_cb(&rec_icon_state_var, access, data);
    return 0;
}
GUI_WEAK int gui_model_video_rec_msg_key_state_cb(gui_msg_action_t access, gui_msg_data_t *data, gui_msg_data_type_t type)
{
    static bool key_state_var = false;
    _gui_msg_bool_cb(&key_state_var, access, data);
    return 0;
}

void gui_model_video_rec_msg_init(lv_ui *ui)
{
    int32_t ids[30] = {
        GUI_MODEL_VIDEO_REC_MSG_ID_CYCREC_ICON,
        GUI_MODEL_VIDEO_REC_MSG_ID_DELAYREC_ICON,
        GUI_MODEL_VIDEO_REC_MSG_ID_CAR_NUNBER,
        GUI_MODEL_VIDEO_REC_MSG_ID_REC_RESO,
        GUI_MODEL_VIDEO_REC_MSG_ID_REC_BTN,
        GUI_MODEL_VIDEO_REC_MSG_ID_SHOW_GSENSOR_ICON,
        GUI_MODEL_VIDEO_REC_MSG_ID_HIDE_GSENSOR_ICON,
        GUI_MODEL_VIDEO_REC_MSG_ID_SHOW_GUARD_ICON,
        GUI_MODEL_VIDEO_REC_MSG_ID_HIDE_GUARD_ICON,
        GUI_MODEL_VIDEO_REC_MSG_ID_SHOW_MOTION_ICON,
        GUI_MODEL_VIDEO_REC_MSG_ID_HIDE_MOTION_ICON,
        GUI_MODEL_VIDEO_REC_MSG_ID_SHOW_HDR_ICON,
        GUI_MODEL_VIDEO_REC_MSG_ID_HIDE_HDR_ICON,
        GUI_MODEL_VIDEO_REC_MSG_ID_REC_REMAIN_TIME,
        GUI_MODEL_VIDEO_REC_MSG_ID_REC_TIME_STATE,
        GUI_MODEL_VIDEO_REC_MSG_ID_VIDEO_REC_MENU,
        GUI_MODEL_VIDEO_REC_MSG_ID_MIC_ICON,
        GUI_MODEL_VIDEO_REC_MSG_ID_GSENSOR_ICON,
        GUI_MODEL_VIDEO_REC_MSG_ID_SD_ICON,
        GUI_MODEL_VIDEO_REC_MSG_ID_GUARD_STATE,
        GUI_MODEL_VIDEO_REC_MSG_ID_CYC_STATE,
        GUI_MODEL_VIDEO_REC_MSG_ID_MOTION_STATE,
        GUI_MODEL_VIDEO_REC_MSG_ID_GAP_STATE,
        GUI_MODEL_VIDEO_REC_MSG_ID_HDR_STATE,
        GUI_MODEL_VIDEO_REC_MSG_ID_GRA_STATE,
        GUI_MODEL_VIDEO_REC_MSG_ID_EXP_ICON,
        GUI_MODEL_VIDEO_REC_MSG_ID_CAR_NUM,
        GUI_MODEL_VIDEO_REC_MSG_ID_FLASH_HEADLIGHT,
        GUI_MODEL_VIDEO_REC_MSG_ID_REC_ICON_STATE,
        GUI_MODEL_VIDEO_REC_MSG_ID_KEY_STATE,
    };
    for (int i = 0; i < 30; i++) {
        gui_msg_sub_t *sub = gui_msg_create_sub(ids[i]);
        if (sub != NULL) {
            lv_subject_init_pointer(sub->subject, &guider_msg_data);
        }
    }
}

void gui_model_video_rec_msg_init_ui()
{
}

void gui_model_video_rec_msg_init_events()
{
    void *res = NULL;
    _gui_msg_status_t status[30] = {
        {GUI_MODEL_VIDEO_REC_MSG_ID_CYCREC_ICON, 0, 0},
        {GUI_MODEL_VIDEO_REC_MSG_ID_DELAYREC_ICON, 0, 0},
        {GUI_MODEL_VIDEO_REC_MSG_ID_CAR_NUNBER, 0, 0},
        {GUI_MODEL_VIDEO_REC_MSG_ID_REC_RESO, 0, 0},
        {GUI_MODEL_VIDEO_REC_MSG_ID_REC_BTN, 0, 0},
        {GUI_MODEL_VIDEO_REC_MSG_ID_SHOW_GSENSOR_ICON, 0, 0},
        {GUI_MODEL_VIDEO_REC_MSG_ID_HIDE_GSENSOR_ICON, 0, 0},
        {GUI_MODEL_VIDEO_REC_MSG_ID_SHOW_GUARD_ICON, 0, 0},
        {GUI_MODEL_VIDEO_REC_MSG_ID_HIDE_GUARD_ICON, 0, 0},
        {GUI_MODEL_VIDEO_REC_MSG_ID_SHOW_MOTION_ICON, 0, 0},
        {GUI_MODEL_VIDEO_REC_MSG_ID_HIDE_MOTION_ICON, 0, 0},
        {GUI_MODEL_VIDEO_REC_MSG_ID_SHOW_HDR_ICON, 0, 0},
        {GUI_MODEL_VIDEO_REC_MSG_ID_HIDE_HDR_ICON, 0, 0},
        {GUI_MODEL_VIDEO_REC_MSG_ID_REC_REMAIN_TIME, 0, 0},
        {GUI_MODEL_VIDEO_REC_MSG_ID_REC_TIME_STATE, 0, 0},
        {GUI_MODEL_VIDEO_REC_MSG_ID_VIDEO_REC_MENU, 0, 0},
        {GUI_MODEL_VIDEO_REC_MSG_ID_MIC_ICON, 0, 0},
        {GUI_MODEL_VIDEO_REC_MSG_ID_GSENSOR_ICON, 0, 0},
        {GUI_MODEL_VIDEO_REC_MSG_ID_SD_ICON, 0, 0},
        {GUI_MODEL_VIDEO_REC_MSG_ID_GUARD_STATE, 0, 0},
        {GUI_MODEL_VIDEO_REC_MSG_ID_CYC_STATE, 0, 0},
        {GUI_MODEL_VIDEO_REC_MSG_ID_MOTION_STATE, 0, 0},
        {GUI_MODEL_VIDEO_REC_MSG_ID_GAP_STATE, 0, 0},
        {GUI_MODEL_VIDEO_REC_MSG_ID_HDR_STATE, 0, 0},
        {GUI_MODEL_VIDEO_REC_MSG_ID_GRA_STATE, 0, 0},
        {GUI_MODEL_VIDEO_REC_MSG_ID_EXP_ICON, 0, 0},
        {GUI_MODEL_VIDEO_REC_MSG_ID_CAR_NUM, 0, 0},
        {GUI_MODEL_VIDEO_REC_MSG_ID_FLASH_HEADLIGHT, 0, 0},
        {GUI_MODEL_VIDEO_REC_MSG_ID_REC_ICON_STATE, 0, 0},
        {GUI_MODEL_VIDEO_REC_MSG_ID_KEY_STATE, 0, 0},
    };

    for (int i = 0; i < 30; i++) {
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

    lv_subject_t *subject_cycrec_icon = gui_msg_get_subject(GUI_MODEL_VIDEO_REC_MSG_ID_CYCREC_ICON);
    lv_subject_t *subject_cyc_state = gui_msg_get_subject(GUI_MODEL_VIDEO_REC_MSG_ID_CYC_STATE);
    lv_subject_t *subject_exp_icon = gui_msg_get_subject(GUI_MODEL_VIDEO_REC_MSG_ID_EXP_ICON);
    lv_subject_t *subject_motion_state = gui_msg_get_subject(GUI_MODEL_VIDEO_REC_MSG_ID_MOTION_STATE);
    lv_subject_t *subject_gap_state = gui_msg_get_subject(GUI_MODEL_VIDEO_REC_MSG_ID_GAP_STATE);
    lv_subject_t *subject_mic_icon = gui_msg_get_subject(GUI_MODEL_VIDEO_REC_MSG_ID_MIC_ICON);
    lv_subject_t *subject_hdr_state = gui_msg_get_subject(GUI_MODEL_VIDEO_REC_MSG_ID_HDR_STATE);
    lv_subject_t *subject_gsensor_icon = gui_msg_get_subject(GUI_MODEL_VIDEO_REC_MSG_ID_GSENSOR_ICON);
    lv_subject_t *subject_gra_state = gui_msg_get_subject(GUI_MODEL_VIDEO_REC_MSG_ID_GRA_STATE);
    lv_subject_t *subject_guard_state = gui_msg_get_subject(GUI_MODEL_VIDEO_REC_MSG_ID_GUARD_STATE);
    lv_subject_t *subject_rec_reso = gui_msg_get_subject(GUI_MODEL_VIDEO_REC_MSG_ID_REC_RESO);
    lv_subject_t *subject_sd_icon = gui_msg_get_subject(GUI_MODEL_VIDEO_REC_MSG_ID_SD_ICON);
    lv_subject_t *subject_rec_time_state = gui_msg_get_subject(GUI_MODEL_VIDEO_REC_MSG_ID_REC_TIME_STATE);
    lv_subject_t *subject_rec_remain_time = gui_msg_get_subject(GUI_MODEL_VIDEO_REC_MSG_ID_REC_REMAIN_TIME);
    lv_subject_t *subject_rec_icon_state = gui_msg_get_subject(GUI_MODEL_VIDEO_REC_MSG_ID_REC_ICON_STATE);
    lv_subject_t *subject_car_nunber = gui_msg_get_subject(GUI_MODEL_VIDEO_REC_MSG_ID_CAR_NUNBER);
    lv_subject_t *subject_car_num = gui_msg_get_subject(GUI_MODEL_VIDEO_REC_MSG_ID_CAR_NUM);
    lv_subject_t *subject_flash_headlight = gui_msg_get_subject(GUI_MODEL_VIDEO_REC_MSG_ID_FLASH_HEADLIGHT);
    lv_subject_t *subject_key_state = gui_msg_get_subject(GUI_MODEL_VIDEO_REC_MSG_ID_KEY_STATE);
    if (guider_ui.video_rec) {
        lv_ui_video_rec *ui_scr = ui_get_scr_ptr(&guider_ui, GUI_SCREEN_VIDEO_REC);
        gui_msg_setup_component(true, false, subject_cycrec_icon, ui_scr->video_rec_img_cyc_state, &guider_msg_data, gui_model_video_rec_msg_video_rec_img_cyc_state_set_img_path_cb, GUI_MODEL_VIDEO_REC_MSG_ID_CYCREC_ICON, GUI_MSG_ACCESS_GET, VALUE_INT, NULL);
        gui_msg_setup_component(true, false, subject_cyc_state, ui_scr->video_rec_img_cyc_state, &guider_msg_data, gui_msg_set_visible_by_bool_cb, GUI_MODEL_VIDEO_REC_MSG_ID_CYC_STATE, GUI_MSG_ACCESS_GET, VALUE_BOOL, NULL);

        gui_msg_setup_component(true, false, subject_exp_icon, ui_scr->video_rec_img_exp_state, &guider_msg_data, gui_model_video_rec_msg_video_rec_img_exp_state_set_img_path_cb, GUI_MODEL_VIDEO_REC_MSG_ID_EXP_ICON, GUI_MSG_ACCESS_GET, VALUE_INT, NULL);

        gui_msg_setup_component(true, false, subject_motion_state, ui_scr->video_rec_img_mot_state, &guider_msg_data, gui_msg_set_visible_by_bool_cb, GUI_MODEL_VIDEO_REC_MSG_ID_MOTION_STATE, GUI_MSG_ACCESS_GET, VALUE_BOOL, NULL);

        gui_msg_setup_component(true, false, subject_gap_state, ui_scr->video_rec_img_gap_state, &guider_msg_data, gui_msg_set_visible_by_bool_cb, GUI_MODEL_VIDEO_REC_MSG_ID_GAP_STATE, GUI_MSG_ACCESS_GET, VALUE_BOOL, NULL);

        gui_msg_setup_component(true, false, subject_mic_icon, ui_scr->video_rec_img_mic_state, &guider_msg_data, gui_model_video_rec_msg_video_rec_img_mic_state_set_img_path_cb, GUI_MODEL_VIDEO_REC_MSG_ID_MIC_ICON, GUI_MSG_ACCESS_GET, VALUE_INT, NULL);

        gui_msg_setup_component(true, false, subject_hdr_state, ui_scr->video_rec_img_hdr_state, &guider_msg_data, gui_msg_set_visible_by_bool_cb, GUI_MODEL_VIDEO_REC_MSG_ID_HDR_STATE, GUI_MSG_ACCESS_GET, VALUE_BOOL, NULL);

        gui_msg_setup_component(true, false, subject_gsensor_icon, ui_scr->video_rec_img_gra_state, &guider_msg_data, gui_model_video_rec_msg_video_rec_img_gra_state_set_img_path_cb, GUI_MODEL_VIDEO_REC_MSG_ID_GSENSOR_ICON, GUI_MSG_ACCESS_GET, VALUE_INT, NULL);
        gui_msg_setup_component(true, false, subject_gra_state, ui_scr->video_rec_img_gra_state, &guider_msg_data, gui_msg_set_visible_by_bool_cb, GUI_MODEL_VIDEO_REC_MSG_ID_GRA_STATE, GUI_MSG_ACCESS_GET, VALUE_BOOL, NULL);

        gui_msg_setup_component(true, false, subject_guard_state, ui_scr->video_rec_img_par_state, &guider_msg_data, gui_msg_set_visible_by_bool_cb, GUI_MODEL_VIDEO_REC_MSG_ID_GUARD_STATE, GUI_MSG_ACCESS_GET, VALUE_BOOL, NULL);

        gui_msg_setup_component(true, false, subject_rec_reso, ui_scr->video_rec_lbl_reso, &guider_msg_data, gui_msg_set_label_text_by_string_cb, GUI_MODEL_VIDEO_REC_MSG_ID_REC_RESO, GUI_MSG_ACCESS_GET, VALUE_STRING, NULL);

        gui_msg_setup_component(true, false, subject_sd_icon, ui_scr->video_rec_img_sd, &guider_msg_data, gui_model_video_rec_msg_video_rec_img_sd_set_img_path_cb, GUI_MODEL_VIDEO_REC_MSG_ID_SD_ICON, GUI_MSG_ACCESS_GET, VALUE_INT, NULL);

        gui_msg_setup_component(true, false, subject_rec_time_state, ui_scr->video_rec_digitclock_2, &guider_msg_data, gui_msg_set_control_state_by_int32_cb, GUI_MODEL_VIDEO_REC_MSG_ID_REC_TIME_STATE, GUI_MSG_ACCESS_GET, VALUE_INT, NULL);
        gui_msg_setup_component(true, false, subject_rec_remain_time, ui_scr->video_rec_digitclock_2, &guider_msg_data, gui_model_video_rec_msg_video_rec_digitclock_2_set_digit_clock_time_cb, GUI_MODEL_VIDEO_REC_MSG_ID_REC_REMAIN_TIME, GUI_MSG_ACCESS_GET, VALUE_TIME, NULL);

        gui_msg_setup_component(true, false, subject_rec_icon_state, ui_scr->video_rec_img_rec_state, &guider_msg_data, gui_msg_set_visible_by_bool_cb, GUI_MODEL_VIDEO_REC_MSG_ID_REC_ICON_STATE, GUI_MSG_ACCESS_GET, VALUE_BOOL, NULL);

        gui_msg_setup_component(true, false, subject_car_nunber, ui_scr->video_rec_lbl_num, &guider_msg_data, gui_msg_set_label_text_by_string_cb, GUI_MODEL_VIDEO_REC_MSG_ID_CAR_NUNBER, GUI_MSG_ACCESS_GET, VALUE_STRING, NULL);
        gui_msg_setup_component(true, false, subject_car_num, ui_scr->video_rec_lbl_num, &guider_msg_data, gui_msg_set_visible_by_bool_cb, GUI_MODEL_VIDEO_REC_MSG_ID_CAR_NUM, GUI_MSG_ACCESS_GET, VALUE_BOOL, NULL);

        gui_msg_setup_component(true, false, subject_flash_headlight, ui_scr->video_rec_img_headlight, &guider_msg_data, gui_msg_set_visible_by_bool_cb, GUI_MODEL_VIDEO_REC_MSG_ID_FLASH_HEADLIGHT, GUI_MSG_ACCESS_GET, VALUE_BOOL, NULL);

        gui_msg_setup_component(true, false, subject_key_state, ui_scr->video_rec_img_key_state, &guider_msg_data, gui_msg_set_visible_by_bool_cb, GUI_MODEL_VIDEO_REC_MSG_ID_KEY_STATE, GUI_MSG_ACCESS_GET, VALUE_BOOL, NULL);


        for (int i = 0; i < 30; i++) {
            if (status[i].msg_id == GUI_MODEL_VIDEO_REC_MSG_ID_CYCREC_ICON) {
                status[i].is_subscribe = 1;
            }
            if (status[i].msg_id == GUI_MODEL_VIDEO_REC_MSG_ID_CYC_STATE) {
                status[i].is_subscribe = 1;
            }
            if (status[i].msg_id == GUI_MODEL_VIDEO_REC_MSG_ID_EXP_ICON) {
                status[i].is_subscribe = 1;
            }
            if (status[i].msg_id == GUI_MODEL_VIDEO_REC_MSG_ID_MOTION_STATE) {
                status[i].is_subscribe = 1;
            }
            if (status[i].msg_id == GUI_MODEL_VIDEO_REC_MSG_ID_GAP_STATE) {
                status[i].is_subscribe = 1;
            }
            if (status[i].msg_id == GUI_MODEL_VIDEO_REC_MSG_ID_MIC_ICON) {
                status[i].is_subscribe = 1;
            }
            if (status[i].msg_id == GUI_MODEL_VIDEO_REC_MSG_ID_HDR_STATE) {
                status[i].is_subscribe = 1;
            }
            if (status[i].msg_id == GUI_MODEL_VIDEO_REC_MSG_ID_GSENSOR_ICON) {
                status[i].is_subscribe = 1;
            }
            if (status[i].msg_id == GUI_MODEL_VIDEO_REC_MSG_ID_GRA_STATE) {
                status[i].is_subscribe = 1;
            }
            if (status[i].msg_id == GUI_MODEL_VIDEO_REC_MSG_ID_GUARD_STATE) {
                status[i].is_subscribe = 1;
            }
            if (status[i].msg_id == GUI_MODEL_VIDEO_REC_MSG_ID_REC_RESO) {
                status[i].is_subscribe = 1;
            }
            if (status[i].msg_id == GUI_MODEL_VIDEO_REC_MSG_ID_SD_ICON) {
                status[i].is_subscribe = 1;
            }
            if (status[i].msg_id == GUI_MODEL_VIDEO_REC_MSG_ID_REC_TIME_STATE) {
                status[i].is_subscribe = 1;
            }
            if (status[i].msg_id == GUI_MODEL_VIDEO_REC_MSG_ID_REC_REMAIN_TIME) {
                status[i].is_subscribe = 1;
            }
            if (status[i].msg_id == GUI_MODEL_VIDEO_REC_MSG_ID_REC_ICON_STATE) {
                status[i].is_subscribe = 1;
            }
            if (status[i].msg_id == GUI_MODEL_VIDEO_REC_MSG_ID_CAR_NUNBER) {
                status[i].is_subscribe = 1;
            }
            if (status[i].msg_id == GUI_MODEL_VIDEO_REC_MSG_ID_CAR_NUM) {
                status[i].is_subscribe = 1;
            }
            if (status[i].msg_id == GUI_MODEL_VIDEO_REC_MSG_ID_FLASH_HEADLIGHT) {
                status[i].is_subscribe = 1;
            }
            if (status[i].msg_id == GUI_MODEL_VIDEO_REC_MSG_ID_KEY_STATE) {
                status[i].is_subscribe = 1;
            }
        }
    }
    if (guider_ui.video_photo) {
        lv_ui_video_photo *ui_scr = ui_get_scr_ptr(&guider_ui, GUI_SCREEN_VIDEO_PHOTO);
        gui_msg_setup_component(true, false, subject_sd_icon, ui_scr->video_photo_img_sd_icon, &guider_msg_data, gui_model_video_rec_msg_video_photo_img_sd_icon_set_img_path_cb, GUI_MODEL_VIDEO_REC_MSG_ID_SD_ICON, GUI_MSG_ACCESS_GET, VALUE_INT, NULL);


        for (int i = 0; i < 30; i++) {
            if (status[i].msg_id == GUI_MODEL_VIDEO_REC_MSG_ID_SD_ICON) {
                status[i].is_subscribe = 1;
            }
        }
    }

    for (int i = 0; i < 30; i++) {
        if (status[i].is_subscribe == 0 && status[i].is_unsubscribe == 1) {
            gui_msg_subscribe_change(status[i].msg_id, GUI_MSG_UNSUBSCRIBE);
        } else if (status[i].is_subscribe == 1 && status[i].is_unsubscribe == 0) {
            gui_msg_subscribe_change(status[i].msg_id, GUI_MSG_SUBSCRIBE);
        }
    }
}

void gui_model_video_rec_msg_unsubscribe()
{
    _gui_msg_status_t status[30] = {
        {GUI_MODEL_VIDEO_REC_MSG_ID_CYCREC_ICON, 0, 0},
        {GUI_MODEL_VIDEO_REC_MSG_ID_DELAYREC_ICON, 0, 0},
        {GUI_MODEL_VIDEO_REC_MSG_ID_CAR_NUNBER, 0, 0},
        {GUI_MODEL_VIDEO_REC_MSG_ID_REC_RESO, 0, 0},
        {GUI_MODEL_VIDEO_REC_MSG_ID_REC_BTN, 0, 0},
        {GUI_MODEL_VIDEO_REC_MSG_ID_SHOW_GSENSOR_ICON, 0, 0},
        {GUI_MODEL_VIDEO_REC_MSG_ID_HIDE_GSENSOR_ICON, 0, 0},
        {GUI_MODEL_VIDEO_REC_MSG_ID_SHOW_GUARD_ICON, 0, 0},
        {GUI_MODEL_VIDEO_REC_MSG_ID_HIDE_GUARD_ICON, 0, 0},
        {GUI_MODEL_VIDEO_REC_MSG_ID_SHOW_MOTION_ICON, 0, 0},
        {GUI_MODEL_VIDEO_REC_MSG_ID_HIDE_MOTION_ICON, 0, 0},
        {GUI_MODEL_VIDEO_REC_MSG_ID_SHOW_HDR_ICON, 0, 0},
        {GUI_MODEL_VIDEO_REC_MSG_ID_HIDE_HDR_ICON, 0, 0},
        {GUI_MODEL_VIDEO_REC_MSG_ID_REC_REMAIN_TIME, 0, 0},
        {GUI_MODEL_VIDEO_REC_MSG_ID_REC_TIME_STATE, 0, 0},
        {GUI_MODEL_VIDEO_REC_MSG_ID_VIDEO_REC_MENU, 0, 0},
        {GUI_MODEL_VIDEO_REC_MSG_ID_MIC_ICON, 0, 0},
        {GUI_MODEL_VIDEO_REC_MSG_ID_GSENSOR_ICON, 0, 0},
        {GUI_MODEL_VIDEO_REC_MSG_ID_SD_ICON, 0, 0},
        {GUI_MODEL_VIDEO_REC_MSG_ID_GUARD_STATE, 0, 0},
        {GUI_MODEL_VIDEO_REC_MSG_ID_CYC_STATE, 0, 0},
        {GUI_MODEL_VIDEO_REC_MSG_ID_MOTION_STATE, 0, 0},
        {GUI_MODEL_VIDEO_REC_MSG_ID_GAP_STATE, 0, 0},
        {GUI_MODEL_VIDEO_REC_MSG_ID_HDR_STATE, 0, 0},
        {GUI_MODEL_VIDEO_REC_MSG_ID_GRA_STATE, 0, 0},
        {GUI_MODEL_VIDEO_REC_MSG_ID_EXP_ICON, 0, 0},
        {GUI_MODEL_VIDEO_REC_MSG_ID_CAR_NUM, 0, 0},
        {GUI_MODEL_VIDEO_REC_MSG_ID_FLASH_HEADLIGHT, 0, 0},
        {GUI_MODEL_VIDEO_REC_MSG_ID_REC_ICON_STATE, 0, 0},
        {GUI_MODEL_VIDEO_REC_MSG_ID_KEY_STATE, 0, 0},
    };
    for (int i = 0; i < 30; i++) {
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

    for (int i = 0; i < 30; i++) {
        if (status[i].is_unsubscribe == 1) {
            gui_msg_subscribe_change(status[i].msg_id, GUI_MSG_UNSUBSCRIBE);
        }
    }
}

gui_msg_status_t gui_model_video_rec_msg_send(int32_t msg_id, void *value, int32_t len)
{
    if (msg_id == GUI_MODEL_VIDEO_REC_MSG_ID) {
    } else {
        gui_msg_data_type_t data_type = VALUE_INT;
        switch (msg_id) {
        case GUI_MODEL_VIDEO_REC_MSG_ID_SHOW_GSENSOR_ICON:
        case GUI_MODEL_VIDEO_REC_MSG_ID_HIDE_GSENSOR_ICON:
        case GUI_MODEL_VIDEO_REC_MSG_ID_SHOW_GUARD_ICON:
        case GUI_MODEL_VIDEO_REC_MSG_ID_HIDE_GUARD_ICON:
        case GUI_MODEL_VIDEO_REC_MSG_ID_SHOW_MOTION_ICON:
        case GUI_MODEL_VIDEO_REC_MSG_ID_HIDE_MOTION_ICON:
        case GUI_MODEL_VIDEO_REC_MSG_ID_SHOW_HDR_ICON:
        case GUI_MODEL_VIDEO_REC_MSG_ID_HIDE_HDR_ICON: {
            data_type = VALUE_INT;
            guider_msg_data.value_array.ptr = value;
            guider_msg_data.value_array.len = len;
        }
        break;
        case GUI_MODEL_VIDEO_REC_MSG_ID_REC_BTN:
        case GUI_MODEL_VIDEO_REC_MSG_ID_REC_TIME_STATE: {
            data_type = VALUE_INT;
            guider_msg_data.value_array.ptr = value;
            guider_msg_data.value_array.len = len;
        }
        break;
        case GUI_MODEL_VIDEO_REC_MSG_ID_VIDEO_REC_MENU:
        case GUI_MODEL_VIDEO_REC_MSG_ID_GUARD_STATE:
        case GUI_MODEL_VIDEO_REC_MSG_ID_CYC_STATE:
        case GUI_MODEL_VIDEO_REC_MSG_ID_MOTION_STATE:
        case GUI_MODEL_VIDEO_REC_MSG_ID_GAP_STATE:
        case GUI_MODEL_VIDEO_REC_MSG_ID_HDR_STATE:
        case GUI_MODEL_VIDEO_REC_MSG_ID_GRA_STATE:
        case GUI_MODEL_VIDEO_REC_MSG_ID_CAR_NUM:
        case GUI_MODEL_VIDEO_REC_MSG_ID_FLASH_HEADLIGHT:
        case GUI_MODEL_VIDEO_REC_MSG_ID_REC_ICON_STATE:
        case GUI_MODEL_VIDEO_REC_MSG_ID_KEY_STATE: {
            data_type = VALUE_BOOL;
            guider_msg_data.value_array.ptr = value;
            guider_msg_data.value_array.len = len;
        }
        break;
        case GUI_MODEL_VIDEO_REC_MSG_ID_CYCREC_ICON:
        case GUI_MODEL_VIDEO_REC_MSG_ID_DELAYREC_ICON:
        case GUI_MODEL_VIDEO_REC_MSG_ID_MIC_ICON:
        case GUI_MODEL_VIDEO_REC_MSG_ID_GSENSOR_ICON:
        case GUI_MODEL_VIDEO_REC_MSG_ID_SD_ICON:
        case GUI_MODEL_VIDEO_REC_MSG_ID_EXP_ICON: {
            data_type = VALUE_INT;
            guider_msg_data.value_array.ptr = value;
            guider_msg_data.value_array.len = len;
        }
        break;
        case GUI_MODEL_VIDEO_REC_MSG_ID_CAR_NUNBER:
        case GUI_MODEL_VIDEO_REC_MSG_ID_REC_RESO: {
            data_type = VALUE_STRING;
            guider_msg_data.value_array.ptr = value;
            guider_msg_data.value_array.len = len;
        }
        break;
        case GUI_MODEL_VIDEO_REC_MSG_ID_REC_REMAIN_TIME: {
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
