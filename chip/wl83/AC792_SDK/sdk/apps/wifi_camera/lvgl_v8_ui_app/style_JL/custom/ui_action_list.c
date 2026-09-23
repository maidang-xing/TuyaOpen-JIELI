#include "app_config.h"
#ifdef CONFIG_UI_STYLE_JL_ENABLE
#if !LV_USE_GUIBUILDER_SIMULATOR
#include "app_config.h"
#include "custom.h"
#include "ui.h"
#include "fs/fs.h"
#include "video_dec_server.h"
#include "video_dec.h"
#include "asm/jpeg_codec.h"
#include "asm/hwi.h"
#include "system/includes.h"
#include "fs/fs.h"
#include "os/os_api.h"
#include "video_ioctl.h"
#include "video.h"
#include "pipeline_core.h"
#include "video/fb.h"
#include "asm/jldma2d.h"
// 动态展示部分
#define interval_dir_x 210
#define interval_dir_y 170

#define PIPELINE_STOP       0
#define PIPELINE_EXIT       1
#define PIPELINE_RUNING     2
#define PIPELINE_IDLE       3

void video_dir_screen_load(void);
void video_file_screen_load(void);
int storage_device_available();
void video_dir_cb_event_handler(lv_event_t *e);

static void jpeg2yuv_pipeline_uninit(void);
static int jpeg2yuv_pipeline_init(struct video_format *f);
static int jpeg2yuv_with_pipeline(const char *path, u8 *img_buf, int dst_w, int dst_h);
static u8 pipeline_state;
static pipe_core_t *pipe_core;
static OS_SEM sem;

#define USE_DMA2D_CONVERT 1

//公版800*480屏幕
#define SCALE_FACTOR_W (LCD_W / 800.0)
#define SCALE_FACTOR_H (LCD_H / 480.0)

//公版800*480 图片资源尺寸
// 文件页面
#define IMG_CONT_W_BASE 192
#define IMG_CONT_H_BASE 205
#define IMG_CONT_COL_SPACE_BASE 20
#define IMG_CONT_ROW_SPACE_BASE 10
#define EXTRA_SPACE_BASE 30
#define IMG_W_BASE 192
#define IMG_H_BASE 160
//文件夹页面
#define VIDEO_FILE_IMG_W_BASE 32
#define VIDEO_FILE_IMG_H_BASE 32
#define DIR_CONT_W_BASE  192
#define DIR_CONT_H_BASE  190
#define DIR_IMG_W_BASE  160
#define DIR_IMG_H_BASE  160
#define CHECK_BOX_W_BASE 45
#define CHECK_BOX_H_BASE 45
#define LOCK_IMG_W_BASE 24
#define LOCK_IMG_H_BASE 24



// 默认使用基础值
#define IMG_CONT_W IMG_CONT_W_BASE
#define IMG_CONT_H IMG_CONT_H_BASE
#define IMG_CONT_COL_SPACE IMG_CONT_COL_SPACE_BASE
#define IMG_CONT_ROW_SPACE IMG_CONT_ROW_SPACE_BASE
#define EXTRA_SPACE EXTRA_SPACE_BASE
#define IMG_W IMG_W_BASE
#define IMG_H IMG_H_BASE
#define LOCK_IMG_W LOCK_IMG_W_BASE
#define LOCK_IMG_H LOCK_IMG_H_BASE


#define VIDEO_FILE_IMG_W VIDEO_FILE_IMG_W_BASE
#define VIDEO_FILE_IMG_H VIDEO_FILE_IMG_H_BASE
#define DIR_CONT_W DIR_CONT_W_BASE
#define DIR_CONT_H DIR_CONT_H_BASE
#define DIR_IMG_W DIR_IMG_W_BASE
#define DIR_IMG_H DIR_IMG_H_BASE
#define CHECK_BOX_W CHECK_BOX_W_BASE
#define CHECK_BOX_H CHECK_BOX_H_BASE

#define ONE_PAGE_MAX_NUM 60
#define IMG_BUF_MAX_NUM 9

#if THREE_WAY_ENABLE

#define ALIGN_16(x) (((x) + 15) & ~15)

// 根据缩放系数重新定义
#undef IMG_CONT_H
#undef IMG_CONT_COL_SPACE
#undef IMG_CONT_ROW_SPACE
#undef EXTRA_SPACE
#undef IMG_W
#undef IMG_H

#undef VIDEO_FILE_IMG_W
#undef VIDEO_FILE_IMG_H
#undef DIR_CONT_W
#undef DIR_CONT_H
#undef DIR_IMG_W
#undef DIR_IMG_H
#undef CHECK_BOX_W
#undef CHECK_BOX_H
#undef LOCK_IMG_W
#undef LOCK_IMG_H

#define IMG_CONT_W (IMG_CONT_W_BASE * SCALE_FACTOR_W)
#define IMG_CONT_H (IMG_CONT_H_BASE * SCALE_FACTOR_H)
#define IMG_CONT_COL_SPACE (IMG_CONT_COL_SPACE_BASE * SCALE_FACTOR_W)
#define IMG_CONT_ROW_SPACE (IMG_CONT_ROW_SPACE_BASE * SCALE_FACTOR_H)
#define EXTRA_SPACE (EXTRA_SPACE_BASE * SCALE_FACTOR_H)

#define IMG_W ALIGN_16((int)(IMG_W_BASE * SCALE_FACTOR_W))
#define IMG_H ALIGN_16((int)(IMG_H_BASE * SCALE_FACTOR_H))

#define VIDEO_FILE_IMG_W (VIDEO_FILE_IMG_W_BASE * SCALE_FACTOR_W)
#define VIDEO_FILE_IMG_H (VIDEO_FILE_IMG_H_BASE * SCALE_FACTOR_H)
#define DIR_CONT_W (DIR_CONT_W_BASE * SCALE_FACTOR_W)
#define DIR_CONT_H (DIR_CONT_H_BASE * SCALE_FACTOR_H)
#define DIR_IMG_W (DIR_IMG_W_BASE * SCALE_FACTOR_W)
#define DIR_IMG_H (DIR_IMG_H_BASE * SCALE_FACTOR_H)
#define CHECK_BOX_W (CHECK_BOX_W_BASE * SCALE_FACTOR_W)
#define CHECK_BOX_H (CHECK_BOX_H_BASE * SCALE_FACTOR_H)
#define LOCK_IMG_W (LOCK_IMG_W_BASE * SCALE_FACTOR_W)
#define LOCK_IMG_H (LOCK_IMG_H_BASE * SCALE_FACTOR_H)



#endif

#define FILE_DISP_REVERSE_ORDER 1
#define DECODE_TASK_NAME "img_decode_task"
static int task_pid;

static void create_page(int page);
static void update_img_text(int start_index, int end_index, u8 dir);
static struct vfscan *fs_file = NULL;
static int jpeg_decode_scale(const char *path, u8 *img_buf, u16 dst_w, u16 dst_h);
static lv_img_dsc_t image_dsc_list[IMG_BUF_MAX_NUM];
static u8 *img_buf_list[IMG_BUF_MAX_NUM];

static u32 cur_page = 1;
static u32 total_file_num = 0;
static u32 total_file_page = 0;
static u32 to_play_video_page = 0;
static int cur_scroll_val = 0;
static int create_num;
static u32 line;
static u32 last_line;
static char *dir_path;
u8 deleting_flag = 0;

static int line_obj_num = 0;
static int img_buf_num = 0;
static int max_show_num = 0;

static void send_msg2file_num(void)
{
    char *num = lvgl_module_msg_get_ptr(GUI_MODEL_MSG_ID_FILE_NUM, 24);
    int cur_file = line * line_obj_num + (cur_page - 1) * ONE_PAGE_MAX_NUM + max_show_num;
    cur_file = cur_file < total_file_num ? cur_file : total_file_num;
    sprintf(num, "%d\n/\n%d", cur_file, total_file_num);
    lvgl_module_msg_send_ptr(num, 0);
}

int get_cur_num()
{
    int line_ = 0;
    lv_ui_video_file *ui_scr = ui_get_scr_ptr(&guider_ui, GUI_SCREEN_VIDEO_FILE);
    if (!ui_scr) {
        return -1;
    }
    lv_obj_t *contain = lv_obj_get_child(ui_scr->video_file, 3);
    cur_scroll_val = lv_obj_get_scroll_y(contain);
    if (total_file_num % 3) {
        line_ = total_file_num / 3 - 1;
    } else {
        line_ = total_file_num / 3 - 2;
    }
    if (line_ <= 0) {
        line_ = 0;
    }
    int cur_file;
    cur_file = cur_scroll_val / 215;
    if (cur_file) {
        if (cur_scroll_val % 215 >= 43) {
            cur_file = cur_file * 3 + 3 * 3;
        } else {
            cur_file = cur_file * 3 + 2 * 3;
        }
    } else {
        if (cur_scroll_val % 215 >= 43) {
            cur_file = 3 * 3;
        } else {
            cur_file = 2 * 3;
        }
    }

    /* printf("srcoll val:%d, line_:%d, cur_file:%d", cur_scroll_val, line_, cur_file); */
    if (line_ * 215 == cur_scroll_val) {
        cur_file = total_file_num;
    }

    cur_file = cur_file < total_file_num ? cur_file : total_file_num;
    return cur_file;
}


