#include "classic/hci_lmp.h"
#include "btstack/btstack_task.h"
#include "btstack/avctp_user.h"
#include "btcontroller_modules.h"
#include "btcontroller_mode.h"
#include "bt_common.h"
#include "tone_player.h"
#include "audio_config.h"
#include "system/timer.h"
#include "app_power_manage.h"
#include "event/bt_event.h"
#include "math.h"
#include "app_config.h"
#if THIRD_PARTY_PROTOCOLS_SEL
#include "multi_protocol_main.h"
#endif
#if TCFG_LE_AUDIO_STREAM_ENABLE
#include "wireless_trans.h"
#endif

static void multi_box_in_bis_start_notify(u8 role);

/*************************************************************************************************/
/*!
 *  \brief      蓝牙连接配置，提供app层用户可以输入配对鉴定key
 *
 *  \param      key :配对需要输入的数字
 *
 *  \return
 *
 *  \note       配对需要输入6位数字的时候，按照顺序从左到右一个个输入
 */
/*************************************************************************************************/
static void bt_send_keypress(u8 key)
{
    log_info("bt_send_keypress:%d", key);
    bt_cmd_prepare(USER_CTRL_KEYPRESS, 1, &key);
}

/*************************************************************************************************/
/*!
 *  \brief      蓝牙连接配置，提供app层用户可以输入确定或者否定
 *
 *  \param      en 0:否定   1:确定
 *
 *  \return
 *
 *  \note       在连接过程中类似手机弹出 确定和否定 按键，可以供用户界面设置
 */
/*************************************************************************************************/
static void bt_send_pair(u8 en)
{
    bt_cmd_prepare(USER_CTRL_PAIR, 1, &en);
}

/*************************************************************************************************/
/*!
 *  \brief      蓝牙获取vm连接记录信息
 *
 *  \param      [in]
 *
 *  \return
 *
 *  \note
 */
/*************************************************************************************************/
static void bt_init_ok_search_index(void)
{
    if (bt_get_current_poweron_memory_search_index(__this->auto_connection_addr)) {
        log_info("bt_wait_connect_and_phone_connect_switch");
        bt_clear_current_poweron_memory_search_index(1);
    }
}

/*************************************************************************************************/
/*!
 *  \brief      蓝牙初始化完成
 *
 *  \param      [in]
 *
 *  \return
 *
 *  \note
 */
/*************************************************************************************************/
static void bt_status_init_ok(void)
{
    if (__this->init_ok) {
        return;
    }

    __this->init_ok = 1;

    bt_init_ok_search_index();

#if TCFG_NORMAL_SET_DUT_MODE
    log_info("edr set dut mode");
    bredr_set_dut_enble(1, 1);
#if TCFG_USER_BLE_ENABLE
    log_info("ble set dut mode");
    ble_standard_dut_test_init();
    return;
#endif
#endif

#if (TCFG_USER_BLE_ENABLE || TCFG_BT_BLE_ADV_ENABLE)
    if (BT_MODE_IS(BT_BQB)) {
        ble_bqb_test_thread_init();
    } else if (BT_MODE_IS(BT_NORMAL)) {
#if TCFG_POWER_ON_ENABLE_BLE
        bt_ble_init();
#endif
    }
#endif

#if THIRD_PARTY_PROTOCOLS_SEL
    multi_protocol_bt_init();
#endif

#if ((TCFG_BT_MODE == BT_BQB)||(TCFG_BT_MODE == BT_PER))
    return;
#endif

#if TCFG_USER_TWS_ENABLE && (THIRD_PARTY_PROTOCOLS_SEL & MULTI_BOX_ADV_EN)
    syscfg_read(VM_MULTI_BOX_ROLE_INDEX, &__this->multi_box_role, sizeof(__this->multi_box_role));
#endif

#if TCFG_TWS_INIT_AFTER_POWERON_TONE_PLAY_END
    if (tone_player_runing()) {
        return;
    }
#endif
#if TCFG_USER_TWS_ENABLE
    bt_tws_poweron();
#endif
#if TCFG_LE_AUDIO_STREAM_ENABLE
    if (!__this->pair_enable) {
        syscfg_read(VM_LE_AUDIO_ONOFF_INDEX, &__this->le_audio_enable, sizeof(__this->le_audio_enable));
        if (__this->le_audio_enable) {
            __this->pair_enable = TRUE;
            le_audio_switch_onoff();
#if (THIRD_PARTY_PROTOCOLS_SEL & MULTI_BOX_ADV_EN)
            multi_box_in_bis_start_notify(__this->multi_box_role);
#endif
        }
    }
#endif
}

