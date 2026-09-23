/*Generate Code, Do NOT Edit!*/
#ifndef UI_STYLE_H
#define UI_STYLE_H

#ifdef __cplusplus
extern "C" {
#endif

#include "lvgl.h"

// scr
extern lv_style_t gui_scr_main_default_style;

// label
extern lv_style_t gui_label_main_default_style;

// imglist
extern lv_style_t gui_imglist_main_default_style;

enum {
    GUI_CTRL_SCR,
    GUI_CTRL_LABEL,
    GUI_CTRL_IMGLIST,
};
typedef uint8_t gui_ctrl_type_t;

extern void ui_style_init(void);
extern void ui_style_set(lv_obj_t *obj, gui_ctrl_type_t type);

#ifdef __cplusplus
}
#endif
#endif /* UI_STYLE_H */
