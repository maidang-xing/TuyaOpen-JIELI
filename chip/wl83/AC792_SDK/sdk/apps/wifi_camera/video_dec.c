#include "app_config.h"
#include "system/includes.h"
#include "server/video_server.h"
#include "server/video_dec_server.h"
#include "video_dec.h"
#include "key_event.h"
#include "device_event.h"
#include "action.h"
#include "lcd_config.h"

#define AUDIO_DEC_BUF_SIZE  64 * 1024

#if __SDRAM_SIZE__ == (16 * 1024 * 1024)
#define VIDEO_DEC_BUF_SIZE  1 * 1024 * 1024 + 512 * 1024
#else
#define VIDEO_DEC_BUF_SIZE  512 * 1024
#endif

#define DEFAULT_PLAY_VOLUME 100

#ifdef CONFIG_EMR_DIR_ENABLE
const char *dec_path[DEC_PATH_NUM][2] = {
    { CONFIG_DEC_PATH_1, "-tMOVJPGAVI -st -r" },
    { CONFIG_DEC_PATH_2, "-tMOVJPGAVI -st -r" },
#if (DEC_PATH_NUM == 3)
    { CONFIG_DEC_PATH_3, "-tMOVJPGAVI -st -r" },
#endif
};
#else
const char *dec_path[DEC_PATH_NUM][2] = {
    { CONFIG_DEC_PATH_1, "-tMOVJPGAVI -sn" },
    { CONFIG_DEC_PATH_2, "-tMOVJPGAVI -sn" },
#if (DEC_PATH_NUM == 3)
    { CONFIG_DEC_PATH_3, "-tMOVJPGAVI -sn" },
#endif
};
#endif

extern int video_dec_change_status(struct video_dec_hdl *, struct intent *it);
extern int video_dec_set_config(struct video_dec_hdl *, struct intent *it);
extern int video_dec_get_config(struct intent *it);

struct video_dec_hdl dec_handler;

#define __this 	(&dec_handler)

//通过预打开fb显存,切换文件时不关闭
//解决切换文件时屏幕会黑一下问题
#define VIDEO_DEC_FB_PREV_OPEN  0

/*
 * 发送一些状态给ui
 */
_WEAK_ void video_dec_post_msg(const char *msg, ...)
{
}
char *video_dec_get_file_name(void)
{
    return __this->fname;

}

u32 video_dec_get_file_toltime(void)
{
    return __this->req.dec.info.total_time;
}

void *video_dec_get_file_fd(void)
{
    return __this->req.dec.file;
}

/*
 * 发送文件的信息给LVGL ui显示
 */
void video_dec_post_file_info_to_ui(int fname_len, int format)
{
#ifdef CONFIG_UI_ENABLE
    int attr;
    int attr_ro = 0;

    /*
     *发送文件名信息，如果文件名长度超过12byte，则为utf16编码格式
     */
    if (fname_len) {
        if (format == 0) {
            ASCII_ToUpper(__this->fname, fname_len);
            video_dec_post_msg("fname:ascii=%p", __this->fname);
        } else {
            video_dec_post_msg("fname:utf16=%p", __this->fname);
        }
    }

    /*
     * 获取文件属性，看是否为写保护文件
     */
    fget_attr(__this->req.dec.file, &attr);
    /*video_dec_post_msg("fattr:ro=%1", !!(attr & F_ATTR_RO));*/
    attr_ro = attr & F_ATTR_RO;

    /*
     * 发送分辨率和影片时长信息
     */
#ifdef CONFIG_FILE_PREVIEW_ENABLE
    video_dec_post_msg("fileInfo", 0);
#else
    video_dec_post_msg("fileInfo",
                       __this->req.dec.info.total_time,
                       __this->req.dec.info.width,
                       __this->req.dec.info.height,
                       __this->file_type, attr_ro);
#endif
    /*video_dec_post_msg("res:w=%2 h=%2,filmLen:s=%4", __this->req.dec.info.width,*/
    /*__this->req.dec.info.height, __this->req.dec.info.total_time);*/


    /*
     * 发送当前解码状态信息
     */
    if (__this->file_type == FILE_TYPE_MOVE) {
        if (__this->status == VIDEO_DEC_PAUSE) {
            sys_power_auto_shutdown_resume();
            video_dec_post_msg("pause");
        } else if (__this->status == VIDEO_DEC_PLAYING) {
            sys_power_auto_shutdown_pause();
            video_dec_post_msg("play");
        }
    } else {
        sys_power_auto_shutdown_resume();
    }


#endif
}


