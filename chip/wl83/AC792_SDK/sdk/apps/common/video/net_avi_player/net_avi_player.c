#include "audio_def.h"
#include "avi_parse.h"
#include "curl_get_data.h"
#include "net_avi_player.h"

#define NET_BUFFER_SIZE  (512 * 1024)       //HTTP读取缓冲区大小
#define AUDIO_BUFFER_SIZE (256 * 1024)      //音频帧缓队列大小
#define VIDEO_BUFFER_SIZE (512 * 1024)      //视频帧缓队列大小
#define IDX1_CACHE_SIZE   (64 * 1024)        //AVI索引缓存大小,用于SEEK跳转，如果不使用跳转功能，可以不缓存索引.
#define IDX1_ENTRY_SIZE   16

enum {
    AVI_PLAYER_EVENT_SEEK = 0x100,
};


struct idx1_map_entry {
    struct list_head entry;
    u32 data_offset;
    u32 data_len;
    u32 frame_start;
    u32 frame_end;
};

struct net_avi_player {
    void *net_session;
    struct avi_player *player;
    struct avi_frame_queue frame_queue;
    struct avi_parser_result avi_parser_result;
    struct avi_info avi_info;

    int get_data_task_pid;
    int get_data_task_exit;
    int seek_request;
    char get_data_task_name[32];

    u32 read_offset;

    u8 *idx1_cache;
    u32 idx1_cache_size;
    u32 idx1_cache_valid;
    u32 idx1_cache_video_start;
    u32 idx1_cache_video_end;
    u32 idx1_data_offset;
    u32 idx1_size;
    u32 idx1_entries;
    u8 idx1_ready;

    struct list_head idx1_map;
    u32 idx1_map_cnt;
};

static void avi_get_data_task(void *priv);
static int queue_init(struct avi_frame_queue *frame_queue, int video_buf_size, int audio_buf_size);
static void queue_deinit(struct avi_frame_queue *frame_queue);
static void queue_clear(struct avi_frame_queue *frame_queue);
static int net_avi_prepare_idx1(struct net_avi_player *net_player);
static int net_avi_find_seek_offset(struct net_avi_player *net_player, u32 target_frame, u32 *out_offset);
static int net_avi_find_seek_offset_in_cache(struct net_avi_player *net_player, u32 target_frame, u32 *out_offset);
static int net_avi_calc_chunk_file_offset(struct net_avi_player *net_player, u32 chunk_offset, u32 *out_offset);
static int do_seek(struct net_avi_player *net_player, u32 target_ms);
static inline u32 read_le32_local(const u8 *buf);
static void idx1_map_clear(struct net_avi_player *net_player);
static void idx1_map_add(struct net_avi_player *net_player, u32 data_offset, u32 data_len,
                         u32 frame_start, u32 frame_end);
static int idx1_map_find(struct net_avi_player *net_player, u32 target_frame,
                         u32 *data_offset, u32 *video_frame);


