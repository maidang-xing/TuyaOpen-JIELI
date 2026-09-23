#include "asm/iic.h"
#include "asm/isp_dev.h"
#include "gpio.h"
#include "generic/jiffies.h"
#include "device/iic.h"
#include "device/device.h"
#include "app_config.h"

typedef struct {
    u16 addr;
    u8 value;
} sensor_reg_ini;

typedef struct {
    void *iic;
    u8 reset_io;
    u8 power_down_io;
} camera_iic;
static camera_iic camera[2];

#define OV2659_INPUT_W 	1600
#define OV2659_INPUT_H	1200
#define CONFIG_INPUT_FPS	15


#define OV2659_WRCMD 0x60
#define OV2659_RDCMD 0x61

#define DELAY_TIME	10

static unsigned char wrOV2659Reg(void *iic, u16 regID, unsigned char regDat)
{
    u8 ret = 1;
    dev_ioctl(iic, IOCTL_IIC_START, 0);
    if (dev_ioctl(iic, IOCTL_IIC_TX_BYTE_WITH_START_BIT, OV2659_WRCMD)) {
        ret = 0;
        printf("iic write err!!! line : %d \n", __LINE__);
        goto exit;
    }
    delay(DELAY_TIME);
    if (dev_ioctl(iic, IOCTL_IIC_TX_BYTE, regID >> 8)) {
        ret = 0;
        printf("iic write err!!! line : %d \n", __LINE__);
        goto exit;
    }
    delay(DELAY_TIME);
    if (dev_ioctl(iic, IOCTL_IIC_TX_BYTE, regID & 0xff)) {
        ret = 0;
        printf("iic write err!!! line : %d \n", __LINE__);
        goto exit;
    }
    delay(DELAY_TIME);
    if (dev_ioctl(iic, IOCTL_IIC_TX_BYTE_WITH_STOP_BIT, regDat)) {
        ret = 0;
        printf("iic write err!!! line : %d \n", __LINE__);
        goto exit;
    }
    delay(DELAY_TIME);

exit:
    dev_ioctl(iic, IOCTL_IIC_STOP, 0);
    return ret;
}

static unsigned char rdOV2659Reg(void *iic, u16 regID, unsigned char *regDat)
{
    u8 ret = 1;
    dev_ioctl(iic, IOCTL_IIC_START, 0);
    if (dev_ioctl(iic, IOCTL_IIC_TX_BYTE_WITH_START_BIT, OV2659_WRCMD)) {
        ret = 0;
        printf("iic write err!!! line : %d \n", __LINE__);
        goto exit;
    }
    delay(DELAY_TIME);
    if (dev_ioctl(iic, IOCTL_IIC_TX_BYTE, regID >> 8)) {
        ret = 0;
        goto exit;
    }
    delay(DELAY_TIME);
    if (dev_ioctl(iic, IOCTL_IIC_TX_BYTE_WITH_STOP_BIT, regID & 0xff)) {
        ret = 0;
        printf("iic write err!!! line : %d \n", __LINE__);
        goto exit;
    }
    delay(DELAY_TIME);
    if (dev_ioctl(iic, IOCTL_IIC_TX_BYTE_WITH_START_BIT, OV2659_RDCMD)) {
        ret = 0;
        printf("iic write err!!! line : %d \n", __LINE__);
        goto exit;
    }
    delay(DELAY_TIME);
    dev_ioctl(iic, IOCTL_IIC_RX_BYTE_WITH_STOP_BIT, (u32)regDat);

exit:
    dev_ioctl(iic, IOCTL_IIC_STOP, 0);
    return ret;
}

u16 OV2659_dvp_rd_reg(u8 isp_dev, u16 addr)
{
    void *iic = camera[isp_dev].iic;
    u8 val;

    rdOV2659Reg(iic, addr, &val);
    return val;
}

void OV2659_dvp_wr_reg(u8 isp_dev, u16 addr, u16 val)
{
    void *iic = camera[isp_dev].iic;

    wrOV2659Reg(iic, addr, (u8)val);
}

