#if defined CONFIG_BOARD_DEVELOP

//*********************************************************************************//
//                                功能模块配置                                     //
//*********************************************************************************//
#define CONFIG_SFC_ENABLE
// #define CONFIG_NO_SDRAM_ENABLE                             //关闭sdram
// #define CONFIG_EXFLASH_ENABLE                              //外挂资源flash
// #define CONFIG_SDFILE_EXT_ENABLE                           //外挂隐藏sdfile区的支持
// #define CONFIG_DMSDX_ENABLE                                //msd多分区显示支持

#define CONFIG_NET_ENABLE
#define CONFIG_BT_ENABLE
// #define CONFIG_UI_ENABLE
// #define CONFIG_VIDEO_ENABLE
#define CONFIG_MEDIA_ENABLE


//
//*********************************************************************************//
//                                   时钟配置                                      //
//*********************************************************************************//
#define TCFG_OSC_FREQUENCY                  24000000
#define TCFG_SYS_CLK                        320000000         //240M,192M,160M,120M,96M,80M,64M,60M,48M,40M,32M,24M，其他值时启用SYS_PLL(最高支持300M)
#define TCFG_LSB_CLK                        48000000          //96M,80M,60M,48M,40M,24M,20M,12M
#define TCFG_HSB_CLK_DIV                    2                 //HSB_CLK = SYS_CLK / HSB_CLK_DIV
#define TCFG_SFCTZ_CLK                      96000000          //SFC时钟，和加载代码的速度有关
#define TCFG_SDRAM_CLK                      200000000         //SDRAM/DDR时钟
#define TCFG_VIDEO_CLK                      TCFG_SYS_CLK      //EVA/PUB时钟，240M,192M,160M,120M,96M,80M,64M,60M,48M，其他值时启用SYS_PLL或者DDR_PLL
#define TCFG_GPU_CLK                        TCFG_SYS_CLK      //GPU时钟，240M,192M,160M,120M,96M,80M,64M,60M,48M，TCFG_SYS_CLK(和cpu同频)


//*********************************************************************************//
//                                  flash配置                                      //
//*********************************************************************************//
/*
#data_width[1 2 4]
#clkdiv [1-255] SPITZ_CLK=SYS_CLK/HSB_CLK_DIV/clkdiv
#mode:
#	  0 RD_OUTPUT,		 1 cmd 		 1 addr
#	  1 RD_I/O,   		 1 cmd 		 x addr
#	  2 RD_I/O_CONTINUE] no_send_cmd x add
#port:固定0
*/
#define TCFG_SPITZ_WIDTH_CLKDIV_MODE_PORT   4_5_0_0

/*
#FLASH_QE_POS和FLASH_SPEC_QE_ID为'或'关系, 有一项条件符合，开机会按特殊QE位flash配置
#TCFG_FLASH_QE_POS     —— QE位置, 0-常规(SR2-BIT1), 1-特殊(SR1-BIT6)
#TCFG_FLASH_SPEC_QE_ID —— QE在SR1_BIT6的FlashID列表(最长128个字符, 'X'为通配符)
*/
#define TCFG_FLASH_QE_POS                   0
#define TCFG_FLASH_SPEC_QE_ID               C220XX_9D70XX_1C7019

//*********************************************************************************//
//                                  sdram配置                                      //
//*********************************************************************************//
#ifdef CONFIG_NO_SDRAM_ENABLE
#define TCFG_FREE_DCACHE_WAY                7
#else
#define TCFG_FREE_DCACHE_WAY                0
#endif
#define TCFG_SDRAM_MODE                     1              //0-sdram    1-ddr1


//*********************************************************************************//
//                                  UART配置                                       //
//*********************************************************************************//
#define TCFG_UBOOT_DEBUG_PORT               PD01
#define TCFG_UART_KEY_INPUT_IO              -1//IO_PORTE_11
#define TCFG_UART_KEY_ENABLE                0              //串口按键

#define TCFG_UART0_ENABLE                   TCFG_DEBUG_UART_ENABLE  //UART0默认用来打印口
#define TCFG_UART0_TX_IO                    TCFG_DEBUG_PORT
#define TCFG_UART0_RX_IO                    TCFG_UART_KEY_INPUT_IO
#define TCFG_UART0_BAUDRATE                 TCFG_DEBUG_BAUDRATE
#define TCFG_UART0_PARITY                   UART_PARITY_DISABLE

#define TCFG_UART1_ENABLE                   0
#define TCFG_UART1_TX_IO                    IO_PORT_USB_DPA
#define TCFG_UART1_RX_IO                    IO_PORT_USB_DMA
#define TCFG_UART1_BAUDRATE                 1000000
#define TCFG_UART1_FLOW_CTL_ENABLE          0
#define TCFG_UART1_RTS_HW_ENABLE            0
#define TCFG_UART1_RTS_RX_THRESH            80
#define TCFG_UART1_MAX_CONTINUE_RECV_CNT    1024
#define TCFG_UART1_RTS_IO                   -1
#define TCFG_UART1_CTS_IO                   -1
#define TCFG_UART1_RTS_IDLE_LEVEL           0
#define TCFG_UART1_CTS_IDLE_LEVEL           0
#define TCFG_UART1_PARITY                   UART_PARITY_DISABLE

