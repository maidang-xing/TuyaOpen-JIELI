/*Generate Code, Do NOT Edit!*/
#include "./events_init.h"
#if LV_USE_GUIBUILDER_SIMULATOR
#include <stdio.h>
#endif
#include "lvgl.h"
#include "./callback_handler.h"
#include "../gui_timelines/gui_timelines.h"
#include "../gui_group/gui_group.h"

void scr_loaded_handler(lv_event_t *e)
{
    lv_obj_t *src = lv_event_get_target(e);
    gui_msg_init_ui();
    gui_msg_init_events();
}

void events_init(lv_ui *ui)
{
}
static void video_call_screen_event_handler(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_SCREEN_LOAD_START: {
        gui_scr_action_cb(GUI_SCREEN_VIDEO_CALL, GUI_SCREEN_ACTION_LOAD);
        break;
    }
    case LV_EVENT_SCREEN_UNLOADED: {
        gui_scr_action_cb(GUI_SCREEN_VIDEO_CALL, GUI_SCREEN_ACTION_UNLOAD);
        break;
    }
    }
}

void events_init_video_call(lv_ui *ui)
{
    lv_ui_video_call *ui_scr = ui_get_scr_ptr(ui, GUI_SCREEN_VIDEO_CALL);
    lv_obj_add_event_cb(ui_scr->video_call, scr_loaded_handler, LV_EVENT_SCREEN_LOADED, ui);
    lv_obj_add_event_cb(ui_scr->video_call, video_call_screen_event_handler, LV_EVENT_ALL, ui);
}
