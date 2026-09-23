#include "app_config.h"
#ifdef CONFIG_UI_STYLE_JL_ENABLE
/*Generate Code, Do NOT Edit!*/
#ifndef GUI_MODEL_MSG_H_
#define GUI_MODEL_MSG_H_
#ifdef __cplusplus
extern "C" {
#endif
#include "./gui_msg.h"

#if LV_USE_OBSERVER

typedef enum {
    GUI_MODEL_MSG_ID_CUR_TIME = 0x0002,
    GUI_MODEL_MSG_ID_PREV_FILE = 0x0003,
    GUI_MODEL_MSG_ID_NEXT_FILE = 0x0004,
    GUI_MODEL_MSG_ID_VIDEO_PAUSE = 0x0005,
    GUI_MODEL_MSG_ID_CUR_TIME_PROCESS = 0x0006,
    GUI_MODEL_MSG_ID_FILE_NAME = 0x0007,
    GUI_MODEL_MSG_ID_TOTAL_TIME = 0x0008,
    GUI_MODEL_MSG_ID_FILE_PATH = 0x0009,
    GUI_MODEL_MSG_ID_FILE_NUM = 0x000A,
} gui_model_msg_id_t;

extern int gui_model_msg_cur_time_cb(gui_msg_action_t access, gui_msg_data_t *data, gui_msg_data_type_t type);
extern int gui_model_msg_prev_file_cb(gui_msg_action_t access, gui_msg_data_t *data, gui_msg_data_type_t type);
extern int gui_model_msg_next_file_cb(gui_msg_action_t access, gui_msg_data_t *data, gui_msg_data_type_t type);
extern int gui_model_msg_video_pause_cb(gui_msg_action_t access, gui_msg_data_t *data, gui_msg_data_type_t type);
extern int gui_model_msg_cur_time_process_cb(gui_msg_action_t access, gui_msg_data_t *data, gui_msg_data_type_t type);
extern int gui_model_msg_file_name_cb(gui_msg_action_t access, gui_msg_data_t *data, gui_msg_data_type_t type);
extern int gui_model_msg_total_time_cb(gui_msg_action_t access, gui_msg_data_t *data, gui_msg_data_type_t type);
extern int gui_model_msg_file_path_cb(gui_msg_action_t access, gui_msg_data_t *data, gui_msg_data_type_t type);
extern int gui_model_msg_file_num_cb(gui_msg_action_t access, gui_msg_data_t *data, gui_msg_data_type_t type);

extern void gui_model_msg_init(lv_ui *ui);
extern void gui_model_msg_init_ui();
extern void gui_model_msg_init_events();
extern void gui_model_msg_unsubscribe();
extern gui_msg_status_t gui_model_msg_send(int32_t msg_id, void *value, int32_t len);
extern gui_msg_data_t *gui_model_msg_get(int32_t msg_id);
extern void gui_model_msg_action_change(int32_t msg_id, gui_msg_action_t access, gui_msg_data_t *data, gui_msg_data_type_t type);

#endif

#ifdef __cplusplus
}
#endif
#endif /* GUI_MODEL_MSG_H_ */

#endif
