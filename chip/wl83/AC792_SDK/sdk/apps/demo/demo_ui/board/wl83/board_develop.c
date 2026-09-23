#include "app_config.h"
#include "system/includes.h"
#include "device/includes.h"
#include "device/iic.h"
#include "device/uart.h"
#include "device/gpio.h"
#include "asm/includes.h"
#include "asm/exti.h"
#ifdef CONFIG_UI_ENABLE
#include "lcd_driver.h"
#include "device/video/fb.h"
#include "tp_driver.h"
#endif
#ifdef CONFIG_EXFLASH_ENABLE
#include "fs/virfat_flash.h"
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

#if TCFG_UART2_ENABLE
UART2_PLATFORM_DATA_BEGIN(uart2_data)
    .flow_ctl_enable        = TCFG_UART2_FLOW_CTL_ENABLE,
    .rts_hw_enable          = TCFG_UART2_RTS_HW_ENABLE,
    .baudrate               = TCFG_UART2_BAUDRATE,
    .tx_pin                 = TCFG_UART2_TX_IO,
    .rx_pin                 = TCFG_UART2_RX_IO,
    .rts_pin                = TCFG_UART2_RTS_IO,
    .cts_pin                = TCFG_UART2_CTS_IO,
    .rts_idle_level         = TCFG_UART2_RTS_IDLE_LEVEL,
    .cts_idle_level         = TCFG_UART2_CTS_IDLE_LEVEL,
    .rx_thresh              = TCFG_UART2_RTS_RX_THRESH,
    .max_continue_recv_cnt  = TCFG_UART2_MAX_CONTINUE_RECV_CNT,
    .idle_sys_clk_cnt       = 500000,
    .parity                 = TCFG_UART2_PARITY,
UART2_PLATFORM_DATA_END();
#endif

#if TCFG_UART3_ENABLE
UART3_PLATFORM_DATA_BEGIN(uart3_data)
    .baudrate               = TCFG_UART3_BAUDRATE,
    .tx_pin                 = TCFG_UART3_TX_IO,
    .rx_pin                 = TCFG_UART3_RX_IO,
    .max_continue_recv_cnt  = 1024,
    .idle_sys_clk_cnt       = 500000,
    .parity                 = TCFG_UART3_PARITY,
UART3_PLATFORM_DATA_END();
#endif

#if TCFG_UART4_ENABLE
UART4_PLATFORM_DATA_BEGIN(uart4_data)
    .baudrate               = TCFG_UART4_BAUDRATE,
    .tx_pin                 = TCFG_UART4_TX_IO,
    .rx_pin                 = TCFG_UART4_RX_IO,
    .max_continue_recv_cnt  = 1024,
    .idle_sys_clk_cnt       = 500000,
    .parity                 = TCFG_UART4_PARITY,
UART4_PLATFORM_DATA_END();
#endif


#if TCFG_SD0_ENABLE
SD0_PLATFORM_DATA_BEGIN(sd0_data)
    .port                   = TCFG_SD0_PORTS,
    .port_group             = TCFG_SD0_PORTS_GROUP,
    .priority               = 2,
    .data_width             = TCFG_SD0_DAT_WIDTH,
    .speed                  = TCFG_SD0_CLK,
    .detect_mode            = TCFG_SD0_DET_MODE,
#if (TCFG_SD0_DET_MODE == SD_CLK_DECT)
    .detect_func            = sdmmc_clk_detect,
#elif (TCFG_SD0_DET_MODE == SD_IO_DECT)
    .detect_func            = sdmmc_io_detect,
    .detect_io              = TCFG_SD0_DET_IO,
    .detect_io_level        = TCFG_SD0_DET_IO_LEVEL,
#else
    .detect_func            = NULL,
#endif
    .hd_level               = TCFG_SD0_HD_LEVEL,
#if TCFG_SD0_POWER_ENABLE
    .power                  = sd_set_power,
#endif
SD0_PLATFORM_DATA_END()
#endif

