#include "system/includes.h"
#include "stream_core.h"
/* #include "server/ui_server.h" */
#include "server/video_server.h"
#include "server/video_engine_server.h"
#include "net_video_rec.h"
#include "video_system.h"
#include "gSensor_manage.h"
#include "action.h"
#include "app_config.h"
#include "asm/debug.h"
#include "vrec_osd.h"
#include "vrec_icon_osd.h"
#include "app_database.h"
#include "storage_device.h"
#include "server/ctp_server.h"
#include "server/net_server.h"
#include "strm_video_rec.h"

#ifdef CONFIG_NET_ENABLE
static int net_video_rec_start(u8 mark);
int net_video_rec_stop(u8 close);
static int net_video_rec1_stop(u8 close);
static int net_video_rec_take_photo(void (*callback)(char *buffer, int len));

#define AUDIO_VOLUME	64
#define NET_VIDEO_REC_SERVER_NAME	"net_video_server"
#define TAKE_PHOTO_MEM_LEN		200 * 1024	//512 * 1024

#define	NET_VIDEO_ERR(x)	{if(x) printf("######## %s %d err !!!! \n\n\n",__func__,__LINE__);}

static int net_rt_video0_stop(struct intent *it);
static int net_rt_video1_stop(struct intent *it);
static int net_video_rec_control(void *_run_cmd);


static char file_str[64];
static int net_vd_msg[2];
static const u16 net_rec_pix_w[] = {1920, 1280, 640};
static const u16 net_rec_pix_h[] = {1088, 720,  480};
static const u16 net_pic_pix_w[] = {320, 640, 1280};
static const u16 net_pic_pix_h[] = {240, 480, 720 };
static struct net_video_hdl net_rec_handler = {0};
static struct strm_video_hdl *fv_rec_handler = NULL;
static struct video_rec_hdl *rec_handler = NULL;

#define __this_net  (&net_rec_handler)
#define __this_strm	(fv_rec_handler)
#define __this 	(rec_handler)

static OS_MUTEX net_vdrec_mutex;


#define CONFIG_OSD_LOGO

/*
 *start user net video rec , 必须在net_config.h配置宏CONFIG_NET_USR_ENABLE 和NET_USR_PATH
 */
int user_net_video_rec_open(char forward)
{
    int ret;
    u8 open = 2;//char type : 0 audio , 1 video , 2 audio and video
    struct intent it;
    struct rt_stream_app_info info;

    info.width = 1280;
    info.height = 720;

    //帧率 net_config.h : NET_VIDEO_REC_FPS0/NET_VIDEO_REC_FPS1

    it.data = &open;
    it.exdata = (u32)&info;

    if (forward) {
#ifdef CONFIG_VIDEO0_ENABLE
        ret = net_rt_video0_open(&it);
#elif (defined CONFIG_VIDEO4_ENABLE)
        ret = net_rt_video4_open(&it);
#endif
    } else {
#ifdef CONFIG_VIDEO2_ENABLE
        ret = net_rt_video2_open(&it);
#elif (defined CONFIG_VIDEO5_ENABLE)
        ret = net_rt_video5_open(&it);
#endif
    }
    return ret;
}

int user_net_video_rec_close(char forward)
{
    int ret;
    struct intent it;
    u8 close = 2;//char type : 0 audio , 1 video , 2 audio and video

    it.data = &close;
    if (forward) {
#ifdef CONFIG_VIDEO0_ENABLE
        ret = net_rt_video0_stop(&it);
#elif (defined CONFIG_VIDEO4_ENABLE)
        ret = net_rt_video4_stop(&it);
#endif
    } else {
#ifdef CONFIG_VIDEO2_ENABLE
        ret = net_rt_video2_stop(&it);
#elif (defined CONFIG_VIDEO5_ENABLE)
        ret = net_rt_video5_stop(&it);
#endif
    }
    return ret;
}

void user_net_video_rec_take_photo_cb(char *buf, int len)//必须打开user_net_video_rec_open()
{
    if (buf && len) {
        printf("take photo success \n");
        put_buf(buf, 32);
        /*
        //目录1写卡例子
        FILE *fd = fopen(CAMERA0_CAP_PATH"IMG_***.JPG","w+");
        if (fd) {
        	fwrite(fd,buf,len);
        	fclose(fd);
        }
        */
    }
}
//qua : 0 240p, 1 480p, 2 720p
int user_net_video_rec_take_photo(int qua, void (*callback)(char *buf, int len))//必须打开user_net_video_rec_open()
{
    db_update("qua", qua);
    net_video_rec_take_photo(callback);
    return 0;
}
//example 720P: user_net_video_rec_take_photo(2, user_net_video_rec_take_photo_cb);
int user_net_video_rec_take_photo_test(void)
{
    user_net_video_rec_take_photo(2, user_net_video_rec_take_photo_cb);
    return 0;
}
/*
 *end of user net video rec
 */
int net_video_rec_get_list_vframe(void)
{
    return __this_net->fbuf_fcnt;
}
void net_video_rec_pkg_get_video_in_frame(char *fbuf, u32 frame_size)
{
    __this_net->fbuf_fcnt++;
    __this_net->fbuf_ffil += frame_size;
}
void net_video_rec_pkg_get_video_out_frame(char *fbuf, u32 frame_size)
{
    if (__this_net->fbuf_fcnt) {
        __this_net->fbuf_fcnt--;
    }
    if (__this_net->fbuf_ffil) {
        __this_net->fbuf_ffil -= frame_size;
    }
}
static void net_video_handler_init(void)
{
    fv_rec_handler = (struct strm_video_hdl *)get_strm_video_rec_handler();
    rec_handler  = (struct video_rec_hdl *)get_video_rec_handler();
}

void *get_net_video_rec_handler(void)
{
    return (void *)&net_rec_handler;
}

void *get_video_rec0_handler(void)
{
    return (void *)__this->video_rec0;
}

u8 get_net_video_rec_state(void)
{
    return __this_net->is_open;
}

u8 set_net_video_rec_state(u8 state)
{
    __this_net->is_open = state;
}

void *get_video_rec1_handler(void)
{
#ifdef CONFIG_VIDEO1_ENABLE
    return (void *)__this->video_rec1;
#endif
#ifdef CONFIG_VIDEO2_ENABLE
    return (void *)__this->video_rec2;
#endif
    return NULL;
}
#ifdef CONFIG_VIDEO2_ENABLE
void *get_video_rec2_handler(void)
{
    return (void *)__this->video_rec2;
}
#endif // CONFIG_VIDEO1_ENABLE
void get_video_state_func()
{
    printf("============= __this->state:%d\n", __this->state);
}

int net_video_rec_state(void)//获取录像状态，返回值大于0（1280/640）成功，失败 0
{
    u8 res = db_select("res");
    if (__this && __this->state == VIDREC_STA_START) {
        return net_rec_pix_w[res];
    }
    return 0;
}
int net_video_rec_uvc_online(void)
{
    return dev_online("uvc");
}
int net_pkg_get_video_size(int *width, int *height)
{
#if defined CONFIG_VIDEO0_ENABLE || defined CONFIG_VIDEO1_ENABLE
    u8 id = __this_net->video_id ? 1 : 0;
#elif (defined CONFIG_VIDEO4_ENABLE)
    u8 id = __this_net->video_id == 4 ? 5 : 4;
#else
    u8 id = 0;
#endif
    *width = __this_net->net_videoreq[id].rec.width;
    *height = __this_net->net_videoreq[id].rec.height;
    return 0;
}
int net_video_buff_set_frame_cnt(void)
{
#ifdef NET_VIDEO_BUFF_FRAME_CNT
    return NET_VIDEO_BUFF_FRAME_CNT;
#else
    return 0;
#endif
}
u8 net_video_rec_get_drop_fp(void)
{
#ifdef NET_VIDEO_REC_DROP_REAl_FP
    return NET_VIDEO_REC_DROP_REAl_FP;
#else
    return 0;
#endif
}
u8 net_video_rec_get_lose_fram(void)
{
#ifdef NET_VIDEO_REC_LOSE_FRAME_CNT
    return NET_VIDEO_REC_LOSE_FRAME_CNT;
#else
    return 0;
#endif
}
u8 net_video_rec_get_send_fram(void)
{
#ifdef NET_VIDEO_REC_SEND_FRAME_CNT
    return  NET_VIDEO_REC_SEND_FRAME_CNT;
#else
    return 0;
#endif
}
int net_video_rec_get_fps(void)
{
    return 25;
}

void net_video_rec_post_msg(const char *msg, ...)
{
}

void net_video_rec_fmt_notify(void)
{
    char buf[32];
#if defined CONFIG_ENABLE_VLIST
    /* FILE_DELETE(NULL, 0); */
    sprintf(buf, "frm:1");
    CTP_CMD_COMBINED(NULL, CTP_NO_ERR, "FORMAT", "NOTIFY", buf);
#endif
}

//只用于8.3规则文件名
static void change_file_name_suffix(char *file_name)
{

    char suffix_buf[3];
    if (!file_name) {
        return;
    }

    int file_name_len = strlen(file_name);
    if (strlen(file_name) > 11) {
        printf("no change file_name:%s", file_name);
        return;
    }
    suffix_buf[0] = file_name[file_name_len - 3];
    suffix_buf[1] = file_name[file_name_len - 2];
    suffix_buf[2] = file_name[file_name_len - 1];

    file_name[file_name_len - 3] = '.';
    file_name[file_name_len - 2] = suffix_buf[0];
    file_name[file_name_len - 1] = suffix_buf[1];
    file_name[file_name_len]   = suffix_buf[2];
    file_name[file_name_len + 1]  = 0;

}

char *video_rec_finish_get_name(FILE *fd, int index, u8 is_emf)  //index ：video0前视0，video1则1，video2则2 , is_emf 紧急文件
{
    static char path[128] ALIGNE(32) = {0};
    u8 name[15];
    u8 *dir;
    int err;

#ifdef CONFIG_ENABLE_VLIST
    memset(path, 0, sizeof(path));
    err = fget_name(fd, name, sizeof(name));
#ifdef CONFIG_JLFAT_ENABLE
    change_file_name_suffix(name);
#endif

    if (err <= 0) {
        return NULL;
    }

    if (index < 0) {
        strcpy(path, name);
        return path;
    }
    switch (index) {
    case 0:
        dir = CONFIG_REC_PATH_0;
        break;
    case 1:
        dir = CONFIG_REC_PATH_1;
        break;
    case 2:
        dir = CONFIG_REC_PATH_2;
        break;
    case 3:
        dir = CONFIG_REC_PATH_2;
        break;
    case 4:
        dir = CONFIG_REC_PATH_4;
        break;
    case 5:
        dir = CONFIG_REC_PATH_5;
        break;

    default:
        return NULL;
    }
#ifdef CONFIG_EMR_DIR_ENABLE
    if (is_emf) {
        sprintf(path, "%s%s%s", dir, CONFIG_EMR_REC_DIR, name);
    } else
#endif
    {
        sprintf(path, "%s%s", dir, name);
    }

    return  path;
#else
    return NULL;
#endif
}

int video_rec_finish_notify(char *path)
{
    int err = 0;

    if (__this_net->video_rec_err) {
        __this_net->video_rec_err = FALSE;
        return 0;
    }
    os_mutex_pend(&net_vdrec_mutex, 0);
    FILE_LIST_ADD(0, (const char *)path, 0);
    os_mutex_post(&net_vdrec_mutex);
    return err;
}
int video_rec_delect_notify(FILE *fd, int id)
{
    int err = 0;
    if (__this_net->video_rec_err) {
        __this_net->video_rec_err = FALSE;
        return 0;
    }
#ifdef CONFIG_ENABLE_VLIST
    char *delect_path;
    os_mutex_pend(&net_vdrec_mutex, 0);
    char *path = video_rec_finish_get_name(fd, id, 0);
    if (path == NULL) {
        os_mutex_post(&net_vdrec_mutex);
        return -1;
    }

    FILE_DELETE((const char *)path, 0);
    os_mutex_post(&net_vdrec_mutex);
#endif

    return err;
}

int video_rec_err_notify(const char *method)
{
    int err = 0;
    char *err_path;
    os_mutex_pend(&net_vdrec_mutex, 0);
    if (method && !strcmp((const char *)method, "VIDEO_REC_ERR")) {
        __this_net->video_rec_err = TRUE;
    }
    os_mutex_post(&net_vdrec_mutex);
    return err;
}

int video_rec_state_notify(void)
{
    int err = 0;
    net_vd_msg[0] = NET_VIDREC_STATE_NOTIFY;
    err = os_taskq_post_msg(NET_VIDEO_REC_SERVER_NAME, 1, (int)net_vd_msg);
    return err;
}

int video_rec_start_notify(void)
{
    return net_video_rec_control(0);//启动录像之前需要关闭实时流
}
int video_rec_all_stop_notify(void)
{
    int err = 0;
    net_vd_msg[0] = NET_VIDREC_STA_STOP;
    err = os_taskq_post_msg(NET_VIDEO_REC_SERVER_NAME, 1, (int)net_vd_msg);
    return err;
}
void net_video_rec_status_notify(void)
{
    char buf[128];
    u8 sta = 0;
    if (!dev_online(SDX_DEV)) {
        return;
    }

    if (__this->state == VIDREC_STA_START) {
        sta = 1;
    }
    memset(buf, 0, sizeof(buf));
    sprintf(buf, "status:%d", sta);
    CTP_CMD_COMBINED(NULL, CTP_NO_ERR, "VIDEO_CTRL", "NOTIFY", buf);
}
int net_video_rec_event_notify(void)
{
    char buf[128];
    if (dev_online("uvc")) {
        sprintf(buf, "status:1,h:%d,w:%d,fps:%d,rate:%d,format:1", 480, 640, net_video_rec_get_fps(), net_video_rec_get_audio_rate());
        CTP_CMD_COMBINED(NULL, CTP_NO_ERR, "THIRD_VIDEO_STATUS", "NOTIFY", buf);
    } else {
        strcpy(buf, "status:0");
        CTP_CMD_COMBINED(NULL, CTP_NO_ERR, "THIRD_VIDEO_STATUS", "NOTIFY", buf);
    }
    return 0;
}

