#include "app_config.h"
#ifdef CONFIG_UI_STYLE_JL_ENABLE
/*Generate Code, Do NOT Edit!*/
#ifndef GUI_MODEL_MAIN_MSG_H_
#define GUI_MODEL_MAIN_MSG_H_
#ifdef __cplusplus
extern "C" {
#endif
#include "./gui_msg.h"

#if LV_USE_OBSERVER

typedef enum {
    GUI_MODEL_MAIN_MSG_ID_SYSTIME = 0x0021,
    GUI_MODEL_MAIN_MSG_ID_SD_ICON = 0x0022,
    GUI_MODEL_MAIN_MSG_ID_BATTERY = 0x0023,
    GUI_MODEL_MAIN_MSG_ID_SHOW_WIN_SWITCH = 0x0024,
    GUI_MODEL_MAIN_MSG_ID_HIDE_WIN_SWITCH = 0x0025,
    GUI_MODEL_MAIN_MSG_ID_SYS_PROMPT = 0x0026,
    GUI_MODEL_MAIN_MSG_ID_HEADLAMP = 0x0027,
    GUI_MODEL_MAIN_MSG_ID_SYS_PROMPT_SHOW = 0x0028,
    GUI_MODEL_MAIN_MSG_ID_SHOW_DEL_BTN = 0x0029,
    GUI_MODEL_MAIN_MSG_ID_HIDE_DEL_BTN = 0x002A,
    GUI_MODEL_MAIN_MSG_ID_WEEKDAY = 0x002B,
    GUI_MODEL_MAIN_MSG_ID_SHOW_HOME_BTN = 0x002C,
    GUI_MODEL_MAIN_MSG_ID_HIDE_HOME_BTN = 0x002D,
} gui_model_main_msg_id_t;

extern int gui_model_main_msg_systime_cb(gui_msg_action_t access, gui_msg_data_t *data, gui_msg_data_type_t type);
extern int gui_model_main_msg_sd_icon_cb(gui_msg_action_t access, gui_msg_data_t *data, gui_msg_data_type_t type);
extern int gui_model_main_msg_battery_cb(gui_msg_action_t access, gui_msg_data_t *data, gui_msg_data_type_t type);
extern int gui_model_main_msg_show_win_switch_cb(gui_msg_action_t access, gui_msg_data_t *data, gui_msg_data_type_t type);
extern int gui_model_main_msg_hide_win_switch_cb(gui_msg_action_t access, gui_msg_data_t *data, gui_msg_data_type_t type);
extern int gui_model_main_msg_sys_prompt_cb(gui_msg_action_t access, gui_msg_data_t *data, gui_msg_data_type_t type);
extern int gui_model_main_msg_headlamp_cb(gui_msg_action_t access, gui_msg_data_t *data, gui_msg_data_type_t type);
extern int gui_model_main_msg_sys_prompt_show_cb(gui_msg_action_t access, gui_msg_data_t *data, gui_msg_data_type_t type);
extern int gui_model_main_msg_show_del_btn_cb(gui_msg_action_t access, gui_msg_data_t *data, gui_msg_data_type_t type);
extern int gui_model_main_msg_hide_del_btn_cb(gui_msg_action_t access, gui_msg_data_t *data, gui_msg_data_type_t type);
extern int gui_model_main_msg_weekday_cb(gui_msg_action_t access, gui_msg_data_t *data, gui_msg_data_type_t type);
extern int gui_model_main_msg_show_home_btn_cb(gui_msg_action_t access, gui_msg_data_t *data, gui_msg_data_type_t type);
extern int gui_model_main_msg_hide_home_btn_cb(gui_msg_action_t access, gui_msg_data_t *data, gui_msg_data_type_t type);

extern void gui_model_main_msg_init(lv_ui *ui);
extern void gui_model_main_msg_init_ui();
extern void gui_model_main_msg_init_events();
extern void gui_model_main_msg_unsubscribe();
extern gui_msg_status_t gui_model_main_msg_send(int32_t msg_id, void *value, int32_t len);
extern gui_msg_data_t *gui_model_main_msg_get(int32_t msg_id);
extern void gui_model_main_msg_action_change(int32_t msg_id, gui_msg_action_t access, gui_msg_data_t *data, gui_msg_data_type_t type);

#endif

#ifdef __cplusplus
}
#endif
#endif /* GUI_MODEL_MAIN_MSG_H_ */

#endif
