#ifndef __RCSP_OVER_ONLINE_CFG_TOOL__
#define __RCSP_OVER_ONLINE_CFG_TOOL__

#include "typedef.h"
#include "generic/list.h"


void JL_rcsp_over_online_cfg_tool_init();
void JL_rcsp_over_online_cfg_tool_deinit();
int JL_rcsp_over_online_cfg_tool_cmd_receive(void *priv, u8 OpCode, u8 OpCode_SN, u8 *data, u16 len, u16 ble_con_handle, u8 *spp_remote_addr);
int JL_rcsp_over_online_cfg_tool_response(u8 *buf, u32 len);

#endif
