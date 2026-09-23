#include "system/includes.h"
#include "server/video_server.h"
#include "video_rec.h"
#include "app_config.h"
#include "asm/debug.h"
#include "asm/osd.h"
#include "asm/rtc.h"
#include "app_database.h"
#include "storage_device.h"
#include "time.h"
#include "simple_avi_unpkg.h"
#include "include/simple_avi_unpkg.h"
#include "bplus.h"
#include "asm/rtc.h"
#define LOG_TAG_CONST       VIDEO_REC_FILE
#define LOG_TAG             "[VIDEO_REC_FILE]"
#define LOG_ERROR_ENABLE
#define LOG_DEBUG_ENABLE
#define LOG_INFO_ENABLE
/* #define LOG_DUMP_ENABLE */
#define LOG_CLI_ENABLE
#include "debug.h"
#define DB_NULL 2
static const char *rec_path[][2] = {
#ifdef CONFIG_EMR_DIR_ENABLE
    {CONFIG_REC_PATH_0, CONFIG_EMR_REC_PATH_0},
    {CONFIG_REC_PATH_1, CONFIG_EMR_REC_PATH_1},
    {CONFIG_REC_PATH_2, CONFIG_EMR_REC_PATH_2},
#else
    {CONFIG_REC_PATH_0, CONFIG_REC_PATH_0},
    {CONFIG_REC_PATH_1, CONFIG_REC_PATH_1},
    {CONFIG_REC_PATH_2, CONFIG_REC_PATH_2},
#endif
};

#define FILE_NAME_MAX_SIZE 128

static struct VideoConfig *video_configs;
static int  config_video_num;
//默认最多三路
static char date_file[3][FILE_NAME_MAX_SIZE];
static struct video_rec_hdl *rec_handler = NULL;
#define __this 	(rec_handler)

extern int long_file_name_encode(const char *input, u8 *output, u32 output_buf_len);
extern int atoi(const char *__nptr);
extern long int atol(const char *__nptr);
//默认最多三路
static bp_db_t db[3] = {{0}, {0}, {0}};
static u8  db_init = 0;
static u8 cloud_playback_list_kill = 0;

typedef struct cloud_playback_list_info {
    u32 name_num;//文件名 ,为了省内存，文件名字固定
    int32_t day;//用于检索文件名
    uint32_t start_time;
    char      length;

} CLOUD_PLAYBACK_LIST_INFO;

static OS_MUTEX cloud_playback_list_mutex;

#define FOURYEARDAY (365+365+365+366)  //4年一个周期内的总天数（1970~2038不存在2100这类年份，故暂不优化）
static const  uint8_t month_day[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31}; //平年
static const  uint8_t Leap_month_day[12] = {31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31}; //闰年

// 判断是否是闰年
// year: 需要判断的年
// return：1：闰年
//        0: 平年
static uint8_t isLeapYear(uint16_t year)
{
    uint8_t res = 0;
// 能够被4整除
    if (year % 4 == 0) { //能够被100整除，但是不能够被400整除
        if ((year % 100 == 0) && (year % 400 != 0)) {
            res = 0;
        } else {
            res = 1;
        }
    }
    return res;
}

static int dayofweek(int y, int m, int d)
{
    const int t[] = {0, 3, 2, 5, 0, 3, 5, 1, 4, 6, 2, 4};
    if (m < 3) {
        y -= 1;
    }
    return (y + y / 4 - y / 100 + y / 400 + t[m - 1] + d) % 7;
}

