#include "../../lv_examples.h"
#if LV_USE_TINY_TTF && LV_TINY_TTF_FILE_SUPPORT && LV_BUILD_EXAMPLES

#include "lcd_config.h"

#define MY_DISP_HOR_RES        LCD_W
#define MY_DISP_VER_RES        LCD_H

// 需要生成字库文件并烧写到 FLASH
#define CONFIG_FONT_TTF_SUB0 "mnt/sdfile/EXT_RESERVED/uipackres/ui/sub0.ttf"       // 风急天高猿啸哀渚清沙白鸟飞回无边落木萧萧下不尽长江滚滚来万里悲秋常作客百年多病独登台艰难苦恨繁霜鬓潦倒新停浊酒杯
#define CONFIG_FONT_TTF_SUB1 "mnt/sdfile/EXT_RESERVED/uipackres/ui/sub1.ttf"       // 龘
#define CONFIG_FONT_TTF_TEST "mnt/sdfile/EXT_RESERVED/uipackres/ui/test_zh.ttf"    // 杰理科技股份有限公司

/**
* Show transformations (zoom and rotation) using a pivot point.
*/
static void set_angle(void *img, int32_t v)
{
    lv_img_set_angle(img, v);
}
static void set_zoom(void *img, int32_t v)
{
    lv_img_set_zoom(img, v);
}

static void lv_example_img_rotate(void)
{
    LV_IMG_DECLARE(img_cogwheel_argb);   // 图片资源声明
    /*Now create the actual image*/
    lv_obj_t *img = lv_img_create(lv_scr_act()); // 创建Image对象
    lv_img_set_src(img, &img_cogwheel_argb); //设置显示的图片源
    lv_obj_align(img, LV_ALIGN_CENTER, 50, 50); // 居中偏移50，50处对齐
    lv_img_set_pivot(img, 0, 0); // 围绕Image对象左上角旋转
    lv_anim_t a;
    lv_anim_init(&a);  // 初时化动画变量
    lv_anim_set_var(&a, img); //设置动画关联的对象img
    lv_anim_set_exec_cb(&a, set_angle); //设置动画执行的回调函数set_angle
    lv_anim_set_values(&a, 0, 3600); // 设置动画的范围，这里是角度0~360度
    lv_anim_set_time(&a, 5000); //设置动画duration时间5000毫秒
    lv_anim_set_repeat_count(&a, LV_ANIM_REPEAT_INFINITE);//设置动画重复次数，这里是无穷次
    lv_anim_start(&a); //启动动画播放
    lv_anim_set_exec_cb(&a, set_zoom); //设置动画执行回调函数set_zoom
    lv_anim_set_values(&a, 64, 768); // 设置动画的范围，这里是缩放比例128~256
    lv_anim_set_playback_time(&a, 5000); // 设置动画回播时间5000毫秒
    lv_anim_start(&a);  //启动动画播放
}

/**
 * Load a font with Tiny_TTF from file
 */

/* Animation callback function to update the character's position */
lv_font_t *anim_font;   // 字体全局变量

static void anim_scale_cb(void *var, int32_t v)
{
    float scale = 1.0f * v / 1000.0f;
    ttf_font_desc_t *ttf_dsc = anim_font->dsc;
#if LV_USE_GPU_JL_GPU2P5D   // 软件直接修改缩放因子的位图混合会导致绘制异常，硬件基于矢量路径能正确绘制
    ttf_dsc->scale = scale;
    //printf("scale = %f\r\n", scale);
#endif
}

static void anim_pos_x_cb(void *var, int32_t v)
{
    lv_obj_t *label = (lv_obj_t *)var;
    lv_obj_set_x(label, v);
}

static void anim_pos_y_cb(void *var, int32_t v)
{
    lv_obj_t *label = (lv_obj_t *)var;
    lv_obj_set_y(label, v);
}

static void anim_fly_out_x_ready_cb(void *var)
{
    lv_anim_t *a_fly_in = (lv_anim_t *)var;
    lv_obj_t *label = (lv_obj_t *)a_fly_in->var;

    // 飞出动画的结束
    lv_obj_del(label);
}

static void anim_fly_out_y_ready_cb(void *var)
{
    lv_anim_t *a_fly_in = (lv_anim_t *)var;
    lv_obj_t *label = (lv_obj_t *)a_fly_in->var;

    // 飞出动画的结束
    lv_obj_del(label);
}

