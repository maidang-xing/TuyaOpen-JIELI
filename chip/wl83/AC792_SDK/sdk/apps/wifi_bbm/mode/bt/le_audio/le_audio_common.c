#include "app_config.h"
#include "app_msg.h"
#include "audio_base.h"
#include "le_broadcast.h"
#include "wireless_trans.h"
#include "le_audio/le_audio_stream.h"
#include "le_audio_player.h"
#include "app_le_broadcast.h"
#include "app_le_connected.h"
#include "app_le_auracast.h"
#include "classic/tws_event.h"
#include "classic/tws_api.h"
#include "bt_tws.h"
#include "event/bt_event.h"
#include "event/key_event.h"
#include "system/init.h"
#include "syscfg/syscfg_id.h"

#if (TCFG_LEA_BIG_CTRLER_TX_EN || TCFG_LEA_BIG_CTRLER_RX_EN || TCFG_LEA_CIG_CENTRAL_EN || TCFG_LEA_CIG_PERIPHERAL_EN) || \
    (TCFG_LE_AUDIO_APP_CONFIG & (LE_AUDIO_AURACAST_SOURCE_EN | LE_AUDIO_JL_AURACAST_SOURCE_EN)) || \
    (TCFG_LE_AUDIO_APP_CONFIG & (LE_AUDIO_AURACAST_SINK_EN | LE_AUDIO_JL_AURACAST_SINK_EN)) || \
    (TCFG_LE_AUDIO_APP_CONFIG & (LE_AUDIO_UNICAST_SOURCE_EN | LE_AUDIO_JL_UNICAST_SOURCE_EN)) || \
    (TCFG_LE_AUDIO_APP_CONFIG & (LE_AUDIO_UNICAST_SINK_EN | LE_AUDIO_JL_UNICAST_SINK_EN))

#define LOG_TAG             "[LEAUDIO_COMMON]"
#define LOG_ERROR_ENABLE
#define LOG_DEBUG_ENABLE
#define LOG_INFO_ENABLE
/* #define LOG_DUMP_ENABLE */
#define LOG_CLI_ENABLE
#include "debug.h"

/**************************************************************************************************
  Static Prototypes
 **************************************************************************************************/
static int default_tx_le_audio_close(void *rx_audio);
static void *default_tx_le_audio_open(void *args);

/**************************************************************************************************
  Extern Global Variables
**************************************************************************************************/
extern const struct le_audio_mode_ops le_audio_a2dp_ops;
extern const struct le_audio_mode_ops le_audio_local_music_ops;
extern const struct le_audio_mode_ops le_audio_net_music_ops;
extern const struct le_audio_mode_ops le_audio_linein_ops;
extern const struct le_audio_mode_ops le_audio_iis_ops;
extern const struct le_audio_mode_ops le_audio_mic_ops;
extern const struct le_audio_mode_ops le_audio_spdif_ops;
extern const struct le_audio_mode_ops le_audio_fm_ops;
extern const struct le_audio_mode_ops le_audio_pc_ops;

/**************************************************************************************************
  Local Global Variables
**************************************************************************************************/
static char lea_product_test_name[28];
static char le_audio_pair_name[28] = "JL_AC792N_AURACAST";
static struct le_audio_mode_ops *broadcast_audio_switch_ops = NULL; /*!< le audio和local audio切换回调接口指针 */
static struct le_audio_mode_ops *connected_audio_switch_ops = NULL; /*!< le audio和local audio切换回调接口指针 */

static const struct le_audio_mode_ops le_audio_default_ops = {
    .rx_le_audio_open = default_rx_le_audio_open,
    .rx_le_audio_close = default_rx_le_audio_close,
};

