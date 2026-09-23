/**
 * @file lv_gpu_jl_gpu2p5d_img.c
 *
 */

/*********************
 *      INCLUDES
 *********************/
#include "lv_gpu_jl_gpu2p5d.h"
#include "../../../extra/jl_extra/libs/rle/lv_rle.h"
#if LV_USE_GPU_JL_GPU2P5D
#if LV_USE_JL_GPU2P5D_DRAW_IMG
/*********************
*      DEFINES
*********************/
#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif
#define MAX_BUF_SIZE (uint32_t) lv_disp_get_hor_res(_lv_refr_get_disp_refreshing())

/**********************
*      TYPEDEFS
**********************/
typedef struct {
    void *src_buf;
    int16_t angle;
    uint16_t zoom;
    lv_area_t transform_area;
    lv_area_t clip_area;
    volatile uint8_t transform_start;
} img_transform_t;

/**********************
*  STATIC PROTOTYPES
**********************/
static img_transform_t __img_trans = { 0 };

/**********************
*  STATIC VARIABLES
**********************/

/**********************
*      MACROS
**********************/
#define GPU2P5d_DEBUG_EN   0

#if GPU2P5d_DEBUG_EN
#define jlgpu_printf(...) printf(__VA_ARGS__)
#else
#define jlgpu_printf(...)
#endif

/**********************
*   GLOBAL FUNCTIONS
**********************/

