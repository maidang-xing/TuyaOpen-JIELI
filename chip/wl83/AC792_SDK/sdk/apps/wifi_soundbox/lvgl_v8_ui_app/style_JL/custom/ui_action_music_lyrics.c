#include "custom.h"
#include "lvgl.h"
#include "gui_guider.h"

#if !LV_USE_GUIBUILDER_SIMULATOR
#include "app_core.h"
#include "app_config.h"
#include "ui.h"
#include "fs/fs.h"
#include "./lyrics_anim_effect.h"
#include "../../lv_examples.h"

#if LV_USE_LYRICS

#include "os/os_api.h"
#include "lvgl.h"

#define CONFIG_UI_RES_PATH CONFIG_ROOT_PATH // SD 路径


#define LYRICS_LETTER_NUM_MAX 256
#define LYRICS_LINE_MAX_CHARS SCREEN_WIDTH / 48      // 单行最大字符数
#define SCREEN_WIDTH 800              // 屏幕宽度
#define LYRIC_LINE_HEIGHT 50          // 行高
#define LYRIC_START_Y 147             // 歌词起始Y坐标

static char lyrics_example_text[LYRICS_LETTER_NUM_MAX] = "  ";

static lv_obj_t *curr_obj_0;

static lv_obj_t *curr_obj_1;

static char *test_text = "龘12345bjg";

static int lyrics_path_init_flag = 0;
// 字符宽度系数（根据实际字体调整）
#define CHAR_WIDTH_CHINESE 1.0f     // 汉字宽度系数
#define CHAR_WIDTH_ENGLISH 0.5f     // 英文字母宽度系数
#define CHAR_WIDTH_DIGIT 0.55f      // 数字宽度系数
#define CHAR_WIDTH_PUNCT 0.4f       // 标点宽度系数
#define CHAR_SPACING 2              // 字符间距（像素）

// 字符类型枚举
typedef enum {
    CHAR_TYPE_CHINESE,    // 汉字
    CHAR_TYPE_ENGLISH,    // 英文字母
    CHAR_TYPE_DIGIT,      // 数字
    CHAR_TYPE_PUNCT,      // 标点符号
    CHAR_TYPE_OTHER       // 其他字符
} char_type_t;
static void lyrics_example_play_anim_cb(void *obj, int32_t v)
{
    lv_obj_t *lyrics_obj = (lv_obj_t *)obj;
    // 缩放效果
    lv_lyrics_set_zoom(lyrics_obj, v, v);

    lv_lyrics_fontimg_redarw(lyrics_obj);
}

// 判断字符类型
static char_type_t get_char_type(uint32_t unicode_char)
{
    // 1. 汉字判断
    if ((unicode_char >= 0x4E00 && unicode_char <= 0x9FFF) ||     // 常用汉字
        (unicode_char >= 0x3400 && unicode_char <= 0x4DBF) ||     // 扩展A区
        (unicode_char >= 0x20000 && unicode_char <= 0x2A6DF)) {   // 扩展B区
        return CHAR_TYPE_CHINESE;
    }

    // 2. 英文字母判断
    if ((unicode_char >= 'a' && unicode_char <= 'z') ||
        (unicode_char >= 'A' && unicode_char <= 'Z')) {
        return CHAR_TYPE_ENGLISH;
    }

    // 3. 数字判断
    if (unicode_char >= '0' && unicode_char <= '9') {
        return CHAR_TYPE_DIGIT;
    }

    // 4. 常见标点符号判断
    if (unicode_char == ' ' || unicode_char == ',' || unicode_char == '.' ||
        unicode_char == ';' || unicode_char == ':' || unicode_char == '!' ||
        unicode_char == '?' || unicode_char == '\'' || unicode_char == '"' ||
        unicode_char == '(' || unicode_char == ')' || unicode_char == '[' ||
        unicode_char == ']' || unicode_char == '{' || unicode_char == '}' ||
        unicode_char == '<' || unicode_char == '>' || unicode_char == '/' ||
        unicode_char == '\\' || unicode_char == '|' || unicode_char == '-' ||
        unicode_char == '_' || unicode_char == '=' || unicode_char == '+' ||
        unicode_char == '*' || unicode_char == '&' || unicode_char == '^' ||
        unicode_char == '%' || unicode_char == '$' || unicode_char == '#' ||
        unicode_char == '@' || unicode_char == '~' || unicode_char == '`' ||
        unicode_char == 0x3001 || unicode_char == 0x3002 ||  // 中文逗号、句号
        unicode_char == 0xFF0C || unicode_char == 0x3000) {  // 全角逗号、空格
        return CHAR_TYPE_PUNCT;
    }

    return CHAR_TYPE_OTHER;
}