/*
 * 打开文件并启动解码
 */
int video_dec_file(int mode)
{
    int err;
    struct vfscan *fs = __this->fs[__this->curr_dir];
    struct imc_presca_ctl pctl;

    if (!__this->video_dec) {
        return -EFAULT;
    }

    if (!fs) {
        video_dec_post_msg("noFile");
        return -ENOENT;
    }

    if (__this->req.dec.file) {
        server_request(__this->video_dec, VIDEO_REQ_DEC_STOP, &__this->req);
        fclose(__this->req.dec.file);
    }

    /*
     * 选择并打开一个文件, 如果fselect返回成功，则此文件不用时需要调用fclose关闭
     */
    __this->req.dec.file = fselect(fs, mode, 0);
    if (!__this->req.dec.file) {
        /*
         *目录内循环播放
         */
        if (mode == FSEL_NEXT_FILE) {
            __this->req.dec.file = fselect(fs, FSEL_FIRST_FILE, 0);
        } else if (mode == FSEL_PREV_FILE) {
            __this->req.dec.file = fselect(fs, FSEL_LAST_FILE, 0);
        }
        if (!__this->req.dec.file) {
            video_dec_post_msg("noFile");
            fscan_release(__this->fs[__this->curr_dir]);
            __this->fs[__this->curr_dir] = NULL;
            return -ENOENT;
        }
    }

    pctl.presca_en = 1;
    pctl.gs_parma = 0;
    pctl.gs_parmb = 0;
    pctl.gs_parmc = 0;
    pctl.gs_parmd = 0;
    __this->req.dec.pctl = NULL;//&pctl;



#ifdef DISP_IMAGE_AND_VIDEO
    test_disp_stop();
#endif

    /*
     * 启动解码
     */
    err = server_request(__this->video_dec, VIDEO_REQ_DEC_START, &__this->req);
    if (err) {
        video_dec_post_msg("fileErr");
        /*
         * 遇到坏损文件无法播放时, 等待1s后播放下一个文件,
         * 如果此处时间设置过短且坏损文件过多时可能造成无法响应按键消息
         */
        if (mode == FSEL_FIRST_FILE) {
            mode = FSEL_NEXT_FILE;
        } else if (mode == FSEL_LAST_FILE) {
            mode = FSEL_PREV_FILE;
        }
        if (__this->status != VIDEO_DEC_STOP) {
            __this->timeout = sys_timeout_add((void *)mode, (void(*)(void *))video_dec_file, 1000);
        }
    } else {
        if (__this->req.dec.preview) {
            __this->status = VIDEO_DEC_PAUSE;
        } else {
            __this->status = VIDEO_DEC_PLAYING;
        }
        sys_power_auto_shutdown_pause();

    }

    int format = 0;
    int len = fget_name(__this->req.dec.file, __this->fname, MAX_FILE_NAME_LEN);
    if (len) {
        if (!ASCII_StrCmpNoCase((char *)(__this->fname + len - 3), "JPG", 3)) {
            __this->file_type = FILE_TYPE_JPG;
        } else {
            __this->file_type = FILE_TYPE_MOVE;
        }
    }

    video_dec_post_file_info_to_ui(len, format);

#ifdef DISP_IMAGE_AND_VIDEO
    if ((err == 0) && (__this->file_type == FILE_TYPE_JPG)) {
        test_disp_start();
    }
#endif

    return err;
}

/*
 * 文件夹扫描
 */
void video_dec_scan_dir()
{
    int curr_dir;

    if (__this->curr_dir >= DEC_PATH_NUM) {
        __this->curr_dir = 0;
    } else if (__this->curr_dir < 0) {
        __this->curr_dir = DEC_PATH_NUM - 1;
    }

    curr_dir = __this->curr_dir;

    if (!__this->video_dec) {
        return;
    }

    while (1) {
        if (!__this->fs[__this->curr_dir]) {
            __this->fs[__this->curr_dir] = fscan(dec_path[__this->curr_dir][0],
                                                 dec_path[__this->curr_dir][1], 9);
        }
        if (__this->fs[__this->curr_dir]) {
            break;
        }
        if (++__this->curr_dir == DEC_PATH_NUM) {
            __this->curr_dir = 0;
        }
        if (__this->curr_dir == curr_dir) {
            break;
        }
    }

    video_dec_file(FSEL_LAST_FILE);
}

