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

void enter_video_photo_callback(void *priv, int err)
{
    printf("--->%s()----->%d\n", __func__, __LINE__);
    // key_event_enable();
}

//注册页面加载卸载回调
int gui_src_action_video_photo(int action)
{
    struct intent it;
    struct application *app;
    init_intent(&it);

    // printf("--->%s()----->%d, action: %d\n", __func__, __LINE__, action);

    switch (action) {
    case GUI_SCREEN_ACTION_LOAD: {
        lv_ui_video_photo *ui_scr = ui_get_scr_ptr(&guider_ui, GUI_SCREEN_VIDEO_PHOTO);
        if (!ui_scr) {
            return -1;
        }
#if LV_DISP_UI_FB_NUM
        lv_obj_set_style_bg_opa(ui_scr->video_photo, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
#else
        lv_obj_set_style_bg_opa(ui_scr->video_photo, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
#endif
        // printf("--->%s()----->%d\n", __func__, __LINE__);
        key_event_disable();
#if 0
        app = get_current_app();
        if (app) {
            app_mode_go_back();
        }
#endif
        app_mode_change_replace(APP_MODE_PHOTO);
        app_send_message(APP_MSG_PHOTO_TAKE_MAIN, 0);
        key_event_enable();
    }
    break;
    case GUI_SCREEN_ACTION_UNLOAD:

        break;
    }
}
REGISTER_UI_SCREEN_ACTION_HANDLER(GUI_SCREEN_VIDEO_PHOTO)
.onchange = gui_src_action_video_photo,
};



/*注册页面按键响应函数回调*/
int video_photo_key_handler(struct key_event *key)
{
    printf("---->%s()----->key action: %d, value: %d\n", __func__, key->action, key->value);
    switch (key->action) {
    case KEY_EVENT_CLICK:
        switch (key->value) {
        case KEY_OK:
        case KEY_DOWN:
        case KEY_UP:
            lv_ui_video_photo *ui_scr = ui_get_scr_ptr(&guider_ui, GUI_SCREEN_VIDEO_PHOTO);
            if (!ui_scr) {
                return -1;
            }
            if (!lv_obj_has_flag(ui_scr->video_photo_view_menu_b, LV_OBJ_FLAG_HIDDEN)) {  //进入设置菜单时, 按键消息不传到792 app_core
                return 0;
            } else {
                return 1;
            }
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
REGISTER_UI_KEY_EVENT_HANDLER(GUI_SCREEN_VIDEO_PHOTO)
.key_onchange = video_photo_key_handler,
};


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

static void take_photo_in(int arg)
{
    lv_ui_video_photo *ui_scr = ui_get_scr_ptr(&guider_ui, GUI_SCREEN_VIDEO_PHOTO);
    if (!ui_scr) {
        return;
    }
    lv_obj_add_flag(ui_scr->video_photo_img_photo_icon, LV_OBJ_FLAG_HIDDEN);
    lv_obj_clear_flag(ui_scr->video_photo_img_taking_photo, LV_OBJ_FLAG_HIDDEN);
}

static void take_photo_out(int arg)
{
    lv_ui_video_photo *ui_scr = ui_get_scr_ptr(&guider_ui, GUI_SCREEN_VIDEO_PHOTO);
    if (!ui_scr) {
        return;
    }
    lv_obj_add_flag(ui_scr->video_photo_img_taking_photo, LV_OBJ_FLAG_HIDDEN);
    lv_obj_clear_flag(ui_scr->video_photo_img_photo_icon, LV_OBJ_FLAG_HIDDEN);
}

static int tph_take_photo_in_handler(void)
{
#if !LV_USE_GUIBUILDER_SIMULATOR
    lvgl_rpc_post_func(take_photo_in, 1, 0);
#endif
}

static int tph_take_photo_out_handler(void)
{
#if !LV_USE_GUIBUILDER_SIMULATOR
    lvgl_rpc_post_func(take_photo_out, 1, 0);
#endif
}

void video_photo_post_msg(const char *msg, ...)
{
#ifdef USE_LVGL_V8_UI_DEMO
    va_list argptr;
    printf("[chili] %s %s   \n", __func__, msg);

    va_start(argptr, msg);
    if (strstr(msg, "tphin")) {
        tph_take_photo_in_handler();
    } else if (strstr(msg, "tphout")) {
        tph_take_photo_out_handler();
    }

    va_end(argptr);
#endif
}


REGISTER_UI_MODULE_EVENT_HANDLER(GUI_MODEL_VIDEO_PHOTO_MSG_ID_PEXP_ICON)
.onchange = gui_model_video_photo_msg_pexp_icon_cb,
};

REGISTER_UI_MODULE_EVENT_HANDLER(GUI_MODEL_VIDEO_PHOTO_MSG_ID_AWB_ICON)
.onchange = gui_model_video_photo_msg_awb_icon_cb,
};

REGISTER_UI_MODULE_EVENT_HANDLER(GUI_MODEL_VIDEO_PHOTO_MSG_ID_ISO_ICON)
.onchange = gui_model_video_photo_msg_iso_icon_cb,
};

