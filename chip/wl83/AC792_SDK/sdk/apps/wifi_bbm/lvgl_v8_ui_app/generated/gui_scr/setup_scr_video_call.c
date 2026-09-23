/*Generate Code, Do NOT Edit!*/
#include "lvgl.h"
#if LV_USE_GUIBUILDER_SIMULATOR
#include <stdio.h>
#endif
#include <stdlib.h>
#include "../gui_guider.h"
#include "../gui_events/events_init.h"
#include "../gui_events/callback_handler.h"
#include "../gui_timelines/gui_timelines.h"
#include "../../custom/custom.h"

static const char *video_call_imglist_1_imgs[5] = {
#if LV_USE_GUIBUILDER_SIMULATOR
    "A:\\gitlab-m\\ac792\\ui_prj\\wifi_bbm_240x320\\import\\image\\wifi_1.png",
    "A:\\gitlab-m\\ac792\\ui_prj\\wifi_bbm_240x320\\import\\image\\wifi_2.png",
    "A:\\gitlab-m\\ac792\\ui_prj\\wifi_bbm_240x320\\import\\image\\wifi_3.png",
    "A:\\gitlab-m\\ac792\\ui_prj\\wifi_bbm_240x320\\import\\image\\wifi_4.png",
    "A:\\gitlab-m\\ac792\\ui_prj\\wifi_bbm_240x320\\import\\image\\wifi_5.png"
#else
    "mnt/sdfile/EXT_RESERVED/uipackres/ui/4b000000.zip",
    "mnt/sdfile/EXT_RESERVED/uipackres/ui/4b000001.zip",
    "mnt/sdfile/EXT_RESERVED/uipackres/ui/4b000002.zip",
    "mnt/sdfile/EXT_RESERVED/uipackres/ui/4b000003.zip",
    "mnt/sdfile/EXT_RESERVED/uipackres/ui/4b000004.zip"
#endif
};

lv_obj_t *setup_scr_video_call(lv_ui *ui)
{
    lv_ui_video_call *ui_scr = ui_get_scr_ptr(ui, GUI_SCREEN_VIDEO_CALL);
    if (ui_scr == NULL) {
        ui_scr = lv_mem_alloc(sizeof(lv_ui_video_call));
        memset(ui_scr, 0, sizeof(lv_ui_video_call));
        ui->video_call = ui_scr;
    }

    //Write codes video_call
    ui_scr->video_call = lv_obj_create(NULL);
    lv_group_t *def_group = lv_group_get_default();
    lv_obj_set_scrollbar_mode(ui_scr->video_call, LV_SCROLLBAR_MODE_OFF);
    lv_group_add_obj(def_group, ui_scr->video_call);
    ui_style_set(ui_scr->video_call, GUI_CTRL_SCR);

    //Write codes video_call_lbl_1
    ui_scr->video_call_lbl_1 = lv_label_create(ui_scr->video_call);
    lv_label_set_text(ui_scr->video_call_lbl_1, "");
    lv_label_set_long_mode(ui_scr->video_call_lbl_1, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui_scr->video_call_lbl_1, 210, 0);
    lv_obj_set_size(ui_scr->video_call_lbl_1, 30, 50);
    lv_obj_set_scrollbar_mode(ui_scr->video_call_lbl_1, LV_SCROLLBAR_MODE_OFF);
    ui_style_set(ui_scr->video_call_lbl_1, GUI_CTRL_LABEL);

    //Write codes video_call_lbl_2
    ui_scr->video_call_lbl_2 = lv_label_create(ui_scr->video_call);
    lv_label_set_text(ui_scr->video_call_lbl_2, "");
    lv_label_set_long_mode(ui_scr->video_call_lbl_2, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui_scr->video_call_lbl_2, 40, 0);
    lv_obj_set_size(ui_scr->video_call_lbl_2, 160, 86);
    lv_obj_set_scrollbar_mode(ui_scr->video_call_lbl_2, LV_SCROLLBAR_MODE_OFF);
    ui_style_set(ui_scr->video_call_lbl_2, GUI_CTRL_LABEL);

    //Write codes video_call_imglist_1
    ui_scr->video_call_imglist_1 = lv_imglist_create(ui_scr->video_call);
    lv_obj_set_pos(ui_scr->video_call_imglist_1, 0, 0);
    lv_obj_set_size(ui_scr->video_call_imglist_1, 39, 32);
    lv_obj_set_scrollbar_mode(ui_scr->video_call_imglist_1, LV_SCROLLBAR_MODE_OFF);
    ui_style_set(ui_scr->video_call_imglist_1, GUI_CTRL_IMGLIST);
    lv_imglist_set_src(ui_scr->video_call_imglist_1, (const void **) video_call_imglist_1_imgs, 5);
    lv_imglist_set_act(ui_scr->video_call_imglist_1, 0);

    lv_obj_update_layout(ui_scr->video_call);
    ui_scr->video_call_del = false;

    //Init events for screen
    events_init_video_call(ui);
    return ui_scr->video_call;
}
void unload_scr_video_call(lv_ui *ui)
{
    ui_free_scr_ptr(ui, GUI_SCREEN_VIDEO_CALL);
}
