#include "app_config.h"
#include "bt_common.h"
#include "le_common.h"
#include "event/bt_event.h"
#include "multi_protocol_main.h"


#define LOG_TAG_CONST        BLE
#define LOG_TAG             "[BLE]"
#define LOG_ERROR_ENABLE
#define LOG_DEBUG_ENABLE
#define LOG_INFO_ENABLE
#define LOG_DUMP_ENABLE
#define LOG_CLI_ENABLE
#include "debug.h"


void bt_ble_module_init(void)
{
#if TCFG_USER_BLE_ENABLE
    u8 tmp_ble_addr[6];
    extern const u8 *bt_get_mac_addr(void);
    bt_make_ble_address(tmp_ble_addr, (u8 *)bt_get_mac_addr());
    le_controller_set_mac((void *)tmp_ble_addr);
    log_info("-----edr + ble 's address-----");
    put_buf((void *)bt_get_mac_addr(), 6);
    put_buf((void *)tmp_ble_addr, 6);

#if (THIRD_PARTY_PROTOCOLS_SEL & LE_HOGP_EN)
    void ble_hid_set_config(void);
    ble_hid_set_config();
#endif
#endif

    btstack_init();
}

static int bt_connction_status_event_handler(struct bt_event *bt)
{
    switch (bt->event) {
    case BT_STATUS_INIT_OK:
#if THIRD_PARTY_PROTOCOLS_SEL
        multi_protocol_bt_init();
#endif
        break;
    }

    return 0;
}

int ble_demo_bt_event_handler(struct sys_event *event)
{
    if (event->from == BT_EVENT_FROM_CON) {
        return bt_connction_status_event_handler((struct bt_event *)event->payload);
    }

    return 0;
}


#if (THIRD_PARTY_PROTOCOLS_SEL & LE_HOGP_EN)

#include "le_hogp/standard_hid.h"

static const u8 hid_descriptor_keyboard_boot_mode[] = {
    0x05, 0x01,        // Usage Page (Generic Desktop Ctrls)
    0x09, 0x06,        // Usage (Keyboard)
    0xA1, 0x01,        // Collection (Application)
    0x85, 0x01,        //   Report ID (1)
    0x05, 0x07,        //   Usage Page (Kbrd/Keypad)
    0x19, 0xE0,        //   Usage Minimum (0xE0)
    0x29, 0xE7,        //   Usage Maximum (0xE7)
    0x15, 0x00,        //   Logical Minimum (0)
    0x25, 0x01,        //   Logical Maximum (1)
    0x75, 0x01,        //   Report Size (1)
    0x95, 0x08,        //   Report Count (8)
    0x81, 0x02,        //   Input (Data,Var,Abs,No Wrap,Linear,Preferred State,No Null Position)
    0x95, 0x01,        //   Report Count (1)
    0x75, 0x08,        //   Report Size (8)
    0x81, 0x01,        //   Input (Const,Array,Abs,No Wrap,Linear,Preferred State,No Null Position)
    0x95, 0x06,        //   Report Count (6)
    0x75, 0x08,        //   Report Size (8)
    0x15, 0x00,        //   Logical Minimum (0)
    0x25, 0x65,        //   Logical Maximum (101)
    0x05, 0x07,        //   Usage Page (Kbrd/Keypad)
    0x19, 0x00,        //   Usage Minimum (0x00)
    0x29, 0x65,        //   Usage Maximum (0x65)
    0x81, 0x00,        //   Input (Data,Array,Abs,No Wrap,Linear,Preferred State,No Null Position)
    0x95, 0x05,        //   Report Count (5)
    0x75, 0x01,        //   Report Size (1)
    0x05, 0x08,        //   Usage Page (LEDs)
    0x19, 0x01,        //   Usage Minimum (Num Lock)
    0x29, 0x05,        //   Usage Maximum (Kana)
    0x91, 0x02,        //   Output (Data,Var,Abs,No Wrap,Linear,Preferred State,No Null Position,Non-volatile)
    0x95, 0x01,        //   Report Count (1)
    0x75, 0x03,        //   Report Size (3)
    0x91, 0x03,        //   Output (Const,Var,Abs,No Wrap,Linear,Preferred State,No Null Position,Non-volatile)
    0xC0,              // End Collection
};

//----------------------------------
#define KEYBOARD_REPORT_MAP \
	USAGE_PAGE(CONSUMER_PAGE),              \
	USAGE(CONSUMER_CONTROL),                \
	COLLECTION(APPLICATION),                \
	REPORT_ID(1),      \
	USAGE(VOLUME_INC),                  \
	USAGE(VOLUME_DEC),                  \
	USAGE(PLAY_PAUSE),                  \
	USAGE(MUTE),                        \
	USAGE(SCAN_PREV_TRACK),             \
	USAGE(SCAN_NEXT_TRACK),             \
	USAGE(FAST_FORWARD),                \
	USAGE(REWIND),                      \
	LOGICAL_MIN(0),                     \
	LOGICAL_MAX(1),                     \
	REPORT_SIZE(1),                     \
	REPORT_COUNT(16),                   \
	INPUT(0x02),                        \
	END_COLLECTION,                         \

static const u8 hid_report_map[] = {KEYBOARD_REPORT_MAP};

void ble_hid_set_config(void)
{
    le_hogp_set_icon(0x03c1);//ble keyboard demo
    le_hogp_set_ReportMap(hid_descriptor_keyboard_boot_mode, sizeof(hid_descriptor_keyboard_boot_mode));
}
#endif

