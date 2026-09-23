#include "app_config.h"
#ifdef CONFIG_UI_STYLE_LY_ENABLE
/*Generate Code, Do NOT Edit!*/
#if LV_USE_GUIBUILDER_SIMULATOR
#include <stdio.h>
#endif
#include "../gui_guider.h"
#include "lvgl.h"
#include "./callback_handler.h"

// Generate video_rec_timer_1 CallBack Handler
void video_rec_timer_1_timer_cb(lv_timer_t *src)
{
    lv_ui_video_rec *ui_scr = ui_get_scr_ptr(&guider_ui, GUI_SCREEN_VIDEO_REC);
    lvgl_module_msg_send_global_ptr(GUI_MODEL_VIDEO_REC_MSG_ID_REC_REMAIN_TIME, NULL, 0, 0);
    printf("enter time cb send msg\n");

    if (src->repeat_count == 0) {
        ui_scr = ui_get_scr_ptr(&guider_ui, GUI_SCREEN_VIDEO_REC);
        if (ui_scr != NULL && ui_scr->video_rec_timer_1 == src) {
            ui_scr->video_rec_timer_1 = NULL;
        }
    }

}
// Generate page_map_timer_1 CallBack Handler
void page_map_timer_1_timer_cb(lv_timer_t *src)
{
    lv_ui_page_map *ui_scr = ui_get_scr_ptr(&guider_ui, GUI_SCREEN_PAGE_MAP);

#if 1
    static uint8_t bat_idx = 0;
    lv_imglist_set_act(ui_scr->page_map_imglist_bat, bat_idx);
    if (bat_idx <  99) {
        bat_idx++;
    } else {
        bat_idx = 0;
    }
#endif

    if (src->repeat_count == 0) {
        ui_scr = ui_get_scr_ptr(&guider_ui, GUI_SCREEN_PAGE_MAP);
        if (ui_scr != NULL && ui_scr->page_map_timer_1 == src) {
            ui_scr->page_map_timer_1 = NULL;
        }
    }

}
// Generate page_map_timer_2 CallBack Handler
void page_map_timer_2_timer_cb(lv_timer_t *src)
{
    lv_ui_page_map *ui_scr = ui_get_scr_ptr(&guider_ui, GUI_SCREEN_PAGE_MAP);
    if (!img_2_init_flag) {
        lv_obj_add_flag(ui_scr->page_map_img_2, LV_OBJ_FLAG_HIDDEN);
        img_2_init_flag = 1;
    }


    if (src->repeat_count == 0) {
        ui_scr = ui_get_scr_ptr(&guider_ui, GUI_SCREEN_PAGE_MAP);
        if (ui_scr != NULL && ui_scr->page_map_timer_2 == src) {
            ui_scr->page_map_timer_2 = NULL;
        }
    }

}
// Generate page_music_timer_1 CallBack Handler
void page_music_timer_1_timer_cb(lv_timer_t *src)
{
    lv_ui_page_music *ui_scr = ui_get_scr_ptr(&guider_ui, GUI_SCREEN_PAGE_MUSIC);
#if 0
    static uint32_t angle_idx = 0;
    lv_img_set_angle(ui_scr->page_music_img_1, angle_idx);
    lv_img_set_pivot(ui_scr->page_music_img_1, 139, 139);
    if (angle_idx < 3600) {
        angle_idx += 10;
    } else {
        angle_idx = 0;
    }
#endif

#if 1
    static uint8_t slider_1_idx = 0;
    lv_slider_set_value(ui_scr->page_music_slider_1, slider_1_idx, LV_ANIM_OFF);
    if (slider_1_idx <=  99) {
        slider_1_idx++;
    } else {
        slider_1_idx = 0;
    }
#endif

    if (src->repeat_count == 0) {
        ui_scr = ui_get_scr_ptr(&guider_ui, GUI_SCREEN_PAGE_MUSIC);
        if (ui_scr != NULL && ui_scr->page_music_timer_1 == src) {
            ui_scr->page_music_timer_1 = NULL;
        }
    }

}
// Generate page_meter_anim_pwr_l CallBack Handler
void page_meter_anim_pwr_l_anim_start_cb(lv_anim_t *anim)
{

}
// Generate page_meter_anim_pwr_l CallBack Handler
void page_meter_anim_pwr_l_anim_ready_cb(lv_anim_t *anim)
{

}
// Generate page_meter_anim_pwr_r CallBack Handler
void page_meter_anim_pwr_r_anim_start_cb(lv_anim_t *anim)
{

}
// Generate page_meter_anim_pwr_r CallBack Handler
void page_meter_anim_pwr_r_anim_ready_cb(lv_anim_t *anim)
{

}
// Generate page_meter_timer_1 CallBack Handler
void page_meter_timer_1_timer_cb(lv_timer_t *src)
{
    lv_ui_page_meter *ui_scr = ui_get_scr_ptr(&guider_ui, GUI_SCREEN_PAGE_METER);

    static uint8_t tens_idx = 0;
    lv_imglist_set_act(ui_scr->page_meter_imglist_speed_tens, tens_idx);
    lv_imglist_set_act(ui_scr->page_meter_imglist_speed_ones, tens_idx);

    if (tens_idx <=  9) {
        tens_idx++;
    } else {
        tens_idx = 0;
    }


    if (src->repeat_count == 0) {
        ui_scr = ui_get_scr_ptr(&guider_ui, GUI_SCREEN_PAGE_METER);
        if (ui_scr != NULL && ui_scr->page_meter_timer_1 == src) {
            ui_scr->page_meter_timer_1 = NULL;
        }
    }

}
// Generate page_meter_timer_2 CallBack Handler
void page_meter_timer_2_timer_cb(lv_timer_t *src)
{
    lv_ui_page_meter *ui_scr = ui_get_scr_ptr(&guider_ui, GUI_SCREEN_PAGE_METER);

    static uint8_t turn_img_flag = 0;

    if (turn_img_flag) {
        turn_img_flag = 0;
        lv_obj_add_flag(ui_scr->page_meter_img_left_turn, LV_OBJ_FLAG_HIDDEN);
        lv_obj_add_flag(ui_scr->page_meter_img_right_turn, LV_OBJ_FLAG_HIDDEN);
    } else {
        turn_img_flag = 1;
        lv_obj_clear_flag(ui_scr->page_meter_img_left_turn, LV_OBJ_FLAG_HIDDEN);
        lv_obj_clear_flag(ui_scr->page_meter_img_right_turn, LV_OBJ_FLAG_HIDDEN);
    }


    if (src->repeat_count == 0) {
        ui_scr = ui_get_scr_ptr(&guider_ui, GUI_SCREEN_PAGE_METER);
        if (ui_scr != NULL && ui_scr->page_meter_timer_2 == src) {
            ui_scr->page_meter_timer_2 = NULL;
        }
    }

}
// Generate page_meter_timer_3 CallBack Handler
void page_meter_timer_3_timer_cb(lv_timer_t *src)
{
    lv_ui_page_meter *ui_scr = ui_get_scr_ptr(&guider_ui, GUI_SCREEN_PAGE_METER);

    static uint8_t turn_img = 0;

    switch (turn_img) {
    case 0:
        lv_obj_clear_flag(ui_scr->page_meter_img_brake_system_fault, LV_OBJ_FLAG_HIDDEN);
        lv_obj_add_flag(ui_scr->page_meter_img_hdc, LV_OBJ_FLAG_HIDDEN);
        turn_img++;
        break;
    case 1:
        lv_obj_clear_flag(ui_scr->page_meter_img_hdc, LV_OBJ_FLAG_HIDDEN);
        lv_obj_add_flag(ui_scr->page_meter_img_position, LV_OBJ_FLAG_HIDDEN);
        turn_img++;
        break;
    case 2:
        lv_obj_clear_flag(ui_scr->page_meter_img_position, LV_OBJ_FLAG_HIDDEN);
        lv_obj_add_flag(ui_scr->page_meter_imgList_high_low_beam, LV_OBJ_FLAG_HIDDEN);
        turn_img++;
        break;
    case 3:
        lv_obj_clear_flag(ui_scr->page_meter_imgList_high_low_beam, LV_OBJ_FLAG_HIDDEN);
        lv_obj_add_flag(ui_scr->page_meter_img_auto, LV_OBJ_FLAG_HIDDEN);
        turn_img++;
        break;
    case 4:
        lv_obj_clear_flag(ui_scr->page_meter_img_auto, LV_OBJ_FLAG_HIDDEN);
        lv_obj_add_flag(ui_scr->page_meter_img_abs, LV_OBJ_FLAG_HIDDEN);
        turn_img++;
        break;
    case 5:
        lv_obj_clear_flag(ui_scr->page_meter_img_abs, LV_OBJ_FLAG_HIDDEN);
        lv_obj_add_flag(ui_scr->page_meter_img_limping, LV_OBJ_FLAG_HIDDEN);
        turn_img++;
        break;
    case 6:
        lv_obj_clear_flag(ui_scr->page_meter_img_limping, LV_OBJ_FLAG_HIDDEN);
        lv_obj_add_flag(ui_scr->page_meter_img_P_mode, LV_OBJ_FLAG_HIDDEN);
        turn_img++;
        break;
    case 7:
        lv_obj_clear_flag(ui_scr->page_meter_img_P_mode, LV_OBJ_FLAG_HIDDEN);
        lv_obj_add_flag(ui_scr->page_meter_img_force_touch, LV_OBJ_FLAG_HIDDEN);
        turn_img++;
        break;
    case 8:
        lv_obj_clear_flag(ui_scr->page_meter_img_force_touch, LV_OBJ_FLAG_HIDDEN);
        lv_obj_add_flag(ui_scr->page_meter_img_box_open, LV_OBJ_FLAG_HIDDEN);
        turn_img++;
        break;
    case 9:
        lv_obj_clear_flag(ui_scr->page_meter_img_box_open, LV_OBJ_FLAG_HIDDEN);
        lv_obj_add_flag(ui_scr->page_meter_img_side_support, LV_OBJ_FLAG_HIDDEN);
        turn_img++;
        break;
    case 10:
        lv_obj_clear_flag(ui_scr->page_meter_img_side_support, LV_OBJ_FLAG_HIDDEN);
        lv_obj_add_flag(ui_scr->page_meter_img_tcs, LV_OBJ_FLAG_HIDDEN);
        turn_img++;
        break;
    case 11:
        lv_obj_clear_flag(ui_scr->page_meter_img_tcs, LV_OBJ_FLAG_HIDDEN);
        lv_obj_add_flag(ui_scr->page_meter_img_tapLoc, LV_OBJ_FLAG_HIDDEN);
        turn_img++;
        break;
    case 12:
        lv_obj_clear_flag(ui_scr->page_meter_img_tapLoc, LV_OBJ_FLAG_HIDDEN);
        lv_obj_add_flag(ui_scr->page_meter_img_car_fault, LV_OBJ_FLAG_HIDDEN);
        turn_img++;
        break;
    case 13:
        lv_obj_clear_flag(ui_scr->page_meter_img_car_fault, LV_OBJ_FLAG_HIDDEN);
        lv_obj_add_flag(ui_scr->page_meter_img_brake_system_fault, LV_OBJ_FLAG_HIDDEN);
        turn_img = 0;
        break;
    }

    if (src->repeat_count == 0) {
        ui_scr = ui_get_scr_ptr(&guider_ui, GUI_SCREEN_PAGE_METER);
        if (ui_scr != NULL && ui_scr->page_meter_timer_3 == src) {
            ui_scr->page_meter_timer_3 = NULL;
        }
    }

}
// Generate power_on_timer_1 CallBack Handler
void power_on_timer_1_timer_cb(lv_timer_t *src)
{
    lv_ui_power_on *ui_scr = ui_get_scr_ptr(&guider_ui, GUI_SCREEN_POWER_ON);
    gui_scr_t *scr = ui_get_scr(GUI_SCREEN_PAGE_METER);
    ui_load_scr_anim(&guider_ui, scr, LV_SCR_LOAD_ANIM_NONE, 0, 0, true, true, false);

    if (src->repeat_count == 0) {
        ui_scr = ui_get_scr_ptr(&guider_ui, GUI_SCREEN_POWER_ON);
        if (ui_scr != NULL && ui_scr->power_on_timer_1 == src) {
            ui_scr->power_on_timer_1 = NULL;
        }
    }

}

#endif

