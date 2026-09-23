#include "custom.h"
#if !LV_USE_GUIBUILDER_SIMULATOR
#include "app_core.h"
#include "app_config.h"
#include "ui.h"
#include "fs/fs.h"


#define JPEG_SAVE_FILE_YUV      0//测试解码保存格式:0 RGB656, 1 YUV
#define JPEG_ENC_ONLY_Y         0//编码JPEG只编灰色的Y
#define RGB565_BE               0//rgb565大小端:0小端,1端
int yuv_enc_image(char *yuvdata, int yuvdata_size, char *jpg_buf, int jpg_buf_size, int width, int height, int q_val);
int yuv_enc_large_image(char *yuvdata, int yuvdata_size, char *jpg_buf, int jpg_buf_size, int width, int height, int out_width, int out_height, u8 q_val);
// 在文件开头添加结构体定义

void path_change_suf_name(char *name, const char *suf, const char *path)//在原始的名称下把后缀修改成suf的值
{
    int len = strlen(path);
    char *find;
    int i  = len - 1;
    while (i >= 0) { //找出第一个'.'
        if (path[i] == '.') {
            break;
        }
        i--;
    }
    find = (char *)&path[i];
    if (i > 0) {
        memcpy(name, path, find - path);
        name[find - path] = 0;
        strcat(name, suf);
    }
}

// 采样计算平均颜色（为了速度，进行下采样）
static rgb_color_t calculate_average_color_rgb565(uint16_t *rgb565_data, uint16_t width, uint16_t height)
{
    uint32_t r_sum = 0, g_sum = 0, b_sum = 0;
    int sample_count = 0;

    // 采样间隔，可以根据需要调整，越大速度越快但精度越低
    const int sample_interval_x = 4;  // 每4个像素采样一次
    const int sample_interval_y = 4;  // 每4行采样一次

    // 边界限制，确保不会越界
    int max_y = height - 1;
    int max_x = width - 1;

    for (int y = 0; y <= max_y; y += sample_interval_y) {
        for (int x = 0; x <= max_x; x += sample_interval_x) {
            uint16_t pixel = rgb565_data[y * width + x];

            // RGB565 转 RGB888
            // RGB565: RRRRR GGGGGG BBBBB
            uint8_t r = ((pixel >> 11) & 0x1F) << 3;  // 5位转8位
            uint8_t g = ((pixel >> 5) & 0x3F) << 2;   // 6位转8位
            uint8_t b = (pixel & 0x1F) << 3;          // 5位转8位

            r_sum += r;
            g_sum += g;
            b_sum += b;
            sample_count++;
        }
    }

    rgb_color_t avg_color;
    if (sample_count > 0) {
        avg_color.r = r_sum / sample_count;
        avg_color.g = g_sum / sample_count;
        avg_color.b = b_sum / sample_count;
    } else {
        // 默认颜色
        avg_color.r = 0x80;
        avg_color.g = 0x80;
        avg_color.b = 0x80;
    }

    return avg_color;
}