void *net_avi_play_start(const char *url, avi_player_event_callback_t event_callback, void *event_priv)
{
    int ret;
    struct net_avi_player *net_player = malloc(sizeof(struct net_avi_player));
    if (!net_player) {
        printf("malloc net_player fail\n");
        return NULL;
    }
    memset(net_player, 0, sizeof(struct net_avi_player));

    INIT_LIST_HEAD(&net_player->idx1_map);

    net_player->net_session = curl_session_create(url);
    if (!net_player->net_session) {
        printf("curl_session_create fail\n");
        goto exit;
    }
    ret = curl_session_init(net_player->net_session);
    if (ret != 0) {
        printf("curl_session_init fail %d\n", ret);
        goto exit;
    }

    // 解析AVI头部
    if (net_avi_parse_header(net_player) != 0) {
        printf("net_avi_parse_header fail\n");
        goto exit;
    }
    avi_parser_result_dump(&net_player->avi_parser_result);

    if (!net_player->avi_parser_result.has_audio && !net_player->avi_parser_result.has_video) {
        printf("no audio and video stream\n");
        goto exit;
    }
    // 转换为avi_info
    net_player->avi_info.width = net_player->avi_parser_result.width;
    net_player->avi_info.height = net_player->avi_parser_result.height;
    net_player->avi_info.fps = net_player->avi_parser_result.fps;
    net_player->avi_info.audio_coding_type = AUDIO_CODING_PCM;
    net_player->avi_info.audio_channels = net_player->avi_parser_result.audio_channels;
    net_player->avi_info.audio_sample_rate = net_player->avi_parser_result.audio_sample_rate;
    net_player->avi_info.has_audio = net_player->avi_parser_result.has_audio;
    net_player->avi_info.has_video = net_player->avi_parser_result.has_video;
    net_player->avi_info.total_time_ms = (net_player->avi_parser_result.total_frames * 1000) / net_player->avi_info.fps;

    net_player->read_offset = net_player->avi_parser_result.movi_offset;

    int video_buf_size = VIDEO_BUFFER_SIZE;
    int audio_buf_size = AUDIO_BUFFER_SIZE;
    ret = queue_init(&net_player->frame_queue, video_buf_size, audio_buf_size);
    if (ret != 0) {
        printf("queue_init fail %d\n", ret);
        goto exit;
    }

    net_player->player = avi_player_init(&net_player->avi_info,
                                         &net_player->frame_queue, event_callback, event_priv);
    if (!net_player->player) {
        printf("avi_player_init fail\n");
        goto exit;
    }

    snprintf(net_player->get_data_task_name, sizeof(net_player->get_data_task_name), "task_%d", net_player->player);

    ret = thread_fork(net_player->get_data_task_name, 20, 2048, 2048,
                      &net_player->get_data_task_pid,
                      avi_get_data_task, net_player);
    if (ret != 0) {
        printf("get_avi_data_task thread fork fail %d\n", ret);
        goto exit;
    }


    return net_player;

exit:
    net_avi_play_stop(net_player);
    return NULL;
}

int net_avi_play_get_info(void *_net_player, struct avi_info *info)
{
    if (!_net_player || !info) {
        return -1;
    }
    struct net_avi_player *net_player = (struct net_avi_player *)_net_player;
    if (net_player->player) {
        memcpy(info, &net_player->avi_info, sizeof(struct avi_info));
        return 0;
    }
    return -1;
}

int net_avi_play_get_total_time_ms(void *_net_player)
{
    if (!_net_player) {
        return 0;
    }

    struct net_avi_player *net_player = (struct net_avi_player *)_net_player;
    if (net_player->player) {
        u32 total_frames = net_player->avi_parser_result.total_frames;
        int fps = net_player->avi_info.fps;
        if (fps > 0) {
            return (total_frames * 1000) / fps;
        }
    }

    return 0;
}

int net_avi_play_pause_resume(void *_net_player, int pause)
{
    if (!_net_player) {
        return -1;
    }
    struct net_avi_player *net_player = (struct net_avi_player *)_net_player;
    if (net_player->player) {
        avi_player_control(net_player->player, pause ? AVI_PLAYER_CMD_PAUSE : AVI_PLAYER_CMD_PLAY, 0);
    }
    return 0;
}

int net_avi_play_seek(void *_net_player, u32 target_ms)
{
    int msg[8];
    int ret = 0;
    if (!_net_player) {
        printf("net_avi_play_seek net_player is NULL\n");
        return -1;
    }

    //暂停播放，等待seek完成后再恢复播放
    net_avi_play_pause_resume(_net_player, 1);

    struct net_avi_player *net_player = (struct net_avi_player *)_net_player;
    if (!net_player->get_data_task_pid) {
        printf("data task not running \n");
        return -1;
    }

    net_player->seek_request = 1;

    msg[0] = AVI_PLAYER_EVENT_SEEK;
    msg[1] = target_ms;
    ret = os_taskq_post_type(net_player->get_data_task_name, Q_MSG, ARRAY_SIZE(msg), msg);
    if (ret != 0) {
        printf("avi seek taskqpost fail %d\n", ret);
        net_avi_play_pause_resume(_net_player, 0);
        return -1;
    }
    return 0;
}

