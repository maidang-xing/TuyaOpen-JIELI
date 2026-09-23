#ifndef _APP_LE_AURACAST_H_
#define _APP_LE_AURACAST_H_

/*  Include header */
#include "generic/typedef.h"
#include "wireless_trans.h"
#include "btstack/le/auracast_sink_api.h"
#include "app_config.h"

#ifdef __cplusplus
extern "C" {
#endif

#define AURACAST_BIS_SAMPLING_RATE 5 // sampling_frequency
#define AURACAST_BIS_VARIANT 1 // variant
#define AURACAST_BIS_RTN 3 // 重发次数
#define AURACAST_ISO_BN 2 // 发包间隔
#define AURACAST_SOURCE_BIS_NUMS TCFG_LE_AUDIO_CODEC_CHANNEL // source广播链路数
#define AURACAST_SINK_BIS_NUMS TCFG_LE_AUDIO_CODEC_CHANNEL // sink最多接收链路数


/**************************************************************************************************
  Data Types
**************************************************************************************************/
enum {
    APP_AURACAST_STATUS_STOP,
    APP_AURACAST_STATUS_SUSPEND,
    APP_AURACAST_STATUS_BROADCAST,
    APP_AURACAST_STATUS_SCAN,
    APP_AURACAST_STATUS_SYNC,
};

enum {
    APP_AURACAST_AS_SOURCE = 1,
    APP_AURACAST_AS_SINK,
};

u8 get_auracast_role(void);
u8 get_auracast_status(void);
u8 get_auracast_app_mode_exit_flag(void);
u8 get_auracast_switch_onoff(void);
int app_auracast_sink_open(void);
int app_auracast_sink_close(u8 status);
int app_auracast_source_open(void);
int app_auracast_source_close(u8 status);
int app_auracast_switch(void);
int update_app_auracast_deal_scene(int scene);
int app_auracast_deal(int scene);
void app_auracast_open_in_other_mode(void);
void app_auracast_close_in_other_mode(void);
int auracast_source_media_reset(void);
void app_auracast_init(void);
void app_auracast_uninit(void);
int app_auracast_open(void);
int app_auracast_sink_start_record(void);
int app_auracast_sink_stop_record(void);
int app_auracast_sink_switch_source_device(u8 switch_mode); //0:切换设备后不过滤设备；1：切换设备后过滤处理只连接记录的设备
void app_auracast_sink_discard_record(void);


typedef enum {
    BROADCAST_STATUS_DEFAULT = 0,
    BROADCAST_STATUS_SCAN_START,
    BROADCAST_STATUS_SCAN_STOP,
    BROADCAST_STATUS_START,
    BROADCAST_STATUS_STOP,
} BROADCAST_STATUS;

/**
 * @brief 关闭auracast功能（音频、扫描）
 */
void le_auracast_stop(void);

/**
 * @brief 手机选中广播设备开始播歌
 *
 * @param param 要监听的广播设备
 */
int app_auracast_sink_big_sync_create(auracast_sink_source_info_t *param);

/**
 * @brief 关闭所有正在监听播歌的广播设备
 */
int app_auracast_sink_big_sync_terminate(void);

/**
 * @brief 手机通知设备开始搜索auracast广播
 */
int app_auracast_sink_scan_start(void);

/**
 * @brief 手机通知设备关闭搜索auracast广播
 */
int app_auracast_sink_scan_stop(void);

#ifdef __cplusplus
};
#endif

#endif
