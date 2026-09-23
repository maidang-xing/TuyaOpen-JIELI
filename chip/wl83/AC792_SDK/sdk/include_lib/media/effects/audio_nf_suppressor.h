#ifndef __AUDIO_NF_SUPPRESSOR_H__
#define __AUDIO_NF_SUPPRESSOR_H__
#include "jlsp_ng.h"

struct noisefloor_param_tool_set {
    int is_bypass;
    int fft_size;    //该参数不支持在线调试
    float add_sub_db;
};

struct noisefloor_open_parm {
    ng_params_t parm;
    int sample_rate;
    u16 fft_pts;
    u8 ch_num;
    u8 bit_width;
    u8 bypass;
};

struct noisefloor_hdl {
    struct noisefloor_open_parm nf_parm;
    void *noisefloor;   //操作句柄
    char *private_buffer;
    char *shared_buffer;
    u8 *left_buf;
    u8 *right_buf;
    u16 frame_size;   //处理的每包数据长度，单位points
    u8 update;
    u8 status;
};

//打开
struct noisefloor_hdl *audio_noisefloor_open(struct noisefloor_open_parm *param);

//关闭
void audio_noisefloor_close(struct noisefloor_hdl *hdl);

//参数更新
void audio_noisefloor_update_parm(struct noisefloor_hdl *hdl, float add_sub_db);

//数据处理
int audio_noisefloor_run(struct noisefloor_hdl *hdl, void *in, void *out, int len);

//暂停处理
void audio_noisefloor_bypass(struct noisefloor_hdl *hdl, u8 bypass);

#endif
