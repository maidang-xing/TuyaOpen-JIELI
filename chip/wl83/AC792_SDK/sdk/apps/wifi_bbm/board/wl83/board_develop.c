#include "app_config.h"

#ifdef CONFIG_BOARD_DEVELOP

#include "app_power_manage.h"
#include "system/includes.h"
#include "device/includes.h"
#include "device/iic.h"
#include "device/uart.h"
#include "device/gpio.h"
#include "server/audio_dev.h"
#include "asm/includes.h"
#include "asm/exti.h"
#if TCFG_USB_SLAVE_ENABLE || TCFG_USB_HOST_ENABLE
#include "otg.h"
#include "usb_host.h"
#include "usb_storage.h"
#include "usb_host_cdc.h"
#include "asm/uvc_device.h"
#endif
#if TCFG_ETH_ENABLE
#include "eth/eth_phy.h"
#include "eth/ethmac.h"
#endif
#ifdef CONFIG_UI_ENABLE
#include "lcd_driver.h"
#include "device/video/fb.h"
#include "tp_driver.h"
#endif
#ifdef CONFIG_EXFLASH_ENABLE
#include "fs/virfat_flash.h"
#endif
#ifdef CONFIG_VIDEO_ENABLE
#include "device/video/video.h"
#include "asm/isc.h"
#include "video_engine.h"
#endif
#if TCFG_GSENSOR_ENABLE
#include "gSensor_manage.h"
#endif
#if TCFG_EXT_WIFI_ENABLE
#include "net/wireless_ext/wifi_dev.h"
#endif

#ifdef CONFIG_LTE_PHY_ENABLE
#include "lte_module.h"
#endif

#if TCFG_EXT_WIFI_ENABLE
WIFI_PLATFORM_DATA_BEGIN(wifi_data)
#if TCFG_RTL8189E_ENABLE
.module = RTL8189E,
#elif TCFG_RTL8822ES_10M_ENABLE
.module = RTL8822E,
#elif TCFG_RTL8822CS_ENABLE
.module = RTL8822C,
#elif TCFG_RTL8733BS_ENABLE
.module = RTL8733B,
#endif
 .sdio_parm = SDIO_GRP_1 | SDIO_PORT_1 | SDIO_4_BIT_DATA | SDIO_POLLING | SDIO_CLOCK_20M,
  .wakeup_port = -1,
   .cs_port = -1,
    .power_port = -1,
     WIFI_PLATFORM_DATA_END()
#endif

// *INDENT-OFF*

#if TCFG_UART0_ENABLE
UART0_PLATFORM_DATA_BEGIN(uart0_data)
#ifdef CONFIG_DEBUG_ENABLE
    .disable_tx_irq         = 1,
#endif
#if TCFG_UART_KEY_ENABLE
    .disable_rx_irq         = 1,
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

#if TCFG_SW_IIC2_ENABLE
SW_IIC_PLATFORM_DATA_BEGIN(sw_iic2_data)
    .clk_pin                = TCFG_SW_IIC2_SCL_IO,
    .dat_pin                = TCFG_SW_IIC2_SDA_IO,
    .sw_iic_delay           = TCFG_SW_IIC2_IO_LEVEL_DELAY,
    .sw_iic_byte_gap_time   = TCFG_SW_IIC2_BYTE_GAP_TIME,
    .hd_level               = TCFG_SW_IIC2_HD_LEVEL,
SW_IIC_PLATFORM_DATA_END()
#endif


#if TCFG_CAN_ENABLE
CAN_PLATFORM_DATA_BEGIN(can_data)
    .can_mode               = TCFG_CAN_MODE,
    .rx_pin                 = TCFG_CAN_RX_IO,
    .tx_pin                 = TCFG_CAN_TX_IO,
    .stm                    = TCFG_CAN_STM_ENABLE,
    .lom                    = TCFG_CAN_LOM_ENABLE,
    .baudrate = {
       .brp                 = TCFG_CAN_BAUD_BRP,
       .sjw                 = TCFG_CAN_BAUD_SJW,
       .sam                 = TCFG_CAN_BAUD_SAM,
       .tseg2               = TCFG_CAN_BAUD_PBS2,
       .tseg1               = TCFG_CAN_BAUD_PTS_PBS1,
    },
    .filter = {
        .filter_mode        = TCFG_CAN_FILTER_MODE,
#if TCFG_CAN_MODE
        .accept_id0         = TCFG_CAN_FILTER_ACC_ID0,
        .accept_id1         = TCFG_CAN_FILTER_ACC_ID1,
        .accept_rtr0        = TCFG_CAN_FILTER_ACC_RTR0,
        .accept_rtr1        = TCFG_CAN_FILTER_ACC_RTR1,
        .mask_id0           = TCFG_CAN_FILTER_MASK_ID0,
        .mask_id1           = TCFG_CAN_FILTER_MASK_ID1,
        .mask_rtr0          = TCFG_CAN_FILTER_MASK_RTR0,
        .mask_rtr1          = TCFG_CAN_FILTER_MASK_RTR1,
#else
        .accept_id0         = TCFG_CAN_FILTER_ACC_ID0,
        .mask_id0           = TCFG_CAN_FILTER_MASK_ID0,
#endif
	},
    .priority               = 5,
    .cpu_id                 = 0,
CAN_PLATFORM_DATA_END()
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
    .priority               = 6,
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
    .priority               = 6,
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
    .priority               = 6,
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

#if TCFG_LEDC0_ENABLE
LEDC0_PLATFORM_DATA_BEGIN(ledc0_data)
    .port                   = TCFG_LEDC0_PORT,
    .idle_level             = TCFG_LEDC0_IDLE_LEVEL,
    .out_inv                = TCFG_LEDC0_OUT_INV,
    .bit_inv                = TCFG_LEDC0_BIT_INV,
    .time_base              = TCFG_LEDC0_TIME_BASE,
    .t1h_cnt                = TCFG_LEDC0_T1H_CNT,
    .t1l_cnt                = TCFG_LEDC0_T1L_CNT,
    .t0h_cnt                = TCFG_LEDC0_T0H_CNT,
    .t0l_cnt                = TCFG_LEDC0_T0L_CNT,
    .rst_time_cnt           = TCFG_LEDC0_RST_TIME_CNT,