static sensor_reg_ini OV2659_INI_REG[] = {
    {0x3000, 0x0f},
    {0x3001, 0xff},
    {0x3002, 0xff},
    {0x0100, 0x01},
    {0x3633, 0x3d},
    {0x3620, 0x02},
    {0x3631, 0x11},
    {0x3612, 0x04},
    {0x3630, 0x20},
    {0x4702, 0x02},
    {0x370c, 0x34},
    {0x3004, 0x10},
    {0x3005, 0x18},
    {0x3800, 0x00},
    {0x3801, 0x00},
    {0x3802, 0x00},
    {0x3803, 0x00},
    {0x3804, 0x06},
    {0x3805, 0x5f},
    {0x3806, 0x04},
    {0x3807, 0xb7},
    {0x3808, 0x03},
    {0x3809, 0x20},
    {0x380a, 0x02},
    {0x380b, 0x58},
    {0x380c, 0x05},
    {0x380d, 0x14},
    {0x380e, 0x02},
    {0x380f, 0x68},
    {0x3811, 0x08},
    {0x3813, 0x02},
    {0x3814, 0x31},
    {0x3815, 0x31},
    {0x3a02, 0x02},
    {0x3a03, 0x68},
    {0x3a08, 0x00},
    {0x3a09, 0x5c},
    {0x3a0a, 0x00},
    {0x3a0b, 0x4d},
    {0x3a0d, 0x08},
    {0x3a0e, 0x06},
    {0x3a14, 0x02},
    {0x3a15, 0x28},

    {0x3a19, 0x50},

    {0x3623, 0x00},
    {0x3634, 0x76},
    {0x3701, 0x44},
    {0x3702, 0x18},
    {0x3703, 0x24},
    {0x3704, 0x24},
    {0x3705, 0x0c},
    {0x3820, 0x81},
    {0x3821, 0x07},
    {0x370a, 0x52},
    {0x4608, 0x00},
    {0x4609, 0x80},
    {0x4300, 0x30},
    {0x5086, 0x02},
    {0x5000, 0xfb},
    {0x5001, 0x1f},
    {0x5002, 0x00},
    {0x5025, 0x0e},
    {0x5026, 0x18},
    {0x5027, 0x34},
    {0x5028, 0x4c},
    {0x5029, 0x62},
    {0x502a, 0x74},
    {0x502b, 0x85},
    {0x502c, 0x92},
    {0x502d, 0x9e},
    {0x502e, 0xb2},
    {0x502f, 0xc0},
    {0x5030, 0xcc},
    {0x5031, 0xe0},
    {0x5032, 0xee},
    {0x5033, 0xf6},
    {0x5034, 0x11},
    {0x5070, 0x1c},
    {0x5071, 0x5b},
    {0x5072, 0x05},
    {0x5073, 0x20},
    {0x5074, 0x94},
    {0x5075, 0xb4},
    {0x5076, 0xb4},
    {0x5077, 0xaf},
    {0x5078, 0x05},
    {0x5079, 0x98},
    {0x507a, 0x21},

    {0x5035, 0x6a},
    {0x5036, 0x11},
    {0x5037, 0x92},
    {0x5038, 0x21},

    {0x5039, 0xe1},
    {0x503a, 0x01},
    {0x503c, 0x05},
    {0x503d, 0x08},
    {0x503e, 0x08},
    {0x503f, 0x64},
    {0x5040, 0x58},
    {0x5041, 0x2a},
    {0x5042, 0xc5},
    {0x5043, 0x2e},
    {0x5044, 0x3a},
    {0x5045, 0x3c},
    {0x5046, 0x44},
    {0x5047, 0xf8},
    {0x5048, 0x08},
    {0x5049, 0x70},
    {0x504a, 0xf0},
    {0x504b, 0xf0},

    {0x500c, 0x03},
    {0x500d, 0x20},
    {0x500e, 0x02},
    {0x500f, 0x5c},
    {0x5010, 0x48},
    {0x5011, 0x00},
    {0x5012, 0x66},
    {0x5013, 0x03},
    {0x5014, 0x30},
    {0x5015, 0x02},
    {0x5016, 0x7c},
    {0x5017, 0x40},
    {0x5018, 0x00},
    {0x5019, 0x66},
    {0x501a, 0x03},
    {0x501b, 0x10},
    {0x501c, 0x02},
    {0x501d, 0x7c},
    {0x501e, 0x3a},
    {0x501f, 0x00},
    {0x5020, 0x66},


    {0x506e, 0x44},
    {0x5064, 0x08},
    {0x5065, 0x10},
    {0x5066, 0x12},
    {0x5067, 0x02},
    {0x506c, 0x08},
    {0x506d, 0x10},
    {0x506f, 0xa6},
    {0x5068, 0x08},

    {0x5069, 0x10},
    {0x506a, 0x04},
    {0x506b, 0x12},
    {0x507e, 0x40},
    {0x507f, 0x20},
    {0x507b, 0x02},
    {0x507a, 0x01},
    {0x5084, 0x0c},
    {0x5085, 0x3e},
    {0x5005, 0x80},
    {0x3a0f, 0x30},
    {0x3a10, 0x28},
    {0x3a1b, 0x32},
    {0x3a1e, 0x26},
    {0x3a11, 0x60},
    {0x3a1f, 0x14},
    {0x5060, 0x69},
    {0x5061, 0x7d},
    {0x5062, 0x7d},
    {0x5063, 0x69},

    {0x3011, 0xC2},
    {0x3003, 0x80},
    {0x3004, 0x10},
    {0x3005, 0x10},
    {0x3006, 0x0d},

    {0x3800, 0x00},
    {0x3801, 0x00},
    {0x3802, 0x00},
    {0x3803, 0x00},
    {0x3804, 0x06},
    {0x3805, 0x5f},
    {0x3806, 0x04},
    {0x3807, 0xbb},
    {0x3808, 0x06},
    {0x3809, 0x40},
    {0x380a, 0x04},
    {0x380b, 0xb0},
    {0x380c, 0x07},
    {0x380d, 0x9f},
    {0x380e, 0x04},
    {0x380f, 0xd0},
    {0x3811, 0x10},
    {0x3813, 0x06},
    {0x3814, 0x11},
    {0x3815, 0x11},
    {0x3a02, 0x04},
    {0x3a03, 0xd0},
    {0x3a08, 0x00},
    {0x3a09, 0xb8},
    {0x3a0a, 0x00},
    {0x3a0b, 0x9a},
    {0x3a0d, 0x08},
    {0x3a0e, 0x06},
    {0x3a14, 0x04},
    {0x3a15, 0x50},
    {0x3623, 0x00},
    {0x3634, 0x44},
    {0x3701, 0x44},
    {0x3702, 0x30},
    {0x3703, 0x48},
    {0x3704, 0x48},
    {0x3705, 0x18},
    {0x3820, 0x80},
    {0x3821, 0x06},
    {0x370a, 0x12},
    {0x4608, 0x00},
    {0x4609, 0x80},
    {0x5002, 0x00},
    {0x3003, 0x80},
    {0x3004, 0x20},
    {0x3005, 0x18},
    {0x3006, 0x0d}
};

