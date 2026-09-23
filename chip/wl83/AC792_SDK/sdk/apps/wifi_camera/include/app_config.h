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

#define CONFIG_VIDEO_DEC_ENABLE             1
#define AP_TEST_MODE       0
#define STA_TEST_MODE      1
#define P2P_TEST_MODE 		3
#define MONITOR_TEST_MODE  2

#define WIFI_ENTER_P2P_MODE	  0
#define WIFI_P2P_DEVICE_NAME  "JLWiFi-P2P"

#define EXT_WIFI_TEST_MODE STA_TEST_MODE
#define EXT_WIFI_AP_SSID   "AC79_EXT_WIFI_"    //配置外挂wifi的AP模式的SSID前缀
#define EXT_WIFI_AP_PWD    "12345678"          //配置外挂wifi的AP模式的密码
#define EXT_WIFI_STA_SSID  "zpc23"              //配置外挂wifi的STA模式的SSID前缀
#define EXT_WIFI_STA_PWD   "abc12345"          //配置外挂wifi的STA模式的密码


//*********************************************************************************//
//                                  调音工具                                       //
//*********************************************************************************//
#define TCFG_NULL_COMM                          0               //不支持通信
#define TCFG_USB_COMM                           1               //USB通信
#define TCFG_UART_COMM                          2               //串口通信



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

#if defined CONFIG_AUDIO_ENABLE && !defined CONFIG_SDFILE_EXT_ENABLE
#define CONFIG_VOICE_PROMPT_FILE_SAVE_IN_RESERVED_EXPAND_ZONE //AUDIO资源打包后放在扩展预留区
#endif

#if (defined CONFIG_AUDIO_ENABLE || defined CONFIG_UI_ENABLE) && !defined CONFIG_SDFILE_EXT_ENABLE
#define CONFIG_LOGO_FILE_SAVE_IN_RESERVED_EXPAND_ZONE //开关机logo资源打包后放在扩展预留区
#endif

#if defined CONFIG_UI_FILE_SAVE_IN_RESERVED_EXPAND_ZONE
#define CONFIG_UI_PACKRES_LEN 0x300000
#define CONFIG_UI_PACKRES_ADR ((__FLASH_SIZE__) - (CONFIG_UI_PACKRES_LEN) - 0x1000)
#else
#define CONFIG_UI_PACKRES_LEN 0
#define CONFIG_UI_PACKRES_ADR 0
#endif

#if defined CONFIG_VOICE_PROMPT_FILE_SAVE_IN_RESERVED_EXPAND_ZONE
#if defined CONFIG_UI_FILE_SAVE_IN_RESERVED_EXPAND_ZONE
#define CONFIG_AUDIO_PACKRES_LEN 0x100000
#define CONFIG_AUDIO_PACKRES_ADR ((__FLASH_SIZE__) - (CONFIG_UI_PACKRES_LEN) - 0x1000 - CONFIG_AUDIO_PACKRES_LEN)
#else
#define CONFIG_AUDIO_PACKRES_LEN 0x100000
#define CONFIG_AUDIO_PACKRES_ADR ((__FLASH_SIZE__) - CONFIG_AUDIO_PACKRES_LEN - 0x1000)
#endif
#else
#define CONFIG_AUDIO_PACKRES_LEN 0
#define CONFIG_AUDIO_PACKRES_ADR 0
#endif

#if defined CONFIG_LOGO_FILE_SAVE_IN_RESERVED_EXPAND_ZONE
#define CONFIG_LOGO_PACKRES_LEN 0x30000
#define CONFIG_LOGO_PACKRES_ADR ((__FLASH_SIZE__) - (CONFIG_UI_PACKRES_LEN) - 0x1000 - CONFIG_AUDIO_PACKRES_LEN - CONFIG_LOGO_PACKRES_LEN)
#endif



//*********************************************************************************//
//                                   DEBUG相关配置                                 //
//*********************************************************************************//
#define CONFIG_DEBUG_ENABLE                     //打印开关
// #define CONFIG_FLOAT_DEBUG_ENABLE
// #define CONFIG_CPU_EFFICIENCY_CALCULATE_ENABLE
// #define CONFIG_ICACHE_EFFICIENCY_CALCULATE_ENABLE
#ifndef CONFIG_NO_SDRAM_ENABLE
#define CONFIG_DCACHE_EFFICIENCY_CALCULATE_ENABLE
#endif
#define CONFIG_MPU_DEBUG_ENABLE
#define CONFIG_RTOS_STACK_CHECK_ENABLE          //是否启用定时检查任务栈
// #define CONFIG_TRUSTZONE_ENABLE
// #define CONFIG_SAVE_EXCEPTION_LOG_IN_FLASH   //保存异常打印信息到flash
// #define MEM_LEAK_CHECK_ENABLE                //是否启用内存泄漏检查(需要包含mem_leak_test.h头文件)