#if TCFG_SD1_ENABLE
SD1_PLATFORM_DATA_BEGIN(sd1_data)
    .port                   = TCFG_SD1_PORTS,
    .port_group             = TCFG_SD1_PORTS_GROUP,
    .priority               = 2,
    .data_width             = TCFG_SD1_DAT_WIDTH,
    .speed                  = TCFG_SD1_CLK,
    .detect_mode            = TCFG_SD1_DET_MODE,
#if (TCFG_SD1_DET_MODE == SD_CLK_DECT)
    .detect_func            = sdmmc_clk_detect,
#elif (TCFG_SD1_DET_MODE == SD_IO_DECT)
    .detect_func            = sdmmc_io_detect,
    .detect_io              = TCFG_SD1_DET_IO,
    .detect_io_level        = TCFG_SD1_DET_IO_LEVEL,
#else
    .detect_func            = NULL,
#endif
    .hd_level               = TCFG_SD1_HD_LEVEL,
#if TCFG_SD1_POWER_ENABLE
    .power                  = sd_set_power,
#endif
SD1_PLATFORM_DATA_END()
#endif


#if TCFG_HW_IIC0_ENABLE
HW_IIC0_PLATFORM_DATA_BEGIN(hw_iic0_data)
#if TCFG_HW_IIC0_ROLE == IIC_ROLE_MASTER
    .role                   = IIC_ROLE_MASTER,
    .hd_level               = TCFG_HW_IIC0_HD_LEVEL,
    .clk_pin                = TCFG_HW_IIC0_SCL_IO,
    .dat_pin                = TCFG_HW_IIC0_SDA_IO,
    .io_filter              = 2,
    .internal_pull_up_enable= 1,
    .fast_resp              = 0,
    .ie_enable              = TCFG_HW_IIC0_IRQ_ENABLE,
    .baudrate               = TCFG_HW_IIC0_BAUDRATE,
    .timeout_cnt            = 40,
#else
    .role                   = IIC_ROLE_SLAVE,
    .hd_level               = TCFG_HW_IIC0_HD_LEVEL,
    .clk_pin                = TCFG_HW_IIC0_SCL_IO,
    .dat_pin                = TCFG_HW_IIC0_SDA_IO,
    .io_filter              = 2,
    .internal_pull_up_enable= 1,
    .fast_resp              = 0,
    .slave_addr             = TCFG_HW_IIC0_SLAVE_ADDR,
    .ie_enable              = TCFG_HW_IIC0_IRQ_ENABLE,
    .adv_enable             = 0,
    .stretch_disable        = TCFG_HW_IIC0_STRETCH_DISABLE,
    .baudrate               = TCFG_HW_IIC0_BAUDRATE,
    .timeout_cnt            = 40,
#endif
HW_IIC0_PLATFORM_DATA_END()
#endif

#if TCFG_HW_IIC1_ENABLE
HW_IIC1_PLATFORM_DATA_BEGIN(hw_iic1_data)
    .role                   = IIC_ROLE_MASTER,
    .hd_level               = TCFG_HW_IIC1_HD_LEVEL,
    .clk_pin                = TCFG_HW_IIC1_SCL_IO,
    .dat_pin                = TCFG_HW_IIC1_SDA_IO,
    .internal_pull_up_enable= 1,
    .ie_enable              = TCFG_HW_IIC1_IRQ_ENABLE,
    .baudrate               = TCFG_HW_IIC1_BAUDRATE,
    .timeout_cnt            = 40,
HW_IIC1_PLATFORM_DATA_END()
#endif

#if TCFG_HW_IIC2_ENABLE
HW_IIC2_PLATFORM_DATA_BEGIN(hw_iic2_data)
    .role                   = IIC_ROLE_MASTER,
    .hd_level               = TCFG_HW_IIC2_HD_LEVEL,
    .clk_pin                = TCFG_HW_IIC2_SCL_IO,
    .dat_pin                = TCFG_HW_IIC2_SDA_IO,
    .internal_pull_up_enable= 1,
    .ie_enable              = TCFG_HW_IIC2_IRQ_ENABLE,
    .baudrate               = TCFG_HW_IIC2_BAUDRATE,
    .timeout_cnt            = 40,
HW_IIC2_PLATFORM_DATA_END()
#endif

