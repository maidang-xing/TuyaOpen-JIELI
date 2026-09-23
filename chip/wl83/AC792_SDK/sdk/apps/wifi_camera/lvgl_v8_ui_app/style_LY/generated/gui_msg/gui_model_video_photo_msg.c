#include "app_config.h"
#ifdef CONFIG_UI_STYLE_LY_ENABLE
/*Generate Code, Do NOT Edit!*/
#include "./gui_model_video_photo_msg.h"
#if LV_USE_OBSERVER

static lv_ll_t subs_ll;

#if LV_USE_GUIBUILDER_SIMULATOR
_gui_msg_entry_t gui_model_video_photo_msg_entry_table[] = {
    { GUI_MODEL_VIDEO_PHOTO_MSG_ID_RESOLUTION_ICON, gui_model_video_photo_msg_resolution_icon_cb, VALUE_STRING },
    { GUI_MODEL_VIDEO_PHOTO_MSG_ID_AWB_ICON, gui_model_video_photo_msg_awb_icon_cb, VALUE_INT },
    { GUI_MODEL_VIDEO_PHOTO_MSG_ID_QUALITY_ICON, gui_model_video_photo_msg_quality_icon_cb, VALUE_INT },
    { GUI_MODEL_VIDEO_PHOTO_MSG_ID_SHOT_MODE_ICON, gui_model_video_photo_msg_shot_mode_icon_cb, VALUE_INT },
    { GUI_MODEL_VIDEO_PHOTO_MSG_ID_SHOW_HANDSHAKE, gui_model_video_photo_msg_show_handshake_cb, VALUE_INT },
    { GUI_MODEL_VIDEO_PHOTO_MSG_ID_HIDE_HANDSHAKE, gui_model_video_photo_msg_hide_handshake_cb, VALUE_INT },
    { GUI_MODEL_VIDEO_PHOTO_MSG_ID_SHOW_SHOTS, gui_model_video_photo_msg_show_shots_cb, VALUE_INT },
    { GUI_MODEL_VIDEO_PHOTO_MSG_ID_HIDE_SHOTS, gui_model_video_photo_msg_hide_shots_cb, VALUE_INT },
    { GUI_MODEL_VIDEO_PHOTO_MSG_ID_SHOW_SHOTS_MODE, gui_model_video_photo_msg_show_shots_mode_cb, VALUE_INT },
    { GUI_MODEL_VIDEO_PHOTO_MSG_ID_HIDE_SHOTS_MODE, gui_model_video_photo_msg_hide_shots_mode_cb, VALUE_INT },
    { GUI_MODEL_VIDEO_PHOTO_MSG_ID_PHOTO_REMAIN, gui_model_video_photo_msg_photo_remain_cb, VALUE_STRING },
    { GUI_MODEL_VIDEO_PHOTO_MSG_ID_PEXP_ICON, gui_model_video_photo_msg_pexp_icon_cb, VALUE_INT },
    { GUI_MODEL_VIDEO_PHOTO_MSG_ID_ISO_ICON, gui_model_video_photo_msg_iso_icon_cb, VALUE_INT },
    { GUI_MODEL_VIDEO_PHOTO_MSG_ID_DELAY_SATE, gui_model_video_photo_msg_delay_sate_cb, VALUE_BOOL },
    { GUI_MODEL_VIDEO_PHOTO_MSG_ID_DELAY_ICON, gui_model_video_photo_msg_delay_icon_cb, VALUE_INT },
    { GUI_MODEL_VIDEO_PHOTO_MSG_ID_HANDSHAKE_ICON, gui_model_video_photo_msg_handshake_icon_cb, VALUE_INT },
    { GUI_MODEL_VIDEO_PHOTO_MSG_ID_SHOTS_ICON, gui_model_video_photo_msg_shots_icon_cb, VALUE_BOOL },
    { GUI_MODEL_VIDEO_PHOTO_MSG_ID_PHOTO_RESO, gui_model_video_photo_msg_photo_reso_cb, VALUE_STRING },
};
#endif

