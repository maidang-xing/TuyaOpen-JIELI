/**
 * @file lv_gpu_jl_gpu2p5d_letter.c
 *
 */

/*********************
 *      INCLUDES
 *********************/
#include "lv_gpu_jl_gpu2p5d.h"

#if LV_USE_GPU_JL_GPU2P5D
#if LV_USE_JL_GPU2P5D_DRAW_LETTER
/*********************
 *      DEFINES
 *********************/

#if (LV_USE_USER_DATA != 1)
#error LV_USE_USER_DATA must be enabled !!!
#endif

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
 *  GLOBAL VARIABLES
 **********************/

/**********************
 *      MACROS
 **********************/

/**********************
 *   GLOBAL FUNCTIONS
 **********************/

void LV_ATTRIBUTE_FAST_MEM lv_draw_jl_gpu2p5d_letter(lv_draw_ctx_t *draw_ctx, const lv_draw_label_dsc_t *dsc, \
        const lv_point_t *pos_p, uint32_t letter)
{
    //printf("[%s] begin", __func__);

    //uint32_t begin_time = get_system_us();

    if (dsc->opa <= (lv_opa_t)LV_OPA_MIN) {
        return;
    }

    bool mode_flag;
    uint8_t blend_mode = lv_jl_gpu2p5d_get_blend_mode(dsc->blend_mode, &mode_flag);   //根据图像的混合模式获取 VG 配置的混合模式

    // JL GPU 支持的矢量绘制字库(freetype、tinyttf)则直接绘制字体到显存
    if ((lv_font_jlgpu2p5d_draw_check_support(dsc->font->user_data) == false) || (mode_flag == false)) {
        // 不支持加速的加速情况执行软件渲染流程
        lv_draw_sw_letter(draw_ctx, dsc, pos_p, letter);
        return;
    }

    // 根据显存空间区域找到原绝对坐标(相对屏幕大小区域的绝对坐标)在显存区域中的相对坐标（相当于在显存区域中的绝对坐标）
    lv_point_t rel_pos_p;
    rel_pos_p.x = pos_p->x - draw_ctx->buf_area->x1;
    rel_pos_p.y = pos_p->y - draw_ctx->buf_area->y1;

    lv_area_t rel_clip_area;
    lv_area_copy(&rel_clip_area, draw_ctx->clip_area);
    lv_area_move(&rel_clip_area, -draw_ctx->buf_area->x1, -draw_ctx->buf_area->y1);

    lv_font_glyph_dsc_t g;
    bool g_ret = lv_font_get_glyph_dsc(dsc->font, &g, letter, '\0');
    if (g_ret == false) {
        /*Add warning if the dsc is not found
         *but do not print warning for non printable ASCII chars (e.g. '\n')*/
        if (letter >= 0x20 &&
            letter != 0xf8ff && /*LV_SYMBOL_DUMMY*/
            letter != 0x200c) { /*ZERO WIDTH NON-JOINER*/
            LV_LOG_WARN("lv_draw_letter: glyph dsc. not found for U+%" LV_PRIX32, letter);

#if LV_USE_FONT_PLACEHOLDER
            /* draw placeholder */
            lv_area_t glyph_coords;
            lv_draw_rect_dsc_t glyph_dsc;
            lv_coord_t begin_x = pos_p->x + g.ofs_x;    // 交付原绝对坐标
            lv_coord_t begin_y = pos_p->y + g.ofs_y;
            lv_area_set(&glyph_coords, begin_x, begin_y, begin_x + g.box_w, begin_y + g.box_h);
            lv_draw_rect_dsc_init(&glyph_dsc);
            glyph_dsc.bg_opa = LV_OPA_MIN;
            glyph_dsc.outline_opa = LV_OPA_MIN;
            glyph_dsc.shadow_opa = LV_OPA_MIN;
            glyph_dsc.bg_img_opa = LV_OPA_MIN;
            glyph_dsc.border_color = dsc->color;
            glyph_dsc.border_width = 1;
            draw_ctx->draw_rect(draw_ctx, &glyph_dsc, &glyph_coords);
#endif
        }
        return;
    }
    //printf("line_height = %d, base_line = %d.", dsc->font->line_height, dsc->font->base_line);

    /*Don't draw anything if the character is empty. E.g. space*/
    if ((g.box_h == 0) || (g.box_w == 0)) { //字符边间的宽度和高度都为0表示这个字符是个空字符
        return;
    }

    lv_point_t gpos;    // 定位字形在显存空间中的绝对位置
    // |<- ofs_x ->|<- box_w ->|
    // | ... |<- ofs_y ->|<- box_h ->|<- base_line ->|
    gpos.x = rel_pos_p.x + g.ofs_x;
    gpos.y = rel_pos_p.y + (dsc->font->line_height - dsc->font->base_line) - g.box_h - g.ofs_y;
    // 说明:  ofs_y 向上为正方向，所以和理解的方向不一样，与 ofs_x 的加偏移量不同，而是减去 ofs_y

    /*If the letter is completely out of mask don't draw it*/
    if (gpos.x + g.box_w < rel_clip_area.x1 ||
        gpos.x > rel_clip_area.x2 ||
        gpos.y + g.box_h < rel_clip_area.y1 ||
        gpos.y > rel_clip_area.y2)  {
        return;
    }

    // 获取字形矢量路径, 获取的是原始字库路径，需要修正翻转问题和偏移问题
    lv_font_path_t *glyph_path = lv_font_jlgpu2p5d_get_glyph_vertex_path(g.resolved_font, letter);
    if (glyph_path == NULL) {
        LV_LOG_WARN("lv_draw_letter: character's glyph path not found");
        return;
    }

    // 装载成 jlvg 的绘制路径格式
    uint32_t segments_num = glyph_path->vertex_number;      //绘制结束需要的路径段数
    uint8_t segments[segments_num];  //绘制完整的路径动作
    uint32_t points_num = glyph_path->points_num;           //绘制结束需要的坐标点数
    float points[points_num];      //绘制结束需要的路径坐标
    uint32_t points_ofs = 0;

    if (segments_num == 0) {    // 空白字符退出绘制
        return;
    }

    for (int i = 0; i < segments_num; i++) {
        segments[i] = lv_jl_gpu2p5d_get_path_type(glyph_path->vertex_list[i].type, NULL);
        //printf("segments[%d] : 0x%02x.", i, segments[i]);
        if ((glyph_path->vertex_list[i].type == LV_FONT_VERTEX_MOVE_TO) || (glyph_path->vertex_list[i].type == LV_FONT_VERTEX_LINE_TO)) {
            points[points_ofs++] = glyph_path->vertex_list[i].x - g.ofs_x;                  // 修正路径翻转问题
            points[points_ofs++] = g.box_h - glyph_path->vertex_list[i].y + g.ofs_y;        // 修正路径翻转问题
            //printf("points e (x, y) = (%f, %f).", points[points_ofs - 2], points[points_ofs - 1]);
        } else if (glyph_path->vertex_list[i].type == LV_FONT_VERTEX_QUAD_TO) {
            points[points_ofs++] = glyph_path->vertex_list[i].cx1 - g.ofs_x;                // 修正路径翻转问题
            points[points_ofs++] = g.box_h - glyph_path->vertex_list[i].cy1 + g.ofs_y;      // 修正路径翻转问题
            //printf("points c (x, y) = (%f, %f).", points[points_ofs - 2], points[points_ofs - 1]);
            points[points_ofs++] = glyph_path->vertex_list[i].x - g.ofs_x;                  // 修正路径翻转问题
            points[points_ofs++] = g.box_h - glyph_path->vertex_list[i].y + g.ofs_y;        // 修正路径翻转问题
            //printf("points e (x, y) = (%f, %f).", points[points_ofs - 2], points[points_ofs - 1]);
        } else if (glyph_path->vertex_list[i].type == LV_FONT_VERTEX_CUBIC_TO) {
            points[points_ofs++] = glyph_path->vertex_list[i].cx1 - g.ofs_x;                // 修正路径翻转问题
            points[points_ofs++] = g.box_h - glyph_path->vertex_list[i].cy1 + g.ofs_y;      // 修正路径翻转问题
            //printf("points c (x, y) = (%f, %f).", points[points_ofs - 2], points[points_ofs - 1]);
            points[points_ofs++] = glyph_path->vertex_list[i].cx2 - g.ofs_x;                // 修正路径翻转问题
            points[points_ofs++] = g.box_h - glyph_path->vertex_list[i].cy2 + g.ofs_y;      // 修正路径翻转问题
            //printf("points c (x, y) = (%f, %f).", points[points_ofs - 2], points[points_ofs - 1]);
            points[points_ofs++] = glyph_path->vertex_list[i].x - g.ofs_x;                  // 修正路径翻转问题
            points[points_ofs++] = g.box_h - glyph_path->vertex_list[i].y + g.ofs_y;        // 修正路径翻转问题
            //printf("points e (x, y) = (%f, %f).", points[points_ofs - 2], points[points_ofs - 1]);
        } else {
            LV_LOG_WARN("lv_draw_letter: Path resolution error");
            return;
        }
    }
    //printf("segments_num = %d; points_num = %d; points_ofs = %d.", segments_num, points_num, points_ofs);

    // 开始绘制字形
    // 根据路径使用 VG 绘制字形
    //开始 JLVG 渲染动作
    // 1、初始化渲染空间
    uint32_t fb_width;
    uint32_t fb_height;
    uint32_t fb_size;
    uint32_t dest_stride;
    uint8_t *dest_buf;
    uint32_t bytes_per_pixel;
    jlvg_hw_imageformat_t jlvg_dest_cf;
    lv_area_t blend_area;

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
            bytes_per_pixel = sizeof(lv_color_t);

            if (gpos.x < rel_clip_area.x1) {
                blend_area.x1 = rel_clip_area.x1;
            } else {
                blend_area.x1 = gpos.x;
            }

            if (gpos.y < rel_clip_area.y1) {
                blend_area.y1 = rel_clip_area.y1;
            } else {
                blend_area.y1 = gpos.y;
            }

            if ((gpos.x + g.box_w) > rel_clip_area.x2) {
                blend_area.x2 = rel_clip_area.x2;
            } else {
                blend_area.x2 = (gpos.x + g.box_w);
            }

            if ((gpos.y + g.box_h) > rel_clip_area.y2) {
                blend_area.y2 = rel_clip_area.y2;
            } else {
                blend_area.y2 = (gpos.y + g.box_h);
            }

        } else {
            jlvg_dest_cf = LV_GPU_COLOR_ALPHA_FORMAT;
            bytes_per_pixel = LV_IMG_PX_SIZE_ALPHA_BYTE;
            /* 兼容字形本身没有变换相关的配置属性，直接使用裁剪区域作为 VG 的混合区域 */
            lv_area_copy(&blend_area, &rel_clip_area);
        }

    } else {
        jlvg_dest_cf = LV_GPU_COLOR_FORMAT;
        bytes_per_pixel = sizeof(lv_color_t);
        if (gpos.x < rel_clip_area.x1) {
            blend_area.x1 = rel_clip_area.x1;
        } else {
            blend_area.x1 = gpos.x;
        }

        if (gpos.y < rel_clip_area.y1) {
            blend_area.y1 = rel_clip_area.y1;
        } else {
            blend_area.y1 = gpos.y;
        }

        if ((gpos.x + g.box_w) > rel_clip_area.x2) {
            blend_area.x2 = rel_clip_area.x2;
        } else {
            blend_area.x2 = (gpos.x + g.box_w);
        }

        if ((gpos.y + g.box_h) > rel_clip_area.y2) {
            blend_area.y2 = rel_clip_area.y2;
        } else {
            blend_area.y2 = (gpos.y + g.box_h);
        }
    }

