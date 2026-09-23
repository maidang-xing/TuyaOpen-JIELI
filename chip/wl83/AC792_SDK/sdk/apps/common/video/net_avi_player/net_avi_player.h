#ifndef NET_AVI_PLAYER_H
#define NET_AVI_PLAYER_H

#include "system/includes.h"
#include "avi_player.h"

void *net_avi_play_start(const char *url, avi_player_event_callback_t event_callback, void *event_priv);
void net_avi_play_stop(void *_net_player);
int net_avi_play_pause_resume(void *_net_player, int pause);
int net_avi_play_get_info(void *_net_player, struct avi_info *info);
int net_avi_play_get_total_time_ms(void *_net_player);
int net_avi_play_seek(void *_net_player, u32 target_ms);

#endif /* NET_AVI_PLAYER_H */

