#include "app_config.h"
#ifdef CONFIG_UI_STYLE_JL_ENABLE
/*Generate Code, Do NOT Edit!*/
#include "../gui_guider.h"
#include <stdlib.h>
#include <string.h>
#if LV_USE_GUIBUILDER_SIMULATOR
#include <stdio.h>
#endif

#if !LV_USE_GUIBUILDER_SIMULATOR
#define max(a, b) ((a) > (b) ? (a) : (b))
char sd_dir[] = "S:/";
char flash_dir[] = "mnt/sdfile/EXT_RESERVED/uipackres/ui/";
char path_buf[max(sizeof(sd_dir), sizeof(flash_dir)) + 20];
#endif

char *gui_get_res_path(int32_t id)
{
#if LV_USE_GUIBUILDER_SIMULATOR
    switch (id) {
    case GUI_RES_MONTSERRATMEDIUM_12_TTF:
        return "E:\\1111\\ac792\\ui_prj\\Application11\\sdk\\ui_res\\flash\\rle\\font\\35000000.rle";
    case GUI_RES_FANGZHENGKAITIJIANTI_1_28_TTF:
        return "E:\\1111\\ac792\\ui_prj\\Application11\\sdk\\ui_res\\flash\\rle\\font\\35000001.rle";
    case GUI_RES_FANGZHENGKAITIJIANTI_1_19_TTF:
        return "E:\\1111\\ac792\\ui_prj\\Application11\\sdk\\ui_res\\flash\\rle\\font\\35000002.rle";
    case GUI_RES_FANGZHENGKAITIJIANTI_1_24_TTF:
        return "E:\\1111\\ac792\\ui_prj\\Application11\\sdk\\ui_res\\flash\\rle\\font\\35000003.rle";
    case GUI_RES_FANGZHENGKAITIJIANTI_1_32_TTF:
        return "E:\\1111\\ac792\\ui_prj\\Application11\\sdk\\ui_res\\flash\\rle\\font\\35000004.rle";
    case GUI_RES_FANGZHENGKAITIJIANTI_1_16_TTF:
        return "E:\\1111\\ac792\\ui_prj\\Application11\\sdk\\ui_res\\flash\\rle\\font\\35000005.rle";
    case GUI_RES_MONTSERRATMEDIUM_18_TTF:
        return "E:\\1111\\ac792\\ui_prj\\Application11\\sdk\\ui_res\\flash\\rle\\font\\35000006.rle";
    case GUI_RES_MONTSERRATMEDIUM_20_TTF:
        return "E:\\1111\\ac792\\ui_prj\\Application11\\sdk\\ui_res\\flash\\rle\\font\\35000007.rle";
    case GUI_RES_FANGZHENGKAITIJIANTI_1_54_TTF:
        return "E:\\1111\\ac792\\ui_prj\\Application11\\sdk\\ui_res\\flash\\rle\\font\\35000008.rle";
    case GUI_RES_FANGZHENGKAITIJIANTI_1_48_TTF:
        return "E:\\1111\\ac792\\ui_prj\\Application11\\sdk\\ui_res\\flash\\rle\\font\\35000009.rle";
    case GUI_RES_FANGZHENGKAITIJIANTI_1_20_TTF:
        return "E:\\1111\\ac792\\ui_prj\\Application11\\sdk\\ui_res\\flash\\rle\\font\\3500000a.rle";
    case GUI_RES_MONTSERRATMEDIUM_24_TTF:
        return "E:\\1111\\ac792\\ui_prj\\Application11\\sdk\\ui_res\\flash\\rle\\font\\3500000b.rle";
    case GUI_RES_MONTSERRATMEDIUM_48_TTF:
        return "E:\\1111\\ac792\\ui_prj\\Application11\\sdk\\ui_res\\flash\\rle\\font\\3500000c.rle";
    case GUI_RES_MONTSERRATMEDIUM_49_TTF:
        return "E:\\1111\\ac792\\ui_prj\\Application11\\sdk\\ui_res\\flash\\rle\\font\\3500000d.rle";
    case GUI_RES_MONTSERRATMEDIUM_32_TTF:
        return "E:\\1111\\ac792\\ui_prj\\Application11\\sdk\\ui_res\\flash\\rle\\font\\3500000e.rle";
    case GUI_RES_FANGZHENGKAITIJIANTI_1_14_TTF:
        return "E:\\1111\\ac792\\ui_prj\\Application11\\sdk\\ui_res\\flash\\rle\\font\\3500000f.rle";
    case GUI_RES_MONTSERRATMEDIUM_160_TTF:
        return "E:\\1111\\ac792\\ui_prj\\Application11\\sdk\\ui_res\\flash\\rle\\font\\35000010.rle";
    case GUI_RES_FANGZHENGKAITIJIANTI_1_26_TTF:
        return "E:\\1111\\ac792\\ui_prj\\Application11\\sdk\\ui_res\\flash\\rle\\font\\35000011.rle";
    case GUI_RES_MONTSERRATMEDIUM_22_TTF:
        return "E:\\1111\\ac792\\ui_prj\\Application11\\sdk\\ui_res\\flash\\rle\\font\\35000012.rle";
    case GUI_RES_MONTSERRATMEDIUM_16_TTF:
        return "E:\\1111\\ac792\\ui_prj\\Application11\\sdk\\ui_res\\flash\\rle\\font\\35000013.rle";
    case GUI_RES_FANGSONG_16_TTF:
        return "E:\\1111\\ac792\\ui_prj\\Application11\\sdk\\ui_res\\flash\\rle\\font\\35000014.rle";
    case GUI_RES_FANGSONG_24_TTF:
        return "E:\\1111\\ac792\\ui_prj\\Application11\\sdk\\ui_res\\flash\\rle\\font\\35000015.rle";
    case GUI_RES_FANGZHENGKAITIJIANTI_1_22_TTF:
        return "E:\\1111\\ac792\\ui_prj\\Application11\\sdk\\ui_res\\flash\\rle\\font\\35000016.rle";
    case GUI_RES_TIMESNEWROMANPSMT_16_TTF:
        return "E:\\1111\\ac792\\ui_prj\\Application11\\sdk\\ui_res\\flash\\rle\\font\\35000017.rle";
    case GUI_RES_TIMESNEWROMANPSMT_24_TTF:
        return "E:\\1111\\ac792\\ui_prj\\Application11\\sdk\\ui_res\\flash\\rle\\font\\35000018.rle";
    case GUI_RES_TIMESNEWROMANPSMT_48_TTF:
        return "E:\\1111\\ac792\\ui_prj\\Application11\\sdk\\ui_res\\flash\\rle\\font\\35000019.rle";
    case GUI_RES_TIMESNEWROMANPSMT_22_TTF:
        return "E:\\1111\\ac792\\ui_prj\\Application11\\sdk\\ui_res\\flash\\rle\\font\\3500001a.rle";
    case GUI_RES_SEGOEUI_16_TTF:
        return "E:\\1111\\ac792\\ui_prj\\Application11\\sdk\\ui_res\\flash\\rle\\font\\3500001b.rle";
    case GUI_RES_SEGOEUI_24_TTF:
        return "E:\\1111\\ac792\\ui_prj\\Application11\\sdk\\ui_res\\flash\\rle\\font\\3500001c.rle";
    case GUI_RES_LEELAWADEEUI_16_TTF:
        return "E:\\1111\\ac792\\ui_prj\\Application11\\sdk\\ui_res\\flash\\rle\\font\\3500001d.rle";
    case GUI_RES_LEELAWADEEUI_24_TTF:
        return "E:\\1111\\ac792\\ui_prj\\Application11\\sdk\\ui_res\\flash\\rle\\font\\3500001e.rle";
    case GUI_RES_MALGUNGOTHIC_16_TTF:
        return "E:\\1111\\ac792\\ui_prj\\Application11\\sdk\\ui_res\\flash\\rle\\font\\3500001f.rle";
    case GUI_RES_MALGUNGOTHIC_24_TTF:
        return "E:\\1111\\ac792\\ui_prj\\Application11\\sdk\\ui_res\\flash\\rle\\font\\35000020.rle";
    case GUI_RES_MS_GOTHIC_16_TTF:
        return "E:\\1111\\ac792\\ui_prj\\Application11\\sdk\\ui_res\\flash\\rle\\font\\35000021.rle";
    case GUI_RES_CALIBRI_16_TTF:
        return "E:\\1111\\ac792\\ui_prj\\Application11\\sdk\\ui_res\\flash\\rle\\font\\35000022.rle";
    case GUI_RES_CALIBRI_24_TTF:
        return "E:\\1111\\ac792\\ui_prj\\Application11\\sdk\\ui_res\\flash\\rle\\font\\35000023.rle";
    case GUI_RES_S_PC_PNG:
        return "A:\\1111\\ac792\\ui_prj\\Application11\\import\\image\\video_page\\USB\\s_PC.png";
    case GUI_RES_S_MASS_PNG:
        return "A:\\1111\\ac792\\ui_prj\\Application11\\import\\image\\video_page\\USB\\s_MASS.png";
    case GUI_RES_VIDEO_PNG:
        return "A:\\1111\\ac792\\ui_prj\\Application11\\import\\image\\video_page\\USB\\VIDEO.png";
    case GUI_RES_VIDEO_ON_PNG:
        return "A:\\1111\\ac792\\ui_prj\\Application11\\import\\image\\video_page\\USB\\VIDEO_on.png";
    case GUI_RES_MASS_PNG:
        return "A:\\1111\\ac792\\ui_prj\\Application11\\import\\image\\video_page\\USB\\MASS.png";
    case GUI_RES_MASS_ON_PNG:
        return "A:\\1111\\ac792\\ui_prj\\Application11\\import\\image\\video_page\\USB\\MASS_on.png";
    case GUI_RES_PCCAM_PNG:
        return "A:\\1111\\ac792\\ui_prj\\Application11\\import\\image\\video_page\\USB\\PCCAM.png";
    case GUI_RES_PCCAM_ON_PNG:
        return "A:\\1111\\ac792\\ui_prj\\Application11\\import\\image\\video_page\\USB\\PCCAM_on.png";
    case GUI_RES_VIDEO_BUTTO_PNG:
        return "A:\\1111\\ac792\\ui_prj\\Application11\\import\\image\\video_page\\video_butto.png";
    case GUI_RES_VIDEO_BUTTO_FLASH1_ON_PNG:
        return "A:\\1111\\ac792\\ui_prj\\Application11\\import\\image\\video_page\\video_butto_flash1_on.png";
    case GUI_RES_VIDEO_BUTTO_FLASH2_PNG:
        return "A:\\1111\\ac792\\ui_prj\\Application11\\import\\image\\video_page\\video_butto_flash2.png";
    case GUI_RES_VIDEO_BUTTO_FLASH2_ON_PNG:
        return "A:\\1111\\ac792\\ui_prj\\Application11\\import\\image\\video_page\\video_butto_flash2_on.png";
    case GUI_RES_CYCLIC_VIDEO_CLOSE_PNG:
        return "A:\\1111\\ac792\\ui_prj\\Application11\\import\\image\\video_page\\cyclic_video_close.png";
    case GUI_RES_GRAVITY_SENSOR_LOW_PNG:
        return "A:\\1111\\ac792\\ui_prj\\Application11\\import\\image\\video_page\\gravity_sensor_low.png";
    case GUI_RES_SOUND_CLOSE_PNG:
        return "A:\\1111\\ac792\\ui_prj\\Application11\\import\\image\\video_page\\sound_close.png";
    case GUI_RES_STOPPING_MONITOR_PNG:
        return "A:\\1111\\ac792\\ui_prj\\Application11\\import\\image\\video_page\\stopping_monitor.png";
    case GUI_RES_CHECK_SPORT_PNG:
        return "A:\\1111\\ac792\\ui_prj\\Application11\\import\\image\\video_page\\check_sport.png";
    case GUI_RES_SD_PNG:
        return "A:\\1111\\ac792\\ui_prj\\Application11\\import\\image\\video_page\\SD.png";
    case GUI_RES_LOCK_PNG:
        return "A:\\1111\\ac792\\ui_prj\\Application11\\import\\image\\video_page\\lock.png";
    case GUI_RES_INTERVAL_VIDEO_CLOSE_PNG:
        return "A:\\1111\\ac792\\ui_prj\\Application11\\import\\image\\video_page\\interval_video_close.png";
    case GUI_RES_DISCONNECT_PNG:
        return "A:\\1111\\ac792\\ui_prj\\Application11\\import\\image\\video_page\\menu_icon\\disconnect.png";
    case GUI_RES_FULL_PNG:
        return "A:\\1111\\ac792\\ui_prj\\Application11\\import\\image\\video_page\\battery\\full.png";
    case GUI_RES_SETTING_PNG:
        return "A:\\1111\\ac792\\ui_prj\\Application11\\import\\image\\video_page\\left_tools\\setting.png";
    case GUI_RES_CAMERA_PNG:
        return "A:\\1111\\ac792\\ui_prj\\Application11\\import\\image\\video_page\\left_tools\\camera.png";
    case GUI_RES_HOME_PNG:
        return "A:\\1111\\ac792\\ui_prj\\Application11\\import\\image\\video_page\\left_tools\\home.png";
    case GUI_RES_BTN_LOCK_PNG:
        return "A:\\1111\\ac792\\ui_prj\\Application11\\import\\image\\video_page\\btn_lock.png";
    case GUI_RES_BTN_LOCK_ON_PNG:
        return "A:\\1111\\ac792\\ui_prj\\Application11\\import\\image\\video_page\\btn_lock_on.png";
    case GUI_RES_SWITCH_PNG:
        return "A:\\1111\\ac792\\ui_prj\\Application11\\import\\image\\video_page\\switch.png";
    case GUI_RES_SWITCH_ON_PNG:
        return "A:\\1111\\ac792\\ui_prj\\Application11\\import\\image\\video_page\\switch_on.png";
    case GUI_RES_RESOLUTION_RATIO_PNG:
        return "A:\\1111\\ac792\\ui_prj\\Application11\\import\\image\\video_page\\menu_icon\\resolution_ratio.png";
    case GUI_RES_DOUBLE_VIDEO_PNG:
        return "A:\\1111\\ac792\\ui_prj\\Application11\\import\\image\\video_page\\menu_icon\\double_video.png";
    case GUI_RES_CYCLIC_VIDEO_PNG:
        return "A:\\1111\\ac792\\ui_prj\\Application11\\import\\image\\video_page\\menu_icon\\cyclic_video.png";
    case GUI_RES_INTERVAL_VIDEO_PNG:
        return "A:\\1111\\ac792\\ui_prj\\Application11\\import\\image\\video_page\\menu_icon\\interval_video.png";
    case GUI_RES_HDR_PNG:
        return "A:\\1111\\ac792\\ui_prj\\Application11\\import\\image\\video_page\\menu_icon\\HDR.png";
    case GUI_RES_EXPOSURE_PNG:
        return "A:\\1111\\ac792\\ui_prj\\Application11\\import\\image\\video_page\\menu_icon\\exposure.png";
    case GUI_RES_CHECK_SPORT_1_PNG:
        return "A:\\1111\\ac792\\ui_prj\\Application11\\import\\image\\video_page\\menu_icon\\check_sport.png";
    case GUI_RES_DATE_PNG:
        return "A:\\1111\\ac792\\ui_prj\\Application11\\import\\image\\video_page\\menu_icon\\date.png";
    case GUI_RES_GRAVITY_SENSOR_PNG:
        return "A:\\1111\\ac792\\ui_prj\\Application11\\import\\image\\video_page\\menu_icon\\gravity_sensor.png";
    case GUI_RES_SOUND_PNG:
        return "A:\\1111\\ac792\\ui_prj\\Application11\\import\\image\\video_page\\menu_icon\\sound.png";
    case GUI_RES_STOPPING_MONITOR_1_PNG:
        return "A:\\1111\\ac792\\ui_prj\\Application11\\import\\image\\video_page\\menu_icon\\stopping_monitor.png";
    case GUI_RES_CAR_NUM_PNG:
        return "A:\\1111\\ac792\\ui_prj\\Application11\\import\\image\\video_page\\menu_icon\\car_num.png";
    case GUI_RES_HEADLIGHT_PNG:
        return "A:\\1111\\ac792\\ui_prj\\Application11\\import\\image\\video_page\\headlight.png";
    case GUI_RES_VIDEO_1_PNG:
        return "A:\\1111\\ac792\\ui_prj\\Application11\\import\\image\\video_page\\main_page\\video.png";
    case GUI_RES_VIDEO__ON_PNG:
        return "A:\\1111\\ac792\\ui_prj\\Application11\\import\\image\\video_page\\main_page\\video__on.png";
    case GUI_RES_FILE_PNG:
        return "A:\\1111\\ac792\\ui_prj\\Application11\\import\\image\\video_page\\main_page\\file.png";
    case GUI_RES_FILE_ON_PNG:
        return "A:\\1111\\ac792\\ui_prj\\Application11\\import\\image\\video_page\\main_page\\file_on.png";
    case GUI_RES_SETTING_1_PNG:
        return "A:\\1111\\ac792\\ui_prj\\Application11\\import\\image\\video_page\\main_page\\setting.png";
    case GUI_RES_SETTING_ON_PNG:
        return "A:\\1111\\ac792\\ui_prj\\Application11\\import\\image\\video_page\\main_page\\setting_on.png";
    case GUI_RES_POP_UP_WINDOW_PNG:
        return "A:\\1111\\ac792\\ui_prj\\Application11\\import\\image\\video_page\\pop_up_window.png";
    case GUI_RES_FLIG_ON_PNG:
        return "A:\\1111\\ac792\\ui_prj\\Application11\\import\\image\\video_page\\flig_on.png";
    case GUI_RES_ASTERN_PNG:
        return "A:\\1111\\ac792\\ui_prj\\Application11\\import\\image\\video_page\\astern.png";
    case GUI_RES_LCD_OFF_PNG:
        return "A:\\1111\\ac792\\ui_prj\\Application11\\import\\image\\video_page\\sys_setting\\icon\\lcd_off.png";
    case GUI_RES_AUTO_OFF_PNG:
        return "A:\\1111\\ac792\\ui_prj\\Application11\\import\\image\\video_page\\sys_setting\\icon\\auto_off.png";
    case GUI_RES_FREQUENCY_PNG:
        return "A:\\1111\\ac792\\ui_prj\\Application11\\import\\image\\video_page\\sys_setting\\icon\\frequency.png";
    case GUI_RES_VOICE_PNG:
        return "A:\\1111\\ac792\\ui_prj\\Application11\\import\\image\\video_page\\sys_setting\\icon\\voice.png";
    case GUI_RES_LANGUAGES_PNG:
        return "A:\\1111\\ac792\\ui_prj\\Application11\\import\\image\\video_page\\sys_setting\\icon\\languages.png";
    case GUI_RES_SOFTWARE_PNG:
        return "A:\\1111\\ac792\\ui_prj\\Application11\\import\\image\\video_page\\menu_icon\\software.png";
    case GUI_RES_CAR_NUM_1_PNG:
        return "A:\\1111\\ac792\\ui_prj\\Application11\\import\\image\\video_page\\sys_setting\\icon\\car_num.png";
    case GUI_RES_LANE_PNG:
        return "A:\\1111\\ac792\\ui_prj\\Application11\\import\\image\\video_page\\sys_setting\\icon\\lane.png";
    case GUI_RES_FLIG_PNG:
        return "A:\\1111\\ac792\\ui_prj\\Application11\\import\\image\\video_page\\sys_setting\\icon\\flig.png";
    case GUI_RES_FORMAT_PNG:
        return "A:\\1111\\ac792\\ui_prj\\Application11\\import\\image\\video_page\\sys_setting\\icon\\format.png";
    case GUI_RES_RESET_PNG:
        return "A:\\1111\\ac792\\ui_prj\\Application11\\import\\image\\video_page\\sys_setting\\icon\\reset.png";
    case GUI_RES_DATE_1_PNG:
        return "A:\\1111\\ac792\\ui_prj\\Application11\\import\\image\\video_page\\sys_setting\\icon\\date.png";
    case GUI_RES_VIDEO_2_PNG:
        return "A:\\1111\\ac792\\ui_prj\\Application11\\import\\image\\video_page\\sys_setting\\left_tools\\video.png";
    case GUI_RES_FILES_PNG:
        return "A:\\1111\\ac792\\ui_prj\\Application11\\import\\image\\video_page\\sys_setting\\left_tools\\FILES.png";
    case GUI_RES_PHOTO_BUTTON_PNG:
        return "A:\\1111\\ac792\\ui_prj\\Application11\\import\\image\\video_page\\photo_button.png";
    case GUI_RES_PHOTO_BUTTON_ON_PNG:
        return "A:\\1111\\ac792\\ui_prj\\Application11\\import\\image\\video_page\\photo_button_on.png";
    case GUI_RES_TIMING_PHOTO_2_PNG:
        return "A:\\1111\\ac792\\ui_prj\\Application11\\import\\image\\video_page\\timing_photo_2.png";
    case GUI_RES_CONTINUOUS_PNG:
        return "A:\\1111\\ac792\\ui_prj\\Application11\\import\\image\\video_page\\continuous.png";
    case GUI_RES_HAND_SHAKE_PNG:
        return "A:\\1111\\ac792\\ui_prj\\Application11\\import\\image\\video_page\\hand_shake.png";
    case GUI_RES_VIDEO_3_PNG:
        return "A:\\1111\\ac792\\ui_prj\\Application11\\import\\image\\video_page\\left_tools\\video.png";
    case GUI_RES_TIMING_PHOTO_PNG:
        return "A:\\1111\\ac792\\ui_prj\\Application11\\import\\image\\video_page\\menu_icon\\timing_photo.png";
    case GUI_RES_CONTINUOUS_PHOTO_PNG:
        return "A:\\1111\\ac792\\ui_prj\\Application11\\import\\image\\video_page\\menu_icon\\continuous_photo.png";
    case GUI_RES_PHOTO_QUALITY_PNG:
        return "A:\\1111\\ac792\\ui_prj\\Application11\\import\\image\\video_page\\menu_icon\\photo_quality.png";
    case GUI_RES_ACUITY_PNG:
        return "A:\\1111\\ac792\\ui_prj\\Application11\\import\\image\\video_page\\menu_icon\\acuity.png";
    case GUI_RES_AWB_PNG:
        return "A:\\1111\\ac792\\ui_prj\\Application11\\import\\image\\video_page\\menu_icon\\AWB.png";
    case GUI_RES_COLOR_PNG:
        return "A:\\1111\\ac792\\ui_prj\\Application11\\import\\image\\video_page\\menu_icon\\color.png";
    case GUI_RES_ISO_PNG:
        return "A:\\1111\\ac792\\ui_prj\\Application11\\import\\image\\video_page\\menu_icon\\ISO.png";
    case GUI_RES_HAND_SHAKE_1_PNG:
        return "A:\\1111\\ac792\\ui_prj\\Application11\\import\\image\\video_page\\menu_icon\\hand_shake.png";
    case GUI_RES_QUICK_SCAN_PNG:
        return "A:\\1111\\ac792\\ui_prj\\Application11\\import\\image\\video_page\\menu_icon\\quick_scan.png";
    case GUI_RES_HIGH_PNG:
        return "A:\\1111\\ac792\\ui_prj\\Application11\\import\\image\\video_page\\high.png";
    case GUI_RES_AWB_1_PNG:
        return "A:\\1111\\ac792\\ui_prj\\Application11\\import\\image\\video_page\\awb.png";
    case GUI_RES_VIDEO_PLAY_PNG:
        return "A:\\1111\\ac792\\ui_prj\\Application11\\import\\image\\video_play.png";
    case GUI_RES_VIDEO_PAUSE_PNG:
        return "A:\\1111\\ac792\\ui_prj\\Application11\\import\\image\\video_pause.png";
    case GUI_RES_VOLUMELOUDER_SOLID_1_PNG:
        return "A:\\1111\\ac792\\ui_prj\\Application11\\import\\image\\volumeLouder_solid_1.png";
    case GUI_RES_VOLUMEMUTE_SOLID_1_PNG:
        return "A:\\1111\\ac792\\ui_prj\\Application11\\import\\image\\volumeMute_solid_1.png";
    case GUI_RES_PHOTO_PNG:
        return "A:\\1111\\ac792\\ui_prj\\Application11\\import\\image\\PHOTO.png";
    case GUI_RES_PHOTO_ON_PNG:
        return "A:\\1111\\ac792\\ui_prj\\Application11\\import\\image\\photo_on.png";
    case GUI_RES_RETURN_PNG:
        return "A:\\1111\\ac792\\ui_prj\\Application11\\import\\image\\RETURN.png";
    case GUI_RES_RETURN_ON_PNG:
        return "A:\\1111\\ac792\\ui_prj\\Application11\\import\\image\\return_on.png";
    case GUI_RES_SKIP_PREVIOUS_PNG:
        return "A:\\1111\\ac792\\ui_prj\\Application11\\import\\image\\skip_previous.png";
    case GUI_RES_SKIP_NEXT_PNG:
        return "A:\\1111\\ac792\\ui_prj\\Application11\\import\\image\\skip_next.png";
    case GUI_RES_UP_PNG:
        return "A:\\1111\\ac792\\ui_prj\\Application11\\import\\image\\up.png";
    case GUI_RES_DOWN_PNG:
        return "A:\\1111\\ac792\\ui_prj\\Application11\\import\\image\\down.png";
    case GUI_RES_EDIT_PNG:
        return "A:\\1111\\ac792\\ui_prj\\Application11\\import\\image\\EDIT.png";
    case GUI_RES_EDITOR_ON_PNG:
        return "A:\\1111\\ac792\\ui_prj\\Application11\\import\\image\\editor_on.png";
    case GUI_RES_LOCK_1_PNG:
        return "A:\\1111\\ac792\\ui_prj\\Application11\\import\\image\\LOCK.png";
    case GUI_RES_LOCK_ON_PNG:
        return "A:\\1111\\ac792\\ui_prj\\Application11\\import\\image\\lock_on.png";
    case GUI_RES_HOME_1_PNG:
        return "A:\\1111\\ac792\\ui_prj\\Application11\\import\\image\\HOME.png";
    case GUI_RES_HOME_ON_PNG:
        return "A:\\1111\\ac792\\ui_prj\\Application11\\import\\image\\home_on.png";
    case GUI_RES_DELETE_PNG:
        return "A:\\1111\\ac792\\ui_prj\\Application11\\import\\image\\DELETE.png";
    case GUI_RES_DELETE_ON_PNG:
        return "A:\\1111\\ac792\\ui_prj\\Application11\\import\\image\\delete_on.png";
    case RES_0:
        return "A:\\1111\\ac792\\ui_prj\\Application11\\import\\image\\video_page\\battery\\0.png";
    case RES_1:
        return "A:\\1111\\ac792\\ui_prj\\Application11\\import\\image\\video_page\\battery\\1.png";
    case RES_2:
        return "A:\\1111\\ac792\\ui_prj\\Application11\\import\\image\\video_page\\battery\\2.png";
    case RES_3:
        return "A:\\1111\\ac792\\ui_prj\\Application11\\import\\image\\video_page\\battery\\3.png";
    case RES_CHARGING:
        return "A:\\1111\\ac792\\ui_prj\\Application11\\import\\image\\video_page\\battery\\charging.png";
    case RES_FULL:
        return "A:\\1111\\ac792\\ui_prj\\Application11\\import\\image\\video_page\\battery\\full.png";
    case RES_CYCLIC_VIDEO_3:
        return "A:\\1111\\ac792\\ui_prj\\Application11\\import\\image\\video_page\\cyclic_video_3.png";
    case RES_CYCLIC_VIDEO_10:
        return "A:\\1111\\ac792\\ui_prj\\Application11\\import\\image\\video_page\\cyclic_video_10.png";
    case RES_CYCLIC_VIDEO_CLOSE:
        return "A:\\1111\\ac792\\ui_prj\\Application11\\import\\image\\video_page\\cyclic_video_close.png";
    case RES_GRAVITY_SENSOR_LOW:
        return "A:\\1111\\ac792\\ui_prj\\Application11\\import\\image\\video_page\\gravity_sensor_low.png";
    case RES_GRAVITY_SENSOR_MIDLLER:
        return "A:\\1111\\ac792\\ui_prj\\Application11\\import\\image\\video_page\\gravity_sensor_midller.png";
    case RES_GRAVITY_SENSOR_HIGH:
        return "A:\\1111\\ac792\\ui_prj\\Application11\\import\\image\\video_page\\gravity_sensor_high.png";
    case RES_INTERVAL_VIDEO_CLOSE:
        return "A:\\1111\\ac792\\ui_prj\\Application11\\import\\image\\video_page\\interval_video_close.png";
    case RES_INTERVAL_VIDEO_500:
        return "A:\\1111\\ac792\\ui_prj\\Application11\\import\\image\\video_page\\interval_video_500.png";
    case RES_INTERVAL_VIDEO_200:
        return "A:\\1111\\ac792\\ui_prj\\Application11\\import\\image\\video_page\\interval_video_200.png";
    case RES_INTERVAL_VIDEO_100:
        return "A:\\1111\\ac792\\ui_prj\\Application11\\import\\image\\video_page\\interval_video_100.png";
    case RES_SD:
        return "A:\\1111\\ac792\\ui_prj\\Application11\\import\\image\\video_page\\SD.png";
    case RES_SD_CLOSE:
        return "A:\\1111\\ac792\\ui_prj\\Application11\\import\\image\\video_page\\SD_close.png";
    case RES_SOUND:
        return "A:\\1111\\ac792\\ui_prj\\Application11\\import\\image\\video_page\\sound.png";
    case RES_SOUND_CLOSE:
        return "A:\\1111\\ac792\\ui_prj\\Application11\\import\\image\\video_page\\sound_close.png";
    case RES_EXPOSURE:
        return "A:\\1111\\ac792\\ui_prj\\Application11\\import\\image\\video_page\\menu_icon\\exposure.png";
    case RES_DOUBLE_VIDEO:
        return "A:\\1111\\ac792\\ui_prj\\Application11\\import\\image\\video_page\\menu_icon\\double_video.png";
    case RES_DATE:
        return "A:\\1111\\ac792\\ui_prj\\Application11\\import\\image\\video_page\\menu_icon\\date.png";
    case RES_CYCLIC_VIDEO:
        return "A:\\1111\\ac792\\ui_prj\\Application11\\import\\image\\video_page\\menu_icon\\cyclic_video.png";
    case RES_CHECK_SPORT:
        return "A:\\1111\\ac792\\ui_prj\\Application11\\import\\image\\video_page\\menu_icon\\check_sport.png";
    case RES_CAR_NUM:
        return "A:\\1111\\ac792\\ui_prj\\Application11\\import\\image\\video_page\\menu_icon\\car_num.png";
    case RES_GRAVITY_SENSOR:
        return "A:\\1111\\ac792\\ui_prj\\Application11\\import\\image\\video_page\\menu_icon\\gravity_sensor.png";
    case RES_HDR:
        return "A:\\1111\\ac792\\ui_prj\\Application11\\import\\image\\video_page\\menu_icon\\HDR.png";
    case RES_INTERVAL_VIDEO:
        return "A:\\1111\\ac792\\ui_prj\\Application11\\import\\image\\video_page\\menu_icon\\interval_video.png";
    case RES_RESOLUTION_RATIO:
        return "A:\\1111\\ac792\\ui_prj\\Application11\\import\\image\\video_page\\menu_icon\\resolution_ratio.png";
    case RES_SOUND_1:
        return "A:\\1111\\ac792\\ui_prj\\Application11\\import\\image\\video_page\\menu_icon\\sound.png";
    case RES_STOPPING_MONITOR:
        return "A:\\1111\\ac792\\ui_prj\\Application11\\import\\image\\video_page\\menu_icon\\stopping_monitor.png";
    case RES_AUTO_OFF:
        return "A:\\1111\\ac792\\ui_prj\\Application11\\import\\image\\video_page\\sys_setting\\icon\\auto_off.png";
    case RES_CAR_NUM_1:
        return "A:\\1111\\ac792\\ui_prj\\Application11\\import\\image\\video_page\\sys_setting\\icon\\car_num.png";
    case RES_FLIG:
        return "A:\\1111\\ac792\\ui_prj\\Application11\\import\\image\\video_page\\sys_setting\\icon\\flig.png";
    case RES_FORMAT:
        return "A:\\1111\\ac792\\ui_prj\\Application11\\import\\image\\video_page\\sys_setting\\icon\\format.png";
    case RES_FREQUENCY:
        return "A:\\1111\\ac792\\ui_prj\\Application11\\import\\image\\video_page\\sys_setting\\icon\\frequency.png";
    case RES_LANE:
        return "A:\\1111\\ac792\\ui_prj\\Application11\\import\\image\\video_page\\sys_setting\\icon\\lane.png";
    case RES_LANGUAGES:
        return "A:\\1111\\ac792\\ui_prj\\Application11\\import\\image\\video_page\\sys_setting\\icon\\languages.png";
    case RES_LCD_OFF:
        return "A:\\1111\\ac792\\ui_prj\\Application11\\import\\image\\video_page\\sys_setting\\icon\\lcd_off.png";
    case RES_RESET:
        return "A:\\1111\\ac792\\ui_prj\\Application11\\import\\image\\video_page\\sys_setting\\icon\\reset.png";
    case RES_VERSION:
        return "A:\\1111\\ac792\\ui_prj\\Application11\\import\\image\\video_page\\sys_setting\\icon\\version.png";
    case RES_VOICE:
        return "A:\\1111\\ac792\\ui_prj\\Application11\\import\\image\\video_page\\sys_setting\\icon\\voice.png";
    case RES_DATE_1:
        return "A:\\1111\\ac792\\ui_prj\\Application11\\import\\image\\video_page\\sys_setting\\icon\\date.png";
    case RES_AWB:
        return "A:\\1111\\ac792\\ui_prj\\Application11\\import\\image\\video_page\\awb.png";
    case RES_AWB_FLUORESCENT_LAMP:
        return "A:\\1111\\ac792\\ui_prj\\Application11\\import\\image\\video_page\\awb_fluorescent_lamp.png";
    case RES_AWB_OSRAM_LAMP:
        return "A:\\1111\\ac792\\ui_prj\\Application11\\import\\image\\video_page\\awb_osram_lamp.png";
    case RES_AWB_SUN_CLOUDY:
        return "A:\\1111\\ac792\\ui_prj\\Application11\\import\\image\\video_page\\awb_sun_cloudy.png";
    case RES_AWB_SUN_LIGHT:
        return "A:\\1111\\ac792\\ui_prj\\Application11\\import\\image\\video_page\\awb_sun_light.png";
    case RES_HIGH:
        return "A:\\1111\\ac792\\ui_prj\\Application11\\import\\image\\video_page\\high.png";
    case RES_LOW:
        return "A:\\1111\\ac792\\ui_prj\\Application11\\import\\image\\video_page\\low.png";
    case RES_MIDDLE:
        return "A:\\1111\\ac792\\ui_prj\\Application11\\import\\image\\video_page\\middle.png";
    case RES_TIMING_PHOTO_2:
        return "A:\\1111\\ac792\\ui_prj\\Application11\\import\\image\\video_page\\timing_photo_2.png";
    case RES_TIMING_PHOTO_5:
        return "A:\\1111\\ac792\\ui_prj\\Application11\\import\\image\\video_page\\timing_photo_5.png";
    case RES_TIMING_PHOTO_10:
        return "A:\\1111\\ac792\\ui_prj\\Application11\\import\\image\\video_page\\timing_photo_10.png";
    case RES_FILE_DIR:
        return "A:\\1111\\ac792\\ui_prj\\Application11\\import\\image\\file_dir.png";
    case RES_DELETE:
        return "A:\\1111\\ac792\\ui_prj\\Application11\\import\\image\\DELETE.png";
    case RES_DELETE_ON:
        return "A:\\1111\\ac792\\ui_prj\\Application11\\import\\image\\delete_on.png";
    case RES_EDIT:
        return "A:\\1111\\ac792\\ui_prj\\Application11\\import\\image\\EDIT.png";
    case RES_EDITOR_ON:
        return "A:\\1111\\ac792\\ui_prj\\Application11\\import\\image\\editor_on.png";
    case RES_HOME:
        return "A:\\1111\\ac792\\ui_prj\\Application11\\import\\image\\HOME.png";
    case RES_HOME_ON:
        return "A:\\1111\\ac792\\ui_prj\\Application11\\import\\image\\home_on.png";
    case RES_LOCK:
        return "A:\\1111\\ac792\\ui_prj\\Application11\\import\\image\\LOCK.png";
    case RES_LOCK_ON:
        return "A:\\1111\\ac792\\ui_prj\\Application11\\import\\image\\lock_on.png";
    case RES_PHOTO:
        return "A:\\1111\\ac792\\ui_prj\\Application11\\import\\image\\PHOTO.png";
    case RES_PHOTO_ON:
        return "A:\\1111\\ac792\\ui_prj\\Application11\\import\\image\\photo_on.png";
    case RES_RETURN:
        return "A:\\1111\\ac792\\ui_prj\\Application11\\import\\image\\RETURN.png";
    case RES_RETURN_ON:
        return "A:\\1111\\ac792\\ui_prj\\Application11\\import\\image\\return_on.png";
    case RES_SELETE:
        return "A:\\1111\\ac792\\ui_prj\\Application11\\import\\image\\SELETE.png";
    case RES_UNLOCK:
        return "A:\\1111\\ac792\\ui_prj\\Application11\\import\\image\\UNLOCK.png";
    case RES_UNLOCK_ON:
        return "A:\\1111\\ac792\\ui_prj\\Application11\\import\\image\\unlock_on.png";
    case RES_VIDEO:
        return "A:\\1111\\ac792\\ui_prj\\Application11\\import\\image\\VIDEO.png";
    case RES_VOLUMELOUDER_SOLID_1:
        return "A:\\1111\\ac792\\ui_prj\\Application11\\import\\image\\volumeLouder_solid_1.png";
    case RES_VIDEO_PAUSE:
        return "A:\\1111\\ac792\\ui_prj\\Application11\\import\\image\\video_pause.png";
    case RES_SKIP_NEXT:
        return "A:\\1111\\ac792\\ui_prj\\Application11\\import\\image\\skip_next.png";
    case RES_SKIP_PREVIOUS:
        return "A:\\1111\\ac792\\ui_prj\\Application11\\import\\image\\skip_previous.png";
    case RES_PLAY:
        return "A:\\1111\\ac792\\ui_prj\\Application11\\import\\image\\play.png";
    case RES_VIDEO_PLAY:
        return "A:\\1111\\ac792\\ui_prj\\Application11\\import\\image\\video_play.png";
    case RES_VOLUMEMUTE_SOLID_1:
        return "A:\\1111\\ac792\\ui_prj\\Application11\\import\\image\\volumeMute_solid_1.png";
    case RES_SOFTWARE:
        return "A:\\1111\\ac792\\ui_prj\\Application11\\import\\image\\video_page\\menu_icon\\software.png";
    case RES_CYCLIC_VIDEO_1:
        return "A:\\1111\\ac792\\ui_prj\\Application11\\import\\image\\video_page\\cyclic_video_1.png";
    case RES_LOCK_FLAG:
        return "A:\\1111\\ac792\\ui_prj\\Application11\\import\\image\\lock_flag.png";
    case RES_CONNECTED:
        return "A:\\1111\\ac792\\ui_prj\\Application11\\import\\image\\video_page\\menu_icon\\connected.png";
    case RES_DISCONNECT:
        return "A:\\1111\\ac792\\ui_prj\\Application11\\import\\image\\video_page\\menu_icon\\disconnect.png";
    default:
        return NULL;
    }
#else
    memset(path_buf, 0, sizeof(path_buf));
    if (id >= 0x30000000 && id < 0x30800000) {
        snprintf(path_buf, sizeof(path_buf), "%s%x.%s", flash_dir, id, "ttf");
    } else if (id >= 0x30800000 && id < 0x31000000) {
        snprintf(path_buf, sizeof(path_buf), "%s%x.%s", sd_dir, id, "ttf");
    } else if (id >= 0x31000000 && id < 0x31800000) {
        snprintf(path_buf, sizeof(path_buf), "%s%x.%s", flash_dir, id, "woff");
    } else if (id >= 0x31800000 && id < 0x32000000) {
        snprintf(path_buf, sizeof(path_buf), "%s%x.%s", sd_dir, id, "woff");
    } else if (id >= 0x32000000 && id < 0x32800000) {
        snprintf(path_buf, sizeof(path_buf), "%s%x.%s", flash_dir, id, "woff2");
    } else if (id >= 0x32800000 && id < 0x33000000) {
        snprintf(path_buf, sizeof(path_buf), "%s%x.%s", sd_dir, id, "woff2");
    } else if (id >= 0x33000000 && id < 0x33800000) {
        snprintf(path_buf, sizeof(path_buf), "%s%x.%s", flash_dir, id, "otf");
    } else if (id >= 0x33800000 && id < 0x34000000) {
        snprintf(path_buf, sizeof(path_buf), "%s%x.%s", sd_dir, id, "otf");
    } else if (id >= 0x34000000 && id < 0x34800000) {
        snprintf(path_buf, sizeof(path_buf), "%s%x.%s", flash_dir, id, "bin");
    } else if (id >= 0x34800000 && id < 0x35000000) {
        snprintf(path_buf, sizeof(path_buf), "%s%x.%s", sd_dir, id, "bin");
    } else if (id >= 0x35000000 && id < 0x35800000) {
        snprintf(path_buf, sizeof(path_buf), "%s%x.%s", flash_dir, id, "rle");
    } else if (id >= 0x35800000 && id < 0x36000000) {
        snprintf(path_buf, sizeof(path_buf), "%s%x.%s", sd_dir, id, "rle");
    } else if (id >= 0x36000000 && id < 0x36800000) {
        snprintf(path_buf, sizeof(path_buf), "%s%x.%s", flash_dir, id, "fnt");
    } else if (id >= 0x36800000 && id < 0x37000000) {
        snprintf(path_buf, sizeof(path_buf), "%s%x.%s", sd_dir, id, "fnt");
    } else if (id >= 0x37000000 && id < 0x37800000) {
        snprintf(path_buf, sizeof(path_buf), "%s%x.%s", flash_dir, id, "lzw");
    } else if (id >= 0x37800000 && id < 0x38000000) {
        snprintf(path_buf, sizeof(path_buf), "%s%x.%s", sd_dir, id, "lzw");
    } else if (id >= 0x39000000 && id < 0x39800000) {
        snprintf(path_buf, sizeof(path_buf), "%s%x.%s", flash_dir, id, "json");
    } else if (id >= 0x39800000 && id < 0x3A000000) {
        snprintf(path_buf, sizeof(path_buf), "%s%x.%s", sd_dir, id, "json");
    } else if (id >= 0x3A000000 && id < 0x3A800000) {
        snprintf(path_buf, sizeof(path_buf), "%s%x.%s", flash_dir, id, "bin");
    } else if (id >= 0x3A800000 && id < 0x3B000000) {
        snprintf(path_buf, sizeof(path_buf), "%s%x.%s", sd_dir, id, "bin");
    } else if (id >= 0x3B000000 && id < 0x3B800000) {
        snprintf(path_buf, sizeof(path_buf), "%s%x.%s", flash_dir, id, "rle");
    } else if (id >= 0x3B800000 && id < 0x3C000000) {
        snprintf(path_buf, sizeof(path_buf), "%s%x.%s", sd_dir, id, "rle");
    } else if (id >= 0x3D000000 && id < 0x3D800000) {
        snprintf(path_buf, sizeof(path_buf), "%s%x.%s", flash_dir, id, "mp4");
    } else if (id >= 0x3D800000 && id < 0x3E000000) {
        snprintf(path_buf, sizeof(path_buf), "%s%x.%s", sd_dir, id, "mp4");
    } else if (id >= 0x3E000000 && id < 0x3E800000) {
        snprintf(path_buf, sizeof(path_buf), "%s%x.%s", flash_dir, id, "avi");
    } else if (id >= 0x3E800000 && id < 0x3F000000) {
        snprintf(path_buf, sizeof(path_buf), "%s%x.%s", sd_dir, id, "avi");
    } else if (id >= 0x3F000000 && id < 0x3F800000) {
        snprintf(path_buf, sizeof(path_buf), "%s%x.%s", flash_dir, id, "bin");
    } else if (id >= 0x3F800000 && id < 0x40000000) {
        snprintf(path_buf, sizeof(path_buf), "%s%x.%s", sd_dir, id, "bin");
    } else if (id >= 0x40000000 && id < 0x40800000) {
        snprintf(path_buf, sizeof(path_buf), "%s%x.%s", flash_dir, id, "rle");
    } else if (id >= 0x40800000 && id < 0x41000000) {
        snprintf(path_buf, sizeof(path_buf), "%s%x.%s", sd_dir, id, "rle");
    } else if (id >= 0x42000000 && id < 0x42800000) {
        snprintf(path_buf, sizeof(path_buf), "%s%x.%s", flash_dir, id, "gif");
    } else if (id >= 0x42800000 && id < 0x43000000) {
        snprintf(path_buf, sizeof(path_buf), "%s%x.%s", sd_dir, id, "gif");
    } else if (id >= 0x43000000 && id < 0x43800000) {
        snprintf(path_buf, sizeof(path_buf), "%s%x.%s", flash_dir, id, "zip");
    } else if (id >= 0x43800000 && id < 0x44000000) {
        snprintf(path_buf, sizeof(path_buf), "%s%x.%s", sd_dir, id, "zip");
    } else if (id >= 0x46000000 && id < 0x46800000) {
        snprintf(path_buf, sizeof(path_buf), "%s%x.%s", flash_dir, id, "png");
    } else if (id >= 0x46800000 && id < 0x47000000) {
        snprintf(path_buf, sizeof(path_buf), "%s%x.%s", sd_dir, id, "png");
    } else if (id >= 0x47000000 && id < 0x47800000) {
        snprintf(path_buf, sizeof(path_buf), "%s%x.%s", flash_dir, id, "jpg");
    } else if (id >= 0x47800000 && id < 0x48000000) {
        snprintf(path_buf, sizeof(path_buf), "%s%x.%s", sd_dir, id, "jpg");
    } else if (id >= 0x48000000 && id < 0x48800000) {
        snprintf(path_buf, sizeof(path_buf), "%s%x.%s", flash_dir, id, "jpeg");
    } else if (id >= 0x48800000 && id < 0x49000000) {
        snprintf(path_buf, sizeof(path_buf), "%s%x.%s", sd_dir, id, "jpeg");
    } else if (id >= 0x49000000 && id < 0x49800000) {
        snprintf(path_buf, sizeof(path_buf), "%s%x.%s", flash_dir, id, "bmp");
    } else if (id >= 0x49800000 && id < 0x4A000000) {
        snprintf(path_buf, sizeof(path_buf), "%s%x.%s", sd_dir, id, "bmp");
    } else if (id >= 0x4A000000 && id < 0x4A800000) {
        snprintf(path_buf, sizeof(path_buf), "%s%x.%s", flash_dir, id, "svg");
    } else if (id >= 0x4A800000 && id < 0x4B000000) {
        snprintf(path_buf, sizeof(path_buf), "%s%x.%s", sd_dir, id, "svg");
    } else if (id >= 0x4B000000 && id < 0x4B800000) {
        snprintf(path_buf, sizeof(path_buf), "%s%x.%s", flash_dir, id, "zip");
    } else if (id >= 0x4B800000 && id < 0x4C000000) {
        snprintf(path_buf, sizeof(path_buf), "%s%x.%s", sd_dir, id, "zip");
    } else if (id >= 0x6E000000 && id < 0x6E800000) {
        snprintf(path_buf, sizeof(path_buf), "%s%x.%s", flash_dir, id, "png");
    } else if (id >= 0x6E800000 && id < 0x6F000000) {
        snprintf(path_buf, sizeof(path_buf), "%s%x.%s", sd_dir, id, "png");
    } else if (id >= 0x6F000000 && id < 0x6F800000) {
        snprintf(path_buf, sizeof(path_buf), "%s%x.%s", flash_dir, id, "jpg");
    } else if (id >= 0x6F800000 && id < 0x70000000) {
        snprintf(path_buf, sizeof(path_buf), "%s%x.%s", sd_dir, id, "jpg");
    } else if (id >= 0x70000000 && id < 0x70800000) {
        snprintf(path_buf, sizeof(path_buf), "%s%x.%s", flash_dir, id, "jpeg");
    } else if (id >= 0x70800000 && id < 0x71000000) {
        snprintf(path_buf, sizeof(path_buf), "%s%x.%s", sd_dir, id, "jpeg");
    } else if (id >= 0x71000000 && id < 0x71800000) {
        snprintf(path_buf, sizeof(path_buf), "%s%x.%s", flash_dir, id, "bmp");
    } else if (id >= 0x71800000 && id < 0x72000000) {
        snprintf(path_buf, sizeof(path_buf), "%s%x.%s", sd_dir, id, "bmp");
    } else if (id >= 0x72000000 && id < 0x72800000) {
        snprintf(path_buf, sizeof(path_buf), "%s%x.%s", flash_dir, id, "svg");
    } else if (id >= 0x72800000 && id < 0x73000000) {
        snprintf(path_buf, sizeof(path_buf), "%s%x.%s", sd_dir, id, "svg");
    } else if (id >= 0x74000000 && id < 0x74800000) {
        snprintf(path_buf, sizeof(path_buf), "%s%x.%s", flash_dir, id, "zip");
    } else if (id >= 0x74800000 && id < 0x75000000) {
        snprintf(path_buf, sizeof(path_buf), "%s%x.%s", sd_dir, id, "zip");
    } else {
        return NULL;
    }
    return path_buf;
#endif
}

#endif