#if TCFG_LOWPOWER_FUNCTION == LOWPOWER_CLOSE
#define CONFIG_WWDG_ENABLE
#endif

// #define CONFIG_AUTO_SHUTDOWN_ENABLE          //自动倒数关机
// #define CONFIG_SYS_VDD_CLOCK_ENABLE          //系统可使用动态电源、时钟配置
// #define CONFIG_IPMASK_ENABLE                 //系统使用不可屏蔽中断


//*********************************************************************************//
//                    异常记录/离线log配置                                      //
//*********************************************************************************//
#if !TCFG_DEBUG_UART_ENABLE
#define TCFG_DEBUG_DLOG_ENABLE             0      // 离线log功能
#define TCFG_DEBUG_DLOG_FLASH_SEL          0      // 选择log保存到内置flash还是外置flash; 0:内置flash; 1:外置flash
#define TCFG_DLOG_FLASH_START_ADDR         (0x00)         // 配置外置flash用于存储dlog和异常数据的区域起始地址
#define TCFG_DLOG_FLASH_REGION_SIZE        (512 * 1024)   // 配置外置flash用于存储dlog和异常数据的区域大小
#if (TCFG_DEBUG_DLOG_ENABLE && TCFG_DEBUG_DLOG_FLASH_SEL)
#if (!defined(TCFG_NORFLASH_DEV_ENABLE) || (TCFG_NORFLASH_DEV_ENABLE == 0))
#undef TCFG_NORFLASH_DEV_ENABLE
#define TCFG_NORFLASH_DEV_ENABLE           1              // 使能外置flash驱动
#define TCFG_NORFLASH_START_ADDR           (0x00)         // 配置外置flash起始地址
#define TCFG_NORFLASH_SIZE                 (512 * 1024)   // 配置外置flash大小
#endif
#endif
#define TCFG_DEBUG_DLOG_RESET_ERASE        0      // 开机擦除flash的log数据
#define TCFG_DEBUG_DLOG_AUTO_FLUSH_TIMEOUT (30)   // 主动刷新的超时时间(当指定时间没有刷新过缓存数据到flash, 则主动刷新)(单位秒)
#define TCFG_DEBUG_DLOG_UART_TX_PIN        TCFG_DEBUG_PORT  // dlog串口打印的引脚
#if (defined(LIB_DEBUG) && TCFG_DEBUG_DLOG_ENABLE)
#undef LIB_DEBUG
#define LIB_DEBUG    1
#undef CONFIG_DEBUG_LIB
#define CONFIG_DEBUG_LIB(x)         (x & LIB_DEBUG)
#endif
#endif

//*********************************************************************************//
//                                  FCC测试相关配置                                //
//*********************************************************************************//
//#define RF_FCC_TEST_ENABLE//使能RF_FCC测试，详细配置见"apps/common/rf_fcc_tool/include/rf_fcc_main.h"


//*********************************************************************************//
//                                调试屏效/摄像头效果相关配置                              //
//*********************************************************************************//
// #define CONFIG_VIDEO_IQ_TOOLS_ENABLE   //使能调试图像效果模式

#ifdef CONFIG_VIDEO_IQ_TOOLS_ENABLE
#undef  TCFG_PC_ENABLE
#define TCFG_PC_ENABLE                      1
#undef  USB_DEVICE_CLASS_CONFIG
#define USB_DEVICE_CLASS_CONFIG             (UVC_CLASS | MASSSTORAGE_CLASS | CDC_CLASS)
#undef  USB_DEVICE_CLASS_CONFIG_2_0
#define USB_DEVICE_CLASS_CONFIG_2_0         (UVC_CLASS | MASSSTORAGE_CLASS | CDC_CLASS)

#endif //CONFIG_VIDEO_IQ_TOOLS_ENABLE


//*********************************************************************************//
//                                  网络相关配置                                   //
//*********************************************************************************//

#define TCFG_AI_SERVER_DISABLE                  1
#define TCFG_DUER_ENABLE                        0

#ifdef CONFIG_NET_ENABLE
// #define CONFIG_LTE_PHY_ENABLE                //usb网卡
#define CONFIG_WIFI_ENABLE                   //无线WIFI

#ifdef CONFIG_SFC_ENABLE
#ifdef CONFIG_NO_SDRAM_ENABLE
#define CONFIG_RF_TRIM_CODE_MOVABLE //把RF TRIM 的运行代码动态加载到ram运行(节省4K ram内存), 防止RF TRIM 期间500ms大电流访问flash造成flash挂掉持续大电流
#else
#define CONFIG_RF_TRIM_CODE_AT_RAM //把RF TRIM 的运行代码定死到ram运行(浪费4K ram内存,否则若动态加载到sdram需清cache), 防止RF TRIM 期间500ms大电流访问flash造成flash挂掉持续大电流
#endif
#endif