LEDC0_PLATFORM_DATA_END()
#endif

#if TCFG_LEDC1_ENABLE
LEDC1_PLATFORM_DATA_BEGIN(ledc1_data)
    .port                   = TCFG_LEDC1_PORT,
    .idle_level             = TCFG_LEDC1_IDLE_LEVEL,
    .out_inv                = TCFG_LEDC1_OUT_INV,
    .bit_inv                = TCFG_LEDC1_BIT_INV,
    .time_base              = TCFG_LEDC1_TIME_BASE,
    .t1h_cnt                = TCFG_LEDC1_T1H_CNT,
    .t1l_cnt                = TCFG_LEDC1_T1L_CNT,
    .t0h_cnt                = TCFG_LEDC1_T0H_CNT,
    .t0l_cnt                = TCFG_LEDC1_T0L_CNT,
    .rst_time_cnt           = TCFG_LEDC1_RST_TIME_CNT,
LEDC1_PLATFORM_DATA_END()
#endif

#if TCFG_LEDC2_ENABLE
LEDC2_PLATFORM_DATA_BEGIN(ledc2_data)
    .port                   = TCFG_LEDC2_PORT,
    .idle_level             = TCFG_LEDC2_IDLE_LEVEL,
    .out_inv                = TCFG_LEDC2_OUT_INV,
    .bit_inv                = TCFG_LEDC2_BIT_INV,
    .time_base              = TCFG_LEDC2_TIME_BASE,
    .t1h_cnt                = TCFG_LEDC2_T1H_CNT,
    .t1l_cnt                = TCFG_LEDC2_T1L_CNT,
    .t0h_cnt                = TCFG_LEDC2_T0H_CNT,
    .t0l_cnt                = TCFG_LEDC2_T0L_CNT,
    .rst_time_cnt           = TCFG_LEDC2_RST_TIME_CNT,
LEDC2_PLATFORM_DATA_END()
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
LCD_PLATFORM_DATA_END()

static const struct lcd_platform_data lcd_data = {
    .cfg_num = ARRAY_SIZE(lcd_bd_cfg),
    .config_ptr = lcd_bd_cfg,
};


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
#endif


#if TCFG_PWM0_ENABLE
PWM_PLATFORM_DATA_BEGIN(pwm_data0)
    .timer_pwm_port         = TCFG_PWM0_TIMER_PWM_REMAP_IO,
    .mcpwm_port             = TCFG_PWM0_MCPWM_REMAP_IO,
    .pwm_config = {
        .pwm_ch             = TCFG_PWM0_CH_MAPPING,
        .freq               = TCFG_PWM0_FREQUENCY,
        .duty               = TCFG_PWM0_DUTY,
        .point_bit          = TCFG_PWM0_DECIMAL_POINT,//根据point_bit值调节占空比小数点精度位: 0<freq<=4K,point_bit=2;4K<freq<=40K,point_bit=1; freq>40K,point_bit=0;
    },
PWM_PLATFORM_DATA_END()
#endif

#if TCFG_PWM1_ENABLE
PWM_PLATFORM_DATA_BEGIN(pwm_data1)
    .timer_pwm_port         = TCFG_PWM1_TIMER_PWM_REMAP_IO,
    .mcpwm_port             = TCFG_PWM1_MCPWM_REMAP_IO,
    .pwm_config = {
        .pwm_ch             = TCFG_PWM1_CH_MAPPING,
        .freq               = TCFG_PWM1_FREQUENCY,
        .duty               = TCFG_PWM1_DUTY,
        .point_bit          = TCFG_PWM1_DECIMAL_POINT,
    },
PWM_PLATFORM_DATA_END()
#endif

#if TCFG_PWM2_ENABLE
PWM_PLATFORM_DATA_BEGIN(pwm_data2)
    .timer_pwm_port         = TCFG_PWM2_TIMER_PWM_REMAP_IO,
    .mcpwm_port             = TCFG_PWM2_MCPWM_REMAP_IO,
    .pwm_config = {
        .pwm_ch             = TCFG_PWM2_CH_MAPPING,
        .freq               = TCFG_PWM2_FREQUENCY,
        .duty               = TCFG_PWM2_DUTY,
        .point_bit          = TCFG_PWM2_DECIMAL_POINT,
    },
PWM_PLATFORM_DATA_END()
#endif

#if TCFG_PWM3_ENABLE
PWM_PLATFORM_DATA_BEGIN(pwm_data3)
    .timer_pwm_port         = TCFG_PWM3_TIMER_PWM_REMAP_IO,
    .mcpwm_port             = TCFG_PWM3_MCPWM_REMAP_IO,
    .pwm_config = {
        .pwm_ch             = TCFG_PWM3_CH_MAPPING,
        .freq               = TCFG_PWM3_FREQUENCY,
        .duty               = TCFG_PWM3_DUTY,
        .point_bit          = TCFG_PWM3_DECIMAL_POINT,
    },
PWM_PLATFORM_DATA_END()
#endif


#if TCFG_GPCNT_ENABLE
static const struct gpcnt_platform_data gpcnt_data = {
    .gpio                   = TCFG_GPCNT_INPUT_IO,
    .gss_clk_source         = TCFG_GPCNT_GSS_CLK_SOURCE,
    .css_clk_source         = TCFG_GPCNT_CSS_CLK_SOURCE,
    .cycle                  = TCFG_GPCNT_GSS_CYCLE,
};
#endif


#if TCFG_IRKEY_ENABLE
static const struct irkey_platform_data irkey_data = {
    .timer_index            = TCFG_IRKEY_TIMER_INDEX,
    .port                   = TCFG_IRKEY_INPUT_IO,
};

const struct irkey_platform_data *get_irkey_platform_data(void)
{
    return &irkey_data;
}
#endif

#if TCFG_RDEC_KEY_ENABLE
static const struct rdec_device rdeckey_list[] = {
#if TCFG_QDEC0_ENABLE
    {
        .index              = RDEC0,
        .mode               = TCFG_QDEC0_MODE,
        .clk_spnd           = TCFG_QDEC0_CLK_SPND,
        .sin_port0          = TCFG_QDEC0_INPUT_IO_A,
        .sin_port1          = TCFG_QDEC0_INPUT_IO_B,
        .key_value0         = TCFG_QDEC0_KEY_VALUE_A | BIT(7),
        .key_value1         = TCFG_QDEC0_KEY_VALUE_B | BIT(7),
    },
#endif
};

