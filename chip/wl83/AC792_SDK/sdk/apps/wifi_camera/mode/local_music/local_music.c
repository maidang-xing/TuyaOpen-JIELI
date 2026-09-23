#include "system/includes.h"
#include "app_config.h"
#include "app_msg.h"
#include "music/music_player.h"
#include "music/breakpoint.h"
#include "app_tone.h"
#include "tone_player.h"
#include "file_player.h"
#include "event/event.h"
#include "event/key_event.h"
#include "event/device_event.h"
#include "local_music.h"
#include "scene_switch.h"
#include "effect/effects_default_param.h"
#include "audio_config_def.h"
#include "device/device.h"
#if TCFG_LOCAL_TWS_ENABLE
#include "local_tws.h"
#endif
#include "wireless_trans.h"
#if TCFG_LE_AUDIO_STREAM_ENABLE
#include "le_audio_recorder.h"
#include "app_le_broadcast.h"
#include "le_audio_player.h"
#endif

#if TCFG_APP_MUSIC_EN

#define LOG_TAG             "[APP_LOCAL_MUSIC]"
#define LOG_ERROR_ENABLE
#define LOG_DEBUG_ENABLE
#define LOG_INFO_ENABLE
/* #define LOG_DUMP_ENABLE */
#define LOG_CLI_ENABLE
#include "debug.h"


#define MUSIC_DEV_ONLINE_START_AFTER_MOUNT_EN			0

//切歌切模式是否保持倍速播放的状态
#define MUSIC_PLAYBACK_SPEED_KEEP            0

//切歌切模式是否保持变调的状态
#define MUSIC_PLAYBACK_PITCH_KEEP            0

//设备提示音使能
#define MUSIC_DEVICE_TONE_EN				1

///模式参数结构体
typedef struct {
    u8 type;
    int val;
} music_task_parm_t;

typedef struct {
    music_task_parm_t task_parm;
    u16 file_err_counter;   //错误文件统计
    u8 file_play_direct;    //0:下一曲， 1：上一曲
    u8 scandisk_break;      //扫描设备打断标志
    char device_tone_dev[16];
    breakpoint_t *breakpoint;
    struct music_player *player_hd;
    speed_level_t speed_mode;
    pitch_level_t pitch_mode;
    u8 scandisk_mark;       //扫描设备标志
    u8 suspend_flag;
    u16 timer;
    u8 close_broadcast_need_resume_local_music_flag;
    u8 music_local_audio_resume_onoff;
    const char *mount_play_logo;
} local_music_t;


static local_music_t music_hdl = {
    .speed_mode = PLAY_SPEED_1,
    .pitch_mode = PITCH_0,
};

#define __this (&music_hdl)


#if MUSIC_DEVICE_TONE_EN

typedef struct {
    const char *logo;
    const char *phy_logo;
    int index;
} dev_tone_t;

enum {
    ///0x1000起始为了不要跟提示音的IDEX_TONE_重叠了
    DEVICE_INDEX_UDISK0 = 0x1000,
    DEVICE_INDEX_UDISK0_REC,
    DEVICE_INDEX_UDISK1,
    DEVICE_INDEX_UDISK1_REC,
    DEVICE_INDEX_SD0,
    DEVICE_INDEX_SD0_REC,
    DEVICE_INDEX_SD1,
    DEVICE_INDEX_SD1_REC,
    DEVICE_INDEX_FLASH,
};

static const dev_tone_t device_tone[] = {
    {"udisk0",      "udisk0",   DEVICE_INDEX_UDISK0},
    {"udisk0_rec",  "udisk0",   DEVICE_INDEX_UDISK0_REC},
    {"udisk1",      "udisk1",   DEVICE_INDEX_UDISK1},
    {"udisk1_rec",  "udisk1",   DEVICE_INDEX_UDISK1_REC},
    {"sd0",         "sd0",      DEVICE_INDEX_SD0},
    {"sd0_rec",     "sd0",      DEVICE_INDEX_SD0_REC},
    {"sd1",         "sd1",      DEVICE_INDEX_SD1},
    {"sd1_rec",     "sd1",      DEVICE_INDEX_SD1_REC},
    {"sdfile",      "sdfile",   DEVICE_INDEX_FLASH},
};
#endif

static int local_music_msg_handler(struct application *app, int *msg);

//*----------------------------------------------------------------------------*/
/**@brief   music 模式首次播放
   @note    切换到音乐模式前可以通过接口music_task_set_parm设置参数, 进入音乐模式后会按照对应参数播放
*/
/*----------------------------------------------------------------------------*/
static void music_player_play_start(void)
{
    switch (__this->task_parm.type) {
    case MUSIC_TASK_START_BY_NORMAL:
        log_info("MUSIC_TASK_START_BY_NORMAL");
        app_send_message(APP_MSG_LOCAL_MUSIC_PLAY_START, 1, 0);
        break;
    case MUSIC_TASK_START_BY_SCLUST:
        log_info("MUSIC_TASK_START_BY_SCLUST");
        app_send_message(APP_MSG_LOCAL_MUSIC_PLAY_START_BY_SCLUST, 0);
        break;
    default:
        break;
    }
}

//*---------------------------------------------------------------------------*/
/**@brief    提示音结束处理
*/
/*----------------------------------------------------------------------------*/
static int music_tone_play_end_callback(void *priv, enum stream_event event)
{
    u32 index = (u32)priv;
    const char *logo = NULL;

    switch (event) {
    case STREAM_EVENT_NONE:
    case STREAM_EVENT_STOP:
        switch (index) {
#if MUSIC_DEVICE_TONE_EN
        case DEVICE_INDEX_UDISK0:
        case DEVICE_INDEX_UDISK0_REC:
        case DEVICE_INDEX_UDISK1:
        case DEVICE_INDEX_UDISK1_REC:
        case DEVICE_INDEX_SD0:
        case DEVICE_INDEX_SD0_REC:
        case DEVICE_INDEX_SD1:
        case DEVICE_INDEX_SD1_REC:
        case DEVICE_INDEX_FLASH:
            for (int i = 0; i < ARRAY_SIZE(device_tone); i++) {
                if (index == device_tone[i].index) {
                    logo = device_tone[i].logo;
                    break;
                }
            }
#if MUSIC_DEV_ONLINE_START_AFTER_MOUNT_EN
            if (__this->mount_play_logo && strcmp(__this->mount_play_logo, logo)) {
                break;
            }
#endif
            app_send_message(APP_MSG_LOCAL_MUSIC_PLAY_START_BY_DEV, 1, (int)logo);
            break;
#endif
        default:
            ///提示音播放结束，启动播放器播放
            music_player_play_start();
            break;
        }
        break;
    default:
        break;
    }

    return 0;
}

#if MUSIC_DEVICE_TONE_EN
static const char *get_music_tone_name_by_logo(const char *logo)
{
    const char *file_name = get_tone_files()->music_mode;

    for (int i = 0; i < ARRAY_SIZE(device_tone); i++) {
        if (strcmp(device_tone[i].logo, logo) == 0) {
            if (device_tone[i].index < DEVICE_INDEX_SD0) {
                file_name = get_tone_files()->device_udisk;
            } else if (device_tone[i].index < DEVICE_INDEX_FLASH) {
                file_name = get_tone_files()->device_sd;
            }
            break;
        }
    }

    return file_name;
}

