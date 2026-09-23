#include "app_config.h"
#ifdef CONFIG_UI_STYLE_JL_ENABLE
#include "./lv_i18n.h"

#define UNUSED(x) (void)(x)

static inline uint32_t op_n(int32_t val)
{
    return (uint32_t)(val < 0 ? -val : val);
}
static inline uint32_t op_i(uint32_t val)
{
    return val;
}
// always zero, when decimal part not exists.
static inline uint32_t op_v(uint32_t val)
{
    UNUSED(val);
    return 0;
}
static inline uint32_t op_w(uint32_t val)
{
    UNUSED(val);
    return 0;
}
static inline uint32_t op_f(uint32_t val)
{
    UNUSED(val);
    return 0;
}
static inline uint32_t op_t(uint32_t val)
{
    UNUSED(val);
    return 0;
}

static lv_i18n_phrase_t zh_cn_singulars[] = {
    { "lcdprotect", "屏幕保护", "lv_font_fangsong_16" },
    { "poweroff", "自动关机", "lv_font_fangsong_16" },
    { "frequency", "光源频率", "lv_font_fangsong_16" },
    { "speaker", "按键声音", "lv_font_fangsong_16" },
    { "language", "语言设置", "lv_font_fangsong_16" },
    { "carnum", "车牌号码", "lv_font_fangsong_16" },
    { "roadline", "车道偏移", "lv_font_fangsong_16" },
    { "lamp", "前照灯", "lv_font_fangsong_16" },
    { "formatting", "格式化", "lv_font_fangsong_16" },
    { "reset", "默认设置", "lv_font_fangsong_16" },
    { "close", "关闭", "lv_font_fangsong_16" },
    { "open", "打开", "lv_font_fangsong_16" },
    { "subpagewarning0", "警告\n点击确认删除所有数据", "lv_font_fangsong_24" },
    { "subpagewarning1", "警告\n没有内存卡", "lv_font_fangsong_24" },
    { "subpagewarning2", "警告\n恢复出厂设置", "lv_font_fangsong_24" },
    { "YES", "确认", "lv_font_fangsong_16" },
    { "CANCEL", "取消", "lv_font_fangsong_16" },
    { "date", "日期时间", "lv_font_fangsong_16" },
    { "shoot", "拍摄方式", "lv_font_fangsong_16" },
    { "dealy10s", "定时10秒", "lv_font_fangsong_16" },
    { "dealy5s", "定时5秒", "lv_font_fangsong_16" },
    { "dealy2s", "定时2秒", "lv_font_fangsong_16" },
    { "nodealy", "单拍", "lv_font_fangsong_16" },
    { "standard", "标准", "lv_font_fangsong_16" },
    { "pool", "经济", "lv_font_fangsong_16" },
    { "high", "优质", "lv_font_fangsong_16" },
    { "strong", "强烈", "lv_font_fangsong_16" },
    { "soft", "柔和", "lv_font_fangsong_16" },
    { "mono", "黑白", "lv_font_fangsong_16" },
    { "Nostalgia", "怀旧", "lv_font_fangsong_16" },
    { "acuity", "图像锐度", "lv_font_fangsong_16" },
    { "sunshine", "日光", "lv_font_fangsong_16" },
    { "cloudy", "阴天", "lv_font_fangsong_16" },
    { "fluolamp", "荧光灯", "lv_font_fangsong_16" },
    { "default", "默认", "lv_font_fangsong_16" },
    { "resolution", "分辨率", "lv_font_fangsong_16" },
    { "shots", "连拍", "lv_font_fangsong_16" },
    { "quality", "图像质量", "lv_font_fangsong_16" },
    { "sharpness", "图像锐度", "lv_font_fangsong_16" },
    { "exposure", "曝光补偿", "lv_font_fangsong_16" },
    { "awb", "白平衡", "lv_font_fangsong_16" },
    { "color", "色彩", "lv_font_fangsong_16" },
    { "handshake", "防手抖", "lv_font_fangsong_16" },
    { "preview", "快速预览", "lv_font_fangsong_16" },
    { "doublerec", "双路录像", "lv_font_fangsong_16" },
    { "cycrec", "循环录像", "lv_font_fangsong_16" },
    { "gaprec", "缩时录影", "lv_font_fangsong_16" },
    { "motion", "运动检测", "lv_font_fangsong_16" },
    { "gsensor", "重力感应", "lv_font_fangsong_16" },
    { "record", "录音", "lv_font_fangsong_16" },
    { "guard", "停车守卫", "lv_font_fangsong_16" },
    { "Lsensitive", "低灵敏度", "lv_font_fangsong_16" },
    { "Msensitive", "中灵敏度", "lv_font_fangsong_16" },
    { "Hsensitive", "高灵敏度", "lv_font_fangsong_16" },
    { "tung", "钨丝灯", "lv_font_fangsong_16" },
    { "sysprompt", "准备好了吗~", "lv_font_fangsong_16" },
    { "lowpow", "电量不足", "lv_font_fangsong_16" },
    { "nofile", "没有文件", "lv_font_fangsong_16" },
    { "nosd", "SD卡未插入", "lv_font_fangsong_16" },
    { "nocamera", "摄像头掉线了", "lv_font_fangsong_16" },
    { "fileerr", "文件损坏", "lv_font_fangsong_16" },
    { "format_succ", "格式化成功！", "lv_font_fangsong_16" },
    { "sys_reset", "恢复出厂设置成功！", "lv_font_fangsong_16" },
    { "format_failed", "格式化失败！", "lv_font_fangsong_16" },
    { "sys_reset_failed", "恢复出厂设置失败！", "lv_font_fangsong_16" },
    { "software", "版本号", "lv_font_fangsong_16" },
    { "subpagewarning3", "版本: JL V1.0.0", "lv_font_fangsong_24" },
    { "update_tips", "请勿断电，升级中", "lv_font_fangsong_16" },
    { "line_drift_car", "请移动至车头", "lv_font_fangsong_16" },
    { "line_drift_horizon", "请移动至地平线", "lv_font_fangsong_16" },
    { "cancel", "取消", "lv_font_fangsong_16" },
    { "ensure", "确定", "lv_font_fangsong_16" },
    { "sd_update", "是否进行 SD卡升级？", "lv_font_fangsong_16" },
    { "Mon", "星期一", "lv_font_fangsong_16" },
    { "Tue", "星期二", "lv_font_fangsong_16" },
    { "Wed", "星期三", "lv_font_fangsong_16" },
    { "Thu", "星期四", "lv_font_fangsong_16" },
    { "Fir", "星期五", "lv_font_fangsong_16" },
    { "Sat", "星期六", "lv_font_fangsong_16" },
    { "Sun", "星期日", "lv_font_fangsong_16" },
    { "del_file", "是否删除选中的文件？", "lv_font_fangsong_16" },
    { "lock_file", "是否加锁/解锁选中的文件？", "lv_font_fangsong_16" },
    { "unlock_file", "是否解锁选中的文件？", "lv_font_fangsong_16" },
    { "file_is_lock", "文件已加锁", "lv_font_fangsong_16" },
    { "del_all", "是否删除全部文件？", "lv_font_fangsong_16" },
    { "unlock_all", "是否解锁全部文件？", "lv_font_fangsong_16" },
    { "lock_all", "是否加锁全部文件？", "lv_font_fangsong_16" },
    { "fs_err", "TF卡异常状态", "lv_font_fangsong_16" },
    { "gap_err", "请关闭缩时录影!", "lv_font_fangsong_16" },
    { "being_formatted", "正在格式化中...", "lv_font_fangsong_16" },
    { "sunny", "特晴", "lv_font_FangZhengKaiTiJianTi_1_48" },
    { "wifi_preview", "WIFI预览中", "lv_font_FangZhengKaiTiJianTi_1_22" },
    { "app_connect", "APP已连接", "lv_font_FangZhengKaiTiJianTi_1_22" },
    { "app_disconnect", "APP已断开", "lv_font_FangZhengKaiTiJianTi_1_22" },
    { "lcdprotect_s", "屏保", "lv_font_FangZhengKaiTiJianTi_1_16" },
    { "poweroff_s", "自动关机", "lv_font_FangZhengKaiTiJianTi_1_16" },
    { "frequency_s", "光源频率", "lv_font_FangZhengKaiTiJianTi_1_16" },
    { "speaker_s", "按键声音", "lv_font_FangZhengKaiTiJianTi_1_16" },
    { "language_s", "语言设置", "lv_font_FangZhengKaiTiJianTi_1_16" },
    { "software_s", "软件版本", "lv_font_FangZhengKaiTiJianTi_1_16" },
    { "carnum_s", "车牌号码", "lv_font_FangZhengKaiTiJianTi_1_16" },
    { "roadline_s", "车道偏移", "lv_font_FangZhengKaiTiJianTi_1_16" },
    { "lamp_s", "前照灯", "lv_font_FangZhengKaiTiJianTi_1_16" },
    { "formatting_s", "格式化", "lv_font_FangZhengKaiTiJianTi_1_16" },
    { "reset_s", "默认设置", "lv_font_FangZhengKaiTiJianTi_1_16" },
    { "date_s", "日期时间", "lv_font_FangZhengKaiTiJianTi_1_16" },
    { "close_s", "关闭", "lv_font_fangsong_16" },
    { "open_s", "打开", "lv_font_fangsong_16" },
    { "Simplified_Chinese", "简体中文", "lv_font_fangsong_24" },
    { "funkey4", "preset", "lv_font_fangsong_16" },
    { "funkey5", "preset", "lv_font_fangsong_16" },
    { "funkey6", "preset", "lv_font_fangsong_16" },
    { "funkey7", "preset", "lv_font_fangsong_16" },
    { "suplanguage", "中文", "lv_font_fangsong_16" },
    { "car_record", "行车记录", "lv_font_fangsong_16" },
    { "grellra", "视频相册", "lv_font_fangsong_16" },
    { "sys_setting", "功能设置", "lv_font_fangsong_16" },
    { "wifi", "WIFI", "lv_font_fangsong_16" },
    { "no_open_wifi", "未打开WiFi", "lv_font_fangsong_16" },
    { "click_out", "点击任意地方退出", "lv_font_fangsong_16" },
    { "setting_title", "·系统设置·", "lv_font_fangsong_16" },
    { "menu_wifi", "WIFI", "lv_font_fangsong_16" },
    { "wait", "请稍候...", "lv_font_fangsong_16" },
    { "min1", "1分钟", "lv_font_fangsong_16" },
    { "min3", "3分钟", "lv_font_fangsong_16" },
    { "min10", "10分钟", "lv_font_fangsong_16" },
    { "date_label", "日期标签", "lv_font_fangsong_16" },
    { "car_set", "车牌设置", "lv_font_fangsong_16" },
    { "back_insert", "未检测到后路", "lv_font_fangsong_16" },
    { "roller_select", "请按模式和菜单按键上下选择", "lv_font_fangsong_16" },
    { "off_10_sec", "机器将在10秒后关机", "lv_font_fangsong_16" },
    { "voi_num", "设备音量", "lv_font_fangsong_16" },
    { "sub_low", "低", "lv_font_fangsong_16" },
    { "sub_middle", "中", "lv_font_fangsong_16" },
    { "sub_high", "高", "lv_font_fangsong_16" },
    { "min5", "5分钟", "lv_font_fangsong_16" },
    { "menu_hdr", "高动态范围", "lv_font_fangsong_16" },
    { "lan_russin", "русск", "lv_font_fangsong_16" },
    { "lcdprotect_p", "·屏幕保护·", "lv_font_fangsong_16" },
    { "poweroff_p", "·自动关机·", "lv_font_fangsong_16" },
    { "frequency_p", "·光源频率·", "lv_font_fangsong_16" },
    { "speaker_p", "·按键声音·", "lv_font_fangsong_16" },
    { "language_p", "·语言设置·", "lv_font_fangsong_16" },
    { "software_p", "·版本号·", "lv_font_fangsong_16" },
    { "carnum_p", "·车牌号码·", "lv_font_fangsong_16" },
    { "roadline_p", "·车道偏移·", "lv_font_fangsong_16" },
    { "lamp_p", "·前照灯·", "lv_font_fangsong_16" },
    { "formatting_p", "·格式化·", "lv_font_fangsong_16" },
    { "reset_p", "·默认设置·", "lv_font_fangsong_16" },
    { "date_p", "·日期时间·", "lv_font_fangsong_16" },
    { "close_p", "·关闭", "lv_font_fangsong_16" },
    { "open_p", "·打开", "lv_font_fangsong_16" },
    { "min1_p", "·1分钟·", "lv_font_fangsong_16" },
    { "min3_p", "·3分钟·", "lv_font_fangsong_16" },
    { "min10_p", "·10分钟·", "lv_font_fangsong_16" },
    { "date_label_p", "·日期标签·", "lv_font_fangsong_16" },
    { "car_set_p", "·车牌设置·", "lv_font_fangsong_16" },
    { "shoot_p", "·拍摄方式·", "lv_font_fangsong_16" },
    { "resolution_p", "·分辨率·", "lv_font_fangsong_16" },
    { "shots_p", "·连拍·", "lv_font_fangsong_16" },
    { "quality_p", "·图像质量·", "lv_font_fangsong_16" },
    { "sharpness_p", "·图像锐度·", "lv_font_fangsong_16" },
    { "awb_p", "·白平衡·", "lv_font_fangsong_16" },
    { "color_p", "·色彩·", "lv_font_fangsong_16" },
    { "exposure_p", "·曝光补偿·", "lv_font_fangsong_16" },
    { "handshake_p", "·防手抖·", "lv_font_fangsong_16" },
    { "preview_p", "·快速预览·", "lv_font_fangsong_16" },
    { "doublerec_p", "·双路录像·", "lv_font_fangsong_16" },
    { "cycrec_p", "·循环录像·", "lv_font_fangsong_16" },
    { "gaprec_p", "·缩时录影·", "lv_font_fangsong_16" },
    { "motion_p", "·运动检测·", "lv_font_fangsong_16" },
    { "gsensor_p", "·重力感应·", "lv_font_fangsong_16" },
    { "record_p", "·录音·", "lv_font_fangsong_16" },
    { "guard_p", "·停车守卫·", "lv_font_fangsong_16" },
    { "menu_hdr_p", "·高动态范围·", "lv_font_fangsong_16" },
    { NULL, NULL, NULL }
};

static lv_i18n_phrase_t zh_cn_plurals_other[] = {

    { NULL, NULL, NULL }
};

static uint8_t zh_cn_plural_fn(int32_t num)
{
    uint32_t n = op_n(num);
    UNUSED(n);
    uint32_t i = op_i(n);
    UNUSED(i);
    uint32_t v = op_v(n);
    UNUSED(v);

    if ((i == 1 && v == 0)) {
        return LV_I18N_PLURAL_TYPE_ONE;
    }
    return LV_I18N_PLURAL_TYPE_OTHER;
}

static const lv_i18n_lang_t zh_cn_lang = {
    .locale_name = "zh_cn",
    .singulars = zh_cn_singulars,
    .plurals[LV_I18N_PLURAL_TYPE_OTHER] = zh_cn_plurals_other,
    .locale_plural_fn = zh_cn_plural_fn
};
static lv_i18n_phrase_t zh_hk_singulars[] = {
    { "funkey4", "preset", "lv_font_fangsong_16" },
    { "funkey5", "preset", "lv_font_fangsong_16" },
    { "funkey6", "preset", "lv_font_fangsong_16" },
    { "funkey7", "preset", "lv_font_fangsong_16" },
    { "suplanguage", "繁體中文", "lv_font_fangsong_16" },
    { "lcdprotect", "屏幕保護", "lv_font_fangsong_16" },
    { "poweroff", "自動關機", "lv_font_fangsong_16" },
    { "frequency", "光源頻率", "lv_font_fangsong_16" },
    { "speaker", "按鍵聲音", "lv_font_fangsong_16" },
    { "language", "語言設置", "lv_font_fangsong_16" },
    { "software", "版本號", "lv_font_fangsong_16" },
    { "carnum", "車牌號碼", "lv_font_fangsong_16" },
    { "roadline", "車道偏移", "lv_font_fangsong_16" },
    { "lamp", "前照燈", "lv_font_fangsong_16" },
    { "formatting", "格式化", "lv_font_fangsong_16" },
    { "reset", "預設設置", "lv_font_fangsong_16" },
    { "date", "日期時間", "lv_font_fangsong_16" },
    { "close", "關閉", "lv_font_fangsong_16" },
    { "open", "打開", "lv_font_fangsong_16" },
    { "subpagewarning0", "警告\n點擊確認刪除所有數據", "lv_font_fangsong_24" },
    { "subpagewarning1", "警告\n沒有內存卡", "lv_font_fangsong_24" },
    { "subpagewarning2", "警告\n恢復出廠設置", "lv_font_fangsong_24" },
    { "YES", "確認", "lv_font_fangsong_16" },
    { "CANCEL", "取消", "lv_font_fangsong_16" },
    { "shoot", "拍攝方式", "lv_font_fangsong_16" },
    { "dealy10s", "定時10秒", "lv_font_fangsong_16" },
    { "dealy5s", "定時5秒", "lv_font_fangsong_16" },
    { "dealy2s", "定時2秒", "lv_font_fangsong_16" },
    { "nodealy", "單拍", "lv_font_fangsong_16" },
    { "standard", "標準", "lv_font_fangsong_16" },
    { "pool", "經濟", "lv_font_fangsong_16" },
    { "high", "優質", "lv_font_fangsong_16" },
    { "strong", "強烈", "lv_font_fangsong_16" },
    { "soft", "柔和", "lv_font_fangsong_16" },
    { "mono", "黑白", "lv_font_fangsong_16" },
    { "Nostalgia", "懷舊", "lv_font_fangsong_16" },
    { "acuity", "圖像銳度", "lv_font_fangsong_16" },
    { "sunshine", "日光", "lv_font_fangsong_16" },
    { "cloudy", "陰天", "lv_font_fangsong_16" },
    { "fluolamp", "螢光燈", "lv_font_fangsong_16" },
    { "default", "預設", "lv_font_fangsong_16" },
    { "resolution", "分辨率", "lv_font_fangsong_16" },
    { "shots", "連拍", "lv_font_fangsong_16" },
    { "quality", "圖像質量", "lv_font_fangsong_16" },
    { "sharpness", "圖像銳度", "lv_font_fangsong_16" },
    { "awb", "白平衡", "lv_font_fangsong_16" },
    { "color", "色彩", "lv_font_fangsong_16" },
    { "exposure", "曝光補償", "lv_font_fangsong_16" },
    { "handshake", "防手抖", "lv_font_fangsong_16" },
    { "preview", "快速預覽", "lv_font_fangsong_16" },
    { "doublerec", "雙路錄像", "lv_font_fangsong_16" },
    { "cycrec", "循環錄像", "lv_font_fangsong_16" },
    { "gaprec", "縮時錄影", "lv_font_fangsong_16" },
    { "motion", "運動檢測", "lv_font_fangsong_16" },
    { "gsensor", "重力感應", "lv_font_fangsong_16" },
    { "record", "錄音", "lv_font_fangsong_16" },
    { "guard", "停車守衛", "lv_font_fangsong_16" },
    { "Lsensitive", "低靈敏度", "lv_font_fangsong_16" },
    { "Msensitive", "中靈敏度", "lv_font_fangsong_16" },
    { "Hsensitive", "高靈敏度", "lv_font_fangsong_16" },
    { "tung", "鎢絲燈", "lv_font_fangsong_16" },
    { "sysprompt", "準備好了嗎~", "lv_font_fangsong_16" },
    { "lowpow", "電量不足", "lv_font_fangsong_16" },
    { "nofile", "沒有文件", "lv_font_fangsong_16" },
    { "nosd", "SD卡未插入", "lv_font_fangsong_16" },
    { "nocamera", "攝像頭斷線了", "lv_font_fangsong_16" },
    { "fileerr", "文件損壞", "lv_font_fangsong_16" },
    { "format_succ", "格式化成功！", "lv_font_fangsong_16" },
    { "sys_reset", "恢復出廠設置成功！", "lv_font_fangsong_16" },
    { "format_failed", "格式化失敗！", "lv_font_fangsong_16" },
    { "sys_reset_failed", "恢復出廠設置失敗！", "lv_font_fangsong_16" },
    { "subpagewarning3", "版本: JL V1.0.0", "lv_font_fangsong_24" },
    { "update_tips", "請勿斷電，升級中", "lv_font_fangsong_16" },
    { "line_drift_horizon", "請移動至地平線", "lv_font_fangsong_16" },
    { "line_drift_car", "請移動至車頭", "lv_font_fangsong_16" },
    { "cancel", "取消", "lv_font_fangsong_16" },
    { "ensure", "確定", "lv_font_fangsong_16" },
    { "sd_update", "是否進行 SD卡升級？", "lv_font_fangsong_16" },
    { "Mon", "星期一", "lv_font_fangsong_16" },
    { "Tue", "星期二", "lv_font_fangsong_16" },
    { "Wed", "星期三", "lv_font_fangsong_16" },
    { "Thu", "星期四", "lv_font_fangsong_16" },
    { "Fir", "星期五", "lv_font_fangsong_16" },
    { "Sat", "星期六", "lv_font_fangsong_16" },
    { "Sun", "星期日", "lv_font_fangsong_16" },
    { "del_file", "是否刪除選中的文件？", "lv_font_fangsong_16" },
    { "lock_file", "是否加鎖/解鎖選中的文件？", "lv_font_fangsong_16" },
    { "unlock_file", "是否解鎖選中的文件？", "lv_font_fangsong_16" },
    { "unlock_all", "是否解鎖全部文件？", "lv_font_fangsong_16" },
    { "file_is_lock", "文件已加鎖", "lv_font_fangsong_16" },
    { "del_all", "是否刪除全部文件？", "lv_font_fangsong_16" },
    { "lock_all", "是否加鎖全部文件？", "lv_font_fangsong_16" },
    { "fs_err", "TF卡異常狀態", "lv_font_fangsong_16" },
    { "gap_err", "請關閉縮時錄影!", "lv_font_fangsong_16" },
    { "being_formatted", "正在格式化中...", "lv_font_fangsong_16" },
    { "car_record", "行車記錄", "lv_font_fangsong_16" },
    { "grellra", "視頻相冊", "lv_font_fangsong_16" },
    { "sys_setting", "功能設置", "lv_font_fangsong_16" },
    { "wifi", "WIFI", "lv_font_fangsong_16" },
    { "no_open_wifi", "未打開WiFi", "lv_font_fangsong_16" },
    { "click_out", "點擊任意地方退出", "lv_font_fangsong_16" },
    { "setting_title", "·系統設置·", "lv_font_fangsong_16" },
    { "menu_wifi", "WIFI", "lv_font_fangsong_16" },
    { "wait", "請稍候...", "lv_font_fangsong_16" },
    { "min1", "1分鐘", "lv_font_fangsong_16" },
    { "min3", "3分鐘", "lv_font_fangsong_16" },
    { "min10", "10分鐘", "lv_font_fangsong_16" },
    { "date_label", "日期標籤", "lv_font_fangsong_16" },
    { "car_set", "車牌設置", "lv_font_fangsong_16" },
    { "back_insert", "未檢測到後路", "lv_font_fangsong_16" },
    { "roller_select", "請按模式和菜單按鍵上下選擇", "lv_font_fangsong_16" },
    { "off_10_sec", "機器將在10秒後關機", "lv_font_fangsong_16" },
    { "voi_num", "設備音量", "lv_font_fangsong_16" },
    { "sub_low", "低", "lv_font_fangsong_16" },
    { "sub_middle", "中", "lv_font_fangsong_16" },
    { "sub_high", "高", "lv_font_fangsong_16" },
    { "min5", "5分鐘", "lv_font_fangsong_16" },
    { "menu_hdr", "高動態範圍", "lv_font_fangsong_16" },
    { "lan_russin", "русск", "lv_font_fangsong_16" },
    { "lcdprotect_p", "·屏幕保護·", "lv_font_fangsong_16" },
    { "poweroff_p", "·自動關機·", "lv_font_fangsong_16" },
    { "frequency_p", "·光源頻率·", "lv_font_fangsong_16" },
    { "speaker_p", "·按鍵聲音·", "lv_font_fangsong_16" },
    { "language_p", "·語言設置·", "lv_font_fangsong_16" },
    { "software_p", "·版本號·", "lv_font_fangsong_16" },
    { "carnum_p", "·車牌號碼·", "lv_font_fangsong_16" },
    { "roadline_p", "·車道偏移·", "lv_font_fangsong_16" },
    { "lamp_p", "·前照燈·", "lv_font_fangsong_16" },
    { "formatting_p", "·格式化·", "lv_font_fangsong_16" },
    { "reset_p", "·預設設置·", "lv_font_fangsong_16" },
    { "date_p", "·日期時間·", "lv_font_fangsong_16" },
    { "close_p", "·關閉", "lv_font_fangsong_16" },
    { "open_p", "·打開", "lv_font_fangsong_16" },
    { "min1_p", "·1分鐘·", "lv_font_fangsong_16" },
    { "min3_p", "·3分鐘·", "lv_font_fangsong_16" },
    { "min10_p", "·10分鐘·", "lv_font_fangsong_16" },
    { "date_label_p", "·日期標籤·", "lv_font_fangsong_16" },
    { "car_set_p", "·車牌設置·", "lv_font_fangsong_16" },
    { "shoot_p", "·拍攝方式·", "lv_font_fangsong_16" },
    { "resolution_p", "·分辨率·", "lv_font_fangsong_16" },
    { "shots_p", "·連拍·", "lv_font_fangsong_16" },
    { "quality_p", "·圖像質量·", "lv_font_fangsong_16" },
    { "sharpness_p", "·圖像銳度·", "lv_font_fangsong_16" },
    { "awb_p", "·白平衡·", "lv_font_fangsong_16" },
    { "color_p", "·色彩·", "lv_font_fangsong_16" },
    { "exposure_p", "·曝光補償·", "lv_font_fangsong_16" },
    { "handshake_p", "·防手抖·", "lv_font_fangsong_16" },
    { "preview_p", "·快速預覽·", "lv_font_fangsong_16" },
    { "doublerec_p", "·雙路錄像·", "lv_font_fangsong_16" },
    { "cycrec_p", "·循環錄像·", "lv_font_fangsong_16" },
    { "gaprec_p", "·縮時錄影·", "lv_font_fangsong_16" },
    { "motion_p", "·運動檢測·", "lv_font_fangsong_16" },
    { "gsensor_p", "·重力感應·", "lv_font_fangsong_16" },
    { "record_p", "·錄音·", "lv_font_fangsong_16" },
    { "guard_p", "·停車守衛·", "lv_font_fangsong_16" },
    { "menu_hdr_p", "·高動態範圍·", "lv_font_fangsong_16" },
    { NULL, NULL, NULL }
};

static lv_i18n_phrase_t zh_hk_plurals_other[] = {

    { NULL, NULL, NULL }
};

static uint8_t zh_hk_plural_fn(int32_t num)
{
    uint32_t n = op_n(num);
    UNUSED(n);
    uint32_t i = op_i(n);
    UNUSED(i);
    uint32_t v = op_v(n);
    UNUSED(v);

    if ((i == 1 && v == 0)) {
        return LV_I18N_PLURAL_TYPE_ONE;
    }
    return LV_I18N_PLURAL_TYPE_OTHER;
}

