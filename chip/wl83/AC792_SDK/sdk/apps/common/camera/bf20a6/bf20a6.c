#include "device/iic.h"
#include "asm/iic.h"
#include "asm/isp_dev.h"
#include "gpio.h"
#include "bf20a6.h"
#include "asm/isp_alg.h"


#define CONFIG_INPUT_FPS    30


static void *iic = NULL;

static u8 bf20a6_reset_io[2] = {-1, -1};
static u8 bf20a6_power_io[2] = {-1, -1};

#define BF20A6_WRCMD 0xdc
#define BF20A6_RDCMD 0xdd


static s32 bf20a6_set_output_size(u16 *width, u16 *height, u8 *freq);

static unsigned char wr_bf20a6_reg(unsigned char regID, unsigned char regDat)
{
    u8 ret = 1;

    dev_ioctl(iic, IOCTL_IIC_START, 0);
    if (dev_ioctl(iic, IOCTL_IIC_TX_BYTE_WITH_START_BIT, BF20A6_WRCMD)) {
        ret = 0;
        printf("iic write err!!! line : %d \n", __LINE__);
        goto exit;
    }
    delay(1000);
    if (dev_ioctl(iic, IOCTL_IIC_TX_BYTE, regID)) {
        ret = 0;
        printf("iic write err!!! line : %d \n", __LINE__);
        goto exit;
    }
    delay(1000);
    if (dev_ioctl(iic, IOCTL_IIC_TX_BYTE_WITH_STOP_BIT, regDat)) {
        ret = 0;
        printf("iic write err!!! line : %d \n", __LINE__);
        goto exit;
    }
    delay(1000);

exit:
    dev_ioctl(iic, IOCTL_IIC_STOP, 0);
    return ret;
}

static unsigned char rd_bf20a6_reg(unsigned char regID, unsigned char *regDat)
{
    u8 ret = 1;
    dev_ioctl(iic, IOCTL_IIC_START, 0);
    if (dev_ioctl(iic, IOCTL_IIC_TX_BYTE_WITH_START_BIT, BF20A6_WRCMD)) {
        ret = 0;
        printf("iic write err!!! line : %d \n", __LINE__);
        goto exit;
    }
    delay(1000);
    if (dev_ioctl(iic, IOCTL_IIC_TX_BYTE_WITH_STOP_BIT, regID)) {
        ret = 0;
        printf("iic write err!!! line : %d \n", __LINE__);
        goto exit;
    }
    delay(1000);
    if (dev_ioctl(iic, IOCTL_IIC_TX_BYTE_WITH_START_BIT, BF20A6_RDCMD)) {
        ret = 0;
        printf("iic write err!!! line : %d \n", __LINE__);
        goto exit;
    }
    delay(1000);
    dev_ioctl(iic, IOCTL_IIC_RX_BYTE_WITH_STOP_BIT, (u32)regDat);

exit:
    dev_ioctl(iic, IOCTL_IIC_STOP, 0);
    return ret;
}

