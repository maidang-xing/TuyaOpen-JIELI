#ifndef GUIDER_FONTS_H
#define GUIDER_FONTS_H
#ifdef __cplusplus
extern "C" {
#endif

#if LVGL_VERSION_MAJOR == 7
#include "lv_font/lv_font.h"
#else
#include "src/font/lv_font.h"
#endif

extern lv_font_t lv_font_FangZhengKaiTiJianTi_1_12;
extern lv_font_t lv_font_FangZhengKaiTiJianTi_1_24;
extern lv_font_t lv_font_FangZhengKaiTiJianTi_1_32;

void init_gui_fonts();
void free_gui_fonts();

#ifdef __cplusplus
}
#endif
#endif