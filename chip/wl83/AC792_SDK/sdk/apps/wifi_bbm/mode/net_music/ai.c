#include "app_config.h"
#include "app_msg.h"
#include "event/event.h"
#include "event/key_event.h"
#include "event/net_event.h"
#include "net/config_network.h"
#include "server/server_core.h"
#include "server/ai_server.h"
#include "tone_player.h"
#include "tts_player.h"
#include "esco_player.h"
#include "mic_effect.h"

#ifdef CONFIG_NET_ENABLE

enum {
    LISTEN_STATE_STOP = 0,
    LISTEN_STATE_STOPPING,
    LISTEN_STATE_START,
    LISTEN_STATE_WAKEUP,
};

int get_ai_listen_state(void)
{
    return __this->listening;
}

static void main_ai_app_event_notify(enum ai_server_event event)
{
    union ai_req req = {0};

    if (__this->ai_server && __this->tts_ai_name && strcmp(__this->tts_ai_name, "null")) {
        req.evt.event = event;
        req.evt.ai_name = __this->tts_ai_name;
        ai_server_request(__this->ai_server, AI_REQ_EVENT, &req);
    }
}

static void main_ai_app_event_notify_value(enum ai_server_event event, int value)
{
    union ai_req req = {0};

    if (__this->ai_server && __this->tts_ai_name && strcmp(__this->tts_ai_name, "null")) {
        req.evt.event = event;
        req.evt.ai_name = __this->tts_ai_name;
        req.evt.arg = value;
        ai_server_request(__this->ai_server, AI_REQ_EVENT, &req);
    }
}

static void ai_app_event_notify(enum ai_server_event event)
{
    union ai_req req = {0};

    if (__this->ai_server && __this->ai_name) {
        req.evt.event = event;
        req.evt.ai_name = __this->ai_name;
        if (AI_EVENT_SPEAK_END == event) {
            req.evt.ai_name = __this->tts_ai_name;
        }
        ai_server_request(__this->ai_server, AI_REQ_EVENT, &req);
    }
}

static void ai_app_event_notify_value(enum ai_server_event event, int value)
{
    union ai_req req = {0};

    if (__this->ai_server && __this->ai_name) {
        req.evt.event = event;
        req.evt.ai_name = __this->ai_name;
        req.evt.arg = value;
        ai_server_request(__this->ai_server, AI_REQ_EVENT, &req);
    }
}

static void ai_app_listen_break(void)
{
    if (__this->listening == LISTEN_STATE_STOP) {
        return;
    }

    if (!__this->ai_connected) {
        __this->listening = LISTEN_STATE_STOP;
        return;
    }

    tone_player_stop();

    if (__this->listening == LISTEN_STATE_WAKEUP) {
        __this->listening = LISTEN_STATE_STOP;
        return;
    }

    if (__this->listening != LISTEN_STATE_STOPPING) {
        union ai_req req = {0};
        req.evt.event = AI_EVENT_RECORD_BREAK;
        req.evt.ai_name = __this->ai_name;
        ai_server_request(__this->ai_server, AI_REQ_EVENT, &req);
        __this->listening = LISTEN_STATE_STOPPING;
    }
}

static void ai_app_listen_stop(void)
{
    union ai_req req = {0};

    if (__this->listening == LISTEN_STATE_STOP) {
        return;
    }

    if (__this->listening != LISTEN_STATE_STOPPING) {
        if (__this->ai_server) {
            req.lis.cmd = AI_LISTEN_STOP;
            ai_server_request(__this->ai_server, AI_REQ_LISTEN, &req);
        }
    }

    __this->listening = LISTEN_STATE_STOP;
}

static int __ai_app_listen_start(u8 voice_mode)
{
    union ai_req req = {0};

    if (!__this->ai_connected) {
        __this->listening = LISTEN_STATE_STOP;
#if TCFG_MIC_EFFECT_ENABLE
        mic_effect_player_pause(0);
#endif
        return -1;
    }

    req.lis.arg = voice_mode;
    req.lis.cmd = AI_LISTEN_START;

    int err = ai_server_request(__this->ai_server, AI_REQ_LISTEN, &req);
    if (err == 0) {
        __this->listening = LISTEN_STATE_START;
        if ((voice_mode & 0xf) == WECHAT_MODE) {
            __this->wechat_flag = 1;
        }
    } else {
        __this->listening = LISTEN_STATE_STOP;
#if TCFG_MIC_EFFECT_ENABLE
        mic_effect_player_pause(0);
#endif
    }

    return err;
}

static int ai_tone_play_end_callback(void *priv, enum stream_event event)
{
    switch (event) {
    case STREAM_EVENT_STOP:
        ///提示音播放结束，启动mic
        __ai_app_listen_start((int)priv);
        break;
    default:
        break;
    }

    return 0;
}

