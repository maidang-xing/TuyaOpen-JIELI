#include "app_config.h"
#ifdef CONFIG_UI_STYLE_LY_ENABLE
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
#include "sys_time.h"
#include "system/includes.h"
#include "asm/includes.h"
#include "include/action.h"
#endif
/*********************
 *      DEFINES
 *********************/

/**********************
*      TYPEDEFS
**********************/



struct subpage_data rec_subpage_data = { 0 };//录像设置子页面显示更新数据
struct sysmenu_subpage_data my_sysmenu_subpage = { 0 };//菜单设置子页面显示更新数据
struct dec_submenu_data dec_subpage_data = { 0 };  //回放模式
struct photo_submenu_data photo_subpage_data = { 0 };  //拍照模式

char user_roller_str[128] = { 0 };//记录roller被选项
int subpage_cur_btn = SUBPAGE_FUNKEY_NULL;//子页面当前被按下的按键 0无按下 1~n代表funkey1~n
bool usb_flag = false;
bool update_date = false; //true时表示需要更新 rtc 时间，默认初始化时需要更新
extern char video_rec_car_num[64];

//=======================================================//
// LVGL按键值重新映射函数:
// 用户可以在custom.c中实现该函数把LVGL的按键重新映射
// key_value为映射前的键值，key_remap为映射后的键值
//=======================================================//
#if !LV_USE_GUIBUILDER_SIMULATOR


int ui_scr_key_event_handler_ext(struct key_event *event)
{
    switch (event->value) {
    case KEY_POWER:
        if (event->action == KEY_EVENT_LONG) {
            return 1;
        }
        return 0;
    default :
        return 0;
    }
}


uint8_t dec_submenu_flag = 0;
void set_dec_submenu_flag(uint8_t data)  //进入dec设置的子单位置1，退出置0
{
    dec_submenu_flag = data;
}

uint8_t get_dec_submenu_flag(void)
{
    return dec_submenu_flag;
}


static bool is_area_in(const lv_area_t *outer, const lv_area_t *inner)
{
    return (inner->x1 >= outer->x1 && inner->x2 <= outer->x2 &&
            inner->y1 >= outer->y1 && inner->y2 <= outer->y2);
}

