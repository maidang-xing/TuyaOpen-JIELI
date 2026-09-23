#include "system/includes.h"
#include "le_broadcast.h"
#include "app_le_broadcast.h"
#include "app_config.h"
#include "btstack/avctp_user.h"
#include "app_tone.h"
#include "app_msg.h"
#include "wireless_trans.h"
#include "le_audio_recorder.h"
#include "audio_config.h"
#include "a2dp_player.h"
#include "pc_spk_player.h"
#include "file_player.h"
#include "net_file_player.h"
#include "vol_sync.h"
#include "user_cfg_id.h"
#include "syscfg/syscfg_id.h"
#include "event/bt_event.h"
#if (BT_AI_SEL_PROTOCOL & RCSP_MODE_EN)
#include "ble_rcsp_server.h"
#endif

#if (TCFG_LEA_BIG_CTRLER_TX_EN || TCFG_LEA_BIG_CTRLER_RX_EN)

#define LOG_TAG             "[APP_LE_BROADCAST]"
#define LOG_ERROR_ENABLE
#define LOG_DEBUG_ENABLE
#define LOG_INFO_ENABLE
/* #define LOG_DUMP_ENABLE */
#define LOG_CLI_ENABLE
#include "debug.h"


enum {
    ///0x1000起始为了不要跟提示音的IDEX_TONE_重叠了
    TONE_INDEX_BROADCAST_OPEN = 0x1000,
    TONE_INDEX_BROADCAST_CLOSE,
};

struct app_bis_hdl_t {
    u8 bis_status;
    u8 remote_dev;
    u16 bis_hdl;
    u16 aux_hdl;
    audio_param_t enc;
};

struct app_big_hdl_t {
    u8 used;
    u8 big_status;
    u8 big_hdl;
    u8 local_dev;
    struct app_bis_hdl_t bis_hdl_info[BIG_MAX_BIS_NUMS];
};

/**************************************************************************************************
  Local Function Prototypes
**************************************************************************************************/
static void broadcast_pair_tx_event_callback(const PAIR_EVENT event, void *priv);
static void broadcast_pair_rx_event_callback(const PAIR_EVENT event, void *priv);
static int broadcast_padv_data_deal(void *priv);
static void remote_dev_msg_status_sync_info_send(u16 acl_hdl);

/**************************************************************************************************
  Local Global Variables
**************************************************************************************************/
static OS_MUTEX mutex;
static u8 broadcast_last_role = 0; /*!< 挂起前广播角色 */
static u8 broadcast_app_mode_exit = 0;  /*!< 音源模式退出标志 */
static u8 bis_connected_nums = 0;
static struct broadcast_sync_info app_broadcast_data_sync;  /*!< 用于记录广播同步状态 */
static struct app_big_hdl_t app_big_hdl_info[BIG_MAX_NUMS];
static u8 config_broadcast_as_master = 0;   /*!< 配置广播强制做主机 */
static u8 receiver_connected_status = 0; /*< 广播接收端连接状态 */
static u8 app_broadcast_init_flag = 0;
static int cur_deal_scene = -1; /*< 当前系统处于的运行场景 */
static u8 bis_switch_onoff = 0;
static const pair_callback_t pair_tx_cb = {
    .pair_event_cb = broadcast_pair_tx_event_callback,
};
static const pair_callback_t pair_rx_cb = {
    .pair_event_cb = broadcast_pair_rx_event_callback,
};

#if TCFG_COMMON_CASE_EN && (TCFG_COMMON_CASE_NAME == 0x1)
static u8 save_sync_status_table[5][2] = {0};
#endif

/**************************************************************************************************
  Function Declarations
**************************************************************************************************/

/* --------------------------------------------------------------------------*/
/**
 * @brief 申请互斥量，用于保护临界区代码，与app_broadcast_mutex_post成对使用
 *
 * @param mutex:已创建的互斥量指针变量
 */
/* ----------------------------------------------------------------------------*/
static inline void app_broadcast_mutex_pend(OS_MUTEX *mutex, u32 line)
{
    if (!app_broadcast_init_flag) {
        log_error("%s err, mutex uninit", __FUNCTION__);
        return;
    }

    int os_ret;
    os_ret = os_mutex_pend(mutex, 0);
    if (os_ret != OS_NO_ERR) {
        log_error("%s err, os_ret:0x%x", __FUNCTION__, os_ret);
        ASSERT(os_ret != OS_ERR_PEND_ISR, "line:%d err, os_ret:0x%x", line, os_ret);
    }
}

/* --------------------------------------------------------------------------*/
/**
 * @brief 释放互斥量，用于保护临界区代码，与app_broadcast_mutex_pend成对使用
 *
 * @param mutex:已创建的互斥量指针变量
 */
/* ----------------------------------------------------------------------------*/
static inline void app_broadcast_mutex_post(OS_MUTEX *mutex, u32 line)
{
    if (!app_broadcast_init_flag) {
        log_error("%s err, mutex uninit", __FUNCTION__);
        return;
    }

    int os_ret = os_mutex_post(mutex);
    if (os_ret != OS_NO_ERR) {
        log_error("%s err, os_ret:0x%x", __FUNCTION__, os_ret);
        ASSERT(os_ret != OS_ERR_PEND_ISR, "line:%d err, os_ret:0x%x", line, os_ret);
    }
}

/* --------------------------------------------------------------------------*/
/**
 * @brief BIG开关提示音结束回调接口
 *
 * @param priv:传递的参数
 * @param event:提示音回调事件
 *
 * @return
 */
/* ----------------------------------------------------------------------------*/
static int broadcast_tone_play_end_callback(void *priv, enum stream_event event)
{
    u32 index = (u32)priv;

    /* g_printf("%s, event:0x%x", __FUNCTION__, event); */

    switch (event) {
    case STREAM_EVENT_NONE:
    case STREAM_EVENT_STOP:
        switch (index) {
        case TONE_INDEX_BROADCAST_OPEN:
            log_info("TONE_INDEX_BROADCAST_OPEN");
            break;
        case TONE_INDEX_BROADCAST_CLOSE:
            log_info("TONE_INDEX_BROADCAST_CLOSE");
            break;
        default:
            break;
        }
    default:
        break;
    }

    return 0;
}

/* --------------------------------------------------------------------------*/
/**
 * @brief 用于外部重新打开发送端的数据流
 */
/* ----------------------------------------------------------------------------*/
void app_broadcast_reset_transmitter(void)
{
    if (get_broadcast_role() == BROADCAST_ROLE_TRANSMITTER) {
        for (u8 i = 0; i < BIG_MAX_NUMS; i++) {
            //固定收发角色重启广播数据流
            broadcast_audio_recorder_reset(app_big_hdl_info[i].big_hdl);
        }
    }
}

