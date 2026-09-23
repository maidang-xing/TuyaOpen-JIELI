
#ifndef WIFI_ADAPTER_H_
#define WIFI_ADAPTER_H_

#ifdef __cplusplus
extern "C" {
#endif

#define DROP_CRC_ERR   BIT(0) //drop CRC error frame
#define DROP_PHY_ERR   BIT(1) //drop physical error frame
#define DROP_UC_NOME   BIT(2) //drop not to me unicast frame
#define DROP_NOT_MYBSS BIT(3) //drop frame that is not my BSSID
#define DROP_VER_ERR   BIT(4) //drop 802.11 version error frame
#define DROP_DROP_MC   BIT(5) //drop multicast frame
#define DROP_BC        BIT(6) //drop broadcast frame
#define DROP_DUPL      BIT(7) //drop duplicated frame
#define DROP_CFACK     BIT(8) //drop CF-END + CF-ACK
#define DROP_CFEND     BIT(9) //drop CF-END
#define DROP_ACK       BIT(10) //drop ACK
#define DROP_CTS       BIT(11) //drop CTS
#define DROP_RTS       BIT(12) //drop RTS
#define DROP_PSPOLL    BIT(13) //drop PS-POLL
#define DROP_BA        BIT(14) //drop BA
#define DROP_BAR       BIT(15) //drop BAR
#define DROP_CTRL_RSV  BIT(16) //drop reserve control subtype

//复位对应的接收过滤包类型
void wf_rx_filt_set(unsigned int reg);
//设置对应的接收过滤包类型
void wf_rx_filt_reset(unsigned int reg);
//设置硬件MAC_BSSID寄存器 ,需要在wifi_raw_on后调用
void wf_asic_set_bssid(unsigned char *bssid);
//设置本机硬件MAC, 需要在wifi_raw_on后调用
void wf_asic_set_mac(unsigned char *mac);
//使能channel power检测,需要在wifi_raw_on后调用
void wf_channel_power_detect_enable(void);
//获取当前channel power
char get_current_channel_power(void);


#ifdef __cplusplus
}
#endif

#endif
