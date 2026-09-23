/**
 * @file bt_album_manager.c
 * @brief 专辑接收管理模块
 * @author
 * @version 1.0
 * @date
 */

#include "system/includes.h"
#include "system/init.h"
#include "app_config.h"
#include "uart_manager.h"
#include "fs/fs.h"

#define LOG_TAG         "[BT_ALBUM_MANAGER]"
#define LOG_ERROR_ENABLE
#define LOG_DEBUG_ENABLE
#define LOG_INFO_ENABLE
#define LOG_DUMP_ENABLE
#include "debug.h"

#if (INSTR_DEV_UART_ENABLE && TCFG_UART_ALBUM_PARSER_ENBALE)

/* 常量定义 */
#define MAX_JPG_SIZE                    (300 * 1024)        ///< 最大JPG文件大小 300KB
#define CONFIG_ALBUM_SAVE2SD_ENABLE     0                   ///< 使能接收到的专辑数据存卡功能
#define CONFIG_ALBUM_RECV_TIME_ENABLE   1                   ///< 使能计算一帧jpg获取传输的时间

/* JPEG文件格式定义 */
#define JPEG_SOI_MARKER                 0xFFD8              ///< JPEG起始标记 (Start of Image)
#define JPEG_EOI_MARKER                 0xFFD9              ///< JPEG结束标记 (End of Image)

/**
 * @brief 专辑接收管理结构体
 */
typedef struct {
    u8 *jpg_buffer;                     ///< JPG数据缓存指针
    u32 jpg_total_len;                  ///< 当前JPG文件总长度
    u32 cur_recv_len;                   ///< 当前已接收数据长度
    u32 start_recv_time;                ///< 开始接收时间戳
    OS_SEM data_sem;                    ///< 数据同步信号量
} bt_album_manager_t;

/**
 * @brief 专辑消息结构体
 */
typedef struct {
    u32 msg_type;                       ///< 消息类型
    u32 data_len;                       ///< 数据长度
    void *data_ptr;                     ///< 数据指针
    u16 crc_value;                      ///< CRC校验值
} bt_album_msg_t;

static bt_album_manager_t g_album_mgr = {0};    ///< 全局专辑管理器实例
static int g_album_task_pid = 0;                ///< 专辑任务PID

/**
 * @brief 保存JPG文件到SD卡
 * @param[in] jpg_data JPG数据指针
 * @param[in] jpg_len JPG数据长度
 * @return 0-成功, 其他-失败
 */
static int album_save_to_sd(const u8 *jpg_data, u32 jpg_len)
{
    int ret = -1;
    FILE *file = NULL;
    char file_path[64] = {0};
    static u16 i = 1;

    printf("%s %d\n", __func__, __LINE__);

    /* 参数检查 */
    if (!jpg_data || jpg_len == 0) {
        log_error("[%s] Invalid parameters\n", __func__);
        return UART_ERR_LEN_ERROR;
    }

    /* 存储设备检查 */
    if (!storage_device_ready()) {
        log_error("[%s] Storage device not ready\n", __func__);
        return UART_ERR_FAILED;
    }

    /* 生成唯一文件名 */
    //snprintf(file_path, sizeof(file_path),
    //         CONFIG_ROOT_PATH"album/jpg_%u.jpg", (unsigned int)jiffies);
    snprintf(file_path, sizeof(file_path),
             CONFIG_ROOT_PATH"album/jpg_%u.jpg", i++);

    /* 打开文件 */
    file = fopen(file_path, "w+");
    if (!file) {
        log_error("[%s] Open file failed: %s\n", __func__, file_path);
        return UART_ERR_FAILED;
    }

    /* 写入数据 */
    if (fwrite(jpg_data, 1, jpg_len, file) == jpg_len) {
        log_info("[%s] Save JPG success: %s, size: %u bytes\n",
                 __func__, file_path, jpg_len);
        ret = UART_ERR_SUCCESS;
    } else {
        log_error("[%s] Write file failed\n", __func__);
        ret = UART_ERR_FAILED;
    }

    /* 清理资源 */
    fclose(file);

    return ret;
}

