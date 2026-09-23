#include "app_config.h"
#ifdef CONFIG_UI_STYLE_LY_ENABLE
#include "custom.h"
uint8_t no_select = 1;
uint8_t lock_all_flag = 1;
#if !LV_USE_GUIBUILDER_SIMULATOR
#include "system/includes.h"
#include "include/action.h"
#include "app_config.h"
#include "ui.h"
#include "fs/fs.h"
#include "video_dec_server.h"
#include "video_dec.h"

#define FILE_DISP_REVERSE_ORDER 1
struct replay_info {
    u8 onkey_mod;           /*按键选中组*/
    s8 onkey_sel;           /*按键选中项*/

    u8 type;                /*当前过滤类型*/
    u8 edit;                /*编辑模式*/
    u8 no_file;             /*没有文件 */

    u8 dec_player;          /*播放器显示状态*/
    u8 is_lock;             /*加锁文件*/
    u8 err_file;            /*损坏文件*/
    u8 file_res;            /*文件分辨率*/
    u8 file_type;           /*文件类型*/
    int dec_player_timer;   /*播放器隐藏计时器*/

    u8 file_dialog;         /*预览对话框内容*/
    u8 file_msg;            /*预览弹窗提示内容*/
    u8 file_timerout_msg;   /*自动隐藏的预览弹窗内容*/
    int file_msg_timer;     /*预览弹窗隐藏计时器*/

    int dec_msg_timer;      /*播放弹窗隐藏计时器*/

    u8 dec_show_status;     /*界面状态 0:文件列表 1:解码界面  */
    u8 page_exit;           /* 退出页面方式 */

    u8 battery_val;         /*电池电量*/
    u8 battery_charging;    /*电池充电状态*/

    int file_num;          /*当前页文件数*/
    int page_cur;          /*当前页码值*/
    int page_tol;          /*总页码值*/
    int file_index;        /*当前编辑的文件序号*/
    u8 refresh_flag;       /*是否刷新当前九宫格页面*/

    char cur_path[128];    /*当前目录路径*/

    u8 edit_sel[99];       /*编辑选中*/
    FILE *file_fd;
    FILE *edit_fd;
};

extern u8 deleting_flag;
static struct replay_info handler;
#define __this  (&handler)
#define sizeof_this     (sizeof(struct replay_info))
void post_msg2_dec(int mode)
{
#ifdef USE_LVGL_V8_UI_DEMO
    lvgl_module_msg_send_string(GUI_MODEL_MSG_ID_TOTAL_TIME, NULL, 0);
    lvgl_module_msg_send_value(GUI_MODEL_MSG_ID_CUR_TIME_PROCESS, 0, 0);
    lvgl_module_msg_send_string(GUI_MODEL_MSG_ID_CUR_TIME,  "00:00", 0);
#endif
}

void refresh_video_file_screen(void)
{
    video_file_screen_unload();
    video_file_screen_load();
}

void dec_list_cur_page(int page_cur)
{
    __this->page_cur = page_cur;
}

void dec_list_tol_page(int page_tol)
{
    __this->page_tol = page_tol;
}

void dec_list_file_num(int file_num)
{
    __this->file_num = file_num;
}

int dec_tol_time_handler(const char *type, u32 arg)
{
    return 0;
}

int dec_play_time_handler(const char *type, u32 arg)
{
    int sec;
    sec = arg;
    u32 minutes = sec / 60;
    u32 seconds = sec % 60;
    u32 tol_time = video_dec_get_file_toltime();
    float cur_time_process = ((float)sec / (float)tol_time);
    int cur_time_process_int = (int)(cur_time_process * 100);
    char *cur_time_ptr =  lvgl_module_msg_get_ptr(GUI_MODEL_MSG_ID_CUR_TIME, 8);
    sprintf(cur_time_ptr, "%02u:%02u", minutes, seconds);
    printf("cur_time %s\n", cur_time_ptr);
    lvgl_module_msg_send_ptr(cur_time_ptr, 0);
    lvgl_module_msg_send_value(GUI_MODEL_MSG_ID_CUR_TIME_PROCESS, cur_time_process_int, 0);
    return 0;
}

