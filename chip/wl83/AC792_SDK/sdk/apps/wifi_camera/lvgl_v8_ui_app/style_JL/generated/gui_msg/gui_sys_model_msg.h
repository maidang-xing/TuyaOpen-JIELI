#include "app_config.h"
#ifdef CONFIG_UI_STYLE_JL_ENABLE
/*Generate Code, Do NOT Edit!*/
#ifndef GUI_SYS_MODEL_MSG_H_
#define GUI_SYS_MODEL_MSG_H_
#ifdef __cplusplus
extern "C" {
#endif
#include "./gui_msg.h"

#if LV_USE_OBSERVER

typedef enum {
    GUI_SYS_MODEL_MSG_ID_SYS_TIME = 0xf001,
} gui_sys_model_msg_id_t;

extern int gui_sys_model_msg_sys_time_cb(gui_msg_action_t access, gui_msg_data_t *data, gui_msg_data_type_t type);

extern void gui_sys_model_msg_init(lv_ui *ui);
extern void gui_sys_model_msg_init_ui();
extern void gui_sys_model_msg_init_events();
extern void gui_sys_model_msg_unsubscribe();
extern gui_msg_status_t gui_sys_model_msg_send(int32_t msg_id, void *value, int32_t len);
extern gui_msg_data_t *gui_sys_model_msg_get(int32_t msg_id);
extern void gui_sys_model_msg_action_change(int32_t msg_id, gui_msg_action_t access, gui_msg_data_t *data, gui_msg_data_type_t type);

#endif

#ifdef __cplusplus
}
#endif
#endif /* GUI_SYS_MODEL_MSG_H_ */

#endif
