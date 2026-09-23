#ifdef CONFIG_BOARD_DEMO

//*********************************************************************************//
//                                功能模块配置                                     //
//*********************************************************************************//
#define CONFIG_SFC_ENABLE
#define CONFIG_NET_ENABLE
// #define CONFIG_NO_SDRAM_ENABLE                             //关闭sdram

//*********************************************************************************//
//                                   时钟配置                                      //
//*********************************************************************************//
#define TCFG_OSC_FREQUENCY                  24000000
#define TCFG_SYS_CLK                        192000000         //240M,192M,160M,120M,96M,80M,64M,60M,48M,40M,32M,24M，其他值时启用SYS_PLL
#define TCFG_LSB_CLK                        48000000          //96M,80M,60M,48M,40M,24M,20M,12M
#define TCFG_HSB_CLK_DIV                    2                 //HSB_CLK = SYS_CLK / HSB_CLK_DIV
#define TCFG_SFCTZ_CLK                      48000000          //SFC时钟，和加载代码的速度有关
#define TCFG_SDRAM_CLK                      200000000         //SDRAM/DDR时钟


//*********************************************************************************//
//                                  flash配置                                      //
//*********************************************************************************//
/*
#data_width[1 2 3 4] 3的时候uboot自动识别2或者4线
#clkdiv [1-255] SPITZ_CLK=SYS_CLK/HSB_CLK_DIV/clkdiv
#mode:
#	  0 RD_OUTPUT,		 1 cmd 		 1 addr
#	  1 RD_I/O,   		 1 cmd 		 x addr
#	  2 RD_I/O_CONTINUE] no_send_cmd x add
#port:固定0
*/
#define TCFG_SPITZ_WIDTH_CLKDIV_MODE_PORT   4_3_0_0

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
#define TCFG_DEBUG_PORT                     IO_PORTD_01
#define TCFG_UBOOT_DEBUG_PORT               PD01

#define TCFG_UART0_ENABLE                   1              //UART0默认用来打印口
#define TCFG_UART0_TX_IO                    TCFG_DEBUG_PORT
#define TCFG_UART0_RX_IO                    IO_PORTE_11    //-1
#define TCFG_UART0_BAUDRATE                 1000000
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


//*********************************************************************************//
//                                 ETH PHY配置                                     //
//*********************************************************************************//
#define TCFG_ETH_ENABLE                     1
#define TCFG_ETH_PHY_DEVICE_NAME            "rtl8201e"     //"dp83848"
#define TCFG_ETH_PHY_SPEED                  PHY_FULLDUPLEX_100M
#define TCFG_ETH_IRQ_PRIO                   1              //-1为查询  0-7 使用中断的优先级
#define TCFG_ETH_HD_LEVEL                   0
#define TCFG_ETH_RX_TASK_PRIO               2
#define TCFG_ETH_RMII_BUS_CLK_IO            IO_PORTE_04
#define TCFG_ETH_RMII_BUS_DAT_IO            IO_PORTE_05
#define TCFG_ETH_RMII_BUS_HD_LEVEL          1


//*********************************************************************************//
//                              电源低功耗配置                                     //
//*********************************************************************************//
#define TCFG_POWER_MODE                     PWR_DCDC15
#define TCFG_POWER_AVDD18_ENABLE            1
#define TCFG_POWER_AVDD28_ENABLE            1

#define TCFG_LOWPOWER_VDDIOM_LEVEL          VDDIOM_VOL_330V//强VDDIO电压档位
#define TCFG_LOWPOWER_VDDIOW_LEVEL          VDDIOW_VOL_200V //弱VDDIO电压档位
#define TCFG_LOWPOWER_VDC14_LEVEL           DCVDD_VOL_140V
#define TCFG_LOWPOWER_FUNCTION              LOWPOWER_CLOSE
#define TCFG_LOWPOWER_OSC_TYPE              OSC_TYPE_LRC

#define TCFG_LOWPOWER_WAKEUP_PORT0_ENABLE   0
#define TCFG_LOWPOWER_WAKEUP_PORT0_IO       IO_PORTA_01
#define TCFG_LOWPOWER_WAKEUP_PORT0_EDGE     FALLING_EDGE
#define TCFG_LOWPOWER_WAKEUP_PORT0_FILTER   PORT_FLT_DISABLE


//*********************************************************************************//
//                                 WIFI配置                                        //
//*********************************************************************************//
#ifdef CONFIG_NET_ENABLE

#define TCFG_WIFI_ENABLE                    0               //内置 WIFI
#define TCFG_EXT_WIFI_ENABLE                1               //外挂 WIFI
#define TCFG_LTE_PHY_ENABLE                 0               //USB  WIFI

#if TCFG_EXT_WIFI_ENABLE
#define TCFG_RTL8189E_ENABLE                1
#define TCFG_RTL8189F_ENABLE                0
#define TCFG_RTL8822ES_10M_ENABLE           0
#define TCFG_RTL8822CS_ENABLE               0
#define TCFG_RTL8733BS_ENABLE               0
#define TCFG_AIC8800_ENABLE                 0
#endif

#endif


//*********************************************************************************//
//                                  USB配置                                        //
//*********************************************************************************//
#define TCFG_FUSB_DEVICE                    BIT(0)
#define TCFG_HUSB_DEVICE                    BIT(1)
#define TCFG_USB_DEVICE                     TCFG_FUSB_DEVICE// | TCFG_HUSB_DEVICE

//*********************************************************************************//
//                                USB从机配置                                      //
//*********************************************************************************//
#define TCFG_PC_ENABLE                      0              //使用USB从机功能一定要打开
#define USB_PC_NO_APP_MODE                  2
#define USB_MALLOC_ENABLE                   1

//*********************************************************************************//
//                                USB主机配置                                      //
//*********************************************************************************//
#if TCFG_LTE_PHY_ENABLE
#define TCFG_HOST_WIRELESS_ENABLE           1
#define TCFG_ADB_ENABLE                     1              //usb虚拟网卡
#endif

#include "usb_std_class_def.h"
#include "usb_common_def.h"


#endif
