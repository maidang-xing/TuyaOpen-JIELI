/**
 * @file lv_port_disp.c
 *
 */
#include "lcd_config.h"

#ifdef USE_LVGL_V9_UI_DEMO

#ifndef CONFIG_DEMO_UI_PROJECT_ENABLE

/*********************
 *      INCLUDES
 *********************/
#define BOOL_DEFINE_CONFLICT
#include "app_config.h"
#include "lv_port_disp.h"
#include "os/os_api.h"
#include "asm/dcache.h"
#include <string.h>
#include "src/core/lv_refr_private.h"
#include "src/display/lv_display_private.h"
#include "src/misc/lv_timer_private.h"
#include "video/fb.h"

/*********************
 *      DEFINES
 *********************/

#define LV_DISP_DRV_MAX_NUM  2

/**********************
 *      TYPEDEFS
 **********************/

#if LV_COLOR_DEPTH == 16
#define LV_PIXEL_COLOR_T lv_color16_t
#elif LV_COLOR_DEPTH == 24
#define LV_PIXEL_COLOR_T lv_color_t
#elif LV_COLOR_DEPTH == 32
#define LV_PIXEL_COLOR_T lv_color32_t
#endif

struct lv_disp_user_data_t {
    u8 id;
    u16 disp_w;
    u16 disp_h;
    void *fb;
    struct fb_map_user map[2];
    lv_draw_buf_t draw_buf[2];
};

/**********************
 *  STATIC PROTOTYPES
 **********************/

static void *_disp_init(u8 id, u16 w, u16 h);
static void _lv_port_disp_prepare(u8 id, u16 disp_w, u16 disp_h);
static void _lv_port_draw_buf_update(lv_draw_buf_t *draw_buf, lv_display_t *disp, void *buf);
static void _lv_port_fill_color_key(void *buf, uint32_t pixel_cnt);
static void _lv_port_draw_buf_user_config(void *buf1, void *buf2);
static void _lv_port_redraw_all_now(void);
static void _lv_fb_combine_task_handler(lv_display_t *disp);
static void _lv_port_disp_event_cb(lv_event_t *e);
static void _lv_lcd_swap_fb(lv_display_t *disp, uint8_t *px_map);
static void disp_flush(lv_display_t *disp, const lv_area_t *area, uint8_t *px_map);
extern int fb_combine_task(u8 id, void *priv);

/**********************
 *  STATIC VARIABLES
 **********************/

static lv_display_t *lv_disp[LV_DISP_DRV_MAX_NUM];
#if (LV_DISP_UI_FB_NUM <= 1)
static volatile u8 g_ui_flush_mode = LV_DISP_UI_FB_NUM;
static char lvgl_send_fb_combine_event_remain_cnt[2] = {0, 0};
#endif

/**********************
 *   GLOBAL FUNCTIONS
 **********************/

u8 lvgl_get_fb_num(void)
{
    return LV_DISP_UI_FB_NUM;
}

#if (LV_DISP_UI_FB_NUM <= 1)
/*
 * Keep the lvgl8 single-UI-buffer handshake available in lvgl9 so
 * fb_combine can still drive the same UI/combine handshake in lvgl9.
 */
u8 lvgl_get_flush_mode(void)
{
    return g_ui_flush_mode;
}

void lvgl_set_flush_mode(u8 mode)
{
    g_ui_flush_mode = mode;
}

