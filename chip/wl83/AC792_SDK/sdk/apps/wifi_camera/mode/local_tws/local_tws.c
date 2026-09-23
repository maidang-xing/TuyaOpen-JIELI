#include "classic/tws_api.h"
#include "local_tws.h"
#include "tws_tone_player.h"
#include "local_tws_player.h"
#include "bt_tws.h"
#include "audio_config.h"
#include "app_config.h"
#include "app_tone.h"
#include "app_msg.h"
#include "event/key_event.h"
#include "event/bt_event.h"
#include "system/timer.h"

#if TCFG_LOCAL_TWS_ENABLE

#define LOG_TAG             "[LOCAL_TWS]"
#define LOG_ERROR_ENABLE
#define LOG_DEBUG_ENABLE
#define LOG_INFO_ENABLE
/* #define LOG_DUMP_ENABLE */
#define LOG_CLI_ENABLE
#include "debug.h"

#define TWS_FUNC_ID_LOCAL_TWS	TWS_FUNC_ID('L', 'O', 'T', 'S')

#define LOCAL_TWS_TASK_NAME          "local_tws"
#define LOCAL_TWS_SYNC_TONE_ID       0x4C5E6353
#define LOCAL_TWS_TASK_DEBUG         1

typedef struct _local_tws_info {
    void *player;
    u8 role;
    u8 sync_goto_bt_mode;
    u8 cmd_record;                  //用于记录上一条命令
    volatile u8 remote_dec_status;  //对方是否开启local_tws_dec
    volatile u32 cmd_timestamp;     //用于记录命令的时间戳
    const char *sync_tone_name;     //记录同步播放的提示音
    void *priv;                     //回调给local_audio_open的参数
    u16 timer;                      //用于音量同步
} local_tws_info;

static local_tws_info info;
#define __this  (&info)

#include "sink.c"

static void curr_task_dump(void *priv)
{
    struct application *app = __get_current_app();

    log_info("curr_mode:%s", app->name);
}

void local_tws_task_debug_init(void)
{
#if LOCAL_TWS_TASK_DEBUG
    sys_timer_add(NULL, curr_task_dump, 3000);
#endif
}

/* 功能描述： local_tws 命令发送接口, 用于TWS信息交流*/
/* 输入参数描述： data: 需要发送的命令数据  len:命令长度* */
/* 输出参数描述： void */
static void local_tws_cmd_send(u8 *data, u8 len)
{
    u32 msg[4];

    ASSERT(len + 4 <= sizeof(msg));
    u32 send_timestamp = bt_audio_reference_clock_time(1);
    if (data[0] == CMD_TWS_ENTER_SINK_MODE_REQ || data[0] == CMD_TWS_BACK_TO_BT_MODE_REQ) {
        /*当前命令如果时模式请求命令更新时间戳， 用于两边都有模式请求的时候，只响应最晚发送的命令*/
        __this->cmd_timestamp = send_timestamp;
    }
    __this->cmd_record = data[0];
    msg[0] = __this->cmd_timestamp;
    memcpy(&msg[1], data, len);
    log_info("cmd:%d timestamp:%d %d", data[0], send_timestamp, __this->cmd_timestamp);
    tws_api_send_data_to_sibling(msg, len + sizeof(u32), TWS_FUNC_ID_LOCAL_TWS);
}

static void local_tws_vol_report(u8 vol)
{
    u8 data[2] = {CMD_TWS_VOL_REPORT, vol};
    log_info("%s %d", __func__, vol);
    local_tws_cmd_send(data, sizeof(data));
}

/* 功能描述： local_tws 音量调节接口，Sink设备调用，Sink设备调节音量并不会调节本地音量，通过发送命令调节Source端的音量值*/
/* 输入参数描述：  operate: 音量增减*/
/* 输出参数描述： void */
void local_tws_vol_operate(u8 operate)
{
    local_tws_cmd_send(&operate, sizeof(operate));
}

