#ifndef PIPELINE_JPEG_DEC_H
#define PIPELINE_JPEG_DEC_H

#include "system/includes.h"
#include "pipeline_core.h"
#include "asm/jpeg_codec.h"

int pipeline_jpeg_dec_one_frame(pipe_core_t *pipeline_core, u8 *buf, int len);
int pipeline_jpeg_dec_init(pipe_core_t **pipe_core, struct video_format *f);
int pipeline_jpeg_dec_exit(pipe_core_t **pipe_core);
void pipeline_jpeg_dec_format_init(struct video_format *f, struct video_window *win,
                                   int src_w, int src_h, char *fb);


#endif // PIPELINE_JPEG_DEC_H



