#include "app_config.h"
#ifdef CONFIG_UI_STYLE_LY_ENABLE
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
    gui_model_video_dec_msg_init(ui);
    gui_model_video_photo_msg_init(ui);
    gui_model_video_rec_msg_init(ui);
    gui_speed_num_msg_init(ui);
    gui_sys_model_msg_init(ui);
    gui_tyw_system_msg_init(ui);
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
    gui_model_video_dec_msg_init_ui();
    gui_model_video_photo_msg_init_ui();
    gui_model_video_rec_msg_init_ui();
    gui_speed_num_msg_init_ui();
    gui_sys_model_msg_init_ui();
    gui_tyw_system_msg_init_ui();
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
    gui_model_video_dec_msg_init_events();
    gui_model_video_photo_msg_init_events();
    gui_model_video_rec_msg_init_events();
    gui_speed_num_msg_init_events();
    gui_sys_model_msg_init_events();
    gui_tyw_system_msg_init_events();
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
    gui_model_video_dec_msg_unsubscribe();
    gui_model_video_photo_msg_unsubscribe();
    gui_model_video_rec_msg_unsubscribe();
    gui_speed_num_msg_unsubscribe();
    gui_sys_model_msg_unsubscribe();
    gui_tyw_system_msg_unsubscribe();
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
    case GUI_MODEL_MSG_ID_MUSIC_STATE:
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
    case GUI_MODEL_GLOBAL_SUBPAGE_MSG_ID_STATE_FUNKEY4:
        ret = gui_model_global_subpage_msg_send(msg_id, value, len);
        gui_msg_send_status = GUI_MSG_SEND_DONE;
        return ret;

    case GUI_MODEL_MAIN_MSG_ID_SYSTIME:
    case GUI_MODEL_MAIN_MSG_ID_SD_ICON:
    case GUI_MODEL_MAIN_MSG_ID_BATTERY:
    case GUI_MODEL_MAIN_MSG_ID_SYS_PROMPT:
    case GUI_MODEL_MAIN_MSG_ID_HEADLAMP:
    case GUI_MODEL_MAIN_MSG_ID_SYS_PROMPT_SHOW:
    case GUI_MODEL_MAIN_MSG_ID_SHOW_DEL_BTN:
    case GUI_MODEL_MAIN_MSG_ID_HIDE_DEL_BTN:
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
    case GUI_MODEL_SYS_SETTING_MSG_ID_SUBPAGE_WARNING_STATE:
        ret = gui_model_sys_setting_msg_send(msg_id, value, len);
        gui_msg_send_status = GUI_MSG_SEND_DONE;
        return ret;

    case GUI_MODEL_UPDATE_MSG_ID_UPDATE_TIPS:
    case GUI_MODEL_UPDATE_MSG_ID_UPDATE_PROCE:
        ret = gui_model_update_msg_send(msg_id, value, len);
        gui_msg_send_status = GUI_MSG_SEND_DONE;
        return ret;

    case GUI_MODEL_VIDEO_DEC_MSG_ID_FILE_TYPE_IMG:
    case GUI_MODEL_VIDEO_DEC_MSG_ID_VIDEO_TIME_LAB:
    case GUI_MODEL_VIDEO_DEC_MSG_ID_FILE_NAME_LAB:
    case GUI_MODEL_VIDEO_DEC_MSG_ID_MEDIA_INFO_LAB:
    case GUI_MODEL_VIDEO_DEC_MSG_ID_SD_STATUS_IMG:
    case GUI_MODEL_VIDEO_DEC_MSG_ID_PLAY_STATUS_IMG:
    case GUI_MODEL_VIDEO_DEC_MSG_ID_VIDEO_CONT_SHOW:
    case GUI_MODEL_VIDEO_DEC_MSG_ID_FILE_LOCK_SHOW:
    case GUI_MODEL_VIDEO_DEC_MSG_ID_VIDEO_DEC_OPTIONS_LAB:
        ret = gui_model_video_dec_msg_send(msg_id, value, len);
        gui_msg_send_status = GUI_MSG_SEND_DONE;
        return ret;

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
    case GUI_MODEL_VIDEO_PHOTO_MSG_ID_PEXP_ICON:
    case GUI_MODEL_VIDEO_PHOTO_MSG_ID_ISO_ICON:
    case GUI_MODEL_VIDEO_PHOTO_MSG_ID_DELAY_SATE:
    case GUI_MODEL_VIDEO_PHOTO_MSG_ID_DELAY_ICON:
    case GUI_MODEL_VIDEO_PHOTO_MSG_ID_HANDSHAKE_ICON:
    case GUI_MODEL_VIDEO_PHOTO_MSG_ID_SHOTS_ICON:
    case GUI_MODEL_VIDEO_PHOTO_MSG_ID_PHOTO_RESO:
        ret = gui_model_video_photo_msg_send(msg_id, value, len);
        gui_msg_send_status = GUI_MSG_SEND_DONE;
        return ret;

    case GUI_MODEL_VIDEO_REC_MSG_ID_CYCREC_ICON:
    case GUI_MODEL_VIDEO_REC_MSG_ID_DELAYREC_ICON:
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
    case GUI_MODEL_VIDEO_REC_MSG_ID_VIDEO_REC_MENU:
    case GUI_MODEL_VIDEO_REC_MSG_ID_MIC_ICON:
    case GUI_MODEL_VIDEO_REC_MSG_ID_GSENSOR_ICON:
    case GUI_MODEL_VIDEO_REC_MSG_ID_SD_ICON:
    case GUI_MODEL_VIDEO_REC_MSG_ID_GUARD_STATE:
    case GUI_MODEL_VIDEO_REC_MSG_ID_CYC_STATE:
    case GUI_MODEL_VIDEO_REC_MSG_ID_MOTION_STATE:
    case GUI_MODEL_VIDEO_REC_MSG_ID_GAP_STATE:
    case GUI_MODEL_VIDEO_REC_MSG_ID_HDR_STATE:
    case GUI_MODEL_VIDEO_REC_MSG_ID_GRA_STATE:
    case GUI_MODEL_VIDEO_REC_MSG_ID_EXP_ICON:
    case GUI_MODEL_VIDEO_REC_MSG_ID_CAR_NUM:
    case GUI_MODEL_VIDEO_REC_MSG_ID_FLASH_HEADLIGHT:
    case GUI_MODEL_VIDEO_REC_MSG_ID_REC_ICON_STATE:
    case GUI_MODEL_VIDEO_REC_MSG_ID_KEY_STATE:
        ret = gui_model_video_rec_msg_send(msg_id, value, len);
        gui_msg_send_status = GUI_MSG_SEND_DONE;
        return ret;

    case GUI_SPEED_NUM_MSG_ID_PROP:
        ret = gui_speed_num_msg_send(msg_id, value, len);
        gui_msg_send_status = GUI_MSG_SEND_DONE;
        return ret;

    case GUI_SYS_MODEL_MSG_ID_SYS_TIME:
        ret = gui_sys_model_msg_send(msg_id, value, len);
        gui_msg_send_status = GUI_MSG_SEND_DONE;
        return ret;

    case GUI_TYW_SYSTEM_MSG_ID_BT_CONN:
    case GUI_TYW_SYSTEM_MSG_ID_BT_DISCONN:
    case GUI_TYW_SYSTEM_MSG_ID_PHONE_INCOME:
    case GUI_TYW_SYSTEM_MSG_ID_PHONE_HANGUP:
    case GUI_TYW_SYSTEM_MSG_ID_PHONE_NUMBER:
    case GUI_TYW_SYSTEM_MSG_ID_MUSIC_INFO:
        ret = gui_tyw_system_msg_send(msg_id, value, len);
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
#if !LV_USE_GUIBUILDER_SIMULATOR
    if (msg_id >= GUI_MSG_ID_CUSTOM_START && msg_id <= GUI_MSG_ID_CUSTOM_END) {
        int32_t index = msg_id - GUI_MSG_ID_CUSTOM_START;
        gui_msg_entry_table[index].cb(GUI_MSG_ACCESS_GET, &guider_msg_data, gui_msg_entry_table[index].type);
        return &guider_msg_data;
    } else {
        for (int i = GUI_MSG_ID_CUSTOM_END - GUI_MSG_ID_CUSTOM_START + 1; i < sizeof(gui_msg_entry_table) / sizeof(gui_msg_entry_table[0]); i++) {
            if (msg_id == gui_msg_entry_table[i].msg_id) {
                gui_msg_entry_table[i].cb(GUI_MSG_ACCESS_GET, &guider_msg_data, gui_msg_entry_table[i].type);
                return &guider_msg_data;
            }
        }
    }
    return NULL;
