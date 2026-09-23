#include "app_config.h"
#ifdef CONFIG_UI_STYLE_LY_ENABLE
/*Generate Code, Do NOT Edit!*/
#include "lvgl.h"
#include "../gui_guider.h"
#include "./gui_timelines.h"
#if LV_USE_GUIBUILDER_SIMULATOR
#include <stdio.h>
#endif

void gui_anim_delete_cb(lv_anim_t *anim)
{
    lv_mem_free(anim->var);
    anim->var = NULL;
}

//Init Timelines
void gui_timelines_init(lv_ui *ui)
{
    gui_timeline_timeline_init(ui);
}
//Stop Timelines
void gui_timelines_stop()
{
    gui_timeline_stop(&gui_timeline_timeline);
}
//Delete Timelines
void gui_timelines_delete()
{
    gui_timeline_delete(&gui_timeline_timeline);
}

void gui_anim_set_var(lv_anim_t *anim, lv_obj_t *obj, lv_anim_exec_xcb_t exec_cb, gui_anim_data_t data)
{
    lv_anim_set_deleted_cb(anim, gui_anim_delete_cb);
    lv_anim_set_exec_cb(anim, exec_cb);
    gui_anim_var_t *var = lv_mem_alloc(sizeof(gui_anim_var_t));
    if (var == NULL) {
        return;
    }
    var->obj = obj;
    var->exec_cb = exec_cb;
    var->data = data;
    lv_anim_set_var(anim, var);
}

void gui_timeline_start(gui_timeline_t *timeline)
{
    if (timeline == NULL) {
        return;
    }
    if (timeline->timeline != NULL) {
        int32_t temp_repeat_count = timeline->_repeat_count;
        timeline->_repeat_count = 0;
        lv_anim_timeline_del(timeline->timeline);
        timeline->_repeat_count = temp_repeat_count;
    }

    int32_t res = timeline->init_cb(&guider_ui);
    if (res != -1) {
        lv_anim_timeline_start(timeline->timeline);
    }
}

void gui_timeline_stop(gui_timeline_t *timeline)
{
    if (timeline == NULL) {
        return;
    }
    timeline->_repeat_count = 0;
    if (timeline->timeline != NULL) {
        lv_anim_timeline_stop(timeline->timeline);
    }
}

void gui_timeline_delete(gui_timeline_t *timeline)
{
    if (timeline == NULL) {
        return;
    }
    timeline->_repeat_count = 0;
    timeline->_period = 0;
    if (timeline->timeline != NULL) {
        lv_anim_timeline_del(timeline->timeline);
        timeline->timeline = NULL;
    }
}

void gui_timeline_set_period(gui_timeline_t *timeline, uint32_t period)
{
    if (timeline == NULL) {
        return;
    }
    timeline->_period = period;
}

void gui_timeline_set_repeat_count(gui_timeline_t *timeline, int32_t repeat_count)
{
    if (timeline == NULL) {
        return;
    }
    timeline->_repeat_count = repeat_count;
}

void gui_anim_set_zoom(void *var, int32_t v)
{
    lv_obj_t *obj = GUI_ANIM_OBJ(var);
    if (obj == NULL || !lv_obj_is_valid(obj)) {
        return;
    }
    lv_img_set_zoom(obj, v);
}
void gui_anim_set_y(void *var, int32_t v)
{
    lv_obj_t *obj = GUI_ANIM_OBJ(var);
    if (obj == NULL || !lv_obj_is_valid(obj)) {
        return;
    }
    lv_obj_set_y(obj, v);
}

#endif