//判断按键聚焦的对象是否在显示范围内，不在则进行处理
void key_scroll_to_view(void)
{
    lv_obj_t *focused_obj = lv_group_get_focused(lv_group_get_default());
    if (focused_obj == NULL) {
        return;
    }
    lv_obj_t *focused_obj_parent = lv_obj_get_parent(focused_obj);

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

static int jude_focused_obj_type(void)
{
    int ret = 0;
    lv_obj_t *focused_obj = NULL;
    focused_obj = lv_group_get_focused(lv_group_get_default());
    if (focused_obj) {
        ret = lv_obj_check_type(focused_obj, &lv_roller_class);  //滚动框
        // printf("%s()--->ret: %d\n", __func__, ret);
        if (ret) {
            return ret;
        }
        ret = lv_obj_check_type(focused_obj, &lv_dropdown_class);  //下拉框
        // printf("%s()--->ret: %d\n", __func__, ret);
        if (ret) {
            return ret;
        }
    }
    return 0;
}

void lvgl_key_value_remap(uint8_t key_value, uint32_t *key_remap)
{
    switch (key_value) {
    case KEY_MODE:
        *key_remap = LV_KEY_RIGHT;  //对应机器的模式（mode）键
        break;
    case KEY_MENU:
        *key_remap = LV_KEY_HOME;  //对应机器的菜单（menu）键
        break;
    case KEY_UP:
        key_scroll_to_view();
        if (jude_focused_obj_type()) {
            *key_remap = LV_KEY_UP;
        } else {
            *key_remap = LV_KEY_PREV;
        }
        break;
    case KEY_DOWN:
        key_scroll_to_view();
        if (jude_focused_obj_type()) {
            *key_remap = LV_KEY_DOWN;
        } else {
            *key_remap = LV_KEY_NEXT;
        }
        break;
    case KEY_OK:
        *key_remap = LV_KEY_ENTER;
        break;
    default://KEY_OK
        *key_remap = LV_KEY_ENTER;
        break;
    }
    printf("--->key_value: %d, key_remap: %d\n", key_value, *key_remap);
}

int key_event_remap(struct key_event *e)
{
    printf("=====>%s()--->key action: %d, value: %d\n", __func__, e->action, e->value);
    if (e->value == KEY_POWER) {
        if (e->action == KEY_EVENT_LONG) {
            e->value = KEY_POWER;
        } else {
            e->value = KEY_MODE;
        }

    }
    return true;
}

#if 1

#if 0
static int rec_menu_status(void)
{
#if 0
    int flag0 = 0, flag1 = 0;

    if (lv_obj_is_valid(ui_scr->video_rec_view_menu)) {
        if (!lv_obj_has_flag(ui_scr->video_rec_view_menu, LV_OBJ_FLAG_HIDDEN)) {
            flag0 = 1;
        } else {
            flag0 = 0;
        }
        printf(">>>>>flag0: %d\n", flag0);
    }

    if (lv_obj_is_valid(ui_scr->sys_setting_view_menu)) {
        if (!lv_obj_has_flag(ui_scr->sys_setting_view_menu, LV_OBJ_FLAG_HIDDEN)) {
            flag1 = 1;
        } else {
            flag1 = 0;
        }
        printf(">>>>>flag1: %d\n", flag1);
    }

    printf("---->flag: %d, flag0: %d, flag1: %d\n", (flag0 || flag1), flag0, flag1);
    return (flag0 || flag1);
#else
    int flag = 0;

    if (lv_obj_is_valid(ui_scr->video_rec_view_scan)) {
        printf("--->%s()----->%d\n", __func__, __LINE__);
        if (lv_obj_has_flag(ui_scr->video_rec_view_scan, LV_OBJ_FLAG_HIDDEN)) {
            flag = 1;
        } else {
            flag = 0;
        }
    } else {
        flag = 1;
    }
    printf(">>>>>flag: %d\n", flag);
    return flag;
#endif
}
#endif

static int menu_status = 0;
void set_menu_status(int data)
{
    menu_status = data;
}

int get_menu_status(void)
{
    return menu_status;
}

extern unsigned char rec_running;
static int key_filter_event_handler(struct sys_event *e)
{
    struct key_event *key = (struct key_event *)e->payload;
    // printf(">>>%s()-----key action: %d, value: %d\n", __func__, key->action, key->value);
    /* 开录像状态下，过滤掉menu按键消息，但在菜单页面下已经是录像状态，则不过滤 */
    if (rec_running && (key->value == KEY_MENU)) {
        if (get_menu_status()) {
            return 0;
        } else {
            return -EINVAL;  //过滤掉menu按键消息，不发给UI
        }
    } else if (rec_running && (key->value == KEY_MODE)) {
        if (key->action == KEY_EVENT_DOWN) {
            rec_lock_setting();
        }
        return -EINVAL;  //过滤掉按键消息，不发给UI
    }

    /* 菜单页面下，过滤掉mode键消息 */
    if (get_menu_status() && (key->value == KEY_MODE)) {
        return -EINVAL;
    }
    return 0;
}

SYS_EVENT_STATIC_HANDLER_REGISTER(key_menu_handler, 2) = {
    .event_type = SYS_KEY_EVENT,
    .prob_handler = key_filter_event_handler,
    .post_handler = NULL,
};
#endif

#endif


/**
 * Create a demo application
 */

void custom_init(lv_ui *ui)
{
    /* Add your codes here */
    printf("[chili] %s %d   \n", __func__, __LINE__);
}


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

int lvgl_module_msg_send_string(unsigned int msg_id, const void *value, char refr_now)
{
    gui_msg_send(msg_id, value, strlen(value));
}

int lvgl_module_msg_send_value(unsigned int msg_id, unsigned int value, char refr_now)
{
    gui_msg_send(msg_id, value, sizeof(unsigned int));
}

#define SDX_DEV                 "sdx"


/*
* 格式化卡
*/
int sdcard_storage_device_format(const char *sd_name)
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
    return 0;
}

void video_dec_edit_files(uint8_t mode)
{

}

void edit_lock_file(lv_obj_t *dest, int dir)
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
#endif








