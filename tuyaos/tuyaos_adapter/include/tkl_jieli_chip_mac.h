/**
 * @file tkl_jieli_chip_mac.h
 * @brief Stable development MAC addresses derived from the JieLi Flash UID.
 */

#ifndef TKL_JIELI_CHIP_MAC_H
#define TKL_JIELI_CHIP_MAC_H

#include <stdint.h>

/* Return 0 on success and -1 if the device UID or address is invalid. */
int jieli_chip_mac_get_wifi(uint8_t mac[6]);
int jieli_chip_mac_set_wifi(const uint8_t mac[6]);
int jieli_chip_mac_get_ble(uint8_t mac[6]);

#endif /* TKL_JIELI_CHIP_MAC_H */
