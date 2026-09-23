/**
 * @file lv_gpu_jl.h
 *
 */

#ifndef LV_GPU_JL_H
#define LV_GPU_JL_H

#ifdef __cplusplus
extern "C" {
#endif

#if LV_USE_GPU_JL

/*********************
 *      INCLUDES
 *********************/
#include "../sw/lv_draw_sw.h"

#if LV_USE_GPU_JL_DMA2D
#include "jl_dma2d/lv_gpu_jl_dma2d.h"
#endif

#if LV_USE_GPU_JL_GPU2P5D
#include "jl_gpu2p5d/lv_gpu_jl_gpu2p5d.h"
#endif

/*********************
 *      DEFINES
 *********************/


/**********************
 *      TYPEDEFS
 **********************/
typedef lv_draw_sw_ctx_t lv_draw_jl_ctx_t;

/**********************
 * GLOBAL PROTOTYPES
 **********************/

void lv_draw_jl_init(void);

void lv_draw_jl_ctx_init(struct _lv_disp_drv_t *drv, lv_draw_ctx_t *draw_ctx);

void lv_draw_jl_ctx_deinit(struct _lv_disp_drv_t *drv, lv_draw_ctx_t *draw_ctx);

/**********************
 *      MACROS
 **********************/

#endif  /*LV_USE_GPU_JL*/

#ifdef __cplusplus
} /*extern "C"*/
#endif

#endif /*LV_GPU_JL_H*/
