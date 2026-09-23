/*
 * @file lv_example_img2p5d_1.c
 *
 * 说明：本用例基于 JLVG 支持 2P5D 变换实现: C 数组格式的图片的 2.5D 变换
 */

#include "../../lv_examples.h"
#if LV_USE_FONT2P5D && LV_BUILD_EXAMPLES

static void set_angle(void *var, int32_t v)
{
    lv_img2p5d_t *img2p5d = (lv_img2p5d_t *)var;

    lv_obj2p5d_set_angle(img2p5d, v);
}

static void set_zoom(void *var, int32_t v)
{
    lv_img2p5d_t *img2p5d = (lv_img2p5d_t *)var;

    lv_obj2p5d_set_zoom(img2p5d, v);
}

void lv_example_img2p5d_1(void)
{
    printf("[%s]", __func__);

    lv_obj_t *img2p5d = lv_img2p5d_create(lv_scr_act());

    lv_obj2p5d_set_pos(img2p5d, 200, 200);

    //lv_obj2p5d_set_axis(img2p5d, 1.0, 0.0, 0.0);  // 绕 x 轴
    lv_obj2p5d_set_axis(img2p5d, 0.0, 1.0, 0.0);  // 绕 y 轴

    lv_obj2p5d_set_pivot(img2p5d, 50, 50);
    LV_IMG_DECLARE(img_cogwheel_argb);
    lv_img2p5d_set_src(img2p5d, &img_cogwheel_argb);

#if 1
    lv_anim_t a_angle;
    lv_anim_init(&a_angle);  // 初时化动画变量
    lv_anim_set_var(&a_angle, img2p5d); //设置动画关联的对象img
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
    lv_anim_set_var(&a_zoom, img2p5d); //设置动画关联的对象img
    lv_anim_set_exec_cb(&a_zoom, set_zoom); //设置动画执行的回调函数set_zoom
    lv_anim_set_values(&a_zoom, 128, 512); // 设置动画的范围，这里是缩放比例 0.5~2
    lv_anim_set_time(&a_zoom, 1000); //设置动画duration时间1000毫秒
    lv_anim_set_playback_time(&a_zoom, 1000); // 设置动画回播时间1000毫秒
    lv_anim_set_repeat_count(&a_zoom, LV_ANIM_REPEAT_INFINITE);//设置动画重复次数，这里是无穷次
    lv_anim_start(&a_zoom); //启动动画播放
#endif

    return;
}

#endif
