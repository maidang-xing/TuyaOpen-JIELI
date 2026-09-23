#include "app_config.h"
#ifdef CONFIG_UI_STYLE_JL_ENABLE
/*Generate Code, Do NOT Edit!*/
#include "./gui_msg.h"

gui_msg_data_t guider_msg_data = {0};
gui_msg_send_status_t gui_msg_send_status = GUI_MSG_SEND_DONE;
static lv_ll_t subs_ll;

void gui_msg_init(lv_ui *ui)
{
#if LV_USE_OBSERVER
    _lv_ll_init(&subs_ll, sizeof(gui_msg_sub_t));
    gui_model_msg_init(ui);
    gui_model_global_subpage_msg_init(ui);
    gui_model_main_msg_init(ui);
    gui_model_sys_setting_msg_init(ui);
    gui_model_update_msg_init(ui);
    gui_model_video_photo_msg_init(ui);
    gui_model_video_play_msg_init(ui);
    gui_model_video_rec_msg_init(ui);
    gui_sys_model_msg_init(ui);
#endif
}
void gui_msg_init_ui()
{
#if LV_USE_OBSERVER
    gui_model_msg_init_ui();
    gui_model_global_subpage_msg_init_ui();
    gui_model_main_msg_init_ui();
    gui_model_sys_setting_msg_init_ui();
    gui_model_update_msg_init_ui();
    gui_model_video_photo_msg_init_ui();
    gui_model_video_play_msg_init_ui();
    gui_model_video_rec_msg_init_ui();
    gui_sys_model_msg_init_ui();
#endif
}
void gui_msg_init_events()
{
#if LV_USE_OBSERVER
    gui_model_msg_init_events();
    gui_model_global_subpage_msg_init_events();
    gui_model_main_msg_init_events();
    gui_model_sys_setting_msg_init_events();
    gui_model_update_msg_init_events();
    gui_model_video_photo_msg_init_events();
    gui_model_video_play_msg_init_events();
    gui_model_video_rec_msg_init_events();
    gui_sys_model_msg_init_events();
#endif
}
void gui_msg_unsubscribe()
{
#if LV_USE_OBSERVER
    gui_model_msg_unsubscribe();
    gui_model_global_subpage_msg_unsubscribe();
    gui_model_main_msg_unsubscribe();
    gui_model_sys_setting_msg_unsubscribe();
    gui_model_update_msg_unsubscribe();
    gui_model_video_photo_msg_unsubscribe();
    gui_model_video_play_msg_unsubscribe();
    gui_model_video_rec_msg_unsubscribe();
    gui_sys_model_msg_unsubscribe();
#endif
}
gui_msg_status_t gui_msg_send(int32_t msg_id, void *value, int32_t len)
{
#if LV_USE_OBSERVER
    gui_msg_send_status = GUI_MSG_SENDING;
    gui_msg_status_t ret;
    switch (msg_id) {
    case GUI_MODEL_MSG_ID_CUR_TIME:
    case GUI_MODEL_MSG_ID_PREV_FILE:
    case GUI_MODEL_MSG_ID_NEXT_FILE:
    case GUI_MODEL_MSG_ID_VIDEO_PAUSE:
    case GUI_MODEL_MSG_ID_CUR_TIME_PROCESS:
    case GUI_MODEL_MSG_ID_FILE_NAME:
    case GUI_MODEL_MSG_ID_TOTAL_TIME:
    case GUI_MODEL_MSG_ID_FILE_PATH:
    case GUI_MODEL_MSG_ID_FILE_NUM:
        ret = gui_model_msg_send(msg_id, value, len);
        gui_msg_send_status = GUI_MSG_SEND_DONE;
        return ret;

    case GUI_MODEL_GLOBAL_SUBPAGE_MSG_ID_SUBPAGE_ICON:
    case GUI_MODEL_GLOBAL_SUBPAGE_MSG_ID_FUNCKEY1:
    case GUI_MODEL_GLOBAL_SUBPAGE_MSG_ID_FUNCKEY2:
    case GUI_MODEL_GLOBAL_SUBPAGE_MSG_ID_FUNCKEY3:
    case GUI_MODEL_GLOBAL_SUBPAGE_MSG_ID_FUNCKEY4:
    case GUI_MODEL_GLOBAL_SUBPAGE_MSG_ID_TITLE:
    case GUI_MODEL_GLOBAL_SUBPAGE_MSG_ID_HIDE_FUNCKEY1:
    case GUI_MODEL_GLOBAL_SUBPAGE_MSG_ID_HIDE_FUNCKEY2:
    case GUI_MODEL_GLOBAL_SUBPAGE_MSG_ID_HIDE_FUNCKEY3:
    case GUI_MODEL_GLOBAL_SUBPAGE_MSG_ID_HIDE_FUNCKEY4:
    case GUI_MODEL_GLOBAL_SUBPAGE_MSG_ID_SHOW_FUNCKEY1:
    case GUI_MODEL_GLOBAL_SUBPAGE_MSG_ID_SHOW_FUNCKEY2:
    case GUI_MODEL_GLOBAL_SUBPAGE_MSG_ID_SHOW_FUNCKEY3:
    case GUI_MODEL_GLOBAL_SUBPAGE_MSG_ID_SHOW_FUNCKEY4:
    case GUI_MODEL_GLOBAL_SUBPAGE_MSG_ID_ROLLER_OPT:
    case GUI_MODEL_GLOBAL_SUBPAGE_MSG_ID_SHOW_ROLLER:
    case GUI_MODEL_GLOBAL_SUBPAGE_MSG_ID_HIDE_ROLLER:
    case GUI_MODEL_GLOBAL_SUBPAGE_MSG_ID_STATE_FUNKEY1:
    case GUI_MODEL_GLOBAL_SUBPAGE_MSG_ID_STATE_FUNKEY2:
    case GUI_MODEL_GLOBAL_SUBPAGE_MSG_ID_STATE_FUNKEY3:
        ret = gui_model_global_subpage_msg_send(msg_id, value, len);
        gui_msg_send_status = GUI_MSG_SEND_DONE;
        return ret;

    case GUI_MODEL_MAIN_MSG_ID_SYSTIME:
    case GUI_MODEL_MAIN_MSG_ID_SD_ICON:
    case GUI_MODEL_MAIN_MSG_ID_BATTERY:
    case GUI_MODEL_MAIN_MSG_ID_SHOW_WIN_SWITCH:
    case GUI_MODEL_MAIN_MSG_ID_HIDE_WIN_SWITCH:
    case GUI_MODEL_MAIN_MSG_ID_SYS_PROMPT:
    case GUI_MODEL_MAIN_MSG_ID_HEADLAMP:
    case GUI_MODEL_MAIN_MSG_ID_SYS_PROMPT_SHOW:
    case GUI_MODEL_MAIN_MSG_ID_SHOW_DEL_BTN:
    case GUI_MODEL_MAIN_MSG_ID_HIDE_DEL_BTN:
    case GUI_MODEL_MAIN_MSG_ID_WEEKDAY:
    case GUI_MODEL_MAIN_MSG_ID_SHOW_HOME_BTN:
    case GUI_MODEL_MAIN_MSG_ID_HIDE_HOME_BTN:
        ret = gui_model_main_msg_send(msg_id, value, len);
        gui_msg_send_status = GUI_MSG_SEND_DONE;
        return ret;

    case GUI_MODEL_SYS_SETTING_MSG_ID_FUNKEY4:
    case GUI_MODEL_SYS_SETTING_MSG_ID_FUNKEY5:
    case GUI_MODEL_SYS_SETTING_MSG_ID_FUNKEY6:
    case GUI_MODEL_SYS_SETTING_MSG_ID_FUNKEY7:
    case GUI_MODEL_SYS_SETTING_MSG_ID_SUBPAGE_WARNING:
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
    case GUI_MODEL_SYS_SETTING_MSG_ID_STATE_FUNKEY4:
    case GUI_MODEL_SYS_SETTING_MSG_ID_STATE_FUNKEY5:
    case GUI_MODEL_SYS_SETTING_MSG_ID_STATE_FUNKEY6:
    case GUI_MODEL_SYS_SETTING_MSG_ID_STATE_FUNKEY7:
    case GUI_MODEL_SYS_SETTING_MSG_ID_HIDE_FUNKEY4:
    case GUI_MODEL_SYS_SETTING_MSG_ID_FUNKEY8:
    case GUI_MODEL_SYS_SETTING_MSG_ID_HIDE_FUNKEY8:
    case GUI_MODEL_SYS_SETTING_MSG_ID_SHOW_FUNKEY8:
    case GUI_MODEL_SYS_SETTING_MSG_ID_STATE_FUNKEY8:
        ret = gui_model_sys_setting_msg_send(msg_id, value, len);
        gui_msg_send_status = GUI_MSG_SEND_DONE;
        return ret;

    case GUI_MODEL_UPDATE_MSG_ID_UPDATE_TIPS:
    case GUI_MODEL_UPDATE_MSG_ID_UPDATE_PROCE:
        ret = gui_model_update_msg_send(msg_id, value, len);
        gui_msg_send_status = GUI_MSG_SEND_DONE;
        return ret;

    case GUI_MODEL_VIDEO_PHOTO_MSG_ID_ISO_ICON:
    case GUI_MODEL_VIDEO_PHOTO_MSG_ID_RESOLUTION_ICON:
    case GUI_MODEL_VIDEO_PHOTO_MSG_ID_AWB_ICON:
    case GUI_MODEL_VIDEO_PHOTO_MSG_ID_QUALITY_ICON:
    case GUI_MODEL_VIDEO_PHOTO_MSG_ID_SHOT_MODE_ICON:
    case GUI_MODEL_VIDEO_PHOTO_MSG_ID_SHOW_HANDSHAKE:
    case GUI_MODEL_VIDEO_PHOTO_MSG_ID_HIDE_HANDSHAKE:
    case GUI_MODEL_VIDEO_PHOTO_MSG_ID_SHOW_SHOTS:
    case GUI_MODEL_VIDEO_PHOTO_MSG_ID_HIDE_SHOTS:
    case GUI_MODEL_VIDEO_PHOTO_MSG_ID_SHOW_SHOTS_MODE:
    case GUI_MODEL_VIDEO_PHOTO_MSG_ID_HIDE_SHOTS_MODE:
    case GUI_MODEL_VIDEO_PHOTO_MSG_ID_PHOTO_REMAIN:
    case GUI_MODEL_VIDEO_PHOTO_MSG_ID_CAPTURE_TIME:
        ret = gui_model_video_photo_msg_send(msg_id, value, len);
        gui_msg_send_status = GUI_MSG_SEND_DONE;
        return ret;

    case GUI_MODEL_VIDEO_PLAY_MSG_ID_DISP_PROGRESS_BAR:
    case GUI_MODEL_VIDEO_PLAY_MSG_ID_ADD_CLICK_FLAG:
    case GUI_MODEL_VIDEO_PLAY_MSG_ID_CLEAR_CLICK_FLAG:
        ret = gui_model_video_play_msg_send(msg_id, value, len);
        gui_msg_send_status = GUI_MSG_SEND_DONE;
        return ret;

    case GUI_MODEL_VIDEO_REC_MSG_ID_CYCREC_ICON:
    case GUI_MODEL_VIDEO_REC_MSG_ID_MIC_ICON:
    case GUI_MODEL_VIDEO_REC_MSG_ID_DELAYREC_ICON:
    case GUI_MODEL_VIDEO_REC_MSG_ID_GSENSOR_ICON:
    case GUI_MODEL_VIDEO_REC_MSG_ID_CAR_NUNBER:
    case GUI_MODEL_VIDEO_REC_MSG_ID_REC_RESO:
    case GUI_MODEL_VIDEO_REC_MSG_ID_REC_BTN:
    case GUI_MODEL_VIDEO_REC_MSG_ID_SHOW_GSENSOR_ICON:
    case GUI_MODEL_VIDEO_REC_MSG_ID_HIDE_GSENSOR_ICON:
    case GUI_MODEL_VIDEO_REC_MSG_ID_SHOW_GUARD_ICON:
    case GUI_MODEL_VIDEO_REC_MSG_ID_HIDE_GUARD_ICON:
    case GUI_MODEL_VIDEO_REC_MSG_ID_SHOW_MOTION_ICON:
    case GUI_MODEL_VIDEO_REC_MSG_ID_HIDE_MOTION_ICON:
    case GUI_MODEL_VIDEO_REC_MSG_ID_SHOW_HDR_ICON:
    case GUI_MODEL_VIDEO_REC_MSG_ID_HIDE_HDR_ICON:
    case GUI_MODEL_VIDEO_REC_MSG_ID_REC_REMAIN_TIME:
    case GUI_MODEL_VIDEO_REC_MSG_ID_REC_TIME_STATE:
    case GUI_MODEL_VIDEO_REC_MSG_ID_HIDE_CAR_NUM:
    case GUI_MODEL_VIDEO_REC_MSG_ID_SHOW_CAR_NUM:
    case GUI_MODEL_VIDEO_REC_MSG_ID_HIDE_CAR_CRASHLOCK:
    case GUI_MODEL_VIDEO_REC_MSG_ID_SHOW_CAR_CRASHLOCK:
    case GUI_MODEL_VIDEO_REC_MSG_ID_FLASH_HEADLIGHT:
    case GUI_MODEL_VIDEO_REC_MSG_ID_HIDE_REMAIN_TIME:
    case GUI_MODEL_VIDEO_REC_MSG_ID_SHOW_REMAIN_TIME:
    case GUI_MODEL_VIDEO_REC_MSG_ID_HIDE_RECORD_TIME:
    case GUI_MODEL_VIDEO_REC_MSG_ID_SHOW_RECORD_TIME:
    case GUI_MODEL_VIDEO_REC_MSG_ID_APP_CONNECTED:
        ret = gui_model_video_rec_msg_send(msg_id, value, len);
        gui_msg_send_status = GUI_MSG_SEND_DONE;
        return ret;

    case GUI_SYS_MODEL_MSG_ID_SYS_TIME:
        ret = gui_sys_model_msg_send(msg_id, value, len);
        gui_msg_send_status = GUI_MSG_SEND_DONE;
        return ret;

    default:
        break;
    }
    gui_msg_send_status = GUI_MSG_SEND_DONE;
    return GUI_MSG_STATUS_NO_FOUND_ID;
#else
    return GUI_MSG_STATUS_ERROR;
#endif
}
gui_msg_send_status_t gui_msg_get_send_status()
{
    return gui_msg_send_status;
}
GUI_WEAK gui_msg_data_t *gui_msg_get(int32_t msg_id)
{
    return gui_msg_get_guider(msg_id);
}
gui_msg_data_t *gui_msg_get_guider(int32_t msg_id)
{
#if LV_USE_OBSERVER
    switch (msg_id) {
    case GUI_MODEL_MSG_ID:
    case GUI_MODEL_MSG_ID_CUR_TIME:
    case GUI_MODEL_MSG_ID_PREV_FILE:
    case GUI_MODEL_MSG_ID_NEXT_FILE:
    case GUI_MODEL_MSG_ID_VIDEO_PAUSE:
    case GUI_MODEL_MSG_ID_CUR_TIME_PROCESS:
    case GUI_MODEL_MSG_ID_FILE_NAME:
    case GUI_MODEL_MSG_ID_TOTAL_TIME:
    case GUI_MODEL_MSG_ID_FILE_PATH:
    case GUI_MODEL_MSG_ID_FILE_NUM:
        return gui_model_msg_get(msg_id);

    case GUI_MODEL_GLOBAL_SUBPAGE_MSG_ID:
    case GUI_MODEL_GLOBAL_SUBPAGE_MSG_ID_SUBPAGE_ICON:
    case GUI_MODEL_GLOBAL_SUBPAGE_MSG_ID_FUNCKEY1:
    case GUI_MODEL_GLOBAL_SUBPAGE_MSG_ID_FUNCKEY2:
    case GUI_MODEL_GLOBAL_SUBPAGE_MSG_ID_FUNCKEY3:
    case GUI_MODEL_GLOBAL_SUBPAGE_MSG_ID_FUNCKEY4:
    case GUI_MODEL_GLOBAL_SUBPAGE_MSG_ID_TITLE:
    case GUI_MODEL_GLOBAL_SUBPAGE_MSG_ID_HIDE_FUNCKEY1:
    case GUI_MODEL_GLOBAL_SUBPAGE_MSG_ID_HIDE_FUNCKEY2:
    case GUI_MODEL_GLOBAL_SUBPAGE_MSG_ID_HIDE_FUNCKEY3:
    case GUI_MODEL_GLOBAL_SUBPAGE_MSG_ID_HIDE_FUNCKEY4:
    case GUI_MODEL_GLOBAL_SUBPAGE_MSG_ID_SHOW_FUNCKEY1:
    case GUI_MODEL_GLOBAL_SUBPAGE_MSG_ID_SHOW_FUNCKEY2:
    case GUI_MODEL_GLOBAL_SUBPAGE_MSG_ID_SHOW_FUNCKEY3:
    case GUI_MODEL_GLOBAL_SUBPAGE_MSG_ID_SHOW_FUNCKEY4:
    case GUI_MODEL_GLOBAL_SUBPAGE_MSG_ID_ROLLER_OPT:
    case GUI_MODEL_GLOBAL_SUBPAGE_MSG_ID_SHOW_ROLLER:
    case GUI_MODEL_GLOBAL_SUBPAGE_MSG_ID_HIDE_ROLLER:
    case GUI_MODEL_GLOBAL_SUBPAGE_MSG_ID_STATE_FUNKEY1:
    case GUI_MODEL_GLOBAL_SUBPAGE_MSG_ID_STATE_FUNKEY2:
    case GUI_MODEL_GLOBAL_SUBPAGE_MSG_ID_STATE_FUNKEY3:
        return gui_model_global_subpage_msg_get(msg_id);

    case GUI_MODEL_MAIN_MSG_ID:
    case GUI_MODEL_MAIN_MSG_ID_SYSTIME:
    case GUI_MODEL_MAIN_MSG_ID_SD_ICON:
    case GUI_MODEL_MAIN_MSG_ID_BATTERY:
    case GUI_MODEL_MAIN_MSG_ID_SHOW_WIN_SWITCH:
    case GUI_MODEL_MAIN_MSG_ID_HIDE_WIN_SWITCH:
    case GUI_MODEL_MAIN_MSG_ID_SYS_PROMPT:
    case GUI_MODEL_MAIN_MSG_ID_HEADLAMP:
    case GUI_MODEL_MAIN_MSG_ID_SYS_PROMPT_SHOW:
    case GUI_MODEL_MAIN_MSG_ID_SHOW_DEL_BTN:
    case GUI_MODEL_MAIN_MSG_ID_HIDE_DEL_BTN:
    case GUI_MODEL_MAIN_MSG_ID_WEEKDAY:
    case GUI_MODEL_MAIN_MSG_ID_SHOW_HOME_BTN:
    case GUI_MODEL_MAIN_MSG_ID_HIDE_HOME_BTN:
        return gui_model_main_msg_get(msg_id);

    case GUI_MODEL_SYS_SETTING_MSG_ID:
    case GUI_MODEL_SYS_SETTING_MSG_ID_FUNKEY4:
    case GUI_MODEL_SYS_SETTING_MSG_ID_FUNKEY5:
    case GUI_MODEL_SYS_SETTING_MSG_ID_FUNKEY6:
    case GUI_MODEL_SYS_SETTING_MSG_ID_FUNKEY7:
    case GUI_MODEL_SYS_SETTING_MSG_ID_SUBPAGE_WARNING:
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
    case GUI_MODEL_SYS_SETTING_MSG_ID_STATE_FUNKEY4:
    case GUI_MODEL_SYS_SETTING_MSG_ID_STATE_FUNKEY5:
    case GUI_MODEL_SYS_SETTING_MSG_ID_STATE_FUNKEY6:
    case GUI_MODEL_SYS_SETTING_MSG_ID_STATE_FUNKEY7:
    case GUI_MODEL_SYS_SETTING_MSG_ID_HIDE_FUNKEY4:
    case GUI_MODEL_SYS_SETTING_MSG_ID_FUNKEY8:
    case GUI_MODEL_SYS_SETTING_MSG_ID_HIDE_FUNKEY8:
    case GUI_MODEL_SYS_SETTING_MSG_ID_SHOW_FUNKEY8:
    case GUI_MODEL_SYS_SETTING_MSG_ID_STATE_FUNKEY8:
        return gui_model_sys_setting_msg_get(msg_id);

    case GUI_MODEL_UPDATE_MSG_ID:
    case GUI_MODEL_UPDATE_MSG_ID_UPDATE_TIPS:
    case GUI_MODEL_UPDATE_MSG_ID_UPDATE_PROCE:
        return gui_model_update_msg_get(msg_id);

    case GUI_MODEL_VIDEO_PHOTO_MSG_ID:
    case GUI_MODEL_VIDEO_PHOTO_MSG_ID_ISO_ICON:
    case GUI_MODEL_VIDEO_PHOTO_MSG_ID_RESOLUTION_ICON:
    case GUI_MODEL_VIDEO_PHOTO_MSG_ID_AWB_ICON:
    case GUI_MODEL_VIDEO_PHOTO_MSG_ID_QUALITY_ICON:
    case GUI_MODEL_VIDEO_PHOTO_MSG_ID_SHOT_MODE_ICON:
    case GUI_MODEL_VIDEO_PHOTO_MSG_ID_SHOW_HANDSHAKE:
    case GUI_MODEL_VIDEO_PHOTO_MSG_ID_HIDE_HANDSHAKE:
    case GUI_MODEL_VIDEO_PHOTO_MSG_ID_SHOW_SHOTS:
    case GUI_MODEL_VIDEO_PHOTO_MSG_ID_HIDE_SHOTS:
    case GUI_MODEL_VIDEO_PHOTO_MSG_ID_SHOW_SHOTS_MODE:
    case GUI_MODEL_VIDEO_PHOTO_MSG_ID_HIDE_SHOTS_MODE:
    case GUI_MODEL_VIDEO_PHOTO_MSG_ID_PHOTO_REMAIN:
    case GUI_MODEL_VIDEO_PHOTO_MSG_ID_CAPTURE_TIME:
        return gui_model_video_photo_msg_get(msg_id);

    case GUI_MODEL_VIDEO_PLAY_MSG_ID:
    case GUI_MODEL_VIDEO_PLAY_MSG_ID_DISP_PROGRESS_BAR:
    case GUI_MODEL_VIDEO_PLAY_MSG_ID_ADD_CLICK_FLAG:
    case GUI_MODEL_VIDEO_PLAY_MSG_ID_CLEAR_CLICK_FLAG:
        return gui_model_video_play_msg_get(msg_id);

    case GUI_MODEL_VIDEO_REC_MSG_ID:
    case GUI_MODEL_VIDEO_REC_MSG_ID_CYCREC_ICON:
    case GUI_MODEL_VIDEO_REC_MSG_ID_MIC_ICON:
    case GUI_MODEL_VIDEO_REC_MSG_ID_DELAYREC_ICON:
    case GUI_MODEL_VIDEO_REC_MSG_ID_GSENSOR_ICON:
    case GUI_MODEL_VIDEO_REC_MSG_ID_CAR_NUNBER:
    case GUI_MODEL_VIDEO_REC_MSG_ID_REC_RESO:
    case GUI_MODEL_VIDEO_REC_MSG_ID_REC_BTN:
    case GUI_MODEL_VIDEO_REC_MSG_ID_SHOW_GSENSOR_ICON:
    case GUI_MODEL_VIDEO_REC_MSG_ID_HIDE_GSENSOR_ICON:
    case GUI_MODEL_VIDEO_REC_MSG_ID_SHOW_GUARD_ICON:
    case GUI_MODEL_VIDEO_REC_MSG_ID_HIDE_GUARD_ICON:
    case GUI_MODEL_VIDEO_REC_MSG_ID_SHOW_MOTION_ICON:
    case GUI_MODEL_VIDEO_REC_MSG_ID_HIDE_MOTION_ICON:
    case GUI_MODEL_VIDEO_REC_MSG_ID_SHOW_HDR_ICON:
    case GUI_MODEL_VIDEO_REC_MSG_ID_HIDE_HDR_ICON:
    case GUI_MODEL_VIDEO_REC_MSG_ID_REC_REMAIN_TIME:
    case GUI_MODEL_VIDEO_REC_MSG_ID_REC_TIME_STATE:
    case GUI_MODEL_VIDEO_REC_MSG_ID_HIDE_CAR_NUM:
    case GUI_MODEL_VIDEO_REC_MSG_ID_SHOW_CAR_NUM:
    case GUI_MODEL_VIDEO_REC_MSG_ID_HIDE_CAR_CRASHLOCK:
    case GUI_MODEL_VIDEO_REC_MSG_ID_SHOW_CAR_CRASHLOCK:
    case GUI_MODEL_VIDEO_REC_MSG_ID_FLASH_HEADLIGHT:
    case GUI_MODEL_VIDEO_REC_MSG_ID_HIDE_REMAIN_TIME:
    case GUI_MODEL_VIDEO_REC_MSG_ID_SHOW_REMAIN_TIME:
    case GUI_MODEL_VIDEO_REC_MSG_ID_HIDE_RECORD_TIME:
    case GUI_MODEL_VIDEO_REC_MSG_ID_SHOW_RECORD_TIME:
    case GUI_MODEL_VIDEO_REC_MSG_ID_APP_CONNECTED:
        return gui_model_video_rec_msg_get(msg_id);

    case GUI_SYS_MODEL_MSG_ID:
    case GUI_SYS_MODEL_MSG_ID_SYS_TIME:
        return gui_sys_model_msg_get(msg_id);

    default:
        break;
    }
#endif
    return NULL;
}
GUI_WEAK void gui_msg_action_change(int32_t msg_id, gui_msg_action_t access, gui_msg_data_t *data, gui_msg_data_type_t type)
{
    gui_msg_action_change_guider(msg_id, access, data, type);
}
void gui_msg_action_change_guider(int32_t msg_id, gui_msg_action_t access, gui_msg_data_t *data, gui_msg_data_type_t type)
{
#if LV_USE_OBSERVER
    switch (msg_id) {
    case GUI_MODEL_MSG_ID:
    case GUI_MODEL_MSG_ID_CUR_TIME:
    case GUI_MODEL_MSG_ID_PREV_FILE:
    case GUI_MODEL_MSG_ID_NEXT_FILE:
    case GUI_MODEL_MSG_ID_VIDEO_PAUSE:
    case GUI_MODEL_MSG_ID_CUR_TIME_PROCESS:
    case GUI_MODEL_MSG_ID_FILE_NAME:
    case GUI_MODEL_MSG_ID_TOTAL_TIME:
    case GUI_MODEL_MSG_ID_FILE_PATH:
    case GUI_MODEL_MSG_ID_FILE_NUM:
        return gui_model_msg_action_change(msg_id, access, data, type);

    case GUI_MODEL_GLOBAL_SUBPAGE_MSG_ID:
    case GUI_MODEL_GLOBAL_SUBPAGE_MSG_ID_SUBPAGE_ICON:
    case GUI_MODEL_GLOBAL_SUBPAGE_MSG_ID_FUNCKEY1:
    case GUI_MODEL_GLOBAL_SUBPAGE_MSG_ID_FUNCKEY2:
    case GUI_MODEL_GLOBAL_SUBPAGE_MSG_ID_FUNCKEY3:
    case GUI_MODEL_GLOBAL_SUBPAGE_MSG_ID_FUNCKEY4:
    case GUI_MODEL_GLOBAL_SUBPAGE_MSG_ID_TITLE:
    case GUI_MODEL_GLOBAL_SUBPAGE_MSG_ID_HIDE_FUNCKEY1:
    case GUI_MODEL_GLOBAL_SUBPAGE_MSG_ID_HIDE_FUNCKEY2:
    case GUI_MODEL_GLOBAL_SUBPAGE_MSG_ID_HIDE_FUNCKEY3:
    case GUI_MODEL_GLOBAL_SUBPAGE_MSG_ID_HIDE_FUNCKEY4:
    case GUI_MODEL_GLOBAL_SUBPAGE_MSG_ID_SHOW_FUNCKEY1:
    case GUI_MODEL_GLOBAL_SUBPAGE_MSG_ID_SHOW_FUNCKEY2:
    case GUI_MODEL_GLOBAL_SUBPAGE_MSG_ID_SHOW_FUNCKEY3:
    case GUI_MODEL_GLOBAL_SUBPAGE_MSG_ID_SHOW_FUNCKEY4:
    case GUI_MODEL_GLOBAL_SUBPAGE_MSG_ID_ROLLER_OPT:
    case GUI_MODEL_GLOBAL_SUBPAGE_MSG_ID_SHOW_ROLLER:
    case GUI_MODEL_GLOBAL_SUBPAGE_MSG_ID_HIDE_ROLLER:
    case GUI_MODEL_GLOBAL_SUBPAGE_MSG_ID_STATE_FUNKEY1:
    case GUI_MODEL_GLOBAL_SUBPAGE_MSG_ID_STATE_FUNKEY2:
    case GUI_MODEL_GLOBAL_SUBPAGE_MSG_ID_STATE_FUNKEY3:
        return gui_model_global_subpage_msg_action_change(msg_id, access, data, type);

    case GUI_MODEL_MAIN_MSG_ID:
    case GUI_MODEL_MAIN_MSG_ID_SYSTIME:
    case GUI_MODEL_MAIN_MSG_ID_SD_ICON:
    case GUI_MODEL_MAIN_MSG_ID_BATTERY:
    case GUI_MODEL_MAIN_MSG_ID_SHOW_WIN_SWITCH:
    case GUI_MODEL_MAIN_MSG_ID_HIDE_WIN_SWITCH:
    case GUI_MODEL_MAIN_MSG_ID_SYS_PROMPT:
    case GUI_MODEL_MAIN_MSG_ID_HEADLAMP:
    case GUI_MODEL_MAIN_MSG_ID_SYS_PROMPT_SHOW:
    case GUI_MODEL_MAIN_MSG_ID_SHOW_DEL_BTN:
    case GUI_MODEL_MAIN_MSG_ID_HIDE_DEL_BTN:
    case GUI_MODEL_MAIN_MSG_ID_WEEKDAY:
    case GUI_MODEL_MAIN_MSG_ID_SHOW_HOME_BTN:
    case GUI_MODEL_MAIN_MSG_ID_HIDE_HOME_BTN:
        return gui_model_main_msg_action_change(msg_id, access, data, type);

    case GUI_MODEL_SYS_SETTING_MSG_ID:
    case GUI_MODEL_SYS_SETTING_MSG_ID_FUNKEY4:
    case GUI_MODEL_SYS_SETTING_MSG_ID_FUNKEY5:
    case GUI_MODEL_SYS_SETTING_MSG_ID_FUNKEY6:
    case GUI_MODEL_SYS_SETTING_MSG_ID_FUNKEY7:
    case GUI_MODEL_SYS_SETTING_MSG_ID_SUBPAGE_WARNING:
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
    case GUI_MODEL_SYS_SETTING_MSG_ID_STATE_FUNKEY4:
    case GUI_MODEL_SYS_SETTING_MSG_ID_STATE_FUNKEY5:
    case GUI_MODEL_SYS_SETTING_MSG_ID_STATE_FUNKEY6:
    case GUI_MODEL_SYS_SETTING_MSG_ID_STATE_FUNKEY7:
    case GUI_MODEL_SYS_SETTING_MSG_ID_HIDE_FUNKEY4:
    case GUI_MODEL_SYS_SETTING_MSG_ID_FUNKEY8:
    case GUI_MODEL_SYS_SETTING_MSG_ID_HIDE_FUNKEY8:
    case GUI_MODEL_SYS_SETTING_MSG_ID_SHOW_FUNKEY8:
    case GUI_MODEL_SYS_SETTING_MSG_ID_STATE_FUNKEY8:
        return gui_model_sys_setting_msg_action_change(msg_id, access, data, type);

    case GUI_MODEL_UPDATE_MSG_ID:
    case GUI_MODEL_UPDATE_MSG_ID_UPDATE_TIPS:
    case GUI_MODEL_UPDATE_MSG_ID_UPDATE_PROCE:
        return gui_model_update_msg_action_change(msg_id, access, data, type);

    case GUI_MODEL_VIDEO_PHOTO_MSG_ID:
    case GUI_MODEL_VIDEO_PHOTO_MSG_ID_ISO_ICON:
    case GUI_MODEL_VIDEO_PHOTO_MSG_ID_RESOLUTION_ICON:
    case GUI_MODEL_VIDEO_PHOTO_MSG_ID_AWB_ICON:
    case GUI_MODEL_VIDEO_PHOTO_MSG_ID_QUALITY_ICON:
    case GUI_MODEL_VIDEO_PHOTO_MSG_ID_SHOT_MODE_ICON:
    case GUI_MODEL_VIDEO_PHOTO_MSG_ID_SHOW_HANDSHAKE:
    case GUI_MODEL_VIDEO_PHOTO_MSG_ID_HIDE_HANDSHAKE:
    case GUI_MODEL_VIDEO_PHOTO_MSG_ID_SHOW_SHOTS:
    case GUI_MODEL_VIDEO_PHOTO_MSG_ID_HIDE_SHOTS:
    case GUI_MODEL_VIDEO_PHOTO_MSG_ID_SHOW_SHOTS_MODE:
    case GUI_MODEL_VIDEO_PHOTO_MSG_ID_HIDE_SHOTS_MODE:
    case GUI_MODEL_VIDEO_PHOTO_MSG_ID_PHOTO_REMAIN:
    case GUI_MODEL_VIDEO_PHOTO_MSG_ID_CAPTURE_TIME:
        return gui_model_video_photo_msg_action_change(msg_id, access, data, type);

    case GUI_MODEL_VIDEO_PLAY_MSG_ID:
    case GUI_MODEL_VIDEO_PLAY_MSG_ID_DISP_PROGRESS_BAR:
    case GUI_MODEL_VIDEO_PLAY_MSG_ID_ADD_CLICK_FLAG:
    case GUI_MODEL_VIDEO_PLAY_MSG_ID_CLEAR_CLICK_FLAG:
        return gui_model_video_play_msg_action_change(msg_id, access, data, type);

    case GUI_MODEL_VIDEO_REC_MSG_ID:
    case GUI_MODEL_VIDEO_REC_MSG_ID_CYCREC_ICON:
    case GUI_MODEL_VIDEO_REC_MSG_ID_MIC_ICON:
    case GUI_MODEL_VIDEO_REC_MSG_ID_DELAYREC_ICON:
    case GUI_MODEL_VIDEO_REC_MSG_ID_GSENSOR_ICON:
    case GUI_MODEL_VIDEO_REC_MSG_ID_CAR_NUNBER:
    case GUI_MODEL_VIDEO_REC_MSG_ID_REC_RESO:
    case GUI_MODEL_VIDEO_REC_MSG_ID_REC_BTN:
    case GUI_MODEL_VIDEO_REC_MSG_ID_SHOW_GSENSOR_ICON:
    case GUI_MODEL_VIDEO_REC_MSG_ID_HIDE_GSENSOR_ICON:
    case GUI_MODEL_VIDEO_REC_MSG_ID_SHOW_GUARD_ICON:
    case GUI_MODEL_VIDEO_REC_MSG_ID_HIDE_GUARD_ICON:
    case GUI_MODEL_VIDEO_REC_MSG_ID_SHOW_MOTION_ICON:
    case GUI_MODEL_VIDEO_REC_MSG_ID_HIDE_MOTION_ICON:
    case GUI_MODEL_VIDEO_REC_MSG_ID_SHOW_HDR_ICON:
    case GUI_MODEL_VIDEO_REC_MSG_ID_HIDE_HDR_ICON:
    case GUI_MODEL_VIDEO_REC_MSG_ID_REC_REMAIN_TIME:
    case GUI_MODEL_VIDEO_REC_MSG_ID_REC_TIME_STATE:
    case GUI_MODEL_VIDEO_REC_MSG_ID_HIDE_CAR_NUM:
    case GUI_MODEL_VIDEO_REC_MSG_ID_SHOW_CAR_NUM:
    case GUI_MODEL_VIDEO_REC_MSG_ID_HIDE_CAR_CRASHLOCK:
    case GUI_MODEL_VIDEO_REC_MSG_ID_SHOW_CAR_CRASHLOCK:
    case GUI_MODEL_VIDEO_REC_MSG_ID_FLASH_HEADLIGHT:
    case GUI_MODEL_VIDEO_REC_MSG_ID_HIDE_REMAIN_TIME:
    case GUI_MODEL_VIDEO_REC_MSG_ID_SHOW_REMAIN_TIME:
    case GUI_MODEL_VIDEO_REC_MSG_ID_HIDE_RECORD_TIME:
    case GUI_MODEL_VIDEO_REC_MSG_ID_SHOW_RECORD_TIME:
    case GUI_MODEL_VIDEO_REC_MSG_ID_APP_CONNECTED:
        return gui_model_video_rec_msg_action_change(msg_id, access, data, type);

    case GUI_SYS_MODEL_MSG_ID:
    case GUI_SYS_MODEL_MSG_ID_SYS_TIME:
        return gui_sys_model_msg_action_change(msg_id, access, data, type);

    default:
        break;
    }
#endif
}
GUI_WEAK void gui_msg_subscribe_change(int32_t msg_id, gui_msg_subscribe_t sub_type)
{
    gui_msg_subscribe_change_guider(msg_id, sub_type);
}
void gui_msg_subscribe_change_guider(int32_t msg_id, gui_msg_subscribe_t sub_type)
{
}
lv_subject_t *gui_msg_get_subject(int32_t msg_id)
{
    gui_msg_sub_t *sub = gui_msg_get_sub(msg_id);
    if (sub != NULL) {
        return sub->subject;
    }
    return NULL;
}
gui_msg_sub_t *gui_msg_get_sub(int32_t msg_id)
{
    gui_msg_sub_t *head = _lv_ll_get_head(&subs_ll);
    while (head != NULL) {
        if (head->msg_id == msg_id) {
            return head;
        }
        head = _lv_ll_get_next(&subs_ll, head);
    }
    return NULL;
}
gui_msg_sub_t *gui_msg_create_sub(int32_t msg_id)
{
    gui_msg_sub_t *sub = gui_msg_get_sub(msg_id);
    if (sub == NULL) {
        sub = _lv_ll_ins_tail(&subs_ll);
        sub->msg_id = msg_id;
        sub->subject = lv_mem_alloc(sizeof(lv_subject_t));
    }
    return sub;
}
gui_msg_data_t *gui_msg_get_data()
{
    return &guider_msg_data;
}
bool gui_msg_has_observer(lv_subject_t *subject, lv_observer_cb_t cb, lv_obj_t *obj, void *user_data)
{
    if (subject == NULL || subject->type == LV_SUBJECT_TYPE_INVALID) {
        return false;
    }
    lv_observer_t *observer = _lv_ll_get_head(&(subject->subs_ll));
    while (observer != NULL) {
        if (observer->cb == cb && observer->target == obj && observer->user_data == user_data) {
            return true;
        }
        observer = _lv_ll_get_next(&(subject->subs_ll), observer);
    }
    return false;
}
void gui_msg_setup_component(bool subscribe_enabled, bool event_enabled, lv_subject_t *subject, lv_obj_t *target_obj, gui_msg_data_t *msg_data, lv_observer_cb_t observer_cb, int32_t msg_id, gui_msg_action_t msg_action, gui_msg_data_type_t data_type, lv_event_cb_t event_cb)
{
    if (subject == NULL || subject->type == LV_SUBJECT_TYPE_INVALID) {
        return;
    }

    if (subscribe_enabled) {
        if (!gui_msg_has_observer(subject, observer_cb, target_obj, msg_data)) {
            gui_msg_action_change(msg_id, msg_action, msg_data, data_type);
            lv_subject_add_observer_obj(subject, observer_cb, target_obj, msg_data);
        }
    }

    if (event_enabled) {
        lv_obj_remove_event_cb(target_obj, event_cb);
        lv_obj_add_event_cb(target_obj, event_cb, LV_EVENT_VALUE_CHANGED, (void *)msg_id);
    }
}

