#include"video_photo.h"
#include"app_config.h"
#include "system/includes.h"
#include "server/video_server.h"
#include "server/video_dec_server.h"
#include "action.h"
#include "app_database.h"
#include "video_rec.h"
#include "lcd_config.h"
#include "event/key_event.h"
#include "user_isp_cfg.h"
#include "storage_device.h"
#include "vrec_osd.h"
#include "device_event.h"
#include "action.h"
#include "asm/gpio.h"

#if !LCD_W
#define SCREEN_W    800
#define SCREEN_H    480
#else
#define SCREEN_W    LCD_W
#define SCREEN_H    LCD_H
#endif

#if __SDRAM_SIZE__ > (8 * 1024 * 1024)
#define CAMERA_W    1280
#define CAMERA_H    720
#else
#define CAMERA_W    640
#define CAMERA_H    480
#endif

#define CAMERA_THUMBNAIL_ENABLE 1
#define THUMBNAIL_W     480
#define THUMBNAIL_H     320

#define IMAGE_THUMB_BUF_SIZE      (64 * 1024)

static int get_camera_setting_value(const char *name);
static int change_capture_res(int reso_index);
static int change_capture_sca(int sca);
static int change_capture_wbl(int wbl);
static int change_capture_pdat(int pdat);
static int change_capture_cyt(int cyt);
static int change_capture_phm(int phm);
static int change_capture_qua(int qua);
static int change_capture_pexp(int pexp);
static int change_capture_acu(int acu);
static int camera_display_start(void);
static int change_capture_zoom(int zoom_factor);
static int change_capture_col(int col);
static int cal_source_crop(struct video_source_crop *crop, float zoom_factor);
static int camera_display_pause(void);
static int camera_display_resume(void);
int storage_device_available(void);
u32 get_take_photo_num(void);
extern int user_isp_color_switch(int channel, int mode);


struct video_photo_handler {
    u8 camera_id;
    u8 camera_subid;
    u8 init_setting;
    int delay_capture_timeout;
    int quick_preview_timeout;
    int delay_ms;
    u8 *cap_buf;
    u8 *image_buf;
    u32 image_size;
    int check_usb_power_timer;
    u8 disable_capture;
    struct server *display;
    struct server *capture;
    struct server *quick_preview;
    struct video_text_osd label;
};

static struct video_photo_handler photo_handler;
#define __this  (&photo_handler)

struct photo_resolution {
    u16 width;
    u16 height;
};


static const struct app_cfg cfg_table_camera[] = {
    {"phm",  change_capture_phm},
    {"pres", change_capture_res},
    {"cyt",  change_capture_cyt},
    {"qua",  change_capture_qua},
    {"acu",  change_capture_acu},
    {"wbl",  change_capture_wbl},
    {"pexp", change_capture_pexp},
    {"pdat", change_capture_pdat},
    {"sca",  change_capture_sca},
    {"zoom", change_capture_zoom},
    {"col", change_capture_col},
};


//图片分辨率  删减要对应app_database
const static struct photo_resolution camera0_reso[] = {
    {640,  480},  //                VGA
    {1280, 720},  //                1M
    {1920, 1088}, //                2M
    {2048, 1552}, //                3M
    {2560, 1552}, //                4M
    {2592, 1968}, //                5M
    {3072, 1968}, //                6M
    {3456, 1968}, //                7M
    {3456, 2448}, //                8M
    {3456, 2592}, //                9M
    {3648, 2736}, //                10M
    {4032, 2736}, //                11M
    {4032, 3024}, //                12M
    {5120, 2880}, //                16M
    {6016, 4096}, //                24M
    {7680, 4352}, //                32M
    {10240, 5760}, //               64M
};

//修改更新摄像头配置 app_database.c
static int update_camera_setting(const char *name, int value)
{
    return db_update(name, value);
}

//获取摄像头配置
static int get_camera_setting_value(const char *name)
{
    if (__this->camera_id != 2) {
        return db_select(name);
    } else {
        if ((strcmp(name, "cyt") == 0) ||
            (strcmp(name, "pdat") == 0) ||
            (strcmp(name, "sca") == 0) ||
            (strcmp(name, "qua") == 0) ||
            (strcmp(name, "phm") == 0) ||
            strcmp(name, "pres") == 0) {
            return db_select(name);
        }
    }

    return 0;
}

//修改图片质量
static int change_capture_qua(int qua)
{
    return update_camera_setting("qua", qua);
}

