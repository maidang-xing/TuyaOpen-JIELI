#include "app_config.h"
#ifdef CONFIG_UI_STYLE_LY_ENABLE
/*Generate Code, Do NOT Edit!*/
#include "lvgl.h"
#if LV_USE_GUIBUILDER_SIMULATOR
#include <stdio.h>
#endif
#include <stdlib.h>
#include "../gui_guider.h"
#include "../gui_events/events_init.h"
#include "../gui_events/callback_handler.h"
#include "../gui_events/i18n_handler.h"
#include "../gui_timelines/gui_timelines.h"
#include "../../custom/custom.h"


lv_obj_t *setup_scr_usb_slave(lv_ui *ui)
{
    lv_ui_usb_slave *ui_scr = ui_get_scr_ptr(ui, GUI_SCREEN_USB_SLAVE);
    if (ui_scr == NULL) {
        ui_scr = lv_mem_alloc(sizeof(lv_ui_usb_slave));
        if (ui_scr == NULL) {
            return NULL;
        }
        memset(ui_scr, 0, sizeof(lv_ui_usb_slave));
        ui->usb_slave = ui_scr;
    }

    //Write codes usb_slave
    ui_scr->usb_slave = lv_obj_create(NULL);
    lv_obj_set_scrollbar_mode(ui_scr->usb_slave, LV_SCROLLBAR_MODE_OFF);
    ui_style_set(ui_scr->usb_slave, GUI_CTRL_SCR);

    //Set style for usb_slave. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
    lv_obj_set_style_bg_opa(ui_scr->usb_slave, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    //Write codes usb_slave_img_icon_pccam
    ui_scr->usb_slave_img_icon_pccam = lv_img_create(ui_scr->usb_slave);
    lv_img_set_src(ui_scr->usb_slave_img_icon_pccam, gui_get_res_path(GUI_RES_S_PC_PNG));
    lv_img_set_pivot(ui_scr->usb_slave_img_icon_pccam, 0, 0);
    lv_img_set_angle(ui_scr->usb_slave_img_icon_pccam, 0);
    lv_img_set_zoom(ui_scr->usb_slave_img_icon_pccam, 256);
    lv_obj_set_pos(ui_scr->usb_slave_img_icon_pccam, 298, 109);
    lv_obj_set_size(ui_scr->usb_slave_img_icon_pccam, 200, 200);
    lv_obj_add_flag(ui_scr->usb_slave_img_icon_pccam, LV_OBJ_FLAG_HIDDEN);
    lv_obj_add_flag(ui_scr->usb_slave_img_icon_pccam, LV_OBJ_FLAG_CLICKABLE);
    ui_style_set(ui_scr->usb_slave_img_icon_pccam, GUI_CTRL_IMG);

    //Write codes usb_slave_img_icon_masstorage
    ui_scr->usb_slave_img_icon_masstorage = lv_img_create(ui_scr->usb_slave);
    lv_img_set_src(ui_scr->usb_slave_img_icon_masstorage, gui_get_res_path(GUI_RES_S_MASS_PNG));
    lv_img_set_pivot(ui_scr->usb_slave_img_icon_masstorage, 0, 0);
    lv_img_set_angle(ui_scr->usb_slave_img_icon_masstorage, 0);
    lv_img_set_zoom(ui_scr->usb_slave_img_icon_masstorage, 256);
    lv_obj_set_pos(ui_scr->usb_slave_img_icon_masstorage, 298, 116);
    lv_obj_set_size(ui_scr->usb_slave_img_icon_masstorage, 200, 200);
    lv_obj_add_flag(ui_scr->usb_slave_img_icon_masstorage, LV_OBJ_FLAG_HIDDEN);
    lv_obj_add_flag(ui_scr->usb_slave_img_icon_masstorage, LV_OBJ_FLAG_CLICKABLE);
    ui_style_set(ui_scr->usb_slave_img_icon_masstorage, GUI_CTRL_IMG);

    //Write codes usb_slave_view_btnlist
    ui_scr->usb_slave_view_btnlist = lv_obj_create(ui_scr->usb_slave);
    lv_obj_set_pos(ui_scr->usb_slave_view_btnlist, 253, 70);
    lv_obj_set_size(ui_scr->usb_slave_view_btnlist, 289, 330);
    lv_obj_set_scrollbar_mode(ui_scr->usb_slave_view_btnlist, LV_SCROLLBAR_MODE_OFF);
    ui_style_set(ui_scr->usb_slave_view_btnlist, GUI_CTRL_CONT);

    //Delete extra default style for usb_slave_view_btnlist
    lv_obj_remove_style(ui_scr->usb_slave_view_btnlist, &gui_cont_main_focus_key_style, LV_PART_MAIN | LV_STATE_FOCUS_KEY);

    //Write codes usb_slave_btn_usb_msd
    ui_scr->usb_slave_btn_usb_msd = lv_btn_create(ui_scr->usb_slave_view_btnlist);
    lv_obj_set_pos(ui_scr->usb_slave_btn_usb_msd, 27, 25);
    lv_obj_set_size(ui_scr->usb_slave_btn_usb_msd, 236, 42);
    lv_obj_set_scrollbar_mode(ui_scr->usb_slave_btn_usb_msd, LV_SCROLLBAR_MODE_OFF);
    ui_style_set(ui_scr->usb_slave_btn_usb_msd, GUI_CTRL_BUTTON);

    //Set style for usb_slave_btn_usb_msd. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
    lv_obj_set_style_text_color(ui_scr->usb_slave_btn_usb_msd, lv_color_make(0x00, 0x00, 0x00), LV_PART_MAIN | LV_STATE_DEFAULT);

    //Set style for usb_slave_btn_usb_msd. Part: LV_PART_MAIN, State: LV_STATE_FOCUS_KEY
    lv_obj_set_style_text_color(ui_scr->usb_slave_btn_usb_msd, lv_color_make(0x00, 0x00, 0x00), LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    ui_scr->usb_slave_btn_usb_msd_label = lv_label_create(ui_scr->usb_slave_btn_usb_msd);
    lv_obj_set_style_pad_all(ui_scr->usb_slave_btn_usb_msd, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_align(ui_scr->usb_slave_btn_usb_msd_label, LV_ALIGN_CENTER, 0, 0);

    //Write codes usb_slave_btn_pc_cam
    ui_scr->usb_slave_btn_pc_cam = lv_btn_create(ui_scr->usb_slave_view_btnlist);
    lv_obj_set_pos(ui_scr->usb_slave_btn_pc_cam, 26, 101);
    lv_obj_set_size(ui_scr->usb_slave_btn_pc_cam, 236, 42);
    lv_obj_set_scrollbar_mode(ui_scr->usb_slave_btn_pc_cam, LV_SCROLLBAR_MODE_OFF);
    ui_style_set(ui_scr->usb_slave_btn_pc_cam, GUI_CTRL_BUTTON);

    //Set style for usb_slave_btn_pc_cam. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
    lv_obj_set_style_text_color(ui_scr->usb_slave_btn_pc_cam, lv_color_make(0x00, 0x00, 0x00), LV_PART_MAIN | LV_STATE_DEFAULT);

    //Set style for usb_slave_btn_pc_cam. Part: LV_PART_MAIN, State: LV_STATE_FOCUS_KEY
    lv_obj_set_style_text_color(ui_scr->usb_slave_btn_pc_cam, lv_color_make(0x00, 0x00, 0x00), LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    ui_scr->usb_slave_btn_pc_cam_label = lv_label_create(ui_scr->usb_slave_btn_pc_cam);
    lv_obj_set_style_pad_all(ui_scr->usb_slave_btn_pc_cam, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_align(ui_scr->usb_slave_btn_pc_cam_label, LV_ALIGN_CENTER, 0, 0);

    //Write codes usb_slave_btn_video_rec
    ui_scr->usb_slave_btn_video_rec = lv_btn_create(ui_scr->usb_slave_view_btnlist);
    lv_obj_set_pos(ui_scr->usb_slave_btn_video_rec, 26, 184);
    lv_obj_set_size(ui_scr->usb_slave_btn_video_rec, 236, 42);
    lv_obj_set_scrollbar_mode(ui_scr->usb_slave_btn_video_rec, LV_SCROLLBAR_MODE_OFF);
    ui_style_set(ui_scr->usb_slave_btn_video_rec, GUI_CTRL_BUTTON);

    //Set style for usb_slave_btn_video_rec. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
    lv_obj_set_style_text_color(ui_scr->usb_slave_btn_video_rec, lv_color_make(0x00, 0x00, 0x00), LV_PART_MAIN | LV_STATE_DEFAULT);

    //Set style for usb_slave_btn_video_rec. Part: LV_PART_MAIN, State: LV_STATE_FOCUS_KEY
    lv_obj_set_style_text_color(ui_scr->usb_slave_btn_video_rec, lv_color_make(0x00, 0x00, 0x00), LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    ui_scr->usb_slave_btn_video_rec_label = lv_label_create(ui_scr->usb_slave_btn_video_rec);
    lv_obj_set_style_pad_all(ui_scr->usb_slave_btn_video_rec, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_align(ui_scr->usb_slave_btn_video_rec_label, LV_ALIGN_CENTER, 0, 0);

    //Write codes usb_slave_btn_1
    ui_scr->usb_slave_btn_1 = lv_btn_create(ui_scr->usb_slave_view_btnlist);
    lv_obj_set_pos(ui_scr->usb_slave_btn_1, 26, 263);
    lv_obj_set_size(ui_scr->usb_slave_btn_1, 236, 42);
    lv_obj_set_scrollbar_mode(ui_scr->usb_slave_btn_1, LV_SCROLLBAR_MODE_OFF);
    ui_style_set(ui_scr->usb_slave_btn_1, GUI_CTRL_BUTTON);

    //Set style for usb_slave_btn_1. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
    lv_obj_set_style_text_color(ui_scr->usb_slave_btn_1, lv_color_make(0x00, 0x00, 0x00), LV_PART_MAIN | LV_STATE_DEFAULT);

    //Set style for usb_slave_btn_1. Part: LV_PART_MAIN, State: LV_STATE_FOCUS_KEY
    lv_obj_set_style_text_color(ui_scr->usb_slave_btn_1, lv_color_make(0x00, 0x00, 0x00), LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    ui_scr->usb_slave_btn_1_label = lv_label_create(ui_scr->usb_slave_btn_1);
    lv_obj_set_style_pad_all(ui_scr->usb_slave_btn_1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_align(ui_scr->usb_slave_btn_1_label, LV_ALIGN_CENTER, 0, 0);

    lv_obj_update_layout(ui_scr->usb_slave);
    ui_scr->usb_slave_del = false;
    i18n_refresh_texts(GUI_SCREEN_USB_SLAVE);

    //Init events for screen
    events_init_usb_slave(ui);
    return ui_scr->usb_slave;
}
void unload_scr_usb_slave(lv_ui *ui)
{
    ui_free_scr_ptr(ui, GUI_SCREEN_USB_SLAVE);
}

#endif
