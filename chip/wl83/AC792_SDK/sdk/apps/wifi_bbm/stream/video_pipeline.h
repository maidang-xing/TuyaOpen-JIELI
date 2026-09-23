#ifndef VIDEO_PIPELINE_H
#define VIDEO_PIPELINE_H

#include "system/includes.h"
#include "pipeline_core.h"
#include "asm/jpeg_codec.h"

int pipeline_dec_one_frame(pipe_core_t *pipeline_core, u8 *buf, int len);
int pipeline_dec_init(pipe_core_t **pipe_core, struct video_format *f);
int pipeline_camera_init(pipe_core_t **pipe_core, struct video_format *f, int camera_id);
int pipeline_exit(pipe_core_t **pipe_core);
int pipeline_set_zoom(pipe_core_t *pipe_core, void *arg);
void pipeline_format_init(struct video_format *f, struct video_window *win,
                          int src_w, int src_h, char *fb);


#endif // VIDEO_PIPELINE_H