// 将北京时间转换为Unix时间戳
// year: 需要判断的年
// return：Unix时间戳（从1970/1/1 00:00:00 到现在的秒数)
// note：没对输入参数正确性做判断
uint64_t covBeijing2UnixTimeStp(struct tm *p)
{
    uint64_t daynum = 0, SecNum = 0; //保存北京时间到起始时间的天数
    uint16_t tempYear = 1970, tempMonth = 0;

    //1.年的天数
    while (tempYear < p->tm_year) {
        if (isLeapYear(tempYear)) {
            daynum += 366;
        } else {
            daynum += 365;
        }
        tempYear++;
    }
    //2.月的天数
    while (tempMonth < p->tm_mon - 1) {
        if (isLeapYear(p->tm_year)) { //闰年
            daynum += Leap_month_day[tempMonth];
        } else {
            daynum += month_day[tempMonth];
        }
        tempMonth++;
    }
    //3.天数
    daynum += (p->tm_mday - 1);

    //4.时分秒
    SecNum = daynum * 24 * 60 * 60; //s
    SecNum += p->tm_hour * 60 * 60;
    SecNum += p->tm_min * 60;
    SecNum += p->tm_sec;

    /* int TIMEZONE = db_select("tzone"); */
    int TIMEZONE = 480; //北京时间时区，默认使用
    //5.时区调整
    SecNum -= TIMEZONE * 60;

    return SecNum;
}

int cloud_playback_list_clear(void)
{
    os_mutex_pend(&cloud_playback_list_mutex, 0);
    //暂时不做删除文件处理
    if (db_init) {
        for (int i = 0; i < config_video_num; i++) {
            int channel = video_configs[i].channel;
            bp_close(&db[channel]);
        }
        db_init = 0;
    }
    /* fdelete_by_name(db.filename); */
    os_mutex_post(&cloud_playback_list_mutex);
    return 0;
}

