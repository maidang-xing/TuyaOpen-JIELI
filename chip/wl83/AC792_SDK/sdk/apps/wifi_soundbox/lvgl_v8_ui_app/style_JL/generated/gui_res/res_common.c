/*Generate Code, Do NOT Edit!*/
#include "../gui_guider.h"
#include <stdlib.h>
#include <string.h>
#if LV_USE_GUIBUILDER_SIMULATOR
#include <stdio.h>
#endif

#if !LV_USE_GUIBUILDER_SIMULATOR
#define MAX2(a, b) ((a) > (b) ? (a) : (b))
#define MAX3(a, b, c) MAX2(MAX2(a, b), c)
#define MAX4(a, b, c, d) MAX2(MAX3(a, b, c), d)
#define MAX5(a, b, c, d, e) MAX2(MAX4(a, b, c, d), e)
#define MAX6(a, b, c, d, e, f) MAX2(MAX5(a, b, c, d, e), f)
#define MAX7(a, b, c, d, e, f, g) MAX2(MAX6(a, b, c, d, e, f), g)
#define MAX8(a, b, c, d, e, f, g, h) MAX2(MAX7(a, b, c, d, e, f, g), h)

const char flash_dir[] = "mnt/sdfile/EXT_RESERVED/uipackres/ui/";
const char sd_dir[] = "storage/sd0/C/";
char path_buf[MAX2(sizeof(flash_dir), sizeof(sd_dir)) + 20];
#endif

