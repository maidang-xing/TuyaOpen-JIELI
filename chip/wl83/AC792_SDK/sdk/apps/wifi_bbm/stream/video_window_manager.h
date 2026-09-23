#ifndef VIDEO_WINDOW_MANAGER_H
#define VIDEO_WINDOW_MANAGER_H

#include "video_ioctl.h"

void video_window_manager_init(void);
int video_window_manager_update_layout_mode(int device_count);
struct video_window *video_window_manager_get_window_by_index(int index);

#endif // VIDEO_WINDOW_MANAGER_H

