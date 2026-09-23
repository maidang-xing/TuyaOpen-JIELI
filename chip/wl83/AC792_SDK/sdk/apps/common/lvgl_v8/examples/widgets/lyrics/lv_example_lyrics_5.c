/*
 * @file lv_example_lyrics_5.c
 *
 * 演示了如何调用 lv_lyrics 控件和label控件实现简单的弹幕 demo
 */
/*使用时请打开lv_conf.h里的LV_USE_FREETYPE!!!!!!!!!!!!!!*/
/*若使用label控件可以加大LV_FREETYPE_CACHE_SIZE和LV_FREETYPE_CACHE_FT_FACES和LV_FREETYPE_CACHE_FT_SIZES提高性能*/
/*使用800*480屏幕 芯片AC7926A测试下的帧率*/
/*歌词控件平均帧率40fps*/
/*label控件平均帧率25fps*/
#include "../../lv_examples.h"
#if LV_USE_LYRICS && LV_BUILD_EXAMPLES
#include "os/os_api.h"
#include "lvgl.h"
#include "../../../common/lvgl_v8/src/extra/libs/freetype/lv_freetype.h"
#define CONFIG_UI_RES_PATH CONFIG_ROOT_PATH // SD 路径
#define CONFIG_FONT_TTF_PATH "storage/sd0/C/OPPO.ttf"
#define LYRICS_LETTER_NUM_MAX 256
#define DIY_TEXT_NUM_MAX 256
#define NUM_LYRICS_OBJS 15
#define SAMESENTENCE 0         //相同弹幕开关(0为不同弹幕，1为相同弹幕)
#define USE_LABEL_SENTENCE 0   //使用LABEL控件开关
float step = 0;
float floatcount =  0 ;
int mytime = 6500;           //运行时间
float time_interval = 1600.0;//开始到结束的像素间隔（必须全部一致）
int keycfl = 0;
int offset =  0;
lv_anim_t anims[NUM_LYRICS_OBJS];
static char lyrics_example5_text[LYRICS_LETTER_NUM_MAX] = "杰理科技JL";
static lv_obj_t *curr_obj[NUM_LYRICS_OBJS] = {0};
static lv_obj_t *curr_obj_user_data[NUM_LYRICS_OBJS];
static lv_obj_t *label[NUM_LYRICS_OBJS] = {0};
jlvg_color_t DIY_Font_color;

// 歌词对象配置结构体
typedef struct {
    int font_size;
    int x;
    int y;
    uint8_t r;
    uint8_t g;
    uint8_t b;
    int anim_start;
    int anim_end;
} lyrics_obj_config_t;

static const lyrics_obj_config_t obj_configs[NUM_LYRICS_OBJS] = {
    {48, 0,   0, 0x00, 0x00, 0x00, 800, -800}, // obj 0
    {48, 400, 0, 0x5C, 0x5C, 0x5C, 1200, -400}, // obj 1
    {32, 0,   50, 0x00, 0x00, 0x00, 800, -800}, // obj 2
    {32, 264, 50, 0x5C, 0x5C, 0x5C, 1064, -532}, // obj 3
    {32, 528, 50, 0x00, 0x00, 0x00, 1328, -264}, // obj 4
    {48, 0,   100, 0x5C, 0x5C, 0x5C, 800, -800}, // obj 5
    {48, 400, 100, 0x00, 0x00, 0x00, 1200, -400}, // obj 6
    {64, 0,   180, 0x00, 0x00, 0x00, 800, -800}, // obj 7
    {24, 600, 183, 0x5C, 0x5C, 0x5C, 1400, -200}, // obj 8
    {24, 600, 213, 0x5C, 0x5C, 0x5C, 1400, -200}, // obj 9
    {32, 0,   300, 0x00, 0x00, 0x00, 1064, -532}, // obj10
    {32, 266, 300, 0x5C, 0x5C, 0x5C, 800, -800}, // obj11
    {32, 532, 300, 0x00, 0x00, 0x00, 1328, -264}, // obj12
    {48, 0,   380, 0x5C, 0x5C, 0x5C, 800, -800}, // obj13
    {48, 400, 380, 0x00, 0x00, 0x00, 1200, -400} // obj14
};