void setting_reset(void)
{
    int reset_err = 0;
    char *carnumber_cn_init;

    reset_err = db_reset();

    update_date = true;  //rtc时间

    /* 车牌 */
    carnumber_cn_init = (char *)lvgl_module_msg_get_ptr(GUI_MODEL_VIDEO_REC_MSG_ID_CAR_NUNBER, 16);
    strcpy(carnumber_cn_init, "京A00000");
    lvgl_module_msg_send_ptr(carnumber_cn_init, 0);

    /* 语言 */
    lv_i18n_set_locale("zh_cn");
    i18n_refresh_all_texts(); //语言即可生效

    if (reset_err < 0) {
        sys_prompt_show_ctl(3000, (void *)_("sys_reset_failed"));
    } else {
        sys_prompt_show_ctl(3000, (void *)_("sys_reset"));
    }
}



void hide_label_timer_cb(lv_timer_t *timer)
{
    // 隐藏标签
    lv_timer_del(timer);
    lv_ui_video_play *ui_scr = ui_get_scr_ptr(&guider_ui, GUI_SCREEN_VIDEO_PLAY);
    if (!ui_scr) {
        return;
    }
    if (lv_obj_is_valid(ui_scr->video_play_lbl_msg)) {
        lv_obj_add_flag(ui_scr->video_play_lbl_msg, LV_OBJ_FLAG_HIDDEN);
    }
}

static void update_btn_label(lv_obj_t *btn_obj, const char *btn_text)
{
    lv_obj_t *label_obj = lv_obj_get_child(btn_obj, 0);
    lv_label_set_text(label_obj, btn_text);
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
        gb2312_data[0] = 0xBE;
        gb2312_data[1] = 0xA9;
        break;
    case 33:
        gb2312_data[0] = 0xB0;
        gb2312_data[1] = 0xC4;
        break;
    }
    for (int i = 2; i < 16; i++) {
        gb2312_data[i] = utf_8[i + 1];

    }
}

//sd卡状态图标更新
void post_msg2sd_icon(int online)
{
#ifdef USE_LVGL_V8_UI_DEMO
    if (online) {
        lvgl_module_msg_send_global_ptr(GUI_MODEL_VIDEO_REC_MSG_ID_SD_ICON, (void *)RES_CARD_ONLINE, sizeof(RES_CARD_ONLINE), 0);
    } else {
        lvgl_module_msg_send_global_ptr(GUI_MODEL_VIDEO_REC_MSG_ID_SD_ICON, (void *)RES_CARD_OFFLINE, sizeof(RES_CARD_OFFLINE), 0);
    }
#endif // USE_LVGL_V8_UI_DEMO
}