#if (JLVG_DRAW_FULL_FB_ENABLE == 1) // 字形绘制的全局 FB 使能只能用于调试！！！！！
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
    dest_buf = draw_ctx->buf + (blend_area.x1 * bytes_per_pixel) + (blend_area.y1 * dest_stride);
#endif
    //printf("fb_width = %d; fb_height = %d; dest_stride = %d.", fb_width, fb_height, dest_stride);

    jlvg_matrix_t user2surface; // 变换矩阵 user to surface
    jlvg_matrix_t surface2paint;// 变换矩阵 surface to paint

    jlvg_surface_t surface;     // 绘制的窗口
    jlvg_rect_t surface_area;   // 绘制的窗口区域:实际就是 layer->buf_area 所在的区域
    jlvg_rect_t draw_area;      // 在窗口内实际要绘制的区域:实际就是 blend_area

    //初始化单位变换矩阵
    jlvg_matrix_set_identity(&user2surface);
    jlvg_matrix_set_identity(&surface2paint);

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
    //printf("0 draw_area (x,y) = (%d, %d); w = %d, y = %d.", draw_area.x, draw_area.y, draw_area.w, draw_area.h);

    //窗口初始化
    jlvg_surface_init(&surface, dest_buf, fb_size, fb_width, fb_height, dest_stride, jlvg_dest_cf, 0, 1, 1, 0);

    // 2、配置绘制路径
    jlvg_path_t glyph_path_to_vg;      // 绘制的字形路径
    jlvg_path_init(&glyph_path_to_vg, JLVG_PATH_DATATYPE_F32, segments_num, segments, points_num, points);
    jlvg_path_update_fill(&glyph_path_to_vg);  //更新路径信息

    // 这一步暂时不需要，接口矩阵计算存在绘制 bug
    //jlvg_boundbox_t bbox_out;
    //jlvg_path_transform_boundbox(&bbox_out, &glyph_path_to_vg.bbox, &user2surface);
    //jlvg_bbox2rect(&draw_area, &bbox_out);
    //printf("1 draw_area (x,y) = (%d, %d); w = %d, y = %d.", draw_area.x, draw_area.y, draw_area.w, draw_area.h);

    // 3、配置变换矩阵，注意：矩阵变换需要在路径配置完成之后
    bool has_angle = false; // TODO: 暂时不支持变换
    bool has_zoom = false;
    lv_point_t glyph_abs;  //字形框(0, 0)原点的绝对位置，不会变化

    if (has_angle || has_zoom) {
        // TODO
    } else {
        //计算变换原点绝对位置在 blend_area 区域的相对位置
#if (JLVG_DRAW_FULL_FB_ENABLE == 1)
        glyph_abs.x = gpos.x;
        glyph_abs.y = gpos.y;
#else
        glyph_abs.x = gpos.x - blend_area.x1;
        glyph_abs.y = gpos.y - blend_area.y1;
#endif
        if ((glyph_abs.x != 0) || (glyph_abs.y != 0)) {
            jlvg_matrix_translate(&user2surface, glyph_abs.x, glyph_abs.y);      // 基于图像(0, 0)原点的绝对位置进行偏移
            //printf("glyph_abs (x,y) = (%d,%d).", glyph_abs.x, glyph_abs.y);
        }
    }

    //4、配置颜色填充
    jlvg_paint_color_t paint_color;
    jlvg_color_t fill_color = {0xff, 0xff, 0xff, 0xff};
    jlvg_color_t draw_color;

    //填充颜色准备
    fill_color.a = dsc->opa;
