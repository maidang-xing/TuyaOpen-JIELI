#include "app_config.h"
#ifdef CONFIG_UI_STYLE_LY_ENABLE
#include "lvgl.h"
#if LV_USE_GUIBUILDER_SIMULATOR
#include <stdio.h>
#endif
#include "./gui_fonts.h"
#include "../common.h"

lv_font_t lv_font_FangZhengKaiTiJianTi_1_22;
lv_font_t *lv_font_FangZhengKaiTiJianTi_1_22_ptr;
void lv_font_FangZhengKaiTiJianTi_1_22_file()
{
    if (lv_font_FangZhengKaiTiJianTi_1_22_ptr != NULL) {
        lv_font_free_bin(lv_font_FangZhengKaiTiJianTi_1_22_ptr);
        lv_font_FangZhengKaiTiJianTi_1_22_ptr = NULL;
        memset(&lv_font_FangZhengKaiTiJianTi_1_22, 0, sizeof(lv_font_t));
    }
#if LV_USE_GUIBUILDER_SIMULATOR
    lv_font_FangZhengKaiTiJianTi_1_22_ptr = lv_font_load_bin("A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\sdk\\ui_res\\flash\\rle\\font\\35000000.rle");
#else
    lv_font_FangZhengKaiTiJianTi_1_22_ptr = lv_font_load_bin(gui_get_res_path(GUI_RES_FANGZHENGKAITIJIANTI_1_22_TTF_FLASH));
#endif
    if (lv_font_FangZhengKaiTiJianTi_1_22_ptr != NULL) {
        lv_font_FangZhengKaiTiJianTi_1_22 = *lv_font_FangZhengKaiTiJianTi_1_22_ptr;
    } else {
#if LV_USE_GUIBUILDER_SIMULATOR
        LV_LOG_ERROR("Load Fnt Font Failed %s\n", "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\sdk\\ui_res\\flash\\rle\\font\\35000000.rle");
#else
        LV_LOG_ERROR("Load Fnt Font Failed %s\n", gui_get_res_path(GUI_RES_FANGZHENGKAITIJIANTI_1_22_TTF_FLASH));
#endif
        lv_font_FangZhengKaiTiJianTi_1_22 = *LV_FONT_DEFAULT;
    }
}
lv_font_t lv_font_FangZhengKaiTiJianTi_1_26;
lv_font_t *lv_font_FangZhengKaiTiJianTi_1_26_ptr;
void lv_font_FangZhengKaiTiJianTi_1_26_file()
{
    if (lv_font_FangZhengKaiTiJianTi_1_26_ptr != NULL) {
        lv_font_free_bin(lv_font_FangZhengKaiTiJianTi_1_26_ptr);
        lv_font_FangZhengKaiTiJianTi_1_26_ptr = NULL;
        memset(&lv_font_FangZhengKaiTiJianTi_1_26, 0, sizeof(lv_font_t));
    }
#if LV_USE_GUIBUILDER_SIMULATOR
    lv_font_FangZhengKaiTiJianTi_1_26_ptr = lv_font_load_bin("A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\sdk\\ui_res\\flash\\rle\\font\\35000001.rle");
#else
    lv_font_FangZhengKaiTiJianTi_1_26_ptr = lv_font_load_bin(gui_get_res_path(GUI_RES_FANGZHENGKAITIJIANTI_1_26_TTF_FLASH));
#endif
    if (lv_font_FangZhengKaiTiJianTi_1_26_ptr != NULL) {
        lv_font_FangZhengKaiTiJianTi_1_26 = *lv_font_FangZhengKaiTiJianTi_1_26_ptr;
    } else {
#if LV_USE_GUIBUILDER_SIMULATOR
        LV_LOG_ERROR("Load Fnt Font Failed %s\n", "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\sdk\\ui_res\\flash\\rle\\font\\35000001.rle");
#else
        LV_LOG_ERROR("Load Fnt Font Failed %s\n", gui_get_res_path(GUI_RES_FANGZHENGKAITIJIANTI_1_26_TTF_FLASH));
#endif
        lv_font_FangZhengKaiTiJianTi_1_26 = *LV_FONT_DEFAULT;
    }
}
lv_font_t lv_font_FangZhengKaiTiJianTi_1_18;
lv_font_t *lv_font_FangZhengKaiTiJianTi_1_18_ptr;
void lv_font_FangZhengKaiTiJianTi_1_18_file()
{
    if (lv_font_FangZhengKaiTiJianTi_1_18_ptr != NULL) {
        lv_font_free_bin(lv_font_FangZhengKaiTiJianTi_1_18_ptr);
        lv_font_FangZhengKaiTiJianTi_1_18_ptr = NULL;
        memset(&lv_font_FangZhengKaiTiJianTi_1_18, 0, sizeof(lv_font_t));
    }
#if LV_USE_GUIBUILDER_SIMULATOR
    lv_font_FangZhengKaiTiJianTi_1_18_ptr = lv_font_load_bin("A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\sdk\\ui_res\\flash\\rle\\font\\35000002.rle");
#else
    lv_font_FangZhengKaiTiJianTi_1_18_ptr = lv_font_load_bin(gui_get_res_path(GUI_RES_FANGZHENGKAITIJIANTI_1_18_TTF_FLASH));
#endif
    if (lv_font_FangZhengKaiTiJianTi_1_18_ptr != NULL) {
        lv_font_FangZhengKaiTiJianTi_1_18 = *lv_font_FangZhengKaiTiJianTi_1_18_ptr;
    } else {
#if LV_USE_GUIBUILDER_SIMULATOR
        LV_LOG_ERROR("Load Fnt Font Failed %s\n", "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\sdk\\ui_res\\flash\\rle\\font\\35000002.rle");
#else
        LV_LOG_ERROR("Load Fnt Font Failed %s\n", gui_get_res_path(GUI_RES_FANGZHENGKAITIJIANTI_1_18_TTF_FLASH));
#endif
        lv_font_FangZhengKaiTiJianTi_1_18 = *LV_FONT_DEFAULT;
    }
}
lv_font_t lv_font_montserratMedium_18;
lv_font_t *lv_font_montserratMedium_18_ptr;
void lv_font_montserratMedium_18_file()
{
    if (lv_font_montserratMedium_18_ptr != NULL) {
        lv_font_free_bin(lv_font_montserratMedium_18_ptr);
        lv_font_montserratMedium_18_ptr = NULL;
        memset(&lv_font_montserratMedium_18, 0, sizeof(lv_font_t));
    }
#if LV_USE_GUIBUILDER_SIMULATOR
    lv_font_montserratMedium_18_ptr = lv_font_load_bin("A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\sdk\\ui_res\\flash\\rle\\font\\35000003.rle");
#else
    lv_font_montserratMedium_18_ptr = lv_font_load_bin(gui_get_res_path(GUI_RES_MONTSERRATMEDIUM_18_TTF_FLASH));
#endif
    if (lv_font_montserratMedium_18_ptr != NULL) {
        lv_font_montserratMedium_18 = *lv_font_montserratMedium_18_ptr;
    } else {
#if LV_USE_GUIBUILDER_SIMULATOR
        LV_LOG_ERROR("Load Fnt Font Failed %s\n", "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\sdk\\ui_res\\flash\\rle\\font\\35000003.rle");
#else
        LV_LOG_ERROR("Load Fnt Font Failed %s\n", gui_get_res_path(GUI_RES_MONTSERRATMEDIUM_18_TTF_FLASH));
#endif
        lv_font_montserratMedium_18 = *LV_FONT_DEFAULT;
    }
}
lv_font_t lv_font_FangZhengKaiTiJianTi_1_48;
lv_font_t *lv_font_FangZhengKaiTiJianTi_1_48_ptr;
void lv_font_FangZhengKaiTiJianTi_1_48_file()
{
    if (lv_font_FangZhengKaiTiJianTi_1_48_ptr != NULL) {
        lv_font_free_bin(lv_font_FangZhengKaiTiJianTi_1_48_ptr);
        lv_font_FangZhengKaiTiJianTi_1_48_ptr = NULL;
        memset(&lv_font_FangZhengKaiTiJianTi_1_48, 0, sizeof(lv_font_t));
    }
#if LV_USE_GUIBUILDER_SIMULATOR
    lv_font_FangZhengKaiTiJianTi_1_48_ptr = lv_font_load_bin("A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\sdk\\ui_res\\flash\\rle\\font\\35000004.rle");
#else
    lv_font_FangZhengKaiTiJianTi_1_48_ptr = lv_font_load_bin(gui_get_res_path(GUI_RES_FANGZHENGKAITIJIANTI_1_48_TTF_FLASH));
#endif
    if (lv_font_FangZhengKaiTiJianTi_1_48_ptr != NULL) {
        lv_font_FangZhengKaiTiJianTi_1_48 = *lv_font_FangZhengKaiTiJianTi_1_48_ptr;
    } else {
#if LV_USE_GUIBUILDER_SIMULATOR
        LV_LOG_ERROR("Load Fnt Font Failed %s\n", "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\sdk\\ui_res\\flash\\rle\\font\\35000004.rle");
#else
        LV_LOG_ERROR("Load Fnt Font Failed %s\n", gui_get_res_path(GUI_RES_FANGZHENGKAITIJIANTI_1_48_TTF_FLASH));
#endif
        lv_font_FangZhengKaiTiJianTi_1_48 = *LV_FONT_DEFAULT;
    }
}
lv_font_t lv_font_montserratMedium_24;
lv_font_t *lv_font_montserratMedium_24_ptr;
void lv_font_montserratMedium_24_file()
{
    if (lv_font_montserratMedium_24_ptr != NULL) {
        lv_font_free_bin(lv_font_montserratMedium_24_ptr);
        lv_font_montserratMedium_24_ptr = NULL;
        memset(&lv_font_montserratMedium_24, 0, sizeof(lv_font_t));
    }
#if LV_USE_GUIBUILDER_SIMULATOR
    lv_font_montserratMedium_24_ptr = lv_font_load_bin("A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\sdk\\ui_res\\flash\\rle\\font\\35000005.rle");
#else
    lv_font_montserratMedium_24_ptr = lv_font_load_bin(gui_get_res_path(GUI_RES_MONTSERRATMEDIUM_24_TTF_FLASH));
#endif
    if (lv_font_montserratMedium_24_ptr != NULL) {
        lv_font_montserratMedium_24 = *lv_font_montserratMedium_24_ptr;
    } else {
#if LV_USE_GUIBUILDER_SIMULATOR
        LV_LOG_ERROR("Load Fnt Font Failed %s\n", "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\sdk\\ui_res\\flash\\rle\\font\\35000005.rle");
#else
        LV_LOG_ERROR("Load Fnt Font Failed %s\n", gui_get_res_path(GUI_RES_MONTSERRATMEDIUM_24_TTF_FLASH));
#endif
        lv_font_montserratMedium_24 = *LV_FONT_DEFAULT;
    }
}
lv_font_t lv_font_montserratMedium_12;
lv_font_t *lv_font_montserratMedium_12_ptr;
void lv_font_montserratMedium_12_file()
{
    if (lv_font_montserratMedium_12_ptr != NULL) {
        lv_font_free_bin(lv_font_montserratMedium_12_ptr);
        lv_font_montserratMedium_12_ptr = NULL;
        memset(&lv_font_montserratMedium_12, 0, sizeof(lv_font_t));
    }
#if LV_USE_GUIBUILDER_SIMULATOR
    lv_font_montserratMedium_12_ptr = lv_font_load_bin("A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\sdk\\ui_res\\flash\\rle\\font\\35000006.rle");
#else
    lv_font_montserratMedium_12_ptr = lv_font_load_bin(gui_get_res_path(GUI_RES_MONTSERRATMEDIUM_12_TTF_FLASH));
#endif
    if (lv_font_montserratMedium_12_ptr != NULL) {
        lv_font_montserratMedium_12 = *lv_font_montserratMedium_12_ptr;
    } else {
#if LV_USE_GUIBUILDER_SIMULATOR
        LV_LOG_ERROR("Load Fnt Font Failed %s\n", "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\sdk\\ui_res\\flash\\rle\\font\\35000006.rle");
#else
        LV_LOG_ERROR("Load Fnt Font Failed %s\n", gui_get_res_path(GUI_RES_MONTSERRATMEDIUM_12_TTF_FLASH));
#endif
        lv_font_montserratMedium_12 = *LV_FONT_DEFAULT;
    }
}
lv_font_t lv_font_montserratMedium_22;
lv_font_t *lv_font_montserratMedium_22_ptr;
void lv_font_montserratMedium_22_file()
{
    if (lv_font_montserratMedium_22_ptr != NULL) {
        lv_font_free_bin(lv_font_montserratMedium_22_ptr);
        lv_font_montserratMedium_22_ptr = NULL;
        memset(&lv_font_montserratMedium_22, 0, sizeof(lv_font_t));
    }
#if LV_USE_GUIBUILDER_SIMULATOR
    lv_font_montserratMedium_22_ptr = lv_font_load_bin("A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\sdk\\ui_res\\flash\\rle\\font\\35000007.rle");
#else
    lv_font_montserratMedium_22_ptr = lv_font_load_bin(gui_get_res_path(GUI_RES_MONTSERRATMEDIUM_22_TTF_FLASH));
#endif
    if (lv_font_montserratMedium_22_ptr != NULL) {
        lv_font_montserratMedium_22 = *lv_font_montserratMedium_22_ptr;
    } else {
#if LV_USE_GUIBUILDER_SIMULATOR
        LV_LOG_ERROR("Load Fnt Font Failed %s\n", "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\sdk\\ui_res\\flash\\rle\\font\\35000007.rle");
#else
        LV_LOG_ERROR("Load Fnt Font Failed %s\n", gui_get_res_path(GUI_RES_MONTSERRATMEDIUM_22_TTF_FLASH));
#endif
        lv_font_montserratMedium_22 = *LV_FONT_DEFAULT;
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
    lv_font_FangZhengKaiTiJianTi_1_24_ptr = lv_font_load_bin("A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\sdk\\ui_res\\flash\\rle\\font\\35000008.rle");
#else
    lv_font_FangZhengKaiTiJianTi_1_24_ptr = lv_font_load_bin(gui_get_res_path(GUI_RES_FANGZHENGKAITIJIANTI_1_24_TTF_FLASH));
#endif
    if (lv_font_FangZhengKaiTiJianTi_1_24_ptr != NULL) {
        lv_font_FangZhengKaiTiJianTi_1_24 = *lv_font_FangZhengKaiTiJianTi_1_24_ptr;
    } else {
#if LV_USE_GUIBUILDER_SIMULATOR
        LV_LOG_ERROR("Load Fnt Font Failed %s\n", "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\sdk\\ui_res\\flash\\rle\\font\\35000008.rle");
#else
        LV_LOG_ERROR("Load Fnt Font Failed %s\n", gui_get_res_path(GUI_RES_FANGZHENGKAITIJIANTI_1_24_TTF_FLASH));
#endif
        lv_font_FangZhengKaiTiJianTi_1_24 = *LV_FONT_DEFAULT;
    }
}
lv_font_t lv_font_FangZhengKaiTiJianTi_1_16;
lv_font_t *lv_font_FangZhengKaiTiJianTi_1_16_ptr;
void lv_font_FangZhengKaiTiJianTi_1_16_file()
{
    if (lv_font_FangZhengKaiTiJianTi_1_16_ptr != NULL) {
        lv_font_free_bin(lv_font_FangZhengKaiTiJianTi_1_16_ptr);
        lv_font_FangZhengKaiTiJianTi_1_16_ptr = NULL;
        memset(&lv_font_FangZhengKaiTiJianTi_1_16, 0, sizeof(lv_font_t));
    }
#if LV_USE_GUIBUILDER_SIMULATOR
    lv_font_FangZhengKaiTiJianTi_1_16_ptr = lv_font_load_bin("A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\sdk\\ui_res\\flash\\rle\\font\\35000009.rle");
#else
    lv_font_FangZhengKaiTiJianTi_1_16_ptr = lv_font_load_bin(gui_get_res_path(GUI_RES_FANGZHENGKAITIJIANTI_1_16_TTF_FLASH));
#endif
    if (lv_font_FangZhengKaiTiJianTi_1_16_ptr != NULL) {
        lv_font_FangZhengKaiTiJianTi_1_16 = *lv_font_FangZhengKaiTiJianTi_1_16_ptr;
    } else {
#if LV_USE_GUIBUILDER_SIMULATOR
        LV_LOG_ERROR("Load Fnt Font Failed %s\n", "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\sdk\\ui_res\\flash\\rle\\font\\35000009.rle");
#else
        LV_LOG_ERROR("Load Fnt Font Failed %s\n", gui_get_res_path(GUI_RES_FANGZHENGKAITIJIANTI_1_16_TTF_FLASH));
#endif
        lv_font_FangZhengKaiTiJianTi_1_16 = *LV_FONT_DEFAULT;
    }
}
lv_font_t lv_font_montserratMedium_16;
lv_font_t *lv_font_montserratMedium_16_ptr;
void lv_font_montserratMedium_16_file()
{
    if (lv_font_montserratMedium_16_ptr != NULL) {
        lv_font_free_bin(lv_font_montserratMedium_16_ptr);
        lv_font_montserratMedium_16_ptr = NULL;
        memset(&lv_font_montserratMedium_16, 0, sizeof(lv_font_t));
    }
#if LV_USE_GUIBUILDER_SIMULATOR
    lv_font_montserratMedium_16_ptr = lv_font_load_bin("A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\sdk\\ui_res\\flash\\rle\\font\\3500000a.rle");
#else
    lv_font_montserratMedium_16_ptr = lv_font_load_bin(gui_get_res_path(GUI_RES_MONTSERRATMEDIUM_16_TTF_FLASH));
#endif
    if (lv_font_montserratMedium_16_ptr != NULL) {
        lv_font_montserratMedium_16 = *lv_font_montserratMedium_16_ptr;
    } else {
#if LV_USE_GUIBUILDER_SIMULATOR
        LV_LOG_ERROR("Load Fnt Font Failed %s\n", "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\sdk\\ui_res\\flash\\rle\\font\\3500000a.rle");
#else
        LV_LOG_ERROR("Load Fnt Font Failed %s\n", gui_get_res_path(GUI_RES_MONTSERRATMEDIUM_16_TTF_FLASH));
#endif
        lv_font_montserratMedium_16 = *LV_FONT_DEFAULT;
    }
}
lv_font_t lv_font_montserratMedium_20;
lv_font_t *lv_font_montserratMedium_20_ptr;
void lv_font_montserratMedium_20_file()
{
    if (lv_font_montserratMedium_20_ptr != NULL) {
        lv_font_free_bin(lv_font_montserratMedium_20_ptr);
        lv_font_montserratMedium_20_ptr = NULL;
        memset(&lv_font_montserratMedium_20, 0, sizeof(lv_font_t));
    }
#if LV_USE_GUIBUILDER_SIMULATOR
    lv_font_montserratMedium_20_ptr = lv_font_load_bin("A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\sdk\\ui_res\\flash\\rle\\font\\3500000b.rle");
#else
    lv_font_montserratMedium_20_ptr = lv_font_load_bin(gui_get_res_path(GUI_RES_MONTSERRATMEDIUM_20_TTF_FLASH));
#endif
    if (lv_font_montserratMedium_20_ptr != NULL) {
        lv_font_montserratMedium_20 = *lv_font_montserratMedium_20_ptr;
    } else {
#if LV_USE_GUIBUILDER_SIMULATOR
        LV_LOG_ERROR("Load Fnt Font Failed %s\n", "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\sdk\\ui_res\\flash\\rle\\font\\3500000b.rle");
#else
        LV_LOG_ERROR("Load Fnt Font Failed %s\n", gui_get_res_path(GUI_RES_MONTSERRATMEDIUM_20_TTF_FLASH));
#endif
        lv_font_montserratMedium_20 = *LV_FONT_DEFAULT;
    }
}
lv_font_t lv_font_montserratMedium_30;
lv_font_t *lv_font_montserratMedium_30_ptr;
void lv_font_montserratMedium_30_file()
{
    if (lv_font_montserratMedium_30_ptr != NULL) {
        lv_font_free_bin(lv_font_montserratMedium_30_ptr);
        lv_font_montserratMedium_30_ptr = NULL;
        memset(&lv_font_montserratMedium_30, 0, sizeof(lv_font_t));
    }
#if LV_USE_GUIBUILDER_SIMULATOR
    lv_font_montserratMedium_30_ptr = lv_font_load_bin("A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\sdk\\ui_res\\flash\\rle\\font\\3500000c.rle");
#else
    lv_font_montserratMedium_30_ptr = lv_font_load_bin(gui_get_res_path(GUI_RES_MONTSERRATMEDIUM_30_TTF_FLASH));
#endif
    if (lv_font_montserratMedium_30_ptr != NULL) {
        lv_font_montserratMedium_30 = *lv_font_montserratMedium_30_ptr;
    } else {
#if LV_USE_GUIBUILDER_SIMULATOR
        LV_LOG_ERROR("Load Fnt Font Failed %s\n", "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\sdk\\ui_res\\flash\\rle\\font\\3500000c.rle");
#else
        LV_LOG_ERROR("Load Fnt Font Failed %s\n", gui_get_res_path(GUI_RES_MONTSERRATMEDIUM_30_TTF_FLASH));
#endif
        lv_font_montserratMedium_30 = *LV_FONT_DEFAULT;
    }
}
lv_font_t lv_font_montserratMedium_32;
lv_font_t *lv_font_montserratMedium_32_ptr;
void lv_font_montserratMedium_32_file()
{
    if (lv_font_montserratMedium_32_ptr != NULL) {
        lv_font_free_bin(lv_font_montserratMedium_32_ptr);
        lv_font_montserratMedium_32_ptr = NULL;
        memset(&lv_font_montserratMedium_32, 0, sizeof(lv_font_t));
    }
#if LV_USE_GUIBUILDER_SIMULATOR
    lv_font_montserratMedium_32_ptr = lv_font_load_bin("A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\sdk\\ui_res\\flash\\rle\\font\\3500000d.rle");
#else
    lv_font_montserratMedium_32_ptr = lv_font_load_bin(gui_get_res_path(GUI_RES_MONTSERRATMEDIUM_32_TTF_FLASH));
#endif
    if (lv_font_montserratMedium_32_ptr != NULL) {
        lv_font_montserratMedium_32 = *lv_font_montserratMedium_32_ptr;
    } else {
#if LV_USE_GUIBUILDER_SIMULATOR
        LV_LOG_ERROR("Load Fnt Font Failed %s\n", "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\sdk\\ui_res\\flash\\rle\\font\\3500000d.rle");
#else
        LV_LOG_ERROR("Load Fnt Font Failed %s\n", gui_get_res_path(GUI_RES_MONTSERRATMEDIUM_32_TTF_FLASH));
#endif
        lv_font_montserratMedium_32 = *LV_FONT_DEFAULT;
    }
}
lv_font_t lv_font_montserratMedium_28;
lv_font_t *lv_font_montserratMedium_28_ptr;
void lv_font_montserratMedium_28_file()
{
    if (lv_font_montserratMedium_28_ptr != NULL) {
        lv_font_free_bin(lv_font_montserratMedium_28_ptr);
        lv_font_montserratMedium_28_ptr = NULL;
        memset(&lv_font_montserratMedium_28, 0, sizeof(lv_font_t));
    }
#if LV_USE_GUIBUILDER_SIMULATOR
    lv_font_montserratMedium_28_ptr = lv_font_load_bin("A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\sdk\\ui_res\\flash\\rle\\font\\3500000e.rle");
#else
    lv_font_montserratMedium_28_ptr = lv_font_load_bin(gui_get_res_path(GUI_RES_MONTSERRATMEDIUM_28_TTF_FLASH));
#endif
    if (lv_font_montserratMedium_28_ptr != NULL) {
        lv_font_montserratMedium_28 = *lv_font_montserratMedium_28_ptr;
    } else {
#if LV_USE_GUIBUILDER_SIMULATOR
        LV_LOG_ERROR("Load Fnt Font Failed %s\n", "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\sdk\\ui_res\\flash\\rle\\font\\3500000e.rle");
#else
        LV_LOG_ERROR("Load Fnt Font Failed %s\n", gui_get_res_path(GUI_RES_MONTSERRATMEDIUM_28_TTF_FLASH));
#endif
        lv_font_montserratMedium_28 = *LV_FONT_DEFAULT;
    }
}
lv_font_t lv_font_montserratMedium_21;
lv_font_t *lv_font_montserratMedium_21_ptr;
void lv_font_montserratMedium_21_file()
{
    if (lv_font_montserratMedium_21_ptr != NULL) {
        lv_font_free_bin(lv_font_montserratMedium_21_ptr);
        lv_font_montserratMedium_21_ptr = NULL;
        memset(&lv_font_montserratMedium_21, 0, sizeof(lv_font_t));
    }
#if LV_USE_GUIBUILDER_SIMULATOR
    lv_font_montserratMedium_21_ptr = lv_font_load_bin("A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\sdk\\ui_res\\flash\\rle\\font\\3500000f.rle");
#else
    lv_font_montserratMedium_21_ptr = lv_font_load_bin(gui_get_res_path(GUI_RES_MONTSERRATMEDIUM_21_TTF_FLASH));
#endif
    if (lv_font_montserratMedium_21_ptr != NULL) {
        lv_font_montserratMedium_21 = *lv_font_montserratMedium_21_ptr;
    } else {
#if LV_USE_GUIBUILDER_SIMULATOR
        LV_LOG_ERROR("Load Fnt Font Failed %s\n", "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\sdk\\ui_res\\flash\\rle\\font\\3500000f.rle");
#else
        LV_LOG_ERROR("Load Fnt Font Failed %s\n", gui_get_res_path(GUI_RES_MONTSERRATMEDIUM_21_TTF_FLASH));
#endif
        lv_font_montserratMedium_21 = *LV_FONT_DEFAULT;
    }
}
lv_font_t lv_font_simsun_16;
lv_font_t *lv_font_simsun_16_ptr;
void lv_font_simsun_16_file()
{
    if (lv_font_simsun_16_ptr != NULL) {
        lv_font_free_bin(lv_font_simsun_16_ptr);
        lv_font_simsun_16_ptr = NULL;
        memset(&lv_font_simsun_16, 0, sizeof(lv_font_t));
    }
#if LV_USE_GUIBUILDER_SIMULATOR
    lv_font_simsun_16_ptr = lv_font_load_bin("A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\sdk\\ui_res\\flash\\rle\\font\\35000010.rle");
#else
    lv_font_simsun_16_ptr = lv_font_load_bin(gui_get_res_path(GUI_RES_SIMSUN_16_WOFF_FLASH));
#endif
    if (lv_font_simsun_16_ptr != NULL) {
        lv_font_simsun_16 = *lv_font_simsun_16_ptr;
    } else {
#if LV_USE_GUIBUILDER_SIMULATOR
        LV_LOG_ERROR("Load Fnt Font Failed %s\n", "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\sdk\\ui_res\\flash\\rle\\font\\35000010.rle");
#else
        LV_LOG_ERROR("Load Fnt Font Failed %s\n", gui_get_res_path(GUI_RES_SIMSUN_16_WOFF_FLASH));
#endif
        lv_font_simsun_16 = *LV_FONT_DEFAULT;
    }
}
lv_font_t lv_font_simsun_18;
lv_font_t *lv_font_simsun_18_ptr;
void lv_font_simsun_18_file()
{
    if (lv_font_simsun_18_ptr != NULL) {
        lv_font_free_bin(lv_font_simsun_18_ptr);
        lv_font_simsun_18_ptr = NULL;
        memset(&lv_font_simsun_18, 0, sizeof(lv_font_t));
    }
#if LV_USE_GUIBUILDER_SIMULATOR
    lv_font_simsun_18_ptr = lv_font_load_bin("A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\sdk\\ui_res\\flash\\rle\\font\\35000011.rle");
#else
    lv_font_simsun_18_ptr = lv_font_load_bin(gui_get_res_path(GUI_RES_SIMSUN_18_WOFF_FLASH));
#endif
    if (lv_font_simsun_18_ptr != NULL) {
        lv_font_simsun_18 = *lv_font_simsun_18_ptr;
    } else {
#if LV_USE_GUIBUILDER_SIMULATOR
        LV_LOG_ERROR("Load Fnt Font Failed %s\n", "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\sdk\\ui_res\\flash\\rle\\font\\35000011.rle");
#else
        LV_LOG_ERROR("Load Fnt Font Failed %s\n", gui_get_res_path(GUI_RES_SIMSUN_18_WOFF_FLASH));
#endif
        lv_font_simsun_18 = *LV_FONT_DEFAULT;
    }
}
lv_font_t lv_font_fangsong_16;
lv_font_t *lv_font_fangsong_16_ptr;
void lv_font_fangsong_16_file()
{
    if (lv_font_fangsong_16_ptr != NULL) {
        lv_font_free_bin(lv_font_fangsong_16_ptr);
        lv_font_fangsong_16_ptr = NULL;
        memset(&lv_font_fangsong_16, 0, sizeof(lv_font_t));
    }
#if LV_USE_GUIBUILDER_SIMULATOR
    lv_font_fangsong_16_ptr = lv_font_load_bin("A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\sdk\\ui_res\\flash\\rle\\font\\35000012.rle");
#else
    lv_font_fangsong_16_ptr = lv_font_load_bin(gui_get_res_path(GUI_RES_FANGSONG_16_TTF_FLASH));
#endif
    if (lv_font_fangsong_16_ptr != NULL) {
        lv_font_fangsong_16 = *lv_font_fangsong_16_ptr;
    } else {
#if LV_USE_GUIBUILDER_SIMULATOR
        LV_LOG_ERROR("Load Fnt Font Failed %s\n", "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\sdk\\ui_res\\flash\\rle\\font\\35000012.rle");
#else
        LV_LOG_ERROR("Load Fnt Font Failed %s\n", gui_get_res_path(GUI_RES_FANGSONG_16_TTF_FLASH));
#endif
        lv_font_fangsong_16 = *LV_FONT_DEFAULT;
    }
}
lv_font_t lv_font_fangsong_24;
lv_font_t *lv_font_fangsong_24_ptr;
void lv_font_fangsong_24_file()
{
    if (lv_font_fangsong_24_ptr != NULL) {
        lv_font_free_bin(lv_font_fangsong_24_ptr);
        lv_font_fangsong_24_ptr = NULL;
        memset(&lv_font_fangsong_24, 0, sizeof(lv_font_t));
    }
#if LV_USE_GUIBUILDER_SIMULATOR
    lv_font_fangsong_24_ptr = lv_font_load_bin("A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\sdk\\ui_res\\flash\\rle\\font\\35000013.rle");
#else
    lv_font_fangsong_24_ptr = lv_font_load_bin(gui_get_res_path(GUI_RES_FANGSONG_24_TTF_FLASH));
#endif
    if (lv_font_fangsong_24_ptr != NULL) {
        lv_font_fangsong_24 = *lv_font_fangsong_24_ptr;
    } else {
#if LV_USE_GUIBUILDER_SIMULATOR
        LV_LOG_ERROR("Load Fnt Font Failed %s\n", "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\sdk\\ui_res\\flash\\rle\\font\\35000013.rle");
#else
        LV_LOG_ERROR("Load Fnt Font Failed %s\n", gui_get_res_path(GUI_RES_FANGSONG_24_TTF_FLASH));
#endif
        lv_font_fangsong_24 = *LV_FONT_DEFAULT;
    }
}
lv_font_t lv_font_timesnewromanpsmt_16;
lv_font_t *lv_font_timesnewromanpsmt_16_ptr;
void lv_font_timesnewromanpsmt_16_file()
{
    if (lv_font_timesnewromanpsmt_16_ptr != NULL) {
        lv_font_free_bin(lv_font_timesnewromanpsmt_16_ptr);
        lv_font_timesnewromanpsmt_16_ptr = NULL;
        memset(&lv_font_timesnewromanpsmt_16, 0, sizeof(lv_font_t));
    }
#if LV_USE_GUIBUILDER_SIMULATOR
    lv_font_timesnewromanpsmt_16_ptr = lv_font_load_bin("A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\sdk\\ui_res\\flash\\rle\\font\\35000014.rle");
#else
    lv_font_timesnewromanpsmt_16_ptr = lv_font_load_bin(gui_get_res_path(GUI_RES_TIMESNEWROMANPSMT_16_TTF_FLASH));
#endif
    if (lv_font_timesnewromanpsmt_16_ptr != NULL) {
        lv_font_timesnewromanpsmt_16 = *lv_font_timesnewromanpsmt_16_ptr;
    } else {
#if LV_USE_GUIBUILDER_SIMULATOR
        LV_LOG_ERROR("Load Fnt Font Failed %s\n", "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\sdk\\ui_res\\flash\\rle\\font\\35000014.rle");
#else
        LV_LOG_ERROR("Load Fnt Font Failed %s\n", gui_get_res_path(GUI_RES_TIMESNEWROMANPSMT_16_TTF_FLASH));
#endif
        lv_font_timesnewromanpsmt_16 = *LV_FONT_DEFAULT;
    }
}
lv_font_t lv_font_timesnewromanpsmt_24;
lv_font_t *lv_font_timesnewromanpsmt_24_ptr;
void lv_font_timesnewromanpsmt_24_file()
{
    if (lv_font_timesnewromanpsmt_24_ptr != NULL) {
        lv_font_free_bin(lv_font_timesnewromanpsmt_24_ptr);
        lv_font_timesnewromanpsmt_24_ptr = NULL;
        memset(&lv_font_timesnewromanpsmt_24, 0, sizeof(lv_font_t));
    }
#if LV_USE_GUIBUILDER_SIMULATOR
    lv_font_timesnewromanpsmt_24_ptr = lv_font_load_bin("A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\sdk\\ui_res\\flash\\rle\\font\\35000015.rle");
#else
    lv_font_timesnewromanpsmt_24_ptr = lv_font_load_bin(gui_get_res_path(GUI_RES_TIMESNEWROMANPSMT_24_TTF_FLASH));
#endif
    if (lv_font_timesnewromanpsmt_24_ptr != NULL) {
        lv_font_timesnewromanpsmt_24 = *lv_font_timesnewromanpsmt_24_ptr;
    } else {
#if LV_USE_GUIBUILDER_SIMULATOR
        LV_LOG_ERROR("Load Fnt Font Failed %s\n", "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\sdk\\ui_res\\flash\\rle\\font\\35000015.rle");
#else
        LV_LOG_ERROR("Load Fnt Font Failed %s\n", gui_get_res_path(GUI_RES_TIMESNEWROMANPSMT_24_TTF_FLASH));
#endif
        lv_font_timesnewromanpsmt_24 = *LV_FONT_DEFAULT;
    }
}
lv_font_t lv_font_segoeui_16;
lv_font_t *lv_font_segoeui_16_ptr;
void lv_font_segoeui_16_file()
{
    if (lv_font_segoeui_16_ptr != NULL) {
        lv_font_free_bin(lv_font_segoeui_16_ptr);
        lv_font_segoeui_16_ptr = NULL;
        memset(&lv_font_segoeui_16, 0, sizeof(lv_font_t));
    }
#if LV_USE_GUIBUILDER_SIMULATOR
    lv_font_segoeui_16_ptr = lv_font_load_bin("A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\sdk\\ui_res\\flash\\rle\\font\\35000016.rle");
#else
    lv_font_segoeui_16_ptr = lv_font_load_bin(gui_get_res_path(GUI_RES_SEGOEUI_16_TTF_FLASH));
#endif
    if (lv_font_segoeui_16_ptr != NULL) {
        lv_font_segoeui_16 = *lv_font_segoeui_16_ptr;
    } else {
#if LV_USE_GUIBUILDER_SIMULATOR
        LV_LOG_ERROR("Load Fnt Font Failed %s\n", "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\sdk\\ui_res\\flash\\rle\\font\\35000016.rle");
#else
        LV_LOG_ERROR("Load Fnt Font Failed %s\n", gui_get_res_path(GUI_RES_SEGOEUI_16_TTF_FLASH));
#endif
        lv_font_segoeui_16 = *LV_FONT_DEFAULT;
    }
}
lv_font_t lv_font_segoeui_24;
lv_font_t *lv_font_segoeui_24_ptr;
void lv_font_segoeui_24_file()
{
    if (lv_font_segoeui_24_ptr != NULL) {
        lv_font_free_bin(lv_font_segoeui_24_ptr);
        lv_font_segoeui_24_ptr = NULL;
        memset(&lv_font_segoeui_24, 0, sizeof(lv_font_t));
    }
#if LV_USE_GUIBUILDER_SIMULATOR
    lv_font_segoeui_24_ptr = lv_font_load_bin("A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\sdk\\ui_res\\flash\\rle\\font\\35000017.rle");
#else
    lv_font_segoeui_24_ptr = lv_font_load_bin(gui_get_res_path(GUI_RES_SEGOEUI_24_TTF_FLASH));
#endif
    if (lv_font_segoeui_24_ptr != NULL) {
        lv_font_segoeui_24 = *lv_font_segoeui_24_ptr;
    } else {
#if LV_USE_GUIBUILDER_SIMULATOR
        LV_LOG_ERROR("Load Fnt Font Failed %s\n", "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\sdk\\ui_res\\flash\\rle\\font\\35000017.rle");
#else
        LV_LOG_ERROR("Load Fnt Font Failed %s\n", gui_get_res_path(GUI_RES_SEGOEUI_24_TTF_FLASH));
#endif
        lv_font_segoeui_24 = *LV_FONT_DEFAULT;
    }
}
lv_font_t lv_font_leelawadeeui_16;
lv_font_t *lv_font_leelawadeeui_16_ptr;
void lv_font_leelawadeeui_16_file()
{
    if (lv_font_leelawadeeui_16_ptr != NULL) {
        lv_font_free_bin(lv_font_leelawadeeui_16_ptr);
        lv_font_leelawadeeui_16_ptr = NULL;
        memset(&lv_font_leelawadeeui_16, 0, sizeof(lv_font_t));
    }
#if LV_USE_GUIBUILDER_SIMULATOR
    lv_font_leelawadeeui_16_ptr = lv_font_load_bin("A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\sdk\\ui_res\\flash\\rle\\font\\35000018.rle");
#else
    lv_font_leelawadeeui_16_ptr = lv_font_load_bin(gui_get_res_path(GUI_RES_LEELAWADEEUI_16_TTF_FLASH));
#endif
    if (lv_font_leelawadeeui_16_ptr != NULL) {
        lv_font_leelawadeeui_16 = *lv_font_leelawadeeui_16_ptr;
    } else {
#if LV_USE_GUIBUILDER_SIMULATOR
        LV_LOG_ERROR("Load Fnt Font Failed %s\n", "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\sdk\\ui_res\\flash\\rle\\font\\35000018.rle");
#else
        LV_LOG_ERROR("Load Fnt Font Failed %s\n", gui_get_res_path(GUI_RES_LEELAWADEEUI_16_TTF_FLASH));
#endif
        lv_font_leelawadeeui_16 = *LV_FONT_DEFAULT;
    }
}
lv_font_t lv_font_leelawadeeui_24;
lv_font_t *lv_font_leelawadeeui_24_ptr;
void lv_font_leelawadeeui_24_file()
{
    if (lv_font_leelawadeeui_24_ptr != NULL) {
        lv_font_free_bin(lv_font_leelawadeeui_24_ptr);
        lv_font_leelawadeeui_24_ptr = NULL;
        memset(&lv_font_leelawadeeui_24, 0, sizeof(lv_font_t));
    }
#if LV_USE_GUIBUILDER_SIMULATOR
    lv_font_leelawadeeui_24_ptr = lv_font_load_bin("A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\sdk\\ui_res\\flash\\rle\\font\\35000019.rle");
#else
    lv_font_leelawadeeui_24_ptr = lv_font_load_bin(gui_get_res_path(GUI_RES_LEELAWADEEUI_24_TTF_FLASH));
#endif
    if (lv_font_leelawadeeui_24_ptr != NULL) {
        lv_font_leelawadeeui_24 = *lv_font_leelawadeeui_24_ptr;
    } else {
#if LV_USE_GUIBUILDER_SIMULATOR
        LV_LOG_ERROR("Load Fnt Font Failed %s\n", "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\sdk\\ui_res\\flash\\rle\\font\\35000019.rle");
#else
        LV_LOG_ERROR("Load Fnt Font Failed %s\n", gui_get_res_path(GUI_RES_LEELAWADEEUI_24_TTF_FLASH));
#endif
        lv_font_leelawadeeui_24 = *LV_FONT_DEFAULT;
    }
}
lv_font_t lv_font_malgungothic_16;
lv_font_t *lv_font_malgungothic_16_ptr;
void lv_font_malgungothic_16_file()
{
    if (lv_font_malgungothic_16_ptr != NULL) {
        lv_font_free_bin(lv_font_malgungothic_16_ptr);
        lv_font_malgungothic_16_ptr = NULL;
        memset(&lv_font_malgungothic_16, 0, sizeof(lv_font_t));
    }
#if LV_USE_GUIBUILDER_SIMULATOR
    lv_font_malgungothic_16_ptr = lv_font_load_bin("A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\sdk\\ui_res\\flash\\rle\\font\\3500001a.rle");
#else
    lv_font_malgungothic_16_ptr = lv_font_load_bin(gui_get_res_path(GUI_RES_MALGUNGOTHIC_16_TTF_FLASH));
#endif
    if (lv_font_malgungothic_16_ptr != NULL) {
        lv_font_malgungothic_16 = *lv_font_malgungothic_16_ptr;
    } else {
#if LV_USE_GUIBUILDER_SIMULATOR
        LV_LOG_ERROR("Load Fnt Font Failed %s\n", "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\sdk\\ui_res\\flash\\rle\\font\\3500001a.rle");
#else
        LV_LOG_ERROR("Load Fnt Font Failed %s\n", gui_get_res_path(GUI_RES_MALGUNGOTHIC_16_TTF_FLASH));
#endif
        lv_font_malgungothic_16 = *LV_FONT_DEFAULT;
    }
}
lv_font_t lv_font_malgungothic_24;
lv_font_t *lv_font_malgungothic_24_ptr;
void lv_font_malgungothic_24_file()
{
    if (lv_font_malgungothic_24_ptr != NULL) {
        lv_font_free_bin(lv_font_malgungothic_24_ptr);
        lv_font_malgungothic_24_ptr = NULL;
        memset(&lv_font_malgungothic_24, 0, sizeof(lv_font_t));
    }
#if LV_USE_GUIBUILDER_SIMULATOR
    lv_font_malgungothic_24_ptr = lv_font_load_bin("A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\sdk\\ui_res\\flash\\rle\\font\\3500001b.rle");
#else
    lv_font_malgungothic_24_ptr = lv_font_load_bin(gui_get_res_path(GUI_RES_MALGUNGOTHIC_24_TTF_FLASH));
#endif
    if (lv_font_malgungothic_24_ptr != NULL) {
        lv_font_malgungothic_24 = *lv_font_malgungothic_24_ptr;
    } else {
#if LV_USE_GUIBUILDER_SIMULATOR
        LV_LOG_ERROR("Load Fnt Font Failed %s\n", "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\sdk\\ui_res\\flash\\rle\\font\\3500001b.rle");
#else
        LV_LOG_ERROR("Load Fnt Font Failed %s\n", gui_get_res_path(GUI_RES_MALGUNGOTHIC_24_TTF_FLASH));
#endif
        lv_font_malgungothic_24 = *LV_FONT_DEFAULT;
    }
}
lv_font_t lv_font_ms_gothic_16;
lv_font_t *lv_font_ms_gothic_16_ptr;
void lv_font_ms_gothic_16_file()
{
    if (lv_font_ms_gothic_16_ptr != NULL) {
        lv_font_free_bin(lv_font_ms_gothic_16_ptr);
        lv_font_ms_gothic_16_ptr = NULL;
        memset(&lv_font_ms_gothic_16, 0, sizeof(lv_font_t));
    }
#if LV_USE_GUIBUILDER_SIMULATOR
    lv_font_ms_gothic_16_ptr = lv_font_load_bin("A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\sdk\\ui_res\\flash\\rle\\font\\3500001c.rle");
#else
    lv_font_ms_gothic_16_ptr = lv_font_load_bin(gui_get_res_path(GUI_RES_MS_GOTHIC_16_TTF_FLASH));
#endif
    if (lv_font_ms_gothic_16_ptr != NULL) {
        lv_font_ms_gothic_16 = *lv_font_ms_gothic_16_ptr;
    } else {
#if LV_USE_GUIBUILDER_SIMULATOR
        LV_LOG_ERROR("Load Fnt Font Failed %s\n", "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\sdk\\ui_res\\flash\\rle\\font\\3500001c.rle");
#else
        LV_LOG_ERROR("Load Fnt Font Failed %s\n", gui_get_res_path(GUI_RES_MS_GOTHIC_16_TTF_FLASH));
#endif
        lv_font_ms_gothic_16 = *LV_FONT_DEFAULT;
    }
}
lv_font_t lv_font_calibri_16;
lv_font_t *lv_font_calibri_16_ptr;
void lv_font_calibri_16_file()
{
    if (lv_font_calibri_16_ptr != NULL) {
        lv_font_free_bin(lv_font_calibri_16_ptr);
        lv_font_calibri_16_ptr = NULL;
        memset(&lv_font_calibri_16, 0, sizeof(lv_font_t));
    }
#if LV_USE_GUIBUILDER_SIMULATOR
    lv_font_calibri_16_ptr = lv_font_load_bin("A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\sdk\\ui_res\\flash\\rle\\font\\3500001d.rle");
#else
    lv_font_calibri_16_ptr = lv_font_load_bin(gui_get_res_path(GUI_RES_CALIBRI_16_TTF_FLASH));
#endif
    if (lv_font_calibri_16_ptr != NULL) {
        lv_font_calibri_16 = *lv_font_calibri_16_ptr;
    } else {
#if LV_USE_GUIBUILDER_SIMULATOR
        LV_LOG_ERROR("Load Fnt Font Failed %s\n", "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\sdk\\ui_res\\flash\\rle\\font\\3500001d.rle");
#else
        LV_LOG_ERROR("Load Fnt Font Failed %s\n", gui_get_res_path(GUI_RES_CALIBRI_16_TTF_FLASH));
#endif
        lv_font_calibri_16 = *LV_FONT_DEFAULT;
    }
}
lv_font_t lv_font_calibri_24;
lv_font_t *lv_font_calibri_24_ptr;
void lv_font_calibri_24_file()
{
    if (lv_font_calibri_24_ptr != NULL) {
        lv_font_free_bin(lv_font_calibri_24_ptr);
        lv_font_calibri_24_ptr = NULL;
        memset(&lv_font_calibri_24, 0, sizeof(lv_font_t));
    }
#if LV_USE_GUIBUILDER_SIMULATOR
    lv_font_calibri_24_ptr = lv_font_load_bin("A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\sdk\\ui_res\\flash\\rle\\font\\3500001e.rle");
#else
    lv_font_calibri_24_ptr = lv_font_load_bin(gui_get_res_path(GUI_RES_CALIBRI_24_TTF_FLASH));
#endif
    if (lv_font_calibri_24_ptr != NULL) {
        lv_font_calibri_24 = *lv_font_calibri_24_ptr;
    } else {
#if LV_USE_GUIBUILDER_SIMULATOR
        LV_LOG_ERROR("Load Fnt Font Failed %s\n", "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\sdk\\ui_res\\flash\\rle\\font\\3500001e.rle");
#else
        LV_LOG_ERROR("Load Fnt Font Failed %s\n", gui_get_res_path(GUI_RES_CALIBRI_24_TTF_FLASH));
#endif
        lv_font_calibri_24 = *LV_FONT_DEFAULT;
    }
}

void init_gui_fonts()
{
    lv_font_FangZhengKaiTiJianTi_1_22_file();
    lv_font_FangZhengKaiTiJianTi_1_26_file();
    lv_font_FangZhengKaiTiJianTi_1_18_file();
    lv_font_montserratMedium_18_file();
    lv_font_FangZhengKaiTiJianTi_1_48_file();
    lv_font_montserratMedium_24_file();
    lv_font_montserratMedium_12_file();
    lv_font_montserratMedium_22_file();
    lv_font_FangZhengKaiTiJianTi_1_24_file();
    lv_font_FangZhengKaiTiJianTi_1_16_file();
    lv_font_montserratMedium_16_file();
    lv_font_montserratMedium_20_file();
    lv_font_montserratMedium_30_file();
    lv_font_montserratMedium_32_file();
    lv_font_montserratMedium_28_file();
    lv_font_montserratMedium_21_file();
    lv_font_simsun_16_file();
    lv_font_simsun_18_file();
    lv_font_fangsong_16_file();
    lv_font_fangsong_24_file();
    lv_font_timesnewromanpsmt_16_file();
    lv_font_timesnewromanpsmt_24_file();
    lv_font_segoeui_16_file();
    lv_font_segoeui_24_file();
    lv_font_leelawadeeui_16_file();
    lv_font_leelawadeeui_24_file();
    lv_font_malgungothic_16_file();
    lv_font_malgungothic_24_file();
    lv_font_ms_gothic_16_file();
    lv_font_calibri_16_file();
    lv_font_calibri_24_file();


}

void free_gui_fonts()
{
    if (lv_font_FangZhengKaiTiJianTi_1_22_ptr != NULL) {
        lv_font_free_bin(lv_font_FangZhengKaiTiJianTi_1_22_ptr);
        lv_font_FangZhengKaiTiJianTi_1_22_ptr = NULL;
        memset(&lv_font_FangZhengKaiTiJianTi_1_22, 0, sizeof(lv_font_t));
    }
    if (lv_font_FangZhengKaiTiJianTi_1_26_ptr != NULL) {
        lv_font_free_bin(lv_font_FangZhengKaiTiJianTi_1_26_ptr);
        lv_font_FangZhengKaiTiJianTi_1_26_ptr = NULL;
        memset(&lv_font_FangZhengKaiTiJianTi_1_26, 0, sizeof(lv_font_t));
    }
    if (lv_font_FangZhengKaiTiJianTi_1_18_ptr != NULL) {
        lv_font_free_bin(lv_font_FangZhengKaiTiJianTi_1_18_ptr);
        lv_font_FangZhengKaiTiJianTi_1_18_ptr = NULL;
        memset(&lv_font_FangZhengKaiTiJianTi_1_18, 0, sizeof(lv_font_t));
    }
    if (lv_font_montserratMedium_18_ptr != NULL) {
        lv_font_free_bin(lv_font_montserratMedium_18_ptr);
        lv_font_montserratMedium_18_ptr = NULL;
        memset(&lv_font_montserratMedium_18, 0, sizeof(lv_font_t));
    }
    if (lv_font_FangZhengKaiTiJianTi_1_48_ptr != NULL) {
        lv_font_free_bin(lv_font_FangZhengKaiTiJianTi_1_48_ptr);
        lv_font_FangZhengKaiTiJianTi_1_48_ptr = NULL;
        memset(&lv_font_FangZhengKaiTiJianTi_1_48, 0, sizeof(lv_font_t));
    }
    if (lv_font_montserratMedium_24_ptr != NULL) {
        lv_font_free_bin(lv_font_montserratMedium_24_ptr);
        lv_font_montserratMedium_24_ptr = NULL;
        memset(&lv_font_montserratMedium_24, 0, sizeof(lv_font_t));
    }
    if (lv_font_montserratMedium_12_ptr != NULL) {
        lv_font_free_bin(lv_font_montserratMedium_12_ptr);
        lv_font_montserratMedium_12_ptr = NULL;
        memset(&lv_font_montserratMedium_12, 0, sizeof(lv_font_t));
    }
    if (lv_font_montserratMedium_22_ptr != NULL) {
        lv_font_free_bin(lv_font_montserratMedium_22_ptr);
        lv_font_montserratMedium_22_ptr = NULL;
        memset(&lv_font_montserratMedium_22, 0, sizeof(lv_font_t));
    }
    if (lv_font_FangZhengKaiTiJianTi_1_24_ptr != NULL) {
        lv_font_free_bin(lv_font_FangZhengKaiTiJianTi_1_24_ptr);
        lv_font_FangZhengKaiTiJianTi_1_24_ptr = NULL;
        memset(&lv_font_FangZhengKaiTiJianTi_1_24, 0, sizeof(lv_font_t));
    }
    if (lv_font_FangZhengKaiTiJianTi_1_16_ptr != NULL) {
        lv_font_free_bin(lv_font_FangZhengKaiTiJianTi_1_16_ptr);
        lv_font_FangZhengKaiTiJianTi_1_16_ptr = NULL;
        memset(&lv_font_FangZhengKaiTiJianTi_1_16, 0, sizeof(lv_font_t));
    }
    if (lv_font_montserratMedium_16_ptr != NULL) {
        lv_font_free_bin(lv_font_montserratMedium_16_ptr);
        lv_font_montserratMedium_16_ptr = NULL;
        memset(&lv_font_montserratMedium_16, 0, sizeof(lv_font_t));
    }
    if (lv_font_montserratMedium_20_ptr != NULL) {
        lv_font_free_bin(lv_font_montserratMedium_20_ptr);
        lv_font_montserratMedium_20_ptr = NULL;
        memset(&lv_font_montserratMedium_20, 0, sizeof(lv_font_t));
    }
    if (lv_font_montserratMedium_30_ptr != NULL) {
        lv_font_free_bin(lv_font_montserratMedium_30_ptr);
        lv_font_montserratMedium_30_ptr = NULL;
        memset(&lv_font_montserratMedium_30, 0, sizeof(lv_font_t));
    }
    if (lv_font_montserratMedium_32_ptr != NULL) {
        lv_font_free_bin(lv_font_montserratMedium_32_ptr);
        lv_font_montserratMedium_32_ptr = NULL;
        memset(&lv_font_montserratMedium_32, 0, sizeof(lv_font_t));
    }
    if (lv_font_montserratMedium_28_ptr != NULL) {
        lv_font_free_bin(lv_font_montserratMedium_28_ptr);
        lv_font_montserratMedium_28_ptr = NULL;
        memset(&lv_font_montserratMedium_28, 0, sizeof(lv_font_t));
    }
    if (lv_font_montserratMedium_21_ptr != NULL) {
        lv_font_free_bin(lv_font_montserratMedium_21_ptr);
        lv_font_montserratMedium_21_ptr = NULL;
        memset(&lv_font_montserratMedium_21, 0, sizeof(lv_font_t));
    }
    if (lv_font_simsun_16_ptr != NULL) {
        lv_font_free_bin(lv_font_simsun_16_ptr);
        lv_font_simsun_16_ptr = NULL;
        memset(&lv_font_simsun_16, 0, sizeof(lv_font_t));
    }
    if (lv_font_simsun_18_ptr != NULL) {
        lv_font_free_bin(lv_font_simsun_18_ptr);
        lv_font_simsun_18_ptr = NULL;
        memset(&lv_font_simsun_18, 0, sizeof(lv_font_t));
    }
    if (lv_font_fangsong_16_ptr != NULL) {
        lv_font_free_bin(lv_font_fangsong_16_ptr);
        lv_font_fangsong_16_ptr = NULL;
        memset(&lv_font_fangsong_16, 0, sizeof(lv_font_t));
    }
    if (lv_font_fangsong_24_ptr != NULL) {
        lv_font_free_bin(lv_font_fangsong_24_ptr);
        lv_font_fangsong_24_ptr = NULL;
        memset(&lv_font_fangsong_24, 0, sizeof(lv_font_t));
    }
    if (lv_font_timesnewromanpsmt_16_ptr != NULL) {
        lv_font_free_bin(lv_font_timesnewromanpsmt_16_ptr);
        lv_font_timesnewromanpsmt_16_ptr = NULL;
        memset(&lv_font_timesnewromanpsmt_16, 0, sizeof(lv_font_t));
    }
    if (lv_font_timesnewromanpsmt_24_ptr != NULL) {
        lv_font_free_bin(lv_font_timesnewromanpsmt_24_ptr);
        lv_font_timesnewromanpsmt_24_ptr = NULL;
        memset(&lv_font_timesnewromanpsmt_24, 0, sizeof(lv_font_t));
    }
    if (lv_font_segoeui_16_ptr != NULL) {
        lv_font_free_bin(lv_font_segoeui_16_ptr);
        lv_font_segoeui_16_ptr = NULL;
        memset(&lv_font_segoeui_16, 0, sizeof(lv_font_t));
    }
    if (lv_font_segoeui_24_ptr != NULL) {
        lv_font_free_bin(lv_font_segoeui_24_ptr);
        lv_font_segoeui_24_ptr = NULL;
        memset(&lv_font_segoeui_24, 0, sizeof(lv_font_t));
    }
    if (lv_font_leelawadeeui_16_ptr != NULL) {
        lv_font_free_bin(lv_font_leelawadeeui_16_ptr);
        lv_font_leelawadeeui_16_ptr = NULL;
        memset(&lv_font_leelawadeeui_16, 0, sizeof(lv_font_t));
    }
    if (lv_font_leelawadeeui_24_ptr != NULL) {
        lv_font_free_bin(lv_font_leelawadeeui_24_ptr);
        lv_font_leelawadeeui_24_ptr = NULL;
        memset(&lv_font_leelawadeeui_24, 0, sizeof(lv_font_t));
    }
    if (lv_font_malgungothic_16_ptr != NULL) {
        lv_font_free_bin(lv_font_malgungothic_16_ptr);
        lv_font_malgungothic_16_ptr = NULL;
        memset(&lv_font_malgungothic_16, 0, sizeof(lv_font_t));
    }
    if (lv_font_malgungothic_24_ptr != NULL) {
        lv_font_free_bin(lv_font_malgungothic_24_ptr);
        lv_font_malgungothic_24_ptr = NULL;
        memset(&lv_font_malgungothic_24, 0, sizeof(lv_font_t));
    }
    if (lv_font_ms_gothic_16_ptr != NULL) {
        lv_font_free_bin(lv_font_ms_gothic_16_ptr);
        lv_font_ms_gothic_16_ptr = NULL;
        memset(&lv_font_ms_gothic_16, 0, sizeof(lv_font_t));
    }
    if (lv_font_calibri_16_ptr != NULL) {
        lv_font_free_bin(lv_font_calibri_16_ptr);
        lv_font_calibri_16_ptr = NULL;
        memset(&lv_font_calibri_16, 0, sizeof(lv_font_t));
    }
    if (lv_font_calibri_24_ptr != NULL) {
        lv_font_free_bin(lv_font_calibri_24_ptr);
        lv_font_calibri_24_ptr = NULL;
        memset(&lv_font_calibri_24, 0, sizeof(lv_font_t));
    }
}


#endif