/*
*   二级菜单更新管理，根据不同的一级菜单选项显示相应的二级菜单选项
*   @my_subpage 子页面更新依赖数据
*/
void subpage_show(struct subpage_data *my_subpage)
{
    lv_ui_video_rec *ui_scr = ui_get_scr_ptr(&guider_ui, GUI_SCREEN_VIDEO_REC);
    if (!ui_scr) {
        return;
    }
    printf("[chili] %s %d   \n", __func__, __LINE__);

    //roller显隐控制
    if (my_subpage->roller_opt && my_subpage->roller) {
        lv_obj_clear_flag(ui_scr->video_rec_roller_mutifunc, LV_OBJ_FLAG_HIDDEN);
        //配置roller被选项
        lv_roller_set_options(my_subpage->roller, my_subpage->roller_opt, LV_ROLLER_MODE_INFINITE);
        lv_roller_set_selected(my_subpage->roller, my_subpage->roller_sel, LV_ANIM_OFF);
        lv_group_focus_obj(ui_scr->video_rec_roller_mutifunc);
        printf("[chili] %s %d   \n", __func__, __LINE__);
    } else {
        lv_obj_add_flag(ui_scr->video_rec_roller_mutifunc, LV_OBJ_FLAG_HIDDEN);
    }

    //车牌设置区域
    if (my_subpage->car_num_view) {
        lv_obj_clear_flag(ui_scr->video_rec_view_carnum, LV_OBJ_FLAG_HIDDEN);
#if !LV_USE_GUIBUILDER_SIMULATOR
        set_car_num_part_a(db_select("cna"));
        set_car_num_part_b(db_select("cnb"));
        lv_dropdown_set_selected(ui_scr->video_rec_ddlist_1, db_select("proc"));
        lv_dropdown_set_selected(ui_scr->video_rec_ddlist_2, (video_rec_car_num[3] - 'A'));
        lv_dropdown_set_selected(ui_scr->video_rec_ddlist_3, (video_rec_car_num[4] - '0'));
        lv_dropdown_set_selected(ui_scr->video_rec_ddlist_4, (video_rec_car_num[5] - '0'));
        lv_dropdown_set_selected(ui_scr->video_rec_ddlist_5, (video_rec_car_num[6] - '0'));
        lv_dropdown_set_selected(ui_scr->video_rec_ddlist_6, (video_rec_car_num[7] - '0'));
        lv_dropdown_set_selected(ui_scr->video_rec_ddlist_7, (video_rec_car_num[8] - '0'));
#endif
        lv_group_focus_obj(ui_scr->video_rec_ddlist_1);
    } else {
        lv_obj_add_flag(ui_scr->video_rec_view_carnum, LV_OBJ_FLAG_HIDDEN);
    }

    //显示或隐藏子菜单的功能键，以及显示功能键的内容
    if (my_subpage->funkey1) {
        lv_obj_clear_flag(ui_scr->video_rec_rec_submenu_btn_1, LV_OBJ_FLAG_HIDDEN);
        update_btn_label(ui_scr->video_rec_rec_submenu_btn_1, (char *)my_subpage->funkey1);
    } else {
        lv_obj_add_flag(ui_scr->video_rec_rec_submenu_btn_1, LV_OBJ_FLAG_HIDDEN);
    }
    if (my_subpage->funkey2) {
        lv_obj_clear_flag(ui_scr->video_rec_rec_submenu_btn_2, LV_OBJ_FLAG_HIDDEN);
        update_btn_label(ui_scr->video_rec_rec_submenu_btn_2, (char *)my_subpage->funkey2);
    } else {
        lv_obj_add_flag(ui_scr->video_rec_rec_submenu_btn_2, LV_OBJ_FLAG_HIDDEN);
    }
    if (my_subpage->funkey3) {
        lv_obj_clear_flag(ui_scr->video_rec_rec_submenu_btn_3, LV_OBJ_FLAG_HIDDEN);
        update_btn_label(ui_scr->video_rec_rec_submenu_btn_3, (char *)my_subpage->funkey3);
    } else {
        lv_obj_add_flag(ui_scr->video_rec_rec_submenu_btn_3, LV_OBJ_FLAG_HIDDEN);
    }
    if (my_subpage->funkey4) {
        lv_obj_clear_flag(ui_scr->video_rec_rec_submenu_btn_4, LV_OBJ_FLAG_HIDDEN);
        update_btn_label(ui_scr->video_rec_rec_submenu_btn_4, (char *)my_subpage->funkey4);
    } else {
        lv_obj_add_flag(ui_scr->video_rec_rec_submenu_btn_4, LV_OBJ_FLAG_HIDDEN);
    }

    //高亮子菜单相应的功能键
    printf(">>>btn_focus_id: %d\n", my_subpage->btn_focus_id);
    switch (my_subpage->btn_focus_id) {
    case SUBPAGE_FUNKEY1:
        lv_group_focus_obj(ui_scr->video_rec_rec_submenu_btn_1);
        break;
    case SUBPAGE_FUNKEY2:
        lv_group_focus_obj(ui_scr->video_rec_rec_submenu_btn_2);
        break;
    case SUBPAGE_FUNKEY3:
        lv_group_focus_obj(ui_scr->video_rec_rec_submenu_btn_3);
        break;
    case SUBPAGE_FUNKEY4:
        lv_group_focus_obj(ui_scr->video_rec_rec_submenu_btn_4);
        break;
    }
}

