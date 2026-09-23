#include "app_config.h"
#include "system/includes.h"
#include "asm/pwm.h"
#include "asm/gpio.h"
#include "device/device.h"

/*********************************PWM设备例子****************************************************
  支持使用board.c板级配置初始化、自定义配置初始化，IOCTL命令基本支持多通道控制
  PWM通过dev_ioctl控制，cmd命令见pwm.h
************************************************************************************************/

#ifdef USE_PWM_TEST_DEMO


#define PWM_CHANNEL       (PWMCH3_H | PWMCH3_L)
// #define PWM_CHANNEL       (PWMCH3_H)
// #define PWM_CHANNEL       (PWM_TIMER4_OPCH)
#define PWM_FREQ          4800
// #define PWM_FREQ          (2 * 1000 * 1000)
#define PWM_DUTY          80
#define PWM_POINT_BIT     2

struct pwm_platform_data pwm = {
    .timer_pwm_port    = {-1/*TMR2*/, -1/*TMR3*/, IO_PORTA_04/*TMR4*/, -1/*TMR5*/},
    .mcpwm_port        = {
        -1/*MCPWM0H*/, -1/*MCPWM1H*/, -1/*MCPWM2H*/, IO_PORTA_04/*MCPWM3H*/,
        -1/*MCPWM0L*/, -1/*MCPWM1L*/, -1/*MCPWM2L*/, IO_PORTA_06/*MCPWM3L*/,
    },

    .pwm_config        = {
        .pwm_ch        = PWM_CHANNEL,
        .freq          = PWM_FREQ,
        .duty          = PWM_DUTY,
        .point_bit     = PWM_POINT_BIT,
    },
};

#define PWM_CFG_PRINTF(cfg) \
    printf("pwm: ch=0x%x, duty=%2.2f%%, point_bit=%d, freq=%dHz\n", \
           (cfg)->pwm_ch, \
           (cfg)->duty, \
           (cfg)->point_bit, \
           (cfg)->freq \
          );

