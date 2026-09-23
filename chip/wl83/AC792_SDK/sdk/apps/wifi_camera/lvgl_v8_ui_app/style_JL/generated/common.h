#include "app_config.h"
#ifdef CONFIG_UI_STYLE_JL_ENABLE
/*Generate Code, Do NOT Edit!*/
#ifndef __COMMON_H__
#define __COMMON_H__
#ifdef __cplusplus
extern "C" {
#endif

#include "./gui_res/res_common.h"

#define GUI_UIT_VERSION_MAJOR 1
#define GUI_UIT_VERSION_MINOR 0
#define GUI_UIT_VERSION_PATCH 0
#define GUI_UIT_VERSION_INFO "20250425"

#define GUI_CORE_VERSION_MAJOR 3
#define GUI_CORE_VERSION_MINOR 0
#define GUI_CORE_VERSION_PATCH 0
#define GUI_CORE_VERSION_INFO "GENERIC(with tools)"

#define GUI_TEMPLATE_VERSION_MAJOR 1
#define GUI_TEMPLATE_VERSION_MINOR 3
#define GUI_TEMPLATE_VERSION_PATCH 3
#define GUI_TEMPLATE_VERSION_INFO "dvr_jl_800x480_V1(1.3.3)"

typedef enum {
    GUI_SCREEN_ACTION_LOAD = 0,
    GUI_SCREEN_ACTION_UNLOAD
} gui_screen_action_t;

typedef enum {
    GUI_SCREEN_USB_SLAVE = 0,
    GUI_SCREEN_VIDEO_REC,
    GUI_SCREEN_HOME_PAGE,
    GUI_SCREEN_SYS_PROMPT,
    GUI_SCREEN_SYS_SETTING,
    GUI_SCREEN_VIDEO_PHOTO,
    GUI_SCREEN_VIDEO_PLAY,
    GUI_SCREEN_VIDEO_FILE,
    GUI_SCREEN_VIDEO_DIR,
    GUI_SCREEN_CAR_PARKING,
    GUI_SCREEN_LINE_DRIFT,
    GUI_SCREEN_SYS_POPWIN,
} gui_screen_id_t;

#define GUI_KEY_F1 1

#ifdef __cplusplus
}
#endif
#endif

#endif