/**************************************************************************************************
  Function Declarations
**************************************************************************************************/
static void read_le_audio_product_name(void)
{
#if (TCFG_LEA_BIG_CTRLER_TX_EN || TCFG_LEA_BIG_CTRLER_RX_EN || TCFG_LEA_CIG_CENTRAL_EN || TCFG_LEA_CIG_PERIPHERAL_EN)
    int len = syscfg_read(CFG_LEA_PRODUCET_TEST_NAME, lea_product_test_name, sizeof(lea_product_test_name));
    if (len <= 0) {
        log_error("can not read the product test name");
        return;
    }
    log_info("product_test_name: %s", lea_product_test_name);
#endif
}

static void read_le_audio_pair_name(void)
{
#if (TCFG_LEA_BIG_CTRLER_TX_EN || TCFG_LEA_BIG_CTRLER_RX_EN || TCFG_LEA_CIG_CENTRAL_EN || TCFG_LEA_CIG_PERIPHERAL_EN)
    int len = syscfg_read(CFG_LEA_PAIR_NAME, le_audio_pair_name, sizeof(le_audio_pair_name));
    if (len <= 0) {
        log_error("can not read the le audio pair name");
        return;
    }
    log_info("pair_name: %s", le_audio_pair_name);
#endif
}

const char *get_le_audio_product_name(void)
{
    return lea_product_test_name;
}

const char *get_le_audio_pair_name(void)
{
    return le_audio_pair_name;
}

static int le_audio_init(void)
{
    read_le_audio_product_name();
    read_le_audio_pair_name();
    return 0;
}
__initcall(le_audio_init);

/* --------------------------------------------------------------------------*/
/**
 * @brief 注册le audio和local audio切换回调接口
 *
 * @param ops:le audio和local audio切换回调接口结构体
 */
/* ----------------------------------------------------------------------------*/
static void le_audio_switch_ops_callback(void *ops)
{
#if (TCFG_LEA_BIG_CTRLER_TX_EN || TCFG_LEA_BIG_CTRLER_RX_EN) || \
    (TCFG_LE_AUDIO_APP_CONFIG & (LE_AUDIO_AURACAST_SOURCE_EN | LE_AUDIO_JL_AURACAST_SOURCE_EN)) || \
    (TCFG_LE_AUDIO_APP_CONFIG & (LE_AUDIO_AURACAST_SINK_EN | LE_AUDIO_JL_AURACAST_SINK_EN))
    broadcast_audio_switch_ops = (struct le_audio_mode_ops *)ops;
#elif (TCFG_LEA_CIG_CENTRAL_EN || TCFG_LEA_CIG_PERIPHERAL_EN)
    connected_audio_switch_ops = (struct le_audio_mode_ops *)ops;
#endif
}

struct le_audio_mode_ops *get_broadcast_audio_sw_ops(void)
{
    return broadcast_audio_switch_ops;
}

struct le_audio_mode_ops *get_connected_audio_sw_ops(void)
{
    return connected_audio_switch_ops;
}

struct le_audio_mode_ops *get_le_audio_sw_ops(void)
{
#if (TCFG_LEA_BIG_CTRLER_TX_EN || TCFG_LEA_BIG_CTRLER_RX_EN) || \
    (TCFG_LE_AUDIO_APP_CONFIG & (LE_AUDIO_AURACAST_SOURCE_EN | LE_AUDIO_JL_AURACAST_SOURCE_EN)) || \
    (TCFG_LE_AUDIO_APP_CONFIG & (LE_AUDIO_AURACAST_SINK_EN | LE_AUDIO_JL_AURACAST_SINK_EN))
    return broadcast_audio_switch_ops;
#elif (TCFG_LEA_CIG_CENTRAL_EN || TCFG_LEA_CIG_PERIPHERAL_EN)
    return connected_audio_switch_ops;
#endif
}