static void sw_convert_cb(const lv_area_t *dest_area, const void *src_buf, lv_coord_t src_w, lv_coord_t src_h,
                          lv_coord_t src_stride, const lv_draw_img_dsc_t *draw_dsc, lv_img_cf_t cf, lv_color_t *cbuf, lv_opa_t *abuf)
{
    LV_UNUSED(draw_dsc);
    LV_UNUSED(src_h);
    LV_UNUSED(src_w);

    const uint8_t *src_tmp8 = (const uint8_t *)src_buf;
    lv_coord_t y;
    lv_coord_t x;

    if (cf == LV_IMG_CF_TRUE_COLOR || cf == LV_IMG_CF_TRUE_COLOR_CHROMA_KEYED) {
        uint32_t px_cnt = lv_area_get_size(dest_area);
        lv_memset_ff(abuf, px_cnt);

        src_tmp8 += (src_stride * dest_area->y1 * sizeof(lv_color_t)) + dest_area->x1 * sizeof(lv_color_t);
        uint32_t dest_w = lv_area_get_width(dest_area);
        uint32_t dest_w_byte = dest_w * sizeof(lv_color_t);

        lv_coord_t src_stride_byte = src_stride * sizeof(lv_color_t);
        lv_color_t *cbuf_tmp = cbuf;
        for (y = dest_area->y1; y <= dest_area->y2; y++) {
            lv_memcpy(cbuf_tmp, src_tmp8, dest_w_byte);
            src_tmp8 += src_stride_byte;
            cbuf_tmp += dest_w;
        }

        /*Make "holes" for with Chroma keying*/
        if (cf == LV_IMG_CF_TRUE_COLOR_CHROMA_KEYED) {
            uint32_t i;
            lv_color_t chk = LV_COLOR_CHROMA_KEY;
#if LV_COLOR_DEPTH == 8 || LV_COLOR_DEPTH == 1
            uint8_t *cbuf_uint = (uint8_t *)cbuf;
            uint8_t chk_v = chk.full;
#elif LV_COLOR_DEPTH == 16
            uint16_t *cbuf_uint = (uint16_t *)cbuf;
            uint16_t chk_v = chk.full;
#elif LV_COLOR_DEPTH == 32
            uint32_t *cbuf_uint = (uint32_t *)cbuf;
            uint32_t chk_v = chk.full;
#endif
            for (i = 0; i < px_cnt; i++) {
                if (chk_v == cbuf_uint[i]) {
                    abuf[i] = 0x00;
                }
            }
        }
    } else if (cf == LV_IMG_CF_TRUE_COLOR_ALPHA) {
        src_tmp8 += (src_stride * dest_area->y1 * LV_IMG_PX_SIZE_ALPHA_BYTE) + dest_area->x1 * LV_IMG_PX_SIZE_ALPHA_BYTE;

        lv_coord_t src_new_line_step_px = (src_stride - lv_area_get_width(dest_area));
        lv_coord_t src_new_line_step_byte = src_new_line_step_px * LV_IMG_PX_SIZE_ALPHA_BYTE;

        lv_coord_t dest_h = lv_area_get_height(dest_area);
        lv_coord_t dest_w = lv_area_get_width(dest_area);
        for (y = 0; y < dest_h; y++) {
            for (x = 0; x < dest_w; x++) {
                abuf[x] = src_tmp8[LV_IMG_PX_SIZE_ALPHA_BYTE - 1];
#if LV_COLOR_DEPTH == 8 || LV_COLOR_DEPTH == 1
                cbuf[x].full = *src_tmp8;
#elif LV_COLOR_DEPTH == 16
                cbuf[x].full = *src_tmp8 + ((*(src_tmp8 + 1)) << 8);
#elif LV_COLOR_DEPTH == 32
                cbuf[x] = *((lv_color_t *) src_tmp8);
                cbuf[x].ch.alpha = 0xff;
#endif
                src_tmp8 += LV_IMG_PX_SIZE_ALPHA_BYTE;

            }
            cbuf += dest_w;
            abuf += dest_w;
            src_tmp8 += src_new_line_step_byte;
        }
    } else if (cf == LV_IMG_CF_RGB565A8) {
        src_tmp8 += (src_stride * dest_area->y1 * sizeof(lv_color_t)) + dest_area->x1 * sizeof(lv_color_t);

        lv_coord_t src_stride_byte = src_stride * sizeof(lv_color_t);

        lv_coord_t dest_h = lv_area_get_height(dest_area);
        lv_coord_t dest_w = lv_area_get_width(dest_area);
        for (y = 0; y < dest_h; y++) {
            lv_memcpy(cbuf, src_tmp8, dest_w * sizeof(lv_color_t));
            cbuf += dest_w;
            src_tmp8 += src_stride_byte;
        }

        src_tmp8 = (const uint8_t *)src_buf;
        src_tmp8 += sizeof(lv_color_t) * src_w * src_h;
        src_tmp8 += src_stride * dest_area->y1 + dest_area->x1;
        for (y = 0; y < dest_h; y++) {
            lv_memcpy(abuf, src_tmp8, dest_w);
            abuf += dest_w;
            src_tmp8 += src_stride;
        }
    }
}
static lv_res_t _lv_jlgpu_texture_copy(lv_draw_ctx_t *draw_ctx, const lv_area_t *dest_area, const uint8_t *src, lv_coord_t src_width, lv_coord_t src_height, lv_coord_t src_stride,
                                       int in_format, int out_format, uint8_t *obuf, lv_color_t *cbuf, lv_opa_t *abuf, uint8_t colorkey_en)
{
    jlvg_surface_t surface;
    jlvg_rect_t area = {0};
    jlvg_matrix_t surface2image;
    rle_info_t *rle_info;
    uint8_t rle_en = 0;
    uint8_t adr_mode = 1;
    uint8_t *src_clut = NULL;

    bool done = false;


    uint32_t dest_width = lv_area_get_width(dest_area);
    uint32_t dest_height = lv_area_get_height(dest_area);
    uint32_t dest_stride = dest_width * sizeof(lv_color_t);

    uint32_t surface_size = dest_width * dest_height * sizeof(lv_color_t);   // 绘制区域的buff大小

    uint32_t src_size = src_width * src_height * jlvg_get_image_format_bpp(in_format) >> 3;
    uint32_t img_stride = src_stride * jlvg_get_image_format_bpp(in_format) >> 3;
    uint8_t *out_buf = cbuf;

    /* area.x = 0; */
    /* area.y = 0; */
    area.w = dest_width;
    area.h = dest_height;
    bool has_indexed = (in_format >= VGHW_FORMAT_L8 && in_format <= VGHW_FORMAT_L1) ? true : false;
    uint16_t clut_format = VGHW_CLUT_FORMAT_ARGB8888;
    if (draw_ctx->compress_type != LV_COMPRESS_RLE) {
        if (in_format == out_format) {
            out_buf = (uint8_t *)src;
            done = false;
            goto __output;
        }
    } else {
        rle_info = (rle_info_t *)src;
        rle_en = 1;
        img_stride = lv_rle_get_stride(rle_info, &adr_mode);
        src_size = rle_info->len;
        area.w = src_width;
        area.h = src_height;
        clut_format = rle_info->lut_format;
        if (has_indexed) {
            src_clut = (uint8_t *)src + rle_info->lut_addr;
        }
        src = (uint8_t *)src + rle_info->addr;
    }
    if (obuf) {
        //用于输出ARGB8565 的临时buf
        out_buf = obuf;
        src_stride = dest_width;
        dest_stride = dest_width * LV_IMG_PX_SIZE_ALPHA_BYTE;
        surface_size = dest_width * dest_height * LV_IMG_PX_SIZE_ALPHA_BYTE;
    }
    lv_jl_gpu2p5d_flush_inv_dcache(out_buf, dest_width, dest_height, dest_width, jlvg_get_image_format_bpp(out_format));
    jlvg_surface_init(&surface, out_buf, surface_size, dest_width, dest_height, dest_stride, out_format, 0, 1, 1, 0);
    if (draw_ctx->compress_type == LV_COMPRESS_RLE) {
        surface.x = dest_area->x1;
        surface.y = dest_area->y1;
    }
    if (in_format >= VGHW_FORMAT_L8 && in_format <= VGHW_FORMAT_L1) {
        area.w = src_width;
        area.h = src_height;
        surface.x = dest_area->x1;
        surface.y = dest_area->y1;
        if (draw_ctx->compress_type != LV_COMPRESS_RLE) {
            src_clut = src;
            src += 1024;//256 * 4 色表大小
        }
    }
    jlvg_matrix_set_identity(&surface2image);

    jlvg_image_t *image = (jlvg_image_t *)lv_mem_alloc(sizeof(jlvg_image_t));
    jlvg_image_init(image, src, src_size, src_width, src_height, img_stride, in_format, rle_en, adr_mode, 1, 0);

    jlvg_image_set_clut(image, src_clut, clut_format);

    jlvg_start_frame(g_gpu2p5d, &surface);

    jlvg_draw_image(g_gpu2p5d, &area, image, &surface2image, VGHW_BLEND_SRC);
    jlvg_end_frame(g_gpu2p5d);

    lv_mem_free(image);

    done = true;
__output:
    if (abuf) {
        uint8_t *src_tmp8 = out_buf;
        lv_coord_t src_new_line_step_px = (src_stride - lv_area_get_width(dest_area));
        lv_coord_t src_new_line_step_byte = src_new_line_step_px * LV_IMG_PX_SIZE_ALPHA_BYTE;

        for (int y = 0; y < dest_height; y++) {
            for (int x = 0; x < dest_width; x++) {
                abuf[x] = src_tmp8[LV_IMG_PX_SIZE_ALPHA_BYTE - 1];

#if LV_COLOR_DEPTH == 8 || LV_COLOR_DEPTH == 1
                cbuf[x].full = *src_tmp8;
#elif LV_COLOR_DEPTH == 16
                cbuf[x].full = *src_tmp8 + ((*(src_tmp8 + 1)) << 8);
#elif LV_COLOR_DEPTH == 32
                cbuf[x] = *((lv_color_t *) src_tmp8);
                cbuf[x].ch.alpha = 0xff;
#endif
                src_tmp8 += LV_IMG_PX_SIZE_ALPHA_BYTE;
            }
            cbuf += dest_width;
            abuf += dest_width;
            src_tmp8 += src_new_line_step_byte;
        }

        done = true;
    }

    return done;

}
static lv_res_t _lv_gpu_jl_gpu2p5d_zoom_rotate(lv_draw_ctx_t *draw_ctx, const lv_area_t *dest_area, img_transform_t *img_trans, const lv_area_t *coords,
        void *src_buf, lv_coord_t src_w, lv_coord_t src_h, lv_coord_t src_stride,
        const lv_draw_img_dsc_t *draw_dsc, lv_img_cf_t cf, uint8_t *obuf, lv_color_t *cbuf, lv_opa_t *abuf)
{
    jlvg_surface_t surface;
    jlvg_rect_t area = {0};
    jlvg_matrix_t surface2image;
    uint8_t *src_clut = NULL;
    rle_info_t *rle_info;
    volatile uint8_t rle_en = 0;
    volatile uint8_t adr_mode = 1;
    uint32_t dest_width = lv_area_get_width(dest_area);
    uint32_t dest_height = lv_area_get_height(dest_area);
    uint32_t dest_stride = dest_width * sizeof(lv_color_t);

    lv_area_t *map_area = &img_trans->transform_area;
    float zoom, rotation;

    jlvg_hw_imageformat_t jlvg_img_cf = lv_img_jl_gpu2p5d_get_color_format(cf, NULL);
    bool has_indexed = (jlvg_img_cf >= VGHW_FORMAT_L8 && jlvg_img_cf <= VGHW_FORMAT_L1) ? true : false;
    uint32_t surface_size = dest_width * dest_height * sizeof(lv_color_t);   // ���������buff��С
    uint32_t src_size = src_w * src_h * jlvg_get_image_format_bpp(jlvg_img_cf) >> 3;
    uint32_t img_stride = src_stride * jlvg_get_image_format_bpp(jlvg_img_cf) >> 3;
    uint8_t *out_buf = (uint8_t *)cbuf;

    if (obuf) {
        //用于输出ARGB8565 的临时buf
        out_buf = obuf;
        dest_stride = dest_width * LV_IMG_PX_SIZE_ALPHA_BYTE;
        surface_size = dest_width * dest_height * LV_IMG_PX_SIZE_ALPHA_BYTE;
    }
    uint16_t clut_format = VGHW_CLUT_FORMAT_ARGB8888;
    if (draw_ctx->compress_type == LV_COMPRESS_RLE) {
        rle_info = (rle_info_t *)src_buf;
        rle_en = 1;
        img_stride = lv_rle_get_stride(rle_info, &adr_mode);
        src_size = rle_info->len;
        jlvg_img_cf = rle_info->format;
        clut_format = rle_info->lut_format;
        if (has_indexed) {
            src_clut = (uint8_t *)src_buf + rle_info->lut_addr;
        }
        src_buf = (uint8_t *)src_buf + rle_info->addr;

    } else {
        if (jlvg_img_cf >= VGHW_FORMAT_L8 && jlvg_img_cf <= VGHW_FORMAT_L1) {
            src_clut = src_buf;
            src_buf = (uint8_t *)src_buf + 1024;//256 * 4
        }
    }

    jlvg_matrix_set_identity(&surface2image);
    lv_jl_gpu2p5d_flush_inv_dcache(out_buf, dest_width, dest_height, dest_width, jlvg_get_image_format_bpp(LV_GPU_COLOR_ALPHA_FORMAT));

    jlvg_image_t *image = (jlvg_image_t *)lv_mem_alloc(sizeof(jlvg_image_t));
    jlvg_image_init(image, src_buf, src_size, src_w, src_h, img_stride, jlvg_img_cf, rle_en, adr_mode, 1, 0);

    jlvg_image_set_clut(image, src_clut, clut_format);

    jlvg_surface_init(&surface, out_buf, surface_size, dest_width, dest_height, dest_stride, LV_GPU_COLOR_ALPHA_FORMAT, 0, 1, 1, 0);

    //area.x = 0;
    //area.y = 0;
    area.w = lv_disp_get_hor_res(lv_disp_get_default());// lv_area_get_width(draw_ctx->clip_area);
    area.h = lv_disp_get_ver_res(lv_disp_get_default());// lv_area_get_height(draw_ctx->clip_area);

    if (draw_dsc->angle && draw_dsc->zoom != LV_IMG_ZOOM_NONE) { /* zoom and rotate */
        int32_t pivot_x = lv_map(draw_dsc->pivot.x, 0, src_w, 0, lv_area_get_width(map_area));
        int32_t pivot_y = lv_map(draw_dsc->pivot.y, 0, src_h, 0, lv_area_get_height(map_area));
        rotation = (-draw_dsc->angle / 10.0f) * M_PI / 180.0f;   /* 角度转弧度 */
        zoom = LV_IMG_ZOOM_NONE / (draw_dsc->zoom * 1.0f);
        jlvg_matrix_translate(&surface2image, -pivot_x, -pivot_y);
        jlvg_matrix_rotate(&surface2image, rotation);
        jlvg_matrix_scale(&surface2image, zoom, zoom);
        jlvg_matrix_translate(&surface2image, draw_dsc->pivot.x, draw_dsc->pivot.y);
    } else {
        if (draw_dsc->angle) { /* only rotate */
            int32_t pivot_x = lv_map(draw_dsc->pivot.x, 0, src_w, 0, lv_area_get_width(map_area));
            int32_t pivot_y = lv_map(draw_dsc->pivot.y, 0, src_h, 0, lv_area_get_height(map_area));
            rotation = (-draw_dsc->angle / 10.0f) * M_PI / 180.0f;   /* 角度转弧度 */
            jlvg_matrix_translate(&surface2image, -pivot_x, -pivot_y); //平移到显示区域的旋转中心点
            jlvg_matrix_rotate(&surface2image, rotation);
            jlvg_matrix_translate(&surface2image, draw_dsc->pivot.x, draw_dsc->pivot.y);

        }
        if (draw_dsc->zoom != LV_IMG_ZOOM_NONE) { /* only zoom */
            zoom = LV_IMG_ZOOM_NONE / (draw_dsc->zoom * 1.0f);
            //printf("scale_x = %f; scale_y = %f.", zoom, zoom);
            jlvg_matrix_translate(&surface2image, -draw_dsc->pivot.x, -draw_dsc->pivot.y);//平移到缩放前的中心点
            jlvg_matrix_scale(&surface2image, zoom, zoom);
            jlvg_matrix_translate(&surface2image, draw_dsc->pivot.x * zoom, draw_dsc->pivot.y * zoom); //平移回缩放后的中心点
        }
        //printf("surface (%d,%d) - w:%d h:%d.\n", surface.x, surface.y, surface.width, surface.height);
    }

    lv_area_move(dest_area, coords->x1, coords->y1);
    surface.x = LV_ABS(dest_area->x1 - map_area->x1);
    surface.y = LV_ABS(dest_area->y1 - map_area->y1);

    jlvg_start_frame(g_gpu2p5d, &surface);

    jlvg_draw_image(g_gpu2p5d, &area, image, &surface2image, VGHW_BLEND_SRC);
    jlvg_end_frame(g_gpu2p5d);

    lv_mem_free(image);

    if (abuf) {
        uint8_t *src_tmp8 = out_buf;
        //lv_coord_t src_new_line_step_px = (dest_stride/LV_IMG_PX_SIZE_ALPHA_BYTE - dest_width);
        //lv_coord_t src_new_line_step_byte = src_new_line_step_px * LV_IMG_PX_SIZE_ALPHA_BYTE;

        for (int y = 0; y < dest_height; y++) {
            for (int x = 0; x < dest_width; x++) {
                abuf[x] = src_tmp8[LV_IMG_PX_SIZE_ALPHA_BYTE - 1];

#if LV_COLOR_DEPTH == 8 || LV_COLOR_DEPTH == 1
                cbuf[x].full = *src_tmp8;
#elif LV_COLOR_DEPTH == 16
                cbuf[x].full = *src_tmp8 + ((*(src_tmp8 + 1)) << 8);
#elif LV_COLOR_DEPTH == 32
                cbuf[x] = *((lv_color_t *) src_tmp8);
                cbuf[x].ch.alpha = 0xff;
#endif
                src_tmp8 += LV_IMG_PX_SIZE_ALPHA_BYTE;
            }
            cbuf += dest_width;
            abuf += dest_width;
            //src_tmp8 += src_new_line_step_byte;
        }
    }

    return LV_RES_OK;
}