static const struct rdec_platform_data rdec_key_data = {
    .num                    = ARRAY_SIZE(rdeckey_list),
    .rdec                   = rdeckey_list,
};

const struct rdec_platform_data *get_rdec_key_platform_data(void)
{
    return &rdec_key_data;
}
#endif

#if TCFG_IOKEY_ENABLE
static const struct iokey_port iokey_list[] = {
#if TCFG_IOKEY_INPUT0_ENABLE
    {
        .connect_way        = TCFG_IOKEY_INPUT0_CONNECT_WAY,
        .key_type.one_io.port = TCFG_IOKEY_INPUT0_IO,
        .key_value          = TCFG_IOKEY_INPUT0_VALUE,
    },
#endif
#if TCFG_IOKEY_INPUT1_ENABLE
    {
        .connect_way        = TCFG_IOKEY_INPUT1_CONNECT_WAY,
        .key_type.one_io.port = TCFG_IOKEY_INPUT1_IO,
        .key_value          = TCFG_IOKEY_INPUT1_VALUE,
    },
#endif
#if TCFG_IOKEY_INPUT2_ENABLE
    {
        .connect_way        = TCFG_IOKEY_INPUT2_CONNECT_WAY,
        .key_type.one_io.port = TCFG_IOKEY_INPUT2_IO,
        .key_value          = TCFG_IOKEY_INPUT2_VALUE,
    },
#endif
};

static const struct iokey_platform_data iokey_data = {
    .num                    = ARRAY_SIZE(iokey_list),
    .port                   = iokey_list,
};

const struct iokey_platform_data *get_iokey_platform_data(void)
{
    return &iokey_data;
}
#endif

#if TCFG_TOUCH_KEY_ENABLE
static const struct touch_key_port plcnt_port[] = {
#if TCFG_TOUCH_KEY0_ENABLE
    {
        .port               = TCFG_TOUCH_KEY0_PORT,
        .key_value          = TCFG_TOUCH_KEY0_VALUE,
        .press_delta        = TCFG_TOUCH_KEY0_PRESS_DELTA,
    },
#endif
#if TCFG_TOUCH_KEY1_ENABLE
    {
        .port               = TCFG_TOUCH_KEY1_PORT,
        .key_value          = TCFG_TOUCH_KEY1_VALUE,
        .press_delta        = TCFG_TOUCH_KEY1_PRESS_DELTA,
    },
#endif
#if TCFG_TOUCH_KEY2_ENABLE
    {
        .port               = TCFG_TOUCH_KEY2_PORT,
        .key_value          = TCFG_TOUCH_KEY2_VALUE,
        .press_delta        = TCFG_TOUCH_KEY2_PRESS_DELTA,
    },
#endif
};

static const struct touch_key_platform_data touch_key_data = {
    .num                    = ARRAY_SIZE(plcnt_port),
    .clk_src                = TOUCH_KEY_CLOCK_SOURCE,
    .port_list              = plcnt_port,
};

const struct touch_key_platform_data *get_touch_key_platform_data(void)
{
    return &touch_key_data;
}
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


#ifdef CONFIG_AUDIO_ENABLE
#if TCFG_AUDIO_DAC_ENABLE
static const struct dac_platform_data dac_data = {
    .pa_auto_mute           = TCFG_AUDIO_DAC_PA_AUTO_MUTE_ENABLE,
    .pa_mute_port           = TCFG_AUDIO_DAC_PA_MUTE_PORT,
    .pa_mute_value          = TCFG_AUDIO_DAC_PA_MUTE_LEVEL,
    .differ_output          = TCFG_AUDIO_DAC_DIFFER_OUTPUT_ENABLE,
    .hw_channel             = TCFG_AUDIO_DAC_HW_CHANNEL,
#if !TCFG_AUDIO_DAC_DIFFER_OUTPUT_ENABLE && TCFG_AUDIO_DAC_HW_CHANNEL == (AUDIO_DAC_CH_L | AUDIO_DAC_CH_R)
    .ch_num                 = 2,
#else
    .ch_num                 = 1,
#endif
    .vcm_init_delay_ms      = TCFG_AUDIO_DAC_VCM_INIT_DELAY_MS,
    .trim_en                = 0,
    .fade_enable            = 1,
    .fade_points_step       = 1,
    .fade_volume_step       = 1,
    .mute_delay_ms          = TCFG_AUDIO_DAC_PA_MUTE_DELAY_MS,
#ifdef CONFIG_AEC_USE_PLAY_MUSIC_ENABLE
    .sr_points = 960,
#endif
};
#endif

#if TCFG_AUDIO_ADC_ENABLE
static const struct adc_platform_data adc_data = {
    .mic_port               = TCFG_MIC_IO_PORT,
    .linein_port            = TCFG_LINEIN_IO_PORT,
    .mic_ch_num             = TCFG_MIC_CHANNEL_NUM,
    .linein_ch_num          = TCFG_LINEIN_CHANNEL_NUM,
    .all_channel_open       = TCFG_AUDIO_ADC_ALL_CHANNEL_OPEN,
    .dmic_enable            = TCFG_DMIC_ENABLE,
    .dmic_sclk_fre          = TCFG_DMIC_SCLK_FREQUENCY,
    .dmic_io_sclk           = TCFG_DMIC_IO_SCLK,
    .dmic_io_idat0          = TCFG_DMIC_IO_IDAT0,
    .dmic_io_idat1          = TCFG_DMIC_IO_IDAT1,
    .dmic_init_delay_ms     = 150,
    /* .dump_num            = 320, */
};
#endif