/*
 * video_decoder server的事件回调函数
 */
static void dec_server_event_handler(void *priv, int argc, int *argv)
{
    switch (argv[0]) {
    case VIDEO_DEC_EVENT_CURR_TIME:
        /*
         *发送当前播放时间给UI
         */
        video_dec_post_msg("plyTime:s=%4", argv[1]);
        break;
    case VIDEO_DEC_EVENT_END:
#ifdef CONFIG_FILE_PREVIEW_ENABLE
        /*
         *解码结束，播放当前文件
         */
        video_dec_post_msg("end");
        if (__this->req.dec.file) {
            server_request(__this->video_dec, VIDEO_REQ_DEC_STOP, &__this->req);
            fseek(__this->req.dec.file, 0, SEEK_SET);
        }
        dec_open_file();

#else
        /*
         *解码结束，播放前一个文件
         */
        video_dec_file(FSEL_PREV_FILE);
#endif
        break;
    case VIDEO_DEC_EVENT_ERR:
        /*
         *解码出错，如果存储设备没有被拔出则播放前一个文件
         */
        if (fdir_exist(CONFIG_STORAGE_PATH)) {
            video_dec_file(FSEL_PREV_FILE);
        }
        break;
    }
}


/*
 *sd卡挂载成功后会调用此函数
 */
static int video_dec_start(void *p)
{
    __this->wait = 0;

    /*
     * 打开video_dec_server, 注册事件回调函数
     */
    if (!__this->video_dec) {
        struct video_dec_arg arg = {0};

        arg.dev_name = "video_dec";
        arg.audio_buf_size = AUDIO_DEC_BUF_SIZE;
        arg.video_buf_size = VIDEO_DEC_BUF_SIZE;

        __this->video_dec = server_open("video_dec_server", &arg);
        if (!__this->video_dec) {
            video_dec_post_msg("hwErr");
            return -EFAULT;
        }
        server_register_event_handler(__this->video_dec, NULL, dec_server_event_handler);
    }

    __this->req.dec.fb 		= "fb1";
    /*
     * 下面4个参数为解码出来的视频在屏幕上的起始坐标和长宽, 长宽配0即为显示屏大小
     */
    __this->req.dec.left 	= 0;
    __this->req.dec.top 	= 0;
    __this->req.dec.width 	= LCD_W;
    __this->req.dec.height 	= LCD_H;

    /*
     * jpeg图片优先解缩略图标志
     */
    __this->req.dec.thm_first = 0;

    /*
      * 是否预览，设0即为自动播放
      */
    __this->req.dec.preview = 1;

    __this->req.dec.volume = __this->volume;
    __this->curr_dir = 0;
    video_dec_scan_dir();

#if VIDEO_DEC_FB_PREV_OPEN
    video_dec_fb_prev_open();
#endif
    return 0;
}

/*
 * 播放和暂停控制
 */
int video_dec_play_pause()
{
    int err;

    if (__this->file_type != FILE_TYPE_MOVE) {
        return 0;
    }

    if (!__this->video_dec) {
        return -EFAULT;
    }

    if (!__this->req.dec.file) {
        return -ENOENT;
    }

    err = server_request(__this->video_dec, VIDEO_REQ_DEC_PLAY_PAUSE, &__this->req);
    if (err) {
        return -EFAULT;
    }

    if (__this->status != VIDEO_DEC_PLAYING) {
        __this->status = VIDEO_DEC_PLAYING;
        sys_power_auto_shutdown_pause();
        video_dec_post_msg("play");
    } else {
        __this->status = VIDEO_DEC_PAUSE;
        sys_power_auto_shutdown_resume();
        video_dec_post_msg("pause");
    }

    if (__this->timeout) {
        sys_timeout_del(__this->timeout);
        __this->timeout = 0;
    }

    return 0;
}

/*
 * 快进快退
 */
