/**
 * @file lv_gpu_jl_gpu2p5d_line.c
 *
 */

/*********************
 *      INCLUDES
 *********************/
#include "lv_gpu_jl_gpu2p5d.h"

#if LV_USE_GPU_JL_GPU2P5D
#if LV_USE_JL_GPU2P5D_DRAW_ARC
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

static void lv_draw_jl_gpu2p5d_arc_endpoints_path_fill(jlvg_path_t *path, jlvg_point2_t point, float radius);

/**********************
 *  STATIC VARIABLES
 **********************/

/**********************
 *      MACROS
 **********************/

/**********************
 *   GLOBAL FUNCTIONS
 **********************/

void lv_draw_jl_gpu2p5d_arc(lv_draw_ctx_t *draw_ctx, const lv_draw_arc_dsc_t *dsc, const lv_point_t *center,
                            uint16_t radius, uint16_t start_angle, uint16_t end_angle)
{
    //printf("%s()", __func__);
    if (dsc->opa <= (lv_opa_t)LV_OPA_MIN) {
        return;
    }
    if (dsc->width == 0) {
        return;
    }
    if (start_angle == end_angle) {
        return;
    }

    lv_coord_t width = dsc->width;
    if (width > radius) {
        width = radius;
    }

    float endpoint_radius = (float)width / 2.0; // 线宽的一半作为端点的半径
    //printf("radius = %d; endpoint_radius = %f.", radius, endpoint_radius);

    lv_point_t rel_center = {center->x - draw_ctx->buf_area->x1, center->y - draw_ctx->buf_area->y1};

    lv_area_t rel_clip_area;
    lv_area_copy(&rel_clip_area, draw_ctx->clip_area);
    lv_area_move(&rel_clip_area, -draw_ctx->buf_area->x1, -draw_ctx->buf_area->y1);    // 重新确定在显存中的相对位置

    lv_area_t blend_area;   //这个区域无论是帧buff还是行buff都是相对的新的绘制区域
    lv_area_copy(&blend_area, &rel_clip_area);
    //printf("blend_area (x1,y1) = (%d,%d); (x2,y2) = (%d,%d).", blend_area.x1, blend_area.y1, blend_area.x2, blend_area.y2);

    //printf("rounded = %d; start_angle = %d; end_angle = %d.", dsc->rounded, start_angle, end_angle);

    bool done = false;
    bool has_mask = lv_draw_mask_is_any(&rel_clip_area);
    bool mode_flag;
    uint8_t blend_mode = lv_jl_gpu2p5d_get_blend_mode(dsc->blend_mode, &mode_flag);   //根据图像的混合模式获取 VG 配置的混合模式
    bool is_img_arc = (dsc->img_src == NULL) ? false : true;

    if ((has_mask == true) || (mode_flag == false) || (is_img_arc == true)) {
        goto jlvg_quit;
    }

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
    jlvg_path_t start_path;     // 绘制弧形的起点路径
    jlvg_path_t arc_path;       // 绘制弧形的路径
    jlvg_path_t end_path;       // 绘制弧形的终点路径
    jlvg_point2_t point_arc_start;
    jlvg_point2_t point_arc_start_1;    // 弧形区域的起点处的坐标
    jlvg_point2_t point_arc_start_2;
    jlvg_point2_t point_arc_end;
    jlvg_point2_t point_arc_end_1;      // 弧形区域的终点处的坐标
    jlvg_point2_t point_arc_end_2;

    float start_angle_f = (float)start_angle;
    float end_angle_f = (float)end_angle;

    // 防止内圆和外圆闭合
    if ((start_angle_f - end_angle_f) == 360.0f) {
        start_angle_f -= 0.1f;
    } else if ((start_angle_f - end_angle_f) == -360.0f) {
        end_angle_f -= 0.1f;
    }

    float sin_start = sin(start_angle_f * M_PI / 180.0);
    float cos_start = cos(start_angle_f * M_PI / 180.0);
    float sin_end = sin(end_angle_f * M_PI / 180.0);
    float cos_end = cos(end_angle_f * M_PI / 180.0);

    // 计算弧形两个端点的中点
    float arc_radius = radius - endpoint_radius;    // 这个是绘制时实际的圆环中心的半径, radius 为外圆半径
    if (arc_radius < 0.0f) {
        arc_radius = 0.0f;
    }
    point_arc_start.x = rel_center.x + cos_start * arc_radius;
    point_arc_start.y = rel_center.y + sin_start * arc_radius;
    point_arc_end.x = rel_center.x + cos_end * arc_radius;
    point_arc_end.y = rel_center.y + sin_end * arc_radius;
    //printf("rel_center: (x, y) = (%d, %d).", rel_center.x, rel_center.y);
    //printf("start_angle: (x, y) = (%f, %f).", point_arc_start.x, point_arc_start.y);
    //printf("end_angle: (x, y) = (%f, %f).", point_arc_end.x, point_arc_end.y);

    // 计算线段矩形区域的坐标
#if (JLVG_DRAW_FULL_FB_ENABLE == 1)
    jlvg_point2_t point_start = point_arc_start;
    jlvg_point2_t point_end = point_arc_end;
    jlvg_point2_t final_center = { rel_center.x, rel_center.y };
    point_arc_start_1.x = point_arc_start.x - (float)cos_start * endpoint_radius;
    point_arc_start_1.y = point_arc_start.y - (float)sin_start * endpoint_radius;
    point_arc_start_2.x = point_arc_start.x + (float)cos_start * endpoint_radius;
    point_arc_start_2.y = point_arc_start.y + (float)sin_start * endpoint_radius;
    point_arc_end_1.x = point_arc_end.x + (float)cos_end * endpoint_radius;
    point_arc_end_1.y = point_arc_end.y + (float)sin_end * endpoint_radius;
    point_arc_end_2.x = point_arc_end.x - (float)cos_end * endpoint_radius;
    point_arc_end_2.y = point_arc_end.y - (float)sin_end * endpoint_radius;
#else
    // 由于开窗限制在了绘制区域，因此绘制坐标需要平移到原点
    jlvg_point2_t point_start = { point_arc_start.x - blend_area.x1, point_arc_start.y - blend_area.y1 };
    jlvg_point2_t point_end = { point_arc_end.x - blend_area.x1, point_arc_end.y - blend_area.y1 };
    jlvg_point2_t final_center = { rel_center.x - blend_area.x1, rel_center.y - blend_area.y1 };
    point_arc_start_1.x = point_arc_start.x - (float)cos_start * endpoint_radius - blend_area.x1;
    point_arc_start_1.y = point_arc_start.y - (float)sin_start * endpoint_radius - blend_area.y1;
    point_arc_start_2.x = point_arc_start.x + (float)cos_start * endpoint_radius - blend_area.x1;
    point_arc_start_2.y = point_arc_start.y + (float)sin_start * endpoint_radius - blend_area.y1;
    point_arc_end_1.x = point_arc_end.x + (float)cos_end * endpoint_radius - blend_area.x1;
    point_arc_end_1.y = point_arc_end.y + (float)sin_end * endpoint_radius - blend_area.y1;
    point_arc_end_2.x = point_arc_end.x - (float)cos_end * endpoint_radius - blend_area.x1;
    point_arc_end_2.y = point_arc_end.y - (float)sin_end * endpoint_radius - blend_area.y1;
#endif
    //printf("point_arc_start_1: (x, y) = (%f, %f).", point_arc_start_1.x, point_arc_start_1.y);
    //printf("point_arc_start_2: (x, y) = (%f, %f).", point_arc_start_2.x, point_arc_start_2.y);
    //printf("point_arc_end_1: (x, y) = (%f, %f).", point_arc_end_1.x, point_arc_end_1.y);
    //printf("point_arc_end_2: (x, y) = (%f, %f).", point_arc_end_2.x, point_arc_end_2.y);

    // 画起点 + 终点
    if (dsc->rounded != 0) { /* 起点有圆角属性 */
        // 以起点为圆心绘制一个圆
        lv_draw_jl_gpu2p5d_arc_endpoints_path_fill(&start_path, point_start, (endpoint_radius));
        jlvg_fill_path(g_gpu2p5d, &draw_area, &start_path, draw_paint, &user2surface_start, NULL, blend_mode, VGHW_NON_ZERO);

        // 以终点为圆心绘制一个圆
        lv_draw_jl_gpu2p5d_arc_endpoints_path_fill(&end_path, point_end, (endpoint_radius));
        jlvg_fill_path(g_gpu2p5d, &draw_area, &end_path, draw_paint, &user2surface_end, NULL, blend_mode, VGHW_NON_ZERO);
    }

    // 画弧形
    uint32_t nsegments = 0;
    //uint8_t segments[1 + 5 + 1 + 5 + 1] = { 0 };
    uint8_t segments[13] = { 0 };
    //float points[2 + 5 * 6 + 2 + 5 * 6 + 2] = { 0 };
    float points[66] = { 0 };
    int npoints = 0;
    int nseg_tmp = 0;
    int npoints_tmp = 0;

    //moveto
    segments[nsegments++] = VGHW_MOVE_TO;
    points[npoints++] = point_arc_start_2.x;
    points[npoints++] = point_arc_start_2.y;

    //outer arc
    float outer_arc_radius = (arc_radius + endpoint_radius);
    float inner_arc_radius = (arc_radius - endpoint_radius);
    //printf("outer_arc_radius = %f; inner_arc_radius = %f.", outer_arc_radius, inner_arc_radius);

    // 绘制外弧: 是必须要画的
    jlvg_path_circle2beizer(&segments[nsegments], &nseg_tmp, &points[npoints], &npoints_tmp,
                            final_center.x, final_center.y, // 圆心
                            outer_arc_radius, // 半径
                            point_arc_start_2.x, point_arc_start_2.y, // 起始点
                            point_arc_end_1.x, point_arc_end_1.y,   // 终点
                            0, 0);  // 顺时针
    nsegments += nseg_tmp;
    npoints += npoints_tmp;

    //line to
    segments[nsegments++] = VGHW_LINE_TO;
    points[npoints++] = point_arc_end_2.x;
    points[npoints++] = point_arc_end_2.y;

    //inner arc
    // 绘制内弧: 内弧半径大于 0.0f 才绘制
    if (inner_arc_radius > 0.0f) {
        jlvg_path_circle2beizer(&segments[nsegments], &nseg_tmp, &points[npoints], &npoints_tmp,
                                final_center.x, final_center.y, // 圆心
                                inner_arc_radius, // 半径
                                point_arc_end_2.x, point_arc_end_2.y, // 起始点
                                point_arc_start_1.x, point_arc_start_1.y, // 终点
                                1, 0);    // 逆时针
        nsegments += nseg_tmp;
        npoints += npoints_tmp;
    }

    //line to
    segments[nsegments++] = VGHW_LINE_TO;
    points[npoints++] = point_arc_start_2.x;
    points[npoints++] = point_arc_start_2.y;

    //printf("nsegments = %d; npoints = %d.", nsegments, npoints);
    jlvg_path_init(&arc_path, JLVG_PATH_DATATYPE_F32, nsegments, segments, npoints, points);
    jlvg_path_update_fill(&arc_path);
    jlvg_fill_path(g_gpu2p5d, &draw_area, &arc_path, draw_paint, &user2surface_line, NULL, blend_mode, VGHW_NON_ZERO);
    jlvg_end_frame(g_gpu2p5d);

    //4、清理现场
    jlvg_path_deinit(&arc_path);
    if (dsc->rounded != 0) {
        jlvg_path_deinit(&start_path);
        jlvg_path_deinit(&end_path);
    }
    jlvg_paint_deinit((jlvg_paint_t *)&paint_color);
    jlvg_surface_deinit(&surface);
    done = true;

jlvg_quit:
    if (!done) {
        lv_draw_sw_arc(draw_ctx, dsc, center, radius, start_angle, end_angle);
    }
}

/**********************
 *   STATIC FUNCTIONS
 **********************/

static void lv_draw_jl_gpu2p5d_arc_endpoints_path_fill(jlvg_path_t *path, jlvg_point2_t point, float radius)
{
    //printf("%s() point: (x, y) = (%f, %f); radius = %f.", __func__, point.x, point.y, radius);
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
#endif  // LV_USE_JL_GPU2P5D_DRAW_ARC
#endif  // LV_USE_GPU_JL_GPU2P5D