#if TCFG_SW_IIC0_ENABLE
SW_IIC_PLATFORM_DATA_BEGIN(sw_iic0_data)
    .clk_pin                = TCFG_SW_IIC0_SCL_IO,
    .dat_pin                = TCFG_SW_IIC0_SDA_IO,
    .sw_iic_delay           = TCFG_SW_IIC0_IO_LEVEL_DELAY,
    .sw_iic_byte_gap_time   = TCFG_SW_IIC0_BYTE_GAP_TIME,
    .hd_level               = TCFG_SW_IIC0_HD_LEVEL,
SW_IIC_PLATFORM_DATA_END()
#endif

#if TCFG_SW_IIC1_ENABLE
SW_IIC_PLATFORM_DATA_BEGIN(sw_iic1_data)
    .clk_pin                = TCFG_SW_IIC1_SCL_IO,
    .dat_pin                = TCFG_SW_IIC1_SDA_IO,
    .sw_iic_delay           = TCFG_SW_IIC1_IO_LEVEL_DELAY,
    .sw_iic_byte_gap_time   = TCFG_SW_IIC1_BYTE_GAP_TIME,
    .hd_level               = TCFG_SW_IIC1_HD_LEVEL,
SW_IIC_PLATFORM_DATA_END()
#endif


#if TCFG_SPI0_ENABLE
SPI0_PLATFORM_DATA_BEGIN(spi0_data)
    .io = {
        .cs_pin             = TCFG_SPI0_CS_IO,
        .di_pin             = TCFG_SPI0_DI_IO,
        .do_pin             = TCFG_SPI0_DO_IO,
        .clk_pin            = TCFG_SPI0_CLK_IO,
        .d2_pin             = TCFG_SPI0_D2_IO,
        .d3_pin             = TCFG_SPI0_D3_IO,
    },
    .clk                    = TCFG_SPI0_BAUDRATE,
    .mode                   = TCFG_SPI0_MODE,
    .priority               = 5,
    .cpu_id                 = 1,
    .hd_level               = TCFG_SPI0_HD_LEVEL,
    .attr                   = TCFG_SPI0_ATTR,
    .role                   = TCFG_SPI0_ROLE,
SPI0_PLATFORM_DATA_END()
#endif

#if TCFG_SPI1_ENABLE
SPI1_PLATFORM_DATA_BEGIN(spi1_data)
    .io = {
        .cs_pin             = TCFG_SPI1_CS_IO,
        .di_pin             = TCFG_SPI1_DI_IO,
        .do_pin             = TCFG_SPI1_DO_IO,
        .clk_pin            = TCFG_SPI1_CLK_IO,
        .d2_pin             = TCFG_SPI1_D2_IO,
        .d3_pin             = TCFG_SPI1_D3_IO,
    },
    .clk                    = TCFG_SPI1_BAUDRATE,
    .mode                   = TCFG_SPI1_MODE,
    .priority               = 5,
    .cpu_id                 = 1,
    .hd_level               = TCFG_SPI1_HD_LEVEL,
    .attr                   = TCFG_SPI1_ATTR,
    .role                   = TCFG_SPI1_ROLE,
SPI1_PLATFORM_DATA_END()
#endif

#if TCFG_SPI2_ENABLE
SPI2_PLATFORM_DATA_BEGIN(spi2_data)
    .io = {
        .cs_pin             = TCFG_SPI2_CS_IO,
        .di_pin             = TCFG_SPI2_DI_IO,
        .do_pin             = TCFG_SPI2_DO_IO,
        .clk_pin            = TCFG_SPI2_CLK_IO,
        .d2_pin             = -1,
        .d3_pin             = -1,
    },
    .clk                    = TCFG_SPI2_BAUDRATE,
    .mode                   = TCFG_SPI2_MODE,
    .priority               = 5,
    .cpu_id                 = 1,
    .hd_level               = TCFG_SPI2_HD_LEVEL,
    .attr                   = TCFG_SPI2_ATTR,
    .role                   = TCFG_SPI2_ROLE,
SPI2_PLATFORM_DATA_END()
#endif