static int music_device_tone_play(const char *logo)
{
    if (logo == NULL) {
        return -1;
    }

    int ret;

    log_info("device_tone_dev = %s, logo =%s", __this->device_tone_dev, logo);

    const char *phy_logo = dev_manager_get_phy_logo(dev_manager_find_spec(logo, 0));
    if (phy_logo && (strcmp(__this->device_tone_dev, phy_logo) == 0)) {
        log_info("%s is the same phy dev, no need device tone", logo);
        return -1;
    }

    for (int i = 0; i < ARRAY_SIZE(device_tone); i++) {
        if (strcmp(device_tone[i].logo, logo) == 0) {
            log_info("%s device_tone play", logo);
            memset(__this->device_tone_dev, 0, sizeof(__this->device_tone_dev));
            memcpy(__this->device_tone_dev, device_tone[i].phy_logo, strlen(device_tone[i].phy_logo));
#if TCFG_LOCAL_TWS_ENABLE
            const char *file_name = get_music_tone_name_by_logo(logo);
            ret = local_tws_enter_mode(file_name, APP_MODE_LOCAL, (void *)logo);
            if (ret)
#endif
            {
                if (device_tone[i].index < DEVICE_INDEX_SD0) {
                    ret = play_tone_file_callback(get_tone_files()->device_udisk, (void *)device_tone[i].index, music_tone_play_end_callback);
                } else if (device_tone[i].index < DEVICE_INDEX_FLASH) {
                    ret = play_tone_file_callback(get_tone_files()->device_sd, (void *)device_tone[i].index, music_tone_play_end_callback);
                } else {
                    ret = play_tone_file_callback(get_tone_files()->music_mode, (void *)device_tone[i].index, music_tone_play_end_callback);
                }
                if (ret) { //提示音播放失败
                    music_tone_play_end_callback((void *)device_tone[i].index, STREAM_EVENT_NONE);
                }
            }
            return 0;
        }
    }

    return -1;
}
#endif

static void music_save_breakpoint(int save_dec_bp)
{
    const char *logo = NULL;

    if (__this->player_hd) {
        logo = dev_manager_get_logo(__this->player_hd->dev);
    }
    ///save breakpoint, 只保存文件信息
    if (music_player_get_playing_breakpoint(__this->player_hd, __this->breakpoint, save_dec_bp) == TRUE) {
        breakpoint_vm_write(__this->breakpoint, logo);
    }
}

/*获取music app当前播放的设备*/
const char *local_music_app_get_dev_cur(void)
{
    if (__this->player_hd && __this->player_hd->dev) {
        return dev_manager_get_logo(__this->player_hd->dev);
    }
    return NULL;
}

/*获取music app当前的断点地址*/
struct audio_dec_breakpoint *local_music_app_get_dbp_addr(void)
{
    if (__this && __this->breakpoint) {
        return &(__this->breakpoint->dbp);
    }
    return NULL;
}

struct music_player *local_music_app_get_cur_hdl(void)
{
    return __this->player_hd;
}

void local_music_task_set_parm(u8 type, int val)
{
    __this->task_parm.type = type;
    __this->task_parm.val = val;
}

/*根据播放文件的格式动态开启SD卡常活动状态*/
static void music_set_sd_keep_active(const char *logo)
{
    struct imount *mount_hdl = NULL;
    void *dev;

    if (logo) {
        if ((!memcmp(logo, "sd0", strlen("sd0")))
            || (!memcmp(logo, "sd1", strlen("sd1")))) {
            struct file_player *file_play_hd = get_music_file_player();
            mount_hdl = dev_manager_get_mount_hdl(dev_manager_find_spec(logo, 0));
            if (file_play_hd && mount_hdl) {
                dev = mount_hdl->dev.fd;
                if (!dev) {
                    return;
                }
                if (file_play_hd->stream->coding_type == AUDIO_CODING_WAV
                    || file_play_hd->stream->coding_type == AUDIO_CODING_DTS
                    || file_play_hd->stream->coding_type == AUDIO_CODING_FLAC
                    || file_play_hd->stream->coding_type == AUDIO_CODING_APE) {
                    dev_ioctl(dev, IOCTL_SET_ACTIVE_STATUS, 1);
                    log_info("sd set active status");
                } else {
                    dev_ioctl(dev, IOCTL_SET_ACTIVE_STATUS, 0);
                    log_info("sd set inactive status");
                }
            }
        }
    } else {
        //非播放状态 关闭sd卡常活动状态
        mount_hdl = dev_manager_get_mount_hdl(dev_manager_find_spec("sd0", 0));
        if (mount_hdl) {
            dev = mount_hdl->dev.fd;
            if (dev) {
                dev_ioctl(mount_hdl->dev.fd, IOCTL_SET_ACTIVE_STATUS, 0);
                log_info("sd0 set inactive status");
            }
        }
        mount_hdl = dev_manager_get_mount_hdl(dev_manager_find_spec("sd1", 0));
        if (mount_hdl) {
            dev = mount_hdl->dev.fd;
            if (dev) {
                dev_ioctl(mount_hdl->dev.fd, IOCTL_SET_ACTIVE_STATUS, 0);
                log_info("sd1 set inactive status");
            }
        }
    }
}

//*----------------------------------------------------------------------------*/
/**@brief   music 解码成功回调
   @param   priv:私有参数， parm:暂时未用
   @note    此处可以做一些用户操作， 如断点保存， 显示， 获取播放信息等
*/
/*----------------------------------------------------------------------------*/
static void music_player_play_success(void *priv, int parm)
{
    const char *logo = dev_manager_get_logo(__this->player_hd->dev);

#if MUSIC_PLAYBACK_SPEED_KEEP
    struct file_player *file_player = get_music_file_player();
    music_file_set_speed(file_player, __this->speed_mode); //设置播放速度
#endif

#if MUSIC_PLAYBACK_PITCH_KEEP
    struct file_player *file_player = get_music_file_player();
    music_file_set_pitch(file_player, __this->pitch_mode);
#endif

#if TCFG_VOCAL_REMOVER_NODE_ENABLE
    musci_vocal_remover_update_parm();
#endif

    //播放WAV APE 格式歌曲，需设置SD卡常活动状态，提高读取速度
    music_set_sd_keep_active(logo);

    log_info("cur filenum = %d", __this->player_hd->fsn->file_counter);
    log_info("totol filenum = %d", __this->player_hd->fsn->file_number);

    int unicode = 0;
    int name_buf_need_len = 128;
    u8 *music_file_name = zalloc(name_buf_need_len);
    int music_file_name_len = fget_name(__this->player_hd->file, music_file_name, name_buf_need_len);
    if ((music_file_name[0] == '\\') && (music_file_name[1] == 'U')) {
        unicode = 1;
        //music_file_name_len -= 2;
        log_info("cur file(unicode) = %s, len = %d, unicode = %d", music_file_name + 2, music_file_name_len - 2, unicode);
        /* put_buf(music_file_name, music_file_name_len + 2); */
#if 1
        char *utf8 = zalloc(2 * name_buf_need_len);
        if (utf8) {
            int Unicode2UTF8(char *utf8_buf, u16 * pUniBuf, int uni_len);
            Unicode2UTF8(utf8, (u16 *)music_file_name + 1, (music_file_name_len - 2) / 2);
            free(utf8);
            utf8 = NULL;
        }
#endif
    } else {
        log_info("cur file = %s, len = %d, unicode = %d", music_file_name, music_file_name_len, unicode);
    }

    if (music_file_name) {
        free(music_file_name);
    }

    music_save_breakpoint(0);

    app_send_message(APP_MSG_LOCAL_MUSIC_FILE_NUM_CHANGED, 2, __this->player_hd->fsn->file_counter, __this->player_hd->fsn->file_number);

    ai_app_local_event_notify(FILE_PLAYER_START);

    app_send_message(APP_MSG_LOCAL_MUSIC_PLAY_STATUS, 1, music_file_get_player_status(get_music_file_player()));
}