#if !SAMESENTENCE
//句子UTF-8
static const char *lyric_texts[NUM_LYRICS_OBJS] = {
    // 1. "这辈子有了"
    "\xe8\xbf\x99\xe8\xbe\x88\xe5\xad\x90\xe6\x9c\x89\xe4\xba\x86",
    // 2. "还得是你啊！"
    "\xe8\xbf\x98\xe5\xbe\x97\xe6\x98\xaf\xe4\xbd\xa0\xe5\x95\x8a\xef\xbc\x81",
    // 3. "我应在江湖悠悠"
    "\xe6\x88\x91\xe5\xba\x94\xe5\x9c\xa8\xe6\xb1\x9f\xe6\xb9\x96\xe6\x82\xa0\xe6\x82\xa0",
    // 4. "善待三旬老人"
    "\xe5\x96\x84\xe5\xbe\x85\xe4\xb8\x89\xe6\x97\xac\xe8\x80\x81\xe4\xba\xba",
    // 5. "你人还怪好的嘞！"
    "\xe4\xbd\xa0\xe4\xba\xba\xe8\xbf\x98\xe6\x80\xaa\xe5\xa5\xbd\xe7\x9a\x84\xe5\x98\x9e\xef\xbc\x81",
    // 6. "快乐才会有好运"
    "\xe5\xbf\xab\xe4\xb9\x90\xe6\x89\x8d\xe4\xbc\x9a\xe6\x9c\x89\xe5\xa5\xbd\xe8\xbf\x90",
    // 7. "被自己穷笑了"
    "\xe8\xa2\xab\xe8\x87\xaa\xe5\xb7\xb1\xe7\xa9\xb7\xe7\xac\x91\xe4\xba\x86",
    // 8. "嘻嘻、不嘻嘻！"
    "\xe5\x98\xbb\xe5\x98\xbb\xe3\x80\x81\xe4\xb8\x8d\xe5\x98\xbb\xe5\x98\xbb\xef\xbc\x81",
    // 9. "233333333333333" (ASCII无需转换)
    "233333333333333",
    // 10. "显眼包来啦！"
    "\xe6\x98\xbe\xe7\x9c\xbc\xe5\x8c\x85\xe6\x9d\xa5\xe5\x95\xa6\xef\xbc\x81",
    // 11. "NBNBNBNB" (ASCII无需转换)
    "NBNBNBNB",
    // 12. "你是我的犬系朋友"
    "\xe4\xbd\xa0\xe6\x98\xaf\xe6\x88\x91\xe7\x9a\x84\xe7\x8a\xac\xe7\xb3\xbb\xe6\x9c\x8b\xe5\x8f\x8b",
    // 13. "嘿嘿其实我也不知道！"
    "\xe5\x98\xbf\xe5\x98\xbf\xe5\x85\xb6\xe5\xae\x9e\xe6\x88\x91\xe4\xb9\x9f\xe4\xb8\x8d\xe7\x9f\xa5\xe9\x81\x93\xef\xbc\x81",
    // 14. "逆天了"
    "\xe9\x80\x86\xe5\xa4\xa9\xe4\xba\x86",
    // 15. "哈基米喔那没路躲"
    "\xe5\x93\x88\xe5\x9f\xba\xe7\xb1\xb3\xe5\x96\x94\xe9\x82\xa3\xe6\xb2\xa1\xe8\xb7\xaf\xe8\xba\xb2"
};
#endif

static void lyrics_example5_play_anim_cb(void *obj, int32_t v)
{
    lv_lyrics_set_x((lv_obj_t *)obj, v);
}

static void label_example5_play_anim_cb(void *obj, int32_t v)
{
    lv_obj_set_x((lv_obj_t *)obj, v);
}
//该路径函数只支持弹幕往左移动，若要往右移动请修改
int32_t my_path_linear(const lv_anim_t *a)
{
    int pos;
    int i = (int)(intptr_t)a->user_data;
    if (step < 1.0) {
        if (i == 0) {
            floatcount += step;
            if (keycfl) {
                keycfl = 0;
                floatcount -= 1;
            }
        }
        if (floatcount > 1.0) {
            //printf("floatcount>1 = %f\n", floatcount);
            if (i == 0) {
                keycfl = 1;
                offset--;
                offset = offset % (int)time_interval;
            }
        }
        pos = a->start_value + offset;
        //printf("floatcount<1 = %f\n", floatcount);
        return pos;
    } else {
        if (i == 0) {
            floatcount -= (float)((int)step + 1) - step;
            if (keycfl) {
                keycfl = 0;
                floatcount += (float)(int)step + 1;
            }
        }
        if (floatcount > -(((float)((int)step + 1)))) {
            //printf("floatcount>-%d = %f\n", (int)step + 1, floatcount);
            if (i == 0) {
                offset -= (int)step + 1;
                offset = offset % (int)time_interval;
            }
            pos = a->start_value + offset;
            return pos;
        }
        if (i == 0) {
            keycfl = 1;
        }
        //printf("floatcount<-%d = %f\n", (int)step + 1,floatcount);
        pos = a->start_value + offset;
        return pos;
    }
}
//只释放内部申请内存
void lyrics_example5_clean(void);

