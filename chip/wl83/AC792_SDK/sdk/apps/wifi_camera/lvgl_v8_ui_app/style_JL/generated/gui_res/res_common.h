#include "app_config.h"
#ifdef CONFIG_UI_STYLE_JL_ENABLE
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
    GUI_RES_MONTSERRATMEDIUM_12_TTF = 0x35000000,   //E:\1111\ac792\ui_prj\Application11\sdk\ui_res\flash\rle\font\35000000.rle
    GUI_RES_FANGZHENGKAITIJIANTI_1_28_TTF = 0x35000001,   //E:\1111\ac792\ui_prj\Application11\sdk\ui_res\flash\rle\font\35000001.rle
    GUI_RES_FANGZHENGKAITIJIANTI_1_19_TTF = 0x35000002,   //E:\1111\ac792\ui_prj\Application11\sdk\ui_res\flash\rle\font\35000002.rle
    GUI_RES_FANGZHENGKAITIJIANTI_1_24_TTF = 0x35000003,   //E:\1111\ac792\ui_prj\Application11\sdk\ui_res\flash\rle\font\35000003.rle
    GUI_RES_FANGZHENGKAITIJIANTI_1_32_TTF = 0x35000004,   //E:\1111\ac792\ui_prj\Application11\sdk\ui_res\flash\rle\font\35000004.rle
    GUI_RES_FANGZHENGKAITIJIANTI_1_16_TTF = 0x35000005,   //E:\1111\ac792\ui_prj\Application11\sdk\ui_res\flash\rle\font\35000005.rle
    GUI_RES_MONTSERRATMEDIUM_18_TTF = 0x35000006,   //E:\1111\ac792\ui_prj\Application11\sdk\ui_res\flash\rle\font\35000006.rle
    GUI_RES_MONTSERRATMEDIUM_20_TTF = 0x35000007,   //E:\1111\ac792\ui_prj\Application11\sdk\ui_res\flash\rle\font\35000007.rle
    GUI_RES_FANGZHENGKAITIJIANTI_1_54_TTF = 0x35000008,   //E:\1111\ac792\ui_prj\Application11\sdk\ui_res\flash\rle\font\35000008.rle
    GUI_RES_FANGZHENGKAITIJIANTI_1_48_TTF = 0x35000009,   //E:\1111\ac792\ui_prj\Application11\sdk\ui_res\flash\rle\font\35000009.rle
    GUI_RES_FANGZHENGKAITIJIANTI_1_20_TTF = 0x3500000A,   //E:\1111\ac792\ui_prj\Application11\sdk\ui_res\flash\rle\font\3500000a.rle
    GUI_RES_MONTSERRATMEDIUM_24_TTF = 0x3500000B,   //E:\1111\ac792\ui_prj\Application11\sdk\ui_res\flash\rle\font\3500000b.rle
    GUI_RES_MONTSERRATMEDIUM_48_TTF = 0x3500000C,   //E:\1111\ac792\ui_prj\Application11\sdk\ui_res\flash\rle\font\3500000c.rle
    GUI_RES_MONTSERRATMEDIUM_49_TTF = 0x3500000D,   //E:\1111\ac792\ui_prj\Application11\sdk\ui_res\flash\rle\font\3500000d.rle
    GUI_RES_MONTSERRATMEDIUM_32_TTF = 0x3500000E,   //E:\1111\ac792\ui_prj\Application11\sdk\ui_res\flash\rle\font\3500000e.rle
    GUI_RES_FANGZHENGKAITIJIANTI_1_14_TTF = 0x3500000F,   //E:\1111\ac792\ui_prj\Application11\sdk\ui_res\flash\rle\font\3500000f.rle
    GUI_RES_MONTSERRATMEDIUM_160_TTF = 0x35000010,   //E:\1111\ac792\ui_prj\Application11\sdk\ui_res\flash\rle\font\35000010.rle
    GUI_RES_FANGZHENGKAITIJIANTI_1_26_TTF = 0x35000011,   //E:\1111\ac792\ui_prj\Application11\sdk\ui_res\flash\rle\font\35000011.rle
    GUI_RES_MONTSERRATMEDIUM_22_TTF = 0x35000012,   //E:\1111\ac792\ui_prj\Application11\sdk\ui_res\flash\rle\font\35000012.rle
    GUI_RES_MONTSERRATMEDIUM_16_TTF = 0x35000013,   //E:\1111\ac792\ui_prj\Application11\sdk\ui_res\flash\rle\font\35000013.rle
    GUI_RES_FANGSONG_16_TTF = 0x35000014,   //E:\1111\ac792\ui_prj\Application11\sdk\ui_res\flash\rle\font\35000014.rle
    GUI_RES_FANGSONG_24_TTF = 0x35000015,   //E:\1111\ac792\ui_prj\Application11\sdk\ui_res\flash\rle\font\35000015.rle
    GUI_RES_FANGZHENGKAITIJIANTI_1_22_TTF = 0x35000016,   //E:\1111\ac792\ui_prj\Application11\sdk\ui_res\flash\rle\font\35000016.rle
    GUI_RES_TIMESNEWROMANPSMT_16_TTF = 0x35000017,   //E:\1111\ac792\ui_prj\Application11\sdk\ui_res\flash\rle\font\35000017.rle
    GUI_RES_TIMESNEWROMANPSMT_24_TTF = 0x35000018,   //E:\1111\ac792\ui_prj\Application11\sdk\ui_res\flash\rle\font\35000018.rle
    GUI_RES_TIMESNEWROMANPSMT_48_TTF = 0x35000019,   //E:\1111\ac792\ui_prj\Application11\sdk\ui_res\flash\rle\font\35000019.rle
    GUI_RES_TIMESNEWROMANPSMT_22_TTF = 0x3500001A,   //E:\1111\ac792\ui_prj\Application11\sdk\ui_res\flash\rle\font\3500001a.rle
    GUI_RES_SEGOEUI_16_TTF = 0x3500001B,   //E:\1111\ac792\ui_prj\Application11\sdk\ui_res\flash\rle\font\3500001b.rle
    GUI_RES_SEGOEUI_24_TTF = 0x3500001C,   //E:\1111\ac792\ui_prj\Application11\sdk\ui_res\flash\rle\font\3500001c.rle
    GUI_RES_LEELAWADEEUI_16_TTF = 0x3500001D,   //E:\1111\ac792\ui_prj\Application11\sdk\ui_res\flash\rle\font\3500001d.rle
    GUI_RES_LEELAWADEEUI_24_TTF = 0x3500001E,   //E:\1111\ac792\ui_prj\Application11\sdk\ui_res\flash\rle\font\3500001e.rle
    GUI_RES_MALGUNGOTHIC_16_TTF = 0x3500001F,   //E:\1111\ac792\ui_prj\Application11\sdk\ui_res\flash\rle\font\3500001f.rle
    GUI_RES_MALGUNGOTHIC_24_TTF = 0x35000020,   //E:\1111\ac792\ui_prj\Application11\sdk\ui_res\flash\rle\font\35000020.rle
    GUI_RES_MS_GOTHIC_16_TTF = 0x35000021,   //E:\1111\ac792\ui_prj\Application11\sdk\ui_res\flash\rle\font\35000021.rle
    GUI_RES_CALIBRI_16_TTF = 0x35000022,   //E:\1111\ac792\ui_prj\Application11\sdk\ui_res\flash\rle\font\35000022.rle
    GUI_RES_CALIBRI_24_TTF = 0x35000023,   //E:\1111\ac792\ui_prj\Application11\sdk\ui_res\flash\rle\font\35000023.rle

    GUI_RES_S_PC_PNG = 0x4B000024,   //E:\1111\ac792\ui_prj\Application11\import\image\video_page\USB\s_PC.png
    GUI_RES_S_MASS_PNG = 0x4B000025,   //E:\1111\ac792\ui_prj\Application11\import\image\video_page\USB\s_MASS.png
    GUI_RES_VIDEO_PNG = 0x4B000026,   //E:\1111\ac792\ui_prj\Application11\import\image\video_page\USB\VIDEO.png
    GUI_RES_VIDEO_ON_PNG = 0x4B000027,   //E:\1111\ac792\ui_prj\Application11\import\image\video_page\USB\VIDEO_on.png
    GUI_RES_MASS_PNG = 0x4B000028,   //E:\1111\ac792\ui_prj\Application11\import\image\video_page\USB\MASS.png
    GUI_RES_MASS_ON_PNG = 0x4B000029,   //E:\1111\ac792\ui_prj\Application11\import\image\video_page\USB\MASS_on.png
    GUI_RES_PCCAM_PNG = 0x4B00002A,   //E:\1111\ac792\ui_prj\Application11\import\image\video_page\USB\PCCAM.png
    GUI_RES_PCCAM_ON_PNG = 0x4B00002B,   //E:\1111\ac792\ui_prj\Application11\import\image\video_page\USB\PCCAM_on.png
    GUI_RES_VIDEO_BUTTO_PNG = 0x4B00002C,   //E:\1111\ac792\ui_prj\Application11\import\image\video_page\video_butto.png
    GUI_RES_VIDEO_BUTTO_FLASH1_ON_PNG = 0x4B00002D,   //E:\1111\ac792\ui_prj\Application11\import\image\video_page\video_butto_flash1_on.png
    GUI_RES_VIDEO_BUTTO_FLASH2_PNG = 0x4B00002E,   //E:\1111\ac792\ui_prj\Application11\import\image\video_page\video_butto_flash2.png
    GUI_RES_VIDEO_BUTTO_FLASH2_ON_PNG = 0x4B00002F,   //E:\1111\ac792\ui_prj\Application11\import\image\video_page\video_butto_flash2_on.png
    GUI_RES_CYCLIC_VIDEO_CLOSE_PNG = 0x4B000030,   //E:\1111\ac792\ui_prj\Application11\import\image\video_page\cyclic_video_close.png
    GUI_RES_GRAVITY_SENSOR_LOW_PNG = 0x4B000031,   //E:\1111\ac792\ui_prj\Application11\import\image\video_page\gravity_sensor_low.png
    GUI_RES_SOUND_CLOSE_PNG = 0x4B000032,   //E:\1111\ac792\ui_prj\Application11\import\image\video_page\sound_close.png
    GUI_RES_STOPPING_MONITOR_PNG = 0x4B000033,   //E:\1111\ac792\ui_prj\Application11\import\image\video_page\stopping_monitor.png
    GUI_RES_CHECK_SPORT_PNG = 0x4B000034,   //E:\1111\ac792\ui_prj\Application11\import\image\video_page\check_sport.png
    GUI_RES_SD_PNG = 0x4B000035,   //E:\1111\ac792\ui_prj\Application11\import\image\video_page\SD.png
    GUI_RES_LOCK_PNG = 0x4B000036,   //E:\1111\ac792\ui_prj\Application11\import\image\video_page\lock.png
    GUI_RES_INTERVAL_VIDEO_CLOSE_PNG = 0x4B000037,   //E:\1111\ac792\ui_prj\Application11\import\image\video_page\interval_video_close.png
    GUI_RES_DISCONNECT_PNG = 0x4B000038,   //E:\1111\ac792\ui_prj\Application11\import\image\video_page\menu_icon\disconnect.png
    GUI_RES_FULL_PNG = 0x4B000039,   //E:\1111\ac792\ui_prj\Application11\import\image\video_page\battery\full.png
    GUI_RES_SETTING_PNG = 0x4B00003A,   //E:\1111\ac792\ui_prj\Application11\import\image\video_page\left_tools\setting.png
    GUI_RES_CAMERA_PNG = 0x4B00003B,   //E:\1111\ac792\ui_prj\Application11\import\image\video_page\left_tools\camera.png
    GUI_RES_HOME_PNG = 0x4B00003C,   //E:\1111\ac792\ui_prj\Application11\import\image\video_page\left_tools\home.png
    GUI_RES_BTN_LOCK_PNG = 0x4B00003D,   //E:\1111\ac792\ui_prj\Application11\import\image\video_page\btn_lock.png
    GUI_RES_BTN_LOCK_ON_PNG = 0x4B00003E,   //E:\1111\ac792\ui_prj\Application11\import\image\video_page\btn_lock_on.png
    GUI_RES_SWITCH_PNG = 0x4B00003F,   //E:\1111\ac792\ui_prj\Application11\import\image\video_page\switch.png
    GUI_RES_SWITCH_ON_PNG = 0x4B000040,   //E:\1111\ac792\ui_prj\Application11\import\image\video_page\switch_on.png
    GUI_RES_RESOLUTION_RATIO_PNG = 0x4B000041,   //E:\1111\ac792\ui_prj\Application11\import\image\video_page\menu_icon\resolution_ratio.png
    GUI_RES_DOUBLE_VIDEO_PNG = 0x4B000042,   //E:\1111\ac792\ui_prj\Application11\import\image\video_page\menu_icon\double_video.png
    GUI_RES_CYCLIC_VIDEO_PNG = 0x4B000043,   //E:\1111\ac792\ui_prj\Application11\import\image\video_page\menu_icon\cyclic_video.png
    GUI_RES_INTERVAL_VIDEO_PNG = 0x4B000044,   //E:\1111\ac792\ui_prj\Application11\import\image\video_page\menu_icon\interval_video.png
    GUI_RES_HDR_PNG = 0x4B000045,   //E:\1111\ac792\ui_prj\Application11\import\image\video_page\menu_icon\HDR.png
    GUI_RES_EXPOSURE_PNG = 0x4B000046,   //E:\1111\ac792\ui_prj\Application11\import\image\video_page\menu_icon\exposure.png
    GUI_RES_CHECK_SPORT_1_PNG = 0x4B000047,   //E:\1111\ac792\ui_prj\Application11\import\image\video_page\menu_icon\check_sport.png
    GUI_RES_DATE_PNG = 0x4B000048,   //E:\1111\ac792\ui_prj\Application11\import\image\video_page\menu_icon\date.png
    GUI_RES_GRAVITY_SENSOR_PNG = 0x4B000049,   //E:\1111\ac792\ui_prj\Application11\import\image\video_page\menu_icon\gravity_sensor.png
    GUI_RES_SOUND_PNG = 0x4B00004A,   //E:\1111\ac792\ui_prj\Application11\import\image\video_page\menu_icon\sound.png
    GUI_RES_STOPPING_MONITOR_1_PNG = 0x4B00004B,   //E:\1111\ac792\ui_prj\Application11\import\image\video_page\menu_icon\stopping_monitor.png
    GUI_RES_CAR_NUM_PNG = 0x4B00004C,   //E:\1111\ac792\ui_prj\Application11\import\image\video_page\menu_icon\car_num.png
    GUI_RES_HEADLIGHT_PNG = 0x4B00004D,   //E:\1111\ac792\ui_prj\Application11\import\image\video_page\headlight.png
    GUI_RES_VIDEO_1_PNG = 0x4B00004E,   //E:\1111\ac792\ui_prj\Application11\import\image\video_page\main_page\video.png
    GUI_RES_VIDEO__ON_PNG = 0x4B00004F,   //E:\1111\ac792\ui_prj\Application11\import\image\video_page\main_page\video__on.png
    GUI_RES_FILE_PNG = 0x4B000050,   //E:\1111\ac792\ui_prj\Application11\import\image\video_page\main_page\file.png
    GUI_RES_FILE_ON_PNG = 0x4B000051,   //E:\1111\ac792\ui_prj\Application11\import\image\video_page\main_page\file_on.png
    GUI_RES_SETTING_1_PNG = 0x4B000052,   //E:\1111\ac792\ui_prj\Application11\import\image\video_page\main_page\setting.png
    GUI_RES_SETTING_ON_PNG = 0x4B000053,   //E:\1111\ac792\ui_prj\Application11\import\image\video_page\main_page\setting_on.png
    GUI_RES_POP_UP_WINDOW_PNG = 0x4B000054,   //E:\1111\ac792\ui_prj\Application11\import\image\video_page\pop_up_window.png
    GUI_RES_FLIG_ON_PNG = 0x4B000055,   //E:\1111\ac792\ui_prj\Application11\import\image\video_page\flig_on.png
    GUI_RES_ASTERN_PNG = 0x4B000056,   //E:\1111\ac792\ui_prj\Application11\import\image\video_page\astern.png
    GUI_RES_LCD_OFF_PNG = 0x4B000057,   //E:\1111\ac792\ui_prj\Application11\import\image\video_page\sys_setting\icon\lcd_off.png
    GUI_RES_AUTO_OFF_PNG = 0x4B000058,   //E:\1111\ac792\ui_prj\Application11\import\image\video_page\sys_setting\icon\auto_off.png
    GUI_RES_FREQUENCY_PNG = 0x4B000059,   //E:\1111\ac792\ui_prj\Application11\import\image\video_page\sys_setting\icon\frequency.png
    GUI_RES_VOICE_PNG = 0x4B00005A,   //E:\1111\ac792\ui_prj\Application11\import\image\video_page\sys_setting\icon\voice.png
    GUI_RES_LANGUAGES_PNG = 0x4B00005B,   //E:\1111\ac792\ui_prj\Application11\import\image\video_page\sys_setting\icon\languages.png
    GUI_RES_SOFTWARE_PNG = 0x4B00005C,   //E:\1111\ac792\ui_prj\Application11\import\image\video_page\menu_icon\software.png
    GUI_RES_CAR_NUM_1_PNG = 0x4B00005D,   //E:\1111\ac792\ui_prj\Application11\import\image\video_page\sys_setting\icon\car_num.png
    GUI_RES_LANE_PNG = 0x4B00005E,   //E:\1111\ac792\ui_prj\Application11\import\image\video_page\sys_setting\icon\lane.png
    GUI_RES_FLIG_PNG = 0x4B00005F,   //E:\1111\ac792\ui_prj\Application11\import\image\video_page\sys_setting\icon\flig.png
    GUI_RES_FORMAT_PNG = 0x4B000060,   //E:\1111\ac792\ui_prj\Application11\import\image\video_page\sys_setting\icon\format.png
    GUI_RES_RESET_PNG = 0x4B000061,   //E:\1111\ac792\ui_prj\Application11\import\image\video_page\sys_setting\icon\reset.png
    GUI_RES_DATE_1_PNG = 0x4B000062,   //E:\1111\ac792\ui_prj\Application11\import\image\video_page\sys_setting\icon\date.png
    GUI_RES_VIDEO_2_PNG = 0x4B000063,   //E:\1111\ac792\ui_prj\Application11\import\image\video_page\sys_setting\left_tools\video.png
    GUI_RES_FILES_PNG = 0x4B000064,   //E:\1111\ac792\ui_prj\Application11\import\image\video_page\sys_setting\left_tools\FILES.png
    GUI_RES_PHOTO_BUTTON_PNG = 0x4B000065,   //E:\1111\ac792\ui_prj\Application11\import\image\video_page\photo_button.png
    GUI_RES_PHOTO_BUTTON_ON_PNG = 0x4B000066,   //E:\1111\ac792\ui_prj\Application11\import\image\video_page\photo_button_on.png
    GUI_RES_TIMING_PHOTO_2_PNG = 0x4B000067,   //E:\1111\ac792\ui_prj\Application11\import\image\video_page\timing_photo_2.png
    GUI_RES_CONTINUOUS_PNG = 0x4B000068,   //E:\1111\ac792\ui_prj\Application11\import\image\video_page\continuous.png
    GUI_RES_HAND_SHAKE_PNG = 0x4B000069,   //E:\1111\ac792\ui_prj\Application11\import\image\video_page\hand_shake.png
    GUI_RES_VIDEO_3_PNG = 0x4B00006A,   //E:\1111\ac792\ui_prj\Application11\import\image\video_page\left_tools\video.png
    GUI_RES_TIMING_PHOTO_PNG = 0x4B00006B,   //E:\1111\ac792\ui_prj\Application11\import\image\video_page\menu_icon\timing_photo.png
    GUI_RES_CONTINUOUS_PHOTO_PNG = 0x4B00006C,   //E:\1111\ac792\ui_prj\Application11\import\image\video_page\menu_icon\continuous_photo.png
    GUI_RES_PHOTO_QUALITY_PNG = 0x4B00006D,   //E:\1111\ac792\ui_prj\Application11\import\image\video_page\menu_icon\photo_quality.png
    GUI_RES_ACUITY_PNG = 0x4B00006E,   //E:\1111\ac792\ui_prj\Application11\import\image\video_page\menu_icon\acuity.png
    GUI_RES_AWB_PNG = 0x4B00006F,   //E:\1111\ac792\ui_prj\Application11\import\image\video_page\menu_icon\AWB.png
    GUI_RES_COLOR_PNG = 0x4B000070,   //E:\1111\ac792\ui_prj\Application11\import\image\video_page\menu_icon\color.png
    GUI_RES_ISO_PNG = 0x4B000071,   //E:\1111\ac792\ui_prj\Application11\import\image\video_page\menu_icon\ISO.png
    GUI_RES_HAND_SHAKE_1_PNG = 0x4B000072,   //E:\1111\ac792\ui_prj\Application11\import\image\video_page\menu_icon\hand_shake.png
    GUI_RES_QUICK_SCAN_PNG = 0x4B000073,   //E:\1111\ac792\ui_prj\Application11\import\image\video_page\menu_icon\quick_scan.png
    GUI_RES_HIGH_PNG = 0x4B000074,   //E:\1111\ac792\ui_prj\Application11\import\image\video_page\high.png
    GUI_RES_AWB_1_PNG = 0x4B000075,   //E:\1111\ac792\ui_prj\Application11\import\image\video_page\awb.png
    GUI_RES_VIDEO_PLAY_PNG = 0x4B000076,   //E:\1111\ac792\ui_prj\Application11\import\image\video_play.png
    GUI_RES_VIDEO_PAUSE_PNG = 0x4B000077,   //E:\1111\ac792\ui_prj\Application11\import\image\video_pause.png
    GUI_RES_VOLUMELOUDER_SOLID_1_PNG = 0x4B000078,   //E:\1111\ac792\ui_prj\Application11\import\image\volumeLouder_solid_1.png
    GUI_RES_VOLUMEMUTE_SOLID_1_PNG = 0x4B000079,   //E:\1111\ac792\ui_prj\Application11\import\image\volumeMute_solid_1.png
    GUI_RES_PHOTO_PNG = 0x4B00007A,   //E:\1111\ac792\ui_prj\Application11\import\image\PHOTO.png
    GUI_RES_PHOTO_ON_PNG = 0x4B00007B,   //E:\1111\ac792\ui_prj\Application11\import\image\photo_on.png
    GUI_RES_RETURN_PNG = 0x4B00007C,   //E:\1111\ac792\ui_prj\Application11\import\image\RETURN.png
    GUI_RES_RETURN_ON_PNG = 0x4B00007D,   //E:\1111\ac792\ui_prj\Application11\import\image\return_on.png
    GUI_RES_SKIP_PREVIOUS_PNG = 0x4B00007E,   //E:\1111\ac792\ui_prj\Application11\import\image\skip_previous.png
    GUI_RES_SKIP_NEXT_PNG = 0x4B00007F,   //E:\1111\ac792\ui_prj\Application11\import\image\skip_next.png
    GUI_RES_UP_PNG = 0x4B000080,   //E:\1111\ac792\ui_prj\Application11\import\image\up.png
    GUI_RES_DOWN_PNG = 0x4B000081,   //E:\1111\ac792\ui_prj\Application11\import\image\down.png
    GUI_RES_EDIT_PNG = 0x4B000082,   //E:\1111\ac792\ui_prj\Application11\import\image\EDIT.png
    GUI_RES_EDITOR_ON_PNG = 0x4B000083,   //E:\1111\ac792\ui_prj\Application11\import\image\editor_on.png
    GUI_RES_LOCK_1_PNG = 0x4B000084,   //E:\1111\ac792\ui_prj\Application11\import\image\LOCK.png
    GUI_RES_LOCK_ON_PNG = 0x4B000085,   //E:\1111\ac792\ui_prj\Application11\import\image\lock_on.png
    GUI_RES_HOME_1_PNG = 0x4B000086,   //E:\1111\ac792\ui_prj\Application11\import\image\HOME.png
    GUI_RES_HOME_ON_PNG = 0x4B000087,   //E:\1111\ac792\ui_prj\Application11\import\image\home_on.png
    GUI_RES_DELETE_PNG = 0x4B000088,   //E:\1111\ac792\ui_prj\Application11\import\image\DELETE.png
    GUI_RES_DELETE_ON_PNG = 0x4B000089,   //E:\1111\ac792\ui_prj\Application11\import\image\delete_on.png
} GUI_RES_ID;

