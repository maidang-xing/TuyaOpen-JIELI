#include "app_config.h"
#ifdef CONFIG_UI_STYLE_JL_ENABLE
/**
 * @file custom.c
 *
 */

/*********************
 *      INCLUDES
 *********************/

#include "custom.h"
#if !LV_USE_GUIBUILDER_SIMULATOR
#include "video_photo.h"
#endif
/*********************
 *      DEFINES
 *********************/

/**********************
*      TYPEDEFS
**********************/
#ifdef USE_LVGL_V8_UI_DEMO
extern lv_indev_t *indev_keypad;
#endif

struct subpage_data rec_subpage_data = { 0 };//拍照设置子页面显示更新数据
int now_videorec_subpage = SUBPAGE_RESOLUTION;//当前拍照模式菜单子页面

struct subpage_data photo_subpage_data = { 0 };//拍照设置子页面显示更新数据
int now_videophoto_subpage = SUBPAGE_RESOLUTION;//当前拍照模式菜单子页面

struct sysmenu_subpage_data my_sysmenu_subpage = { 0 };//菜单设置子页面显示更新数据

static lv_timer_t *funkey8_timer = 0;
static int funkey8_timer_cnt = 5;

char user_roller_str[64] = { 0 };//记录roller被选项
int subpage_cur_btn = SUBPAGE_FUNKEY_NULL;//子页面当前被按下的按键 0无按下 1~n代表funkey1~n
bool usb_flag = false;
bool update_date = false;
static bool reset_update_yes = false;
/**********************
 *  STATIC PROTOTYPES
 **********************/
#ifndef USE_LVGL_V8_UI_DEMO
void lvgl_ui_suspend(void)
{
}
void lvgl_ui_resume(void)
{
}
#endif // USE_LVGL_V8_UI_DEMO

/**********************
 *  STATIC VARIABLES
 **********************/
#if !LV_USE_GUIBUILDER_SIMULATOR
extern lv_group_t *def_group;
extern lv_group_t *group_list;
int ui_scr_key_event_handler_ext(struct key_event *event)
{
    switch (event->value) {
    case KEY_POWER:
        if (event->action == KEY_EVENT_LONG) {
            return 1;
        }
        return 0;
    case KEY_ENC:
        printf("voice wake up\n");
        return 1;
    default :
        return 0;
    }
}
/*注册页面按键响应函数回调*/
int video_rec_key_handler(struct key_event *key)
{
    switch (key->value) {
    case KEY_UP:
    case KEY_DOWN:
        lv_obj_t *focused_obj = lv_group_get_focused(lv_group_get_default());
        // 检查聚焦的对象是否是 roller 控件
        if (focused_obj != NULL && lv_obj_check_type(focused_obj, &lv_roller_class)) {
            //聚焦对象是roller时，说明正在使用key_up键选择roller的选项，此时不将按键发给app_core
            return 0;
        } else {
            // 聚焦的对象不是 roller 控件
            return 1;
        }
    default:
        return 0;
    }
}
REGISTER_UI_KEY_EVENT_HANDLER(GUI_SCREEN_VIDEO_REC)
.key_onchange = video_rec_key_handler,
};

static bool is_area_in(const lv_area_t *outer, const lv_area_t *inner)
{
    return (inner->x1 >= outer->x1 && inner->x2 <= outer->x2 &&
            inner->y1 >= outer->y1 && inner->y2 <= outer->y2);
}

//判断按键聚焦的对象是否在显示范围内，不在则进行处理
static void key_scroll_to_view(void)
{

    lv_obj_t *focused_obj = lv_group_get_focused(lv_group_get_default());
    lv_obj_t *focused_obj_parent = lv_obj_get_parent(focused_obj);
    //控件是有效的才继续操作
    if ((!lv_obj_is_valid(focused_obj)) || (!lv_obj_is_valid(focused_obj_parent))) {
        return;
    }

    // 获取滚动容器的滚动区域
    lv_area_t container_area;
    lv_obj_get_coords(focused_obj_parent, &container_area);

    // 获取焦点对象的区域
    lv_area_t obj_area;
    lv_obj_get_coords(focused_obj, &obj_area);

    /* printf("obj x1:%d  y1:%d  x2:%d  y2:%d\n",obj_area.x1,obj_area.y1,obj_area.x2,obj_area.y2); */
    /* printf("cont x1:%d  y1:%d  x2:%d  y2:%d\n",container_area.x1, */
    /* container_area.y1,container_area.x2,container_area.y2); */
    // 检查焦点对象是否在可见区域内
    if (!is_area_in(&container_area, &obj_area)) {
        // 如果不在可见区域内，则滚动滚动容器，使其显示焦点对象
        lv_obj_scroll_to_view_recursive(focused_obj, LV_ANIM_ON);
    }

}

//=======================================================//
// LVGL按键值重新映射函数:
// 用户可以在custom.c中实现该函数把LVGL的按键重新映射
// key_value为映射前的键值，key_remap为映射后的键值
//=======================================================//
void lvgl_key_value_remap(u8 key_value, uint32_t *key_remap)
{
    /* LV_KEY_PREV/LV_KEY_NEXT 为按键导航时聚焦上、下一个控件；
      LV_KEY_UP/LV_KEY_DOWN 为选中下拉列表控件后向上、下翻值 */
    switch (key_value) {
    case KEY_POWER:
        key_scroll_to_view();
        *key_remap = LV_KEY_PREV;
        break;
    case KEY_MENU:
        key_scroll_to_view();
        *key_remap = LV_KEY_NEXT;
        break;
    case KEY_UP:
        *key_remap = LV_KEY_UP;
        break;
    case KEY_DOWN:
        *key_remap = LV_KEY_DOWN;
        break;
    default://KEY_OK
        *key_remap = LV_KEY_ENTER;
        break;
    }

}
#endif
/**
 * Create a demo application
 */

