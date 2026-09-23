#include "tkl_gpio.h"

#include "tuya_error_code.h"
#include "asm/port_waked_up.h"
#include "device/gpio.h"

#include <string.h>

#define JIELI_TKL_GPIO_COUNT 64
#define JIELI_TKL_IRQ_COUNT  2

typedef struct {
    TUYA_GPIO_IRQ_E mode;
    TUYA_GPIO_IRQ_CB cb;
    void *arg;
    uint8_t configured;
} jieli_gpio_irq_cfg_t;

typedef struct {
    TUYA_GPIO_NUM_E pin;
    void *handle;
    uint8_t enabled;
} jieli_gpio_irq_slot_t;

static const int s_jieli_gpio_map[JIELI_TKL_GPIO_COUNT] = {
    IO_PORTA_00, IO_PORTA_01, IO_PORTA_02, IO_PORTA_03, IO_PORTA_04, IO_PORTA_05,
    IO_PORTA_06, IO_PORTA_07, IO_PORTA_08, IO_PORTA_09, IO_PORTA_10,
    IO_PORTB_00, IO_PORTB_01, IO_PORTB_02, IO_PORTB_03, IO_PORTB_04, IO_PORTB_05,
    IO_PORTB_06, IO_PORTB_07, IO_PORTB_08,
    IO_PORTC_00, IO_PORTC_01, IO_PORTC_02, IO_PORTC_03, IO_PORTC_04, IO_PORTC_05,
    IO_PORTC_06, IO_PORTC_07, IO_PORTC_08, IO_PORTC_09, IO_PORTC_10,
    IO_PORTE_00, IO_PORTE_01, IO_PORTE_02, IO_PORTE_03, IO_PORTE_04, IO_PORTE_05,
    IO_PORTE_06, IO_PORTE_07, IO_PORTE_08, IO_PORTE_09,
    IO_PORTH_00, IO_PORTH_01, IO_PORTH_02, IO_PORTH_03, IO_PORTH_04, IO_PORTH_05,
    IO_PORTH_06, IO_PORTH_07, IO_PORTH_08, IO_PORTH_09,
    IO_PORTG_08, IO_PORTG_09, IO_PORTG_10, IO_PORTG_11, IO_PORTG_12, IO_PORTG_13,
    IO_PORTG_14, IO_PORTG_15,
    -1,
    IO_PORT_USB_DPA, IO_PORT_USB_DMA, IO_PORT_USB_DPB, IO_PORT_USB_DMB,
};

static uint8_t s_jieli_open_drain[JIELI_TKL_GPIO_COUNT];
static uint8_t s_jieli_open_drain_pullup[JIELI_TKL_GPIO_COUNT];
static jieli_gpio_irq_cfg_t s_jieli_irq_cfg[JIELI_TKL_GPIO_COUNT];
static jieli_gpio_irq_slot_t s_jieli_irq_slots[JIELI_TKL_IRQ_COUNT];

static OPERATE_RET jieli_gpio_get_native(TUYA_GPIO_NUM_E pin_id, unsigned int *gpio)
{
    if (pin_id >= TUYA_GPIO_NUM_MAX || pin_id >= JIELI_TKL_GPIO_COUNT || gpio == NULL) {
        return OPRT_INVALID_PARM;
    }
    if (s_jieli_gpio_map[pin_id] < 0) {
        return OPRT_NOT_SUPPORTED;
    }
    *gpio = (unsigned int)s_jieli_gpio_map[pin_id];
    return OPRT_OK;
}

static OPERATE_RET jieli_gpio_set_input(unsigned int gpio, TUYA_GPIO_MODE_E mode)
{
    if (gpio_direction_input(gpio) != 0 || gpio_set_die(gpio, 1) != 0) {
        return OPRT_COM_ERROR;
    }

    switch (mode) {
    case TUYA_GPIO_PULLUP:
        if (gpio_set_pull_down(gpio, 0) != 0 || gpio_set_pull_up(gpio, 1) != 0) {
            return OPRT_COM_ERROR;
        }
        break;
    case TUYA_GPIO_PULLDOWN:
        if (gpio_set_pull_up(gpio, 0) != 0 || gpio_set_pull_down(gpio, 1) != 0) {
            return OPRT_COM_ERROR;
        }
        break;
    case TUYA_GPIO_HIGH_IMPEDANCE:
    case TUYA_GPIO_FLOATING:
        if (gpio_set_pull_up(gpio, 0) != 0 || gpio_set_pull_down(gpio, 0) != 0) {
            return OPRT_COM_ERROR;
        }
        break;
    default:
        return OPRT_INVALID_PARM;
    }
    return OPRT_OK;
}