/*----------------------------------------------------------------------------*/
/**@brief    蓝牙获取在连接设备名字回调
   @param    status : 1：获取失败   0：获取成功
			 addr   : 配对设备地址
			 name   :配对设备名字
   @return
   @note     需要连接上设备后发起USER_CTRL_READ_REMOTE_NAME
   			 命令来
*/
/*----------------------------------------------------------------------------*/
static void bt_read_remote_name(u8 status, u8 *addr, u8 *name)
{
    if (status) {
        log_info("remote_name fail");
    } else {
        log_info("remote_name : %s", name);
    }
    put_buf(addr, 6);
}

/*----------------------------------------------------------------------------*/
/**@brief    蓝牙歌曲信息获取回调
   @param
   @return
   @note
   const u8 more_avctp_cmd_support = 1;置上1
   需要在void bredr_handle_register()注册回调函数
   要动态获取播放时间的，可以发送USER_CTRL_AVCTP_OPID_GET_PLAY_TIME命令就可以了
   要半秒或者1秒获取就做个定时发这个命令
*/
/*----------------------------------------------------------------------------*/

static void ms_to_time(u8 *info, u16 len)
{
    //毫秒转换成分:秒
    u32 time = 0;
    u16 cnt;
    for (cnt = 0; cnt < len; cnt ++) {
        time += (info[len - 1 - cnt] - '0') * pow(10, cnt);
    }
    log_info("music_time: %02d : %02d", time / 1000 / 60, (time % 60000) / 1000);
}

#ifdef CONFIG_UI_ENABLE
_WEAK_ void lv_example_lyrics_text_input(char *buf)
{
    return;
}

static void lv_example_lyrics_input_dynamic(char *buf)
{
    if (buf == NULL) {
        return;
    }
    extern void lv_example_lyrics_text_input(char *new_text);
    lv_example_lyrics_text_input(buf);

    free(buf);
}
#endif

static void user_get_bt_music_info(u8 type, u32 time, u8 *info, u16 len)
{
    //profile define type:
    //1-title 2-artist name 3-album names 4-track number
    //5-total number of tracks 6-genre  7-playing time
    //JL define 0x10-total time , 0x11 current play position
    u8 min, sec, ret;
    //printf("type %d\n", type );
    if ((info != NULL) && (len != 0) && (type != 7)) {
        if (type == 1) {
            char *title_buf = (char *)malloc(len + 1);
            if (!title_buf) {
                log_error("malloc failed for music info buffer");
                return;
            }
            memcpy(title_buf, info, len);
            title_buf[len] = '\0';
            log_info("title: %s", title_buf);
#ifdef CONFIG_UI_ENABLE
            ret = lvgl_rpc_post_func(lv_example_lyrics_input_dynamic, 1, title_buf);
            if (ret == -1) {
                log_info("lyrics post fail");
                free(title_buf);
            }
#endif
        } else if (type == 2) {
            log_info("artist: %s", info);
        } else if (type == 3) {
            log_info("album: %s", info);
#if TCFG_BT_SUPPORT_PROFILE_BIP == 1
            static u8 music_id_3[255] = {0};
            if (memcmp(music_id_3, info, len) != 0) {
                log_info("get image");
                bt_cmd_prepare(USER_CTRL_BIP_GET_IMAGE, 0, NULL);
            }
            memcpy(music_id_3, info, len);
#endif
        }
    }

    if (type == 7) {
        ms_to_time(info, len);
    }
    if (time != 0) {
        min = time / 1000 / 60;
        sec = time / 1000 - (min * 60);
        log_info("time %02d : %02d", min, sec);
    }
}

static void bt_music_player_time_deal(void *priv)
{
    if (BT_STATUS_PLAYING_MUSIC == bt_get_connect_status()) {
        bt_cmd_prepare(USER_CTRL_AVCTP_OPID_GET_PLAY_TIME, 0, NULL);
    }
}

//播歌时配置为1
static void bt_music_player_time_timer_deal(u8 en)
{
#if TCFG_BT_MUSIC_INFO_ENABLE
    if (en) {
        if (__this->get_music_player_timer == 0) {
            __this->get_music_player_timer = sys_timer_add(NULL, bt_music_player_time_deal, 800);
        }
    } else {
        if (__this->get_music_player_timer) {
            sys_timer_del(__this->get_music_player_timer);
            __this->get_music_player_timer = 0;
        }
    }
#endif
}

