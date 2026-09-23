/*
 * @file lv_example_lyrics_1.c
 *
 * 演示了如何调用 lv_lyrics 控件的矢量缩放和2.5D变换接口
 */

#include "../../lv_examples.h"
#if LV_USE_LYRICS && LV_BUILD_EXAMPLES

#define CONFIG_UI_RES_PATH CONFIG_ROOT_PATH // SD 路径

//#define CONFIG_FONT_TTF_PATH CONFIG_UI_RES_PATH"font/simkai.ttf"    // windos 下完整楷体字库
#define CONFIG_FONT_TTF_PATH "mnt/sdfile/EXT_RESERVED/uipackres/ui/sub1.ttf" // 龘: flash
//#define CONFIG_FONT_TTF_PATH "mnt/sdfile/EXT_RESERVED/uipackres/ui/sub2.ttf"  // 《生僻字部分歌词》: flash

#define LYRICS_LETTER_NUM_MAX 256

static void set_angle(void *var, int32_t v)
{
    lv_obj_t *obj = (lv_obj_t *)var;
    lv_lyrics_set_rotation(obj, 0, v, 0);
    //lv_lyrics_fontimg_redarw(obj);
}

static void set_zoom(void *var, int32_t v)
{
    lv_obj_t *obj = (lv_obj_t *)var;
    //lv_lyrics_set_pos(obj, v, v);

    //lv_lyrics_set_zoom(obj, 128, 128);
    //lv_lyrics_set_zoom(obj, 256 + 128, 256 + 128);
    lv_lyrics_set_zoom(obj, v, v);
    lv_lyrics_fontimg_redarw(obj);
}

void lv_example_lyrics_1(void)
{
    printf("[%s]", __func__);

    char *text = "龘12345bjg";

    size_t text_len = strlen(text);


    uint32_t *letter_buf = (uint32_t *)lv_mem_alloc(sizeof(uint32_t) * text_len);    // 空间大小最大不会超过 text_len * 4

    uint16_t letter_num = 0;
    // 解析字符串中的每一个 unicode
    int ofs = 0;
    while (ofs < text_len) {
        uint32_t letter;
        uint32_t letter_next;
        _lv_txt_encoded_letter_next_2(text, &letter, &letter_next, &ofs);
        //printf("ofs = %d; letter = 0x%08x; letter_next = 0x%08x.", ofs, letter, letter_next);

        letter_buf[letter_num] = letter;
        printf("info.letter_buf[%d] = 0x%08x.", letter_num, letter_buf[letter_num]);

        letter_num++;
        assert(letter_num < LYRICS_LETTER_NUM_MAX);   // 歌词字符数量过大，有需求再修改
    }

    lv_obj_t *obj = lv_lyrics_create(lv_scr_act(), CONFIG_FONT_TTF_PATH, 64, 0, letter_buf, letter_num);
    if (obj == NULL) {
        printf("lv_lyrics_create is fail!!");
        goto example_exit;
    }

    lv_lyrics_set_pos(obj, 256, 256);

#if 1
    lv_anim_t a_angle;
    lv_anim_init(&a_angle);  // 初时化动画变量
    lv_anim_set_var(&a_angle, obj); //设置动画关联的对象img
    lv_anim_set_exec_cb(&a_angle, set_angle); //设置动画执行的回调函数set_angle
    lv_anim_set_values(&a_angle, 0, 3600); // 设置动画的范围，这里是角度0~360度
    lv_anim_set_time(&a_angle, 3000); //设置动画duration时间3000毫秒
    lv_anim_set_playback_time(&a_angle, 3000); // 设置动画回播时间3000毫秒
    lv_anim_set_repeat_count(&a_angle, LV_ANIM_REPEAT_INFINITE);//设置动画重复次数，这里是无穷次
    lv_anim_start(&a_angle); //启动动画播放
#endif

#if 1
    lv_anim_t a_zoom;
    lv_anim_init(&a_zoom);  // 初时化动画变量
    lv_anim_set_var(&a_zoom, obj); //设置动画关联的对象img
    lv_anim_set_exec_cb(&a_zoom, set_zoom); //设置动画执行的回调函数set_zoom
    lv_anim_set_values(&a_zoom, 256, 256 + 128); // 设置动画的范围，这里是缩放比例 0.5~1.0
    lv_anim_set_time(&a_zoom, 3000); //设置动画duration时间3000毫秒
    lv_anim_set_playback_time(&a_zoom, 3000); // 设置动画回播时间3000毫秒
    lv_anim_set_repeat_count(&a_zoom, LV_ANIM_REPEAT_INFINITE);//设置动画重复次数，这里是无穷次
    lv_anim_start(&a_zoom); //启动动画播放
#endif

example_exit:
    lv_mem_free(letter_buf);

    return;
}

#endif
