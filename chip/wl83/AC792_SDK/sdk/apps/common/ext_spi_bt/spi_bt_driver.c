#include "system/includes.h"
#include "app_config.h"
#include "device/device.h"
#include "asm/spi.h"
#include "device/gpio.h"
#include "asm/exti.h"
#if INSTR_DEV_SPI_ENABLE

#define LOG_TAG         "[SPI_DRIVER]"
#define LOG_ERROR_ENABLE
#define LOG_DEBUG_ENABLE
#define LOG_INFO_ENABLE
#define LOG_DUMP_ENABLE
#include "debug.h"

/* 宏定义 */

//SPI1参考板级配置:
SPI1_PLATFORM_DATA_BEGIN(spi1_data)
.io = {
    .cs_pin             = IO_PORTE_00,
    .di_pin             = IO_PORTE_03,
    .do_pin             = IO_PORTE_01,
    .clk_pin            = IO_PORTE_02,
    .d2_pin             = -1,
    .d3_pin             = -1,
},
.clk                    = 10000000,
 .mode                   = SPI_STD_MODE,
  .priority               = 6,
   .cpu_id                 = 1,
    .hd_level               = 0,
     .attr                   = SPI_SCLK_L_UPL_SMPH,
      .role                   = SPI_MODE_MASTER,
       SPI1_PLATFORM_DATA_END()

#define spi_name   "spi1"
#define SPI_MAX_RECV_SIZE   (16 * 1024)        /**< 最大接收数据大小 **/
#define SPI_CBUF_LEN 		(256 * 1024)        /**< cbuf缓存区长度   读写各一个**/
#define HEADER_FIXED_LEN     10                 /**< 协议头固定头长度 **/
#define SPI_PACK_LEN        532
#define INVALID_WCHAR           ((u8)0x11)        //空写内容

#define SPI_CS  IO_PORTA_01
#define CLIENT_DATA_REQ_IO IO_PORTD_01
#define CLIENT_READY_IO    IO_PORTA_02

#define AC7016_SPI_INT_EDGE	EDGE_NEGATIVE //中断引脚边沿触发:EDGE_NEGATIVE下降沿,EDGE_POSITIVE上升沿

#define PRINTFCOMMBUF 0

       /* 全局变量声明 */
       static void *spi_hdl = NULL;
cbuffer_t *spicbuf_handle = NULL;
cbuffer_t *spiwritecbuf_handle = NULL;
/**< cbuf句柄 */
static u8 spi_buf[SPI_MAX_RECV_SIZE] __attribute__((aligned(32)));
OS_SEM sem_spiclient;

typedef enum {
    CS_TYPE_BEGIN_W = 0,
    CS_TYPE_BEGIN_R,
    CS_TYPE_END,
} CS_CTRL_TYPE;



/*************************************************************************************************/
/**
 * @brief  控制CS电平
 *
 * @param[in] val:  0主机写：拉低50us；1主机读：拉低100us；2结束：拉低200us
  *
 * @return 无
 *
  */
/*************************************************************************************************/
void set_spi_cs(CS_CTRL_TYPE val)
{
    if (val < CS_TYPE_END) { //开始读写时拉低CS
        gpio_direction_output(SPI_CS, 0);
    } else { //结束时拉高
        delay_us(10);
        gpio_direction_output(SPI_CS, 1);
        delay_us(5);
    }
}

//返回从机是否有数据需要主机读
u32 get_client_status()
{
    return gpio_read(CLIENT_DATA_REQ_IO);
}

