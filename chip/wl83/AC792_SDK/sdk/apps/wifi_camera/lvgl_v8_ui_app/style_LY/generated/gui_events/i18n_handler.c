#include "app_config.h"
#ifdef CONFIG_UI_STYLE_LY_ENABLE
/*Generate Code, Do NOT Edit!*/
#include "./i18n_handler.h"

void i18n_refresh_texts(int32_t scr_id)
{

    if (scr_id == GUI_SCREEN_USB_SLAVE && guider_ui.usb_slave) {
        lv_ui_usb_slave *ui_scr = ui_get_scr_ptr(&guider_ui, GUI_SCREEN_USB_SLAVE);
        if (ui_scr->usb_slave_btn_usb_msd_label != NULL && lv_obj_is_valid(ui_scr->usb_slave_btn_usb_msd_label)) {
            lv_label_set_text(ui_scr->usb_slave_btn_usb_msd_label, _("msd"));
            const lv_font_t *font = _font("msd");
            if (font != NULL) {
                lv_obj_set_style_text_font(ui_scr->usb_slave_btn_usb_msd_label, font, LV_PART_MAIN | LV_STATE_DEFAULT);
                lv_obj_set_style_text_font(ui_scr->usb_slave_btn_usb_msd_label, font, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
            }
        }
        if (ui_scr->usb_slave_btn_pc_cam_label != NULL && lv_obj_is_valid(ui_scr->usb_slave_btn_pc_cam_label)) {
            lv_label_set_text(ui_scr->usb_slave_btn_pc_cam_label, _("pc_cam"));
            const lv_font_t *font = _font("pc_cam");
            if (font != NULL) {
                lv_obj_set_style_text_font(ui_scr->usb_slave_btn_pc_cam_label, font, LV_PART_MAIN | LV_STATE_DEFAULT);
                lv_obj_set_style_text_font(ui_scr->usb_slave_btn_pc_cam_label, font, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
            }
        }
        if (ui_scr->usb_slave_btn_video_rec_label != NULL && lv_obj_is_valid(ui_scr->usb_slave_btn_video_rec_label)) {
            lv_label_set_text(ui_scr->usb_slave_btn_video_rec_label, _("video_rec"));
            const lv_font_t *font = _font("video_rec");
            if (font != NULL) {
                lv_obj_set_style_text_font(ui_scr->usb_slave_btn_video_rec_label, font, LV_PART_MAIN | LV_STATE_DEFAULT);
                lv_obj_set_style_text_font(ui_scr->usb_slave_btn_video_rec_label, font, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
            }
        }
        if (ui_scr->usb_slave_btn_1_label != NULL && lv_obj_is_valid(ui_scr->usb_slave_btn_1_label)) {
            lv_label_set_text(ui_scr->usb_slave_btn_1_label, _("video_dashboard"));
            const lv_font_t *font = _font("video_dashboard");
            if (font != NULL) {
                lv_obj_set_style_text_font(ui_scr->usb_slave_btn_1_label, font, LV_PART_MAIN | LV_STATE_DEFAULT);
                lv_obj_set_style_text_font(ui_scr->usb_slave_btn_1_label, font, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
            }
        }
    }

    if (scr_id == GUI_SCREEN_VIDEO_REC && guider_ui.video_rec) {
        lv_ui_video_rec *ui_scr = ui_get_scr_ptr(&guider_ui, GUI_SCREEN_VIDEO_REC);
        if (ui_scr->video_rec_lbl_1 != NULL && lv_obj_is_valid(ui_scr->video_rec_lbl_1)) {
            lv_label_set_text(ui_scr->video_rec_lbl_1, _("resolution"));
            const lv_font_t *font = _font("resolution");
            if (font != NULL) {
                lv_obj_set_style_text_font(ui_scr->video_rec_lbl_1, font, LV_PART_MAIN | LV_STATE_DEFAULT);
            }
        }

        if (ui_scr->video_rec_lbl_3 != NULL && lv_obj_is_valid(ui_scr->video_rec_lbl_3)) {
            lv_label_set_text(ui_scr->video_rec_lbl_3, _("doublerec"));
            const lv_font_t *font = _font("doublerec");
            if (font != NULL) {
                lv_obj_set_style_text_font(ui_scr->video_rec_lbl_3, font, LV_PART_MAIN | LV_STATE_DEFAULT);
            }
        }

        if (ui_scr->video_rec_lbl_4 != NULL && lv_obj_is_valid(ui_scr->video_rec_lbl_4)) {
            lv_label_set_text(ui_scr->video_rec_lbl_4, _("cycrec"));
            const lv_font_t *font = _font("cycrec");
            if (font != NULL) {
                lv_obj_set_style_text_font(ui_scr->video_rec_lbl_4, font, LV_PART_MAIN | LV_STATE_DEFAULT);
            }
        }

        if (ui_scr->video_rec_lbl_5 != NULL && lv_obj_is_valid(ui_scr->video_rec_lbl_5)) {
            lv_label_set_text(ui_scr->video_rec_lbl_5, _("gaprec"));
            const lv_font_t *font = _font("gaprec");
            if (font != NULL) {
                lv_obj_set_style_text_font(ui_scr->video_rec_lbl_5, font, LV_PART_MAIN | LV_STATE_DEFAULT);
            }
        }

        if (ui_scr->video_rec_lbl_6 != NULL && lv_obj_is_valid(ui_scr->video_rec_lbl_6)) {
            lv_label_set_text(ui_scr->video_rec_lbl_6, _("hdr"));
            const lv_font_t *font = _font("hdr");
            if (font != NULL) {
                lv_obj_set_style_text_font(ui_scr->video_rec_lbl_6, font, LV_PART_MAIN | LV_STATE_DEFAULT);
            }
        }

        if (ui_scr->video_rec_lbl_7 != NULL && lv_obj_is_valid(ui_scr->video_rec_lbl_7)) {
            lv_label_set_text(ui_scr->video_rec_lbl_7, _("exposure"));
            const lv_font_t *font = _font("exposure");
            if (font != NULL) {
                lv_obj_set_style_text_font(ui_scr->video_rec_lbl_7, font, LV_PART_MAIN | LV_STATE_DEFAULT);
            }
        }

        if (ui_scr->video_rec_lbl_8 != NULL && lv_obj_is_valid(ui_scr->video_rec_lbl_8)) {
            lv_label_set_text(ui_scr->video_rec_lbl_8, _("motion"));
            const lv_font_t *font = _font("motion");
            if (font != NULL) {
                lv_obj_set_style_text_font(ui_scr->video_rec_lbl_8, font, LV_PART_MAIN | LV_STATE_DEFAULT);
            }
        }

        if (ui_scr->video_rec_lbl_9 != NULL && lv_obj_is_valid(ui_scr->video_rec_lbl_9)) {
            lv_label_set_text(ui_scr->video_rec_lbl_9, _("record"));
            const lv_font_t *font = _font("record");
            if (font != NULL) {
                lv_obj_set_style_text_font(ui_scr->video_rec_lbl_9, font, LV_PART_MAIN | LV_STATE_DEFAULT);
            }
        }

        if (ui_scr->video_rec_lbl_10 != NULL && lv_obj_is_valid(ui_scr->video_rec_lbl_10)) {
            lv_label_set_text(ui_scr->video_rec_lbl_10, _("date"));
            const lv_font_t *font = _font("date");
            if (font != NULL) {
                lv_obj_set_style_text_font(ui_scr->video_rec_lbl_10, font, LV_PART_MAIN | LV_STATE_DEFAULT);
            }
        }

        if (ui_scr->video_rec_lbl_11 != NULL && lv_obj_is_valid(ui_scr->video_rec_lbl_11)) {
            lv_label_set_text(ui_scr->video_rec_lbl_11, _("gsensor"));
            const lv_font_t *font = _font("gsensor");
            if (font != NULL) {
                lv_obj_set_style_text_font(ui_scr->video_rec_lbl_11, font, LV_PART_MAIN | LV_STATE_DEFAULT);
            }
        }

        if (ui_scr->video_rec_lbl_12 != NULL && lv_obj_is_valid(ui_scr->video_rec_lbl_12)) {
            lv_label_set_text(ui_scr->video_rec_lbl_12, _("guard"));
            const lv_font_t *font = _font("guard");
            if (font != NULL) {
                lv_obj_set_style_text_font(ui_scr->video_rec_lbl_12, font, LV_PART_MAIN | LV_STATE_DEFAULT);
            }
        }

        if (ui_scr->video_rec_lbl_13 != NULL && lv_obj_is_valid(ui_scr->video_rec_lbl_13)) {
            lv_label_set_text(ui_scr->video_rec_lbl_13, _("carnum"));
            const lv_font_t *font = _font("carnum");
            if (font != NULL) {
                lv_obj_set_style_text_font(ui_scr->video_rec_lbl_13, font, LV_PART_MAIN | LV_STATE_DEFAULT);
            }
        }

        if (ui_scr->video_rec_lbl_14 != NULL && lv_obj_is_valid(ui_scr->video_rec_lbl_14)) {
            lv_label_set_text(ui_scr->video_rec_lbl_14, _("lamp"));
            const lv_font_t *font = _font("lamp");
            if (font != NULL) {
                lv_obj_set_style_text_font(ui_scr->video_rec_lbl_14, font, LV_PART_MAIN | LV_STATE_DEFAULT);
            }
        }

    }

    if (scr_id == GUI_SCREEN_SYS_PROMPT && guider_ui.sys_prompt) {
        lv_ui_sys_prompt *ui_scr = ui_get_scr_ptr(&guider_ui, GUI_SCREEN_SYS_PROMPT);
        if (ui_scr->sys_prompt_lbl_warn != NULL && lv_obj_is_valid(ui_scr->sys_prompt_lbl_warn)) {
            lv_label_set_text(ui_scr->sys_prompt_lbl_warn, _("sd_update"));
            const lv_font_t *font = _font("sd_update");
            if (font != NULL) {
                lv_obj_set_style_text_font(ui_scr->sys_prompt_lbl_warn, font, LV_PART_MAIN | LV_STATE_DEFAULT);
            }
        }

    }

    if (scr_id == GUI_SCREEN_SYS_SETTING && guider_ui.sys_setting) {
        lv_ui_sys_setting *ui_scr = ui_get_scr_ptr(&guider_ui, GUI_SCREEN_SYS_SETTING);
        if (ui_scr->sys_setting_lbl_1 != NULL && lv_obj_is_valid(ui_scr->sys_setting_lbl_1)) {
            lv_label_set_text(ui_scr->sys_setting_lbl_1, _("lcdprotect"));
            const lv_font_t *font = _font("lcdprotect");
            if (font != NULL) {
                lv_obj_set_style_text_font(ui_scr->sys_setting_lbl_1, font, LV_PART_MAIN | LV_STATE_DEFAULT);
            }
        }

        if (ui_scr->sys_setting_lbl_2 != NULL && lv_obj_is_valid(ui_scr->sys_setting_lbl_2)) {
            lv_label_set_text(ui_scr->sys_setting_lbl_2, _("poweroff"));
            const lv_font_t *font = _font("poweroff");
            if (font != NULL) {
                lv_obj_set_style_text_font(ui_scr->sys_setting_lbl_2, font, LV_PART_MAIN | LV_STATE_DEFAULT);
            }
        }

        if (ui_scr->sys_setting_lbl_3 != NULL && lv_obj_is_valid(ui_scr->sys_setting_lbl_3)) {
            lv_label_set_text(ui_scr->sys_setting_lbl_3, _("frequency"));
            const lv_font_t *font = _font("frequency");
            if (font != NULL) {
                lv_obj_set_style_text_font(ui_scr->sys_setting_lbl_3, font, LV_PART_MAIN | LV_STATE_DEFAULT);
            }
        }

        if (ui_scr->sys_setting_lbl_4 != NULL && lv_obj_is_valid(ui_scr->sys_setting_lbl_4)) {
            lv_label_set_text(ui_scr->sys_setting_lbl_4, _("speaker"));
            const lv_font_t *font = _font("speaker");
            if (font != NULL) {
                lv_obj_set_style_text_font(ui_scr->sys_setting_lbl_4, font, LV_PART_MAIN | LV_STATE_DEFAULT);
            }
        }

        if (ui_scr->sys_setting_lbl_5 != NULL && lv_obj_is_valid(ui_scr->sys_setting_lbl_5)) {
            lv_label_set_text(ui_scr->sys_setting_lbl_5, _("language"));
            const lv_font_t *font = _font("language");
            if (font != NULL) {
                lv_obj_set_style_text_font(ui_scr->sys_setting_lbl_5, font, LV_PART_MAIN | LV_STATE_DEFAULT);
            }
        }

        if (ui_scr->sys_setting_lbl_6 != NULL && lv_obj_is_valid(ui_scr->sys_setting_lbl_6)) {
            lv_label_set_text(ui_scr->sys_setting_lbl_6, _("date"));
            const lv_font_t *font = _font("date");
            if (font != NULL) {
                lv_obj_set_style_text_font(ui_scr->sys_setting_lbl_6, font, LV_PART_MAIN | LV_STATE_DEFAULT);
            }
        }

        if (ui_scr->sys_setting_lbl_7 != NULL && lv_obj_is_valid(ui_scr->sys_setting_lbl_7)) {
            lv_label_set_text(ui_scr->sys_setting_lbl_7, _("tv_mode"));
            const lv_font_t *font = _font("tv_mode");
            if (font != NULL) {
                lv_obj_set_style_text_font(ui_scr->sys_setting_lbl_7, font, LV_PART_MAIN | LV_STATE_DEFAULT);
            }
        }

        if (ui_scr->sys_setting_lbl_8 != NULL && lv_obj_is_valid(ui_scr->sys_setting_lbl_8)) {
            lv_label_set_text(ui_scr->sys_setting_lbl_8, _("formatting"));
            const lv_font_t *font = _font("formatting");
            if (font != NULL) {
                lv_obj_set_style_text_font(ui_scr->sys_setting_lbl_8, font, LV_PART_MAIN | LV_STATE_DEFAULT);
            }
        }

        if (ui_scr->sys_setting_lbl_9 != NULL && lv_obj_is_valid(ui_scr->sys_setting_lbl_9)) {
            lv_label_set_text(ui_scr->sys_setting_lbl_9, _("reset"));
            const lv_font_t *font = _font("reset");
            if (font != NULL) {
                lv_obj_set_style_text_font(ui_scr->sys_setting_lbl_9, font, LV_PART_MAIN | LV_STATE_DEFAULT);
            }
        }

        if (ui_scr->sys_setting_lbl_10 != NULL && lv_obj_is_valid(ui_scr->sys_setting_lbl_10)) {
            lv_label_set_text(ui_scr->sys_setting_lbl_10, _("ver"));
            const lv_font_t *font = _font("ver");
            if (font != NULL) {
                lv_obj_set_style_text_font(ui_scr->sys_setting_lbl_10, font, LV_PART_MAIN | LV_STATE_DEFAULT);
            }
        }

    }

    if (scr_id == GUI_SCREEN_VIDEO_PHOTO && guider_ui.video_photo) {
        lv_ui_video_photo *ui_scr = ui_get_scr_ptr(&guider_ui, GUI_SCREEN_VIDEO_PHOTO);
        if (ui_scr->video_photo_lbl_1 != NULL && lv_obj_is_valid(ui_scr->video_photo_lbl_1)) {
            lv_label_set_text(ui_scr->video_photo_lbl_1, _("shoot"));
            const lv_font_t *font = _font("shoot");
            if (font != NULL) {
                lv_obj_set_style_text_font(ui_scr->video_photo_lbl_1, font, LV_PART_MAIN | LV_STATE_DEFAULT);
            }
        }

        if (ui_scr->video_photo_lbl_2 != NULL && lv_obj_is_valid(ui_scr->video_photo_lbl_2)) {
            lv_label_set_text(ui_scr->video_photo_lbl_2, _("reso"));
            const lv_font_t *font = _font("reso");
            if (font != NULL) {
                lv_obj_set_style_text_font(ui_scr->video_photo_lbl_2, font, LV_PART_MAIN | LV_STATE_DEFAULT);
            }
        }

        if (ui_scr->video_photo_lbl_3 != NULL && lv_obj_is_valid(ui_scr->video_photo_lbl_3)) {
            lv_label_set_text(ui_scr->video_photo_lbl_3, _("shots"));
            const lv_font_t *font = _font("shots");
            if (font != NULL) {
                lv_obj_set_style_text_font(ui_scr->video_photo_lbl_3, font, LV_PART_MAIN | LV_STATE_DEFAULT);
            }
        }

        if (ui_scr->video_photo_lbl_4 != NULL && lv_obj_is_valid(ui_scr->video_photo_lbl_4)) {
            lv_label_set_text(ui_scr->video_photo_lbl_4, _("quality"));
            const lv_font_t *font = _font("quality");
            if (font != NULL) {
                lv_obj_set_style_text_font(ui_scr->video_photo_lbl_4, font, LV_PART_MAIN | LV_STATE_DEFAULT);
            }
        }

        if (ui_scr->video_photo_lbl_5 != NULL && lv_obj_is_valid(ui_scr->video_photo_lbl_5)) {
            lv_label_set_text(ui_scr->video_photo_lbl_5, _("sharpness"));
            const lv_font_t *font = _font("sharpness");
            if (font != NULL) {
                lv_obj_set_style_text_font(ui_scr->video_photo_lbl_5, font, LV_PART_MAIN | LV_STATE_DEFAULT);
            }
        }

        if (ui_scr->video_photo_lbl_6 != NULL && lv_obj_is_valid(ui_scr->video_photo_lbl_6)) {
            lv_label_set_text(ui_scr->video_photo_lbl_6, _("awb"));
            const lv_font_t *font = _font("awb");
            if (font != NULL) {
                lv_obj_set_style_text_font(ui_scr->video_photo_lbl_6, font, LV_PART_MAIN | LV_STATE_DEFAULT);
            }
        }

        if (ui_scr->video_photo_lbl_7 != NULL && lv_obj_is_valid(ui_scr->video_photo_lbl_7)) {
            lv_label_set_text(ui_scr->video_photo_lbl_7, _("color"));
            const lv_font_t *font = _font("color");
            if (font != NULL) {
                lv_obj_set_style_text_font(ui_scr->video_photo_lbl_7, font, LV_PART_MAIN | LV_STATE_DEFAULT);
            }
        }

        if (ui_scr->video_photo_lbl_8 != NULL && lv_obj_is_valid(ui_scr->video_photo_lbl_8)) {
            lv_label_set_text(ui_scr->video_photo_lbl_8, _("iso"));
            const lv_font_t *font = _font("iso");
            if (font != NULL) {
                lv_obj_set_style_text_font(ui_scr->video_photo_lbl_8, font, LV_PART_MAIN | LV_STATE_DEFAULT);
            }
        }

        if (ui_scr->video_photo_lbl_9 != NULL && lv_obj_is_valid(ui_scr->video_photo_lbl_9)) {
            lv_label_set_text(ui_scr->video_photo_lbl_9, _("exposure"));
            const lv_font_t *font = _font("exposure");
            if (font != NULL) {
                lv_obj_set_style_text_font(ui_scr->video_photo_lbl_9, font, LV_PART_MAIN | LV_STATE_DEFAULT);
            }
        }

        if (ui_scr->video_photo_lbl_10 != NULL && lv_obj_is_valid(ui_scr->video_photo_lbl_10)) {
            lv_label_set_text(ui_scr->video_photo_lbl_10, _("handshake"));
            const lv_font_t *font = _font("handshake");
            if (font != NULL) {
                lv_obj_set_style_text_font(ui_scr->video_photo_lbl_10, font, LV_PART_MAIN | LV_STATE_DEFAULT);
            }
        }

        if (ui_scr->video_photo_lbl_11 != NULL && lv_obj_is_valid(ui_scr->video_photo_lbl_11)) {
            lv_label_set_text(ui_scr->video_photo_lbl_11, _("preview"));
            const lv_font_t *font = _font("preview");
            if (font != NULL) {
                lv_obj_set_style_text_font(ui_scr->video_photo_lbl_11, font, LV_PART_MAIN | LV_STATE_DEFAULT);
            }
        }

        if (ui_scr->video_photo_lbl_12 != NULL && lv_obj_is_valid(ui_scr->video_photo_lbl_12)) {
            lv_label_set_text(ui_scr->video_photo_lbl_12, _("date_label"));
            const lv_font_t *font = _font("date_label");
            if (font != NULL) {
                lv_obj_set_style_text_font(ui_scr->video_photo_lbl_12, font, LV_PART_MAIN | LV_STATE_DEFAULT);
            }
        }

    }

    if (scr_id == GUI_SCREEN_VIDEO_FILE && guider_ui.video_file) {
        lv_ui_video_file *ui_scr = ui_get_scr_ptr(&guider_ui, GUI_SCREEN_VIDEO_FILE);
        if (ui_scr->video_file_lbl_2 != NULL && lv_obj_is_valid(ui_scr->video_file_lbl_2)) {
            lv_label_set_text(ui_scr->video_file_lbl_2, _("delete"));
            const lv_font_t *font = _font("delete");
            if (font != NULL) {
                lv_obj_set_style_text_font(ui_scr->video_file_lbl_2, font, LV_PART_MAIN | LV_STATE_DEFAULT);
            }
        }

        if (ui_scr->video_file_lbl_3 != NULL && lv_obj_is_valid(ui_scr->video_file_lbl_3)) {
            lv_label_set_text(ui_scr->video_file_lbl_3, _("protection"));
            const lv_font_t *font = _font("protection");
            if (font != NULL) {
                lv_obj_set_style_text_font(ui_scr->video_file_lbl_3, font, LV_PART_MAIN | LV_STATE_DEFAULT);
            }
        }

    }

    if (scr_id == GUI_SCREEN_LINE_DRIFT && guider_ui.line_drift) {
        lv_ui_line_drift *ui_scr = ui_get_scr_ptr(&guider_ui, GUI_SCREEN_LINE_DRIFT);
        if (ui_scr->line_drift_btn_horizon_label != NULL && lv_obj_is_valid(ui_scr->line_drift_btn_horizon_label)) {
            lv_label_set_text(ui_scr->line_drift_btn_horizon_label, _("line_drift_horizon"));
            const lv_font_t *font = _font("line_drift_horizon");
            if (font != NULL) {
                lv_obj_set_style_text_font(ui_scr->line_drift_btn_horizon_label, font, LV_PART_MAIN | LV_STATE_DEFAULT);
            }
        }
        if (ui_scr->line_drift_btn_carhead_label != NULL && lv_obj_is_valid(ui_scr->line_drift_btn_carhead_label)) {
            lv_label_set_text(ui_scr->line_drift_btn_carhead_label, _("line_drift_car"));
            const lv_font_t *font = _font("line_drift_car");
            if (font != NULL) {
                lv_obj_set_style_text_font(ui_scr->line_drift_btn_carhead_label, font, LV_PART_MAIN | LV_STATE_DEFAULT);
            }
        }
        if (ui_scr->line_drift_lbl_7 != NULL && lv_obj_is_valid(ui_scr->line_drift_lbl_7)) {
            lv_label_set_text(ui_scr->line_drift_lbl_7, _("YES"));
            const lv_font_t *font = _font("YES");
            if (font != NULL) {
                lv_obj_set_style_text_font(ui_scr->line_drift_lbl_7, font, LV_PART_MAIN | LV_STATE_DEFAULT);
                lv_obj_set_style_text_font(ui_scr->line_drift_lbl_7, font, LV_PART_MAIN | LV_STATE_FOCUSED);
            }
        }

        if (ui_scr->line_drift_lbl_6 != NULL && lv_obj_is_valid(ui_scr->line_drift_lbl_6)) {
            lv_label_set_text(ui_scr->line_drift_lbl_6, _("CANCEL"));
            const lv_font_t *font = _font("CANCEL");
            if (font != NULL) {
                lv_obj_set_style_text_font(ui_scr->line_drift_lbl_6, font, LV_PART_MAIN | LV_STATE_DEFAULT);
                lv_obj_set_style_text_font(ui_scr->line_drift_lbl_6, font, LV_PART_MAIN | LV_STATE_FOCUSED);
            }
        }

    }

    if (scr_id == GUI_SCREEN_SYS_POPWIN && guider_ui.sys_popwin) {
        lv_ui_sys_popwin *ui_scr = ui_get_scr_ptr(&guider_ui, GUI_SCREEN_SYS_POPWIN);
        if (ui_scr->sys_popwin_lbl_1 != NULL && lv_obj_is_valid(ui_scr->sys_popwin_lbl_1)) {
            lv_label_set_text(ui_scr->sys_popwin_lbl_1, _("del_file"));
            const lv_font_t *font = _font("del_file");
            if (font != NULL) {
                lv_obj_set_style_text_font(ui_scr->sys_popwin_lbl_1, font, LV_PART_MAIN | LV_STATE_DEFAULT);
            }
        }

        if (ui_scr->sys_popwin_btn_1_label != NULL && lv_obj_is_valid(ui_scr->sys_popwin_btn_1_label)) {
            lv_label_set_text(ui_scr->sys_popwin_btn_1_label, _("cancel"));
            const lv_font_t *font = _font("cancel");
            if (font != NULL) {
                lv_obj_set_style_text_font(ui_scr->sys_popwin_btn_1_label, font, LV_PART_MAIN | LV_STATE_DEFAULT);
                lv_obj_set_style_text_font(ui_scr->sys_popwin_btn_1_label, font, LV_PART_MAIN | LV_STATE_FOCUSED);
            }
        }
        if (ui_scr->sys_popwin_btn_2_label != NULL && lv_obj_is_valid(ui_scr->sys_popwin_btn_2_label)) {
            lv_label_set_text(ui_scr->sys_popwin_btn_2_label, _("ensure"));
            const lv_font_t *font = _font("ensure");
            if (font != NULL) {
                lv_obj_set_style_text_font(ui_scr->sys_popwin_btn_2_label, font, LV_PART_MAIN | LV_STATE_DEFAULT);
                lv_obj_set_style_text_font(ui_scr->sys_popwin_btn_2_label, font, LV_PART_MAIN | LV_STATE_FOCUSED);
            }
        }
    }

    if (scr_id == GUI_SCREEN_VIDEO_DEC && guider_ui.video_dec) {
        lv_ui_video_dec *ui_scr = ui_get_scr_ptr(&guider_ui, GUI_SCREEN_VIDEO_DEC);
        if (ui_scr->video_dec_lbl_1 != NULL && lv_obj_is_valid(ui_scr->video_dec_lbl_1)) {
            lv_label_set_text(ui_scr->video_dec_lbl_1, _("delete"));
            const lv_font_t *font = _font("delete");
            if (font != NULL) {
                lv_obj_set_style_text_font(ui_scr->video_dec_lbl_1, font, LV_PART_MAIN | LV_STATE_DEFAULT);
            }
        }

        if (ui_scr->video_dec_lbl_2 != NULL && lv_obj_is_valid(ui_scr->video_dec_lbl_2)) {
            lv_label_set_text(ui_scr->video_dec_lbl_2, _("protection"));
            const lv_font_t *font = _font("protection");
            if (font != NULL) {
                lv_obj_set_style_text_font(ui_scr->video_dec_lbl_2, font, LV_PART_MAIN | LV_STATE_DEFAULT);
            }
        }

    }

    if (scr_id == GUI_SCREEN_VIDEO_DEC_OPTIONS && guider_ui.video_dec_options) {
        lv_ui_video_dec_options *ui_scr = ui_get_scr_ptr(&guider_ui, GUI_SCREEN_VIDEO_DEC_OPTIONS);
        if (ui_scr->video_dec_options_lbl_1 != NULL && lv_obj_is_valid(ui_scr->video_dec_options_lbl_1)) {
            lv_label_set_text(ui_scr->video_dec_options_lbl_1, _("del_file"));
            const lv_font_t *font = _font("del_file");
            if (font != NULL) {
                lv_obj_set_style_text_font(ui_scr->video_dec_options_lbl_1, font, LV_PART_MAIN | LV_STATE_DEFAULT);
            }
        }

        if (ui_scr->video_dec_options_btn_1_label != NULL && lv_obj_is_valid(ui_scr->video_dec_options_btn_1_label)) {
            lv_label_set_text(ui_scr->video_dec_options_btn_1_label, _("cancel"));
            const lv_font_t *font = _font("cancel");
            if (font != NULL) {
                lv_obj_set_style_text_font(ui_scr->video_dec_options_btn_1_label, font, LV_PART_MAIN | LV_STATE_DEFAULT);
                lv_obj_set_style_text_font(ui_scr->video_dec_options_btn_1_label, font, LV_PART_MAIN | LV_STATE_FOCUSED);
            }
        }
        if (ui_scr->video_dec_options_btn_2_label != NULL && lv_obj_is_valid(ui_scr->video_dec_options_btn_2_label)) {
            lv_label_set_text(ui_scr->video_dec_options_btn_2_label, _("ensure"));
            const lv_font_t *font = _font("ensure");
            if (font != NULL) {
                lv_obj_set_style_text_font(ui_scr->video_dec_options_btn_2_label, font, LV_PART_MAIN | LV_STATE_DEFAULT);
                lv_obj_set_style_text_font(ui_scr->video_dec_options_btn_2_label, font, LV_PART_MAIN | LV_STATE_FOCUSED);
            }
        }
    }
}

void i18n_refresh_all_texts()
{
    for (int i = 0; i < sizeof(gui_screen_ids) / sizeof(gui_screen_ids[0]); i++) {
        i18n_refresh_texts(gui_screen_ids[i]);
    }
}

#endif