int video_dec_ff_fr(int ff_fr_req)
{
    int err;
    union video_dec_req req;

    if (!__this->video_dec) {
        return -EFAULT;
    }

    if (!__this->req.dec.file) {
        return -ENOENT;
    }

    __this->ff_fr_times <<= 1;
    if (__this->ff_fr_times > 8) {
        __this->ff_fr_times = 2;
    }

    /*
     * on = true:开始快进/快退, on = false:停止快进/快退
     * times: 快进/快退的倍数, once = false时有效
     * once:  一次快进/快退，和msec_step配合，用于直接快进/快退到某个时间点
     */
    req.f.on = true;
    req.f.once = false;
    req.f.msec_step = 0;
    req.f.times = __this->ff_fr_times;
    err = server_request(__this->video_dec, ff_fr_req, &req);
    if (err) {
        return -EFAULT;
    }

    if (ff_fr_req == VIDEO_REQ_DEC_FF) {
        video_dec_post_msg("ff:t=%1", __this->ff_fr_times);
        __this->status = VIDEO_DEC_FF;
    } else {
        video_dec_post_msg("fr:t=%1", __this->ff_fr_times);
        __this->status = VIDEO_DEC_FR;
    }
    sys_power_auto_shutdown_pause();

    return 0;
}

/*
 * 停止解码
 */
int video_dec_stop(int release)
{
    int i;

    /*
     * 释放文件扫描的资源
     */
    if (release) {
        for (i = 0; i < DEC_PATH_NUM; i++) {
            if (__this->fs[i]) {
                fscan_release(__this->fs[i]);
                __this->fs[i] = NULL;
            }
        }
    }

    __this->status = VIDEO_DEC_STOP;

    if (!__this->video_dec) {
        return 0;
    }

    if (__this->req.dec.file) {
        server_request(__this->video_dec, VIDEO_REQ_DEC_STOP, &__this->req);
        fclose(__this->req.dec.file);
        __this->req.dec.file = NULL;
    }

    if (__this->timeout) {
        sys_timeout_del(__this->timeout);
        __this->timeout = 0;
    }
    sys_power_auto_shutdown_resume();

    return 0;
}

static int video_dec_get_frame(void)
{
    int err;
    FILE *fp = NULL;
    u8 *img_buf = NULL;
    u32 img_size = 100 * 1024;
    union video_dec_req req = {0};
    char path[64];
    sprintf(path, "%simg_***.jpg", __this->cur_path);

    if (__this->file_type != FILE_TYPE_MOVE || __this->status != VIDEO_DEC_PLAYING) {
        return 0;
    }

    img_buf = malloc(img_size);
    if (!img_buf) {
        log_e("img_buf malloc err");
        goto exit;
    }

    if (__this->video_dec) {
        req.dec.dec_frame_buf = img_buf;
        req.dec.dec_frame_size = img_size;
        err = server_request(__this->video_dec, VIDEO_REQ_DEC_GET_FRAME, &req);
        if (!err) {
            fp = fopen(path, "wb+");
            if (!fp) {
                log_e("fopen fail");
                goto exit;
            }
            if (fwrite(req.dec.dec_frame_buf, req.dec.dec_frame_size, 1, fp) != req.dec.dec_frame_size) {
                log_e("img fwrite err");
                goto exit;
            }
        } else {
            log_w("video dec get frame fail");
        }
    }

exit:
    if (img_buf) {
        free(img_buf);
        img_buf = NULL;
    }
    if (fp) {
        fclose(fp);
        fp = NULL;
    }
    return err;
}

static int video_dec_set_audio_volume(u8 volume)
{
    int err = -1;
    __this->req.dec.volume = volume;
    if (__this->video_dec) {
        err = server_request(__this->video_dec, VIDEO_REQ_DEC_SET_AUDIO_VOLUME, &__this->req);
    }

    return err;
}

static int video_dec_switch_audio_volume(void)
{
    if (__this->file_type != FILE_TYPE_MOVE) {
        return 0;
    }

    __this->req.dec.volume = __this->req.dec.volume ? 0 : 100;
    __this->volume = __this->req.dec.volume;
    return video_dec_set_audio_volume(__this->req.dec.volume);
}


static int video_dec_set_speed(float speed)
{
    log_i("video_dec set play speed:%.1f", speed);
    union video_dec_req req = {0};
    req.dec.speed = speed;
    server_request(__this->video_dec, VIDEO_REQ_DEC_SET_PLAY_SPEED, &req);

    return 0;
}

//TODO
//SEEK到文件头部开始播放
static int video_dec_set_seek(void)
{
    union video_dec_req req = {0};

    server_request(__this->video_dec, VIDEO_REQ_DEC_SET_SEEK, &req);
    return 0;
}