void lv_jl_gpu2p5d_img_transform(lv_draw_ctx_t *draw_ctx, const lv_area_t *dest_area, img_transform_t *img_trans,
                                 const lv_area_t *coords, const void *src_buf, lv_coord_t src_w, lv_coord_t src_h,
                                 lv_coord_t src_stride, const lv_draw_img_dsc_t *draw_dsc, lv_img_cf_t cf, uint8_t *obuf, lv_color_t *cbuf, lv_opa_t *abuf)
{

    bool done = false;
    if (draw_dsc->angle || draw_dsc->zoom != LV_IMG_ZOOM_NONE) {
#if 0
        lv_area_t *map_area = &img_trans->transform_area;
        printf("\ndraw_area (x,y) = (%d,%d); w = %d, h = %d\n.", dest_area->x1, dest_area->y1, lv_area_get_width(dest_area), lv_area_get_height(dest_area));
        printf("draw_ctx->clip_area (x,y) = (%d,%d) w:%d h:%d\n", draw_ctx->clip_area->x1, draw_ctx->clip_area->y1, lv_area_get_width(draw_ctx->clip_area), lv_area_get_height(draw_ctx->clip_area));
        lv_area_t area;
        lv_area_copy(&area, dest_area);
        lv_area_move(&area, coords->x1, coords->y1);
        printf("area (x1,y1) = (%d,%d); (w,h) = (%d,%d)\n", area.x1, area.y1, lv_area_get_width(&area), lv_area_get_height(&area));
        printf("map_area (x1,y1) = (%d,%d); (w,h) = (%d,%d)\n", map_area->x1, map_area->y1, lv_area_get_width(map_area), lv_area_get_height(map_area));
#endif
#if 1
        // zoom or rotate
        done = _lv_gpu_jl_gpu2p5d_zoom_rotate(draw_ctx, dest_area, img_trans, coords, src_buf, src_w, src_h,
                                              src_stride, draw_dsc, cf, obuf, cbuf, abuf);
        if (!done) {
            printf("JLGPU img transform failed. Fallback.");
        }
#endif
    }

    if (!done) {
        lv_draw_sw_transform(draw_ctx, dest_area, src_buf, src_w, src_h, src_stride, draw_dsc, cf, cbuf, abuf);
    }


}
static lv_res_t lv_draw_jl_gpu2p5d_covert_cb(lv_draw_ctx_t *draw_ctx, const lv_area_t *dest_area, const void *src_buf, lv_coord_t src_w, lv_coord_t src_h,
        lv_coord_t src_stride, const lv_draw_img_dsc_t *draw_dsc, lv_img_cf_t cf, uint8_t *obuf, lv_color_t *cbuf, lv_opa_t *abuf)
{
    const uint8_t *src_tmp8 = (const uint8_t *)src_buf;
    bool done = false;

    if (cf == LV_IMG_CF_TRUE_COLOR_ALPHA) {
        if (draw_ctx->compress_type != LV_COMPRESS_RLE) {
            src_tmp8 += (src_stride * dest_area->y1 * LV_IMG_PX_SIZE_ALPHA_BYTE) + dest_area->x1 * LV_IMG_PX_SIZE_ALPHA_BYTE;
        }
        _lv_jlgpu_texture_copy(draw_ctx, dest_area, src_tmp8, src_w, src_h, src_stride, LV_GPU_COLOR_ALPHA_FORMAT, LV_GPU_COLOR_ALPHA_FORMAT, obuf, cbuf, abuf, 0);
        return LV_RES_OK;
    } else if (cf == LV_IMG_CF_TRUE_COLOR_CHROMA_KEYED) {
        //TODO
        printf("\n[ debug ]--func=%s line=%d\n", __func__, __LINE__);
        /* src_tmp8 += (src_stride * dest_area->y1 * sizeof(lv_color_t)) + dest_area->x1 * sizeof(lv_color_t); */
        /* _lv_jlgpu_texture_copy(draw_ctx, dest_area, src_tmp8, src_w, src_h, src_stride, LV_GPU_COLOR_ALPHA_FORMAT, LV_GPU_COLOR_FORMAT, obuf, cbuf, abuf, 1); */
        /* return LV_RES_OK; */
    } else if (cf == LV_IMG_CF_TRUE_COLOR) {
        uint32_t px_cnt = lv_area_get_size(dest_area);
        lv_memset_ff(abuf, px_cnt);
        if (draw_ctx->compress_type != LV_COMPRESS_RLE) {
            src_tmp8 += (src_stride * dest_area->y1 * sizeof(lv_color_t)) + dest_area->x1 * sizeof(lv_color_t);
        }
        done = _lv_jlgpu_texture_copy(draw_ctx, dest_area, src_tmp8, src_w, src_h, src_stride, LV_GPU_COLOR_FORMAT, LV_GPU_COLOR_FORMAT, obuf, cbuf, NULL, 0);
        if (done == LV_RES_OK) {
            return LV_RES_OK;
        }

    } else if (cf == LV_IMG_CF_RGB565A8) {
        //TODO
        printf("\n[ debug ]--func=%s line=%d\n", __func__, __LINE__);
        /* src_tmp8 += (src_stride * dest_area->y1 * sizeof(lv_color_t)) + dest_area->x1 * sizeof(lv_color_t); */
        /* _lv_jlgpu_texture_copy(draw_ctx, dest_area, src_tmp8, src_w, src_h, src_stride, LV_GPU_COLOR_FORMAT, LV_GPU_COLOR_FORMAT, cbuf, NULL, 0); */
        /* src_tmp8 = (const uint8_t*)src_buf; */
        /* src_tmp8 += sizeof(lv_color_t) * src_w * src_h; */
        /* src_tmp8 += src_stride * dest_area->y1 + dest_area->x1; */
        /* _lv_jlgpu_texture_copy_only_alpha(draw_ctx, dest_area, src_tmp8, src_w, src_h, src_stride, abuf); */
        /* return LV_RES_OK; */
    } else if (cf >= LV_IMG_CF_INDEXED_1BIT && cf <= LV_IMG_CF_INDEXED_8BIT) {
        _lv_jlgpu_texture_copy(draw_ctx, dest_area, src_tmp8, src_w, src_h, src_stride, lv_img_jl_gpu2p5d_get_color_format(cf, NULL), LV_GPU_COLOR_ALPHA_FORMAT, obuf, cbuf, abuf, 0);
        return LV_RES_OK;
    }

    sw_convert_cb(dest_area, src_buf, src_w, src_h, src_w, draw_dsc, cf, cbuf, abuf);
    return LV_RES_OK;
}

