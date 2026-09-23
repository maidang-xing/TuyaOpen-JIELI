#include "system/includes.h"
#include "fs/fs.h"
#include "asm/sfc_norflash_api.h"
#include "lfs.h"

// variables used by the filesystem
static lfs_t lfs;
static OS_MUTEX lfs_mutex;

static int lfs_flash_block_read(const struct lfs_config *c, lfs_block_t block,
                                lfs_off_t off, void *buffer, lfs_size_t size)
{
    u32 addr = (u32)c->context + block * c->block_size + off;
    u32 end = addr + size;
    u32 lfs_end = (u32)c->context + c->block_count * c->block_size;

    if (end > lfs_end) {
        printf("lfs_flash_block_read out of range! addr=0x%x, size=%d\r\n", addr, size);
        return -1;
    }
    // printf("read context=0x%x, block=%d, off=%d, size=%d, lfs_flash_block_read addr=0x%x\r\n", c->context, block, off, size, (u32)c->context + block * c->block_size + off);
    norflash_read(NULL, buffer, size, addr);
    return 0;
}

static int lfs_flash_block_prog(const struct lfs_config *c, lfs_block_t block,
                                lfs_off_t off, const void *buffer, lfs_size_t size)
{
    u32 addr = (u32)c->context + block * c->block_size + off;
    u32 end = addr + size;
    u32 lfs_end = (u32)c->context + c->block_count * c->block_size;

    if (end > lfs_end) {
        printf("lfs_flash_block_prog out of range! addr=0x%x, size=%d\r\n", addr, size);
        return -1;
    }
    // printf("write context=0x%x, block=%d, off=%d, size=%d, lfs_flash_block_prog addr=0x%x\r\n", c->context, block, off, size, (u32)c->context + block * c->block_size + off);
    norflash_write(NULL, (void *)buffer, size, addr);

    return 0;
}

static int lfs_flash_block_erase(const struct lfs_config *c, lfs_block_t block)
{
    u32 addr = (u32)c->context + block * c->block_size;
    u32 end = addr + c->block_size;
    u32 lfs_end = (u32)c->context + c->block_count * c->block_size;
    if (end > lfs_end) {
        printf("lfs_flash_block_erase out of range! addr=0x%x, size=%d\r\n", addr, c->block_size);
        return -1;
    }
    // printf("context=0x%x, erase addr=0x%x\r\n", c->context, (u32)c->context + block * c->block_size);
    norflash_ioctl(NULL, IOCTL_ERASE_SECTOR, addr);
    return 0;
}
static int lfs_flash_block_sync(const struct lfs_config *c)
{
    return 0;
}

#ifdef  LFS_THREADSAFE
static void lfs_lock(const struct lfs_config *c)
{
    os_mutex_pend(&lfs_mutex, 0);
}
static void lfs_unlock(const struct lfs_config *c)
{
    os_mutex_post(&lfs_mutex);

}
#endif


// configuration of the filesystem is provided by this struct

static struct lfs_config cfg = {
    // block device operations
    .read  = lfs_flash_block_read,
    .prog  = lfs_flash_block_prog,
    .erase = lfs_flash_block_erase,
    .sync  = lfs_flash_block_sync,

#ifdef  LFS_THREADSAFE
    .lock = lfs_lock,
    .unlock = lfs_unlock,
#endif

    // block device configuration
    .read_size = 4 * 1024,
    .prog_size = 4 * 1024,
    .block_size = 4 * 1024,
    .block_count = 1024 * 1024,
    .cache_size = 4 * 1024,
    .block_cycles = 500,
};

lfs_t *lfs_dev_mount(void)
{
    printf("lfs_dev_mount start...\n");
    u32 raw_lfs_addr, lfs_space;

    FILE *profile_fp = fopen("mnt/sdfile/EXT_RESERVED/extflash", "r");
    if (!profile_fp) {
        puts("Failed to open extflash config!\r\n");
        return NULL;
    }

    struct vfs_attr file_attr;
    fget_attrs(profile_fp, &file_attr);
    raw_lfs_addr = sdfile_cpu_addr2flash_addr(file_attr.sclust);
    lfs_space = file_attr.fsize;
    fclose(profile_fp);

    printf("Raw LFS region: 0x%08x, size=0x%x (%u KB)\n",
           raw_lfs_addr, lfs_space, lfs_space / 1024);

    // === Step 1: 对齐起始地址 ===
    u32 block_size = cfg.block_size;
    u32 aligned_start = (raw_lfs_addr + block_size - 1) & ~(block_size - 1);
    printf("Aligned LFS start address: 0x%08x\n", aligned_start);
    // === Step 2: 检查是否还有足够空间 ===
    if (aligned_start - raw_lfs_addr >= lfs_space) {
        printf("ERROR: Not enough space after alignment!\n");
        return NULL;
    }

    u32 usable_space = lfs_space - (aligned_start - raw_lfs_addr);
    u32 block_count = usable_space / block_size;

    if (block_count == 0) {
        printf("ERROR: No complete block available after alignment!\n");
        return NULL;
    }

    // === Step 3: 配置 LFS ===
    cfg.context = (void *)aligned_start;
    cfg.block_count = block_count;
    cfg.lookahead_size = ((block_count + 63) / 64) * 8; // 保证 8-byte 对齐

    printf("Aligned LFS: start=0x%08x, blocks=%u, total=%u KB\n",
           aligned_start, block_count, (block_count * block_size) / 1024);

    os_mutex_create(&lfs_mutex);

    // === Mount or format ===
    int err = lfs_mount(&lfs, &cfg);
    if (err) {
        printf("Mount failed (%d), formatting...\n", err);
        if (lfs_format(&lfs, &cfg) || lfs_mount(&lfs, &cfg)) {
            printf("Format or remount failed!\n");
            return NULL;
        }
    }

    return &lfs;
}
