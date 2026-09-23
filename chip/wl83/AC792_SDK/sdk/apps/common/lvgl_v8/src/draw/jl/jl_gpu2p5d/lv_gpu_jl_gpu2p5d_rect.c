/**
 * @file lv_gpu_jl_gpu2p5d_rect.c
 *
 */

/*********************
 *      INCLUDES
 *********************/
#include "lv_gpu_jl_gpu2p5d.h"

#if LV_USE_GPU_JL_GPU2P5D
#if LV_USE_JL_GPU2P5D_DRAW_RECT
/*********************
 *      DEFINES
 *********************/

/**********************
 *      TYPEDEFS
 **********************/

/**********************
 *  STATIC PROTOTYPES
 **********************/
static lv_res_t lv_jl_gpu2p5d_draw_bg(lv_draw_ctx_t *draw_ctx, const lv_draw_rect_dsc_t *dsc, const lv_area_t *coords);
static lv_res_t lv_jl_gpu2p5d_draw_bg_img(lv_draw_ctx_t *draw_ctx, const lv_draw_rect_dsc_t *dsc, const lv_area_t *coords);
static lv_res_t lv_jl_gpu2p5d_draw_border(lv_draw_ctx_t *draw_ctx, const lv_draw_rect_dsc_t *dsc, const lv_area_t *coords);

static lv_res_t lv_jl_gpu2p5d_draw_outline(lv_draw_ctx_t *draw_ctx, const lv_draw_rect_dsc_t *dsc, const lv_area_t *coords);

#if LV_DRAW_COMPLEX
static lv_res_t /* LV_ATTRIBUTE_FAST_MEM */ lv_jl_gpu2p5d_draw_shadow(lv_draw_ctx_t *draw_ctx, const lv_draw_rect_dsc_t *dsc,
        const lv_area_t *coords);
#endif

/**********************
 *  STATIC VARIABLES
 **********************/

/**********************
 *      MACROS
 **********************/

/**********************
 *   GLOBAL FUNCTIONS
 **********************/

void lv_draw_jl_gpu2p5d_rect(lv_draw_ctx_t *draw_ctx, const lv_draw_rect_dsc_t *dsc, const lv_area_t *coords)
{
    //printf("%s()", __func__);
    bool mode_flag;
    uint8_t blend_mode = lv_jl_gpu2p5d_get_blend_mode(dsc->blend_mode, &mode_flag);   //根据图像的混合模式获取 VG 配置的混合模式
    if (mode_flag == false) {
        lv_draw_sw_rect(draw_ctx, dsc, coords);
        return;  // 意味着该动作硬件无法绘制，直接交由软件绘制
    }

    lv_draw_rect_dsc_t jlvg_dsc;
    lv_memcpy(&jlvg_dsc, dsc, sizeof(jlvg_dsc));
    jlvg_dsc.bg_opa = 0;
    jlvg_dsc.bg_img_opa = 0;
    jlvg_dsc.border_opa = 0;
    jlvg_dsc.outline_opa = 0;
    jlvg_dsc.shadow_opa = 0;

    // 配置 VG 绘制命令列表
#if LV_DRAW_COMPLEX
    jlvg_dsc.shadow_opa = dsc->shadow_opa;
    if (lv_jl_gpu2p5d_draw_shadow(draw_ctx, &jlvg_dsc, coords) != LV_RES_OK) {
        lv_draw_sw_rect(draw_ctx, &jlvg_dsc, coords);
    }
    jlvg_dsc.shadow_opa = 0;
#endif

    jlvg_dsc.bg_opa = dsc->bg_opa;
    if (lv_jl_gpu2p5d_draw_bg(draw_ctx, &jlvg_dsc, coords) != LV_RES_OK) {
        lv_draw_sw_rect(draw_ctx, &jlvg_dsc, coords);
    }
    jlvg_dsc.bg_opa = 0;

    jlvg_dsc.bg_img_opa = dsc->bg_img_opa;
    if (lv_jl_gpu2p5d_draw_bg_img(draw_ctx, &jlvg_dsc, coords) != LV_RES_OK) {
        lv_draw_sw_rect(draw_ctx, &jlvg_dsc, coords);
    }
    jlvg_dsc.bg_img_opa = 0;

    jlvg_dsc.border_opa = dsc->border_opa;
    if (lv_jl_gpu2p5d_draw_border(draw_ctx, &jlvg_dsc, coords) != LV_RES_OK) {
        lv_draw_sw_rect(draw_ctx, &jlvg_dsc, coords);
    }
    jlvg_dsc.border_opa = 0;

    jlvg_dsc.outline_opa = dsc->outline_opa;
    if (lv_jl_gpu2p5d_draw_outline(draw_ctx, &jlvg_dsc, coords) != LV_RES_OK) {
        lv_draw_sw_rect(draw_ctx, &jlvg_dsc, coords);
    }
    jlvg_dsc.outline_opa = 0;
    LV_ASSERT_MEM_INTEGRITY();
}

void lv_draw_jl_gpu2p5d_bg(lv_draw_ctx_t *draw_ctx, const lv_draw_rect_dsc_t *dsc, const lv_area_t *coords)
{
    //printf("%s()", __func__);
    bool mode_flag;
    uint8_t blend_mode = lv_jl_gpu2p5d_get_blend_mode(dsc->blend_mode, &mode_flag);   //根据图像的混合模式获取 VG 配置的混合模式
    if (mode_flag == false) {
        lv_draw_sw_rect(draw_ctx, dsc, coords);
        return;  // 意味着该动作硬件无法绘制，直接交由软件绘制
    }

    lv_draw_rect_dsc_t jlvg_dsc;
    lv_memcpy(&jlvg_dsc, dsc, sizeof(jlvg_dsc));
    jlvg_dsc.bg_opa = 0;
    jlvg_dsc.bg_img_opa = 0;

#if LV_COLOR_SCREEN_TRANSP && LV_COLOR_DEPTH == 32
    u8 lvgl_get_fb_num(void);
    if (lvgl_get_fb_num() != 0) {
        /** fix bug **/
        /** https://github.com/lvgl/lv_port_win_codeblocks/issues/39 **/
        //lv_memset_00(draw_ctx->buf, lv_area_get_size(draw_ctx->buf_area) * sizeof(lv_color_t));
        uint8_t *_buf_area = (uint8_t *)draw_ctx->buf + (lv_area_get_width(draw_ctx->buf_area) * draw_ctx->clip_area->y1 + draw_ctx->clip_area->x1) * sizeof(lv_color_t);
        uint32_t area_buf_size = lv_area_get_width(draw_ctx->clip_area) * sizeof(lv_color_t);
        uint32_t area_offset = lv_area_get_width(draw_ctx->buf_area) * sizeof(lv_color_t);
        for (int i = 0; i < lv_area_get_height(draw_ctx->clip_area); i++) {
            lv_memset_00(_buf_area, area_buf_size);
            _buf_area += area_offset;
        }
    }
#endif

    jlvg_dsc.bg_opa = dsc->bg_opa;
    if (lv_jl_gpu2p5d_draw_bg(draw_ctx, &jlvg_dsc, coords) != LV_RES_OK) {
        lv_draw_sw_rect(draw_ctx, &jlvg_dsc, coords);
    }
    jlvg_dsc.bg_opa = 0;

    jlvg_dsc.bg_img_opa = dsc->bg_img_opa;
    if (lv_jl_gpu2p5d_draw_bg_img(draw_ctx, &jlvg_dsc, coords) != LV_RES_OK) {
        lv_draw_sw_rect(draw_ctx, &jlvg_dsc, coords);
    }
    jlvg_dsc.bg_img_opa = 0;
}

/**********************
 *   STATIC FUNCTIONS
 **********************/

static void lv_draw_jl_gpu2p5d_rect_path_fill(const lv_draw_rect_dsc_t *dsc, lv_area_t coords, jlvg_path_t *path)
{
    if (dsc->radius != 0) { /* 有圆角属性 */
        //printf("radius = %d", dsc->radius);

        //圆角矩形路径描述
        //确定四个圆弧的圆心位置以及四个起始点 + 四个终点，以左上角圆弧为起点： 1 + 3 + 1 + 3 + 1 + 3 + 1 + 3 + 1   //13, p0 -> p3 顺时针
        int32_t coords_w = lv_area_get_width(&coords);
        int32_t coords_h = lv_area_get_height(&coords);
        float short_side = LV_MIN(coords_w, coords_h);
        float rout = LV_MIN((float)dsc->radius, (short_side / 2.0));    // 计算圆角的半径

        jlvg_point2_t p0;   // 左上角圆弧
        p0.x =  coords.x1 + rout;
        p0.y =  coords.y1 + rout;
        jlvg_point2_t p01;
        p01.x = coords.x1 + rout;
        p01.y = coords.y1;
        jlvg_point2_t p02;
        p02.x = coords.x1;
        p02.y = coords.y1 + rout;

        jlvg_point2_t p1;   // 左下角圆弧
        p1.x = coords.x1 + rout;
        p1.y = coords.y2 - rout + 1;
        jlvg_point2_t p11;
        p11.x = coords.x1;
        p11.y = coords.y2 - rout + 1;
        jlvg_point2_t p12;
        p12.x = coords.x1 + rout;
        p12.y = coords.y2 + 1;

        jlvg_point2_t p2;   // 右下角圆弧
        p2.x = coords.x2 - rout + 1;
        p2.y = coords.y2 - rout + 1;
        jlvg_point2_t p21;
        p21.x = coords.x2 - rout + 1;
        p21.y = coords.y2 + 1;
        jlvg_point2_t p22;
        p22.x = coords.x2 + 1;
        p22.y = coords.y2 - rout + 1;

        jlvg_point2_t p3;   // 右上角圆弧
        p3.x = coords.x2 - rout + 1;
        p3.y = coords.y1 + rout;
        jlvg_point2_t p31;
        p31.x = coords.x2 + 1;
        p31.y = coords.y1 + rout;
        jlvg_point2_t p32;
        p32.x = coords.x2 - rout + 1;
        p32.y = coords.y1;

        int nseg_tmp = 0;
        int npoints_tmp = 0;
        uint32_t nsegments = 0;
        uint8_t segments[1 + 3 + 1 + 3 + 1 + 3 + 1 + 3 + 1];     //13
        int npoints = 0;
        float points[2 + 2 * 6 + 2 + 2 * 6 + 2 + 2 * 6 + 2 + 2 * 6 + 2];

        //moveto
        segments[nsegments++] = VGHW_MOVE_TO;   //起点 and 终点
        points[npoints++] = p01.x;
        points[npoints++] = p01.y;

        //1st arc
        jlvg_path_circle2beizer(&segments[nsegments], &nseg_tmp, &points[npoints], &npoints_tmp,
                                p0.x, p0.y, rout, p01.x, p01.y, p02.x, p02.y, 1, 0);
        nsegments += nseg_tmp;
        npoints += npoints_tmp;

        //1st line to
        segments[nsegments++] = VGHW_LINE_TO;
        points[npoints++] = p11.x;
        points[npoints++] = p11.y;

        //2nd arc
        jlvg_path_circle2beizer(&segments[nsegments], &nseg_tmp, &points[npoints], &npoints_tmp,
                                p1.x, p1.y, rout, p11.x, p11.y, p12.x, p12.y, 1, 0);
        nsegments += nseg_tmp;
        npoints += npoints_tmp;

        //2nd line to
        segments[nsegments++] = VGHW_LINE_TO;
        points[npoints++] = p21.x;
        points[npoints++] = p21.y;

        //3rd arc
        jlvg_path_circle2beizer(&segments[nsegments], &nseg_tmp, &points[npoints], &npoints_tmp,
                                p2.x, p2.y, rout, p21.x, p21.y, p22.x, p22.y, 1, 0);
        nsegments += nseg_tmp;
        npoints += npoints_tmp;

        //3rd line to
        segments[nsegments++] = VGHW_LINE_TO;
        points[npoints++] = p31.x;
        points[npoints++] = p31.y;

        //4th arc
        jlvg_path_circle2beizer(&segments[nsegments], &nseg_tmp, &points[npoints], &npoints_tmp,
                                p3.x, p3.y, rout, p31.x, p31.y, p32.x, p32.y, 1, 0);
        nsegments += nseg_tmp;
        npoints += npoints_tmp;

        //4th line to
        segments[nsegments++] = VGHW_LINE_TO;
        points[npoints++] = p01.x;
        points[npoints++] = p01.y;

        jlvg_path_init(path, JLVG_PATH_DATATYPE_F32, nsegments, segments, npoints, points);
        jlvg_path_update_fill(path);  //更新路径信息
    } else {
        //printf("no radius");
        //常规矩形路径描述
        //描述四个角的路径
        uint32_t nsegments = 1 + 1 + 1 + 1 + 1;//5
        uint8_t segments[1 + 1 + 1 + 1 + 1] = { VGHW_MOVE_TO, VGHW_HLINE_TO, VGHW_VLINE_TO, VGHW_HLINE_TO, VGHW_VLINE_TO };
        float points[2 + 2 + 2];
        points[0] = points[4] = coords.x1;    // 原点(起点和终点)的 x
        points[1] = points[5] = coords.y1;    // 原点(起点和终点)的 y
        points[2] = coords.x2 + 1;  // 矩形原点对角的 x
        points[3] = coords.y2 + 1;  // 矩形原点对角的 y

        jlvg_path_init(path, JLVG_PATH_DATATYPE_F32, nsegments, segments, sizeof(points) / sizeof(float), points);
        jlvg_path_update_fill(path);  //更新路径信息
    }
}

