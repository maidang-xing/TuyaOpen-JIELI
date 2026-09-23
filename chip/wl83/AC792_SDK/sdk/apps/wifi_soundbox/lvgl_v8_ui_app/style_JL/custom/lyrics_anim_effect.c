#include "lyrics_anim_effect.h"
#if !LV_USE_GUIBUILDER_SIMULATOR
#if LV_USE_LYRICS
// 配置参数
#define LYRIC_ANIM_ZOOM_BASE 256  // 256表示100%缩放
#define LYRIC_ANIM_MOVE_DISTANCE 100  // 底部上移距离

// 安全的歌词动画上下文结构
typedef struct {
    lv_obj_t *obj;              // 歌词对象（弱引用）
    uint8_t is_valid;           // 标记是否有效（1=有效，0=无效）
    uint8_t is_animating;       // 标记是否在动画中
    lv_coord_t start_x;         // 起始X坐标
    lv_coord_t start_y;         // 起始Y坐标
    lv_coord_t target_x;        // 目标X坐标
    lv_coord_t target_y;        // 目标Y坐标
    lv_coord_t original_y;      // 原始Y坐标（用于移动动画）
} safe_lyrics_context_t;

// 全局上下文池（避免动态内存分配）
#define MAX_SAFE_CONTEXTS 10
static safe_lyrics_context_t safe_contexts[MAX_SAFE_CONTEXTS] = {0};
static int context_index = 0;

// 获取安全上下文
static safe_lyrics_context_t *get_safe_context(lv_obj_t *obj)
{
    if (!obj) {
        return NULL;
    }

    // 寻找空闲位置
    for (int i = 0; i < MAX_SAFE_CONTEXTS; i++) {
        if (safe_contexts[i].obj == NULL) {
            safe_contexts[i].obj = obj;
            safe_contexts[i].is_valid = 1;
            safe_contexts[i].is_animating = 1;
            return &safe_contexts[i];
        }
    }

    // 如果满了，循环使用
    context_index = (context_index + 1) % MAX_SAFE_CONTEXTS;
    safe_contexts[context_index].obj = obj;
    safe_contexts[context_index].is_valid = 1;
    safe_contexts[context_index].is_animating = 1;
    return &safe_contexts[context_index];
}

// 验证上下文是否有效
static int is_context_valid(safe_lyrics_context_t *ctx)
{
    return (ctx != NULL && ctx->is_valid == 1 && ctx->obj != NULL);
}

// 无效化上下文
static void invalidate_context(safe_lyrics_context_t *ctx)
{
    if (ctx) {
        ctx->is_valid = 0;
        ctx->is_animating = 0;
        ctx->obj = NULL;
    }
}

// 安全的对象检查函数
static int is_obj_valid(lv_obj_t *obj)
{
    // 简化检查：确保对象指针不为NULL
    if (!obj) {
        return 0;
    }

    return 1;
}

// 安全的歌词颜色设置（无重绘）
static void safe_lyrics_set_color_no_redraw(lv_obj_t *obj, jlvg_color_t color)
{
    if (!is_obj_valid(obj)) {
        return;
    }

    // 直接设置颜色，不立即重绘
    lv_lyrics_set_color(obj, color);
}

// 安全的歌词缩放设置（无重绘）
static void safe_lyrics_set_zoom_no_redraw(lv_obj_t *obj, int32_t zoom_x, int32_t zoom_y)
{
    if (!is_obj_valid(obj)) {
        return;
    }

    // 边界检查
    if (zoom_x < 0) {
        zoom_x = 0;
    }
    if (zoom_y < 0) {
        zoom_y = 0;
    }
    if (zoom_x > 1000) {
        zoom_x = 1000;    // 限制最大缩放
    }
    if (zoom_y > 1000) {
        zoom_y = 1000;
    }

    // 直接设置缩放，不立即重绘
    lv_lyrics_set_zoom(obj, zoom_x, zoom_y);
}

// 安全的歌词位置设置
static void safe_lyrics_set_pos_no_redraw(lv_obj_t *obj, lv_coord_t x, lv_coord_t y)
{
    if (!is_obj_valid(obj)) {
        return;
    }

    // 直接设置位置，不立即重绘
    lv_lyrics_set_pos(obj, x, y);
}

// 安全的歌词重绘函数（添加保护）
static void safe_lyrics_redraw(lv_obj_t *obj)
{
    if (!is_obj_valid(obj)) {
        printf("[WARN] Attempted to redraw invalid object\n");
        return;
    }

    // 这里使用简单的延迟机制
    static uint32_t last_redraw_time = 0;
    uint32_t current_time = lv_tick_get();

    // 限制重绘频率（最少间隔20ms）
    if (current_time - last_redraw_time < 20) {
        return;
    }

    last_redraw_time = current_time;

    // 尝试重绘
    lv_lyrics_fontimg_redarw(obj);
}

