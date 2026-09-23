#include "custom.h"
#if !LV_USE_GUIBUILDER_SIMULATOR
#include "app_core.h"
#include "app_config.h"
#include "ui.h"
#include "fs/fs.h"


#if LV_USE_LYRICS
#include "lvgl_v8/src/extra/jl_extra/widgets/lyrics/lv_lyrics.h"
#include "asm/gpu/jlvg.h"

#define SONG_INFO_FONT_SIZE 32
#define SYS_SONG_INFO_FONT_SIZE 24
#define SONG_NAME_Y_POS 394
#define SONG_ARTIST_Y_POS 433
#define SONG_INFO_X_POS 15

#define SYS_SONG_INFO_X_POS 0
#define SYS_SONG_INFO_Y_POS 17


#define SONG_INFO_LETTER_MAX 64

#define lv_max(a, b) ((a) > (b) ? (a) : (b))

static lv_obj_t *song_name_lyrics_obj = NULL;
static lv_obj_t *song_artist_lyrics_obj = NULL;
static lv_obj_t *sys_menu_song_info_lyrics_obj = NULL;
static int lyrics_path_init_flag = 0;


static char song_name_text[SONG_INFO_LETTER_MAX] = "  ";
static char song_artist_text[SONG_INFO_LETTER_MAX] = "  ";
static char song_info_text[SONG_INFO_LETTER_MAX] = "  ";

static int song_info_lyrics_is_available(void)
{
    if (!lyrics_path_init_flag) {
        FILE *fd = fopen(CONFIG_FONT_TTF_PATH, "r");
        if (fd) {
            fclose(fd);
            lyrics_path_init_flag = 1;
        } else {
            printf("Open font fft path error 30100000.ttf  or no exit font fft resource 30100000.ttf !!!!!\n");
        }
    }
    return lyrics_path_init_flag;
}

static void song_name_lyrics_delete_event_cb(lv_event_t *e)
{
    if (lv_event_get_code(e) == LV_EVENT_DELETE) {
        lv_anim_del(song_name_lyrics_obj, NULL);
        song_name_lyrics_obj = NULL;
    }
}

static void song_artist_lyrics_delete_event_cb(lv_event_t *e)
{
    if (lv_event_get_code(e) == LV_EVENT_DELETE) {
        lv_anim_del(song_artist_lyrics_obj, NULL);
        song_artist_lyrics_obj = NULL;
    }
}

static void sys_menu_song_info_lyrics_delete_event_cb(lv_event_t *e)
{
    if (lv_event_get_code(e) == LV_EVENT_DELETE) {

        lv_anim_del(sys_menu_song_info_lyrics_obj, NULL);

        sys_menu_song_info_lyrics_obj = NULL;
    }
}

static void sys_menu_song_info_scroll_cb(void *var, int32_t x)
{
    lv_obj_t *lyrics_obj = (lv_obj_t *)var;
    if (!lyrics_obj) {
        return;
    }
    lv_coord_t current_y = lv_obj_get_y(lyrics_obj);
    lv_lyrics_set_pos(lyrics_obj, x, current_y);
}

static lv_obj_t *create_song_info_lyrics_line(lv_obj_t *parent, const char *font_file,
        uint16_t font_size, const char *text,
        lv_coord_t x, lv_coord_t y)
{
    size_t text_len = strlen(text);
    uint32_t *letter_buf = (uint32_t *)lv_mem_alloc(sizeof(uint32_t) * text_len);
    if (!letter_buf) {
        printf("[song_info_line] Failed to allocate letter buffer\n");
        return NULL;
    }

    uint16_t letter_count = 0;
    uint32_t ofs = 0;
    while (ofs < text_len && letter_count < text_len) {
        uint32_t letter;
        uint32_t letter_next;
        _lv_txt_encoded_letter_next_2(text, &letter, &letter_next, &ofs);

        if (letter == 0) {
            continue;
        }
        letter_buf[letter_count++] = letter;

        if (letter_count >= SONG_INFO_LETTER_MAX) {
            printf("[song_info_line] Text exceeds max limit\n");
            break;
        }
    }

    if (letter_count == 0) {
        printf("[song_info_line] No valid letters\n");
        lv_mem_free(letter_buf);
        return NULL;
    }

    printf("[song_info_line] Creating lyrics with %d letters\n", letter_count);

    lv_obj_t *lyrics_obj = create_lyrics_line(parent, font_file, font_size, letter_buf, letter_count, x, y);

    lv_mem_free(letter_buf);

    if (!lyrics_obj) {
        printf("[song_info_line] Failed to create lyrics object\n");
        return NULL;
    }

    lv_lyrics_fontimg_redarw(lyrics_obj);

    return lyrics_obj;
}

