/*
 * @file lv_example_lyrics_2.c
 *
 * 演示了如何调用 lv_lyrics 控件模拟实现歌词播放的demo
 */

#include "../../lv_examples.h"
#include "app_config.h"
#if LV_USE_LYRICS && LV_BUILD_EXAMPLES

#include "os/os_api.h"

#define CONFIG_UI_RES_PATH CONFIG_ROOT_PATH // SD 路径

#define CONFIG_FONT_TTF_PATH CONFIG_UI_RES_PATH"font/simkai.ttf"    // windos 下完整楷体字库
//#define CONFIG_FONT_TTF_PATH "mnt/sdfile/EXT_RESERVED/uipackres/ui/sub1.ttf" // 龘: flash
//#define CONFIG_FONT_TTF_PATH "mnt/sdfile/EXT_RESERVED/uipackres/ui/sub2.ttf"  // 《生僻字部分歌词》: flash

#define LYRICS_LETTER_NUM_MAX 256

static OS_SEM lyrics_example2_sem;
static lv_obj_t *curr_obj_0;
static lv_obj_t *curr_obj_1;

#if 1
const char *lyrics_example2_text[] = {
    "煢煢孑立 沆瀣一氣 踽踽獨行 醍醐灌頂",
    "綿綿瓜瓞 奉為圭臬 龍行龘龘 犄角旮旯",
    "娉婷嫋娜 涕泗滂沱 呶呶不休 不稂不莠",
    "咄嗟 蹀躞 耄耋 饕餮 囹圄 蘡薁 覬覦 齟齬",
    "狖軛鼯軒 怙惡不悛 其靁虺虺 醃臢孑孓",
    "陟罰臧否 針砭時弊 鱗次櫛比 一張一翕"
};
#else
const char *lyrics_example2_text[] = {
    "0123456789",
    "一二三四五六七八九十",
    "ABCDEFGHIJK",
    "abcdefghijk",
    "!@#$%^&*()",
    "-_=+[{]},<.>"
};
#endif

static int lyrics_example2_sem_pend(int timeout)
{
    return os_sem_pend(&lyrics_example2_sem, timeout);
}

static int lyrics_example2_sem_post(void)
{
    os_sem_set(&lyrics_example2_sem, 0);
    return os_sem_post(&lyrics_example2_sem);
}

static void lyrics_example2_play_anim_cb(void *obj, int32_t v)
{
    lv_lyrics_info *lyrics_info = (lv_lyrics_info *)(((lv_obj_t *)obj)->user_data);

    //lv_lyrics_set_pos(obj, v, v);

    //lv_lyrics_set_zoom(obj, 128, 128);
    //lv_lyrics_set_zoom(obj, 256 + 128, 256 + 128);
    lv_lyrics_set_zoom(obj, v, v);
    lv_lyrics_fontimg_redarw(obj);
}

static void lv_example_lyrics_2_letter(const char *text, uint16_t font_size, const char *font_file)
{
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
        //printf("info.letter_buf[%d] = 0x%08x.", letter_num, letter_buf[letter_num]);

        letter_num++;
        assert(letter_num < LYRICS_LETTER_NUM_MAX);   // 歌词字符数量过大，有需求再修改
    }
    printf("letter_num = %d.", letter_num);

    uint16_t lyrics_0_len = (letter_num / 2);

    curr_obj_0 = lv_lyrics_create(lv_scr_act(), font_file, font_size, 0, letter_buf, lyrics_0_len);
    if (curr_obj_0 == NULL) {
        printf("lv_lyrics_create is fail!!");
        goto example_error0;
    }

    lv_lyrics_set_pos(curr_obj_0, 100, 100);
    lv_lyrics_set_rotation(curr_obj_0, -450, 0, 0);

    curr_obj_1 = lv_lyrics_create(lv_scr_act(), font_file, font_size, 0, letter_buf + lyrics_0_len, (letter_num - lyrics_0_len));
    if (curr_obj_1 == NULL) {
        printf("lv_lyrics_create is fail!!");
        goto example_error1;
    }

    lv_lyrics_set_pos(curr_obj_1, 100, 300);
    lv_lyrics_set_rotation(curr_obj_1, 450, 0, 0);