#define TCFG_UART2_ENABLE                   0
#define TCFG_UART2_TX_IO                    IO_PORT_USB_DPA
#define TCFG_UART2_RX_IO                    IO_PORT_USB_DMA
#define TCFG_UART2_BAUDRATE                 1000000
#define TCFG_UART2_FLOW_CTL_ENABLE          0
#define TCFG_UART2_RTS_HW_ENABLE            0
#define TCFG_UART2_RTS_RX_THRESH            80
#define TCFG_UART2_MAX_CONTINUE_RECV_CNT    1024
#define TCFG_UART2_RTS_IO                   -1
#define TCFG_UART2_CTS_IO                   -1
#define TCFG_UART2_RTS_IDLE_LEVEL           0
#define TCFG_UART2_CTS_IDLE_LEVEL           0
#define TCFG_UART2_PARITY                   UART_PARITY_DISABLE

#define TCFG_UART3_ENABLE                   0
#define TCFG_UART3_TX_IO                    IO_PORT_USB_DPA
#define TCFG_UART3_RX_IO                    IO_PORT_USB_DMA
#define TCFG_UART3_BAUDRATE                 1000000
#define TCFG_UART3_PARITY                   UART_PARITY_DISABLE

#define TCFG_UART4_ENABLE                   0
#define TCFG_UART4_TX_IO                    IO_PORT_USB_DPA
#define TCFG_UART4_RX_IO                    IO_PORT_USB_DMA
#define TCFG_UART4_BAUDRATE                 1000000
#define TCFG_UART4_PARITY                   UART_PARITY_DISABLE


//*********************************************************************************//
//                                  SDIO配置                                       //
//*********************************************************************************//
#define TCFG_SD0_POWER_ENABLE               0
#define TCFG_SD1_POWER_ENABLE               0


//*********************************************************************************//
//                                   IIC配置                                       //
//*********************************************************************************//
/* touch panel IIC */
#define TCFG_HW_IIC0_ENABLE                 1
#define TCFG_HW_IIC0_ROLE                   IIC_ROLE_MASTER
#define TCFG_HW_IIC0_HD_LEVEL               0
#define TCFG_HW_IIC0_SDA_IO                 IO_PORTA_02
#define TCFG_HW_IIC0_SCL_IO                 IO_PORTA_01
#define TCFG_HW_IIC0_IRQ_ENABLE             0
#define TCFG_HW_IIC0_BAUDRATE               400000
#define TCFG_HW_IIC0_SLAVE_ADDR             0x86
#define TCFG_HW_IIC0_STRETCH_DISABLE        0

/* CAM2(DVP0) IIC */
#define TCFG_HW_IIC1_ENABLE                 0
#define TCFG_HW_IIC1_HD_LEVEL               0
#define TCFG_HW_IIC1_SDA_IO                 IO_PORTE_07
#define TCFG_HW_IIC1_SCL_IO                 IO_PORTE_08
#define TCFG_HW_IIC1_IRQ_ENABLE             0
#define TCFG_HW_IIC1_BAUDRATE               400000

/* CAM1(MIPI) IIC */
#define TCFG_HW_IIC2_ENABLE                 0
#define TCFG_HW_IIC2_HD_LEVEL               0
#define TCFG_HW_IIC2_SDA_IO                 IO_PORTE_13
#define TCFG_HW_IIC2_SCL_IO                 IO_PORTE_14
// #define TCFG_HW_IIC2_SDA_IO                 IO_PORTC_03
// #define TCFG_HW_IIC2_SCL_IO                 IO_PORTC_04
#define TCFG_HW_IIC2_IRQ_ENABLE             0
#define TCFG_HW_IIC2_BAUDRATE               400000

#define TCFG_SW_IIC0_ENABLE                 0
#define TCFG_SW_IIC0_HD_LEVEL               0
#define TCFG_SW_IIC0_SDA_IO                 IO_PORTD_08
#define TCFG_SW_IIC0_SCL_IO                 IO_PORTD_01
#define TCFG_SW_IIC0_IO_LEVEL_DELAY         50

#define TCFG_SW_IIC1_ENABLE                 0
#define TCFG_SW_IIC1_HD_LEVEL               0
#define TCFG_SW_IIC1_SDA_IO                 IO_PORTC_05
#define TCFG_SW_IIC1_SCL_IO                 IO_PORTC_04
#define TCFG_SW_IIC1_IO_LEVEL_DELAY         50


