#include "app_config.h"
#ifdef CONFIG_UI_STYLE_JL_ENABLE
/*Generate Code, Do NOT Edit!*/
#if LV_USE_GUIBUILDER_SIMULATOR
#include <stdio.h>
#endif
#include "../gui_guider.h"
#include "lvgl.h"
#include "./callback_handler.h"

// Generate video_rec_timer_1 CallBack Handler
void video_rec_timer_1_timer_cb(lv_timer_t *src)
{
    lv_ui_video_rec *ui_scr = ui_get_scr_ptr(&guider_ui, GUI_SCREEN_VIDEO_REC);
    extern int video_rec_record_time();
    lvgl_rpc_post_func(video_rec_record_time, 0);

    if (src->repeat_count == 0) {
        ui_scr->video_rec_timer_1 = NULL;
    }

}
// Generate video_play_hide_bar CallBack Handler
void video_play_hide_bar_timer_cb(lv_timer_t *src)
{
    lv_ui_video_play *ui_scr = ui_get_scr_ptr(&guider_ui, GUI_SCREEN_VIDEO_PLAY);
    if (lv_obj_is_valid(ui_scr->video_play_view_1)) {
        lv_obj_add_flag(ui_scr->video_play_view_1, LV_OBJ_FLAG_HIDDEN);
    }
    if (ui_scr->video_play_hide_bar) {
        lv_timer_del(ui_scr->video_play_hide_bar);
        ui_scr->video_play_hide_bar = NULL;
    }


    if (src->repeat_count == 0) {
        ui_scr->video_play_hide_bar = NULL;
    }

}
// Generate video_play_hide_label CallBack Handler
void video_play_hide_label_timer_cb(lv_timer_t *src)
{
    lv_ui_video_play *ui_scr = ui_get_scr_ptr(&guider_ui, GUI_SCREEN_VIDEO_PLAY);
    if (ui_scr->video_play_hide_label) {
        lv_timer_del(ui_scr->video_play_hide_label);
        ui_scr->video_play_hide_label = NULL;
    }


    if (src->repeat_count == 0) {
        ui_scr->video_play_hide_label = NULL;
    }

}

#endif
