#include "device/iic.h"
#include "asm/iic.h"
#include "asm/isp_dev.h"
#include "gpio.h"
#include "asm/isp_alg.h"

typedef struct {
    void *iic;
    u8 reset_io;
    u8 power_down_io;
    u32 cur_again;
    u32 cur_dgain;
    u32 cur_expline;
} camera_iic;

static camera_iic camera[2];

#define NT99141_DEVP_INPUT_W    1280
#define NT99141_DEVP_INPUT_H	720

#define CONFIG_INPUT_FPS	30

#define WRCMD 0x54
#define RDCMD 0x55

static unsigned char wrNT99141Reg(void *iic, u16 regID, unsigned char regDat)
{
    u8 ret = 1;

    dev_ioctl(iic, IOCTL_IIC_START, 0);

    if (dev_ioctl(iic, IOCTL_IIC_TX_BYTE_WITH_START_BIT, WRCMD)) {
        ret = 0;
        goto __wend;
    }

    delay(100);

    if (dev_ioctl(iic, IOCTL_IIC_TX_BYTE, regID >> 8)) {
        ret = 0;
        goto __wend;
    }

    delay(100);

    if (dev_ioctl(iic, IOCTL_IIC_TX_BYTE, regID & 0xff)) {
        ret = 0;
        goto __wend;
    }

    delay(100);

    if (dev_ioctl(iic, IOCTL_IIC_TX_BYTE_WITH_STOP_BIT, regDat)) {
        ret = 0;
        goto __wend;
    }

__wend:

    dev_ioctl(iic, IOCTL_IIC_STOP, 0);
    if (ret == 0) {
        printf("wreg iic fail\n");
    }
    return ret;

}

static unsigned char rdNT99141Reg(void *iic, u16 regID, unsigned char *regDat)
{
    u8 ret = 1;
    dev_ioctl(iic, IOCTL_IIC_START, 0);
    if (dev_ioctl(iic, IOCTL_IIC_TX_BYTE_WITH_START_BIT, WRCMD)) {
        ret = 0;
        goto __rend;
    }

    delay(100);

    if (dev_ioctl(iic, IOCTL_IIC_TX_BYTE, regID >> 8)) {
        ret = 0;
        goto __rend;
    }

    if (dev_ioctl(iic, IOCTL_IIC_TX_BYTE_WITH_STOP_BIT, regID & 0xff)) {
        ret = 0;
        goto __rend;
    }

    delay(100);

    if (dev_ioctl(iic, IOCTL_IIC_TX_BYTE_WITH_START_BIT, RDCMD)) {
        ret = 0;
        goto __rend;
    }

    delay(1000);

    dev_ioctl(iic, IOCTL_IIC_RX_BYTE_WITH_STOP_BIT, (u32)regDat);

__rend:

    dev_ioctl(iic, IOCTL_IIC_STOP, 0);
    if (ret == 0) {
        printf("rreg iic fail\n");
    }
    return ret;
}

typedef struct {
    u16 addr;
    u8 value;
} Sensor_reg_ini;

