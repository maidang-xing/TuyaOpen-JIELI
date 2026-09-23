/**
 * @file lv_curvemenu.h
 *
 */

#ifndef LV_CURVEMENU_H
#define LV_CURVEMENU_H

#ifdef __cplusplus
extern "C" {
#endif

/*********************
 *      INCLUDES
 *********************/
#include "lvgl.h"

#if LV_USE_CURVEMENU != 0

/*Testing of dependencies*/
#if LV_USE_IMG == 0
#error "lv_curvemenu: lv_img is required. Enable it in lv_conf.h (LV_USE_IMG 1)"
#endif
#if LV_USE_LABEL == 0
#error "lv_curvemenu: lv_label is required. Enable it in lv_conf.h (LV_USE_LABEL 1)"
#endif

/*********************
 *      DEFINES
 *********************/

/**********************
 *      TYPEDEFS
 **********************/

typedef struct {
    lv_obj_t obj;
    lv_coord_t angle_start;     /*可视区域起始角度*/
    lv_coord_t angle_end;       /*可视区域结束角度*/
    lv_coord_t angle;           /*当前角度*/
    lv_coord_t angle_step;      /*菜单项之间的角度差*/
    lv_coord_t radius;          /*菜单半径*/
    lv_coord_t px_per_angle;    /*每度对应的像素*/
    lv_coord_t col_num;         /*列数*/
    lv_coord_t
    cr;              /*圆心半径(圆心到菜单控件的距离，实际半径为菜单半径加上圆心半径)*/
    bool _is_init;              /*是否初始化*/

    struct {
        lv_coord_t ver_momentum;

        lv_timer_t *scroll_tmr;
    } scroll;

    lv_obj_t **layout_buf;
    uint32_t layout_buf_cap;

} lv_curvemenu_t;

typedef struct {
    lv_obj_t obj;
    bool is_hide;
    lv_obj_t *img;
    lv_obj_t *label;
} lv_curvemenu_btn_t;

extern const lv_obj_class_t lv_curvemenu_class;
extern const lv_obj_class_t lv_curvemenu_btn_class;

/**********************
 * GLOBAL PROTOTYPES
 **********************/

/**
 * Create a curve menu objects
 * @param parent pointer to the parent object
 * @return lv_obj_t* pointer to the created curve menu object
 */
lv_obj_t *lv_curvemenu_create(lv_obj_t *parent);

/**
 * Add a button to the curve menu
 * @param parent pointer to the parent object
 * @param icon pointer to an image source (a C array or path to a file)
 * @return lv_obj_t* pointer to the created button object
 */
lv_obj_t *lv_curvemenu_add_btn(lv_obj_t *parent, const void *icon);

/**
 * Add a button with text to the curve menu
 * @param parent pointer to the parent object
 * @param icon pointer to an image source (a C array or path to a file)
 * @param text pointer to the text, set NULL for no text
 * @return lv_obj_t* pointer to the created button object
 */
lv_obj_t *lv_curvemenu_add_btn_with_text(lv_obj_t *parent, const void *icon, const char *text);

/*=====================
 * Setter functions
 *====================*/

/**
 * Set the radius of the curve menu
 * @param obj
 * @param radius
 */
void lv_curvemenu_set_radius(lv_obj_t *obj, lv_coord_t radius);

void lv_curvemenu_set_angle_step(lv_obj_t *obj, lv_coord_t angle_step);

void lv_curvemenu_set_start_angle(lv_obj_t *obj, lv_coord_t start);

void lv_curvemenu_set_end_angle(lv_obj_t *obj, lv_coord_t end);

void lv_curvemenu_set_angles(lv_obj_t *obj, lv_coord_t start, lv_coord_t end);

void lv_curvemenu_set_col_num(lv_obj_t *obj, lv_coord_t col_num);

void lv_curvemenu_set_cr(lv_obj_t *obj, lv_coord_t cr);

void lv_curvemenu_btn_set_hide(lv_obj_t *btn, bool is_hide);

void lv_curvemenu_btn_set_zoom(lv_obj_t *btn, uint16_t zoom);

void lv_curvemenu_btn_set_text(lv_obj_t *btn, const char *text);

/*=====================
 * Getter functions
 *====================*/

lv_coord_t lv_curvemenu_get_radius(lv_obj_t *obj);

lv_coord_t lv_curvemenu_get_angle_step(lv_obj_t *obj);

lv_coord_t lv_curvemenu_get_start_angle(lv_obj_t *obj);

lv_coord_t lv_curvemenu_get_end_angle(lv_obj_t *obj);

lv_coord_t lv_curvemenu_get_col_num(lv_obj_t *obj);

lv_coord_t lv_curvemenu_get_cr(lv_obj_t *obj);

bool lv_curvemenu_btn_get_hide(lv_obj_t *btn);

uint16_t lv_curvemenu_btn_get_zoom(lv_obj_t *btn);

/*=====================
 * Other functions
 *====================*/

/**********************
 *      MACROS
 **********************/

#endif /*LV_USE_CURVEMENU*/

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /*LV_CURVEMENU_H*/

