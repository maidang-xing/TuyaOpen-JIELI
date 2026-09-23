#ifndef  __RNDIS_H__
#define  __RNDIS_H__

#include "lte_module.h"

/* 目前调试过的4G模组列表 */
// 移远模组：EG800K-CN, EC800K-CN, EC801E-CN,
//           EC800M-CN, EC800G-CN, EC800E-CN
// 中移模组：ML307C, ML307A
// 其他模组：SLM332, LYNL511CN, YM310, TC10E,
//           CTL103-CE, HQ308, P102WU, P102H,NT26

typedef struct {
    s32(*init)(struct lte_module_data *);
    void (*dev_in)(int id);
    void (*dev_out)(void);
    void (*get_mac)(u8 *mac);
    void *(*get_txaddr)(void);
    void (*tx_packet)(u16 length);
    s32(*get_rxpkt_addr_len)(struct lte_module_pkg *lte_module_pkg);
    void (*release_current_rxpkt)(void);
} rndis_interface_type;

void get_rndis_ops(const rndis_interface_type **ops);

#endif  /*PHY_STATE_H*/


