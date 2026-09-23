/*Generate Code, Do NOT Edit!*/
#if LV_USE_GUIBUILDER_SIMULATOR
#include <stdio.h>
#endif
#include "../gui_guider.h"
#include "lvgl.h"
#include "./callback_handler.h"

// Generate music_player_timer_1 CallBack Handler
void music_player_timer_1_timer_cb(lv_timer_t *src)
{
    lv_ui_music_player *ui_scr = ui_get_scr_ptr(&guider_ui, GUI_SCREEN_MUSIC_PLAYER);
#if 0
    static uint32_t angle_idx = 0;
    lv_img_set_angle(ui_scr->music_player_img_3, angle_idx);
    lv_img_set_pivot(ui_scr->music_player_img_3, 139, 139);
    if (angle_idx < 3600) {
        angle_idx += 10;
    } else {
        angle_idx = 0;
    }
#endif

    if (src->repeat_count == 0) {
        ui_scr = ui_get_scr_ptr(&guider_ui, GUI_SCREEN_MUSIC_PLAYER);
        if (ui_scr != NULL && ui_scr->music_player_timer_1 == src) {
            ui_scr->music_player_timer_1 = NULL;
        }
    }

}
