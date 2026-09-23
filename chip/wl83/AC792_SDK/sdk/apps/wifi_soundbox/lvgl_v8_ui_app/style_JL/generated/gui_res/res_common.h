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
    GUI_RES_FANGZHENGKAITIJIANTI_1_12_TTF_FLASH = 0x35000000,   //D:\wl83\ac792\ui_prj\wifi_soundbox_800x480\sdk\ui_res\flash\rle\font\35000000.rle
    GUI_RES_FANGZHENGKAITIJIANTI_1_24_TTF_FLASH = 0x35000001,   //D:\wl83\ac792\ui_prj\wifi_soundbox_800x480\sdk\ui_res\flash\rle\font\35000001.rle
    GUI_RES_FANGZHENGKAITIJIANTI_1_32_TTF_FLASH = 0x35000002,   //D:\wl83\ac792\ui_prj\wifi_soundbox_800x480\sdk\ui_res\flash\rle\font\35000002.rle

    GUI_RES_IMAGE_4225207_0_PNG = 0x4B000003,   //D:\wl83\ac792\ui_prj\wifi_soundbox_800x480\import\image\icon_02itzp4fqyho\image_4225207_0.png
    GUI_RES_IMAGE_4225207_1_PNG = 0x4B000004,   //D:\wl83\ac792\ui_prj\wifi_soundbox_800x480\import\image\icon_02itzp4fqyho\image_4225207_1.png
    GUI_RES_IMAGE_4225207_2_PNG = 0x4B000005,   //D:\wl83\ac792\ui_prj\wifi_soundbox_800x480\import\image\icon_02itzp4fqyho\image_4225207_2.png
    GUI_RES_IMAGE_4225207_3_PNG = 0x4B000006,   //D:\wl83\ac792\ui_prj\wifi_soundbox_800x480\import\image\icon_02itzp4fqyho\image_4225207_3.png
    GUI_RES_IMAGE_4225532_4_PNG = 0x4B000007,   //D:\wl83\ac792\ui_prj\wifi_soundbox_800x480\import\image\icon_02itzp4fqyho\image_4225532_4.png
    GUI_RES_IMAGE_4150274_3_PNG = 0x4B000008,   //D:\wl83\ac792\ui_prj\wifi_soundbox_800x480\import\image\icon_02itzp4fqyho\image_4150274_3.png
    GUI_RES_WIFI_PNG = 0x4B000009,   //D:\wl83\ac792\ui_prj\wifi_soundbox_800x480\import\image\icon_02itzp4fqyho\wifi.png
    GUI_RES_IMAGE_4150274_5_PNG = 0x4B00000A,   //D:\wl83\ac792\ui_prj\wifi_soundbox_800x480\import\image\icon_02itzp4fqyho\image_4150274_5.png
    GUI_RES_IMAGE_4150274_8_PNG = 0x4B00000B,   //D:\wl83\ac792\ui_prj\wifi_soundbox_800x480\import\image\icon_02itzp4fqyho\image_4150274_8.png
    GUI_RES_SHEZHI_PNG = 0x4B00000C,   //D:\wl83\ac792\ui_prj\wifi_soundbox_800x480\import\image\icon_02itzp4fqyho\shezhi.png
    GUI_RES_IMAGE_4161193_1_PNG = 0x4B00000D,   //D:\wl83\ac792\ui_prj\wifi_soundbox_800x480\import\image\icon_02itzp4fqyho\image_4161193_1.png
    GUI_RES_IMAGE_4161390_0_PNG = 0x4B00000E,   //D:\wl83\ac792\ui_prj\wifi_soundbox_800x480\import\image\icon_02itzp4fqyho\image_4161390_0.png
} GUI_RES_ID;

typedef enum {
    RES_EVENT_NEXT_SONG_ID = 0x10000,
    RES_EVENT_PREV_SONG_ID = 0x10001,
    RES_EVENT_PAUSE_OR_PLAY_ID = 0x10002,
    RES_EVENT_MUSIC_VOLUME_CHANGE_ID = 0x10003,
    RES_EVENT_MUSIC_PROCESS_CHANGE_ID = 0x10004,
    RES_EVENT_MUSIC_EQ_MODE_SET_ID = 0x10005,
    RES_EVENT_MUSIC_EQ_GAIN_CHANGE_CUSTOM_ID = 0x10006,
    RES_EVENT_MUSIC_EQ_SAVE_ENABLE_ID = 0x10007,
    RES_EVENT_LYRICS_ALBUM_VIEW_CHANGE_ID = 0x10008,
    SPECTRUM_DRAW_EVENT_CB2_ID = 0x10009,
    SPECTRUM_DELETE_EVENT_CB_ID = 0x1000A,
} RES_EVENT_ID;

extern char *gui_get_res_path(int32_t id);

extern lv_event_cb_t gui_get_event_cb(int32_t id);

extern void res_event_next_song(lv_event_t *e);
extern void res_event_prev_song(lv_event_t *e);
extern void res_event_pause_or_play(lv_event_t *e);
extern void res_event_music_volume_change(lv_event_t *e);
extern void res_event_music_process_change(lv_event_t *e);
extern void res_event_music_eq_mode_set(lv_event_t *e);
extern void res_event_music_eq_gain_change_custom(lv_event_t *e);
extern void res_event_music_eq_save_enable(lv_event_t *e);
extern void res_event_lyrics_album_view_change(lv_event_t *e);
extern void spectrum_draw_event_cb2(lv_event_t *e);
extern void spectrum_delete_event_cb(lv_event_t *e);

#ifdef __cplusplus
}
#endif
#endif

