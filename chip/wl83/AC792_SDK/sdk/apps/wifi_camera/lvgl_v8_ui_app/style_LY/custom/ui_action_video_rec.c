#include "app_config.h"
#ifdef CONFIG_UI_STYLE_LY_ENABLE
#include "custom.h"
#if !LV_USE_GUIBUILDER_SIMULATOR
#include "ui.h"
#include "lvgl.h"
#include "sys_time.h"
#include "system/includes.h"
#include "asm/includes.h"
#include "app_database.h"
#include "action.h"

unsigned char rec_running = 0;
char video_rec_car_num[64];
static struct tm rec_running_time = { 0 };
int target_time = 0;
static int count = 0;
static int rec_remain_handler(const char *type, u32 remain_time);

extern bool usb_flag;

void enter_video_rec_callback(void *priv, int err)
{
    printf("--->%s()----->%d\n", __func__, __LINE__);
    // key_event_enable();
}

//注册页面加载卸载回调
int gui_src_action_video_rec(int action)
{
    struct intent it;
    struct application *app;
    init_intent(&it);

    printf("--->%s()----->%d, action: %d\n", __func__, __LINE__, action);

    switch (action) {
    case GUI_SCREEN_ACTION_LOAD: {
        lv_ui_video_rec *ui_scr = ui_get_scr_ptr(&guider_ui, GUI_SCREEN_VIDEO_REC);
        if (!ui_scr) {
            return -1;
        }
#if LV_DISP_UI_FB_NUM
        lv_obj_set_style_bg_opa(ui_scr->video_rec, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
#else
        lv_obj_set_style_bg_opa(ui_scr->video_rec, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
#endif
        usb_flag = false;
        /* 当在设置菜单页面里开录像后，返回录像页面需重新打开录像计时的定时器 */
        if ((ui_scr->video_rec_timer_1 != NULL) && rec_running) {
            lv_timer_resume(ui_scr->video_rec_timer_1);
        }

        /* 录像状态下改变计时时间颜色 */
        if (lv_obj_is_valid(ui_scr->video_rec_digitclock_2) && rec_running) {
            lvgl_module_msg_send_global_ptr(GUI_MODEL_VIDEO_REC_MSG_ID_REC_TIME_STATE, (void *)LV_STATE_DISABLED, 1, 0);
        }

        // printf("--->%s()----->%d\n", __func__, __LINE__);
        /* app = get_current_app(); */
        key_event_disable();
        /* if (app) { */
        /* printf("[chili] %s %d   \n", app->name, __LINE__); */
        /* printf("\n -[function] %s -[line] %d\n", __FUNCTION__, __LINE__); */
        /* app_mode_go_back(); */
        /* } */
        //} else {
        // printf("--->%s()----->%d\n", __func__, __LINE__);
        //	video_rec_get_remain_time();
        // break;
        // }
        printf("\n -[function] %s -[line] %d\n", __FUNCTION__, __LINE__);
        app_mode_change_replace(APP_MODE_REC);
        app_send_message(APP_MSG_REC_MAIN, 0);
        key_event_enable();
    }
    break;
    case GUI_SCREEN_ACTION_UNLOAD:
        break;
    }

}
REGISTER_UI_SCREEN_ACTION_HANDLER(GUI_SCREEN_VIDEO_REC)
.onchange = gui_src_action_video_rec,
};



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

static void rec_set_file_lock(void)
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

void rec_lock_setting(void)
{
    rec_set_file_lock();
    lv_ui_video_rec *ui_scr = ui_get_scr_ptr(&guider_ui, GUI_SCREEN_VIDEO_REC);
    if (!ui_scr) {
        return;
    }
    if (!lv_obj_has_flag(ui_scr->video_rec_img_key_state, LV_OBJ_FLAG_HIDDEN)) {
        lvgl_module_msg_send_value(GUI_MODEL_VIDEO_REC_MSG_ID_KEY_STATE, false, 0);
    } else {
        lvgl_module_msg_send_value(GUI_MODEL_VIDEO_REC_MSG_ID_KEY_STATE, true, 0);
    }

}


/*注册页面按键响应函数回调*/
int video_rec_key_handler(struct key_event *key)
{
    printf("---->%s()----->key action: %d, value: %d\n", __func__, key->action, key->value);
    switch (key->action) {
    case KEY_EVENT_CLICK:
        switch (key->value) {
        case KEY_OK:
        case KEY_DOWN:
        case KEY_UP:
            lv_ui_video_rec *ui_scr = ui_get_scr_ptr(&guider_ui, GUI_SCREEN_VIDEO_REC);
            if (!ui_scr) {
                return -1;
            }
            if (!lv_obj_has_flag(ui_scr->video_rec_view_menu_b, LV_OBJ_FLAG_HIDDEN)) {  //进入设置菜单时, 按键消息不传到792 app_core
                return 0;
            } else {
                return 1;
            }
            break;
        default:
            break;
        }
        break;
    case KEY_EVENT_LONG:
        switch (key->value) {
        case KEY_MENU:
#if 0
            printf("key event long swith video photo\n");
            gui_scr_t *screen = gui_scr_get(GUI_SCREEN_VIDEO_PHOTO);
            if (screen == NULL) {
                screen = gui_scr_create(GUI_SCREEN_VIDEO_PHOTO, "video_photo", guider_ui.video_photo, (gui_scr_setup_cb_t)setup_scr_video_photo, (gui_scr_unload_cb_t)unload_scr_video_photo);
            }
            ui_load_scr_anim(&guider_ui, screen, LV_SCR_LOAD_ANIM_NONE, 0, 0, true, true, false);
#endif
            break;
        default:
            break;
        }
        break;
    default:
        break;
    }

    return 0;
}
REGISTER_UI_KEY_EVENT_HANDLER(GUI_SCREEN_VIDEO_REC)
.key_onchange = video_rec_key_handler,
};


