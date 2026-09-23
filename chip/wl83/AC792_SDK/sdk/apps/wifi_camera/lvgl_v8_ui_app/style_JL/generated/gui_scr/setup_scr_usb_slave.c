#include "app_config.h"
#ifdef CONFIG_UI_STYLE_JL_ENABLE
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
        memset(ui_scr, 0, sizeof(lv_ui_usb_slave));
        ui->usb_slave = ui_scr;
    }

    //Write codes usb_slave
    ui_scr->usb_slave = lv_obj_create(NULL);
    lv_group_t *def_group = lv_group_get_default();
    lv_obj_set_scrollbar_mode(ui_scr->usb_slave, LV_SCROLLBAR_MODE_OFF);
    ui_style_set(ui_scr->usb_slave, GUI_CTRL_SCR);

    //Set style for usb_slave. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
    lv_obj_set_style_bg_color(ui_scr->usb_slave, lv_color_make(0x00, 0x00, 0x00), LV_PART_MAIN | LV_STATE_DEFAULT);
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

    //Delete extra default style for usb_slave_img_icon_pccam
    lv_obj_remove_style(ui_scr->usb_slave_img_icon_pccam, &gui_img_main_focus_key_style, LV_PART_MAIN | LV_STATE_FOCUS_KEY);

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

    //Delete extra default style for usb_slave_img_icon_masstorage
    lv_obj_remove_style(ui_scr->usb_slave_img_icon_masstorage, &gui_img_main_focus_key_style, LV_PART_MAIN | LV_STATE_FOCUS_KEY);

    //Write codes usb_slave_view_btnlist
    ui_scr->usb_slave_view_btnlist = lv_obj_create(ui_scr->usb_slave);
    lv_obj_set_pos(ui_scr->usb_slave_view_btnlist, 125, 70);
    lv_obj_set_size(ui_scr->usb_slave_view_btnlist, 565, 314);
    lv_obj_set_scrollbar_mode(ui_scr->usb_slave_view_btnlist, LV_SCROLLBAR_MODE_OFF);
    ui_style_set(ui_scr->usb_slave_view_btnlist, GUI_CTRL_CONT);

    //Set style for usb_slave_view_btnlist. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
    lv_obj_set_style_bg_opa(ui_scr->usb_slave_view_btnlist, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

    //Write codes usb_slave_imgbtn_videorec
    ui_scr->usb_slave_imgbtn_videorec = lv_imgbtn_create(ui_scr->usb_slave_view_btnlist);
    lv_obj_set_pos(ui_scr->usb_slave_imgbtn_videorec, 414, 33);
    lv_obj_set_size(ui_scr->usb_slave_imgbtn_videorec, 128, 220);
    lv_obj_set_scrollbar_mode(ui_scr->usb_slave_imgbtn_videorec, LV_SCROLLBAR_MODE_OFF);
    lv_group_add_obj(def_group, ui_scr->usb_slave_imgbtn_videorec);
    ui_style_set(ui_scr->usb_slave_imgbtn_videorec, GUI_CTRL_IMGBTN);

    //Set style for usb_slave_imgbtn_videorec. Part: LV_PART_MAIN, State: LV_STATE_PRESSED
    lv_obj_set_style_bg_opa(ui_scr->usb_slave_imgbtn_videorec, 255, LV_PART_MAIN | LV_STATE_PRESSED);

    //Set style for usb_slave_imgbtn_videorec. Part: LV_PART_MAIN, State: LV_STATE_CHECKED
    lv_obj_set_style_bg_opa(ui_scr->usb_slave_imgbtn_videorec, 255, LV_PART_MAIN | LV_STATE_CHECKED);

    //Set style for usb_slave_imgbtn_videorec. Part: LV_PART_MAIN, State: LV_STATE_FOCUS_KEY
    lv_obj_set_style_bg_opa(ui_scr->usb_slave_imgbtn_videorec, 255, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_outline_width(ui_scr->usb_slave_imgbtn_videorec, 5, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_img_recolor(ui_scr->usb_slave_imgbtn_videorec, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_img_recolor_opa(ui_scr->usb_slave_imgbtn_videorec, 0, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_imgbtn_set_src(ui_scr->usb_slave_imgbtn_videorec, LV_IMGBTN_STATE_RELEASED, NULL, gui_get_res_path(GUI_RES_VIDEO_PNG), NULL);
    lv_imgbtn_set_src(ui_scr->usb_slave_imgbtn_videorec, LV_IMGBTN_STATE_PRESSED, NULL, gui_get_res_path(GUI_RES_VIDEO_ON_PNG), NULL);
    lv_imgbtn_set_src(ui_scr->usb_slave_imgbtn_videorec, LV_IMGBTN_STATE_CHECKED_RELEASED, NULL, gui_get_res_path(GUI_RES_VIDEO_PNG), NULL);
    lv_imgbtn_set_src(ui_scr->usb_slave_imgbtn_videorec, LV_IMGBTN_STATE_CHECKED_PRESSED, NULL, gui_get_res_path(GUI_RES_VIDEO_ON_PNG), NULL);
    lv_obj_add_flag(ui_scr->usb_slave_imgbtn_videorec, LV_OBJ_FLAG_CHECKABLE);
    ui_scr->usb_slave_imgbtn_videorec_label = lv_label_create(ui_scr->usb_slave_imgbtn_videorec);
    lv_label_set_text(ui_scr->usb_slave_imgbtn_videorec_label, "");
    lv_obj_set_style_pad_all(ui_scr->usb_slave_imgbtn_videorec, 0, LV_STATE_DEFAULT);
    lv_obj_align(ui_scr->usb_slave_imgbtn_videorec_label, LV_ALIGN_CENTER, 0, 0);

    //Write codes usb_slave_imgbtn_masstorage
    ui_scr->usb_slave_imgbtn_masstorage = lv_imgbtn_create(ui_scr->usb_slave_view_btnlist);
    lv_obj_set_pos(ui_scr->usb_slave_imgbtn_masstorage, 24, 33);
    lv_obj_set_size(ui_scr->usb_slave_imgbtn_masstorage, 128, 220);
    lv_obj_set_scrollbar_mode(ui_scr->usb_slave_imgbtn_masstorage, LV_SCROLLBAR_MODE_OFF);
    lv_group_add_obj(def_group, ui_scr->usb_slave_imgbtn_masstorage);
    ui_style_set(ui_scr->usb_slave_imgbtn_masstorage, GUI_CTRL_IMGBTN);

    //Set style for usb_slave_imgbtn_masstorage. Part: LV_PART_MAIN, State: LV_STATE_FOCUSED
    lv_obj_add_style(ui_scr->usb_slave_imgbtn_masstorage, &gui_imgbtn_main_focused_style, LV_PART_MAIN | LV_STATE_FOCUSED);

    //Set style for usb_slave_imgbtn_masstorage. Part: LV_PART_MAIN, State: LV_STATE_FOCUS_KEY
    lv_obj_set_style_outline_width(ui_scr->usb_slave_imgbtn_masstorage, 5, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_img_recolor(ui_scr->usb_slave_imgbtn_masstorage, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_img_recolor_opa(ui_scr->usb_slave_imgbtn_masstorage, 0, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_imgbtn_set_src(ui_scr->usb_slave_imgbtn_masstorage, LV_IMGBTN_STATE_RELEASED, NULL, gui_get_res_path(GUI_RES_MASS_PNG), NULL);
    lv_imgbtn_set_src(ui_scr->usb_slave_imgbtn_masstorage, LV_IMGBTN_STATE_PRESSED, NULL, gui_get_res_path(GUI_RES_MASS_ON_PNG), NULL);
    lv_imgbtn_set_src(ui_scr->usb_slave_imgbtn_masstorage, LV_IMGBTN_STATE_CHECKED_RELEASED, NULL, gui_get_res_path(GUI_RES_MASS_PNG), NULL);
    lv_imgbtn_set_src(ui_scr->usb_slave_imgbtn_masstorage, LV_IMGBTN_STATE_CHECKED_PRESSED, NULL, gui_get_res_path(GUI_RES_MASS_ON_PNG), NULL);
    lv_obj_add_flag(ui_scr->usb_slave_imgbtn_masstorage, LV_OBJ_FLAG_CHECKABLE);
    ui_scr->usb_slave_imgbtn_masstorage_label = lv_label_create(ui_scr->usb_slave_imgbtn_masstorage);
    lv_label_set_text(ui_scr->usb_slave_imgbtn_masstorage_label, "");
    lv_obj_set_style_pad_all(ui_scr->usb_slave_imgbtn_masstorage, 0, LV_STATE_DEFAULT);
    lv_obj_align(ui_scr->usb_slave_imgbtn_masstorage_label, LV_ALIGN_CENTER, 0, 0);

    //Write codes usb_slave_imgbtn_pccam
    ui_scr->usb_slave_imgbtn_pccam = lv_imgbtn_create(ui_scr->usb_slave_view_btnlist);
    lv_obj_set_pos(ui_scr->usb_slave_imgbtn_pccam, 221, 33);
    lv_obj_set_size(ui_scr->usb_slave_imgbtn_pccam, 128, 220);
    lv_obj_set_scrollbar_mode(ui_scr->usb_slave_imgbtn_pccam, LV_SCROLLBAR_MODE_OFF);
    lv_group_add_obj(def_group, ui_scr->usb_slave_imgbtn_pccam);
    ui_style_set(ui_scr->usb_slave_imgbtn_pccam, GUI_CTRL_IMGBTN);

    //Set style for usb_slave_imgbtn_pccam. Part: LV_PART_MAIN, State: LV_STATE_PRESSED
    lv_obj_set_style_bg_opa(ui_scr->usb_slave_imgbtn_pccam, 255, LV_PART_MAIN | LV_STATE_PRESSED);

    //Set style for usb_slave_imgbtn_pccam. Part: LV_PART_MAIN, State: LV_STATE_CHECKED
    lv_obj_set_style_bg_opa(ui_scr->usb_slave_imgbtn_pccam, 255, LV_PART_MAIN | LV_STATE_CHECKED);

    //Set style for usb_slave_imgbtn_pccam. Part: LV_PART_MAIN, State: LV_STATE_FOCUS_KEY
    lv_obj_set_style_bg_opa(ui_scr->usb_slave_imgbtn_pccam, 255, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_outline_width(ui_scr->usb_slave_imgbtn_pccam, 5, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_img_recolor(ui_scr->usb_slave_imgbtn_pccam, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_img_recolor_opa(ui_scr->usb_slave_imgbtn_pccam, 0, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_imgbtn_set_src(ui_scr->usb_slave_imgbtn_pccam, LV_IMGBTN_STATE_RELEASED, NULL, gui_get_res_path(GUI_RES_PCCAM_PNG), NULL);
    lv_imgbtn_set_src(ui_scr->usb_slave_imgbtn_pccam, LV_IMGBTN_STATE_PRESSED, NULL, gui_get_res_path(GUI_RES_PCCAM_ON_PNG), NULL);
    lv_imgbtn_set_src(ui_scr->usb_slave_imgbtn_pccam, LV_IMGBTN_STATE_CHECKED_RELEASED, NULL, gui_get_res_path(GUI_RES_PCCAM_PNG), NULL);
    lv_imgbtn_set_src(ui_scr->usb_slave_imgbtn_pccam, LV_IMGBTN_STATE_CHECKED_PRESSED, NULL, gui_get_res_path(GUI_RES_PCCAM_ON_PNG), NULL);
    lv_obj_add_flag(ui_scr->usb_slave_imgbtn_pccam, LV_OBJ_FLAG_CHECKABLE);
    ui_scr->usb_slave_imgbtn_pccam_label = lv_label_create(ui_scr->usb_slave_imgbtn_pccam);
    lv_label_set_text(ui_scr->usb_slave_imgbtn_pccam_label, "");
    lv_obj_set_style_pad_all(ui_scr->usb_slave_imgbtn_pccam, 0, LV_STATE_DEFAULT);
    lv_obj_align(ui_scr->usb_slave_imgbtn_pccam_label, LV_ALIGN_CENTER, 0, 0);

    lv_obj_update_layout(ui_scr->usb_slave);
    ui_scr->usb_slave_del = false;
    i18n_refresh_texts("usb_slave");

    //Init events for screen
    events_init_usb_slave(ui);
    return ui_scr->usb_slave;
}
void unload_scr_usb_slave(lv_ui *ui)
{
    ui_free_scr_ptr(ui, GUI_SCREEN_USB_SLAVE);
}

#endif
