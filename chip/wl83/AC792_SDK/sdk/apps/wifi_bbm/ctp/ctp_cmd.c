#include "server/ctp_server.h"
#include "server/net_server.h"
#include "json_c/json.h"
#include "json_c/json_tokener.h"
#include "server/server_core.h"
#include "system/app_core.h"
#include "action.h"
#include "app_config.h"
#include "fs/fs.h"
#include "http/http_server.h"
#include "ctp.h"
#include "cdp.h"
#include "os/os_api.h"
#include "action.h"
#include "video_stream_common.h"


#define CTP_CMD_HEADER "{\"errno\":%d,\"op\":\"%s\",\"param\":{"
#define CTP_CMD_HEADER_WITHOUT_ERR "{\"op\":\"%s\",\"param\":{"
#define CTP_CMD_END "}}"
#define CTP_ERR_MESSAGE "{\"errno\":%d}"

static struct ctp_arg info;

static int send_ctp_string(int cmd_type, char *buf, const char *_req, void *priv)
{
    struct ctp_req req;
    struct server *ctp = NULL;

    ctp = get_ctp_server_hander();
    if (ctp == NULL) {
        return -1;
    }

    req.parm = buf;
    req.topic = _req;
    req.cli = priv;
    if (!priv) {
        req.cli = info.cli;
    }
    printf("buf:%s ", buf);
    if (server_request(ctp, cmd_type, (void *)&req)) {
        return -1;
    }

    return 0;
}

static inline int _CTP_CMD_COMBINED(int cmd_type, void *priv, u32 err, const char *_req, const char *mothod, char *str)
{
    char *buf = NULL;
    int ret;
    int id = 0;
    char tmp[64];
    char *tmp1 = NULL;
    buf = (char *)malloc(512);

    if (buf == NULL) {
        printf("%s %d mem is fail \n", __func__, __LINE__);
        return -1;
    }

    if (err) {
        ret = snprintf(buf, 512, CTP_CMD_HEADER, err, mothod);
    } else {
        ret = snprintf(buf, 512, CTP_CMD_HEADER_WITHOUT_ERR, mothod);
    }

    char *key;
    char *value;

    if (!err && str != NULL) {
        while (1) {
            key = strtok_r(str, ":", &tmp1); //这函数会改数组，不能用const
            value = strtok_r(NULL, ",", &tmp1);

            if (key == NULL || value == NULL) {
                break;
            }

            ret = sprintf(tmp, "\"%s\":\"%s\",", key, value);
            tmp[ret] = '\0';
            ret = snprintf(buf, 512, "%s%s", buf, tmp);
            str = NULL;
        }

        buf[ret - 1] = '\0';//主要是去掉最后的逗号
        ret = snprintf(buf, 512, "%s%s", buf, CTP_CMD_END);
    } else {
        snprintf(buf, 512, "{\"op\":\"NOTIFY\",\"errno\":%d,\"param\":{%s}}", err, str);
    }

    void *cli = NULL;
    if (!strcmp(_req, info.topic) || !priv) {
        cli = info.cli;
    } else {
        cli = priv;
    }


    if (send_ctp_string(cmd_type, buf, _req, cli) < 0) {
        free(buf);
        return -1;
    }
    return 0;
}

static int CTP_CMD_COMBINED(void *priv, u32 err, const char *_req, const char *mothod, char *str)
{
    return _CTP_CMD_COMBINED(CTP_NOTIFY_COMMAND, priv, err, _req, mothod, str);
}

static void __all_get_cmd_run(void *priv, char *content)
{
    const struct ctp_map_entry *map = NULL;
    list_for_ctp_mapping_tab(map) {
        if (map->get != NULL) {
            map->get(priv, content);    //执行map中所有get命令
        }
    }
}

