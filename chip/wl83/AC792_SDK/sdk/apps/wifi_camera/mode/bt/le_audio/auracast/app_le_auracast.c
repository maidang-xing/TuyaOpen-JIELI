#include "system/includes.h"
#include "app_le_auracast.h"
#include "wireless_trans.h"
#include "le/auracast_source_api.h"
#include "le/auracast_sink_api.h"
#include "app_config.h"
#include "btstack/avctp_user.h"
#include "app_tone.h"
#include "app_msg.h"
#include "audio_config.h"
#include "le_audio_player.h"
#include "a2dp_player.h"
#include "pc_spk_player.h"
#include "file_player.h"
#include "net_file_player.h"
#include "vol_sync.h"
#include "btstack/le/auracast_delegator_api.h"
#include "btstack/le/att.h"
#include "btstack/le/ble_api.h"
#include "btctrler/ble/hci_ll.h"
#include "asm/power_interface.h"

#if (TCFG_LE_AUDIO_APP_CONFIG & (LE_AUDIO_AURACAST_SINK_EN | LE_AUDIO_AURACAST_SOURCE_EN))

#if (THIRD_PARTY_PROTOCOLS_SEL & MULTI_BOX_ADV_EN)
#include "multi_box_adv/multi_box_adv.h"
#endif

/**************************************************************************************************
  Macros
**************************************************************************************************/
#define LOG_TAG             "[APP_LE_AURACAST]"
#define LOG_ERROR_ENABLE
#define LOG_DEBUG_ENABLE
#define LOG_INFO_ENABLE
/* #define LOG_DUMP_ENABLE */
#define LOG_CLI_ENABLE
#include "debug.h"

/****
| sampling_frequency| variant  | 采样率 | 帧间隔(us) | 包长(字节) | 码率(kbps) |
| ----------------- | -------- | ------ | ---------- | -----------| -----------|
|        0          |    0     | 8000   | 7500       | 26         | 27.732     |
|        0          |    1     | 8000   | 10000      | 30         | 24         |
|        1          |    0     | 16000  | 7500       | 30         | 32         |
|        1          |    1     | 16000  | 10000      | 40         | 32         |
|        2          |    0     | 24000  | 7500       | 45         | 48         |
|        2          |    1     | 24000  | 10000      | 60         | 48         |
|        3          |    0     | 32000  | 7500       | 60         | 64         |
|        3          |    1     | 32000  | 10000      | 80         | 64         |
|        4          |    0     | 44100  | 8163       | 97         | 95.06      |
|        4          |    1     | 44100  | 10884      | 130        | 95.55      |
|        5          |    0     | 48000  | 7500       | 75         | 80         |
|        5          |    1     | 48000  | 10000      | 100        | 80         |
****/

/**************************************************************************************************
  Macros
**************************************************************************************************/
#ifndef AURACAST_SOURCE_BIS_NUMS
#define AURACAST_SOURCE_BIS_NUMS             (2)
#endif
#ifndef AURACAST_SINK_BIS_NUMS
#define AURACAST_SINK_BIS_NUMS               (2)
#endif
#define MAX_BIS_NUMS                         MAX(AURACAST_SOURCE_BIS_NUMS, AURACAST_SINK_BIS_NUMS)

#define AURACAST_BIS_ENCRYPTION_ENABLE       (0)

/**************************************************************************************************
  Data Types
**************************************************************************************************/
enum {
    ///0x1000起始为了不要跟提示音的IDEX_TONE_重叠了
    TONE_INDEX_AURACAST_OPEN = 0x1000,
    TONE_INDEX_AURACAST_CLOSE,
};

struct app_auracast_info_t {
    bool init_ok;
    u16 bis_hdl;
};

struct broadcast_source_endpoint_notify {
    uint8_t prd_delay[3];
    uint8_t num_subgroups;
    uint8_t num_bis;
    uint8_t codec_id[5];
    uint8_t codec_spec_length;
    uint8_t codec_spec_data[0];
    uint8_t metadata_length;
    uint8_t bis_data[0];
} __attribute__((packed));

struct auracast_adv_info {
    uint16_t length;
    uint8_t flag;
    uint8_t op;
    uint8_t sn;
    //uint8_t seq;
    uint8_t data[0];
    uint8_t crc[0];
} __attribute__((packed));

struct app_auracast_t {
    u8 status;
    u8 role;
    u8 bis_num;
    u8 big_hdl;
    void *recorder;
    struct le_audio_player_hdl rx_player;
    struct app_auracast_info_t bis_hdl_info[MAX_BIS_NUMS];
};

struct broadcast_featrue_notify {
    uint8_t feature;
    uint8_t metadata_len;
    uint8_t metadata[20];
} __attribute__((packed));

struct broadcast_base_info_notify {
    uint8_t address_type;
    uint8_t address[6];
    uint8_t adv_sid;
    uint16_t pa_interval;
} __attribute__((packed));

struct broadcast_codec_info {
    uint8_t nch;
    u32 coding_type;
    s16 frame_len;
    s16 sdu_period;
    int sample_rate;
    int bit_rate;
} __attribute__((packed));

typedef struct {
    uint8_t  save_auracast_addr[NO_PAST_MAX_BASS_NUM_SOURCES][6];
    uint8_t encryp_addr[NO_PAST_MAX_BASS_NUM_SOURCES][6];
    uint8_t  broadcast_name[28];
    uint32_t  broadcast_id;
    uint8_t enc;
    struct  broadcast_featrue_notify fea_data;
    struct broadcast_base_info_notify base_data;
    struct broadcast_codec_info codec_data;
} bass_no_past_source_t;

static const struct _auracast_code_list_t {
    u32 sample_rate;
    u32 frame_len;
    u16 max_SDU_octets;   // (bytes / ch)
    u32 bit_rate;         // (bps / ch)
} auracast_code_list[6][2] = {
    {
        { 8000, 7500, 26, 27732 },
        { 8000, 10000, 30, 24000 },
    },
    {
        { 16000, 7500, 30, 32000 },
        { 16000, 10000, 40, 32000 },
    },
    {
        { 24000, 7500, 45, 48000 },
        { 24000, 10000, 60, 48000 },
    },
    {
        { 32000, 7500, 60, 64000 },
        { 32000, 10000, 80, 64000 },
    },
    {
        { 44100, 8163, 97, 95060 },
        { 44100, 10884, 130, 95550 },
    },
    {
        { 48000, 7500, 75, 80000 },
        { 48000, 10000, 100, 80000 },
    },
};

/**************************************************************************************************
  Local Function Prototypes
**************************************************************************************************/
static int auracast_source_media_open(void);
static int auracast_source_media_close(void);
static int auracast_source_media_reset(void);
static void auracast_iso_rx_callback(uint8_t *packet, uint16_t size);
static int auracast_sink_media_open(uint16_t bis_hdl, uint8_t *packet, uint16_t length);
static int auracast_sink_media_close(void);
static int auracast_sink_record_mac_addr(u8 *mac_addr);
static int auracast_sink_get_mac_addr_is_recorded(u8 *mac_addr);
static void auracast_sink_connect_filter_timeout(void *priv);

/**************************************************************************************************
  Local Global Variables
**************************************************************************************************/
static OS_MUTEX mutex;
static u8 app_auracast_init_flag = 0;
static u8 auracast_app_mode_exit = 0;  /*!< 音源模式退出标志 */
static u8 config_auracast_as_master = 0;   /*!< 配置广播强制做主机 */
static int cur_deal_scene = -1; /*< 当前系统处于的运行场景 */
static struct app_auracast_t app_auracast;
static struct le_audio_mode_ops *le_audio_switch_ops = NULL; /*!< 广播音频和本地音频切换回调接口指针 */
static char auracast_listen_name[28] = "JL_AC792N_AURACAST";
static u16 multi_bis_rx_temp_buf_len;
static u8 *multi_bis_rx_buf[7];
static u16 multi_bis_data_offect[7];
static bool multi_bis_plc_flag[7];
static u8 g_sink_bn = 0;
static u8 *tx_temp_buf = 0;
static u16 tx_temp_buf_len = 0;
static u8 prev_volume;

static const unsigned char errpacket[2] = {
    0x02, 0x00
};

static const auracast_user_config_t user_config = {
    .config_num_bis = AURACAST_SOURCE_BIS_NUMS,
    .config_sampling_frequency = AURACAST_BIS_SAMPLING_RATE,
    .config_variant = AURACAST_BIS_VARIANT,
    .encryption = AURACAST_BIS_ENCRYPTION_ENABLE,
    .broadcast_id = 0x123456,
    .broadcast_name = "JL_AC792N_AURACAST",
};
static const auracast_advanced_config_t user_advanced_config = {
    .bn = AURACAST_ISO_BN,
    .rtn = AURACAST_BIS_RTN,
    .adv_cnt = 3,
    .big_offset = 1500,
};

static u16 auracast_sink_sync_timeout_hdl = 0;
static auracast_sink_source_info_t *cur_listening_source_info = NULL;						// 当前正在监听广播设备播歌的信息

u8 lea_cfg_support_ll_hci_cmd_in_lea_lib = 1;


