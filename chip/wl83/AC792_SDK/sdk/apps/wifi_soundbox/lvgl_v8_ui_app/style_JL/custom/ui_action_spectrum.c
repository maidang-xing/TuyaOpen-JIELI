#include "custom.h"
#include "src/core/lv_disp.h"
#if !LV_USE_GUIBUILDER_SIMULATOR
#include "effects/eq_config.h"
#include "app_core.h"
#include "app_config.h"
#include "ui.h"
#include "fs/fs.h"
#include "math.h"

#define CIRCULAR_SPECTRUM_BAR_CNT    72      // 条形数量
#define CIRCULAR_SPECTRUM_DEG_STEP   (360 / CIRCULAR_SPECTRUM_BAR_CNT)  // 每个条形的角度间隔
#define CIRCULAR_SPECTRUM_INNER_RADIUS 120    // 内圆半径
#define CIRCULAR_SPECTRUM_MAX_RADIUS  170     // 最大半径（对应最大幅度）
#define CIRCULAR_SPECTRUM_MIN_RADIUS  122     // 最小半径

float bar_chart[CIRCULAR_SPECTRUM_BAR_CNT] = {0};
static lv_obj_t *spectrum_obj = NULL;
static float expanded_data[CIRCULAR_SPECTRUM_BAR_CNT] = {0};
rgb_color_t g_spectrum_bg_avg_color = {0x80, 0x80, 0x80}; // 默认灰色
bool g_spectrum_bg_color_initialized = false;


// 设置背景平均颜色
void ui_music_spectrum_set_bg_avg_color(uint8_t r, uint8_t g, uint8_t b)
{
    g_spectrum_bg_avg_color.r = r;
    g_spectrum_bg_avg_color.g = g;
    g_spectrum_bg_avg_color.b = b;
    g_spectrum_bg_color_initialized = true;
}

// 更新条形数据（调整为圆形）
static void bar_value_update_circular(float *mag)
{
    // 使用插值将32点数据扩展到BAR_CNT点
    for (int i = 0; i < CIRCULAR_SPECTRUM_BAR_CNT; i++) {
        float position = (float)i * (64 - 1) / (CIRCULAR_SPECTRUM_BAR_CNT - 1);
        int index1 = (int)position;
        int index2 = index1 + 1;
        if (index2 >= 64) {
            index2 = 63;
        }

        float fraction = position - index1;

        // 线性插值
        float value = mag[index1] * (1.0f - fraction) + mag[index2] * fraction;

        // 转换为半径长度（0-100映射到MIN_RADIUS-MAX_RADIUS）
        bar_chart[i] = CIRCULAR_SPECTRUM_MIN_RADIUS +
                       (value / 100.0f) * (CIRCULAR_SPECTRUM_MAX_RADIUS - CIRCULAR_SPECTRUM_MIN_RADIUS);

        // 限制范围
        if (bar_chart[i] < CIRCULAR_SPECTRUM_MIN_RADIUS) {
            bar_chart[i] = CIRCULAR_SPECTRUM_MIN_RADIUS;
        }
        if (bar_chart[i] > CIRCULAR_SPECTRUM_MAX_RADIUS) {
            bar_chart[i] = CIRCULAR_SPECTRUM_MAX_RADIUS;
        }
    }
}

// 分贝值转幅度值
static float db_to_magnitude_optimized(float db_value)
{
    if (db_value <= -143.0f) {
        return 0.0f;
    }
    if (db_value >= 0.0f) {
        return 100.0f;
    }

    float magnitude = (db_value + 140.0f) * (100.0f / 140.0f);

    if (magnitude < 1.0f) {
        magnitude = 1.0f;
    }
    if (magnitude > 100.0f) {
        magnitude = 100.0f;
    }

    return magnitude;
}

