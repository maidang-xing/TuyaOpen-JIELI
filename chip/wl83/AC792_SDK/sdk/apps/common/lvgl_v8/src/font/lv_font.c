/**
 * @file lv_font.c
 *
 */

/*********************
 *      INCLUDES
 *********************/

#include "lv_font.h"
#include "../misc/lv_utils.h"
#include "../misc/lv_log.h"
#include "../misc/lv_assert.h"

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

/**********************
 * GLOBAL PROTOTYPES
 **********************/

/**********************
 *      MACROS
 **********************/

/**********************
 *   GLOBAL FUNCTIONS
 **********************/

#if LV_USE_GPU_JL_GPU2P5D
/* ------------------------------------------------------------------------------------*/
/**
 * @brief lv_font_jlgpu2p5d_draw_check_support
 *
 * @Params user_data
 *
 * @return
 */
/* ------------------------------------------------------------------------------------*/
bool lv_font_jlgpu2p5d_draw_check_support(void *user_data)
{
    if (user_data == NULL) {
        return false;
    }

    lv_font_jlgpu_privately_t *jlgpu_privately = (lv_font_jlgpu_privately_t *)user_data;

    return jlgpu_privately->is_support;
}

/**
 * Gets the vertex path of the glyph
 * @param font_p pointer to a font
 * @param letter a UNICODE character code
 * @return pointer to the vertex and path of the letter
 */
const lv_font_path_t *lv_font_jlgpu2p5d_get_glyph_vertex_path(const lv_font_t *font_p, uint32_t letter)
{
    LV_ASSERT_NULL(font_p);
    LV_ASSERT_NULL(font_p->user_data);

    lv_font_jlgpu_privately_t *jlgpu_privately = (lv_font_jlgpu_privately_t *)font_p->user_data;

    return jlgpu_privately->get_glyph_vertex_path(font_p, letter);
}
#endif

/**
 * Return with the bitmap of a font.
 * @param font_p pointer to a font
 * @param letter a UNICODE character code
 * @return pointer to the bitmap of the letter
 */
const uint8_t *lv_font_get_glyph_bitmap(const lv_font_t *font_p, uint32_t letter)
{
    LV_ASSERT_NULL(font_p);
    return font_p->get_glyph_bitmap(font_p, letter);
}

/**
 * Get the descriptor of a glyph
 * @param font_p pointer to font
 * @param dsc_out store the result descriptor here
 * @param letter a UNICODE letter code
 * @param letter_next the next letter after `letter`. Used for kerning
 * @return true: descriptor is successfully loaded into `dsc_out`.
 *         false: the letter was not found, no data is loaded to `dsc_out`
 */
bool lv_font_get_glyph_dsc(const lv_font_t *font_p, lv_font_glyph_dsc_t *dsc_out, uint32_t letter,
                           uint32_t letter_next)
{

    LV_ASSERT_NULL(font_p);
    LV_ASSERT_NULL(dsc_out);

#if LV_USE_FONT_PLACEHOLDER
    const lv_font_t *placeholder_font = NULL;
#endif

    const lv_font_t *f = font_p;

    dsc_out->resolved_font = NULL;

    while (f) {
        bool found = f->get_glyph_dsc(f, dsc_out, letter, letter_next);
        if (found) {
            if (!dsc_out->is_placeholder) {
                dsc_out->resolved_font = f;
                return true;
            }
#if LV_USE_FONT_PLACEHOLDER
            else if (placeholder_font == NULL) {
                placeholder_font = f;
            }
#endif
        }
        f = f->fallback;
    }

#if LV_USE_FONT_PLACEHOLDER
    if (placeholder_font != NULL) {
        placeholder_font->get_glyph_dsc(placeholder_font, dsc_out, letter, letter_next);
        dsc_out->resolved_font = placeholder_font;
        return true;
    }
#endif

    if (letter < 0x20 ||
        letter == 0xf8ff || /*LV_SYMBOL_DUMMY*/
        letter == 0x200c) { /*ZERO WIDTH NON-JOINER*/
        dsc_out->box_w = 0;
        dsc_out->adv_w = 0;
    } else {
#if LV_USE_FONT_PLACEHOLDER
        dsc_out->box_w = font_p->line_height / 2;
        dsc_out->adv_w = dsc_out->box_w + 2;
#else
        dsc_out->box_w = 0;
        dsc_out->adv_w = 0;
#endif
    }

    dsc_out->resolved_font = NULL;
    dsc_out->box_h = font_p->line_height;
    dsc_out->ofs_x = 0;
    dsc_out->ofs_y = 0;
    dsc_out->bpp   = 1;
    dsc_out->is_placeholder = true;

    return false;
}

/**
 * Get the width of a glyph with kerning
 * @param font pointer to a font
 * @param letter a UNICODE letter
 * @param letter_next the next letter after `letter`. Used for kerning
 * @return the width of the glyph
 */
uint16_t lv_font_get_glyph_width(const lv_font_t *font, uint32_t letter, uint32_t letter_next)
{
    LV_ASSERT_NULL(font);
    lv_font_glyph_dsc_t g;
    lv_font_get_glyph_dsc(font, &g, letter, letter_next);
    return g.adv_w;
}

/**********************
 *   STATIC FUNCTIONS
 **********************/
