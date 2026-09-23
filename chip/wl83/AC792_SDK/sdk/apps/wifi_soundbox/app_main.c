#include "system/includes.h"
#include "app_msg.h"
#include "app_tone.h"
#include "app_config.h"
#include "os/os_api.h"
#include "event/key_event.h"
#include "event/bt_event.h"
#include "event/device_event.h"
#include "event/net_event.h"
#include "audio_config.h"
#include "mic_effect.h"
#if TCFG_LOCAL_TWS_ENABLE
#include "local_tws.h"
#endif
#if TCFG_LE_AUDIO_STREAM_ENABLE
#include "wireless_trans.h"
#endif
#if (THIRD_PARTY_PROTOCOLS_SEL & MULTI_BOX_ADV_EN)
#include "multi_box_adv/multi_box_adv.h"
#endif

/*中断列表 */
const struct irq_info irq_info_table[] = {
    //中断号   //优先级0-7   //注册的cpu(0或1)
#ifdef CONFIG_IPMASK_ENABLE
    //不可屏蔽中断方法：支持写flash，但中断函数和调用函数和const要全部放在内部ram
#if 0 //如下，SPI1使用不可屏蔽中断设置
    { IRQ_SPI1_IDX,      7,   1    },//中断强制注册到cpu0/1
#endif
#endif

    { IRQ_BT_TIMEBASE_IDX,  5,  0 },
    { IRQ_BLE_RX_IDX,       5,  0 },
    { IRQ_BLE_EVENT_IDX,    5,  0 },
    { IRQ_BT_CLKN_IDX,      5,  0 },
    { IRQ_BREDR_IDX,        5,  0 },

#if CPU_CORE_NUM == 1
    { IRQ_SOFT5_IDX,        6,  0 }, //此中断强制注册到cpu0
    { IRQ_SOFT4_IDX,        6,  1 }, //此中断强制注册到cpu1
    { -2,                  -2, -2 }, //如果加入了该行, 那么只有该行之前的中断注册到对应核, 其他所有中断强制注册到CPU0
#endif
    { -1,                  -1, -1 },
};


/*创建使用 os_task_create_static 或者task_create 接口的 静态任务堆栈*/
#define SYS_TIMER_STK_SIZE 512
#define SYS_TIMER_Q_SIZE 256
static u8 sys_timer_tcb_stk_q[sizeof(StaticTask_t) + SYS_TIMER_STK_SIZE * 4 + sizeof(struct task_queue) + SYS_TIMER_Q_SIZE] ALIGNE(4);

#define SYSTIMER_STK_SIZE 256
static u8 systimer_tcb_stk_q[sizeof(StaticTask_t) + SYSTIMER_STK_SIZE * 4] ALIGNE(4);

#define SYS_EVENT_STK_SIZE 512
static u8 sys_event_tcb_stk_q[sizeof(StaticTask_t) + SYS_EVENT_STK_SIZE * 4] ALIGNE(4);

#define APP_CORE_STK_SIZE 2048
#define APP_CORE_Q_SIZE 1024
static u8 app_core_tcb_stk_q[sizeof(StaticTask_t) + APP_CORE_STK_SIZE * 4 + sizeof(struct task_queue) + APP_CORE_Q_SIZE] ALIGNE(4);