void net_avi_play_stop(void *_net_player)
{
    if (!_net_player) {
        return;
    }
    struct net_avi_player *net_player = (struct net_avi_player *)_net_player;

    if (net_player->get_data_task_pid) {
        net_player->get_data_task_exit = 1;
        thread_kill(&net_player->get_data_task_pid, KILL_WAIT);
        net_player->get_data_task_exit = 0;
    }

    if (net_player->player) {
        avi_player_exit(net_player->player);
    }
    if (net_player->net_session) {
        curl_session_destroy(net_player->net_session);
    }
    queue_deinit(&net_player->frame_queue);
    idx1_map_clear(net_player);
    if (net_player->idx1_cache) {
        free(net_player->idx1_cache);
        net_player->idx1_cache = NULL;
    }
    free(net_player);
}

static void avi_get_data_task(void *priv)
{
    struct net_avi_player *net_player = (struct net_avi_player *)priv;
    printf("avi video play task started\n");
    char index_chunk_id[5] = {'i', 'd', 'x', '1', '\0'};
    int msg[8];
    int buffer_size = NET_BUFFER_SIZE;
    u8 *buffer = malloc(buffer_size);
    if (!buffer) {
        printf("avi video play task malloc buffer fail\n");
        return;
    }
    u32 buffer_offset = 0;

    //从指定offset开始读取数据
    u32 offset = net_player->read_offset;
    printf("start read from offset=%d\n", offset);

    if (curl_session_seek(net_player->net_session, offset) != 0) {
        printf("curl_session_seek fail\n");
        free(buffer);
        return;
    }

    while (!net_player->get_data_task_exit) {

        if (os_taskq_accept(ARRAY_SIZE(msg), msg) == OS_TASKQ) {
            if (msg[0] == Q_MSG) {
                switch (msg[1]) {
                case AVI_PLAYER_EVENT_SEEK:
                    int target_ms = msg[2];
                    if (do_seek(net_player, target_ms) != 0) {
                        printf("net avi seek fail\n");
                        break;
                    }

                    //seek后从新offset开始读取数据
                    offset = net_player->read_offset;
                    if (curl_session_seek(net_player->net_session, offset) != 0) {
                        printf("curl_session_seek fail\n");
                    }
                    buffer_offset = 0;
                    break;
                default:
                    break;
                }
            }
        }

        if (net_player->seek_request) {
            os_time_dly(1);
            continue;
        }

        u32 received = 0;
        int ret = curl_session_read(net_player->net_session,
                                    buffer + buffer_offset, buffer_size - buffer_offset, &received);
        if (ret != 0 || received == 0) {
            printf("curl_session_read_at fail %d\n", ret);
            break;
        }
        received += buffer_offset;

        //解析数据
        u32 processed = 0;
        while (processed + 8 < received) {
            //printf("processed=%d, received=%d\n", processed, received);
            if (net_player->seek_request) {
                break;
            }

            char *video_chunk_id = net_player->avi_parser_result.video_chunk_id;
            char *audio_chunk_id = net_player->avi_parser_result.audio_chunk_id;
            u32 chunk_id;
            u32 chunk_size;
            memcpy(&chunk_id, buffer + processed, 4);
            memcpy(&chunk_size, buffer + processed + 4, 4);

            //printf("chunk_id=0x%08x, chunk_size=%d\n", chunk_id, chunk_size);

            if (chunk_id == *(u32 *)video_chunk_id) {
                //printf("video chunk_id:%s , chunk_size=%d\n", video_chunk_id, chunk_size);
                //视频帧
                u32 total_size = 8 + chunk_size;
                if (processed + total_size <= received) {
                    //完整帧
                    struct avi_frame_lbuf_node *video_node = NULL;
                    while (!video_node && !net_player->get_data_task_exit && !net_player->seek_request) {
                        video_node = lbuf_alloc(net_player->frame_queue.video_lbuf_handle, chunk_size);
                        if (!video_node) {
                            os_time_dly(2);
                        }
                    }
                    if (video_node) {
                        video_node->len = chunk_size;
                        memcpy(video_node->data, buffer + processed + 8, chunk_size);
                        lbuf_push(video_node, BIT(0));
                        processed += total_size;
                    }
                } else {
                    //不完整帧，等待下次读取
                    break;
                }
            } else if (chunk_id == *(u32 *)audio_chunk_id) {
                //printf("audio chunk_id:%s , chunk_size=%d\n", audio_chunk_id, chunk_size);
                //音频数据
                u32 total_size = 8 + chunk_size;
                if (processed + total_size <= received) {
                    //完整音频数据
                    struct avi_frame_lbuf_node *audio_node = NULL;
                    while (!audio_node && !net_player->get_data_task_exit && !net_player->seek_request) {
                        audio_node = lbuf_alloc(net_player->frame_queue.audio_lbuf_handle, chunk_size);
                        if (!audio_node) {
                            os_time_dly(2);
                        }
                    }
                    if (audio_node) {
                        audio_node->len = chunk_size;
                        memcpy(audio_node->data, buffer + processed + 8, chunk_size);
                        lbuf_push(audio_node, BIT(0));
                        processed += total_size;
                    }
                } else {
                    //不完整数据，等待下次读取
                    break;
                }
            } else if (chunk_id == *(u32 *)index_chunk_id) {
                printf("index chunk_id:%s , chunk_size=%d\n", index_chunk_id, chunk_size);
                //退出
                net_player->get_data_task_exit = 1;
                break;
            } else {
                //printf("unknown chunk_id=0x%08x , chunk_size=%d\n", chunk_id, chunk_size);
                //未知chunk，跳过
                processed++;
            }

        }
        //未处理完的数据，移动到buffer起始位置
        if (processed < received) {
            //printf("move remain data, processed=%d, received=%d\n", processed, received);
            u32 remain = received - processed;
            memmove(buffer, buffer + processed, remain);
            buffer_offset = remain;
        } else {
            //printf("all data processed\n");
            buffer_offset = 0;
        }

    }
    if (buffer) {
        free(buffer);
    }
    printf("avi video play task exiting\n");
}

