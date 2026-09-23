#include "app_config.h"
#ifdef CONFIG_UI_STYLE_JL_ENABLE
/**
 * @file C
 *
 * BY HUANG YEJIAN
 *
 * 20241203
 */

/*********************
 *      INCLUDES
 *********************/

#include "multi_language.h"


//多国语言18语字体映射表
static const excel_font_mapping_t excel_font_mapping[] = {
    {"lv_font_fangsong_16", "中文", "zh_cn", LANG_ZH_CN},
    {"lv_font_fangsong_16", "繁體中文", "zh_hk", LANG_ZH_HK},
    {"lv_font_timesnewromanpsmt_16", "English", "en", LANG_ENGLISH},
    {"lv_font_timesnewromanpsmt_16", "Русский язык", "ru", LANG_RU},
    {"lv_font_segoeui_16", "اللغة العربية", "ar_ae", LANG_AR},
    {"lv_font_leelawadeeui_16", "ภาษาไทย", "th", LANG_TH},
    {"lv_font_segoeui_16", "Deutsch", "de", LANG_DE},
    {"lv_font_segoeui_16", "Français", "fr", LANG_FR},
    {"lv_font_malgungothic_16", "한국어", "ko", LANG_KO},
    {"lv_font_fangsong_16", "日本語", "ja", LANG_JA},
    {"lv_font_segoeui_16", "Español", "es", LANG_ES},
    {"lv_font_segoeui_16", "Português", "pt", LANG_PT},
    {"lv_font_segoeui_16", "Čeština", "cs", LANG_CS},
    {"lv_font_segoeui_16", "Polski", "pl", LANG_PL},
    {"lv_font_segoeui_16", "Italiano", "it", LANG_IT},
    {"lv_font_segoeui_16", "Nederlands", "nl", LANG_NL},
    {"lv_font_segoeui_16", "Svenska", "sv", LANG_SV},
    {"lv_font_segoeui_16", "Dansk", "da", LANG_DA},
    {NULL, NULL, NULL, NULL} // End mark
};


#define FLEX_POS_X  6
#define FLEX_POS_Y  93
#define FLEX_WIDTH  354
#define FLEX_HEIGHT  316//239

#if !LV_USE_GUIBUILDER_SIMULATOR
extern lv_group_t *def_group;
extern lv_group_t *group_list;
extern lv_indev_t *indev_keypad;
#endif

static lv_obj_t *flex_cont = 0;
static lv_obj_t *focused_obj = 0;//记录当前高亮对象


static void flex_cont_event_handler(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    //lv_ui* ui = (lv_ui*)lv_event_get_user_data(e);
    lv_obj_t *src = lv_event_get_target(e);
    char label_str[128] = { 0 };

    switch (code) {
    case LV_EVENT_CLICKED: {
        if (focused_obj) {//取消高亮上一次选项
            printf("[chili]: %s focused_obj:%d\n", __func__, focused_obj);
            lv_obj_clear_state(focused_obj, LV_STATE_DISABLED);
            //lv_obj_clear_state(focused_obj, LV_STATE_FOCUS_KEY);
        }
        if (src) {//高亮被点击项
            lv_obj_add_state(src, LV_STATE_DISABLED);
            //lv_obj_add_state(src, LV_STATE_FOCUS_KEY);
            focused_obj = src;
        }
        strcpy(label_str, lv_label_get_text(src));

        for (uint16_t i = 0; excel_font_mapping[i].ture_name != NULL; i++) {
            if (strcmp(label_str, excel_font_mapping[i].ture_name) == 0) {
                db_update("lag", excel_font_mapping[i].id);
                lv_i18n_set_locale(excel_font_mapping[i].origin_text);
                break;
            }
        }
        i18n_refresh_all_texts(); //语言即可生效
        //刷新菜单子页面标题
        my_sysmenu_subpage.icon_res_id = (void *)RES_LANGUAGES;
        my_sysmenu_subpage.title = (void *)_("language");

        sysmenu_subpage_show(&my_sysmenu_subpage);
#if !LV_USE_GUIBUILDER_SIMULATOR
        //组切回默认组
        if (def_group) {
            lv_group_set_default(def_group);
            lv_indev_set_group(indev_keypad, def_group);
        }
#endif
        lv_ui_sys_setting *ui_scr = ui_get_scr_ptr(&guider_ui, GUI_SCREEN_SYS_SETTING);
        if (!ui_scr) {
            return;
        }
        lv_group_focus_obj(ui_scr->sys_setting_img_5);

    }
    break;
    default:
        break;
    }
}

