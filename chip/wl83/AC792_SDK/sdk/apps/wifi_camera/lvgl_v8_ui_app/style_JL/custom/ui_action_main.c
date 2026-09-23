#include "app_config.h"
#ifdef CONFIG_UI_STYLE_JL_ENABLE
/*********************
 *      INCLUDES
 *********************/
#include "lvgl.h"
#include "custom.h"

lv_timer_t *prompt_timer = 0;
static char prompt_str[64] = { 0 };
extern bool update_date;

/*
*   顶层页面显示定时器回调--倒计时隐藏系统提示界面
*
*/
static void sys_prompt_timer_cb(lv_timer_t *timer)
{
    printf("[chili]: %s %d\n", __func__, __LINE__);
    lv_ui_sys_prompt *ui_scr = ui_get_scr_ptr(&guider_ui, GUI_SCREEN_SYS_PROMPT);
    if (ui_scr && ui_scr->sys_prompt_del == false && lv_obj_is_valid(ui_scr->sys_prompt)) {
        lv_obj_add_flag(ui_scr->sys_prompt, LV_OBJ_FLAG_HIDDEN);
        unload_scr_sys_prompt(&guider_ui);
        /*lv_obj_clean(ui_scr->sys_prompt);*/
        gui_msg_init_ui();
        gui_msg_init_events();
        gui_timelines_delete();
    }
    if (prompt_timer) {//删除定时器
        lv_timer_del(prompt_timer);
        prompt_timer = NULL;

    }

}


/*
*
* 顶层系统警告页面显示隐藏控制---后面用bool类型的模型回调实现
* @show_time 填0立马隐藏，提示窗提示时间，单位ms
* @tips 提示语
*/
void sys_prompt_show_ctl(int32_t show_time, void *tips)
{
    printf("[chili]: %s show_time %d\n", __func__, show_time);
    if (show_time) {
        //倒计时隐藏
        strcpy(prompt_str, tips);
        if (prompt_timer == NULL) {
            prompt_timer = lv_timer_create(sys_prompt_timer_cb, show_time, 0);
        } else {
            //需要先删除上一个定时器
            lv_timer_del(prompt_timer);
            prompt_timer = NULL;
            prompt_timer = lv_timer_create(sys_prompt_timer_cb, show_time, 0);
        }
        lv_ui_sys_prompt *ui_scr = ui_get_scr_ptr(&guider_ui, GUI_SCREEN_SYS_PROMPT);
        if (ui_scr && ui_scr->sys_prompt_del == false && lv_obj_is_valid(ui_scr->sys_prompt)) {
            //lv_obj_clear_flag(ui_scr->sys_prompt, LV_OBJ_FLAG_HIDDEN);
        } else {
            setup_scr_sys_prompt(&guider_ui);
            ui_scr = ui_get_scr_ptr(&guider_ui, GUI_SCREEN_SYS_PROMPT);
            lv_obj_clear_flag(ui_scr->sys_prompt, LV_OBJ_FLAG_HIDDEN);
            gui_model_main_msg_init_ui();
            gui_model_main_msg_init_events();


        }
        lvgl_module_msg_send_global_ptr(GUI_MODEL_MAIN_MSG_ID_SYS_PROMPT, tips, strlen(tips), 0);
    } else {
        lv_ui_sys_prompt *ui_scr = ui_get_scr_ptr(&guider_ui, GUI_SCREEN_SYS_PROMPT);
        if (!ui_scr) {
            return;
        }
        if (ui_scr->sys_prompt_del == false && lv_obj_is_valid(ui_scr->sys_prompt)) {
            lv_obj_add_flag(ui_scr->sys_prompt, LV_OBJ_FLAG_HIDDEN);
            unload_scr_sys_prompt(&guider_ui);
            /*lv_obj_clean(ui_scr->sys_prompt);*/
            gui_msg_init_ui();
            gui_msg_init_events();
            delete_gui_timelines();
        }

        if (prompt_timer) {//删除定时器
            lv_timer_del(prompt_timer);
            prompt_timer = NULL;

        }

    }
}
/*
* 系统警告提示框首次GET更新提示语
*
*/
int gui_model_main_msg_sys_prompt_cb(gui_msg_action_t access, gui_msg_data_t *data, gui_msg_data_type_t type)
{
    if (access == GUI_MSG_ACCESS_SET) {
        strcpy(prompt_str, data->value_string);
    }
    data->value_string = prompt_str;
    return 0;
}

#if !LV_USE_GUIBUILDER_SIMULATOR
#include "ui.h"
#include "sys_time.h"
#include "system/includes.h"
#include "asm/includes.h"
#include "syscfg/syscfg_id.h"
#include "action.h"

/*********************
 *      DEFINES
 *********************/

/**********************
 *  STATIC FUNCTION
 **********************/
