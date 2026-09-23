#if 1
//pipeline方式：virtual-h264_dec-replay-imc-display串联
//性能统计：
//分辨率320*240平均帧率：25fps
//分辨率640*480平均帧率：6fps
//分辨率1280*720平均帧率：2fps

#include "app_config.h"
#include "fs/fs.h"
#include "video_dec_server.h"
#include "video_dec.h"
#include "pipeline_core.h"

struct video_format f  = {0};

void on_event2(const char *name, int type, void *arg)
{
    OS_SEM *sem = (OS_SEM *)arg;
    switch (type) {

    case EVENT_FRAME_DONE:
        if (!strcmp("imagesink0", name)) {
            os_sem_post(sem);
        }
        break;

    case EVENT_PREPARE_DONE:
        printf("PREPARE %s done", name);
        break;

    case EVENT_START_DONE:
        printf("START %s done", name);
        break;

    case EVENT_STOP_DONE:
        printf("STOP %s done", name);
        break;
    case EVENT_RESET_DONE:
        printf("RESET %s done", name);
        break;
    case EVENT_BW_FULL:
    case EVENT_BUFFER_FULL:
    case EVENT_SPEED_FULL:
    case EVENT_OSD_ERR:
    case EVENT_LINE_ERR:
        printf("err %s ", name);
        break;
    }

}

int show_h264()
{
    FILE *fp, *fpidx;
    int dataLen, i, idxLen;
    unsigned char *dataSrc;
    int *idxData;
    struct video_cap_buffer buffer ;
    struct video_dev_fps fps = {0};
    pipe_filter_t *soft_h264_dec_filter, *imc_filter, *rep_filter, *disp_filter, *virtual_filter;
    int err = 0;
    OS_SEM sem;

    os_time_dly(100);
    while (!storage_device_ready()) {
        os_time_dly(10);
    }

    os_sem_create(&sem, 0);
    pipe_core_t *pipe_core = pipeline_init(on_event2, &sem);
    if (!pipe_core) {
        printf("%s   %d err", __func__, __LINE__);
        return -1;
    }
    printf("init OK!\n");

    char *source_name = plugin_factory_find("virtual");
    pipe_core->channel = plugin_source_to_channel(source_name);
    printf("source channel info: %s %d\n", source_name, pipe_core->channel);
    virtual_filter = pipeline_filter_add(pipe_core, source_name); //选择pipeline_core插件
    soft_h264_dec_filter = pipeline_filter_add(pipe_core, plugin_factory_find("soft_h264_dec0"));
    rep_filter = pipeline_filter_add(pipe_core, "rep0");
    imc_filter = pipeline_filter_add(pipe_core, plugin_factory_find("imc"));
    disp_filter = pipeline_filter_add(pipe_core, "disp2");
    printf("filter add OK!\n");

    f.type = VIDEO_BUF_TYPE_VIDEO_PLAY;
    f.pixelformat = VIDEO_PIX_FMT_H264 | VIDEO_PIX_FMT_YUV420; //设置H264转换成YUV
    f.src_width = 1280;  //原图像的宽高
    f.src_height = 720;
    f.win.width = 800;  //显示屏的宽高
    f.win.height = 480;
    f.private_data = "fb2";
    f.win.combine = 1;
    pipeline_param_set(pipe_core, NULL, PIPELINE_SET_FORMAT, (int)&f);

    int line_cnt = f.src_height;
    pipeline_param_set(pipe_core, NULL, PIPELINE_SET_BUFFER_LINE, (int)&line_cnt);
    printf("param set OK!\n");


    pipeline_filter_link(virtual_filter, soft_h264_dec_filter); //链接pipeline_core插件
    pipeline_filter_link(soft_h264_dec_filter, rep_filter);
    pipeline_filter_link(rep_filter, imc_filter);
    pipeline_filter_link(imc_filter, disp_filter);
    printf("filter link OK!\n");

    pipeline_prepare(pipe_core);
    pipeline_start(pipe_core);
    printf("pipeline start OK!\n");

    fpidx = fopen("storage/sd0/C/h264samples/dest.idx", "r");
    if (fpidx == NULL) {
        printf("open idx file fail\n");
        return -1;
    }

    idxLen = flen(fpidx);
    idxData = (int *)malloc(idxLen);
    fread((void *)idxData, 1, idxLen, fpidx);
    fclose(fpidx);
    printf("idx len = %d\n", idxLen);

    fp = fopen("storage/sd0/C/h264samples/dest.264", "r");
    if (fp == NULL) {
        printf("open dv file fail\n");
        return -1;
    }

    for (i = 0; i < idxLen / 4; i += 2) {
        dataLen = idxData[i + 1];
        printf("Decode frame %d datalen %d\n", i / 2, dataLen);
        dataSrc = (unsigned char *)malloc(dataLen);
        fread((void *)dataSrc, 1, dataLen, fp);
        buffer.size = dataLen;
        buffer.buf = dataSrc;
        pipeline_param_set(pipe_core, NULL, VIDIOC_RDBUF, (int)&buffer); //pipeline_core启动之后向里面写入H264视频数据
        free(dataSrc);
    }

    free(idxData);
    fclose(fp);
    printf("decode finish!\n");

    err = os_sem_pend(&sem, 400);
    if (err) {
        printf("image capture error\n");
        return -1;
    }

    pipeline_stop(pipe_core);
    pipeline_reset(pipe_core);
    pipeline_uninit(pipe_core);
}





