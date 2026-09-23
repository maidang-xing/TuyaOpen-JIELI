#ifndef APP_CONFIG_H
#define APP_CONFIG_H

#define AUDIO_ENC_SAMPLE_SOURCE_MIC         0
#define AUDIO_ENC_SAMPLE_SOURCE_PLNK0       1
#define AUDIO_ENC_SAMPLE_SOURCE_PLNK1       2
#define AUDIO_ENC_SAMPLE_SOURCE_IIS0        3
#define AUDIO_ENC_SAMPLE_SOURCE_IIS1        4
#define AUDIO_ENC_SAMPLE_SOURCE_LINEIN      5

#define CONFIG_AUDIO_DEC_PLAY_SOURCE        "dac"

#include "sdk_config.h"

#include "board_config.h"

//*********************************************************************************//
//                                 应用相关配置                                    //
//*********************************************************************************//
//PA使能
//此宏只控制了应用相关配置:WIFI增益等参数.
//PA生效需要wifi_conf.c的WIFI_PA_ENABLE变量要手动置1
#define BBM_WIFI_PA_ENABLE                  1

//音频编码使用opus. 默认为pcm.
//使能opus需要修改可视化工具配置,输出对应的stream.bin
#define BBM_AUDIO_OPUS_ENABLE               0


#define CONFIG_VIDEO_DEC_ENABLE             1


#if TCFG_IIS_NODE_ENABLE
#undef TCFG_ESCO_DL_CVSD_SR_USE_16K
#define TCFG_ESCO_DL_CVSD_SR_USE_16K            0
#endif
#ifndef CONFIG_BT_ENABLE
#undef TCFG_APP_BT_EN
#define TCFG_APP_BT_EN                          0
#endif
#ifndef CONFIG_NET_ENABLE
#undef TCFG_APP_NET_MUSIC_EN
#define TCFG_APP_NET_MUSIC_EN                   0
#endif
#if !defined TCFG_PC_ENABLE || !TCFG_PC_ENABLE
#undef TCFG_APP_PC_EN
#define TCFG_APP_PC_EN                          0
#endif



//*********************************************************************************//
//                                 资源分配相关配置                                //
//*********************************************************************************//
#ifdef CONFIG_SDFILE_EXT_ENABLE

#undef CONFIG_SFC_ENABLE
#undef __FLASH_SIZE__
#define __FLASH_SIZE__    (16 * 1024 * 1024)

#define CONFIG_SDNAND_HFS_LEN_TEXT  16M
#define CONFIG_SDNAND_HFAT_LEN_TEXT 4G
#define CONFIG_SDNAND_FAT1_LEN_TEXT 8G
#define CONFIG_SDNAND_HFS_LEN       (16llu * 1024 * 1024)
#define CONFIG_SDNAND_HFAT_LEN      (4llu * 1024 * 1024 * 1024)
#define CONFIG_SDNAND_FAT1_LEN      (8llu * 1024 * 1024 * 1024)

//每个簇有多少个block，比如簇大小设置为32768时，该值为32768 / 512 = 0x40
#if CONFIG_SDNAND_HFAT_LEN > 0x80000000
#define CONFIG_SDNAND_HFAT_CLUSTER_SIZE 0x40
#elif CONFIG_SDNAND_HFAT_LEN > 0x40000000
#define CONFIG_SDNAND_HFAT_CLUSTER_SIZE 0x20
#elif CONFIG_SDNAND_HFAT_LEN > 0x20000000
#define CONFIG_SDNAND_HFAT_CLUSTER_SIZE 0x10
#elif CONFIG_SDNAND_HFAT_LEN > 0x10000000
#define CONFIG_SDNAND_HFAT_CLUSTER_SIZE 0x8
#elif CONFIG_SDNAND_HFAT_LEN > 0x8000000
#define CONFIG_SDNAND_HFAT_CLUSTER_SIZE 0x4
#elif CONFIG_SDNAND_HFAT_LEN > 0x4000000
#define CONFIG_SDNAND_HFAT_CLUSTER_SIZE 0x2
#else
#define CONFIG_SDNAND_HFAT_CLUSTER_SIZE 0x1
#endif

