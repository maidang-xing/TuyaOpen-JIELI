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
#define GUI_UIT_VERSION_INFO "20260319"

#define GUI_CORE_VERSION_MAJOR 3
#define GUI_CORE_VERSION_MINOR 0
#define GUI_CORE_VERSION_PATCH 3
#define GUI_CORE_VERSION_INFO "GENERIC(with tools)"

#define GUI_TEMPLATE_VERSION_MAJOR 1
#define GUI_TEMPLATE_VERSION_MINOR 3
#define GUI_TEMPLATE_VERSION_PATCH 0
#define GUI_TEMPLATE_VERSION_INFO "wl83_empty"

#if LV_USE_GUIBUILDER_SIMULATOR
#define GUI_TM_MON(mon) ((mon) + 1)
#else
#define GUI_TM_MON(mon) (mon)
#endif

typedef enum {
    GUI_SCREEN_ACTION_LOAD = 0,
    GUI_SCREEN_ACTION_UNLOAD
} gui_screen_action_t;

typedef enum {
    GUI_SCREEN_MUSIC_PLAYER = 0,
    GUI_SCREEN_SYS_MENU,
    GUI_SCREEN_EQ_MODIFY,
} gui_screen_id_t;

static const int32_t gui_screen_ids[] = {
    GUI_SCREEN_MUSIC_PLAYER,
    GUI_SCREEN_SYS_MENU,
    GUI_SCREEN_EQ_MODIFY,
};


#ifdef __cplusplus
}
#endif
#endif
