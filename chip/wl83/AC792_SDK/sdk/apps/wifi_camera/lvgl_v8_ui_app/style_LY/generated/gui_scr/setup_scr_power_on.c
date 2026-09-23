#include "app_config.h"
#ifdef CONFIG_UI_STYLE_LY_ENABLE
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


lv_obj_t *setup_scr_power_on(lv_ui *ui)
{
    lv_ui_power_on *ui_scr = ui_get_scr_ptr(ui, GUI_SCREEN_POWER_ON);
    if (ui_scr == NULL) {
        ui_scr = lv_mem_alloc(sizeof(lv_ui_power_on));
        if (ui_scr == NULL) {
            return NULL;
        }
        memset(ui_scr, 0, sizeof(lv_ui_power_on));
        ui->power_on = ui_scr;
    }

    //Write codes power_on
    ui_scr->power_on = lv_obj_create(NULL);
    lv_obj_set_scrollbar_mode(ui_scr->power_on, LV_SCROLLBAR_MODE_OFF);
    ui_style_set(ui_scr->power_on, GUI_CTRL_SCR);

    //Set style for power_on. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
    lv_obj_set_style_bg_opa(ui_scr->power_on, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    //Write codes power_on_img_1
    ui_scr->power_on_img_1 = lv_img_create(ui_scr->power_on);
    lv_img_set_src(ui_scr->power_on_img_1, gui_get_res_path(GUI_RES_IMG_LOGO_PNG));
    lv_img_set_pivot(ui_scr->power_on_img_1, 0, 0);
    lv_img_set_angle(ui_scr->power_on_img_1, 0);
    lv_img_set_zoom(ui_scr->power_on_img_1, 256);
    lv_obj_set_pos(ui_scr->power_on_img_1, 234, 181);
    lv_obj_set_size(ui_scr->power_on_img_1, 332, 82);
    lv_obj_add_flag(ui_scr->power_on_img_1, LV_OBJ_FLAG_CLICKABLE);
    ui_style_set(ui_scr->power_on_img_1, GUI_CTRL_IMG);

    // Write Timer power_on_timer_1
    if (ui_scr->power_on_timer_1 != NULL) {
        lv_timer_del(ui_scr->power_on_timer_1);
    }
    ui_scr->power_on_timer_1 = lv_timer_create(power_on_timer_1_timer_cb, 1300, "");
    lv_timer_set_repeat_count(ui_scr->power_on_timer_1, 1);

    lv_obj_update_layout(ui_scr->power_on);
    ui_scr->power_on_del = false;
    i18n_refresh_texts(GUI_SCREEN_POWER_ON);

    //Init events for screen
    events_init_power_on(ui);
    return ui_scr->power_on;
}
void unload_scr_power_on(lv_ui *ui)
{
    lv_ui_power_on *ui_scr = ui_get_scr_ptr(ui, GUI_SCREEN_POWER_ON);
    if (ui_scr->power_on_timer_1 != NULL) {
        lv_timer_del(ui_scr->power_on_timer_1);
        ui_scr->power_on_timer_1 = NULL;
    }
    ui_free_scr_ptr(ui, GUI_SCREEN_POWER_ON);
}

#endif