#ifdef CONFIG_VIDEO2_ENABLE
int net_video2_rec_event_notify(void)
{
    char buf[128];
    sprintf(buf, "status:1,h:%d,w:%d,fps:%d,rate:%d,format:0", 480, 640, net_video_rec_get_fps(), net_video_rec_get_audio_rate());
    CTP_CMD_COMBINED(NULL, CTP_NO_ERR, "THIRD_VIDEO_STATUS", "NOTIFY", buf);
    return 0;
}
#endif // CONFIG_VIDEO2_ENABLE
int video_rec_sd_event_ctp_notify(char state)
{
    char buf[128];
    printf("~~~ : %s , %d\n\n", __func__, state);

    /* #if defined CONFIG_ENABLE_VLIST */
    /* if (!state) { */
    /* FILE_REMOVE_ALL(); */
    /* } */
    /* #endif */
    if (state) {
        u32 space = 0;
        struct vfs_partition *part = NULL;
        if (storage_device_ready() == 0) {
            msleep(200);
            if (storage_device_ready()) {
                goto sd_scan;
            }
            printf("---%s , storage_device_not_ready !!!!\n\n", __func__);
            CTP_CMD_COMBINED(NULL, CTP_SD_OFFLINE, "TF_CAP", "NOTIFY", CTP_SD_OFFLINE_MSG);
        } else {
sd_scan:
            part = fget_partition(CONFIG_ROOT_PATH);
            fget_free_space(CONFIG_ROOT_PATH, &space);
            sprintf(buf, "left:%d,total:%d", space / 1024, part->total_size / 1024);
            CTP_CMD_COMBINED(NULL, CTP_NO_ERR, "TF_CAP", "NOTIFY", buf);
        }
    } else {
        /* sprintf(buf, "status:%d", 0); */
        /* CTP_CMD_COMBINED(NULL, CTP_NO_ERR, "VIDEO_CTRL", "NOTIFY", buf); */
    }
    sprintf(buf, "online:%d", state);
    CTP_CMD_COMBINED(NULL, CTP_NO_ERR, "SD_STATUS", "NOTIFY", buf);
    return 0;
}

//NET USE API
static void video_rec_get_app_status(struct intent *it)
{
    it->data = (const char *)__this;
    it->exdata = (u32)__this_net;
}
static void video_rec_get_path(struct intent *it)
{

    u8  buf[15];
#ifdef CONFIG_VIDEO0_ENABLE

    if (!strcmp(it->data, "video_rec0") && __this->file[0] != NULL) {
        fget_name((FILE *)__this->file[0], buf, sizeof(buf));
        sprintf(file_str, CONFIG_REC_PATH_0"%s", buf);
        it->data = file_str;
    }

#elif (defined CONFIG_VIDEO4_ENABLE)

    if (!strcmp(it->data, "video_rec4") && __this->file[4] != NULL) {
        fget_name((FILE *)__this->file[4], buf, sizeof(buf));
        sprintf(file_str, CONFIG_REC_PATH_4"%s", buf);
        it->data = file_str;
    }

#endif

#if (defined CONFIG_VIDEO1_ENABLE) || (defined CONFIG_VIDEO2_ENABLE) || (defined CONFIG_VIDEO5_ENABLE)
    if (!strcmp(it->data, "video_rec1") && __this->file[1] != NULL) {
        fget_name((FILE *)__this->file[1], buf, sizeof(buf));
        sprintf(file_str, CONFIG_REC_PATH_1"%s", buf);
        it->data = file_str;
    } else if (!strcmp(it->data, "video_rec2") && __this->file[2] != NULL) {
        fget_name((FILE *)__this->file[2], buf, sizeof(buf));
        sprintf(file_str, CONFIG_REC_PATH_2"%s", buf);
        it->data = file_str;
    } else if (!strcmp(it->data, "video_rec5") && __this->file[5] != NULL) {
        fget_name((FILE *)__this->file[5], buf, sizeof(buf));
        sprintf(file_str, CONFIG_REC_PATH_5"%s", buf);
        it->data = file_str;
    } else
#endif
    {
        puts("get file name fail\n");
        it->data = NULL;
    }
    printf("file %s \n", it->data);
}
static void ctp_cmd_notity(const char *path)
{
#if defined CONFIG_ENABLE_VLIST
    FILE_LIST_ADD(0, path, 0);
#endif
}

int net_video_rec_get_audio_rate()
{
    return VIDEO_REC_AUDIO_SAMPLE_RATE;
}
static int video_cyc_file(u32 sel)
{
    /*
        struct server *server = NULL;
        union video_req req = {0};
        if (sel == 0) {
            server = __this->video_rec0;

            req.rec.channel = 0;
        } else if (sel == 1) {
            server = __this->video_rec1;
            req.rec.channel = 1;
        } else {
            server = __this->video_rec2;
            req.rec.channel = 2;
        }
        if ((__this->state != VIDREC_STA_START) || (server == NULL)) {
            return -EINVAL;
        }

        req.rec.state   = VIDEO_STATE_CYC_FILE;
        req.rec.cyc_file = 1;
        int err = server_request(server, VIDEO_REQ_REC, &req);
        if (err != 0) {
            return -EINVAL;
        }
    */
    return 0;
}

static int set_label_config(u16 image_width, u16 image_height, u32 font_color,
                            struct video_text_osd *label)
{
    static char label_format[128] ALIGNE(64) = "yyyy-nn-dd hh:mm:ss";
    if (!label) {
        return 0;
    }

    /*
     *日期标签设置
     *1920以下使用 16x32字体大小，以上使用32x64字体
     */
#ifdef __CPU_AC521x__
    label->direction = 1;
#else
    label->direction = 0;
#endif
    if (image_width > 1920) {
        return -1;

    } else {
        label->font_w = 16;
        label->font_h = 32;
        label->text_format = label_format;
        label->font_matrix_table = osd_str_total;
        label->font_matrix_base = osd_str_matrix;
        label->font_matrix_len = sizeof(osd_str_matrix);
    }
    label->color[0] = font_color;

    label->x = (image_width - strlen(label_format) * label->font_w) / 64 * 64;
    label->y = (image_height - label->font_h - 16) / 16 * 16;


    return 0;
}

int video_rec_cap_photo(char *buf, int len)
{
    u32 *flen;
    u8 *cap_img;
    if (__this_net->cap_image) {
        cap_img = &__this_net->cap_image;
    } else {
        cap_img = &__this_strm->cap_image;
    }
    if (*cap_img && __this->cap_buf) {
        *cap_img = FALSE;
        flen = __this->cap_buf;
        memcpy(__this->cap_buf + 4, buf, len);
        *flen = len;
    }
    return 0;
}
static int net_video_rec_take_photo(void (*callback)(char *buffer, int len))
{
    struct server *server = NULL;
    void *cap_buf = NULL;
    union video_req req = {0};
    int err;
    char *path;
    u32 *image_len;
    char buf[128] = {0};
    char video_dev_name[20] = {0};
    char name_buf[20];
    struct video_text_osd text_osd;
    u8 server_open_flag = 0;
    /*不开实时流不能拍照*/
    if (!(__this_strm->state == VIDREC_STA_START)    &&
        !(__this_net->net_state == VIDREC_STA_START) &&
        !(__this_net->net_state1 == VIDREC_STA_START) &&
        !(__this_net->net_state2 == VIDREC_STA_START) &&
        !(__this_net->net_state4 == VIDREC_STA_START) &&
        !(__this_net->net_state5 == VIDREC_STA_START)) {
        goto exit;
    }

    __this_net->cap_image = FALSE;
    __this_strm->cap_image = FALSE;

    if ((__this_net->net_state == VIDREC_STA_START || __this_net->net_state1 == VIDREC_STA_START || __this_net->net_state2 == VIDREC_STA_START || __this_net->net_state4 == VIDREC_STA_START || __this_net->net_state5 == VIDREC_STA_START)) {
        printf("%s   %d\n", __func__, __LINE__);

        switch (__this_net->video_id) {
        case 0:
            server = __this_net->net_video_rec;
            req.icap.path = CONFIG_REC_PATH_0"IMG_****.JPG";
            path = CONFIG_REC_PATH_0;
            break;
        case 1:
            server = __this_net->net_video_rec1;
            req.icap.path = CONFIG_REC_PATH_1"IMG_****.JPG";
            path = CONFIG_REC_PATH_1;
            break;
        case 4:
            server = __this_net->net_video_rec4;
            req.icap.path = CONFIG_REC_PATH_4"IMG_****.JPG";
            path = CONFIG_REC_PATH_4;
            break;
        case 5:
            server = __this_net->net_video_rec5;
            req.icap.path = CONFIG_REC_PATH_5"IMG_****.JPG";
            path = CONFIG_REC_PATH_5;
            break;
        default:
            server = __this_net->net_video_rec2;
            req.icap.path = CONFIG_REC_PATH_2"IMG_****.JPG";
            path = CONFIG_REC_PATH_2;
            break;
        }
        req.icap.width =  __this_net->net_videoreq[__this_net->video_id].rec.width;
        req.icap.height = __this_net->net_videoreq[__this_net->video_id].rec.height;
        req.icap.image_state = 1;

        printf("%s   %d\n", __func__, __LINE__);
    } else if (__this_strm->state == VIDREC_STA_START) {
        printf("%s   %d\n", __func__, __LINE__);
        switch (__this_strm->video_id) {
        case 0:
            server = __this_strm->video_rec0;
            req.icap.path = CONFIG_REC_PATH_0"IMG_****.JPG";
            path = CONFIG_REC_PATH_0;
            break;
        case 1:
            server = __this_strm->video_rec1;
            req.icap.path = CONFIG_REC_PATH_1"IMG_****.JPG";
            path = CONFIG_REC_PATH_1;
            break;
        case 4:
            server = __this_strm->video_rec4;
            req.icap.path = CONFIG_REC_PATH_4"IMG_****.JPG";
            path = CONFIG_REC_PATH_4;
            break;
        case 5:
            server = __this_strm->video_rec5;
            req.icap.path = CONFIG_REC_PATH_5"IMG_****.JPG";
            path = CONFIG_REC_PATH_5;
            break;
        default:
            server = __this_strm->video_rec2;
            req.icap.path = CONFIG_REC_PATH_2"IMG_****.JPG";
            path = CONFIG_REC_PATH_2;
            break;
        }
        req.icap.width = __this_strm->width;
        req.icap.height = __this_strm->height;
        printf("%s   %d\n", __func__, __LINE__);
    } else {
        /*目前不使用*/
        /* printf("%s   %d\n", __func__, __LINE__); */
        /* req.icap.path = __this->video_rec0 ? CONFIG_REC_PATH_0"IMG_****.JPG" : CONFIG_REC_PATH_1"IMG_****.JPG"; */
        /* path = __this->video_rec0 ? CONFIG_REC_PATH_0 : CONFIG_REC_PATH_1; */
        /* req.icap.width = 1280; */
        /* req.icap.height = 720; */
        /* sprintf(video_dev_name, "video%d.3", __this_strm->video_id); */
        /* server = server_open("video_server", video_dev_name); */
        /* server_open_flag = server ? 1 : 0; */
        printf("%s   %d\n", __func__, __LINE__);
    }


    printf("req.icap.width:%d\n", req.icap.width);
    if (!server) {
        printf("\nserver open err !!!\n");
        goto exit;
    }
    cap_buf = (u8 *)malloc(TAKE_PHOTO_MEM_LEN);
    if (!cap_buf) {
        printf("\n %s malloc fail\n", __func__);
        goto exit;
    }
    req.icap.buf_size = TAKE_PHOTO_MEM_LEN;
    req.icap.quality = VIDEO_MID_Q;
    req.icap.buf = cap_buf;
    req.icap.file_name = name_buf;


    req.rec.text_osd = NULL;
    req.rec.graph_osd = NULL;
    req.icap.text_label = NULL;
    /*
     * osd 相关的参数，注意坐标位置，x要64对齐，y要16对齐,底下例子是根据图像大小偏移到右下
     */
    /* if (db_select("dat")) { */
    /* req.icap.text_label = &text_osd; */
    /* set_label_config(req.icap.width, req.icap.height, 0xe20095, req.icap.text_label); */
    /* } */


    if (callback) {
        image_len = cap_buf;
        req.icap.save_cap_buf = TRUE;//保存到cap_buff写TRUE，数据格式，前4字节为数据长度，4字节后为有效数据
    }

    err = server_request(server, VIDEO_REQ_IMAGE_CAPTURE, &req);
    if (err != 0) {
        printf("\ntake photo err\n");
        goto exit;
    }
    printf("%s   %d\n", __func__, __LINE__);

    if (callback) {
        if (image_len && cap_buf) {
            callback(cap_buf + 4, *image_len);
        } else {
            callback(NULL, 0);
        }
    } else {
#if defined CONFIG_ENABLE_VLIST
        sprintf(buf, "%s%s", path, req.icap.file_name);
        FILE_LIST_ADD(0, buf, 0);
#endif
    }
    printf("%s   %d\n", __func__, __LINE__);
    if (server_open_flag) {
        server_close(server);
    }
    printf("%s   %d\n", __func__, __LINE__);
    if (cap_buf) {
        free(cap_buf);
    }
    printf("%s   %d\n", __func__, __LINE__);
    return 0;
exit:
#if defined CONFIG_ENABLE_VLIST
    CTP_CMD_COMBINED(NULL, CTP_REQUEST, "PHOTO_CTRL", "NOTIFY", CTP_REQUEST_MSG);
#endif
    if (callback) {
        callback(NULL, 0);
    }
    if (server_open_flag) {
        server_close(server);
    }
    if (cap_buf) {
        free(cap_buf);
    }
    return -EINVAL;
}



extern int atoi(const char *);
static void rt_stream_cmd_analysis(u8 chl,  u32 add)
{
    char *key;
    char *value;
    struct rt_stream_app_info *info = (struct rt_stream_app_info *)add;

    __this_net->net_videoreq[chl].rec.width = 640;
    __this_net->net_videoreq[chl].rec.height = 480;
    __this_net->net_videoreq[chl].rec.format = 0;
    __this_net->net_videoreq[chl].rec.fps = net_video_rec_get_fps();
    __this_net->net_videoreq[chl].rec.real_fps = net_video_rec_get_fps();
    __this_net->priv = info->priv;
    printf(">>>>>>>> ch %d , info->type : %d ,w:%d , h:%d\n\n", chl, info->type, info->width, info->height);

}

static void net_video_rec_set_bitrate(unsigned int bits_rate)
{
    union video_req req = {0};

    req.rec.channel = __this_net->channel;

    req.rec.state = VIDEO_STATE_RESET_BITS_RATE;
    req.rec.abr_kbps = bits_rate;
#if (defined CONFIG_VIDEO0_ENABLE)
    server_request(__this_net->net_video_rec, VIDEO_REQ_REC, &req);
#elif (defined CONFIG_VIDEO4_ENABLE)
    server_request(__this_net->net_video_rec4, VIDEO_REQ_REC, &req);
#endif
}

/*码率控制，根据具体分辨率设置*/
static int net_video_rec_get_abr(u32 width)
{
    if (width <= 720) {
        return 3000;
    } else if (width <= 1280) {
        return 3000;
    } else {
        return 3000;
    }
}

