/*Generate Code, Do NOT Edit!*/
#include "./gui_group.h"

void add_children_to_group(lv_obj_t *obj, lv_group_t *group);
void set_default_group_cb();

void gui_group_init()
{
    if (guider_ui.default_group == NULL) {
        guider_ui.default_group = lv_group_get_default();
    }
}

void gui_group_set_default(lv_group_t *group)
{
    if (group == NULL) {
        return;
    }

    if (guider_ui.default_group == group) {
        return set_default_group_cb();
    }
}

void gui_group_add_obj(lv_group_t *group, lv_obj_t *obj, bool is_add)
{
    if (group == NULL || obj == NULL) {
        return;
    }

    bool is_group_def = lv_obj_is_group_def(obj);
    if (is_group_def && is_add) {
        lv_group_add_obj(group, obj);
    }

    if (
#if LV_USE_LIST
        lv_obj_check_type(obj, &lv_list_class) ||
#endif
#if LV_USE_CALENDAR
        lv_obj_check_type(obj, &lv_calendar_class) ||
#endif
#if LV_USE_MSGBOX
        lv_obj_check_type(obj, &lv_msgbox_class) ||
#endif
#if LV_USE_TABVIEW
        lv_obj_check_type(obj, &lv_tabview_class) ||
#endif
#if LV_USE_CALENDAR_HEADER_ARROW
        lv_obj_check_type(obj, &lv_calendar_header_arrow_class) ||
#endif
#if LV_USE_CALENDAR_HEADER_DROPDOWN
        lv_obj_check_type(obj, &lv_calendar_header_dropdown_class) ||
#endif
        0) {
        add_children_to_group(obj, group);
#if LV_USE_WIN
    } else if (lv_obj_check_type(obj, &lv_win_class)) {
        lv_obj_t *header = lv_win_get_header(obj);
        add_children_to_group(header, group);
#endif
    }

    if (!is_group_def && is_add) {
        lv_group_add_obj(group, obj);
    }
}

void add_children_to_group(lv_obj_t *obj, lv_group_t *group)
{
    if (obj == NULL || group == NULL) {
        return;
    }

    int childCnt = lv_obj_get_child_cnt(obj);
    for (int i = 0; i < childCnt; i++) {
        lv_obj_t *child = lv_obj_get_child(obj, i);
        if (lv_obj_is_group_def(child)) {
            lv_group_add_obj(group, child);
        }
    }
}

void set_default_group_cb()
{
    if (guider_ui.default_group == NULL) {
        return;
    }

    lv_group_remove_all_objs(guider_ui.default_group);
    int32_t act_scr_id = gui_scr_get_id(gui_scr_get_act());

    if (act_scr_id == GUI_SCREEN_SYS_MENU) {
        lv_ui_sys_menu *ui_scr = ui_get_scr_ptr(&guider_ui, GUI_SCREEN_SYS_MENU);
        gui_group_add_obj(guider_ui.default_group, ui_scr->sys_menu_slider_2, true);
        gui_group_add_obj(guider_ui.default_group, ui_scr->sys_menu_slider_1, true);
    } else if (act_scr_id == GUI_SCREEN_EQ_MODIFY) {
        lv_ui_eq_modify *ui_scr = ui_get_scr_ptr(&guider_ui, GUI_SCREEN_EQ_MODIFY);
        gui_group_add_obj(guider_ui.default_group, ui_scr->eq_modify_slider_1, true);
        gui_group_add_obj(guider_ui.default_group, ui_scr->eq_modify_slider_2, true);
        gui_group_add_obj(guider_ui.default_group, ui_scr->eq_modify_slider_3, true);
        gui_group_add_obj(guider_ui.default_group, ui_scr->eq_modify_slider_4, true);
        gui_group_add_obj(guider_ui.default_group, ui_scr->eq_modify_slider_5, true);
        gui_group_add_obj(guider_ui.default_group, ui_scr->eq_modify_slider_6, true);
        gui_group_add_obj(guider_ui.default_group, ui_scr->eq_modify_slider_7, true);
        gui_group_add_obj(guider_ui.default_group, ui_scr->eq_modify_slider_8, true);
        gui_group_add_obj(guider_ui.default_group, ui_scr->eq_modify_slider_9, true);
        gui_group_add_obj(guider_ui.default_group, ui_scr->eq_modify_slider_10, true);
        gui_group_add_obj(guider_ui.default_group, ui_scr->eq_modify_ddlist_1, true);
    }
    lv_group_set_default(guider_ui.default_group);

    lv_indev_t *indev = NULL;
    while ((indev = lv_indev_get_next(indev)) != NULL) {
        lv_indev_set_group(indev, guider_ui.default_group);
    }
}
