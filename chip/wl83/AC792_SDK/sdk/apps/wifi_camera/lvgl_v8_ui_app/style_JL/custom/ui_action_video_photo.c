#include "app_config.h"
#ifdef CONFIG_UI_STYLE_JL_ENABLE
#include "lvgl.h"
#include "custom.h"
#if !LV_USE_GUIBUILDER_SIMULATOR
#include "ui.h"
#include "app_msg.h"
#include "sys_time.h"
#include "system/includes.h"
#include "asm/includes.h"
#include "app_database.h"
#include "action.h"

REGISTER_UI_MODULE_EVENT_HANDLER(GUI_MODEL_VIDEO_PHOTO_MSG_ID_PHOTO_REMAIN)
.onchange = gui_model_video_photo_msg_photo_remain_cb,
};

REGISTER_UI_MODULE_EVENT_HANDLER(GUI_MODEL_VIDEO_PHOTO_MSG_ID_RESOLUTION_ICON)
.onchange = gui_model_video_photo_msg_resolution_icon_cb,
};

REGISTER_UI_MODULE_EVENT_HANDLER(GUI_MODEL_VIDEO_PHOTO_MSG_ID_AWB_ICON)
.onchange = gui_model_video_photo_msg_awb_icon_cb,
};

REGISTER_UI_MODULE_EVENT_HANDLER(GUI_MODEL_VIDEO_PHOTO_MSG_ID_QUALITY_ICON)
.onchange = gui_model_video_photo_msg_quality_icon_cb,
};

REGISTER_UI_MODULE_EVENT_HANDLER(GUI_MODEL_VIDEO_PHOTO_MSG_ID_SHOT_MODE_ICON)
.onchange = gui_model_video_photo_msg_shot_mode_icon_cb,
};

REGISTER_UI_MODULE_EVENT_HANDLER(GUI_MODEL_VIDEO_PHOTO_MSG_ID_HIDE_SHOTS_MODE)
.onchange = gui_model_video_photo_msg_hide_shots_mode_cb,
};

REGISTER_UI_MODULE_EVENT_HANDLER(GUI_MODEL_VIDEO_PHOTO_MSG_ID_SHOW_SHOTS_MODE)
.onchange = gui_model_video_photo_msg_show_shots_mode_cb,
};

REGISTER_UI_MODULE_EVENT_HANDLER(GUI_MODEL_VIDEO_PHOTO_MSG_ID_HIDE_SHOTS)
.onchange = gui_model_video_photo_msg_hide_shots_cb,
};

REGISTER_UI_MODULE_EVENT_HANDLER(GUI_MODEL_VIDEO_PHOTO_MSG_ID_SHOW_SHOTS)
.onchange = gui_model_video_photo_msg_show_shots_cb,
};

REGISTER_UI_MODULE_EVENT_HANDLER(GUI_MODEL_VIDEO_PHOTO_MSG_ID_CAPTURE_TIME)
.onchange = gui_model_video_photo_msg_capture_time_cb,
};

REGISTER_UI_MODULE_EVENT_HANDLER(GUI_MODEL_VIDEO_PHOTO_MSG_ID_HIDE_HANDSHAKE)
.onchange = gui_model_video_photo_msg_hide_handshake_cb,
};

REGISTER_UI_MODULE_EVENT_HANDLER(GUI_MODEL_VIDEO_PHOTO_MSG_ID_SHOW_HANDSHAKE)
.onchange = gui_model_video_photo_msg_show_handshake_cb,
};



#endif
#if !LV_USE_GUIBUILDER_SIMULATOR

