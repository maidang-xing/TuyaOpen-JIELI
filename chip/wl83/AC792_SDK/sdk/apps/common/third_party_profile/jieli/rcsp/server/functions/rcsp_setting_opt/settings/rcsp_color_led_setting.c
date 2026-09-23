#ifdef SUPPORT_MS_EXTENSIONS
#pragma bss_seg(".rcsp_color_led_setting.data.bss")
#pragma data_seg(".rcsp_color_led_setting.data")
#pragma const_seg(".rcsp_color_led_setting.text.const")
#pragma code_seg(".rcsp_color_led_setting.text")
#endif
#include "rcsp_color_led_setting.h"
#if (RCSP_MODE && RCSP_ADV_COLOR_LED_SET_ENABLE)
#include "syscfg_id.h"
#include "user_cfg.h"

#include "rcsp_setting_sync.h"
#include "rcsp_setting_opt.h"

#if TCFG_COLORLED_ENABLE
//#include "ui_manage.h"
#include "color_led_app.h"
#endif

#define IS_COLOR_LED_LEGAL(color_led) \
	((color_led.open_status < COLOR_LED_STATUS_MAX) && \
	 (color_led.mode < MODE_MAX))

enum {
    COLOR_LED_STATUS_CLOSE,             //关闭
    COLOR_LED_STATUS_OPEN,              //打开
    COLOR_LED_STATUS_SETTING,           //设置
    COLOR_LED_STATUS_RESUME,            //恢复
    COLOR_LED_STATUS_MAX
};
enum {
    MODE_LIGHT,                         //常量（纯色）模式
    MODE_TWINKLE,                       //闪烁模式
    MODE_USER,                          //情景模式
    MODE_BREATHE,                       //呼吸模式
    MODE_CYCLIC_COLOR,                  //循环变色模式
    MODE_MUSICAL_RHYTHM,                //音乐律动模式
    MODE_MAX
};
#if TCFG_COLORLED_ENABLE
const u32 twinkle_color_table[] = {
    //COLOR_COLORFUL_TWINKLE,
    COLOR_RED,
    COLOR_ORANGE,
    COLOR_YELLOW,
    COLOR_GREEN,
    COLOR_CYAN,
    COLOR_BLUE,
    COLOR_PURPLE,
};
#endif

typedef struct {
    u8 open_status  : 2;//0:关闭  1：打开  2：设置模式
    u8 mode			: 3;//参考枚举值MODE_LIGHT
    u8 reseved		: 3;
    u8 red;
    u8 green;
    u8 blue;
    u8 twinkle_mode;    //闪烁模式选择
    //speed字段
    //闪烁模式时,表示闪烁频率：
    //  0：快闪
    //  1：慢闪
    //  2：缓闪
    //  3：音乐闪烁
    //呼吸模式、循环变色模式时，表示更新间隔：
    //  取值范围：[10, 100]
    u8 speed;
    u8 user_mode;       //情景模式选择
    u16 hue;
    u8 saturation;
    u8 lightness;
} __attribute__((packed)) color_led_t;
static color_led_t g_color_led;

#define COLOR_LED_PROTOCOL_DATA_LEN		 	(sizeof(color_led_t))

u32 rcsp_get_color_led_setting_data_len(void)
{
    return COLOR_LED_PROTOCOL_DATA_LEN;
}

static void set_color_led_setting(u8 *color_led_setting_info)
{
    /* printf("%s, %s, %d\n", __FILE__, __FUNCTION__, __LINE__); */
    /* put_buf(color_led_setting_info, COLOR_LED_PROTOCOL_DATA_LEN); */
    color_led_t color_led_cur;
    memcpy((u8 *)&color_led_cur, color_led_setting_info, sizeof(color_led_t));

    printf("set color led info:\n"
           "status: %u\n"
           "mode: %u\n"
           "R: %u, G: %u, B: %u\n"
           "twinkle_mode: %u\n"
           "speed: %u\n"
           "usr_mode: %u\n"
           "hue: %u\n"
           "saturation: %u\n"
           "lightness: %u\n",
           color_led_cur.open_status,
           color_led_cur.mode,
           color_led_cur.red, color_led_cur.green, color_led_cur.blue,
           color_led_cur.twinkle_mode,
           color_led_cur.speed,
           color_led_cur.user_mode,
           color_led_cur.hue,
           color_led_cur.saturation,
           color_led_cur.lightness);

    if ((color_led_cur.open_status == 0) || (color_led_cur.open_status == 1)) {
        //switch active,not set other_status
        g_color_led.open_status = color_led_cur.open_status;
        return;
    }

    memcpy((u8 *)&g_color_led, color_led_setting_info, sizeof(color_led_t));
}

static int get_color_led_setting(u8 *color_led_setting_info)
{
    color_led_t color_led_cur;
    int len = syscfg_read(VM_COLOR_LED_SETTING, color_led_setting_info, COLOR_LED_PROTOCOL_DATA_LEN);

    if (len != COLOR_LED_PROTOCOL_DATA_LEN) {
        printf("!!!!!!!!color led data read error !!!!!!!!!!!!!!! \n");
    }
    return 0;
}

