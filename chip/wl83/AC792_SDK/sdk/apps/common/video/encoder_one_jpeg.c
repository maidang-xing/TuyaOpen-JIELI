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


//应用层使用YUV编码JPG API
//yuvdata:YUV或Y数据地址，yuvdata_size:数据长度
//jpg_buf:JPG图片编码预先存放数据缓存区,jpg_buf_size:JPG数据缓存区长度(30K-100K:<=320*240->30K,480*320->40K,640*480->50K,1280*720*90K)
//width/height:YUV/Y数据源的分辨率宽高, q_val:图片编码质量:0-13
//返回值:0失败,非0:JPG实际编码的图片数据长度(用户调用该函数后保存JPG数据为jpg_buf，长度为返回值)
int yuv_enc_jpeg(char *yuvdata, int yuvdata_size, char *jpg_buf, int jpg_buf_size, int width, int height, int q_val)
{
    struct jpeg_encode_req req = {0};
    int err = 0;
    char only_y = 0;
    char yuv_alloc = 0;
    char *yuv = yuvdata;

    if (yuvdata_size == width * height * 3) {
        req.format = JPG_SAMP_FMT_YUV444;
    } else if (yuvdata_size == width * height * 2) {
        req.format = JPG_SAMP_FMT_YUV422;
    } else {
        req.format = JPG_SAMP_FMT_YUV420;
        only_y = (yuvdata_size == width * height) ? 1 : 0;
        if (only_y) {
            yuv = malloc(width * height + width * height / 4);
            yuv_alloc = 1;
        }
    }
    if (!yuv) {
        printf("err yuv buf not enough\n");
        return 0;
    }
    req.q = q_val;
    req.data.buf = (u8 *)jpg_buf;
    req.data.len = jpg_buf_size;
    req.width =  width;
    req.height = height;
    req.y = (u8 *)yuv;
    req.u = req.y + req.width * req.height;
    req.v = req.u + req.width * req.height / 4;

#if JPEG_ENC_ONLY_Y
    only_y = 1;
#endif
    if (only_y) {
        if (yuv != yuvdata) {
            memcpy(yuv, yuvdata, width * height);
        }
        memset(yuv + width * height, 0x80, width * height / 4);
        req.v = req.u;
    }
    if (jpeg_encode_one_image(&req) == 0) {
        printf("jpeg_encode_one_image ok\n");
        err = req.data.len;
    } else {
        printf("jpeg_encode_one_image err\n");
    }
    if (yuv_alloc) {
        free(yuv);
    }
    return err;
}

void encoder_one_jpeg(const char *path, int width, int height)
{
    int err = 0;
    FILE *fd = NULL;
    int yuv_size;
    char name[64];
    int pix = width * height;
    int jpg_size = 100 * 1024;//指定分辨率编码的数据长度缓冲区(一般50K-100K，不够再加大)
    char *jpg_img = NULL;
    char *yuvbuf = NULL;
    fd = fopen(path, "rb");
    if (fd == NULL) {
        printf("no file name :%s \n", path);
        goto exit;
    }
    yuv_size = flen(fd);//读取jYUV数据长度
    yuvbuf = malloc(yuv_size);//申请YUV内存块
    if (!yuvbuf) {
        printf("yuvbuf malloc err ...\n");
        goto exit;
    }
    if (fread(yuvbuf, yuv_size, 1, fd) != yuv_size) {//读取YUV数据
        printf("read file yuv_size err ...\n");
        goto exit;
    }
    fclose(fd);
    fd = NULL;
    //4.申请编码的JPEG的内存缓冲区，一般50K-100K即可
    /* VGA图片大小说明：低等质量(小于20K)，中等质量(20K-40K)，高质量(大于40K，极限70K)
       720P图片大小说明：低等质量(小于50K)，中等质量(50k-100K)，高质量(大于100K，极限150K)
    */
    jpg_img = malloc(jpg_size);
    if (!jpg_img) {
        printf("jpg img malloc err!!!\n");
        goto exit;
    }
    memset(jpg_img, 0, jpg_size);

    jpeg_codec_init();
    err = yuv_enc_jpeg((char *)yuvbuf, yuv_size, (char *)jpg_img, jpg_size, width, height, 5);
    if (!err) {
        printf("jpeg_encode_one_image err \n\n");
        goto exit;
    }
    jpg_size = err;

    printf("jpeg_encode_one_image ok size = %dKb\n", jpg_size / 1024);

    //7.保存jpeg图片
    path_change_suf_name(name, "_***.jpg", path);
    fd = fopen(name, "w+");
    if (!fd) {
        printf("open file err :\n");
        goto exit;
    }
    fwrite(jpg_img, 1, jpg_size, fd);//保存jpeg图片
    printf("file write ok\n");

    //8.关闭文件和释放内存
exit:
    if (yuvbuf) {
        free(yuvbuf);
        yuvbuf = NULL;
    }
    if (jpg_img) {
        free(jpg_img);
        jpg_img = NULL;
    }
    if (fd) {
        fclose(fd);
        fd = NULL;
    }
    return;
}

