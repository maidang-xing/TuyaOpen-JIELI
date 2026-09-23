#ifndef __CDP_CLIENT_H
#define __CDP_CLIENT_H

#include "system/includes.h"


void *cdp_cli_reg(u32 ip_addr, void *priv);
void cdp_cli_unreg(void *hdl);
int cdp_client_send_async(void *hdl, const char *topic, const char *content);
int cdp_client_send_sync(void *hdl, const char *topic, const char *content, int timeout_ms);


#endif /* __CDP_CLIENT_H */

