#ifndef _LOCAL_TWS_H_
#define _LOCAL_TWS_H_

#include "app_msg.h"

enum {
    LOCAL_TWS_ROLE_NULL,
    LOCAL_TWS_ROLE_SOURCE,
    LOCAL_TWS_ROLE_SINK,
};

enum {
    CMD_TWS_OPEN_LOCAL_DEC_REQ = 0x1,
    CMD_TWS_OPEN_LOCAL_DEC_RSP,
    CMD_TWS_CLOSE_LOCAL_DEC_REQ,
    CMD_TWS_CLOSE_LOCAL_DEC_RSP,
    CMD_TWS_ENTER_SINK_MODE_REQ,
    CMD_TWS_ENTER_SINK_MODE_RSP,
    CMD_TWS_BACK_TO_BT_MODE_REQ,
    CMD_TWS_BACK_TO_BT_MODE_RSP,
    CMD_TWS_CONNECT_MODE_REPORT,
    CMD_TWS_PLAYER_STATUS_REPORT,
    CMD_TWS_ENTER_NO_SOURCE_MODE_REPORT,
    CMD_TWS_VOL_UP,
    CMD_TWS_VOL_DOWN,
    CMD_TWS_VOL_REPORT,
    CMD_TWS_MUSIC_PP,
    CMD_TWS_MUSIC_NEXT,
    CMD_TWS_MUSIC_PREV,
};

struct local_tws_mode_ops {
    app_mode_t mode;
    const char *name;
    void (*audio_open)(void *priv);
    bool (*get_play_status)(void);
};

#define REGISTER_LOCAL_TWS_OPS(local_tws_ops) \
    static const struct local_tws_mode_ops __##local_tws_ops SEC_USED(.local_tws)

extern struct local_tws_mode_ops local_tws_ops_begin[];
extern struct local_tws_mode_ops local_tws_ops_end[];

#define list_for_each_local_tws_ops(ops) \
    for (ops = local_tws_ops_begin; ops < local_tws_ops_end; ops++)

int local_tws_enter_mode(const char *file_name, app_mode_t mode, void *priv);
void local_tws_exit_mode(void);
void local_tws_connect_mode_report(void);
void local_tws_disconnect_deal(void);
void local_tws_enter_sink_mode_rsp(app_mode_t mode);
void local_tws_close_dec_rsp(void);
u8 local_tws_get_remote_dec_status(void);
void local_tws_vol_operate(u8 operate);
void local_tws_music_operate(u8 operate, void *arg);
void local_tws_sync_vol(void);
u8 local_tws_get_role(void);

#endif

