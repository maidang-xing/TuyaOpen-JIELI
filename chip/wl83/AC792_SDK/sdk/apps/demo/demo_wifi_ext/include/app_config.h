#ifndef APP_CONFIG_H
#define APP_CONFIG_H

#include "board_config.h"


#define CONFIG_DEBUG_ENABLE                     //打印开关

#ifdef CONFIG_SFC_ENABLE
#ifdef CONFIG_NO_SDRAM_ENABLE
#define CONFIG_RF_TRIM_CODE_MOVABLE             //把RF TRIM 的运行代码动态加载到ram运行(节省4K ram内存), 防止RF TRIM 期间500ms大电流访问flash造成flash挂掉持续大电流
#else
#define CONFIG_RF_TRIM_CODE_AT_RAM              //把RF TRIM 的运行代码定死到ram运行(浪费4K ram内存,否则若动态加载到sdram需清cache), 防止RF TRIM 期间500ms大电流访问flash造成flash挂掉持续大电流
#endif
#endif

#define CONFIG_ASSIGN_MACADDR_ENABLE            //第一次开机连上外网后，使用杰理服务器分配WIFI模块的MAC地址, 关闭则使用<蓝牙地址更新工具*.exe>或者随机数作为MAC地址
#define CONFIG_IPERF_ENABLE       				//iperf测试
//#define CONFIG_AIRKISS_NET_CFG                //AIRKISS配网
//#define CONFIG_STATIC_IPADDR_ENABLE           //记忆路由器分配的IP,下次直接使用记忆IP节省DHCP时间
#define CONFIG_RTOS_STACK_CHECK_ENABLE
// #define CONFIG_MEM_LEAK_CHECK_ENABLE         //是否启用内存泄漏检查(需要包含mem_leak_test.h头文件)
//#define TCFG_EXT_RF_FCC_TEST_ENABLE 1

#define AP_TEST_MODE       0
#define STA_TEST_MODE      1
#define P2P_TEST_MODE 	   2
#define MONITOR_TEST_MODE  3

#define EXT_WIFI_TEST_MODE AP_TEST_MODE
#define EXT_WIFI_AP_SSID   "AC79_EXT_WIFI_"    //配置外挂wifi的AP模式的SSID前缀
#define EXT_WIFI_AP_PWD    "12345678"          //配置外挂wifi的AP模式的密码
#define EXT_WIFI_STA_SSID  "WL83"              //配置外挂wifi的STA模式的SSID前缀
#define EXT_WIFI_STA_PWD   "12345678"          //配置外挂wifi的STA模式的密码

#define WIFI_TEST_MODE AP_TEST_MODE
#define WIFI_AP_SSID       "AC79_WIFI_"        //配置内置wifi的AP模式的SSID前缀
#define WIFI_AP_PWD        "12345678"          //配置内置wifi的AP模式的密码
#define WIFI_STA_SSID      "WL83"              //配置内置wifi的STA模式的SSID前缀
#define WIFI_STA_PWD       "12345678"          //配置内置wifi的STA模式的密码

#ifdef CONFIG_RELEASE_ENABLE
#define LIB_DEBUG    0
#else
#define LIB_DEBUG    1
#endif
#define CONFIG_DEBUG_LIB(x)         (x & LIB_DEBUG)

#endif