static void app_broadcast_big_event_transmitter_connect_handler(big_hdl_t *hdl)
{
    u8 find = 0;

    //由于是异步操作需要加互斥量保护，避免broadcast_close的代码与其同时运行,添加的流程请放在互斥量保护区里面
    app_broadcast_mutex_pend(&mutex, __LINE__);

    for (u8 i = 0; i < BIG_MAX_NUMS; i++) {
        if (app_big_hdl_info[i].used && (app_big_hdl_info[i].big_hdl == hdl->big_hdl)) {
            app_big_hdl_info[i].local_dev = WIRELESS_TX_DEV1;
            for (u8 j = 0; j < BIG_MAX_BIS_NUMS; j++) {
                if (!app_big_hdl_info[i].bis_hdl_info[j].bis_hdl)     {
                    app_big_hdl_info[i].bis_hdl_info[j].bis_hdl = hdl->bis_hdl[0];
                    app_big_hdl_info[i].bis_hdl_info[j].aux_hdl = hdl->aux_hdl;
                    app_big_hdl_info[i].bis_hdl_info[j].remote_dev = WIRELESS_RX_DEV1;
                    memcpy(&app_big_hdl_info[i].bis_hdl_info[j].enc, &hdl->enc, sizeof(audio_param_t));
                    find = 1;
                    break;
                }
            }
        }
        if (find) {
            break;
        }
    }

    if (!find) {
        //释放互斥量
        app_broadcast_mutex_post(&mutex, __LINE__);
        return;
    }

#if TCFG_AUTO_SHUT_DOWN_TIME
    sys_auto_shut_down_disable();
#endif

    u32 bitrate = get_big_audio_coding_bit_rate();
#if (TCFG_LEA_TX_CHANNEL_SEPARATION && (TCFG_LE_AUDIO_CODEC_CHANNEL == 2))
    app_broadcast_data_sync.bit_rate = bitrate / 2;
#else
    app_broadcast_data_sync.bit_rate = bitrate;
#endif
    app_broadcast_data_sync.coding_type = TCFG_LE_AUDIO_CODEC_TYPE;
    app_broadcast_data_sync.sample_rate = TCFG_LE_AUDIO_CODEC_SAMPLERATE;
    broadcast_set_sync_data(hdl->big_hdl, &app_broadcast_data_sync, sizeof(struct broadcast_sync_info));

    app_mode_t mode = get_current_app_mode();

    int ret = broadcast_transmitter_connect_deal((void *)hdl, mode);
    if (ret < 0) {
        log_error("broadcast_transmitter_connect_deal fail");
    }

    app_broadcast_mutex_post(&mutex, __LINE__);
}

static void app_broadcast_big_event_receiver_connect_handler(big_hdl_t *hdl)
{
    u8 find = 0;

    //由于是异步操作需要加互斥量保护，避免broadcast_close的代码与其同时运行,添加的流程请放在互斥量保护区里面
    app_broadcast_mutex_pend(&mutex, __LINE__);

    receiver_connected_status = 1;

#if (!TCFG_KBOX_1T3_MODE_EN)
    //接收端更新同步广播发送端的参数
    update_receiver_big_params(hdl->enc.max_sdu, hdl->enc.sdu_int_us);
#endif

    for (u8 i = 0; i < BIG_MAX_NUMS; i++) {
        if (app_big_hdl_info[i].used && (app_big_hdl_info[i].big_hdl == hdl->big_hdl)) {
            app_big_hdl_info[i].local_dev = WIRELESS_RX_DEV1;
            for (u8 j = 0; j < BIG_MAX_BIS_NUMS; j++) {
                if (!app_big_hdl_info[i].bis_hdl_info[j].bis_hdl)     {
                    app_big_hdl_info[i].bis_hdl_info[j].bis_hdl = hdl->bis_hdl[0];
                    app_big_hdl_info[i].bis_hdl_info[j].aux_hdl = hdl->aux_hdl;
                    app_big_hdl_info[i].bis_hdl_info[j].remote_dev = WIRELESS_TX_DEV1 << j;
                    memcpy(&app_big_hdl_info[i].bis_hdl_info[j].enc, &hdl->enc, sizeof(audio_param_t));
                    find = 1;
                    break;
                }
            }
        }
        if (find) {
            break;
        }
    }

    if (!find) {
        //释放互斥量
        app_broadcast_mutex_post(&mutex, __LINE__);
        return;
    }

#if TCFG_AUTO_SHUT_DOWN_TIME
    sys_auto_shut_down_disable();
#endif

    log_info("big_hdl:0x%x, bis_hdl:0x%x, aux_hdl:0x%x", hdl->big_hdl, hdl->bis_hdl[0], hdl->aux_hdl);

#if TCFG_KBOX_1T3_MODE_EN
    bis_connected_nums++;
    ASSERT(bis_connected_nums <= BIG_MAX_BIS_NUMS && bis_connected_nums >= 0, "bis_connected_nums:%d", bis_connected_nums);
#endif

    int ret = broadcast_receiver_connect_deal((void *)hdl);
    if (ret < 0) {
        log_error("broadcast_receiver_connect_deal fail");
    }

#if TCFG_COMMON_CASE_EN && (TCFG_COMMON_CASE_NAME == 0x1)
    if (bis_connected_nums > 1) {
        for (i = 0; i < BIG_MAX_NUMS; i++) {
            for (j = 0; j < BIG_MAX_BIS_NUMS; j++) {
                remote_dev_msg_status_sync_info_send(app_big_hdl_info[i].bis_hdl_info[j].aux_hdl);
            }
        }
    }
#endif

    app_broadcast_mutex_post(&mutex, __LINE__);
}