static void net_rec_dev_server_event_handler(void *priv, int argc, int *argv)
{
    int mark = 2;
    struct intent it;
    /*
     *该回调函数会在录像过程中，写卡出错被当前录像APP调用，例如录像过程中突然拔卡
     */
    switch (argv[0]) {
    case VIDEO_SERVER_UVM_ERR:
        log_e("APP_UVM_DEAL_ERR\n");
        break;
    case VIDEO_SERVER_PKG_ERR:
        log_e("video_server_pkg_err\n");
        if (__this->state == VIDREC_STA_START) {
            net_video_rec_control(0);
        }
        init_intent(&it);
        it.data = &mark;
        net_video_rec_stop(1);
        break;
    case VIDEO_SERVER_PKG_END:
        if (db_select("cyc")) {
            /*video_rec_savefile((int)priv);*/
        } else {
            net_video_rec_control(0);
        }
        break;
    case VIDEO_SERVER_NET_ERR:
        log_e("\nVIDEO_SERVER_NET_ERR\n");
        init_intent(&it);
        it.data = &mark;
        net_video_rec_stop(1);
        __this_net->is_open = FALSE;
        break;
    default :
        /*log_e("unknow rec server cmd %x , %x!\n", argv[0], (int)priv);*/
        break;
    }
}

static int net_video_rec0_start()
{
    int err;
    union video_req req = {0};
    struct video_text_osd text_osd;
    struct video_graph_osd graph_osd;
    u16 max_one_line_strnum;
    u16 osd_line_num;
    u16 osd_max_heigh;
    char buf[128];
    u8 res = db_select("res");
    if (__this->video_rec0) {
        printf("use in same channel");
        __this_net->net_video_rec = __this->video_rec0;
    }


    if (!__this_net->net_video_rec) {
        __this_net->net_video_rec = server_open("video_server", "video0.1");
        if (!__this_net->net_video_rec) {
            return VREC_ERR_V0_SERVER_OPEN;
        }
        server_register_event_handler(__this_net->net_video_rec, (void *)0, net_rec_dev_server_event_handler);
    }
    /*
     *通道号，分辨率，封装格式，写卡的路径
     */

    req.rec.channel     = 1;//用于区分任务
    req.rec.camera_type = VIDEO_CAMERA_NORMAL;
    req.rec.width       = __this_net->net_videoreq[0].rec.width;
    req.rec.height      = __this_net->net_videoreq[0].rec.height;
    req.rec.format      = USER_VIDEO_FMT_AVI;
    printf(">>>>>>width=%d    height=%d\n\n\n\n", __this_net->net_videoreq[0].rec.width, __this_net->net_videoreq[0].rec.height);
    req.rec.state       = VIDEO_STATE_START;
    //req.rec.file        = __this->file[0];  //实时流无需写卡

#if THREE_WAY_DOUBLE_RAW
    req.rec.double_raw      = 1;
#endif


    /*
     *帧率为0表示使用摄像头的帧率
     */
    req.rec.quality     = VIDEO_MID_Q;
    req.rec.fps         = 0;
    req.rec.real_fps    = net_video_rec_get_fps();

    /*
     *采样率，通道数，录像音量，音频使用的循环BUF,录不录声音
     */
    req.rec.audio.sample_rate = VIDEO_REC_AUDIO_SAMPLE_RATE;
    req.rec.audio.channel   = 1;
    req.rec.audio.volume    = __this_net->net_video0_art_on ? AUDIO_VOLUME : 0;
    req.rec.audio.buf = __this_net->audio_buf;
    req.rec.audio.buf_len = NET_AUDIO_BUF_SIZE;

    req.rec.pkg_mute.aud_mute = !db_select("mic");

    /*
     *码率，I帧和P帧比例，必须是偶数（当录MOV的时候才有效）,
     *roio_xy :值表示宏块坐标， [6:0]左边x坐标 ，[14:8]右边x坐标，[22:16]上边y坐标，[30:24]下边y坐标,写0表示1个宏块有效
     *roio_ratio : 区域比例系数
     */
    req.rec.abr_kbps = net_video_rec_get_abr(req.rec.width);

    /*
     * osd 相关的参数，注意坐标位置，x要64对齐，y要16对齐,底下例子是根据图像大小偏移到右下
     */

    text_osd.font_w = 16;
    text_osd.font_h = 32;
    max_one_line_strnum = strlen(video_rec_osd_buf);//21;
    osd_line_num = 1;
    /*   if (db_select("num")) { */
    /* osd_line_num = 2; */
    /* } */
    osd_max_heigh = (req.rec.height == 1088) ? 1080 : req.rec.height ;
    text_osd.x = (req.rec.width - max_one_line_strnum * text_osd.font_w) / 64 * 64;
    text_osd.y = (osd_max_heigh - text_osd.font_h * osd_line_num) / 16 * 16;
    /* text_osd.color[0] = 0xe20095; */
    /* text_osd.bit_mode = 1; */
    text_osd.color[0] = 0x057d88;
    text_osd.color[1] = 0xe20095;
    text_osd.color[2] = 0xe20095;
    text_osd.bit_mode = 2;
    text_osd.text_format = video_rec_osd_buf;
    text_osd.font_matrix_table = osd_str_total;
    /*     text_osd.font_matrix_base = osd_str_matrix; */
    /* text_osd.font_matrix_len = sizeof(osd_str_matrix); */
    text_osd.font_matrix_base = osd2_str_matrix;
    text_osd.font_matrix_len = sizeof(osd2_str_matrix);


    text_osd.direction = 1;

    /* if (db_select("dat")) { */
    req.rec.text_osd = &text_osd;
    req.rec.graph_osd = NULL;//&graph_osd;
    /* } */

    req.rec.buf = __this_net->net_v0_fbuf;
    req.rec.buf_len = NET_VREC0_FBUF_SIZE;

    req.rec.cycle_time = db_select("cyc");
    if (req.rec.cycle_time == 0) {
        req.rec.cycle_time = 5;
    }
    req.rec.cycle_time = req.rec.cycle_time * 60;

    struct sockaddr_in *addr = ctp_srv_get_cli_addr(__this_net->priv);
    if (!addr) {
        addr = cdp_srv_get_cli_addr(__this_net->priv);
    }
#if (defined CONFIG_NET_UDP_ENABLE)
    sprintf(req.rec.net_par.netpath, "udp://%s:%d"
            , inet_ntoa(addr->sin_addr.s_addr)
            , _FORWARD_PORT);
#elif (defined CONFIG_NET_TCP_ENABLE)
    sprintf(req.rec.net_par.netpath, "tcp://%s:%d"
            , inet_ntoa(addr->sin_addr.s_addr)
            , _FORWARD_PORT);
#elif (defined CONFIG_NET_USR_ENABLE)
    sprintf(req.rec.net_par.netpath, "usr://%s", NET_USR_PATH);
#endif
    printf("\n @@@@@@ path = %s\n", req.rec.net_par.netpath);
    //数据外引，用于网络
    req.rec.target = VIDEO_TO_OUT;
    req.rec.out.path = req.rec.net_par.netpath;
    req.rec.out.arg  = NULL ;
    req.rec.out.open = stream_open;
    req.rec.out.send = stream_write;
    req.rec.out.close = stream_close;
    req.rec.online  = 1;

#if CONFIG_NET_VDIEO_GAP_ENABLE
    req.rec.tlp_time = db_select("gap");
    if (req.rec.tlp_time) {
        req.rec.real_fps = 1000 / req.rec.tlp_time;
        req.rec.pkg_fps = video_rec_get_fps();

        //audio
        req.rec.audio.sample_rate = 0;
        req.rec.audio.channel 	= 0;
        req.rec.audio.volume    = 0;
        req.rec.audio.buf = 0;
        req.rec.audio.buf_len = 0;
    }
#endif

    err = server_request(__this_net->net_video_rec, VIDEO_REQ_REC, &req);

    if (err != 0) {
        puts("\n\n\nstart rec err\n\n\n");
        return VREC_ERR_V0_REQ_START;
    }

    net_video_rec_set_bitrate(net_video_rec_get_abr(req.rec.width));

    return 0;
}



static int net_video_rec0_stop(u8 close)
{
    union video_req req = {0};
    int err;
    __this_net->net_state = VIDREC_STA_STOPING;
    if (__this_net->net_video_rec) {
        puts("\nnet video rec0 stop\n");
        req.rec.channel = 1;
        req.rec.state = VIDEO_STATE_STOP;
        err = server_request(__this_net->net_video_rec, VIDEO_REQ_REC, &req);
        if (err != 0) {
            printf("\nstop rec err 0x%x\n", err);
            return VREC_ERR_V0_REQ_STOP;
        }
        net_video_rec_set_bitrate(video_rec_get_abr(__this_net->net_videoreq[0].rec.width));
        if (close) {
            server_close(__this_net->net_video_rec);
            __this_net->net_video_rec = NULL;
        }

    }

    __this_net->net_state = VIDREC_STA_STOP;

    puts("\nnet video rec0 stop end\n");

    return 0;
}

static int net_video_rec1_start()
{
    int err;
    union video_req req = {0};
    struct video_text_osd text_osd;
    struct video_graph_osd graph_osd;
    u16 max_one_line_strnum;
    u16 osd_line_num;
    u16 osd_max_heigh;

    req.rec.width 	= __this_net->net_videoreq[1].rec.width;
    req.rec.height 	= __this_net->net_videoreq[1].rec.height;
#if THREE_WAY_DOUBLE_RAW
    req.rec.double_raw      = 1;
#endif

#ifdef CONFIG_VIDEO1_ENABLE
    puts("start_video_rec1 \n");

    if (__this->video_rec1) {
        __this_net->net_video_rec1 = __this->video_rec1;
    }
    if (!__this_net->net_video_rec1) {
        __this_net->net_video_rec1 = server_open("video_server", "video1.1");
        if (!__this_net->net_video_rec1) {
            return VREC_ERR_V1_SERVER_OPEN;
        }
        server_register_event_handler(__this_net->net_video_rec1, (void *)1, net_rec_dev_server_event_handler);
    }
    req.rec.camera_type = VIDEO_CAMERA_NORMAL;
    req.rec.file    = __this->file[1];
    req.rec.IP_interval = 0;
    req.rec.online  = 1;
    __this_net->video_id = 1;
#endif

#ifdef CONFIG_VIDEO3_ENABLE
    char name[12];
    void *uvc_fd;
    if (__this->video_rec2) {
        __this_net->net_video_rec1 = __this->video_rec2;
    }

    /* struct uvc_capability uvc_cap; */

    puts("start_video_rec2 \n");
    if (!__this_net->net_video_rec1) {
        sprintf(name, "video10.%d", __this->uvc_id);
        __this_net->net_video_rec1 = server_open("video_server", name);
        if (!__this_net->net_video_rec1) {
            return -EINVAL;
        }
        server_register_event_handler(__this_net->net_video_rec1, (void *)1, net_rec_dev_server_event_handler);
    }
    req.rec.camera_type = VIDEO_CAMERA_UVC;
    req.rec.three_way_type = 0;
    req.rec.IP_interval = 0;
    /* req.rec.width 	= UVC_ENC_WIDTH; */
    /* req.rec.height 	= UVC_ENC_HEIGH; */
    __this->uvc_width = req.rec.width;
    __this->uvc_height = req.rec.height;
    req.rec.uvc_id = __this->uvc_id;
    req.rec.file    = __this->file[2];
    __this_net->video_id = 1;
    req.rec.online  = 0;
#endif
    /*
     *通道号，分辨率，封装格式，写卡的路径
     */
    req.rec.channel = __this_net->channel = 1;
    req.rec.format  = USER_VIDEO_FMT_AVI;
    req.rec.state 	= VIDEO_STATE_START;

    /*
     *帧率为0表示使用摄像头的帧率
     */
    req.rec.quality     = VIDEO_MID_Q;
    req.rec.fps         = 0;
    req.rec.real_fps    = net_video_rec_get_fps();

    /*
     *采样率，通道数，录像音量，音频使用的循环BUF,录不录声音
     */
    req.rec.audio.sample_rate = VIDEO_REC_AUDIO_SAMPLE_RATE;
    req.rec.audio.channel   = 1;
    req.rec.audio.volume    = __this_net->net_video1_art_on ? AUDIO_VOLUME : 0;
    req.rec.audio.buf = __this_net->audio_buf;
    req.rec.audio.buf_len = NET_AUDIO_BUF_SIZE;
    req.rec.pkg_mute.aud_mute = !db_select("mic");

    /*
     *码率，I帧和P帧比例，必须是偶数（当录MOV的时候才有效）,
     *roio_xy :值表示宏块坐标， [6:0]左边x坐标 ，[14:8]右边x坐标，[22:16]上边y坐标，[30:24]下边y坐标,写0表示1个宏块有效
     *roio_ratio : 区域比例系数
     */
    req.rec.abr_kbps = net_video_rec_get_abr(req.rec.width);

    /*
     * osd 相关的参数，注意坐标位置，x要64对齐，y要16对齐,底下例子是根据图像大小偏移到右下
     */
    /* memcpy(video_rec_osd_buf, osd_str_buf, strlen(osd_str_buf));  */
    text_osd.font_w = 16;
    text_osd.font_h = 32;
    max_one_line_strnum = strlen(video_rec_osd_buf);//21;
    osd_line_num = 1;
    /* if (db_select("num")) { */
    /* osd_line_num = 2; */
    /* } */
    osd_max_heigh = (req.rec.height == 1088) ? 1080 : req.rec.height ;
    text_osd.x = (req.rec.width - max_one_line_strnum * text_osd.font_w) / 64 * 64;
    text_osd.y = (osd_max_heigh - text_osd.font_h * osd_line_num) / 16 * 16;
    /*     text_osd.color[0] = 0xe20095; */
    /* text_osd.bit_mode = 1; */
    text_osd.color[0] = 0x057d88;
    text_osd.color[1] = 0xe20095;
    text_osd.color[2] = 0xe20095;
    text_osd.bit_mode = 2;
    text_osd.text_format = video_rec_osd_buf;
    text_osd.font_matrix_table = osd_str_total;
    /*     text_osd.font_matrix_base = osd_str_matrix; */
    /* text_osd.font_matrix_len = sizeof(osd_str_matrix); */
    text_osd.font_matrix_base = osd2_str_matrix;
    text_osd.font_matrix_len = sizeof(osd2_str_matrix);


    text_osd.direction = 1;

    if (db_select("dat")) {
        req.rec.text_osd = &text_osd;
        req.rec.graph_osd = NULL;//&graph_osd;
    }

    req.rec.buf = __this_net->net_v0_fbuf;
    req.rec.buf_len = NET_VREC0_FBUF_SIZE;

    /* req.rec.cycle_time = 3 * 60; */
    req.rec.cycle_time = db_select("cyc");
    if (req.rec.cycle_time == 0) {
        req.rec.cycle_time = 5;
    }
    req.rec.cycle_time = req.rec.cycle_time * 60;



    struct sockaddr_in *addr = ctp_srv_get_cli_addr(__this_net->priv);
    if (!addr) {
        addr = cdp_srv_get_cli_addr(__this_net->priv);
    }
#if (defined CONFIG_NET_UDP_ENABLE)
    sprintf(req.rec.net_par.netpath, "udp://%s:%d"
            , inet_ntoa(addr->sin_addr.s_addr)
            , _THIRD_PORT);
#elif (defined CONFIG_NET_TCP_ENABLE)
    sprintf(req.rec.net_par.netpath, "tcp://%s:%d"
            , inet_ntoa(addr->sin_addr.s_addr)
            , _THIRD_PORT);
#elif (defined CONFIG_NET_USR_ENABLE)
    sprintf(req.rec.net_par.netpath, "usr://%s", NET_USR_PATH);
#endif
    printf("\n @@@@@@ path = %s\n", req.rec.net_par.netpath);
    //数据外引，用于网络
    req.rec.target = VIDEO_TO_OUT;
    req.rec.out.path = req.rec.net_par.netpath;
    req.rec.out.arg  = NULL ;
    req.rec.out.open = stream_open;
    req.rec.out.send = stream_write;
    req.rec.out.close = stream_close;

#if CONFIG_NET_VDIEO_GAP_ENABLE
    req.rec.tlp_time = db_select("gap");
    if (req.rec.tlp_time) {
        req.rec.real_fps = 1000 / req.rec.tlp_time;
        req.rec.pkg_fps = video_rec_get_fps();

        //audio
        req.rec.audio.sample_rate = 0;
        req.rec.audio.channel 	= 0;
        req.rec.audio.volume    = 0;
        req.rec.audio.buf = 0;
        req.rec.audio.buf_len = 0;
    }
#endif

    err = server_request(__this_net->net_video_rec1, VIDEO_REQ_REC, &req);
    if (err != 0) {
        puts("\n\n\nstart rec2 err\n\n\n");
        return VREC_ERR_V1_SERVER_OPEN;
    }

    return 0;
}



