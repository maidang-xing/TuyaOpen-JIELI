#include "system/includes.h"
#include "le_ancs_client.h"
#include "app_config.h"
#if THIRD_PARTY_PROTOCOLS_SEL
#include "multi_protocol_main.h"
#endif

#if (THIRD_PARTY_PROTOCOLS_SEL & ANCS_CLIENT_EN)

#if TCFG_LE_AUDIO_STREAM_ENABLE
#error "ANCS and LE_AUDIO cannot be opened together"
#endif

#define LOG_TAG     		"[LE_ANCS]"
#define LOG_ERROR_ENABLE
#define LOG_DEBUG_ENABLE
#define LOG_INFO_ENABLE
#define LOG_DUMP_ENABLE
#define LOG_WARN_ENABLE
#include "debug.h"

#define ANCS_SUBEVENT_CLIENT_CONNECTED                     0xF0
#define ANCS_SUBEVENT_CLIENT_NOTIFICATION                  0xF1
#define ANCS_SUBEVENT_CLIENT_DISCONNECTED                  0xF2
#define HCI_EVENT_ANCS_META                                0xEA

#define ANCS_MESSAGE_MANAGE_EN                                      1

void ancs_client_init(void);
void ancs_client_exit(void);
void ancs_client_register_callback(btstack_packet_handler_t callback);
const char *ancs_client_attribute_name_for_id(int id);
void ancs_set_notification_buffer(u8 *buffer, u16 buffer_size);
void ancs_set_out_callback(void *cb);

extern const int config_le_sm_support_enable;
extern const int config_le_gatt_client_num;

//ancs info buffer
#define ANCS_INFO_BUFFER_SIZE  (1024)
static u8 ancs_info_buffer[ANCS_INFO_BUFFER_SIZE];
static u16 ancs_client_adv_interval_min = 200;
static char gap_device_name[BT_NAME_LEN_MAX] = "JL-ANCS-TEST(BLE)";
static void *ancs_client_ble_hdl = NULL;

static const uint8_t ancs_client_profile_data[] = {
    //////////////////////////////////////////////////////
    //
    // 0x0001 PRIMARY_SERVICE  1800
    //
    //////////////////////////////////////////////////////
    0x0a, 0x00, 0x02, 0x00, 0x01, 0x00, 0x00, 0x28, 0x00, 0x18,

    /* CHARACTERISTIC,  2a00, READ | WRITE | DYNAMIC, */
    // 0x0002 CHARACTERISTIC 2a00 READ | WRITE | DYNAMIC
    0x0d, 0x00, 0x02, 0x00, 0x02, 0x00, 0x03, 0x28, 0x0a, 0x03, 0x00, 0x00, 0x2a,
    // 0x0003 VALUE 2a00 READ | WRITE | DYNAMIC
    0x08, 0x00, 0x0a, 0x01, 0x03, 0x00, 0x00, 0x2a,

    //////////////////////////////////////////////////////
    //
    // 0x0004 PRIMARY_SERVICE  ae00
    //
    //////////////////////////////////////////////////////
    0x0a, 0x00, 0x02, 0x00, 0x04, 0x00, 0x00, 0x28, 0x00, 0xae,

    /* CHARACTERISTIC,  ae01, WRITE_WITHOUT_RESPONSE | DYNAMIC, */
    // 0x0005 CHARACTERISTIC ae01 WRITE_WITHOUT_RESPONSE | DYNAMIC
    0x0d, 0x00, 0x02, 0x00, 0x05, 0x00, 0x03, 0x28, 0x04, 0x06, 0x00, 0x01, 0xae,
    // 0x0006 VALUE ae01 WRITE_WITHOUT_RESPONSE | DYNAMIC
    0x08, 0x00, 0x04, 0x01, 0x06, 0x00, 0x01, 0xae,

    /* CHARACTERISTIC,  ae02, NOTIFY, */
    // 0x0007 CHARACTERISTIC ae02 NOTIFY
    0x0d, 0x00, 0x02, 0x00, 0x07, 0x00, 0x03, 0x28, 0x10, 0x08, 0x00, 0x02, 0xae,
    // 0x0008 VALUE ae02 NOTIFY
    0x08, 0x00, 0x10, 0x00, 0x08, 0x00, 0x02, 0xae,
    // 0x0009 CLIENT_CHARACTERISTIC_CONFIGURATION
    0x0a, 0x00, 0x0a, 0x01, 0x09, 0x00, 0x02, 0x29, 0x00, 0x00,

    // END
    0x00, 0x00,
};

