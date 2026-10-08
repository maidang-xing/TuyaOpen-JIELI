#include "app_config.h"
#include "event/device_event.h"
#include "event/event.h"
#include "usb_common_def.h"

#if defined(TCFG_USB_SLAVE_ENABLE) && TCFG_USB_SLAVE_ENABLE
extern int pc_device_event_handler(struct sys_event *event);

static int jieli_usb_download_event_handler(struct sys_event *event)
{
    if (event == NULL || event->from != DEVICE_EVENT_FROM_OTG) {
        return 0;
    }

    return pc_device_event_handler(event);
}

#if defined(JIELI_SELECTED_CHIP_WL83)
SYS_EVENT_STATIC_HANDLER_REGISTER(jieli_usb_download_event, 0) = {
#else
SYS_EVENT_STATIC_HANDLER_REGISTER(jieli_usb_download_event) = {
#endif
    .event_type = SYS_DEVICE_EVENT,
    .prob_handler = jieli_usb_download_event_handler,
    .post_handler = NULL,
};
#endif