static const lv_i18n_lang_t zh_hk_lang = {
    .locale_name = "zh_hk",
    .singulars = zh_hk_singulars,
    .plurals[LV_I18N_PLURAL_TYPE_OTHER] = zh_hk_plurals_other,
    .locale_plural_fn = zh_hk_plural_fn
};
static lv_i18n_phrase_t en_singulars[] = {
    { "lcdprotect", "Screensaver", "lv_font_timesnewromanpsmt_16" },
    { "poweroff", "Auto Shutdown", "lv_font_timesnewromanpsmt_16" },
    { "frequency", "Frequency", "lv_font_timesnewromanpsmt_16" },
    { "reset", "Default", "lv_font_timesnewromanpsmt_16" },
    { "formatting", "Formatting", "lv_font_timesnewromanpsmt_16" },
    { "lamp", "Headlamp", "lv_font_timesnewromanpsmt_16" },
    { "roadline", "Lane drift", "lv_font_timesnewromanpsmt_16" },
    { "carnum", "License plate", "lv_font_timesnewromanpsmt_16" },
    { "language", "Language", "lv_font_timesnewromanpsmt_16" },
    { "speaker", "Keying Tone", "lv_font_timesnewromanpsmt_16" },
    { "close", "close", "lv_font_timesnewromanpsmt_16" },
    { "open", "open", "lv_font_timesnewromanpsmt_16" },
    { "subpagewarning0", "Warning\n Click to confirm deletion of all data", "lv_font_timesnewromanpsmt_24" },
    { "subpagewarning1", "Warning\n No memory card", "lv_font_timesnewromanpsmt_24" },
    { "subpagewarning2", "Warning\n Restore factory settings", "lv_font_timesnewromanpsmt_24" },
    { "YES", "YES", "lv_font_timesnewromanpsmt_16" },
    { "CANCEL", "CANCEL", "lv_font_timesnewromanpsmt_16" },
    { "date", "Date", "lv_font_timesnewromanpsmt_16" },
    { "shoot", "Shooting Method", "lv_font_timesnewromanpsmt_16" },
    { "dealy10s", "timing 10s", "lv_font_timesnewromanpsmt_16" },
    { "dealy5s", "timing 5s", "lv_font_timesnewromanpsmt_16" },
    { "dealy2s", "timing 2s", "lv_font_timesnewromanpsmt_16" },
    { "nodealy", "Single Shot", "lv_font_timesnewromanpsmt_16" },
    { "standard", "standard", "lv_font_timesnewromanpsmt_16" },
    { "pool", "pool", "lv_font_timesnewromanpsmt_16" },
    { "high", "high quality", "lv_font_timesnewromanpsmt_16" },
    { "strong", "strong", "lv_font_timesnewromanpsmt_16" },
    { "soft", "soft", "lv_font_timesnewromanpsmt_16" },
    { "mono", "black and white", "lv_font_timesnewromanpsmt_16" },
    { "Nostalgia", "Nostalgia", "lv_font_timesnewromanpsmt_16" },
    { "acuity", "Acuity", "lv_font_timesnewromanpsmt_16" },
    { "sunshine", "sunshine", "lv_font_timesnewromanpsmt_16" },
    { "cloudy", "cloudy", "lv_font_timesnewromanpsmt_16" },
    { "fluolamp", "fluorescent", "lv_font_timesnewromanpsmt_16" },
    { "default", "Default", "lv_font_timesnewromanpsmt_16" },
    { "resolution", "Resolution", "lv_font_timesnewromanpsmt_16" },
    { "shots", "Shots", "lv_font_timesnewromanpsmt_16" },
    { "quality", "Image Quality", "lv_font_timesnewromanpsmt_16" },
    { "sharpness", "Sharpness", "lv_font_timesnewromanpsmt_16" },
    { "exposure", "Exposure", "lv_font_timesnewromanpsmt_16" },
    { "awb", "AWB", "lv_font_timesnewromanpsmt_16" },
    { "color", "COLOR", "lv_font_timesnewromanpsmt_16" },
    { "handshake", "Handshake", "lv_font_timesnewromanpsmt_16" },
    { "preview", "Preview", "lv_font_timesnewromanpsmt_16" },
    { "guard", "Parking", "lv_font_timesnewromanpsmt_16" },
    { "record", "Sound", "lv_font_timesnewromanpsmt_16" },
    { "gsensor", "Gravity", "lv_font_timesnewromanpsmt_16" },
    { "motion", "Motion", "lv_font_timesnewromanpsmt_16" },
    { "gaprec", "Interval recording", "lv_font_timesnewromanpsmt_16" },
    { "doublerec", "Dual channel recording", "lv_font_timesnewromanpsmt_16" },
    { "cycrec", "Cycle", "lv_font_timesnewromanpsmt_16" },
    { "Lsensitive", "Low sensitive", "lv_font_timesnewromanpsmt_16" },
    { "Msensitive", "middle sensitive", "lv_font_timesnewromanpsmt_16" },
    { "Hsensitive", "high sensitive", "lv_font_timesnewromanpsmt_16" },
    { "tung", "Tungsten lamp", "lv_font_timesnewromanpsmt_16" },
    { "sysprompt", "are you ready~", "lv_font_timesnewromanpsmt_16" },
    { "lowpow", "low battery", "lv_font_timesnewromanpsmt_16" },
    { "nofile", "no file", "lv_font_timesnewromanpsmt_16" },
    { "nosd", "no sd card", "lv_font_timesnewromanpsmt_16" },
    { "nocamera", "camera lost", "lv_font_timesnewromanpsmt_16" },
    { "fileerr", "file err", "lv_font_timesnewromanpsmt_16" },
    { "format_succ", "format successfully!", "lv_font_timesnewromanpsmt_16" },
    { "sys_reset", "system reset successfully!", "lv_font_timesnewromanpsmt_16" },
    { "format_failed", "format failed!", "lv_font_timesnewromanpsmt_16" },
    { "sys_reset_failed", "system reset failed!", "lv_font_timesnewromanpsmt_16" },
    { "software", "Version", "lv_font_timesnewromanpsmt_16" },
    { "subpagewarning3", "Version: JL V1.0.0", "lv_font_timesnewromanpsmt_24" },
    { "update_tips", "Do not power off, upgrade", "lv_font_timesnewromanpsmt_16" },
    { "line_drift_car", "Please move to the front", "lv_font_timesnewromanpsmt_16" },
    { "line_drift_horizon", "Please move to the horizon", "lv_font_timesnewromanpsmt_16" },
    { "cancel", "cancel", "lv_font_timesnewromanpsmt_16" },
    { "ensure", "ensure", "lv_font_timesnewromanpsmt_16" },
    { "sd_update", "Whether to upgrade the SD card?", "lv_font_timesnewromanpsmt_16" },
    { "Mon", "Monday", "lv_font_timesnewromanpsmt_16" },
    { "Tue", "Tuesday", "lv_font_timesnewromanpsmt_16" },
    { "Wed", "Wednesday", "lv_font_timesnewromanpsmt_16" },
    { "Thu", "Thursday", "lv_font_timesnewromanpsmt_16" },
    { "Fir", "Firday", "lv_font_timesnewromanpsmt_16" },
    { "Sat", "Saturday", "lv_font_timesnewromanpsmt_16" },
    { "Sun", "Sunday", "lv_font_timesnewromanpsmt_16" },
    { "del_file", "Do you want to delete the selected file?", "lv_font_timesnewromanpsmt_16" },
    { "lock_file", "Do you want to lock/unlock the selected file?", "lv_font_timesnewromanpsmt_16" },
    { "unlock_file", "Do you want to unlock the selected file?", "lv_font_timesnewromanpsmt_16" },
    { "file_is_lock", "The file is locked!", "lv_font_timesnewromanpsmt_16" },
    { "del_all", "Do you want to delete all files?", "lv_font_timesnewromanpsmt_16" },
    { "unlock_all", "Do you want to unlock all files?", "lv_font_timesnewromanpsmt_16" },
    { "lock_all", "Do you want to lock all files?", "lv_font_timesnewromanpsmt_16" },
    { "fs_err", "The TF card is abnormal!", "lv_font_timesnewromanpsmt_16" },
    { "gap_err", "Please turn off the time-lapse recording!", "lv_font_timesnewromanpsmt_16" },
    { "being_formatted", "Being formatted...", "lv_font_timesnewromanpsmt_16" },
    { "sunny", "sunny", "lv_font_timesnewromanpsmt_48" },
    { "wifi_preview", "WIFI Preview", "lv_font_timesnewromanpsmt_22" },
    { "app_connect", "APP is connected!", "lv_font_timesnewromanpsmt_22" },
    { "app_disconnect", "APP is disconnected!", "lv_font_timesnewromanpsmt_22" },
    { "lcdprotect_s", "screensaver", "lv_font_timesnewromanpsmt_16" },
    { "poweroff_s", "auto shutdown", "lv_font_timesnewromanpsmt_16" },
    { "frequency_s", "frequency", "lv_font_timesnewromanpsmt_16" },
    { "speaker_s", "keying tone", "lv_font_timesnewromanpsmt_16" },
    { "language_s", "language", "lv_font_timesnewromanpsmt_16" },
    { "software_s", "software version", "lv_font_timesnewromanpsmt_16" },
    { "carnum_s", "License plate", "lv_font_timesnewromanpsmt_16" },
    { "roadline_s", "Lane drift", "lv_font_timesnewromanpsmt_16" },
    { "lamp_s", "headlamp", "lv_font_timesnewromanpsmt_16" },
    { "formatting_s", "formatting", "lv_font_timesnewromanpsmt_16" },
    { "reset_s", "default setting", "lv_font_timesnewromanpsmt_16" },
    { "date_s", "date", "lv_font_timesnewromanpsmt_16" },
    { "close_s", "close", "lv_font_timesnewromanpsmt_16" },
    { "open_s", "open", "lv_font_timesnewromanpsmt_16" },
    { "Simplified_Chinese", "Chinese", "lv_font_timesnewromanpsmt_24" },
    { "funkey4", "preset", "lv_font_timesnewromanpsmt_16" },
    { "funkey5", "preset", "lv_font_timesnewromanpsmt_16" },
    { "funkey6", "preset", "lv_font_timesnewromanpsmt_16" },
    { "funkey7", "preset", "lv_font_timesnewromanpsmt_16" },
    { "suplanguage", "English", "lv_font_timesnewromanpsmt_16" },
    { "car_record", "RECORD", "lv_font_timesnewromanpsmt_16" },
    { "grellra", "FILES", "lv_font_timesnewromanpsmt_16" },
    { "sys_setting", "SETTINGS", "lv_font_timesnewromanpsmt_16" },
    { "wifi", "WIFI", "lv_font_timesnewromanpsmt_16" },
    { "no_open_wifi", "Not to open the wifi", "lv_font_timesnewromanpsmt_16" },
    { "click_out", "Click anywhere to exit", "lv_font_timesnewromanpsmt_16" },
    { "setting_title", "·System Settings·", "lv_font_timesnewromanpsmt_16" },
    { "menu_wifi", "WIFI", "lv_font_timesnewromanpsmt_16" },
    { "wait", "Wait...", "lv_font_timesnewromanpsmt_16" },
    { "min1", "1 Min", "lv_font_timesnewromanpsmt_16" },
    { "min3", "3 Min", "lv_font_timesnewromanpsmt_16" },
    { "min10", "10 Min", "lv_font_timesnewromanpsmt_16" },
    { "date_label", "Label", "lv_font_timesnewromanpsmt_16" },
    { "car_set", "Car setting", "lv_font_timesnewromanpsmt_16" },
    { "back_insert", "No back path detected", "lv_font_timesnewromanpsmt_16" },
    { "roller_select", "Please press the Mode and menu buttons to select up or down", "lv_font_timesnewromanpsmt_16" },
    { "off_10_sec", "Shutdown in 10 seconds", "lv_font_timesnewromanpsmt_16" },
    { "voi_num", "Audio", "lv_font_timesnewromanpsmt_16" },
    { "sub_low", "low", "lv_font_timesnewromanpsmt_16" },
    { "sub_middle", "middle", "lv_font_timesnewromanpsmt_16" },
    { "sub_high", "high", "lv_font_timesnewromanpsmt_16" },
    { "min5", "5 Min", "lv_font_timesnewromanpsmt_16" },
    { "menu_hdr", "HDR", "lv_font_timesnewromanpsmt_16" },
    { "lan_russin", "русск", "lv_font_timesnewromanpsmt_16" },
    { "lcdprotect_p", "·Screensaver·", "lv_font_timesnewromanpsmt_16" },
    { "poweroff_p", "·Auto Shutdown·", "lv_font_timesnewromanpsmt_16" },
    { "frequency_p", "·Frequency·", "lv_font_timesnewromanpsmt_16" },
    { "speaker_p", "·Keying Tone·", "lv_font_timesnewromanpsmt_16" },
    { "language_p", "·Language·", "lv_font_timesnewromanpsmt_16" },
    { "software_p", "·Version·", "lv_font_timesnewromanpsmt_16" },
    { "carnum_p", "·License plate·", "lv_font_timesnewromanpsmt_16" },
    { "roadline_p", "·Lane drift·", "lv_font_timesnewromanpsmt_16" },
    { "lamp_p", "·Headlamp·", "lv_font_timesnewromanpsmt_16" },
    { "formatting_p", "·Formatting·", "lv_font_timesnewromanpsmt_16" },
    { "reset_p", "·Default·", "lv_font_timesnewromanpsmt_16" },
    { "date_p", "·Date·", "lv_font_timesnewromanpsmt_16" },
    { "close_p", "·close", "lv_font_timesnewromanpsmt_16" },
    { "open_p", "·open", "lv_font_timesnewromanpsmt_16" },
    { "min1_p", "·1 Min", "lv_font_timesnewromanpsmt_16" },
    { "min3_p", "·3 Min", "lv_font_timesnewromanpsmt_16" },
    { "min10_p", "·10 Min", "lv_font_timesnewromanpsmt_16" },
    { "date_label_p", "·Label·", "lv_font_timesnewromanpsmt_16" },
    { "car_set_p", "·Car setting·", "lv_font_timesnewromanpsmt_16" },
    { "shoot_p", "·Shooting Method·", "lv_font_timesnewromanpsmt_16" },
    { "resolution_p", "·Resolution·", "lv_font_timesnewromanpsmt_16" },
    { "shots_p", "·Shots·", "lv_font_timesnewromanpsmt_16" },
    { "quality_p", "·Image Quality·", "lv_font_timesnewromanpsmt_16" },
    { "sharpness_p", "·Sharpness·", "lv_font_timesnewromanpsmt_16" },
    { "awb_p", "·AWB·", "lv_font_timesnewromanpsmt_16" },
    { "color_p", "·COLOR·", "lv_font_timesnewromanpsmt_16" },
    { "exposure_p", "·Exposure·", "lv_font_timesnewromanpsmt_16" },
    { "handshake_p", "·Handshake·", "lv_font_timesnewromanpsmt_16" },
    { "preview_p", "·Preview·", "lv_font_timesnewromanpsmt_16" },
    { "doublerec_p", "·Dual channel recording·", "lv_font_timesnewromanpsmt_16" },
    { "cycrec_p", "·Cycle·", "lv_font_timesnewromanpsmt_16" },
    { "gaprec_p", "·Interval recording·", "lv_font_timesnewromanpsmt_16" },
    { "motion_p", "·Motion·", "lv_font_timesnewromanpsmt_16" },
    { "gsensor_p", "·Gravity·", "lv_font_timesnewromanpsmt_16" },
    { "record_p", "·Sound·", "lv_font_timesnewromanpsmt_16" },
    { "guard_p", "·Parking·", "lv_font_timesnewromanpsmt_16" },
    { "menu_hdr_p", "·HDR·", "lv_font_timesnewromanpsmt_16" },
    { NULL, NULL, NULL }
};

static lv_i18n_phrase_t en_plurals_other[] = {

    { NULL, NULL, NULL }
};

static uint8_t en_plural_fn(int32_t num)
{
    uint32_t n = op_n(num);
    UNUSED(n);
    uint32_t i = op_i(n);
    UNUSED(i);
    uint32_t v = op_v(n);
    UNUSED(v);

    if ((i == 1 && v == 0)) {
        return LV_I18N_PLURAL_TYPE_ONE;
    }
    return LV_I18N_PLURAL_TYPE_OTHER;
}

static const lv_i18n_lang_t en_lang = {
    .locale_name = "en",
    .singulars = en_singulars,
    .plurals[LV_I18N_PLURAL_TYPE_OTHER] = en_plurals_other,
    .locale_plural_fn = en_plural_fn
};
static lv_i18n_phrase_t ru_singulars[] = {
    { "funkey4", "preset", "lv_font_timesnewromanpsmt_16" },
    { "funkey5", "preset", "lv_font_timesnewromanpsmt_16" },
    { "funkey6", "preset", "lv_font_timesnewromanpsmt_16" },
    { "funkey7", "preset", "lv_font_timesnewromanpsmt_16" },
    { "suplanguage", "Русский язык", "lv_font_timesnewromanpsmt_16" },
    { "lcdprotect", "Защита экрана.", "lv_font_timesnewromanpsmt_16" },
    { "poweroff", "Автоматический выключение", "lv_font_timesnewromanpsmt_16" },
    { "frequency", "Частота источника света", "lv_font_timesnewromanpsmt_16" },
    { "speaker", "Нажми на кнопку.", "lv_font_timesnewromanpsmt_16" },
    { "language", "Настройка языка", "lv_font_timesnewromanpsmt_16" },
    { "software", "Номер версии.", "lv_font_timesnewromanpsmt_16" },
    { "carnum", "Номер машины.", "lv_font_timesnewromanpsmt_16" },
    { "roadline", "Сдвиг полосы.", "lv_font_timesnewromanpsmt_16" },
    { "lamp", "Фары!", "lv_font_timesnewromanpsmt_16" },
    { "formatting", "Форматирование.", "lv_font_timesnewromanpsmt_16" },
    { "reset", "Настройка по умолчанию", "lv_font_timesnewromanpsmt_16" },
    { "date", "Дата, время.", "lv_font_timesnewromanpsmt_16" },
    { "close", "закр", "lv_font_timesnewromanpsmt_16" },
    { "open", "откр", "lv_font_timesnewromanpsmt_16" },
    { "subpagewarning0", "Предупреждение \n подтверждает удаление всех данных", "lv_font_timesnewromanpsmt_24" },
    { "subpagewarning1", "Предупреждай \n, что у него нет карточки", "lv_font_timesnewromanpsmt_24" },
    { "subpagewarning2", "Предупредите \n восстановить заводские настройки", "lv_font_timesnewromanpsmt_24" },
    { "YES", "подтверд", "lv_font_timesnewromanpsmt_16" },
    { "CANCEL", "отмен", "lv_font_timesnewromanpsmt_16" },
    { "shoot", "Способ съемки.", "lv_font_timesnewromanpsmt_16" },
    { "dealy10s", "10 секунд.", "lv_font_timesnewromanpsmt_16" },
    { "dealy5s", "5 секунд.", "lv_font_timesnewromanpsmt_16" },
    { "dealy2s", "2 секунды.", "lv_font_timesnewromanpsmt_16" },
    { "nodealy", "Одиночн удар", "lv_font_timesnewromanpsmt_16" },
    { "standard", "стандартн", "lv_font_timesnewromanpsmt_16" },
    { "pool", "экономическ", "lv_font_timesnewromanpsmt_16" },
    { "high", "качествен", "lv_font_timesnewromanpsmt_16" },
    { "strong", "сильн", "lv_font_timesnewromanpsmt_16" },
    { "soft", "мягк", "lv_font_timesnewromanpsmt_16" },
    { "mono", "Черн-бел", "lv_font_timesnewromanpsmt_16" },
    { "Nostalgia", "ностальг", "lv_font_timesnewromanpsmt_16" },
    { "acuity", "Острота изображения", "lv_font_timesnewromanpsmt_16" },
    { "sunshine", "Дневн свет", "lv_font_timesnewromanpsmt_16" },
    { "cloudy", "облачн", "lv_font_timesnewromanpsmt_16" },
    { "fluolamp", "Флуоресцентная лампа", "lv_font_timesnewromanpsmt_16" },
    { "default", "По умолчан", "lv_font_timesnewromanpsmt_16" },
    { "resolution", "Разрешающая способность", "lv_font_timesnewromanpsmt_16" },
    { "shots", "Даж снима", "lv_font_timesnewromanpsmt_16" },
    { "quality", "Качество изображения", "lv_font_timesnewromanpsmt_16" },
    { "sharpness", "Острота изображения", "lv_font_timesnewromanpsmt_16" },
    { "awb", "Белый баланс.", "lv_font_timesnewromanpsmt_16" },
    { "color", "цвет", "lv_font_timesnewromanpsmt_16" },
    { "exposure", "Компенсация экспозиции", "lv_font_timesnewromanpsmt_16" },
    { "handshake", "Руки трясутся.", "lv_font_timesnewromanpsmt_16" },
    { "preview", "Быстрый предварительный просмотр.", "lv_font_timesnewromanpsmt_16" },
    { "doublerec", "Двойная съемка", "lv_font_timesnewromanpsmt_16" },
    { "cycrec", "Повтор.", "lv_font_timesnewromanpsmt_16" },
    { "gaprec", "Видео, когда оно сжимается", "lv_font_timesnewromanpsmt_16" },
    { "motion", "Проверка движения", "lv_font_timesnewromanpsmt_16" },
    { "gsensor", "Гравитационная индукция", "lv_font_timesnewromanpsmt_16" },
    { "record", "зап", "lv_font_timesnewromanpsmt_16" },
    { "guard", "Охрана парковки.", "lv_font_timesnewromanpsmt_16" },
    { "Lsensitive", "Низкая чувствительность", "lv_font_timesnewromanpsmt_16" },
    { "Msensitive", "Средняя чувствительность", "lv_font_timesnewromanpsmt_16" },
    { "Hsensitive", "Высокая чувствительность", "lv_font_timesnewromanpsmt_16" },
    { "tung", "Вольфрамовая лампа", "lv_font_timesnewromanpsmt_16" },
    { "sysprompt", "готов", "lv_font_timesnewromanpsmt_16" },
    { "lowpow", "Недостаточно мощности.", "lv_font_timesnewromanpsmt_16" },
    { "nofile", "Документов нет.", "lv_font_timesnewromanpsmt_16" },
    { "nosd", "Карта памяти не включена", "lv_font_timesnewromanpsmt_16" },
    { "nocamera", "Камеры выключены", "lv_font_timesnewromanpsmt_16" },
    { "fileerr", "Файл поврежден.", "lv_font_timesnewromanpsmt_16" },
    { "format_succ", "Формат принят!", "lv_font_timesnewromanpsmt_16" },
    { "sys_reset", "Восстановление заводской установки успешно!", "lv_font_timesnewromanpsmt_16" },
    { "format_failed", "Формат не работает!", "lv_font_timesnewromanpsmt_16" },
    { "sys_reset_failed", "Восстановление заводской установки не работает!", "lv_font_timesnewromanpsmt_16" },
    { "subpagewarning3", "Версия: JL V1.0.0", "lv_font_timesnewromanpsmt_24" },
    { "update_tips", "Пожалуйста, не отключайте электричество", "lv_font_timesnewromanpsmt_16" },
    { "line_drift_horizon", "Пожалуйста, подойдите к горизонту", "lv_font_timesnewromanpsmt_16" },
    { "line_drift_car", "Пожалуйста, пройдите в машину", "lv_font_timesnewromanpsmt_16" },
    { "cancel", "отмен", "lv_font_timesnewromanpsmt_16" },
    { "ensure", "увер", "lv_font_timesnewromanpsmt_16" },
    { "sd_update", "Была ли обновлена карта памяти?", "lv_font_timesnewromanpsmt_16" },
    { "Mon", "понедельник", "lv_font_timesnewromanpsmt_16" },
    { "Tue", "Вторник.", "lv_font_timesnewromanpsmt_16" },
    { "Wed", "среда", "lv_font_timesnewromanpsmt_16" },
    { "Thu", "Четверг.", "lv_font_timesnewromanpsmt_16" },
    { "Fir", "пятница", "lv_font_timesnewromanpsmt_16" },
    { "Sat", "Суббота.", "lv_font_timesnewromanpsmt_16" },
    { "Sun", "воскресенье", "lv_font_timesnewromanpsmt_16" },
    { "del_file", "Удалены ли выбранные файлы?", "lv_font_timesnewromanpsmt_16" },
    { "lock_file", "Добавлять или открывать выбранные файлы?", "lv_font_timesnewromanpsmt_16" },
    { "unlock_file", "Открыть выбранный файл или нет?", "lv_font_timesnewromanpsmt_16" },
    { "unlock_all", "Открыть все файлы или нет?", "lv_font_timesnewromanpsmt_16" },
    { "file_is_lock", "Файл был закрыт", "lv_font_timesnewromanpsmt_16" },
    { "del_all", "Удалить все файлы или нет?", "lv_font_timesnewromanpsmt_16" },
    { "lock_all", "Все файлы заблокированы?", "lv_font_timesnewromanpsmt_16" },
    { "fs_err", "Аномальное состояние карты тф", "lv_font_timesnewromanpsmt_16" },
    { "gap_err", "Пожалуйста, выключите съемку!", "lv_font_timesnewromanpsmt_16" },
    { "being_formatted", "В формате...", "lv_font_timesnewromanpsmt_16" },
    { "car_record", "Регистрация движения", "lv_font_timesnewromanpsmt_16" },
    { "grellra", "видеоальбом", "lv_font_timesnewromanpsmt_16" },
    { "sys_setting", "Режим.", "lv_font_timesnewromanpsmt_16" },
    { "wifi", "Wi-fi", "lv_font_timesnewromanpsmt_16" },
    { "no_open_wifi", "Wi-fi не включен", "lv_font_timesnewromanpsmt_16" },
    { "click_out", "Нажмите  выход  в любом месте", "lv_font_timesnewromanpsmt_16" },
    { "setting_title", "... настройки системы", "lv_font_timesnewromanpsmt_16" },
    { "menu_wifi", "Wi-fi", "lv_font_timesnewromanpsmt_16" },
    { "wait", "Подождите, пожалуйста...", "lv_font_timesnewromanpsmt_16" },
    { "min1", "Одна минута.", "lv_font_timesnewromanpsmt_16" },
    { "min3", "Три минуты.", "lv_font_timesnewromanpsmt_16" },
    { "min10", "10 минут.", "lv_font_timesnewromanpsmt_16" },
    { "date_label", "Дата.", "lv_font_timesnewromanpsmt_16" },
    { "car_set", "Номерной знак.", "lv_font_timesnewromanpsmt_16" },
    { "back_insert", "Задние дороги не обнаружены", "lv_font_timesnewromanpsmt_16" },
    { "roller_select", "Пожалуйста, выбирайте по порядку и меню вверх и вниз", "lv_font_timesnewromanpsmt_16" },
    { "off_10_sec", "Машина выключится через 10 секунд", "lv_font_timesnewromanpsmt_16" },
    { "voi_num", "Громкость оборудования", "lv_font_timesnewromanpsmt_16" },
    { "sub_low", "низк", "lv_font_timesnewromanpsmt_16" },
    { "sub_middle", "в", "lv_font_timesnewromanpsmt_16" },
    { "sub_high", "высок", "lv_font_timesnewromanpsmt_16" },
    { "min5", "Пять минут.", "lv_font_timesnewromanpsmt_16" },
    { "menu_hdr", "Высокодинамический диапазон", "lv_font_timesnewromanpsmt_16" },
    { "lan_russin", "русск", "lv_font_timesnewromanpsmt_16" },
    { "lcdprotect_p", "Защита экрана.", "lv_font_timesnewromanpsmt_16" },
    { "poweroff_p", "Автоматический выключение", "lv_font_timesnewromanpsmt_16" },
    { "frequency_p", "Частота источника света", "lv_font_timesnewromanpsmt_16" },
    { "speaker_p", "Нажми на кнопку.", "lv_font_timesnewromanpsmt_16" },
    { "language_p", "Настройка языка", "lv_font_timesnewromanpsmt_16" },
    { "software_p", "Номер версии.", "lv_font_timesnewromanpsmt_16" },
    { "carnum_p", "Номер машины.", "lv_font_timesnewromanpsmt_16" },
    { "roadline_p", "Сдвиг полосы.", "lv_font_timesnewromanpsmt_16" },
    { "lamp_p", "Фары!", "lv_font_timesnewromanpsmt_16" },
    { "formatting_p", "Форматирование.", "lv_font_timesnewromanpsmt_16" },
    { "reset_p", "Настройка по умолчанию", "lv_font_timesnewromanpsmt_16" },
    { "date_p", "Дата, время.", "lv_font_timesnewromanpsmt_16" },
    { "close_p", "закр", "lv_font_timesnewromanpsmt_16" },
    { "open_p", "откр", "lv_font_timesnewromanpsmt_16" },
    { "min1_p", "Одна минута.", "lv_font_timesnewromanpsmt_16" },
    { "min3_p", "Три минуты.", "lv_font_timesnewromanpsmt_16" },
    { "min10_p", "10 минут.", "lv_font_timesnewromanpsmt_16" },
    { "date_label_p", "Дата.", "lv_font_timesnewromanpsmt_16" },
    { "car_set_p", "Номерной знак.", "lv_font_timesnewromanpsmt_16" },
    { "shoot_p", "Способ съемки.", "lv_font_timesnewromanpsmt_16" },
    { "resolution_p", "Разрешающая способность", "lv_font_timesnewromanpsmt_16" },
    { "shots_p", "Даж снима", "lv_font_timesnewromanpsmt_16" },
    { "quality_p", "Качество изображения", "lv_font_timesnewromanpsmt_16" },
    { "sharpness_p", "Острота изображения", "lv_font_timesnewromanpsmt_16" },
    { "awb_p", "Белый баланс.", "lv_font_timesnewromanpsmt_16" },
    { "color_p", "цвет", "lv_font_timesnewromanpsmt_16" },
    { "exposure_p", "Компенсация экспозиции", "lv_font_timesnewromanpsmt_16" },
    { "handshake_p", "Руки трясутся.", "lv_font_timesnewromanpsmt_16" },
    { "preview_p", "Быстрый предварительный просмотр.", "lv_font_timesnewromanpsmt_16" },
    { "doublerec_p", "Двойная съемка", "lv_font_timesnewromanpsmt_16" },
    { "cycrec_p", "Повтор.", "lv_font_timesnewromanpsmt_16" },
    { "gaprec_p", "Видео, когда оно сжимается", "lv_font_timesnewromanpsmt_16" },
    { "motion_p", "Проверка движения", "lv_font_timesnewromanpsmt_16" },
    { "gsensor_p", "Гравитационная индукция", "lv_font_timesnewromanpsmt_16" },
    { "record_p", "зап", "lv_font_timesnewromanpsmt_16" },
    { "guard_p", "Охрана парковки.", "lv_font_timesnewromanpsmt_16" },
    { "menu_hdr_p", "Высокодинамический диапазон", "lv_font_timesnewromanpsmt_16" },
    { NULL, NULL, NULL }
};

static lv_i18n_phrase_t ru_plurals_other[] = {

    { NULL, NULL, NULL }
};

static uint8_t ru_plural_fn(int32_t num)
{
    uint32_t n = op_n(num);
    UNUSED(n);
    uint32_t i = op_i(n);
    UNUSED(i);
    uint32_t v = op_v(n);
    UNUSED(v);

    if ((i == 1 && v == 0)) {
        return LV_I18N_PLURAL_TYPE_ONE;
    }
    return LV_I18N_PLURAL_TYPE_OTHER;
}