//注册页面加载卸载回调
int gui_src_action_home(int action)
{
    switch (action) {
    case GUI_SCREEN_ACTION_LOAD:
        app_mode_go_back();
        struct sys_time usr_time;
        get_sys_time(&usr_time);
        u8 weekday = caculate_weekday_by_time(&usr_time);
        switch (weekday) {
        case 1:
            lvgl_module_msg_send_string(GUI_MODEL_MAIN_MSG_ID_WEEKDAY, _("Mon"), 0);
            break;
        case 2:
            lvgl_module_msg_send_string(GUI_MODEL_MAIN_MSG_ID_WEEKDAY, _("Tue"), 0);
            break;
        case 3:
            lvgl_module_msg_send_string(GUI_MODEL_MAIN_MSG_ID_WEEKDAY, _("Wed"), 0);
            break;
        case 4:
            lvgl_module_msg_send_string(GUI_MODEL_MAIN_MSG_ID_WEEKDAY, _("Thu"), 0);
            break;
        case 5:
            lvgl_module_msg_send_string(GUI_MODEL_MAIN_MSG_ID_WEEKDAY, _("Fir"), 0);
            break;
        case 6:
            lvgl_module_msg_send_string(GUI_MODEL_MAIN_MSG_ID_WEEKDAY, _("Sat"), 0);
            break;
        case 7:
            lvgl_module_msg_send_string(GUI_MODEL_MAIN_MSG_ID_WEEKDAY, _("Sun"), 0);
            break;
        }

        break;
    case GUI_SCREEN_ACTION_UNLOAD:

        break;
    }

}

REGISTER_UI_SCREEN_ACTION_HANDLER(GUI_SCREEN_HOME_PAGE)
.onchange = gui_src_action_home,
};


int get_sys_time(struct sys_time *time)
{
    void *fd = dev_open("rtc", NULL);
    if (fd) {
        dev_ioctl(fd, IOCTL_GET_SYS_TIME, (u32)time);
        if (update_date) {
            time->year = db_select("datey");
            time->month = db_select("datem");
            time->day = db_select("dated");
            time->hour = db_select("dateh");
            time->min = db_select("datemi");
            dev_ioctl(fd, IOCTL_SET_SYS_TIME, (u32)time);
            dev_close(fd);
            update_date = false;
        }
        return 0;
    }
    return -EINVAL;
}

/**********************
 *  PUBILC FUNCTION
 **********************/
extern u8 lvgl_ui_is_suspended(void);
u8 lvgl_is_prepare(void)
{
    if (!lvgl_ui_is_suspended()) {
        return 1;
    }
    return 0;
}
void sys_update_post(void)
{
#if 0
    if (fs_update_set_file_path(CONFIG_UPGRADE_PATH) == true) {
        printf("[chili]: %s %d\n", __func__, __LINE__);
        extern void sys_prompt_show_ctl(int32_t show_time, void *tips);
        lvgl_rpc_post_func(sys_prompt_show_ctl, 2, 8000, (void *)_("sd_update"));
    }
#endif
}

void sys_update_cancel(void)
{
    extern void sys_prompt_show_ctl(int32_t show_time, void *tips);
    lvgl_rpc_post_func(sys_prompt_show_ctl, 2, 0, (void *)_("sd_update"));
}

void post_msg2sd_delbtn(int online)
{
#ifdef USE_LVGL_V8_UI_DEMO
    printf("[chili] %s online %d   \n", __func__, online);
    if (online) {
        lvgl_module_msg_send_value(GUI_MODEL_MAIN_MSG_ID_SHOW_DEL_BTN, LV_OBJ_FLAG_HIDDEN, 0);
    } else {
        lvgl_module_msg_send_value(GUI_MODEL_MAIN_MSG_ID_HIDE_DEL_BTN, LV_OBJ_FLAG_HIDDEN, 0);
    }
#endif // USE_LVGL_V8_UI_DEMO
}
void post_msg2sd_homebtn(int online)
{
#ifdef USE_LVGL_V8_UI_DEMO
    printf("[chili] %s online %d   \n", __func__, online);
    if (online) {
        lvgl_module_msg_send_value(GUI_MODEL_MAIN_MSG_ID_SHOW_HOME_BTN, LV_OBJ_FLAG_HIDDEN, 0);
    } else {
        lvgl_module_msg_send_value(GUI_MODEL_MAIN_MSG_ID_HIDE_HOME_BTN, LV_OBJ_FLAG_HIDDEN, 0);
    }
#endif // USE_LVGL_V8_UI_DEMO
}
//sd卡状态图标更新
void post_msg2sd_icon(const char *type, u32 online)
{
#ifdef USE_LVGL_V8_UI_DEMO
    if (online) {
        lvgl_module_msg_send_global_ptr(GUI_MODEL_MAIN_MSG_ID_SD_ICON, (void *)RES_SD, sizeof(RES_SD), 0);
    } else {
        lvgl_module_msg_send_global_ptr(GUI_MODEL_MAIN_MSG_ID_SD_ICON, (void *)RES_SD_CLOSE, sizeof(RES_SD_CLOSE), 0);
    }
#endif // USE_LVGL_V8_UI_DEMO
}