/* 注册控件模型 */
REGISTER_UI_MODULE_EVENT_HANDLER(GUI_MODEL_VIDEO_REC_MSG_ID_REC_REMAIN_TIME)
.onchange = gui_model_video_rec_msg_rec_remain_time_cb,
};

REGISTER_UI_MODULE_EVENT_HANDLER(GUI_MODEL_VIDEO_REC_MSG_ID_CYCREC_ICON)
.onchange = gui_model_video_rec_msg_cycrec_icon_cb,
};

REGISTER_UI_MODULE_EVENT_HANDLER(GUI_MODEL_VIDEO_REC_MSG_ID_CYC_STATE)
.onchange = gui_model_video_rec_msg_cyc_state_cb,
};

REGISTER_UI_MODULE_EVENT_HANDLER(GUI_MODEL_VIDEO_REC_MSG_ID_GUARD_STATE)
.onchange = gui_model_video_rec_msg_guard_state_cb,
};

REGISTER_UI_MODULE_EVENT_HANDLER(GUI_MODEL_VIDEO_REC_MSG_ID_MOTION_STATE)
.onchange = gui_model_video_rec_msg_motion_state_cb,
};

REGISTER_UI_MODULE_EVENT_HANDLER(GUI_MODEL_VIDEO_REC_MSG_ID_GAP_STATE)
.onchange = gui_model_video_rec_msg_gap_state_cb,
};

REGISTER_UI_MODULE_EVENT_HANDLER(GUI_MODEL_VIDEO_REC_MSG_ID_HDR_STATE)
.onchange = gui_model_video_rec_msg_hdr_state_cb,
};

REGISTER_UI_MODULE_EVENT_HANDLER(GUI_MODEL_VIDEO_REC_MSG_ID_GRA_STATE)
.onchange = gui_model_video_rec_msg_gra_state_cb,
};

REGISTER_UI_MODULE_EVENT_HANDLER(GUI_MODEL_VIDEO_REC_MSG_ID_GSENSOR_ICON)
.onchange = gui_model_video_rec_msg_gsensor_icon_cb,
};

REGISTER_UI_MODULE_EVENT_HANDLER(GUI_MODEL_VIDEO_REC_MSG_ID_EXP_ICON)
.onchange = gui_model_video_rec_msg_exp_icon_cb,
};

REGISTER_UI_MODULE_EVENT_HANDLER(GUI_MODEL_VIDEO_REC_MSG_ID_REC_RESO)
.onchange = gui_model_video_rec_msg_rec_reso_cb,
};

REGISTER_UI_MODULE_EVENT_HANDLER(GUI_MODEL_VIDEO_REC_MSG_ID_CAR_NUM)
.onchange = gui_model_video_rec_msg_car_num_cb,
};

REGISTER_UI_MODULE_EVENT_HANDLER(GUI_MODEL_VIDEO_REC_MSG_ID_CAR_NUNBER)
.onchange = gui_model_video_rec_msg_car_nunber_cb,
};

REGISTER_UI_MODULE_EVENT_HANDLER(GUI_MODEL_VIDEO_REC_MSG_ID_FLASH_HEADLIGHT)
.onchange = gui_model_video_rec_msg_flash_headlight_cb,
};

REGISTER_UI_MODULE_EVENT_HANDLER(GUI_MODEL_VIDEO_REC_MSG_ID_REC_ICON_STATE)
.onchange = gui_model_video_rec_msg_rec_icon_state_cb,
};


//录像走时
int gui_model_video_rec_msg_rec_remain_time_cb(gui_msg_action_t access, gui_msg_data_t *data, gui_msg_data_type_t type)
{
    // printf(">>>>>>>%s------>%d---->access: %d\n", __func__, __LINE__, access);
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
    if (rec_running) {
        if (!count) {
            // printf("--->%s()----->%d\n", __func__, __LINE__);
            memset(&rec_running_time, 0, sizeof(rec_running_time));
            data->value_time = rec_running_time;
            count = 1;
            return 0;
        }

        data->value_time = rec_running_time;
        if (++rec_running_time.tm_sec > 59) {
            rec_running_time.tm_sec = 0;
            if (++rec_running_time.tm_min > 59) {
                rec_running_time.tm_min = 0;
                if (++rec_running_time.tm_hour > 23) {
                    rec_running_time.tm_hour = 0;
                }
            } else if ((rec_running_time.tm_min == target_time) && (target_time != 0)) {
                // printf("--->%s()----->%d\n", __func__, __LINE__);
                rec_running_time.tm_sec = 0;
                rec_running_time.tm_min = 0;
                rec_running_time.tm_hour = 0;
            }
        }

        if ((rec_running_time.tm_sec % 2) == 0) {
            //   lv_obj_clear_flag(ui_scr->video_rec_img_rec_state, LV_OBJ_FLAG_HIDDEN);
            lvgl_module_msg_send_value(GUI_MODEL_VIDEO_REC_MSG_ID_REC_ICON_STATE, true, 0);
        } else {
            //   lv_obj_add_flag(ui_scr->video_rec_img_rec_state, LV_OBJ_FLAG_HIDDEN);
            lvgl_module_msg_send_value(GUI_MODEL_VIDEO_REC_MSG_ID_REC_ICON_STATE, false, 0);
        }
        // printf(">>>>>rec time: %d: %d: %d\n", rec_running_time.tm_hour, rec_running_time.tm_min, rec_running_time.tm_sec);
        return 0;
    }
    // printf(">>>>>time: %d: %d: %d\n", rec_running_time.tm_hour, rec_running_time.tm_min, rec_running_time.tm_sec);
    data->value_time = rec_remain_time_var;
    return 0;
}