int ctp_cmd_analysis(const char *topic, char *content, void *priv)
{
    struct ctp_map_entry *map = NULL;
    char buf[128];
    struct intent it;
    int ret = -1;

    if (strlen(topic) <= 0 || strlen(content) <= 0) {
        printf("%s  %d err....\n", __func__, __LINE__);
        return -1;
    }

    strcpy(info.topic, topic);
    info.content = NULL;
    info.cli = priv;

    list_for_ctp_mapping_tab(map) {
        if (!strcmp(topic, map->ctp_command)) {
            if (strstr(content, "PUT") && map->put != NULL) {
                if (map->sync != true) {
                    map->sync = true;  //防止APP多次发送重发命令
                    ret =  map->put(priv, content);
                } else {
                    printf("Warnning CTP<%s> is doing now\n", map->ctp_command);
                    ret = 0;
                }
            } else if (strstr(content, "GET") && map->get != NULL) {
                if (map->sync != true) {
                    map->sync = true;
                    ret = map->get(priv, content);
                } else {
                    printf("Warnning CTP<%s> is doing now\n", map->ctp_command);
                    ret = 0;
                }
            } else {
                puts("content is error \n\n");
            }

        }

        if (ret != -1) {
            return ret;
        }
    }

    CTP_CMD_COMBINED(priv, CTP_NO_TOPIC, topic, "NOTIFY", CTP_NO_TOPIC_MSG);
    printf("%s %d topic:%s not find it or cb is NULL\n", __func__, __LINE__, topic);
    return -1;

}

static void get_video_stream_info(struct video_stream_info *stream_info, json_object *param_obj)
{
    stream_info->img_width = json_object_get_int(json_object_object_get(param_obj, "img_width"));
    stream_info->img_height = json_object_get_int(json_object_object_get(param_obj, "img_height"));
    stream_info->fps = json_object_get_int(json_object_object_get(param_obj, "fps"));
    stream_info->bitrate_kbps = json_object_get_int(json_object_object_get(param_obj, "bitrate_kbps"));
    stream_info->online = json_object_get_int(json_object_object_get(param_obj, "online"));
    stream_info->device_id = json_object_get_int(json_object_object_get(param_obj, "device_id"));
    stream_info->osd_enable = json_object_get_int(json_object_object_get(param_obj, "osd_enable"));
    stream_info->audio_enable = json_object_get_int(json_object_object_get(param_obj, "audio_enable"));
    stream_info->sample_rate = json_object_get_int(json_object_object_get(param_obj, "sample_rate"));
    stream_info->channel = json_object_get_int(json_object_object_get(param_obj, "channel"));
    stream_info->volume = json_object_get_int(json_object_object_get(param_obj, "volume"));
    stream_info->aud_interval_size = json_object_get_int(json_object_object_get(param_obj, "aud_interval_size"));
}


static int cmd_put_open_video_call(void *priv, char *content)
{
    int ret, status;
    char buf[64];
    struct video_stream_info stream_info = {0};
    struct intent it;
    init_intent(&it);

    json_object *obj = json_tokener_parse(content);
    if (!obj) {
        printf("json_tokener_parse err \n");
        return -1;
    }
    json_object *param_obj = json_object_object_get(obj, "param");
    if (!param_obj) {
        printf("json_object_object_get param err \n");
        json_object_put(obj);
        return -1;
    }
    get_video_stream_info(&stream_info, param_obj);
    int device_num = json_object_get_int(json_object_object_get(param_obj, "device_num"));
    json_object_put(obj);

    it.name	= "video_call";
    it.data = (void *)&stream_info;
    it.exdata = device_num;
    it.action = ACTION_VIDEO_CALL_OPEN_STREAM;
    ret = start_app(&it);
    if (ret != 0) {
        status = 0;
    } else {
        status = 1;
    }

    snprintf(buf, sizeof(buf), "status:%d", status);
    CTP_CMD_COMBINED(NULL, CTP_NO_ERR, "OPEN_VIDEO_CALL", "NOTIFY", buf);
    return 0;
}

static int cmd_put_close_video_call(void *priv, char *content)
{
    int ret, status;
    char buf[64];

    struct intent it;
    init_intent(&it);
    it.action = ACTION_VIDEO_CALL_CLOSE_STREAM;
    ret = start_app(&it);
    if (ret != 0) {
        status = 0;
    } else {
        status = 1;
    }


    snprintf(buf, sizeof(buf), "status:%d", status);
    CTP_CMD_COMBINED(NULL, CTP_NO_ERR, "CLOSE_VIDEO_CALL", "NOTIFY", buf);

    return 0;
}


const struct ctp_map_entry ctp_video_cmd_tab[] SEC_USED(.ctp_video_cmd) = {
    {NULL, "OPEN_VIDEO_CALL", NULL, cmd_put_open_video_call},
    {NULL, "CLOSE_VIDEO_CALL", NULL, cmd_put_close_video_call},
};