const Sensor_reg_ini NT99141_INI_REG[] = {
    //initial setting
    {0x32F0, 0x01}, //[1:0] YUV: 0:UYVY 1:YUYV 2:VYUY 3:YVYU [7:4] 0:YUV
    {0x3109, 0x04},
    {0x3040, 0x04},
    {0x3041, 0x02},
    {0x3042, 0xFF},
    {0x3043, 0x08},
    {0x3052, 0xE0},
    {0x305F, 0x33},
    {0x3100, 0x07},
    {0x3106, 0x03},

    //pixout driving    要是摄像头出图颜色不对, 可能是输出驱动能力不足, 选择档位0~3
    {0x3069, 0x01},

    {0x3105, 0x01},
    {0x3108, 0x05},
    {0x3110, 0x22},
    {0x3111, 0x57},
    {0x3112, 0x22},
    {0x3113, 0x55},
    {0x3114, 0x05},
    {0x3135, 0x00},

    {0x3290, 0x01},
    {0x3291, 0x80},
    {0x3296, 0x01},
    {0x3297, 0x73},

    {0x3250, 0x80},
    {0x3251, 0x03},
    {0x3252, 0xFF},
    {0x3253, 0x00},
    {0x3254, 0x03},
    {0x3255, 0xFF},
    {0x3256, 0x00},
    {0x3257, 0x50},

    {0x3270, 0x00},
    {0x3271, 0x0C},
    {0x3272, 0x18},
    {0x3273, 0x32},
    {0x3274, 0x44},
    {0x3275, 0x54},
    {0x3276, 0x70},
    {0x3277, 0x88},
    {0x3278, 0x9D},
    {0x3279, 0xB0},
    {0x327A, 0xCF},
    {0x327B, 0xE2},
    {0x327C, 0xEF},
    {0x327D, 0xF7},
    {0x327E, 0xFF},

    {0x3302, 0x00},
    {0x3303, 0x40},
    {0x3304, 0x00},
    {0x3305, 0x96},
    {0x3306, 0x00},
    {0x3307, 0x29},
    {0x3308, 0x07},
    {0x3309, 0xBA},
    {0x330A, 0x06},
    {0x330B, 0xF5},
    {0x330C, 0x01},
    {0x330D, 0x51},
    {0x330E, 0x01},
    {0x330F, 0x30},
    {0x3310, 0x07},
    {0x3311, 0x16},
    {0x3312, 0x07},
    {0x3313, 0xBA},

    {0x3326, 0x02},
    {0x32F6, 0x0F},
    {0x32F9, 0x42},
    {0x32FA, 0x24},
    {0x3325, 0x4A},
    {0x3330, 0x00},
    {0x3331, 0x05},
    {0x3332, 0xFF},
    {0x3338, 0x30},
    {0x3339, 0x84},
    {0x333A, 0x48},
    {0x333F, 0x07},

    {0x3360, 0x10},
    {0x3361, 0x18},
    {0x3362, 0x1f},
    {0x3363, 0x37},
    {0x3364, 0x70},
    {0x3365, 0x60},
    {0x3366, 0x4A},
    {0x3367, 0x30},
    {0x3368, 0x38},
    {0x3369, 0x38},
    {0x336A, 0x28},
    {0x336B, 0x1F},
    {0x336C, 0x00},
    {0x336D, 0x20},
    {0x336E, 0x1C},
    {0x336F, 0x18},
    {0x3370, 0x10},
    {0x3371, 0x38},
    {0x3372, 0x3C},
    {0x3373, 0x3F},
    {0x3374, 0x3F},
    {0x338A, 0x34},
    {0x338B, 0x7F},
    {0x338C, 0x10},
    {0x338D, 0x23},
    {0x338E, 0x7F},
    {0x338F, 0x14},
    {0x3375, 0x0A},
    {0x3376, 0x0C},
    {0x3377, 0x10},
    {0x3378, 0x14},

    {0x32B0, 0x55},
    {0x32B1, 0x69},
    {0x32B2, 0x69},
    {0x32B3, 0x55},
    {0x3012, 0x02},
    {0x3013, 0xD0},
    //PCLK output driving
    {0x306a, 0x01},
    //[YUYV_1280x720_30.00_30.01_Fps]
    {0x32BF, 0x60},
    {0x32C0, 0x5A},
    {0x32C1, 0x5A},
    {0x32C2, 0x5A},
    {0x32C3, 0x00},
    {0x32C4, 0x2a},
    {0x32C5, 0x20},
    {0x32C6, 0x20},
    {0x32C7, 0x00},
    {0x32C8, 0xDD},
    {0x32C9, 0x5A},
    {0x32CA, 0x7A},
    {0x32CB, 0x7A},
    {0x32CC, 0x7A},
    {0x32CD, 0x7A},
    {0x32DB, 0x7B},
    {0x3200, 0x3E},
    {0x3201, 0x0F},
    {0x3028, 0x24},
    {0x3029, 0x20},
    {0x302A, 0x04},
    {0x3022, 0x27}, //24
    {0x3023, 0x24},
    {0x3002, 0x00},
    {0x3003, 0x04},
    {0x3004, 0x00},
    {0x3005, 0x04},
    {0x3006, 0x05},
    {0x3007, 0x03},
    {0x3008, 0x02},
    {0x3009, 0xD3},
    {0x300A, 0x06},
    {0x300B, 0x8B},
    {0x300C, 0x02},
    {0x300D, 0xE0},
    //width
    {0x300E, 0x05},
    {0x300F, 0x00},
    //height
    {0x3010, 0x02},
    {0x3011, 0xD0},
    {0x32B8, 0x3F},
    {0x32B9, 0x31},
    {0x32BB, 0x87},
    {0x32BC, 0x38},
    {0x32BD, 0x3C},
    {0x32BE, 0x34},
    {0x3201, 0x3F},
    {0x3021, 0x06},
    {0x3060, 0x01},

    /* {0x3025,0x02},//彩条 */
};

static void NT99141_config_SENSOR(u8 isp_dev, u16 *width, u16 *height, u8 *format, u8 *frame_freq)
{
    void *iic = camera[isp_dev].iic;

    for (int i = 0; i < sizeof(NT99141_INI_REG) / sizeof(Sensor_reg_ini); i++) {
        wrNT99141Reg(iic, NT99141_INI_REG[i].addr, NT99141_INI_REG[i].value);
    }
}

