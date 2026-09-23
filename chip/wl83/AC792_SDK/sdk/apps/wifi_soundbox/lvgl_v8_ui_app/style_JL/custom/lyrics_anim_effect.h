// lyrics_anim_effect.h
#ifndef LYRIC_ANIM_EFFECT_H
#define LYRIC_ANIM_EFFECT_H

#include "lvgl.h"

#ifdef __cplusplus
extern "C" {
#endif

// 歌词特效参数
typedef struct {
    int32_t delay;      // 延迟时间(ms)
    int32_t duration;   // 持续时间(ms)
    lv_coord_t target_x; // 目标X坐标（新增）
    lv_coord_t target_y; // 目标Y坐标（新增）
} lyrics_anim_effect_args_t;

// 安全特效函数
void lyrics_anim_effect_zooming_in_down(lv_obj_t *lyrics_obj, lyrics_anim_effect_args_t *args);
void lyrics_anim_effect_zooming_in(lv_obj_t *lyrics_obj, lyrics_anim_effect_args_t *args);

// 清理函数
void lyrics_anim_effect_cleanup(void);

#ifdef __cplusplus
}
#endif

#endif /* LYRIC_ANIM_EFFECT_H */