#if TCFG_ALNK_ENABLE
static const struct alnk_platform_data alnk_data = {
    .port                   = TCFG_ALNK_PORTS,   ///< [0]MCLK [1]LRCLK [2]SCLK [3]DAT0 [4]DAT1 [5]DAT2 [6]DAT3
    .channel_in             = TCFG_ALNK_CHANNLE_IN_MAP,
    .channel_out            = TCFG_ALNK_CHANNLE_OUT_MAP,
    .data_width             = TCFG_ALNK_DATA_WIDTH,
    .mode                   = TCFG_ALNK_MODE,
    .dma_mode               = TCFG_ALNK_DMA_MODE,
    .slave_mode             = TCFG_ALNK_SLAVE_MODE_ENABLE,
    .mclk_src               = TCFG_ALNK_MCLK_SRC,
    .update_edge            = TCFG_ALNK_UPDATE_EDGE,
#if TCFG_ALNK_DATA_WIDTH == ALNK_DATA_WIDTH_24_BIT
    .dec_width_16_to_24     = 1,
    .enc_width_24_to_32     = 1,
#endif
};
#endif

#if TCFG_PLNK_ENABLE
static const struct plnk_platform_data plnk_data = {
    .hw_channel             = TCFG_PLNK_HW_CHANNEL,
    .share_data_io          = TCFG_PLNK_INPUT_DAT_SHARE_IO_ENABLE,
    .sclk_io                = TCFG_PLNK_SCLK_IO,
    .dat0_io                = TCFG_PLNK_INPUT_DAT0_IO,
    .dat1_io                = TCFG_PLNK_INPUT_DAT1_IO,
    .sclk_fre               = TCFG_PLNK_SCLK_FREQUENCY,
    .ch0_mode               = TCFG_PLNK_CH0_SAMPLE_MODE,
    .ch1_mode               = TCFG_PLNK_CH1_SAMPLE_MODE,
    .order                  = TCFG_PLNK_CIC_ORDER,
    .dfdly_m                = TCFG_PLNK_CIC_DFDLY_M,
    .dc_cancelling_filter   = 4,
    .init_delay_ms          = 80,
    .dump_points_num        = 0,
};
#endif

static const struct audio_pf_data audio_pf_d = {
#if TCFG_AUDIO_DAC_ENABLE
    .dac_pf_data            = &dac_data,
#endif
#if TCFG_AUDIO_ADC_ENABLE
    .adc_pf_data            = &adc_data,
#endif
#if TCFG_ALNK_ENABLE
    .alnk_pf_data           = &alnk_data,
#endif
#if TCFG_PLNK_ENABLE
    .plnk_pf_data           = &plnk_data,
#endif
};

static const struct audio_platform_data audio_data = {
    .private_data           = (void *)&audio_pf_d,
};
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
        .reset_pin          = TCFG_ETH_RMII_BUS_RESET_IO,
        .hd_mode            = TCFG_ETH_RMII_BUS_HD_LEVEL,
    },
NET_PLATFORM_DATA_END()
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

#if TCFG_HOST_CDC_ENABLE
USB_CDC_PLATFORM_DATA_BEGIN(cdc_data)
    .baud_rate = 115200,
    .stop_bits = 0,
    .parity = 0,
    .data_bits = 8,
USB_CDC_PLATFORM_DATA_END()
#endif

#if TCFG_VIR_UDISK_ENABLE
extern const struct device_operations ram_disk_dev_ops;
#endif
#if TCFG_MSD_CDROM_ENABLE
extern const struct device_operations cdrom_dev_ops;
#endif
#endif

#ifdef CONFIG_VIDEO0_ENABLE
static const struct camera_platform_data camera0_data_mipi = {
    .iic_sel        = "iic2",
    .xclk_gpio      = IO_PORTE_10,
    .pwdn_gpio      = IO_PORTE_11,
    .reset_gpio     = IO_PORTE_12,
    .online_detect  = NULL,
    .power_value    = 0,
    .interface      = 2,//SEN_INTERFACE_CSI2,
    .csi2 = {
        .data_lane_num = 1,
        .clk_rmap = CSI2_X0_LANE,
        .clk_inv = 0,
        .d0_rmap = CSI2_X1_LANE,
        .d0_inv = 0,
        .tval_hstt = 12,
        .tval_stto = 12,
    }
};


static const struct video_subdevice_data video0_subdev_data[] = {
    { VIDEO_TAG_CAMERA, (void *)&camera0_data_mipi },
};
static const struct video_platform_data video0_data = {
    .data = video0_subdev_data,
    .num = ARRAY_SIZE(video0_subdev_data),
};



#endif // CONFIG_VIDEO0_ENABLE




#ifdef CONFIG_VIDEO1_ENABLE
const struct camera_platform_data camera1_data = {
    .iic_sel        = TCFG_VIDEO1_IIC_SEL,
	.xclk_gpio      = TCFG_VIDEO1_XCLK,//注意： 如果硬件xclk接到芯片IO，则会占用OUTPUT_CHANNEL1
    .reset_gpio     = TCFG_VIDEO1_RESET,
    .pwdn_gpio      = TCFG_VIDEO1_PWDN,
    .power_value    = 0,
    .interface      = 0,//SEN_INTERFACE_CSI2,
    .dvp = {
		.group_port  = 0,
        .reverse = 0,
        .shift = 0,
        .timing_mode = 0,
        .scan_mode = 0,
        .width_mode = 0,
        .pclk_gpio   = TCFG_VIDEO1_PCLK,
        .hsync_gpio  = TCFG_VIDEO1_HSYNC,
        .vsync_gpio  = TCFG_VIDEO1_VSYNC,
        .data_gpio = {
            TCFG_VIDEO1_D0,
            TCFG_VIDEO1_D1,
            TCFG_VIDEO1_D2,
            TCFG_VIDEO1_D3,
            TCFG_VIDEO1_D4,
            TCFG_VIDEO1_D5,
            TCFG_VIDEO1_D6,
            TCFG_VIDEO1_D7,
            TCFG_VIDEO1_D8,
            TCFG_VIDEO1_D9,
        },
    }
};




static const struct video_subdevice_data video1_subdev_data[] = {
    { VIDEO_TAG_CAMERA, (void *)&camera1_data },
};
static const struct video_platform_data video1_data = {
    .data = video1_subdev_data,
    .num = ARRAY_SIZE(video1_subdev_data),
};
#endif // CONFIG_VIDEO1_ENABLE