void lvgl_set_ui_flush_mode(u8 mode, void *buf1, void *buf2)
{
#if (LV_DISP_UI_FB_NUM == 0)
    static uint8_t *_ui_draw_buf;
    void *p1 = NULL;
    void *p2 = NULL;

    if (mode) {
        if (buf1) {
            p1 = buf1;
            p2 = buf2;
        } else if (buf2) {
            p1 = buf2;
        }
    }

    lvgl_set_flush_mode(mode);

    if (mode) {
        if (mode == 2) {
            if (_ui_draw_buf == NULL) {
                _ui_draw_buf = zalloc(LCD_W * LCD_H * LV_COLOR_DEPTH / 8);
                printf("malloc ui draw buf %x\n", _ui_draw_buf);
                ASSERT(_ui_draw_buf, "ui self flush mode buffer malloc err!");
            }
            _lv_port_draw_buf_user_config(_ui_draw_buf, NULL);
        } else {
            _lv_port_draw_buf_user_config(p1, p2);
        }

        if (lvgl_ui_is_suspended()) {
            lvgl_ui_resume();
        }
    } else {
        if (_ui_draw_buf) {
            printf("free ui draw buf %x\n", _ui_draw_buf);
            free(_ui_draw_buf);
            _ui_draw_buf = NULL;
        }
        _lv_port_draw_buf_user_config(NULL, NULL);
    }
#else
    (void)buf1;
    (void)buf2;
    lvgl_set_flush_mode(mode);
#endif
}

static void _fb_combine_task(void *priv)
{


    /*
     * In the lvgl9 no-fb0 port, dropping to mode 0 here strands the UI in
     * external-refresh mode and the restore timer path never brings it back.
     * Keep self-flush enabled so lv_timer_handler can continue driving UI timers.
     */
    fb_combine_task((u8)priv, NULL);
    lvgl_send_fb_combine_event_remain_cnt[(u8)priv] = 0;
}

int lvgl_send_fb_combine_event(u8 id)
{
    char *task_name;
    int err;
    int msg[3];

    if (lvgl_send_fb_combine_event_remain_cnt[id]) {
        return -1;
    }

    lvgl_send_fb_combine_event_remain_cnt[id] = 1;

    if (os_task_get_handle(LVGL_TASK_NAME) == NULL) {
        task_name = "app_core";
    } else {
        task_name = LVGL_TASK_NAME;
    }

    msg[0] = (int)_fb_combine_task;
    msg[1] = 1;
    msg[2] = id;
    err = os_taskq_post_type(task_name, Q_CALLBACK, ARRAY_SIZE(msg), msg);
    if (err) {
        lvgl_send_fb_combine_event_remain_cnt[id] = 0;
        printf("lvgl_send_fb_combine_event err=%d\n", err);
    }

    return err;
}
#endif

lv_display_t *lv_port_get_disp(uint8_t id)
{
    lv_display_t *disp = lv_disp[id];

    if (disp == NULL) {
        return lv_disp[0];
    }

    return disp;
}

void lv_port_refr_now(lv_display_t *disp)
{
    lv_timer_t tmr = {0};

    if (disp) {
        tmr.user_data = disp;
        lv_display_refr_timer(&tmr);
    } else {
        lv_display_t *d = lv_display_get_next(NULL);
        while (d) {
            tmr.user_data = d;
            lv_display_refr_timer(&tmr);
            d = lv_display_get_next(d);
        }
    }
}

int fb_combine_output_handler(void *out, u32 in0_addr, u32 in1_addr)
{
#if (LV_DISP_UI_FB_NUM <= 1)
    struct fb_map_user *omap = (struct fb_map_user *)out;
    uint16_t bpp = dma2d_get_format_bpp(omap->format) >> 3;

    (void)in0_addr;
    (void)in1_addr;

    if (lvgl_get_flush_mode()) {
        DcuInvalidRegion(omap->baddr, omap->width * omap->height * bpp);
        return 1;
    }

    DcuInvalidRegion(omap->baddr, omap->width * omap->height * bpp);
    _lv_port_draw_buf_user_config((void *)omap->baddr, NULL);
    _lv_port_redraw_all_now();
    lv_timer_handler();
#else
    (void)out;
    (void)in0_addr;
    (void)in1_addr;
#endif
    return 0;
}

void lv_port_disp_init(void)
{
    _lv_port_disp_prepare(0, LCD_W, LCD_H);
#if TCFG_LCD_SUPPORT_MULTI_DRIVER_EN
    _lv_port_disp_prepare(1, LCD1_W, LCD1_H);
#endif
}

/**********************
 *   STATIC FUNCTIONS
 **********************/