#ifdef CONFIG_FILE_PREVIEW_ENABLE
int dec_open_file()
{
    int err;
    int attr;
    int format = 0;

    if (!__this->video_dec) {
        struct video_dec_arg arg = {0};

        arg.dev_name = "video_dec";
        arg.audio_buf_size = AUDIO_DEC_BUF_SIZE;
        arg.video_buf_size = VIDEO_DEC_BUF_SIZE;

        __this->video_dec = server_open("video_dec_server", &arg);
        if (!__this->video_dec) {
            video_dec_post_msg("hwErr");
            return -EFAULT;
        }
        server_register_event_handler(__this->video_dec, NULL, dec_server_event_handler);
    }

    if (!__this->req.dec.file) {
        server_close(__this->video_dec);
        __this->video_dec = NULL;
        video_dec_post_msg("noFile");
        return -ENOENT;
    }

    __this->req.dec.fb 		= "fb1";
    /*
     * 下面4个参数为解码出来的视频在屏幕上的起始坐标和长宽, 长宽配0即为显示屏大小
     */
    __this->req.dec.left 	= 0;
    __this->req.dec.top 	= 0;
    __this->req.dec.width 	= LCD_W;
    __this->req.dec.height 	= LCD_H;

    //优先解缩略图
    __this->req.dec.thm_first = 0;

    /*
     * 是否预览，设0即为自动播放
     */
    __this->req.dec.preview = 1;
    __this->req.dec.volume = __this->volume;

    __this->req.dec.pctl = NULL;

    int len = fget_name(__this->req.dec.file, __this->fname, MAX_FILE_NAME_LEN);
    /*
     * 启动解码
     */
    err = server_request(__this->video_dec, VIDEO_REQ_DEC_START, &__this->req);
    if (err) {
        video_dec_post_msg("fileErr");

    } else {
        if (__this->req.dec.preview) {
            __this->status = VIDEO_DEC_PAUSE;
        } else {
            __this->status = VIDEO_DEC_PLAYING;
        }
        /* sys_power_auto_shutdown_pause(); */
        if (len) {
            if (!ASCII_StrCmpNoCase((char *)(__this->fname + len - 3), "JPG", 3)) {
                __this->file_type = FILE_TYPE_JPG;
            } else {
                __this->file_type = FILE_TYPE_MOVE;
            }

            /*
             *发送文件名信息，如果文件名长度超过12byte，则为utf16编码格式
             */
            if (format == 0) {
                ASCII_ToUpper(__this->fname, len);
                video_dec_post_msg("fname:ascii=%p", __this->fname);
            } else {
                video_dec_post_msg("fname:utf16=%p", __this->fname);
            }
        }
    }
    /*
     * 发送分辨率和影片时长信息
     */
    video_dec_post_msg("fileInfo", 0);
    /*video_dec_post_msg("res:w=%2 h=%2,filmLen:s=%4", __this->req.dec.info.width,*/
    /*__this->req.dec.info.height, __this->req.dec.info.total_time);*/

    /*
     * 发送当前解码状态信息
     */
    if (__this->file_type == FILE_TYPE_MOVE) {
        if (__this->status == VIDEO_DEC_PAUSE) {
            sys_power_auto_shutdown_resume();
            video_dec_post_msg("pause");
        } else if (__this->status == VIDEO_DEC_PLAYING) {
            sys_power_auto_shutdown_pause();
            video_dec_post_msg("play");
        }
    }

#if VIDEO_DEC_FB_PREV_OPEN
    video_dec_fb_prev_open();
#endif
    return err;
}
#endif

int ui_video_dir(char *dir_path)
{
    if (!dir_path) {
        return -1;
    }
    int attr;
    char file_name[128];
    FILE *file;
    struct vfscan *fs = NULL;
    dec_path[__this->curr_dir][0] = dir_path;
    log_d("cur_path = %s", dec_path[__this->curr_dir][0]);
    fs = fscan(dec_path[__this->curr_dir][0], dec_path[__this->curr_dir][1], 9);

    if (!fs || fs->file_number == 0) {
        log_e("fscan err");
        return -1;
    }
    file = fselect(fs, FSEL_FIRST_FILE, 0);
    while (file) {
        int len = fget_name(file, file_name, MAX_FILE_NAME_LEN);
        if (strcmp(file_name, __this->fname) == 0) {
            //更新当前句柄
            __this->fs[__this->curr_dir]  = fs;
            fclose((FILE *)file);
            return 0;
        }
        fclose((FILE *)file);

        file = fselect(fs, FSEL_NEXT_FILE, 0);
    }

    fscan_release(fs);
    return 0;
}