void gui_model_video_photo_msg_video_photo_img_exp_icon_set_img_path_cb(lv_observer_t *observer, lv_subject_t *subject)
{
    lv_obj_t *obj = lv_observer_get_target_obj(observer);
    if (obj == NULL || lv_obj_is_valid(obj) == false) {
        return;
    }

    gui_msg_data_t *data = (gui_msg_data_t *)observer->user_data;
    lv_img_set_src(obj, gui_get_res_path(data->value_int));
}
void gui_model_video_photo_msg_video_photo_img_awb_icon_set_img_path_cb(lv_observer_t *observer, lv_subject_t *subject)
{
    lv_obj_t *obj = lv_observer_get_target_obj(observer);
    if (obj == NULL || lv_obj_is_valid(obj) == false) {
        return;
    }

    gui_msg_data_t *data = (gui_msg_data_t *)observer->user_data;
    lv_img_set_src(obj, gui_get_res_path(data->value_int));
}
void gui_model_video_photo_msg_video_photo_img_iso_icon_set_img_path_cb(lv_observer_t *observer, lv_subject_t *subject)
{
    lv_obj_t *obj = lv_observer_get_target_obj(observer);
    if (obj == NULL || lv_obj_is_valid(obj) == false) {
        return;
    }

    gui_msg_data_t *data = (gui_msg_data_t *)observer->user_data;
    lv_img_set_src(obj, gui_get_res_path(data->value_int));
}
void gui_model_video_photo_msg_video_photo_img_qua_icon_set_img_path_cb(lv_observer_t *observer, lv_subject_t *subject)
{
    lv_obj_t *obj = lv_observer_get_target_obj(observer);
    if (obj == NULL || lv_obj_is_valid(obj) == false) {
        return;
    }

    gui_msg_data_t *data = (gui_msg_data_t *)observer->user_data;
    lv_img_set_src(obj, gui_get_res_path(data->value_int));
}
void gui_model_video_photo_msg_video_photo_img_delay_icon_set_img_path_cb(lv_observer_t *observer, lv_subject_t *subject)
{
    lv_obj_t *obj = lv_observer_get_target_obj(observer);
    if (obj == NULL || lv_obj_is_valid(obj) == false) {
        return;
    }

    gui_msg_data_t *data = (gui_msg_data_t *)observer->user_data;
    lv_img_set_src(obj, gui_get_res_path(data->value_int));
}
void gui_model_video_photo_msg_video_photo_img_shake_icon_set_img_path_cb(lv_observer_t *observer, lv_subject_t *subject)
{
    lv_obj_t *obj = lv_observer_get_target_obj(observer);
    if (obj == NULL || lv_obj_is_valid(obj) == false) {
        return;
    }

    gui_msg_data_t *data = (gui_msg_data_t *)observer->user_data;
    lv_img_set_src(obj, gui_get_res_path(data->value_int));
}