static void app_broadcast_big_event_disconnect_handler(big_hdl_t *hdl)
{
    u8 find = 0;

    //由于是异步操作需要加互斥量保护，避免broadcast_close的代码与其同时运行,添加的流程请放在互斥量保护区里面
    app_broadcast_mutex_pend(&mutex, __LINE__);

    receiver_connected_status = 0;

    for (u8 i = 0; i < BIG_MAX_NUMS; i++) {
        if (app_big_hdl_info[i].used && (app_big_hdl_info[i].big_hdl == hdl->big_hdl)) {
            for (u8 j = 0; j < BIG_MAX_BIS_NUMS; j++) {
#if TCFG_KBOX_1T3_MODE_EN
                if (app_big_hdl_info[i].bis_hdl_info[j].bis_hdl == hdl->bis_hdl[0]) {
                    app_big_hdl_info[i].bis_hdl_info[j].bis_hdl = 0;
                    app_big_hdl_info[i].bis_hdl_info[j].aux_hdl = 0;
                    app_big_hdl_info[i].bis_hdl_info[j].remote_dev = 0;
                    find = 1;
                    break;
                }
#else
                app_big_hdl_info[i].bis_hdl_info[j].bis_hdl = 0;
                app_big_hdl_info[i].bis_hdl_info[j].aux_hdl = 0;
                app_big_hdl_info[i].bis_hdl_info[j].remote_dev = 0;
                find = 1;
                break;
#endif
            }
        }
        if (find) {
            break;
        }
    }

    if (!find) {
        //释放互斥量
        app_broadcast_mutex_post(&mutex, __LINE__);
        return;
    }

#if TCFG_AUTO_SHUT_DOWN_TIME
    sys_auto_shut_down_enable();   // 恢复自动关机
#endif

    log_info("big_hdl:0x%x, bis_hdl:0x%x, aux_hdl:0x%x", hdl->big_hdl, hdl->bis_hdl[0], hdl->aux_hdl);

#if TCFG_KBOX_1T3_MODE_EN
    bis_connected_nums--;
    ASSERT(bis_connected_nums <= BIG_MAX_BIS_NUMS && bis_connected_nums >= 0, "bis_connected_nums:%d", bis_connected_nums);
#endif

    int ret = broadcast_receiver_disconnect_deal((void *)hdl);
    if (ret < 0) {
        log_error("broadcast_receiver_disconnect_deal fail");
    }

    app_broadcast_mutex_post(&mutex, __LINE__);
}

/* --------------------------------------------------------------------------*/
/**
 * @brief BIG状态事件处理函数
 *
 * @param msg:状态事件附带的返回参数
 *
 * @return
 */
/* ----------------------------------------------------------------------------*/
static int app_broadcast_conn_status_event_handler(void *evt)
{
    int *msg = (int *)evt;
    int event = msg[0];
    big_hdl_t *hdl = (big_hdl_t *)&msg[1];

    switch (event) {
    case BIG_EVENT_TRANSMITTER_CONNECT:
        log_info("BIG_EVENT_TRANSMITTER_CONNECT");
        app_broadcast_big_event_transmitter_connect_handler(hdl);
        break;

    case BIG_EVENT_RECEIVER_CONNECT:
        log_info("BIG_EVENT_RECEIVER_CONNECT");
        app_broadcast_big_event_receiver_connect_handler(hdl);
        break;

    case BIG_EVENT_PERIODIC_DISCONNECT:
    case BIG_EVENT_RECEIVER_DISCONNECT:
        log_info("BIG_EVENT_RECEIVER_DISCONNECT");
        app_broadcast_big_event_disconnect_handler(hdl);
        break;

    case BIG_EVENT_CUSTOM_DATA_SYNC:
        log_info("BIG_EVENT_PADV_DATA_SYNC");
        broadcast_padv_data_deal((void *)&msg[1]);
        break;

    default:
        break;
    }

    return FALSE;
}

REGISTER_APP_EVENT_HANDLER(app_broadcast_conn_status_event) = {
    .event      = SYS_BT_EVENT,
    .from       = BT_EVENT_FROM_BIG,
    .handler    = app_broadcast_conn_status_event_handler,
};

/* --------------------------------------------------------------------------*/
/**
 * @brief 判断当前设备作为广播发送设备还是广播接收设备
 *
 * @return true:发送设备，false:接收设备
 */
/* ----------------------------------------------------------------------------*/
static bool is_broadcast_as_transmitter(void)
{
#if (TCFG_LEA_BIG_FIX_ROLE == 1)
    return true;
#elif (TCFG_LEA_BIG_FIX_ROLE == 2)
    return false;
#endif

    app_mode_t cur_mode = get_current_app_mode();

    //当前处于蓝牙模式并且已连接手机设备时，
    //(1)播歌作为广播发送设备；
    //(2)暂停作为广播接收设备。
    if ((cur_mode == APP_MODE_BT) &&
        (bt_get_connect_status() != BT_STATUS_WAITINT_CONN)) {
        if ((bt_a2dp_get_status() == BT_MUSIC_STATUS_STARTING && bt_get_connect_status() == BT_STATUS_PLAYING_MUSIC) ||
            get_a2dp_decoder_status() ||
            a2dp_player_runing()) {
            return true;
        } else {
            return false;
        }
    }

#if TCFG_APP_LINEIN_EN
    if (cur_mode == APP_MODE_LINEIN)  {
        extern bool linein_get_status(void);
        if (linein_get_status() || config_broadcast_as_master) {
            return true;
        } else {
            return false;
        }
    }
#endif

#if TCFG_APP_IIS_EN
    if (cur_mode == APP_MODE_IIS)  {
        if (iis_get_status() || config_broadcast_as_master) {
            return true;
        } else {
            return false;
        }
    }
#endif

#if TCFG_APP_MIC_EN
    if (cur_mode == APP_MODE_MIC)  {
        if (mic_get_status() || config_broadcast_as_master) {
            return true;
        } else {
            return false;
        }
    }
#endif

#if TCFG_APP_MUSIC_EN
    if (cur_mode == APP_MODE_LOCAL) {
        if ((music_file_get_player_status(get_music_file_player()) == FILE_PLAYER_START) || config_broadcast_as_master) {
            return true;
        } else {
            return false;
        }
    }
#endif

#if TCFG_APP_NET_MUSIC_EN
    if (cur_mode == APP_MODE_NET) {
        if (net_file_get_player_status(get_net_file_player()) == FILE_PLAYER_START || config_broadcast_as_master) {
            return true;
        } else {
            return false;
        }
    }
#endif

#if TCFG_APP_FM_EN
    //当处于下面几种模式时，作为广播发送设备
    if (cur_mode == APP_MODE_FM)  {
        if (fm_get_fm_dev_mute() == 0 || config_broadcast_as_master) {
            return true;
        } else {
            return false;
        }
    }
#endif

#if TCFG_APP_SPDIF_EN
    //当处于下面几种模式时，作为广播发送设备
    if (cur_mode == APP_MODE_SPDIF) {
        //由于spdif 是先打开数据源然后再打开数据流的顺序，具有一定的滞后性，所以不能用 函数 spdif_player_runing 函数作为判断依据
        /* if (spdif_player_runing() ||  config_broadcast_as_master) { */
        if (!get_spdif_mute_state()) {
            y_printf("spdif_player_runing?\n");
            return true;
        } else {
            return false;
        }
    }
#endif

#if TCFG_APP_PC_EN
    //当处于下面几种模式时，作为广播发送设备
    if (cur_mode == APP_MODE_PC) {
#if defined(TCFG_USB_SLAVE_AUDIO_SPK_ENABLE) && TCFG_USB_SLAVE_AUDIO_SPK_ENABLE
        if (pc_spk_player_runing() || config_broadcast_as_master) {
            return true;
        } else {
            return false;
        }
#else
        return false;
#endif
    }
#endif

    return false;
}