int cloud_playback_list_add(char *path, int dev_id)
{
    log_info("cloud_playback_list_add %s\n", path);
    struct vfs_attr attr;

    if (!storage_device_ready()) {
        return -1;
    }

    char year_str[5], month_str[3], day_str[3], hour_str[3], minute_str[3], second_str[3];

    // 从字符串中提取年月日时分秒信息
    strncpy(year_str, path + 25, 4);
    year_str[4] = '\0';
    strncpy(month_str, path + 29, 2);
    month_str[2] = '\0';
    strncpy(day_str, path + 31, 2);
    day_str[2] = '\0';
    strncpy(hour_str, path + 34, 2);
    hour_str[2] = '\0';
    strncpy(minute_str, path + 36, 2);
    minute_str[2] = '\0';
    strncpy(second_str, path + 38, 2);
    second_str[2] = '\0';

    int year = atoi(year_str);
    int month = atoi(month_str);
    int day1 = atoi(day_str);
    int hour = atoi(hour_str);
    int minute = atoi(minute_str);
    int second = atoi(second_str);


    struct tm name;
    name.tm_year = year;
    name.tm_mday  = day1;
    name.tm_mon = month;
    name.tm_hour   = hour;
    name.tm_min  = minute;
    name.tm_sec  = second;

    log_debug("Year: %d\n", name.tm_year);
    log_debug("Month: %d\n", name.tm_mon);
    log_debug("Day: %d\n", name.tm_mday);
    log_debug("Hour: %d\n", name.tm_hour);
    log_debug("Minute: %d\n", name.tm_min);
    log_debug("Second: %d\n", name.tm_sec);

    //长文件名转化，打开录像文件，确保文件存在
    char path_file[FILE_NAME_MAX_SIZE];
    int len;

    len = long_file_name_encode(path, (u8 *)path_file, sizeof(path_file));
    memcpy(path, path_file, len);

    /* put_buf(path,len); */

    void *fd = fopen(path, "r");
    if (!fd) {
        return -1;
    }

    os_mutex_pend(&cloud_playback_list_mutex, 0);
#ifdef CONFIG_BOARD_FPGA		    // FPGA

    int length = 60;
#else
    int ret =  avi_net_preview_unpkg_init(fd, 0);
    if (ret) {
        avi_net_unpkg_exit(fd, 0);
        fclose(fd);
        return -1;
    }

    int length = avi_get_file_time(fd, 0);

    avi_net_unpkg_exit(fd, 0);
#endif

    CLOUD_PLAYBACK_LIST_INFO info = {0};
    info.length = length;
    info.name_num = covBeijing2UnixTimeStp(&name);
    fget_attrs(fd, &attr);
    struct tm p;
    p.tm_year = attr.crt_time.year;
    p.tm_mday  = attr.crt_time.day;
    p.tm_mon = attr.crt_time.month;
    p.tm_hour   = attr.crt_time.hour;
    p.tm_min  = attr.crt_time.min;
    p.tm_sec  = attr.crt_time.sec;

    char day[32];
    snprintf(day, sizeof(day), "%d%02d%02d", p.tm_year, p.tm_mon, p.tm_mday);
    info.day = atol(day);
    info.start_time = info.name_num;
    log_info("\n>>>>>>>>>>>>>>>>>> info->name = %d\n", info.name_num);
    log_info("\n>>>>>>>>>>>>>>>>>> info->length = %d \n", info.length);
    log_info("\n>>>>>>>>>>>>>>>>>> info->start_time = %d \n", info.start_time);
    log_info("\n>>>>>>>>>>>>>>>>>> info->day = %d \n", info.day);

    fclose(fd);

    char str[20] = {0};
    snprintf(str, 20, "%d", info.start_time);
    log_debug("bp_set_value =%s\n ", str);
    log_debug("dev_id_bp_set_value =%d\n ", dev_id);
    bp_key_t key;
    bp_value_t value;

    key.length = strlen(str) + 1;
    key.value  = str;

    value.length = sizeof(info);
    /* value.value  = &info; */
    value.value  = (char *)&info;

    if (db_init) {

        bp_set(&db[dev_id], &key, &value);

    }

    os_mutex_post(&cloud_playback_list_mutex);
    return 0;
}
#if 0
int cloud_playback_list_local_remove(char *path)
{
    printf("cloud_playback_list_local_remove %s\n", path);
    CLOUD_PLAYBACK_LIST_INFO info = {0};
    uint64_t file_id = 0;
    int i;
    struct vfs_attr attr;
    if (!storage_device_ready()) {
        return 0;
    }
    os_mutex_pend(&cloud_playback_list_mutex, 0);


    char path_file[FILE_NAME_MAX_SIZE];
    int len;

    len = long_file_name_encode(path, (u8 *)path_file, sizeof(path_file));
    memcpy(path, path_file, len);

    /* put_buf(path,len); */

    /* sprintf(name, "VID_%04d.AVI", p->name_num); */
    void *fd = fopen(path, "r");
    if (!fd) {
        log_error("fopen %s fail\n", path);
        os_mutex_post(&cloud_playback_list_mutex);
        return 0;
    }

    fget_attrs(fd, &attr);
    struct tm p;
    p.tm_year = attr.crt_time.year;
    p.tm_mday  = attr.crt_time.day;
    p.tm_mon = attr.crt_time.month;
    p.tm_hour   = attr.crt_time.hour;
    p.tm_min  = attr.crt_time.min;
    p.tm_sec  = attr.crt_time.sec;


    /* char day[32]; */
    /* snprintf(day, sizeof(day), "%d%02d%02d", attr.crt_time.year, attr.crt_time.month, attr.crt_time.day); */
    /* info.day = atol(day); */
    uint64_t start_time = covBeijing2UnixTimeStp(&p);

    char str[20] = {0};
    snprintf(str, 20, "%ld", start_time);
    if (db_init) {
        bp_removes(&db, str);
    }

    if (fd) {
        fdelete(fd);
    }
    os_mutex_post(&cloud_playback_list_mutex);
    return 0;
}
#endif

void cloud_playback_list_uninit(void)
{
    cloud_playback_list_kill = 1;
    //thread_kill
    os_time_dly(10); //not used thread_kill yet

}

static int __first_file_cb(void *__p, const bp_key_t *key, const bp_value_t *value)
{
    uint64_t *arg = (uint64_t *)__p;
    //删完最后一个再次获取字符串为空
    *arg = 0;
    if (key->value) {
        log_debug("key->value=%s\n", key->value);
        /* if (atol(key->value) != 0) { */
        //sdk发表日期,rtc时钟没联网时时间,这里utc为2022_01_01_00_00_00
        if (atol(key->value) > 1640966400) {
            *arg = atol(key->value);
            return -1;
        }
    }
    return 0;
}

