#ifndef CTP_CLIENT_H
#define CTP_CLIENT_H

#include "system/includes.h"

int ctp_client_init(void **client_hdl, u32 ip_addr, void *priv);
void ctp_client_exit(void *client_hdl);
int ctp_client_send_sync(void *client_hdl, const char *topic, const char *content, int timeout_ms);
int ctp_client_send_async(void *client_hdl, const char *topic, const char *content);



#endif // CTP_CLIENT_H