#else
//读卡-解码-写卡方式
#include "stdio.h"
#include "../../lib/driver/cpu/wl83/video/hw/soft_h264_decode/tinyh264.h"
//#include "fs/fs.h"

storage_t *storage;

int show_h264()
{
    FILE *fp, *fpidx, *fpout, *fptmp;
    int dataLen, width, height, i, begintime, endtime, idxLen;
    unsigned char *dataSrc, *dest;
    int *idxData;

    while (!storage_device_ready()) {
        os_time_dly(10);
    }

    storage = h264bsdAlloc();
    if (h264bsdInit(storage, 0) == HANTRO_NOK) {
        printf("h.264 decode init fail\n");
        h264bsdFree(storage);
        return -1;
    }

    fpidx = fopen("storage/sd0/C/h264samples/dest.idx", "rb");
    if (fpidx == NULL) {
        printf("open idx file fail\n");
        h264bsdShutdown(storage);
        h264bsdFree(storage);
        return -1;
    }

    idxLen = flen(fpidx);
    idxData = (int *)malloc(idxLen);
    fread((void *)idxData, 1, idxLen, fpidx);
    fclose(fpidx);
    printf("idx len = %d\n", idxLen);

    fp = fopen("storage/sd0/C/h264samples/dest.264", "rb");
    if (fp == NULL) {
        printf("open dv file fail\n");
        h264bsdShutdown(storage);
        h264bsdFree(storage);
        return -1;
    }

    fpout = fopen("storage/sd0/C/h264samples/output.yuv", "wb");
    if (fpout == NULL) {
        printf("open save file fail\n");
        h264bsdShutdown(storage);
        h264bsdFree(storage);
        return -1;
    }

    printf("begin h264 decode!\n");
    for (i = 0; i < idxLen / 4; i += 2) {
        int decRes;
        dataLen = idxData[i + 1];
        printf("Decode frame %d datalen%d\n", i / 2, dataLen);
        dataSrc = (unsigned char *)malloc(dataLen);
        fread((void *)dataSrc, 1, dataLen, fp);
        fwrite(dataSrc, dataLen, 1, fptmp);
        fclose(fptmp);

        dest = NULL;
        printf("Decode frame %d\n", i / 2);
        begintime = timer_get_ms();
        decRes = h264bsdDecode(storage, dataSrc, dataLen, &dest, &width, &height);
        endtime = timer_get_ms();
        printf("Decode frame %d cost %dms %d,%d\n", i / 2, endtime - begintime, width, height);

        if (decRes == H264BSD_PIC_RDY) {
            int uSeg, vSeg;

            vSeg = width * height;
            uSeg = width * height * 5 / 4;

            fwrite(dest, width * height, 1, fpout);
            fwrite(dest + uSeg, width * height / 4, 1, fpout);
            fwrite(dest + vSeg, width * height / 4, 1, fpout);
        }

        free(dataSrc);
    }

    free(idxData);
    fclose(fp);
    fclose(fpout);
    h264bsdShutdown(storage);
    h264bsdFree(storage);

    return 0;

}

#endif

