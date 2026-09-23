#include "btstack/avctp_user.h"
#include "classic/tws_api.h"
#include "app_tone.h"
#include "app_msg.h"
#include "event/bt_event.h"
#include "system/timer.h"
#include "tws_tone_player.h"
#include "bt_tws.h"
#include "app_config.h"

#if TCFG_APP_BT_EN

bool get_bt_connction_enable_status(void);

static int tone_btstack_event_handler(void *evt)
{
    struct bt_event *event = (struct bt_event *)evt;

    switch (event->event) {
    case BT_STATUS_FIRST_CONNECTED:
    case BT_STATUS_SECOND_CONNECTED:
        /*
         * 获取tws状态，如果正在播歌或打电话则返回1,不播连接成功提示音
         */
#if TCFG_USER_TWS_ENABLE
        if (tws_api_get_role() == TWS_ROLE_SLAVE) {
            break;
        }

        int state = tws_api_get_lmp_state(event->args);
        if (state & TWS_STA_ESCO_OPEN) {
            break;
        }
        tws_play_tone_file(get_tone_files()->bt_connect, 400);
#else
        play_tone_file(get_tone_files()->bt_connect);
#endif
        break;
    case BT_STATUS_FIRST_DISCONNECT:
    case BT_STATUS_SECOND_DISCONNECT:
        if (get_bt_connction_enable_status()) {
#if TCFG_USER_TWS_ENABLE
            if (tws_api_get_role() == TWS_ROLE_SLAVE) {
                break;
            }
            tws_play_tone_file(get_tone_files()->bt_disconnect, 400);
#else
            play_tone_file(get_tone_files()->bt_disconnect);

#endif
        }
        break;
    }

    return FALSE;
}

REGISTER_APP_EVENT_HANDLER(tone_btstack_event) = {
    .event      = SYS_BT_EVENT,
    .from       = BT_EVENT_FROM_CON,
    .handler    = tone_btstack_event_handler,
};


#if TCFG_USER_TWS_ENABLE

#define TWS_DLY_DISCONN_TIME            0//2000    //TWS超时断开，快速连接上不播提示音

static u8 g_tws_connected;
static u8 g_role_switch;
static u16 tws_dly_discon_time;

static void tws_disconn_dly_deal(void *priv)
{
    if (tws_dly_discon_time == 0) {
        return;
    }
    tws_dly_discon_time = 0;

    if (get_bt_connction_enable_status()) {
        tone_player_stop();
        play_tone_file(get_tone_files()->tws_disconnect);
    }
}

static int tone_tws_event_handler(void *evt)
{
    struct tws_event *event = (struct tws_event *)evt;

    switch (event->event) {
    case TWS_EVENT_CONNECTED:
        g_tws_connected = 1;

        if (tws_dly_discon_time) {
            sys_timeout_del(tws_dly_discon_time);
            tws_dly_discon_time = 0;
            break;
        }

        tone_player_stop();

        int role = event->args[0];
        if (role == TWS_ROLE_MASTER) {
            int state = tws_api_get_tws_state();
            if (state & (TWS_STA_SBC_OPEN | TWS_STA_ESCO_OPEN)) {
                break;
            }
#if TCFG_BT_TWS_CHANNEL_SELECT == CONFIG_TWS_MASTER_AS_LEFT
            if (tws_api_get_local_channel() == 'R') {
                g_role_switch = 1;
                bt_tws_role_switch();
                break;
            }
#endif
            tws_play_tone_file(get_tone_files()->tws_connect, 400);
        }
        break;
    case TWS_EVENT_CONNECTION_DETACH:
        if (!g_tws_connected) {
            break;
        }
        g_role_switch = 0;
        g_tws_connected = 0;

        int reason = event->args[2];
        if (reason == (TWS_DETACH_BY_REMOTE | TWS_DETACH_BY_POWEROFF)) {
            break;
        }

#if TWS_DLY_DISCONN_TIME
        if (reason & TWS_DETACH_BY_SUPER_TIMEOUT) {
            tws_dly_discon_time = sys_timeout_add(NULL, tws_disconn_dly_deal,
                                                  TWS_DLY_DISCONN_TIME);
            break;
        }
#endif
        if (get_bt_connction_enable_status()) {
            tone_player_stop();
            play_tone_file(get_tone_files()->tws_disconnect);
        }
        break;
    case TWS_EVENT_REMOVE_PAIRS:
        //play_tone_file(get_tone_files()->tws_disconnect);
        break;
    case TWS_EVENT_ROLE_SWITCH:
        if (g_role_switch) {
            tws_play_tone_file(get_tone_files()->tws_connect, 400);
        }
        break;
    }

    return 0;
}

REGISTER_APP_EVENT_HANDLER(tone_tws_event) = {
    .event      = SYS_BT_EVENT,
    .from       = BT_EVENT_FROM_TWS,
    .handler    = tone_tws_event_handler,
};

#endif

#endif