//*********************************************************************************//
//                                   CAN配置                                       //
//*********************************************************************************//
#define TCFG_CAN_ENABLE                     0
#define TCFG_CANOPEN_ENABLE                 TCFG_CAN_ENABLE
#define TCFG_CAN_MODE                       1 //enhanced can
#define TCFG_CAN_RX_IO                      IO_PORTC_01
#define TCFG_CAN_TX_IO                      IO_PORTC_02
#define TCFG_CAN_STM_ENABLE                 0
#define TCFG_CAN_LOM_ENABLE                 0
#define TCFG_CAN_BAUD_BRP                   3
#define TCFG_CAN_BAUD_SJW                   3
#define TCFG_CAN_BAUD_SAM                   1
#define TCFG_CAN_BAUD_PTS_PBS1              2
#define TCFG_CAN_BAUD_PBS2                  1
#if TCFG_CAN_MODE == 1 //enhanced can
#define TCFG_CAN_FILTER_MODE                1
#define TCFG_CAN_FILTER_ACC_ID0             0x1FFFFFFF
#define TCFG_CAN_FILTER_ACC_ID1             0x10FFFFFF
#define TCFG_CAN_FILTER_ACC_RTR0            1
#define TCFG_CAN_FILTER_ACC_RTR1            0
#define TCFG_CAN_FILTER_MASK_ID0            0xFFFFFFFF
#define TCFG_CAN_FILTER_MASK_ID1            0xFFFFFFFF
#define TCFG_CAN_FILTER_MASK_RTR0           1
#define TCFG_CAN_FILTER_MASK_RTR1           1
#else
#define TCFG_CAN_FILTER_MODE                2
#define TCFG_CAN_FILTER_ACC_ID0             0x654
#define TCFG_CAN_FILTER_MASK_ID0            0xFF
#endif


//*********************************************************************************//
//                                  LEDC配置                                        //
//*********************************************************************************//
#define TCFG_LEDC0_ENABLE                   0
#define TCFG_LEDC0_PORT                     IO_PORTA_04
#define TCFG_LEDC0_IDLE_LEVEL               LEDC_IDLE_LEVEL_L
#define TCFG_LEDC0_OUT_INV                  LEDC_OUT_INV_NREV
#define TCFG_LEDC0_BIT_INV                  LEDC_BIT_INV_8BIT
#define TCFG_LEDC0_TIME_BASE                LEDC_TIME_BASE_42NS
#define TCFG_LEDC0_T1H_CNT                  24
#define TCFG_LEDC0_T1L_CNT                  7
#define TCFG_LEDC0_T0H_CNT                  7
#define TCFG_LEDC0_T0L_CNT                  24
#define TCFG_LEDC0_RST_TIME_CNT             20000

#define TCFG_LEDC1_ENABLE                   0
#define TCFG_LEDC1_PORT                     IO_PORTA_04
#define TCFG_LEDC1_IDLE_LEVEL               LEDC_IDLE_LEVEL_L
#define TCFG_LEDC1_OUT_INV                  LEDC_OUT_INV_NREV
#define TCFG_LEDC1_BIT_INV                  LEDC_BIT_INV_8BIT
#define TCFG_LEDC1_TIME_BASE                LEDC_TIME_BASE_42NS
#define TCFG_LEDC1_T1H_CNT                  24
#define TCFG_LEDC1_T1L_CNT                  7
#define TCFG_LEDC1_T0H_CNT                  7
#define TCFG_LEDC1_T0L_CNT                  24
#define TCFG_LEDC1_RST_TIME_CNT             20000

#define TCFG_LEDC2_ENABLE                   0
#define TCFG_LEDC2_PORT                     IO_PORTA_04
#define TCFG_LEDC2_IDLE_LEVEL               LEDC_IDLE_LEVEL_L
#define TCFG_LEDC2_OUT_INV                  LEDC_OUT_INV_NREV
#define TCFG_LEDC2_BIT_INV                  LEDC_BIT_INV_8BIT
#define TCFG_LEDC2_TIME_BASE                LEDC_TIME_BASE_42NS
#define TCFG_LEDC2_T1H_CNT                  24
#define TCFG_LEDC2_T1L_CNT                  7
#define TCFG_LEDC2_T0H_CNT                  7
#define TCFG_LEDC2_T0L_CNT                  24
#define TCFG_LEDC2_RST_TIME_CNT             20000

//*********************************************************************************//
//                                   SPI配置                                       //
//*********************************************************************************//
#define TCFG_SPI0_ENABLE                    0
#define TCFG_SPI0_CS_IO                     -1
#define TCFG_SPI0_CLK_IO                    IO_PORTC_06
#define TCFG_SPI0_DO_IO                     IO_PORTC_07
#define TCFG_SPI0_DI_IO                     IO_PORTC_08
#define TCFG_SPI0_D2_IO                     IO_PORTC_09
#define TCFG_SPI0_D3_IO                     IO_PORTC_10
#define TCFG_SPI0_BAUDRATE                  48000000
#define TCFG_SPI0_HD_LEVEL                  0
#define TCFG_SPI0_MODE                      SPI_QUAD_MODE
#define TCFG_SPI0_ATTR                      SPI_SCLK_L_UPL_SMPL
#define TCFG_SPI0_ROLE                      SPI_MODE_MASTER

#define TCFG_SPI1_ENABLE                    0
#define TCFG_SPI1_CS_IO                     -1
#define TCFG_SPI1_CLK_IO                    IO_PORTC_06
#define TCFG_SPI1_DO_IO                     IO_PORTB_08
#define TCFG_SPI1_DI_IO                     IO_PORTB_09
#define TCFG_SPI1_D2_IO                     IO_PORTA_04
#define TCFG_SPI1_D3_IO                     IO_PORTA_05
#define TCFG_SPI1_BAUDRATE                  10000000
#define TCFG_SPI1_HD_LEVEL                  0
#define TCFG_SPI1_MODE                      SPI_STD_MODE//SPI_QUAD_MODE
#define TCFG_SPI1_ATTR                      SPI_SCLK_L_UPL_SMPH
#define TCFG_SPI1_ROLE                      SPI_MODE_MASTER

