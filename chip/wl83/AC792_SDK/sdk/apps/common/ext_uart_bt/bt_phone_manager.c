/**
 * @file bt_phone_manager.c
 * @brief 蓝牙电话管理模块
 * @author
 * @version 1.0
 * @date
 */

#include "system/includes.h"
#include "app_config.h"
#include "uart_manager.h"

#define LOG_TAG         "[BT_PHONE_MANAGER]"
#define LOG_ERROR_ENABLE
#define LOG_DEBUG_ENABLE
#define LOG_INFO_ENABLE
#define LOG_DUMP_ENABLE
#include "debug.h"

#if INSTR_DEV_UART_ENABLE

/**
 * @brief 电话本数据结构体（小端序，序列号占1字节）
 */
#pragma pack(1)
typedef struct {
    u8 sequence_number;    /**< 序列号 */
    u8 type;              /**< 类型 */
    u8 *name;             /**< 姓名指针 */
    u8 *number;           /**< 号码指针 */
    u8 *date;             /**< 日期指针 */
} PhonebookData;
#pragma pack()

#define FIELD_SEPARATOR 0x1F  /**< Unit Separator ASCII字符，字段分隔符 */

/**
 * @brief 获取蓝牙电话本信息
 *
 * @details 发送获取PBAP电话本列表的请求命令
 */
void bt_phone_get_pbap_info(void)
{
    log_debug("%s %d\n", __func__, __LINE__);

    u8 data = PROTOCOL_TAG_BT_PBAP_LIST_READ;

    if (INTSR_TASK_UART_API) {
        INTSR_TASK_UART_API->custom_uart_send_cmd_handle(OP_CODE_BT_PABP, 1, RSP_CMD_TYPE_REQUEST, &data, 1);
    }
}

/**
 * @brief 电话控制：接听、拒接
 *
 * @param deal 处理方式
 */
void bt_phone_call_conctrl(u8 deal)
{
    log_debug("%s %d\n", __func__, __LINE__);

    u8 data[2] = {0};

    data[0] = PROTOCOL_TAG_HFP_CALL_CTRL;
    data[1] = deal;

    if (INTSR_TASK_UART_API) {
        INTSR_TASK_UART_API->custom_uart_send_cmd_handle(OP_CODE_HFP_CALL_CONCTRL, 1, RSP_CMD_TYPE_REQUEST, &data, sizeof(data));
    }
}

/**
 * @brief 三方通话控制
 *
 * @param hangup 挂断控制参数
 */
void bt_phone_3WayCall_conctrl(uint8_t hangup)
{
    log_debug("%s %d hangup : %d\n", __func__, __LINE__, hangup);

    u8 data[2] = {0};

    data[0] = PROTOCOL_TAG_HFP_SECOND_CALL_CTRL;
    data[1] = hangup;

    if (INTSR_TASK_UART_API) {
        INTSR_TASK_UART_API->custom_uart_send_cmd_handle(OP_CODE_HFP_CALL_CONCTRL, 1, RSP_CMD_TYPE_REQUEST, &data, sizeof(data));
    }
}

/**
 * @brief HFP通话相关命令回复从机
 *
 * @param cmd_stats 命令状态
 * @param data 数据指针
 * @param len 数据长度
 */
void bt_phone_hfp_rsp_slave(uint8_t cmd_stats, u8 *data, u32 len)
{
    log_debug("%s %d\n", __func__, __LINE__);

    if (INTSR_TASK_UART_API) {
        INTSR_TASK_UART_API->custom_uart_response_cmd_handle(OP_CODE_HFP_CALL_CONCTRL, 1, BT_CMD_TYPE_REQUEST_WITH_RSP, cmd_stats, data, len);
    }
}

/**
 * @brief 解析电话本通话记录原始数据
 *
 * @param data 原始数据指针
 * @param data_len 数据长度
 * @param result 解析结果结构体指针
 * @return int 0成功，负数表示错误码
 */