GUI_WEAK int gui_model_video_photo_msg_resolution_icon_cb(gui_msg_action_t access, gui_msg_data_t *data, gui_msg_data_type_t type)
{
    char resolution_icon_init_var[] = "1M";
    static bool resolution_icon_is_init = false;
    static char *resolution_icon_var = NULL;
    _gui_msg_char_array_cb(&resolution_icon_var, resolution_icon_init_var, &resolution_icon_is_init, access, data);
    return 0;
}
GUI_WEAK int gui_model_video_photo_msg_awb_icon_cb(gui_msg_action_t access, gui_msg_data_t *data, gui_msg_data_type_t type)
{
    static int32_t awb_icon_var = RES_AWB_AUTO;
    _gui_msg_int32_cb(&awb_icon_var, access, data);
    return 0;
}
GUI_WEAK int gui_model_video_photo_msg_quality_icon_cb(gui_msg_action_t access, gui_msg_data_t *data, gui_msg_data_type_t type)
{
    static int32_t quality_icon_var = RES_Q3;
    _gui_msg_int32_cb(&quality_icon_var, access, data);
    return 0;
}
GUI_WEAK int gui_model_video_photo_msg_shot_mode_icon_cb(gui_msg_action_t access, gui_msg_data_t *data, gui_msg_data_type_t type)
{
    static int32_t shot_mode_icon_var = RES_TIMING_PHOTO_2;
    _gui_msg_int32_cb(&shot_mode_icon_var, access, data);
    return 0;
}
GUI_WEAK int gui_model_video_photo_msg_show_handshake_cb(gui_msg_action_t access, gui_msg_data_t *data, gui_msg_data_type_t type)
{
    static lv_obj_flag_t show_handshake_var = LV_OBJ_FLAG_HIDDEN;
    _gui_msg_obj_flag_cb(&show_handshake_var, access, data);
    return 0;
}
GUI_WEAK int gui_model_video_photo_msg_hide_handshake_cb(gui_msg_action_t access, gui_msg_data_t *data, gui_msg_data_type_t type)
{
    static lv_obj_flag_t hide_handshake_var = LV_OBJ_FLAG_HIDDEN;
    _gui_msg_obj_flag_cb(&hide_handshake_var, access, data);
    return 0;
}
GUI_WEAK int gui_model_video_photo_msg_show_shots_cb(gui_msg_action_t access, gui_msg_data_t *data, gui_msg_data_type_t type)
{
    static lv_obj_flag_t show_shots_var = LV_OBJ_FLAG_HIDDEN;
    _gui_msg_obj_flag_cb(&show_shots_var, access, data);
    return 0;
}
GUI_WEAK int gui_model_video_photo_msg_hide_shots_cb(gui_msg_action_t access, gui_msg_data_t *data, gui_msg_data_type_t type)
{
    static lv_obj_flag_t hide_shots_var = LV_OBJ_FLAG_HIDDEN;
    _gui_msg_obj_flag_cb(&hide_shots_var, access, data);
    return 0;
}
GUI_WEAK int gui_model_video_photo_msg_show_shots_mode_cb(gui_msg_action_t access, gui_msg_data_t *data, gui_msg_data_type_t type)
{
    static lv_obj_flag_t show_shots_mode_var = LV_OBJ_FLAG_HIDDEN;
    _gui_msg_obj_flag_cb(&show_shots_mode_var, access, data);
    return 0;
}
GUI_WEAK int gui_model_video_photo_msg_hide_shots_mode_cb(gui_msg_action_t access, gui_msg_data_t *data, gui_msg_data_type_t type)
{
    static lv_obj_flag_t hide_shots_mode_var = LV_OBJ_FLAG_HIDDEN;
    _gui_msg_obj_flag_cb(&hide_shots_mode_var, access, data);
    return 0;
}
GUI_WEAK int gui_model_video_photo_msg_photo_remain_cb(gui_msg_action_t access, gui_msg_data_t *data, gui_msg_data_type_t type)
{
    char photo_remain_init_var[] = "99999999";
    static bool photo_remain_is_init = false;
    static char *photo_remain_var = NULL;
    _gui_msg_char_array_cb(&photo_remain_var, photo_remain_init_var, &photo_remain_is_init, access, data);
    return 0;
}
GUI_WEAK int gui_model_video_photo_msg_pexp_icon_cb(gui_msg_action_t access, gui_msg_data_t *data, gui_msg_data_type_t type)
{
    static int32_t pexp_icon_var = RES_EXP_A0;
    _gui_msg_int32_cb(&pexp_icon_var, access, data);
    return 0;
}
GUI_WEAK int gui_model_video_photo_msg_iso_icon_cb(gui_msg_action_t access, gui_msg_data_t *data, gui_msg_data_type_t type)
{
    static int32_t iso_icon_var = RES_ISO_AUTO;
    _gui_msg_int32_cb(&iso_icon_var, access, data);
    return 0;
}
GUI_WEAK int gui_model_video_photo_msg_delay_sate_cb(gui_msg_action_t access, gui_msg_data_t *data, gui_msg_data_type_t type)
{
    static bool delay_sate_var = false;
    _gui_msg_bool_cb(&delay_sate_var, access, data);
    return 0;
}
GUI_WEAK int gui_model_video_photo_msg_delay_icon_cb(gui_msg_action_t access, gui_msg_data_t *data, gui_msg_data_type_t type)
{
    static int32_t delay_icon_var = RES_DL2;
    _gui_msg_int32_cb(&delay_icon_var, access, data);
    return 0;
}
GUI_WEAK int gui_model_video_photo_msg_handshake_icon_cb(gui_msg_action_t access, gui_msg_data_t *data, gui_msg_data_type_t type)
{
    static int32_t handshake_icon_var = RES_SHAKE_OFF;
    _gui_msg_int32_cb(&handshake_icon_var, access, data);
    return 0;
}
GUI_WEAK int gui_model_video_photo_msg_shots_icon_cb(gui_msg_action_t access, gui_msg_data_t *data, gui_msg_data_type_t type)
{
    static bool shots_icon_var = false;
    _gui_msg_bool_cb(&shots_icon_var, access, data);
    return 0;
}
GUI_WEAK int gui_model_video_photo_msg_photo_reso_cb(gui_msg_action_t access, gui_msg_data_t *data, gui_msg_data_type_t type)
{
    char photo_reso_init_var[] = "VGA";
    static bool photo_reso_is_init = false;
    static char *photo_reso_var = NULL;
    _gui_msg_char_array_cb(&photo_reso_var, photo_reso_init_var, &photo_reso_is_init, access, data);
    return 0;
}

