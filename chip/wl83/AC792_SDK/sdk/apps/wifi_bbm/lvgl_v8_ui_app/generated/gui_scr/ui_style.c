/*Generate Code, Do NOT Edit!*/
#include "./ui_style.h"
#include "../gui_guider.h"

// scr
lv_style_t gui_scr_main_default_style;

// label
lv_style_t gui_label_main_default_style;

// imglist
lv_style_t gui_imglist_main_default_style;

void ui_style_init(void)
{
    // scr
    lv_style_init(&gui_scr_main_default_style);
    lv_style_set_bg_color(&gui_scr_main_default_style, lv_color_make(0x55, 0xaa, 0xa5));
    lv_style_set_bg_grad_color(&gui_scr_main_default_style, lv_color_make(0x21, 0x95, 0xf6));
    lv_style_set_bg_grad_dir(&gui_scr_main_default_style, LV_GRAD_DIR_NONE);
    lv_style_set_bg_opa(&gui_scr_main_default_style, 255);
    lv_style_set_border_color(&gui_scr_main_default_style, lv_color_make(0x21, 0x95, 0xf6));
    lv_style_set_border_width(&gui_scr_main_default_style, 0);
    lv_style_set_border_opa(&gui_scr_main_default_style, 0);
    lv_style_set_bg_img_opa(&gui_scr_main_default_style, 0);

    // label
    lv_style_init(&gui_label_main_default_style);
    lv_style_set_radius(&gui_label_main_default_style, 0);
    lv_style_set_bg_color(&gui_label_main_default_style, lv_color_make(0x21, 0x95, 0xf6));
    lv_style_set_bg_grad_color(&gui_label_main_default_style, lv_color_make(0x21, 0x95, 0xf6));
    lv_style_set_bg_grad_dir(&gui_label_main_default_style, LV_GRAD_DIR_NONE);
    lv_style_set_bg_opa(&gui_label_main_default_style, 0);
    lv_style_set_shadow_width(&gui_label_main_default_style, 0);
    lv_style_set_shadow_color(&gui_label_main_default_style, lv_color_make(0x21, 0x95, 0xf6));
    lv_style_set_shadow_opa(&gui_label_main_default_style, 0);
    lv_style_set_shadow_spread(&gui_label_main_default_style, 0);
    lv_style_set_shadow_ofs_x(&gui_label_main_default_style, 0);
    lv_style_set_shadow_ofs_y(&gui_label_main_default_style, 0);
    lv_style_set_border_color(&gui_label_main_default_style, lv_color_make(0x21, 0x95, 0xf6));
    lv_style_set_border_width(&gui_label_main_default_style, 0);
    lv_style_set_border_opa(&gui_label_main_default_style, 0);
    lv_style_set_border_side(&gui_label_main_default_style, LV_BORDER_SIDE_FULL);
    lv_style_set_outline_color(&gui_label_main_default_style, lv_color_make(0x21, 0x95, 0xf6));
    lv_style_set_outline_width(&gui_label_main_default_style, 0);
    lv_style_set_outline_opa(&gui_label_main_default_style, 0);
    lv_style_set_outline_pad(&gui_label_main_default_style, 0);
    lv_style_set_text_color(&gui_label_main_default_style, lv_color_make(0xE4, 0x18, 0x18));
    lv_style_set_text_font(&gui_label_main_default_style, &lv_font_montserratMedium_12);
    lv_style_set_text_letter_space(&gui_label_main_default_style, 2);
    lv_style_set_text_line_space(&gui_label_main_default_style, 0);
    lv_style_set_text_align(&gui_label_main_default_style, LV_TEXT_ALIGN_CENTER);
    lv_style_set_pad_left(&gui_label_main_default_style, 0);
    lv_style_set_pad_right(&gui_label_main_default_style, 0);
    lv_style_set_pad_top(&gui_label_main_default_style, 8);
    lv_style_set_pad_bottom(&gui_label_main_default_style, 0);

    // imglist
    lv_style_init(&gui_imglist_main_default_style);
    lv_style_set_radius(&gui_imglist_main_default_style, 0);
    lv_style_set_clip_corner(&gui_imglist_main_default_style, true);
    lv_style_set_bg_color(&gui_imglist_main_default_style, lv_color_make(0x55, 0xaa, 0xa5));
    lv_style_set_bg_grad_color(&gui_imglist_main_default_style, lv_color_make(0x55, 0xaa, 0xa5));
    lv_style_set_bg_grad_dir(&gui_imglist_main_default_style, LV_GRAD_DIR_NONE);
    lv_style_set_bg_opa(&gui_imglist_main_default_style, 255);
    lv_style_set_outline_color(&gui_imglist_main_default_style, lv_color_make(0x21, 0x95, 0xf6));
    lv_style_set_outline_width(&gui_imglist_main_default_style, 0);
    lv_style_set_outline_opa(&gui_imglist_main_default_style, 0);
    lv_style_set_outline_pad(&gui_imglist_main_default_style, 0);
    lv_style_set_img_recolor(&gui_imglist_main_default_style, lv_color_make(0xff, 0xff, 0xff));
    lv_style_set_img_recolor_opa(&gui_imglist_main_default_style, 0);
    lv_style_set_img_opa(&gui_imglist_main_default_style, 255);

}

void ui_style_set(lv_obj_t *obj, gui_ctrl_type_t type)
{
    switch (type) {
    case GUI_CTRL_SCR:
        lv_obj_add_style(obj, &gui_scr_main_default_style, LV_PART_MAIN | LV_STATE_DEFAULT);
        break;
    case GUI_CTRL_LABEL:
        lv_obj_add_style(obj, &gui_label_main_default_style, LV_PART_MAIN | LV_STATE_DEFAULT);
        break;
    case GUI_CTRL_IMGLIST:
        lv_obj_add_style(obj, &gui_imglist_main_default_style, LV_PART_MAIN | LV_STATE_DEFAULT);
        break;
    default:
        break;
    }
}