#ifdef CONFIG_VIDEO2_ENABLE
UVC_PLATFORM_DATA_BEGIN(uvc_data)
#if THREE_WAY_ENABLE
    .width = 640,
    .height = 480,
#else
    .width = 1280,//1280,
    .height = 720,//480,
#endif
    .fps = 25,
    .mem_size = 200 * 1024,
    .timeout = 500,//ms
UVC_PLATFORM_DATA_END()

static const struct video_subdevice_data video2_subdev_data[] = {
    { VIDEO_TAG_UVC, (void *)&uvc_data },
};
static const struct video_platform_data video2_data = {
    .data = video2_subdev_data,
    .num = ARRAY_SIZE(video2_subdev_data),
};
#endif


#ifdef CONFIG_VIDEO3_ENABLE
const struct camera_platform_data camera3_data = {
    .iic_sel        = "iic1",
	.xclk_gpio      = IO_PORTD_08,//注意： 如果硬件xclk接到芯片IO，则会占用OUTPUT_CHANNEL1
    .reset_gpio     = IO_PORTE_09,
    .pwdn_gpio      = -1,
    .power_value    = 0,
    .interface      = 0,//SEN_INTERFACE_CSI2,
    .dvp = {
		.group_port  = 0,
        .reverse = 0,
        .shift = 0,
        .timing_mode = 0,
        .scan_mode = 0,
        .width_mode = 0,
        .pclk_gpio   = IO_PORTE_03,
        .vsync_gpio  = IO_PORTE_04,
        .hsync_gpio  = IO_PORTE_05,
        .data_gpio = {
               IO_PORTD_09,
               IO_PORTD_10,
               IO_PORTD_11,
               IO_PORTD_12,
               IO_PORTD_13,
               IO_PORTD_14,
               IO_PORTD_15,
               IO_PORTE_00,
			   IO_PORTE_01,
			   IO_PORTE_02,
        },
    }
};


static const struct video_subdevice_data video3_subdev_data[] = {
    { VIDEO_TAG_CAMERA, (void *)&camera3_data },
};
static const struct video_platform_data video3_data = {
    .data = video3_subdev_data,
    .num = ARRAY_SIZE(video3_subdev_data),
};


#endif

#ifdef CONFIG_VIDEO4_ENABLE
const struct camera_platform_data camera4_data = {
    .iic_sel        = "iic1",
	.xclk_gpio      = -1,
    .reset_gpio     = IO_PORTE_09,
    .pwdn_gpio      = -1,
    .power_value    = 0,
    .interface      = 4,
    .dvp = {
		.group_port  = -1,
        .reverse = 0,
        .shift = 0,
        .timing_mode = 0,
        .scan_mode = 0,
        .width_mode = 0,
        .pclk_gpio   = IO_PORTE_03,
        .vsync_gpio  = -1,
        .hsync_gpio  = -1,
        .data_gpio = {
               -1,
               -1,
		IO_PORTD_11,
		IO_PORTD_12,
		IO_PORTD_13,
		IO_PORTD_14,
		IO_PORTD_15,
		IO_PORTE_00,
		IO_PORTE_01,
		IO_PORTE_02,
        },
    }
};

static const struct video_subdevice_data video4_subdev_data[] = {
    { VIDEO_TAG_CAMERA, (void *)&camera4_data },
};

static const struct video_platform_data video4_data = {
    .data = video4_subdev_data,
    .num = ARRAY_SIZE(video4_subdev_data),
};
#endif

#ifdef CONFIG_VIDEO5_ENABLE
const struct camera_platform_data camera5_data = {
    .iic_sel        = "iic1",
	.xclk_gpio      = -1,
    .reset_gpio     = IO_PORTE_09,
    .pwdn_gpio      = -1,
    .power_value    = 0,
    .interface      = 5,
    .dvp = {
		.group_port  = -1,
        .reverse = 0,
        .shift = 0,
        .timing_mode = 0,
        .scan_mode = 0,
        .width_mode = 0,
        .pclk_gpio   = IO_PORTE_03,
        .vsync_gpio  = -1,
        .hsync_gpio  = -1,
        .data_gpio = {
               -1,
               -1,
               IO_PORTD_11,
               IO_PORTD_12,
               IO_PORTD_13,
               IO_PORTD_14,
               IO_PORTD_15,
               IO_PORTE_00,
			   IO_PORTE_01,
			   IO_PORTE_02,
        },
    }
};

static const struct video_subdevice_data video5_subdev_data[] = {
    { VIDEO_TAG_CAMERA, (void *)&camera5_data },
};

static const struct video_platform_data video5_data = {
    .data = video5_subdev_data,
    .num = ARRAY_SIZE(video5_subdev_data),
};

#endif

#ifdef CONFIG_LTE_PHY_ENABLE
extern const struct device_operations lte_module_dev_ops;
LTE_MODULE_DATA_BEGIN(lte_module_data)
	.name = (u8 *)"usb_rndis",
LTE_MODULE_DATA_END()
#endif


