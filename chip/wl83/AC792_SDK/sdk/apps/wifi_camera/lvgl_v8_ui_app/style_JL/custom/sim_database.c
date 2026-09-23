#include "app_config.h"
#ifdef CONFIG_UI_STYLE_JL_ENABLE
/**
 * @file C
 *
 */

/*********************
 *      INCLUDES
 *********************/

#include "sim_database.h"

#if LV_USE_GUIBUILDER_SIMULATOR//电脑仿真专用

/*
 * app配置项表---仿真模拟固定菜单表专用
 * 参数1: 配置项名字
 * 参数2: 配置项需要多少个字节存储(最大4字节)
 * 参数4: 配置项的默认值
 */
static const struct db_cfg default_config_table[] = {
    /*
     *  录像模式配置项
     */
    {"mic",     1,     1},                         // 录音开关
    {"mot",     1,     0},                         // 移动侦测开关
    {"par",     1,     0},                         // 停车守卫开关
    {"wdr",     1,     0},                         // 夜视增强开关
    {"num",     1,     0},                         // 车牌开关
    {"dat",     1,     1},                         // 时间标签开关
    {"two",     1,     1},                         // 双路开关
    {"gra",     2,     GRA_SEN_MD},               // 重力感应灵敏度
    {"res",     3,     VIDEO_RES_720P},           // 录像分辨率
    {"cyc",     4,     1},                         // 循环录像时间，单位分钟
    {"exp",     4,     0},                         // 曝光, 范围-3到+3
    {"cna",     4,    CN_PA},                     // 车牌号码前3个字符
    {"cnb",     4,    CN_PB},                     // 车牌号码后4个字符
    {"gap",     4,    0},                         // 间隔录影设置
    /*
     *  系统模式配置项
     */
    {"kvo",     1,    1},                         // 按键音开关
    {"lag",     4,    1},        // 语言设置
    {"fre",     4,    50},                        // 灯光频率
    {"aff",     4,    0},                         // 自动关机时间, 单位分钟
    {"pro",     4,    0},                         // 屏幕保护时间, 单位秒
    {"tvm",     4,    TVM_PAL},                   // 电视制式
    {"lan",     4,   0},                         // 轨道偏移
    {"hlw",     1,    0},                         // 前照灯提醒开关
    {"datey",     4,    2024},                         // 年
    {"datem",     1,    5},                         // 月
    {"dated",     1,    20},                         //日
    {"dateh",     1,    13},                         // 时
    {"datemi",     1,    14},                         // 分

    /*
     *  拍照模式配置项
     */
    {"sok",     1,     0},                         // 防手抖开关
    {"pdat",    1,     1},                         // 图片日期标签开关
    {"cyt",     1,     0},                         // 连拍开关
    {"qua",     3,     PHOTO_QUA_HI},              // 图片质量
    {"acu",     3,     PHOTO_ACU_HI},              // 图片锐度
    {"phm",     4,     0},                         // 延时拍照， 单位秒
    {"pres",    4,     PHOTO_RES_1M},              // 图片分辨率
    {"wbl",     4,     PHOTO_WBL_AUTO},            // 白平衡
    {"col",     4,     PHOTO_COLOR_NORMAL},        // 颜色模式
    {"sca",     4,     0},                         // 快速预览时间，单位s
    {"pexp",    4,     0},                         // 曝光设置，范围-3到+3
    {"iso",     4,    0},                         // iso
    {"stk",     4,     0},                         // 大头贴索引

    {"dac",     4,    0x55aa},                         // dac_trim

#if 0//def CONFIG_WIFI_ENABLE
    {"res2",    3,      VIDEO_RES_VGA},           // 录像分辨率
    {"rtf",     3,      VIDEO_RES_VGA},            //预览前视分辨率
    {"rtb",     3,      VIDEO_RES_VGA},             //预览后视分辨率
    {"wfo",     1,      1},                         //wifi开关
    {"wfmode",  1,      0},                        // wifi运行模式
    {"bvo",     1,      1},                         // 开机音开关
#endif

};

/*
 * app配置项表---仿真模拟设置专用
 * 参数1: 配置项名字
 * 参数2: 配置项需要多少个字节存储(最大4字节)
 * 参数4: 配置项的默认值
 */