// #define CONFIG_IPERF_ENABLE  				// iperf测试
// #define CONFIG_WIFIBOX_ENABLE                //WIFI测试盒性能测试
// #define CONFIG_MP_TEST_ENABLE                //RF量产测试
// #define CONFIG_READ_RF_PARAM_FROM_CFGTOOL_ENABLE    //从配置文件读取RF参数
// #define CONFIG_SERVER_ASSIGN_PROFILE            //第三方平台的profile由杰理服务器分配
// #define CONFIG_PROFILE_UPDATE                //每次开机都从杰理服务器获取第三方平台的profile,不读flash
// #define CONFIG_STATIC_IPADDR_ENABLE          //记忆路由器分配的IP,下次直接使用记忆IP节省DHCP时间
// #define CONFIG_ASSIGN_MACADDR_ENABLE            //第一次开机连上外网后，使用杰理服务器分配WIFI模块的MAC地址, 关闭则使用<蓝牙地址更新工具*.exe>或者随机数作为MAC地址
// #define CONFIG_TURING_SDK_ENABLE             //使用图灵平台
// #define CONFIG_DUER_SDK_ENABLE               //使用百度平台
// #define CONFIG_DUI_SDK_ENABLE                //使用思必驰DUI平台
// #define CONFIG_ALI_SDK_ENABLE                //使用天猫精灵平台
// #define CONFIG_TVS_SDK_ENABLE                //使用腾讯云平台
// #define CONFIG_TELECOM_SDK_ENABLE            //电信云平台
// #define CONFIG_JL_CLOUD_SDK_ENABLE           //打开使用杰理云平台
// #define CONFIG_DLNA_SDK_ENABLE               //打开DLNA音乐播放功能
// #define CONFIG_DOWNLOAD_SAVE_FILE            //保存网络下载的音乐文件
// #define CONFIG_SCAN_PEN_ENABLE               //扫描笔图像拼接
// #define CONFIG_HTTP_SERVER_ENABLE            //HTTP服务器
// #define CONFIG_FTP_SERVER_ENABLE             //FTP服务器
// #define CONFIG_VOLC_RTC_ENABLE               //火山RTC大模型
// #define CONFIG_VOLC_ONESDK_ENABLE            //火山ONESDK
// #define CONFIG_DUER_LC_DEMO_ENABLE           //小度澜川AI对话demo

/*************电信云平台配网方式选择*************/
#ifdef CONFIG_TELECOM_SDK_ENABLE
#define CONFIG_APLINK_NET_CFG                   //电信AP配网。注意：1.电信AP配网不能与elink无感配网同时使能。2.wifi库需要支持ap
#ifndef CONFIG_APLINK_NET_CFG
#define CONFIG_ELINK_QLINK_NET_CFG              //电信elink无感配网。注意：elink无感配网不能与AIRKISS配网同时使能。
#endif
#define CONFIG_CTEI_DEVICE_ENABLE               //电信非蜂窝类串码对接设备使用
//#define CONFIG_MC_DEVICE_ENABLE               //电信mc接口类直连设备使用
#endif


#ifdef CONFIG_AUDIO_ENABLE
#define CONFIG_ACOUSTIC_COMMUNICATION_ENABLE    //声波配网

#define AISP_ALGORITHM                      1   //思必驰双mic唤醒,未授权版本只支持运行10分钟
#define ROOBO_ALGORITHM                     2   //ROOBO 单/双MIC唤醒 ROOBO_DUAL_MIC_ALGORITHM ,,,测试版本只支持运行10分钟
#define WANSON_ALGORITHM                    3   //华镇算法,测试版只能够正确识别1000次
#define JLKWS_ALGORITHM                     4   //杰理算法,现阶段仅用于测试效果
// #define CONFIG_ASR_ALGORITHM  JLKWS_ALGORITHM //本地打断唤醒算法选择

#ifdef CONFIG_ASR_ALGORITHM
#define WIFI_PCM_STREAN_SOCKET_ENABLE           //打开打断唤醒pcm音频流局域网传输工具
#endif
#endif


// #define CONFIG_MASS_PRODUCTION_ENABLE //启用产测模式
// #define CONFIG_AUTO_PRODUCTION_ENABLE	//启用自动化产测模式

#define ACCESS_NUM 				1
#define CONFIG_ENABLE_VLIST		//支持SD卡录像下的APP文件缩略图、文件列表检索

//AP模式的热点名称和密码
#define AP_WIFI_CAM_PREFIX    "wifi_camera_wl8x_"
#define AP_WIFI_CAM_WIFI_PWD  "12345678"

//默认网络视频为JPEG格式
#define CONFIG_NET_JPEG

// #define CONFIG_NET_TCP_ENABLE
#define CONFIG_NET_UDP_ENABLE

//默认间隔录影不允许连接实时流
#define CONFIG_NET_VDIEO_GAP_ENABLE 0

#define CONFIG_NET_SCR  /*网络投屏*/

