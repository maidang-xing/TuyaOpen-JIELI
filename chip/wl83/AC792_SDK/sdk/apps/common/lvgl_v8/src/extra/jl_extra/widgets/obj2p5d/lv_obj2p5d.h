/**
 * @file lv_obj2p5d.h
 *
 */

#ifndef LV_OBJ2P5D_H
#define LV_OBJ2P5D_H

#ifdef __cplusplus
extern "C" {
#endif

/*********************
 *      INCLUDES
 *********************/

#include "lvgl.h"

#if LV_USE_OBJ2P5D

/*Testing of dependencies*/
#if LV_USE_GPU_JL_GPU2P5D == 0
#error "lv_obj2p5d: jlvg is required. Enable it in lv_conf.h (LV_USE_GPU_JL_GPU2P5D  1) "
#endif

#include "asm/gpu/jlvg.h"
#include "asm/jlgpu_driver.h"

extern jlvg_t *g_gpu2p5d;   // in lv_gpu_jl_gpu2p5d.c

/*********************
 *      DEFINES
 *********************/
#if LV_COLOR_DEPTH == 8
#error "Can't use 2.5D GPU with LV_COLOR_DEPTH == 8"
#endif

#if LV_COLOR_DEPTH == 16
#define LV_GPU_COLOR_FORMAT         VGHW_FORMAT_RGB565
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

/**********************
 *      TYPEDEFS
 **********************/
typedef struct _lv_vector_t {
    float x;
    float y;
    float z;
} lv_vector_t;

typedef struct _lv_fpoint_t {
    float x;
    float y;
} lv_fpoint_t;

typedef struct _lv_obj2p5d_t {
    lv_img_t img;

    lv_opa_t opa;
    lv_blend_mode_t blend_mode;

    uint16_t zoom;
    int16_t angle;
    lv_vector_t axis3;  // 相对于起始坐标区域内的三维空间旋转轴, 变换过程中恒定不变
    lv_point_t pivot2; // 相对于起始坐标区域内的三维空间旋转轴的原点，对于二维图像，该变换点需要位于 X-Y 平面内，且变换过程中在显存中的绝对位置恒定不变
    lv_point_t pos2;    // 相对于父类的 position
    lv_fpoint_t pivot2_final;  // 变换之后的变换原点的最终位置
    /** Obj transforms the 2D drawing actions of img */
    // 不同类型的控件(img、font、...)在进行 2.5D 变换前都需要先将 OBJ 转换成 IMG 对象
    const lv_img_dsc_t *(*obj2p5d2img_2ddraw)(const void *, float rotation, float scale_x, float scale_y);
} lv_obj2p5d_t;

/**********************
 * GLOBAL PROTOTYPES
 **********************/
void lv_obj2p5d_set_opa(lv_obj_t *obj, lv_opa_t opa);
void lv_obj2p5d_set_blend_mode(lv_obj_t *obj, lv_blend_mode_t blend_mode);
void lv_obj2p5d_set_angle(lv_obj_t *obj, int16_t angle);
void lv_obj2p5d_set_zoom(lv_obj_t *obj, uint16_t zoom);
void lv_obj2p5d_set_x(lv_obj_t *obj, lv_coord_t x);
void lv_obj2p5d_set_y(lv_obj_t *obj, lv_coord_t y);
void lv_obj2p5d_set_pos(lv_obj_t *obj, lv_coord_t x, lv_coord_t y);
void lv_obj2p5d_set_axis(lv_obj_t *obj, float x, float y, float z);
void lv_obj2p5d_set_pivot(lv_obj_t *obj, float x, float y);

void lv_obj2p5d_get_x(lv_obj_t *obj, lv_coord_t *x);
void lv_obj2p5d_get_y(lv_obj_t *obj, lv_coord_t *y);
void lv_obj2p5d_get_pos(lv_obj_t *obj, lv_coord_t *x, lv_coord_t *y);

/**********************
 *      MACROS
 **********************/

#endif /*LV_USE_OBJ2P5D*/

#ifdef __cplusplus
} /*extern "C"*/
#endif

#endif /*LV_OBJ2P5D_H*/