static void send_music_player_end_msg(void *parm)
{
    __this->timer = 0;
    app_send_message(APP_MSG_LOCAL_MUSIC_PLAYER_END, 1, (int)parm);
}

//*----------------------------------------------------------------------------*/
/**@brief   music 解码结束回调处理
   @note    此处统一通过消息的方式发出
*/
/*----------------------------------------------------------------------------*/
static void music_player_play_end(void *priv, int parm)
{
    if (parm) {
        if (__this->timer == 0) {
            __this->timer = sys_timeout_add((void *)parm, send_music_player_end_msg, 1000);
        }
    } else {
        app_send_message(APP_MSG_LOCAL_MUSIC_PLAYER_END, 1, parm);
    }
}

//*----------------------------------------------------------------------------*/
/**@brief   music 解码错误回调
   @note    此处统一将错误通过消息的方式发出
*/
/*----------------------------------------------------------------------------*/
static void music_player_decode_err(void *priv, int parm)
{
    log_error("music_player_decode_err");
    app_send_message(APP_MSG_LOCAL_MUSIC_DEC_ERR, 1, parm);
}

//*----------------------------------------------------------------------------*/
/**@brief   music 播放器扫盘打断接口
   @return  1:打断当前扫描，0:正常扫描
   @note    设备扫描耗时长的情况下， 此接口提供打断机制
*/
/*----------------------------------------------------------------------------*/
static int music_player_scandisk_break(void)
{
    ///需要break fsn的事件， 请在这里拦截,
    ///需要结合MUSIC_PLAYER_ERR_FSCAN错误，做相应的处理
    if (__this->scandisk_break) {
        return 1;
    }

    return 0;
}

static void scan_enter(struct __dev *dev)
{
    __this->scandisk_mark = 1;
}

static void scan_exit(struct __dev *dev)
{
    __this->scandisk_mark = 0;
}

static const player_callback_t music_player_callback = {
    .start  = music_player_play_success,
    .end    = music_player_play_end,
    .err    = music_player_decode_err,
};

static const scan_callback_t scan_cb = {
    .enter      = scan_enter,
    .exit       = scan_exit,
    .scan_break = music_player_scandisk_break,
};

static int local_music_init(void)
{
    __this->player_hd = music_player_creat();
    music_player_reg_scandisk_callback(__this->player_hd, &scan_cb);    //扫盘回调
    music_player_reg_dec_callback(__this->player_hd, &music_player_callback);   //解码状态回调
    __this->breakpoint = breakpoint_handle_creat(); //获取断点句柄， 后面所有断点读/写都需要用到
    __this->file_err_counter = 0;
    __this->file_play_direct = 0;
    __this->scandisk_break = 0;
    __this->mount_play_logo = NULL;
    memset(__this->device_tone_dev, 0, sizeof(__this->device_tone_dev));

#if TCFG_LE_AUDIO_STREAM_ENABLE
    le_audio_scene_deal(LE_AUDIO_APP_MODE_EXIT);
#endif

#if MUSIC_DEVICE_TONE_EN
    music_player_play_start();  //music(首次)播放
#else
    int ret;
#if TCFG_LOCAL_TWS_ENABLE
    ret = local_tws_enter_mode(get_tone_files()->music_mode, APP_MODE_LOCAL, NULL);
    if (ret)
#endif
    {
        tone_player_stop(); //停止播放当前提示音并清空播放队列
        //播放单个提示音文件，支持播放事件回调
        ret = play_tone_file_callback(get_tone_files()->music_mode, NULL, music_tone_play_end_callback);
        if (ret) {
            music_tone_play_end_callback(NULL, STREAM_EVENT_NONE);  //提示音结束处理
            ///该行代码传递参数-》提示音播放结束， 启动播放器播放-music_player_play_start();
        }
    }
#endif

#if ((TCFG_LEA_BIG_CTRLER_TX_EN || TCFG_LEA_BIG_CTRLER_RX_EN) || \
    (TCFG_LE_AUDIO_APP_CONFIG & (LE_AUDIO_AURACAST_SOURCE_EN | LE_AUDIO_JL_AURACAST_SOURCE_EN)) || \
    (TCFG_LE_AUDIO_APP_CONFIG & (LE_AUDIO_AURACAST_SINK_EN | LE_AUDIO_JL_AURACAST_SINK_EN))) && (TCFG_LEA_BIG_FIX_ROLE==2)
    //当固定为接收端时，其它模式下开广播切进music模式，关闭广播后music模式不会自动播放
    music_set_broadcast_local_open_flag(1);
#endif

    /* app_send_message(APP_MSG_ENTER_MODE, APP_MODE_LOCAL_MUSIC); */

    return 0;
}

static int local_music_exit(void)
{
#if TCFG_LOCAL_TWS_ENABLE
    local_tws_exit_mode();
#endif
    music_save_breakpoint(1);
    music_player_stop(__this->player_hd, 1);
    breakpoint_handle_destroy(&__this->breakpoint);
    music_player_destroy(__this->player_hd);
    music_set_sd_keep_active(NULL);

    if (__this->timer) {
        sys_timeout_del(__this->timer);
        __this->timer = 0;
    }

    __this->player_hd = NULL;

    ai_app_local_event_notify(FILE_PLAYER_STOP);

#if TCFG_LE_AUDIO_STREAM_ENABLE
    le_audio_scene_deal(LE_AUDIO_APP_MODE_EXIT);
#endif
    /* app_send_message(APP_MSG_EXIT_MODE, APP_MODE_LOCAL_MUSIC); */

    return 0;
}

//*----------------------------------------------------------------------------*/
/**@brief    music 模式新设备上线处理
*/
/*----------------------------------------------------------------------------*/
static void music_task_dev_online_start(const char *in_logo)
{
    u8 save = 0;
    const char *logo = dev_manager_get_logo(__this->player_hd->dev);

    if (logo && __this->breakpoint) {
        ///新设备上线, 先记录当前设备断点， 然后播放活动设备
        if (music_player_get_playing_breakpoint(__this->player_hd, __this->breakpoint, 1) == TRUE) {
            save = 1;
            //这里不要直接记忆断点， 解码停了之后再记忆
            //breakpoint_vm_write(__this->breakpoint, logo);
        }
    }
    ///停止解码，播放新活动设备
    __this->suspend_flag = 0;
    music_player_stop(__this->player_hd, 1);
    if (save && __this->breakpoint) {
        breakpoint_vm_write(__this->breakpoint, logo);
    }
    //先挂载了设备再执行
    app_send_message(APP_MSG_LOCAL_MUSIC_MOUNT_PLAY_START, 1, (int)in_logo);
}