static int do_seek(struct net_avi_player *net_player, u32 target_ms)
{
    int err = 0;

    if (net_avi_prepare_idx1(net_player) != 0) {
        printf("net_avi_play_seek: prepare idx1 fail\n");
        err = -1;
        goto __exit;
    }

    u32 total_frames = net_player->avi_parser_result.total_frames;
    u32 target_frame = (target_ms * net_player->avi_info.fps) / 1000;
    if (total_frames > 0 && target_frame >= total_frames) {
        target_frame = total_frames - 1;
    }

    printf("seek to target_ms=%d ms, target_frame=%d\n", target_ms, target_frame);

    u32 target_offset = 0;
    if (net_avi_find_seek_offset_in_cache(net_player, target_frame, &target_offset) != 0) {
        if (net_avi_find_seek_offset(net_player, target_frame, &target_offset) != 0) {
            printf("net_avi_play_seek: find offset fail\n");
            err = -1;
            goto __exit;
        }
    }

    queue_clear(&net_player->frame_queue);

    net_player->read_offset = target_offset;
    avi_player_control(net_player->player, AVI_PLAYER_CMD_SEEK, target_ms);

__exit:
    net_player->seek_request = 0;
    net_avi_play_pause_resume(net_player, 0);
    return err;
}

static int net_avi_parse_header(struct net_avi_player *net_player)
{
    int ret = 0;
    u8 *head_buf;
    u32 head_buf_size;
    struct avi_parser_result result;

    head_buf_size = 64 * 1024;
    head_buf = malloc(head_buf_size);
    if (!head_buf) {
        printf("malloc head_buf fail\n");
        return -1;
    }

    u32 received;
    ret = curl_session_read_at(net_player->net_session, 0, head_buf, head_buf_size, &received);
    if (ret != 0) {
        printf("curl_session_read_at fail %d\n", ret);
        free(head_buf);
        return -1;
    }

    ret = avi_parse_header(head_buf, received, &result);
    if (ret != 0) {
        printf("avi_parse_header fail %d\n", ret);
        free(head_buf);
        return -1;
    }

    free(head_buf);

    memcpy(&net_player->avi_parser_result, &result, sizeof(struct avi_parser_result));

    return 0;
}

