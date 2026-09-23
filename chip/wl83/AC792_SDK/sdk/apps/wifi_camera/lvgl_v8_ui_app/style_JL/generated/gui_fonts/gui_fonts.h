#include "app_config.h"
#ifdef CONFIG_UI_STYLE_JL_ENABLE
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

extern lv_font_t lv_font_montserratMedium_12;
extern lv_font_t lv_font_FangZhengKaiTiJianTi_1_28;
extern lv_font_t lv_font_FangZhengKaiTiJianTi_1_19;
extern lv_font_t lv_font_FangZhengKaiTiJianTi_1_24;
extern lv_font_t lv_font_FangZhengKaiTiJianTi_1_32;
extern lv_font_t lv_font_FangZhengKaiTiJianTi_1_16;
extern lv_font_t lv_font_montserratMedium_18;
extern lv_font_t lv_font_montserratMedium_20;
extern lv_font_t lv_font_FangZhengKaiTiJianTi_1_54;
extern lv_font_t lv_font_FangZhengKaiTiJianTi_1_48;
extern lv_font_t lv_font_FangZhengKaiTiJianTi_1_20;
extern lv_font_t lv_font_montserratMedium_24;
extern lv_font_t lv_font_montserratMedium_48;
extern lv_font_t lv_font_montserratMedium_49;
extern lv_font_t lv_font_montserratMedium_32;
extern lv_font_t lv_font_FangZhengKaiTiJianTi_1_14;
extern lv_font_t lv_font_montserratMedium_160;
extern lv_font_t lv_font_FangZhengKaiTiJianTi_1_26;
extern lv_font_t lv_font_montserratMedium_22;
extern lv_font_t lv_font_montserratMedium_16;
extern lv_font_t lv_font_fangsong_16;
extern lv_font_t lv_font_fangsong_24;
extern lv_font_t lv_font_FangZhengKaiTiJianTi_1_22;
extern lv_font_t lv_font_timesnewromanpsmt_16;
extern lv_font_t lv_font_timesnewromanpsmt_24;
extern lv_font_t lv_font_timesnewromanpsmt_48;
extern lv_font_t lv_font_timesnewromanpsmt_22;
extern lv_font_t lv_font_segoeui_16;
extern lv_font_t lv_font_segoeui_24;
extern lv_font_t lv_font_leelawadeeui_16;
extern lv_font_t lv_font_leelawadeeui_24;
extern lv_font_t lv_font_malgungothic_16;
extern lv_font_t lv_font_malgungothic_24;
extern lv_font_t lv_font_ms_gothic_16;
extern lv_font_t lv_font_calibri_16;
extern lv_font_t lv_font_calibri_24;

void init_gui_fonts();

#ifdef __cplusplus
}
#endif
#endif
#endif