//*----------------------------------------------------------------------------*/
/**@brief    music 模式设备下线处理
*/
/*----------------------------------------------------------------------------*/
static void music_task_dev_offline_stop(const char *out_logo)
{
    int str_len = 0;
    const char *logo = music_player_get_phy_dev(__this->player_hd, &str_len);

    if (__this->timer) {
        sys_timeout_del(__this->timer);
        __this->timer = 0;
    }
    if (logo == NULL) {
        return;
    }
    if (0 == memcmp(logo, out_logo, str_len)) {
        ///相同的设备才响应
        if (music_player_get_playing_breakpoint(__this->player_hd, __this->breakpoint, 1) == TRUE) {
            dev_manager_set_valid_by_logo(logo, 0); //尽快将设备设置为无效设备
            breakpoint_vm_write(__this->breakpoint, logo);
        } else {
            dev_manager_set_valid_by_logo(logo, 0); //将设备设置为无效设备
        }
        if (__this->scandisk_mark) {
            //自己打断自己的扫描推消息出去,重启解码
            app_send_message(APP_MSG_LOCAL_MUSIC_PLAY_START, 1, 0);
            __this->scandisk_break = 1;
        }

        memset(__this->device_tone_dev, 0, sizeof(__this->device_tone_dev));

        if (music_player_runing()) {
            __this->suspend_flag = 0;
            ///停止解码,防止设备掉线后还继续使用
            music_player_stop(__this->player_hd, 1);
            ///重新选择活动设备播放
            app_send_message(APP_MSG_LOCAL_MUSIC_PLAY_START, 1, 0);
        }
    } else {
        if (!dev_manager_check_by_logo(out_logo)) { //未成功的插入，打断原来播放需恢复
            if (!music_player_runing()) {
                app_send_message(APP_MSG_LOCAL_MUSIC_PLAY_START, 1, 0);
            }
        }
    }
}

//*----------------------------------------------------------------------------*/
/**@brief   music 模式解码错误处理
   @param   err:错误码，详细错误码描述请看MUSIC_PLAYER错误码表枚举
*/
/*----------------------------------------------------------------------------*/
static void music_player_err_deal(int err)
{
    u16 msg = APP_MSG_NULL;
    const char *logo = NULL;

    if (err != MUSIC_PLAYER_ERR_NULL && err != MUSIC_PLAYER_ERR_DECODE_FAIL) {
        __this->file_err_counter = 0;   //清除错误文件累计
    }

    if (err != MUSIC_PLAYER_ERR_NULL && err != MUSIC_PLAYER_SUCC) {
        log_error("music player err = %d", err);
        ai_app_local_event_notify(FILE_PLAYER_STOP);
    }

    switch (err) {
    case MUSIC_PLAYER_SUCC:
        le_audio_scene_deal(LE_AUDIO_MUSIC_START);
        __this->file_err_counter = 0;
        break;
    case MUSIC_PLAYER_ERR_NULL:
        break;
    case MUSIC_PLAYER_ERR_POINT:
    /* fall-through */
    case MUSIC_PLAYER_ERR_NO_RAM:
        msg = APP_MSG_GOTO_NEXT_MODE;
        break;
    case MUSIC_PLAYER_ERR_DECODE_FAIL:
        if (__this->file_err_counter >= __this->player_hd->fsn->file_number) {
            __this->file_err_counter = 0;
            dev_manager_set_valid_by_logo(dev_manager_get_logo(__this->player_hd->dev), 0);///将设备设置为无效设备
            if (dev_manager_get_total(1) == 0) {
                msg = APP_MSG_GOTO_NEXT_MODE;   //没有设备了，退出音乐模式
            } else {
                msg = APP_MSG_LOCAL_MUSIC_AUTO_NEXT_DEV;    //所有文件都是错误的，切换到下一个设备
            }
        } else {
            __this->file_err_counter++;
            if (__this->file_play_direct == 0) {
                msg = APP_MSG_LOCAL_MUSIC_NEXT; //播放下一曲
            } else {
                msg = APP_MSG_LOCAL_MUSIC_PREV; //播放上一曲
            }
        }
        break;
    case MUSIC_PLAYER_ERR_DEV_NOFOUND:
        if (dev_manager_get_total(1) == 0) {
            msg = APP_MSG_GOTO_NEXT_MODE;   //没有设备在线，退出音乐模式
        } else {
            msg = APP_MSG_LOCAL_MUSIC_PLAY_FIRST; //没有找到指定设备，播放之前的活动设备
        }
        break;
    case MUSIC_PLAYER_ERR_FSCAN:
        //需要结合music_player_scandisk_break中处理的标志位处理
        if (__this->scandisk_break) {
            __this->scandisk_break = 0;
            //此处不做任何处理，打断的事件已经重发，由重发事件执行后续处理
            break;
        }
    case MUSIC_PLAYER_ERR_DEV_READ:
    /* fall-through */
    case MUSIC_PLAYER_ERR_DEV_OFFLINE:
        logo = dev_manager_get_logo(__this->player_hd->dev);
        if (dev_manager_online_check_by_logo(logo, 1)) {
            ///如果错误失败在线，并且是播放过程中产生的，先记录下断点
            if (music_player_get_playing_breakpoint(__this->player_hd, __this->breakpoint, 1) == TRUE) {
                music_player_stop(__this->player_hd, 0);    //先停止，防止下一步操作VM卡顿
                breakpoint_vm_write(__this->breakpoint, logo);
            }
            if (err == MUSIC_PLAYER_ERR_FSCAN) {
                dev_manager_set_valid_by_logo(logo, 0); //将设备设置为无效设备
            } else {
                //针对读错误，因为时间推到应用层有延时导致下一个模式判断不正常，此处需要将设备卸载
                dev_manager_unmount(logo);
            }
        }
        if (dev_manager_get_total(1) == 0) {
            msg = APP_MSG_GOTO_NEXT_MODE;   //没有设备在线，退出音乐模式
        } else {
            msg = APP_MSG_LOCAL_MUSIC_AUTO_NEXT_DEV;  //切换设备
        }
        break;
    case MUSIC_PLAYER_ERR_FILE_NOFOUND:
        ///查找文件有扫盘的可能，也需要结合music_player_scandisk_break中处理的标志位处理
        if (__this->scandisk_break) {
            __this->scandisk_break = 0;
            ///此处不做任何处理， 打断的事件已经重发， 由重发事件执行后续处理
            break;
        }
    case MUSIC_PLAYER_ERR_PARM:
        logo = dev_manager_get_logo(__this->player_hd->dev);
        if (dev_manager_online_check_by_logo(logo, 1)) {
            if (__this->player_hd->fsn->file_number) {
                msg = APP_MSG_LOCAL_MUSIC_PLAY_FIRST;   //有文件,播放第一个文件
                break;
            }
        }

        if (dev_manager_get_total(1) == 0) {
            msg = APP_MSG_GOTO_NEXT_MODE;//没有设备了，退出音乐模式
        } else {
            msg = APP_MSG_LOCAL_MUSIC_AUTO_NEXT_DEV;
        }
        break;
    case MUSIC_PLAYER_ERR_FILE_READ:    //文件读错误
        msg = APP_MSG_LOCAL_MUSIC_NEXT; //播放下一曲
        break;
    }

    if (msg != APP_MSG_NULL) {
        app_send_message(msg, 0);
    }
}

