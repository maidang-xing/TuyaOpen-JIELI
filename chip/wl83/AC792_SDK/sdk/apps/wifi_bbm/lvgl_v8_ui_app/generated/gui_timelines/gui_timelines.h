/*Generate Code, Do NOT Edit!*/
#ifndef GUI_TIMELINES_H_
#define GUI_TIMELINES_H_
#ifdef __cplusplus
extern "C" {
#endif

#include "../gui_guider.h"
#include "lvgl.h"
#include "../../custom/custom.h"

#define init_gui_timelines(ui) gui_timelines_init(ui)
#define stop_gui_timelines() gui_timelines_stop()
#define delete_gui_timelines() gui_timelines_delete()
extern void gui_timelines_init(lv_ui *ui);
extern void gui_timelines_stop();
extern void gui_timelines_delete();

//One file per timeline

#ifdef __cplusplus
}
#endif
#endif /* GUI_TIMELINES_H_ */