//
// characteristics <--> handles
//
#define ATT_CHARACTERISTIC_2a00_01_VALUE_HANDLE 0x0003
#define ATT_CHARACTERISTIC_ae01_01_VALUE_HANDLE 0x0006
#define ATT_CHARACTERISTIC_ae02_01_VALUE_HANDLE 0x0008
#define ATT_CHARACTERISTIC_ae02_01_CLIENT_CONFIGURATION_HANDLE 0x0009

static void ancs_client_cbk_packet_handler(void *hdl, uint8_t packet_type, uint16_t channel, uint8_t *packet, uint16_t size)
{
    u16 con_handle;

    /* log_debug("cbk packet_type:0x%x, packet[0]:0x%x, packet[2]:0x%x", packet_type, packet[0], packet[2]); */

    switch (packet_type) {
    case HCI_EVENT_PACKET:
        switch (hci_event_packet_get_type(packet)) {
        case ATT_EVENT_CAN_SEND_NOW:
            log_info("ATT_EVENT_CAN_SEND_NOW");
            break;

        case HCI_EVENT_LE_META:
            switch (hci_event_le_meta_get_subevent_code(packet)) {
            case HCI_SUBEVENT_LE_CONNECTION_COMPLETE:
                con_handle = little_endian_read_16(packet, 4);
                log_info("HCI_SUBEVENT_LE_CONNECTION_COMPLETE: %0x", con_handle);
                log_info_hexdump(&packet[8], 6);
                ancs_client_adv_enable(0);
                break;
            default:
                break;
            }
            break;

        case HCI_EVENT_DISCONNECTION_COMPLETE:
            log_info("HCI_EVENT_DISCONNECTION_COMPLETE: %0x", packet[5]);
            ancs_client_adv_enable(1);
            break;
        default:
            break;
        }
        break;
    }
    return;
}

static uint16_t ancs_client_att_read_callback(void *hdl, hci_con_handle_t connection_handle, uint16_t att_handle, uint16_t offset, uint8_t *buffer, uint16_t buffer_size)
{
    uint16_t att_value_len = 0;
    uint16_t handle = att_handle;

    log_info("read_callback, handle= 0x%04x, buffer= %08x", handle, (u32)buffer);

    switch (handle) {
    case ATT_CHARACTERISTIC_2a00_01_VALUE_HANDLE:
        att_value_len = strlen(gap_device_name);
        if ((offset >= att_value_len) || (offset + buffer_size) > att_value_len) {
            break;
        }
        if (buffer) {
            memcpy(buffer, &gap_device_name[offset], buffer_size);
            att_value_len = buffer_size;
            log_info("read gap_name: %s", gap_device_name);
        }
        break;
    case ATT_CHARACTERISTIC_ae02_01_CLIENT_CONFIGURATION_HANDLE:
        if (buffer) {
            buffer[0] = multi_att_get_ccc_config(connection_handle, handle);
            buffer[1] = 0;
        }
        att_value_len = 2;
        break;
    default:
        break;
    }
    log_info("att_value_len= %d", att_value_len);
    return att_value_len;
}

static int ancs_client_att_write_callback(void *hdl, hci_con_handle_t connection_handle, uint16_t att_handle, uint16_t transaction_mode, uint16_t offset, uint8_t *buffer, uint16_t buffer_size)
{
    u16 handle = att_handle;

    log_info("write_callback, handle= 0x%04x, size = %d", handle, buffer_size);

    switch (handle) {
    case ATT_CHARACTERISTIC_2a00_01_VALUE_HANDLE:
        break;
    case ATT_CHARACTERISTIC_ae01_01_VALUE_HANDLE:
        log_info("rx(%d):", buffer_size);
        log_info_hexdump(buffer, buffer_size);
    case ATT_CHARACTERISTIC_ae02_01_CLIENT_CONFIGURATION_HANDLE:
        log_info("write ccc:%04x, %02x", handle, buffer[0]);
        multi_att_set_ccc_config(connection_handle, handle, buffer[0]);
        break;
    default:
        break;
    }
    return 0;
}