void custom_init(lv_ui *ui)
{
    /* Add your codes here */
    printf("[chili] %s %d   \n", __func__, __LINE__);

}
void carnum_utf8_to_gb2312(const uint8_t *utf_8, uint8_t *gb2312_data, int selected_index)
{
    switch (selected_index) {
    case 0:
        gb2312_data[0] = 0xBE;
        gb2312_data[1] = 0xA9;
        break;
    case 1:
        gb2312_data[0] = 0xBD;
        gb2312_data[1] = 0xF2;
        break;
    case 2:
        gb2312_data[0] = 0xBD;
        gb2312_data[1] = 0xFA;
        break;
    case 3:
        gb2312_data[0] = 0xBC;
        gb2312_data[1] = 0xBD;
        break;
    case 4:
        gb2312_data[0] = 0xC3;
        gb2312_data[1] = 0xC9;
        break;
    case 5:
        gb2312_data[0] = 0xC1;
        gb2312_data[1] = 0xC9;
        break;
    case 6:
        gb2312_data[0] = 0xBC;
        gb2312_data[1] = 0xAA;
        break;
    case 7:
        gb2312_data[0] = 0xBA;
        gb2312_data[1] = 0xDA;
        break;
    case 8:
        gb2312_data[0] = 0xCB;
        gb2312_data[1] = 0xD5;
        break;
    case 9:
        gb2312_data[0] = 0xD5;
        gb2312_data[1] = 0xE3;
        break;
    case 10:
        gb2312_data[0] = 0xCD;
        gb2312_data[1] = 0xEE;
        break;
    case 11:
        gb2312_data[0] = 0xC3;
        gb2312_data[1] = 0xF6;
        break;
    case 12:
        gb2312_data[0] = 0xB8;
        gb2312_data[1] = 0xD3;
        break;
    case 13:
        gb2312_data[0] = 0xC2;
        gb2312_data[1] = 0xB3;
        break;
    case 14:
        gb2312_data[0] = 0xD4;
        gb2312_data[1] = 0xA5;
        break;
    case 15:
        gb2312_data[0] = 0xB6;
        gb2312_data[1] = 0xF5;
        break;
    case 16:
        gb2312_data[0] = 0xCF;
        gb2312_data[1] = 0xE6;
        break;
    case 17:
        gb2312_data[0] = 0xD4;
        gb2312_data[1] = 0xC1;
        break;
    case 18:
        gb2312_data[0] = 0xB9;
        gb2312_data[1] = 0xF0;
        break;
    case 19:
        gb2312_data[0] = 0xC7;
        gb2312_data[1] = 0xC7;
        break;
    case 20:
        gb2312_data[0] = 0xB4;
        gb2312_data[1] = 0xA8;
        break;
    case 21:
        gb2312_data[0] = 0xB9;
        gb2312_data[1] = 0xF3;
        break;
    case 22:
        gb2312_data[0] = 0xB5;
        gb2312_data[1] = 0xE1;
        break;
    case 23:
        gb2312_data[0] = 0xD3;
        gb2312_data[1] = 0xE5;
        break;
    case 24:
        gb2312_data[0] = 0xB2;
        gb2312_data[1] = 0xD8;
        break;
    case 25:
        gb2312_data[0] = 0xC9;
        gb2312_data[1] = 0xC2;
        break;
    case 26:
        gb2312_data[0] = 0xB8;
        gb2312_data[1] = 0xCA;
        break;
    case 27:
        gb2312_data[0] = 0xC7;
        gb2312_data[1] = 0xE0;
        break;
    case 28:
        gb2312_data[0] = 0xC4;
        gb2312_data[1] = 0xFE;
        break;
    case 29:
        gb2312_data[0] = 0xD0;
        gb2312_data[1] = 0xC2;
        break;
    case 30:
        gb2312_data[0] = 0xCC;
        gb2312_data[1] = 0xA8;
        break;
    case 31:
        gb2312_data[0] = 0xB8;
        gb2312_data[1] = 0xDB;
        break;
    case 32:
        gb2312_data[0] = 0xB0;
        gb2312_data[1] = 0xC4;
        break;
    }
    for (int i = 2; i < 16; i++) {
        gb2312_data[i] = utf_8[i + 1];

    }
}

//仿真测试
#if LV_USE_GUIBUILDER_SIMULATOR
#define SDX_DEV                 "sdx"
/*
* 录像启停控制--控件触摸事件回调
*/
void rec_control_ontouch(void)
{

}

/*
* 录像模式视窗切换控制--控件触摸事件回调
*/
void rec_switch_win_ontouch(void)
{


}

/*
* 录像模式文件加锁--控件触摸事件回调
*/

void rec_set_lock_ontouch(void)
{


}

int lvgl_rpc_post_func(void (*rpc_func)(void *, ...), int argc, ...)
{
}

int video_rec_record_time()
{

}

/*
* 格式化卡
*/
int sdcard_storage_device_format(const char *sd_name)
{

}
int storage_device_ready()
{
    return 1;
}
void video_system_format(void)
{

}
int aff_set_function(uint32_t parm)
{
    return 0;
}

void video_rec_config_init(void)
{

}
uint32_t get_take_photo_num(void)
{

}

void edit_lock_file(lv_obj_t *dest, int dir)
{

}

void video_dec_edit_files(uint8_t mode)
{

}
void ui_lcd_light_time_set(int sec)
{

}
void rec_tell_app_exit_menu(void)
{

}
int rec_ask_app_open_menu(void)
{

}
void rec_set_config(char *cfg, int val)
{

}
#endif


//仿真专用模型发送函数，对接792不允许直接gui_msg_send
#if LV_USE_GUIBUILDER_SIMULATOR
/*
* 模型消息发送
* 模型id
* 模型消息
* 模型消息长度
* refr_now 0是等屏幕下一个刷新周期再一起刷新（最好是），1是立即刷新
*/
int lvgl_module_msg_send_global_ptr(unsigned int msg_id, const void *value, unsigned int len, char refr_now)
{
    gui_msg_send(msg_id, value, len);
}
int lvgl_module_msg_send_string(unsigned int msg_id, const char *string, char refr_now)
{
    gui_msg_send(msg_id, string, 4);
}
int lvgl_module_msg_send_value(unsigned int msg_id, unsigned int value, char refr_now)
{
    gui_msg_send(msg_id, value, 4);
}
void *lvgl_module_group_create(unsigned int msg_group_id)
{

}
int lvgl_module_msg_group_add_global_ptr(void *group, unsigned int msg_id, const void *ptr, unsigned int len)
{
    gui_msg_send(msg_id, ptr, len);
}
int lvgl_module_msg_group_add_string(void *group, unsigned int msg_id, const char *string)
{
    gui_msg_send(msg_id, string, 4);
}
int lvgl_module_msg_group_add_value(void *group, unsigned int msg_id, unsigned int value)
{
    gui_msg_send(msg_id, value, 4);
}
void *lvgl_module_msg_group_add_ptr(void *group, unsigned int msg_id, unsigned int len)
{
}
int lvgl_module_msg_group_send(void *group, char refr_now)
{

}

/*
* 模型消息发送--数组类型
* 模型id
* 模型消息
* 模型消息长度
* refr_now 0是等屏幕下一个刷新周期再一起刷新（最好是），1是立即刷新
*/
static uint32_t mmsg_id = 0;
static uint32_t mmsg_len = 0;
static void *ptr_p = 0;

void *lvgl_module_msg_get_ptr(unsigned int msg_id, unsigned int len)
{
    mmsg_id = msg_id;
    mmsg_len = len;
    ptr_p = malloc(len);
    return ptr_p;
}

int lvgl_module_msg_send_ptr(void *ptr, char refr_now)
{
    gui_msg_send(mmsg_id, ptr, mmsg_len);
    free(ptr_p);
}

#endif