static s32 NT99141_set_output_size(u8 isp_dev, u16 *width, u16 *height, u8 *freq)
{
    return 0;
}

static s32 NT99141_power_ctl(u8 isp_dev, u8 is_work)
{
    return 0;
}

static s32 NT99141_ID_check(void *iic)
{
    u8 chip;
    u8 ver;
    for (int i = 0; i < 3; i++) {
        rdNT99141Reg(iic, 0x3000, &chip);
        rdNT99141Reg(iic, 0x3001, &ver);
        printf("NT99141 Sensor ID : 0x%x%x\n", chip, ver);
    }
    if (chip != 0x14 || ver != 0x10) {
        printf("-------not NT99141------\n\n");
        return -1;
    }

    printf("-------hello NT99141------\n\n");

    return 0;
}

static void NT99141_reset(u8 isp_dev)
{
    u32 reset_gpio = camera[isp_dev].reset_io;
    u32 pwdn_gpio = camera[isp_dev].power_down_io;
    printf("reset io: %x, power io: %x\n", reset_gpio, pwdn_gpio);

    if (pwdn_gpio != (u8) - 1) {
        gpio_direction_output((u32)pwdn_gpio, 0);
    }
    if (reset_gpio != (u8) - 1) {
        gpio_direction_output(reset_gpio, 1);
        os_time_dly(4);
        gpio_direction_output(reset_gpio, 0);
        os_time_dly(4);
        gpio_direction_output(reset_gpio, 1);
    }
}

static s32 NT99141_check(u8 isp_dev, u32 reset_gpio, u32 pwdn_gpio, char *iic_name)
{
    if (isp_dev > 1) {
        return -1;
    }
    printf("\n\n %s, isp_dev = %d\n\n", __func__, isp_dev);

    if (!camera[isp_dev].iic) {
        camera[isp_dev].iic = dev_open(iic_name, 0);
        camera[isp_dev].reset_io = (u8)reset_gpio;
        camera[isp_dev].power_down_io = (u8)pwdn_gpio;
    }

    if (!camera[isp_dev].iic) {
        printf("%s iic open err!!!\n\n", __func__);
        return -1;
    }

    NT99141_reset(isp_dev);

    if (0 != NT99141_ID_check(camera[isp_dev].iic)) {
        dev_close(camera[isp_dev].iic);
        camera[isp_dev].iic = NULL;
        return -1;
    }
    // ================================

    return 0;
}


static s32 NT99141_init(u8 isp_dev, u16 *width, u16 *height, u8 *format, u8 *frame_freq)
{
    puts("\n\n NT99141_init \n\n");

    NT99141_config_SENSOR(isp_dev, width, height, format, frame_freq);

    return 0;
}


u16 NT99141_dvp_rd_reg(u8 isp_dev, u16 addr)
{
    void *iic = camera[isp_dev].iic;
    u8 val;
    rdNT99141Reg(iic, addr, &val);
    return val;
}

void NT99141_dvp_wr_reg(u8 isp_dev, u16 addr, u16 val)
{
    void *iic = camera[isp_dev].iic;
    wrNT99141Reg(iic, addr, (u8)val);
}

// *INDENT-OFF*
REGISTER_CAMERA(NT99141) = {
    .logo 				= 	"NT99141",
    .isp_dev 			= 	ISP_DEV_NONE,
    .in_format 			= 	SEN_IN_FORMAT_YUYV,
    .out_format 		= 	ISP_OUT_FORMAT_YUV,
    .mbus_type          =   SEN_MBUS_PARALLEL,
    .mbus_config        =   SEN_MBUS_HSYNC_ACTIVE_HIGH | \
    						SEN_MBUS_PCLK_SAMPLE_FALLING | SEN_MBUS_VSYNC_ACTIVE_HIGH,
    .fps         		= 	CONFIG_INPUT_FPS,
    .sen_size 			= 	{NT99141_DEVP_INPUT_W, NT99141_DEVP_INPUT_H},
    .ops                =   {
        .avin_fps           =   NULL,
        .avin_valid_signal  =   NULL,
        .avin_mode_det      =   NULL,
        .sensor_check 		= 	NT99141_check,
        .init 		        = 	NT99141_init,
        .set_size_fps 		=	NT99141_set_output_size,
        .power_ctrl         =   NT99141_power_ctl,


        .sleep 		        =	NULL,
        .wakeup 		    =	NULL,
        .write_reg 		    =	NT99141_dvp_wr_reg,
        .read_reg 		    =	NT99141_dvp_rd_reg,
    }
};