#if CONFIG_SDNAND_FAT1_LEN > 0x80000000
#define CONFIG_SDNAND_FAT1_CLUSTER_SIZE 0x40
#elif CONFIG_SDNAND_FAT1_LEN > 0x40000000
#define CONFIG_SDNAND_FAT1_CLUSTER_SIZE 0x20
#elif CONFIG_SDNAND_FAT1_LEN > 0x20000000
#define CONFIG_SDNAND_FAT1_CLUSTER_SIZE 0x10
#elif CONFIG_SDNAND_FAT1_LEN > 0x10000000
#define CONFIG_SDNAND_FAT1_CLUSTER_SIZE 0x8
#elif CONFIG_SDNAND_FAT1_LEN > 0x8000000
#define CONFIG_SDNAND_FAT1_CLUSTER_SIZE 0x4
#elif CONFIG_SDNAND_FAT1_LEN > 0x4000000
#define CONFIG_SDNAND_FAT1_CLUSTER_SIZE 0x2
#else
#define CONFIG_SDNAND_FAT1_CLUSTER_SIZE 0x1
#endif

#endif

//*********************************************************************************//
//                          预留区UI和AUDIO资源配置                                //
//*********************************************************************************//
//注意：ui和audio资源的起始地址和大小, 根据产品生命周期最大情况定义,根据实际需求进行配置
//FLASH后面4K用于一些配置存储，所以禁止覆盖
//具体说明和注意事项请阅读文档

//(1)ui和audio资源 ,如果存在ui资源则位于扩展预留区末尾,
//还存在audio则位于ui项前面，其他配置项则位于它们之前.
/*
#------------------------------|
#  (其他预留区配置项)          |
#------------------------------|<----CONFIG_UI_PACKRES_ADR - CONFIG_AUDIO_PACKRES_LEN = CONFIG_AUDIO_PACKRES_ADR
#  (CONFIG_AUDIO_PACKRES_LEN)  |
#------------------------------|<----__FLASH_SIZE__ - 0x1000 - CONFIG_UI_PACKRES_LEN = CONFIG_UI_PACKRES_ADR
#  (CONFIG_UI_PACKRES_LEN)     |
#------------------------------|<----__FLASH_SIZE__ - 0x1000
#  (4K Reserved)               |
#------------------------------+<----__FLASH_SIZE__
*/

//(2)只有audio资源,则将其位于扩展预留区末尾.
/*
#------------------------------|
#  (其他预留区配置项)          |
#------------------------------|<----__FLASH_SIZE__ - 0x1000 - CONFIG_AUDIO_PACKRES_LEN = CONFIG_AUDIO_PACKRES_ADR
#  (CONFIG_AUDIO_PACKRES_LEN)  |
#------------------------------|<----__FLASH_SIZE__ - 0x1000
#  (4K Reserved)               |
#------------------------------+<----__FLASH_SIZE__
*/

#if defined CONFIG_UI_ENABLE && !defined CONFIG_SDFILE_EXT_ENABLE
#define CONFIG_UI_FILE_SAVE_IN_RESERVED_EXPAND_ZONE //UI资源打包后放在扩展预留区
#endif

#if defined CONFIG_MEDIA_ENABLE && !defined CONFIG_SDFILE_EXT_ENABLE
#define CONFIG_VOICE_PROMPT_FILE_SAVE_IN_RESERVED_EXPAND_ZONE //AUDIO资源打包后放在扩展预留区
#endif

#if defined CONFIG_UI_FILE_SAVE_IN_RESERVED_EXPAND_ZONE
// #define CONFIG_UI_PACKRES_LEN 0x200000
#define CONFIG_UI_PACKRES_LEN 0x019000
#define CONFIG_UI_PACKRES_ADR ((__FLASH_SIZE__) - (CONFIG_UI_PACKRES_LEN) - 0x1000)
#endif

#if defined CONFIG_VOICE_PROMPT_FILE_SAVE_IN_RESERVED_EXPAND_ZONE
#if defined CONFIG_UI_FILE_SAVE_IN_RESERVED_EXPAND_ZONE
#define CONFIG_AUDIO_PACKRES_LEN 0xC800
#define CONFIG_AUDIO_PACKRES_ADR (CONFIG_UI_PACKRES_ADR - CONFIG_AUDIO_PACKRES_LEN)
#else
#define CONFIG_AUDIO_PACKRES_LEN 0xC800
#define CONFIG_AUDIO_PACKRES_ADR ((__FLASH_SIZE__) - CONFIG_AUDIO_PACKRES_LEN - 0x1000)
#endif
#endif

#define  CONFIG_LOGO_FILE_SAVE_IN_RESERVED_EXPAND_ZONE
#if defined CONFIG_LOGO_FILE_SAVE_IN_RESERVED_EXPAND_ZONE
#define CONFIG_LOGO_PACKRES_LEN 0x025800
#define CONFIG_LOGO_PACKRES_ADR ((__FLASH_SIZE__) - (CONFIG_UI_PACKRES_LEN) - 0x1000 - CONFIG_AUDIO_PACKRES_LEN - CONFIG_LOGO_PACKRES_LEN)
#endif




