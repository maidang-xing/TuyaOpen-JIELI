#include "app_config.h"
#include "system/includes.h"
#include "lv_conf.h"
#include "lvgl.h"

#ifdef USE_LVGL_V9_UI_DEMO

static void create_my_label(void);
static void label_update_timer_cb(lv_timer_t *timer);
static void update_test_label(lv_obj_t *label);

void lvgl_v9_main_task_hook(void)
{

}

static void lv_example_img_bin(void)
{
    LV_IMAGE_DECLARE(img_benchmark_cogwheel_argb);
    static lv_style_t style_common;

    lv_style_reset(&style_common);

    lv_obj_t *img = lv_img_create(lv_scr_act());
    lv_obj_t *label = lv_label_create(lv_scr_act());
    lv_obj_remove_style_all(img);
    lv_obj_add_style(img, &style_common, 0);

    //Img
    lv_obj_set_pos(img, 330, 189);
    //C数组
    /* lv_img_set_src(img, &img_benchmark_cogwheel_argb); */
    //bin文件
    lv_img_set_src(img, "mnt/sdfile/EXT_RESERVED/uipackres/ui/logoargb.bin");

    //Font
    /* lv_font_t *font_bin = lv_font_load_bin("mnt/sdfile/EXT_RESERVED/uipackres/ui/font1.bin"); //不压缩字体 */
    lv_font_t *font_bin = lv_font_load_bin("mnt/sdfile/EXT_RESERVED/uipackres/ui/font1.rle");//压缩字体
    lv_obj_set_style_text_font(label, font_bin, LV_PART_MAIN);//
    /* lv_obj_set_style_text_font(label,&lv_font_montserrat_24, LV_PART_MAIN);//C数组 */

    lv_label_set_text(label, "123");

    lv_obj_set_pos(label, 100, 100);
}

//FIXME
void lv_album_img_show(const uint8_t *jpg_buf, uint32_t jpg_buf_len)
{
}

void lvgl_v9_gui_init(void)
{
    puts("lvgl_v9_gui_init \n\n");

#if 0
    while (!storage_device_ready()) {//等待sd文件系统挂载完成
        os_time_dly(2);
        puts("waitting sd on... ");
    }
#endif

    lv_init();
    lv_port_disp_init();
    lv_port_indev_init();
    lv_port_fs_init();
    lv_tick_set_cb(&timer_get_ms);

#if LV_USE_MONKEY != 0
    /*Create pointer monkey test*/
    lv_monkey_config_t monkey_pointer_config;
    monkey_pointer_config.type = LV_INDEV_TYPE_POINTER;
    monkey_pointer_config.period_range.min = 20;
    monkey_pointer_config.period_range.max = 20;
    lv_monkey_set_enable(lv_monkey_create(&monkey_pointer_config), true);

    /*Create keypad monkey test*/
    lv_monkey_config_t monkey_keypad_config;
    monkey_keypad_config.type = LV_INDEV_TYPE_KEYPAD;
    monkey_keypad_config.period_range.min = 20;
    monkey_keypad_config.period_range.max = 20;
    lv_monkey_set_enable(lv_monkey_create(&monkey_keypad_config), true);

    /*Create encoder monkey test*/
    lv_monkey_config_t monkey_encode_config;
    monkey_encode_config.type = LV_INDEV_TYPE_ENCODER;
    monkey_encode_config.period_range.min = 20;
    monkey_encode_config.period_range.max = 20;
    monkey_encode_config.input_range.min = -5;
    monkey_encode_config.input_range.max = 5;
    lv_monkey_set_enable(lv_monkey_create(&monkey_encode_config), true);
#endif

    /*lv_demo_benchmark();*/
    lv_demo_widgets();
    /*lv_demo_keypad_encoder();*/

    /* create_my_label(); */
}

static void create_my_label(void)
{
    lv_obj_t *scr = lv_screen_active();
    lv_obj_t *overlay;
    lv_obj_t *label;


    /* The root screen stays at the compose color key so only the real widgets cover the camera. */
    lv_obj_set_style_bg_color(scr, lv_color_hex(0x55aaa5), LV_PART_MAIN);
    lv_obj_set_style_bg_opa(scr, LV_OPA_COVER, LV_PART_MAIN);
    lv_obj_set_style_border_opa(scr, LV_OPA_TRANSP, LV_PART_MAIN);
    lv_obj_set_style_outline_opa(scr, LV_OPA_TRANSP, LV_PART_MAIN);
    lv_obj_set_style_shadow_opa(scr, LV_OPA_TRANSP, LV_PART_MAIN);

    /* Keep the demo label on the top layer so it is never reordered behind regular screen widgets. */
    overlay = lv_obj_create(scr);
    lv_obj_remove_style_all(overlay);
    lv_obj_set_size(overlay, 280, 64);
    lv_obj_align(overlay, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_style_bg_color(overlay, lv_color_hex(0x000000), 0);
    lv_obj_set_style_bg_opa(overlay, LV_OPA_80, 0);
    lv_obj_set_style_border_color(overlay, lv_color_hex(0xFFFFFF), 0);
    lv_obj_set_style_border_width(overlay, 2, 0);
    lv_obj_set_style_radius(overlay, 8, 0);
    lv_obj_clear_flag(overlay, LV_OBJ_FLAG_SCROLLABLE);

    label = lv_label_create(overlay);
    lv_label_set_text(label, "UI refresh test");
    lv_obj_set_size(label, 240, LV_SIZE_CONTENT);
    lv_obj_center(label);
    lv_obj_set_style_text_align(label, LV_TEXT_ALIGN_CENTER, 0);
    lv_obj_set_style_text_font(label, &lv_font_montserrat_20, 0);
    lv_obj_set_style_text_color(label, lv_color_hex(0xFFFFFF), 0);

    lv_timer_create(label_update_timer_cb, 1000, label);
    update_test_label(label);
}

static void label_update_timer_cb(lv_timer_t *timer)
{
    lv_obj_t *label = timer ? lv_timer_get_user_data(timer) : NULL;

    if (label == NULL) {
        return;
    }

    update_test_label(label);
}

static void update_test_label(lv_obj_t *label)
{
    static uint32_t refresh_cnt;

    refresh_cnt++;
    lv_label_set_text_fmt(label, "UI refresh ok\ncount: %04" LV_PRIu32, refresh_cnt);
}


static int lvgl_v9_test(void)
{
    int lvgl_v9_main_task_init(void);
    lvgl_v9_main_task_init();
    return 0;
}
/* late_initcall(lvgl_v9_test); */

int lvgl_main_task_init(void)
{
    int lvgl_v9_main_task_init(void);
    lvgl_v9_main_task_init();
}


#endif


