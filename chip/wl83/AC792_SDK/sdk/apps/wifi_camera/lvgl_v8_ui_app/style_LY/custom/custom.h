#include "app_config.h"
#ifdef CONFIG_UI_STYLE_LY_ENABLE
#ifndef __CUSTOM_H_
#define __CUSTOM_H_
#ifdef __cplusplus
extern "C" {
#endif

#include "../generated/gui_guider.h"
#include "lvgl.h"
#include "custom.h"
#include "app_msg.h"
#include <time.h>
#include "../generated/gui_events/screen_handler.h"
#include "../generated/gui_timelines/gui_timelines.h"
#include "sim_database.h"//仿真专用数据库

#if !LV_USE_GUIBUILDER_SIMULATOR
#include "key_event.h"
#include "ui.h"
#include "../generated/gui_res/res_common.h"
#include "../generated/gui_msg/gui_msg.h"
#endif

//子菜单页面枚举
enum MENU_SUBPAGE {
    //录像设置子界面
    SUBPAGE_RESOLUTION,
    SUBPAGE_DOUBLE_REC,
    SUBPAGE_CYC_REC,
    SUBPAGE_GAP,
    SUBPAGE_HDR,
    SUBPAGE_EXPOSURE,
    SUBPAGE_MOTION,
    SUBPAGE_DATE,
    SUBPAGE_GSENSOR,
    SUBPAGE_RECORD,
    SUBPAGE_GUARD,
    SUBPAGE_CARNUM,
    SUBPAGE_HAEDLAMP,
    //拍照设置子界面
    //SUBPAGE_RESOLUTION,
    SUBPAGE_SHOOT,
    SUBPAGE_SHOTS,
    SUBPAGE_QUALITY,
    SUBPAGE_SHARPNESS,
    SUBPAGE_AWB,
    SUBPAGE_COLOR,
    SUBPAGE_ISO,
    //SUBPAGE_EXPOSURE,
    SUBPAGE_HANDSHAKE,
    SUBPAGE_PREVIEW,
    //SUBPAGE_DATE
    //菜单页面
    SUBPAGE_SAVER,
    SUBPAGE_POWEROFF,
    SUBPAGE_FREQ,
    SUBPAGE_VOLUME,
    SUBPAGE_LANGUAGE,
    SUBPAGE_TVSYSTEM,
    SUBPAGE_DATA,
    //SUBPAGE_CARNUM,
    SUBPAGE_LINEDRIFT,
    SUBPAGE_FORMATTING,
    SUBPAGE_RESET,
    SUBPAGE_VERSION,
    //回放页面
    SUBPAGE_DELETE,
    SUBPAGE_PROTECTION
};

enum {//子页面功能键
    SUBPAGE_FUNKEY_NULL,
    SUBPAGE_FUNKEY1,
    SUBPAGE_FUNKEY2,
    SUBPAGE_FUNKEY3,
    SUBPAGE_FUNKEY4,
    SUBPAGE_FUNKEY5,
    SUBPAGE_FUNKEY6,
    SUBPAGE_FUNKEY7
};

enum {//语言
    LANG_CHINESE_SIMP = 1,
    LANG_ENGLISH
};

struct sysmenu_subpage_data {
    void *funkey1;//功能按键1文字内容（填空就是不显示）
    void *funkey2;
    void *funkey3;
    void *funkey4;
    void *time_num_view;//rtc时间设置
    void *warning;//警告语
    void *roller_opt;//按照1,2,3格式传入显示roller（填空就是不显示）
    void *roller;//roller控件句柄
    int roller_sel;//roller被选项
    int btn_focus_id;//功能按键高亮id
    int now_subpage;
    uint32_t menu_index; //菜单序号
};

struct subpage_data {
    void *funkey1;//功能按键1文字内容（填空就是不显示）
    void *funkey2;
    void *funkey3;
    void *funkey4;
    void *roller_opt;//按照1,2,3格式传入显示roller（填空就是不显示）
    void *roller;//roller控件句柄
    void *car_num_view;
    int btn_focus_id;//功能按键高亮id
    int roller_sel;//roller被选项
    int now_subpage;//enum MENU_VIDEOPHOTO_SUBPAGE
    uint32_t menu_index; //菜单序号
};

struct dec_submenu_data {
    void *funkey1;
    void *funkey2;
    void *funkey3;
    void *funkey4;
    void *warning;
    int btn_focus_id;
    int now_subpage;
    uint32_t menu_index; //菜单序号
};

struct photo_submenu_data {
    void *funkey1;
    void *funkey2;
    void *funkey3;
    void *funkey4;
    void *roller_opt;//按照1,2,3格式传入显示roller（填空就是不显示）
    void *roller;//roller控件句柄
    int roller_sel;//roller被选项
    int btn_focus_id;
    int now_subpage;
    uint32_t menu_index; //菜单序号
};

extern struct subpage_data rec_subpage_data; //录像设置子页面显示更新数据
extern struct dec_submenu_data dec_subpage_data;  //回放设置菜单
extern struct photo_submenu_data photo_subpage_data;  //拍照设置菜单
extern struct sysmenu_subpage_data my_sysmenu_subpage;  //系统设置菜单
extern char user_roller_str[128];//记录roller被选项
extern int subpage_cur_btn;//子页面当前被按下的按键 0无按下 1~n代表funkey1~n


/*
* 录像启停控制--控件触摸事件回调
*/
void rec_control_ontouch(void);

/*
* 录像模式视窗切换控制--控件触摸事件回调
*/
void rec_switch_win_ontouch(void);

/*
* 录像模式文件加锁--控件触摸事件回调
*/

void rec_set_lock_ontouch(void);

/*
* 格式化卡
*/
int sdcard_storage_device_format(const char *sd_name);

/*
*   子页面的更新管理函数
*   @my_subpage 子页面更新依赖数据
*/
void subpage_show(struct subpage_data *my_subpage);

/*
*更新预览界面图标
* @arg1 icon:菜单子页面作为更新预览界面图标的依据 比如SUBPAGE_RESOLUTION就是对应预览界面下的分辨率图标
* return void
*/
void video_rec_icon_reshow(int icon);

/*
*更新拍照预览界面图标
* @arg1 icon:菜单子页面作为更新预览界面图标的依据 比如SUBPAGE_RESOLUTION就是对应预览界面下的分辨率图标
* return void
*/
void video_photo_icon_reshow(int icon);

/*
* 系统设置菜单子页面列表样式处理、数据处理
*
*/
void sysmenu_subpage_btnlist_keyevent_cb(lv_ui *ui);

/*
*   系统菜单子页面的更新管理函数
*   @my_subpage 子页面更新依赖数据
*/
void sysmenu_subpage_show(struct sysmenu_subpage_data *my_subpage);

void set_dec_submenu_flag(uint8_t data);
uint8_t get_dec_submenu_flag(void);
void format_sdcard(void);
void setting_reset(void);
void custom_init(lv_ui *ui);
void hide_label_timer_cb(lv_timer_t *timer);


#if !LV_USE_GUIBUILDER_SIMULATOR
void set_menu_status(int data);
void rec_lock_setting(void);
#endif

#ifdef __cplusplus
}
#endif
#endif /* EVENT_CB_H_ */

#endif
