#ifndef _APP_BT_TWS_H_
#define _APP_BT_TWS_H_

#include "classic/tws_api.h"
#include "classic/tws_event.h"

#define TWS_FUNC_ID_VOL_SYNC        TWS_FUNC_ID('V', 'O', 'L', 'S')
#define TWS_FUNC_ID_VBAT_SYNC       TWS_FUNC_ID('V', 'B', 'A', 'T')
#define TWS_FUNC_ID_CHARGE_SYNC     TWS_FUNC_ID('C', 'H', 'G', 'S')
#define TWS_FUNC_ID_BOX_SYNC        TWS_FUNC_ID('B', 'O', 'X', 'S')
#define TWS_FUNC_ID_AI_DMA_RAND     TWS_FUNC_ID('A', 'I', 'D', 'M')
#define TWS_FUNC_ID_AI_SPEECH_STOP  TWS_FUNC_ID('A', 'I', 'S', 'T')
#define TWS_FUNC_ID_APP_MODE  		TWS_FUNC_ID('M', 'O', 'D', 'E')
#define TWS_FUNC_ID_AI_SYNC			TWS_FUNC_ID('A', 'I', 'P', 'A')
#define TWS_FUNC_ID_EAR_DETECT_SYNC	TWS_FUNC_ID('E', 'D', 'E', 'T')
#define TWS_FUNC_ID_LL_SYNC_STATE	TWS_FUNC_ID('L', 'L', 'S', 'S')
#define TWS_FUNC_ID_TUYA_STATE      TWS_FUNC_ID('T', 'U', 'Y', 'A')

enum {
    TWS_SYNC_VOL = 0,
    TWS_SYNC_VBAT,
    TWS_SYNC_CHG,
    TWS_SYNC_CALL_VOL,
    TWS_SYNC_PBG_INFO,
    TWS_APP_DATA_SEND,
    TWS_AI_DMA_RAND,
    TWS_DATA_SEND,

    TWS_UPDATE_START,
    TWS_UPDATE_RESULT_EXCHANGE,
    TWS_UPDATE_RESULT_EXCHANGE_RES,
    TWS_UPDATE_OVER,
    TWS_UPDATE_OVER_CONFIRM,
    TWS_UPDATE_OVER_CONFIRM_REQ,
    TWS_UPDATE_OVER_CONFIRM_RES,
    TWS_UPDATE_VERIFY,

    TWS_AI_A2DP_DROP_FRAME_CTL,
};

const u8 *bt_get_mac_addr(void);

void bt_update_mac_addr(u8 *addr);

const char *bt_get_local_name(void);

bool bt_tws_is_paired(void);

bool get_bt_tws_connect_status(void);

void bt_tws_sync_volume(void);

bool get_tws_sibling_connect_state(void);

void tws_cancle_all_noconn(void);

void bt_tws_key_msg_sync(u8 action, u8 value);

void bt_tws_detach_and_remove_pairs(void);

int bt_tws_start_pair(void);

void tws_set_search_sbiling_state(u8 state);

u16 bt_tws_get_state(void);

u8 bt_tws_active(void);

void bt_tws_set_active(u8 status);

void send_page_device_addr_2_sibling(void);

void tws_dual_conn_state_handler(void);

bool get_bt_connction_enable_status(void);

void tws_dual_conn_close(void);

void tws_delete_pair_timer(void);

void bt_tws_role_switch(void);

#endif