/*
*更新预览界面图标
* @arg1 icon:菜单子页面作为更新预览界面图标的依据 比如SUBPAGE_RESOLUTION就是对应预览界面下的分辨率图标
* return void
*/
void video_rec_icon_reshow(int icon)
{
    char *str_buf;
    void *rec_group = lvgl_module_group_create(GROUP_VIDEO_REC);
    int exp;
    switch (icon) {
    case SUBPAGE_RESOLUTION:
        str_buf = lvgl_module_msg_get_ptr(GUI_MODEL_VIDEO_REC_MSG_ID_REC_RESO, 8);
        switch (db_select("res")) {
        case VIDEO_RES_1080P:
            sprintf(str_buf, "%dP", 1080);
            break;
        case VIDEO_RES_720P:
            sprintf(str_buf, "%dP", 720);
            break;
        default:
            strcpy(str_buf, "VGA");
            break;
        }
        extern uint32_t get_take_photo_num(void);
        uint32_t img_num = get_take_photo_num();
        lvgl_module_msg_send_ptr(str_buf, 0);
        break;
    case SUBPAGE_EXPOSURE:
        exp = db_select("exp");
        rec_set_config("exp", exp);
        break;
    case SUBPAGE_DOUBLE_REC:

        break;
    case SUBPAGE_CYC_REC:
        switch (db_select("cyc")) {
        case 3:
            lvgl_module_msg_group_add_global_ptr(rec_group, GUI_MODEL_VIDEO_REC_MSG_ID_CYCREC_ICON, (void *)RES_CYCLIC_VIDEO_3, sizeof(RES_CYCLIC_VIDEO_3));
            break;
        case 1:
            lvgl_module_msg_group_add_global_ptr(rec_group, GUI_MODEL_VIDEO_REC_MSG_ID_CYCREC_ICON, (void *)RES_CYCLIC_VIDEO_1, sizeof(RES_CYCLIC_VIDEO_1));
            break;
        case 10:
            lvgl_module_msg_group_add_global_ptr(rec_group, GUI_MODEL_VIDEO_REC_MSG_ID_CYCREC_ICON, (void *)RES_CYCLIC_VIDEO_10, sizeof(RES_CYCLIC_VIDEO_10));
            break;
        default:
            lvgl_module_msg_group_add_global_ptr(rec_group, GUI_MODEL_VIDEO_REC_MSG_ID_CYCREC_ICON, (void *)RES_CYCLIC_VIDEO_CLOSE, sizeof(RES_CYCLIC_VIDEO_CLOSE));
            break;
        }

        break;
    case SUBPAGE_GAP:
        switch (db_select("gap")) {
        case 100:
            lvgl_module_msg_group_add_global_ptr(rec_group, GUI_MODEL_VIDEO_REC_MSG_ID_DELAYREC_ICON, (void *)RES_INTERVAL_VIDEO_100, sizeof(RES_INTERVAL_VIDEO_100));
            break;
        case 200:
            lvgl_module_msg_group_add_global_ptr(rec_group, GUI_MODEL_VIDEO_REC_MSG_ID_DELAYREC_ICON, (void *)RES_INTERVAL_VIDEO_200, sizeof(RES_INTERVAL_VIDEO_200));
            break;
        case 500:
            lvgl_module_msg_group_add_global_ptr(rec_group, GUI_MODEL_VIDEO_REC_MSG_ID_DELAYREC_ICON, (void *)RES_INTERVAL_VIDEO_500, sizeof(RES_INTERVAL_VIDEO_500));
            break;
        default:
            lvgl_module_msg_group_add_global_ptr(rec_group, GUI_MODEL_VIDEO_REC_MSG_ID_DELAYREC_ICON, (void *)RES_INTERVAL_VIDEO_CLOSE, sizeof(RES_INTERVAL_VIDEO_CLOSE));
            break;
        }
        break;

    case SUBPAGE_HDR:
        if (db_select("hdr")) {
            lvgl_module_msg_group_add_global_ptr(rec_group, GUI_MODEL_VIDEO_REC_MSG_ID_SHOW_HDR_ICON, (void *)LV_OBJ_FLAG_HIDDEN, 1);
        } else {
            lvgl_module_msg_group_add_global_ptr(rec_group, GUI_MODEL_VIDEO_REC_MSG_ID_HIDE_HDR_ICON, (void *)LV_OBJ_FLAG_HIDDEN, 1);
        }
        break;
    case SUBPAGE_MOTION:
        if (db_select("mot")) {
            lvgl_module_msg_group_add_global_ptr(rec_group, GUI_MODEL_VIDEO_REC_MSG_ID_SHOW_MOTION_ICON, (void *)LV_OBJ_FLAG_HIDDEN, 1);
        } else {
            lvgl_module_msg_group_add_global_ptr(rec_group, GUI_MODEL_VIDEO_REC_MSG_ID_HIDE_MOTION_ICON, (void *)LV_OBJ_FLAG_HIDDEN, 1);
        }
        break;
    case SUBPAGE_GSENSOR:
        lvgl_module_msg_group_add_global_ptr(rec_group, GUI_MODEL_VIDEO_REC_MSG_ID_SHOW_GSENSOR_ICON, (void *)LV_OBJ_FLAG_HIDDEN, 1);
        switch (db_select("gra")) {
        case 1:
            lvgl_module_msg_group_add_global_ptr(rec_group, GUI_MODEL_VIDEO_REC_MSG_ID_GSENSOR_ICON, (void *)RES_GRAVITY_SENSOR_LOW, sizeof(RES_GRAVITY_SENSOR_LOW));
            break;
        case 2:
            lvgl_module_msg_group_add_global_ptr(rec_group, GUI_MODEL_VIDEO_REC_MSG_ID_GSENSOR_ICON, (void *)RES_GRAVITY_SENSOR_MIDLLER, sizeof(RES_GRAVITY_SENSOR_MIDLLER));
            break;
        case 3:
            lvgl_module_msg_group_add_global_ptr(rec_group, GUI_MODEL_VIDEO_REC_MSG_ID_GSENSOR_ICON, (void *)RES_GRAVITY_SENSOR_HIGH, sizeof(RES_GRAVITY_SENSOR_HIGH));
            break;
        default:
            lvgl_module_msg_group_add_global_ptr(rec_group, GUI_MODEL_VIDEO_REC_MSG_ID_HIDE_GSENSOR_ICON, (void *)LV_OBJ_FLAG_HIDDEN, 1);
            break;
        }
        break;
    case SUBPAGE_RECORD:
        if (db_select("mic")) {
            lvgl_module_msg_group_add_global_ptr(rec_group, GUI_MODEL_VIDEO_REC_MSG_ID_MIC_ICON, (void *)RES_SOUND, sizeof(RES_SOUND));
        } else {
            lvgl_module_msg_group_add_global_ptr(rec_group, GUI_MODEL_VIDEO_REC_MSG_ID_MIC_ICON, (void *)RES_SOUND_CLOSE, sizeof(RES_SOUND_CLOSE));
        }
        break;
    case SUBPAGE_GUARD:
        if (db_select("par")) {
            lvgl_module_msg_group_add_global_ptr(rec_group, GUI_MODEL_VIDEO_REC_MSG_ID_SHOW_GUARD_ICON, (void *)LV_OBJ_FLAG_HIDDEN, 1);
        } else {
            lvgl_module_msg_group_add_global_ptr(rec_group, GUI_MODEL_VIDEO_REC_MSG_ID_HIDE_GUARD_ICON, (void *)LV_OBJ_FLAG_HIDDEN, 1);
        }
        break;
    default:
        //printf("[chili] %s %d   no match subpage!\n", __func__, __LINE__);
        break;

    }
    lvgl_module_msg_group_send(rec_group, 0);
}

