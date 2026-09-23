#include "app_config.h"
#ifdef CONFIG_UI_STYLE_LY_ENABLE
/*Generate Code, Do NOT Edit!*/
#ifndef CALLBACK_HANDLER_H_
#define CALLBACK_HANDLER_H_
#ifdef __cplusplus
extern "C" {
#endif
#include "../gui_guider.h"
#include "lvgl.h"
#include "../../custom/custom.h"

// Generate video_rec_timer_1 CallBack Handler
extern void video_rec_timer_1_timer_cb(lv_timer_t *src);

// Generate page_map_timer_1 CallBack Handler
extern void page_map_timer_1_timer_cb(lv_timer_t *src);

// Generate page_map_timer_2 CallBack Handler
static int img_2_init_flag  = 0;
extern void page_map_timer_2_timer_cb(lv_timer_t *src);

// Generate page_music_timer_1 CallBack Handler
extern void page_music_timer_1_timer_cb(lv_timer_t *src);

// Generate page_meter_anim_pwr_l CallBack Handler
extern void page_meter_anim_pwr_l_anim_start_cb(lv_anim_t *anim);

// Generate page_meter_anim_pwr_l CallBack Handler
extern void page_meter_anim_pwr_l_anim_ready_cb(lv_anim_t *anim);

// Generate page_meter_anim_pwr_r CallBack Handler
extern void page_meter_anim_pwr_r_anim_start_cb(lv_anim_t *anim);

// Generate page_meter_anim_pwr_r CallBack Handler
extern void page_meter_anim_pwr_r_anim_ready_cb(lv_anim_t *anim);

// Generate page_meter_timer_1 CallBack Handler
extern void page_meter_timer_1_timer_cb(lv_timer_t *src);

// Generate page_meter_timer_2 CallBack Handler
extern void page_meter_timer_2_timer_cb(lv_timer_t *src);

// Generate page_meter_timer_3 CallBack Handler
extern void page_meter_timer_3_timer_cb(lv_timer_t *src);

// Generate power_on_timer_1 CallBack Handler
extern void power_on_timer_1_timer_cb(lv_timer_t *src);

#ifdef __cplusplus
}
#endif
#endif /* CALLBACK_HANDLER_H_ */

#endif