static void lv_draw_jl_gpu2p5d_border_path_fill(const lv_draw_rect_dsc_t *dsc, lv_area_t coords, int32_t rout, int32_t rin, jlvg_path_t *path)
{
    //printf("rout = %d; rin = %d.", rout, rin);
    uint8_t rin_ofs;
    if (rout > dsc->border_width) {
        rin_ofs = 0;
    } else {
        rin_ofs = dsc->border_width - rout;
    }

    jlvg_point2_t p0;   // 左上角外圆圆弧
    p0.x =  coords.x1 + rout;
    p0.y =  coords.y1 + rout;
    jlvg_point2_t p01;
    p01.x = coords.x1 + rout;
    p01.y = coords.y1;
    jlvg_point2_t p02;
    p02.x = coords.x1;
    p02.y = coords.y1 + rout;

    jlvg_point2_t p1;   // 左下角外圆圆弧
    p1.x = coords.x1 + rout;
    p1.y = coords.y2 - rout + 1;
    jlvg_point2_t p11;
    p11.x = coords.x1;
    p11.y = coords.y2 - rout + 1;
    jlvg_point2_t p12;
    p12.x = coords.x1 + rout;
    p12.y = coords.y2 + 1;

    jlvg_point2_t p2;   // 右下角外圆圆弧
    p2.x = coords.x2 - rout + 1;
    p2.y = coords.y2 - rout + 1;
    jlvg_point2_t p21;
    p21.x = coords.x2 - rout + 1;
    p21.y = coords.y2 + 1;
    jlvg_point2_t p22;
    p22.x = coords.x2 + 1;
    p22.y = coords.y2 - rout + 1;

    jlvg_point2_t p3;   // 右上角外圆圆弧
    p3.x = coords.x2 - rout + 1;
    p3.y = coords.y1 + rout;
    jlvg_point2_t p31;
    p31.x = coords.x2 + 1;
    p31.y = coords.y1 + rout;
    jlvg_point2_t p32;
    p32.x = coords.x2 - rout + 1;
    p32.y = coords.y1;

    jlvg_point2_t p0_in;   // 左上角内圆圆弧
    p0_in.x =  coords.x1 + rout + rin_ofs;
    p0_in.y =  coords.y1 + rout + rin_ofs;
    jlvg_point2_t p01_in;
    p01_in.x = p0_in.x;
    p01_in.y = p0_in.y - rin;
    jlvg_point2_t p02_in;
    p02_in.x = p0_in.x - rin;
    p02_in.y = p0_in.y;

    jlvg_point2_t p1_in;   // 左下角内圆圆弧
    p1_in.x = coords.x1 + rout + rin_ofs;
    p1_in.y = coords.y2 - rout - rin_ofs + 1;
    jlvg_point2_t p11_in;
    p11_in.x = p1_in.x - rin;
    p11_in.y = p1_in.y;
    jlvg_point2_t p12_in;
    p12_in.x = p1_in.x;
    p12_in.y = p1_in.y + rin;

    jlvg_point2_t p2_in;   // 右下角内圆圆弧
    p2_in.x = coords.x2 - rout - rin_ofs + 1;
    p2_in.y = coords.y2 - rout - rin_ofs + 1;
    jlvg_point2_t p21_in;
    p21_in.x = p2_in.x;
    p21_in.y = p2_in.y + rin;
    jlvg_point2_t p22_in;
    p22_in.x = p2_in.x + rin;
    p22_in.y = p2_in.y;

    jlvg_point2_t p3_in;   // 右上角内圆圆弧
    p3_in.x = coords.x2 - rout - rin_ofs + 1;
    p3_in.y = coords.y1 + rout + rin_ofs;
    jlvg_point2_t p31_in;
    p31_in.x = p3_in.x + rin;
    p31_in.y = p3_in.y;
    jlvg_point2_t p32_in;
    p32_in.x = p3_in.x;
    p32_in.y = p3_in.y - rin;

    if (dsc->border_side == LV_BORDER_SIDE_FULL) {  // 四边
        //圆角矩形边框路径描述
        //确定八个圆弧的圆心位置以及八个起始点 + 八个终点，以左上角圆弧为起点： (1 + 3 + 1 + 3 + 1 + 3 + 1 + 3 + 1) * 2
        //17 * 2, p0 -> p3 顺时针
        int nseg_tmp = 0;
        int npoints_tmp = 0;
        uint32_t nsegments = 0;
        uint8_t segments[2 * (1 + 3 + 1 + 3 + 1 + 3 + 1 + 3 + 1)];     //17 * 2
        int npoints = 0;
        float points[2 * (2 + 2 * 6 + 2 + 2 * 6 + 2 + 2 * 6 + 2 + 2 * 6 + 2)];

        // 内圈 : 内外圈圆心一样
        //moveto
        segments[nsegments++] = VGHW_MOVE_TO;   //起点 and 终点
        points[npoints++] = p01_in.x;
        points[npoints++] = p01_in.y;

        if (rin > 0) {
            //1st arc
            jlvg_path_circle2beizer(&segments[nsegments], &nseg_tmp, &points[npoints], &npoints_tmp,
                                    p0.x, p0.y, rin, p01_in.x, p01_in.y, p02_in.x, p02_in.y, 1, 0);
            nsegments += nseg_tmp;
            npoints += npoints_tmp;
        }

        //1st line to
        segments[nsegments++] = VGHW_LINE_TO;
        points[npoints++] = p11_in.x;
        points[npoints++] = p11_in.y;

        if (rin > 0) {
            //2nd arc
            jlvg_path_circle2beizer(&segments[nsegments], &nseg_tmp, &points[npoints], &npoints_tmp,
                                    p1.x, p1.y, rin, p11_in.x, p11_in.y, p12_in.x, p12_in.y, 1, 0);
            nsegments += nseg_tmp;
            npoints += npoints_tmp;
        }

        //2nd line to
        segments[nsegments++] = VGHW_LINE_TO;
        points[npoints++] = p21_in.x;
        points[npoints++] = p21_in.y;

        if (rin > 0) {
            //3rd arc
            jlvg_path_circle2beizer(&segments[nsegments], &nseg_tmp, &points[npoints], &npoints_tmp,
                                    p2.x, p2.y, rin, p21_in.x, p21_in.y, p22_in.x, p22_in.y, 1, 0);
            nsegments += nseg_tmp;
            npoints += npoints_tmp;
        }

        //3rd line to
        segments[nsegments++] = VGHW_LINE_TO;
        points[npoints++] = p31_in.x;
        points[npoints++] = p31_in.y;

        if (rin > 0) {
            //4th arc
            jlvg_path_circle2beizer(&segments[nsegments], &nseg_tmp, &points[npoints], &npoints_tmp,
                                    p3.x, p3.y, rin, p31_in.x, p31_in.y, p32_in.x, p32_in.y, 1, 0);
            nsegments += nseg_tmp;
            npoints += npoints_tmp;
        }

        //4th line to
        segments[nsegments++] = VGHW_LINE_TO;
        points[npoints++] = p01_in.x;
        points[npoints++] = p01_in.y;

        //printf("0 nsegments = %d; npoints = %d.", nsegments, npoints);

        // 外圈 : 与内圈方向相反
        //moveto
        segments[nsegments++] = VGHW_MOVE_TO;   //起点 and 终点
        points[npoints++] = p32.x;
        points[npoints++] = p32.y;

        if (rout > 0) {
            //5th arc
            jlvg_path_circle2beizer(&segments[nsegments], &nseg_tmp, &points[npoints], &npoints_tmp,
                                    p3.x, p3.y, rout, p32.x, p32.y, p31.x, p31.y, 0, 0);
            nsegments += nseg_tmp;
            npoints += npoints_tmp;
        }

        //5th line to
        segments[nsegments++] = VGHW_LINE_TO;
        points[npoints++] = p22.x;
        points[npoints++] = p22.y;

        if (rout > 0) {
            //6th arc
            jlvg_path_circle2beizer(&segments[nsegments], &nseg_tmp, &points[npoints], &npoints_tmp,
                                    p2.x, p2.y, rout, p22.x, p22.y, p21.x, p21.y, 0, 0);
            nsegments += nseg_tmp;
            npoints += npoints_tmp;
        }

        //6th line to
        segments[nsegments++] = VGHW_LINE_TO;
        points[npoints++] = p12.x;
        points[npoints++] = p12.y;

        if (rout > 0) {
            //7th arc
            jlvg_path_circle2beizer(&segments[nsegments], &nseg_tmp, &points[npoints], &npoints_tmp,
                                    p1.x, p1.y, rout, p12.x, p12.y, p11.x, p11.y, 0, 0);
            nsegments += nseg_tmp;
            npoints += npoints_tmp;
        }

        //7th line to
        segments[nsegments++] = VGHW_LINE_TO;
        points[npoints++] = p02.x;
        points[npoints++] = p02.y;

        if (rout > 0) {
            //8th arc
            jlvg_path_circle2beizer(&segments[nsegments], &nseg_tmp, &points[npoints], &npoints_tmp,
                                    p0.x, p0.y, rout, p02.x, p02.y, p01.x, p01.y, 0, 0);
            nsegments += nseg_tmp;
            npoints += npoints_tmp;
        }

        //8th line to
        segments[nsegments++] = VGHW_LINE_TO;
        points[npoints++] = p32.x;
        points[npoints++] = p32.y;

        //printf("1 nsegments = %d; npoints = %d.", nsegments, npoints);

        jlvg_path_init(path, JLVG_PATH_DATATYPE_F32, nsegments, segments, npoints, points);
        jlvg_path_update_fill(path);  //更新路径信息

    } else if ((dsc->border_side == (LV_BORDER_SIDE_BOTTOM | LV_BORDER_SIDE_TOP | LV_BORDER_SIDE_LEFT)) || \
               (dsc->border_side == (LV_BORDER_SIDE_BOTTOM | LV_BORDER_SIDE_TOP | LV_BORDER_SIDE_RIGHT)) || \
               (dsc->border_side == (LV_BORDER_SIDE_BOTTOM | LV_BORDER_SIDE_LEFT | LV_BORDER_SIDE_RIGHT)) || \
               (dsc->border_side == (LV_BORDER_SIDE_TOP | LV_BORDER_SIDE_LEFT | LV_BORDER_SIDE_RIGHT))) {
        // 三边
        //printf("side : 0x%02x.", dsc->border_side);
        //圆角矩形边框路径描述: 三条边的情况
        //确定8个圆弧的圆心位置以及8个起始点 + 8个终点，以左上角圆弧为起点： (1 + 3 + 1 + 3 + 3 + 1 + 3) * 2
        //15 * 2, p0 -> p3 顺时针
        int nseg_tmp = 0;
        int npoints_tmp = 0;
        uint32_t nsegments = 0;
        uint8_t segments[2 * (1 + 3 + 3 + 1 + 3 + 1 + 3 + 1 + 3 + 3 + 1 + 3 + 1 + 3 + 1)];     //23
        int npoints = 0;
        float points[2 * (2 + 2 * 6 + 2 * 6 + 2 + 2 * 6 + 2 + 2 * 6 + 2 + 2 * 6 + 2 + 2 * 6 + 2 + 2 * 6 + 2 + 2 * 6 + 2)];

        jlvg_point2_t p_tmp0;
        jlvg_point2_t p_tmp01;
        jlvg_point2_t p_tmp02;
        jlvg_point2_t p_tmp1;
        jlvg_point2_t p_tmp11;
        jlvg_point2_t p_tmp12;
        jlvg_point2_t p_tmp2;
        jlvg_point2_t p_tmp21;
        jlvg_point2_t p_tmp22;
        jlvg_point2_t p_tmp3;
        jlvg_point2_t p_tmp31;
        jlvg_point2_t p_tmp32;

        jlvg_point2_t p_tmp0_in;
        jlvg_point2_t p_tmp01_in;
        jlvg_point2_t p_tmp02_in;
        jlvg_point2_t p_tmp1_in;
        jlvg_point2_t p_tmp11_in;
        jlvg_point2_t p_tmp12_in;
        jlvg_point2_t p_tmp2_in;
        jlvg_point2_t p_tmp21_in;
        jlvg_point2_t p_tmp22_in;
        jlvg_point2_t p_tmp3_in;
        jlvg_point2_t p_tmp31_in;
        jlvg_point2_t p_tmp32_in;

        if (dsc->border_side == (LV_BORDER_SIDE_BOTTOM | LV_BORDER_SIDE_LEFT | LV_BORDER_SIDE_RIGHT)) {
            p_tmp0 = p0;
            p_tmp01 = p01;
            p_tmp02 = p02;
            p_tmp1 = p1;
            p_tmp11 = p11;
            p_tmp12 = p12;
            p_tmp2 = p2;
            p_tmp21 = p21;
            p_tmp22 = p22;
            p_tmp3 = p3;
            p_tmp31 = p31;
            p_tmp32 = p32;

            // 左上角内圆圆弧
            p_tmp0_in.x = coords.x1 + rout + rin_ofs;
            p_tmp0_in.y = coords.y1 + rin;
            p_tmp01_in.x = p_tmp0_in.x;
            p_tmp01_in.y = p_tmp0_in.y - rin;
            p_tmp02_in.x = p_tmp0_in.x - rin;
            p_tmp02_in.y = p_tmp0_in.y;

            p_tmp1_in = p1_in;
            p_tmp11_in = p11_in;
            p_tmp12_in = p12_in;

            p_tmp2_in = p2_in;
            p_tmp21_in = p21_in;
            p_tmp22_in = p22_in;

            // 右上角内圆圆弧
            p_tmp3_in.x = coords.x2 - rout - rin_ofs + 1;
            p_tmp3_in.y = coords.y1 + rin;
            p_tmp31_in.x = p_tmp3_in.x + rin;
            p_tmp31_in.y = p_tmp3_in.y;
            p_tmp32_in.x = p_tmp3_in.x;
            p_tmp32_in.y = p_tmp3_in.y - rin;
        } else if (dsc->border_side == (LV_BORDER_SIDE_BOTTOM | LV_BORDER_SIDE_TOP | LV_BORDER_SIDE_RIGHT)) {
            p_tmp0 = p1;
            p_tmp01 = p11;
            p_tmp02 = p12;
            p_tmp1 = p2;
            p_tmp11 = p21;
            p_tmp12 = p22;
            p_tmp2 = p3;
            p_tmp21 = p31;
            p_tmp22 = p32;
            p_tmp3 = p0;
            p_tmp31 = p01;
            p_tmp32 = p02;

            // 左下角内圆圆弧
            p_tmp0_in.x = coords.x1 + rin;
            p_tmp0_in.y = coords.y2 - rout - rin_ofs + 1;
            p_tmp01_in.x = p_tmp0_in.x - rin;
            p_tmp01_in.y = p_tmp0_in.y;
            p_tmp02_in.x = p_tmp0_in.x;
            p_tmp02_in.y = p_tmp0_in.y + rin;

            p_tmp1_in = p2_in;
            p_tmp11_in = p21_in;
            p_tmp12_in = p22_in;

            p_tmp2_in = p3_in;
            p_tmp21_in = p31_in;
            p_tmp22_in = p32_in;

            // 左上角内圆圆弧
            p_tmp3_in.x = coords.x1 + rin;
            p_tmp3_in.y = coords.y1 + rout + rin_ofs;
            p_tmp31_in.x = p_tmp3_in.x;
            p_tmp31_in.y = p_tmp3_in.y - rin;
            p_tmp32_in.x = p_tmp3_in.x - rin;
            p_tmp32_in.y = p_tmp3_in.y;
        } else if (dsc->border_side == (LV_BORDER_SIDE_TOP | LV_BORDER_SIDE_LEFT | LV_BORDER_SIDE_RIGHT)) {
            p_tmp0 = p2;
            p_tmp01 = p21;
            p_tmp02 = p22;
            p_tmp1 = p3;
            p_tmp11 = p31;
            p_tmp12 = p32;
            p_tmp2 = p0;
            p_tmp21 = p01;
            p_tmp22 = p02;
            p_tmp3 = p1;
            p_tmp31 = p11;
            p_tmp32 = p12;

            // 右下角内圆圆弧
            p_tmp0_in.x = coords.x2 - rout - rin_ofs + 1;
            p_tmp0_in.y = coords.y2 - rin + 1;
            p_tmp01_in.x = p_tmp0_in.x;
            p_tmp01_in.y = p_tmp0_in.y + rin;
            p_tmp02_in.x = p_tmp0_in.x + rin;
            p_tmp02_in.y = p_tmp0_in.y;

            p_tmp1_in = p3_in;
            p_tmp11_in = p31_in;
            p_tmp12_in = p32_in;

            p_tmp2_in = p0_in;
            p_tmp21_in = p01_in;
            p_tmp22_in = p02_in;

            // 左下角内圆圆弧
            p_tmp3_in.x = coords.x1 + rout + rin_ofs;
            p_tmp3_in.y = coords.y2 - rin + 1;
            p_tmp31_in.x = p_tmp3_in.x - rin;
            p_tmp31_in.y = p_tmp3_in.y;
            p_tmp32_in.x = p_tmp3_in.x;
            p_tmp32_in.y = p_tmp3_in.y + rin;
        } else if (dsc->border_side == (LV_BORDER_SIDE_BOTTOM | LV_BORDER_SIDE_TOP | LV_BORDER_SIDE_LEFT)) {
            p_tmp0 = p3;
            p_tmp01 = p31;
            p_tmp02 = p32;
            p_tmp1 = p0;
            p_tmp11 = p01;
            p_tmp12 = p02;
            p_tmp2 = p1;
            p_tmp21 = p11;
            p_tmp22 = p12;
            p_tmp3 = p2;
            p_tmp31 = p21;
            p_tmp32 = p22;

            // 右上角内圆圆弧
            p_tmp0_in.x = coords.x2 - rin + 1;
            p_tmp0_in.y = coords.y1 + rout + rin_ofs;
            p_tmp01_in.x = p_tmp0_in.x + rin;
            p_tmp01_in.y = p_tmp0_in.y;
            p_tmp02_in.x = p_tmp0_in.x;
            p_tmp02_in.y = p_tmp0_in.y - rin;

            p_tmp1_in = p0_in;
            p_tmp11_in = p01_in;
            p_tmp12_in = p02_in;

            p_tmp2_in = p1_in;
            p_tmp21_in = p11_in;
            p_tmp22_in = p12_in;

            // 右下角内圆圆弧
            p_tmp3_in.x = coords.x2 - rin + 1;
            p_tmp3_in.y = coords.y2 - rout - rin_ofs + 1;
            p_tmp31_in.x = p_tmp3_in.x;
            p_tmp31_in.y = p_tmp3_in.y + rin;
            p_tmp32_in.x = p_tmp3_in.x + rin;
            p_tmp32_in.y = p_tmp3_in.y;
        }

        //moveto
        segments[nsegments++] = VGHW_MOVE_TO;   //起点 and 终点
        points[npoints++] = p_tmp02_in.x;
        points[npoints++] = p_tmp02_in.y;

        if (rin > 0) {
            //1st arc 顺时针
            jlvg_path_circle2beizer(&segments[nsegments], &nseg_tmp, &points[npoints], &npoints_tmp,
                                    p_tmp0_in.x, p_tmp0_in.y, rin, p_tmp02_in.x, p_tmp02_in.y, p_tmp01_in.x, p_tmp01_in.y, 0, 0);
            nsegments += nseg_tmp;
            npoints += npoints_tmp;
        } else {
            segments[nsegments++] = VGHW_LINE_TO;
            points[npoints++] = p_tmp01.x;
            points[npoints++] = p_tmp01.y;
        }

        if (rout > 0) {
            //2nd arc 逆时针
            jlvg_path_circle2beizer(&segments[nsegments], &nseg_tmp, &points[npoints], &npoints_tmp,
                                    p_tmp0.x, p_tmp0.y, rout, p_tmp01.x, p_tmp01.y, p_tmp02.x, p_tmp02.y, 1, 0);
            nsegments += nseg_tmp;
            npoints += npoints_tmp;
        }

        //1st line to
        segments[nsegments++] = VGHW_LINE_TO;
        points[npoints++] = p_tmp11.x;
        points[npoints++] = p_tmp11.y;

        if (rout > 0) {
            //3rd arc 逆时针
            jlvg_path_circle2beizer(&segments[nsegments], &nseg_tmp, &points[npoints], &npoints_tmp,
                                    p_tmp1.x, p_tmp1.y, rout, p_tmp11.x, p_tmp11.y, p_tmp12.x, p_tmp12.y, 1, 0);
            nsegments += nseg_tmp;
            npoints += npoints_tmp;
        }

        //2nd line to
        segments[nsegments++] = VGHW_LINE_TO;
        points[npoints++] = p_tmp21.x;
        points[npoints++] = p_tmp21.y;

        if (rout > 0) {
            //4th arc 逆时针
            jlvg_path_circle2beizer(&segments[nsegments], &nseg_tmp, &points[npoints], &npoints_tmp,
                                    p_tmp2.x, p_tmp2.y, rout, p_tmp21.x, p_tmp21.y, p_tmp22.x, p_tmp22.y, 1, 0);
            nsegments += nseg_tmp;
            npoints += npoints_tmp;
        }

        //3rd line to
        segments[nsegments++] = VGHW_LINE_TO;
        points[npoints++] = p_tmp31.x;
        points[npoints++] = p_tmp31.y;

        if (rout > 0) {
            //5th arc 逆时针
            jlvg_path_circle2beizer(&segments[nsegments], &nseg_tmp, &points[npoints], &npoints_tmp,
                                    p_tmp3.x, p_tmp3.y, rout, p_tmp31.x, p_tmp31.y, p_tmp32.x, p_tmp32.y, 1, 0);
            nsegments += nseg_tmp;
            npoints += npoints_tmp;
        }

        if (rin > 0) {
            //6th arc 顺时针
            jlvg_path_circle2beizer(&segments[nsegments], &nseg_tmp, &points[npoints], &npoints_tmp,
                                    p_tmp3_in.x, p_tmp3_in.y, rin, p_tmp32_in.x, p_tmp32_in.y, p_tmp31_in.x, p_tmp31_in.y, 0, 0);
            nsegments += nseg_tmp;
            npoints += npoints_tmp;
        } else {
            segments[nsegments++] = VGHW_LINE_TO;
            points[npoints++] = p_tmp31_in.x;
            points[npoints++] = p_tmp31_in.y;
        }

        //4th line to
        segments[nsegments++] = VGHW_LINE_TO;
        points[npoints++] = p_tmp22_in.x;
        points[npoints++] = p_tmp22_in.y;

        if (rin > 0) {
            //7th arc 顺时针
            jlvg_path_circle2beizer(&segments[nsegments], &nseg_tmp, &points[npoints], &npoints_tmp,
                                    p_tmp2_in.x, p_tmp2_in.y, rin, p_tmp22_in.x, p_tmp22_in.y, p_tmp21_in.x, p_tmp21_in.y, 0, 0);
            nsegments += nseg_tmp;
            npoints += npoints_tmp;
        }

        //5th line to
        segments[nsegments++] = VGHW_LINE_TO;
        points[npoints++] = p_tmp12_in.x;
        points[npoints++] = p_tmp12_in.y;

        if (rin > 0) {
            //8th arc 顺时针
            jlvg_path_circle2beizer(&segments[nsegments], &nseg_tmp, &points[npoints], &npoints_tmp,
                                    p_tmp1_in.x, p_tmp1_in.y, rin, p_tmp12_in.x, p_tmp12_in.y, p_tmp11_in.x, p_tmp11_in.y, 0, 0);
            nsegments += nseg_tmp;
            npoints += npoints_tmp;
        }

        //6th line to
        segments[nsegments++] = VGHW_LINE_TO;
        points[npoints++] = p_tmp02_in.x;
        points[npoints++] = p_tmp02_in.y;

        //printf("nsegments = %d; npoints = %d.", nsegments, npoints);

        jlvg_path_init(path, JLVG_PATH_DATATYPE_F32, nsegments, segments, npoints, points);
        jlvg_path_update_fill(path);  //更新路径信息
    } else if ((dsc->border_side == (LV_BORDER_SIDE_BOTTOM | LV_BORDER_SIDE_LEFT)) || \
               (dsc->border_side == (LV_BORDER_SIDE_BOTTOM | LV_BORDER_SIDE_RIGHT)) || \
               (dsc->border_side == (LV_BORDER_SIDE_TOP | LV_BORDER_SIDE_LEFT)) || \
               (dsc->border_side == (LV_BORDER_SIDE_TOP | LV_BORDER_SIDE_RIGHT))) {
        // 双边邻边
        //printf("side : 0x%02x.", dsc->border_side);
        //圆角矩形边框路径描述: 两条相邻边的情况
        //确定6个圆弧的圆心位置以及6个起始点 + 6个终点，以左上角圆弧为起点： (1 + 3 + 3 + 1 + 3 + 1 + 3 + 3 + 1 + 3 + 1) * 2
        //15 * 2, p0 -> p3 顺时针
        int nseg_tmp = 0;
        int npoints_tmp = 0;
        uint32_t nsegments = 0;
        uint8_t segments[2 * (1 + 3 + 3 + 1 + 3 + 1 + 3 + 3 + 1 + 3 + 1)];     //23
        int npoints = 0;
        float points[2 * (2 + 2 * 6 + 2 * 6 + 2 + 2 * 6 + 2 + 2 * 6 + 2 * 6 + 2 + 2 * 6 + 2)];

        jlvg_point2_t p_tmp0;
        jlvg_point2_t p_tmp01;
        jlvg_point2_t p_tmp02;
        jlvg_point2_t p_tmp1;
        jlvg_point2_t p_tmp11;
        jlvg_point2_t p_tmp12;
        jlvg_point2_t p_tmp2;
        jlvg_point2_t p_tmp21;
        jlvg_point2_t p_tmp22;

        jlvg_point2_t p_tmp0_in;
        jlvg_point2_t p_tmp01_in;
        jlvg_point2_t p_tmp02_in;
        jlvg_point2_t p_tmp1_in;
        jlvg_point2_t p_tmp11_in;
        jlvg_point2_t p_tmp12_in;
        jlvg_point2_t p_tmp2_in;
        jlvg_point2_t p_tmp21_in;
        jlvg_point2_t p_tmp22_in;

        if (dsc->border_side == (LV_BORDER_SIDE_BOTTOM | LV_BORDER_SIDE_LEFT)) {
            p_tmp0 = p0;
            p_tmp01 = p01;
            p_tmp02 = p02;
            p_tmp1 = p1;
            p_tmp11 = p11;
            p_tmp12 = p12;
            p_tmp2 = p2;
            p_tmp21 = p21;
            p_tmp22 = p22;

            // 左上角内圆圆弧
            p_tmp0_in.x = coords.x1 + rout + rin_ofs;
            p_tmp0_in.y = coords.y1 + rin;
            p_tmp01_in.x = p_tmp0_in.x;
            p_tmp01_in.y = p_tmp0_in.y - rin;
            p_tmp02_in.x = p_tmp0_in.x - rin;
            p_tmp02_in.y = p_tmp0_in.y;

            p_tmp1_in = p1_in;
            p_tmp11_in = p11_in;
            p_tmp12_in = p12_in;

            // 右下角内圆圆弧
            p_tmp2_in.x = coords.x2 - rin + 1;
            p_tmp2_in.y = coords.y2 - rout - rin_ofs + 1;
            p_tmp21_in.x = p_tmp2_in.x;
            p_tmp21_in.y = p_tmp2_in.y + rin;
            p_tmp22_in.x = p_tmp2_in.x + rin;
            p_tmp22_in.y = p_tmp2_in.y;
        } else if (dsc->border_side == (LV_BORDER_SIDE_BOTTOM | LV_BORDER_SIDE_RIGHT)) {
            p_tmp0 = p1;
            p_tmp01 = p11;
            p_tmp02 = p12;
            p_tmp1 = p2;
            p_tmp11 = p21;
            p_tmp12 = p22;
            p_tmp2 = p3;
            p_tmp21 = p31;
            p_tmp22 = p32;

            // 左下角内圆圆弧
            p_tmp0_in.x = coords.x1 + rin;
            p_tmp0_in.y = coords.y2 - rout - rin_ofs + 1;
            p_tmp01_in.x = p_tmp0_in.x - rin;
            p_tmp01_in.y = p_tmp0_in.y;
            p_tmp02_in.x = p_tmp0_in.x;
            p_tmp02_in.y = p_tmp0_in.y + rin;

            p_tmp1_in = p2_in;
            p_tmp11_in = p21_in;
            p_tmp12_in = p22_in;

            // 右上角内圆圆弧
            p_tmp2_in.x = coords.x2 - rout - rin_ofs + 1;
            p_tmp2_in.y = coords.y1 + rin;
            p_tmp21_in.x = p_tmp2_in.x + rin;
            p_tmp21_in.y = p_tmp2_in.y;
            p_tmp22_in.x = p_tmp2_in.x;
            p_tmp22_in.y = p_tmp2_in.y - rin;
        } else if (dsc->border_side == (LV_BORDER_SIDE_TOP | LV_BORDER_SIDE_RIGHT)) {
            p_tmp0 = p2;
            p_tmp01 = p21;
            p_tmp02 = p22;
            p_tmp1 = p3;
            p_tmp11 = p31;
            p_tmp12 = p32;
            p_tmp2 = p0;
            p_tmp21 = p01;
            p_tmp22 = p02;

            // 右下角内圆圆弧
            p_tmp0_in.x = coords.x2 - rout - rin_ofs + 1;
            p_tmp0_in.y = coords.y2 - rin + 1;
            p_tmp01_in.x = p_tmp0_in.x;
            p_tmp01_in.y = p_tmp0_in.y + rin;
            p_tmp02_in.x = p_tmp0_in.x + rin;
            p_tmp02_in.y = p_tmp0_in.y;

            p_tmp1_in = p3_in;
            p_tmp11_in = p31_in;
            p_tmp12_in = p32_in;

            // 左上角内圆圆弧
            p_tmp2_in.x = coords.x1 + rin;
            p_tmp2_in.y = coords.y1 + rout + rin_ofs;
            p_tmp21_in.x = p_tmp2_in.x;
            p_tmp21_in.y = p_tmp2_in.y - rin;
            p_tmp22_in.x = p_tmp2_in.x - rin;
            p_tmp22_in.y = p_tmp2_in.y;
        } else if (dsc->border_side == (LV_BORDER_SIDE_TOP | LV_BORDER_SIDE_LEFT)) {
            p_tmp0 = p3;
            p_tmp01 = p31;
            p_tmp02 = p32;
            p_tmp1 = p0;
            p_tmp11 = p01;
            p_tmp12 = p02;
            p_tmp2 = p1;
            p_tmp21 = p11;
            p_tmp22 = p12;

            // 右上角内圆圆弧
            p_tmp0_in.x = coords.x2 - rin + 1;
            p_tmp0_in.y = coords.y1 + rout + rin_ofs;
            p_tmp01_in.x = p_tmp0_in.x + rin;
            p_tmp01_in.y = p_tmp0_in.y;
            p_tmp02_in.x = p_tmp0_in.x;
            p_tmp02_in.y = p_tmp0_in.y - rin;

            p_tmp1_in = p0_in;
            p_tmp11_in = p01_in;
            p_tmp12_in = p02_in;

            // 左下角内圆圆弧
            p_tmp2_in.x = coords.x1 + rout + rin_ofs;
            p_tmp2_in.y = coords.y2 - rin + 1;
            p_tmp21_in.x = p_tmp2_in.x - rin;
            p_tmp21_in.y = p_tmp2_in.y;
            p_tmp22_in.x = p_tmp2_in.x;
            p_tmp22_in.y = p_tmp2_in.y + rin;
        }

        //moveto
        segments[nsegments++] = VGHW_MOVE_TO;   //起点 and 终点
        points[npoints++] = p_tmp02_in.x;
        points[npoints++] = p_tmp02_in.y;

        if (rin > 0) {
            //1st arc 顺时针
            jlvg_path_circle2beizer(&segments[nsegments], &nseg_tmp, &points[npoints], &npoints_tmp,
                                    p_tmp0_in.x, p_tmp0_in.y, rin, p_tmp02_in.x, p_tmp02_in.y, p_tmp01_in.x, p_tmp01_in.y, 0, 0);
            nsegments += nseg_tmp;
            npoints += npoints_tmp;
        } else {
            segments[nsegments++] = VGHW_LINE_TO;
            points[npoints++] = p_tmp01.x;
            points[npoints++] = p_tmp01.y;
        }

        if (rout > 0) {
            //2nd arc 逆时针
            jlvg_path_circle2beizer(&segments[nsegments], &nseg_tmp, &points[npoints], &npoints_tmp,
                                    p_tmp0.x, p_tmp0.y, rout, p_tmp01.x, p_tmp01.y, p_tmp02.x, p_tmp02.y, 1, 0);
            nsegments += nseg_tmp;
            npoints += npoints_tmp;
        }

        //1st line to
        segments[nsegments++] = VGHW_LINE_TO;
        points[npoints++] = p_tmp11.x;
        points[npoints++] = p_tmp11.y;

        if (rout > 0) {
            //3rd arc 逆时针
            jlvg_path_circle2beizer(&segments[nsegments], &nseg_tmp, &points[npoints], &npoints_tmp,
                                    p_tmp1.x, p_tmp1.y, rout, p_tmp11.x, p_tmp11.y, p_tmp12.x, p_tmp12.y, 1, 0);
            nsegments += nseg_tmp;
            npoints += npoints_tmp;
        }

        //2nd line to
        segments[nsegments++] = VGHW_LINE_TO;
        points[npoints++] = p_tmp21.x;
        points[npoints++] = p_tmp21.y;

        if (rout > 0) {
            //4th arc 逆时针
            jlvg_path_circle2beizer(&segments[nsegments], &nseg_tmp, &points[npoints], &npoints_tmp,
                                    p_tmp2.x, p_tmp2.y, rout, p_tmp21.x, p_tmp21.y, p_tmp22.x, p_tmp22.y, 1, 0);
            nsegments += nseg_tmp;
            npoints += npoints_tmp;
        }

        if (rin > 0) {
            //5th arc 顺时针
            jlvg_path_circle2beizer(&segments[nsegments], &nseg_tmp, &points[npoints], &npoints_tmp,
                                    p_tmp2_in.x, p_tmp2_in.y, rin, p_tmp22_in.x, p_tmp22_in.y, p_tmp21_in.x, p_tmp21_in.y, 0, 0);
            nsegments += nseg_tmp;
            npoints += npoints_tmp;
        } else {
            segments[nsegments++] = VGHW_LINE_TO;
            points[npoints++] = p_tmp21_in.x;
            points[npoints++] = p_tmp21_in.y;
        }

        //3rd line to
        segments[nsegments++] = VGHW_LINE_TO;
        points[npoints++] = p_tmp12_in.x;
        points[npoints++] = p_tmp12_in.y;

        if (rin > 0) {
            //6th arc 顺时针
            jlvg_path_circle2beizer(&segments[nsegments], &nseg_tmp, &points[npoints], &npoints_tmp,
                                    p_tmp1_in.x, p_tmp1_in.y, rin, p_tmp12_in.x, p_tmp12_in.y, p_tmp11_in.x, p_tmp11_in.y, 0, 0);
            nsegments += nseg_tmp;
            npoints += npoints_tmp;
        }

        //4th line to
        segments[nsegments++] = VGHW_LINE_TO;
        points[npoints++] = p_tmp02_in.x;
        points[npoints++] = p_tmp02_in.y;

        //printf("nsegments = %d; npoints = %d.", nsegments, npoints);

        jlvg_path_init(path, JLVG_PATH_DATATYPE_F32, nsegments, segments, npoints, points);
        jlvg_path_update_fill(path);  //更新路径信息
    } else if ((!((dsc->border_side & LV_BORDER_SIDE_LEFT) || (dsc->border_side & LV_BORDER_SIDE_RIGHT))) || \
               (!((dsc->border_side & LV_BORDER_SIDE_BOTTOM) || (dsc->border_side & LV_BORDER_SIDE_TOP)))) {
        // 对边 + 单边
        //圆角矩形边框路径描述: 对边或者只有一条单边的情况
        //最多确定八个圆弧的圆心位置以及八个起始点 + 八个终点，以左上角圆弧为起点： (1 + 3 + 1 + 3 + 3 + 1 + 3) * 2
        //15 * 2, p0 -> p3 顺时针
        int nseg_tmp = 0;
        int npoints_tmp = 0;
        uint32_t nsegments = 0;
        uint8_t segments[2 * (1 + 3 + 1 + 3 + 3 + 1 + 3)];     //15
        int npoints = 0;
        float points[2 * (2 + 2 * 6 + 2 + 2 * 6 + 2 * 6 + 2 + 2 * 6)];

        jlvg_point2_t p_tmp0;
        jlvg_point2_t p_tmp01;
        jlvg_point2_t p_tmp02;
        jlvg_point2_t p_tmp1;
        jlvg_point2_t p_tmp11;
        jlvg_point2_t p_tmp12;


        jlvg_point2_t p_tmp0_in;
        jlvg_point2_t p_tmp01_in;
        jlvg_point2_t p_tmp02_in;
        jlvg_point2_t p_tmp1_in;
        jlvg_point2_t p_tmp11_in;
        jlvg_point2_t p_tmp12_in;

        //printf("side : 0x%02x.", dsc->border_side);
        if (dsc->border_side & LV_BORDER_SIDE_BOTTOM) {
            p_tmp0 = p1;
            p_tmp01 = p11;
            p_tmp02 = p12;
            p_tmp1 = p2;
            p_tmp11 = p21;
            p_tmp12 = p22;

            // 左下角内圆圆弧
            p_tmp0_in.x = coords.x1 + rin;
            p_tmp0_in.y = coords.y2 - rout - rin_ofs + 1;
            p_tmp01_in.x = p_tmp0_in.x - rin;
            p_tmp01_in.y = p_tmp0_in.y;
            p_tmp02_in.x = p_tmp0_in.x;
            p_tmp02_in.y = p_tmp0_in.y + rin;

            // 右下角内圆圆弧
            p_tmp1_in.x = coords.x2 - rin + 1;
            p_tmp1_in.y = coords.y2 - rout - rin_ofs + 1;
            p_tmp11_in.x = p_tmp1_in.x;
            p_tmp11_in.y = p_tmp1_in.y + rin;
            p_tmp12_in.x = p_tmp1_in.x + rin;
            p_tmp12_in.y = p_tmp1_in.y;
        }

        if (dsc->border_side & LV_BORDER_SIDE_LEFT) {
            p_tmp0 = p0;
            p_tmp01 = p01;
            p_tmp02 = p02;
            p_tmp1 = p1;
            p_tmp11 = p11;
            p_tmp12 = p12;

            // 左上角内圆圆弧
            p_tmp0_in.x = coords.x1 + rout + rin_ofs;
            p_tmp0_in.y = coords.y1 + rin;
            p_tmp01_in.x = p_tmp0_in.x;
            p_tmp01_in.y = p_tmp0_in.y - rin;
            p_tmp02_in.x = p_tmp0_in.x - rin;
            p_tmp02_in.y = p_tmp0_in.y;

            // 左下角内圆圆弧
            p_tmp1_in.x = coords.x1 + rout + rin_ofs;
            p_tmp1_in.y = coords.y2 - rin + 1;
            p_tmp11_in.x = p_tmp1_in.x - rin;
            p_tmp11_in.y = p_tmp1_in.y;
            p_tmp12_in.x = p_tmp1_in.x;
            p_tmp12_in.y = p_tmp1_in.y + rin;
        }

        if ((dsc->border_side & LV_BORDER_SIDE_BOTTOM) || (dsc->border_side & LV_BORDER_SIDE_LEFT)) {
            //moveto
            segments[nsegments++] = VGHW_MOVE_TO;   //起点 and 终点
            points[npoints++] = p_tmp02_in.x;
            points[npoints++] = p_tmp02_in.y;

            if (rin > 0) {
                //1st arc 顺时针
                jlvg_path_circle2beizer(&segments[nsegments], &nseg_tmp, &points[npoints], &npoints_tmp,
                                        p_tmp0_in.x, p_tmp0_in.y, rin, p_tmp02_in.x, p_tmp02_in.y, p_tmp01_in.x, p_tmp01_in.y, 0, 0);
                nsegments += nseg_tmp;
                npoints += npoints_tmp;
            } else {
                segments[nsegments++] = VGHW_LINE_TO;
                points[npoints++] = p_tmp01.x;
                points[npoints++] = p_tmp01.y;
            }

            if (rout > 0) {
                //2nd arc 逆时针
                jlvg_path_circle2beizer(&segments[nsegments], &nseg_tmp, &points[npoints], &npoints_tmp,
                                        p_tmp0.x, p_tmp0.y, rout, p_tmp01.x, p_tmp01.y, p_tmp02.x, p_tmp02.y, 1, 0);
                nsegments += nseg_tmp;
                npoints += npoints_tmp;
            }

            //1st line to
            segments[nsegments++] = VGHW_LINE_TO;
            points[npoints++] = p_tmp11.x;
            points[npoints++] = p_tmp11.y;

            if (rout > 0) {
                //3rd arc 逆时针
                jlvg_path_circle2beizer(&segments[nsegments], &nseg_tmp, &points[npoints], &npoints_tmp,
                                        p_tmp1.x, p_tmp1.y, rout, p_tmp11.x, p_tmp11.y, p_tmp12.x, p_tmp12.y, 1, 0);
                nsegments += nseg_tmp;
                npoints += npoints_tmp;
            }

            if (rin > 0) {
                //4th arc 顺时针
                jlvg_path_circle2beizer(&segments[nsegments], &nseg_tmp, &points[npoints], &npoints_tmp,
                                        p_tmp1_in.x, p_tmp1_in.y, rin, p_tmp12_in.x, p_tmp12_in.y, p_tmp11_in.x, p_tmp11_in.y, 0, 0);
                nsegments += nseg_tmp;
                npoints += npoints_tmp;
            } else {
                segments[nsegments++] = VGHW_LINE_TO;
                points[npoints++] = p_tmp11_in.x;
                points[npoints++] = p_tmp11_in.y;
            }

            //2nd line to
            segments[nsegments++] = VGHW_LINE_TO;
            points[npoints++] = p_tmp02_in.x;
            points[npoints++] = p_tmp02_in.y;
        }

        if (dsc->border_side & LV_BORDER_SIDE_TOP) {
            p_tmp0 = p3;
            p_tmp01 = p31;
            p_tmp02 = p32;
            p_tmp1 = p0;
            p_tmp11 = p01;
            p_tmp12 = p02;

            // 右上角内圆圆弧
            p_tmp0_in.x = coords.x2 - rin + 1;
            p_tmp0_in.y = coords.y1 + rout + rin_ofs;
            p_tmp01_in.x = p_tmp0_in.x + rin;
            p_tmp01_in.y = p_tmp0_in.y;
            p_tmp02_in.x = p_tmp0_in.x;
            p_tmp02_in.y = p_tmp0_in.y - rin;

            // 左上角内圆圆弧
            p_tmp1_in.x = coords.x1 + rin;
            p_tmp1_in.y = coords.y1 + rout + rin_ofs;
            p_tmp11_in.x = p_tmp1_in.x;
            p_tmp11_in.y = p_tmp1_in.y - rin;
            p_tmp12_in.x = p_tmp1_in.x - rin;
            p_tmp12_in.y = p_tmp1_in.y;
        }

        if (dsc->border_side & LV_BORDER_SIDE_RIGHT) {
            p_tmp0 = p2;
            p_tmp01 = p21;
            p_tmp02 = p22;
            p_tmp1 = p3;
            p_tmp11 = p31;
            p_tmp12 = p32;

            // 右下角内圆圆弧
            p_tmp0_in.x = coords.x2 - rout - rin_ofs + 1;
            p_tmp0_in.y = coords.y2 - rin + 1;
            p_tmp01_in.x = p_tmp0_in.x;
            p_tmp01_in.y = p_tmp0_in.y + rin;
            p_tmp02_in.x = p_tmp0_in.x + rin;
            p_tmp02_in.y = p_tmp0_in.y;

            // 右上角内圆圆弧
            p_tmp1_in.x = coords.x2 - rout - rin_ofs + 1;
            p_tmp1_in.y = coords.y1 + rin;
            p_tmp11_in.x = p_tmp1_in.x + rin;
            p_tmp11_in.y = p_tmp1_in.y;
            p_tmp12_in.x = p_tmp1_in.x;
            p_tmp12_in.y = p_tmp1_in.y - rin;
        }

        if ((dsc->border_side & LV_BORDER_SIDE_TOP) || (dsc->border_side & LV_BORDER_SIDE_RIGHT)) {
            //moveto
            segments[nsegments++] = VGHW_MOVE_TO;   //起点 and 终点
            points[npoints++] = p_tmp02_in.x;
            points[npoints++] = p_tmp02_in.y;

            if (rin > 0) {
                //1st arc 顺时针
                jlvg_path_circle2beizer(&segments[nsegments], &nseg_tmp, &points[npoints], &npoints_tmp,
                                        p_tmp0_in.x, p_tmp0_in.y, rin, p_tmp02_in.x, p_tmp02_in.y, p_tmp01_in.x, p_tmp01_in.y, 0, 0);
                nsegments += nseg_tmp;
                npoints += npoints_tmp;
            } else {
                segments[nsegments++] = VGHW_LINE_TO;
                points[npoints++] = p_tmp01.x;
                points[npoints++] = p_tmp01.y;
            }

            if (rout > 0) {
                //2nd arc 逆时针
                jlvg_path_circle2beizer(&segments[nsegments], &nseg_tmp, &points[npoints], &npoints_tmp,
                                        p_tmp0.x, p_tmp0.y, rout, p_tmp01.x, p_tmp01.y, p_tmp02.x, p_tmp02.y, 1, 0);
                nsegments += nseg_tmp;
                npoints += npoints_tmp;
            }

            //1st line to
            segments[nsegments++] = VGHW_LINE_TO;
            points[npoints++] = p_tmp11.x;
            points[npoints++] = p_tmp11.y;

            if (rout > 0) {
                //3rd arc 逆时针
                jlvg_path_circle2beizer(&segments[nsegments], &nseg_tmp, &points[npoints], &npoints_tmp,
                                        p_tmp1.x, p_tmp1.y, rout, p_tmp11.x, p_tmp11.y, p_tmp12.x, p_tmp12.y, 1, 0);
                nsegments += nseg_tmp;
                npoints += npoints_tmp;
            }

            if (rin > 0) {
                //4th arc 顺时针
                jlvg_path_circle2beizer(&segments[nsegments], &nseg_tmp, &points[npoints], &npoints_tmp,
                                        p_tmp1_in.x, p_tmp1_in.y, rin, p_tmp12_in.x, p_tmp12_in.y, p_tmp11_in.x, p_tmp11_in.y, 0, 0);
                nsegments += nseg_tmp;
                npoints += npoints_tmp;
            } else {
                segments[nsegments++] = VGHW_LINE_TO;
                points[npoints++] = p_tmp11_in.x;
                points[npoints++] = p_tmp11_in.y;
            }

            //2nd line to
            segments[nsegments++] = VGHW_LINE_TO;
            points[npoints++] = p_tmp02_in.x;
            points[npoints++] = p_tmp02_in.y;
        }

        jlvg_path_init(path, JLVG_PATH_DATATYPE_F32, nsegments, segments, npoints, points);
        jlvg_path_update_fill(path);  //更新路径信息
    } else {
        printf("error: side 0x%02x is non-support!!", dsc->border_side);
    }
}