int dec_file_name_handler(const char *type, u32 arg)
{
    const char *fname = (const char *)arg;
    const char *str_p;
    puts("rep_file_name_handler\n");
    if (strstr(type, "ascii")) {
        str_p = (const char *)(arg + strlen((char *)arg) - 3);
        if (!strcmp(str_p, "JPG") || !strcmp(str_p, "jpg")) {
            __this->file_type = 0;
        } else {
            __this->file_type = 1;
        }
        __this->dec_player = 1;
        __this->no_file = 0;
        __this->err_file = 0;
        lvgl_module_msg_send_string(GUI_MODEL_MSG_ID_FILE_NAME, (const char *)arg, 0);
    } else if (strstr(type, "utf16")) {
    }
    return 0;
}

int dec_file_err_handler(const char *type, u32 arg)
{
    extern void sys_prompt_show_ctl(int32_t show_time, void *tips);
    lvgl_rpc_post_func(sys_prompt_show_ctl, 2, 3000, (void *)_("fileerr"));
    __this->err_file = 1;
    __this->file_fd = NULL;
    return 0;
}

void video_dir_cb_event_handler(lv_event_t *e)  //录像文件控件右上角复选框回调
{
    lv_event_code_t code = lv_event_get_code(e);
    lv_ui *ui = (lv_ui *) lv_event_get_user_data(e);
    lv_obj_t *src = lv_event_get_target(e);  //拿到复选框控件
    switch (code) {
    case LV_EVENT_VALUE_CHANGED: {
        //custom code video_dir_view_dir
        {

            lv_obj_t *child_contain = lv_obj_get_parent(src);  //拿到对应录像文件的控件
            lv_ui_video_file *ui_scr = ui_get_scr_ptr(&guider_ui, GUI_SCREEN_VIDEO_FILE);
            if (!ui_scr) {
                return;
            }
            lv_obj_t *contain = lv_obj_get_child(ui_scr->video_file, 3);
            int32_t child_index = lv_obj_get_index(child_contain);
            printf("Child is the %dth in the parent container\n", child_index);
            if (__this->edit_sel[child_index] == 0) {
                __this->edit_sel[child_index] = 1;
            } else {
                __this->edit_sel[child_index] = 0;
            }
            no_select = 0;
        }
    }
    break;
    default:
        break;
    }
}

void enter_video_dir_callback(void *priv, int err)
{
    printf("--->%s()----->%d\n", __func__, __LINE__);
    key_event_enable();
}

