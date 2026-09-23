#ifndef BOARD_CONFIG_H
#define BOARD_CONFIG_H

//芯片型号
// #define CONFIG_BOARD_AC7925A
// #define CONFIG_BOARD_AC7925B
#define CONFIG_BOARD_AC7926A
// #define CONFIG_BOARD_AC7922C

//板子型号
#define CONFIG_BOARD_DEVELOP      // 开发板

//芯片型号sdram和flash配置文件
#include "chip_cfg.h"

//不同板子外设配置文件，如有新的板子，在这里同理添加
#ifdef CONFIG_BOARD_DEVELOP
#ifdef CONFIG_BOARD_AC7925A
#include "board_develop_AC7925A.h"
#endif
#ifdef CONFIG_BOARD_AC7925B
#include "board_develop_AC7925B.h"
#endif
#ifdef CONFIG_BOARD_AC7926A
#include "board_develop_AC7926A.h"
#endif
#ifdef CONFIG_BOARD_AC7922C
#include "board_develop_AC7922C.h"
#endif
#endif

#ifdef CONFIG_NO_SDRAM_ENABLE
#undef  __SDRAM_SIZE__
#define __SDRAM_SIZE__    0
#else
#if (__SDRAM_SIZE__ == 0)
#ifndef CONFIG_NO_SDRAM_ENABLE
#define CONFIG_NO_SDRAM_ENABLE
#endif
#endif
#endif

#endif