//快速预览
static int change_capture_sca(int sca)
{
    return update_camera_setting("sca", sca);
}

//定时拍照
static int change_capture_phm(int phm)
{
    return update_camera_setting("phm", phm);
}

//日期标签
static int change_capture_pdat(int pdat)
{
    return update_camera_setting("pdat", pdat);
}

//是否连拍
static int change_capture_cyt(int cyt)
{
    return update_camera_setting("cyt", cyt);
}

//修改分辨率
static int change_capture_res(int reso_index)
{
    return update_camera_setting("pres", reso_index);
}


_WEAK_ void video_photo_post_msg(const char *msg, ...)
{
//给UI发送消息
}

//修改图片锐度:强烈/标准/柔和
static int change_capture_acu(int acu)
{
    int err;
    struct server *server;
    union video_req req = {0};

    if (__this->camera_id == 2 || __this->camera_id == 4 || __this->camera_id == 5) {
        return 0;
    }
    if ((acu < PHOTO_ACU_LO) || (acu > PHOTO_ACU_HI)) {
        log_w("invalid value acu");
        return -1;
    }

    update_camera_setting("acu", acu);
    /* server = __this->capture? __this->capture:__this->display; */
    server = __this->display;

    if (!server) {
        log_e("acu not found server");
        return -1;
    }
    req.camera.shpn_level = acu;
    req.camera.cmd = SET_CAMERA_SHP_LEVEL;
    err = server_request(server, VIDEO_REQ_CAMERA_EFFECT, &req);
    if (err) {
        log_e("acu server_request err: %d", err);
        return err;
    }

    return 0;
}

//修改白平衡:自动/日光/阴天/钨丝灯/荧光灯
static int change_capture_wbl(int wbl)
{
    int err;
    struct server *server;
    union video_req req = {0};

    if (__this->camera_id == 2 || __this->camera_id == 4 || __this->camera_id == 5) {
        return 0;
    }

    if ((wbl < PHOTO_WBL_AUTO) || (wbl > PHOTO_WBL_FLUL)) {
        log_w("invalid value wbl");
        return -1;
    }

    update_camera_setting("wbl", wbl);
    /* server = __this->capture? __this->capture:__this->display; */
    server = __this->display;

    if (!server) {
        log_e("wbl not found server");
        return -1;
    }

    req.camera.white_blance = wbl;
    req.camera.cmd = SET_CAMERA_WB;
    err = server_request(server, VIDEO_REQ_CAMERA_EFFECT, &req);
    if (err) {
        log_e("wbl server_request err: %d", err);
        return err;
    }

    return 0;
}

//曝光补偿-3/-2/-1/+1/+2/+3
static int change_capture_pexp(int pexp)
{
    int err;
    struct server *server;
    union video_req req = {0};

    if (__this->camera_id == 2 || __this->camera_id == 4 || __this->camera_id == 5) {
        return 0;
    }

    if ((pexp < -3) || (pexp > 3)) {
        log_w("invalid value pexp");
        return -1;
    }

    update_camera_setting("pexp", pexp);
    /* server = __this->capture? __this->capture:__this->display; */
    server = __this->display;

    if (!server) {
        log_e("set not found server");
        return -1;
    }

    req.camera.ev = pexp;
    req.camera.cmd = SET_CAMERA_EV;
    err = server_request(server, VIDEO_REQ_CAMERA_EFFECT, &req);

    if (err) {
        log_e("pexp server_request err: %d", err);
    }

    return err;
}

//数字变焦
static int change_capture_zoom(int zoom_factor)
{
    int err;
    union video_req req = {0};
    struct video_source_crop crop;

    update_camera_setting("zoom", zoom_factor);
    float zoom = (float)zoom_factor / 10;

    log_i("%s----value:%.1f \n", __FUNCTION__, zoom);
    err = cal_source_crop(&crop, zoom);
    if (err) {
        log_e("set disp digital zoom err");
        return err;
    }

    //显示
    if (__this->display) {
        req.display.crop = &crop;
        req.display.state = VIDEO_STATE_SET_DIS_CROP;
        err = server_request(__this->display, VIDEO_REQ_DISPLAY, &req);
        if (err) {
            log_e("%s err", __FUNCTION__);
        }
    }
    return err;
}

