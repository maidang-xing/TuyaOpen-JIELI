/**
 * @file lv_img2p5d.h
 *
 */

#ifndef LV_IMG2P5D_H
#define LV_IMG2P5D_H

#ifdef __cplusplus
extern "C" {
#endif

/*********************
 *      INCLUDES
 *********************/

#include "lvgl.h"

#if LV_USE_IMG2P5D

/*Testing of dependencies*/
#if LV_USE_GPU_JL_GPU2P5D == 0
#error "lv_obj2p5d: jlvg is required. Enable it in lv_conf.h (LV_USE_GPU_JL_GPU2P5D  1) "
#endif

#include "lv_obj2p5d.h"

/*********************
 *      DEFINES
 *********************/

/**********************
 *      TYPEDEFS
 **********************/
typedef struct _lv_img2p5d_t {
    lv_obj2p5d_t obj2p5d;
    const void *src;  /*Image source: Pointer to an array or a file or a symbol*/
} lv_img2p5d_t;

/**********************
 * GLOBAL PROTOTYPES
 **********************/
extern const lv_obj_class_t lv_img2p5d_class;
lv_obj_t *lv_img2p5d_create(lv_obj_t *parent);
void lv_img2p5d_set_src(lv_obj_t *obj, const void *src);

/**********************
 *      MACROS
 **********************/

#endif /*LV_USE_IMG2P5D*/

#ifdef __cplusplus
} /*extern "C"*/
#endif

#endif /*LV_IMG2P5D_H*/