#if TCFG_NORFLASH_SFC_DEV_ENABLE
SFC_SPI_PLATFORM_DATA_BEGIN(sfc_spi_data)
    .sfc_read_mode          = TCFG_NORFLASH_SFC_READ_MODE,
    .sfc_data_width         = TCFG_NORFLASH_SFC_DATA_WIDTH,
    .sfc_encry              = TCFG_NORFLASH_SFC_ENCRYPTION,
    .sfc_clk_div            = TCFG_NORFLASH_SFC_CLK_DIV,
    .spi_clk_div            = TCFG_NORFLASH_SPI_CLK_DIV,
    .sfc_clk_sel            = TCFG_NORFLASH_SFC_CLK_SRC,
    .unencry_start_addr     = TCFG_NORFLASH_SFC_UNENC_START_ADDR,
    .unencry_size           = TCFG_NORFLASH_SFC_UNENC_START_SIZE,
SFC_SPI_PLATFORM_DATA_END()

NORFLASH_SFC_DEV_PLATFORM_DATA_BEGIN(norflash_sfc_dev_data)
    .sfc_spi_pdata          = &sfc_spi_data,
    .start_addr             = 0,
    .size                   = __EXTERN_FLASH_SIZE__,
NORFLASH_SFC_DEV_PLATFORM_DATA_END()
#endif


#if TCFG_PAP_ENABLE
PAP_PLATFORM_DATA_BEGIN(pap_data)
    .datawidth              = TCFG_PAP_DATA_WIDTH,
    .endian                 = TCFG_PAP_DATA_ENDIAN,
    .pwe                    = TCFG_PAP_WRITE_ACTIVE_LEVEL,
    .pre                    = TCFG_PAP_READ_ACTIVE_LEVEL,
    .rd_en                  = TCFG_PAP_READ_ENABLE,
    .we_port                = TCFG_PAP_WE_IO,
    .re_port                = TCFG_PAP_RE_IO,
    .port_sel               = PAP_PORT_A,
    .timing_setup           = PAP_TS_0_CLK,
    .timing_hold            = PAP_TH_0_CLK,
    .timing_width           = PAP_TW_3_CLK,
PAP_PLATFORM_DATA_END();
#endif


#if TCFG_LCD_ENABLE
LCD_PLATFORM_DATA_BEGIN(lcd_bd_cfg)
    .lcd_name               = TCFG_LCD_DEVICE_NAME,
    .lcd_io                 = {
        .backlight          = TCFG_LCD_BL_IO,
        .backlight_value    = TCFG_LCD_BL_VALUE,
        .lcd_reset          = TCFG_LCD_RESET_IO,
        .lcd_cs             = TCFG_LCD_CS_IO,
        .lcd_rs             = TCFG_LCD_RS_IO,
    },
    .te_mode                = {
        .te_mode_en         = TCFG_LCD_TE_ENABLE,
        .gpio               = TCFG_LCD_TE_IO,
        .edge               = EDGE_NEGATIVE,
    },
    .spi_lcd_interface      = TCFG_LCD_SPI_INTERFACE,
#if TCFG_LCD_SUPPORT_MULTI_DRIVER_EN
LCD_PLATFORM_DATA_ADD()
    .lcd_name               = TCFG_LCD1_DEVICE_NAME,
    .lcd_io                 = {
        .backlight          = TCFG_LCD1_BL_IO,
        .backlight_value    = TCFG_LCD1_BL_VALUE,
        .lcd_reset          = TCFG_LCD1_RESET_IO,
        .lcd_cs             = TCFG_LCD1_CS_IO,
        .lcd_rs             = TCFG_LCD1_RS_IO,
    },
    .te_mode                = {
        .te_mode_en         = TCFG_LCD1_TE_ENABLE,
        .gpio               = TCFG_LCD1_TE_IO,
        .edge               = EDGE_NEGATIVE,
    },
    .spi_lcd_interface      = TCFG_LCD1_SPI_INTERFACE,
#endif
LCD_PLATFORM_DATA_END()

static const struct lcd_platform_data lcd_data = {
    .cfg_num = ARRAY_SIZE(lcd_bd_cfg),
    .config_ptr = lcd_bd_cfg,
};
#endif


