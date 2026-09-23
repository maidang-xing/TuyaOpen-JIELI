#include "app_config.h"
#include "system/includes.h"
#include "video_system.h"
#include "action.h"
#include "app_msg.h"

extern int video_sys_set_config(struct intent *it);

struct video_system_hdl sys_handler;

#define __this 	(&sys_handler)
#define sizeof_this     (sizeof(struct video_system_hdl))


static int video_sys_init(void)
{
    static u8 init = 0;
    if (init == 0) {
        init = 1;
        memset(__this, 0, sizeof_this);
    }
    return 0;
}

static int state_machine(struct application *app, enum app_state state, struct intent *it)
{
    int err = 0;

    switch (state) {
    case APP_STA_CREATE:

        printf("===========================%s  %d", __func__, __LINE__);
        video_sys_init();
        sys_fun_restore();

        break;
    case APP_STA_START:
        break;
    case APP_STA_PAUSE:
        break;
    case APP_STA_RESUME:
        break;
    case APP_STA_STOP:
        break;
    case APP_STA_DESTROY:
        break;
    }

    return err;
}


static int msg_handler(struct application *app, int *msg)
{
    int err = 0;
    int ret = 0;
    struct intent *it = NULL;

    printf("===========================%s  %d", __func__, __LINE__);
    it = (struct intent *)msg[1];
    switch (msg[0]) {
    case APP_MSG_SUSPEND:
        break;
    case APP_MSG_RESUME:
        break;
    case APP_MSG_STOP:
        break;
    case APP_MSG_SYSTEM_SD_CARD_FORMAT:
        printf("===========================%s  %d", __func__, __LINE__);
#if defined CONFIG_ENABLE_VLIST
        FILE_LIST_EXIT();
#endif
        err = sdcard_storage_device_format(SDX_DEV);
#if defined CONFIG_ENABLE_VLIST
        FILE_LIST_IN_MEM(1);
#endif
#ifdef CONFIG_WIFI_ENABLE
        net_video_rec_fmt_notify();
#endif
        break;
    case APP_MSG_SYSTEM_SET_CONFIG:
        err = video_sys_set_config(it);
        break;
    default:
        break;
    }
}




static const struct application_operation video_system_ops = {
    .state_machine  = state_machine,
    .event_handler 	= NULL,
    .msg_handler    = msg_handler,
};

REGISTER_APPLICATION(app_video_system) = {
    .name 	= "video_system",
    .action	= ACTION_SYSTEM_MAIN,
    .ops 	= &video_system_ops,
    .state  = APP_STA_DESTROY,
};
