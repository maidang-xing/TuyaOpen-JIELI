#include "app_config.h"
#include "fs/fs.h"
#include "video_dec_server.h"
#include "video_dec.h"
#include "asm/jpeg_codec.h"
#include "pipeline_core.h"
#include "video_dec.h"

char jpeg_src[400 * 1024];
struct video_device dev1;
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

int show_jpeg()
{

    pipe_filter_t *jpeg_dec_filter, *imc_filter, *rep_filter, *disp_filter, *virtual_filter;
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


    char *source_name = plugin_factory_find("virtual");
    pipe_core->channel = plugin_source_to_channel(source_name);
    virtual_filter = pipeline_filter_add(pipe_core, source_name); //选择pipeline_core插件
    jpeg_dec_filter = pipeline_filter_add(pipe_core, plugin_factory_find("jpeg_dec"));
    rep_filter = pipeline_filter_add(pipe_core, "rep0");
    imc_filter = pipeline_filter_add(pipe_core, plugin_factory_find("imc"));
    disp_filter = pipeline_filter_add(pipe_core, "disp2");


    f.type = VIDEO_BUF_TYPE_VIDEO_PLAY;
    f.pixelformat = VIDEO_PIX_FMT_JPEG | VIDEO_PIX_FMT_YUV420; //设置图片转换成
    f.src_width = 1920;  //原图片的宽高
    f.src_height = 1088;
    f.win.width = 480;  //显示屏的宽高
    f.win.height = 272;
    f.private_data = "fb2";
    pipeline_param_set(pipe_core, NULL, PIPELINE_SET_FORMAT, &f);


    int line_cnt = 16;
    pipeline_param_set(pipe_core, NULL, PIPELINE_SET_BUFFER_LINE, (int)&line_cnt);


    pipeline_filter_link(virtual_filter, jpeg_dec_filter); //链接pipeline_core插件
    pipeline_filter_link(jpeg_dec_filter, rep_filter);
    pipeline_filter_link(rep_filter, imc_filter);
    pipeline_filter_link(imc_filter, disp_filter);
    pipeline_prepare(pipe_core);
    pipeline_start(pipe_core);


    int j = 0;
    while (1) {
        FILE *fd = NULL;
        if (j == 0) {
            fd = fopen("storage/sd0/C/DCIM/1/jpeg00001.jpg", "r");
            if (fd != NULL) {
                printf("open file success\n");
            } else {
                printf("open file fail\n");
                return -1;
            }
            int jpeg_len = fread(jpeg_src, 400 * 1024, 1, fd);
            struct video_cap_buffer buffer ;
            buffer.size = jpeg_len;
            buffer.buf = jpeg_src;
            pipeline_param_set(pipe_core, NULL, VIDIOC_RDBUF, &buffer); //pipeline_core启动之后向里面写入JPEG图片数据

        } else if (j == 1) {
            fd = fopen("storage/sd0/C/DCIM/1/jpeg00002.jpg", "r");
            if (fd != NULL) {
                printf("open file success\n");
            } else {
                printf("open file fail\n");
                return -1;
            }
            int jpeg_len = fread(jpeg_src, 400 * 1024, 1, fd);
            struct video_cap_buffer buffer ;
            buffer.size = jpeg_len;
            buffer.buf = jpeg_src;
            pipeline_param_set(pipe_core, NULL, VIDIOC_RDBUF, &buffer);

        } else if (j == 2) {
            fd = fopen("storage/sd0/C/DCIM/1/jpeg00003.jpg", "r");
            if (fd != NULL) {
                printf("open file success\n");
            } else {
                printf("open file fail\n");
                return -1;
            }
            int jpeg_len = fread(jpeg_src, 400 * 1024, 1, fd);
            struct video_cap_buffer buffer ;
            buffer.size = jpeg_len;
            buffer.buf = jpeg_src;
            pipeline_param_set(pipe_core, NULL, VIDIOC_RDBUF, &buffer);

        }

        fclose(fd);

        if (j < 2) {
            j++;
        } else if (j >= 2) {
            j = 0;
        }

        os_time_dly(100);
    }

    err = os_sem_pend(&sem, 400);
    if (err) {
        printf("image capture error\n");
        return -1;
    }

    pipeline_stop(pipe_core);
    pipeline_reset(pipe_core);
    pipeline_uninit(pipe_core);


}
