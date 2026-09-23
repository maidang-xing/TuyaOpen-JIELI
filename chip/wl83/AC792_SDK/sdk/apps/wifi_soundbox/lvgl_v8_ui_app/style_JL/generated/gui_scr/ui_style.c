/*Generate Code, Do NOT Edit!*/
#include "./ui_style.h"
#include "../gui_guider.h"

// slider
lv_style_t gui_slider_main_default_style;
lv_style_t gui_slider_indicator_default_style;
lv_style_t gui_slider_knob_default_style;

// img
lv_style_t gui_img_main_default_style;

// scr
lv_style_t gui_scr_main_default_style;

// imgbtn
lv_style_t gui_imgbtn_main_default_style;
lv_style_t gui_imgbtn_main_focused_style;
lv_style_t gui_imgbtn_main_pressed_style;
lv_style_t gui_imgbtn_main_checked_style;

// sw
lv_style_t gui_sw_main_default_style;
lv_style_t gui_sw_indicator_checked_style;
lv_style_t gui_sw_knob_default_style;

// ddlist
lv_style_t gui_ddlist_main_default_style;
lv_style_t gui_ddlist_selected_checked_style;
lv_style_t gui_ddlist_dropdown_list_default_style;
lv_style_t gui_ddlist_scrollbar_default_style;

// label
lv_style_t gui_label_main_default_style;

// cont
lv_style_t gui_cont_main_default_style;

// btn
lv_style_t gui_btn_main_default_style;
lv_style_t gui_btn_main_disabled_style;

