/**
 * @file lv_extra.c
 *
 */

/*********************
 *      INCLUDES
 *********************/
#include "../../lvgl.h"
#include "app_config.h"
/*********************
 *      DEFINES
 *********************/

/**********************
 *      TYPEDEFS
 **********************/

/**********************
 *  STATIC PROTOTYPES
 **********************/

/**********************
 *  STATIC VARIABLES
 **********************/

/**********************
 *      MACROS
 **********************/

/**********************
 *   GLOBAL FUNCTIONS
 **********************/

void lv_jl_extra_init(void)
{

#if LV_USE_RLE
    lv_rle_init();
    lv_gpu_rle_init(LV_USE_GPU_RLE);
#endif

#if LV_USE_JL_GUI_COMP

#if LV_USE_GUI_SCR
    gui_scr_init();
#endif
#if LV_USE_GUI_SCR_STACK
    gui_scr_stack_init();
#endif

#if LV_USE_JLJPEG
    lv_jlhw_jpeg_init();
#endif

#if LV_USE_JLFFMPEG
    puts("JLFFMPEG INITING...");
#if defined(CONFIG_JLFAT_ENABLE) && !defined(TCFG_JLFAT_SUPPORT_OVERSECTOR_RW_ENABLE)
    LV_LOG_WARN("please define TCFG_JLFAT_SUPPORT_OVERSECTOR_RW_ENABLE to ensure card reading performance!!!");
#endif
#if TCFG_SD0_ENABLE && (TCFG_SD0_DAT_WIDTH < 4 || TCFG_SD0_CLK < 48000000)
    LV_LOG_WARN("SD0 card performance is not configured to the optimal level!!!");
#endif
#if TCFG_SD1_ENABLE && (TCFG_SD1_DAT_WIDTH < 4 || TCFG_SD1_CLK < 48000000)
    LV_LOG_WARN("SD1 card performance is not configured to the optimal level!!!");
#endif
    lv_ffmpeg_init(LV_USE_JLFFMPEG_BUF_NUM, LVGL_Q_USER_TYPE_FFMPEG, UI_MSG_RPC_FUNC);
#endif

#endif
}

/**********************
 *   STATIC FUNCTIONS
 **********************/
