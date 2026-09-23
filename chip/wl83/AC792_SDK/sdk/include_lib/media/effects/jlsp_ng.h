#ifndef __JLSP_NG_H__
#define __JLSP_NG_H__

typedef struct {
    const float *ng_arr_T;
    float add_sub_db;
} ng_params_t;

//fft_pts: 256 or 512
//ch: 1 or 2
void *JLSP_ng_init(char *private_buffer, int private_size, char *shared_buffer, int share_size, int samplerate, int fft_pts, int ch);
int JLSP_ng_get_heap_size(int *private_size, int *shared_size, int samplerate, int fft_pts, int ch);
int JLSP_ng_reset(void *m);
void JLSP_ng_update_shared_buffer(void *m, char *shared_buffer);
int JLSP_ng_process(void *m, void *input1, void *input2, void *output1, void *output2, int *outsize);
int JLSP_ng_free(void *m);
int JLSP_ng_set_th(void *m, ng_params_t *p);

#endif

