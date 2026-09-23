#include "app_config.h"
#ifdef CONFIG_UI_STYLE_JL_ENABLE
/*Generate Code, Do NOT Edit!*/
#ifndef GUI_MODEL_VIDEO_PLAY_MSG_H_
#define GUI_MODEL_VIDEO_PLAY_MSG_H_
#ifdef __cplusplus
extern "C" {
#endif
#include "./gui_msg.h"

#if LV_USE_OBSERVER

typedef enum {
    GUI_MODEL_VIDEO_PLAY_MSG_ID_DISP_PROGRESS_BAR = 0x005E,
    GUI_MODEL_VIDEO_PLAY_MSG_ID_ADD_CLICK_FLAG = 0x005F,
    GUI_MODEL_VIDEO_PLAY_MSG_ID_CLEAR_CLICK_FLAG = 0x0060,
} gui_model_video_play_msg_id_t;

extern int gui_model_video_play_msg_disp_progress_bar_cb(gui_msg_action_t access, gui_msg_data_t *data, gui_msg_data_type_t type);
extern int gui_model_video_play_msg_add_click_flag_cb(gui_msg_action_t access, gui_msg_data_t *data, gui_msg_data_type_t type);
extern int gui_model_video_play_msg_clear_click_flag_cb(gui_msg_action_t access, gui_msg_data_t *data, gui_msg_data_type_t type);

extern void gui_model_video_play_msg_init(lv_ui *ui);
extern void gui_model_video_play_msg_init_ui();
extern void gui_model_video_play_msg_init_events();
extern void gui_model_video_play_msg_unsubscribe();
extern gui_msg_status_t gui_model_video_play_msg_send(int32_t msg_id, void *value, int32_t len);
extern gui_msg_data_t *gui_model_video_play_msg_get(int32_t msg_id);
extern void gui_model_video_play_msg_action_change(int32_t msg_id, gui_msg_action_t access, gui_msg_data_t *data, gui_msg_data_type_t type);

#endif

#ifdef __cplusplus
}
#endif
#endif /* GUI_MODEL_VIDEO_PLAY_MSG_H_ */

#endif