void music_player_song_info_lyrics_clean(void)
{
    if (song_name_lyrics_obj != NULL) {
        lv_anim_del(song_name_lyrics_obj, NULL);
        lv_lyrics_destructor(song_name_lyrics_obj);
        song_name_lyrics_obj = NULL;
    }
    if (song_artist_lyrics_obj != NULL) {
        lv_anim_del(song_artist_lyrics_obj, NULL);
        lv_lyrics_destructor(song_artist_lyrics_obj);
        song_artist_lyrics_obj = NULL;
    }
}

void sys_menu_song_info_lyrics_clean(void)
{
    if (sys_menu_song_info_lyrics_obj != NULL) {
        lv_anim_del(sys_menu_song_info_lyrics_obj, NULL);
        lv_lyrics_destructor(sys_menu_song_info_lyrics_obj);
        sys_menu_song_info_lyrics_obj = NULL;
    }
}

void music_player_song_name_update(lv_obj_t *dest_scr, const char *text,
                                   lv_coord_t x, lv_coord_t y)
{
    if (!text || strlen(text) == 0) {
        printf("[song_name] Empty text\n");
        return;
    }

    printf("[song_name] Creating lyrics for: %s\n", text);
    song_name_lyrics_obj = create_song_info_lyrics_line(dest_scr, CONFIG_FONT_TTF_PATH,
                           SONG_INFO_FONT_SIZE, text,
                           x, y);//SONG_INFO_X_POS, SONG_NAME_Y_POS);
    if (song_name_lyrics_obj) {
        lv_obj_add_event_cb(song_name_lyrics_obj, song_name_lyrics_delete_event_cb,
                            LV_EVENT_DELETE, NULL);
    }
}

void music_player_song_artist_update(lv_obj_t *dest_scr, const char *text,
                                     lv_coord_t x, lv_coord_t y)
{
    if (!text || strlen(text) == 0) {
        printf("[song_artist] Empty text\n");
        return;
    }

    printf("[song_artist] Creating lyrics for: %s\n", text);
    song_artist_lyrics_obj = create_song_info_lyrics_line(dest_scr, CONFIG_FONT_TTF_PATH,
                             SONG_INFO_FONT_SIZE, text,
                             x, y);//SONG_INFO_X_POS, SONG_ARTIST_Y_POS);
    if (song_artist_lyrics_obj) {
        lv_obj_add_event_cb(song_artist_lyrics_obj, song_artist_lyrics_delete_event_cb,
                            LV_EVENT_DELETE, NULL);
    }
}