#if 1
    lv_anim_t lyrics_example2_play_anim0;
    lv_anim_init(&lyrics_example2_play_anim0);  // 初时化动画变量
    lv_anim_set_var(&lyrics_example2_play_anim0, curr_obj_0); //设置动画关联的对象img
    lv_anim_set_exec_cb(&lyrics_example2_play_anim0, lyrics_example2_play_anim_cb); //设置动画执行的回调函数set_angle
    lv_anim_set_values(&lyrics_example2_play_anim0, 128, 256);
    lv_anim_set_time(&lyrics_example2_play_anim0, 3000);
    lv_anim_set_playback_time(&lyrics_example2_play_anim0, 2000);
    lv_anim_set_repeat_count(&lyrics_example2_play_anim0, LV_ANIM_REPEAT_INFINITE);//设置动画重复次数，这里是无穷次
    lv_anim_start(&lyrics_example2_play_anim0); //启动动画播放

    lv_anim_t lyrics_example2_play_anim1;
    lv_anim_init(&lyrics_example2_play_anim1);  // 初时化动画变量
    lv_anim_set_var(&lyrics_example2_play_anim1, curr_obj_1); //设置动画关联的对象img
    lv_anim_set_exec_cb(&lyrics_example2_play_anim1, lyrics_example2_play_anim_cb); //设置动画执行的回调函数set_angle
    lv_anim_set_values(&lyrics_example2_play_anim1, 128, 256);
    lv_anim_set_time(&lyrics_example2_play_anim1, 3000);
    lv_anim_set_playback_time(&lyrics_example2_play_anim1, 2000);
    lv_anim_set_repeat_count(&lyrics_example2_play_anim1, LV_ANIM_REPEAT_INFINITE);//设置动画重复次数，这里是无穷次
    lv_anim_start(&lyrics_example2_play_anim1); //启动动画播放
#endif

    lv_mem_free(letter_buf);
    return;

example_error1:
    lv_lyrics_destructor(curr_obj_0);

example_error0:
    lv_mem_free(letter_buf);
}

static void lyrics_example2_play(void *priv)
{
    int obj_id = 0;

    while (1) {
        lyrics_example2_sem_pend(0);
        printf("[%s] obj_id = %d; text : %s.", __func__, obj_id, lyrics_example2_text[obj_id]);
        if (curr_obj_0 != NULL) {
            lvgl_rpc_post_func(lv_anim_del, 2, curr_obj_0, NULL);
            lvgl_rpc_post_func(lv_lyrics_destructor, 1, curr_obj_0);
        }
        if (curr_obj_1 != NULL) {
            lvgl_rpc_post_func(lv_anim_del, 2, curr_obj_1, NULL);
            lvgl_rpc_post_func(lv_lyrics_destructor, 1, curr_obj_1);
        }

        lvgl_rpc_post_func(lv_example_lyrics_2_letter, 3, lyrics_example2_text[obj_id], 64, CONFIG_FONT_TTF_PATH);

        obj_id++;

        if (obj_id >= 6) {
            obj_id = 0;
        }
    }

    return;
}

static void lyrics_example2_load(void *priv)
{
    while (1) {
        lyrics_example2_sem_post();
        os_time_dly(500);   // 间隔 5s 再开始下一句歌词
    }

    return;
}

void lv_example_lyrics_2(void)
{
    printf("[%s]", __func__);

    os_sem_create(&lyrics_example2_sem, 0);

    thread_fork("lyrics_example2_play", 19, 1024, 0, NULL, lyrics_example2_play, NULL);
    thread_fork("lyrics_example2_load", 19, 1024, 0, NULL, lyrics_example2_load, NULL);    // 5s 间隔加载一句歌词

    return;
}

#endif