static void _lv_port_draw_buf_update(lv_draw_buf_t *draw_buf, lv_display_t *disp, void *buf)
{
    lv_color_format_t cf = lv_display_get_color_format(disp);
    uint32_t stride = lv_draw_buf_width_to_stride(lv_display_get_horizontal_resolution(disp), cf);
    uint32_t data_size = stride * lv_display_get_vertical_resolution(disp);

    if (buf == NULL) {
        return;
    }

    lv_draw_buf_init(draw_buf,
                     lv_display_get_horizontal_resolution(disp),
                     lv_display_get_vertical_resolution(disp),
                     cf,
                     stride,
                     buf,
                     data_size);
}

static void _lv_port_draw_buf_user_config(void *buf1, void *buf2)
{
    struct lv_disp_user_data_t *disp_fh = NULL;
    lv_display_t *disp = lv_display_get_next(NULL);

    if (disp == NULL) {
        disp = lv_port_get_disp(0);
    }

    while (disp) {
        disp_fh = lv_display_get_user_data(disp);
        if (disp_fh) {
            if (buf1) {
                _lv_port_draw_buf_update(&disp_fh->draw_buf[0], disp, buf1);
            } else {
                memset(&disp_fh->draw_buf[0], 0, sizeof(disp_fh->draw_buf[0]));
            }

            if (buf2) {
                _lv_port_draw_buf_update(&disp_fh->draw_buf[1], disp, buf2);
            } else {
                memset(&disp_fh->draw_buf[1], 0, sizeof(disp_fh->draw_buf[1]));
            }

            lv_display_set_draw_buffers(disp,
                                        buf1 ? &disp_fh->draw_buf[0] : NULL,
                                        buf2 ? &disp_fh->draw_buf[1] : NULL);
        }
        disp = lv_display_get_next(disp);
    }
}

static void _lv_port_redraw_all_now(void)
{
    lv_display_t *disp = lv_display_get_next(NULL);

    if (disp == NULL) {
        disp = lv_port_get_disp(0);
    }

    while (disp) {
        lv_area_t a;
        lv_area_set(&a, 0, 0,
                    lv_display_get_horizontal_resolution(disp) - 1,
                    lv_display_get_vertical_resolution(disp) - 1);
        lv_inv_area(disp, &a);
        disp = lv_display_get_next(disp);
    }
}

static void _lv_fb_combine_task_handler(lv_display_t *disp)
{
    lv_draw_buf_t *draw_buf;
    struct lv_disp_user_data_t *disp_fh;

    if (disp == NULL) {
        disp = lv_refr_get_disp_refreshing();
    }
    if (disp == NULL) {
        return;
    }

    draw_buf = lv_display_get_buf_active(disp);
    disp_fh = lv_display_get_user_data(disp);
    if (draw_buf == NULL || draw_buf->data == NULL || disp_fh == NULL) {
        return;
    }

    if (fb_combine_task(disp_fh->id, draw_buf->data) == 0) {
        dma_memset_sync(NO_CACHE_ADDR(draw_buf->data), 0x00, draw_buf->data_size);
        DcuInvalidRegion(draw_buf->data, draw_buf->data_size);
    }
}

static void _lv_port_disp_event_cb(lv_event_t *e)
{
#if (LV_DISP_UI_FB_NUM == 0)
    if (lv_event_get_code(e) == LV_EVENT_RENDER_START && lvgl_get_flush_mode()) {
        _lv_fb_combine_task_handler(lv_event_get_target(e));
    }
#else
    (void)e;
#endif
}