// 可选：YUV直接计算平均颜色（更快，因为不需要RGB转换）
static rgb_color_t calculate_average_color_yuv(uint8_t *yuv_data, uint16_t width, uint16_t height, u8 ytype)
{
    uint32_t y_sum = 0, u_sum = 0, v_sum = 0;
    int sample_count = 0;
    const int sample_interval = 4;  // 采样间隔

    int max_y = height - 1;
    int max_x = width - 1;
    uint32_t pix = width * height;

    uint8_t *cy = yuv_data;
    uint8_t *cb = cy + pix;
    uint8_t *cr = cb + pix / ytype;

    for (int y = 0; y <= max_y; y += sample_interval) {
        for (int x = 0; x <= max_x; x += sample_interval) {
            int idx = y * width + x;
            y_sum += cy[idx];

            // 根据YUV格式计算UV索引
            int uv_idx;
            switch (ytype) {
            case 1:  // YUV444
                uv_idx = idx;
                break;
            case 2:  // YUV422
                uv_idx = (y * width + (x & ~1)) / 2;
                break;
            case 4:  // YUV420
                uv_idx = (y / 2) * (width / 2) + (x / 2);
                break;
            default:
                uv_idx = idx;
                break;
            }

            u_sum += cb[uv_idx];
            v_sum += cr[uv_idx];
            sample_count++;
        }
    }

    rgb_color_t avg_color;
    if (sample_count > 0) {
        // YUV 转 RGB（简化版）
        uint8_t y = y_sum / sample_count;
        uint8_t u = u_sum / sample_count;
        uint8_t v = v_sum / sample_count;

        // YUV to RGB 转换公式
        int r = y + 1.402 * (v - 128);
        int g = y - 0.344136 * (u - 128) - 0.714136 * (v - 128);
        int b = y + 1.772 * (u - 128);

        // 限制范围 0-255
        avg_color.r = (r < 0) ? 0 : (r > 255) ? 255 : r;
        avg_color.g = (g < 0) ? 0 : (g > 255) ? 255 : g;
        avg_color.b = (b < 0) ? 0 : (b > 255) ? 255 : b;
    } else {
        avg_color.r = 0x80;
        avg_color.g = 0x80;
        avg_color.b = 0x80;
    }

    return avg_color;
}