#define AURACAST_SINK_MAX_RECORD_NUM  3
#define AURACAST_SINK_RECORDED_WIRTE_VM     0
#define AURACAST_SINK_FILTER_TIMEOUT  0*1000L

static u8 auracast_sink_start_record = 0;
static u8 auracast_sink_curr_connect_mac_addr[6];
static u8 auracast_sink_last_connect_mac_addr[6];
static u8 auracast_sink_record_connect_mac_addr[AURACAST_SINK_MAX_RECORD_NUM][6];
static u8 auarcast_sink_mac_addr_filter = 0;
static u32 auracast_sink_connect_timeout = 0;
static u8 auracast_switch_onoff = 0;

static u8 le_auracast_state = 0;
static u16 auracast_scan_time = 0;
static u16 multi_box_bis_role_change_timer;
extern void set_ext_scan_priority(u8 set_pr);

static u8 app_auracast_idle_query(void)
{
    return auracast_switch_onoff == 0;
}

REGISTER_LP_TARGET(app_auracast_lp_target) = {
    .name       = "auracast",
    .is_idle    = app_auracast_idle_query,
};

u32 get_auracast_sdu_size(void)
{
    u16 frame_dms;
    if (auracast_code_list[AURACAST_BIS_SAMPLING_RATE][AURACAST_BIS_VARIANT].frame_len >= 10000) {
        frame_dms = 100;
    } else {
        frame_dms = 75;
    }
    return (frame_dms * auracast_code_list[AURACAST_BIS_SAMPLING_RATE][AURACAST_BIS_VARIANT].bit_rate / 8 / 1000 / 10);
}

/* --------------------------------------------------------------------------*/
/**
 * @brief 广播资源初始化
 */
/* ----------------------------------------------------------------------------*/
void app_auracast_init(void)
{
    if (app_auracast_init_flag) {
        return;
    }

    int os_ret = os_mutex_create(&mutex);
    if (os_ret != OS_NO_ERR) {
        log_error("%s %d err, os_ret:0x%x", __FUNCTION__, __LINE__, os_ret);
        ASSERT(0);
    }

    app_auracast_init_flag = 1;
}

/* --------------------------------------------------------------------------*/
/**
 * @brief 广播资源初始化
 */
/* ----------------------------------------------------------------------------*/
void app_auracast_uninit(void)
{
    if (!app_auracast_init_flag) {
        return;
    }

    app_auracast_init_flag = 0;

    int os_ret = os_mutex_del(&mutex, OS_DEL_NO_PEND);
    if (os_ret != OS_NO_ERR) {
        log_error("%s %d err, os_ret:0x%x", __FUNCTION__, __LINE__, os_ret);
    }
}

/* --------------------------------------------------------------------------*/
/**
 * @brief 申请互斥量，用于保护临界区代码，与app_broadcast_mutex_post成对使用
 *
 * @param mutex:已创建的互斥量指针变量
 */