void photo_submenu_update(struct photo_submenu_data *my_subpage)
{
    printf("[chili] %s %d   \n", __func__, __LINE__);
    lv_ui_video_photo *ui_scr = ui_get_scr_ptr(&guider_ui, GUI_SCREEN_VIDEO_PHOTO);
    if (!ui_scr) {
        return;
    }
    //roller显隐控制
    if (my_subpage->roller_opt && my_subpage->roller) {
        lv_obj_clear_flag(ui_scr->video_photo_roller_mutifunc, LV_OBJ_FLAG_HIDDEN);
        //配置roller被选项
        lv_roller_set_options(my_subpage->roller, my_subpage->roller_opt, LV_ROLLER_MODE_INFINITE);
        lv_roller_set_selected(my_subpage->roller, my_subpage->roller_sel, LV_ANIM_OFF);
        lv_group_focus_obj(ui_scr->video_photo_roller_mutifunc);
        printf("[chili] %s %d   \n", __func__, __LINE__);
    } else {
        lv_obj_add_flag(ui_scr->video_photo_roller_mutifunc, LV_OBJ_FLAG_HIDDEN);
    }

    //显示或隐藏子菜单的功能键，以及显示功能键的内容
    if (my_subpage->funkey1) {
        lv_obj_clear_flag(ui_scr->video_photo_submenu_btn_1, LV_OBJ_FLAG_HIDDEN);
        update_btn_label(ui_scr->video_photo_submenu_btn_1, (char *)my_subpage->funkey1);
    } else {
        lv_obj_add_flag(ui_scr->video_photo_submenu_btn_1, LV_OBJ_FLAG_HIDDEN);
    }
    if (my_subpage->funkey2) {
        lv_obj_clear_flag(ui_scr->video_photo_submenu_btn_2, LV_OBJ_FLAG_HIDDEN);
        update_btn_label(ui_scr->video_photo_submenu_btn_2, (char *)my_subpage->funkey2);
    } else {
        lv_obj_add_flag(ui_scr->video_photo_submenu_btn_2, LV_OBJ_FLAG_HIDDEN);
    }
    if (my_subpage->funkey3) {
        lv_obj_clear_flag(ui_scr->video_photo_submenu_btn_3, LV_OBJ_FLAG_HIDDEN);
        update_btn_label(ui_scr->video_photo_submenu_btn_3, (char *)my_subpage->funkey3);
    } else {
        lv_obj_add_flag(ui_scr->video_photo_submenu_btn_3, LV_OBJ_FLAG_HIDDEN);
    }
    if (my_subpage->funkey4) {
        lv_obj_clear_flag(ui_scr->video_photo_submenu_btn_4, LV_OBJ_FLAG_HIDDEN);
        update_btn_label(ui_scr->video_photo_submenu_btn_4, (char *)my_subpage->funkey4);
    } else {
        lv_obj_add_flag(ui_scr->video_photo_submenu_btn_4, LV_OBJ_FLAG_HIDDEN);
    }

    //高亮子菜单相应的功能键
    printf(">>>btn_focus_id: %d\n", my_subpage->btn_focus_id);
    switch (my_subpage->btn_focus_id) {
    case SUBPAGE_FUNKEY1:
        lv_group_focus_obj(ui_scr->video_photo_submenu_btn_1);
        break;
    case SUBPAGE_FUNKEY2:
        lv_group_focus_obj(ui_scr->video_photo_submenu_btn_2);
        break;
    case SUBPAGE_FUNKEY3:
        lv_group_focus_obj(ui_scr->video_photo_submenu_btn_3);
        break;
    case SUBPAGE_FUNKEY4:
        lv_group_focus_obj(ui_scr->video_photo_submenu_btn_4);
        break;
    }
}

