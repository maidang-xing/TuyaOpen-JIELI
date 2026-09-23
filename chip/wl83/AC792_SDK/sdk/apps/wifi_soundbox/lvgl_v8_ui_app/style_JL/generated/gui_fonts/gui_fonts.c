#include "lvgl.h"
#if LV_USE_GUIBUILDER_SIMULATOR
#include <stdio.h>
#endif
#include "./gui_fonts.h"
#include "../common.h"

lv_font_t lv_font_FangZhengKaiTiJianTi_1_12;
lv_font_t *lv_font_FangZhengKaiTiJianTi_1_12_ptr;
void lv_font_FangZhengKaiTiJianTi_1_12_file()
{
    if (lv_font_FangZhengKaiTiJianTi_1_12_ptr != NULL) {
        lv_font_free_bin(lv_font_FangZhengKaiTiJianTi_1_12_ptr);
        lv_font_FangZhengKaiTiJianTi_1_12_ptr = NULL;
        memset(&lv_font_FangZhengKaiTiJianTi_1_12, 0, sizeof(lv_font_t));
    }
#if LV_USE_GUIBUILDER_SIMULATOR
    lv_font_FangZhengKaiTiJianTi_1_12_ptr = lv_font_load_bin("A:\\wl83\\ac792\\ui_prj\\wifi_soundbox_800x480\\sdk\\ui_res\\flash\\rle\\font\\35000000.rle");
#else
    lv_font_FangZhengKaiTiJianTi_1_12_ptr = lv_font_load_bin(gui_get_res_path(GUI_RES_FANGZHENGKAITIJIANTI_1_12_TTF_FLASH));
#endif
    if (lv_font_FangZhengKaiTiJianTi_1_12_ptr != NULL) {
        lv_font_FangZhengKaiTiJianTi_1_12 = *lv_font_FangZhengKaiTiJianTi_1_12_ptr;
    } else {
#if LV_USE_GUIBUILDER_SIMULATOR
        LV_LOG_ERROR("Load Fnt Font Failed %s\n", "A:\\wl83\\ac792\\ui_prj\\wifi_soundbox_800x480\\sdk\\ui_res\\flash\\rle\\font\\35000000.rle");
#else
        LV_LOG_ERROR("Load Fnt Font Failed %s\n", gui_get_res_path(GUI_RES_FANGZHENGKAITIJIANTI_1_12_TTF_FLASH));
#endif
        lv_font_FangZhengKaiTiJianTi_1_12 = *LV_FONT_DEFAULT;
    }
}
lv_font_t lv_font_FangZhengKaiTiJianTi_1_24;
lv_font_t *lv_font_FangZhengKaiTiJianTi_1_24_ptr;
void lv_font_FangZhengKaiTiJianTi_1_24_file()
{
    if (lv_font_FangZhengKaiTiJianTi_1_24_ptr != NULL) {
        lv_font_free_bin(lv_font_FangZhengKaiTiJianTi_1_24_ptr);
        lv_font_FangZhengKaiTiJianTi_1_24_ptr = NULL;
        memset(&lv_font_FangZhengKaiTiJianTi_1_24, 0, sizeof(lv_font_t));
    }
#if LV_USE_GUIBUILDER_SIMULATOR
    lv_font_FangZhengKaiTiJianTi_1_24_ptr = lv_font_load_bin("A:\\wl83\\ac792\\ui_prj\\wifi_soundbox_800x480\\sdk\\ui_res\\flash\\rle\\font\\35000001.rle");
#else
    lv_font_FangZhengKaiTiJianTi_1_24_ptr = lv_font_load_bin(gui_get_res_path(GUI_RES_FANGZHENGKAITIJIANTI_1_24_TTF_FLASH));
#endif
    if (lv_font_FangZhengKaiTiJianTi_1_24_ptr != NULL) {
        lv_font_FangZhengKaiTiJianTi_1_24 = *lv_font_FangZhengKaiTiJianTi_1_24_ptr;
    } else {
#if LV_USE_GUIBUILDER_SIMULATOR
        LV_LOG_ERROR("Load Fnt Font Failed %s\n", "A:\\wl83\\ac792\\ui_prj\\wifi_soundbox_800x480\\sdk\\ui_res\\flash\\rle\\font\\35000001.rle");
#else
        LV_LOG_ERROR("Load Fnt Font Failed %s\n", gui_get_res_path(GUI_RES_FANGZHENGKAITIJIANTI_1_24_TTF_FLASH));
#endif
        lv_font_FangZhengKaiTiJianTi_1_24 = *LV_FONT_DEFAULT;
    }
}
lv_font_t lv_font_FangZhengKaiTiJianTi_1_32;
lv_font_t *lv_font_FangZhengKaiTiJianTi_1_32_ptr;
void lv_font_FangZhengKaiTiJianTi_1_32_file()
{
    if (lv_font_FangZhengKaiTiJianTi_1_32_ptr != NULL) {
        lv_font_free_bin(lv_font_FangZhengKaiTiJianTi_1_32_ptr);
        lv_font_FangZhengKaiTiJianTi_1_32_ptr = NULL;
        memset(&lv_font_FangZhengKaiTiJianTi_1_32, 0, sizeof(lv_font_t));
    }
#if LV_USE_GUIBUILDER_SIMULATOR
    lv_font_FangZhengKaiTiJianTi_1_32_ptr = lv_font_load_bin("A:\\wl83\\ac792\\ui_prj\\wifi_soundbox_800x480\\sdk\\ui_res\\flash\\rle\\font\\35000002.rle");
#else
    lv_font_FangZhengKaiTiJianTi_1_32_ptr = lv_font_load_bin(gui_get_res_path(GUI_RES_FANGZHENGKAITIJIANTI_1_32_TTF_FLASH));
#endif
    if (lv_font_FangZhengKaiTiJianTi_1_32_ptr != NULL) {
        lv_font_FangZhengKaiTiJianTi_1_32 = *lv_font_FangZhengKaiTiJianTi_1_32_ptr;
    } else {
#if LV_USE_GUIBUILDER_SIMULATOR
        LV_LOG_ERROR("Load Fnt Font Failed %s\n", "A:\\wl83\\ac792\\ui_prj\\wifi_soundbox_800x480\\sdk\\ui_res\\flash\\rle\\font\\35000002.rle");
#else
        LV_LOG_ERROR("Load Fnt Font Failed %s\n", gui_get_res_path(GUI_RES_FANGZHENGKAITIJIANTI_1_32_TTF_FLASH));
#endif
        lv_font_FangZhengKaiTiJianTi_1_32 = *LV_FONT_DEFAULT;
    }
}