//*********************************************************************************//
//                                   DEBUG相关配置                                 //
//*********************************************************************************//
// #define CONFIG_FLOAT_DEBUG_ENABLE
// #define CONFIG_CPU_EFFICIENCY_CALCULATE_ENABLE
// #define CONFIG_ICACHE_EFFICIENCY_CALCULATE_ENABLE
#ifndef CONFIG_NO_SDRAM_ENABLE
// #define CONFIG_DCACHE_EFFICIENCY_CALCULATE_ENABLE
#endif

#define CONFIG_CXX_SUPPORT                      //使能C++支持
#define CONFIG_MPU_DEBUG_ENABLE
#define CONFIG_LZ4_COMPRESS_APP_CODE_ENABLE     //使用LZ4压缩代码

#ifdef CONFIG_SFC_ENABLE
#define CONFIG_LZ4_DATA_CODE_ENABLE             //使用LZ4压缩data段
#endif

#if TCFG_DEBUG_ENABLE
#define CONFIG_DEBUG_ENABLE                     //打印开关
#endif

#if TCFG_RTOS_STACK_CHECK_ENABLE
#define CONFIG_RTOS_STACK_CHECK_ENABLE          //是否启用定时检查任务栈
#endif

#if TCFG_SAVE_EXCEPTION_LOG_IN_FLASH
#define CONFIG_SAVE_EXCEPTION_LOG_IN_FLASH      //保存异常打印信息到flash
#endif

#if TCFG_MEM_LEAK_CHECK_ENABLE
#define CONFIG_MEM_LEAK_CHECK_ENABLE            //是否启用内存泄漏检查(需要包含mem_leak_test.h头文件)
#endif


//*********************************************************************************//
//                                  网络相关配置                                   //
//*********************************************************************************//
#define TCFG_AI_SERVER_DISABLE                  0
#define TCFG_DUER_ENABLE                        1

#ifdef CONFIG_NET_ENABLE

#ifdef CONFIG_SFC_ENABLE
#ifdef CONFIG_NO_SDRAM_ENABLE
#define CONFIG_RF_TRIM_CODE_MOVABLE             //把RF TRIM 的运行代码动态加载到ram运行(节省4K ram内存), 防止RF TRIM 期间500ms大电流访问flash造成flash挂掉持续大电流
#else
#define CONFIG_RF_TRIM_CODE_AT_RAM              //把RF TRIM 的运行代码定死到ram运行(浪费4K ram内存,否则若动态加载到sdram需清cache), 防止RF TRIM 期间500ms大电流访问flash造成flash挂掉持续大电流
#endif
#endif

//==============网络配置.json--网络性能测试================/
#if TCFG_IPERF_ENABLE
#define CONFIG_IPERF_ENABLE                     //iperf测试
#endif

//==============网络配置.json--IP地址相关配置==============/
#if TCFG_STATIC_IPADDR_ENABLE
// #define CONFIG_STATIC_IPADDR_ENABLE          //记忆路由器分配的IP,下次直接使用记忆IP节省DHCP时间
#endif
#if TCFG_ASSIGN_MACADDR_ENABLE
#define CONFIG_ASSIGN_MACADDR_ENABLE            //第一次开机连上外网后，使用杰理服务器分配WIFI模块的MAC地址, 关闭则使用<蓝牙地址更新工具*.exe>或者随机数作为MAC地址
#endif

//==============网络配置.json--配网相关配置==============/
#if TCFG_WIFI_ENABLE
// #define CONFIG_AIRKISS_NET_CFG               //AIRKISS配网
// #define CONFIG_WSC_NET_CFG                   //WSC配网
#endif

#if TCFG_ACOUSTIC_COMMUNICATION_NODE_ENABLE
#define CONFIG_ACOUSTIC_COMMUNICATION_ENABLE    //声波配网
#endif