static void local_music_pp_handler(void)
{
    struct file_player *file_player = get_music_file_player();
    u8 music_pp_flag = 0;

#if (TCFG_LEA_BIG_CTRLER_TX_EN || TCFG_LEA_BIG_CTRLER_RX_EN) || \
    (TCFG_LE_AUDIO_APP_CONFIG & (LE_AUDIO_AURACAST_SOURCE_EN | LE_AUDIO_JL_AURACAST_SOURCE_EN)) || \
    (TCFG_LE_AUDIO_APP_CONFIG & (LE_AUDIO_AURACAST_SINK_EN | LE_AUDIO_JL_AURACAST_SINK_EN))
#if (TCFG_LEA_BIG_FIX_ROLE==2)
    //固定为接收端
    u8 music_volume_mute_mark = app_audio_get_mute_state(APP_AUDIO_STATE_MUSIC);
    if (get_le_audio_curr_role() == 2 || music_volume_mute_mark == 1) {
        //接收端已连上
        music_volume_mute_mark ^= 1;
        audio_app_mute_en(music_volume_mute_mark);
        return;
    }
#endif
    //不固定角色
    if (file_player && file_player->stream) {
        if (file_player->status == FILE_PLAYER_START) {
#if (TCFG_LEA_BIG_FIX_ROLE==1)
            __this->music_local_audio_resume_onoff = 0;
#endif
#if (TCFG_LEA_BIG_FIX_ROLE==2)
            if (__this->close_broadcast_need_resume_local_music_flag) {
                __this->close_broadcast_need_resume_local_music_flag = 0;
            }
#endif
        } else {
#if (TCFG_LEA_BIG_FIX_ROLE==1)
            __this->music_local_audio_resume_onoff = 1;
#endif
        }
        music_file_player_pp(file_player);
        ai_app_local_event_notify(music_file_get_player_status(file_player));
        le_audio_scene_deal(file_player->status == FILE_PLAYER_START ? LE_AUDIO_MUSIC_START : LE_AUDIO_MUSIC_STOP);
    } else {
        __this->music_local_audio_resume_onoff = 1;
        le_audio_scene_deal(LE_AUDIO_MUSIC_START);
        __this->music_local_audio_resume_onoff = 0;
        ai_app_local_event_notify(music_file_get_player_status(file_player));
    }

    music_pp_flag = 1;
#endif

#if (TCFG_LEA_CIG_CENTRAL_EN || TCFG_LEA_CIG_PERIPHERAL_EN)
    if (((app_get_connected_role() == APP_CONNECTED_ROLE_TRANSMITTER) ||
         (app_get_connected_role() == APP_CONNECTED_ROLE_DUPLEX)) &&
        file_player && file_player->stream) {
        music_file_player_pp(file_player);
        music_pp_flag = 1;
        ai_app_local_event_notify(music_file_get_player_status(file_player));
        le_audio_scene_deal(file_player->status == FILE_PLAYER_START ? LE_AUDIO_MUSIC_START : LE_AUDIO_MUSIC_STOP);
    }
#endif

    if (!music_pp_flag) {
        music_file_player_pp(file_player);
        ai_app_local_event_notify(music_file_get_player_status(file_player));
    }

    app_send_message(APP_MSG_LOCAL_MUSIC_PLAY_STATUS, 1, music_file_get_player_status(file_player));
}

static void local_music_app_suspend(void)
{
    struct file_player *file_player = get_music_file_player();

    if (file_player && music_file_get_player_status(file_player) == FILE_PLAYER_START) {
        local_music_pp_handler();
        __this->suspend_flag = 1;
    }
}

static void local_music_app_resume(void)
{
    if (!__this->suspend_flag) {
        return;
    }

    local_music_pp_handler();

    __this->suspend_flag = 0;
}

static void local_music_app_stop(void)
{
    if (music_player_runing() && music_player_get_playing_breakpoint(__this->player_hd, __this->breakpoint, 1) == TRUE) {
        music_player_stop(__this->player_hd, 0);
        breakpoint_vm_write(__this->breakpoint, dev_manager_get_logo(__this->player_hd->dev));
    }

    __this->suspend_flag = 0;
}

static int local_music_play_start(u8 le_audio)
{
    int err = MUSIC_PLAYER_ERR_NULL;

    ///断点播放活动设备
    const char *logo = dev_manager_get_logo(dev_manager_find_active(1));
    if (music_player_runing()) {
        if (dev_manager_get_logo(__this->player_hd->dev) && logo) {///播放的设备跟当前活动的设备是同一个设备，不处理
            if (0 == strcmp(logo, dev_manager_get_logo(__this->player_hd->dev))) {
                if (le_audio) {
                    music_player_stop(music_hdl.player_hd, 0);
                } else {
                    log_warn("the same dev!!!");
                    return err;
                }
            }
        }
    }

#if (MUSIC_DEVICE_TONE_EN)
    if (!le_audio && 0 == music_device_tone_play(logo)) {
        return err;
    }
#endif

    log_info("play start %s", logo);

    if (!le_audio && le_audio_scene_deal(LE_AUDIO_APP_MODE_ENTER) > 0) {
        return err;
    }

    if (TRUE == breakpoint_vm_read(__this->breakpoint, logo)) {
        err = music_player_play_by_breakpoint(__this->player_hd, logo, __this->breakpoint);
    } else {
        err = music_player_play_first_file(__this->player_hd, logo);
    }

    if (le_audio) {
        if (err == MUSIC_PLAYER_SUCC) {
            update_le_audio_deal_scene(LE_AUDIO_MUSIC_START);
        } else {
            le_audio_scene_deal(LE_AUDIO_MUSIC_STOP);
        }
    }

    return err;
}

#if (TCFG_LEA_BIG_CTRLER_TX_EN || TCFG_LEA_BIG_CTRLER_RX_EN || TCFG_LEA_CIG_CENTRAL_EN || TCFG_LEA_CIG_PERIPHERAL_EN) || \
    (TCFG_LE_AUDIO_APP_CONFIG & (LE_AUDIO_AURACAST_SOURCE_EN | LE_AUDIO_JL_AURACAST_SOURCE_EN)) || \
    (TCFG_LE_AUDIO_APP_CONFIG & (LE_AUDIO_AURACAST_SINK_EN | LE_AUDIO_JL_AURACAST_SINK_EN)) || \
    (TCFG_LE_AUDIO_APP_CONFIG & (LE_AUDIO_UNICAST_SOURCE_EN | LE_AUDIO_JL_UNICAST_SOURCE_EN)) || \
    (TCFG_LE_AUDIO_APP_CONFIG & (LE_AUDIO_UNICAST_SINK_EN | LE_AUDIO_JL_UNICAST_SINK_EN))

static u8 g_le_audio_flag;

/* --------------------------------------------------------------------------*/
/**
 * @brief 获取音乐模式广播音频流开启标志
 *
 * @return 广播音频流开启标志
 */
/* ----------------------------------------------------------------------------*/
u8 get_music_le_audio_flag(void)
{
    return g_le_audio_flag;
}

/*设置music app 的广播音箱句柄*/
u8 music_app_set_btaddr(void *le_audio, struct stream_enc_fmt *fmt)
{
    if (__this->player_hd) {
        __this->player_hd->le_audio = le_audio;
        memcpy(&__this->player_hd->fmt, fmt, sizeof(struct stream_enc_fmt));
        return 0;
    }
    return -1;
}

//当固定为接收端时，其它模式下开广播切进music模式，关闭广播后music模式不会自动播放
void music_set_broadcast_local_open_flag(u8 en)
{
#if (TCFG_LEA_BIG_FIX_ROLE==2)
    __this->close_broadcast_need_resume_local_music_flag = en;
#endif
}

