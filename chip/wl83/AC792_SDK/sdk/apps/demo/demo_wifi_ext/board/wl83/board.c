#include "app_config.h"
#include "system/includes.h"
#include "device/includes.h"
#include "asm/includes.h"
#include "device/uart.h"
#if TCFG_USB_SLAVE_ENABLE || TCFG_USB_HOST_ENABLE
#include "otg.h"
#include "usb_host.h"
#include "usb_storage.h"
#endif
#if TCFG_EXT_WIFI_ENABLE
#include "net/wireless_ext/wifi_dev.h"
#endif
#if TCFG_LTE_PHY_ENABLE
#include "lte_module/lte_module.h"
#endif
#if TCFG_ETH_ENABLE
#include "eth/eth_phy.h"
#include "eth/ethmac.h"
#endif


// *INDENT-OFF*

#if TCFG_UART0_ENABLE
UART0_PLATFORM_DATA_BEGIN(uart0_data)
#ifdef CONFIG_DEBUG_ENABLE
    .disable_tx_irq         = 1,
#endif
    .baudrate               = TCFG_UART0_BAUDRATE,
    .tx_pin                 = TCFG_UART0_TX_IO,
    .rx_pin                 = TCFG_UART0_RX_IO,
    .max_continue_recv_cnt  = 1024,
    .idle_sys_clk_cnt       = 500000,
    .flags                  = UART_DEBUG,
    .parity                 = TCFG_UART0_PARITY,
UART0_PLATFORM_DATA_END();
#endif

#if TCFG_UART1_ENABLE
UART1_PLATFORM_DATA_BEGIN(uart1_data)
    .flow_ctl_enable        = TCFG_UART1_FLOW_CTL_ENABLE,
    .rts_hw_enable          = TCFG_UART1_RTS_HW_ENABLE,
    .baudrate               = TCFG_UART1_BAUDRATE,
    .tx_pin                 = TCFG_UART1_TX_IO,
    .rx_pin                 = TCFG_UART1_RX_IO,
    .rts_pin                = TCFG_UART1_RTS_IO,
    .cts_pin                = TCFG_UART1_CTS_IO,
    .rts_idle_level         = TCFG_UART1_RTS_IDLE_LEVEL,
    .cts_idle_level         = TCFG_UART1_CTS_IDLE_LEVEL,
    .rx_thresh              = TCFG_UART1_RTS_RX_THRESH,
    .max_continue_recv_cnt  = TCFG_UART1_MAX_CONTINUE_RECV_CNT,
    .idle_sys_clk_cnt       = 500000,
    .parity                 = TCFG_UART1_PARITY,
UART1_PLATFORM_DATA_END();
#endif


#if TCFG_ETH_ENABLE
NET_PLATFORM_DATA_BEGIN(net_phy_data)
    .name                   = TCFG_ETH_PHY_DEVICE_NAME,
    .speed                  = TCFG_ETH_PHY_SPEED,
    .mode                   = RMII_MODE,
    .irq                    = TCFG_ETH_IRQ_PRIO,
    .hd_mode                = TCFG_ETH_HD_LEVEL,
    .task_prio              = TCFG_ETH_RX_TASK_PRIO,
    .check_link_time        = 100, // 检测网络连接状态时间间隔
    .rmii_bus               = {
        .phy_addr           = 0x1,
        .clk_pin            = TCFG_ETH_RMII_BUS_CLK_IO,
        .dat_pin            = TCFG_ETH_RMII_BUS_DAT_IO,
        .hd_mode            = TCFG_ETH_RMII_BUS_HD_LEVEL,
    },
NET_PLATFORM_DATA_END()
#endif


#if TCFG_WIFI_ENABLE
#include "wifi/wifi_connect.h"
const struct wifi_calibration_param wifi_calibration_param = {
    .xosc_l     = 0xb,// 调节左晶振电容
    .xosc_r     = 0xb,// 调节右晶振电容
    .pa_trim_data = {1, 7, 4, 7, 11, 1, 7},// 根据MP测试生成PA TRIM值
	.mcs_dgain    = {
        50,//11B_1M
        50,//11B_2.2M
        50,//11B_5.5M
        50,//11B_11M

        72,//11G_6M
        72,//11G_9M
        85,//11G_12M
        80,//11G_18M
        64,//11G_24M
        64,//11G_36M
        62,//11G_48M
        52,//11G_54M

        72,//11N_MCS0
        90,//11N_MCS1
        80,//11N_MCS2
        64,//11N_MCS3
        64,//11N_MCS4
        64,//11N_MCS5
        50,//11N_MCS6
        43,//11N_MCS7
    }
};
#endif


#if TCFG_EXT_WIFI_ENABLE
WIFI_PLATFORM_DATA_BEGIN(wifi_data)
#if TCFG_RTL8189E_ENABLE
	.module = RTL8189E,