static void dec_no_card_return(int dir)
{
    gui_scr_t *screen = gui_scr_get(GUI_SCREEN_HOME_PAGE);
    if (screen == NULL) {
        screen = gui_scr_create(GUI_SCREEN_HOME_PAGE, "home_page", guider_ui.home_page, (gui_scr_setup_cb_t)setup_scr_home_page, (gui_scr_unload_cb_t)unload_scr_home_page);
    }
    ui_load_scr_anim(&guider_ui, screen, LV_SCR_LOAD_ANIM_NONE, 0, 0, true, true, false);

}

static int dec_no_card_handler(const char *type, u32 arg)
{
    extern void sys_prompt_show_ctl(int32_t show_time, void *tips);
    lvgl_rpc_post_func(dec_no_card_return, 1, arg);
    lvgl_rpc_post_func(sys_prompt_show_ctl, 2, 3000, (void *)_("nosd"));
    return 0;
}

static int dec_no_file_handler(const char *type, u32 arg)
{
    extern void sys_prompt_show_ctl(int32_t show_time, void *tips);
    lvgl_rpc_post_func(sys_prompt_show_ctl, 2, 1000, (void *)_("nofile"));
    return 0;
}

/*
*	模式post消息给UI，执行UI动作
*
*/
void video_dec_post_msg(const char *msg, ...)
{
#ifdef USE_LVGL_V8_UI_DEMO
    va_list argptr;

    printf("[chili] %s %s   \n", __func__, msg);

    va_start(argptr, msg);

    if (strstr(msg, "noCard")) {
        dec_no_card_handler(msg, va_arg(argptr, int));
    } else if (strstr(msg, "noFile")) {
        dec_no_file_handler(msg, va_arg(argptr, int));
    } else if (strstr(msg, "fileErr")) {
        dec_file_err_handler(msg, 0);
    } else if (strstr(msg, "end") || strstr(msg, "pause")) {
        lvgl_module_msg_send_value(GUI_MODEL_MSG_ID_VIDEO_PAUSE, LV_STATE_DEFAULT, 0);
    } else if (strstr(msg, "play")) {
        lvgl_module_msg_send_value(GUI_MODEL_MSG_ID_VIDEO_PAUSE, LV_STATE_CHECKED, 0);
    } else if (strstr(msg, "plyTime")) {
        dec_play_time_handler(msg, va_arg(argptr, int));
    } else if (strstr(msg, "fname")) {
        dec_file_name_handler(msg, va_arg(argptr, int));
    } else if (strstr(msg, "fileInfo")) {
        post_msg2_dec(msg, va_arg(argptr, int));
    } else {
        printf("[chili] %s your msg [%s] no callback! \n", __func__, msg, __LINE__);
    }

    va_end(argptr);

#endif

}
static void video_dir_view_9_event_handler(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    lv_ui *ui = (lv_ui *)lv_event_get_user_data(e);
    lv_obj_t *src = lv_event_get_target(e);
    switch (code) {
    case LV_EVENT_CLICKED: {
        //custom code video_file
        {
            lv_ui_video_dir *ui_scr = ui_get_scr_ptr(&guider_ui, GUI_SCREEN_VIDEO_DIR);
            if (!ui_scr) {
                return;
            }
            lv_obj_t *dest = ui->video_dir;
            lv_obj_t *label = lv_obj_get_child(src, 2);
            if (!label) {
                lv_obj_t *parent = lv_obj_get_parent(src);
                label = lv_obj_get_child(parent, 2);
            }
            const char *text1 = lv_label_get_text(label); //文件夹
            const char *text2 = lv_label_get_text(ui_scr->video_dir_lbl_path); //路径
            char *full_path = lvgl_module_msg_get_ptr(GUI_MODEL_MSG_ID_FILE_PATH, strlen(text1) + strlen(text2) + 2);
            if (full_path) {
                strcpy(full_path, text2);
                strcat(full_path, text1);
                size_t len = strlen(full_path);
                if (len > 0 && full_path[len - 1] != '/') {
                    full_path[len] = '/';
                    full_path[len + 1] = '\0';
                }
            }
            dir_path = malloc(strlen(full_path) + 1);
            if (!dir_path) {
                printf("dir_path malloc err \n");
                return;
            }
            strcpy(dir_path, full_path);
            printf("cur path: %s\n", full_path);
#if LV_USE_GUIBUILDER_SIMULATOR
#else
            lvgl_module_msg_send_ptr(full_path, 0);
#endif
        }
        gui_scr_t *screen = gui_scr_get(GUI_SCREEN_VIDEO_FILE);
        if (screen == NULL) {
            screen = gui_scr_create(GUI_SCREEN_VIDEO_FILE, "video_file", guider_ui.video_file, (gui_scr_setup_cb_t)setup_scr_video_file, (gui_scr_unload_cb_t)unload_scr_video_file);
        }
        ui_load_scr_anim(ui, screen, LV_SCR_LOAD_ANIM_NONE, 0, 0, true, true, false);

    }
    break;
    default:
        break;
    }
}