static int video_dec_fb_prev_open(void)
{
    printf("server req fb prev open \n");
    if (!__this->video_dec) {
        printf("err !! video_dec server is NULL \n");
        return -1;
    }

    return server_request(__this->video_dec, VIDEO_REQ_DEC_FB_PREV_OPEN, &__this->req);
}

static int video_dec_fb_prev_close(void)
{
    printf("server req fb prev close \n");
    if (!__this->video_dec) {
        printf("err !! video_dec server is NULL");
        return -1;

    }
    return server_request(__this->video_dec, VIDEO_REQ_DEC_FB_PREV_CLOSE, &__this->req);
}



/*
 * 解码任务的状态机函数，由start_app负责调用
 */
static int state_machine(struct application *app, enum app_state state, struct intent *it)
{
    int ret = 0;
    int err = 0;

    switch (state) {
    case APP_STA_CREATE:
        log_d("\n>>>>>>> video_dec: create\n");
        memset(__this, 0, sizeof(struct video_dec_hdl));
        __this->volume = DEFAULT_PLAY_VOLUME;
#if 0 //def CONFIG_UI_ENABLE
        /*
         *打开UI服务，请求显示界面
         */
        union uireq req;
#ifdef MULTI_LCD_EN
        struct ui_style style = {0};
        if (get_current_disp_device()) {
            style.file = "mnt/spiflash/res/avo_LY.sty\0";
        } else {
            style.file = "mnt/spiflash/res/lcd_LY.sty\0";
        }
        __this->ui = server_open("ui_server", &style);
#else
        __this->ui = server_open("ui_server", NULL);
#endif

        if (__this->ui) {
            req.show.id = ID_WINDOW_VIDEO_REP;
            server_request_async(__this->ui, UI_REQ_SHOW, &req);
        }
#endif
        break;
    case APP_STA_START:
        switch (it->action) {
        case ACTION_VIDEO_DEC_MAIN:
#ifndef CONFIG_FILE_PREVIEW_ENABLE
            /*
             *等待存储设备(sd卡)挂载完成，然后自动调用video_dec_start
             */
            __this->wait = wait_completion(storage_device_ready, video_dec_start, NULL, NULL);
#endif
            break;
        case ACTION_VIDEO_DEC_CHANGE_STATUS:
            ret = video_dec_change_status(__this, it);
            break;
        case ACTION_VIDEO_DEC_SET_CONFIG:
            /*if (!__this->ui) {*/
            /*return -EINVAL;*/
            /*}*/
            /* #ifdef CONFIG_UI_STYLE_JL02_ENABLE */
            /* ret = dec_set_config(__this, it); */
            /* #else */
            ret = video_dec_set_config(__this, it);
            /* #endif */
            break;
#ifdef CONFIG_FILE_PREVIEW_ENABLE
        case ACTION_VIDEO_DEC_OPEN_FILE:
            if (!__this->req.dec.file) {
                __this->req.dec.file = (FILE *)it->data;
            }
            strcpy(__this->cur_path, (char *)it->exdata);
            dec_open_file();
            break;
        case ACTION_VIDEO_PREV_NEXT_CONTROL:
            //切换上下首
            if (__this->status  == VIDEO_DEC_PLAYING
                || __this->status  == VIDEO_DEC_FF
                || __this->status  == VIDEO_DEC_FR) {
                if (__this->status  == VIDEO_DEC_FF
                    || __this->status  == VIDEO_DEC_FR) {
                    video_dec_play_pause();
                    os_time_dly(100);
                }
                video_dec_stop(0);
                if (it->exdata) {
                    video_dec_file(it->exdata);
                }
            } else if (__this->status == VIDEO_DEC_PAUSE ||
                       __this->status == VIDEO_DEC_STOP) {
                if (it->exdata) {
                    video_dec_file(it->exdata);
                }
            }
            break;
        case ACTION_VIDEO_DEC_CONTROL:
            video_dec_play_pause();
            break;
        case ACTION_VIDEO_DEC_GET_FRAME:
            video_dec_get_frame();
            break;
        case ACTION_VIDEO_DEC_SET_AUDIO_VOLUME:
            video_dec_switch_audio_volume();
            break;
        case ACTION_VIDEO_DEC_SET_PLAY_SPEED:
            video_dec_set_speed(*(float *)it->exdata);
            break;
        case ACTION_VIDEO_DEC_CUR_PAGE:
            if (__this->req.dec.file) {
                server_request(__this->video_dec, VIDEO_REQ_DEC_STOP, &__this->req);
#if VIDEO_DEC_FB_PREV_OPEN
                video_dec_fb_prev_close();
#endif
                server_close(__this->video_dec);
                __this->video_dec = NULL;
#ifdef CONFIG_EMR_DIR_ENABLE
                if (__this->need_move) {
                    int attr;
                    char emr_path[128];
                    strcpy(emr_path, __this->cur_path);
                    strcat(emr_path, CONFIG_EMR_REC_DIR);

                    fget_attr(__this->req.dec.file, &attr);
                    if (attr & F_ATTR_RO) {
                        err = fmove(__this->req.dec.file, emr_path + sizeof(CONFIG_ROOT_PATH) - 1, NULL, 0);
                        if (err) {
                            log_e("move err");
                            fclose(__this->req.dec.file);
                        }
                    } else {
                        err = fmove(__this->req.dec.file, __this->cur_path + sizeof(CONFIG_ROOT_PATH) - 1, NULL, 0);
                        if (err) {
                            log_e("move err");
                            fclose(__this->req.dec.file);
                        }
                    }
                    __this->need_move = 0;
                } else {
                    fclose(__this->req.dec.file);
                }
#else
                if (__this->req.dec.file != NULL) {
                    fclose(__this->req.dec.file);
                }

#endif
                __this->req.dec.file = NULL;
                __this->status = VIDEO_DEC_STOP;
                sys_power_auto_shutdown_resume();
            }
            break;
#endif
        }
        break;
    case APP_STA_PAUSE:
        if (!strcmp(it->data, "frm")) {
            video_dec_stop(1);
        }
        break;
    case APP_STA_RESUME:
        if (__this->status == VIDEO_DEC_STOP) {
            video_dec_scan_dir();
        }
        break;
    case APP_STA_STOP:
#ifdef DISP_IMAGE_AND_VIDEO
        test_disp_stop();
#endif
        video_dec_stop(1);
        if (__this->wait) {
            wait_completion_del(__this->wait);
        }
#if (defined CONFIG_EMR_DIR_ENABLE && ! defined CONFIG_FILE_PREVIEW_ENABLE)
        if (__this->need_move) {
            int attr;
            char emr_path[128];
            FILE *file;
            struct vfscan *fs = NULL;
            strcpy(emr_path, dec_path[__this->curr_dir][0]);
            strcat(emr_path, CONFIG_EMR_REC_DIR);
            log_d("cur_path = %s", dec_path[__this->curr_dir][0]);
            log_d("emr_path = %s", emr_path);
            fs = fscan(dec_path[__this->curr_dir][0], dec_path[__this->curr_dir][1]);

            if (!fs || fs->file_number == 0) {
                log_e("fscan err");
                break;
            }
            file = fselect(fs, FSEL_FIRST_FILE, 0);
            while (file) {
                fget_attr(file, &attr);

                if (attr & F_ATTR_RO) {
                    log_d("locked");
                    err = fmove(file, emr_path + sizeof(CONFIG_ROOT_PATH) - 1, NULL, 0);
                    if (err) {
                        log_e("move err");
                        fclose(file);
                    }
                } else if (!(attr & F_ATTR_RO)) {
                    log_d("unlocked");
                    err = fmove(file, dec_path[__this->curr_dir][0] + sizeof(CONFIG_ROOT_PATH) - 1, NULL, 0);
                    if (err) {
                        log_e("move err");
                        fclose(file);
                    }
                }
                file = fselect(fs, FSEL_NEXT_FILE, 0);
            }
            __this->need_move = 0;
        }
#endif
        break;
    case APP_STA_DESTROY:
        if (__this->video_dec) {
#if VIDEO_DEC_FB_PREV_OPEN
            video_dec_fb_prev_close();
#endif
            server_close(__this->video_dec);
            __this->video_dec = NULL;
        }

#if 0//def CONFIG_UI_ENABLE
        {
            union uireq req;
            if (__this->ui) {
                req.hide.id = ID_WINDOW_VIDEO_REP;
                server_request(__this->ui, UI_REQ_HIDE, &req);
                server_close(__this->ui);
                __this->ui = NULL;
            }
        }
#endif


        log_d("<<<<<<< video_dec: destroy\n");
        break;
    }


    return ret;
}