//视窗切换图标显示隐藏
void post_msg2sw_winicon(const char *type, u32 online)
{
#ifdef USE_LVGL_V8_UI_DEMO
    printf("[chili] %s online %d   \n", __func__, online);
    if (online) {
        lvgl_module_msg_send_global_ptr(GUI_MODEL_MAIN_MSG_ID_SHOW_WIN_SWITCH, (void *)LV_OBJ_FLAG_HIDDEN, 1, 0);
    } else {
        lvgl_module_msg_send_global_ptr(GUI_MODEL_MAIN_MSG_ID_HIDE_WIN_SWITCH, (void *)LV_OBJ_FLAG_HIDDEN, 1, 0);
    }
#endif // USE_LVGL_V8_UI_DEMO
}
//电池电量图标更新
void post_msg2bat_icon(const char *type, u32 vbt)
{
#ifdef USE_LVGL_V8_UI_DEMO
    //电量更新
    void *bat_icon = 0;
    //int vbt = get_vbat_level() * 10 / 42;
    //    printf("[chili] %s vbat:%d   \n",  __func__, vbt);
    if (vbt <= 15) {
        bat_icon = RES_0;
    } else if (vbt > 15 && vbt <= 25) {
        bat_icon = RES_1;
    } else if (vbt > 25 && vbt <= 50) {
        bat_icon = RES_2;
    } else if (vbt > 50 && vbt <= 75) {
        bat_icon = RES_3;
    } else if (vbt > 75 && vbt <= 100) {
        bat_icon = RES_FULL;
    } else { //(sys_power_is_charging())
        bat_icon = RES_CHARGING;
    }

    lvgl_module_msg_send_global_ptr(GUI_MODEL_MAIN_MSG_ID_BATTERY, bat_icon, sizeof(bat_icon), 0);
#endif // USE_LVGL_V8_UI_DEMO
}

//系统时间更新
int gui_model_main_msg_systime_cb(gui_msg_action_t access, gui_msg_data_t *data, gui_msg_data_type_t type)
{

    static struct tm systime_var = { 0 };
    struct sys_time usr_time;
    get_sys_time(&usr_time);
    /*printf("[chili] %s  y:%d d:%d hour:%d min%d\n", __func__, usr_time.year, usr_time.day, usr_time.hour, usr_time.min);*/
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



//隐藏摄像头切换图标
int gui_model_main_msg_hide_win_switch_cb(gui_msg_action_t access, gui_msg_data_t *data, gui_msg_data_type_t type)
{
    static lv_obj_flag_t hide_win_switch_var = LV_OBJ_FLAG_HIDDEN;
    if (data == NULL) {
        data = &guider_msg_data;
    }
    printf("[chili] %s dev_online(uvc) %d   \n", __func__, dev_online("uvc"));
    /* if (dev_online("uvc") || dev_online("video1.*")) { */
    /* hide_win_switch_var = LV_OBJ_FLAG_CHECKABLE; */
    /* printf("%d, %s", __LINE__, __func__); */
    /* } */
    if (access == GUI_MSG_ACCESS_SET) {
        hide_win_switch_var = data->value_int;
    }
    data->value_int = hide_win_switch_var;
    return 0;
}

//显示摄像头切换图标
int gui_model_main_msg_show_win_switch_cb(gui_msg_action_t access, gui_msg_data_t *data, gui_msg_data_type_t type)
{
    static lv_obj_flag_t show_win_switch_var = LV_OBJ_FLAG_HIDDEN;
    if (data == NULL) {
        data = &guider_msg_data;
    }
    /* if (!dev_online("uvc") && !dev_online("video1.*")) { */
    /* show_win_switch_var = LV_OBJ_FLAG_CHECKABLE; */
    /* } */
    if (access == GUI_MSG_ACCESS_SET) {
        show_win_switch_var = data->value_int;
    }
    data->value_int = show_win_switch_var;
    return 0;
}


//SD卡图标
int gui_model_main_msg_sd_icon_cb(gui_msg_action_t access, gui_msg_data_t *data, gui_msg_data_type_t type)
{
    static int32_t sd_icon_var = RES_SD_CLOSE;
    if (data == NULL) {
        data = &guider_msg_data;
    }
    if (access == GUI_MSG_ACCESS_GET) {
        if (storage_device_available()) {
            sd_icon_var = RES_SD;
        } else {
            sd_icon_var = RES_SD_CLOSE;
        }
    }
    if (access == GUI_MSG_ACCESS_SET) {
        sd_icon_var = data->value_int;
    }
    data->value_int = sd_icon_var;
    return 0;
}

#endif

#endif