static const lv_i18n_lang_t ru_lang = {
    .locale_name = "ru",
    .singulars = ru_singulars,
    .plurals[LV_I18N_PLURAL_TYPE_OTHER] = ru_plurals_other,
    .locale_plural_fn = ru_plural_fn
};
static lv_i18n_phrase_t ar_ae_singulars[] = {
    { "funkey4", "preset", "lv_font_segoeui_16" },
    { "funkey5", "preset", "lv_font_segoeui_16" },
    { "funkey6", "preset", "lv_font_segoeui_16" },
    { "funkey7", "preset", "lv_font_segoeui_16" },
    { "suplanguage", "اللغة العربية", "lv_font_segoeui_16" },
    { "lcdprotect", "شاشة التوقف", "lv_font_segoeui_16" },
    { "poweroff", "الاغلاق التلقائي", "lv_font_segoeui_16" },
    { "frequency", "مصدر الضوء تردد", "lv_font_segoeui_16" },
    { "speaker", "مفتاح الصوت", "lv_font_segoeui_16" },
    { "language", "إعدادات اللغة", "lv_font_segoeui_16" },
    { "software", "رقم الإصدار", "lv_font_segoeui_16" },
    { "carnum", "رقم لوحة الرخصة", "lv_font_segoeui_16" },
    { "roadline", "لين الانحراف", "lv_font_segoeui_16" },
    { "lamp", "المصابيح الأمامية", "lv_font_segoeui_16" },
    { "formatting", "شكل", "lv_font_segoeui_16" },
    { "reset", "الإعداد الافتراضي", "lv_font_segoeui_16" },
    { "date", "التاريخ والوقت", "lv_font_segoeui_16" },
    { "close", "غلق", "lv_font_segoeui_16" },
    { "open", "فتح .", "lv_font_segoeui_16" },
    { "subpagewarning0", "تحذيرn\انقر فوق موافق حذف جميع البيانات", "lv_font_segoeui_24" },
    { "subpagewarning1", "تحذيرn\لا توجد بطاقة الذاكرة", "lv_font_segoeui_24" },
    { "subpagewarning2", "تحذيرn\استعادة إعدادات المصنع", "lv_font_segoeui_24" },
    { "YES", "أكّد", "lv_font_segoeui_16" },
    { "CANCEL", "ألغى", "lv_font_segoeui_16" },
    { "shoot", "طريقة اطلاق النار", "lv_font_segoeui_16" },
    { "dealy10s", "توقيت 10 ثانية", "lv_font_segoeui_16" },
    { "dealy5s", "توقيت 5 ثوان", "lv_font_segoeui_16" },
    { "dealy2s", "توقيت 2 ثانية", "lv_font_segoeui_16" },
    { "nodealy", "طلقة واحدة", "lv_font_segoeui_16" },
    { "standard", "ستاندرد", "lv_font_segoeui_16" },
    { "pool", "اقتصاديات", "lv_font_segoeui_16" },
    { "high", "جودة عالية", "lv_font_segoeui_16" },
    { "strong", "بشكل مكثف", "lv_font_segoeui_16" },
    { "soft", "ليونة", "lv_font_segoeui_16" },
    { "mono", "أبيض وأسود", "lv_font_segoeui_16" },
    { "Nostalgia", "حنين", "lv_font_segoeui_16" },
    { "acuity", "حدة الصورة", "lv_font_segoeui_16" },
    { "sunshine", "ضوء النهار", "lv_font_segoeui_16" },
    { "cloudy", "متلبد بالغيوم متلبد بالغيوم", "lv_font_segoeui_16" },
    { "fluolamp", "مصباح الفلورسنت", "lv_font_segoeui_16" },
    { "default", "افتراضي", "lv_font_segoeui_16" },
    { "resolution", "القرار", "lv_font_segoeui_16" },
    { "shots", "ضرب", "lv_font_segoeui_16" },
    { "quality", "جودة الصورة", "lv_font_segoeui_16" },
    { "sharpness", "حدة الصورة", "lv_font_segoeui_16" },
    { "awb", "توازن اللون الأبيض", "lv_font_segoeui_16" },
    { "color", "لون", "lv_font_segoeui_16" },
    { "exposure", "التعرض للتعويضات", "lv_font_segoeui_16" },
    { "handshake", "منع اهتزاز اليد", "lv_font_segoeui_16" },
    { "preview", "معاينة سريعة", "lv_font_segoeui_16" },
    { "doublerec", "المسار المزدوج الفيديو", "lv_font_segoeui_16" },
    { "cycrec", "حلقة فيديو", "lv_font_segoeui_16" },
    { "gaprec", "فيديو مصغر", "lv_font_segoeui_16" },
    { "motion", "كشف الحركة", "lv_font_segoeui_16" },
    { "gsensor", "الجاذبية التعريفي", "lv_font_segoeui_16" },
    { "record", "تسجيل صوتي", "lv_font_segoeui_16" },
    { "guard", "موقف الحرس", "lv_font_segoeui_16" },
    { "Lsensitive", "حساسية منخفضة", "lv_font_segoeui_16" },
    { "Msensitive", "حساسية متوسطة", "lv_font_segoeui_16" },
    { "Hsensitive", "حساسية عالية", "lv_font_segoeui_16" },
    { "tung", "التنغستن مصباح", "lv_font_segoeui_16" },
    { "sysprompt", "جاهز", "lv_font_segoeui_16" },
    { "lowpow", "نقص الكهرباء", "lv_font_segoeui_16" },
    { "nofile", "لا يوجد ملف", "lv_font_segoeui_16" },
    { "nosd", "بطاقة الذاكرة الرقمية المؤمنة لا تضاف", "lv_font_segoeui_16" },
    { "nocamera", "الكاميرا قد انخفض .", "lv_font_segoeui_16" },
    { "fileerr", "ملف الفساد", "lv_font_segoeui_16" },
    { "format_succ", "تنسيق بنجاح !", "lv_font_segoeui_16" },
    { "sys_reset", "استعادة إعدادات المصنع بنجاح !", "lv_font_segoeui_16" },
    { "format_failed", "فشل التنسيق !", "lv_font_segoeui_16" },
    { "sys_reset_failed", "فشل في استعادة إعدادات المصنع !", "lv_font_segoeui_16" },
    { "subpagewarning3", "النسخة : JL V1.0.0", "lv_font_segoeui_24" },
    { "update_tips", "لا انقطاع التيار الكهربائي ، ترقية", "lv_font_segoeui_16" },
    { "line_drift_horizon", "يرجى الانتقال إلى الأفق", "lv_font_segoeui_16" },
    { "line_drift_car", "يرجى الانتقال إلى الأمام", "lv_font_segoeui_16" },
    { "cancel", "ألغى", "lv_font_segoeui_16" },
    { "ensure", "أكّد", "lv_font_segoeui_16" },
    { "sd_update", "هل تريد ترقية بطاقة الذاكرة الرقمية المؤمنة ؟", "lv_font_segoeui_16" },
    { "Mon", "الاثنين .", "lv_font_segoeui_16" },
    { "Tue", "يوم الثلاثاء", "lv_font_segoeui_16" },
    { "Wed", "الأربعاء .", "lv_font_segoeui_16" },
    { "Thu", "يوم الخميس", "lv_font_segoeui_16" },
    { "Fir", "الجمعة .", "lv_font_segoeui_16" },
    { "Sat", "سبت", "lv_font_segoeui_16" },
    { "Sun", "الأحد .", "lv_font_segoeui_16" },
    { "del_file", "حذف الملف المحدد ؟", "lv_font_segoeui_16" },
    { "lock_file", "هل تريد قفل / فتح الملف المحدد ؟", "lv_font_segoeui_16" },
    { "unlock_file", "هل تريد فتح الملف المحدد ؟", "lv_font_segoeui_16" },
    { "unlock_all", "فتح جميع الملفات ؟", "lv_font_segoeui_16" },
    { "file_is_lock", "الملف مغلق", "lv_font_segoeui_16" },
    { "del_all", "حذف جميع الملفات ؟", "lv_font_segoeui_16" },
    { "lock_all", "قفل جميع الملفات ؟", "lv_font_segoeui_16" },
    { "fs_err", "بطاقة TF حالة شاذة", "lv_font_segoeui_16" },
    { "gap_err", "الرجاء إغلاق الفيديو المصغرة !", "lv_font_segoeui_16" },
    { "being_formatted", "شكل . . .", "lv_font_segoeui_16" },
    { "car_record", "سجل القيادة", "lv_font_segoeui_16" },
    { "grellra", "فيديو البوم", "lv_font_segoeui_16" },
    { "sys_setting", "إعدادات الوظيفة", "lv_font_segoeui_16" },
    { "wifi", "WIFI", "lv_font_segoeui_16" },
    { "no_open_wifi", "واي فاي لا تحول", "lv_font_segoeui_16" },
    { "click_out", "انقر في أي مكان للخروج", "lv_font_segoeui_16" },
    { "setting_title", "إعدادات النظام", "lv_font_segoeui_16" },
    { "menu_wifi", "WIFI", "lv_font_segoeui_16" },
    { "wait", "انتظر من فضلك", "lv_font_segoeui_16" },
    { "min1", "دقيقة", "lv_font_segoeui_16" },
    { "min3", "دقيقة", "lv_font_segoeui_16" },
    { "min10", "10 دقائق", "lv_font_segoeui_16" },
    { "date_label", "تاريخ التسمية", "lv_font_segoeui_16" },
    { "car_set", "لوحة ترخيص مجموعة", "lv_font_segoeui_16" },
    { "back_insert", "لم يتم الكشف عن الخلفية", "lv_font_segoeui_16" },
    { "roller_select", "من فضلك اضغط على طريقة اختيار القائمة الرئيسية صعودا وهبوطا", "lv_font_segoeui_16" },
    { "off_10_sec", "الجهاز سوف تغلق في 10 ثوان .", "lv_font_segoeui_16" },
    { "voi_num", "حجم الجهاز", "lv_font_segoeui_16" },
    { "sub_low", "منخفض", "lv_font_segoeui_16" },
    { "sub_middle", "وسط", "lv_font_segoeui_16" },
    { "sub_high", "عالية .", "lv_font_segoeui_16" },
    { "min5", "دقيقة", "lv_font_segoeui_16" },
    { "menu_hdr", "مجموعة ديناميكية عالية", "lv_font_segoeui_16" },
    { "lan_russin", "русск", "lv_font_segoeui_16" },
    { "lcdprotect_p", "شاشة التوقف", "lv_font_segoeui_16" },
    { "poweroff_p", "الاغلاق التلقائي", "lv_font_segoeui_16" },
    { "frequency_p", "· تردد مصدر الضوء", "lv_font_segoeui_16" },
    { "speaker_p", "مفتاح الصوت", "lv_font_segoeui_16" },
    { "language_p", "إعدادات اللغة", "lv_font_segoeui_16" },
    { "software_p", "· رقم الإصدار", "lv_font_segoeui_16" },
    { "carnum_p", "· رقم لوحة الرخصة", "lv_font_segoeui_16" },
    { "roadline_p", "لين أوفست", "lv_font_segoeui_16" },
    { "lamp_p", "• المصابيح الأمامية", "lv_font_segoeui_16" },
    { "formatting_p", "تنسيق", "lv_font_segoeui_16" },
    { "reset_p", "الإعدادات الافتراضية", "lv_font_segoeui_16" },
    { "date_p", "التاريخ والوقت", "lv_font_segoeui_16" },
    { "close_p", "إغلاق", "lv_font_segoeui_16" },
    { "open_p", "فتح", "lv_font_segoeui_16" },
    { "min1_p", "دقيقة واحدة", "lv_font_segoeui_16" },
    { "min3_p", "· 3 دقائق", "lv_font_segoeui_16" },
    { "min10_p", "• 10 دقائق", "lv_font_segoeui_16" },
    { "date_label_p", "تاريخ الوسم", "lv_font_segoeui_16" },
    { "car_set_p", "· إعدادات لوحة ترخيص", "lv_font_segoeui_16" },
    { "shoot_p", "طريقة التصوير", "lv_font_segoeui_16" },
    { "resolution_p", "• القرار", "lv_font_segoeui_16" },
    { "shots_p", "( ترجمة حرفية ) : استمرار اطلاق النار", "lv_font_segoeui_16" },
    { "quality_p", "· جودة الصورة", "lv_font_segoeui_16" },
    { "sharpness_p", "· حدة الصورة", "lv_font_segoeui_16" },
    { "awb_p", "توازن اللون الأبيض", "lv_font_segoeui_16" },
    { "color_p", "اللون", "lv_font_segoeui_16" },
    { "exposure_p", "· تعويض التعرض", "lv_font_segoeui_16" },
    { "handshake_p", "• مكافحة اهتزاز اليد", "lv_font_segoeui_16" },
    { "preview_p", "معاينة سريعة", "lv_font_segoeui_16" },
    { "doublerec_p", "· فيديو الطريق المزدوج", "lv_font_segoeui_16" },
    { "cycrec_p", "• حلقة فيديو", "lv_font_segoeui_16" },
    { "gaprec_p", "• الفيديو المصغر", "lv_font_segoeui_16" },
    { "motion_p", "كشف الحركة", "lv_font_segoeui_16" },
    { "gsensor_p", "• الحث على الجاذبية", "lv_font_segoeui_16" },
    { "record_p", "تسجيل", "lv_font_segoeui_16" },
    { "guard_p", "حراس مواقف السيارات", "lv_font_segoeui_16" },
    { "menu_hdr_p", "مجموعة ديناميكية عالية", "lv_font_segoeui_16" },
    { NULL, NULL, NULL }
};

static lv_i18n_phrase_t ar_ae_plurals_other[] = {

    { NULL, NULL, NULL }
};

static uint8_t ar_ae_plural_fn(int32_t num)
{
    uint32_t n = op_n(num);
    UNUSED(n);
    uint32_t i = op_i(n);
    UNUSED(i);
    uint32_t v = op_v(n);
    UNUSED(v);

    if ((i == 1 && v == 0)) {
        return LV_I18N_PLURAL_TYPE_ONE;
    }
    return LV_I18N_PLURAL_TYPE_OTHER;
}

static const lv_i18n_lang_t ar_ae_lang = {
    .locale_name = "ar_ae",
    .singulars = ar_ae_singulars,
    .plurals[LV_I18N_PLURAL_TYPE_OTHER] = ar_ae_plurals_other,
    .locale_plural_fn = ar_ae_plural_fn
};
static lv_i18n_phrase_t th_singulars[] = {
    { "funkey4", "preset", "lv_font_leelawadeeui_16" },
    { "funkey5", "preset", "lv_font_leelawadeeui_16" },
    { "funkey6", "preset", "lv_font_leelawadeeui_16" },
    { "funkey7", "preset", "lv_font_leelawadeeui_16" },
    { "suplanguage", "ภาษาไทย", "lv_font_leelawadeeui_16" },
    { "lcdprotect", "การป้องกันหน้าจอ", "lv_font_leelawadeeui_16" },
    { "poweroff", "ปิดเครื่องอัตโนมัติ", "lv_font_leelawadeeui_16" },
    { "frequency", "ความถี่แหล่งกำเนิดแสง", "lv_font_leelawadeeui_16" },
    { "speaker", "เสียงคีย์", "lv_font_leelawadeeui_16" },
    { "language", "การตั้งค่าภาษา", "lv_font_leelawadeeui_16" },
    { "software", "หมายเลขรุ่น", "lv_font_leelawadeeui_16" },
    { "carnum", "หมายเลขทะเบียนรถ", "lv_font_leelawadeeui_16" },
    { "roadline", "การชดเชยเลน", "lv_font_leelawadeeui_16" },
    { "lamp", "ไฟหน้า", "lv_font_leelawadeeui_16" },
    { "formatting", "การจัดรูปแบบ", "lv_font_leelawadeeui_16" },
    { "reset", "ตั้งค่าปริยาย", "lv_font_leelawadeeui_16" },
    { "date", "วันที่ เวลา", "lv_font_leelawadeeui_16" },
    { "close", "ปิด", "lv_font_leelawadeeui_16" },
    { "open", "เปิด", "lv_font_leelawadeeui_16" },
    { "subpagewarning0", "คำเตือน\nคลิกเพื่อยืนยันการลบข้อมูลทั้งหมด", "lv_font_leelawadeeui_24" },
    { "subpagewarning1", "คำเตือน\nไม่มีการ์ดหน่วยความจำ", "lv_font_leelawadeeui_24" },
    { "subpagewarning2", "คำเตือน\nเรียกคืนการตั้งค่าจากโรงงาน", "lv_font_leelawadeeui_24" },
    { "YES", "ยืนยัน", "lv_font_leelawadeeui_16" },
    { "CANCEL", "การยกเลิก", "lv_font_leelawadeeui_16" },
    { "shoot", "วิธีการถ่ายภาพ", "lv_font_leelawadeeui_16" },
    { "dealy10s", "เวลา 10 วินาที", "lv_font_leelawadeeui_16" },
    { "dealy5s", "เวลา 5 วินาที", "lv_font_leelawadeeui_16" },
    { "dealy2s", "เวลา 2 วินาที", "lv_font_leelawadeeui_16" },
    { "nodealy", "จังหวะเดียว", "lv_font_leelawadeeui_16" },
    { "standard", "มาตรฐาน", "lv_font_leelawadeeui_16" },
    { "pool", "เศรษฐกิจ", "lv_font_leelawadeeui_16" },
    { "high", "คุณภาพสูง", "lv_font_leelawadeeui_16" },
    { "strong", "แข็งแกร่ง", "lv_font_leelawadeeui_16" },
    { "soft", "นุ่มนวล", "lv_font_leelawadeeui_16" },
    { "mono", "ขาวดำ", "lv_font_leelawadeeui_16" },
    { "Nostalgia", "ความคิดถึง", "lv_font_leelawadeeui_16" },
    { "acuity", "ความคมชัดของภาพ", "lv_font_leelawadeeui_16" },
    { "sunshine", "กลางวัน", "lv_font_leelawadeeui_16" },
    { "cloudy", "วันที่มีเมฆมาก", "lv_font_leelawadeeui_16" },
    { "fluolamp", "หลอดฟลูออเรสเซนต์", "lv_font_leelawadeeui_16" },
    { "default", "ปริยาย", "lv_font_leelawadeeui_16" },
    { "resolution", "ความละเอียด", "lv_font_leelawadeeui_16" },
    { "shots", "ยิงต่อเนื่อง", "lv_font_leelawadeeui_16" },
    { "quality", "คุณภาพของภาพ", "lv_font_leelawadeeui_16" },
    { "sharpness", "ความคมชัดของภาพ", "lv_font_leelawadeeui_16" },
    { "awb", "สมดุลสีขาว", "lv_font_leelawadeeui_16" },
    { "color", "สี", "lv_font_leelawadeeui_16" },
    { "exposure", "การชดเชยแสง", "lv_font_leelawadeeui_16" },
    { "handshake", "ป้องกันมือสั่น", "lv_font_leelawadeeui_16" },
    { "preview", "ตัวอย่างด่วน", "lv_font_leelawadeeui_16" },
    { "doublerec", "วิดีโอคู่", "lv_font_leelawadeeui_16" },
    { "cycrec", "ลูปวิดีโอ", "lv_font_leelawadeeui_16" },
    { "gaprec", "วิดีโอย่อเวลา", "lv_font_leelawadeeui_16" },
    { "motion", "การตรวจจับการเคลื่อนไหว", "lv_font_leelawadeeui_16" },
    { "gsensor", "การเหนี่ยวนำแรงโน้มถ่วง", "lv_font_leelawadeeui_16" },
    { "record", "การบันทึกเสียง", "lv_font_leelawadeeui_16" },
    { "guard", "ที่จอดรถยาม", "lv_font_leelawadeeui_16" },
    { "Lsensitive", "ความไวต่ำ", "lv_font_leelawadeeui_16" },
    { "Msensitive", "ความไวปานกลาง", "lv_font_leelawadeeui_16" },
    { "Hsensitive", "ความไวสูง", "lv_font_leelawadeeui_16" },
    { "tung", "หลอดลวดทังสเตน", "lv_font_leelawadeeui_16" },
    { "sysprompt", "พร้อมยัง ~", "lv_font_leelawadeeui_16" },
    { "lowpow", "ไฟฟ้าไม่เพียงพอ", "lv_font_leelawadeeui_16" },
    { "nofile", "ไม่มีแฟ้ม", "lv_font_leelawadeeui_16" },
    { "nosd", "ไม่ได้เสียบการ์ด SD", "lv_font_leelawadeeui_16" },
    { "nocamera", "กล้องตก", "lv_font_leelawadeeui_16" },
    { "fileerr", "แฟ้มเสียหาย", "lv_font_leelawadeeui_16" },
    { "format_succ", "ฟอร์แมตสำเร็จ!", "lv_font_leelawadeeui_16" },
    { "sys_reset", "เรียกคืนการตั้งค่าจากโรงงานที่ประสบความสำเร็จ!", "lv_font_leelawadeeui_16" },
    { "format_failed", "การจัดรูปแบบล้มเหลว!", "lv_font_leelawadeeui_16" },
    { "sys_reset_failed", "การกู้คืนการตั้งค่าจากโรงงานล้มเหลว!", "lv_font_leelawadeeui_16" },
    { "subpagewarning3", "รุ่น: JL V1.0.0", "lv_font_leelawadeeui_24" },
    { "update_tips", "ห้ามปิดเครื่องอัพเกรด", "lv_font_leelawadeeui_16" },
    { "line_drift_horizon", "โปรดย้ายไปที่ขอบฟ้า", "lv_font_leelawadeeui_16" },
    { "line_drift_car", "กรุณาย้ายไปที่หัวรถ", "lv_font_leelawadeeui_16" },
    { "cancel", "การยกเลิก", "lv_font_leelawadeeui_16" },
    { "ensure", "ระบุ", "lv_font_leelawadeeui_16" },
    { "sd_update", "จะทำการอัปเกรดการ์ด SD หรือไม่?", "lv_font_leelawadeeui_16" },
    { "Mon", "วันจันทร์", "lv_font_leelawadeeui_16" },
    { "Tue", "วันอังคาร", "lv_font_leelawadeeui_16" },
    { "Wed", "วันพุธ", "lv_font_leelawadeeui_16" },
    { "Thu", "วันพฤหัสบดี", "lv_font_leelawadeeui_16" },
    { "Fir", "วันศุกร์", "lv_font_leelawadeeui_16" },
    { "Sat", "วันเสาร์", "lv_font_leelawadeeui_16" },
    { "Sun", "วันอาทิตย์", "lv_font_leelawadeeui_16" },
    { "del_file", "คุณต้องการลบแฟ้มที่เลือกไว้หรือไม่?", "lv_font_leelawadeeui_16" },
    { "lock_file", "เพิ่มล็อค/ปลดล็อคแฟ้มที่เลือกไว้หรือไม่?", "lv_font_leelawadeeui_16" },
    { "unlock_file", "จะปลดล็อคแฟ้มที่เลือกไว้หรือไม่?", "lv_font_leelawadeeui_16" },
    { "unlock_all", "คุณต้องการปลดล็อคแฟ้มทั้งหมดหรือไม่?", "lv_font_leelawadeeui_16" },
    { "file_is_lock", "แฟ้มถูกล็อค", "lv_font_leelawadeeui_16" },
    { "del_all", "คุณต้องการลบแฟ้มทั้งหมดหรือไม่?", "lv_font_leelawadeeui_16" },
    { "lock_all", "เพิ่มล็อคแฟ้มทั้งหมดหรือไม่?", "lv_font_leelawadeeui_16" },
    { "fs_err", "บัตร TF สถานะผิดปกติ", "lv_font_leelawadeeui_16" },
    { "gap_err", "โปรดปิดวิดีโอย่อเวลา!", "lv_font_leelawadeeui_16" },
    { "being_formatted", "กำลังฟอร์แมต...", "lv_font_leelawadeeui_16" },
    { "car_record", "บันทึกการขับขี่", "lv_font_leelawadeeui_16" },
    { "grellra", "อัลบั้มวิดีโอ", "lv_font_leelawadeeui_16" },
    { "sys_setting", "การตั้งค่าฟังก์ชั่น", "lv_font_leelawadeeui_16" },
    { "wifi", "WIFI", "lv_font_leelawadeeui_16" },
    { "no_open_wifi", "ไม่ได้เปิด WiFi", "lv_font_leelawadeeui_16" },
    { "click_out", "คลิกที่ใดก็ได้เพื่อออก", "lv_font_leelawadeeui_16" },
    { "setting_title", "·การตั้งค่าระบบ ·", "lv_font_leelawadeeui_16" },
    { "menu_wifi", "WIFI", "lv_font_leelawadeeui_16" },
    { "wait", "กรุณารอสักครู่...", "lv_font_leelawadeeui_16" },
    { "min1", "1 นาที", "lv_font_leelawadeeui_16" },
    { "min3", "3 นาที", "lv_font_leelawadeeui_16" },
    { "min10", "10 นาที", "lv_font_leelawadeeui_16" },
    { "date_label", "ป้ายวันที่", "lv_font_leelawadeeui_16" },
    { "car_set", "การตั้งค่าป้ายทะเบียน", "lv_font_leelawadeeui_16" },
    { "back_insert", "ตรวจสอบไม่พบเส้นทางด้านหลัง", "lv_font_leelawadeeui_16" },
    { "roller_select", "โปรดเลือกขึ้นและลงโดยโหมดและปุ่มเมนู", "lv_font_leelawadeeui_16" },
    { "off_10_sec", "เครื่องจะปิดใน 10 วินาที", "lv_font_leelawadeeui_16" },
    { "voi_num", "ระดับเสียงของอุปกรณ์", "lv_font_leelawadeeui_16" },
    { "sub_low", "ต่ำ", "lv_font_leelawadeeui_16" },
    { "sub_middle", "กลาง", "lv_font_leelawadeeui_16" },
    { "sub_high", "สูง", "lv_font_leelawadeeui_16" },
    { "min5", "5 นาที", "lv_font_leelawadeeui_16" },
    { "menu_hdr", "ช่วงไดนามิกสูง", "lv_font_leelawadeeui_16" },
    { "lan_russin", "русск", "lv_font_segoeui_16" },
    { "lcdprotect_p", "·การป้องกันหน้าจอ ·", "lv_font_leelawadeeui_16" },
    { "poweroff_p", "· ปิดอัตโนมัติ ·", "lv_font_leelawadeeui_16" },
    { "frequency_p", "·ความถี่แหล่งกำเนิดแสง ·", "lv_font_leelawadeeui_16" },
    { "speaker_p", "·เสียงคีย์ ·", "lv_font_leelawadeeui_16" },
    { "language_p", "·การตั้งค่าภาษา ·", "lv_font_leelawadeeui_16" },
    { "software_p", "·หมายเลขรุ่น ·", "lv_font_leelawadeeui_16" },
    { "carnum_p", "· หมายเลขทะเบียนรถ ·", "lv_font_leelawadeeui_16" },
    { "roadline_p", "·การชดเชยเลน ·", "lv_font_leelawadeeui_16" },
    { "lamp_p", "· ไฟหน้า ·", "lv_font_leelawadeeui_16" },
    { "formatting_p", "· รูปแบบ ·", "lv_font_leelawadeeui_16" },
    { "reset_p", "· การตั้งค่าเริ่มต้น ·", "lv_font_leelawadeeui_16" },
    { "date_p", "· วันที่และเวลา ·", "lv_font_leelawadeeui_16" },
    { "close_p", "· ปิด", "lv_font_leelawadeeui_16" },
    { "open_p", "· เปิด", "lv_font_leelawadeeui_16" },
    { "min1_p", "· 1 นาที ·", "lv_font_leelawadeeui_16" },
    { "min3_p", "· 3 นาที ·", "lv_font_leelawadeeui_16" },
    { "min10_p", "· 10 นาที ·", "lv_font_leelawadeeui_16" },
    { "date_label_p", "· ป้ายวันที่ ·", "lv_font_leelawadeeui_16" },
    { "car_set_p", "·การตั้งค่าป้ายทะเบียน·", "lv_font_leelawadeeui_16" },
    { "shoot_p", "· วิธีการถ่ายภาพ ·", "lv_font_leelawadeeui_16" },
    { "resolution_p", "· ความละเอียด ·", "lv_font_leelawadeeui_16" },
    { "shots_p", "· การถ่ายภาพต่อเนื่อง ·", "lv_font_leelawadeeui_16" },
    { "quality_p", "· คุณภาพของภาพ ·", "lv_font_leelawadeeui_16" },
    { "sharpness_p", "· ความคมชัดของภาพ ·", "lv_font_leelawadeeui_16" },
    { "awb_p", "· สมดุลสีขาว ·", "lv_font_leelawadeeui_16" },
    { "color_p", "· สี ·", "lv_font_leelawadeeui_16" },
    { "exposure_p", "· การชดเชยแสง ·", "lv_font_leelawadeeui_16" },
    { "handshake_p", "· ป้องกันการสั่นมือ ·", "lv_font_leelawadeeui_16" },
    { "preview_p", "· ตัวอย่างรวดเร็ว ·", "lv_font_leelawadeeui_16" },
    { "doublerec_p", "·วิดีโอสองทาง ·", "lv_font_leelawadeeui_16" },
    { "cycrec_p", "·วงจรวิดีโอ ·", "lv_font_leelawadeeui_16" },
    { "gaprec_p", "· ภาพวิดีโอย่อเวลา ·", "lv_font_leelawadeeui_16" },
    { "motion_p", "·การตรวจจับการเคลื่อนไหว ·", "lv_font_leelawadeeui_16" },
    { "gsensor_p", "· แรงโน้มถ่วงเหนี่ยวนำ ·", "lv_font_leelawadeeui_16" },
    { "record_p", "·การบันทึก ·", "lv_font_leelawadeeui_16" },
    { "guard_p", "· ยามจอดรถ ·", "lv_font_leelawadeeui_16" },
    { "menu_hdr_p", "·ช่วงไดนามิกสูง ·", "lv_font_leelawadeeui_16" },
    { NULL, NULL, NULL }
};

static lv_i18n_phrase_t th_plurals_other[] = {

    { NULL, NULL, NULL }
};

static uint8_t th_plural_fn(int32_t num)
{
    uint32_t n = op_n(num);
    UNUSED(n);
    uint32_t i = op_i(n);
    UNUSED(i);
    uint32_t v = op_v(n);
    UNUSED(v);

    if ((i == 1 && v == 0)) {
        return LV_I18N_PLURAL_TYPE_ONE;
    }
    return LV_I18N_PLURAL_TYPE_OTHER;
}

static const lv_i18n_lang_t th_lang = {
    .locale_name = "th",
    .singulars = th_singulars,
    .plurals[LV_I18N_PLURAL_TYPE_OTHER] = th_plurals_other,
    .locale_plural_fn = th_plural_fn
};
static lv_i18n_phrase_t de_singulars[] = {
    { "funkey4", "preset", "lv_font_segoeui_16" },
    { "funkey5", "preset", "lv_font_segoeui_16" },
    { "funkey6", "preset", "lv_font_segoeui_16" },
    { "funkey7", "preset", "lv_font_segoeui_16" },
    { "suplanguage", "Deutsch", "lv_font_segoeui_16" },
    { "lcdprotect", "Bildschirmschoner", "lv_font_segoeui_16" },
    { "poweroff", "Automatischer Abschaltung", "lv_font_segoeui_16" },
    { "frequency", "Lichtquellenzählfrequenz", "lv_font_segoeui_16" },
    { "speaker", "Tastenklickton", "lv_font_segoeui_16" },
    { "language", "Spracheinstellungen", "lv_font_segoeui_16" },
    { "software", "Versionsnummer", "lv_font_segoeui_16" },
    { "carnum", "Kennzeichennummer", "lv_font_segoeui_16" },
    { "roadline", "Fahrspurabdrift", "lv_font_segoeui_16" },
    { "lamp", "Scheinwerfer", "lv_font_segoeui_16" },
    { "formatting", "Formatierung", "lv_font_segoeui_16" },
    { "reset", "Standardeinstellungen", "lv_font_segoeui_16" },
    { "date", "Datum und Uhrzeit", "lv_font_segoeui_16" },
    { "close", "Schließen", "lv_font_segoeui_16" },
    { "open", "Öffnen", "lv_font_segoeui_16" },
    { "subpagewarning0", "Warnung\nBestätigen, um alle Daten zu löschen", "lv_font_segoeui_24" },
    { "subpagewarning1", "Warnung\nKeine Speicherkarte vorhanden", "lv_font_segoeui_24" },
    { "subpagewarning2", "Warnung\nAuf Werkseinstellungen zurücksetzen", "lv_font_segoeui_24" },
    { "YES", "Bestätigen", "lv_font_segoeui_16" },
    { "CANCEL", "Abbrechen", "lv_font_segoeui_16" },
    { "shoot", "Aufnahmeart", "lv_font_segoeui_16" },
    { "dealy10s", "10-Sekunden-Timer", "lv_font_segoeui_16" },
    { "dealy5s", "5-Sekunden-Timer", "lv_font_segoeui_16" },
    { "dealy2s", "2-Sekunden-Timer", "lv_font_segoeui_16" },
    { "nodealy", "Einzelaufnahme", "lv_font_segoeui_16" },
    { "standard", "Standard", "lv_font_segoeui_16" },
    { "pool", "Sparmodus", "lv_font_segoeui_16" },
    { "high", "Hochwertig", "lv_font_segoeui_16" },
    { "strong", "Stark", "lv_font_segoeui_16" },
    { "soft", "Weich", "lv_font_segoeui_16" },
    { "mono", "Schwarz-Weiss", "lv_font_segoeui_16" },
    { "Nostalgia", "Sepia", "lv_font_segoeui_16" },
    { "acuity", "Bildschärfe", "lv_font_segoeui_16" },
    { "sunshine", "Sonnenlicht", "lv_font_segoeui_16" },
    { "cloudy", "Bewölkt", "lv_font_segoeui_16" },
    { "fluolamp", "Leuchtstofflampe", "lv_font_segoeui_16" },
    { "default", "Standard", "lv_font_segoeui_16" },
    { "resolution", "Auflösung", "lv_font_segoeui_16" },
    { "shots", "Serienaufnahme", "lv_font_segoeui_16" },
    { "quality", "Bildqualität", "lv_font_segoeui_16" },
    { "sharpness", "Bildschärfe", "lv_font_segoeui_16" },
    { "awb", "Weißabgleich", "lv_font_segoeui_16" },
    { "color", "Farbe", "lv_font_segoeui_16" },
    { "exposure", "Belichtungskorrektur", "lv_font_segoeui_16" },
    { "handshake", "Kamerastabilisierung", "lv_font_segoeui_16" },
    { "preview", "Schnelle Vorschau", "lv_font_segoeui_16" },
    { "doublerec", "Doppeltkamera Aufnahme", "lv_font_segoeui_16" },
    { "cycrec", "Endlosschleife", "lv_font_segoeui_16" },
    { "gaprec", "Zeitlupenaufnahme", "lv_font_segoeui_16" },
    { "motion", "Bewegungserkennung", "lv_font_segoeui_16" },
    { "gsensor", "Schwerkraftsensor", "lv_font_segoeui_16" },
    { "record", "Tonaufnahme", "lv_font_segoeui_16" },
    { "guard", "Parküberwachung", "lv_font_segoeui_16" },
    { "Lsensitive", "Niedrige Empfindlichkeit", "lv_font_segoeui_16" },
    { "Msensitive", "Mittlere Empfindlichkeit", "lv_font_segoeui_16" },
    { "Hsensitive", "Hohe Empfindlichkeit", "lv_font_segoeui_16" },
    { "tung", "Glühlampe", "lv_font_segoeui_16" },
    { "sysprompt", "Bist du bereit?", "lv_font_segoeui_16" },
    { "lowpow", "Geringe Batteriekapazität", "lv_font_segoeui_16" },
    { "nofile", "Keine Dateien vorhanden", "lv_font_segoeui_16" },
    { "nosd", "SD-Karte nicht eingeführt", "lv_font_segoeui_16" },
    { "nocamera", "Kamera-Verbindung abfallen", "lv_font_segoeui_16" },
    { "fileerr", "Dateien beschädigt", "lv_font_segoeui_16" },
    { "format_succ", "Formatierung erfolgreich!", "lv_font_segoeui_16" },
    { "sys_reset", "Auf Werkseinstellungen zurücksetzen erfolgreich!", "lv_font_segoeui_16" },
    { "format_failed", "Formatierung fehlgeschlagen!", "lv_font_segoeui_16" },
    { "sys_reset_failed", "Auf Werkseinstellungen zurücksetzen fehlgeschlagen!", "lv_font_segoeui_16" },
    { "subpagewarning3", "Version: JL V1.0.0", "lv_font_segoeui_24" },
    { "update_tips", "Während des Updates bitte nicht abschalten", "lv_font_segoeui_16" },
    { "line_drift_horizon", "Bitte auf die Horizontlinie bewegen", "lv_font_segoeui_16" },
    { "line_drift_car", "Bitte auf die Fahrzeugfront bewegen", "lv_font_segoeui_16" },
    { "cancel", "Abbrechen", "lv_font_segoeui_16" },
    { "ensure", "Bestätigen", "lv_font_segoeui_16" },
    { "sd_update", "Möchten Sie die SD-Karte aktualisieren?", "lv_font_segoeui_16" },
    { "Mon", "Montag", "lv_font_segoeui_16" },
    { "Tue", "Dienstag", "lv_font_segoeui_16" },
    { "Wed", "Mittwoch", "lv_font_segoeui_16" },
    { "Thu", "Donnerstag", "lv_font_segoeui_16" },
    { "Fir", "Freitag", "lv_font_segoeui_16" },
    { "Sat", "Samstag", "lv_font_segoeui_16" },
    { "Sun", "Sonntag", "lv_font_segoeui_16" },
    { "del_file", "Möchten Sie die ausgewählte Datei löschen?", "lv_font_segoeui_16" },
    { "lock_file", "Möchten Sie die ausgewählte Datei sperren/entsperren?", "lv_font_segoeui_16" },
    { "unlock_file", "Möchten Sie die ausgewählte Datei entsperren?", "lv_font_segoeui_16" },
    { "unlock_all", "Möchten Sie alle Dateien entsperren?", "lv_font_segoeui_16" },
    { "file_is_lock", "Datei gesperrt", "lv_font_segoeui_16" },
    { "del_all", "Möchten Sie alle Dateien löschen?", "lv_font_segoeui_16" },
    { "lock_all", "Möchten Sie alle Dateien sperren?", "lv_font_segoeui_16" },
    { "fs_err", "Abnormale TF-Kartenstatus", "lv_font_segoeui_16" },
    { "gap_err", "Bitte Zeitlupenaufnahme ausschalten!", "lv_font_segoeui_16" },
    { "being_formatted", "Formatierung läuft...", "lv_font_segoeui_16" },
    { "car_record", "Fahrzeugaufzeichnung", "lv_font_segoeui_16" },
    { "grellra", "Videoalbum", "lv_font_segoeui_16" },
    { "sys_setting", "Funktionseinstellungen", "lv_font_segoeui_16" },
    { "wifi", "WIFI", "lv_font_segoeui_16" },
    { "no_open_wifi", "WIFI nicht aktiviert", "lv_font_segoeui_16" },
    { "click_out", "Klicken Sie irgendwoher, um zu verlassen", "lv_font_segoeui_16" },
    { "setting_title", "·Systemeinstellungen·", "lv_font_segoeui_16" },
    { "menu_wifi", "WIFI", "lv_font_segoeui_16" },
    { "wait", "Bitte warten Sie...", "lv_font_segoeui_16" },
    { "min1", "1 Minute", "lv_font_segoeui_16" },
    { "min3", "3 Minuten", "lv_font_segoeui_16" },
    { "min10", "10 Minuten", "lv_font_segoeui_16" },
    { "date_label", "Datumstempel", "lv_font_segoeui_16" },
    { "car_set", "Kennzeichen-Einstellungen", "lv_font_segoeui_16" },
    { "back_insert", "Keine Rückfahrspurerkennung", "lv_font_segoeui_16" },
    { "roller_select", "Bitte mit Tasten für Modus und Menü nach oben und unten wählen", "lv_font_segoeui_16" },
    { "off_10_sec", "Gerät wird in 10 Sekunden abgeschaltet", "lv_font_segoeui_16" },
    { "voi_num", "Gerätelautstärke", "lv_font_segoeui_16" },
    { "sub_low", "Niedrig", "lv_font_segoeui_16" },
    { "sub_middle", "Mittel", "lv_font_segoeui_16" },
    { "sub_high", "Hoch", "lv_font_segoeui_16" },
    { "min5", "5 Minuten", "lv_font_segoeui_16" },
    { "menu_hdr", "Hochdynamischer Bereich", "lv_font_segoeui_16" },
    { "lan_russin", "русск", "lv_font_segoeui_16" },
    { "lcdprotect_p", "·Bildschirmschoner·", "lv_font_segoeui_16" },
    { "poweroff_p", "·Automatischer Abschaltung·", "lv_font_segoeui_16" },
    { "frequency_p", "·Lichtquellenzählfrequenz·", "lv_font_segoeui_16" },
    { "speaker_p", "·Tastenklickton·", "lv_font_segoeui_16" },
    { "language_p", "·Spracheinstellungen·", "lv_font_segoeui_16" },
    { "software_p", "·Versionsnummer·", "lv_font_segoeui_16" },
    { "carnum_p", "·Kennzeichennummer·", "lv_font_segoeui_16" },
    { "roadline_p", "·Fahrspurabdrift·", "lv_font_segoeui_16" },
    { "lamp_p", "·Scheinwerfer·", "lv_font_segoeui_16" },
    { "formatting_p", "·Formatierung·", "lv_font_segoeui_16" },
    { "reset_p", "·Standardeinstellungen·", "lv_font_segoeui_16" },
    { "date_p", "·Datum und Uhrzeit·", "lv_font_segoeui_16" },
    { "close_p", "·Schließen·", "lv_font_segoeui_16" },
    { "open_p", "·Öffnen·", "lv_font_segoeui_16" },
    { "min1_p", "·1 Minute·", "lv_font_segoeui_16" },
    { "min3_p", "·3 Minuten·", "lv_font_segoeui_16" },
    { "min10_p", "·10 Minuten·", "lv_font_segoeui_16" },
    { "date_label_p", "·Datumstempel·", "lv_font_segoeui_16" },
    { "car_set_p", "·Kennzeichen-Einstellungen·", "lv_font_segoeui_16" },
    { "shoot_p", "·Aufnahmeart·", "lv_font_segoeui_16" },
    { "resolution_p", "·Auflösung·", "lv_font_segoeui_16" },
    { "shots_p", "·Serienaufnahme·", "lv_font_segoeui_16" },
    { "quality_p", "·Bildqualität·", "lv_font_segoeui_16" },
    { "sharpness_p", "·Bildschärfe·", "lv_font_segoeui_16" },
    { "awb_p", "·Weißabgleich·", "lv_font_segoeui_16" },
    { "color_p", "·Farbe·", "lv_font_segoeui_16" },
    { "exposure_p", "·Belichtungskorrektur·", "lv_font_segoeui_16" },
    { "handshake_p", "·Kamerastabilisierung·", "lv_font_segoeui_16" },
    { "preview_p", "·Schnelle Vorschau·", "lv_font_segoeui_16" },
    { "doublerec_p", "·Doppeltkamera Aufnahme·", "lv_font_segoeui_16" },
    { "cycrec_p", "·Endlosschleife·", "lv_font_segoeui_16" },
    { "gaprec_p", "·Zeitlupenaufnahme·", "lv_font_segoeui_16" },
    { "motion_p", "·Bewegungserkennung·", "lv_font_segoeui_16" },
    { "gsensor_p", "·Schwerkraftsensor·", "lv_font_segoeui_16" },
    { "record_p", "·Tonaufnahme·", "lv_font_segoeui_16" },
    { "guard_p", "·Parküberwachung·", "lv_font_segoeui_16" },
    { "menu_hdr_p", "·Hochdynamischer Bereich·", "lv_font_segoeui_16" },
    { NULL, NULL, NULL }
};