// 根据字符类型获取宽度系数
static float get_char_width_coefficient(char_type_t type)
{
    switch (type) {
    case CHAR_TYPE_CHINESE:
        return CHAR_WIDTH_CHINESE;
    case CHAR_TYPE_ENGLISH:
        return CHAR_WIDTH_ENGLISH;
    case CHAR_TYPE_DIGIT:
        return CHAR_WIDTH_DIGIT;
    case CHAR_TYPE_PUNCT:
        return CHAR_WIDTH_PUNCT;
    case CHAR_TYPE_OTHER:
        return 0.8f;  // 默认系数
    default:
        return 0.8f;
    }
}

// 精确计算文本宽度
lv_coord_t calculate_exact_width(const uint32_t *letters, uint16_t count, uint16_t font_size)
{
    if (!letters || count == 0) {
        return 0;
    }

    lv_coord_t total_width = 0;

    for (uint16_t i = 0; i < count; i++) {
        // 获取字符类型和宽度系数
        char_type_t type = get_char_type(letters[i]);
        float coefficient = get_char_width_coefficient(type);

        // 计算字符宽度
        lv_coord_t char_width = (lv_coord_t)(font_size * coefficient);
        total_width += char_width;

        // 添加字符间距（最后一个字符不加）
        if (i < count - 1) {
            total_width += CHAR_SPACING;
        }
    }

    return total_width;
}

// 智能文本分割
static uint16_t find_optimal_split_point(const uint32_t *letters, uint16_t count, uint16_t font_size)
{
    if (count <= LYRICS_LINE_MAX_CHARS) {
        return count;
    }

    uint16_t best_split = LYRICS_LINE_MAX_CHARS;
    int best_score = -1000;  // 评分初始值

    // 在允许的范围内寻找最佳分割点
    uint16_t search_start = (count > LYRICS_LINE_MAX_CHARS + 5) ?
                            LYRICS_LINE_MAX_CHARS - 3 : 0;
    uint16_t search_end = (count < 2 * LYRICS_LINE_MAX_CHARS) ?
                          count : LYRICS_LINE_MAX_CHARS + 8;

    // 确保搜索范围有效
    if (search_end > count) {
        search_end = count;
    }

    for (uint16_t i = search_start; i < search_end; i++) {
        if (i == 0) {
            continue;    // 不能在第一字符前分割
        }

        int score = 0;

        // 1. 检查当前位置是否适合分割
        uint32_t current_char = letters[i];
        uint32_t prev_char = (i > 0) ? letters[i - 1] : 0;

        // 2. 加分项：在标点处分割
        if (current_char == ' ' || current_char == ',' || current_char == '.' ||
            current_char == ';' || current_char == '!' || current_char == '?' ||
            current_char == 0x3001 || current_char == 0x3002 ||
            current_char == 0xFF0C || current_char == 0x3000) {
            score += 50;  // 标点处分割加高分
        }

        // 3. 加分项：避免在词语中间分割
        // 检查前一个字符是否是标点，是则适合分割
        char_type_t prev_type = get_char_type(prev_char);
        if (prev_type == CHAR_TYPE_PUNCT) {
            score += 30;
        }

        // 4. 考虑两行宽度平衡（加分项）
        uint16_t line1_count = i;
        uint16_t line2_count = count - i;

        // 计算两行宽度
        lv_coord_t line1_width = calculate_exact_width(letters, line1_count, font_size);
        lv_coord_t line2_width = calculate_exact_width(letters + i, line2_count, font_size);

        // 宽度差异越小，评分越高
        lv_coord_t width_diff = abs(line1_width - line2_width);
        score -= width_diff / 5;  // 宽度差异每5像素扣1分

        // 5. 字符数量平衡（加分项）
        int count_diff = abs(line1_count - line2_count);
        score -= count_diff * 2;  // 字符数差异每1个扣2分

        // 6. 确保分割点不是英文字母中间（检查是否在英文单词中间）
        if (i > 0 && i < count - 1) {
            char_type_t prev_type = get_char_type(prev_char);
            char_type_t next_type = get_char_type(letters[i + 1]);

            // 如果前后都是英文字母，说明在单词中间
            if (prev_type == CHAR_TYPE_ENGLISH && next_type == CHAR_TYPE_ENGLISH) {
                score -= 100;  // 严重扣分，避免在单词中间分割
            }
        }

        // 更新最佳分割点
        if (score > best_score) {
            best_score = score;
            best_split = i;
        }
    }

    // 确保分割点有效
    if (best_split == 0 || best_split >= count) {
        best_split = count / 2;
    }

    return best_split;
}

