
#include "avi_parse.h"

/*============================================================================
 *                              AVI格式常量
 *============================================================================*/

/* RIFF/AVI FourCC */
#define FOURCC_RIFF     0x46464952  // "RIFF"
#define FOURCC_AVI      0x20495641  // "AVI "
#define FOURCC_LIST     0x5453494C  // "LIST"
#define FOURCC_hdrl     0x6C726468  // "hdrl"
#define FOURCC_avih     0x68697661  // "avih"
#define FOURCC_strl     0x6C727473  // "strl"
#define FOURCC_strh     0x68727473  // "strh"
#define FOURCC_strf     0x66727473  // "strf"
#define FOURCC_movi     0x69766F6D  // "movi"
#define FOURCC_idx1     0x31786469  // "idx1"
#define FOURCC_vids     0x73646976  // "vids"
#define FOURCC_auds     0x73647561  // "auds"

/* 常见视频编码FourCC */
#define FOURCC_MJPG     0x47504A4D  // "MJPG"
#define FOURCC_mjpg     0x67706A6D  // "mjpg"
#define FOURCC_JPEG     0x4745504A  // "JPEG"
#define FOURCC_jpeg     0x6765706A  // "jpeg"
#define FOURCC_H264     0x34363248  // "H264"
#define FOURCC_h264     0x34363268  // "h264"
#define FOURCC_X264     0x34363258  // "X264"
#define FOURCC_avc1     0x31637661  // "avc1"

/* 音频格式 */
#define WAVE_FORMAT_PCM         0x0001
#define WAVE_FORMAT_ADPCM       0x0002
#define WAVE_FORMAT_ALAW        0x0006
#define WAVE_FORMAT_MULAW       0x0007
#define WAVE_FORMAT_MP3         0x0055

#define AVI_INDEX_ENTRY_SIZE    16
#define AVIIF_KEYFRAME          0x10

/*============================================================================
 *                              数据结构
 *============================================================================*/

/* AVI主头部 (avih) */
typedef struct {
    uint32_t dwMicroSecPerFrame;     // 每帧微秒数
    uint32_t dwMaxBytesPerSec;       // 最大字节率
    uint32_t dwPaddingGranularity;   // 填充粒度
    uint32_t dwFlags;                // 标志
    uint32_t dwTotalFrames;          // 总帧数
    uint32_t dwInitialFrames;        // 初始帧数
    uint32_t dwStreams;              // 流数量
    uint32_t dwSuggestedBufferSize;  // 建议缓冲区大小
    uint32_t dwWidth;                // 视频宽度
    uint32_t dwHeight;               // 视频高度
    uint32_t dwReserved[4];          // 保留
} AVI_MAIN_HEADER;

/* 流头部 (strh) */
typedef struct {
    uint32_t fccType;                // 流类型 (vids/auds)
    uint32_t fccHandler;             // 编解码器
    uint32_t dwFlags;                // 标志
    uint16_t wPriority;              // 优先级
    uint16_t wLanguage;              // 语言
    uint32_t dwInitialFrames;        // 初始帧
    uint32_t dwScale;                // 时间刻度
    uint32_t dwRate;                 // 采样率
    uint32_t dwStart;                // 开始时间
    uint32_t dwLength;               // 流长度
    uint32_t dwSuggestedBufferSize;  // 建议缓冲区大小
    uint32_t dwQuality;              // 质量
    uint32_t dwSampleSize;           // 采样大小
    struct {
        int16_t left;
        int16_t top;
        int16_t right;
        int16_t bottom;
    } rcFrame;                  // 帧矩形
} AVI_STREAM_HEADER;

/* 视频格式 (strf for vids) */
typedef struct {
    uint32_t biSize;                 // 结构大小
    int32_t biWidth;                // 宽度
    int32_t biHeight;               // 高度
    uint16_t biPlanes;               // 平面数
    uint16_t biBitCount;             // 位深
    uint32_t biCompression;          // 压缩格式 (FourCC)
    uint32_t biSizeImage;            // 图像大小
    int32_t biXPelsPerMeter;        // X分辨率
    int32_t biYPelsPerMeter;        // Y分辨率
    uint32_t biClrUsed;              // 使用的颜色数
    uint32_t biClrImportant;         // 重要颜色数
} BITMAPINFOHEADER;

/* 音频格式 (strf for auds) */
typedef struct {
    uint16_t wFormatTag;             // 格式标签
    uint16_t nChannels;              // 声道数
    uint32_t nSamplesPerSec;         // 采样率
    uint32_t nAvgBytesPerSec;        // 平均字节率
    uint16_t nBlockAlign;            // 块对齐
    uint16_t wBitsPerSample;         // 采样位数
} WAVEFORMATEX;