void gui_model_video_photo_msg_init(lv_ui *ui)
{
    int32_t ids[18] = {
        GUI_MODEL_VIDEO_PHOTO_MSG_ID_RESOLUTION_ICON,
        GUI_MODEL_VIDEO_PHOTO_MSG_ID_AWB_ICON,
        GUI_MODEL_VIDEO_PHOTO_MSG_ID_QUALITY_ICON,
        GUI_MODEL_VIDEO_PHOTO_MSG_ID_SHOT_MODE_ICON,
        GUI_MODEL_VIDEO_PHOTO_MSG_ID_SHOW_HANDSHAKE,
        GUI_MODEL_VIDEO_PHOTO_MSG_ID_HIDE_HANDSHAKE,
        GUI_MODEL_VIDEO_PHOTO_MSG_ID_SHOW_SHOTS,
        GUI_MODEL_VIDEO_PHOTO_MSG_ID_HIDE_SHOTS,
        GUI_MODEL_VIDEO_PHOTO_MSG_ID_SHOW_SHOTS_MODE,
        GUI_MODEL_VIDEO_PHOTO_MSG_ID_HIDE_SHOTS_MODE,
        GUI_MODEL_VIDEO_PHOTO_MSG_ID_PHOTO_REMAIN,
        GUI_MODEL_VIDEO_PHOTO_MSG_ID_PEXP_ICON,
        GUI_MODEL_VIDEO_PHOTO_MSG_ID_ISO_ICON,
        GUI_MODEL_VIDEO_PHOTO_MSG_ID_DELAY_SATE,
        GUI_MODEL_VIDEO_PHOTO_MSG_ID_DELAY_ICON,
        GUI_MODEL_VIDEO_PHOTO_MSG_ID_HANDSHAKE_ICON,
        GUI_MODEL_VIDEO_PHOTO_MSG_ID_SHOTS_ICON,
        GUI_MODEL_VIDEO_PHOTO_MSG_ID_PHOTO_RESO,
    };
    for (int i = 0; i < 18; i++) {
        gui_msg_sub_t *sub = gui_msg_create_sub(ids[i]);
        if (sub != NULL) {
            lv_subject_init_pointer(sub->subject, &guider_msg_data);
        }
    }
}

