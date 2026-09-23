#include "system/includes.h"
#include "app_database.h"
#include "app_config.h"
#include "generic/typedef.h"
#include "syscfg/syscfg_id.h"
#include "bitstore.h"
//813d43e
/* #define CN_PA   (0x4EAC) */
//#define CN_PA   (0xE4BAAC)
//#define CN_PA   (0x4EAC)
/* #define CN_PB   (('A' << 24) | (' ' << 16) | ('1' << 8)  | ('2' << 0)) */
#define CN_PC   (('3' << 24) | ('4' << 16) | ('5' << 8) | (' ' << 0))


#define CN_PA   (('0' << 24) | ('A' << 16)  | (0xA9BE << 0))
#define CN_PB   (('0'    << 24) | ('0' << 16) | ('0' << 8) | ('0' << 0))


static const struct db_table app_config_table[] = {
    /*
     *  录像模式配置项
     */
    {"mic",     1,     1},                         // 录音开关
    {"mot",     1,     0},                         // 移动侦测开关
    {"par",     1,     1},                         // 停车守卫开关
    {"wdr",     1,     0},                         // 夜视增强开关
    {"num",     1,     0},                         // 车牌开关
    {"dat",     1,     1},                         // 时间标签开关
    {"two",     1,     1},                         // 双路开关
    {"gra",     2,     GRA_SEN_MD},               // 重力感应灵敏度
    {"gap",     4,     0},                         // 间隔录影设置
    {"res",     3,     VIDEO_RES_720P},           // 录像分辨率
    {"cyc",     4,     3},                         // 循环录像时间，单位分钟
    {"exp",     8,     0},                         // 曝光, 范围-3到+3
    {"cna",     32,     CN_PA},                     // 车牌号码--京
    {"cnb",     32,     CN_PB},                     // 车牌号码 --A 12
    {"cnc",     32,     CN_PC},                     // 车牌号码 --345
    {"proc",    32,    0},                     // 车牌号码 --345
    {"hdr",     8,     0},                     // HDR
    /*
     *  系统模式配置项
     */
    {"kvo",     1,     1},                         // 按键音开关
    {"lag",     4,     1},        // 语言设置
    {"fre",     8,     50},                        // 灯光频率
    {"aff",     8,     0},                         // 自动关机时间, 单位分钟
    {"pro",     8,     0},                         // 屏幕保护时间, 单位秒
    {"tvm",     5,     TVM_PAL},                   // 电视制式
    {"lan",     8,     0},                         // 轨道偏移
    {"hlw",     1,     0},                         // 前照灯提醒开关
    {"datey",     32,   2024},                         // 年
    {"datem",     5,   5},                         // 月
    {"dated",     5,   20},                         //日
    {"dateh",     7,   13},                         // 时
    {"datemi",    7,  14},                         // 分
    {"dates",     7,   10},                         // 秒

    /*
     *  拍照模式配置项
     */
    {"sok",     1,    0},                         // 防手抖开关
    {"pdat",    1,     0},                         // 图片日期标签开关
    {"cyt",     1,    0},                         // 连拍开关
    {"qua",     3,    PHOTO_QUA_HI},              // 图片质量
    {"acu",     8,    PHOTO_ACU_HI},              // 图片锐度
    {"phm",     8,    0},                         // 延时拍照， 单位秒
    {"pres",    6,     PHOTO_RES_1M},              // 图片分辨率
    {"wbl",     4,    PHOTO_WBL_AUTO},            // 白平衡
    {"col",     4,    PHOTO_COLOR_NORMAL},        // 颜色模式
    {"sca",     8,    0},                         // 快速预览时间，单位s
    {"pexp",    8,     0},                         // 曝光设置，范围-3到+3
    {"iso",     8,    0},                         // iso
    {"stk",     8,    0},                         // 大头贴索引
    {"zoom",    8,     10},              // 数字变焦,为了方便传参,实际值除以10

    {"dac",     32,    0x55aa},                         // dac_trim
#ifdef CONFIG_WIFI_ENABLE
    {"rtf",     3,   VIDEO_RES_720P},            //预览前视分辨率
    {"rtb",     3,   VIDEO_RES_VGA},             //预览后视分辨率
    {"wfo",     1,   1},                         //wifi开关
    {"wfmode",  1,      0},                        // wifi运行模式
    {"bvo",     1,   1},                         // 开机音开关
#endif
};

int app_set_config(struct intent *it, const struct app_cfg *cfg, int size)
{
    int i;

    printf("app_set_config: %s, %d\n", it->data, it->exdata);

    for (i = 0; i < size; i++) {
        if (!strcmp(it->data, cfg[i].table)) {
            if (cfg[i].set) {
                int err = cfg[i].set(it->exdata);
                if (err) {
                    return err;
                }
            }
            db_update(cfg[i].table, it->exdata);
            db_flush();
            return 0;
        }
    }

    return -EINVAL;
}


static int app_config_init()
{
    db_create();
    return db_create_table(app_config_table, ARRAY_SIZE(app_config_table));
}
__initcall(app_config_init);