/*任务列表 */
const struct task_info task_info_table[] = {
    { "app_core",            15,     APP_CORE_STK_SIZE,      APP_CORE_Q_SIZE,    app_core_tcb_stk_q  },
    { "sys_event",           29,     SYS_EVENT_STK_SIZE,                   0,    sys_event_tcb_stk_q },
    { "systimer",            14,     SYSTIMER_STK_SIZE,                    0,    systimer_tcb_stk_q  },
    { "sys_timer",            9,     SYS_TIMER_STK_SIZE,    SYS_TIMER_Q_SIZE,    sys_timer_tcb_stk_q },
    { "thread_fork_kill",    25,     256,      0 },
    { "dlog",                 1,     256,    128 },
#if TEE_ENABLE
    { "tee_core0",           22,    1024,      0 },
    { "tee_core1",           23,    1024,      0 },
#endif
#ifdef CONFIG_MEDIA_ENABLE
#if TCFG_ENC_AMR_16K_ENABLE //16k amr enc
    { "jlstream_",           25,    3072,      0 },
#else
    { "jlstream_",           25,     768,      0 },
#endif
    { "jlstream",            23,     768,    128 },
    { "a2dp_dec",            24,     768,      0 },
    /* file dec任务不打断jlstream任务运行,故优先级低于jlstream */
#if TCFG_DEC_AMR_16K_ENABLE //16k amr dec
    { "file_dec",            24,    1536,      0 },
#else
    { "file_dec",            24,     768,      0 },
#endif
    { "file_cache",          26,     512,      0 },
    { "write_file",          25,     512,      0 },
    { "vir_data_tx",         25,     256,      0 },
    /* 麦克风音效任务优先级要高 */
    { "mic_effect",          26,     768,      0 },
    /* 为了防止dac buf太大，通话一开始一直解码，导致编码输入数据需要很大的缓存，这里提高编码的优先级 */
    { "audio_enc",           26,     768,    128 },
    { "aec",                 26,     768,    128 },
    { "aec_dbg",             13,     512,    128 },
    { "aud_capture",         24,     512,    256 },
    { "dac",                 22,     256,    128 },
    { "spec",                 6,     512,      0 },
    { "spec_adv",             6,     512,      0 },
    { "kws",                  3,     256,     64 },
    { "smart_voice",         11,     512,    128 },
    { "audio_vad",           11,     768,      0 },
    { "key_tone",            25,     256,     32 },
    { "cvp_ref",             24,     256,    128 },
    { "CVP_RefTask",         26,     256,    128 },
#endif
    { "usb_msd",              1,     512,    128 },
    { "uda_main",             2,    7000,      0 },
    { "update",              21,     512,     32 },
    { "dw_update",           21,     512,     32 },
    { "uac_play",            26,     512,     32 },
    { "uac_record",          26,     512,      0 },
#if RCSP_MODE
    {"rcsp",                 17,     768,    128 },
#if RCSP_FILE_OPT
    {"rcsp_file_bs",         10,     768,    128 },
    {"ftran_back",           10,     768,    128 },
#endif
#endif

#ifdef CONFIG_NET_ENABLE
    { "update_rtc_task",      1,     512,      0 },
    { "ntp_client_get_time", 10,    1024,      0 },
    { "get_profile_task",    22,    3328,      0 },
    { "get_macaddr_task",    22,    1536,      0 },
    { "tcpip_thread",        16,     800,      0 },
    { "iperf_test",          15,    1024,      0 },
    { "net_download_task",   11,    1536,      0 },
    { "websocket_client_recv", 18,  1024,      0 },
    { "websocket_client_heart", 19,  1024,      0 },
#ifdef CONFIG_DUI_SDK_ENABLE
    { "dui_net_task",        20,    1536,    256 },
    { "dui_app_task",        20,    1536,    256 },
    { "dui_iot_poll_online", 21,    1024,      0 },
    { "dui_iot_ctl_proc",    20,    1024,      0 },
    { "dui_iot_parse_proc",  22,     768,      0 },
#endif
#ifdef CONFIG_TURING_SDK_ENABLE
    { "turing_app_task",     22,    1536,    128 },
    { "turing_mqtt_task",    21,    1536,      0 },
    { "wechat_api_task",     21,    1536,     64 },
    { "turing_bind_device_task", 11, 768,     64 },
#endif
#ifdef CONFIG_ALI_SDK_ENABLE
    { "ali_app_task",        20,    2048,     64 },
#endif
#ifdef CONFIG_DLNA_SDK_ENABLE
    { "RunMiniServerTask",   20,    1536,     16 },
    { "HandleRequestTask",   21,    1536,    128 },
    { "GenaNotifyTask",      23,    1024,      0 },
    { "dlna_app_task",       22,    1024,     64 },
#endif
#if TCFG_WIFI_ENABLE
    { "voiceprint",          11,    2048,     32 },
    { "change_channel",      10,    2000,      0 },
    { "tasklet",             10,    1400,      0 }, //通过调节任务优先级平衡WIFI收发占据总CPU的比重
    { "RtmpMlmeTask",        17,     768,      0 },
    { "RtmpCmdQTask",        17,     300,      0 },
    { "wl_rx_irq_thread",     7,     256,      0 },
    { "wl_rx_query_thread",   2,     256,      0 },
#endif
#if TCFG_ETH_ENABLE
    { "eth_rx_task_n",        7,     256,      0 },
#endif
#if TCFG_LTE_PHY_ENABLE
    { "lte_rx_task",          7,     256,      0 },
#endif
#endif
#ifdef CONFIG_BT_ENABLE
    { "btencry",             14,     512,    128 },
    { "btctrler",            19,     512,    384 },
    { "btstack",             18,     768,    384 },
    {"app_proto",            14,     768,     64 },
#endif
#ifdef CONFIG_VIDEO_ENABLE
    { "net_video_server",    16,     256,     64 },
    { "video_server_transfer", 23,  1024,      0 },
    { "video_server",        16,     768,    128 },
    { "vpkg_server",         16,     512,    128 },
    { "video0_rec",          20,     256,    128 },
    { "video1_rec",          20,     512,    128 },
    { "video2_rec",          20,     512,    128 },
    { "video3_rec",          20,    1024,    128 },
    { "audio0_rec",          20,    1024,    128 },
    { "audio1_rec",          20,    1024,    128 },
    { "audio2_rec",          20,    1024,    128 },
    { "audio3_rec",          20,    1024,    128 },
    { "net_avi",             18,     512,      0 },
    { "avi",                 11,     320,     64 },
    { "jpg_dec",             10,    1024,     32 },
    { "dynamic_huffman",     15,    1024,     32 },
    { "video_dec_server",    16,    1024,    256 },
    { "vunpkg_server",       16,    1024,    128 },
#endif
#ifdef CONFIG_UI_ENABLE
    { "lvgl_v8_main_task",   25,    8192,   1024 },
#endif

    {0, 0},
};