//修改图片色彩
static int change_capture_col(int col)
{
    if (__this->camera_id == 2 || __this->camera_id == 4 || __this->camera_id == 5) {
        return 0;
    }

    switch (col) {
    case PHOTO_COLOR_NORMAL:
        user_isp_color_switch(__this->camera_id == 0 ? 2 : 0, 0);
        //效果会覆盖,重新设置
        change_capture_wbl(get_camera_setting_value("wbl"));
        change_capture_pexp(get_camera_setting_value("pexp"));
        break;
    case PHOTO_COLOR_WB:
        user_isp_color_switch(__this->camera_id == 0 ? 2 : 0, 1);
        break;
    case PHOTO_COLOR_OLD:
        user_isp_color_switch(__this->camera_id == 0 ? 2 : 0, 2);
        break;
    default:
        break;
    }
}



static int set_camera_config(struct intent *it)
{
    ASSERT(it != NULL);
    ASSERT(it->data != NULL);
    int i = 0 ;

    for (i = 0; i < ARRAY_SIZE(cfg_table_camera); i++) {
        if (strcmp(it->data, cfg_table_camera[i].table) == 0) {
            log_i("camera set config %s", it->data);
            return cfg_table_camera[i].set(it->exdata);
        }
    }
    log_w("no cmp config");
    return 0;
}


//判断SD卡是否挂载成功和簇大小是否大于32K
int storage_device_available()
{
    struct vfs_partition *part;

    if (!storage_device_ready()) {
        return false;
    } else {
        part = fget_partition(CONFIG_ROOT_PATH);
        if (part->clust_size < 32 || (part->fs_attr & F_ATTR_RO)) {
            return false;
        }
    }
    return true;
}

//获取可拍照数量
u32 get_take_photo_num(void)
{
    int err;
    u32 free_space = 0;
    int coef;
    int reso_index = get_camera_setting_value("pres");
    //单位KB
    if (!storage_device_available()) {
        return 0;
    }

    err = fget_free_space(CONFIG_ROOT_PATH, &free_space);
    if (err) {
        log_e("get free space err:%d", err);
        return 0;
    }

    coef = get_camera_setting_value("pres") > PHOTO_RES_5M ? 60 : 40;
    coef = coef / (get_camera_setting_value("qua") + 1);
    u32 img_num = free_space / (camera0_reso[reso_index].width *
                                camera0_reso[reso_index].height / coef / 1024);

    log_i("sd free space : %dKB img_size: %dKB img_num:%d \n", free_space, __this->image_size / 1024, img_num);
    return img_num > 99999 ? 99999 : img_num;
}

//根据分辨率调整申请的内存大小
static u32 get_cap_buf_size(void)
{
    int reso_index = get_camera_setting_value("pres");
    u32 buf_size = 0;

    if (reso_index >= PHOTO_RES_5M && reso_index < PHOTO_RES_11M) {
        // 1.5MB
        buf_size = 1024 * 1024 * 1 + 1024 * 512;
    } else if (reso_index >= PHOTO_RES_11M) {
        // 3MB
        buf_size = 1024 * 1024 * 3;
    } else {
        // 1MB
        buf_size = 1024 * 1024 * 1;
    }
    return buf_size;
}

//停止显示
static int camera_display_stop(void)
{
    union video_req req;

    if (__this->display) {
        req.display.state = VIDEO_STATE_STOP;

        server_request(__this->display, VIDEO_REQ_DISPLAY, &req);
        server_close(__this->display);
        __this->display = NULL;

    }
    return 0;
}

static int cal_source_crop(struct video_source_crop *crop, float zoom_factor)
{
    if (zoom_factor < 1) {
        log_e("zoom_factor invalid");
        return -EFAULT;
    }

    int src_width = CAMERA_W;
    int src_height = CAMERA_H;

    crop->width = src_width / zoom_factor;
    crop->height = src_height / zoom_factor;

    //居中变焦
    crop->x_offset = (src_width - crop->width) / 2;
    crop->y_offset = (src_height - crop->height) / 2;

    return 0;
}


//停止拍照,释放拍照内存
static int camera_capture_stop(void)
{
    union video_req req;

    if (__this->cap_buf) {
        free(__this->cap_buf);
        __this->cap_buf = NULL;
    }

    if (__this->capture) {
        server_close(__this->capture);
        __this->capture = NULL;
    }
    return 0;
}

//设置日期水印
static int set_label_config(u16 image_width, u16 image_height, u32 font_color,
                            struct video_text_osd *label)
{
    if (!label) {
        return 0;
    }

    label->direction = 0;

