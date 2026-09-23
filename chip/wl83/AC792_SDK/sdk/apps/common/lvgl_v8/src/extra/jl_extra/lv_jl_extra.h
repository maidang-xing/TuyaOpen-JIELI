/**
 * @file jl_common.h
 *
 */

#ifndef LV_JL_EXTRA_H
#define LV_JL_EXTRA_H

#ifdef __cplusplus
extern "C" {
#endif

/*********************
 *      INCLUDES
 *********************/

#include "gui/jl_gui.h"
#include "gui/gui_common.h"
#include "libs/jl_libs.h"
#include "others/jl_others.h"
#include "widgets/jl_widgets.h"
/*********************
 *      DEFINES
 *********************/

/**********************
 *      TYPEDEFS
 **********************/

/**********************
 * GLOBAL PROTOTYPES
 **********************/

/**
 * Initialize the jieli components
 */
void lv_jl_extra_init(void);

/**********************
 *      MACROS
 **********************/

#ifdef __cplusplus
} /*extern "C"*/
#endif

#endif /*JL_COMMON_H*/