static int net_video_rec1_stop(u8 close)
{
    union video_req req = {0};
    int err;

#if (defined CONFIG_VIDEO1_ENABLE || defined CONFIG_VIDEO2_ENABLE)
    __this_net->net_state1 = VIDREC_STA_STOPING;
    if (__this_net->net_video_rec1) {
        req.rec.channel = 1;
        req.rec.state = VIDEO_STATE_STOP;
        err = server_request(__this_net->net_video_rec1, VIDEO_REQ_REC, &req);

        if (err != 0) {
            printf("\nstop rec2 err 0x%x\n", err);
            return VREC_ERR_V1_REQ_STOP;
        }

        net_video_rec_set_bitrate(video_rec_get_abr(__this_net->net_videoreq[1].rec.width));

        if (close) {
            server_close(__this_net->net_video_rec1);
            __this_net->net_video_rec1 = NULL;
        }
    }

    puts("net_video_rec1_stop\n");
    __this_net->net_state1 = VIDREC_STA_STOP;
    __this_net->video_id = 0;
#endif

    return 0;
}

#ifdef CONFIG_VIDEO2_ENABLE
static int net_video_rec2_start()
{
    int err;
    union video_req req = {0};
    struct video_text_osd text_osd;
    struct video_graph_osd graph_osd;
    u16 max_one_line_strnum;
    u16 osd_line_num;
    u16 osd_max_heigh;

    req.rec.width 	= __this_net->net_videoreq[1].rec.width;
    req.rec.height 	= __this_net->net_videoreq[1].rec.height;

// #ifdef CONFIG_VIDEO1_ENABLE
//     puts("start_video_rec1 \n");

//     if (__this->video_rec1) {
//         __this_net->net_video_rec1 = __this->video_rec1;
//     }
//     if (!__this_net->net_video_rec1) {
//         __this_net->net_video_rec1 = server_open("video_server", "video1.1");
//         if (!__this_net->net_video_rec1) {
//             return VREC_ERR_V1_SERVER_OPEN;
//         }
//         server_register_event_handler(__this_net->net_video_rec1, (void *)1, net_rec_dev_server_event_handler);
//     }
//     req.rec.camera_type = VIDEO_CAMERA_NORMAL;
//     req.rec.file    = __this->file[1];
//     req.rec.IP_interval = 0;
//     req.rec.online  = 1;
//     __this_net->video_id = 1;
// #endif

#ifdef CONFIG_VIDEO2_ENABLE
    char name[12];
    void *uvc_fd;
    if (__this->video_rec2) {
        __this_net->net_video_rec2 = __this->video_rec2;
    }

    /* struct uvc_capability uvc_cap; */

    puts("start_video_rec2 \n");
    if (!__this_net->net_video_rec2) {
        sprintf(name, "video10.%d", __this->uvc_id);
        __this_net->net_video_rec2 = server_open("video_server", name);
        if (!__this_net->net_video_rec2) {
            return -EINVAL;
        }
        server_register_event_handler(__this_net->net_video_rec2, (void *)1, net_rec_dev_server_event_handler);
    }
    req.rec.camera_type = VIDEO_CAMERA_UVC;
#if THREE_WAY_ENABLE
    req.rec.three_way_type = VIDEO_THREE_WAY_JPEG;
#else
    req.rec.three_way_type = 0;
#endif

    req.rec.width 	= 640;
    req.rec.height 	= 480;
    __this->uvc_width = 640;
    __this->uvc_height = 480;
    req.rec.uvc_id = __this->uvc_id;
    req.rec.file    = __this->file[2];
    __this_net->video_id = 2;
    req.rec.online  = 0;
#endif
    /*
     *通道号，分辨率，封装格式，写卡的路径
     */
    req.rec.channel = __this_net->channel = 2;
    req.rec.format  = USER_VIDEO_FMT_AVI;
    req.rec.state 	= VIDEO_STATE_START;

    /*
     *帧率为0表示使用摄像头的帧率
     */
    req.rec.quality     = VIDEO_MID_Q;
    req.rec.fps         = 0;
    req.rec.real_fps    = net_video_rec_get_fps();

    /*
     *采样率，通道数，录像音量，音频使用的循环BUF,录不录声音
     */
    req.rec.audio.sample_rate = VIDEO_REC_AUDIO_SAMPLE_RATE;
    req.rec.audio.channel   = 1;
    req.rec.audio.volume    = __this_net->net_video2_art_on ? AUDIO_VOLUME : 0;
    req.rec.audio.buf = __this_net->audio_buf;
    req.rec.audio.buf_len = NET_AUDIO_BUF_SIZE;
    req.rec.pkg_mute.aud_mute = !db_select("mic");

    /*
     *码率，I帧和P帧比例，必须是偶数（当录MOV的时候才有效）,
     *roio_xy :值表示宏块坐标， [6:0]左边x坐标 ，[14:8]右边x坐标，[22:16]上边y坐标，[30:24]下边y坐标,写0表示1个宏块有效
     *roio_ratio : 区域比例系数
     */
    req.rec.abr_kbps = net_video_rec_get_abr(req.rec.width);

    /*
     * osd 相关的参数，注意坐标位置，x要64对齐，y要16对齐,底下例子是根据图像大小偏移到右下
     */
    /* memcpy(video_rec_osd_buf, osd_str_buf, strlen(osd_str_buf));  */
    text_osd.font_w = 16;
    text_osd.font_h = 32;
    max_one_line_strnum = strlen(video_rec_osd_buf);//21;
    osd_line_num = 1;
    /* if (db_select("num")) { */
    /* osd_line_num = 2; */
    /* } */
    osd_max_heigh = (req.rec.height == 1088) ? 1080 : req.rec.height ;
    text_osd.x = (req.rec.width - max_one_line_strnum * text_osd.font_w) / 64 * 64;
    text_osd.y = (osd_max_heigh - text_osd.font_h * osd_line_num) / 16 * 16;
    /*     text_osd.color[0] = 0xe20095; */
    /* text_osd.bit_mode = 1; */
    text_osd.color[0] = 0x057d88;
    text_osd.color[1] = 0xe20095;
    text_osd.color[2] = 0xe20095;
    text_osd.bit_mode = 2;
    text_osd.text_format = video_rec_osd_buf;
    text_osd.font_matrix_table = osd_str_total;
    /*     text_osd.font_matrix_base = osd_str_matrix; */
    /* text_osd.font_matrix_len = sizeof(osd_str_matrix); */
    text_osd.font_matrix_base = osd2_str_matrix;
    text_osd.font_matrix_len = sizeof(osd2_str_matrix);


    text_osd.direction = 1;

    if (db_select("dat")) {
        req.rec.text_osd = &text_osd;
        req.rec.graph_osd = NULL;//&graph_osd;
    }

    req.rec.buf = __this_net->net_v0_fbuf;
    req.rec.buf_len = NET_VREC0_FBUF_SIZE;

    /* req.rec.cycle_time = 3 * 60; */
    req.rec.cycle_time = db_select("cyc");
    if (req.rec.cycle_time == 0) {
        req.rec.cycle_time = 5;
    }
    req.rec.cycle_time = req.rec.cycle_time * 60;



    struct sockaddr_in *addr = ctp_srv_get_cli_addr(__this_net->priv);
    if (!addr) {
        addr = cdp_srv_get_cli_addr(__this_net->priv);
    }
#if (defined CONFIG_NET_UDP_ENABLE)
    sprintf(req.rec.net_par.netpath, "udp://%s:%d"
            , inet_ntoa(addr->sin_addr.s_addr)
            , _BEHIND_PORT);
#elif (defined CONFIG_NET_TCP_ENABLE)
    sprintf(req.rec.net_par.netpath, "tcp://%s:%d"
            , inet_ntoa(addr->sin_addr.s_addr)
            , _BEHIND_PORT);
#elif (defined CONFIG_NET_USR_ENABLE)
    sprintf(req.rec.net_par.netpath, "usr://%s", NET_USR_PATH);
#endif
    printf("\n @@@@@@ path = %s\n", req.rec.net_par.netpath);
    //数据外引，用于网络
    req.rec.target = VIDEO_TO_OUT;
    req.rec.out.path = req.rec.net_par.netpath;
    req.rec.out.arg  = NULL ;
    req.rec.out.open = stream_open;
    req.rec.out.send = stream_write;
    req.rec.out.close = stream_close;

#if CONFIG_NET_VDIEO_GAP_ENABLE
    req.rec.tlp_time = db_select("gap");
    if (req.rec.tlp_time) {
        req.rec.real_fps = 1000 / req.rec.tlp_time;
        req.rec.pkg_fps = video_rec_get_fps();

        //audio
        req.rec.audio.sample_rate = 0;
        req.rec.audio.channel 	= 0;
        req.rec.audio.volume    = 0;
        req.rec.audio.buf = 0;
        req.rec.audio.buf_len = 0;
    }
#endif

    err = server_request(__this_net->net_video_rec2, VIDEO_REQ_REC, &req);
    if (err != 0) {
        puts("\n\n\nstart rec2 err\n\n\n");
        return VREC_ERR_V1_SERVER_OPEN;
    }

    return 0;
}


static int net_video_rec2_stop(u8 close)
{
    union video_req req = {0};
    int err;

#if (defined CONFIG_VIDEO2_ENABLE || defined CONFIG_VIDEO3_ENABLE)
    __this_net->net_state2 = VIDREC_STA_STOPING;

    if (__this_net->net_video_rec2) {
        req.rec.channel = 2;
        req.rec.state = VIDEO_STATE_STOP;
        err = server_request(__this_net->net_video_rec2, VIDEO_REQ_REC, &req);

        if (err != 0) {
            printf("\nstop rec2 err 0x%x\n", err);
            return VREC_ERR_V3_REQ_STOP;
        }
        if (close) {
            server_close(__this_net->net_video_rec2);
            __this_net->net_video_rec2 = NULL;
        }
    }

    puts("net_video_rec2_stop\n");

    __this_net->net_state2 = VIDREC_STA_STOP;
    __this_net->video_id = 0;
#endif

    return 0;
}

#endif