#define TCFG_SPI2_ENABLE                    1
#define TCFG_SPI2_CS_IO                     -1
#define TCFG_SPI2_CLK_IO                    IO_PORTC_07
#define TCFG_SPI2_DO_IO                     IO_PORTB_10
#define TCFG_SPI2_DI_IO                     IO_PORTB_11
#define TCFG_SPI2_BAUDRATE                  10000000
#define TCFG_SPI2_HD_LEVEL                  0
#define TCFG_SPI2_MODE                      SPI_STD_MODE //SPI_DUAL_MODE
#define TCFG_SPI2_ATTR                      SPI_SCLK_L_UPL_SMPH
#define TCFG_SPI2_ROLE                      SPI_MODE_SLAVE


//*********************************************************************************//
//                            外挂资源NORFLASH配置                                 //
//*********************************************************************************//
#define TCFG_NORFLASH_SFC_DEV_ENABLE        0
#define TCFG_NORFLASH_SFC_READ_MODE         FAST_READ_OUTPUT_MODE
#define TCFG_NORFLASH_SFC_DATA_WIDTH        4
#define TCFG_NORFLASH_SFC_ENCRYPTION        0
#define TCFG_NORFLASH_SFC_CLK_DIV           1
#define TCFG_NORFLASH_SPI_CLK_DIV           1
#define TCFG_NORFLASH_SFC_CLK_SRC           SFC_CLK_SRC_HSB_CLK
#define TCFG_NORFLASH_SFC_UNENC_START_ADDR  0
#define TCFG_NORFLASH_SFC_UNENC_START_SIZE  0


//*********************************************************************************//
//                                  GPCNT配置                                      //
//*********************************************************************************//
#define TCFG_GPCNT_ENABLE                   0
#define TCFG_GPCNT_INPUT_IO                 IO_PORTA_01
#define TCFG_GPCNT_GSS_CLK_SOURCE           GPCNT_GSS_CSS_PLL_96M
#define TCFG_GPCNT_CSS_CLK_SOURCE           GPCNT_GSS_CSS_INPUT_CAP_MUX
#define TCFG_GPCNT_GSS_CYCLE                15


//*********************************************************************************//
//                                   PAP配置                                       //
//*********************************************************************************//
#define TCFG_PAP_ENABLE                     1
#define TCFG_PAP_DATA_WIDTH                 PAP_DATAWIDTH_8BIT
#define TCFG_PAP_DATA_ENDIAN                PAP_ENDIAN_BE
#define TCFG_PAP_WRITE_ACTIVE_LEVEL         PAP_WR_LEVEL_LOW
#define TCFG_PAP_READ_ACTIVE_LEVEL          PAP_RD_LEVEL_LOW
#define TCFG_PAP_READ_ENABLE                0
#define TCFG_PAP_WE_IO                      IO_PORTA_12
#define TCFG_PAP_RE_IO                      IO_PORTA_14


//*********************************************************************************//
//                                   LCD配置                                       //
//*********************************************************************************//
#ifdef CONFIG_UI_ENABLE
#define TCFG_LCD_ENABLE                     1
#define TCFG_LCD_INPUT_FORMAT               LCD_IN_RGB565//注意修改后需要同步修改lv_conf.h:LV_COLOR_DEPTH
#define TCFG_LCD_SUPPORT_MULTI_DRIVER_EN    0

// 屏驱配置使能
#define TCFG_LCD_MIPI_ST7701S_480x800             0
#define TCFG_LCD_MIPI_ST7701S_480x800_ROTATE_90   1 ///< mipi ST7701S_480x800竖屏横显的配置
#include "lcd_board_cfg_template.h"                 ///< WL83开发板标配屏以外的屏驱配置放这里

#if TCFG_LCD_MIPI_ST7701S_480x800
#define TCFG_LCD_DEVICE_NAME                "MIPI_480x800_ST7701S"
#define TCFG_LCD_BL_VALUE                   1
#define TCFG_LCD_RESET_IO                   IO_PORTB_00
#define TCFG_LCD_BL_IO                      IO_PORTB_01
#define TCFG_LCD_RS_IO                      -1
#define TCFG_LCD_CS_IO                      -1
#define TCFG_LCD_TE_ENABLE                  0
#define TCFG_LCD_TE_IO                      -1
#define TCFG_LCD_SPI_INTERFACE              NULL
#endif

#if TCFG_LCD_MIPI_ST7701S_480x800_ROTATE_90
#define TCFG_LCD_DEVICE_NAME                "MIPI_480x800_ST7701S_ROTATE90"
#define TCFG_LCD_BL_VALUE                   1
#define TCFG_LCD_RESET_IO                   IO_PORTB_00
#define TCFG_LCD_BL_IO                      IO_PORTB_01
#define TCFG_LCD_RS_IO                      -1
#define TCFG_LCD_CS_IO                      -1
#define TCFG_LCD_TE_ENABLE                  0
#define TCFG_LCD_TE_IO                      -1
#define TCFG_LCD_SPI_INTERFACE              NULL
#endif