#ifdef CONFIG_NET_SCR
#define CONFIG_NET_PROTOCOL_TCP  0  //网络投屏协议选择
#define CONFIG_NET_PROTOCOL_UDP  1
#endif
/*-------------网络端口----------------*/
#define CTP_CTRL_PORT   	3333
#define CDP_CTRL_PORT   	2228
#define NET_SCR_PORT    	2230
#define VIDEO_PREVIEW_PORT 	2226
#define VIDEO_PLAYBACK_PORT 2223
#define HTTP_PORT           8080
#define RTSP_PORT           554

/*--------视频库内使用----------------*/
#define _DUMP_PORT          2229
#define _FORWARD_PORT    	2224
#define _BEHIND_PORT     	2225
#define _THIRD_PORT     	3225


#define CONFIG_NET_PKG_JPEG

/*--------录像和实时流帧率配置--------*/
//录卡和实时流的音频采样率,注意：硬件没有接咪头需要设置为0
#define VIDEO_REC_AUDIO_SAMPLE_RATE		16000

//录卡前后视帧率设置
#define  LOCAL_VIDEO_REC_FPS 			25  //不使用0作为默认值，写具体数值

#if (__SDRAM_SIZE__ <= (2 * 1024 * 1024))
#undef LOCAL_VIDEO_REC_FPS
#define  LOCAL_VIDEO_REC_FPS            20
#endif

//实时流BUFF允许缓存帧数(延时大则需要打开，例如录像中720P),写0无效,注意：该宏大于1时，会引起实时流实际帧率比配置低，但是实时性好
#define  NET_VIDEO_BUFF_FRAME_CNT		2

//实时流前后视帧率设置
#define  NET_VIDEO_REC_FPS0   			20  //不使用0作为默认值，写具体数值
#define  NET_VIDEO_REC_FPS1   			25   //不使用0作为默认值，写具体数值

//录像模式实时流丢帧配置(单路720录像且实时流720或双路录像有效),只能配置以下3个宏数值>=1其中一个,配置必须小于等于摄像头输出帧率,全0则输出录像帧率
#define  NET_VIDEO_REC_DROP_REAl_FP		15	//(实际输出帧率，单路720录像且实时流720或双路录像或SFC 2M版本录像有效,写0无效,不录像请用NET_VIDEO_REC_FPS0,NET_VIDEO_REC_FPS1)
#define  NET_VIDEO_REC_LOSE_FRAME_CNT	0	//(每隔n帧丢一帧,单路720录像且实时流720或双路录像或SFC 2M版本录像有效,写0无效)30p摄像头,需求>=15p/s则配置>=1;25p摄像头,需求>=12p/s则配置>=1.
#define  NET_VIDEO_REC_SEND_FRAME_CNT	0	//(每隔n帧发一帧,单路720录像且实时流720或双路录像或SFC 2M版本录像有效,写0无效)

//RTSP实时流帧率设置
#define  STRM_VIDEO_REC_FPS0   			20  //不使用0作为默认值，写具体数值
#define  STRM_VIDEO_REC_DROP_REAl_FP 	15  //(实际输出帧率，单路720录像且实时流720或双路录像有效或SFC 2M版本录像,写0无效)

//RTSP实时流BUFF允许缓存帧数(延时大则需要打开，例如录像中720P),写0无效,注意：该宏大于1时，会引起实时流实际帧率比配置低，但是实时性好
#define  STRM_VIDEO_BUFF_FRAME_CNT		2
/*--------------------------------------*/

#endif


//*********************************************************************************//
//                                AUDIO功能配置                                    //
//*********************************************************************************//
#ifdef CONFIG_AUDIO_ENABLE

// #define CONFIG_DEC_DIGITAL_VOLUME_ENABLE     //数字音量淡入淡出功能
// #define CONFIG_RESUME_LOCAL_PLAY_FILE        //本地断点恢复播放
#if (!defined CONFIG_SFC_ENABLE) && (defined __SDRAM_SIZE__ && __SDRAM_SIZE__ >= (8 * 1024 * 1024))
// #define LOAD_SDRAM_PROMPT_PLAY           0   //0 首次调用提示音装载全部进sdram  1 装载当前提示音
#endif

#ifdef CONFIG_BT_ENABLE
#define CONFIG_SBC_DEC_ENABLE
#if __FLASH_SIZE__ > (1 * 1024 * 1024)
#define CONFIG_SBC_ENC_ENABLE
#define CONFIG_MSBC_DEC_ENABLE
#define CONFIG_MSBC_ENC_ENABLE
#define CONFIG_CVSD_DEC_ENABLE
#define CONFIG_CVSD_ENC_ENABLE
#endif
#endif

