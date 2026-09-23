#include "app_config.h"
#ifdef CONFIG_UI_STYLE_JL_ENABLE
/*Generate Code, Do NOT Edit!*/
#ifndef GUI_MODEL_GLOBAL_SUBPAGE_MSG_H_
#define GUI_MODEL_GLOBAL_SUBPAGE_MSG_H_
#ifdef __cplusplus
extern "C" {
#endif
#include "./gui_msg.h"

#if LV_USE_OBSERVER

typedef enum {
    GUI_MODEL_GLOBAL_SUBPAGE_MSG_ID_SUBPAGE_ICON = 0x000C,
    GUI_MODEL_GLOBAL_SUBPAGE_MSG_ID_FUNCKEY1 = 0x000D,
    GUI_MODEL_GLOBAL_SUBPAGE_MSG_ID_FUNCKEY2 = 0x000E,
    GUI_MODEL_GLOBAL_SUBPAGE_MSG_ID_FUNCKEY3 = 0x000F,
    GUI_MODEL_GLOBAL_SUBPAGE_MSG_ID_FUNCKEY4 = 0x0010,
    GUI_MODEL_GLOBAL_SUBPAGE_MSG_ID_TITLE = 0x0011,
    GUI_MODEL_GLOBAL_SUBPAGE_MSG_ID_HIDE_FUNCKEY1 = 0x0012,
    GUI_MODEL_GLOBAL_SUBPAGE_MSG_ID_HIDE_FUNCKEY2 = 0x0013,
    GUI_MODEL_GLOBAL_SUBPAGE_MSG_ID_HIDE_FUNCKEY3 = 0x0014,
    GUI_MODEL_GLOBAL_SUBPAGE_MSG_ID_HIDE_FUNCKEY4 = 0x0015,
    GUI_MODEL_GLOBAL_SUBPAGE_MSG_ID_SHOW_FUNCKEY1 = 0x0016,
    GUI_MODEL_GLOBAL_SUBPAGE_MSG_ID_SHOW_FUNCKEY2 = 0x0017,
    GUI_MODEL_GLOBAL_SUBPAGE_MSG_ID_SHOW_FUNCKEY3 = 0x0018,
    GUI_MODEL_GLOBAL_SUBPAGE_MSG_ID_SHOW_FUNCKEY4 = 0x0019,
    GUI_MODEL_GLOBAL_SUBPAGE_MSG_ID_ROLLER_OPT = 0x001A,
    GUI_MODEL_GLOBAL_SUBPAGE_MSG_ID_SHOW_ROLLER = 0x001B,
    GUI_MODEL_GLOBAL_SUBPAGE_MSG_ID_HIDE_ROLLER = 0x001C,
    GUI_MODEL_GLOBAL_SUBPAGE_MSG_ID_STATE_FUNKEY1 = 0x001D,
    GUI_MODEL_GLOBAL_SUBPAGE_MSG_ID_STATE_FUNKEY2 = 0x001E,
    GUI_MODEL_GLOBAL_SUBPAGE_MSG_ID_STATE_FUNKEY3 = 0x001F,
} gui_model_global_subpage_msg_id_t;

extern int gui_model_global_subpage_msg_subpage_icon_cb(gui_msg_action_t access, gui_msg_data_t *data, gui_msg_data_type_t type);
extern int gui_model_global_subpage_msg_funckey1_cb(gui_msg_action_t access, gui_msg_data_t *data, gui_msg_data_type_t type);
extern int gui_model_global_subpage_msg_funckey2_cb(gui_msg_action_t access, gui_msg_data_t *data, gui_msg_data_type_t type);
extern int gui_model_global_subpage_msg_funckey3_cb(gui_msg_action_t access, gui_msg_data_t *data, gui_msg_data_type_t type);
extern int gui_model_global_subpage_msg_funckey4_cb(gui_msg_action_t access, gui_msg_data_t *data, gui_msg_data_type_t type);
extern int gui_model_global_subpage_msg_title_cb(gui_msg_action_t access, gui_msg_data_t *data, gui_msg_data_type_t type);
extern int gui_model_global_subpage_msg_hide_funckey1_cb(gui_msg_action_t access, gui_msg_data_t *data, gui_msg_data_type_t type);
extern int gui_model_global_subpage_msg_hide_funckey2_cb(gui_msg_action_t access, gui_msg_data_t *data, gui_msg_data_type_t type);
extern int gui_model_global_subpage_msg_hide_funckey3_cb(gui_msg_action_t access, gui_msg_data_t *data, gui_msg_data_type_t type);
extern int gui_model_global_subpage_msg_hide_funckey4_cb(gui_msg_action_t access, gui_msg_data_t *data, gui_msg_data_type_t type);
extern int gui_model_global_subpage_msg_show_funckey1_cb(gui_msg_action_t access, gui_msg_data_t *data, gui_msg_data_type_t type);
extern int gui_model_global_subpage_msg_show_funckey2_cb(gui_msg_action_t access, gui_msg_data_t *data, gui_msg_data_type_t type);
extern int gui_model_global_subpage_msg_show_funckey3_cb(gui_msg_action_t access, gui_msg_data_t *data, gui_msg_data_type_t type);
extern int gui_model_global_subpage_msg_show_funckey4_cb(gui_msg_action_t access, gui_msg_data_t *data, gui_msg_data_type_t type);
extern int gui_model_global_subpage_msg_roller_opt_cb(gui_msg_action_t access, gui_msg_data_t *data, gui_msg_data_type_t type);
extern int gui_model_global_subpage_msg_show_roller_cb(gui_msg_action_t access, gui_msg_data_t *data, gui_msg_data_type_t type);
extern int gui_model_global_subpage_msg_hide_roller_cb(gui_msg_action_t access, gui_msg_data_t *data, gui_msg_data_type_t type);
extern int gui_model_global_subpage_msg_state_funkey1_cb(gui_msg_action_t access, gui_msg_data_t *data, gui_msg_data_type_t type);
extern int gui_model_global_subpage_msg_state_funkey2_cb(gui_msg_action_t access, gui_msg_data_t *data, gui_msg_data_type_t type);
extern int gui_model_global_subpage_msg_state_funkey3_cb(gui_msg_action_t access, gui_msg_data_t *data, gui_msg_data_type_t type);

extern void gui_model_global_subpage_msg_init(lv_ui *ui);
extern void gui_model_global_subpage_msg_init_ui();
extern void gui_model_global_subpage_msg_init_events();
extern void gui_model_global_subpage_msg_unsubscribe();
extern gui_msg_status_t gui_model_global_subpage_msg_send(int32_t msg_id, void *value, int32_t len);
extern gui_msg_data_t *gui_model_global_subpage_msg_get(int32_t msg_id);
extern void gui_model_global_subpage_msg_action_change(int32_t msg_id, gui_msg_action_t access, gui_msg_data_t *data, gui_msg_data_type_t type);

#endif

#ifdef __cplusplus
}
#endif
#endif /* GUI_MODEL_GLOBAL_SUBPAGE_MSG_H_ */

#endif