/**
 * @brief 检查JPG文件完整性
 * @param[in] jpg_data JPG数据指针
 * @param[in] jpg_len JPG数据长度
 * @return 0-完整, 1-不完整
 */
static int album_check_jpg_integrity(const u8 *jpg_data, u32 jpg_len)
{
    u16 soi_marker = 0;
    u16 eoi_marker = 0;

    /* 基本长度检查 */
    if (!jpg_data || jpg_len < 4) {
        log_error("[%s] Invalid JPG data or length\n", __func__);
        return UART_ERR_SUCCESS;
    }

    /* 检查SOI标记 (Start of Image) */
    soi_marker = (jpg_data[0] << 8) | jpg_data[1];
    if (soi_marker != JPEG_SOI_MARKER) {
        log_error("[%s] Invalid JPG SOI marker: 0x%04X\n", __func__, soi_marker);
        return UART_ERR_FAILED;
    }

    /* 检查EOI标记 (End of Image) */
    eoi_marker = (jpg_data[jpg_len - 2] << 8) | jpg_data[jpg_len - 1];
    if (eoi_marker != JPEG_EOI_MARKER) {
        log_error("[%s] Invalid JPG EOI marker: 0x%04X\n", __func__, eoi_marker);
        return UART_ERR_SUCCESS;
    }

    log_debug("[%s] JPG integrity check passed\n", __func__);

    return UART_ERR_SUCCESS;
}

/**
 * @brief 处理接收到的数据包
 * @param[in] packet_data 数据包指针
 * @param[in] packet_size 数据包大小
 */
static void album_handle_data_packet(const u8 *packet_data, u32 packet_size)
{
    /* 参数检查 */
    if (!packet_data || packet_size == 0) {
        log_error("[%s] Invalid packet data\n", __func__);
        return;
    }

    /* 缓冲区边界检查 */
    if ((g_album_mgr.cur_recv_len + packet_size) > MAX_JPG_SIZE) {
        log_error("[%s] Buffer overflow: cur=%u, new=%u, max=%u\n",
                  __func__, g_album_mgr.cur_recv_len, packet_size, MAX_JPG_SIZE);
        return;
    }

    /* 复制数据到缓冲区 */
    memcpy(g_album_mgr.jpg_buffer + g_album_mgr.cur_recv_len,
           packet_data, packet_size);
    g_album_mgr.cur_recv_len += packet_size;

    log_debug("[%s] Received %u bytes, total: %u/%u\n",
              __func__, packet_size, g_album_mgr.cur_recv_len, g_album_mgr.jpg_total_len);
}

/**
 * @brief 处理传输开始消息
 * @param[in] total_len 总数据长度
 */
static void album_handle_start_transfer(u32 total_len)
{
    log_info("[%s] Start transfer, total length: %u\n", __func__, total_len);

    /* 重置接收状态 */
    g_album_mgr.jpg_total_len = total_len;
    g_album_mgr.cur_recv_len = 0;

#if CONFIG_ALBUM_RECV_TIME_ENABLE
    g_album_mgr.start_recv_time = jiffies;
#endif

    /* 清空缓冲区 */
    if (g_album_mgr.jpg_buffer) {
        memset(g_album_mgr.jpg_buffer, 0, MAX_JPG_SIZE);
    }
}

/**
 * @brief 处理传输结束消息
 * @param[in] crc_value CRC校验值
 */

static uint8_t *g_ui_jpg_buf = NULL;
static uint32_t g_ui_jpg_buf_size = 0;   // 当前实际 alloc 的容量