/* ----------------------------------------------------------------------------*/
static inline void app_auracast_mutex_pend(OS_MUTEX *mutex, u32 line)
{
    if (!app_auracast_init_flag) {
        log_error("%s err, mutex uninit", __FUNCTION__);
        return;
    }

    int os_ret = os_mutex_pend(mutex, 0);
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
static inline void app_auracast_mutex_post(OS_MUTEX *mutex, u32 line)
{
    if (!app_auracast_init_flag) {
        log_error("%s err, mutex uninit", __FUNCTION__);
        return;
    }

    int os_ret = os_mutex_post(mutex);
    if (os_ret != OS_NO_ERR) {
        log_error("%s err, os_ret:0x%x", __FUNCTION__, os_ret);
        ASSERT(os_ret != OS_ERR_PEND_ISR, "line:%d err, os_ret:0x%x", line, os_ret);
    }
}

void auracast_scan_switch_priority(void *_sw)
{
    int sw = (int)_sw;
    u8 bt_addr[6];
    int timeout = 150;
    u8 a2dp_play = 0;

    if (a2dp_player_get_btaddr(bt_addr)) {
        a2dp_play = 1;
    }
    /* r_printf("auracast_scan_switch=%d,%d\n",sw,timeout ); */
    //edr classic acl priority 30-11=19
    if (sw) {
        /* putchar('S'); */
        set_ext_scan_priority(12);//30-12=18
    } else {
        /* putchar('s'); */
        set_ext_scan_priority(8);//30-8=22
        timeout = a2dp_play ? 300 : 400;
    }
    sw = !sw;
    auracast_scan_time = sys_timeout_add((void *)sw, auracast_scan_switch_priority, timeout);
}

/**************************************************************************************************
  Function Declarations
**************************************************************************************************/
u8 get_auracast_role(void)
{
    return app_auracast.role;
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
static int auracast_tone_play_end_callback(void *priv, enum stream_event event)
{
    u32 index = (u32)priv;

    /* g_printf("%s, event:0x%x", __FUNCTION__, event); */

    switch (event) {
    case STREAM_EVENT_NONE:
    case STREAM_EVENT_STOP:
        switch (index) {
        case TONE_INDEX_AURACAST_OPEN:
            log_info("TONE_INDEX_AURACAST_OPEN");
            break;
        case TONE_INDEX_AURACAST_CLOSE:
            log_info("TONE_INDEX_AURACAST_CLOSE");
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
 * @brief 获取接收方连接状态
 *
 * @return 接收方连接状态
 */
/* ----------------------------------------------------------------------------*/
u8 get_auracast_status(void)
{
    return app_auracast.status;
}

/* --------------------------------------------------------------------------*/
/**
 * @brief 获取当前是否在退出模式的状态
 *
 * @return 1；是，0：否
 */
/* ----------------------------------------------------------------------------*/
u8 get_auracast_app_mode_exit_flag(void)
{
    return auracast_app_mode_exit;
}

/* --------------------------------------------------------------------------*/
/**
 * @brief 判断当前设备作为广播发送设备还是广播接收设备
 *
 * @return true:发送设备，false:接收设备
 */
/* ----------------------------------------------------------------------------*/
static bool is_auracast_as_source(void)
{
#if (TCFG_LEA_BIG_FIX_ROLE == LEA_ROLE_AS_TX)
    return true;
#elif (TCFG_LEA_BIG_FIX_ROLE == LEA_ROLE_AS_RX)
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
        if (linein_get_status() || config_auracast_as_master) {
            return true;
        } else {
            return false;
        }
    }
#endif

#if TCFG_APP_IIS_EN
    if (cur_mode == APP_MODE_IIS)  {
        if (iis_get_status() || config_auracast_as_master) {
            return true;
        } else {
            return false;
        }
    }
#endif

#if TCFG_APP_MIC_EN
    if (cur_mode == APP_MODE_MIC)  {
        if (mic_get_status() || config_auracast_as_master) {
            return true;
        } else {
            return false;
        }
    }
#endif

#if TCFG_APP_MUSIC_EN
    if (cur_mode == APP_MODE_LOCAL) {
        if ((music_file_get_player_status(get_music_file_player()) == FILE_PLAYER_START) || config_auracast_as_master) {
            return true;
        } else {
            return false;
        }
    }
#endif

#if TCFG_APP_FM_EN
    //当处于下面几种模式时，作为广播发送设备
    if (cur_mode == APP_MODE_FM)  {
        if (fm_get_fm_dev_mute() == 0 || config_auracast_as_master) {
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
        /* if (spdif_player_runing() ||  config_auracast_as_master) { */
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
        if (pc_spk_player_runing() || config_auracast_as_master) {
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
static bool is_need_resume_auracast(void)
{
    if (app_auracast.status == APP_AURACAST_STATUS_SUSPEND) {
        return true;
    } else {
        return false;
    }
}

/* --------------------------------------------------------------------------*/
/**
 * @brief 广播从挂起状态恢复
 */
/* ----------------------------------------------------------------------------*/
static void app_auracast_resume(void)
{
    if (!is_need_resume_auracast()) {
        return;
    }

    app_auracast_open();
}

/* --------------------------------------------------------------------------*/
/**
 * @brief 广播进入挂起状态
 */
/* ----------------------------------------------------------------------------*/
static void app_auracast_suspend(void)
{
    if (app_auracast.role == APP_AURACAST_AS_SOURCE) {
        app_auracast_source_close(APP_AURACAST_STATUS_SUSPEND);
    } else if (app_auracast.role == APP_AURACAST_AS_SINK) {
        app_auracast_sink_close(APP_AURACAST_STATUS_SUSPEND);
    }
}
/* --------------------------------------------------------------------------*/
/**
 * @brief 开启广播
 *
 * @return >=0:success
 */
/* ----------------------------------------------------------------------------*/
int app_auracast_open(void)
{
    if (!app_auracast_init_flag) {
        return -EPERM;
    }

    app_mode_t mode = get_current_app_mode();
    if (mode && (mode == APP_MODE_BT) &&
        (bt_get_call_status() != BT_CALL_HANGUP)) {
        return -EPERM;
    }

    log_info("auracast_open");

    app_auracast_mutex_pend(&mutex, __LINE__);

#if TCFG_KBOX_1T3_MODE_EN
    le_audio_ops_register(APP_MODE_NULL);
#endif

    if (is_auracast_as_source()) {
        //初始化广播发送端参数
        app_auracast_source_open();
    } else {
        //初始化广播接收端参数
        app_auracast_sink_open();
    }

    app_auracast_mutex_post(&mutex, __LINE__);

    return 0;
}

static bool match_name(const char *target_name, const char *source_name, size_t target_len)
{
    if (strlen(target_name) == 0 || strlen(source_name) == 0) {
        return FALSE;
    }

    if (0 == memcmp(target_name, source_name, target_len)) {
        return TRUE;
    }

    return FALSE;
}

void read_auracast_listen_name(void)
{
#if 0
    int len = syscfg_read(CFG_AURACAST_LISTEN_NAME, auracast_listen_name, sizeof(auracast_listen_name));
    if (len <= 0) {
        r_printf("ERR:Can not read the auracast listen name\n");
        return;
    }
#endif

    //put_buf((const u8 *)auracast_listen_name, sizeof(auracast_listen_name));
    log_info("sink_listen_name:%s", auracast_listen_name);
}

static void auracast_sync_info_report(uint8_t *packet, uint16_t length)
{
    if (!app_auracast_init_flag) {
        return;
    }
    app_auracast_mutex_pend(&mutex, __LINE__);
    if (app_auracast.status == APP_AURACAST_STATUS_STOP || app_auracast.status == APP_AURACAST_STATUS_SUSPEND) {
        app_auracast_mutex_post(&mutex, __LINE__);
        return;
    }
    auracast_sink_source_info_t *config = (auracast_sink_source_info_t *)packet;
    ASSERT(config, "config is NULL");
    log_info("sync create");
    log_info("Advertising_SID[%d]Address_Type[%d]ADDR:", config->Advertising_SID, config->Address_Type);
    put_buf(config->source_mac_addr, 6);
    log_info("auracast name:%s", config->broadcast_name);

    if (match_name(auracast_listen_name, "no_match_name", strlen(auracast_listen_name))) {
        //不匹配设备名，搜到直接同步，如需匹配设备名，请#if 0
        log_info("no need match name");
        app_auracast_sink_big_sync_create(config);
        app_auracast_mutex_post(&mutex, __LINE__);
        return;
    }

#if 0
    printf("last_connect_addr:\n");
    put_buf(auracast_sink_last_connect_mac_addr, 6);

    if ((!memcmp(auracast_sink_last_connect_mac_addr, config->source_mac_addr, 6)) && auracast_sink_start_record) {
#if AURACAST_SINK_FILTER_TIMEOUT
        if (!auracast_sink_connect_timeout) {
            auracast_sink_connect_timeout = sys_timeout_add(NULL, auracast_sink_connect_filter_timeout, AURACAST_SINK_FILTER_TIMEOUT);
        }
#endif
        app_auracast_mutex_post(&mutex, __LINE__);
        //auracast_sink_rescan();
        return ;
    }

    if (auarcast_sink_mac_addr_filter) {
        /* for(int i = 0; i < AURACAST_SINK_MAX_RECORD_NUM; i++){ */
        /*     printf("recorded_addr[%d]:", i); */
        /*     put_buf(auracast_sink_record_connect_mac_addr[i],6); */
        /* } */
        if ((auracast_sink_get_mac_addr_is_recorded(config->source_mac_addr))) {
#if AURACAST_SINK_FILTER_TIMEOUT
            if (auracast_sink_connect_timeout) {
                sys_timeout_del(auracast_sink_connect_timeout);
                auracast_sink_connect_timeout =  0;
            }
#endif
            app_auracast_sink_big_sync_create(config);
        } else {
            app_auracast_mutex_post(&mutex, __LINE__);
            //auracast_sink_rescan();
            return ;
        }
    } else {
#if AURACAST_SINK_FILTER_TIMEOUT
        if (auracast_sink_connect_timeout) {
            sys_timeout_del(auracast_sink_connect_timeout);
            auracast_sink_connect_timeout =  0;
        }
#endif
        app_auracast_sink_big_sync_create(config);
    }
    ;
    if (auracast_sink_start_record) {
        auracast_sink_record_mac_addr(config->source_mac_addr);
    }

    memcpy(auracast_sink_curr_connect_mac_addr, config->source_mac_addr, 6);
    app_auracast_mutex_post(&mutex, __LINE__);
    return;

#endif

    if (match_name((void *)config->broadcast_name, auracast_listen_name, strlen(auracast_listen_name))) {
        log_info("auracast name match");
        app_auracast_sink_big_sync_create(config);
        app_auracast_mutex_post(&mutex, __LINE__);
    } else {
        log_info("auracast name no match");
        app_auracast_mutex_post(&mutex, __LINE__);
        //auracast_sink_rescan();
    }
}

static int auracast_sink_sync_create(uint8_t *packet, uint16_t length)
{
    auracast_sink_source_info_t *config = (auracast_sink_source_info_t *)packet;

    if (!app_auracast_init_flag) {
        return -1;
    }

    app_auracast_mutex_pend(&mutex, __LINE__);
    if (app_auracast.status == APP_AURACAST_STATUS_STOP || app_auracast.status == APP_AURACAST_STATUS_SUSPEND) {
        app_auracast_mutex_post(&mutex, __LINE__);
        return -1;
    }

    if (config->Num_BIS > AURACAST_SINK_BIS_NUMS) {
        app_auracast.bis_num = AURACAST_SINK_BIS_NUMS;
    } else {
        app_auracast.bis_num = config->Num_BIS;
    }

    app_auracast.big_hdl = config->BIG_Handle;
    app_auracast.status = APP_AURACAST_STATUS_SYNC;

    u16 frame_dms = 0;
    if (config->frame_duration == FRAME_DURATION_7_5) {
        frame_dms = 75;
    } else if (config->frame_duration == FRAME_DURATION_10) {
        frame_dms = 100;
    } else {
        ASSERT(0, "frame_dms err:%d", config->frame_duration);
    }
    log_info("bis_num:%d, big_hdl:0x%x, config->Num_BIS:%d", app_auracast.bis_num, app_auracast.big_hdl, config->Num_BIS);

    auracast_sink_media_open(config->Connection_Handle[0], packet, length);

    if (app_auracast.bis_num > 1) {
        for (u8 i = 0; i < g_sink_bn; i++) {
            if (!multi_bis_rx_buf[i]) {
                multi_bis_rx_temp_buf_len = app_auracast.bis_num * config->bit_rate * frame_dms / 8 / 1000 / 10;
                log_info("multi_bis_rx_temp_buf_len:%d", multi_bis_rx_temp_buf_len);
                multi_bis_rx_buf[i] = zalloc(multi_bis_rx_temp_buf_len);
            }
        }
    }

    for (u8 i = 0; i < app_auracast.bis_num; i++) {
        app_auracast.bis_hdl_info[i].bis_hdl = config->Connection_Handle[i];
        app_auracast.bis_hdl_info[i].init_ok = 1;
        log_info("bis_hdl:0x%x", app_auracast.bis_hdl_info[i].bis_hdl);
    }

    app_auracast_mutex_post(&mutex, __LINE__);

    return 0;
}

static int auracast_sink_sync_terminate(uint8_t *packet, uint16_t length)
{
    if (!app_auracast_init_flag) {
        return -1;
    }

    app_auracast_mutex_pend(&mutex, __LINE__);
    if (app_auracast.status == APP_AURACAST_STATUS_STOP || app_auracast.status == APP_AURACAST_STATUS_SUSPEND) {
        app_auracast_mutex_post(&mutex, __LINE__);
        return -1;
    }

    for (u8 i = 0; i < app_auracast.bis_num; i++) {
        app_auracast.bis_hdl_info[i].init_ok = 0;
    }

    for (u8 i = 0; i < g_sink_bn; i++) {
        if (multi_bis_rx_buf[i]) {
            free(multi_bis_rx_buf[i]);
            multi_bis_rx_buf[i] = 0;
        }
    }
    auracast_sink_media_close();

    app_auracast.bis_num = 0;
    app_auracast.big_hdl = 0;
    app_auracast.status = APP_AURACAST_STATUS_SCAN;

    app_auracast_sink_scan_start();

    app_auracast_mutex_post(&mutex, __LINE__);

    return 0;
}

/**
 * @brief 设备收到广播设备信息汇报给手机APP
 */
static void auracast_sink_source_info_report_event_deal(uint8_t *packet, uint16_t length)
{
    auracast_sync_info_report(packet, length);
}

static void auracast_sink_big_info_report_event_deal(uint8_t *packet, uint16_t length)
{
    auracast_sink_source_info_t *param = (auracast_sink_source_info_t *)packet;
    g_sink_bn = param->bn;
    log_info("auracast_sink_big_info_report_event_deal");
    log_info("num bis : %d, bn : %d", param->Num_BIS, g_sink_bn);
    if (param->Num_BIS > AURACAST_SINK_BIS_NUMS) {
        param->Num_BIS = AURACAST_SINK_BIS_NUMS;
    }
    //param->Num_BIS = 1;
}

static void auracast_sink_event_callback(uint16_t event, uint8_t *packet, uint16_t length)
{
    if (!app_auracast_init_flag) {
        return;
    }

    switch (event) {
    case AURACAST_SINK_SOURCE_INFO_REPORT_EVENT:
        log_info("AURACAST_SINK_SOURCE_INFO_REPORT_EVENT");
        auracast_sink_source_info_report_event_deal(packet, length);
        break;
    case AURACAST_SINK_BLE_CONNECT_EVENT:
        log_info("AURACAST_SINK_BLE_CONNECT_EVENT");
        break;
    case AURACAST_SINK_BIG_SYNC_CREATE_EVENT:
        log_info("AURACAST_SINK_BIG_SYNC_CREATE_EVENT");

        ASSERT(cur_listening_source_info);
        memcpy(cur_listening_source_info, auracast_sink_listening_source_info_get(), sizeof(auracast_sink_source_info_t));

        if (auracast_sink_sync_timeout_hdl != 0) {
            sys_timeout_del(auracast_sink_sync_timeout_hdl);
            auracast_sink_sync_timeout_hdl = 0;
        }

        if (current_app_in_mode(APP_MODE_PC)) {
            app_msg_handler("pc_music", APP_MSG_SUSPEND);
        }
#if (THIRD_PARTY_PROTOCOLS_SEL & MULTI_BOX_ADV_EN)
        app_auracast_mutex_pend(&mutex, __LINE__);
        multi_box_bis_role_change(MULTI_BOX_ROLE_SLAVE);
        app_auracast_mutex_post(&mutex, __LINE__);
#endif
        app_send_message(APP_MSG_BT_DISCONNECT, 0);
        auracast_sink_sync_create(packet, length);
        //le_auracast_audio_open(packet, length);
        //app_auracast_app_notify_listening_status(2, 0);
        break;
    case AURACAST_SINK_BIG_SYNC_TERMINATE_EVENT:
        //主动解除同步
        log_info("AURACAST_SINK_BIG_SYNC_TERMINATE_EVENT");
        break;
    case AURACAST_SINK_BIG_SYNC_FAIL_EVENT:
    case AURACAST_SINK_BIG_SYNC_LOST_EVENT:
        log_warn("big lost or fail");
        auracast_sink_sync_terminate(packet, length);
        //app_auracast_app_notify_listening_status(0, 2);
        if (cur_listening_source_info) {
            free(cur_listening_source_info);
            cur_listening_source_info = NULL;
        }
        break;
    case AURACAST_SINK_PERIODIC_ADVERTISING_SYNC_LOST_EVENT:
        if (cur_listening_source_info) {
            log_info("AURACAST_SINK_PERIODIC_ADVERTISING_SYNC_LOST_EVENT");
            app_auracast_sink_big_sync_create(cur_listening_source_info);
        } else {
            log_warn("AURACAST_SINK_PERIODIC_ADVERTISING_SYNC_LOST_EVENT FAIL!");
        }
        break;
    case AURACAST_SINK_BIG_INFO_REPORT_EVENT:
        log_info("AURACAST_SINK_BIG_INFO_REPORT_EVENT");
        auracast_sink_big_info_report_event_deal(packet, length);
        break;
    case AURACAST_SINK_ISO_RX_CALLBACK_EVENT:
        //printf("AURACAST_SINK_ISO_RX_CALLBACK_EVENT\n");
        //获取音频数据
        auracast_iso_rx_callback(packet, length);
        break;
    case AURACAST_SINK_EXT_SCAN_COMPLETE_EVENT:
        log_info("AURACAST_SINK_EXT_SCAN_COMPLETE_EVENT");
        break;
    case AURACAST_SINK_PADV_REPORT_EVENT:
        //log_info("AURACAST_SINK_PADV_REPORT_EVENT");
        //put_buf(packet, length);
        if (packet[length - 3] == 2 && packet[length - 2] == 0xFF && prev_volume != packet[length - 1]) {
            prev_volume = packet[length - 1];
#if (THIRD_PARTY_PROTOCOLS_SEL & MULTI_BOX_ADV_EN)
            void multi_box_bis_change_volume_deal(u8 volume);
            multi_box_bis_change_volume_deal(prev_volume);
#endif
        }
        break;
    default:
        break;
    }
}

static void app_auracast_sink_init(void)
{
    log_info("app_auracast_sink_init");

    auracast_sink_init(AURACAST_SINK_API_VERSION);
    auracast_sink_event_callback_register(auracast_sink_event_callback);

    //le_audio_bass_event_callback_register(app_auracast_bass_server_event_callback);
}

static int __app_auracast_sink_big_sync_terminate(void)
{
    if (cur_listening_source_info) {
        free(cur_listening_source_info);
        cur_listening_source_info = NULL;
    }
    int ret = auracast_sink_big_sync_terminate();
    if (0 == ret) {
        //le_auracast_audio_close();
        if (auracast_sink_sync_timeout_hdl != 0) {
            sys_timeout_del(auracast_sink_sync_timeout_hdl);
            auracast_sink_sync_timeout_hdl = 0;
        }
    }
    return ret;
}

/**
 * @brief 关闭所有正在监听播歌的广播设备
 */
int app_auracast_sink_big_sync_terminate(void)
{
    log_info("app_auracast_sink_big_sync_terminate");
    return __app_auracast_sink_big_sync_terminate();
}

/**
 * @brief 手机通知设备开始搜索auracast广播
 */
int app_auracast_sink_scan_start(void)
{
    int ret = auracast_sink_scan_start();
    log_info("app_auracast_sink_scan_start ret:%d, ret");
    return ret;
}

/**
 * @brief 手机通知设备关闭搜索auracast广播
 */
int app_auracast_sink_scan_stop(void)
{
    int ret = auracast_sink_scan_stop();
    log_info("app_auracast_sink_scan_stop ret:%d", ret);
    return ret;
}

static void auracast_sink_sync_timeout_handler(void *priv)
{
    if (app_auracast.role == APP_AURACAST_AS_SINK) {
        log_info("auracast_sink_sync_timeout_handler");
        auracast_sink_scan_stop();
        auracast_sink_big_sync_terminate();
    }
    //app_auracast_app_notify_listening_status(0, 2);
    auracast_sink_sync_timeout_hdl = 0;
}

static int __app_auracast_sink_big_sync_create(auracast_sink_source_info_t *param, u8 tws_malloc)
{
    if (cur_listening_source_info == NULL) {
        cur_listening_source_info = malloc(sizeof(auracast_sink_source_info_t));
    }
    memcpy(cur_listening_source_info, param, sizeof(auracast_sink_source_info_t));
    //put_buf(cur_listening_source_info->source_mac_addr, 6);
    int ret = auracast_sink_big_sync_create(cur_listening_source_info);
    if (0 == ret) {
        //auracast_sink_sync_timeout_hdl = sys_timeout_add(NULL, auracast_sink_sync_timeout_handler, 15000);
    } else {
        log_error("__app_auracast_sink_big_sync_create ret:%d", ret);
    }
    if (tws_malloc) {
        free(param);
    }

    return ret;
}

/**
 * @brief 手机选中广播设备开始播歌
 *
 * @param param 要监听的广播设备
 */
int app_auracast_sink_big_sync_create(auracast_sink_source_info_t *param)
{
    log_info("app_auracast_sink_big_sync_create");

    //u8 bt_addr[6];
    if (auracast_sink_sync_timeout_hdl != 0) {
        log_error("auracast_sink_sync_timeout_hdl is not null");
        return -1;
    }

    /* if (esco_player_runing()) { */
    /* printf("app_auracast_sink_big_sync_create esco_player_runing\n"); */
    /* // 暂停auracast的播歌 */
    /* return -1; */
    /* } */

    /* if (a2dp_player_get_btaddr(bt_addr)) { */
    /* #if TCFG_A2DP_PREEMPTED_ENABLE */
    /* memcpy(a2dp_auracast_preempted_addr, bt_addr, 6); */
    /* a2dp_player_close(bt_addr); */
    /* a2dp_media_mute(bt_addr); */
    /* void *device = btstack_get_conn_device(bt_addr); */
    /* if (device) { */
    /* btstack_device_control(device, USER_CTRL_AVCTP_OPID_PAUSE); */
    /* } */
    /* #else */
    /* // 不抢播, 暂停auracast的播歌 */
    /* return -1; */
    /* #endif */
    /* } */

    return __app_auracast_sink_big_sync_create(param, 0);
}

/* --------------------------------------------------------------------------*/
/**
 * @brief 开启广播
 *
 * @return >=0:success
 */
/* ----------------------------------------------------------------------------*/
int app_auracast_sink_open(void)
{
    if (!app_auracast_init_flag) {
        return -EPERM;
    }

    if (app_auracast.status != APP_AURACAST_STATUS_STOP && app_auracast.status != APP_AURACAST_STATUS_SUSPEND) {
        return -EPERM;
    }

    app_mode_t mode = get_current_app_mode();
    if (mode && (mode == APP_MODE_BT) &&
        (bt_get_call_status() != BT_CALL_HANGUP)) {
        return -EPERM;
    }

#if (TCFG_LEA_BIG_FIX_ROLE == LEA_ROLE_AS_RX)
    le_audio_switch_ops = get_broadcast_audio_sw_ops();
    //关闭本地音频播放
    if (le_audio_switch_ops && le_audio_switch_ops->local_audio_close) {
        le_audio_switch_ops->local_audio_close();
    }
#endif

    auracast_switch_onoff = 1;

    log_info("auracast_sink_open");

    app_auracast_mutex_pend(&mutex, __LINE__);

    if (multi_box_bis_role_change_timer) {
        sys_timeout_del(multi_box_bis_role_change_timer);
        multi_box_bis_role_change_timer = 0;
    }

    read_auracast_listen_name();
    le_auracast_state = 0;
    app_auracast_sink_init();

    app_auracast_sink_scan_start();

    app_auracast.role = APP_AURACAST_AS_SINK;
    app_auracast.status = APP_AURACAST_STATUS_SCAN;

    app_auracast_mutex_post(&mutex, __LINE__);
    return 0;
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
int app_auracast_sink_close(u8 status)
{
    if (app_auracast.status == APP_AURACAST_STATUS_STOP || app_auracast.status == APP_AURACAST_STATUS_SUSPEND) {
        return -EPERM;
    }

    if (!app_auracast_init_flag) {
        return -EPERM;
    }

    if (auracast_sink_sync_timeout_hdl != 0) {
        sys_timeout_del(auracast_sink_sync_timeout_hdl);
        auracast_sink_sync_timeout_hdl = 0;
    }

    log_info("auracast_sink_close");

    app_auracast_mutex_pend(&mutex, __LINE__);

    if (app_auracast.status == APP_AURACAST_STATUS_SYNC) {
        auracast_sink_big_sync_terminate();
    }
    auracast_sink_scan_stop();
    os_time_dly(10);
    auracast_sink_uninit();
    app_auracast.status = status;
    auracast_sink_media_close();

    app_auracast.bis_num = 0;
    app_auracast.role = 0;
    app_auracast.big_hdl = 0;

    for (u8 i = 0; i < MAX_BIS_NUMS; i++) {
        memset(&app_auracast.bis_hdl_info[i], 0, sizeof(struct app_auracast_info_t));
    }

    app_auracast_mutex_post(&mutex, __LINE__);

    auracast_switch_onoff = 0;

    return 0;
}

static void auracast_source_app_send_callback(uint8_t *buff, uint16_t length)
{
#if 0
    int rlen = 0;
    u32 timestamp;
    auracast_event_send_t *send_packet = (auracast_event_send_t *)buff;
    u32 sdu_interval_us = auracast_code_list[AURACAST_BIS_SAMPLING_RATE][AURACAST_BIS_VARIANT].frame_len;
    timestamp = (auracast_source_read_iso_tx_sync(send_packet->bis_index) \
                 + auracast_source_get_sync_delay()) & 0xfffffff;
    timestamp += ((send_packet->bis_sub_event_counter - 1) * sdu_interval_us);
    /* printf("0x%x %d %d\n", send_packet->bis_index, send_packet->bis_sub_event_counter, timestamp); */
    if (app_auracast.recorder) {
        rlen = le_audio_stream_tx_data_handler(app_auracast.recorder, send_packet->buffer, length, timestamp, TCFG_LE_AUDIO_PLAY_LATENCY);
        if (!rlen) {
            putchar('^');
        }
    }
    if (!rlen) {
        memset(send_packet->buffer, 0, length);
    }
#endif
}

int auracast_source_user_can_send_now_callback(uint8_t big_hdl)
{
    u8 bis_index;
    u8 bis_sub_event_counter;
    int rlen = 0;
    u16 tx_offset = 0;
    u32 timestamp = (auracast_source_read_iso_tx_sync(0) \
                     + auracast_source_get_sync_delay()) & 0xfffffff;
    if (app_auracast.recorder) {
        rlen = le_audio_stream_tx_data_handler(app_auracast.recorder, tx_temp_buf, tx_temp_buf_len, timestamp, TCFG_LE_AUDIO_PLAY_LATENCY);
        if (!rlen) {
            putchar('^');
        }
    }
    if (!rlen) {
        memset(tx_temp_buf, 0, tx_temp_buf_len);
    }

    for (bis_sub_event_counter = 0; bis_sub_event_counter < AURACAST_ISO_BN; bis_sub_event_counter++) {
        for (bis_index = 0; bis_index < AURACAST_SOURCE_BIS_NUMS; bis_index++) {
            auracast_source_user_send_iso_packet(bis_index, bis_sub_event_counter, tx_temp_buf + tx_offset, get_auracast_sdu_size());
            tx_offset += get_auracast_sdu_size();
        }
    }
    return 1;// 就是用户使用接口自己发iso数据
    /* return 0; */
}

static void auracast_source_create(uint8_t *packet, uint16_t length)
{
    if (!app_auracast_init_flag) {
        return;
    }

    app_auracast_mutex_pend(&mutex, __LINE__);
    if (app_auracast.status == APP_AURACAST_STATUS_STOP || app_auracast.status == APP_AURACAST_STATUS_SUSPEND) {
        app_auracast_mutex_post(&mutex, __LINE__);
        return;
    }
    app_auracast.role = APP_AURACAST_AS_SOURCE;
    app_auracast.bis_num = AURACAST_SOURCE_BIS_NUMS;

    auracast_source_media_open();

    for (u8 i = 0; i < app_auracast.bis_num; i++) {
        app_auracast.bis_hdl_info[i].init_ok = 1;
    }

    app_auracast_mutex_post(&mutex, __LINE__);
}

static void auracast_source_app_event_callback(uint16_t event, uint8_t *packet, uint16_t length)
{
    switch (event) {
    case AURACAST_SOURCE_BIG_CREATED:
        log_info("AURACAST_SOURCE_BIG_CREATED");
        auracast_source_create(packet, length);
        break;
    case AURACAST_SOURCE_BIG_TERMINATED:
        log_info("AURACAST_SOURCE_BIG_TERMINATED");
        break;
    case AURACAST_SOURCE_SEND_CALLBACK:
        auracast_source_app_send_callback(packet, length);
        break;
    default:
        log_info("auracast source unknow event %x", event);
        break;
    }
}

#if (THIRD_PARTY_PROTOCOLS_SEL & MULTI_BOX_ADV_EN)
static void multi_box_bis_role_change_timer_callback(void *p)
{
    app_auracast_mutex_pend(&mutex, __LINE__);
    multi_box_bis_role_change_timer = 0;
    multi_box_bis_role_change(MULTI_BOX_ROLE_MASTER);
    app_auracast_mutex_post(&mutex, __LINE__);
}
#endif

/* --------------------------------------------------------------------------*/
/**
 * @brief 开启广播
 *
 * @return >=0:success
 */
/* ----------------------------------------------------------------------------*/
int app_auracast_source_open(void)
{
    if (!app_auracast_init_flag) {
        return -EPERM;
    }

    if (app_auracast.status != APP_AURACAST_STATUS_STOP && app_auracast.status != APP_AURACAST_STATUS_SUSPEND) {
        return -EPERM;
    }

    app_mode_t mode = get_current_app_mode();
    if (mode && (mode == APP_MODE_BT) &&
        (bt_get_call_status() != BT_CALL_HANGUP)) {
        return -EPERM;
    }

    auracast_switch_onoff = 1;

    log_info("auracast_source_open");

    app_auracast_mutex_pend(&mutex, __LINE__);

#if (THIRD_PARTY_PROTOCOLS_SEL & MULTI_BOX_ADV_EN)
    if (current_app_in_mode(APP_MODE_PC)) {
        if (multi_box_bis_role_change_timer) {
            sys_timeout_del(multi_box_bis_role_change_timer);
        }
        multi_box_bis_role_change_timer = sys_timeout_add(NULL, multi_box_bis_role_change_timer_callback, 2000);
    } else {
        multi_box_bis_role_change(MULTI_BOX_ROLE_MASTER);
    }
#endif

    /* strcpy(user_config.broadcast_name, get_le_audio_pair_name()); */

    if (tx_temp_buf) {
        free(tx_temp_buf);
        tx_temp_buf = NULL;
    }

    tx_temp_buf_len = AURACAST_SOURCE_BIS_NUMS * AURACAST_ISO_BN * get_auracast_sdu_size();
    log_info("tx_temp_buf_len:%d", tx_temp_buf_len);
    tx_temp_buf = zalloc(tx_temp_buf_len);
    if (!tx_temp_buf) {
        app_auracast_mutex_post(&mutex, __LINE__);
        return -1;
    }

    auracast_source_init(AURACAST_SOURCE_API_VERSION);
    auracast_source_config((auracast_user_config_t *)&user_config);
    auracast_source_advanced_config((auracast_advanced_config_t *)&user_advanced_config);
    auracast_source_event_callback_register(auracast_source_app_event_callback);
    auracast_source_start();
#if (THIRD_PARTY_PROTOCOLS_SEL & MULTI_BOX_ADV_EN)
    multi_box_bis_change_volume_notify();
#endif

    app_auracast.status = APP_AURACAST_STATUS_BROADCAST;

    app_auracast_mutex_post(&mutex, __LINE__);

    return 0;
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
int app_auracast_source_close(u8 status)
{
    if (app_auracast.status == APP_AURACAST_STATUS_STOP || app_auracast.status == APP_AURACAST_STATUS_SUSPEND) {
        return -EPERM;
    }


    log_info("auracast_source_close");

    app_auracast_mutex_pend(&mutex, __LINE__);

    app_auracast.status = status;

    auracast_source_stop();
    os_time_dly(10);
    auracast_source_uninit();
    auracast_source_media_close();

    app_auracast.bis_num = 0;
    app_auracast.role = 0;
    app_auracast.big_hdl = 0;

    for (u8 i = 0; i < MAX_BIS_NUMS; i++) {
        memset(&app_auracast.bis_hdl_info[i], 0, sizeof(struct app_auracast_info_t));
    }

    if (tx_temp_buf) {
        free(tx_temp_buf);
        tx_temp_buf = 0;
    }

    app_auracast_mutex_post(&mutex, __LINE__);

    auracast_switch_onoff = 0;

    return 0;
}

/* --------------------------------------------------------------------------*/
/**
 * @brief 广播开关切换
 *
 * @return 0：操作成功
 */
/* ----------------------------------------------------------------------------*/
int app_auracast_switch(void)
{
    u8 find = 0;

    app_mode_t mode = get_current_app_mode();
    if (mode && (mode == APP_MODE_BT) &&
        (bt_get_call_status() != BT_CALL_HANGUP)) {
        return -EPERM;
    }

    if (app_auracast.status == APP_AURACAST_STATUS_STOP || app_auracast.status == APP_AURACAST_STATUS_SUSPEND) {
        app_auracast_init();

        app_auracast_open();

        play_tone_file_alone_callback(get_tone_files()->le_broadcast_open,
                                      (void *)TONE_INDEX_AURACAST_OPEN,
                                      auracast_tone_play_end_callback);
    } else {
        if (app_auracast.role == APP_AURACAST_AS_SOURCE) {
            app_auracast_source_close(APP_AURACAST_STATUS_STOP);
        } else if (app_auracast.role == APP_AURACAST_AS_SINK) {
            app_auracast_sink_close(APP_AURACAST_STATUS_STOP);
        }

        play_tone_file_alone_callback(get_tone_files()->le_broadcast_close,
                                      (void *)TONE_INDEX_AURACAST_CLOSE,
                                      auracast_tone_play_end_callback);
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
int update_app_auracast_deal_scene(int scene)
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
int app_auracast_deal(int scene)
{
    u32 rets_addr;
    __asm__ volatile("%0 = rets ;" : "=r"(rets_addr));

    int ret = 0;
    static u8 phone_start_cnt = 0;
    app_mode_t mode;

    if ((cur_deal_scene == scene) &&
        (scene != LE_AUDIO_PHONE_START) &&
        (scene != LE_AUDIO_PHONE_STOP)) {
        log_error("app_auracast_deal,scene not be modified:%d", scene);
        return -EPERM;
    }

    log_info("app_auracast_deal %d, rets_addr:0x%x", scene, rets_addr);

    cur_deal_scene = scene;

    switch (scene) {
    case LE_AUDIO_APP_MODE_ENTER:
        log_info("LE_AUDIO_APP_MODE_ENTER");
        //进入当前模式
        auracast_app_mode_exit = 0;
    case LE_AUDIO_APP_OPEN:
        config_auracast_as_master = 1;
        mode = get_current_app_mode();
        if (mode) {
            le_audio_ops_register(mode);
        }
        if (is_need_resume_auracast()) {
            if (mode == APP_MODE_BT || mode == APP_MODE_PC) {
                //处于其他模式时，手机后台播歌使设备跳回蓝牙模式，此时获取蓝牙底层a2dp状态为正在播放，
                //但BT_STATUS_A2DP_MEDIA_START事件还没到来，无法获取设备信息，导致直接开关tx_le_audio_open使用了空设备地址引起死机
                app_auracast_sink_open();
            } else {
                app_auracast_resume();
            }
            ret = 1;
        }
        config_auracast_as_master = 0;
        break;
    case LE_AUDIO_APP_MODE_EXIT:
        log_info("auracast_app_mode_exit");
        //退出当前模式
        auracast_app_mode_exit = 1;
    case LE_AUDIO_APP_CLOSE:
        phone_start_cnt = 0;
        app_auracast_suspend();
        le_audio_ops_unregister();
        break;
    case LE_AUDIO_MUSIC_START:
    case LE_AUDIO_A2DP_START:
        log_info("LE_AUDIO_MUSIC_START");
        //启动a2dp播放
        if (auracast_app_mode_exit) {
            //防止蓝牙非后台情况下退出蓝牙模式时，会先出现auracast_app_mode_exit，再出现LE_AUDIO_A2DP_START，导致广播状态发生改变
            break;
        }
#if (TCFG_LEA_BIG_FIX_ROLE == 0)
        if (app_auracast.status != APP_AURACAST_STATUS_STOP && app_auracast.status != APP_AURACAST_STATUS_SUSPEND) {
            //(1)当处于广播开启并且作为接收设备时，挂起广播，播放当前手机音乐；
            //(2)当前广播处于挂起状态时，恢复广播并作为发送设备。
            if (app_auracast.role == APP_AURACAST_AS_SINK) {
                app_auracast_suspend();
            } else if (app_auracast.role == APP_AURACAST_AS_SOURCE) {
                ret = 1;
            }
        }
#else
        if (app_auracast.role == APP_AURACAST_AS_SOURCE) {
            //固定收发角色重启广播数据流
            auracast_source_media_reset();
            ret = 1;
            break;
        }
#endif

        if (is_need_resume_auracast()) {
            /* app_auracast_resume(); */
            app_auracast_source_open();
            ret = 1;
        }
        break;

    case LE_AUDIO_MUSIC_STOP:
    case LE_AUDIO_A2DP_STOP:
        log_info("LE_AUDIO_MUSIC_STOP");
        //停止a2dp播放
        if (auracast_app_mode_exit) {
            //防止蓝牙非后台情况下退出蓝牙模式时，会先出现auracast_app_mode_exit，再出现LE_AUDIO_A2DP_STOP，导致广播状态发生改变
            break;
        }
#if (TCFG_LEA_BIG_FIX_ROLE == 0)
        //当前处于广播挂起状态时，停止手机播放，恢复广播并接收其他设备的音频数据
        app_auracast_suspend();
#else
        if (app_auracast.role == APP_AURACAST_AS_SOURCE) {
            //固定收发角色暂停播放时关闭广播数据流
            auracast_source_media_close();
            ret = 1;
            break;
        }
#endif
        if (is_need_resume_auracast()) {
            /* app_auracast_resume(); */
            app_auracast_sink_open();
            ret = 1;
        }
        break;
    case LE_AUDIO_PHONE_START:
        log_info("LE_AUDIO_PHONE_START");
        //通话时，挂起广播
        phone_start_cnt++;
        log_info("phone_start_cnt: %d", phone_start_cnt);
        app_auracast_suspend();
        break;
    case LE_AUDIO_PHONE_STOP:
        log_info("LE_AUDIO_PHONE_STOP");
        //通话结束恢复广播
        phone_start_cnt--;
        log_info("phone_start_cnt: %d", phone_start_cnt);
        if (phone_start_cnt) {
            break;
        }
        //当前处于蓝牙模式并且挂起前广播，恢复广播并作为接收设备
        if (is_need_resume_auracast()) {
            /* app_auracast_resume(); */
            app_auracast_sink_open();
        }
        break;
    case LE_AUDIO_EDR_DISCONN:
        log_info("LE_AUDIO_EDR_DISCONN");
        if (auracast_app_mode_exit) {
            //防止蓝牙非后台情况下退出蓝牙模式时，会先出现auracast_app_mode_exit，再出现LE_AUDIO_EDR_DISCONN，导致广播状态发生改变
            break;
        }
        //当经典蓝牙断开后，作为发送端的广播设备挂起广播
        if (app_auracast.role == APP_AURACAST_AS_SOURCE) {
            app_auracast_suspend();
        }
        if (is_need_resume_auracast()) {
            /* app_auracast_resume(); */
            app_auracast_sink_open();
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
 * @brief 非蓝牙后台情况下，在其他音源模式开启BIG，前提要先开蓝牙协议栈
 */
/* ----------------------------------------------------------------------------*/
void app_auracast_open_in_other_mode(void)
{
    app_auracast_init();

    if (is_need_resume_auracast()) {
        app_mode_t mode = get_current_app_mode();
        if (mode) {
            le_audio_ops_register(mode);
        }
    }
}

/* --------------------------------------------------------------------------*/
/**
 * @brief 非蓝牙后台情况下，在其他音源模式关闭BIG
 */
/* ----------------------------------------------------------------------------*/
void app_auracast_close_in_other_mode(void)
{
    app_auracast_suspend();
}

static int auracast_source_media_open(void)
{
    log_info("auracast_source_media_open");

    le_audio_switch_ops = get_broadcast_audio_sw_ops();
    //关闭本地音频播放
    if (le_audio_switch_ops && le_audio_switch_ops->local_audio_close) {
        le_audio_switch_ops->local_audio_close();
    }

    u16 frame_dms;
    if (auracast_code_list[AURACAST_BIS_SAMPLING_RATE][AURACAST_BIS_VARIANT].frame_len >= 10000) {
        frame_dms = 100;
    } else {
        frame_dms = 75;
    }

    struct le_audio_stream_params params = {0};
    params.fmt.nch = AURACAST_SOURCE_BIS_NUMS;
    params.fmt.coding_type = AUDIO_CODING_LC3;
    params.fmt.frame_dms = frame_dms;
    params.fmt.bit_rate = params.fmt.nch * auracast_code_list[AURACAST_BIS_SAMPLING_RATE][AURACAST_BIS_VARIANT].bit_rate;
    params.fmt.sdu_period = AURACAST_ISO_BN * auracast_code_list[AURACAST_BIS_SAMPLING_RATE][AURACAST_BIS_VARIANT].frame_len;
    params.fmt.isoIntervalUs = AURACAST_ISO_BN * auracast_code_list[AURACAST_BIS_SAMPLING_RATE][AURACAST_BIS_VARIANT].frame_len;
    params.fmt.sample_rate = auracast_code_list[AURACAST_BIS_SAMPLING_RATE][AURACAST_BIS_VARIANT].sample_rate;
    params.fmt.dec_ch_mode = TCFG_LEA_TX_DEC_OUTPUT_CHANNEL;
    params.latency = TCFG_LE_AUDIO_PLAY_LATENCY;
    params.conn = auracast_source_get_bis_hdl(0);

    //打开广播音频播放
    if (le_audio_switch_ops && le_audio_switch_ops->tx_le_audio_open) {
        log_info("auracast_source_tx_le_audio_open");
        app_auracast.recorder = le_audio_switch_ops->tx_le_audio_open(&params);
    }

    return 0;
}

static int auracast_source_media_close(void)
{
    void *recorder = 0;
    u8 player_status = 0;

    //获取当前播放器状态
    if (le_audio_switch_ops && le_audio_switch_ops->play_status) {
        player_status = le_audio_switch_ops->play_status();
    }

    if (app_auracast.recorder) {
        recorder = app_auracast.recorder;
        app_auracast.recorder = NULL;
    }

    if (recorder) {
        if (le_audio_switch_ops && le_audio_switch_ops->tx_le_audio_close) {
            le_audio_switch_ops->tx_le_audio_close(recorder);
            recorder = NULL;
            log_info("auracast_source_media_close");
        }
    }

    //当前处于播放状态，关闭le audio音频流后恢复本地播放
    if (player_status == LOCAL_AUDIO_PLAYER_STATUS_PLAY) {
        if (le_audio_switch_ops && le_audio_switch_ops->local_audio_open) {
            le_audio_switch_ops->local_audio_open();
        }
    }

    return 0;
}

static int auracast_source_media_reset(void)
{
    auracast_source_media_close();
    auracast_source_media_open();
    return 0;
}

static int auracast_sink_media_open(uint16_t bis_hdl, uint8_t *packet, uint16_t length)
{
    log_info("auracast_sink_media_open");

    auracast_sink_source_info_t *config = (auracast_sink_source_info_t *)packet;

    le_audio_switch_ops = get_broadcast_audio_sw_ops();
    //关闭本地音频播放
    if (le_audio_switch_ops && le_audio_switch_ops->local_audio_close) {
        le_audio_switch_ops->local_audio_close();
    }

    struct le_audio_stream_params params = {0};
    //默认解码所有bis链路的数据
    params.fmt.nch = app_auracast.bis_num;
    //解码器最多支持双声道数据解码,超过2条声道的情况,只能选其中一条声道进行解码
    if (params.fmt.nch > 2) {
        params.fmt.nch = 1;
    }
    params.fmt.coding_type = AUDIO_CODING_LC3;
    params.fmt.dec_ch_mode = TCFG_LEA_RX_DEC_OUTPUT_CHANNEL;

    log_info("nch:%d, coding_type:0x%x, dec_ch_mode:%d",
             params.fmt.nch, params.fmt.coding_type, params.fmt.dec_ch_mode);

    if (config->frame_duration == FRAME_DURATION_7_5) {
        params.fmt.frame_dms = 75;
    } else if (config->frame_duration == FRAME_DURATION_10) {
        params.fmt.frame_dms = 100;
    } else {
        ASSERT(0, "frame_dms err:%d", config->frame_duration);
    }
    params.fmt.sdu_period = config->sdu_period;
    params.fmt.isoIntervalUs = config->sdu_period;
    params.fmt.sample_rate = config->sample_rate;
    params.fmt.bit_rate = params.fmt.nch * config->bit_rate;
    params.conn = bis_hdl;

    log_info("frame_dms:%d, sdu_period:%d, sample_rate:%d, bit_rate:%d",
             params.fmt.frame_dms, config->sdu_period, config->sample_rate, config->bit_rate);

    //打开广播音频播放
    ASSERT(le_audio_switch_ops, "le_audio_sw_ops == NULL");

    if (le_audio_switch_ops && le_audio_switch_ops->rx_le_audio_open) {
        log_info("auracast_sink_rx_le_audio_open");
        le_audio_switch_ops->rx_le_audio_open(&app_auracast.rx_player, &params);
    }

    return 0;
}

static int auracast_sink_media_close(void)
{
    u8 player_status = 0;
    struct le_audio_player_hdl player;
    player.le_audio = 0;
    player.rx_stream = 0;

    //获取当前播放器状态
    if (le_audio_switch_ops && le_audio_switch_ops->play_status) {
        player_status = le_audio_switch_ops->play_status();
    }

    if (app_auracast.rx_player.le_audio) {
        player.le_audio = app_auracast.rx_player.le_audio;
        app_auracast.rx_player.le_audio = NULL;
    }

    if (app_auracast.rx_player.rx_stream) {
        player.rx_stream = app_auracast.rx_player.rx_stream;
        app_auracast.rx_player.rx_stream = NULL;
    }

    if (player.le_audio && player.rx_stream) {
        if (le_audio_switch_ops && le_audio_switch_ops->rx_le_audio_close) {
            le_audio_switch_ops->rx_le_audio_close(&player);
            player.le_audio = 0;
            player.rx_stream = 0;
            log_info("auracast_sink_media_close");
        }
    }

    //当前处于播放状态，关闭le audio音频流后恢复本地播放
    if (player_status == LOCAL_AUDIO_PLAYER_STATUS_PLAY) {
        if (le_audio_switch_ops && le_audio_switch_ops->local_audio_open) {
            le_audio_switch_ops->local_audio_open();
        }
    }

    return 0;
}

static bool are_all_zeros(uint8_t *array, int length)
{
    for (int i = 0; i < length; i++) {
        if (array[i] != 0) {
            return false;
        }
    }
    return true;
}

static void auracast_iso_rx_callback(uint8_t *packet, uint16_t size)
{
    //putchar('o');
    u8 i = 0;
    static u8 j = 0;
    s8 index = -1;
    bool plc_flag = 0;
    hci_iso_hdr_t hdr = {0};

    ll_iso_unpack_hdr(packet, &hdr);

    if (size) {
        if (are_all_zeros(hdr.iso_sdu, hdr.iso_sdu_length)) {
            /* log_error("SDU empty"); */
            putchar('m');
            plc_flag = 1;
        }
    }

    if ((hdr.pb_flag == 0b10) && (hdr.iso_sdu_length == 0)) {
        if (hdr.packet_status_flag == 0b00) {
            /* log_error("SDU empty"); */
            putchar('m');
            plc_flag = 1;
        } else {
            /* log_error("SDU lost"); */
            putchar('s');
            plc_flag = 1;
        }
    }
    if (((hdr.pb_flag == 0b10) || (hdr.pb_flag == 0b00)) && (hdr.packet_status_flag == 0b01)) {
        //log_error("SDU invalid, len=%d", hdr.iso_sdu_length);
        putchar('p');
        plc_flag = 1;
    }

    for (i = 0; i < app_auracast.bis_num; i++) {
        if (app_auracast.bis_hdl_info[i].bis_hdl == hdr.handle) {
            if (!app_auracast.rx_player.rx_stream || !app_auracast.bis_hdl_info[i].init_ok) {
                return;
            }
            index = i;
            break;
        }
    }

    if (index == -1) {
        return;
    }

    j++;
    if (j >= g_sink_bn) {
        j = 0;
    }

    /* printf("[%d][%x]\n",hdr.handle,(u32)app_auracast.rx_player.rx_stream); */
    if (plc_flag || multi_bis_plc_flag[j]) {
        if (multi_bis_rx_buf[j]) {
            multi_bis_plc_flag[j] = 1;
            for (i = 0; i < app_auracast.bis_num; i++) {
                if (app_auracast.bis_hdl_info[i].bis_hdl == hdr.handle) {
                    break;
                }
            }
            if (i == (app_auracast.bis_num - 1)) {
                memcpy(multi_bis_rx_buf[j], errpacket, 2);
                le_audio_stream_rx_frame(app_auracast.rx_player.rx_stream, (void *)multi_bis_rx_buf[j], 2,
                                         hdr.time_stamp + TCFG_LE_AUDIO_PLAY_LATENCY);
                multi_bis_data_offect[j] = 0;
                multi_bis_plc_flag[j] = 0;
            }
        } else {
            le_audio_stream_rx_frame(app_auracast.rx_player.rx_stream, (void *)errpacket, 2, hdr.time_stamp + TCFG_LE_AUDIO_PLAY_LATENCY);
        }
    } else {
        /* printf("%d 0x%x", j, hdr.handle); */
        if (multi_bis_rx_buf[j]) {
            memcpy(multi_bis_rx_buf[j] + multi_bis_data_offect[j], hdr.iso_sdu, hdr.iso_sdu_length);
            multi_bis_data_offect[j] += hdr.iso_sdu_length;
            ASSERT(multi_bis_data_offect[j] <= multi_bis_rx_temp_buf_len);
            if (multi_bis_data_offect[j] >= multi_bis_rx_temp_buf_len) {
                le_audio_stream_rx_frame(app_auracast.rx_player.rx_stream, (void *)multi_bis_rx_buf[j], multi_bis_rx_temp_buf_len, hdr.time_stamp + TCFG_LE_AUDIO_PLAY_LATENCY);
                multi_bis_data_offect[j] -= multi_bis_rx_temp_buf_len;
            }
        } else {
            le_audio_stream_rx_frame(app_auracast.rx_player.rx_stream, (void *)hdr.iso_sdu, hdr.iso_sdu_length, hdr.time_stamp + TCFG_LE_AUDIO_PLAY_LATENCY);
        }
    }
}

int app_auracast_sink_start_record(void)
{
    if (!app_auracast_init_flag) {
        return -EPERM;
    }

    if (app_auracast.role != APP_AURACAST_AS_SINK) {
        return -EPERM;
    }

    app_mode_t mode = get_current_app_mode();
    if (mode && (mode == APP_MODE_BT) &&
        (bt_get_call_status() != BT_CALL_HANGUP)) {
        return -EPERM;
    }

    auracast_sink_start_record = 1;

#if AURACAST_SINK_RECORDED_WIRTE_VM
    for (int i = 0; i < AURACAST_SINK_MAX_RECORD_NUM; i++) {
        syscfg_read(VM_WIRELESS_RECORDED_ADDR0 + i, auracast_sink_record_connect_mac_addr[i], 6);
    }
#endif

    u8 temp[6] = {0};
    if (memcmp(auracast_sink_curr_connect_mac_addr, temp, 6)) {
        auracast_sink_record_mac_addr(auracast_sink_curr_connect_mac_addr);
    }

    return 0;
}

int app_auracast_sink_stop_record(void)
{
    if (!app_auracast_init_flag) {
        return -EPERM;
    }

    if (app_auracast.role != APP_AURACAST_AS_SINK) {
        return -EPERM;
    }

    app_mode_t mode = get_current_app_mode();
    if (mode && (mode == APP_MODE_BT) &&
        (bt_get_call_status() != BT_CALL_HANGUP)) {
        return -EPERM;
    }

    app_auracast_mutex_pend(&mutex, __LINE__);

    if (auracast_sink_start_record) {
        auracast_sink_start_record = 0;
    }

    if (auarcast_sink_mac_addr_filter) {
        auarcast_sink_mac_addr_filter = 0;
    }

    memset(auracast_sink_last_connect_mac_addr, 0, 6);

    app_auracast_mutex_post(&mutex, __LINE__);

    return 0;
}

static int auracast_sink_get_mac_addr_is_recorded(u8 *mac_addr)
{
    int ret = 0;

    app_auracast_mutex_pend(&mutex, __LINE__);

    for (int i = 0; i < AURACAST_SINK_MAX_RECORD_NUM; i++) {
        if (!(memcmp(auracast_sink_record_connect_mac_addr[i], mac_addr, 6))) {
            ret = 1;
        }
    }

    app_auracast_mutex_post(&mutex, __LINE__);

    return ret;
}

static int auracast_sink_get_recorded_addr_num(void)
{
    int num = 0;
    u8 temp[6] = {0};

    app_auracast_mutex_pend(&mutex, __LINE__);

    for (int i = 0; i < AURACAST_SINK_MAX_RECORD_NUM; i++) {
        if ((memcmp(auracast_sink_record_connect_mac_addr[i], temp, 6))) {
            num++;
        }
    }

    app_auracast_mutex_post(&mutex, __LINE__);

    return num;
}

int app_auracast_sink_switch_source_device(u8 switch_mode) //0:切换设备后不过滤设备；1：切换设备后过滤处理只连接记录的设备
{
    if (!app_auracast_init_flag) {
        return -EPERM;
    }

    if (app_auracast.role != APP_AURACAST_AS_SINK) {
        return -EPERM;
    }

    app_mode_t mode = get_current_app_mode();
    if (mode && (mode == APP_MODE_BT) &&
        (bt_get_call_status() != BT_CALL_HANGUP)) {
        return -EPERM;
    }

    u8 temp[6] = {0};
    u8 recorded_num = 0;

    if (!auracast_sink_start_record) {
        app_auracast_sink_start_record();
    }

    recorded_num = auracast_sink_get_recorded_addr_num();
    if (!recorded_num) {
        return -EPERM;
    }

    app_auracast_mutex_pend(&mutex, __LINE__);

    if (recorded_num >= 2 && switch_mode) {
        auarcast_sink_mac_addr_filter = switch_mode;
    } else if (switch_mode) {
        log_error("[error]The current number of records is insufficient");
        auarcast_sink_mac_addr_filter = 0;
    } else {
        auarcast_sink_mac_addr_filter = 0;
    }

    memcpy(auracast_sink_last_connect_mac_addr, auracast_sink_curr_connect_mac_addr, 6);

    app_auracast_mutex_post(&mutex, __LINE__);

    app_auracast_sink_close(APP_AURACAST_STATUS_STOP);
    app_auracast_sink_open();

    return 0;
}

u8 check_local_not_accept_sniff_by_remote(void)
{
    /* printf("le_auracast_state=%d\n",le_auracast_state ); */
    if (le_audio_player_is_playing() || le_auracast_state == BROADCAST_STATUS_SCAN_START) {
        return TRUE;
    }

    return FALSE;
}

static int auracast_sink_record_mac_addr(u8 *mac_addr)
{
    int ret = 0;
    u8 temp[6] = {0};
    static u8 discard_cnt = 0;
    int i = 0;

    if (!mac_addr) {
        return -EPERM;
    }

    if (!memcmp(mac_addr, temp, 6)) {
        return -EPERM;
    }

    app_auracast_mutex_pend(&mutex, __LINE__);

    for (i = 0; i < AURACAST_SINK_MAX_RECORD_NUM; i++) {
        if (!memcmp(mac_addr, auracast_sink_record_connect_mac_addr[i], 6)) {
            ret = 1;
            break;
        }
        if ((memcmp(auracast_sink_record_connect_mac_addr[i], temp, 6))) {
            memcpy(auracast_sink_record_connect_mac_addr[i], mac_addr, 6);
            ret = 2;
            break;
        }
    }

    if (i == AURACAST_SINK_MAX_RECORD_NUM) {
        log_info("reached maxixmum number of records, discard [%d] addr:", discard_cnt);
        put_buf(auracast_sink_record_connect_mac_addr[discard_cnt], 6);
        memcpy(auracast_sink_record_connect_mac_addr[discard_cnt], mac_addr, 6);
        i = discard_cnt;
        discard_cnt++;
        discard_cnt = (discard_cnt >= 3) ? 0 : discard_cnt;
    }

#if AURACAST_SINK_RECORDED_WIRTE_VM
    syscfg_write(VM_WIRELESS_RECORDED_ADDR0 + i, auracast_sink_record_connect_mac_addr[i], 6);
#endif

    app_auracast_mutex_post(&mutex, __LINE__);

    return ret;
}

void app_auracast_sink_discard_record(void)
{
    app_auracast_mutex_pend(&mutex, __LINE__);

    for (int i = 0; i < AURACAST_SINK_MAX_RECORD_NUM; i++) {
        memset(auracast_sink_record_connect_mac_addr[i], 0, 6);
#if AURACAST_SINK_RECORDED_WIRTE_VM
        syscfg_write(VM_WIRELESS_RECORDED_ADDR0 + i, auracast_sink_record_connect_mac_addr[i], 6);
#endif
    }

    auarcast_sink_mac_addr_filter = 0;

    memset(auracast_sink_last_connect_mac_addr, 0, 6);

    app_auracast_mutex_post(&mutex, __LINE__);
}

static void auracast_sink_connect_filter_timeout(void *priv)
{
    memset(auracast_sink_last_connect_mac_addr, 0, 6);

    auarcast_sink_mac_addr_filter = 0;
}

u8 get_auracast_switch_onoff(void)
{
    return auracast_switch_onoff;
}

#endif