/* --------------------------------------------------------------------------*/
/**
 * @brief 检测广播当前是否处于挂起状态
 *
 * @return true:处于挂起状态，false:处于非挂起状态
 */
/* ----------------------------------------------------------------------------*/
static bool is_need_resume_broadcast(void)
{
    u8 find = 0;

    for (u8 i = 0; i < BIG_MAX_NUMS; i++) {
        if (app_big_hdl_info[i].big_status == APP_BROADCAST_STATUS_SUSPEND) {
            find = 1;
            break;
        }
    }

    return find;
}

/* --------------------------------------------------------------------------*/
/**
 * @brief 广播从挂起状态恢复
 */
/* ----------------------------------------------------------------------------*/
static void app_broadcast_resume(void)
{
    big_parameter_t *params;

    if (!is_need_resume_broadcast()) {
        return;
    }

    app_broadcast_open();
}

/* --------------------------------------------------------------------------*/
/**
 * @brief 广播进入挂起状态
 */
/* ----------------------------------------------------------------------------*/
static void app_broadcast_suspend(void)
{
    u8 find = 0;

    for (u8 i = 0; i < BIG_MAX_NUMS; i++) {
        if (app_big_hdl_info[i].used) {
            find = 1;
            break;
        }
    }

    if (find) {
        broadcast_last_role = get_broadcast_role();
        app_broadcast_close(APP_BROADCAST_STATUS_SUSPEND);
    }
}

/* --------------------------------------------------------------------------*/
/**
 * @brief 开启广播
 *
 * @return >=0:success
 */
/* ----------------------------------------------------------------------------*/
int app_broadcast_open(void)
{
    u8 big_available_num = 0;
    int temp_broadcast_hdl = 0;
    big_parameter_t *params;

    if (!app_broadcast_init_flag) {
        return -EPERM;
    }

    for (u8 i = 0; i < BIG_MAX_NUMS; i++) {
        if (!app_big_hdl_info[i].used) {
            big_available_num++;
        }
    }

    if (!big_available_num) {
        return -EPERM;
    }

    app_mode_t mode = get_current_app_mode();
    if (mode && (mode == APP_MODE_BT) &&
        (bt_get_call_status() != BT_CALL_HANGUP)) {
        return -EPERM;
    }

    bis_switch_onoff = 1;

    log_info("broadcast_open");

    app_broadcast_mutex_pend(&mutex, __LINE__);

#if TCFG_KBOX_1T3_MODE_EN
    le_audio_ops_register(APP_MODE_NULL);
#endif

    if (is_broadcast_as_transmitter()) {
        //初始化广播发送端参数
        params = set_big_params(mode, BROADCAST_ROLE_TRANSMITTER, 0);

        //打开big，打开成功后会在函数app_broadcast_conn_status_event_handler做后续处理
        temp_broadcast_hdl = broadcast_transmitter(params);
    } else {
        //初始化广播接收端参数
        params = set_big_params(mode, BROADCAST_ROLE_RECEIVER, 0);

        //打开big，打开成功后会在函数app_broadcast_conn_status_event_handler做后续处理
        temp_broadcast_hdl = broadcast_receiver(params);
    }

    if (temp_broadcast_hdl >= 0) {
        for (u8 i = 0; i < BIG_MAX_NUMS; i++) {
            if (!app_big_hdl_info[i].used) {
                app_big_hdl_info[i].big_hdl = temp_broadcast_hdl;
                app_big_hdl_info[i].big_status = APP_BROADCAST_STATUS_START;
                app_big_hdl_info[i].used = 1;
                break;
            }
        }
    }

    app_broadcast_mutex_post(&mutex, __LINE__);

    return temp_broadcast_hdl;
}

/* --------------------------------------------------------------------------*/
/**
 * @brief 固定角色（0：接收端，1：发射端）开启广播
 *
 * @return >=0:success
 */
/* ----------------------------------------------------------------------------*/
int app_broadcast_open_with_role(u8 role)
{
    u8 big_available_num = 0;
    int temp_broadcast_hdl = 0;
    big_parameter_t *params;

    if (!app_broadcast_init_flag) {
        return -EPERM;
    }

    for (u8 i = 0; i < BIG_MAX_NUMS; i++) {
        if (!app_big_hdl_info[i].used) {
            big_available_num++;
        }
    }

    if (!big_available_num) {
        return -EPERM;
    }

    app_mode_t mode = get_current_app_mode();
    if (mode && (mode == APP_MODE_BT) &&
        (bt_get_call_status() != BT_CALL_HANGUP)) {
        return -EPERM;
    }

    bis_switch_onoff = 1;

    log_info("broadcast_open_with_role %d", role);

    app_broadcast_mutex_pend(&mutex, __LINE__);

#if TCFG_KBOX_1T3_MODE_EN
    le_audio_ops_register(APP_MODE_NULL);
#endif

    if (role) {
        //初始化广播发送端参数
        params = set_big_params(mode, BROADCAST_ROLE_TRANSMITTER, 0);

        //打开big，打开成功后会在函数app_broadcast_conn_status_event_handler做后续处理
        temp_broadcast_hdl = broadcast_transmitter(params);
    } else {
        //初始化广播接收端参数
        params = set_big_params(mode, BROADCAST_ROLE_RECEIVER, 0);

        //打开big，打开成功后会在函数app_broadcast_conn_status_event_handler做后续处理
        temp_broadcast_hdl = broadcast_receiver(params);
    }

    if (temp_broadcast_hdl >= 0) {
        for (u8 i = 0; i < BIG_MAX_NUMS; i++) {
            if (!app_big_hdl_info[i].used) {
                app_big_hdl_info[i].big_hdl = temp_broadcast_hdl;
                app_big_hdl_info[i].big_status = APP_BROADCAST_STATUS_START;
                app_big_hdl_info[i].used = 1;
                break;
            }
        }
    }

    app_broadcast_mutex_post(&mutex, __LINE__);

    return temp_broadcast_hdl;
}

/* --------------------------------------------------------------------------*/
/**
 * @brief 关闭广播
 *
 * @param status:挂起还是停止
 *
 * @return 0:success
 */