int gui_model_video_rec_msg_cycrec_icon_cb(gui_msg_action_t access, gui_msg_data_t *data, gui_msg_data_type_t type)
{
    static int32_t cycrec_icon_var = 0;
    target_time = 0;
    if (data == NULL) {
        data = &guider_msg_data;
    }

    int cycrec_t = db_select("cyc");
    printf("[chili] %s %d   \n", __func__, cycrec_t);
    switch (cycrec_t) {
    case 3:
        target_time = 3;
        cycrec_icon_var = RES_CYCLIC_VIDEO_3;
        break;
    case 5:
        target_time = 5;
        cycrec_icon_var = RES_CYCLIC_VIDEO_5;
        break;
    case 10:
        target_time = 10;
        cycrec_icon_var = RES_CYCLIC_VIDEO_10;
        break;
    default:  //关循环录像时（cyc为0），按录像5min来计时
        target_time = 5;
        cycrec_icon_var = RES_CYCLIC_VIDEO_5;
        break;
    }

    if (access == GUI_MSG_ACCESS_SET) {
        cycrec_icon_var = data->value_int;
    }
    printf(">>>%s()---->target_time: %d\n", __func__, target_time);
    data->value_int = cycrec_icon_var;
    return 0;
}

int gui_model_video_rec_msg_cyc_state_cb(gui_msg_action_t access, gui_msg_data_t *data, gui_msg_data_type_t type)
{
    static bool cyc_state_var = false;
    if (data == NULL) {
        data = &guider_msg_data;
    }

    if (db_select("cyc")) {
        cyc_state_var = true;
    }

    if (access == GUI_MSG_ACCESS_SET) {
        cyc_state_var = data->value_int;
    }
    data->value_int = cyc_state_var;
    return 0;
}

int gui_model_video_rec_msg_guard_state_cb(gui_msg_action_t access, gui_msg_data_t *data, gui_msg_data_type_t type)
{
    static bool guard_state_var = false;
    if (data == NULL) {
        data = &guider_msg_data;
    }

    if (db_select("par")) {
        guard_state_var = true;
    }

    if (access == GUI_MSG_ACCESS_SET) {
        guard_state_var = data->value_int;
    }
    data->value_int = guard_state_var;
    return 0;
}

int gui_model_video_rec_msg_motion_state_cb(gui_msg_action_t access, gui_msg_data_t *data, gui_msg_data_type_t type)
{
    static bool motion_state_var = false;
    if (data == NULL) {
        data = &guider_msg_data;
    }

    if (db_select("mot")) {
        motion_state_var = true;
    }

    if (access == GUI_MSG_ACCESS_SET) {
        motion_state_var = data->value_int;
    }
    data->value_int = motion_state_var;
    return 0;
}

int gui_model_video_rec_msg_gap_state_cb(gui_msg_action_t access, gui_msg_data_t *data, gui_msg_data_type_t type)
{
    static bool gap_state_var = false;
    if (data == NULL) {
        data = &guider_msg_data;
    }

    if (db_select("gap")) {
        gap_state_var = true;
    }

    if (access == GUI_MSG_ACCESS_SET) {
        gap_state_var = data->value_int;
    }
    data->value_int = gap_state_var;
    return 0;
}

int gui_model_video_rec_msg_hdr_state_cb(gui_msg_action_t access, gui_msg_data_t *data, gui_msg_data_type_t type)
{
    static bool hdr_state_var = false;
    if (data == NULL) {
        data = &guider_msg_data;
    }

    if (db_select("hdr")) {
        hdr_state_var = true;
    }

    if (access == GUI_MSG_ACCESS_SET) {
        hdr_state_var = data->value_int;
    }
    data->value_int = hdr_state_var;
    return 0;
}

int gui_model_video_rec_msg_gra_state_cb(gui_msg_action_t access, gui_msg_data_t *data, gui_msg_data_type_t type)
{
    static bool gra_state_var = false;
    if (data == NULL) {
        data = &guider_msg_data;
    }

    if (db_select("gra")) {
        gra_state_var = true;
    }

    if (access == GUI_MSG_ACCESS_SET) {
        gra_state_var = data->value_int;
    }
    data->value_int = gra_state_var;
    return 0;
}

int gui_model_video_rec_msg_gsensor_icon_cb(gui_msg_action_t access, gui_msg_data_t *data, gui_msg_data_type_t type)
{
    static int32_t gsensor_icon_var = RES_I_GRA_L;
    if (data == NULL) {
        data = &guider_msg_data;
    }

    int gra = db_select("gra");
    switch (gra) {
    case GRA_SEN_LO:
        gsensor_icon_var = RES_I_GRA_L;
        break;
    case GRA_SEN_MD:
        gsensor_icon_var = RES_I_GRA_M;
        break;
    case GRA_SEN_HI:
        gsensor_icon_var = RES_I_GRA_H;
        break;
    default:
        gsensor_icon_var = RES_I_GRA_L;
        break;
    }

    if (access == GUI_MSG_ACCESS_SET) {
        gsensor_icon_var = data->value_int;
    }
    data->value_int = gsensor_icon_var;
    return 0;
}

