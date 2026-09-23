#ifndef __NET_STREAM_INFO_H
#define __NET_STREAM_INFO_H

#include "stdint.h"


struct net_stream_info {
    int sample_rate;
    int abr_kbps;
    int fps;
};


#endif /* __NET_STREAM_INFO_H */

