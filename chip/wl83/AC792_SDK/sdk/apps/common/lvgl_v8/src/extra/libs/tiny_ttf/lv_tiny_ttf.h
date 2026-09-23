/**
 * @file lv_tiny_ttf.h
 *
 */

#ifndef LV_TINY_TTF_H
#define LV_TINY_TTF_H

#ifdef __cplusplus
extern "C" {
#endif

/*********************
 *      INCLUDES
 *********************/
#include "../../../lvgl.h"

#if LV_USE_TINY_TTF

#include "../../../misc/lv_lru.h"

#define SPECIFIED_CACHE_SIZE_MIN 65536  // lru 管理的用于暂存 bitmap 或 path 的最小缓冲空间大小(256 * 256)

#define STB_RECT_PACK_IMPLEMENTATION
#define STBRP_STATIC
#define STBTT_STATIC
#define STB_TRUETYPE_IMPLEMENTATION
#define STBTT_HEAP_FACTOR_SIZE_32 50
#define STBTT_HEAP_FACTOR_SIZE_128 20
#define STBTT_HEAP_FACTOR_SIZE_DEFAULT 10
#define STBTT_malloc(x, u) ((void)(u), lv_mem_alloc(x))
#define STBTT_free(x, u) ((void)(u), lv_mem_free(x))
#define TTF_MALLOC(x) (lv_mem_alloc(x))
#define TTF_FREE(x) (lv_mem_free(x))

/*********************
 *      DEFINES
 *********************/

#if LV_TINY_TTF_FILE_SUPPORT
/* a hydra stream that can be in memory or from a file*/
typedef struct ttf_cb_stream {
    lv_fs_file_t *file;
    const void *data;
    size_t size;
    size_t position;
} ttf_cb_stream_t;

void ttf_cb_stream_read(ttf_cb_stream_t *stream, void *data, size_t to_read);
void ttf_cb_stream_seek(ttf_cb_stream_t *stream, size_t position);

/* for stream support */
#define STBTT_STREAM_TYPE ttf_cb_stream_t *
#define STBTT_STREAM_SEEK(s, x) ttf_cb_stream_seek(s, x);
#define STBTT_STREAM_READ(s, x, y) ttf_cb_stream_read(s, x, y);
#endif /*LV_TINY_TTF_FILE_SUPPORT*/

/**********************
 *      TYPEDEFS
 **********************/

#include "stb_rect_pack.h"
#include "stb_truetype_htcw.h"

typedef struct ttf_font_desc {
    lv_fs_file_t file;
#if LV_TINY_TTF_FILE_SUPPORT
    ttf_cb_stream_t stream;
#else
    const uint8_t *stream;
#endif
    stbtt_fontinfo info;
    float scale;
    int ascent;
    int descent;
    lv_lru_t *bitmap_cache;
} ttf_font_desc_t;

typedef struct ttf_bitmap_cache_key {
    uint32_t unicode_letter;
    lv_coord_t line_height;
    bool is_path;  // 0 : bitmap; 1 : path
} ttf_bitmap_cache_key_t;

/**********************
 * GLOBAL PROTOTYPES
 **********************/

#if LV_TINY_TTF_FILE_SUPPORT
/* create a font from the specified file or path with the specified line height.*/
lv_font_t *lv_tiny_ttf_create_file(const char *path, lv_coord_t font_size);

/* create a font from the specified file or path with the specified line height with the specified cache size.*/
lv_font_t *lv_tiny_ttf_create_file_ex(const char *path, lv_coord_t font_size, size_t cache_size);
#endif /*LV_TINY_TTF_FILE_SUPPORT*/

/* create a font from the specified data pointer with the specified line height.*/
lv_font_t *lv_tiny_ttf_create_data(const void *data, size_t data_size, lv_coord_t font_size);

/* create a font from the specified data pointer with the specified line height and the specified cache size.*/
lv_font_t *lv_tiny_ttf_create_data_ex(const void *data, size_t data_size, lv_coord_t font_size, size_t cache_size);

/* set the size of the font to a new font_size*/
void lv_tiny_ttf_set_size(lv_font_t *font, lv_coord_t font_size);

/* destroy a font previously created with lv_tiny_ttf_create_xxxx()*/
void lv_tiny_ttf_destroy(lv_font_t *font);

/**********************
 *      MACROS
 **********************/

#endif /*LV_USE_TINY_TTF*/

#ifdef __cplusplus
} /*extern "C"*/
#endif

#endif /*LV_TINY_TTF_H*/
