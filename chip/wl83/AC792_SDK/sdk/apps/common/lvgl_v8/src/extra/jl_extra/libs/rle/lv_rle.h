
/**
 * @file lv_rle.h
 *
 */

#ifndef LV_RLE_H_
#define LV_RLE_H_

#ifdef __cplusplus
extern "C" {
#endif

/*********************
 *      INCLUDES
 *********************/

/*********************
 *      DEFINES
 *********************/

/**********************
 *      TYPEDEFS
 **********************/
enum {
    ARGB8888 = 0,
    ARGB8565,
    ARGB1555,
    ARGB4444,
    RGB888,
    RGB565,
    AL88,
    AL44,
    L8,
    A8,
};

typedef struct rle_info {
    uint32_t width;
    uint32_t height;
    uint16_t format;    //可配置项
    // 0 : ARGB8888,
    // 1 : ARGB8565
    // 2 : ARGB1555
    // 3 : ARGB4444
    // 4 : RGB888
    // 5 : RGB565
    // 6 : BT601
    // 7 : BT709
    // 8 : AL88
    // 16 : AL44
    // 17 : AL22
    // 18 : L8
    // 19 : L4
    // 20 : L2
    // 21 : L1
    // 22 : A8
    // 23 : A4
    // 24 : A2
    // 25 : A1

    uint16_t block;  //可配置项
    // 0 : block_64x1
    // 1 : block_8x8
    // 2 : block_256x1
    // 3 : block_16x16

    uint16_t lut_format; //可配置项
    // 0 : ARGB8888
    // 1 : ARGB8565
    // 2 : RGB888
    // 3 : RGB565
    uint16_t nop; //可配置项

    uint32_t stride;		//图像每行像素字节
    uint32_t lut_addr;		//颜色表地址
    uint32_t lut_len;		//颜色表大小
    uint32_t addr;			//压缩数据地址
    uint32_t len;			//压缩数据长度
} rle_info_t;
/**********************
 * GLOBAL PROTOTYPES
 **********************/

void lv_rle_init(void);
void lv_gpu_rle_init(u8 use_gpu);
void test_rle_decompress(char *fg_filename);
uint16_t lv_get_rle_stride(rle_info_t *rle_info, uint8_t *adr_mode);
/**********************
 *      MACROS
 **********************/

#ifdef __cplusplus
}
#endif

#endif /* LV_RLE_H */