/*
*更新拍照预览界面图标
* @arg1 icon:菜单子页面作为更新预览界面图标的依据 比如SUBPAGE_RESOLUTION就是对应预览界面下的分辨率图标
* return void
*/
void video_photo_icon_reshow(int icon)
{
    char *strarr;
    uint32_t img_num;
    void *photo_group = lvgl_module_group_create(GROUP_VIDEO_PHOTO);
    switch (icon) {
    case SUBPAGE_RESOLUTION:
        lvgl_module_msg_group_add_global_ptr(photo_group, GUI_MODEL_VIDEO_PHOTO_MSG_ID_RESOLUTION_ICON, (void *)user_roller_str, strlen(user_roller_str));
        extern uint32_t get_take_photo_num(void);
        img_num = get_take_photo_num();
        post_msg2photo_remain(NULL, img_num);
        break;
    case SUBPAGE_EXPOSURE:
#if !LV_USE_GUIBUILDER_SIMULATOR
        gui_set_camera_config("pexp", atoi(user_roller_str));
#endif
        break;
    case SUBPAGE_ISO:
        strarr = lvgl_module_msg_get_ptr(GUI_MODEL_VIDEO_PHOTO_MSG_ID_ISO_ICON, 16);
        if (strcmp("AUTO", user_roller_str)) {
            sprintf(strarr, "ISO\n%s", user_roller_str);
        } else {
            strcpy(strarr, "AUTO");
        }
        lvgl_module_msg_send_ptr(strarr, 0);
        break;
    case SUBPAGE_SHOOT:
        //拍照界面显示并更新图标--拍摄方式
        lvgl_module_msg_group_add_global_ptr(photo_group, GUI_MODEL_VIDEO_PHOTO_MSG_ID_SHOW_SHOTS_MODE, (void *)LV_OBJ_FLAG_HIDDEN, 1);
        switch (db_select("phm")) {
        case 2:
            lvgl_module_msg_group_add_global_ptr(photo_group, GUI_MODEL_VIDEO_PHOTO_MSG_ID_SHOT_MODE_ICON, (void *)RES_TIMING_PHOTO_2, sizeof(RES_TIMING_PHOTO_2));
            break;
        case 5:
            lvgl_module_msg_group_add_global_ptr(photo_group, GUI_MODEL_VIDEO_PHOTO_MSG_ID_SHOT_MODE_ICON, (void *)RES_TIMING_PHOTO_5, sizeof(RES_TIMING_PHOTO_5));
            break;
        case 10:
            lvgl_module_msg_group_add_global_ptr(photo_group, GUI_MODEL_VIDEO_PHOTO_MSG_ID_SHOT_MODE_ICON, (void *)RES_TIMING_PHOTO_10, sizeof(RES_TIMING_PHOTO_10));
            break;
        default:
            lvgl_module_msg_group_add_global_ptr(photo_group, GUI_MODEL_VIDEO_PHOTO_MSG_ID_HIDE_SHOTS_MODE, (void *)LV_OBJ_FLAG_HIDDEN, 1);
            break;
        }
        break;
    case SUBPAGE_SHOTS:
        //拍照界面显示并更新图标--连拍
        switch (db_select("cyt")) {
        case 1:
            lvgl_module_msg_group_add_global_ptr(photo_group, GUI_MODEL_VIDEO_PHOTO_MSG_ID_SHOW_SHOTS, (void *)LV_OBJ_FLAG_HIDDEN, 1);
            break;
        default:
            lvgl_module_msg_group_add_global_ptr(photo_group, GUI_MODEL_VIDEO_PHOTO_MSG_ID_HIDE_SHOTS, (void *)LV_OBJ_FLAG_HIDDEN, 1);
            break;
        }
        break;
    case SUBPAGE_QUALITY:
        img_num = get_take_photo_num();
        post_msg2photo_remain(NULL, img_num);
        //拍照界面显示并更新图标--图像质量
        switch (db_select("qua")) {
        case 2:
            lvgl_module_msg_group_add_global_ptr(photo_group, GUI_MODEL_VIDEO_PHOTO_MSG_ID_QUALITY_ICON, (void *)RES_HIGH, sizeof(RES_HIGH));
            break;
        case 1:
            lvgl_module_msg_group_add_global_ptr(photo_group, GUI_MODEL_VIDEO_PHOTO_MSG_ID_QUALITY_ICON, (void *)RES_MIDDLE, sizeof(RES_MIDDLE));
            break;
        default:
            lvgl_module_msg_group_add_global_ptr(photo_group, GUI_MODEL_VIDEO_PHOTO_MSG_ID_QUALITY_ICON, (void *)RES_LOW, sizeof(RES_LOW));
            break;
        }
        break;
    case SUBPAGE_SHARPNESS:
#if !LV_USE_GUIBUILDER_SIMULATOR
        gui_set_camera_config("acu", db_select("acu"));
#endif
        break;
    case SUBPAGE_AWB:
        //拍照界面更新图标--AWB
        switch (db_select("wbl")) {
        case 1:
            lvgl_module_msg_group_add_global_ptr(photo_group, GUI_MODEL_VIDEO_PHOTO_MSG_ID_AWB_ICON, (void *)RES_AWB_SUN_LIGHT, sizeof(RES_AWB_SUN_LIGHT));
            break;
        case 2:
            lvgl_module_msg_group_add_global_ptr(photo_group, GUI_MODEL_VIDEO_PHOTO_MSG_ID_AWB_ICON, (void *)RES_AWB_SUN_CLOUDY, sizeof(RES_AWB_SUN_CLOUDY));
            break;
        case 3:
            lvgl_module_msg_group_add_global_ptr(photo_group, GUI_MODEL_VIDEO_PHOTO_MSG_ID_AWB_ICON, (void *)RES_AWB_OSRAM_LAMP, sizeof(RES_AWB_OSRAM_LAMP));
            break;
        case 4:
            lvgl_module_msg_group_add_global_ptr(photo_group, GUI_MODEL_VIDEO_PHOTO_MSG_ID_AWB_ICON, (void *)RES_AWB_FLUORESCENT_LAMP, sizeof(RES_AWB_FLUORESCENT_LAMP));
            break;
        default:
            lvgl_module_msg_group_add_global_ptr(photo_group, GUI_MODEL_VIDEO_PHOTO_MSG_ID_AWB_ICON, (void *)RES_AWB, sizeof(RES_AWB));
            break;
        }
        break;
    case SUBPAGE_COLOR:
        gui_set_camera_config("col", db_select("col"));

        break;

    case SUBPAGE_HANDSHAKE:
        //拍照界面显示并更新图标--连拍
        switch (db_select("sok")) {
        case 1:
            lvgl_module_msg_group_add_global_ptr(photo_group, GUI_MODEL_VIDEO_PHOTO_MSG_ID_SHOW_HANDSHAKE, (void *)LV_OBJ_FLAG_HIDDEN, 1);
            break;
        default:
            lvgl_module_msg_group_add_global_ptr(photo_group, GUI_MODEL_VIDEO_PHOTO_MSG_ID_HIDE_HANDSHAKE, (void *)LV_OBJ_FLAG_HIDDEN, 1);
            break;
        }
        break;
    case SUBPAGE_PREVIEW:
#if !LV_USE_GUIBUILDER_SIMULATOR
        gui_set_camera_config("sca", db_select("sca"));
#endif
        break;
    case SUBPAGE_DATE:
#if !LV_USE_GUIBUILDER_SIMULATOR
        gui_set_camera_config("pdat", db_select("pdat"));
#endif
        break;

    default:
        printf("[chili] %s %d   no match subpage!\n", __func__, __LINE__);
        break;

    }
    lvgl_module_msg_group_send(photo_group, 0);
}

/*
*   funkey2按键定时器删除、恢复正常样式
*
*
*/
static void funkey8_timer_del(void *strarr)
{

    funkey8_timer_cnt = 5;

    if (funkey8_timer) {
        lv_timer_del(funkey8_timer);
        funkey8_timer = NULL;

    }
    if (strarr) {
        lvgl_module_msg_send_global_ptr(GUI_MODEL_SYS_SETTING_MSG_ID_STATE_FUNKEY8, (void *)LV_STATE_DEFAULT, 1, 0);
        lvgl_module_msg_send_global_ptr(GUI_MODEL_SYS_SETTING_MSG_ID_FUNKEY8, strarr, strlen(strarr), 0);
    }

}
/*
*   funkey2按键定时器回调
*
*/
static void funkey8_timer_cb(lv_timer_t *timer)
{
    if (--funkey8_timer_cnt < 1) {//让funkey2恢复默认样式
        funkey8_timer_cnt = 5;
        funkey8_timer_del(timer->user_data);
    } else {
        char *strarr = lvgl_module_msg_get_ptr(GUI_MODEL_SYS_SETTING_MSG_ID_FUNKEY8, 16);
        sprintf(strarr, "%s(%d)", timer->user_data, funkey8_timer_cnt);
        lvgl_module_msg_send_ptr(strarr, funkey8_timer_cnt);

    }
}