#ifdef CONFIG_VIDEO4_ENABLE
static int net_video_rec4_start()
{
    int err;
    union video_req req = {0};
    struct video_text_osd text_osd;
    struct video_graph_osd graph_osd;
    u16 max_one_line_strnum;
    u16 osd_line_num;
    u16 osd_max_heigh;
    char buf[128];
    u8 res = db_select("res");
    if (__this->video_rec4) {
        printf("use in same channel");
        __this_net->net_video_rec4 = __this->video_rec4;
    }


    if (!__this_net->net_video_rec4) {
        __this_net->net_video_rec4 = server_open("video_server", "video4.1");
        if (!__this_net->net_video_rec4) {
            return VREC_ERR_V4_SERVER_OPEN;
        }
        server_register_event_handler(__this_net->net_video_rec4, (void *)4, net_rec_dev_server_event_handler);
    }
    /*
     *通道号，分辨率，封装格式，写卡的路径
     */

    req.rec.channel     = 1;//用于区分任务
    req.rec.camera_type = VIDEO_CAMERA_NORMAL;
    req.rec.width       = __this_net->net_videoreq[4].rec.width;
    req.rec.height      = __this_net->net_videoreq[4].rec.height;
    req.rec.format      = USER_VIDEO_FMT_AVI;
    printf(">>>>>>width=%d    height=%d\n\n\n\n", __this_net->net_videoreq[4].rec.width, __this_net->net_videoreq[4].rec.height);
    req.rec.state       = VIDEO_STATE_START;
    //req.rec.file        = __this->file[0];  //实时流无需写卡

    /*
     *帧率为0表示使用摄像头的帧率
     */
    req.rec.quality     = VIDEO_MID_Q;
    req.rec.fps         = 0;
    req.rec.real_fps    = net_video_rec_get_fps();

    /*
     *采样率，通道数，录像音量，音频使用的循环BUF,录不录声音
     */
    req.rec.audio.sample_rate = VIDEO_REC_AUDIO_SAMPLE_RATE;
    req.rec.audio.channel   = 1;
    req.rec.audio.volume    = __this_net->net_video4_art_on ? AUDIO_VOLUME : 0;
    req.rec.audio.buf = __this_net->audio_buf;
    req.rec.audio.buf_len = NET_AUDIO_BUF_SIZE;

    req.rec.pkg_mute.aud_mute = !db_select("mic");

    /*
     *码率，I帧和P帧比例，必须是偶数（当录MOV的时候才有效）,
     *roio_xy :值表示宏块坐标， [6:0]左边x坐标 ，[14:8]右边x坐标，[22:16]上边y坐标，[30:24]下边y坐标,写0表示1个宏块有效
     *roio_ratio : 区域比例系数
     */
    req.rec.abr_kbps = net_video_rec_get_abr(req.rec.width);

    /*
     * osd 相关的参数，注意坐标位置，x要64对齐，y要16对齐,底下例子是根据图像大小偏移到右下
     */

    text_osd.font_w = 16;
    text_osd.font_h = 32;
    max_one_line_strnum = strlen(video_rec_osd_buf);//21;
    osd_line_num = 1;
    /*   if (db_select("num")) { */
    /* osd_line_num = 2; */
    /* } */
    osd_max_heigh = (req.rec.height == 1088) ? 1080 : req.rec.height ;
    text_osd.x = (req.rec.width - max_one_line_strnum * text_osd.font_w) / 64 * 64;
    text_osd.y = (osd_max_heigh - text_osd.font_h * osd_line_num) / 16 * 16;
    /* text_osd.color[0] = 0xe20095; */
    /* text_osd.bit_mode = 1; */
    text_osd.color[0] = 0x057d88;
    text_osd.color[1] = 0xe20095;
    text_osd.color[2] = 0xe20095;
    text_osd.bit_mode = 2;
    text_osd.text_format = video_rec_osd_buf;
    text_osd.font_matrix_table = osd_str_total;
    /*     text_osd.font_matrix_base = osd_str_matrix; */
    /* text_osd.font_matrix_len = sizeof(osd_str_matrix); */
    text_osd.font_matrix_base = osd2_str_matrix;
    text_osd.font_matrix_len = sizeof(osd2_str_matrix);


    text_osd.direction = 1;

    /* if (db_select("dat")) { */
    req.rec.text_osd = &text_osd;
    req.rec.graph_osd = NULL;//&graph_osd;
    /* } */

    req.rec.buf = __this_net->net_v0_fbuf;
    req.rec.buf_len = NET_VREC4_FBUF_SIZE;

    req.rec.cycle_time = db_select("cyc");
    if (req.rec.cycle_time == 0) {
        req.rec.cycle_time = 5;
    }
    req.rec.cycle_time = req.rec.cycle_time * 60;

    struct sockaddr_in *addr = ctp_srv_get_cli_addr(__this_net->priv);
    if (!addr) {
        addr = cdp_srv_get_cli_addr(__this_net->priv);
    }
#if (defined CONFIG_NET_UDP_ENABLE)
    sprintf(req.rec.net_par.netpath, "udp://%s:%d"
            , inet_ntoa(addr->sin_addr.s_addr)
            , _FORWARD_PORT);
#elif (defined CONFIG_NET_TCP_ENABLE)
    sprintf(req.rec.net_par.netpath, "tcp://%s:%d"
            , inet_ntoa(addr->sin_addr.s_addr)
            , _FORWARD_PORT);
#elif (defined CONFIG_NET_USR_ENABLE)
    sprintf(req.rec.net_par.netpath, "usr://%s", NET_USR_PATH);
#endif
    printf("\n @@@@@@ path = %s\n", req.rec.net_par.netpath);
    //数据外引，用于网络
    req.rec.target = VIDEO_TO_OUT;
    req.rec.out.path = req.rec.net_par.netpath;
    req.rec.out.arg  = NULL ;
    req.rec.out.open = stream_open;
    req.rec.out.send = stream_write;
    req.rec.out.close = stream_close;
    req.rec.online  = 1;

#if CONFIG_NET_VDIEO_GAP_ENABLE
    req.rec.tlp_time = db_select("gap");
    if (req.rec.tlp_time) {
        req.rec.real_fps = 1000 / req.rec.tlp_time;
        req.rec.pkg_fps = video_rec_get_fps();

        //audio
        req.rec.audio.sample_rate = 0;
        req.rec.audio.channel 	= 0;
        req.rec.audio.volume    = 0;
        req.rec.audio.buf = 0;
        req.rec.audio.buf_len = 0;
    }
#endif

    err = server_request(__this_net->net_video_rec4, VIDEO_REQ_REC, &req);

    if (err != 0) {
        puts("\n\n\nstart rec err\n\n\n");
        return VREC_ERR_V4_REQ_START;
    }

    net_video_rec_set_bitrate(net_video_rec_get_abr(req.rec.width));

    return 0;
}



static int net_video_rec4_stop(u8 close)
{
    union video_req req = {0};
    int err;
    __this_net->net_state4 = VIDREC_STA_STOPING;
    if (__this_net->net_video_rec4) {
        puts("\nnet video rec4 stop\n");
        req.rec.channel = 1;
        req.rec.state = VIDEO_STATE_STOP;
        err = server_request(__this_net->net_video_rec4, VIDEO_REQ_REC, &req);
        if (err != 0) {
            printf("\nstop rec err 0x%x\n", err);
            return VREC_ERR_V4_REQ_STOP;
        }
        net_video_rec_set_bitrate(video_rec_get_abr(__this_net->net_videoreq[4].rec.width));
        if (close) {
            server_close(__this_net->net_video_rec4);
            __this_net->net_video_rec4 = NULL;
        }

    }

    __this_net->net_state4 = VIDREC_STA_STOP;

    puts("\nnet video rec4 stop end\n");

    return 0;
}
#endif

#ifdef CONFIG_VIDEO5_ENABLE
static int net_video_rec5_start()
{
    int err;
    union video_req req = {0};
    struct video_text_osd text_osd;
    struct video_graph_osd graph_osd;
    u16 max_one_line_strnum;
    u16 osd_line_num;
    u16 osd_max_heigh;

    req.rec.width 	= __this_net->net_videoreq[5].rec.width;
    req.rec.height 	= __this_net->net_videoreq[5].rec.height;

    puts("start_video_rec5 \n");

    if (__this->video_rec5) {
        __this_net->net_video_rec5 = __this->video_rec5;
    }
    if (!__this_net->net_video_rec5) {
        __this_net->net_video_rec5 = server_open("video_server", "video5.1");
        if (!__this_net->net_video_rec5) {
            return VREC_ERR_V5_SERVER_OPEN;
        }
        server_register_event_handler(__this_net->net_video_rec5, (void *)1, net_rec_dev_server_event_handler);
    }
    req.rec.camera_type = VIDEO_CAMERA_NORMAL;
    req.rec.file    = __this->file[5];
    req.rec.IP_interval = 0;
    req.rec.online  = 1;
    __this_net->video_id = 1;

    /*
     *通道号，分辨率，封装格式，写卡的路径
     */
    req.rec.channel = __this_net->channel = 2;
    req.rec.format  = USER_VIDEO_FMT_AVI;
    req.rec.state 	= VIDEO_STATE_START;

    /*
     *帧率为0表示使用摄像头的帧率
     */
    req.rec.quality     = VIDEO_MID_Q;
    req.rec.fps         = 0;
    req.rec.real_fps    = net_video_rec_get_fps();

    /*
     *采样率，通道数，录像音量，音频使用的循环BUF,录不录声音
     */
    req.rec.audio.sample_rate = VIDEO_REC_AUDIO_SAMPLE_RATE;
    req.rec.audio.channel   = 1;
    req.rec.audio.volume    = __this_net->net_video5_art_on ? AUDIO_VOLUME : 0;
    req.rec.audio.buf = __this_net->audio_buf;
    req.rec.audio.buf_len = NET_AUDIO_BUF_SIZE;
    req.rec.pkg_mute.aud_mute = !db_select("mic");

    /*
     *码率，I帧和P帧比例，必须是偶数（当录MOV的时候才有效）,
     *roio_xy :值表示宏块坐标， [6:0]左边x坐标 ，[14:8]右边x坐标，[22:16]上边y坐标，[30:24]下边y坐标,写0表示1个宏块有效
     *roio_ratio : 区域比例系数
     */
    req.rec.abr_kbps = net_video_rec_get_abr(req.rec.width);

    /*
     * osd 相关的参数，注意坐标位置，x要64对齐，y要16对齐,底下例子是根据图像大小偏移到右下
     */
    /* memcpy(video_rec_osd_buf, osd_str_buf, strlen(osd_str_buf));  */
    text_osd.font_w = 16;
    text_osd.font_h = 32;
    max_one_line_strnum = strlen(video_rec_osd_buf);//21;
    osd_line_num = 1;
    /* if (db_select("num")) { */
    /* osd_line_num = 2; */
    /* } */
    osd_max_heigh = (req.rec.height == 1088) ? 1080 : req.rec.height ;
    text_osd.x = (req.rec.width - max_one_line_strnum * text_osd.font_w) / 64 * 64;
    text_osd.y = (osd_max_heigh - text_osd.font_h * osd_line_num) / 16 * 16;
    /*     text_osd.color[0] = 0xe20095; */
    /* text_osd.bit_mode = 1; */
    text_osd.color[0] = 0x057d88;
    text_osd.color[1] = 0xe20095;
    text_osd.color[2] = 0xe20095;
    text_osd.bit_mode = 2;
    text_osd.text_format = video_rec_osd_buf;
    text_osd.font_matrix_table = osd_str_total;
    /*     text_osd.font_matrix_base = osd_str_matrix; */
    /* text_osd.font_matrix_len = sizeof(osd_str_matrix); */
    text_osd.font_matrix_base = osd2_str_matrix;
    text_osd.font_matrix_len = sizeof(osd2_str_matrix);


    text_osd.direction = 1;

    if (db_select("dat")) {
        req.rec.text_osd = &text_osd;
        req.rec.graph_osd = NULL;//&graph_osd;
    }

    req.rec.buf = __this_net->net_v0_fbuf;
    req.rec.buf_len = NET_VREC5_FBUF_SIZE;

    /* req.rec.cycle_time = 3 * 60; */
    req.rec.cycle_time = db_select("cyc");
    if (req.rec.cycle_time == 0) {
        req.rec.cycle_time = 5;
    }
    req.rec.cycle_time = req.rec.cycle_time * 60;



    struct sockaddr_in *addr = ctp_srv_get_cli_addr(__this_net->priv);
    if (!addr) {
        addr = cdp_srv_get_cli_addr(__this_net->priv);
    }
#if (defined CONFIG_NET_UDP_ENABLE)
    sprintf(req.rec.net_par.netpath, "udp://%s:%d"
            , inet_ntoa(addr->sin_addr.s_addr)
            , _BEHIND_PORT);
#elif (defined CONFIG_NET_TCP_ENABLE)
    sprintf(req.rec.net_par.netpath, "tcp://%s:%d"
            , inet_ntoa(addr->sin_addr.s_addr)
            , _BEHIND_PORT);
#elif (defined CONFIG_NET_USR_ENABLE)
    sprintf(req.rec.net_par.netpath, "usr://%s", NET_USR_PATH);
#endif
    printf("\n @@@@@@ path = %s\n", req.rec.net_par.netpath);
    //数据外引，用于网络
    req.rec.target = VIDEO_TO_OUT;
    req.rec.out.path = req.rec.net_par.netpath;
    req.rec.out.arg  = NULL ;
    req.rec.out.open = stream_open;
    req.rec.out.send = stream_write;
    req.rec.out.close = stream_close;

#if CONFIG_NET_VDIEO_GAP_ENABLE
    req.rec.tlp_time = db_select("gap");
    if (req.rec.tlp_time) {
        req.rec.real_fps = 1000 / req.rec.tlp_time;
        req.rec.pkg_fps = video_rec_get_fps();

        //audio
        req.rec.audio.sample_rate = 0;
        req.rec.audio.channel 	= 0;
        req.rec.audio.volume    = 0;
        req.rec.audio.buf = 0;
        req.rec.audio.buf_len = 0;
    }
#endif

    err = server_request(__this_net->net_video_rec5, VIDEO_REQ_REC, &req);
    if (err != 0) {
        puts("\n\n\nstart rec5 err\n\n\n");
        return VREC_ERR_V5_SERVER_OPEN;
    }

    return 0;
}



static int net_video_rec5_stop(u8 close)
{
    union video_req req = {0};
    int err;

#if (defined CONFIG_VIDEO5_ENABLE)
    __this_net->net_state5 = VIDREC_STA_STOPING;
    if (__this_net->net_video_rec5) {
        req.rec.channel = 2;
        req.rec.state = VIDEO_STATE_STOP;
        err = server_request(__this_net->net_video_rec5, VIDEO_REQ_REC, &req);

        if (err != 0) {
            printf("\nstop rec5 err 0x%x\n", err);
            return VREC_ERR_V5_REQ_STOP;
        }

        net_video_rec_set_bitrate(video_rec_get_abr(__this_net->net_videoreq[5].rec.width));

        if (close) {
            server_close(__this_net->net_video_rec5);
            __this_net->net_video_rec5 = NULL;
        }
    }

    puts("net_video_rec5_stop\n");
    __this_net->net_state5 = VIDREC_STA_STOP;
    __this_net->video_id = 0;
#endif

    return 0;
}
#endif

static void net_video_rec_free_buf(void)
{
    if (__this_net->net_v0_fbuf) {
        free(__this_net->net_v0_fbuf);
        __this_net->net_v0_fbuf = NULL;
    }
    if (__this_net->audio_buf) {
        free(__this_net->audio_buf);
        __this_net->audio_buf = NULL;
    }
}

static int net_video0_rec_start(struct intent *it)
{
    int err = 0;
#ifdef CONFIG_VIDEO0_ENABLE

    __this_net->net_state = VIDREC_STA_STARTING;
    if (!__this_net->net_v0_fbuf) {
        __this_net->net_v0_fbuf = malloc(NET_VREC0_FBUF_SIZE);
        if (!__this_net->net_v0_fbuf) {
            puts("malloc v0_buf err\n\n");
            return -1;
        }
    }
    if (!__this_net->audio_buf) {
        __this_net->audio_buf = malloc(NET_AUDIO_BUF_SIZE);
        if (!__this_net->audio_buf) {
            free(__this_net->net_v0_fbuf);
            return -1;
        }
    }
    err = net_video_rec0_start();
    if (err) {
        goto __start_err0;
    }
    if (__this->state != VIDREC_STA_START) {
        __this_net->videoram_mark = 1;
    } else {
        __this_net->videoram_mark = 0;
    }
    __this_net->net_state = VIDREC_STA_START;

    return 0;

__start_err0:
    puts("\nstart net_video_rec0 err\n");
    err = net_video_rec0_stop(0);
    if (err) {
        printf("\nstop net_video_rec0 wrong0 %x\n", err);
    }

#endif
    return -1;
}

static int net_video0_rec_stop(u8 close)
{
    int err;
#ifdef CONFIG_VIDEO0_ENABLE
    __this_net->net_state = VIDREC_STA_STOPING;
    err = net_video_rec0_stop(close);
    if (err) {
        puts("\n net stop0 err\n");
    }
    __this_net->net_state = VIDREC_STA_STOP;
#endif

    return err;
}