REGISTER_UI_MODULE_EVENT_HANDLER(GUI_MODEL_VIDEO_PHOTO_MSG_ID_QUALITY_ICON)
.onchange = gui_model_video_photo_msg_quality_icon_cb,
};

REGISTER_UI_MODULE_EVENT_HANDLER(GUI_MODEL_VIDEO_PHOTO_MSG_ID_DELAY_SATE)
.onchange = gui_model_video_photo_msg_delay_sate_cb,
};

REGISTER_UI_MODULE_EVENT_HANDLER(GUI_MODEL_VIDEO_PHOTO_MSG_ID_DELAY_ICON)
.onchange = gui_model_video_photo_msg_delay_icon_cb,
};

REGISTER_UI_MODULE_EVENT_HANDLER(GUI_MODEL_VIDEO_PHOTO_MSG_ID_HANDSHAKE_ICON)
.onchange = gui_model_video_photo_msg_handshake_icon_cb,
};

REGISTER_UI_MODULE_EVENT_HANDLER(GUI_MODEL_VIDEO_PHOTO_MSG_ID_SHOTS_ICON)
.onchange = gui_model_video_photo_msg_shots_icon_cb,
};

REGISTER_UI_MODULE_EVENT_HANDLER(GUI_MODEL_VIDEO_PHOTO_MSG_ID_PHOTO_RESO)
.onchange = gui_model_video_photo_msg_photo_reso_cb,
};

REGISTER_UI_MODULE_EVENT_HANDLER(GUI_MODEL_VIDEO_PHOTO_MSG_ID_PHOTO_REMAIN)
.onchange = gui_model_video_photo_msg_photo_remain_cb,
};




int gui_model_video_photo_msg_pexp_icon_cb(gui_msg_action_t access, gui_msg_data_t *data, gui_msg_data_type_t type)
{
    static int32_t pexp_icon_var = RES_EXP_A0;
    if (data == NULL) {
        data = &guider_msg_data;
    }

    int exp = db_select("pexp");
    printf("----->%s()----->pexp: %d\n", __func__, exp);
    switch (exp) {
    case 0xfffffffd://-3
        pexp_icon_var = RES_EXP_D3;
        break;
    case 0xfffffffe://-2
        pexp_icon_var = RES_EXP_D2;
        break;
    case 0xffffffff://-1
        pexp_icon_var = RES_EXP_D1;
        break;
    case 0:
        pexp_icon_var = RES_EXP_A0;
        break;
    case 1:
        pexp_icon_var = RES_EXP_A1;
        break;
    case 2:
        pexp_icon_var = RES_EXP_A2;
        break;
    case 3:
        pexp_icon_var = RES_EXP_A3;
        break;
    default:
        pexp_icon_var = RES_EXP_A0;
        break;
    }

    if (access == GUI_MSG_ACCESS_SET) {
        pexp_icon_var = data->value_int;
    }
    data->value_int = pexp_icon_var;
    return 0;
}

