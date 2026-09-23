#include "app_config.h"
#ifdef CONFIG_UI_STYLE_JL_ENABLE
/*Generate Code, Do NOT Edit!*/
#ifndef UI_STYLE_H
#define UI_STYLE_H

#ifdef __cplusplus
extern "C" {
#endif

#include "lvgl.h"

// digitclock
extern lv_style_t gui_digitclock_main_default_style;
extern lv_style_t gui_digitclock_main_disabled_style;

// digital_clock
extern lv_style_t gui_digitclock_main_default_style;
extern lv_style_t gui_digitclock_main_disabled_style;

// img
extern lv_style_t gui_img_main_default_style;
extern lv_style_t gui_img_main_focused_style;
extern lv_style_t gui_img_main_focus_key_style;

// datetext
extern lv_style_t gui_datetext_main_default_style;

// bar
extern lv_style_t gui_bar_main_default_style;
extern lv_style_t gui_bar_indicator_default_style;

// scr
extern lv_style_t gui_scr_main_default_style;

// imgbtn
extern lv_style_t gui_imgbtn_main_default_style;
extern lv_style_t gui_imgbtn_main_pressed_style;
extern lv_style_t gui_imgbtn_main_checked_style;
extern lv_style_t gui_imgbtn_main_focus_key_style;
extern lv_style_t gui_imgbtn_main_focused_style;

// ddlist
extern lv_style_t gui_ddlist_main_default_style;
extern lv_style_t gui_ddlist_selected_checked_style;
extern lv_style_t gui_ddlist_dropdown_list_default_style;
extern lv_style_t gui_ddlist_scrollbar_default_style;
extern lv_style_t gui_ddlist_main_focus_key_style;

// dropdown
extern lv_style_t gui_ddlist_main_default_style;
extern lv_style_t gui_ddlist_selected_checked_style;
extern lv_style_t gui_ddlist_dropdown_list_default_style;
extern lv_style_t gui_ddlist_scrollbar_default_style;
extern lv_style_t gui_ddlist_main_focus_key_style;

// label
extern lv_style_t gui_label_main_default_style;
extern lv_style_t gui_label_main_disabled_style;
extern lv_style_t gui_label_main_focus_key_style;
extern lv_style_t gui_label_main_focused_style;

// cont
extern lv_style_t gui_cont_main_default_style;

// btn
extern lv_style_t gui_btn_main_default_style;
extern lv_style_t gui_btn_main_focused_style;
extern lv_style_t gui_btn_main_focus_key_style;
extern lv_style_t gui_btn_main_disabled_style;

// roller
extern lv_style_t gui_roller_main_default_style;
extern lv_style_t gui_roller_selected_default_style;
extern lv_style_t gui_roller_main_focus_key_style;

enum {
    GUI_CTRL_DIGITALCLOCK,
    GUI_CTRL_IMG,
    GUI_CTRL_DATETEXT,
    GUI_CTRL_BAR,
    GUI_CTRL_SCR,
    GUI_CTRL_IMGBTN,
    GUI_CTRL_DROPDOWN,
    GUI_CTRL_LABEL,
    GUI_CTRL_CONT,
    GUI_CTRL_BUTTON,
    GUI_CTRL_ROLLER,
};
typedef uint8_t gui_ctrl_type_t;

extern void ui_style_init(void);
extern void ui_style_set(lv_obj_t *obj, gui_ctrl_type_t type);

#ifdef __cplusplus
}
#endif
#endif /* UI_STYLE_H */

#endif