// 1、写入VM
static void update_color_led_setting_vm_value(u8 *color_led_setting_info)
{
    color_led_t color_led_cur;
    memcpy((u8 *)&color_led_cur, color_led_setting_info, sizeof(color_led_t));
    if ((color_led_cur.open_status == 0) || (color_led_cur.open_status == 1)) {
        //switch active,not set other_status
        u8 open_status = color_led_cur.open_status;
        int len = syscfg_read(VM_COLOR_LED_SETTING, (u8 *)&color_led_cur, COLOR_LED_PROTOCOL_DATA_LEN);
        color_led_cur.open_status = open_status;
        syscfg_write(VM_COLOR_LED_SETTING, (u8 *)&color_led_cur, COLOR_LED_PROTOCOL_DATA_LEN);
        return;
    }

    syscfg_write(VM_COLOR_LED_SETTING, color_led_setting_info, COLOR_LED_PROTOCOL_DATA_LEN);
}
// 2、同步对端
static void color_led_setting_sync(u8 *color_led_setting_info)
{
#if TCFG_USER_TWS_ENABLE
    extern int get_bt_tws_connect_status();
    if (get_bt_tws_connect_status()) {
        update_rcsp_setting(ATTR_TYPE_COLOR_LED_SETTING);
    }
#endif
}

static void color_led_flash(void)
{

    color_led_t color_led_cur;
    get_color_led_setting((u8 *)&color_led_cur);
    if (!IS_COLOR_LED_LEGAL(color_led_cur)) {
        printf("color led illegal data \n");
        return;
    }

#if TCFG_COLORLED_ENABLE
    u8 mode = 0;
    u8 speed = 0;
    u32 color = 0;

    if (color_led_cur.open_status == COLOR_LED_STATUS_CLOSE) {
        mode = COLOR_LED_MODE_LIGHT;
        color = COLOR_BLACK;
        color_led_set_api(mode, speed, color);
        return;
    }

    speed = color_led_cur.speed;
    color = color_led_cur.red + ((int)color_led_cur.green << 8) + ((int)color_led_cur.blue << 16);
    switch (color_led_cur.mode) {
    case MODE_LIGHT:
        mode = COLOR_LED_MODE_LIGHT;
        break;
    case MODE_TWINKLE:
        if (color_led_cur.twinkle_mode == 0) {
            mode = COLOR_LED_MODE_COLORFUL_TWINKLE;
        } else {
            mode = COLOR_LED_MODE_TWINKLE;
            color = twinkle_color_table[color_led_cur.twinkle_mode - 1];
        }
        break;
    case MODE_USER:
        mode = COLOR_LED_MODE_RAINBOW + color_led_cur.user_mode;
        break;
    default:
        break;
    }

    printf("mode:%d fre_mode:%d color:0x%x \n", mode, speed, color);
    color_led_set_api(mode, speed, color);
#endif
}

static void deal_color_led_setting(u8 *color_led_setting_info, u8 write_vm, u8 tws_sync)
{
    u8 led_setting[COLOR_LED_PROTOCOL_DATA_LEN];
    if (!color_led_setting_info) {
        get_color_led_setting(led_setting);
    } else {
        memcpy(led_setting, color_led_setting_info, COLOR_LED_PROTOCOL_DATA_LEN);
        set_color_led_setting(color_led_setting_info);
    }
    if (write_vm) {
        update_color_led_setting_vm_value(led_setting);
    }
    if (tws_sync) {
        color_led_setting_sync(led_setting);
    }

    color_led_flash();
}

static int rcsp_color_led_init(void)
{
    color_led_t color_led_cur;
    int len = syscfg_read(VM_COLOR_LED_SETTING, (u8 *)&color_led_cur, COLOR_LED_PROTOCOL_DATA_LEN);

    if ((!IS_COLOR_LED_LEGAL(color_led_cur)) || (len != COLOR_LED_PROTOCOL_DATA_LEN)) {
        printf("first time start device,reset color led data \n");
        memset((u8 *)&color_led_cur, 0x00, sizeof(color_led_cur));
#if 0
        color_led_cur.open_status = COLOR_LED_STATUS_SETTING;
        color_led_cur.mode = MODE_USER;
        color_led_cur.red = 64;
        color_led_cur.green = 191;
        color_led_cur.blue = 191;
        color_led_cur.hue = 180;
        color_led_cur.saturation = 50;
        color_led_cur.lightness = 50;

#else
        color_led_cur.open_status = COLOR_LED_STATUS_CLOSE;
        color_led_cur.mode = MODE_LIGHT;
        color_led_cur.red = 0;
        color_led_cur.green = 0;
        color_led_cur.blue = 255;
        color_led_cur.hue = 0;
        color_led_cur.saturation = 0;
        color_led_cur.lightness = 0;
#endif
        syscfg_write(VM_COLOR_LED_SETTING, (u8 *)&color_led_cur, COLOR_LED_PROTOCOL_DATA_LEN);
    }

    set_color_led_setting((u8 *)&color_led_cur);
    deal_color_led_setting(NULL, 0, 0);

    return 0;
}

static RCSP_SETTING_OPT adv_color_led_opt = {
    .data_len = COLOR_LED_PROTOCOL_DATA_LEN,
    .setting_type = ATTR_TYPE_COLOR_LED_SETTING,
    .syscfg_id = VM_COLOR_LED_SETTING,
    .deal_opt_setting = deal_color_led_setting,
    .set_setting = set_color_led_setting,
    .get_setting = get_color_led_setting,
    .custom_setting_init = rcsp_color_led_init,
    .custom_vm_info_update = NULL,
    .custom_setting_update = NULL,
    .custom_sibling_setting_deal = NULL,
    .custom_setting_release = NULL,
};
REGISTER_APP_SETTING_OPT(adv_color_led_opt);

#endif
