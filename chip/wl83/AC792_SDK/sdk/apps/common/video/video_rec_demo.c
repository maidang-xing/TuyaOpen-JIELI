#include "server/video_server.h"
#include "system/includes.h"
#include "server/audio_dev.h"
#include "video/video_ioctl.h"
#include "video/videobuf.h"
#include "fs/fs.h"

#define CYCLE_TIME 500 * 60
#define __ALIGN_2(a)   (((a) + 1) / 2 * 2)

struct VideoRecParams {
    u8 bindex;
    u32 cycle_time;
    u8  task_kill;
    int pid;
    struct video_buffer b;
    void *fd;
    int (*packet_cb)(u8 type, u8 *buf, u32 size);
    void *buf;
    int buf_len;
};

struct VideoRecParams video_rec;

static void video_rec_task(void *p)
{
    int err = 0;
    struct VideoRecParams *channel = &video_rec;
    while (1) {
        if (channel->task_kill) {
            printf("video rec task exit");
            break;
        }
        if (err == 0) {
            channel->b.noblock = 0;
            channel->b.timeout = 10;
            channel->b.index = 0;
        }
        err = dev_ioctl(channel->fd, VIDIOC_DQBUF, (unsigned int)&channel->b);
        if (!err) {
            if (channel->packet_cb) {
                channel->packet_cb(VIDEO_REC_JPEG_TYPE_VIDEO, (u8 *)channel->b.baddr, channel->b.len);
            }
            dev_ioctl(channel->fd, VIDIOC_QBUF, (unsigned int)&channel->b);
            channel->b.len = 0;
        }
    }
}

static int stream_packet_cb(u8 type, u8 *buf, u32 size)
{
    u32 *head = (u32 *)buf;
    if (size <= 512) { //过滤补帧
        return size;
    }

    if (type == VIDEO_REC_JPEG_TYPE_VIDEO) {
        printf("size:%d \n", size);
    }
    return size;
}

static int video_rec_start(char *video_name, int width, int height, int des_fps)
{
    int err;
    struct video_format f;
    struct video_reqbufs breq;
    struct VideoRecParams *channel = &video_rec;

    channel->packet_cb = stream_packet_cb;
    memset(&f, 0, sizeof(struct video_format));
    channel->fd = dev_open(video_name, NULL);
    if (channel->fd == NULL) {
        printf("video_dev_open: %s", video_name);
        return -ENODEV;
    }
    f.type = VIDEO_BUF_TYPE_VIDEO_CAPTURE;
    f.camera_type = VIDEO_CAMERA_NORMAL;
    f.win.width = __ALIGN_2(width);
    f.win.height = __ALIGN_2(height);
    /* f.win.mirror = rec->mirror; */
    f.src_width = 0;
    f.src_height = 0;
    f.online = 1;
    f.pixelformat = VIDEO_PIX_FMT_JPEG | VIDEO_PIX_FMT_YUV420;

    err = dev_ioctl(channel->fd, VIDIOC_SET_FMT, (u32)&f);
    if (err) {
        goto __err1;
    }

    if ((channel->buf_len == 0) && (channel->buf == NULL)) {
        channel->buf_len = 2 * 1024 * 1024;
    }
    breq.buf = channel->buf;
    breq.size = channel->buf_len;
    err = dev_ioctl(channel->fd, VIDIOC_REQBUFS, (unsigned int)&breq);
    if (err) {
        goto __err1;
    }
    struct video_dev_fps fps;

    dev_ioctl(channel->fd, VIDIOC_GET_FPS, (u32)&fps);
    fps.camera_fps = des_fps;
    fps.real_fps    = des_fps;
    fps.target_fps  = des_fps;
    fps.tlp_time	= des_fps;
    dev_ioctl(channel->fd, VIDIOC_SET_FPS, (u32)&fps);

    channel->cycle_time = CYCLE_TIME;
    dev_ioctl(channel->fd, VIDIOC_SET_CYC_TIME, (u32)channel->cycle_time);
    memset(&channel->b, 0, sizeof(struct video_buffer));

    struct video_enc_attr attr;
    struct mjpg_s_attr s_attr;
    attr.format = VID_PIX_FMT_MJPG;
    attr.attr = &s_attr;
    dev_ioctl(channel->fd, VIDIOC_GET_S_ATTR, (u32)&attr);
    s_attr.head_len = 0;
    s_attr.quality = VIDEO_LOW_Q;;
    s_attr.abr_kbps = 4000;
    dev_ioctl(channel->fd, VIDIOC_SET_S_ATTR, (u32)&attr);
    err = dev_ioctl(channel->fd, VIDIOC_SET_STOP_FRAME_INTERVAL, (u32)channel->cycle_time);
    if (err) {
        goto __err1;
    }
    err = dev_ioctl(channel->fd, VIDIOC_STREAM_ON, (u32)&channel->bindex);
    if (err) {
        printf("video_stream_on: err = %d", err);
        goto __err1;
    }

    err = thread_fork("video_rec_demo", 10, 1024, 1024, &channel->pid, video_rec_task, channel);
    if (err) {
        goto __err2;
    }
    printf("%s_rec_start: eixt", video_name);
    return 0;
__err2:
    dev_ioctl(channel->fd, VIDIOC_STREAM_OFF, (u32)&channel->bindex);
__err1:
    dev_close(channel->fd);
    channel->fd = NULL;
    return err;
}

static int video_rec_stop()
{
    int err;
    struct VideoRecParams *channel = &video_rec;

    printf("video_rec_stop_in");

    if (channel->fd) {
        dev_ioctl(channel->fd, VIDIOC_STREAM_OFF, channel->bindex);
    }

    if (channel->pid) {
        channel->task_kill = true;
        thread_kill(&channel->pid, KILL_WAIT);
        channel->task_kill = false;
    }

    if (channel->fd) {
        dev_close(channel->fd);
        channel->fd = NULL;
    }
    printf("video_rec_stop_exit");

    return 0;
}