static void ancs_event_callback(u8 packet_type, u16 channel, u8 *packet, u16 size)
{
    const char *attribute_name;
    if (hci_event_packet_get_type(packet) != HCI_EVENT_ANCS_META) {
        log_info("NO ANCE ENVET");
        return;
    }

    switch (hci_event_ancs_meta_get_subevent_code(packet)) {
    case ANCS_SUBEVENT_CLIENT_CONNECTED:
        log_info("ANCS Client: Connected");
        break;
    case ANCS_SUBEVENT_CLIENT_DISCONNECTED:
        log_info("ANCS Client: Disconnected");
        ancs_client_adv_enable(1);
        break;
    case ANCS_SUBEVENT_CLIENT_NOTIFICATION:
        log_info("ANCS_SUBEVENT_CLIENT_NOTIFICATION");
        attribute_name = ancs_client_attribute_name_for_id(ancs_subevent_client_notification_get_attribute_id(packet));
        if (!attribute_name) {
            log_info("ancs unknow attribute_id :%d", ancs_subevent_client_notification_get_attribute_id(packet));
            break;
        } else {
            u16 attribute_strlen = little_endian_read_16(packet, 7);
            u8 *attribute_str = (void *)little_endian_read_32(packet, 9);
            log_info("Notification: %s - %s", attribute_name, attribute_str);
        }
        break;
    default:
        break;
    }

}

static void ancs_notification_message_callback(u8 *packet, u16 size)
{
#if ANCS_MESSAGE_MANAGE_EN
    u8 *value;
    u32 ancs_notification_uid;
    value = &packet[8];
    ancs_notification_uid = little_endian_read_32(value, 4);
    log_info("Notification: EventID %02x, EventFlags %02x, CategoryID %02x, CategoryCount %u, UID %04x",
             value[0], value[1], value[2], value[3], little_endian_read_32(value, 4));

    if (value[1] & BIT(2)) {
        log_info("is PreExisting Message!!!");
    }

    if (value[0] == 2) { //0:added 1:modifiled 2:removed
        log_info("remove message:ancs_notification_uid %04x", ancs_notification_uid);
    } else if (value[0] == 0) {
        log_info("add message:ancs_notification_uid %04x", ancs_notification_uid);
    }
#endif
}

int ancs_client_adv_enable(u8 enable)
{
    uint8_t len = 0;
    uint8_t offset = 0;
    uint8_t adv_type = ADV_IND;
    uint8_t adv_channel = ADV_CHANNEL_ALL;
    uint8_t advData[ADV_RSP_PACKET_MAX] = {0};
    uint8_t rspData[ADV_RSP_PACKET_MAX] = {0};
    const uint8_t ancs_uuid[] = {
        0xD0, 0x00, 0x2D, 0x12, 0x1E, 0x4B, 0x0F, 0xA4, 0x99, 0x4E, 0xCE, 0xB5, 0x31, 0xF4, 0x05, 0x79
    };

    offset += make_eir_packet_val(&advData[offset], offset, HCI_EIR_DATATYPE_FLAGS, 0x06, 1);
    offset += make_eir_packet_data(&advData[offset], offset, HCI_EIR_DATATYPE_128BIT_SERVICE_SOLICITATION_UUIDS, (void *)ancs_uuid, sizeof(ancs_uuid));

    offset = 0;
    offset += make_eir_packet_data(&rspData[offset], offset, HCI_EIR_DATATYPE_COMPLETE_LOCAL_NAME, (void *)gap_device_name, strlen(gap_device_name));

    if (enable == app_ble_adv_state_get(ancs_client_ble_hdl)) {
        return 0;
    }

    if (enable) {
        app_ble_set_adv_param(ancs_client_ble_hdl, ancs_client_adv_interval_min, adv_type, adv_channel);
        len = sizeof(advData);
        if (len) {
            app_ble_adv_data_set(ancs_client_ble_hdl, advData, len);
        }
        len = strlen(rspData);
        if (len) {
            app_ble_rsp_data_set(ancs_client_ble_hdl, rspData, len);
        }
    }
    app_ble_adv_enable(ancs_client_ble_hdl, enable);
    return 0;
}