/*----------------------------------------------------------------------------*/
/**@brief    蓝牙spp 协议数据 回调
   @param    packet_type:数据类型
  			 ch         :区分spp链路的连接号
			 packet     :数据缓存
			size        ：数据长度
   @return
   @note
*/
/*----------------------------------------------------------------------------*/
static void spp_data_handler(u8 packet_type, u16 ch, u8 *packet, u16 size)
{
    switch (packet_type) {
    case 1:
        log_info("spp connect:%x", ch);
        break;
    case 2:
        log_info("spp disconnect:%x", ch);
        break;
    case 7:
        //puts("spp_rx:");
        //put_buf(packet,size);
#if AEC_DEBUG_ONLINE
        aec_debug_online(packet, size);
#endif

#if TCFG_USER_RSSI_TEST_EN
        int spp_get_rssi_handler(u8 * packet, u16 size);
        spp_get_rssi_handler(packet, size);
#endif
        break;
    }
}

/*----------------------------------------------------------------------------*/
/**@brief    蓝牙获取样机当前电量
   @param
   @return
   @note
*/
/*----------------------------------------------------------------------------*/
static int bt_get_battery_value(void)
{
    //取消默认蓝牙定时发送电量给手机，需要更新电量给手机使用USER_CTRL_HFP_CMD_UPDATE_BATTARY命令
    /*电量协议的是0-9个等级，请比例换算*/
    return get_cur_battery_level();
}

/*----------------------------------------------------------------------------*/
/**@brief  蓝牙event   搜索结束
   @param
   @return
   @note
*/
/*----------------------------------------------------------------------------*/
static void bt_hci_event_inquiry(struct bt_event *bt)
{
#if TCFG_USER_EMITTER_ENABLE
    if (__this->emitter_or_receiver == BT_EMITTER_EN) {
        //以后扩展，暂时注释
        //emitter_search_stop();
    }
#endif
}

/*----------------------------------------------------------------------------*/
/**@brief  蓝牙event链接断开,实际流程处理位于dual_conn.c中，此处预留做状态更新
   @param
   @return
   @note
*/
/*----------------------------------------------------------------------------*/
static void bt_hci_event_disconnect(struct bt_event *bt)
{

}

/*----------------------------------------------------------------------------*/
/**@brief  蓝牙event   链接超时
   @param
   @return
   @note    回链超时内没有连接上设备
*/
/*----------------------------------------------------------------------------*/
static void bt_hci_event_connection_timeout(struct bt_event *bt)
{

}

/*----------------------------------------------------------------------------*/
/**@brief  蓝牙event   获取sco状态
   @param
   @return
   @note
*/
/*----------------------------------------------------------------------------*/
static u8 bt_sco_state(void)
{
    return __this->phone_call_dec_begin;
}

/*----------------------------------------------------------------------------*/
/**@brief  蓝牙weak函数重新定义，蓝牙获取到的电话本信息反馈给用户层
   @param
   @return
   @note
*/
/*----------------------------------------------------------------------------*/
void bt_phonebook_packet_handler(u8 type, const u8 *name, const u8 *number, const u8 *date)
{
    static u16 number_cnt = 0;

    log_info("NO.%d:", number_cnt);
    number_cnt++;

    log_info("type:%d ", type);

    if (type == 0xff) {
        number_cnt = 0;
    }
    if (name) {
        log_info("name:%s", name);
    }
    if (number) {
        log_info("number:%s", number);
    }
    if (date) {
        log_info("date:%s", date);
    }
}

#if TCFG_BT_SUPPORT_PROFILE_MAP

#define    PROFILE_CMD_TRY_AGAIN_LATER      -1004

static void bt_get_time_date(void *p)
{
    int error = bt_cmd_prepare(USER_CTRL_HFP_GET_PHONE_DATE_TIME, 0, NULL);
    if (error == PROFILE_CMD_TRY_AGAIN_LATER) {
        sys_timeout_add(NULL, bt_get_time_date, 100);
    }
}

void phone_date_and_time_feedback(u8 *data, u16 len)
{
    log_info("time：%s", data);
}

void map_get_time_data(char *time, int status)
{
    if (status == 0) {
        log_info("time：%s", time);
    } else  {
        log_warn("map get fail");
        sys_timeout_add(NULL, bt_get_time_date, 100);
    }
}

#endif