//返回从机是否通讯就绪
u32 get_client_ready()
{
    return gpio_read(CLIENT_READY_IO);
}
//等从机是否从空闲状态切到就绪状态
u32 wait_client_ready()
{
    u32 count = 0;
    gpio_direction_output(IO_PORTA_09, 0);
    while (get_client_ready()) {
        count++;
        delay_us(1);
        if (count > 50000) {
            log_error("wait client ready RW timeout>50ms\n");
            return -1;
        }
    }
    gpio_direction_output(IO_PORTA_09, 1);
    return 0;
}
//等从机切到空闲状态
u32 wait_client_free()
{
    u32 count = 0;
    while (get_client_ready() == 0) {
        count++;
        delay_us(10);
        if (count > 5000) {
            log_error("wait client to free status timeout>50ms\n");
            return -1;
        }
    }
    return 0;
}
/*************************************************************************************************/
/**
 * @brief  SPI数据发送函数，若写cbuf里还有空间，则直接写入后返回，若无，则等待
 *
 * @param[in] data 待发送数据指针
 * @param[in] len  待发送数据长度
 *
 * @return 无
 *
 * @note 通过spi发送指定长度的数据，为简化从机接收，改成定长，长度为SPI_PACK_LEN
 */
/*************************************************************************************************/

void spi_dev_write(u8 *data, u32 len)
{
    u32 ret;
    u8 real_buf[SPI_PACK_LEN];
    memset(real_buf, 0, SPI_PACK_LEN);
    memcpy(real_buf, data, len);

    ret = 0;
    do {
        if (cbuf_is_write_able(spiwritecbuf_handle, SPI_PACK_LEN)) {
            //查询cbuf是否有足够空间可写
            ret = cbuf_write(spiwritecbuf_handle, real_buf, SPI_PACK_LEN);  //写入并且更新到cbuf
        }
        if (ret == 0) {
            os_time_dly(1);
        }
    } while (!ret);         //将要写的数据先放到写cbuf
    os_sem_post(&sem_spiclient);
    //printf("<Q>");
}

/*************************************************************************************************/
/**
 * @brief  真正往SPI从机写数据函数，从cbuf里取出一包数据写，若无，则固定发全0x11
 *
 * @param[in]flag:0:从cbuf里取数发，1：重发上一包
 * @param[in]
 *
 * @return 无
 *
 * @note 包长度固定为SPI_PACK_LEN
 */
/*************************************************************************************************/
void spi_dev_write_alf(int flag)
{
    static u8 *wr_buf = NULL;
    if (wr_buf == NULL) {
        wr_buf = (u8 *)malloc(SPI_PACK_LEN);
    }

    if (flag == 0) {

        if (cbuf_get_data_size(spiwritecbuf_handle) >= SPI_PACK_LEN) {
            int ret = cbuf_read(spiwritecbuf_handle, wr_buf, SPI_PACK_LEN);

        } else {
            memset(wr_buf, INVALID_WCHAR, SPI_PACK_LEN);
        }
    }
    //printf("wdat->\n");
#if PRINTFCOMMBUF
    printf_buf(wr_buf, SPI_PACK_LEN);
#endif
    delay_us(50);
    dev_write(spi_hdl, wr_buf, SPI_PACK_LEN);
    //printf("<-w\n");
}

void spi_dev_write_CMDPack(u8 cmdtyoe)
{
    static u8 *cmd_buf = NULL;
    if (cmd_buf == NULL) {
        cmd_buf = (u8 *)malloc(SPI_PACK_LEN);
    }

    memset(cmd_buf, cmdtyoe, 16);

    //printf("wcmd:->\n");
    delay_us(150);
    dev_write(spi_hdl, cmd_buf, 16);
    //printf("<-w\n");
}

/**
 * @brief   将两个字节转换为16位无符号整数
 *
 * @param[in] high_byte 高字节
 * @param[in] low_byte  低字节
 *
 * @return  转换后的16位无符号整数
 */
static uint16_t bytes_to_u16(uint8_t high_byte, uint8_t low_byte)
{
    return (uint16_t)((high_byte << 8) | low_byte);
}

/**
 * @brief   初始化循环缓冲区
 *
 * @param[in] buf_size 缓冲区大小
 *
 * @return  成功返回cbuffer_t指针，失败返回NULL
 */
