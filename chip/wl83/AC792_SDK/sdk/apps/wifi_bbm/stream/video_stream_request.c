#include "cdp_client.h"
#include "json_c/json.h"
#include "json_c/json_tokener.h"
#include "video_stream_request.h"

#define LOG_TAG_CONST       VIDEO_STREAM_REQUEST
#define LOG_TAG             "[VIDEO_STREAM_REQUEST]"
#define LOG_ERROR_ENABLE
#define LOG_INFO_ENABLE
#define LOG_DUMP_ENABLE
#include "debug.h"

int video_stream_open_request(void *cdp_client_hdl, struct video_stream_info *stream, int device_num)
{
    int err = 0;
    void *client_hdl = cdp_client_hdl;
    char *topic = "OPEN_VIDEO_CALL";
    char *content = malloc(1024);
    int timeout_ms = 3 * 1000;

    if (!cdp_client_hdl || !stream || !content) {
        log_error("cdp ptr or video stream ptr or content ptr null \n");
        return -1;
    }

    snprintf(content, 1024,
             "{\"op\":\"PUT\",\"param\":{\"img_width\":%d,\"img_height\":%d,\"fps\":%d,"
             "\"bitrate_kbps\":%d,\"online\":%d,\"device_id\":%d,\"osd_enable\":%d,"
             "\"audio_enable\":%d,\"sample_rate\":%d,\"channel\":%d,\"volume\":%d,"
             "\"aud_interval_size\":%d,\"device_num\":%d}}",
             stream->img_width,
             stream->img_height,
             stream->fps,
             stream->bitrate_kbps,
             stream->online,
             stream->device_id,
             stream->osd_enable,
             stream->audio_enable,
             stream->sample_rate,
             stream->channel,
             stream->volume,
             stream->aud_interval_size,
             device_num
            );
    log_debug("request content:%s \n", content);

    err = cdp_client_send_sync(client_hdl, topic, content, timeout_ms);
    if (err != 0) {
        log_error("cdp client send open video stream err \n");
        return -1;
    }

    return 0;
}

