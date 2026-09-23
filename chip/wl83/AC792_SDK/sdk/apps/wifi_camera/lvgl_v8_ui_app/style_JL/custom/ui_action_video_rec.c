#include "app_config.h"
#ifdef CONFIG_UI_STYLE_JL_ENABLE
unsigned char rec_running = 0;
char video_rec_car_num[64];
#if !LV_USE_GUIBUILDER_SIMULATOR
#include "lvgl.h"
#include "ui.h"
#include "custom.h"
#include "sys_time.h"
#include "system/includes.h"
#include "asm/includes.h"
#include "app_database.h"
#include "app_msg.h"
#include "action.h"

static struct tm rec_running_time = { 0 };
int target_time = 0;
static int count = 0;
extern bool usb_flag;
static int rec_remain_handler(const char *type, u32 remain_time);
extern void sys_prompt_show_ctl(int32_t show_time, void *tips);
void video_rec_post_msg(const char *msg, ...);
/* 注册控件模型 */
REGISTER_UI_MODULE_EVENT_HANDLER(GUI_MODEL_VIDEO_REC_MSG_ID_REC_REMAIN_TIME)
.onchange = gui_model_video_rec_msg_rec_remain_time_cb,
};

REGISTER_UI_MODULE_EVENT_HANDLER(GUI_MODEL_VIDEO_REC_MSG_ID_CYCREC_ICON)
.onchange = gui_model_video_rec_msg_cycrec_icon_cb,
};

REGISTER_UI_MODULE_EVENT_HANDLER(GUI_MODEL_VIDEO_REC_MSG_ID_MIC_ICON)
.onchange = gui_model_video_rec_msg_mic_icon_cb,
};

REGISTER_UI_MODULE_EVENT_HANDLER(GUI_MODEL_VIDEO_REC_MSG_ID_DELAYREC_ICON)
.onchange = gui_model_video_rec_msg_delayrec_icon_cb,
};

REGISTER_UI_MODULE_EVENT_HANDLER(GUI_MODEL_VIDEO_REC_MSG_ID_GSENSOR_ICON)
.onchange = gui_model_video_rec_msg_gsensor_icon_cb,
};

REGISTER_UI_MODULE_EVENT_HANDLER(GUI_MODEL_VIDEO_REC_MSG_ID_REC_RESO)
.onchange = gui_model_video_rec_msg_rec_reso_cb,
};

REGISTER_UI_MODULE_EVENT_HANDLER(GUI_MODEL_VIDEO_REC_MSG_ID_SHOW_GSENSOR_ICON)
.onchange = gui_model_video_rec_msg_show_gsensor_icon_cb,
};

REGISTER_UI_MODULE_EVENT_HANDLER(GUI_MODEL_VIDEO_REC_MSG_ID_HIDE_GSENSOR_ICON)
.onchange = gui_model_video_rec_msg_hide_gsensor_icon_cb,
};

REGISTER_UI_MODULE_EVENT_HANDLER(GUI_MODEL_VIDEO_REC_MSG_ID_SHOW_GUARD_ICON)
.onchange = gui_model_video_rec_msg_show_guard_icon_cb,
};

REGISTER_UI_MODULE_EVENT_HANDLER(GUI_MODEL_VIDEO_REC_MSG_ID_HIDE_GUARD_ICON)
.onchange = gui_model_video_rec_msg_hide_guard_icon_cb,
};

REGISTER_UI_MODULE_EVENT_HANDLER(GUI_MODEL_VIDEO_REC_MSG_ID_SHOW_MOTION_ICON)
.onchange = gui_model_video_rec_msg_show_motion_icon_cb,
};

REGISTER_UI_MODULE_EVENT_HANDLER(GUI_MODEL_VIDEO_REC_MSG_ID_HIDE_MOTION_ICON)
.onchange = gui_model_video_rec_msg_hide_motion_icon_cb,
};

REGISTER_UI_MODULE_EVENT_HANDLER(GUI_MODEL_VIDEO_REC_MSG_ID_HIDE_HDR_ICON)
.onchange = gui_model_video_rec_msg_hide_hdr_icon_cb,
};

REGISTER_UI_MODULE_EVENT_HANDLER(GUI_MODEL_VIDEO_REC_MSG_ID_SHOW_HDR_ICON)
.onchange = gui_model_video_rec_msg_show_hdr_icon_cb,
};

REGISTER_UI_MODULE_EVENT_HANDLER(GUI_MODEL_VIDEO_REC_MSG_ID_FLASH_HEADLIGHT)
.onchange = gui_model_video_rec_msg_flash_headlight_cb,
};

void get_province(void)
{
    const char *options = "京\n津\n晋\n冀\n蒙\n辽\n吉\n黑\n苏\n浙\n皖\n闽\n赣\n鲁\n豫\n鄂\n湘\n粤\n桂\n琼\n川\n贵\n滇\n渝\n藏\n陕\n甘\n青\n宁\n新\n台\n港\n澳"; // 获取所有选项的字符串
    int16_t index = db_select("proc"); // 你想要的索引号
    printf("index %d\n", index);
    if (index >= 0 && index < strlen(options)) {
        // 选项字符串是由 '\n' 分隔的，所以可以通过逐个比较每个选项来找到对应的文本
        const char *current_option = options;
        int option_count = 0; // 记录当前选项的数量

        while (*current_option != '\0' && option_count < index) {
            const char *next_option = strchr(current_option, '\n');
            if (next_option != NULL) {
                // 如果不是最后一个选项，跳过换行符
                current_option = next_option + 1;
            } else {
                // 如果是最后一个选项，停止搜索
                break;
            }
            option_count++; // 增加选项计数
        }

        if (option_count == index) {
            // 如果找到了正确的索引，复制选项文本到缓冲区
            const char *next_option = strchr(current_option, '\n');
            size_t length = next_option ? (next_option - current_option) : strlen(current_option);
            strncpy(video_rec_car_num, current_option, length);
            video_rec_car_num[length] = '\0'; // 确保字符串以 null 结尾
            printf("Found province: %s\n", video_rec_car_num);
        } else {
            printf("Province not found\n");
        }
    } else {
        printf("Index out of range\n");
    }

}
int set_car_num_part_a(uint32_t parm)
{
    get_province();
    video_rec_car_num[3] = (uint8_t)(parm >> 16);
    video_rec_car_num[4] = (uint8_t)(parm >> 24);

    return 0;
}