/* ----------------------------------------------------------------------------*/
int app_broadcast_close(u8 status)
{
    int ret = 0;

    if (!app_broadcast_init_flag) {
        return -EPERM;
    }

    log_info("broadcast_close");

    //由于是异步操作需要加互斥量保护，避免和开启开广播的流程同时运行,添加的流程请放在互斥量保护区里面
    app_broadcast_mutex_pend(&mutex, __LINE__);

    for (u8 i = 0; i < BIG_MAX_NUMS; i++) {
        if (app_big_hdl_info[i].used && app_big_hdl_info[i].big_hdl) {
            ret = broadcast_close(app_big_hdl_info[i].big_hdl);
            memset(&app_big_hdl_info[i], 0, sizeof(struct app_big_hdl_t));
            app_big_hdl_info[i].big_status = status;
        }
    }

    receiver_connected_status = 0;
    bis_connected_nums = 0;

#if TCFG_AUTO_SHUT_DOWN_TIME
    sys_auto_shut_down_enable();   // 恢复自动关机
#endif

    //如果开启了VM配置项暂存RAM功能则在关机前保存数据到vm_flash
    //if (get_vm_ram_storage_enable() || get_vm_ram_storage_in_irq_enable()) {
    //    vm_flush2flash(1);
    //}

    //释放互斥量
    app_broadcast_mutex_post(&mutex, __LINE__);

    bis_switch_onoff = 0;

#if defined(RCSP_MODE) && RCSP_MODE
    if (status != APP_BROADCAST_STATUS_SUSPEND) {
        setLeAudioModeMode(JL_LeAudioModeNone);
        ble_module_enable(1);
    }
#endif

    return ret;
}

/* --------------------------------------------------------------------------*/
/**
 * @brief 广播开关切换
 *
 * @return 0：操作成功
 */
/* ----------------------------------------------------------------------------*/
int app_broadcast_switch(void)
{
    u8 find = 0;
    big_parameter_t *params;

    app_mode_t mode = get_current_app_mode();
    if (mode && (mode == APP_MODE_BT) &&
        (bt_get_call_status() != BT_CALL_HANGUP)) {
        return -EPERM;
    }

    for (u8 i = 0; i < BIG_MAX_NUMS; i++) {
        if (app_big_hdl_info[i].used) {
            find = 1;
            break;
        }
    }

    if (find) {
        if (app_broadcast_close(APP_BROADCAST_STATUS_STOP) == 0) {
            le_audio_scene_deal(LE_AUDIO_MUSIC_STOP);
            play_tone_file_alone_callback(get_tone_files()->le_broadcast_close,
                                          (void *)TONE_INDEX_BROADCAST_CLOSE,
                                          broadcast_tone_play_end_callback);
        }

        app_broadcast_uninit();
    } else {
        app_broadcast_init();

        if (app_broadcast_open() >= 0) {
            play_tone_file_alone_callback(get_tone_files()->le_broadcast_open,
                                          (void *)TONE_INDEX_BROADCAST_OPEN,
                                          broadcast_tone_play_end_callback);
        }
    }

    return 0;
}

/* --------------------------------------------------------------------------*/
/**
 * @brief 更新系统当前处于的场景
 *
 * @param scene:当前系统状态
 *
 * @return 0:success
 */
/* ----------------------------------------------------------------------------*/
int update_app_broadcast_deal_scene(int scene)
{
    cur_deal_scene = scene;
    return 0;
}

/* --------------------------------------------------------------------------*/
/**
 * @brief 广播开启情况下，不同场景的处理流程
 *
 * @param scene:当前系统状态
 *
 * @return ret < 0:无需处理，ret == 0:处理事件但不拦截后续流程，ret > 0:处理事件并拦截后续流程
 */
