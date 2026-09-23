/**
 * @file avi_parse.h
 * @brief 简易AVI头部解析器接口
 */

#ifndef AVI_PARSE_H
#define AVI_PARSE_H

#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

/* AVI解析结果结构 */
struct avi_parser_result {
    /* 基本信息 */
    int valid;                  // 解析是否成功

    /* 视频信息 */
    int has_video;              // 是否有视频流
    int video_stream_id;        // 视频流编号 (用于构建chunk标识如00dc)
    char video_chunk_id[5];     // 视频chunk标识 (如"00dc")
    int width;                  // 视频宽度
    int height;                 // 视频高度
    int fps;                    // 帧率
    uint32_t video_codec;            // 视频编码FourCC
    int video_coding_type;      // 视频编码类型 (用于avi_info)
    uint32_t total_frames;           // 总帧数

    /* 音频信息 */
    int has_audio;              // 是否有音频流
    int audio_stream_id;        // 音频流编号 (用于构建chunk标识如01wb)
    char audio_chunk_id[5];     // 音频chunk标识 (如"01wb")
    int audio_channels;         // 音频声道数
    int audio_sample_rate;      // 音频采样率
    int audio_bits;             // 音频位深
    uint16_t audio_format;           // 音频格式
    int audio_coding_type;      // 音频编码类型 (用于avi_info)

    /* 关键位置 (相对文件起始的偏移) */
    uint32_t movi_offset;            // movi数据起始位置
    uint32_t movi_size;              // movi数据大小
    uint32_t idx1_offset;            // idx1索引起始位置
    uint32_t idx1_size;              // idx1索引大小

    /* 文件信息 */
    uint32_t file_size;              // AVI文件总大小 (从RIFF头获取)
};

/**
 * @brief 解析AVI头部信息
 *
 * @param buf       AVI文件头部数据 (建议至少读取64KB以确保包含完整hdrl)
 * @param buf_size  buffer大小
 * @param result    解析结果输出
 * @return int      0成功, <0失败
 *
 **/
int avi_parse_header(const uint8_t *buf, uint32_t buf_size, struct avi_parser_result *result);

/**
 * @brief 打印解析结果 (调试用)
 *
 * @param result    解析结果
 */
void avi_parser_result_dump(const struct avi_parser_result *result);

/*============================================================================
 *                          idx1 索引相关函数
 *============================================================================*/
/**
 * @brief 计算idx1在文件中的预期位置
 *
 * @param result    已解析的AVI头部结果
 * @return uint32_t      idx1的预期文件偏移，0表示无法计算
 */
uint32_t avi_calc_idx1_offset(const struct avi_parser_result *result);

/**
 * @brief 计算需要下载的文件末尾大小以获取idx1
 *
 * @param result    已解析的AVI头部结果
 * @return uint32_t      建议下载的末尾字节数
 */
uint32_t avi_calc_idx1_download_size(const struct avi_parser_result *result);

#endif /* AVI_PARSE_H */