//*********************************************************************************//
//                               定义触摸使能                                      //
//*********************************************************************************//
#define TCFG_TP_DRIVER_ENABLE               1
#define TCFG_TOUCH_GT1151_ENABLE            0
#define TCFG_TOUCH_FT6236_ENABLE            0
#define TCFG_TOUCH_GT911_ENABLE             0
#define TCFG_TOUCH_PL6133_ENABLE            0
#define TCFG_TOUCH_CST3240_ENABLE           0
#define TCFG_TOUCH_GT9271_ENABLE            0

/*
 * TP旋转坐标常用的配置参数
 * ---------------------------------------------------
 *    配置   |  逆时针90° |  旋转180° |  逆时针270° |
 * ---------------------------------------------------
 *  SWAP_X_Y |     1      |     0     |      1      |
 * ---------------------------------------------------
 *  X_MIRROR |     0      |     1     |      1      |
 * ---------------------------------------------------
 *  Y_MIRROR |     1      |     1     |      0      |
 * ---------------------------------------------------
*/
#define TCFG_TP_SWAP_X_Y                    1///< 是否交换TP的X和Y坐标
#define TCFG_TP_X_MIRROR                    0///< 是否以TP的X中心轴镜像y坐标。
#define TCFG_TP_Y_MIRROR                    1///< 是否以TP的Y中心轴镜像x坐标。
#define TCFG_TP_RST_PIN                     IO_PORTE_06
#define TCFG_TP_INT_PIN                     IO_PORTA_03
#define TCFG_TP_COMMUNICATE_IF              "iic0"

#endif


//*********************************************************************************//
//                                   PWM配置                                       //
//*********************************************************************************//
#define TCFG_PWM0_ENABLE                    0
#define TCFG_PWM0_TIMER_PWM_REMAP_IO        { -1/*PWM2*/, -1/*PWM3*/, -1/*PWM4*/, -1/*PWM5*/, }
#define TCFG_PWM0_MCPWM_REMAP_IO            {\
                                                IO_PORTC_00/*MCPWM0H*/, IO_PORTC_01/*MCPWM1H*/, IO_PORTC_02/*MCPWM2H*/, IO_PORTC_03/*MCPWM3H*/,\
                                                IO_PORTC_04/*MCPWM0L*/, IO_PORTC_05/*MCPWM1L*/, IO_PORTC_06/*MCPWM2L*/, IO_PORTC_07/*MCPWM3L*/,\
                                            }
#define TCFG_PWM0_CH_MAPPING                PWMCH0_H | PWMCH0_L | PWMCH1_H | PWMCH1_L | PWMCH2_H | PWMCH2_L | PWMCH3_H | PWMCH3_L
#define TCFG_PWM0_FREQUENCY                 3000000
#define TCFG_PWM0_DUTY                      50
#define TCFG_PWM0_DECIMAL_POINT             0              //占空比小数点精度位: 0<freq<=4K,point_bit=2;4K<freq<=40K,point_bit=1; freq>40K,point_bit=0;

#define TCFG_PWM1_ENABLE                    0
#define TCFG_PWM1_TIMER_PWM_REMAP_IO        { IO_PORTA_07/*PWM2*/, -1/*PWM3*/, -1/*PWM4*/, -1/*PWM5*/, }
#define TCFG_PWM1_MCPWM_REMAP_IO            {\
                                                -1/*MCPWM0H*/, -1/*MCPWM1H*/, -1/*MCPWM2H*/, -1/*MCPWM3H*/,\
                                                -1/*MCPWM0L*/, -1/*MCPWM1L*/, -1/*MCPWM2L*/, -1/*MCPWM3L*/,\
                                            }
#define TCFG_PWM1_CH_MAPPING                PWM_TIMER2_OPCH
#define TCFG_PWM1_FREQUENCY                 2000000
#define TCFG_PWM1_DUTY                      50
#define TCFG_PWM1_DECIMAL_POINT             0              //占空比小数点精度位: 0<freq<=4K,point_bit=2;4K<freq<=40K,point_bit=1; freq>40K,point_bit=0;

#define TCFG_PWM2_ENABLE                    0
#define TCFG_PWM2_TIMER_PWM_REMAP_IO        { -1/*PWM2*/, IO_PORTA_07/*PWM3*/, -1/*PWM4*/, -1/*PWM5*/, }
#define TCFG_PWM2_MCPWM_REMAP_IO            {\
                                                -1/*MCPWM0H*/, -1/*MCPWM1H*/, -1/*MCPWM2H*/, -1/*MCPWM3H*/,\
                                                -1/*MCPWM0L*/, -1/*MCPWM1L*/, -1/*MCPWM2L*/, -1/*MCPWM3L*/,\
                                            }
#define TCFG_PWM2_CH_MAPPING                PWM_TIMER3_OPCH
#define TCFG_PWM2_FREQUENCY                 32768
#define TCFG_PWM2_DUTY                      50
#define TCFG_PWM2_DECIMAL_POINT             0              //占空比小数点精度位: 0<freq<=4K,point_bit=2;4K<freq<=40K,point_bit=1; freq>40K,point_bit=0;