void create_dir(int index, char *dir_name)
{
    lv_group_t *def_group = lv_group_get_default();
    //Write codes video_dir_view_9
    lv_ui_video_dir *ui_scr = ui_get_scr_ptr(&guider_ui, GUI_SCREEN_VIDEO_DIR);
    if (!ui_scr) {
        return;
    }
    lv_obj_t *video_dir_view_new = lv_obj_create(ui_scr->video_dir);
    //Set style for video_dir_view_9. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
    lv_obj_set_style_radius(video_dir_view_new, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(video_dir_view_new, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(video_dir_view_new, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(video_dir_view_new, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(video_dir_view_new, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(video_dir_view_new, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(video_dir_view_new, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(video_dir_view_new, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(video_dir_view_new, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

    //Set style for video_dir_view_dir. Part: LV_PART_MAIN, State: LV_STATE_FOCUS_KEY
    lv_obj_set_style_radius(video_dir_view_new, 0, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_bg_color(video_dir_view_new, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_bg_opa(video_dir_view_new, 0, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_shadow_width(video_dir_view_new, 0, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_border_width(video_dir_view_new, 0, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_outline_color(video_dir_view_new, lv_color_make(0x21, 0x95, 0xf6), LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_outline_width(video_dir_view_new, 2, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_outline_opa(video_dir_view_new, 128, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_outline_pad(video_dir_view_new, 2, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_pad_left(video_dir_view_new, 0, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_pad_right(video_dir_view_new, 0, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_pad_top(video_dir_view_new, 0, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_pad_bottom(video_dir_view_new, 0, LV_PART_MAIN | LV_STATE_FOCUS_KEY);

    lv_obj_set_pos(video_dir_view_new, SCALE_FACTOR_W * (91 + index  % 3 * interval_dir_x),
                   SCALE_FACTOR_H * (90 + index  / 3 * interval_dir_y));
    lv_obj_set_size(video_dir_view_new, DIR_CONT_W, DIR_CONT_H);
    lv_obj_set_scrollbar_mode(video_dir_view_new, LV_SCROLLBAR_MODE_OFF);
    lv_group_add_obj(def_group, video_dir_view_new);
    //Write codes video_dir_cb_1
    lv_obj_t *video_dir_cb_new = lv_checkbox_create(video_dir_view_new);
    lv_checkbox_set_text(video_dir_cb_new, "checkbox");

    //Set style for video_dir_cb_1. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
    lv_obj_set_style_radius(video_dir_cb_new, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(video_dir_cb_new, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(video_dir_cb_new, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(video_dir_cb_new, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(video_dir_cb_new, lv_color_make(0xe1, 0xe6, 0xee), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(video_dir_cb_new, 1, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(video_dir_cb_new, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_side(video_dir_cb_new, LV_BORDER_SIDE_NONE, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(video_dir_cb_new, lv_color_make(0x00, 0x00, 0x00), LV_PART_MAIN | LV_STATE_DEFAULT);
#if THREE_WAY_ENABLE && (LCD_W < 800)
    //三路小屏幕简单处理,如更换其他屏幕且缩放了UI,请自行更换字体
    //这里字体对应公版640*360 UI工程
    lv_obj_set_style_text_font(video_dir_cb_new, &lv_font_montserratMedium_17, LV_PART_MAIN | LV_STATE_DEFAULT);
#else
    lv_obj_set_style_text_font(video_dir_cb_new, &lv_font_montserratMedium_22, LV_PART_MAIN | LV_STATE_DEFAULT);
#endif
    lv_obj_set_style_text_letter_space(video_dir_cb_new, 2, LV_PART_MAIN | LV_STATE_DEFAULT);

    //Set style for video_dir_cb_1. Part: LV_PART_INDICATOR, State: LV_STATE_DEFAULT
    lv_obj_set_style_radius(video_dir_cb_new, 20, LV_PART_INDICATOR | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(video_dir_cb_new, lv_color_make(0xff, 0xff, 0xff), LV_PART_INDICATOR | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(video_dir_cb_new, 0, LV_PART_INDICATOR | LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(video_dir_cb_new, lv_color_make(0xCE, 0xC2, 0x63), LV_PART_INDICATOR | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(video_dir_cb_new, 3, LV_PART_INDICATOR | LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(video_dir_cb_new, 255, LV_PART_INDICATOR | LV_STATE_DEFAULT);
    lv_obj_set_style_border_side(video_dir_cb_new, LV_BORDER_SIDE_FULL, LV_PART_INDICATOR | LV_STATE_DEFAULT);

    //Set style for video_dir_cb_1. Part: LV_PART_INDICATOR, State: LV_STATE_CHECKED
    lv_obj_set_style_radius(video_dir_cb_new, 20, LV_PART_INDICATOR | LV_STATE_CHECKED);
    lv_obj_set_style_bg_color(video_dir_cb_new, lv_color_make(0xCE, 0xC2, 0x63), LV_PART_INDICATOR | LV_STATE_CHECKED);
    lv_obj_set_style_bg_opa(video_dir_cb_new, 255, LV_PART_INDICATOR | LV_STATE_CHECKED);
    lv_obj_set_style_border_color(video_dir_cb_new, lv_color_make(0xCE, 0xC2, 0x63), LV_PART_INDICATOR | LV_STATE_CHECKED);
    lv_obj_set_style_border_width(video_dir_cb_new, 3, LV_PART_INDICATOR | LV_STATE_CHECKED);
    lv_obj_set_style_border_opa(video_dir_cb_new, 255, LV_PART_INDICATOR | LV_STATE_CHECKED);
    lv_obj_set_style_border_side(video_dir_cb_new, LV_BORDER_SIDE_FULL, LV_PART_INDICATOR | LV_STATE_CHECKED);
    lv_obj_set_size(video_dir_cb_new, CHECK_BOX_W, CHECK_BOX_H);
    lv_obj_set_align(video_dir_cb_new, LV_ALIGN_OUT_TOP_RIGHT);
    lv_obj_set_scrollbar_mode(video_dir_cb_new, LV_SCROLLBAR_MODE_OFF);
    lv_obj_add_flag(video_dir_cb_new, LV_OBJ_FLAG_HIDDEN);
    /*lv_obj_add_event_cb(video_dir_cb_new, video_dir_cb_event_handler, LV_EVENT_ALL, &guider_ui);*/

    //Write codes video_dir_img_19
    lv_obj_t *video_dir_img_new = lv_img_create(video_dir_view_new);

    //Set style for video_dir_img_19. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
    lv_obj_set_style_radius(video_dir_img_new, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(video_dir_img_new, true, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(video_dir_img_new, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(video_dir_img_new, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_img_recolor(video_dir_img_new, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_img_recolor_opa(video_dir_img_new, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_img_opa(video_dir_img_new, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_size(video_dir_img_new, DIR_IMG_W, DIR_IMG_H);
    lv_obj_set_align(video_dir_img_new, LV_ALIGN_TOP_MID);
    lv_obj_set_scrollbar_mode(video_dir_img_new, LV_SCROLLBAR_MODE_OFF);
    lv_obj_add_flag(video_dir_img_new, LV_OBJ_FLAG_CLICKABLE);
#if LV_USE_GUIBUILDER_SIMULATOR
    lv_img_set_src(video_dir_img_new, "A:\\wl83_411\\wifi_video_master\\ui_prj\\dvr_800x480\\import\\image\\file_dir.png");
#else
    lv_img_set_src(video_dir_img_new, gui_get_res_path(RES_FILE_DIR));
#endif
    lv_img_set_pivot(video_dir_img_new, 0, 0);
    lv_img_set_angle(video_dir_img_new, 0);
    lv_img_set_zoom(video_dir_img_new, 256);
    lv_obj_add_flag(video_dir_img_new, LV_OBJ_FLAG_EVENT_BUBBLE);
    lv_obj_add_flag(video_dir_img_new, LV_OBJ_FLAG_CLICKABLE);
    //Write codes video_dir_lbl_9
    lv_obj_t *video_dir_lbl_new = lv_label_create(video_dir_view_new);
    lv_label_set_text(video_dir_lbl_new, dir_name);
    lv_label_set_long_mode(video_dir_lbl_new, LV_LABEL_LONG_WRAP);

    //Set style for video_dir_lbl_9. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
    lv_obj_set_style_radius(video_dir_lbl_new, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(video_dir_lbl_new, lv_color_make(0x21, 0x95, 0xf6), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(video_dir_lbl_new, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(video_dir_lbl_new, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(video_dir_lbl_new, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(video_dir_lbl_new, lv_color_make(0xFF, 0xFF, 0xFF), LV_PART_MAIN | LV_STATE_DEFAULT);
#if THREE_WAY_ENABLE && (LCD_W < 800)
    //三路小屏幕简单处理,如更换其他屏幕且缩放了UI,请自行更换字体
    //这里字体对应公版640*360 UI工程
    lv_obj_set_style_text_font(video_dir_lbl_new, &lv_font_montserratMedium_12, LV_PART_MAIN | LV_STATE_DEFAULT);
#else
    lv_obj_set_style_text_font(video_dir_lbl_new, &lv_font_montserratMedium_16, LV_PART_MAIN | LV_STATE_DEFAULT);
#endif
    lv_obj_set_style_text_letter_space(video_dir_lbl_new, 2, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(video_dir_lbl_new, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(video_dir_lbl_new, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(video_dir_lbl_new, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(video_dir_lbl_new, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(video_dir_lbl_new, 8, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(video_dir_lbl_new, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_size(video_dir_lbl_new, DIR_CONT_W, DIR_CONT_H - DIR_IMG_H - 5);
    lv_obj_align_to(video_dir_lbl_new, video_dir_img_new,
                    LV_ALIGN_OUT_BOTTOM_MID, -5, 0);
    lv_obj_set_scrollbar_mode(video_dir_lbl_new, LV_SCROLLBAR_MODE_OFF);
    lv_obj_add_flag(video_dir_lbl_new, LV_OBJ_FLAG_EVENT_BUBBLE);

    lv_obj_add_event_cb(video_dir_view_new, video_dir_view_9_event_handler, LV_EVENT_ALL, &guider_ui);
}

static void video_file_view_1_event_handler(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    lv_ui *ui = (lv_ui *)lv_event_get_user_data(e);
    lv_obj_t *src = lv_event_get_target(e);
    switch (code) {
    case LV_EVENT_CLICKED: {
        if (pipeline_state == PIPELINE_RUNING) {
            return;
        } else if (pipeline_state == PIPELINE_IDLE) {
            pipeline_state = PIPELINE_EXIT;
            jpeg2yuv_pipeline_uninit();
        }

        //记录当前页面和滚动条值
        to_play_video_page = cur_page;
        lv_ui_video_file *ui_scr = ui_get_scr_ptr(&guider_ui, GUI_SCREEN_VIDEO_FILE);
        if (!ui_scr) {
            return;
        }
        lv_obj_t *contain = lv_obj_get_child(ui_scr->video_file, 3);
        cur_scroll_val = lv_obj_get_scroll_y(contain);


        extern int browser_open_file(void *file, char *path, char *name);
        lv_obj_t *label = lv_obj_get_child(src, 2);
        if (!label) {
            lv_obj_t *parent = lv_obj_get_parent(src);
            label = lv_obj_get_child(parent, 2);
        }
        const char *text1 = lv_label_get_text(label); //文件名
        const char *text2 = lv_label_get_text(ui_scr->video_file_lbl_path); //路径
        char *file_path;
        asprintf(&file_path, "%s%s", text2, text1);
        printf("cur path: %s\n", file_path);
#if LV_USE_GUIBUILDER_SIMULATOR
#else
        FILE *fd = NULL;//文件句柄指针
        fd = fopen(file_path, "r");
        if (fd) {
            browser_open_file(fd, text2, text1);
        }
        free(file_path);
        /*fclose(fd);   */
#endif
        gui_scr_t *screen = gui_scr_get(GUI_SCREEN_VIDEO_PLAY);
        if (screen == NULL) {
            screen = gui_scr_create(GUI_SCREEN_VIDEO_PLAY, "video_play", guider_ui.video_play, (gui_scr_setup_cb_t)setup_scr_video_play, (gui_scr_unload_cb_t)unload_scr_video_play);
        }
        ui_load_scr_anim(ui, screen, LV_SCR_LOAD_ANIM_NONE, 0, 0, true, true, false);

    }
    break;
    default:
        break;
    }

}

static void reset_scroll_and_line(lv_obj_t *contain)
{
    int max_line;
    lv_obj_update_layout(contain);
    int  max_scroll_y = lv_obj_get_scroll_bottom(contain);

    if (cur_scroll_val > max_scroll_y) {
        cur_scroll_val = max_scroll_y;
        cur_scroll_val = cur_scroll_val < 0 ? 0 : cur_scroll_val;
        line = cur_scroll_val / (IMG_CONT_H + IMG_CONT_ROW_SPACE);
        max_line = ceil((float)create_num / 3) - 3;
        if (line > max_line) {
            line  = max_line;
        }
        last_line = line;
    }
}


static void next_page(void)
{
    int start, end, remain;

    cur_page++;
    printf("cur Page %d\n", cur_page);
    if (cur_page > total_file_page) {
        cur_page = total_file_page;
        return;
    }
    line = 0;
    last_line = line;
    lv_ui_video_file *ui_scr = ui_get_scr_ptr(&guider_ui, GUI_SCREEN_VIDEO_FILE);
    if (!ui_scr) {
        return;
    }
    lv_obj_t *contain = lv_obj_get_child(ui_scr->video_file, 3);
    lv_obj_clean(contain);
    create_page(cur_page);

    start = (line * line_obj_num) + (cur_page - 1) * ONE_PAGE_MAX_NUM;
    remain = create_num + (cur_page - 1) * ONE_PAGE_MAX_NUM - start;
    remain = remain > img_buf_num ? img_buf_num : remain;
    end = start + remain;
    update_img_text(start, end, 0);
    dec_list_cur_page(cur_page); //保存当前页数在结构体
}

static void prev_page(void)
{
    int start, remain, end;
    int line_h, max_scroll_val;
    int max_line;
    cur_page--;
    printf("cur Page %d\n", cur_page);
    if (cur_page < 1) {
        cur_page = 1;
        return;
    }
    lv_ui_video_file *ui_scr = ui_get_scr_ptr(&guider_ui, GUI_SCREEN_VIDEO_FILE);
    if (!ui_scr) {
        return;
    }
    lv_obj_t *contain = lv_obj_get_child(ui_scr->video_file, 3);
    lv_obj_clean(contain);
    create_page(cur_page);
    //上一页的底部
    max_line = ceil((float)create_num / line_obj_num) - line_obj_num;
    line = max_line;
    last_line = line;
    line_h = IMG_CONT_H + IMG_CONT_ROW_SPACE;
    max_scroll_val = (line_h * ceil((float)create_num / line_obj_num) - line_h * 2);
    lv_obj_scroll_to_y(contain, max_scroll_val, LV_ANIM_OFF);

    start = (line * line_obj_num) + (cur_page - 1) * ONE_PAGE_MAX_NUM;
    remain = create_num + (cur_page - 1) * ONE_PAGE_MAX_NUM - start;
    remain = remain > img_buf_num ? img_buf_num : remain;
    end = start + remain;
    update_img_text(start, end, 0);
    dec_list_cur_page(cur_page); //保存当前页数在结构体

}

static void add_img_text(lv_obj_t *obj)
{
    //img
    lv_obj_t *video_file_img_new_src_1 = lv_img_create(obj);
    lv_obj_set_style_radius(video_file_img_new_src_1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(video_file_img_new_src_1, true, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(video_file_img_new_src_1, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(video_file_img_new_src_1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_img_recolor(video_file_img_new_src_1, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_img_recolor_opa(video_file_img_new_src_1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_img_opa(video_file_img_new_src_1, 200, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_pos(video_file_img_new_src_1, 0, 0);
    lv_obj_set_size(video_file_img_new_src_1, IMG_W, IMG_H);
    lv_obj_set_scrollbar_mode(video_file_img_new_src_1, LV_SCROLLBAR_MODE_OFF);
    lv_obj_clear_flag(video_file_img_new_src_1, LV_OBJ_FLAG_SCROLLABLE);

    //path
    lv_obj_t *video_file_lbl_new_path_1 = lv_label_create(obj);
    lv_label_set_long_mode(video_file_lbl_new_path_1, LV_LABEL_LONG_WRAP);
    lv_obj_set_style_radius(video_file_lbl_new_path_1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(video_file_lbl_new_path_1, lv_color_make(0x21, 0x95, 0xf6), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(video_file_lbl_new_path_1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(video_file_lbl_new_path_1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(video_file_lbl_new_path_1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(video_file_lbl_new_path_1, lv_color_make(0xFF, 0xFF, 0xFF), LV_PART_MAIN | LV_STATE_DEFAULT);
#if THREE_WAY_ENABLE && (LCD_W < 800)
    //三路小屏幕简单处理,如更换其他屏幕且缩放了UI,请自行更换字体
    //这里字体对应公版640*360 UI工程
    lv_obj_set_style_text_font(video_file_lbl_new_path_1, &lv_font_montserratMedium_12, LV_PART_MAIN | LV_STATE_DEFAULT);
#else
    lv_obj_set_style_text_font(video_file_lbl_new_path_1, &lv_font_montserratMedium_16, LV_PART_MAIN | LV_STATE_DEFAULT);
#endif
    lv_obj_set_style_text_letter_space(video_file_lbl_new_path_1, 2, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(video_file_lbl_new_path_1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(video_file_lbl_new_path_1, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(video_file_lbl_new_path_1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(video_file_lbl_new_path_1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(video_file_lbl_new_path_1, 8, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(video_file_lbl_new_path_1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_size(video_file_lbl_new_path_1, IMG_W, IMG_CONT_H - IMG_H - 5);
    lv_obj_align_to(video_file_lbl_new_path_1, video_file_img_new_src_1,
                    LV_ALIGN_OUT_BOTTOM_LEFT, -5, 0);
    lv_label_set_long_mode(video_file_lbl_new_path_1, LV_LABEL_LONG_WRAP);
    lv_obj_set_scrollbar_mode(video_file_lbl_new_path_1, LV_SCROLLBAR_MODE_OFF);

    // img label
    lv_obj_t *video_file_img_new_flag_1 = lv_img_create(obj);
    lv_obj_set_style_radius(video_file_img_new_flag_1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(video_file_img_new_flag_1, true, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(video_file_img_new_flag_1, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(video_file_img_new_flag_1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_img_recolor(video_file_img_new_flag_1, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_img_recolor_opa(video_file_img_new_flag_1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_img_opa(video_file_img_new_flag_1, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_center(video_file_img_new_flag_1);
    lv_obj_set_size(video_file_img_new_flag_1, VIDEO_FILE_IMG_W, VIDEO_FILE_IMG_H);
    lv_obj_set_scrollbar_mode(video_file_img_new_flag_1, LV_SCROLLBAR_MODE_OFF);
    lv_obj_add_flag(video_file_img_new_flag_1, LV_OBJ_FLAG_CLICKABLE);
#if LV_USE_GUIBUILDER_SIMULATOR
    lv_img_set_src(video_file_img_new_flag_1, "A:\\wl83_411\\wifi_video_master\\ui_prj\\dvr_800x480\\import\\image\\play_s.png");
#else
    lv_img_set_src(video_file_img_new_flag_1, gui_get_res_path(RES_PLAY));
#endif
    lv_img_set_pivot(video_file_img_new_flag_1, 0, 0);
    lv_img_set_angle(video_file_img_new_flag_1, 0);
    lv_img_set_zoom(video_file_img_new_flag_1, 256);
    lv_obj_clear_flag(video_file_img_new_flag_1, LV_OBJ_FLAG_SCROLLABLE);
    lv_obj_add_flag(video_file_img_new_flag_1, LV_OBJ_FLAG_EVENT_BUBBLE);

    //add lock_flag
    lv_obj_t *video_file_img_lock = lv_img_create(obj);

    //Set style for video_file_img_lock. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
    lv_obj_set_style_radius(video_file_img_lock, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(video_file_img_lock, true, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(video_file_img_lock, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(video_file_img_lock, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_img_recolor(video_file_img_lock, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_img_recolor_opa(video_file_img_lock, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_img_opa(video_file_img_lock, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_align(video_file_img_lock, LV_ALIGN_TOP_RIGHT);
    lv_obj_set_size(video_file_img_lock, LOCK_IMG_W, LOCK_IMG_H);
    lv_obj_set_scrollbar_mode(video_file_img_lock, LV_SCROLLBAR_MODE_OFF);
    lv_obj_add_flag(video_file_img_lock, LV_OBJ_FLAG_CLICKABLE);
#if LV_USE_GUIBUILDER_SIMULATOR
    lv_img_set_src(video_file_img_lock, "A:\\wl83_723\\wifi_video_master\\ui_prj\\Application1\\import\\image\\lock88.png");
#else
    lv_img_set_src(video_file_img_lock, gui_get_res_path(RES_LOCK_FLAG));
#endif
    lv_img_set_pivot(video_file_img_lock, 0, 0);
    lv_img_set_angle(video_file_img_lock, 0);
    lv_img_set_zoom(video_file_img_lock, 256);

}


static void update_img_text(int start_index, int end_index, u8 dir)
{
    static int img_index = 0;
    static int last_img_index = 0;
    static  u8 last_dir = 0;
    FILE *fp;
    char name[50];
    char *full_name;
    int update_num = end_index - start_index;

    if (dir != last_dir) {
        img_index = last_img_index;
    }
    last_dir = dir;
    lv_ui_video_file *ui_scr = ui_get_scr_ptr(&guider_ui, GUI_SCREEN_VIDEO_FILE);
    if (!ui_scr) {
        return;
    }
    lv_obj_t *contain = lv_obj_get_child(ui_scr->video_file, 3);
    while (start_index < end_index) {
        lv_obj_t *img_cont = lv_obj_get_child(contain, start_index % ONE_PAGE_MAX_NUM);
        add_img_text(img_cont);

        lv_obj_t *img = lv_obj_get_child(img_cont, 1);
        lv_obj_t *text = lv_obj_get_child(img_cont, 2);
        lv_obj_t *img_label = lv_obj_get_child(img_cont, 3);
        lv_obj_t *img_lock_flag = lv_obj_get_child(img_cont, 4); //文件是否加锁标志
#if FILE_DISP_REVERSE_ORDER
        //反序显示
        fp = fselect(fs_file, FSEL_BY_NUMBER, total_file_num - start_index);
#else
        //正序显示
        fp = fselect(fs_file, FSEL_BY_NUMBER, start_index + 1);
#endif
        if (!fp) {
            return;
        }
        fget_name(fp, name, sizeof(name));
        lv_label_set_text(text, name);
        int attr;
        fget_attr(fp, &attr);
        if (attr & F_ATTR_RO) {
        } else if (!(attr & F_ATTR_RO)) {
            lv_obj_add_flag(img_lock_flag, LV_OBJ_FLAG_HIDDEN);  //文件未加锁，去掉加锁标识
        }
        fclose(fp);
        asprintf(&full_name, "%s%s", dir_path, name);
        //缩略图
        if (strcmp(lv_fs_get_ext(name), "jpg") == 0 || strcmp(lv_fs_get_ext(name), "JPG") == 0) {
            lv_obj_add_flag(img_label, LV_OBJ_FLAG_HIDDEN);
        }

        int msg[3];
        msg[0] = (int)full_name;
        msg[1] = img_index;
        msg[2] = --update_num;
        int err = os_taskq_post_type(DECODE_TASK_NAME, Q_MSG, 3, msg);
        lv_img_set_src(img, &image_dsc_list[img_index]);

        start_index++;

        last_img_index = img_index;
        if (dir == 0) {
            img_index = (img_index + 1) % img_buf_num;
        } else {
            img_index = (img_index - 1 + img_buf_num) % img_buf_num;
        }

    }

    //确保每次操作buf数量正确
    while (end_index % line_obj_num) {
        last_img_index = img_index;
        if (dir == 0) {
            img_index = (img_index + 1) % img_buf_num;
        } else {
            img_index = (img_index - 1 + img_buf_num) % img_buf_num;
        }
        end_index++;
    }

    //清空不显示的容器
    if (dir == 0) {
        for (int i = last_line * line_obj_num; i < line * line_obj_num; i++) {
            lv_obj_t *clean_cont = lv_obj_get_child(contain, i);
            lv_obj_t *child = lv_obj_get_child(clean_cont, 1);
            while (child) {
                lv_obj_del(child);
                child = lv_obj_get_child(clean_cont, 1);
            }
        }
    } else {
        for (int i = line * line_obj_num + max_show_num + line_obj_num; i < last_line * line_obj_num + max_show_num + line_obj_num; i++) {
            if (i > create_num - 1) {
                continue;
            }
            lv_obj_t *clean_cont = lv_obj_get_child(contain, i);
            lv_obj_t *child = lv_obj_get_child(clean_cont, 1);
            while (child) {
                lv_obj_del(child);
                child = lv_obj_get_child(clean_cont, 1);
            }
        }
    }

    send_msg2file_num();
}

void scroll_update_position(int scroll_val)
{
    if (deleting_flag) {
        //正在执行删除操作，防止进入scroll事件
        return;
    }
    int start, end, remain;
    int max_line;
    int dir;
    if (scroll_val < -EXTRA_SPACE) {
        prev_page();
        return;
    }

    if (scroll_val > (ONE_PAGE_MAX_NUM - max_show_num) / line_obj_num * (IMG_CONT_H + IMG_CONT_ROW_SPACE) +  EXTRA_SPACE) {
        next_page();
        return;
    }

    line = scroll_val / (IMG_CONT_H + IMG_CONT_ROW_SPACE);
    max_line = ceil((float)create_num / line_obj_num) - (img_buf_num / line_obj_num);
    if (line > max_line) {
        line  = max_line;
    }

    //刷新图片
    if (line != last_line) {
        dir = line > last_line ? 0 : 1;
        if (dir == 0) {
            start = ((last_line + 1) * line_obj_num + max_show_num) + (cur_page - 1) * ONE_PAGE_MAX_NUM;
            remain = create_num + (cur_page - 1) * ONE_PAGE_MAX_NUM - start;
            remain = remain > (line - last_line) * line_obj_num ? (line - last_line) * line_obj_num : remain;
            end = start + remain;
            update_img_text(start, end, dir);
        } else {
            start = (line * line_obj_num) + (cur_page - 1) * ONE_PAGE_MAX_NUM;
            end = start + (last_line - line) * line_obj_num;
            update_img_text(start, end, dir);
        }
    }
    last_line = line;
    lv_ui_video_file *ui_scr = ui_get_scr_ptr(&guider_ui, GUI_SCREEN_VIDEO_FILE);
    if (!ui_scr) {
        return;
    }
    edit_lock_file(ui_scr->video_file, 0);

}

void file_list_up(void)
{
    lv_ui_video_file *ui_scr = ui_get_scr_ptr(&guider_ui, GUI_SCREEN_VIDEO_FILE);
    if (!ui_scr) {
        return;
    }
    lv_obj_t *contain = lv_obj_get_child(ui_scr->video_file, 3);

    int cur_scroll_val = lv_obj_get_scroll_y(contain);
    int line_h = IMG_CONT_H + IMG_CONT_ROW_SPACE;
    int set_val = cur_scroll_val - line_h;
    int min_scroll_val = 0;
    if (set_val < min_scroll_val) {
        set_val = min_scroll_val;
        lv_obj_scroll_to_y(contain, set_val, LV_ANIM_OFF);
        prev_page();
    } else {
        lv_obj_scroll_to_y(contain, set_val, LV_ANIM_OFF);
    }
}

void file_list_down(void)
{
    lv_ui_video_file *ui_scr = ui_get_scr_ptr(&guider_ui, GUI_SCREEN_VIDEO_FILE);
    if (!ui_scr) {
        return;
    }
    lv_obj_t *contain = lv_obj_get_child(ui_scr->video_file, 3);

    int cur_scroll_val = lv_obj_get_scroll_y(contain);
    int line_h = IMG_CONT_H + IMG_CONT_ROW_SPACE;
    int set_val = cur_scroll_val + line_h;

    int max_scroll_val = (line_h * ceil((float)create_num / line_obj_num) - line_h * 2);
    if (set_val > max_scroll_val) {
        set_val = max_scroll_val;
        lv_obj_scroll_to_y(contain, set_val, LV_ANIM_OFF);
        next_page();
    } else {
        lv_obj_scroll_to_y(contain, set_val, LV_ANIM_OFF);
    }
}



//页面加载
void video_dir_screen_load(void)
{
    lv_ui_video_dir *ui_scr = ui_get_scr_ptr(&guider_ui, GUI_SCREEN_VIDEO_DIR);
    if (!ui_scr) {
        return;
    }
    if (storage_device_ready() == 0) {
        //sd卡未挂載
        printf("-NOT SD \n");
        video_dec_post_msg("noCard", 1);
        return;
    }
    if (dir_path) {
        free(dir_path);
        dir_path = NULL;
    }
    u8 name[128];
    struct vfscan *fs = NULL;
    fs = fscan(CONFIG_DEC_ROOT_PATH, "-d -tPNGBINAVITTLDAT -sn", 2);
    if (!fs || fs->file_number == 0) {
        printf("fscan err!!");
        video_dec_post_msg("noFile", 1);
    } else {
        void *dir = fselect(fs, FSEL_FIRST_FILE, 0);
        for (int i = 0; i < fs->file_number; i++) {
            fget_name(dir, name, sizeof(name));
            printf("name %s\n", name);
            fclose((FILE *)dir);
            create_dir(i, name);
            dir = fselect(fs, FSEL_NEXT_FILE, 0);
        }
        fscan_release(fs);
        lv_obj_update_layout(ui_scr->video_dir);
    }
}

static void create_page(int page)
{
    if (page < total_file_page) {
        create_num = total_file_num < ONE_PAGE_MAX_NUM ? total_file_num : ONE_PAGE_MAX_NUM;
    } else {
        create_num = total_file_num - ONE_PAGE_MAX_NUM * (page - 1);
    }
    lv_ui_video_file *ui_scr = ui_get_scr_ptr(&guider_ui, GUI_SCREEN_VIDEO_FILE);
    if (!ui_scr) {
        return;
    }
    lv_obj_t *contain = lv_obj_get_child(ui_scr->video_file, 3);
    lv_group_t *def_group = lv_group_get_default();
    for (int i = 0; i < create_num; i++) {
        lv_obj_t *img_cont = lv_obj_create(contain);
        lv_obj_set_style_radius(img_cont, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_set_style_bg_color(img_cont, lv_color_make(0x00, 0x00, 0x00), LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_set_style_bg_opa(img_cont, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_set_style_shadow_width(img_cont, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_set_style_border_color(img_cont, lv_color_make(0x2F, 0x63, 0x8F), LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_set_style_border_width(img_cont, 2, LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_set_style_border_opa(img_cont, LV_OPA_50, LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_set_style_border_side(img_cont, LV_BORDER_SIDE_FULL, LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_set_style_pad_left(img_cont, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_set_style_pad_right(img_cont, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_set_style_pad_top(img_cont, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_set_style_pad_bottom(img_cont, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

        //Set style for img_cont. Part: LV_PART_MAIN, State: LV_STATE_FOCUS_KEY
        lv_obj_set_style_radius(img_cont, 0, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
        lv_obj_set_style_bg_color(img_cont, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN | LV_STATE_FOCUS_KEY);
        lv_obj_set_style_bg_opa(img_cont, 0, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
        lv_obj_set_style_shadow_width(img_cont, 0, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
        lv_obj_set_style_border_width(img_cont, 0, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
        lv_obj_set_style_outline_color(img_cont, lv_color_make(0x21, 0x95, 0xf6), LV_PART_MAIN | LV_STATE_FOCUS_KEY);
        lv_obj_set_style_outline_width(img_cont, 2, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
        lv_obj_set_style_outline_opa(img_cont, 128, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
        lv_obj_set_style_outline_pad(img_cont, 2, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
        lv_obj_set_style_pad_left(img_cont, 0, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
        lv_obj_set_style_pad_right(img_cont, 0, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
        lv_obj_set_style_pad_top(img_cont, 0, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
        lv_obj_set_style_pad_bottom(img_cont, 0, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
        lv_obj_set_size(img_cont, IMG_CONT_W, IMG_CONT_H);
        lv_obj_clear_flag(img_cont, LV_OBJ_FLAG_SCROLLABLE);
        lv_obj_set_scrollbar_mode(img_cont, LV_SCROLLBAR_MODE_OFF);
        lv_group_add_obj(def_group, img_cont);
        lv_obj_add_event_cb(img_cont, video_file_view_1_event_handler, LV_EVENT_ALL, &guider_ui);

        lv_obj_t *video_file_cb_new = lv_checkbox_create(img_cont);
        lv_checkbox_set_text(video_file_cb_new, "checkbox");

        //Set style for video_file_cb_1. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
        lv_obj_set_style_radius(video_file_cb_new, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_set_style_bg_color(video_file_cb_new, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_set_style_bg_opa(video_file_cb_new, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_set_style_shadow_width(video_file_cb_new, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_set_style_border_color(video_file_cb_new, lv_color_make(0xe1, 0xe6, 0xee), LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_set_style_border_width(video_file_cb_new, 1, LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_set_style_border_opa(video_file_cb_new, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_set_style_border_side(video_file_cb_new, LV_BORDER_SIDE_NONE, LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_set_style_text_color(video_file_cb_new, lv_color_make(0x00, 0x00, 0x00), LV_PART_MAIN | LV_STATE_DEFAULT);
#if THREE_WAY_ENABLE && (LCD_W < 800)
        //三路小屏幕简单处理,如更换其他屏幕且缩放了UI,请自行更换字体
        //这里字体对应公版640*360 UI工程
        lv_obj_set_style_text_font(video_file_cb_new, &lv_font_montserratMedium_17, LV_PART_MAIN | LV_STATE_DEFAULT);
#else
        lv_obj_set_style_text_font(video_file_cb_new, &lv_font_montserratMedium_22, LV_PART_MAIN | LV_STATE_DEFAULT);
#endif
        lv_obj_set_style_text_letter_space(video_file_cb_new, 2, LV_PART_MAIN | LV_STATE_DEFAULT);

        //Set style for video_dir_cb_1. Part: LV_PART_INDICATOR, State: LV_STATE_DEFAULT
        lv_obj_set_style_radius(video_file_cb_new, 20, LV_PART_INDICATOR | LV_STATE_DEFAULT);
        lv_obj_set_style_bg_color(video_file_cb_new, lv_color_make(0xff, 0xff, 0xff), LV_PART_INDICATOR | LV_STATE_DEFAULT);
        lv_obj_set_style_bg_opa(video_file_cb_new, 0, LV_PART_INDICATOR | LV_STATE_DEFAULT);
        lv_obj_set_style_border_color(video_file_cb_new, lv_color_make(0xCE, 0xC2, 0x63), LV_PART_INDICATOR | LV_STATE_DEFAULT);
        lv_obj_set_style_border_width(video_file_cb_new, 3, LV_PART_INDICATOR | LV_STATE_DEFAULT);
        lv_obj_set_style_border_opa(video_file_cb_new, 255, LV_PART_INDICATOR | LV_STATE_DEFAULT);
        lv_obj_set_style_border_side(video_file_cb_new, LV_BORDER_SIDE_FULL, LV_PART_INDICATOR | LV_STATE_DEFAULT);

        //Set style for video_dir_cb_1. Part: LV_PART_INDICATOR, State: LV_STATE_CHECKED
        lv_obj_set_style_radius(video_file_cb_new, 20, LV_PART_INDICATOR | LV_STATE_CHECKED);
        lv_obj_set_style_bg_color(video_file_cb_new, lv_color_make(0xCE, 0xC2, 0x63), LV_PART_INDICATOR | LV_STATE_CHECKED);
        lv_obj_set_style_bg_opa(video_file_cb_new, 255, LV_PART_INDICATOR | LV_STATE_CHECKED);
        lv_obj_set_style_border_color(video_file_cb_new, lv_color_make(0xCE, 0xC2, 0x63), LV_PART_INDICATOR | LV_STATE_CHECKED);
        lv_obj_set_style_border_width(video_file_cb_new, 3, LV_PART_INDICATOR | LV_STATE_CHECKED);
        lv_obj_set_style_border_opa(video_file_cb_new, 255, LV_PART_INDICATOR | LV_STATE_CHECKED);
        lv_obj_set_style_border_side(video_file_cb_new, LV_BORDER_SIDE_FULL, LV_PART_INDICATOR | LV_STATE_CHECKED);
        lv_obj_set_size(video_file_cb_new, CHECK_BOX_W, CHECK_BOX_H);
        lv_obj_set_align(video_file_cb_new, LV_ALIGN_OUT_TOP_LEFT);
        lv_obj_set_scrollbar_mode(video_file_cb_new, LV_SCROLLBAR_MODE_OFF);
        lv_obj_add_flag(video_file_cb_new, LV_OBJ_FLAG_HIDDEN);
        lv_obj_add_event_cb(video_file_cb_new, video_dir_cb_event_handler, LV_EVENT_ALL, &guider_ui);

    }
}

static void post_func_flush_img(void)
{
    lv_ui_video_file *ui_scr = ui_get_scr_ptr(&guider_ui, GUI_SCREEN_VIDEO_FILE);
    if (!ui_scr) {
        return;
    }
    if (lv_obj_is_valid(ui_scr->video_file)) {
        lv_obj_t *contain = lv_obj_get_child(ui_scr->video_file, 3);
        if (lv_obj_is_valid(contain)) {
            lv_obj_invalidate(contain);
        }
    }
}

static void dec_img_task(void)
{
    int res;
    int kill_flag = 0;
    int msg[8];

    while (1) {
        res = os_task_pend("taskq", msg, ARRAY_SIZE(msg));

        switch (res) {
        case OS_TASKQ:
            switch (msg[0]) {
            case Q_EVENT:
                break;
            case Q_MSG:
                char *full_name = (char *)msg[1];
                int img_index = msg[2];
                int update_num = msg[3];

                jpeg2yuv_with_pipeline(full_name, img_buf_list[img_index], IMG_W, IMG_H);
                free(full_name);
                if (!update_num) {
                    pipeline_state = PIPELINE_IDLE;
                    //刷新UI
                    lvgl_rpc_post_func(post_func_flush_img, 0);
                }
                break;
            case Q_USER:
                pipeline_state = PIPELINE_STOP;
                kill_flag = msg[1];
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

        if (kill_flag) {
            jpeg2yuv_pipeline_uninit();
            printf("kill task:%s \n", DECODE_TASK_NAME);
            break;
        }
    }

}

void video_file_screen_load(void)
{
    int start, end, remain;

    if (storage_device_ready() == 0) {
        //sd卡未挂載 b
        printf("-NOT SD \n");
        video_dec_post_msg("noCard", 0);
        return;
    }
    lv_ui_video_file *ui_scr = ui_get_scr_ptr(&guider_ui, GUI_SCREEN_VIDEO_FILE);
    if (!ui_scr) {
        return;
    }
    lv_obj_t *contain = lv_obj_get_child(ui_scr->video_file, 3);
    lv_obj_set_style_pad_column(contain, IMG_CONT_COL_SPACE, 0);  // 设置列间距
    lv_obj_set_style_pad_row(contain, IMG_CONT_ROW_SPACE, 0);     // 设置行间距
    lv_obj_clear_flag(contain, LV_OBJ_FLAG_SCROLL_CHAIN_HOR);
    lv_obj_set_scroll_dir(contain, LV_DIR_VER);

    lv_obj_set_style_pad_all(contain, 0, 0);                  // 设置所有内边距为0
    lv_obj_set_style_base_dir(contain, LV_BASE_DIR_LTR, 0);   // 设置基础方向为从左到右
    lv_obj_set_flex_flow(contain, LV_FLEX_FLOW_ROW_WRAP);     // 设置Flex流动方向为行包裹

    lv_coord_t container_width = lv_obj_get_width(contain);     // 父控件宽度
    lv_coord_t container_height = lv_obj_get_height(contain);

    lv_coord_t column_space = IMG_CONT_COL_SPACE;              // 列间距
    lv_coord_t row_space = IMG_CONT_ROW_SPACE;                 // 行间距

    lv_coord_t child_width = IMG_CONT_W;                        // 子控件宽度
    lv_coord_t child_height = IMG_CONT_H;

    // 计算每行控件数
    line_obj_num = (container_width + column_space) / (child_width + column_space);
    max_show_num = (container_height + row_space) / (child_height + row_space) * line_obj_num;
    img_buf_num = max_show_num + line_obj_num;
    printf("line_obj_num:%d max_show_num:%d img_buf_num:%d \n\n", line_obj_num, max_show_num, img_buf_num);

    thread_fork(DECODE_TASK_NAME, 10, 1024, 1024, &task_pid, dec_img_task, NULL);
    fs_file = fscan(dir_path, "-tMOVJPGAVI -sn", 3);
    if (!fs_file) {
        printf("fscan err !!!");
        video_dec_post_msg("noCard", 0);
        return;
    } else if (fs_file->file_number == 0) {
        printf("file number is 0 !!");
        video_dec_post_msg("noFile", 0);
        total_file_num = fs_file->file_number;
        total_file_page  = ceil((float)total_file_num / ONE_PAGE_MAX_NUM);
        dec_list_tol_page(total_file_page); //保存总页数在结构体
        dec_list_file_num(total_file_num); //保存文件总数在结构体
        line = 0;
    } else {
        total_file_num = fs_file->file_number;
        total_file_page  = ceil((float)total_file_num / ONE_PAGE_MAX_NUM);
        dec_list_tol_page(total_file_page); //保存总页数在结构体
        dec_list_file_num(total_file_num); //保存文件总数在结构体
        printf("total file:%d total page: %d\n", total_file_num, total_file_page);

        for (int i = 0; i < img_buf_num; i++) {
            u32 size = IMG_W * IMG_H * 2;
            img_buf_list[i] = malloc(size);
            if (img_buf_list[i] == NULL) {
                printf("img_buf_list[%d] malloc fail \n", i);
                break;
            }
            memset(img_buf_list[i], 0x00, size);
            image_dsc_list[i].header.always_zero = 0;
            image_dsc_list[i].header.w = IMG_W;
            image_dsc_list[i].header.h = IMG_H;
            image_dsc_list[i].data_size = IMG_W * IMG_H * 2;
            image_dsc_list[i].header.cf = LV_IMG_CF_TRUE_COLOR;
            image_dsc_list[i].data = img_buf_list[i];
        }

        if (to_play_video_page) {
            cur_page = to_play_video_page > total_file_page ? total_file_page : to_play_video_page;
            dec_list_cur_page(cur_page); //保存当前页数在结构体
            create_page(cur_page);
            //文件删除后需要判断一下滚动条值是c过当前最大值
            reset_scroll_and_line(contain);

            lv_obj_scroll_to_y(contain, cur_scroll_val, LV_ANIM_OFF);
            start = line * line_obj_num  + (cur_page - 1) * ONE_PAGE_MAX_NUM;
            remain = create_num + (cur_page - 1) * ONE_PAGE_MAX_NUM - start;
            remain = remain > img_buf_num ? img_buf_num : remain;
            end = start + remain;
            update_img_text(start, end, 0);
            to_play_video_page = 0;
        } else {
            cur_page = 1;
            line = 0;
            last_line = 0;
            create_page(cur_page);
            start = line * line_obj_num  + (cur_page - 1) * ONE_PAGE_MAX_NUM;
            remain = create_num + (cur_page - 1) * ONE_PAGE_MAX_NUM - start;
            remain = remain > img_buf_num ? img_buf_num : remain;
            end = start + remain;
            update_img_text(start, end, 0);
        }
    }
    send_msg2file_num();
}

void video_file_screen_unload(void)
{
    if (deleting_flag) {
        to_play_video_page = cur_page;
        lv_ui_video_file *ui_scr = ui_get_scr_ptr(&guider_ui, GUI_SCREEN_VIDEO_FILE);
        if (!ui_scr) {
            printf("ui_get_scr_ptr err \n");
            return;
        }
        lv_obj_t *contain = lv_obj_get_child(ui_scr->video_file, 3);
        cur_scroll_val = lv_obj_get_scroll_y(contain);

        if (lv_obj_is_valid(ui_scr->video_file_view_3)) {
            lv_obj_clean(ui_scr->video_file_view_3);
        }
        deleting_flag = 0;
    }

    int msg = 1;
    os_taskq_post_type(DECODE_TASK_NAME, Q_USER, 1, &msg);
    thread_kill(&task_pid, KILL_WAIT);
    task_pid = 0;

    if (fs_file) {
        fscan_release(fs_file);
        fs_file = NULL;
    }
    for (int i = 0; i < img_buf_num; i++) {
        if (img_buf_list[i]) {
            free(img_buf_list[i]);
            img_buf_list[i] = NULL;
        }
    }
}


/**************************************************************************************************************/
/**************************************************************************************************************/
//取出缩略图
static u8 *find_jpg_thumbnails(u8 *stream, int len, int *thm_len)
{
    u8  marker;
    int chunk_len = 0;
    int offset = 0;

    if ((stream[0] != 0xFF) || (stream[1] != 0xD8)) {
        return NULL;
    }

    stream += 2;
    while (1) {
        if (*stream++ != 0xFF) {
            return NULL;
        }

        while (*stream == 0xFF) {
            stream++;
        }

        marker = *stream++;
        chunk_len = (u16)(stream[0] << 8) | stream[1];
        if (marker == 0xE1) {
            stream += 2;
            while (1) {
                if ((stream[offset] == 0xFF) && (stream[offset + 1] == 0xD8)) {
                    break;
                }

                if (++offset > (chunk_len - 2)) {
                    return NULL;
                }
            }

            *thm_len = chunk_len - 2 - offset;
            return stream + offset;
        }
        stream += chunk_len;
    }

    return NULL;
}
static int check_fourcc(u8 *buf, const char *fourcc)
{
    return memcmp(buf, fourcc, 4) == 0;
}

static int read_fourcc_and_size(FILE *fd, u8 *fourcc, u32 *size)
{
    if (fread(fourcc, 4, 1, fd) != 4) {
        return -1;
    }
    if (fread(size, 4, 1, fd) != 4) {
        return -1;
    }
    return 0;
}

//获取AVI文件的第一帧
static u8 *get_avi_first_frame(FILE *fd, u32 *jpeg_size)
{
    static int read_times = 0;
    char fourcc[4];
    u32 size;

    fseek(fd, 0, SEEK_SET);

    if (read_fourcc_and_size(fd, fourcc, &size) != 0  || !check_fourcc(fourcc, "RIFF")) {
        printf("invalid RIFF header");
        return NULL;
    }
    if (read_fourcc_and_size(fd, fourcc, &size) != 0  || !check_fourcc(fourcc, "AVI ")) {
        printf("invalid AVI header");
        return NULL;
    }


    while (read_fourcc_and_size(fd, fourcc, &size) == 0) {
        if (check_fourcc(fourcc, "LIST")) {
            char list_type[4];
            if (fread(list_type, 1, 4, fd) != 4) {
                printf("invalid LIST type\n");
                return NULL;
            }
            if (check_fourcc(list_type, "movi")) {
                break;
            } else {
                fseek(fd, size - 4, SEEK_CUR);
            }
        } else {
            fseek(fd, size, SEEK_CUR);
        }
    }

    while (read_fourcc_and_size(fd, fourcc, &size) == 0) {
        if (read_times++ > 4) {
            //避免读太久,直接退出
            read_times = 0;
            break;
        }

        if (check_fourcc(fourcc, "00dc")) {
            read_times = 0;
            *jpeg_size = size;
            u8 *jpeg_buf = malloc(size);
            if (!jpeg_buf) {
                printf("jpeg_buf malloc fail\n");
                return NULL;
            }
            if (fread(jpeg_buf, size, 1, fd) != size) {
                printf("jpeg fread err\n");
                free(jpeg_buf);
                return NULL;
            }
            return jpeg_buf;
        } else {
            //跳过当前块
            fseek(fd, size, SEEK_CUR);
        }

    }
    printf("not found jpeg frame\n");
    return NULL;
}

static u8 *get_frame_buf(const char *path, u32 *size)
{
    FILE *fd = NULL;
    u8 *file_buf = NULL;
    u32 file_len;

    fd = fopen(path, "rb");
    if (fd == NULL) {
        printf("no file name : %s\n", path);
        goto err;
    }

    if (strcmp(lv_fs_get_ext(path), "jpg") == 0 || strcmp(lv_fs_get_ext(path), "JPG") == 0) {
        file_len = flen(fd);
        file_buf = malloc(file_len);
        if (!file_buf) {
            printf("buf malloc err ...\n");
            goto err;
        }
        if (fread(file_buf, 1, file_len, fd) != file_len) {
            printf("read file lenth err ...\n");
            goto err;
        }
    } else {
        file_buf = get_avi_first_frame(fd, &file_len);
        if (!file_buf) {
            printf("get_avi_first_frame err");
            goto err;
        }
    }

    fclose(fd);

    *size = file_len;
    return file_buf;

err:
    if (fd) {
        fclose(fd);
    }
    if (file_buf) {
        free(file_buf);
    }
    return NULL;
}

static int yuyv2rgb16_dma2d(u8 *yuv_buf, u8 *rgb_buf, int width, int height)
{
    int err;

    u32 in_format = JLDMA2D_FORMAT_YUV422_BT709;
    u32 out_format = JLDMA2D_FORMAT_RGB565;
    u32 dest_stride = width * dma2d_get_format_bpp(out_format) / 8;
    u32 src_stride = width * dma2d_get_format_bpp(in_format) / 8;
    err = jldma2d_format(rgb_buf, \
                         yuv_buf, \
                         dest_stride, \
                         src_stride, \
                         in_format, \
                         out_format, \
                         width, \
                         height, \
                         0, \
                         0);
    return err;
}

static void soft_uyvy_to_rgb16(u8 *uyvy, u16 *rgb, int width, int height)
{
    int x, y;
    u8 u, y1, v, y2;
    int c, d, e;
    int r, g, b;

    for (y = 0; y < height; y++) {
        for (x = 0; x < width; x += 2) {
            u  = uyvy[0];
            y1 = uyvy[1];
            v  = uyvy[2];
            y2 = uyvy[3];

            uyvy += 4;

            c = y1 - 16;
            d = u - 128;
            e = v - 128;

            r = (298 * c + 409 * e + 128) >> 8;
            g = (298 * c - 100 * d - 208 * e + 128) >> 8;
            b = (298 * c + 516 * d + 128) >> 8;

            r = (r < 0) ? 0 : ((r > 255) ? 255 : r);
            g = (g < 0) ? 0 : ((g > 255) ? 255 : g);
            b = (b < 0) ? 0 : ((b > 255) ? 255 : b);

            rgb[0] = ((r & 0xF8) << 8) | ((g & 0xFC) << 3) | (b >> 3);

            c = y2 - 16;
            r = (298 * c + 409 * e + 128) >> 8;
            g = (298 * c - 100 * d - 208 * e + 128) >> 8;
            b = (298 * c + 516 * d + 128) >> 8;

            r = (r < 0) ? 0 : ((r > 255) ? 255 : r);
            g = (g < 0) ? 0 : ((g > 255) ? 255 : g);
            b = (b < 0) ? 0 : ((b > 255) ? 255 : b);

            rgb[1] = ((r & 0xF8) << 8) | ((g & 0xFC) << 3) | (b >> 3);

            rgb += 2;
        }
    }
}

static void on_event2(const char *name, int type, void *arg)
{
    OS_SEM *sem = (OS_SEM *)arg;
    switch (type) {
    case EVENT_FRAME_DONE:
        if (!strncmp(name, "yuv", 3)) {
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

static int jpeg2yuv_pipeline_init(struct video_format *f)
{
    pipe_filter_t *jpeg_dec_filter, *imc_filter, *rep_filter, *yuv_filter, *virtual_filter;
    os_sem_create(&sem, 0);
    pipe_core = pipeline_init(on_event2, &sem);
    if (!pipe_core) {
        printf("pipeline init err\n");
        return -1;
    }


    char *source_name = plugin_factory_find("virtual");
    pipe_core->channel = plugin_source_to_channel(source_name);
    virtual_filter = pipeline_filter_add(pipe_core, source_name);
    jpeg_dec_filter = pipeline_filter_add(pipe_core, plugin_factory_find("jpeg_dec"));
    rep_filter = pipeline_filter_add(pipe_core, "rep1");
    imc_filter = pipeline_filter_add(pipe_core, "imc3");
    yuv_filter = pipeline_filter_add(pipe_core, plugin_factory_find("yuv"));

    pipeline_param_set(pipe_core, NULL, PIPELINE_SET_FORMAT, f);

    int out_format = FORMAT_YUV422_UYVY;
    pipeline_param_set(pipe_core, NULL, PIPELINE_SET_SINK_OUT_FORMAT, (int)&out_format);

    int line_cnt = 16;
    pipeline_param_set(pipe_core, NULL, PIPELINE_SET_BUFFER_LINE, (int)&line_cnt);

    pipeline_filter_link(virtual_filter, jpeg_dec_filter);

    pipeline_filter_link(jpeg_dec_filter, rep_filter);

    pipeline_filter_link(rep_filter, imc_filter);

    pipeline_filter_link(imc_filter, yuv_filter);

    pipeline_prepare(pipe_core);

    pipeline_start(pipe_core);
}

static void jpeg2yuv_pipeline_uninit(void)
{
    if (!pipe_core) {
        return;
    }

    pipeline_stop(pipe_core);

    pipeline_reset(pipe_core);

    pipeline_uninit(pipe_core);

    os_sem_del(&sem, 0);
    pipe_core = NULL;
}


static int jpeg2yuv_with_pipeline(const char *path, u8 *img_buf, int dst_w, int dst_h)
{
    int err = 0;
    u8 *frame_buf = NULL;
    int frame_len;
    u8 *dec_buf = NULL;
    int dec_len;
    u8 *yuv_buf;
    static int last_width, last_height, last_format;

    if (pipeline_state == PIPELINE_EXIT) {
        return 0;
    }

    frame_buf = get_frame_buf(path, &frame_len);
    if (!frame_buf) {
        printf("get decode data fail");
        err = -EFAULT;
        goto exit;
    }

    //缩略图
    dec_buf = find_jpg_thumbnails(frame_buf, frame_len, &dec_len);
    if (!dec_buf) {
        dec_buf = frame_buf;
        dec_len = frame_len;
    }

    struct jpeg_image_info info = {0};
    struct video_format f  = {0};
    int fmt;
    info.input.data.buf = dec_buf;
    info.input.data.len = dec_len;
    err = jpeg_decode_image_info(&info);
    if (err) {
        printf("jpeg_decode_image_info err %s\n", path);
        goto exit;
    }
    switch (info.sample_fmt) {
    case JPG_SAMP_FMT_YUV444:
        fmt = VIDEO_PIX_FMT_YUV444;
        break;
    case JPG_SAMP_FMT_YUV422:
        fmt = VIDEO_PIX_FMT_YUV422;
        break;
    case JPG_SAMP_FMT_YUV420:
        fmt = VIDEO_PIX_FMT_YUV420;
        break;
    default:
        printf("err fmt\n");
        break;
    }
    f.src_width = info.width;
    f.src_height = info.height;
    f.win.width = dst_w;
    f.win.height = dst_h;
    f.type = VIDEO_BUF_TYPE_VIDEO_PLAY;
    f.pixelformat = VIDEO_PIX_FMT_JPEG | fmt;
    f.private_data = "fb5";

    if ((last_height != info.height) || (last_width != info.width)
        || (last_format != fmt) || (pipeline_state == PIPELINE_STOP)) {

        jpeg2yuv_pipeline_uninit();
        jpeg2yuv_pipeline_init(&f);
    }
    pipeline_state = PIPELINE_RUNING;

    last_width = info.width;
    last_height = info.height;
    last_format = fmt;

    //设置jpeg buf
    struct video_cap_buffer buffer ;
    buffer.size = dec_len;
    buffer.buf = dec_buf;
    pipeline_param_set(pipe_core, NULL, VIDIOC_RDBUF, &buffer);

    err = os_sem_pend(&sem, 200);
    if (err) {
        log_e("jpeg2yuv timeout\n");
        goto exit;
    }
    printf("jpeg2yuv ok\n");

    //获取YUV
    pipeline_param_get(pipe_core, NULL, PIPELINE_GET_YUV_BUF, &yuv_buf);
    if (!yuv_buf) {
        printf("get yuv buf err\n");
        err = -EFAULT;
        goto exit;
    }

#if USE_DMA2D_CONVERT
    yuyv2rgb16_dma2d(yuv_buf, img_buf, dst_w, dst_h);
#else
    soft_uyvy_to_rgb16(yuv_buf, img_buf, dst_w, dst_h);
#endif

exit:
    if (err) {
        memset(img_buf, 0x00, dst_w * dst_h * 2);
    }
    if (frame_buf) {
        free(frame_buf);
        frame_buf = NULL;
    }
    return err;
}

#endif

#endif
