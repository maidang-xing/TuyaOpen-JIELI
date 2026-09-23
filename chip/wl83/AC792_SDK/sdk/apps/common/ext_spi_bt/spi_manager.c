#include "system/includes.h"
#include "app_config.h"
#include "spi_manager.h"

#if INSTR_DEV_SPI_ENABLE

#define LOG_TAG         "[SPI_MANAGER]"
#define LOG_ERROR_ENABLE
#define LOG_DEBUG_ENABLE
#define LOG_INFO_ENABLE
#define LOG_DUMP_ENABL
#define LOG_ERROR_ENABLE
#include "debug.h"

static u8 real_sn = 0;

/**
 * @brief 获取下一个序列号
 * @return 下一个序列号值
 */
static inline u8 get_next_sn(void)
{
    u8 sn = real_sn++;

    if (real_sn > 255) {
        real_sn = 0;
    }

    return sn;
}

/**
 * @description: spi 发送cmd接口
 * @param {u8} cmd：命令号
 * @param {bt_cmd_type_t} rsp_flag：响应类型
 * @param {u8 *} data：有效数据
 * @param {u32} len : 有效数据长度
 * @return {void}
 */
static void spi_send_cmd_deal(u8 cmd, u8 sn, bt_cmd_type_t rsp_flag, u8 *data, u32 len)
{
    printf("spi_send_cmd_deal---cmd:%d\n", cmd);

    if (!data) {
        log_error("data is null\n");
        return;
    }

#if 0
    instr_send_cmd(cmd, sn, rsp_flag, data, len);
#else
    /***由于SPI通信驱动层加了通过SN判断是否为驱动层重传，
    SN相同情况下，认为是重传包；因此每次发新命令包之前要SN++***/
    instr_send_cmd(cmd, get_next_sn(), rsp_flag, data, len);
#endif
}

/**
 * @description: spi 响应cmd接口
 * @param {u8} cmd：命令号
 * @param {bt_cmd_type_t} rsp_flag：响应类型
 * @param {u8 } cmd_stats：回复命令状态
 * @param {u8 *} data：有效数据
 * @param {u32} len : 有效数据长度
 * @return {void}
 */
static void spi_response_cmd_deal(u8 cmd, u8 sn, bt_cmd_type_t rsp_flag, uint8_t cmd_stats, u8 *data, u32 len)
{
    printf("spi_response_cmd_deal");

    if (!data) {
        log_error("data is null\n");
        return;
    }

#if 0
    instr_rsp_send_cmd(cmd, sn, rsp_flag, cmd_stats, data, len);
#else
    /***由于SPI通信驱动层加了通过SN判断是否为驱动层重传，
    SN相同情况下，认为是重传包；因此每次发新命令包之前要SN++***/
    instr_rsp_send_cmd(cmd, get_next_sn(), rsp_flag, cmd_stats, data, len);
#endif
}

/**
 * @description: spi 发送data cmd接口
 * @param {u8} cmd：命令号
 * @param {u8} sn：sn码
 * @param {bt_cmd_type_t} rsp_flag：响应类型
 * @param {u8} respon_code：响应的命令
*  @param {u8} data：有效数据
 * @param {u32} len : 有效数据长度
 * @return {void}
 */
static void spi_send_data_deal(u8 cmd, uint8_t sn, bt_data_type_t rsp_flag, uint8_t respon_code, uint8_t *buffer, uint32_t buffer_len)
{
    printf("spi_send_data_deal\n");
}

/**
 * @description: 响应data包接口
 * @param {void}
 * @return {void}
 */
static void spi_response_data_deal(u8 cmd, uint8_t sn, bt_data_type_t rsp_flag, uint8_t cmd_stats, uint8_t rsp_opcode, uint8_t *buffer, uint32_t buffer_len)
{
    printf("spi_response_data_deal\n");
}

/**
 * @description: SPI初始化接口
 * @param {void}
 * @return {void}
 */
static int spi_dev_init(void)
{
    printf("spi dev init\n");
    int ret = 0;

    //ret = spi_driver_init();
    ret = spi_driver_init();

    return ret;
}

custom_spi_api_t custom_spi_api = {
    .custom_spi_dev_init               = spi_dev_init,            //SPI初始化
    .custom_spi_send_cmd_handle        = spi_send_cmd_deal,       //发送命令包处理
    .custom_spi_response_cmd_handle    = spi_response_cmd_deal,   //回复从机命令处理
    .custom_spi_send_data_handle       = spi_send_data_deal,      //发送数据包处理（未启用）
    .custom_spi_response_data_handle   = spi_response_data_deal,  //回复从机数据包处理（未启用）
};

static int instr_spi_test(void)
{
    log_info("instr_spi_test\n");

    int ret = 0;
    if (INTSR_TASK_SPI_API) {
        ret = INTSR_TASK_SPI_API->custom_spi_dev_init();
        if (ret) {
            return -1;
        }
    }

    spi_parse_init();  //SPI解析任务初始化

#if TCFG_SPI_ALBUM_PARSER_ENBALE
    bt_album_recv_init();//专辑解析任务初始化
#endif

    return 0;
}
late_initcall(instr_spi_test);
#endif