// 解析UTF-8文本为Unicode数组
uint32_t *parse_unicode_text(const char *text, uint16_t *char_count)
{
    if (!text) {
        *char_count = 0;
        return NULL;
    }

    size_t text_len = strlen(text);
    uint32_t *letter_buf = (uint32_t *)lv_mem_alloc(sizeof(uint32_t) * text_len);

    if (!letter_buf) {
        *char_count = 0;
        return NULL;
    }

    uint16_t count = 0;
    int ofs = 0;

    while (ofs < text_len && count < text_len) {
        uint32_t letter;
        uint32_t letter_next;
        _lv_txt_encoded_letter_next_2(text, &letter, &letter_next, &ofs);
        letter_buf[count++] = letter;

        if (count >= LYRICS_LETTER_NUM_MAX) {
            printf("Warning: Text exceeds maximum character limit\n");
            break;
        }
    }

    *char_count = count;
    return letter_buf;
}
static void lyrics_0_delete_event_cb(lv_event_t *e)
{
    if (lv_event_get_code(e) == LV_EVENT_DELETE) {
        lv_anim_del(curr_obj_0, NULL);
        curr_obj_0 = NULL;
        printf("[lyrics 0] Object deleted\n");
    }
}
static void lyrics_1_delete_event_cb(lv_event_t *e)
{
    if (lv_event_get_code(e) == LV_EVENT_DELETE) {
        lv_anim_del(curr_obj_1, NULL);
        curr_obj_1 = NULL;
        printf("[lyrics 1] Object deleted\n");
    }
}

// 修改清理函数
void lyrics_example_clean(void)
{
    // 清理特效动画
    lyrics_anim_effect_cleanup();

    if (curr_obj_0 != NULL) {
        // 先停止动画
        lv_anim_del(curr_obj_0, NULL);
        // 然后销毁对象
        lv_lyrics_destructor(curr_obj_0);
        curr_obj_0 = NULL;
    }

    if (curr_obj_1 != NULL) {
        lv_anim_del(curr_obj_1, NULL);
        lv_lyrics_destructor(curr_obj_1);
        curr_obj_1 = NULL;
    }
}