/*
 * 按键消息处理函数
 */
static int video_dec_key_event_handler(struct key_event *key)
{
    int err;
    struct intent it;
    switch (key->action) {
    case KEY_EVENT_CLICK:
        switch (key->value) {
        case KEY_OK:
            printf("key ok");
            video_dec_play_pause();
            break;
        case KEY_UP:
            printf("key up");
#ifndef CONFIG_FILE_PREVIEW_ENABLE
            if (__this->status == VIDEO_DEC_PAUSE ||
                __this->status == VIDEO_DEC_STOP) {
                video_dec_file(FSEL_PREV_FILE);
            } else
#endif
            {
                //todo
#if 1
                if (__this->status != VIDEO_DEC_FR) {
                    __this->ff_fr_times = 1;
                }
                video_dec_ff_fr(VIDEO_REQ_DEC_FR);
#endif
            }
            break;
        case KEY_DOWN:
            printf("key down");
#ifndef CONFIG_FILE_PREVIEW_ENABLE
            if (__this->status == VIDEO_DEC_PAUSE ||
                __this->status == VIDEO_DEC_STOP) {
                video_dec_file(FSEL_NEXT_FILE);
            } else
#endif
            {
                //todo
#if 1
                if (__this->status != VIDEO_DEC_FF) {
                    __this->ff_fr_times = 1;
                }
                video_dec_ff_fr(VIDEO_REQ_DEC_FF);
#endif

            }
            break;
        case KEY_MODE:
            printf("key mode");
            if (__this->status  == VIDEO_DEC_PLAYING
                || __this->status  == VIDEO_DEC_FF
                || __this->status  == VIDEO_DEC_FR) {
                if (__this->status  == VIDEO_DEC_FF
                    || __this->status  == VIDEO_DEC_FR) {
                    video_dec_play_pause();
                    os_time_dly(100);
                }
                video_dec_stop(0);
                video_dec_file(FSEL_NEXT_FILE);
                return true;
            }
            break;
        default:
            break;
        }
        break;
    case KEY_EVENT_LONG:
        switch (key->value) {
        case KEY_UP:
            video_dec_stop(0);
            __this->curr_dir++;
            video_dec_scan_dir();
            break;
        case KEY_DOWN:
            video_dec_stop(0);
            __this->curr_dir--;
            video_dec_scan_dir();
            break;
        }
        break;
    default:
        break;
    }

    return false;
}