int delete_first_left_file(int dev_id)
{
    u32 start_time = 0;
    u32 end_time = 2015201473;
    char start_time_str[20] = {0};
    char end_time_str[20]    = {0};
    char delete_time_str[20]    = {0};
    int err = 0;
    uint64_t arg = 0;
    sprintf(start_time_str, "%d", start_time);
    sprintf(end_time_str, "%d", end_time);

    os_mutex_pend(&cloud_playback_list_mutex, 0);

    log_info("dev_id_delete_first =%d\n", dev_id);
    bp_get_ranges(&db[dev_id], start_time_str, end_time_str, __first_file_cb, &arg);

    log_debug("arg =%d\n", arg);

    if (arg <= 1640966400) {
        log_error("db is null!\n");
        os_mutex_post(&cloud_playback_list_mutex);
        return DB_NULL;
    }

    /* sprintf(delete_time_str, "%d", arg); */
    sprintf(delete_time_str, "%lld", arg);

    log_debug("dev_id_bp_removes=%d\n", dev_id);
    log_debug("delete_time_str=%s\n", delete_time_str);
    err = bp_removes(&db[dev_id], delete_time_str);
    if (err) {
        log_error("bp_removes_err =%x\n", err);
    }

    os_mutex_post(&cloud_playback_list_mutex);

    char time_str[64] = {0};
    char name[FILE_NAME_MAX_SIZE];
    u8 dir_len = 0;
    struct tm timeinfo = {0};
    time_t timestamp = arg;
    localtime_r(&timestamp, &timeinfo);//将UTC时间转化为当地对应时间

    strcpy(time_str, rec_path[dev_id][0]);
    dir_len = strlen(time_str);
    strftime(time_str + dir_len, sizeof(time_str) - dir_len, "VID_%Y%m%d_%H%M%S.AVI", &timeinfo);
    log_info("recorder file name : %s\n", time_str);//拼接完成由bp表拿到的时间


    int len;
    char path_file[FILE_NAME_MAX_SIZE];

    //长文件名转化utf8
    len = long_file_name_encode(time_str, (u8 *)path_file, sizeof(path_file));
    memcpy(name, path_file, len);


    void *fd = fopen(name, "r");
    if (fd) {
        fdelete(fd);
    } else {
        log_error("fopen %s fail\n", time_str);
        return -1;
    }
    return 0;
}

void cloud_playback_list_task(void *priv)
{
    int len;
    struct tm p;
    struct vfscan *fs = NULL;
    void *fd = NULL;
    int length = 0;
    struct vfs_attr attr;
    u8 bp_find = 0;

    while (!storage_device_ready()) {
        os_time_dly(10);
    }

    const char *file_extension = "INDEX.DAT";
    char file_path[FILE_NAME_MAX_SIZE];

    for (int i = 0; i < config_video_num; i++) {
        int channel = video_configs[i].channel;
        strcpy(file_path, rec_path[channel][0]);
        strcat(file_path, file_extension);

        void *fp = fopen(file_path, "r");
        if (fp) {
            bp_find = 1;
            fclose(fp);
        }
        db_init = 0;
        bp_open(&db[channel], file_path);
    }

    db_init = 1;
    if (bp_find) {
        log_info("db_database find \n\n");
        return;
    }

}

int cloud_playback_list_init()
{
    rec_handler  = (struct video_rec_hdl *)get_video_rec_handler();
    video_configs = get_video_configs();
    config_video_num = get_config_viedo_num();

    os_mutex_create(&cloud_playback_list_mutex);
    cloud_playback_list_kill = 0;
    thread_fork("cloud_playback_list_task", 20, 1024, 0, 0, cloud_playback_list_task, NULL);
    return 0;
}

#include "event/event.h"
#include "event/device_event.h"

/*
 * sd卡插拔事件处理
 */