char *gui_get_res_path(int32_t id)
{
#if LV_USE_GUIBUILDER_SIMULATOR
    switch (id) {
    case GUI_RES_FANGZHENGKAITIJIANTI_1_12_TTF_FLASH:
        return "D:\\wl83\\ac792\\ui_prj\\wifi_soundbox_800x480\\sdk\\ui_res\\flash\\rle\\font\\35000000.rle";
    case GUI_RES_FANGZHENGKAITIJIANTI_1_24_TTF_FLASH:
        return "D:\\wl83\\ac792\\ui_prj\\wifi_soundbox_800x480\\sdk\\ui_res\\flash\\rle\\font\\35000001.rle";
    case GUI_RES_FANGZHENGKAITIJIANTI_1_32_TTF_FLASH:
        return "D:\\wl83\\ac792\\ui_prj\\wifi_soundbox_800x480\\sdk\\ui_res\\flash\\rle\\font\\35000002.rle";
    case GUI_RES_IMAGE_4225207_0_PNG:
        return "A:\\wl83\\ac792\\ui_prj\\wifi_soundbox_800x480\\import\\image\\icon_02itzp4fqyho\\image_4225207_0.png";
    case GUI_RES_IMAGE_4225207_1_PNG:
        return "A:\\wl83\\ac792\\ui_prj\\wifi_soundbox_800x480\\import\\image\\icon_02itzp4fqyho\\image_4225207_1.png";
    case GUI_RES_IMAGE_4225207_2_PNG:
        return "A:\\wl83\\ac792\\ui_prj\\wifi_soundbox_800x480\\import\\image\\icon_02itzp4fqyho\\image_4225207_2.png";
    case GUI_RES_IMAGE_4225207_3_PNG:
        return "A:\\wl83\\ac792\\ui_prj\\wifi_soundbox_800x480\\import\\image\\icon_02itzp4fqyho\\image_4225207_3.png";
    case GUI_RES_IMAGE_4225532_4_PNG:
        return "A:\\wl83\\ac792\\ui_prj\\wifi_soundbox_800x480\\import\\image\\icon_02itzp4fqyho\\image_4225532_4.png";
    case GUI_RES_IMAGE_4150274_3_PNG:
        return "A:\\wl83\\ac792\\ui_prj\\wifi_soundbox_800x480\\import\\image\\icon_02itzp4fqyho\\image_4150274_3.png";
    case GUI_RES_WIFI_PNG:
        return "A:\\wl83\\ac792\\ui_prj\\wifi_soundbox_800x480\\import\\image\\icon_02itzp4fqyho\\wifi.png";
    case GUI_RES_IMAGE_4150274_5_PNG:
        return "A:\\wl83\\ac792\\ui_prj\\wifi_soundbox_800x480\\import\\image\\icon_02itzp4fqyho\\image_4150274_5.png";
    case GUI_RES_IMAGE_4150274_8_PNG:
        return "A:\\wl83\\ac792\\ui_prj\\wifi_soundbox_800x480\\import\\image\\icon_02itzp4fqyho\\image_4150274_8.png";
    case GUI_RES_SHEZHI_PNG:
        return "A:\\wl83\\ac792\\ui_prj\\wifi_soundbox_800x480\\import\\image\\icon_02itzp4fqyho\\shezhi.png";
    case GUI_RES_IMAGE_4161193_1_PNG:
        return "A:\\wl83\\ac792\\ui_prj\\wifi_soundbox_800x480\\import\\image\\icon_02itzp4fqyho\\image_4161193_1.png";
    case GUI_RES_IMAGE_4161390_0_PNG:
        return "A:\\wl83\\ac792\\ui_prj\\wifi_soundbox_800x480\\import\\image\\icon_02itzp4fqyho\\image_4161390_0.png";
    default:
        return NULL;
    }
#else
    memset(path_buf, 0, sizeof(path_buf));
    if (id >= 0x30000000 && id < 0x30100000) {
        snprintf(path_buf, sizeof(path_buf), "%s%x.%s", flash_dir, id, "ttf");
    } else if (id >= 0x30100000 && id < 0x30200000) {
        snprintf(path_buf, sizeof(path_buf), "%s%x.%s", sd_dir, id, "ttf");
    } else if (id >= 0x31000000 && id < 0x31100000) {
        snprintf(path_buf, sizeof(path_buf), "%s%x.%s", flash_dir, id, "woff");
    } else if (id >= 0x31100000 && id < 0x31200000) {
        snprintf(path_buf, sizeof(path_buf), "%s%x.%s", sd_dir, id, "woff");
    } else if (id >= 0x32000000 && id < 0x32100000) {
        snprintf(path_buf, sizeof(path_buf), "%s%x.%s", flash_dir, id, "woff2");
    } else if (id >= 0x32100000 && id < 0x32200000) {
        snprintf(path_buf, sizeof(path_buf), "%s%x.%s", sd_dir, id, "woff2");
    } else if (id >= 0x33000000 && id < 0x33100000) {
        snprintf(path_buf, sizeof(path_buf), "%s%x.%s", flash_dir, id, "otf");
    } else if (id >= 0x33100000 && id < 0x33200000) {
        snprintf(path_buf, sizeof(path_buf), "%s%x.%s", sd_dir, id, "otf");
    } else if (id >= 0x34000000 && id < 0x34100000) {
        snprintf(path_buf, sizeof(path_buf), "%s%x.%s", flash_dir, id, "bin");
    } else if (id >= 0x34100000 && id < 0x34200000) {
        snprintf(path_buf, sizeof(path_buf), "%s%x.%s", sd_dir, id, "bin");
    } else if (id >= 0x35000000 && id < 0x35100000) {
        snprintf(path_buf, sizeof(path_buf), "%s%x.%s", flash_dir, id, "rle");
    } else if (id >= 0x35100000 && id < 0x35200000) {
        snprintf(path_buf, sizeof(path_buf), "%s%x.%s", sd_dir, id, "rle");
    } else if (id >= 0x36000000 && id < 0x36100000) {
        snprintf(path_buf, sizeof(path_buf), "%s%x.%s", flash_dir, id, "fnt");
    } else if (id >= 0x36100000 && id < 0x36200000) {
        snprintf(path_buf, sizeof(path_buf), "%s%x.%s", sd_dir, id, "fnt");
    } else if (id >= 0x37000000 && id < 0x37100000) {
        snprintf(path_buf, sizeof(path_buf), "%s%x.%s", flash_dir, id, "lzw");
    } else if (id >= 0x37100000 && id < 0x37200000) {
        snprintf(path_buf, sizeof(path_buf), "%s%x.%s", sd_dir, id, "lzw");
    } else if (id >= 0x39000000 && id < 0x39100000) {
        snprintf(path_buf, sizeof(path_buf), "%s%x.%s", flash_dir, id, "json");
    } else if (id >= 0x39100000 && id < 0x39200000) {
        snprintf(path_buf, sizeof(path_buf), "%s%x.%s", sd_dir, id, "json");
    } else if (id >= 0x3A000000 && id < 0x3A100000) {
        snprintf(path_buf, sizeof(path_buf), "%s%x.%s", flash_dir, id, "bin");
    } else if (id >= 0x3A100000 && id < 0x3A200000) {
        snprintf(path_buf, sizeof(path_buf), "%s%x.%s", sd_dir, id, "bin");
    } else if (id >= 0x3B000000 && id < 0x3B100000) {
        snprintf(path_buf, sizeof(path_buf), "%s%x.%s", flash_dir, id, "rle");
    } else if (id >= 0x3B100000 && id < 0x3B200000) {
        snprintf(path_buf, sizeof(path_buf), "%s%x.%s", sd_dir, id, "rle");
    } else if (id >= 0x3D000000 && id < 0x3D100000) {
        snprintf(path_buf, sizeof(path_buf), "%s%x.%s", flash_dir, id, "mp4");
    } else if (id >= 0x3D100000 && id < 0x3D200000) {
        snprintf(path_buf, sizeof(path_buf), "%s%x.%s", sd_dir, id, "mp4");
    } else if (id >= 0x3E000000 && id < 0x3E100000) {
        snprintf(path_buf, sizeof(path_buf), "%s%x.%s", flash_dir, id, "avi");
    } else if (id >= 0x3E100000 && id < 0x3E200000) {
        snprintf(path_buf, sizeof(path_buf), "%s%x.%s", sd_dir, id, "avi");
    } else if (id >= 0x3F000000 && id < 0x3F100000) {
        snprintf(path_buf, sizeof(path_buf), "%s%x.%s", flash_dir, id, "bin");
    } else if (id >= 0x3F100000 && id < 0x3F200000) {
        snprintf(path_buf, sizeof(path_buf), "%s%x.%s", sd_dir, id, "bin");
    } else if (id >= 0x40000000 && id < 0x40100000) {
        snprintf(path_buf, sizeof(path_buf), "%s%x.%s", flash_dir, id, "rle");
    } else if (id >= 0x40100000 && id < 0x40200000) {
        snprintf(path_buf, sizeof(path_buf), "%s%x.%s", sd_dir, id, "rle");
    } else if (id >= 0x42000000 && id < 0x42100000) {
        snprintf(path_buf, sizeof(path_buf), "%s%x.%s", flash_dir, id, "gif");
    } else if (id >= 0x42100000 && id < 0x42200000) {
        snprintf(path_buf, sizeof(path_buf), "%s%x.%s", sd_dir, id, "gif");
    } else if (id >= 0x43000000 && id < 0x43100000) {
        snprintf(path_buf, sizeof(path_buf), "%s%x.%s", flash_dir, id, "zip");
    } else if (id >= 0x43100000 && id < 0x43200000) {
        snprintf(path_buf, sizeof(path_buf), "%s%x.%s", sd_dir, id, "zip");
    } else if (id >= 0x46000000 && id < 0x46100000) {
        snprintf(path_buf, sizeof(path_buf), "%s%x.%s", flash_dir, id, "png");
    } else if (id >= 0x46100000 && id < 0x46200000) {
        snprintf(path_buf, sizeof(path_buf), "%s%x.%s", sd_dir, id, "png");
    } else if (id >= 0x47000000 && id < 0x47100000) {
        snprintf(path_buf, sizeof(path_buf), "%s%x.%s", flash_dir, id, "jpg");
    } else if (id >= 0x47100000 && id < 0x47200000) {
        snprintf(path_buf, sizeof(path_buf), "%s%x.%s", sd_dir, id, "jpg");
    } else if (id >= 0x48000000 && id < 0x48100000) {
        snprintf(path_buf, sizeof(path_buf), "%s%x.%s", flash_dir, id, "jpeg");
    } else if (id >= 0x48100000 && id < 0x48200000) {
        snprintf(path_buf, sizeof(path_buf), "%s%x.%s", sd_dir, id, "jpeg");
    } else if (id >= 0x49000000 && id < 0x49100000) {
        snprintf(path_buf, sizeof(path_buf), "%s%x.%s", flash_dir, id, "bmp");
    } else if (id >= 0x49100000 && id < 0x49200000) {
        snprintf(path_buf, sizeof(path_buf), "%s%x.%s", sd_dir, id, "bmp");
    } else if (id >= 0x4A000000 && id < 0x4A100000) {
        snprintf(path_buf, sizeof(path_buf), "%s%x.%s", flash_dir, id, "svg");
    } else if (id >= 0x4A100000 && id < 0x4A200000) {
        snprintf(path_buf, sizeof(path_buf), "%s%x.%s", sd_dir, id, "svg");
    } else if (id >= 0x4B000000 && id < 0x4B100000) {
        snprintf(path_buf, sizeof(path_buf), "%s%x.%s", flash_dir, id, "zip");
    } else if (id >= 0x4B100000 && id < 0x4B200000) {
        snprintf(path_buf, sizeof(path_buf), "%s%x.%s", sd_dir, id, "zip");
    } else {
        return NULL;
    }
    return path_buf;
#endif
}

