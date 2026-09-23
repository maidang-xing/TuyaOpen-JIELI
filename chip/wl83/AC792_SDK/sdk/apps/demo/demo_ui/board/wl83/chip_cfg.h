#ifndef CONFIG_CHIP_CFG_H
#define CONFIG_CHIP_CFG_H

#if defined CONFIG_BOARD_AC7926A  // 16M-ddr，外置flash
#define __FLASH_SIZE__    (8 * 1024 * 1024)
#define __SDRAM_SIZE__    (16 * 1024 * 1024)
#define __EXTERN_FLASH_SIZE_MB__  32
#define __EXTERN_FLASH_SIZE__     (__EXTERN_FLASH_SIZE_MB__ * 1024 * 1024)
#endif

#endif