void le_audio_ops_register(u8 mode)
{
#if TCFG_KBOX_1T3_MODE_EN
    mode = APP_MODE_IDLE;
#endif

    switch (mode) {
#if TCFG_APP_BT_EN
    case APP_MODE_BT:
        le_audio_switch_ops_callback((void *)&le_audio_a2dp_ops);
        break;
#endif
#if TCFG_APP_MUSIC_EN
    case APP_MODE_LOCAL:
        le_audio_switch_ops_callback((void *)&le_audio_local_music_ops);
        break;
#endif
#if TCFG_APP_NET_MUSIC_EN
    case APP_MODE_NET:
        le_audio_switch_ops_callback((void *)&le_audio_net_music_ops);
        break;
#endif
#if TCFG_APP_LINEIN_EN
    case APP_MODE_LINEIN:
        le_audio_switch_ops_callback((void *)&le_audio_linein_ops);
        break;
#endif
#if TCFG_APP_MIC_EN
    case APP_MODE_MIC:
        le_audio_switch_ops_callback((void *)&le_audio_mic_ops);
        break;
#endif
#if TCFG_APP_PC_EN
    case APP_MODE_PC:
        le_audio_switch_ops_callback((void *)&le_audio_pc_ops);
        break;
#endif
#if TCFG_APP_SPDIF_EN
    case APP_MODE_SPDIF:
        le_audio_switch_ops_callback((void *)&le_audio_spdif_ops);
        break;
#endif
#if TCFG_APP_FM_EN
    case APP_MODE_FM:
        le_audio_switch_ops_callback((void *)&le_audio_fm_ops);
        break;
#endif
    default:
        le_audio_switch_ops_callback((void *)&le_audio_default_ops);
        break;
    }
}

void le_audio_ops_unregister(void)
{
    le_audio_switch_ops_callback(NULL);
}

int default_rx_le_audio_open(void *rx_audio, void *args)
{
    struct le_audio_player_hdl *rx_audio_hdl = (struct le_audio_player_hdl *)rx_audio;

    if (!rx_audio) {
        return -EPERM;
    }

    //打开广播音频播放
    struct le_audio_stream_params *params = (struct le_audio_stream_params *)args;
    rx_audio_hdl->le_audio = le_audio_stream_create(params->conn, &params->fmt);
    rx_audio_hdl->rx_stream = le_audio_stream_rx_open(rx_audio_hdl->le_audio, params->fmt.coding_type);

    return le_audio_player_open(rx_audio_hdl->le_audio, params);
}

int default_rx_le_audio_close(void *rx_audio)
{
    struct le_audio_player_hdl *rx_audio_hdl = (struct le_audio_player_hdl *)rx_audio;

    if (!rx_audio) {
        return -EPERM;
    }

    //关闭广播音频播放
    le_audio_player_close(rx_audio_hdl->le_audio);
    le_audio_stream_rx_close(rx_audio_hdl->rx_stream);
    le_audio_stream_free(rx_audio_hdl->le_audio);

    return 0;
}

void le_audio_working_status_switch(u8 en)
{
#if ((TCFG_LEA_BIG_CTRLER_TX_EN || TCFG_LEA_BIG_CTRLER_RX_EN))
    if (en) {
        app_broadcast_open_in_other_mode();
    } else {
        if (get_current_app_mode() != APP_MODE_BT) {
            app_broadcast_close_in_other_mode();
        } else {
            app_broadcast_close(APP_BROADCAST_STATUS_STOP);
        }
    }
#endif

#if ((TCFG_LEA_CIG_CENTRAL_EN || TCFG_LEA_CIG_PERIPHERAL_EN))
    if (en) {
        app_connected_open_in_other_mode();
    } else {
        if (get_current_app_mode() != APP_MODE_BT) {
            app_connected_close_in_other_mode();
        } else {
            app_connected_close_all(APP_CONNECTED_STATUS_STOP);
        }
    }
#endif
}

#if (TCFG_USER_TWS_ENABLE && TCFG_APP_BT_EN)