// 复合动画回调：同时处理缩放、位置和透明度
static void composite_zoom_move_opa_cb(void *var, int32_t v)
{
    safe_lyrics_context_t *ctx = (safe_lyrics_context_t *)var;
    if (!is_context_valid(ctx) || !is_obj_valid(ctx->obj)) {
        return;
    }

    lv_obj_t *obj = ctx->obj;

    // 边界检查
    if (v < 0) {
        v = 0;
    }
    if (v > 100) {
        v = 100;
    }

    // 1. 计算缩放：从10%到100%
    // 第一阶段：0-40%进度：10% -> 47.5%
    // 第二阶段：40%-100%进度：52% -> 100%
    uint32_t scale;
    if (v <= 40) {
        // 第一阶段：0-40%进度
        scale = v * 375 / 400 + 10;  // 10% + (v/40)*37.5%
    } else {
        // 第二阶段：40%-100%进度
        scale = (v - 40) * 48 / 60 + 52;  // 52% + ((v-40)/60)*48%
    }

    // 2. 计算位置：从起始位置移动到目标位置
    // 使用线性插值：v=0时在起始位置，v=100时在目标位置
    lv_coord_t current_x, current_y;

    // 方法A：简单的线性插值
    current_x = ctx->start_x + (ctx->target_x - ctx->start_x) * v / 100;
    current_y = ctx->start_y + (ctx->target_y - ctx->start_y) * v / 100;


    // 3. 计算透明度：从0到100%
    uint8_t alpha = v * 255 / 100;

    // 4. 应用所有效果
    // 计算缩放值
    int32_t zoom_value = scale * LYRIC_ANIM_ZOOM_BASE / 100;
    if (zoom_value < 26) {
        zoom_value = 26;    // 最小10%
    }
    if (zoom_value > 256) {
        zoom_value = 256;    // 最大100%
    }

    // 设置缩放（不立即重绘）
    safe_lyrics_set_zoom_no_redraw(obj, zoom_value, zoom_value);

    // 设置位置（不立即重绘） - 这里用current_x而不是ctx->target_x
    safe_lyrics_set_pos_no_redraw(obj, current_x, current_y);

    // 设置透明度（不立即重绘）
    jlvg_color_t color = {0xFF, 0xFF, 0xFF, alpha};
    safe_lyrics_set_color_no_redraw(obj, color);

    // 5. 重绘（控制频率）
    static uint32_t composite_redraw_count = 0;
    composite_redraw_count++;

    // 每3帧重绘一次
    if (composite_redraw_count % 3 == 0) {
        safe_lyrics_redraw(obj);
    }
}

// 简化版本：只处理缩放和透明度（向后兼容）
static void simple_zoom_opa_cb(void *var, int32_t v)
{
    lv_obj_t *obj = (lv_obj_t *)var;
    if (!is_obj_valid(obj)) {
        return;
    }

    // 边界检查
    if (v < 0) {
        v = 0;
    }
    if (v > 100) {
        v = 100;
    }

    // 计算缩放：从10%到47.5%
    uint32_t scale = v * 375 / 1000 + 10;

    // 计算透明度：从0到100%
    uint8_t alpha = v * 255 / 100;

    // 计算缩放值
    int32_t zoom_value = scale * LYRIC_ANIM_ZOOM_BASE / 100;
    if (zoom_value < 26) {
        zoom_value = 26;
    }
    if (zoom_value > 256) {
        zoom_value = 256;
    }

    // 设置缩放（不立即重绘）
    safe_lyrics_set_zoom_no_redraw(obj, zoom_value, zoom_value);

    // 设置透明度（不立即重绘）
    jlvg_color_t color = {0xFF, 0xFF, 0xFF, alpha};
    safe_lyrics_set_color_no_redraw(obj, color);

    // 重绘（控制频率）
    static uint32_t simple_redraw_count = 0;
    simple_redraw_count++;
    if (simple_redraw_count % 3 == 0) {
        safe_lyrics_redraw(obj);
    }
}

// 简化第二阶段动画回调
static void simple_second_stage_cb(void *var, int32_t v)
{
    lv_obj_t *obj = (lv_obj_t *)var;
    if (!is_obj_valid(obj)) {
        return;
    }

    // 边界检查
    if (v < 0) {
        v = 0;
    }
    if (v > 100) {
        v = 100;
    }

    // 计算缩放：从52%到100%
    uint32_t scale = v * 48 / 100 + 52;

    // 计算缩放值
    int32_t zoom_value = scale * LYRIC_ANIM_ZOOM_BASE / 100;
    if (zoom_value < 135) {
        zoom_value = 135;    // 52%
    }
    if (zoom_value > 256) {
        zoom_value = 256;    // 100%
    }

    // 设置缩放（不立即重绘）
    safe_lyrics_set_zoom_no_redraw(obj, zoom_value, zoom_value);

    // 透明度保持100%
    jlvg_color_t color = {0xFF, 0xFF, 0xFF, 0xFF};
    safe_lyrics_set_color_no_redraw(obj, color);

    // 重绘（控制频率）
    static uint32_t second_redraw_count = 0;
    second_redraw_count++;
    if (second_redraw_count % 3 == 0) {
        safe_lyrics_redraw(obj);
    }
}

