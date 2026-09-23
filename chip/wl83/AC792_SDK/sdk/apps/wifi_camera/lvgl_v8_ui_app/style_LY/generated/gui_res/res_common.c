#include "app_config.h"
#ifdef CONFIG_UI_STYLE_LY_ENABLE
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
const char sd_dir[] = "storage/sd0/C/ui/";
char path_buf[MAX2(sizeof(flash_dir), sizeof(sd_dir)) + 20];
#endif

char *gui_get_res_path(int32_t id)
{
#if LV_USE_GUIBUILDER_SIMULATOR
    switch (id) {
    case GUI_RES_FANGZHENGKAITIJIANTI_1_22_TTF_FLASH:
        return "D:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\sdk\\ui_res\\flash\\rle\\font\\35000000.rle";
    case GUI_RES_FANGZHENGKAITIJIANTI_1_26_TTF_FLASH:
        return "D:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\sdk\\ui_res\\flash\\rle\\font\\35000001.rle";
    case GUI_RES_FANGZHENGKAITIJIANTI_1_18_TTF_FLASH:
        return "D:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\sdk\\ui_res\\flash\\rle\\font\\35000002.rle";
    case GUI_RES_MONTSERRATMEDIUM_18_TTF_FLASH:
        return "D:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\sdk\\ui_res\\flash\\rle\\font\\35000003.rle";
    case GUI_RES_FANGZHENGKAITIJIANTI_1_48_TTF_FLASH:
        return "D:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\sdk\\ui_res\\flash\\rle\\font\\35000004.rle";
    case GUI_RES_MONTSERRATMEDIUM_24_TTF_FLASH:
        return "D:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\sdk\\ui_res\\flash\\rle\\font\\35000005.rle";
    case GUI_RES_MONTSERRATMEDIUM_12_TTF_FLASH:
        return "D:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\sdk\\ui_res\\flash\\rle\\font\\35000006.rle";
    case GUI_RES_MONTSERRATMEDIUM_22_TTF_FLASH:
        return "D:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\sdk\\ui_res\\flash\\rle\\font\\35000007.rle";
    case GUI_RES_FANGZHENGKAITIJIANTI_1_24_TTF_FLASH:
        return "D:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\sdk\\ui_res\\flash\\rle\\font\\35000008.rle";
    case GUI_RES_FANGZHENGKAITIJIANTI_1_16_TTF_FLASH:
        return "D:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\sdk\\ui_res\\flash\\rle\\font\\35000009.rle";
    case GUI_RES_MONTSERRATMEDIUM_16_TTF_FLASH:
        return "D:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\sdk\\ui_res\\flash\\rle\\font\\3500000a.rle";
    case GUI_RES_MONTSERRATMEDIUM_20_TTF_FLASH:
        return "D:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\sdk\\ui_res\\flash\\rle\\font\\3500000b.rle";
    case GUI_RES_MONTSERRATMEDIUM_30_TTF_FLASH:
        return "D:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\sdk\\ui_res\\flash\\rle\\font\\3500000c.rle";
    case GUI_RES_MONTSERRATMEDIUM_32_TTF_FLASH:
        return "D:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\sdk\\ui_res\\flash\\rle\\font\\3500000d.rle";
    case GUI_RES_MONTSERRATMEDIUM_28_TTF_FLASH:
        return "D:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\sdk\\ui_res\\flash\\rle\\font\\3500000e.rle";
    case GUI_RES_MONTSERRATMEDIUM_21_TTF_FLASH:
        return "D:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\sdk\\ui_res\\flash\\rle\\font\\3500000f.rle";
    case GUI_RES_SIMSUN_16_WOFF_FLASH:
        return "D:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\sdk\\ui_res\\flash\\rle\\font\\35000010.rle";
    case GUI_RES_SIMSUN_18_WOFF_FLASH:
        return "D:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\sdk\\ui_res\\flash\\rle\\font\\35000011.rle";
    case GUI_RES_FANGSONG_16_TTF_FLASH:
        return "D:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\sdk\\ui_res\\flash\\rle\\font\\35000012.rle";
    case GUI_RES_FANGSONG_24_TTF_FLASH:
        return "D:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\sdk\\ui_res\\flash\\rle\\font\\35000013.rle";
    case GUI_RES_TIMESNEWROMANPSMT_16_TTF_FLASH:
        return "D:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\sdk\\ui_res\\flash\\rle\\font\\35000014.rle";
    case GUI_RES_TIMESNEWROMANPSMT_24_TTF_FLASH:
        return "D:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\sdk\\ui_res\\flash\\rle\\font\\35000015.rle";
    case GUI_RES_SEGOEUI_16_TTF_FLASH:
        return "D:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\sdk\\ui_res\\flash\\rle\\font\\35000016.rle";
    case GUI_RES_SEGOEUI_24_TTF_FLASH:
        return "D:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\sdk\\ui_res\\flash\\rle\\font\\35000017.rle";
    case GUI_RES_LEELAWADEEUI_16_TTF_FLASH:
        return "D:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\sdk\\ui_res\\flash\\rle\\font\\35000018.rle";
    case GUI_RES_LEELAWADEEUI_24_TTF_FLASH:
        return "D:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\sdk\\ui_res\\flash\\rle\\font\\35000019.rle";
    case GUI_RES_MALGUNGOTHIC_16_TTF_FLASH:
        return "D:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\sdk\\ui_res\\flash\\rle\\font\\3500001a.rle";
    case GUI_RES_MALGUNGOTHIC_24_TTF_FLASH:
        return "D:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\sdk\\ui_res\\flash\\rle\\font\\3500001b.rle";
    case GUI_RES_MS_GOTHIC_16_TTF_FLASH:
        return "D:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\sdk\\ui_res\\flash\\rle\\font\\3500001c.rle";
    case GUI_RES_CALIBRI_16_TTF_FLASH:
        return "D:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\sdk\\ui_res\\flash\\rle\\font\\3500001d.rle";
    case GUI_RES_CALIBRI_24_TTF_FLASH:
        return "D:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\sdk\\ui_res\\flash\\rle\\font\\3500001e.rle";
    case GUI_RES_S_PC_PNG:
        return "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\video_page\\USB\\s_PC.png";
    case GUI_RES_S_MASS_PNG:
        return "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\video_page\\USB\\s_MASS.png";
    case GUI_RES_I_REC_PNG:
        return "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\LY_UI\\rec\\rec_scan\\i_rec.png";
    case GUI_RES_CYCLIC_VIDEO_3_PNG:
        return "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\LY_UI\\rec\\rec_scan\\cyclic_video_3.png";
    case GUI_RES_EXP_A0_PNG:
        return "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\LY_UI\\rec\\rec_scan\\exp_a0.png";
    case GUI_RES_I_MOT_PNG:
        return "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\LY_UI\\rec\\rec_scan\\i_mot.png";
    case GUI_RES_I_TEAR_PNG:
        return "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\LY_UI\\rec\\rec_scan\\i_tear.png";
    case GUI_RES_MIC_ON_PNG:
        return "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\LY_UI\\rec\\rec_scan\\mic_on.png";
    case GUI_RES_I_HDR_PNG:
        return "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\LY_UI\\rec\\rec_scan\\i_hdr.png";
    case GUI_RES_I_GRA_L_PNG:
        return "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\LY_UI\\rec\\rec_scan\\i_gra_l.png";
    case GUI_RES_PARK_PNG:
        return "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\LY_UI\\rec\\rec_scan\\park.png";
    case GUI_RES_BAT_FULL_PNG:
        return "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\LY_UI\\rec\\rec_scan\\bat_full.png";
    case GUI_RES_CARD_ONLINE_PNG:
        return "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\LY_UI\\rec\\rec_scan\\card_online.png";
    case GUI_RES_RED_CIRCLE_PNG:
        return "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\LY_UI\\rec\\rec_scan\\red_circle.png";
    case GUI_RES_FLIG_ON_PNG:
        return "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\LY_UI\\rec\\rec_scan\\flig_on.png";
    case GUI_RES_KEY_PNG:
        return "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\LY_UI\\rec\\rec_scan\\key.png";
    case GUI_RES_M_SOLU_PNG:
        return "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\LY_UI\\rec\\rec_menu\\m_solu.png";
    case GUI_RES_M_TWO_REC_PNG:
        return "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\LY_UI\\rec\\rec_menu\\m_two_rec.png";
    case GUI_RES_M_CYC_PNG:
        return "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\LY_UI\\rec\\rec_menu\\m_cyc.png";
    case GUI_RES_REC_NOCYC_PNG:
        return "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\LY_UI\\rec\\rec_menu\\rec_nocyc.png";
    case GUI_RES_M_HDR_PNG:
        return "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\LY_UI\\rec\\rec_menu\\m_hdr.png";
    case GUI_RES_M_EXP_PNG:
        return "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\LY_UI\\rec\\rec_menu\\m_exp.png";
    case GUI_RES_M_MOT_PNG:
        return "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\LY_UI\\rec\\rec_menu\\m_mot.png";
    case GUI_RES_M_AUD_PNG:
        return "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\LY_UI\\rec\\rec_menu\\m_aud.png";
    case GUI_RES_M_DAT_PNG:
        return "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\LY_UI\\rec\\rec_menu\\m_dat.png";
    case GUI_RES_M_GRA_PNG:
        return "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\LY_UI\\rec\\rec_menu\\m_gra.png";
    case GUI_RES_M_PARK_PNG:
        return "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\LY_UI\\rec\\rec_menu\\m_park.png";
    case GUI_RES_M_NUM_PNG:
        return "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\LY_UI\\rec\\rec_menu\\m_num.png";
    case GUI_RES_M_FLIG_PNG:
        return "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\LY_UI\\rec\\rec_menu\\m_flig.png";
    case GUI_RES_MENU_STA_PNG:
        return "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\LY_UI\\rec\\rec_menu\\menu_sta.png";
    case GUI_RES_REC_PNG:
        return "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\LY_UI\\rec\\rec_menu\\rec.png";
    case GUI_RES_SET_PNG:
        return "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\LY_UI\\rec\\rec_menu\\set.png";
    case GUI_RES_LEFT_PNG:
        return "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\LY_UI\\direc\\left.png";
    case GUI_RES_UP_PNG:
        return "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\LY_UI\\direc\\up.png";
    case GUI_RES_DOWN_PNG:
        return "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\LY_UI\\direc\\down.png";
    case GUI_RES_RIGHT_PNG:
        return "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\LY_UI\\direc\\right.png";
    case GUI_RES_POP_UP_WINDOW_PNG:
        return "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\video_page\\pop_up_window.png";
    case GUI_RES_FLIG_ON_1_PNG:
        return "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\video_page\\flig_on.png";
    case GUI_RES_LCD_AU_PNG:
        return "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\LY_UI\\sys_menu\\lcd_au.png";
    case GUI_RES_AUTO_OFF_PNG:
        return "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\LY_UI\\sys_menu\\auto_off.png";
    case GUI_RES_HZ_PNG:
        return "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\LY_UI\\sys_menu\\hz.png";
    case GUI_RES_KEY_V_PNG:
        return "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\LY_UI\\sys_menu\\key_v.png";
    case GUI_RES_LANGUAGE_PNG:
        return "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\LY_UI\\sys_menu\\language.png";
    case GUI_RES_TIME_PNG:
        return "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\LY_UI\\sys_menu\\time.png";
    case GUI_RES_TV_PNG:
        return "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\LY_UI\\sys_menu\\tv.png";
    case GUI_RES_MDK_PNG:
        return "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\LY_UI\\sys_menu\\mdk.png";
    case GUI_RES_DEF_SET_PNG:
        return "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\LY_UI\\sys_menu\\def_set.png";
    case GUI_RES_VERSION_PNG:
        return "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\LY_UI\\sys_menu\\version.png";
    case GUI_RES_NUM_L_PNG:
        return "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\LY_UI\\sys_menu\\NUM_l.png";
    case GUI_RES_NUM_D_PNG:
        return "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\LY_UI\\sys_menu\\NUM_d.png";
    case GUI_RES_TP_3_PNG:
        return "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\LY_UI\\photo\\photo_scan\\tp_3.png";
    case GUI_RES_TP_PNG:
        return "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\LY_UI\\photo\\photo_scan\\tp.png";
    case GUI_RES_AWB_AUTO_PNG:
        return "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\LY_UI\\photo\\photo_scan\\awb_auto.png";
    case GUI_RES_ISO_AUTO_PNG:
        return "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\LY_UI\\photo\\photo_scan\\iso_auto.png";
    case GUI_RES_Q1_PNG:
        return "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\LY_UI\\photo\\photo_scan\\q1.png";
    case GUI_RES_DL2_PNG:
        return "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\LY_UI\\photo\\photo_scan\\dl2.png";
    case GUI_RES_SHAKE_OFF_PNG:
        return "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\LY_UI\\photo\\photo_scan\\shake_off.png";
    case GUI_RES_LIANP_PNG:
        return "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\LY_UI\\photo\\photo_scan\\lianp.png";
    case GUI_RES_PAIZ_PNG:
        return "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\LY_UI\\photo\\photo_menu\\paiz.png";
    case GUI_RES_LIANP_1_PNG:
        return "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\LY_UI\\photo\\photo_menu\\lianp.png";
    case GUI_RES_IMG_Q_PNG:
        return "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\LY_UI\\photo\\photo_menu\\img_q.png";
    case GUI_RES_RUIDU_PNG:
        return "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\LY_UI\\photo\\photo_menu\\ruidu.png";
    case GUI_RES_COLOR_PNG:
        return "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\LY_UI\\photo\\photo_menu\\color.png";
    case GUI_RES_ISO_PNG:
        return "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\LY_UI\\photo\\photo_menu\\iso.png";
    case GUI_RES_SHAKE_PNG:
        return "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\LY_UI\\photo\\photo_menu\\shake.png";
    case GUI_RES_SCAN_PNG:
        return "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\LY_UI\\photo\\photo_menu\\scan.png";
    case GUI_RES_PHOTO_PNG:
        return "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\LY_UI\\rec\\rec_menu\\photo.png";
    case GUI_RES_VIDEO_PLAY_PNG:
        return "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\video_play.png";
    case GUI_RES_VIDEO_PAUSE_PNG:
        return "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\video_pause.png";
    case GUI_RES_SKIP_PREVIOUS_PNG:
        return "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\skip_previous.png";
    case GUI_RES_SKIP_NEXT_PNG:
        return "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\skip_next.png";
    case GUI_RES_VOLUMELOUDER_SOLID_1_PNG:
        return "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\volumeLouder_solid_1.png";
    case GUI_RES_VOLUMEMUTE_SOLID_1_PNG:
        return "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\volumeMute_solid_1.png";
    case GUI_RES_PHOTO_1_PNG:
        return "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\PHOTO.png";
    case GUI_RES_PHOTO_ON_PNG:
        return "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\photo_on.png";
    case GUI_RES_UP_1_PNG:
        return "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\up.png";
    case GUI_RES_DOWN_1_PNG:
        return "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\down.png";
    case GUI_RES_DELET_PNG:
        return "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\LY_UI\\dec\\delet.png";
    case GUI_RES_PROTECT_PNG:
        return "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\LY_UI\\dec\\protect.png";
    case GUI_RES_PLAY_PNG:
        return "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\LY_UI\\rec\\rec_menu\\play.png";
    case GUI_RES_ASTERN_PNG:
        return "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\video_page\\astern.png";
    case GUI_RES_VIDEO_PNG:
        return "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\LY_UI\\dec\\video.png";
    case GUI_RES_PHOTO_2_PNG:
        return "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\LY_UI\\dec\\photo.png";
    case GUI_RES_CARD_OFFLINE_PNG:
        return "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\LY_UI\\rec\\rec_scan\\card_offline.png";
    case GUI_RES_PLAY_1_PNG:
        return "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\LY_UI\\dec\\play.png";
    case GUI_RES_PAUSE_PNG:
        return "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\LY_UI\\dec\\pause.png";
    case GUI_RES_SPORT_PNG:
        return "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\alarm\\SPORT.png";
    case GUI_RES_TTFAR_PNG:
        return "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\alarm\\TTFAR.png";
    case GUI_RES_FREE_PNG:
        return "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\alarm\\FREE.png";
    case GUI_RES_TEM_01_PNG:
        return "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\main\\tem_01.png";
    case GUI_RES_LAMP_25_PNG:
        return "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\alarm\\Lamp_25.png";
    case GUI_RES_LAMP_26_PNG:
        return "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\alarm\\Lamp_26.png";
    case GUI_RES_LAMP_23_PNG:
        return "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\alarm\\Lamp_23.png";
    case GUI_RES_LAMP_24_PNG:
        return "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\alarm\\Lamp_24.png";
    case GUI_RES_LAMP_29_PNG:
        return "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\alarm\\Lamp_29.png";
    case GUI_RES_LAMP_30_PNG:
        return "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\alarm\\Lamp_30.png";
    case GUI_RES_LAMP_27_PNG:
        return "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\alarm\\Lamp_27.png";
    case GUI_RES_LAMP_28_PNG:
        return "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\alarm\\Lamp_28.png";
    case GUI_RES_READY_PNG:
        return "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\alarm\\READY.png";
    case GUI_RES_LAMP_19_PNG:
        return "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\alarm\\Lamp_19.png";
    case GUI_RES_LAMP_20_PNG:
        return "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\alarm\\Lamp_20.png";
    case GUI_RES_LAMP_21_PNG:
        return "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\alarm\\Lamp_21.png";
    case GUI_RES_LAMP_22_PNG:
        return "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\alarm\\Lamp_22.png";
    case GUI_RES_BAT_001_PNG:
        return "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\battery\\bat_001.png";
    case GUI_RES_BAT_002_PNG:
        return "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\battery\\bat_002.png";
    case GUI_RES_BAT_003_PNG:
        return "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\battery\\bat_003.png";
    case GUI_RES_BAT_004_PNG:
        return "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\battery\\bat_004.png";
    case GUI_RES_BAT_005_PNG:
        return "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\battery\\bat_005.png";
    case GUI_RES_BAT_006_PNG:
        return "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\battery\\bat_006.png";
    case GUI_RES_BAT_007_PNG:
        return "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\battery\\bat_007.png";
    case GUI_RES_BAT_008_PNG:
        return "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\battery\\bat_008.png";
    case GUI_RES_BAT_009_PNG:
        return "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\battery\\bat_009.png";
    case GUI_RES_BAT_010_PNG:
        return "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\battery\\bat_010.png";
    case GUI_RES_BAT_011_PNG:
        return "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\battery\\bat_011.png";
    case GUI_RES_BAT_012_PNG:
        return "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\battery\\bat_012.png";
    case GUI_RES_BAT_013_PNG:
        return "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\battery\\bat_013.png";
    case GUI_RES_BAT_014_PNG:
        return "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\battery\\bat_014.png";
    case GUI_RES_BAT_015_PNG:
        return "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\battery\\bat_015.png";
    case GUI_RES_BAT_016_PNG:
        return "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\battery\\bat_016.png";
    case GUI_RES_BAT_017_PNG:
        return "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\battery\\bat_017.png";
    case GUI_RES_BAT_018_PNG:
        return "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\battery\\bat_018.png";
    case GUI_RES_BAT_019_PNG:
        return "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\battery\\bat_019.png";
    case GUI_RES_BAT_020_PNG:
        return "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\battery\\bat_020.png";
    case GUI_RES_BAT_021_PNG:
        return "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\battery\\bat_021.png";
    case GUI_RES_BAT_022_PNG:
        return "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\battery\\bat_022.png";
    case GUI_RES_BAT_023_PNG:
        return "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\battery\\bat_023.png";
    case GUI_RES_BAT_024_PNG:
        return "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\battery\\bat_024.png";
    case GUI_RES_BAT_025_PNG:
        return "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\battery\\bat_025.png";
    case GUI_RES_BAT_026_PNG:
        return "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\battery\\bat_026.png";
    case GUI_RES_BAT_027_PNG:
        return "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\battery\\bat_027.png";
    case GUI_RES_BAT_028_PNG:
        return "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\battery\\bat_028.png";
    case GUI_RES_BAT_029_PNG:
        return "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\battery\\bat_029.png";
    case GUI_RES_BAT_030_PNG:
        return "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\battery\\bat_030.png";
    case GUI_RES_BAT_031_PNG:
        return "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\battery\\bat_031.png";
    case GUI_RES_BAT_032_PNG:
        return "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\battery\\bat_032.png";
    case GUI_RES_BAT_033_PNG:
        return "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\battery\\bat_033.png";
    case GUI_RES_BAT_034_PNG:
        return "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\battery\\bat_034.png";
    case GUI_RES_BAT_035_PNG:
        return "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\battery\\bat_035.png";
    case GUI_RES_BAT_036_PNG:
        return "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\battery\\bat_036.png";
    case GUI_RES_BAT_037_PNG:
        return "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\battery\\bat_037.png";
    case GUI_RES_BAT_038_PNG:
        return "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\battery\\bat_038.png";
    case GUI_RES_BAT_039_PNG:
        return "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\battery\\bat_039.png";
    case GUI_RES_BAT_040_PNG:
        return "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\battery\\bat_040.png";
    case GUI_RES_BAT_041_PNG:
        return "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\battery\\bat_041.png";
    case GUI_RES_BAT_042_PNG:
        return "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\battery\\bat_042.png";
    case GUI_RES_BAT_043_PNG:
        return "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\battery\\bat_043.png";
    case GUI_RES_BAT_044_PNG:
        return "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\battery\\bat_044.png";
    case GUI_RES_BAT_045_PNG:
        return "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\battery\\bat_045.png";
    case GUI_RES_BAT_046_PNG:
        return "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\battery\\bat_046.png";
    case GUI_RES_BAT_047_PNG:
        return "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\battery\\bat_047.png";
    case GUI_RES_BAT_048_PNG:
        return "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\battery\\bat_048.png";
    case GUI_RES_BAT_049_PNG:
        return "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\battery\\bat_049.png";
    case GUI_RES_BAT_050_PNG:
        return "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\battery\\bat_050.png";
    case GUI_RES_BAT_051_PNG:
        return "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\battery\\bat_051.png";
    case GUI_RES_BAT_052_PNG:
        return "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\battery\\bat_052.png";
    case GUI_RES_BAT_053_PNG:
        return "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\battery\\bat_053.png";
    case GUI_RES_BAT_054_PNG:
        return "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\battery\\bat_054.png";
    case GUI_RES_BAT_055_PNG:
        return "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\battery\\bat_055.png";
    case GUI_RES_BAT_056_PNG:
        return "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\battery\\bat_056.png";
    case GUI_RES_BAT_057_PNG:
        return "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\battery\\bat_057.png";
    case GUI_RES_BAT_058_PNG:
        return "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\battery\\bat_058.png";
    case GUI_RES_BAT_059_PNG:
        return "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\battery\\bat_059.png";
    case GUI_RES_BAT_060_PNG:
        return "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\battery\\bat_060.png";
    case GUI_RES_BAT_061_PNG:
        return "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\battery\\bat_061.png";
    case GUI_RES_BAT_062_PNG:
        return "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\battery\\bat_062.png";
    case GUI_RES_BAT_063_PNG:
        return "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\battery\\bat_063.png";
    case GUI_RES_BAT_064_PNG:
        return "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\battery\\bat_064.png";
    case GUI_RES_BAT_065_PNG:
        return "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\battery\\bat_065.png";
    case GUI_RES_BAT_066_PNG:
        return "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\battery\\bat_066.png";
    case GUI_RES_BAT_067_PNG:
        return "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\battery\\bat_067.png";
    case GUI_RES_BAT_068_PNG:
        return "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\battery\\bat_068.png";
    case GUI_RES_BAT_069_PNG:
        return "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\battery\\bat_069.png";
    case GUI_RES_BAT_070_PNG:
        return "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\battery\\bat_070.png";
    case GUI_RES_BAT_071_PNG:
        return "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\battery\\bat_071.png";
    case GUI_RES_BAT_072_PNG:
        return "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\battery\\bat_072.png";
    case GUI_RES_BAT_073_PNG:
        return "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\battery\\bat_073.png";
    case GUI_RES_BAT_074_PNG:
        return "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\battery\\bat_074.png";
    case GUI_RES_BAT_075_PNG:
        return "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\battery\\bat_075.png";
    case GUI_RES_BAT_076_PNG:
        return "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\battery\\bat_076.png";
    case GUI_RES_BAT_077_PNG:
        return "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\battery\\bat_077.png";
    case GUI_RES_BAT_078_PNG:
        return "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\battery\\bat_078.png";
    case GUI_RES_BAT_079_PNG:
        return "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\battery\\bat_079.png";
    case GUI_RES_BAT_080_PNG:
        return "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\battery\\bat_080.png";
    case GUI_RES_BAT_081_PNG:
        return "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\battery\\bat_081.png";
    case GUI_RES_BAT_082_PNG:
        return "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\battery\\bat_082.png";
    case GUI_RES_BAT_083_PNG:
        return "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\battery\\bat_083.png";
    case GUI_RES_BAT_084_PNG:
        return "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\battery\\bat_084.png";
    case GUI_RES_BAT_085_PNG:
        return "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\battery\\bat_085.png";
    case GUI_RES_BAT_086_PNG:
        return "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\battery\\bat_086.png";
    case GUI_RES_BAT_087_PNG:
        return "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\battery\\bat_087.png";
    case GUI_RES_BAT_088_PNG:
        return "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\battery\\bat_088.png";
    case GUI_RES_BAT_089_PNG:
        return "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\battery\\bat_089.png";
    case GUI_RES_BAT_090_PNG:
        return "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\battery\\bat_090.png";
    case GUI_RES_BAT_091_PNG:
        return "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\battery\\bat_091.png";
    case GUI_RES_BAT_092_PNG:
        return "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\battery\\bat_092.png";
    case GUI_RES_BAT_093_PNG:
        return "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\battery\\bat_093.png";
    case GUI_RES_BAT_094_PNG:
        return "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\battery\\bat_094.png";
    case GUI_RES_BAT_095_PNG:
        return "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\battery\\bat_095.png";
    case GUI_RES_BAT_096_PNG:
        return "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\battery\\bat_096.png";
    case GUI_RES_BAT_097_PNG:
        return "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\battery\\bat_097.png";
    case GUI_RES_BAT_098_PNG:
        return "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\battery\\bat_098.png";
    case GUI_RES_BAT_099_PNG:
        return "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\battery\\bat_099.png";
    case GUI_RES_BAT_100_PNG:
        return "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\battery\\bat_100.png";
    case GUI_RES_LAMP_01_PNG:
        return "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\alarm\\Lamp_01.png";
    case GUI_RES_TIPS_PNG:
        return "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\tips\\tips.png";
    case GUI_RES_DIE1_PNG:
        return "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\music\\die1.png";
    case GUI_RES_ZHEN_PNG:
        return "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\music\\zhen.png";
    case GUI_RES_ROAD_ECO_PNG:
        return "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\main\\road_eco.png";
    case GUI_RES_ARROW_ECO_PNG:
        return "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\main\\arrow_eco.png";
    case GUI_RES_BAT_B_PNG:
        return "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\main\\bat_b.png";
    case GUI_RES_LAMP_02_PNG:
        return "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\alarm\\Lamp_02.png";
    case GUI_RES_LAMP_03_PNG:
        return "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\alarm\\Lamp_03.png";
    case GUI_RES_LAMP_04_PNG:
        return "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\alarm\\Lamp_04.png";
    case GUI_RES_LAMP_05_PNG:
        return "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\alarm\\Lamp_05.png";
    case GUI_RES_LAMP_08_PNG:
        return "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\alarm\\Lamp_08.png";
    case GUI_RES_LAMP_09_PNG:
        return "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\alarm\\Lamp_09.png";
    case GUI_RES_LAMP_10_PNG:
        return "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\alarm\\Lamp_10.png";
    case GUI_RES_LAMP_11_PNG:
        return "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\alarm\\Lamp_11.png";
    case GUI_RES_LAMP_12_PNG:
        return "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\alarm\\Lamp_12.png";
    case GUI_RES_LAMP_13_PNG:
        return "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\alarm\\Lamp_13.png";
    case GUI_RES_LAMP_14_PNG:
        return "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\alarm\\Lamp_14.png";
    case GUI_RES_LAMP_15_PNG:
        return "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\alarm\\Lamp_15.png";
    case GUI_RES_LAMP_16_PNG:
        return "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\alarm\\Lamp_16.png";
    case GUI_RES_LAMP_17_PNG:
        return "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\alarm\\Lamp_17.png";
    case GUI_RES_LAMP_18_PAGE_METER_IMG_CRUISEWORK_PNG:
        return "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\alarm\\Lamp_18.png";
    case GUI_RES_0_PNG:
        return "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\main\\0.png";
    case GUI_RES_1_PNG:
        return "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\main\\1.png";
    case GUI_RES_2_PNG:
        return "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\main\\2.png";
    case GUI_RES_3_PNG:
        return "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\main\\3.png";
    case GUI_RES_4_PNG:
        return "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\main\\4.png";
    case GUI_RES_5_PNG:
        return "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\main\\5.png";
    case GUI_RES_6_PNG:
        return "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\main\\6.png";
    case GUI_RES_7_PNG:
        return "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\main\\7.png";
    case GUI_RES_8_PNG:
        return "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\main\\8.png";
    case GUI_RES_9_PNG:
        return "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\main\\9.png";
    case GUI_RES_LAMP_06_PNG:
        return "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\alarm\\Lamp_06.png";
    case GUI_RES_LAMP_07_PNG:
        return "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\alarm\\Lamp_07.png";
    case GUI_RES_PW_001_PNG:
        return "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\power\\pw_001.png";
    case GUI_RES_PW_002_PNG:
        return "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\power\\pw_002.png";
    case GUI_RES_PW_003_PNG:
        return "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\power\\pw_003.png";
    case GUI_RES_PW_004_PNG:
        return "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\power\\pw_004.png";
    case GUI_RES_PW_005_PNG:
        return "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\power\\pw_005.png";
    case GUI_RES_PW_006_PNG:
        return "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\power\\pw_006.png";
    case GUI_RES_PW_007_PNG:
        return "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\power\\pw_007.png";
    case GUI_RES_PW_008_PNG:
        return "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\power\\pw_008.png";
    case GUI_RES_PW_009_PNG:
        return "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\power\\pw_009.png";
    case GUI_RES_PW_010_PNG:
        return "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\power\\pw_010.png";
    case GUI_RES_PW_011_PNG:
        return "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\power\\pw_011.png";
    case GUI_RES_PW_012_PNG:
        return "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\power\\pw_012.png";
    case GUI_RES_PW_013_PNG:
        return "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\power\\pw_013.png";
    case GUI_RES_PW_014_PNG:
        return "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\power\\pw_014.png";
    case GUI_RES_PW_015_PNG:
        return "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\power\\pw_015.png";
    case GUI_RES_PW_016_PNG:
        return "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\power\\pw_016.png";
    case GUI_RES_PW_017_PNG:
        return "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\power\\pw_017.png";
    case GUI_RES_PW_018_PNG:
        return "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\power\\pw_018.png";
    case GUI_RES_PW_019_PNG:
        return "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\power\\pw_019.png";
    case GUI_RES_PW_020_PNG:
        return "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\power\\pw_020.png";
    case GUI_RES_PW_021_PNG:
        return "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\power\\pw_021.png";
    case GUI_RES_PW_022_PNG:
        return "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\power\\pw_022.png";
    case GUI_RES_PW_023_PNG:
        return "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\power\\pw_023.png";
    case GUI_RES_PW_024_PNG:
        return "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\power\\pw_024.png";
    case GUI_RES_PW_025_PNG:
        return "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\power\\pw_025.png";
    case GUI_RES_PW_026_PNG:
        return "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\power\\pw_026.png";
    case GUI_RES_PW_027_PNG:
        return "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\power\\pw_027.png";
    case GUI_RES_PW_028_PNG:
        return "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\power\\pw_028.png";
    case GUI_RES_PW_029_PNG:
        return "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\power\\pw_029.png";
    case GUI_RES_PW_030_PNG:
        return "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\power\\pw_030.png";
    case GUI_RES_PW_031_PNG:
        return "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\power\\pw_031.png";
    case GUI_RES_PW_032_PNG:
        return "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\power\\pw_032.png";
    case GUI_RES_PW_034_PNG:
        return "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\power\\pw_034.png";
    case GUI_RES_PW_035_PNG:
        return "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\power\\pw_035.png";
    case GUI_RES_PW_036_PNG:
        return "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\power\\pw_036.png";
    case GUI_RES_PW_037_PNG:
        return "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\power\\pw_037.png";
    case GUI_RES_PW_038_PNG:
        return "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\power\\pw_038.png";
    case GUI_RES_PW_039_PNG:
        return "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\power\\pw_039.png";
    case GUI_RES_PW_040_PNG:
        return "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\power\\pw_040.png";
    case GUI_RES_PW_041_PNG:
        return "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\power\\pw_041.png";
    case GUI_RES_PW_042_PNG:
        return "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\power\\pw_042.png";
    case GUI_RES_PW_043_PNG:
        return "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\power\\pw_043.png";
    case GUI_RES_PW_044_PNG:
        return "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\power\\pw_044.png";
    case GUI_RES_PW_045_PNG:
        return "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\power\\pw_045.png";
    case GUI_RES_PW_046_PNG:
        return "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\power\\pw_046.png";
    case GUI_RES_PW_047_PNG:
        return "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\power\\pw_047.png";
    case GUI_RES_PW_048_PNG:
        return "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\power\\pw_048.png";
    case GUI_RES_PW_049_PNG:
        return "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\power\\pw_049.png";
    case GUI_RES_PW_050_PNG:
        return "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\power\\pw_050.png";
    case GUI_RES_PW_051_PNG:
        return "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\power\\pw_051.png";
    case GUI_RES_PW_052_PNG:
        return "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\power\\pw_052.png";
    case GUI_RES_PW_053_PNG:
        return "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\power\\pw_053.png";
    case GUI_RES_PW_054_PNG:
        return "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\power\\pw_054.png";
    case GUI_RES_PW_055_PNG:
        return "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\power\\pw_055.png";
    case GUI_RES_PW_056_PNG:
        return "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\power\\pw_056.png";
    case GUI_RES_PW_057_PNG:
        return "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\power\\pw_057.png";
    case GUI_RES_PW_058_PNG:
        return "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\power\\pw_058.png";
    case GUI_RES_PW_059_PNG:
        return "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\power\\pw_059.png";
    case GUI_RES_PW_060_PNG:
        return "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\power\\pw_060.png";
    case GUI_RES_PW_061_PNG:
        return "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\power\\pw_061.png";
    case GUI_RES_PW_062_PNG:
        return "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\power\\pw_062.png";
    case GUI_RES_PW_063_PNG:
        return "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\power\\pw_063.png";
    case GUI_RES_PW_064_PNG:
        return "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\power\\pw_064.png";
    case GUI_RES_PW_065_PNG:
        return "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\power\\pw_065.png";
    case GUI_RES_PW_066_PNG:
        return "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\power\\pw_066.png";
    case GUI_RES_PW_067_PNG:
        return "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\power\\pw_067.png";
    case GUI_RES_PW_068_PNG:
        return "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\power\\pw_068.png";
    case GUI_RES_PW_069_PNG:
        return "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\power\\pw_069.png";
    case GUI_RES_PW_070_PNG:
        return "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\power\\pw_070.png";
    case GUI_RES_PW_071_PNG:
        return "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\power\\pw_071.png";
    case GUI_RES_PW_072_PNG:
        return "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\power\\pw_072.png";
    case GUI_RES_PW_073_PNG:
        return "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\power\\pw_073.png";
    case GUI_RES_PW_074_PNG:
        return "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\power\\pw_074.png";
    case GUI_RES_PW_075_PNG:
        return "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\power\\pw_075.png";
    case GUI_RES_PW_076_PNG:
        return "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\power\\pw_076.png";
    case GUI_RES_PW_077_PNG:
        return "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\power\\pw_077.png";
    case GUI_RES_PW_078_PNG:
        return "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\power\\pw_078.png";
    case GUI_RES_PW_079_PNG:
        return "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\power\\pw_079.png";
    case GUI_RES_PW_080_PNG:
        return "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\power\\pw_080.png";
    case GUI_RES_PW_081_PNG:
        return "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\power\\pw_081.png";
    case GUI_RES_PW_082_PNG:
        return "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\power\\pw_082.png";
    case GUI_RES_PW_083_PNG:
        return "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\power\\pw_083.png";
    case GUI_RES_PW_084_PNG:
        return "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\power\\pw_084.png";
    case GUI_RES_PW_085_PNG:
        return "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\power\\pw_085.png";
    case GUI_RES_PW_086_PNG:
        return "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\power\\pw_086.png";
    case GUI_RES_PW_087_PNG:
        return "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\power\\pw_087.png";
    case GUI_RES_PW_088_PNG:
        return "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\power\\pw_088.png";
    case GUI_RES_PW_089_PNG:
        return "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\power\\pw_089.png";
    case GUI_RES_PW_090_PNG:
        return "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\power\\pw_090.png";
    case GUI_RES_PW_091_PNG:
        return "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\power\\pw_091.png";
    case GUI_RES_PW_092_PNG:
        return "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\power\\pw_092.png";
    case GUI_RES_PW_093_PNG:
        return "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\power\\pw_093.png";
    case GUI_RES_PW_094_PNG:
        return "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\power\\pw_094.png";
    case GUI_RES_PW_095_PNG:
        return "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\power\\pw_095.png";
    case GUI_RES_PW_096_PNG:
        return "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\power\\pw_096.png";
    case GUI_RES_PW_097_PNG:
        return "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\power\\pw_097.png";
    case GUI_RES_PW_098_PNG:
        return "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\power\\pw_098.png";
    case GUI_RES_PW_099_PNG:
        return "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\power\\pw_099.png";
    case GUI_RES_PW_100_PNG:
        return "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\power\\pw_100.png";
    case GUI_RES_PWR_001_PNG:
        return "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\power_R\\pwr_001.png";
    case GUI_RES_PWR_002_PNG:
        return "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\power_R\\pwr_002.png";
    case GUI_RES_PWR_003_PNG:
        return "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\power_R\\pwr_003.png";
    case GUI_RES_PWR_004_PNG:
        return "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\power_R\\pwr_004.png";
    case GUI_RES_PWR_005_PNG:
        return "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\power_R\\pwr_005.png";
    case GUI_RES_PWR_006_PNG:
        return "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\power_R\\pwr_006.png";
    case GUI_RES_PWR_007_PNG:
        return "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\power_R\\pwr_007.png";
    case GUI_RES_PWR_008_PNG:
        return "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\power_R\\pwr_008.png";
    case GUI_RES_PWR_009_PNG:
        return "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\power_R\\pwr_009.png";
    case GUI_RES_PWR_010_PNG:
        return "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\power_R\\pwr_010.png";
    case GUI_RES_PWR_011_PNG:
        return "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\power_R\\pwr_011.png";
    case GUI_RES_PWR_012_PNG:
        return "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\power_R\\pwr_012.png";
    case GUI_RES_PWR_013_PNG:
        return "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\power_R\\pwr_013.png";
    case GUI_RES_PWR_014_PNG:
        return "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\power_R\\pwr_014.png";
    case GUI_RES_PWR_015_PNG:
        return "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\power_R\\pwr_015.png";
    case GUI_RES_PWR_016_PNG:
        return "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\power_R\\pwr_016.png";
    case GUI_RES_PWR_017_PNG:
        return "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\power_R\\pwr_017.png";
    case GUI_RES_PWR_018_PNG:
        return "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\power_R\\pwr_018.png";
    case GUI_RES_PWR_019_PNG:
        return "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\power_R\\pwr_019.png";
    case GUI_RES_PWR_020_PNG:
        return "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\power_R\\pwr_020.png";
    case GUI_RES_PWR_021_PNG:
        return "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\power_R\\pwr_021.png";
    case GUI_RES_PWR_022_PNG:
        return "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\power_R\\pwr_022.png";
    case GUI_RES_PWR_023_PNG:
        return "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\power_R\\pwr_023.png";
    case GUI_RES_PWR_024_PNG:
        return "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\power_R\\pwr_024.png";
    case GUI_RES_PWR_025_PNG:
        return "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\power_R\\pwr_025.png";
    case GUI_RES_PWR_026_PNG:
        return "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\power_R\\pwr_026.png";
    case GUI_RES_PWR_027_PNG:
        return "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\power_R\\pwr_027.png";
    case GUI_RES_PWR_028_PNG:
        return "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\power_R\\pwr_028.png";
    case GUI_RES_PWR_029_PNG:
        return "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\power_R\\pwr_029.png";
    case GUI_RES_PWR_030_PNG:
        return "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\power_R\\pwr_030.png";
    case GUI_RES_PWR_031_PNG:
        return "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\power_R\\pwr_031.png";
    case GUI_RES_PWR_032_PNG:
        return "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\power_R\\pwr_032.png";
    case GUI_RES_PWR_033_PNG:
        return "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\power_R\\pwr_033.png";
    case GUI_RES_PWR_034_PNG:
        return "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\power_R\\pwr_034.png";
    case GUI_RES_PWR_035_PNG:
        return "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\power_R\\pwr_035.png";
    case GUI_RES_PWR_036_PNG:
        return "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\power_R\\pwr_036.png";
    case GUI_RES_PWR_037_PNG:
        return "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\power_R\\pwr_037.png";
    case GUI_RES_PWR_038_PNG:
        return "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\power_R\\pwr_038.png";
    case GUI_RES_PWR_039_PNG:
        return "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\power_R\\pwr_039.png";
    case GUI_RES_PWR_040_PNG:
        return "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\power_R\\pwr_040.png";
    case GUI_RES_PWR_041_PNG:
        return "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\power_R\\pwr_041.png";
    case GUI_RES_PWR_042_PNG:
        return "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\power_R\\pwr_042.png";
    case GUI_RES_PWR_043_PNG:
        return "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\power_R\\pwr_043.png";
    case GUI_RES_PWR_044_PNG:
        return "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\power_R\\pwr_044.png";
    case GUI_RES_PWR_045_PNG:
        return "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\power_R\\pwr_045.png";
    case GUI_RES_PWR_046_PNG:
        return "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\power_R\\pwr_046.png";
    case GUI_RES_PWR_047_PNG:
        return "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\power_R\\pwr_047.png";
    case GUI_RES_PWR_048_PNG:
        return "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\power_R\\pwr_048.png";
    case GUI_RES_PWR_049_PNG:
        return "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\power_R\\pwr_049.png";
    case GUI_RES_PWR_050_PNG:
        return "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\power_R\\pwr_050.png";
    case GUI_RES_PWR_051_PNG:
        return "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\power_R\\pwr_051.png";
    case GUI_RES_PWR_052_PNG:
        return "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\power_R\\pwr_052.png";
    case GUI_RES_PWR_053_PNG:
        return "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\power_R\\pwr_053.png";
    case GUI_RES_PWR_054_PNG:
        return "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\power_R\\pwr_054.png";
    case GUI_RES_PWR_055_PNG:
        return "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\power_R\\pwr_055.png";
    case GUI_RES_PWR_056_PNG:
        return "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\power_R\\pwr_056.png";
    case GUI_RES_PWR_057_PNG:
        return "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\power_R\\pwr_057.png";
    case GUI_RES_PWR_058_PNG:
        return "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\power_R\\pwr_058.png";
    case GUI_RES_PWR_059_PNG:
        return "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\power_R\\pwr_059.png";
    case GUI_RES_PWR_060_PNG:
        return "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\power_R\\pwr_060.png";
    case GUI_RES_PWR_061_PNG:
        return "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\power_R\\pwr_061.png";
    case GUI_RES_PWR_062_PNG:
        return "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\power_R\\pwr_062.png";
    case GUI_RES_PWR_063_PNG:
        return "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\power_R\\pwr_063.png";
    case GUI_RES_PWR_064_PNG:
        return "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\power_R\\pwr_064.png";
    case GUI_RES_PWR_065_PNG:
        return "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\power_R\\pwr_065.png";
    case GUI_RES_PWR_066_PNG:
        return "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\power_R\\pwr_066.png";
    case GUI_RES_PWR_067_PNG:
        return "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\power_R\\pwr_067.png";
    case GUI_RES_PWR_068_PNG:
        return "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\power_R\\pwr_068.png";
    case GUI_RES_PWR_069_PNG:
        return "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\power_R\\pwr_069.png";
    case GUI_RES_PWR_070_PNG:
        return "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\power_R\\pwr_070.png";
    case GUI_RES_PWR_071_PNG:
        return "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\power_R\\pwr_071.png";
    case GUI_RES_PWR_072_PNG:
        return "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\power_R\\pwr_072.png";
    case GUI_RES_PWR_073_PNG:
        return "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\power_R\\pwr_073.png";
    case GUI_RES_PWR_074_PNG:
        return "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\power_R\\pwr_074.png";
    case GUI_RES_PWR_075_PNG:
        return "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\power_R\\pwr_075.png";
    case GUI_RES_PWR_076_PNG:
        return "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\power_R\\pwr_076.png";
    case GUI_RES_PWR_077_PNG:
        return "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\power_R\\pwr_077.png";
    case GUI_RES_PWR_078_PNG:
        return "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\power_R\\pwr_078.png";
    case GUI_RES_PWR_079_PNG:
        return "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\power_R\\pwr_079.png";
    case GUI_RES_PWR_080_PNG:
        return "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\power_R\\pwr_080.png";
    case GUI_RES_PWR_081_PNG:
        return "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\power_R\\pwr_081.png";
    case GUI_RES_PWR_082_PNG:
        return "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\power_R\\pwr_082.png";
    case GUI_RES_PWR_083_PNG:
        return "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\power_R\\pwr_083.png";
    case GUI_RES_PWR_084_PNG:
        return "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\power_R\\pwr_084.png";
    case GUI_RES_PWR_085_PNG:
        return "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\power_R\\pwr_085.png";
    case GUI_RES_PWR_086_PNG:
        return "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\power_R\\pwr_086.png";
    case GUI_RES_PWR_087_PNG:
        return "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\power_R\\pwr_087.png";
    case GUI_RES_PWR_088_PNG:
        return "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\power_R\\pwr_088.png";
    case GUI_RES_PWR_089_PNG:
        return "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\power_R\\pwr_089.png";
    case GUI_RES_PWR_090_PNG:
        return "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\power_R\\pwr_090.png";
    case GUI_RES_PWR_091_PNG:
        return "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\power_R\\pwr_091.png";
    case GUI_RES_PWR_092_PNG:
        return "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\power_R\\pwr_092.png";
    case GUI_RES_PWR_093_PNG:
        return "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\power_R\\pwr_093.png";
    case GUI_RES_PWR_094_PNG:
        return "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\power_R\\pwr_094.png";
    case GUI_RES_PWR_095_PNG:
        return "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\power_R\\pwr_095.png";
    case GUI_RES_PWR_096_PNG:
        return "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\power_R\\pwr_096.png";
    case GUI_RES_PWR_097_PNG:
        return "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\power_R\\pwr_097.png";
    case GUI_RES_PWR_098_PNG:
        return "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\power_R\\pwr_098.png";
    case GUI_RES_PWR_099_PNG:
        return "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\power_R\\pwr_099.png";
    case GUI_RES_HANG_PNG:
        return "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\main\\hang.png";
    case GUI_RES_PICK_PNG:
        return "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\main\\pick.png";
    case GUI_RES_IMG_LOGO_PNG:
        return "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\img_logo.png";
    case RES_0:
        return "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\video_page\\battery\\0.png";
    case RES_1:
        return "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\video_page\\battery\\1.png";
    case RES_2:
        return "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\video_page\\battery\\2.png";
    case RES_3:
        return "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\video_page\\battery\\3.png";
    case RES_CHARGING:
        return "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\video_page\\battery\\charging.png";
    case RES_FULL:
        return "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\video_page\\battery\\full.png";
    case RES_GRAVITY_SENSOR_LOW:
        return "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\video_page\\gravity_sensor_low.png";
    case RES_GRAVITY_SENSOR_MIDLLER:
        return "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\video_page\\gravity_sensor_midller.png";
    case RES_GRAVITY_SENSOR_HIGH:
        return "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\video_page\\gravity_sensor_high.png";
    case RES_INTERVAL_VIDEO_CLOSE:
        return "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\video_page\\interval_video_close.png";
    case RES_INTERVAL_VIDEO_500:
        return "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\video_page\\interval_video_500.png";
    case RES_INTERVAL_VIDEO_200:
        return "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\video_page\\interval_video_200.png";
    case RES_INTERVAL_VIDEO_100:
        return "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\video_page\\interval_video_100.png";
    case RES_SD:
        return "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\video_page\\SD.png";
    case RES_SD_CLOSE:
        return "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\video_page\\SD_close.png";
    case RES_SOUND:
        return "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\video_page\\sound.png";
    case RES_SOUND_CLOSE:
        return "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\video_page\\sound_close.png";
    case RES_EXPOSURE:
        return "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\video_page\\menu_icon\\exposure.png";
    case RES_DOUBLE_VIDEO:
        return "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\video_page\\menu_icon\\double_video.png";
    case RES_DATE:
        return "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\video_page\\menu_icon\\date.png";
    case RES_CYCLIC_VIDEO:
        return "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\video_page\\menu_icon\\cyclic_video.png";
    case RES_CHECK_SPORT:
        return "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\video_page\\menu_icon\\check_sport.png";
    case RES_CAR_NUM:
        return "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\video_page\\menu_icon\\car_num.png";
    case RES_GRAVITY_SENSOR:
        return "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\video_page\\menu_icon\\gravity_sensor.png";
    case RES_HDR:
        return "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\video_page\\menu_icon\\HDR.png";
    case RES_INTERVAL_VIDEO:
        return "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\video_page\\menu_icon\\interval_video.png";
    case RES_RESOLUTION_RATIO:
        return "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\video_page\\menu_icon\\resolution_ratio.png";
    case RES_SOUND_1:
        return "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\video_page\\menu_icon\\sound.png";
    case RES_STOPPING_MONITOR:
        return "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\video_page\\menu_icon\\stopping_monitor.png";
    case RES_AUTO_OFF:
        return "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\video_page\\sys_setting\\icon\\auto_off.png";
    case RES_CAR_NUM_1:
        return "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\video_page\\sys_setting\\icon\\car_num.png";
    case RES_FLIG:
        return "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\video_page\\sys_setting\\icon\\flig.png";
    case RES_FORMAT:
        return "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\video_page\\sys_setting\\icon\\format.png";
    case RES_FREQUENCY:
        return "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\video_page\\sys_setting\\icon\\frequency.png";
    case RES_LANE:
        return "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\video_page\\sys_setting\\icon\\lane.png";
    case RES_LANGUAGES:
        return "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\video_page\\sys_setting\\icon\\languages.png";
    case RES_LCD_OFF:
        return "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\video_page\\sys_setting\\icon\\lcd_off.png";
    case RES_RESET:
        return "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\video_page\\sys_setting\\icon\\reset.png";
    case RES_VERSION:
        return "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\video_page\\sys_setting\\icon\\version.png";
    case RES_VOICE:
        return "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\video_page\\sys_setting\\icon\\voice.png";
    case RES_DATE_1:
        return "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\video_page\\sys_setting\\icon\\date.png";
    case RES_AWB:
        return "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\video_page\\awb.png";
    case RES_AWB_FLUORESCENT_LAMP:
        return "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\video_page\\awb_fluorescent_lamp.png";
    case RES_AWB_OSRAM_LAMP:
        return "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\video_page\\awb_osram_lamp.png";
    case RES_AWB_SUN_CLOUDY:
        return "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\video_page\\awb_sun_cloudy.png";
    case RES_AWB_SUN_LIGHT:
        return "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\video_page\\awb_sun_light.png";
    case RES_HIGH:
        return "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\video_page\\high.png";
    case RES_LOW:
        return "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\video_page\\low.png";
    case RES_MIDDLE:
        return "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\video_page\\middle.png";
    case RES_TIMING_PHOTO_2:
        return "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\video_page\\timing_photo_2.png";
    case RES_TIMING_PHOTO_5:
        return "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\video_page\\timing_photo_5.png";
    case RES_TIMING_PHOTO_10:
        return "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\video_page\\timing_photo_10.png";
    case RES_SELETE:
        return "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\SELETE.png";
    case RES_UNLOCK:
        return "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\UNLOCK.png";
    case RES_UNLOCK_ON:
        return "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\unlock_on.png";
    case RES_VIDEO:
        return "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\VIDEO.png";
    case RES_VOLUMELOUDER_SOLID_1:
        return "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\volumeLouder_solid_1.png";
    case RES_VIDEO_PAUSE:
        return "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\video_pause.png";
    case RES_SKIP_NEXT:
        return "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\skip_next.png";
    case RES_SKIP_PREVIOUS:
        return "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\skip_previous.png";
    case RES_PLAY:
        return "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\play.png";
    case RES_VIDEO_PLAY:
        return "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\video_play.png";
    case RES_VOLUMEMUTE_SOLID_1:
        return "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\volumeMute_solid_1.png";
    case RES_SOFTWARE:
        return "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\video_page\\menu_icon\\software.png";
    case RES_LOCK_FLAG:
        return "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\lock_flag.png";
    case RES_CYCLIC_VIDEO_10:
        return "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\LY_UI\\rec\\rec_scan\\cyclic_video_10.png";
    case RES_CYCLIC_VIDEO_3:
        return "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\LY_UI\\rec\\rec_scan\\cyclic_video_3.png";
    case RES_CYCLIC_VIDEO_5:
        return "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\LY_UI\\rec\\rec_scan\\cyclic_video_5.png";
    case RES_MIC_OFF:
        return "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\LY_UI\\rec\\rec_scan\\mic_off.png";
    case RES_MIC_ON:
        return "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\LY_UI\\rec\\rec_scan\\mic_on.png";
    case RES_I_GRA_H:
        return "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\LY_UI\\rec\\rec_scan\\i_gra_h.png";
    case RES_I_GRA_M:
        return "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\LY_UI\\rec\\rec_scan\\i_gra_m.png";
    case RES_I_GRA_L:
        return "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\LY_UI\\rec\\rec_scan\\i_gra_l.png";
    case RES_BAT_0:
        return "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\LY_UI\\rec\\rec_scan\\bat_0.png";
    case RES_BAT_L:
        return "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\LY_UI\\rec\\rec_scan\\bat_l.png";
    case RES_BAT_HALF:
        return "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\LY_UI\\rec\\rec_scan\\bat_half.png";
    case RES_BAT_H:
        return "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\LY_UI\\rec\\rec_scan\\bat_h.png";
    case RES_CHAR:
        return "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\LY_UI\\rec\\rec_scan\\char.png";
    case RES_CARD_OFFLINE:
        return "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\LY_UI\\rec\\rec_scan\\card_offline.png";
    case RES_CARD_ONLINE:
        return "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\LY_UI\\rec\\rec_scan\\card_online.png";
    case RES_PARK:
        return "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\LY_UI\\rec\\rec_scan\\park.png";
    case RES_EXP_A3:
        return "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\LY_UI\\rec\\rec_scan\\exp_a3.png";
    case RES_EXP_A2:
        return "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\LY_UI\\rec\\rec_scan\\exp_a2.png";
    case RES_EXP_A1:
        return "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\LY_UI\\rec\\rec_scan\\exp_a1.png";
    case RES_EXP_A0:
        return "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\LY_UI\\rec\\rec_scan\\exp_a0.png";
    case RES_EXP_D1:
        return "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\LY_UI\\rec\\rec_scan\\exp_d1.png";
    case RES_EXP_D2:
        return "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\LY_UI\\rec\\rec_scan\\exp_d2.png";
    case RES_EXP_D3:
        return "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\LY_UI\\rec\\rec_scan\\exp_d3.png";
    case RES_AWB_AUTO:
        return "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\LY_UI\\photo\\photo_scan\\awb_auto.png";
    case RES_AWB_CLOUDY:
        return "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\LY_UI\\photo\\photo_scan\\awb_cloudy.png";
    case RES_AWB_FINE:
        return "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\LY_UI\\photo\\photo_scan\\awb_fine.png";
    case RES_AWB_FLUORESCENT_LAMP_1:
        return "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\LY_UI\\photo\\photo_scan\\awb_fluorescent_lamp.png";
    case RES_AWB_TUNGSTEN_LAMP:
        return "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\LY_UI\\photo\\photo_scan\\awb_tungsten_lamp.png";
    case RES_ISO_1:
        return "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\LY_UI\\photo\\photo_scan\\iso_1.png";
    case RES_ISO_2:
        return "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\LY_UI\\photo\\photo_scan\\iso_2.png";
    case RES_ISO_4:
        return "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\LY_UI\\photo\\photo_scan\\iso_4.png";
    case RES_ISO_AUTO:
        return "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\LY_UI\\photo\\photo_scan\\iso_auto.png";
    case RES_Q1:
        return "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\LY_UI\\photo\\photo_scan\\q1.png";
    case RES_Q2:
        return "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\LY_UI\\photo\\photo_scan\\q2.png";
    case RES_Q3:
        return "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\LY_UI\\photo\\photo_scan\\q3.png";
    case RES_DL2:
        return "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\LY_UI\\photo\\photo_scan\\dl2.png";
    case RES_DL5:
        return "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\LY_UI\\photo\\photo_scan\\dl5.png";
    case RES_DL10:
        return "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\LY_UI\\photo\\photo_scan\\dl10.png";
    case RES_SHAKE_OFF:
        return "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\LY_UI\\photo\\photo_scan\\shake_off.png";
    case RES_SHAKE_ON:
        return "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\LY_UI\\photo\\photo_scan\\shake_on.png";
    case RES_BAT_FULL:
        return "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\LY_UI\\rec\\rec_scan\\bat_full.png";
    case RES_FILE_DIR:
        return "A:\\wl83_soundbox\\ac792\\ui_prj\\new_ui\\import\\image\\file_dir.png";
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
    } else if (id >= 0x6E000000 && id < 0x6E100000) {
        snprintf(path_buf, sizeof(path_buf), "%s%x.%s", flash_dir, id, "png");
    } else if (id >= 0x6E100000 && id < 0x6E200000) {
        snprintf(path_buf, sizeof(path_buf), "%s%x.%s", sd_dir, id, "png");
    } else if (id >= 0x6F000000 && id < 0x6F100000) {
        snprintf(path_buf, sizeof(path_buf), "%s%x.%s", flash_dir, id, "jpg");
    } else if (id >= 0x6F100000 && id < 0x6F200000) {
        snprintf(path_buf, sizeof(path_buf), "%s%x.%s", sd_dir, id, "jpg");
    } else if (id >= 0x70000000 && id < 0x70100000) {
        snprintf(path_buf, sizeof(path_buf), "%s%x.%s", flash_dir, id, "jpeg");
    } else if (id >= 0x70100000 && id < 0x70200000) {
        snprintf(path_buf, sizeof(path_buf), "%s%x.%s", sd_dir, id, "jpeg");
    } else if (id >= 0x71000000 && id < 0x71100000) {
        snprintf(path_buf, sizeof(path_buf), "%s%x.%s", flash_dir, id, "bmp");
    } else if (id >= 0x71100000 && id < 0x71200000) {
        snprintf(path_buf, sizeof(path_buf), "%s%x.%s", sd_dir, id, "bmp");
    } else if (id >= 0x72000000 && id < 0x72100000) {
        snprintf(path_buf, sizeof(path_buf), "%s%x.%s", flash_dir, id, "svg");
    } else if (id >= 0x72100000 && id < 0x72200000) {
        snprintf(path_buf, sizeof(path_buf), "%s%x.%s", sd_dir, id, "svg");
    } else if (id >= 0x74000000 && id < 0x74100000) {
        snprintf(path_buf, sizeof(path_buf), "%s%x.%s", flash_dir, id, "zip");
    } else if (id >= 0x74100000 && id < 0x74200000) {
        snprintf(path_buf, sizeof(path_buf), "%s%x.%s", sd_dir, id, "zip");
    } else {
        return NULL;
    }
    return path_buf;
#endif
}

#endif
