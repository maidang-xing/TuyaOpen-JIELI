#include "app_config.h"
#ifdef CONFIG_UI_STYLE_JL_ENABLE
/*Generate Code, Do NOT Edit!*/
#include "./gui_model_global_subpage_msg.h"
#if LV_USE_OBSERVER

static lv_ll_t subs_ll;

void gui_model_global_subpage_msg_video_rec_img_16_set_img_path_cb(lv_observer_t *observer, lv_subject_t *subject)
{
    lv_obj_t *obj = lv_observer_get_target_obj(observer);
    if (obj == NULL || lv_obj_is_valid(obj) == false) {
        return;
    }

    gui_msg_data_t *data = (gui_msg_data_t *)observer->user_data;
    lv_img_set_src(obj, gui_get_res_path(data->value_int));
}
void gui_model_global_subpage_msg_video_rec_lbl_funkey1_set_text_cb(lv_observer_t *observer, lv_subject_t *subject)
{
    lv_obj_t *obj = lv_observer_get_target_obj(observer);
    if (obj == NULL || lv_obj_is_valid(obj) == false) {
        return;
    }

    gui_msg_data_t *data = (gui_msg_data_t *)observer->user_data;
    lv_ui_video_rec *ui_scr = ui_get_scr_ptr(&guider_ui, GUI_SCREEN_VIDEO_REC);
    lv_label_set_text(ui_scr->video_rec_lbl_funkey1_label, data->value_string);
}
void gui_model_global_subpage_msg_video_rec_lbl_funkey2_set_text_cb(lv_observer_t *observer, lv_subject_t *subject)
{
    lv_obj_t *obj = lv_observer_get_target_obj(observer);
    if (obj == NULL || lv_obj_is_valid(obj) == false) {
        return;
    }

    gui_msg_data_t *data = (gui_msg_data_t *)observer->user_data;
    lv_ui_video_rec *ui_scr = ui_get_scr_ptr(&guider_ui, GUI_SCREEN_VIDEO_REC);
    lv_label_set_text(ui_scr->video_rec_lbl_funkey2_label, data->value_string);
}
void gui_model_global_subpage_msg_video_rec_lbl_funkey3_set_text_cb(lv_observer_t *observer, lv_subject_t *subject)
{
    lv_obj_t *obj = lv_observer_get_target_obj(observer);
    if (obj == NULL || lv_obj_is_valid(obj) == false) {
        return;
    }

    gui_msg_data_t *data = (gui_msg_data_t *)observer->user_data;
    lv_ui_video_rec *ui_scr = ui_get_scr_ptr(&guider_ui, GUI_SCREEN_VIDEO_REC);
    lv_label_set_text(ui_scr->video_rec_lbl_funkey3_label, data->value_string);
}
void gui_model_global_subpage_msg_video_rec_lbl_funkey4_set_text_cb(lv_observer_t *observer, lv_subject_t *subject)
{
    lv_obj_t *obj = lv_observer_get_target_obj(observer);
    if (obj == NULL || lv_obj_is_valid(obj) == false) {
        return;
    }

    gui_msg_data_t *data = (gui_msg_data_t *)observer->user_data;
    lv_ui_video_rec *ui_scr = ui_get_scr_ptr(&guider_ui, GUI_SCREEN_VIDEO_REC);
    lv_label_set_text(ui_scr->video_rec_lbl_funkey4_label, data->value_string);
}
void gui_model_global_subpage_msg_sys_setting_img_icon_set_img_path_cb(lv_observer_t *observer, lv_subject_t *subject)
{
    lv_obj_t *obj = lv_observer_get_target_obj(observer);
    if (obj == NULL || lv_obj_is_valid(obj) == false) {
        return;
    }

    gui_msg_data_t *data = (gui_msg_data_t *)observer->user_data;
    lv_img_set_src(obj, gui_get_res_path(data->value_int));
}
void gui_model_global_subpage_msg_sys_setting_lbl_funkey1_set_text_cb(lv_observer_t *observer, lv_subject_t *subject)
{
    lv_obj_t *obj = lv_observer_get_target_obj(observer);
    if (obj == NULL || lv_obj_is_valid(obj) == false) {
        return;
    }

    gui_msg_data_t *data = (gui_msg_data_t *)observer->user_data;
    lv_ui_sys_setting *ui_scr = ui_get_scr_ptr(&guider_ui, GUI_SCREEN_SYS_SETTING);
    lv_label_set_text(ui_scr->sys_setting_lbl_funkey1_label, data->value_string);
}
void gui_model_global_subpage_msg_sys_setting_lbl_funkey3_set_text_cb(lv_observer_t *observer, lv_subject_t *subject)
{
    lv_obj_t *obj = lv_observer_get_target_obj(observer);
    if (obj == NULL || lv_obj_is_valid(obj) == false) {
        return;
    }

    gui_msg_data_t *data = (gui_msg_data_t *)observer->user_data;
    lv_ui_sys_setting *ui_scr = ui_get_scr_ptr(&guider_ui, GUI_SCREEN_SYS_SETTING);
    lv_label_set_text(ui_scr->sys_setting_lbl_funkey3_label, data->value_string);
}
void gui_model_global_subpage_msg_video_photo_img_16_set_img_path_cb(lv_observer_t *observer, lv_subject_t *subject)
{
    lv_obj_t *obj = lv_observer_get_target_obj(observer);
    if (obj == NULL || lv_obj_is_valid(obj) == false) {
        return;
    }

    gui_msg_data_t *data = (gui_msg_data_t *)observer->user_data;
    lv_img_set_src(obj, gui_get_res_path(data->value_int));
}
void gui_model_global_subpage_msg_video_photo_lbl_funkey1_set_text_cb(lv_observer_t *observer, lv_subject_t *subject)
{
    lv_obj_t *obj = lv_observer_get_target_obj(observer);
    if (obj == NULL || lv_obj_is_valid(obj) == false) {
        return;
    }

    gui_msg_data_t *data = (gui_msg_data_t *)observer->user_data;
    lv_ui_video_photo *ui_scr = ui_get_scr_ptr(&guider_ui, GUI_SCREEN_VIDEO_PHOTO);
    lv_label_set_text(ui_scr->video_photo_lbl_funkey1_label, data->value_string);
}
void gui_model_global_subpage_msg_video_photo_lbl_funkey2_set_text_cb(lv_observer_t *observer, lv_subject_t *subject)
{
    lv_obj_t *obj = lv_observer_get_target_obj(observer);
    if (obj == NULL || lv_obj_is_valid(obj) == false) {
        return;
    }

    gui_msg_data_t *data = (gui_msg_data_t *)observer->user_data;
    lv_ui_video_photo *ui_scr = ui_get_scr_ptr(&guider_ui, GUI_SCREEN_VIDEO_PHOTO);
    lv_label_set_text(ui_scr->video_photo_lbl_funkey2_label, data->value_string);
}
void gui_model_global_subpage_msg_video_photo_lbl_funkey3_set_text_cb(lv_observer_t *observer, lv_subject_t *subject)
{
    lv_obj_t *obj = lv_observer_get_target_obj(observer);
    if (obj == NULL || lv_obj_is_valid(obj) == false) {
        return;
    }

    gui_msg_data_t *data = (gui_msg_data_t *)observer->user_data;
    lv_ui_video_photo *ui_scr = ui_get_scr_ptr(&guider_ui, GUI_SCREEN_VIDEO_PHOTO);
    lv_label_set_text(ui_scr->video_photo_lbl_funkey3_label, data->value_string);
}
void gui_model_global_subpage_msg_video_photo_lbl_funkey4_set_text_cb(lv_observer_t *observer, lv_subject_t *subject)
{
    lv_obj_t *obj = lv_observer_get_target_obj(observer);
    if (obj == NULL || lv_obj_is_valid(obj) == false) {
        return;
    }

    gui_msg_data_t *data = (gui_msg_data_t *)observer->user_data;
    lv_ui_video_photo *ui_scr = ui_get_scr_ptr(&guider_ui, GUI_SCREEN_VIDEO_PHOTO);
    lv_label_set_text(ui_scr->video_photo_lbl_funkey4_label, data->value_string);
}