/* ----------------------------------------------------------------------------*/
int app_broadcast_deal(int scene)
{
    int ret = 0;
    static u8 phone_start_cnt = 0;
    app_mode_t mode;

    if ((cur_deal_scene == scene) &&
        (scene != LE_AUDIO_PHONE_START) &&
        (scene != LE_AUDIO_PHONE_STOP)) {
        log_error("app_broadcast_deal,scene not be modified:%d", scene);
        return -EPERM;
    }

#if TCFG_KBOX_1T3_MODE_EN
    if ((scene != LE_AUDIO_PHONE_START) && (scene != LE_AUDIO_PHONE_STOP)) {
        log_error("app_broadcast_deal,cur scene Operation not permitted:%d", scene);
        return -EPERM;
    }
#endif

    cur_deal_scene = scene;

    switch (scene) {
    case LE_AUDIO_APP_MODE_ENTER:
        log_info("LE_AUDIO_APP_MODE_ENTER");
        //进入当前模式
        broadcast_app_mode_exit = 0;
    case LE_AUDIO_APP_OPEN:
        config_broadcast_as_master = 1;
        mode = get_current_app_mode();
        if (mode) {
            le_audio_ops_register(mode);
        }
        if (is_need_resume_broadcast()) {
            app_broadcast_resume();
            ret = 1;
        }
        config_broadcast_as_master = 0;
        break;

    case LE_AUDIO_APP_MODE_EXIT:
        log_info("LE_AUDIO_APP_MODE_EXIT");
        //退出当前模式
        broadcast_app_mode_exit = 1;
    case LE_AUDIO_APP_CLOSE:
        app_broadcast_suspend();
        le_audio_ops_unregister();
        break;

    case LE_AUDIO_MUSIC_START:
    case LE_AUDIO_A2DP_START:
        log_info("LE_AUDIO_MUSIC_START");
        //启动a2dp播放
        if (broadcast_app_mode_exit) {
            //防止蓝牙非后台情况下退出蓝牙模式时，会先出现BROADCAST_APP_MODE_EXIT，再出现BROADCAST_A2DP_START，导致广播状态发生改变
            break;
        }
#if (TCFG_LEA_BIG_FIX_ROLE == 0)
        for (u8 i = 0; i < BIG_MAX_NUMS; i++) {
            if (app_big_hdl_info[i].used && (app_big_hdl_info[i].big_status == APP_BROADCAST_STATUS_START)) {
                //(1)当处于广播开启并且作为接收设备时，挂起广播，播放当前手机音乐；
                //(2)当前广播处于挂起状态时，恢复广播并作为发送设备。
                if (get_broadcast_role() == BROADCAST_ROLE_RECEIVER) {
                    app_broadcast_suspend();
                } else if (get_broadcast_role() == BROADCAST_ROLE_TRANSMITTER) {
                    ret = 1;
                }
                break;
            }
        }
#else
        if (get_broadcast_role() == BROADCAST_ROLE_TRANSMITTER) {
            for (i = 0; i < BIG_MAX_NUMS; i++) {
                //固定收发角色重启广播数据流
                broadcast_audio_all_open(app_big_hdl_info[i].big_hdl);
            }
            ret = 1;
            break;
        }
#endif

#if TCFG_BT_VOL_SYNC_ENABLE
        mode = get_current_app_mode();
        if (mode && (mode == APP_MODE_BT)) {
            bt_set_music_device_volume(get_music_sync_volume());
        }
#endif

        if (is_need_resume_broadcast()) {
#if OLD_CASE
            app_broadcast_resume();
#else
            app_broadcast_open_with_role(1);
#endif
            ret = 1;
        }
        break;

    case LE_AUDIO_MUSIC_STOP:
    case LE_AUDIO_A2DP_STOP:
        log_info("LE_AUDIO_MUSIC_STOP");
        //停止a2dp播放
        if (broadcast_app_mode_exit) {
            //防止蓝牙非后台情况下退出蓝牙模式时，会先出现LE_AUDIO_APP_MODE_EXIT，再出现LE_AUDIO_A2DP_STOP，导致广播状态发生改变
            break;
        }
#if (TCFG_LEA_BIG_FIX_ROLE == 0)
        //当前处于广播挂起状态时，停止手机播放，恢复广播并接收其他设备的音频数据
        app_broadcast_suspend();
#else
        if (get_broadcast_role() == BROADCAST_ROLE_TRANSMITTER) {
            for (u8 i = 0; i < BIG_MAX_NUMS; i++) {
                //固定收发角色暂停播放时关闭广播数据流
                broadcast_audio_all_close(app_big_hdl_info[i].big_hdl);
            }
            ret = 1;
            break;
        }
#endif
        if (is_need_resume_broadcast()) {
#if OLD_CASE
            app_broadcast_resume();
#else
            app_broadcast_open_with_role(0);
#endif
            ret = 1;
        }
        break;

    case LE_AUDIO_PHONE_START:
        log_info("LE_AUDIO_PHONE_START");
        //通话时，挂起广播
        phone_start_cnt++;
        log_info("phone_start_cnt: %d", phone_start_cnt);
        app_broadcast_suspend();
        break;

    case LE_AUDIO_PHONE_STOP:
        log_info("LE_AUDIO_PHONE_STOP");
        //通话结束恢复广播
        phone_start_cnt--;
        log_info("phone_start_cnt: %d", phone_start_cnt);
        if (phone_start_cnt) {
            log_info("phone_start_cnt:%d", phone_start_cnt);
            break;
        }

        mode = get_current_app_mode();
        //当前处于蓝牙模式并且挂起前广播作为发送设备，恢复广播的操作在播放a2dp处执行
        if (mode && (mode == APP_MODE_BT)) {
            if (broadcast_last_role == BROADCAST_ROLE_TRANSMITTER) {
            }
        }
        //当前处于蓝牙模式并且挂起前广播，恢复广播并作为接收设备
        if (is_need_resume_broadcast()) {
#if OLD_CASE
            app_broadcast_resume();
#else
            app_broadcast_open_with_role(0);
            ret = 1;
#endif
        }
        break;

    case LE_AUDIO_EDR_DISCONN:
        log_info("LE_AUDIO_EDR_DISCONN");
        if (broadcast_app_mode_exit) {
            //防止蓝牙非后台情况下退出蓝牙模式时，会先出现LE_AUDIO_APP_MODE_EXIT，再出现LE_AUDIO_EDR_DISCONN，导致广播状态发生改变
            break;
        }
        //当经典蓝牙断开后，作为发送端的广播设备挂起广播
        if (get_broadcast_role() == BROADCAST_ROLE_TRANSMITTER) {
            app_broadcast_suspend();
        }
        if (is_need_resume_broadcast()) {
#if OLD_CASE
            app_broadcast_resume();
#else
            app_broadcast_open_with_role(0);
            ret = 1;
#endif
        }
        break;

    default:
        log_error("%s invalid operation", __FUNCTION__);
        ret = -ESRCH;
        break;
    }

    return ret;
}

/* --------------------------------------------------------------------------*/
/**
 * @brief 初始化同步的状态数据的内容
 */
/* ----------------------------------------------------------------------------*/
static void app_broadcast_sync_data_init(void)
{
    app_broadcast_data_sync.volume = app_audio_get_volume(APP_AUDIO_STATE_MUSIC);
    broadcast_sync_data_init(&app_broadcast_data_sync);
}

/* --------------------------------------------------------------------------*/
/**
 * @brief 更新广播同步状态的数据
 *
 * @param type:更新项
 * @param value:更新值
 *
 * @return 0:success
 */
/* ----------------------------------------------------------------------------*/
int update_broadcast_sync_data(u8 type, int value)
{
    switch (type) {
    case BROADCAST_SYNC_VOL:
        if (app_broadcast_data_sync.volume == value) {
            return 0;
        }
        app_broadcast_data_sync.volume = value;
        break;
    default:
        return -ESRCH;
    }

    for (u8 i = 0; i < BIG_MAX_NUMS; i++) {
        broadcast_set_sync_data(app_big_hdl_info[i].big_hdl, &app_broadcast_data_sync, sizeof(struct broadcast_sync_info));
    }

    return 0;
}

/* --------------------------------------------------------------------------*/
/**
 * @brief 接收到广播发送端的同步数据，并更新本地配置
 *
 * @param priv:接收到的同步数据
 *
 * @return
 */
/* ----------------------------------------------------------------------------*/
static int broadcast_padv_data_deal(void *priv)
{
    struct broadcast_sync_info *sync_data = (struct broadcast_sync_info *)priv;

    if (app_broadcast_data_sync.volume != sync_data->volume) {
        app_broadcast_data_sync.volume = sync_data->volume;
#if (TCFG_LEA_BIG_VOL_SYNC_EN && (!TCFG_KBOX_1T3_MODE_EN))
        app_audio_set_volume(APP_AUDIO_STATE_MUSIC, app_broadcast_data_sync.volume, 1);
#endif
    }

    memcpy(&app_broadcast_data_sync, sync_data, sizeof(struct broadcast_sync_info));

    return 0;
}

/* --------------------------------------------------------------------------*/
/**
 * @brief 广播资源初始化
 */
/* ----------------------------------------------------------------------------*/
void app_broadcast_init(void)
{
    if (app_broadcast_init_flag) {
        return;
    }

    os_mutex_create(&mutex);

    broadcast_init();

    app_broadcast_sync_data_init();

    app_broadcast_init_flag = 1;
}

/* --------------------------------------------------------------------------*/
/**
 * @brief 广播资源卸载
 */
/* ----------------------------------------------------------------------------*/
void app_broadcast_uninit(void)
{
    if (!app_broadcast_init_flag) {
        return;
    }

    app_broadcast_init_flag = 0;

    os_mutex_del(&mutex, OS_DEL_NO_PEND);

    broadcast_uninit();
}

/* --------------------------------------------------------------------------*/
/**
 * @brief 广播接收端配对事件回调
 *
 * @param event：配对事件
 * @param priv：事件附带的参数
 */
