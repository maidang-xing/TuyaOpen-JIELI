#include "server/video_server.h"
#include "system/includes.h"
#include "server/audio_dev.h"
#include "video/video_ioctl.h"
#include "video/videobuf.h"
#include "lcd_config.h"
#include "fs/fs.h"

#define __ALIGN_2(a)   (((a) + 1) / 2 * 2)
#define __ALIGN_16(a)   (((a) + 15) / 16 * 16)
#define __ALIGN_8(a)   (((a) + 7) / 8 * 8)

struct VideoDecParams {
    int width;
    int height;
    void *fd;
};

struct VideoDecParams video_dec_;

static int jpeg_get_size(u8 *stream, int len, u16 *width, u16 *height, u16 *format)
{
    u8 marker;
    int chunk_len;

    if ((stream[0] != 0xFF) || (stream[1] != 0xD8)) {
        printf("not jpg picture.");
        return -EINVAL;
    }

    stream += 2;

    while (1) {
        if (*stream++ != 0xFF) {
            return -EINVAL;
        }

        while (*stream == 0xFF) {
            stream++;
        }

        marker = *stream++;
        chunk_len = (u16)(stream[0] << 8) | stream[1];

        if (marker == 0xC0) {
            *height = (u16)((stream[3] << 8) | stream[4]);
            *width  = (u16)((stream[5] << 8) | stream[6]);
            /* printf("image info : %d x %d.\n", *width, *height); */
            int offset = 8;
            while (offset < chunk_len) {
                if (*(stream + offset) == 0x1) {
                    u8 sample_Y = *(stream + offset + 1);
                    if (sample_Y == 0x11) {
                        *format = VIDEO_PIX_FMT_YUV444;
                        *width = __ALIGN_8(*width);
                        *height = __ALIGN_8(*height);
                    } else if (sample_Y == 0x22) {
                        *format = VIDEO_PIX_FMT_YUV420;
                        *width = __ALIGN_16(*width);
                        *height = __ALIGN_16(*height);
                    } else {
                        *format = VIDEO_PIX_FMT_YUV422;
                        *width = __ALIGN_16(*width);
                        *height = __ALIGN_8(*height);
                    }
                    break;
                }
                offset += 3;
            }
            break;
        }

        stream += chunk_len;
    }
    return 0;
}


/* -----------------------------------------------------------------------*/
/**
 * @brief video_dec_start 传入jpeg并显示屏幕
 *
 * @Params buf
 * @Params size
 *
 * @return
 */
/* -----------------------------------------------------------------------*/
static int video_dec_start(u8 *buf, int size)
{
    int err;
    u16 width, height, data_format;
    struct video_format f = {0};
    struct jpg_dec_s_attr s_attr = {0};
    u8 *dec_buf;
    int dec_len;

    dec_buf = buf;
    dec_len = size;

    err = jpeg_get_size((u8 *)dec_buf, dec_len, &width, &height, &data_format);
    if (err) {
        return -EFAULT;
    }
    printf("w:%d, h:%d, format:%d", width, height, data_format);

    if ((video_dec_.fd) && ((width != video_dec_.width) || (height != video_dec_.height))) {
        dev_ioctl(video_dec_.fd, VIDIOC_PLAY, 0);
        dev_close(video_dec_.fd);
        video_dec_.fd = NULL;
    }

    if (!video_dec_.fd) {
        video_dec_.fd = dev_open("video_dec", NULL);
        if (!video_dec_.fd) {
            printf("!video_dec_.fd\n");
            return -EINVAL;
        }

        memset(&f, 0x0, sizeof(f));
        f.type 		    = VIDEO_BUF_TYPE_VIDEO_PLAY;
        f.pixelformat 	= VIDEO_PIX_FMT_JPEG | data_format;
        f.src_width     = width;
        f.src_height 	= height;
        f.win.width  	= __ALIGN_8(LCD_W);
        f.win.height 	= __ALIGN_2(LCD_H);
        f.win.mirror  = 0;
        f.win.combine = 1;
        f.private_data  = (void *)"fb1";
        f.dis_rotate = 0;
        f.disp_id   = 0;

        dev_ioctl(video_dec_.fd, VIDIOC_SET_FMT, (u32)&f);
        dev_ioctl(video_dec_.fd, VIDIOC_PLAY, 1);
        video_dec_.width = width;
        video_dec_.height = height;
    }

    if (dec_len != dev_write(video_dec_.fd, (void *)dec_buf, dec_len)) {
        return -EFAULT;
    }
    return 0;
}

static int video_dec_stop()
{
    printf("video_dec_stop");
    if (video_dec_.fd) {
        dev_ioctl(video_dec_.fd, VIDIOC_PLAY, 0);
        dev_close(video_dec_.fd);
        video_dec_.fd = NULL;
    }
    return 0;
}