/*
*   弹性布局放置18语 label列表并根据语言映射表设置对应的字体样式
*
*/
void flex_language_list(void)
{
    const lv_font_t *font_tmp = NULL;

    printf("[chili]: %s flex_cont:%d\n", __func__, flex_cont);

    if (flex_cont) {
        //lv_obj_clear_flag(flex_cont, LV_OBJ_FLAG_HIDDEN);
        printf("[chili]: %s %d\n", __func__, __LINE__);
        lv_obj_del(flex_cont);
        flex_cont = NULL;
    }
    //else
    {
        lv_ui_sys_setting *ui_scr = ui_get_scr_ptr(&guider_ui, GUI_SCREEN_SYS_SETTING);
        if (!ui_scr) {
            return;
        }
        flex_cont = lv_obj_create(ui_scr->sys_setting_view_subpage);
        lv_obj_set_pos(flex_cont, FLEX_POS_X, FLEX_POS_Y);//88
        lv_obj_set_size(flex_cont, FLEX_WIDTH, FLEX_HEIGHT);
        lv_obj_set_style_pad_all(flex_cont, 0, 0);//布局风格
        lv_obj_set_style_arc_width(flex_cont, 0, 0);
        lv_obj_set_flex_flow(flex_cont, LV_FLEX_FLOW_ROW_WRAP);//将孩子按行排列并包裹起来
        lv_obj_set_style_bg_color(flex_cont, lv_color_white(), 0);
        lv_obj_set_style_border_width(flex_cont, 0, 0);
        //lv_obj_add_flag(flex_cont, LV_OBJ_FLAG_CLICKABLE);

        //创建label列表并根据语言映射表设置对应的字体样式
        for (uint16_t i = 0; excel_font_mapping[i].ture_name != NULL; i++) {
            lv_obj_t *langu_label = lv_label_create(flex_cont);
            lv_label_set_text(langu_label, excel_font_mapping[i].ture_name);
            lv_obj_set_size(langu_label, 346, 54);
            lv_obj_clear_flag(langu_label, LV_OBJ_FLAG_SCROLLABLE);

            //Set style for langu_label. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
            lv_obj_set_style_border_width(langu_label, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_align(langu_label, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_top(langu_label, 14, LV_PART_MAIN | LV_STATE_DEFAULT);
            //lv_obj_set_style_border_color(langu_label, lv_color_black(), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_color(langu_label, lv_color_black(), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_opa(langu_label, LV_OPA_10, LV_PART_MAIN | LV_STATE_DEFAULT);

            //Set style for langu_label. Part: LV_PART_MAIN, State: LV_STATE_FOCUS_KEY
            lv_obj_set_style_bg_color(langu_label, lv_color_make(0xff, 0x00, 0x00), LV_PART_MAIN | LV_STATE_FOCUS_KEY);
            lv_obj_set_style_bg_opa(langu_label, 51, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
            lv_obj_set_style_text_align(langu_label, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
            lv_obj_set_style_pad_top(langu_label, 0, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
            lv_obj_set_style_border_width(langu_label, 15, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
            lv_obj_set_style_border_side(langu_label, LV_BORDER_SIDE_LEFT, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
            lv_obj_set_style_border_color(langu_label, lv_color_make(0xff, 0x00, 0x00), LV_PART_MAIN | LV_STATE_FOCUS_KEY);

            //Set style for langu_label. Part: LV_PART_MAIN, State:  LV_STATE_FOCUSED
            //lv_obj_set_style_bg_color(langu_label, lv_color_make(0xff, 0x00, 0x00), LV_PART_MAIN | LV_STATE_FOCUSED);
            //lv_obj_set_style_bg_opa(langu_label, 51, LV_PART_MAIN | LV_STATE_FOCUSED);
            //lv_obj_set_style_text_align(langu_label, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_FOCUSED);
            //lv_obj_set_style_pad_top(langu_label, 0, LV_PART_MAIN | LV_STATE_FOCUSED);
            //lv_obj_set_style_border_width(langu_label, 15, LV_PART_MAIN | LV_STATE_FOCUSED);
            //lv_obj_set_style_border_side(langu_label, LV_BORDER_SIDE_LEFT, LV_PART_MAIN | LV_STATE_FOCUSED);
            //lv_obj_set_style_border_color(langu_label, lv_color_make(0xff, 0x00, 0x00), LV_PART_MAIN  | LV_STATE_FOCUSED);

            //Set style for langu_label. Part: LV_PART_MAIN, State: LV_STATE_DISABLED
            lv_obj_set_style_bg_color(langu_label, lv_color_make(0xff, 0x00, 0x00), LV_PART_MAIN | LV_STATE_DISABLED);
            lv_obj_set_style_bg_opa(langu_label, 51, LV_PART_MAIN | LV_STATE_DISABLED);
            lv_obj_set_style_text_align(langu_label, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DISABLED);
            lv_obj_set_style_pad_top(langu_label, 0, LV_PART_MAIN | LV_STATE_DISABLED);
            lv_obj_set_style_border_width(langu_label, 15, LV_PART_MAIN | LV_STATE_DISABLED);
            lv_obj_set_style_border_side(langu_label, LV_BORDER_SIDE_LEFT, LV_PART_MAIN | LV_STATE_DISABLED);
            lv_obj_set_style_border_color(langu_label, lv_color_make(0xff, 0x00, 0x00), LV_PART_MAIN | LV_STATE_DISABLED);

            //根据设置的语言，高亮选择的label（LV_STATE_DISABLED样式做高亮）
            lv_obj_clear_state(langu_label, LV_STATE_DISABLED);
            //lv_obj_clear_state(langu_label, LV_STATE_FOCUS_KEY);
            if (db_select("lag") == excel_font_mapping[i].id) {
                printf("[chili]: %s excel_font_mapping[i].id %d langu_label:%d\n", __func__, excel_font_mapping[i].id, langu_label);
                lv_obj_add_state(langu_label, LV_STATE_DISABLED);
                //lv_obj_add_state(langu_label, LV_STATE_FOCUS_KEY);
                focused_obj = langu_label;
            }

            //每一行语言项根据语言分别设置字体样式
            //printf("[chili]: %s fontname%s\n", __func__, excel_font_mapping[i].font_name);
            font_tmp = lv_i18n_get_font_by_name(excel_font_mapping[i].font_name);
            //printf("[chili]: %s font_tmp %d\n", __func__, font_tmp);
            if (font_tmp && langu_label) {
                lv_obj_set_style_text_font(langu_label, font_tmp, LV_STATE_DEFAULT);
                lv_obj_set_style_text_font(langu_label, font_tmp, LV_STATE_ANY);
            }
            lv_obj_add_flag(langu_label, LV_OBJ_FLAG_CLICKABLE);
            lv_obj_add_event_cb(langu_label, flex_cont_event_handler, LV_EVENT_CLICKED, NULL);
            //lv_obj_update_layout(flex_cont);//刷新一下容器
#if !LV_USE_GUIBUILDER_SIMULATOR
            //加入按键组
            if (group_list) {
                lv_group_add_obj(group_list, langu_label);
            }
#endif
        }
    }



#if !LV_USE_GUIBUILDER_SIMULATOR
    //默认组切换
    if (group_list) {
        lv_group_set_default(group_list);
        lv_indev_set_group(indev_keypad, group_list);
    }
#endif


}

/*
*   隐藏弹性布局放置18语 label列表
*
*/
void hide_flex_language_list(void)
{
    if (flex_cont) {
        printf("[chili]: %s %d\n", __func__, __LINE__);
        lv_obj_del(flex_cont);
        flex_cont = NULL;
        //lv_obj_add_flag(flex_cont, LV_OBJ_FLAG_HIDDEN);
    }
}

/*
*   根据flash语言设置刷新所有UI的字体样式
*   返回值：对应excel表的origin_text
*/
char *refresh_all_obj_language_style(void)
{
    uint16_t i = 0;
    for (i = 0; excel_font_mapping[i].ture_name != NULL; i++) {
        if (db_select("lag") == excel_font_mapping[i].id) {
            printf("[chili]: %s %d\n", __func__, __LINE__);
            lv_i18n_set_locale(excel_font_mapping[i].origin_text);
            break;
        }
    }
    i18n_refresh_all_texts(); //语言即可生效

    return excel_font_mapping[i].origin_text;
}



#endif