#define CONFIG_PCM_DEC_ENABLE
#define CONFIG_PCM_ENC_ENABLE
// #define CONFIG_WAV_DEC_ENABLE
// #define CONFIG_WAV_ENC_ENABLE
#if __FLASH_SIZE__ > (1 * 1024 * 1024)
#define CONFIG_MP3_DEC_ENABLE
// #define CONFIG_M4A_DEC_ENABLE
// #define CONFIG_NEW_M4A_DEC_ENABLE            //需要把lib_m4a_dec.a替换成lib_m4a_dec_seek.a
#ifdef CONFIG_NEW_M4A_DEC_ENABLE
// #define CONFIG_AAC_DEC_ENABLE
#endif
// #define CONFIG_VIRTUAL_DEV_ENC_ENABLE
// #define CONFIG_SPEEX_ENC_ENABLE
// #define CONFIG_OPUS_ENC_ENABLE
// #define CONFIG_VAD_ENC_ENABLE
#endif
#if __FLASH_SIZE__ > (2 * 1024 * 1024)
// #define CONFIG_DTS_DEC_ENABLE
#define CONFIG_ADPCM_DEC_ENABLE
// #define CONFIG_MP3_ENC_ENABLE
// #define CONFIG_WMA_DEC_ENABLE
// #define CONFIG_AMR_DEC_ENABLE
// #define CONFIG_APE_DEC_ENABLE
// #define CONFIG_FLAC_DEC_ENABLE
// #define CONFIG_SPEEX_DEC_ENABLE
// #define CONFIG_ADPCM_ENC_ENABLE
// #define CONFIG_OPUS_DEC_ENABLE
// #define CONFIG_AMR_ENC_ENABLE
// #define CONFIG_AEC_ENC_ENABLE
// #define CONFIG_DNS_ENC_ENABLE
// #define CONFIG_OGG_VORBIS_DEC_ENABLE

// #define CONFIG_SPECTRUM_FFT_EFFECT_ENABLE    //频谱运算
// #define CONFIG_REVERB_MODE_ENABLE            //打开混响功能
// #define CONFIG_AUDIO_MIX_ENABLE              //打开叠音功能
// #define CONFIG_AUDIO_PS_ENABLE                  //打开变调变速功能
#endif

#ifdef CONFIG_AEC_ENC_ENABLE
#define CONFIG_USB_AUDIO_AEC_ENABLE             //usb mic使能回声消除功能
// #define CONFIG_AEC_HW_REC_LINEIN_ENABLE     //AEC回采使用硬件通道数据
#endif

#ifndef CONFIG_AUDIO_LINEIN_SAMPLERATE
#define CONFIG_AUDIO_LINEIN_SAMPLERATE 48000 //LINEIN采样率
#endif

#endif


//*********************************************************************************//
//                                  路径配置                                       //
//*********************************************************************************//
// #define CONFIG_JLFAT_ENABLE
#if TCFG_SD0_ENABLE
#define CONFIG_STORAGE_PATH 	"storage/sd0"  //定义对应SD0的路径
#define SDX_DEV					"sd0"
#endif

#if TCFG_SD1_ENABLE && !TCFG_SD0_ENABLE
#define CONFIG_STORAGE_PATH 	"storage/sd1" //定义对应SD1的路径
#define SDX_DEV					"sd1"
#endif

#ifndef CONFIG_STORAGE_PATH
#define CONFIG_STORAGE_PATH		"storage/sdx" //不使用SD定义对应别的路径，防止编译出错
#define SDX_DEV					"sdx"
#endif

#define CONFIG_UDISK_STORAGE_PATH	"storage/udisk0"

#define CONFIG_ROOT_PATH            CONFIG_STORAGE_PATH"/C/" //定义对应SD文件系统的根目录路径
#define CONFIG_UDISK_ROOT_PATH     	CONFIG_UDISK_STORAGE_PATH"/C/" //定义对应U盘文件系统的根目录路径

#define CONFIG_MUSIC_PATH_SD        CONFIG_ROOT_PATH
#define CONFIG_MUSIC_PATH_SD0       "storage/sd0/C/"
#define CONFIG_MUSIC_PATH_SD1       "storage/sd1/C/"
#define CONFIG_MUSIC_PATH_UDISK     CONFIG_UDISK_ROOT_PATH
#define CONFIG_MUSIC_PATH_UDISK0    "storage/udisk0/C/"
#define CONFIG_MUSIC_PATH_UDISK1    "storage/udisk1/C/"

#define CONFIG_MUSIC_PATH_FLASH             "mnt/sdfile/res/"
#define CONFIG_EQ_FILE_NAME                 "mnt/sdfile/res/cfg/eq_cfg_hw.bin"

#ifdef CONFIG_AUDIO_ENABLE
#define CONFIG_VOICE_PROMPT_FILE_PATH       "mnt/sdfile/EXT_RESERVED/aupackres/tone/"
#endif

#if defined CONFIG_UI_ENABLE
#define CONFIG_UI_FILE_PATH               "mnt/sdfile/EXT_RESERVED/uipackres/ui/"
#endif

//#define CONFIG_DOUBLE_BANK_ENABLE         //双备份方式升级

#ifdef CONFIG_DOUBLE_BANK_ENABLE
#define CONFIG_SUPPORT_DOUBLE_UBOOT        //开启双uboot架构支持
#endif