// 修改创建歌词的函数
lv_obj_t *create_lyrics_line(lv_obj_t *parent, const char *font_file,
                             uint16_t font_size, uint32_t *letter_buf,
                             uint16_t letter_count, lv_coord_t x, lv_coord_t y)
{
    if (!letter_buf || letter_count == 0) {
        printf("[ERROR] create_lyrics_line: invalid parameters\n");
        return NULL;
    }

    lv_obj_t *lyrics_obj = lv_lyrics_create(parent, font_file, font_size, 0,
                                            letter_buf, letter_count);

    if (lyrics_obj == NULL) {
        printf("[ERROR] Failed to create lyrics object\n");
        lv_lyrics_destructor(lyrics_obj);
        return NULL;
    }

    // 设置样式
    lv_obj_set_style_bg_opa(lyrics_obj, LV_OPA_TRANSP, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_clear_flag(lyrics_obj, LV_OBJ_FLAG_CLICKABLE);

    // 设置颜色
    jlvg_color_t color = {0xff, 0xff, 0xff, 0xff};
    lv_lyrics_set_color(lyrics_obj, color);

    // 设置位置
    lv_lyrics_set_pos(lyrics_obj, x, y);

    return lyrics_obj;
}

static void lv_example_lyrics_letter(lv_obj_t *dest_scr, const char *text,
                                     uint16_t font_size, const char *font_file)
{
    lyrics_example_clean();

    if (!text || strlen(text) == 0) {
        printf("Empty text provided\n");
        return;
    }

    // 解析文本
    uint16_t char_count = 0;
    uint32_t *letter_buf = parse_unicode_text(text, &char_count);

    if (!letter_buf || char_count == 0) {
        printf("Failed to parse text\n");
        return;
    }

    lv_coord_t y_position = LYRIC_START_Y;

    // 根据字符数量决定显示方式
    if (char_count <= LYRICS_LINE_MAX_CHARS) {
        // 单行显示
        // 计算居中位置
        lv_coord_t line_width = calculate_exact_width(letter_buf, char_count, font_size);
        lv_coord_t center_x = (SCREEN_WIDTH - line_width) / 2;

        if (center_x < 10) {
            center_x = 10;
        }

        // 创建歌词对象
        curr_obj_0 = create_lyrics_line(dest_scr, font_file, font_size,
                                        letter_buf, char_count,
                                        center_x, y_position);
        lv_obj_add_event_cb(curr_obj_0, lyrics_0_delete_event_cb, LV_EVENT_DELETE, NULL);
        if (curr_obj_0) {
            lyrics_anim_effect_args_t effect_args;
            effect_args.delay = 0;
            effect_args.duration = 1000;
            effect_args.target_x = center_x;  // 传入目标位置
            effect_args.target_y = y_position;
            lyrics_anim_effect_zooming_in_down(curr_obj_0, &effect_args);
        }

    } else {
        // 两行显示
        // 寻找分割点
        uint16_t split_pos = find_optimal_split_point(letter_buf, char_count, font_size);

        // 第一行
        uint16_t line1_count = split_pos;
        lv_coord_t line1_width = calculate_exact_width(letter_buf, line1_count, font_size);
        lv_coord_t line1_center_x = (SCREEN_WIDTH - line1_width) / 2;

        if (line1_center_x < 10) {
            line1_center_x = 10;
        }

        curr_obj_0 = create_lyrics_line(dest_scr, font_file, font_size,
                                        letter_buf, line1_count,
                                        line1_center_x, y_position);
        lv_obj_add_event_cb(curr_obj_0, lyrics_0_delete_event_cb, LV_EVENT_DELETE, NULL);
        if (curr_obj_0) {
            lyrics_anim_effect_args_t effect_args1;
            effect_args1.delay = 0;
            effect_args1.duration = 800;
            effect_args1.target_x = line1_center_x;  // 传入第一行目标位置
            effect_args1.target_y = y_position;  // 注意：这是第一行的Y坐标
            lyrics_anim_effect_zooming_in_down(curr_obj_0, &effect_args1);
        }
        // 第二行
        y_position += LYRIC_LINE_HEIGHT;
        uint16_t line2_count = char_count - split_pos;
        lv_coord_t line2_width = calculate_exact_width(letter_buf + split_pos, line2_count, font_size);
        lv_coord_t line2_center_x = (SCREEN_WIDTH - line2_width) / 2;

        if (line2_center_x < 10) {
            line2_center_x = 10;
        }

        curr_obj_1 = create_lyrics_line(dest_scr, font_file, font_size,
                                        letter_buf + split_pos, line2_count,
                                        line2_center_x, y_position);
        lv_obj_add_event_cb(curr_obj_1, lyrics_1_delete_event_cb, LV_EVENT_DELETE, NULL);
        // 使用特效动画

        if (curr_obj_1) {
            lyrics_anim_effect_args_t effect_args2;
            effect_args2.delay = 200;
            effect_args2.duration = 800;
            effect_args2.target_x = line2_center_x;  // 传入第二行目标位置
            effect_args2.target_y = y_position;  // 这是第二行的Y坐标
            lyrics_anim_effect_zooming_in_down(curr_obj_1, &effect_args2);
        }
    }

    lv_mem_free(letter_buf);

    if (!curr_obj_0 && !curr_obj_1) {
        printf("Failed to create any lyrics objects\n");
    }
}

//更新歌词
void lv_example_lyrics_text_input(char *new_text)
{

    if (!lyrics_path_init_flag) {
        FILE *fd = fopen(CONFIG_FONT_TTF_PATH, "r");
        if (fd) {
            fclose(fd);
            lyrics_path_init_flag = 1;
        } else {
            printf("Open font fft path error 30100000.ttf  or no exit font fft resource 30100000.ttf !!!!!\n");
            return;
        }
    }

    size_t text_len = strlen(new_text);
    if (text_len > LYRICS_LETTER_NUM_MAX) {

        printf("error: new_text is too len. len = %d.", text_len);

        return;

    }
    printf("[%s] new lyrics is [%s]", __func__, new_text);
    memcpy(lyrics_example_text, new_text, text_len);
    lyrics_example_text[text_len] = '\0';
    free(new_text);
    lv_ui_music_player *ui_scr = ui_get_scr_ptr(&guider_ui, GUI_SCREEN_MUSIC_PLAYER);
    if (!ui_scr) {
        return;
    }
    lv_example_lyrics_letter(ui_scr->music_player_view_lyrics, lyrics_example_text, 48, CONFIG_FONT_TTF_PATH);
}
#endif //LV_USE_LYRICS
#endif