/*
*   系统菜单子页面的更新管理函数
*   @my_subpage 子页面更新依赖数据
*/
void sysmenu_subpage_show(struct sysmenu_subpage_data *my_subpage)
{
    lv_ui_sys_setting *ui_scr = ui_get_scr_ptr(&guider_ui, GUI_SCREEN_SYS_SETTING);
    if (!ui_scr) {
        return;
    }
    lv_obj_t *focused_obj = lv_group_get_focused(lv_group_get_default());
#ifdef USE_LVGL_V8_UI_DEMO
    if (!my_subpage->carnum_view && !my_subpage->warning && !my_subpage->date_view && my_subpage->now_subpage) {
        lv_group_set_default(group_list);
        lv_indev_set_group(indev_keypad, group_list);
    }
#endif
    //更新图标、标题、key值内容
    void *sys_group = lvgl_module_group_create(GROUP_VIDEO_SYSTEM);
    lvgl_module_msg_group_add_global_ptr(sys_group, GUI_MODEL_GLOBAL_SUBPAGE_MSG_ID_SUBPAGE_ICON, my_subpage->icon_res_id, sizeof(my_subpage->icon_res_id));
    lvgl_module_msg_group_add_global_ptr(sys_group, GUI_MODEL_GLOBAL_SUBPAGE_MSG_ID_TITLE, my_subpage->title, strlen(my_subpage->title));
    if (my_subpage->funkey4) {
        lvgl_module_msg_group_add_global_ptr(sys_group, GUI_MODEL_GLOBAL_SUBPAGE_MSG_ID_FUNCKEY4, my_subpage->funkey4, strlen(my_subpage->funkey4));
        lvgl_module_msg_group_add_value(sys_group, GUI_MODEL_GLOBAL_SUBPAGE_MSG_ID_SHOW_FUNCKEY4, (void *)LV_OBJ_FLAG_HIDDEN);
    } else {
        lvgl_module_msg_group_add_value(sys_group, GUI_MODEL_GLOBAL_SUBPAGE_MSG_ID_HIDE_FUNCKEY4, (void *)LV_OBJ_FLAG_HIDDEN);
    }
    if (my_subpage->funkey5) {
        lvgl_module_msg_group_add_global_ptr(sys_group, GUI_MODEL_SYS_SETTING_MSG_ID_FUNKEY5, my_subpage->funkey5, strlen(my_subpage->funkey5));
        lvgl_module_msg_group_add_value(sys_group, GUI_MODEL_SYS_SETTING_MSG_ID_SHOW_FUNKEY5, (void *)LV_OBJ_FLAG_HIDDEN);
    } else {
        lvgl_module_msg_group_add_value(sys_group, GUI_MODEL_SYS_SETTING_MSG_ID_HIDE_FUNKEY5, (void *)LV_OBJ_FLAG_HIDDEN);
    }
    if (my_subpage->funkey6) {
        lvgl_module_msg_group_add_global_ptr(sys_group, GUI_MODEL_SYS_SETTING_MSG_ID_FUNKEY6, my_subpage->funkey6, strlen(my_subpage->funkey6));
        lvgl_module_msg_group_add_value(sys_group, GUI_MODEL_SYS_SETTING_MSG_ID_SHOW_FUNKEY6, (void *)LV_OBJ_FLAG_HIDDEN);
    } else {
        lvgl_module_msg_group_add_value(sys_group, GUI_MODEL_SYS_SETTING_MSG_ID_HIDE_FUNKEY6, (void *)LV_OBJ_FLAG_HIDDEN);
    }
    if (my_subpage->funkey7) {
        lvgl_module_msg_group_add_global_ptr(sys_group, GUI_MODEL_SYS_SETTING_MSG_ID_FUNKEY7, my_subpage->funkey7, strlen(my_subpage->funkey7));
        lvgl_module_msg_group_add_value(sys_group, GUI_MODEL_SYS_SETTING_MSG_ID_SHOW_FUNKEY7, (void *)LV_OBJ_FLAG_HIDDEN);
    } else {
        lvgl_module_msg_group_add_value(sys_group, GUI_MODEL_SYS_SETTING_MSG_ID_HIDE_FUNKEY7, (void *)LV_OBJ_FLAG_HIDDEN);
    }

    //显示相关页面隐藏非相关页面
    if (my_subpage->funkey4) {
        lvgl_module_msg_group_add_value(sys_group, GUI_MODEL_SYS_SETTING_MSG_ID_SHOW_VIEWLIST, (void *)LV_OBJ_FLAG_HIDDEN);
    } else {
        lvgl_module_msg_group_add_value(sys_group, GUI_MODEL_SYS_SETTING_MSG_ID_HIDE_VIEWLIST, (void *)LV_OBJ_FLAG_HIDDEN);
    }
    if (my_subpage->carnum_view) {
        lvgl_module_msg_group_add_value(sys_group, GUI_MODEL_SYS_SETTING_MSG_ID_SHOW_VIEWCARNUM, (void *)LV_OBJ_FLAG_HIDDEN);
    } else {
        lvgl_module_msg_group_add_value(sys_group, GUI_MODEL_SYS_SETTING_MSG_ID_HIDE_VIEWCARNUM, (void *)LV_OBJ_FLAG_HIDDEN);
    }
    if (my_subpage->date_view) {
        lvgl_module_msg_group_add_value(sys_group, GUI_MODEL_SYS_SETTING_MSG_ID_SHOW_VIEWDATE, (void *)LV_OBJ_FLAG_HIDDEN);
    } else {
        lvgl_module_msg_group_add_value(sys_group, GUI_MODEL_SYS_SETTING_MSG_ID_HIDE_VIEWDATE, (void *)LV_OBJ_FLAG_HIDDEN);
    }
    if (my_subpage->warning) {
        lvgl_module_msg_group_add_value(sys_group, GUI_MODEL_SYS_SETTING_MSG_ID_SHOW_SUBPAGEWARNING, (void *)LV_OBJ_FLAG_HIDDEN);
        lvgl_module_msg_group_add_global_ptr(sys_group, GUI_MODEL_SYS_SETTING_MSG_ID_SUBPAGE_WARNING, my_subpage->warning, strlen(my_subpage->warning));
    } else {
        lvgl_module_msg_group_add_value(sys_group, GUI_MODEL_SYS_SETTING_MSG_ID_HIDE_SUBPAGEWARNING, (void *)LV_OBJ_FLAG_HIDDEN);
    }
    //定时器 funkey8指定秒数内不允许按下
    funkey8_timer_del(my_subpage->funkey8);
    if (my_subpage->funkey8 && my_subpage->warning) {
        //让funkey8失能
        char *strarr = lvgl_module_msg_get_ptr(GUI_MODEL_SYS_SETTING_MSG_ID_FUNKEY8, 16);
        sprintf(strarr, "%s(%d)", my_subpage->funkey8, 5);
        lvgl_module_msg_send_ptr(strarr, 0);
        if (reset_update_yes) {
            lvgl_module_msg_group_add_value(sys_group, GUI_MODEL_SYS_SETTING_MSG_ID_STATE_FUNKEY8, (void *)LV_STATE_DEFAULT);
            reset_update_yes = false;
        } else {
            lvgl_module_msg_group_add_value(sys_group, GUI_MODEL_SYS_SETTING_MSG_ID_STATE_FUNKEY8, (void *)LV_STATE_DISABLED);
            funkey8_timer = lv_timer_create(funkey8_timer_cb, 1000, my_subpage->funkey8);
        }

    }

    //启用高亮样式（LV_STATE_DISABLED临时充当,注意LV_STATE_DISABLED之后控件失能状态，无法处理按键事件）
    lvgl_module_msg_group_add_value(sys_group, GUI_MODEL_SYS_SETTING_MSG_ID_STATE_FUNKEY4, (void *)LV_STATE_DEFAULT);
    lvgl_module_msg_group_add_value(sys_group, GUI_MODEL_SYS_SETTING_MSG_ID_STATE_FUNKEY5, (void *)LV_STATE_DEFAULT);
    lvgl_module_msg_group_add_value(sys_group, GUI_MODEL_SYS_SETTING_MSG_ID_STATE_FUNKEY6, (void *)LV_STATE_DEFAULT);
    lvgl_module_msg_group_add_value(sys_group, GUI_MODEL_SYS_SETTING_MSG_ID_STATE_FUNKEY7, (void *)LV_STATE_DEFAULT);
    switch (my_subpage->list_focus_id) {
    case 1:
        lv_group_focus_obj(ui_scr->sys_setting_lbl_funkey5);
        lvgl_module_msg_group_add_value(sys_group, GUI_MODEL_SYS_SETTING_MSG_ID_STATE_FUNKEY5, (void *)LV_STATE_FOCUS_KEY);
        break;
    case 2:
        lv_group_focus_obj(ui_scr->sys_setting_lbl_funkey6);
        lvgl_module_msg_group_add_value(sys_group, GUI_MODEL_SYS_SETTING_MSG_ID_STATE_FUNKEY6, (void *)LV_STATE_FOCUS_KEY);
        break;
    case 3:
        lv_group_focus_obj(ui_scr->sys_setting_lbl_funkey7);
        lvgl_module_msg_group_add_value(sys_group, GUI_MODEL_SYS_SETTING_MSG_ID_STATE_FUNKEY7, (void *)LV_STATE_FOCUS_KEY);
        break;
    default:
        lv_group_focus_obj(ui_scr->sys_setting_lbl_funkey4);
        lvgl_module_msg_group_add_value(sys_group, GUI_MODEL_SYS_SETTING_MSG_ID_STATE_FUNKEY4, (void *)LV_STATE_FOCUS_KEY);
        break;
    }
    if (my_subpage->funkey8) {
        lvgl_module_msg_group_add_global_ptr(sys_group, GUI_MODEL_SYS_SETTING_MSG_ID_FUNKEY8, my_subpage->funkey8, strlen(my_subpage->funkey8));
        lvgl_module_msg_group_add_value(sys_group, GUI_MODEL_SYS_SETTING_MSG_ID_SHOW_FUNKEY8, (void *)LV_OBJ_FLAG_HIDDEN);
    } else {
        lvgl_module_msg_group_add_value(sys_group, GUI_MODEL_SYS_SETTING_MSG_ID_HIDE_FUNKEY8, (void *)LV_OBJ_FLAG_HIDDEN);
    }
    lvgl_module_msg_group_send(sys_group, 0);


}