void decmenu_subpage_show(struct dec_submenu_data *my_subpage)
{
    lv_ui_video_file *ui_scr = ui_get_scr_ptr(&guider_ui, GUI_SCREEN_VIDEO_FILE);
    if (!ui_scr) {
        return;
    }
    printf("[chili] %s %d   \n", __func__, __LINE__);
    //警告提示语
    if (my_subpage->warning) {
        lv_obj_clear_flag(ui_scr->video_file_lbl_submenu_warning, LV_OBJ_FLAG_HIDDEN);
        lv_label_set_text(ui_scr->video_file_lbl_submenu_warning, (char *)my_subpage->warning);
    } else {
        lv_obj_add_flag(ui_scr->video_file_lbl_submenu_warning, LV_OBJ_FLAG_HIDDEN);
    }

    //显示或隐藏子菜单的功能键，以及显示功能键的内容
    if (my_subpage->funkey1) {
        lv_obj_clear_flag(ui_scr->video_file_submenu_btn_1, LV_OBJ_FLAG_HIDDEN);

        update_btn_label(ui_scr->video_file_submenu_btn_1, (char *)my_subpage->funkey1);
    } else {
        lv_obj_add_flag(ui_scr->video_file_submenu_btn_1, LV_OBJ_FLAG_HIDDEN);
    }
    if (my_subpage->funkey2) {
        lv_obj_clear_flag(ui_scr->video_file_submenu_btn_2, LV_OBJ_FLAG_HIDDEN);
        update_btn_label(ui_scr->video_file_submenu_btn_2, (char *)my_subpage->funkey2);
    } else {
        lv_obj_add_flag(ui_scr->video_file_submenu_btn_2, LV_OBJ_FLAG_HIDDEN);
    }
    if (my_subpage->funkey3) {
        lv_obj_clear_flag(ui_scr->video_file_submenu_btn_3, LV_OBJ_FLAG_HIDDEN);
        update_btn_label(ui_scr->video_file_submenu_btn_3, (char *)my_subpage->funkey3);
    } else {
        lv_obj_add_flag(ui_scr->video_file_submenu_btn_3, LV_OBJ_FLAG_HIDDEN);
    }
    if (my_subpage->funkey4) {
        lv_obj_clear_flag(ui_scr->video_file_submenu_btn_4, LV_OBJ_FLAG_HIDDEN);
        update_btn_label(ui_scr->video_file_submenu_btn_4, (char *)my_subpage->funkey4);
    } else {
        lv_obj_add_flag(ui_scr->video_file_submenu_btn_4, LV_OBJ_FLAG_HIDDEN);
    }

    //高亮子菜单相应的功能键
    printf(">>>btn_focus_id: %d\n", my_subpage->btn_focus_id);
    switch (my_subpage->btn_focus_id) {
    case SUBPAGE_FUNKEY1:
        lv_group_focus_obj(ui_scr->video_file_submenu_btn_1);
        break;
    case SUBPAGE_FUNKEY2:
        lv_group_focus_obj(ui_scr->video_file_submenu_btn_2);
        break;
    case SUBPAGE_FUNKEY3:
        lv_group_focus_obj(ui_scr->video_file_submenu_btn_3);
        break;
    case SUBPAGE_FUNKEY4:
        lv_group_focus_obj(ui_scr->video_file_submenu_btn_4);
        break;
    }
}