static void lv_draw_jl_gpu2p5d_outline_path_fill(const lv_draw_rect_dsc_t *dsc, lv_area_t coords, int32_t rout, int32_t rin, jlvg_path_t *path)
{
    //printf("rout = %d; rin = %d.", rout, rin);
    uint8_t rin_ofs;
    if (rout > dsc->border_width) {
        rin_ofs = 0;
    } else {
        rin_ofs = dsc->outline_width - rout;
    }

    jlvg_point2_t p0;   // 左上角外圆圆弧
    p0.x =  coords.x1 + rout;
    p0.y =  coords.y1 + rout;
    jlvg_point2_t p01;
    p01.x = coords.x1 + rout;
    p01.y = coords.y1;
    jlvg_point2_t p02;
    p02.x = coords.x1;
    p02.y = coords.y1 + rout;

    jlvg_point2_t p1;   // 左下角外圆圆弧
    p1.x = coords.x1 + rout;
    p1.y = coords.y2 - rout + 1;
    jlvg_point2_t p11;
    p11.x = coords.x1;
    p11.y = coords.y2 - rout + 1;
    jlvg_point2_t p12;
    p12.x = coords.x1 + rout;
    p12.y = coords.y2 + 1;

    jlvg_point2_t p2;   // 右下角外圆圆弧
    p2.x = coords.x2 - rout + 1;
    p2.y = coords.y2 - rout + 1;
    jlvg_point2_t p21;
    p21.x = coords.x2 - rout + 1;
    p21.y = coords.y2 + 1;
    jlvg_point2_t p22;
    p22.x = coords.x2 + 1;
    p22.y = coords.y2 - rout + 1;

    jlvg_point2_t p3;   // 右上角外圆圆弧
    p3.x = coords.x2 - rout + 1;
    p3.y = coords.y1 + rout;
    jlvg_point2_t p31;
    p31.x = coords.x2 + 1;
    p31.y = coords.y1 + rout;
    jlvg_point2_t p32;
    p32.x = coords.x2 - rout + 1;
    p32.y = coords.y1;

    jlvg_point2_t p0_in;   // 左上角内圆圆弧
    p0_in.x =  coords.x1 + rout + rin_ofs;
    p0_in.y =  coords.y1 + rout + rin_ofs;
    jlvg_point2_t p01_in;
    p01_in.x = p0_in.x;
    p01_in.y = p0_in.y - rin;
    jlvg_point2_t p02_in;
    p02_in.x = p0_in.x - rin;
    p02_in.y = p0_in.y;

    jlvg_point2_t p1_in;   // 左下角内圆圆弧
    p1_in.x = coords.x1 + rout + rin_ofs;
    p1_in.y = coords.y2 - rout - rin_ofs + 1;
    jlvg_point2_t p11_in;
    p11_in.x = p1_in.x - rin;
    p11_in.y = p1_in.y;
    jlvg_point2_t p12_in;
    p12_in.x = p1_in.x;
    p12_in.y = p1_in.y + rin;

    jlvg_point2_t p2_in;   // 右下角内圆圆弧
    p2_in.x = coords.x2 - rout - rin_ofs + 1;
    p2_in.y = coords.y2 - rout - rin_ofs + 1;
    jlvg_point2_t p21_in;
    p21_in.x = p2_in.x;
    p21_in.y = p2_in.y + rin;
    jlvg_point2_t p22_in;
    p22_in.x = p2_in.x + rin;
    p22_in.y = p2_in.y;

    jlvg_point2_t p3_in;   // 右上角内圆圆弧
    p3_in.x = coords.x2 - rout - rin_ofs + 1;
    p3_in.y = coords.y1 + rout + rin_ofs;
    jlvg_point2_t p31_in;
    p31_in.x = p3_in.x + rin;
    p31_in.y = p3_in.y;
    jlvg_point2_t p32_in;
    p32_in.x = p3_in.x;
    p32_in.y = p3_in.y - rin;

    //圆角矩形边框路径描述
    //确定八个圆弧的圆心位置以及八个起始点 + 八个终点，以左上角圆弧为起点： (1 + 3 + 1 + 3 + 1 + 3 + 1 + 3 + 1) * 2
    //17 * 2, p0 -> p3 顺时针
    int nseg_tmp = 0;
    int npoints_tmp = 0;
    uint32_t nsegments = 0;
    uint8_t segments[2 * (1 + 3 + 1 + 3 + 1 + 3 + 1 + 3 + 1)];     //17 * 2
    int npoints = 0;
    float points[2 * (2 + 2 * 6 + 2 + 2 * 6 + 2 + 2 * 6 + 2 + 2 * 6 + 2)];

    // 内圈 : 内外圈圆心一样
    //moveto
    segments[nsegments++] = VGHW_MOVE_TO;   //起点 and 终点
    points[npoints++] = p01_in.x;
    points[npoints++] = p01_in.y;

    if (rin > 0) {
        //1st arc
        jlvg_path_circle2beizer(&segments[nsegments], &nseg_tmp, &points[npoints], &npoints_tmp,
                                p0.x, p0.y, rin, p01_in.x, p01_in.y, p02_in.x, p02_in.y, 1, 0);
        nsegments += nseg_tmp;
        npoints += npoints_tmp;
    }

    //1st line to
    segments[nsegments++] = VGHW_LINE_TO;
    points[npoints++] = p11_in.x;
    points[npoints++] = p11_in.y;

    if (rin > 0) {
        //2nd arc
        jlvg_path_circle2beizer(&segments[nsegments], &nseg_tmp, &points[npoints], &npoints_tmp,
                                p1.x, p1.y, rin, p11_in.x, p11_in.y, p12_in.x, p12_in.y, 1, 0);
        nsegments += nseg_tmp;
        npoints += npoints_tmp;
    }

    //2nd line to
    segments[nsegments++] = VGHW_LINE_TO;
    points[npoints++] = p21_in.x;
    points[npoints++] = p21_in.y;

    if (rin > 0) {
        //3rd arc
        jlvg_path_circle2beizer(&segments[nsegments], &nseg_tmp, &points[npoints], &npoints_tmp,
                                p2.x, p2.y, rin, p21_in.x, p21_in.y, p22_in.x, p22_in.y, 1, 0);
        nsegments += nseg_tmp;
        npoints += npoints_tmp;
    }

    //3rd line to
    segments[nsegments++] = VGHW_LINE_TO;
    points[npoints++] = p31_in.x;
    points[npoints++] = p31_in.y;

    if (rin > 0) {
        //4th arc
        jlvg_path_circle2beizer(&segments[nsegments], &nseg_tmp, &points[npoints], &npoints_tmp,
                                p3.x, p3.y, rin, p31_in.x, p31_in.y, p32_in.x, p32_in.y, 1, 0);
        nsegments += nseg_tmp;
        npoints += npoints_tmp;
    }

    //4th line to
    segments[nsegments++] = VGHW_LINE_TO;
    points[npoints++] = p01_in.x;
    points[npoints++] = p01_in.y;

    //printf("0 nsegments = %d; npoints = %d.", nsegments, npoints);

    // 外圈 : 与内圈方向相反
    //moveto
    segments[nsegments++] = VGHW_MOVE_TO;   //起点 and 终点
    points[npoints++] = p32.x;
    points[npoints++] = p32.y;

    //5th arc
    jlvg_path_circle2beizer(&segments[nsegments], &nseg_tmp, &points[npoints], &npoints_tmp,
                            p3.x, p3.y, rout, p32.x, p32.y, p31.x, p31.y, 0, 0);
    nsegments += nseg_tmp;
    npoints += npoints_tmp;

    //5th line to
    segments[nsegments++] = VGHW_LINE_TO;
    points[npoints++] = p22.x;
    points[npoints++] = p22.y;

    //6th arc
    jlvg_path_circle2beizer(&segments[nsegments], &nseg_tmp, &points[npoints], &npoints_tmp,
                            p2.x, p2.y, rout, p22.x, p22.y, p21.x, p21.y, 0, 0);
    nsegments += nseg_tmp;
    npoints += npoints_tmp;

    //6th line to
    segments[nsegments++] = VGHW_LINE_TO;
    points[npoints++] = p12.x;
    points[npoints++] = p12.y;

    //7th arc
    jlvg_path_circle2beizer(&segments[nsegments], &nseg_tmp, &points[npoints], &npoints_tmp,
                            p1.x, p1.y, rout, p12.x, p12.y, p11.x, p11.y, 0, 0);
    nsegments += nseg_tmp;
    npoints += npoints_tmp;

    //7th line to
    segments[nsegments++] = VGHW_LINE_TO;
    points[npoints++] = p02.x;
    points[npoints++] = p02.y;

    //8th arc
    jlvg_path_circle2beizer(&segments[nsegments], &nseg_tmp, &points[npoints], &npoints_tmp,
                            p0.x, p0.y, rout, p02.x, p02.y, p01.x, p01.y, 0, 0);
    nsegments += nseg_tmp;
    npoints += npoints_tmp;

    //8th line to
    segments[nsegments++] = VGHW_LINE_TO;
    points[npoints++] = p32.x;
    points[npoints++] = p32.y;

    //printf("1 nsegments = %d; npoints = %d.", nsegments, npoints);

    jlvg_path_init(path, JLVG_PATH_DATATYPE_F32, nsegments, segments, npoints, points);
    jlvg_path_update_fill(path);  //更新路径信息
}

