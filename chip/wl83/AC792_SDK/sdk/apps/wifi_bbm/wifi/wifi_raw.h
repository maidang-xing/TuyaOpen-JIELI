#ifndef WIFI_RAW_H
#define WIFI_RAW_H

#include "app_config.h"
#include "typedef.h"

#if BBM_WIFI_PA_ENABLE
#define WIFI_DEFAULT_PWR        3                   // 默认使用的发射功率
#define WIFI_MIN_PWR            1                   // 最小发射功率
#define WIFI_MAX_PWR            6                   // 最大发射功率
#else
//不接PA默认最大
#define WIFI_DEFAULT_PWR        9                   // 默认使用的发射功率
#define WIFI_MIN_PWR            9                   // 最大发射功率
#define WIFI_MAX_PWR            9                   // 最大发射功率
#endif

void wifi_raw_init(void);
void wifi_raw_exit(void);

void wifi_raw_set_txrate_val(u8 txrate);
u8 wifi_raw_get_txrate_val(void);
const char *wifi_raw_get_txrate_str(void);
void wifi_raw_set_short_retry(u8 retry);
u8 wifi_raw_get_short_retry(void);
void wifi_raw_set_long_retry(u8 retry);
u8 wifi_raw_get_long_retry(void);
void wifi_raw_set_pwr(u8 pwr);
u8 wifi_raw_get_pwr(void);

#endif // WIFI_RAW_H