static void bf20a6_config_sensor(u16 *width, u16 *height, u8 *format, u8 *frame_freq)
{
    puts("bf20a6_config_sensor \n");
    wr_bf20a6_reg(0xf2, 0x01);
    wr_bf20a6_reg(0x12, 0x20);
    wr_bf20a6_reg(0x3a, 0x00);
    wr_bf20a6_reg(0xe1, 0x92);
    wr_bf20a6_reg(0xe3, 0x02);
    wr_bf20a6_reg(0xe0, 0x00);
    wr_bf20a6_reg(0x2a, 0x98);

    wr_bf20a6_reg(0x0e, 0x47);
    wr_bf20a6_reg(0x0f, 0x60);
    wr_bf20a6_reg(0x10, 0x57);
    wr_bf20a6_reg(0x11, 0x60);
    wr_bf20a6_reg(0x30, 0x61);
    wr_bf20a6_reg(0x62, 0xcd);
    wr_bf20a6_reg(0x63, 0x1a);
    wr_bf20a6_reg(0x64, 0x38);
    wr_bf20a6_reg(0x65, 0x52);
    wr_bf20a6_reg(0x66, 0x68);
    wr_bf20a6_reg(0x67, 0xc2);
    wr_bf20a6_reg(0x68, 0xa7);
    wr_bf20a6_reg(0x69, 0xab);
    wr_bf20a6_reg(0x6a, 0xad);
    wr_bf20a6_reg(0x6b, 0xa9);
    wr_bf20a6_reg(0x6c, 0xc4);
    wr_bf20a6_reg(0x6d, 0xc5);
    wr_bf20a6_reg(0x6e, 0x18);
    wr_bf20a6_reg(0xc0, 0x20);
    wr_bf20a6_reg(0xc1, 0x24);
    wr_bf20a6_reg(0xc2, 0x29);
    wr_bf20a6_reg(0xc3, 0x25);
    wr_bf20a6_reg(0xc4, 0x28);
    wr_bf20a6_reg(0xc5, 0x2a);
    wr_bf20a6_reg(0xc6, 0x41);
    wr_bf20a6_reg(0xca, 0x23);
    wr_bf20a6_reg(0xcd, 0x34);
    wr_bf20a6_reg(0xce, 0x32);
    wr_bf20a6_reg(0xcf, 0x35);
    wr_bf20a6_reg(0xd0, 0x6c);
    wr_bf20a6_reg(0xd1, 0x6e);
    wr_bf20a6_reg(0xd2, 0xcb);

    /* wr_bf20a6_reg(0xe2, 0x09); */
    wr_bf20a6_reg(0xe4, 0x73);
    wr_bf20a6_reg(0xe5, 0x22);
    wr_bf20a6_reg(0xe6, 0x24);
    wr_bf20a6_reg(0xe7, 0x64);
    /* wr_bf20a6_reg(0xe8, 0xa6); */
    wr_bf20a6_reg(0xe8, 0xa2);  //DVP:a2;  SPI:f2        VDDIO=1.8V,E8[2]=1;VDDIO=2.8V,E8[2]=0;
    wr_bf20a6_reg(0x4a, 0x00);
    wr_bf20a6_reg(0x00, 0x03);
    wr_bf20a6_reg(0x1f, 0x02);
    wr_bf20a6_reg(0x22, 0x02);
    wr_bf20a6_reg(0x0c, 0x31);

    wr_bf20a6_reg(0x00, 0x00);
    wr_bf20a6_reg(0x60, 0x81);
    wr_bf20a6_reg(0x61, 0x81);

    wr_bf20a6_reg(0xa0, 0x08);
    wr_bf20a6_reg(0x01, 0x1a);
    wr_bf20a6_reg(0x01, 0x1a);
    wr_bf20a6_reg(0x01, 0x1a);
    wr_bf20a6_reg(0x02, 0x15);
    wr_bf20a6_reg(0x02, 0x15);
    wr_bf20a6_reg(0x02, 0x15);
    wr_bf20a6_reg(0x13, 0x08);
    wr_bf20a6_reg(0x8a, 0x96);
    wr_bf20a6_reg(0x8b, 0x06);
    wr_bf20a6_reg(0x87, 0x18);


    wr_bf20a6_reg(0x34, 0x48); //lens
    wr_bf20a6_reg(0x35, 0x40);
    wr_bf20a6_reg(0x36, 0x40);

    wr_bf20a6_reg(0x71, 0x44);
    wr_bf20a6_reg(0x72, 0x48);
    wr_bf20a6_reg(0x74, 0xa2);
    wr_bf20a6_reg(0x75, 0xa9);
    wr_bf20a6_reg(0x78, 0x12);
    wr_bf20a6_reg(0x79, 0xa0);
    wr_bf20a6_reg(0x7a, 0x94);
    wr_bf20a6_reg(0x7c, 0x97);
    wr_bf20a6_reg(0x40, 0x30);
    wr_bf20a6_reg(0x41, 0x30);
    wr_bf20a6_reg(0x42, 0x28);
    wr_bf20a6_reg(0x43, 0x1f);
    wr_bf20a6_reg(0x44, 0x1c);
    wr_bf20a6_reg(0x45, 0x16);
    wr_bf20a6_reg(0x46, 0x13);
    wr_bf20a6_reg(0x47, 0x10);
    wr_bf20a6_reg(0x48, 0x0D);
    wr_bf20a6_reg(0x49, 0x0C);
    wr_bf20a6_reg(0x4B, 0x0A);
    wr_bf20a6_reg(0x4C, 0x0B);
    wr_bf20a6_reg(0x4E, 0x09);
    wr_bf20a6_reg(0x4F, 0x08);
    wr_bf20a6_reg(0x50, 0x08);


    wr_bf20a6_reg(0x5f, 0x29);
    wr_bf20a6_reg(0x23, 0x33);
    wr_bf20a6_reg(0xa1, 0x10); //AWB
    wr_bf20a6_reg(0xa2, 0x0d);
    wr_bf20a6_reg(0xa3, 0x30);
    wr_bf20a6_reg(0xa4, 0x06);
    wr_bf20a6_reg(0xa5, 0x22);
    wr_bf20a6_reg(0xa6, 0x56);
    wr_bf20a6_reg(0xa7, 0x18);
    wr_bf20a6_reg(0xa8, 0x1a);
    wr_bf20a6_reg(0xa9, 0x12);
    wr_bf20a6_reg(0xaa, 0x12);
    wr_bf20a6_reg(0xab, 0x16);
    wr_bf20a6_reg(0xac, 0xb1);
    wr_bf20a6_reg(0xba, 0x12);
    wr_bf20a6_reg(0xbb, 0x12);
    wr_bf20a6_reg(0xad, 0x12);
    wr_bf20a6_reg(0xae, 0x56);
    wr_bf20a6_reg(0xaf, 0x0a);
    wr_bf20a6_reg(0x3b, 0x30);
    wr_bf20a6_reg(0x3c, 0x12);
    wr_bf20a6_reg(0x3d, 0x22);
    wr_bf20a6_reg(0x3e, 0x3f);
    wr_bf20a6_reg(0x3f, 0x28);
    wr_bf20a6_reg(0xb8, 0xc3);
    wr_bf20a6_reg(0xb9, 0xA3);
    wr_bf20a6_reg(0x39, 0x47); //pure color threshold
    wr_bf20a6_reg(0x26, 0x13);
    wr_bf20a6_reg(0x27, 0x16);
    wr_bf20a6_reg(0x28, 0x14);
    wr_bf20a6_reg(0x29, 0x18);
    wr_bf20a6_reg(0xee, 0x0d);


    wr_bf20a6_reg(0x13, 0x05);
    wr_bf20a6_reg(0x24, 0x3C);
    wr_bf20a6_reg(0x81, 0x20);
    wr_bf20a6_reg(0x82, 0x40);
    wr_bf20a6_reg(0x83, 0x30);
    wr_bf20a6_reg(0x84, 0x58);
    wr_bf20a6_reg(0x85, 0x30);
    wr_bf20a6_reg(0x92, 0x08);
    wr_bf20a6_reg(0x86, 0xA0);
    wr_bf20a6_reg(0x8a, 0x96);
    wr_bf20a6_reg(0x91, 0xff);
    wr_bf20a6_reg(0x94, 0x62);
    wr_bf20a6_reg(0x9a, 0x18); //outdoor threshold
    wr_bf20a6_reg(0xf0, 0x4e);
    /* wr_bf20a6_reg(0xf0, 0x83); //动态帧率关闭 0x8f打开 */
    wr_bf20a6_reg(0x51, 0x17); //color normal
    wr_bf20a6_reg(0x52, 0x03);
    wr_bf20a6_reg(0x53, 0x5F);
    wr_bf20a6_reg(0x54, 0x47);
    wr_bf20a6_reg(0x55, 0x66);
    wr_bf20a6_reg(0x56, 0x0F);
    wr_bf20a6_reg(0x7e, 0x14);
    wr_bf20a6_reg(0x57, 0x36); //A光color
    wr_bf20a6_reg(0x58, 0x2A);
    wr_bf20a6_reg(0x59, 0xAA);
    wr_bf20a6_reg(0x5a, 0xA8);
    wr_bf20a6_reg(0x5b, 0x43);
    wr_bf20a6_reg(0x5c, 0x10);
    wr_bf20a6_reg(0x5d, 0x00);
    wr_bf20a6_reg(0x7d, 0x36);
    wr_bf20a6_reg(0x5e, 0x10);

    wr_bf20a6_reg(0xd6, 0x88); //contrast
    wr_bf20a6_reg(0xd5, 0x20); //低光加亮度
    wr_bf20a6_reg(0xb0, 0x84); //灰色区域降饱和度
    wr_bf20a6_reg(0xb5, 0x08); //低光降饱和度阈值
    wr_bf20a6_reg(0xb1, 0xc8); //saturation
    wr_bf20a6_reg(0xb2, 0xc0);
    wr_bf20a6_reg(0xb3, 0xd0);
    wr_bf20a6_reg(0xb4, 0xB0);

    wr_bf20a6_reg(0x32, 0x00);

    wr_bf20a6_reg(0xa0, 0x09);

    wr_bf20a6_reg(0x00, 0x03);

    wr_bf20a6_reg(0x0b, 0x02);
}
static s32 bf20a6_set_output_size(u16 *width, u16 *height, u8 *freq)
{
    u16 liv_width = *width;
    u16 liv_height = *height;
    return 0;
}