int set_car_num_part_b(uint32_t parm)
{
    video_rec_car_num[5] = (uint8_t)(parm);
    video_rec_car_num[6] = (uint8_t)(parm >> 8);
    video_rec_car_num[7] = (uint8_t)(parm >> 16);
    video_rec_car_num[8] = (uint8_t)(parm >> 24);
    video_rec_car_num[9] = '\0';
    printf("set_car_num: %s\n", video_rec_car_num);
    for (int i = 0; i < strlen(video_rec_car_num); i++) {
        printf("0x%02X ", video_rec_car_num[i]);
    }

    return 0;
}


/*
* 录像模式刷新录像剩余时间
*/
void rec_get_remain_time_ontouch(void)
{
    printf("\n -[function] %s -[line] %d\n", __FUNCTION__, __LINE__);
    app_send_message(APP_MSG_REC_GET_REMAIN_TIME, 0);
}

void rec_set_config(char *cfg, int val)
{
    printf("\n -[function] %s -[line] %d\n", __FUNCTION__, __LINE__);
    struct intent *it = NULL;
    it = malloc(sizeof(struct intent));
    init_intent(it);
    it->data = cfg;
    it->exdata = val;
    app_send_message(APP_MSG_REC_SET_CONFIG, 1, it);
}

static void key_touch_enable_cb(void)
{
    key_event_enable();
    touch_event_enable();
}

/*
* 录像启停控制--控件触摸事件回调
*/
void rec_control_ontouch(void)
{
    //异步模式下,暂时关闭触摸和按键
    key_event_disable();
    touch_event_disable();

    printf("\n -[function] %s -[line] %d\n", __FUNCTION__, __LINE__);
    app_send_message(APP_MSG_REC_CONTROL, 0);
    mdelay(5);
    key_touch_enable_cb();
}

/*
* 录像模式视窗切换控制--控件触摸事件回调
*/
void rec_switch_win_ontouch(void)
{
    printf("\n -[function] %s -[line] %d\n", __FUNCTION__, __LINE__);
    app_send_message(APP_MSG_REC_SWITCH_WIN, 0);

}

/*
 * (begin)UI状态变更主动请求APP函数
 */
void rec_tell_app_exit_menu(void)
{

    printf("\n -[function] %s -[line] %d\n", __FUNCTION__, __LINE__);
    int err;
    struct intent *it = NULL;
    it = malloc(sizeof(struct intent));
    init_intent(it);
    it->data = "exitMENU";
    err = app_send_message(APP_MSG_REC_CHANGE_STATUS, 1, it);
    if (err) {
        printf("res exit menu err! %d\n", err);
        /* ASSERT(err == 0, ":rec exitMENU\n"); */
    }
}

int rec_ask_app_open_menu(void)
{

    int err;
    struct intent *it = NULL;
    it = malloc(sizeof(struct intent));
    init_intent(it);

    it->data = "opMENU:";
    err = app_send_message(APP_MSG_REC_CHANGE_STATUS, 1, it);
    if (err) {
        printf("res ask menu err! %d\n", err);
        return -1;
        /* ASSERT(err == 0, ":rec opMENU fail! %d\n", err); */
    }
    if (!strcmp(it->data, "opMENU:dis")) {
        return -1;
    } else if (!strcmp(it->data, "opMENU:en")) {
    } else {
        ASSERT(0, "opMENU err\n");
    }
    return 0;
    /*
     * 返回0则打开菜单
     */
}

/*
* 录像模式文件加锁--控件触摸事件回调
*/

void rec_set_lock_ontouch(void)
{
    struct intent *it = NULL;
    it = malloc(sizeof(struct intent));
    init_intent(it);
    printf("it:%p", it);
    printf("\n -[function] %s -[line] %d\n", __FUNCTION__, __LINE__);
    it->data = "set_lock_statu";
    app_send_message(APP_MSG_REC_LOCK_FILE, 1, it);
    printf("it:%p", it);
    mdelay(30);

    if (it->exdata) {//已经上锁
        it->exdata = 0x0;//解锁
    } else {
        it->exdata = 0xff;//上锁
    }
    printf("it:%p", it);
    app_send_message(APP_MSG_REC_LOCK_FILE, 1, it);

}

void rec_set_lock_crash(void)
{
#if 0
    struct intent it;
    init_intent(&it);

    it.name = "video_rec";
    it.action = ACTION_VIDEO_REC_LOCK_FILE;
    it.data = "set_lock_statu";
    it.exdata = 0xff;//上锁
    start_app(&it);
#endif
}