//==============网络配置.json--第三方平台相关配置==========/
#if TCFG_SERVER_ASSIGN_PROFILE
#define CONFIG_SERVER_ASSIGN_PROFILE            //第三方平台的profile由杰理服务器分配
#endif
#if TCFG_PROFILE_UPDATE
#define CONFIG_PROFILE_UPDATE                   //每次开机都从杰理服务器获取第三方平台的profile,不读flash
#endif
#if TCFG_HTTP_SERVER_ENABLE
#define CONFIG_HTTP_SERVER_ENABLE               //HTTP服务器
#endif
#if TCFG_FTP_SERVER_ENABLE
#define CONFIG_FTP_SERVER_ENABLE                //FTP服务器
#endif
#if TCFG_DLNA_SDK_ENABLE
#define CONFIG_DLNA_SDK_ENABLE                  //打开DLNA音乐播放功能
#endif
#if TCFG_AI_SERVER == TCFG_DUER_ENABLE
#define CONFIG_DUER_SDK_ENABLE                  //使用百度平台
#elif TCFG_AI_SERVER == TCFG_AI_SERVER_DISABLE
// #define CONFIG_TURING_SDK_ENABLE             //使用图灵平台
// #define CONFIG_DUI_SDK_ENABLE                //使用思必驰DUI平台
// #define CONFIG_ALI_SDK_ENABLE                //使用天猫精灵平台
// #define CONFIG_TVS_SDK_ENABLE                //使用腾讯云平台
// #define CONFIG_TELECOM_SDK_ENABLE            //电信云平台
// #define CONFIG_JL_CLOUD_SDK_ENABLE           //打开使用杰理云平台

/*************电信云平台配网方式选择*************/
#ifdef CONFIG_TELECOM_SDK_ENABLE
#define CONFIG_APLINK_NET_CFG                   //电信AP配网。注意：1.电信AP配网不能与elink无感配网同时使能。2.wifi库需要支持ap
#ifndef CONFIG_APLINK_NET_CFG
#define CONFIG_ELINK_QLINK_NET_CFG              //电信elink无感配网。注意：elink无感配网不能与AIRKISS配网同时使能。
#endif
#define CONFIG_CTEI_DEVICE_ENABLE               //电信非蜂窝类串码对接设备使用
//#define CONFIG_MC_DEVICE_ENABLE               //电信mc接口类直连设备使用
#endif
#endif

#ifdef CONFIG_VIDEO_ENABLE
/*************绘本识别服务器*************/
#ifdef CONFIG_TURING_SDK_ENABLE
#define CONFIG_TURING_PAGE_TURNING_DET_ENABLE   //图灵翻页算法，需要配合图灵绘本平台使用
#endif

// #define CONFIG_WT_SDK_ENABLE                 //新玩瞳接口
// #define CONFIG_QR_CODE_NET_CFG                  //二维码配网
#endif

#endif


//*********************************************************************************//
//                                MEDIA功能配置                                    //
//*********************************************************************************//
#ifdef CONFIG_MEDIA_ENABLE

#ifndef TCFG_ADC0_INSIDE_BIAS_RESISTOR_ENABLE
#define TCFG_ADC0_INSIDE_BIAS_RESISTOR_ENABLE 0 //MIC0 BIAS是否使用内置电阻
#endif

#ifndef TCFG_ADC1_INSIDE_BIAS_RESISTOR_ENABLE
#define TCFG_ADC1_INSIDE_BIAS_RESISTOR_ENABLE 0 //MIC1 BIAS是否使用内置电阻
#endif

#define TCFG_AUDIO_LINEIN_ENABLE                TCFG_APP_LINEIN_EN
#define SYS_VOL_TYPE                            VOL_TYPE_DIGITAL    /*目前仅支持软件数字音量模式*/

/*
 *第三方ASR（语音识别）配置
 *(1)用户自己开发算法
 *#define TCFG_AUDIO_ASR_DEVELOP                ASR_CFG_USER_DEFINED
 *(2)使用思必驰ASR算法
 *#define TCFG_AUDIO_ASR_DEVELOP                ASR_CFG_AIS
 *(2)使华镇ASR算法
 *#define TCFG_AUDIO_ASR_DEVELOP                ASR_CFG_WANSON
 */
#define ASR_CFG_USER_DEFINED                    1
#define ASR_CFG_AIS                             2
#define ASR_CFG_WANSON                          3
#define TCFG_AUDIO_ASR_DEVELOP                  0

//#define CONFIG_AUDIO_ENC_AEC_DATA_CHECK      //打开查看AEC操作数据(mic/dac/aec数据)

/*使能iis输出外部参考数据*/
#if (TCFG_IIS_NODE_ENABLE == 1) && (TCFG_DAC_NODE_ENABLE == 0)
#define TCFG_AUDIO_CVP_OUTPUT_WAY_IIS_ENABLE    1 //回声消除参考数据为iis数据
#else
#define TCFG_AUDIO_CVP_OUTPUT_WAY_IIS_ENABLE    0 //回声消除参考数据为iis数据
#endif

/*Audio数据导出配置:通过蓝牙spp导出/sd写卡导出/uart写卡导出, 目前仅支持uart导出写卡*/
#define AUDIO_DATA_EXPORT_VIA_UART              1
#define AUDIO_DATA_EXPORT_VIA_SPP               2
#define AUDIO_DATA_EXPORT_VIA_SD                3
#define TCFG_AUDIO_DATA_EXPORT_DEFINE           0