static void _lv_port_fill_color_key(void *buf, uint32_t pixel_cnt)
{
    /* Keep UI background aligned with fb_combine's color key so camera stays visible below fb0. */
#define LV_FB_COLOR_KEY_HEX  0x52aaa5

    uint32_t i;
    LV_PIXEL_COLOR_T *p = buf;
    lv_color_t key = lv_color_hex(LV_FB_COLOR_KEY_HEX);

    if (buf == NULL) {
        return;
    }

#if LV_COLOR_DEPTH == 16
    LV_PIXEL_COLOR_T pixel = {
        .red = key.red >> 3,
        .green = key.green >> 2,
        .blue = key.blue >> 3,
    };
#elif LV_COLOR_DEPTH == 24
    LV_PIXEL_COLOR_T pixel = key;
#elif LV_COLOR_DEPTH == 32
    LV_PIXEL_COLOR_T pixel = {
        .red = key.red,
        .green = key.green,
        .blue = key.blue,
        .alpha = 0xff,
    };
#endif

    for (i = 0; i < pixel_cnt; i++) {
        p[i] = pixel;
    }
}

static void *_disp_init(u8 id, u16 w, u16 h)
{
    void *fb = NULL;
    struct fb_draw_info info = {0};

    info.name = "fb0";
    info.fb_num = LV_DISP_UI_FB_NUM;
    info.width = w;
    info.height = h;
    info.real_width = w;
    info.real_height = h;
    info.x = 0;
    info.y = 0;
    info.out_id = id;
#if LV_COLOR_DEPTH == 32
    info.format = FB_COLOR_FORMAT_ARGB8888;
#elif LV_COLOR_DEPTH == 16
#if LV_COLOR_DEPTH_EXTEN == 24
    info.format = FB_COLOR_FORMAT_ARGB8565;
#else
    info.format = FB_COLOR_FORMAT_RGB565;
#endif
#else
#error "FB NOT SUPPORT INFO_FORMAT"
#endif
    info.combine = 1;
    info.z_order = 253;

    fb = fb_draw_open(&info);
    return fb;
}

static void _lv_port_disp_prepare(u8 id, u16 disp_w, u16 disp_h)
{
    struct lv_disp_user_data_t *disp_fh;
    lv_display_t *disp;
    void *buf1 = NULL;
    void *buf2 = NULL;

    disp_fh = zalloc(sizeof(*disp_fh));
    ASSERT(disp_fh, "lvgl v9 display user data malloc err");

    disp_fh->id = id;
    disp_fh->disp_w = disp_w;
    disp_fh->disp_h = disp_h;
#if (LV_DISP_UI_FB_NUM != 0)
    disp_fh->fb = _disp_init(id, disp_w, disp_h);
    ASSERT(disp_fh->fb, "lvgl v9 fb0 open err");
    /* Get both fb0 maps up front and hand them directly to LVGL as the draw buffers. */
    fb_draw_getmap(disp_fh->fb, &disp_fh->map[1]);
    buf2 = disp_fh->map[1].baddr;
    if (buf2) {
        fb_draw_putmap(disp_fh->fb, &disp_fh->map[1]);
    }

    fb_draw_getmap(disp_fh->fb, &disp_fh->map[0]);
    buf1 = disp_fh->map[0].baddr;

    if (buf1 == NULL) {
        buf1 = buf2;
        buf2 = NULL;
        memcpy(&disp_fh->map[0], &disp_fh->map[1], sizeof(struct fb_map_user));
        memset(&disp_fh->map[1], 0, sizeof(struct fb_map_user));
    }

    ASSERT(buf1, "lvgl v9 fb0 map get err");
#endif

    disp = lv_display_create(disp_w, disp_h);
    ASSERT(disp, "lvgl v9 display create err");

    disp->disp_id = id;
    lv_disp[id] = disp;

    lv_display_set_user_data(disp, disp_fh);
    lv_display_set_flush_cb(disp, disp_flush);
    lv_display_add_event_cb(disp, _lv_port_disp_event_cb, LV_EVENT_RENDER_START, NULL);

#if (LV_DISP_UI_FB_NUM == 0)
    lv_display_set_draw_buffers(disp, NULL, NULL);
    lv_display_set_render_mode(disp, LV_DISPLAY_RENDER_MODE_FULL);
    /*
     * Match the lvgl8 no-fb0 startup ordering: register the display first,
     * then open fb0 so fb_combine can bind the initial self-flush buffers
     * onto an already-existing display instance.
     */
    disp_fh->fb = _disp_init(id, disp_w, disp_h);
    ASSERT(disp_fh->fb, "lvgl v9 fb0 open err");
#else
    /* Start from the transparent key color; only widgets should become visible after compose. */
    _lv_port_fill_color_key(buf1, disp_w * disp_h);
    _lv_port_draw_buf_update(&disp_fh->draw_buf[0], disp, buf1);
    if (buf2) {
        _lv_port_fill_color_key(buf2, disp_w * disp_h);
        _lv_port_draw_buf_update(&disp_fh->draw_buf[1], disp, buf2);
    }

    lv_display_set_draw_buffers(disp,
                                &disp_fh->draw_buf[0],
                                buf2 ? &disp_fh->draw_buf[1] : NULL);
    /*
     * Keep the v9 port aligned with the proven lvgl8 fb0 path:
     * LVGL renders into full-screen fb0 buffers, and only swaps them on the
     * last dirty chunk after fb_draw_putmap()/getmap() completes.
     */
    lv_display_set_render_mode(disp, LV_DISPLAY_RENDER_MODE_DIRECT);
#endif

    /* Match the lvgl8 port: the outer UI task owns refresh scheduling. */
    lv_display_delete_refr_timer(disp);
}