//录像走时
int video_rec_record_time()
{
    lv_ui_video_rec *ui_scr = ui_get_scr_ptr(&guider_ui, GUI_SCREEN_VIDEO_REC);
    if (!ui_scr) {
        return -1;
    }
    if (rec_running) {
        if (!lv_obj_is_valid(ui_scr->video_rec_digitclock_record_time)) {
            printf("obj no valid \n");
            return 0;
        }

        if (!count) {
            memset(&rec_running_time, 0, sizeof(rec_running_time));
            count = 1;
            lv_label_set_text_fmt(ui_scr->video_rec_digitclock_record_time, "%02d:%02d:%02d", rec_running_time.tm_hour, rec_running_time.tm_min, rec_running_time.tm_sec);
            return 0;
        }
        if (++rec_running_time.tm_sec > 59) {
            rec_running_time.tm_sec = 0;
            if (++rec_running_time.tm_min > 59) {
                rec_running_time.tm_min = 0;
                if (++rec_running_time.tm_hour > 23) {
                    rec_running_time.tm_hour = 0;
                }
            } else if ((rec_running_time.tm_min == target_time) && (target_time != 0)) {
                rec_running_time.tm_sec = 0;
                rec_running_time.tm_min = 0;
                rec_running_time.tm_hour = 0;
            }
        }
        lv_label_set_text_fmt(ui_scr->video_rec_digitclock_record_time, "%02d:%02d:%02d", rec_running_time.tm_hour, rec_running_time.tm_min, rec_running_time.tm_sec);
        return 0;
    }
}

/*
 * 录像模式的APP状态响应回调
 */
//static const struct uimsg_handl rec_msg_handler[] = {
//	{ "onREC",          rec_on_handler       }, /* 开始录像 */
//	{ "offREC",         rec_off_handler      }, /* 停止录像 */
//	{ "saveREC",        rec_save_handler     }, /* 保存录像 */
//	{ "noCard",         rec_no_card_handler  }, /* 没有SD卡 */
//	{ "fsErr",          rec_fs_err_handler   }, /* 需要格式化 */
//	{ "gapErr",          rec_gap_err_handler   }, /* gap异常回调 */
//	{ "recErr",          rec_rec_err_handler   }, /* 录像异常回调  */
//	{ "onMIC",          rec_on_mic_handler   }, /* 打开录音 */
//	{ "offMIC",         rec_off_mic_handler  }, /* 关闭录音 */
//	{ "lockREC",        rec_lock_handler     }, /* 锁文件 */
//	{ "unlockREC",      rec_unlock_handler   }, /* 解锁文件 */
//	{ "HlightOn",      rec_headlight_on_handler   },
//	{ "HlightOff",     rec_headlight_off_handler  },
//	{ "Remain",         rec_remain_handler  },
//  { "appConnect",     app_connect_handler  },
//  { "appDisconnect",  app_disconnect_handler  },
//  { "wifiPreview",    wifi_preview_handler  },
//	{ NULL, NULL},      /* 必须以此结尾！ */
//};
/*
 * (begin)APP状态变更，UI响应回调
 */
static int rec_on_handler(const char *type, u32 arg)
{
    lv_ui_video_rec *ui_scr = ui_get_scr_ptr(&guider_ui, GUI_SCREEN_VIDEO_REC);
    if (!ui_scr) {
        return -1;
    }
    rec_remain_handler(0, 0);
    count = 0;
    lvgl_module_msg_send_value(GUI_MODEL_VIDEO_REC_MSG_ID_REC_BTN, LV_STATE_CHECKED, 0);
    rec_running = 1;
    lvgl_module_msg_send_global_ptr(GUI_MODEL_VIDEO_REC_MSG_ID_HIDE_REMAIN_TIME, (void *)LV_OBJ_FLAG_HIDDEN, 1, 0);
    lvgl_module_msg_send_global_ptr(GUI_MODEL_VIDEO_REC_MSG_ID_SHOW_RECORD_TIME, (void *)LV_OBJ_FLAG_HIDDEN, 1, 0);
    if (ui_scr->video_rec_timer_1 != NULL) {
        lv_timer_resume(ui_scr->video_rec_timer_1);
    }
    lvgl_module_msg_send_global_ptr(GUI_MODEL_VIDEO_REC_MSG_ID_REC_TIME_STATE, (void *)LV_STATE_DISABLED, 1, 0);

    return 0;
}

static int rec_off_handler(const char *type, u32 arg)
{
    lv_ui_video_rec *ui_scr = ui_get_scr_ptr(&guider_ui, GUI_SCREEN_VIDEO_REC);
    if (!ui_scr) {
        return -1;
    }
    rec_running = 0;
    if (ui_scr->video_rec_timer_1 != NULL) {
        lv_timer_pause(ui_scr->video_rec_timer_1);
    }
    lvgl_module_msg_send_global_ptr(GUI_MODEL_VIDEO_REC_MSG_ID_SHOW_REMAIN_TIME, (void *)LV_OBJ_FLAG_HIDDEN, 1, 0);
    lvgl_module_msg_send_global_ptr(GUI_MODEL_VIDEO_REC_MSG_ID_HIDE_RECORD_TIME, (void *)LV_OBJ_FLAG_HIDDEN, 1, 0);
    memset(&rec_running_time, 0, sizeof(rec_running_time));
    if (lv_obj_is_valid(ui_scr->video_rec_digitclock_record_time)) {
        lv_label_set_text_fmt(ui_scr->video_rec_digitclock_record_time, "%02d:%02d:%02d", rec_running_time.tm_hour, rec_running_time.tm_min, rec_running_time.tm_sec);
    }
    lvgl_module_msg_send_value(GUI_MODEL_VIDEO_REC_MSG_ID_REC_BTN, LV_STATE_DEFAULT, 0);
    lvgl_module_msg_send_global_ptr(GUI_MODEL_VIDEO_REC_MSG_ID_REC_TIME_STATE, (void *)LV_STATE_DEFAULT, 1, 0);
    return 0;
}