static int net_video1_rec_start(struct intent *it)
{
    int err = 0;

#if (defined CONFIG_VIDEO1_ENABLE || defined CONFIG_VIDEO2_ENABLE)


    if (!__this_net->net_v0_fbuf) {
        __this_net->net_v0_fbuf = malloc(NET_VREC0_FBUF_SIZE);

        if (!__this_net->net_v0_fbuf) {
            puts("malloc v1_buf err\n\n");
            return -1;
        }
    }
    if (!__this_net->audio_buf) {
        __this_net->audio_buf = malloc(NET_AUDIO_BUF_SIZE);

        if (!__this_net->audio_buf) {
            free(__this_net->net_v0_fbuf);
            return -1;
        }
    }
    if (__this->video_online[1] || __this->video_online[2] || __this->video_online[3]) {
        __this_net->net_state1 = VIDREC_STA_STARTING;
        err = net_video_rec1_start();
        if (err) {
            goto __start_err1;
        }

        __this_net->net_state1 = VIDREC_STA_START;
    }

    return 0;

__start_err1:
    puts("\nstart net_video_rec1 err\n");
    err = net_video_rec1_stop(0);
    if (err) {
        printf("\nstop net_video_rec1 wrong1 %x\n", err);
    }
#endif

    return -1;
}
#ifdef CONFIG_VIDEO2_ENABLE
static int net_video2_rec_start(struct intent *it)
{
    int err = 0;


    if (!__this_net->net_v0_fbuf) {
        __this_net->net_v0_fbuf = malloc(NET_VREC0_FBUF_SIZE);

        if (!__this_net->net_v0_fbuf) {
            puts("malloc v1_buf err\n\n");
            return -1;
        }
    }
    if (!__this_net->audio_buf) {
        __this_net->audio_buf = malloc(NET_AUDIO_BUF_SIZE);

        if (!__this_net->audio_buf) {
            free(__this_net->net_v0_fbuf);
            return -1;
        }
    }
    if (__this->video_online[2] || __this->video_online[3]) {
        __this_net->net_state2 = VIDREC_STA_STARTING;
        err = net_video_rec2_start();
        if (err) {
            goto __start_err2;
        }

        __this_net->net_state2 = VIDREC_STA_START;
    }

    return 0;

__start_err2:
    puts("\nstart net_video_rec2 err\n");
    err = net_video_rec2_stop(0);
    if (err) {
        printf("\nstop net_video_rec2 wrong2 %x\n", err);
    }

    return -1;
}

#endif

#ifdef CONFIG_VIDEO4_ENABLE
static int net_video4_rec_start(struct intent *it)
{
    int err = 0;

    __this_net->net_state4 = VIDREC_STA_STARTING;
    if (!__this_net->net_v0_fbuf) {
        __this_net->net_v0_fbuf = malloc(NET_VREC0_FBUF_SIZE);
        if (!__this_net->net_v0_fbuf) {
            puts("malloc v0_buf err\n\n");
            return -1;
        }
    }
    if (!__this_net->audio_buf) {
        __this_net->audio_buf = malloc(NET_AUDIO_BUF_SIZE);
        if (!__this_net->audio_buf) {
            free(__this_net->net_v0_fbuf);
            return -1;
        }
    }
    err = net_video_rec4_start();
    if (err) {
        goto __start_err4;
    }
    if (__this->state != VIDREC_STA_START) {
        __this_net->videoram_mark = 1;
    } else {
        __this_net->videoram_mark = 0;
    }
    __this_net->net_state4 = VIDREC_STA_START;

    return 0;

__start_err4:
    puts("\nstart net_video_rec4 err\n");
    err = net_video_rec4_stop(0);
    if (err) {
        printf("\nstop net_video_rec4 wrong4 %x\n", err);
    }

    return -1;
}

static int net_video4_rec_stop(u8 close)
{
    int err;
    __this_net->net_state4 = VIDREC_STA_STOPING;
    err = net_video_rec4_stop(close);
    if (err) {
        puts("\n net stop4 err\n");
    }
    __this_net->net_state4 = VIDREC_STA_STOP;

    return err;
}
#endif

#ifdef CONFIG_VIDEO5_ENABLE
static int net_video5_rec_start(struct intent *it)
{
    int err = 0;

    __this_net->net_state5 = VIDREC_STA_STARTING;
    if (!__this_net->net_v0_fbuf) {
        __this_net->net_v0_fbuf = malloc(NET_VREC0_FBUF_SIZE);
        if (!__this_net->net_v0_fbuf) {
            puts("malloc v0_buf err\n\n");
            return -1;
        }
    }
    if (!__this_net->audio_buf) {
        __this_net->audio_buf = malloc(NET_AUDIO_BUF_SIZE);
        if (!__this_net->audio_buf) {
            free(__this_net->net_v0_fbuf);
            return -1;
        }
    }
    err = net_video_rec5_start();
    if (err) {
        goto __start_err5;
    }
    __this_net->net_state5 = VIDREC_STA_START;

    return 0;

__start_err5:
    puts("\nstart net_video_rec5 err\n");
    err = net_video_rec5_stop(0);
    if (err) {
        printf("\nstop net_video_rec5 wrong5 %x\n", err);
    }

    return -1;
}

static int net_video5_rec_stop(u8 close)
{
    int err;
    __this_net->net_state5 = VIDREC_STA_STOPING;
    err = net_video_rec5_stop(close);
    if (err) {
        puts("\n net stop5 err\n");
    }
    __this_net->net_state5 = VIDREC_STA_STOP;

    return err;
}
#endif

static int net_video_rec_start(u8 mark)
{
    int err;
    if (!__this_net->is_open) {
        return 0;
    }
    puts("start net rec\n");
    if (!__this_net->net_v0_fbuf) {
        __this_net->net_v0_fbuf = malloc(NET_VREC0_FBUF_SIZE);

        if (!__this_net->net_v0_fbuf) {
            puts("malloc v0_buf err\n\n");
            return -1;
        }

    }
    if (!__this_net->audio_buf) {
        __this_net->audio_buf = malloc(NET_AUDIO_BUF_SIZE);

        if (!__this_net->audio_buf) {
            free(__this_net->net_v0_fbuf);
            return -ENOMEM;
        }
    }

#ifdef CONFIG_VIDEO0_ENABLE
    printf("\n art %d, vrt %d\n", __this_net->net_video0_art_on, __this_net->net_video0_vrt_on);
    if ((__this_net->net_video0_art_on || __this_net->net_video0_vrt_on)
        && (__this_net->net_state != VIDREC_STA_START)) {
        puts("\nnet video rec0 start \n");
        err = net_video_rec0_start();
        if (err) {
            goto __start_err0;
        }
        __this_net->net_state = VIDREC_STA_START;
    }

#endif

#if (defined CONFIG_VIDEO1_ENABLE)

    if ((__this_net->net_video1_art_on || __this_net->net_video1_vrt_on)
        && (__this_net->net_state1 != VIDREC_STA_START))	{
        if (__this->video_online[1]) {
            puts("\nnet video rec1 start \n");
            err = net_video_rec1_start();
            if (err) {
                goto __start_err1;
            }
            __this_net->net_state1 = VIDREC_STA_START;
        }
    }

#endif

#if (defined CONFIG_VIDEO2_ENABLE)

    if ((__this_net->net_video2_art_on || __this_net->net_video2_vrt_on)
        && (__this_net->net_state2 != VIDREC_STA_START))	{
        if (__this->video_online[2]) {
            puts("\nnet video rec2 start \n");
            err = net_video_rec2_start();
            if (err) {
                goto __start_err2;
            }
            __this_net->net_state2 = VIDREC_STA_START;
        }
    }

#endif

#if (defined CONFIG_VIDEO4_ENABLE)

    printf("\n art %d, vrt %d\n", __this_net->net_video4_art_on, __this_net->net_video4_vrt_on);
    if ((__this_net->net_video4_art_on || __this_net->net_video4_vrt_on)
        && (__this_net->net_state4 != VIDREC_STA_START)) {
        puts("\nnet video rec4 start \n");
        err = net_video_rec4_start();
        if (err) {
            goto __start_err4;
        }
        __this_net->net_state4 = VIDREC_STA_START;
    }

#endif

#if (defined CONFIG_VIDEO5_ENABLE)

    if ((__this_net->net_video5_art_on || __this_net->net_video5_vrt_on)
        && (__this_net->net_state5 != VIDREC_STA_START))	{
        if (__this->video_online[5]) {
            puts("\nnet video rec5 start \n");
            err = net_video_rec5_start();
            if (err) {
                goto __start_err5;
            }
            __this_net->net_state5 = VIDREC_STA_START;
        }
    }

#endif

    return 0;


#ifdef CONFIG_VIDEO5_ENABLE
__start_err5:
    puts("\nstart5 err\n");
    err = net_video_rec5_stop(0);

    if (err) {
        printf("\nstart wrong5 %x\n", err);
    }

#endif

#ifdef CONFIG_VIDEO4_ENABLE
__start_err4:
    puts("\nstart4 err\n");
    err = net_video_rec4_stop(0);

    if (err) {
        printf("\nstart wrong4 %x\n", err);
    }

#endif

#if (defined CONFIG_VIDEO1_ENABLE || defined CONFIG_VIDEO2_ENABLE)
__start_err2:
    puts("\nstart2 err\n");
    err = net_video_rec2_stop(0);

    if (err) {
        printf("\nstart wrong2 %x\n", err);
    }
__start_err1:
    puts("\nstart1 err\n");
    err = net_video_rec1_stop(0);

    if (err) {
        printf("\nstart wrong1 %x\n", err);
    }

#endif
#ifdef CONFIG_VIDEO0_ENABLE
__start_err0:
    puts("\nstart0 err\n");
    err = net_video_rec0_stop(0);

    if (err) {
        printf("\nstart wrong0 %x\n", err);
    }

#endif
    return -EFAULT;
}




int net_video_rec_stop(u8 close)
{
    int err = 0;
    if (!__this_net->is_open) {
        return 0;
    }
#ifdef CONFIG_VIDEO0_ENABLE
    puts("\n net_video_rec_stop. 0.. \n");
#if !(defined CONFIG_VIDEO1_ENABLE || defined CONFIG_VIDEO2_ENABLE)
    if (__this_net->videoram_mark != 1 && close == 0) {
        puts("\n video ram mark\n");
        return 0;
    }
#endif
    if (__this_net->net_state == VIDREC_STA_START) {
        __this_net->net_state = VIDREC_STA_STOPING;
        err = net_video_rec0_stop(close);
        if (err) {
            puts("\n net stop0 err\n");
        }
    }
#endif
#ifdef CONFIG_VIDEO4_ENABLE
    puts("\n net_video_rec_stop. 4.. \n");
    if (__this_net->net_state4 == VIDREC_STA_START) {
        __this_net->net_state4 = VIDREC_STA_STOPING;
        err = net_video_rec4_stop(close);
        if (err) {
            puts("\n net stop4 err\n");
        }
    }
#endif

#if (defined CONFIG_VIDEO1_ENABLE || defined CONFIG_VIDEO2_ENABLE)
    if (__this_net->net_state1 == VIDREC_STA_START) {
        __this_net->net_state1 = VIDREC_STA_STOPING;
        err = net_video_rec1_stop(close);
        if (err) {
            puts("\n net stop1 err\n");
        }
    }
#endif

    /* __this_net->is_open = FALSE; */
#if (defined CONFIG_VIDEO2_ENABLE)
    if (__this_net->net_state2 == VIDREC_STA_START) {
        __this_net->net_state2 = VIDREC_STA_STOPING;
        err = net_video_rec2_stop(close);
        if (err) {
            puts("\n net stop2 err\n");
        }
    }
#endif

#if (defined CONFIG_VIDEO5_ENABLE)
    if (__this_net->net_state5 == VIDREC_STA_START) {
        __this_net->net_state5 = VIDREC_STA_STOPING;
        err = net_video_rec5_stop(close);
        if (err) {
            puts("\n net stop5 err\n");
        }
    }
#endif
    return err;
}


static int  net_rt_video0_open(struct intent *it)
{
    int ret = 0;
    if (__this_net->is_open) {
        return 0;
    }
    __this_net->is_open = TRUE;
#ifdef CONFIG_VIDEO0_ENABLE
    if (it) {
        u8 mark = *((u8 *)it->data);
        __this_net->net_video0_art_on = (mark | (mark >> 1)) & 0x01;
        __this_net->net_video0_vrt_on = (mark >> 1) & 0x01 ;
        rt_stream_cmd_analysis(0, it->exdata);
    } else {
        if (__this_net->net_video0_art_on == 0 && __this_net->net_video0_vrt_on == 0) {
            goto exit;
        }
    }
    if (__this_net->net_state == VIDREC_STA_STOP || __this_net->net_state == VIDREC_STA_IDLE) {
        puts("\nnet rt video0 open \n");
        ret = net_video0_rec_start(it);
        if (ret) {
            __this_net->is_open = FALSE;//启动失败允许重新打开
        }
    }
#endif
exit:
    return ret;
}


static int  net_rt_video0_stop(struct intent *it)
{
    int ret = 0;
    if (!__this_net->is_open) {
        return 0;
    }
    printf("========================%s  %d\n", __func__, __LINE__);
    __this_net->is_open = FALSE;
#ifdef CONFIG_VIDEO0_ENABLE
    u8 mark = *((u8 *)it->data);
    __this_net->net_video0_art_on = 0;
    __this_net->net_video0_vrt_on = 0;
    if (__this_net->net_state == VIDREC_STA_START) {
        ret = net_video0_rec_stop(0);
        if (ret) {
            __this_net->is_open = TRUE;
            printf("net_video_rec0_stop fail \n\n");
        } else {
            printf("net_video_rec0_stop suc \n\n");
        }
    }
#endif
    return ret;
}

static int net_rt_video1_open(struct intent *it)
{

    int ret = 0;
    if (__this_net->is_open) {
        return 0;
    }
    __this_net->is_open = TRUE;
#if (defined CONFIG_VIDEO1_ENABLE || defined CONFIG_VIDEO2_ENABLE)
    if (it) {
        u8 mark = *((u8 *)it->data);
        __this_net->net_video1_art_on = (mark | (mark >> 1)) & 0x01;
        __this_net->net_video1_vrt_on = (mark >> 1) & 0x01 ;
        rt_stream_cmd_analysis(1, it->exdata);
    } else {
        if (__this_net->net_video1_art_on == 0 && __this_net->net_video1_vrt_on == 0) {
            puts("\nvideo1 rt not open \n");
            goto exit;
        }
    }
    if (__this_net->net_state1 == VIDREC_STA_STOP || __this_net->net_state1 == VIDREC_STA_IDLE) {
        puts("\n net rt video1 open\n");
        ret = net_video1_rec_start(it);
        if (ret) {
            __this_net->is_open = FALSE;//启动失败允许重新打开
        }
    }
#endif
exit:
    return ret;
}

