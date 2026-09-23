#ifndef AUIO_PLAYER_H
#define AUIO_PLAYER_H

#include "system/includes.h"

int audio_player_one_frame(u8 *buf, u32 size);
int audio_player_init(void);
int audio_player_exit(void);


#endif // AUIO_PLAYER_H