#if LV_COLOR_DEPTH == 16
    fill_color.r = dsc->color.ch.red << 3;
    fill_color.g = dsc->color.ch.green << 2;
    fill_color.b = dsc->color.ch.blue << 3;
#else
    fill_color.r = dsc->color.ch.red;
    fill_color.g = dsc->color.ch.green;
    fill_color.b = dsc->color.ch.blue;
#endif
    //printf("fill_color: a = 0x%02x; r = 0x%02x; g = 0x%02x; b = 0x%02x.", fill_color.a, fill_color.r, fill_color.g, fill_color.b);

    jlvg_color_premultiply(&fill_color);    // 填充像素预乘
    draw_color = fill_color;
    jlvg_paint_color_init(&paint_color, draw_color); //初始化填充的颜色内容

    // 配置 paint
    jlvg_paint_t *draw_paint;
    draw_paint = &paint_color;

    // 4、硬件绘制
    jlvg_start_frame(g_gpu2p5d, &surface);

    // 非真实显存需要进行一次清屏操作
    if (!is_frame_buf) {
        jlvg_color_t clear_color = {0x00, 0x00, 0x00, 0x00};
        jlvg_clear(g_gpu2p5d, &draw_area, &clear_color);
    }

    jlvg_fill_path(g_gpu2p5d, &draw_area, &glyph_path_to_vg, draw_paint, &user2surface, &surface2paint, blend_mode, VGHW_NON_ZERO);

    //uint32_t gpurun_time = get_system_us();
    jlvg_end_frame(g_gpu2p5d);

    //5、清理现场
    jlvg_path_deinit(&glyph_path_to_vg);
    jlvg_paint_deinit((jlvg_paint_t *)&paint_color);
    jlvg_surface_deinit(&surface);

    //uint32_t end_time = get_system_us();
    //printf("[%s] diff_time = %d(%d+%d)", __func__, (end_time - begin_time), (gpurun_time - begin_time), (end_time - gpurun_time));
}

/**********************
 *   STATIC FUNCTIONS
 **********************/
#endif  // LV_USE_JL_GPU2P5D_DRAW_LETTER
#endif /*LV_USE_GPU_JL_GPU2P5D*/