static lv_i18n_phrase_t de_plurals_other[] = {

    { NULL, NULL, NULL }
};

static uint8_t de_plural_fn(int32_t num)
{
    uint32_t n = op_n(num);
    UNUSED(n);
    uint32_t i = op_i(n);
    UNUSED(i);
    uint32_t v = op_v(n);
    UNUSED(v);

    if ((i == 1 && v == 0)) {
        return LV_I18N_PLURAL_TYPE_ONE;
    }
    return LV_I18N_PLURAL_TYPE_OTHER;
}

static const lv_i18n_lang_t de_lang = {
    .locale_name = "de",
    .singulars = de_singulars,
    .plurals[LV_I18N_PLURAL_TYPE_OTHER] = de_plurals_other,
    .locale_plural_fn = de_plural_fn
};
static lv_i18n_phrase_t fr_singulars[] = {
    { "funkey4", "preset", "lv_font_segoeui_16" },
    { "funkey5", "preset", "lv_font_segoeui_16" },
    { "funkey6", "preset", "lv_font_segoeui_16" },
    { "funkey7", "preset", "lv_font_segoeui_16" },
    { "suplanguage", "Français", "lv_font_segoeui_16" },
    { "lcdprotect", "Écran de veille", "lv_font_segoeui_16" },
    { "poweroff", "Arrêt automatique", "lv_font_segoeui_16" },
    { "frequency", "Fréquence de la source lumineuse", "lv_font_segoeui_16" },
    { "speaker", "Son des touches", "lv_font_segoeui_16" },
    { "language", "Paramètres de langue", "lv_font_segoeui_16" },
    { "software", "Numéro de version", "lv_font_segoeui_16" },
    { "carnum", "Numéro de plaque d'immatriculation", "lv_font_segoeui_16" },
    { "roadline", "Dérapage de voie", "lv_font_segoeui_16" },
    { "lamp", "Phare", "lv_font_segoeui_16" },
    { "formatting", "Formatage", "lv_font_segoeui_16" },
    { "reset", "Paramètres par défaut", "lv_font_segoeui_16" },
    { "date", "Date et heure", "lv_font_segoeui_16" },
    { "close", "Fermer", "lv_font_segoeui_16" },
    { "open", "Ouvrir", "lv_font_segoeui_16" },
    { "subpagewarning0", "Avertissement\nCliquer pour confirmer la suppression de toutes les données", "lv_font_segoeui_24" },
    { "subpagewarning1", "Avertissement\nPas de carte mémoire", "lv_font_segoeui_24" },
    { "subpagewarning2", "Avertissement\nRestaurer les paramètres d'usine", "lv_font_segoeui_24" },
    { "YES", "Confirmer", "lv_font_segoeui_16" },
    { "CANCEL", "Annuler", "lv_font_segoeui_16" },
    { "shoot", "Mode de prise de vue", "lv_font_segoeui_16" },
    { "dealy10s", "Minuterie de 10 secondes", "lv_font_segoeui_16" },
    { "dealy5s", "Minuterie de 5 secondes", "lv_font_segoeui_16" },
    { "dealy2s", "Minuterie de 2 secondes", "lv_font_segoeui_16" },
    { "nodealy", "Photo unique", "lv_font_segoeui_16" },
    { "standard", "Standard", "lv_font_segoeui_16" },
    { "pool", "Économique", "lv_font_segoeui_16" },
    { "high", "Haute qualité", "lv_font_segoeui_16" },
    { "strong", "Fort", "lv_font_segoeui_16" },
    { "soft", "Doux", "lv_font_segoeui_16" },
    { "mono", "Noir et blanc", "lv_font_segoeui_16" },
    { "Nostalgia", "Sépia", "lv_font_segoeui_16" },
    { "acuity", "Aiguiseur d'image", "lv_font_segoeui_16" },
    { "sunshine", "Lumière du jour", "lv_font_segoeui_16" },
    { "cloudy", "Temps nuageux", "lv_font_segoeui_16" },
    { "fluolamp", "Lumière fluorescente", "lv_font_segoeui_16" },
    { "default", "Par défaut", "lv_font_segoeui_16" },
    { "resolution", "Résolution", "lv_font_segoeui_16" },
    { "shots", "Prise de vue en série", "lv_font_segoeui_16" },
    { "quality", "Qualité d'image", "lv_font_segoeui_16" },
    { "sharpness", "Aiguiseur d'image", "lv_font_segoeui_16" },
    { "awb", "Balance des blancs", "lv_font_segoeui_16" },
    { "color", "Couleur", "lv_font_segoeui_16" },
    { "exposure", "Correction d'exposition", "lv_font_segoeui_16" },
    { "handshake", "Stabilisation de l'appareil photo", "lv_font_segoeui_16" },
    { "preview", "Aperçu rapide", "lv_font_segoeui_16" },
    { "doublerec", "Enregistrement à double vue", "lv_font_segoeui_16" },
    { "cycrec", "Enregistrement en boucle", "lv_font_segoeui_16" },
    { "gaprec", "Vidéo accélérée", "lv_font_segoeui_16" },
    { "motion", "Détection de mouvement", "lv_font_segoeui_16" },
    { "gsensor", "Capteur de gravité", "lv_font_segoeui_16" },
    { "record", "Enregistrement audio", "lv_font_segoeui_16" },
    { "guard", "Surveillance de stationnement", "lv_font_segoeui_16" },
    { "Lsensitive", "Basse sensibilité", "lv_font_segoeui_16" },
    { "Msensitive", "Sensibilité moyenne", "lv_font_segoeui_16" },
    { "Hsensitive", "Haute sensibilité", "lv_font_segoeui_16" },
    { "tung", "Lampe à incandescence", "lv_font_segoeui_16" },
    { "sysprompt", "Êtes-vous prêt?", "lv_font_segoeui_16" },
    { "lowpow", "Faible niveau de batterie", "lv_font_segoeui_16" },
    { "nofile", "Aucun fichier", "lv_font_segoeui_16" },
    { "nosd", "Carte SD non insérée", "lv_font_segoeui_16" },
    { "nocamera", "La caméra a perdu la connexion", "lv_font_segoeui_16" },
    { "fileerr", "Fichier corrompu", "lv_font_segoeui_16" },
    { "format_succ", "Formatage réussi!", "lv_font_segoeui_16" },
    { "sys_reset", "Restauration des paramètres d'usine réussi!", "lv_font_segoeui_16" },
    { "format_failed", "Formatage échoué!", "lv_font_segoeui_16" },
    { "sys_reset_failed", "Restauration des paramètres d'usine échoué!", "lv_font_segoeui_16" },
    { "subpagewarning3", "Version: JL V1.0.0", "lv_font_segoeui_24" },
    { "update_tips", "Ne débrancher pas pendant la mise à jour", "lv_font_segoeui_16" },
    { "line_drift_horizon", "Veuillez déplacer vers l'horizon", "lv_font_segoeui_16" },
    { "line_drift_car", "Veuillez déplacer vers l'avant du véhicule", "lv_font_segoeui_16" },
    { "cancel", "Annuler", "lv_font_segoeui_16" },
    { "ensure", "Confirmer", "lv_font_segoeui_16" },
    { "sd_update", "Souhaitez-vous mettre à jour la carte SD?", "lv_font_segoeui_16" },
    { "Mon", "Lundi", "lv_font_segoeui_16" },
    { "Tue", "Mardi", "lv_font_segoeui_16" },
    { "Wed", "Mercredi", "lv_font_segoeui_16" },
    { "Thu", "Jeudi", "lv_font_segoeui_16" },
    { "Fir", "Vendredi", "lv_font_segoeui_16" },
    { "Sat", "Samedi", "lv_font_segoeui_16" },
    { "Sun", "Dimanche", "lv_font_segoeui_16" },
    { "del_file", "Souhaitez-vous supprimer le fichier sélectionné?", "lv_font_segoeui_16" },
    { "lock_file", "Souhaitez-vous verrouiller/déverrouiller le fichier sélectionné?", "lv_font_segoeui_16" },
    { "unlock_file", "Souhaitez-vous déverrouiller le fichier sélectionné?", "lv_font_segoeui_16" },
    { "unlock_all", "Souhaitez-vous déverrouiller tous les fichiers?", "lv_font_segoeui_16" },
    { "file_is_lock", "Fichier verrouillé", "lv_font_segoeui_16" },
    { "del_all", "Souhaitez-vous supprimer tous les fichiers?", "lv_font_segoeui_16" },
    { "lock_all", "Souhaitez-vous verrouiller tous les fichiers?", "lv_font_segoeui_16" },
    { "fs_err", "État anormal de la carte TF", "lv_font_segoeui_16" },
    { "gap_err", "Veuillez désactiver la vidéo accélérée!", "lv_font_segoeui_16" },
    { "being_formatted", "Formatage en cours...", "lv_font_segoeui_16" },
    { "car_record", "Enregistrement de voyage", "lv_font_segoeui_16" },
    { "grellra", "Album vidéo", "lv_font_segoeui_16" },
    { "sys_setting", "Paramètres de fonction", "lv_font_segoeui_16" },
    { "wifi", "WIFI", "lv_font_segoeui_16" },
    { "no_open_wifi", "WIFI non activé", "lv_font_segoeui_16" },
    { "click_out", "Cliquer n'importe où pour quitter", "lv_font_segoeui_16" },
    { "setting_title", "·Paramètres du système·", "lv_font_segoeui_16" },
    { "menu_wifi", "WIFI", "lv_font_segoeui_16" },
    { "wait", "Veuillez patienter...", "lv_font_segoeui_16" },
    { "min1", "1 minute", "lv_font_segoeui_16" },
    { "min3", "3 minutes", "lv_font_segoeui_16" },
    { "min10", "10 minutes", "lv_font_segoeui_16" },
    { "date_label", "Étiquette de date", "lv_font_segoeui_16" },
    { "car_set", "Paramètres de plaque d'immatriculation", "lv_font_segoeui_16" },
    { "back_insert", "Pas de détection arrière", "lv_font_segoeui_16" },
    { "roller_select", "Veuillez sélectionner avec les boutons Mode et Menu pour naviguer", "lv_font_segoeui_16" },
    { "off_10_sec", "L'appareil s'éteindra dans 10 secondes", "lv_font_segoeui_16" },
    { "voi_num", "Volume de l'appareil", "lv_font_segoeui_16" },
    { "sub_low", "Bas", "lv_font_segoeui_16" },
    { "sub_middle", "Moyen", "lv_font_segoeui_16" },
    { "sub_high", "Haut", "lv_font_segoeui_16" },
    { "min5", "5 minutes", "lv_font_segoeui_16" },
    { "menu_hdr", "Haute gamme dynamique", "lv_font_segoeui_16" },
    { "lan_russin", "русск", "lv_font_segoeui_16" },
    { "lcdprotect_p", "·Écran de veille·", "lv_font_segoeui_16" },
    { "poweroff_p", "·Arrêt automatique·", "lv_font_segoeui_16" },
    { "frequency_p", "·Fréquence de la source lumineuse·", "lv_font_segoeui_16" },
    { "speaker_p", "·Son des touches·", "lv_font_segoeui_16" },
    { "language_p", "·Paramètres de langue·", "lv_font_segoeui_16" },
    { "software_p", "·Numéro de version·", "lv_font_segoeui_16" },
    { "carnum_p", "·Numéro de plaque d'immatriculation·", "lv_font_segoeui_16" },
    { "roadline_p", "·Dérapage de voie·", "lv_font_segoeui_16" },
    { "lamp_p", "·Phare·", "lv_font_segoeui_16" },
    { "formatting_p", "·Formatage·", "lv_font_segoeui_16" },
    { "reset_p", "·Paramètres par défaut·", "lv_font_segoeui_16" },
    { "date_p", "·Date et heure·", "lv_font_segoeui_16" },
    { "close_p", "·Fermer·", "lv_font_segoeui_16" },
    { "open_p", "·Ouvrir·", "lv_font_segoeui_16" },
    { "min1_p", "·1 minute·", "lv_font_segoeui_16" },
    { "min3_p", "·3 minutes·", "lv_font_segoeui_16" },
    { "min10_p", "·10 minutes·", "lv_font_segoeui_16" },
    { "date_label_p", "·Étiquette de date·", "lv_font_segoeui_16" },
    { "car_set_p", "·Paramètres de plaque d'immatriculation·", "lv_font_segoeui_16" },
    { "shoot_p", "·Mode de prise de vue·", "lv_font_segoeui_16" },
    { "resolution_p", "·Résolution·", "lv_font_segoeui_16" },
    { "shots_p", "·Prise de vue en série·", "lv_font_segoeui_16" },
    { "quality_p", "·Qualité d'image·", "lv_font_segoeui_16" },
    { "sharpness_p", "·Aiguiseur d'image·", "lv_font_segoeui_16" },
    { "awb_p", "·Balance des blancs·", "lv_font_segoeui_16" },
    { "color_p", "·Couleur·", "lv_font_segoeui_16" },
    { "exposure_p", "·Correction d'exposition·", "lv_font_segoeui_16" },
    { "handshake_p", "·Stabilisation de l'appareil photo·", "lv_font_segoeui_16" },
    { "preview_p", "·Aperçu rapide·", "lv_font_segoeui_16" },
    { "doublerec_p", "·Enregistrement à double vue·", "lv_font_segoeui_16" },
    { "cycrec_p", "·Enregistrement en boucle·", "lv_font_segoeui_16" },
    { "gaprec_p", "·Vidéo accélérée·", "lv_font_segoeui_16" },
    { "motion_p", "·Détection de mouvement·", "lv_font_segoeui_16" },
    { "gsensor_p", "·Capteur de gravité·", "lv_font_segoeui_16" },
    { "record_p", "·Enregistrement audio·", "lv_font_segoeui_16" },
    { "guard_p", "·Surveillance de stationnement·", "lv_font_segoeui_16" },
    { "menu_hdr_p", "·Haute gamme dynamique·", "lv_font_segoeui_16" },
    { NULL, NULL, NULL }
};

static lv_i18n_phrase_t fr_plurals_other[] = {

    { NULL, NULL, NULL }
};

static uint8_t fr_plural_fn(int32_t num)
{
    uint32_t n = op_n(num);
    UNUSED(n);
    uint32_t i = op_i(n);
    UNUSED(i);
    uint32_t v = op_v(n);
    UNUSED(v);

    if ((i == 1 && v == 0)) {
        return LV_I18N_PLURAL_TYPE_ONE;
    }
    return LV_I18N_PLURAL_TYPE_OTHER;
}

static const lv_i18n_lang_t fr_lang = {
    .locale_name = "fr",
    .singulars = fr_singulars,
    .plurals[LV_I18N_PLURAL_TYPE_OTHER] = fr_plurals_other,
    .locale_plural_fn = fr_plural_fn
};
static lv_i18n_phrase_t ko_singulars[] = {
    { "funkey4", "preset", "lv_font_malgungothic_16" },
    { "funkey5", "preset", "lv_font_malgungothic_16" },
    { "funkey6", "preset", "lv_font_malgungothic_16" },
    { "funkey7", "preset", "lv_font_malgungothic_16" },
    { "suplanguage", "한국어", "lv_font_malgungothic_16" },
    { "lcdprotect", "화면 보호기", "lv_font_malgungothic_16" },
    { "poweroff", "자동 종료", "lv_font_malgungothic_16" },
    { "frequency", "광원 주파수", "lv_font_malgungothic_16" },
    { "speaker", "버튼 소리", "lv_font_malgungothic_16" },
    { "language", "언어 설정", "lv_font_malgungothic_16" },
    { "software", "버전 번호", "lv_font_malgungothic_16" },
    { "carnum", "차량 번호", "lv_font_malgungothic_16" },
    { "roadline", "차선 이탈", "lv_font_malgungothic_16" },
    { "lamp", "전조등", "lv_font_malgungothic_16" },
    { "formatting", "포맷", "lv_font_malgungothic_16" },
    { "reset", "기본 설정", "lv_font_malgungothic_16" },
    { "date", "날짜와 시간", "lv_font_malgungothic_16" },
    { "close", "닫기", "lv_font_malgungothic_16" },
    { "open", "열기", "lv_font_malgungothic_16" },
    { "subpagewarning0", "경고\n모든 데이터 삭제 확인을 클릭하십시오", "lv_font_malgungothic_24" },
    { "subpagewarning1", "경고\n메모리 카드 없음", "lv_font_malgungothic_24" },
    { "subpagewarning2", "경고\n공장 초기화", "lv_font_malgungothic_24" },
    { "YES", "확인", "lv_font_malgungothic_16" },
    { "CANCEL", "취소", "lv_font_malgungothic_16" },
    { "shoot", "촬영 모드", "lv_font_malgungothic_16" },
    { "dealy10s", "10초 타이머", "lv_font_malgungothic_16" },
    { "dealy5s", "5초 타이머", "lv_font_malgungothic_16" },
    { "dealy2s", "2초 타이머", "lv_font_malgungothic_16" },
    { "nodealy", "단일 촬영", "lv_font_malgungothic_16" },
    { "standard", "표준", "lv_font_malgungothic_16" },
    { "pool", "경제", "lv_font_malgungothic_16" },
    { "high", "고품질", "lv_font_malgungothic_16" },
    { "strong", "강렬", "lv_font_malgungothic_16" },
    { "soft", "부드러움", "lv_font_malgungothic_16" },
    { "mono", "흑백", "lv_font_malgungothic_16" },
    { "Nostalgia", "레트로", "lv_font_malgungothic_16" },
    { "acuity", "이미지 선명도", "lv_font_malgungothic_16" },
    { "sunshine", "일광", "lv_font_malgungothic_16" },
    { "cloudy", "흐림", "lv_font_malgungothic_16" },
    { "fluolamp", "형광등", "lv_font_malgungothic_16" },
    { "default", "기본", "lv_font_malgungothic_16" },
    { "resolution", "해상도", "lv_font_malgungothic_16" },
    { "shots", "연속 촬영", "lv_font_malgungothic_16" },
    { "quality", "이미지 품질", "lv_font_malgungothic_16" },
    { "sharpness", "이미지 선명도", "lv_font_malgungothic_16" },
    { "awb", "화이트 밸런스", "lv_font_malgungothic_16" },
    { "color", "색상", "lv_font_malgungothic_16" },
    { "exposure", "노출 보정", "lv_font_malgungothic_16" },
    { "handshake", "손떨림 방지", "lv_font_malgungothic_16" },
    { "preview", "빠른 미리보기", "lv_font_malgungothic_16" },
    { "doublerec", "이중 녹화", "lv_font_malgungothic_16" },
    { "cycrec", "순환 녹화", "lv_font_malgungothic_16" },
    { "gaprec", "타임랩스 녹화", "lv_font_malgungothic_16" },
    { "motion", "동작 감지", "lv_font_malgungothic_16" },
    { "gsensor", "중력 감지", "lv_font_malgungothic_16" },
    { "record", "녹음", "lv_font_malgungothic_16" },
    { "guard", "주차 모니터링", "lv_font_malgungothic_16" },
    { "Lsensitive", "저 감도", "lv_font_malgungothic_16" },
    { "Msensitive", "중 감도", "lv_font_malgungothic_16" },
    { "Hsensitive", "고 감도", "lv_font_malgungothic_16" },
    { "tung", "텅스텐 등", "lv_font_malgungothic_16" },
    { "sysprompt", "준비됐었나요~", "lv_font_malgungothic_16" },
    { "lowpow", "배터리 부족", "lv_font_malgungothic_16" },
    { "nofile", "파일 없음", "lv_font_malgungothic_16" },
    { "nosd", "SD 카드 미삽입", "lv_font_malgungothic_16" },
    { "nocamera", "카메라 연결 끊김", "lv_font_malgungothic_16" },
    { "fileerr", "파일 손상", "lv_font_malgungothic_16" },
    { "format_succ", "포맷 성공!", "lv_font_malgungothic_16" },
    { "sys_reset", "공장 초기화 성공!", "lv_font_malgungothic_16" },
    { "format_failed", "포맷 실패!", "lv_font_malgungothic_16" },
    { "sys_reset_failed", "공장 초기화 실패!", "lv_font_malgungothic_16" },
    { "subpagewarning3", "버전: JL V1.0.0", "lv_font_malgungothic_24" },
    { "update_tips", "전원 끄지 마세요, 업그레이드 중입니다", "lv_font_malgungothic_16" },
    { "line_drift_horizon", "지평선으로 이동하십시오", "lv_font_malgungothic_16" },
    { "line_drift_car", "전면으로 이동하십시오", "lv_font_malgungothic_16" },
    { "cancel", "취소", "lv_font_malgungothic_16" },
    { "ensure", "확인", "lv_font_malgungothic_16" },
    { "sd_update", "SD 카드 업그레이드를 진행하시겠습니까?", "lv_font_malgungothic_16" },
    { "Mon", "월요일", "lv_font_malgungothic_16" },
    { "Tue", "화요일", "lv_font_malgungothic_16" },
    { "Wed", "수요일", "lv_font_malgungothic_16" },
    { "Thu", "목요일", "lv_font_malgungothic_16" },
    { "Fir", "금요일", "lv_font_malgungothic_16" },
    { "Sat", "토요일", "lv_font_malgungothic_16" },
    { "Sun", "일요일", "lv_font_malgungothic_16" },
    { "del_file", "선택한 파일을 삭제하시겠습니까?", "lv_font_malgungothic_16" },
    { "lock_file", "선택한 파일을 잠금/잠금 해제하시겠습니까?", "lv_font_malgungothic_16" },
    { "unlock_file", "선택한 파일의 잠금을 해제하시겠습니까?", "lv_font_malgungothic_16" },
    { "unlock_all", "모든 파일의 잠금을 해제하시겠습니까?", "lv_font_malgungothic_16" },
    { "file_is_lock", "파일이 잠금되었습니다", "lv_font_malgungothic_16" },
    { "del_all", "모든 파일을 삭제하시겠습니까?", "lv_font_malgungothic_16" },
    { "lock_all", "모든 파일을 잠금하시겠습니까?", "lv_font_malgungothic_16" },
    { "fs_err", "TF 카드 이상 상태", "lv_font_malgungothic_16" },
    { "gap_err", "타임랩스 녹화를 종료하십시오!", "lv_font_malgungothic_16" },
    { "being_formatted", "포맷 중입니다...", "lv_font_malgungothic_16" },
    { "car_record", "주행 녹화", "lv_font_malgungothic_16" },
    { "grellra", "비디오 앨범", "lv_font_malgungothic_16" },
    { "sys_setting", "기능 설정", "lv_font_malgungothic_16" },
    { "wifi", "와이파이", "lv_font_malgungothic_16" },
    { "no_open_wifi", "와이파이 미연결", "lv_font_malgungothic_16" },
    { "click_out", "아무 곳이나 클릭하여 종료", "lv_font_malgungothic_16" },
    { "setting_title", "·시스템 설정·", "lv_font_malgungothic_16" },
    { "menu_wifi", "와이파이", "lv_font_malgungothic_16" },
    { "wait", "잠시만 기다려 주십시오...", "lv_font_malgungothic_16" },
    { "min1", "1분", "lv_font_malgungothic_16" },
    { "min3", "3분", "lv_font_malgungothic_16" },
    { "min10", "10분", "lv_font_malgungothic_16" },
    { "date_label", "날짜 표시", "lv_font_malgungothic_16" },
    { "car_set", "차량 번호 설정", "lv_font_malgungothic_16" },
    { "back_insert", "후방 미감지", "lv_font_malgungothic_16" },
    { "roller_select", "모드 및 메뉴 버튼을 눌러 상하 선택", "lv_font_malgungothic_16" },
    { "off_10_sec", "기기가 10초 후 종료됩니다", "lv_font_malgungothic_16" },
    { "voi_num", "디바이스 볼륨", "lv_font_malgungothic_16" },
    { "sub_low", "낮음", "lv_font_malgungothic_16" },
    { "sub_middle", "중간", "lv_font_malgungothic_16" },
    { "sub_high", "높음", "lv_font_malgungothic_16" },
    { "min5", "5분", "lv_font_malgungothic_16" },
    { "menu_hdr", "고다이나믹레인지", "lv_font_malgungothic_16" },
    { "lan_russin", "русск", "lv_font_malgungothic_16" },
    { "lcdprotect_p", "·화면 보호기·", "lv_font_malgungothic_16" },
    { "poweroff_p", "·자동 종료·", "lv_font_malgungothic_16" },
    { "frequency_p", "·광원 주파수·", "lv_font_malgungothic_16" },
    { "speaker_p", "·버튼 소리·", "lv_font_malgungothic_16" },
    { "language_p", "·언어 설정·", "lv_font_malgungothic_16" },
    { "software_p", "·버전 번호·", "lv_font_malgungothic_16" },
    { "carnum_p", "·차량 번호·", "lv_font_malgungothic_16" },
    { "roadline_p", "·차선 이탈·", "lv_font_malgungothic_16" },
    { "lamp_p", "·전조등·", "lv_font_malgungothic_16" },
    { "formatting_p", "·포맷·", "lv_font_malgungothic_16" },
    { "reset_p", "·기본 설정·", "lv_font_malgungothic_16" },
    { "date_p", "·날짜와 시간·", "lv_font_malgungothic_16" },
    { "close_p", "·닫기·", "lv_font_malgungothic_16" },
    { "open_p", "·열기·", "lv_font_malgungothic_16" },
    { "min1_p", "·1분·", "lv_font_malgungothic_16" },
    { "min3_p", "·3분·", "lv_font_malgungothic_16" },
    { "min10_p", "·10분·", "lv_font_malgungothic_16" },
    { "date_label_p", "·날짜 표시·", "lv_font_malgungothic_16" },
    { "car_set_p", "·차량 번호 설정·", "lv_font_malgungothic_16" },
    { "shoot_p", "·촬영 모드·", "lv_font_malgungothic_16" },
    { "resolution_p", "·해상도·", "lv_font_malgungothic_16" },
    { "shots_p", "·연속 촬영·", "lv_font_malgungothic_16" },
    { "quality_p", "·이미지 품질·", "lv_font_malgungothic_16" },
    { "sharpness_p", "·이미지 선명도·", "lv_font_malgungothic_16" },
    { "awb_p", "·화이트 밸런스·", "lv_font_malgungothic_16" },
    { "color_p", "·색상·", "lv_font_malgungothic_16" },
    { "exposure_p", "·노출 보정·", "lv_font_malgungothic_16" },
    { "handshake_p", "·손떨림 방지·", "lv_font_malgungothic_16" },
    { "preview_p", "·빠른 미리보기·", "lv_font_malgungothic_16" },
    { "doublerec_p", "·이중 녹화·", "lv_font_malgungothic_16" },
    { "cycrec_p", "·순환 녹화·", "lv_font_malgungothic_16" },
    { "gaprec_p", "·타임랩스 녹화·", "lv_font_malgungothic_16" },
    { "motion_p", "·동작 감지·", "lv_font_malgungothic_16" },
    { "gsensor_p", "·중력 감지·", "lv_font_malgungothic_16" },
    { "record_p", "·녹음·", "lv_font_malgungothic_16" },
    { "guard_p", "·주차 모니터링·", "lv_font_malgungothic_16" },
    { "menu_hdr_p", "·고다이나믹레인지·", "lv_font_malgungothic_16" },
    { NULL, NULL, NULL }
};

static lv_i18n_phrase_t ko_plurals_other[] = {

    { NULL, NULL, NULL }
};