void lv_example_lyrics_5_letter(lv_obj_t *dest_obj, const char *text, const char *font_file)
{
    printf("[chili] %s %d\n", __func__, __LINE__);
    lyrics_example5_clean();
#if !USE_LABEL_SENTENCE
#if SAMESENTENCE
    size_t text_len = strlen(text);
    uint32_t *letter_buf = (uint32_t *)lv_mem_alloc(sizeof(uint32_t) * text_len);

    uint16_t letter_num = 0;
    int ofs = 0;
    while (ofs < text_len) {
        uint32_t letter;
        uint32_t letter_next;
        _lv_txt_encoded_letter_next_2(text, &letter, &letter_next, &ofs);
        letter_buf[letter_num] = letter;
        printf("Input text: %s (len=%d bytes)\n", text, (int)strlen(text));
        printf("First byte: 0x%02X\n", (uint8_t)text[letter_num]);
        letter_num++;
        assert(letter_num < LYRICS_LETTER_NUM_MAX);
    }
#endif
#if !SAMESENTENCE
    uint32_t *letter_buf[NUM_LYRICS_OBJS] = {0};
#endif
    // 创建所有歌词对象
    for (int i = 0; i < NUM_LYRICS_OBJS; i++) {
        const lyrics_obj_config_t *config = &obj_configs[i];
#if SAMESENTENCE
        curr_obj[i] = lv_lyrics_create(dest_obj, font_file, config->font_size, 0, letter_buf, letter_num); //同句字幕
#endif
#if !SAMESENTENCE
        letter_buf[i] = (uint32_t *)lv_mem_alloc(sizeof(uint32_t) * strlen(lyric_texts[i]));
        uint16_t letter_num = 0;
        int ofs = 0;
        while (ofs < strlen(lyric_texts[i])) {
            uint32_t letter;
            uint32_t letter_next;
            _lv_txt_encoded_letter_next_2(lyric_texts[i], &letter, &letter_next, &ofs);
            letter_buf[i][letter_num] = letter;
            letter_num++;
            assert(letter_num < LYRICS_LETTER_NUM_MAX);
        }
        curr_obj[i] = lv_lyrics_create(dest_obj, font_file, config->font_size, 0, letter_buf[i], letter_num); //不同句字幕
#endif
        if (curr_obj[i] == NULL) {
            printf("lv_lyrics_create is fail for obj %d!!", i);
            // 错误处理：释放所有已创建的对象
            for (int j = 0; j < i; j++) {
                lv_lyrics_destructor(curr_obj[j]);
            }
            lv_mem_free(letter_buf);
            return;
        }

        curr_obj_user_data[i] = curr_obj[i]->user_data;
        lv_lyrics_set_pos(curr_obj[i], config->x, config->y);

        DIY_Font_color.r = config->r;
        DIY_Font_color.g = config->g;
        DIY_Font_color.b = config->b;
        lv_lyrics_set_color(curr_obj[i], DIY_Font_color);
    }
#endif
    lv_anim_timeline_t *tl = lv_anim_timeline_create();
#if USE_LABEL_SENTENCE
    lv_freetype_init(64, 1, 0);
#endif
    // 创建所有动画
    for (int i = 0; i < NUM_LYRICS_OBJS; i++) {
        const lyrics_obj_config_t *config = &obj_configs[i];
#if !USE_LABEL_SENTENCE
        printf("!USE_LABEL_SENTENCE\n");
        lv_anim_init(&anims[i]);
        lv_anim_set_var(&anims[i], curr_obj[i]);
        lv_anim_set_exec_cb(&anims[i], lyrics_example5_play_anim_cb);
        lv_anim_set_values(&anims[i], config->anim_start, config->anim_end);
        lv_anim_set_time(&anims[i], mytime);
        lv_anim_set_user_data(&anims[i], (void *)(intptr_t)i);
        lv_anim_set_repeat_count(&anims[i], LV_ANIM_REPEAT_INFINITE);
        lv_anim_set_path_cb(&anims[i], my_path_linear);
        lv_anim_timeline_add(tl, 0, &anims[i]);
#endif

#if USE_LABEL_SENTENCE
        printf("USE_LABEL_SENTENCE\n");
        label[i] = lv_label_create(lv_scr_act());

        lv_ft_info_t ft_info;
        ft_info.name = CONFIG_FONT_TTF_PATH;       // 字体文件路径
        ft_info.weight = config->font_size;      // 字号
        ft_info.style = 0;                       // 普通风格
        ft_info.mem = NULL;                      // 不用内存加载
        ft_info.mem_size = 0;
        if (!lv_ft_font_init(&ft_info)) {
            printf("❌ 字体加载失败\n");
        }
        lv_obj_set_style_text_font(label[i], ft_info.font, 0);
#if SAMESENTENCE
        lv_label_set_text(label[i], lyrics_example5_text);
#endif
#if !SAMESENTENCE
        lv_label_set_text(label[i], lyric_texts[i]);
#endif
        lv_obj_set_x(label[i], config->x);
        lv_obj_set_y(label[i], config->y);
        lv_anim_init(&anims[i]);
        lv_anim_set_var(&anims[i], label[i]);
        lv_anim_set_exec_cb(&anims[i], label_example5_play_anim_cb);
        lv_anim_set_values(&anims[i], config->anim_start, config->anim_end);
        lv_anim_set_time(&anims[i], mytime);
        lv_anim_set_user_data(&anims[i], (void *)(intptr_t)i);
        lv_anim_set_repeat_count(&anims[i], LV_ANIM_REPEAT_INFINITE);
        lv_anim_set_path_cb(&anims[i], my_path_linear);
        lv_anim_timeline_add(tl, 0, &anims[i]);
#endif
    }
    step = time_interval / ((float)mytime / (float)LV_DISP_DEF_REFR_PERIOD);
    printf("step = %f\n", step);
    printf("hello world\n");
    lv_anim_timeline_start(tl);
#if !USE_LABEL_SENTENCE
#if SAMESENTENCE
    lv_mem_free(letter_buf);
#endif
#if !SAMESENTENCE
    for (int i = 0; i < NUM_LYRICS_OBJS; i++) {
        lv_mem_free(letter_buf[i]);
    }
#endif
#endif
}