#if TCFG_TP_DRIVER_ENABLE
TP_PLATFORM_DATA_BEGIN(tp_data)
    .interface              = TCFG_TP_COMMUNICATE_IF,
    .int_pin                = TCFG_TP_INT_PIN,
    .rst_pin                = TCFG_TP_RST_PIN,
    .x_mirror               = TCFG_TP_X_MIRROR,
    .y_mirror               = TCFG_TP_Y_MIRROR,
    .swap_x_y               = TCFG_TP_SWAP_X_Y,
TP_PLATFORM_DATA_END()

const tp_platform_data_t *tp_get_platform_data(void)
{
    return &tp_data;
}
#endif


REGISTER_DEVICES(device_table) = {
#if TCFG_PAP_ENABLE
    { "pap", &pap_dev_ops, (void *)&pap_data }, ///< MCU屏使用了pap，pap设备需要放在lcd前面注册
#endif
#if TCFG_SPI2_ENABLE
    { "spi2", &spi_dev_ops, (void *)&spi2_data }, ///< SPI屏使用了spi2，spi2设备需要放在lcd前面注册
#endif
#if TCFG_LCD_ENABLE
    { "lcd",   &lcd_dev_ops, (void*)&lcd_data },
    { "fb0",   &fb_dev_ops, NULL },
    { "fb1",   &fb_dev_ops, NULL },
    { "fb2",   &fb_dev_ops, NULL },
    { "fb_out",  &fb_out_dev_ops, NULL },
#endif

#if TCFG_HW_IIC0_ENABLE
    { "iic0", &iic_dev_ops, (void *)&hw_iic0_data },
#endif
#if TCFG_HW_IIC1_ENABLE
    { "iic1", &iic_dev_ops, (void *)&hw_iic1_data },
#endif
#if TCFG_HW_IIC2_ENABLE
    { "iic2", &iic_dev_ops, (void *)&hw_iic2_data },
#endif
#if TCFG_SW_IIC0_ENABLE
    { "iic3", &iic_dev_ops, (void *)&sw_iic0_data },
#endif
#if TCFG_SW_IIC1_ENABLE
    { "iic4", &iic_dev_ops, (void *)&sw_iic1_data },
#endif

#if TCFG_SD0_ENABLE
    { "sd0", &sd_dev_ops, (void *)&sd0_data },
#endif
#if TCFG_SD1_ENABLE
    { "sd1", &sd_dev_ops, (void *)&sd1_data },
#endif

#if TCFG_SPI0_ENABLE
    { "spi0", &spi_dev_ops, (void *)&spi0_data },
#endif
#if TCFG_SPI1_ENABLE
    { "spi1", &spi_dev_ops, (void *)&spi1_data },
#endif

#if TCFG_UART0_ENABLE
    { "uart0", &uart_dev_ops, (void *)&uart0_data },
#endif
#if TCFG_UART1_ENABLE
    { "uart1", &uart_dev_ops, (void *)&uart1_data },
#endif
#if TCFG_UART2_ENABLE
    { "uart2", &uart_dev_ops, (void *)&uart2_data },
#endif
#if TCFG_UART3_ENABLE
    { "uart3", &uart_dev_ops, (void *)&uart3_data },
#endif
#if TCFG_UART4_ENABLE
    { "uart4", &uart_dev_ops, (void *)&uart4_data },
#endif

#if TCFG_NORFLASH_SFC_DEV_ENABLE
#if defined CONFIG_EXFLASH_ENABLE
    { "res_nor", &norflash_sfc_fs_dev_ops, (void *)&norflash_sfc_dev_data },
    { "virfat_flash", &virfat_flash_dev_ops, (void *)"res_nor" },
#else
    { "fat_nor", &norflash_sfc_dev_ops, (void *)&norflash_sfc_dev_data },
#endif
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
#if TCFG_LOWPOWER_WAKEUP_PORT1_ENABLE
    PORT_PROTECT(TCFG_LOWPOWER_WAKEUP_PORT1_IO);
#endif
#if TCFG_LOWPOWER_WAKEUP_PORT2_ENABLE
    PORT_PROTECT(TCFG_LOWPOWER_WAKEUP_PORT2_IO);
#endif

    __port_init((u32)gpio_config);
}

u8 power_soff_callback(void)
{
    printf("++++++++%s--------", __FUNCTION__);

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

}
