/**
 * @file lv_gpu_jl_gpu2p5d.c
 *
 */

/*********************
 *      INCLUDES
 *********************/
#include "../../lv_draw.h"
#include "lv_gpu_jl_gpu2p5d.h"

#if LV_USE_GPU_JL_GPU2P5D

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
jlvg_t *g_gpu2p5d = NULL;

void lv_draw_jl_gpu2p5d_init(void)
{
    /* JL gpu hw init */
    g_gpu2p5d = jlvg_create();
}

void lv_draw_jl_gpu2p5d_ctx_init(lv_disp_drv_t *drv, lv_draw_ctx_t *draw_ctx)
{
    lv_draw_jl_gpu2p5d_ctx_t *gpu2p5d_draw_ctx = (lv_draw_jl_gpu2p5d_ctx_t *)draw_ctx;

#if LV_USE_JL_GPU2P5D_DRAW_RECT
    gpu2p5d_draw_ctx->base_draw.draw_rect = lv_draw_jl_gpu2p5d_rect;
    gpu2p5d_draw_ctx->base_draw.draw_bg = lv_draw_jl_gpu2p5d_bg;
#endif

#if LV_USE_JL_GPU2P5D_DRAW_LINE
    gpu2p5d_draw_ctx->base_draw.draw_line = lv_draw_jl_gpu2p5d_line;
#endif

#if LV_USE_JL_GPU2P5D_DRAW_ARC
    gpu2p5d_draw_ctx->base_draw.draw_arc = lv_draw_jl_gpu2p5d_arc;
#endif

#if LV_USE_JL_GPU2P5D_DRAW_POLYGON
    gpu2p5d_draw_ctx->base_draw.draw_polygon = lv_draw_jl_gpu2p5d_polygon;
#endif

#if LV_USE_JL_GPU2P5D_DRAW_LETTER
    gpu2p5d_draw_ctx->base_draw.draw_letter = lv_draw_jl_gpu2p5d_letter;
#endif

#if LV_USE_JL_GPU2P5D_DRAW_IMG
    gpu2p5d_draw_ctx->base_draw.draw_img_decoded = lv_draw_jl_gpu2p5d_img_decoded;
#endif
}

void lv_draw_jl_gpu2p5d_ctx_deinit(lv_disp_drv_t *drv, lv_draw_ctx_t *draw_ctx)
{
    LV_UNUSED(drv);
    LV_UNUSED(draw_ctx);
}

/**********************
 *   STATIC FUNCTIONS
 **********************/

#endif /*LV_USE_GPU_JL_GPU2P5D*/