#define CONFIG_UPGRADE_FILE_NAME            "update.ufw"
#define CONFIG_UPGRADE_PATH                 CONFIG_ROOT_PATH\
											CONFIG_UPGRADE_FILE_NAME	//备份方式升级

#define CONFIG_SD0_UPGRADE_PATH             "storage/sd0/C/" CONFIG_UPGRADE_FILE_NAME	//备份方式升级
#define CONFIG_SD1_UPGRADE_PATH             "storage/sd1/C/" CONFIG_UPGRADE_FILE_NAME	//备份方式升级
#define CONFIG_UDISK0_UPGRADE_PATH          "storage/udisk0/C/" CONFIG_UPGRADE_FILE_NAME	//备份方式升级
#define CONFIG_UDISK1_UPGRADE_PATH          "storage/udisk1/C/" CONFIG_UPGRADE_FILE_NAME	//备份方式升级




//*********************************************************************************//
//                                  网络视频配置                                   //
//*********************************************************************************//



//*********************************************************************************//
//                                VIDEO功能配置                                    //
//*********************************************************************************//
#ifdef CONFIG_VIDEO_ENABLE

#ifdef CONFIG_SCAN_PEN_ENABLE
#define CONFIG_VIDEO1_ENABLE
#define CONFIG_SPI_VIDEO_ENABLE
#define CONFIG_VIDEO_720P
#endif

#if TCFG_LCD_ENABLE
#define CONFIG_DISPLAY_ENABLE
#endif

#define CONFIG_VE_MOTION_DETECT_MODE_ISP		/* 移动侦测使用MODE_ISP, 否则使用MODE_NORMAL */

//*********************************************************************************//
//                             视频流相关配置                                      //
//*********************************************************************************//
#define VIDEO_REC_FPS 					20   //录像SD卡视频帧率设置,0为默认

#define CONFIG_USR_VIDEO_ENABLE		//用户VIDEO使能

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
#define OTA_MAJOR   1
#define OTA_MINOR   3
#define OTA_PATCH   0

#define CONFIG_REC_DIR_0       "DCIM/1/"
#define CONFIG_REC_DIR_1       "DCIM/2/"
#define CONFIG_REC_DIR_2       "DCIM/3/"
#define CONFIG_REC_DIR_4       "DCIM/4/"
#define CONFIG_REC_DIR_5       "DCIM/5/"

#if TCFG_SD0_ENABLE
#define CONFIG_STORAGE_PATH 	"storage/sd0"
#define SDX_DEV					"sd0"
#endif

#if TCFG_SD1_ENABLE
#define CONFIG_STORAGE_PATH 	"storage/sd1"
#define SDX_DEV					"sd1"
#endif

#ifndef CONFIG_STORAGE_PATH
#define CONFIG_STORAGE_PATH		"no_sd_card" //不使用SD定义对应别的路径，防止编译出错
#define SDX_DEV					"no_sd"
#endif

#define CONFIG_ROOT_PATH     	CONFIG_STORAGE_PATH"/C/"
#define CONFIG_REC_PATH_0       CONFIG_STORAGE_PATH"/C/"CONFIG_REC_DIR_0
#define CONFIG_REC_PATH_1       CONFIG_STORAGE_PATH"/C/"CONFIG_REC_DIR_1
#define CONFIG_REC_PATH_2       CONFIG_STORAGE_PATH"/C/"CONFIG_REC_DIR_2
#define CONFIG_REC_PATH_4       CONFIG_STORAGE_PATH"/C/"CONFIG_REC_DIR_4
#define CONFIG_REC_PATH_5       CONFIG_STORAGE_PATH"/C/"CONFIG_REC_DIR_5

#define CONFIG_UDISK_STORAGE_PATH	"storage/udisk0"
#define CONFIG_UDISK_ROOT_PATH     	CONFIG_UDISK_STORAGE_PATH"/C/"

#ifdef CONFIG_EMR_DIR_ENABLE
#define CONFIG_EMR_REC_DIR         "EMR/"
#define CONFIG_EMR_REC_DIR_0       "DCIM/1/"CONFIG_EMR_REC_DIR
#define CONFIG_EMR_REC_DIR_1       "DCIM/2/"CONFIG_EMR_REC_DIR
#define CONFIG_EMR_REC_DIR_2       "DCIM/3/"CONFIG_EMR_REC_DIR
#define CONFIG_EMR_REC_DIR_4       "DCIM/4/"CONFIG_EMR_REC_DIR
#define CONFIG_EMR_REC_DIR_5       "DCIM/5/"CONFIG_EMR_REC_DIR