#if 0
static void lv_draw_jl_gpu2p5d_shadow_bg_path_fill(jlvg_point2_t point0, jlvg_point2_t point1, float radius, jlvg_path_t *path)
{
    if (radius != 0.0f) { /* 有圆角属性 */
        //printf("radius = %d", dsc->radius);

        //圆角矩形路径描述
        //确定四个圆弧的圆心位置以及四个起始点 + 四个终点，以左上角圆弧为起点： 1 + 3 + 1 + 3 + 1 + 3 + 1 + 3 + 1   //13, p0 -> p3 顺时针
        jlvg_point2_t p0;   // 左上角圆弧
        p0.x =  point0.x + radius;
        p0.y =  point0.y + radius;
        jlvg_point2_t p01;
        p01.x = point0.x + radius;
        p01.y = point0.y;
        jlvg_point2_t p02;
        p02.x = point0.x;
        p02.y = point0.y + radius;

        jlvg_point2_t p1;   // 左下角圆弧
        p1.x = point0.x + radius;
        p1.y = point1.y - radius;
        jlvg_point2_t p11;
        p11.x = point0.x;
        p11.y = point1.y - radius;
        jlvg_point2_t p12;
        p12.x = point0.x + radius;
        p12.y = point1.y;

        jlvg_point2_t p2;   // 右下角圆弧
        p2.x = point1.x - radius;
        p2.y = point1.y - radius;
        jlvg_point2_t p21;
        p21.x = point1.x - radius;
        p21.y = point1.y;
        jlvg_point2_t p22;
        p22.x = point1.x;
        p22.y = point1.y - radius;

        jlvg_point2_t p3;   // 右上角圆弧
        p3.x = point1.x - radius;
        p3.y = point0.y + radius;
        jlvg_point2_t p31;
        p31.x = point1.x;
        p31.y = point0.y + radius;
        jlvg_point2_t p32;
        p32.x = point1.x - radius;
        p32.y = point0.y;

        int nseg_tmp = 0;
        int npoints_tmp = 0;
        uint32_t nsegments = 0;
        uint8_t segments[1 + 3 + 1 + 3 + 1 + 3 + 1 + 3 + 1];     //13
        int npoints = 0;
        float points[2 + 2 * 6 + 2 + 2 * 6 + 2 + 2 * 6 + 2 + 2 * 6 + 2];

        //moveto
        segments[nsegments++] = VGHW_MOVE_TO;   //起点 and 终点
        points[npoints++] = p01.x;
        points[npoints++] = p01.y;

        //1st arc
        jlvg_path_circle2beizer(&segments[nsegments], &nseg_tmp, &points[npoints], &npoints_tmp,
                                p0.x, p0.y, radius, p01.x, p01.y, p02.x, p02.y, 1, 0);
        nsegments += nseg_tmp;
        npoints += npoints_tmp;

        //1st line to
        segments[nsegments++] = VGHW_LINE_TO;
        points[npoints++] = p11.x;
        points[npoints++] = p11.y;

        //2nd arc
        jlvg_path_circle2beizer(&segments[nsegments], &nseg_tmp, &points[npoints], &npoints_tmp,
                                p1.x, p1.y, radius, p11.x, p11.y, p12.x, p12.y, 1, 0);
        nsegments += nseg_tmp;
        npoints += npoints_tmp;

        //2nd line to
        segments[nsegments++] = VGHW_LINE_TO;
        points[npoints++] = p21.x;
        points[npoints++] = p21.y;

        //3rd arc
        jlvg_path_circle2beizer(&segments[nsegments], &nseg_tmp, &points[npoints], &npoints_tmp,
                                p2.x, p2.y, radius, p21.x, p21.y, p22.x, p22.y, 1, 0);
        nsegments += nseg_tmp;
        npoints += npoints_tmp;

        //3rd line to
        segments[nsegments++] = VGHW_LINE_TO;
        points[npoints++] = p31.x;
        points[npoints++] = p31.y;

        //4th arc
        jlvg_path_circle2beizer(&segments[nsegments], &nseg_tmp, &points[npoints], &npoints_tmp,
                                p3.x, p3.y, radius, p31.x, p31.y, p32.x, p32.y, 1, 0);
        nsegments += nseg_tmp;
        npoints += npoints_tmp;

        //4th line to
        segments[nsegments++] = VGHW_LINE_TO;
        points[npoints++] = p01.x;
        points[npoints++] = p01.y;

        jlvg_path_init(path, JLVG_PATH_DATATYPE_F32, nsegments, segments, npoints, points);
        jlvg_path_update_fill(path);  //更新路径信息
    } else {
        //printf("no radius");
        //常规矩形路径描述
        //描述四个角的路径
        uint32_t nsegments = 1 + 1 + 1 + 1 + 1;//5
        uint8_t segments[1 + 1 + 1 + 1 + 1] = { VGHW_MOVE_TO, VGHW_HLINE_TO, VGHW_VLINE_TO, VGHW_HLINE_TO, VGHW_VLINE_TO };
        float points[2 + 2 + 2];
        points[0] = points[4] = point0.x;    // 原点(起点和终点)的 x
        points[1] = points[5] = point0.y;    // 原点(起点和终点)的 y
        points[2] = point1.x;  // 矩形原点对角的 x
        points[3] = point1.y;  // 矩形原点对角的 y

        jlvg_path_init(path, JLVG_PATH_DATATYPE_F32, nsegments, segments, sizeof(points) / sizeof(float), points);
        jlvg_path_update_fill(path);  //更新路径信息
    }
}
#endif

