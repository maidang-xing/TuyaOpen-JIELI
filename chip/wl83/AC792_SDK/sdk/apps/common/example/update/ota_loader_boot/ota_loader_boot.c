//该实例用于客户不通过sd方式启动ota loader进行单备份升级

//  1.SD卡ota loader正常启动流程
//  -----------    --------------
//  |sd卡升级 |    |sdk app读取  |
//  |otaloader|--->|ufw中ota.bin |
//  |启动流程 |    |数据到flash中|
//  -----------    --------------
//                        |
//                        V
//                 ---------------        -----------
//                 |校验ota.bin   |--否-->|升级失败 |
//                 |数据是否正确? |       |  退出   |
//                 ---------------        -----------
//                        |
//                        是
//                        |
//                        V
//                 ---------------
//                 |system_reset |
//                 |             |
//                 ---------------
//                        |
//                        V
//                 -----------------         ----------
//                 |uboot 检查      |        |退出升级 |
//                 |UPDATA_PARM参数 | --否-->| ,启动APP|
//                 |判断是否需要升级|        |         |
//                 -----------------         ----------
//                        |
//                        是
//                        |
//                        V
//                 --------------------
//                 |根据UPDATA_PARM   |
//                 |参数启动ota loader|
//                 |进行升级          |
//                 --------------------


//  2.当ota升级失败或升级过程中断电启动流程

//                  --------------------
//   -------------> |ota loader升级失败 |
//   |              |或意外断电设备重启 |
//   |              --------------------
//   |                       |
//   |                       |
//   |                       V
//   |              ---------------------          ----------
//   |              |uboot检查ram中     |          |退出升级|
//   |      ------> |UPDATA_PARM数据判断| --否---->|启动 APP|
//   |      |       |是否需要升级       |          |        |
//   |      |       ---------------------          ----------
//   |      |             |                            |
//   |      |             是                           |
//   |      |             |                            |
//   |      |             V                            V           ---------------------------------------
//   |      |      --------------------           ----------       |当uboot启动app失败时，会去指定的ram   |
//   |      |      |根据UPDATA_PARM   |           |启动app |       |地址读取UPDATA_PARM启动参数启动ota    |
//   |      |      |参数启动ota loader|           | 成功？ |--否-->|loader再次进行升级。但是如果断电      |
//   |      |      |进行升级          |           |        |       |重启ram中的UPDATA_PARM数据丢失，uboot |
//   |      |      --------------------           ----------       |会从flash末尾开始往低地址以4K为单位   |
//   |      |                                         |            |搜索是否有保存的UPDATA_PARM？         |
//   |      |                                         是           ----------------------------------------
//   |      |                                         |                                 |
//   |      |                                         V                                 |
//   |      |                                    ---------                              V
//   |      |                                    |运行APP|                        --------------
//   |      |                                    ---------                        |flash 中存在|
//   |      |--------------------------------------------------------------是---- |UPDATA_PARM?|
//   |                                                                            --------------
//   |                                                                                  |
//   |                                                                                 否
//   -----------------------------------------------------------------------------------|


//3.如果不想通过读取ufw升级文件的方式加载ota.bin，则需要将ota.bin放到flash中，
//然后告诉uboot相关启动参数即可。这个提供一个参考示例

//该例子通过预留区来保存ota.bin,需要根据自身需求灵活使用
#include "system/includes.h"
#include "fs/fs.h"
#include "asm/crc16.h"
#include "update.h"
#include "asm/sfc_norflash_api.h"

#define FLASH_SECTOR_SIZE (4096L)

typedef struct stJL_FILE_HEAD {
    u16 u16Crc;
    u16 u16DataCrc;
    u32 u32Address;
    u32 u32Length;
    u8 u8Attribute;
    u8 u8Res;
    u16 u16Index;
    char szFileName[16];
} JL_FILE_HEAD;

typedef struct _loader_info {
    UPDATA_PARM update_parm_info;
    JL_FILE_HEAD loader_head_info;
} loader_info;

