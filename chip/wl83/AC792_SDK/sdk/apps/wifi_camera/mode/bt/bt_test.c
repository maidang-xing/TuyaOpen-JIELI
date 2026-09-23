#include "classic/hci_lmp.h"
#include "btstack/btstack_task.h"
#include "btstack/avctp_user.h"
#include "btcontroller_mode.h"
#include "bluetooth.h"
#include "hci_transport.h"
#include "btctrler_task.h"
#include "system/timer.h"
#include "app_power_manage.h"
#include "asm/hwi.h"
#include "event/bt_event.h"
#include "audio_config.h"
#include "app_config.h"
#include "app_msg.h"


/*----------------------------------------------------------------------------*/
/**@brief    蓝牙快速测试
   @param
   @return
   @note     样机和蓝牙测试盒链接开启快速测试，开启mic扩音功能，
   			 按键就播放按键音来检测硬件是否焊接正常
*/
/*----------------------------------------------------------------------------*/
static void bt_fast_test_api(void)
{
    /*
     * 进入快速测试模式，用户根据此标志判断测试，
     * 如测试按键-开按键音  、测试mic-开扩音 、
     * 根据fast_test_mode根据改变led闪烁方式、关闭可发现可连接
     */
    log_info("------------bt_fast_test_api---------");

    if (__this->fast_test_mode == 0) {
        __this->fast_test_mode = 1;
        audio_fast_mode_test();
    }
}

/*----------------------------------------------------------------------------*/
/**@brief    蓝牙模式样机被测试仪链接上的回调函数，把其他状态关闭
   @param
   @return
   @note
*/
/*----------------------------------------------------------------------------*/
static void bt_dut_api(u8 param)
{
    log_info("bt in dut");

    sys_power_auto_shutdown_stop();

#if TCFG_USER_TWS_ENABLE
    tws_cancle_all_noconn();
#endif

    if (__this->auto_connection_timer) {
        sys_timeout_del(__this->auto_connection_timer);
        __this->auto_connection_timer = 0;
    }

#if TCFG_BT_BLE_ADV_ENABLE
#if (TCFG_BT_MODE == BT_NORMAL)
    bt_ble_adv_enable(0);
#endif
#endif
}

/*----------------------------------------------------------------------------*/
/**@brief    蓝牙模式进入定频状态
   @param
   @return
   @note     量产的时候可以通过按键等来触发进入定频状态，这时候蓝牙会在一个通道里
   			 发送信号,可以通过设置下面变量来设置定频的频点
		  	const int config_bredr_fcc_fix_fre = 0;
*/
/*----------------------------------------------------------------------------*/
void bt_fix_fre_api(u8 fre)
{
    bt_dut_api(0);

    bit_clr_ie(IRQ_BREDR_IDX, 0);
    bit_clr_ie(IRQ_BT_CLKN_IDX, 0);

    bredr_fcc_init(BT_FRE, fre);
}

/*----------------------------------------------------------------------------*/
/**@brief    蓝牙模式进入定频测试接收发射
   @param      mode ：0 测试发射    1：测试接收
   			  mac_addr:测试设置的地址
			  fre：定频的频点   0=2402  1=2403
			  packet_type：数据包类型

				#define DH1_1        0
				#define DH3_1        1
				#define DH5_1        2
				#define DH1_2        3
				#define DH3_2        4
				#define DH5_2        5

			  payload：数据包内容  0x0000  0x0055 0x00aa 0x00ff
						0xffff:prbs9
			 payload_len：数据包长度，不可以超过包类型最大长度，0：底层按照最大包发送
			 pwr： 发送功率
   @return
   @note     量产的时候通过串口，发送设置的参数，设置发送接收的参数

   关闭定频接收发射测试
	void link_fix_txrx_disable();

	更新接收结果
	void bt_updata_fix_rx_result()

struct link_fix_rx_result {
    u32 rx_err_b;  //接收到err bit
    u32 rx_sum_b;  //接收到正确bit
    u32 rx_perr_p;  //接收到crc 错误 包数
    u32 rx_herr_p;  //接收到crc 以外其他错误包数
    u32 rx_invail_p; //接收到crc错误bit太多的包数，丢弃不统计到err bit中
};*/
/*----------------------------------------------------------------------------*/
void bt_fix_txrx_api(u8 mode, u8 *mac_addr, u8 fre, u8 packet_type, u16 payload)
{
    bt_dut_api(0);
    local_irq_disable();
    link_fix_txrx_disable();
    if (mode) {
        link_fix_rx_enable(mac_addr, fre, packet_type, 0xffff, 0, 9);
    } else {
        link_fix_tx_enable(mac_addr, fre, packet_type, 0xffff, 0, 9);
    }
    local_irq_enable();
}