/* 功能描述： local_tws 音乐上下曲接口，Sink设备调用，Sink设备无法自行控制音乐上下曲，通过发送命令让Source段切换上下曲*/
/* 输入参数描述：  operate: 音量增减*/
/* 输出参数描述： void */
void local_tws_music_operate(u8 operate, void *arg)
{
    switch (operate) {
    case CMD_TWS_MUSIC_PP:
        if (!arg) {
            break;
        }
        //arg：当前Source设备所在的模式，会通过CMD_TWS_ENTER_SINK_MODE_REQ同步给Sink设备，该参数的作用时防止Sink发送命令的时候，Source设备切模式，导致Source切到下一模式被暂停播放了*/
        u8 data[2] = {CMD_TWS_MUSIC_PP, *((app_mode_t *)arg)};
        local_tws_cmd_send(data, sizeof(data));
        break;
    case CMD_TWS_MUSIC_NEXT:
    case CMD_TWS_MUSIC_PREV:
        local_tws_cmd_send(&operate, sizeof(operate));
        break;
    }
}

/* 功能描述： 用于同步模式，tws连接的时候调用，会根据当前双方所在的模式决定那端切到Sink模式，如果都在蓝牙模式则不进行切换*/
/* 输入参数描述： void */
/* 输出参数描述： void */
void local_tws_connect_mode_report(void)
{
    u8 data[3] = {0};
    struct local_tws_mode_ops *ops;
    data[0] = CMD_TWS_CONNECT_MODE_REPORT;
    data[1] = get_current_app_mode();
    list_for_each_local_tws_ops(ops) {
        if (!strcmp(ops->name, __get_current_app()->name) && ops->get_play_status) {
            data[2] = ops->get_play_status();
        }
    }
    local_tws_cmd_send(data, sizeof(data));
    __this->sync_tone_name = NULL;
}

/* 功能描述： tws断开的时候调用，tws断开，Sink设备需要返回蓝牙模式*/
/* 输入参数描述： void */
/* 输出参数描述： void */
void local_tws_disconnect_deal(void)
{
    if (__this->player) {
        local_tws_player_close(__this->player);
        __this->player = NULL;
    }

    if (__this->role == LOCAL_TWS_ROLE_SINK) {
        app_mode_change_replace(APP_MODE_BT);
    }

    __this->role = LOCAL_TWS_ROLE_NULL;
}

/* 功能描述： Sink端进行Sink模式时回复Source端的接口，外部流程不会调用*/
/* 输入参数描述： void */
/* 输出参数描述： void */
void local_tws_enter_sink_mode_rsp(app_mode_t mode)
{
    u8 data[2];
    data[0] = CMD_TWS_ENTER_SINK_MODE_RSP;
    data[1] = mode;
    local_tws_cmd_send(data, sizeof(data));
}

/* 功能描述： 用于获取当前的角色*/
/* 输入参数描述： void */
/* 输出参数描述： 返回当前样机的角色 */
u8 local_tws_get_role(void)
{
    return __this->role;
}

/* 功能描述： 用于回复Source端关闭本地解码的消息*/
/* 输入参数描述： void */
/* 输出参数描述： void */
void local_tws_close_dec_rsp(void)
{
    u8 data = CMD_TWS_CLOSE_LOCAL_DEC_RSP;
    local_tws_cmd_send(&data, sizeof(data));
}

/* 功能描述： 用于Sink端回复本地解码状态*/
/* 输入参数描述： st: 当前本地解码开关状态 */
/* 输出参数描述： void */
static void local_tws_dec_status_report(u8 st)
{
    u8 data[2] = { CMD_TWS_PLAYER_STATUS_REPORT, st};
    local_tws_cmd_send(data, sizeof(data));
}

/* 功能描述： 用于获取Sink端本地解码状态*/
/* 输入参数描述： void */
/* 输出参数描述： 当前Sink端本地解码开关状态 */
u8 local_tws_get_remote_dec_status(void)
{
    return __this->remote_dec_status;
}

static void sync_vol_timer_hdl(void *priv)
{
    s16 vol = app_audio_get_volume(APP_AUDIO_STATE_MUSIC);
    local_tws_vol_report((u8)vol);
    __this->timer = 0;
}