static void anim_tran_x_ready_cb(void *var)
{
    lv_anim_t *a_tran = (lv_anim_t *)var;
    lv_obj_t *label = (lv_obj_t *)a_tran->var;
    ttf_font_desc_t *ttf_dsc = anim_font->dsc;

    // 移动播放的结束值就是每个字的起点位置
    //printf("current_value: %d, end_value: %d.\r\n", a_fly_in->current_value, a_fly_in->end_value);

    // 创建飞出动画
    lv_anim_t a_fly_out;
    lv_anim_init(&a_fly_out);  // 初时化动画变量
    lv_anim_set_var(&a_fly_out, label); //设置动画关联的对象
    lv_anim_set_exec_cb(&a_fly_out, anim_pos_x_cb);
    lv_anim_set_ready_cb(&a_fly_out, anim_fly_out_x_ready_cb);  // 飞出播放结束回调
    lv_anim_set_values(&a_fly_out, a_tran->current_value, MY_DISP_HOR_RES);
    lv_anim_set_time(&a_fly_out, 1000); //设置动画duration时间1000毫秒

    // 创建缩小动画
    lv_anim_t a_fly_out_scale;
    lv_anim_init(&a_fly_out_scale);  // 初时化动画变量
    lv_anim_set_var(&a_fly_out_scale, label); //设置动画关联的对象
    lv_anim_set_time(&a_fly_out_scale, 1000); //设置动画duration时间1000毫秒
    lv_anim_set_exec_cb(&a_fly_out_scale, anim_scale_cb);
    lv_anim_set_values(&a_fly_out_scale, (ttf_dsc->scale * 1000), 0);

    lv_anim_start(&a_fly_out); //启动动画播放
    lv_anim_start(&a_fly_out_scale); //启动动画播放
}

static void anim_tran_y_ready_cb(void *var)
{
    lv_anim_t *a_tran = (lv_anim_t *)var;
    lv_obj_t *label = (lv_obj_t *)a_tran->var;

    // 移动播放的结束值就是每个字的起点位置
    //printf("current_value: %d, end_value: %d.\r\n", a_fly_in->current_value, a_fly_in->end_value);

    //开始飞出动画
    // 创建飞出动画
    lv_anim_t a_fly_out;
    lv_anim_init(&a_fly_out);  // 初时化动画变量
    lv_anim_set_var(&a_fly_out, label); //设置动画关联的对象
    lv_anim_set_exec_cb(&a_fly_out, anim_pos_y_cb);
    lv_anim_set_ready_cb(&a_fly_out, anim_fly_out_y_ready_cb);  // 飞出播放结束回调
    lv_anim_set_values(&a_fly_out, a_tran->current_value, MY_DISP_VER_RES);
    lv_anim_set_time(&a_fly_out, 1000); //设置动画duration时间1000毫秒
    lv_anim_start(&a_fly_out); //启动动画播放
}

static void anim_fly_in_x_ready_cb(void *var)
{
    lv_anim_t *a_fly_in = (lv_anim_t *)var;
    lv_obj_t *label = (lv_obj_t *)a_fly_in->var;

    // 飞入动画的结束值就是每个字的起点位置
    //printf("current_value: %d, end_value: %d.\r\n", a_fly_in->current_value, a_fly_in->end_value);
    lv_anim_t a_tran;
    lv_anim_init(&a_tran);  // 初时化动画变量
    lv_anim_set_var(&a_tran, label); //设置动画关联的对象
    lv_anim_set_exec_cb(&a_tran, anim_pos_x_cb);
    lv_anim_set_ready_cb(&a_tran, anim_tran_x_ready_cb);  // 移动播放结束回调
    lv_anim_set_values(&a_tran, a_fly_in->current_value - 10, a_fly_in->current_value + 10);
    lv_anim_set_time(&a_tran, 1000); //设置动画duration时间1000毫秒
    lv_anim_set_playback_time(&a_tran, 1000); // 设置动画回播时间1000毫秒
    lv_anim_set_repeat_count(&a_tran, 3);//设置动画重复次数，这里是3
    lv_anim_start(&a_tran); //启动动画播放
}

