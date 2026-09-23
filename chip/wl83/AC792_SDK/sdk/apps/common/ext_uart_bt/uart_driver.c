#include "system/includes.h"
#include "app_config.h"
#include "uart.h"

#if INSTR_DEV_UART_ENABLE

#define LOG_TAG         "[UART_DRIVER]"
#define LOG_ERROR_ENABLE
#define LOG_DEBUG_ENABLE
#define LOG_INFO_ENABLE
#define LOG_DUMP_ENABLE
#include "debug.h"

/* 宏定义 */
#define uart_name   "uart2"                     /**< 使用的串口设备名 **/
#define UART_MAX_RECV_SIZE   (64 * 1024)        /**< 最大接收数据大小 **/
#define UART_CBUF_LEN 		(128 * 1024)        /**< cbuf缓存区长度 **/
#define HEADER_FIXED_LEN     10                 /**< 协议头固定头长度 **/

/* 全局变量声明 */
static void *uart_hdl = NULL;                   /**< 串口设备句柄 */
static *cbuf_handle = NULL;                  /**< cbuf句柄 */
static u8 uart_buf[UART_MAX_RECV_SIZE] __attribute__((aligned(32))); /**< 串口接收缓冲区，32字节对齐 */

/*************************************************************************************************/
/**
 * @brief  串口数据发送函数
 *
 * @param[in] data 待发送数据指针
 * @param[in] len  待发送数据长度
 *
 * @return 无
 *
 * @note 通过串口发送指定长度的数据
 */
/*************************************************************************************************/
void uart_dev_write(u8 *data, u32 len)
{
    if (uart_hdl) {
        dev_write(uart_hdl, data, len);
    }
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
    return (uint16_t)(((uint16_t)high_byte << 8) | (uint16_t)low_byte);
}

/**
 * @brief   初始化循环缓冲区
 *
 * @param[in] buf_size 缓冲区大小
 *
 * @return  成功返回cbuffer_t指针，失败返回NULL
 */
static cbuffer_t *uart_cbuf_init(u32 buf_size)
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

/*************************************************************************************************/
/**
 * @brief  串口接收任务
 *
 * @param[in] priv 任务私有参数（未使用）
 *
 * @return 无
 *
 * @note 该任务负责持续接收串口数据并进行处理
 */
/*************************************************************************************************/
static void uart_recevice_task(void *priv)
{
    u8 *recv_buf;
    s32 recv_len = 0;
    int ret = 0;

    /* 分配接收缓冲区 */
    recv_buf = malloc(UART_MAX_RECV_SIZE);
    if (!recv_buf) {
        log_error("malloc uart recv buf err !!!\n");
        return ;
    }

    cbuf_handle = uart_cbuf_init(UART_CBUF_LEN);
    if (cbuf_handle == NULL) {
        log_error("malloc uart cbuf err !!!\n");
        return;
    }

    g_printf("uart_recevice_task start.\n");

    /* 任务主循环 */
    while (1) {
        memset(recv_buf, 0, UART_MAX_RECV_SIZE);
        ret = 0;

        /* 从串口读取数据 */
        recv_len = dev_read(uart_hdl, recv_buf, UART_MAX_RECV_SIZE);
        if (recv_len > 0) {
            do {
                if (cbuf_is_write_able(cbuf_handle, recv_len)) {    //查询cbuf是否有足够空间可写
                    ret = cbuf_write(cbuf_handle, recv_buf, recv_len);  //写入并且更新到cbuf
                }
                os_time_dly(1);
            } while (!ret);
        } else if (recv_len <= 0) {
            /* 接收失败或超时处理 */
            if (recv_len == UART_CIRCULAR_BUFFER_WRITE_OVERLAY) {
                /* 刷新串口缓冲区 */
                log_error("UART_CIRCULAR_BUFFER_WRITE_OVERLAY...\n");
                dev_ioctl(uart_hdl, IOCTL_UART_FLUSH, 0);
            } else if (recv_len == UART_RECV_TIMEOUT) {
                log_error("UART_RECV_TIMEOUT...\n");
            } else if (recv_len == UART_RECV_EXIT) {
                log_error("UART_RECV_EXIT...\n");
            }

            os_time_dly(1);
            continue;
        }
    }
}