    label->font_w = 16;
    label->font_h = 32;
    label->text_format = label_format;
    label->font_matrix_table = (char *)osd_str_total;

    label->color[0] = 0x057d88;
    label->color[1] = 0xe20095;
    label->color[2] = 0xe20095;
    label->bit_mode = 2;
    label->font_matrix_base = osd2_str_matrix;
    label->font_matrix_len = sizeof(osd2_str_matrix);
    //label->font_matrix_base = (u8 *)osd_str_matrix;
    //label->font_matrix_len = sizeof(osd_str_matrix);

    label->x = (1280 - strlen(label_format) * label->font_w) / 64 * 64;
    label->y = (720 - label->font_h - 16) / 16 * 16;

    return 0;
}

//结束快速预览
static void interrupt_quick_preview(void)
{
    union video_dec_req dec_req = {0};
    if (__this->quick_preview_timeout) {
        sys_timeout_del(__this->quick_preview_timeout);
        __this->quick_preview_timeout  = 0;
    }

    if (__this->quick_preview) {
        server_request(__this->quick_preview, VIDEO_REQ_DEC_STOP, &dec_req);
        server_close(__this->quick_preview);
        __this->quick_preview = NULL;

        camera_display_resume();
    }

    /* camera_display_start(); */
    //禁止拍照标志，快速预览时禁止拍照
    __this-> disable_capture = 0;
    key_event_enable();
    touch_event_enable();
}

//启动快速预览
static int camera_quick_preview(u32 timeout)
{
    int err = 0;
    union video_req req;
    union video_dec_req dec_req;
    char fb_name[4];

    memset(&dec_req, 0x0, sizeof(dec_req));

    //if (__this->display) {
    //camera_display_stop();
    //}

    if (!__this->quick_preview) {
        struct video_dec_arg arg = {0};
        arg.dev_name = "video_dec";
        arg.video_buf_size = 512;
        __this->quick_preview = server_open("video_dec_server", &arg);
        if (!__this->quick_preview) {
            log_e("open video_dec_server fail");
            return -EFAULT;
        }
    }
    camera_display_pause();

    //优先解缩略图标志
#if CAMERA_THUMBNAIL_ENABLE
    dec_req.dec.thm_first = 1;
#endif

    sprintf(fb_name, "fb%d", __this->camera_id + 1);
    dec_req.dec.fb = fb_name;
    dec_req.dec.left = 0;
    dec_req.dec.top = 0;
    dec_req.dec.width = SCREEN_W;
    dec_req.dec.height = SCREEN_H;

    dec_req.dec.pctl = NULL;
    dec_req.dec.preview = 1;
    dec_req.dec.image.buf = __this->image_buf;
    dec_req.dec.image.size = __this->image_size;

    //禁止拍照标志，快速预览时禁止拍照
    __this->disable_capture = 1;
    err = server_request(__this->quick_preview, VIDEO_REQ_DEC_IMAGE, &dec_req);

    __this->quick_preview_timeout = sys_timeout_add(NULL, interrupt_quick_preview, timeout);

    return 0;
}