/* 功能描述： 用于音量同步*/
/* 输入参数描述： void */
/* 输出参数描述： 当前Sink端本地解码开关状态 */
void local_tws_sync_vol(void)
{
    if (current_app_in_mode(APP_MODE_BT)) {
        return;
    }
    if (!get_bt_tws_connect_status()) {
        return;
    }
    if (__this->timer != 0) {
        sys_timeout_del(__this->timer);
    }
    __this->timer = sys_timeout_add(NULL, sync_vol_timer_hdl, 1000);
}

/* 功能描述： localtws同步播放提示音的回调接口, ops是每个模式通过REGISTER_LOCAL_TWS_OPS注册（该接口不是提供给用户手动调用）*/
/* 输入参数描述： 提示音返回的当前播放事件 */
/* 输出参数描述： void */
static void local_tws_tone_callback(int priv, enum stream_event event)
{
    /*Todo切模式的时候如何处理上个模式的提示音结束在当前模式回调*/
    log_info("local_tws_tone_callback: %d",  event);

    if (event == STREAM_EVENT_STOP) {
        if (__this->role == LOCAL_TWS_ROLE_SOURCE) {
            struct local_tws_mode_ops *ops;
            list_for_each_local_tws_ops(ops) {
                if (!strcmp(ops->name, __get_current_app()->name)) {
                    ops->audio_open(__this->priv);                   //Source打开本地音频解码
                }
            }
        }
    }
}

REGISTER_TWS_TONE_CALLBACK(local_tws_tone_stub) = {
    .func_uuid  = LOCAL_TWS_SYNC_TONE_ID,
    .callback   = local_tws_tone_callback,
};

static void local_tws_become_to_source(app_mode_t mode)
{
    u8 data[2] = {CMD_TWS_ENTER_SINK_MODE_REQ, mode};     //mode参数会回发给发送端，如果发送端收到了命令回复之后所在的模式不等于发送命令时的模式则不响应rsp
    local_tws_cmd_send(data, sizeof(data));
}

static void local_tws_become_to_sink(app_mode_t mode)
{
    log_info("local_tws_become_to_sink : %d", mode);

    __this->role = LOCAL_TWS_ROLE_SINK;

    app_sink_set_sink_mode_rsp_arg(mode);                //sink记录当前Source模式

    if (current_app_in_mode(APP_MODE_SINK) == FALSE) {
        app_mode_change_replace(APP_MODE_SINK);
    } else {
        local_tws_enter_sink_mode_rsp(mode);
    }
}

/* 功能描述： 在每个模式init调用, 切到蓝牙模式通知对端设备切回蓝牙，非蓝牙模式则通知对端设备进行Sink模式 */
/* 输入参数描述： file_name :当前模式提示音文件名  priv:提示音播放完之后回调本地音乐解码时的参数* */
/* 输出参数描述： 0：表示执行成功  -1：tws未连接，走原本单箱进行模式的流程*/

int local_tws_enter_mode(const char *file_name, app_mode_t mode, void *priv)
{
    u8 data;
    log_info("local_tws_enter_mode:%s", file_name);

    if (get_bt_tws_connect_status()) {
        __this->sync_tone_name = file_name;
        __this->priv = priv;

        if (mode == APP_MODE_BT) {
            if (__this->sync_goto_bt_mode == 0) {    		//TWS有一边切到蓝牙模式同步通知另一边也切到蓝牙模式, 后切换的设备不需要发送命令
                data = CMD_TWS_BACK_TO_BT_MODE_REQ;		    //通知对方进入蓝牙模式
            } else {
                data = CMD_TWS_BACK_TO_BT_MODE_RSP;
            }
            local_tws_cmd_send(&data, 1);
            __this->sync_goto_bt_mode = 0;
            __this->role = LOCAL_TWS_ROLE_NULL;         //进入蓝牙模式不区分source和sink
        } else {
            if (__this->sync_goto_bt_mode == 0) {       //由于推消息到app_core执行切换模式存在滞后，所以当sync_goto_bt_mode为1说明当前需要切到BT，但是被按键打断先切到别的模式，这里如果通知对方切到sink模式会导致当前小机最后处于蓝牙模式，对方处于sink模式
                struct local_tws_mode_ops *ops;
                bool match = FALSE;
                list_for_each_local_tws_ops(ops) {
                    if (ops->mode == mode) {
                        local_tws_become_to_source(mode);
                        match = TRUE;
                        break;
                    }
                }
                if (!match) {
                    data = CMD_TWS_ENTER_NO_SOURCE_MODE_REPORT;
                    local_tws_cmd_send(&data, 1);
                }
            }
        }
        return 0;
    }

    return -1;
}