#elif TCFG_RTL8189F_ENABLE
	.module = RTL8189F,
#elif TCFG_RTL8822ES_10M_ENABLE
	.module = RTL8822E,
#elif TCFG_RTL8822CS_ENABLE
	.module = RTL8822C,
#elif TCFG_RTL8733BS_ENABLE
	.module = RTL8733B,
#elif TCFG_AIC8800_ENABLE
	.module = AIC8800,
#endif
 .sdio_parm = SDIO_GRP_0 | SDIO_PORT_0 | SDIO_4_BIT_DATA | SDIO_POLLING | SDIO_CLOCK_20M,
	.wakeup_port = -1,
	.cs_port = -1,
	.power_port = -1,
WIFI_PLATFORM_DATA_END()
#endif


#if TCFG_LTE_PHY_ENABLE
LTE_MODULE_DATA_BEGIN(lte_module_data)
    .name = (u8 *)"usb_rndis",
LTE_MODULE_DATA_END()
#endif


#if TCFG_USB_SLAVE_ENABLE || TCFG_USB_HOST_ENABLE
static const struct otg_dev_data otg_data = {
    .usb_dev_en             = TCFG_USB_DEVICE,
#if TCFG_USB_SLAVE_ENABLE
    .slave_online_cnt       = 10,
    .slave_offline_cnt      = 10,
#endif
#if TCFG_USB_HOST_ENABLE
    .host_online_cnt        = 10,
    .host_offline_cnt       = 10,
#endif
    .detect_mode            = OTG_CHARGE_MODE
#if TCFG_USB_SLAVE_ENABLE
                            | OTG_SLAVE_MODE
#endif
#if TCFG_USB_HOST_ENABLE
                            | OTG_HOST_MODE
#endif
                              ,
    .detect_time_interval   = 50,
};
#endif


REGISTER_DEVICES(device_table) = {
#if TCFG_UART0_ENABLE
    { "uart0", &uart_dev_ops, (void *) &uart0_data },
#endif
#if TCFG_UART1_ENABLE
    { "uart1", &uart_dev_ops, (void *) &uart1_data },
#endif
#if TCFG_USB_SLAVE_ENABLE || TCFG_USB_HOST_ENABLE
    { "otg", &usb_dev_ops, (void *)&otg_data},
#endif
#if TCFG_EXT_WIFI_ENABLE
    { "wifi",  &wifi_dev_ops, (void *) &wifi_data},
#endif
#if TCFG_LTE_PHY_ENABLE
    { "lte",  &lte_module_dev_ops, (void *)&lte_module_data},
#endif
#if TCFG_ETH_ENABLE
    { "eth", &eth_phy_dev_ops, (void *)&net_phy_data },
#endif
};


static const power_param_t power_param = {
    .config                 = TCFG_LOWPOWER_FUNCTION,
    .btosc_hz               = 24000000,
    .vddiom_lev             = TCFG_LOWPOWER_VDDIOM_LEVEL,
    .vddiow_lev             = TCFG_LOWPOWER_VDDIOW_LEVEL,
    .vdc14_lev              = TCFG_LOWPOWER_VDC14_LEVEL,
    .osc_type               = TCFG_LOWPOWER_OSC_TYPE,
    .osc_delay_us           = 8000,
#if TCFG_POWER_AVDD18_ENABLE
    .avdd18_enable          = 1,
#endif
#if TCFG_POWER_AVDD28_ENABLE
    .avdd28_enable          = 1,
#endif
};

static const power_pdata_t power_pdata = {
    .power_param            = &power_param,
};

#if TCFG_LOWPOWER_WAKEUP_PORT0_ENABLE
static void wakeup_port0_callback_in_irq(p33_io_wkup_edge_t edge)
{

}

static const p33_io_wakeup_config_t wakeup_port0 = {
    .pullup_down_enable     = 1,
    .filter                 = TCFG_LOWPOWER_WAKEUP_PORT0_FILTER,
    .edge                   = TCFG_LOWPOWER_WAKEUP_PORT0_EDGE,
    .gpio                   = TCFG_LOWPOWER_WAKEUP_PORT0_IO,
    .callback               = wakeup_port0_callback_in_irq,
};
#endif

static u32 fusb_io_con = 0;
static u32 husb_io_con = 0;