static void bredr_handle_register(void)
{
#if TCFG_BT_SUPPORT_PROFILE_HID
#if TCFG_BT_PROFILE_HID_CHANGE_DESCRIPTOR
    void user_hid_descriptor_init(void);
    user_hid_descriptor_init();
#else
    void user_hid_init(void (*user_hid_output_handler)(u8 * packet, u16 size, u16 channel));
    user_hid_init(NULL);
#endif
#endif

#if TCFG_BT_SUPPORT_PROFILE_SPP
#if APP_ONLINE_DEBUG
    online_spp_init();
#endif
    bt_spp_data_deal_handle_register(spp_data_handler);
#endif

    bt_fast_test_handle_register(bt_fast_test_api);//测试盒快速测试接口

#if TCFG_BT_VOL_SYNC_ENABLE
    bt_music_vol_change_handle_register(bt_set_music_device_volume, bt_get_phone_device_vol);
#endif
#if TCFG_BT_DISPLAY_BAT_ENABLE
    bt_get_battery_percent_handle_register(bt_get_battery_value);   /*电量显示获取电量的接口*/
#endif

    //样机进入dut被测试仪器链接上回调
    bt_dut_test_handle_register(bt_dut_api);

    //获取远端设备蓝牙名字回调
    bt_read_remote_name_handle_register(bt_read_remote_name);

#if TCFG_BT_MUSIC_INFO_ENABLE
    //获取歌曲信息回调
    bt_music_info_handle_register(user_get_bt_music_info);
#endif
}

static void bt_function_select_init(void)
{
    /* set_bt_data_rate_acl_3mbs_mode(1); */
#if TCFG_BT_DUAL_CONN_ENABLE
    bt_set_user_ctrl_conn_num(2);
#else
    bt_set_user_ctrl_conn_num(1);
#endif
#if (defined(TCFG_BT_SUPPORT_MSBC) && TCFG_BT_SUPPORT_MSBC)
    bt_set_support_msbc_flag(TCFG_BT_SUPPORT_MSBC);
#endif

#if (defined(TCFG_BT_SUPPORT_AAC) && TCFG_BT_SUPPORT_AAC)
    bt_set_support_aac_flag(TCFG_BT_SUPPORT_AAC);
    bt_set_aac_bitrate(TCFG_BT_AAC_BITRATE);
#endif

#if (defined(TCFG_BT_SUPPORT_LHDC) && TCFG_BT_SUPPORT_LHDC)
    bt_set_support_lhdc_flag(TCFG_BT_SUPPORT_LHDC);
#endif

#if (defined(TCFG_BT_SUPPORT_LHDC_V5) && TCFG_BT_SUPPORT_LHDC_V5)
    bt_set_support_lhdc_v5_flag(TCFG_BT_SUPPORT_LHDC_V5);
#endif

#if (defined(TCFG_BT_SUPPORT_LDAC) && TCFG_BT_SUPPORT_LDAC)
    bt_set_support_ldac_flag(TCFG_BT_SUPPORT_LDAC);
#endif

#if TCFG_BT_DISPLAY_BAT_ENABLE
    bt_set_update_battery_time(60);
#else
    bt_set_update_battery_time(0);
#endif
    /*回连搜索时间长度设置,可使用该函数注册使用，ms单位,u16*/
    bt_set_page_timeout_value(0);

    /*回连时超时参数设置。ms单位。做主机有效*/
    bt_set_super_timeout_value(8000);

#if TCFG_BT_DUAL_CONN_ENABLE
    bt_set_auto_conn_device_num(2);
#endif

#if TCFG_BT_VOL_SYNC_ENABLE
    vol_sys_tab_init();
#endif
    /* io_capabilities
     * 0: Display only 1: Display YesNo 2: KeyboardOnly 3: NoInputNoOutput
     *  authentication_requirements: 0:not protect  1 :protect
    */
#if TCFG_BT_BQB_PROFILE_TEST_ENABLE
    bt_set_simple_pair_param(1, 0, 2);
#else
    bt_set_simple_pair_param(3, 0, 2);
#endif

#if 0
    /*测试盒连接获取参数需要的一些接口注册*/
    bt_testbox_ex_info_get_handle_register(TESTBOX_INFO_VBAT_VALUE, get_vbat_value);
    bt_testbox_ex_info_get_handle_register(TESTBOX_INFO_VBAT_PERCENT, get_vbat_percent);
    bt_testbox_ex_info_get_handle_register(TESTBOX_INFO_BURN_CODE, sdfile_get_burn_code);
    bt_testbox_ex_info_get_handle_register(TESTBOX_INFO_SDK_VERSION, bt_get_sdk_ver_info);
#endif

    bt_set_sbc_cap_bitpool(TCFG_BT_SBC_BITPOOL);

#if TCFG_USER_BLE_ENABLE
    u8 tmp_ble_addr[6];
#if TCFG_BT_BLE_BREDR_SAME_ADDR
    memcpy(tmp_ble_addr, (void *)bt_get_mac_addr(), 6);
#else
    bt_make_ble_address(tmp_ble_addr, (void *)bt_get_mac_addr());
#endif
    le_controller_set_mac((void *)tmp_ble_addr);
    log_info("-----edr + ble 's address-----");
    put_buf((void *)bt_get_mac_addr(), 6);
    put_buf((void *)tmp_ble_addr, 6);
#endif

#if (TCFG_BT_MODE != BT_NORMAL)
    set_bt_enhanced_power_control(1);
#endif

#if (TCFG_BT_SUPPORT_PROFILE_PBAP==1)
    ////设置蓝牙设备类型
    bt_change_hci_class_type(BD_CLASS_CAR_AUDIO);
#else
    bt_change_hci_class_type(BD_CLASS_LOUDSPEAKER);
#endif
}