void video_photo_post_msg(const char *msg, ...)
{
#ifdef USE_LVGL_V8_UI_DEMO
    va_list argptr;
    printf("[chili] %s %s   \n", __func__, msg);

    va_start(argptr, msg);
    if (strstr(msg, "tphin")) {

    } else if (strstr(msg, "tphout")) {

    } else if (strstr(msg, "captureTime")) {
        post_msg2photo_capture_time(msg, va_arg(argptr, int)); //获取第一个int数据

    } else if (strstr(msg, "remainPhoto")) {
        post_msg2photo_remain(msg, va_arg(argptr, int)); //获取第一个int数据

    } else if (strstr(msg, "swWinicon")) {
        post_msg2sw_winicon(msg, va_arg(argptr, int)); //获取第一个int数据

    } else if (strstr(msg, "batIcon")) {
        post_msg2bat_icon(msg, va_arg(argptr, int)); //获取第一个int数据

    } else if (strstr(msg, "sdStatus")) {
        post_msg2sd_icon(msg, va_arg(argptr, int)); //获取第一个int数据

    }

    va_end(argptr);
#endif

}

//注册页面加载卸载回调
int gui_src_action_video_photo(int action)
{
    struct application *app;

    app = get_current_app();

    printf("[chili] %s %d   \n", __func__, __LINE__);
    lv_ui_video_photo *ui_scr = ui_get_scr_ptr(&guider_ui, GUI_SCREEN_VIDEO_PHOTO);
    if (!ui_scr) {
        return -1;
    }
#if LV_DISP_UI_FB_NUM
    lv_obj_set_style_bg_opa(ui_scr->video_photo, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
#else
    lv_obj_set_style_bg_opa(ui_scr->video_photo, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
#endif

    switch (action) {
    case GUI_SCREEN_ACTION_LOAD:
        if (app) {
            app_mode_go_back();
        }
        app_mode_change_replace(APP_MODE_PHOTO);
        app_send_message(APP_MSG_PHOTO_TAKE_MAIN, 0);
        break;
    case GUI_SCREEN_ACTION_UNLOAD:

        break;
    }
}
REGISTER_UI_SCREEN_ACTION_HANDLER(GUI_SCREEN_VIDEO_PHOTO)
.onchange = gui_src_action_video_photo,
};
#endif
//拍照
int gui_take_photo(void)
{
#if !LV_USE_GUIBUILDER_SIMULATOR
    return app_send_message(APP_MSG_PHOTO_TAKE_CONTROL, 0);
#else
    return 0;
#endif
}

//切换摄像头
int gui_switch_camera(void)
{
#if !LV_USE_GUIBUILDER_SIMULATOR
    return app_send_message(APP_MSG_PHOTO_TAKE_SWITCH_WIN, 0);
#else
    return 0;
#endif
}

//修改摄像头配置
int gui_set_camera_config(char *label, uint32_t value)
{
#if !LV_USE_GUIBUILDER_SIMULATOR
    struct intent *it;
    it = malloc(sizeof(struct intent));
    init_intent(it);
    it->data = label;
    it->exdata = value;
    return app_send_message(APP_MSG_PHOTO_TAKE_SET_CONFIG, 1, it);
#else
    return 0;
#endif
}

//获取摄像头配置
int gui_get_camera_config(char *label)
{
#if !LV_USE_GUIBUILDER_SIMULATOR
    struct intent *it = NULL;
    it = malloc(sizeof(struct intent));
    init_intent(it);
    it->data = label;
    app_send_message(APP_MSG_PHOTO_TAKE_SET_CONFIG, 1, it);
    mdelay(40);
    return it->exdata;
#else
    return 0;
#endif
}

//剩余拍照数量更新
int post_msg2photo_remain(const char *type, uint32_t num)
{
#ifdef USE_LVGL_V8_UI_DEMO
    static char remain[9];
    sprintf(remain, "%d", num);
    lvgl_module_msg_send_global_ptr(GUI_MODEL_VIDEO_PHOTO_MSG_ID_PHOTO_REMAIN, (void *)remain, sizeof(remain), 0);
#endif // USE_LVGL_V8_UI_DEMO
}

//延时拍照时间
static int post_msg2photo_capture_time(const char *type, uint32_t num)
{
#ifdef USE_LVGL_V8_UI_DEMO
    char *time = lvgl_module_msg_get_ptr(GUI_MODEL_VIDEO_PHOTO_MSG_ID_CAPTURE_TIME, 4);
    sprintf(time, "%d", num);
    lvgl_module_msg_send_ptr(time, 0);
#endif // USE_LVGL_V8_UI_DEMO
}


int gui_model_video_photo_msg_photo_remain_cb(gui_msg_action_t access, gui_msg_data_t *data, gui_msg_data_type_t type)
{
    if (access == GUI_MSG_ACCESS_GET) {
        data->value_string = "99999";
    }
    if (access == GUI_MSG_ACCESS_SET) {
    }
    return 0;
}

//分辨率
int gui_model_video_photo_msg_resolution_icon_cb(gui_msg_action_t access, gui_msg_data_t *data, gui_msg_data_type_t type)
{
    static char reso_icon_var[16] = { 0 };

    if (data == NULL) {
        data = &guider_msg_data;
    }
    if (access == GUI_MSG_ACCESS_SET) {
        strcpy(reso_icon_var, (char *)data->value_string);
        if (strcmp(reso_icon_var, "VGA") == 0) {
            gui_set_camera_config("pres", PHOTO_RES_VGA);
        } else if (strcmp(reso_icon_var, "1M") == 0) {
            gui_set_camera_config("pres", PHOTO_RES_1M);
        } else if (strcmp(reso_icon_var, "2M") == 0) {
            gui_set_camera_config("pres", PHOTO_RES_2M);
        } else if (strcmp(reso_icon_var, "3M") == 0) {
            gui_set_camera_config("pres", PHOTO_RES_3M);
        } else if (strcmp(reso_icon_var, "5M") == 0) {
            gui_set_camera_config("pres", PHOTO_RES_5M);
        } else if (strcmp(reso_icon_var, "8M") == 0) {
            gui_set_camera_config("pres", PHOTO_RES_8M);
        } else if (strcmp(reso_icon_var, "10M") == 0) {
            gui_set_camera_config("pres", PHOTO_RES_10M);
        } else if (strcmp(reso_icon_var, "64M") == 0) {
            gui_set_camera_config("pres", PHOTO_RES_64M);
        } else {
        }
    }
    if (access == GUI_MSG_ACCESS_GET) {
        uint32_t res = db_select("pres");
        if (res) {
            sprintf(reso_icon_var, "%dM", res);
        } else {
            strcpy(reso_icon_var, "VGA");
        }
    }
    data->value_string = reso_icon_var;
    return 0;
}

//白平衡
int gui_model_video_photo_msg_awb_icon_cb(gui_msg_action_t access, gui_msg_data_t *data, gui_msg_data_type_t type)
{
    static int32_t awb_icon_var = RES_AWB;
    if (data == NULL) {
        data = &guider_msg_data;
    }
    if (access == GUI_MSG_ACCESS_GET) {
        int camera_wbl = db_select("wbl");
        if (camera_wbl == PHOTO_WBL_SUN) {		//日光
            awb_icon_var = RES_AWB_SUN_LIGHT;
        } else if (camera_wbl == PHOTO_WBL_CLDY) {	//阴天
            awb_icon_var = RES_AWB_SUN_CLOUDY;
        } else if (camera_wbl == PHOTO_WBL_FLUL) {	//荧光灯
            awb_icon_var = RES_AWB_FLUORESCENT_LAMP;
        } else if (camera_wbl == PHOTO_WBL_TSL) {	//钨丝灯
            awb_icon_var = RES_AWB_OSRAM_LAMP;
        } else if (camera_wbl == PHOTO_WBL_AUTO) {	//自动
            awb_icon_var = RES_AWB;
        }
    }
    if (access == GUI_MSG_ACCESS_SET) {
        awb_icon_var = data->value_int;
        if (awb_icon_var == RES_AWB_SUN_LIGHT) {					//日光
            gui_set_camera_config("wbl", PHOTO_WBL_SUN);
        } else if (awb_icon_var == RES_AWB_SUN_CLOUDY) {			//阴天
            gui_set_camera_config("wbl", PHOTO_WBL_CLDY);
        } else if (awb_icon_var == RES_AWB_FLUORESCENT_LAMP) {		//荧光灯
            gui_set_camera_config("wbl", PHOTO_WBL_FLUL);
        } else if (awb_icon_var == RES_AWB_OSRAM_LAMP) {		//钨丝灯
            gui_set_camera_config("wbl", PHOTO_WBL_TSL);
        } else if (awb_icon_var == RES_AWB) {					//自动
            gui_set_camera_config("wbl", PHOTO_WBL_AUTO);
        }
    }
    data->value_int = awb_icon_var;
    return 0;
}


//照片质量
int gui_model_video_photo_msg_quality_icon_cb(gui_msg_action_t access, gui_msg_data_t *data, gui_msg_data_type_t type)
{
    static int32_t quality_icon_var = RES_HIGH;
    if (data == NULL) {
        data = &guider_msg_data;
    }
    if (access == GUI_MSG_ACCESS_GET) {
        int camera_qua = db_select("qua");
        if (camera_qua == PHOTO_QUA_HI) {					//高
            quality_icon_var = RES_HIGH;
        } else if (camera_qua == PHOTO_QUA_MD) {				//中
            quality_icon_var = RES_MIDDLE;
        } else if (camera_qua == PHOTO_QUA_LO) {				//低
            quality_icon_var = RES_LOW;
        }
    }
    if (access == GUI_MSG_ACCESS_SET) {
        quality_icon_var = data->value_int;
        if (quality_icon_var == RES_HIGH) {					//高
            gui_set_camera_config("qua", PHOTO_QUA_HI);
        } else if (quality_icon_var == RES_MIDDLE) {			//中
            gui_set_camera_config("qua", PHOTO_QUA_MD);
        } else if (quality_icon_var == RES_LOW) {		//低
            gui_set_camera_config("qua", PHOTO_QUA_LO);
        }
    }
    data->value_int = quality_icon_var;
    return 0;
}


//延时拍照 2、5、10
int gui_model_video_photo_msg_shot_mode_icon_cb(gui_msg_action_t access, gui_msg_data_t *data, gui_msg_data_type_t type)
{
    static int32_t shot_mode_icon_var = RES_TIMING_PHOTO_2;
    if (data == NULL) {
        data = &guider_msg_data;
    }
    if (access == GUI_MSG_ACCESS_GET) {
        int camera_delay = db_select("phm");
        if (camera_delay == 2) {						//2s
            shot_mode_icon_var = RES_TIMING_PHOTO_2;
        } else if (camera_delay == 5) {				//5s
            shot_mode_icon_var = RES_TIMING_PHOTO_5;
        } else if (camera_delay == 10) {				//10s
            shot_mode_icon_var = RES_TIMING_PHOTO_10;
        } else {										//0s

        }
    }
    if (access == GUI_MSG_ACCESS_SET) {
        shot_mode_icon_var = data->value_int;
        if (shot_mode_icon_var == RES_TIMING_PHOTO_2) {					//2s
            gui_set_camera_config("phm", 2);
        } else if (shot_mode_icon_var == RES_TIMING_PHOTO_5) {			//5s
            gui_set_camera_config("phm", 5);
        } else if (shot_mode_icon_var == RES_TIMING_PHOTO_10) {		//10s
            gui_set_camera_config("phm", 10);
        } else {

        }
    }
    data->value_int = shot_mode_icon_var;
    return 0;
}


//无延时
int gui_model_video_photo_msg_hide_shots_mode_cb(gui_msg_action_t access, gui_msg_data_t *data, gui_msg_data_type_t type)
{
    static lv_obj_flag_t hide_shots_var = LV_OBJ_FLAG_HIDDEN;
    if (data == NULL) {
        data = &guider_msg_data;
    }

    int delay = db_select("phm");
    if (delay) {
        hide_shots_var = LV_OBJ_FLAG_CHECKABLE;
    }

    if (access == GUI_MSG_ACCESS_SET) {
        gui_set_camera_config("phm", 0);
        hide_shots_var = data->value_int;
    }
    data->value_int = hide_shots_var;
    return 0;
}


//有延时
int gui_model_video_photo_msg_show_shots_mode_cb(gui_msg_action_t access, gui_msg_data_t *data, gui_msg_data_type_t type)
{
    static lv_obj_flag_t hide_shots_var = LV_OBJ_FLAG_HIDDEN;
    if (data == NULL) {
        data = &guider_msg_data;
    }

    int delay = db_select("phm");
    if (!delay) {
        hide_shots_var = LV_OBJ_FLAG_CHECKABLE;
    }

    if (access == GUI_MSG_ACCESS_SET) {
        hide_shots_var = data->value_int;
    }
    data->value_int = hide_shots_var;
    return 0;
}


//无连拍
int gui_model_video_photo_msg_hide_shots_cb(gui_msg_action_t access, gui_msg_data_t *data, gui_msg_data_type_t type)
{
    static lv_obj_flag_t show_shots_var = LV_OBJ_FLAG_HIDDEN;
    if (data == NULL) {
        data = &guider_msg_data;
    }

    int cyt = db_select("cyt");
    if (cyt) {
        show_shots_var = LV_OBJ_FLAG_CHECKABLE;
    }

    if (access == GUI_MSG_ACCESS_SET) {
        gui_set_camera_config("cyt", 0);
        show_shots_var = data->value_int;
    }
    data->value_int = show_shots_var;
    return 0;

}


//有连拍
int gui_model_video_photo_msg_show_shots_cb(gui_msg_action_t access, gui_msg_data_t *data, gui_msg_data_type_t type)
{
    static lv_obj_flag_t show_shots_var = LV_OBJ_FLAG_HIDDEN;
    if (data == NULL) {
        data = &guider_msg_data;
    }

    int cyt = db_select("cyt");
    if (!cyt) {
        show_shots_var = LV_OBJ_FLAG_CHECKABLE;
    }

    if (access == GUI_MSG_ACCESS_SET) {
        gui_set_camera_config("cyt", 1);
        show_shots_var = data->value_int;
    }
    data->value_int = show_shots_var;
    return 0;
}

int gui_model_video_photo_msg_hide_handshake_cb(gui_msg_action_t access, gui_msg_data_t *data, gui_msg_data_type_t type)
{
    int sok;
    if (access == GUI_MSG_ACCESS_GET) {
        sok = db_select("sok");
        if (!sok) {
            data->value_int = LV_OBJ_FLAG_HIDDEN;
        } else {
            data->value_int = LV_OBJ_FLAG_CHECKABLE;
        }
    }
    return 0;
}

int gui_model_video_photo_msg_show_handshake_cb(gui_msg_action_t access, gui_msg_data_t *data, gui_msg_data_type_t type)
{
    int sok;
    if (access == GUI_MSG_ACCESS_GET) {
        sok = db_select("sok");
        if (!sok) {
            data->value_int = LV_OBJ_FLAG_CHECKABLE;
        } else {
            data->value_int = LV_OBJ_FLAG_HIDDEN;
        }
    }
    return 0;
}


//延时拍照倒计时
int gui_model_video_photo_msg_capture_time_cb(gui_msg_action_t access, gui_msg_data_t *data, gui_msg_data_type_t type)
{
    char *str = data->value_string;
    lv_ui_video_photo *ui_scr = ui_get_scr_ptr(&guider_ui, GUI_SCREEN_VIDEO_PHOTO);
    if (!ui_scr) {
        return -1;
    }
    if (access == GUI_MSG_ACCESS_SET) {
        int time = atoi(str);
        if (time) {
            lv_obj_clear_flag(ui_scr->video_photo_show_capture_time, LV_OBJ_FLAG_HIDDEN);
        } else {
            lv_obj_add_flag(ui_scr->video_photo_show_capture_time, LV_OBJ_FLAG_HIDDEN);
        }
    }
    if (access == GUI_MSG_ACCESS_GET) {
        data->value_string = "0";
        lv_obj_add_flag(ui_scr->video_photo_show_capture_time, LV_OBJ_FLAG_HIDDEN);
    }

    return 0;
}




#endif