static s32 bf20a6_power_ctl(u8 isp_dev, u8 is_work)
{
    return 0;
}

static s32 bf20a6_id_check(void)
{
    u8 pid = 0x00;
    u8 ver = 0x00;
    rd_bf20a6_reg(0xfc, &pid);
    delay(40000);
    rd_bf20a6_reg(0xfd, &ver);
    delay(40000);
    printf("bf20a6 sensor id : 0x%x %x\n", pid, ver);
    if (pid != 0x20 || ver != 0xa6) {
        return -1;
    }

    return 0;
}

static void bf20a6_power_io_ctl(u32 _power_gpio, u32 on_off)
{
    gpio_direction_output(_power_gpio, on_off);
}

static void bf20a6_reset(u8 isp_dev)
{
    u8 res_io;
    u8 powd_io;
    u8 id = 0;
    puts("BF20A6 reset\n");

    if (isp_dev == ISP_DEV_0) {
        res_io = bf20a6_reset_io[0];
        powd_io = bf20a6_power_io[0];
    } else {
        res_io = bf20a6_reset_io[1];
        powd_io = bf20a6_power_io[1];
    }

    bf20a6_power_io_ctl(powd_io, 0);
    gpio_direction_output(res_io, 1);
    delay(40000);
    delay(40000);
    gpio_direction_output(res_io, 0);
    delay(40000);
    delay(40000);
    gpio_direction_output(res_io, 1);
    delay(40000);
    delay(40000);
}

