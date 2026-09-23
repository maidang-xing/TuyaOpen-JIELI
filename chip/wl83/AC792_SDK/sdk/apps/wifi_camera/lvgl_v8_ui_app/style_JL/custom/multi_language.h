#include "app_config.h"
#ifdef CONFIG_UI_STYLE_JL_ENABLE
#ifndef __MULTI_LANGUAGE_H_
#define __MULTI_LANGUAGE_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "custom.h"


typedef struct {
    const char *font_name;
    const char *ture_name;//对应excel表suplanguage的字体字号
    const char *origin_text;//对应excel表origin_text
    int id;//id宏 写flash用
} excel_font_mapping_t;



/*
      中文: 中文
      繁体中文: 繁體中文
      英语: English
      俄语: Русский язык
      泰语: ภาษาไทย
      阿拉伯语: اللغة العربية
      德语: Deutsch
      法语: Français
      韩语: 한국어
      日语: 日本語
      西班牙语: Español
      葡萄牙语: Português
      捷克语: Čeština
      波兰语: Polski
      意大利语: Italiano
      荷兰语: Nederlands
      瑞典语: Svenska
      丹麦语: Dansk
*/
enum {//语言
    LANG_ZH_CN = 1,
    LANG_ZH_HK,
    LANG_ENGLISH,
    LANG_RU,
    LANG_AR,
    LANG_TH,
    LANG_DE,
    LANG_FR,
    LANG_KO,
    LANG_JA,
    LANG_ES,
    LANG_PT,
    LANG_CS,
    LANG_PL,
    LANG_IT,
    LANG_NL,
    LANG_SV,
    LANG_DA
};

/*
*   根据flash语言设置刷新所有UI的字体样式
*   返回值：对应excel表的origin_text
*/
char *refresh_all_obj_language_style(void);


/*
*   弹性布局放置18语 label列表并根据语言映射表设置对应的字体样式
*
*/
void flex_language_list(void);


/*
*   隐藏弹性布局放置18语 label列表
*
*/
void hide_flex_language_list(void);


#ifdef __cplusplus
}
#endif
#endif /* __MULTI_LANGUAGE_H_ */


#endif