int gui_model_video_rec_msg_exp_icon_cb(gui_msg_action_t access, gui_msg_data_t *data, gui_msg_data_type_t type)
{
    static int32_t exp_icon_var = RES_EXP_A0;
    if (data == NULL) {
        data = &guider_msg_data;
    }

    int exp = db_select("exp");
    switch (exp) {
    case 0xfffffffd://-3
        exp_icon_var = RES_EXP_D3;
        break;
    case 0xfffffffe://-2
        exp_icon_var = RES_EXP_D2;
        break;
    case 0xffffffff://-1
        exp_icon_var = RES_EXP_D1;
        break;
    case 0:
        exp_icon_var = RES_EXP_A0;
        break;
    case 1:
        exp_icon_var = RES_EXP_A1;
        break;
    case 2:
        exp_icon_var = RES_EXP_A2;
        break;
    case 3:
        exp_icon_var = RES_EXP_A3;
        break;
    default:
        exp_icon_var = RES_EXP_A0;
        break;
    }

    if (access == GUI_MSG_ACCESS_SET) {
        exp_icon_var = data->value_int;
    }
    data->value_int = exp_icon_var;
    return 0;
}

int index_of_table8(u8 value, const u8 *table, int table_size)
{
    int i;

    for (i = 0; i < table_size; i++) {
        if (table[i] == value) {
            return i;
        }
    }

    return -ENOENT;
}

int index_of_table16(u16 value, const u16 *table, int table_size)
{
    int i;

    for (i = 0; i < table_size; i++) {
        if (table[i] == value) {
            return i;
        }
    }

    return -ENOENT;
}

static const u16 province_gb2312[] = {
    0xA9BE, 0xF2BD, 0xFABD, 0xBDBC, 0xC9C3, 0xC9C1, 0xAABC, 0xDABA,
    0xD5CB, 0xE3D5, 0xEECD, 0xF6C3, 0xD3B8, 0xB3C2, 0xA5D4, 0xF5B6,
    0xE6CF, 0xC1D4, 0xF0B9, 0xEDC7, 0xA8B4, 0xF3B9, 0xC6D4, 0xE5D3,
    0xD8B2, 0xC2C9, 0xCAB8, 0xE0C7, 0xFEC4, 0xC2D0, 0xA6BB
};

int gui_model_video_rec_msg_car_num_cb(gui_msg_action_t access, gui_msg_data_t *data, gui_msg_data_type_t type)
{
    static bool car_num_var = false;
    if (data == NULL) {
        data = &guider_msg_data;
    }

    printf("---->%s()----num: %d\n", __func__, db_select("num"));
    if (db_select("num")) {
        car_num_var = true;
        u32 parm = db_select("cna");
        printf(">>>>>>car parm: %x\n", parm);

    }

    if (access == GUI_MSG_ACCESS_SET) {
        car_num_var = data->value_int;
    }
    data->value_int = car_num_var;
    return 0;
}

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

int gui_model_video_rec_msg_flash_headlight_cb(gui_msg_action_t access, gui_msg_data_t *data, gui_msg_data_type_t type)
{
    if (access == GUI_MSG_ACCESS_GET) {
        data->value_int = 0;
    }
    return 0;
}

int gui_model_video_rec_msg_rec_icon_state_cb(gui_msg_action_t access, gui_msg_data_t *data, gui_msg_data_type_t type)
{
    static bool rec_icon_state_var = false;

    if (!rec_running) {
        // if (lv_obj_is_valid(ui_scr->video_rec_img_rec_state) && (!lv_obj_has_flag(ui_scr->video_rec_img_rec_state, LV_OBJ_FLAG_HIDDEN))) {
        printf("--->%s()----->%d\n", __func__, __LINE__);
        rec_icon_state_var = false;
        // }
        lvgl_module_msg_send_global_ptr(GUI_MODEL_VIDEO_REC_MSG_ID_REC_TIME_STATE, (void *)LV_STATE_DEFAULT, 1, 0);
    }

    if (access == GUI_MSG_ACCESS_SET) {
        rec_icon_state_var = data->value_int;
    }
    data->value_int = rec_icon_state_var;
    return 0;
}


int rec_set_config(char *label, uint32_t value)
{
#if !LV_USE_GUIBUILDER_SIMULATOR
    printf("\n -[function] %s -[line] %d\n", __FUNCTION__, __LINE__);
    struct intent *it = NULL;
    it = malloc(sizeof(struct intent));
    init_intent(it);
    it->data = label;
    it->exdata = value;
    app_send_message(APP_MSG_REC_SET_CONFIG, 1, it);
    return 0;
#else
    return 0;
#endif
}

/*
* 录像模式刷新录像剩余时间
*/
void rec_get_remain_time_ontouch(void)
{
    printf("\n -[function] %s -[line] %d\n", __FUNCTION__, __LINE__);
    app_send_message(APP_MSG_REC_GET_REMAIN_TIME, 0);
}

