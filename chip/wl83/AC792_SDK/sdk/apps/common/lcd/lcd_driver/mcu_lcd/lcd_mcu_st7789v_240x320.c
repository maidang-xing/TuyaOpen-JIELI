#include "lcd_driver.h"
#include "lcd_config.h"
#include "asm/exti.h"
#include "gpio.h"

#if TCFG_LCD_MCU_ST7789V_240x320

#define __LCD_W  LCD_W
#define __LCD_H  LCD_H
#define __LCD_ID LCD_ID

#define READ_ID 	0x04
#define REGFLAG_DELAY 0x45

typedef struct {
    u8 cmd;
    u8 cnt;
    u8 dat[128];
} InitCode;

static const InitCode code1[] = {
    {0xfd, 2, {0x06, 0x08}},
    {0x61, 2, {0x07, 0x07}},
    {0x73, 1, {0x70}},
    {0x73, 1, {0x00}},

    {0x62, 3, {0x00, 0x44, 0x40}},

    {0x63, 4, {0x41, 0x07, 0x12, 0x12}},

    {0x64, 1, {0x37}},
    {0x65, 3, {0x09, 0x10, 0x21}},

    {0x66, 3, {0x09, 0x10, 0x21}},
    {0x67, 2, {0x21, 0x40}},
    {0x68, 4, {0x5d, 0x4c, 0x2c, 0x1c}},

    {0xb1, 3, {0x0f, 0x02, 0x00}},
    {0xb4, 1, {0x01}},

    {0xb5, 4, {0x02, 0x02, 0x0a, 0x14}},

    {0xb6, 5, {0x44, 0x01, 0x9f, 0x00, 0x02}},

    {0xdf, 1, {0x11}},

    ///////////NV3030A2 GAMMA/////////////////
    {0xe0, 8, {0x01, 0x06, 0x0e, 0x10, 0x0e, 0x0c, 0x0a, 0x16}},
    {0xe3, 8, {0x16, 0x13, 0x14, 0x10, 0x0f, 0x0f, 0x04, 0x01}},
    {0xe1, 2, {0x14, 0x68}},
    {0xe4, 2, {0x68, 0x14}},
    {0xe2, 6, {0x00, 0x0a, 0x09, 0x30, 0x39, 0x3f}},
    {0xe5, 6, {0x3f, 0x33, 0x28, 0x09, 0x0a, 0x00}},
    {0xe6, 2, {0x00, 0xff}},
    {0xe7, 6, {0x01, 0x04, 0x03, 0x03, 0x00, 0x12}},
    {0xe8, 3, {0x00, 0x70, 0x00}},
    {0xec, 1, {0x52}},
    {0xf1, 3, {0x01, 0xaa, 0xab}},
    {0xf6, 4, {0x01, 0x30, 0x00, 0x00}},
    {0xfd, 2, {0xfa, 0xfc}},
    {0x3a, 1, {0x55}},
    {0x35, 1, {0x00}},
    /* {0x36,1,{0x40}}, */  //rotate_90??
    {0x36, 1, {0x00}},
    {0x11, 0},
    { REGFLAG_DELAY, 200}, // delay 200ms
    {0x29, 0},
    { REGFLAG_DELAY, 10}, // delay 10ms
    {0x2C, 0},
};

static void ST7789V_set_direction(u8 dir)
{

}

static void ST7789V_init_code(const InitCode *code, u8 cnt)
{
    for (u8 i = 0; i < cnt; i++) {
        if (code[i].cmd == REGFLAG_DELAY) {
            lcd_delay(code[i].cnt);
        } else {
            WriteCOM(__LCD_ID, code[i].cmd);
            for (u8 j = 0; j < code[i].cnt; j++) {
                WriteDAT_8(__LCD_ID, code[i].dat[j]);
            }
        }
    }
}

void ST7789V_clear_screen(u32 color)
{
    WriteCOM(__LCD_ID, 0x2c);

    u8 *buf = malloc(LCD_W * LCD_H * 2);
    if (!buf) {
        printf("no men in %s \n", __func__);
        return;
    }
    for (u32 i = 0; i < LCD_W * LCD_H; i++) {
        buf[2 * i] = (color >> 8) & 0xff;
        buf[2 * i + 1] = color & 0xff;
    }
    WriteDAT_one_page(__LCD_ID, (u8 *)buf, __LCD_W * __LCD_H * 2);
    free(buf);
}

static int ST7789V_show_page(void *data)
{
    WriteCOM(__LCD_ID, 0x2c);
    WriteDAT_one_page(__LCD_ID, (u8 *)data, __LCD_W * __LCD_H * 2);
    return 0;
}