static int get_music_play_status(void)
{
    if (get_le_audio_app_mode_exit_flag()) {
        return LOCAL_AUDIO_PLAYER_STATUS_STOP;
    }

#if (TCFG_LEA_BIG_CTRLER_TX_EN || TCFG_LEA_BIG_CTRLER_RX_EN) || \
    (TCFG_LE_AUDIO_APP_CONFIG & (LE_AUDIO_AURACAST_SOURCE_EN | LE_AUDIO_JL_AURACAST_SOURCE_EN)) || \
    (TCFG_LE_AUDIO_APP_CONFIG & (LE_AUDIO_AURACAST_SINK_EN | LE_AUDIO_JL_AURACAST_SINK_EN))
    if (__this->music_local_audio_resume_onoff == 1) {
        return LOCAL_AUDIO_PLAYER_STATUS_PLAY;
    }

#if (TCFG_LEA_BIG_FIX_ROLE==2)
    //固定为接收端时，打开广播接收后，如果连接上了会关闭本地的音频，当关闭广播后，需要恢复本地的音频播放
    /* __this->close_broadcast_need_resume_local_music_flag = 0; */
    if (__this->close_broadcast_need_resume_local_music_flag == 1) {
        return LOCAL_AUDIO_PLAYER_STATUS_PLAY;
    } else {
        return LOCAL_AUDIO_PLAYER_STATUS_STOP;
    }
#endif
#endif

    if (music_file_get_player_status(get_music_file_player()) == FILE_PLAYER_START) {
        return LOCAL_AUDIO_PLAYER_STATUS_PLAY;
    } else {
        return LOCAL_AUDIO_PLAYER_STATUS_STOP;
    }
}

static int music_local_audio_open(void)
{
    int err = MUSIC_PLAYER_ERR_NULL;

#if 0
    if (get_music_play_status() != LOCAL_AUDIO_PLAYER_STATUS_PLAY) {
        return 0;
    }
#endif

    //打开本地播放
#if (TCFG_LEA_BIG_FIX_ROLE==2)
    if (__this->close_broadcast_need_resume_local_music_flag) {
        __this->close_broadcast_need_resume_local_music_flag = 0;
    }
#endif

    const char *logo = dev_manager_get_logo(dev_manager_find_active(1));
    if (music_player_runing()) {
        if (dev_manager_get_logo(__this->player_hd->dev) && logo) {///播放的设备跟当前活动的设备是同一个设备，不处理
            if (0 == strcmp(logo, dev_manager_get_logo(__this->player_hd->dev))) {
                log_info("the same dev!!");
                return TRUE;
            }
        }
    }

    if (TRUE == breakpoint_vm_read(__this->breakpoint, logo)) {
        err = music_player_play_by_breakpoint(__this->player_hd, logo, __this->breakpoint);
    } else {
        err = music_player_play_first_file(__this->player_hd, logo);
    }

    ///错误处理
    music_player_err_deal(err);

    return err;
}

static int music_local_audio_close(void)
{
#if 0
    if (get_music_play_status() != LOCAL_AUDIO_PLAYER_STATUS_PLAY) {
        return 0;
    }
#endif

    struct file_player *file_player = get_music_file_player();
#if TCFG_LEA_BIG_FIX_ROLE
    if (music_file_get_player_status(file_player) == FILE_PLAYER_START) {
        __this->music_local_audio_resume_onoff = 1;	//关闭广播需要恢复本地音频播放
    } else {
        __this->music_local_audio_resume_onoff = 0;	//关闭广播需要恢复本地音频播放
    }
#endif

    if (music_player_runing()) {
#if ((TCFG_LEA_BIG_CTRLER_TX_EN || TCFG_LEA_BIG_CTRLER_RX_EN) || \
    (TCFG_LE_AUDIO_APP_CONFIG & (LE_AUDIO_AURACAST_SOURCE_EN | LE_AUDIO_JL_AURACAST_SOURCE_EN)) || \
    (TCFG_LE_AUDIO_APP_CONFIG & (LE_AUDIO_AURACAST_SINK_EN | LE_AUDIO_JL_AURACAST_SINK_EN))) && (TCFG_LEA_BIG_FIX_ROLE==2)
        /* if (music_player_runing()) {	//这句判断需要放在 music_player_stop之前 */
        __this->close_broadcast_need_resume_local_music_flag = 1;
        /* } */
#endif
        //关闭本地播放
        if (music_player_get_playing_breakpoint(__this->player_hd, __this->breakpoint, 1) == TRUE) {
            music_player_stop(__this->player_hd, 0); //先停止，防止下一步操作VM卡顿
            breakpoint_vm_write(__this->breakpoint, dev_manager_get_logo(__this->player_hd->dev));
        } else {
            music_player_stop(__this->player_hd, 0);
        }
    } else {
#if (TCFG_LEA_BIG_FIX_ROLE==1)
        __this->music_local_audio_resume_onoff = 0;
#endif
    }

    return 0;
}

static void *music_tx_le_audio_open(void *fmt)
{
#if 0
    if (get_music_play_status() != LOCAL_AUDIO_PLAYER_STATUS_PLAY) {
        return NULL;
    }
#endif

    g_le_audio_flag = 1;

    //打开广播音频播放
    struct le_audio_stream_params *params = (struct le_audio_stream_params *)fmt;
    struct le_audio_stream_format stream_fmt = params->fmt;
    void *le_audio = le_audio_stream_create(params->conn, &params->fmt);

    struct stream_enc_fmt enc_fmt = {
        .coding_type = stream_fmt.coding_type,
        .channel = stream_fmt.nch,
        .bit_rate = stream_fmt.bit_rate,
        .sample_rate = stream_fmt.sample_rate,
        .frame_dms = stream_fmt.frame_dms,
    };

    music_app_set_btaddr(le_audio, &enc_fmt);

    app_send_message(APP_MSG_LOCAL_MUSIC_PLAY_START, 1, 1);

    return le_audio;
}

static int music_tx_le_audio_close(void *le_audio)
{
    if (!le_audio) {
        return -EPERM;
    }

    g_le_audio_flag = 0;

    if (music_player_get_playing_breakpoint(__this->player_hd, __this->breakpoint, 1) == TRUE) {
        music_player_stop(__this->player_hd, 0); //先停止，防止下一步操作VM卡顿
        breakpoint_vm_write(__this->breakpoint, dev_manager_get_logo(__this->player_hd->dev));
    }
    //关闭广播音频播放
#if TCFG_LEA_LOCAL_SYNC_PLAY_EN
    le_audio_player_close(le_audio);
#endif
    le_audio_stream_free(le_audio);

    return 0;
}

const struct le_audio_mode_ops le_audio_local_music_ops = {
    .local_audio_open = music_local_audio_open,
    .local_audio_close = music_local_audio_close,
    .tx_le_audio_open = music_tx_le_audio_open,
    .tx_le_audio_close = music_tx_le_audio_close,
    .rx_le_audio_open = default_rx_le_audio_open,
    .rx_le_audio_close = default_rx_le_audio_close,
    .play_status = get_music_play_status,
};

#endif

