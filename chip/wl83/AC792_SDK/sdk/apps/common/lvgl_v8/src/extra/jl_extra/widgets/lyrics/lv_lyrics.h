/**
 * @file lv_lyrics.h
 *
 */

#ifndef LV_LYRICS_H
#define LV_LYRICS_H

#ifdef __cplusplus
extern "C" {
#endif

/*********************
 *      INCLUDES
 *********************/

#include "lvgl.h"

#if LV_USE_LYRICS

/*Testing of dependencies*/
#if LV_USE_GPU_JL_GPU2P5D == 0
#error "lv_lyrics: jlvg is required. Enable it in lv_conf.h (LV_USE_GPU_JL_GPU2P5D  1) "
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

#define ORIGINAL_FONTIMG_ENABLE 0   // TODO: 1: 保留最初未变换的 fontimg, 消耗额外的动态内存但是节省一步绘制原始图像流程; 0 反之(空间和时间置换)

#define PROJECTION_DEEP 500         // 投影深度 500~1000,值越小立体感越强

#define GLYPH_MAX_SEGMENTS 1024 // 字形最大的轮廓数，如果超了就要改大绘制修改字形

/**********************
 *      TYPEDEFS
 **********************/
typedef struct {
    // 字库引擎相关信息
    void *font_info;        // freetype or tinyttf(todo)

    // OBJ Extension info
    lv_opa_t opa;
    uint8_t blend_mode;
    lv_point_t abs_pos;     // 相对于父类的 position, 这个位置只能通过来 lv_lyrics_set_xxx 等 API 改变
    lv_point_t curr_pos;    // 相对于原始的 pos 的改变，比如变换等动作需要通过 lv_obj_set_pos 来微调
    int16_t x_angle;       // fontimg 的旋转角度: -3600 ~ 3600, 即 -360° ~ 360°
    int16_t y_angle;
    int16_t z_angle;
    uint16_t x_zoom;   // fontimg 的缩放因子: 255 为界限, 大于 256 放大; 小于 256 缩小;
    uint16_t y_zoom;
    lv_point_t angle_adj;       // 旋转变换的位置修正偏移
    lv_point_t zoom_adj;        // 缩放变换的位置修正偏移
    lv_style_t *default_style;  // 默认样式

    // GPU 纹理映射相关信息
    lv_img_dsc_t *original_fontimg; // 根据 ORIGINAL_FONTIMG_ENABLE 确认是否保留原始 fontimg, 即 original_fontimg->data
    lv_img_dsc_t *curr_fontimg;

    jlvg_point2_t tc_point;     // 变换中心: 这是一个比例范围点: 0.0f ~ 1.0f; 例如 (0.0f, 0.0f) 表示左上角, (1.0f, 1.0f) 表示右下角, 也可以在范围外
    jlvg_matrix_t tf_matrix_sw; // 用于软件计算的变换矩阵
    jlvg_matrix_t tf_matrix_hw; // 配置给 GPU 硬件的变换矩阵: 这个矩阵其实就是 tf_matrix_sw 的逆矩阵

    jlvg_color_t fill_color; //设置字形填充颜色
} lv_lyrics_info;

/**********************
 * GLOBAL PROTOTYPES
 **********************/

/* ------------------------------------------------------------------------------------*/
/**
 * @brief lv_lyrics_create
 *
 * @Params parent
 * @Params font_file
 * @Params font_size
 * @Params font_spacing 单位是1/64 像素点,0表示默认间距
 * @Params letter
 * @Params len
 *
 * @return
 */
/* ------------------------------------------------------------------------------------*/
lv_obj_t *lv_lyrics_create(lv_obj_t *parent, const char *font_file, uint16_t font_size, int font_spacing, uint32_t *letter, uint8_t len);

/* ------------------------------------------------------------------------------------*/
/**
 * @brief lv_lyrics_destructor
 *
 * @Params obj
 */
/* ------------------------------------------------------------------------------------*/
void lv_lyrics_destructor(lv_obj_t *obj);

/* ------------------------------------------------------------------------------------*/
/**
 * @brief lv_lyrics_fontimg_redarw 重绘 fontimg
 *
 * @Params obj
 *
 * @return
 */
/* ------------------------------------------------------------------------------------*/
bool lv_lyrics_fontimg_redarw(lv_obj_t *obj);

/* ------------------------------------------------------------------------------------*/
/**
 * @brief lv_lyrics_pos_adjust
 *
 * @Params obj
 * @Params new_x_adj
 * @Params new_y_adj
 */
/* ------------------------------------------------------------------------------------*/
void lv_lyrics_pos_adjust(lv_obj_t *obj, short new_x_adj, short new_y_adj);

/* ------------------------------------------------------------------------------------*/
/**
 * @brief lv_lyrics_set_x
 *
 * @Params obj
 * @Params x
 */
/* ------------------------------------------------------------------------------------*/
void lv_lyrics_set_x(lv_obj_t *obj, short x);

/* ------------------------------------------------------------------------------------*/
/**
 * @brief lv_lyrics_set_y
 *
 * @Params obj
 * @Params y
 */
/* ------------------------------------------------------------------------------------*/
void lv_lyrics_set_y(lv_obj_t *obj, short y);

/* ------------------------------------------------------------------------------------*/
/**
 * @brief lv_lyrics_set_pos
 *
 * @Params obj
 * @Params x
 * @Params y
 */
/* ------------------------------------------------------------------------------------*/
void lv_lyrics_set_pos(lv_obj_t *obj, short x, short y);

/* ------------------------------------------------------------------------------------*/
/**
 * @brief lv_lyrics_set_zoom  只是替换了变换因子，需要在下一次调用 lv_lyrics_fontimg_redarw 时才会生效
 *
 * @Params obj
 * @Params x_zoom
 * @Params y_zoom
 */
/* ------------------------------------------------------------------------------------*/
void lv_lyrics_set_zoom(lv_obj_t *obj, uint16_t x_zoom, uint16_t y_zoom);

/* ------------------------------------------------------------------------------------*/
/**
 * @brief lv_lyrics_set_rotation
 *
 * @Params obj
 * @Params x_angle
 * @Params y_angle
 * @Params z_angle
 */
/* ------------------------------------------------------------------------------------*/
void lv_lyrics_set_rotation(lv_obj_t *obj, int16_t x_angle, int16_t y_angle, int16_t z_angle);

/* ------------------------------------------------------------------------------------*/
/**
 * @brief lv_lyrics_set_color
 *
 * @Params color
 */
/* ------------------------------------------------------------------------------------*/
void lv_lyrics_set_color(lv_obj_t *obj, jlvg_color_t color);

/* ------------------------------------------------------------------------------------*/
/**
 * @brief lv_lyrics_set_tc_point
 *
 * @Params tc_point
 */
/* ------------------------------------------------------------------------------------*/
void lv_lyrics_set_tc_point(lv_obj_t *obj, jlvg_point2_t tc_point);
/**********************
 *      MACROS
 **********************/

#endif /*LV_USE_LYRICS*/

#ifdef __cplusplus
} /*extern "C"*/
#endif

#endif /*LV_FONT2P5D_H*/