/* 功能描述： 在每个模式exit调用, 用于通知对方关闭本地解码(对方本地解码可能已经在Source关闭解码的时候同步关闭了)， 并同步当前模式音量*/
/* 输入参数描述： void */
/* 输出参数描述： void */
void local_tws_exit_mode(void)
{
    uint32_t rets_addr;
    __asm__ volatile("%0 = rets ;" : "=r"(rets_addr));

    if (get_bt_tws_connect_status()) {
        if (!(current_app_in_mode(APP_MODE_BT) || current_app_in_mode(APP_MODE_SINK))) {
            if (__this->remote_dec_status) {
                u8 data = CMD_TWS_CLOSE_LOCAL_DEC_REQ;
                local_tws_cmd_send(&data, 1);
                log_info("local_tws_exit_mode:0x%x", rets_addr);
                if (__this->timer != 0) {
                    sys_timeout_del(__this->timer);
                    __this->timer = 0;
                }
                s16 vol = app_audio_get_volume(APP_AUDIO_STATE_MUSIC);
                local_tws_vol_report((u8)vol);
            }
        }
    }
}

static int bt_local_tws_cmd_handler(void *evt)
{
    u32 *msg = (u32 *)evt;
    u32 cmd_timestamp = msg[0];
    u8 *cmd = (u8 *)&msg[1];
    struct key_event key = {0};

    log_info("task get cmd: %d timestamp: %d", cmd[0], cmd_timestamp);

    switch (cmd[0]) {
    case CMD_TWS_CLOSE_LOCAL_DEC_REQ:
        //Sink 关闭local_tws_dec
        log_info("CMD_TWS_CLOSE_LOCAL_DEC_REQ");
        __this->sync_goto_bt_mode = 0;
        local_tws_close_dec_rsp();
        break;
    case CMD_TWS_CLOSE_LOCAL_DEC_RSP:
        log_info("CMD_TWS_CLOSE_LOCAL_DEC_RSP");
        __this->remote_dec_status = 0;
        break;
    case CMD_TWS_ENTER_SINK_MODE_REQ:
        //Sink进入sink模式
        log_info("CMD_TWS_ENTER_SINK_MODE_REQ: %d %d %d", __this->cmd_record, __this->cmd_timestamp, cmd_timestamp);

        bool bt_app_exit_check(void);
        if (bt_app_exit_check() == FALSE) { //当前如果处于通话则不能切到sink，通知对方切回蓝牙模式
            u8 data = CMD_TWS_BACK_TO_BT_MODE_REQ;		    //通知对方进入蓝牙模式
            local_tws_cmd_send(&data, 1);
            break;
        }
        if (__this->cmd_record == CMD_TWS_ENTER_SINK_MODE_REQ || __this->cmd_record == CMD_TWS_BACK_TO_BT_MODE_REQ) {
            if (__this->cmd_timestamp > cmd_timestamp) {        //如果当前发送的命令的时间戳比对方请求的大，则不响应
                log_info("local timestamp > remote timestamp!");
                break;
            }
        }
        __this->sync_goto_bt_mode = 0;
        local_tws_become_to_sink(cmd[1]);
        break;
    case CMD_TWS_ENTER_SINK_MODE_RSP:           //sink设备切到sink模式之后回复source，表示已经切换到sink模式了
        log_info("CMD_TWS_ENTER_SINK_MODE_RSP:%d %d", get_current_app_mode(), cmd[1]);
        __this->role = LOCAL_TWS_ROLE_SOURCE;
        s16 vol = app_audio_get_volume(APP_AUDIO_STATE_MUSIC);      //source同步一次音量给sink避免两边音量不同步
        local_tws_vol_report((u8)vol);
        if (__this->sync_tone_name && current_app_in_mode(cmd[1])) {        //cmd[1] = mode, 如果不等于当前模式则说明已经切到下个模式
            tone_player_stop();
            tws_play_tone_file_alone_callback(__this->sync_tone_name, 200, LOCAL_TWS_SYNC_TONE_ID);
            __this->sync_tone_name = NULL;
        }
        break;
    case CMD_TWS_BACK_TO_BT_MODE_REQ:
        log_info("CMD_TWS_BACK_TO_BT_MODE_REQ: %d %d %d", __this->cmd_record, __this->cmd_timestamp, cmd_timestamp);
        if (__this->cmd_record == CMD_TWS_ENTER_SINK_MODE_REQ || __this->cmd_record == CMD_TWS_BACK_TO_BT_MODE_REQ) {
            if (__this->cmd_timestamp > cmd_timestamp) {        //如果当前发送的命令的时间戳比对方请求的大，则不响应
                log_info("local timestamp > remote timestamp!");
                break;
            }
        }
        if (FALSE == current_app_in_mode(APP_MODE_BT)) {
            __this->sync_goto_bt_mode = 1;
            app_mode_change_replace(APP_MODE_BT);
        } else {
            u8 data = CMD_TWS_BACK_TO_BT_MODE_RSP;
            local_tws_cmd_send(&data, 1);
        }
        break;
    case CMD_TWS_BACK_TO_BT_MODE_RSP:
        log_info("CMD_TWS_BACK_TO_BT_MODE_RSP");
        if (current_app_in_mode(APP_MODE_BT)) {
            tone_player_stop();
            tws_play_tone_file_alone_callback(__this->sync_tone_name, 200, LOCAL_TWS_SYNC_TONE_ID);
            __this->sync_tone_name = NULL;
        }
        break;
    case CMD_TWS_PLAYER_STATUS_REPORT:
        log_info("CMD_TWS_PLAYER_STATUS_REPORT:%d", cmd[1]);
        __this->remote_dec_status = cmd[1];
        break;
    case CMD_TWS_CONNECT_MODE_REPORT:
        if (cmd[1] == APP_MODE_BT && !current_app_in_mode(APP_MODE_BT)) {   //当前仅考虑了除蓝牙模式其他模式都为Source的情况
            log_info("CMD_TWS_CONNECT_MODE_REPORT:BECOME TO SOURCE");
            local_tws_become_to_source(get_current_app_mode());
        } else if (cmd[1] != APP_MODE_BT && current_app_in_mode(APP_MODE_BT)) {
            log_info("CMD_TWS_CONNECT_MODE_REPORT: MODE REPORT");
            local_tws_connect_mode_report();
        } else if (cmd[1] == APP_MODE_BT && current_app_in_mode(APP_MODE_BT)) {
            //都处于蓝牙模式不需要操作
            log_info("Both in BT MODE");
        } else {
            //两边都处于非蓝牙模式,有可能一边在音乐模式下播歌，另一边开机切到音乐模式才连上
            bool local_play_status = FALSE;
            struct local_tws_mode_ops *ops;
            list_for_each_local_tws_ops(ops) {
                if (!strcmp(ops->name, __get_current_app()->name) && ops->get_play_status) {
                    local_play_status = ops->get_play_status();
                }
            }
            log_info("local_play_status:%d remote_play_status:%d", local_play_status, cmd[2]);
            if (local_play_status == FALSE && cmd[2] == TRUE) {
                local_tws_connect_mode_report();
            } else {
                local_tws_become_to_source(get_current_app_mode());
            }
        }
        break;
    case CMD_TWS_ENTER_NO_SOURCE_MODE_REPORT:
        if (current_app_in_mode(APP_MODE_SINK)) {
            app_mode_change_replace(APP_MODE_BT);
        }
        break;
    case CMD_TWS_VOL_UP:
        key.action = KEY_EVENT_CLICK;
        key.value = KEY_VOLUME_INC;
        key_event_notify_no_filter(KEY_EVENT_FROM_TWS, &key);
        break;
    case CMD_TWS_VOL_DOWN:
        key.action = KEY_EVENT_CLICK;
        key.value = KEY_VOLUME_DEC;
        key_event_notify_no_filter(KEY_EVENT_FROM_TWS, &key);
        break;
    case CMD_TWS_VOL_REPORT:
        if (!current_app_in_mode(APP_MODE_BT)) {
            app_audio_set_volume(APP_AUDIO_STATE_MUSIC, cmd[1], 1);
        }
        break;
    case CMD_TWS_MUSIC_PP:
        key.action = KEY_EVENT_CLICK;
        key.value = KEY_OK;
        key_event_notify_no_filter(KEY_EVENT_FROM_TWS, &key);
        break;
    case CMD_TWS_MUSIC_NEXT:
        key.action = KEY_EVENT_LONG;
        key.value = KEY_NEXT;
        key_event_notify_no_filter(KEY_EVENT_FROM_TWS, &key);
        break;
    case CMD_TWS_MUSIC_PREV:
        key.action = KEY_EVENT_LONG;
        key.value = KEY_PREV;
        key_event_notify_no_filter(KEY_EVENT_FROM_TWS, &key);
        break;
    default:
        log_info("default msg: %d", cmd[0]);
        break;
    }

    return 0;
}