#if TCFG_DATA_EXPORT_NODE_ENABLE
#undef TCFG_AUDIO_DATA_EXPORT_DEFINE
#define TCFG_AUDIO_DATA_EXPORT_DEFINE           AUDIO_DATA_EXPORT_VIA_UART
#endif

#if TCFG_AUDIO_CVP_SMS_ANS_MODE                 /*单MIC+ANS通话*/
#define TCFG_AUDIO_TRIPLE_MIC_ENABLE            0
#define TCFG_AUDIO_DUAL_MIC_ENABLE              0
#define TCFG_AUDIO_CVP_NS_MODE                  CVP_ANS_MODE
#define TCFG_AUDIO_DMS_SEL                      DMS_NORMAL
#elif (TCFG_AUDIO_CVP_SMS_DNS_MODE)             /*单MIC+DNS通话*/
#define TCFG_AUDIO_TRIPLE_MIC_ENABLE            0
#define TCFG_AUDIO_DUAL_MIC_ENABLE              0
#define TCFG_AUDIO_CVP_NS_MODE                  CVP_DNS_MODE
#define TCFG_AUDIO_DMS_SEL                      DMS_NORMAL
#elif (TCFG_AUDIO_CVP_DMS_ANS_MODE)             /*双MIC+ANS通话*/
#define TCFG_AUDIO_TRIPLE_MIC_ENABLE            0
#define TCFG_AUDIO_DUAL_MIC_ENABLE              1
#define TCFG_AUDIO_CVP_NS_MODE                  CVP_ANS_MODE
#define TCFG_AUDIO_DMS_SEL                      DMS_NORMAL
#elif (TCFG_AUDIO_CVP_DMS_DNS_MODE)             /*双MIC+DNS通话*/
#define TCFG_AUDIO_TRIPLE_MIC_ENABLE            0
#define TCFG_AUDIO_DUAL_MIC_ENABLE              1
#define TCFG_AUDIO_CVP_NS_MODE                  CVP_DNS_MODE
#define TCFG_AUDIO_DMS_SEL                      DMS_NORMAL
#elif (TCFG_AUDIO_CVP_DMS_FLEXIBLE_ANS_MODE)    /*话务双MIC+ANS通话*/
#define TCFG_AUDIO_TRIPLE_MIC_ENABLE            0
#define TCFG_AUDIO_DUAL_MIC_ENABLE              1
#define TCFG_AUDIO_CVP_NS_MODE                  CVP_ANS_MODE
#define TCFG_AUDIO_DMS_SEL                      DMS_FLEXIBLE
#elif (TCFG_AUDIO_CVP_DMS_FLEXIBLE_DNS_MODE)    /*话务双MIC+DNS通话*/
#define TCFG_AUDIO_TRIPLE_MIC_ENABLE            0
#define TCFG_AUDIO_DUAL_MIC_ENABLE              1
#define TCFG_AUDIO_CVP_NS_MODE                  CVP_DNS_MODE
#define TCFG_AUDIO_DMS_SEL                      DMS_FLEXIBLE
#elif (TCFG_AUDIO_CVP_3MIC_MODE)                /*3MIC通话*/
#define TCFG_AUDIO_TRIPLE_MIC_ENABLE            1
#define TCFG_AUDIO_DUAL_MIC_ENABLE              0
#define TCFG_AUDIO_CVP_NS_MODE                  CVP_DNS_MODE
#define TCFG_AUDIO_DMS_SEL                      DMS_NORMAL
#else
#define TCFG_AUDIO_TRIPLE_MIC_ENABLE            0
#define TCFG_AUDIO_DUAL_MIC_ENABLE              0
#define TCFG_AUDIO_CVP_NS_MODE                  CVP_ANS_MODE
#define TCFG_AUDIO_DMS_SEL                      DMS_NORMAL
#endif/*TCFG_AUDIO_CVP_DMS_DNS_MODE*/

#if TCFG_ESCO_DL_CVSD_SR_USE_16K
#define TCFG_AUDIO_CVP_BAND_WIDTH_CFG           (CVP_WB_EN) //只保留16k参数
#else
#define TCFG_AUDIO_CVP_BAND_WIDTH_CFG           (CVP_NB_EN | CVP_WB_EN) //同时保留8k和16k的参数
#endif

#if TCFG_CFG_TOOL_ENABLE
#undef EQ_SECTION_MAX
#define EQ_SECTION_MAX                          (32+2)  //2多阶高低通滤波器
#endif

