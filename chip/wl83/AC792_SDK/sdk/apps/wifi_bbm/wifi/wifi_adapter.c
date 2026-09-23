//硬件过滤特定包
#include "system/includes.h"
#include "wifi/wifi_connect.h"
#include "event/net_event.h"
#include "wifi_adapter.h"

//example
void filt_not_my_bssid(void)
{
    wf_rx_filt_set(DROP_NOT_MYBSS);
}

//example
/* void filt_pack_not_need(void) */
/* { */
/* wf_rx_filt_set(DROP_CRC_ERR | DROP_PHY_ERR | DROP_UC_NOME | DROP_VER_ERR | DROP_DROP_MC | DROP_BC \ */
/* | DROP_CFACK | DROP_CFEND | DROP_CTS | DROP_RTS | DROP_BA | DROP_BAR | DROP_CTRL_RSV */
/* | DROP_PSPOLL); */
/* } */
void filt_pack_not_need(void)
{
    wf_rx_filt_set(DROP_CRC_ERR | DROP_PHY_ERR \
                   | DROP_CFACK | DROP_CFEND | DROP_CTS | DROP_PSPOLL | DROP_RTS | DROP_BA | DROP_BAR | DROP_CTRL_RSV);
}

//example
char get_channel_power(void)
{
    char noise;
    do {
        noise = get_current_channel_power();
    } while (!noise);
    return noise;
}

#define CHANNEL_NOISE_DET_CNT 12
static void wf_channel_power_detect_task(void *priv)
{
    char max_noise = -120;
    char min_noise = 0;
    char max_id = 0, min_id = 0;
    for (int i = 1; i < 14; i++) {
        //设置信道
        wifi_set_channel(i);
        os_time_dly(1);

        do {
            int noise_sum_total = 0;
            for (int j = 0; j < CHANNEL_NOISE_DET_CNT; j++) {
                noise_sum_total += get_channel_power();
                os_time_dly(1);
            }

            char average_noise = noise_sum_total / CHANNEL_NOISE_DET_CNT;
            if (average_noise > max_noise) {
                max_noise = average_noise;
                max_id = i;
            }

            if (average_noise < min_noise) {
                min_noise = average_noise;
                min_id = i;
            }
            printf("(channe:%d, noise:%d)\n", i, average_noise);
        } while (0);
    }

    printf("max:(channel: %d, noise: %d)\n", max_id, max_noise);
    printf("min:(channel: %d, noise: %d)\n", min_id, min_noise);
}

void channel_power_detect_example(void)
{
    wf_channel_power_detect_enable();
    thread_fork("wf_channel_power_detect_task", 10, 1024, 0, NULL, wf_channel_power_detect_task, NULL);
}

