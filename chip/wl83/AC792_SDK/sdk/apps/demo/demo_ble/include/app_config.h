#ifndef APP_CONFIG_H
#define APP_CONFIG_H

#include "board_config.h"

#define CONFIG_DEBUG_ENABLE                             //打印开关

#define CONFIG_RTOS_STACK_CHECK_ENABLE                  //是否启用定时检查任务栈
// #define CONFIG_MEM_LEAK_CHECK_ENABLE                 //是否启用内存泄漏检查(需要包含mem_leak_test.h头文件)


//*********************************************************************************//
//                                  BT_BLE配置                                     //
//*********************************************************************************//
#ifdef CONFIG_BT_ENABLE

#define TCFG_BT_MODE                            BT_NORMAL   //BT_BQB

#define TCFG_USER_BLE_ENABLE                    1   //BLE功能使能
#define TCFG_USER_BT_CLASSIC_ENABLE             0   //经典蓝牙功能
#define TCFG_POWER_ON_ENABLE_BLE                0   //开机自动打开BLE

#define TCFG_TRANS_MULTI_BLE_SLAVE_NUMS         1
#define TCFG_TRANS_MULTI_BLE_MASTER_NUMS        2

#define RCSP_MODE_EN                            (1 << 0)
#define TRANS_DATA_EN                           (1 << 1)
#define LL_SYNC_EN                              (1 << 2)
#define TUYA_DEMO_EN                            (1 << 3)
#define ANCS_CLIENT_EN                          (1 << 4)
#define GFPS_EN                                 (1 << 5)
#define REALME_EN                               (1 << 6)
#define TME_EN                                  (1 << 7)
#define DMA_EN                                  (1 << 8)
#define GMA_EN                                  (1 << 9)
#define MMA_EN                                  (1 << 10)
#define FMNA_EN                                 (1 << 11)
#define SWIFT_PAIR_EN                           (1 << 12)
#define LE_AUDIO_CIS_RX_EN                      (1 << 13)
#define LE_AUDIO_CIS_TX_EN                      (1 << 14)
#define LE_AUDIO_BIS_RX_EN                      (1 << 15)
#define LE_AUDIO_BIS_TX_EN                      (1 << 16)
#define HONOR_EN                                (1 << 17)
#define ONLINE_DEBUG_EN                         (1 << 18)
#define CUSTOM_DEMO_EN                          (1 << 19)   // 第三方协议的demo，用于示例客户开发自定义协议
#define MULTI_BOX_ADV_EN                        (1 << 20)
#define MIJIA_EN                                (1 << 21)
#define CLIENT_EN                               (1 << 27)
#define DUEROS_EN                               (1 << 28)
#define NET_CFG_EN                              (1 << 29)
#define LE_HOGP_EN                              (1 << 30)
#define ALIPAY_EN                               (1 << 31)

#define THIRD_PARTY_PROTOCOLS_SEL               CUSTOM_DEMO_EN

#endif

#ifdef CONFIG_RELEASE_ENABLE
#define LIB_DEBUG    0
#else
#define LIB_DEBUG    1
#endif
#define CONFIG_DEBUG_LIB(x)         (x & LIB_DEBUG)

#endif