void LV_ATTRIBUTE_FAST_MEM lv_draw_jl_gpu2p5d_img_decoded_with_mask(struct _lv_draw_ctx_t *draw_ctx, const lv_draw_img_dsc_t *draw_dsc, const lv_area_t *coords, lv_area_t *draw_area, const uint8_t *src_buf, lv_img_cf_t cf)
{
    jlgpu_printf("[ debug ] %s() %d", __func__, __LINE__);
    lv_area_t _blend_area = {0};
    _blend_area.x1 = draw_ctx->clip_area->x1;
    _blend_area.x2 = draw_ctx->clip_area->x2;
    _blend_area.y1 = draw_ctx->clip_area->y1;
    _blend_area.y2 = draw_ctx->clip_area->y2;
    lv_draw_sw_blend_dsc_t blend_dsc = {0};
    /*lv_area_t *blend_area = draw_area;*/
    lv_area_t *blend_area = &_blend_area;
    blend_dsc.opa = draw_dsc->opa;
    blend_dsc.blend_mode = draw_dsc->blend_mode;
    blend_dsc.blend_area = blend_area;

    lv_coord_t src_w = lv_area_get_width(coords);
    lv_coord_t src_h = lv_area_get_height(coords);
    lv_coord_t blend_h = lv_area_get_height(blend_area);
    lv_coord_t blend_w = lv_area_get_width(blend_area);

    uint32_t max_buf_size = MAX_BUF_SIZE;
    uint32_t blend_size = lv_area_get_size(blend_area);
    uint32_t buf_h;
    uint32_t buf_w = blend_w;
    if (blend_size <= max_buf_size) {
        buf_h = blend_h;
    } else {
        /*Round to full lines*/
        buf_h = max_buf_size / blend_w;
    }
    /*Create buffers and masks*/
    uint32_t buf_size = buf_w * buf_h;

    lv_color_t *rgb_buf = lv_mem_buf_get(buf_size * sizeof(lv_color_t));

    uint8_t *out_tmp_buf = NULL;
    lv_opa_t *mask_buf = lv_mem_buf_get(buf_size);
    blend_dsc.mask_buf = mask_buf;
    blend_dsc.mask_area = blend_area;
    blend_dsc.mask_res = LV_DRAW_MASK_RES_CHANGED;
    blend_dsc.src_buf = rgb_buf;
    lv_coord_t y_last = blend_area->y2;
    blend_area->y2 = blend_area->y1 + buf_h - 1;

    lv_draw_mask_res_t mask_res_def = (cf != LV_IMG_CF_TRUE_COLOR || draw_dsc->angle ||
                                       draw_dsc->zoom != LV_IMG_ZOOM_NONE) ?
                                      LV_DRAW_MASK_RES_CHANGED : LV_DRAW_MASK_RES_FULL_COVER;
    blend_dsc.mask_res = mask_res_def;
    bool transform = draw_dsc->angle != 0 || draw_dsc->zoom != LV_IMG_ZOOM_NONE ? true : false;
    if (transform || cf == LV_IMG_CF_TRUE_COLOR_ALPHA || cf == LV_IMG_CF_TRUE_COLOR_CHROMA_KEYED
        || (cf >= LV_IMG_CF_INDEXED_1BIT && cf <= LV_IMG_CF_INDEXED_8BIT)) {
        if (transform) {
            if (__img_trans.transform_start == 0 || __img_trans.src_buf != src_buf
                || __img_trans.zoom != draw_dsc->zoom
                || __img_trans.angle != draw_dsc->angle
                || draw_ctx->clip_area->x2 != __img_trans.transform_area.x2
                || draw_ctx->clip_area->y2 != __img_trans.transform_area.y2) {
                int32_t w = lv_area_get_width(coords);
                int32_t h = lv_area_get_height(coords);

                lv_area_t a;
                /* 获取变换后的区域 */
                _lv_img_buf_get_transformed_area(&a, w, h, draw_dsc->angle, draw_dsc->zoom, &draw_dsc->pivot);
                lv_area_move(&a, coords->x1, coords->y1);

                __img_trans.zoom = draw_dsc->zoom;
                __img_trans.angle = draw_dsc->angle;
                __img_trans.src_buf = (void *)src_buf;
                lv_area_set(&__img_trans.transform_area, a.x1, a.y1, a.x2, a.y2);
                //lv_area_set(&__img_trans.transform_area, draw_ctx->clip_area->x1, draw_ctx->clip_area->y1, a.x2, a.y2);

                /* 保存变换第一次的区域，用于GPU做整张图变换 */
                lv_area_copy(&__img_trans.clip_area, &blend_area);
                lv_area_move(&__img_trans.clip_area, -coords->x1, -coords->y1);

                if (draw_ctx->clip_area->y2 < __img_trans.transform_area.y2) {
                    __img_trans.transform_start = 1;
                }
            } else {
                if (draw_ctx->clip_area->y2 >= __img_trans.transform_area.y2) {
                    __img_trans.transform_start = 0;
                }
            }
        }
        out_tmp_buf = lv_mem_alloc(blend_size * LV_IMG_PX_SIZE_ALPHA_BYTE);
    }

    while (blend_area->y1 <= y_last) {
        /*Apply transformations if any or separate the channels*/
        lv_area_t transform_area;
        lv_area_copy(&transform_area, blend_area);
        lv_area_move(&transform_area, -coords->x1, -coords->y1);
        if (transform) {
            lv_jl_gpu2p5d_img_transform(draw_ctx, &transform_area, &__img_trans, coords, src_buf, src_w, src_h, src_w,
                                        draw_dsc, cf, out_tmp_buf, rgb_buf, mask_buf);
        } else {
            lv_draw_jl_gpu2p5d_covert_cb(draw_ctx, &transform_area, src_buf, src_w, src_h, src_w, draw_dsc, cf, out_tmp_buf, rgb_buf, mask_buf);
        }

        /*Apply recolor*/
        if (draw_dsc->recolor_opa > LV_OPA_MIN) {
            uint16_t premult_v[3];
            lv_opa_t recolor_opa = draw_dsc->recolor_opa;
            lv_color_t recolor = draw_dsc->recolor;
            lv_color_premult(recolor, recolor_opa, premult_v);
            recolor_opa = 255 - recolor_opa;
            uint32_t i;
            for (i = 0; i < buf_size; i++) {
                rgb_buf[i] = lv_color_mix_premult(premult_v, rgb_buf[i], recolor_opa);
            }
        }
#if LV_DRAW_COMPLEX
        /*Apply the masks if any*/
        lv_coord_t y;
        lv_opa_t *mask_buf_tmp = mask_buf;
        for (y = blend_area->y1; y <= blend_area->y2; y++) {
            lv_draw_mask_res_t mask_res_line;
            mask_res_line = lv_draw_mask_apply(mask_buf_tmp, blend_area->x1, y, blend_w);

            if (mask_res_line == LV_DRAW_MASK_RES_TRANSP) {
                lv_memset_00(mask_buf_tmp, blend_w);
                blend_dsc.mask_res = LV_DRAW_MASK_RES_CHANGED;
            } else if (mask_res_line == LV_DRAW_MASK_RES_CHANGED) {
                blend_dsc.mask_res = LV_DRAW_MASK_RES_CHANGED;
            }
            mask_buf_tmp += blend_w;
        }
#endif

        /*Blend*/
        lv_draw_sw_blend(draw_ctx, &blend_dsc);

        /*Go the the next lines*/
        blend_area->y1 = blend_area->y2 + 1;
        blend_area->y2 = blend_area->y1 + buf_h - 1;
        if (blend_area->y2 > y_last) {
            blend_area->y2 = y_last;
        }
    }

    lv_mem_buf_release(mask_buf);
    lv_mem_buf_release(rgb_buf);
    if (out_tmp_buf) {
        lv_mem_free(out_tmp_buf);
    }


}