static int  net_rt_video1_stop(struct intent *it)
{
    int ret = 0;
    if (!__this_net->is_open) {
        return 0;
    }
    __this_net->is_open = FALSE;
#if (defined CONFIG_VIDEO1_ENABLE || defined CONFIG_VIDEO2_ENABLE)
    u8 mark = *((u8 *)it->data);
    __this_net->net_video1_art_on = 0;
    __this_net->net_video1_vrt_on = 0 ;
    if (__this_net->net_state1 == VIDREC_STA_START) {
        ret = net_video_rec1_stop(0);
        if (ret) {
            __this_net->is_open = TRUE;
            printf("net_video_rec1_stop fail \n\n");
        } else {
            printf("net_video_rec1_stop suc \n\n");
        }
    }
#endif
    return  ret;
}

#ifdef CONFIG_VIDEO2_ENABLE
static int net_rt_video2_open(struct intent *it)
{

    int ret = 0;
    if (__this_net->is_open) {
        return 0;
    }
    __this_net->is_open = TRUE;
    if (it) {
        u8 mark = *((u8 *)it->data);
        __this_net->net_video2_art_on = (mark | (mark >> 1)) & 0x01;
        __this_net->net_video2_vrt_on = (mark >> 1) & 0x01 ;
        rt_stream_cmd_analysis(2, it->exdata);
    } else {
        if (__this_net->net_video2_art_on == 0 && __this_net->net_video2_vrt_on == 0) {
            puts("\nvideo2 rt not open \n");
            goto exit;
        }
    }
    if (__this_net->net_state2 == VIDREC_STA_STOP || __this_net->net_state2 == VIDREC_STA_IDLE) {
        puts("\n net rt video2 open\n");
        ret = net_video2_rec_start(it);
        if (ret) {
            __this_net->is_open = FALSE;//启动失败允许重新打开
        }
    }
exit:
    return ret;
}

static int  net_rt_video2_stop(struct intent *it)
{
    int ret = 0;
    if (!__this_net->is_open) {
        return 0;
    }
    __this_net->is_open = FALSE;
    u8 mark = *((u8 *)it->data);
    __this_net->net_video2_art_on = 0;
    __this_net->net_video2_vrt_on = 0 ;
    if (__this_net->net_state2 == VIDREC_STA_START) {
        ret = net_video_rec2_stop(0);
        if (ret) {
            __this_net->is_open = TRUE;
            printf("net_video_rec2_stop fail \n\n");
        } else {
            printf("net_video_rec2_stop suc \n\n");
        }
    }
    return  ret;
}
#endif // CONFIG_VIDEO2_ENABLE


#ifdef CONFIG_VIDEO4_ENABLE
static int  net_rt_video4_open(struct intent *it)
{
    int ret = 0;
    if (__this_net->is_open) {
        return 0;
    }
    __this_net->is_open = TRUE;
#ifdef CONFIG_VIDEO4_ENABLE
    if (it) {
        u8 mark = *((u8 *)it->data);
        __this_net->net_video4_art_on = (mark | (mark >> 1)) & 0x01;
        __this_net->net_video4_vrt_on = (mark >> 1) & 0x01 ;
        rt_stream_cmd_analysis(4, it->exdata);
    } else {
        if (__this_net->net_video4_art_on == 0 && __this_net->net_video4_vrt_on == 0) {
            goto exit;
        }
    }
    if (__this_net->net_state4 == VIDREC_STA_STOP || __this_net->net_state4 == VIDREC_STA_IDLE) {
        puts("\nnet rt video4 open \n");
        ret = net_video4_rec_start(it);
        if (ret) {
            __this_net->is_open = FALSE;//启动失败允许重新打开
        }
    }
#endif
exit:
    return ret;
}


static int  net_rt_video4_stop(struct intent *it)
{
    int ret = 0;
    if (!__this_net->is_open) {
        return 0;
    }
    printf("========================%s  %d\n", __func__, __LINE__);
    __this_net->is_open = FALSE;
#ifdef CONFIG_VIDEO4_ENABLE
    u8 mark = *((u8 *)it->data);
    __this_net->net_video4_art_on = 0;
    __this_net->net_video4_vrt_on = 0;
    if (__this_net->net_state4 == VIDREC_STA_START) {
        ret = net_video4_rec_stop(0);
        if (ret) {
            __this_net->is_open = TRUE;
            printf("net_video_rec4_stop fail \n\n");
        } else {
            printf("net_video_rec4_stop suc \n\n");
        }
    }
#endif
    return ret;
}
#endif

#ifdef CONFIG_VIDEO5_ENABLE
static int  net_rt_video5_open(struct intent *it)
{
    int ret = 0;
    if (__this_net->is_open) {
        return 0;
    }
    __this_net->is_open = TRUE;
#ifdef CONFIG_VIDEO5_ENABLE
    if (it) {
        u8 mark = *((u8 *)it->data);
        __this_net->net_video5_art_on = (mark | (mark >> 1)) & 0x01;
        __this_net->net_video5_vrt_on = (mark >> 1) & 0x01 ;
        rt_stream_cmd_analysis(5, it->exdata);
    } else {
        if (__this_net->net_video5_art_on == 0 && __this_net->net_video5_vrt_on == 0) {
            goto exit;
        }
    }
    if (__this_net->net_state5 == VIDREC_STA_STOP || __this_net->net_state5 == VIDREC_STA_IDLE) {
        puts("\nnet rt video5 open \n");
        ret = net_video5_rec_start(it);
        if (ret) {
            __this_net->is_open = FALSE;//启动失败允许重新打开
        }
    }
#endif
exit:
    return ret;
}


static int  net_rt_video5_stop(struct intent *it)
{
    int ret = 0;
    if (!__this_net->is_open) {
        return 0;
    }
    printf("========================%s  %d\n", __func__, __LINE__);
    __this_net->is_open = FALSE;
#ifdef CONFIG_VIDEO5_ENABLE
    u8 mark = *((u8 *)it->data);
    __this_net->net_video5_art_on = 0;
    __this_net->net_video5_vrt_on = 0;
    if (__this_net->net_state5 == VIDREC_STA_START) {
        ret = net_video5_rec_stop(0);
        if (ret) {
            __this_net->is_open = TRUE;
            printf("net_video_rec5_stop fail \n\n");
        } else {
            printf("net_video_rec5_stop suc \n\n");
        }
    }
#endif
    return ret;
}
#endif

void net_rec_close(void)
{
#if NET_REC_FORMAT
    NET_VIDEO_ERR(strm_video_rec_close());
    NET_VIDEO_ERR(net_video_rec_stop(0));
    __this_net->fbuf_fcnt = 0;
    __this_net->fbuf_ffil = 0;
#endif
}

int net_video_rec_event_stop(void)
{
    strm_video_rec_close();
    net_video_rec_stop(0);
    return 0;
}
int net_video_rec_event_start(void)
{
    strm_video_rec_open();
    net_video_rec_start(1);
    return 0;
}


/*
 * 录像app的录像控制入口, 根据当前状态调用相应的函数
 */
static int net_video_rec_control(void *_run_cmd)
{
    int err = 0;
    u32 clust;
    int run_cmd = (int)_run_cmd;
    struct vfs_partition *part;
    if (storage_device_ready() == 0) {
        if (!dev_online(SDX_DEV)) {
            net_video_rec_post_msg("noCard");
        } else {
            net_video_rec_post_msg("fsErr");
        }
        CTP_CMD_COMBINED(NULL, CTP_SDCARD, "VIDEO_CTRL", "NOTIFY", CTP_SDCARD_MSG);
        return 0;
    } else {
        part = fget_partition(CONFIG_ROOT_PATH);

        __this->total_size = part->total_size;

        if (part->clust_size < 32 || (part->fs_attr & F_ATTR_RO)) {
            net_video_rec_post_msg("fsErr");
            CTP_CMD_COMBINED(NULL, CTP_SDCARD, "VIDEO_CTRL", "NOTIFY", CTP_SDCARD_MSG);
            return 0;
        }
    }
    switch (__this->state) {
    case VIDREC_STA_IDLE:
    case VIDREC_STA_STOP:
        if (run_cmd) {
            break;
        }
        __this_net->video_rec_err = FALSE;//用在录像IMC打不开情况下
        printf("--NET_VIDEO_STOP\n");
#if (defined CONFIG_VIDEO0_ENABLE && (defined CONFIG_VIDEO1_ENABLE || defined CONFIG_VIDEO2_ENABLE)) || (defined CONFIG_VIDEO4_ENABLE && defined CONFIG_VIDEO5_ENABLE)
        NET_VIDEO_ERR(strm_video_rec_close());
        NET_VIDEO_ERR(net_video_rec_stop(0));
        __this_net->fbuf_fcnt = 0;
        __this_net->fbuf_ffil = 0;
#endif
        err = video_rec_control_start();
        if (err == 0) {
            if (__this->gsen_lock == 1) {
                net_video_rec_post_msg("lockREC");
            }
        }
        NET_VIDEO_ERR(err);
#if (defined CONFIG_VIDEO0_ENABLE && (defined CONFIG_VIDEO1_ENABLE || defined CONFIG_VIDEO2_ENABLE)) || (defined CONFIG_VIDEO4_ENABLE && defined CONFIG_VIDEO5_ENABLE)
        NET_VIDEO_ERR(strm_video_rec_open());
        NET_VIDEO_ERR(net_video_rec_start(1));
#endif
        net_video_rec_status_notify();
        printf("--NET_VIDEO_OPEN OK\n");

        break;
    case VIDREC_STA_START:
        if (run_cmd == 0) {
            printf("--NET_VIDEO_STOP\n");
#if (defined CONFIG_VIDEO0_ENABLE && (defined CONFIG_VIDEO1_ENABLE || defined CONFIG_VIDEO2_ENABLE)) || (defined CONFIG_VIDEO4_ENABLE && defined CONFIG_VIDEO5_ENABLE)
            NET_VIDEO_ERR(strm_video_rec_close());
            NET_VIDEO_ERR(net_video_rec_stop(0));
            __this_net->fbuf_fcnt = 0;
            __this_net->fbuf_ffil = 0;
#endif
            err = video_rec_control_doing();
            NET_VIDEO_ERR(err);
#if (defined CONFIG_VIDEO0_ENABLE && (defined CONFIG_VIDEO1_ENABLE || defined CONFIG_VIDEO2_ENABLE)) || (defined CONFIG_VIDEO4_ENABLE && defined CONFIG_VIDEO5_ENABLE)
            NET_VIDEO_ERR(strm_video_rec_open());
            NET_VIDEO_ERR(net_video_rec_start(1));
#endif
            printf("--NET_VIDEO_OPEN OK\n");
        }
        net_video_rec_status_notify();
        break;
    default:
        puts("\nvrec forbid\n");
        err = 1;
        break;
    }

    return err;
}

/*
 *录像的状态机,进入录像app后就是跑这里
 */
