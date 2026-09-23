/*
 * @file lv_example_font2p5d_1.c
 *
 * 说明：本用例基于 TinyTTF 和 JLVG 支持 2P5D 变换实现: .ttf 字库文件矢量字体的 2.5D 变换
 */

#include "../../lv_examples.h"
#if LV_USE_FONT2P5D && LV_BUILD_EXAMPLES && LV_USE_TINY_TTF && LV_TINY_TTF_FILE_SUPPORT

// 需要生成字库文件并烧写到 FLASH
#define CONFIG_FONT_TTF_SUB1 "mnt/sdfile/EXT_RESERVED/uipackres/ui/sub1.ttf"       // 龘

static void set_angle(void *var, int32_t v)
{
    lv_font2p5d_t *font2p5d = (lv_font2p5d_t *)var;

    lv_obj2p5d_set_angle(font2p5d, v);
}

static void set_zoom(void *var, int32_t v)
{
    lv_font2p5d_t *font2p5d = (lv_font2p5d_t *)var;

    lv_obj2p5d_set_zoom(font2p5d, v);
}

void lv_example_font2p5d_1(void)
{
    printf("[%s]", __func__);

    lv_obj_t *font2p5d = lv_font2p5d_create(lv_scr_act());

    lv_obj2p5d_set_pos(font2p5d, 200, 200);

    //lv_font_2p5dimg_set_axis(font2p5d, 1.0, 0.0, 0.0);  // 绕 x 轴
    lv_obj2p5d_set_axis(font2p5d, 0.0, 1.0, 0.0);  // 绕 y 轴

    lv_obj2p5d_set_pivot(font2p5d, 128, 128);

    lv_font_t *font = lv_tiny_ttf_create_file(CONFIG_FONT_TTF_SUB1, 256);
    uint32_t ofs = 0;
    uint32_t letter = _lv_txt_encoded_next("龘", &ofs);
    lv_font2p5d_set_letter(font2p5d, font, letter);

#if 1
    lv_anim_t a_angle;
    lv_anim_init(&a_angle);  // 初时化动画变量
    lv_anim_set_var(&a_angle, font2p5d); //设置动画关联的对象img
    lv_anim_set_exec_cb(&a_angle, set_angle); //设置动画执行的回调函数set_angle
    lv_anim_set_values(&a_angle, 0, 3600); // 设置动画的范围，这里是角度0~360度
    lv_anim_set_time(&a_angle, 5000); //设置动画duration时间5000毫秒
    lv_anim_set_playback_time(&a_angle, 5000); // 设置动画回播时间5000毫秒
    lv_anim_set_repeat_count(&a_angle, LV_ANIM_REPEAT_INFINITE);//设置动画重复次数，这里是无穷次
    lv_anim_start(&a_angle); //启动动画播放
#endif

#if 1
    lv_anim_t a_zoom;
    lv_anim_init(&a_zoom);  // 初时化动画变量
    lv_anim_set_var(&a_zoom, font2p5d); //设置动画关联的对象img
    lv_anim_set_exec_cb(&a_zoom, set_zoom); //设置动画执行的回调函数set_zoom
    lv_anim_set_values(&a_zoom, 128, 256); // 设置动画的范围，这里是缩放比例 0.5~1.0
    lv_anim_set_time(&a_zoom, 1000); //设置动画duration时间1000毫秒
    lv_anim_set_playback_time(&a_zoom, 1000); // 设置动画回播时间1000毫秒
    lv_anim_set_repeat_count(&a_zoom, LV_ANIM_REPEAT_INFINITE);//设置动画重复次数，这里是无穷次
    lv_anim_start(&a_zoom); //启动动画播放
#endif

    return;
}

#endif