static void OV2659_config_SENSOR(u8 isp_dev, u16 *width, u16 *height, u8 *format, u8 *frame_freq)
{
    u8 width_l = 0, width_h = 0, height_l = 0, height_h = 0;
    void *iic = camera[isp_dev].iic;

    for (int i = 0; i < sizeof(OV2659_INI_REG) / sizeof(sensor_reg_ini); i++) {
        wrOV2659Reg(iic, OV2659_INI_REG[i].addr, OV2659_INI_REG[i].value);
    }

    rdOV2659Reg(iic, 0x3808, &width_h);
    rdOV2659Reg(iic, 0x3809, &width_l);
    rdOV2659Reg(iic, 0x380a, &height_h);
    rdOV2659Reg(iic, 0x380b, &height_l);

    *width = width_h << 8 | width_l;
    *height = height_h << 8 | height_l;

    *format = SEN_IN_FORMAT_UYVY;
    puts("\nOV2659 UYVY\n");
}

static s32 OV2659_set_output_size(u8 isp_dev, u16 *width, u16 *height, u8 *freq)
{
    return 0;
}

static s32 OV2659_power_ctl(u8 isp_dev, u8 is_work)
{
    return 0;
}

static s32 OV2659_ID_check(void *iic)
{
    u8 h_pid = 0x00;
    u8 l_pid = 0x00;
    u8 sub_id = 0x00;
    u16 pid = 0x00;
    for (int i = 0; i < 3; i++) {
        rdOV2659Reg(iic, 0x300A, &h_pid);
        rdOV2659Reg(iic, 0x300B, &l_pid);
        rdOV2659Reg(iic, 0x302B, &sub_id);
        pid = h_pid << 8 | l_pid;
        printf("OV2659 Sensor ID : 0x%x\n", pid);
        printf("OV2659 Sensor SUB: 0x%x\n", sub_id);
    }
    if (pid != 0x2656 || sub_id != 0x60) {
        return -1;
    }

    return 0;
}