/*
* 系统设置菜单子页面列表样式处理、功能键数据处理
*
*/
void sysmenu_subpage_btnlist_keyevent_cb(lv_ui *ui)
{
    char *str_p = 0;
    char hour[8] = { 0 };
    char min[8] = { 0 };
    unsigned char *carnumber_cn ;
    char *carnumber_cn_init;
    int format_err, reset_err;
    lv_obj_t *focused_obj = lv_group_get_focused(lv_group_get_default());

    if (focused_obj != NULL && lv_obj_check_type(focused_obj, &lv_label_class)) {
        lv_obj_add_state(focused_obj, LV_STATE_DISABLED);
    }

    printf("[chili] %s %d   \n", __func__, __LINE__);
    lv_ui_sys_setting *ui_scr = ui_get_scr_ptr(&guider_ui, GUI_SCREEN_SYS_SETTING);
    if (!ui_scr) {
        return;
    }
#ifdef USE_LVGL_V8_UI_DEMO
    lv_group_set_default(def_group);
    lv_indev_set_group(indev_keypad, def_group);
#endif

    //根据当前子页面处理事件
    switch (my_sysmenu_subpage.now_subpage) {
    case  SUBPAGE_SAVER:
        switch (subpage_cur_btn) {
        case SUBPAGE_FUNKEY5:
            db_update("pro", 30);
            break;
        case SUBPAGE_FUNKEY6:
            db_update("pro", 60);
            break;
        case SUBPAGE_FUNKEY7:
            db_update("pro", 120);
            break;
        default:
            db_update("pro", 0);
            break;
        }
        ui_lcd_light_time_set(db_select("pro"));
        lv_group_focus_obj(ui_scr->sys_setting_img_saver);
        break;

    case  SUBPAGE_POWEROFF:
        switch (subpage_cur_btn) {
        case SUBPAGE_FUNKEY5:
            db_update("aff", 3);
            break;
        case SUBPAGE_FUNKEY6:
            db_update("aff", 5);
            break;
        case SUBPAGE_FUNKEY7:
            db_update("aff", 10);
            break;
        default:
            db_update("aff", 0);
            break;
        }

        aff_set_function(db_select("aff"));
        lv_group_focus_obj(ui_scr->sys_setting_img_2);

        break;

    case  SUBPAGE_FREQ:
        switch (subpage_cur_btn) {
        case SUBPAGE_FUNKEY5:
            db_update("fre", 60);
            break;
        default:
            db_update("fre", 50);
            break;
        }
        lv_group_focus_obj(ui_scr->sys_setting_img_3);
        break;

    case  SUBPAGE_VOLUME:
        switch (subpage_cur_btn) {
        case SUBPAGE_FUNKEY5:
            db_update("kvo", 1);
            break;
        default:
            db_update("kvo", 0);
            break;
        }
        lv_group_focus_obj(ui_scr->sys_setting_img_4);

        break;

    case  SUBPAGE_TVSYSTEM:
        switch (subpage_cur_btn) {
        case SUBPAGE_FUNKEY5:
            db_update("tvm", 1);//0 pal 1 ntsc
            break;
        default:
            db_update("tvm", 0);//0 pal 1 ntsc
            break;
        }

        break;

    case  SUBPAGE_DATA:
        switch (subpage_cur_btn) {
        case SUBPAGE_FUNKEY2:
            lv_roller_get_selected_str(ui_scr->sys_setting_roller_hour, hour, 4);
            lv_roller_get_selected_str(ui_scr->sys_setting_roller_min, min, 4);
            //datetime:2024/05/20  23: 1
            char *date = strdup(lv_label_get_text(ui_scr->sys_setting_datetext_subpage));
            str_p = strtok(date, "/");
            if (str_p) {
                db_update("datey", atoi(str_p));
            }
            str_p = strtok(NULL, "/");
            if (str_p) {
                db_update("datem", atoi(str_p));
            }
            str_p = strtok(NULL, "/");
            if (str_p) {
                db_update("dated", atoi(str_p));
            }
            db_update("dateh", atoi(hour));
            db_update("datemi", atoi(min));
            free(date);
            update_date = true;
            break;
        default:
            break;
        }
        lv_group_focus_obj(ui_scr->sys_setting_img_12);
        break;

    case  SUBPAGE_CARNUM:
        switch (subpage_cur_btn) {
        case SUBPAGE_FUNKEY2:
            carnumber_cn =  lvgl_module_msg_get_ptr(GUI_MODEL_VIDEO_REC_MSG_ID_CAR_NUNBER, 16);
            lv_dropdown_get_selected_str(ui_scr->sys_setting_ddlist_1, carnumber_cn, 4);
            lv_dropdown_get_selected_str(ui_scr->sys_setting_ddlist_2, &carnumber_cn[3], 2);
            lv_dropdown_get_selected_str(ui_scr->sys_setting_ddlist_3, &carnumber_cn[4], 2);
            lv_dropdown_get_selected_str(ui_scr->sys_setting_ddlist_4, &carnumber_cn[5], 2);
            lv_dropdown_get_selected_str(ui_scr->sys_setting_ddlist_5, &carnumber_cn[6], 2);
            lv_dropdown_get_selected_str(ui_scr->sys_setting_ddlist_6, &carnumber_cn[7], 2);
            lv_dropdown_get_selected_str(ui_scr->sys_setting_ddlist_7, &carnumber_cn[8], 2);
            printf("[chili] %s carnumber_cn:%s   \n", __func__, carnumber_cn);
            int  selected_idx = lv_dropdown_get_selected(ui_scr->sys_setting_ddlist_1);
            db_update("proc", selected_idx);
            unsigned char gb2312Data[16] = {0};
            carnum_utf8_to_gb2312((uint8_t *)carnumber_cn, (uint8_t *)gb2312Data, selected_idx);
            uint32_t *carnum_p = gb2312Data;
            db_update("cna", carnum_p[0]);
            db_update("cnb", carnum_p[1]);
            lvgl_module_msg_send_ptr(carnumber_cn, 0);
            break;
        default:
            break;
        }
        lv_group_focus_obj(ui_scr->sys_setting_img_9);
        break;

    case  SUBPAGE_LINEDRIFT:
        switch (subpage_cur_btn) {
        case SUBPAGE_FUNKEY5:
            db_update("lan", 1);
            break;
        default:
            db_update("lan", 0);
            break;
        }
        lv_group_focus_obj(ui_scr->sys_setting_img_8);

        break;

    case  SUBPAGE_HAEDLAMP:
        switch (subpage_cur_btn) {
        case SUBPAGE_FUNKEY5:
            db_update("hlw", 1);
            break;
        default:
            db_update("hlw", 0);
            break;
        }

        lv_group_focus_obj(ui_scr->sys_setting_img_6);
        break;

    case  SUBPAGE_FORMATTING:
        if (storage_device_ready() == 0) {
            //sd卡未挂载
            sys_prompt_show_ctl(3000, (void *)_("nosd"));
            return;
        }
        sys_prompt_show_ctl(30000, (void *)_("being_formatted"));
        lv_ui_sys_prompt *sys_prompt_scr = ui_get_scr_ptr(&guider_ui, GUI_SCREEN_SYS_PROMPT);
        if (!sys_prompt_scr) {
            return;
        }
        lv_obj_clear_flag(sys_prompt_scr->sys_prompt_img_warn, LV_OBJ_FLAG_CLICKABLE);
        extern void video_system_format(void);
        video_system_format();
        lv_group_focus_obj(ui_scr->sys_setting_img_10);
        break;

    case  SUBPAGE_RESET:
        reset_err = db_reset();
        update_date = true;
        carnumber_cn_init = (char *)lvgl_module_msg_get_ptr(GUI_MODEL_VIDEO_REC_MSG_ID_CAR_NUNBER, 16);
        strcpy(carnumber_cn_init, "京A00000");
        lvgl_module_msg_send_ptr(carnumber_cn_init, 0);
        lv_i18n_set_locale("zh_cn");
        i18n_refresh_all_texts(); //语言即可生效
        if (reset_err < 0) {
            sys_prompt_show_ctl(3000, (void *)_("sys_reset_failed"));
        } else {
            sys_prompt_show_ctl(3000, (void *)_("sys_reset"));
        }
        reset_update_yes = true; //表示已经reset了，不需要再发确认的模型消息
        //刷新菜单子页面标题
        my_sysmenu_subpage.icon_res_id = (void *)RES_RESET;
        my_sysmenu_subpage.title = (void *)_("reset");
        my_sysmenu_subpage.warning = (void *)_("subpagewarning2");
        my_sysmenu_subpage.funkey8 = (void *)_("YES");

        sysmenu_subpage_show(&my_sysmenu_subpage);
#ifdef USE_LVGL_V8_UI_DEMO
        lv_group_set_default(def_group);
        lv_indev_set_group(indev_keypad, def_group);
#endif
        lv_group_focus_obj(ui_scr->sys_setting_img_11);
        break;

    case  SUBPAGE_VERSION:
        lv_group_focus_obj(ui_scr->sys_setting_img_7);
        break;

    default:
        printf("[chili] %s %d  no match subpage err \n", __func__, __LINE__);
        break;
    }

}