static int parse_phonebook_data(const u8 *data, u16 data_len, PhonebookData *result)
{
    /* 参数检查 */
    if (data == NULL || result == NULL || data_len < 5) {
        return -1; // 无效参数或数据长度不足
    }

    u16 pos = 0;

    /* 解析序列号 (1字节) */
    result->sequence_number = data[pos++];

    /* 解析类型 (1字节) */
    result->type = data[pos++];

    /* 检查第一个分隔符 */
    if (pos >= data_len || data[pos] != FIELD_SEPARATOR) {
        return -2; // 分隔符错误
    }
    pos++;

    /* 解析姓名 (直到下一个分隔符或数据结束) */
    u8 *field_start = (u8 *)&data[pos];
    while (pos < data_len && data[pos] != FIELD_SEPARATOR) {
        pos++;
    }

    if (pos >= data_len) {
        return -3; // 数据不完整
    }

    u16 name_len = pos - (field_start - data);
    if (name_len > 0) {
        result->name = (u8 *)malloc(name_len + 1);
        memcpy(result->name, field_start, name_len);
        result->name[name_len] = '\0'; // 添加字符串结束符
    } else {
        result->name = NULL;
    }
    pos++; // 跳过分隔符

    /* 解析号码 (直到下一个分隔符或数据结束) */
    field_start = (u8 *)&data[pos];
    while (pos < data_len && data[pos] != FIELD_SEPARATOR) {
        pos++;
    }
    if (pos >= data_len) {
        /* 清理已分配的内存 */
        if (result->name) {
            free(result->name);
        }
        return -4; // 数据不完整
    }

    u16 number_len = pos - (field_start - data);
    if (number_len > 0) {
        result->number = (u8 *)malloc(number_len + 1);
        memcpy(result->number, field_start, number_len);
        result->number[number_len] = '\0';
    } else {
        result->number = NULL;
    }
    pos++; // 跳过分隔符

    /* 解析日期 (直到数据结束) */
    field_start = (u8 *)&data[pos];
    u16 date_len = data_len - pos;
    if (date_len > 0) {
        result->date = (u8 *)malloc(date_len + 1);
        memcpy(result->date, field_start, date_len);
        result->date[date_len] = '\0';
    } else {
        result->date = NULL;
    }

    return 0; // 成功
}

/**
 * @brief 释放电话本数据内存
 *
 * @param data 电话本数据结构体指针
 */
static void free_phonebook_data(PhonebookData *data)
{
    if (data->name) {
        free(data->name);
    }
    if (data->number) {
        free(data->number);
    }
    if (data->date) {
        free(data->date);
    }

    data->name = NULL;
    data->number = NULL;
    data->date = NULL;
}

/**
 * @brief 打印电话本数据
 *
 * @param data 电话本数据结构体指针
 */
static void print_phonebook_data(PhonebookData *data)
{
    if (data == NULL) {
        log_debug("结构体指针为空\n");
        return;
    }

    printf("sequence_number: %d\n", data->sequence_number);  // 十进制打印
    printf("type: %d\n", data->type);                      // 十进制打印

    if (data->name) {
        printf("name: %s\n", data->name);   // 字符串打印
    } else {
        log_error("data->name is null\n");
    }

    if (data->number) {
        printf("number: %s\n", data->number);
    } else {
        log_error("data->number is null\n");
    }

    if (data->date) {
        printf("date: %s\n", data->date);
    } else {
        log_error("data->date is null\n");
    }
}

/**
 * @brief 蓝牙电话数据包解析处理
 *
 * @param data 数据指针
 * @param data_len 数据长度
 */
void bt_phone_pack_parse_handle(const u8 *data, u16 data_len)
{
    PhonebookData *pbap_result = (PhonebookData *)malloc(sizeof(PhonebookData));
    if (!pbap_result) {
        printf("malloc pabp result fail.\n");
        return;
    }

    int ret = parse_phonebook_data(data, data_len, pbap_result);
    if (ret) {
        return;
    }

    print_phonebook_data(pbap_result);

    free_phonebook_data(pbap_result);
    free(pbap_result);
}

#endif