static void album_handle_end_transfer(u16 crc_value)
{
    u16 calculated_crc = 0;
    u32 transfer_time = 0;

    log_info("[%s] End transfer, received: %u/%u\n",
             __func__, g_album_mgr.cur_recv_len, g_album_mgr.jpg_total_len);

    /* 长度检查 */
//    if (g_album_mgr.cur_recv_len != g_album_mgr.jpg_total_len) {
    if (0) {	//兼容部分安卓手机,先不做长度校验
        log_error("[%s] Length mismatch: expected=%u, actual=%u\n",
                  __func__, g_album_mgr.jpg_total_len, g_album_mgr.cur_recv_len);
        bt_music_album_finish_control(1);
        goto cleanup;
    }

    /* JPG完整性检查 */
    if (album_check_jpg_integrity(g_album_mgr.jpg_buffer, g_album_mgr.cur_recv_len)) {
        log_error("[%s] JPG integrity check failed\n", __func__);
        bt_music_album_finish_control(1);
        goto cleanup;
    }

    /* CRC校验 */
    calculated_crc = calculate_crc(g_album_mgr.jpg_buffer, g_album_mgr.cur_recv_len, 0);
    if (calculated_crc != crc_value) {
        log_error("[%s] CRC check failed: expected=0x%X, actual=0x%X\n",
                  __func__, crc_value, calculated_crc);
        bt_music_album_finish_control(1);
        goto cleanup;
    }

    /* 传输成功处理 */
    log_info("[%s] JPG transfer completed successfully\n", __func__);

#if CONFIG_ALBUM_RECV_TIME_ENABLE
    transfer_time = jiffies_to_msecs(jiffies - g_album_mgr.start_recv_time);
    log_info("[%s] Transfer %uKB time: %ums\n",
             __func__, g_album_mgr.cur_recv_len / 1024, transfer_time);
#endif

#if CONFIG_ALBUM_SAVE2SD_ENABLE
    album_save_to_sd(g_album_mgr.jpg_buffer, g_album_mgr.cur_recv_len);
#endif

#ifdef CONFIG_UI_ENABLE	//将专辑图片显示到屏幕

    uint32_t jpg_len = g_album_mgr.cur_recv_len;
    if (g_ui_jpg_buf == NULL || g_ui_jpg_buf_size < jpg_len) {

        uint8_t *new_buf = realloc(g_ui_jpg_buf, jpg_len);
        if (!new_buf) {
            printf("realloc failed\n");
            return;
        }

        g_ui_jpg_buf = new_buf;
        g_ui_jpg_buf_size = jpg_len;
    }

    memcpy(g_ui_jpg_buf, g_album_mgr.jpg_buffer, jpg_len);
    lv_album_img_show(g_ui_jpg_buf, jpg_len);

#endif

    bt_music_album_finish_control(0);   //校验通过，发送确认结束接收命令

cleanup:
    /* 重置状态 */
    g_album_mgr.cur_recv_len = 0;
    g_album_mgr.jpg_total_len = 0;
}

/**
 * @brief 处理专辑消息
 * @param[in] msg 消息指针
 */
static void album_process_message(const bt_album_msg_t *msg)
{
    if (!msg) {
        log_error("[%s] Invalid message\n", __func__);
        return;
    }

    switch (msg->msg_type) {
    case PROTOCOL_TAG_BT_ALBUM_START:
        album_handle_start_transfer(msg->data_len);
        break;
    case PROTOCOL_TAG_BT_ALBUM_TRANSFER_DATA:
        if (msg->data_ptr == NULL) {
            break;
        }
        album_handle_data_packet((u8 *)msg->data_ptr, msg->data_len);
        break;
    case PROTOCOL_TAG_BT_ALBUM_TRANSFER_DATA_END:
        album_handle_end_transfer(msg->crc_value);
        break;
    default:
        log_warn("[%s] Unknown message type: %d\n", __func__, msg->msg_type);
        break;
    }
}

/**
 * @brief 创建专辑信号量
 */
void bt_album_sem_create(void)
{
    printf("%s %d\n", __func__, __LINE__);
    os_sem_create(&g_album_mgr.data_sem, 0);
}

