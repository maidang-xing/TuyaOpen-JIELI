#include "app_config.h"
#include "system/includes.h"
#include "device/includes.h"
#include "asm/includes.h"
#include "device/uart.h"


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


#if TCFG_ADKEY_ENABLE
#define ADC_VDDIO   (0x3FF)

#define ADKEY_V_9   ((TCFG_ADC_LEVEL_09 + ADC_VDDIO) / 2)
#define ADKEY_V_8   ((TCFG_ADC_LEVEL_08 + TCFG_ADC_LEVEL_09) / 2)
#define ADKEY_V_7   ((TCFG_ADC_LEVEL_07 + TCFG_ADC_LEVEL_08) / 2)
#define ADKEY_V_6   ((TCFG_ADC_LEVEL_06 + TCFG_ADC_LEVEL_07) / 2)
#define ADKEY_V_5   ((TCFG_ADC_LEVEL_05 + TCFG_ADC_LEVEL_06) / 2)
#define ADKEY_V_4   ((TCFG_ADC_LEVEL_04 + TCFG_ADC_LEVEL_05) / 2)
#define ADKEY_V_3   ((TCFG_ADC_LEVEL_03 + TCFG_ADC_LEVEL_04) / 2)
#define ADKEY_V_2   ((TCFG_ADC_LEVEL_02 + TCFG_ADC_LEVEL_03) / 2)
#define ADKEY_V_1   ((TCFG_ADC_LEVEL_01 + TCFG_ADC_LEVEL_02) / 2)
#define ADKEY_V_0   ((TCFG_ADC_LEVEL_00 + TCFG_ADC_LEVEL_01) / 2)

static const struct adkey_platform_data adkey_data = {
    .adkey_pin              = TCFG_ADKEY_INPUT_IO,
    .extern_up_en           = 1,
    .ad_channel             = TCFG_ADKEY_INPUT_CHANNEL,
    .ad_value               = {
                                ADKEY_V_0,
                                ADKEY_V_1,
                                ADKEY_V_2,
                                ADKEY_V_3,
                                ADKEY_V_4,
                                ADKEY_V_5,
                                ADKEY_V_6,
                                ADKEY_V_7,
                                ADKEY_V_8,
                                ADKEY_V_9,
    },
    .key_value              = {
                                TCFG_ADKEY_VALUE_0,
                                TCFG_ADKEY_VALUE_1,
                                TCFG_ADKEY_VALUE_2,
                                TCFG_ADKEY_VALUE_3,
                                TCFG_ADKEY_VALUE_4,
                                TCFG_ADKEY_VALUE_5,
                                TCFG_ADKEY_VALUE_6,
                                TCFG_ADKEY_VALUE_7,
                                TCFG_ADKEY_VALUE_8,
                                TCFG_ADKEY_VALUE_9,
    },
};

const struct adkey_platform_data *get_adkey_platform_data(void)
{
    return &adkey_data;
}
#endif


#ifdef CONFIG_BT_ENABLE
#include "wifi/wifi_connect.h"
const struct wifi_calibration_param wifi_calibration_param = {
    .xosc_l     = 0x7,// 调节左晶振电容
    .xosc_r     = 0x7,// 调节右晶振电容
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


REGISTER_DEVICES(device_table) = {
#if TCFG_UART0_ENABLE
    { "uart0", &uart_dev_ops, (void *) &uart0_data },
#endif
#if TCFG_UART1_ENABLE
    { "uart1", &uart_dev_ops, (void *) &uart1_data },
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

    adc_suspend();
    /* do_platform_uninitcall(); */

#if TCFG_LOWPOWER_WAKEUP_PORT0_ENABLE
    p33_io_wakeup_port_init(&wakeup_port0);
    p33_io_wakeup_enable(TCFG_LOWPOWER_WAKEUP_PORT0_IO, 1);
#endif

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

    //前面已经初始化过的IO需要在这里加一下对应IO的保护，否则会被覆盖成高阻状态
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

#if TCFG_ADKEY_ENABLE
    key_driver_init();
#endif

#ifdef CONFIG_BT_ENABLE
    void cfg_file_parse(void);
    cfg_file_parse();
#endif
}