#define CONFIG_EMR_REC_PATH_0   CONFIG_STORAGE_PATH"/C/"CONFIG_EMR_REC_DIR_0
#define CONFIG_EMR_REC_PATH_1   CONFIG_STORAGE_PATH"/C/"CONFIG_EMR_REC_DIR_1
#define CONFIG_EMR_REC_PATH_2   CONFIG_STORAGE_PATH"/C/"CONFIG_EMR_REC_DIR_2
#define CONFIG_EMR_REC_PATH_4   CONFIG_STORAGE_PATH"/C/"CONFIG_EMR_REC_DIR_4
#define CONFIG_EMR_REC_PATH_5   CONFIG_STORAGE_PATH"/C/"CONFIG_EMR_REC_DIR_5
#endif
#define CAMERA0_CAP_PATH        CONFIG_REC_PATH_0
#define CAMERA1_CAP_PATH        CONFIG_REC_PATH_1
#define CAMERA2_CAP_PATH        CONFIG_REC_PATH_2
#define CAMERA4_CAP_PATH        CONFIG_REC_PATH_4
#define CAMERA5_CAP_PATH        CONFIG_REC_PATH_5

#define CONFIG_DEC_ROOT_PATH 	CONFIG_ROOT_PATH"DCIM/"
#define CONFIG_DEC_PATH_1 	    CONFIG_REC_PATH_0
#define CONFIG_DEC_PATH_2 	    CONFIG_REC_PATH_1
#define CONFIG_DEC_PATH_3 	    CONFIG_REC_PATH_2
#define CONFIG_DEC_PATH_4 	    CONFIG_REC_PATH_4
#define CONFIG_DEC_PATH_5 	    CONFIG_REC_PATH_5

#define CONFIG_MUSIC_PATH      CONFIG_ROOT_PATH"MUSIC/"

#define CONFIG_MUSIC_PATH_SD        CONFIG_ROOT_PATH
#define CONFIG_MUSIC_PATH_UDISK     CONFIG_UDISK_ROOT_PATH

#define MAX_FILE_NAME_LEN       64
#define FILE_SHOW_NUM           12  /* 一页显示文件数 */

//一旦有VIDEO0/VIDEO1打开, 则不能共存VIDEO4/VIDEO5
#if (defined CONFIG_VIDEO4_ENABLE) || (defined CONFIG_VIDEO5_ENABLE)
//二合一功能
#define THREE_WAY_ENABLE		0
#define THREE_WAY_DOUBLE_RAW    0
#define CONFIG_VIDEO_REC_NUM    6

//warning
#if (defined CONFIG_VIDEO0_ENABLE) || (defined CONFIG_VIDEO1_ENABLE)
#error "they can not enable at the same time!"
#endif

#else

#define CONFIG_VIDEO_REC_NUM    4
#if (defined CONFIG_VIDEO0_ENABLE) && (defined CONFIG_VIDEO1_ENABLE) && (defined CONFIG_VIDEO2_ENABLE)
//dvp+mipi+uvc
#define THREE_WAY_ENABLE		1
#define THREE_WAY_DOUBLE_RAW    1
#elif (defined CONFIG_VIDEO0_ENABLE) && (defined CONFIG_VIDEO1_ENABLE)
//dvp+mipi
#define THREE_WAY_ENABLE		0
#define THREE_WAY_DOUBLE_RAW    1
#else
#define THREE_WAY_ENABLE		0
#define THREE_WAY_DOUBLE_RAW    0
#endif

#endif

#if defined CONFIG_VIDEO1_ENABLE
#define CONFIG_PARK_ENABLE
#ifdef CONFIG_VIDEO2_ENABLE
#define	CONFIG_VIDEO_PARK_DECT		3
#else
#define	CONFIG_VIDEO_PARK_DECT		3
#endif
#else
#if defined CONFIG_VIDEO2_ENABLE
#define CONFIG_PARK_ENABLE
#define	CONFIG_VIDEO_PARK_DECT		3
#else
#define	CONFIG_VIDEO_PARK_DECT		0
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
//                                  EDR和BLE配置                                   //
//*********************************************************************************//
#ifdef CONFIG_BT_ENABLE

#define TCFG_BT_MODE                            BT_NORMAL

#define BT_EMITTER_EN                           1
#define BT_RECEIVER_EN                          2

#define TCFG_POWER_ON_ENABLE_EMITTER            0   //开机自动打开发射器
#define TCFG_POWER_ON_ENABLE_BT                 0   //开机自动打开经典蓝牙
#define TCFG_POWER_ON_ENABLE_BLE                0   //开机自动打开BLE
#define TCFG_USER_BT_CLASSIC_ENABLE             1   //经典蓝牙功能
#define TCFG_USER_BLE_ENABLE                    1   //BLE功能使能
#define TCFG_USER_EMITTER_ENABLE                0   //蓝牙发射功能
#define TCFG_BT_DUAL_CONN_ENABLE                0   //经典蓝牙支持同时连接2台设备

#endif

#ifndef TCFG_USER_BLE_ENABLE
#define TCFG_USER_BLE_ENABLE                    0   //BLE功能使能
#endif

