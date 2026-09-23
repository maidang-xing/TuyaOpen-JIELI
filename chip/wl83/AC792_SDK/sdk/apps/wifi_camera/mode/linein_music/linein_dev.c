#include "app_config.h"
#include "system/timer.h"
#include "asm/adc_api.h"
#include "linein_dev.h"
#include "device/gpio.h"
#include "event/device_event.h"
#include "app_msg.h"
#include "linein_file.h"


#if TCFG_APP_LINEIN_EN && TCFG_LINEIN_DETECT_ENABLE

#define LINEIN_STU_HOLD		0
#define LINEIN_STU_ON		1
#define LINEIN_STU_OFF		2

#define LINEIN_DETECT_CNT   6//滤波计算

typedef struct {
    struct linein_dev_data *dev;
    u8 cnt;     //滤波计算
    u8 stu;     //当前状态
    u16 timer;  //定时器句柄
    u8 online;  //是否在线
    u8 active;  //进入sniff的判断标志
    u8 init;    //初始化完成标志
    u8 step;    //检测阶段
} line_dev_t;

static line_dev_t linein_dev_hdl;

#define __this 	(&linein_dev_hdl)

extern u8 uuid2gpio(u16 uuid);

/*----------------------------------------------------------------------------*/
/*@brief   获取linein是否在线
  @param
  @return  1:在线 0：不在线
  @note    app通过这个接口判断linein是否在线
 */
/*----------------------------------------------------------------------------*/
int linein_is_online(void)
{
    return __this->online;
}

/*----------------------------------------------------------------------------*/
/*@brief    设置inein是否在线
  @param    1:在线 0：不在线
  @return   null
  @note     检测驱动通过这个接口判断linein是否在线
 */
/*----------------------------------------------------------------------------*/
void linein_set_online(u8 online)
{
    __this->online = !!online;
}

/*----------------------------------------------------------------------------*/
/*@brief    发布设备上下线消息
  @param    上下线消息
 */
/*----------------------------------------------------------------------------*/
static void linein_event_notify(int arg)
{
    struct device_event event = {0};
    event.event = arg;
    device_event_notify(DEVICE_EVENT_FROM_LINEIN, &event);
}

/*----------------------------------------------------------------------------*/
/*@brief    检测前使能io
  @param    null
  @return   null
  @note     检测驱动检测前使能io ，检测完成后设为高阻 可以节约功耗
  (io检测、sd复用ad检测动态使用，单独ad检测不动态修改)
 */
/*----------------------------------------------------------------------------*/
static void linein_io_start(void)
{
    struct linein_dev_data *linein_dev = (struct linein_dev_data *)__this->dev;
    if (__this->init) {
        return;
    }

    __this->init = 1;

    if (linein_dev->down) {
        gpio_set_mode(linein_dev->port, GPIO_INPUT_PULL_DOWN_10K);
    } else if (linein_dev->up) {
        gpio_set_mode(linein_dev->port, GPIO_INPUT_PULL_UP_10K);
    } else {
        gpio_set_mode(linein_dev->port, GPIO_INPUT_FLOATING);
    }

    if (linein_dev->ad_channel == -1) {
    } else {
        gpio_set_mode(linein_dev->port, GPIO_HIGHZ);
    }
}

/*----------------------------------------------------------------------------*/
/*@brief    检测完成关闭使能io
  @param    null
  @return   null
  @note     检测驱动检测前使能io ，检测完成后设为高阻 可以节约功耗
  (io检测、sd复用ad检测动态使用，单独ad检测不动态修改)
 */
/*----------------------------------------------------------------------------*/
static void linein_io_stop(void)
{
    struct linein_dev_data *linein_dev = (struct linein_dev_data *)__this->dev;
    if (!__this->init) {
        return;
    }

    __this->init = 0;
    gpio_set_mode(linein_dev->port, GPIO_DEINIT);
}

#if !TCFG_LINEIN_MULTIPLEX_WITH_SD
/*----------------------------------------------------------------------------*/
/*@brief    检测是否在线
  @param    驱动句柄
  @return   1:有设备插入 0：没有设备插入
  @note     检测驱动检测前使能io ，检测完成后设为高阻 可以节约功耗
  (io检测、sd复用ad检测动态使用，单独ad检测不动态修改)
 */
/*----------------------------------------------------------------------------*/
static int linein_sample_detect(void *arg)
{
    struct linein_dev_data *linein_dev = (struct linein_dev_data *)arg;
    u8 cur_stu;

    if (linein_dev->ad_channel == -1) {
        linein_io_start();
        cur_stu = gpio_read(linein_dev->port) ? false : true;
        linein_io_stop();
        if (!linein_dev->up) {
            cur_stu	= !cur_stu;
        }
    } else {
        cur_stu = adc_get_voltage(linein_dev->ad_channel) > linein_dev->ad_vol * 10 ? false : true;
        /* printf("<%d> <%d> \n", adc_get_voltage(linein_dev->ad_channel), cur_stu); */
    }

    return cur_stu;
}