void store_loader_info(loader_info *info, u32 loader_addr, u32 loader_len, u32 info_addr)
{
    //1
    info->loader_head_info.u16DataCrc = 0xffff;
    info->loader_head_info.u32Address = loader_addr;
    //info->loader_head_info.u32Length = loader_len + sizeof(JL_FILE_HEAD);
    info->loader_head_info.u32Length = loader_len;
    info->loader_head_info.u8Attribute = 0;
    info->loader_head_info.u8Res = 0xff;
    info->loader_head_info.u16Index = 0xffff;
    memcpy(info->loader_head_info.szFileName, "LOADER.BIN", 16);
    info->loader_head_info.u16Crc = CRC16((u8 *)&info->loader_head_info + 2, sizeof(JL_FILE_HEAD) - 2);

    //2
    UPDATA_PARM *p = &info->update_parm_info;
    p->parm_type = (u16)USB_HID_UPDATA;
    p->parm_result = (u16)UPDATA_READY;
    p->magic = UPDATE_PARAM_MAGIC;
    //该地址保存loader_head_info 信息的flash地址
    p->ota_addr = info_addr + FLASH_SECTOR_SIZE - 0x100 + sizeof(UPDATA_PARM); //LOADER.BIN 的头部信息地址

    //计算crc值
    p->parm_crc = CRC16(((u8 *)p) + 2, sizeof(UPDATA_PARM) - 2);


    //保存loader info信息到flash中,用于意外断电后重新启动loader。当uboot启动app 失败后，uboot会搜索每个flash sector,搜索到启动参数就会加载
    //ota loader厂商升级
    //启动信息写入位置, 有一定要求，需要将UPDATA_PARM放到(SECTOR_ADR_END - 0x100)位置
    /*
    #------------------------------|<---SECTOR_ADR_START，该地址需要4K对齐;如设置的BOOTINFO_ADR CONFIG_BOOTINFO_ADR
    #                              |
    #          (Reserved)          |
    #                              |
    #------------------------------|<----SECTOR_ADR_END - 0x100, UPDATA_PARM信息必须位于该地址
    #          (256 Bytes)         |
    #------------------------------+<----SECTOR_ADR_END
    */
    u32 sector_adr_start = info_addr;
    u32  info_store_addr = info_addr + FLASH_SECTOR_SIZE - 0x100;

    norflash_ioctl(NULL, IOCTL_ERASE_SECTOR, info_addr);
    norflash_write(NULL, info, sizeof(loader_info), info_store_addr);

#if 1
    //保存UPDATA_PARM 到ram,system reset后会根据该信息判断是否需要升级
    update_param_ram_set((u8 *)p, sizeof(UPDATA_PARM));
    system_reset();
#endif
}

u32 nor_read(u8 *buf, u32 addr, u32 len)
{
    norflash_read(NULL, buf, len, addr);
}

/*
#
# 在isd_config_rule.c ，增加扩展预留区用于保存ota loader数据
# LOADER_FILE=ota.bin;
# LOADER_ADR=CONFIG_LOADER_ADR;
# LOADER_LEN=CONFIG_LOADER_LEN;
#LOADER_OPT=1;
#
*/
#define LOADER_PATH "mnt/sdfile/EXT_RESERVED/LOADER"

/*
#
# 在isd_config_rule.c ，增加扩展预留区用于保存boot info数据
#BOOTINFO_ADR=CONFIG_BOOTINFO_ADR;
#BOOTINFO_LEN=CONFIG_BOOTINFO_LEN;
#BOOTINFO_OPT=1;
#
*/

//在app_config.h预留区UI和AUDIO资源配置 后加入区域配置
//#ifndef CONFIG_UI_PACKRES_LEN
//#define CONFIG_UI_PACKRES_LEN 0
//#endif
//#ifndef CONFIG_AUDIO_PACKRES_LEN
//#define CONFIG_AUDIO_PACKRES_LEN 0
//#endif
//#define CONFIG_LOADER_LEN 0x94000
//#define CONFIG_LOADER_ADR ((__FLASH_SIZE__) - (CONFIG_UI_PACKRES_LEN) - 0x1000 - CONFIG_AUDIO_PACKRES_LEN - CONFIG_LOADER_LEN)
//#define CONFIG_BOOTINFO_LEN 0x1000
//#define CONFIG_BOOTINFO_ADR (CONFIG_LOADER_ADR - CONFIG_BOOTINFO_LEN)

#define LOASER_INFO_PATH "mnt/sdfile/EXT_RESERVED/BOOTINFO"