GUI_WEAK int gui_model_global_subpage_msg_subpage_icon_cb(gui_msg_action_t access, gui_msg_data_t *data, gui_msg_data_type_t type)
{
    static int32_t subpage_icon_var = RES_RESOLUTION_RATIO;
    if (access == GUI_MSG_ACCESS_SET) {
        subpage_icon_var = data->value_int;
    }
    data->value_int = subpage_icon_var;
    return 0;
}
GUI_WEAK int gui_model_global_subpage_msg_funckey1_cb(gui_msg_action_t access, gui_msg_data_t *data, gui_msg_data_type_t type)
{
    char funckey1_init_var[] = "funckey1";
    static bool funckey1_is_init = false;
    static char *funckey1_var = NULL;
    if (funckey1_is_init == false) {
        funckey1_var = lv_mem_alloc(strlen(funckey1_init_var) + 1);
        strcpy(funckey1_var, funckey1_init_var);
        funckey1_is_init = true;
    }
    if (access == GUI_MSG_ACCESS_SET) {
        lv_mem_free(funckey1_var);
        funckey1_var = lv_mem_alloc(strlen(data->value_string) + 1);
        strcpy(funckey1_var, data->value_string);
    }
    data->value_string = funckey1_var;
    return 0;
}
GUI_WEAK int gui_model_global_subpage_msg_funckey2_cb(gui_msg_action_t access, gui_msg_data_t *data, gui_msg_data_type_t type)
{
    char funckey2_init_var[] = "funckey2";
    static bool funckey2_is_init = false;
    static char *funckey2_var = NULL;
    if (funckey2_is_init == false) {
        funckey2_var = lv_mem_alloc(strlen(funckey2_init_var) + 1);
        strcpy(funckey2_var, funckey2_init_var);
        funckey2_is_init = true;
    }
    if (access == GUI_MSG_ACCESS_SET) {
        lv_mem_free(funckey2_var);
        funckey2_var = lv_mem_alloc(strlen(data->value_string) + 1);
        strcpy(funckey2_var, data->value_string);
    }
    data->value_string = funckey2_var;
    return 0;
}
GUI_WEAK int gui_model_global_subpage_msg_funckey3_cb(gui_msg_action_t access, gui_msg_data_t *data, gui_msg_data_type_t type)
{
    char funckey3_init_var[] = "funckey3";
    static bool funckey3_is_init = false;
    static char *funckey3_var = NULL;
    if (funckey3_is_init == false) {
        funckey3_var = lv_mem_alloc(strlen(funckey3_init_var) + 1);
        strcpy(funckey3_var, funckey3_init_var);
        funckey3_is_init = true;
    }
    if (access == GUI_MSG_ACCESS_SET) {
        lv_mem_free(funckey3_var);
        funckey3_var = lv_mem_alloc(strlen(data->value_string) + 1);
        strcpy(funckey3_var, data->value_string);
    }
    data->value_string = funckey3_var;
    return 0;
}
GUI_WEAK int gui_model_global_subpage_msg_funckey4_cb(gui_msg_action_t access, gui_msg_data_t *data, gui_msg_data_type_t type)
{
    char funckey4_init_var[] = "funckey4";
    static bool funckey4_is_init = false;
    static char *funckey4_var = NULL;
    if (funckey4_is_init == false) {
        funckey4_var = lv_mem_alloc(strlen(funckey4_init_var) + 1);
        strcpy(funckey4_var, funckey4_init_var);
        funckey4_is_init = true;
    }
    if (access == GUI_MSG_ACCESS_SET) {
        lv_mem_free(funckey4_var);
        funckey4_var = lv_mem_alloc(strlen(data->value_string) + 1);
        strcpy(funckey4_var, data->value_string);
    }
    data->value_string = funckey4_var;
    return 0;
}
GUI_WEAK int gui_model_global_subpage_msg_title_cb(gui_msg_action_t access, gui_msg_data_t *data, gui_msg_data_type_t type)
{
    char title_init_var[] = "title";
    static bool title_is_init = false;
    static char *title_var = NULL;
    if (title_is_init == false) {
        title_var = lv_mem_alloc(strlen(title_init_var) + 1);
        strcpy(title_var, title_init_var);
        title_is_init = true;
    }
    if (access == GUI_MSG_ACCESS_SET) {
        lv_mem_free(title_var);
        title_var = lv_mem_alloc(strlen(data->value_string) + 1);
        strcpy(title_var, data->value_string);
    }
    data->value_string = title_var;
    return 0;
}
GUI_WEAK int gui_model_global_subpage_msg_hide_funckey1_cb(gui_msg_action_t access, gui_msg_data_t *data, gui_msg_data_type_t type)
{
    static lv_obj_flag_t hide_funckey1_var = LV_OBJ_FLAG_HIDDEN;
    if (access == GUI_MSG_ACCESS_SET) {
        hide_funckey1_var = data->value_int;
    }
    data->value_int = hide_funckey1_var;
    return 0;
}
GUI_WEAK int gui_model_global_subpage_msg_hide_funckey2_cb(gui_msg_action_t access, gui_msg_data_t *data, gui_msg_data_type_t type)
{
    static lv_obj_flag_t hide_funckey2_var = LV_OBJ_FLAG_HIDDEN;
    if (access == GUI_MSG_ACCESS_SET) {
        hide_funckey2_var = data->value_int;
    }
    data->value_int = hide_funckey2_var;
    return 0;
}
GUI_WEAK int gui_model_global_subpage_msg_hide_funckey3_cb(gui_msg_action_t access, gui_msg_data_t *data, gui_msg_data_type_t type)
{
    static lv_obj_flag_t hide_funckey3_var = LV_OBJ_FLAG_HIDDEN;
    if (access == GUI_MSG_ACCESS_SET) {
        hide_funckey3_var = data->value_int;
    }
    data->value_int = hide_funckey3_var;
    return 0;
}
GUI_WEAK int gui_model_global_subpage_msg_hide_funckey4_cb(gui_msg_action_t access, gui_msg_data_t *data, gui_msg_data_type_t type)
{
    static lv_obj_flag_t hide_funckey4_var = LV_OBJ_FLAG_HIDDEN;
    if (access == GUI_MSG_ACCESS_SET) {
        hide_funckey4_var = data->value_int;
    }
    data->value_int = hide_funckey4_var;
    return 0;
}
GUI_WEAK int gui_model_global_subpage_msg_show_funckey1_cb(gui_msg_action_t access, gui_msg_data_t *data, gui_msg_data_type_t type)
{
    static lv_obj_flag_t show_funckey1_var = 0;
    if (access == GUI_MSG_ACCESS_SET) {
        show_funckey1_var = data->value_int;
    }
    data->value_int = show_funckey1_var;
    return 0;
}
GUI_WEAK int gui_model_global_subpage_msg_show_funckey2_cb(gui_msg_action_t access, gui_msg_data_t *data, gui_msg_data_type_t type)
{
    static lv_obj_flag_t show_funckey2_var = 0;
    if (access == GUI_MSG_ACCESS_SET) {
        show_funckey2_var = data->value_int;
    }
    data->value_int = show_funckey2_var;
    return 0;
}
GUI_WEAK int gui_model_global_subpage_msg_show_funckey3_cb(gui_msg_action_t access, gui_msg_data_t *data, gui_msg_data_type_t type)
{
    static lv_obj_flag_t show_funckey3_var = 0;
    if (access == GUI_MSG_ACCESS_SET) {
        show_funckey3_var = data->value_int;
    }
    data->value_int = show_funckey3_var;
    return 0;
}
GUI_WEAK int gui_model_global_subpage_msg_show_funckey4_cb(gui_msg_action_t access, gui_msg_data_t *data, gui_msg_data_type_t type)
{
    static lv_obj_flag_t show_funckey4_var = 0;
    if (access == GUI_MSG_ACCESS_SET) {
        show_funckey4_var = data->value_int;
    }
    data->value_int = show_funckey4_var;
    return 0;
}
GUI_WEAK int gui_model_global_subpage_msg_roller_opt_cb(gui_msg_action_t access, gui_msg_data_t *data, gui_msg_data_type_t type)
{
    char roller_opt_init_var[] = "1\n2\n3\n";
    static bool roller_opt_is_init = false;
    static char *roller_opt_var = NULL;
    if (roller_opt_is_init == false) {
        roller_opt_var = lv_mem_alloc(strlen(roller_opt_init_var) + 1);
        strcpy(roller_opt_var, roller_opt_init_var);
        roller_opt_is_init = true;
    }
    if (access == GUI_MSG_ACCESS_SET) {
        lv_mem_free(roller_opt_var);
        roller_opt_var = lv_mem_alloc(strlen(data->value_string) + 1);
        strcpy(roller_opt_var, data->value_string);
    }
    data->value_string = roller_opt_var;
    return 0;
}
GUI_WEAK int gui_model_global_subpage_msg_show_roller_cb(gui_msg_action_t access, gui_msg_data_t *data, gui_msg_data_type_t type)
{
    static lv_obj_flag_t show_roller_var = LV_OBJ_FLAG_HIDDEN;
    if (access == GUI_MSG_ACCESS_SET) {
        show_roller_var = data->value_int;
    }
    data->value_int = show_roller_var;
    return 0;
}
GUI_WEAK int gui_model_global_subpage_msg_hide_roller_cb(gui_msg_action_t access, gui_msg_data_t *data, gui_msg_data_type_t type)
{
    static lv_obj_flag_t hide_roller_var = LV_OBJ_FLAG_HIDDEN;
    if (access == GUI_MSG_ACCESS_SET) {
        hide_roller_var = data->value_int;
    }
    data->value_int = hide_roller_var;
    return 0;
}
GUI_WEAK int gui_model_global_subpage_msg_state_funkey1_cb(gui_msg_action_t access, gui_msg_data_t *data, gui_msg_data_type_t type)
{
    static lv_state_t state_funkey1_var = LV_STATE_DEFAULT;
    if (access == GUI_MSG_ACCESS_SET) {
        state_funkey1_var = data->value_int;
    }
    data->value_int = state_funkey1_var;
    return 0;
}
GUI_WEAK int gui_model_global_subpage_msg_state_funkey2_cb(gui_msg_action_t access, gui_msg_data_t *data, gui_msg_data_type_t type)
{
    static lv_state_t state_funkey2_var = LV_STATE_DEFAULT;
    if (access == GUI_MSG_ACCESS_SET) {
        state_funkey2_var = data->value_int;
    }
    data->value_int = state_funkey2_var;
    return 0;
}
GUI_WEAK int gui_model_global_subpage_msg_state_funkey3_cb(gui_msg_action_t access, gui_msg_data_t *data, gui_msg_data_type_t type)
{
    static lv_state_t state_funkey3_var = LV_STATE_DEFAULT;
    if (access == GUI_MSG_ACCESS_SET) {
        state_funkey3_var = data->value_int;
    }
    data->value_int = state_funkey3_var;
    return 0;
}

