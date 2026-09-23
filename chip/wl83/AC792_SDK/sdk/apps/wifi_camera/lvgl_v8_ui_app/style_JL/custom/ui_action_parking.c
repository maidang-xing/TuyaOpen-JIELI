#include "app_config.h"
#ifdef CONFIG_UI_STYLE_JL_ENABLE
/*********************
 *      INCLUDES
 *********************/
#if !LV_USE_GUIBUILDER_SIMULATOR

#include "lvgl.h"
#include "ui.h"
#include "custom.h"
#include "app_config.h"
#include "sys_time.h"
#include "system/includes.h"
#include "asm/includes.h"
#include "syscfg/syscfg_id.h"
#include "action.h"
/*********************
 *      DEFINES
 *********************/


/*
* 显示倒车页面
*
*/
void parking_page_show(int arg)
{
    lv_ui_video_file *video_file_scr = ui_get_scr_ptr(&guider_ui, GUI_SCREEN_VIDEO_FILE);
    if (!video_file_scr) {
        return;
    }
    printf("[chili]: %s %d\n", __func__, __LINE__);
    if (video_file_scr->video_file_del == false) {
        //此时为九宫格页面，倒车会有死机，所以先unload
        printf("[chili]: %s %d\n", __func__, __LINE__);
        video_file_screen_unload();
    }
    lv_ui_video_rec *video_rec_scr = ui_get_scr_ptr(&guider_ui, GUI_SCREEN_VIDEO_REC);
    if (!video_rec_scr) {
        /*return;*/
        /*}*/
        /*if (video_rec_scr->video_rec_del != false) {*/
        gui_scr_t *screen = gui_scr_get(GUI_SCREEN_VIDEO_REC);
        if (screen == NULL) {
            screen = gui_scr_create(GUI_SCREEN_VIDEO_REC, "video_rec", guider_ui.video_rec, (gui_scr_setup_cb_t)setup_scr_video_rec, (gui_scr_unload_cb_t)unload_scr_video_rec);
        }
        ui_load_scr_anim(&guider_ui, screen, LV_SCR_LOAD_ANIM_NONE, 0, 0, true, true, false);
    }
    video_rec_scr = ui_get_scr_ptr(&guider_ui, GUI_SCREEN_VIDEO_REC);
    if (!video_rec_scr) {
        return;
    }
    if (video_rec_scr->video_rec_del == false && lv_obj_is_valid(video_rec_scr->video_rec)) {
        lv_obj_add_flag(video_rec_scr->video_rec, LV_OBJ_FLAG_HIDDEN);
    }
    lv_ui_car_parking *car_parking_scr = ui_get_scr_ptr(&guider_ui, GUI_SCREEN_CAR_PARKING);
    if (!car_parking_scr) {
        return;
    }
    if (car_parking_scr->car_parking_del == false && lv_obj_is_valid(car_parking_scr->car_parking)) {
        //  lv_obj_clear_flag(ui_scr->car_parking, LV_OBJ_FLAG_HIDDEN);
    } else {
        setup_scr_car_parking(&guider_ui);
        lv_obj_clear_flag(car_parking_scr->car_parking, LV_OBJ_FLAG_HIDDEN);
        //顶层页面没有screen_load_start等事件，所以把页面色彩和透明度转换在这里做修改
#if LV_DISP_UI_FB_NUM
        lv_obj_set_style_bg_opa(car_parking_scr->car_parking, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
#else
        lv_obj_set_style_bg_opa(car_parking_scr->car_parking, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
#endif
        delete_gui_timelines();
    }

}

/*
*
* 隐藏倒车页面--出栈显示上一界面
*
*/
void parking_page_hide(int arg)
{
    lv_ui_car_parking *car_parking_scr = ui_get_scr_ptr(&guider_ui, GUI_SCREEN_CAR_PARKING);
    if (!car_parking_scr) {
        return;
    }
    printf("[chili]: %s %d\n", __func__, __LINE__);
    if (car_parking_scr->car_parking_del == false && lv_obj_is_valid(car_parking_scr->car_parking)) {
        lv_obj_add_flag(car_parking_scr->car_parking, LV_OBJ_FLAG_HIDDEN);
        unload_scr_car_parking(&guider_ui);
        lv_obj_clean(car_parking_scr->car_parking);

    }
    lv_ui_video_rec *video_rec_scr = ui_get_scr_ptr(&guider_ui, GUI_SCREEN_VIDEO_REC);
    if (!video_rec_scr) {
        return;
    }
    if (video_rec_scr->video_rec_del == false && lv_obj_is_valid(video_rec_scr->video_rec)) {
        lv_obj_clear_flag(video_rec_scr->video_rec, LV_OBJ_FLAG_HIDDEN);
    }
}

#endif



#endif