//协议栈sm 消息回调处理
static void ancs_client_cbk_sm_packet_handler(void *hdl, uint8_t packet_type, uint16_t channel, uint8_t *packet, uint16_t size)
{
    sm_just_event_t *event = (void *)packet;

    switch (packet_type) {
    case HCI_EVENT_PACKET:
        switch (hci_event_packet_get_type(packet)) {
        case SM_EVENT_JUST_WORKS_REQUEST:
            log_info("Just Works Confirmed.");
            sm_just_works_confirm(sm_event_just_works_request_get_handle(packet));
            break;
        case SM_EVENT_PASSKEY_DISPLAY_NUMBER:
            u32 tmp32;
            log_info_hexdump(packet, size);
            memcpy(&tmp32, event->data, 4);
            log_info("Passkey display: %06u", tmp32);
            break;
        case SM_EVENT_PAIR_PROCESS:
            log_info("SM_PAIR_PROCESS: %02x", event->data[0]);
            switch (event->data[0]) {
            case SM_EVENT_PAIR_SUB_RECONNECT_START:
                break;
            case SM_EVENT_PAIR_SUB_PAIR_FAIL:
            case SM_EVENT_PAIR_SUB_PIN_KEY_MISS:
            case SM_EVENT_PAIR_SUB_PAIR_TIMEOUT:
            case SM_EVENT_PAIR_SUB_ADD_LIST_SUCCESS:
            case SM_EVENT_PAIR_SUB_ADD_LIST_FAILED:
            default:
                break;
            }
        }
        break;
    }
}

#define PASSKEY_ENTER_ENABLE      0 //输入passkey使能，可修改passkey
//重设passkey回调函数，在这里可以重新设置passkey
//passkey为6个数字组成，十万位、万位。。。。个位 各表示一个数字 高位不够为0
static void reset_passkey_cb(u32 *key)
{
#if 1
    u32 newkey = rand32();//获取随机数

    newkey &= 0xfffff;
    if (newkey > 999999) {
        newkey = newkey - 999999; //不能大于999999
    }
    *key = newkey; //小于或等于六位数
    printf("set new_key= %06u\n", *key);
#else
    *key = 123456; //for debug
#endif
}

void ancs_client_all_init(void)
{
    log_info("ANCS CLIENT INIT");
    if ((!config_le_sm_support_enable) || (!config_le_gatt_client_num)) {
        log_error("ANCS need sm and client support!!!\n");
        ASSERT(0);
    }
    const uint8_t *edr_addr = bt_get_mac_addr();

    if (ancs_client_ble_hdl == NULL) {
        ancs_client_ble_hdl = app_ble_hdl_alloc();
        if (ancs_client_ble_hdl == NULL) {
            log_error("ancs_client_ble_hdl alloc err !");
            return;
        }
        //set ble mac addr
        app_ble_set_mac_addr(ancs_client_ble_hdl, (void *)edr_addr);

        //setup ATT server
        app_ble_profile_set(ancs_client_ble_hdl, ancs_client_profile_data);
        app_ble_att_read_callback_register(ancs_client_ble_hdl, ancs_client_att_read_callback);
        app_ble_att_write_callback_register(ancs_client_ble_hdl, ancs_client_att_write_callback);
        app_ble_att_server_packet_handler_register(ancs_client_ble_hdl, ancs_client_cbk_packet_handler);

        // register for HCI events
        app_ble_hci_event_callback_register(ancs_client_ble_hdl, ancs_client_cbk_packet_handler);
        app_ble_l2cap_packet_handler_register(ancs_client_ble_hdl, ancs_client_cbk_packet_handler);

        // register for sm events
        app_ble_sm_event_callback_register(ancs_client_ble_hdl, ancs_client_cbk_sm_packet_handler);
#if PASSKEY_ENTER_ENABLE
        reset_PK_cb_register(reset_passkey_cb);
#endif
        //setup GATT client
        gatt_client_init();

        //setup ANCS clent
        ancs_client_init();
        ancs_set_notification_buffer(ancs_info_buffer, sizeof(ancs_info_buffer));
        ancs_client_register_callback(&ancs_event_callback);
        ancs_set_out_callback(ancs_notification_message_callback);

        //setup ble adv
        ancs_client_adv_enable(1);
    }
}

void ancs_client_all_exit(void)
{
    log_info("ANCS CLIENT EXIT");

    if (app_ble_get_hdl_con_handle(ancs_client_ble_hdl)) {
        app_ble_disconnect(ancs_client_ble_hdl);
    }
    ancs_client_exit();
    app_ble_hdl_free(ancs_client_ble_hdl);
    ancs_client_ble_hdl = NULL;
}

#endif