#define TCFG_PWM3_ENABLE                    0
#define TCFG_PWM3_TIMER_PWM_REMAP_IO        { -1/*PWM2*/, -1/*PWM3*/, IO_PORTA_07/*PWM4*/, -1/*PWM5*/, }
#define TCFG_PWM3_MCPWM_REMAP_IO            {\
                                                -1/*MCPWM0H*/, -1/*MCPWM1H*/, -1/*MCPWM2H*/, -1/*MCPWM3H*/,\
                                                -1/*MCPWM0L*/, -1/*MCPWM1L*/, -1/*MCPWM2L*/, -1/*MCPWM3L*/,\
                                            }
#define TCFG_PWM3_CH_MAPPING                PWM_TIMER4_OPCH
#define TCFG_PWM3_FREQUENCY                 32768
#define TCFG_PWM3_DUTY                      50
#define TCFG_PWM3_DECIMAL_POINT             0              //占空比小数点精度位: 0<freq<=4K,point_bit=2;4K<freq<=40K,point_bit=1; freq>40K,point_bit=0;


//*********************************************************************************//
//                                  AD按键配置                                     //
//*********************************************************************************//
#define TCFG_ADKEY_ENABLE                   1              //AD按键
#define TCFG_PRESS_LONG_KEY_POWERON_ENABLE  TCFG_ADKEY_ENABLE       //长按开关机功能
#define TCFG_ADKEY_INPUT_IO                 IO_PORTD_08
#define TCFG_ADKEY_INPUT_CHANNEL            ADC_IO_CH_PD08

#define ADKEY_UPLOAD_R                      22             //上拉电阻值
#define TCFG_ADC_LEVEL_09                   0x3FF
#define TCFG_ADC_LEVEL_08                   0x3FF
#define TCFG_ADC_LEVEL_07                   0x3FF
#define TCFG_ADC_LEVEL_06                   0x3FF
#define TCFG_ADC_LEVEL_05                   0x3FF
#define TCFG_ADC_LEVEL_04                   (ADC_VDDIO * 100 / (100 + ADKEY_UPLOAD_R))
#define TCFG_ADC_LEVEL_03                   (ADC_VDDIO * 33  / (33  + ADKEY_UPLOAD_R))
#define TCFG_ADC_LEVEL_02                   (ADC_VDDIO * 15  / (15  + ADKEY_UPLOAD_R))
#define TCFG_ADC_LEVEL_01                   (ADC_VDDIO * 51  / (51  + ADKEY_UPLOAD_R * 10))
#define TCFG_ADC_LEVEL_00                   (0)

#define TCFG_ADKEY_VALUE_0                  KEY_POWER
#define TCFG_ADKEY_VALUE_1                  KEY_MODE
#define TCFG_ADKEY_VALUE_2                  KEY_UP
#define TCFG_ADKEY_VALUE_3                  KEY_DOWN
#define TCFG_ADKEY_VALUE_4                  KEY_OK
#define TCFG_ADKEY_VALUE_5                  KEY_CANCLE
#define TCFG_ADKEY_VALUE_6                  KEY_ENC
#define TCFG_ADKEY_VALUE_7                  KEY_PHOTO
#define TCFG_ADKEY_VALUE_8                  KEY_F1
#define TCFG_ADKEY_VALUE_9                  NO_KEY


//*********************************************************************************//
//                                    IR配置                                       //
//*********************************************************************************//
#define TCFG_IRKEY_ENABLE                   0
#define TCFG_IRKEY_TIMER_INDEX              5
#define TCFG_IRKEY_INPUT_IO                 IO_PORTC_10


//*********************************************************************************//
//                                   QDEC配置                                      //
//*********************************************************************************//
#define TCFG_RDEC_KEY_ENABLE                0
#define TCFG_QDEC0_ENABLE                   1
#define TCFG_QDEC0_MODE                     RDEC_PHASE_1
#define TCFG_QDEC0_CLK_SPND                 0xf
#define TCFG_QDEC0_INPUT_IO_A               IO_PORTE_12
#define TCFG_QDEC0_INPUT_IO_B               IO_PORTE_13
#define TCFG_QDEC0_KEY_VALUE_A              KEY_VOLUME_INC
#define TCFG_QDEC0_KEY_VALUE_B              KEY_VOLUME_DEC


//*********************************************************************************//
//                                  IO按键配置                                     //
//*********************************************************************************//
#define TCFG_IOKEY_ENABLE                   0
#define TCFG_IOKEY_INPUT0_ENABLE            1
#define TCFG_IOKEY_INPUT0_CONNECT_WAY       ONE_PORT_TO_LOW
#define TCFG_IOKEY_INPUT0_IO                IO_PORTC_00
#define TCFG_IOKEY_INPUT0_VALUE             KEY_VOLUME_DEC
#define TCFG_IOKEY_INPUT1_ENABLE            1
#define TCFG_IOKEY_INPUT1_CONNECT_WAY       ONE_PORT_TO_LOW
#define TCFG_IOKEY_INPUT1_IO                IO_PORTC_01
#define TCFG_IOKEY_INPUT1_VALUE             KEY_VOLUME_INC
#define TCFG_IOKEY_INPUT2_ENABLE            1
#define TCFG_IOKEY_INPUT2_CONNECT_WAY       ONE_PORT_TO_LOW
#define TCFG_IOKEY_INPUT2_IO                IO_PORTC_02
#define TCFG_IOKEY_INPUT2_VALUE             KEY_MODE