static void jieli_gpio_irq_dispatch(uint32_t slot)
{
    if (slot >= JIELI_TKL_IRQ_COUNT || !s_jieli_irq_slots[slot].enabled) {
        return;
    }

    TUYA_GPIO_NUM_E pin = s_jieli_irq_slots[slot].pin;
    if (pin < TUYA_GPIO_NUM_MAX && s_jieli_irq_cfg[pin].cb != NULL) {
        s_jieli_irq_cfg[pin].cb(s_jieli_irq_cfg[pin].arg);
    }
}

static void jieli_gpio_irq_dispatch_0(void)
{
    jieli_gpio_irq_dispatch(0);
}

static void jieli_gpio_irq_dispatch_1(void)
{
    jieli_gpio_irq_dispatch(1);
}

static void (*const s_jieli_irq_handlers[JIELI_TKL_IRQ_COUNT])(void) = {
    jieli_gpio_irq_dispatch_0,
    jieli_gpio_irq_dispatch_1,
};

OPERATE_RET tkl_gpio_init(TUYA_GPIO_NUM_E pin_id, const TUYA_GPIO_BASE_CFG_T *cfg)
{
    unsigned int gpio;
    OPERATE_RET ret;

    if (cfg == NULL) {
        return OPRT_INVALID_PARM;
    }
    ret = jieli_gpio_get_native(pin_id, &gpio);
    if (ret != OPRT_OK) {
        return ret;
    }

    s_jieli_open_drain[pin_id] = 0;
    s_jieli_open_drain_pullup[pin_id] = 0;

    if (cfg->direct == TUYA_GPIO_INPUT) {
        return jieli_gpio_set_input(gpio, cfg->mode);
    }
    if (cfg->direct != TUYA_GPIO_OUTPUT) {
        return OPRT_INVALID_PARM;
    }

    if (cfg->mode == TUYA_GPIO_OPENDRAIN || cfg->mode == TUYA_GPIO_OPENDRAIN_PULLUP) {
        s_jieli_open_drain[pin_id] = 1;
        s_jieli_open_drain_pullup[pin_id] = (cfg->mode == TUYA_GPIO_OPENDRAIN_PULLUP);
        if (gpio_direction_output(gpio, 0) != 0) {
            return OPRT_COM_ERROR;
        }
        if (s_jieli_open_drain_pullup[pin_id] && gpio_set_pull_up(gpio, 1) != 0) {
            return OPRT_COM_ERROR;
        }
        return OPRT_OK;
    }
    if (cfg->mode != TUYA_GPIO_PUSH_PULL && cfg->mode != TUYA_GPIO_PULLUP &&
        cfg->mode != TUYA_GPIO_PULLDOWN && cfg->mode != TUYA_GPIO_FLOATING) {
        return OPRT_INVALID_PARM;
    }
    if (gpio_direction_output(gpio, cfg->level == TUYA_GPIO_LEVEL_HIGH ? 1 : 0) != 0) {
        return OPRT_COM_ERROR;
    }
    return OPRT_OK;
}

OPERATE_RET tkl_gpio_deinit(TUYA_GPIO_NUM_E pin_id)
{
    unsigned int gpio;
    OPERATE_RET ret = jieli_gpio_get_native(pin_id, &gpio);
    if (ret != OPRT_OK) {
        return ret;
    }

    (void)tkl_gpio_irq_disable(pin_id);
    s_jieli_irq_cfg[pin_id].configured = 0;
    s_jieli_open_drain[pin_id] = 0;
    s_jieli_open_drain_pullup[pin_id] = 0;
    if (gpio_direction_input(gpio) != 0 || gpio_set_pull_up(gpio, 0) != 0 ||
        gpio_set_pull_down(gpio, 0) != 0) {
        return OPRT_COM_ERROR;
    }
    return OPRT_OK;
}

OPERATE_RET tkl_gpio_write(TUYA_GPIO_NUM_E pin_id, TUYA_GPIO_LEVEL_E level)
{
    unsigned int gpio;
    OPERATE_RET ret = jieli_gpio_get_native(pin_id, &gpio);
    if (ret != OPRT_OK) {
        return ret;
    }
    if (level != TUYA_GPIO_LEVEL_LOW && level != TUYA_GPIO_LEVEL_HIGH) {
        return OPRT_INVALID_PARM;
    }

    if (s_jieli_open_drain[pin_id]) {
        if (level == TUYA_GPIO_LEVEL_HIGH) {
            if (gpio_direction_input(gpio) != 0) {
                return OPRT_COM_ERROR;
            }
            if (s_jieli_open_drain_pullup[pin_id] && gpio_set_pull_up(gpio, 1) != 0) {
                return OPRT_COM_ERROR;
            }
        } else if (gpio_direction_output(gpio, 0) != 0) {
            return OPRT_COM_ERROR;
        }
        return OPRT_OK;
    }
    return gpio_direction_output(gpio, level == TUYA_GPIO_LEVEL_HIGH ? 1 : 0) == 0 ? OPRT_OK : OPRT_COM_ERROR;
}