#if TCFG_BT_SUPPORT_PROFILE_BIP == 1

/*************************************************************************/
//			avrcp传输音乐图片
/*************************************************************************/
//配置
#define BIP_FILE_NAME               "album.jpg"
#define BIP_FILE_PATH               CONFIG_ROOT_PATH\
                                    BIP_FILE_NAME

enum {
    BIP_DATA_STATUS_START = 0X01,   //开始包
    BIP_DATA_STATUS_CONTINUE,       //继续包(中间包)
    BIP_DATA_STATUS_STOP,           //结束包
    BIP_DATA_STATUS_ERR,            //错误包，可能是不支持，或者音乐软件未打开
    BIP_DATA_STATUS_ERR_GET,        //重复获取
    BIP_DATA_STATUS_GET_NULL,       //上一个获取中，获取无图片歌曲
};

enum {
    BIP_FILE_STATUS_ERR,            //文件不存在
    BIP_FILE_STATUS_OK,             //文件存在
    BIP_FILE_STATUS_UPDATE,         //文件更新中
};

struct bip_file_info {
    FILE *fp;                       //文件句柄
    volatile u8 file_status;        //文件状态
};

static struct bip_file_info bip_file;
#define __bip_info (&bip_file)

const char *bip_file_path_get(void)
{
    return BIP_FILE_PATH;
}

const char *bip_file_name_get(void)
{
    return BIP_FILE_NAME;
}

u8 bip_file_status_get(void)
{
    return __bip_info->file_status;
}

/* ------------------------------------------------------------------------------------*/
/**
 * @brief bip_rx_data_handle	音乐图片数据回调
 *
 * @param packet	数据包内容
 * @param body_len	数据包长度
 * @param length	整个图片大小,只有ios支持在第一包返回
 * @param bip_data_status	数据状态
 */
/* ------------------------------------------------------------------------------------*/
void bip_rx_data_handle(u8 *packet, u16 body_len, u32 length, u8 bip_data_status)
{
    /* log_info("<%s>status:%d", __func__, bip_data_status); */

    switch (bip_data_status) {
    case BIP_DATA_STATUS_START: //收到第一包数据
        log_info("BIP_DATA_STATUS_START");
        const char *bit_file_path = bip_file_path_get();
        log_info("bip_file_path: %s", bit_file_path);
        //删除旧文件
        __bip_info->fp = fopen(bit_file_path, "r");
        if (__bip_info->fp) {
            /* __bip_info->file_status = BIP_FILE_STATUS_ERR; */
            fdelete(__bip_info->fp);
            __bip_info->fp = NULL;
        }
        //新增文件
        __bip_info->fp = fopen(bit_file_path, "w+");
        if (__bip_info->fp) {
            __bip_info->file_status = BIP_FILE_STATUS_UPDATE;
            fwrite(packet, body_len, 1, __bip_info->fp);
        } else {
            log_error("bip file open err");
        }
        break;
    case BIP_DATA_STATUS_CONTINUE: //收到文件数据
        if (__bip_info->fp) {
            fwrite(packet, body_len, 1, __bip_info->fp);
        }
        break;
    case BIP_DATA_STATUS_STOP: //收到结束命令
        log_info("BIP_DATA_STATUS_STOP");
        if (__bip_info->fp) {
            fwrite(packet, body_len, 1, __bip_info->fp);
            fclose(__bip_info->fp);
            __bip_info->fp = NULL;
            __bip_info->file_status = BIP_FILE_STATUS_OK;
        }
        break;
    case BIP_DATA_STATUS_ERR:
        log_info("BIP_DATA_STATUS_ERR");
        break;
    default:
        break;
    }
}

#endif