//拍照
static int camera_take_photo(void)
{
    int err = 0;
    union video_req req;
    union video_req img_req = {0};
    char video_name[16];
    char file_name[32];
    u32 preview_timeout_val;
    int reso_index;
    int img_width, img_height;
    struct jpg_thumbnail thumbnails = {0};
    struct image_sticker sticker = {0};
    struct video_source_crop crop;
    float zoom_val;
    u32 img_buf_size;
    static u32 last_buf_size;
    int photo_cnt = 1;

    key_event_disable();
    touch_event_disable();

    if (!storage_device_available()) {
        log_w("storage no available");
        err = -EINVAL;
        goto __err;
    }

    //video0.0
    if (__this->camera_id == 2) {
        sprintf(video_name, "video%d.0", 10);
    } else {
        sprintf(video_name, "video%d.0", __this->camera_id);
    }
    if (!__this->capture) {
        __this->capture = server_open("video_server", video_name);
        if (!__this->capture) {
            log_e("video_server open fail");
            err = -EINVAL;
            goto __err;
        }
    }

    img_buf_size = get_cap_buf_size();
    if ((!__this->cap_buf) || (last_buf_size != img_buf_size)) {
        if (__this->cap_buf) {
            free(__this->cap_buf);
            __this->cap_buf = NULL;
        }
        __this->cap_buf = (u8 *)malloc(img_buf_size);
    }
    last_buf_size = img_buf_size;

    memset(&req, 0x0, sizeof(req));

    //拍照分辨率
    reso_index = get_camera_setting_value("pres");
    img_width = camera0_reso[reso_index].width;
    img_height = camera0_reso[reso_index].height;

    req.icap.width = img_width;
    req.icap.height = img_height;
    req.icap.quality = get_camera_setting_value("qua");

    req.icap.buf = __this->cap_buf;
    req.icap.buf_size = img_buf_size;
    req.icap.camera_type = VIDEO_CAMERA_NORMAL;
    req.icap.online = 0;
    req.icap.image_state = 0;

    if (__this->camera_id == 0) {
        req.icap.path = CAMERA0_CAP_PATH"img_****.jpg";
    } else if (__this->camera_id == 1) {
        req.icap.path = CAMERA1_CAP_PATH"img_****.jpg";
    } else if (__this->camera_id == 4) {
        req.icap.path = CAMERA4_CAP_PATH"img_****.jpg";
    } else if (__this->camera_id == 5) {
        req.icap.path = CAMERA5_CAP_PATH"img_****.jpg";
    } else {
#if THREE_WAY_ENABLE
        req.icap.path = CAMERA2_CAP_PATH"img_****.jpg";
#else
        req.icap.path = CAMERA1_CAP_PATH"img_****.jpg";
#endif
    }

    req.icap.file_name = file_name;

    //拍照贴纸配置
    sticker.x = 10;
    sticker.y = 10;
    sticker.addr = "mnt/sdfile/EXT_RESERVED/uipackres/ui/4b000056.zip";
    /* req.icap.sticker = &sticker; */
    req.icap.sticker = NULL;

    //日期标签
    req.icap.text_label = get_camera_setting_value("pdat") ? &__this->label : NULL;
    req.icap.src_w = 1280;//CAMERA_W;
    req.icap.src_h = 720;//CAMERA_H;
    set_label_config(req.icap.width, req.icap.height, 0xe20095, req.icap.text_label);

    //变焦, VM值除以10,暂时不用
#if 0
    if (__this->camera_id != 2) {
        zoom_val = (float)get_camera_setting_value("zoom") / 10;
        if (!cal_source_crop(&crop, zoom_val)) {
            req.icap.crop = &crop;
        }
    }
#endif
    //uvc
    if (__this->camera_id == 2) {
        req.icap.camera_type = VIDEO_CAMERA_UVC;
        req.icap.uvc_id = __this->camera_subid;
    }

    //连拍
    if (get_camera_setting_value("cyt")) {
        photo_cnt = 3;
    }


#ifdef CONFIG_UI_STYLE_LY_ENABLE
    video_photo_post_msg("tphin");
#endif

    //打断快速预览
    //interrupt_quick_preview();

    while (photo_cnt--) {
        //拍缩略图
#if CAMERA_THUMBNAIL_ENABLE
        log_i("add thumbnail");
        thumbnails.enable = 1;
        thumbnails.buf = __this->cap_buf + img_buf_size - IMAGE_THUMB_BUF_SIZE;
        thumbnails.len = IMAGE_THUMB_BUF_SIZE;
        req.icap.thumbnails = &thumbnails;
#endif
        //发送拍照请求
        log_i("server request image capture");
        err = server_request(__this->capture, VIDEO_REQ_IMAGE_CAPTURE, &req);
        if (err) {
            goto __err;
        }

        log_i("take photo ok :%s \n", req.icap.file_name);

        //获取照片
        err = server_request(__this->capture, VIDEO_REQ_GET_IMAGE, &img_req);
        if (err) {
            log_e("get image fail");
            err = -EINVAL;
            goto __err;
        }
        __this->image_buf = img_req.image.buf;
        __this->image_size = img_req.image.size;

        //发送UI MSG 更新可拍照数量
        u32 img_num = get_take_photo_num();
        video_photo_post_msg("remainPhoto", img_num);

        key_voice_start(1);
    }

#ifdef CONFIG_UI_STYLE_LY_ENABLE
    video_photo_post_msg("tphout");
#endif

    preview_timeout_val = get_camera_setting_value("sca");
    if (preview_timeout_val) {
        log_i("quick preview time: %d\n", preview_timeout_val);
        int sec = preview_timeout_val * 1000;
        camera_quick_preview(sec);
    } else {
        key_event_enable();
        touch_event_enable();

    }

    log_i("take photo res:%dx%d succ\n", img_width, img_height);
    __this->image_size  = 0;

    return 0;

__err:
    log_w("video take photo err : %d\n", err);

    camera_capture_stop();
    key_event_enable();
    touch_event_enable();

    return err;

}