OPERATE_RET tkl_gpio_read(TUYA_GPIO_NUM_E pin_id, TUYA_GPIO_LEVEL_E *level)
{
    unsigned int gpio;
    OPERATE_RET ret;
    if (level == NULL) {
        return OPRT_INVALID_PARM;
    }
    ret = jieli_gpio_get_native(pin_id, &gpio);
    if (ret != OPRT_OK) {
        return ret;
    }
    *level = gpio_read(gpio) ? TUYA_GPIO_LEVEL_HIGH : TUYA_GPIO_LEVEL_LOW;
    return OPRT_OK;
}

OPERATE_RET tkl_gpio_irq_init(TUYA_GPIO_NUM_E pin_id, const TUYA_GPIO_IRQ_T *cfg)
{
    unsigned int gpio;
    OPERATE_RET ret;
    if (cfg == NULL || cfg->cb == NULL) {
        return OPRT_INVALID_PARM;
    }
    if (cfg->mode != TUYA_GPIO_IRQ_RISE && cfg->mode != TUYA_GPIO_IRQ_FALL) {
        return OPRT_NOT_SUPPORTED;
    }
    ret = jieli_gpio_get_native(pin_id, &gpio);
    if (ret != OPRT_OK) {
        return ret;
    }
    (void)gpio;
    (void)tkl_gpio_irq_disable(pin_id);
    s_jieli_irq_cfg[pin_id].mode = cfg->mode;
    s_jieli_irq_cfg[pin_id].cb = cfg->cb;
    s_jieli_irq_cfg[pin_id].arg = cfg->arg;
    s_jieli_irq_cfg[pin_id].configured = 1;
    return OPRT_OK;
}

OPERATE_RET tkl_gpio_irq_enable(TUYA_GPIO_NUM_E pin_id)
{
    unsigned int gpio;
    uint32_t slot;
    PORT_EDGE_E edge;
    void *handle;
    OPERATE_RET ret;

    ret = jieli_gpio_get_native(pin_id, &gpio);
    if (ret != OPRT_OK) {
        return ret;
    }
    if (!s_jieli_irq_cfg[pin_id].configured) {
        return OPRT_INVALID_PARM;
    }
    for (slot = 0; slot < JIELI_TKL_IRQ_COUNT; ++slot) {
        if (s_jieli_irq_slots[slot].enabled && s_jieli_irq_slots[slot].pin == pin_id) {
            return OPRT_OK;
        }
    }
    for (slot = 0; slot < JIELI_TKL_IRQ_COUNT; ++slot) {
        if (!s_jieli_irq_slots[slot].enabled) {
            break;
        }
    }
    if (slot == JIELI_TKL_IRQ_COUNT) {
        return OPRT_NOT_SUPPORTED;
    }

    edge = s_jieli_irq_cfg[pin_id].mode == TUYA_GPIO_IRQ_RISE ? EDGE_POSITIVE : EDGE_NEGATIVE;
    handle = port_wakeup_reg(slot == 0 ? EVENT_IO_0 : EVENT_IO_1, gpio, edge, s_jieli_irq_handlers[slot]);
    if (handle == NULL) {
        return OPRT_COM_ERROR;
    }
    s_jieli_irq_slots[slot].pin = pin_id;
    s_jieli_irq_slots[slot].handle = handle;
    s_jieli_irq_slots[slot].enabled = 1;
    return OPRT_OK;
}

OPERATE_RET tkl_gpio_irq_disable(TUYA_GPIO_NUM_E pin_id)
{
    uint32_t slot;
    if (pin_id >= TUYA_GPIO_NUM_MAX) {
        return OPRT_INVALID_PARM;
    }
    for (slot = 0; slot < JIELI_TKL_IRQ_COUNT; ++slot) {
        if (s_jieli_irq_slots[slot].enabled && s_jieli_irq_slots[slot].pin == pin_id) {
            port_wakeup_unreg(s_jieli_irq_slots[slot].handle);
            memset(&s_jieli_irq_slots[slot], 0, sizeof(s_jieli_irq_slots[slot]));
            s_jieli_irq_slots[slot].pin = TUYA_GPIO_NUM_MAX;
        }
    }
    return OPRT_OK;
}

