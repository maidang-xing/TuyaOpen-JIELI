#include "app_config.h"
#ifdef CONFIG_UI_STYLE_JL_ENABLE
/*Generate Code, Do NOT Edit!*/
#ifndef EVENTS_INIT_H_
#define EVENTS_INIT_H_
#ifdef __cplusplus
extern "C" {
#endif
#include "../gui_guider.h"
#include "./screen_handler.h"
#include "./i18n_handler.h"

void events_init(lv_ui *ui);
void events_init_usb_slave(lv_ui *ui);
void events_init_video_rec(lv_ui *ui);
void events_init_home_page(lv_ui *ui);
void events_init_sys_prompt(lv_ui *ui);
void events_init_sys_setting(lv_ui *ui);
void events_init_video_photo(lv_ui *ui);
void events_init_video_play(lv_ui *ui);
void events_init_video_file(lv_ui *ui);
void events_init_video_dir(lv_ui *ui);
void events_init_car_parking(lv_ui *ui);
void events_init_line_drift(lv_ui *ui);
void events_init_sys_popwin(lv_ui *ui);

#ifdef __cplusplus
}
#endif
#endif /* EVENTS_INIT_H_ */

#endif