lv_event_cb_t gui_get_event_cb(int32_t id)
{
    switch (id) {
    case RES_EVENT_NEXT_SONG_ID:
        return res_event_next_song;
    case RES_EVENT_PREV_SONG_ID:
        return res_event_prev_song;
    case RES_EVENT_PAUSE_OR_PLAY_ID:
        return res_event_pause_or_play;
    case RES_EVENT_MUSIC_VOLUME_CHANGE_ID:
        return res_event_music_volume_change;
    case RES_EVENT_MUSIC_PROCESS_CHANGE_ID:
        return res_event_music_process_change;
    case RES_EVENT_MUSIC_EQ_MODE_SET_ID:
        return res_event_music_eq_mode_set;
    case RES_EVENT_MUSIC_EQ_GAIN_CHANGE_CUSTOM_ID:
        return res_event_music_eq_gain_change_custom;
    case RES_EVENT_MUSIC_EQ_SAVE_ENABLE_ID:
        return res_event_music_eq_save_enable;
    case RES_EVENT_LYRICS_ALBUM_VIEW_CHANGE_ID:
        return res_event_lyrics_album_view_change;
    case SPECTRUM_DRAW_EVENT_CB2_ID:
        return spectrum_draw_event_cb2;
    case SPECTRUM_DELETE_EVENT_CB_ID:
        return spectrum_delete_event_cb;
    default:
        return NULL;
    }
}
GUI_WEAK void res_event_next_song(lv_event_t *e)
{
}
GUI_WEAK void res_event_prev_song(lv_event_t *e)
{
}
GUI_WEAK void res_event_pause_or_play(lv_event_t *e)
{
}
GUI_WEAK void res_event_music_volume_change(lv_event_t *e)
{
}
GUI_WEAK void res_event_music_process_change(lv_event_t *e)
{
}
GUI_WEAK void res_event_music_eq_mode_set(lv_event_t *e)
{
}
GUI_WEAK void res_event_music_eq_gain_change_custom(lv_event_t *e)
{
}
GUI_WEAK void res_event_music_eq_save_enable(lv_event_t *e)
{
}
GUI_WEAK void res_event_lyrics_album_view_change(lv_event_t *e)
{
}
GUI_WEAK void spectrum_draw_event_cb2(lv_event_t *e)
{
}
GUI_WEAK void spectrum_delete_event_cb(lv_event_t *e)
{
}