static void anim_completed_cb(lv_anim_t *anim)
{
    if (!anim) {
        return;
    }

    safe_lyrics_context_t *ctx = (safe_lyrics_context_t *)anim->var;
    if (ctx && is_context_valid(ctx)) {

        // 只需确保最终缩放为100%
        if (is_obj_valid(ctx->obj)) {
            // 设置最终缩放（确保100%）
            safe_lyrics_set_zoom_no_redraw(ctx->obj, LYRIC_ANIM_ZOOM_BASE, LYRIC_ANIM_ZOOM_BASE);

            // 设置最终透明度（确保不透明）
            jlvg_color_t final_color = {0xFF, 0xFF, 0xFF, 0xFF};
            safe_lyrics_set_color_no_redraw(ctx->obj, final_color);

            // 只重绘一次
            safe_lyrics_redraw(ctx->obj);
        }

        // 清理上下文
        for (int i = 0; i < MAX_SAFE_CONTEXTS; i++) {
            if (&safe_contexts[i] == ctx) {
                invalidate_context(ctx);
                break;
            }
        }
    }
}
// 增强版ZoomInDown特效：包含缩放、上移和透明度动画
void lyrics_anim_effect_zooming_in_down(lv_obj_t *lyrics_obj, lyrics_anim_effect_args_t *args)
{
    if (!lyrics_obj || !args) {
        printf("[ERROR] Invalid parameters\n");
        return;
    }


    // 获取安全上下文
    safe_lyrics_context_t *ctx = get_safe_context(lyrics_obj);
    if (!ctx) {
        printf("[ERROR] No safe context available\n");
        return;
    }

    // 使用传入的目标位置（最可靠的方式）
    ctx->target_x = args->target_x;
    ctx->target_y = args->target_y;

    // 设置起始位置 - 在目标位置下方
    ctx->start_x = ctx->target_x;  // X坐标相同（水平居中位置不变）
    ctx->start_y = ctx->target_y + LYRIC_ANIM_MOVE_DISTANCE;  // 从下方开始

    // 创建单个复合动画，同时处理缩放、位置和透明度
    lv_anim_t composite_anim;
    lv_anim_init(&composite_anim);
    lv_anim_set_var(&composite_anim, ctx);
    lv_anim_set_exec_cb(&composite_anim, (lv_anim_exec_xcb_t)composite_zoom_move_opa_cb);
    lv_anim_set_values(&composite_anim, 0, 100);
    lv_anim_set_delay(&composite_anim, args->delay);
    lv_anim_set_time(&composite_anim, args->duration);

    // 使用自定义路径：先快速后慢速
    lv_anim_set_path_cb(&composite_anim, lv_anim_path_ease_out);
    lv_anim_set_ready_cb(&composite_anim, anim_completed_cb);

    // 设置初始状态
    safe_lyrics_set_zoom_no_redraw(lyrics_obj, 26, 26);  // 10%缩放
    safe_lyrics_set_pos_no_redraw(lyrics_obj, ctx->start_x, ctx->start_y);  // 起始位置

    jlvg_color_t transparent = {0xFF, 0xFF, 0xFF, 0x00};
    safe_lyrics_set_color_no_redraw(lyrics_obj, transparent);

    // 初始重绘
    safe_lyrics_redraw(lyrics_obj);

    // 启动复合动画
    lv_anim_start(&composite_anim);
}

// 清理所有动画
void lyrics_anim_effect_cleanup(void)
{

    // 停止所有动画
    for (int i = 0; i < MAX_SAFE_CONTEXTS; i++) {
        if (safe_contexts[i].obj && safe_contexts[i].is_animating) {
            // 停止所有相关动画
            lv_anim_del(safe_contexts[i].obj, NULL);
            lv_anim_del(&safe_contexts[i], NULL);

            // 恢复对象到最终位置
            if (is_obj_valid(safe_contexts[i].obj)) {
                safe_lyrics_set_pos_no_redraw(safe_contexts[i].obj,
                                              safe_contexts[i].target_x, safe_contexts[i].target_y);
                safe_lyrics_redraw(safe_contexts[i].obj);
            }

            invalidate_context(&safe_contexts[i]);
        }
    }
}
#endif
#endif