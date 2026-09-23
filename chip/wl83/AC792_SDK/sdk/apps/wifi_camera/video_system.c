#include "system/includes.h"
/* #include "server/ui_server.h" */
#include "video_system.h"

#include "action.h"
/* #include "style.h" */
#include "app_config.h"


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
static int show_main_ui()
{

    return 0;
}
static void hide_main_ui()
{
}


static int state_machine(struct application *app, enum app_state state, struct intent *it)
{
    int err = 0;

    switch (state) {
    case APP_STA_CREATE:
        video_sys_init();
        sys_fun_restore();

        break;
    case APP_STA_START:
        if (!it) {
            break;
        }
        switch (it->action) {
        case ACTION_SYSTEM_MAIN:
            break;
        case ACTION_SYSTEM_SD_CARD_FORMAT:
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
        case ACTION_SYSTEM_SET_CONFIG:
            err = video_sys_set_config(it);
            /* db_flush(); */
            break;
        }
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






static const struct application_operation video_system_ops = {
    .state_machine  = state_machine,
    .event_handler 	= NULL,
};

REGISTER_APPLICATION(app_video_system) = {
    .name 	= "video_system",
    .action	= ACTION_SYSTEM_MAIN,
    .ops 	= &video_system_ops,
    .state  = APP_STA_DESTROY,
};