#else

/*----------------------------------------------------------------------------*/
/*@brief    sd_cmd 复用检测是否在线
  @param    驱动句柄
  @return   1:有设备插入 0：没有设备插入
  @note     检测驱动检测前使能io ，检测完成后设为高阻 可以节约功耗
  (io检测、sd复用ad检测动态使用，单独ad检测不动态修改)
 */
/*----------------------------------------------------------------------------*/
static int linein_sample_mult_sd(void *arg)
{
    struct linein_dev_data *linein_dev = (struct linein_dev_data *)arg;

    linein_io_start();

    u8 cur_stu;

    if (linein_dev->ad_channel == -1) {
        cur_stu = gpio_read(linein_dev->port) ? false : true;
    } else {
        u16 ad_value = adc_get_value_blocking(linein_dev->ad_channel);
        cur_stu = ad_value > linein_dev->ad_vol ? false : true;
    }

    linein_io_stop();

    return cur_stu;
}
#endif

/*----------------------------------------------------------------------------*/
/*@brief    注册的定时器回调检测函数
  @note     定时进行检测
 */
/*----------------------------------------------------------------------------*/
static void linein_detect(void *arg)
{
    int cur_stu;

#if TCFG_LINEIN_MULTIPLEX_WITH_SD
    if (sd_io_suspend(TCFG_LINEIN_SD_PORT, 0) == 0) {//判断sd 看是否空闲
        cur_stu = linein_sample_mult_sd(arg);
        sd_io_resume(TCFG_LINEIN_SD_PORT, 0);//使用完，回复sd
    } else {
        return;
    }
#else
    if (__this->step == 0) {
        __this->step = 1;
        sys_timer_modify(__this->timer, 30);//猜测是检测状态变化的时候改变定时器回调时间
        return;
    }
    cur_stu = linein_sample_detect(arg);
    if (!__this->active) {
        __this->step = 0;
        sys_timer_modify(__this->timer, 500);//猜测是检测状态不变化的时候改变定时器回调时间
    }
#endif

    if (cur_stu != __this->stu) {
        __this->stu = cur_stu;
        __this->cnt = 0;
        __this->active = 1;
    } else {
        __this->cnt++;
    }

    //滤波计算
    if (__this->cnt < LINEIN_DETECT_CNT) {
        return;
    }

    __this->active = 0; //检测一次完成

    if ((linein_is_online()) && (!__this->stu)) {
        linein_set_online(false);
        linein_event_notify(DEVICE_EVENT_OUT);  //发布下线消息
    } else if ((!linein_is_online()) && (__this->stu)) {
        linein_set_online(true);
        linein_event_notify(DEVICE_EVENT_IN);   //发布上线消息
    }
}

void linein_detect_timer_add(void)
{
    if (!__this->dev) {
        return;
    }
    if (__this->timer == 0) {
        __this->timer = sys_timer_add_to_task("sys_timer", __this->dev, linein_detect, 500);
    }
}

void linein_detect_timer_del(void)
{
    if (__this->timer) {
        sys_timer_del(__this->timer);
        __this->timer = 0;
    }
}

static int linein_driver_init(const struct dev_node *node,  void *arg)
{
    struct linein_dev_data *linein_dev = (struct linein_dev_data *)arg;
    if (!linein_dev) {
        linein_set_online(true);
        return 0;
    }
#if TCFG_LINEIN_DETECT_ENABLE == 0
    linein_set_online(true);//没有配置detcct 默认在线
    return 0;
#else
    linein_dev->port    =  TCFG_LINEIN_DETECT_IO;
    linein_dev->up      =  TCFG_LINEIN_DETECT_PULL_UP_ENABLE;
    linein_dev->down    =  TCFG_LINEIN_DETECT_PULL_DOWN_ENABLE;
#if TCFG_LINEIN_AD_DETECT_ENABLE
    linein_dev->ad_channel = adc_io2ch(linein_dev->port);
    linein_dev->ad_vol =  TCFG_LINEIN_AD_DETECT_VALUE;
#endif

    if (linein_dev->port == -1) {
        linein_set_online(true);    //配置的io 不在范围 ，默认在线
        return 0;
    }

    linein_set_online(false);

#if !TCFG_LINEIN_MULTIPLEX_WITH_SD
    //复用情况和io检测仅在使用的时候配置io
    if (linein_dev->ad_channel != -1) {
        linein_io_start();  //初始化io
        adc_add_sample_ch(linein_dev->ad_channel);
    }
#endif

    __this->dev = linein_dev;
    __this->timer = sys_timer_add_to_task("sys_timer", arg, linein_detect, 500);
#endif
    return 0;
}

const struct device_operations linein_detect_dev_ops = {
    .init = linein_driver_init,
};

#else

int linein_is_online(void)
{
    return 1;
}

#endif
