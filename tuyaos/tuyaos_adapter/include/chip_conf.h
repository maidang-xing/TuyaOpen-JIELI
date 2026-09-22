/**
 * @file chip_conf.h
 * @brief Per-chip configuration for the Jieli platform adapter.
 *
 * The platform serves one vendor family with several silicon revisions
 * (wl82/AC79NN today, wl83/AC792N planned). The TKL sources stay shared;
 * every known silicon difference is funnelled into this header so the
 * per-chip delta remains auditable in one place.
 *
 * Chip selection comes from the board Kconfig (CHIP_WL82 / CHIP_WL83).
 */

#ifndef __CHIP_CONF_H__
#define __CHIP_CONF_H__

#include "tuya_kconfig.h"

#if defined(ENABLE_CHIP_WL83) && (ENABLE_CHIP_WL83 == 1)
#define JIELI_CHIP_WL83 1
#define JIELI_CHIP_WL82 0
#else
#define JIELI_CHIP_WL82 1
#define JIELI_CHIP_WL83 0
#endif

/*
 * wl82 (AC79_AIoT_SDK, verified 2026-09):
 *   - bt_get_mac_addr() exposes the EDR MAC used to derive the BLE address.
 * wl83 (fw-AC792_SDK):
 *   - bt_get_mac_addr() is absent from the headers; derive the BLE address
 *     from le_controller_get_mac() or the board syscfg instead.
 */
#if JIELI_CHIP_WL82
#define JIELI_CHIP_HAS_EDR_MAC_API 1
#else
#define JIELI_CHIP_HAS_EDR_MAC_API 0
#endif

/*
 * Known-compatible surface (measured against both SDKs, 2026-09):
 *   - WiFi event enum: core values 0..21 are identical on both chips.
 *   - TKL vendor symbols: 58/59 identical, only bt_get_mac_addr differs.
 *
 * Porting checklist when enabling wl83 (do NOT hand-copy these):
 *   - WIFI_EVENT values >= 22 differ (792 inserts 5 events at 22).
 *   - ATT_CTRL_BLOCK_SIZE / ATT_PACKET_HEAD_SIZE values in le_common_define.h.
 *   - struct lan_setting field layout in the lwip port header.
 *   - btstack task_info_table stack/priority defaults.
 */

#endif /* __CHIP_CONF_H__ */