//延时拍照定时器回调
static void delay_capture_timer_cb(void *p)
{
    __this->delay_ms -= 1000;

    printf("----delay time :%d ----\n", __this->delay_ms);
#ifndef CONFIG_UI_STYLE_LY_ENABLE
    video_photo_post_msg("captureTime", __this->delay_ms / 1000);
#endif

    if (__this->delay_ms == 0) {
        sys_timer_del(__this->delay_capture_timeout);
        __this->delay_capture_timeout = 0;
        camera_take_photo();
    } else {

    }
}

//打断延时拍照,不拍了
static void interrupt_delay_capture(void)
{
    if (__this->delay_capture_timeout) {
        sys_timer_del(__this->delay_capture_timeout);
        __this->delay_capture_timeout = 0;
    }


}

//延时拍照.拍照统一调这个接口
static int camera_delay_capture(int sec)
{
    //禁止拍照标志，快速预览时禁止拍照
    if (__this->disable_capture) {
        return 0;
    }

    //目前内存不支持超大分辨率拍照
    int reso_index = get_camera_setting_value("pres");
    if (reso_index > 10) {
        log_w("Please switch to a smaller resolution to take photos");
        return 0;
    }

    interrupt_delay_capture();

    if (sec > 0) {
        __this->delay_ms = sec * 1000;
#ifndef CONFIG_UI_STYLE_LY_ENABLE
        video_photo_post_msg("captureTime", __this->delay_ms / 1000);
#endif
        __this->delay_capture_timeout = sys_timer_add(NULL, delay_capture_timer_cb, 1000);
        if (!__this->delay_capture_timeout) {
            log_e("delay capture  timer add fail");
            return -EFAULT;
        }
    } else {
        camera_take_photo();
    }
    return 0;
}

static int camera_display_pause(void)
{
    union video_req req = {0};
    if (!__this->display) {
        return 0;
    }
    req.display.state 	= VIDEO_STATE_PAUSE;

    return server_request(__this->display, VIDEO_REQ_DISPLAY, &req);
}

static int camera_display_resume(void)
{
    union video_req req = {0};
    if (!__this->display) {
        return 0;
    }
    req.display.state 	= VIDEO_STATE_RESUME;

    return server_request(__this->display, VIDEO_REQ_DISPLAY, &req);
}


static int camera_display_start(void)
{
    int ret;
    union video_req req;
    char video_name[16];
    char fb_name[4];


#ifdef CONFIG_VIDEO2_ENABLE

#if TCFG_HOST_UVC_ENABLE
    int uvc_host_online(void);
    if (__this->camera_id == 2 && uvc_host_online() != __this->camera_subid) {
        log_w(" uvc sub id:%d not online", __this->camera_subid);
#ifdef CONFIG_VIDEO0_ENABLE
        //uvc不在线 切换回video0
        __this->camera_id = 0;
#elif (defined CONFIG_VIDEO4_ENABLE)
        __this->camera_id = 4;
#elif (defined CONFIG_VIDEO5_ENABLE)
        __this->camera_id = 5;
#endif
        __this->camera_subid = 0;
    }
#endif

#endif

    if (__this->display) {
        return 0;
    }

    if (__this->camera_id == 2) {
        sprintf(video_name, "video%d.0", 10);
    } else {
        sprintf(video_name, "video%d.0", __this->camera_id);
    }
    sprintf(fb_name, "fb%d", __this->camera_id + 1);

    __this->display = server_open("video_server", video_name);
    if (!__this->display) {
        log_e("server open fail");
        return -EFAULT;
    }



    memset(&req, 0x0, sizeof(req));
    req.display.fb 		= fb_name;
    req.display.width 	= SCREEN_W;
    req.display.height 	= SCREEN_H;
    req.display.left  	= 0;
    req.display.top 	= 0;
    req.display.mirror  = 0; //1镜像
    req.display.state 	= VIDEO_STATE_START;
    req.display.pctl = NULL;

    if (__this->camera_id == 2) {
        req.display.uvc_id          = __this->camera_subid;
        req.display.camera_config   = NULL;
        req.display.camera_type     = VIDEO_CAMERA_UVC;
        req.display.src_w           = CAMERA_W;
        req.display.src_h           = CAMERA_H;
    } else {
        req.display.camera_type = VIDEO_CAMERA_NORMAL;
    }

    ret = server_request(__this->display, VIDEO_REQ_DISPLAY, &req);
    if (ret) {
        //todo
        log_e("display req ret: %d", ret);
        return ret;
    }

    change_capture_acu(get_camera_setting_value("acu"));     //锐度
    change_capture_wbl(get_camera_setting_value("wbl"));     //白平衡
    change_capture_pexp(get_camera_setting_value("pexp"));     //曝光
    change_capture_col(get_camera_setting_value("col"));      //色彩

    //UVC暂时不用
    if (__this->camera_id != 2) {
        //先不保存上次退出时使用的变焦值
        update_camera_setting("zoom", 10);
        /* change_capture_zoom(get_camera_setting_value("zoom")); */
    }

    return 0;
}