#ifndef EQ_SECTION_MAX
#if TCFG_EQ_ENABLE
#define EQ_SECTION_MAX                          (32+2)  //2多阶高低通滤波器
#endif
#endif

#endif


//*********************************************************************************//
//                                  路径配置                                       //
//*********************************************************************************//
#define CONFIG_JLFAT_ENABLE

#if defined CONFIG_UI_ENABLE
#define TCFG_JLFAT_SUPPORT_OVERSECTOR_RW_ENABLE 1
#endif

#if TCFG_SD0_ENABLE
#define CONFIG_STORAGE_PATH                     "storage/sd0"   //定义对应SD0的路径
#define SDX_DEV                                 "sd0"
#endif

#if TCFG_SD1_ENABLE && !TCFG_SD0_ENABLE
#define CONFIG_STORAGE_PATH                     "storage/sd1"   //定义对应SD1的路径
#define SDX_DEV                                 "sd1"
#endif

#ifndef CONFIG_STORAGE_PATH
#define CONFIG_STORAGE_PATH                     "storage/sdx"   //不使用SD定义对应别的路径，防止编译出错
#define SDX_DEV                                 "sdx"
#endif

#define CONFIG_UDISK_STORAGE_PATH               "storage/udisk0"
#define CONFIG_ROOT_PATH                        CONFIG_STORAGE_PATH"/C/"
#define CONFIG_UDISK_ROOT_PATH                  CONFIG_UDISK_STORAGE_PATH"/C/"


//*********************************************************************************//
//                                  升级配置                                       //
//*********************************************************************************//
// #define CONFIG_DOUBLE_BANK_ENABLE                            //双备份方式升级
#ifdef CONFIG_DOUBLE_BANK_ENABLE
#define CONFIG_SUPPORT_DOUBLE_UBOOT                             //开启双uboot架构支持
#endif

#define CONFIG_UPGRADE_FILE_NAME                "update.ufw"
#define CONFIG_UPGRADE_PATH                     CONFIG_ROOT_PATH\
                                                CONFIG_UPGRADE_FILE_NAME
#define CONFIG_MIJIA_OTA_TO_FLASH               0//1-米家ota-flash方式 0-米家ota-sd方式


//*********************************************************************************//
//                                  调音工具                                       //
//*********************************************************************************//
#define TCFG_NULL_COMM                          0               //不支持通信
#define TCFG_USB_COMM                           1               //USB通信


//*********************************************************************************//
//                                VIDEO功能配置                                    //
//*********************************************************************************//
#ifdef CONFIG_VIDEO_ENABLE

#define CONFIG_USR_VIDEO_ENABLE                     //自定义VIDEO流使能

#ifdef CONFIG_USR_VIDEO_ENABLE
#ifdef CONFIG_USER_VIDEO_720P
#define CONFIG_USER_VIDEO_WIDTH                 1280
#define CONFIG_USER_VIDEO_HEIGHT                720
#define CONFIG_USER_VIDEO_ISC_SBUF_SIZE         (CONFIG_USER_VIDEO_WIDTH*64*3/2)
#define CONFIG_USER_VIDEO_SBUF_SIZE             (200 * 1024)
#else
#define CONFIG_USER_VIDEO_WIDTH                 640
#define CONFIG_USER_VIDEO_HEIGHT                480
#define CONFIG_USER_VIDEO_ISC_SBUF_SIZE         (CONFIG_USER_VIDEO_WIDTH*32*3/2)
#define CONFIG_USER_VIDEO_SBUF_SIZE             (300 * 1024)
#endif
// #define CONFIG_USER_VIDEO_ISC_STATIC_BUF_ENABLE
#define CONFIG_USER_VIDEO_PATH                  "192.168.1.1:8000"  //用户路径可随意设置
#define CONFIG_USER_VIDEO_REC_FPS               20  //自定义视频流帧率设置，0为默认
#define CONFIG_USER_VIDEO_REC_AUDIO_SAMPLE_RATE 0   //视频流的音频采样率，设成0为关闭mic
#endif

#endif


//*********************************************************************************//
//                                  EDR和BLE配置                                   //
//*********************************************************************************//
#ifdef CONFIG_BT_ENABLE

#define TCFG_BT_MODE                            BT_NORMAL

#define TCFG_POWER_ON_ENABLE_EMITTER            0   //开机自动打开发射器
#define TCFG_POWER_ON_ENABLE_BLE                0   //开机自动打开BLE
#define TCFG_USER_BT_CLASSIC_ENABLE             0   //经典蓝牙功能
#define TCFG_USER_BLE_ENABLE                    1   //BLE功能使能
#define TCFG_BT_DUAL_CONN_ENABLE                1   //经典蓝牙支持同时连接2台设备