#define INSTR_DEV_UART_ENABLE                   1	//拓展串口-蓝牙协议使能
#define INSTR_DEV_SPI_ENABLE                    0
//*********************************************************************************//
//                                     TWS配置                                     //
//*********************************************************************************//
#if TCFG_USER_TWS_ENABLE

#define CONFIG_TWS_COMMON_ADDR_AUTO             0   //自动生成TWS配对后的MAC地址
#define CONFIG_TWS_COMMON_ADDR_USED_LEFT        1   /* 使用左耳的MAC地址作为TWS配对后的地址
                                                    可配合烧写器MAC地址自增功能一起使用
                                                    多台交叉配对会出现MAC地址相同情况 */
#define CONFIG_TWS_COMMON_ADDR_SELECT           CONFIG_TWS_COMMON_ADDR_AUTO

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
#if TCFG_PAY_ALIOS_ENABLE
#define ALIPAY_SEL                              ALIPAY_EN
#else
#define ALIPAY_SEL                              0
#endif
#if TCFG_AI_SERVER == TCFG_DUER_ENABLE
#define THIRD_PARTY_PROTOCOLS_SEL               ((TCFG_THIRD_PARTY_PROTOCOLS_SEL & ~NET_CFG_EN) | DUEROS_EN)
#else
#define THIRD_PARTY_PROTOCOLS_SEL               (TCFG_THIRD_PARTY_PROTOCOLS_SEL|ALIPAY_SEL)
#endif
#endif

#ifndef THIRD_PARTY_PROTOCOLS_SEL
#define THIRD_PARTY_PROTOCOLS_SEL               0
#endif


//*********************************************************************************//
//                                  LCD配置                                        //
//*********************************************************************************//
#if TCFG_LCD_ENABLE
#ifdef CONFIG_UI_ENABLE
#define USE_LVGL_V8_UI_DEMO
// #define USE_LVGL_V9_UI_DEMO
#endif
/* LV_DISP_UI_FB_NUM: LVGL UI绘制的FB帧显存个数 */
/* 0:表示 LVGL UI直接在LCD显存上绘制,不需要额外的帧buffer (使用于UI刷新要求不高的方案)
 * 1:表示 LVGL UI 单独申请1块帧buffer
 * 2:表示 LVGL UI 单独申请2块帧buffer
 * */
/* FB_LCD_BUF_NUM : LCD使用的帧显存个数 */
/* 0:表示 LCD不需要额外帧buf,用UI绘制FB 或者摄像头图像FB 直接推屏显示
 * 1:表示 LCD只开一块帧显存,只能拷贝更新或者旋转更新推屏数据
 * 2:表示 LCD开2块帧显存,可以通过交换的方式来更新推屏数据
 * 3:表示 LCD开3块帧显存,其中2块通过交换的方式来更新推屏数据,另外1块用做合成输出
 * */
/* 2个宏组合更多详细说明,请移步开源文档 */
#define LV_DISP_UI_FB_NUM      1 //注意当修改为0时,需要设置lv_conf.h:LV_COLOR_DEPTH_EXTEN = LV_COLOR_DEPTH
#define FB_LCD_BUF_NUM         2
#endif

//描述当前SDK能够兼容的UI项目模板最低版本
#define COMPATIBLE_UI_PRJ_TEMPLATE_VERSION_MIN_MAJOR 1
#define COMPATIBLE_UI_PRJ_TEMPLATE_VERSION_MIN_MINOR 3
#define COMPATIBLE_UI_PRJ_TEMPLATE_VERSION_MIN_PATCH 0

//描述当前SDK能够兼容的UI项目模板最高版本
#define COMPATIBLE_UI_PRJ_TEMPLATE_VERSION_MAX_MAJOR 1
#define COMPATIBLE_UI_PRJ_TEMPLATE_VERSION_MAX_MINOR 3
#define COMPATIBLE_UI_PRJ_TEMPLATE_VERSION_MAX_PATCH 2


#ifdef CONFIG_UI_ENABLE
#define CONFIG_UI_STYLE_LY_ENABLE   //LY风格UI，使用按键UI工程时要打开
#define CONFIG_FILE_PREVIEW_ENABLE
#endif


#define CONFIG_CXX_SUPPORT //使能C++支持


// #define CONFIG_LZ4_COMPRESS_APP_CODE_ENABLE     //使用LZ4压缩代码

#ifdef CONFIG_SFC_ENABLE
#define CONFIG_LZ4_DATA_CODE_ENABLE             //使用LZ4压缩data段
#endif

// #define CONFIG_DOUBLE_BANK_ENABLE               //双备份方式升级
// #define CONFIG_UPDATE_COMPRESS                  //双备份压缩升级

#if defined (CONFIG_DOUBLE_BANK_ENABLE) && defined(CONFIG_UPDATE_COMPRESS)
#define CONFIG_DOUBLE_BANK_LESS                 1 //双备份结构，但appcore1区域可以更小
#endif


//*********************************************************************************//
//                          异常记录/离线log配置                                      //
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


#include "video_buf_config.h"

#endif