static void sd_event_handler(struct device_event *event)
{


    /* struct vfs_partition *part = NULL; */
    switch (event->event) {
    case DEVICE_EVENT_IN:


#if 0
        part = fget_partition(CONFIG_ROOT_PATH);
        printf("part_fs_attr: %x\n", part->fs_attr);
        printf("part->clust_size:%d\n", part->clust_size);
        printf("part->fs_type:%d\n", part->fs_type);
#ifdef CONFIG_JLFAT_ENABLE
        if (part->clust_size != 32 * 1024 || (part->fs_attr & F_ATTR_RO)
            || part->fs_type != 0x4) {
#else
        if (part->clust_size != 32 || (part->fs_attr & F_ATTR_RO)
            || part->fs_type != 0x4) {
#endif

            sdcard_storage_device_format(SDX_DEV);
            cpu_reset();
        } else {
            log_info("\nTF use in fat32\n");

        }
#endif

        cloud_playback_list_init();
        break;
    case DEVICE_EVENT_OUT:
        cloud_playback_list_clear();
        break;
    }
}

static int device_event_handler(struct sys_event *e)
{
    struct device_event *event = (struct device_event *)e->payload;

    if (e->from == DEVICE_EVENT_FROM_OTG) {
    } else if (e->from == DEVICE_EVENT_FROM_SD) {
        sd_event_handler(event);
    }

    return 0;
}
/*
 * 静态注册设备事件回调函数，优先级为0
 */
SYS_EVENT_STATIC_HANDLER_REGISTER(device_event2, 0) = {
    .event_type     = SYS_DEVICE_EVENT,
    .prob_handler   = device_event_handler,
    .post_handler   = NULL,
};

static int video_rec_finish_notify(char *path, int dev_id)
{

    cloud_playback_list_add(path, dev_id);
    return 0;
}

static int __get_sys_time(struct sys_time *time)
{

//todo
#if 1		    // FPGA

    struct tm fixed_time = {0};
    fixed_time.tm_year = 2024 - 1900; // 年份要减去1900
    fixed_time.tm_mon = 1 - 1; // 月份需要减去1
    fixed_time.tm_mday = 23;
    fixed_time.tm_hour = 9;
    fixed_time.tm_min = 0;
    fixed_time.tm_sec = 0;

// 获取系统运行时间（秒）
    u32 system_run_time = sys_timer_get_ms() / 1000;
    printf("system_run_time ==%d\n", system_run_time);

// 将固定时间转换为秒数
    time_t fixed_time_sec = mktime(&fixed_time);

// 计算加上系统运行时间后的秒数
    time_t after_time_sec = fixed_time_sec + system_run_time;

// 将加上系统运行时间后的秒数转换为时间结构体
    struct tm *after_timeinfo = localtime(&after_time_sec);

// 输出加上系统运行时间后的日期和时间
    printf("After time: %d-%02d-%02d %02d:%02d:%02d\n",
           after_timeinfo->tm_year,
           after_timeinfo->tm_mon,
           after_timeinfo->tm_mday,
           after_timeinfo->tm_hour,
           after_timeinfo->tm_min,
           after_timeinfo->tm_sec);

    time->year = after_timeinfo->tm_year;
    time->month = after_timeinfo->tm_mon;
    time->day = after_timeinfo->tm_mday;
    time->hour = after_timeinfo->tm_hour;
    time->min = after_timeinfo->tm_min;
    time->sec = after_timeinfo->tm_sec;

    return 0;
#else
    void *fd = dev_open("rtc", NULL);
    if (fd) {
        dev_ioctl(fd, IOCTL_GET_SYS_TIME, (u32)time);
        dev_close(fd);
        return 0;
    }

    return -EINVAL;
#endif
}

void rec_file_name(int format, char *file_name)
{
    struct sys_time time;

    if (__get_sys_time(&time) == 0) {
        if (format == VIDEO_FMT_AVI) {
            sprintf(file_name, "VID_%d%02d%02d_%02d%02d%02d.AVI",
                    time.year, time.month, time.day, time.hour, time.min, time.sec);
        } else if (format == VIDEO_FMT_MOV) {
            sprintf(file_name, "VID_%d%02d%02d_%02d%02d%02d.MOV",
                    time.year, time.month, time.day, time.hour, time.min, time.sec);
        } else if (format == VIDEO_FMT_MP4) {
            sprintf(file_name, "VID_%d%02d%02d_%02d%02d%02d.MP4",
                    time.year, time.month, time.day, time.hour, time.min, time.sec);
        }
    }
}

static u32 video_rec_get_fsize(u8 cycle_time, u16 vid_width, int format)
{
    u32 fsize;

    if (cycle_time > 10 || cycle_time == 0) {
        cycle_time = 3;
    }

    extern int video_rec_get_abr_from(u32 width);
    fsize = video_rec_get_abr_from(vid_width) * cycle_time * 10000 * 2;

    if (format == VIDEO_FMT_AVI) {
        fsize = fsize + fsize / 4;
    }
    log_info("fsize---->> %d \n\n", fsize);

    return fsize;
}

static int video_rec_create_file(int id, u32 fsize, int format, const char *path)
{
    FILE *file;
    int try_cnt = 0;
    char file_path[FILE_NAME_MAX_SIZE];
    char file_name[FILE_NAME_MAX_SIZE];

    rec_file_name(format, file_name);
    sprintf(file_path, "%s%s", path, file_name);

    log_info("id:%d , fopen: %s, min space %dMB\n", id, file_path, fsize >> 20);

    memcpy(date_file[id], file_path, sizeof(file_path)); //将按时间创建出来的文件给到关闭录像时使用

    char path_file[FILE_NAME_MAX_SIZE];
    int len;
    //拼接的长文件名转UTF8才能创建文件
    len = long_file_name_encode(file_path, (u8 *)path_file, sizeof(path_file));
    memcpy(file_path, path_file, sizeof(path_file));
    do {
        file = fopen(file_path, "w+");
        if (!file) {
            log_error("video_rec_create_file fopen faild\n");
            break;
        }
        /* #ifdef CONFIG_NET_ENABLE */
        /* goto __exit;//在写第一帧时候再seek整个文件大小 */
        /* #endif */
        if (fseek(file, fsize, SEEK_SET)) {
            goto __exit;
        }
        fdelete(file);

    } while (++try_cnt < 2);

    return -EIO;

__exit:
    fseek(file, 0, SEEK_SET);
    __this->new_file_size[id] = 0;
    __this->new_file[id] = file;

    return 0;
}

static int get_channel_with_max_file_number()
{
    struct vfscan *fs[3] = {0};//文件扫描结构体句柄
    struct vfs_attr attr[3] = {0};

    // 扫描路径，搜索.avi格式文件-tAVI，按照文件号排序-sn
    for (int i = 0; i < config_video_num; i++) {
        fs[i] = fscan(video_configs[i].path_main, "-tAVI -sn", 1);
        if (fs[i] == NULL) {
            printf("fscan_faild\n");
            return -1;
        }
    }

    int max_num = fs[0]->file_number;
    int channel = 0;

    for (int i = 1; i < config_video_num; i++) {
        if (fs[i]->file_number > max_num) {
            max_num = fs[i]->file_number;
            channel = video_configs[i].channel;
        }
    }

    return channel;
}
int video_rec_del_old_file(int dev_id)
{
    int i, err;
    FILE *file;
    int fsize[4] = {0, 0, 0, 0};
    u32 cur_space = 0;
    u32 need_space = 0;
    int cyc_time = db_select("cyc");

    int channel = 0;
    int create_id = dev_id;

    if (!db_init) {
        log_info("db table is not ready!\n");
        return -1;
    }
    for (i = 0; i < config_video_num; i++) {
        if (dev_id == video_configs[i].channel) {
            channel = i;
            break;
        }
    }
    if (!__this->new_file[dev_id]) {
        fsize[dev_id] = video_rec_get_fsize(cyc_time, video_configs[channel].req.rec.width, video_configs[channel].req.rec.format);
        need_space += fsize[dev_id];
    }
    err = fget_free_space(CONFIG_ROOT_PATH, &cur_space);
    if (err) {
        return err;
    }

    log_info("space: %dMB, %dMB\n", cur_space / 1024, need_space / 1024 / 1024);
    log_debug("fsize%d\n = %x", dev_id, fsize[dev_id]);

    if (cur_space >= (need_space / 1024) * 3) {
        err = video_rec_create_file(video_configs[channel].channel, fsize[dev_id], video_configs[channel].req.rec.format, video_configs[channel].path_main);
        if (err) {
            return err;
        }
        return 0;
    }

    while (1) {
        if (cur_space >= (need_space / 1024) * 3) {
            break;
        }
        //对两路以上删除bp表做处理，删除数目多的
        if (config_video_num > 1) {
            dev_id = get_channel_with_max_file_number();
        }

        int ret = delete_first_left_file(dev_id);
        if (ret == DB_NULL) {
            log_error("please free space for bp!\n");
            return ret;
        }
        if (ret) {
            log_error("delete_first_left_file open file fail!\n");
        }
        fget_free_space(CONFIG_ROOT_PATH, &cur_space);
    }
    log_debug("create_fsize%d = %x", create_id, fsize[create_id]);
    err = video_rec_create_file(video_configs[channel].channel, fsize[create_id], video_configs[channel].req.rec.format, video_configs[channel].path_main);
    if (err) {
        return err;
    }
    return 0;
}

void video_rec_close_file(int dev_id)
{
    if (!__this->file[dev_id]) {
        return;
    }

    char is_emf = 0;
    char *path;
    path = date_file[dev_id];
    log_info("video_rec_close_file path =%s", path);

    fclose(__this->file[dev_id]);
    __this->file[dev_id] = NULL;

    if (path) { //必须关闭文件之后才能调用，否则在读取文件信息不全！！！
        video_rec_finish_notify(path, dev_id);
    }
}

/*
 *注意：循环录像的时候，虽然要重新传参，但是要和start传的参数保持一致！！！
 */
int video_rec_savefile(int dev_id)
{
    int i;
    int err;
    int post_msg = 0;
    log_info(">>>>>> video_rec_savefile : 0x%x \n\n", dev_id);

    if (__this->state != VIDREC_STA_START) {
        return 0;
    }

    if (__this->need_restart_rec) {
        log_debug("need restart rec\n");
        video_rec_stop(0);
        video_rec_start();
        return 0;
    }

    log_debug("\nvideo_rec_start_new_file: %d\n", dev_id);

    video_rec_close_file(dev_id);

    if (__this->new_file[dev_id] == NULL) {

        /* os_mutex_pend(&delete_file_mutex,0); */
        err = video_rec_del_old_file(dev_id);
        /* os_mutex_post(&delete_file_mutex); */
        if (err) {
            goto __err;
        }
        post_msg = 1;
    }
    __this->file[dev_id]     = __this->new_file[dev_id];
    __this->new_file[dev_id] = NULL;

    union video_req req = {0};
    struct video_text_osd text_osd = {0};

    if (!__this->file[dev_id]) {
        return -ENOENT;
    }

    int channel = 0;
    for (int i = 0; i < config_video_num; i++) {
        if (dev_id == video_configs[dev_id].channel) {
            channel = i;
            break;
        }
    }
    assign_video_rec_params(&req, &text_osd, &video_configs[channel]);
    req.rec.file        = __this->file[dev_id];
#ifdef CONFIG_NET_ENABLE
    req.rec.fsize       = __this->new_file_size[dev_id];
#endif
    req.rec.audio.buf   = __this->audio_buf;
    req.rec.buf         = __this->video_buf[dev_id];
    req.rec.state       = VIDEO_STATE_SAVE_FILE;
#ifdef CONFIG_UVC_VIDEO2_ENABLE
    req.rec.uvc_id       = uvc_host_online();
#endif

    if (dev_id == 0) {
        err = server_request(__this->video_rec0, VIDEO_REQ_REC, &req);
    } else if (dev_id == 1) {
        err = server_request(__this->video_rec1, VIDEO_REQ_REC, &req);
    } else if (dev_id == 2) {
        err = server_request(__this->video_rec2, VIDEO_REQ_REC, &req);
    }
    if (err != 0) {
        log_error("rec_save_file: err=%d\n", err);
        goto __err;
    }

    __this->state = VIDREC_STA_START;

    video_rec_state_notify();

    log_info("rec_savefile ok .....\n\n");
    return 0;

__err:
    err = video_rec_stop(0);
    if (err) {
        log_error("\nsave wrong0 %x\n", err);
    }
    __this->state = VIDREC_STA_STOP;
    log_error("rec_savefile err .....\n\n");
    return -EFAULT;
}