//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
//如果改了这里的参数
//要把tools目录下的isd_config.ini文件中的VM_OPT值设置成0,擦除VM
//否者WIFI初始化时会读取VM里已经保存的值进行设置.导致这里值设置不进去.
#if defined CONFIG_BT_ENABLE || TCFG_WIFI_ENABLE
#include "wifi/wifi_connect.h"
#if !BBM_WIFI_PA_ENABLE
const struct wifi_calibration_param wifi_calibration_param = {
    .xosc_l     = 0xb,// 调节左晶振电容
    .xosc_r     = 0xb,// 调节右晶振电容
    .pa_trim_data = {1, 7, 4, 7, 11, 1, 7},// 根据MP测试生成PA TRIM值
	.mcs_dgain    = {
        43,//11B_1M
        42,//11B_2.2M
        42,//11B_5.5M
        41,//11B_11M

        51,//11G_6M
        50,//11G_9M
        60,//11G_12M
        51,//11G_18M
        44,//11G_24M
        44,//11G_36M
        43,//11G_48M
        38,//11G_54M

        50,//11N_MCS0
        71,//11N_MCS1
        52,//11N_MCS2
        44,//11N_MCS3
        44,//11N_MCS4
        43,//11N_MCS5
        38,//11N_MCS6
        33,//11N_MCS7
    }
};
#else
//PA参数
const struct wifi_calibration_param wifi_calibration_param = {
    .xosc_l     = TCFG_WIFI_PA_XOSC_L,// 调节左晶振电容
    .xosc_r     = TCFG_WIFI_PA_XOSC_R,// 调节右晶振电容
    .pa_trim_data = TCFG_WIFI_PA_TRIM_DATA,// 根据MP测试生成PA TRIM值
    .mcs_dgain    = {
        TCFG_WIFI_PA_MCS_DGAIN_1M,//11B_1M
        TCFG_WIFI_PA_MCS_DGAIN_2M,//11B_2.2M
        TCFG_WIFI_PA_MCS_DGAIN_5_5M,//11B_5.5M
        TCFG_WIFI_PA_MCS_DGAIN_11M,//11B_11M

        TCFG_WIFI_PA_MCS_DGAIN_6M,//11G_6M
        TCFG_WIFI_PA_MCS_DGAIN_9M,//11G_9M
        TCFG_WIFI_PA_MCS_DGAIN_12M,//11G_12M
        TCFG_WIFI_PA_MCS_DGAIN_18M,//11G_18M
        TCFG_WIFI_PA_MCS_DGAIN_24M,//11G_24M
        TCFG_WIFI_PA_MCS_DGAIN_36M,//11G_36M
        TCFG_WIFI_PA_MCS_DGAIN_48M,//11G_48M
        TCFG_WIFI_PA_MCS_DGAIN_54M,//11G_54M

        TCFG_WIFI_PA_MCS_DGAIN_MCS0,//11N_MCS0
        TCFG_WIFI_PA_MCS_DGAIN_MCS1,//11N_MCS1
        TCFG_WIFI_PA_MCS_DGAIN_MCS2,//11N_MCS2
        TCFG_WIFI_PA_MCS_DGAIN_MCS3,//11N_MCS3
        TCFG_WIFI_PA_MCS_DGAIN_MCS4,//11N_MCS4
        TCFG_WIFI_PA_MCS_DGAIN_MCS5,//11N_MCS5
        TCFG_WIFI_PA_MCS_DGAIN_MCS6,//11N_MCS6
        TCFG_WIFI_PA_MCS_DGAIN_MCS7,//11N_MCS7
    }
};

#endif /* !BBM_WIFI_PA_ENABLE */

#endif


#if TCFG_RTC_ENABLE
static void alarm_wakeup_cb_in_irq(void)
{

}

static void pr_wakeup_cb_in_irq(int port)
{

}

RTC_PLATFORM_DATA_BEGIN(rtc_data)
    .default_sys_time       = {
        .year               = 2024,
        .month              = 1,
        .day                = 1,
        .hour               = 0,
        .min                = 0,
        .sec                = 0,
    },
    .alarm_wakeup_cb_in_irq = alarm_wakeup_cb_in_irq,
    .pr_wakeup_cb_in_irq    = pr_wakeup_cb_in_irq,
    .clk_sel                = TCFG_RTC_CLK_SEL,
    .x32xs                  = TCFG_RTC_X32XS_LEVEL,
RTC_PLATFORM_DATA_END()
#endif


#ifdef CONFIG_DMSDX_ENABLE
static struct dmsdx_platform_data dmsdx_data0 = {
    .block_offset_start     = CONFIG_SDNAND_HFS_LEN / 512,
    .block_offset_end       = (CONFIG_SDNAND_HFS_LEN + CONFIG_SDNAND_HFAT_LEN) / 512,
};
static struct dmsdx_platform_data dmsdx_data1 = {
    .block_offset_start     = (CONFIG_SDNAND_HFS_LEN + CONFIG_SDNAND_HFAT_LEN) / 512,
    .block_offset_end       = (CONFIG_SDNAND_HFS_LEN + CONFIG_SDNAND_HFAT_LEN + CONFIG_SDNAND_FAT1_LEN) / 512,
};
#endif

#if TCFG_GSENSOR_ENABLE
const struct gsensor_platform_data gsensor_data = {
    .iic                    = TCFG_GSENSOR_IIC_INTERFACE,
};
#endif