void gui_model_global_subpage_msg_init(lv_ui *ui)
{
    gui_msg_sub_t *sub;
    sub = gui_msg_create_sub(GUI_MODEL_GLOBAL_SUBPAGE_MSG_ID_SUBPAGE_ICON);
    if (sub != NULL) {
        lv_subject_init_pointer(sub->subject, &guider_msg_data);
    }
    sub = gui_msg_create_sub(GUI_MODEL_GLOBAL_SUBPAGE_MSG_ID_FUNCKEY1);
    if (sub != NULL) {
        lv_subject_init_pointer(sub->subject, &guider_msg_data);
    }
    sub = gui_msg_create_sub(GUI_MODEL_GLOBAL_SUBPAGE_MSG_ID_FUNCKEY2);
    if (sub != NULL) {
        lv_subject_init_pointer(sub->subject, &guider_msg_data);
    }
    sub = gui_msg_create_sub(GUI_MODEL_GLOBAL_SUBPAGE_MSG_ID_FUNCKEY3);
    if (sub != NULL) {
        lv_subject_init_pointer(sub->subject, &guider_msg_data);
    }
    sub = gui_msg_create_sub(GUI_MODEL_GLOBAL_SUBPAGE_MSG_ID_FUNCKEY4);
    if (sub != NULL) {
        lv_subject_init_pointer(sub->subject, &guider_msg_data);
    }
    sub = gui_msg_create_sub(GUI_MODEL_GLOBAL_SUBPAGE_MSG_ID_TITLE);
    if (sub != NULL) {
        lv_subject_init_pointer(sub->subject, &guider_msg_data);
    }
    sub = gui_msg_create_sub(GUI_MODEL_GLOBAL_SUBPAGE_MSG_ID_HIDE_FUNCKEY1);
    if (sub != NULL) {
        lv_subject_init_pointer(sub->subject, &guider_msg_data);
    }
    sub = gui_msg_create_sub(GUI_MODEL_GLOBAL_SUBPAGE_MSG_ID_HIDE_FUNCKEY2);
    if (sub != NULL) {
        lv_subject_init_pointer(sub->subject, &guider_msg_data);
    }
    sub = gui_msg_create_sub(GUI_MODEL_GLOBAL_SUBPAGE_MSG_ID_HIDE_FUNCKEY3);
    if (sub != NULL) {
        lv_subject_init_pointer(sub->subject, &guider_msg_data);
    }
    sub = gui_msg_create_sub(GUI_MODEL_GLOBAL_SUBPAGE_MSG_ID_HIDE_FUNCKEY4);
    if (sub != NULL) {
        lv_subject_init_pointer(sub->subject, &guider_msg_data);
    }
    sub = gui_msg_create_sub(GUI_MODEL_GLOBAL_SUBPAGE_MSG_ID_SHOW_FUNCKEY1);
    if (sub != NULL) {
        lv_subject_init_pointer(sub->subject, &guider_msg_data);
    }
    sub = gui_msg_create_sub(GUI_MODEL_GLOBAL_SUBPAGE_MSG_ID_SHOW_FUNCKEY2);
    if (sub != NULL) {
        lv_subject_init_pointer(sub->subject, &guider_msg_data);
    }
    sub = gui_msg_create_sub(GUI_MODEL_GLOBAL_SUBPAGE_MSG_ID_SHOW_FUNCKEY3);
    if (sub != NULL) {
        lv_subject_init_pointer(sub->subject, &guider_msg_data);
    }
    sub = gui_msg_create_sub(GUI_MODEL_GLOBAL_SUBPAGE_MSG_ID_SHOW_FUNCKEY4);
    if (sub != NULL) {
        lv_subject_init_pointer(sub->subject, &guider_msg_data);
    }
    sub = gui_msg_create_sub(GUI_MODEL_GLOBAL_SUBPAGE_MSG_ID_ROLLER_OPT);
    if (sub != NULL) {
        lv_subject_init_pointer(sub->subject, &guider_msg_data);
    }
    sub = gui_msg_create_sub(GUI_MODEL_GLOBAL_SUBPAGE_MSG_ID_SHOW_ROLLER);
    if (sub != NULL) {
        lv_subject_init_pointer(sub->subject, &guider_msg_data);
    }
    sub = gui_msg_create_sub(GUI_MODEL_GLOBAL_SUBPAGE_MSG_ID_HIDE_ROLLER);
    if (sub != NULL) {
        lv_subject_init_pointer(sub->subject, &guider_msg_data);
    }
    sub = gui_msg_create_sub(GUI_MODEL_GLOBAL_SUBPAGE_MSG_ID_STATE_FUNKEY1);
    if (sub != NULL) {
        lv_subject_init_pointer(sub->subject, &guider_msg_data);
    }
    sub = gui_msg_create_sub(GUI_MODEL_GLOBAL_SUBPAGE_MSG_ID_STATE_FUNKEY2);
    if (sub != NULL) {
        lv_subject_init_pointer(sub->subject, &guider_msg_data);
    }
    sub = gui_msg_create_sub(GUI_MODEL_GLOBAL_SUBPAGE_MSG_ID_STATE_FUNKEY3);
    if (sub != NULL) {
        lv_subject_init_pointer(sub->subject, &guider_msg_data);
    }
}

void gui_model_global_subpage_msg_init_ui()
{
}

