#include "app_config.h"
#ifdef CONFIG_UI_STYLE_JL_ENABLE
/*Generate Code, Do NOT Edit!*/
#include "./i18n_handler.h"

void i18n_refresh_texts(const char *page_name)
{
    if (page_name == NULL) {
        return;
    }

    if (strcmp(page_name, "video_rec") == 0 && guider_ui.video_rec) {
        lv_ui_video_rec *ui_scr = ui_get_scr_ptr(&guider_ui, GUI_SCREEN_VIDEO_REC);
        if (ui_scr->video_rec_lbl_5 != NULL && lv_obj_is_valid(ui_scr->video_rec_lbl_5)) {
            lv_label_set_text(ui_scr->video_rec_lbl_5, _("resolution"));
            const lv_font_t *font = _font("resolution");
            if (font != NULL) {
                lv_obj_set_style_text_font(ui_scr->video_rec_lbl_5, font, LV_PART_MAIN | LV_STATE_DEFAULT);
            }
        }

        if (ui_scr->video_rec_lbl_6 != NULL && lv_obj_is_valid(ui_scr->video_rec_lbl_6)) {
            lv_label_set_text(ui_scr->video_rec_lbl_6, _("doublerec"));
            const lv_font_t *font = _font("doublerec");
            if (font != NULL) {
                lv_obj_set_style_text_font(ui_scr->video_rec_lbl_6, font, LV_PART_MAIN | LV_STATE_DEFAULT);
            }
        }

        if (ui_scr->video_rec_lbl_7 != NULL && lv_obj_is_valid(ui_scr->video_rec_lbl_7)) {
            lv_label_set_text(ui_scr->video_rec_lbl_7, _("cycrec"));
            const lv_font_t *font = _font("cycrec");
            if (font != NULL) {
                lv_obj_set_style_text_font(ui_scr->video_rec_lbl_7, font, LV_PART_MAIN | LV_STATE_DEFAULT);
            }
        }

        if (ui_scr->video_rec_lbl_8 != NULL && lv_obj_is_valid(ui_scr->video_rec_lbl_8)) {
            lv_label_set_text(ui_scr->video_rec_lbl_8, _("gaprec"));
            const lv_font_t *font = _font("gaprec");
            if (font != NULL) {
                lv_obj_set_style_text_font(ui_scr->video_rec_lbl_8, font, LV_PART_MAIN | LV_STATE_DEFAULT);
            }
        }

        if (ui_scr->video_rec_lbl_14 != NULL && lv_obj_is_valid(ui_scr->video_rec_lbl_14)) {
            lv_label_set_text(ui_scr->video_rec_lbl_14, _("gsensor"));
            const lv_font_t *font = _font("gsensor");
            if (font != NULL) {
                lv_obj_set_style_text_font(ui_scr->video_rec_lbl_14, font, LV_PART_MAIN | LV_STATE_DEFAULT);
            }
        }

        if (ui_scr->video_rec_lbl_15 != NULL && lv_obj_is_valid(ui_scr->video_rec_lbl_15)) {
            lv_label_set_text(ui_scr->video_rec_lbl_15, _("exposure"));
            const lv_font_t *font = _font("exposure");
            if (font != NULL) {
                lv_obj_set_style_text_font(ui_scr->video_rec_lbl_15, font, LV_PART_MAIN | LV_STATE_DEFAULT);
            }
        }

        if (ui_scr->video_rec_lbl_16 != NULL && lv_obj_is_valid(ui_scr->video_rec_lbl_16)) {
            lv_label_set_text(ui_scr->video_rec_lbl_16, _("motion"));
            const lv_font_t *font = _font("motion");
            if (font != NULL) {
                lv_obj_set_style_text_font(ui_scr->video_rec_lbl_16, font, LV_PART_MAIN | LV_STATE_DEFAULT);
            }
        }

        if (ui_scr->video_rec_lbl_17 != NULL && lv_obj_is_valid(ui_scr->video_rec_lbl_17)) {
            lv_label_set_text(ui_scr->video_rec_lbl_17, _("date"));
            const lv_font_t *font = _font("date");
            if (font != NULL) {
                lv_obj_set_style_text_font(ui_scr->video_rec_lbl_17, font, LV_PART_MAIN | LV_STATE_DEFAULT);
            }
        }

        if (ui_scr->video_rec_lbl_18 != NULL && lv_obj_is_valid(ui_scr->video_rec_lbl_18)) {
            lv_label_set_text(ui_scr->video_rec_lbl_18, _("record"));
            const lv_font_t *font = _font("record");
            if (font != NULL) {
                lv_obj_set_style_text_font(ui_scr->video_rec_lbl_18, font, LV_PART_MAIN | LV_STATE_DEFAULT);
            }
        }

        if (ui_scr->video_rec_lbl_19 != NULL && lv_obj_is_valid(ui_scr->video_rec_lbl_19)) {
            lv_label_set_text(ui_scr->video_rec_lbl_19, _("guard"));
            const lv_font_t *font = _font("guard");
            if (font != NULL) {
                lv_obj_set_style_text_font(ui_scr->video_rec_lbl_19, font, LV_PART_MAIN | LV_STATE_DEFAULT);
            }
        }

        if (ui_scr->video_rec_lbl_20 != NULL && lv_obj_is_valid(ui_scr->video_rec_lbl_20)) {
            lv_label_set_text(ui_scr->video_rec_lbl_20, _("carnum"));
            const lv_font_t *font = _font("carnum");
            if (font != NULL) {
                lv_obj_set_style_text_font(ui_scr->video_rec_lbl_20, font, LV_PART_MAIN | LV_STATE_DEFAULT);
            }
        }

        if (ui_scr->video_rec_lbl_menu_title != NULL && lv_obj_is_valid(ui_scr->video_rec_lbl_menu_title)) {
            lv_label_set_text(ui_scr->video_rec_lbl_menu_title, _("language"));
            const lv_font_t *font = _font("language");
            if (font != NULL) {
                lv_obj_set_style_text_font(ui_scr->video_rec_lbl_menu_title, font, LV_PART_MAIN | LV_STATE_DEFAULT);
            }
        }

        if (ui_scr->video_rec_lbl_funkey1_label != NULL && lv_obj_is_valid(ui_scr->video_rec_lbl_funkey1_label)) {
            lv_label_set_text(ui_scr->video_rec_lbl_funkey1_label, _("YES"));
            const lv_font_t *font = _font("YES");
            if (font != NULL) {
                lv_obj_set_style_text_font(ui_scr->video_rec_lbl_funkey1_label, font, LV_PART_MAIN | LV_STATE_DEFAULT);
                lv_obj_set_style_text_font(ui_scr->video_rec_lbl_funkey1_label, font, LV_PART_MAIN | LV_STATE_FOCUSED);
                lv_obj_set_style_text_font(ui_scr->video_rec_lbl_funkey1_label, font, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
            }
        }
        if (ui_scr->video_rec_lbl_funkey2_label != NULL && lv_obj_is_valid(ui_scr->video_rec_lbl_funkey2_label)) {
            lv_label_set_text(ui_scr->video_rec_lbl_funkey2_label, _("YES"));
            const lv_font_t *font = _font("YES");
            if (font != NULL) {
                lv_obj_set_style_text_font(ui_scr->video_rec_lbl_funkey2_label, font, LV_PART_MAIN | LV_STATE_DEFAULT);
                lv_obj_set_style_text_font(ui_scr->video_rec_lbl_funkey2_label, font, LV_PART_MAIN | LV_STATE_FOCUSED);
                lv_obj_set_style_text_font(ui_scr->video_rec_lbl_funkey2_label, font, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
            }
        }
        if (ui_scr->video_rec_lbl_funkey3_label != NULL && lv_obj_is_valid(ui_scr->video_rec_lbl_funkey3_label)) {
            lv_label_set_text(ui_scr->video_rec_lbl_funkey3_label, _("YES"));
            const lv_font_t *font = _font("YES");
            if (font != NULL) {
                lv_obj_set_style_text_font(ui_scr->video_rec_lbl_funkey3_label, font, LV_PART_MAIN | LV_STATE_DEFAULT);
                lv_obj_set_style_text_font(ui_scr->video_rec_lbl_funkey3_label, font, LV_PART_MAIN | LV_STATE_FOCUSED);
                lv_obj_set_style_text_font(ui_scr->video_rec_lbl_funkey3_label, font, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
            }
        }
        if (ui_scr->video_rec_lbl_funkey4_label != NULL && lv_obj_is_valid(ui_scr->video_rec_lbl_funkey4_label)) {
            lv_label_set_text(ui_scr->video_rec_lbl_funkey4_label, _("YES"));
            const lv_font_t *font = _font("YES");
            if (font != NULL) {
                lv_obj_set_style_text_font(ui_scr->video_rec_lbl_funkey4_label, font, LV_PART_MAIN | LV_STATE_DEFAULT);
                lv_obj_set_style_text_font(ui_scr->video_rec_lbl_funkey4_label, font, LV_PART_MAIN | LV_STATE_FOCUSED);
                lv_obj_set_style_text_font(ui_scr->video_rec_lbl_funkey4_label, font, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
            }
        }
    }

    if (strcmp(page_name, "home_page") == 0 && guider_ui.home_page) {
        lv_ui_home_page *ui_scr = ui_get_scr_ptr(&guider_ui, GUI_SCREEN_HOME_PAGE);
        if (ui_scr->home_page_lbl_3 != NULL && lv_obj_is_valid(ui_scr->home_page_lbl_3)) {
            lv_label_set_text(ui_scr->home_page_lbl_3, _("sunny"));
            const lv_font_t *font = _font("sunny");
            if (font != NULL) {
                lv_obj_set_style_text_font(ui_scr->home_page_lbl_3, font, LV_PART_MAIN | LV_STATE_DEFAULT);
            }
        }

        if (ui_scr->home_page_lbl_1 != NULL && lv_obj_is_valid(ui_scr->home_page_lbl_1)) {
            lv_label_set_text(ui_scr->home_page_lbl_1, _("Sun"));
            const lv_font_t *font = _font("Sun");
            if (font != NULL) {
                lv_obj_set_style_text_font(ui_scr->home_page_lbl_1, font, LV_PART_MAIN | LV_STATE_DEFAULT);
            }
        }

    }

    if (strcmp(page_name, "sys_prompt") == 0 && guider_ui.sys_prompt) {
        lv_ui_sys_prompt *ui_scr = ui_get_scr_ptr(&guider_ui, GUI_SCREEN_SYS_PROMPT);
        if (ui_scr->sys_prompt_lbl_warn != NULL && lv_obj_is_valid(ui_scr->sys_prompt_lbl_warn)) {
            lv_label_set_text(ui_scr->sys_prompt_lbl_warn, _("sd_update"));
            const lv_font_t *font = _font("sd_update");
            if (font != NULL) {
                lv_obj_set_style_text_font(ui_scr->sys_prompt_lbl_warn, font, LV_PART_MAIN | LV_STATE_DEFAULT);
            }
        }

    }

    if (strcmp(page_name, "sys_setting") == 0 && guider_ui.sys_setting) {
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
            lv_label_set_text(ui_scr->sys_setting_lbl_6, _("lamp"));
            const lv_font_t *font = _font("lamp");
            if (font != NULL) {
                lv_obj_set_style_text_font(ui_scr->sys_setting_lbl_6, font, LV_PART_MAIN | LV_STATE_DEFAULT);
            }
        }

        if (ui_scr->sys_setting_lbl_7 != NULL && lv_obj_is_valid(ui_scr->sys_setting_lbl_7)) {
            lv_label_set_text(ui_scr->sys_setting_lbl_7, _("software"));
            const lv_font_t *font = _font("software");
            if (font != NULL) {
                lv_obj_set_style_text_font(ui_scr->sys_setting_lbl_7, font, LV_PART_MAIN | LV_STATE_DEFAULT);
            }
        }

        if (ui_scr->sys_setting_lbl_8 != NULL && lv_obj_is_valid(ui_scr->sys_setting_lbl_8)) {
            lv_label_set_text(ui_scr->sys_setting_lbl_8, _("carnum"));
            const lv_font_t *font = _font("carnum");
            if (font != NULL) {
                lv_obj_set_style_text_font(ui_scr->sys_setting_lbl_8, font, LV_PART_MAIN | LV_STATE_DEFAULT);
            }
        }

        if (ui_scr->sys_setting_lbl_9 != NULL && lv_obj_is_valid(ui_scr->sys_setting_lbl_9)) {
            lv_label_set_text(ui_scr->sys_setting_lbl_9, _("roadline"));
            const lv_font_t *font = _font("roadline");
            if (font != NULL) {
                lv_obj_set_style_text_font(ui_scr->sys_setting_lbl_9, font, LV_PART_MAIN | LV_STATE_DEFAULT);
            }
        }

        if (ui_scr->sys_setting_lbl_10 != NULL && lv_obj_is_valid(ui_scr->sys_setting_lbl_10)) {
            lv_label_set_text(ui_scr->sys_setting_lbl_10, _("formatting"));
            const lv_font_t *font = _font("formatting");
            if (font != NULL) {
                lv_obj_set_style_text_font(ui_scr->sys_setting_lbl_10, font, LV_PART_MAIN | LV_STATE_DEFAULT);
            }
        }

        if (ui_scr->sys_setting_lbl_11 != NULL && lv_obj_is_valid(ui_scr->sys_setting_lbl_11)) {
            lv_label_set_text(ui_scr->sys_setting_lbl_11, _("reset"));
            const lv_font_t *font = _font("reset");
            if (font != NULL) {
                lv_obj_set_style_text_font(ui_scr->sys_setting_lbl_11, font, LV_PART_MAIN | LV_STATE_DEFAULT);
            }
        }

        if (ui_scr->sys_setting_lbl_12 != NULL && lv_obj_is_valid(ui_scr->sys_setting_lbl_12)) {
            lv_label_set_text(ui_scr->sys_setting_lbl_12, _("date"));
            const lv_font_t *font = _font("date");
            if (font != NULL) {
                lv_obj_set_style_text_font(ui_scr->sys_setting_lbl_12, font, LV_PART_MAIN | LV_STATE_DEFAULT);
            }
        }

        if (ui_scr->sys_setting_lbl_menu_title != NULL && lv_obj_is_valid(ui_scr->sys_setting_lbl_menu_title)) {
            lv_label_set_text(ui_scr->sys_setting_lbl_menu_title, _("language"));
            const lv_font_t *font = _font("language");
            if (font != NULL) {
                lv_obj_set_style_text_font(ui_scr->sys_setting_lbl_menu_title, font, LV_PART_MAIN | LV_STATE_DEFAULT);
            }
        }

        if (ui_scr->sys_setting_lbl_funkey4 != NULL && lv_obj_is_valid(ui_scr->sys_setting_lbl_funkey4)) {
            lv_label_set_text(ui_scr->sys_setting_lbl_funkey4, _("funkey4"));
            const lv_font_t *font = _font("funkey4");
            if (font != NULL) {
                lv_obj_set_style_text_font(ui_scr->sys_setting_lbl_funkey4, font, LV_PART_MAIN | LV_STATE_DEFAULT);
                lv_obj_set_style_text_font(ui_scr->sys_setting_lbl_funkey4, font, LV_PART_MAIN | LV_STATE_DISABLED);
                lv_obj_set_style_text_font(ui_scr->sys_setting_lbl_funkey4, font, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
            }
        }

        if (ui_scr->sys_setting_lbl_funkey5 != NULL && lv_obj_is_valid(ui_scr->sys_setting_lbl_funkey5)) {
            lv_label_set_text(ui_scr->sys_setting_lbl_funkey5, _("funkey5"));
            const lv_font_t *font = _font("funkey5");
            if (font != NULL) {
                lv_obj_set_style_text_font(ui_scr->sys_setting_lbl_funkey5, font, LV_PART_MAIN | LV_STATE_DEFAULT);
                lv_obj_set_style_text_font(ui_scr->sys_setting_lbl_funkey5, font, LV_PART_MAIN | LV_STATE_DISABLED);
                lv_obj_set_style_text_font(ui_scr->sys_setting_lbl_funkey5, font, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
            }
        }

        if (ui_scr->sys_setting_lbl_funkey6 != NULL && lv_obj_is_valid(ui_scr->sys_setting_lbl_funkey6)) {
            lv_label_set_text(ui_scr->sys_setting_lbl_funkey6, _("funkey6"));
            const lv_font_t *font = _font("funkey6");
            if (font != NULL) {
                lv_obj_set_style_text_font(ui_scr->sys_setting_lbl_funkey6, font, LV_PART_MAIN | LV_STATE_DEFAULT);
                lv_obj_set_style_text_font(ui_scr->sys_setting_lbl_funkey6, font, LV_PART_MAIN | LV_STATE_DISABLED);
                lv_obj_set_style_text_font(ui_scr->sys_setting_lbl_funkey6, font, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
            }
        }

        if (ui_scr->sys_setting_lbl_funkey7 != NULL && lv_obj_is_valid(ui_scr->sys_setting_lbl_funkey7)) {
            lv_label_set_text(ui_scr->sys_setting_lbl_funkey7, _("funkey7"));
            const lv_font_t *font = _font("funkey7");
            if (font != NULL) {
                lv_obj_set_style_text_font(ui_scr->sys_setting_lbl_funkey7, font, LV_PART_MAIN | LV_STATE_DEFAULT);
                lv_obj_set_style_text_font(ui_scr->sys_setting_lbl_funkey7, font, LV_PART_MAIN | LV_STATE_DISABLED);
                lv_obj_set_style_text_font(ui_scr->sys_setting_lbl_funkey7, font, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
            }
        }

        if (ui_scr->sys_setting_lbl_subpage_warning != NULL && lv_obj_is_valid(ui_scr->sys_setting_lbl_subpage_warning)) {
            lv_label_set_text(ui_scr->sys_setting_lbl_subpage_warning, _("subpagewarning0"));
            const lv_font_t *font = _font("subpagewarning0");
            if (font != NULL) {
                lv_obj_set_style_text_font(ui_scr->sys_setting_lbl_subpage_warning, font, LV_PART_MAIN | LV_STATE_DEFAULT);
            }
        }

        if (ui_scr->sys_setting_lbl_funkey2_label != NULL && lv_obj_is_valid(ui_scr->sys_setting_lbl_funkey2_label)) {
            lv_label_set_text(ui_scr->sys_setting_lbl_funkey2_label, _("YES"));
            const lv_font_t *font = _font("YES");
            if (font != NULL) {
                lv_obj_set_style_text_font(ui_scr->sys_setting_lbl_funkey2_label, font, LV_PART_MAIN | LV_STATE_DEFAULT);
                lv_obj_set_style_text_font(ui_scr->sys_setting_lbl_funkey2_label, font, LV_PART_MAIN | LV_STATE_DISABLED);
                lv_obj_set_style_text_font(ui_scr->sys_setting_lbl_funkey2_label, font, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
            }
        }
    }

    if (strcmp(page_name, "video_photo") == 0 && guider_ui.video_photo) {
        lv_ui_video_photo *ui_scr = ui_get_scr_ptr(&guider_ui, GUI_SCREEN_VIDEO_PHOTO);
        if (ui_scr->video_photo_lbl_5 != NULL && lv_obj_is_valid(ui_scr->video_photo_lbl_5)) {
            lv_label_set_text(ui_scr->video_photo_lbl_5, _("resolution"));
            const lv_font_t *font = _font("resolution");
            if (font != NULL) {
                lv_obj_set_style_text_font(ui_scr->video_photo_lbl_5, font, LV_PART_MAIN | LV_STATE_DEFAULT);
            }
        }

        if (ui_scr->video_photo_lbl_6 != NULL && lv_obj_is_valid(ui_scr->video_photo_lbl_6)) {
            lv_label_set_text(ui_scr->video_photo_lbl_6, _("shoot"));
            const lv_font_t *font = _font("shoot");
            if (font != NULL) {
                lv_obj_set_style_text_font(ui_scr->video_photo_lbl_6, font, LV_PART_MAIN | LV_STATE_DEFAULT);
            }
        }

        if (ui_scr->video_photo_lbl_7 != NULL && lv_obj_is_valid(ui_scr->video_photo_lbl_7)) {
            lv_label_set_text(ui_scr->video_photo_lbl_7, _("shots"));
            const lv_font_t *font = _font("shots");
            if (font != NULL) {
                lv_obj_set_style_text_font(ui_scr->video_photo_lbl_7, font, LV_PART_MAIN | LV_STATE_DEFAULT);
            }
        }

        if (ui_scr->video_photo_lbl_8 != NULL && lv_obj_is_valid(ui_scr->video_photo_lbl_8)) {
            lv_label_set_text(ui_scr->video_photo_lbl_8, _("quality"));
            const lv_font_t *font = _font("quality");
            if (font != NULL) {
                lv_obj_set_style_text_font(ui_scr->video_photo_lbl_8, font, LV_PART_MAIN | LV_STATE_DEFAULT);
            }
        }

        if (ui_scr->video_photo_lbl_13 != NULL && lv_obj_is_valid(ui_scr->video_photo_lbl_13)) {
            lv_label_set_text(ui_scr->video_photo_lbl_13, _("sharpness"));
            const lv_font_t *font = _font("sharpness");
            if (font != NULL) {
                lv_obj_set_style_text_font(ui_scr->video_photo_lbl_13, font, LV_PART_MAIN | LV_STATE_DEFAULT);
            }
        }

        if (ui_scr->video_photo_lbl_14 != NULL && lv_obj_is_valid(ui_scr->video_photo_lbl_14)) {
            lv_label_set_text(ui_scr->video_photo_lbl_14, _("exposure"));
            const lv_font_t *font = _font("exposure");
            if (font != NULL) {
                lv_obj_set_style_text_font(ui_scr->video_photo_lbl_14, font, LV_PART_MAIN | LV_STATE_DEFAULT);
            }
        }

        if (ui_scr->video_photo_lbl_15 != NULL && lv_obj_is_valid(ui_scr->video_photo_lbl_15)) {
            lv_label_set_text(ui_scr->video_photo_lbl_15, _("awb"));
            const lv_font_t *font = _font("awb");
            if (font != NULL) {
                lv_obj_set_style_text_font(ui_scr->video_photo_lbl_15, font, LV_PART_MAIN | LV_STATE_DEFAULT);
            }
        }

        if (ui_scr->video_photo_lbl_16 != NULL && lv_obj_is_valid(ui_scr->video_photo_lbl_16)) {
            lv_label_set_text(ui_scr->video_photo_lbl_16, _("color"));
            const lv_font_t *font = _font("color");
            if (font != NULL) {
                lv_obj_set_style_text_font(ui_scr->video_photo_lbl_16, font, LV_PART_MAIN | LV_STATE_DEFAULT);
            }
        }

        if (ui_scr->video_photo_lbl_18 != NULL && lv_obj_is_valid(ui_scr->video_photo_lbl_18)) {
            lv_label_set_text(ui_scr->video_photo_lbl_18, _("handshake"));
            const lv_font_t *font = _font("handshake");
            if (font != NULL) {
                lv_obj_set_style_text_font(ui_scr->video_photo_lbl_18, font, LV_PART_MAIN | LV_STATE_DEFAULT);
            }
        }

        if (ui_scr->video_photo_lbl_19 != NULL && lv_obj_is_valid(ui_scr->video_photo_lbl_19)) {
            lv_label_set_text(ui_scr->video_photo_lbl_19, _("preview"));
            const lv_font_t *font = _font("preview");
            if (font != NULL) {
                lv_obj_set_style_text_font(ui_scr->video_photo_lbl_19, font, LV_PART_MAIN | LV_STATE_DEFAULT);
            }
        }

        if (ui_scr->video_photo_lbl_20 != NULL && lv_obj_is_valid(ui_scr->video_photo_lbl_20)) {
            lv_label_set_text(ui_scr->video_photo_lbl_20, _("date"));
            const lv_font_t *font = _font("date");
            if (font != NULL) {
                lv_obj_set_style_text_font(ui_scr->video_photo_lbl_20, font, LV_PART_MAIN | LV_STATE_DEFAULT);
            }
        }

        if (ui_scr->video_photo_lbl_menu_title != NULL && lv_obj_is_valid(ui_scr->video_photo_lbl_menu_title)) {
            lv_label_set_text(ui_scr->video_photo_lbl_menu_title, _("language"));
            const lv_font_t *font = _font("language");
            if (font != NULL) {
                lv_obj_set_style_text_font(ui_scr->video_photo_lbl_menu_title, font, LV_PART_MAIN | LV_STATE_DEFAULT);
            }
        }

        if (ui_scr->video_photo_lbl_funkey1_label != NULL && lv_obj_is_valid(ui_scr->video_photo_lbl_funkey1_label)) {
            lv_label_set_text(ui_scr->video_photo_lbl_funkey1_label, _("YES"));
            const lv_font_t *font = _font("YES");
            if (font != NULL) {
                lv_obj_set_style_text_font(ui_scr->video_photo_lbl_funkey1_label, font, LV_PART_MAIN | LV_STATE_DEFAULT);
                lv_obj_set_style_text_font(ui_scr->video_photo_lbl_funkey1_label, font, LV_PART_MAIN | LV_STATE_FOCUSED);
                lv_obj_set_style_text_font(ui_scr->video_photo_lbl_funkey1_label, font, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
            }
        }
        if (ui_scr->video_photo_lbl_funkey2_label != NULL && lv_obj_is_valid(ui_scr->video_photo_lbl_funkey2_label)) {
            lv_label_set_text(ui_scr->video_photo_lbl_funkey2_label, _("YES"));
            const lv_font_t *font = _font("YES");
            if (font != NULL) {
                lv_obj_set_style_text_font(ui_scr->video_photo_lbl_funkey2_label, font, LV_PART_MAIN | LV_STATE_DEFAULT);
                lv_obj_set_style_text_font(ui_scr->video_photo_lbl_funkey2_label, font, LV_PART_MAIN | LV_STATE_FOCUSED);
                lv_obj_set_style_text_font(ui_scr->video_photo_lbl_funkey2_label, font, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
            }
        }
        if (ui_scr->video_photo_lbl_funkey3_label != NULL && lv_obj_is_valid(ui_scr->video_photo_lbl_funkey3_label)) {
            lv_label_set_text(ui_scr->video_photo_lbl_funkey3_label, _("YES"));
            const lv_font_t *font = _font("YES");
            if (font != NULL) {
                lv_obj_set_style_text_font(ui_scr->video_photo_lbl_funkey3_label, font, LV_PART_MAIN | LV_STATE_DEFAULT);
                lv_obj_set_style_text_font(ui_scr->video_photo_lbl_funkey3_label, font, LV_PART_MAIN | LV_STATE_FOCUSED);
                lv_obj_set_style_text_font(ui_scr->video_photo_lbl_funkey3_label, font, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
            }
        }
        if (ui_scr->video_photo_lbl_funkey4_label != NULL && lv_obj_is_valid(ui_scr->video_photo_lbl_funkey4_label)) {
            lv_label_set_text(ui_scr->video_photo_lbl_funkey4_label, _("YES"));
            const lv_font_t *font = _font("YES");
            if (font != NULL) {
                lv_obj_set_style_text_font(ui_scr->video_photo_lbl_funkey4_label, font, LV_PART_MAIN | LV_STATE_DEFAULT);
                lv_obj_set_style_text_font(ui_scr->video_photo_lbl_funkey4_label, font, LV_PART_MAIN | LV_STATE_FOCUSED);
                lv_obj_set_style_text_font(ui_scr->video_photo_lbl_funkey4_label, font, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
            }
        }
    }

    if (strcmp(page_name, "line_drift") == 0 && guider_ui.line_drift) {
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

    if (strcmp(page_name, "sys_popwin") == 0 && guider_ui.sys_popwin) {
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
}

void i18n_refresh_all_texts()
{
    if (guider_ui.video_rec) {
        lv_ui_video_rec *ui_scr = ui_get_scr_ptr(&guider_ui, GUI_SCREEN_VIDEO_REC);
        if (ui_scr->video_rec_lbl_5 != NULL && lv_obj_is_valid(ui_scr->video_rec_lbl_5)) {
            lv_label_set_text(ui_scr->video_rec_lbl_5, _("resolution"));
            const lv_font_t *font = _font("resolution");
            if (font != NULL) {
                lv_obj_set_style_text_font(ui_scr->video_rec_lbl_5, font, LV_PART_MAIN | LV_STATE_DEFAULT);
            }
        }

        if (ui_scr->video_rec_lbl_6 != NULL && lv_obj_is_valid(ui_scr->video_rec_lbl_6)) {
            lv_label_set_text(ui_scr->video_rec_lbl_6, _("doublerec"));
            const lv_font_t *font = _font("doublerec");
            if (font != NULL) {
                lv_obj_set_style_text_font(ui_scr->video_rec_lbl_6, font, LV_PART_MAIN | LV_STATE_DEFAULT);
            }
        }

        if (ui_scr->video_rec_lbl_7 != NULL && lv_obj_is_valid(ui_scr->video_rec_lbl_7)) {
            lv_label_set_text(ui_scr->video_rec_lbl_7, _("cycrec"));
            const lv_font_t *font = _font("cycrec");
            if (font != NULL) {
                lv_obj_set_style_text_font(ui_scr->video_rec_lbl_7, font, LV_PART_MAIN | LV_STATE_DEFAULT);
            }
        }

        if (ui_scr->video_rec_lbl_8 != NULL && lv_obj_is_valid(ui_scr->video_rec_lbl_8)) {
            lv_label_set_text(ui_scr->video_rec_lbl_8, _("gaprec"));
            const lv_font_t *font = _font("gaprec");
            if (font != NULL) {
                lv_obj_set_style_text_font(ui_scr->video_rec_lbl_8, font, LV_PART_MAIN | LV_STATE_DEFAULT);
            }
        }

        if (ui_scr->video_rec_lbl_14 != NULL && lv_obj_is_valid(ui_scr->video_rec_lbl_14)) {
            lv_label_set_text(ui_scr->video_rec_lbl_14, _("gsensor"));
            const lv_font_t *font = _font("gsensor");
            if (font != NULL) {
                lv_obj_set_style_text_font(ui_scr->video_rec_lbl_14, font, LV_PART_MAIN | LV_STATE_DEFAULT);
            }
        }

        if (ui_scr->video_rec_lbl_15 != NULL && lv_obj_is_valid(ui_scr->video_rec_lbl_15)) {
            lv_label_set_text(ui_scr->video_rec_lbl_15, _("exposure"));
            const lv_font_t *font = _font("exposure");
            if (font != NULL) {
                lv_obj_set_style_text_font(ui_scr->video_rec_lbl_15, font, LV_PART_MAIN | LV_STATE_DEFAULT);
            }
        }

        if (ui_scr->video_rec_lbl_16 != NULL && lv_obj_is_valid(ui_scr->video_rec_lbl_16)) {
            lv_label_set_text(ui_scr->video_rec_lbl_16, _("motion"));
            const lv_font_t *font = _font("motion");
            if (font != NULL) {
                lv_obj_set_style_text_font(ui_scr->video_rec_lbl_16, font, LV_PART_MAIN | LV_STATE_DEFAULT);
            }
        }

        if (ui_scr->video_rec_lbl_17 != NULL && lv_obj_is_valid(ui_scr->video_rec_lbl_17)) {
            lv_label_set_text(ui_scr->video_rec_lbl_17, _("date"));
            const lv_font_t *font = _font("date");
            if (font != NULL) {
                lv_obj_set_style_text_font(ui_scr->video_rec_lbl_17, font, LV_PART_MAIN | LV_STATE_DEFAULT);
            }
        }

        if (ui_scr->video_rec_lbl_18 != NULL && lv_obj_is_valid(ui_scr->video_rec_lbl_18)) {
            lv_label_set_text(ui_scr->video_rec_lbl_18, _("record"));
            const lv_font_t *font = _font("record");
            if (font != NULL) {
                lv_obj_set_style_text_font(ui_scr->video_rec_lbl_18, font, LV_PART_MAIN | LV_STATE_DEFAULT);
            }
        }

        if (ui_scr->video_rec_lbl_19 != NULL && lv_obj_is_valid(ui_scr->video_rec_lbl_19)) {
            lv_label_set_text(ui_scr->video_rec_lbl_19, _("guard"));
            const lv_font_t *font = _font("guard");
            if (font != NULL) {
                lv_obj_set_style_text_font(ui_scr->video_rec_lbl_19, font, LV_PART_MAIN | LV_STATE_DEFAULT);
            }
        }

        if (ui_scr->video_rec_lbl_20 != NULL && lv_obj_is_valid(ui_scr->video_rec_lbl_20)) {
            lv_label_set_text(ui_scr->video_rec_lbl_20, _("carnum"));
            const lv_font_t *font = _font("carnum");
            if (font != NULL) {
                lv_obj_set_style_text_font(ui_scr->video_rec_lbl_20, font, LV_PART_MAIN | LV_STATE_DEFAULT);
            }
        }

        if (ui_scr->video_rec_lbl_menu_title != NULL && lv_obj_is_valid(ui_scr->video_rec_lbl_menu_title)) {
            lv_label_set_text(ui_scr->video_rec_lbl_menu_title, _("language"));
            const lv_font_t *font = _font("language");
            if (font != NULL) {
                lv_obj_set_style_text_font(ui_scr->video_rec_lbl_menu_title, font, LV_PART_MAIN | LV_STATE_DEFAULT);
            }
        }

        if (ui_scr->video_rec_lbl_funkey1_label != NULL && lv_obj_is_valid(ui_scr->video_rec_lbl_funkey1_label)) {
            lv_label_set_text(ui_scr->video_rec_lbl_funkey1_label, _("YES"));
            const lv_font_t *font = _font("YES");
            if (font != NULL) {
                lv_obj_set_style_text_font(ui_scr->video_rec_lbl_funkey1_label, font, LV_PART_MAIN | LV_STATE_DEFAULT);
                lv_obj_set_style_text_font(ui_scr->video_rec_lbl_funkey1_label, font, LV_PART_MAIN | LV_STATE_FOCUSED);
                lv_obj_set_style_text_font(ui_scr->video_rec_lbl_funkey1_label, font, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
            }
        }
        if (ui_scr->video_rec_lbl_funkey2_label != NULL && lv_obj_is_valid(ui_scr->video_rec_lbl_funkey2_label)) {
            lv_label_set_text(ui_scr->video_rec_lbl_funkey2_label, _("YES"));
            const lv_font_t *font = _font("YES");
            if (font != NULL) {
                lv_obj_set_style_text_font(ui_scr->video_rec_lbl_funkey2_label, font, LV_PART_MAIN | LV_STATE_DEFAULT);
                lv_obj_set_style_text_font(ui_scr->video_rec_lbl_funkey2_label, font, LV_PART_MAIN | LV_STATE_FOCUSED);
                lv_obj_set_style_text_font(ui_scr->video_rec_lbl_funkey2_label, font, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
            }
        }
        if (ui_scr->video_rec_lbl_funkey3_label != NULL && lv_obj_is_valid(ui_scr->video_rec_lbl_funkey3_label)) {
            lv_label_set_text(ui_scr->video_rec_lbl_funkey3_label, _("YES"));
            const lv_font_t *font = _font("YES");
            if (font != NULL) {
                lv_obj_set_style_text_font(ui_scr->video_rec_lbl_funkey3_label, font, LV_PART_MAIN | LV_STATE_DEFAULT);
                lv_obj_set_style_text_font(ui_scr->video_rec_lbl_funkey3_label, font, LV_PART_MAIN | LV_STATE_FOCUSED);
                lv_obj_set_style_text_font(ui_scr->video_rec_lbl_funkey3_label, font, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
            }
        }
        if (ui_scr->video_rec_lbl_funkey4_label != NULL && lv_obj_is_valid(ui_scr->video_rec_lbl_funkey4_label)) {
            lv_label_set_text(ui_scr->video_rec_lbl_funkey4_label, _("YES"));
            const lv_font_t *font = _font("YES");
            if (font != NULL) {
                lv_obj_set_style_text_font(ui_scr->video_rec_lbl_funkey4_label, font, LV_PART_MAIN | LV_STATE_DEFAULT);
                lv_obj_set_style_text_font(ui_scr->video_rec_lbl_funkey4_label, font, LV_PART_MAIN | LV_STATE_FOCUSED);
                lv_obj_set_style_text_font(ui_scr->video_rec_lbl_funkey4_label, font, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
            }
        }
    }

    if (guider_ui.home_page) {
        lv_ui_home_page *ui_scr = ui_get_scr_ptr(&guider_ui, GUI_SCREEN_HOME_PAGE);
        if (ui_scr->home_page_lbl_3 != NULL && lv_obj_is_valid(ui_scr->home_page_lbl_3)) {
            lv_label_set_text(ui_scr->home_page_lbl_3, _("sunny"));
            const lv_font_t *font = _font("sunny");
            if (font != NULL) {
                lv_obj_set_style_text_font(ui_scr->home_page_lbl_3, font, LV_PART_MAIN | LV_STATE_DEFAULT);
            }
        }

        if (ui_scr->home_page_lbl_1 != NULL && lv_obj_is_valid(ui_scr->home_page_lbl_1)) {
            lv_label_set_text(ui_scr->home_page_lbl_1, _("Sun"));
            const lv_font_t *font = _font("Sun");
            if (font != NULL) {
                lv_obj_set_style_text_font(ui_scr->home_page_lbl_1, font, LV_PART_MAIN | LV_STATE_DEFAULT);
            }
        }

    }

    if (guider_ui.sys_prompt) {
        lv_ui_sys_prompt *ui_scr = ui_get_scr_ptr(&guider_ui, GUI_SCREEN_SYS_PROMPT);
        if (ui_scr->sys_prompt_lbl_warn != NULL && lv_obj_is_valid(ui_scr->sys_prompt_lbl_warn)) {
            lv_label_set_text(ui_scr->sys_prompt_lbl_warn, _("sd_update"));
            const lv_font_t *font = _font("sd_update");
            if (font != NULL) {
                lv_obj_set_style_text_font(ui_scr->sys_prompt_lbl_warn, font, LV_PART_MAIN | LV_STATE_DEFAULT);
            }
        }

    }

    if (guider_ui.sys_setting) {
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
            lv_label_set_text(ui_scr->sys_setting_lbl_6, _("lamp"));
            const lv_font_t *font = _font("lamp");
            if (font != NULL) {
                lv_obj_set_style_text_font(ui_scr->sys_setting_lbl_6, font, LV_PART_MAIN | LV_STATE_DEFAULT);
            }
        }

        if (ui_scr->sys_setting_lbl_7 != NULL && lv_obj_is_valid(ui_scr->sys_setting_lbl_7)) {
            lv_label_set_text(ui_scr->sys_setting_lbl_7, _("software"));
            const lv_font_t *font = _font("software");
            if (font != NULL) {
                lv_obj_set_style_text_font(ui_scr->sys_setting_lbl_7, font, LV_PART_MAIN | LV_STATE_DEFAULT);
            }
        }

        if (ui_scr->sys_setting_lbl_8 != NULL && lv_obj_is_valid(ui_scr->sys_setting_lbl_8)) {
            lv_label_set_text(ui_scr->sys_setting_lbl_8, _("carnum"));
            const lv_font_t *font = _font("carnum");
            if (font != NULL) {
                lv_obj_set_style_text_font(ui_scr->sys_setting_lbl_8, font, LV_PART_MAIN | LV_STATE_DEFAULT);
            }
        }

        if (ui_scr->sys_setting_lbl_9 != NULL && lv_obj_is_valid(ui_scr->sys_setting_lbl_9)) {
            lv_label_set_text(ui_scr->sys_setting_lbl_9, _("roadline"));
            const lv_font_t *font = _font("roadline");
            if (font != NULL) {
                lv_obj_set_style_text_font(ui_scr->sys_setting_lbl_9, font, LV_PART_MAIN | LV_STATE_DEFAULT);
            }
        }

        if (ui_scr->sys_setting_lbl_10 != NULL && lv_obj_is_valid(ui_scr->sys_setting_lbl_10)) {
            lv_label_set_text(ui_scr->sys_setting_lbl_10, _("formatting"));
            const lv_font_t *font = _font("formatting");
            if (font != NULL) {
                lv_obj_set_style_text_font(ui_scr->sys_setting_lbl_10, font, LV_PART_MAIN | LV_STATE_DEFAULT);
            }
        }

        if (ui_scr->sys_setting_lbl_11 != NULL && lv_obj_is_valid(ui_scr->sys_setting_lbl_11)) {
            lv_label_set_text(ui_scr->sys_setting_lbl_11, _("reset"));
            const lv_font_t *font = _font("reset");
            if (font != NULL) {
                lv_obj_set_style_text_font(ui_scr->sys_setting_lbl_11, font, LV_PART_MAIN | LV_STATE_DEFAULT);
            }
        }

        if (ui_scr->sys_setting_lbl_12 != NULL && lv_obj_is_valid(ui_scr->sys_setting_lbl_12)) {
            lv_label_set_text(ui_scr->sys_setting_lbl_12, _("date"));
            const lv_font_t *font = _font("date");
            if (font != NULL) {
                lv_obj_set_style_text_font(ui_scr->sys_setting_lbl_12, font, LV_PART_MAIN | LV_STATE_DEFAULT);
            }
        }

        if (ui_scr->sys_setting_lbl_menu_title != NULL && lv_obj_is_valid(ui_scr->sys_setting_lbl_menu_title)) {
            lv_label_set_text(ui_scr->sys_setting_lbl_menu_title, _("language"));
            const lv_font_t *font = _font("language");
            if (font != NULL) {
                lv_obj_set_style_text_font(ui_scr->sys_setting_lbl_menu_title, font, LV_PART_MAIN | LV_STATE_DEFAULT);
            }
        }

        if (ui_scr->sys_setting_lbl_funkey4 != NULL && lv_obj_is_valid(ui_scr->sys_setting_lbl_funkey4)) {
            lv_label_set_text(ui_scr->sys_setting_lbl_funkey4, _("funkey4"));
            const lv_font_t *font = _font("funkey4");
            if (font != NULL) {
                lv_obj_set_style_text_font(ui_scr->sys_setting_lbl_funkey4, font, LV_PART_MAIN | LV_STATE_DEFAULT);
                lv_obj_set_style_text_font(ui_scr->sys_setting_lbl_funkey4, font, LV_PART_MAIN | LV_STATE_DISABLED);
                lv_obj_set_style_text_font(ui_scr->sys_setting_lbl_funkey4, font, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
            }
        }

        if (ui_scr->sys_setting_lbl_funkey5 != NULL && lv_obj_is_valid(ui_scr->sys_setting_lbl_funkey5)) {
            lv_label_set_text(ui_scr->sys_setting_lbl_funkey5, _("funkey5"));
            const lv_font_t *font = _font("funkey5");
            if (font != NULL) {
                lv_obj_set_style_text_font(ui_scr->sys_setting_lbl_funkey5, font, LV_PART_MAIN | LV_STATE_DEFAULT);
                lv_obj_set_style_text_font(ui_scr->sys_setting_lbl_funkey5, font, LV_PART_MAIN | LV_STATE_DISABLED);
                lv_obj_set_style_text_font(ui_scr->sys_setting_lbl_funkey5, font, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
            }
        }

        if (ui_scr->sys_setting_lbl_funkey6 != NULL && lv_obj_is_valid(ui_scr->sys_setting_lbl_funkey6)) {
            lv_label_set_text(ui_scr->sys_setting_lbl_funkey6, _("funkey6"));
            const lv_font_t *font = _font("funkey6");
            if (font != NULL) {
                lv_obj_set_style_text_font(ui_scr->sys_setting_lbl_funkey6, font, LV_PART_MAIN | LV_STATE_DEFAULT);
                lv_obj_set_style_text_font(ui_scr->sys_setting_lbl_funkey6, font, LV_PART_MAIN | LV_STATE_DISABLED);
                lv_obj_set_style_text_font(ui_scr->sys_setting_lbl_funkey6, font, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
            }
        }

        if (ui_scr->sys_setting_lbl_funkey7 != NULL && lv_obj_is_valid(ui_scr->sys_setting_lbl_funkey7)) {
            lv_label_set_text(ui_scr->sys_setting_lbl_funkey7, _("funkey7"));
            const lv_font_t *font = _font("funkey7");
            if (font != NULL) {
                lv_obj_set_style_text_font(ui_scr->sys_setting_lbl_funkey7, font, LV_PART_MAIN | LV_STATE_DEFAULT);
                lv_obj_set_style_text_font(ui_scr->sys_setting_lbl_funkey7, font, LV_PART_MAIN | LV_STATE_DISABLED);
                lv_obj_set_style_text_font(ui_scr->sys_setting_lbl_funkey7, font, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
            }
        }

        if (ui_scr->sys_setting_lbl_subpage_warning != NULL && lv_obj_is_valid(ui_scr->sys_setting_lbl_subpage_warning)) {
            lv_label_set_text(ui_scr->sys_setting_lbl_subpage_warning, _("subpagewarning0"));
            const lv_font_t *font = _font("subpagewarning0");
            if (font != NULL) {
                lv_obj_set_style_text_font(ui_scr->sys_setting_lbl_subpage_warning, font, LV_PART_MAIN | LV_STATE_DEFAULT);
            }
        }

        if (ui_scr->sys_setting_lbl_funkey2_label != NULL && lv_obj_is_valid(ui_scr->sys_setting_lbl_funkey2_label)) {
            lv_label_set_text(ui_scr->sys_setting_lbl_funkey2_label, _("YES"));
            const lv_font_t *font = _font("YES");
            if (font != NULL) {
                lv_obj_set_style_text_font(ui_scr->sys_setting_lbl_funkey2_label, font, LV_PART_MAIN | LV_STATE_DEFAULT);
                lv_obj_set_style_text_font(ui_scr->sys_setting_lbl_funkey2_label, font, LV_PART_MAIN | LV_STATE_DISABLED);
                lv_obj_set_style_text_font(ui_scr->sys_setting_lbl_funkey2_label, font, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
            }
        }
    }

    if (guider_ui.video_photo) {
        lv_ui_video_photo *ui_scr = ui_get_scr_ptr(&guider_ui, GUI_SCREEN_VIDEO_PHOTO);
        if (ui_scr->video_photo_lbl_5 != NULL && lv_obj_is_valid(ui_scr->video_photo_lbl_5)) {
            lv_label_set_text(ui_scr->video_photo_lbl_5, _("resolution"));
            const lv_font_t *font = _font("resolution");
            if (font != NULL) {
                lv_obj_set_style_text_font(ui_scr->video_photo_lbl_5, font, LV_PART_MAIN | LV_STATE_DEFAULT);
            }
        }

        if (ui_scr->video_photo_lbl_6 != NULL && lv_obj_is_valid(ui_scr->video_photo_lbl_6)) {
            lv_label_set_text(ui_scr->video_photo_lbl_6, _("shoot"));
            const lv_font_t *font = _font("shoot");
            if (font != NULL) {
                lv_obj_set_style_text_font(ui_scr->video_photo_lbl_6, font, LV_PART_MAIN | LV_STATE_DEFAULT);
            }
        }

        if (ui_scr->video_photo_lbl_7 != NULL && lv_obj_is_valid(ui_scr->video_photo_lbl_7)) {
            lv_label_set_text(ui_scr->video_photo_lbl_7, _("shots"));
            const lv_font_t *font = _font("shots");
            if (font != NULL) {
                lv_obj_set_style_text_font(ui_scr->video_photo_lbl_7, font, LV_PART_MAIN | LV_STATE_DEFAULT);
            }
        }

        if (ui_scr->video_photo_lbl_8 != NULL && lv_obj_is_valid(ui_scr->video_photo_lbl_8)) {
            lv_label_set_text(ui_scr->video_photo_lbl_8, _("quality"));
            const lv_font_t *font = _font("quality");
            if (font != NULL) {
                lv_obj_set_style_text_font(ui_scr->video_photo_lbl_8, font, LV_PART_MAIN | LV_STATE_DEFAULT);
            }
        }

        if (ui_scr->video_photo_lbl_13 != NULL && lv_obj_is_valid(ui_scr->video_photo_lbl_13)) {
            lv_label_set_text(ui_scr->video_photo_lbl_13, _("sharpness"));
            const lv_font_t *font = _font("sharpness");
            if (font != NULL) {
                lv_obj_set_style_text_font(ui_scr->video_photo_lbl_13, font, LV_PART_MAIN | LV_STATE_DEFAULT);
            }
        }

        if (ui_scr->video_photo_lbl_14 != NULL && lv_obj_is_valid(ui_scr->video_photo_lbl_14)) {
            lv_label_set_text(ui_scr->video_photo_lbl_14, _("exposure"));
            const lv_font_t *font = _font("exposure");
            if (font != NULL) {
                lv_obj_set_style_text_font(ui_scr->video_photo_lbl_14, font, LV_PART_MAIN | LV_STATE_DEFAULT);
            }
        }

        if (ui_scr->video_photo_lbl_15 != NULL && lv_obj_is_valid(ui_scr->video_photo_lbl_15)) {
            lv_label_set_text(ui_scr->video_photo_lbl_15, _("awb"));
            const lv_font_t *font = _font("awb");
            if (font != NULL) {
                lv_obj_set_style_text_font(ui_scr->video_photo_lbl_15, font, LV_PART_MAIN | LV_STATE_DEFAULT);
            }
        }

        if (ui_scr->video_photo_lbl_16 != NULL && lv_obj_is_valid(ui_scr->video_photo_lbl_16)) {
            lv_label_set_text(ui_scr->video_photo_lbl_16, _("color"));
            const lv_font_t *font = _font("color");
            if (font != NULL) {
                lv_obj_set_style_text_font(ui_scr->video_photo_lbl_16, font, LV_PART_MAIN | LV_STATE_DEFAULT);
            }
        }

        if (ui_scr->video_photo_lbl_18 != NULL && lv_obj_is_valid(ui_scr->video_photo_lbl_18)) {
            lv_label_set_text(ui_scr->video_photo_lbl_18, _("handshake"));
            const lv_font_t *font = _font("handshake");
            if (font != NULL) {
                lv_obj_set_style_text_font(ui_scr->video_photo_lbl_18, font, LV_PART_MAIN | LV_STATE_DEFAULT);
            }
        }

        if (ui_scr->video_photo_lbl_19 != NULL && lv_obj_is_valid(ui_scr->video_photo_lbl_19)) {
            lv_label_set_text(ui_scr->video_photo_lbl_19, _("preview"));
            const lv_font_t *font = _font("preview");
            if (font != NULL) {
                lv_obj_set_style_text_font(ui_scr->video_photo_lbl_19, font, LV_PART_MAIN | LV_STATE_DEFAULT);
            }
        }

        if (ui_scr->video_photo_lbl_20 != NULL && lv_obj_is_valid(ui_scr->video_photo_lbl_20)) {
            lv_label_set_text(ui_scr->video_photo_lbl_20, _("date"));
            const lv_font_t *font = _font("date");
            if (font != NULL) {
                lv_obj_set_style_text_font(ui_scr->video_photo_lbl_20, font, LV_PART_MAIN | LV_STATE_DEFAULT);
            }
        }

        if (ui_scr->video_photo_lbl_menu_title != NULL && lv_obj_is_valid(ui_scr->video_photo_lbl_menu_title)) {
            lv_label_set_text(ui_scr->video_photo_lbl_menu_title, _("language"));
            const lv_font_t *font = _font("language");
            if (font != NULL) {
                lv_obj_set_style_text_font(ui_scr->video_photo_lbl_menu_title, font, LV_PART_MAIN | LV_STATE_DEFAULT);
            }
        }

        if (ui_scr->video_photo_lbl_funkey1_label != NULL && lv_obj_is_valid(ui_scr->video_photo_lbl_funkey1_label)) {
            lv_label_set_text(ui_scr->video_photo_lbl_funkey1_label, _("YES"));
            const lv_font_t *font = _font("YES");
            if (font != NULL) {
                lv_obj_set_style_text_font(ui_scr->video_photo_lbl_funkey1_label, font, LV_PART_MAIN | LV_STATE_DEFAULT);
                lv_obj_set_style_text_font(ui_scr->video_photo_lbl_funkey1_label, font, LV_PART_MAIN | LV_STATE_FOCUSED);
                lv_obj_set_style_text_font(ui_scr->video_photo_lbl_funkey1_label, font, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
            }
        }
        if (ui_scr->video_photo_lbl_funkey2_label != NULL && lv_obj_is_valid(ui_scr->video_photo_lbl_funkey2_label)) {
            lv_label_set_text(ui_scr->video_photo_lbl_funkey2_label, _("YES"));
            const lv_font_t *font = _font("YES");
            if (font != NULL) {
                lv_obj_set_style_text_font(ui_scr->video_photo_lbl_funkey2_label, font, LV_PART_MAIN | LV_STATE_DEFAULT);
                lv_obj_set_style_text_font(ui_scr->video_photo_lbl_funkey2_label, font, LV_PART_MAIN | LV_STATE_FOCUSED);
                lv_obj_set_style_text_font(ui_scr->video_photo_lbl_funkey2_label, font, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
            }
        }
        if (ui_scr->video_photo_lbl_funkey3_label != NULL && lv_obj_is_valid(ui_scr->video_photo_lbl_funkey3_label)) {
            lv_label_set_text(ui_scr->video_photo_lbl_funkey3_label, _("YES"));
            const lv_font_t *font = _font("YES");
            if (font != NULL) {
                lv_obj_set_style_text_font(ui_scr->video_photo_lbl_funkey3_label, font, LV_PART_MAIN | LV_STATE_DEFAULT);
                lv_obj_set_style_text_font(ui_scr->video_photo_lbl_funkey3_label, font, LV_PART_MAIN | LV_STATE_FOCUSED);
                lv_obj_set_style_text_font(ui_scr->video_photo_lbl_funkey3_label, font, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
            }
        }
        if (ui_scr->video_photo_lbl_funkey4_label != NULL && lv_obj_is_valid(ui_scr->video_photo_lbl_funkey4_label)) {
            lv_label_set_text(ui_scr->video_photo_lbl_funkey4_label, _("YES"));
            const lv_font_t *font = _font("YES");
            if (font != NULL) {
                lv_obj_set_style_text_font(ui_scr->video_photo_lbl_funkey4_label, font, LV_PART_MAIN | LV_STATE_DEFAULT);
                lv_obj_set_style_text_font(ui_scr->video_photo_lbl_funkey4_label, font, LV_PART_MAIN | LV_STATE_FOCUSED);
                lv_obj_set_style_text_font(ui_scr->video_photo_lbl_funkey4_label, font, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
            }
        }
    }

    if (guider_ui.line_drift) {
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

    if (guider_ui.sys_popwin) {
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
}

#endif