// 进入、退出低功耗函数回调状态，函数单核操作、关中断，请勿做耗时操作
void sleep_enter_callback(u8 step)
{
    /* 此函数禁止添加打印 */
    putchar('<');

    //USB IO打印引脚特殊处理
#if (defined CONFIG_DEBUG_ENABLE) && ((TCFG_DEBUG_UART_TX_PIN == IO_PORT_USB_DPA) || (TCFG_DEBUG_UART_TX_PIN == IO_PORT_USB_DMA))
    fusb_io_con = JL_PORTFUSB->DIR;
    gpio_close(PORTFUSB, 0xffff);
#endif
#if (defined CONFIG_DEBUG_ENABLE) && ((TCFG_DEBUG_UART_TX_PIN == IO_PORT_USB_DPB) || (TCFG_DEBUG_UART_TX_PIN == IO_PORT_USB_DMB))
    husb_io_con = JL_PORTHUSB->DIR;
    gpio_close(PORTHUSB, 0xffff);
#endif
}

void sleep_exit_callback(u32 usec)
{
    //USB IO打印引脚特殊处理
#if (defined CONFIG_DEBUG_ENABLE) && ((TCFG_DEBUG_UART_TX_PIN == IO_PORT_USB_DPA) || (TCFG_DEBUG_UART_TX_PIN == IO_PORT_USB_DMA))
    JL_PORTFUSB->DIR = fusb_io_con;
#endif
#if (defined CONFIG_DEBUG_ENABLE) && ((TCFG_DEBUG_UART_TX_PIN == IO_PORT_USB_DPB) || (TCFG_DEBUG_UART_TX_PIN == IO_PORT_USB_DMB))
    JL_PORTHUSB->DIR = husb_io_con;
#endif

    putchar('>');
}

//maskrom 使用到的io
static void __mask_io_cfg(void)
{
    struct boot_soft_flag_t g_boot_soft_flag = {0};

    g_boot_soft_flag.flag0.boot_ctrl.wdt_dis                    = 0;
    g_boot_soft_flag.flag0.boot_ctrl.lvd_en                     = 1;
    g_boot_soft_flag.flag0.boot_ctrl.sfc_fast_boot              = 0;
    g_boot_soft_flag.flag0.boot_ctrl.flash_power_keep           = 0;
    g_boot_soft_flag.flag0.boot_ctrl.skip_flash_reset           = 0;
    g_boot_soft_flag.flag0.boot_ctrl.sfc_flash_stable_delay_sel = 0;
    g_boot_soft_flag.flag0.boot_ctrl.flash_stable_delay_sel     = 0;    //0: 0mS;   1: 4mS

    g_boot_soft_flag.flag1.boot_ctrl.fusbdp                      = 0;
    g_boot_soft_flag.flag1.boot_ctrl.fusbdm                      = 0;

    g_boot_soft_flag.flag3.boot_ctrl.husbdp                      = 0;
    g_boot_soft_flag.flag3.boot_ctrl.husbdm                      = 0;

    mask_softflag_config(&g_boot_soft_flag);
}

static void gpio_config_soft_poweroff(void)
{
    PORT_TABLE(g);

#if TCFG_LOWPOWER_WAKEUP_PORT0_ENABLE
    PORT_PROTECT(TCFG_LOWPOWER_WAKEUP_PORT0_IO);
#endif

    __port_init((u32)gpio_config);
}

u8 power_soff_callback(void)
{
    printf("++++++++%s--------", __FUNCTION__);

    /* do_platform_uninitcall(); */

    __mask_io_cfg();

    gpio_config_soft_poweroff();

    /* gpio_config_uninit(); */

    return 0;
}

void power_early_flowing(void)
{
    PORT_TABLE(g);

    // 默认关闭长按复位0，由key_driver配置
    gpio_longpress_pin0_reset_config(IO_PORTD_01, 0, 0, 1, 1);

#if (defined CONFIG_DEBUG_ENABLE) && (TCFG_DEBUG_PORT != -1)
    PORT_PROTECT(TCFG_DEBUG_PORT);
#endif

    power_early_init((u32)gpio_config);

    power_set_mode(TCFG_POWER_MODE);
}

static void board_power_init(void)
{
    /* gpio_config_init(); */

    power_control(PCONTROL_PD_VDDIO_KEEP, VDDIO_KEEP_TYPE_NORMAL);
    power_control(PCONTROL_SF_VDDIO_KEEP, VDDIO_KEEP_TYPE_NORMAL);

    power_init(&power_pdata);

#if TCFG_LOWPOWER_WAKEUP_PORT0_ENABLE
    p33_io_wakeup_port_init(&wakeup_port0);
    p33_io_wakeup_enable(TCFG_LOWPOWER_WAKEUP_PORT0_IO, 1);
#endif
}


#ifdef CONFIG_DEBUG_ENABLE
void debug_uart_init(void)
{
#if TCFG_UART0_ENABLE
    uart_init(&uart0_data);
#endif
}
#endif

void board_early_init(void)
{
    board_power_init();

    devices_init();
}

void board_init(void)
{
    adc_init();
}