REGISTER_DEVICES(device_table) = {
#if TCFG_USB_SLAVE_ENABLE || TCFG_USB_HOST_ENABLE
    { "otg", &usb_dev_ops, (void *)&otg_data },
#endif
#if TCFG_PAP_ENABLE
    { "pap", &pap_dev_ops, (void *)&pap_data }, ///< MCU屏使用了pap，pap设备需要放在lcd前面注册
#endif
#if TCFG_SPI2_ENABLE
    { "spi2", &spi_dev_ops, (void *)&spi2_data }, ///< SPI屏使用了spi2，spi2设备需要放在lcd前面注册
#endif
#if TCFG_LCD_ENABLE
    { "lcd",   &lcd_dev_ops, (void*)&lcd_data },
    { "fb_out",  &fb_out_dev_ops, NULL },
#endif
#if TCFG_GPCNT_ENABLE
    { "gpcnt", &gpcnt_dev_ops, (void *)&gpcnt_data },
#endif
#if TCFG_ETH_ENABLE
    { "eth", &eth_phy_dev_ops, (void *)&net_phy_data },
#endif

#if TCFG_EXT_WIFI_ENABLE
    { "wifi",  &wifi_dev_ops, (void *) &wifi_data},
#endif

#if TCFG_LEDC0_ENABLE
    { "ledc0", &ledc_dev_ops, (void *)&ledc0_data },
#endif
#if TCFG_LEDC1_ENABLE
    { "ledc1", &ledc_dev_ops, (void *)&ledc1_data },
#endif
#if TCFG_LEDC2_ENABLE
    { "ledc2", &ledc_dev_ops, (void *)&ledc2_data },
#endif

#if TCFG_PWM0_ENABLE
    { "pwm0", &pwm_dev_ops, (void *)&pwm_data0 },
#endif
#if TCFG_PWM1_ENABLE
    { "pwm1", &pwm_dev_ops, (void *)&pwm_data1 },
#endif
#if TCFG_PWM2_ENABLE
    { "pwm2", &pwm_dev_ops, (void *)&pwm_data2 },
#endif
#if TCFG_PWM3_ENABLE
    { "pwm3", &pwm_dev_ops, (void *)&pwm_data3 },
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
#if TCFG_SW_IIC2_ENABLE
    { "iic5", &iic_dev_ops, (void *)&sw_iic2_data },
#endif

#if TCFG_SD0_ENABLE
    { "sd0", &sd_dev_ops, (void *)&sd0_data },
#ifdef CONFIG_DMSDX_ENABLE
    { "sd0.0", &dmsd_dev_ops, (void *)&dmsdx_data0 },
    { "sd0.1", &dmsd_dev_ops, (void *)&dmsdx_data1 },
#endif
#endif
#if TCFG_SD1_ENABLE
    { "sd1", &sd_dev_ops, (void *)&sd1_data },
#ifdef CONFIG_DMSDX_ENABLE
    { "sd1.0", &dmsd_dev_ops, (void *)&dmsdx_data0 },
    { "sd1.1", &dmsd_dev_ops, (void *)&dmsdx_data1 },
#endif
#endif

#if TCFG_CAN_ENABLE
    { "can", &can_dev_ops, (void *)&can_data },
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

#ifdef CONFIG_AUDIO_ENABLE
    { "audio", &audio_dev_ops, (void *)&audio_data },
#endif


#ifdef CONFIG_VIDEO0_ENABLE
    { "video0.*",  &video_dev_ops, (void *)&video0_data },
#endif

#ifdef CONFIG_VIDEO1_ENABLE
    { "video1.*",  &video_dev_ops, (void *)&video1_data },
#endif
#ifdef CONFIG_VIDEO2_ENABLE
    {"uvc", &uvc_dev_ops, NULL},
    { "video10.*",  &video_dev_ops, (void *)&video2_data },
    { "video11.*",  &video_dev_ops, (void *)&video2_data },
#endif

#ifdef CONFIG_VIDEO3_ENABLE
    {"video3.*",  &video_dev_ops, (void *) &video3_data},
#endif

#ifdef CONFIG_VIDEO4_ENABLE
    {"video4.*",  &video_dev_ops, (void *) &video4_data},
#endif

#ifdef CONFIG_VIDEO5_ENABLE
    {"video5.*",  &video_dev_ops, (void *) &video5_data},
#endif

#ifdef CONFIG_VIDEO_DEC_ENABLE
	{ "video_dec",  &video_dev_ops, NULL },
#endif
    /* { "videoengine",  &video_engine_ops, NULL }, */



#if defined CONFIG_VIDEO_ENABLE || defined CONFIG_UI_ENABLE
    { "fb0",   &fb_dev_ops, NULL },
    { "fb1",   &fb_dev_ops, NULL },
    { "fb2",   &fb_dev_ops, NULL },
    { "fb3",   &fb_dev_ops, NULL },
    { "fb4",   &fb_dev_ops, NULL },
    { "fb5",   &fb_dev_ops, NULL },
    { "fb6",   &fb_dev_ops, NULL },
    { "fb7",   &fb_dev_ops, NULL },
    { "fb8",   &fb_dev_ops, NULL },
#endif

#if TCFG_RTC_ENABLE
    { "rtc", &rtc_dev_ops, (void *)&rtc_data },
#endif

#if TCFG_UDISK_ENABLE
    { "udisk0", &mass_storage_ops, NULL },
    { "udisk1", &mass_storage_ops, NULL },
#endif
#if TCFG_VIR_UDISK_ENABLE
    { "vir_udisk", &ram_disk_dev_ops, NULL },
#endif
#if TCFG_MSD_CDROM_ENABLE
    { "cdrom", &cdrom_dev_ops, NULL },
#endif
#if TCFG_HOST_CDC_ENABLE
    { "cdc0", &usb_cdc_ops, (void *)&cdc_data },
    { "cdc1", &usb_cdc_ops, (void *)&cdc_data },
#endif

#if TCFG_GSENSOR_ENABLE
	{"gsensor", &gsensor_dev_ops, (void *)&gsensor_data },
#endif

#ifdef CONFIG_LTE_PHY_ENABLE
    { "lte",  &lte_module_dev_ops, (void *) &lte_module_data},
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

#if TCFG_LOWPOWER_WAKEUP_PORT1_ENABLE
static void wakeup_port1_callback_in_irq(p33_io_wkup_edge_t edge)
{

}

static const p33_io_wakeup_config_t wakeup_port1 = {
    .pullup_down_enable     = 1,
    .filter                 = TCFG_LOWPOWER_WAKEUP_PORT1_FILTER,
    .edge                   = TCFG_LOWPOWER_WAKEUP_PORT1_EDGE,
    .gpio                   = TCFG_LOWPOWER_WAKEUP_PORT1_IO,
    .callback               = wakeup_port1_callback_in_irq,
};
#endif

#if TCFG_LOWPOWER_WAKEUP_PORT2_ENABLE
static void wakeup_port2_callback_in_irq(p33_io_wkup_edge_t edge)
{

}

static const p33_io_wakeup_config_t wakeup_port2 = {
    .pullup_down_enable     = 1,
    .filter                 = TCFG_LOWPOWER_WAKEUP_PORT2_FILTER,
    .edge                   = TCFG_LOWPOWER_WAKEUP_PORT2_EDGE,
    .gpio                   = TCFG_LOWPOWER_WAKEUP_PORT2_IO,
    .callback               = wakeup_port2_callback_in_irq,
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

#if TCFG_IOKEY_ENABLE
#if TCFG_IOKEY_INPUT0_ENABLE
    PORT_PROTECT(iokey_list[0].key_type.one_io.port);
#endif
#if TCFG_IOKEY_INPUT1_ENABLE
    //cppcheck-suppress arrayIndexOutOfBounds
    PORT_PROTECT(iokey_list[1].key_type.one_io.port);
#endif
#if TCFG_IOKEY_INPUT2_ENABLE
    //cppcheck-suppress arrayIndexOutOfBounds
    PORT_PROTECT(iokey_list[2].key_type.one_io.port);
#endif
#endif

#if TCFG_ADKEY_ENABLE
    PORT_PROTECT(adkey_data.adkey_pin);
#endif

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

#if TCFG_RTC_ENABLE
    poweroff_save_rtc_time();
#endif

#if TCFG_ADKEY_ENABLE || (defined CONFIG_BT_ENABLE || TCFG_WIFI_ENABLE) || TCFG_RTC_ENABLE
    adc_suspend();
#endif
    /* do_platform_uninitcall(); */

#if TCFG_LOWPOWER_WAKEUP_PORT0_ENABLE
    p33_io_wakeup_port_init(&wakeup_port0);
    p33_io_wakeup_enable(TCFG_LOWPOWER_WAKEUP_PORT0_IO, 1);
#endif

#if TCFG_LOWPOWER_WAKEUP_PORT1_ENABLE
    p33_io_wakeup_port_uninit(TCFG_LOWPOWER_WAKEUP_PORT1_IO);
#endif

#if TCFG_LOWPOWER_WAKEUP_PORT2_ENABLE
    p33_io_wakeup_port_init(&wakeup_port2);
    p33_io_wakeup_enable(TCFG_LOWPOWER_WAKEUP_PORT2_IO, 1);
#endif

    __mask_io_cfg();

    gpio_config_soft_poweroff();

    /* gpio_config_uninit(); */

    return 0;
}

#if TCFG_PRESS_LONG_KEY_POWERON_ENABLE
//ad按键和开关机键复用
static unsigned int read_power_key(int dly)
{
    gpio_latch_en(adkey_data.adkey_pin, 0);
    gpio_direction_input(adkey_data.adkey_pin);
    gpio_set_die(adkey_data.adkey_pin, 0);
    gpio_set_pull_up(adkey_data.adkey_pin, 0);
    gpio_set_pull_down(adkey_data.adkey_pin, 0);

    if (dly) {
        delay_us(3000);
    }

    return (adc_sample(adkey_data.ad_channel, 1) < 50);
}

void sys_power_poweroff_wait_powerkey_up(void)
{
    adc_suspend();

    while (read_power_key(1));

    adc_resume();
}
#endif

void power_early_flowing(void)
{
    PORT_TABLE(g);

    // 默认关闭MCLR
    p33_and_1byte(P3_PR_PWR, (u8)~(BIT(3)));

    // 默认关闭长按复位0，由key_driver配置
    gpio_longpress_pin0_reset_config(IO_PORTD_01, 0, 0, 1, 1);

    //前面已经初始化过的IO需要在这里加一下对应IO的保护，否则会被覆盖成高阻状态
#if (defined CONFIG_DEBUG_ENABLE) && (TCFG_DEBUG_PORT != -1)
    PORT_PROTECT(TCFG_DEBUG_PORT);
#endif
#if TCFG_UART_KEY_ENABLE && TCFG_UART_KEY_INPUT_IO != -1
    PORT_PROTECT(TCFG_UART_KEY_INPUT_IO);
#endif

    power_early_init((u32)gpio_config);

    power_set_mode(TCFG_POWER_MODE);

#if TCFG_RTC_ENABLE
    set_rtc_platform_data(&rtc_data);
#endif
}

static void board_power_init(void)
{
    /* gpio_config_init(); */
#if TCFG_RTC_ENABLE
    power_control(PCONTROL_RTC_CLK, TCFG_RTC_CLK_SEL);
#endif
    power_control(PCONTROL_PD_VDDIO_KEEP, VDDIO_KEEP_TYPE_NORMAL);
    power_control(PCONTROL_SF_VDDIO_KEEP, VDDIO_KEEP_TYPE_NULL);
    power_control(PCONTROL_SF_KEEP_VCM_DET , true);

    power_init(&power_pdata);

#if TCFG_PRESS_LONG_KEY_POWERON_ENABLE
    if (is_gpio_wakeup(adkey_data.adkey_pin)) {
        for (int i = 0; i < 500; i++) {
            if (0 == read_power_key(1)) {
                sys_power_poweroff();
                break;
            }
        }
    }
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
    os_time_dly(1);
#ifdef CONFIG_AUDIO_ENABLE
#if TCFG_AUDIO_DAC_ENABLE || TCFG_AUDIO_ADC_ENABLE
    dac_early_init(dac_data.hw_channel, TCFG_AUDIO_DAC_VCM_CAP_ENABLE);
#if !TCFG_AUDIO_DAC_PA_AUTO_MUTE_ENABLE && TCFG_AUDIO_DAC_PA_MUTE_PORT != -1
    gpio_direction_output(TCFG_AUDIO_DAC_PA_MUTE_PORT, !TCFG_AUDIO_DAC_PA_MUTE_LEVEL);
#endif
#endif
#endif

    extern const char WIFI_PA_ENABLE;
    if(WIFI_PA_ENABLE){

        gpio_set_mode(TCFG_WIFI_PA_RXEN_IO,GPIO_OUTPUT_LOW);
        gpio_set_mode(TCFG_WIFI_PA_TXEN_IO,GPIO_OUTPUT_LOW);

        gpio_och_sel_output_signal(TCFG_WIFI_PA_RXEN_IO,OUTPUT_CH_SIGNAL_WL_LNAE);   //RX
        gpio_och_sel_output_signal(TCFG_WIFI_PA_TXEN_IO,OUTPUT_CH_SIGNAL_WL_AMPE);   //TX

    }

#if TCFG_ADKEY_ENABLE || (defined CONFIG_BT_ENABLE || TCFG_WIFI_ENABLE) || TCFG_RTC_ENABLE
    adc_init();
#endif
#if TCFG_RTC_ENABLE
    rtc_early_init();
#endif
#if (TCFG_IOKEY_ENABLE || TCFG_IRKEY_ENABLE || TCFG_RDEC_KEY_ENABLE || TCFG_ADKEY_ENABLE || TCFG_TOUCH_KEY_ENABLE || TCFG_UART_KEY_ENABLE)
    key_driver_init();
    key_event_disable();
    touch_event_disable();
#endif

#if TCFG_LOW_POWER_AUTO_SHUTDOWN_ENABLE
    sys_power_init();
#endif
#ifdef CONFIG_BT_ENABLE
    void cfg_file_parse(void);
    cfg_file_parse();
#endif
}

#endif // CONFIG_BOARD_DEVELOP