static void anim_fly_in_y_ready_cb(void *var)
{
    lv_anim_t *a_fly_in = (lv_anim_t *)var;
    lv_obj_t *label = (lv_obj_t *)a_fly_in->var;

    // 飞入动画的结束值就是每个字的起点位置
    //printf("current_value: %d, end_value: %d.\r\n", a_fly_in->current_value, a_fly_in->end_value);
    lv_anim_t a_tran;
    lv_anim_init(&a_tran);  // 初时化动画变量
    lv_anim_set_var(&a_tran, label); //设置动画关联的对象
    lv_anim_set_exec_cb(&a_tran, anim_pos_y_cb);
    lv_anim_set_ready_cb(&a_tran, anim_tran_y_ready_cb);  // 移动播放结束回调
    lv_anim_set_values(&a_tran, a_fly_in->current_value - 10, a_fly_in->current_value + 10);
    lv_anim_set_time(&a_tran, 1000); //设置动画duration时间1000毫秒
    lv_anim_set_playback_time(&a_tran, 1000); // 设置动画回播时间1000毫秒
    lv_anim_set_repeat_count(&a_tran, 3);//设置动画重复次数，这里是3
    lv_anim_start(&a_tran); //启动动画播放
}

static void anim_style_angle_cb(void *var, int32_t v)
{
    lv_obj_t *label = (lv_obj_t *)var;
    lv_obj_set_style_transform_angle(label, v, 0);
}
static void anim_style_zoom_cb(void *var, int32_t v)
{
    lv_obj_t *label = (lv_obj_t *)var;
    lv_obj_set_style_transform_zoom(label, v, 0);
}

static void lv_example_zh_2d_anim_full_disp(char *pach, lv_coord_t font_size, const char *txt)
{
    extern const uint8_t ubuntu_font[];
    extern const int ubuntu_font_size;

    size_t txt_len = strlen(txt);

    // 解析字符串中的每一个 unicode
    int ofs = 0;
    char buf[64][4];    // 暂存分割的每一个 unicode 和对应的字符, 注意字符串长度，暂时设置 64，可以根据实际情况改变
    memset(buf, 0, sizeof(buf));
    uint16_t unicode_num = 0;
    while (ofs < txt_len) {
        uint32_t logical_char_pos = 0;

        uint32_t letter;
        uint32_t letter_next;
        int ofs_old = ofs;
        _lv_txt_encoded_letter_next_2(txt, &letter, &letter_next, &ofs);
        uint8_t unicode_size = ofs - ofs_old;
        assert(unicode_size < 4);

        if (letter != 0) {
            for (int i = 0; i < unicode_size; i++) {
                buf[unicode_num][i] = (char)txt[ofs_old + i];
            }

            unicode_num++;
        }
    }

    //printf("unicode_num = %d\r\n", unicode_num);

    while (1) {
        if (font_size * font_size * unicode_num > MY_DISP_HOR_RES * MY_DISP_VER_RES) {
            font_size = (font_size * 7) >> 3;
        } else {
            break;
        }
    }

    //printf("MY_DISP_HOR_RES = %d; MY_DISP_VER_RES = %d.\r\n", MY_DISP_HOR_RES, MY_DISP_VER_RES);

    uint8_t mx = MY_DISP_HOR_RES / font_size;
    uint8_t my = MY_DISP_VER_RES / font_size;

    uint8_t mx_max = mx;
    uint8_t my_max = my;

    while (1) {
        if (mx * my > unicode_num) {
            mx_max = mx;
            my_max = my;
            mx--;
            my--;
        } else {
            break;
        }
    }

    uint8_t mx_min = mx_max;
    uint8_t my_min = my_max;

    while (1) {
        if (mx_max * my_max < unicode_num) {
            mx_max++;
            my_max++;
            mx_min = mx_max;
            my_min = my_max;
        } else {
            break;
        }
    }

    while (1) {
        if (font_size * font_size * mx_min * my_min > MY_DISP_HOR_RES * MY_DISP_VER_RES) {
            font_size = (font_size * 7) >> 3;   // 再次调整字体大小
        } else {
            break;
        }
    }

    // 最终计算得到每行的字体个数以及有多少行
    //printf("[%s] begin ===> unicode_num = %d; mx = %d; my = %d; font_size = %d. mx_min = %d, my_min = %d.\r\n", __func__, unicode_num, mx, my, font_size, mx_min, my_min);

    uint16_t exedra_x = (MY_DISP_HOR_RES - (mx_min * font_size)) >> 1;    //字体显示前廊
    uint16_t exedra_y = (MY_DISP_VER_RES - (my_min * font_size)) >> 1;
    //printf("[%s] exedra_x = %d; exedra_y = %d.\r\n", __func__, exedra_x, exedra_y);

    /* 创建字体样式 */
    static lv_style_t style;
    lv_style_init(&style);
    anim_font = lv_tiny_ttf_create_file(pach, font_size);
    ttf_font_desc_t *ttf_dsc = anim_font->dsc;

    lv_style_set_text_font(&style, anim_font);
    lv_style_set_text_align(&style, LV_TEXT_ALIGN_LEFT);

    uint16_t txt_id = 0;
    for (int i = 0; i < my_min; i++) {
        for (int j = 0; j < mx_min; j++) {
            /* 创建标签 */
            lv_obj_t *label = lv_label_create(lv_scr_act());
            lv_label_set_text(label, buf[i * mx_min + j]);
            //lv_obj_align(label, LV_ALIGN_TOP_MID, x_ofs, y_ofs);

            // 每个字的起点位置
            lv_point_t start_pos;
            start_pos.x = exedra_x + j * font_size;
            start_pos.y = exedra_y + i * font_size;
            lv_obj_set_pos(label, start_pos.x, start_pos.x);
            //printf("[x][y] = [%d][%d]start_pos : (x, y) = (%d, %d).\r\n", j, i, start_pos.x, start_pos.y);

            /* 绑定样式和字体 */
            lv_obj_add_style(label, &style, 0);

            // 创建飞入动画
            lv_anim_t a_fly_in_x;
            lv_anim_init(&a_fly_in_x);  // 初时化动画变量
            lv_anim_set_var(&a_fly_in_x, label); //设置动画关联的对象
            lv_anim_set_time(&a_fly_in_x, 1000); //设置动画duration时间1000毫秒
            lv_anim_set_exec_cb(&a_fly_in_x, anim_pos_x_cb);
            lv_anim_set_ready_cb(&a_fly_in_x, anim_fly_in_x_ready_cb);  // 飞入播放结束回调
            lv_anim_set_values(&a_fly_in_x, -font_size, start_pos.x);

            lv_anim_t a_fly_in_y;
            lv_anim_init(&a_fly_in_y);  // 初时化动画变量
            lv_anim_set_var(&a_fly_in_y, label); //设置动画关联的对象
            lv_anim_set_time(&a_fly_in_y, 1000); //设置动画duration时间1000毫秒
            lv_anim_set_exec_cb(&a_fly_in_y, anim_pos_y_cb);
            lv_anim_set_ready_cb(&a_fly_in_y, anim_fly_in_y_ready_cb);  // 飞入播放结束回调
            lv_anim_set_values(&a_fly_in_y, -font_size, start_pos.y);

            // 创建放大动画
            lv_anim_t a_fly_in_scale;
            lv_anim_init(&a_fly_in_scale);  // 初时化动画变量
            lv_anim_set_var(&a_fly_in_scale, label); //设置动画关联的对象
            lv_anim_set_time(&a_fly_in_scale, 1000); //设置动画duration时间1000毫秒
            lv_anim_set_exec_cb(&a_fly_in_scale, anim_scale_cb);
            lv_anim_set_values(&a_fly_in_scale, 0, (ttf_dsc->scale * 1000));

            lv_anim_start(&a_fly_in_x); //启动动画播放
            lv_anim_start(&a_fly_in_y); //启动动画播放
            lv_anim_start(&a_fly_in_scale); //启动动画播放

            txt_id++;
            if (txt_id >= unicode_num) {
                break;  // 退出循环
            }
        }

    }
}