void gui_msg_set_control_state_by_int32_cb(lv_observer_t *observer, lv_subject_t *subject)
{
    lv_obj_t *obj = lv_observer_get_target_obj(observer);
    if (obj == NULL || lv_obj_is_valid(obj) == false) {
        return;
    }

    gui_msg_data_t *data = (gui_msg_data_t *)observer->user_data;
    lv_obj_clear_state(obj, LV_STATE_ANY);
    lv_obj_add_state(obj, data->value_int);
}
void gui_msg_set_clear_flag_by_int32_cb(lv_observer_t *observer, lv_subject_t *subject)
{
    lv_obj_t *obj = lv_observer_get_target_obj(observer);
    if (obj == NULL || lv_obj_is_valid(obj) == false) {
        return;
    }

    gui_msg_data_t *data = (gui_msg_data_t *)observer->user_data;
    lv_obj_clear_flag(obj, data->value_int);
}
void gui_msg_set_flag_by_int32_cb(lv_observer_t *observer, lv_subject_t *subject)
{
    lv_obj_t *obj = lv_observer_get_target_obj(observer);
    if (obj == NULL || lv_obj_is_valid(obj) == false) {
        return;
    }

    gui_msg_data_t *data = (gui_msg_data_t *)observer->user_data;
    lv_obj_add_flag(obj, data->value_int);
}
void gui_msg_set_label_text_by_string_cb(lv_observer_t *observer, lv_subject_t *subject)
{
    lv_obj_t *obj = lv_observer_get_target_obj(observer);
    if (obj == NULL || lv_obj_is_valid(obj) == false) {
        return;
    }

    gui_msg_data_t *data = (gui_msg_data_t *)observer->user_data;
    lv_label_set_text(obj, data->value_string);
}
void gui_msg_set_roller_roller_name_by_string_cb(lv_observer_t *observer, lv_subject_t *subject)
{
    lv_obj_t *obj = lv_observer_get_target_obj(observer);
    if (obj == NULL || lv_obj_is_valid(obj) == false) {
        return;
    }

    gui_msg_data_t *data = (gui_msg_data_t *)observer->user_data;
    lv_roller_set_options(obj, (const char *)data->value_string, ((lv_roller_t *)obj)->mode);
}
void gui_msg_set_visible_by_bool_cb(lv_observer_t *observer, lv_subject_t *subject)
{
    lv_obj_t *obj = lv_observer_get_target_obj(observer);
    if (obj == NULL || lv_obj_is_valid(obj) == false) {
        return;
    }

    gui_msg_data_t *data = (gui_msg_data_t *)observer->user_data;
    if (data->value_bool) {
        lv_obj_clear_flag(obj, LV_OBJ_FLAG_HIDDEN);
    } else {
        lv_obj_add_flag(obj, LV_OBJ_FLAG_HIDDEN);
    }
}
void gui_msg_set_digital_clock_clock_time_by_time_cb(lv_observer_t *observer, lv_subject_t *subject)
{
    lv_obj_t *obj = lv_observer_get_target_obj(observer);
    if (obj == NULL || lv_obj_is_valid(obj) == false) {
        return;
    }

    gui_msg_data_t *data = (gui_msg_data_t *)observer->user_data;
}
void gui_msg_set_bar_bar_value_by_int32_cb(lv_observer_t *observer, lv_subject_t *subject)
{
    lv_obj_t *obj = lv_observer_get_target_obj(observer);
    if (obj == NULL || lv_obj_is_valid(obj) == false) {
        return;
    }

    gui_msg_data_t *data = (gui_msg_data_t *)observer->user_data;
    lv_bar_set_value(obj, data->value_int, LV_ANIM_OFF);
}

#endif
