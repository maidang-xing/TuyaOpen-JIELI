#include "custom.h"
#if !LV_USE_GUIBUILDER_SIMULATOR
#include "effects/eq_config.h"
#include "app_core.h"
#include "app_config.h"
/*#include "action.h"*/
#include "ui.h"
#include "fs/fs.h"
#if TCFG_EQ_ENABLE
void ui_eq_update_sliders_from_eq_mode(EQ_MODE mode);
void ui_eq_ddlist_set_eq_mode(EQ_MODE cur_mode);

void res_event_music_eq_mode_set(lv_event_t *e)
{
    //UI层设置eq模式
    lv_obj_t *ddlist = lv_event_get_target(e);
    uint16_t selected_idx = lv_dropdown_get_selected(ddlist);
    eq_mode_set(selected_idx);
    ui_eq_update_sliders_from_eq_mode(selected_idx); //UI同步更新新模式下的滑动条
    lvgl_module_msg_send_value(GUI_PLAYER_MSG_ID_SAVE_MODE, LV_STATE_DISABLED, 0); //更新保存按钮的状态
}

void res_event_music_eq_gain_change_custom(lv_event_t *e)
{
    //UI 层获取slider增益的值并更新到EQ custom模式
    lv_ui_eq_modify *ui_scr = ui_get_scr_ptr(&guider_ui, GUI_SCREEN_EQ_MODIFY);
    if (!ui_scr || ui_scr->eq_modify_del) {
        return;
    }

    // 直接访问每个slider
    lv_obj_t *sliders[10] = {
        ui_scr->eq_modify_slider_1,
        ui_scr->eq_modify_slider_2,
        ui_scr->eq_modify_slider_3,
        ui_scr->eq_modify_slider_4,
        ui_scr->eq_modify_slider_5,
        ui_scr->eq_modify_slider_6,
        ui_scr->eq_modify_slider_7,
        ui_scr->eq_modify_slider_8,
        ui_scr->eq_modify_slider_9,
        ui_scr->eq_modify_slider_10
    };

    // 更新每个slider的值
    for (int i = 0; i < 10; i++) {
        if (sliders[i] && lv_obj_is_valid(sliders[i])) {
            int32_t value = lv_slider_get_value(sliders[i]);
            printf("slider[%d] value: %d\n", i, value);
            eq_mode_set_custom_param(i, value);
        } else {
            printf("warn：slider[%d] invalid\n", i);
        }
    }

    // 切换到自定义模式
    eq_mode_set(EQ_MODE_CUSTOM);
}

void res_event_music_eq_save_enable(lv_event_t *e)
{
    //设置保存按钮使能，且EQ模式变为custom自定义模式
    lvgl_module_msg_send_value(GUI_PLAYER_MSG_ID_SAVE_MODE, LV_STATE_DEFAULT, 0);
    ui_eq_ddlist_set_eq_mode(EQ_MODE_CUSTOM);  //ddlist显示为custom模式
}

//UI层面更新
/**
 * UI层根据EQ模式的增益更新所有slider
 * @param mode EQ模式 (EQ_MODE_NORMAL, EQ_MODE_ROCK等)
 */
void ui_eq_update_sliders_from_eq_mode(EQ_MODE mode)
{
    // 1. 验证模式有效性
    if (mode >= EQ_MODE_MAX) {
        printf("invalid EQ mode: %d\n", mode);
        return;
    }

    // 2. 遍历10个频段
    for (int i = 0; i < 10; i++) {
        // 获取该模式下第i段的增益值 (dB)
        float gain_db = (float)eq_mode_get_gain(mode, i);

        // 更新对应的slider
        lvgl_module_msg_send_value(GUI_PLAYER_MSG_ID_EQ_1 + i, gain_db, 0);
    }
}

/**
 * UI层更新单个slider
 * @param band_index 频段索引 (0-9)
 * @param gain_db 增益值 (dB)
 */
void ui_eq_update_single_slider(int band_index, float gain_db)
{
    lvgl_module_msg_send_value(GUI_PLAYER_MSG_ID_EQ_1 + band_index, gain_db, 0);
}

/**
 * UI层更新设置EQ模式到Dropdown列表
 * @param cur_mode EQ模式ID (EQ_MODE_NORMAL, EQ_MODE_ROCK等)
 */
void ui_eq_ddlist_set_eq_mode(EQ_MODE cur_mode)
{
    lv_ui_eq_modify *ui_scr = ui_get_scr_ptr(&guider_ui, GUI_SCREEN_EQ_MODIFY);
    if (!ui_scr || ui_scr->eq_modify_del) {
        return;
    }

    if (!lv_obj_is_valid(ui_scr->eq_modify_ddlist_1)) {
        return;
    }

    lv_obj_t *ddlist = ui_scr->eq_modify_ddlist_1;

    u8 selected_index = (u8)cur_mode;

    // 调用UI框架的选中函数
    lv_dropdown_set_selected(ddlist, selected_index);
}

int gui_src_action_eq_modify(int action)
{

    printf("--->%s()----->%d, action: %d\n", __func__, __LINE__, action);

    switch (action) {
    case GUI_SCREEN_ACTION_LOAD: {
        printf("--->%s()----->%d, action: %d\n", __func__, __LINE__, action);
        //获取当前模式，并更新到滑动条和下拉页面中
        ui_eq_ddlist_set_eq_mode(eq_mode_get_cur());
        //读取当前mode的增益并更新到slider
        ui_eq_update_sliders_from_eq_mode(eq_mode_get_cur());
    }
    break;
    case GUI_SCREEN_ACTION_UNLOAD:

        break;
    }

}
REGISTER_UI_SCREEN_ACTION_HANDLER(GUI_SCREEN_EQ_MODIFY)
.onchange = gui_src_action_eq_modify,
};
#endif
#endif