#endif


//*********************************************************************************//
//                                     TWS配置                                     //
//*********************************************************************************//
#if TCFG_USER_TWS_ENABLE

#define CONFIG_TWS_COMMON_ADDR_AUTO             0   //自动生成TWS配对后的MAC地址
#define CONFIG_TWS_COMMON_ADDR_USED_LEFT        1   /* 使用左耳的MAC地址作为TWS配对后的地址
                                                    可配合烧写器MAC地址自增功能一起使用
                                                    多台交叉配对会出现MAC地址相同情况 */
#define CONFIG_TWS_COMMON_ADDR_SELECT           CONFIG_TWS_COMMON_ADDR_USED_LEFT    //CONFIG_TWS_COMMON_ADDR_AUTO

/* 配对方式选择 */
#define CONFIG_TWS_PAIR_BY_CLICK                0   //按键发起配对
#define CONFIG_TWS_PAIR_BY_AUTO                 1   //开机自动配对
#define CONFIG_TWS_PAIR_BY_BOX                  2   //测试盒/充电仓配对

/* 声道确定方式选择 */
#define CONFIG_TWS_MASTER_AS_LEFT               0   //主机作为左耳
#define CONFIG_TWS_MASTER_AS_RIGHT              1   //主机作为右耳
#define CONFIG_TWS_AS_LEFT                      2   //固定左耳
#define CONFIG_TWS_AS_RIGHT                     3   //固定右耳
#define CONFIG_TWS_START_PAIR_AS_LEFT           4   //双击发起配对的耳机做左耳
#define CONFIG_TWS_START_PAIR_AS_RIGHT          5   //双击发起配对的耳机做右耳
#define CONFIG_TWS_EXTERN_UP_AS_LEFT            6   //外部有上拉电阻作为左耳
#define CONFIG_TWS_EXTERN_DOWN_AS_LEFT          7   //外部有下拉电阻作为左耳
#define CONFIG_TWS_EXTERN_UP_AS_RIGHT           8   //外部有上拉电阻作为右耳
#define CONFIG_TWS_EXTERN_DOWN_AS_RIGHT         9   //外部有下拉电阻作为右耳
#define CONFIG_TWS_CHANNEL_SELECT_BY_BOX        10  //充电仓/测试盒决定左右耳

#define TCFG_TWS_CHANNEL_CHECK_IO               -1  //上下拉电阻检测引脚

/* 对箱电量显示方式 */
#if TCFG_BT_DISPLAY_BAT_ENABLE
#define CONFIG_DISPLAY_TWS_BAT_LOWER            1   //对耳手机端电量显示，显示低电量耳机的电量
#define CONFIG_DISPLAY_TWS_BAT_HIGHER           2   //对耳手机端电量显示，显示高电量耳机的电量
#define CONFIG_DISPLAY_TWS_BAT_LEFT             3   //对耳手机端电量显示，显示左耳的电量
#define CONFIG_DISPLAY_TWS_BAT_RIGHT            4   //对耳手机端电量显示，显示右耳的电量

#define CONFIG_DISPLAY_TWS_BAT_TYPE             CONFIG_DISPLAY_TWS_BAT_LOWER
#endif

#if TCFG_TWS_USE_COMMMON_ADDR == 0
#undef TCFG_TWS_AUTO_ROLE_SWITCH_ENABLE
#define TCFG_TWS_AUTO_ROLE_SWITCH_ENABLE 0
#endif

#define TCFG_TWS_INIT_AFTER_POWERON_TONE_PLAY_END 1 //tws播完开机提示音再初始化，处理提示音不同步问题

#define TCFG_BT_CONNECTION_CLOSE_ALL            1

#endif //TCFG_USER_TWS_ENABLE


//*********************************************************************************//
//                                  le_audio 配置                                  //
//*********************************************************************************//
#define LE_AUDIO_UNICAST_SOURCE_EN              (1 << 0)
#define LE_AUDIO_UNICAST_SINK_EN                (1 << 1)
#define LE_AUDIO_AURACAST_SOURCE_EN             (1 << 2)
#define LE_AUDIO_AURACAST_SINK_EN               (1 << 3)
#define LE_AUDIO_JL_UNICAST_SOURCE_EN           (1 << 4)
#define LE_AUDIO_JL_UNICAST_SINK_EN             (1 << 5)
#define LE_AUDIO_JL_AURACAST_SOURCE_EN          (1 << 6)
#define LE_AUDIO_JL_AURACAST_SINK_EN            (1 << 7)