static int rec_remain_handler(const char *type, u32 remain_time)
{

    printf("remain= %s %d\n", type, remain_time);
    lvgl_module_msg_send_global_ptr(GUI_MODEL_VIDEO_REC_MSG_ID_HIDE_RECORD_TIME, (void *)LV_OBJ_FLAG_HIDDEN, 1, 0);
    struct tm *rec_remain_time_var;
    rec_remain_time_var = lvgl_module_msg_get_ptr(GUI_MODEL_VIDEO_REC_MSG_ID_REC_REMAIN_TIME, sizeof(struct tm));

    struct tm *time = rec_remain_time_var;
    time->tm_hour = remain_time / 3600;
    time->tm_min = remain_time % 3600 / 60;
    time->tm_sec = remain_time % 60;
    printf("%p reTIME hour:%02d, min:%02d, sec:%02d\n", rec_remain_time_var, time->tm_hour, time->tm_min, time->tm_sec);
    lvgl_module_msg_send_ptr(rec_remain_time_var, 0);

    return 0;
}

static int rec_video_rec_time_handler(const char *type, u32 rec_time)
{
    struct tm time = {0};
    time.tm_hour = rec_time / 3600;
    time.tm_min = rec_time % 3600 / 60;
    time.tm_sec = rec_time % 60;
    rec_running_time = time;
    return 0;
}




//更新剩余时间
int gui_model_video_rec_msg_rec_remain_time_cb(gui_msg_action_t access, gui_msg_data_t *data, gui_msg_data_type_t type)
{
    static struct tm rec_remain_time_var = {
        .tm_year = 124,
        .tm_mon = 6,
        .tm_mday = 2,
        .tm_hour = 0,
        .tm_min = 0,
        .tm_sec = 0,
    };
    if (access == GUI_MSG_ACCESS_SET) {
        rec_remain_time_var = data->value_time;
    }
    data->value_time = rec_remain_time_var;
    return 0;
}

static int rec_no_card_handler(const char *type, u32 arg)
{
    rec_remain_handler(NULL, 0);// 剩余时间清0
    lvgl_module_msg_send_value(GUI_MODEL_VIDEO_REC_MSG_ID_REC_BTN, LV_STATE_DEFAULT, 0);
    lvgl_rpc_post_func(sys_prompt_show_ctl, 2, 3000, (void *)_("nosd"));
    return 0;
}

static int rec_fs_err_handler(const char *type, u32 arg)
{
    //TF卡状态异常回调
    lvgl_module_msg_send_value(GUI_MODEL_VIDEO_REC_MSG_ID_REC_BTN, LV_STATE_DEFAULT, 0);
    video_rec_post_msg("sdStatus", 0);
    lvgl_rpc_post_func(sys_prompt_show_ctl, 2, 3000, (void *)_("fs_err"));
    return 0;
}

static int rec_gap_err_handler(const char *type, u32 arg)
{
    //提示用户关闭缩时录影
    lvgl_rpc_post_func(sys_prompt_show_ctl, 2, 3000, (void *)_("gap_err"));
    return 0;
}

static int rec_headlight_on_handler(const char *type, u32 arg)
{
    static int is_visible = 0;

    if (is_visible) {
        //隐藏图标
        lvgl_module_msg_send_value(GUI_MODEL_VIDEO_REC_MSG_ID_FLASH_HEADLIGHT, 0, 0);
        is_visible = 0;
    } else {
        //显示图标
        lvgl_module_msg_send_value(GUI_MODEL_VIDEO_REC_MSG_ID_FLASH_HEADLIGHT, 1, 0);
        is_visible = 1;
    }

    return 0;
}

static int app_connect_handler(const char *type, u32 arg)
{
    //app已连接回调
    lvgl_module_msg_send_global_ptr(GUI_MODEL_VIDEO_REC_MSG_ID_APP_CONNECTED, (void *)RES_CONNECTED, sizeof(RES_CONNECTED), 0);
    lvgl_rpc_post_func(sys_prompt_show_ctl, 2, 3000, (void *)_("app_connect"));
}

static int app_disconnect_handler(const char *type, u32 arg)
{
    //app断开回调
    lvgl_module_msg_send_global_ptr(GUI_MODEL_VIDEO_REC_MSG_ID_APP_CONNECTED, (void *)RES_DISCONNECT, sizeof(RES_CONNECTED), 0);
    lvgl_rpc_post_func(sys_prompt_show_ctl, 2, 3000, (void *)_("app_disconnect"));
}

static int wifi_preview_handler(const char *type, u32 arg)
{
    //不允许录像
    lvgl_module_msg_send_value(GUI_MODEL_VIDEO_REC_MSG_ID_REC_BTN, LV_STATE_DEFAULT, 0);
    lvgl_rpc_post_func(sys_prompt_show_ctl, 2, 3000, (void *)_("wifi_preview"));
}

static int rec_headlight_off_handler(const char *type, u32 arg)
{
    //隐藏图标
    lvgl_module_msg_send_value(GUI_MODEL_VIDEO_REC_MSG_ID_FLASH_HEADLIGHT, 0, 0);

    return 0;
}

