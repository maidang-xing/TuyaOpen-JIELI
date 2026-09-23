#ifndef VIR_AUDIO_RECODER_H
#define VIR_AUDIO_RECODER_H

#include "system/includes.h"
#include "audio_def.h"


void *vir_audio_recoder_open(u16 sample_rate, u32 code_type, void *priv, void (*cb)(void *, u8 *, u32));
int vir_audio_recoder_close(void *priv);

#endif // VIR_AUDIO_RECODER_H