int gui_model_video_photo_msg_awb_icon_cb(gui_msg_action_t access, gui_msg_data_t *data, gui_msg_data_type_t type)
{
    static int32_t awb_icon_var = RES_AWB_AUTO;
    if (data == NULL) {
        data = &guider_msg_data;
    }

    if (access == GUI_MSG_ACCESS_GET) {
        int camera_wbl = db_select("wbl");
        if (camera_wbl == PHOTO_WBL_SUN) {		//日光
            awb_icon_var = RES_AWB_FINE;
        } else if (camera_wbl == PHOTO_WBL_CLDY) {	//阴天
            awb_icon_var = RES_AWB_CLOUDY;
        } else if (camera_wbl == PHOTO_WBL_FLUL) {	//荧光灯
            awb_icon_var = RES_AWB_FLUORESCENT_LAMP_1;
        } else if (camera_wbl == PHOTO_WBL_TSL) {	//钨丝灯
            awb_icon_var = RES_AWB_TUNGSTEN_LAMP;
        } else if (camera_wbl == PHOTO_WBL_AUTO) {	//自动
            awb_icon_var = RES_AWB_AUTO;
        }
    }

    if (access == GUI_MSG_ACCESS_SET) {
        awb_icon_var = data->value_int;
        if (awb_icon_var == RES_AWB_FINE) {					//日光
            gui_set_camera_config("wbl", PHOTO_WBL_SUN);
        } else if (awb_icon_var == RES_AWB_CLOUDY) {			//阴天
            gui_set_camera_config("wbl", PHOTO_WBL_CLDY);
        } else if (awb_icon_var == RES_AWB_FLUORESCENT_LAMP_1) {		//荧光灯
            gui_set_camera_config("wbl", PHOTO_WBL_FLUL);
        } else if (awb_icon_var == RES_AWB_TUNGSTEN_LAMP) {		//钨丝灯
            gui_set_camera_config("wbl", PHOTO_WBL_TSL);
        } else if (awb_icon_var == RES_AWB_AUTO) {					//自动
            gui_set_camera_config("wbl", PHOTO_WBL_AUTO);
        }
    }
    data->value_int = awb_icon_var;
    return 0;
}

int gui_model_video_photo_msg_iso_icon_cb(gui_msg_action_t access, gui_msg_data_t *data, gui_msg_data_type_t type)
{
    static int32_t iso_icon_var = RES_ISO_AUTO;
    if (data == NULL) {
        data = &guider_msg_data;
    }

    // if (access == GUI_MSG_ACCESS_GET) {
    switch (db_select("iso")) {
    case 100:
        iso_icon_var = RES_ISO_1;
        break;
    case 200:
        iso_icon_var = RES_ISO_2;
        break;
    case 400:
        iso_icon_var = RES_ISO_4;
        break;
    default:
        iso_icon_var = RES_ISO_AUTO;
        break;
    }
    // }

    if (access == GUI_MSG_ACCESS_SET) {
        iso_icon_var = data->value_int;
    }
    data->value_int = iso_icon_var;
    return 0;
}

int gui_model_video_photo_msg_quality_icon_cb(gui_msg_action_t access, gui_msg_data_t *data, gui_msg_data_type_t type)
{
    static int32_t quality_icon_var = RES_Q3;
    if (data == NULL) {
        data = &guider_msg_data;
    }

    switch (db_select("qua")) {
    case 0:
        quality_icon_var = RES_Q1;
        break;
    case 1:
        quality_icon_var = RES_Q2;
        break;
    case 2:
        quality_icon_var = RES_Q3;
        break;
    default:
        quality_icon_var = RES_Q3;
        break;
    }

    if (access == GUI_MSG_ACCESS_SET) {
        quality_icon_var = data->value_int;
    }
    data->value_int = quality_icon_var;
    return 0;
}

int gui_model_video_photo_msg_delay_sate_cb(gui_msg_action_t access, gui_msg_data_t *data, gui_msg_data_type_t type)
{
    static bool delay_sate_var = false;
    if (data == NULL) {
        data = &guider_msg_data;
    }

    if (db_select("phm")) {
        delay_sate_var = true;
    }

    if (access == GUI_MSG_ACCESS_SET) {
        delay_sate_var = data->value_int;
    }
    data->value_int = delay_sate_var;
    return 0;
}