static cbuffer_t *spi_cbuf_init(u32 buf_size)
{
    cbuffer_t *cbuf_handle = NULL;
    cbuf_handle = (cbuffer_t *)malloc(sizeof(cbuffer_t) + buf_size);

    if (cbuf_handle == NULL) {
        printf("cbuf malloc buf err");
        return NULL;
    }

    //cbuf初始化:
    cbuf_init(cbuf_handle, (void *)(cbuf_handle + 1), buf_size);

    return cbuf_handle;
}
//检查包是否有效
int is_pack_valid(u8 *buf, int len)
{
    int isvalid = 1;
    int data_len = bytes_to_u16(buf[HEADER_FIXED_LEN - 1], buf[HEADER_FIXED_LEN - 2]);
    if (data_len == 0 || data_len > (len - HEADER_FIXED_LEN)) {
        isvalid = 0;
    }

    if ((buf[0] != 0xfe) || (buf[1] != 0x55) || (buf[2] != 0xaa)) {
        isvalid = 0;
    }
    if (isvalid) {
        uint16_t calculated_crc = calculate_crc(buf + 7, data_len + 3, 0);
        uint16_t srccrc = (buf[6] << 8) + buf[5];
        //printf("crc %04x -> %04x\n",srccrc,calculated_crc);
        if (calculated_crc != srccrc) {
            isvalid = 0;
            printf("crc err: %04x -> %04x\n", srccrc, calculated_crc);
        }
    }
    return isvalid;
}
/*************************************************************************************************/
/**
 * @brief  spi接收任务
 *
 * @param[in] priv 任务私有参数（未使用）
 *
 * @return 无
 *
 * @note 该任务负责持续接收串口数据并进行处理
 */