static int send_tone_play_end_callback(void *priv, enum stream_event event)
{
    switch (event) {
    case STREAM_EVENT_STOP:
#if TCFG_MIC_EFFECT_ENABLE
        mic_effect_player_pause(1);
#endif
        break;
    default:
        break;
    }

    return 0;
}

static int ai_app_listen_start(int voice_mode, int enable_vad)
{
    int err;

    __this->wechat_flag = 0;

    if (!__this->ai_connected) {
        if (WECHAT_MODE == voice_mode) {

        } else if (AI_MODE == voice_mode) {

        } else if (TRANSLATE_MODE == voice_mode) {

        }
        return -1;
    }

    app_msg_handler(NULL, APP_MSG_SUSPEND);

    tone_player_stop();

#if TCFG_MIC_EFFECT_ENABLE
    mic_effect_player_pause(1);
#endif

    if (__this->listening == LISTEN_STATE_START) {
        ai_app_listen_stop();
    }

    tts_player_stop();

    if (enable_vad && voice_mode != WECHAT_MODE) {
        voice_mode |= VAD_ENABLE;	//enable local vad
    }

    err = play_tone_file_callback(get_tone_files()->rec, (void *)voice_mode, ai_tone_play_end_callback);
    if (err) {
        return __ai_app_listen_start(voice_mode);
    }

    __this->listening = LISTEN_STATE_WAKEUP;

    return 0;
}

static int ai_tts_play_end_callback(void *priv, enum stream_event event)
{
    switch (event) {
    case STREAM_EVENT_NONE:
    case STREAM_EVENT_STOP:
        break;
    case STREAM_EVENT_END:
        ///TTS播放结束
        ai_app_event_notify(AI_EVENT_SPEAK_END);
        break;
    default:
        break;
    }

    return 0;
}

static void ai_app_tts_play_start(const char *url)
{
    if (__this->listening == LISTEN_STATE_WAKEUP || __this->listening == LISTEN_STATE_START) {
        free((void *)url);
        return;
    }

    tts_player_stop();

    app_msg_handler(NULL, APP_MSG_SUSPEND);

    if (play_tts_file_callback(url, NULL, ai_tts_play_end_callback)) {
        ai_app_event_notify(AI_EVENT_SPEAK_END);
    }

    free((void *)url);
}

static void ai_app_url_play_start(const char *url, const char *ai_name)
{
    if (__this->listening == LISTEN_STATE_WAKEUP || __this->listening == LISTEN_STATE_START) {
        free((void *)url);
        return;
    }

    if (FALSE == current_app_in_mode(APP_MODE_NET)) {
        app_msg_handler(NULL, APP_MSG_STOP);
        app_mode_change_replace(APP_MODE_NET);
    }

    if (strcmp(__this->ai_name, ai_name)) {
        ai_app_event_notify_value(AI_EVENT_MEDIA_STOP, 0);
    }

    __this->ai_name = ai_name;

    if (strcmp(__this->tts_ai_name, ai_name)) {
        main_ai_app_event_notify_value(AI_EVENT_LOCAL_PP, 0);
    }

    app_send_message(APP_MSG_NET_MUSIC_PLAY_START, 1, url);
}