int gui_model_video_rec_msg_rec_reso_cb(gui_msg_action_t access, gui_msg_data_t *data, gui_msg_data_type_t type)
{
    static char rec_reso_init_var[8] = { 0 };

    if (data == NULL) {
        data = &guider_msg_data;
    }

    switch (db_select("res")) {
    case 1:
        sprintf(rec_reso_init_var, "%dP", 720);
        break;
    case 2:
        sprintf(rec_reso_init_var, "%dP", 480);
        break;
    default:
        strcpy(rec_reso_init_var, "480P");
        break;
    }

    if (access == GUI_MSG_ACCESS_SET) {
        strcpy(rec_reso_init_var, (char *)data->value_string);
        rec_get_remain_time_ontouch();
    }
    data->value_string = rec_reso_init_var;
    return 0;
}

static int rec_remain_handler(const char *type, u32 remain_time)
{
#if 0
    printf("remain= %s %d\n", type, remain_time);

    struct tm *rec_remain_time_var;

    if (ui_scr->video_rec_digitclock_2) {
        if (lv_obj_is_valid(ui_scr->video_rec_digitclock_2)) {
            rec_remain_time_var = lvgl_module_msg_get_ptr(GUI_MODEL_VIDEO_REC_MSG_ID_REC_REMAIN_TIME, sizeof(struct tm));
        } else {
            return 0;
        }
    } else {
        return 0;
    }
    struct tm *time = rec_remain_time_var;
    time->tm_hour = remain_time / 3600;
    time->tm_min = remain_time % 3600 / 60;
    time->tm_sec = remain_time % 60;
    printf("%p reTIME hour:%02d, min:%02d, sec:%02d\n", rec_remain_time_var, time->tm_hour, time->tm_min, time->tm_sec);
    if (ui_scr->video_rec_digitclock_2 && rec_remain_time_var) {
        if (lv_obj_is_valid(ui_scr->video_rec_digitclock_2)) {
            lvgl_module_msg_send_ptr(rec_remain_time_var, 0);
        }
    }
    printf("[chili] %s %d   \n", __func__, __LINE__);

    return 0;
#else
    printf("remain= %s %d\n", type, remain_time);

    struct tm *rec_remain_time_var = NULL;

    rec_remain_time_var = lvgl_module_msg_get_ptr(GUI_MODEL_VIDEO_REC_MSG_ID_REC_REMAIN_TIME, sizeof(struct tm));
    if (!rec_remain_time_var) {
        printf("------>%s()----->%d\n", __func__, __LINE__);
        return 0;
    }

    struct tm *time = rec_remain_time_var;
    time->tm_hour = remain_time / 3600;
    time->tm_min = remain_time % 3600 / 60;
    time->tm_sec = remain_time % 60;
    printf("%p reTIME hour:%02d, min:%02d, sec:%02d\n", rec_remain_time_var, time->tm_hour, time->tm_min, time->tm_sec);
    lvgl_module_msg_send_ptr(rec_remain_time_var, 0);

    return 0;
#endif
}

static int rec_no_card_handler(const char *type, u32 arg)
{
    printf("------>%s()----->%d\n", __func__, __LINE__);
    rec_remain_handler(NULL, 0);  //剩余时间清0
    // lvgl_module_msg_send_value(GUI_MODEL_VIDEO_REC_MSG_ID_REC_BTN, LV_STATE_DEFAULT, 0);
    extern void sys_prompt_show_ctl(int32_t show_time, void *tips);
    lvgl_rpc_post_func(sys_prompt_show_ctl, 2, 3000, (void *)_("nosd"));
    return 0;
}

static int rec_on_handler(const char *type, u32 arg)
{
    count = 0;
    rec_running = 1;
    lv_ui_video_rec *ui_scr = ui_get_scr_ptr(&guider_ui, GUI_SCREEN_VIDEO_REC);
    if (!ui_scr) {
        return -1;
    }
    if (lv_obj_is_valid(ui_scr->video_rec_img_rec_state)) {
        lvgl_module_msg_send_value(GUI_MODEL_VIDEO_REC_MSG_ID_REC_ICON_STATE, true, 0);
    }

    lvgl_module_msg_send_global_ptr(GUI_MODEL_VIDEO_REC_MSG_ID_REC_REMAIN_TIME, NULL, 0, 0);
    if (ui_scr->video_rec_timer_1 != NULL) {
        printf(">>>>>>>resume rec timer");
        lv_timer_resume(ui_scr->video_rec_timer_1);
    }

    if (lv_obj_is_valid(ui_scr->video_rec_digitclock_2)) {
        lvgl_module_msg_send_global_ptr(GUI_MODEL_VIDEO_REC_MSG_ID_REC_TIME_STATE, (void *)LV_STATE_DISABLED, 1, 0);  //设置录像时间控件的状态，状态不同字体颜色不同
    }

    return 0;
}

static int rec_off_handler(const char *type, u32 arg)
{
    rec_running = 0;
    lv_ui_video_rec *ui_scr = ui_get_scr_ptr(&guider_ui, GUI_SCREEN_VIDEO_REC);
    if (!ui_scr) {
        return -1;
    }
    if (ui_scr->video_rec_timer_1 != NULL) {
        printf(">>>>>>>pause rec timer");
        lv_timer_pause(ui_scr->video_rec_timer_1);
    }
    memset(&rec_running_time, 0, sizeof(rec_running_time));
    if (ui_scr->video_rec_img_rec_state) {
        if (lv_obj_is_valid(ui_scr->video_rec_img_rec_state)) {
            lvgl_module_msg_send_value(GUI_MODEL_VIDEO_REC_MSG_ID_REC_ICON_STATE, false, 0);
        }
    }
    if (ui_scr->video_rec_digitclock_2) {
        if (lv_obj_is_valid(ui_scr->video_rec_digitclock_2)) {
            lvgl_module_msg_send_global_ptr(GUI_MODEL_VIDEO_REC_MSG_ID_REC_TIME_STATE, (void *)LV_STATE_DEFAULT, 1, 0);
        }
    }
    return 0;
}