/* ----------------------------------------------------------------------------*/
static void broadcast_pair_rx_event_callback(const PAIR_EVENT event, void *priv)
{
    switch (event) {
    case PAIR_EVENT_RX_PRI_CHANNEL_CREATE_SUCCESS:
        u32 *private_connect_access_addr = (u32 *)priv;
        log_info("PAIR_EVENT_RX_PRI_CHANNEL_CREATE_SUCCESS: 0x%x", *private_connect_access_addr);
        syscfg_write(VM_WIRELESS_PAIR_CODE0_INDEX, private_connect_access_addr, sizeof(u32));
        break;

    case PAIR_EVENT_RX_OPEN_PAIR_MODE_SUCCESS:
        log_info("PAIR_EVENT_RX_OPEN_PAIR_MODE_SUCCESS");
        break;

    case PAIR_EVENT_RX_CLOSE_PAIR_MODE_SUCCESS:
        log_info("PAIR_EVENT_RX_CLOSE_PAIR_MODE_SUCCESS");
        break;

    default:
        break;
    }
}

/* --------------------------------------------------------------------------*/
/**
 * @brief 广播发送端配对事件回调
 *
 * @param event：配对事件
 * @param priv：事件附带的参数
 */
/* ----------------------------------------------------------------------------*/
static void broadcast_pair_tx_event_callback(const PAIR_EVENT event, void *priv)
{
    switch (event) {
    case PAIR_EVENT_TX_PRI_CHANNEL_CREATE_SUCCESS:
        u32 *private_connect_access_addr = (u32 *)priv;
        log_info("PAIR_EVENT_TX_PRI_CHANNEL_CREATE_SUCCESS: 0x%x", *private_connect_access_addr);
        syscfg_write(VM_WIRELESS_PAIR_CODE0_INDEX, private_connect_access_addr, sizeof(u32));
        break;

    case PAIR_EVENT_TX_OPEN_PAIR_MODE_SUCCESS:
        log_info("PAIR_EVENT_TX_OPEN_PAIR_MODE_SUCCESS");
        break;

    case PAIR_EVENT_TX_CLOSE_PAIR_MODE_SUCCESS:
        log_info("PAIR_EVENT_TX_CLOSE_PAIR_MODE_SUCCESS");
        break;

    default:
        break;
    }
}

/* --------------------------------------------------------------------------*/
/**
 * @brief 广播进入配对模式
 *
 * @param role：广播角色接收端还是发送端
 * @param mode：0-广播配对，1-连接配对
 */
/* ----------------------------------------------------------------------------*/
void app_broadcast_enter_pair(u8 role, u8 mode)
{
    u32 private_connect_access_addr = 0;;

    app_broadcast_close(APP_BROADCAST_STATUS_STOP);

    syscfg_read(VM_WIRELESS_PAIR_CODE0_INDEX, &private_connect_access_addr, sizeof(u32));

    if (role == BROADCAST_ROLE_UNKNOW) {
        if (is_broadcast_as_transmitter()) {
            broadcast_enter_pair(BROADCAST_ROLE_TRANSMITTER, mode, (void *)&pair_tx_cb, private_connect_access_addr);
        } else {
            broadcast_enter_pair(BROADCAST_ROLE_RECEIVER, mode, (void *)&pair_rx_cb, private_connect_access_addr);
        }
    } else if (role == BROADCAST_ROLE_TRANSMITTER) {
        broadcast_enter_pair(role, mode, (void *)&pair_tx_cb, private_connect_access_addr);
    } else if (role == BROADCAST_ROLE_RECEIVER) {
        broadcast_enter_pair(role, mode, (void *)&pair_rx_cb, private_connect_access_addr);
    }
}

/* --------------------------------------------------------------------------*/
/**
 * @brief 退出广播配对模式
 *
 * @param role：广播角色接收端还是发送端
 */
/* ----------------------------------------------------------------------------*/
void app_broadcast_exit_pair(u8 role)
{
    if (role == BROADCAST_ROLE_UNKNOW) {
        if (is_broadcast_as_transmitter()) {
            broadcast_exit_pair(BROADCAST_ROLE_TRANSMITTER);
        } else {
            broadcast_exit_pair(BROADCAST_ROLE_RECEIVER);
        }
    } else {
        broadcast_exit_pair(role);
    }
}

/* --------------------------------------------------------------------------*/
/**
 * @brief 非蓝牙后台情况下，在其他音源模式开启BIG，前提要先开蓝牙协议栈
 */
/* ----------------------------------------------------------------------------*/
void app_broadcast_open_in_other_mode(void)
{
    app_broadcast_init();
#if TCFG_KBOX_1T3_MODE_EN
    app_broadcast_open();
#endif
    if (is_need_resume_broadcast()) {
        app_mode_t mode = get_current_app_mode();
        if (mode) {
            le_audio_ops_register(mode);
        }
        //下面的代码，会导致在关闭蓝牙后台后，切模式时会提前打开广播
        /* app_broadcast_resume(); */
    }
}

/* --------------------------------------------------------------------------*/
/**
 * @brief 非蓝牙后台情况下，在其他音源模式关闭BIG
 */
/* ----------------------------------------------------------------------------*/
void app_broadcast_close_in_other_mode(void)
{
#if TCFG_KBOX_1T3_MODE_EN
    app_broadcast_close(APP_BROADCAST_STATUS_STOP);
#else
    app_broadcast_suspend();
#endif
    app_broadcast_uninit();
}

/* --------------------------------------------------------------------------*/
/**
 * @brief 自定义数据发送接口
 *
 * @param device:发送给远端设备的标识
 * @param data:需要发送的数据
 * @param length:数据长度
 *
 * @return slen:实际发送数据的总长度
 */
/* ----------------------------------------------------------------------------*/
int app_broadcast_send_custom_data(u8 device, void *data, size_t length)
{
    u8 i, j;
    int slen = 0;
    struct wireless_data_callback_func *p;

    for (i = 0; i < BIG_MAX_NUMS; i++) {
        if (app_big_hdl_info[i].used) {
            for (j = 0; j < BIG_MAX_BIS_NUMS; j++) {
                if (app_big_hdl_info[i].bis_hdl_info[j].remote_dev & device) {
                    slen += broadcast_send_custom_data(app_big_hdl_info[i].bis_hdl_info[j].aux_hdl, data, length);
                }
            }
        }
    }

    if (slen) {
        list_for_each_wireless_data_callback(p) {
            if (p->tx_events_suss) {
                if (p->tx_events_suss(data, length)) {
                    break;
                }
            }
        }
    }

    return slen;
}

/* --------------------------------------------------------------------------*/
/**
 * @brief 将先前记录的信息同步给新加入组队的设备，默认新设备连上后调用
 */