static void pwm_test_task(void *arg)
{
    void *pwm_hdl = NULL;

    // open时第二个参数为NULL则使用board.c板级注册的参数进行初始化，
    // 若不为NULL则按照所传参数配置进行初始化。
    pwm_hdl = dev_open("pwm1", &pwm); // 使用传入的pwm参数进行初始化
    // pwm_hdl = dev_open("pwm1", NULL); // 使用board.c中注册的配置进行初始化

    if (!pwm_hdl) {
        printf("open pwm err !!!\n\n");
        return;
    }

    PWM_CFG_PRINTF(&pwm.pwm_config);

    pwm_config_t pwm_cfg;
    pwm_cfg.pwm_ch = PWM_CHANNEL; // 选择需要控制的通道
    // 早期版本dev_open后，IO直接输出信号。现改为dev_open后需要使用IOCTL_PWM_SET_RUN才输出信号。-2025.12.05
    dev_ioctl(pwm_hdl, IOCTL_PWM_SET_RUN, (u32)&pwm_cfg);//PWM运行
    os_time_dly(300);



#if 0 /* 配置与获取占空比 */
    // 注意:
    // 1.设置占空比时，所传参数的pwm_ch需匹配。
    // 2.且point_bit和duty都需要根据需求配置。
    pwm_cfg.pwm_ch    = PWM_CHANNEL;
    pwm_cfg.duty      = 60;
    pwm_cfg.point_bit = 2;
    // float tmp_duty = 100.0;
    double tmp_duty = 100.0;
    while (1) {
        printf("\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
        tmp_duty = (tmp_duty <= 0.0) ? 100.0 : (tmp_duty - 0.01);
        printf("tmp_duty = %f\n", tmp_duty);
        pwm_cfg.duty = tmp_duty;
        printf("pwm set duty  : %f\n", pwm_cfg.duty);
        PWM_CFG_PRINTF(&pwm_cfg);
        dev_ioctl(pwm_hdl, IOCTL_PWM_SET_DUTY, (u32)&pwm_cfg);//设置占空比
        dev_ioctl(pwm_hdl, IOCTL_PWM_GET_DUTY, (u32)&pwm_cfg);//获取实际的占空比，读回的值在.duty中
        printf("pwm read duty : %f\n", pwm_cfg.duty);
        os_time_dly(200);
    }
#endif


#if 0 /* 设置PWM输出频率 */
    // 注意:
    // 1.设置输出频率时，所传参数的pwm_ch需匹配。
    // 2.duty和point_bit也需要是目标占空比。
    pwm_cfg.pwm_ch    = PWM_CHANNEL;
    pwm_cfg.point_bit = PWM_POINT_BIT;
    pwm_cfg.duty      = PWM_DUTY;
    pwm_cfg.freq      = 3000;
    while (1) {
        printf("\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
        pwm_cfg.freq = (pwm_cfg.freq <= 0) ? PWM_FREQ : (pwm_cfg.freq - 100);
        printf("pwm set freq : %d\n", pwm_cfg.freq);
        PWM_CFG_PRINTF(&pwm_cfg);
        dev_ioctl(pwm_hdl, IOCTL_PWM_SET_FREQ, (u32)&pwm_cfg);//设置频率
        os_time_dly(200);
    }
#endif


#if 0 /* 设置MCPWM死区时间 */
    // 注意:
    // 1.设置死区时间时，所传参数的pwm_ch需匹配（H或L通道至少匹配一个）。
    pwm_cfg.pwm_ch    = PWM_CHANNEL;
    pwm_cfg.deathtime = 0;
    while (1) {
        printf("\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
        printf("deathtime = %d\n", pwm_cfg.deathtime);
        dev_ioctl(pwm_hdl, IOCTL_PWM_SET_DEATH_TIME, (u32)&pwm_cfg);//PWM死区时间设置
        // dev_ioctl(pwm_hdl, IOCTL_PWM_SET_RUN, (u32)&pwm_cfg);//实际使用时应该配置完死区时间后才RUN
        pwm_cfg.deathtime = (pwm_cfg.deathtime >= 31) ? 0 : (pwm_cfg.deathtime + 1);
        os_time_dly(100);
    }
#endif


#if 0 /* 控制PWM暂停、运行 */
    // 注意:
    // 1.所传参数的pwm_ch需匹配。
    pwm_cfg.pwm_ch    = PWM_CHANNEL;
    while (1) {
        printf("\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
        printf("pwm stop\n");
        dev_ioctl(pwm_hdl, IOCTL_PWM_SET_STOP, (u32)&pwm_cfg);//PWM停止
        os_time_dly(300);
        printf("pwm run\n");
        dev_ioctl(pwm_hdl, IOCTL_PWM_SET_RUN, (u32)&pwm_cfg);//PWM运行
        os_time_dly(300);
    }
#endif


#if 0 /* 设置输出波形反向、正向 */
    // 注意:
    // 1.所传参数的pwm_ch需匹配。
    pwm_cfg.pwm_ch    = PWM_CHANNEL;
    while (1) {
        printf("\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
        printf("pwm set REVDIRC\n");
        dev_ioctl(pwm_hdl, IOCTL_PWM_SET_REVDIRC, (u32)&pwm_cfg);//PWM反向
        os_time_dly(300);
        printf("pwm set FORDIRC\n");
        dev_ioctl(pwm_hdl, IOCTL_PWM_SET_FORDIRC, (u32)&pwm_cfg);//PWM正向
        os_time_dly(300);
    }
#endif


#if 0 /* 添加、删除输出通道 */
    // 注意:
    // 1.添加的通道在dev_close前必须通过命令删除。
    struct pwm_platform_data pwm_temp = {
        .timer_pwm_port    = {-1/*TMR2*/, -1/*TMR3*/, -1/*TMR4*/, -1/*TMR5*/},
        .mcpwm_port        = {
            -1/*MCPWM0H*/, -1/*MCPWM1H*/, IO_PORTA_08/*MCPWM2H*/, -1/*MCPWM3H*/,
            -1/*MCPWM0L*/, -1/*MCPWM1L*/, IO_PORTA_10/*MCPWM2L*/, -1/*MCPWM3L*/,
        },
        .pwm_config        = {
            .pwm_ch        = PWMCH2_H | PWMCH2_L,
            .freq          = 9600,
            .duty          = 50,
            .point_bit     = 1,
        },
    };
    while (1) {
        printf("\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
        PWM_CFG_PRINTF(&pwm_temp.pwm_config);
        printf("pwm add channel\n");
        dev_ioctl(pwm_hdl, IOCTL_PWM_SET_ADD_CHANNEL, (u32)&pwm_temp);
        dev_ioctl(pwm_hdl, IOCTL_PWM_SET_RUN, (u32)&pwm_temp.pwm_config);
        os_time_dly(300);

        // 关闭前把添加通道删除
        printf("pwm remove channel\n");
        // dev_ioctl(pwm_hdl, IOCTL_PWM_SET_STOP, (u32)&pwm_temp.pwm_config);
        dev_ioctl(pwm_hdl, IOCTL_PWM_SET_REMOV_CHANNEL, (u32)&pwm_temp);
        os_time_dly(300);
    }
#endif



    dev_close(pwm_hdl);
    printf("pwm test end\n\n");

    while (1) {
        os_time_dly(2);
    }
}

static int c_main_pwm(void)
{
    os_task_create(pwm_test_task, NULL, 12, 1000, 0, "pwm_test_task");
    return 0;
}

late_initcall(c_main_pwm);

#endif ///< USE_PWM_TEST_DEMO