/*
*   回放、拍照子页面的更新管理函数
*   @my_subpage 子页面更新依赖数据
*/
void subpage_show(struct subpage_data *my_subpage)
{
    printf("[chili] %s %d   \n", __func__, __LINE__);

    lvgl_module_msg_send_global_ptr(GUI_MODEL_GLOBAL_SUBPAGE_MSG_ID_SUBPAGE_ICON, my_subpage->icon_res_id, sizeof(my_subpage->icon_res_id), 0);
    lvgl_module_msg_send_global_ptr(GUI_MODEL_GLOBAL_SUBPAGE_MSG_ID_TITLE, my_subpage->title, strlen(my_subpage->title), 0);

    //roller显隐控制
    if (my_subpage->roller_opt && my_subpage->roller) {
        lvgl_module_msg_send_global_ptr(GUI_MODEL_GLOBAL_SUBPAGE_MSG_ID_SHOW_ROLLER, (void *)LV_OBJ_FLAG_HIDDEN, 1, 0);
        //配置roller被选项
        lv_roller_set_options(my_subpage->roller, my_subpage->roller_opt, LV_ROLLER_MODE_NORMAL);
        lv_roller_set_selected(my_subpage->roller, my_subpage->roller_sel, LV_ANIM_OFF);
    } else {
        lvgl_module_msg_send_global_ptr(GUI_MODEL_GLOBAL_SUBPAGE_MSG_ID_HIDE_ROLLER, (void *)LV_OBJ_FLAG_HIDDEN, 1, 0);
    }
    //显示隐藏一些功能键
    if (my_subpage->funkey1) {
        lvgl_module_msg_send_global_ptr(GUI_MODEL_GLOBAL_SUBPAGE_MSG_ID_SHOW_FUNCKEY1, (void *)LV_OBJ_FLAG_HIDDEN, 1, 0);
        lvgl_module_msg_send_global_ptr(GUI_MODEL_GLOBAL_SUBPAGE_MSG_ID_FUNCKEY1, my_subpage->funkey1, strlen(my_subpage->funkey1), 0);
    } else {
        lvgl_module_msg_send_global_ptr(GUI_MODEL_GLOBAL_SUBPAGE_MSG_ID_HIDE_FUNCKEY1, (void *)LV_OBJ_FLAG_HIDDEN, 1, 0);
    }
    if (my_subpage->funkey2) {
        lvgl_module_msg_send_global_ptr(GUI_MODEL_GLOBAL_SUBPAGE_MSG_ID_SHOW_FUNCKEY2, (void *)LV_OBJ_FLAG_HIDDEN, 1, 0);
        lvgl_module_msg_send_global_ptr(GUI_MODEL_GLOBAL_SUBPAGE_MSG_ID_FUNCKEY2, my_subpage->funkey2, strlen(my_subpage->funkey2), 0);
    } else {
        lvgl_module_msg_send_global_ptr(GUI_MODEL_GLOBAL_SUBPAGE_MSG_ID_HIDE_FUNCKEY2, (void *)LV_OBJ_FLAG_HIDDEN, 1, 0);
    }
    if (my_subpage->funkey3) {
        lvgl_module_msg_send_global_ptr(GUI_MODEL_GLOBAL_SUBPAGE_MSG_ID_SHOW_FUNCKEY3, (void *)LV_OBJ_FLAG_HIDDEN, 1, 0);
        lvgl_module_msg_send_global_ptr(GUI_MODEL_GLOBAL_SUBPAGE_MSG_ID_FUNCKEY3, my_subpage->funkey3, strlen(my_subpage->funkey3), 0);
    } else {
        lvgl_module_msg_send_global_ptr(GUI_MODEL_GLOBAL_SUBPAGE_MSG_ID_HIDE_FUNCKEY3, (void *)LV_OBJ_FLAG_HIDDEN, 1, 0);
    }
    if (my_subpage->funkey4) {
        lvgl_module_msg_send_global_ptr(GUI_MODEL_GLOBAL_SUBPAGE_MSG_ID_SHOW_FUNCKEY4, (void *)LV_OBJ_FLAG_HIDDEN, 1, 0);
        lvgl_module_msg_send_global_ptr(GUI_MODEL_GLOBAL_SUBPAGE_MSG_ID_FUNCKEY4, my_subpage->funkey4, strlen(my_subpage->funkey4), 0);
    } else {
        lvgl_module_msg_send_global_ptr(GUI_MODEL_GLOBAL_SUBPAGE_MSG_ID_HIDE_FUNCKEY4, (void *)LV_OBJ_FLAG_HIDDEN, 1, 0);
    }
    //启用高亮样式
    lvgl_module_msg_send_global_ptr(GUI_MODEL_GLOBAL_SUBPAGE_MSG_ID_STATE_FUNKEY1, (void *)LV_STATE_DEFAULT, 1, 0);
    lvgl_module_msg_send_global_ptr(GUI_MODEL_GLOBAL_SUBPAGE_MSG_ID_STATE_FUNKEY2, (void *)LV_STATE_DEFAULT, 1, 0);
    lvgl_module_msg_send_global_ptr(GUI_MODEL_GLOBAL_SUBPAGE_MSG_ID_STATE_FUNKEY3, (void *)LV_STATE_DEFAULT, 1, 0);
    lvgl_module_msg_send_global_ptr(GUI_MODEL_SYS_SETTING_MSG_ID_STATE_FUNKEY4, (void *)LV_STATE_DEFAULT, 1, 0);
    switch (my_subpage->btn_focus_id) {
    case 1:
        lvgl_module_msg_send_global_ptr(GUI_MODEL_GLOBAL_SUBPAGE_MSG_ID_STATE_FUNKEY1, (void *)LV_STATE_FOCUSED, 1, 0);
        break;
    case 2:
        lvgl_module_msg_send_global_ptr(GUI_MODEL_GLOBAL_SUBPAGE_MSG_ID_STATE_FUNKEY2, (void *)LV_STATE_FOCUSED, 1, 0);
        break;
    case 3:
        lvgl_module_msg_send_global_ptr(GUI_MODEL_GLOBAL_SUBPAGE_MSG_ID_STATE_FUNKEY3, (void *)LV_STATE_FOCUSED, 1, 0);
        break;
    case 4:
        lvgl_module_msg_send_global_ptr(GUI_MODEL_SYS_SETTING_MSG_ID_STATE_FUNKEY4, (void *)LV_STATE_FOCUSED, 1, 0);
        break;
    }
}



