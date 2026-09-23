#include "app_config.h"
#ifdef CONFIG_UI_STYLE_JL_ENABLE
/*Generate Code, Do NOT Edit!*/
#ifndef GUI_MODEL_VIDEO_PHOTO_MSG_H_
#define GUI_MODEL_VIDEO_PHOTO_MSG_H_
#ifdef __cplusplus
extern "C" {
#endif
#include "./gui_msg.h"

#if LV_USE_OBSERVER

typedef enum {
    GUI_MODEL_VIDEO_PHOTO_MSG_ID_ISO_ICON = 0x0050,
    GUI_MODEL_VIDEO_PHOTO_MSG_ID_RESOLUTION_ICON = 0x0051,
    GUI_MODEL_VIDEO_PHOTO_MSG_ID_AWB_ICON = 0x0052,
    GUI_MODEL_VIDEO_PHOTO_MSG_ID_QUALITY_ICON = 0x0053,
    GUI_MODEL_VIDEO_PHOTO_MSG_ID_SHOT_MODE_ICON = 0x0054,
    GUI_MODEL_VIDEO_PHOTO_MSG_ID_SHOW_HANDSHAKE = 0x0055,
    GUI_MODEL_VIDEO_PHOTO_MSG_ID_HIDE_HANDSHAKE = 0x0056,
    GUI_MODEL_VIDEO_PHOTO_MSG_ID_SHOW_SHOTS = 0x0057,
    GUI_MODEL_VIDEO_PHOTO_MSG_ID_HIDE_SHOTS = 0x0058,
    GUI_MODEL_VIDEO_PHOTO_MSG_ID_SHOW_SHOTS_MODE = 0x0059,
    GUI_MODEL_VIDEO_PHOTO_MSG_ID_HIDE_SHOTS_MODE = 0x005A,
    GUI_MODEL_VIDEO_PHOTO_MSG_ID_PHOTO_REMAIN = 0x005B,
    GUI_MODEL_VIDEO_PHOTO_MSG_ID_CAPTURE_TIME = 0x005C,
} gui_model_video_photo_msg_id_t;

extern int gui_model_video_photo_msg_iso_icon_cb(gui_msg_action_t access, gui_msg_data_t *data, gui_msg_data_type_t type);
extern int gui_model_video_photo_msg_resolution_icon_cb(gui_msg_action_t access, gui_msg_data_t *data, gui_msg_data_type_t type);
extern int gui_model_video_photo_msg_awb_icon_cb(gui_msg_action_t access, gui_msg_data_t *data, gui_msg_data_type_t type);
extern int gui_model_video_photo_msg_quality_icon_cb(gui_msg_action_t access, gui_msg_data_t *data, gui_msg_data_type_t type);
extern int gui_model_video_photo_msg_shot_mode_icon_cb(gui_msg_action_t access, gui_msg_data_t *data, gui_msg_data_type_t type);
extern int gui_model_video_photo_msg_show_handshake_cb(gui_msg_action_t access, gui_msg_data_t *data, gui_msg_data_type_t type);
extern int gui_model_video_photo_msg_hide_handshake_cb(gui_msg_action_t access, gui_msg_data_t *data, gui_msg_data_type_t type);
extern int gui_model_video_photo_msg_show_shots_cb(gui_msg_action_t access, gui_msg_data_t *data, gui_msg_data_type_t type);
extern int gui_model_video_photo_msg_hide_shots_cb(gui_msg_action_t access, gui_msg_data_t *data, gui_msg_data_type_t type);
extern int gui_model_video_photo_msg_show_shots_mode_cb(gui_msg_action_t access, gui_msg_data_t *data, gui_msg_data_type_t type);
extern int gui_model_video_photo_msg_hide_shots_mode_cb(gui_msg_action_t access, gui_msg_data_t *data, gui_msg_data_type_t type);
extern int gui_model_video_photo_msg_photo_remain_cb(gui_msg_action_t access, gui_msg_data_t *data, gui_msg_data_type_t type);
extern int gui_model_video_photo_msg_capture_time_cb(gui_msg_action_t access, gui_msg_data_t *data, gui_msg_data_type_t type);

extern void gui_model_video_photo_msg_init(lv_ui *ui);
extern void gui_model_video_photo_msg_init_ui();
extern void gui_model_video_photo_msg_init_events();
extern void gui_model_video_photo_msg_unsubscribe();
extern gui_msg_status_t gui_model_video_photo_msg_send(int32_t msg_id, void *value, int32_t len);
extern gui_msg_data_t *gui_model_video_photo_msg_get(int32_t msg_id);
extern void gui_model_video_photo_msg_action_change(int32_t msg_id, gui_msg_action_t access, gui_msg_data_t *data, gui_msg_data_type_t type);

#endif

#ifdef __cplusplus
}
#endif
#endif /* GUI_MODEL_VIDEO_PHOTO_MSG_H_ */

#endif