extern void in_app_stop_display(u8 state);
static int net_video_rec_state_machine(struct application *app, enum app_state state, struct intent *it)
{
    int err = 0;
    int len;
    char buf[128];

    switch (state) {
    case APP_STA_START:

        /* video_rec_config_init(); */
        if (!it) {
            break;
        }

#ifdef CONFIG_VIDEO0_ENABLE
        __this->video_online[0] = 1;
#endif

#ifdef CONFIG_VIDEO1_ENABLE
        __this->video_online[1] = 1;//dev_online("video1.*");
#endif

#ifdef CONFIG_VIDEO2_ENABLE
        __this->video_online[2] = dev_online("uvc");
#endif

#ifdef CONFIG_VIDEO3_ENABLE
        __this->video_online[3] = 1;
#endif

#ifdef CONFIG_VIDEO4_ENABLE
        __this->video_online[4] = 1;
#endif

#ifdef CONFIG_VIDEO5_ENABLE
        __this->video_online[5] = 1;
#endif

        switch (it->action) {
        case ACTION_VIDEO_DEC_MAIN:
            break;
        case ACTION_VIDEO_TAKE_PHOTO:
            printf("----ACTION_VIDEO_TAKE_PHOTO----\n\n");
            net_video_rec_take_photo(NULL);
            break;
        case ACTION_VIDEO_REC_CONCTRL:
            printf("----ACTION_VIDEO_REC_CONCTRL-----\n\n");
            err = net_video_rec_control(0);
            break;

        case ACTION_VIDEO_REC_GET_APP_STATUS:
            printf("----ACTION_VIDEO_REC_GET_APP_STATUS-----\n\n");
            video_rec_get_app_status(it);
            break;

        case ACTION_VIDEO_REC_GET_PATH:
            /*printf("----ACTION_VIDEO_REC_GET_PATHL-----\n\n");*/
            video_rec_get_path(it);
        case ACTION_VIDEO0_OPEN_RT_STREAM:
            in_app_stop_display(0);
            printf("----ACTION_VIDEO0_OPEN_RT_STREAM-----\n\n");
            __this_net->fbuf_fcnt = 0;
            __this_net->fbuf_ffil = 0;
            err = net_rt_video0_open(it);
            sprintf(buf, "format:%d,w:%d,h:%d,fps:%d,rate:%d"
                    , __this_net->net_videoreq[0].rec.format
                    , __this_net->net_videoreq[0].rec.width
                    , __this_net->net_videoreq[0].rec.height
                    , __this_net->net_videoreq[0].rec.real_fps
                    , VIDEO_REC_AUDIO_SAMPLE_RATE);
            printf("<<<<<<< : %s\n\n\n\n\n", buf);
            if (err) {
                printf("ACTION_VIDEO0_OPEN_RT_STREAM err!!!\n\n");
                CTP_CMD_COMBINED(NULL, CTP_RT_OPEN_FAIL, "OPEN_RT_STREAM", "NOTIFY", CTP_RT_OPEN_FAIL_MSG);
            } else {
                if (CTP_CMD_COMBINED(NULL, CTP_NO_ERR, "OPEN_RT_STREAM", "NOTIFY", buf)) {
                    CTP_CMD_COMBINED(NULL, CTP_NO_ERR, "OPEN_RT_STREAM", "NOTIFY", buf);
                }
                printf("CTP NOTIFY VIDEO0 OK\n\n");
            }
            break;

        case ACTION_VIDEO1_OPEN_RT_STREAM:
            in_app_stop_display(1);
            printf("----ACTION_VIDEO1_OPEN_RT_STREAM----\n\n");
            __this_net->fbuf_fcnt = 0;
            __this_net->fbuf_ffil = 0;

            err = net_rt_video1_open(it);
            sprintf(buf, "format:%d,w:%d,h:%d,fps:%d,rate:%d"
                    , __this_net->net_videoreq[1].rec.format
                    , __this_net->net_videoreq[1].rec.width
                    , __this_net->net_videoreq[1].rec.height
                    , __this_net->net_videoreq[1].rec.real_fps
                    , VIDEO_REC_AUDIO_SAMPLE_RATE);
            printf("<<<<<<< : %s\n\n\n\n\n", buf);
            if (err) {
                printf("ACTION_VIDEO1_OPEN_RT_STREAM err!!!\n\n");
                CTP_CMD_COMBINED(NULL, CTP_RT_OPEN_FAIL, "OPEN_THIRD_RT_STREAM", "NOTIFY", CTP_RT_OPEN_FAIL_MSG);
            } else {
                CTP_CMD_COMBINED(NULL, CTP_NO_ERR, "OPEN_THIRD_RT_STREAM", "NOTIFY", buf);
                printf("CTP NOTIFY VIDEO1 OK\n\n");
            }
            break;
#ifdef CONFIG_VIDEO2_ENABLE
        case ACTION_VIDEO2_OPEN_RT_STREAM:
            in_app_stop_display(2);
            printf("----ACTION_VIDEO2_OPEN_RT_STREAM----\n\n");
            __this_net->fbuf_fcnt = 0;
            __this_net->fbuf_ffil = 0;

            err = net_rt_video2_open(it);
            sprintf(buf, "format:%d,w:%d,h:%d,fps:%d,rate:%d"
                    , __this_net->net_videoreq[2].rec.format
                    , __this_net->net_videoreq[2].rec.width
                    , __this_net->net_videoreq[2].rec.height
                    , __this_net->net_videoreq[2].rec.real_fps
                    , VIDEO_REC_AUDIO_SAMPLE_RATE);
            printf("<<<<<<< : %s\n\n\n\n\n", buf);
            if (err) {
                printf("ACTION_VIDEO2_OPEN_RT_STREAM err!!!\n\n");
                CTP_CMD_COMBINED(NULL, CTP_RT_OPEN_FAIL, "OPEN_PULL_RT_STREAM", "NOTIFY", CTP_RT_OPEN_FAIL_MSG);
            } else {
                CTP_CMD_COMBINED(NULL, CTP_NO_ERR, "OPEN_PULL_RT_STREAM", "NOTIFY", buf);
                printf("CTP NOTIFY VIDEO2 OK\n\n");
            }
            break;
#endif

#ifdef CONFIG_VIDEO4_ENABLE
        case ACTION_VIDEO4_OPEN_RT_STREAM:
            in_app_stop_display(4);
            printf("----ACTION_VIDEO4_OPEN_RT_STREAM----\n\n");
            __this_net->fbuf_fcnt = 0;
            __this_net->fbuf_ffil = 0;

            err = net_rt_video4_open(it);
            sprintf(buf, "format:%d,w:%d,h:%d,fps:%d,rate:%d"
                    , __this_net->net_videoreq[4].rec.format
                    , __this_net->net_videoreq[4].rec.width
                    , __this_net->net_videoreq[4].rec.height
                    , __this_net->net_videoreq[4].rec.real_fps
                    , VIDEO_REC_AUDIO_SAMPLE_RATE);
            printf("<<<<<<< : %s\n\n\n\n\n", buf);
            if (err) {
                printf("ACTION_VIDEO4_OPEN_RT_STREAM err!!!\n\n");
                CTP_CMD_COMBINED(NULL, CTP_RT_OPEN_FAIL, "OPEN_RT_STREAM", "NOTIFY", CTP_RT_OPEN_FAIL_MSG);
            } else {
                if (CTP_CMD_COMBINED(NULL, CTP_NO_ERR, "OPEN_RT_STREAM", "NOTIFY", buf)) {
                    CTP_CMD_COMBINED(NULL, CTP_NO_ERR, "OPEN_RT_STREAM", "NOTIFY", buf);
                }
                printf("CTP NOTIFY VIDEO4 OK\n\n");
            }
            break;
#endif

#ifdef CONFIG_VIDEO5_ENABLE
        case ACTION_VIDEO5_OPEN_RT_STREAM:
            in_app_stop_display(5);
            printf("----ACTION_VIDEO5_OPEN_RT_STREAM----\n\n");
            __this_net->fbuf_fcnt = 0;
            __this_net->fbuf_ffil = 0;

            err = net_rt_video5_open(it);
            sprintf(buf, "format:%d,w:%d,h:%d,fps:%d,rate:%d"
                    , __this_net->net_videoreq[5].rec.format
                    , __this_net->net_videoreq[5].rec.width
                    , __this_net->net_videoreq[5].rec.height
                    , __this_net->net_videoreq[5].rec.real_fps
                    , VIDEO_REC_AUDIO_SAMPLE_RATE);
            printf("<<<<<<< : %s\n\n\n\n\n", buf);
            if (err) {
                printf("ACTION_VIDEO5_OPEN_RT_STREAM err!!!\n\n");
                CTP_CMD_COMBINED(NULL, CTP_RT_OPEN_FAIL, "OPEN_PULL_RT_STREAM", "NOTIFY", CTP_RT_OPEN_FAIL_MSG);
            } else {
                CTP_CMD_COMBINED(NULL, CTP_NO_ERR, "OPEN_PULL_RT_STREAM", "NOTIFY", buf);
                printf("CTP NOTIFY VIDEO5 OK\n\n");
            }
            break;
#endif
        case ACTION_VIDEO0_CLOSE_RT_STREAM:
            printf("---ACTION_VIDEO0_CLOSE_RT_STREAM---\n\n");
            err = net_rt_video0_stop(it);
            if (err) {
                printf("ACTION_VIDEO_CLOE_RT_STREAM err!!!\n\n");
                strcpy(buf, "status:0");
            } else {
                strcpy(buf, "status:1");
            }
            CTP_CMD_COMBINED(NULL, CTP_NO_ERR, "CLOSE_RT_STREAM", "NOTIFY", buf);
            printf("CTP NOTIFY VIDEO0 OK\n\n");
            __this_net->fbuf_fcnt = 0;
            __this_net->fbuf_ffil = 0;
            break;

        case ACTION_VIDEO1_CLOSE_RT_STREAM:
            printf("---ACTION_VIDEO1_CLOSE_RT_STREAM---\n\n");
            err =  net_rt_video1_stop(it);
            if (err) {
                printf("ACTION_VIDE1_CLOE_RT_STREAM err!!!\n\n");
                strcpy(buf, "status:0");
            } else {
                strcpy(buf, "status:1");
            }

            CTP_CMD_COMBINED(NULL, CTP_NO_ERR, "CLOSE_THIRD_RT_STREAM", "NOTIFY", buf);
            printf("CTP NOTIFY VIDEO1 OK\n\n");
            __this_net->fbuf_fcnt = 0;
            __this_net->fbuf_ffil = 0;

            break;
#ifdef CONFIG_VIDEO2_ENABLE
        case ACTION_VIDEO2_CLOSE_RT_STREAM:
            printf("---ACTION_VIDEO2_CLOSE_RT_STREAM---\n\n");
            err =  net_rt_video2_stop(it);
            if (err) {
                printf("ACTION_VIDE2_CLOE_RT_STREAM err!!!\n\n");
                strcpy(buf, "status:0");
            } else {
                strcpy(buf, "status:1");
            }

            CTP_CMD_COMBINED(NULL, CTP_NO_ERR, "CLOSE_PULL_RT_STREAM", "NOTIFY", buf);
            printf("CTP NOTIFY VIDEO2 OK\n\n");
            __this_net->fbuf_fcnt = 0;
            __this_net->fbuf_ffil = 0;
            break;
#endif

#ifdef CONFIG_VIDEO4_ENABLE
        case ACTION_VIDEO4_CLOSE_RT_STREAM:
            printf("---ACTION_VIDEO4_CLOSE_RT_STREAM---\n\n");
            err =  net_rt_video4_stop(it);
            if (err) {
                printf("ACTION_VIDE4_CLOE_RT_STREAM err!!!\n\n");
                strcpy(buf, "status:0");
            } else {
                strcpy(buf, "status:1");
            }

            CTP_CMD_COMBINED(NULL, CTP_NO_ERR, "CLOSE_PULL_RT_STREAM", "NOTIFY", buf);
            printf("CTP NOTIFY VIDEO4 OK\n\n");
            __this_net->fbuf_fcnt = 0;
            __this_net->fbuf_ffil = 0;
            break;
#endif

#ifdef CONFIG_VIDEO5_ENABLE
        case ACTION_VIDEO5_CLOSE_RT_STREAM:
            printf("---ACTION_VIDEO5_CLOSE_RT_STREAM---\n\n");
            err =  net_rt_video5_stop(it);
            if (err) {
                printf("ACTION_VIDE5_CLOE_RT_STREAM err!!!\n\n");
                strcpy(buf, "status:0");
            } else {
                strcpy(buf, "status:1");
            }

            CTP_CMD_COMBINED(NULL, CTP_NO_ERR, "CLOSE_PULL_RT_STREAM", "NOTIFY", buf);
            printf("CTP NOTIFY VIDEO5 OK\n\n");
            __this_net->fbuf_fcnt = 0;
            __this_net->fbuf_ffil = 0;
            break;
#endif
        case ACTION_VIDEO_CYC_SAVEFILE:
#if 0
            video_cyc_file(0);
#if defined CONFIG_VIDEO1_ENABLE
            video_cyc_file(1);
#endif
#if defined CONFIG_VIDEO2_ENABLE
            video_cyc_file(2);
#endif
#if defined CONFIG_VIDEO4_ENABLE
            video_cyc_file(4);
#endif
#if defined CONFIG_VIDEO5_ENABLE
            video_cyc_file(5);
#endif
#endif
            strcpy(buf, "status:1");
            CTP_CMD_COMBINED(NULL, CTP_NO_ERR, "VIDEO_CYC_SAVEFILE", "NOTIFY", buf);
            break;

#ifdef CONFIG_NET_SCR
        case ACTION_NET_SCR_REC_OPEN:
            printf("%s ACTION_NET_SCR_REC_OPEN\n", __func__);
            extern int net_video_disp_stop(int id);
            net_video_disp_stop(0);
            break;

        case ACTION_NET_SCR_REC_CLOSE:
            printf("%s ACTION_NET_SCR_REC_CLOSE\n", __func__);
            extern int net_video_disp_start(int id);
            net_video_disp_start(0);
            break;
#endif
        }

        break;
    case APP_STA_STOP:
        puts("\n[MSG] net_video_rec APP_STA_STOP\n");
        break;
    case APP_STA_DESTROY:
        puts("\n[MSG] net_video_rec APP_STA_DESTROY\n");
        break;

    }

    return err;
}

static void net_video_rec_ioctl(u32 argv)
{
    char buf[128];
    u32 *pargv = (u32 *)argv;
    u32 type = (u32)pargv[0];
    char *path = (char *)pargv[1];

    /*printf("%s type : %d , %s \n\n", __func__, type, path);*/
    switch (type) {
    case NET_VIDREC_STA_STOP:
        puts("\n NET_VIDREC_STA_STOP\n");
        if (__this_net->net_state == VIDREC_STA_START || __this_net->net_state1 == VIDREC_STA_START || __this_net->net_state4 == VIDREC_STA_START || __this_net->net_state5 == VIDREC_STA_START) {
            net_video_rec_stop(0);          //这个值由1改成0  解决在APP连接出流时，直接断手机热点，再立马打开热点，连接APP重启问题
        }
        if (__this_strm->state == VIDREC_STA_START) {
            printf("\n strm_video_rec_close 1\n");
            extern int strm_video_rec_close2(void);
            strm_video_rec_close2();
            printf("\n strm_video_rec_close 2\n");
        }
        net_video_rec_free_buf();
        extern void strm_video_rec_free_buf(void);
        strm_video_rec_free_buf();
        __this_net->is_open = FALSE;
        __this_strm->is_open = FALSE;
        break;
    case NET_VIDREC_STATE_NOTIFY:
        sprintf(buf, "status:%d", ((__this->state == VIDREC_STA_START) ? 1 : 0));
        CTP_CMD_COMBINED(NULL, CTP_NO_ERR, "VIDEO_CTRL", "NOTIFY", buf);
        break;
    default :
        return ;
    }
}

static int net_video_rec_device_event_handler(struct sys_event *event)
{
    int err;
    struct intent it;

#if 0
    if (!ASCII_StrCmp(event->arg, "sd*", 4)) {
        switch (event->u.dev.event) {
        case DEVICE_EVENT_IN:
            video_rec_sd_in_notify();
            break;
        case DEVICE_EVENT_OUT:
            if (!fdir_exist(CONFIG_STORAGE_PATH)) {
                video_rec_sd_out_notify();
            }
            break;
        }
    } else if (!ASCII_StrCmp(event->arg, "sys_power", 7)) {
        switch (event->u.dev.event) {
        case DEVICE_EVENT_POWER_CHARGER_IN:
            puts("---charger in\n\n");
            if ((__this->state == VIDREC_STA_IDLE) ||
                (__this->state == VIDREC_STA_STOP)) {
                video_rec_control_start();
            }
            break;
        case DEVICE_EVENT_POWER_CHARGER_OUT:
            puts("---charger out\n");
#if 0
            if (__this->state == VIDREC_STA_START) {
                video_rec_control_doing();
            }
#endif
            break;
        }
    }
#endif
    return 0;
}
static void net_video_server_task(void *p)
{
    int res;
    int msg[16];

    if (os_mutex_create(&net_vdrec_mutex) != OS_NO_ERR) {
        printf("net_video_server_task , os_mutex_create err !!!\n\n");
        return;
    }
    net_video_handler_init();
    printf("net_video_server_task running\n\n");

    while (1) {

        res = os_task_pend("taskq", msg, ARRAY_SIZE(msg));
        if (os_task_del_req(OS_TASK_SELF) == OS_TASK_DEL_REQ) {
            os_task_del_res(OS_TASK_SELF);
        }

        switch (res) {
        case OS_TASKQ:
            switch (msg[0]) {
            case Q_EVENT:
                break;
            case Q_MSG:
                net_video_rec_ioctl((u32)msg[1]);
                break;
            default:
                break;
            }
            break;
        case OS_TIMER:
            break;
        case OS_TIMEOUT:
            break;
        }
    }
    os_mutex_del(&net_vdrec_mutex, OS_DEL_ALWAYS);
}

void net_video_server_init(void)
{
    task_create(net_video_server_task, 0, "net_video_server");
}
__initcall(net_video_server_init);


/*录像app的事件总入口*/
static int net_video_rec_event_handler(struct application *app, struct sys_event *event)
{
    switch (event->type) {
    case SYS_DEVICE_EVENT:
        return video_rec_device_event_action(event);//设备事件和 vidoe_rec公用一个handler，
    default:
        return false;
    }
}

static const struct application_operation net_video_rec_ops = {
    .state_machine  = net_video_rec_state_machine,
    .event_handler 	= net_video_rec_event_handler,
};

REGISTER_APPLICATION(app_video_rec) = {
    .name 	= "net_video_rec",
    .action	= ACTION_VIDEO_REC_MAIN,
    .ops 	= &net_video_rec_ops,
    .state  = APP_STA_DESTROY,
};

#endif