static int net_avi_prepare_idx1(struct net_avi_player *net_player)
{
    if (!net_player) {
        return -1;
    }
    if (net_player->idx1_ready) {
        return 0;
    }

    u32 idx1_chunk_offset = 0;
    if (net_player->avi_parser_result.idx1_offset) {
        idx1_chunk_offset = net_player->avi_parser_result.idx1_offset - 8;
    } else {
        idx1_chunk_offset = avi_calc_idx1_offset(&net_player->avi_parser_result);
    }
    if (idx1_chunk_offset == 0) {
        return -1;
    }

    if (net_player->avi_parser_result.idx1_size) {
        net_player->idx1_size = net_player->avi_parser_result.idx1_size;
    } else {
        u8 head[8];
        u32 received = 0;
        if (curl_session_read_at(net_player->net_session, idx1_chunk_offset, head, sizeof(head), &received) != 0 || received < sizeof(head)) {
            return -1;
        }
        if (memcmp(head, "idx1", 4) != 0) {
            printf("net_avi_prepare_idx1: idx1 header not found\n");
            return -1;
        }
        net_player->idx1_size = read_le32_local(head + 4);
    }

    if (net_player->idx1_size < IDX1_ENTRY_SIZE) {
        return -1;
    }

    net_player->idx1_data_offset = idx1_chunk_offset + 8;
    net_player->idx1_entries = net_player->idx1_size / IDX1_ENTRY_SIZE;
    idx1_map_clear(net_player);
    INIT_LIST_HEAD(&net_player->idx1_map);

    if (!net_player->idx1_cache) {
        u32 cache_size = IDX1_CACHE_SIZE;
        if (cache_size > net_player->idx1_size) {
            cache_size = net_player->idx1_size;
        }
        cache_size = (cache_size / IDX1_ENTRY_SIZE) * IDX1_ENTRY_SIZE;
        if (cache_size < IDX1_ENTRY_SIZE) {
            cache_size = IDX1_ENTRY_SIZE;
        }
        net_player->idx1_cache = malloc(cache_size);
        if (!net_player->idx1_cache) {
            return -1;
        }
        net_player->idx1_cache_size = cache_size;
    }

    net_player->idx1_ready = 1;
    return 0;
}

static int net_avi_find_seek_offset_in_cache(struct net_avi_player *net_player, u32 target_frame, u32 *out_offset)
{
    if (!net_player || !out_offset || !net_player->idx1_cache_valid) {
        return -1;
    }

    if (target_frame < net_player->idx1_cache_video_start || target_frame > net_player->idx1_cache_video_end) {
        return -1;
    }

    u32 video_frame = net_player->idx1_cache_video_start;
    const u8 *buf = net_player->idx1_cache;
    u32 len = (net_player->idx1_cache_valid / IDX1_ENTRY_SIZE) * IDX1_ENTRY_SIZE;
    for (u32 pos = 0; pos < len; pos += IDX1_ENTRY_SIZE) {
        const u8 *entry = buf + pos;
        if (memcmp(entry, net_player->avi_parser_result.video_chunk_id, 4) == 0) {
            u32 chunk_offset = read_le32_local(entry + 8);
            if (video_frame == target_frame) {
                return net_avi_calc_chunk_file_offset(net_player, chunk_offset, out_offset);
            }
            video_frame++;
        }
    }
    return -1;
}

