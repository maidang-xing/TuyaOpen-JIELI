/**
 * @file lv_gpu_jl_gpu2p5d_line.c
 *
 */

/*********************
 *      INCLUDES
 *********************/
#include "lv_gpu_jl_gpu2p5d.h"

#if LV_USE_GPU_JL_GPU2P5D
#if LV_USE_JL_GPU2P5D_DRAW_LINE
/*********************
 *      DEFINES
 *********************/

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

/**********************
 *      TYPEDEFS
 **********************/

/**********************
 *  STATIC PROTOTYPES
 **********************/

static void lv_draw_jl_gpu2p5d_line_endpoints_path_fill(jlvg_path_t *path, jlvg_point2_t point, float radius);

/**********************
 *  STATIC VARIABLES
 **********************/

/**********************
 *      MACROS
 **********************/

/**********************
 *   GLOBAL FUNCTIONS
 **********************/

void lv_draw_jl_gpu2p5d_line(struct _lv_draw_ctx_t *draw_ctx, const lv_draw_line_dsc_t *dsc,
                             const lv_point_t *point1, const lv_point_t *point2)
{
    //printf("%s()", __func__);
    if (dsc->width == 0) {
        return;
    }
    if (dsc->opa <= LV_OPA_MIN) {
        return;
    }

    if (point1->x == point2->x && point1->y == point2->y) {
        return;
    }

    lv_coord_t radius_i = (dsc->width / 2) + 1; // 线宽的一半作为半径
    lv_area_t rel_coords;
    rel_coords.x1 = LV_MIN(point1->x, point2->x) - radius_i;
    rel_coords.x2 = LV_MAX(point1->x, point2->x) + radius_i;
    rel_coords.y1 = LV_MIN(point1->y, point2->y) - radius_i;
    rel_coords.y2 = LV_MAX(point1->y, point2->y) + radius_i;

    // 计算相对于实际的绘制buff进行偏移
    lv_area_move(&rel_coords, -draw_ctx->buf_area->x1, -draw_ctx->buf_area->y1);    // 重新确定在显存中的相对位置

    lv_area_t rel_clip_area;
    lv_area_copy(&rel_clip_area, draw_ctx->clip_area);
    lv_area_move(&rel_clip_area, -draw_ctx->buf_area->x1, -draw_ctx->buf_area->y1);    // 重新确定在显存中的相对位置

    lv_area_t blend_area;   //这个区域无论是帧buff还是行buff都是相对的新的绘制区域
    if (!_lv_area_intersect(&blend_area, &rel_coords, &rel_clip_area)) {
        return;   // 意味着软件也不需要渲染动作
    }
    //printf("blend_area (x1,y1) = (%d,%d); (x2,y2) = (%d,%d).", blend_area.x1, blend_area.y1, blend_area.x2, blend_area.y2);

    lv_point_t rel_point1 = { point1->x - draw_ctx->buf_area->x1, point1->y - draw_ctx->buf_area->y1 };
    lv_point_t rel_point2 = { point2->x - draw_ctx->buf_area->x1, point2->y - draw_ctx->buf_area->y1 };
    //printf("rel_point1 = (x, y) = (%d, %d); rel_point2 = (x, y) = (%d, %d).", rel_point1.x, rel_point1.y, rel_point2.x, rel_point2.y);
    //printf("round_start = %d; round_end = %d.", dsc->round_start, dsc->round_end);

    bool done = false;
    bool has_mask = lv_draw_mask_is_any(&rel_coords);
    bool is_dashed = (dsc->dash_width && dsc->dash_gap);
    bool mode_flag;
    uint8_t blend_mode = lv_jl_gpu2p5d_get_blend_mode(dsc->blend_mode, &mode_flag);   //根据图像的混合模式获取 VG 配置的混合模式
    if ((has_mask == true) || (is_dashed == true) || (mode_flag == false)) {
        goto jlvg_quit;
    }
    done = true;

jlvg_begin:
    // VG 开始绘制背景
    // 1、初始化渲染空间
    uint32_t fb_width;
    uint32_t fb_height;
    uint32_t fb_size;
    uint32_t dest_stride;
    uint8_t *dest_buf;
    uint32_t bytes_per_pixel;
    jlvg_hw_imageformat_t jlvg_dest_cf;
    bool is_frame_buf = lv_jl_gpu2p5d_check_draw_ctx_buf(draw_ctx->buf);

    // 绘制区域非显存区域，即 layer 的绘制流程, 重绘区域需要带透明度，例如 RGB565 -> ARGB565
    if (!is_frame_buf) {
        //针对canvas的处理,判断canvas的buf是否带透明度
        if (lv_jl_gpu2p5d_check_canvas_buf_format(draw_ctx) == LV_IMG_CF_TRUE_COLOR) {
#if LV_COLOR_DEPTH_EXTEN == 24
            jlvg_dest_cf = VGHW_FORMAT_RGB565;
#else
            jlvg_dest_cf = LV_GPU_COLOR_FORMAT;
#endif
            bytes_per_pixel = jlvg_get_image_format_bpp(jlvg_dest_cf) >> 3;
        } else {
            jlvg_dest_cf = LV_GPU_COLOR_ALPHA_FORMAT;
            bytes_per_pixel = LV_IMG_PX_SIZE_ALPHA_BYTE;
        }
    } else {
        jlvg_dest_cf = LV_GPU_COLOR_FORMAT;
        bytes_per_pixel = jlvg_get_image_format_bpp(LV_GPU_COLOR_FORMAT) >> 3;
    }

#if (JLVG_DRAW_FULL_FB_ENABLE == 1)
    fb_width = draw_ctx->buf_area->x2 - draw_ctx->buf_area->x1 + 1;     // 显存区域的宽度
    fb_height = draw_ctx->buf_area->y2 - draw_ctx->buf_area->y1 + 1;    // 显存区域的高度
    fb_size = fb_width * fb_height * bytes_per_pixel;                   // 显存区域的buff大小
    dest_stride = fb_width * bytes_per_pixel;
    dest_buf = draw_ctx->buf;  //最终会更新到屏幕上面的 buff 区域
#else
    fb_width = blend_area.x2 - blend_area.x1 + 1;       // 绘制区域的宽度
    fb_height = blend_area.y2 - blend_area.y1 + 1;      // 绘制区域的高度
    fb_size = fb_width * fb_height * bytes_per_pixel;   // 绘制区域的buff大小

    uint32_t buf_area_w = draw_ctx->buf_area->x2 - draw_ctx->buf_area->x1 + 1;
    dest_stride = buf_area_w * bytes_per_pixel;
    dest_buf = (uint8_t *)draw_ctx->buf + (blend_area.x1 * bytes_per_pixel) + (blend_area.y1 * dest_stride);
#endif
    //printf("fb_width = %d; fb_height = %d; dest_stride = %d.", fb_width, fb_height, dest_stride);

    jlvg_matrix_t user2surface_start;   // 变换矩阵 user to surface
    jlvg_matrix_t user2surface_line;    // 变换矩阵 user to surface
    jlvg_matrix_t user2surface_end;     // 变换矩阵 user to surface

    jlvg_surface_t surface;     // 绘制的窗口
    jlvg_rect_t draw_area;      // 在窗口内实际要绘制的区域:实际就是 blend_area

    //初始化单位变换矩阵
    jlvg_matrix_set_identity(&user2surface_start);
    jlvg_matrix_set_identity(&user2surface_line);
    jlvg_matrix_set_identity(&user2surface_end);

    //初始化要绘制的区域
#if (JLVG_DRAW_FULL_FB_ENABLE == 1)
#if 0   /* 允许 VG 绘制整个 FB 空间: 重要，绘制整个 FB 会导致 VG 加速效果变差，耗时会变长 */
    draw_area.x = 0;
    draw_area.y = 0;
    draw_area.w = fb_width;
    draw_area.h = fb_height;
#else   /* 只允许 VG 绘制 LVGL 限制的交叉裁剪区域 */
    draw_area.x = blend_area.x1;
    draw_area.y = blend_area.y1;
    draw_area.w = blend_area.x2 - blend_area.x1 + 1;
    draw_area.h = blend_area.y2 - blend_area.y1 + 1;
#endif

    // 刷新要绘制的区域的 cache
    const uint8_t *flush_addr = dest_buf + (draw_area.x * bytes_per_pixel) + (draw_area.y * dest_stride);
    lv_jl_gpu2p5d_flush_inv_dcache(flush_addr, draw_area.w, draw_area.h, fb_width, bytes_per_pixel << 3);
#else
    // 即 blend_area 区域
    draw_area.x = 0;
    draw_area.y = 0;
    draw_area.w = fb_width;
    draw_area.h = fb_height;

    // 刷新要绘制的区域的 cache
    const uint8_t *flush_addr = dest_buf;
    lv_jl_gpu2p5d_flush_inv_dcache(flush_addr, draw_area.w, draw_area.h, buf_area_w, bytes_per_pixel << 3);
#endif
    //printf("draw_area (x,y) = (%d,%d); w = %d, y = %d.", draw_area.x, draw_area.y, draw_area.w, draw_area.h);

    //窗口初始化
    jlvg_surface_init(&surface, dest_buf, fb_size, fb_width, fb_height, dest_stride, jlvg_dest_cf, 0, 1, 1, 0);

    //2、配置颜色填充
    //填充颜色
    jlvg_paint_color_t paint_color;     // 正常渲染的颜色
    jlvg_color_t fill_color;

#if LV_COLOR_DEPTH == 16
    //填充颜色准备
    fill_color.a = dsc->opa;
    fill_color.r = dsc->color.ch.red << 3;
    fill_color.g = dsc->color.ch.green << 2;
    fill_color.b = dsc->color.ch.blue << 3;
    jlvg_color_premultiply(&fill_color);    // 填充像素预乘
    jlvg_paint_color_init(&paint_color, fill_color); //初始化填充的颜色内容
#else
    //填充颜色准备
    //printf("no grad");
    fill_color.a = dsc->opa;
    fill_color.r = dsc->color.ch.red;
    fill_color.g = dsc->color.ch.green;
    fill_color.b = dsc->color.ch.blue;
    jlvg_color_premultiply(&fill_color);    // 填充像素预乘
    jlvg_paint_color_init(&paint_color, fill_color); //初始化填充的颜色内容
#endif

    // 配置 paint
    jlvg_paint_t *draw_paint = &paint_color;

    // 3、配置绘制路径 + 4、硬件绘制
    jlvg_start_frame(g_gpu2p5d, &surface);
    jlvg_path_t start_path;     // 绘制线段的起点路径
    jlvg_path_t line_path;      // 绘制的线段路径
    jlvg_path_t end_path;       // 绘制线段的终点路径
    jlvg_point2_t point_line_1;    // 线段的矩形区域坐标
    jlvg_point2_t point_line_2;
    jlvg_point2_t point_line_3;
    jlvg_point2_t point_line_4;
    float len_h;
    float len_w;

    // 计算线段两段的相对宽高
    if (rel_point1.x > rel_point2.x) {
        len_w = rel_point2.x - rel_point1.x - 1;
    } else {
        len_w = rel_point2.x - rel_point1.x + 1;
    }

    if (rel_point1.y > rel_point2.y) {
        len_h = rel_point2.y - rel_point1.y - 1;
    } else {
        len_h = rel_point2.y - rel_point1.y + 1;
    }
    //printf("len_w = %f; len_h = %f.", len_w, len_h);

    float hypotenuse = sqrt(len_w * len_w + len_h * len_h);
    float sin = len_h / hypotenuse;
    float cos = len_w / hypotenuse;
    float radius_f = (float)dsc->width / 2.0; // 线宽的一半作为半径
    //printf("hypotenuse = %f; sin = %f; cos %f.", hypotenuse, sin, cos);
    // 计算线段矩形区域的坐标
#if (JLVG_DRAW_FULL_FB_ENABLE == 1)
    jlvg_point2_t point_start = { rel_point1.x, rel_point1.y };
    jlvg_point2_t point_end = { rel_point2.x, rel_point2.y };
    point_line_1.x = rel_point1.x + (float)sin * radius_f;
    point_line_1.y = rel_point1.y - (float)cos * radius_f;
    point_line_2.x = rel_point1.x - (float)sin * radius_f;
    point_line_2.y = rel_point1.y + (float)cos * radius_f;
    point_line_3.x = rel_point2.x - (float)sin * radius_f;
    point_line_3.y = rel_point2.y + (float)cos * radius_f;
    point_line_4.x = rel_point2.x + (float)sin * radius_f;
    point_line_4.y = rel_point2.y - (float)cos * radius_f;
#else
    // 由于开窗限制在了绘制区域，因此绘制坐标需要平移到原点
    jlvg_point2_t point_start = { rel_point1.x - blend_area.x1, rel_point1.y - blend_area.y1 };
    jlvg_point2_t point_end = { rel_point2.x - blend_area.x1, rel_point2.y - blend_area.y1 };

    point_line_1.x = rel_point1.x + (float)sin * radius_f - blend_area.x1;
    point_line_1.y = rel_point1.y - (float)cos * radius_f - blend_area.y1;
    point_line_2.x = rel_point1.x - (float)sin * radius_f - blend_area.x1;
    point_line_2.y = rel_point1.y + (float)cos * radius_f - blend_area.y1;
    point_line_3.x = rel_point2.x - (float)sin * radius_f - blend_area.x1;
    point_line_3.y = rel_point2.y + (float)cos * radius_f - blend_area.y1;
    point_line_4.x = rel_point2.x + (float)sin * radius_f - blend_area.x1;
    point_line_4.y = rel_point2.y - (float)cos * radius_f - blend_area.y1;
#endif
    //printf("point_line_1: (x, y) = (%f, %f).", point_line_1.x, point_line_1.y);
    //printf("point_line_2: (x, y) = (%f, %f).", point_line_2.x, point_line_2.y);
    //printf("point_line_3: (x, y) = (%f, %f).", point_line_3.x, point_line_3.y);
    //printf("point_line_4: (x, y) = (%f, %f).", point_line_4.x, point_line_4.y);

    // 画起点
    if (dsc->round_start != 0) { /* 起点有圆角属性 */
        // 以起点为圆心绘制一个圆
        lv_draw_jl_gpu2p5d_line_endpoints_path_fill(&start_path, point_start, (radius_f));
        jlvg_fill_path(g_gpu2p5d, &draw_area, &start_path, draw_paint, &user2surface_start, NULL, blend_mode, VGHW_NON_ZERO);
    }

    // 画线段
    uint32_t nsegments = 5;
    uint8_t segments[] = { VGHW_MOVE_TO, VGHW_LINE_TO, VGHW_LINE_TO, VGHW_LINE_TO, VGHW_LINE_TO};
    float points[] = { point_line_1.x, point_line_1.y, point_line_2.x, point_line_2.y, point_line_3.x, point_line_3.y, point_line_4.x, point_line_4.y, point_line_1.x, point_line_1.y };

    jlvg_path_init(&line_path, JLVG_PATH_DATATYPE_F32, nsegments, segments, sizeof(points) / sizeof(float), points);
    jlvg_path_update_fill(&line_path);
    jlvg_fill_path(g_gpu2p5d, &draw_area, &line_path, draw_paint, &user2surface_line, NULL, blend_mode, VGHW_NON_ZERO);

    // 画终点
    if (dsc->round_end != 0) {  /* 终点有圆角属性 */
        // 以终点为圆心绘制一个圆
        lv_draw_jl_gpu2p5d_line_endpoints_path_fill(&end_path, point_end, (radius_f));
        jlvg_fill_path(g_gpu2p5d, &draw_area, &end_path, draw_paint, &user2surface_end, NULL, blend_mode, VGHW_NON_ZERO);
    }

    jlvg_end_frame(g_gpu2p5d);

    //4、清理现场
    jlvg_path_deinit(&line_path);
    if (dsc->round_start != 0) {
        jlvg_path_deinit(&start_path);
    }
    if (dsc->round_end != 0) {
        jlvg_path_deinit(&end_path);
    }
    jlvg_paint_deinit((jlvg_paint_t *)&paint_color);
    jlvg_surface_deinit(&surface);

jlvg_quit:
    if (!done) {
        lv_draw_sw_line(draw_ctx, dsc, point1, point2);
    }
}