// 获取余弦值（优化版）
static int32_t get_cos(int32_t deg, int32_t a)
{
    int32_t r = (lv_trigo_cos(deg) * a);
    r += LV_TRIGO_SIN_MAX / 2;
    return r >> LV_TRIGO_SHIFT;
}

// 获取正弦值（优化版）
static int32_t get_sin(int32_t deg, int32_t a)
{
    int32_t r = lv_trigo_sin(deg) * a;
    r += LV_TRIGO_SIN_MAX / 2;
    return r >> LV_TRIGO_SHIFT;
}

// 修改绘制函数，使用 g_spectrum_bg_avg_color
static void circular_spectrum_draw_event_cb(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);

    if (code != LV_EVENT_DRAW_POST_BEGIN) {
        return;
    }

    lv_obj_t *obj = lv_event_get_target(e);
    lv_draw_ctx_t *draw_ctx = lv_event_get_draw_ctx(e);

    if (!obj || !draw_ctx || !lv_obj_is_valid(obj) || !lv_obj_is_visible(obj)) {
        return;
    }

    lv_coord_t width = lv_obj_get_width(obj);
    lv_coord_t height = lv_obj_get_height(obj);

    if (width <= 0 || height <= 0) {
        return;
    }

    // 计算圆心位置
    lv_point_t center;
    center.x = obj->coords.x1 + width / 2;
    center.y = obj->coords.y1 + height / 2;


    // 设置多边形描述符
    lv_draw_rect_dsc_t rect_dsc;
    lv_draw_rect_dsc_init(&rect_dsc);
    rect_dsc.bg_opa = LV_OPA_100;
    rect_dsc.radius = 4;

    // 使用背景平均颜色
    lv_color_t base_color;
    base_color = lv_color_make(g_spectrum_bg_avg_color.r,
                               g_spectrum_bg_avg_color.g,
                               g_spectrum_bg_avg_color.b);

    // 绘制每个条形
    for (int i = 0; i < CIRCULAR_SPECTRUM_BAR_CNT; i++) {
        int32_t deg_base = i * CIRCULAR_SPECTRUM_DEG_STEP;
        int32_t deg_space = 1;

        // 获取条形的外半径
        int32_t outer_radius = (int32_t)bar_chart[i];
        int32_t inner_radius = CIRCULAR_SPECTRUM_INNER_RADIUS;

        // 计算多边形的四个顶点
        lv_point_t poly[4];

        // 第一个外点
        int32_t deg = deg_base + deg_space;
        poly[0].x = center.x + get_cos(deg, outer_radius);
        poly[0].y = center.y + get_sin(deg, outer_radius);

        // 第一个内点
        poly[1].x = center.x + get_cos(deg, inner_radius);
        poly[1].y = center.y + get_sin(deg, inner_radius);

        // 第二个内点
        deg += CIRCULAR_SPECTRUM_DEG_STEP - deg_space * 2;
        poly[2].x = center.x + get_cos(deg, inner_radius);
        poly[2].y = center.y + get_sin(deg, inner_radius);

        // 第二个外点
        poly[3].x = center.x + get_cos(deg, outer_radius);
        poly[3].y = center.y + get_sin(deg, outer_radius);

        // 设置颜色为背景平均颜色
        rect_dsc.bg_color = base_color;

        // 绘制多边形
        lv_draw_polygon(draw_ctx, &rect_dsc, poly, 4);
    }
}

// 删除事件回调
static void spectrum_delete_event_cb(lv_event_t *e)
{
    if (lv_event_get_code(e) == LV_EVENT_DELETE) {
        spectrum_obj = NULL;
    }
}