static struct db_cfg config_table[] = {
    /*
     *  录像模式配置项
     */
    {"mic",     1,     1},                         // 录音开关
    {"mot",     1,     0},                         // 移动侦测开关
    {"par",     1,     0},                         // 停车守卫开关
    {"wdr",     1,     0},                         // 夜视增强开关
    {"num",     1,     0},                         // 车牌开关
    {"dat",     1,     1},                         // 时间标签开关
    {"two",     1,     1},                         // 双路开关
    {"gra",     2,     GRA_SEN_MD},               // 重力感应灵敏度
    {"res",     3,     VIDEO_RES_720P},           // 录像分辨率
    {"cyc",     4,     1},                         // 循环录像时间，单位分钟
    {"exp",     4,     0},                         // 曝光, 范围-3到+3
    {"cna",     4,    CN_PA},                     // 车牌号码前3个字符
    {"cnb",     4,    CN_PB},                     // 车牌号码后4个字符
    {"gap",     4,    0},                         // 间隔录影设置
    /*
     *  系统模式配置项
     */
    {"kvo",     1,    1},                         // 按键音开关
    {"lag",     4,    1},        // 语言设置
    {"fre",     4,    50},                        // 灯光频率
    {"aff",     4,    0},                         // 自动关机时间, 单位分钟
    {"pro",     4,    0},                         // 屏幕保护时间, 单位秒
    {"tvm",     4,    TVM_PAL},                   // 电视制式
    {"lan",     4,   0},                         // 轨道偏移
    {"hlw",     1,    0},                         // 前照灯提醒开关
    {"datey",     4,    2024},                         // 年
    {"datem",     1,    5},                         // 月
    {"dated",     1,    20},                         //日
    {"dateh",     1,    13},                         // 时
    {"datemi",     1,    14},                         // 分
    /*
     *  拍照模式配置项
     */
    {"sok",     1,     0},                         // 防手抖开关
    {"pdat",    1,     1},                         // 图片日期标签开关
    {"cyt",     1,     0},                         // 连拍开关
    {"qua",     3,     PHOTO_QUA_HI},              // 图片质量
    {"acu",     3,     PHOTO_ACU_HI},              // 图片锐度
    {"phm",     4,     0},                         // 延时拍照， 单位秒
    {"pres",    4,     PHOTO_RES_1M},              // 图片分辨率
    {"wbl",     4,     PHOTO_WBL_AUTO},            // 白平衡
    {"col",     4,     PHOTO_COLOR_NORMAL},        // 颜色模式
    {"sca",     4,     0},                         // 快速预览时间，单位s
    {"pexp",    4,     0},                         // 曝光设置，范围-3到+3
    {"iso",     4,    0},                         // iso
    {"stk",     4,     0},                         // 大头贴索引

    {"dac",     4,    0x55aa},                         // dac_trim

#if 0//def CONFIG_WIFI_ENABLE
    {"res2",    3,      VIDEO_RES_VGA},           // 录像分辨率
    {"rtf",     3,      VIDEO_RES_VGA},            //预览前视分辨率
    {"rtb",     3,      VIDEO_RES_VGA},             //预览后视分辨率
    {"wfo",     1,      1},                         //wifi开关
    {"wfmode",  1,      0},                        // wifi运行模式
    {"bvo",     1,      1},                         // 开机音开关
#endif

};


//读取指定菜单项
int db_select(const char *name)
{
    int err;
    int value = 0;

    if (name == NULL) {
        return -22;
    }

    for (int i = 0; i < ARRAY_SIZE(config_table); i++) {
        if (!strcmp(name, config_table[i].name)) {
            return config_table[i].value;
        }
    }
    return -22;
}

//更新指定菜单项
int db_update(const char *name, uint32_t value)
{
    int err;

    if (name == NULL) {
        return -22;
    }

    for (int i = 0; i < ARRAY_SIZE(config_table); i++) {
        if (!strcmp(name, config_table[i].name)) {
            config_table[i].value = value;
        }
    }
    return -22;
}


//恢复默认配置--用户配置项0~59
int db_reset(void)
{
    int err;
    int value;

    for (int i = 0; i < ARRAY_SIZE(config_table); i++) {
        config_table[i].value = default_config_table[i].value;
    }
    puts(">>>db_reset okk~");
}



#endif

#endif
