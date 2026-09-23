/**
 * @file custom.c
 *
 */

/*********************
 *      INCLUDES
 *********************/
#include "lvgl.h"
#include "custom.h"
#include <time.h>
#include "app_config.h"

/*********************
 *      DEFINES
 *********************/

/**********************
 *      TYPEDEFS
 **********************/

/**********************
 *  STATIC PROTOTYPES
 **********************/

/**********************
 *  STATIC VARIABLES
 **********************/

/**
 * Create a demo application
 */

void custom_init(lv_ui *ui)
{
    /* Add your codes here */

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
#endif
/*
*	模式post消息给UI，执行UI动作
*
*/

#ifdef USE_LVGL_V8_UI_DEMO
void bt_music_post_msg_to_ui(const char *msg, ...)
{
    if (!storage_device_ready()) {
        printf("SD card is not online!, please insert SD Card!\n");
        return;
    }

    va_list argptr;

    printf("[chili] %s %s   \n", __func__, msg);
    va_start(argptr, msg);

    if (strstr(msg, "music_state_off")) {
        //暂停
        ui_music_pause_handler();
    } else if (strstr(msg, "music_state_on")) {
        //播放音乐
        ui_music_on_handler();
    } else if (strstr(msg, "music_tol_time")) {
        //总时长
        ui_music_tol_time_handler(va_arg(argptr, int));
    } else if (strstr(msg, "music_cur_time")) {
        //当前时长
        ui_music_cur_time_handler(va_arg(argptr, int));
    } else if (strstr(msg, "music_lyrics")) {

        ui_music_lyrics_handler(va_arg(argptr, char *));
    } else if (strstr(msg, "music_artist")) {
        /* 歌手/歌名 要用“/”切割出来 */
        ui_music_artist_handler(va_arg(argptr, char *));
    } else if (strstr(msg, "music_album_pic")) {
        lvgl_rpc_post_func(ui_music_album_pic_handler, 0);
    } else if (strstr(msg, "music_volume")) {
        ui_music_volume_handler(va_arg(argptr, int));
    } else if (strstr(msg, "player_state")) {
        //播放器状态(单曲循环/...)
    } else if (strstr(msg, "music_spectrum")) {
        // 频谱数据 - 这里传递指针
        float (*db_data)[MAX_SPECTRUM_SECTION_NUM] = va_arg(argptr, float(*)[MAX_SPECTRUM_SECTION_NUM]);
        ui_music_spectrum_handler(db_data);
    } else {
        printf("[chili] %s your msg [%s] no callback! \n", __func__, msg, __LINE__);
    }

    va_end(argptr);
}
#endif