static int net_avi_find_seek_offset(struct net_avi_player *net_player, u32 target_frame, u32 *out_offset)
{
    if (!net_player || !out_offset) {
        return -1;
    }

    u32 idx1_size = net_player->idx1_size;
    u32 idx1_offset = net_player->idx1_data_offset;
    u32 cache_size = net_player->idx1_cache_size;
    if (cache_size < IDX1_ENTRY_SIZE) {
        return -1;
    }

    u32 scan_offset = 0;
    u32 video_frame = 0;

    u32 map_offset = 0;
    if (idx1_map_find(net_player, target_frame, &map_offset, &video_frame) == 0) {
        scan_offset = map_offset - net_player->idx1_data_offset;
        if (scan_offset >= idx1_size) {
            printf("idx1 map offset invalid, scan_offset=%d\n", scan_offset);
            return -1;
        }
        printf("idx1 map hit: scan_offset=%d, video_frame=%d\n", scan_offset, video_frame);
    }


    while (scan_offset < idx1_size) {
        u32 read_len = idx1_size - scan_offset;
        if (read_len > cache_size) {
            read_len = cache_size;
        }
        read_len = (read_len / IDX1_ENTRY_SIZE) * IDX1_ENTRY_SIZE;
        if (read_len == 0) {
            printf("read_len is 0\n");
            break;
        }

        u32 received = 0;
        if (curl_session_read_at(net_player->net_session, idx1_offset + scan_offset,
                                 net_player->idx1_cache, read_len, &received) != 0 || received == 0) {
            printf("curl_session_read_at fail when read idx1, offset=%d, len=%d\n", idx1_offset + scan_offset, read_len);
            return -1;
        }

        received = (received / IDX1_ENTRY_SIZE) * IDX1_ENTRY_SIZE;
        if (received == 0) {
            return -1;
        }
        //printf("read idx1 chunk, offset=%d, len=%d\n", idx1_offset + scan_offset, received);

        u32 start_frame = video_frame;
        u32 target_chunk_offset = 0;
        for (u32 pos = 0; pos < received; pos += IDX1_ENTRY_SIZE) {
            const u8 *entry = net_player->idx1_cache + pos;
            if (memcmp(entry, net_player->avi_parser_result.video_chunk_id, 4) == 0) {
                u32 chunk_offset = read_le32_local(entry + 8);
                video_frame++;
                if (video_frame == target_frame) {
                    target_chunk_offset = chunk_offset;
                }
            }
        }

        idx1_map_add(net_player, idx1_offset + scan_offset, received,
                     start_frame + 1, video_frame);

        net_player->idx1_cache_valid = received;
        net_player->idx1_cache_video_start = start_frame;
        net_player->idx1_cache_video_end = video_frame;

        scan_offset += received;

        if (target_chunk_offset) {
            printf("find target frame in idx1 cache, target_frame=%d, target_chunk_offset=%d\n", target_frame, target_chunk_offset);
            return net_avi_calc_chunk_file_offset(net_player, target_chunk_offset, out_offset);
        }
    }

    printf("seek offset not found in idx1\n");
    return -1;
}

static int net_avi_calc_chunk_file_offset(struct net_avi_player *net_player, u32 chunk_offset, u32 *out_offset)
{
    if (!net_player || !out_offset) {
        return -1;
    }

    u32 base_candidates[3] = {0};
    u32 movi_offset = net_player->avi_parser_result.movi_offset;
    base_candidates[0] = movi_offset;
    if (movi_offset >= 4) {
        base_candidates[1] = movi_offset - 4;
    }
    if (movi_offset >= 12) {
        base_candidates[2] = movi_offset - 12;
    }

    for (int i = 0; i < 3; i++) {
        u32 base = base_candidates[i];
        if (base == 0) {
            continue;
        }
        u32 file_offset = base + chunk_offset;
        u8 idbuf[4];
        u32 received = 0;
        if (curl_session_read_at(net_player->net_session, file_offset, idbuf, sizeof(idbuf), &received) == 0 && received == sizeof(idbuf)) {
            if (memcmp(idbuf, net_player->avi_parser_result.video_chunk_id, 4) == 0 ||
                memcmp(idbuf, net_player->avi_parser_result.audio_chunk_id, 4) == 0) {
                *out_offset = file_offset;
                return 0;
            }
        }
    }

    *out_offset = movi_offset + chunk_offset;
    return 0;
}