/*************************************************************************************************/
static void spi_recevice_task(void *priv)
{
    u8 *recv_buf;
    s32 recv_len = 0;
    int ret = 0;

    /* 分配接收缓冲区 */
    recv_buf = malloc(SPI_MAX_RECV_SIZE);
    if (!recv_buf) {
        log_error("malloc spi recv buf err !!!\n");
        return ;
    }

    spicbuf_handle = spi_cbuf_init(SPI_CBUF_LEN);
    if (spicbuf_handle == NULL) {
        log_error("malloc spi cbuf err !!!\n");
        return;
    }

    //写cbuf
    if (spiwritecbuf_handle == NULL) {
        spiwritecbuf_handle = spi_cbuf_init(SPI_CBUF_LEN);
        if (spiwritecbuf_handle == NULL) {
            log_error("init spi write cbuf err !!!\n");
            return;
        }
    }
    g_printf("spi_recevice_task start.\n");

    /* 任务主循环 */
    while (1) {
        int err, count, writetype;
        char readcmd;

        err = os_sem_pend(&sem_spiclient, 1);

        if (get_client_status() && (cbuf_get_data_size(spiwritecbuf_handle) < SPI_PACK_LEN)) { //如果从机INT已拉低，说明对应数据包已被接收，如果写cbuf里已空，则表明数据此前已写完
            //printf("int is high,wcbuf is empty,skip w&read\n");
            continue;
        }

        memset(recv_buf, 0, SPI_MAX_RECV_SIZE);
        ret = 0;

Readagain:

        if ((cbuf_get_data_size(spiwritecbuf_handle) >= SPI_PACK_LEN)) { //有数据需要写
            writetype = 0;
            while (1) {
                if (wait_client_free()) {
                    break;
                }
                set_spi_cs(CS_TYPE_BEGIN_W);
                if (wait_client_ready()) {
                    set_spi_cs(CS_TYPE_END);
                    os_time_dly(1);
                    break;
                }
                spi_dev_write_CMDPack('W');
                set_spi_cs(CS_TYPE_END);

                if (wait_client_free()) {
                    break;
                }

                set_spi_cs(CS_TYPE_BEGIN_W);
                if (wait_client_ready()) {
                    set_spi_cs(CS_TYPE_END);
                    os_time_dly(1);
                    break;
                }
                spi_dev_write_alf(writetype);
                set_spi_cs(CS_TYPE_END);

                if (wait_client_free()) {
                    break;
                }
                set_spi_cs(CS_TYPE_BEGIN_R);
                if (wait_client_ready()) {
                    set_spi_cs(CS_TYPE_END);
                    os_time_dly(1);
                    break;
                }
                //printf("rd->");
                delay_us(250);
                recv_len = dev_read(spi_hdl, recv_buf, 16);
                set_spi_cs(CS_TYPE_END);
                if (wait_client_free()) {
                    break;
                }
                if ((recv_buf[0] == 'O') && (recv_buf[1] == 'O') && (recv_buf[2] == 'O') && (recv_buf[3] == 'O')) {
                    //从机收到数据正常
                    break;
                } else {
                    //从机收到数据异常
                    printf("client nak:%x %x %x %x writetry\n", recv_buf[0], recv_buf[1], recv_buf[2], recv_buf[3]);
                    writetype = 1;
                }
            }
        }

        if (get_client_status()) { //从机是否有数据需要主机去读
            continue;    //
        }
        if (wait_client_free()) {
            continue;
        }

        readcmd = 'R';

readtry:
        set_spi_cs(CS_TYPE_BEGIN_W);
        if (wait_client_ready()) {
            set_spi_cs(CS_TYPE_END);
            os_time_dly(1);
            continue;
        }
        spi_dev_write_CMDPack(readcmd);
        set_spi_cs(CS_TYPE_END);

        if (wait_client_free()) {
            continue;
        }
        set_spi_cs(CS_TYPE_BEGIN_R);
        if (wait_client_ready()) {
            set_spi_cs(CS_TYPE_END);
            os_time_dly(1);
            continue;
        }
        //printf("rd->");
        delay_us(250);
        recv_len = dev_read(spi_hdl, recv_buf, SPI_PACK_LEN);
        set_spi_cs(CS_TYPE_END);
        if (wait_client_free()) {
            continue;
        }
        //printf("<-erd\n");

        int data_valid = is_pack_valid(recv_buf, SPI_PACK_LEN);

        if (!data_valid) {
            log_error("pack invalid,readtry\n");
            readcmd = 'C';
            goto readtry;
        }

        count = 0;
        while (!get_client_status()) { //读完后检查int是否拉高，如果在50us没有拉高，则认为从机还有数据需要读
            delay_us(5);
            count++;
            //putchar('z');
            if (count >= 10) {
                //printf("int is low,read next\n");
                break;
            }
        }

        int data_len = bytes_to_u16(recv_buf[HEADER_FIXED_LEN - 1], recv_buf[HEADER_FIXED_LEN - 2]);

        if (data_valid) {
            recv_len = data_len + HEADER_FIXED_LEN;//有效的长度
#if PRINTFCOMMBUF
            printf("bt spi recv data:->\n");
            printf_buf(recv_buf, recv_len);
            printf("bt spi recv data end\n");
#endif

            do {
                if (cbuf_is_write_able(spicbuf_handle, recv_len)) {
                    //查询cbuf是否有足够空间可写
                    ret = cbuf_write(spicbuf_handle, recv_buf, recv_len);  //写入并且更新到cbuf
                }
                if (!ret) {
                    os_time_dly(1);
                }
            } while (!ret);

        }
        if ((count >= 10) || (cbuf_get_data_size(spiwritecbuf_handle) >= SPI_PACK_LEN)) { //int还是低或者写CBUF里还有数据 则继续一轮写读
            goto Readagain;
        } else { //否则结束本轮读操作
            printf("int is high & wcbuf has no data ,finish W&read\n");
            //set_spi_cs(CS_TYPE_END);
        }

    }
}

static void spiclient_interrupt(void *arg, u32 parm)
{
    if (parm == CLIENT_DATA_REQ_IO) {
        os_sem_post(&sem_spiclient);
        printf("<P>");
    }

}

/*************************************************************************************************/
/**
 * @brief  SPI驱动初始化函数
 *
 * @return 初始化结果
 *
 * @note 初始化SPI设备并创建接收任务
 */