int gui_scr_action_video_dir_cb(int action)
{
    printf("--->%s()----->%d, action: %d\n", __func__, __LINE__, action);
    switch (action) {
    case GUI_SCREEN_ACTION_LOAD:
        lv_ui_video_dir *ui_scr = ui_get_scr_ptr(&guider_ui, GUI_SCREEN_VIDEO_DIR);
        if (!ui_scr) {
            return -1;
        }
        printf("--->%s()----->%d\n", __func__, __LINE__);
#if LV_DISP_UI_FB_NUM
        lv_obj_set_style_bg_opa(ui_scr->video_dir, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
#else
        lv_obj_set_style_bg_opa(ui_scr->video_dir, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
#endif
        key_event_disable();
        app_mode_change_replace(APP_MODE_DEC);
        app_send_message(APP_MSG_DEC_MAIN, 0);
        key_event_enable();
        break;
    }
}

int gui_scr_action_video_file_cb(int action)
{
    switch (action) {
    case GUI_SCREEN_ACTION_LOAD:
        lv_ui_video_file *ui_scr = ui_get_scr_ptr(&guider_ui, GUI_SCREEN_VIDEO_FILE);
        if (!ui_scr) {
            return -1;
        }
#if LV_DISP_UI_FB_NUM
        lv_obj_set_style_bg_opa(ui_scr->video_file, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
#else
        lv_obj_set_style_bg_opa(ui_scr->video_file, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
#endif
        if ((__this->file_fd != NULL) && (__this->err_file == 0) && (__this->type == 1)) {
            __this->file_fd = NULL;
        }
        /* app_msg_handler(NULL, APP_MSG_STOP); */
        app_mode_change_replace(APP_MODE_DEC);
        app_send_message(APP_MSG_DEC_MAIN, 0);
        break;
    }
}



int gui_scr_action_video_play_cb(int action)
{

    switch (action) {
    case GUI_SCREEN_ACTION_LOAD:
        lv_ui_video_play *ui_scr = ui_get_scr_ptr(&guider_ui, GUI_SCREEN_VIDEO_PLAY);
        if (!ui_scr) {
            return -1;
        }
#if LV_DISP_UI_FB_NUM
        lv_obj_set_style_bg_opa(ui_scr->video_play, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
#else
        lv_obj_set_style_bg_opa(ui_scr->video_play, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
#endif
        if (__this->type == 0) {
            //jpg时隐藏进度条
            lv_obj_add_flag(ui_scr->video_play_view_1, LV_OBJ_FLAG_HIDDEN);
        }
        break;
    }
}

void get_focused_file_idx(lv_obj_t *focused_obj)
{
    __this->file_index = lv_obj_get_index(focused_obj);
    printf("enter play file idx: %d\n", __this->file_index);
}

void focus_video_file(void)
{
    lv_ui_video_file *ui_scr = ui_get_scr_ptr(&guider_ui, GUI_SCREEN_VIDEO_FILE);
    if (!ui_scr) {
        return;
    }
    printf("---->%s(), file idx: %d\n", __func__, __this->file_index);
    //聚焦到指定文件
    lv_obj_t *focuse_file_obj = lv_obj_get_child(ui_scr->video_file_view_3, __this->file_index);
    if (focuse_file_obj) {
        printf("----%d---%s\n", __LINE__, __func__);
        lv_group_focus_obj(focuse_file_obj);
    }

    //滚动到聚焦文件位置
    extern void key_scroll_to_view(void);
    key_scroll_to_view();
}

void set_file_idx(int idx)
{
    __this->file_index = idx;
}

int gui_get_video_frame(void)
{
    app_send_message(APP_MSG_DEC_GET_FRAME, 0);
    return 0;
}

int gui_set_video_volume(void)
{
    app_send_message(APP_MSG_DEC_SET_AUDIO_VOLUME, 0);
    return 0;
}

int browser_open_file(void *p, char *path, char *name)
{
    struct intent *it = NULL;
    it = malloc(sizeof(struct intent));
    if (strcmp(lv_fs_get_ext(name), "jpg") == 0 || strcmp(lv_fs_get_ext(name), "JPG") == 0) {
        __this->type = 0;   //文件为jpg
    } else {
        __this->type = 1;   //文件为avi
    }
    __this->err_file = 0;
    __this->file_fd = (FILE *)p;
    if (__this->file_fd != NULL) {
        init_intent(it);
        it->data = (const char *)__this->file_fd;
        it->exdata = (u32)path;
        app_send_message(APP_MSG_DEC_OPEN_FILE, 1, it);
    }

    ui_video_dir(path);
    return 0;
}

void dec_video_prev_next(u32 mode)
{
#if FILE_DISP_REVERSE_ORDER
    if (mode == FSEL_NEXT_FILE) {
        mode = FSEL_PREV_FILE;
    } else {
        mode = FSEL_NEXT_FILE;
    }
#endif
    struct intent *it = NULL;
    it = malloc(sizeof(struct intent));
    printf("it:%p", it);
    init_intent(it);
    it->exdata = mode;
    app_send_message(APP_MSG_DEC_PREV_NEXT_CONTROL, 1, it);
}

void cfun_dec_ok(void)
{
    app_send_message(APP_MSG_DEC_CONTROL, 0);
}

void cfun_dec_return(void)
{
    app_send_message(APP_MSG_DEC_CUR_PAGE, 0);
}

void del_file_callback(void *priv, int err)
{
    printf("del_file_callback: err=%d\n", err);
    if (err == (int) - EPERM) {
        puts("del file -EPERM, locked file.\n");
    } else {
        __this->edit_fd = NULL;
    }

}
void lock_file_callback(void *priv, int err)
{
    printf("lock_file_callback: err=%d\n", err);
    if (err == (int) - EPERM) {
        puts("lock file -EPERM.\n");
    } else {
        __this->edit_fd = NULL;
    }
}

static void cfun_dec_lock_all(u8 lock_flag)
{
    struct intent *it = NULL;
    it = malloc(sizeof(struct intent));
    init_intent(it);
    if (lock_flag) {
        it->data = "lock:all";
        lock_all_flag = 0;
    } else {
        it->data = "unlock:all";
        lock_all_flag = 1;
    }
    it->exdata = (u32)__this->cur_path;
    app_send_message(APP_MSG_DEC_SET_CONFIG, 1, it);
}

static void cfun_dec_lock()
{
    struct intent *it = NULL;
    it = malloc(sizeof(struct intent));
    if (__this->is_lock) {
        init_intent(it);
        it->data = "unlock:cur";
        it->exdata = (const char *)__this->edit_fd;
        __this->is_lock = 0;
        app_send_message(APP_MSG_DEC_SET_CONFIG, 1, it);
        __this->edit_fd = NULL;
    } else {
        init_intent(it);
        it->data = "lock:cur";
        it->exdata = (const char *)__this->edit_fd;
        app_send_message(APP_MSG_DEC_SET_CONFIG, 1, it);
        __this->is_lock = 1;
        __this->edit_fd = NULL;
    }
}

static void cfun_dec_delete(void)
{
    printf(">>>lock: %d, edit_fd: %d\n", __this->is_lock, __this->edit_fd);
    if (__this->is_lock) {
        //是加锁文件，弹窗警告不能删除
        sys_prompt_show_ctl(3000, (void *)_("file_is_lock"));
        return;
    }
    deleting_flag = 1;
    __this->refresh_flag = 1;
    struct intent *it = NULL;
    it = malloc(sizeof(struct intent));
    init_intent(it);
    it->data = "del:cur";
    it->exdata = (const char *)__this->edit_fd;
    app_send_message(APP_MSG_DEC_SET_CONFIG, 1, it);
    __this->edit_fd = NULL;
}

static void cfun_dec_delete_all(void)
{
    struct intent *it;
    it = malloc(sizeof(struct intent));
    init_intent(it);
    deleting_flag = 1;
    __this->refresh_flag = 1;
    it->data = "del:all";
    it->exdata = (u32)__this->cur_path;
    app_send_message(APP_MSG_DEC_SET_CONFIG, 1, it);
}

void edit_lock_file(lv_obj_t *dest, int dir)  //对所有录像文件的复选框进行显示或者隐藏
{
    lv_obj_t *src = dest;
    uint32_t child_cnt = 0;
    uint32_t start_index = 0;
    no_select = 1; //清除上一次的标记

    /* 获取文件数量 */
    if (dir) {
        src = dest;
        child_cnt = lv_obj_get_child_cnt(src);
        start_index = 3;
    } else {
        src = lv_obj_get_child(dest, 3);
        child_cnt = lv_obj_get_child_cnt(src);
    }
    printf("child_cnt %d\n", child_cnt);
    for (uint32_t i = start_index; i < child_cnt; i++) {
        lv_obj_t *child = lv_obj_get_child(src, i); // 获取第i个子控件，即录像文件对应的控件
        if (child) {
            lv_obj_t *edit_obj = lv_obj_get_child(child, 0);  //录像文件控件右上角复选框
            if (__this->edit_sel[i] != 0) {
                __this->edit_sel[i] = 0;  //清除上一次的标记
            }
            lv_obj_clear_state(edit_obj, LV_STATE_CHECKED);
            bool is_hidden = lv_obj_has_flag(edit_obj, LV_OBJ_FLAG_HIDDEN);
            if (is_hidden) { //复选框控件是隐藏的
                lv_obj_clear_flag(edit_obj, LV_OBJ_FLAG_HIDDEN);
                lv_obj_clear_flag(child, LV_OBJ_FLAG_CLICKABLE);
            } else { // 控件不是隐藏的

                lv_obj_add_flag(edit_obj, LV_OBJ_FLAG_HIDDEN);
                lv_obj_add_flag(child, LV_OBJ_FLAG_CLICKABLE);
            }
        } else {
        }
    }
}

void video_dec_edit_files(u8 mode)
{

    char file_name[50];
    struct vfscan *fs = NULL;
    __this->refresh_flag = 0; //每次进来要清空下重刷屏幕的标志位
    lv_ui_video_file *ui_scr = ui_get_scr_ptr(&guider_ui, GUI_SCREEN_VIDEO_FILE);
    if (!ui_scr) {
        return;
    }
    const char *text_dir = lv_label_get_text(ui_scr->video_file_lbl_path); //路径
    fs = fscan(text_dir, "-tMOVJPGAVI -sn", 3);
    strncpy(&__this->cur_path, text_dir, sizeof(__this->cur_path) - 1);
    __this->cur_path[sizeof(__this->cur_path) - 1] = '\0';
    uint32_t child_cnt = lv_obj_get_child_cnt(ui_scr->video_file_view_3);

    for (int i = 0; i < child_cnt; i++) {
        if (__this->edit_sel[i]) {  //文件选中，edit_sel标记选中的文件序号
            __this->file_index = i;
            __this->edit_sel[i] = 0;
            lv_obj_t *child_contain = lv_obj_get_child(ui_scr->video_file_view_3, i);  //拿到录像文件控件
            lv_obj_t *checkbox = lv_obj_get_child(child_contain, 0);  //拿到复选框控件
            lv_obj_clear_state(checkbox, LV_STATE_CHECKED);
            FILE *fp = fselect(fs, FSEL_BY_NUMBER, __this->file_num - i);
            fget_name(fp, file_name, sizeof(file_name));
            char *file_path;
            asprintf(&file_path, "%s%s", text_dir, file_name);
            printf("edit cur file: %s\n", file_path);
            __this->edit_fd = NULL;
            __this->edit_fd = fp;  //edit_fd会传到video_dec下对文件进行加锁或者删除
            int attr;
            fget_attr(__this->edit_fd, &attr);
            if (attr & F_ATTR_RO) {
                puts("locked");
                __this->is_lock = 1;
            } else if (!(attr & F_ATTR_RO)) {
                __this->is_lock = 0;
                puts("unlocked");
            }
            switch (mode) {
            case 0:  //加锁
                cfun_dec_lock();
                lv_obj_t *child_contain = lv_obj_get_child(ui_scr->video_file_view_3, __this->file_index);  //录像文件控件
                lv_obj_t *lock_flag = lv_obj_get_child(child_contain, 4);
                if (lv_obj_is_valid(lock_flag)) {
                    if (lv_obj_has_flag(lock_flag, LV_OBJ_FLAG_HIDDEN)) {
                        lv_obj_clear_flag(lock_flag, LV_OBJ_FLAG_HIDDEN);
                    } else {
                        lv_obj_add_flag(lock_flag, LV_OBJ_FLAG_HIDDEN);
                    }
                }
                break;
            default:  //删除
                cfun_dec_delete();
                break;
            }
        }
    }
    if (no_select != 0) {  //文件没选中，即对全部文件进行操作
        //没选中任何一个文件，全部加锁/删除
        switch (mode) {
        case 0:
            u8 flag = lock_all_flag;
            cfun_dec_lock_all(lock_all_flag);
            for (int i = 0; i < child_cnt; i++) {
                lv_obj_t *child_contain = lv_obj_get_child(ui_scr->video_file_view_3, i);
                lv_obj_t *lock_flag = lv_obj_get_child(child_contain, 4);
                if (lv_obj_is_valid(lock_flag)) {
                    if (flag) {
                        if (lv_obj_has_flag(lock_flag, LV_OBJ_FLAG_HIDDEN)) {
                            lv_obj_clear_flag(lock_flag, LV_OBJ_FLAG_HIDDEN);
                        }
                    } else {
                        if (!lv_obj_has_flag(lock_flag, LV_OBJ_FLAG_HIDDEN)) {
                            lv_obj_add_flag(lock_flag, LV_OBJ_FLAG_HIDDEN);
                        }
                    }
                }
            }
            break;
        default:
            __this->is_lock = 0;
            cfun_dec_delete_all();
            break;
        }
    }
    no_select = 1; //标识已消耗掉选中的选项
    fscan_release(fs);
    if (__this->refresh_flag) {
        //有删除文件时，该标志位为1，需重新刷新屏幕
        refresh_video_file_screen();
    }
}

int get_focused_file(void)
{
    int attr = 0;
    uint32_t idx = 0;
    lv_obj_t *focused_video_file_obj = NULL;
    struct vfscan *fs = NULL;
    FILE *fp = NULL;
    __this->edit_fd = NULL;
    __this->is_lock = 0;
    char file_name[64];

    focused_video_file_obj = lv_group_get_focused(lv_group_get_default());
    if (focused_video_file_obj) {
        idx = lv_obj_get_index(focused_video_file_obj);
        __this->file_index = idx;
        printf("file_idx: %d\n", idx);
    } else {
        printf("------>%s(), focused_video_file_obj is NULL\n", __func__);
        return -1;
    }
    lv_ui_video_file *ui_scr = ui_get_scr_ptr(&guider_ui, GUI_SCREEN_VIDEO_FILE);
    if (!ui_scr) {
        return -1;
    }
    const char *text_dir = lv_label_get_text(ui_scr->video_file_lbl_path); //路径
    fs = fscan(text_dir, "-tMOVJPGAVI -sn", 3);
    strncpy(&__this->cur_path, text_dir, sizeof(__this->cur_path) - 1);
    __this->cur_path[sizeof(__this->cur_path) - 1] = '\0';
    printf("focused file path: %s, file num: %d\n",  __this->cur_path, __this->file_num);

    fp = fselect(fs, FSEL_BY_NUMBER, __this->file_num - idx);
    printf(">>>>fp: %d\n", fp);
#if 1
    char *file_path;
    fget_name(fp, file_name, sizeof(file_name));
    asprintf(&file_path, "%s%s", text_dir, file_name);
    printf("edit cur file: %s\n", file_path);
#endif
    fget_attr(fp, &attr);
    if (attr & F_ATTR_RO) {
        puts("locked");
        __this->is_lock = 1;
    } else if (!(attr & F_ATTR_RO)) {
        __this->is_lock = 0;
        puts("unlocked");
    }
    __this->edit_fd = fp;
    fscan_release(fs);
    // fclose(fp);
    fs = NULL;
    // fp = NULL;

    return __this->file_index;
}

//删除文件，0：删除当前选中的文件，1：删除全部文件
void delete_file(uint8_t data)
{
    if (!data) {
        cfun_dec_delete();  //删除当前选中的文件
    } else {
        cfun_dec_delete_all();  //删除全部文件
    }

    printf("------>%s()----->%d\n", __func__, __LINE__);
    if (__this->refresh_flag) {
        printf("------>%s()----->%d\n", __func__, __LINE__);
        //有删除文件时，该标志位为1，需重新刷新屏幕
        refresh_video_file_screen();
        __this->refresh_flag = 0; //每次进来要清空下重刷屏幕的标志位
    }
}

/*
 * 文件加锁与解锁
 * file_num：0为对当前单个文件操作，1为全部文件
 * lock：0为解锁，1为加锁
 *
 */
void lock_flie(uint8_t file_num, uint8_t lock)
{
    lv_obj_t *video_file_obj = NULL;
    lv_obj_t *lock_icon_obj = NULL;
    uint32_t video_file_num = 0;
    struct intent *it = NULL;
    it = malloc(sizeof(struct intent));
    init_intent(it);
    lv_ui_video_file *ui_scr = ui_get_scr_ptr(&guider_ui, GUI_SCREEN_VIDEO_FILE);
    if (!ui_scr) {
        return;
    }
    printf(">>>file_num: %d, lock: %d\n", file_num, lock);

    if (file_num) {
        video_file_num = lv_obj_get_child_cnt(ui_scr->video_file_view_3);
        if (lock) {
            it->data = "lock:all";
        } else {
            it->data = "unlock:all";
        }
        it->exdata = (u32)__this->cur_path;
        app_send_message(APP_MSG_DEC_SET_CONFIG, 1, it);
    } else {
        video_file_num = 1;
        if (lock) {
            it->data = "lock:cur";
        } else {
            it->data = "unlock:cur";
        }
        it->exdata = (const char *)__this->edit_fd;
        app_send_message(APP_MSG_DEC_SET_CONFIG, 1, it);
        __this->edit_fd = NULL;
    }

    for (int i = 0; i < video_file_num; i++) {
        printf("file cnt: %d\n", i);
        if (file_num) {
            video_file_obj = lv_obj_get_child(ui_scr->video_file_view_3, i);
        } else {
            video_file_obj = lv_obj_get_child(ui_scr->video_file_view_3, __this->file_index);
        }

        lock_icon_obj = lv_obj_get_child(video_file_obj, 4);
        if (lv_obj_is_valid(lock_icon_obj)) {
            if (lock) {
                if (lv_obj_has_flag(lock_icon_obj, LV_OBJ_FLAG_HIDDEN)) {
                    lv_obj_clear_flag(lock_icon_obj, LV_OBJ_FLAG_HIDDEN);
                }
            } else {
                if (!lv_obj_has_flag(lock_icon_obj, LV_OBJ_FLAG_HIDDEN)) {
                    lv_obj_add_flag(lock_icon_obj, LV_OBJ_FLAG_HIDDEN);
                }
            }
        }
        video_file_obj = NULL;
        lock_icon_obj = NULL;
    }


}

void speed_change(int index)
{
    struct intent *it = NULL;
    it = malloc(sizeof(struct intent));
    init_intent(it);
    float speed;

    switch (index) {
    case 0:
        //2x
        speed = 2.0;
        break;
    case 1:
        //1x
        speed = 1.0;
        break;
    case 2:
        //0.5x
        speed = 0.5;
        break;
    default:
        speed = 1.0;
        break;
    }

    it->exdata = &speed;
    app_send_message(APP_MSG_DEC_SET_PLAY_SPEED, 1, it);
}

/* 各个控件模型的消息处理回调 */
int gui_model_msg_video_pause_cb(gui_msg_action_t access, gui_msg_data_t *data, gui_msg_data_type_t type)
{
    static lv_state_t video_pause_var = LV_STATE_DEFAULT;
    if (access == GUI_MSG_ACCESS_SET) {
        video_pause_var = data->value_int;
    }
    data->value_int = video_pause_var;
    if (data->value_int == LV_STATE_DEFAULT) {
    } else if (data->value_int == LV_STATE_CHECKED) {
    }
}

int gui_model_msg_total_time_cb(gui_msg_action_t access, gui_msg_data_t *data,  gui_msg_data_type_t type)
{
#if 1
    static char total_time_init_var[] = "/02:40";
    static bool total_time_is_init = false;
    static char *total_time_var = NULL;
    if (total_time_is_init == false) {
        total_time_var = lv_mem_alloc(strlen(total_time_init_var) + 1);
        strcpy(total_time_var, total_time_init_var);
        total_time_is_init = true;
    }
    /*if (access == GUI_MSG_ACCESS_GET) {*/
    // 调用 video_dec_get_file_toltime 获取总时间
    u32 total_time_seconds = video_dec_get_file_toltime();
    // 计算分钟和秒数
    u32 minutes = total_time_seconds / 60;
    u32 seconds = total_time_seconds % 60;
    // 确保分钟和秒数都是两位数字
    char time_str[8];
    sprintf(time_str, "%02u:%02u", minutes, seconds);
    // 更新 total_time_var
    lv_mem_free(total_time_var);
    total_time_var = lv_mem_alloc(strlen("/") + strlen(time_str) + 1);
    strcpy(total_time_var, "/");
    strcat(total_time_var, time_str);
    data->value_string = total_time_var;
#else
#endif
}

int gui_model_msg_file_name_cb(gui_msg_action_t access, gui_msg_data_t *data, gui_msg_data_type_t type)
{
#if 1
    static char file_name_init_var[] = "正在播放 xxx.avi";
    static bool file_name_is_init = false;
    static char *file_name_var = NULL;
    if (file_name_is_init == false) {
        file_name_var = lv_mem_alloc(strlen(file_name_init_var) + 1);
        strcpy(file_name_var, file_name_init_var);
        file_name_is_init = true;
    }
    char *current_file_name = video_dec_get_file_name();
    size_t new_length = strlen("正在播放 ") + strlen(current_file_name) + 1;
    lv_mem_free(file_name_var);
    file_name_var = lv_mem_alloc(new_length);
    // 拼接 "正在播放" 和当前文件名
    strcpy(file_name_var, "正在播放 ");
    strcat(file_name_var, current_file_name);

    data->value_string = file_name_var;
#else
#endif
}

/* 注册控件模型 */
REGISTER_UI_MODULE_EVENT_HANDLER(GUI_MODEL_MSG_ID_TOTAL_TIME)
.onchange = gui_model_msg_total_time_cb,
};
REGISTER_UI_MODULE_EVENT_HANDLER(GUI_MODEL_MSG_ID_VIDEO_PAUSE)
.onchange = gui_model_msg_video_pause_cb,
};
REGISTER_UI_MODULE_EVENT_HANDLER(GUI_MODEL_MSG_ID_FILE_NAME)
.onchange = gui_model_msg_file_name_cb,
};

//注册页面
REGISTER_UI_SCREEN_ACTION_HANDLER(GUI_SCREEN_VIDEO_DIR)
.onchange = gui_scr_action_video_dir_cb,
};
REGISTER_UI_SCREEN_ACTION_HANDLER(GUI_SCREEN_VIDEO_FILE)
.onchange = gui_scr_action_video_file_cb,
};
REGISTER_UI_SCREEN_ACTION_HANDLER(GUI_SCREEN_VIDEO_PLAY)
.onchange = gui_scr_action_video_play_cb,
};
#endif

#endif
