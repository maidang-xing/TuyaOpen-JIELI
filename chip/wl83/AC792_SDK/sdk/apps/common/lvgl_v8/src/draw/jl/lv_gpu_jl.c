/**
 * @file lv_gpu_jl.c
 *
 */

/*********************
 *      INCLUDES
 *********************/
#include "../lv_draw.h"
#include "lv_gpu_jl.h"

#if LV_USE_GPU_JL

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
void lv_draw_jl_init(void)
{
#if LV_USE_GPU_JL_DMA2D
    lv_draw_jl_dma2d_init();
#endif

#if LV_USE_GPU_JL_GPU2P5D
    lv_draw_jl_gpu2p5d_init();
#endif
}

void lv_draw_jl_ctx_init(struct _lv_disp_drv_t *drv, lv_draw_ctx_t *draw_ctx)
{
    lv_draw_sw_init_ctx(drv, draw_ctx);

#if LV_USE_GPU_JL_DMA2D
    lv_draw_jl_dma2d_ctx_init(drv, draw_ctx);
    LV_LOG_USER("Renderer: LV_USE_GPU_JL_DMA2D enabled.");
#endif

#if LV_USE_GPU_JL_GPU2P5D
    lv_draw_jl_gpu2p5d_ctx_init(drv, draw_ctx);
    LV_LOG_USER("Renderer: LV_USE_GPU_JL_GPU2P5D enabled.");
#endif
}

void lv_draw_jl_ctx_deinit(struct _lv_disp_drv_t *drv, lv_draw_ctx_t *draw_ctx)
{
#if LV_USE_GPU_JL_DMA2D
    lv_draw_jl_dma2d_ctx_deinit(drv, draw_ctx);
    LV_LOG_USER("Renderer: LV_USE_GPU_JL_DMA2D disenabled.");
#endif

#if LV_USE_GPU_JL_GPU2P5D
    lv_draw_jl_gpu2p5d_ctx_deinit(drv, draw_ctx);
    LV_LOG_USER("Renderer: LV_USE_GPU_JL_GPU2P5D disenabled.");
#endif
}

/**********************
 *   STATIC FUNCTIONS
 **********************/

#endif /*LV_USE_GPU_JL*/