static int rec_headlight_on_handler(const char *type, u32 arg)
{
    static int is_visible = 0;
    // printf("----->%s()------visible: %d\n", __func__, is_visible);
    if (is_visible) {
        //隐藏图标
        lvgl_module_msg_send_value(GUI_MODEL_VIDEO_REC_MSG_ID_FLASH_HEADLIGHT, false, 0);
        is_visible = 0;
    } else {
        //显示图标
        lvgl_module_msg_send_value(GUI_MODEL_VIDEO_REC_MSG_ID_FLASH_HEADLIGHT, true, 0);
        is_visible = 1;
    }

    return 0;
}

static int rec_headlight_off_handler(const char *type, u32 arg)
{
    // printf("------>%s()----->%d\n", __func__, __LINE__);
    //隐藏图标
    lvgl_module_msg_send_value(GUI_MODEL_VIDEO_REC_MSG_ID_FLASH_HEADLIGHT, false, 0);

    return 0;
}

static int rec_video_rec_time_handler(const char *type, u32 rec_time)
{
    printf("videoRecTime= %s %d\n", type, rec_time);
    struct tm time = {0};
    time.tm_hour = rec_time / 3600;
    time.tm_min = rec_time % 3600 / 60;
    time.tm_sec = rec_time % 60;
    rec_running_time = time;

    return 0;
}

static int rec_fs_err_handler(const char *type, u32 arg)
{
    //TF卡状态异常回调
    // lvgl_module_msg_send_value(GUI_MODEL_VIDEO_REC_MSG_ID_REC_BTN, LV_STATE_DEFAULT, 0);
    post_msg2sd_icon(0);
    extern void sys_prompt_show_ctl(int32_t show_time, void *tips);
    lvgl_rpc_post_func(sys_prompt_show_ctl, 2, 3000, (void *)_("fs_err"));
    return 0;
}

static int rec_gap_err_handler(const char *type, u32 arg)
{
    //提示用户关闭缩时录影
    extern void sys_prompt_show_ctl(int32_t show_time, void *tips);
    lvgl_rpc_post_func(sys_prompt_show_ctl, 2, 3000, (void *)_("gap_err"));
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
        rec_on_handler(msg, 0);
    } else if (strstr(msg, "offREC")) {
        rec_off_handler(msg, 0);
    } else if (strstr(msg, "noCard")) {
        rec_no_card_handler(msg, 0);
    } else if (strstr(msg, "HlightOn")) {
        rec_headlight_on_handler(msg, 0);
    } else if (strstr(msg, "HlightOff")) {
        rec_headlight_off_handler(msg, 0);
    } else if (strstr(msg, "videoRecTime")) {
        rec_video_rec_time_handler(msg, va_arg(argptr, int));
    } else if (!strcmp(msg, "lockREC")) {
        lvgl_module_msg_send_value(GUI_MODEL_VIDEO_REC_MSG_ID_KEY_STATE, true, 0);
    } else if (!strcmp(msg, "unlockREC")) {
        lvgl_module_msg_send_value(GUI_MODEL_VIDEO_REC_MSG_ID_KEY_STATE, false, 0);
    } else if (strstr(msg, "fsErr")) {
        rec_fs_err_handler(msg, 0);
    } else if (strstr(msg, "gapErr")) {
        rec_gap_err_handler(msg, 0);
    } else if (strstr(msg, "sdStatus")) {
        post_msg2sd_icon(msg, va_arg(argptr, int)); //获取第一个int数据
    } else {
        printf("[chili] %s your msg [%s] no callback! \n", __func__, msg, __LINE__);
    }

    va_end(argptr);

#endif

}

extern bool update_date;

static int get_sys_time(struct sys_time *time)
{
    static u8 first_time = 1;
    void *fd = dev_open("rtc", NULL);
    if (fd) {
        dev_ioctl(fd, IOCTL_GET_SYS_TIME, (u32)time);
        if (update_date) {
            time->year = db_select("datey");
            time->month = db_select("datem");
            time->day = db_select("dated");
            time->hour = db_select("dateh");
            time->min = db_select("datemi");
            time->sec = db_select("dates");
            dev_ioctl(fd, IOCTL_SET_SYS_TIME, (u32)time);
            dev_close(fd);
            update_date = false;
        }
        return 0;
    }
    return -EINVAL;
}


//rtc时间模型回调函数，系统时间更新
int gui_model_main_msg_systime_cb(gui_msg_action_t access, gui_msg_data_t *data, gui_msg_data_type_t type)
{

    static struct tm systime_var = { 0 };
    struct sys_time usr_time;
    get_sys_time(&usr_time);
    // printf("[chili] %s  y:%d d:%d \n", __func__, usr_time.year, usr_time.day);
    systime_var.tm_year = usr_time.year - 1900;
    systime_var.tm_mon = usr_time.month - 1;
    systime_var.tm_mday = usr_time.day;
    systime_var.tm_hour = usr_time.hour;
    systime_var.tm_min = usr_time.min;
    systime_var.tm_sec = usr_time.sec;

    if (data == NULL) {
        data = &guider_msg_data;
    }
    if (access == GUI_MSG_ACCESS_SET) {
        systime_var = data->value_time;
    }
    data->value_time = systime_var;
    return 0;
}