/*************************************************************************************************/
int spi_driver_init(void)
{
    printf("spi hdl=%x\n", spi_hdl);

    gpio_direction_output(SPI_CS, 1);
    if (spi_hdl) {
        return OS_ERR_NONE;
    }

    spi_hdl = dev_open(spi_name, NULL);
    if (!spi_hdl) {
        printf("dev spi1 open err \n");
        return -1;
    }

    printf("open spi1 success\n");

    // 在同步收/发时，使用信号量等待。(未配置的话默认while等待)
    dev_ioctl(spi_hdl, IOCTL_SPI_SET_USE_SEM, 1);


    gpio_direction_input(CLIENT_READY_IO);
    gpio_set_die(CLIENT_READY_IO, 1);
    gpio_direction_input(CLIENT_DATA_REQ_IO);
    gpio_set_die(CLIENT_DATA_REQ_IO, 1);
    os_sem_create(&sem_spiclient, 0);

    exti_init(CLIENT_DATA_REQ_IO, AC7016_SPI_INT_EDGE, spiclient_interrupt, NULL);

    printf("---> spi_recv_task start create!!! \n");

    /* 创建SPI接收任务 */
    int err = thread_fork("spi_recevice_task", 20, 2048, 0, 0, spi_recevice_task, NULL);
    if (err != OS_ERR_NONE) {
        log_error("create spi_recevice_task fail %x\n", err);
    }

    return err;
}

/**
 * @brief   spi数据解析任务
 *
 * @param[in] priv 任务私有参数（未使用）
 *
 * @return 无
 *
 * @note 该任务负责从循环缓冲区中解析数据包
 */
static void spi_parse_task(void *priv)
{
    printf("%s %d\n", __func__, __LINE__);

    int ret = 0;
    u8 *rbuf;

    /* 分配接收缓冲区 */
    rbuf = spi_buf;

    while (1) {
        memset(rbuf, 0, SPI_MAX_RECV_SIZE);

        do {    //读取头数据
            if (cbuf_get_data_size(spicbuf_handle) < HEADER_FIXED_LEN) {
                os_time_dly(1);
                continue;
            }
            ret = cbuf_read(spicbuf_handle, rbuf, HEADER_FIXED_LEN);
            // printf("read header ret : %d\n", ret);
            if (ret == HEADER_FIXED_LEN) {
                // put_buf(rbuf, HEADER_FIXED_LEN);
                break;
            }
            os_time_dly(1);
        } while (1);

        int data_len = bytes_to_u16(rbuf[HEADER_FIXED_LEN - 1], rbuf[HEADER_FIXED_LEN - 2]);
        // printf("data_len : %d\n", data_len);
        /* 验证数据长度有效性 */
        if (data_len == 0 || data_len > (SPI_MAX_RECV_SIZE - HEADER_FIXED_LEN)) {
            log_error("data len is illegal: %d", data_len);
            continue;;
        }

        do {    //读取有效数据
            if (cbuf_get_data_size(spicbuf_handle) < data_len) {
                os_time_dly(1);
                continue;
            }
            ret = cbuf_read(spicbuf_handle, rbuf + HEADER_FIXED_LEN, data_len);
            // printf("read data ret : %d\n", ret);
            if (ret == data_len) {
                // put_buf(rbuf, HEADER_FIXED_LEN);
                break;
            }
            os_time_dly(1);
        } while (1);

        printf("\n spi rx ok!***len:%d*****\n", HEADER_FIXED_LEN + data_len);
        pack_parseread(rbuf, HEADER_FIXED_LEN + data_len);
    }
}

/**
 * @brief   spi解析初始化函数
 *
 * @return 无
 *
 * @note 创建spi数据解析任务
 */
void spi_parse_init(void)
{
    printf("%s %d\n", __func__, __LINE__);

    int err = thread_fork("spi_parse_task", 15, 2048, 0, 0, spi_parse_task, NULL);
    if (err != OS_ERR_NONE) {
        log_error("creat spi_parse_task fail %x\n", err);
    }
}

#endif