#if !LV_USE_GUIBUILDER_SIMULATOR
static int ui_update_rtc_time(void)
{
    struct sys_time time;
    lv_ui_sys_setting *ui_scr = ui_get_scr_ptr(&guider_ui, GUI_SCREEN_SYS_SETTING);
    if (!ui_scr) {
        return -1;
    }
    void *fd = dev_open("rtc", NULL);
    if (fd) {
        dev_ioctl(fd, IOCTL_GET_SYS_TIME, (u32)&time);
        printf("cur rtc time: %d/%d/%d %d:%d:%d\n", time.year, time.month, time.day, time.hour, time.min, time.sec);
        lv_dropdown_set_selected(ui_scr->sys_setting_ddlist_year, time.year - 2024);
        lv_dropdown_set_selected(ui_scr->sys_setting_ddlist_month, time.month - 1);
        lv_dropdown_set_selected(ui_scr->sys_setting_ddlist_day, time.day - 1);
        lv_dropdown_set_selected(ui_scr->sys_setting_ddlist_hour, time.hour);
        lv_dropdown_set_selected(ui_scr->sys_setting_ddlist_min, time.min);
        lv_dropdown_set_selected(ui_scr->sys_setting_ddlist_sec, time.sec);
        dev_close(fd);
    }
    return 0;
}
#endif
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
    printf("[chili] %s %d   \n", __func__, __LINE__);
    //roller显隐控制
    if (my_subpage->roller_opt && my_subpage->roller) {
        lv_obj_clear_flag(ui_scr->sys_setting_roller_mutifunc, LV_OBJ_FLAG_HIDDEN);
        //配置roller被选项
        lv_roller_set_options(my_subpage->roller, my_subpage->roller_opt, LV_ROLLER_MODE_INFINITE);
        lv_roller_set_selected(my_subpage->roller, my_subpage->roller_sel, LV_ANIM_OFF);
        lv_group_focus_obj(ui_scr->sys_setting_roller_mutifunc);
        printf("[chili] %s %d   \n", __func__, __LINE__);
    } else {
        lv_obj_add_flag(ui_scr->sys_setting_roller_mutifunc, LV_OBJ_FLAG_HIDDEN);
    }

    //警告提示语
    if (my_subpage->warning) {
        lv_obj_clear_flag(ui_scr->sys_setting_lbl_submenu_warning, LV_OBJ_FLAG_HIDDEN);
        lv_label_set_text(ui_scr->sys_setting_lbl_submenu_warning, (char *)my_subpage->warning);
        //开关焦点功能，默认不开
        switch (my_subpage->now_subpage) {
        case SUBPAGE_VERSION:
            lv_group_add_obj(lv_group_get_default(), ui_scr->sys_setting_lbl_submenu_warning);
            // lv_group_focus_obj(ui_scr->sys_setting_lbl_submenu_warning);
            break;
        default:
            lv_group_remove_obj(ui_scr->sys_setting_lbl_submenu_warning);
            break;
        }
    } else {
        lv_obj_add_flag(ui_scr->sys_setting_lbl_submenu_warning, LV_OBJ_FLAG_HIDDEN);
    }

    //时间设置区域
    if (my_subpage->time_num_view) {
        lv_obj_clear_flag(ui_scr->sys_setting_view_time_mun, LV_OBJ_FLAG_HIDDEN);
        lv_group_focus_obj(ui_scr->sys_setting_ddlist_year);
#if !LV_USE_GUIBUILDER_SIMULATOR
        ui_update_rtc_time();
#endif
    } else {
        lv_obj_add_flag(ui_scr->sys_setting_view_time_mun, LV_OBJ_FLAG_HIDDEN);
    }

    //显示或隐藏子菜单的功能键，以及显示功能键的内容
    if (my_subpage->funkey1) {
        lv_obj_clear_flag(ui_scr->sys_setting_submenu_btn_1, LV_OBJ_FLAG_HIDDEN);
        update_btn_label(ui_scr->sys_setting_submenu_btn_1, (char *)my_subpage->funkey1);
    } else {
        lv_obj_add_flag(ui_scr->sys_setting_submenu_btn_1, LV_OBJ_FLAG_HIDDEN);
    }
    if (my_subpage->funkey2) {
        lv_obj_clear_flag(ui_scr->sys_setting_submenu_btn_2, LV_OBJ_FLAG_HIDDEN);
        update_btn_label(ui_scr->sys_setting_submenu_btn_2, (char *)my_subpage->funkey2);
    } else {
        lv_obj_add_flag(ui_scr->sys_setting_submenu_btn_2, LV_OBJ_FLAG_HIDDEN);
    }
    if (my_subpage->funkey3) {
        lv_obj_clear_flag(ui_scr->sys_setting_submenu_btn_3, LV_OBJ_FLAG_HIDDEN);
        update_btn_label(ui_scr->sys_setting_submenu_btn_3, (char *)my_subpage->funkey3);
    } else {
        lv_obj_add_flag(ui_scr->sys_setting_submenu_btn_3, LV_OBJ_FLAG_HIDDEN);
    }
    if (my_subpage->funkey4) {
        lv_obj_clear_flag(ui_scr->sys_setting_submenu_btn_4, LV_OBJ_FLAG_HIDDEN);
        update_btn_label(ui_scr->sys_setting_submenu_btn_4, (char *)my_subpage->funkey4);
    } else {
        lv_obj_add_flag(ui_scr->sys_setting_submenu_btn_4, LV_OBJ_FLAG_HIDDEN);
    }

    //高亮子菜单相应的功能键
    printf(">>>btn_focus_id: %d\n", my_subpage->btn_focus_id);
    switch (my_subpage->btn_focus_id) {
    case SUBPAGE_FUNKEY1:
        lv_group_focus_obj(ui_scr->sys_setting_submenu_btn_1);
        break;
    case SUBPAGE_FUNKEY2:
        lv_group_focus_obj(ui_scr->sys_setting_submenu_btn_2);
        break;
    case SUBPAGE_FUNKEY3:
        lv_group_focus_obj(ui_scr->sys_setting_submenu_btn_3);
        break;
    case SUBPAGE_FUNKEY4:
        lv_group_focus_obj(ui_scr->sys_setting_submenu_btn_4);
        break;
    }
}





#endif
