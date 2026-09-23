/**
 * @file lv_gpu_jl_gpu2p5d_polygon.c
 *
 */

/*********************
 *      INCLUDES
 *********************/
#include "lv_gpu_jl_gpu2p5d.h"

#if LV_USE_GPU_JL_GPU2P5D
#if LV_USE_JL_GPU2P5D_DRAW_POLYGON
/*********************
 *      DEFINES
 *********************/

/**********************
 *      TYPEDEFS
 **********************/

/**********************
 *  STATIC PROTOTYPES
 **********************/

/**********************
 *  STATIC VARIABLES
 **********************/

/**********************
 *      MACROS
 **********************/

/**********************
 *   GLOBAL FUNCTIONS
 **********************/

void lv_draw_jl_gpu2p5d_polygon(lv_draw_ctx_t *draw_ctx, const lv_draw_rect_dsc_t *draw_dsc, const lv_point_t *points, uint16_t point_cnt)
{
    //printf("%s()", __func__);
    // 只关心 bg 属性，其余属性不进行绘制
    if (draw_dsc->bg_opa <= LV_OPA_MIN) {
        return;
    }

    if (point_cnt < 3) {
        return;
    }
    if (points == NULL) {
        return;
    }

    /*Join adjacent points if they are on the same coordinate*/
    lv_point_t *p = lv_mem_buf_get(point_cnt * sizeof(lv_point_t));

    uint16_t i;
    uint16_t pcnt = 0;
    p[0] = points[0];
    for (i = 0; i < point_cnt - 1; i++) {
        if (points[i].x != points[i + 1].x || points[i].y != points[i + 1].y) {
            p[pcnt] = points[i];
            pcnt++;
        }
    }

    /*The first and the last points are also adjacent*/
    if (points[0].x != points[point_cnt - 1].x || points[0].y != points[point_cnt - 1].y) {
        p[pcnt] = points[point_cnt - 1];
        pcnt++;
    }

    point_cnt = pcnt;
    if (point_cnt < 3) {
        lv_mem_buf_release(p);
        return;
    }

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

    // 多边形绘制的区域
    lv_area_t poly_coords = {.x1 = LV_COORD_MAX, .y1 = LV_COORD_MAX, .x2 = LV_COORD_MIN, .y2 = LV_COORD_MIN};

    for (i = 0; i < point_cnt; i++) {
        poly_coords.x1 = LV_MIN(poly_coords.x1, p[i].x);
        poly_coords.y1 = LV_MIN(poly_coords.y1, p[i].y);
        poly_coords.x2 = LV_MAX(poly_coords.x2, p[i].x);
        poly_coords.y2 = LV_MAX(poly_coords.y2, p[i].y);
    }

    lv_area_t rel_clip_area;
    lv_area_copy(&rel_clip_area, draw_ctx->clip_area);
    // 计算相对于实际的绘制buff进行偏移
    lv_area_move(&rel_clip_area, -draw_ctx->buf_area->x1, -draw_ctx->buf_area->y1);    // 重新确定在显存中的相对位置

    lv_area_t rel_coords;
    lv_area_copy(&rel_coords, &poly_coords);
    // 计算相对于实际的绘制buff进行偏移
    lv_area_move(&rel_coords, -draw_ctx->buf_area->x1, -draw_ctx->buf_area->y1);    // 重新确定在显存中的相对位置

    lv_area_t blend_area;   //这个区域无论是帧buff还是行buff都是相对的新的绘制区域
    if (!_lv_area_intersect(&blend_area, &rel_coords, &rel_clip_area)) {
        lv_mem_buf_release(p);
        return;
    }

    lv_point_t rel_point[point_cnt];
    for (i = 0; i < point_cnt; i++) {   // 重新确定在显存中的相对位置
        rel_point[i].x = p[i].x - draw_ctx->buf_area->x1;
        rel_point[i].y = p[i].y - draw_ctx->buf_area->x1;
    }

    bool has_mask = lv_draw_mask_is_any(&rel_coords);
    bool mode_flag;
    uint8_t blend_mode = lv_jl_gpu2p5d_get_blend_mode(draw_dsc->blend_mode, &mode_flag);   //根据图像的混合模式获取 VG 配置的混合模式
    if ((has_mask == true) || (mode_flag == false)) {
        //printf("%s -> sw", __func__);
        lv_mem_buf_release(p);
        lv_draw_sw_polygon(draw_ctx, draw_dsc, points, point_cnt);
        return;
    }

    // VG 开始绘制背景
    // 1、初始化渲染空间
    uint32_t fb_width;
    uint32_t fb_height;
    uint32_t fb_size;
    uint32_t dest_stride;
    uint8_t *dest_buf;

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

    jlvg_matrix_t user2surface_polygon;    // 变换矩阵 user to surface

    jlvg_surface_t surface;     // 绘制的窗口
    jlvg_rect_t draw_area;      // 在窗口内实际要绘制的区域:实际就是 blend_area

    //初始化单位变换矩阵
    jlvg_matrix_set_identity(&user2surface_polygon);

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
    jlvg_path_t polygon_path;      // 绘制的线段路径

    //2、配置颜色填充
    //填充颜色
    jlvg_paint_color_t paint_color;     // 正常渲染的颜色
    jlvg_color_t fill_color;

#if LV_COLOR_DEPTH == 16
    //填充颜色准备
    fill_color.a = draw_dsc->bg_opa;
    fill_color.r = draw_dsc->bg_color.ch.red << 3;
    fill_color.g = draw_dsc->bg_color.ch.green << 2;
    fill_color.b = draw_dsc->bg_color.ch.blue << 3;
    jlvg_color_premultiply(&fill_color);    // 填充像素预乘
    jlvg_paint_color_init(&paint_color, fill_color); //初始化填充的颜色内容
#else
    //填充颜色准备
    //printf("no grad");
    fill_color.a = draw_dsc->bg_opa;
    fill_color.r = draw_dsc->bg_color.ch.red;
    fill_color.g = draw_dsc->bg_color.ch.green;
    fill_color.b = draw_dsc->bg_color.ch.blue;
    jlvg_color_premultiply(&fill_color);    // 填充像素预乘
    jlvg_paint_color_init(&paint_color, fill_color); //初始化填充的颜色内容
#endif

    // 配置 paint
    jlvg_paint_t *draw_paint = &paint_color;

    // 3、配置绘制路径 + 4、硬件绘制
    jlvg_start_frame(g_gpu2p5d, &surface);

    // 重定位多边形闭合矩形区域的坐标
#if (JLVG_DRAW_FULL_FB_ENABLE == 1)
    // nothing
#else
    // 由于开窗限制在了绘制区域，因此绘制坐标需要平移到原点
    for (i = 0; i < point_cnt; i++) {   // 重新确定在显存中的相对位置
        rel_point[i].x = rel_point[i].x - blend_area.x1;
        rel_point[i].y = rel_point[i].y - blend_area.y1;
    }
#endif

    // 画闭合区域
    uint32_t nsegments = 1 + point_cnt;
    uint8_t segments[nsegments];
    uint32_t npoints = nsegments * 2;
    float points_f[npoints];
    int nseg_tmp = 0;
    int npoints_tmp = 0;

    segments[nseg_tmp++] = VGHW_MOVE_TO;
    points_f[npoints_tmp++] = rel_point[point_cnt - 1].x;
    points_f[npoints_tmp++] = rel_point[point_cnt - 1].y;

    for (i = 0; i < point_cnt; i++) {
        segments[nseg_tmp++] = VGHW_LINE_TO;
        points_f[npoints_tmp++] = rel_point[i].x;
        points_f[npoints_tmp++] = rel_point[i].y;
    }

    jlvg_path_init(&polygon_path, JLVG_PATH_DATATYPE_F32, nsegments, segments, npoints, points_f);
    jlvg_path_update_fill(&polygon_path);
    jlvg_fill_path(g_gpu2p5d, &draw_area, &polygon_path, draw_paint, &user2surface_polygon, NULL, blend_mode, VGHW_NON_ZERO);

    jlvg_end_frame(g_gpu2p5d);

    //4、清理现场
    jlvg_path_deinit(&polygon_path);
    jlvg_paint_deinit((jlvg_paint_t *)&paint_color);
    jlvg_surface_deinit(&surface);
    lv_mem_buf_release(p);
}

/**********************
 *   STATIC FUNCTIONS
 **********************/

#endif  // LV_USE_JL_GPU2P5D_DRAW_POLYGON
#endif  // LV_USE_GPU_JL_GPU2P5D
