#ifndef __UI_ACTION_SONG_INFO_H_
#define __UI_ACTION_SONG_INFO_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "lvgl.h"

void music_player_song_info_lyrics_clean(void);
void sys_menu_song_info_lyrics_clean(void);
void sys_menu_song_info_update(char *song_info);
void music_player_song_info_update(char *song_name, char *song_artist);

#ifdef __cplusplus
}
#endif

#endif /* __UI_ACTION_SONG_INFO_H_ */