/* idx1 索引条目结构 (每条16字节) */
typedef struct {
    uint32_t ckid;           // chunk标识 (如 '00dc', '01wb')
    uint32_t dwFlags;        // 标志 (0x10 = keyframe)
    uint32_t dwChunkOffset;  // chunk在movi中的偏移 (相对于movi起始或文件起始，取决于AVI版本)
    uint32_t dwChunkLength;  // chunk数据长度
} AVI_INDEX_ENTRY;



/* 从buffer读取小端32位整数 */
static inline uint32_t read_le32(const uint8_t *buf)
{
    return buf[0] | (buf[1] << 8) | (buf[2] << 16) | (buf[3] << 24);
}

/* 从buffer读取小端16位整数 */
static inline uint16_t read_le16(const uint8_t *buf)
{
    return buf[0] | (buf[1] << 8);
}

/* FourCC转字符串 (用于调试) */
static void fourcc_to_str(uint32_t fourcc, char *str)
{
    str[0] = (fourcc >> 0) & 0xFF;
    str[1] = (fourcc >> 8) & 0xFF;
    str[2] = (fourcc >> 16) & 0xFF;
    str[3] = (fourcc >> 24) & 0xFF;
    str[4] = '\0';
}


static int get_video_coding_type(uint32_t fourcc)
{
    switch (fourcc) {
    case FOURCC_MJPG:
    case FOURCC_mjpg:
    case FOURCC_JPEG:
    case FOURCC_jpeg:
        return 1;  // MJPEG, 根据你的实际定义调整
    case FOURCC_H264:
    case FOURCC_h264:
    case FOURCC_X264:
    case FOURCC_avc1:
        return 2;  // H264, 根据你的实际定义调整
    default:
        return 0;  // 未知
    }
}


static int get_audio_coding_type(uint16_t format)
{
    switch (format) {
    case WAVE_FORMAT_PCM:
        return 1;  // PCM, 根据你的实际AUDIO_CODING_PCM定义调整
    case WAVE_FORMAT_MP3:
        return 2;  // MP3
    case WAVE_FORMAT_ALAW:
        return 3;  // A-Law
    case WAVE_FORMAT_MULAW:
        return 4;  // u-Law
    default:
        return 0;  // 未知
    }
}

