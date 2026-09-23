#ifdef SUPPORT_MS_EXTENSIONS
#pragma bss_seg(".recp_gaming_headset.data.bss")
#pragma data_seg(".recp_gaming_headset.data")
#pragma const_seg(".recp_gaming_headset.text.const")
#pragma code_seg(".recp_gaming_headset.text")
#endif
#include "system/includes.h"
#include "app_config.h"
#include "app_msg.h"
#include "btstack_rcsp_user.h"
#include "rcsp.h"
#include "rcsp_config.h"
#include "rcsp/JL_rcsp_protocol.h"
#include "JL_rcsp_attr.h"
#include "rcsp_over_online_cfg_tool.h"
/* #include "app_protocol_common.h" */
#include "os/os_api.h"
#include "cfg_tool.h"

#define RCSP_DEBUG_EN
#ifdef  RCSP_DEBUG_EN
#define rcsp_putchar(x)                	putchar(x)
#define rcsp_printf                    	printf
#define rcsp_put_buf(x,len)				put_buf(x,len)
#else
#define rcsp_putchar(...)
#define rcsp_printf(...)
#define rcsp_put_buf(...)
#endif

#if RCSP_MODE && RCSP_ADV_OVER_ONLINE_CFG_TOOL

struct rcsp_over_online_cfg_tool_meta_t {
    struct RcspModel *rcspModel;
    u16 ble_con_handle;
    u8 spp_remote_addr[6];
    u8 OpCode;
    u8 OpCode_SN;
};
static struct rcsp_over_online_cfg_tool_meta_t g_over_cfg_tool_info;


int JL_rcsp_over_online_cfg_tool_response(u8 *buf, u32 len)
{
    int ret = 0;
    if (g_over_cfg_tool_info.rcspModel == NULL) {
        return -1;
    }
    int err = JL_CMD_response_send(g_over_cfg_tool_info.OpCode,
                                   JL_PRO_STATUS_SUCCESS,
                                   g_over_cfg_tool_info.OpCode_SN,
                                   buf,
                                   len,
                                   g_over_cfg_tool_info.ble_con_handle,
                                   g_over_cfg_tool_info.spp_remote_addr);
    if (err != JL_ERR_NONE) {
        ret = -1;
    }
    return ret;
}

int JL_rcsp_over_online_cfg_tool_cmd_receive(void *priv, u8 OpCode, u8 OpCode_SN, u8 *data, u16 len, u16 ble_con_handle, u8 *spp_remote_addr)
{
    struct RcspModel *rcspModel = (struct RcspModel *)priv;
    u32 param_len;
    u8 *param;
    u32 resp_len;
    u8 *resp_buf;
    int err;
    int ret = 0;
    u8 action;
    u8 type;
    u32 mask32;

#define check_resp_alloc(resp_buf) \
    if (resp_buf == NULL) { \
        /*ASSERT(resp_buf, "malloc fail\n");*/ \
        ret = JL_PRO_STATUS_FAIL; \
        goto __err_exit; \
    }

    if (rcspModel == NULL) {
        return JL_PRO_STATUS_FAIL;
    }

    g_over_cfg_tool_info.rcspModel = rcspModel;
    g_over_cfg_tool_info.ble_con_handle = ble_con_handle;
    if (spp_remote_addr) {
        memcpy(g_over_cfg_tool_info.spp_remote_addr, spp_remote_addr, 6);
    }
    g_over_cfg_tool_info.OpCode = OpCode;
    g_over_cfg_tool_info.OpCode_SN = OpCode_SN;

    switch (OpCode) {
    case JL_OPCODE_OVER_ONLINE_CFG_TOOL_CMD:
        rcsp_printf("JL_OPCODE_OVER_ONLINE_CFG_TOOL_CMD");
        param = data;
        param_len = len;
        /* put_buf(param, param_len); */
        err = online_cfg_tool_data_deal(param, param_len);
        if (err) {
            JL_CMD_response_send(OpCode, JL_PRO_STATUS_FAIL, OpCode_SN, NULL, 0, ble_con_handle, spp_remote_addr);
        }
        break;
    default:
        ret = JL_PRO_STATUS_UNKOWN_CMD;
        break;
    }
    return ret;

__err_exit:
    return ret;
}

void JL_rcsp_over_online_cfg_tool_init()
{
    rcsp_printf("%s()", __func__);
    memset(&g_over_cfg_tool_info, 0, sizeof(g_over_cfg_tool_info));
}

void JL_rcsp_over_online_cfg_tool_deinit()
{
    rcsp_printf("%s()", __func__);

}


#endif