static s32 bf20a6_check(u8 isp_dev, u32 _reset_gpio, u32 _power_gpio, char *iic_name)
{
    if (!iic) {
        /*        if (isp_dev == ISP_DEV_0) { */
        /* iic = dev_open("iic0", 0); */
        /* } else { */
        /* iic = dev_open("iic1", 0); */
        /* } */
        iic = dev_open(iic_name, 0);
        bf20a6_reset_io[isp_dev] = (u8)_reset_gpio;
        bf20a6_power_io[isp_dev] = (u8)_power_gpio;
    }

    if (iic == NULL) {
        printf("BF20A6 iic open err!!!\n\n");
        return -1;
    }
    bf20a6_reset(isp_dev);

    if (0 != bf20a6_id_check()) {
        printf("-------not BF20A6------\n\n");
        dev_close(iic);
        iic = NULL;
        return -1;
    }

    printf("-------hello BF20A6------\n\n");
    return 0;
}


static s32 bf20a6_init(u8 isp_dev, u16 *width, u16 *height, u8 *format, u8 *frame_freq)
{
    puts("\n\n bf20a6_init \n\n");

    /*     if (0 != bf20a6_check(isp_dev, 0, 0)) { */
    /* return -1; */
    /* } */

    bf20a6_config_sensor(width, height, format, frame_freq);

    return 0;
}
void set_rev_sensor_bf20a6(u16 rev_flag)
{
    if (!iic) {
        printf("no iic \n");
        return;
    }
    if (!rev_flag) {
        wr_bf20a6_reg(0x1e, 0x30);
    } else {
        wr_bf20a6_reg(0x1e, 0x00);
    }
}

u16 bf20a6_dvp_rd_reg(u16 addr)
{
    u8 val;
    rd_bf20a6_reg((u8)addr, &val);
    return val;
}

void bf20a6_dvp_wr_reg(u16 addr, u16 val)
{
    wr_bf20a6_reg((u8)addr, (u8)val);
}

// *INDENT-OFF*
REGISTER_CAMERA(BF20A6) = {
    .logo               =   "BF20A6D",
    .isp_dev            =   ISP_DEV_NONE,
    .in_format          =   SEN_IN_FORMAT_YUYV,
    .mbus_type          =   SEN_MBUS_PARALLEL,
    .mbus_config        =   SEN_MBUS_DATA_WIDTH_8B  | SEN_MBUS_HSYNC_ACTIVE_HIGH | \
                            SEN_MBUS_PCLK_SAMPLE_FALLING | SEN_MBUS_VSYNC_ACTIVE_HIGH | SEN_MBUS_SYNC0_VSYNC_SYNC1_HSYNC ,

    .fps                =   CONFIG_INPUT_FPS,
    .sen_size           =   {BF20A6_DVP_INPUT_W, BF20A6_DVP_INPUT_H},
    .isp_size           =   {BF20A6_DVP_INPUT_W, BF20A6_DVP_INPUT_H},
    .cap_fps            =   CONFIG_INPUT_FPS,
    .sen_cap_size       =   {BF20A6_DVP_INPUT_W, BF20A6_DVP_INPUT_H},
    .isp_cap_size       =   {BF20A6_DVP_INPUT_W, BF20A6_DVP_INPUT_H},
    .ops                =   {
        .avin_fps           =   NULL,
        .avin_valid_signal  =   NULL,
        .avin_mode_det      =   NULL,
        .sensor_check       =   bf20a6_check,
        .init               =   bf20a6_init,
        .set_size_fps       =   bf20a6_set_output_size,
        .power_ctrl         =   bf20a6_power_ctl,
        .sleep              =   NULL,
        .wakeup             =   NULL,
        .write_reg          =   bf20a6_dvp_wr_reg,
        .read_reg           =   bf20a6_dvp_rd_reg,
    }
};