//电池电量图标更新
void post_msg2bat_icon(int vbt)
{
#ifdef USE_LVGL_V8_UI_DEMO
    //电量更新
    void *bat_icon = 0;
    //int vbt = get_vbat_level() * 10 / 42;
    //    printf("[chili] %s vbat:%d   \n",  __func__, vbt);
    if (vbt <= 15) {
        bat_icon = RES_BAT_0;
    } else if (vbt > 15 && vbt <= 25) {
        bat_icon = RES_BAT_L;
    } else if (vbt > 25 && vbt <= 50) {
        bat_icon = RES_BAT_HALF;
    } else if (vbt > 50 && vbt <= 75) {
        bat_icon = RES_BAT_H;
    } else if (vbt > 75 && vbt <= 100) {
        bat_icon = RES_BAT_FULL;
    } else { //(sys_power_is_charging())
        bat_icon = RES_CHAR;
    }

    lvgl_module_msg_send_global_ptr(GUI_MODEL_MAIN_MSG_ID_BATTERY, bat_icon, sizeof(bat_icon), 0);
#endif // USE_LVGL_V8_UI_DEMO
}

//SD卡图标
int gui_model_video_rec_msg_sd_icon_cb(gui_msg_action_t access, gui_msg_data_t *data, gui_msg_data_type_t type)
{
    static int32_t sd_icon_var = RES_CARD_OFFLINE;
    if (data == NULL) {
        data = &guider_msg_data;
    }
    if (access == GUI_MSG_ACCESS_GET) {
        if (storage_device_available()) {
            sd_icon_var = RES_CARD_ONLINE;
        } else {
            sd_icon_var = RES_CARD_OFFLINE;
        }
    }
    if (access == GUI_MSG_ACCESS_SET) {
        sd_icon_var = data->value_int;
    }
    data->value_int = sd_icon_var;
    return 0;
}


#endif

