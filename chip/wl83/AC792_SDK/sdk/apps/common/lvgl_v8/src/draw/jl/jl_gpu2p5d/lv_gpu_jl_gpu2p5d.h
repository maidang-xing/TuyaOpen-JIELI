/**
 * @file lv_gpu_jl_gpu2p5d.h
 *
 */

#ifndef LV_GPU_JL_GPU2P5D_H
#define LV_GPU_JL_GPU2P5D_H

#ifdef __cplusplus
extern "C" {
#endif

/*********************
 *      INCLUDES
 *********************/
#include "../../../misc/lv_color.h"
#include "../../../hal/lv_hal_disp.h"
#include "../../sw/lv_draw_sw.h"
#include "../../../core/lv_refr.h"

#if LV_USE_GPU_JL_GPU2P5D

#include "asm/gpu/jlvg.h"
#include "asm/jlgpu_driver.h"

/*********************
 *      DEFINES
 *********************/

#if LV_COLOR_DEPTH == 8
#error "Can't use 2.5D GPU with LV_COLOR_DEPTH == 8"
#endif

#if LV_COLOR_DEPTH == 16
#if LV_COLOR_DEPTH_EXTEN == 24
#define LV_GPU_COLOR_FORMAT         VGHW_FORMAT_ARGB8565
#else
#define LV_GPU_COLOR_FORMAT         VGHW_FORMAT_RGB565
#endif
#define LV_GPU_COLOR_ALPHA_FORMAT   VGHW_FORMAT_ARGB8565
#elif LV_COLOR_DEPTH == 24
#define LV_GPU_COLOR_FORMAT         VGHW_FORMAT_RGB888
#define LV_GPU_COLOR_ALPHA_FORMAT   VGHW_FORMAT_ARGB8888
#elif LV_COLOR_DEPTH == 32
#define LV_GPU_COLOR_FORMAT         VGHW_FORMAT_ARGB8888
#define LV_GPU_COLOR_ALPHA_FORMAT   VGHW_FORMAT_ARGB8888
#else
/*Can't use GPU with other formats*/
#endif

#define LV_JL_GPU_MIN_AREA_SIZE 1024    // 交付给 GPU 渲染的最小区域大小，小于这个大小则不采用 GPU，太小的区域再使用 GPU 渲染反而会导致耗时加长

#define JLVG_DRAW_FULL_FB_ENABLE 0      // 使用小窗绘制速度会更快，默认关闭这个宏，调试时可以观察到 vg 绘制的实际区域，而非 LVGL 的裁剪区域
#define JLVG_DRAW_WIN_RES_WIDTH 4       // VG 窗口绘制预留宽度, (TODO)，可解决小窗绘制时，vg 绘制区域和 LVGL 裁剪区域的边缘混合问题

/**********************
 *      TYPEDEFS
 **********************/
typedef lv_draw_sw_ctx_t lv_draw_jl_gpu2p5d_ctx_t;

struct _lv_disp_drv_t;

/**********************
 * GLOBAL PROTOTYPES
 **********************/
extern jlvg_t *g_gpu2p5d;

/**
 * Turn on the peripheral and set output color mode, this only needs to be done once
 */
void lv_draw_jl_gpu2p5d_init(void);

void lv_draw_jl_gpu2p5d_ctx_init(struct _lv_disp_drv_t *drv, lv_draw_ctx_t *draw_ctx);

void lv_draw_jl_gpu2p5d_ctx_deinit(struct _lv_disp_drv_t *drv, lv_draw_ctx_t *draw_ctx);

void /* LV_ATTRIBUTE_FAST_MEM */ lv_draw_jl_gpu2p5d_rect(lv_draw_ctx_t *draw_ctx, const lv_draw_rect_dsc_t *dsc, const lv_area_t *coords);

void /* LV_ATTRIBUTE_FAST_MEM */ lv_draw_jl_gpu2p5d_bg(lv_draw_ctx_t *draw_ctx, const lv_draw_rect_dsc_t *dsc, const lv_area_t *coords);

void /* LV_ATTRIBUTE_FAST_MEM */ lv_draw_jl_gpu2p5d_line(struct _lv_draw_ctx_t *draw_ctx, const lv_draw_line_dsc_t *dsc,
        const lv_point_t *point1, const lv_point_t *point2);

void /* LV_ATTRIBUTE_FAST_MEM */ lv_draw_jl_gpu2p5d_arc(lv_draw_ctx_t *draw_ctx, const lv_draw_arc_dsc_t *dsc, const lv_point_t *center,
        uint16_t radius, uint16_t start_angle, uint16_t end_angle);

void /* LV_ATTRIBUTE_FAST_MEM */ lv_draw_jl_gpu2p5d_polygon(lv_draw_ctx_t *draw_ctx, const lv_draw_rect_dsc_t *draw_dsc, const lv_point_t *points, uint16_t point_cnt);

void /* LV_ATTRIBUTE_FAST_MEM */ lv_draw_jl_gpu2p5d_letter(lv_draw_ctx_t *draw_ctx, const lv_draw_label_dsc_t *dsc, \
        const lv_point_t *pos_p, uint32_t letter);

void /* LV_ATTRIBUTE_FAST_MEM */ lv_draw_jl_gpu2p5d_img_decoded(struct _lv_draw_ctx_t *draw_ctx,
        const lv_draw_img_dsc_t *dsc,
        const lv_area_t *coords, const uint8_t *src_buf,
        lv_img_cf_t cf);

// common api
jlvg_hw_imageformat_t lv_img_jl_gpu2p5d_get_color_format(lv_img_cf_t cf, bool *cf_flag);
uint8_t lv_jl_gpu2p5d_get_blend_mode(lv_blend_mode_t lv_blend_mode, bool *mode_flag);
uint8_t lv_jl_gpu2p5d_get_path_type(lv_font_path_type_t lv_font_path_type, bool *path_flag);
void lv_jl_gpu2p5d_flush_inv_dcache(uint8_t *buf, uint32_t w, uint32_t h, uint32_t stride, uint8_t color_depth);
void lv_jl_gpu2p5d_flush_dcache(uint8_t *buf, uint32_t w, uint32_t h, uint32_t stride, uint8_t color_depth);
bool lv_jl_gpu2p5d_cheak_draw_ctx_buf(uint8_t *buf);
/**********************
 *      MACROS
 **********************/

#endif  /*LV_USE_GPU_JL_GPU2P5D*/

#ifdef __cplusplus
} /*extern "C"*/
#endif

#endif /*LV_GPU_JL_GPU2P5D_H*/