static void OV2659_reset(u8 isp_dev)
{
    u8 res_io;
    u8 powd_io;
    u8 id = 0;
    printf("%s, isp_dev = %d\n\r", __func__, isp_dev);

    res_io = camera[isp_dev].reset_io;
    powd_io = camera[isp_dev].power_down_io;

    if (powd_io != (u8) - 1) {
        gpio_direction_output((u32)powd_io, 0);
    }

    if (res_io != (u8) - 1) {
        gpio_direction_output(res_io, 1);
        gpio_direction_output(res_io, 0);
        os_time_dly(1);
        gpio_direction_output(res_io, 1);
    }
}

static s32 OV2659_check(u8 isp_dev, u32 _reset_gpio, u32 _power_gpio, char *iic_name)
{
    if (isp_dev > 1) {
        return -1;
    }

    if (!camera[isp_dev].iic) {
        camera[isp_dev].iic = dev_open(iic_name, 0);
        camera[isp_dev].reset_io = (u8)_reset_gpio;
        camera[isp_dev].power_down_io = (u8)_power_gpio;
    }

    if (!camera[isp_dev].iic) {
        printf("%s iic open err!!!\n\n", __func__);
        return -1;
    }

    OV2659_reset(isp_dev);

    if (0 != OV2659_ID_check(camera[isp_dev].iic)) {
        printf("-------not OV2659------\n\n");
        dev_close(camera[isp_dev].iic);
        camera[isp_dev].iic = NULL;
        return -1;
    }
    printf("-------hello OV2659------\n\n");

    return 0;
}

static s32 OV2659_init(u8 isp_dev, u16 *width, u16 *height, u8 *format, u8 *frame_freq)
{
    puts("\n\n OV2659_init \n\n");

    OV2659_config_SENSOR(isp_dev, width, height, format, frame_freq);

    return 0;
}

// *INDENT-OFF*
REGISTER_CAMERA(OV2659) = {
    .logo 				= 	"OV2659",
    .isp_dev 			= 	ISP_DEV_NONE,
    .in_format 			= 	SEN_IN_FORMAT_YUYV,
    .out_format 		= 	ISP_OUT_FORMAT_YUV,
    .mbus_type          =   SEN_MBUS_PARALLEL,
    .mbus_config        =   SEN_MBUS_DATA_WIDTH_8B | SEN_MBUS_HSYNC_ACTIVE_HIGH | \
    						SEN_MBUS_PCLK_SAMPLE_FALLING | SEN_MBUS_VSYNC_ACTIVE_HIGH,
    .fps         		= 	CONFIG_INPUT_FPS,
    .sen_size 			= 	{OV2659_INPUT_W, OV2659_INPUT_H},

    .ops                =   {
        .avin_fps           =   NULL,
        .avin_valid_signal  =   NULL,
        .avin_mode_det      =   NULL,
        .sensor_check 		= 	OV2659_check,
        .init 		        = 	OV2659_init,
        .set_size_fps 		=	OV2659_set_output_size,
        .power_ctrl         =   OV2659_power_ctl,


        .sleep 		        =	NULL,
        .wakeup 		    =	NULL,
        .write_reg 		    =	OV2659_dvp_wr_reg,
        .read_reg 		    =	OV2659_dvp_rd_reg,
    }
};
