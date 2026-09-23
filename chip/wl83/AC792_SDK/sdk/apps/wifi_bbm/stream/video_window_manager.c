#include "system/includes.h"
#include "video_window_manager.h"
#include "video_stream_common.h"

#define LOG_TAG_CONST       VIDEO_WINDOW_MANAGER
#define LOG_TAG             "[VIDEO_WINDOW_MANAGER]"
#define LOG_ERROR_ENABLE
#define LOG_INFO_ENABLE
#define LOG_DUMP_ENABLE
#include "debug.h"


enum {
    LAYOUT_MODE_SINGLE = 1,
    LAYOUT_MODE_DOUBLE,
    LAYOUT_MODE_THRIPLE,
    LAYOUT_MODE_QUAD,
};

static struct video_window single_win = {
    .left = 0,
    .top = 0,
    .width = SCREEN_WIDTH,
    .height = SCREEN_HEIGHT,
    .mirror = DISP_MIRROR,
    .combine = 1,
};

static struct video_window double_win[2] = {
    {
        .left = 0,
        .top = 0,
        .width = SCREEN_WIDTH,
        .height = SCREEN_HEIGHT,
        .mirror = DISP_MIRROR,
        .combine = 1,
    },
    {
        .left = SCREEN_WIDTH - DOUBLE_SMALL_WIDTH,
        .top = SCREEN_HEIGHT - DOUBLE_SMALL_HEIGHT,
        .width = DOUBLE_SMALL_WIDTH,
        .height = DOUBLE_SMALL_HEIGHT,
        .mirror = DISP_MIRROR,
        .combine = 1,
    }
};

static struct video_window triple_win[3] = {
    {
        .left = 0,
        .top = 0,
        .width = SCREEN_WIDTH / 2,
        .height = SCREEN_HEIGHT / 2,
        .mirror = DISP_MIRROR,
        .combine = 1,
    },
    {
        .left = SCREEN_WIDTH / 2,
        .top = 0,
        .width = SCREEN_WIDTH / 2,
        .height = SCREEN_HEIGHT / 2,
        .mirror = DISP_MIRROR,
        .combine = 1,
    },
    {
        .left = SCREEN_WIDTH / 4,
        .top = SCREEN_HEIGHT / 2,
        .width = SCREEN_WIDTH / 2,
        .height = SCREEN_HEIGHT / 2,
        .mirror = DISP_MIRROR,
        .combine = 1,
    }
};
static struct video_window quad_win[4] = {
    {
        .left = 0,
        .top = 0,
        .width = SCREEN_WIDTH / 2,
        .height = SCREEN_HEIGHT / 2,
        .mirror = DISP_MIRROR,
        .combine = 1,
    },
    {
        .left = SCREEN_WIDTH / 2,
        .top = 0,
        .width = SCREEN_WIDTH / 2,
        .height = SCREEN_HEIGHT / 2,
        .mirror = DISP_MIRROR,
        .combine = 1,
    },
    {
        .left = 0,
        .top = SCREEN_HEIGHT / 2,
        .width = SCREEN_WIDTH / 2,
        .height = SCREEN_HEIGHT / 2,
        .mirror = DISP_MIRROR,
        .combine = 1,
    },
    {
        .left = SCREEN_WIDTH / 2,
        .top = SCREEN_HEIGHT / 2,
        .width = SCREEN_WIDTH / 2,
        .height = SCREEN_HEIGHT / 2,
        .mirror = DISP_MIRROR,
        .combine = 1,
    }
};

static struct {
    int current_layout_mode;
    int device_count;
    int initialized;
    int index;
} g_window_manager;


void video_window_manager_init(void)
{
    if (g_window_manager.initialized) {
        return;
    }

    g_window_manager.initialized = 1;
    g_window_manager.current_layout_mode = LAYOUT_MODE_SINGLE;
}

int video_window_manager_update_layout_mode(int device_count)
{
    if (device_count == 1) {
        g_window_manager.current_layout_mode = LAYOUT_MODE_SINGLE;
    } else if (device_count == 2) {
        g_window_manager.current_layout_mode = LAYOUT_MODE_DOUBLE;
    } else if (device_count == 3) {
        g_window_manager.current_layout_mode = LAYOUT_MODE_THRIPLE;
    } else if (device_count == 4) {
        g_window_manager.current_layout_mode = LAYOUT_MODE_QUAD;
    } else {
        log_error("Unsupported device count: %d\n", device_count);
        return -1;
    }

    g_window_manager.index = 0;
    g_window_manager.device_count = device_count;
    return 0;
}



struct video_window *video_window_manager_get_window_by_index(int index)
{
    if (check_indec_valid(index) != 0) {
        log_error("Invalid index: %d\n", index);
        return NULL;
    }

    int layout_mode = g_window_manager.current_layout_mode;
    switch (layout_mode) {
    case LAYOUT_MODE_SINGLE:
        return &single_win;
    case LAYOUT_MODE_DOUBLE:
        return &double_win[index];
    case LAYOUT_MODE_THRIPLE:
        return &triple_win[index];
    case LAYOUT_MODE_QUAD:
        return &quad_win[index];
    default:
        return NULL;
    }

    return NULL;
}

struct video_window *video_window_manager_get_window_next(void)
{
    if (g_window_manager.device_count == 0) {
        log_error("Device count is 0\n");
        return NULL;
    }

    int index = g_window_manager.index % g_window_manager.device_count;
    if (check_indec_valid(index) != 0) {
        log_error("Invalid index: %d\n", index);
        return NULL;
    }
    g_window_manager.index++;
    int layout_mode = g_window_manager.current_layout_mode;
    switch (layout_mode) {
    case LAYOUT_MODE_SINGLE:
        return &single_win;
    case LAYOUT_MODE_DOUBLE:
        return &double_win[index];
    case LAYOUT_MODE_THRIPLE:
        return &triple_win[index];
    case LAYOUT_MODE_QUAD:
        return &quad_win[index];
    default:
        return NULL;
    }
}


static int check_indec_valid(int index)
{
    if (index < 0 || index > g_window_manager.device_count - 1) {
        return -1;
    }
    return 0;
}