void lv_example_tiny_ttf_anim_of_style(char *pach, char *txt, uint16_t font_size)
{
    /*Create style with the new font*/
    static lv_style_t style;
    lv_style_init(&style);
    lv_font_t *font = lv_tiny_ttf_create_file(pach, font_size);
    lv_style_set_text_font(&style, font);
    lv_style_set_text_align(&style, LV_TEXT_ALIGN_CENTER);

    /*Create a label with the new style*/
    lv_obj_t *label = lv_label_create(lv_scr_act());
    lv_obj_add_style(label, &style, 0);
    lv_label_set_text(label, txt);
    lv_obj_center(label);

#if 1
    lv_anim_t a_angle;
    lv_anim_init(&a_angle);  // 初时化动画变量
    lv_anim_set_var(&a_angle, label); //设置动画关联的对象
    lv_anim_set_exec_cb(&a_angle, anim_style_angle_cb); // 基于样式属性旋转动画
    lv_anim_set_values(&a_angle, 0, 3600);
    lv_anim_set_time(&a_angle, 1000); //设置动画duration时间5000毫秒
    lv_anim_set_playback_time(&a_angle, 1000); // 设置动画回播时间5000毫秒
    lv_anim_set_repeat_count(&a_angle, LV_ANIM_REPEAT_INFINITE);//设置动画重复次数，这里是无穷次
    lv_anim_start(&a_angle); //启动动画播放
#endif

#if 1
    lv_anim_t a_zoom;
    lv_anim_init(&a_zoom);  // 初时化动画变量
    lv_anim_set_var(&a_zoom, label); //设置动画关联的对象
    lv_anim_set_exec_cb(&a_zoom, anim_style_zoom_cb); // 基于样式属性旋转动画
    lv_anim_set_values(&a_zoom, 512 + 256, 1024 + 256);
    lv_anim_set_time(&a_zoom, 1000); //设置动画duration时间5000毫秒
    lv_anim_set_playback_time(&a_zoom, 1000); // 设置动画回播时间5000毫秒
    lv_anim_set_repeat_count(&a_zoom, LV_ANIM_REPEAT_INFINITE);//设置动画重复次数，这里是无穷次
    lv_anim_start(&a_zoom); //启动动画播放
#endif
}