void gui_model_video_photo_msg_init_ui()
{
}

void gui_model_video_photo_msg_init_events()
{
    void *res = NULL;
    _gui_msg_status_t status[18] = {
        {GUI_MODEL_VIDEO_PHOTO_MSG_ID_RESOLUTION_ICON, 0, 0},
        {GUI_MODEL_VIDEO_PHOTO_MSG_ID_AWB_ICON, 0, 0},
        {GUI_MODEL_VIDEO_PHOTO_MSG_ID_QUALITY_ICON, 0, 0},
        {GUI_MODEL_VIDEO_PHOTO_MSG_ID_SHOT_MODE_ICON, 0, 0},
        {GUI_MODEL_VIDEO_PHOTO_MSG_ID_SHOW_HANDSHAKE, 0, 0},
        {GUI_MODEL_VIDEO_PHOTO_MSG_ID_HIDE_HANDSHAKE, 0, 0},
        {GUI_MODEL_VIDEO_PHOTO_MSG_ID_SHOW_SHOTS, 0, 0},
        {GUI_MODEL_VIDEO_PHOTO_MSG_ID_HIDE_SHOTS, 0, 0},
        {GUI_MODEL_VIDEO_PHOTO_MSG_ID_SHOW_SHOTS_MODE, 0, 0},
        {GUI_MODEL_VIDEO_PHOTO_MSG_ID_HIDE_SHOTS_MODE, 0, 0},
        {GUI_MODEL_VIDEO_PHOTO_MSG_ID_PHOTO_REMAIN, 0, 0},
        {GUI_MODEL_VIDEO_PHOTO_MSG_ID_PEXP_ICON, 0, 0},
        {GUI_MODEL_VIDEO_PHOTO_MSG_ID_ISO_ICON, 0, 0},
        {GUI_MODEL_VIDEO_PHOTO_MSG_ID_DELAY_SATE, 0, 0},
        {GUI_MODEL_VIDEO_PHOTO_MSG_ID_DELAY_ICON, 0, 0},
        {GUI_MODEL_VIDEO_PHOTO_MSG_ID_HANDSHAKE_ICON, 0, 0},
        {GUI_MODEL_VIDEO_PHOTO_MSG_ID_SHOTS_ICON, 0, 0},
        {GUI_MODEL_VIDEO_PHOTO_MSG_ID_PHOTO_RESO, 0, 0},
    };

    for (int i = 0; i < 18; i++) {
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

    lv_subject_t *subject_pexp_icon = gui_msg_get_subject(GUI_MODEL_VIDEO_PHOTO_MSG_ID_PEXP_ICON);
    lv_subject_t *subject_awb_icon = gui_msg_get_subject(GUI_MODEL_VIDEO_PHOTO_MSG_ID_AWB_ICON);
    lv_subject_t *subject_iso_icon = gui_msg_get_subject(GUI_MODEL_VIDEO_PHOTO_MSG_ID_ISO_ICON);
    lv_subject_t *subject_quality_icon = gui_msg_get_subject(GUI_MODEL_VIDEO_PHOTO_MSG_ID_QUALITY_ICON);
    lv_subject_t *subject_delay_icon = gui_msg_get_subject(GUI_MODEL_VIDEO_PHOTO_MSG_ID_DELAY_ICON);
    lv_subject_t *subject_delay_sate = gui_msg_get_subject(GUI_MODEL_VIDEO_PHOTO_MSG_ID_DELAY_SATE);
    lv_subject_t *subject_handshake_icon = gui_msg_get_subject(GUI_MODEL_VIDEO_PHOTO_MSG_ID_HANDSHAKE_ICON);
    lv_subject_t *subject_shots_icon = gui_msg_get_subject(GUI_MODEL_VIDEO_PHOTO_MSG_ID_SHOTS_ICON);
    lv_subject_t *subject_photo_reso = gui_msg_get_subject(GUI_MODEL_VIDEO_PHOTO_MSG_ID_PHOTO_RESO);
    lv_subject_t *subject_photo_remain = gui_msg_get_subject(GUI_MODEL_VIDEO_PHOTO_MSG_ID_PHOTO_REMAIN);
    if (guider_ui.video_photo) {
        lv_ui_video_photo *ui_scr = ui_get_scr_ptr(&guider_ui, GUI_SCREEN_VIDEO_PHOTO);
        gui_msg_setup_component(true, false, subject_pexp_icon, ui_scr->video_photo_img_exp_icon, &guider_msg_data, gui_model_video_photo_msg_video_photo_img_exp_icon_set_img_path_cb, GUI_MODEL_VIDEO_PHOTO_MSG_ID_PEXP_ICON, GUI_MSG_ACCESS_GET, VALUE_INT, NULL);

        gui_msg_setup_component(true, false, subject_awb_icon, ui_scr->video_photo_img_awb_icon, &guider_msg_data, gui_model_video_photo_msg_video_photo_img_awb_icon_set_img_path_cb, GUI_MODEL_VIDEO_PHOTO_MSG_ID_AWB_ICON, GUI_MSG_ACCESS_GET, VALUE_INT, NULL);

        gui_msg_setup_component(true, false, subject_iso_icon, ui_scr->video_photo_img_iso_icon, &guider_msg_data, gui_model_video_photo_msg_video_photo_img_iso_icon_set_img_path_cb, GUI_MODEL_VIDEO_PHOTO_MSG_ID_ISO_ICON, GUI_MSG_ACCESS_GET, VALUE_INT, NULL);

        gui_msg_setup_component(true, false, subject_quality_icon, ui_scr->video_photo_img_qua_icon, &guider_msg_data, gui_model_video_photo_msg_video_photo_img_qua_icon_set_img_path_cb, GUI_MODEL_VIDEO_PHOTO_MSG_ID_QUALITY_ICON, GUI_MSG_ACCESS_GET, VALUE_INT, NULL);

        gui_msg_setup_component(true, false, subject_delay_icon, ui_scr->video_photo_img_delay_icon, &guider_msg_data, gui_model_video_photo_msg_video_photo_img_delay_icon_set_img_path_cb, GUI_MODEL_VIDEO_PHOTO_MSG_ID_DELAY_ICON, GUI_MSG_ACCESS_GET, VALUE_INT, NULL);
        gui_msg_setup_component(true, false, subject_delay_sate, ui_scr->video_photo_img_delay_icon, &guider_msg_data, gui_msg_set_visible_by_bool_cb, GUI_MODEL_VIDEO_PHOTO_MSG_ID_DELAY_SATE, GUI_MSG_ACCESS_GET, VALUE_BOOL, NULL);

        gui_msg_setup_component(true, false, subject_handshake_icon, ui_scr->video_photo_img_shake_icon, &guider_msg_data, gui_model_video_photo_msg_video_photo_img_shake_icon_set_img_path_cb, GUI_MODEL_VIDEO_PHOTO_MSG_ID_HANDSHAKE_ICON, GUI_MSG_ACCESS_GET, VALUE_INT, NULL);

        gui_msg_setup_component(true, false, subject_shots_icon, ui_scr->video_photo_img_repeat_icon, &guider_msg_data, gui_msg_set_visible_by_bool_cb, GUI_MODEL_VIDEO_PHOTO_MSG_ID_SHOTS_ICON, GUI_MSG_ACCESS_GET, VALUE_BOOL, NULL);

        gui_msg_setup_component(true, false, subject_photo_reso, ui_scr->video_photo_lbl_photo_reso, &guider_msg_data, gui_msg_set_label_text_by_string_cb, GUI_MODEL_VIDEO_PHOTO_MSG_ID_PHOTO_RESO, GUI_MSG_ACCESS_GET, VALUE_STRING, NULL);

        gui_msg_setup_component(true, false, subject_photo_remain, ui_scr->video_photo_lbl_remain_pnum, &guider_msg_data, gui_msg_set_label_text_by_string_cb, GUI_MODEL_VIDEO_PHOTO_MSG_ID_PHOTO_REMAIN, GUI_MSG_ACCESS_GET, VALUE_STRING, NULL);


        for (int i = 0; i < 18; i++) {
            if (status[i].msg_id == GUI_MODEL_VIDEO_PHOTO_MSG_ID_PEXP_ICON) {
                status[i].is_subscribe = 1;
            }
            if (status[i].msg_id == GUI_MODEL_VIDEO_PHOTO_MSG_ID_AWB_ICON) {
                status[i].is_subscribe = 1;
            }
            if (status[i].msg_id == GUI_MODEL_VIDEO_PHOTO_MSG_ID_ISO_ICON) {
                status[i].is_subscribe = 1;
            }
            if (status[i].msg_id == GUI_MODEL_VIDEO_PHOTO_MSG_ID_QUALITY_ICON) {
                status[i].is_subscribe = 1;
            }
            if (status[i].msg_id == GUI_MODEL_VIDEO_PHOTO_MSG_ID_DELAY_ICON) {
                status[i].is_subscribe = 1;
            }
            if (status[i].msg_id == GUI_MODEL_VIDEO_PHOTO_MSG_ID_DELAY_SATE) {
                status[i].is_subscribe = 1;
            }
            if (status[i].msg_id == GUI_MODEL_VIDEO_PHOTO_MSG_ID_HANDSHAKE_ICON) {
                status[i].is_subscribe = 1;
            }
            if (status[i].msg_id == GUI_MODEL_VIDEO_PHOTO_MSG_ID_SHOTS_ICON) {
                status[i].is_subscribe = 1;
            }
            if (status[i].msg_id == GUI_MODEL_VIDEO_PHOTO_MSG_ID_PHOTO_RESO) {
                status[i].is_subscribe = 1;
            }
            if (status[i].msg_id == GUI_MODEL_VIDEO_PHOTO_MSG_ID_PHOTO_REMAIN) {
                status[i].is_subscribe = 1;
            }
        }
    }

    for (int i = 0; i < 18; i++) {
        if (status[i].is_subscribe == 0 && status[i].is_unsubscribe == 1) {
            gui_msg_subscribe_change(status[i].msg_id, GUI_MSG_UNSUBSCRIBE);
        } else if (status[i].is_subscribe == 1 && status[i].is_unsubscribe == 0) {
            gui_msg_subscribe_change(status[i].msg_id, GUI_MSG_SUBSCRIBE);
        }
    }
}

void gui_model_video_photo_msg_unsubscribe()
{
    _gui_msg_status_t status[18] = {
        {GUI_MODEL_VIDEO_PHOTO_MSG_ID_RESOLUTION_ICON, 0, 0},
        {GUI_MODEL_VIDEO_PHOTO_MSG_ID_AWB_ICON, 0, 0},
        {GUI_MODEL_VIDEO_PHOTO_MSG_ID_QUALITY_ICON, 0, 0},
        {GUI_MODEL_VIDEO_PHOTO_MSG_ID_SHOT_MODE_ICON, 0, 0},
        {GUI_MODEL_VIDEO_PHOTO_MSG_ID_SHOW_HANDSHAKE, 0, 0},
        {GUI_MODEL_VIDEO_PHOTO_MSG_ID_HIDE_HANDSHAKE, 0, 0},
        {GUI_MODEL_VIDEO_PHOTO_MSG_ID_SHOW_SHOTS, 0, 0},
        {GUI_MODEL_VIDEO_PHOTO_MSG_ID_HIDE_SHOTS, 0, 0},
        {GUI_MODEL_VIDEO_PHOTO_MSG_ID_SHOW_SHOTS_MODE, 0, 0},
        {GUI_MODEL_VIDEO_PHOTO_MSG_ID_HIDE_SHOTS_MODE, 0, 0},
        {GUI_MODEL_VIDEO_PHOTO_MSG_ID_PHOTO_REMAIN, 0, 0},
        {GUI_MODEL_VIDEO_PHOTO_MSG_ID_PEXP_ICON, 0, 0},
        {GUI_MODEL_VIDEO_PHOTO_MSG_ID_ISO_ICON, 0, 0},
        {GUI_MODEL_VIDEO_PHOTO_MSG_ID_DELAY_SATE, 0, 0},
        {GUI_MODEL_VIDEO_PHOTO_MSG_ID_DELAY_ICON, 0, 0},
        {GUI_MODEL_VIDEO_PHOTO_MSG_ID_HANDSHAKE_ICON, 0, 0},
        {GUI_MODEL_VIDEO_PHOTO_MSG_ID_SHOTS_ICON, 0, 0},
        {GUI_MODEL_VIDEO_PHOTO_MSG_ID_PHOTO_RESO, 0, 0},
    };
    for (int i = 0; i < 18; i++) {
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

    for (int i = 0; i < 18; i++) {
        if (status[i].is_unsubscribe == 1) {
            gui_msg_subscribe_change(status[i].msg_id, GUI_MSG_UNSUBSCRIBE);
        }
    }
}

gui_msg_status_t gui_model_video_photo_msg_send(int32_t msg_id, void *value, int32_t len)
{
    if (msg_id == GUI_MODEL_VIDEO_PHOTO_MSG_ID) {
    } else {
        gui_msg_data_type_t data_type = VALUE_INT;
        switch (msg_id) {
        case GUI_MODEL_VIDEO_PHOTO_MSG_ID_SHOW_HANDSHAKE:
        case GUI_MODEL_VIDEO_PHOTO_MSG_ID_HIDE_HANDSHAKE:
        case GUI_MODEL_VIDEO_PHOTO_MSG_ID_SHOW_SHOTS:
        case GUI_MODEL_VIDEO_PHOTO_MSG_ID_HIDE_SHOTS:
        case GUI_MODEL_VIDEO_PHOTO_MSG_ID_SHOW_SHOTS_MODE:
        case GUI_MODEL_VIDEO_PHOTO_MSG_ID_HIDE_SHOTS_MODE: {
            data_type = VALUE_INT;
            guider_msg_data.value_array.ptr = value;
            guider_msg_data.value_array.len = len;
        }
        break;
        case GUI_MODEL_VIDEO_PHOTO_MSG_ID_DELAY_SATE:
        case GUI_MODEL_VIDEO_PHOTO_MSG_ID_SHOTS_ICON: {
            data_type = VALUE_BOOL;
            guider_msg_data.value_array.ptr = value;
            guider_msg_data.value_array.len = len;
        }
        break;
        case GUI_MODEL_VIDEO_PHOTO_MSG_ID_AWB_ICON:
        case GUI_MODEL_VIDEO_PHOTO_MSG_ID_QUALITY_ICON:
        case GUI_MODEL_VIDEO_PHOTO_MSG_ID_SHOT_MODE_ICON:
        case GUI_MODEL_VIDEO_PHOTO_MSG_ID_PEXP_ICON:
        case GUI_MODEL_VIDEO_PHOTO_MSG_ID_ISO_ICON:
        case GUI_MODEL_VIDEO_PHOTO_MSG_ID_DELAY_ICON:
        case GUI_MODEL_VIDEO_PHOTO_MSG_ID_HANDSHAKE_ICON: {
            data_type = VALUE_INT;
            guider_msg_data.value_array.ptr = value;
            guider_msg_data.value_array.len = len;
        }
        break;
        case GUI_MODEL_VIDEO_PHOTO_MSG_ID_RESOLUTION_ICON:
        case GUI_MODEL_VIDEO_PHOTO_MSG_ID_PHOTO_REMAIN:
        case GUI_MODEL_VIDEO_PHOTO_MSG_ID_PHOTO_RESO: {
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