static uint8_t ko_plural_fn(int32_t num)
{
    uint32_t n = op_n(num);
    UNUSED(n);
    uint32_t i = op_i(n);
    UNUSED(i);
    uint32_t v = op_v(n);
    UNUSED(v);

    if ((i == 1 && v == 0)) {
        return LV_I18N_PLURAL_TYPE_ONE;
    }
    return LV_I18N_PLURAL_TYPE_OTHER;
}

static const lv_i18n_lang_t ko_lang = {
    .locale_name = "ko",
    .singulars = ko_singulars,
    .plurals[LV_I18N_PLURAL_TYPE_OTHER] = ko_plurals_other,
    .locale_plural_fn = ko_plural_fn
};
static lv_i18n_phrase_t ja_singulars[] = {
    { "funkey4", "preset", "lv_font_ms_gothic_16" },
    { "funkey5", "preset", "lv_font_ms_gothic_16" },
    { "funkey6", "preset", "lv_font_ms_gothic_16" },
    { "funkey7", "preset", "lv_font_ms_gothic_16" },
    { "suplanguage", "日本語", "lv_font_fangsong_16" },
    { "lcdprotect", "スクリーンセーバー", "lv_font_fangsong_16" },
    { "poweroff", "自動シャットダウン", "lv_font_fangsong_16" },
    { "frequency", "光源周波数", "lv_font_fangsong_16" },
    { "speaker", "ボタン音", "lv_font_fangsong_16" },
    { "language", "言語設定", "lv_font_fangsong_16" },
    { "software", "バージョン番号", "lv_font_fangsong_16" },
    { "carnum", "車両番号", "lv_font_fangsong_16" },
    { "roadline", "車線逸脱", "lv_font_fangsong_16" },
    { "lamp", "ヘッドライト", "lv_font_fangsong_16" },
    { "formatting", "フォーマット", "lv_font_fangsong_16" },
    { "reset", "デフォルト設定", "lv_font_fangsong_16" },
    { "date", "日付と時間", "lv_font_fangsong_16" },
    { "close", "閉じる", "lv_font_fangsong_16" },
    { "open", "開く", "lv_font_fangsong_16" },
    { "subpagewarning0", "警告\nクリックしてすべてのデータを削除確認", "lv_font_fangsong_24" },
    { "subpagewarning1", "警告\nメモリカードなし", "lv_font_fangsong_24" },
    { "subpagewarning2", "警告\n工場出荷状態に復元", "lv_font_fangsong_24" },
    { "YES", "確認", "lv_font_fangsong_16" },
    { "CANCEL", "キャンセル", "lv_font_fangsong_16" },
    { "shoot", "撮影モード", "lv_font_fangsong_16" },
    { "dealy10s", "10秒タイマー", "lv_font_fangsong_16" },
    { "dealy5s", "5秒タイマー", "lv_font_fangsong_16" },
    { "dealy2s", "2秒タイマー", "lv_font_fangsong_16" },
    { "nodealy", "単写", "lv_font_fangsong_16" },
    { "standard", "標準", "lv_font_fangsong_16" },
    { "pool", "エコノミー", "lv_font_fangsong_16" },
    { "high", "高品質", "lv_font_fangsong_16" },
    { "strong", "強い", "lv_font_fangsong_16" },
    { "soft", "やわらかい", "lv_font_fangsong_16" },
    { "mono", "モノクロ", "lv_font_fangsong_16" },
    { "Nostalgia", "レトロ", "lv_font_fangsong_16" },
    { "acuity", "画像の鮮明度", "lv_font_fangsong_16" },
    { "sunshine", "日光", "lv_font_fangsong_16" },
    { "cloudy", "曇り", "lv_font_fangsong_16" },
    { "fluolamp", "蛍光灯", "lv_font_fangsong_16" },
    { "default", "デフォルト", "lv_font_fangsong_16" },
    { "resolution", "解像度", "lv_font_fangsong_16" },
    { "shots", "連写", "lv_font_fangsong_16" },
    { "quality", "画像品質", "lv_font_fangsong_16" },
    { "sharpness", "画像の鮮明度", "lv_font_fangsong_16" },
    { "awb", "ホワイトバランス", "lv_font_fangsong_16" },
    { "color", "カラー", "lv_font_fangsong_16" },
    { "exposure", "露出補正", "lv_font_fangsong_16" },
    { "handshake", "手ぶれ防止", "lv_font_fangsong_16" },
    { "preview", "クイックプレビュー", "lv_font_fangsong_16" },
    { "doublerec", "ダブル録画", "lv_font_fangsong_16" },
    { "cycrec", "ループ録画", "lv_font_fangsong_16" },
    { "gaprec", "タイムラプス録画", "lv_font_fangsong_16" },
    { "motion", "動体検出", "lv_font_fangsong_16" },
    { "gsensor", "重力センサー", "lv_font_fangsong_16" },
    { "record", "録音", "lv_font_fangsong_16" },
    { "guard", "駐車監視", "lv_font_fangsong_16" },
    { "Lsensitive", "低感度", "lv_font_fangsong_16" },
    { "Msensitive", "中感度", "lv_font_fangsong_16" },
    { "Hsensitive", "高感度", "lv_font_fangsong_16" },
    { "tung", "タングステンランプ", "lv_font_fangsong_16" },
    { "sysprompt", "準備はいいですか～", "lv_font_fangsong_16" },
    { "lowpow", "バッテリー残量不足", "lv_font_fangsong_16" },
    { "nofile", "ファイルなし", "lv_font_fangsong_16" },
    { "nosd", "SDカード未挿入", "lv_font_fangsong_16" },
    { "nocamera", "カメラ接続切れ", "lv_font_fangsong_16" },
    { "fileerr", "ファイル破損", "lv_font_fangsong_16" },
    { "format_succ", "フォーマット成功！", "lv_font_fangsong_16" },
    { "sys_reset", "工場出荷状態に復元成功！", "lv_font_fangsong_16" },
    { "format_failed", "フォーマット失敗！", "lv_font_fangsong_16" },
    { "sys_reset_failed", "工場出荷状態に復元失敗！", "lv_font_fangsong_16" },
    { "subpagewarning3", "バージョン: JL V1.0.0", "lv_font_fangsong_24" },
    { "update_tips", "電源を切らないでください、アップグレード中", "lv_font_fangsong_16" },
    { "line_drift_horizon", "地平線まで移動してください", "lv_font_fangsong_16" },
    { "line_drift_car", "車の前方まで移動してください", "lv_font_fangsong_16" },
    { "cancel", "キャンセル", "lv_font_fangsong_16" },
    { "ensure", "確定", "lv_font_fangsong_16" },
    { "sd_update", "SDカードのアップグレードをしますか？", "lv_font_fangsong_16" },
    { "Mon", "月曜日", "lv_font_fangsong_16" },
    { "Tue", "火曜日", "lv_font_fangsong_16" },
    { "Wed", "水曜日", "lv_font_fangsong_16" },
    { "Thu", "木曜日", "lv_font_fangsong_16" },
    { "Fir", "金曜日", "lv_font_fangsong_16" },
    { "Sat", "土曜日", "lv_font_fangsong_16" },
    { "Sun", "日曜日", "lv_font_fangsong_16" },
    { "del_file", "選択したファイルを削除しますか？", "lv_font_fangsong_16" },
    { "lock_file", "選択したファイルをロック/アンロックしますか？", "lv_font_fangsong_16" },
    { "unlock_file", "選択したファイルのロックを解除しますか？", "lv_font_fangsong_16" },
    { "unlock_all", "すべてのファイルのロックを解除しますか？", "lv_font_fangsong_16" },
    { "file_is_lock", "ファイルはすでにロックされています", "lv_font_fangsong_16" },
    { "del_all", "すべてのファイルを削除しますか？", "lv_font_fangsong_16" },
    { "lock_all", "すべてのファイルをロックしますか？", "lv_font_fangsong_16" },
    { "fs_err", "TFカード異常状態", "lv_font_fangsong_16" },
    { "gap_err", "タイムラプス録画を終了してください！", "lv_font_fangsong_16" },
    { "being_formatted", "フォーマット中です...", "lv_font_fangsong_16" },
    { "car_record", "ドライブレコーダー", "lv_font_fangsong_16" },
    { "grellra", "ビデオアルバム", "lv_font_fangsong_16" },
    { "sys_setting", "機能設定", "lv_font_fangsong_16" },
    { "wifi", "WIFI", "lv_font_fangsong_16" },
    { "no_open_wifi", "WIFI未接続", "lv_font_fangsong_16" },
    { "click_out", "どこでもクリックして終了", "lv_font_fangsong_16" },
    { "setting_title", "・システム設定・", "lv_font_ms_gothic_16" },
    { "menu_wifi", "WIFI", "lv_font_fangsong_16" },
    { "wait", "お待ちください...", "lv_font_fangsong_16" },
    { "min1", "1分", "lv_font_fangsong_16" },
    { "min3", "3分", "lv_font_fangsong_16" },
    { "min10", "10分", "lv_font_fangsong_16" },
    { "date_label", "日付ラベル", "lv_font_fangsong_16" },
    { "car_set", "車両番号設定", "lv_font_fangsong_16" },
    { "back_insert", "後方未検出", "lv_font_fangsong_16" },
    { "roller_select", "モードとメニューボタンを押して上下選択", "lv_font_fangsong_16" },
    { "off_10_sec", "機器は10秒後にシャットダウンします", "lv_font_fangsong_16" },
    { "voi_num", "デバイスボリューム", "lv_font_fangsong_16" },
    { "sub_low", "低", "lv_font_fangsong_16" },
    { "sub_middle", "中", "lv_font_fangsong_16" },
    { "sub_high", "高", "lv_font_fangsong_16" },
    { "min5", "5分", "lv_font_fangsong_16" },
    { "menu_hdr", "ハイダイナミックレンジ", "lv_font_fangsong_16" },
    { "lan_russin", "русск", "lv_font_fangsong_16" },
    { "lcdprotect_p", "・スクリーンセーバー・", "lv_font_ms_gothic_16" },
    { "poweroff_p", "・自動シャットダウン・", "lv_font_ms_gothic_16" },
    { "frequency_p", "・光源周波数・", "lv_font_ms_gothic_16" },
    { "speaker_p", "・ボタン音・", "lv_font_ms_gothic_16" },
    { "language_p", "・言語設定・", "lv_font_ms_gothic_16" },
    { "software_p", "・バージョン番号・", "lv_font_ms_gothic_16" },
    { "carnum_p", "・車両番号・", "lv_font_ms_gothic_16" },
    { "roadline_p", "・車線逸脱・", "lv_font_ms_gothic_16" },
    { "lamp_p", "・ヘッドライト・", "lv_font_ms_gothic_16" },
    { "formatting_p", "・フォーマット・", "lv_font_ms_gothic_16" },
    { "reset_p", "・デフォルト設定・", "lv_font_ms_gothic_16" },
    { "date_p", "・日付と時間・", "lv_font_ms_gothic_16" },
    { "close_p", "・閉じる", "lv_font_ms_gothic_16" },
    { "open_p", "・開く", "lv_font_ms_gothic_16" },
    { "min1_p", "・1分・", "lv_font_ms_gothic_16" },
    { "min3_p", "・3分・", "lv_font_ms_gothic_16" },
    { "min10_p", "・10分・", "lv_font_ms_gothic_16" },
    { "date_label_p", "・日付ラベル・", "lv_font_ms_gothic_16" },
    { "car_set_p", "・車両番号設定・", "lv_font_ms_gothic_16" },
    { "shoot_p", "・撮影モード・", "lv_font_ms_gothic_16" },
    { "resolution_p", "・解像度・", "lv_font_ms_gothic_16" },
    { "shots_p", "・連写・", "lv_font_ms_gothic_16" },
    { "quality_p", "・画像品質・", "lv_font_ms_gothic_16" },
    { "sharpness_p", "・画像の鮮明度・", "lv_font_ms_gothic_16" },
    { "awb_p", "・ホワイトバランス・", "lv_font_ms_gothic_16" },
    { "color_p", "・カラー・", "lv_font_ms_gothic_16" },
    { "exposure_p", "・露出補正・", "lv_font_ms_gothic_16" },
    { "handshake_p", "・手ぶれ防止・", "lv_font_ms_gothic_16" },
    { "preview_p", "・クイックプレビュー・", "lv_font_ms_gothic_16" },
    { "doublerec_p", "・ダブル録画・", "lv_font_ms_gothic_16" },
    { "cycrec_p", "・ループ録画・", "lv_font_ms_gothic_16" },
    { "gaprec_p", "・タイムラプス録画・", "lv_font_ms_gothic_16" },
    { "motion_p", "・動体検出・", "lv_font_ms_gothic_16" },
    { "gsensor_p", "・重力センサー・", "lv_font_ms_gothic_16" },
    { "record_p", "・録音・", "lv_font_ms_gothic_16" },
    { "guard_p", "・駐車監視・", "lv_font_ms_gothic_16" },
    { "menu_hdr_p", "・ハイダイナミックレンジ・", "lv_font_ms_gothic_16" },
    { NULL, NULL, NULL }
};

static lv_i18n_phrase_t ja_plurals_other[] = {

    { NULL, NULL, NULL }
};

static uint8_t ja_plural_fn(int32_t num)
{
    uint32_t n = op_n(num);
    UNUSED(n);
    uint32_t i = op_i(n);
    UNUSED(i);
    uint32_t v = op_v(n);
    UNUSED(v);

    if ((i == 1 && v == 0)) {
        return LV_I18N_PLURAL_TYPE_ONE;
    }
    return LV_I18N_PLURAL_TYPE_OTHER;
}

static const lv_i18n_lang_t ja_lang = {
    .locale_name = "ja",
    .singulars = ja_singulars,
    .plurals[LV_I18N_PLURAL_TYPE_OTHER] = ja_plurals_other,
    .locale_plural_fn = ja_plural_fn
};
static lv_i18n_phrase_t es_singulars[] = {
    { "funkey4", "preset", "lv_font_segoeui_16" },
    { "funkey5", "preset", "lv_font_segoeui_16" },
    { "funkey6", "preset", "lv_font_segoeui_16" },
    { "funkey7", "preset", "lv_font_segoeui_16" },
    { "suplanguage", "Español", "lv_font_segoeui_16" },
    { "lcdprotect", "Protector de pantalla", "lv_font_segoeui_16" },
    { "poweroff", "Apagado automático", "lv_font_segoeui_16" },
    { "frequency", "Frecuencia de la fuente de luz", "lv_font_segoeui_16" },
    { "speaker", "Sonido de los botones", "lv_font_segoeui_16" },
    { "language", "Configuración de idioma", "lv_font_segoeui_16" },
    { "software", "Versión", "lv_font_segoeui_16" },
    { "carnum", "Número de matrícula", "lv_font_segoeui_16" },
    { "roadline", "Desviación de carril", "lv_font_segoeui_16" },
    { "lamp", "Luces delanteras", "lv_font_segoeui_16" },
    { "formatting", "Formatear", "lv_font_segoeui_16" },
    { "reset", "Configuración por defecto", "lv_font_segoeui_16" },
    { "date", "Fecha y hora", "lv_font_segoeui_16" },
    { "close", "Cerrar", "lv_font_segoeui_16" },
    { "open", "Abrir", "lv_font_segoeui_16" },
    { "subpagewarning0", "Advertencia\nPulsa para confirmar la eliminación de todos los datos", "lv_font_segoeui_24" },
    { "subpagewarning1", "Advertencia\nNo hay tarjeta de memoria", "lv_font_segoeui_24" },
    { "subpagewarning2", "Advertencia\nRestaurar configuración de fábrica", "lv_font_segoeui_24" },
    { "YES", "Confirmar", "lv_font_segoeui_16" },
    { "CANCEL", "Cancelar", "lv_font_segoeui_16" },
    { "shoot", "Modo de disparo", "lv_font_segoeui_16" },
    { "dealy10s", "Temporizador 10 segundos", "lv_font_segoeui_16" },
    { "dealy5s", "Temporizador 5 segundos", "lv_font_segoeui_16" },
    { "dealy2s", "Temporizador 2 segundos", "lv_font_segoeui_16" },
    { "nodealy", "Disparo simple", "lv_font_segoeui_16" },
    { "standard", "Estándar", "lv_font_segoeui_16" },
    { "pool", "Económico", "lv_font_segoeui_16" },
    { "high", "De alta calidad", "lv_font_segoeui_16" },
    { "strong", "Intenso", "lv_font_segoeui_16" },
    { "soft", "Suave", "lv_font_segoeui_16" },
    { "mono", "Blanco y negro", "lv_font_segoeui_16" },
    { "Nostalgia", "Retro", "lv_font_segoeui_16" },
    { "acuity", "Nitidez de la imagen", "lv_font_segoeui_16" },
    { "sunshine", "Luz solar", "lv_font_segoeui_16" },
    { "cloudy", "Nublado", "lv_font_segoeui_16" },
    { "fluolamp", "Luz fluorescente", "lv_font_segoeui_16" },
    { "default", "Por defecto", "lv_font_segoeui_16" },
    { "resolution", "Resolución", "lv_font_segoeui_16" },
    { "shots", "Disparo continuo", "lv_font_segoeui_16" },
    { "quality", "Calidad de la imagen", "lv_font_segoeui_16" },
    { "sharpness", "Nitidez de la imagen", "lv_font_segoeui_16" },
    { "awb", "Balance de blancos", "lv_font_segoeui_16" },
    { "color", "Color", "lv_font_segoeui_16" },
    { "exposure", "Compensación de exposición", "lv_font_segoeui_16" },
    { "handshake", "Antivibración", "lv_font_segoeui_16" },
    { "preview", "Vista previa rápida", "lv_font_segoeui_16" },
    { "doublerec", "Grabación dúplex", "lv_font_segoeui_16" },
    { "cycrec", "Grabación cíclica", "lv_font_segoeui_16" },
    { "gaprec", "Grabación de lapso de tiempo", "lv_font_segoeui_16" },
    { "motion", "Detección de movimiento", "lv_font_segoeui_16" },
    { "gsensor", "Sensor de gravedad", "lv_font_segoeui_16" },
    { "record", "Grabación de audio", "lv_font_segoeui_16" },
    { "guard", "Vigilancia de aparcamiento", "lv_font_segoeui_16" },
    { "Lsensitive", "Baja sensibilidad", "lv_font_segoeui_16" },
    { "Msensitive", "Sensibilidad media", "lv_font_segoeui_16" },
    { "Hsensitive", "Alta sensibilidad", "lv_font_segoeui_16" },
    { "tung", "Luz de tungsteno", "lv_font_segoeui_16" },
    { "sysprompt", "¿Estás listo? ~", "lv_font_segoeui_16" },
    { "lowpow", "Batería baja", "lv_font_segoeui_16" },
    { "nofile", "No hay archivos", "lv_font_segoeui_16" },
    { "nosd", "Tarjeta SD no insertada", "lv_font_segoeui_16" },
    { "nocamera", "Cámara desconectada", "lv_font_segoeui_16" },
    { "fileerr", "Archivo dañado", "lv_font_segoeui_16" },
    { "format_succ", "¡Formateo exitoso!", "lv_font_segoeui_16" },
    { "sys_reset", "¡Restauración de fábrica exitosa!", "lv_font_segoeui_16" },
    { "format_failed", "¡Formateo fallido!", "lv_font_segoeui_16" },
    { "sys_reset_failed", "¡Restauración de fábrica fallida!", "lv_font_segoeui_16" },
    { "subpagewarning3", "Versión: JL V1.0.0", "lv_font_segoeui_24" },
    { "update_tips", "No cortar la alimentación, actualizando", "lv_font_segoeui_16" },
    { "line_drift_horizon", "Mueva hacia el horizonte", "lv_font_segoeui_16" },
    { "line_drift_car", "Mueva hacia el frente del coche", "lv_font_segoeui_16" },
    { "cancel", "Cancelar", "lv_font_segoeui_16" },
    { "ensure", "Confirmar", "lv_font_segoeui_16" },
    { "sd_update", "¿Actualizar la tarjeta SD?", "lv_font_segoeui_16" },
    { "Mon", "Lunes", "lv_font_segoeui_16" },
    { "Tue", "Martes", "lv_font_segoeui_16" },
    { "Wed", "Miércoles", "lv_font_segoeui_16" },
    { "Thu", "Jueves", "lv_font_segoeui_16" },
    { "Fir", "Viernes", "lv_font_segoeui_16" },
    { "Sat", "Sábado", "lv_font_segoeui_16" },
    { "Sun", "Domingo", "lv_font_segoeui_16" },
    { "del_file", "¿Eliminar el archivo seleccionado?", "lv_font_segoeui_16" },
    { "lock_file", "¿Bloquear/desbloquear el archivo seleccionado?", "lv_font_segoeui_16" },
    { "unlock_file", "¿Desbloquear el archivo seleccionado?", "lv_font_segoeui_16" },
    { "unlock_all", "¿Desbloquear todos los archivos?", "lv_font_segoeui_16" },
    { "file_is_lock", "Archivo bloqueado", "lv_font_segoeui_16" },
    { "del_all", "¿Eliminar todos los archivos?", "lv_font_segoeui_16" },
    { "lock_all", "¿Bloquear todos los archivos?", "lv_font_segoeui_16" },
    { "fs_err", "Tarjeta TF en estado anormal", "lv_font_segoeui_16" },
    { "gap_err", "¡Cerrar grabación de lapso de tiempo!", "lv_font_segoeui_16" },
    { "being_formatted", "Formateando...", "lv_font_segoeui_16" },
    { "car_record", "Registro de conducción", "lv_font_segoeui_16" },
    { "grellra", "Álbum de videos", "lv_font_segoeui_16" },
    { "sys_setting", "Configuración de funciones", "lv_font_segoeui_16" },
    { "wifi", "WIFI", "lv_font_segoeui_16" },
    { "no_open_wifi", "WIFI no conectado", "lv_font_segoeui_16" },
    { "click_out", "Pulsa en cualquier lugar para salir", "lv_font_segoeui_16" },
    { "setting_title", "·Configuración del sistema·", "lv_font_segoeui_16" },
    { "menu_wifi", "WIFI", "lv_font_segoeui_16" },
    { "wait", "Espera un momento...", "lv_font_segoeui_16" },
    { "min1", "1 minuto", "lv_font_segoeui_16" },
    { "min3", "3 minutos", "lv_font_segoeui_16" },
    { "min10", "10 minutos", "lv_font_segoeui_16" },
    { "date_label", "Etiqueta de fecha", "lv_font_segoeui_16" },
    { "car_set", "Configuración de matrícula", "lv_font_segoeui_16" },
    { "back_insert", "No se detecta la cámara trasera", "lv_font_segoeui_16" },
    { "roller_select", "Pulsa los botones de modo y menú para seleccionar arriba y abajo", "lv_font_segoeui_16" },
    { "off_10_sec", "El dispositivo se apagará en 10 segundos", "lv_font_segoeui_16" },
    { "voi_num", "Volumen del dispositivo", "lv_font_segoeui_16" },
    { "sub_low", "Bajo", "lv_font_segoeui_16" },
    { "sub_middle", "Medio", "lv_font_segoeui_16" },
    { "sub_high", "Alto", "lv_font_segoeui_16" },
    { "min5", "5 minutos", "lv_font_segoeui_16" },
    { "menu_hdr", "Alto rango dinámico", "lv_font_segoeui_16" },
    { "lan_russin", "русск", "lv_font_segoeui_16" },
    { "lcdprotect_p", "·Protector de pantalla·", "lv_font_segoeui_16" },
    { "poweroff_p", "·Apagado automático·", "lv_font_segoeui_16" },
    { "frequency_p", "·Frecuencia de la fuente de luz·", "lv_font_segoeui_16" },
    { "speaker_p", "·Sonido de los botones·", "lv_font_segoeui_16" },
    { "language_p", "·Configuración de idioma·", "lv_font_segoeui_16" },
    { "software_p", "·Versión·", "lv_font_segoeui_16" },
    { "carnum_p", "·Número de matrícula·", "lv_font_segoeui_16" },
    { "roadline_p", "·Desviación de carril·", "lv_font_segoeui_16" },
    { "lamp_p", "·Luces delanteras·", "lv_font_segoeui_16" },
    { "formatting_p", "·Formatear·", "lv_font_segoeui_16" },
    { "reset_p", "·Configuración por defecto·", "lv_font_segoeui_16" },
    { "date_p", "·Fecha y hora·", "lv_font_segoeui_16" },
    { "close_p", "·Cerrar", "lv_font_segoeui_16" },
    { "open_p", "·Abrir", "lv_font_segoeui_16" },
    { "min1_p", "·1 minuto·", "lv_font_segoeui_16" },
    { "min3_p", "·3 minutos·", "lv_font_segoeui_16" },
    { "min10_p", "·10 minutos·", "lv_font_segoeui_16" },
    { "date_label_p", "·Etiqueta de fecha·", "lv_font_segoeui_16" },
    { "car_set_p", "·Configuración de matrícula·", "lv_font_segoeui_16" },
    { "shoot_p", "·Modo de disparo·", "lv_font_segoeui_16" },
    { "resolution_p", "·Resolución·", "lv_font_segoeui_16" },
    { "shots_p", "·Disparo continuo·", "lv_font_segoeui_16" },
    { "quality_p", "·Calidad de la imagen·", "lv_font_segoeui_16" },
    { "sharpness_p", "·Nitidez de la imagen·", "lv_font_segoeui_16" },
    { "awb_p", "·Balance de blancos·", "lv_font_segoeui_16" },
    { "color_p", "·Color·", "lv_font_segoeui_16" },
    { "exposure_p", "·Compensación de exposición·", "lv_font_segoeui_16" },
    { "handshake_p", "·Antivibración·", "lv_font_segoeui_16" },
    { "preview_p", "·Vista previa rápida·", "lv_font_segoeui_16" },
    { "doublerec_p", "·Grabación dúplex·", "lv_font_segoeui_16" },
    { "cycrec_p", "·Grabación cíclica·", "lv_font_segoeui_16" },
    { "gaprec_p", "·Grabación de lapso de tiempo·", "lv_font_segoeui_16" },
    { "motion_p", "·Detección de movimiento·", "lv_font_segoeui_16" },
    { "gsensor_p", "·Sensor de gravedad·", "lv_font_segoeui_16" },
    { "record_p", "·Grabación de audio·", "lv_font_segoeui_16" },
    { "guard_p", "·Vigilancia de aparcamiento·", "lv_font_segoeui_16" },
    { "menu_hdr_p", "·Alto rango dinámico·", "lv_font_segoeui_16" },
    { NULL, NULL, NULL }
};

static lv_i18n_phrase_t es_plurals_other[] = {

    { NULL, NULL, NULL }
};

static uint8_t es_plural_fn(int32_t num)
{
    uint32_t n = op_n(num);
    UNUSED(n);
    uint32_t i = op_i(n);
    UNUSED(i);
    uint32_t v = op_v(n);
    UNUSED(v);

    if ((i == 1 && v == 0)) {
        return LV_I18N_PLURAL_TYPE_ONE;
    }
    return LV_I18N_PLURAL_TYPE_OTHER;
}

