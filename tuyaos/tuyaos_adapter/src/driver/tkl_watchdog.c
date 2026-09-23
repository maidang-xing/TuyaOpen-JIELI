#include "tkl_watchdog.h"

#include "tuya_error_code.h"
#include "generic/typedef.h"
#include "asm/wdt.h"

typedef struct {
    uint8_t code;
    uint32_t ms;
} jieli_wdt_level_t;

static const jieli_wdt_level_t s_jieli_wdt_levels[] = {
    {WDT_1MS, 1},     {WDT_2MS, 2},     {WDT_4MS, 4},     {WDT_8MS, 8},
    {WDT_16MS, 16},   {WDT_32MS, 32},   {WDT_64MS, 64},   {WDT_128MS, 128},
    {WDT_256MS, 256}, {WDT_512MS, 512}, {WDT_1S, 1000},   {WDT_2S, 2000},
    {WDT_4S, 4000},   {WDT_8S, 8000},   {WDT_16S, 16000}, {WDT_32S, 32000},
};

static uint32_t jieli_wdt_select(uint32_t requested_ms, uint8_t *code)
{
    uint32_t i;
    if (requested_ms == 0 || code == NULL) {
        return 0;
    }
    for (i = 0; i < sizeof(s_jieli_wdt_levels) / sizeof(s_jieli_wdt_levels[0]); ++i) {
        if (requested_ms <= s_jieli_wdt_levels[i].ms) {
            *code = s_jieli_wdt_levels[i].code;
            return s_jieli_wdt_levels[i].ms;
        }
    }
    *code = s_jieli_wdt_levels[(sizeof(s_jieli_wdt_levels) / sizeof(s_jieli_wdt_levels[0])) - 1].code;
    return 32000;
}

uint32_t tkl_watchdog_init(TUYA_WDOG_BASE_CFG_T *cfg)
{
    uint8_t code;
    uint32_t actual_ms;
    if (cfg == NULL) {
        return 0;
    }
    actual_ms = jieli_wdt_select(cfg->interval_ms, &code);
    if (actual_ms == 0) {
        return 0;
    }
    wdt_init(code);
    wdt_enable();
    cfg->interval_ms = actual_ms;
    return actual_ms;
}

OPERATE_RET tkl_watchdog_deinit(void)
{
    wdt_close();
    return OPRT_OK;
}

OPERATE_RET tkl_watchdog_refresh(void)
{
    wdt_clear();
    return OPRT_OK;
}