void app_default_volume_change_handler(int inc)
{
    if (inc) {
        app_audio_volume_up(10);
    } else {
        app_audio_volume_down(10);

        if (app_audio_get_volume(APP_AUDIO_CURRENT_STATE) == app_audio_get_max_volume()) {
            if (tone_player_runing() == 0) {
#if TCFG_MAX_VOL_PROMPT
                play_tone_file(get_tone_files()->max_vol);
#endif
            }
        }
    }

#if TCFG_LOCAL_TWS_ENABLE || TCFG_LOCAL_TWS_SYNC_VOL
    local_tws_sync_vol();
#endif
#if (THIRD_PARTY_PROTOCOLS_SEL & MULTI_BOX_ADV_EN)
    multi_box_bis_change_volume_notify();
#endif
}

static int poweroff_tone_play_end_callback(void *priv, enum stream_event event)
{
    if (event == STREAM_EVENT_STOP) {
        void power_set_soft_poweroff(u32 ms);
        power_set_soft_poweroff(0);
    }

    return 0;
}

static void app_default_key_click(struct key_event *key)
{
    switch (key->value) {
    case KEY_OK:
        break;
    case KEY_VOLUME_DEC:
    case KEY_UP:
    case KEY_PREV:
        app_default_volume_change_handler(0);
        break;
    case KEY_VOLUME_INC:
    case KEY_DOWN:
    case KEY_NEXT:
        app_default_volume_change_handler(1);
        break;
    case KEY_MODE:
        app_mode_change_next();
        break;
    case KEY_POWER:
        if (0 != play_tone_file_alone_callback(get_tone_files()->power_off, NULL, poweroff_tone_play_end_callback)) {
            poweroff_tone_play_end_callback(NULL, STREAM_EVENT_STOP);
        }
        break;
    default:
        break;
    }
}

static void app_default_key_long(struct key_event *key)
{
    switch (key->value) {
    case KEY_OK:
#if TCFG_MIC_EFFECT_ENABLE
        if (mic_effect_player_runing()) {
            mic_effect_player_close();
        } else {
            mic_effect_player_open();
        }
#endif
        break;
    default:
        break;
    }
}

static void app_default_key_event_handler(struct key_event *key)
{
    switch (key->action) {
    case KEY_EVENT_CLICK:
        app_default_key_click(key);
        break;
    case KEY_EVENT_LONG:
        app_default_key_long(key);
        break;
    case KEY_EVENT_HOLD:
        break;
    default:
        break;
    }
}

/*
 * 默认的系统事件处理函数
 * 当所有活动的app的事件处理函数都返回false时此函数会被调用
 */
void app_default_event_handler(struct sys_event *event)
{
    const struct app_event_handler *handler;

    for_each_app_event_handler(handler) {
        if (event->type == handler->event && handler->from == event->from) {
            handler->handler(event->payload);
        }
    }

    switch (event->type) {
    case SYS_KEY_EVENT:
        app_default_key_event_handler((struct key_event *)event->payload);
        break;
    case SYS_TOUCH_EVENT:
        break;
    case SYS_DEVICE_EVENT:
        break;
    case SYS_NET_EVENT:
        break;
    case SYS_BT_EVENT:
        break;
    default:
        ASSERT(0, "unknow event type: %s\n", __func__);
        break;
    }
}

static int poweron_tone_play_end_callback(void *priv, enum stream_event event)
{
    if (event == STREAM_EVENT_STOP) {
        app_mode_change(APP_MODE_BT);
    }

    return 0;
}

/*
 * 应用程序主函数
 */
void app_main(void)
{
    puts("------------- wifi_soundbox app main-------------\n");

#ifdef USE_LVGL_V8_UI_DEMO
    int lvgl_main_task_init(void);
    lvgl_main_task_init();
#endif

    int ret = play_tone_file_callback(get_tone_files()->power_on, NULL, poweron_tone_play_end_callback);
    if (ret) {
        poweron_tone_play_end_callback(NULL, STREAM_EVENT_STOP);
    }
}

