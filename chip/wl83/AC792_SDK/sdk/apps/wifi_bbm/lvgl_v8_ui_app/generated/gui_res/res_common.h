/*Generate Code, Do NOT Edit!*/
#ifndef __RES_COMMON_H__
#define __RES_COMMON_H__
#ifdef __cplusplus
extern "C" {
#endif

#include "lvgl.h"

#if LV_USE_GUIBUILDER_SIMULATOR
#define GUI_WEAKREF __attribute__((weakref))
#define GUI_WEAK __attribute__((weak))
#else
#define GUI_WEAKREF
#define GUI_WEAK __attribute__((weak))
#endif

#define CONV_RES_ID(id) (((id) >> 24) | ((id) & 0x00FFFFFF) << 8)
typedef enum {
    GUI_RES_WIFI_1_PNG = 0x4B000000,   //F:\gitlab-m\ac792\ui_prj\wifi_bbm_240x320\import\image\wifi_1.png
    GUI_RES_WIFI_2_PNG = 0x4B000001,   //F:\gitlab-m\ac792\ui_prj\wifi_bbm_240x320\import\image\wifi_2.png
    GUI_RES_WIFI_3_PNG = 0x4B000002,   //F:\gitlab-m\ac792\ui_prj\wifi_bbm_240x320\import\image\wifi_3.png
    GUI_RES_WIFI_4_PNG = 0x4B000003,   //F:\gitlab-m\ac792\ui_prj\wifi_bbm_240x320\import\image\wifi_4.png
    GUI_RES_WIFI_5_PNG = 0x4B000004,   //F:\gitlab-m\ac792\ui_prj\wifi_bbm_240x320\import\image\wifi_5.png
} GUI_RES_ID;

extern char *gui_get_res_path(int32_t id);

#ifdef __cplusplus
}
#endif
#endif