//*********************************************************************************//
//                                 触摸按键配置                                    //
//*********************************************************************************//
#define TCFG_TOUCH_KEY_ENABLE               0
#define TOUCH_KEY_CLOCK_SOURCE              TOUCH_KEY_CLK_PLL_480M
#define TCFG_TOUCH_KEY0_ENABLE              1
#define TCFG_TOUCH_KEY0_PORT                IO_PORTC_09
#define TCFG_TOUCH_KEY0_VALUE               KEY_OK
#define TCFG_TOUCH_KEY0_PRESS_DELTA         100
#define TCFG_TOUCH_KEY1_ENABLE              0
#define TCFG_TOUCH_KEY1_PORT                IO_PORTA_00
#define TCFG_TOUCH_KEY1_VALUE               KEY_VOLUME_DEC
#define TCFG_TOUCH_KEY1_PRESS_DELTA         100
#define TCFG_TOUCH_KEY2_ENABLE              0
#define TCFG_TOUCH_KEY2_PORT                IO_PORTC_08
#define TCFG_TOUCH_KEY2_VALUE               KEY_VOLUME_INC
#define TCFG_TOUCH_KEY2_PRESS_DELTA         100


//*********************************************************************************//
//                                 ETH PHY配置                                     //
//*********************************************************************************//
#define TCFG_ETH_ENABLE                     0
#define TCFG_ETH_PHY_DEVICE_NAME            "dp83848"      //"rtl8201e"
#define TCFG_ETH_PHY_SPEED                  PHY_FULLDUPLEX_100M
#define TCFG_ETH_IRQ_PRIO                   1              //-1为查询  0-7 使用中断的优先级
#define TCFG_ETH_HD_LEVEL                   0
#define TCFG_ETH_RX_TASK_PRIO               2
#define TCFG_ETH_RMII_BUS_CLK_IO            IO_PORTE_04
#define TCFG_ETH_RMII_BUS_DAT_IO            IO_PORTE_05
#define TCFG_ETH_RMII_BUS_RESET_IO          IO_PORTE_03
#define TCFG_ETH_RMII_BUS_HD_LEVEL          1


//*********************************************************************************//
//                                 WIFI配置                                        //
//*********************************************************************************//
#ifdef CONFIG_NET_ENABLE
#define TCFG_WIFI_ENABLE                    1
#endif


//*********************************************************************************//
//                                  USB相关配置                                    //
//*********************************************************************************//
#if defined CONFIG_VIDEO_ENABLE
#define TCFG_HOST_UVC_ENABLE                1              //UVC主机功能
#endif
#if defined CONFIG_NET_ENABLE
#define TCFG_HOST_WIRELESS_ENABLE           0
#define TCFG_ADB_ENABLE                     0              //usb虚拟网卡
#endif
#define TCFG_HOST_RNDIS_ENABLE              0

#include "usb_std_class_def.h"
#include "usb_common_def.h"

#if (USB_DEVICE_CLASS_CONFIG & SPEAKER_CLASS) || (USB_DEVICE_CLASS_CONFIG_2_0 & SPEAKER_CLASS)
#define TCFG_USB_SLAVE_AUDIO_SPK_ENABLE     1              // UAC从机SPK使能
#else
#define TCFG_USB_SLAVE_AUDIO_SPK_ENABLE     0              // UAC从机SPK使能
#endif
#if (USB_DEVICE_CLASS_CONFIG & MIC_CLASS) || (USB_DEVICE_CLASS_CONFIG_2_0 & MIC_CLASS)
#define TCFG_USB_SLAVE_AUDIO_MIC_ENABLE     1              // UAC从机MIC使能
#else
#define TCFG_USB_SLAVE_AUDIO_MIC_ENABLE     0              // UAC从机MIC使能
#endif

#define TCFG_EXTFLASH_ENABLE                TCFG_EXTFLASH_UDISK_ENABLE   //截取flash中的一段空间作为extflash


//*********************************************************************************//
//                              电源低功耗配置                                     //
//*********************************************************************************//
#define TCFG_POWER_MODE                     PWR_DCDC15
#define TCFG_POWER_AVDD18_ENABLE            1
#define TCFG_POWER_AVDD28_ENABLE            1

#define TCFG_LOW_POWER_WARN_TIME            (60 * 1000)    //低电提醒时间，单位秒
#define TCFG_LOW_POWER_AUTO_SHUTDOWN_ENABLE 0              //空闲自动倒数关机
#define TCFG_POWER_DVD_DCV_SUPPLY_MODE      0              // 0-DVD和DCV短接 1-DVD和DCV内部独立供电

#define TCFG_LOW_POWER_SHUTDOWN             320            //低电直接关机电压
#define TCFG_LOW_POWER_OFF_VAL              330            //低电关机电压
#define TCFG_LOW_POWER_WARN_VAL             340            //低电提醒电压
#define TCFG_LOWPOWER_VDDIOM_LEVEL          VDDIOM_VOL_330V//强VDDIO电压档位，不要高于外部DCDC的电压

