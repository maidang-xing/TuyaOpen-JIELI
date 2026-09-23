#include "system/includes.h"
#include "local_tws.h"
#include "local_tws_player.h"
#include "app_msg.h"
#include "asm/rf_coexistence_config.h"
#include "app_config.h"

#if TCFG_LOCAL_TWS_ENABLE

static app_mode_t sink_mode_rsp_arg;

static void app_sink_set_sink_mode_rsp_arg(app_mode_t arg)
{
    sink_mode_rsp_arg = arg;
}

static int sink_music_msg_handler(struct application *app, int *msg)
{
    switch (msg[0]) {
    case APP_MSG_SUSPEND:
        break;
    case APP_MSG_RESUME:
        break;
    case APP_MSG_STOP:
        break;
#if TCFG_LOCAL_TWS_SYNC_VOL
    case APP_MSG_SINK_MUSIC_VOL_UP:
        log_info("sink music vol up");
        local_tws_vol_operate(CMD_TWS_VOL_UP);
        break;
    case APP_MSG_SINK_MUSIC_VOL_DOWN:
        log_info("sink music vol down");
        local_tws_vol_operate(CMD_TWS_VOL_DOWN);
        break;
#endif
    case APP_MSG_SINK_MUSIC_PP:
        log_info("sink music pp");
        local_tws_music_operate(CMD_TWS_MUSIC_PP, &sink_mode_rsp_arg);
        break;
    case APP_MSG_SINK_MUSIC_PREV:
        log_info("sink music prev");
        local_tws_music_operate(CMD_TWS_MUSIC_PREV, NULL);
        break;
    case APP_MSG_SINK_MUSIC_NEXT:
        log_info("sink music next");
        local_tws_music_operate(CMD_TWS_MUSIC_NEXT, NULL);
        break;
    default:
        break;
    }

    return 0;
}

static int sink_music_init(void)
{
    local_tws_enter_sink_mode_rsp(sink_mode_rsp_arg);

    log_info("enter sink mode success");

    return 0;
}

static void sink_music_exit(void)
{
    if (__this->player) {
        local_tws_player_close(__this->player);
        __this->player = NULL;
    }

    rf_coexistence_scene_exit(RF_COEXISTENCE_SCENE_LOCAL_TWS_RX);

    log_info("exit sink mode success");
}

static int sink_music_key_click(struct key_event *key)
{
    int ret = FALSE;

    switch (key->value) {
    case KEY_OK:
        app_send_message(APP_MSG_SINK_MUSIC_PP, 0);
        break;
    case KEY_PLAY:
        app_send_message(APP_MSG_SINK_MUSIC_PLAY, 0);
        break;
    case KEY_PAUSE:
        app_send_message(APP_MSG_SINK_MUSIC_PAUSE, 0);
        break;
    case KEY_VOLUME_DEC:
    case KEY_UP:
    case KEY_PREV:
        app_send_message(APP_MSG_SINK_MUSIC_VOL_DOWN, 0);
        break;
    case KEY_VOLUME_INC:
    case KEY_DOWN:
    case KEY_NEXT:
        app_send_message(APP_MSG_SINK_MUSIC_VOL_UP, 0);
        break;
    default:
        ret = FALSE;
        break;
    }

    return ret;
}

static int sink_music_key_long(struct key_event *key)
{
    int ret = TRUE;

    switch (key->value) {
    case KEY_VOLUME_DEC:
    case KEY_UP:
    case KEY_PREV:
        app_send_message(APP_MSG_SINK_MUSIC_PREV, 0);
        break;
    case KEY_VOLUME_INC:
    case KEY_DOWN:
    case KEY_NEXT:
        app_send_message(APP_MSG_SINK_MUSIC_NEXT, 0);
        break;
    default:
        ret = FALSE;
        break;
    }

    return ret;
}

static int sink_music_key_event_handler(struct key_event *key)
{
    int ret = FALSE;

    switch (key->action) {
    case KEY_EVENT_CLICK:
        ret = sink_music_key_click(key);
        break;
    case KEY_EVENT_LONG:
        ret = sink_music_key_long(key);
        break;
    default:
        break;
    }

    return ret;
}

static int sink_music_event_handler(struct application *app, struct sys_event *event)
{
    switch (event->type) {
    case SYS_KEY_EVENT:
        return sink_music_key_event_handler((struct key_event *)event->payload);
    default:
        return FALSE;
    }
}

static int sink_music_state_machine(struct application *app, enum app_state state,
                                    struct intent *it)
{
    switch (state) {
    case APP_STA_CREATE:
        sink_music_init();
        break;
    case APP_STA_START:
        break;
    case APP_STA_PAUSE:
        /* sink_music_app_suspend(); */
        break;
    case APP_STA_RESUME:
        /* sink_music_app_resume(); */
        break;
    case APP_STA_STOP:
        break;
    case APP_STA_DESTROY:
        sink_music_exit();
        break;
    case APP_STA_COMPLETE:
        break;
    }

    return 0;
}

static const struct application_operation sink_music_ops = {
    .state_machine  = sink_music_state_machine,
    .event_handler 	= sink_music_event_handler,
    .msg_handler 	= sink_music_msg_handler,
};

REGISTER_APPLICATION(sink_music) = {
    .name   = "sink_music",
    .ops    = &sink_music_ops,
    .state  = APP_STA_DESTROY,
};

#endif
