#include "app_config.h"
#ifdef CONFIG_UI_STYLE_JL_ENABLE
/*Generate Code, Do NOT Edit!*/
#ifndef GUI_MODEL_SYS_SETTING_MSG_H_
#define GUI_MODEL_SYS_SETTING_MSG_H_
#ifdef __cplusplus
extern "C" {
#endif
#include "./gui_msg.h"

#if LV_USE_OBSERVER

typedef enum {
    GUI_MODEL_SYS_SETTING_MSG_ID_FUNKEY4 = 0x002F,
    GUI_MODEL_SYS_SETTING_MSG_ID_FUNKEY5 = 0x0030,
    GUI_MODEL_SYS_SETTING_MSG_ID_FUNKEY6 = 0x0031,
    GUI_MODEL_SYS_SETTING_MSG_ID_FUNKEY7 = 0x0032,
    GUI_MODEL_SYS_SETTING_MSG_ID_SUBPAGE_WARNING = 0x0033,
    GUI_MODEL_SYS_SETTING_MSG_ID_HIDE_VIEWDATE = 0x0034,
    GUI_MODEL_SYS_SETTING_MSG_ID_HIDE_VIEWCARNUM = 0x0035,
    GUI_MODEL_SYS_SETTING_MSG_ID_HIDE_VIEWLIST = 0x0036,
    GUI_MODEL_SYS_SETTING_MSG_ID_HIDE_SUBPAGEWARNING = 0x0037,
    GUI_MODEL_SYS_SETTING_MSG_ID_SHOW_VIEWDATE = 0x0038,
    GUI_MODEL_SYS_SETTING_MSG_ID_SHOW_VIEWCARNUM = 0x0039,
    GUI_MODEL_SYS_SETTING_MSG_ID_SHOW_VIEWLIST = 0x003A,
    GUI_MODEL_SYS_SETTING_MSG_ID_SHOW_SUBPAGEWARNING = 0x003B,
    GUI_MODEL_SYS_SETTING_MSG_ID_HIDE_FUNKEY5 = 0x003C,
    GUI_MODEL_SYS_SETTING_MSG_ID_HIDE_FUNKEY6 = 0x003D,
    GUI_MODEL_SYS_SETTING_MSG_ID_HIDE_FUNKEY7 = 0x003E,
    GUI_MODEL_SYS_SETTING_MSG_ID_SHOW_FUNKEY4 = 0x003F,
    GUI_MODEL_SYS_SETTING_MSG_ID_SHOW_FUNKEY5 = 0x0040,
    GUI_MODEL_SYS_SETTING_MSG_ID_SHOW_FUNKEY6 = 0x0041,
    GUI_MODEL_SYS_SETTING_MSG_ID_SHOW_FUNKEY7 = 0x0042,
    GUI_MODEL_SYS_SETTING_MSG_ID_STATE_FUNKEY4 = 0x0043,
    GUI_MODEL_SYS_SETTING_MSG_ID_STATE_FUNKEY5 = 0x0044,
    GUI_MODEL_SYS_SETTING_MSG_ID_STATE_FUNKEY6 = 0x0045,
    GUI_MODEL_SYS_SETTING_MSG_ID_STATE_FUNKEY7 = 0x0046,
    GUI_MODEL_SYS_SETTING_MSG_ID_HIDE_FUNKEY4 = 0x0047,
    GUI_MODEL_SYS_SETTING_MSG_ID_FUNKEY8 = 0x0048,
    GUI_MODEL_SYS_SETTING_MSG_ID_HIDE_FUNKEY8 = 0x0049,
    GUI_MODEL_SYS_SETTING_MSG_ID_SHOW_FUNKEY8 = 0x004A,
    GUI_MODEL_SYS_SETTING_MSG_ID_STATE_FUNKEY8 = 0x004B,
} gui_model_sys_setting_msg_id_t;

extern int gui_model_sys_setting_msg_funkey4_cb(gui_msg_action_t access, gui_msg_data_t *data, gui_msg_data_type_t type);
extern int gui_model_sys_setting_msg_funkey5_cb(gui_msg_action_t access, gui_msg_data_t *data, gui_msg_data_type_t type);
extern int gui_model_sys_setting_msg_funkey6_cb(gui_msg_action_t access, gui_msg_data_t *data, gui_msg_data_type_t type);
extern int gui_model_sys_setting_msg_funkey7_cb(gui_msg_action_t access, gui_msg_data_t *data, gui_msg_data_type_t type);
extern int gui_model_sys_setting_msg_subpage_warning_cb(gui_msg_action_t access, gui_msg_data_t *data, gui_msg_data_type_t type);
extern int gui_model_sys_setting_msg_hide_viewdate_cb(gui_msg_action_t access, gui_msg_data_t *data, gui_msg_data_type_t type);
extern int gui_model_sys_setting_msg_hide_viewcarnum_cb(gui_msg_action_t access, gui_msg_data_t *data, gui_msg_data_type_t type);
extern int gui_model_sys_setting_msg_hide_viewlist_cb(gui_msg_action_t access, gui_msg_data_t *data, gui_msg_data_type_t type);
extern int gui_model_sys_setting_msg_hide_subpagewarning_cb(gui_msg_action_t access, gui_msg_data_t *data, gui_msg_data_type_t type);
extern int gui_model_sys_setting_msg_show_viewdate_cb(gui_msg_action_t access, gui_msg_data_t *data, gui_msg_data_type_t type);
extern int gui_model_sys_setting_msg_show_viewcarnum_cb(gui_msg_action_t access, gui_msg_data_t *data, gui_msg_data_type_t type);
extern int gui_model_sys_setting_msg_show_viewlist_cb(gui_msg_action_t access, gui_msg_data_t *data, gui_msg_data_type_t type);
extern int gui_model_sys_setting_msg_show_subpagewarning_cb(gui_msg_action_t access, gui_msg_data_t *data, gui_msg_data_type_t type);
extern int gui_model_sys_setting_msg_hide_funkey5_cb(gui_msg_action_t access, gui_msg_data_t *data, gui_msg_data_type_t type);
extern int gui_model_sys_setting_msg_hide_funkey6_cb(gui_msg_action_t access, gui_msg_data_t *data, gui_msg_data_type_t type);
extern int gui_model_sys_setting_msg_hide_funkey7_cb(gui_msg_action_t access, gui_msg_data_t *data, gui_msg_data_type_t type);
extern int gui_model_sys_setting_msg_show_funkey4_cb(gui_msg_action_t access, gui_msg_data_t *data, gui_msg_data_type_t type);
extern int gui_model_sys_setting_msg_show_funkey5_cb(gui_msg_action_t access, gui_msg_data_t *data, gui_msg_data_type_t type);
extern int gui_model_sys_setting_msg_show_funkey6_cb(gui_msg_action_t access, gui_msg_data_t *data, gui_msg_data_type_t type);
extern int gui_model_sys_setting_msg_show_funkey7_cb(gui_msg_action_t access, gui_msg_data_t *data, gui_msg_data_type_t type);
extern int gui_model_sys_setting_msg_state_funkey4_cb(gui_msg_action_t access, gui_msg_data_t *data, gui_msg_data_type_t type);
extern int gui_model_sys_setting_msg_state_funkey5_cb(gui_msg_action_t access, gui_msg_data_t *data, gui_msg_data_type_t type);
extern int gui_model_sys_setting_msg_state_funkey6_cb(gui_msg_action_t access, gui_msg_data_t *data, gui_msg_data_type_t type);
extern int gui_model_sys_setting_msg_state_funkey7_cb(gui_msg_action_t access, gui_msg_data_t *data, gui_msg_data_type_t type);
extern int gui_model_sys_setting_msg_hide_funkey4_cb(gui_msg_action_t access, gui_msg_data_t *data, gui_msg_data_type_t type);
extern int gui_model_sys_setting_msg_funkey8_cb(gui_msg_action_t access, gui_msg_data_t *data, gui_msg_data_type_t type);
extern int gui_model_sys_setting_msg_hide_funkey8_cb(gui_msg_action_t access, gui_msg_data_t *data, gui_msg_data_type_t type);
extern int gui_model_sys_setting_msg_show_funkey8_cb(gui_msg_action_t access, gui_msg_data_t *data, gui_msg_data_type_t type);
extern int gui_model_sys_setting_msg_state_funkey8_cb(gui_msg_action_t access, gui_msg_data_t *data, gui_msg_data_type_t type);

extern void gui_model_sys_setting_msg_init(lv_ui *ui);
extern void gui_model_sys_setting_msg_init_ui();
extern void gui_model_sys_setting_msg_init_events();
extern void gui_model_sys_setting_msg_unsubscribe();
extern gui_msg_status_t gui_model_sys_setting_msg_send(int32_t msg_id, void *value, int32_t len);
extern gui_msg_data_t *gui_model_sys_setting_msg_get(int32_t msg_id);
extern void gui_model_sys_setting_msg_action_change(int32_t msg_id, gui_msg_action_t access, gui_msg_data_t *data, gui_msg_data_type_t type);

#endif

#ifdef __cplusplus
}
#endif
#endif /* GUI_MODEL_SYS_SETTING_MSG_H_ */

#endif
