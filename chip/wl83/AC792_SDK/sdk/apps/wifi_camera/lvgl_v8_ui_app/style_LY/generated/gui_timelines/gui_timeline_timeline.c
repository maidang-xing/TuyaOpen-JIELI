#include "app_config.h"
#ifdef CONFIG_UI_STYLE_LY_ENABLE
/*Generate Code, Do NOT Edit!*/
#if LV_USE_GUIBUILDER_SIMULATOR
#include <stdio.h>
#endif
#include <stdlib.h>
#include "lvgl.h"
#include "../gui_guider.h"
#include "./gui_timeline_timeline.h"

gui_timeline_t gui_timeline_timeline = {
    .timeline = NULL,
    .init_cb = gui_timeline_timeline_init,
    ._repeat_count = 0,
    ._period = 0,
};
void gui_timeline_power_on_img_1_1_init(struct _lv_anim_t *a)
{
    lv_obj_t *var = (lv_obj_t *)a->var;
    lv_obj_set_x(var, 224);
    lv_obj_set_y(var, 400);
    lv_obj_set_width(var, 332);
    lv_obj_set_height(var, 82);
    lv_obj_set_style_bg_opa(var, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(var, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_color(var, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(var, LV_GRAD_DIR_NONE, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_radius(var, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_img_set_pivot(var, 0, 0);
    lv_img_set_angle(var, 0);
    lv_img_set_zoom(var, 215);
}

void gui_timeline_timeline_end_cb(struct _lv_anim_t *a)
{
    if (gui_timeline_timeline._repeat_count == -1) {
        gui_timeline_start(&gui_timeline_timeline);
    } else if (gui_timeline_timeline._repeat_count > 0) {
        gui_timeline_timeline._repeat_count--;
        gui_timeline_start(&gui_timeline_timeline);
    }
}
int32_t gui_timeline_timeline_init(lv_ui *ui)
{
    if (!ui->power_on) {
        return -1;
    }
    gui_timeline_timeline.timeline = lv_anim_timeline_create();
    if (!gui_timeline_timeline.timeline) {
        return -1;
    }
    lv_ui_power_on *ui_scr = ui_get_scr_ptr(ui, GUI_SCREEN_POWER_ON);
    if (!ui_scr) {
        return -1;
    }

    lv_anim_t power_on_img_1_1_init;
    lv_anim_init(&power_on_img_1_1_init);
    lv_anim_set_var(&power_on_img_1_1_init, ui_scr->power_on_img_1);
    lv_anim_set_start_cb(&power_on_img_1_1_init, gui_timeline_power_on_img_1_1_init);
    lv_anim_set_time(&power_on_img_1_1_init, 1);
    lv_anim_timeline_add(gui_timeline_timeline.timeline, 0, &power_on_img_1_1_init);

    lv_anim_t power_on_img_1_zoom_1_0_a;
    lv_anim_init(&power_on_img_1_zoom_1_0_a);
    lv_anim_set_early_apply(&power_on_img_1_zoom_1_0_a, false);
    lv_anim_set_values(&power_on_img_1_zoom_1_0_a, 215, 295);
    gui_anim_set_var(&power_on_img_1_zoom_1_0_a, ui_scr->power_on_img_1, (lv_anim_exec_xcb_t)gui_anim_set_zoom, (gui_anim_data_t) {
        .value_int = 0
    });
    lv_anim_set_path_cb(&power_on_img_1_zoom_1_0_a, lv_anim_path_linear);
    lv_anim_set_time(&power_on_img_1_zoom_1_0_a, 1050);
    lv_anim_timeline_add(gui_timeline_timeline.timeline, 0, &power_on_img_1_zoom_1_0_a);

    lv_anim_t power_on_img_1_top_1_0_a;
    lv_anim_init(&power_on_img_1_top_1_0_a);
    lv_anim_set_early_apply(&power_on_img_1_top_1_0_a, false);
    lv_anim_set_values(&power_on_img_1_top_1_0_a, 400, 185);
    gui_anim_set_var(&power_on_img_1_top_1_0_a, ui_scr->power_on_img_1, (lv_anim_exec_xcb_t)gui_anim_set_y, (gui_anim_data_t) {
        .value_int = 0
    });
    lv_anim_set_path_cb(&power_on_img_1_top_1_0_a, lv_anim_path_linear);
    lv_anim_set_time(&power_on_img_1_top_1_0_a, 1050);
    lv_anim_timeline_add(gui_timeline_timeline.timeline, 0, &power_on_img_1_top_1_0_a);

    lv_anim_t timeline_end_a;
    lv_anim_init(&timeline_end_a);
    lv_anim_set_time(&timeline_end_a, gui_timeline_timeline._period);
    lv_anim_set_deleted_cb(&timeline_end_a, gui_timeline_timeline_end_cb);
    lv_anim_timeline_add(gui_timeline_timeline.timeline, 1050, &timeline_end_a);
    return 0;
}

#endif