int avi_parse_header(const uint8_t *buf, uint32_t buf_size, struct avi_parser_result *result)
{
    if (!buf || !result || buf_size < 12) {
        printf("invalid params");
        return -1;
    }

    memset(result, 0, sizeof(*result));

    uint32_t pos = 0;
    char fcc_str[8];
    int stream_index = 0;  // 当前流编号，按strl出现顺序递增
    int current_stream_type = 0;  // 0=未知, 1=vids, 2=auds

    /* 检查RIFF头 */
    uint32_t riff_fcc = read_le32(buf + pos);
    if (riff_fcc != FOURCC_RIFF) {
        fourcc_to_str(riff_fcc, fcc_str);
        printf("not RIFF file, got: %s", fcc_str);
        return -2;
    }
    pos += 4;

    /* 文件大小 (RIFF chunk size) */
    result->file_size = read_le32(buf + pos) + 8;
    pos += 4;

    /* 检查AVI标识 */
    uint32_t avi_fcc = read_le32(buf + pos);
    if (avi_fcc != FOURCC_AVI) {
        fourcc_to_str(avi_fcc, fcc_str);
        printf("not AVI file, got: %s", fcc_str);
        return -3;
    }
    pos += 4;

    //printf("AVI file size: %d bytes", result->file_size);

    /* 遍历chunks */
    while (pos + 8 <= buf_size) {
        uint32_t chunk_fcc = read_le32(buf + pos);
        uint32_t chunk_size = read_le32(buf + pos + 4);

        fourcc_to_str(chunk_fcc, fcc_str);
        //printf("chunk: %s, size: %d, pos: %d", fcc_str, chunk_size, pos);

        if (chunk_fcc == FOURCC_LIST) {
            /* LIST chunk, 读取list类型 */
            uint32_t list_type = read_le32(buf + pos + 8);
            fourcc_to_str(list_type, fcc_str);
            //printf("  LIST type: %s", fcc_str);

            if (list_type == FOURCC_hdrl) {
                /* hdrl - 头部列表，进入解析 */
                pos += 12;  // 跳过 LIST + size + hdrl
                continue;
            } else if (list_type == FOURCC_strl) {
                /* strl - 流列表，进入解析，记录当前流编号 */
                current_stream_type = 0;  // 重置，等待strh确定类型
                pos += 12;  // 跳过 LIST + size + strl
                continue;
            } else if (list_type == FOURCC_movi) {
                /* movi - 数据区域 */
                result->movi_offset = pos + 12;  // movi数据起始
                result->movi_size = chunk_size - 4;
                printf("movi found at offset: %d, size: %d", result->movi_offset, result->movi_size);

                /* movi之后可能是idx1，跳过movi继续找 */
                pos += 8 + chunk_size;
                if (chunk_size & 1) {
                    pos++;    // 对齐
                }
                continue;
            } else {
                /* 其他LIST，跳过 */
                pos += 8 + chunk_size;
                if (chunk_size & 1) {
                    pos++;
                }
                continue;
            }
        } else if (chunk_fcc == FOURCC_avih) {
            /* 主AVI头部 */
            if (pos + 8 + sizeof(AVI_MAIN_HEADER) <= buf_size) {
                const AVI_MAIN_HEADER *avih = (const AVI_MAIN_HEADER *)(buf + pos + 8);
                result->width = avih->dwWidth;
                result->height = avih->dwHeight;
                result->total_frames = avih->dwTotalFrames;
                if (avih->dwMicroSecPerFrame > 0) {
                    result->fps = 1000000 / avih->dwMicroSecPerFrame;
                }
                printf("avih: %dx%d, fps=%d, frames=%d",
                       result->width, result->height, result->fps, result->total_frames);
            }
            pos += 8 + chunk_size;
            if (chunk_size & 1) {
                pos++;
            }

        } else if (chunk_fcc == FOURCC_strh) {
            /* 流头部 */
            if (pos + 8 + sizeof(AVI_STREAM_HEADER) <= buf_size) {
                const AVI_STREAM_HEADER *strh = (const AVI_STREAM_HEADER *)(buf + pos + 8);

                if (strh->fccType == FOURCC_vids) {
                    /* 视频流 */
                    result->has_video = 1;
                    result->video_stream_id = stream_index;
                    result->video_codec = strh->fccHandler;
                    result->video_coding_type = get_video_coding_type(strh->fccHandler);
                    if (strh->dwScale > 0) {
                        result->fps = strh->dwRate / strh->dwScale;
                    }
                    /* 构建视频chunk标识符: 如"00dc" */
                    snprintf(result->video_chunk_id, sizeof(result->video_chunk_id),
                             "%02ddc", stream_index);
                    current_stream_type = 1;
                    fourcc_to_str(strh->fccHandler, fcc_str);
                    printf("video stream[%d]: codec=%s, fps=%d, chunk_id=%s",
                           stream_index, fcc_str, result->fps, result->video_chunk_id);

                } else if (strh->fccType == FOURCC_auds) {
                    /* 音频流 */
                    result->has_audio = 1;
                    result->audio_stream_id = stream_index;
                    /* 构建音频chunk标识符: 如"01wb" */
                    snprintf(result->audio_chunk_id, sizeof(result->audio_chunk_id),
                             "%02dwb", stream_index);
                    current_stream_type = 2;
                    fourcc_to_str(strh->fccHandler, fcc_str);
                    printf("audio stream[%d]: handler=%s, chunk_id=%s",
                           stream_index, fcc_str, result->audio_chunk_id);
                }
                stream_index++;  // 处理完一个流，编号递增
            }
            pos += 8 + chunk_size;
            if (chunk_size & 1) {
                pos++;
            }

        } else if (chunk_fcc == FOURCC_strf) {
            /* 流格式 - 根据current_stream_type判断是视频还是音频 */
            if (current_stream_type == 1 && result->width == 0) {
                /* 视频格式 */
                if (pos + 8 + sizeof(BITMAPINFOHEADER) <= buf_size) {
                    const BITMAPINFOHEADER *bih = (const BITMAPINFOHEADER *)(buf + pos + 8);
                    if (result->width == 0) {
                        result->width = bih->biWidth;
                        result->height = bih->biHeight > 0 ? bih->biHeight : -bih->biHeight;
                    }
                    if (result->video_codec == 0) {
                        result->video_codec = bih->biCompression;
                        result->video_coding_type = get_video_coding_type(bih->biCompression);
                    }
                    fourcc_to_str(bih->biCompression, fcc_str);
                    printf("video format: %dx%d, compression=%s",
                           result->width, result->height, fcc_str);
                }
            } else if (current_stream_type == 2 && result->audio_sample_rate == 0) {
                /* 音频格式 */
                if (pos + 8 + sizeof(WAVEFORMATEX) <= buf_size) {
                    const WAVEFORMATEX *wfx = (const WAVEFORMATEX *)(buf + pos + 8);
                    result->audio_format = wfx->wFormatTag;
                    result->audio_channels = wfx->nChannels;
                    result->audio_sample_rate = wfx->nSamplesPerSec;
                    result->audio_bits = wfx->wBitsPerSample;
                    result->audio_coding_type = get_audio_coding_type(wfx->wFormatTag);
                    printf("audio format: %dHz, %dch, %dbit, fmt=0x%04x",
                           result->audio_sample_rate, result->audio_channels,
                           result->audio_bits, result->audio_format);
                }
            }
            pos += 8 + chunk_size;
            if (chunk_size & 1) {
                pos++;
            }

        } else if (chunk_fcc == FOURCC_idx1) {
            /* 索引 */
            result->idx1_offset = pos + 8;
            result->idx1_size = chunk_size;
            printf("idx1 found at offset: %d, size: %d", result->idx1_offset, result->idx1_size);
            pos += 8 + chunk_size;
            if (chunk_size & 1) {
                pos++;
            }

        } else {
            /* 其他chunk，跳过 */
            pos += 8 + chunk_size;
            if (chunk_size & 1) {
                pos++;    // 奇数大小需要填充
            }
        }

        /* 防止无限循环 */
        if (chunk_size == 0) {
            printf("zero size chunk, abort");
            break;
        }
    }

    /* 验证解析结果 */
    if (result->has_video || result->has_audio) {
        result->valid = 1;
        // printf("=== AVI Parse Result ===");
        // printf("  Video: %s (stream=%d, chunk=%s, %dx%d @ %dfps)",
        //          result->has_video ? "YES" : "NO",
        //          result->video_stream_id, result->video_chunk_id,
        //          result->width, result->height, result->fps);
        // printf("  Audio: %s (stream=%d, chunk=%s, %dHz, %dch)",
        //          result->has_audio ? "YES" : "NO",
        //          result->audio_stream_id, result->audio_chunk_id,
        //          result->audio_sample_rate, result->audio_channels);
        // printf("  movi: offset=%d, size=%d", result->movi_offset, result->movi_size);
        // printf("  idx1: offset=%d, size=%d", result->idx1_offset, result->idx1_size);
        return 0;
    }

    printf("no valid streams found");
    return -4;
}