void ui_style_init(void)
{
    // slider
    lv_style_init(&gui_slider_main_default_style);
    lv_style_set_radius(&gui_slider_main_default_style, 50);
    lv_style_set_bg_color(&gui_slider_main_default_style, lv_color_make(0xe2, 0xe5, 0xe9));
    lv_style_set_bg_grad_color(&gui_slider_main_default_style, lv_color_make(0x21, 0x95, 0xf6));
    lv_style_set_bg_grad_dir(&gui_slider_main_default_style, LV_GRAD_DIR_NONE);
    lv_style_set_bg_opa(&gui_slider_main_default_style, 255);
    lv_style_set_shadow_width(&gui_slider_main_default_style, 0);
    lv_style_set_shadow_color(&gui_slider_main_default_style, lv_color_make(0x21, 0x95, 0xf6));
    lv_style_set_shadow_opa(&gui_slider_main_default_style, 255);
    lv_style_set_shadow_spread(&gui_slider_main_default_style, 0);
    lv_style_set_shadow_ofs_x(&gui_slider_main_default_style, 0);
    lv_style_set_shadow_ofs_y(&gui_slider_main_default_style, 0);
    lv_style_set_outline_color(&gui_slider_main_default_style, lv_color_make(0x21, 0x95, 0xf6));
    lv_style_set_outline_width(&gui_slider_main_default_style, 0);
    lv_style_set_outline_opa(&gui_slider_main_default_style, 0);
    lv_style_set_outline_pad(&gui_slider_main_default_style, 0);
    lv_style_init(&gui_slider_indicator_default_style);
    lv_style_set_radius(&gui_slider_indicator_default_style, 50);
    lv_style_set_bg_color(&gui_slider_indicator_default_style, lv_color_make(0xff, 0x3a, 0x3a));
    lv_style_set_bg_grad_color(&gui_slider_indicator_default_style, lv_color_make(0x21, 0x95, 0xf6));
    lv_style_set_bg_grad_dir(&gui_slider_indicator_default_style, LV_GRAD_DIR_NONE);
    lv_style_set_bg_opa(&gui_slider_indicator_default_style, 204);
    lv_style_init(&gui_slider_knob_default_style);
    lv_style_set_radius(&gui_slider_knob_default_style, 50);
    lv_style_set_bg_color(&gui_slider_knob_default_style, lv_color_make(0xff, 0xff, 0xff));
    lv_style_set_bg_grad_color(&gui_slider_knob_default_style, lv_color_make(0x21, 0x95, 0xf6));
    lv_style_set_bg_grad_dir(&gui_slider_knob_default_style, LV_GRAD_DIR_NONE);
    lv_style_set_bg_opa(&gui_slider_knob_default_style, 255);

    // img
    lv_style_init(&gui_img_main_default_style);
    lv_style_set_radius(&gui_img_main_default_style, 0);
    lv_style_set_clip_corner(&gui_img_main_default_style, true);
    lv_style_set_bg_color(&gui_img_main_default_style, lv_color_make(0xff, 0xff, 0xff));
    lv_style_set_bg_grad_color(&gui_img_main_default_style, lv_color_make(0xff, 0xff, 0xff));
    lv_style_set_bg_grad_dir(&gui_img_main_default_style, LV_GRAD_DIR_NONE);
    lv_style_set_bg_opa(&gui_img_main_default_style, 0);
    lv_style_set_outline_color(&gui_img_main_default_style, lv_color_make(0x21, 0x95, 0xf6));
    lv_style_set_outline_width(&gui_img_main_default_style, 0);
    lv_style_set_outline_opa(&gui_img_main_default_style, 128);
    lv_style_set_outline_pad(&gui_img_main_default_style, 0);
    lv_style_set_img_recolor(&gui_img_main_default_style, lv_color_make(0x7E, 0x7E, 0x7E));
    lv_style_set_img_recolor_opa(&gui_img_main_default_style, 204);
    lv_style_set_img_opa(&gui_img_main_default_style, 255);

    // scr
    lv_style_init(&gui_scr_main_default_style);
    lv_style_set_bg_color(&gui_scr_main_default_style, lv_color_make(0x55, 0xaa, 0xa5));
    lv_style_set_bg_grad_color(&gui_scr_main_default_style, lv_color_make(0x21, 0x95, 0xf6));
    lv_style_set_bg_grad_dir(&gui_scr_main_default_style, LV_GRAD_DIR_NONE);
    lv_style_set_bg_opa(&gui_scr_main_default_style, 255);
    lv_style_set_border_color(&gui_scr_main_default_style, lv_color_make(0x21, 0x95, 0xf6));
    lv_style_set_border_width(&gui_scr_main_default_style, 0);
    lv_style_set_border_opa(&gui_scr_main_default_style, 255);

    // imgbtn
    lv_style_init(&gui_imgbtn_main_default_style);
    lv_style_set_radius(&gui_imgbtn_main_default_style, 0);
    lv_style_set_clip_corner(&gui_imgbtn_main_default_style, true);
    lv_style_set_bg_color(&gui_imgbtn_main_default_style, lv_color_make(0xff, 0xff, 0xff));
    lv_style_set_bg_grad_color(&gui_imgbtn_main_default_style, lv_color_make(0xff, 0xff, 0xff));
    lv_style_set_bg_grad_dir(&gui_imgbtn_main_default_style, LV_GRAD_DIR_NONE);
    lv_style_set_bg_opa(&gui_imgbtn_main_default_style, 0);
    lv_style_set_shadow_width(&gui_imgbtn_main_default_style, 0);
    lv_style_set_shadow_color(&gui_imgbtn_main_default_style, lv_color_make(0x21, 0x95, 0xf6));
    lv_style_set_shadow_opa(&gui_imgbtn_main_default_style, 255);
    lv_style_set_shadow_spread(&gui_imgbtn_main_default_style, 0);
    lv_style_set_shadow_ofs_x(&gui_imgbtn_main_default_style, 0);
    lv_style_set_shadow_ofs_y(&gui_imgbtn_main_default_style, 0);
    lv_style_set_outline_color(&gui_imgbtn_main_default_style, lv_color_make(0x21, 0x95, 0xf6));
    lv_style_set_outline_width(&gui_imgbtn_main_default_style, 0);
    lv_style_set_outline_opa(&gui_imgbtn_main_default_style, 128);
    lv_style_set_outline_pad(&gui_imgbtn_main_default_style, 0);
    lv_style_set_text_color(&gui_imgbtn_main_default_style, lv_color_make(0x00, 0x00, 0x00));
    lv_style_set_text_font(&gui_imgbtn_main_default_style, &lv_font_FangZhengKaiTiJianTi_1_12);
    lv_style_set_text_letter_space(&gui_imgbtn_main_default_style, 0);
    lv_style_set_text_align(&gui_imgbtn_main_default_style, LV_TEXT_ALIGN_CENTER);
    lv_style_set_img_recolor(&gui_imgbtn_main_default_style, lv_color_make(0xff, 0xff, 0xff));
    lv_style_set_img_recolor_opa(&gui_imgbtn_main_default_style, 0);
    lv_style_set_img_opa(&gui_imgbtn_main_default_style, 255);
    lv_style_init(&gui_imgbtn_main_focused_style);
    lv_style_set_radius(&gui_imgbtn_main_focused_style, 0);
    lv_style_set_clip_corner(&gui_imgbtn_main_focused_style, true);
    lv_style_set_bg_color(&gui_imgbtn_main_focused_style, lv_color_make(0xff, 0xff, 0xff));
    lv_style_set_bg_grad_color(&gui_imgbtn_main_focused_style, lv_color_make(0xff, 0xff, 0xff));
    lv_style_set_bg_grad_dir(&gui_imgbtn_main_focused_style, LV_GRAD_DIR_NONE);
    lv_style_set_bg_opa(&gui_imgbtn_main_focused_style, 0);
    lv_style_set_shadow_width(&gui_imgbtn_main_focused_style, 0);
    lv_style_set_shadow_color(&gui_imgbtn_main_focused_style, lv_color_make(0x21, 0x95, 0xf6));
    lv_style_set_shadow_opa(&gui_imgbtn_main_focused_style, 255);
    lv_style_set_shadow_spread(&gui_imgbtn_main_focused_style, 0);
    lv_style_set_shadow_ofs_x(&gui_imgbtn_main_focused_style, 0);
    lv_style_set_shadow_ofs_y(&gui_imgbtn_main_focused_style, 0);
    lv_style_set_outline_color(&gui_imgbtn_main_focused_style, lv_color_make(0x21, 0x95, 0xf6));
    lv_style_set_outline_width(&gui_imgbtn_main_focused_style, 0);
    lv_style_set_outline_opa(&gui_imgbtn_main_focused_style, 0);
    lv_style_set_outline_pad(&gui_imgbtn_main_focused_style, 0);
    lv_style_set_text_color(&gui_imgbtn_main_focused_style, lv_color_make(0x00, 0x00, 0x00));
    lv_style_set_text_font(&gui_imgbtn_main_focused_style, &lv_font_FangZhengKaiTiJianTi_1_12);
    lv_style_set_img_recolor(&gui_imgbtn_main_focused_style, lv_color_make(0xff, 0xff, 0xff));
    lv_style_set_img_recolor_opa(&gui_imgbtn_main_focused_style, 0);
    lv_style_set_img_opa(&gui_imgbtn_main_focused_style, 255);
    lv_style_init(&gui_imgbtn_main_pressed_style);
    lv_style_set_radius(&gui_imgbtn_main_pressed_style, 0);
    lv_style_set_clip_corner(&gui_imgbtn_main_pressed_style, true);
    lv_style_set_bg_color(&gui_imgbtn_main_pressed_style, lv_color_make(0xff, 0xff, 0xff));
    lv_style_set_bg_grad_color(&gui_imgbtn_main_pressed_style, lv_color_make(0xff, 0xff, 0xff));
    lv_style_set_bg_grad_dir(&gui_imgbtn_main_pressed_style, LV_GRAD_DIR_NONE);
    lv_style_set_bg_opa(&gui_imgbtn_main_pressed_style, 0);
    lv_style_set_shadow_width(&gui_imgbtn_main_pressed_style, 0);
    lv_style_set_shadow_color(&gui_imgbtn_main_pressed_style, lv_color_make(0x21, 0x95, 0xf6));
    lv_style_set_shadow_opa(&gui_imgbtn_main_pressed_style, 255);
    lv_style_set_shadow_spread(&gui_imgbtn_main_pressed_style, 0);
    lv_style_set_shadow_ofs_x(&gui_imgbtn_main_pressed_style, 0);
    lv_style_set_shadow_ofs_y(&gui_imgbtn_main_pressed_style, 0);
    lv_style_set_text_color(&gui_imgbtn_main_pressed_style, lv_color_make(0xFF, 0x33, 0xFF));
    lv_style_set_text_font(&gui_imgbtn_main_pressed_style, &lv_font_FangZhengKaiTiJianTi_1_12);
    lv_style_set_img_recolor(&gui_imgbtn_main_pressed_style, lv_color_make(0xAA, 0xAA, 0xAA));
    lv_style_set_img_recolor_opa(&gui_imgbtn_main_pressed_style, 128);
    lv_style_set_img_opa(&gui_imgbtn_main_pressed_style, 255);
    lv_style_init(&gui_imgbtn_main_checked_style);
    lv_style_set_radius(&gui_imgbtn_main_checked_style, 0);
    lv_style_set_clip_corner(&gui_imgbtn_main_checked_style, true);
    lv_style_set_bg_color(&gui_imgbtn_main_checked_style, lv_color_make(0xff, 0xff, 0xff));
    lv_style_set_bg_grad_color(&gui_imgbtn_main_checked_style, lv_color_make(0xff, 0xff, 0xff));
    lv_style_set_bg_grad_dir(&gui_imgbtn_main_checked_style, LV_GRAD_DIR_NONE);
    lv_style_set_bg_opa(&gui_imgbtn_main_checked_style, 0);
    lv_style_set_shadow_width(&gui_imgbtn_main_checked_style, 0);
    lv_style_set_shadow_color(&gui_imgbtn_main_checked_style, lv_color_make(0x21, 0x95, 0xf6));
    lv_style_set_shadow_opa(&gui_imgbtn_main_checked_style, 255);
    lv_style_set_shadow_spread(&gui_imgbtn_main_checked_style, 0);
    lv_style_set_shadow_ofs_x(&gui_imgbtn_main_checked_style, 0);
    lv_style_set_shadow_ofs_y(&gui_imgbtn_main_checked_style, 0);
    lv_style_set_text_color(&gui_imgbtn_main_checked_style, lv_color_make(0xFF, 0x33, 0xFF));
    lv_style_set_text_font(&gui_imgbtn_main_checked_style, &lv_font_FangZhengKaiTiJianTi_1_12);
    lv_style_set_img_recolor(&gui_imgbtn_main_checked_style, lv_color_make(0x00, 0x00, 0x00));
    lv_style_set_img_recolor_opa(&gui_imgbtn_main_checked_style, 0);
    lv_style_set_img_opa(&gui_imgbtn_main_checked_style, 255);

    // sw
    lv_style_init(&gui_sw_main_default_style);
    lv_style_set_radius(&gui_sw_main_default_style, 50);
    lv_style_set_bg_color(&gui_sw_main_default_style, lv_color_make(0xe6, 0xe2, 0xe6));
    lv_style_set_bg_grad_color(&gui_sw_main_default_style, lv_color_make(0xe6, 0xe2, 0xe6));
    lv_style_set_bg_grad_dir(&gui_sw_main_default_style, LV_GRAD_DIR_NONE);
    lv_style_set_bg_opa(&gui_sw_main_default_style, 255);
    lv_style_set_shadow_width(&gui_sw_main_default_style, 0);
    lv_style_set_shadow_color(&gui_sw_main_default_style, lv_color_make(0x21, 0x95, 0xf6));
    lv_style_set_shadow_opa(&gui_sw_main_default_style, 255);
    lv_style_set_shadow_spread(&gui_sw_main_default_style, 0);
    lv_style_set_shadow_ofs_x(&gui_sw_main_default_style, 0);
    lv_style_set_shadow_ofs_y(&gui_sw_main_default_style, 0);
    lv_style_set_border_color(&gui_sw_main_default_style, lv_color_make(0x21, 0x95, 0xf6));
    lv_style_set_border_width(&gui_sw_main_default_style, 0);
    lv_style_set_border_opa(&gui_sw_main_default_style, 255);
    lv_style_set_border_side(&gui_sw_main_default_style, LV_BORDER_SIDE_FULL);
    lv_style_set_outline_color(&gui_sw_main_default_style, lv_color_make(0x21, 0x95, 0xf6));
    lv_style_set_outline_width(&gui_sw_main_default_style, 0);
    lv_style_set_outline_opa(&gui_sw_main_default_style, 128);
    lv_style_set_outline_pad(&gui_sw_main_default_style, 0);
    lv_style_init(&gui_sw_indicator_checked_style);
    lv_style_set_bg_color(&gui_sw_indicator_checked_style, lv_color_make(0xff, 0x3a, 0x3a));
    lv_style_set_bg_grad_color(&gui_sw_indicator_checked_style, lv_color_make(0x21, 0x95, 0xf6));
    lv_style_set_bg_grad_dir(&gui_sw_indicator_checked_style, LV_GRAD_DIR_NONE);
    lv_style_set_bg_opa(&gui_sw_indicator_checked_style, 255);
    lv_style_set_border_color(&gui_sw_indicator_checked_style, lv_color_make(0x21, 0x95, 0xf6));
    lv_style_set_border_width(&gui_sw_indicator_checked_style, 0);
    lv_style_set_border_opa(&gui_sw_indicator_checked_style, 255);
    lv_style_set_border_side(&gui_sw_indicator_checked_style, LV_BORDER_SIDE_FULL);
    lv_style_init(&gui_sw_knob_default_style);
    lv_style_set_radius(&gui_sw_knob_default_style, 100);
    lv_style_set_bg_color(&gui_sw_knob_default_style, lv_color_make(0xff, 0xff, 0xff));
    lv_style_set_bg_grad_color(&gui_sw_knob_default_style, lv_color_make(0xff, 0xff, 0xff));
    lv_style_set_bg_grad_dir(&gui_sw_knob_default_style, LV_GRAD_DIR_NONE);
    lv_style_set_bg_opa(&gui_sw_knob_default_style, 255);
    lv_style_set_border_color(&gui_sw_knob_default_style, lv_color_make(0x21, 0x95, 0xf6));
    lv_style_set_border_width(&gui_sw_knob_default_style, 0);
    lv_style_set_border_opa(&gui_sw_knob_default_style, 255);
    lv_style_set_border_side(&gui_sw_knob_default_style, LV_BORDER_SIDE_FULL);

    // ddlist
    lv_style_init(&gui_ddlist_main_default_style);
    lv_style_set_radius(&gui_ddlist_main_default_style, 100);
    lv_style_set_bg_color(&gui_ddlist_main_default_style, lv_color_make(0xf0, 0xf3, 0xf6));
    lv_style_set_bg_grad_color(&gui_ddlist_main_default_style, lv_color_make(0xff, 0xff, 0xff));
    lv_style_set_bg_grad_dir(&gui_ddlist_main_default_style, LV_GRAD_DIR_NONE);
    lv_style_set_bg_opa(&gui_ddlist_main_default_style, 255);
    lv_style_set_shadow_width(&gui_ddlist_main_default_style, 0);
    lv_style_set_shadow_color(&gui_ddlist_main_default_style, lv_color_make(0x21, 0x95, 0xf6));
    lv_style_set_shadow_opa(&gui_ddlist_main_default_style, 255);
    lv_style_set_shadow_spread(&gui_ddlist_main_default_style, 0);
    lv_style_set_shadow_ofs_x(&gui_ddlist_main_default_style, 0);
    lv_style_set_shadow_ofs_y(&gui_ddlist_main_default_style, 0);
    lv_style_set_border_color(&gui_ddlist_main_default_style, lv_color_make(0xe1, 0xe6, 0xee));
    lv_style_set_border_width(&gui_ddlist_main_default_style, 0);
    lv_style_set_border_opa(&gui_ddlist_main_default_style, 0);
    lv_style_set_border_side(&gui_ddlist_main_default_style, LV_BORDER_SIDE_FULL);
    lv_style_set_outline_color(&gui_ddlist_main_default_style, lv_color_make(0x21, 0x95, 0xf6));
    lv_style_set_outline_width(&gui_ddlist_main_default_style, 0);
    lv_style_set_outline_opa(&gui_ddlist_main_default_style, 128);
    lv_style_set_outline_pad(&gui_ddlist_main_default_style, 0);
    lv_style_set_text_color(&gui_ddlist_main_default_style, lv_color_make(0x64, 0x6c, 0x7c));
    lv_style_set_text_font(&gui_ddlist_main_default_style, &lv_font_FangZhengKaiTiJianTi_1_24);
    lv_style_set_text_letter_space(&gui_ddlist_main_default_style, 0);
    lv_style_set_pad_left(&gui_ddlist_main_default_style, 6);
    lv_style_set_pad_right(&gui_ddlist_main_default_style, 6);
    lv_style_set_pad_top(&gui_ddlist_main_default_style, 8);
    lv_style_init(&gui_ddlist_selected_checked_style);
    lv_style_set_radius(&gui_ddlist_selected_checked_style, 0);
    lv_style_set_bg_color(&gui_ddlist_selected_checked_style, lv_color_make(0xf2, 0xf3, 0xf4));
    lv_style_set_bg_grad_color(&gui_ddlist_selected_checked_style, lv_color_make(0xB0, 0xB8, 0xB8));
    lv_style_set_bg_grad_dir(&gui_ddlist_selected_checked_style, LV_GRAD_DIR_NONE);
    lv_style_set_bg_opa(&gui_ddlist_selected_checked_style, 255);
    lv_style_set_border_color(&gui_ddlist_selected_checked_style, lv_color_make(0xe1, 0xe6, 0xee));
    lv_style_set_border_width(&gui_ddlist_selected_checked_style, 1);
    lv_style_set_border_opa(&gui_ddlist_selected_checked_style, 0);
    lv_style_set_border_side(&gui_ddlist_selected_checked_style, LV_BORDER_SIDE_FULL);
    lv_style_set_text_color(&gui_ddlist_selected_checked_style, lv_color_make(0x64, 0x6c, 0x7c));
    lv_style_set_text_font(&gui_ddlist_selected_checked_style, &lv_font_FangZhengKaiTiJianTi_1_24);
    lv_style_set_text_letter_space(&gui_ddlist_selected_checked_style, 0);
    lv_style_init(&gui_ddlist_dropdown_list_default_style);
    lv_style_set_radius(&gui_ddlist_dropdown_list_default_style, 10);
    lv_style_set_bg_color(&gui_ddlist_dropdown_list_default_style, lv_color_make(0xf0, 0xf3, 0xf6));
    lv_style_set_bg_grad_color(&gui_ddlist_dropdown_list_default_style, lv_color_make(0xff, 0xff, 0xff));
    lv_style_set_bg_grad_dir(&gui_ddlist_dropdown_list_default_style, LV_GRAD_DIR_NONE);
    lv_style_set_bg_opa(&gui_ddlist_dropdown_list_default_style, 0);
    lv_style_set_border_color(&gui_ddlist_dropdown_list_default_style, lv_color_make(0xe1, 0xe6, 0xee));
    lv_style_set_border_width(&gui_ddlist_dropdown_list_default_style, 0);
    lv_style_set_border_opa(&gui_ddlist_dropdown_list_default_style, 0);
    lv_style_set_border_side(&gui_ddlist_dropdown_list_default_style, LV_BORDER_SIDE_FULL);
    lv_style_set_text_color(&gui_ddlist_dropdown_list_default_style, lv_color_make(0x64, 0x6c, 0x7c));
    lv_style_set_text_font(&gui_ddlist_dropdown_list_default_style, &lv_font_FangZhengKaiTiJianTi_1_24);
    lv_style_set_text_letter_space(&gui_ddlist_dropdown_list_default_style, 0);
    lv_style_set_max_height(&gui_ddlist_dropdown_list_default_style, 90);
    lv_style_init(&gui_ddlist_scrollbar_default_style);
    lv_style_set_radius(&gui_ddlist_scrollbar_default_style, 3);
    lv_style_set_bg_color(&gui_ddlist_scrollbar_default_style, lv_color_make(0xD7, 0xDD, 0xDD));
    lv_style_set_bg_opa(&gui_ddlist_scrollbar_default_style, 255);

    // label
    lv_style_init(&gui_label_main_default_style);
    lv_style_set_radius(&gui_label_main_default_style, 0);
    lv_style_set_bg_color(&gui_label_main_default_style, lv_color_make(0x21, 0x95, 0xf6));
    lv_style_set_bg_grad_color(&gui_label_main_default_style, lv_color_make(0x21, 0x95, 0xf6));
    lv_style_set_bg_grad_dir(&gui_label_main_default_style, LV_GRAD_DIR_NONE);
    lv_style_set_bg_opa(&gui_label_main_default_style, 0);
    lv_style_set_shadow_width(&gui_label_main_default_style, 0);
    lv_style_set_shadow_color(&gui_label_main_default_style, lv_color_make(0x21, 0x95, 0xf6));
    lv_style_set_shadow_opa(&gui_label_main_default_style, 255);
    lv_style_set_shadow_spread(&gui_label_main_default_style, 0);
    lv_style_set_shadow_ofs_x(&gui_label_main_default_style, 0);
    lv_style_set_shadow_ofs_y(&gui_label_main_default_style, 0);
    lv_style_set_border_color(&gui_label_main_default_style, lv_color_make(0x21, 0x95, 0xf6));
    lv_style_set_border_width(&gui_label_main_default_style, 0);
    lv_style_set_border_opa(&gui_label_main_default_style, 255);
    lv_style_set_border_side(&gui_label_main_default_style, LV_BORDER_SIDE_FULL);
    lv_style_set_outline_color(&gui_label_main_default_style, lv_color_make(0x21, 0x95, 0xf6));
    lv_style_set_outline_width(&gui_label_main_default_style, 0);
    lv_style_set_outline_opa(&gui_label_main_default_style, 128);
    lv_style_set_outline_pad(&gui_label_main_default_style, 0);
    lv_style_set_text_color(&gui_label_main_default_style, lv_color_make(0x64, 0x6c, 0x7c));
    lv_style_set_text_font(&gui_label_main_default_style, &lv_font_FangZhengKaiTiJianTi_1_24);
    lv_style_set_text_letter_space(&gui_label_main_default_style, 2);
    lv_style_set_text_line_space(&gui_label_main_default_style, 0);
    lv_style_set_text_align(&gui_label_main_default_style, LV_TEXT_ALIGN_CENTER);
    lv_style_set_pad_left(&gui_label_main_default_style, 0);
    lv_style_set_pad_right(&gui_label_main_default_style, 0);
    lv_style_set_pad_top(&gui_label_main_default_style, 0);
    lv_style_set_pad_bottom(&gui_label_main_default_style, 0);

    // cont
    lv_style_init(&gui_cont_main_default_style);
    lv_style_set_radius(&gui_cont_main_default_style, 15);
    lv_style_set_bg_color(&gui_cont_main_default_style, lv_color_make(0xD3, 0xD3, 0xD3));
    lv_style_set_bg_grad_color(&gui_cont_main_default_style, lv_color_make(0xff, 0xff, 0xff));
    lv_style_set_bg_grad_dir(&gui_cont_main_default_style, LV_GRAD_DIR_NONE);
    lv_style_set_bg_opa(&gui_cont_main_default_style, 255);
    lv_style_set_shadow_width(&gui_cont_main_default_style, 0);
    lv_style_set_shadow_color(&gui_cont_main_default_style, lv_color_make(0x21, 0x95, 0xf6));
    lv_style_set_shadow_opa(&gui_cont_main_default_style, 255);
    lv_style_set_shadow_spread(&gui_cont_main_default_style, 0);
    lv_style_set_shadow_ofs_x(&gui_cont_main_default_style, 0);
    lv_style_set_shadow_ofs_y(&gui_cont_main_default_style, 0);
    lv_style_set_border_color(&gui_cont_main_default_style, lv_color_make(0x21, 0x95, 0xf6));
    lv_style_set_border_width(&gui_cont_main_default_style, 0);
    lv_style_set_border_opa(&gui_cont_main_default_style, 255);
    lv_style_set_border_side(&gui_cont_main_default_style, LV_BORDER_SIDE_FULL);
    lv_style_set_outline_color(&gui_cont_main_default_style, lv_color_make(0x21, 0x95, 0xf6));
    lv_style_set_outline_width(&gui_cont_main_default_style, 0);
    lv_style_set_outline_opa(&gui_cont_main_default_style, 128);
    lv_style_set_outline_pad(&gui_cont_main_default_style, 0);
    lv_style_set_pad_left(&gui_cont_main_default_style, 0);
    lv_style_set_pad_right(&gui_cont_main_default_style, 0);
    lv_style_set_pad_top(&gui_cont_main_default_style, 0);
    lv_style_set_pad_bottom(&gui_cont_main_default_style, 0);

    // btn
    lv_style_init(&gui_btn_main_default_style);
    lv_style_set_radius(&gui_btn_main_default_style, 100);
    lv_style_set_bg_color(&gui_btn_main_default_style, lv_color_make(0xF4, 0xF8, 0xFD));
    lv_style_set_bg_grad_color(&gui_btn_main_default_style, lv_color_make(0x21, 0x95, 0xf6));
    lv_style_set_bg_grad_dir(&gui_btn_main_default_style, LV_GRAD_DIR_NONE);
    lv_style_set_bg_opa(&gui_btn_main_default_style, 255);
    lv_style_set_shadow_width(&gui_btn_main_default_style, 0);
    lv_style_set_shadow_color(&gui_btn_main_default_style, lv_color_make(0x21, 0x95, 0xf6));
    lv_style_set_shadow_opa(&gui_btn_main_default_style, 255);
    lv_style_set_shadow_spread(&gui_btn_main_default_style, 0);
    lv_style_set_shadow_ofs_x(&gui_btn_main_default_style, 0);
    lv_style_set_shadow_ofs_y(&gui_btn_main_default_style, 0);
    lv_style_set_border_color(&gui_btn_main_default_style, lv_color_make(0xf0, 0xf3, 0xf6));
    lv_style_set_border_width(&gui_btn_main_default_style, 2);
    lv_style_set_border_opa(&gui_btn_main_default_style, 255);
    lv_style_set_border_side(&gui_btn_main_default_style, LV_BORDER_SIDE_FULL);
    lv_style_set_outline_color(&gui_btn_main_default_style, lv_color_make(0x21, 0x95, 0xf6));
    lv_style_set_outline_width(&gui_btn_main_default_style, 0);
    lv_style_set_outline_opa(&gui_btn_main_default_style, 128);
    lv_style_set_outline_pad(&gui_btn_main_default_style, 0);
    lv_style_set_text_color(&gui_btn_main_default_style, lv_color_make(0x64, 0x6c, 0x7c));
    lv_style_set_text_font(&gui_btn_main_default_style, &lv_font_FangZhengKaiTiJianTi_1_24);
    lv_style_set_text_letter_space(&gui_btn_main_default_style, 0);
    lv_style_set_text_align(&gui_btn_main_default_style, LV_TEXT_ALIGN_CENTER);
    lv_style_init(&gui_btn_main_disabled_style);
    lv_style_set_radius(&gui_btn_main_disabled_style, 100);
    lv_style_set_bg_color(&gui_btn_main_disabled_style, lv_color_make(0xf0, 0xf3, 0xf6));
    lv_style_set_bg_grad_color(&gui_btn_main_disabled_style, lv_color_make(0x21, 0x95, 0xf6));
    lv_style_set_bg_grad_dir(&gui_btn_main_disabled_style, LV_GRAD_DIR_NONE);
    lv_style_set_bg_opa(&gui_btn_main_disabled_style, 255);
    lv_style_set_shadow_width(&gui_btn_main_disabled_style, 0);
    lv_style_set_shadow_color(&gui_btn_main_disabled_style, lv_color_make(0x21, 0x95, 0xf6));
    lv_style_set_shadow_opa(&gui_btn_main_disabled_style, 255);
    lv_style_set_shadow_spread(&gui_btn_main_disabled_style, 0);
    lv_style_set_shadow_ofs_x(&gui_btn_main_disabled_style, 0);
    lv_style_set_shadow_ofs_y(&gui_btn_main_disabled_style, 0);
    lv_style_set_border_color(&gui_btn_main_disabled_style, lv_color_make(0xf0, 0xf3, 0xf6));
    lv_style_set_border_width(&gui_btn_main_disabled_style, 2);
    lv_style_set_border_opa(&gui_btn_main_disabled_style, 255);
    lv_style_set_border_side(&gui_btn_main_disabled_style, LV_BORDER_SIDE_FULL);
    lv_style_set_text_color(&gui_btn_main_disabled_style, lv_color_make(0xD5, 0xDA, 0xE6));
    lv_style_set_text_font(&gui_btn_main_disabled_style, &lv_font_FangZhengKaiTiJianTi_1_24);

}