/*
*	模式post消息给UI，执行UI动作
*
*/
void video_rec_post_msg(const char *msg, ...)
{
#ifdef USE_LVGL_V8_UI_DEMO
    va_list argptr;

    printf("[chili] %s %s   \n", __func__, msg);

    va_start(argptr, msg);

    if (strstr(msg, "Remain")) {
        rec_remain_handler(msg, va_arg(argptr, int));//获取第一个int数据
    } else if (strstr(msg, "onREC")) {
        lvgl_rpc_post_func(rec_on_handler, 2, msg, 0);
    } else if (strstr(msg, "offREC")) {
        lvgl_rpc_post_func(rec_off_handler, 2, msg, 0);
    } else if (strstr(msg, "noCard")) {
        rec_no_card_handler(msg, 0);
    } else if (strstr(msg, "HlightOn")) {
        rec_headlight_on_handler(msg, 0);
    } else if (strstr(msg, "HlightOff")) {
        rec_headlight_off_handler(msg, 0);
    } else if (strstr(msg, "videoRecTime")) {
        rec_video_rec_time_handler(msg, va_arg(argptr, int));//获取第一个int数据

    } else if (!strcmp(msg, "lockREC")) {
        lvgl_module_msg_send_global_ptr(GUI_MODEL_VIDEO_REC_MSG_ID_SHOW_CAR_CRASHLOCK, (void *)LV_OBJ_FLAG_HIDDEN, 1, 0);

    } else if (!strcmp(msg, "unlockREC")) {
        lvgl_module_msg_send_global_ptr(GUI_MODEL_VIDEO_REC_MSG_ID_HIDE_CAR_CRASHLOCK, (void *)LV_OBJ_FLAG_HIDDEN, 1, 0);

    } else if (strstr(msg, "recErr")) {
        lvgl_module_msg_send_value(GUI_MODEL_VIDEO_REC_MSG_ID_REC_BTN, LV_STATE_DEFAULT, 0);

    } else if (strstr(msg, "fsErr")) {
        rec_fs_err_handler(msg, 0);

    } else if (strstr(msg, "gapErr")) {
        rec_gap_err_handler(msg, 0);

    } else if (!strcmp(msg, "appConnect")) {
        app_connect_handler(msg, va_arg(argptr, int)); //获取第一个int数据

    } else if (!strcmp(msg, "appDisconnect")) {
        app_disconnect_handler(msg, va_arg(argptr, int));//

    } else if (!strcmp(msg, "wifiPreview")) {
        wifi_preview_handler(msg, va_arg(argptr, int));

    } else if (strstr(msg, "swWinicon")) {
        post_msg2sw_winicon(msg, va_arg(argptr, int)); //获取第一个int数据

    } else if (strstr(msg, "batIcon")) {
        post_msg2bat_icon(msg, va_arg(argptr, int)); //获取第一个int数据

    } else if (strstr(msg, "sdStatus")) {
        post_msg2sd_icon(msg, va_arg(argptr, int)); //获取第一个int数据


    } else {
        printf("[chili] %s your msg [%s] no callback! \n", __func__, msg, __LINE__);

    }
    va_end(argptr);

#endif

}