void LV_ATTRIBUTE_FAST_MEM lv_draw_jl_gpu2p5d_img_decoded(struct _lv_draw_ctx_t *draw_ctx,
        const lv_draw_img_dsc_t *dsc,
        const lv_area_t *coords, const uint8_t *src_buf,
        lv_img_cf_t cf)
{
    jlgpu_printf("[ debug ] %s() %d", __func__, __LINE__);

    if (dsc->opa <= (lv_opa_t)LV_OPA_MIN) {
        jlgpu_printf("[ debug ] %s() %d", __func__, __LINE__);
        return;
    }

    if (!src_buf) {
        jlgpu_printf("[ debug ] %s() %d", __func__, __LINE__);
        lv_draw_sw_img_decoded(draw_ctx, dsc, coords, src_buf, cf);
        return;
    }

    bool done = false;
    bool cf_flag;
    jlvg_hw_imageformat_t jlvg_img_cf = lv_img_jl_gpu2p5d_get_color_format(cf, &cf_flag);   //根据图像颜色格式获取 VG 配置的像素格式
    if (cf_flag == false) {
        jlgpu_printf("[ debug ] %s() %d", __func__, __LINE__);
        goto jlvg_quit;
    }
    bool mode_flag;
    uint8_t blend_mode = lv_jl_gpu2p5d_get_blend_mode(dsc->blend_mode, &mode_flag);   //根据图像的混合模式获取 VG 配置的混合模式
    if (mode_flag == false) {
        jlgpu_printf("[ debug ] %s() %d", __func__, __LINE__);
        goto jlvg_quit;
    }
    if (lv_img_cf_is_chroma_keyed(cf)) {
        jlgpu_printf("[ debug ] %s() %d", __func__, __LINE__);
        goto jlvg_quit;
    }
    jlgpu_printf("[ debug ] %s() %d", __func__, __LINE__);

    lv_area_t image_tf_area;
    lv_area_copy(&image_tf_area, coords);
    bool has_angle = dsc->angle == 0 ? false : true;
    bool has_zoom = dsc->zoom == LV_IMG_ZOOM_NONE ? false : true;
    if (has_angle || has_zoom) {
        int32_t w = lv_area_get_width(coords);
        int32_t h = lv_area_get_height(coords);

        _lv_img_buf_get_transformed_area(&image_tf_area, w, h, dsc->angle, dsc->zoom, &dsc->pivot);

        lv_area_move(&image_tf_area, coords->x1, coords->y1);
    }

    lv_area_t rel_coords;
    lv_area_copy(&rel_coords, coords);
    lv_area_move(&rel_coords, -draw_ctx->buf_area->x1, -draw_ctx->buf_area->y1);
    //printf("rel_coords (x1,y1) = (%d,%d); (x2,y2) = (%d,%d).", rel_coords.x1, rel_coords.y1, rel_coords.x2, rel_coords.y2);

    lv_area_t rel_clip_area;
    lv_area_copy(&rel_clip_area, draw_ctx->clip_area);
    lv_area_move(&rel_clip_area, -draw_ctx->buf_area->x1, -draw_ctx->buf_area->y1);

    lv_area_t rel_image_tf_area;
    lv_area_copy(&rel_image_tf_area, &image_tf_area);
    lv_area_move(&rel_image_tf_area, -draw_ctx->buf_area->x1, -draw_ctx->buf_area->y1);

    bool has_indexed = (jlvg_img_cf >= VGHW_FORMAT_L8 && jlvg_img_cf <= VGHW_FORMAT_L1) ? true : false;

    lv_area_t blend_area;   //这个区域无论是帧buff还是行buff都是相对的新的绘制区域
    if (!_lv_area_intersect(&blend_area, &rel_image_tf_area, &rel_clip_area)) {
        jlgpu_printf("[ debug ] %s() %d", __func__, __LINE__);
        return; /*Fully clipped, nothing to do*/
    }
    //printf("blend_area (x1,y1) = (%d,%d); (x2,y2) = (%d,%d).", blend_area.x1, blend_area.y1, blend_area.x2, blend_area.y2);
    bool has_recolor = (dsc->recolor_opa != LV_OPA_TRANSP);
    if (has_recolor) {
        lv_draw_jl_gpu2p5d_img_decoded_with_mask(draw_ctx, dsc, coords, &blend_area, src_buf, cf);
        done = true;
        goto jlvg_quit;
    }

    bool has_mask = lv_draw_mask_is_any(&blend_area);
    if (has_mask) {
        //带mask的情况
        jlgpu_printf("[ debug ] %s() %d", __func__, __LINE__);
        lv_draw_jl_gpu2p5d_img_decoded_with_mask(draw_ctx, dsc, coords, &blend_area, src_buf, cf);
        done = true;
        goto jlvg_quit;
    }

    int32_t gpu_min_area_size = (draw_ctx->compress_type == LV_COMPRESS_RLE || has_indexed || (LV_COLOR_DEPTH_EXTEN == 24)) ? 0 : LV_JL_GPU_MIN_AREA_SIZE;
    if ((lv_area_get_size(&blend_area) > gpu_min_area_size)) { // 确认绘制属性是否支持�ϻ��������Ƿ�֧��
        done = true;
        goto jlvg_begin;
    } else {
        jlgpu_printf("\n[ debug ] %s() %d has_mask:%d has_recolor:%d cf_flag:%d mode_flag:%d %d\n", __func__, __LINE__, has_mask, has_recolor, cf_flag, mode_flag, lv_area_get_size(&blend_area));
        goto jlvg_quit;
    }

jlvg_begin:
    //开始 JLVG 渲染动作
    // 1、初始化渲染空间
    uint32_t fb_width;
    uint32_t fb_height;
    uint32_t fb_size;
    uint32_t dest_stride;
    uint8_t *dest_buf;
    rle_info_t *rle_info;
    uint32_t bytes_per_pixel;
    jlvg_hw_imageformat_t jlvg_dest_cf;
    uint32_t img_stride;
    uint32_t src_size;
    uint8_t *src_clut = NULL;

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

    jlvg_matrix_t surface2image;    // 变换矩阵 surface to image
    jlvg_matrix_t image2surface;    // 变换矩阵 image to surface (surface2image 的逆矩阵)
    jlvg_matrix_t surface2paint;    // 变换矩阵 surface to paint

    jlvg_surface_t surface;     // 绘制的窗口
    jlvg_rect_t surface_area;   // 绘制的窗口区域:实际就是 draw_ctx->buf_area 所在的区域
    jlvg_rect_t draw_area;      // 在窗口内实际要绘制的区域:实际就是 blend_area

    //初始化单位变换矩阵
    jlvg_matrix_set_identity(&surface2image);
    jlvg_matrix_set_identity(&image2surface);
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
    /* printf("draw_area (x,y) = (%d,%d); w = %d, y = %d.", draw_area.x, draw_area.y, draw_area.w, draw_area.h); */


    uint8_t adr_mode = 1;
    uint8_t rle_en = 0;
    uint8_t dither_en = 0;

    //2、获取原始图像数据信息: 根据  坐标获取图像坐标
    uint32_t src_width = coords->x2 - coords->x1 + 1;
    uint32_t src_height = coords->y2 - coords->y1 + 1;
    uint32_t img_bytes_per_pixel = lv_img_cf_get_px_size(cf) >> 3;  // ÷ 8 得到颜色深度对应的字节数
    uint16_t clut_format = VGHW_CLUT_FORMAT_ARGB8888;
    if (draw_ctx->compress_type == LV_COMPRESS_RLE) {
        rle_info = (rle_info_t *)src_buf;
        rle_en = 1;
        img_stride = lv_rle_get_stride(rle_info, &adr_mode);
        src_size = rle_info->len;
        jlvg_img_cf = rle_info->format;
        clut_format = rle_info->lut_format;
        if (has_indexed) {
            src_clut = (uint8_t *)src_buf + rle_info->lut_addr;
        }
        src_buf = (uint8_t *)src_buf + rle_info->addr;
        if (has_indexed) {
            if (clut_format == VGHW_CLUT_FORMAT_ARGB8888 || clut_format == VGHW_CLUT_FORMAT_RGB888) {
                dither_en = 1;
            }
        }
        if (jlvg_img_cf == VGHW_CLUT_FORMAT_ARGB8888 || jlvg_img_cf == VGHW_CLUT_FORMAT_RGB888) {
            dither_en = 1;
        }
        jlgpu_printf("[ debug ] %s() %d %x %dx%d rle block:%d rle format:%d", __func__, __LINE__, src_buf, rle_info->width, rle_info->height, rle_info->block, rle_info->format);
    } else {
        img_stride = src_width * img_bytes_per_pixel;
        src_size = src_width * src_height * img_bytes_per_pixel;
        if (has_indexed) {
            src_clut = src_buf;
            src_buf += 1024;//256 * 4
            dither_en = 1;
        }
    }

    //窗口初始化
    jlvg_surface_init(&surface, dest_buf, fb_size, fb_width, fb_height, dest_stride, jlvg_dest_cf, dither_en, 1, 1, 0);

    jlvg_image_t *image  = (jlvg_image_t *)lv_mem_alloc(sizeof(jlvg_image_t));

    lv_jl_gpu2p5d_flush_inv_dcache(src_buf, src_width, src_height, src_width, lv_img_cf_get_px_size(cf));

    jlvg_image_init(image, src_buf, src_size, src_width, src_height, img_stride, jlvg_img_cf, rle_en, adr_mode, 1, 0);
    /* printf("img info : rle_en:%d; src_width = %d; src_height = %d; src_size = %d; img_stride = %d.", rle_en, src_width, src_height, src_size, img_stride); */

    jlvg_image_set_clut(image, src_clut, clut_format);

    //3�配置变换矩阵
    float scale_x;
    float scale_y;
    float rotation;
    lv_point_t pivot_abs;   //变换原点的绝对位置，不会变化
    lv_point_t coords_abs;  //图像(0, 0)原点的绝对位置，不会变化

    if (has_angle || has_zoom) {
        // 计算变换原点的绝对位置
#if (JLVG_DRAW_FULL_FB_ENABLE == 1)
        pivot_abs.x = dsc->pivot.x + rel_coords.x1;
        pivot_abs.y = dsc->pivot.y + rel_coords.y1;
        //printf("0 pivot_abs (x,y) = (%d,%d).", pivot_abs.x, pivot_abs.y);
#else
        //计算变换原点绝对位置在 blend_area 区域的相对位置
        pivot_abs.x = dsc->pivot.x + rel_coords.x1 - blend_area.x1;
        pivot_abs.y = dsc->pivot.y + rel_coords.y1 - blend_area.y1;
        //printf("1 pivot_abs (x,y) = (%d,%d).", pivot_abs.x, pivot_abs.y);
#endif
        /* printf("pivot_abs (x,y) = (%d,%d) ; pivot (x,y) = (%d,%d).", pivot_abs.x, pivot_abs.y, dsc->pivot.x, dsc->pivot.y); */

        if (has_angle && (!has_zoom)) { // 仅旋转
            rotation = (-1.0f) * dsc->angle * M_PI / 1800.0f;
            //printf("rotation = %f.", rotation);

            // 旋转变换流程说明：
            // openVG 的流程是先平移到相对变换原点位置，再旋转变换之后再平移到绝对原点位置; JLVG 仅旋转时保持一样的动作
            /* ===== rotate begin ===== */
            jlvg_matrix_translate(&image2surface, -pivot_abs.x, -pivot_abs.y);      // 基于变换原点的绝对位置进行偏移

            jlvg_matrix_rotate(&image2surface, rotation);

            jlvg_matrix_translate(&image2surface, dsc->pivot.x, dsc->pivot.y);      // 基于变换原点的相对位置进行偏移
            /* ===== rotate end ===== */
        } else if (has_zoom && (!has_angle)) {  // 仅缩放
            scale_x = dsc->zoom * 1.0f / LV_IMG_ZOOM_NONE;
            scale_y = scale_x;
            //printf("scale_x = %f; scale_y = %f.", scale_x, scale_y);

            // 缩放变换流程说明：
            // openVG 的流程是先平移到相对变换原点位置，再缩放变换之后再平移到绝对原点位置;
            // JLVG 需要通过逆变换：实际上是先缩放变换然后平移到绝对原点位置之后再逆变换，之后再平移回变换原点位置，并且由于逆变换之后平移方向反向
            /* ===== scale begin ===== */
            jlvg_matrix_set_scale(&surface2image, scale_x, scale_y);

            jlvg_matrix_translate(&surface2image, pivot_abs.x, pivot_abs.y);    // 基于变换原点的绝对位置进行偏移

            //矩阵逆运算
            jlvg_matrix_invert(&image2surface, &surface2image);

            jlvg_matrix_translate(&image2surface, dsc->pivot.x, dsc->pivot.y);  // 基于变换原点的相对位置进行偏移,由于逆变换，方向相反，流程上和旋转变换的第一步相对抵消
            /* ===== scale end ===== */
        } else {    // 同时缩放和旋转
            rotation = (-1.0f) * dsc->angle * M_PI / 1800.0f;
            //printf("rotation = %f.", rotation);
            scale_x = dsc->zoom * 1.0f / LV_IMG_ZOOM_NONE;
            scale_y = scale_x;
            //printf("scale_x = %f; scale_y = %f.", scale_x, scale_y);

            // 缩放变换流程说明：
            // openVG 的流程是先平移到相对变换原点位置，再缩放变换之后再平移到绝对原点位置;
            // JLVG 需要通过逆变换：实际上是先缩放变换然后平移到绝对原点位置之后再逆变换，之后再平移回变换原点位置，并且由于逆变换之后平移方向反向
            /* ===== scale begin ===== */
            jlvg_matrix_set_scale(&surface2image, scale_x, scale_y);

            jlvg_matrix_translate(&surface2image, pivot_abs.x, pivot_abs.y);    // 基于变换原点的绝对位置进行偏移

            //矩阵逆运算
            jlvg_matrix_invert(&image2surface, &surface2image);

            //jlvg_matrix_translate(&image2surface, dsc->pivot.x , dsc->pivot.y); // 基于变换原点的相对位置进行偏移,由于逆变换，方向相反，流程上和旋转变换的第一步相对抵消
            /* ===== scale end ===== */

            // 旋转变换流程说明：
            // openVG 的流程是先平移到相对变换原点位置，再旋转变换之后再平移到绝对原点位置;
            // JLVG 由于和缩放一起走的逆变换流程，所以只需要平移相对原点位置即可
            /* ===== rotate begin ===== */
            //jlvg_matrix_translate(&image2surface, -dsc->pivot.x , -dsc->pivot.y);   // 基于变换原点的相对位置进行偏移，由于逆变换，方向相反，流程上和缩放变换的最后一步互相抵消

            jlvg_matrix_rotate(&image2surface, rotation);

            jlvg_matrix_translate(&image2surface, dsc->pivot.x, dsc->pivot.y);      // 基于变换原点的相对位置进行偏移
            /* ===== rotate end ===== */
        }
    } else {    // 无变换动作
#if (JLVG_DRAW_FULL_FB_ENABLE == 1)
        coords_abs.x = rel_coords.x1;
        coords_abs.y = rel_coords.y1;
        //printf("0 coords_abs (x,y) = (%d,%d).", coords_abs.x, coords_abs.y);
#else
        //计算变换原点绝对位置在 blend_area 区域的相对位置
        coords_abs.x = rel_coords.x1 - blend_area.x1;
        coords_abs.y = rel_coords.y1 - blend_area.y1;
        //printf("1 coords_abs (x,y) = (%d,%d).", coords_abs.x, coords_abs.y);
#endif
        if (coords_abs.x || coords_abs.y) {
            jlvg_matrix_translate(&image2surface, -coords_abs.x, -coords_abs.y);      // 基于图像(0, 0)原点的绝对位置进行偏移
            //printf("coords_abs (x,y) = (%d,%d).", coords_abs.x, coords_abs.y);
        }
    }

    //4、硬件渲染图像数据
    jlvg_start_frame(g_gpu2p5d, &surface);

    // 非真实显存需要进行一次清屏操作
    if (!is_frame_buf) {
        jlvg_color_t clear_color = {0x00, 0x00, 0x00, 0x00};
        jlvg_clear(g_gpu2p5d, &draw_area, &clear_color);
    }

    //根据图像透明度进行渲染动作
    jlvg_paint_color_t paint;
    jlvg_color_t paint_color = { 0xff, 0xff, 0xff, 0xff };
    if (dsc->opa < (lv_opa_t)LV_OPA_MAX) {
        /* printf("dsc->opa = 0x%02x.", dsc->opa); */
        paint_color.a = dsc->opa;
        jlvg_color_premultiply(&paint_color);    // 填充像素预乘
        jlvg_paint_color_init(&paint, paint_color);
        jlvg_draw_image_with_paint(g_gpu2p5d, &draw_area, image, &paint, &image2surface, &surface2paint, blend_mode, 0);
    } else {

#if LV_COLOR_DEPTH_EXTEN == 24
        if (jlvg_get_bgcolor_is_color_key(dest_buf, LV_COLOR_KEY)) {
            jlvg_draw_image(g_gpu2p5d, &draw_area, image, &image2surface, VGHW_BLEND_SRC);//保留a通道
        } else {
            jlvg_draw_image(g_gpu2p5d, &draw_area, image, &image2surface, blend_mode);
        }
#else
        jlvg_draw_image(g_gpu2p5d, &draw_area, image, &image2surface, blend_mode);
#endif

    }

    jlvg_end_frame(g_gpu2p5d);

    /* jlvg_image_deinit(image); */

    lv_mem_free(image);

    /* jlvg_surface_deinit(&surface); */


jlvg_quit:
    if (!done) {
        if (draw_ctx->compress_type == LV_COMPRESS_RLE) {
            LV_LOG_ERROR("jl_gpu2p5d_img_decoded rle error");
            return;
        } else {
            lv_draw_sw_img_decoded(draw_ctx, dsc, coords, src_buf, cf);
        }
    }
}

/**********************
 *   STATIC FUNCTIONS
 **********************/
#endif  //LV_USE_JL_GPU2P5D_DRAW_IMG
#endif /*LV_USE_GPU_JL_GPU2P5D*/