static void ai_server_event_handler(void *priv, int argc, int *argv)
{
    log_info("ai server event : 0x%x", argv[0]);

#if TCFG_USER_BT_CLASSIC_ENABLE && TCFG_BT_SUPPORT_PROFILE_HFP
    if (esco_player_runing()) {
        switch (argv[0]) {
        case AI_SERVER_EVENT_CONNECTED:
            __this->ai_connected = 1;
            break;
        case AI_SERVER_EVENT_DISCONNECTED:
            __this->ai_connected = 0;
            break;
        case AI_SERVER_EVENT_URL:
        case AI_SERVER_EVENT_URL_MEDIA:
        /* ai_app_event_notify_value(AI_EVENT_MEDIA_STOP, 0); */
        case AI_SERVER_EVENT_URL_TTS:
            free((void *)argv[1]);
            break;
        case AI_SERVER_EVENT_CONTINUE:
        case AI_SERVER_EVENT_PAUSE:
            break;
        case AI_SERVER_EVENT_STOP:
            if (!strcmp(__this->ai_name, (const char *)argv[2])) {
                app_send_message(APP_MSG_NET_MUSIC_PLAY_STOP, 0);
            }
            break;
        default:
            break;
        }

        return;
    }
#endif

    switch (argv[0]) {
    case AI_SERVER_EVENT_CONNECTED:
        __this->ai_connected = 1;
        break;
    case AI_SERVER_EVENT_DISCONNECTED:
        __this->ai_connected = 0;
        break;
    case AI_SERVER_EVENT_URL_TTS:
        ai_app_tts_play_start((const char *)argv[1]);
        break;
    case AI_SERVER_EVENT_URL:
    case AI_SERVER_EVENT_URL_MEDIA:
        ai_app_url_play_start((const char *)argv[1], (const char *)argv[2]);
        break;
    case AI_SERVER_EVENT_CONTINUE:
        app_send_message(APP_MSG_NET_MUSIC_PLAY, 1, 0);
        break;
    case AI_SERVER_EVENT_PAUSE:
        app_send_message(APP_MSG_NET_MUSIC_PAUSE, 1, 0);
        break;
    case AI_SERVER_EVENT_STOP:
        if (!strcmp(__this->ai_name, (const char *)argv[2])) {
            app_send_message(APP_MSG_NET_MUSIC_PLAY_STOP, 0);
        }
        break;
    case AI_SERVER_EVENT_RESUME_PLAY:
        break;
    case AI_SERVER_EVENT_SEEK:
        break;
    case AI_SERVER_EVENT_VOLUME_CHANGE:
        app_send_message(APP_MSG_NET_MUSIC_VOL_SET, 1, argv[1]);
        break;
    case AI_SERVER_EVENT_MIC_OPEN:
        if (__this->listening == LISTEN_STATE_STOP) {
            __this->listening = LISTEN_STATE_START;
            tone_player_stop();
            play_tone_file(get_tone_files()->rec);
        }
        if (argv[1]) {
            os_sem_post((OS_SEM *)argv[1]);
        }
        break;
    case AI_SERVER_EVENT_MIC_CLOSE:
        if (__this->listening == LISTEN_STATE_START) {
            __this->listening = LISTEN_STATE_STOP;
            tone_player_stop();
            if (play_tone_file_callback(get_tone_files()->send, NULL, send_tone_play_end_callback)) {
#if TCFG_MIC_EFFECT_ENABLE
                mic_effect_player_pause(1);
#endif
            }
        }
        break;
    case AI_SERVER_EVENT_LOCAL_PLAY_PAUSE:
        app_msg_handler(NULL, APP_MSG_SUSPEND);
        break;
    case AI_SERVER_EVENT_LOCAL_PLAY_RESUME:
        app_msg_handler(NULL, APP_MSG_RESUME);
        break;
    case AI_SERVER_EVENT_LOCAL_PLAY_STOP:
        break;
    default:
        break;
    }
}

static void ai_server_connect(void)
{
    union ai_req req = {0};

    if (__this->ai_server) {
        return;
    }

#if defined CONFIG_DUER_SDK_ENABLE
    __this->tts_ai_name = "duer";
#else
    __this->tts_ai_name = "null";
#endif

    __this->ai_name = __this->tts_ai_name;

    __this->ai_server = server_open("ai_server", NULL);
    if (__this->ai_server) {
        server_register_event_handler(__this->ai_server, NULL, ai_server_event_handler);
        ai_server_request(__this->ai_server, AI_REQ_CONNECT, &req);
    }
}

static void ai_server_disconnect(void)
{
    if (__this->ai_server) {
        __this->ai_connected = 0;
        server_close(__this->ai_server);
        __this->ai_server = NULL;
    }
}

static int ai_net_event_handler(void *evt)
{
    struct net_event *event = (struct net_event *)evt;

    switch (event->event) {
    case NET_EVENT_CONNECTED:
        log_info("AI_NET_EVENT_CONNECTED");
        ai_server_connect();
        break;
    case NET_EVENT_DISCONNECTED:
        log_info("AI_NET_EVENT_DISCONNECTED");
        ai_server_disconnect();
        break;
    default:
        break;
    }

    return FALSE;
}

REGISTER_APP_EVENT_HANDLER(ai_net_event) = {
    .event      = SYS_NET_EVENT,
    .from       = NET_EVENT_FROM_WIFI,
    .handler    = ai_net_event_handler,
};

static int ai_key_click_event(struct key_event *key)
{
    int ret = FALSE;

    switch (key->value) {
    case KEY_POWER:
    case KEY_ENC:
        ai_app_listen_start(AI_MODE, 1);
        ret = TRUE;
        break;
    default:
        break;
    }

    return ret;
}

static int ai_key_event_handler(void *evt)
{
    struct key_event *key = (struct key_event *)evt;
    int ret = FALSE;

    switch (key->action) {
    case KEY_EVENT_CLICK:
        ret = ai_key_click_event(key);
        break;
    default:
        break;
    }

    return ret;
}

REGISTER_APP_EVENT_HANDLER(ai_key_event) = {
    .event      = SYS_KEY_EVENT,
    .from       = KEY_EVENT_FROM_KEY,
    .handler    = ai_key_event_handler,
};

void ai_app_local_event_notify(enum play_status status)
{
    if (status == FILE_PLAYER_STOP) {
        main_ai_app_event_notify_value(AI_EVENT_MEDIA_STOP, 1);
    } else {
        main_ai_app_event_notify_value(AI_EVENT_LOCAL_PP, status == FILE_PLAYER_PAUSE);
    }
}

#endif