/* ----------------------------------------------------------------------------*/
static void remote_dev_msg_status_sync_info_send(u16 acl_hdl)
{
#if TCFG_COMMON_CASE_EN && (TCFG_COMMON_CASE_NAME == 0x1)
    if (!save_sync_status_table[0][0]) {
        return;
    }

    int table_size_h = (sizeof(save_sync_status_table) / sizeof(save_sync_status_table[0]));
    int table_size_l = (sizeof(save_sync_status_table[0]) / sizeof(save_sync_status_table[0][0]));

    for (u8 i = 0; i < BIG_MAX_NUMS; i++) {
        for (u8 j = 0; j < BIG_MAX_BIS_NUMS; j++) {
            if (app_big_hdl_info[i].bis_hdl_info[j].aux_hdl == acl_hdl) {
                for (u8 k = 0; k < table_size_h; k++) {
                    if (save_sync_status_table[k][0]) {
                        wireless_custom_data_send_to_sibling('M', save_sync_status_table[k], table_size_l, app_big_hdl_info[i].bis_hdl_info[j].remote_dev);
                    }

                }
            }
        }
    }
#endif
}

/* --------------------------------------------------------------------------*/
/**
 * @brief 保存需要同步给新加入组队的远端设备的变量
 */
/* ----------------------------------------------------------------------------*/
static void remote_dev_msg_status_sync_info_save(u8 *data, u32 len)
{
#if TCFG_COMMON_CASE_EN && (TCFG_COMMON_CASE_NAME == 0x1)
    int table_size_h = (sizeof(save_sync_status_table) / sizeof(save_sync_status_table[0]));

    for (int i = 0; i < table_size_h; i++) { //控制行
        if (save_sync_status_table[i][0] == data[0]) {
            save_sync_status_table[i][1]  = data[1];
            break;
        } else if (!save_sync_status_table[i][0]) {
            save_sync_status_table[i][0] = data[0];
            save_sync_status_table[i][1]  = data[1];
            break;
        }
    }
#endif
}

/* --------------------------------------------------------------------------*/
/**
 * @brief 转发某个从机的消息给所有从机，用于同步所有从机消息和状态
 *
 * @param acl_hdl:对应特定远端设备的句柄
 * @param arg_num:参数个数
 * @param argv:首个参数地址
 */
/* ----------------------------------------------------------------------------*/
static void remote_dev_msg_status_sync_handler(u16 acl_hdl, u8 arg_num, int *argv)
{
    u8 i, j;
    int trans_role = argv[0];
    u8 *data = (u8 *)argv[1];
    int len = argv[2];

    if (trans_role == WIRELESS_SYNC_CALL_RX) {
        for (i = 0; i < BIG_MAX_NUMS; i++) {
            for (j = 0; j < BIG_MAX_BIS_NUMS; j++) {
                if (app_big_hdl_info[i].bis_hdl_info[j].aux_hdl != acl_hdl) {
                    wireless_custom_data_send_to_sibling('M', data, len, app_big_hdl_info[i].bis_hdl_info[j].remote_dev);
                }
            }
        }
        //记录信息，便于同步给新加入组队的设备
        remote_dev_msg_status_sync_info_save(data, len);
    }

    //由于转发流程中申请了内存，因此执行完毕后必须释放
    if (data) {
        free(data);
    }
}

WIRELESS_CUSTOM_DATA_STUB_REGISTER(msg_status_sync) = {
    .uuid = 'M',
    .task_name = "app_core",
    .func = remote_dev_msg_status_sync_handler,
};

/* --------------------------------------------------------------------------*/
/**
 * @brief 音量同步
 */
/* ----------------------------------------------------------------------------*/
void app_broadcast_sync_volume(u8 remote_dev_identification)
{
    u8 data[2];
    data[0] = app_audio_get_volume(APP_AUDIO_STATE_MUSIC);
    data[1] = app_audio_get_volume(APP_AUDIO_STATE_CALL);
    /* g_printf("music_vol_sync: %d, call_vol_sync: %d\n", data[0], data[1]); */
    //同步音量
    wireless_custom_data_send_to_sibling('V', data, sizeof(data), remote_dev_identification);
}

static void volume_sync_handler(u16 acl_hdl, u8 arg_num, int *argv)
{
    int trans_role = argv[0];
    u8 *data = (u8 *)argv[1];

    if (trans_role == WIRELESS_SYNC_CALL_RX) {
        for (u8 i = 0; i < BIG_MAX_NUMS; i++) {
            for (u8 j = 0; j < BIG_MAX_BIS_NUMS; j++) {
                if (app_big_hdl_info[i].bis_hdl_info[j].aux_hdl == acl_hdl) {
                    app_audio_set_volume(APP_AUDIO_STATE_MUSIC, data[0], 1);
                    app_audio_set_volume(APP_AUDIO_STATE_CALL, data[1], 1);
                    /* r_printf("music_vol_sync: %d, call_vol_sync: %d\n", data[0], data[1]); */
                    break;
                }
            }
        }
    }

    //由于转发流程中申请了内存，因此执行完毕后必须释放
    if (data) {
        free(data);
    }
}

WIRELESS_CUSTOM_DATA_STUB_REGISTER(volume_sync) = {
    .uuid = 'V',
    .task_name = "app_core",
    .func = volume_sync_handler,
};

static void remote_dev_cmd_status_sync_handler(u16 acl_hdl, u8 arg_num, int *argv)
{
    int trans_role = argv[0];
    u8 *data = (u8 *)argv[1];

    if (trans_role == WIRELESS_SYNC_CALL_RX) {
    }

    //由于转发流程中申请了内存，因此执行完毕后必须释放
    if (data) {
        free(data);
    }
}

WIRELESS_CUSTOM_DATA_STUB_REGISTER(cmd_status_sync) = {
    .uuid = 'C',
    .task_name = "app_core",
    .func = remote_dev_cmd_status_sync_handler,
};

/* --------------------------------------------------------------------------*/
/**
 * @brief 获取bis连接数量
 *
 * @return bis连接数量
 */
/* ----------------------------------------------------------------------------*/
u8 get_bis_connected_num(void)
{
    return bis_connected_nums;
}

/* --------------------------------------------------------------------------*/
/**
 * @brief 获取接收方连接状态
 *
 * @return 接收方连接状态
 */
/* ----------------------------------------------------------------------------*/
u8 get_receiver_connected_status(void)
{
    return receiver_connected_status;
}

/* --------------------------------------------------------------------------*/
/**
 * @brief 获取当前是否在退出模式的状态
 *
 * @return 1；是，0：否
 */
/* ----------------------------------------------------------------------------*/
u8 get_broadcast_app_mode_exit_flag(void)
{
    return broadcast_app_mode_exit;
}

u8 get_bis_switch_onoff(void)
{
    return bis_switch_onoff;
}

#endif