void hide_label_timer_cb(lv_timer_t *timer)
{
    lv_obj_t *obj = timer->user_data;
    lv_ui_video_play *ui_scr = ui_get_scr_ptr(&guider_ui, GUI_SCREEN_VIDEO_PLAY);
    if (!ui_scr) {
        return;
    }
    if (timer == ui_scr->video_play_hide_bar) {
        ui_scr->video_play_hide_bar = NULL;
    } else if (timer == ui_scr->video_play_hide_label) {
        ui_scr->video_play_hide_label = NULL;
    }
    lv_timer_del(timer);

    if (lv_obj_is_valid(obj)) {
        lv_obj_add_flag(obj, LV_OBJ_FLAG_HIDDEN);
    }
}

void reinit_sys_setting_model(void)
{
    lv_ui_sys_setting *ui_scr = ui_get_scr_ptr(&guider_ui, GUI_SCREEN_SYS_SETTING);
    if (!ui_scr) {
        return;
    }
    gui_msg_send(GUI_MODEL_GLOBAL_SUBPAGE_MSG_ID_SUBPAGE_ICON, (void *)RES_LCD_OFF, sizeof(RES_LCD_OFF));
    gui_msg_send(GUI_MODEL_GLOBAL_SUBPAGE_MSG_ID_TITLE, (void *)_("lcdprotect"), strlen(_("lcdprotect")));
    gui_msg_send(GUI_MODEL_GLOBAL_SUBPAGE_MSG_ID_HIDE_FUNCKEY1, (void *)LV_OBJ_FLAG_HIDDEN, 4);
    gui_msg_send(GUI_MODEL_GLOBAL_SUBPAGE_MSG_ID_HIDE_FUNCKEY2, (void *)LV_OBJ_FLAG_HIDDEN, 4);
    gui_msg_send(GUI_MODEL_GLOBAL_SUBPAGE_MSG_ID_HIDE_FUNCKEY3, (void *)LV_OBJ_FLAG_HIDDEN, 4);
    gui_msg_send(GUI_MODEL_SYS_SETTING_MSG_ID_HIDE_FUNKEY8, (void *)LV_OBJ_FLAG_HIDDEN, 4);

    gui_msg_send(GUI_MODEL_GLOBAL_SUBPAGE_MSG_ID_FUNCKEY4, (void *)_("close"), strlen(_("close")));
    gui_msg_send(GUI_MODEL_GLOBAL_SUBPAGE_MSG_ID_SHOW_FUNCKEY4, (void *)LV_OBJ_FLAG_HIDDEN, 4);
    gui_msg_send(GUI_MODEL_SYS_SETTING_MSG_ID_FUNKEY5, (void *)("30s"), 4);
    gui_msg_send(GUI_MODEL_SYS_SETTING_MSG_ID_SHOW_FUNKEY5, (void *)LV_OBJ_FLAG_HIDDEN, 4);
    gui_msg_send(GUI_MODEL_SYS_SETTING_MSG_ID_FUNKEY6, (void *)("60s"), 4);
    gui_msg_send(GUI_MODEL_SYS_SETTING_MSG_ID_SHOW_FUNKEY6, (void *)LV_OBJ_FLAG_HIDDEN, 4);
    gui_msg_send(GUI_MODEL_SYS_SETTING_MSG_ID_FUNKEY7, (void *)("120s"), 4);
    gui_msg_send(GUI_MODEL_SYS_SETTING_MSG_ID_SHOW_FUNKEY7, (void *)LV_OBJ_FLAG_HIDDEN, 4);

    gui_msg_send(GUI_MODEL_SYS_SETTING_MSG_ID_SHOW_VIEWLIST, (void *)LV_OBJ_FLAG_HIDDEN, 4);
    gui_msg_send(GUI_MODEL_SYS_SETTING_MSG_ID_HIDE_VIEWCARNUM, (void *)LV_OBJ_FLAG_HIDDEN, 4);
    gui_msg_send(GUI_MODEL_SYS_SETTING_MSG_ID_HIDE_VIEWDATE, (void *)LV_OBJ_FLAG_HIDDEN, 4);
    gui_msg_send(GUI_MODEL_SYS_SETTING_MSG_ID_HIDE_SUBPAGEWARNING, (void *)LV_OBJ_FLAG_HIDDEN, 4);

    gui_msg_send(GUI_MODEL_SYS_SETTING_MSG_ID_STATE_FUNKEY4, (void *)LV_STATE_DEFAULT, 4);
    gui_msg_send(GUI_MODEL_SYS_SETTING_MSG_ID_STATE_FUNKEY5, (void *)LV_STATE_DEFAULT, 4);
    gui_msg_send(GUI_MODEL_SYS_SETTING_MSG_ID_STATE_FUNKEY6, (void *)LV_STATE_DEFAULT, 4);
    gui_msg_send(GUI_MODEL_SYS_SETTING_MSG_ID_STATE_FUNKEY7, (void *)LV_STATE_DEFAULT, 4);
    switch (db_select("pro")) { //处理高亮样式
    case 30:
        lv_group_focus_obj(ui_scr->sys_setting_lbl_funkey5);
        break;
    case 60:
        lv_group_focus_obj(ui_scr->sys_setting_lbl_funkey6);
        break;
    case 120:
        lv_group_focus_obj(ui_scr->sys_setting_lbl_funkey7);
        break;
    default:
        lv_group_focus_obj(ui_scr->sys_setting_lbl_funkey4);
        break;
    }

}

#endif