/*
 * 设备消息处理函数
 */
static int video_dec_device_event_handler(struct sys_event *sys_eve)
{
    struct device_event *device_eve = (struct device_event *)sys_eve->payload;
    switch (device_eve->event) {
    case DEVICE_EVENT_IN:
        video_dec_post_msg("cardIn");
        break;
    case DEVICE_EVENT_ONLINE:
        break;
    case DEVICE_EVENT_OUT:
        if (!fdir_exist(CONFIG_STORAGE_PATH)) {
#ifdef CONFIG_FILE_PREVIEW_ENABLE
            if (__this->status != VIDEO_DEC_STOP) {
                //进入了解码才关闭dec
                if (__this->video_dec) {
                    server_request(__this->video_dec, VIDEO_REQ_DEC_STOP, &__this->req);
#if VIDEO_DEC_FB_PREV_OPEN
                    video_dec_fb_prev_close();
#endif
                    server_close(__this->video_dec);
                    __this->video_dec = NULL;

                }
                if (__this->req.dec.file) {
                    fclose(__this->req.dec.file);
                    __this->req.dec.file = NULL;

                }
                __this->status = VIDEO_DEC_STOP;
                sys_power_auto_shutdown_resume();
            }
            video_dec_post_msg("noCard");
#else
            video_dec_stop(1);
            video_dec_post_msg("noCard");
            if (!__this->wait) {
                __this->wait = wait_completion(storage_device_ready, video_dec_start, NULL, NULL);
            }
#endif
        }
        break;
    }

    return false;
}

static int event_handler(struct application *app, struct sys_event *event)
{
    switch (event->type) {
    case SYS_KEY_EVENT:
        return video_dec_key_event_handler((struct key_event *)event->payload);
    case SYS_DEVICE_EVENT:
        return video_dec_device_event_handler(event);
    default:
        return false;
    }
}
static const struct application_operation video_dec_ops = {
    .state_machine  = state_machine,
    .event_handler 	= event_handler,
};

/*
 * 注册video_dec app
 *
 */
REGISTER_APPLICATION(app_video_dec) = {
    .name 	= "video_dec",
    .action	= ACTION_VIDEO_DEC_MAIN,
    .ops 	= &video_dec_ops,
    .state  = APP_STA_DESTROY,
};