int gui_model_video_photo_msg_delay_icon_cb(gui_msg_action_t access, gui_msg_data_t *data, gui_msg_data_type_t type)
{
    static int32_t delay_icon_var = RES_DL2;
    if (data == NULL) {
        data = &guider_msg_data;
    }

    switch (db_select("phm")) {
    case 2:
        delay_icon_var = RES_DL2;
        break;
    case 5:
        delay_icon_var = RES_DL5;
        break;
    case 10:
        delay_icon_var = RES_DL10;
        break;
    default:
        delay_icon_var = RES_DL2;
        break;

    }

    if (access == GUI_MSG_ACCESS_SET) {
        delay_icon_var = data->value_int;
    }
    data->value_int = delay_icon_var;
    return 0;
}

int gui_model_video_photo_msg_handshake_icon_cb(gui_msg_action_t access, gui_msg_data_t *data, gui_msg_data_type_t type)
{
    static int32_t handshake_icon_var = RES_SHAKE_OFF;
    if (data == NULL) {
        data = &guider_msg_data;
    }

    if (db_select("sok")) {
        handshake_icon_var = RES_SHAKE_ON;
    }

    if (access == GUI_MSG_ACCESS_SET) {
        handshake_icon_var = data->value_int;
    }
    data->value_int = handshake_icon_var;
    return 0;
}

int gui_model_video_photo_msg_shots_icon_cb(gui_msg_action_t access, gui_msg_data_t *data, gui_msg_data_type_t type)
{
    static bool shots_icon_var = false;
    if (data == NULL) {
        data = &guider_msg_data;
    }

    if (db_select("cyt")) {
        shots_icon_var = true;
    }

    if (access == GUI_MSG_ACCESS_SET) {
        shots_icon_var = data->value_int;
    }
    data->value_int = shots_icon_var;
    return 0;
}

int gui_model_video_photo_msg_photo_reso_cb(gui_msg_action_t access, gui_msg_data_t *data, gui_msg_data_type_t type)
{
    static char photo_reso_init_var[16] = { 0 };
    if (data == NULL) {
        data = &guider_msg_data;
    }

    uint32_t p_reso = db_select("pres");
    if (p_reso) {
        sprintf(photo_reso_init_var, "%dM", p_reso);
    } else {
        strcpy(photo_reso_init_var, "VGA");
    }

    if (access == GUI_MSG_ACCESS_SET) {
        strcpy(photo_reso_init_var, (char *)data->value_string);
    }
    data->value_string = photo_reso_init_var;
    return 0;
}

//剩余拍照数量更新
void post_msg2photo_remain(int32_t num)
{
#ifdef USE_LVGL_V8_UI_DEMO
    static char remain[16];
    printf("----->%s()----->photo_remain: %d\n", __func__, num);
    sprintf(remain, "%d", num);
    lvgl_module_msg_send_global_ptr(GUI_MODEL_VIDEO_PHOTO_MSG_ID_PHOTO_REMAIN, (void *)remain, strlen(remain), 0);
#endif // USE_LVGL_V8_UI_DEMO
}

int gui_model_video_photo_msg_photo_remain_cb(gui_msg_action_t access, gui_msg_data_t *data, gui_msg_data_type_t type)
{
    static char photo_remain_init_var[16] = { 0 };
    if (data == NULL) {
        data = &guider_msg_data;
    }

    // if (access == GUI_MSG_ACCESS_GET) {
    extern u32 get_take_photo_num(void);
    u32 photo_remain = get_take_photo_num();
    printf("----->%s()----->p_remain: %d\n", __func__, photo_remain);

    sprintf(photo_remain_init_var, "%d", photo_remain);

    // }
    data->value_string = photo_remain_init_var;

    return 0;
}

#endif