void ui_music_spectrum_handler(float db_data[2][MAX_SPECTRUM_SECTION_NUM])
{
    static float magnitude_data[USE_SPECTRUM_SECTION_NUM] = {0};
    float min_db = -140.0f;
    float max_db = 0.0f;


    // 处理32个频段数据
    for (int i = 0; i < USE_SPECTRUM_SECTION_NUM; i++) {
        float db_left = db_data[0][i];
        float db_right = db_data[1][i];
        float db_avg = (db_left + db_right) / 2.0f;

        if (db_avg < min_db) {
            db_avg = min_db;
        }
        if (db_avg > max_db) {
            db_avg = max_db;
        }

        magnitude_data[i] = db_to_magnitude_optimized(db_avg);
    }

    // 清零数组
    memset(expanded_data, 0, sizeof(expanded_data));

    // 使用插值算法将USE_SPECTRUM_SECTION_NUM点扩展到72点
    for (int i = 0; i < CIRCULAR_SPECTRUM_BAR_CNT; i++) {
        float position = (float)i * (USE_SPECTRUM_SECTION_NUM - 1) / 71.0f;
        int index1 = (int)position;
        int index2 = index1 + 1;
        if (index2 > USE_SPECTRUM_SECTION_NUM - 1) {
            index2 = USE_SPECTRUM_SECTION_NUM - 1;
        }

        float fraction = position - index1;

        // 线性插值
        expanded_data[i] = magnitude_data[index1] * (1.0f - fraction) +
                           magnitude_data[index2] * fraction;

    }


    // 直接使用 expanded_data 计算半径
    for (int i = 0; i < CIRCULAR_SPECTRUM_BAR_CNT; i++) {
        float value = expanded_data[i];
        // 转换为半径长度
        bar_chart[i] = CIRCULAR_SPECTRUM_MIN_RADIUS +
                       (value / 100.0f) * (CIRCULAR_SPECTRUM_MAX_RADIUS - CIRCULAR_SPECTRUM_MIN_RADIUS);

        // 限制范围
        if (bar_chart[i] < CIRCULAR_SPECTRUM_MIN_RADIUS) {
            bar_chart[i] = CIRCULAR_SPECTRUM_MIN_RADIUS;
        }
        if (bar_chart[i] > CIRCULAR_SPECTRUM_MAX_RADIUS) {
            bar_chart[i] = CIRCULAR_SPECTRUM_MAX_RADIUS;
        }
    }

    // 更新显示
    lvgl_rpc_post_func(ui_music_update_spectrum_with_magnitude, 0);
}

void ui_music_draw_spectrum(void)
{
    lv_ui_music_player *ui_scr = ui_get_scr_ptr(&guider_ui, GUI_SCREEN_MUSIC_PLAYER);
    if (!ui_scr || ui_scr->music_player_del) {
        return;
    }

    // 检查是否已存在
    if (spectrum_obj && !lv_obj_is_valid(spectrum_obj)) {
        spectrum_obj = NULL;
    }

    // 检查主屏幕
    if (!lv_scr_act()) {
        return;
    }

    spectrum_obj = ui_scr->music_player_view_1;

    // 清除旧标志
    lv_obj_clear_flag(spectrum_obj, LV_OBJ_FLAG_SCROLLABLE);

    // 设置新的绘制回调
    lv_obj_add_event_cb(spectrum_obj, circular_spectrum_draw_event_cb, LV_EVENT_DRAW_POST_BEGIN, NULL);
    lv_obj_add_event_cb(spectrum_obj, spectrum_delete_event_cb, LV_EVENT_DELETE, NULL);

    // 设置对象样式
    lv_obj_set_style_bg_opa(spectrum_obj, LV_OPA_TRANSP, 0);
    lv_obj_set_style_border_width(spectrum_obj, 0, 0);
    lv_obj_set_style_pad_all(spectrum_obj, 0, 0);

    // 强制重绘
    lv_obj_invalidate(spectrum_obj);
}

void ui_music_update_spectrum_with_magnitude(void)
{
    // 标记重绘
    if (spectrum_obj && lv_obj_is_valid(spectrum_obj)) {
        lv_obj_invalidate(spectrum_obj);
    } else {
        ui_music_draw_spectrum();
    }
}

#endif