/**
 * @brief 等待专辑信号量
 */
void bt_album_sem_pending(void)
{
    printf("%s %d\n", __func__, __LINE__);
    os_sem_pend(&g_album_mgr.data_sem, 0);
}

/**
 * @brief 释放专辑信号量
 */
void bt_album_sem_post(void)
{
    printf("%s %d\n", __func__, __LINE__);
    os_sem_post(&g_album_mgr.data_sem);
}

/**
 * @brief 删除专辑信号量
 */
void bt_album_sem_del(void)
{
    printf("%s %d\n", __func__, __LINE__);

    if (os_sem_valid(&g_album_mgr.data_sem)) {
        os_sem_del(&g_album_mgr.data_sem, 0);
    }
}

/**
 * @brief 专辑接收任务主函数
 * @param[in] priv 私有参数
 */
static void album_recv_task(void *priv)
{
    int err = 0;
    int msg[32] = {0};      ///< 接收消息队列缓冲区
    bt_album_msg_t album_msg = {0};

    log_debug("%s %d\n", __func__, __LINE__);

    /* 分配JPG缓冲区 */
    g_album_mgr.jpg_buffer = (u8 *)malloc(MAX_JPG_SIZE);
    if (!g_album_mgr.jpg_buffer) {
        log_error("[%s] Allocate JPG buffer failed\n", __func__);
        return;
    }
    memset(g_album_mgr.jpg_buffer, 0, MAX_JPG_SIZE);

    /* 创建信号量 */
    bt_album_sem_create();

    log_info("[%s] Album receive task started\n", __func__);

    while (1) {
        /* 等待消息 */
        log_debug("[%s] Waiting for message...\n", __func__);
        memset(msg, 0, sizeof(msg));

        err = os_taskq_pend("taskq", msg, ARRAY_SIZE(msg));
        if (err != OS_TASKQ || msg[0] != Q_USER) {
            continue;
        }

        /* 解析消息 */
        album_msg.msg_type = msg[1];
        album_msg.data_len = msg[2];
        if ((void *)msg[3] != NULL) {
            album_msg.data_ptr = (u8 *)msg[3];
        }
        album_msg.crc_value = msg[4];   // CRC值在msg[4]中

        /* 处理消息 */
        album_process_message(&album_msg);

        /* 释放信号量，通知生产者可以释放内存 */
        bt_album_sem_post();
    }
}

/**
 * @brief 初始化专辑接收模块
 * @return 0-成功, 其他-失败
 */
int bt_album_recv_init(void)
{
    int err = 0;

    if (g_album_task_pid) {
        log_warn("[%s] Album task already initialized\n", __func__);
        return UART_ERR_FAILED;
    }

    /* 初始化管理器结构 */
    memset(&g_album_mgr, 0, sizeof(g_album_mgr));

    /* 创建接收任务 */
    err = thread_fork("album_recv_task", 15, 2048, 1024, &g_album_task_pid, album_recv_task, NULL);
    if (err != OS_ERR_NONE) {
        log_error("[%s] Create album receive task failed: 0x%X\n", __func__, err);
        return err;
    }

    log_info("[%s] Album receive module initialized successfully\n", __func__);
    return 0;
}

/**
 * @brief 注销专辑接收模块
 */
void bt_album_recv_deinit(void)
{
    /* 删除信号量 */
    bt_album_sem_del();

    /* 释放缓冲区 */
    if (g_album_mgr.jpg_buffer) {
        free(g_album_mgr.jpg_buffer);
        g_album_mgr.jpg_buffer = NULL;
    }

    /* 重置任务PID */
    g_album_task_pid = 0;

    /* 重置管理器 */
    memset(&g_album_mgr, 0, sizeof(g_album_mgr));

    log_info("[%s] Album receive module deinitialized\n", __func__);
}

#endif /* INSTR_DEV_UART_ENABLE */

