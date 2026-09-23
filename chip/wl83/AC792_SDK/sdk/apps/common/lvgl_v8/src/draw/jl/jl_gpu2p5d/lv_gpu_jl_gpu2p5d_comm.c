/**
 * @file lv_gpu_jl_gpu2p5d_comm.c
 *
 */

/*********************
 *      INCLUDES
 *********************/
#include "../../lv_draw.h"
#include "lv_gpu_jl_gpu2p5d.h"
#include "lvgl.h"
#if LV_USE_GPU_JL_GPU2P5D

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

jlvg_hw_imageformat_t lv_img_jl_gpu2p5d_get_color_format(lv_img_cf_t cf, bool *cf_flag)
{
    jlvg_hw_imageformat_t jlvg_cf = VGHW_FORMAT_ARGB8888;
    if (cf_flag != NULL) {
        *cf_flag = true;   // false : 不支持：true : 支持
    }

    //printf("lv_img_cf_t  = 0x%02x.", cf);
    switch (cf) {
    case LV_IMG_CF_TRUE_COLOR:
#if LV_COLOR_DEPTH == 16
        jlvg_cf = VGHW_FORMAT_RGB565;
#elif LV_COLOR_DEPTH == 24
        jlvg_cf = VGHW_FORMAT_RGB888;
#elif LV_COLOR_DEPTH == 32
        jlvg_cf = VGHW_FORMAT_ARGB8888;
#else
        /*Can't use GPU with other formats*/
#endif
        break;
    case LV_IMG_CF_TRUE_COLOR_ALPHA:
#if LV_COLOR_DEPTH == 16
        jlvg_cf = VGHW_FORMAT_ARGB8565;
#elif LV_COLOR_DEPTH == 24
        jlvg_cf = VGHW_FORMAT_ARGB8888;
#elif LV_COLOR_DEPTH == 32
        jlvg_cf = VGHW_FORMAT_ARGB8888;
#else
        /*Can't use GPU with other formats*/
#endif
        break;
    case LV_IMG_CF_RGB888:
        jlvg_cf = VGHW_FORMAT_RGB888;
        break;
    case LV_IMG_CF_RGB565:
        jlvg_cf = VGHW_FORMAT_RGB565;
        break;
    case LV_IMG_CF_ALPHA_8BIT:
        jlvg_cf = VGHW_FORMAT_A8;
        break;
    case LV_IMG_CF_ALPHA_4BIT:
        jlvg_cf = VGHW_FORMAT_A4;
        break;
    case LV_IMG_CF_ALPHA_2BIT:
        jlvg_cf = VGHW_FORMAT_A2;
        break;
    case LV_IMG_CF_ALPHA_1BIT:
        jlvg_cf = VGHW_FORMAT_A1;
        break;
    case LV_IMG_CF_INDEXED_1BIT:
        jlvg_cf = VGHW_FORMAT_L1;
        break;
    case LV_IMG_CF_INDEXED_2BIT:
        jlvg_cf = VGHW_FORMAT_L2;
        break;
    case LV_IMG_CF_INDEXED_4BIT:
        jlvg_cf = VGHW_FORMAT_L4;
        break;
    case LV_IMG_CF_INDEXED_8BIT:
        jlvg_cf = VGHW_FORMAT_L8;
        break;
    default:
        if (cf_flag != NULL) {
            *cf_flag = false;   // false : 不支持：true : 支持
        }
        //printf("Unsupported color format.");
        break;
    }

    //printf("jlvg_cf  = 0x%02x.", jlvg_cf);
    return jlvg_cf;
}

uint8_t lv_jl_gpu2p5d_get_blend_mode(lv_blend_mode_t lv_blend_mode, bool *mode_flag)
{
    uint8_t jlvg_blend_mode = VGHW_BLEND_SRC;
    if (mode_flag != NULL) {
        *mode_flag = true;   // false : 不支持：true : 支持
    }

    //printf("lv_blend_mode 0x%02x.", lv_blend_mode);
    switch (lv_blend_mode) {
    case LV_BLEND_MODE_NORMAL:
        jlvg_blend_mode = VGHW_BLEND_SRC_OVER;
        break;
    case LV_BLEND_MODE_ADDITIVE:
        jlvg_blend_mode = VGHW_BLEND_ADDITIVE;
        break;
    case LV_BLEND_MODE_MULTIPLY:
        jlvg_blend_mode = VGHW_BLEND_MULTIPLY;
        break;
    case LV_BLEND_MODE_REPLACE:
        jlvg_blend_mode = VGHW_BLEND_SRC;
    default:
        if (mode_flag != NULL) {
            *mode_flag = false;   // false : 不支持：true : 支持
        }
        //printf("Unsupported blend mode.");
        break;
    }

    //printf("jlvg_blend_mode  = 0x%02x.", jlvg_blend_mode);
    return jlvg_blend_mode;
}