/**********************
 *   STATIC FUNCTIONS
 **********************/

static void lv_draw_jl_gpu2p5d_line_endpoints_path_fill(jlvg_path_t *path, jlvg_point2_t point, float radius)
{
    //printf("%s() point: (x, y) = (%d, %d); radius = %f.", __func__, point.x, point.y, radius);
    uint32_t nsegments = 0;
    uint8_t segments[9] = { 0 };
    float points[2 + 3 * 6 + 3 * 6] = { 0 };
    int npoints = 0;
    int nseg_tmp = 0;
    int npoints_tmp = 0;

    segments[nsegments++] = VGHW_MOVE_TO;
    points[npoints++] = point.x;
    points[npoints++] = point.y - radius;

    jlvg_path_circle2beizer(&segments[nsegments], &nseg_tmp, &points[npoints], &npoints_tmp,
                            point.x, point.y, radius, point.x, (point.y - radius), point.x, (point.y + radius), 0, 1);
    nsegments += nseg_tmp;
    npoints += npoints_tmp;

    jlvg_path_circle2beizer(&segments[nsegments], &nseg_tmp, &points[npoints], &npoints_tmp,
                            point.x, point.y, radius, point.x, (point.y + radius), point.x, (point.y - radius), 0, 1);
    nsegments += nseg_tmp;
    npoints += npoints_tmp;

    jlvg_path_init(path, JLVG_PATH_DATATYPE_F32, nsegments, segments, sizeof(points) / sizeof(float), points);
    jlvg_path_update_fill(path);
}
#endif  // LV_USE_JL_GPU2P5D_DRAW_LINE
#endif  // LV_USE_GPU_JL_GPU2P5D