void sys_menu_song_info_update(char *song_info)
{
    lv_ui_sys_menu *ui_scr = ui_get_scr_ptr(&guider_ui, GUI_SCREEN_SYS_MENU);
    if (!ui_scr || ui_scr->sys_menu_del) {
        return;
    }

    size_t song_info_len = strlen(song_info);
    if (!song_info || song_info_len == 0) {
        printf("[song info] Empty text\n");
        return;
    }
    if (song_info_len > SONG_INFO_LETTER_MAX) {
        printf("error: new_text is too len. len = %d.", song_info_len);
        return;
    }
    if (!song_info_lyrics_is_available()) {
        if (song_info != NULL) {
            free(song_info);
        }
        return;

    }
    memcpy(song_info_text, song_info, song_info_len);
    song_info_text[song_info_len] = '\0';
    free(song_info);
    // 先销毁旧对象及动画
    sys_menu_song_info_lyrics_clean();

    lv_obj_t *parent = ui_scr->sys_menu_view_song_info;
    sys_menu_song_info_lyrics_obj = create_song_info_lyrics_line(
                                        parent, CONFIG_FONT_TTF_PATH, SYS_SONG_INFO_FONT_SIZE, song_info_text,
                                        SYS_SONG_INFO_X_POS, SYS_SONG_INFO_Y_POS);

    if (!sys_menu_song_info_lyrics_obj) {
        return;
    }

    jlvg_color_t color = {0x00, 0x00, 0x00, 0xff};
    lv_lyrics_set_color(sys_menu_song_info_lyrics_obj, color);

    // ---------- 计算文本实际宽度 ----------
    uint16_t char_count = 0;
    uint32_t *letter_buf = parse_unicode_text(song_info_text, &char_count);
    if (letter_buf && char_count > 0) {
        lv_coord_t text_width = calculate_exact_width(letter_buf, char_count, SYS_SONG_INFO_FONT_SIZE);
        lv_mem_free(letter_buf);

        lv_coord_t parent_width = lv_obj_get_width(parent);
        // 可适当增加内边距，不紧贴边缘
        const lv_coord_t margin = 20;
        lv_coord_t available_width = parent_width - margin;

        if (text_width > available_width) {
            // ----- 需要滚动 -----
            // 设置初始位置：从父控件右侧开始（右边缘对齐）
            lv_coord_t start_x = parent_width;
            lv_coord_t end_x = -text_width;   // 向左完全移出
            lv_coord_t anim_time = (text_width + parent_width) * 50 / 10; // 速度系数，可调
            if (anim_time < 1000) {
                anim_time = 1000;
            }
            if (anim_time > 10000) {
                anim_time = 10000;
            }

            lv_lyrics_set_pos(sys_menu_song_info_lyrics_obj, start_x, 15);

            // 创建动画
            lv_anim_t anim;
            lv_anim_init(&anim);
            lv_anim_set_var(&anim, sys_menu_song_info_lyrics_obj);
            lv_anim_set_exec_cb(&anim, sys_menu_song_info_scroll_cb);
            lv_anim_set_values(&anim, start_x, end_x);
            lv_anim_set_time(&anim, anim_time);
            lv_anim_set_repeat_count(&anim, LV_ANIM_REPEAT_INFINITE);
            lv_anim_set_path_cb(&anim, lv_anim_path_linear);
            lv_anim_start(&anim);
        } else {
            // 不滚动，居中或左对齐
            lv_coord_t x_pos = (parent_width - text_width) / 2;
            if (x_pos < 0) {
                x_pos = 0;
            }
            lv_lyrics_set_pos(sys_menu_song_info_lyrics_obj, x_pos, 15);
        }
    } else {
        // 无法解析文本时，简单左对齐
        lv_lyrics_set_pos(sys_menu_song_info_lyrics_obj, 0, 15);
    }

    lv_lyrics_fontimg_redarw(sys_menu_song_info_lyrics_obj);
    lv_obj_add_event_cb(sys_menu_song_info_lyrics_obj, sys_menu_song_info_lyrics_delete_event_cb,
                        LV_EVENT_DELETE, NULL);
}

void music_player_song_info_update(char *song_name, char *song_artist)
{
    lv_ui_music_player *ui_scr = ui_get_scr_ptr(&guider_ui, GUI_SCREEN_MUSIC_PLAYER);
    if (!ui_scr || ui_scr->music_player_del || !song_info_lyrics_is_available()) {
        goto __exit;
    }

    music_player_song_info_lyrics_clean();
    size_t song_name_len = strlen(song_name);
    size_t song_artist_len = strlen(song_artist);
    if (!song_name || !song_artist || song_name_len == 0 || song_artist_len == 0) {
        printf("[song info] Empty text\n");
        goto __exit;
    }
    if (song_name_len > SONG_INFO_LETTER_MAX || song_artist_len > SONG_INFO_LETTER_MAX) {
        printf("error: new_text is too len. len = %d.", lv_max(song_name_len, song_artist_len));
        goto __exit;
    }
    printf("song_info:%s %s\n", song_name, song_artist);
    memcpy(song_name_text, song_name, song_name_len);
    memcpy(song_artist_text, song_artist, song_artist_len);
    song_name_text[song_name_len] = '\0';
    song_artist_text[song_artist_len] = '\0';
    lv_obj_t *dest_scr = NULL;
    dest_scr = ui_scr->music_player;
    music_player_song_name_update(dest_scr, song_name_text, SONG_INFO_X_POS, SONG_NAME_Y_POS);
    music_player_song_artist_update(dest_scr, song_artist_text, SONG_INFO_X_POS, SONG_ARTIST_Y_POS);
__exit:
    free(song_name);
    free(song_artist);
}

#else // !LV_USE_LYRICS

// 非 LV_USE_LYRICS 时的空实现
void music_player_song_info_lyrics_clean(void)
{
}

void sys_menu_song_info_lyrics_clean(void)
{
}

void sys_menu_song_info_update(char *song_info)
{

    if (song_info != NULL) {
        free(song_info);
    }
}

void music_player_song_info_update(char *song_name, char *song_artist)
{
    if (song_name != NULL) {
        free(song_name);
    }
    if (song_artist != NULL) {
        free(song_artist);
    }
}
#endif // LV_USE_LYRICS

#endif // !LV_USE_GUIBUILDER_SIMULATOR