void gui_model_global_subpage_msg_init_events()
{
    void *res = NULL;
    _gui_msg_status_t status[20] = {
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
    };

    for (int i = 0; i < 20; i++) {
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

    lv_subject_t *subject_subpage_icon = gui_msg_get_subject(GUI_MODEL_GLOBAL_SUBPAGE_MSG_ID_SUBPAGE_ICON);
    lv_subject_t *subject_funckey1 = gui_msg_get_subject(GUI_MODEL_GLOBAL_SUBPAGE_MSG_ID_FUNCKEY1);
    lv_subject_t *subject_funckey2 = gui_msg_get_subject(GUI_MODEL_GLOBAL_SUBPAGE_MSG_ID_FUNCKEY2);
    lv_subject_t *subject_funckey3 = gui_msg_get_subject(GUI_MODEL_GLOBAL_SUBPAGE_MSG_ID_FUNCKEY3);
    lv_subject_t *subject_funckey4 = gui_msg_get_subject(GUI_MODEL_GLOBAL_SUBPAGE_MSG_ID_FUNCKEY4);
    lv_subject_t *subject_title = gui_msg_get_subject(GUI_MODEL_GLOBAL_SUBPAGE_MSG_ID_TITLE);
    lv_subject_t *subject_hide_funckey1 = gui_msg_get_subject(GUI_MODEL_GLOBAL_SUBPAGE_MSG_ID_HIDE_FUNCKEY1);
    lv_subject_t *subject_hide_funckey2 = gui_msg_get_subject(GUI_MODEL_GLOBAL_SUBPAGE_MSG_ID_HIDE_FUNCKEY2);
    lv_subject_t *subject_hide_funckey3 = gui_msg_get_subject(GUI_MODEL_GLOBAL_SUBPAGE_MSG_ID_HIDE_FUNCKEY3);
    lv_subject_t *subject_hide_funckey4 = gui_msg_get_subject(GUI_MODEL_GLOBAL_SUBPAGE_MSG_ID_HIDE_FUNCKEY4);
    lv_subject_t *subject_show_funckey1 = gui_msg_get_subject(GUI_MODEL_GLOBAL_SUBPAGE_MSG_ID_SHOW_FUNCKEY1);
    lv_subject_t *subject_show_funckey2 = gui_msg_get_subject(GUI_MODEL_GLOBAL_SUBPAGE_MSG_ID_SHOW_FUNCKEY2);
    lv_subject_t *subject_show_funckey3 = gui_msg_get_subject(GUI_MODEL_GLOBAL_SUBPAGE_MSG_ID_SHOW_FUNCKEY3);
    lv_subject_t *subject_show_funckey4 = gui_msg_get_subject(GUI_MODEL_GLOBAL_SUBPAGE_MSG_ID_SHOW_FUNCKEY4);
    lv_subject_t *subject_roller_opt = gui_msg_get_subject(GUI_MODEL_GLOBAL_SUBPAGE_MSG_ID_ROLLER_OPT);
    lv_subject_t *subject_show_roller = gui_msg_get_subject(GUI_MODEL_GLOBAL_SUBPAGE_MSG_ID_SHOW_ROLLER);
    lv_subject_t *subject_hide_roller = gui_msg_get_subject(GUI_MODEL_GLOBAL_SUBPAGE_MSG_ID_HIDE_ROLLER);
    lv_subject_t *subject_state_funkey1 = gui_msg_get_subject(GUI_MODEL_GLOBAL_SUBPAGE_MSG_ID_STATE_FUNKEY1);
    lv_subject_t *subject_state_funkey2 = gui_msg_get_subject(GUI_MODEL_GLOBAL_SUBPAGE_MSG_ID_STATE_FUNKEY2);
    lv_subject_t *subject_state_funkey3 = gui_msg_get_subject(GUI_MODEL_GLOBAL_SUBPAGE_MSG_ID_STATE_FUNKEY3);
    if (guider_ui.video_rec) {
        lv_ui_video_rec *ui_scr = ui_get_scr_ptr(&guider_ui, GUI_SCREEN_VIDEO_REC);
        gui_msg_setup_component(true, false, subject_subpage_icon, ui_scr->video_rec_img_16, &guider_msg_data, gui_model_global_subpage_msg_video_rec_img_16_set_img_path_cb, GUI_MODEL_GLOBAL_SUBPAGE_MSG_ID_SUBPAGE_ICON, GUI_MSG_ACCESS_GET, VALUE_INT, NULL);

        gui_msg_setup_component(true, false, subject_title, ui_scr->video_rec_lbl_menu_title, &guider_msg_data, gui_msg_set_label_text_by_string_cb, GUI_MODEL_GLOBAL_SUBPAGE_MSG_ID_TITLE, GUI_MSG_ACCESS_GET, VALUE_STRING, NULL);

        gui_msg_setup_component(true, false, subject_state_funkey1, ui_scr->video_rec_lbl_funkey1, &guider_msg_data, gui_msg_set_control_state_by_int32_cb, GUI_MODEL_GLOBAL_SUBPAGE_MSG_ID_STATE_FUNKEY1, GUI_MSG_ACCESS_GET, VALUE_INT, NULL);
        gui_msg_setup_component(true, false, subject_funckey1, ui_scr->video_rec_lbl_funkey1, &guider_msg_data, gui_model_global_subpage_msg_video_rec_lbl_funkey1_set_text_cb, GUI_MODEL_GLOBAL_SUBPAGE_MSG_ID_FUNCKEY1, GUI_MSG_ACCESS_GET, VALUE_STRING, NULL);
        gui_msg_setup_component(true, false, subject_show_funckey1, ui_scr->video_rec_lbl_funkey1, &guider_msg_data, gui_msg_set_clear_flag_by_int32_cb, GUI_MODEL_GLOBAL_SUBPAGE_MSG_ID_SHOW_FUNCKEY1, GUI_MSG_ACCESS_GET, VALUE_INT, NULL);
        gui_msg_setup_component(true, false, subject_hide_funckey1, ui_scr->video_rec_lbl_funkey1, &guider_msg_data, gui_msg_set_flag_by_int32_cb, GUI_MODEL_GLOBAL_SUBPAGE_MSG_ID_HIDE_FUNCKEY1, GUI_MSG_ACCESS_GET, VALUE_INT, NULL);

        gui_msg_setup_component(true, false, subject_state_funkey2, ui_scr->video_rec_lbl_funkey2, &guider_msg_data, gui_msg_set_control_state_by_int32_cb, GUI_MODEL_GLOBAL_SUBPAGE_MSG_ID_STATE_FUNKEY2, GUI_MSG_ACCESS_GET, VALUE_INT, NULL);
        gui_msg_setup_component(true, false, subject_funckey2, ui_scr->video_rec_lbl_funkey2, &guider_msg_data, gui_model_global_subpage_msg_video_rec_lbl_funkey2_set_text_cb, GUI_MODEL_GLOBAL_SUBPAGE_MSG_ID_FUNCKEY2, GUI_MSG_ACCESS_GET, VALUE_STRING, NULL);
        gui_msg_setup_component(true, false, subject_show_funckey2, ui_scr->video_rec_lbl_funkey2, &guider_msg_data, gui_msg_set_clear_flag_by_int32_cb, GUI_MODEL_GLOBAL_SUBPAGE_MSG_ID_SHOW_FUNCKEY2, GUI_MSG_ACCESS_GET, VALUE_INT, NULL);
        gui_msg_setup_component(true, false, subject_hide_funckey2, ui_scr->video_rec_lbl_funkey2, &guider_msg_data, gui_msg_set_flag_by_int32_cb, GUI_MODEL_GLOBAL_SUBPAGE_MSG_ID_HIDE_FUNCKEY2, GUI_MSG_ACCESS_GET, VALUE_INT, NULL);

        gui_msg_setup_component(true, false, subject_state_funkey3, ui_scr->video_rec_lbl_funkey3, &guider_msg_data, gui_msg_set_control_state_by_int32_cb, GUI_MODEL_GLOBAL_SUBPAGE_MSG_ID_STATE_FUNKEY3, GUI_MSG_ACCESS_GET, VALUE_INT, NULL);
        gui_msg_setup_component(true, false, subject_funckey3, ui_scr->video_rec_lbl_funkey3, &guider_msg_data, gui_model_global_subpage_msg_video_rec_lbl_funkey3_set_text_cb, GUI_MODEL_GLOBAL_SUBPAGE_MSG_ID_FUNCKEY3, GUI_MSG_ACCESS_GET, VALUE_STRING, NULL);
        gui_msg_setup_component(true, false, subject_show_funckey3, ui_scr->video_rec_lbl_funkey3, &guider_msg_data, gui_msg_set_clear_flag_by_int32_cb, GUI_MODEL_GLOBAL_SUBPAGE_MSG_ID_SHOW_FUNCKEY3, GUI_MSG_ACCESS_GET, VALUE_INT, NULL);
        gui_msg_setup_component(true, false, subject_hide_funckey3, ui_scr->video_rec_lbl_funkey3, &guider_msg_data, gui_msg_set_flag_by_int32_cb, GUI_MODEL_GLOBAL_SUBPAGE_MSG_ID_HIDE_FUNCKEY3, GUI_MSG_ACCESS_GET, VALUE_INT, NULL);

        gui_msg_setup_component(true, false, subject_funckey4, ui_scr->video_rec_lbl_funkey4, &guider_msg_data, gui_model_global_subpage_msg_video_rec_lbl_funkey4_set_text_cb, GUI_MODEL_GLOBAL_SUBPAGE_MSG_ID_FUNCKEY4, GUI_MSG_ACCESS_GET, VALUE_STRING, NULL);
        gui_msg_setup_component(true, false, subject_show_funckey4, ui_scr->video_rec_lbl_funkey4, &guider_msg_data, gui_msg_set_clear_flag_by_int32_cb, GUI_MODEL_GLOBAL_SUBPAGE_MSG_ID_SHOW_FUNCKEY4, GUI_MSG_ACCESS_GET, VALUE_INT, NULL);
        gui_msg_setup_component(true, false, subject_hide_funckey4, ui_scr->video_rec_lbl_funkey4, &guider_msg_data, gui_msg_set_flag_by_int32_cb, GUI_MODEL_GLOBAL_SUBPAGE_MSG_ID_HIDE_FUNCKEY4, GUI_MSG_ACCESS_GET, VALUE_INT, NULL);

        gui_msg_setup_component(true, false, subject_roller_opt, ui_scr->video_rec_roller_mutifunc, &guider_msg_data, gui_msg_set_roller_roller_name_by_string_cb, GUI_MODEL_GLOBAL_SUBPAGE_MSG_ID_ROLLER_OPT, GUI_MSG_ACCESS_GET, VALUE_STRING, NULL);
        gui_msg_setup_component(true, false, subject_show_roller, ui_scr->video_rec_roller_mutifunc, &guider_msg_data, gui_msg_set_clear_flag_by_int32_cb, GUI_MODEL_GLOBAL_SUBPAGE_MSG_ID_SHOW_ROLLER, GUI_MSG_ACCESS_GET, VALUE_INT, NULL);
        gui_msg_setup_component(true, false, subject_hide_roller, ui_scr->video_rec_roller_mutifunc, &guider_msg_data, gui_msg_set_flag_by_int32_cb, GUI_MODEL_GLOBAL_SUBPAGE_MSG_ID_HIDE_ROLLER, GUI_MSG_ACCESS_GET, VALUE_INT, NULL);


        for (int i = 0; i < 20; i++) {
            if (status[i].msg_id == GUI_MODEL_GLOBAL_SUBPAGE_MSG_ID_SUBPAGE_ICON) {
                status[i].is_subscribe = 1;
            }
            if (status[i].msg_id == GUI_MODEL_GLOBAL_SUBPAGE_MSG_ID_TITLE) {
                status[i].is_subscribe = 1;
            }
            if (status[i].msg_id == GUI_MODEL_GLOBAL_SUBPAGE_MSG_ID_STATE_FUNKEY1) {
                status[i].is_subscribe = 1;
            }
            if (status[i].msg_id == GUI_MODEL_GLOBAL_SUBPAGE_MSG_ID_FUNCKEY1) {
                status[i].is_subscribe = 1;
            }
            if (status[i].msg_id == GUI_MODEL_GLOBAL_SUBPAGE_MSG_ID_SHOW_FUNCKEY1) {
                status[i].is_subscribe = 1;
            }
            if (status[i].msg_id == GUI_MODEL_GLOBAL_SUBPAGE_MSG_ID_HIDE_FUNCKEY1) {
                status[i].is_subscribe = 1;
            }
            if (status[i].msg_id == GUI_MODEL_GLOBAL_SUBPAGE_MSG_ID_STATE_FUNKEY2) {
                status[i].is_subscribe = 1;
            }
            if (status[i].msg_id == GUI_MODEL_GLOBAL_SUBPAGE_MSG_ID_FUNCKEY2) {
                status[i].is_subscribe = 1;
            }
            if (status[i].msg_id == GUI_MODEL_GLOBAL_SUBPAGE_MSG_ID_SHOW_FUNCKEY2) {
                status[i].is_subscribe = 1;
            }
            if (status[i].msg_id == GUI_MODEL_GLOBAL_SUBPAGE_MSG_ID_HIDE_FUNCKEY2) {
                status[i].is_subscribe = 1;
            }
            if (status[i].msg_id == GUI_MODEL_GLOBAL_SUBPAGE_MSG_ID_STATE_FUNKEY3) {
                status[i].is_subscribe = 1;
            }
            if (status[i].msg_id == GUI_MODEL_GLOBAL_SUBPAGE_MSG_ID_FUNCKEY3) {
                status[i].is_subscribe = 1;
            }
            if (status[i].msg_id == GUI_MODEL_GLOBAL_SUBPAGE_MSG_ID_SHOW_FUNCKEY3) {
                status[i].is_subscribe = 1;
            }
            if (status[i].msg_id == GUI_MODEL_GLOBAL_SUBPAGE_MSG_ID_HIDE_FUNCKEY3) {
                status[i].is_subscribe = 1;
            }
            if (status[i].msg_id == GUI_MODEL_GLOBAL_SUBPAGE_MSG_ID_FUNCKEY4) {
                status[i].is_subscribe = 1;
            }
            if (status[i].msg_id == GUI_MODEL_GLOBAL_SUBPAGE_MSG_ID_SHOW_FUNCKEY4) {
                status[i].is_subscribe = 1;
            }
            if (status[i].msg_id == GUI_MODEL_GLOBAL_SUBPAGE_MSG_ID_HIDE_FUNCKEY4) {
                status[i].is_subscribe = 1;
            }
            if (status[i].msg_id == GUI_MODEL_GLOBAL_SUBPAGE_MSG_ID_ROLLER_OPT) {
                status[i].is_subscribe = 1;
            }
            if (status[i].msg_id == GUI_MODEL_GLOBAL_SUBPAGE_MSG_ID_SHOW_ROLLER) {
                status[i].is_subscribe = 1;
            }
            if (status[i].msg_id == GUI_MODEL_GLOBAL_SUBPAGE_MSG_ID_HIDE_ROLLER) {
                status[i].is_subscribe = 1;
            }
        }
    }
    if (guider_ui.sys_setting) {
        lv_ui_sys_setting *ui_scr = ui_get_scr_ptr(&guider_ui, GUI_SCREEN_SYS_SETTING);
        gui_msg_setup_component(true, false, subject_subpage_icon, ui_scr->sys_setting_img_icon, &guider_msg_data, gui_model_global_subpage_msg_sys_setting_img_icon_set_img_path_cb, GUI_MODEL_GLOBAL_SUBPAGE_MSG_ID_SUBPAGE_ICON, GUI_MSG_ACCESS_GET, VALUE_INT, NULL);

        gui_msg_setup_component(true, false, subject_title, ui_scr->sys_setting_lbl_menu_title, &guider_msg_data, gui_msg_set_label_text_by_string_cb, GUI_MODEL_GLOBAL_SUBPAGE_MSG_ID_TITLE, GUI_MSG_ACCESS_GET, VALUE_STRING, NULL);

        gui_msg_setup_component(true, false, subject_funckey4, ui_scr->sys_setting_lbl_funkey4, &guider_msg_data, gui_msg_set_label_text_by_string_cb, GUI_MODEL_GLOBAL_SUBPAGE_MSG_ID_FUNCKEY4, GUI_MSG_ACCESS_GET, VALUE_STRING, NULL);
        gui_msg_setup_component(true, false, subject_show_funckey4, ui_scr->sys_setting_lbl_funkey4, &guider_msg_data, gui_msg_set_clear_flag_by_int32_cb, GUI_MODEL_GLOBAL_SUBPAGE_MSG_ID_SHOW_FUNCKEY4, GUI_MSG_ACCESS_GET, VALUE_INT, NULL);
        gui_msg_setup_component(true, false, subject_hide_funckey4, ui_scr->sys_setting_lbl_funkey4, &guider_msg_data, gui_msg_set_flag_by_int32_cb, GUI_MODEL_GLOBAL_SUBPAGE_MSG_ID_HIDE_FUNCKEY4, GUI_MSG_ACCESS_GET, VALUE_INT, NULL);

        gui_msg_setup_component(true, false, subject_funckey1, ui_scr->sys_setting_lbl_funkey1, &guider_msg_data, gui_model_global_subpage_msg_sys_setting_lbl_funkey1_set_text_cb, GUI_MODEL_GLOBAL_SUBPAGE_MSG_ID_FUNCKEY1, GUI_MSG_ACCESS_GET, VALUE_STRING, NULL);
        gui_msg_setup_component(true, false, subject_show_funckey1, ui_scr->sys_setting_lbl_funkey1, &guider_msg_data, gui_msg_set_clear_flag_by_int32_cb, GUI_MODEL_GLOBAL_SUBPAGE_MSG_ID_SHOW_FUNCKEY1, GUI_MSG_ACCESS_GET, VALUE_INT, NULL);
        gui_msg_setup_component(true, false, subject_hide_funckey1, ui_scr->sys_setting_lbl_funkey1, &guider_msg_data, gui_msg_set_flag_by_int32_cb, GUI_MODEL_GLOBAL_SUBPAGE_MSG_ID_HIDE_FUNCKEY1, GUI_MSG_ACCESS_GET, VALUE_INT, NULL);

        gui_msg_setup_component(true, false, subject_funckey3, ui_scr->sys_setting_lbl_funkey3, &guider_msg_data, gui_model_global_subpage_msg_sys_setting_lbl_funkey3_set_text_cb, GUI_MODEL_GLOBAL_SUBPAGE_MSG_ID_FUNCKEY3, GUI_MSG_ACCESS_GET, VALUE_STRING, NULL);
        gui_msg_setup_component(true, false, subject_show_funckey3, ui_scr->sys_setting_lbl_funkey3, &guider_msg_data, gui_msg_set_clear_flag_by_int32_cb, GUI_MODEL_GLOBAL_SUBPAGE_MSG_ID_SHOW_FUNCKEY3, GUI_MSG_ACCESS_GET, VALUE_INT, NULL);
        gui_msg_setup_component(true, false, subject_hide_funckey3, ui_scr->sys_setting_lbl_funkey3, &guider_msg_data, gui_msg_set_flag_by_int32_cb, GUI_MODEL_GLOBAL_SUBPAGE_MSG_ID_HIDE_FUNCKEY3, GUI_MSG_ACCESS_GET, VALUE_INT, NULL);


        for (int i = 0; i < 20; i++) {
            if (status[i].msg_id == GUI_MODEL_GLOBAL_SUBPAGE_MSG_ID_SUBPAGE_ICON) {
                status[i].is_subscribe = 1;
            }
            if (status[i].msg_id == GUI_MODEL_GLOBAL_SUBPAGE_MSG_ID_TITLE) {
                status[i].is_subscribe = 1;
            }
            if (status[i].msg_id == GUI_MODEL_GLOBAL_SUBPAGE_MSG_ID_FUNCKEY4) {
                status[i].is_subscribe = 1;
            }
            if (status[i].msg_id == GUI_MODEL_GLOBAL_SUBPAGE_MSG_ID_SHOW_FUNCKEY4) {
                status[i].is_subscribe = 1;
            }
            if (status[i].msg_id == GUI_MODEL_GLOBAL_SUBPAGE_MSG_ID_HIDE_FUNCKEY4) {
                status[i].is_subscribe = 1;
            }
            if (status[i].msg_id == GUI_MODEL_GLOBAL_SUBPAGE_MSG_ID_FUNCKEY1) {
                status[i].is_subscribe = 1;
            }
            if (status[i].msg_id == GUI_MODEL_GLOBAL_SUBPAGE_MSG_ID_SHOW_FUNCKEY1) {
                status[i].is_subscribe = 1;
            }
            if (status[i].msg_id == GUI_MODEL_GLOBAL_SUBPAGE_MSG_ID_HIDE_FUNCKEY1) {
                status[i].is_subscribe = 1;
            }
            if (status[i].msg_id == GUI_MODEL_GLOBAL_SUBPAGE_MSG_ID_FUNCKEY3) {
                status[i].is_subscribe = 1;
            }
            if (status[i].msg_id == GUI_MODEL_GLOBAL_SUBPAGE_MSG_ID_SHOW_FUNCKEY3) {
                status[i].is_subscribe = 1;
            }
            if (status[i].msg_id == GUI_MODEL_GLOBAL_SUBPAGE_MSG_ID_HIDE_FUNCKEY3) {
                status[i].is_subscribe = 1;
            }
        }
    }
    if (guider_ui.video_photo) {
        lv_ui_video_photo *ui_scr = ui_get_scr_ptr(&guider_ui, GUI_SCREEN_VIDEO_PHOTO);
        gui_msg_setup_component(true, false, subject_subpage_icon, ui_scr->video_photo_img_16, &guider_msg_data, gui_model_global_subpage_msg_video_photo_img_16_set_img_path_cb, GUI_MODEL_GLOBAL_SUBPAGE_MSG_ID_SUBPAGE_ICON, GUI_MSG_ACCESS_GET, VALUE_INT, NULL);

        gui_msg_setup_component(true, false, subject_title, ui_scr->video_photo_lbl_menu_title, &guider_msg_data, gui_msg_set_label_text_by_string_cb, GUI_MODEL_GLOBAL_SUBPAGE_MSG_ID_TITLE, GUI_MSG_ACCESS_GET, VALUE_STRING, NULL);

        gui_msg_setup_component(true, false, subject_roller_opt, ui_scr->video_photo_roller_mutifunc, &guider_msg_data, gui_msg_set_roller_roller_name_by_string_cb, GUI_MODEL_GLOBAL_SUBPAGE_MSG_ID_ROLLER_OPT, GUI_MSG_ACCESS_GET, VALUE_STRING, NULL);
        gui_msg_setup_component(true, false, subject_show_roller, ui_scr->video_photo_roller_mutifunc, &guider_msg_data, gui_msg_set_clear_flag_by_int32_cb, GUI_MODEL_GLOBAL_SUBPAGE_MSG_ID_SHOW_ROLLER, GUI_MSG_ACCESS_GET, VALUE_INT, NULL);
        gui_msg_setup_component(true, false, subject_hide_roller, ui_scr->video_photo_roller_mutifunc, &guider_msg_data, gui_msg_set_flag_by_int32_cb, GUI_MODEL_GLOBAL_SUBPAGE_MSG_ID_HIDE_ROLLER, GUI_MSG_ACCESS_GET, VALUE_INT, NULL);

        gui_msg_setup_component(true, false, subject_state_funkey1, ui_scr->video_photo_lbl_funkey1, &guider_msg_data, gui_msg_set_control_state_by_int32_cb, GUI_MODEL_GLOBAL_SUBPAGE_MSG_ID_STATE_FUNKEY1, GUI_MSG_ACCESS_GET, VALUE_INT, NULL);
        gui_msg_setup_component(true, false, subject_funckey1, ui_scr->video_photo_lbl_funkey1, &guider_msg_data, gui_model_global_subpage_msg_video_photo_lbl_funkey1_set_text_cb, GUI_MODEL_GLOBAL_SUBPAGE_MSG_ID_FUNCKEY1, GUI_MSG_ACCESS_GET, VALUE_STRING, NULL);
        gui_msg_setup_component(true, false, subject_show_funckey1, ui_scr->video_photo_lbl_funkey1, &guider_msg_data, gui_msg_set_clear_flag_by_int32_cb, GUI_MODEL_GLOBAL_SUBPAGE_MSG_ID_SHOW_FUNCKEY1, GUI_MSG_ACCESS_GET, VALUE_INT, NULL);
        gui_msg_setup_component(true, false, subject_hide_funckey1, ui_scr->video_photo_lbl_funkey1, &guider_msg_data, gui_msg_set_flag_by_int32_cb, GUI_MODEL_GLOBAL_SUBPAGE_MSG_ID_HIDE_FUNCKEY1, GUI_MSG_ACCESS_GET, VALUE_INT, NULL);

        gui_msg_setup_component(true, false, subject_state_funkey2, ui_scr->video_photo_lbl_funkey2, &guider_msg_data, gui_msg_set_control_state_by_int32_cb, GUI_MODEL_GLOBAL_SUBPAGE_MSG_ID_STATE_FUNKEY2, GUI_MSG_ACCESS_GET, VALUE_INT, NULL);
        gui_msg_setup_component(true, false, subject_funckey2, ui_scr->video_photo_lbl_funkey2, &guider_msg_data, gui_model_global_subpage_msg_video_photo_lbl_funkey2_set_text_cb, GUI_MODEL_GLOBAL_SUBPAGE_MSG_ID_FUNCKEY2, GUI_MSG_ACCESS_GET, VALUE_STRING, NULL);
        gui_msg_setup_component(true, false, subject_show_funckey2, ui_scr->video_photo_lbl_funkey2, &guider_msg_data, gui_msg_set_clear_flag_by_int32_cb, GUI_MODEL_GLOBAL_SUBPAGE_MSG_ID_SHOW_FUNCKEY2, GUI_MSG_ACCESS_GET, VALUE_INT, NULL);
        gui_msg_setup_component(true, false, subject_hide_funckey2, ui_scr->video_photo_lbl_funkey2, &guider_msg_data, gui_msg_set_flag_by_int32_cb, GUI_MODEL_GLOBAL_SUBPAGE_MSG_ID_HIDE_FUNCKEY2, GUI_MSG_ACCESS_GET, VALUE_INT, NULL);

        gui_msg_setup_component(true, false, subject_state_funkey3, ui_scr->video_photo_lbl_funkey3, &guider_msg_data, gui_msg_set_control_state_by_int32_cb, GUI_MODEL_GLOBAL_SUBPAGE_MSG_ID_STATE_FUNKEY3, GUI_MSG_ACCESS_GET, VALUE_INT, NULL);
        gui_msg_setup_component(true, false, subject_funckey3, ui_scr->video_photo_lbl_funkey3, &guider_msg_data, gui_model_global_subpage_msg_video_photo_lbl_funkey3_set_text_cb, GUI_MODEL_GLOBAL_SUBPAGE_MSG_ID_FUNCKEY3, GUI_MSG_ACCESS_GET, VALUE_STRING, NULL);
        gui_msg_setup_component(true, false, subject_show_funckey3, ui_scr->video_photo_lbl_funkey3, &guider_msg_data, gui_msg_set_clear_flag_by_int32_cb, GUI_MODEL_GLOBAL_SUBPAGE_MSG_ID_SHOW_FUNCKEY3, GUI_MSG_ACCESS_GET, VALUE_INT, NULL);
        gui_msg_setup_component(true, false, subject_hide_funckey3, ui_scr->video_photo_lbl_funkey3, &guider_msg_data, gui_msg_set_flag_by_int32_cb, GUI_MODEL_GLOBAL_SUBPAGE_MSG_ID_HIDE_FUNCKEY3, GUI_MSG_ACCESS_GET, VALUE_INT, NULL);

        gui_msg_setup_component(true, false, subject_funckey4, ui_scr->video_photo_lbl_funkey4, &guider_msg_data, gui_model_global_subpage_msg_video_photo_lbl_funkey4_set_text_cb, GUI_MODEL_GLOBAL_SUBPAGE_MSG_ID_FUNCKEY4, GUI_MSG_ACCESS_GET, VALUE_STRING, NULL);
        gui_msg_setup_component(true, false, subject_show_funckey4, ui_scr->video_photo_lbl_funkey4, &guider_msg_data, gui_msg_set_clear_flag_by_int32_cb, GUI_MODEL_GLOBAL_SUBPAGE_MSG_ID_SHOW_FUNCKEY4, GUI_MSG_ACCESS_GET, VALUE_INT, NULL);
        gui_msg_setup_component(true, false, subject_hide_funckey4, ui_scr->video_photo_lbl_funkey4, &guider_msg_data, gui_msg_set_flag_by_int32_cb, GUI_MODEL_GLOBAL_SUBPAGE_MSG_ID_HIDE_FUNCKEY4, GUI_MSG_ACCESS_GET, VALUE_INT, NULL);


        for (int i = 0; i < 20; i++) {
            if (status[i].msg_id == GUI_MODEL_GLOBAL_SUBPAGE_MSG_ID_SUBPAGE_ICON) {
                status[i].is_subscribe = 1;
            }
            if (status[i].msg_id == GUI_MODEL_GLOBAL_SUBPAGE_MSG_ID_TITLE) {
                status[i].is_subscribe = 1;
            }
            if (status[i].msg_id == GUI_MODEL_GLOBAL_SUBPAGE_MSG_ID_ROLLER_OPT) {
                status[i].is_subscribe = 1;
            }
            if (status[i].msg_id == GUI_MODEL_GLOBAL_SUBPAGE_MSG_ID_SHOW_ROLLER) {
                status[i].is_subscribe = 1;
            }
            if (status[i].msg_id == GUI_MODEL_GLOBAL_SUBPAGE_MSG_ID_HIDE_ROLLER) {
                status[i].is_subscribe = 1;
            }
            if (status[i].msg_id == GUI_MODEL_GLOBAL_SUBPAGE_MSG_ID_STATE_FUNKEY1) {
                status[i].is_subscribe = 1;
            }
            if (status[i].msg_id == GUI_MODEL_GLOBAL_SUBPAGE_MSG_ID_FUNCKEY1) {
                status[i].is_subscribe = 1;
            }
            if (status[i].msg_id == GUI_MODEL_GLOBAL_SUBPAGE_MSG_ID_SHOW_FUNCKEY1) {
                status[i].is_subscribe = 1;
            }
            if (status[i].msg_id == GUI_MODEL_GLOBAL_SUBPAGE_MSG_ID_HIDE_FUNCKEY1) {
                status[i].is_subscribe = 1;
            }
            if (status[i].msg_id == GUI_MODEL_GLOBAL_SUBPAGE_MSG_ID_STATE_FUNKEY2) {
                status[i].is_subscribe = 1;
            }
            if (status[i].msg_id == GUI_MODEL_GLOBAL_SUBPAGE_MSG_ID_FUNCKEY2) {
                status[i].is_subscribe = 1;
            }
            if (status[i].msg_id == GUI_MODEL_GLOBAL_SUBPAGE_MSG_ID_SHOW_FUNCKEY2) {
                status[i].is_subscribe = 1;
            }
            if (status[i].msg_id == GUI_MODEL_GLOBAL_SUBPAGE_MSG_ID_HIDE_FUNCKEY2) {
                status[i].is_subscribe = 1;
            }
            if (status[i].msg_id == GUI_MODEL_GLOBAL_SUBPAGE_MSG_ID_STATE_FUNKEY3) {
                status[i].is_subscribe = 1;
            }
            if (status[i].msg_id == GUI_MODEL_GLOBAL_SUBPAGE_MSG_ID_FUNCKEY3) {
                status[i].is_subscribe = 1;
            }
            if (status[i].msg_id == GUI_MODEL_GLOBAL_SUBPAGE_MSG_ID_SHOW_FUNCKEY3) {
                status[i].is_subscribe = 1;
            }
            if (status[i].msg_id == GUI_MODEL_GLOBAL_SUBPAGE_MSG_ID_HIDE_FUNCKEY3) {
                status[i].is_subscribe = 1;
            }
            if (status[i].msg_id == GUI_MODEL_GLOBAL_SUBPAGE_MSG_ID_FUNCKEY4) {
                status[i].is_subscribe = 1;
            }
            if (status[i].msg_id == GUI_MODEL_GLOBAL_SUBPAGE_MSG_ID_SHOW_FUNCKEY4) {
                status[i].is_subscribe = 1;
            }
            if (status[i].msg_id == GUI_MODEL_GLOBAL_SUBPAGE_MSG_ID_HIDE_FUNCKEY4) {
                status[i].is_subscribe = 1;
            }
        }
    }

    for (int i = 0; i < 20; i++) {
        if (status[i].is_subscribe == 0 && status[i].is_unsubscribe == 1) {
            gui_msg_subscribe_change(status[i].msg_id, GUI_MSG_UNSUBSCRIBE);
        } else if (status[i].is_subscribe == 1 && status[i].is_unsubscribe == 0) {
            gui_msg_subscribe_change(status[i].msg_id, GUI_MSG_SUBSCRIBE);
        }
    }
}

void gui_model_global_subpage_msg_unsubscribe()
{
    _gui_msg_status_t status[20] = {
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
    };
    for (int i = 0; i < 20; i++) {
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

    for (int i = 0; i < 20; i++) {
        if (status[i].is_unsubscribe == 1) {
            gui_msg_subscribe_change(status[i].msg_id, GUI_MSG_UNSUBSCRIBE);
        }
    }
}

gui_msg_data_t *gui_model_global_subpage_msg_get(int32_t msg_id)
{
    switch (msg_id) {
    case GUI_MODEL_GLOBAL_SUBPAGE_MSG_ID_SUBPAGE_ICON: {
        gui_model_global_subpage_msg_subpage_icon_cb(GUI_MSG_ACCESS_GET, &guider_msg_data, VALUE_INT);
        break;
    }
    case GUI_MODEL_GLOBAL_SUBPAGE_MSG_ID_FUNCKEY1: {
        gui_model_global_subpage_msg_funckey1_cb(GUI_MSG_ACCESS_GET, &guider_msg_data, VALUE_STRING);
        break;
    }
    case GUI_MODEL_GLOBAL_SUBPAGE_MSG_ID_FUNCKEY2: {
        gui_model_global_subpage_msg_funckey2_cb(GUI_MSG_ACCESS_GET, &guider_msg_data, VALUE_STRING);
        break;
    }
    case GUI_MODEL_GLOBAL_SUBPAGE_MSG_ID_FUNCKEY3: {
        gui_model_global_subpage_msg_funckey3_cb(GUI_MSG_ACCESS_GET, &guider_msg_data, VALUE_STRING);
        break;
    }
    case GUI_MODEL_GLOBAL_SUBPAGE_MSG_ID_FUNCKEY4: {
        gui_model_global_subpage_msg_funckey4_cb(GUI_MSG_ACCESS_GET, &guider_msg_data, VALUE_STRING);
        break;
    }
    case GUI_MODEL_GLOBAL_SUBPAGE_MSG_ID_TITLE: {
        gui_model_global_subpage_msg_title_cb(GUI_MSG_ACCESS_GET, &guider_msg_data, VALUE_STRING);
        break;
    }
    case GUI_MODEL_GLOBAL_SUBPAGE_MSG_ID_HIDE_FUNCKEY1: {
        gui_model_global_subpage_msg_hide_funckey1_cb(GUI_MSG_ACCESS_GET, &guider_msg_data, VALUE_INT);
        break;
    }
    case GUI_MODEL_GLOBAL_SUBPAGE_MSG_ID_HIDE_FUNCKEY2: {
        gui_model_global_subpage_msg_hide_funckey2_cb(GUI_MSG_ACCESS_GET, &guider_msg_data, VALUE_INT);
        break;
    }
    case GUI_MODEL_GLOBAL_SUBPAGE_MSG_ID_HIDE_FUNCKEY3: {
        gui_model_global_subpage_msg_hide_funckey3_cb(GUI_MSG_ACCESS_GET, &guider_msg_data, VALUE_INT);
        break;
    }
    case GUI_MODEL_GLOBAL_SUBPAGE_MSG_ID_HIDE_FUNCKEY4: {
        gui_model_global_subpage_msg_hide_funckey4_cb(GUI_MSG_ACCESS_GET, &guider_msg_data, VALUE_INT);
        break;
    }
    case GUI_MODEL_GLOBAL_SUBPAGE_MSG_ID_SHOW_FUNCKEY1: {
        gui_model_global_subpage_msg_show_funckey1_cb(GUI_MSG_ACCESS_GET, &guider_msg_data, VALUE_INT);
        break;
    }
    case GUI_MODEL_GLOBAL_SUBPAGE_MSG_ID_SHOW_FUNCKEY2: {
        gui_model_global_subpage_msg_show_funckey2_cb(GUI_MSG_ACCESS_GET, &guider_msg_data, VALUE_INT);
        break;
    }
    case GUI_MODEL_GLOBAL_SUBPAGE_MSG_ID_SHOW_FUNCKEY3: {
        gui_model_global_subpage_msg_show_funckey3_cb(GUI_MSG_ACCESS_GET, &guider_msg_data, VALUE_INT);
        break;
    }
    case GUI_MODEL_GLOBAL_SUBPAGE_MSG_ID_SHOW_FUNCKEY4: {
        gui_model_global_subpage_msg_show_funckey4_cb(GUI_MSG_ACCESS_GET, &guider_msg_data, VALUE_INT);
        break;
    }
    case GUI_MODEL_GLOBAL_SUBPAGE_MSG_ID_ROLLER_OPT: {
        gui_model_global_subpage_msg_roller_opt_cb(GUI_MSG_ACCESS_GET, &guider_msg_data, VALUE_STRING);
        break;
    }
    case GUI_MODEL_GLOBAL_SUBPAGE_MSG_ID_SHOW_ROLLER: {
        gui_model_global_subpage_msg_show_roller_cb(GUI_MSG_ACCESS_GET, &guider_msg_data, VALUE_INT);
        break;
    }
    case GUI_MODEL_GLOBAL_SUBPAGE_MSG_ID_HIDE_ROLLER: {
        gui_model_global_subpage_msg_hide_roller_cb(GUI_MSG_ACCESS_GET, &guider_msg_data, VALUE_INT);
        break;
    }
    case GUI_MODEL_GLOBAL_SUBPAGE_MSG_ID_STATE_FUNKEY1: {
        gui_model_global_subpage_msg_state_funkey1_cb(GUI_MSG_ACCESS_GET, &guider_msg_data, VALUE_INT);
        break;
    }
    case GUI_MODEL_GLOBAL_SUBPAGE_MSG_ID_STATE_FUNKEY2: {
        gui_model_global_subpage_msg_state_funkey2_cb(GUI_MSG_ACCESS_GET, &guider_msg_data, VALUE_INT);
        break;
    }
    case GUI_MODEL_GLOBAL_SUBPAGE_MSG_ID_STATE_FUNKEY3: {
        gui_model_global_subpage_msg_state_funkey3_cb(GUI_MSG_ACCESS_GET, &guider_msg_data, VALUE_INT);
        break;
    }
    default:
        return NULL;
    }
    return &guider_msg_data;
}

void gui_model_global_subpage_msg_action_change(int32_t msg_id, gui_msg_action_t access, gui_msg_data_t *data, gui_msg_data_type_t type)
{
    switch (msg_id) {
    case GUI_MODEL_GLOBAL_SUBPAGE_MSG_ID_SUBPAGE_ICON: {
        gui_model_global_subpage_msg_subpage_icon_cb(access, data, type);
        break;
    }
    case GUI_MODEL_GLOBAL_SUBPAGE_MSG_ID_FUNCKEY1: {
        gui_model_global_subpage_msg_funckey1_cb(access, data, type);
        break;
    }
    case GUI_MODEL_GLOBAL_SUBPAGE_MSG_ID_FUNCKEY2: {
        gui_model_global_subpage_msg_funckey2_cb(access, data, type);
        break;
    }
    case GUI_MODEL_GLOBAL_SUBPAGE_MSG_ID_FUNCKEY3: {
        gui_model_global_subpage_msg_funckey3_cb(access, data, type);
        break;
    }
    case GUI_MODEL_GLOBAL_SUBPAGE_MSG_ID_FUNCKEY4: {
        gui_model_global_subpage_msg_funckey4_cb(access, data, type);
        break;
    }
    case GUI_MODEL_GLOBAL_SUBPAGE_MSG_ID_TITLE: {
        gui_model_global_subpage_msg_title_cb(access, data, type);
        break;
    }
    case GUI_MODEL_GLOBAL_SUBPAGE_MSG_ID_HIDE_FUNCKEY1: {
        gui_model_global_subpage_msg_hide_funckey1_cb(access, data, type);
        break;
    }
    case GUI_MODEL_GLOBAL_SUBPAGE_MSG_ID_HIDE_FUNCKEY2: {
        gui_model_global_subpage_msg_hide_funckey2_cb(access, data, type);
        break;
    }
    case GUI_MODEL_GLOBAL_SUBPAGE_MSG_ID_HIDE_FUNCKEY3: {
        gui_model_global_subpage_msg_hide_funckey3_cb(access, data, type);
        break;
    }
    case GUI_MODEL_GLOBAL_SUBPAGE_MSG_ID_HIDE_FUNCKEY4: {
        gui_model_global_subpage_msg_hide_funckey4_cb(access, data, type);
        break;
    }
    case GUI_MODEL_GLOBAL_SUBPAGE_MSG_ID_SHOW_FUNCKEY1: {
        gui_model_global_subpage_msg_show_funckey1_cb(access, data, type);
        break;
    }
    case GUI_MODEL_GLOBAL_SUBPAGE_MSG_ID_SHOW_FUNCKEY2: {
        gui_model_global_subpage_msg_show_funckey2_cb(access, data, type);
        break;
    }
    case GUI_MODEL_GLOBAL_SUBPAGE_MSG_ID_SHOW_FUNCKEY3: {
        gui_model_global_subpage_msg_show_funckey3_cb(access, data, type);
        break;
    }
    case GUI_MODEL_GLOBAL_SUBPAGE_MSG_ID_SHOW_FUNCKEY4: {
        gui_model_global_subpage_msg_show_funckey4_cb(access, data, type);
        break;
    }
    case GUI_MODEL_GLOBAL_SUBPAGE_MSG_ID_ROLLER_OPT: {
        gui_model_global_subpage_msg_roller_opt_cb(access, data, type);
        break;
    }
    case GUI_MODEL_GLOBAL_SUBPAGE_MSG_ID_SHOW_ROLLER: {
        gui_model_global_subpage_msg_show_roller_cb(access, data, type);
        break;
    }
    case GUI_MODEL_GLOBAL_SUBPAGE_MSG_ID_HIDE_ROLLER: {
        gui_model_global_subpage_msg_hide_roller_cb(access, data, type);
        break;
    }
    case GUI_MODEL_GLOBAL_SUBPAGE_MSG_ID_STATE_FUNKEY1: {
        gui_model_global_subpage_msg_state_funkey1_cb(access, data, type);
        break;
    }
    case GUI_MODEL_GLOBAL_SUBPAGE_MSG_ID_STATE_FUNKEY2: {
        gui_model_global_subpage_msg_state_funkey2_cb(access, data, type);
        break;
    }
    case GUI_MODEL_GLOBAL_SUBPAGE_MSG_ID_STATE_FUNKEY3: {
        gui_model_global_subpage_msg_state_funkey3_cb(access, data, type);
        break;
    }
    default: {
        break;
    }
    }
}

gui_msg_status_t gui_model_global_subpage_msg_send(int32_t msg_id, void *value, int32_t len)
{
    if (msg_id == GUI_MODEL_GLOBAL_SUBPAGE_MSG_ID) {
    } else {
        gui_msg_data_type_t data_type = VALUE_INT;
        switch (msg_id) {
        case GUI_MODEL_GLOBAL_SUBPAGE_MSG_ID_SUBPAGE_ICON: {
            data_type = VALUE_INT;
            guider_msg_data.value_array.ptr = value;
            guider_msg_data.value_array.len = len;
            break;
        }
        case GUI_MODEL_GLOBAL_SUBPAGE_MSG_ID_FUNCKEY1: {
            data_type = VALUE_STRING;
            guider_msg_data.value_array.ptr = value;
            guider_msg_data.value_array.len = len;
            break;
        }
        case GUI_MODEL_GLOBAL_SUBPAGE_MSG_ID_FUNCKEY2: {
            data_type = VALUE_STRING;
            guider_msg_data.value_array.ptr = value;
            guider_msg_data.value_array.len = len;
            break;
        }
        case GUI_MODEL_GLOBAL_SUBPAGE_MSG_ID_FUNCKEY3: {
            data_type = VALUE_STRING;
            guider_msg_data.value_array.ptr = value;
            guider_msg_data.value_array.len = len;
            break;
        }
        case GUI_MODEL_GLOBAL_SUBPAGE_MSG_ID_FUNCKEY4: {
            data_type = VALUE_STRING;
            guider_msg_data.value_array.ptr = value;
            guider_msg_data.value_array.len = len;
            break;
        }
        case GUI_MODEL_GLOBAL_SUBPAGE_MSG_ID_TITLE: {
            data_type = VALUE_STRING;
            guider_msg_data.value_array.ptr = value;
            guider_msg_data.value_array.len = len;
            break;
        }
        case GUI_MODEL_GLOBAL_SUBPAGE_MSG_ID_HIDE_FUNCKEY1: {
            data_type = VALUE_INT;
            guider_msg_data.value_array.ptr = value;
            guider_msg_data.value_array.len = len;
            break;
        }
        case GUI_MODEL_GLOBAL_SUBPAGE_MSG_ID_HIDE_FUNCKEY2: {
            data_type = VALUE_INT;
            guider_msg_data.value_array.ptr = value;
            guider_msg_data.value_array.len = len;
            break;
        }
        case GUI_MODEL_GLOBAL_SUBPAGE_MSG_ID_HIDE_FUNCKEY3: {
            data_type = VALUE_INT;
            guider_msg_data.value_array.ptr = value;
            guider_msg_data.value_array.len = len;
            break;
        }
        case GUI_MODEL_GLOBAL_SUBPAGE_MSG_ID_HIDE_FUNCKEY4: {
            data_type = VALUE_INT;
            guider_msg_data.value_array.ptr = value;
            guider_msg_data.value_array.len = len;
            break;
        }
        case GUI_MODEL_GLOBAL_SUBPAGE_MSG_ID_SHOW_FUNCKEY1: {
            data_type = VALUE_INT;
            guider_msg_data.value_array.ptr = value;
            guider_msg_data.value_array.len = len;
            break;
        }
        case GUI_MODEL_GLOBAL_SUBPAGE_MSG_ID_SHOW_FUNCKEY2: {
            data_type = VALUE_INT;
            guider_msg_data.value_array.ptr = value;
            guider_msg_data.value_array.len = len;
            break;
        }
        case GUI_MODEL_GLOBAL_SUBPAGE_MSG_ID_SHOW_FUNCKEY3: {
            data_type = VALUE_INT;
            guider_msg_data.value_array.ptr = value;
            guider_msg_data.value_array.len = len;
            break;
        }
        case GUI_MODEL_GLOBAL_SUBPAGE_MSG_ID_SHOW_FUNCKEY4: {
            data_type = VALUE_INT;
            guider_msg_data.value_array.ptr = value;
            guider_msg_data.value_array.len = len;
            break;
        }
        case GUI_MODEL_GLOBAL_SUBPAGE_MSG_ID_ROLLER_OPT: {
            data_type = VALUE_STRING;
            guider_msg_data.value_array.ptr = value;
            guider_msg_data.value_array.len = len;
            break;
        }
        case GUI_MODEL_GLOBAL_SUBPAGE_MSG_ID_SHOW_ROLLER: {
            data_type = VALUE_INT;
            guider_msg_data.value_array.ptr = value;
            guider_msg_data.value_array.len = len;
            break;
        }
        case GUI_MODEL_GLOBAL_SUBPAGE_MSG_ID_HIDE_ROLLER: {
            data_type = VALUE_INT;
            guider_msg_data.value_array.ptr = value;
            guider_msg_data.value_array.len = len;
            break;
        }
        case GUI_MODEL_GLOBAL_SUBPAGE_MSG_ID_STATE_FUNKEY1: {
            data_type = VALUE_INT;
            guider_msg_data.value_array.ptr = value;
            guider_msg_data.value_array.len = len;
            break;
        }
        case GUI_MODEL_GLOBAL_SUBPAGE_MSG_ID_STATE_FUNKEY2: {
            data_type = VALUE_INT;
            guider_msg_data.value_array.ptr = value;
            guider_msg_data.value_array.len = len;
            break;
        }
        case GUI_MODEL_GLOBAL_SUBPAGE_MSG_ID_STATE_FUNKEY3: {
            data_type = VALUE_INT;
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
