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


lv_obj_t *setup_scr_car_parking(lv_ui *ui)
{
    lv_ui_car_parking *ui_scr = ui_get_scr_ptr(ui, GUI_SCREEN_CAR_PARKING);
    if (ui_scr == NULL) {
        ui_scr = lv_mem_alloc(sizeof(lv_ui_car_parking));
        if (ui_scr == NULL) {
            return NULL;
        }
        memset(ui_scr, 0, sizeof(lv_ui_car_parking));
        ui->car_parking = ui_scr;
    }

    //Write codes car_parking
    ui_scr->car_parking = lv_obj_create(NULL);
    lv_obj_set_scrollbar_mode(ui_scr->car_parking, LV_SCROLLBAR_MODE_OFF);
    ui_style_set(ui_scr->car_parking, GUI_CTRL_SCR);

    //Set style for car_parking. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
    lv_obj_set_style_bg_color(ui_scr->car_parking, lv_color_make(0x55, 0xaa, 0xa5), LV_PART_MAIN | LV_STATE_DEFAULT);

    //Write codes car_parking_img_1
    ui_scr->car_parking_img_1 = lv_img_create(ui_scr->car_parking);
    lv_img_set_src(ui_scr->car_parking_img_1, gui_get_res_path(GUI_RES_ASTERN_PNG));
    lv_img_set_pivot(ui_scr->car_parking_img_1, 0, 0);
    lv_img_set_angle(ui_scr->car_parking_img_1, 0);
    lv_img_set_zoom(ui_scr->car_parking_img_1, 256);
    lv_obj_set_pos(ui_scr->car_parking_img_1, 109, 309);
    lv_obj_set_size(ui_scr->car_parking_img_1, 550, 167);
    lv_obj_add_flag(ui_scr->car_parking_img_1, LV_OBJ_FLAG_CLICKABLE);
    ui_style_set(ui_scr->car_parking_img_1, GUI_CTRL_IMG);

    lv_obj_update_layout(ui_scr->car_parking);
    ui_scr->car_parking_del = false;
    i18n_refresh_texts(GUI_SCREEN_CAR_PARKING);

    //Init events for screen
    events_init_car_parking(ui);
    return ui_scr->car_parking;
}
void unload_scr_car_parking(lv_ui *ui)
{
    ui_free_scr_ptr(ui, GUI_SCREEN_CAR_PARKING);
}

#endif
