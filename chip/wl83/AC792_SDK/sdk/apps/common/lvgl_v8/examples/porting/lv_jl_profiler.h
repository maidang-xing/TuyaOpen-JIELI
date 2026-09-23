/**
 * @file lv_jl_profiler.h
 *
 */

#ifndef LV_JL_PROFILER_H
#define LV_JL_PROFILER_H

#ifdef __cplusplus
extern "C" {
#endif

/*********************
 *      INCLUDES
 *********************/

/*********************
 *      DEFINES
 *********************/

/**********************
 *      TYPEDEFS
 **********************/

/**********************
 * GLOBAL PROTOTYPES
 **********************/

void lv_jl_profiler_init(int timeout);
void lv_jl_profilter_stop(void);

/**********************
 *      MACROS
 **********************/

#ifdef __cplusplus
} /*extern "C"*/
#endif

#endif /*LV_JL_PROFILER_H*/