/*************************************************************************************************/
/**
 * @brief  串口驱动初始化函数
 *
 * @return 初始化结果
 *
 * @note 初始化串口设备并创建接收任务
 */
/*************************************************************************************************/
int uart_driver_init(void)
{
    int len = sizeof(uart_buf);

    /* 打开串口设备 */
    uart_hdl = dev_open(uart_name, NULL);

    if (!uart_hdl) {
        log_info("open uart err !!!\n");
        return -1;
    }

    /* 1. 设置环形缓冲区地址 */
    dev_ioctl(uart_hdl, IOCTL_UART_SET_CIRCULAR_BUFF_ADDR, (int)uart_buf);

    /* 2. 设置环形缓冲区长度 */
    dev_ioctl(uart_hdl, IOCTL_UART_SET_CIRCULAR_BUFF_LENTH, len);

    /* 3. 设置接收模式为阻塞方式 */
    dev_ioctl(uart_hdl, IOCTL_UART_SET_RECV_BLOCK, 1);

    /* 设置接收超时时间 */
    u32 parm = 500 * 10;  /**< 接收超时时间（单位：ms），需比发送超时时间小 */
    dev_ioctl(uart_hdl, IOCTL_UART_SET_RECV_TIMEOUT, (u32)parm);

    /* 4. 启动串口设备 */
    dev_ioctl(uart_hdl, IOCTL_UART_START, 0);

    printf("---> uart_recv_task start create!!! \n");

    /* 创建串口接收任务 */
    int err = thread_fork("uart_recevice_task", 20, 2048, 0, 0, uart_recevice_task, NULL);
    if (err != OS_ERR_NONE) {
        log_error("create uart_recevice_task fail %x\n", err);
    }

    return err;
}

/**
 * @brief   串口数据解析任务
 *
 * @param[in] priv 任务私有参数（未使用）
 *
 * @return 无
 *
 * @note 该任务负责从循环缓冲区中解析数据包
 */
static void uart_parse_task(void *priv)
{
    printf("%s %d\n", __func__, __LINE__);

    int ret = 0;
    u8 *rbuf;

    /* 分配接收缓冲区 */
    rbuf = malloc(UART_MAX_RECV_SIZE);
    if (!rbuf) {
        log_error("malloc uart recv size err !!!\n");
        return ;
    }

    while (1) {
        memset(rbuf, 0, UART_MAX_RECV_SIZE);

        do {    //读取头数据
            if (cbuf_get_data_size(cbuf_handle) < HEADER_FIXED_LEN) {
                os_time_dly(1);
                continue;
            }
            ret = cbuf_read(cbuf_handle, rbuf, HEADER_FIXED_LEN);
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
        if (data_len == 0 || data_len > (UART_MAX_RECV_SIZE - HEADER_FIXED_LEN)) {
            log_error("无效数据长度: %d", data_len);
            continue;;
        }

        do {    //读取有效数据
            if (cbuf_get_data_size(cbuf_handle) < data_len) {
                os_time_dly(1);
                continue;
            }
            ret = cbuf_read(cbuf_handle, rbuf + HEADER_FIXED_LEN, data_len);
            // printf("read data ret : %d\n", ret);
            if (ret == data_len) {
                // put_buf(rbuf, HEADER_FIXED_LEN);
                break;
            }
            os_time_dly(1);
        } while (1);

        printf("\n uart rx ok!***len:%d*****\n", HEADER_FIXED_LEN + data_len);
        pack_parseread(rbuf, HEADER_FIXED_LEN + data_len);
    }
}

/**
 * @brief   串口解析初始化函数
 *
 * @return 无
 *
 * @note 创建串口数据解析任务
 */
void uart_parse_init(void)
{
    printf("%s %d\n", __func__, __LINE__);

    int err = thread_fork("uart_parse_task", 15, 2048, 0, 0, uart_parse_task, NULL);
    if (err != OS_ERR_NONE) {
        log_error("creat uart_parse_task fail %x\n", err);
    }
}

#endif
