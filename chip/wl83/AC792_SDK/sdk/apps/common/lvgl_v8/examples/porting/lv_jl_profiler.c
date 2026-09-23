/**
 * @file lv_jl_profiler.c
 *
 */

/*********************
 *      INCLUDES
 *********************/

#include "lv_jl_profiler.h"
#include "lvgl.h"

#if LV_USE_PROFILER && LV_USE_PROFILER_BUILTIN

/* #include <stdio.h> */
#include "src/misc/lv_profiler_builtin.h"
/* #include "fs/fs.h" */
#include "app_config.h"

/*********************
 *      DEFINES
 *********************/

/**********************
 *      TYPEDEFS
 **********************/

/**********************
 *  STATIC PROTOTYPES
 **********************/

/**********************
 *  STATIC VARIABLES
 **********************/
static volatile uint8_t profilter_stop = 0;
static FILE *ofile = NULL;

static uint32_t tick_get_cb(void);
static void flush_cb(const char *buf);

/**********************
 *      MACROS
 **********************/

/**********************
 *   GLOBAL FUNCTIONS
 **********************/
static void timeout_to_stop_profiler(lv_timer_t *timer)
{
    printf(">>>> timeout_to_stop_profiler\n");
    lv_jl_profilter_stop();
}

void lv_jl_profiler_init(int timeout)
{
    lv_profiler_builtin_config_t config;
    lv_profiler_builtin_config_init(&config);
    config.tick_per_sec = 1000000; /* 1 sec = 1000000 usec */
    config.tick_get_cb = tick_get_cb;
    config.flush_cb = flush_cb;
    lv_profiler_builtin_init(&config);
    profilter_stop = 0;
    if (timeout) {
        lv_timer_t *t = lv_timer_create(timeout_to_stop_profiler, timeout, NULL);
        lv_timer_set_repeat_count(t, 1);
    }
}

/**********************
 *   STATIC FUNCTIONS
 **********************/

static uint32_t tick_get_cb(void)
{
    static uint32_t prev_tick = 0;
    static uint32_t cur_tick_us = 0;
    //uint32_t act_time = up_perf_gettime();
    uint32_t act_time = get_system_us();
    uint32_t elaps;

    /*If there is no overflow in sys_time simple subtract*/
    if (act_time >= prev_tick) {
        elaps = act_time - prev_tick;
    } else {
        elaps = UINT32_MAX - prev_tick + 1;
        elaps += act_time;
    }

    //cur_tick_us += TICK_TO_USEC(elaps);
    cur_tick_us += (elaps);
    prev_tick = act_time;
    return cur_tick_us;
}
static void flush_cb(const char *buf)
{
    //printf("%s", buf);
    if (profilter_stop) {
        return;
    }
    /* printf("len=%d\n", strlen(buf)); */
    if (ofile == NULL) {
        ofile = fopen(CONFIG_ROOT_PATH"output.txt", "wb");
    }
    if (ofile) {
        fwrite(buf, strlen(buf), 1, ofile);
    }

}
void lv_jl_profilter_stop(void)
{
    lv_profiler_builtin_flush();
    if (ofile) {
        fclose(ofile);
        ofile = NULL;
    }
    profilter_stop = 1;
}
#endif
