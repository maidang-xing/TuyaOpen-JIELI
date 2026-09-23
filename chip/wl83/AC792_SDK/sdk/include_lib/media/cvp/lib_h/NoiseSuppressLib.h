#ifndef NoiseSuppressLib_H
#define NoiseSuppressLib_H
#define NOISESP_CONFIG_FREEZE 0
#define NOISESP_CONFIG_NOISEFLOOR 1
#define NOISESP_CONFIG_LOWCUTTHR 2
#define NOISESP_CONFIG_MINSUPPRESS 3
#define NOISESP_CONFIG_AGGRESSFACTOR 4
#define NOISESP_CONFIG_GETESTIMATEDNOISE 5
#define NOISESP_CONFIG_SETNOISE 6
#define NOISESP_CONFIGV3_SETENGTHR 7
#define NOISESP_CONFIGV3_SETINDBTHR 8
#define NOISESP_CONFIGV3_SETENGDB 9
#define NOISESP_CONFIGV3_SETENGFREQ 10
#define NOISESP_CONFIG_SETOUTWIDTH 11
#define NOISESP_CONFIG_USEDYNGAIN 12

struct SEMode_FadeInOut_Config {
    float fs;
    float Release_Time;     // ms
    float Attack_Time;      // ms
    float Release_HoldTime; // ms
    float Attack_HoldTime;  // ms
};

#ifdef __cplusplus
extern "C"
{
#endif
//======================= Original version interface of ANS ======================//
int NoiseSuppress_QueryProcessDelay(int mode, int is_wideband);
int NoiseSuppress_QueryBufSize(int mode, int is_wideband);
int NoiseSuppress_QueryTempBufSize(int mode, int is_wideband);
void NoiseSuppress_Init(void *NoiseSpRunBuffer,
                        float AggressFactor,
                        float minSuppress,
                        int mode,
                        int is_wideband,
                        float noise_lvl);
void NoiseSuppress_Process(void *NoiseSpRunBuffer,
                           void *NoiseSpTempBuffer,
                           short *input,
                           void *output,
                           short *inputH,
                           void *outputH,
                           int npoint);
void NoiseSuppress_Config(void *NoiseSpRunBuffer,
                          int ConfigType,
                          void *ConfigPara);
//======================= Lightweight version interface of ANS ======================//
int NoiseSuppress_SE_QueryBufSize(int mode, int is_wideband);
int NoiseSuppress_SE_QueryTempBufSize(int mode, int is_wideband);
void NoiseSuppress_SE_Init(void *NoiseSpRunBuffer,
                           float AggressFactor,
                           float minSuppress,
                           int mode,
                           int is_wideband,
                           float noise_lvl);
void NoiseSuppress_SE_Process(void *NoiseSpRunBuffer,
                              void *NoiseSpTempBuffer,
                              short *input,
                              void *output,
                              short *inputH,
                              void *outputH,
                              int npoint);
void NoiseSuppress_SE_Config(void *NoiseSpRunBuffer,
                             int ConfigType,
                             void *ConfigPara);
//======================= Common version interface of ANS ======================//
int NoiseSuppress_GetMiniFrame(int is_wideband);

#ifdef __cplusplus
}
#endif
#endif