static int queue_init(struct avi_frame_queue *frame_queue, int video_buf_size, int audio_buf_size)
{
    frame_queue->video_buf_size = video_buf_size;
    frame_queue->video_buf_ptr = malloc(frame_queue->video_buf_size);
    if (!frame_queue->video_buf_ptr) {
        printf("video_buf_ptr malloc fail\n");
        return -1;
    }
    frame_queue->audio_buf_size = audio_buf_size;
    frame_queue->audio_buf_ptr = malloc(frame_queue->audio_buf_size);
    if (!frame_queue->audio_buf_ptr) {
        printf("audio_buf_ptr malloc fail\n");
        free(frame_queue->video_buf_ptr);
        return -1;
    }

    frame_queue->video_lbuf_handle = lbuf_init(frame_queue->video_buf_ptr,
                                     frame_queue->video_buf_size,
                                     8, sizeof(struct avi_frame_lbuf_node));
    if (!frame_queue->video_lbuf_handle) {
        printf("avi video lbuf handle init err \n");
        return -1;
    }

    frame_queue->audio_lbuf_handle = lbuf_init(frame_queue->audio_buf_ptr,
                                     frame_queue->audio_buf_size,
                                     8, sizeof(struct avi_frame_lbuf_node));
    if (!frame_queue->audio_lbuf_handle) {
        printf("avi audio lbuf handle init err \n");
        return -1;
    }

    return 0;
}

static void queue_deinit(struct avi_frame_queue *frame_queue)
{
    if (frame_queue->video_lbuf_handle) {
        free(frame_queue->video_buf_ptr);
        frame_queue->video_lbuf_handle = NULL;
    }
    if (frame_queue->audio_lbuf_handle) {
        free(frame_queue->audio_buf_ptr);
        frame_queue->audio_lbuf_handle = NULL;
    }
}

static void queue_clear(struct avi_frame_queue *frame_queue)
{
    if (frame_queue->video_lbuf_handle) {

        while (1) {
            struct avi_frame_lbuf_node *node = lbuf_pop(frame_queue->video_lbuf_handle, BIT(0));
            if (!node) {
                break;
            }
            lbuf_free(node);
        }
    }
    if (frame_queue->audio_lbuf_handle) {
        while (1) {
            struct avi_frame_lbuf_node *node = lbuf_pop(frame_queue->audio_lbuf_handle, BIT(0));
            if (!node) {
                break;
            }
            lbuf_free(node);
        }
    }
}

static inline u32 read_le32_local(const u8 *buf)
{
    return buf[0] | (buf[1] << 8) | (buf[2] << 16) | (buf[3] << 24);
}

static void idx1_map_clear(struct net_avi_player *net_player)
{
    if (!net_player) {
        return;
    }

    struct idx1_map_entry *entry, *tmp;
    list_for_each_entry_safe(entry, tmp, &net_player->idx1_map, entry) {
        list_del(&entry->entry);
        free(entry);
    }
    net_player->idx1_map_cnt = 0;
}

static void idx1_map_add(struct net_avi_player *net_player, u32 data_offset, u32 data_len,
                         u32 frame_start, u32 frame_end)
{
    if (!net_player || frame_end < frame_start) {
        return;
    }

    if (net_player->idx1_map_cnt > 0) {
        struct idx1_map_entry *last = NULL;
        list_for_each_entry(last, &net_player->idx1_map, entry) {
            if (last && last->data_offset == data_offset && last->data_len == data_len) {
                return;
            }
        }
    }

    struct idx1_map_entry *entry = malloc(sizeof(*entry));
    if (!entry) {
        printf("malloc idx1_map_entry fail\n");
        return;
    }

    entry->data_offset = data_offset;
    entry->data_len = data_len;
    entry->frame_start = frame_start;
    entry->frame_end = frame_end;
    list_add_tail(&entry->entry, &net_player->idx1_map);
    net_player->idx1_map_cnt++;
}

static int idx1_map_find(struct net_avi_player *net_player, u32 target_frame,
                         u32 *data_offset, u32 *video_frame)
{
    if (!net_player || !data_offset || !video_frame) {
        return -1;
    }

    struct idx1_map_entry *entry;
    list_for_each_entry(entry, &net_player->idx1_map, entry) {
        if (target_frame >= entry->frame_start && target_frame <= entry->frame_end) {
            *data_offset = entry->data_offset;
            *video_frame = entry->frame_start - 1;
            return 0;
        }
    }

    return -1;
}



