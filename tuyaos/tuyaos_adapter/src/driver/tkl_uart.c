#include "tkl_uart.h"
#include "tuya_error_code.h"

#include "device.h"
#include "uart.h"

#define TKL_UART_PORT_MAX 2

enum jieli_uart_ioctl_cmd {
    JIELI_UART_IOCTL_SET_RECV_BLOCK,
    JIELI_UART_IOCTL_SET_BAUDRATE,
    JIELI_UART_IOCTL_START,
};

static void *s_uart_handles[TKL_UART_PORT_MAX];

static const char *jieli_uart_device_name(TUYA_UART_NUM_E port_id)
{
    if (port_id == 0u) {
        return "uart0";
    }
#if defined(JIELI_SELECTED_CHIP_WL83)
    if (port_id == 1u) {
        return "uart2";
    }
#endif
    return NULL;
}

static uint32_t jieli_uart_ioctl(enum jieli_uart_ioctl_cmd cmd)
{
#if defined(JIELI_SELECTED_CHIP_WL83)
    switch (cmd) {
    case JIELI_UART_IOCTL_SET_RECV_BLOCK:
        return IOCTL_UART_SET_RECV_BLOCK;
    case JIELI_UART_IOCTL_SET_BAUDRATE:
        return IOCTL_UART_SET_BAUDRATE;
    case JIELI_UART_IOCTL_START:
        return IOCTL_UART_START;
    default:
        return 0u;
    }
#elif defined(JIELI_SELECTED_CHIP_WL82)
    switch (cmd) {
    case JIELI_UART_IOCTL_SET_RECV_BLOCK:
        return UART_SET_RECV_BLOCK;
    case JIELI_UART_IOCTL_SET_BAUDRATE:
        return UART_SET_BAUDRATE;
    case JIELI_UART_IOCTL_START:
        return UART_START;
    default:
        return 0u;
    }
#else
#error "Jieli UART mapping requires a selected chip"
#endif
}

OPERATE_RET tkl_uart_init(TUYA_UART_NUM_E port_id, TUYA_UART_BASE_CFG_T *cfg)
{
    const char *device_name;

    if (port_id >= TUYA_UART_NUM_MAX || port_id >= TKL_UART_PORT_MAX || cfg == NULL) {
        return OPRT_INVALID_PARM;
    }
    device_name = jieli_uart_device_name(port_id);
    if (device_name == NULL) {
        return OPRT_NOT_SUPPORTED;
    }
    if (s_uart_handles[port_id] != NULL) {
        return OPRT_OK;
    }

    s_uart_handles[port_id] = dev_open(device_name, NULL);
    if (s_uart_handles[port_id] != NULL &&
        (dev_ioctl(s_uart_handles[port_id], jieli_uart_ioctl(JIELI_UART_IOCTL_SET_RECV_BLOCK), 1u) != 0 ||
         dev_ioctl(s_uart_handles[port_id], jieli_uart_ioctl(JIELI_UART_IOCTL_SET_BAUDRATE), cfg->baudrate) != 0 ||
         dev_ioctl(s_uart_handles[port_id], jieli_uart_ioctl(JIELI_UART_IOCTL_START), 0u) != 0)) {
        dev_close(s_uart_handles[port_id]);
        s_uart_handles[port_id] = NULL;
    }
    if (s_uart_handles[port_id] == NULL) {
        return OPRT_OS_ADAPTER_UART_INIT_FAILED;
    }
    return OPRT_OK;
}

OPERATE_RET tkl_uart_deinit(TUYA_UART_NUM_E port_id)
{
    if (port_id >= TUYA_UART_NUM_MAX || port_id >= TKL_UART_PORT_MAX || s_uart_handles[port_id] == NULL) {
        return OPRT_INVALID_PARM;
    }
    dev_close(s_uart_handles[port_id]);
    s_uart_handles[port_id] = NULL;
    return OPRT_OK;
}

int tkl_uart_write(TUYA_UART_NUM_E port_id, void *buff, uint16_t len)
{
    if (port_id >= TUYA_UART_NUM_MAX || port_id >= TKL_UART_PORT_MAX || s_uart_handles[port_id] == NULL ||
        buff == NULL) {
        return OPRT_INVALID_PARM;
    }
    int ret = dev_write(s_uart_handles[port_id], buff, len);
    return ret < 0 ? OPRT_OS_ADAPTER_UART_SEND_FAILED : ret;
}

void tkl_uart_rx_irq_cb_reg(TUYA_UART_NUM_E port_id, TUYA_UART_IRQ_CB rx_cb)
{
    (void)port_id;
    (void)rx_cb;
}

void tkl_uart_tx_irq_cb_reg(TUYA_UART_NUM_E port_id, TUYA_UART_IRQ_CB tx_cb)
{
    (void)port_id;
    (void)tx_cb;
}

int tkl_uart_read(TUYA_UART_NUM_E port_id, void *buff, uint16_t len)
{
    if (port_id >= TUYA_UART_NUM_MAX || port_id >= TKL_UART_PORT_MAX || s_uart_handles[port_id] == NULL ||
        buff == NULL) {
        return OPRT_INVALID_PARM;
    }
    int ret = dev_read(s_uart_handles[port_id], buff, len);
    return ret < 0 ? OPRT_OS_ADAPTER_UART_READ_FAILED : ret;
}

OPERATE_RET tkl_uart_set_tx_int(TUYA_UART_NUM_E port_id, BOOL_T enable)
{
    (void)port_id;
    (void)enable;
    return OPRT_NOT_SUPPORTED;
}

OPERATE_RET tkl_uart_set_rx_flowctrl(TUYA_UART_NUM_E port_id, BOOL_T enable)
{
    (void)port_id;
    (void)enable;
    return OPRT_NOT_SUPPORTED;
}

OPERATE_RET tkl_uart_wait_for_data(TUYA_UART_NUM_E port_id, int timeout_ms)
{
    (void)port_id;
    (void)timeout_ms;
    return OPRT_NOT_SUPPORTED;
}

OPERATE_RET tkl_uart_ioctl(TUYA_UART_NUM_E port_id, uint32_t cmd, void *arg)
{
    (void)port_id;
    (void)cmd;
    (void)arg;
    return OPRT_NOT_SUPPORTED;
}
