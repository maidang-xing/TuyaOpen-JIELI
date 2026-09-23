#include "app_config.h"
#ifdef CONFIG_UI_STYLE_LY_ENABLE
#include "lvgl.h"
#include "../generated/gui_guider.h"

#if !LV_USE_GUIBUILDER_SIMULATOR
#include "app_core.h"
#include "app_config.h"
#include "action.h"
#include "ui.h"
#endif

#if !LV_USE_GUIBUILDER_SIMULATOR
//专辑图片显示
static lv_img_dsc_t album_image_dsc = {0};

lv_img_dsc_t *lv_get_page_music_image_dsc(void)
{
    return &album_image_dsc;
}

void lv_update_ui_music_img(lv_img_dsc_t *image_dsc);
void lv_album_img_show(const uint8_t *jpg_buf, uint32_t jpg_buf_len)
{
    if (!jpg_buf || jpg_buf_len == 0) {
        return;
    }

    album_image_dsc.header.always_zero = 0;
    album_image_dsc.header.w = 200;
    album_image_dsc.header.h = 200;
    album_image_dsc.data = jpg_buf;
    album_image_dsc.data_size = jpg_buf_len;
    album_image_dsc.header.cf = LV_IMG_CF_TRUE_COLOR;

    lv_update_ui_music_img(&album_image_dsc);
}

void update_ui_music_img(lv_img_dsc_t *image_dsc)
{
    if (ui_is_act_scr(GUI_SCREEN_PAGE_MUSIC)) {
        lv_ui_page_music *ui_scr = ui_get_scr_ptr(&guider_ui, GUI_SCREEN_PAGE_MUSIC);
        lv_img_t *img = (lv_img_t *)ui_scr->page_music_img_3;
        lv_img_set_src(img, image_dsc);
    }
}


void lv_update_ui_music_img(lv_img_dsc_t *image_dsc)
{
    lvgl_rpc_post_func(update_ui_music_img, 1, image_dsc);
}
#endif
#endif