static const lv_i18n_lang_t es_lang = {
    .locale_name = "es",
    .singulars = es_singulars,
    .plurals[LV_I18N_PLURAL_TYPE_OTHER] = es_plurals_other,
    .locale_plural_fn = es_plural_fn
};
static lv_i18n_phrase_t pt_singulars[] = {
    { "funkey4", "preset", "lv_font_segoeui_16" },
    { "funkey5", "preset", "lv_font_segoeui_16" },
    { "funkey6", "preset", "lv_font_segoeui_16" },
    { "funkey7", "preset", "lv_font_segoeui_16" },
    { "suplanguage", "Português", "lv_font_segoeui_16" },
    { "lcdprotect", "Proteção de tela", "lv_font_segoeui_16" },
    { "poweroff", "Desligamento automático", "lv_font_segoeui_16" },
    { "frequency", "Frequência de luz", "lv_font_segoeui_16" },
    { "speaker", "Som de botões", "lv_font_segoeui_16" },
    { "language", "Configurações de idioma", "lv_font_segoeui_16" },
    { "software", "Versão", "lv_font_segoeui_16" },
    { "carnum", "Número de placa", "lv_font_segoeui_16" },
    { "roadline", "Desvio de faixa", "lv_font_segoeui_16" },
    { "lamp", "Luzes dianteiras", "lv_font_segoeui_16" },
    { "formatting", "Formatar", "lv_font_segoeui_16" },
    { "reset", "Configurações padrão", "lv_font_segoeui_16" },
    { "date", "Data e hora", "lv_font_segoeui_16" },
    { "close", "Desligar", "lv_font_segoeui_16" },
    { "open", "Ligar", "lv_font_segoeui_16" },
    { "subpagewarning0", "Aviso\nClique para confirmar a exclusão de todos os dados", "lv_font_segoeui_24" },
    { "subpagewarning1", "Aviso\nSem cartão de memória", "lv_font_segoeui_24" },
    { "subpagewarning2", "Aviso\nRestaurar configurações de fábrica", "lv_font_segoeui_24" },
    { "YES", "Confirmar", "lv_font_segoeui_16" },
    { "CANCEL", "Cancelar", "lv_font_segoeui_16" },
    { "shoot", "Modo de captura", "lv_font_segoeui_16" },
    { "dealy10s", "Temporizador 10 segundos", "lv_font_segoeui_16" },
    { "dealy5s", "Temporizador 5 segundos", "lv_font_segoeui_16" },
    { "dealy2s", "Temporizador 2 segundos", "lv_font_segoeui_16" },
    { "nodealy", "Captura única", "lv_font_segoeui_16" },
    { "standard", "Padrão", "lv_font_segoeui_16" },
    { "pool", "Econômico", "lv_font_segoeui_16" },
    { "high", "Alta qualidade", "lv_font_segoeui_16" },
    { "strong", "Intenso", "lv_font_segoeui_16" },
    { "soft", "Suave", "lv_font_segoeui_16" },
    { "mono", "Preto e branco", "lv_font_segoeui_16" },
    { "Nostalgia", "Retro", "lv_font_segoeui_16" },
    { "acuity", "Nitidez de imagem", "lv_font_segoeui_16" },
    { "sunshine", "Sol", "lv_font_segoeui_16" },
    { "cloudy", "Nublado", "lv_font_segoeui_16" },
    { "fluolamp", "Lâmpada fluorescente", "lv_font_segoeui_16" },
    { "default", "Padrão", "lv_font_segoeui_16" },
    { "resolution", "Resolução", "lv_font_segoeui_16" },
    { "shots", "Captura contínua", "lv_font_segoeui_16" },
    { "quality", "Qualidade de imagem", "lv_font_segoeui_16" },
    { "sharpness", "Nitidez de imagem", "lv_font_segoeui_16" },
    { "awb", "Balanço de branco", "lv_font_segoeui_16" },
    { "color", "Cor", "lv_font_segoeui_16" },
    { "exposure", "Compensação de exposição", "lv_font_segoeui_16" },
    { "handshake", "Antivibração", "lv_font_segoeui_16" },
    { "preview", "Previsualização rápida", "lv_font_segoeui_16" },
    { "doublerec", "Gravação dupla", "lv_font_segoeui_16" },
    { "cycrec", "Gravação cíclica", "lv_font_segoeui_16" },
    { "gaprec", "Gravação em intervalos", "lv_font_segoeui_16" },
    { "motion", "Detecção de movimento", "lv_font_segoeui_16" },
    { "gsensor", "Sensor de gravidade", "lv_font_segoeui_16" },
    { "record", "Gravação de áudio", "lv_font_segoeui_16" },
    { "guard", "Vigilância de estacionamento", "lv_font_segoeui_16" },
    { "Lsensitive", "Baixa sensibilidade", "lv_font_segoeui_16" },
    { "Msensitive", "Sensibilidade média", "lv_font_segoeui_16" },
    { "Hsensitive", "Alta sensibilidade", "lv_font_segoeui_16" },
    { "tung", "Lâmpada de tungstênio", "lv_font_segoeui_16" },
    { "sysprompt", "Está pronto?~", "lv_font_segoeui_16" },
    { "lowpow", "Bateria baixa", "lv_font_segoeui_16" },
    { "nofile", "Sem arquivos", "lv_font_segoeui_16" },
    { "nosd", "Cartão SD não inserido", "lv_font_segoeui_16" },
    { "nocamera", "Câmera desconectada", "lv_font_segoeui_16" },
    { "fileerr", "Arquivo corrompido", "lv_font_segoeui_16" },
    { "format_succ", "Formatação bem sucedida!", "lv_font_segoeui_16" },
    { "sys_reset", "Restauração de fábrica bem sucedida!", "lv_font_segoeui_16" },
    { "format_failed", "Falha na formatação!", "lv_font_segoeui_16" },
    { "sys_reset_failed", "Falha na restauração de fábrica!", "lv_font_segoeui_16" },
    { "subpagewarning3", "Versão: JL V1.0.0", "lv_font_segoeui_24" },
    { "update_tips", "Não desligar, atualizando", "lv_font_segoeui_16" },
    { "line_drift_horizon", "Mover para o horizonte", "lv_font_segoeui_16" },
    { "line_drift_car", "Mover para a frente do carro", "lv_font_segoeui_16" },
    { "cancel", "Cancelar", "lv_font_segoeui_16" },
    { "ensure", "Confirmar", "lv_font_segoeui_16" },
    { "sd_update", "Atualizar cartão SD?", "lv_font_segoeui_16" },
    { "Mon", "Segunda-feira", "lv_font_segoeui_16" },
    { "Tue", "Terça-feira", "lv_font_segoeui_16" },
    { "Wed", "Quarta-feira", "lv_font_segoeui_16" },
    { "Thu", "Quinta-feira", "lv_font_segoeui_16" },
    { "Fir", "Sexta-feira", "lv_font_segoeui_16" },
    { "Sat", "Sábado", "lv_font_segoeui_16" },
    { "Sun", "Domingo", "lv_font_segoeui_16" },
    { "del_file", "Excluir arquivo selecionado?", "lv_font_segoeui_16" },
    { "lock_file", "Bloquear/desbloquear arquivo selecionado?", "lv_font_segoeui_16" },
    { "unlock_file", "Desbloquear arquivo selecionado?", "lv_font_segoeui_16" },
    { "unlock_all", "Desbloquear todos os arquivos?", "lv_font_segoeui_16" },
    { "file_is_lock", "Arquivo bloqueado", "lv_font_segoeui_16" },
    { "del_all", "Excluir todos os arquivos?", "lv_font_segoeui_16" },
    { "lock_all", "Bloquear todos os arquivos?", "lv_font_segoeui_16" },
    { "fs_err", "Cartão TF em estado anormal", "lv_font_segoeui_16" },
    { "gap_err", "Desligar gravação em intervalos!", "lv_font_segoeui_16" },
    { "being_formatted", "Formatando...", "lv_font_segoeui_16" },
    { "car_record", "Registro de condução", "lv_font_segoeui_16" },
    { "grellra", "Álbum de vídeos", "lv_font_segoeui_16" },
    { "sys_setting", "Configurações de função", "lv_font_segoeui_16" },
    { "wifi", "WIFI", "lv_font_segoeui_16" },
    { "no_open_wifi", "WIFI não conectado", "lv_font_segoeui_16" },
    { "click_out", "Clique em qualquer lugar para sair", "lv_font_segoeui_16" },
    { "setting_title", "·Configurações de sistema·", "lv_font_segoeui_16" },
    { "menu_wifi", "WIFI", "lv_font_segoeui_16" },
    { "wait", "Aguarde...", "lv_font_segoeui_16" },
    { "min1", "1 minuto", "lv_font_segoeui_16" },
    { "min3", "3 minutos", "lv_font_segoeui_16" },
    { "min10", "10 minutos", "lv_font_segoeui_16" },
    { "date_label", "Marca de data", "lv_font_segoeui_16" },
    { "car_set", "Configurações de placa", "lv_font_segoeui_16" },
    { "back_insert", "Câmera traseira não detectada", "lv_font_segoeui_16" },
    { "roller_select", "Use os botões de modo e menu para selecionar cima/baixo", "lv_font_segoeui_16" },
    { "off_10_sec", "O dispositivo desligará em 10 segundos", "lv_font_segoeui_16" },
    { "voi_num", "Volume do dispositivo", "lv_font_segoeui_16" },
    { "sub_low", "Baixo", "lv_font_segoeui_16" },
    { "sub_middle", "Médio", "lv_font_segoeui_16" },
    { "sub_high", "Alto", "lv_font_segoeui_16" },
    { "min5", "5 minutos", "lv_font_segoeui_16" },
    { "menu_hdr", "Alto alcance dinâmico", "lv_font_segoeui_16" },
    { "lan_russin", "русск", "lv_font_segoeui_16" },
    { "lcdprotect_p", "·Tela protegida·", "lv_font_segoeui_16" },
    { "poweroff_p", "·Desligamento automático·", "lv_font_segoeui_16" },
    { "frequency_p", "·Frequência de luz·", "lv_font_segoeui_16" },
    { "speaker_p", "·Som de botões·", "lv_font_segoeui_16" },
    { "language_p", "·Configurações de idioma·", "lv_font_segoeui_16" },
    { "software_p", "·Versão·", "lv_font_segoeui_16" },
    { "carnum_p", "·Número de placa·", "lv_font_segoeui_16" },
    { "roadline_p", "·Desvio de faixa·", "lv_font_segoeui_16" },
    { "lamp_p", "·Luzes dianteiras·", "lv_font_segoeui_16" },
    { "formatting_p", "·Formatar·", "lv_font_segoeui_16" },
    { "reset_p", "·Configurações padrão·", "lv_font_segoeui_16" },
    { "date_p", "·Data e hora·", "lv_font_segoeui_16" },
    { "close_p", "·Desligar", "lv_font_segoeui_16" },
    { "open_p", "·Ligar", "lv_font_segoeui_16" },
    { "min1_p", "·1 minuto·", "lv_font_segoeui_16" },
    { "min3_p", "·3 minutos·", "lv_font_segoeui_16" },
    { "min10_p", "·10 minutos·", "lv_font_segoeui_16" },
    { "date_label_p", "·Marca de data·", "lv_font_segoeui_16" },
    { "car_set_p", "·Configurações de placa·", "lv_font_segoeui_16" },
    { "shoot_p", "·Modo de captura·", "lv_font_segoeui_16" },
    { "resolution_p", "·Resolução·", "lv_font_segoeui_16" },
    { "shots_p", "·Captura contínua·", "lv_font_segoeui_16" },
    { "quality_p", "·Qualidade de imagem·", "lv_font_segoeui_16" },
    { "sharpness_p", "·Nitidez de imagem·", "lv_font_segoeui_16" },
    { "awb_p", "·Balanço de branco·", "lv_font_segoeui_16" },
    { "color_p", "·Cor·", "lv_font_segoeui_16" },
    { "exposure_p", "·Compensação de exposição·", "lv_font_segoeui_16" },
    { "handshake_p", "·Antivibração·", "lv_font_segoeui_16" },
    { "preview_p", "·Previsualização rápida·", "lv_font_segoeui_16" },
    { "doublerec_p", "·Gravação dupla·", "lv_font_segoeui_16" },
    { "cycrec_p", "·Gravação cíclica·", "lv_font_segoeui_16" },
    { "gaprec_p", "·Gravação em intervalos·", "lv_font_segoeui_16" },
    { "motion_p", "·Detecção de movimento·", "lv_font_segoeui_16" },
    { "gsensor_p", "·Sensor de gravidade·", "lv_font_segoeui_16" },
    { "record_p", "·Gravação de áudio·", "lv_font_segoeui_16" },
    { "guard_p", "·Vigilância de estacionamento·", "lv_font_segoeui_16" },
    { "menu_hdr_p", "·Alto alcance dinâmico·", "lv_font_segoeui_16" },
    { NULL, NULL, NULL }
};

static lv_i18n_phrase_t pt_plurals_other[] = {

    { NULL, NULL, NULL }
};

static uint8_t pt_plural_fn(int32_t num)
{
    uint32_t n = op_n(num);
    UNUSED(n);
    uint32_t i = op_i(n);
    UNUSED(i);
    uint32_t v = op_v(n);
    UNUSED(v);

    if ((i == 1 && v == 0)) {
        return LV_I18N_PLURAL_TYPE_ONE;
    }
    return LV_I18N_PLURAL_TYPE_OTHER;
}

static const lv_i18n_lang_t pt_lang = {
    .locale_name = "pt",
    .singulars = pt_singulars,
    .plurals[LV_I18N_PLURAL_TYPE_OTHER] = pt_plurals_other,
    .locale_plural_fn = pt_plural_fn
};
static lv_i18n_phrase_t cs_singulars[] = {
    { "funkey4", "preset", "lv_font_segoeui_16" },
    { "funkey5", "preset", "lv_font_segoeui_16" },
    { "funkey6", "preset", "lv_font_segoeui_16" },
    { "funkey7", "preset", "lv_font_segoeui_16" },
    { "suplanguage", "Čeština", "lv_font_segoeui_16" },
    { "lcdprotect", "Ochrana obrazovky", "lv_font_segoeui_16" },
    { "poweroff", "Automatické vypnutí", "lv_font_segoeui_16" },
    { "frequency", "Frekvence světla", "lv_font_segoeui_16" },
    { "speaker", "Zvuk tlačítek", "lv_font_segoeui_16" },
    { "language", "Jazykové nastavení", "lv_font_segoeui_16" },
    { "software", "Číslo verze", "lv_font_segoeui_16" },
    { "carnum", "Číslo SPZ", "lv_font_segoeui_16" },
    { "roadline", "Odchylka jízdního pruhu", "lv_font_segoeui_16" },
    { "lamp", "Přední světla", "lv_font_segoeui_16" },
    { "formatting", "Formatování", "lv_font_segoeui_16" },
    { "reset", "Výchozí nastavení", "lv_font_segoeui_16" },
    { "date", "Datum a čas", "lv_font_segoeui_16" },
    { "close", "Vypnout", "lv_font_segoeui_16" },
    { "open", "Zapnout", "lv_font_segoeui_16" },
    { "subpagewarning0", "Varování\nKliknutím potvrďte smazání všech dat", "lv_font_segoeui_24" },
    { "subpagewarning1", "Varování\nNení vložená paměťová karta", "lv_font_segoeui_24" },
    { "subpagewarning2", "Varování\nObnovení továrního nastavení", "lv_font_segoeui_24" },
    { "YES", "Potvrdit", "lv_font_segoeui_16" },
    { "CANCEL", "Zrušit", "lv_font_segoeui_16" },
    { "shoot", "Režim fotografování", "lv_font_segoeui_16" },
    { "dealy10s", "Časovač 10 sekund", "lv_font_segoeui_16" },
    { "dealy5s", "Časovač 5 sekund", "lv_font_segoeui_16" },
    { "dealy2s", "Časovač 2 sekundy", "lv_font_segoeui_16" },
    { "nodealy", "Jednotlivé foto", "lv_font_segoeui_16" },
    { "standard", "Standardní", "lv_font_segoeui_16" },
    { "pool", "Ekonomický", "lv_font_segoeui_16" },
    { "high", "Kvalitní", "lv_font_segoeui_16" },
    { "strong", "Intenzivní", "lv_font_segoeui_16" },
    { "soft", "Měkký", "lv_font_segoeui_16" },
    { "mono", "Černobílý", "lv_font_segoeui_16" },
    { "Nostalgia", "Retro", "lv_font_segoeui_16" },
    { "acuity", "Ostrost obrazu", "lv_font_segoeui_16" },
    { "sunshine", "Denní světlo", "lv_font_segoeui_16" },
    { "cloudy", "Zataženo", "lv_font_segoeui_16" },
    { "fluolamp", "Zářivka", "lv_font_segoeui_16" },
    { "default", "Výchozí", "lv_font_segoeui_16" },
    { "resolution", "Rozlišení", "lv_font_segoeui_16" },
    { "shots", "Sériové snímání", "lv_font_segoeui_16" },
    { "quality", "Kvalita obrazu", "lv_font_segoeui_16" },
    { "sharpness", "Ostrost obrazu", "lv_font_segoeui_16" },
    { "awb", "Vyvážení bílé", "lv_font_segoeui_16" },
    { "color", "Barva", "lv_font_segoeui_16" },
    { "exposure", "Kompenzace expozice", "lv_font_segoeui_16" },
    { "handshake", "Protiotřes", "lv_font_segoeui_16" },
    { "preview", "Rychlý náhled", "lv_font_segoeui_16" },
    { "doublerec", "Dvojité nahrávání", "lv_font_segoeui_16" },
    { "cycrec", "Cyklické nahrávání", "lv_font_segoeui_16" },
    { "gaprec", "Časosběrné nahrávání", "lv_font_segoeui_16" },
    { "motion", "Detekce pohybu", "lv_font_segoeui_16" },
    { "gsensor", "Senzor gravitace", "lv_font_segoeui_16" },
    { "record", "Nahrávání zvuku", "lv_font_segoeui_16" },
    { "guard", "Parkovací režim", "lv_font_segoeui_16" },
    { "Lsensitive", "Nízká citlivost", "lv_font_segoeui_16" },
    { "Msensitive", "Střední citlivost", "lv_font_segoeui_16" },
    { "Hsensitive", "Vysoká citlivost", "lv_font_segoeui_16" },
    { "tung", "Wolframová žárovka", "lv_font_segoeui_16" },
    { "sysprompt", "Jste připraveni?~", "lv_font_segoeui_16" },
    { "lowpow", "Nízká baterie", "lv_font_segoeui_16" },
    { "nofile", "Žádné soubory", "lv_font_segoeui_16" },
    { "nosd", "Karta SD není vložena", "lv_font_segoeui_16" },
    { "nocamera", "Kamera je offline", "lv_font_segoeui_16" },
    { "fileerr", "Poškozený soubor", "lv_font_segoeui_16" },
    { "format_succ", "Formatování úspěšné!", "lv_font_segoeui_16" },
    { "sys_reset", "Obnovení továrního nastavení úspěšné!", "lv_font_segoeui_16" },
    { "format_failed", "Formatování selhalo!", "lv_font_segoeui_16" },
    { "sys_reset_failed", "Obnovení továrního nastavení selhalo!", "lv_font_segoeui_16" },
    { "subpagewarning3", "Verze: JL V1.0.0", "lv_font_segoeui_24" },
    { "update_tips", "Nevypínejte, probíhá aktualizace", "lv_font_segoeui_16" },
    { "line_drift_horizon", "Přemístěte na obzor", "lv_font_segoeui_16" },
    { "line_drift_car", "Přemístěte na přední část vozu", "lv_font_segoeui_16" },
    { "cancel", "Zrušit", "lv_font_segoeui_16" },
    { "ensure", "Potvrdit", "lv_font_segoeui_16" },
    { "sd_update", "Aktualizovat kartu SD?", "lv_font_segoeui_16" },
    { "Mon", "Pondělí", "lv_font_segoeui_16" },
    { "Tue", "Úterý", "lv_font_segoeui_16" },
    { "Wed", "Středa", "lv_font_segoeui_16" },
    { "Thu", "Čtvrtek", "lv_font_segoeui_16" },
    { "Fir", "Pátek", "lv_font_segoeui_16" },
    { "Sat", "Sobota", "lv_font_segoeui_16" },
    { "Sun", "Neděle", "lv_font_segoeui_16" },
    { "del_file", "Smazat vybrané soubory?", "lv_font_segoeui_16" },
    { "lock_file", "Zamknout/odemknout vybrané soubory?", "lv_font_segoeui_16" },
    { "unlock_file", "Odemknout vybrané soubory?", "lv_font_segoeui_16" },
    { "unlock_all", "Odemknout všechny soubory?", "lv_font_segoeui_16" },
    { "file_is_lock", "Soubor je zamknutý", "lv_font_segoeui_16" },
    { "del_all", "Smazat všechny soubory?", "lv_font_segoeui_16" },
    { "lock_all", "Zamknout všechny soubory?", "lv_font_segoeui_16" },
    { "fs_err", "Abnormální stav karty TF", "lv_font_segoeui_16" },
    { "gap_err", "Vypněte časosběrné nahrávání!", "lv_font_segoeui_16" },
    { "being_formatted", "Probíhá formatování...", "lv_font_segoeui_16" },
    { "car_record", "Záznam jízdy", "lv_font_segoeui_16" },
    { "grellra", "Videoalbum", "lv_font_segoeui_16" },
    { "sys_setting", "Nastavení funkce", "lv_font_segoeui_16" },
    { "wifi", "WIFI", "lv_font_segoeui_16" },
    { "no_open_wifi", "WIFI není zapnuto", "lv_font_segoeui_16" },
    { "click_out", "Klikněte kamkoliv pro odchod", "lv_font_segoeui_16" },
    { "setting_title", "·Systémové nastavení·", "lv_font_segoeui_16" },
    { "menu_wifi", "WIFI", "lv_font_segoeui_16" },
    { "wait", "Prosím čekejte...", "lv_font_segoeui_16" },
    { "min1", "1 minuta", "lv_font_segoeui_16" },
    { "min3", "3 minuty", "lv_font_segoeui_16" },
    { "min10", "10 minut", "lv_font_segoeui_16" },
    { "date_label", "Značka data", "lv_font_segoeui_16" },
    { "car_set", "Nastavení SPZ", "lv_font_segoeui_16" },
    { "back_insert", "Zadní kamera nebyla detekována", "lv_font_segoeui_16" },
    { "roller_select", "Pro výběr použijte tlačítka módu a menu", "lv_font_segoeui_16" },
    { "off_10_sec", "Zařízení se vypne po 10 sekundách", "lv_font_segoeui_16" },
    { "voi_num", "Hlasitost zařízení", "lv_font_segoeui_16" },
    { "sub_low", "Nízká", "lv_font_segoeui_16" },
    { "sub_middle", "Střední", "lv_font_segoeui_16" },
    { "sub_high", "Vysoká", "lv_font_segoeui_16" },
    { "min5", "5 minut", "lv_font_segoeui_16" },
    { "menu_hdr", "Vysoký dynamický rozsah", "lv_font_segoeui_16" },
    { "lan_russin", "русск", "lv_font_segoeui_16" },
    { "lcdprotect_p", "·Ochrana obrazovky·", "lv_font_segoeui_16" },
    { "poweroff_p", "·Automatické vypnutí·", "lv_font_segoeui_16" },
    { "frequency_p", "·Frekvence světla·", "lv_font_segoeui_16" },
    { "speaker_p", "·Zvuk tlačítek·", "lv_font_segoeui_16" },
    { "language_p", "·Jazykové nastavení·", "lv_font_segoeui_16" },
    { "software_p", "·Číslo verze·", "lv_font_segoeui_16" },
    { "carnum_p", "·Číslo SPZ·", "lv_font_segoeui_16" },
    { "roadline_p", "·Odchylka jízdního pruhu·", "lv_font_segoeui_16" },
    { "lamp_p", "·Přední světla·", "lv_font_segoeui_16" },
    { "formatting_p", "·Formatování·", "lv_font_segoeui_16" },
    { "reset_p", "·Výchozí nastavení·", "lv_font_segoeui_16" },
    { "date_p", "·Datum a čas·", "lv_font_segoeui_16" },
    { "close_p", "·Vypnout", "lv_font_segoeui_16" },
    { "open_p", "·Zapnout", "lv_font_segoeui_16" },
    { "min1_p", "·1 minuta·", "lv_font_segoeui_16" },
    { "min3_p", "·3 minuty·", "lv_font_segoeui_16" },
    { "min10_p", "·10 minut·", "lv_font_segoeui_16" },
    { "date_label_p", "·Značka data·", "lv_font_segoeui_16" },
    { "car_set_p", "·Nastavení SPZ·", "lv_font_segoeui_16" },
    { "shoot_p", "·Režim fotografování·", "lv_font_segoeui_16" },
    { "resolution_p", "·Rozlišení·", "lv_font_segoeui_16" },
    { "shots_p", "·Sériové snímání·", "lv_font_segoeui_16" },
    { "quality_p", "·Kvalita obrazu·", "lv_font_segoeui_16" },
    { "sharpness_p", "·Ostrost obrazu·", "lv_font_segoeui_16" },
    { "awb_p", "·Vyvážení bílé·", "lv_font_segoeui_16" },
    { "color_p", "·Barva·", "lv_font_segoeui_16" },
    { "exposure_p", "·Kompenzace expozice·", "lv_font_segoeui_16" },
    { "handshake_p", "·Protiotřes·", "lv_font_segoeui_16" },
    { "preview_p", "·Rychlý náhled·", "lv_font_segoeui_16" },
    { "doublerec_p", "·Dvojité nahrávání·", "lv_font_segoeui_16" },
    { "cycrec_p", "·Cyklické nahrávání·", "lv_font_segoeui_16" },
    { "gaprec_p", "·Časosběrné nahrávání·", "lv_font_segoeui_16" },
    { "motion_p", "·Detekce pohybu·", "lv_font_segoeui_16" },
    { "gsensor_p", "·Senzor gravitace·", "lv_font_segoeui_16" },
    { "record_p", "·Nahrávání zvuku·", "lv_font_segoeui_16" },
    { "guard_p", "·Parkovací režim·", "lv_font_segoeui_16" },
    { "menu_hdr_p", "·Vysoký dynamický rozsah·", "lv_font_segoeui_16" },
    { NULL, NULL, NULL }
};

static lv_i18n_phrase_t cs_plurals_other[] = {

    { NULL, NULL, NULL }
};

static uint8_t cs_plural_fn(int32_t num)
{
    uint32_t n = op_n(num);
    UNUSED(n);
    uint32_t i = op_i(n);
    UNUSED(i);
    uint32_t v = op_v(n);
    UNUSED(v);

    if ((i == 1 && v == 0)) {
        return LV_I18N_PLURAL_TYPE_ONE;
    }
    return LV_I18N_PLURAL_TYPE_OTHER;
}

static const lv_i18n_lang_t cs_lang = {
    .locale_name = "cs",
    .singulars = cs_singulars,
    .plurals[LV_I18N_PLURAL_TYPE_OTHER] = cs_plurals_other,
    .locale_plural_fn = cs_plural_fn
};
static lv_i18n_phrase_t pl_singulars[] = {
    { "funkey4", "preset", "lv_font_segoeui_16" },
    { "funkey5", "preset", "lv_font_segoeui_16" },
    { "funkey6", "preset", "lv_font_segoeui_16" },
    { "funkey7", "preset", "lv_font_segoeui_16" },
    { "suplanguage", "Polski", "lv_font_segoeui_16" },
    { "lcdprotect", "Ekran osłonowy", "lv_font_segoeui_16" },
    { "poweroff", "Automatyczne wyłączenie", "lv_font_segoeui_16" },
    { "frequency", "Częstotliwość światła", "lv_font_segoeui_16" },
    { "speaker", "Dźwięk przycisków", "lv_font_segoeui_16" },
    { "language", "Ustawienia języka", "lv_font_segoeui_16" },
    { "software", "Numer wersji", "lv_font_segoeui_16" },
    { "carnum", "Numer tablicy rejestracyjnej", "lv_font_segoeui_16" },
    { "roadline", "Odchylenie z toru", "lv_font_segoeui_16" },
    { "lamp", "Światła przednie", "lv_font_segoeui_16" },
    { "formatting", "Formatowanie", "lv_font_segoeui_16" },
    { "reset", "Ustawienia domyślne", "lv_font_segoeui_16" },
    { "date", "Data i czas", "lv_font_segoeui_16" },
    { "close", "Wyłączyć", "lv_font_segoeui_16" },
    { "open", "Włączyć", "lv_font_segoeui_16" },
    { "subpagewarning0", "Ostrzeżenie\nKliknij, aby potwierdzić usunięcie wszystkich danych", "lv_font_segoeui_24" },
    { "subpagewarning1", "Ostrzeżenie\nBrak karty pamięci", "lv_font_segoeui_24" },
    { "subpagewarning2", "Ostrzeżenie\nPrzywrócenie fabrycznych ustawień", "lv_font_segoeui_24" },
    { "YES", "Potwierdź", "lv_font_segoeui_16" },
    { "CANCEL", "Anuluj", "lv_font_segoeui_16" },
    { "shoot", "Tryb fotografowania", "lv_font_segoeui_16" },
    { "dealy10s", "Zegar 10 sekund", "lv_font_segoeui_16" },
    { "dealy5s", "Zegar 5 sekund", "lv_font_segoeui_16" },
    { "dealy2s", "Zegar 2 sekundy", "lv_font_segoeui_16" },
    { "nodealy", "Jedno zdjęcie", "lv_font_segoeui_16" },
    { "standard", "Standardowy", "lv_font_segoeui_16" },
    { "pool", "Ekonomiczny", "lv_font_segoeui_16" },
    { "high", "Wysoka jakość", "lv_font_segoeui_16" },
    { "strong", "Intensywny", "lv_font_segoeui_16" },
    { "soft", "Łagodliwy", "lv_font_segoeui_16" },
    { "mono", "Czarno-biały", "lv_font_segoeui_16" },
    { "Nostalgia", "Retro", "lv_font_segoeui_16" },
    { "acuity", "Ostrość obrazu", "lv_font_segoeui_16" },
    { "sunshine", "Światło dzienne", "lv_font_segoeui_16" },
    { "cloudy", "Zachmurzenie", "lv_font_segoeui_16" },
    { "fluolamp", "Żarówka", "lv_font_segoeui_16" },
    { "default", "Domyślne", "lv_font_segoeui_16" },
    { "resolution", "Rozdzielczość", "lv_font_segoeui_16" },
    { "shots", "Seryjne zdjęcia", "lv_font_segoeui_16" },
    { "quality", "Jakość obrazu", "lv_font_segoeui_16" },
    { "sharpness", "Ostrość obrazu", "lv_font_segoeui_16" },
    { "awb", "Balans bieli", "lv_font_segoeui_16" },
    { "color", "Kolor", "lv_font_segoeui_16" },
    { "exposure", "Kompensacja ekspozycji", "lv_font_segoeui_16" },
    { "handshake", "Stabilizacja obrazu", "lv_font_segoeui_16" },
    { "preview", "Szybki podgląd", "lv_font_segoeui_16" },
    { "doublerec", "Nagranie dwukierunkowe", "lv_font_segoeui_16" },
    { "cycrec", "Nagranie cykliczne", "lv_font_segoeui_16" },
    { "gaprec", "Nagranie z czasopomiarem", "lv_font_segoeui_16" },
    { "motion", "Detekcja ruchu", "lv_font_segoeui_16" },
    { "gsensor", "Czujnik grawitacji", "lv_font_segoeui_16" },
    { "record", "Nagranie dźwięku", "lv_font_segoeui_16" },
    { "guard", "Ochrona parkingu", "lv_font_segoeui_16" },
    { "Lsensitive", "Niska czułość", "lv_font_segoeui_16" },
    { "Msensitive", "Średnia czułość", "lv_font_segoeui_16" },
    { "Hsensitive", "Wysoka czułość", "lv_font_segoeui_16" },
    { "tung", "Żarówka z wolframu", "lv_font_segoeui_16" },
    { "sysprompt", "Jesteś gotowy?~", "lv_font_segoeui_16" },
    { "lowpow", "Niska akumulatora", "lv_font_segoeui_16" },
    { "nofile", "Brak plików", "lv_font_segoeui_16" },
    { "nosd", "Karta SD nie jest włożona", "lv_font_segoeui_16" },
    { "nocamera", "Kamera straciła połączenie", "lv_font_segoeui_16" },
    { "fileerr", "Plik jest uszkodzony", "lv_font_segoeui_16" },
    { "format_succ", "Formatowanie zakończone sukcesem!", "lv_font_segoeui_16" },
    { "sys_reset", "Przywrócenie fabrycznych ustawień zakończone sukcesem!", "lv_font_segoeui_16" },
    { "format_failed", "Formatowanie nie powiodło się!", "lv_font_segoeui_16" },
    { "sys_reset_failed", "Przywrócenie fabrycznych ustawień nie powiodło się!", "lv_font_segoeui_16" },
    { "subpagewarning3", "Wersja: JL V1.0.0", "lv_font_segoeui_24" },
    { "update_tips", "Nie wyłączaj zasilania, trwa aktualizacja", "lv_font_segoeui_16" },
    { "line_drift_horizon", "Przenieś na poziom", "lv_font_segoeui_16" },
    { "line_drift_car", "Przenieś na przednią część samochodu", "lv_font_segoeui_16" },
    { "cancel", "Anuluj", "lv_font_segoeui_16" },
    { "ensure", "OK", "lv_font_segoeui_16" },
    { "sd_update", "Czy chcesz aktualizować kartę SD?", "lv_font_segoeui_16" },
    { "Mon", "Poniedziałek", "lv_font_segoeui_16" },
    { "Tue", "Wtorek", "lv_font_segoeui_16" },
    { "Wed", "Środa", "lv_font_segoeui_16" },
    { "Thu", "Czwartek", "lv_font_segoeui_16" },
    { "Fir", "Piątek", "lv_font_segoeui_16" },
    { "Sat", "Sobota", "lv_font_segoeui_16" },
    { "Sun", "Niedziela", "lv_font_segoeui_16" },
    { "del_file", "Czy chcesz usunąć wybrane pliki?", "lv_font_segoeui_16" },
    { "lock_file", "Czy chcesz zablokować/odblokować wybrane pliki?", "lv_font_segoeui_16" },
    { "unlock_file", "Czy chcesz odblokować wybrane pliki?", "lv_font_segoeui_16" },
    { "unlock_all", "Czy chcesz odblokować wszystkie pliki?", "lv_font_segoeui_16" },
    { "file_is_lock", "Plik jest zablokowany", "lv_font_segoeui_16" },
    { "del_all", "Czy chcesz usunąć wszystkie pliki?", "lv_font_segoeui_16" },
    { "lock_all", "Czy chcesz zablokować wszystkie pliki?", "lv_font_segoeui_16" },
    { "fs_err", "Nieprawidłowy stan karty TF", "lv_font_segoeui_16" },
    { "gap_err", "Proszę wyłączyć nagranie z czasopomiarem!", "lv_font_segoeui_16" },
    { "being_formatted", "Trwa formatowanie...", "lv_font_segoeui_16" },
    { "car_record", "Nagranie jazdy", "lv_font_segoeui_16" },
    { "grellra", "Album filmów", "lv_font_segoeui_16" },
    { "sys_setting", "Ustawienia funkcji", "lv_font_segoeui_16" },
    { "wifi", "WIFI", "lv_font_segoeui_16" },
    { "no_open_wifi", "WIFI nie jest włączone", "lv_font_segoeui_16" },
    { "click_out", "Kliknij dowolne miejsce, aby wyjść", "lv_font_segoeui_16" },
    { "setting_title", "·Ustawienia systemowe·", "lv_font_segoeui_16" },
    { "menu_wifi", "WIFI", "lv_font_segoeui_16" },
    { "wait", "Proszę czekać...", "lv_font_segoeui_16" },
    { "min1", "1 minuta", "lv_font_segoeui_16" },
    { "min3", "3 minuty", "lv_font_segoeui_16" },
    { "min10", "10 minut", "lv_font_segoeui_16" },
    { "date_label", "Znacznik daty", "lv_font_segoeui_16" },
    { "car_set", "Ustawienia tablicy rejestracyjnej", "lv_font_segoeui_16" },
    { "back_insert", "Nie wykryto tylnej kamery", "lv_font_segoeui_16" },
    { "roller_select", "Proszę użyć przycisków menu i trybu do wyboru", "lv_font_segoeui_16" },
    { "off_10_sec", "Urządzenie zostanie wyłączone po 10 sekundach", "lv_font_segoeui_16" },
    { "voi_num", "Głośność urządzenia", "lv_font_segoeui_16" },
    { "sub_low", "Niska", "lv_font_segoeui_16" },
    { "sub_middle", "Średnia", "lv_font_segoeui_16" },
    { "sub_high", "Wysoka", "lv_font_segoeui_16" },
    { "min5", "5 minut", "lv_font_segoeui_16" },
    { "menu_hdr", "Wysoki zakres dynamiczny", "lv_font_segoeui_16" },
    { "lan_russin", "русск", "lv_font_segoeui_16" },
    { "lcdprotect_p", "·Ekran osłonowy·", "lv_font_segoeui_16" },
    { "poweroff_p", "·Automatyczne wyłączenie·", "lv_font_segoeui_16" },
    { "frequency_p", "·Częstotliwość światła·", "lv_font_segoeui_16" },
    { "speaker_p", "·Dźwięk przycisków·", "lv_font_segoeui_16" },
    { "language_p", "·Ustawienia języka·", "lv_font_segoeui_16" },
    { "software_p", "·Numer wersji·", "lv_font_segoeui_16" },
    { "carnum_p", "·Numer tablicy rejestracyjnej·", "lv_font_segoeui_16" },
    { "roadline_p", "·Odchylenie z toru·", "lv_font_segoeui_16" },
    { "lamp_p", "·Światła przednie·", "lv_font_segoeui_16" },
    { "formatting_p", "·Formatowanie·", "lv_font_segoeui_16" },
    { "reset_p", "·Ustawienia domyślne·", "lv_font_segoeui_16" },
    { "date_p", "·Data i czas·", "lv_font_segoeui_16" },
    { "close_p", "·Wyłączyć", "lv_font_segoeui_16" },
    { "open_p", "·Włączyć", "lv_font_segoeui_16" },
    { "min1_p", "·1 minuta·", "lv_font_segoeui_16" },
    { "min3_p", "·3 minuty·", "lv_font_segoeui_16" },
    { "min10_p", "·10 minut·", "lv_font_segoeui_16" },
    { "date_label_p", "·Znacznik daty·", "lv_font_segoeui_16" },
    { "car_set_p", "·Ustawienia tablicy rejestracyjnej·", "lv_font_segoeui_16" },
    { "shoot_p", "·Tryb fotografowania·", "lv_font_segoeui_16" },
    { "resolution_p", "·Rozdzielczość·", "lv_font_segoeui_16" },
    { "shots_p", "·Seryjne zdjęcia·", "lv_font_segoeui_16" },
    { "quality_p", "·Jakość obrazu·", "lv_font_segoeui_16" },
    { "sharpness_p", "·Ostrość obrazu·", "lv_font_segoeui_16" },
    { "awb_p", "·Balans bieli·", "lv_font_segoeui_16" },
    { "color_p", "·Kolor·", "lv_font_segoeui_16" },
    { "exposure_p", "·Kompensacja ekspozycji·", "lv_font_segoeui_16" },
    { "handshake_p", "·Stabilizacja obrazu·", "lv_font_segoeui_16" },
    { "preview_p", "·Szybki podgląd·", "lv_font_segoeui_16" },
    { "doublerec_p", "·Nagranie dwukierunkowe·", "lv_font_segoeui_16" },
    { "cycrec_p", "·Nagranie cykliczne·", "lv_font_segoeui_16" },
    { "gaprec_p", "·Nagranie z czasopomiarem·", "lv_font_segoeui_16" },
    { "motion_p", "·Detekcja ruchu·", "lv_font_segoeui_16" },
    { "gsensor_p", "·Czujnik grawitacji·", "lv_font_segoeui_16" },
    { "record_p", "·Nagranie dźwięku·", "lv_font_segoeui_16" },
    { "guard_p", "·Ochrona parkingu·", "lv_font_segoeui_16" },
    { "menu_hdr_p", "·Wysoki zakres dynamiczny·", "lv_font_segoeui_16" },
    { NULL, NULL, NULL }
};

