#ifndef __TKL_JIELI_CHIP_MAC_H__
#define __TKL_JIELI_CHIP_MAC_H__

#include "tuya_cloud_types.h"
#include "asm/sfc_norflash_api.h"

#include <string.h>

/*
 * Deterministic per-chip MAC derivation for the wl82 adapters.
 *
 * The vendor SDK keeps the BT/WiFi MACs in the VM (syscfg) area, but on this
 * image the syscfg write path does not survive a reboot (vendor and TKL
 * writes alike), and the vendor fallback mixes host randomness into a
 * flash-UID hash, so the address drifts on every boot ("wifi use
 * flash_uid+random mac" changing across resets, 2026-09-23).  Fold the
 * factory-programmed 16-byte flash UUID (get_norflash_uuid(), fixed for the
 * life of the chip) into a locally-administered unicast MAC instead:
 * stable across reboots, reflashes and VM relocation without any storage.
 */

#define JIELI_CHIP_MAC_SALT 0xA5

static inline void jieli_chip_mac(uint8_t mac[6])
{
    const uint8_t *uid;
    int i;

    memset(mac, 0, 6);
    uid = (const uint8_t *)get_norflash_uuid();
    for (i = 0; i < 16; i++) {
        mac[i % 6] ^= (uint8_t)(uid[i] + (uint8_t)(i * JIELI_CHIP_MAC_SALT));
    }
    mac[0] |= 0x02; /* locally administered */
    mac[0] &= 0xFE; /* unicast */
    if (0x00 == mac[0] && 0x00 == mac[1] && 0x00 == mac[2] &&
        0x00 == mac[3] && 0x00 == mac[4] && 0x00 == mac[5]) {
        mac[5] = (uint8_t)(~mac[5] | 0x01);
    }
}

#endif /* __TKL_JIELI_CHIP_MAC_H__ */