void video_photo_icon_reshow(int icon_type)
{
    switch (icon_type) {
    case SUBPAGE_EXPOSURE:
        printf("----->%s()----->pexp: %d\n", __func__, db_select("pexp"));
        switch (db_select("pexp")) {
        case 0xfffffffd://-3
            lvgl_module_msg_send_global_ptr(GUI_MODEL_VIDEO_PHOTO_MSG_ID_PEXP_ICON, (void *)RES_EXP_D3, sizeof(RES_EXP_D3), 0);
            break;
        case 0xfffffffe://-2
            lvgl_module_msg_send_global_ptr(GUI_MODEL_VIDEO_PHOTO_MSG_ID_PEXP_ICON, (void *)RES_EXP_D2, sizeof(RES_EXP_D2), 0);
            break;
        case 0xffffffff://-1
            lvgl_module_msg_send_global_ptr(GUI_MODEL_VIDEO_PHOTO_MSG_ID_PEXP_ICON, (void *)RES_EXP_D1, sizeof(RES_EXP_D1), 0);
            break;
        case 0:
            lvgl_module_msg_send_global_ptr(GUI_MODEL_VIDEO_PHOTO_MSG_ID_PEXP_ICON, (void *)RES_EXP_A0, sizeof(RES_EXP_A0), 0);
            break;
        case 1:
            lvgl_module_msg_send_global_ptr(GUI_MODEL_VIDEO_PHOTO_MSG_ID_PEXP_ICON, (void *)RES_EXP_A1, sizeof(RES_EXP_A1), 0);
            break;
        case 2:
            lvgl_module_msg_send_global_ptr(GUI_MODEL_VIDEO_PHOTO_MSG_ID_PEXP_ICON, (void *)RES_EXP_A2, sizeof(RES_EXP_A2), 0);
            break;
        case 3:
            lvgl_module_msg_send_global_ptr(GUI_MODEL_VIDEO_PHOTO_MSG_ID_PEXP_ICON, (void *)RES_EXP_A3, sizeof(RES_EXP_A3), 0);
            break;
        default:
            lvgl_module_msg_send_global_ptr(GUI_MODEL_VIDEO_PHOTO_MSG_ID_PEXP_ICON, (void *)RES_EXP_A0, sizeof(RES_EXP_A0), 0);
            break;
        }
#if !LV_USE_GUIBUILDER_SIMULATOR
        gui_set_camera_config("pexp", db_select("pexp"));
#endif
        break;
    case SUBPAGE_AWB:
        switch (db_select("wbl")) {
        case PHOTO_WBL_SUN:
            lvgl_module_msg_send_global_ptr(GUI_MODEL_VIDEO_PHOTO_MSG_ID_AWB_ICON, (void *)RES_AWB_FINE, sizeof(RES_AWB_FINE), 0);
            break;
        case PHOTO_WBL_CLDY:
            lvgl_module_msg_send_global_ptr(GUI_MODEL_VIDEO_PHOTO_MSG_ID_AWB_ICON, (void *)RES_AWB_CLOUDY, sizeof(RES_AWB_CLOUDY), 0);
            break;
        case PHOTO_WBL_TSL:
            lvgl_module_msg_send_global_ptr(GUI_MODEL_VIDEO_PHOTO_MSG_ID_AWB_ICON, (void *)RES_AWB_TUNGSTEN_LAMP, sizeof(RES_AWB_TUNGSTEN_LAMP), 0);
            break;
        case PHOTO_WBL_FLUL:
            lvgl_module_msg_send_global_ptr(GUI_MODEL_VIDEO_PHOTO_MSG_ID_AWB_ICON, (void *)RES_AWB_FLUORESCENT_LAMP_1, sizeof(RES_AWB_FLUORESCENT_LAMP_1), 0);
            break;
        default:  //PHOTO_WBL_AUTO
            lvgl_module_msg_send_global_ptr(GUI_MODEL_VIDEO_PHOTO_MSG_ID_AWB_ICON, (void *)RES_AWB_AUTO, sizeof(RES_AWB_AUTO), 0);
            break;
        }
        break;
    case SUBPAGE_COLOR:
#if !LV_USE_GUIBUILDER_SIMULATOR
        gui_set_camera_config("col", db_select("col"));
#endif
        break;
    case SUBPAGE_ISO:
        printf("----->%s()----->iso: %d\n", __func__, db_select("iso"));
        switch (db_select("iso")) {
        case 100:
            lvgl_module_msg_send_global_ptr(GUI_MODEL_VIDEO_PHOTO_MSG_ID_ISO_ICON, (void *)RES_ISO_1, sizeof(RES_ISO_1), 0);
            break;
        case 200:
            lvgl_module_msg_send_global_ptr(GUI_MODEL_VIDEO_PHOTO_MSG_ID_ISO_ICON, (void *)RES_ISO_2, sizeof(RES_ISO_2), 0);
            break;
        case 400:
            lvgl_module_msg_send_global_ptr(GUI_MODEL_VIDEO_PHOTO_MSG_ID_ISO_ICON, (void *)RES_ISO_4, sizeof(RES_ISO_4), 0);
            break;
        default:
            lvgl_module_msg_send_global_ptr(GUI_MODEL_VIDEO_PHOTO_MSG_ID_ISO_ICON, (void *)RES_ISO_AUTO, sizeof(RES_ISO_AUTO), 0);
            break;
        }
        break;
    case SUBPAGE_QUALITY:
        switch (db_select("qua")) {
        case 2:
            lvgl_module_msg_send_global_ptr(GUI_MODEL_VIDEO_PHOTO_MSG_ID_QUALITY_ICON, (void *)RES_Q3, sizeof(RES_Q3), 0);
            break;
        case 1:
            lvgl_module_msg_send_global_ptr(GUI_MODEL_VIDEO_PHOTO_MSG_ID_QUALITY_ICON, (void *)RES_Q2, sizeof(RES_Q2), 0);
            break;
        case 0:
            lvgl_module_msg_send_global_ptr(GUI_MODEL_VIDEO_PHOTO_MSG_ID_QUALITY_ICON, (void *)RES_Q1, sizeof(RES_Q1), 0);
            break;
        default:
            lvgl_module_msg_send_global_ptr(GUI_MODEL_VIDEO_PHOTO_MSG_ID_QUALITY_ICON, (void *)RES_Q3, sizeof(RES_Q3), 0);
            break;
        }
        break;
    case SUBPAGE_SHOOT:
        lvgl_module_msg_send_value(GUI_MODEL_VIDEO_PHOTO_MSG_ID_DELAY_SATE, true, 0);
        switch (db_select("phm")) {
        case 2:
            lvgl_module_msg_send_global_ptr(GUI_MODEL_VIDEO_PHOTO_MSG_ID_DELAY_ICON, (void *)RES_DL2, sizeof(RES_DL2), 0);
            break;
        case 5:
            lvgl_module_msg_send_global_ptr(GUI_MODEL_VIDEO_PHOTO_MSG_ID_DELAY_ICON, (void *)RES_DL5, sizeof(RES_DL5), 0);
            break;
        case 10:
            lvgl_module_msg_send_global_ptr(GUI_MODEL_VIDEO_PHOTO_MSG_ID_DELAY_ICON, (void *)RES_DL10, sizeof(RES_DL10), 0);
            break;
        default:
            lvgl_module_msg_send_value(GUI_MODEL_VIDEO_PHOTO_MSG_ID_DELAY_SATE, false, 0);
            break;
        }
        break;
    case SUBPAGE_HANDSHAKE:
        switch (db_select("sok")) {
        case 1:
            lvgl_module_msg_send_global_ptr(GUI_MODEL_VIDEO_PHOTO_MSG_ID_HANDSHAKE_ICON, (void *)RES_SHAKE_ON, sizeof(RES_SHAKE_ON), 0);
            break;
        default:
            lvgl_module_msg_send_global_ptr(GUI_MODEL_VIDEO_PHOTO_MSG_ID_HANDSHAKE_ICON, (void *)RES_SHAKE_OFF, sizeof(RES_SHAKE_OFF), 0);
            break;
        }
        break;
    case SUBPAGE_SHOTS:
        if (db_select("cyt")) {
            lvgl_module_msg_send_value(GUI_MODEL_VIDEO_PHOTO_MSG_ID_SHOTS_ICON, true, 0);
        } else {
            lvgl_module_msg_send_value(GUI_MODEL_VIDEO_PHOTO_MSG_ID_SHOTS_ICON, false, 0);
        }
        break;
    case SUBPAGE_SHARPNESS:
#if !LV_USE_GUIBUILDER_SIMULATOR
        gui_set_camera_config("acu", db_select("acu"));
#endif
        break;
    }
}

#endif
