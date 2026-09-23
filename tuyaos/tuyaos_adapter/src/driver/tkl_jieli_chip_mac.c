/**
 * @file tkl_jieli_chip_mac.c
 * @brief Stable, non-persistent development MAC address management.
 */

#include "tkl_jieli_chip_mac.h"

#include "asm/sfc_norflash_api.h"

#include <stdio.h>
#include <string.h>

#define JIELI_FLASH_UID_LEN 16U

static uint8_t s_wifi_mac[6];
static uint8_t s_ble_mac[6];
static uint8_t s_mac_initialized;
static uint8_t s_wifi_mac_overridden;

static int jieli_bytes_are(const uint8_t *bytes, uint32_t length, uint8_t value)
{
    uint32_t i;

    for (i = 0; i < length; i++) {
        if (bytes[i] != value) {
            return 0;
        }
    }
    return 1;
}

static int jieli_mac_is_unicast(const uint8_t mac[6])
{
    return mac != NULL && !jieli_bytes_are(mac, 6, 0x00) && !jieli_bytes_are(mac, 6, 0xFF) &&
           (mac[0] & 0x01U) == 0U;
}

static void jieli_make_ble_static_random(uint8_t mac[6])
{
    uint8_t payload_is_zero;
    uint8_t payload_is_one;

    mac[0] = (uint8_t)((mac[0] & 0x3FU) | 0xC0U);
    payload_is_zero = (uint8_t)((mac[0] & 0x3FU) == 0U && jieli_bytes_are(&mac[1], 5, 0x00));
    payload_is_one = (uint8_t)((mac[0] & 0x3FU) == 0x3FU && jieli_bytes_are(&mac[1], 5, 0xFF));
    if (payload_is_zero) {
        mac[5] = 0x01;
    } else if (payload_is_one) {
        mac[5] = 0xFE;
    }
}

static uint64_t jieli_uid_hash(const uint8_t uid[JIELI_FLASH_UID_LEN])
{
    uint64_t hash = UINT64_C(14695981039346656037);
    uint32_t i;

    /* FNV-1a over a versioned domain and the 16-byte Flash UID. */
    static const uint8_t domain[] = "TuyaOpen-JieLi-dev-mac-v1";
    for (i = 0; i < sizeof(domain) - 1U; i++) {
        hash ^= domain[i];
        hash *= UINT64_C(1099511628211);
    }
    for (i = 0; i < JIELI_FLASH_UID_LEN; i++) {
        hash ^= uid[i];
        hash *= UINT64_C(1099511628211);
    }
    return hash;
}

static int jieli_mac_initialize(void)
{
    const uint8_t *uid;
    uint8_t uid_copy[JIELI_FLASH_UID_LEN];
    uint64_t hash;
    uint32_t i;

    if (s_mac_initialized) {
        return 0;
    }

#if defined(CONFIG_CPU_WL83)
    uid = get_norflash_uuid(0);
#else
    uid = get_norflash_uuid();
#endif
    if (uid == NULL) {
        return -1;
    }
    memcpy(uid_copy, uid, sizeof(uid_copy));
    if (jieli_bytes_are(uid_copy, sizeof(uid_copy), 0x00) ||
        jieli_bytes_are(uid_copy, sizeof(uid_copy), 0xFF)) {
        return -1;
    }

    hash = jieli_uid_hash(uid_copy);
    for (i = 0; i < 6U; i++) {
        s_wifi_mac[i] = (uint8_t)(hash >> (40U - (i * 8U)));
    }
    /* IEEE 802 locally administered unicast address for WiFi. */
    s_wifi_mac[0] = (uint8_t)((s_wifi_mac[0] & 0xFCU) | 0x02U);

    /* Follow the IPC convention of deriving BLE from the shared base MAC,
     * then encode it as a stable BLE random-static address for development. */
    memcpy(s_ble_mac, s_wifi_mac, sizeof(s_ble_mac));
    s_ble_mac[5]++;
    jieli_make_ble_static_random(s_ble_mac);

    memset(uid_copy, 0, sizeof(uid_copy));
    s_mac_initialized = 1;
    printf("[JIELI][MAC] dev UID-derived WiFi %02X:%02X:%02X:%02X:%02X:%02X, BLE static-random %02X:%02X:%02X:%02X:%02X:%02X\n",
           s_wifi_mac[0], s_wifi_mac[1], s_wifi_mac[2], s_wifi_mac[3], s_wifi_mac[4], s_wifi_mac[5],
           s_ble_mac[0], s_ble_mac[1], s_ble_mac[2], s_ble_mac[3], s_ble_mac[4], s_ble_mac[5]);
    return 0;
}

int jieli_chip_mac_get_wifi(uint8_t mac[6])
{
    if (mac == NULL || jieli_mac_initialize() != 0) {
        return -1;
    }
    memcpy(mac, s_wifi_mac, sizeof(s_wifi_mac));
    return 0;
}

int jieli_chip_mac_set_wifi(const uint8_t mac[6])
{
    if (!jieli_mac_is_unicast(mac) || jieli_mac_initialize() != 0) {
        return -1;
    }
    memcpy(s_wifi_mac, mac, sizeof(s_wifi_mac));
    s_wifi_mac_overridden = 1;
    return 0;
}

int jieli_chip_mac_get_ble(uint8_t mac[6])
{
    if (mac == NULL || jieli_mac_initialize() != 0) {
        return -1;
    }
    if (s_wifi_mac_overridden) {
        memcpy(s_ble_mac, s_wifi_mac, sizeof(s_ble_mac));
        s_ble_mac[5]++;
        jieli_make_ble_static_random(s_ble_mac);
    }
    memcpy(mac, s_ble_mac, sizeof(s_ble_mac));
    return 0;
}