void ui_style_set(lv_obj_t *obj, gui_ctrl_type_t type)
{
    switch (type) {
    case GUI_CTRL_SLIDER:
        lv_obj_add_style(obj, &gui_slider_main_default_style, LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_add_style(obj, &gui_slider_indicator_default_style, LV_PART_INDICATOR | LV_STATE_DEFAULT);
        lv_obj_add_style(obj, &gui_slider_knob_default_style, LV_PART_KNOB | LV_STATE_DEFAULT);
        break;
    case GUI_CTRL_IMG:
        lv_obj_add_style(obj, &gui_img_main_default_style, LV_PART_MAIN | LV_STATE_DEFAULT);
        break;
    case GUI_CTRL_SCR:
        lv_obj_add_style(obj, &gui_scr_main_default_style, LV_PART_MAIN | LV_STATE_DEFAULT);
        break;
    case GUI_CTRL_IMGBTN:
        lv_obj_add_style(obj, &gui_imgbtn_main_default_style, LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_add_style(obj, &gui_imgbtn_main_pressed_style, LV_PART_MAIN | LV_STATE_PRESSED);
        lv_obj_add_style(obj, &gui_imgbtn_main_checked_style, LV_PART_MAIN | LV_STATE_CHECKED);
        break;
    case GUI_CTRL_SWITCH:
        lv_obj_add_style(obj, &gui_sw_main_default_style, LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_add_style(obj, &gui_sw_indicator_checked_style, LV_PART_INDICATOR | LV_STATE_CHECKED);
        lv_obj_add_style(obj, &gui_sw_knob_default_style, LV_PART_KNOB | LV_STATE_DEFAULT);
        break;
    case GUI_CTRL_DROPDOWN:
        lv_obj_add_style(obj, &gui_ddlist_main_default_style, LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_add_style(obj, &gui_ddlist_selected_checked_style, LV_PART_SELECTED | LV_STATE_CHECKED);
        lv_obj_add_style(obj, &gui_ddlist_dropdown_list_default_style, LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_add_style(obj, &gui_ddlist_scrollbar_default_style, LV_PART_SCROLLBAR | LV_STATE_DEFAULT);
        break;
    case GUI_CTRL_LABEL:
        lv_obj_add_style(obj, &gui_label_main_default_style, LV_PART_MAIN | LV_STATE_DEFAULT);
        break;
    case GUI_CTRL_CONT:
        lv_obj_add_style(obj, &gui_cont_main_default_style, LV_PART_MAIN | LV_STATE_DEFAULT);
        break;
    case GUI_CTRL_BUTTON:
        lv_obj_add_style(obj, &gui_btn_main_default_style, LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_add_style(obj, &gui_btn_main_disabled_style, LV_PART_MAIN | LV_STATE_DISABLED);
        break;
    default:
        break;
    }
}

