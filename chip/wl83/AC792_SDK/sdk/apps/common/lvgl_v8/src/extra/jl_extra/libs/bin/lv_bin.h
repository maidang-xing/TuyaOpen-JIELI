/**
 * @file lv_bin.h
 *
 */


#ifndef LV_BIN_H
#define LV_BIN_H

#ifdef __cplusplus
extern "C" {
#endif

/*********************
 *      INCLUDES
 *********************/
#include "../lvgl.h"

/*********************
 *      DEFINES
 *********************/
extern const uint8_t flash_src_use_crc;
/**********************
 *      TYPEDEFS
 **********************/
/*******************JL************************/
typedef struct {
    uint8_t res_type;
    uint8_t res_compress;
    uint16_t res_crc;
    uint32_t res_size;
    uint32_t nop;
} JLBinResourceHeader;

typedef struct {
    char JL[2];
    uint16_t version;
    JLBinResourceHeader jl_header;
    void *resource;
} JLBinResource;

/**
 * 用作加载sd卡图片资源加速;
 * 调用tools/gen_info_file.py生成信息文件;
 * 信息文件结构:
 * uint32_t file_num;
 * lv_src_file_header_info_t;
 * lv_src_file_header_info_t;
 * ...
 */
typedef struct _header_info {
    char filename[16];//请勿改动，否则存在对齐问题
    JLBinResource jl_bin;
    lv_img_dsc_t img_dsc;
} lv_src_file_header_info_t;

/**
 * 检查并加载信息文件,存在则从信息文件中获取资源信息,请在加载ui前调用
 * info_file_name:信息文件路径
 */
lv_res_t lv_check_header_info_file(const char *info_file_name);
lv_res_t lv_close_header_info_file(void);

/**
 * 检查并加载UIPACKRES,存在则内部资源从UIPACKRES中解析
 * src:UIPACKRES路径
 * return:被打包文件个数+2
 */
uint16_t lv_load_pack_sdfile(const char *src);
/**
 * 通过资源路径在UIPACKRES中定位位置以及该资源长度
 * 为了兼容flash_src_use_malloc,约定资源路径都以's'开头即可,例如s/xxx.bin
 */
lv_res_t lv_sdfile_get_src_info(const char *src, uint32_t *pos, uint32_t *len);
/*******************JL************************/
/**********************
 * GLOBAL PROTOTYPES
 **********************/

/*JL获取.bin文件位图数据接口*/
//get lv_img_dsc_t结构体数据
lv_res_t lv_get_img_dsc_bin(const char *src, lv_img_dsc_t *bin_dsc);
lv_res_t lv_get_JLBinResource(const char *src, JLBinResource *bin_res);
lv_res_t lv_get_img_dsc_bin_header(const char *src, lv_img_header_t *header, JLBinResource *jl_resource);
lv_img_src_t lv_get_img_src_type(const char *src);
uint8_t lv_get_compress_type(const void *src);
u32 lv_get_flash_src_addr(const char *src);
lv_res_t lv_release_flash_src_addr(const char *src);
lv_res_t lv_release_all_flash_src_addr(void);
/**********************
 *      MACROS
 **********************/
extern const uint8_t flash_src_use_malloc;

#ifdef __cplusplus
} /*extern "C"*/
#endif

#endif /*LV_BIN_H*/

