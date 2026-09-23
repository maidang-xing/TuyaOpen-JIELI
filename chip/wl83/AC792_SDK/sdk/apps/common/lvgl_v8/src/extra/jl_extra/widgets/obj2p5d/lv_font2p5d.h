/**
 * @file lv_font2p5d.h
 *
 */

#ifndef LV_FONT2P5D_H
#define LV_FONT2P5D_H

#ifdef __cplusplus
extern "C" {
#endif

/*********************
 *      INCLUDES
 *********************/

#include "lvgl.h"

#if LV_USE_FONT2P5D

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
typedef struct _lv_font2p5d_t {
    lv_obj2p5d_t obj2p5d;
    lv_font_glyph_dsc_t glyph;
    uint32_t letter;
    lv_color_t color;
} lv_font2p5d_t;

/**********************
 * GLOBAL PROTOTYPES
 **********************/
extern const lv_obj_class_t lv_font2p5d_class;
lv_obj_t *lv_font2p5d_create(lv_obj_t *parent);
bool lv_font2p5d_set_letter(lv_obj_t *obj, const lv_font_t *font_p, const uint32_t letter);

/**********************
 *      MACROS
 **********************/

#endif /*LV_USE_FONT2P5D*/

#ifdef __cplusplus
} /*extern "C"*/
#endif

#endif /*LV_FONT2P5D_H*/