void avi_parser_result_dump(const struct avi_parser_result *result)
{
    if (!result) {
        printf("avi_parser_result: NULL\n");
        return;
    }

    printf("=== AVI Parser Result ===\n");
    printf("valid: %d\n", result->valid);
    printf("file_size: %u\n", result->file_size);

    printf("--- Video ---\n");
    printf("  has_video: %d\n", result->has_video);
    printf("  video_stream_id: %d\n", result->video_stream_id);
    printf("  video_chunk_id: %s\n", result->video_chunk_id);
    printf("  width: %d\n", result->width);
    printf("  height: %d\n", result->height);
    printf("  fps: %d\n", result->fps);
    printf("  video_codec: 0x%08X\n", result->video_codec);
    printf("  video_coding_type: %d\n", result->video_coding_type);
    printf("  total_frames: %u\n", result->total_frames);

    printf("--- Audio ---\n");
    printf("  has_audio: %d\n", result->has_audio);
    printf("  audio_stream_id: %d\n", result->audio_stream_id);
    printf("  audio_chunk_id: %s\n", result->audio_chunk_id);
    printf("  audio_channels: %d\n", result->audio_channels);
    printf("  audio_sample_rate: %d\n", result->audio_sample_rate);
    printf("  audio_bits: %d\n", result->audio_bits);
    printf("  audio_format: 0x%04X\n", result->audio_format);
    printf("  audio_coding_type: %d\n", result->audio_coding_type);

    printf("--- Offsets ---\n");
    printf("  movi_offset: %u\n", result->movi_offset);
    printf("  movi_size: %u\n", result->movi_size);
    printf("  idx1_offset: %u\n", result->idx1_offset);
    printf("  idx1_size: %u\n", result->idx1_size);
}


uint32_t avi_calc_idx1_offset(const struct avi_parser_result *result)
{
    if (!result || !result->valid || result->movi_offset == 0) {
        return 0;
    }

    // idx1 位于 movi LIST 之后
    // movi LIST 结构: "LIST" (4) + size (4) + "movi" (4) + data
    // movi_offset 指向 "movi" 之后的数据起始
    // 所以 movi LIST 起始 = movi_offset - 12
    // movi LIST 结束 = movi_offset - 12 + 8 + (movi_size + 4) = movi_offset + movi_size
    uint32_t movi_list_end = result->movi_offset + result->movi_size;

    // 考虑对齐
    if (movi_list_end & 1) {
        movi_list_end++;
    }

    printf("idx1 expected at offset: %u (file_size=%u)", movi_list_end, result->file_size);
    return movi_list_end;
}

uint32_t avi_calc_idx1_download_size(const struct avi_parser_result *result)
{
    if (!result || !result->valid) {
        return 0;
    }

    uint32_t idx1_offset = avi_calc_idx1_offset(result);
    if (idx1_offset == 0 || idx1_offset >= result->file_size) {
        return 64 * 1024;  // 默认64KB
    }

    // idx1大小 = file_size - idx1_offset
    // 加上一些余量
    uint32_t size = result->file_size - idx1_offset + 1024;

    printf("idx1 download size: %u bytes", size);
    return size;
}

