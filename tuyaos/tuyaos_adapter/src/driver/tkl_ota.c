#include "tkl_ota.h"
#include "tuya_error_code.h"
#include "update/net_update.h"

#include <stdint.h>
#include <stdio.h>

/*
 * OTA rides the vendor dual-bank (双备份) update machinery, the same bridge
 * the official ipc_ac7916a reference uses.  TuyaOpen streams the exact bytes
 * of the db_update_files_data.bin package (uploaded to the cloud as the UG
 * artifact); net_fopen routes the CONFIG_UPGRADE_OTA_FILE_NAME stream into
 * the backup bank, and net_fclose verifies it, burns the new boot info and
 * reboots.  The running bank stays bootable, so a failed transfer or a power
 * loss during the swap cannot brick the device.
 */

/*
 * Ceiling reported to the cloud.  The dual-bank layout gives the update
 * bank [0x1FC000, 0x3A0000) once the TuyaOpen reserved window is carved out
 * at 0x3A0000, i.e. ~1.66 MiB of OTA capacity; the current package is
 * ~1.05 MiB.  The vendor library re-checks the true bank budget through
 * dual_bank_update_allow_check() when the stream starts.
 */
#define TKL_OTA_MAX_IMAGE_SIZE 0x001A4000U

static void *s_update_fd = NULL;
static uint32_t s_written = 0;

static void ota_abort(void)
{
    if (s_update_fd != NULL) {
        /* is_socket_err=1 keeps net_fclose from burning the boot info. */
        net_fclose(s_update_fd, 1);
        s_update_fd = NULL;
    }
    s_written = 0;
}

OPERATE_RET tkl_ota_get_ability(uint32_t *image_size, TUYA_OTA_TYPE_E *type)
{
    if (NULL == image_size || NULL == type) {
        return OPRT_INVALID_PARM;
    }
    *image_size = TKL_OTA_MAX_IMAGE_SIZE;
    *type = TUYA_OTA_FULL;
    return OPRT_OK;
}

OPERATE_RET tkl_ota_start_notify(uint32_t image_size, TUYA_OTA_TYPE_E type, TUYA_OTA_PATH_E path)
{
    (void)path;
    if (TUYA_OTA_FULL != type) {
        return OPRT_NOT_SUPPORTED;
    }
    if (0 == image_size || image_size > TKL_OTA_MAX_IMAGE_SIZE) {
        printf("[JIELI][OTA] reject image size %u\n", image_size);
        return OPRT_INVALID_PARM;
    }
    /* The HTTP download re-notifies the size on every reconnect; while the
     * stream is open the offsets keep advancing, so re-opening would drop
     * the already staged bytes. */
    if (s_update_fd != NULL) {
        return OPRT_OK;
    }
    s_update_fd = net_fopen(CONFIG_UPGRADE_OTA_FILE_NAME, "w");
    if (NULL == s_update_fd) {
        printf("[JIELI][OTA] net_fopen failed\n");
        return OPRT_COM_ERROR;
    }
    s_written = 0;
    printf("[JIELI][OTA] start %u bytes\n", image_size);
    return OPRT_OK;
}

OPERATE_RET tkl_ota_data_process(TUYA_OTA_DATA_T *pack, uint32_t *remain_len)
{
    int written;
    if (NULL == pack || NULL == pack->data || NULL == remain_len) {
        return OPRT_INVALID_PARM;
    }
    if (NULL == s_update_fd) {
        return OPRT_COM_ERROR;
    }
    /* The vendor staging path is append-only: it cannot seek when TuyaOpen
     * resumes a broken download at a new offset.  Abort instead of
     * corrupting the bank; the cloud restarts the transfer from zero. */
    if (pack->offset != s_written) {
        printf("[JIELI][OTA] offset %u != staged %u\n", pack->offset, s_written);
        ota_abort();
        return OPRT_COM_ERROR;
    }
    written = net_fwrite(s_update_fd, (unsigned char *)pack->data, (int)pack->len, 0);
    if (written < 0) {
        printf("[JIELI][OTA] net_fwrite error %d\n", written);
        ota_abort();
        return OPRT_COM_ERROR;
    }
    s_written += (uint32_t)written;
    *remain_len = pack->len - (uint32_t)written;
    return OPRT_OK;
}

OPERATE_RET tkl_ota_end_notify(BOOL_T reset)
{
    if (NULL == s_update_fd) {
        return OPRT_COM_ERROR;
    }
    if (reset) {
        printf("[JIELI][OTA] download complete (%u bytes), switching bank\n", s_written);
        /* net_fclose verifies the staged bank, burns the new boot info and
         * schedules the system reset two seconds later. */
        net_fclose(s_update_fd, 0);
    } else {
        ota_abort();
    }
    s_update_fd = NULL;
    s_written = 0;
    return OPRT_OK;
}

OPERATE_RET tkl_ota_get_old_firmware_info(TUYA_OTA_FIRMWARE_INFO_T **info)
{
    /* Breakpoint-resume bookkeeping is only used by BLE sub-devices. */
    if (info) {
        *info = NULL;
    }
    return OPRT_NOT_SUPPORTED;
}
