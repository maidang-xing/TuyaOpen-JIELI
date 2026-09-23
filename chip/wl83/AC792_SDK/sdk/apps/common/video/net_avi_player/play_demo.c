#include "net_avi_player.h"


static void *net_player = NULL;

static void event_callback(int event, int arg, void *priv)
{
    switch (event) {
    case AVI_PLAYER_EVENT_CURRENT_TIME_MS:
        printf("AVI_PLAYER_EVENT_CURRENT_TIME_MS: %d ms\n", arg);
        break;
    case AVI_PLAYER_EVENT_END:
        printf("AVI_PLAYER_EVENT_END\n");
        break;
    default:
        break;
    }
}


int net_avi_player_test(const char *url)
{
    if (!url) {
        return -1;
    }

    net_player = net_avi_play_start(url, event_callback, NULL);
    if (!net_player) {
        printf("net_avi_play_start fail \n");
        return -1;
    }

    // 控制暂停/播放
    // net_avi_play_pause_resume(net_player, 0);

    //跳转
    /* u32 target_ms = 10 * 1000; //跳转到第10s */
    /* net_avi_play_seek(net_player, target_ms); */

    return 0;
}
