#ifndef VIDEO_STREAM_COMMON_H
#define VIDEO_STREAM_COMMON_H

#include "lcd_config.h"
#include "video.h"

#define VIDEO_STREAM_BROADCAST_ADDR    "238.238.238.238"
#define VIDEO_STREAM_BROADCAST_PORT     23456

#define __ALIGN_16(a)     (((a) + 15) & ~15)

// 根据不同屏幕分辨率，设置默认视频参数

// 视频配置
#if LCD_W >= 640
#define STREAM_VIDEO_WIDTH               640                 //视频宽度
#define STREAM_VIDEO_HEIGHT              480                 //视频高度
#define STREAM_VIDEO_ABR_KBPS            2000                //视频码率(kbps)
#else
#define STREAM_VIDEO_WIDTH               320                 //视频宽度
#define STREAM_VIDEO_HEIGHT              240                 //视频高度
#define STREAM_VIDEO_ABR_KBPS            800                //视频码率(kbps)
#endif

#define STREAM_VIDEO_FPS                 25                  //视频帧率
#define STREAM_VIDEO_ONLINE              1                   //视频是否联动编码
#define STREAM_VIDEO_DEVICE              1                   //视频设备
// 音频配置
#define STREAM_AUDIO_SAMPLE_RATE         16000               //音频采样率
#define STREAM_AUDIO_CHANNEL             1                   //音频通道数
#define STREAM_AUDIO_VOLUME              100                 //音频音量
#define STREAM_AUDIO_INTERVAL_SIZE       512 * 4             //单个音频包大小
// 使能配置
#define STREAM_VIDEO_OSD_ENABLE           0                   //发送视频水印使能
#define STREAM_AUDIO_ENABLE               1                   //发送音频使能

// 渲染窗口配置
#define SCREEN_WIDTH                    LCD_W                 //屏幕宽度
#define SCREEN_HEIGHT                   LCD_H                 //屏幕高度

#define DOUBLE_BIG_WIN_WIDTH     SCREEN_WIDTH                 //双窗口渲染时 大窗口宽度
#define DOUBLE_BIG_WIN_HEIGHT    SCREEN_HEIGHT                //双窗口渲染时 大窗口高度
//根据不同屏幕分辨率，设置双窗口渲染时小窗口的宽高
#if SCREEN_WIDTH >= 640
#define DOUBLE_SMALL_WIDTH   320                               //双窗口渲染时 小窗口宽度
#define DOUBLE_SMALL_HEIGHT  240                               //双窗口渲染时 小窗口高度
#else
#define DOUBLE_SMALL_WIDTH   120                                //双窗口渲染时 小窗口宽度
#define DOUBLE_SMALL_HEIGHT  160                                //双窗口渲染时 小窗口高度
#endif

#define DISP_ROTATE           270                               //窗口旋转角度 0/90/180/270
#define DISP_MIRROR           VIDEO_DIR_NONE                   //窗口镜像 NOR/HOR/VER

struct video_stream_info {
    int img_width;
    int img_height;
    int fps;
    int bitrate_kbps;
    int online;
    int device_id;
    int osd_enable;
    int audio_enable;
    int sample_rate;
    int channel;
    int volume;
    int aud_interval_size;
};

#endif // VIDEO_STREAM_COMMON_H