typedef enum {
    RES_0 = 0x7400008A,   //E:\1111\ac792\ui_prj\Application11\import\image\video_page\battery\0.png 48x48
    RES_1 = 0x7400008B,   //E:\1111\ac792\ui_prj\Application11\import\image\video_page\battery\1.png 48x48
    RES_2 = 0x7400008C,   //E:\1111\ac792\ui_prj\Application11\import\image\video_page\battery\2.png 48x48
    RES_3 = 0x7400008D,   //E:\1111\ac792\ui_prj\Application11\import\image\video_page\battery\3.png 48x48
    RES_CHARGING = 0x7400008E,   //E:\1111\ac792\ui_prj\Application11\import\image\video_page\battery\charging.png 48x48
    RES_FULL = 0x7400008F,   //E:\1111\ac792\ui_prj\Application11\import\image\video_page\battery\full.png 48x48
    RES_CYCLIC_VIDEO_3 = 0x74000090,   //E:\1111\ac792\ui_prj\Application11\import\image\video_page\cyclic_video_3.png 48x48
    RES_CYCLIC_VIDEO_10 = 0x74000091,   //E:\1111\ac792\ui_prj\Application11\import\image\video_page\cyclic_video_10.png 48x48
    RES_CYCLIC_VIDEO_CLOSE = 0x74000092,   //E:\1111\ac792\ui_prj\Application11\import\image\video_page\cyclic_video_close.png 48x48
    RES_GRAVITY_SENSOR_LOW = 0x74000093,   //E:\1111\ac792\ui_prj\Application11\import\image\video_page\gravity_sensor_low.png 48x48
    RES_GRAVITY_SENSOR_MIDLLER = 0x74000094,   //E:\1111\ac792\ui_prj\Application11\import\image\video_page\gravity_sensor_midller.png 48x48
    RES_GRAVITY_SENSOR_HIGH = 0x74000095,   //E:\1111\ac792\ui_prj\Application11\import\image\video_page\gravity_sensor_high.png 48x48
    RES_INTERVAL_VIDEO_CLOSE = 0x74000096,   //E:\1111\ac792\ui_prj\Application11\import\image\video_page\interval_video_close.png 48x48
    RES_INTERVAL_VIDEO_500 = 0x74000097,   //E:\1111\ac792\ui_prj\Application11\import\image\video_page\interval_video_500.png 48x48
    RES_INTERVAL_VIDEO_200 = 0x74000098,   //E:\1111\ac792\ui_prj\Application11\import\image\video_page\interval_video_200.png 48x48
    RES_INTERVAL_VIDEO_100 = 0x74000099,   //E:\1111\ac792\ui_prj\Application11\import\image\video_page\interval_video_100.png 48x48
    RES_SD = 0x7400009A,   //E:\1111\ac792\ui_prj\Application11\import\image\video_page\SD.png 45x45
    RES_SD_CLOSE = 0x7400009B,   //E:\1111\ac792\ui_prj\Application11\import\image\video_page\SD_close.png 45x45
    RES_SOUND = 0x7400009C,   //E:\1111\ac792\ui_prj\Application11\import\image\video_page\sound.png 48x48
    RES_SOUND_CLOSE = 0x7400009D,   //E:\1111\ac792\ui_prj\Application11\import\image\video_page\sound_close.png 48x48
    RES_EXPOSURE = 0x7400009E,   //E:\1111\ac792\ui_prj\Application11\import\image\video_page\menu_icon\exposure.png 80x80
    RES_DOUBLE_VIDEO = 0x7400009F,   //E:\1111\ac792\ui_prj\Application11\import\image\video_page\menu_icon\double_video.png 80x80
    RES_DATE = 0x740000A0,   //E:\1111\ac792\ui_prj\Application11\import\image\video_page\menu_icon\date.png 80x80
    RES_CYCLIC_VIDEO = 0x740000A1,   //E:\1111\ac792\ui_prj\Application11\import\image\video_page\menu_icon\cyclic_video.png 80x80
    RES_CHECK_SPORT = 0x740000A2,   //E:\1111\ac792\ui_prj\Application11\import\image\video_page\menu_icon\check_sport.png 80x80
    RES_CAR_NUM = 0x740000A3,   //E:\1111\ac792\ui_prj\Application11\import\image\video_page\menu_icon\car_num.png 80x80
    RES_GRAVITY_SENSOR = 0x740000A4,   //E:\1111\ac792\ui_prj\Application11\import\image\video_page\menu_icon\gravity_sensor.png 80x80
    RES_HDR = 0x740000A5,   //E:\1111\ac792\ui_prj\Application11\import\image\video_page\menu_icon\HDR.png 80x80
    RES_INTERVAL_VIDEO = 0x740000A6,   //E:\1111\ac792\ui_prj\Application11\import\image\video_page\menu_icon\interval_video.png 80x80
    RES_RESOLUTION_RATIO = 0x740000A7,   //E:\1111\ac792\ui_prj\Application11\import\image\video_page\menu_icon\resolution_ratio.png 80x80
    RES_SOUND_1 = 0x740000A8,   //E:\1111\ac792\ui_prj\Application11\import\image\video_page\menu_icon\sound.png 80x80
    RES_STOPPING_MONITOR = 0x740000A9,   //E:\1111\ac792\ui_prj\Application11\import\image\video_page\menu_icon\stopping_monitor.png 80x80
    RES_AUTO_OFF = 0x740000AA,   //E:\1111\ac792\ui_prj\Application11\import\image\video_page\sys_setting\icon\auto_off.png 80x80
    RES_CAR_NUM_1 = 0x740000AB,   //E:\1111\ac792\ui_prj\Application11\import\image\video_page\sys_setting\icon\car_num.png 80x80
    RES_FLIG = 0x740000AC,   //E:\1111\ac792\ui_prj\Application11\import\image\video_page\sys_setting\icon\flig.png 80x80
    RES_FORMAT = 0x740000AD,   //E:\1111\ac792\ui_prj\Application11\import\image\video_page\sys_setting\icon\format.png 80x80
    RES_FREQUENCY = 0x740000AE,   //E:\1111\ac792\ui_prj\Application11\import\image\video_page\sys_setting\icon\frequency.png 80x80
    RES_LANE = 0x740000AF,   //E:\1111\ac792\ui_prj\Application11\import\image\video_page\sys_setting\icon\lane.png 80x80
    RES_LANGUAGES = 0x740000B0,   //E:\1111\ac792\ui_prj\Application11\import\image\video_page\sys_setting\icon\languages.png 80x80
    RES_LCD_OFF = 0x740000B1,   //E:\1111\ac792\ui_prj\Application11\import\image\video_page\sys_setting\icon\lcd_off.png 80x80
    RES_RESET = 0x740000B2,   //E:\1111\ac792\ui_prj\Application11\import\image\video_page\sys_setting\icon\reset.png 80x80
    RES_VERSION = 0x740000B3,   //E:\1111\ac792\ui_prj\Application11\import\image\video_page\sys_setting\icon\version.png 80x80
    RES_VOICE = 0x740000B4,   //E:\1111\ac792\ui_prj\Application11\import\image\video_page\sys_setting\icon\voice.png 80x80
    RES_DATE_1 = 0x740000B5,   //E:\1111\ac792\ui_prj\Application11\import\image\video_page\sys_setting\icon\date.png 80x80
    RES_AWB = 0x740000B6,   //E:\1111\ac792\ui_prj\Application11\import\image\video_page\awb.png 48x48
    RES_AWB_FLUORESCENT_LAMP = 0x740000B7,   //E:\1111\ac792\ui_prj\Application11\import\image\video_page\awb_fluorescent_lamp.png 48x48
    RES_AWB_OSRAM_LAMP = 0x740000B8,   //E:\1111\ac792\ui_prj\Application11\import\image\video_page\awb_osram_lamp.png 48x48
    RES_AWB_SUN_CLOUDY = 0x740000B9,   //E:\1111\ac792\ui_prj\Application11\import\image\video_page\awb_sun_cloudy.png 48x48
    RES_AWB_SUN_LIGHT = 0x740000BA,   //E:\1111\ac792\ui_prj\Application11\import\image\video_page\awb_sun_light.png 48x48
    RES_HIGH = 0x740000BB,   //E:\1111\ac792\ui_prj\Application11\import\image\video_page\high.png 48x48
    RES_LOW = 0x740000BC,   //E:\1111\ac792\ui_prj\Application11\import\image\video_page\low.png 48x48
    RES_MIDDLE = 0x740000BD,   //E:\1111\ac792\ui_prj\Application11\import\image\video_page\middle.png 48x48
    RES_TIMING_PHOTO_2 = 0x740000BE,   //E:\1111\ac792\ui_prj\Application11\import\image\video_page\timing_photo_2.png 48x48
    RES_TIMING_PHOTO_5 = 0x740000BF,   //E:\1111\ac792\ui_prj\Application11\import\image\video_page\timing_photo_5.png 48x48
    RES_TIMING_PHOTO_10 = 0x740000C0,   //E:\1111\ac792\ui_prj\Application11\import\image\video_page\timing_photo_10.png 48x48
    RES_FILE_DIR = 0x740000C1,   //E:\1111\ac792\ui_prj\Application11\import\image\file_dir.png 160x160
    RES_DELETE = 0x740000C2,   //E:\1111\ac792\ui_prj\Application11\import\image\DELETE.png 48x48
    RES_DELETE_ON = 0x740000C3,   //E:\1111\ac792\ui_prj\Application11\import\image\delete_on.png 48x48
    RES_EDIT = 0x740000C4,   //E:\1111\ac792\ui_prj\Application11\import\image\EDIT.png 48x48
    RES_EDITOR_ON = 0x740000C5,   //E:\1111\ac792\ui_prj\Application11\import\image\editor_on.png 48x48
    RES_HOME = 0x740000C6,   //E:\1111\ac792\ui_prj\Application11\import\image\HOME.png 48x48
    RES_HOME_ON = 0x740000C7,   //E:\1111\ac792\ui_prj\Application11\import\image\home_on.png 48x48
    RES_LOCK = 0x740000C8,   //E:\1111\ac792\ui_prj\Application11\import\image\LOCK.png 48x48
    RES_LOCK_ON = 0x740000C9,   //E:\1111\ac792\ui_prj\Application11\import\image\lock_on.png 48x48
    RES_PHOTO = 0x740000CA,   //E:\1111\ac792\ui_prj\Application11\import\image\PHOTO.png 48x48
    RES_PHOTO_ON = 0x740000CB,   //E:\1111\ac792\ui_prj\Application11\import\image\photo_on.png 48x48
    RES_RETURN = 0x740000CC,   //E:\1111\ac792\ui_prj\Application11\import\image\RETURN.png 48x48
    RES_RETURN_ON = 0x740000CD,   //E:\1111\ac792\ui_prj\Application11\import\image\return_on.png 48x48
    RES_SELETE = 0x740000CE,   //E:\1111\ac792\ui_prj\Application11\import\image\SELETE.png 48x48
    RES_UNLOCK = 0x740000CF,   //E:\1111\ac792\ui_prj\Application11\import\image\UNLOCK.png 48x48
    RES_UNLOCK_ON = 0x740000D0,   //E:\1111\ac792\ui_prj\Application11\import\image\unlock_on.png 48x48
    RES_VIDEO = 0x740000D1,   //E:\1111\ac792\ui_prj\Application11\import\image\VIDEO.png 48x48
    RES_VOLUMELOUDER_SOLID_1 = 0x740000D2,   //E:\1111\ac792\ui_prj\Application11\import\image\volumeLouder_solid_1.png 48x48
    RES_VIDEO_PAUSE = 0x740000D3,   //E:\1111\ac792\ui_prj\Application11\import\image\video_pause.png 48x48
    RES_SKIP_NEXT = 0x740000D4,   //E:\1111\ac792\ui_prj\Application11\import\image\skip_next.png 48x48
    RES_SKIP_PREVIOUS = 0x740000D5,   //E:\1111\ac792\ui_prj\Application11\import\image\skip_previous.png 48x48
    RES_PLAY = 0x740000D6,   //E:\1111\ac792\ui_prj\Application11\import\image\play.png 32x32
    RES_VIDEO_PLAY = 0x740000D7,   //E:\1111\ac792\ui_prj\Application11\import\image\video_play.png 48x48
    RES_VOLUMEMUTE_SOLID_1 = 0x740000D8,   //E:\1111\ac792\ui_prj\Application11\import\image\volumeMute_solid_1.png 48x48
    RES_SOFTWARE = 0x740000D9,   //E:\1111\ac792\ui_prj\Application11\import\image\video_page\menu_icon\software.png 80x80
    RES_CYCLIC_VIDEO_1 = 0x740000DA,   //E:\1111\ac792\ui_prj\Application11\import\image\video_page\cyclic_video_1.png 48x48
    RES_LOCK_FLAG = 0x740000DB,   //E:\1111\ac792\ui_prj\Application11\import\image\lock_flag.png 24x24
    RES_CONNECTED = 0x740000DC,   //E:\1111\ac792\ui_prj\Application11\import\image\video_page\menu_icon\connected.png 45x45
    RES_DISCONNECT = 0x740000DD,   //E:\1111\ac792\ui_prj\Application11\import\image\video_page\menu_icon\disconnect.png 45x45
} RES_ID;

extern char *gui_get_res_path(int32_t id);

#ifdef __cplusplus
}
#endif
#endif

#endif