//uvc用sub_id
static int photo_mode_start(u8 id, u8 sub_id)
{
    int err = 0;

    __this->camera_id = id;
    if (id == 2) {
        __this->camera_subid = sub_id;
    }

    log_i("camera display start");
    err = camera_display_start();
    if (err) {
        return err;
    }

    return 0;
}
static void switch_camera(void)
{
    camera_display_stop();
    camera_capture_stop();

#if THREE_WAY_ENABLE
    if (__this->camera_id == 0) {
        __this->camera_id = 1;
    } else if (__this->camera_id == 1) {
        __this->camera_id = 2;
    } else {
        __this->camera_id = 0;
    }
#else
#ifdef CONFIG_VIDEO0_ENABLE
    __this->camera_id = __this->camera_id ? 0 : 2;
#elif (defined CONFIG_VIDEO4_ENABLE && defined CONFIG_VIDEO5_ENABLE)
    __this->camera_id = __this->camera_id == 4 ? 5 : 4;
#endif
#endif

#if TCFG_HOST_UVC_ENABLE
    __this->camera_subid  = uvc_host_online();
#endif

    camera_display_start();
}

static void check_usb_gpio_state(void)
{
    gpio_direction_input(TCFG_USB_POWER_CHECK_IO);
    gpio_set_die(TCFG_USB_POWER_CHECK_IO, 1);
    int gpio_state = gpio_read(TCFG_USB_POWER_CHECK_IO);
    int vbat_level;
    if (gpio_state) {
        video_photo_post_msg("batIcon", 110);
    } else {
        vbat_level = get_vbat_percent();
        video_photo_post_msg("batIcon", vbat_level);
    }
}

static void photo_mode_init(void)
{
    memset(__this, 0, sizeof(__this));
#if (defined(CONFIG_VIDEO0_ENABLE) && defined(CONFIG_VIDEO1_ENABLE)) || (defined(CONFIG_VIDEO4_ENABLE) && defined(CONFIG_VIDEO5_ENABLE))
    video_photo_post_msg("swWinicon", 1);
#endif

    __this->check_usb_power_timer = sys_timer_add_to_task("app_core", NULL, check_usb_gpio_state, 1000);
}

static void photo_mode_exit(void)
{
    interrupt_delay_capture();
    interrupt_quick_preview();
    camera_display_stop();
    camera_capture_stop();

    if (__this->check_usb_power_timer) {
        sys_timer_del(__this->check_usb_power_timer);
        __this->check_usb_power_timer = NULL;
    }

    memset(__this, 0, sizeof(__this));
}

static int state_machine(struct application *app, enum app_state state, struct intent *it)
{
    u32 delay, img_num;
    switch (state) {
    case APP_STA_CREATE:
        log_d("\n>>>>> photo_mode_init <<<<<\n");
        photo_mode_init();
        break;
    case APP_STA_START:
        if (!it) {
            break;
        }
        switch (it->action) {
        case ACTION_PHOTO_TAKE_MAIN:
            log_d("\n>>>>> photo_mode_start <<<<<\n");
            u8 uvc_id = 0;
#if TCFG_HOST_UVC_ENABLE
            uvc_id = uvc_host_online();
#endif

            printf("uvc->id:%d", uvc_id);
            u8 id = 0;
#ifdef CONFIG_VIDEO0_ENABLE
            id = 0;
#elif (defined CONFIG_VIDEO4_ENABLE)
            id = 4;
#elif (defined CONFIG_VIDEO5_ENABLE)
            id = 5;
#endif
            photo_mode_start(id, uvc_id >= 0 ? uvc_id : 0);
            //发送UI MSG 更新可拍照数量
            img_num = get_take_photo_num();
            video_photo_post_msg("remainPhoto", img_num);
            break;
        case ACTION_PHOTO_TAKE_CONTROL:
            delay = get_camera_setting_value("phm");
            log_i("deley take photo: %d sec", delay);
            camera_delay_capture(delay);
            break;
        case ACTION_PHOTO_TAKE_SET_CONFIG:
            set_camera_config(it);
            break;
        case ACTION_PHOTO_TAKE_GET_CONFIG:
            it->exdata = get_camera_setting_value(it->data);
            break;
        case ACTION_PHOTO_TAKE_SWITCH_WIN:
            switch_camera();
            break;
        }
        break;
    case APP_STA_PAUSE:
        break;
    case APP_STA_RESUME:
        break;
    case APP_STA_STOP:
        break;
    case APP_STA_DESTROY:
        log_d("\n>>>>> photo_mode_exit <<<<<\n");
        photo_mode_exit();
        break;
    default:
        break;
    }
    return 0;
}