static int local_music_msg_handler(struct application *app, int *msg)
{
    int err = MUSIC_PLAYER_ERR_NULL;
    const char *logo;

    struct file_player *file_player = get_music_file_player();

    switch (msg[0]) {
    case APP_MSG_SUSPEND:
        local_music_app_suspend();
        break;
    case APP_MSG_RESUME:
        local_music_app_resume();
        break;
    case APP_MSG_STOP:
        local_music_app_stop();
        break;
    case APP_MSG_LOCAL_MUSIC_PP:
        log_info("pp");
        local_music_pp_handler();
        break;
    case APP_MSG_LOCAL_MUSIC_PLAY:
        log_info("play");
        if (music_file_get_player_status(file_player) != FILE_PLAYER_START) {
            local_music_pp_handler();
        }
        break;
    case APP_MSG_LOCAL_MUSIC_PAUSE:
        log_info("pause");
        if (music_file_get_player_status(file_player) == FILE_PLAYER_START) {
            local_music_pp_handler();
        }
        break;
    case APP_MSG_LOCAL_MUSIC_SPEED_UP:
        log_info("speed up");
        __this->speed_mode = music_file_speed_up(file_player);
        break;
    case APP_MSG_LOCAL_MUSIC_SPEED_DOWN:
        log_info("speed down");
        __this->speed_mode = music_file_speed_down(file_player);
        break;
    case APP_MSG_LOCAL_MUSIC_PITCH_UP:
        log_info("pitch up");
        __this->pitch_mode = music_file_pitch_up(file_player);
        break;
    case APP_MSG_LOCAL_MUSIC_PITCH_DOWN:
        log_info("pitch down");
        __this->pitch_mode = music_file_pitch_down(file_player);
        break;
    case APP_MSG_LOCAL_MUSIC_CHANGE_REPEAT:
        log_info("change repeat");
        music_player_change_repeat_mode(__this->player_hd);
        app_send_message(APP_MSG_LOCAL_MUSIC_REPEAT_MODE_CHANGED, 1, music_player_get_repeat_mode());
        break;
    case APP_MSG_LOCAL_MUSIC_PLAYER_AB_REPEAT_SWITCH:
        log_info("ab repeat switch");
#if FILE_DEC_AB_REPEAT_EN
        music_file_ab_repeat_switch(file_player);
#endif
        break;
    case APP_MSG_LOCAL_MUSIC_PLAY_FIRST:
        log_info("play first file");
        err = music_player_play_first_file(__this->player_hd, NULL);
        break;
    case APP_MSG_LOCAL_MUSIC_NEXT:
        log_info("play next");
        __this->file_play_direct = 0;
        err = music_player_play_next(__this->player_hd);
        break;
    case APP_MSG_LOCAL_MUSIC_PREV:
        log_info("play prev");
        __this->file_play_direct = 1;
        err = music_player_play_prev(__this->player_hd);
        break;
    case APP_MSG_LOCAL_MUSIC_PLAY_PREV_FOLDER:
        log_info("play prev folder");
        err = music_player_play_folder_prev(__this->player_hd);
        break;
    case APP_MSG_LOCAL_MUSIC_PLAY_NEXT_FOLDER:
        log_info("play next folder");
        err = music_player_play_folder_next(__this->player_hd);
        break;
    case APP_MSG_LOCAL_MUSIC_AUTO_NEXT_DEV:
    /* fall-through */
    case APP_MSG_LOCAL_MUSIC_CHANGE_DEV:
        log_info("change play dev");
        __this->mount_play_logo = NULL;
        u8 auto_next_dev = ((msg[0] == APP_MSG_LOCAL_MUSIC_AUTO_NEXT_DEV) ? 1 : 0);
        logo = music_player_get_dev_next(__this->player_hd, auto_next_dev);
        if (logo == NULL) { ///找不到下一个设备，不响应设备切换
            break;
        }
        __this->suspend_flag = 0;
        log_info("next dev is %s", logo);
        ///切换设备前先保存一下上一个设备的断点信息,包括文件和解码信息
        if (music_player_get_playing_breakpoint(__this->player_hd, __this->breakpoint, 1) == TRUE) {
            music_player_stop(__this->player_hd, 0); //先停止，防止下一步操作VM卡顿
            breakpoint_vm_write(__this->breakpoint, dev_manager_get_logo(__this->player_hd->dev));
        }
#if (MUSIC_DEVICE_TONE_EN)
        if (0 == music_device_tone_play(logo)) {
            break;
        }
#endif
        if (TRUE == breakpoint_vm_read(__this->breakpoint, logo)) {
            err = music_player_play_by_breakpoint(__this->player_hd, logo, __this->breakpoint);
        } else {
            err = music_player_play_first_file(__this->player_hd, logo);
        }
        break;
#if TCFG_MIX_RECORD_ENABLE
    //只有使能录音宏，才会出现删文件的操作，此时可能会出现删了最后一个文件的情况
    case APP_MSG_LOCAL_MUSIC_DELETE_CUR_FILE:
        // 删除当前文件
        int ret = music_player_delete_playing_file(__this->player_hd);
        if (ret != MUSIC_PLAYER_SUCC) {
            //播放失败，此时可能删除了最后一个可播放的文件，处理是：切换模式
            log_error("music_player_delete_playing_file error : %d", ret);
        }
        break;
#endif
#if TCFG_RECORD_FOLDER_DEV_ENABLE
    case APP_MSG_LOCAL_MUSIC_PLAY_REC_FOLDER_SWITCH:
        log_info("play rec folder switch");
        // 切换到录音文件夹里播录音
        logo = dev_manager_get_logo(__this->player_hd->dev);
        if (logo == NULL) {
            err = MUSIC_PLAYER_ERR_RECORD_DEV;
        } else {
            err = music_player_play_by_path(__this->player_hd, logo, REC_FOLDER_NAME);
        }
        break;
#endif
    case APP_MSG_LOCAL_MUSIC_PLAY_START_BY_DEV:
#if (MUSIC_DEVICE_TONE_EN)
        logo = (const char *)msg[1];
        log_info("play start by dev %s", logo);
        if (logo) {
            if (le_audio_scene_deal(LE_AUDIO_APP_MODE_ENTER) > 0) {
                break;
            }
            if (TRUE == breakpoint_vm_read(__this->breakpoint, logo)) {
                err = music_player_play_by_breakpoint(__this->player_hd, logo, __this->breakpoint);
            } else {
                err = music_player_play_first_file(__this->player_hd, logo);
            }
        }
        break;
#endif
    case APP_MSG_LOCAL_MUSIC_MOUNT_PLAY_START:
        logo = (const char *)msg[1];
        log_info("mount play start %s", logo);
        dev_manager_set_active_by_logo(logo);
    /* fall-through */
    case APP_MSG_LOCAL_MUSIC_PLAY_START:
        log_info("play start");
        err = local_music_play_start(msg[1]);
        break;
    case APP_MSG_LOCAL_MUSIC_PLAY_START_BY_SCLUST:
        log_info("play start by sclust");
        logo = dev_manager_get_logo(dev_manager_find_active(1));
        err = music_player_play_by_sclust(__this->player_hd, logo, msg[1]);
        break;
    case APP_MSG_LOCAL_MUSIC_FR:
        log_info("play fr");
        music_file_player_fr(3, file_player);
        break;
    case APP_MSG_LOCAL_MUSIC_FF:
        log_info("play ff");
        music_file_player_ff(3, file_player);
        break;
    case APP_MSG_LOCAL_MUSIC_PLAYER_END:
        log_info("play end");
        err = music_player_end_deal(__this->player_hd, msg[1]);
        break;
    case APP_MSG_LOCAL_MUSIC_DEC_ERR:
        err = music_player_decode_err_deal(__this->player_hd, msg[1]);
        break;
    case APP_MSG_LOCAL_MUSIC_PLAY_BY_NUM:
        log_info("play by num :%d", msg[1]);
        logo = dev_manager_get_logo(dev_manager_find_active(1));
        err = music_player_play_by_number(__this->player_hd, logo, msg[1]);
        break;
    case APP_MSG_LOCAL_MUSIC_PLAY_START_AT_DEST_TIME:
#if FILE_DEC_DEST_PLAY
        if (music_player_runing()) {
            //for test 测试MP3定点播放功能
            log_info("play start at %dms", msg[1]);
            file_dec_set_start_play(msg[1], AUDIO_CODING_MP3);
        }
#endif
        break;
    default:
        break;
    }

    music_player_err_deal(err);

    return 0;
}