#if (TCFG_KBOX_1T3_MODE_EN)
static void set_tws_sibling_mic_status(void *_data, u16 len, bool rx)
{
    u8 *data = (u8 *)_data;
    u8 local_mic_con_num = get_bis_connected_num();

    if (rx) {
        log_info("mic status tws rx %d", data[0]);

        if (tws_api_get_role() == TWS_ROLE_SLAVE) {
            ///从机没有连接mic，或者主机有连接mic的情况，从机都将le audio关掉
            if ((local_mic_con_num == 0) || (data[0])) {
                log_info("slave working mic close");
                /* le_audio_working_status_switch(0); */
                app_send_message(APP_MSG_WIRELESS_MIC_CLOSE, 0);
            }
        } else {
            ///主机没有mic连接并且从机有mic连接，主机将le audio关掉
            if ((local_mic_con_num == 0) && (data[0])) {
                log_info("master working mic close");
                /* le_audio_working_status_switch(0); */
                app_send_message(APP_MSG_WIRELESS_MIC_CLOSE, 0);
            }
        }
    }
}

REGISTER_TWS_FUNC_STUB(mic_sync_stub) = {
    .func_id = TWS_FUNC_ID_MIC_SYNC,
    .func    = set_tws_sibling_mic_status,
};

static void le_audio_tws_sync_mic_status(void)
{
    u8 mic_con_num = get_bis_connected_num();
    u8 data = mic_con_num;
    tws_api_send_data_to_sibling(&data, 1, TWS_FUNC_ID_MIC_SYNC);

    log_info("tws_sync_mic_num: %d", mic_con_num);
}
#endif

static int le_audio_sync_tws_event_handler(void *msg)
{
    struct tws_event *evt = (struct tws_event *)msg;

    log_info("le_auido_sync_tws_event_handler : 0x%x", evt->event);
    log_info("tws role: %s", (tws_api_get_role() == TWS_ROLE_MASTER) ? "master" : "slave");

    switch (evt->event) {
    case TWS_EVENT_CONNECTED:
#if (TCFG_KBOX_1T3_MODE_EN)
#if 0
        le_audio_tws_sync_mic_status();
#else
        app_send_message(APP_MSG_WIRELESS_MIC_CLOSE, 0);
        app_send_message(APP_MSG_WIRELESS_MIC_OPEN, 0);
#endif
#endif
        break;
    case TWS_EVENT_CONNECTION_TIMEOUT:
        break;
    case TWS_EVENT_CONNECTION_DETACH:
#if (TCFG_KBOX_1T3_MODE_EN)
        app_send_message(APP_MSG_WIRELESS_MIC_CLOSE, 0);
        app_send_message(APP_MSG_WIRELESS_MIC_OPEN, 0);
#endif
        break;
    case TWS_EVENT_MONITOR_START:
        break;
    case TWS_EVENT_PHONE_LINK_DETACH:
        /*
         * 跟手机的链路LMP层已完全断开, 只有tws在连接状态才会收到此事件
         */
        break;
    case TWS_EVENT_ROLE_SWITCH:
        break;
    }

    return FALSE;
}

REGISTER_APP_EVENT_HANDLER(le_audio_sync_tws_event) = {
    .event      = SYS_BT_EVENT,
    .from       = BT_EVENT_FROM_TWS,
    .handler    = le_audio_sync_tws_event_handler,
};
#endif

#endif

int le_audio_scene_deal(int scene)
{
#if (TCFG_LEA_BIG_CTRLER_TX_EN || TCFG_LEA_BIG_CTRLER_RX_EN)
    return app_broadcast_deal(scene);
#endif

#if (TCFG_LEA_CIG_CENTRAL_EN || TCFG_LEA_CIG_PERIPHERAL_EN)
    return app_connected_deal(scene);
#endif

#if (TCFG_LE_AUDIO_APP_CONFIG & (LE_AUDIO_AURACAST_SINK_EN | LE_AUDIO_AURACAST_SOURCE_EN))
    return app_auracast_deal(scene);
#endif

    return -EPERM;
}