static int video_photo_key_event_handler(struct key_event *key)
{
    int ret = false;
    if (key->action == KEY_EVENT_CLICK) {
        ret = true;
        switch (key->value) {
        case KEY_POWER:
            printf("KEY1\n");
            // camera_delay_capture(0);
            break;
        case KEY_MODE:
            printf("KEY2\n");
            // switch_camera();
            break;
        case KEY_UP:
            printf("KEY3\n");
            break;
        case KEY_DOWN:
            printf("KEY4\n");
            switch_camera();
            break;
        case KEY_OK:
            printf("KEY5\n");
            camera_delay_capture(get_camera_setting_value("phm"));
            break;
        default:
            printf("Unknow KEY\n");
            break;
        }
    }

    return ret;
}



static int video_photo_device_event_handler(struct sys_event *e)
{
    struct device_event *device_eve = (struct device_event *)e->payload;
    int dev_id = 0;
    char *type = NULL;
    static u32 uvc_offline = 0;


    //SD卡
    if (e->from == DEVICE_EVENT_FROM_SD) {
        switch (device_eve->event) {
        case DEVICE_EVENT_IN:
            video_photo_post_msg("sdStatus", 1);
            u32 img_num = get_take_photo_num();
            video_photo_post_msg("remainPhoto", img_num);
            break;
        case DEVICE_EVENT_OUT:
            video_photo_post_msg("sdStatus", 0);
            video_photo_post_msg("remainPhoto", 0);
            break;
        }
    }
#ifdef CONFIG_VIDEO2_ENABLE
    else if (e->from == DEVICE_EVENT_FROM_USB_HOST && !strncmp((const char *)device_eve->value, "uvc", 3)) {
        switch (device_eve->event) {
        case DEVICE_EVENT_IN:
#ifndef CONFIG_UI_STYLE_LY_ENABLE
            video_photo_post_msg("swWinicon", 1);
#endif
            break;
        case DEVICE_EVENT_OUT:
#ifndef CONFIG_UI_STYLE_LY_ENABLE
#if (defined(CONFIG_VIDEO0_ENABLE) && defined(CONFIG_VIDEO1_ENABLE)) || (defined(CONFIG_VIDEO4_ENABLE) && defined(CONFIG_VIDEO5_ENABLE))
            video_photo_post_msg("swWinicon", 1);
#elif defined(CONFIG_VIDEO0_ENABLE) || defined(CONFIG_VIDEO1_ENABLE) || defined(CONFIG_VIDEO4_ENABLE) || defined(CONFIG_VIDEO5_ENABLE)
            video_photo_post_msg("swWinicon", 0);
#endif
#endif
            if (__this->camera_id == 2) {
                switch_camera();
            }
            break;
        }
    }
#endif


    return false;
}

static int event_handler(struct application *app, struct sys_event *event)
{
    switch (event->type) {
    case SYS_KEY_EVENT:
        return  video_photo_key_event_handler((struct key_event *)event->payload);
    case SYS_DEVICE_EVENT:
        return  video_photo_device_event_handler(event);
    default:
        return false;
    }
}

static const struct application_operation video_photo_ops = {
    .state_machine  = state_machine,
    .event_handler  = event_handler,
};

REGISTER_APPLICATION(app_video_photo) = {
    .name 	= "video_photo",
    .action	= ACTION_PHOTO_TAKE_MAIN,
    .ops 	= &video_photo_ops,
    .state  = APP_STA_DESTROY,
};