/*----------------------------------------------------------------------------*/
/**@brief  蓝牙event   退出dut模式
   @param
   @return
   @note
*/
/*----------------------------------------------------------------------------*/
void bt_bredr_exit_dut_mode(void)
{
    bredr_set_dut_enble(0, 1);
}

static void *ble_dut_hdl;

static const hci_transport_config_uart_t config = {
    HCI_TRANSPORT_CONFIG_UART,
    115200,
    0,  // main baudrate
    0,  // flow control
    NULL,
};

extern void ll_hci_destory(void);
extern void dut_hci_controller_init(const hci_transport_t *transport, const void *config);

static void ble_dut_mode_init(void)
{
    if (!ble_dut_hdl) {
        ll_hci_destory();
        ble_dut_hdl = __ble_dut_ops->init();
    }
}

static void ble_dut_mode_exit(void)
{
    if (ble_dut_hdl) {
        __ble_dut_ops->exit(ble_dut_hdl);
        ble_dut_hdl = NULL;
    }
}

static int ble_dut_test_end(void)
{
    int pkt_valid_cnt = 0;
    int pkt_err_cnt = 0;

    if (ble_dut_hdl) {
        __ble_dut_ops->ioctrl(BLE_DUT_SET_TEST_END, &pkt_valid_cnt, NULL);

        log_info("pkt_rx_cnt:%d pkt_err_cnt:%d", pkt_valid_cnt, pkt_err_cnt);
    } else {
        log_error("ble dut hdl not inited");
    }

    return pkt_valid_cnt;
}

void ble_standard_dut_test_init(void)
{
    ble_dut_mode_init();
    //ble_bqb_test_thread_init();
    dut_hci_controller_init((void *)hci_transport_uart_instance(), &config);
}

void ble_standard_dut_test_close(void)
{
    ble_dut_test_end();
    ble_dut_mode_exit();
    const hci_transport_t *p_uart_trans = hci_transport_uart_instance();
    p_uart_trans->close();
}


enum {
    TEST_STATE_INIT = 1,
    TEST_STATE_EXIT = 3,
};

enum {
    ITEM_KEY_STATE_DETECT = 0,
    ITEM_IN_EAR_DETECT,
};

static u8 in_ear_detect_test_flag = 0;

static void testbox_in_ear_detect_test_flag_set(u8 flag)
{
    in_ear_detect_test_flag = flag;
}

u8 testbox_in_ear_detect_test_flag_get(void)
{
    return in_ear_detect_test_flag;
}

static void bt_in_ear_detection_test_state_handle(u8 state, u8 *value)
{
    switch (state) {
    case TEST_STATE_INIT:
        testbox_in_ear_detect_test_flag_set(1);
        //start trim
        break;
    case TEST_STATE_EXIT:
        testbox_in_ear_detect_test_flag_set(0);
        break;
    }
}

static void bt_vendor_meta_event_handle(u8 sub_evt, u8 *arg, u8 len)
{
    log_info("vendor event:%x", sub_evt);
    log_info_hexdump(arg, 6);

    if (sub_evt != HCI_SUBEVENT_VENDOR_TEST_MODE_CFG) {
        log_info("unknow_sub_evt:%x", sub_evt);
        return;
    }

    u8 test_item = arg[0];
    u8 state = arg[1];

    if (ITEM_IN_EAR_DETECT == test_item) {
        bt_in_ear_detection_test_state_handle(state, NULL);
    }
}

static int bt_hci_test_event_handler(void *evt)
{
    struct bt_event *event = (struct bt_event *)evt;

    switch (event->event) {
    case HCI_EVENT_VENDOR_REMOTE_TEST:
        if (event->value == VENDOR_TEST_DISCONNECTED) {
            bt_set_remote_test_flag(0);
            log_info("clear_test_box_flag");
            /* cpu_reset(); */
        } else {
#if TCFG_BT_BLE_ADV_ENABLE
#if (TCFG_BT_MODE == BT_NORMAL)
            //1:edr con;2:ble con;
            if (VENDOR_TEST_LEGACY_CONNECTED_BY_BT_CLASSIC == event->value) {
                bt_ble_adv_enable(0);
            }
#endif
#endif
#if TCFG_USER_TWS_ENABLE
            if (VENDOR_TEST_CONNECTED_WITH_TWS != event->value) {
                bt_tws_poweroff();
            }
#endif
        }
        break;
    case HCI_EVENT_VENDOR_META:
        bt_vendor_meta_event_handle(event->value, event->args, 6);
        break;
    }

    return FALSE;
}

REGISTER_APP_EVENT_HANDLER(bt_hci_test_event) = {
    .event      = SYS_BT_EVENT,
    .from       = BT_EVENT_FROM_HCI,
    .handler    = bt_hci_test_event_handler,
};