#else
    if (msg_id >= GUI_MODEL_MSG_ID_CUR_TIME && msg_id <= GUI_MODEL_MSG_ID_MUSIC_STATE) {
        int32_t index = msg_id - GUI_MODEL_MSG_ID_CUR_TIME;
        gui_model_msg_entry_table[index].cb(GUI_MSG_ACCESS_GET, &guider_msg_data, gui_model_msg_entry_table[index].type);
        return &guider_msg_data;
    } else if (msg_id >= GUI_MODEL_GLOBAL_SUBPAGE_MSG_ID_SUBPAGE_ICON && msg_id <= GUI_MODEL_GLOBAL_SUBPAGE_MSG_ID_STATE_FUNKEY4) {
        int32_t index = msg_id - GUI_MODEL_GLOBAL_SUBPAGE_MSG_ID_SUBPAGE_ICON;
        gui_model_global_subpage_msg_entry_table[index].cb(GUI_MSG_ACCESS_GET, &guider_msg_data, gui_model_global_subpage_msg_entry_table[index].type);
        return &guider_msg_data;
    } else if (msg_id >= GUI_MODEL_MAIN_MSG_ID_SYSTIME && msg_id <= GUI_MODEL_MAIN_MSG_ID_HIDE_HOME_BTN) {
        int32_t index = msg_id - GUI_MODEL_MAIN_MSG_ID_SYSTIME;
        gui_model_main_msg_entry_table[index].cb(GUI_MSG_ACCESS_GET, &guider_msg_data, gui_model_main_msg_entry_table[index].type);
        return &guider_msg_data;
    } else if (msg_id >= GUI_MODEL_SYS_SETTING_MSG_ID_FUNKEY4 && msg_id <= GUI_MODEL_SYS_SETTING_MSG_ID_SUBPAGE_WARNING_STATE) {
        int32_t index = msg_id - GUI_MODEL_SYS_SETTING_MSG_ID_FUNKEY4;
        gui_model_sys_setting_msg_entry_table[index].cb(GUI_MSG_ACCESS_GET, &guider_msg_data, gui_model_sys_setting_msg_entry_table[index].type);
        return &guider_msg_data;
    } else if (msg_id >= GUI_MODEL_UPDATE_MSG_ID_UPDATE_TIPS && msg_id <= GUI_MODEL_UPDATE_MSG_ID_UPDATE_PROCE) {
        int32_t index = msg_id - GUI_MODEL_UPDATE_MSG_ID_UPDATE_TIPS;
        gui_model_update_msg_entry_table[index].cb(GUI_MSG_ACCESS_GET, &guider_msg_data, gui_model_update_msg_entry_table[index].type);
        return &guider_msg_data;
    } else if (msg_id >= GUI_MODEL_VIDEO_DEC_MSG_ID_FILE_TYPE_IMG && msg_id <= GUI_MODEL_VIDEO_DEC_MSG_ID_VIDEO_DEC_OPTIONS_LAB) {
        int32_t index = msg_id - GUI_MODEL_VIDEO_DEC_MSG_ID_FILE_TYPE_IMG;
        gui_model_video_dec_msg_entry_table[index].cb(GUI_MSG_ACCESS_GET, &guider_msg_data, gui_model_video_dec_msg_entry_table[index].type);
        return &guider_msg_data;
    } else if (msg_id >= GUI_MODEL_VIDEO_PHOTO_MSG_ID_RESOLUTION_ICON && msg_id <= GUI_MODEL_VIDEO_PHOTO_MSG_ID_PHOTO_RESO) {
        int32_t index = msg_id - GUI_MODEL_VIDEO_PHOTO_MSG_ID_RESOLUTION_ICON;
        gui_model_video_photo_msg_entry_table[index].cb(GUI_MSG_ACCESS_GET, &guider_msg_data, gui_model_video_photo_msg_entry_table[index].type);
        return &guider_msg_data;
    } else if (msg_id >= GUI_MODEL_VIDEO_REC_MSG_ID_CYCREC_ICON && msg_id <= GUI_MODEL_VIDEO_REC_MSG_ID_KEY_STATE) {
        int32_t index = msg_id - GUI_MODEL_VIDEO_REC_MSG_ID_CYCREC_ICON;
        gui_model_video_rec_msg_entry_table[index].cb(GUI_MSG_ACCESS_GET, &guider_msg_data, gui_model_video_rec_msg_entry_table[index].type);
        return &guider_msg_data;
    } else if (msg_id >= GUI_SPEED_NUM_MSG_ID_PROP && msg_id <= GUI_SPEED_NUM_MSG_ID_PROP) {
        int32_t index = msg_id - GUI_SPEED_NUM_MSG_ID_PROP;
        gui_speed_num_msg_entry_table[index].cb(GUI_MSG_ACCESS_GET, &guider_msg_data, gui_speed_num_msg_entry_table[index].type);
        return &guider_msg_data;
    } else if (msg_id >= GUI_TYW_SYSTEM_MSG_ID_BT_CONN && msg_id <= GUI_TYW_SYSTEM_MSG_ID_MUSIC_INFO) {
        int32_t index = msg_id - GUI_TYW_SYSTEM_MSG_ID_BT_CONN;
        gui_tyw_system_msg_entry_table[index].cb(GUI_MSG_ACCESS_GET, &guider_msg_data, gui_tyw_system_msg_entry_table[index].type);
        return &guider_msg_data;
    } else {
        for (int i = 0; i < 1; i++) {
            if (msg_id == gui_sys_model_msg_entry_table[i].msg_id) {
                gui_sys_model_msg_entry_table[i].cb(GUI_MSG_ACCESS_GET, &guider_msg_data, gui_sys_model_msg_entry_table[i].type);
                return &guider_msg_data;
            }
        }
    }
    return NULL;
