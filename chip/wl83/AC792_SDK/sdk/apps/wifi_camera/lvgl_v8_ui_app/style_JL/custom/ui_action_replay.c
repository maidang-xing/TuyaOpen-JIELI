#include "app_config.h"
#ifdef CONFIG_UI_STYLE_JL_ENABLE
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
void post_msg2_dec(const char *type, u32 arg)
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
    lv_ui_video_file *ui_scr = ui_get_scr_ptr(&guider_ui, GUI_SCREEN_VIDEO_FILE);
    if (!ui_scr) {
        return;
    }
    lv_obj_clear_flag(ui_scr->video_file_imgbtn_5, LV_OBJ_FLAG_HIDDEN);
    lv_obj_add_flag(ui_scr->video_file_imgbtn_2, LV_OBJ_FLAG_HIDDEN);
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
        lvgl_module_msg_send_string(GUI_MODEL_VIDEO_PLAY_MSG_ID_DISP_PROGRESS_BAR, __this->file_type, 0);
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

void video_dir_cb_event_handler(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    lv_ui *ui = (lv_ui *) lv_event_get_user_data(e);
    lv_obj_t *src = lv_event_get_target(e);
    switch (code) {
    case LV_EVENT_VALUE_CHANGED: {
        //custom code video_dir_view_dir
        {
            lv_obj_t *child_contain = lv_obj_get_parent(src);
            lv_ui_video_file *ui_scr = ui_get_scr_ptr(&guider_ui, GUI_SCREEN_VIDEO_FILE);
            if (!ui_scr) {
                return;
            }
            lv_obj_t *contain = lv_obj_get_child(ui_scr->video_file, 3);
            int32_t child_index = lv_obj_get_index(child_contain);
            printf("Child is the %dth in the parent container\n", child_index);
            if (__this->edit_sel[child_index] == 0) {
                ;
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

int gui_scr_action_video_dir_cb(int action)
{
    switch (action) {
    case GUI_SCREEN_ACTION_LOAD:
        app_mode_change_replace(APP_MODE_DEC);
        app_send_message(APP_MSG_DEC_MAIN, 0);
        break;
    }
}

int gui_scr_action_video_file_cb(int action)
{
    switch (action) {
    case GUI_SCREEN_ACTION_LOAD:
        if ((__this->file_fd != NULL) && (__this->err_file == 0) && (__this->type == 1)) {
            __this->file_fd = NULL;
        }
        app_msg_handler(NULL, APP_MSG_STOP);
        app_mode_change_replace(APP_MODE_DEC);
        app_send_message(APP_MSG_DEC_MAIN, 0);
        break;
    }
}



int gui_scr_action_video_play_cb(int action)
{
    /*struct intent it;*/
    /*init_intent(&it);*/
    lv_ui_video_play *ui_scr = ui_get_scr_ptr(&guider_ui, GUI_SCREEN_VIDEO_PLAY);
    if (!ui_scr) {
        return -1;
    }
#if LV_DISP_UI_FB_NUM
    lv_obj_set_style_bg_opa(ui_scr->video_play, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
#else
    lv_obj_set_style_bg_opa(ui_scr->video_play, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
#endif

    switch (action) {
    case GUI_SCREEN_ACTION_LOAD:
        break;
    }
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

static void cfun_dec_delete()
{
    if (__this->is_lock) {
        //是加锁文件，弹窗警告不能删除
        sys_prompt_show_ctl(3000, (void *)_("file_is_lock"));
        return;
    }
    deleting_flag = 1;
    __this->refresh_flag = 1;
    struct intent *it = NULL;
    it = malloc(sizeof(struct intent));
    it->data = "del:cur";
    it->exdata = (const char *)__this->edit_fd;
    app_send_message(APP_MSG_DEC_SET_CONFIG, 1, it);
    __this->edit_fd = NULL;
}

static void cfun_dec_delete_all()
{
    struct intent *it;
    it = malloc(sizeof(struct intent));
    deleting_flag = 1;
    __this->refresh_flag = 1;
    it->data = "del:all";
    it->exdata = (u32)__this->cur_path;
    app_send_message(APP_MSG_DEC_SET_CONFIG, 1, it);
}

/* extern int get_total_file_num(); */
extern int get_cur_num();
extern int get_edit_flag();

void edit_lock_file(lv_obj_t *dest, int dir)
{
    uint32_t  num;
    lv_obj_t *src = dest;
    uint32_t child_cnt = 0;
    uint32_t start_index = 0;
    no_select = 1; //清除上一次的标记
    printf("%s, %d", __func__, __LINE__);
    if (dir) {
        src = dest;
        child_cnt = lv_obj_get_child_cnt(src);
        start_index = 3;
        num = child_cnt - start_index;
    } else {
        src = lv_obj_get_child(dest, 3);
        child_cnt = lv_obj_get_child_cnt(src);
        num = get_cur_num();
    }
    printf("child_cnt %d\n", child_cnt);
    printf("cur num %d\n", get_cur_num());
    num = get_cur_num();

    for (uint32_t i = start_index; i < child_cnt; i++) {
        lv_obj_t *child1 = lv_obj_get_child(src, i); // 获取第i个子控件
        if (child1) {
            lv_obj_t *edit_obj1 = lv_obj_get_child(child1, 0);
            lv_obj_clear_state(edit_obj1, LV_STATE_CHECKED);
            lv_obj_add_flag(edit_obj1, LV_OBJ_FLAG_HIDDEN);
            /* lv_obj_add_flag(child1, LV_OBJ_FLAG_CLICKABLE); */
        }
    }
    lv_ui_video_file *ui_scr = ui_get_scr_ptr(&guider_ui, GUI_SCREEN_VIDEO_FILE);
    if (!ui_scr) {
        return;
    }
    for (uint32_t i = start_index; i < num; i++) {
        lv_obj_t *child = lv_obj_get_child(src, i); // 获取第i个子控件}
        if (child) {
            lv_obj_t *edit_obj = lv_obj_get_child(child, 0);

            if (lv_obj_has_flag(ui_scr->video_file_imgbtn_2, LV_OBJ_FLAG_HIDDEN)) {
                if (__this->edit_sel[i] != 0) {
                    __this->edit_sel[i] = 0;  //清除上一次的标记
                }
            }

            lv_obj_clear_state(edit_obj, LV_STATE_CHECKED);
            bool is_hidden = lv_obj_has_flag(edit_obj, LV_OBJ_FLAG_HIDDEN);
            /* printf("is hidden:%d, %d", is_hidden, get_edit_flag()); */
            if (is_hidden) {
                /* 控件是隐藏的 */
                if (!lv_obj_has_flag(ui_scr->video_file_imgbtn_2, LV_OBJ_FLAG_HIDDEN)) {
                    lv_obj_clear_flag(edit_obj, LV_OBJ_FLAG_HIDDEN);
                    lv_obj_clear_flag(child, LV_OBJ_FLAG_CLICKABLE);
                    if (__this->edit_sel[i]) {
                        lv_obj_add_state(edit_obj, LV_STATE_CHECKED);
                        no_select = 0; //清除上一次的标记
                        /* __this->edit_sel[i] = 0;  //清除上一次的标记 */
                    }
                }
            } else {
                /* 控件不是隐藏的 */
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
        if (__this->edit_sel[i]) {
            __this->file_index = i;
            __this->edit_sel[i] = 0;
            lv_obj_t *child_contain = lv_obj_get_child(ui_scr->video_file_view_3, i);
            lv_obj_t *checkbox = lv_obj_get_child(child_contain, 0);
            lv_obj_clear_state(checkbox, LV_STATE_CHECKED);
            FILE *fp = fselect(fs, FSEL_BY_NUMBER, __this->file_num - i);
            fget_name(fp, file_name, sizeof(file_name));
            char *file_path;
            asprintf(&file_path, "%s%s", text_dir, file_name);
            printf("edit cur file: %s\n", file_path);
            __this->edit_fd = NULL;
            __this->edit_fd = fp;
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
            case 0:
                cfun_dec_lock();
                lv_obj_t *child_contain = lv_obj_get_child(ui_scr->video_file_view_3, __this->file_index);
                lv_obj_t *lock_flag = lv_obj_get_child(child_contain, 4);
                if (lv_obj_is_valid(lock_flag)) {
                    if (lv_obj_has_flag(lock_flag, LV_OBJ_FLAG_HIDDEN)) {
                        lv_obj_clear_flag(lock_flag, LV_OBJ_FLAG_HIDDEN);
                    } else {
                        lv_obj_add_flag(lock_flag, LV_OBJ_FLAG_HIDDEN);
                    }
                }
                break;
            default:
                cfun_dec_delete();
                break;
            }
        }
    }
    if (no_select != 0) {
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

int gui_model_video_play_msg_disp_progress_bar_cb(gui_msg_action_t access, gui_msg_data_t *data, gui_msg_data_type_t type)
{
    if (access == GUI_MSG_ACCESS_GET) {
        data->value_int = __this->type;
    }
    if (access == GUI_MSG_ACCESS_SET) {
        if (data->value_int) {
            lvgl_module_msg_send_value(GUI_MODEL_VIDEO_PLAY_MSG_ID_ADD_CLICK_FLAG, LV_OBJ_FLAG_CLICKABLE, 0);
        } else {
            lvgl_module_msg_send_value(GUI_MODEL_VIDEO_PLAY_MSG_ID_CLEAR_CLICK_FLAG, LV_OBJ_FLAG_CLICKABLE, 0);
        }
    }
    return 0;
}

int gui_model_video_play_msg_add_click_flag_cb(gui_msg_action_t access, gui_msg_data_t *data, gui_msg_data_type_t type)
{
    if (access == GUI_MSG_ACCESS_GET) {
        data->value_int = LV_OBJ_FLAG_CLICKABLE;
    }
    return 0;
}

int gui_model_video_play_msg_clear_click_flag_cb(gui_msg_action_t access, gui_msg_data_t *data, gui_msg_data_type_t type)
{
    return 0;
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
REGISTER_UI_MODULE_EVENT_HANDLER(GUI_MODEL_VIDEO_PLAY_MSG_ID_DISP_PROGRESS_BAR)
.onchange = gui_model_video_play_msg_disp_progress_bar_cb,
};
REGISTER_UI_MODULE_EVENT_HANDLER(GUI_MODEL_VIDEO_PLAY_MSG_ID_ADD_CLICK_FLAG)
.onchange = gui_model_video_play_msg_add_click_flag_cb,
};
REGISTER_UI_MODULE_EVENT_HANDLER(GUI_MODEL_VIDEO_PLAY_MSG_ID_CLEAR_CLICK_FLAG)
.onchange = gui_model_video_play_msg_clear_click_flag_cb,
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