static lv_i18n_phrase_t pl_plurals_other[] = {

    { NULL, NULL, NULL }
};

static uint8_t pl_plural_fn(int32_t num)
{
    uint32_t n = op_n(num);
    UNUSED(n);
    uint32_t i = op_i(n);
    UNUSED(i);
    uint32_t v = op_v(n);
    UNUSED(v);

    if ((i == 1 && v == 0)) {
        return LV_I18N_PLURAL_TYPE_ONE;
    }
    return LV_I18N_PLURAL_TYPE_OTHER;
}

static const lv_i18n_lang_t pl_lang = {
    .locale_name = "pl",
    .singulars = pl_singulars,
    .plurals[LV_I18N_PLURAL_TYPE_OTHER] = pl_plurals_other,
    .locale_plural_fn = pl_plural_fn
};
static lv_i18n_phrase_t it_singulars[] = {
    { "funkey4", "preset", "lv_font_segoeui_16" },
    { "funkey5", "preset", "lv_font_segoeui_16" },
    { "funkey6", "preset", "lv_font_segoeui_16" },
    { "funkey7", "preset", "lv_font_segoeui_16" },
    { "suplanguage", "Italiano", "lv_font_segoeui_16" },
    { "lcdprotect", "Protezione schermo", "lv_font_segoeui_16" },
    { "poweroff", "Spegnimento automatico", "lv_font_segoeui_16" },
    { "frequency", "Frequenza della luce", "lv_font_segoeui_16" },
    { "speaker", "Suono dei pulsanti", "lv_font_segoeui_16" },
    { "language", "Impostazioni lingua", "lv_font_segoeui_16" },
    { "software", "Numero di versione", "lv_font_segoeui_16" },
    { "carnum", "Numero di targa", "lv_font_segoeui_16" },
    { "roadline", "Deviazione dalla corsia", "lv_font_segoeui_16" },
    { "lamp", "Fari anteriori", "lv_font_segoeui_16" },
    { "formatting", "Formattazione", "lv_font_segoeui_16" },
    { "reset", "Impostazioni predefinite", "lv_font_segoeui_16" },
    { "date", "Data e ora", "lv_font_segoeui_16" },
    { "close", "Chiudi", "lv_font_segoeui_16" },
    { "open", "Apri", "lv_font_segoeui_16" },
    { "subpagewarning0", "Avviso\nConferma per cancellare tutti i dati", "lv_font_segoeui_24" },
    { "subpagewarning1", "Avviso\nNessuna scheda di memoria", "lv_font_segoeui_24" },
    { "subpagewarning2", "Avviso\nRipristino impostazioni di fabbrica", "lv_font_segoeui_24" },
    { "YES", "Conferma", "lv_font_segoeui_16" },
    { "CANCEL", "Annulla", "lv_font_segoeui_16" },
    { "shoot", "Modalità di scatto", "lv_font_segoeui_16" },
    { "dealy10s", "Temporizzatore 10 secondi", "lv_font_segoeui_16" },
    { "dealy5s", "Temporizzatore 5 secondi", "lv_font_segoeui_16" },
    { "dealy2s", "Temporizzatore 2 secondi", "lv_font_segoeui_16" },
    { "nodealy", "Scatto singolo", "lv_font_segoeui_16" },
    { "standard", "Standard", "lv_font_segoeui_16" },
    { "pool", "Economico", "lv_font_segoeui_16" },
    { "high", "Alta qualità", "lv_font_segoeui_16" },
    { "strong", "Intenso", "lv_font_segoeui_16" },
    { "soft", "Morbido", "lv_font_segoeui_16" },
    { "mono", "Bianco e nero", "lv_font_segoeui_16" },
    { "Nostalgia", "Retro", "lv_font_segoeui_16" },
    { "acuity", "Nitidezza immagine", "lv_font_segoeui_16" },
    { "sunshine", "Luce naturale", "lv_font_segoeui_16" },
    { "cloudy", "Tempo nuvoloso", "lv_font_segoeui_16" },
    { "fluolamp", "Fluorescente", "lv_font_segoeui_16" },
    { "default", "Predefinito", "lv_font_segoeui_16" },
    { "resolution", "Risoluzione", "lv_font_segoeui_16" },
    { "shots", "Scatto seriale", "lv_font_segoeui_16" },
    { "quality", "Qualità immagine", "lv_font_segoeui_16" },
    { "sharpness", "Nitidezza immagine", "lv_font_segoeui_16" },
    { "awb", "Bilanciamento del bianco", "lv_font_segoeui_16" },
    { "color", "Colore", "lv_font_segoeui_16" },
    { "exposure", "Compensazione dell'esposizione", "lv_font_segoeui_16" },
    { "handshake", "Antivibrazione", "lv_font_segoeui_16" },
    { "preview", "Anteprima rapida", "lv_font_segoeui_16" },
    { "doublerec", "Registrazione a due vie", "lv_font_segoeui_16" },
    { "cycrec", "Registrazione ciclica", "lv_font_segoeui_16" },
    { "gaprec", "Time-lapse", "lv_font_segoeui_16" },
    { "motion", "Rilevamento movimento", "lv_font_segoeui_16" },
    { "gsensor", "Sensore di accelerazione", "lv_font_segoeui_16" },
    { "record", "Registrazione audio", "lv_font_segoeui_16" },
    { "guard", "Sorveglianza parcheggio", "lv_font_segoeui_16" },
    { "Lsensitive", "Bassa sensibilità", "lv_font_segoeui_16" },
    { "Msensitive", "Sensibilità media", "lv_font_segoeui_16" },
    { "Hsensitive", "Alta sensibilità", "lv_font_segoeui_16" },
    { "tung", "Lampada a tungsteno", "lv_font_segoeui_16" },
    { "sysprompt", "Pronto?~", "lv_font_segoeui_16" },
    { "lowpow", "Batteria scarsa", "lv_font_segoeui_16" },
    { "nofile", "Nessun file", "lv_font_segoeui_16" },
    { "nosd", "Scheda SD non inserita", "lv_font_segoeui_16" },
    { "nocamera", "La telecamera ha perso la connessione", "lv_font_segoeui_16" },
    { "fileerr", "Il file è danneggiato", "lv_font_segoeui_16" },
    { "format_succ", "Formattazione completata con successo!", "lv_font_segoeui_16" },
    { "sys_reset", "Ripristino impostazioni di fabbrica completato con successo!", "lv_font_segoeui_16" },
    { "format_failed", "Formattazione fallita!", "lv_font_segoeui_16" },
    { "sys_reset_failed", "Ripristino impostazioni di fabbrica fallito!", "lv_font_segoeui_16" },
    { "subpagewarning3", "Versione: JL V1.0.0", "lv_font_segoeui_24" },
    { "update_tips", "Non spegnere durante l'aggiornamento", "lv_font_segoeui_16" },
    { "line_drift_horizon", "Sposta all'orizzontale", "lv_font_segoeui_16" },
    { "line_drift_car", "Sposta verso la parte anteriore", "lv_font_segoeui_16" },
    { "cancel", "Annulla", "lv_font_segoeui_16" },
    { "ensure", "OK", "lv_font_segoeui_16" },
    { "sd_update", "Vuoi aggiornare la scheda SD?", "lv_font_segoeui_16" },
    { "Mon", "Lunedì", "lv_font_segoeui_16" },
    { "Tue", "Martedì", "lv_font_segoeui_16" },
    { "Wed", "Mercoledì", "lv_font_segoeui_16" },
    { "Thu", "Giovedì", "lv_font_segoeui_16" },
    { "Fir", "Venerdì", "lv_font_segoeui_16" },
    { "Sat", "Sabato", "lv_font_segoeui_16" },
    { "Sun", "Domenica", "lv_font_segoeui_16" },
    { "del_file", "Vuoi eliminare i file selezionati?", "lv_font_segoeui_16" },
    { "lock_file", "Vuoi bloccare/sbloccare i file selezionati?", "lv_font_segoeui_16" },
    { "unlock_file", "Vuoi sbloccare i file selezionati?", "lv_font_segoeui_16" },
    { "unlock_all", "Vuoi sbloccare tutti i file?", "lv_font_segoeui_16" },
    { "file_is_lock", "Il file è bloccato", "lv_font_segoeui_16" },
    { "del_all", "Vuoi eliminare tutti i file?", "lv_font_segoeui_16" },
    { "lock_all", "Vuoi bloccare tutti i file?", "lv_font_segoeui_16" },
    { "fs_err", "Stato anomalo della scheda TF", "lv_font_segoeui_16" },
    { "gap_err", "Si prega di disattivare il time-lapse!", "lv_font_segoeui_16" },
    { "being_formatted", "Sta formattando...", "lv_font_segoeui_16" },
    { "car_record", "Registrazione viaggio", "lv_font_segoeui_16" },
    { "grellra", "Album video", "lv_font_segoeui_16" },
    { "sys_setting", "Impostazioni funzionali", "lv_font_segoeui_16" },
    { "wifi", "WIFI", "lv_font_segoeui_16" },
    { "no_open_wifi", "WIFI non è attivato", "lv_font_segoeui_16" },
    { "click_out", "Fare clic su qualsiasi punto per uscire", "lv_font_segoeui_16" },
    { "setting_title", "·Impostazioni di sistema·", "lv_font_segoeui_16" },
    { "menu_wifi", "WIFI", "lv_font_segoeui_16" },
    { "wait", "Attendere...", "lv_font_segoeui_16" },
    { "min1", "1 minuto", "lv_font_segoeui_16" },
    { "min3", "3 minuti", "lv_font_segoeui_16" },
    { "min10", "10 minuti", "lv_font_segoeui_16" },
    { "date_label", "Etichetta data", "lv_font_segoeui_16" },
    { "car_set", "Impostazioni targa", "lv_font_segoeui_16" },
    { "back_insert", "Non rilevata la telecamera posteriore", "lv_font_segoeui_16" },
    { "roller_select", "Si prega di usare i pulsanti menu e modalità per selezionare", "lv_font_segoeui_16" },
    { "off_10_sec", "Il dispositivo si spegnerà tra 10 secondi", "lv_font_segoeui_16" },
    { "voi_num", "Volume del dispositivo", "lv_font_segoeui_16" },
    { "sub_low", "Basso", "lv_font_segoeui_16" },
    { "sub_middle", "Medio", "lv_font_segoeui_16" },
    { "sub_high", "Alto", "lv_font_segoeui_16" },
    { "min5", "5 minuti", "lv_font_segoeui_16" },
    { "menu_hdr", "Alto raggio dinamico", "lv_font_segoeui_16" },
    { "lan_russin", "русск", "lv_font_segoeui_16" },
    { "lcdprotect_p", "·Protezione schermo·", "lv_font_segoeui_16" },
    { "poweroff_p", "·Spegnimento automatico·", "lv_font_segoeui_16" },
    { "frequency_p", "·Frequenza della luce·", "lv_font_segoeui_16" },
    { "speaker_p", "·Suono dei pulsanti·", "lv_font_segoeui_16" },
    { "language_p", "·Impostazioni lingua·", "lv_font_segoeui_16" },
    { "software_p", "·Numero di versione·", "lv_font_segoeui_16" },
    { "carnum_p", "·Numero di targa·", "lv_font_segoeui_16" },
    { "roadline_p", "·Deviazione dalla corsia·", "lv_font_segoeui_16" },
    { "lamp_p", "·Fari anteriori·", "lv_font_segoeui_16" },
    { "formatting_p", "·Formattazione·", "lv_font_segoeui_16" },
    { "reset_p", "·Impostazioni predefinite·", "lv_font_segoeui_16" },
    { "date_p", "·Data e ora·", "lv_font_segoeui_16" },
    { "close_p", "·Chiudi", "lv_font_segoeui_16" },
    { "open_p", "·Apri", "lv_font_segoeui_16" },
    { "min1_p", "·1 minuto·", "lv_font_segoeui_16" },
    { "min3_p", "·3 minuti·", "lv_font_segoeui_16" },
    { "min10_p", "·10 minuti·", "lv_font_segoeui_16" },
    { "date_label_p", "·Etichetta data·", "lv_font_segoeui_16" },
    { "car_set_p", "·Impostazioni targa·", "lv_font_segoeui_16" },
    { "shoot_p", "·Modalità di scatto·", "lv_font_segoeui_16" },
    { "resolution_p", "·Risoluzione·", "lv_font_segoeui_16" },
    { "shots_p", "·Scatto seriale·", "lv_font_segoeui_16" },
    { "quality_p", "·Qualità immagine·", "lv_font_segoeui_16" },
    { "sharpness_p", "·Nitidezza immagine·", "lv_font_segoeui_16" },
    { "awb_p", "·Bilanciamento del bianco·", "lv_font_segoeui_16" },
    { "color_p", "·Colore·", "lv_font_segoeui_16" },
    { "exposure_p", "·Compensazione dell'esposizione·", "lv_font_segoeui_16" },
    { "handshake_p", "·Antivibrazione·", "lv_font_segoeui_16" },
    { "preview_p", "·Anteprima rapida·", "lv_font_segoeui_16" },
    { "doublerec_p", "·Registrazione a due vie·", "lv_font_segoeui_16" },
    { "cycrec_p", "·Registrazione ciclica·", "lv_font_segoeui_16" },
    { "gaprec_p", "·Time-lapse·", "lv_font_segoeui_16" },
    { "motion_p", "·Rilevamento movimento·", "lv_font_segoeui_16" },
    { "gsensor_p", "·Sensore di accelerazione·", "lv_font_segoeui_16" },
    { "record_p", "·Registrazione audio·", "lv_font_segoeui_16" },
    { "guard_p", "·Sorveglianza parcheggio·", "lv_font_segoeui_16" },
    { "menu_hdr_p", "·Alto raggio dinamico·", "lv_font_segoeui_16" },
    { NULL, NULL, NULL }
};

static lv_i18n_phrase_t it_plurals_other[] = {

    { NULL, NULL, NULL }
};

static uint8_t it_plural_fn(int32_t num)
{
    uint32_t n = op_n(num);
    UNUSED(n);
    uint32_t i = op_i(n);
    UNUSED(i);
    uint32_t v = op_v(n);
    UNUSED(v);

    if ((i == 1 && v == 0)) {
        return LV_I18N_PLURAL_TYPE_ONE;
    }
    return LV_I18N_PLURAL_TYPE_OTHER;
}

static const lv_i18n_lang_t it_lang = {
    .locale_name = "it",
    .singulars = it_singulars,
    .plurals[LV_I18N_PLURAL_TYPE_OTHER] = it_plurals_other,
    .locale_plural_fn = it_plural_fn
};
static lv_i18n_phrase_t nl_singulars[] = {
    { "funkey4", "preset", "lv_font_calibri_16" },
    { "funkey5", "preset", "lv_font_calibri_16" },
    { "funkey6", "preset", "lv_font_calibri_16" },
    { "funkey7", "preset", "lv_font_calibri_16" },
    { "suplanguage", "Nederlands", "lv_font_segoeui_16" },
    { "lcdprotect", "Schermbeveiliging", "lv_font_calibri_16" },
    { "poweroff", "Automatische uitschakeling", "lv_font_calibri_16" },
    { "frequency", "Lichtfrequentie", "lv_font_calibri_16" },
    { "speaker", "Knoppenklank", "lv_font_calibri_16" },
    { "language", "Taalinstellingen", "lv_font_calibri_16" },
    { "software", "Versienummer", "lv_font_calibri_16" },
    { "carnum", "Kennplaatnummer", "lv_font_calibri_16" },
    { "roadline", "Rijrichting", "lv_font_calibri_16" },
    { "lamp", "Voorlichten", "lv_font_calibri_16" },
    { "formatting", "Formatteren", "lv_font_calibri_16" },
    { "reset", "Standaardinstellingen", "lv_font_calibri_16" },
    { "date", "Datum en tijd", "lv_font_calibri_16" },
    { "close", "Sluiten", "lv_font_calibri_16" },
    { "open", "Openen", "lv_font_calibri_16" },
    { "subpagewarning0", "Waarschuwing\nBevestig om alle gegevens te wissen", "lv_font_calibri_24" },
    { "subpagewarning1", "Waarschuwing\nGeen geheugenkaart", "lv_font_calibri_24" },
    { "subpagewarning2", "Waarschuwing\nHerstel fabrieksinstellingen", "lv_font_calibri_24" },
    { "YES", "Bevestig", "lv_font_calibri_16" },
    { "CANCEL", "Annuleren", "lv_font_calibri_16" },
    { "shoot", "Afbeeldingsmodus", "lv_font_calibri_16" },
    { "dealy10s", "10-seconden timer", "lv_font_calibri_16" },
    { "dealy5s", "5-seconden timer", "lv_font_calibri_16" },
    { "dealy2s", "2-seconden timer", "lv_font_calibri_16" },
    { "nodealy", "Enkelvoudige afbeelding", "lv_font_calibri_16" },
    { "standard", "Standaard", "lv_font_calibri_16" },
    { "pool", "Economisch", "lv_font_calibri_16" },
    { "high", "Hoge kwaliteit", "lv_font_calibri_16" },
    { "strong", "Intens", "lv_font_calibri_16" },
    { "soft", "Zacht", "lv_font_calibri_16" },
    { "mono", "Zwart-wit", "lv_font_calibri_16" },
    { "Nostalgia", "Achtergrond", "lv_font_calibri_16" },
    { "acuity", "Beeldscherpte", "lv_font_calibri_16" },
    { "sunshine", "Natuurlijke belichting", "lv_font_calibri_16" },
    { "cloudy", "Bewolkt weer", "lv_font_calibri_16" },
    { "fluolamp", "Fluorescent", "lv_font_calibri_16" },
    { "default", "Standaard", "lv_font_calibri_16" },
    { "resolution", "Resolutie", "lv_font_calibri_16" },
    { "shots", "Seriële foto", "lv_font_calibri_16" },
    { "quality", "Beeldkwaliteit", "lv_font_calibri_16" },
    { "sharpness", "Beeldscherpte", "lv_font_calibri_16" },
    { "awb", "Witbalans", "lv_font_calibri_16" },
    { "color", "Kleur", "lv_font_calibri_16" },
    { "exposure", "Belichtingcompensatie", "lv_font_calibri_16" },
    { "handshake", "Vibratiedemping", "lv_font_calibri_16" },
    { "preview", "Snelle voorvertoning", "lv_font_calibri_16" },
    { "doublerec", "Dubbelkanaals opname", "lv_font_calibri_16" },
    { "cycrec", "Cyclusopname", "lv_font_calibri_16" },
    { "gaprec", "Time-lapse", "lv_font_calibri_16" },
    { "motion", "Bewegingsensor", "lv_font_calibri_16" },
    { "gsensor", "Versnellingsensor", "lv_font_calibri_16" },
    { "record", "Audio-opname", "lv_font_calibri_16" },
    { "guard", "Parkeerbewaking", "lv_font_calibri_16" },
    { "Lsensitive", "Lage gevoeligheid", "lv_font_calibri_16" },
    { "Msensitive", "Gemiddelde gevoeligheid", "lv_font_calibri_16" },
    { "Hsensitive", "Hoge gevoeligheid", "lv_font_calibri_16" },
    { "tung", "Wolfraamlamp", "lv_font_calibri_16" },
    { "sysprompt", "Klaar?~", "lv_font_calibri_16" },
    { "lowpow", "Lage batterij", "lv_font_calibri_16" },
    { "nofile", "Geen bestand", "lv_font_calibri_16" },
    { "nosd", "Geheugenkaart niet ingevoegd", "lv_font_calibri_16" },
    { "nocamera", "Camera-verbinding verloren", "lv_font_calibri_16" },
    { "fileerr", "Bestand beschadigd", "lv_font_calibri_16" },
    { "format_succ", "Formattering voltooid!", "lv_font_calibri_16" },
    { "sys_reset", "Herstel fabrieksinstellingen voltooid!", "lv_font_calibri_16" },
    { "format_failed", "Formattering mislukt!", "lv_font_calibri_16" },
    { "sys_reset_failed", "Herstel fabrieksinstellingen mislukt!", "lv_font_calibri_16" },
    { "subpagewarning3", "Versie: JL V1.0.0", "lv_font_calibri_24" },
    { "update_tips", "Niet uitschakelen tijdens het updaten", "lv_font_calibri_16" },
    { "line_drift_horizon", "Naar horizontaal bewegen", "lv_font_calibri_16" },
    { "line_drift_car", "Naar voor bewegen", "lv_font_calibri_16" },
    { "cancel", "Annuleren", "lv_font_calibri_16" },
    { "ensure", "OK", "lv_font_calibri_16" },
    { "sd_update", "Wilt u de geheugenkaart bijwerken?", "lv_font_calibri_16" },
    { "Mon", "Maandag", "lv_font_calibri_16" },
    { "Tue", "Dinsdag", "lv_font_calibri_16" },
    { "Wed", "Woensdag", "lv_font_calibri_16" },
    { "Thu", "Donderdag", "lv_font_calibri_16" },
    { "Fir", "Vrijdag", "lv_font_calibri_16" },
    { "Sat", "Zaterdag", "lv_font_calibri_16" },
    { "Sun", "Zondag", "lv_font_calibri_16" },
    { "del_file", "Wilt u de geselecteerde bestanden verwijderen?", "lv_font_calibri_16" },
    { "lock_file", "Wilt u de geselecteerde bestanden blokkeren/deblokkeren?", "lv_font_calibri_16" },
    { "unlock_file", "Wilt u de geselecteerde bestanden deblokkeren?", "lv_font_calibri_16" },
    { "unlock_all", "Wilt u alle bestanden deblokkeren?", "lv_font_calibri_16" },
    { "file_is_lock", "Bestand geblokkeerd", "lv_font_calibri_16" },
    { "del_all", "Wilt u alle bestanden verwijderen?", "lv_font_calibri_16" },
    { "lock_all", "Wilt u alle bestanden blokkeren?", "lv_font_calibri_16" },
    { "fs_err", "Abnormale toestand geheugenkaart", "lv_font_calibri_16" },
    { "gap_err", "Gelieve de time-lapse uit te schakelen!", "lv_font_calibri_16" },
    { "being_formatted", "Formattaar in behandeling...", "lv_font_calibri_16" },
    { "car_record", "Reisopname", "lv_font_calibri_16" },
    { "grellra", "Videoalbum", "lv_font_calibri_16" },
    { "sys_setting", "Functionele instellingen", "lv_font_calibri_16" },
    { "wifi", "WIFI", "lv_font_calibri_16" },
    { "no_open_wifi", "WIFI niet ingeschakeld", "lv_font_calibri_16" },
    { "click_out", "Klik op een willekeurig punt om te afsluiten", "lv_font_calibri_16" },
    { "setting_title", "·Systeeminstellingen·", "lv_font_calibri_16" },
    { "menu_wifi", "WIFI", "lv_font_calibri_16" },
    { "wait", "In behandeling...", "lv_font_calibri_16" },
    { "min1", "1 minuut", "lv_font_calibri_16" },
    { "min3", "3 minuten", "lv_font_calibri_16" },
    { "min10", "10 minuten", "lv_font_calibri_16" },
    { "date_label", "Datumetiket", "lv_font_calibri_16" },
    { "car_set", "Kennplaatinstellingen", "lv_font_calibri_16" },
    { "back_insert", "Achterlicht niet detecteerd", "lv_font_calibri_16" },
    { "roller_select", "Gebruik menu- en modusknoppen om te selecteren", "lv_font_calibri_16" },
    { "off_10_sec", "Het apparaat gaat uit na 10 seconden", "lv_font_calibri_16" },
    { "voi_num", "Apparaatvolume", "lv_font_calibri_16" },
    { "sub_low", "Laag", "lv_font_calibri_16" },
    { "sub_middle", "Gemiddeld", "lv_font_calibri_16" },
    { "sub_high", "Hoog", "lv_font_calibri_16" },
    { "min5", "5 minuten", "lv_font_calibri_16" },
    { "menu_hdr", "Dynamisch hoogstraal", "lv_font_calibri_16" },
    { "lan_russin", "русск", "lv_font_calibri_16" },
    { "lcdprotect_p", "·Schermbeveiliging·", "lv_font_calibri_16" },
    { "poweroff_p", "·Automatische uitschakeling·", "lv_font_calibri_16" },
    { "frequency_p", "·Lichtfrequentie·", "lv_font_calibri_16" },
    { "speaker_p", "·Knoppenklank·", "lv_font_calibri_16" },
    { "language_p", "·Taalinstellingen·", "lv_font_calibri_16" },
    { "software_p", "·Versienummer·", "lv_font_calibri_16" },
    { "carnum_p", "·Kennplaatnummer·", "lv_font_calibri_16" },
    { "roadline_p", "·Rijrichting·", "lv_font_calibri_16" },
    { "lamp_p", "·Voorlichten·", "lv_font_calibri_16" },
    { "formatting_p", "·Formatteren·", "lv_font_calibri_16" },
    { "reset_p", "·Standaardinstellingen·", "lv_font_calibri_16" },
    { "date_p", "·Datum en tijd·", "lv_font_calibri_16" },
    { "close_p", "·Sluiten·", "lv_font_calibri_16" },
    { "open_p", "·Openen·", "lv_font_calibri_16" },
    { "min1_p", "·1 minuut·", "lv_font_calibri_16" },
    { "min3_p", "·3 minuten·", "lv_font_calibri_16" },
    { "min10_p", "·10 minuten·", "lv_font_calibri_16" },
    { "date_label_p", "·Datumetiket·", "lv_font_calibri_16" },
    { "car_set_p", "·Kennplaatinstellingen·", "lv_font_calibri_16" },
    { "shoot_p", "·Afbeeldingsmodus·", "lv_font_calibri_16" },
    { "resolution_p", "·Resolutie·", "lv_font_calibri_16" },
    { "shots_p", "·Seriële foto·", "lv_font_calibri_16" },
    { "quality_p", "·Beeldkwaliteit·", "lv_font_calibri_16" },
    { "sharpness_p", "·Beeldscherpte·", "lv_font_calibri_16" },
    { "awb_p", "·Witbalans·", "lv_font_calibri_16" },
    { "color_p", "·Kleur·", "lv_font_calibri_16" },
    { "exposure_p", "·Belichtingcompensatie·", "lv_font_calibri_16" },
    { "handshake_p", "·Vibratiedemping·", "lv_font_calibri_16" },
    { "preview_p", "·Snelle voorvertoning·", "lv_font_calibri_16" },
    { "doublerec_p", "·Dubbelkanaals opname·", "lv_font_calibri_16" },
    { "cycrec_p", "·Cyclusopname·", "lv_font_calibri_16" },
    { "gaprec_p", "·Time-lapse·", "lv_font_calibri_16" },
    { "motion_p", "·Bewegingsensor·", "lv_font_calibri_16" },
    { "gsensor_p", "·Versnellingsensor·", "lv_font_calibri_16" },
    { "record_p", "·Audio-opname·", "lv_font_calibri_16" },
    { "guard_p", "·Parkeerbewaking·", "lv_font_calibri_16" },
    { "menu_hdr_p", "·Dynamisch hoogstraal·", "lv_font_calibri_16" },
    { NULL, NULL, NULL }
};

static lv_i18n_phrase_t nl_plurals_other[] = {

    { NULL, NULL, NULL }
};

static uint8_t nl_plural_fn(int32_t num)
{
    uint32_t n = op_n(num);
    UNUSED(n);
    uint32_t i = op_i(n);
    UNUSED(i);
    uint32_t v = op_v(n);
    UNUSED(v);

    if ((i == 1 && v == 0)) {
        return LV_I18N_PLURAL_TYPE_ONE;
    }
    return LV_I18N_PLURAL_TYPE_OTHER;
}

