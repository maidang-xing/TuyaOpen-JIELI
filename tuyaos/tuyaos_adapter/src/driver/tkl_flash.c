#include "tkl_flash.h"
#include "tuya_error_code.h"
#include "asm/sfc_norflash_api.h"
#include "vm.h"

#include <string.h>

/*
 * TuyaOpen data lives in a vendor reserved flash window (TUYA_ADR/OPT=1 in
 * the generated isd_config.ini, injected by jieli_build.py after make
 * pre_build).  The dual-bank OTA layout gives the second app bank the area
 * between the code boundary and the first reserved region and protects it
 * as code, so the window must stay above that bank and below the vendor
 * USER area at 0x3F5000.  Measured FLASH INFO with a ~1.06 MiB app:
 *
 *   bank0 [0x2000, 0x1CD000)   running app (protected as code)
 *   app2  [0x1CD000, 0x397000) OTA target bank, ~1.86 MiB capacity
 *   VM/BTIF [0x397000, 0x3A0000) vendor areas (placed automatically)
 *   TUYA  [0x3A0000, 0x3F5000) this window, OPT=1 (never erased/protected)
 *   USER  [0x3F5000, 0x3F6000) vendor area
 *
 * The exact offsets are kept here in one place so a board can override them
 * when its production partition table is known.
 */
#define JIELI_FLASH_SIZE       (4U * 1024U * 1024U)
#define JIELI_FLASH_BLOCK      (4U * 1024U)
#define JIELI_KV_KEY_START     0x003A0000U
#define JIELI_KV_KEY_SIZE      JIELI_FLASH_BLOCK
#define JIELI_KV_DATA_START    0x003A1000U
#define JIELI_KV_DATA_SIZE     (64U * 1024U)
#define JIELI_UF_START         0x003B1000U
#define JIELI_UF_SIZE          (192U * 1024U)
#define JIELI_RCD_START        0x003E1000U
#define JIELI_RCD_SIZE         (80U * 1024U)

static OPERATE_RET jieli_flash_check_range(uint32_t addr, uint32_t size)
{
    if (addr >= JIELI_FLASH_SIZE || size > JIELI_FLASH_SIZE - addr) {
        return OPRT_INVALID_PARM;
    }
    return OPRT_OK;
}

OPERATE_RET tkl_flash_read(uint32_t addr, uint8_t *dst, uint32_t size)
{
    if (NULL == dst || OPRT_OK != jieli_flash_check_range(addr, size)) {
        return OPRT_INVALID_PARM;
    }
    return (norflash_read(NULL, dst, size, addr) == (int)size) ? OPRT_OK : OPRT_COM_ERROR;
}

OPERATE_RET tkl_flash_write(uint32_t addr, const uint8_t *src, uint32_t size)
{
    if (NULL == src || OPRT_OK != jieli_flash_check_range(addr, size)) {
        return OPRT_INVALID_PARM;
    }
    return (norflash_write(NULL, (void *)src, size, addr) == (int)size) ? OPRT_OK : OPRT_COM_ERROR;
}

OPERATE_RET tkl_flash_erase(uint32_t addr, uint32_t size)
{
    if (0U == size || (addr % JIELI_FLASH_BLOCK) != 0U || (size % JIELI_FLASH_BLOCK) != 0U ||
        OPRT_OK != jieli_flash_check_range(addr, size)) {
        return OPRT_INVALID_PARM;
    }
    return sfc_erase_zone(addr, size) ? OPRT_OK : OPRT_COM_ERROR;
}

OPERATE_RET tkl_flash_lock(uint32_t addr, uint32_t size)
{
    (void)addr;
    (void)size;
    return OPRT_OK;
}

OPERATE_RET tkl_flash_unlock(uint32_t addr, uint32_t size)
{
    (void)addr;
    (void)size;
    return OPRT_OK;
}

OPERATE_RET tkl_flash_get_one_type_info(TUYA_FLASH_TYPE_E type, TUYA_FLASH_BASE_INFO_T *info)
{
    if (NULL == info) {
        return OPRT_INVALID_PARM;
    }
    memset(info, 0, sizeof(*info));
    info->partition_num = 1;
    info->partition[0].block_size = JIELI_FLASH_BLOCK;

    switch (type) {
    case TUYA_FLASH_TYPE_KV_KEY:
        info->partition[0].start_addr = JIELI_KV_KEY_START;
        info->partition[0].size = JIELI_KV_KEY_SIZE;
        break;
    case TUYA_FLASH_TYPE_KV_DATA:
        info->partition[0].start_addr = JIELI_KV_DATA_START;
        info->partition[0].size = JIELI_KV_DATA_SIZE;
        break;
    case TUYA_FLASH_TYPE_UF:
        info->partition[0].start_addr = JIELI_UF_START;
        info->partition[0].size = JIELI_UF_SIZE;
        break;
    case TUYA_FLASH_TYPE_RCD:
        info->partition[0].start_addr = JIELI_RCD_START;
        info->partition[0].size = JIELI_RCD_SIZE;
        break;
    default:
        memset(info, 0, sizeof(*info));
        return OPRT_NOT_SUPPORTED;
    }
    return OPRT_OK;
}
