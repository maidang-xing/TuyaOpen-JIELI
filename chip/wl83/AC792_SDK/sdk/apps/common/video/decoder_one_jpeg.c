#include "asm/jpeg_codec.h"
#include "asm/hwi.h"
#include "system/includes.h"
#include "fs/fs.h"
#include "os/os_api.h"
#include "video_ioctl.h"
#include "video.h"
#include "yuv_to_rgb.h"
#include "yuv_soft_scalling.h"
#include "app_config.h"

#define JPEG_SAVE_FILE_YUV		1//测试解码保存格式:0 RGB656, 1 YUV
static void path_change_suf_name(char *name, const char *suf, const char *path)//在原始的名称下把后缀修改成suf的值
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

int decoder_one_jpeg(const char *path)//path:存在SD文件的jpeg图片
{
    FILE *fd = NULL;
    u32 lenth = 0;
    u8 *cy = NULL, *cb = NULL, *cr = NULL, *yuv = NULL, *rgb16 = NULL;
    u8 *buf = NULL;
    u32 pix = 0;
    u16 width, height;
    u8 ytype = 0;
    u32 len;
    char name[64];
    int err = 0;

    printf("open file : %s \n", path);

    //1.打开jpeg文件并读取jpeg数据到内存缓存区
    fd = fopen(path, "rb");
    if (fd == NULL) {
        printf("no file name : %s\n", path);
        goto exit;
    }
    lenth = flen(fd);//读取jpeg图片数据长度
    buf = malloc(lenth);
    if (!buf) {
        printf("buf malloc err ...\n");
        goto exit;
    }
    if (fread(buf, lenth, 1, fd) != lenth) {//读取jpeg图片数据
        printf("read file lenth err ...\n");
        goto exit;
    }
    fclose(fd);
    fd = NULL;

    jpeg_codec_init();
    //2.解析jpeg信息获取源JPEG YUV数据类型和分辨率
    struct jpeg_image_info info = {0};
    info.input.data.buf = buf;
    info.input.data.len = lenth;
    if (jpeg_decode_image_info(&info)) {
        printf("jpeg_decode_image_info err %s\n", path);
        goto exit;
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
    if (!yuv) {
        yuv = malloc(len);
        if (!yuv) {
            printf("yuv malloc err len : %d , width : %d , height : %d \n", width, height, len);
            goto exit;
        }
    }
#if !JPEG_SAVE_FILE_YUV
    if (!rgb16) { //使用YUV转RGB
        rgb16 = malloc(pix * 2);//rgb565总需要申请内存大小为:分辨率*2，rgb24为:分辨率*3
    }
#endif

    //4.配置解码相关参数
    cy = yuv;
    cb = cy + pix;
    cr = cb + pix / ytype;
    struct jpeg_decode_req req = {0};
    req.input_type = JPEG_INPUT_TYPE_DATA;
    req.input.data.buf = buf;
    req.input.data.len = lenth;
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
    if (err) {//非0，解码失败
        printf("jpeg_decode_one_image err \n");
        goto exit;
    }

    switch (ytype) {
    case 1:
#if JPEG_SAVE_FILE_YUV
        //YUV444p统一转YUV420
        YUV444pToYUV420p(yuv, yuv, width, height);
#else
        //YUV统一转rgb565
        if (rgb16) {
            yuv444p_quto_rgb565(yuv, rgb16, width, height, RGB565_BE);
        }
#endif
        break;//444
    case 4:
#if JPEG_SAVE_FILE_YUV
        //YUV420p统一转YUV420，次数数据源已经是YUV420，不用再转换
#else
        if (rgb16) {
            yuv420p_quto_rgb565(yuv, rgb16, width, height, RGB565_BE);
        }
#endif
        break;//420
    default:
#if JPEG_SAVE_FILE_YUV
        //YUV422p统一转YUV420
        YUV422pToYUV420p(yuv, yuv, width, height);
#else
        if (rgb16) {
            yuv422p_quto_rgb565(yuv, rgb16, width, height, RGB565_BE);
        }
#endif
        break;//422
    }

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

    //7.关闭文件和释放内存
exit:
    if (yuv) {
        free(yuv);
        yuv = NULL;
    }
    if (rgb16) {
        free(rgb16);
        rgb16 = NULL;
    }
    if (fd) {
        fclose(fd);
        fd = NULL;
    }
    return  0;
}
