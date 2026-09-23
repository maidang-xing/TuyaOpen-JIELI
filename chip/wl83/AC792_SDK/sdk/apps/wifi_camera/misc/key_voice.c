#include "system/includes.h"
#include "app_config.h"
#include "app_tone.h"
#include "app_msg.h"
#include "dev_manager.h"
#include "file_recorder.h"
#include "event/key_event.h"
#include "event/touch_event.h"
/* #include "event/device_event.h" */




static u8 tone_play_process = 0;

static int tone_play_end_callback(void *priv, enum stream_event event)
{
    /* printf("======================event:%d",event); */
    switch (event) {
    case STREAM_EVENT_END:
    case STREAM_EVENT_STOP:
        /* tone_play_process = 0; */
        break;
    default:
        break;
    }
    return 0;
}



static int key_event_handler(struct sys_event *e)
{

    struct key_event *key = (struct key_event *)e->payload;

    if (!db_select("kvo")) {
        return -1;
    }
    /* if(tone_play_process) { */
    /* return -1; */
    /* } */

    /* tone_play_process = 1; */

    if (key->action != KEY_EVENT_DOWN) {
        return -1;
    }

    if (key->value != KEY_PHOTO) {
        return -1;
    }

    tone_player_stop();
    play_tone_file_callback(get_tone_files()->bottom, NULL,
                            tone_play_end_callback);


    return 0;
}
/*
 * 静态注册按键事件处理函数
 */
SYS_EVENT_STATIC_HANDLER_REGISTER(key_voice_handler, 1) = {
    .event_type = SYS_KEY_EVENT,
    .prob_handler = key_event_handler,
    .post_handler = NULL,
};

static int touch_event_handler(struct sys_event *e)
{
    struct touch_event *touch = (struct touch_event *)e->payload;

    if (!db_select("kvo")) {
        return -1;
    }
    /* printf("tone_play_process:%d",tone_play_process); */
    /* if(tone_play_process) { */
    /* return -1; */
    /* } */

    /* tone_play_process = 1; */

    if (touch->action != TOUCH_EVENT_DOWN) {
        return -1;
    }

    tone_player_stop();

    play_tone_file_callback(get_tone_files()->bottom, NULL,
                            tone_play_end_callback);

    return 0;
}

SYS_EVENT_STATIC_HANDLER_REGISTER(touch_voice_handler, 1) = {
    .event_type = SYS_TOUCH_EVENT,
    .prob_handler = touch_event_handler,
    .post_handler = NULL,
};