#endif
#endif
}
GUI_WEAK void gui_msg_action_change(int32_t msg_id, gui_msg_action_t access, gui_msg_data_t *data, gui_msg_data_type_t type)
{
    gui_msg_action_change_guider(msg_id, access, data, type);
}
void gui_msg_action_change_guider(int32_t msg_id, gui_msg_action_t access, gui_msg_data_t *data, gui_msg_data_type_t type)
{
#if LV_USE_OBSERVER
#if !LV_USE_GUIBUILDER_SIMULATOR
    if (msg_id >= GUI_MSG_ID_CUSTOM_START && msg_id <= GUI_MSG_ID_CUSTOM_END) {
        int32_t index = msg_id - GUI_MSG_ID_CUSTOM_START;
        gui_msg_entry_table[index].cb(access, data, type);
    } else {
        for (int i = GUI_MSG_ID_CUSTOM_END - GUI_MSG_ID_CUSTOM_START + 1; i < sizeof(gui_msg_entry_table) / sizeof(gui_msg_entry_table[0]); i++) {
            if (msg_id == gui_msg_entry_table[i].msg_id) {
                gui_msg_entry_table[i].cb(access, data, type);
                return;
            }
        }
    }
#else
    if (msg_id >= GUI_MODEL_MSG_ID_CUR_TIME && msg_id <= GUI_MODEL_MSG_ID_MUSIC_STATE) {
        int32_t index = msg_id - GUI_MODEL_MSG_ID_CUR_TIME;
        gui_model_msg_entry_table[index].cb(access, data, type);
    } else if (msg_id >= GUI_MODEL_GLOBAL_SUBPAGE_MSG_ID_SUBPAGE_ICON && msg_id <= GUI_MODEL_GLOBAL_SUBPAGE_MSG_ID_STATE_FUNKEY4) {
        int32_t index = msg_id - GUI_MODEL_GLOBAL_SUBPAGE_MSG_ID_SUBPAGE_ICON;
        gui_model_global_subpage_msg_entry_table[index].cb(access, data, type);
    } else if (msg_id >= GUI_MODEL_MAIN_MSG_ID_SYSTIME && msg_id <= GUI_MODEL_MAIN_MSG_ID_HIDE_HOME_BTN) {
        int32_t index = msg_id - GUI_MODEL_MAIN_MSG_ID_SYSTIME;
        gui_model_main_msg_entry_table[index].cb(access, data, type);
    } else if (msg_id >= GUI_MODEL_SYS_SETTING_MSG_ID_FUNKEY4 && msg_id <= GUI_MODEL_SYS_SETTING_MSG_ID_SUBPAGE_WARNING_STATE) {
        int32_t index = msg_id - GUI_MODEL_SYS_SETTING_MSG_ID_FUNKEY4;
        gui_model_sys_setting_msg_entry_table[index].cb(access, data, type);
    } else if (msg_id >= GUI_MODEL_UPDATE_MSG_ID_UPDATE_TIPS && msg_id <= GUI_MODEL_UPDATE_MSG_ID_UPDATE_PROCE) {
        int32_t index = msg_id - GUI_MODEL_UPDATE_MSG_ID_UPDATE_TIPS;
        gui_model_update_msg_entry_table[index].cb(access, data, type);
    } else if (msg_id >= GUI_MODEL_VIDEO_DEC_MSG_ID_FILE_TYPE_IMG && msg_id <= GUI_MODEL_VIDEO_DEC_MSG_ID_VIDEO_DEC_OPTIONS_LAB) {
        int32_t index = msg_id - GUI_MODEL_VIDEO_DEC_MSG_ID_FILE_TYPE_IMG;
        gui_model_video_dec_msg_entry_table[index].cb(access, data, type);
    } else if (msg_id >= GUI_MODEL_VIDEO_PHOTO_MSG_ID_RESOLUTION_ICON && msg_id <= GUI_MODEL_VIDEO_PHOTO_MSG_ID_PHOTO_RESO) {
        int32_t index = msg_id - GUI_MODEL_VIDEO_PHOTO_MSG_ID_RESOLUTION_ICON;
        gui_model_video_photo_msg_entry_table[index].cb(access, data, type);
    } else if (msg_id >= GUI_MODEL_VIDEO_REC_MSG_ID_CYCREC_ICON && msg_id <= GUI_MODEL_VIDEO_REC_MSG_ID_KEY_STATE) {
        int32_t index = msg_id - GUI_MODEL_VIDEO_REC_MSG_ID_CYCREC_ICON;
        gui_model_video_rec_msg_entry_table[index].cb(access, data, type);
    } else if (msg_id >= GUI_SPEED_NUM_MSG_ID_PROP && msg_id <= GUI_SPEED_NUM_MSG_ID_PROP) {
        int32_t index = msg_id - GUI_SPEED_NUM_MSG_ID_PROP;
        gui_speed_num_msg_entry_table[index].cb(access, data, type);
    } else if (msg_id >= GUI_TYW_SYSTEM_MSG_ID_BT_CONN && msg_id <= GUI_TYW_SYSTEM_MSG_ID_MUSIC_INFO) {
        int32_t index = msg_id - GUI_TYW_SYSTEM_MSG_ID_BT_CONN;
        gui_tyw_system_msg_entry_table[index].cb(access, data, type);
    } else {
        for (int i = 0; i < 1; i++) {
            if (msg_id == gui_sys_model_msg_entry_table[i].msg_id) {
                gui_sys_model_msg_entry_table[i].cb(access, data, type);
                return;
            }
        }
    }
#endif
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
        if (sub->subject == NULL) {
            return NULL;
        }
    }
    return sub;
}
gui_msg_data_t *gui_msg_get_data()
{
    return &guider_msg_data;
}
char *gui_msg_get_name(int32_t msg_id)
{
    switch (msg_id) {
    case GUI_MODEL_MSG_ID:
        return "MODEL";
    case GUI_MODEL_MSG_ID_CUR_TIME:
        return "MODEL_CUR_TIME";
    case GUI_MODEL_MSG_ID_PREV_FILE:
        return "MODEL_PREV_FILE";
    case GUI_MODEL_MSG_ID_NEXT_FILE:
        return "MODEL_NEXT_FILE";
    case GUI_MODEL_MSG_ID_VIDEO_PAUSE:
        return "MODEL_VIDEO_PAUSE";
    case GUI_MODEL_MSG_ID_CUR_TIME_PROCESS:
        return "MODEL_CUR_TIME_PROCESS";
    case GUI_MODEL_MSG_ID_FILE_NAME:
        return "MODEL_FILE_NAME";
    case GUI_MODEL_MSG_ID_TOTAL_TIME:
        return "MODEL_TOTAL_TIME";
    case GUI_MODEL_MSG_ID_FILE_PATH:
        return "MODEL_FILE_PATH";
    case GUI_MODEL_MSG_ID_FILE_NUM:
        return "MODEL_FILE_NUM";
    case GUI_MODEL_MSG_ID_MUSIC_STATE:
        return "MODEL_MUSIC_STATE";

    case GUI_MODEL_GLOBAL_SUBPAGE_MSG_ID:
        return "MODEL_GLOBAL_SUBPAGE";
    case GUI_MODEL_GLOBAL_SUBPAGE_MSG_ID_SUBPAGE_ICON:
        return "MODEL_GLOBAL_SUBPAGE_SUBPAGE_ICON";
    case GUI_MODEL_GLOBAL_SUBPAGE_MSG_ID_FUNCKEY1:
        return "MODEL_GLOBAL_SUBPAGE_FUNCKEY1";
    case GUI_MODEL_GLOBAL_SUBPAGE_MSG_ID_FUNCKEY2:
        return "MODEL_GLOBAL_SUBPAGE_FUNCKEY2";
    case GUI_MODEL_GLOBAL_SUBPAGE_MSG_ID_FUNCKEY3:
        return "MODEL_GLOBAL_SUBPAGE_FUNCKEY3";
    case GUI_MODEL_GLOBAL_SUBPAGE_MSG_ID_FUNCKEY4:
        return "MODEL_GLOBAL_SUBPAGE_FUNCKEY4";
    case GUI_MODEL_GLOBAL_SUBPAGE_MSG_ID_TITLE:
        return "MODEL_GLOBAL_SUBPAGE_TITLE";
    case GUI_MODEL_GLOBAL_SUBPAGE_MSG_ID_HIDE_FUNCKEY1:
        return "MODEL_GLOBAL_SUBPAGE_HIDE_FUNCKEY1";
    case GUI_MODEL_GLOBAL_SUBPAGE_MSG_ID_HIDE_FUNCKEY2:
        return "MODEL_GLOBAL_SUBPAGE_HIDE_FUNCKEY2";
    case GUI_MODEL_GLOBAL_SUBPAGE_MSG_ID_HIDE_FUNCKEY3:
        return "MODEL_GLOBAL_SUBPAGE_HIDE_FUNCKEY3";
    case GUI_MODEL_GLOBAL_SUBPAGE_MSG_ID_HIDE_FUNCKEY4:
        return "MODEL_GLOBAL_SUBPAGE_HIDE_FUNCKEY4";
    case GUI_MODEL_GLOBAL_SUBPAGE_MSG_ID_SHOW_FUNCKEY1:
        return "MODEL_GLOBAL_SUBPAGE_SHOW_FUNCKEY1";
    case GUI_MODEL_GLOBAL_SUBPAGE_MSG_ID_SHOW_FUNCKEY2:
        return "MODEL_GLOBAL_SUBPAGE_SHOW_FUNCKEY2";
    case GUI_MODEL_GLOBAL_SUBPAGE_MSG_ID_SHOW_FUNCKEY3:
        return "MODEL_GLOBAL_SUBPAGE_SHOW_FUNCKEY3";
    case GUI_MODEL_GLOBAL_SUBPAGE_MSG_ID_SHOW_FUNCKEY4:
        return "MODEL_GLOBAL_SUBPAGE_SHOW_FUNCKEY4";
    case GUI_MODEL_GLOBAL_SUBPAGE_MSG_ID_ROLLER_OPT:
        return "MODEL_GLOBAL_SUBPAGE_ROLLER_OPT";
    case GUI_MODEL_GLOBAL_SUBPAGE_MSG_ID_SHOW_ROLLER:
        return "MODEL_GLOBAL_SUBPAGE_SHOW_ROLLER";
    case GUI_MODEL_GLOBAL_SUBPAGE_MSG_ID_HIDE_ROLLER:
        return "MODEL_GLOBAL_SUBPAGE_HIDE_ROLLER";
    case GUI_MODEL_GLOBAL_SUBPAGE_MSG_ID_STATE_FUNKEY1:
        return "MODEL_GLOBAL_SUBPAGE_STATE_FUNKEY1";
    case GUI_MODEL_GLOBAL_SUBPAGE_MSG_ID_STATE_FUNKEY2:
        return "MODEL_GLOBAL_SUBPAGE_STATE_FUNKEY2";
    case GUI_MODEL_GLOBAL_SUBPAGE_MSG_ID_STATE_FUNKEY3:
        return "MODEL_GLOBAL_SUBPAGE_STATE_FUNKEY3";
    case GUI_MODEL_GLOBAL_SUBPAGE_MSG_ID_STATE_FUNKEY4:
        return "MODEL_GLOBAL_SUBPAGE_STATE_FUNKEY4";

    case GUI_MODEL_MAIN_MSG_ID:
        return "MODEL_MAIN";
    case GUI_MODEL_MAIN_MSG_ID_SYSTIME:
        return "MODEL_MAIN_SYSTIME";
    case GUI_MODEL_MAIN_MSG_ID_SD_ICON:
        return "MODEL_MAIN_SD_ICON";
    case GUI_MODEL_MAIN_MSG_ID_BATTERY:
        return "MODEL_MAIN_BATTERY";
    case GUI_MODEL_MAIN_MSG_ID_SYS_PROMPT:
        return "MODEL_MAIN_SYS_PROMPT";
    case GUI_MODEL_MAIN_MSG_ID_HEADLAMP:
        return "MODEL_MAIN_HEADLAMP";
    case GUI_MODEL_MAIN_MSG_ID_SYS_PROMPT_SHOW:
        return "MODEL_MAIN_SYS_PROMPT_SHOW";
    case GUI_MODEL_MAIN_MSG_ID_SHOW_DEL_BTN:
        return "MODEL_MAIN_SHOW_DEL_BTN";
    case GUI_MODEL_MAIN_MSG_ID_HIDE_DEL_BTN:
        return "MODEL_MAIN_HIDE_DEL_BTN";
    case GUI_MODEL_MAIN_MSG_ID_SHOW_HOME_BTN:
        return "MODEL_MAIN_SHOW_HOME_BTN";
    case GUI_MODEL_MAIN_MSG_ID_HIDE_HOME_BTN:
        return "MODEL_MAIN_HIDE_HOME_BTN";

    case GUI_MODEL_SYS_SETTING_MSG_ID:
        return "MODEL_SYS_SETTING";
    case GUI_MODEL_SYS_SETTING_MSG_ID_FUNKEY4:
        return "MODEL_SYS_SETTING_FUNKEY4";
    case GUI_MODEL_SYS_SETTING_MSG_ID_FUNKEY5:
        return "MODEL_SYS_SETTING_FUNKEY5";
    case GUI_MODEL_SYS_SETTING_MSG_ID_FUNKEY6:
        return "MODEL_SYS_SETTING_FUNKEY6";
    case GUI_MODEL_SYS_SETTING_MSG_ID_FUNKEY7:
        return "MODEL_SYS_SETTING_FUNKEY7";
    case GUI_MODEL_SYS_SETTING_MSG_ID_SUBPAGE_WARNING:
        return "MODEL_SYS_SETTING_SUBPAGE_WARNING";
    case GUI_MODEL_SYS_SETTING_MSG_ID_HIDE_VIEWDATE:
        return "MODEL_SYS_SETTING_HIDE_VIEWDATE";
    case GUI_MODEL_SYS_SETTING_MSG_ID_HIDE_VIEWCARNUM:
        return "MODEL_SYS_SETTING_HIDE_VIEWCARNUM";
    case GUI_MODEL_SYS_SETTING_MSG_ID_HIDE_VIEWLIST:
        return "MODEL_SYS_SETTING_HIDE_VIEWLIST";
    case GUI_MODEL_SYS_SETTING_MSG_ID_HIDE_SUBPAGEWARNING:
        return "MODEL_SYS_SETTING_HIDE_SUBPAGEWARNING";
    case GUI_MODEL_SYS_SETTING_MSG_ID_SHOW_VIEWDATE:
        return "MODEL_SYS_SETTING_SHOW_VIEWDATE";
    case GUI_MODEL_SYS_SETTING_MSG_ID_SHOW_VIEWCARNUM:
        return "MODEL_SYS_SETTING_SHOW_VIEWCARNUM";
    case GUI_MODEL_SYS_SETTING_MSG_ID_SHOW_VIEWLIST:
        return "MODEL_SYS_SETTING_SHOW_VIEWLIST";
    case GUI_MODEL_SYS_SETTING_MSG_ID_SHOW_SUBPAGEWARNING:
        return "MODEL_SYS_SETTING_SHOW_SUBPAGEWARNING";
    case GUI_MODEL_SYS_SETTING_MSG_ID_HIDE_FUNKEY5:
        return "MODEL_SYS_SETTING_HIDE_FUNKEY5";
    case GUI_MODEL_SYS_SETTING_MSG_ID_HIDE_FUNKEY6:
        return "MODEL_SYS_SETTING_HIDE_FUNKEY6";
    case GUI_MODEL_SYS_SETTING_MSG_ID_HIDE_FUNKEY7:
        return "MODEL_SYS_SETTING_HIDE_FUNKEY7";
    case GUI_MODEL_SYS_SETTING_MSG_ID_SHOW_FUNKEY4:
        return "MODEL_SYS_SETTING_SHOW_FUNKEY4";
    case GUI_MODEL_SYS_SETTING_MSG_ID_SHOW_FUNKEY5:
        return "MODEL_SYS_SETTING_SHOW_FUNKEY5";
    case GUI_MODEL_SYS_SETTING_MSG_ID_SHOW_FUNKEY6:
        return "MODEL_SYS_SETTING_SHOW_FUNKEY6";
    case GUI_MODEL_SYS_SETTING_MSG_ID_SHOW_FUNKEY7:
        return "MODEL_SYS_SETTING_SHOW_FUNKEY7";
    case GUI_MODEL_SYS_SETTING_MSG_ID_STATE_FUNKEY4:
        return "MODEL_SYS_SETTING_STATE_FUNKEY4";
    case GUI_MODEL_SYS_SETTING_MSG_ID_STATE_FUNKEY5:
        return "MODEL_SYS_SETTING_STATE_FUNKEY5";
    case GUI_MODEL_SYS_SETTING_MSG_ID_STATE_FUNKEY6:
        return "MODEL_SYS_SETTING_STATE_FUNKEY6";
    case GUI_MODEL_SYS_SETTING_MSG_ID_STATE_FUNKEY7:
        return "MODEL_SYS_SETTING_STATE_FUNKEY7";
    case GUI_MODEL_SYS_SETTING_MSG_ID_HIDE_FUNKEY4:
        return "MODEL_SYS_SETTING_HIDE_FUNKEY4";
    case GUI_MODEL_SYS_SETTING_MSG_ID_SUBPAGE_WARNING_STATE:
        return "MODEL_SYS_SETTING_SUBPAGE_WARNING_STATE";

    case GUI_MODEL_UPDATE_MSG_ID:
        return "MODEL_UPDATE";
    case GUI_MODEL_UPDATE_MSG_ID_UPDATE_TIPS:
        return "MODEL_UPDATE_UPDATE_TIPS";
    case GUI_MODEL_UPDATE_MSG_ID_UPDATE_PROCE:
        return "MODEL_UPDATE_UPDATE_PROCE";

    case GUI_MODEL_VIDEO_DEC_MSG_ID:
        return "MODEL_VIDEO_DEC";
    case GUI_MODEL_VIDEO_DEC_MSG_ID_FILE_TYPE_IMG:
        return "MODEL_VIDEO_DEC_FILE_TYPE_IMG";
    case GUI_MODEL_VIDEO_DEC_MSG_ID_VIDEO_TIME_LAB:
        return "MODEL_VIDEO_DEC_VIDEO_TIME_LAB";
    case GUI_MODEL_VIDEO_DEC_MSG_ID_FILE_NAME_LAB:
        return "MODEL_VIDEO_DEC_FILE_NAME_LAB";
    case GUI_MODEL_VIDEO_DEC_MSG_ID_MEDIA_INFO_LAB:
        return "MODEL_VIDEO_DEC_MEDIA_INFO_LAB";
    case GUI_MODEL_VIDEO_DEC_MSG_ID_SD_STATUS_IMG:
        return "MODEL_VIDEO_DEC_SD_STATUS_IMG";
    case GUI_MODEL_VIDEO_DEC_MSG_ID_PLAY_STATUS_IMG:
        return "MODEL_VIDEO_DEC_PLAY_STATUS_IMG";
    case GUI_MODEL_VIDEO_DEC_MSG_ID_VIDEO_CONT_SHOW:
        return "MODEL_VIDEO_DEC_VIDEO_CONT_SHOW";
    case GUI_MODEL_VIDEO_DEC_MSG_ID_FILE_LOCK_SHOW:
        return "MODEL_VIDEO_DEC_FILE_LOCK_SHOW";
    case GUI_MODEL_VIDEO_DEC_MSG_ID_VIDEO_DEC_OPTIONS_LAB:
        return "MODEL_VIDEO_DEC_VIDEO_DEC_OPTIONS_LAB";

    case GUI_MODEL_VIDEO_PHOTO_MSG_ID:
        return "MODEL_VIDEO_PHOTO";
    case GUI_MODEL_VIDEO_PHOTO_MSG_ID_RESOLUTION_ICON:
        return "MODEL_VIDEO_PHOTO_RESOLUTION_ICON";
    case GUI_MODEL_VIDEO_PHOTO_MSG_ID_AWB_ICON:
        return "MODEL_VIDEO_PHOTO_AWB_ICON";
    case GUI_MODEL_VIDEO_PHOTO_MSG_ID_QUALITY_ICON:
        return "MODEL_VIDEO_PHOTO_QUALITY_ICON";
    case GUI_MODEL_VIDEO_PHOTO_MSG_ID_SHOT_MODE_ICON:
        return "MODEL_VIDEO_PHOTO_SHOT_MODE_ICON";
    case GUI_MODEL_VIDEO_PHOTO_MSG_ID_SHOW_HANDSHAKE:
        return "MODEL_VIDEO_PHOTO_SHOW_HANDSHAKE";
    case GUI_MODEL_VIDEO_PHOTO_MSG_ID_HIDE_HANDSHAKE:
        return "MODEL_VIDEO_PHOTO_HIDE_HANDSHAKE";
    case GUI_MODEL_VIDEO_PHOTO_MSG_ID_SHOW_SHOTS:
        return "MODEL_VIDEO_PHOTO_SHOW_SHOTS";
    case GUI_MODEL_VIDEO_PHOTO_MSG_ID_HIDE_SHOTS:
        return "MODEL_VIDEO_PHOTO_HIDE_SHOTS";
    case GUI_MODEL_VIDEO_PHOTO_MSG_ID_SHOW_SHOTS_MODE:
        return "MODEL_VIDEO_PHOTO_SHOW_SHOTS_MODE";
    case GUI_MODEL_VIDEO_PHOTO_MSG_ID_HIDE_SHOTS_MODE:
        return "MODEL_VIDEO_PHOTO_HIDE_SHOTS_MODE";
    case GUI_MODEL_VIDEO_PHOTO_MSG_ID_PHOTO_REMAIN:
        return "MODEL_VIDEO_PHOTO_PHOTO_REMAIN";
    case GUI_MODEL_VIDEO_PHOTO_MSG_ID_PEXP_ICON:
        return "MODEL_VIDEO_PHOTO_PEXP_ICON";
    case GUI_MODEL_VIDEO_PHOTO_MSG_ID_ISO_ICON:
        return "MODEL_VIDEO_PHOTO_ISO_ICON";
    case GUI_MODEL_VIDEO_PHOTO_MSG_ID_DELAY_SATE:
        return "MODEL_VIDEO_PHOTO_DELAY_SATE";
    case GUI_MODEL_VIDEO_PHOTO_MSG_ID_DELAY_ICON:
        return "MODEL_VIDEO_PHOTO_DELAY_ICON";
    case GUI_MODEL_VIDEO_PHOTO_MSG_ID_HANDSHAKE_ICON:
        return "MODEL_VIDEO_PHOTO_HANDSHAKE_ICON";
    case GUI_MODEL_VIDEO_PHOTO_MSG_ID_SHOTS_ICON:
        return "MODEL_VIDEO_PHOTO_SHOTS_ICON";
    case GUI_MODEL_VIDEO_PHOTO_MSG_ID_PHOTO_RESO:
        return "MODEL_VIDEO_PHOTO_PHOTO_RESO";

    case GUI_MODEL_VIDEO_REC_MSG_ID:
        return "MODEL_VIDEO_REC";
    case GUI_MODEL_VIDEO_REC_MSG_ID_CYCREC_ICON:
        return "MODEL_VIDEO_REC_CYCREC_ICON";
    case GUI_MODEL_VIDEO_REC_MSG_ID_DELAYREC_ICON:
        return "MODEL_VIDEO_REC_DELAYREC_ICON";
    case GUI_MODEL_VIDEO_REC_MSG_ID_CAR_NUNBER:
        return "MODEL_VIDEO_REC_CAR_NUNBER";
    case GUI_MODEL_VIDEO_REC_MSG_ID_REC_RESO:
        return "MODEL_VIDEO_REC_REC_RESO";
    case GUI_MODEL_VIDEO_REC_MSG_ID_REC_BTN:
        return "MODEL_VIDEO_REC_REC_BTN";
    case GUI_MODEL_VIDEO_REC_MSG_ID_SHOW_GSENSOR_ICON:
        return "MODEL_VIDEO_REC_SHOW_GSENSOR_ICON";
    case GUI_MODEL_VIDEO_REC_MSG_ID_HIDE_GSENSOR_ICON:
        return "MODEL_VIDEO_REC_HIDE_GSENSOR_ICON";
    case GUI_MODEL_VIDEO_REC_MSG_ID_SHOW_GUARD_ICON:
        return "MODEL_VIDEO_REC_SHOW_GUARD_ICON";
    case GUI_MODEL_VIDEO_REC_MSG_ID_HIDE_GUARD_ICON:
        return "MODEL_VIDEO_REC_HIDE_GUARD_ICON";
    case GUI_MODEL_VIDEO_REC_MSG_ID_SHOW_MOTION_ICON:
        return "MODEL_VIDEO_REC_SHOW_MOTION_ICON";
    case GUI_MODEL_VIDEO_REC_MSG_ID_HIDE_MOTION_ICON:
        return "MODEL_VIDEO_REC_HIDE_MOTION_ICON";
    case GUI_MODEL_VIDEO_REC_MSG_ID_SHOW_HDR_ICON:
        return "MODEL_VIDEO_REC_SHOW_HDR_ICON";
    case GUI_MODEL_VIDEO_REC_MSG_ID_HIDE_HDR_ICON:
        return "MODEL_VIDEO_REC_HIDE_HDR_ICON";
    case GUI_MODEL_VIDEO_REC_MSG_ID_REC_REMAIN_TIME:
        return "MODEL_VIDEO_REC_REC_REMAIN_TIME";
    case GUI_MODEL_VIDEO_REC_MSG_ID_REC_TIME_STATE:
        return "MODEL_VIDEO_REC_REC_TIME_STATE";
    case GUI_MODEL_VIDEO_REC_MSG_ID_VIDEO_REC_MENU:
        return "MODEL_VIDEO_REC_VIDEO_REC_MENU";
    case GUI_MODEL_VIDEO_REC_MSG_ID_MIC_ICON:
        return "MODEL_VIDEO_REC_MIC_ICON";
    case GUI_MODEL_VIDEO_REC_MSG_ID_GSENSOR_ICON:
        return "MODEL_VIDEO_REC_GSENSOR_ICON";
    case GUI_MODEL_VIDEO_REC_MSG_ID_SD_ICON:
        return "MODEL_VIDEO_REC_SD_ICON";
    case GUI_MODEL_VIDEO_REC_MSG_ID_GUARD_STATE:
        return "MODEL_VIDEO_REC_GUARD_STATE";
    case GUI_MODEL_VIDEO_REC_MSG_ID_CYC_STATE:
        return "MODEL_VIDEO_REC_CYC_STATE";
    case GUI_MODEL_VIDEO_REC_MSG_ID_MOTION_STATE:
        return "MODEL_VIDEO_REC_MOTION_STATE";
    case GUI_MODEL_VIDEO_REC_MSG_ID_GAP_STATE:
        return "MODEL_VIDEO_REC_GAP_STATE";
    case GUI_MODEL_VIDEO_REC_MSG_ID_HDR_STATE:
        return "MODEL_VIDEO_REC_HDR_STATE";
    case GUI_MODEL_VIDEO_REC_MSG_ID_GRA_STATE:
        return "MODEL_VIDEO_REC_GRA_STATE";
    case GUI_MODEL_VIDEO_REC_MSG_ID_EXP_ICON:
        return "MODEL_VIDEO_REC_EXP_ICON";
    case GUI_MODEL_VIDEO_REC_MSG_ID_CAR_NUM:
        return "MODEL_VIDEO_REC_CAR_NUM";
    case GUI_MODEL_VIDEO_REC_MSG_ID_FLASH_HEADLIGHT:
        return "MODEL_VIDEO_REC_FLASH_HEADLIGHT";
    case GUI_MODEL_VIDEO_REC_MSG_ID_REC_ICON_STATE:
        return "MODEL_VIDEO_REC_REC_ICON_STATE";
    case GUI_MODEL_VIDEO_REC_MSG_ID_KEY_STATE:
        return "MODEL_VIDEO_REC_KEY_STATE";

    case GUI_SPEED_NUM_MSG_ID:
        return "SPEED_NUM";
    case GUI_SPEED_NUM_MSG_ID_PROP:
        return "SPEED_NUM_PROP";

    case GUI_SYS_MODEL_MSG_ID:
        return "SYS_MODEL";
    case GUI_SYS_MODEL_MSG_ID_SYS_TIME:
        return "SYS_MODEL_SYS_TIME";

    case GUI_TYW_SYSTEM_MSG_ID:
        return "TYW_SYSTEM";
    case GUI_TYW_SYSTEM_MSG_ID_BT_CONN:
        return "TYW_SYSTEM_BT_CONN";
    case GUI_TYW_SYSTEM_MSG_ID_BT_DISCONN:
        return "TYW_SYSTEM_BT_DISCONN";
    case GUI_TYW_SYSTEM_MSG_ID_PHONE_INCOME:
        return "TYW_SYSTEM_PHONE_INCOME";
    case GUI_TYW_SYSTEM_MSG_ID_PHONE_HANGUP:
        return "TYW_SYSTEM_PHONE_HANGUP";
    case GUI_TYW_SYSTEM_MSG_ID_PHONE_NUMBER:
        return "TYW_SYSTEM_PHONE_NUMBER";
    case GUI_TYW_SYSTEM_MSG_ID_MUSIC_INFO:
        return "TYW_SYSTEM_MUSIC_INFO";

    default:
        break;
    }
    return NULL;
}
gui_msg_data_type_t gui_msg_get_data_type(int32_t msg_id)
{
#if !LV_USE_GUIBUILDER_SIMULATOR
    if (msg_id >= GUI_MSG_ID_CUSTOM_START && msg_id <= GUI_MSG_ID_CUSTOM_END) {
        return gui_msg_entry_table[msg_id - GUI_MSG_ID_CUSTOM_START].type;
    } else {
        for (int i = GUI_MSG_ID_CUSTOM_END - GUI_MSG_ID_CUSTOM_START + 1; i < sizeof(gui_msg_entry_table) / sizeof(gui_msg_entry_table[0]); i++) {
            if (msg_id == gui_msg_entry_table[i].msg_id) {
                return gui_msg_entry_table[i].type;
            }
        }
    }
    return VALUE_UNKNOWN;
#else
    if (msg_id >= GUI_MODEL_MSG_ID_CUR_TIME && msg_id <= GUI_MODEL_MSG_ID_MUSIC_STATE) {
        return gui_model_msg_entry_table[msg_id - GUI_MODEL_MSG_ID_CUR_TIME].type;
    } else if (msg_id >= GUI_MODEL_GLOBAL_SUBPAGE_MSG_ID_SUBPAGE_ICON && msg_id <= GUI_MODEL_GLOBAL_SUBPAGE_MSG_ID_STATE_FUNKEY4) {
        return gui_model_global_subpage_msg_entry_table[msg_id - GUI_MODEL_GLOBAL_SUBPAGE_MSG_ID_SUBPAGE_ICON].type;
    } else if (msg_id >= GUI_MODEL_MAIN_MSG_ID_SYSTIME && msg_id <= GUI_MODEL_MAIN_MSG_ID_HIDE_HOME_BTN) {
        return gui_model_main_msg_entry_table[msg_id - GUI_MODEL_MAIN_MSG_ID_SYSTIME].type;
    } else if (msg_id >= GUI_MODEL_SYS_SETTING_MSG_ID_FUNKEY4 && msg_id <= GUI_MODEL_SYS_SETTING_MSG_ID_SUBPAGE_WARNING_STATE) {
        return gui_model_sys_setting_msg_entry_table[msg_id - GUI_MODEL_SYS_SETTING_MSG_ID_FUNKEY4].type;
    } else if (msg_id >= GUI_MODEL_UPDATE_MSG_ID_UPDATE_TIPS && msg_id <= GUI_MODEL_UPDATE_MSG_ID_UPDATE_PROCE) {
        return gui_model_update_msg_entry_table[msg_id - GUI_MODEL_UPDATE_MSG_ID_UPDATE_TIPS].type;
    } else if (msg_id >= GUI_MODEL_VIDEO_DEC_MSG_ID_FILE_TYPE_IMG && msg_id <= GUI_MODEL_VIDEO_DEC_MSG_ID_VIDEO_DEC_OPTIONS_LAB) {
        return gui_model_video_dec_msg_entry_table[msg_id - GUI_MODEL_VIDEO_DEC_MSG_ID_FILE_TYPE_IMG].type;
    } else if (msg_id >= GUI_MODEL_VIDEO_PHOTO_MSG_ID_RESOLUTION_ICON && msg_id <= GUI_MODEL_VIDEO_PHOTO_MSG_ID_PHOTO_RESO) {
        return gui_model_video_photo_msg_entry_table[msg_id - GUI_MODEL_VIDEO_PHOTO_MSG_ID_RESOLUTION_ICON].type;
    } else if (msg_id >= GUI_MODEL_VIDEO_REC_MSG_ID_CYCREC_ICON && msg_id <= GUI_MODEL_VIDEO_REC_MSG_ID_KEY_STATE) {
        return gui_model_video_rec_msg_entry_table[msg_id - GUI_MODEL_VIDEO_REC_MSG_ID_CYCREC_ICON].type;
    } else if (msg_id >= GUI_SPEED_NUM_MSG_ID_PROP && msg_id <= GUI_SPEED_NUM_MSG_ID_PROP) {
        return gui_speed_num_msg_entry_table[msg_id - GUI_SPEED_NUM_MSG_ID_PROP].type;
    } else if (msg_id >= GUI_TYW_SYSTEM_MSG_ID_BT_CONN && msg_id <= GUI_TYW_SYSTEM_MSG_ID_MUSIC_INFO) {
        return gui_tyw_system_msg_entry_table[msg_id - GUI_TYW_SYSTEM_MSG_ID_BT_CONN].type;
    } else {
        for (int i = 0; i < 1; i++) {
            if (msg_id == gui_sys_model_msg_entry_table[i].msg_id) {
                return gui_sys_model_msg_entry_table[i].type;
            }
        }
    }
    return VALUE_UNKNOWN;
#endif
}
gui_msg_array_type_t gui_msg_get_data_array_type(int32_t msg_id)
{
    switch (msg_id) {
    default:
        return GUI_MSG_ARRAY_TYPE_INVALID;
    }
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
void gui_msg_set_label_text_by_string_cb(lv_observer_t *observer, lv_subject_t *subject)
{
    lv_obj_t *obj = lv_observer_get_target_obj(observer);
    if (obj == NULL || lv_obj_is_valid(obj) == false) {
        return;
    }

    gui_msg_data_t *data = (gui_msg_data_t *)observer->user_data;
    lv_label_set_text(obj, data->value_string);
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
void gui_msg_set_roller_roller_name_by_string_cb(lv_observer_t *observer, lv_subject_t *subject)
{
    lv_obj_t *obj = lv_observer_get_target_obj(observer);
    if (obj == NULL || lv_obj_is_valid(obj) == false) {
        return;
    }

    gui_msg_data_t *data = (gui_msg_data_t *)observer->user_data;
    lv_roller_set_options(obj, (const char *)data->value_string, ((lv_roller_t *)obj)->mode);
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
void gui_msg_set_imglist_selected_index_by_int32_cb(lv_observer_t *observer, lv_subject_t *subject)
{
    lv_obj_t *obj = lv_observer_get_target_obj(observer);
    if (obj == NULL || lv_obj_is_valid(obj) == false) {
        return;
    }

    gui_msg_data_t *data = (gui_msg_data_t *)observer->user_data;
    lv_imglist_set_act(obj, data->value_int);
}
void gui_msg_set_textarea_text_by_string_cb(lv_observer_t *observer, lv_subject_t *subject)
{
    lv_obj_t *obj = lv_observer_get_target_obj(observer);
    if (obj == NULL || lv_obj_is_valid(obj) == false) {
        return;
    }

    gui_msg_data_t *data = (gui_msg_data_t *)observer->user_data;
    const char *old_text = lv_textarea_get_text(obj);
    if (strcmp(old_text, data->value_string) != 0) {
        lv_textarea_set_text(obj, data->value_string);
    }
}
void gui_msg_change_textarea_text_cb(lv_event_t *e)
{
    lv_obj_t *obj = lv_event_get_target(e);
    if (obj == NULL || lv_obj_is_valid(obj) == false) {
        return;
    }

    int32_t msg_id = (int32_t)lv_event_get_user_data(e);
    char *var = (char *)lv_textarea_get_text(obj);
    gui_msg_send(msg_id, var, 1);
}
void _gui_msg_char_array_cb(char **var_ptr, const char *init_value, bool *is_init, gui_msg_action_t access, gui_msg_data_t *data)
{
    if (*is_init == false) {
        *var_ptr = lv_mem_alloc(strlen(init_value) + 1);
        if (*var_ptr == NULL) {
            return;
        }
        strcpy(*var_ptr, init_value);
        *is_init = true;
    }
    if (access == GUI_MSG_ACCESS_SET) {
        lv_mem_free(*var_ptr);
        *var_ptr = lv_mem_alloc(strlen(data->value_string) + 1);
        if (*var_ptr == NULL) {
            return;
        }
        strcpy(*var_ptr, data->value_string);
    }
    data->value_string = *var_ptr;
    return;
}
void _gui_msg_int32_cb(int32_t *var_ptr, gui_msg_action_t access, gui_msg_data_t *data)
{
    if (access == GUI_MSG_ACCESS_SET) {
        *var_ptr = data->value_int;
    }
    data->value_int = *var_ptr;
    return;
}
void _gui_msg_state_cb(lv_state_t *var_ptr, gui_msg_action_t access, gui_msg_data_t *data)
{
    if (access == GUI_MSG_ACCESS_SET) {
        *var_ptr = (lv_state_t)data->value_int;
    }
    data->value_int = (int32_t) * var_ptr;
    return;
}
void _gui_msg_obj_flag_cb(lv_obj_flag_t *var_ptr, gui_msg_action_t access, gui_msg_data_t *data)
{
    if (access == GUI_MSG_ACCESS_SET) {
        *var_ptr = (lv_obj_flag_t)data->value_int;
    }
    data->value_int = (int32_t) * var_ptr;
    return;
}
void _gui_msg_tm_cb(struct tm *var_ptr, bool is_systime, gui_msg_action_t access, gui_msg_data_t *data)
{
    if (access == GUI_MSG_ACCESS_SET) {
        *var_ptr = data->value_time;
    } else {
        if (is_systime) {
            time_t now = time(NULL);
            struct tm *tm = localtime(&now);
            if (tm != NULL) {
                *var_ptr = *tm;
            }
        }
    }
    data->value_time = *var_ptr;
    return;
}
void _gui_msg_bool_cb(bool *var_ptr, gui_msg_action_t access, gui_msg_data_t *data)
{
    if (access == GUI_MSG_ACCESS_SET) {
        *var_ptr = data->value_bool;
    }
    data->value_bool = *var_ptr;
    return;
}

#endif