// 修改函数签名，添加颜色输出参数
int ui_action_jpeg_decoder(u8 **buf, u32 *length, rgb_color_t *avg_color, u16 *rgb_width, u16 *rgb_height)
{
    FILE *fd = NULL;
    u8 *cy = NULL, *cb = NULL, *cr = NULL, *yuv = NULL, *rgb16 = NULL;
    u32 pix = 0;
    u16 width, height;
    u8 ytype = 0;
    u32 len;
    int err = 0;

    if (!buf) {
        return -1;
    }

    if (avg_color) {
        // 初始化默认颜色
        avg_color->r = 0x80;
        avg_color->g = 0x80;
        avg_color->b = 0x80;
    }

    bip_file_mutex_lock();

    const uint8_t *jpg_buf = bip_file_path_get();
    u32 jpg_buf_len = bip_file_size_get();
    if (!jpg_buf || !jpg_buf_len || bip_file_status_get() != 1) {
        bip_file_mutex_unlock();
        return -1;
    }

    //2.解析jpeg信息获取源JPEG YUV数据类型和分辨率
    struct jpeg_image_info info = {0};
    info.input.data.buf = jpg_buf;
    info.input.data.len = jpg_buf_len;
    if (jpeg_decode_image_info(&info)) {
        bip_file_mutex_unlock();
        printf("jpeg_decode_image_info err");
        return -1;
    }

    width = info.width;
    height = info.height;
    pix = width * height;

    switch (info.sample_fmt) {
    case JPG_SAMP_FMT_YUV444:
        ytype = 1;
        printf("jpeg yuv444, pix : %dx%d \n", width, height);
        break;//444
    case JPG_SAMP_FMT_YUV420:
        ytype = 4;
        printf("jpeg yuv420, pix : %dx%d \n", width, height);
        break;//420
    default:
        ytype = 2;
        printf("jpeg yuv422, pix : %dx%d \n", width, height);
        break;//422
    }

    //3.申请YUV内存缓存
    len = pix + pix / ytype * 2;

    yuv = malloc(len);
    if (!yuv) {
        bip_file_mutex_unlock();
        printf("yuv malloc err len : %d , width : %d , height : %d \n", width, height, len);
        return -1;
    }

#if !JPEG_SAVE_FILE_YUV
    //使用YUV转RGB
    rgb16 = lv_mem_alloc(pix * 2);//rgb565总需要申请内存大小为:分辨率*2，rgb24为:分辨率*3
    if (!rgb16) {
        bip_file_mutex_unlock();
        free(yuv);
        return -1;
    }
#endif

    //4.配置解码相关参数
    cy = yuv;
    cb = cy + pix;
    cr = cb + pix / ytype;
    struct jpeg_decode_req req = {0};
    req.input_type = JPEG_INPUT_TYPE_DATA;
    req.input.data.buf = jpg_buf;
    req.input.data.len = jpg_buf_len;
    req.buf_y = cy;//配置Y地址
    req.buf_u = cb;//配置U地址
    req.buf_v = cr;//配置V地址
    req.buf_width = width;
    req.buf_height = height;
    req.out_width = width;
    req.out_height = height;
    req.output_type = JPEG_DECODE_TYPE_DEFAULT;
    req.bits_mode = BITS_MODE_UNCACHE;

    //5.启动jpeg图片解码
    err = jpeg_decode_one_image(&req, JPEG_DEV_ID_0);

    bip_file_mutex_unlock();

    if (err) {//非0，解码失败
        printf("jpeg_decode_one_image err \n");
        goto exit;
    }

    switch (ytype) {
    case 1:
#if JPEG_SAVE_FILE_YUV
        //YUV444p统一转YUV420
        YUV444pToYUV420p(yuv, yuv, width, height);
        // 计算平均颜色（从YUV）
        if (avg_color) {
            *avg_color = calculate_average_color_yuv(yuv, width, height, ytype);
        }
#else
        //YUV统一转rgb565
        if (rgb16) {
            yuv444p_quto_rgb565(yuv, rgb16, width, height, RGB565_BE);
            // 计算平均颜色（从RGB565）
            if (avg_color) {
                *avg_color = calculate_average_color_rgb565((uint16_t *)rgb16, width, height);
            }
        }
#endif
        break;//444
    case 4:
#if JPEG_SAVE_FILE_YUV
        //YUV420p统一转YUV420，次数数据源已经是YUV420，不用再转换
        if (avg_color) {
            *avg_color = calculate_average_color_yuv(yuv, width, height, ytype);
        }
#else
        if (rgb16) {
            yuv420p_quto_rgb565(yuv, rgb16, width, height, RGB565_BE);
            if (avg_color) {
                *avg_color = calculate_average_color_rgb565((uint16_t *)rgb16, width, height);
            }
        }
#endif
        break;//420
    default:
#if JPEG_SAVE_FILE_YUV
        //YUV422p统一转YUV420
        YUV422pToYUV420p(yuv, yuv, width, height);
        if (avg_color) {
            *avg_color = calculate_average_color_yuv(yuv, width, height, ytype);
        }
#else
        if (rgb16) {
            yuv422p_quto_rgb565(yuv, rgb16, width, height, RGB565_BE);
            if (avg_color) {
                *avg_color = calculate_average_color_rgb565((uint16_t *)rgb16, width, height);
            }
        }
#endif
        break;//422
    }

#if 0
    char name[64];
    //6.保存RGB/YUV文件
#if JPEG_SAVE_FILE_YUV
    path_change_suf_name(name, ".yuv", path);//源名字改后缀.yuv
    fd = fopen(name, "wb+");//可以自行指定保存的名字
    if (!fd) {
        printf("open file err : %s \n", name);
        goto exit;
    }
    fwrite(yuv, 1, pix * 3 / 2, fd);//YUV420p大小为:分辨率*1.5倍
#else
    path_change_suf_name(name, ".rgb", path);//源名字改后缀.rgb
    fd = fopen(name, "wb+");//可以自行指定保存的名字
    if (!fd) {
        printf("open file err : %s \n", name);
        goto exit;
    }
    fwrite(rgb16, 1, pix * 2, fd);//rgb565大小为:分辨率*2倍
#endif
    printf("file write ok\n");
#endif

    // 输出平均颜色信息
    if (avg_color) {
        printf("Average color: R=0x%02X, G=0x%02X, B=0x%02X\n",
               avg_color->r, avg_color->g, avg_color->b);
    }

    //7.关闭文件和释放内存
exit:
    if (yuv) {
        free(yuv);
    }
    *rgb_width = width;
    *rgb_height = height;
    *buf = rgb16;
    *length = pix * 2;
    return err;
}

#endif
