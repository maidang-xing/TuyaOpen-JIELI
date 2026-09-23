#include "event/net_event.h"
#include "event/key_event.h"
#include "net/config_network.h"
#include "net_app_cfg.h"
#include "app_msg.h"
#include "app_tone.h"
#include "tts_player.h"
#include "wifi/wifi_connect.h"
#include "app_config.h"
#if TCFG_SMART_VOICE_ENABLE
#include "asr/jl_kws.h"
#include "smart_voice/smart_voice.h"
#endif

#ifdef CONFIG_NET_ENABLE

#define LOG_TAG             "[NET_CFG]"
#define LOG_ERROR_ENABLE
#define LOG_DEBUG_ENABLE
#define LOG_INFO_ENABLE
#define LOG_CLI_ENABLE
#include "debug.h"

typedef struct {
    u8 request_connect_flag : 1;
    u8 recv_ssid_flag : 1;
} net_app_cfg_t;

static net_app_cfg_t net_app_cfg;

#define __this (&net_app_cfg)


static int net_wifi_event_handler(void *evt)
{
    struct net_event *event = (struct net_event *)evt;

    switch (event->event) {
    case NET_CONNECT_TIMEOUT_NOT_FOUND_SSID:
    case NET_CONNECT_ASSOCIAT_FAIL:
        if (!is_in_config_network_state() || __this->recv_ssid_flag) {
            play_tone_file(get_tone_files()->net_cfg_fail);
        }
        break;
    case NET_EVENT_SMP_CFG_FIRST:
        log_info("NET_EVENT_SMP_CFG_FIRST");
        /* play_tone_file(get_tone_files()->net_empty); */
        break;
    case NET_EVENT_CONNECTED:
        log_info("NET_EVENT_CONNECTED");
        if (!is_in_config_network_state()) {
#if TCFG_BT_NET_CFG_EN || (THIRD_PARTY_PROTOCOLS_SEL & NET_CFG_EN)
            void ble_cfg_net_result_notify(int event);
            ble_cfg_net_result_notify(event->event);
#endif
            play_tone_file(get_tone_files()->net_cfg_succ);
#ifdef CONFIG_SERVER_ASSIGN_PROFILE
            dev_profile_init();
#endif
        }
        __this->request_connect_flag = 0;
        __this->recv_ssid_flag = 0;
        break;
    case NET_EVENT_DISCONNECTED:
        log_info("NET_EVENT_DISCONNECTED");
        if (wifi_is_on() && !is_in_config_network_state() && !__this->request_connect_flag) {
            play_tone_file(get_tone_files()->net_disc);
        }
        break;
    case NET_EVENT_SMP_CFG_TIMEOUT:
        if (is_in_config_network_state()) {
            play_tone_file(get_tone_files()->net_cfg_to);
        }
        break;
    case NET_SMP_CFG_COMPLETED:
#ifdef CONFIG_AIRKISS_NET_CFG
        wifi_smp_set_ssid_pwd();
#endif
        break;
    case NET_EVENT_DISCONNECTED_AND_REQ_CONNECT:
        if (wifi_is_on()) {
            wifi_return_sta_mode();
        }
        break;
    case NET_SCR_EVENT_DISCONNECTED:
        int net_scr_stop(void);
        net_scr_stop();
        break;
    default:
        break;
    }

    return FALSE;
}

REGISTER_APP_EVENT_HANDLER(net_wifi_event) = {
    .event      = SYS_NET_EVENT,
    .from       = NET_EVENT_FROM_WIFI,
    .handler    = net_wifi_event_handler,
};

static int net_smp_cfg_event_handler(void *evt)
{
    struct net_event *event = (struct net_event *)evt;

    switch (event->event) {
    case NET_EVENT_SMP_CFG_FINISH:
        log_info("NET_EVENT_SMP_CFG_FINISH");
        if (is_in_config_network_state()) {
            play_tone_file(get_tone_files()->net_ssid_recv);
            config_network_stop();
            config_network_connect();
#if TCFG_SMART_VOICE_ENABLE
            audio_smart_voice_detect_open(JL_KWS_COMMAND_KEYWORD);
#endif
        } else {
            play_tone_file(get_tone_files()->net_ssid_recv);
            config_network_connect();
        }
        __this->recv_ssid_flag = 1;
        __this->request_connect_flag = 1;
        break;
    default:
        break;
    }

    return FALSE;
}

REGISTER_APP_EVENT_HANDLER(net_smp_cfg_event) = {
    .event      = SYS_NET_EVENT,
    .from       = NET_EVENT_FROM_USER,
    .handler    = net_smp_cfg_event_handler,
};


static void app_net_config_enter(void)
{
#ifdef CONFIG_ASSIGN_MACADDR_ENABLE
    cancel_server_assign_macaddr();
#endif
#ifdef CONFIG_SERVER_ASSIGN_PROFILE
    dev_profile_uninit();
#endif
    app_msg_handler(NULL, APP_MSG_SUSPEND);
    tts_player_stop();
    play_tone_file(get_tone_files()->net_cfg_enter);
#if TCFG_SMART_VOICE_ENABLE
    audio_smart_voice_detect_close();
#endif
    config_network_start();

    __this->recv_ssid_flag = 0;
}

static void app_net_config_exit(void)
{
    play_tone_file(get_tone_files()->net_connting);
    config_network_stop();
    wifi_return_sta_mode();
#if TCFG_SMART_VOICE_ENABLE
    audio_smart_voice_detect_open(JL_KWS_COMMAND_KEYWORD);
#endif
    __this->request_connect_flag = 1;
}

static int net_cfg_key_long_event(struct key_event *key)
{
    int ret = FALSE;

    switch (key->value) {
    case KEY_MODE:
        is_in_config_network_state() ? app_net_config_exit() : app_net_config_enter();
        break;
    default:
        break;
    }

    return ret;
}

static int net_cfg_key_event_handler(void *evt)
{
    struct key_event *key = (struct key_event *)evt;
    int ret = FALSE;

    switch (key->action) {
    case KEY_EVENT_LONG:
        ret = net_cfg_key_long_event(key);
        break;
    default:
        break;
    }

    return ret;
}

REGISTER_APP_EVENT_HANDLER(net_cfg_key_event) = {
    .event      = SYS_KEY_EVENT,
    .from       = KEY_EVENT_FROM_KEY,
    .handler    = net_cfg_key_event_handler,
};

#endif