void init_gui_fonts()
{
    lv_font_FangZhengKaiTiJianTi_1_12_file();
    lv_font_FangZhengKaiTiJianTi_1_24_file();
    lv_font_FangZhengKaiTiJianTi_1_32_file();


}

void free_gui_fonts()
{
    if (lv_font_FangZhengKaiTiJianTi_1_12_ptr != NULL) {
        lv_font_free_bin(lv_font_FangZhengKaiTiJianTi_1_12_ptr);
        lv_font_FangZhengKaiTiJianTi_1_12_ptr = NULL;
        memset(&lv_font_FangZhengKaiTiJianTi_1_12, 0, sizeof(lv_font_t));
    }
    if (lv_font_FangZhengKaiTiJianTi_1_24_ptr != NULL) {
        lv_font_free_bin(lv_font_FangZhengKaiTiJianTi_1_24_ptr);
        lv_font_FangZhengKaiTiJianTi_1_24_ptr = NULL;
        memset(&lv_font_FangZhengKaiTiJianTi_1_24, 0, sizeof(lv_font_t));
    }
    if (lv_font_FangZhengKaiTiJianTi_1_32_ptr != NULL) {
        lv_font_free_bin(lv_font_FangZhengKaiTiJianTi_1_32_ptr);
        lv_font_FangZhengKaiTiJianTi_1_32_ptr = NULL;
        memset(&lv_font_FangZhengKaiTiJianTi_1_32, 0, sizeof(lv_font_t));
    }
}


