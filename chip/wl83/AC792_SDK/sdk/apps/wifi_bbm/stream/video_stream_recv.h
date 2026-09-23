#ifndef VIDEO_STREAM_RECV_H
#define VIDEO_STREAM_RECV_H
#include "system/includes.h"

#define STREAM_RECV_BUF_SIZE               100 * 1024  //socket接收缓存大小
#define STREAM_PARSE_BUF_SIZE              STREAM_RECV_BUF_SIZE
#define STREAM_PACKET_VIDEO_QUEUE_SIZE     300 * 1024
#define STREAM_PACKET_AUDIO_QUEUE_SIZE     100 * 1024

typedef enum {
    VIDEO_FRAME = 0x01,
    AUDIO_FRAME = 0x02,
} FRAME_TYPE;

struct video_stream_recv_hdl {
    void *stream_recv_sockfd;
    char *net_path;
    int stream_recv_task_pid;
    u8 stream_recv_task_exit;
    char *recv_buf;
    int recv_buf_size;
    void (*add_dev_notify)(u32 ip_addr);
    void (*del_dev_notify)(u32 ip_addr);

    struct list_head dev_list;
};

int video_stream_recv_create(struct video_stream_recv_hdl **hdl);
int video_stream_recv_init(struct video_stream_recv_hdl *recv_hdl, char *net_path);
void video_stream_recv_set_dev_notify(struct video_stream_recv_hdl *recv_hdl, void (*add_dev_notify)(u32), void (*del_dev_notify)(u32));
int video_stream_recv_start(struct video_stream_recv_hdl *recv_hdl);
int video_stream_recv_stop(struct video_stream_recv_hdl *recv_hdl);
int video_stream_recv_destroy(struct video_stream_recv_hdl **hdl);
int video_stream_recv_acquire_frame(struct video_stream_recv_hdl *recv_hdl, u32 ip_addr,
                                    u8 **frame_buf, int *frame_len, FRAME_TYPE frame_type);
int video_stream_recv_acquire_frame_block(struct video_stream_recv_hdl *recv_hdl, u32 ip_addr,
        u8 **frame_buf, int *frame_len, FRAME_TYPE frame_type, int timeout_ms);
void video_stream_recv_release_frame(struct video_stream_recv_hdl *recv_hdl, u8 *frame_buf);

/**
 * 录像接口: 将指定设备的音视频流封装为 AVI 文件
 *
 * @param recv_hdl         video_stream_recv 句柄
 * @param ip_addr          远端设备 IP（网络字节序）
 * @param file_path        AVI 文件完整路径
 * @param video_width      视频宽度
 * @param video_height     视频高度
 * @param fps              视频帧率
 * @param audio_sample_rate 音频采样率 (0 表示不录制音频)
 * @param audio_channels   音频通道数
 * @param audio_bits       音频位深
 * @return 0 成功, <0 失败
 */
int video_stream_recv_rec_start(struct video_stream_recv_hdl *recv_hdl, u32 ip_addr,
                                const char *file_path, int video_width, int video_height,
                                double fps, int audio_sample_rate, int audio_channels, int audio_bits);

/**
 * 停止录像
 *
 * @param recv_hdl         video_stream_recv 句柄
 * @param ip_addr          远端设备 IP（网络字节序）
 * @return 0 成功, <0 失败
 */
int video_stream_recv_rec_stop(struct video_stream_recv_hdl *recv_hdl, u32 ip_addr);


#endif // VIDEO_STREAM_RECV_H