static void _lv_lcd_swap_fb(lv_display_t *disp, uint8_t *px_map)
{
    struct lv_disp_user_data_t *disp_fh;
    lv_draw_buf_t *draw_buf;
    struct fb_map_user *map = NULL;
    struct fb_map_user next_map = {0};

    if (disp == NULL || px_map == NULL) {
        return;
    }

    disp_fh = lv_display_get_user_data(disp);
    if (disp_fh == NULL || disp_fh->fb == NULL) {
        return;
    }

#if (LV_DISP_UI_FB_NUM == 0)
    draw_buf = lv_display_get_buf_active(disp);
    if (lvgl_get_flush_mode() && draw_buf && draw_buf->data == px_map) {
        struct fb_map_user map_tmp = {0};

        map_tmp.baddr = px_map;
        map_tmp.transp = 1;
        fb_draw_putmap(disp_fh->fb, &map_tmp);
    }
    return;
#endif

    if (disp->buf_1 && disp->buf_1->data == px_map) {
        map = &disp_fh->map[0];
        draw_buf = disp->buf_1;
    } else if (disp->buf_2 && disp->buf_2->data == px_map) {
        map = &disp_fh->map[1];
        draw_buf = disp->buf_2;
    }

    if (map == NULL || draw_buf == NULL || map->baddr == NULL) {
        return;
    }

    /* Return the frame just flushed, then fetch the matching fb0 buffer back for the next draw pass. */
    fb_draw_putmap(disp_fh->fb, map);
    if (fb_draw_getmap(disp_fh->fb, &next_map) == 0 && next_map.baddr) {
        /*
         * fb_draw normally rotates between the same fixed fb0 addresses like lvgl8.
         * Only rebind the LVGL draw buffer if the driver hands back a different slot.
         */
        if (draw_buf->data != next_map.baddr) {
            _lv_port_draw_buf_update(draw_buf, disp, next_map.baddr);
        }
        memcpy(map, &next_map, sizeof(next_map));
    }
}

static void disp_flush(lv_display_t *disp, const lv_area_t *area, uint8_t *px_map)
{
    if (disp == NULL || px_map == NULL) {
        if (disp) {
            lv_display_flush_ready(disp);
        }
        return;
    }

#if (LV_DISP_UI_FB_NUM == 0)
    DcuFlushRegion(px_map, disp->buf_act->data_size);
    _lv_lcd_swap_fb(disp, px_map);
#else
    if (disp->flushing_last) {
        /* DIRECT mode swaps fb0 only after LVGL finishes the last dirty chunk. */
        DcuFlushRegion(px_map, disp->buf_act->data_size);
        _lv_lcd_swap_fb(disp, px_map);
    }
#endif

    lv_display_flush_ready(disp);
}

#endif

#endif