void lv_example_tiny_ttf_anim_line(char *pach, lv_coord_t font_size, lv_coord_t x_ofs, lv_coord_t y_ofs, char *load)
{
    extern const uint8_t ubuntu_font[];
    extern const int ubuntu_font_size;

    //printf("[%s] begin ===>", __func__);

#if 1
    /*Create style with the new font*/
    static lv_style_t style;
    lv_style_init(&style);
    lv_font_t *font = lv_tiny_ttf_create_file(pach, font_size);

    lv_style_set_text_font(&style, font);
    lv_style_set_text_align(&style, LV_TEXT_ALIGN_CENTER);

    /*Create a label with the new style*/
    lv_obj_t *label = lv_label_create(lv_scr_act());
    lv_obj_add_style(label, &style, 0);
    //lv_label_set_text(label, "Hello world, I'm a font created with Tiny TTF");
    lv_label_set_text(label, load);
    lv_obj_center(label);
#endif

    //lv_obj_set_pos(label, 0, 40);
    lv_obj_align(label, LV_ALIGN_TOP_MID, x_ofs, y_ofs);
#if 1
    lv_anim_t a;
    lv_anim_init(&a);  // 初时化动画变量
    lv_anim_set_var(&a, label); //设置动画关联的对象
    lv_anim_set_exec_cb(&a, anim_pos_x_cb);
    lv_anim_set_values(&a, 0, 480);
    lv_anim_set_time(&a, 10000); //设置动画duration时间5000毫秒
    lv_anim_set_playback_time(&a, 10000); // 设置动画回播时间5000毫秒
    lv_anim_set_repeat_count(&a, LV_ANIM_REPEAT_INFINITE);//设置动画重复次数，这里是无穷次
    lv_anim_start(&a); //启动动画播放
#endif
}


void lv_fout_and_img_2d_blend_test(void)
{
    //lv_example_img_rotate();    // 背景图片动画：带旋转缩放变换，测试性能和效果
    //lv_example_tiny_ttf_file(CONFIG_FONT_TTF_SUB1, "龘", 256);
    lv_example_tiny_ttf_anim_of_style(CONFIG_FONT_TTF_SUB1, "龘", 64);

    //lv_example_tiny_ttf_anim_line(CONFIG_FONT_TTF_SUB0, 128, 0, 300, "ABCabc!@#$%");
    //lv_example_tiny_ttf_anim_line(CONFIG_FONT_TTF_SUB0, 256, 0, 300, "风急天高猿啸哀渚清沙白鸟飞回无边落木萧萧下不尽长江滚滚来万里悲秋常作客百年多病独登台艰难苦恨繁霜鬓潦倒新停浊酒杯");
    //lv_example_tiny_ttf_anim_line(CONFIG_FONT_TTF_TEST, 128, 0, 300, "杰理科技股份有限公司");

    //lv_example_zh_2d_anim_full_disp(CONFIG_FONT_TTF_SUB0, 256, "风急天高猿啸哀，渚清沙白鸟飞回");
    //lv_example_zh_2d_anim_full_disp(CONFIG_FONT_TTF_SUB0, 256, "无边落木萧萧下，不尽长江滚滚来");
    //lv_example_zh_2d_anim_full_disp(CONFIG_FONT_TTF_SUB0, 256, "万里悲秋常作客，百年多病独登台");
    //lv_example_zh_2d_anim_full_disp(CONFIG_FONT_TTF_SUB0, 256, "艰难苦恨繁霜鬓，潦倒新停浊酒杯");
}

// 基于 font2p5d 控件实现，见 widgets/obj2p5d
void lv_fout_and_img_3d_blend_test(void)
{
#if LV_USE_GPU_JL_GPU2P5D   // 2.5D 图像渲染效果需要使能硬件图形加速
    // TODO
#endif
}

#endif
