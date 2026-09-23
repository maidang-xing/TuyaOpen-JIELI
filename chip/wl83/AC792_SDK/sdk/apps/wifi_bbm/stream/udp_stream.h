#ifndef UDP_STREAM_H
#define UDP_STREAM_H

#include <stdint.h>

struct net_stream_info {
    int sample_rate;
    int abr_kbps;
    int fps;
};

int net_rt_vpkg_open(const char *path, struct net_stream_info *s_info);
int net_rt_vpkg_close(void);
int net_rt_send_frame(char *buffer, size_t len, u8 type);


#endif // UDP_STREAM_H