static lv_res_t lv_jl_gpu2p5d_draw_bg(lv_draw_ctx_t *draw_ctx, const lv_draw_rect_dsc_t *dsc, const lv_area_t *coords)
{
    //printf("%s()", __func__);
    if (dsc->bg_opa <= LV_OPA_MIN) {
        return LV_RES_OK;   // 意味着软件也不需要渲染动作
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

    lv_area_t rel_coords;
    lv_area_copy(&rel_coords, coords);

    /*If the border fully covers make the bg area 1px smaller to avoid artifacts on the corners*/
    if (dsc->border_width > 1 && dsc->border_opa >= LV_OPA_MAX && dsc->radius != 0) {
        rel_coords.x1 += (dsc->border_side & LV_BORDER_SIDE_LEFT) ? 1 : 0;
        rel_coords.y1 += (dsc->border_side & LV_BORDER_SIDE_TOP) ? 1 : 0;
        rel_coords.x2 -= (dsc->border_side & LV_BORDER_SIDE_RIGHT) ? 1 : 0;
        rel_coords.y2 -= (dsc->border_side & LV_BORDER_SIDE_BOTTOM) ? 1 : 0;
    }
    lv_area_move(&rel_coords, -draw_ctx->buf_area->x1, -draw_ctx->buf_area->y1);    // 重新确定在显存中的相对位置
    //printf("rel_coords (x1,y1) = (%d,%d); (x2,y2) = (%d,%d).", rel_coords.x1, rel_coords.y1, rel_coords.x2, rel_coords.y2);

    lv_area_t rel_clip_area;
    lv_area_copy(&rel_clip_area, draw_ctx->clip_area);
    lv_area_move(&rel_clip_area, -draw_ctx->buf_area->x1, -draw_ctx->buf_area->y1);    // 重新确定在显存中的相对位置

    lv_area_t blend_area;   //这个区域无论是帧buff还是行buff都是相对的新的绘制区域
    if (!_lv_area_intersect(&blend_area, &rel_coords, &rel_clip_area)) {
        return LV_RES_OK;   // 意味着软件也不需要渲染动作
    }
    //printf("blend_area (x1,y1) = (%d,%d); (x2,y2) = (%d,%d).", blend_area.x1, blend_area.y1, blend_area.x2, blend_area.y2);

    // 判断不支持 VG 绘制的属性并退出
    bool mask_any = lv_draw_mask_is_any(&rel_coords);
    uint8_t blend_mode = lv_jl_gpu2p5d_get_blend_mode(dsc->blend_mode, NULL);   //根据图像的混合模式获取 VG 配置的混合模式
    if (mask_any == true) {
        return LV_RES_INV;  // 意味着该动作硬件无法绘制，重新交由软件绘制
    }

    lv_grad_dir_t grad_dir = dsc->bg_grad.dir;
    lv_color_t bg_color = ((grad_dir == LV_GRAD_DIR_NONE) ? dsc->bg_color : dsc->bg_grad.stops[0].color);
    if (bg_color.full == dsc->bg_grad.stops[LV_GRADIENT_MAX_STOPS - 1].color.full) {
        grad_dir = LV_GRAD_DIR_NONE;
    }
    // 针对渐变属性说明：不考虑 lv_dither_mode_t 字段的影响
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

    jlvg_matrix_t user2surface; // 变换矩阵 user to surface
    jlvg_matrix_t surface2paint;// 变换矩阵 surface to paint

    jlvg_surface_t surface;     // 绘制的窗口
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
    //printf("draw_area (x,y) = (%d,%d); w = %d, y = %d.", draw_area.x, draw_area.y, draw_area.w, draw_area.h);

    //窗口初始化
    jlvg_surface_init(&surface, dest_buf, fb_size, fb_width, fb_height, dest_stride, jlvg_dest_cf, 0, 1, 1, 0);

    // 2、配置绘制路径
    jlvg_path_t rect_path;      // 绘制的矩形路径, 最终的绘制区域是 blend_area
    lv_area_t rect_area;      // 绘制矩形的区域
    lv_area_copy(&rect_area, &rel_coords);
#if (JLVG_DRAW_FULL_FB_ENABLE == 1)
    // nothing
#else
    lv_area_move(&rect_area, -blend_area.x1, -blend_area.y1); // 由于开窗限制在了绘制区域，因此绘制坐标需要平移到原点
#endif
    lv_draw_jl_gpu2p5d_rect_path_fill(dsc, rect_area, &rect_path);

    //3、配置颜色填充
    //渐变属性填充颜色
    jlvg_paint_linear_t paint_linear;   // 渐变渲染的颜色
    /* 注意 stops_count 和 LV_GRADIENT_MAX_STOPS 的取值: 目前只支持两个渐变控制点，即起始点和终点 */
    LV_ASSERT((LV_GRADIENT_MAX_STOPS == 2));
    jlvg_color_t rampstops[LV_GRADIENT_MAX_STOPS];  // 渐变颜色阶梯
    jlvg_point2_t gc_point[LV_GRADIENT_MAX_STOPS];  // 渐变控制点

    //正常填充颜色
    jlvg_paint_color_t paint_color;     // 正常渲染的颜色
    jlvg_color_t fill_color;

#if LV_COLOR_DEPTH == 16
    if (dsc->bg_grad.dir != (lv_grad_dir_t)LV_GRAD_DIR_NONE) { /* 有渐变属性 */
        if (dsc->bg_grad.dir == (lv_grad_dir_t)LV_GRAD_DIR_HOR) {
            gc_point[0].x = rect_area.x1 + ((rect_area.x2 - rect_area.x1 + 1) * (dsc->bg_grad.stops[0].frac) >> 8);
            gc_point[0].y = rect_area.y1;
            gc_point[1].x = rect_area.x1 + ((rect_area.x2 - rect_area.x1 + 1) * (dsc->bg_grad.stops[1].frac) >> 8);
            gc_point[1].y = rect_area.y1;
            if (gc_point[0].x == gc_point[1].x) {
                gc_point[1].x += 0.1;   // 防止控制点一样时的绘制异常
            }
        } else {
            gc_point[0].x = rect_area.x1;
            gc_point[0].y = rect_area.y1 + ((rect_area.y2 - rect_area.y1 + 1) * (dsc->bg_grad.stops[0].frac) >> 8);
            gc_point[1].x = rect_area.x1;
            gc_point[1].y = rect_area.y1 + ((rect_area.y2 - rect_area.y1 + 1) * (dsc->bg_grad.stops[1].frac) >> 8);
            if (gc_point[0].x == gc_point[1].x) {
                gc_point[1].x += 0.1;   // 防止控制点一样时的绘制异常
            }
        }

        for (int i = 0; i < LV_GRADIENT_MAX_STOPS; i++) {
            rampstops[i].a = dsc->bg_opa;
            rampstops[i].r = dsc->bg_grad.stops[i].color.ch.red << 3;
            rampstops[i].g = dsc->bg_grad.stops[i].color.ch.green << 2;
            rampstops[i].b = dsc->bg_grad.stops[i].color.ch.blue << 3;
            jlvg_color_premultiply(&(rampstops[i]));    // 填充像素预乘
        }

        jlvg_paint_linear_init(&paint_linear, &(gc_point[0]), &(gc_point[1]));

        jlvg_paint_set_rampstops(&paint_linear,
                                 VGHW_COLOR_RAMP_SPREAD_PAD,
                                 0,                          // 渐变梯度: [0,1,2,3,4,5,6]->[2,3,5,9,17,33,64]
                                 rampstops);
    } else {
        //填充颜色准备
        //printf("no grad");
        fill_color.a = dsc->bg_opa;
        fill_color.r = dsc->bg_color.ch.red << 3;
        fill_color.g = dsc->bg_color.ch.green << 2;
        fill_color.b = dsc->bg_color.ch.blue << 3;
        jlvg_color_premultiply(&fill_color);    // 填充像素预乘
        jlvg_paint_color_init(&paint_color, fill_color); //初始化填充的颜色内容
    }
#else
    if (dsc->bg_grad.dir != (lv_grad_dir_t)LV_GRAD_DIR_NONE) { /* 有渐变属性 */
        if (dsc->bg_grad.dir == (lv_grad_dir_t)LV_GRAD_DIR_HOR) {
            gc_point[0].x = rect_area.x1 + ((rect_area.x2 - rect_area.x1 + 1) * (dsc->bg_grad.stops[0].frac) >> 8);
            gc_point[0].y = rect_area.y1;
            gc_point[1].x = rect_area.x1 + ((rect_area.x2 - rect_area.x1 + 1) * (dsc->bg_grad.stops[1].frac) >> 8);
            gc_point[1].y = rect_area.y1;
            if (gc_point[0].x == gc_point[1].x) {
                gc_point[1].x += 0.1;   // 防止控制点一样时的绘制异常
            }
        } else {
            gc_point[0].x = rect_area.x1;
            gc_point[0].y = rect_area.y1 + ((rect_area.y2 - rect_area.y1 + 1) * (dsc->bg_grad.stops[0].frac) >> 8);
            gc_point[1].x = rect_area.x1;
            gc_point[1].y = rect_area.y1 + ((rect_area.y2 - rect_area.y1 + 1) * (dsc->bg_grad.stops[1].frac) >> 8);
            if (gc_point[0].x == gc_point[1].x) {
                gc_point[1].x += 0.1;   // 防止控制点一样时的绘制异常
            }
        }

        for (int i = 0; i < LV_GRADIENT_MAX_STOPS; i++) {
            rampstops[i].a = dsc->bg_opa;
            rampstops[i].r = dsc->bg_grad.stops[i].color.ch.red;
            rampstops[i].g = dsc->bg_grad.stops[i].color.ch.green;
            rampstops[i].b = dsc->bg_grad.stops[i].color.ch.blue;
            jlvg_color_premultiply(&(rampstops[i]));    // 填充像素预乘
        }

        jlvg_paint_linear_init(&paint_linear, &(gc_point[0]), &(gc_point[1]));

        jlvg_paint_set_rampstops(&paint_linear,
                                 VGHW_COLOR_RAMP_SPREAD_PAD,
                                 1,                          // 渐变梯度1 对应 2 的 1 次方
                                 rampstops);
    } else {
        //填充颜色准备
        //printf("no grad");
        fill_color.a = dsc->bg_opa;
        fill_color.r = dsc->bg_color.ch.red;
        fill_color.g = dsc->bg_color.ch.green;
        fill_color.b = dsc->bg_color.ch.blue;
        jlvg_color_premultiply(&fill_color);    // 填充像素预乘
        jlvg_paint_color_init(&paint_color, fill_color); //初始化填充的颜色内容
    }
#endif

    // 配置 paint
    jlvg_paint_t *draw_paint;
    if (dsc->bg_grad.dir == (lv_grad_dir_t)LV_GRAD_DIR_NONE) {
        draw_paint = &paint_color;
    } else {
        draw_paint = &paint_linear; // 渐变色
    }

    // 4、硬件绘制
    jlvg_start_frame(g_gpu2p5d, &surface);

    jlvg_fill_path(g_gpu2p5d, &draw_area, &rect_path, draw_paint, &user2surface, &surface2paint, blend_mode, VGHW_NON_ZERO);

    jlvg_end_frame(g_gpu2p5d);

    //4、清理现场
    jlvg_path_deinit(&rect_path);
    //jlvg_paint_deinit((jlvg_paint_t *)&paint_color);
    //jlvg_paint_deinit((jlvg_paint_t *)&paint_linear);
    jlvg_surface_deinit(&surface);

    return LV_RES_OK;
}

static lv_res_t lv_jl_gpu2p5d_draw_bg_img(lv_draw_ctx_t *draw_ctx, const lv_draw_rect_dsc_t *dsc, const lv_area_t *coords)
{
    // TODO
    return LV_RES_INV;

    //printf("%s()", __func__);
    if (dsc->bg_img_src == NULL) {
        return LV_RES_INV;
    }
    if (dsc->bg_img_opa <= LV_OPA_MIN) {
        return LV_RES_INV;
    }

    lv_area_t clip_area;
    if (!_lv_area_intersect(&clip_area, coords, draw_ctx->clip_area)) {
        return LV_RES_INV;
    }
}

static lv_res_t lv_jl_gpu2p5d_draw_border(lv_draw_ctx_t *draw_ctx, const lv_draw_rect_dsc_t *dsc, const lv_area_t *coords)
{
    //printf("%s()", __func__);
    if (dsc->border_opa <= LV_OPA_MIN) {
        return LV_RES_INV;
    }
    if (dsc->border_width == 0) {
        return LV_RES_INV;
    }
    if (dsc->border_side == LV_BORDER_SIDE_NONE) {
        return LV_RES_INV;
    }
    if (dsc->border_post) {
        return LV_RES_INV;
    }

    int32_t coords_w = lv_area_get_width(coords);
    int32_t coords_h = lv_area_get_height(coords);
    int32_t rout = dsc->radius;
    int32_t short_side = LV_MIN(coords_w, coords_h);
    if (rout > short_side >> 1) {
        rout = short_side >> 1;
    }

    lv_coord_t rin = rout - dsc->border_width;
    if (rin < 0) {
        rin = 0;
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

    lv_area_t rel_coords;
    lv_area_copy(&rel_coords, coords);
    lv_area_move(&rel_coords, -draw_ctx->buf_area->x1, -draw_ctx->buf_area->y1);    // 重新确定在显存中的相对位置
    //printf("rel_coords (x1,y1) = (%d,%d); (x2,y2) = (%d,%d).", rel_coords.x1, rel_coords.y1, rel_coords.x2, rel_coords.y2);

    lv_area_t rel_clip_area;
    lv_area_copy(&rel_clip_area, draw_ctx->clip_area);
    lv_area_move(&rel_clip_area, -draw_ctx->buf_area->x1, -draw_ctx->buf_area->y1);    // 重新确定在显存中的相对位置

    lv_area_t blend_area;   //这个区域无论是帧buff还是行buff都是相对的新的绘制区域
    if (!_lv_area_intersect(&blend_area, &rel_coords, &rel_clip_area)) {
        return LV_RES_OK;   // 意味着软件也不需要渲染动作
    }
    //printf("blend_area (x1,y1) = (%d,%d); (x2,y2) = (%d,%d).", blend_area.x1, blend_area.y1, blend_area.x2, blend_area.y2);

    // 判断不支持 VG 绘制的属性并退出
    bool mask_any = lv_draw_mask_is_any(&rel_coords);
    uint8_t blend_mode = lv_jl_gpu2p5d_get_blend_mode(dsc->blend_mode, NULL);   //根据图像的混合模式获取 VG 配置的混合模式
    if (mask_any == true) {
        return LV_RES_INV;  // 意味着该动作硬件无法绘制，重新交由软件绘制
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

    jlvg_matrix_t user2surface; // 变换矩阵 user to surface

    jlvg_surface_t surface;     // 绘制的窗口
    jlvg_rect_t draw_area;      // 在窗口内实际要绘制的区域:实际就是 blend_area

    //初始化单位变换矩阵
    jlvg_matrix_set_identity(&user2surface);

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

    // 2、配置绘制路径
    jlvg_path_t border_path;    // 绘制的矩形边框路径, 最终的绘制区域是 blend_area
    lv_area_t border_area;      // 绘制矩形边框的区域
    lv_area_copy(&border_area, &rel_coords);
#if (JLVG_DRAW_FULL_FB_ENABLE == 1)
    // nothing
#else
    lv_area_move(&border_area, -blend_area.x1, -blend_area.y1); // 由于开窗限制在了绘制区域，因此绘制坐标需要平移到原点
#endif
    lv_draw_jl_gpu2p5d_border_path_fill(dsc, border_area, rout, rin, &border_path);

    //3、配置颜色填充
    //正常填充颜色
    jlvg_paint_color_t paint_color;     // 正常渲染的颜色
    jlvg_color_t fill_color;

#if LV_COLOR_DEPTH == 16
    fill_color.a = dsc->border_opa;
    fill_color.r = dsc->border_color.ch.red << 3;
    fill_color.g = dsc->border_color.ch.green << 2;
    fill_color.b = dsc->border_color.ch.blue << 3;
    jlvg_color_premultiply(&fill_color);    // 填充像素预乘
    jlvg_paint_color_init(&paint_color, fill_color); //初始化填充的颜色内容
#else
    fill_color.a = dsc->border_opa;
    fill_color.r = dsc->border_color.ch.red;
    fill_color.g = dsc->border_color.ch.green;
    fill_color.b = dsc->border_color.ch.blue;
    jlvg_color_premultiply(&fill_color);    // 填充像素预乘
    jlvg_paint_color_init(&paint_color, fill_color); //初始化填充的颜色内容
#endif
    // 配置 paint
    jlvg_paint_t *draw_paint;
    draw_paint = &paint_color;

    // 4、硬件绘制
    jlvg_start_frame(g_gpu2p5d, &surface);

    jlvg_fill_path(g_gpu2p5d, &draw_area, &border_path, draw_paint, &user2surface, NULL, blend_mode, VGHW_NON_ZERO);

    jlvg_end_frame(g_gpu2p5d);

    //4、清理现场
    jlvg_path_deinit(&border_path);
    //jlvg_paint_deinit((jlvg_paint_t *)&paint_color);
    jlvg_surface_deinit(&surface);

    return LV_RES_OK;
}

#if LV_DRAW_COMPLEX
static lv_res_t LV_ATTRIBUTE_FAST_MEM lv_jl_gpu2p5d_draw_shadow(lv_draw_ctx_t *draw_ctx, const lv_draw_rect_dsc_t *dsc,
        const lv_area_t *coords)
{
    return LV_RES_INV;
#if 0
    //FIXME : 径向渐变实现的效果无法和软件实现的阴影效果重叠

    //printf("%s()", __func__);
    /*Check whether the shadow is visible*/
    if (dsc->shadow_width == 0) {
        return LV_RES_INV;
    }
    if (dsc->shadow_opa <= LV_OPA_MIN) {
        return LV_RES_INV;
    }

    if (dsc->shadow_width == 1 && dsc->shadow_spread <= 0 &&
        dsc->shadow_ofs_x == 0 && dsc->shadow_ofs_y == 0) {
        return LV_RES_INV;
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

    lv_area_t rel_coords;
    lv_area_copy(&rel_coords, coords);
    lv_area_move(&rel_coords, -draw_ctx->buf_area->x1, -draw_ctx->buf_area->y1);        // 重新确定在显存中的相对位置
    //printf("rel_coords (x1,y1) = (%d,%d); (x2,y2) = (%d,%d).", rel_coords.x1, rel_coords.y1, rel_coords.x2, rel_coords.y2);

    // 计算内径外径以及绘制区域
    float sh_w_half = (float)dsc->shadow_width / 2.0f;

    // 阴影进行扩散前的区域
    lv_area_t original_area;
    original_area.x1 = rel_coords.x1  + dsc->shadow_ofs_x - dsc->shadow_spread;
    original_area.x2 = rel_coords.x2  + dsc->shadow_ofs_x + dsc->shadow_spread;
    original_area.y1 = rel_coords.y1  + dsc->shadow_ofs_y - dsc->shadow_spread;
    original_area.y2 = rel_coords.y2  + dsc->shadow_ofs_y + dsc->shadow_spread;
    //printf("original_area (x1,y1) = (%d,%d); (x2,y2) = (%d,%d).", original_area.x1, original_area.y1, original_area.x2, original_area.y2);

    // 整个阴影的区域: 用于计算开窗大小
    lv_area_t shadow_area;
    shadow_area.x1 = original_area.x1 - dsc->shadow_width / 2 - 1;
    shadow_area.x2 = original_area.x2 + dsc->shadow_width / 2 + 1;
    shadow_area.y1 = original_area.y1 - dsc->shadow_width / 2 - 1;
    shadow_area.y2 = original_area.y2 + dsc->shadow_width / 2 + 1;

    lv_area_t rel_clip_area;
    lv_area_copy(&rel_clip_area, draw_ctx->clip_area);
    lv_area_move(&rel_clip_area, -draw_ctx->buf_area->x1, -draw_ctx->buf_area->y1);    // 重新确定在显存中的相对位置

    lv_area_t blend_area;   //这个区域无论是帧buff还是行buff都是相对的新的绘制区域
    if (!_lv_area_intersect(&blend_area, &shadow_area, &rel_clip_area)) {
        return LV_RES_OK;   // 意味着软件也不需要渲染动作
    }
    //printf("blend_area (x1,y1) = (%d,%d); (x2,y2) = (%d,%d).", blend_area.x1, blend_area.y1, blend_area.x2, blend_area.y2);

    // 判断不支持 VG 绘制的属性并退出
    bool mask_any = lv_draw_mask_is_any(&shadow_area);
    uint8_t blend_mode = lv_jl_gpu2p5d_get_blend_mode(dsc->blend_mode, NULL);   //根据图像的混合模式获取 VG 配置的混合模式
    if (mask_any == true) {
        return LV_RES_INV;  // 意味着该动作硬件无法绘制，重新交由软件绘制
    }

    // 计算内外径以及背景区域
    float r_in;   // 渐变内径, 不会进行渐变区域的半径
    jlvg_point2_t bg_area_point0;
    jlvg_point2_t bg_area_point1;
    lv_coord_t short_side = LV_MIN(lv_area_get_width(&original_area), lv_area_get_height(&original_area));
    if ((dsc->shadow_width) > (short_side)) {
        r_in = 0.0f;
        bg_area_point0.x = (float)original_area.x1 + (float)(short_side / 2.0f);
        bg_area_point0.y = (float)original_area.y1 + (float)(short_side / 2.0f);
        bg_area_point1.x = (float)original_area.x2 + 1 - (float)(short_side / 2.0f);
        bg_area_point1.y = (float)original_area.y2 + 1 - (float)(short_side / 2.0f);
    } else {
        if ((float)dsc->radius > ((float)(dsc->shadow_width) / 2.0f)) {
            r_in = (float)dsc->radius - (float)(dsc->shadow_width) / 2.0f;
        } else {
            r_in = 0.0f;
        }

        bg_area_point0.x = (float)original_area.x1 + (float)(dsc->shadow_width / 2.0f);
        bg_area_point0.y = (float)original_area.y1 + (float)(dsc->shadow_width / 2.0f);
        bg_area_point1.x = (float)original_area.x2 + 1 - (float)(dsc->shadow_width / 2.0f);
        bg_area_point1.y = (float)original_area.y2 + 1 - (float)(dsc->shadow_width / 2.0f);
    }

    float r_out;  // 渐变外径
    r_out = bg_area_point0.x - (float)original_area.x1 + (float)(dsc->shadow_width) / 2.0f + r_in;
    //printf("r_in = %f; r_out = %f.", r_in, r_out);

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

    jlvg_matrix_t user2surface; // 变换矩阵 user to surface
    jlvg_matrix_t surface2paint;// 变换矩阵 surface to paint

    jlvg_surface_t surface;     // 绘制的窗口
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
    //printf("draw_area (x,y) = (%d,%d); w = %d, y = %d.", draw_area.x, draw_area.y, draw_area.w, draw_area.h);

    //窗口初始化
    jlvg_surface_init(&surface, dest_buf, fb_size, fb_width, fb_height, dest_stride, jlvg_dest_cf, 0, 1, 1, 0);

    // 2.1、绘制阴影非渐变的背景区域
    // 配置绘制路径
    jlvg_path_t shadow_bg_path;    // 绘制阴影中没有扩散效果的区域
    jlvg_point2_t shadow_bg_point0 = bg_area_point0;
    jlvg_point2_t shadow_bg_point1 = bg_area_point1;
#if (JLVG_DRAW_FULL_FB_ENABLE == 1)
    // nothing
#else
    shadow_bg_point0.x -= (float)blend_area.x1;
    shadow_bg_point0.y -= (float)blend_area.y1;
    shadow_bg_point1.x -= (float)blend_area.x1;
    shadow_bg_point1.y -= (float)blend_area.y1;
    //lv_area_move(&shadow_bg_area, -blend_area.x1, -blend_area.y1); // 由于开窗限制在了绘制区域，因此绘制坐标需要平移到原点
#endif
    lv_draw_jl_gpu2p5d_shadow_bg_path_fill(shadow_bg_point0, shadow_bg_point1, r_in, &shadow_bg_path);

    //正常填充颜色
    jlvg_paint_color_t paint_color;     // 正常渲染的颜色
    jlvg_color_t fill_color;

#if LV_COLOR_DEPTH == 16
    fill_color.a = dsc->shadow_opa;
    fill_color.r = dsc->shadow_color.ch.red << 3;
    fill_color.g = dsc->shadow_color.ch.green << 2;
    fill_color.b = dsc->shadow_color.ch.blue << 3;
    jlvg_color_premultiply(&fill_color);    // 填充像素预乘
    jlvg_paint_color_init(&paint_color, fill_color); //初始化填充的颜色内容
#else
    fill_color.a = dsc->shadow_opa;
    fill_color.r = dsc->shadow_color.ch.red;
    fill_color.g = dsc->shadow_color.ch.green;
    fill_color.b = dsc->shadow_color.ch.blue;
    jlvg_color_premultiply(&fill_color);    // 填充像素预乘
    jlvg_paint_color_init(&paint_color, fill_color); //初始化填充的颜色内容
#endif
    // 配置 paint
    jlvg_paint_t *draw_paint;
    draw_paint = &paint_color;

    jlvg_start_frame(g_gpu2p5d, &surface);

    jlvg_fill_path(g_gpu2p5d, &draw_area, &shadow_bg_path, draw_paint, &user2surface, NULL, blend_mode, VGHW_NON_ZERO);

    // 2.2、绘制阴影的渐变区域
    jlvg_color_t rampstops[2];  // 渐变颜色阶梯 : 四个角和四条边的颜色渐变阶梯都是一样的
#if LV_COLOR_DEPTH == 16
    rampstops[0].a = dsc->shadow_opa;
    rampstops[0].r = dsc->shadow_color.ch.red << 3;
    rampstops[0].g = dsc->shadow_color.ch.green << 2;
    rampstops[0].b = dsc->shadow_color.ch.blue << 3;
    jlvg_color_premultiply(&(rampstops[0]));    // 填充像素预乘
#else
    rampstops[i].a = dsc->shadow_opa;
    rampstops[i].r = dsc->shadow_color.ch.red;
    rampstops[i].g = dsc->shadow_color.ch.green;
    rampstops[i].b = dsc->shadow_color.ch.blue;
    jlvg_color_premultiply(&(rampstops[0]));    // 填充像素预乘
#endif

    rampstops[1].a = 0x00;
    rampstops[1].r = 0x00;
    rampstops[1].g = 0x00;
    rampstops[1].b = 0x00;

    // 四条线性渐变的边
    // 线性渐变属性填充颜色
    jlvg_paint_linear_t paint_linear[4];    // 线性渐变渲染的颜色
    jlvg_point2_t gc_point[4][2];       // 线性渐变控制点
    jlvg_path_t shadow_edge_path[4];    // 绘制阴影中有扩散效果的边的路径
    float linear_points[4][6];
    uint32_t linear_nsegments = 5;//5
    uint8_t linear_segments[5] = { VGHW_MOVE_TO, VGHW_HLINE_TO, VGHW_VLINE_TO, VGHW_HLINE_TO, VGHW_VLINE_TO };
    uint32_t linear_npoints = 6;

    // 上边
    linear_points[0][0] = linear_points[0][4] = shadow_bg_point0.x + (r_in);    // 原点(起点和终点)的 x
    linear_points[0][1] = linear_points[0][5] = shadow_bg_point0.y - (r_out - r_in);    // 原点(起点和终点)的 y
    linear_points[0][2] = shadow_bg_point1.x - (r_in);  // 矩形原点对角的 x
    linear_points[0][3] = shadow_bg_point0.y;  // 矩形原点对角的 y

    gc_point[0][0].x = linear_points[0][2];
    gc_point[0][0].y = linear_points[0][3];
    gc_point[0][1].x = linear_points[0][2];
    gc_point[0][1].y = linear_points[0][1];
    if (gc_point[0][0].y == gc_point[0][1].y) {
        gc_point[0][1].y += 0.1;   // 防止控制点一样时的绘制异常
    }

    // 下边
    linear_points[1][0] = linear_points[1][4] = shadow_bg_point0.x + (r_in);    // 原点(起点和终点)的 x
    linear_points[1][1] = linear_points[1][5] = shadow_bg_point1.y;    // 原点(起点和终点)的 y
    linear_points[1][2] = shadow_bg_point1.x - (r_in);  // 矩形原点对角的 x
    linear_points[1][3] = shadow_bg_point1.y + (r_out - r_in);  // 矩形原点对角的 y

    gc_point[1][0].x = linear_points[1][0];
    gc_point[1][0].y = linear_points[1][1];
    gc_point[1][1].x = linear_points[1][0];
    gc_point[1][1].y = linear_points[1][3];
    if (gc_point[1][0].y == gc_point[1][1].y) {
        gc_point[1][1].y += 0.1;   // 防止控制点一样时的绘制异常
    }

    // 左边
    linear_points[2][0] = linear_points[2][4] = shadow_bg_point0.x - (r_out - r_in);    // 原点(起点和终点)的 x
    linear_points[2][1] = linear_points[2][5] = shadow_bg_point0.y + (r_in);    // 原点(起点和终点)的 y
    linear_points[2][2] = shadow_bg_point0.x;  // 矩形原点对角的 x
    linear_points[2][3] = shadow_bg_point1.y - (r_in);  // 矩形原点对角的 y

    gc_point[2][0].x = linear_points[2][2];
    gc_point[2][0].y = linear_points[2][3];
    gc_point[2][1].x = linear_points[2][0];
    gc_point[2][1].y = linear_points[2][3];
    if (gc_point[2][0].x == gc_point[2][1].x) {
        gc_point[2][1].x += 0.1;   // 防止控制点一样时的绘制异常
    }

    // 右边
    linear_points[3][0] = linear_points[3][4] = shadow_bg_point1.x;    // 原点(起点和终点)的 x
    linear_points[3][1] = linear_points[3][5] = shadow_bg_point0.y + (r_in);    // 原点(起点和终点)的 y
    linear_points[3][2] = shadow_bg_point1.x + (r_out - r_in);  // 矩形原点对角的 x
    linear_points[3][3] = shadow_bg_point1.y - (r_in);  // 矩形原点对角的 y

    gc_point[3][0].x = linear_points[3][0];
    gc_point[3][0].y = linear_points[3][1];
    gc_point[3][1].x = linear_points[3][2];
    gc_point[3][1].y = linear_points[3][1];
    if (gc_point[3][0].x == gc_point[3][1].x) {
        gc_point[3][1].x += 0.1;   // 防止控制点一样时的绘制异常
    }

    for (int i = 0; i < 4; i++) {
        jlvg_path_init(&(shadow_edge_path[i]), JLVG_PATH_DATATYPE_F32, linear_nsegments, linear_segments, linear_npoints, linear_points[i]);
        jlvg_path_update_fill(&(shadow_edge_path[i]));  //更新路径信息

        jlvg_paint_linear_init(&(paint_linear[i]), &(gc_point[i][0]), &(gc_point[i][1]));

        jlvg_paint_set_rampstops(&(paint_linear[i]),
                                 VGHW_COLOR_RAMP_SPREAD_PAD,
                                 0,                          // 渐变梯度: [0,1,2,3,4,5,6]->[2,3,5,9,17,33,64]
                                 rampstops);

        draw_paint = &(paint_linear[i]);
        jlvg_fill_path(g_gpu2p5d, &draw_area, &(shadow_edge_path[i]), draw_paint, &user2surface, &surface2paint, blend_mode, VGHW_NON_ZERO);
    }

    // 四个圆形渐变的角
    // 圆形渐变属性填充颜色
    jlvg_paint_linear_t paint_corners[4];   // 圆形渐变渲染的颜色
    jlvg_point2_t corners_center[4];;       // 圆形渐变的中心点
    jlvg_path_t shadow_corners_path[4];     // 绘制阴影中有扩散效果的角的路径
    uint8_t corners_segments[4][1 + 1 + 3 + 1];    // 6
    float corners_points[4][2 + 2 + 2 * 6 + 2]; // 18

    jlvg_point2_t p[4][3];  // 四个角的圆弧和圆心

    // 左上角圆弧
    p[0][0].x =  shadow_bg_point0.x + r_in;
    p[0][0].y =  shadow_bg_point0.y + r_in;
    p[0][1].x = p[0][0].x;
    p[0][1].y = p[0][0].y - r_out;
    p[0][2].x = p[0][0].x - r_out;
    p[0][2].y = p[0][0].y;

    // 左下角圆弧
    p[1][0].x = shadow_bg_point0.x + r_in;
    p[1][0].y = shadow_bg_point1.y - r_in;
    p[1][1].x = p[1][0].x - r_out;
    p[1][1].y = p[1][0].y;
    p[1][2].x = p[1][0].x;
    p[1][2].y = p[1][0].y + r_out;

    // 右下角圆弧
    p[2][0].x = shadow_bg_point1.x - r_in;
    p[2][0].y = shadow_bg_point1.y - r_in;
    p[2][1].x = p[2][0].x;
    p[2][1].y = p[2][0].y + r_out;
    p[2][2].x = p[2][0].x + r_out;
    p[2][2].y = p[2][0].y;

    // 右上角圆弧
    p[3][0].x = shadow_bg_point1.x - r_in;
    p[3][0].y = shadow_bg_point0.y + r_in;
    p[3][1].x = p[3][0].x + r_out;
    p[3][1].y = p[3][0].y;
    p[3][2].x = p[3][0].x;
    p[3][2].y = p[3][0].y - r_out;

    for (int i = 0; i < 4; i++) {
        int nseg_tmp = 0;
        int npoints_tmp = 0;
        uint32_t corners_nsegments = 0;
        uint32_t corners_npoints = 0;

        //moveto
        corners_segments[i][corners_nsegments++] = VGHW_MOVE_TO;   //起点 and 终点
        corners_points[i][corners_npoints++] = p[i][0].x;
        corners_points[i][corners_npoints++] = p[i][0].y;

        //1st line to
        corners_segments[i][corners_nsegments++] = VGHW_LINE_TO;
        corners_points[i][corners_npoints++] = p[i][1].x;
        corners_points[i][corners_npoints++] = p[i][1].y;

        //1st arc
        jlvg_path_circle2beizer(&corners_segments[i][corners_nsegments], &nseg_tmp, &corners_points[i][corners_npoints], &npoints_tmp,
                                p[i][0].x, p[i][0].y, r_out, p[i][1].x, p[i][1].y, p[i][2].x, p[i][2].y, 1, 0);
        corners_nsegments += nseg_tmp;
        corners_npoints += npoints_tmp;

        //2nd line to
        corners_segments[i][corners_nsegments++] = VGHW_LINE_TO;
        corners_points[i][corners_npoints++] = p[i][0].x;
        corners_points[i][corners_npoints++] = p[i][0].y;

        corners_center[i].x = corners_points[i][0];
        corners_center[i].y = corners_points[i][1];

        //printf("corners_nsegments = %d; corners_npoints = %d.", corners_nsegments, corners_npoints);
        jlvg_path_init(&(shadow_corners_path[i]), JLVG_PATH_DATATYPE_F32, corners_nsegments, corners_segments[i], corners_npoints, corners_points[i]);
        jlvg_path_update_fill(&(shadow_corners_path[i]));  //更新路径信息

        jlvg_paint_radial_init(&(paint_corners[i]), &(corners_center[i]), r_out, r_in);

        jlvg_paint_set_rampstops(&(paint_corners[i]),
                                 VGHW_COLOR_RAMP_SPREAD_PAD,
                                 0,                          // 渐变梯度: [0,1,2,3,4,5,6]->[2,3,5,9,17,33,64]
                                 rampstops);

        draw_paint = &(paint_corners[i]);
        jlvg_fill_path(g_gpu2p5d, &draw_area, &(shadow_corners_path[i]), draw_paint, &user2surface, &surface2paint, blend_mode, VGHW_NON_ZERO);
    }

    // 3、启动硬件绘制
    jlvg_end_frame(g_gpu2p5d);

    //4、清理现场
    jlvg_path_deinit(&shadow_bg_path);
    //jlvg_paint_deinit((jlvg_paint_t *)&paint_color);
    for (int i = 0; i < 4; i++) {
        jlvg_path_deinit(&(shadow_edge_path[i]));
        jlvg_path_deinit(&(shadow_corners_path[i]));
        //jlvg_paint_deinit((jlvg_paint_t *)&(paint_linear[i]));
        //jlvg_paint_deinit((jlvg_paint_t *)&(paint_corners[i]));
    }
    jlvg_surface_deinit(&surface);

    return LV_RES_OK;
#endif
}
#endif

static lv_res_t lv_jl_gpu2p5d_draw_outline(lv_draw_ctx_t *draw_ctx, const lv_draw_rect_dsc_t *dsc, const lv_area_t *coords)
{
    //printf("%s()", __func__);
    if (dsc->outline_opa <= LV_OPA_MIN) {
        return LV_RES_INV;
    }
    if (dsc->outline_width == 0) {
        return LV_RES_INV;
    }

    /*Get the inner radius*/
    lv_area_t area_inner;
    lv_area_copy(&area_inner, coords);

    /*Bring the outline closer to make sure there is no color bleeding with pad=0*/
    lv_coord_t outline_pad = dsc->outline_pad - 1;
    area_inner.x1 -= outline_pad;
    area_inner.y1 -= outline_pad;
    area_inner.x2 += outline_pad;
    area_inner.y2 += outline_pad;

    int32_t inner_w = lv_area_get_width(&area_inner);
    int32_t inner_h = lv_area_get_height(&area_inner);
    int32_t rin = dsc->radius;
    int32_t short_side = LV_MIN(inner_w, inner_h);
    if (rin > short_side >> 1) {
        rin = short_side >> 1;
    }

    int32_t rout = rin + dsc->outline_width;

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

    /* Move outline outwards to align with software rendered outline */
    lv_area_t rel_coords;
    rel_coords.x1 = coords->x1 - outline_pad - dsc->outline_width;
    rel_coords.x2 = coords->x2 + outline_pad + dsc->outline_width;
    rel_coords.y1 = coords->y1 - outline_pad - dsc->outline_width;
    rel_coords.y2 = coords->y2 + outline_pad + dsc->outline_width;

    lv_area_move(&rel_coords, -draw_ctx->buf_area->x1, -draw_ctx->buf_area->y1);        // 重新确定在显存中的相对位置
    //printf("rel_coords (x1,y1) = (%d,%d); (x2,y2) = (%d,%d).", rel_coords.x1, rel_coords.y1, rel_coords.x2, rel_coords.y2);

    lv_area_t rel_clip_area;
    lv_area_copy(&rel_clip_area, draw_ctx->clip_area);
    lv_area_move(&rel_clip_area, -draw_ctx->buf_area->x1, -draw_ctx->buf_area->y1);    // 重新确定在显存中的相对位置

    lv_area_t blend_area;   //这个区域无论是帧buff还是行buff都是相对的新的绘制区域
    if (!_lv_area_intersect(&blend_area, &rel_coords, &rel_clip_area)) {
        return LV_RES_OK;   // 意味着软件也不需要渲染动作
    }
    //printf("blend_area (x1,y1) = (%d,%d); (x2,y2) = (%d,%d).", blend_area.x1, blend_area.y1, blend_area.x2, blend_area.y2);

    // 判断不支持 VG 绘制的属性并退出
    bool mask_any = lv_draw_mask_is_any(&rel_coords);
    uint8_t blend_mode = lv_jl_gpu2p5d_get_blend_mode(dsc->blend_mode, NULL);   //根据图像的混合模式获取 VG 配置的混合模式
    if (mask_any == true) {
        return LV_RES_INV;  // 意味着该动作硬件无法绘制，重新交由软件绘制
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

    jlvg_matrix_t user2surface; // 变换矩阵 user to surface

    jlvg_surface_t surface;     // 绘制的窗口
    jlvg_rect_t draw_area;      // 在窗口内实际要绘制的区域:实际就是 blend_area

    //初始化单位变换矩阵
    jlvg_matrix_set_identity(&user2surface);

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

    // 2、配置绘制路径
    jlvg_path_t outline_path;    // 绘制的矩形轮廓路径, 最终的绘制区域是 blend_area
    lv_area_t outline_area;     // 绘制矩形轮廓的区域
    lv_area_copy(&outline_area, &rel_coords);
#if (JLVG_DRAW_FULL_FB_ENABLE == 1)
    // nothing
#else
    lv_area_move(&outline_area, -blend_area.x1, -blend_area.y1); // 由于开窗限制在了绘制区域，因此绘制坐标需要平移到原点
#endif
    lv_draw_jl_gpu2p5d_outline_path_fill(dsc, outline_area, rout, rin, &outline_path);

    //3、配置颜色填充
    //正常填充颜色
    jlvg_paint_color_t paint_color;     // 正常渲染的颜色
    jlvg_color_t fill_color;

#if LV_COLOR_DEPTH == 16
    fill_color.a = dsc->outline_opa;
    fill_color.r = dsc->outline_color.ch.red << 3;
    fill_color.g = dsc->outline_color.ch.green << 2;
    fill_color.b = dsc->outline_color.ch.blue << 3;
    jlvg_color_premultiply(&fill_color);    // 填充像素预乘
    jlvg_paint_color_init(&paint_color, fill_color); //初始化填充的颜色内容
#else
    fill_color.a = dsc->outline_opa;
    fill_color.r = dsc->outline_color.ch.red;
    fill_color.g = dsc->outline_color.ch.green;
    fill_color.b = dsc->outline_color.ch.blue;
    jlvg_color_premultiply(&fill_color);    // 填充像素预乘
    jlvg_paint_color_init(&paint_color, fill_color); //初始化填充的颜色内容
#endif
    // 配置 paint
    jlvg_paint_t *draw_paint;
    draw_paint = &paint_color;

    // 4、硬件绘制
    jlvg_start_frame(g_gpu2p5d, &surface);

    jlvg_fill_path(g_gpu2p5d, &draw_area, &outline_path, draw_paint, &user2surface, NULL, blend_mode, VGHW_NON_ZERO);

    jlvg_end_frame(g_gpu2p5d);

    //4、清理现场
    jlvg_path_deinit(&outline_path);
    //jlvg_paint_deinit((jlvg_paint_t *)&paint_color);
    jlvg_surface_deinit(&surface);

    return LV_RES_OK;

}
#endif  // LV_USE_JL_GPU2P5D_DRAW_RECT
#endif  // LV_USE_GPU_JL_GPU2P5D