//注册页面加载卸载回调
int gui_src_action_video_rec(int action)
{
    struct application *app;
    lv_ui_video_rec *ui_scr = ui_get_scr_ptr(&guider_ui, GUI_SCREEN_VIDEO_REC);
    if (!ui_scr) {
        return -1;
    }

    printf("[chili] %s %d   \n", __func__, __LINE__);

#if LV_DISP_UI_FB_NUM
    lv_obj_set_style_bg_opa(ui_scr->video_rec, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
#else
    lv_obj_set_style_bg_opa(ui_scr->video_rec, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
#endif

    switch (action) {
    case GUI_SCREEN_ACTION_LOAD:
        usb_flag = false;
        if (db_select("num")) {
            lv_obj_clear_flag(ui_scr->video_rec_lbl_4, LV_OBJ_FLAG_HIDDEN);  //开启车牌号码功能，取消隐藏
        } else {
            lv_obj_add_flag(ui_scr->video_rec_lbl_4, LV_OBJ_FLAG_HIDDEN);    //未开启车牌号码功能，添加隐藏
        }
        if (db_select("dat")) {
            lv_obj_clear_flag(ui_scr->video_rec_digitclock_2, LV_OBJ_FLAG_HIDDEN);
        } else {
            lv_obj_add_flag(ui_scr->video_rec_digitclock_2, LV_OBJ_FLAG_HIDDEN);
        }
        if (db_select("lag") == LANG_ENGLISH) {
            lv_i18n_set_locale("en");
            i18n_refresh_all_texts(); //语言即可生效
        }
        printf("\n -[function] %s -[line] %d\n", __FUNCTION__, __LINE__);
        app = get_current_app();
        if (app) {
            printf("[chili] %s %d   \n", app->name, __LINE__);
            printf("\n -[function] %s -[line] %d\n", __FUNCTION__, __LINE__);
            app_mode_go_back();
        }
        printf("\n -[function] %s -[line] %d\n", __FUNCTION__, __LINE__);
        app_mode_change_replace(APP_MODE_REC);
        app_send_message(APP_MSG_REC_MAIN, 0);

        break;
    case GUI_SCREEN_ACTION_UNLOAD:

        break;
    }

}
REGISTER_UI_SCREEN_ACTION_HANDLER(GUI_SCREEN_VIDEO_REC)
.onchange = gui_src_action_video_rec,
};

/*下面是模型回调*/

int gui_model_video_rec_msg_cycrec_icon_cb(gui_msg_action_t access, gui_msg_data_t *data, gui_msg_data_type_t type)
{
    static int32_t cycrec_icon_var = RES_CYCLIC_VIDEO_1;
    if (data == NULL) {
        data = &guider_msg_data;
    }

    int cycrec_t = db_select("cyc");
    printf("[chili] %s %d   \n", __func__, cycrec_t);
    switch (cycrec_t) {
    case 1:
        cycrec_icon_var = RES_CYCLIC_VIDEO_1;
        target_time = 1;
        break;
    case 3:
        cycrec_icon_var = RES_CYCLIC_VIDEO_3;
        target_time = 3;
        break;
    case 10:
        cycrec_icon_var = RES_CYCLIC_VIDEO_10;
        target_time = 10;
        break;
        break;
    default:
        cycrec_icon_var = RES_CYCLIC_VIDEO_CLOSE;
        target_time = 0;
        break;
    }
    if (access == GUI_MSG_ACCESS_SET) {
        cycrec_icon_var = data->value_int;
        switch (cycrec_icon_var) {
        case RES_CYCLIC_VIDEO_3:
            cycrec_t = 3;
            target_time = 3;
            break;
        case RES_CYCLIC_VIDEO_1:
            cycrec_t = 1;
            target_time = 1;
            break;
        case RES_CYCLIC_VIDEO_10:
            cycrec_t = 10;
            target_time = 10;
            break;
        default:
            cycrec_t = 0;
            target_time = 0;
            break;
        }
        db_update("cyc", cycrec_t);
    }
    data->value_int = cycrec_icon_var;
    return 0;
}
int gui_model_video_rec_msg_car_nunber_cb(gui_msg_action_t access, gui_msg_data_t *data, gui_msg_data_type_t type)
{
    printf("[chili] %s %d   \n", __func__, __LINE__);
    if (access == GUI_MSG_ACCESS_GET) {
        set_car_num_part_a(db_select("cna"));
        set_car_num_part_b(db_select("cnb"));
    }
    static bool car_nunber_is_init = false;
    static char *car_nunber_var = NULL;
    if (car_nunber_is_init == false) {
        car_nunber_var = lv_mem_alloc(strlen(video_rec_car_num) + 1);
        strcpy(car_nunber_var, video_rec_car_num);
        car_nunber_is_init = true;
    }
    if (access == GUI_MSG_ACCESS_SET) {
        lv_mem_free(car_nunber_var);
        car_nunber_var = lv_mem_alloc(strlen(data->value_string) + 1);
        strcpy(car_nunber_var, data->value_string);
    }
    data->value_string = car_nunber_var;
    return 0;
}
int gui_model_video_rec_msg_mic_icon_cb(gui_msg_action_t access, gui_msg_data_t *data, gui_msg_data_type_t type)
{
    static int32_t mic_icon_var = RES_SOUND_CLOSE;
    if (data == NULL) {
        data = &guider_msg_data;
    }
    int mic = db_select("mic");
    switch (mic) {
    case 1:
        mic_icon_var = RES_SOUND;
        break;
    default:
        mic_icon_var = RES_SOUND_CLOSE;
        break;
    }
    if (access == GUI_MSG_ACCESS_SET) {
        mic_icon_var = data->value_int;
        switch (mic_icon_var) {
        case RES_SOUND:
            mic = 1;
            break;
        default:
            mic = 0;
            break;
        }
        db_update("mic", mic);
    }
    data->value_int = mic_icon_var;
    return 0;
}
int gui_model_video_rec_msg_delayrec_icon_cb(gui_msg_action_t access, gui_msg_data_t *data, gui_msg_data_type_t type)
{
    static int32_t delayrec_icon_var = RES_INTERVAL_VIDEO_CLOSE;
    if (data == NULL) {
        data = &guider_msg_data;
    }
    int delayrec = db_select("gap");
    printf("[chili] %s delayrec %d   \n", __func__, delayrec);
    switch (delayrec) {
    case 100:
        delayrec_icon_var = RES_INTERVAL_VIDEO_100;
        break;
    case 200:
        delayrec_icon_var = RES_INTERVAL_VIDEO_200;
        break;
    case 500:
        delayrec_icon_var = RES_INTERVAL_VIDEO_500;
        break;
    default:
        delayrec_icon_var = RES_INTERVAL_VIDEO_CLOSE;
        break;
    }
    if (access == GUI_MSG_ACCESS_SET) {
        delayrec_icon_var = data->value_int;
        switch (delayrec_icon_var) {
        case RES_INTERVAL_VIDEO_100:
            delayrec = 100;
            break;
        case RES_INTERVAL_VIDEO_200:
            delayrec = 200;
            break;
        case RES_INTERVAL_VIDEO_500:
            delayrec = 500;
            break;
        default:
            delayrec = 0;
            break;
        }
        db_update("gap", delayrec);
    }
    data->value_int = delayrec_icon_var;
    return 0;
}
int gui_model_video_rec_msg_gsensor_icon_cb(gui_msg_action_t access, gui_msg_data_t *data, gui_msg_data_type_t type)
{
    static int32_t gsensor_icon_var = RES_GRAVITY_SENSOR_LOW;
    if (data == NULL) {
        data = &guider_msg_data;
    }
    int gra = db_select("gra");
    switch (gra) {
    case GRA_SEN_LO:
        gsensor_icon_var = RES_GRAVITY_SENSOR_LOW;
        break;
    case GRA_SEN_MD:
        gsensor_icon_var = RES_GRAVITY_SENSOR_MIDLLER;
        break;
    case GRA_SEN_HI:
        gsensor_icon_var = RES_GRAVITY_SENSOR_HIGH;
        break;
    default:
        gsensor_icon_var = RES_GRAVITY_SENSOR_LOW;
        break;

    }
    if (access == GUI_MSG_ACCESS_SET) {
        gsensor_icon_var = data->value_int;
        switch (gsensor_icon_var) {
        case RES_GRAVITY_SENSOR_MIDLLER:
            gra = GRA_SEN_MD;
            break;
        case RES_GRAVITY_SENSOR_HIGH:
            gra = GRA_SEN_HI;
            break;
        default:
            gra = GRA_SEN_LO;
            break;
        }
        db_update("gra", gra);
        gra_set_function(db_select("gra"));
    }
    data->value_int = gsensor_icon_var;
    return 0;
}

int gui_model_video_rec_msg_rec_reso_cb(gui_msg_action_t access, gui_msg_data_t *data, gui_msg_data_type_t type)
{
    static char rec_reso_init_var[8] = { 0 };

    if (data == NULL) {
        data = &guider_msg_data;
    }
    int res = db_select("res");
    switch (res) {
    case VIDEO_RES_1080P:
        sprintf(rec_reso_init_var, "%dP", 1080);
        break;
    case VIDEO_RES_720P:
        sprintf(rec_reso_init_var, "%dP", 720);
        break;
    default:
        strcpy(rec_reso_init_var, "VGA");
        break;

    }

    if (access == GUI_MSG_ACCESS_SET) {
        strcpy(rec_reso_init_var, (char *)data->value_string);
        rec_get_remain_time_ontouch();
    }
    data->value_string = rec_reso_init_var;
    return 0;
}

int gui_model_video_rec_msg_show_gsensor_icon_cb(gui_msg_action_t access, gui_msg_data_t *data, gui_msg_data_type_t type)
{
    static lv_obj_flag_t show_gsensor_icon_var = LV_OBJ_FLAG_HIDDEN;
    if (data == NULL) {
        data = &guider_msg_data;
    }
    if (GRA_SEN_OFF == db_select("gra")) {
        show_gsensor_icon_var = LV_OBJ_FLAG_CLICKABLE;//发个标志，代替隐藏标志

    }
    if (access == GUI_MSG_ACCESS_SET) {
        show_gsensor_icon_var = data->value_int;
    }
    data->value_int = show_gsensor_icon_var;
    return 0;
}
int gui_model_video_rec_msg_hide_gsensor_icon_cb(gui_msg_action_t access, gui_msg_data_t *data, gui_msg_data_type_t type)
{
    static lv_obj_flag_t hide_gsensor_icon_var = LV_OBJ_FLAG_HIDDEN;
    if (data == NULL) {
        data = &guider_msg_data;
    }
    if (GRA_SEN_OFF != db_select("gra")) {
        hide_gsensor_icon_var = LV_OBJ_FLAG_CLICKABLE;//发个标志，代替隐藏标志

    }
    if (access == GUI_MSG_ACCESS_SET) {
        hide_gsensor_icon_var = data->value_int;
        if (LV_OBJ_FLAG_HIDDEN == hide_gsensor_icon_var) {
            db_update("gra", GRA_SEN_OFF);
        }
    }
    data->value_int = hide_gsensor_icon_var;
    return 0;
}
int gui_model_video_rec_msg_show_guard_icon_cb(gui_msg_action_t access, gui_msg_data_t *data, gui_msg_data_type_t type)
{
    static lv_obj_flag_t show_guard_icon_var = LV_OBJ_FLAG_HIDDEN;
    if (data == NULL) {
        data = &guider_msg_data;
    }
    if (!db_select("par")) {
        show_guard_icon_var = LV_OBJ_FLAG_CLICKABLE;//发个标志，代替隐藏标志

    }
    if (access == GUI_MSG_ACCESS_SET) {
        show_guard_icon_var = data->value_int;
        if (LV_OBJ_FLAG_HIDDEN == show_guard_icon_var) {
            db_update("par", 1);
        }
    }
    data->value_int = show_guard_icon_var;
    return 0;
}
int gui_model_video_rec_msg_hide_guard_icon_cb(gui_msg_action_t access, gui_msg_data_t *data, gui_msg_data_type_t type)
{
    static lv_obj_flag_t hide_guard_icon_var = LV_OBJ_FLAG_HIDDEN;
    if (data == NULL) {
        data = &guider_msg_data;
    }
    if (db_select("par")) {
        hide_guard_icon_var = LV_OBJ_FLAG_CLICKABLE;//发个标志，代替隐藏标志

    }
    if (access == GUI_MSG_ACCESS_SET) {
        hide_guard_icon_var = data->value_int;
        if (LV_OBJ_FLAG_HIDDEN == hide_guard_icon_var) {
            db_update("par", 0);
        }
    }
    data->value_int = hide_guard_icon_var;
    return 0;
}
int gui_model_video_rec_msg_show_motion_icon_cb(gui_msg_action_t access, gui_msg_data_t *data, gui_msg_data_type_t type)
{
    static lv_obj_flag_t show_motion_icon_var = LV_OBJ_FLAG_HIDDEN;
    if (data == NULL) {
        data = &guider_msg_data;
    }
    if (!db_select("mot")) {
        show_motion_icon_var = LV_OBJ_FLAG_CLICKABLE;//发个标志，代替隐藏标志

    }
    if (access == GUI_MSG_ACCESS_SET) {
        show_motion_icon_var = data->value_int;
        if (LV_OBJ_FLAG_HIDDEN == show_motion_icon_var) {
            db_update("mot", 1);
        }
    }
    data->value_int = show_motion_icon_var;
    return 0;
}
int gui_model_video_rec_msg_hide_motion_icon_cb(gui_msg_action_t access, gui_msg_data_t *data, gui_msg_data_type_t type)
{
    static lv_obj_flag_t hide_motion_icon_var = LV_OBJ_FLAG_HIDDEN;
    if (data == NULL) {
        data = &guider_msg_data;
    }
    if (db_select("mot")) {
        hide_motion_icon_var = LV_OBJ_FLAG_CLICKABLE;//发个标志，代替隐藏标志

    }
    if (access == GUI_MSG_ACCESS_SET) {
        hide_motion_icon_var = data->value_int;
        if (LV_OBJ_FLAG_HIDDEN == hide_motion_icon_var) {
            db_update("mot", 0);
        }
    }
    data->value_int = hide_motion_icon_var;
    return 0;
}
int gui_model_video_rec_msg_show_hdr_icon_cb(gui_msg_action_t access, gui_msg_data_t *data, gui_msg_data_type_t type)
{
    static lv_obj_flag_t show_hdr_icon_var = LV_OBJ_FLAG_HIDDEN;
    if (data == NULL) {
        data = &guider_msg_data;
    }
    if (!db_select("hdr")) {
        show_hdr_icon_var = LV_OBJ_FLAG_CLICKABLE;//发个标志，代替隐藏标志

    }
    if (access == GUI_MSG_ACCESS_SET) {
        show_hdr_icon_var = data->value_int;
        if (LV_OBJ_FLAG_HIDDEN == show_hdr_icon_var) {
            db_update("hdr", 1);
        }
    }
    data->value_int = show_hdr_icon_var;
    return 0;
}


int gui_model_video_rec_msg_hide_hdr_icon_cb(gui_msg_action_t access, gui_msg_data_t *data, gui_msg_data_type_t type)
{
    static lv_obj_flag_t hide_hdr_icon_var = LV_OBJ_FLAG_HIDDEN;
    if (data == NULL) {
        data = &guider_msg_data;
    }
    if (db_select("hdr")) {
        hide_hdr_icon_var = LV_OBJ_FLAG_CLICKABLE;//发个标志，代替隐藏标志

    }
    if (access == GUI_MSG_ACCESS_SET) {
        hide_hdr_icon_var = data->value_int;
        if (LV_OBJ_FLAG_HIDDEN == hide_hdr_icon_var) {
            db_update("hdr", 0);
        }
    }
    data->value_int = hide_hdr_icon_var;
    return 0;
}



int gui_model_video_rec_msg_show_rec_btn_cb(gui_msg_action_t access, gui_msg_data_t *data, gui_msg_data_type_t type)
{
    static lv_obj_flag_t show_rec_btn_var = LV_OBJ_FLAG_HIDDEN;

    if (access == GUI_MSG_ACCESS_GET) {
        if (rec_running) {
            show_rec_btn_var = LV_OBJ_FLAG_CLICKABLE;
        }
    }
    if (access == GUI_MSG_ACCESS_SET) {
        show_rec_btn_var = data->value_int;
    }
    data->value_int = show_rec_btn_var;
    return 0;
}
int gui_model_video_rec_msg_hide_rec_btn_cb(gui_msg_action_t access, gui_msg_data_t *data, gui_msg_data_type_t type)
{
    static lv_obj_flag_t hide_rec_btn_var = LV_OBJ_FLAG_HIDDEN;

    if (access == GUI_MSG_ACCESS_GET) {
        if (!rec_running) {
            hide_rec_btn_var = LV_OBJ_FLAG_CHECKABLE;
        }
    }
    if (access == GUI_MSG_ACCESS_SET) {
        hide_rec_btn_var = data->value_int;
    }
    data->value_int = hide_rec_btn_var;
    return 0;
}

int gui_model_video_rec_msg_show_rec_btn_anim_cb(gui_msg_action_t access, gui_msg_data_t *data, gui_msg_data_type_t type)
{
    static lv_obj_flag_t show_rec_btn_anim_var = LV_OBJ_FLAG_HIDDEN;
    if (access == GUI_MSG_ACCESS_GET) {
        if (!rec_running) {
            show_rec_btn_anim_var = LV_OBJ_FLAG_CHECKABLE;
        }
    }
    if (access == GUI_MSG_ACCESS_SET) {
        show_rec_btn_anim_var = data->value_int;
    }
    data->value_int = show_rec_btn_anim_var;
    return 0;
}

int gui_model_video_rec_msg_hide_rec_btn_anim_cb(gui_msg_action_t access, gui_msg_data_t *data, gui_msg_data_type_t type)
{
    static lv_obj_flag_t hide_rec_btn_anim_var = LV_OBJ_FLAG_HIDDEN;
    if (access == GUI_MSG_ACCESS_GET) {
        if (rec_running) {
            hide_rec_btn_anim_var = LV_OBJ_FLAG_CLICKABLE;
        }
    }
    if (access == GUI_MSG_ACCESS_SET) {
        hide_rec_btn_anim_var = data->value_int;
    }
    data->value_int = hide_rec_btn_anim_var;
    return 0;
}

int gui_model_video_rec_msg_flash_headlight_cb(gui_msg_action_t access, gui_msg_data_t *data, gui_msg_data_type_t type)
{
    if (access == GUI_MSG_ACCESS_GET) {
        data->value_int = 0;
    }
    return 0;
}



#endif


#endif