#define HEADE_NUM_MAX 16
static int find_entry_addr_and_target_loader(const u8 *loader_name, const u32 loader_entry_addr, JL_FILE_HEAD *target_head, u32 *entry_addr)
{
    int i;
    u8 *tmp_buf = (u8 *)malloc(sizeof(JL_FILE_HEAD) *  HEADE_NUM_MAX);
    if (!tmp_buf) {
        return -1;
    }

    norflash_origin_read(tmp_buf, loader_entry_addr, sizeof(JL_FILE_HEAD) *  HEADE_NUM_MAX);

    JL_FILE_HEAD *phead = (JL_FILE_HEAD *)tmp_buf;
    *entry_addr = 0xdeadbeef;
    for (i = 0; i < HEADE_NUM_MAX; i++) {
        if (jl_file_head_valid_check(phead)) {
            phead++;
            continue;
        }

        if (*entry_addr == 0xdeadbeef) {
            *entry_addr = i * 0x20;
        }

        printf("find loader name:%s, size: 0x%x, addr: 0x%x\n",  \
               phead->szFileName, phead->u32Length, phead->u32Address);

        if (0 == strcmp(phead->szFileName, loader_name)) {
            memcpy(target_head, phead, sizeof(JL_FILE_HEAD));
            free(tmp_buf);
            return 0;
        }

        phead++;
    }

    free(tmp_buf);
    return -1;
}

void loader_boot_main(void *priv)
{
    //打开保存ota loader数据的路径
    FILE *fp = fopen(LOADER_PATH, "r");
    if (fp == NULL) {
        puts("fopen loader path err\r\n");
        return;
    }

    //获取ota loader所在flash的物理地址
    u32 ota_loader_addr;
    struct vfs_attr file_attr;
    fget_attrs(fp, &file_attr);
    ota_loader_addr = sdfile_cpu_addr2flash_addr(file_attr.sclust);
    fclose(fp);
    printf("loader data addr 0x%x, size = 0x%x \r\n", ota_loader_addr, file_attr.fsize);

    JL_FILE_HEAD loader_entry;
    u32 entry_addr_offset;
    if (find_entry_addr_and_target_loader("usb_hid_ota.bin", ota_loader_addr, &loader_entry, &entry_addr_offset)) {
        printf("not found target loader file\n");
        return;
    }

    printf("entry_addr_offset: 0x%x\n", entry_addr_offset);

    //检查ota loader头部
    int ret = jl_file_head_valid_check(&loader_entry);
    if (ret) {
        printf("check loader entry head err\n");
        return;
    }
    printf("loader name:%s, size: 0x%x, crc: 0x%x, addr: 0x%x\n",  \
           loader_entry.szFileName, loader_entry.u32Length, loader_entry.u16DataCrc, loader_entry.u32Address);

    u32 loader_file_addr = loader_entry.u32Address + entry_addr_offset + ota_loader_addr;
    printf("loader_file_addr: 0x%x\n", loader_file_addr);

    //校验ota loader数据
    int file_data_verify_by_crc(u32 addr, u32 len, u16 file_crc, u32(*read_func)(u8 * buf, u32 addr, u32len));
    if (file_data_verify_by_crc(loader_file_addr, loader_entry.u32Length, loader_entry.u16DataCrc, nor_read)) {
        printf("loader data verify err\n");
        return ;
    }

    //打开保存ota loader info数据的路径
    fp = fopen(LOASER_INFO_PATH, "r");
    if (fp == NULL) {
        puts("fopen loader info path err\r\n");
        return;
    }

    //获取ota loader info所在flash的物理地址
    u32 loader_info_addr;
    fget_attrs(fp, &file_attr);
    loader_info_addr = sdfile_cpu_addr2flash_addr(file_attr.sclust);
    fclose(fp);
    printf("loader info addr 0x%x, size = 0x%x \r\n", loader_info_addr, file_attr.fsize);

    //保存boot info信息
    loader_info loader_info_t;
    store_loader_info(&loader_info_t, loader_file_addr - 32, loader_entry.u32Length + 32, loader_info_addr);
}

void loader_boot_task(void)
{
    if (thread_fork("loader_boot_main", 10, 512, 0, NULL, loader_boot_main, NULL) != OS_NO_ERR) {
        printf("thread fork fail\n");
    }
}