void lyrics_example5_play(void *priv)
{
    lv_example_lyrics_5_letter(priv, lyrics_example5_text, CONFIG_FONT_TTF_PATH);
}


//因为歌词控件在顶层页面，所以不需要显示歌词的页面隐藏掉歌词控件
void hide_lyrics(int hide)
{
    for (int i = 0; i < NUM_LYRICS_OBJS; i++) {
        if (curr_obj[i]) {
            if (hide) {
                printf("[hide_lyrics1 : 隐藏控件] %s %d\n", __func__, __LINE__);
                lv_obj_add_flag(curr_obj[i], LV_OBJ_FLAG_HIDDEN);
                //lyrics_example5_clean();
            } else {
                printf("[hide_lyrics1 : 显示控件] %s %d\n", __func__, __LINE__);
                lv_obj_clear_flag(curr_obj[i], LV_OBJ_FLAG_HIDDEN);
            }
        }
    }
}


//清空歌词
void lyrics_example5_clean(void)
{
    printf("[chili] %s %d\n", __func__, __LINE__);
    for (int i = 0; i < NUM_LYRICS_OBJS; i++) {
        if (curr_obj[i]) {
            printf("[chili] cleaning line %d\n", i);
            lv_anim_del(curr_obj[i], NULL);
            lv_lyrics_destructor(curr_obj[i]);
            curr_obj[i] = NULL;
        }
    }
}

#if SAMESENTENCE
//更新歌词lyrics_example5_text(相同句)
void lv_example_lyrics_5_text_input(char *new_text, int len)
{
    size_t text_len = strlen(new_text);

    if (text_len > LYRICS_LETTER_NUM_MAX) {
        printf("error: new_text is too len. len = %d.", text_len);
        return;
    }

    printf("[%s] new lyrics is [%s]", __func__, new_text);

    memcpy(lyrics_example5_text, new_text, text_len);
    lyrics_example5_text[text_len] = '\0';

    lyrics_example5_play(lv_layer_top());
}
#endif // SAMESENTENCE

void lv_example_lyrics_5_sentence_show()
{
    lv_example_lyrics_5_letter(lv_layer_top(), lyrics_example5_text, CONFIG_FONT_TTF_PATH);
}

#endif