static int local_music_device_event_handler(enum device_event_from from, struct device_event *device_event)
{
    if (from == DEVICE_EVENT_FROM_SD || from == DEVICE_EVENT_FROM_UDISK) {
        const char *logo = (const char *)device_event->arg;

        switch (device_event->event) {
        case DEVICE_EVENT_OUT:
            music_task_dev_offline_stop(logo);
#if MUSIC_DEV_ONLINE_START_AFTER_MOUNT_EN
            if (__this->mount_play_logo && !strcmp(__this->mount_play_logo, logo)) {
                __this->mount_play_logo = NULL;
            }
#endif
            break;
        case DEVICE_EVENT_IN:
            if (__this->scandisk_mark) {
                __this->scandisk_break = 1;
            }
#if MUSIC_DEV_ONLINE_START_AFTER_MOUNT_EN
            music_task_dev_online_start(logo);
            __this->mount_play_logo = logo;
#endif
            break;
        }
    }

    return FALSE;
}

static int local_music_key_click(struct key_event *key)
{
    int ret = TRUE;

    switch (key->value) {
    case KEY_OK:
        app_send_message(APP_MSG_LOCAL_MUSIC_PP, 0);
        break;
    case KEY_PLAY:
        app_send_message(APP_MSG_LOCAL_MUSIC_PLAY, 0);
        break;
    case KEY_PAUSE:
        app_send_message(APP_MSG_LOCAL_MUSIC_PAUSE, 0);
        break;
    default:
        ret = FALSE;
        break;
    }

    return ret;
}

static int local_music_key_long(struct key_event *key)
{
    int ret = TRUE;

    switch (key->value) {
    case KEY_VOLUME_DEC:
    case KEY_UP:
    case KEY_PREV:
        app_send_message(APP_MSG_LOCAL_MUSIC_PREV, 0);
        break;
    case KEY_VOLUME_INC:
    case KEY_DOWN:
    case KEY_NEXT:
        app_send_message(APP_MSG_LOCAL_MUSIC_NEXT, 0);
        break;
    case KEY_MODE:
        app_send_message(APP_MSG_LOCAL_MUSIC_CHANGE_DEV, 0);
        break;
    default:
        ret = FALSE;
        break;
    }

    return ret;
}

static int local_music_key_hold(struct key_event *key)
{
    return FALSE;
}

static int local_music_key_event_handler(struct key_event *key)
{
    int ret = FALSE;

    switch (key->action) {
    case KEY_EVENT_CLICK:
        ret = local_music_key_click(key);
        break;
    case KEY_EVENT_LONG:
        ret = local_music_key_long(key);
        break;
    case KEY_EVENT_HOLD:
        ret = local_music_key_hold(key);
        break;
    default:
        break;
    }

    return ret;
}

static int local_music_event_handler(struct application *app, struct sys_event *event)
{
    switch (event->type) {
    case SYS_KEY_EVENT:
        return local_music_key_event_handler((struct key_event *)event->payload);
    case SYS_DEVICE_EVENT:
        return local_music_device_event_handler(event->from, (struct device_event *)event->payload);
    default:
        return FALSE;
    }
}

static int local_music_state_machine(struct application *app, enum app_state state,
                                     struct intent *it)
{
    switch (state) {
    case APP_STA_CREATE:
        local_music_init();
        break;
    case APP_STA_START:
        break;
    case APP_STA_PAUSE:
        local_music_app_suspend();
        break;
    case APP_STA_RESUME:
        local_music_app_resume();
        break;
    case APP_STA_STOP:
        break;
    case APP_STA_DESTROY:
        local_music_exit();
        break;
    case APP_STA_COMPLETE:
        break;
    }

    return 0;
}

static int scandisk_break_event_handler(struct sys_event *event)
{
    struct key_event *key = (struct key_event *)event->payload;
    struct device_event *device = (struct device_event *)event->payload;

    switch (event->type) {
    case SYS_KEY_EVENT:
        if (key->value == KEY_MODE && (key->value == KEY_POWER && key->action == KEY_EVENT_LONG)) {
            if (__this->scandisk_mark) {
                __this->scandisk_break = 1;
            }
        }
        break;
    case SYS_DEVICE_EVENT:
        if (event->from == DEVICE_EVENT_FROM_SD || event->from == DEVICE_EVENT_FROM_UDISK) {
            const char *evt_logo = (const char *)device->arg;
            int str_len = 0;
            const char *logo;

            switch (device->event) {
            case DEVICE_EVENT_OUT:
                logo = music_player_get_phy_dev(__this->player_hd, &str_len);
                if (__this->scandisk_mark && logo && (0 == memcmp(logo, evt_logo, str_len))) {
                    ///相同的设备才响应
                    __this->scandisk_break = 1;
                }
                break;
            case DEVICE_EVENT_IN:
                if (__this->scandisk_mark) {
                    __this->scandisk_break = 1;
                }
                break;
            }
        }
        break;
    case SYS_NET_EVENT:
        break;
    case SYS_BT_EVENT:
        break;
    }

    return FALSE;
}

//注册提前打断fscan操作的事件预处理
SYS_EVENT_STATIC_HANDLER_REGISTER(scandisk_break, 3) = {
    .event_type     = SYS_KEY_EVENT | SYS_DEVICE_EVENT,
    .prob_handler   = scandisk_break_event_handler,
    .post_handler   = NULL,
};

static const struct application_operation local_music_ops = {
    .state_machine  = local_music_state_machine,
    .event_handler 	= local_music_event_handler,
    .msg_handler 	= local_music_msg_handler,
};

REGISTER_APPLICATION(local_music) = {
    .name   = "local_music",
    .ops    = &local_music_ops,
    .state  = APP_STA_DESTROY,
};

#if MUSIC_DEV_ONLINE_START_AFTER_MOUNT_EN

//设备插入检测触发app切换动作
static int local_device_detect_event_handler(void *evt)
{
    struct intent it;
    struct device_event *event = (struct device_event *)evt;

    if (event->event == DEVICE_EVENT_IN) {
        if (current_app_in_mode(APP_MODE_LOCAL) == FALSE) {
            os_taskq_del_type("app_core", MSG_FROM_APP);
            app_mode_change(APP_MODE_LOCAL);
        }
    } else {
        if (current_app_in_mode(APP_MODE_LOCAL) == TRUE && dev_manager_get_total(1) == 0) {
            os_taskq_del_type("app_core", MSG_FROM_APP);
            app_mode_go_back();
        }
    }

    return FALSE;
}

REGISTER_APP_EVENT_HANDLER(sd_device_detect_event) = {
    .event      = SYS_DEVICE_EVENT,
    .from       = DEVICE_EVENT_FROM_SD,
    .handler    = local_device_detect_event_handler,
};

REGISTER_APP_EVENT_HANDLER(udisk_device_detect_event) = {
    .event      = SYS_DEVICE_EVENT,
    .from       = DEVICE_EVENT_FROM_UDISK,
    .handler    = local_device_detect_event_handler,
};

#endif


#if TCFG_LOCAL_TWS_ENABLE
static void local_tws_local_music_start(void *priv)
{
    if (priv) {
        app_send_message(APP_MSG_LOCAL_MUSIC_PLAY_START_BY_DEV, 1, (int)priv);
    } else {
        music_player_play_start();
    }
}

static bool get_local_music_player_status(void)
{
    return music_file_get_player_status(get_music_file_player()) == FILE_PLAYER_START ? TRUE : FALSE;
}

REGISTER_LOCAL_TWS_OPS(tws_local_music) = {
    .mode = APP_MODE_LOCAL,
    .name = "local_music",
    .audio_open = local_tws_local_music_start,
    .get_play_status = get_local_music_player_status,
};
#endif

#endif