static void ST7789V_backctrl(struct lcd_board_cfg *bd_cfg, u8 onoff)
{
    if (onoff) {
        gpio_direction_output(bd_cfg->lcd_io.backlight, bd_cfg->lcd_io.backlight_value);
    } else {
        gpio_direction_output(bd_cfg->lcd_io.backlight, !bd_cfg->lcd_io.backlight_value);
    }
}

static int ST7789V_check_id(struct lcd_board_cfg *bd_cfg)
{
    return 0;
}

static int ST7789V_send_init_code(struct lcd_board_cfg *bd_cfg)
{
    ST7789V_init_code(code1, sizeof(code1) / sizeof(code1[0]));
    return 0;
}

static void ST7789V_reset(void)
{
    printf("ST7789V mcu lcd reset\n");
    lcd_rst_pinstate(__LCD_ID, 1);
    lcd_rs_pinstate(__LCD_ID, 1);
    lcd_cs_pinstate(__LCD_ID, 1);

    lcd_rst_pinstate(__LCD_ID, 1);
    lcd_delay(60);
    lcd_rst_pinstate(__LCD_ID, 0);
    lcd_delay(10);
    lcd_rst_pinstate(__LCD_ID, 1);
    lcd_delay(100);
}

static int ST7789V_init(void)
{
    printf("LCD_ST7789V init_start\n");
    ST7789V_reset();
    /* ST7789V_set_direction(ROTATE_DEGREE_90); */
    printf("LCD_ST7789V config succes\n");
    return 0;
}


REGISTER_IMD_DEVICE_BEGIN(lcd_mcu_dev) = {
    .info = {
        .test_mode 	     = false,
        /* .test_mode 	     = true, */
        .test_mode_color = 0x0000ff,
        .bg_color   	 = 0x00ff00,
        .xres 			 = __LCD_W,
        .yres 			 = __LCD_H,
        .target_xres 	 = __LCD_W,
        .target_yres 	 = __LCD_H,
        .sample          = SAMP_YUV420,
        .format          = FORMAT_RGB565,
        .len 			 = LEN_256,
        .interlaced_mode = INTERLACED_NONE,
        .rotate          = ROTATE_0,

        .adjust = {
            .r_gain = 1.0,
            .g_gain = 1.0,
            .b_gain = 1.0,
            .bright_gain = 1.0,
            .contrast_gain = 1.0,
            .saturation_gain = 1.0,
            .mean = 128,
            .angle = 0,
            .mode = 0,
        },

        .in_rbs         = false, //输入数据RB交换
        .out_rbs        = false, //输出数据RB交换
        .in_fmt         = TCFG_LCD_INPUT_FORMAT,
        .out_fmt        = LCD_OUT_RGB565,
        .dither_en      = false, //使能dither 0低位截断 1dither
        .in_bt601       = false, //yuv422输入 转换0 bt601, 1 bt709
        .out_bt601      = false, //yuv422输出 转换0 bt601, 1 bt709
    },

    .data_out_endian = MODE_BE,//RGB565模式生效 RGB888调节swap
    .set_io_hd       = 1,
    .ncycle          = CYCLE_TWO,
    .data_width      = PORT_8BITS,

    .dclk_set        = CLK_DIS,
    .sync0_set       = CLK_EN  | SIGNAL_DEN,
    .sync1_set       = CLK_DIS | SIGNAL_HSYNC,
    .sync2_set       = CLK_DIS | SIGNAL_VSYNC,

    .lcd_group       = PORT_GROUP_AA,
    .clk_cfg	 	 = PLL2_CLK_192M   | DIVA_3 | DIVB_2,
    .dclk_cfg        = DPI_CLK_STD_48M | DIVA_1 | DIVB_1,

    .timing = {
        .hori_total 		    = (240 + 40) * 2,
        .hori_sync 		        = 20 * 2,
        .hori_back_porth 	    = 20 * 2,
        .hori_pixel 	        = 240,

        .vert_total 		    = 320 + 20,
        .vert_sync 		        = 10,
        .vert_back_porth_odd 	= 10,
        .vert_back_porth_even 	= 0,
        .vert_pixel 	        = 320,
    },

},
REGISTER_IMD_DEVICE_END()

REGISTER_LCD_DEVICE_DRIVE(lcd_dev_mcu)  = {
    .logo            = "MCU_240x320_ST7789V",
    .id              = __LCD_ID,
    .type		     = LCD_MCU_SINGLE_FRAME,
    /* .type		     = LCD_MCU,  */
    .dev    	     = &lcd_mcu_dev,
    .init		     = ST7789V_init,
    .draw            = ST7789V_show_page,
    .bl_ctrl	     = ST7789V_backctrl,
    .check           = ST7789V_check_id,
    .send_init_code  = ST7789V_send_init_code,
};



#endif