#define TCFG_LOWPOWER_VDDIOW_LEVEL          VDDIOW_VOL_200V//弱VDDIO电压档位
#if TCFG_POWER_DVD_DCV_SUPPLY_MODE
#define TCFG_LOWPOWER_VDC14_LEVEL           DCVDD_VOL_155V
#else
#define TCFG_LOWPOWER_VDC14_LEVEL           DCVDD_VOL_140V
#endif
#define TCFG_LOWPOWER_FUNCTION              LOWPOWER_CLOSE
#define TCFG_LOWPOWER_OSC_TYPE              OSC_TYPE_LRC

#define TCFG_LOWPOWER_WAKEUP_PORT0_ENABLE   1
#define TCFG_LOWPOWER_WAKEUP_PORT0_IO       IO_PORTD_00
#define TCFG_LOWPOWER_WAKEUP_PORT0_EDGE     FALLING_EDGE
#define TCFG_LOWPOWER_WAKEUP_PORT0_FILTER   PORT_FLT_DISABLE

#define TCFG_LOWPOWER_WAKEUP_PORT1_ENABLE   0
#define TCFG_LOWPOWER_WAKEUP_PORT1_IO       IO_PORTA_02
#define TCFG_LOWPOWER_WAKEUP_PORT1_EDGE     FALLING_EDGE
#define TCFG_LOWPOWER_WAKEUP_PORT1_FILTER   PORT_FLT_DISABLE

#define TCFG_LOWPOWER_WAKEUP_PORT2_ENABLE   0
#define TCFG_LOWPOWER_WAKEUP_PORT2_IO       IO_PORTA_03
#define TCFG_LOWPOWER_WAKEUP_PORT2_EDGE     FALLING_EDGE
#define TCFG_LOWPOWER_WAKEUP_PORT2_FILTER   PORT_FLT_DISABLE


//*********************************************************************************//
//                                  RTC配置                                        //
//*********************************************************************************//
#define TCFG_RTC_ENABLE                     1
#define TCFG_RTC_CLK_SEL                    CLK_SEL_32K
#define TCFG_RTC_X32XS_LEVEL                X32XS_LEVEL_1


//*********************************************************************************//
//                                 VIDEO配置                                       //
//*********************************************************************************//
#ifdef CONFIG_VIDEO_ENABLE

#define CONFIG_VIDEO0_ENABLE
#define CONFIG_VIDEO1_ENABLE
#if TCFG_HOST_UVC_ENABLE
#define CONFIG_VIDEO2_ENABLE
#endif
#define CONFIG_VIDEO3_ENABLE

/*video0的IO组和硬件IO */
#ifdef CONFIG_VIDEO0_ENABLE
#define TCFG_CAMERA0_GROUP_PORT             ISC_GROUPA
#define TCFG_VIDEO0_CAMERA_XCLOCK           IO_PORTD_08
#define TCFG_VIDEO0_CAMERA_RESET            -1
#define TCFG_VIDEO0_CAMERA_PWDN             -1
#define TCFG_VIDEO0_CAMERA_INTERFACE        0//SEN_INTERFACE0
#endif // CONFIG_VIDEO0_ENABLE

#ifdef CONFIG_VIDEO1_ENABLE
#define TCFG_CAMERA1_GROUP_PORT             ISC_GROUPB
#define TCFG_VIDEO1_CAMERA_XCLOCK           IO_PORTC_05
#define TCFG_VIDEO1_CAMERA_RESET            -1
#define TCFG_VIDEO1_CAMERA_PWDN             -1
#define TCFG_VIDEO1_CAMERA_INTERFACE        1//SEN_INTERFACE0
#endif // CONFIG_VIDEO0_ENABLE

/*video3的IO组和硬件IO */
#ifdef CONFIG_VIDEO3_ENABLE
#define TCFG_VIDEO3_CAMERA_XCLOCK           IO_PORTE_10
#define TCFG_VIDEO3_CAMERA_RESET            IO_PORTE_12
#define TCFG_VIDEO3_CAMERA_PWDN             IO_PORTE_11
#define TCFG_VIDEO3_CAMERA_INTERFACE        2//SEN_INTERFACE_CSI2
#endif // CONFIG_VIDEO3_ENABLE

#define TCFG_SLAVE_UVC0_JPEG_DATA_SOURCE    "video3.2"
#define TCFG_SLAVE_UVC1_JPEG_DATA_SOURCE    "video0.2"
#define TCFG_SLAVE_UVC0_YUV_DATA_SOURCE     "video3.2"
#define TCFG_SLAVE_UVC1_YUV_DATA_SOURCE     "video0.2"
#define TCFG_SLAVE_UVC_YUV_DATA_OUT_WIDTH   640
#define TCFG_SLAVE_UVC_YUV_DATA_OUT_HEIGHT  480

#define TCFG_YUV_DATA_SOURCE                "video0.2"
#define TCFG_YUV_DATA_OUT_WIDTH             640
#define TCFG_YUV_DATA_OUT_HEIGHT            480

#endif // CONFIG_VIDEO_ENABLE


#endif