static const lv_i18n_lang_t nl_lang = {
    .locale_name = "nl",
    .singulars = nl_singulars,
    .plurals[LV_I18N_PLURAL_TYPE_OTHER] = nl_plurals_other,
    .locale_plural_fn = nl_plural_fn
};
static lv_i18n_phrase_t sv_singulars[] = {
    { "funkey4", "preset", "lv_font_calibri_16" },
    { "funkey5", "preset", "lv_font_calibri_16" },
    { "funkey6", "preset", "lv_font_calibri_16" },
    { "funkey7", "preset", "lv_font_calibri_16" },
    { "suplanguage", "Svenska", "lv_font_segoeui_16" },
    { "lcdprotect", "Skärmskydd", "lv_font_calibri_16" },
    { "poweroff", "Automatisk avstängning", "lv_font_calibri_16" },
    { "frequency", "Lysfrekvens", "lv_font_calibri_16" },
    { "speaker", "Knappsljud", "lv_font_calibri_16" },
    { "language", "Språkinställningar", "lv_font_calibri_16" },
    { "software", "Versionsnummer", "lv_font_calibri_16" },
    { "carnum", "Fordonsregistreringsnummer", "lv_font_calibri_16" },
    { "roadline", "Körriktning", "lv_font_calibri_16" },
    { "lamp", "Framljus", "lv_font_calibri_16" },
    { "formatting", "Formatera", "lv_font_calibri_16" },
    { "reset", "Standardinställningar", "lv_font_calibri_16" },
    { "date", "Datum och tid", "lv_font_calibri_16" },
    { "close", "Stänga", "lv_font_calibri_16" },
    { "open", "Öppna", "lv_font_calibri_16" },
    { "subpagewarning0", "Varning\nBekräfta för att radera alla data", "lv_font_calibri_24" },
    { "subpagewarning1", "Varning\nInget minneskort", "lv_font_calibri_24" },
    { "subpagewarning2", "Varning\nÅterställ fabriksinställningar", "lv_font_calibri_24" },
    { "YES", "Bekräfta", "lv_font_calibri_16" },
    { "CANCEL", "Avbryt", "lv_font_calibri_16" },
    { "shoot", "Bildläge", "lv_font_calibri_16" },
    { "dealy10s", "10-sekunders timer", "lv_font_calibri_16" },
    { "dealy5s", "5-sekunders timer", "lv_font_calibri_16" },
    { "dealy2s", "2-sekunders timer", "lv_font_calibri_16" },
    { "nodealy", "Enkel bild", "lv_font_calibri_16" },
    { "standard", "Standard", "lv_font_calibri_16" },
    { "pool", "Ekonomisk", "lv_font_calibri_16" },
    { "high", "Hög kvalitet", "lv_font_calibri_16" },
    { "strong", "Intens", "lv_font_calibri_16" },
    { "soft", "Mjuk", "lv_font_calibri_16" },
    { "mono", "Svart-vit", "lv_font_calibri_16" },
    { "Nostalgia", "Bakgrund", "lv_font_calibri_16" },
    { "acuity", "Skärpning", "lv_font_calibri_16" },
    { "sunshine", "Naturlig belysning", "lv_font_calibri_16" },
    { "cloudy", "Mulet", "lv_font_calibri_16" },
    { "fluolamp", "Lysrör", "lv_font_calibri_16" },
    { "default", "Standard", "lv_font_calibri_16" },
    { "resolution", "Upplösning", "lv_font_calibri_16" },
    { "shots", "Seriefoto", "lv_font_calibri_16" },
    { "quality", "Bildkvalitet", "lv_font_calibri_16" },
    { "sharpness", "Skärpning", "lv_font_calibri_16" },
    { "awb", "Vitbalans", "lv_font_calibri_16" },
    { "color", "Färg", "lv_font_calibri_16" },
    { "exposure", "Belysningskorrigering", "lv_font_calibri_16" },
    { "handshake", "Vibrationsdämpning", "lv_font_calibri_16" },
    { "preview", "Snabb förhandsvisning", "lv_font_calibri_16" },
    { "doublerec", "Dubbelkanalsinspelning", "lv_font_calibri_16" },
    { "cycrec", "Cykelinspelning", "lv_font_calibri_16" },
    { "gaprec", "Tidsintervall", "lv_font_calibri_16" },
    { "motion", "Rörelsesensor", "lv_font_calibri_16" },
    { "gsensor", "Hastighetsensor", "lv_font_calibri_16" },
    { "record", "Ljudinspelning", "lv_font_calibri_16" },
    { "guard", "Parkeringsövervakning", "lv_font_calibri_16" },
    { "Lsensitive", "Låg känslighet", "lv_font_calibri_16" },
    { "Msensitive", "Medium känslighet", "lv_font_calibri_16" },
    { "Hsensitive", "Hög känslighet", "lv_font_calibri_16" },
    { "tung", "Wolframlampa", "lv_font_calibri_16" },
    { "sysprompt", "Klart?~", "lv_font_calibri_16" },
    { "lowpow", "Låg batterinivå", "lv_font_calibri_16" },
    { "nofile", "Ingen fil", "lv_font_calibri_16" },
    { "nosd", "Inget minneskort införd", "lv_font_calibri_16" },
    { "nocamera", "Kamerans anslutning förlorad", "lv_font_calibri_16" },
    { "fileerr", "Fil skadad", "lv_font_calibri_16" },
    { "format_succ", "Formatering klar!", "lv_font_calibri_16" },
    { "sys_reset", "Återställning av fabriksinställningar klar!", "lv_font_calibri_16" },
    { "format_failed", "Formatering misslyckades!", "lv_font_calibri_16" },
    { "sys_reset_failed", "Återställning av fabriksinställningar misslyckades!", "lv_font_calibri_16" },
    { "subpagewarning3", "Version: JL V1.0.0", "lv_font_calibri_24" },
    { "update_tips", "Stänga av inte under uppdatering", "lv_font_calibri_16" },
    { "line_drift_horizon", "Flytta till vågrätt", "lv_font_calibri_16" },
    { "line_drift_car", "Flytta framåt", "lv_font_calibri_16" },
    { "cancel", "Avbryt", "lv_font_calibri_16" },
    { "ensure", "OK", "lv_font_calibri_16" },
    { "sd_update", "Vill du uppdatera minneskortet?", "lv_font_calibri_16" },
    { "Mon", "Måndag", "lv_font_calibri_16" },
    { "Tue", "Tisdag", "lv_font_calibri_16" },
    { "Wed", "Onsdag", "lv_font_calibri_16" },
    { "Thu", "Torsdag", "lv_font_calibri_16" },
    { "Fir", "Fredag", "lv_font_calibri_16" },
    { "Sat", "Lördag", "lv_font_calibri_16" },
    { "Sun", "Söndag", "lv_font_calibri_16" },
    { "del_file", "Vill du ta bort de markerade filer?", "lv_font_calibri_16" },
    { "lock_file", "Vill du låsa/låsa upp de markerade filer?", "lv_font_calibri_16" },
    { "unlock_file", "Vill du låsa upp de markerade filer?", "lv_font_calibri_16" },
    { "unlock_all", "Vill du låsa upp alla filer?", "lv_font_calibri_16" },
    { "file_is_lock", "Fil låst", "lv_font_calibri_16" },
    { "del_all", "Vill du ta bort alla filer?", "lv_font_calibri_16" },
    { "lock_all", "Vill du låsa alla filer?", "lv_font_calibri_16" },
    { "fs_err", "Abnormalt tillstånd på minneskort", "lv_font_calibri_16" },
    { "gap_err", "Vänligen inaktivera tidsintervall!", "lv_font_calibri_16" },
    { "being_formatted", "Formatering pågår...", "lv_font_calibri_16" },
    { "car_record", "Cykelinspelning", "lv_font_calibri_16" },
    { "grellra", "Videoalbum", "lv_font_calibri_16" },
    { "sys_setting", "Funktionella inställningar", "lv_font_calibri_16" },
    { "wifi", "WIFI", "lv_font_calibri_16" },
    { "no_open_wifi", "WIFI inaktiverat", "lv_font_calibri_16" },
    { "click_out", "Klicka på valfri punkt för att stänga", "lv_font_calibri_16" },
    { "setting_title", "·Systeminställningar·", "lv_font_calibri_16" },
    { "menu_wifi", "WIFI", "lv_font_calibri_16" },
    { "wait", "Pågående...", "lv_font_calibri_16" },
    { "min1", "1 minut", "lv_font_calibri_16" },
    { "min3", "3 minuter", "lv_font_calibri_16" },
    { "min10", "10 minuter", "lv_font_calibri_16" },
    { "date_label", "Datumetikett", "lv_font_calibri_16" },
    { "car_set", "Fordonsregistreringsinställningar", "lv_font_calibri_16" },
    { "back_insert", "Bakgrundsbelysning inte upptäckt", "lv_font_calibri_16" },
    { "roller_select", "Använd meny- och lägesknapparna för att välja", "lv_font_calibri_16" },
    { "off_10_sec", "Enheten kommer att släckas om 10 sekunder", "lv_font_calibri_16" },
    { "voi_num", "Enhetens ljudnivå", "lv_font_calibri_16" },
    { "sub_low", "Låg", "lv_font_calibri_16" },
    { "sub_middle", "Medium", "lv_font_calibri_16" },
    { "sub_high", "Hög", "lv_font_calibri_16" },
    { "min5", "5 minuter", "lv_font_calibri_16" },
    { "menu_hdr", "Dynamisk högstrålning", "lv_font_calibri_16" },
    { "lan_russin", "русск", "lv_font_calibri_16" },
    { "lcdprotect_p", "·Skärmskydd·", "lv_font_calibri_16" },
    { "poweroff_p", "·Automatisk avstängning·", "lv_font_calibri_16" },
    { "frequency_p", "·Lysfrekvens·", "lv_font_calibri_16" },
    { "speaker_p", "·Knappsljud·", "lv_font_calibri_16" },
    { "language_p", "·Språkinställningar·", "lv_font_calibri_16" },
    { "software_p", "·Versionsnummer·", "lv_font_calibri_16" },
    { "carnum_p", "·Fordonsregistreringsnummer·", "lv_font_calibri_16" },
    { "roadline_p", "·Körriktning·", "lv_font_calibri_16" },
    { "lamp_p", "·Framljus·", "lv_font_calibri_16" },
    { "formatting_p", "·Formatera·", "lv_font_calibri_16" },
    { "reset_p", "·Standardinställningar·", "lv_font_calibri_16" },
    { "date_p", "·Datum och tid·", "lv_font_calibri_16" },
    { "close_p", "·Stänga·", "lv_font_calibri_16" },
    { "open_p", "·Öppna·", "lv_font_calibri_16" },
    { "min1_p", "·1 minut·", "lv_font_calibri_16" },
    { "min3_p", "·3 minuter·", "lv_font_calibri_16" },
    { "min10_p", "·10 minuter·", "lv_font_calibri_16" },
    { "date_label_p", "·Datumetikett·", "lv_font_calibri_16" },
    { "car_set_p", "·Fordonsregistreringsinställningar·", "lv_font_calibri_16" },
    { "shoot_p", "·Bildläge·", "lv_font_calibri_16" },
    { "resolution_p", "·Upplösning·", "lv_font_calibri_16" },
    { "shots_p", "·Seriefoto·", "lv_font_calibri_16" },
    { "quality_p", "·Bildkvalitet·", "lv_font_calibri_16" },
    { "sharpness_p", "·Skärpning·", "lv_font_calibri_16" },
    { "awb_p", "·Vitbalans·", "lv_font_calibri_16" },
    { "color_p", "·Färg·", "lv_font_calibri_16" },
    { "exposure_p", "·Belysningskorrigering·", "lv_font_calibri_16" },
    { "handshake_p", "·Vibrationsdämpning·", "lv_font_calibri_16" },
    { "preview_p", "·Snabb förhandsvisning·", "lv_font_calibri_16" },
    { "doublerec_p", "·Dubbelkanalsinspelning·", "lv_font_calibri_16" },
    { "cycrec_p", "·Cykelinspelning·", "lv_font_calibri_16" },
    { "gaprec_p", "·Tidsintervall·", "lv_font_calibri_16" },
    { "motion_p", "·Rörelsesensor·", "lv_font_calibri_16" },
    { "gsensor_p", "·Hastighetsensor·", "lv_font_calibri_16" },
    { "record_p", "·Ljudinspelning·", "lv_font_calibri_16" },
    { "guard_p", "·Parkeringsövervakning·", "lv_font_calibri_16" },
    { "menu_hdr_p", "·Dynamisk högstrålning·", "lv_font_calibri_16" },
    { NULL, NULL, NULL }
};

static lv_i18n_phrase_t sv_plurals_other[] = {

    { NULL, NULL, NULL }
};

static uint8_t sv_plural_fn(int32_t num)
{
    uint32_t n = op_n(num);
    UNUSED(n);
    uint32_t i = op_i(n);
    UNUSED(i);
    uint32_t v = op_v(n);
    UNUSED(v);

    if ((i == 1 && v == 0)) {
        return LV_I18N_PLURAL_TYPE_ONE;
    }
    return LV_I18N_PLURAL_TYPE_OTHER;
}

static const lv_i18n_lang_t sv_lang = {
    .locale_name = "sv",
    .singulars = sv_singulars,
    .plurals[LV_I18N_PLURAL_TYPE_OTHER] = sv_plurals_other,
    .locale_plural_fn = sv_plural_fn
};
static lv_i18n_phrase_t da_singulars[] = {
    { "funkey4", "preset", "lv_font_calibri_16" },
    { "funkey5", "preset", "lv_font_calibri_16" },
    { "funkey6", "preset", "lv_font_calibri_16" },
    { "funkey7", "preset", "lv_font_calibri_16" },
    { "suplanguage", "Dansk", "lv_font_segoeui_16" },
    { "lcdprotect", "Skærmskærm", "lv_font_calibri_16" },
    { "poweroff", "Automatisk slukning", "lv_font_calibri_16" },
    { "frequency", "Lysfrekvens", "lv_font_calibri_16" },
    { "speaker", "Tastenlyd", "lv_font_calibri_16" },
    { "language", "Sprogindstillinger", "lv_font_calibri_16" },
    { "software", "Versionsnummer", "lv_font_calibri_16" },
    { "carnum", "Køretøjsregistreringsnummer", "lv_font_calibri_16" },
    { "roadline", "Kørselretning", "lv_font_calibri_16" },
    { "lamp", "Forlygte", "lv_font_calibri_16" },
    { "formatting", "Formatere", "lv_font_calibri_16" },
    { "reset", "Standardindstillinger", "lv_font_calibri_16" },
    { "date", "Dato og tid", "lv_font_calibri_16" },
    { "close", "Luk", "lv_font_calibri_16" },
    { "open", "Åbn", "lv_font_calibri_16" },
    { "subpagewarning0", "Advarsel\nBekræft for at slette alle data", "lv_font_calibri_24" },
    { "subpagewarning1", "Advarsel\nIntet hukommelseskort", "lv_font_calibri_24" },
    { "subpagewarning2", "Advarsel\nGendannelse af fabriksindstillinger", "lv_font_calibri_24" },
    { "YES", "Bekræft", "lv_font_calibri_16" },
    { "CANCEL", "Fortryd", "lv_font_calibri_16" },
    { "shoot", "Billedläge", "lv_font_calibri_16" },
    { "dealy10s", "10-sekunders tæller", "lv_font_calibri_16" },
    { "dealy5s", "5-sekunders tæller", "lv_font_calibri_16" },
    { "dealy2s", "2-sekunders tæller", "lv_font_calibri_16" },
    { "nodealy", "Enkelt billede", "lv_font_calibri_16" },
    { "standard", "Standard", "lv_font_calibri_16" },
    { "pool", "Økonomisk", "lv_font_calibri_16" },
    { "high", "Høj kvalitet", "lv_font_calibri_16" },
    { "strong", "Intens", "lv_font_calibri_16" },
    { "soft", "Blødt", "lv_font_calibri_16" },
    { "mono", "Sort-hvid", "lv_font_calibri_16" },
    { "Nostalgia", "Baggrund", "lv_font_calibri_16" },
    { "acuity", "Skærpning", "lv_font_calibri_16" },
    { "sunshine", "Naturlys", "lv_font_calibri_16" },
    { "cloudy", "Overskyet", "lv_font_calibri_16" },
    { "fluolamp", "Lysrør", "lv_font_calibri_16" },
    { "default", "Standard", "lv_font_calibri_16" },
    { "resolution", "Opløsning", "lv_font_calibri_16" },
    { "shots", "Seriefoto", "lv_font_calibri_16" },
    { "quality", "Billedkvalitet", "lv_font_calibri_16" },
    { "sharpness", "Skærpning", "lv_font_calibri_16" },
    { "awb", "Hvidbalance", "lv_font_calibri_16" },
    { "color", "Farve", "lv_font_calibri_16" },
    { "exposure", "Lyskorrektion", "lv_font_calibri_16" },
    { "handshake", "Vibrationsdæmpning", "lv_font_calibri_16" },
    { "preview", "Hurtig forsyning", "lv_font_calibri_16" },
    { "doublerec", "Dubbelkanaloptagelse", "lv_font_calibri_16" },
    { "cycrec", "Cykeloptagelse", "lv_font_calibri_16" },
    { "gaprec", "Tidsinterval", "lv_font_calibri_16" },
    { "motion", "Bevægelsessensor", "lv_font_calibri_16" },
    { "gsensor", "Hastighedssensor", "lv_font_calibri_16" },
    { "record", "Lydoptagelse", "lv_font_calibri_16" },
    { "guard", "Parkeringsovervågning", "lv_font_calibri_16" },
    { "Lsensitive", "Lav følsomhed", "lv_font_calibri_16" },
    { "Msensitive", "Medium følsomhed", "lv_font_calibri_16" },
    { "Hsensitive", "Høj følsomhed", "lv_font_calibri_16" },
    { "tung", "Wolframlampe", "lv_font_calibri_16" },
    { "sysprompt", "Klar?~", "lv_font_calibri_16" },
    { "lowpow", "Lavt batteriniveau", "lv_font_calibri_16" },
    { "nofile", "Ingen fil", "lv_font_calibri_16" },
    { "nosd", "Intet hukommelseskort indsat", "lv_font_calibri_16" },
    { "nocamera", "Kameraens forbindelse tabt", "lv_font_calibri_16" },
    { "fileerr", "Fil beskadiget", "lv_font_calibri_16" },
    { "format_succ", "Formatering klar!", "lv_font_calibri_16" },
    { "sys_reset", "Gendannelse af fabriksindstillinger klar!", "lv_font_calibri_16" },
    { "format_failed", "Formatering mislykkedes!", "lv_font_calibri_16" },
    { "sys_reset_failed", "Gendannelse af fabriksindstillinger mislykkedes!", "lv_font_calibri_16" },
    { "subpagewarning3", "Version: JL V1.0.0", "lv_font_calibri_24" },
    { "update_tips", "Sluk ikke under opdatering", "lv_font_calibri_16" },
    { "line_drift_horizon", "Flyt til vandret", "lv_font_calibri_16" },
    { "line_drift_car", "Flyt fremad", "lv_font_calibri_16" },
    { "cancel", "Fortryd", "lv_font_calibri_16" },
    { "ensure", "OK", "lv_font_calibri_16" },
    { "sd_update", "Ønsker du at opdatere hukommelseskortet?", "lv_font_calibri_16" },
    { "Mon", "Mandag", "lv_font_calibri_16" },
    { "Tue", "Tirsdag", "lv_font_calibri_16" },
    { "Wed", "Onsdag", "lv_font_calibri_16" },
    { "Thu", "Torsdag", "lv_font_calibri_16" },
    { "Fir", "Fredag", "lv_font_calibri_16" },
    { "Sat", "Lørdag", "lv_font_calibri_16" },
    { "Sun", "Søndag", "lv_font_calibri_16" },
    { "del_file", "Ønsker du at slette de markerede filer?", "lv_font_calibri_16" },
    { "lock_file", "Ønsker du at låse/låse op de markerede filer?", "lv_font_calibri_16" },
    { "unlock_file", "Ønsker du at låse op de markerede filer?", "lv_font_calibri_16" },
    { "unlock_all", "Ønsker du at låse op alle filer?", "lv_font_calibri_16" },
    { "file_is_lock", "Fil låst", "lv_font_calibri_16" },
    { "del_all", "Ønsker du at slette alle filer?", "lv_font_calibri_16" },
    { "lock_all", "Ønsker du at låse alle filer?", "lv_font_calibri_16" },
    { "fs_err", "Abnormt tilstand på hukommelseskort", "lv_font_calibri_16" },
    { "gap_err", "Venligst slå tidsintervallet fra!", "lv_font_calibri_16" },
    { "being_formatted", "Formatering i gang...", "lv_font_calibri_16" },
    { "car_record", "Cykeloptagelse", "lv_font_calibri_16" },
    { "grellra", "Videoalbum", "lv_font_calibri_16" },
    { "sys_setting", "Funktionelle indstillinger", "lv_font_calibri_16" },
    { "wifi", "WIFI", "lv_font_calibri_16" },
    { "no_open_wifi", "WIFI slået fra", "lv_font_calibri_16" },
    { "click_out", "Klik på enhver punkt for at lukke", "lv_font_calibri_16" },
    { "setting_title", "·Systemindstillinger·", "lv_font_calibri_16" },
    { "menu_wifi", "WIFI", "lv_font_calibri_16" },
    { "wait", "I gang...", "lv_font_calibri_16" },
    { "min1", "1 minut", "lv_font_calibri_16" },
    { "min3", "3 minutter", "lv_font_calibri_16" },
    { "min10", "10 minutter", "lv_font_calibri_16" },
    { "date_label", "Datoetiket", "lv_font_calibri_16" },
    { "car_set", "Køretøjsregistreringsindstillinger", "lv_font_calibri_16" },
    { "back_insert", "Baggrundsbelysning ikke opdaget", "lv_font_calibri_16" },
    { "roller_select", "Brug menu- og modusknapperne til at vælge", "lv_font_calibri_16" },
    { "off_10_sec", "Enhed vil slukke om 10 sekunder", "lv_font_calibri_16" },
    { "voi_num", "Enhedens lydniveau", "lv_font_calibri_16" },
    { "sub_low", "Lav", "lv_font_calibri_16" },
    { "sub_middle", "Medium", "lv_font_calibri_16" },
    { "sub_high", "Høj", "lv_font_calibri_16" },
    { "min5", "5 minutter", "lv_font_calibri_16" },
    { "menu_hdr", "Dynamisk højstråling", "lv_font_calibri_16" },
    { "lan_russin", "русск", "lv_font_calibri_16" },
    { "lcdprotect_p", "·Skærmskærm·", "lv_font_calibri_16" },
    { "poweroff_p", "·Automatisk slukning·", "lv_font_calibri_16" },
    { "frequency_p", "·Lysfrekvens·", "lv_font_calibri_16" },
    { "speaker_p", "·Tastenlyd·", "lv_font_calibri_16" },
    { "language_p", "·Sprogindstillinger·", "lv_font_calibri_16" },
    { "software_p", "·Versionsnummer·", "lv_font_calibri_16" },
    { "carnum_p", "·Køretøjsregistreringsnummer·", "lv_font_calibri_16" },
    { "roadline_p", "·Kørselretning·", "lv_font_calibri_16" },
    { "lamp_p", "·Forlygte·", "lv_font_calibri_16" },
    { "formatting_p", "·Formatere·", "lv_font_calibri_16" },
    { "reset_p", "·Standardindstillinger·", "lv_font_calibri_16" },
    { "date_p", "·Dato og tid·", "lv_font_calibri_16" },
    { "close_p", "·Luk·", "lv_font_calibri_16" },
    { "open_p", "·Åbn·", "lv_font_calibri_16" },
    { "min1_p", "·1 minut·", "lv_font_calibri_16" },
    { "min3_p", "·3 minutter·", "lv_font_calibri_16" },
    { "min10_p", "·10 minutter·", "lv_font_calibri_16" },
    { "date_label_p", "·Datoetiket·", "lv_font_calibri_16" },
    { "car_set_p", "·Køretøjsregistreringsindstillinger·", "lv_font_calibri_16" },
    { "shoot_p", "·Billedlæge·", "lv_font_calibri_16" },
    { "resolution_p", "·Opløsning·", "lv_font_calibri_16" },
    { "shots_p", "·Seriefoto·", "lv_font_calibri_16" },
    { "quality_p", "·Billedkvalitet·", "lv_font_calibri_16" },
    { "sharpness_p", "·Skærpning·", "lv_font_calibri_16" },
    { "awb_p", "·Hvidbalance·", "lv_font_calibri_16" },
    { "color_p", "·Farve·", "lv_font_calibri_16" },
    { "exposure_p", "·Lyskorrektion·", "lv_font_calibri_16" },
    { "handshake_p", "·Vibrationsdæmpning·", "lv_font_calibri_16" },
    { "preview_p", "·Hurtig forsyning·", "lv_font_calibri_16" },
    { "doublerec_p", "·Dubbelkanaloptagelse·", "lv_font_calibri_16" },
    { "cycrec_p", "·Cykeloptagelse·", "lv_font_calibri_16" },
    { "gaprec_p", "·Tidsinterval·", "lv_font_calibri_16" },
    { "motion_p", "·Bevægelsessensor·", "lv_font_calibri_16" },
    { "gsensor_p", "·Hastighedssensor·", "lv_font_calibri_16" },
    { "record_p", "·Lydoptagelse·", "lv_font_calibri_16" },
    { "guard_p", "·Parkeringsovervågning·", "lv_font_calibri_16" },
    { "menu_hdr_p", "·Dynamisk højstråling·", "lv_font_calibri_16" },
    { NULL, NULL, NULL }
};

static lv_i18n_phrase_t da_plurals_other[] = {

    { NULL, NULL, NULL }
};

static uint8_t da_plural_fn(int32_t num)
{
    uint32_t n = op_n(num);
    UNUSED(n);
    uint32_t i = op_i(n);
    UNUSED(i);
    uint32_t v = op_v(n);
    UNUSED(v);

    if ((i == 1 && v == 0)) {
        return LV_I18N_PLURAL_TYPE_ONE;
    }
    return LV_I18N_PLURAL_TYPE_OTHER;
}

static const lv_i18n_lang_t da_lang = {
    .locale_name = "da",
    .singulars = da_singulars,
    .plurals[LV_I18N_PLURAL_TYPE_OTHER] = da_plurals_other,
    .locale_plural_fn = da_plural_fn
};
const lv_i18n_language_pack_t lv_i18n_language_pack[] = {
    &zh_cn_lang,
    &zh_hk_lang,
    &en_lang,
    &ru_lang,
    &ar_ae_lang,
    &th_lang,
    &de_lang,
    &fr_lang,
    &ko_lang,
    &ja_lang,
    &es_lang,
    &pt_lang,
    &cs_lang,
    &pl_lang,
    &it_lang,
    &nl_lang,
    &sv_lang,
    &da_lang,
    NULL // End mark
};
////////////////////////////////////////////////////////////////////////////////

// Internal state
static const lv_i18n_language_pack_t *current_lang_pack;
static const lv_i18n_lang_t *current_lang;


/**
* Reset internal state. For testing.
*/
void __lv_i18n_reset(void)
{
    current_lang_pack = NULL;
    current_lang = NULL;
}

/**
* Set the languages for internationalization
* @param langs pointer to the array of languages. (Last element has to be `NULL`)
*/
int lv_i18n_init(const lv_i18n_language_pack_t *langs)
{
    if (langs == NULL) {
        return -1;
    }
    if (langs[0] == NULL) {
        return -1;
    }

    current_lang_pack = langs;
    current_lang = langs[0];     /*Automatically select the first language*/
    return 0;
}

/**
* Change the localization (language)
* @param l_name name of the translation locale to use. E.g. "en-GB"
*/
int lv_i18n_set_locale(const char *l_name)
{
    if (current_lang_pack == NULL) {
        return -1;
    }

    uint16_t i;

    for (i = 0; current_lang_pack[i] != NULL; i++) {
        // Found -> finish
        if (strcmp(current_lang_pack[i]->locale_name, l_name) == 0) {
            current_lang = current_lang_pack[i];
            return 0;
        }
    }

    return -1;
}


static const char *__lv_i18n_get_text_core(lv_i18n_phrase_t *trans, const char *msg_id)
{
    uint16_t i;
    for (i = 0; trans[i].msg_id != NULL; i++) {
        if (strcmp(trans[i].msg_id, msg_id) == 0) {
            /*The msg_id has found. Check the translation*/
            if (trans[i].translation) {
                return trans[i].translation;
            }
        }
    }

    return NULL;
}


/**
* Get the translation from a message ID
* @param msg_id message ID
* @return the translation of `msg_id` on the set local
*/
const char *lv_i18n_get_text(const char *msg_id)
{
    if (current_lang == NULL) {
        return msg_id;
    }

    const lv_i18n_lang_t *lang = current_lang;
    const void *txt;

    // Search in current locale
    if (lang->singulars != NULL) {
        txt = __lv_i18n_get_text_core(lang->singulars, msg_id);
        if (txt != NULL) {
            return txt;
        }
    }

    // Try to fallback
    if (lang == current_lang_pack[0]) {
        return msg_id;
    }
    lang = current_lang_pack[0];

    // Repeat search for default locale
    if (lang->singulars != NULL) {
        txt = __lv_i18n_get_text_core(lang->singulars, msg_id);
        if (txt != NULL) {
            return txt;
        }
    }

    return msg_id;
}

/**
* Get the translation from a message ID and apply the language's plural rule to get correct form
* @param msg_id message ID
* @param num an integer to select the correct plural form
* @return the translation of `msg_id` on the set local
*/
const char *lv_i18n_get_text_plural(const char *msg_id, int32_t num)
{
    if (current_lang == NULL) {
        return msg_id;
    }

    const lv_i18n_lang_t *lang = current_lang;
    const void *txt;
    lv_i18n_plural_type_t ptype;

    // Search in current locale
    if (lang->locale_plural_fn != NULL) {
        ptype = lang->locale_plural_fn(num);

        if (lang->plurals[ptype] != NULL) {
            txt = __lv_i18n_get_text_core(lang->plurals[ptype], msg_id);
            if (txt != NULL) {
                return txt;
            }
        }
    }

    // Try to fallback
    if (lang == current_lang_pack[0]) {
        return msg_id;
    }
    lang = current_lang_pack[0];

    // Repeat search for default locale
    if (lang->locale_plural_fn != NULL) {
        ptype = lang->locale_plural_fn(num);

        if (lang->plurals[ptype] != NULL) {
            txt = __lv_i18n_get_text_core(lang->plurals[ptype], msg_id);
            if (txt != NULL) {
                return txt;
            }
        }
    }

    return msg_id;
}

typedef struct {
    const char *font_name;
    const lv_font_t *font_ptr;
} font_mapping_t;

static const font_mapping_t font_mapping[] = {
    {"lv_font_fangsong_16", &lv_font_fangsong_16},
    {"lv_font_fangsong_24", &lv_font_fangsong_24},
    {"lv_font_FangZhengKaiTiJianTi_1_48", &lv_font_FangZhengKaiTiJianTi_1_48},
    {"lv_font_FangZhengKaiTiJianTi_1_22", &lv_font_FangZhengKaiTiJianTi_1_22},
    {"lv_font_FangZhengKaiTiJianTi_1_16", &lv_font_FangZhengKaiTiJianTi_1_16},
    {"lv_font_timesnewromanpsmt_16", &lv_font_timesnewromanpsmt_16},
    {"lv_font_timesnewromanpsmt_24", &lv_font_timesnewromanpsmt_24},
    {"lv_font_timesnewromanpsmt_48", &lv_font_timesnewromanpsmt_48},
    {"lv_font_timesnewromanpsmt_22", &lv_font_timesnewromanpsmt_22},
    {"lv_font_segoeui_16", &lv_font_segoeui_16},
    {"lv_font_segoeui_24", &lv_font_segoeui_24},
    {"lv_font_leelawadeeui_16", &lv_font_leelawadeeui_16},
    {"lv_font_leelawadeeui_24", &lv_font_leelawadeeui_24},
    {"lv_font_malgungothic_16", &lv_font_malgungothic_16},
    {"lv_font_malgungothic_24", &lv_font_malgungothic_24},
    {"lv_font_ms_gothic_16", &lv_font_ms_gothic_16},
    {"lv_font_calibri_16", &lv_font_calibri_16},
    {"lv_font_calibri_24", &lv_font_calibri_24},
    {NULL, NULL} // End mark
};

const lv_font_t *lv_i18n_get_font_by_name(const char *font_name)
{
    if (font_name == NULL) {
        return NULL;
    }

    for (uint16_t i = 0; font_mapping[i].font_name != NULL; i++) {
        if (strcmp(font_mapping[i].font_name, font_name) == 0) {
            return font_mapping[i].font_ptr;
        }
    }

    return NULL;
}

/*
* Get the font for a message ID
* @param msg_id message ID
*/
const lv_font_t *lv_i18n_get_font(const char *msg_id)
{
    if (current_lang == NULL) {
        return NULL;
    }

    const lv_i18n_lang_t *lang = current_lang;
    const lv_font_t *font = NULL;

    // Search in current locale singulars
    if (lang->singulars != NULL) {
        for (uint16_t i = 0; lang->singulars[i].msg_id != NULL; i++) {
            if (strcmp(lang->singulars[i].msg_id, msg_id) == 0) {
                const char *font_name = lang->singulars[i].font_name;
                font = lv_i18n_get_font_by_name(font_name);
                return font;
            }
        }
    }

    // Search in current locale plurals for type ONE
    if (lang->plurals[LV_I18N_PLURAL_TYPE_ONE] != NULL) {
        for (uint16_t i = 0; lang->plurals[LV_I18N_PLURAL_TYPE_ONE][i].msg_id != NULL; i++) {
            if (strcmp(lang->plurals[LV_I18N_PLURAL_TYPE_ONE][i].msg_id, msg_id) == 0) {
                const char *font_name = lang->plurals[LV_I18N_PLURAL_TYPE_ONE][i].font_name;
                font = lv_i18n_get_font_by_name(font_name);
                return font;
            }
        }
    }

    // Search in current locale plurals for type OTHER
    if (lang->plurals[LV_I18N_PLURAL_TYPE_OTHER] != NULL) {
        for (uint16_t i = 0; lang->plurals[LV_I18N_PLURAL_TYPE_OTHER][i].msg_id != NULL; i++) {
            if (strcmp(lang->plurals[LV_I18N_PLURAL_TYPE_OTHER][i].msg_id, msg_id) == 0) {
                const char *font_name = lang->plurals[LV_I18N_PLURAL_TYPE_OTHER][i].font_name;
                font = lv_i18n_get_font_by_name(font_name);
                return font;
            }
        }
    }

    return NULL;
}

/**
* Get the name of the currently used locale.
* @return name of the currently used locale. E.g. "en-GB"
*/
const char *lv_i18n_get_current_locale(void)
{
    if (!current_lang) {
        return NULL;
    }
    return current_lang->locale_name;
}

/**
 * Get the default locale
 * @return the default locale. E.g. "en_GB"
 */
GUI_WEAK const char *lv_i18n_get_default_locale(void)
{
    return "zh_CN";
}

#endif
