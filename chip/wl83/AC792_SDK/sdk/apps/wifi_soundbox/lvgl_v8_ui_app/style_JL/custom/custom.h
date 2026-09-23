
#ifndef __CUSTOM_H_
#define __CUSTOM_H_
#ifdef __cplusplus
extern "C" {
#endif

#include "../generated/gui_guider.h"
#if !LV_USE_GUIBUILDER_SIMULATOR
#include "app_msg.h"
#include "app_core.h"
#include "app_config.h"
#include "ui.h"
#include "fs/fs.h"
#include "btstack/avctp_user.h"
#include "asm/jpeg_codec.h"
#include "asm/hwi.h"
#include "system/includes.h"
#include "os/os_api.h"
#include "video_ioctl.h"
#include "video.h"
#include "yuv_to_rgb.h"
#include "yuv_soft_scalling.h"
#include "ui_action_song_info.h"
#endif
#define CONFIG_FONT_TTF_NAME                "30100000.ttf"
#define CONFIG_FONT_TTF_PATH                CONFIG_ROOT_PATH\
                                            CONFIG_FONT_TTF_NAME
#define MAX_SPECTRUM_SECTION_NUM    32
#define USE_SPECTRUM_SECTION_NUM    16

typedef struct {
    uint8_t r;
    uint8_t g;
    uint8_t b;
} rgb_color_t;

void custom_init(lv_ui *ui);
//²¥·ÅÆ÷
void ui_music_pause_handler(void);
void ui_music_on_handler(void);
void ui_music_tol_time_handler(u32 tol_time);
void ui_music_cur_time_handler(u32  cur_time);
void ui_music_artist_handler(char *song_info);
void ui_music_album_pic_handler(void);
void ui_music_volume_handler(int volume);
void ui_music_process_handler(u32 cur_time);
void ui_music_lyrics_handler(char *song_lyrics);

//×¨¼­jpegÕÕÆ¬½âÂëÆ÷
int ui_action_jpeg_decoder(u8 **buf, u32 *length, rgb_color_t *avg_color, u16 *rgb_width, u16 *rgb_length);

//ÆµÆ×
void ui_music_draw_spectrum(void);
void ui_music_spectrum_handler(float db_data[2][MAX_SPECTRUM_SECTION_NUM]);
void ui_music_update_spectrum_with_magnitude(void);
void ui_music_spectrum_set_bg_avg_color(uint8_t r, uint8_t g, uint8_t b);
#ifdef __cplusplus
}
#endif
#endif /* EVENT_CB_H_ */