uint8_t lv_jl_gpu2p5d_get_path_type(lv_font_path_type_t lv_font_path_type, bool *path_flag)
{
    jlvg_hw_pathtype_t jlvg_path_type = VGHW_CLOSE_PATH;
    if (path_flag != NULL) {
        *path_flag = true;   // false : 不支持：true : 支持
    }

    //printf("lv_font_path_type 0x%02x.", lv_font_path_type);
    switch (lv_font_path_type) {
    case LV_FONT_VERTEX_MOVE_TO:
        jlvg_path_type = VGHW_MOVE_TO;
        break;
    case LV_FONT_VERTEX_LINE_TO:
        jlvg_path_type = VGHW_LINE_TO;
        break;
    case LV_FONT_VERTEX_QUAD_TO:
        jlvg_path_type = VGHW_QUAD_TO;
        break;
    case LV_FONT_VERTEX_CUBIC_TO:
        jlvg_path_type = VGHW_CUBIC_TO;
    default:
        if (path_flag != NULL) {
            *path_flag = false;   // false : 不支持：true : 支持
        }
        //printf("Unsupported path type.");
        break;
    }

    //printf("jlvg_path_type  = 0x%02x.", jlvg_path_type);
    return jlvg_path_type;
}

void lv_jl_gpu2p5d_flush_inv_dcache(uint8_t *buf, uint32_t w, uint32_t h, uint32_t stride, uint8_t color_depth)
{
    /* 区域刷新Cache */
    uint8_t *area_ptr = (uint8_t *)buf;
    uint32_t width_bytes = w * color_depth >> 3;
    uint32_t offset = stride * color_depth >> 3;
    for (int y = 0; y < h; y++) {
        DcuFlushinvRegion((u32 *)area_ptr, width_bytes);
        area_ptr += offset;
    }
}

void lv_jl_gpu2p5d_flush_dcache(uint8_t *buf, uint32_t w, uint32_t h, uint32_t stride, uint8_t color_depth)
{
    uint8_t *area_ptr = (uint8_t *)buf;
    uint32_t width_bytes = w * color_depth >> 3;
    uint32_t offset = stride * color_depth >> 3;
    for (int y = 0; y < h; y++) {
        DcuFlushRegion((u32 *)area_ptr, width_bytes);
        area_ptr += offset;
    }
}


bool lv_jl_gpu2p5d_check_draw_ctx_buf(uint8_t *buf)
{
    lv_disp_t *disp_refr = _lv_refr_get_disp_refreshing();

    if (disp_refr->driver->draw_buf == NULL) {
        return false;
    }

    /* 不是显存地址的绘制不启用 GPU，因为不知道目标 buf 的颜色格式， V8 暂时没法拿到， V9 有 img header */
    if ((buf == disp_refr->driver->draw_buf->buf1) || (buf == disp_refr->driver->draw_buf->buf2)) {
        return true;
    } else {
        //printf("Not real video memory");
        return false;
    }
}

//针对canvas的处理,用作在绘制动作中判断canvas的buf类型
lv_img_cf_t lv_jl_gpu2p5d_check_canvas_buf_format(lv_draw_ctx_t *draw_ctx)
{
#if LV_USE_USER_DATA
    if (draw_ctx->user_data) {
        lv_obj_t *obj  = (lv_obj_t *)draw_ctx->user_data;
        if (lv_obj_check_type(obj, &lv_canvas_class)) {
            lv_canvas_t *canvas = (lv_canvas_t *)obj;
            return canvas->dsc.header.cf;
        } else {
            return LV_IMG_CF_UNKNOWN;
        }
    }
#endif
    return LV_IMG_CF_UNKNOWN;
}
/**********************
 *   STATIC FUNCTIONS
 **********************/

#endif /*LV_USE_GPU_JL_GPU2P5D*/
