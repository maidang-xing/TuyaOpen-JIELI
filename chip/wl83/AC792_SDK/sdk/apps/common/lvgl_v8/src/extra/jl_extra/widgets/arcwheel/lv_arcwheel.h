/**
 * @file lv_arcwheel.h
 */

#ifndef LV_ARCWHEEL_H
#define LV_ARCWHEEL_H

#ifdef __cplusplus
extern "C" {
#endif

/*********************
 *      INCLUDES
 *********************/
#include "lvgl.h"

#if LV_USE_ARCWHEEL != 0

#if LV_USE_IMG == 0
#error "lv_arcwheel: lv_img is required. Enable it in lv_conf.h (LV_USE_IMG 1)"
#endif

/*********************
 *      DEFINES
 *********************/

/**********************
 *      TYPEDEFS
 **********************/

typedef enum {
    LV_ARCWHEEL_STYLE_SLIDE_SCALE,  /**< 滑动缩放效果（默认） */
    LV_ARCWHEEL_STYLE_CUSTOM,       /**< 自定义效果 */
} lv_arcwheel_style_t;

typedef enum {
    LV_ARCWHEEL_SCROLL_DIR_HORIZONTAL,  /**< 水平滑动模式（默认） */
    LV_ARCWHEEL_SCROLL_DIR_VERTICAL,    /**< 垂直滑动模式 */
} lv_arcwheel_scroll_dir_t;

typedef union {
    struct {
        uint16_t zoom_min;
        uint16_t zoom_max;
    } slide_scale;

    struct {
        lv_coord_t nop1;
        lv_coord_t nop2;
        lv_coord_t nop3;
        lv_coord_t nop4;
    } custom;
} lv_arcwheel_transform_param_t;

/**
 * @brief arcwheel item 的转换回调函数
 * @param arcwheel arcwheel 容器对象
 * @param item 当前正在转换的子项对象
 * @param angle 该子项当前的显示角度（相对角度，已应用 angle_offset）
 * @param item_pos 子项的位置（输入/输出参数，回调可以修改）
 * @return 缩放值（zoom）
 */
typedef uint16_t (*lv_arcwheel_item_transform_cb_t)(
    const lv_obj_t *arcwheel,
    const lv_obj_t *item,
    lv_coord_t angle,
    lv_point_t *item_pos
);

typedef struct {
    lv_obj_t obj;

    lv_arcwheel_item_transform_cb_t item_transform_cb;  /* 转换回调函数 */
    lv_arcwheel_style_t style;                          /* 当前样式类型 */
    lv_arcwheel_scroll_dir_t scroll_dir;                /* 滑动方向模式 */

    lv_coord_t current_angle;                           /* 当前旋转角度 */
    lv_coord_t friction_factor;                         /* 摩擦系数 */

    uint16_t visible_count;                             /* 可见子项数量 */
    lv_coord_t snap_factor;                             /* 吸附强度系数 */

    lv_coord_t radius_x;                                /* 椭圆 X 轴半径 */
    lv_coord_t radius_y;                                /* 椭圆 Y 轴半径 */

    /* 角度偏移量，用于控制子项的起始方向（LVGL标准坐标系：0°=右侧，90°=下方，180°=左侧，270°=上方） */
    lv_coord_t angle_offset;
    lv_coord_t angle_step;

    lv_coord_t px_per_angle;                           /* 滑动灵敏度 */

    lv_arcwheel_transform_param_t transform_param;      /* 转换参数 */

    struct {
        lv_timer_t *scroll_tmr;
        lv_coord_t momentum;
    } scroll;

    bool is_loop;                                       /* 是否循环模式 */
    bool is_snap;                                       /* 是否启用吸附 */
    bool _is_init;

    struct {
        lv_anim_t anim;
        bool is_animating;
    } snap;
} lv_arcwheel_t;

typedef struct {
    lv_img_t img;
} lv_arcwheel_item_t;

extern const lv_obj_class_t lv_arcwheel_class;
extern const lv_obj_class_t lv_arcwheel_item_class;

/**********************
 * GLOBAL PROTOTYPES
 **********************/

lv_obj_t *lv_arcwheel_create(lv_obj_t *parent);
lv_obj_t *lv_arcwheel_add_item(lv_obj_t *wheel, const void *icon);

void lv_arcwheel_set_radius(lv_obj_t *obj, lv_coord_t radius_x, lv_coord_t radius_y);
void lv_arcwheel_set_px_per_angle(lv_obj_t *obj, lv_coord_t px_per_angle);
void lv_arcwheel_set_loop(lv_obj_t *obj, bool enabled);
void lv_arcwheel_set_visible_count(lv_obj_t *obj, uint16_t count);
void lv_arcwheel_set_angle_offset(lv_obj_t *obj, lv_coord_t offset);
void lv_arcwheel_rotate_to_angle(lv_obj_t *obj, lv_coord_t angle, bool anim, uint32_t speed);
void lv_arcwheel_stop_rotate(lv_obj_t *obj, bool snap_to_nearest, uint32_t speed);
void lv_arcwheel_item_set_src(lv_obj_t *item, const void *src);
void lv_arcwheel_set_style(lv_obj_t *obj, lv_arcwheel_style_t style,
                           lv_arcwheel_transform_param_t *params);
void lv_arcwheel_set_item_transform_cb(lv_obj_t *obj, lv_arcwheel_item_transform_cb_t transform_cb,
                                       lv_arcwheel_transform_param_t *params);
void lv_arcwheel_set_friction_factor(lv_obj_t *obj, lv_coord_t factor);
void lv_arcwheel_set_snap_factor(lv_obj_t *obj, lv_coord_t factor);
void lv_arcwheel_set_snap(lv_obj_t *obj, bool enabled);
void lv_arcwheel_set_scroll_direction(lv_obj_t *obj, lv_arcwheel_scroll_dir_t dir);

lv_coord_t lv_arcwheel_get_radius_x(lv_obj_t *obj);
lv_coord_t lv_arcwheel_get_radius_y(lv_obj_t *obj);
lv_coord_t lv_arcwheel_get_current_angle(lv_obj_t *obj);
lv_coord_t lv_arcwheel_get_angle_offset(lv_obj_t *obj);
uint16_t lv_arcwheel_get_item_count(lv_obj_t *obj);
uint16_t lv_arcwheel_get_visible_count(lv_obj_t *obj);
lv_coord_t lv_arcwheel_get_px_per_angle(lv_obj_t *obj);
bool lv_arcwheel_is_loop(lv_obj_t *obj);
lv_arcwheel_style_t lv_arcwheel_get_style(lv_obj_t *obj);
lv_arcwheel_transform_param_t *lv_arcwheel_get_transform_params(lv_obj_t *obj);
lv_coord_t lv_arcwheel_get_friction_factor(lv_obj_t *obj);
lv_coord_t lv_arcwheel_get_snap_factor(lv_obj_t *obj);
bool lv_arcwheel_is_snap(lv_obj_t *obj);
lv_arcwheel_scroll_dir_t lv_arcwheel_get_scroll_direction(lv_obj_t *obj);

/**********************
 *      MACROS
 **********************/

#endif /*LV_USE_ARCWHEEL*/

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /*LV_ARCWHEEL_H*/