/*
* 更新录像预览界面图标
* @arg1 icon:菜单子页面作为更新预览界面图标的依据 比如SUBPAGE_RESOLUTION就是对应预览界面下的分辨率图标
* return void
*/
void video_rec_icon_reshow(int icon)
{
    char *str_buf;
    switch (icon) {
    case SUBPAGE_RESOLUTION:
        printf("-->res value: %d\n", db_select("res"));
        str_buf = lvgl_module_msg_get_ptr(GUI_MODEL_VIDEO_REC_MSG_ID_REC_RESO, 8);
        // sprintf(str_buf, "%dP", db_select("res"));
        switch (db_select("res")) {
        case 1:
            sprintf(str_buf, "720P");
            break;
        case 2:
            sprintf(str_buf, "480P");
            break;
        default:
            sprintf(str_buf, "720P");
            break;
        }

        lvgl_module_msg_send_ptr(str_buf, 0);
        break;
    case SUBPAGE_DOUBLE_REC:

        break;
    case SUBPAGE_CYC_REC:
        printf("--> cyc value: %d\n", db_select("cyc"));
        lvgl_module_msg_send_value(GUI_MODEL_VIDEO_REC_MSG_ID_CYC_STATE, true, 0);
        switch (db_select("cyc")) {
        case 3:
            lvgl_module_msg_send_global_ptr(GUI_MODEL_VIDEO_REC_MSG_ID_CYCREC_ICON, (void *)RES_CYCLIC_VIDEO_3, sizeof(RES_CYCLIC_VIDEO_3), 0);
            break;
        case 5:
            lvgl_module_msg_send_global_ptr(GUI_MODEL_VIDEO_REC_MSG_ID_CYCREC_ICON, (void *)RES_CYCLIC_VIDEO_5, sizeof(RES_CYCLIC_VIDEO_5), 0);
            break;
        case 10:
            lvgl_module_msg_send_global_ptr(GUI_MODEL_VIDEO_REC_MSG_ID_CYCREC_ICON, (void *)RES_CYCLIC_VIDEO_10, sizeof(RES_CYCLIC_VIDEO_10), 0);
            break;
        default:
            lvgl_module_msg_send_value(GUI_MODEL_VIDEO_REC_MSG_ID_CYC_STATE, false, 0);
            break;
        }
        break;
    case SUBPAGE_EXPOSURE:
        printf("--> exp value: %x\n", db_select("exp"));
#if !LV_USE_GUIBUILDER_SIMULATOR
        rec_set_config("exp", db_select("exp"));
#endif
        switch (db_select("exp")) {
        case 0xfffffffd://-3
            lvgl_module_msg_send_global_ptr(GUI_MODEL_VIDEO_REC_MSG_ID_EXP_ICON, (void *)RES_EXP_D3, sizeof(RES_EXP_D3), 0);
            break;
        case 0xfffffffe://-2
            lvgl_module_msg_send_global_ptr(GUI_MODEL_VIDEO_REC_MSG_ID_EXP_ICON, (void *)RES_EXP_D2, sizeof(RES_EXP_D2), 0);
            break;
        case 0xffffffff://-1
            lvgl_module_msg_send_global_ptr(GUI_MODEL_VIDEO_REC_MSG_ID_EXP_ICON, (void *)RES_EXP_D1, sizeof(RES_EXP_D1), 0);
            break;
        case 0:
            lvgl_module_msg_send_global_ptr(GUI_MODEL_VIDEO_REC_MSG_ID_EXP_ICON, (void *)RES_EXP_A0, sizeof(RES_EXP_A0), 0);
            break;
        case 1:
            lvgl_module_msg_send_global_ptr(GUI_MODEL_VIDEO_REC_MSG_ID_EXP_ICON, (void *)RES_EXP_A1, sizeof(RES_EXP_A1), 0);
            break;
        case 2:
            lvgl_module_msg_send_global_ptr(GUI_MODEL_VIDEO_REC_MSG_ID_EXP_ICON, (void *)RES_EXP_A2, sizeof(RES_EXP_A2), 0);
            break;
        case 3:
            lvgl_module_msg_send_global_ptr(GUI_MODEL_VIDEO_REC_MSG_ID_EXP_ICON, (void *)RES_EXP_A3, sizeof(RES_EXP_A3), 0);
            break;
        default:
            lvgl_module_msg_send_global_ptr(GUI_MODEL_VIDEO_REC_MSG_ID_EXP_ICON, (void *)RES_EXP_A0, sizeof(RES_EXP_A0), 0);
            break;
        }

        break;
    case SUBPAGE_GAP:
        printf("--> gap value: %d\n", db_select("gap"));
        switch (db_select("gap")) {
        case 100:
        case 200:
        case 500:
            lvgl_module_msg_send_value(GUI_MODEL_VIDEO_REC_MSG_ID_GAP_STATE, true, 0);
            break;
        default:
            lvgl_module_msg_send_value(GUI_MODEL_VIDEO_REC_MSG_ID_GAP_STATE, false, 0);
            break;
        }
        break;
    case SUBPAGE_HDR:
        printf("-->hdr value: %d\n", db_select("hdr"));
        if (db_select("hdr")) {
            lvgl_module_msg_send_value(GUI_MODEL_VIDEO_REC_MSG_ID_HDR_STATE, true, 0);
        } else {
            lvgl_module_msg_send_value(GUI_MODEL_VIDEO_REC_MSG_ID_HDR_STATE, false, 0);
        }
        break;
    case SUBPAGE_MOTION:
        printf("-->mot value: %d\n", db_select("mot"));
        if (db_select("mot")) {
            lvgl_module_msg_send_value(GUI_MODEL_VIDEO_REC_MSG_ID_MOTION_STATE, true, 0);
        } else {
            lvgl_module_msg_send_value(GUI_MODEL_VIDEO_REC_MSG_ID_MOTION_STATE, false, 0);
        }
        rec_tell_app_exit_menu();
        break;
    case SUBPAGE_GSENSOR:
        printf("-->gra value: %d\n", db_select("gra"));
        lvgl_module_msg_send_value(GUI_MODEL_VIDEO_REC_MSG_ID_GRA_STATE, true, 0);
        switch (db_select("gra")) {
        case 1:
            lvgl_module_msg_send_global_ptr(GUI_MODEL_VIDEO_REC_MSG_ID_GSENSOR_ICON, (void *)RES_I_GRA_L, sizeof(RES_I_GRA_L), 0);
            break;
        case 2:
            lvgl_module_msg_send_global_ptr(GUI_MODEL_VIDEO_REC_MSG_ID_GSENSOR_ICON, (void *)RES_I_GRA_M, sizeof(RES_I_GRA_M), 0);
            break;
        case 3:
            lvgl_module_msg_send_global_ptr(GUI_MODEL_VIDEO_REC_MSG_ID_GSENSOR_ICON, (void *)RES_I_GRA_H, sizeof(RES_I_GRA_H), 0);
            break;
        default:
            lvgl_module_msg_send_value(GUI_MODEL_VIDEO_REC_MSG_ID_GRA_STATE, false, 0);
            break;
        }
        break;
    case SUBPAGE_RECORD:
        printf("-->mic value: %d\n", db_select("mic"));
        if (db_select("mic")) {
            lvgl_module_msg_send_global_ptr(GUI_MODEL_VIDEO_REC_MSG_ID_MIC_ICON, (void *)RES_MIC_ON, sizeof(RES_MIC_ON), 0);
        } else {
            lvgl_module_msg_send_global_ptr(GUI_MODEL_VIDEO_REC_MSG_ID_MIC_ICON, (void *)RES_MIC_OFF, sizeof(RES_MIC_OFF), 0);
        }
        break;
    case SUBPAGE_GUARD:
        printf("-->par value: %d\n", db_select("par"));
        if (db_select("par")) {
            lvgl_module_msg_send_value(GUI_MODEL_VIDEO_REC_MSG_ID_GUARD_STATE, true, 0);
        } else {
            lvgl_module_msg_send_value(GUI_MODEL_VIDEO_REC_MSG_ID_GUARD_STATE, false, 0);
        }
        break;
    case SUBPAGE_CARNUM:
        printf("-->%s()--->num value: %d\n", __func__, db_select("num"));
        if (db_select("num")) {
            // lv_obj_clear_flag(ui_scr->video_rec_lbl_num, LV_OBJ_FLAG_HIDDEN);
            lvgl_module_msg_send_value(GUI_MODEL_VIDEO_REC_MSG_ID_CAR_NUM, true, 0);
        } else {
            // lv_obj_add_flag(ui_scr->video_rec_lbl_num, LV_OBJ_FLAG_HIDDEN);
            lvgl_module_msg_send_value(GUI_MODEL_VIDEO_REC_MSG_ID_CAR_NUM, false, 0);
        }
        break;
    default:
        printf("[chili] %s %d   no match subpage!\n", __func__, __LINE__);
        break;

    }
}
#endif