int update_le_audio_deal_scene(int scene)
{
#if (TCFG_LEA_BIG_CTRLER_TX_EN || TCFG_LEA_BIG_CTRLER_RX_EN)
    return update_app_broadcast_deal_scene(scene);
#endif

#if (TCFG_LEA_CIG_CENTRAL_EN || TCFG_LEA_CIG_PERIPHERAL_EN)
    return update_app_connected_deal_scene(scene);
#endif

#if (TCFG_LE_AUDIO_APP_CONFIG & (LE_AUDIO_AURACAST_SINK_EN | LE_AUDIO_AURACAST_SOURCE_EN))
    return update_app_auracast_deal_scene(scene);
#endif

    return -EPERM;
}

u8 get_le_audio_app_mode_exit_flag(void)
{
#if (TCFG_LEA_BIG_CTRLER_TX_EN || TCFG_LEA_BIG_CTRLER_RX_EN)
    return get_broadcast_app_mode_exit_flag();
#endif

#if (TCFG_LEA_CIG_CENTRAL_EN || TCFG_LEA_CIG_PERIPHERAL_EN)
    return get_connected_app_mode_exit_flag();
#endif

#if (TCFG_LE_AUDIO_APP_CONFIG & (LE_AUDIO_AURACAST_SINK_EN | LE_AUDIO_AURACAST_SOURCE_EN))
    return get_auracast_app_mode_exit_flag();
#endif

    return 0;
}

u8 get_le_audio_curr_role(void) //1:transmitter; 2:recevier
{
#if (TCFG_LEA_BIG_CTRLER_TX_EN || TCFG_LEA_BIG_CTRLER_RX_EN)
    return get_broadcast_role();
#endif

#if (TCFG_LEA_CIG_CENTRAL_EN || TCFG_LEA_CIG_PERIPHERAL_EN)
#if (TCFG_LEA_CIG_TRANS_MODE == 2)
    return 1;
#else
    return get_connected_role();
#endif
#endif

#if (TCFG_LE_AUDIO_APP_CONFIG & (LE_AUDIO_AURACAST_SINK_EN | LE_AUDIO_AURACAST_SOURCE_EN))
    return get_auracast_role();
#endif

    return 0;
}

u8 get_le_audio_switch_onoff(void) //1:on; 0:off
{
#if (TCFG_LEA_BIG_CTRLER_TX_EN || TCFG_LEA_BIG_CTRLER_RX_EN)
    return get_bis_switch_onoff();
#endif

#if (TCFG_LEA_CIG_CENTRAL_EN || TCFG_LEA_CIG_PERIPHERAL_EN)
    return get_cis_switch_onoff();
#endif

#if (TCFG_LE_AUDIO_APP_CONFIG & (LE_AUDIO_AURACAST_SINK_EN | LE_AUDIO_AURACAST_SOURCE_EN))
    return get_auracast_switch_onoff();
#endif

    return 0;
}

void le_audio_switch_onoff(void)
{
#if (TCFG_LEA_BIG_CTRLER_TX_EN || TCFG_LEA_BIG_CTRLER_RX_EN)
    app_broadcast_switch();
#endif
#if (TCFG_LE_AUDIO_APP_CONFIG & (LE_AUDIO_AURACAST_SINK_EN | LE_AUDIO_AURACAST_SOURCE_EN))
    app_auracast_switch();
#endif
}

#if TCFG_LE_AUDIO_STREAM_ENABLE
static int le_audio_key_double_click_event(struct key_event *key)
{
    int ret = FALSE;

    switch (key->value) {
    case KEY_OK:
        le_audio_switch_onoff();
        ret = TRUE;
        break;
    default:
        break;
    }

    return ret;
}

static int le_audio_key_event_handler(void *evt)
{
    struct key_event *key = (struct key_event *)evt;
    int ret = FALSE;

    switch (key->action) {
    case KEY_EVENT_DOUBLE_CLICK:
        ret = le_audio_key_double_click_event(key);
        break;
    default:
        break;
    }

    return ret;
}

REGISTER_APP_EVENT_HANDLER(le_audio_key_event) = {
    .event      = SYS_KEY_EVENT,
    .from       = KEY_EVENT_FROM_KEY,
    .handler    = le_audio_key_event_handler,
};
#endif