#ifndef TCFG_LE_AUDIO_APP_CONFIG
#define TCFG_LE_AUDIO_APP_CONFIG                0
#endif


//*********************************************************************************//
//                                  pay 配置                                       //
//*********************************************************************************//
#define TCFG_PAY_ALIOS_ENABLE                   0

#define TCFG_PAY_ALIOS_WAY_T_HEAD               1  // 平头哥
#define TCFG_PAY_ALIOS_WAY_SEL                  TCFG_PAY_ALIOS_WAY_T_HEAD

#if (TCFG_PAY_ALIOS_WAY_SEL==TCFG_PAY_ALIOS_WAY_T_HEAD)
#define TCFG_PAY_ALIOS_PRODUCT_MODEL            ""
#define TCFG_PAY_ALIOS_COMPANY_NAME             "" //需要客户申请
#define ALIPAY_SE_FW_V2_0                       1  //SE版本固件为2.0设置为1,否则设置为0
#define ALIPAY_SE_USE_RESET_PIN                 0  //置1加密芯片采用reset管脚复位进低功耗，置0 上下电进低功耗
#define SE_POWER_GPIO                           0  //使用GPIO口给SE芯片电源脚供电
#endif


//*********************************************************************************//
//                                   AI配置                                        //
//*********************************************************************************//
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

#if TCFG_THIRD_PARTY_PROTOCOLS_ENABLE
#define THIRD_PARTY_PROTOCOLS_SEL               TCFG_THIRD_PARTY_PROTOCOLS_SEL
#endif

#ifndef THIRD_PARTY_PROTOCOLS_SEL
#define THIRD_PARTY_PROTOCOLS_SEL               0
#endif


//*********************************************************************************//
//                                UI DEMO配置                                      //
//*********************************************************************************//
#if TCFG_LCD_ENABLE
#define USE_LVGL_V8_UI_DEMO
/* LVGL UI使用的FB显存个数 */
/* 0:表示 LVGL UI直接在LCD显存上绘制,不需要额外的帧buffer (适用于UI刷新要求不高的方案)
 * 1:表示 LVGL UI 单独申请1块帧buffer
 * 2:表示 LVGL UI 单独申请2块帧buffer
 * */
#define LV_DISP_UI_FB_NUM      1
#define FB_LCD_BUF_NUM         2
#if (LV_DISP_UI_FB_NUM)
#define LV_COLOR_DEPTH_EXTEN   24 //24-适配ARGB8565,需要把LV_DISP_UI_FB_NUM 1/2
#endif
#endif

//*********************************************************************************//
//                             异常记录/离线log配置                                //
//*********************************************************************************//
#if !TCFG_DEBUG_UART_ENABLE
#define TCFG_DEBUG_DLOG_ENABLE                  0    // 离线log功能
#define TCFG_DEBUG_DLOG_FLASH_SEL               0    // 选择log保存到内置flash还是外置flash; 0:内置flash; 1:外置flash
#define TCFG_DLOG_FLASH_START_ADDR              0    // 配置外置flash用于存储dlog和异常数据的区域起始地址
#define TCFG_DLOG_FLASH_REGION_SIZE             (512 * 1024)    // 配置外置flash用于存储dlog和异常数据的区域大小
#if (TCFG_DEBUG_DLOG_ENABLE && TCFG_DEBUG_DLOG_FLASH_SEL)
#if (!defined(TCFG_NORFLASH_DEV_ENABLE) || (TCFG_NORFLASH_DEV_ENABLE == 0))
#undef TCFG_NORFLASH_DEV_ENABLE
#define TCFG_NORFLASH_DEV_ENABLE                1    // 使能外置flash驱动
#define TCFG_NORFLASH_START_ADDR                0    // 配置外置flash起始地址
#define TCFG_NORFLASH_SIZE                      (512 * 1024)   // 配置外置flash大小
#endif
#endif
#define TCFG_DEBUG_DLOG_RESET_ERASE             0    // 开机擦除flash的log数据
#define TCFG_DEBUG_DLOG_AUTO_FLUSH_TIMEOUT     30    // 主动刷新的超时时间(当指定时间没有刷新过缓存数据到flash, 则主动刷新)(单位秒)
#define TCFG_DEBUG_DLOG_UART_TX_PIN            TCFG_DEBUG_PORT   // dlog串口打印的引脚
#endif

#if defined CONFIG_RELEASE_ENABLE || TCFG_DEBUG_DLOG_ENABLE
#define LIB_DEBUG    1
#else
#define LIB_DEBUG    1
#endif
#define CONFIG_DEBUG_LIB(x)         (x & LIB_DEBUG)


#endif

