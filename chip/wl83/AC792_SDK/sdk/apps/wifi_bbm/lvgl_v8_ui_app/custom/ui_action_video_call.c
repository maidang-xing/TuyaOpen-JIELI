#include <stdio.h>
#include "lvgl.h"
#include "gui_guider.h"

#if !LV_USE_GUIBUILDER_SIMULATOR
#include "app_core.h"
#include "app_config.h"
#include "action.h"
#include "ui.h"
#include "wifi_raw.h"

extern void wifi_get_tx_stats(u32 *TxRetransmit, u32 *TxSuccess, u32 *TxFailCount);
extern char wifi_raw_rssi_get(void);

static int video_call_key_handler(struct key_event *key)
{
    //全部按键事件交给app core处理
    return 1;
}
REGISTER_UI_KEY_EVENT_HANDLER(GUI_SCREEN_VIDEO_CALL)
.key_onchange = video_call_key_handler,
};


//调试接口：设置视频通话界面的视频帧率显示
void gui_video_call_set_video_fps_label(int fps)
{
    char label_len = 16;
    char *lab = lvgl_module_msg_get_ptr(GUI_VIDEO_CALL_MSG_ID_VIDEO_FPS_DEBUG, label_len);
    if (!lab) {
        printf("gui video call get label ptr failed\n");
        return;
    }
    snprintf(lab, label_len, "FPS:%d", fps);
    lvgl_module_msg_send_ptr(lab, 0);
}

int gui_video_call_msg_wifi_stats_debug_cb(gui_msg_action_t access, gui_msg_data_t *data, gui_msg_data_type_t type)
{
    static char *wifi_stats_debug_var = NULL;
    int buff_size = 256;
    if (access == GUI_MSG_ACCESS_GET) {
        if (wifi_stats_debug_var == NULL) {
            wifi_stats_debug_var = lv_mem_alloc(buff_size);
        }
        //获取wifi状态调试信息接口

        u32 retry, succ, fail;
        wifi_get_tx_stats(&retry, &succ, &fail);
        char rssi = wifi_raw_rssi_get();
        const char *txrate = wifi_raw_get_txrate_str();
        u8 short_retry = wifi_raw_get_short_retry();
        u8 long_retry = wifi_raw_get_long_retry();
        u8 ch = wifi_get_channel();
        u8 pwr = wifi_raw_get_pwr();

        snprintf(wifi_stats_debug_var, buff_size, "ch:%d\ntxrate:%s\nretry: s=%d l=%d\nrssi: %d pwr:%d\nr:%d s:%d f:%d",
                 ch, txrate, short_retry, long_retry, rssi, pwr, retry, succ, fail);

    }
    if (access == GUI_MSG_ACCESS_SET) {
        lv_mem_free(wifi_stats_debug_var);
        wifi_stats_debug_var = lv_mem_alloc(strlen(data->value_string) + 1);
        strcpy(wifi_stats_debug_var, data->value_string);
    }
    data->value_string = wifi_stats_debug_var;
    return 0;
}


int gui_video_call_msg_wifi_rssi_cb(gui_msg_action_t access, gui_msg_data_t *data, gui_msg_data_type_t type)
{
    static int32_t wifi_rssi_var = 0;
    if (access == GUI_MSG_ACCESS_GET) {
        char rssi = wifi_raw_rssi_get();
        if (rssi >= -20) {
            wifi_rssi_var = 4;
        } else if (rssi >= -40) {
            wifi_rssi_var = 3;
        } else if (rssi >= -50) {
            wifi_rssi_var = 2;
        } else if (rssi >= -60) {
            wifi_rssi_var = 1;
        } else {
            wifi_rssi_var = 0;
        }
    }
    data->value_int = wifi_rssi_var;
    return 0;
}

REGISTER_UI_MODULE_EVENT_HANDLER(GUI_VIDEO_CALL_MSG_ID_WIFI_RSSI)
.onchange = gui_video_call_msg_wifi_rssi_cb,
};

REGISTER_UI_MODULE_EVENT_HANDLER(GUI_VIDEO_CALL_MSG_ID_WIFI_STATS_DEBUG)
.onchange = gui_video_call_msg_wifi_stats_debug_cb,
};

#endif