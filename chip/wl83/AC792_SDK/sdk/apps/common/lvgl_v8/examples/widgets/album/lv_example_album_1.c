#include "../../lv_examples.h"
#if LV_USE_ALBUM && LV_BUILD_EXAMPLES
void test_album_album_1_album_load_more_cb(lv_obj_t *obj)
{
    static int index = 1;
    index ++;
    if (index == 2) {
        lv_album_add_pic(obj, LV_SYMBOL_NEXT);

    }

}
void lv_example_album_1(void)
{
    // 示例1：创建指定大小的相册
    lv_obj_t   *album = lv_album_create(lv_scr_act());
    lv_obj_set_style_bg_opa(album, LV_OPA_COVER, LV_PART_MAIN);
    lv_obj_set_style_bg_color(album, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN);

    lv_coord_t scr_w = (lv_coord_t)lv_disp_get_hor_res(NULL);
    lv_coord_t scr_h = (lv_coord_t)lv_disp_get_ver_res(NULL);
    lv_obj_set_size(album, 720, 413);
    static int load_count = 0;
    //增加相片
    lv_album_add_pic(album, LV_SYMBOL_OK);
    lv_album_add_pic(album, LV_SYMBOL_PLAY);
    lv_album_set_auto_load(album, true);
    lv_album_set_load_more_cb(album, test_album_album_1_album_load_more_cb);

    lv_album_effect_cfg_t test_album_album_1_effect_cfg = {
        .type = LV_ALBUM_EFFECT_EDGE_ROTATE,
        .anim_time = 400,
        .path_cb = lv_anim_path_ease_out,
        .params.edge_rotate.angle = 60,
    };
    lv_album_set_effect(album, LV_ALBUM_EFFECT_EDGE_ROTATE, &test_album_album_1_effect_cfg);
}
#endif