REGISTER_APP_EVENT_HANDLER(bt_local_tws_cmd) = {
    .event      = SYS_BT_EVENT,
    .from       = BT_EVENT_FROM_LOCAL_TWS,
    .handler    = bt_local_tws_cmd_handler,
};

//in irq，注意不要调用Pend、Ostimedly等接口
static void local_tws_rx_from_sibling(void *data, u16 len, bool rx)
{
    struct tws_event evt = {0};

    if (rx) {
        ASSERT(len <= sizeof(evt));
        memcpy(&evt, data, len);
        sys_event_notify(SYS_BT_EVENT, BT_EVENT_FROM_LOCAL_TWS, &evt, sizeof(evt));
    }
}

REGISTER_TWS_FUNC_STUB(local_tws_sync_stub) = {
    .func_id = TWS_FUNC_ID_LOCAL_TWS,
    .func    = local_tws_rx_from_sibling,
};

static int bt_local_tws_event_handler(void *evt)
{
    struct tws_event *event = (struct tws_event *)evt;

    switch (event->event) {
    case TWS_EVENT_DATA_TRANS_OPEN:
        break;
    case TWS_EVENT_DATA_TRANS_START:
        /*Source端打开本地传输Sink端会收到该event并收到参数，在此处打开本地解码*/
        log_info("TWS_EVENT_DATA_TRANS_START");
        local_tws_dec_status_report(1);
        struct local_tws_player_param tws_player_param;
        tws_player_param.tws_channel = event->args[0];
        tws_player_param.channel_mode = event->args[2];
        tws_player_param.sample_rate = event->args[3];
        tws_player_param.coding_type = event->args[4];
        tws_player_param.durations = event->args[5];
        tws_player_param.bit_rate = event->args[6];
        rf_coexistence_scene_enter(RF_COEXISTENCE_SCENE_LOCAL_TWS_RX, -1);
        __this->player = local_tws_player_open(&tws_player_param);
        break;
    case TWS_EVENT_DATA_TRANS_CLOSE:
        /*Source端关闭本地传输Sink端会收到该event并收到参数，在此处关闭本地解码*/
        log_info("TWS_EVENT_DATA_TRANS_CLOSE");
        if (__this->player) {
            local_tws_player_close(__this->player);
            __this->player = NULL;
        }
        rf_coexistence_scene_exit(RF_COEXISTENCE_SCENE_LOCAL_TWS_RX);
        local_tws_dec_status_report(0);
        break;
    default:
        break;
    }

    return FALSE;
}

REGISTER_APP_EVENT_HANDLER(bt_local_tws_event) = {
    .event      = SYS_BT_EVENT,
    .from       = BT_EVENT_FROM_TWS,
    .handler    = bt_local_tws_event_handler,
};

#endif
