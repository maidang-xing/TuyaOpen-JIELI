#include "device/device.h"
#include "os/os_api.h"
#include "generic/lbuf.h"
#include "spinlock.h"

#include "pipeline_core.h"
#include "message_event.h"
#include "pipeline_plugin.h"
#include "pipeline_hash.h"
#include "video_ioctl.h"
#include "video.h"
/* #include "jl_sharpen.h" */
#include "app_config.h"

#include "fs/fs.h"
#define LOG_TAG_CONST       SHARPEN_ADAPTER
#define LOG_TAG             "[SHARPEN_ADAPTER]"
#define LOG_ERROR_ENABLE
#define LOG_INFO_ENABLE
#define LOG_DUMP_ENABLE
#include "debug.h"

#define QQ 5874

#define SHARPEN_MAX_CHANNEL  1

struct sharpen_handle {
    u8 channel;
    int source_channel;
    u8 ref;
    u8 state;
    spinlock_t lock;
    struct list_head info_head;

    u8  input_format;
    u16 input_width;
    u16 input_height;

    u8  output_format;
    u16 output_width;
    u16 output_height;
    u16 line;
    u8  task_kill;
    int  pid;
    OS_SEM task_sem;
};

static struct sharpen_handle *g_sharpen_used[SHARPEN_MAX_CHANNEL];

static int sharpen_data_done(pipe_plugin_t *plugin)
{
    struct sharpen_handle *hdl = plugin->private_data;
    buffer_t *buffer = port_get_output_endpoint(plugin->port, 0)->data_buffer;
    buffer_meta_t *buffer_meta = buffer->meta_addr;
    buffer_meta_t buf_meta = {0};

    if (!plugin->on_event) {
        return -1;
    }

    buf_meta.meta.vmeta.width = hdl->output_width;
    buf_meta.meta.vmeta.height = hdl->output_height;
    buf_meta.meta.vmeta.format = hdl->output_format;
    buf_meta.meta.vmeta.line = hdl->line;
    buf_meta.data_len = buffer_meta->data_len;


    if (buffer->type == GENERAL_BUFFER || buffer->type == FAST_BUFFER) {
        buf_meta.ext_data = buffer_get_memory_address(buffer);
    } else if (buffer->type == QUEUE_BUFFER) {
        buf_meta.ext_data = buffer_meta->data;
    } else if (buffer->type == EXTERN_BUFFER) {
        buf_meta.ext_data = buffer_meta->ext_data;
    } else {
        return -1;
    }

    plugin->on_event(plugin->name, EVENT_DATA_DONE, &buf_meta);

    return 0;
}


static void sharpen_recv_task(void *arg)
{
    u8 i = 0;
    u32 start_time = 0;
    u32 end_time = 0;
    u32 len = 0;

    pipe_plugin_t *plugin = (pipe_plugin_t *)arg;

    struct sharpen_handle *hdl = (struct sharpen_handle *)plugin->private_data;
    //目前只考虑单端点的情况
    //
    buffer_t *buffer_in = port_get_input_endpoint(plugin->port, 0)->data_buffer;
    buffer_t *buffer_out = port_get_output_endpoint(plugin->port, 0)->data_buffer;

    buffer_meta_t *buffer_meta_in = NULL;
    buffer_meta_t *buffer_meta_out = NULL;

    if (buffer_check_vaild(buffer_in) == false && buffer_check_vaild(buffer_out) == false) {
        ASSERT(0, "sharpen buffer in and out memory isn't ok. Please malloc firstly.\r\n");
        return ;
    }

    while (1) {
        if (hdl->task_kill) {
            /* log_info("sharpen task exit.\r\n"); */
            break;
        }

        if (!buffer_meta_in) {
            printf("buffer_in->read_data:%p", buffer_in->read_data);
            buffer_meta_in = buffer_in->read_data(buffer_in, 0);
            if (!buffer_meta_in) {
                os_sem_set(&hdl->task_sem, 0);
                /* log_error("sharpen buffer in memory read_data null!\n"); */
                continue;
            }
        }

        do {
            if (hdl->state != PLUGIN_RUNNING) {
                break;
            }

            buffer_meta_out = buffer_out->get_write_addr(buffer_out, len);
            if (!buffer_meta_out) {
                /* log_warn("next moudle buffer no enough. free_len: %d, need_len: %d", buffer_out->get_free_size(buffer_out), len); */
                continue;
            }
            printf("---%s---%s---%d addr = %x\n\r", __FILE__, __func__, __LINE__, buffer_meta_in->data);
//            put_buf(buffer_meta_in->data, 1024);
//            invalidate_button_area()
            printf("(((((((((((((((((((((((((((((((((((((((((((((");
            memcpy(buffer_meta_out->ext_data + hdl->output_width * hdl->output_height, buffer_meta_in->data + hdl->output_width * hdl->output_height, hdl->output_width * hdl->output_height);
            //加入处理代码
            /* JLSharpen(buffer_meta_in->data, buffer_meta_out->ext_data, hdl->output_width, hdl->output_height); */

            buffer_meta_out->meta.vmeta.width = hdl->output_width;
            buffer_meta_out->meta.vmeta.height = hdl->output_height;
            buffer_meta_out->meta.vmeta.line = hdl->line;
            buffer_meta_out->pts = timer_get_ms();
            buffer_meta_out->data_len = len;
            buffer_meta_out->dts = buffer_meta_out->pts;

            //on_event
            buffer_out->meta_addr = buffer_meta_out;
            sharpen_data_done(plugin);

            buffer_out->update_data(buffer_out, buffer_meta_out);
        } while (0);
    }

}

static int sharpen_set_sink_info(pipe_plugin_t *plugin, int source_channel)
{
    struct sharpen_handle *hdl = (struct sharpen_handle *)plugin->private_data;

    if (hdl->source_channel == source_channel && hdl->state == PLUGIN_RUNNING) {
        return 0;
    }

    pipe_common_t info = {0};
    info.channel = source_channel;
    message_request(plugin->port, GET_DATA_INFO | MESSAGE_NEXT, &info);

    struct info_handle *info_hdl = NULL;
    list_for_each_entry(info_hdl, &hdl->info_head, entry) {
        if (info_hdl->channel == source_channel) {
            //以next plugin的src为准
            info_hdl->dst_format = info.format;
            info_hdl->dst_width = info.width;
            info_hdl->dst_height = info.height;
            info_hdl->dst_fps = info.fps;

#if 0
            log_debug("-- %s ==> src ch : %d", plugin->ops->name, info_hdl->channel);
            log_debug("-- size : %d x %d --> %d x %d", info_hdl->src_width, info_hdl->src_height, info_hdl->dst_width, info_hdl->dst_height);
            log_debug("-- fps : %d --> %d", info_hdl->src_fps, info_hdl->dst_fps);
            log_debug("-- format : %s --> %s", video_format_str(info_hdl->src_format), video_format_str(info_hdl->dst_format));
#endif

            //set last info
            if ((hdl->source_channel == (u8) - 1) || (hdl->source_channel == source_channel && info_hdl->src_width != info_hdl->dst_width)) {
                hdl->input_format = info_hdl->src_format;
                hdl->input_width = info_hdl->src_width;
                hdl->input_height = info_hdl->src_height;

                hdl->output_width = info_hdl->dst_width;
                hdl->output_height = info_hdl->dst_height;
                hdl->output_format = info_hdl->dst_format;

                hdl->source_channel = info_hdl->channel;
            }
            break;
        }
    }
    ASSERT(hdl->output_width && hdl->output_height, "[%s]: please check sink plugin. ", plugin->ops->name);

    return 0;
}


static int sharpen_debug_info(pipe_plugin_t *plugin, int source_channel)
{
    struct sharpen_handle *hdl = (struct sharpen_handle *)plugin->private_data;

    struct info_handle *info_hdl = NULL;
    list_for_each_entry(info_hdl, &hdl->info_head, entry) {
        if (info_hdl->channel == source_channel) {
            /* log_debug("-- %s ==> src ch : %d", plugin->ops->name, info_hdl->channel); */
            /* log_debug("-- size : %d x %d --> %d x %d", info_hdl->src_width, info_hdl->src_height, info_hdl->dst_width, info_hdl->dst_height); */
            /* log_debug("-- fps : %d --> %d", info_hdl->src_fps, info_hdl->dst_fps); */
            /* log_debug("-- format : %s --> %s", video_format_str(info_hdl->src_format), video_format_str(info_hdl->dst_format)); */
            break;
        }
    }
    return 0;
}

static int sharpen_prepare(pipe_plugin_t *plugin, int source_channel)
{
    ASSERT(plugin);
    struct sharpen_handle *hdl = (struct sharpen_handle *)plugin->private_data;
    ASSERT(hdl);
    sharpen_set_sink_info(plugin, source_channel);
    sharpen_debug_info(plugin, source_channel);

    if (hdl->state != PLUGIN_INITED) {
        /* log_info("%s %s skipped. cur state: %s\r\n", plugin->name, __func__, plugin_state_str(hdl->state)); */
        return 0;
    }

    hdl->state = PLUGIN_READY;

    os_sem_create(&hdl->task_sem, 0);

    return 0;
}

static int sharpen_start(pipe_plugin_t *plugin, int source_channel)
{
    ASSERT(plugin);
    struct sharpen_handle *hdl = (struct sharpen_handle *)plugin->private_data;
    ASSERT(hdl);

    if (hdl->state == PLUGIN_UNINIT || hdl->state == PLUGIN_INITED) {
        /* log_info("%s %s skipped. cur state: %s\r\n", plugin->name, __func__, plugin_state_str(hdl->state)); */
        return 0;
    }

    struct info_handle *info_hdl = NULL;
    list_for_each_entry(info_hdl, &hdl->info_head, entry) {
        if (info_hdl->channel == source_channel) {
            info_hdl->refs++;
            break;
        }
    }
    hdl->ref++;

    if (hdl->state == PLUGIN_RUNNING) {
        /* log_info("%s start. ref: %d\r\n", plugin->name, hdl->ref); */
    } else {
        thread_fork("sharpen_recv", 10, 2048, 0, &hdl->pid, sharpen_recv_task, plugin);

        hdl->state = PLUGIN_RUNNING;
    }

    return 0;
}

static int sharpen_stop(pipe_plugin_t *plugin, int source_channel)
{
    ASSERT(plugin);
    struct sharpen_handle *hdl = (struct sharpen_handle *)plugin->private_data;
    ASSERT(hdl);

    if (hdl->state != PLUGIN_RUNNING) {
        /* log_info("%s %s skipped. cur state: %s\r\n", plugin->name, __func__, plugin_state_str(hdl->state)); */
        return 0;
    }

    struct info_handle *info_hdl = NULL;
    list_for_each_entry(info_hdl, &hdl->info_head, entry) {
        if (info_hdl->channel == source_channel) {
            info_hdl->refs--;
            break;
        }
    }

    ASSERT(hdl->ref);
    hdl->ref--;
    if (hdl->ref > 0) {
        return 0;
    }

    hdl->state = PLUGIN_PAUSED;

    hdl->task_kill = true;
    thread_kill(&hdl->pid, KILL_WAIT);
    hdl->task_kill = false;

    for (int i = 0 ; i < port_input_endpoint_num(plugin->port); i++) {
        pipe_endpoint_t *in_endpoint = port_get_input_endpoint(plugin->port, i);
        if (in_endpoint) {
            buffer_early_uninit(in_endpoint->data_buffer);
        }

    }

    return 0;
}

static int sharpen_reset(pipe_plugin_t *plugin, int source_channel)
{
    ASSERT(plugin);
    struct sharpen_handle *hdl = (struct sharpen_handle *)plugin->private_data;
    ASSERT(hdl);

    if (hdl->ref > 0) {
        return 0;
    }

    hdl->state = PLUGIN_UNINIT;

    for (int i = 0 ; i < port_input_endpoint_num(plugin->port); i++) {
        pipe_endpoint_t *in_endpoint = port_get_input_endpoint(plugin->port, i);
        if (in_endpoint) {
            buffer_uninit(in_endpoint->data_buffer, source_channel);
        }

    }

    g_sharpen_used[hdl->channel] = NULL;
    plugin->private_data = NULL;
    free(hdl);

    return 0;
}

static int sharpen_get_parameter(pipe_plugin_t *plugin, int cmd, void *arg, int source_channel)
{
    return 0;
}

static int sharpen_set_parameter(pipe_plugin_t *plugin, int cmd, void *arg, int source_channel)
{
    struct sharpen_handle *hdl = (struct sharpen_handle *)plugin->private_data;
    if (!hdl) {
        return -1;
    }
    struct info_handle *info_hdl = NULL;

    switch (cmd) {
    case QQ://这里加入你要处理的内容
        //   JLsharpen_init(A, B, C);
        /* JLsharpen_init(64, 128, 128);  //阈值, 强度， 限制 */
        break;
    case PIPELINE_SET_FORMAT:
        struct video_format *f = (struct video_format *)arg;
        u8 find = 0;
        list_for_each_entry(info_hdl, &hdl->info_head, entry) {
            if (info_hdl->channel == source_channel) {
                find = 1;
                break;
            }
        }
        if (!find) {
            info_hdl = zalloc(sizeof(struct info_handle));
            ASSERT(info_hdl);
            info_hdl->channel = source_channel;
        }
        info_hdl->src_width = f->src_width;
        info_hdl->src_height = f->src_height;
        info_hdl->dst_width = f->win.width;
        info_hdl->dst_height = f->win.height;
        info_hdl->dst_fps = info_hdl->src_fps = f->fps;

        if (!find) {
            list_add(&info_hdl->entry, &hdl->info_head);
        }
        /* log_debug("[%s]: source channel %d saved.\r\n", plugin->ops->name, source_channel); */
        /* log_debug("-- size : %d x %d --> %d x %d", info_hdl->src_width, info_hdl->src_height, info_hdl->dst_width, info_hdl->dst_height); */
        break;
    case VIDIOC_SET_FPS:
        pipe_common_t info = {0};
        info.channel = source_channel;
        message_request(plugin->port, GET_DATA_INFO | MESSAGE_PREV, &info);
        ASSERT(info.fps);
        int src_fps = info.fps;

        list_for_each_entry(info_hdl, &hdl->info_head, entry) {
            struct video_dev_fps *fps = (struct video_dev_fps *)arg;
            if (info_hdl->channel == source_channel) {
                info_hdl->src_fps = src_fps;
                info_hdl->dst_fps = fps->target_fps;
                /* log_debug("-- fps : %d --> %d", info_hdl->src_fps, info_hdl->dst_fps); */
                break;
            }
        }
        break;
//    case VIDIOC_SET_D_ATTR:
//        struct video_enc_attr *attr = (struct video_enc_attr *)arg;
//        if (attr->format == VID_PIX_FMT_MJPG) {
//            hdl->thumbnail_enable = 1;
//        }
//        break;
    default:
        break;
    }

    return 0;
}


static u32 sharpen_outdata_len(struct sharpen_handle *hdl, u32 pix_len)
{
    u32 len = pix_len;
    switch (hdl->input_format) {
    case FORMAT_YUV420P:
        len *= 1.5;
        break;
    case FORMAT_YUV422P:
    //go on
    case FORMAT_YUV422_UYVY:
    //go on
    case FORMAT_YUV422_YUYV:
        len *= 2;
        break;
    default:
        break;
    }
    printf("xzpin sharpen len = %d\n", len);
    return len;
}

static int sharpen_set_source_info(pipe_plugin_t *plugin, int source_channel)
{
    struct sharpen_handle *hdl = (struct sharpen_handle *)plugin->private_data;

    if (hdl->source_channel == source_channel && hdl->state == PLUGIN_RUNNING) {
        return 0;
    }

    pipe_common_t info = {0};
    info.channel = source_channel;
    message_request(plugin->port, GET_DATA_INFO | MESSAGE_PREV, &info);
    ASSERT(info.width);

    u8 find = 0;
    struct info_handle *info_hdl = NULL;
    list_for_each_entry(info_hdl, &hdl->info_head, entry) {
        if (info_hdl->channel == source_channel) {
            find = 1;
            break;
        }
    }

    if (!find) {
        info_hdl = zalloc(sizeof(struct info_handle));
        ASSERT(info_hdl);
        info_hdl->channel = source_channel;
        list_add(&info_hdl->entry, &hdl->info_head);
    }

    if (!info_hdl->src_width) {
        info_hdl->src_format = info.format;
        info_hdl->src_width = info.width;
        info_hdl->src_height = info.height;
        info_hdl->src_fps = info.fps;
    }

    if (!info_hdl->dst_width) {
        info_hdl->dst_format = info_hdl->src_format;
        info_hdl->dst_width = info_hdl->src_width;
        info_hdl->dst_height = info_hdl->src_height;
        info_hdl->dst_fps = info_hdl->src_fps;
    }

    if (hdl->source_channel == (u8) - 1) {
        hdl->input_format = info_hdl->src_format;
        hdl->input_width = info_hdl->src_width;
        hdl->input_height = info_hdl->src_height;

        hdl->output_width = info_hdl->dst_width;
        hdl->output_height = info_hdl->dst_height;
        hdl->output_format = info_hdl->dst_format;
        printf("output_format:%d", hdl->output_format);
        hdl->source_channel = info_hdl->channel;
    }

    return 0;
}

static int sharpen_connect(pipe_plugin_t *prev_plugin, pipe_plugin_t *plugin, int source_channel)
{
    ASSERT(prev_plugin);
    ASSERT(plugin);

    buffer_info_t buffer_info = {0};
    buffer_t *buffer = buffer_init(plugin->name, &buffer_info);
    if (!buffer) {
        /* log_info("plugin link fail: %s -> %s", prev_plugin->name, plugin->name); */
        return -1;
    }

    /* log_info("plugin link: %s -> %s", prev_plugin->name, plugin->name); */

    if (!port_check_connected(prev_plugin, plugin)) {
        pipe_endpoint_t *out_endpoint = port_add_output_endpoint(prev_plugin->port, plugin->name, source_channel);
        out_endpoint->data_buffer = buffer;

        pipe_endpoint_t *in_endpoint = port_add_input_endpoint(plugin->port, prev_plugin->name, source_channel);
        in_endpoint->data_buffer = buffer;
        sharpen_set_source_info(plugin, source_channel);
    } else {
        port_source_channel_inc(prev_plugin, plugin, source_channel);
        sharpen_set_source_info(plugin, source_channel);
        return 0;
    }

    struct sharpen_handle *hdl = (struct sharpen_handle *)plugin->private_data;
    u32 buf_len = sizeof(buffer_meta_t) + LBUF_RESERVE_LEN + sharpen_outdata_len(hdl, hdl->input_width * hdl->input_height);
    if (buffer_get_memory_size(buffer) < buf_len) {
        if (buffer_get_memory_size(buffer) != false) {
            buffer_free_memory(buffer);
        }
        buffer_info.buffer_type = QUEUE_BUFFER;
        buffer_info.memory_type = DDR_MEMORY;
        buffer_info.buffer_size = buf_len;
        int ret = buffer_alloc_memory(buffer, &buffer_info);
        ASSERT(ret == 0, "buffer malloc failed, need size: %d", buf_len);
    }

    return 0;
}

static int check_channel_legal(pipe_plugin_t *plugin, u8 channel_max)
{
    int channel = 0;
    u8 plugin_name_len = strlen(plugin->ops->name) - 1;
    char plugin_channel = plugin->name[plugin_name_len];

    if (plugin_channel != '\0' &&
        plugin_channel >= '0' &&
        plugin_channel <= '9') {
        channel = plugin_channel - '0';
    } else {
        ASSERT(0, "plugin name is illegal : %s, please check!!", plugin->name);
    }

    if (channel > channel_max) {
        ASSERT(0, "channel is illegal : %s, please check!!", plugin->name);
    }

    return channel;
}

static int sharpen_init(pipe_plugin_t *plugin)
{
    ASSERT(plugin);
    int channel = check_channel_legal(plugin, SHARPEN_MAX_CHANNEL);
    struct sharpen_handle *hdl = NULL;
    if (!g_sharpen_used[channel]) {
        hdl = (struct sharpen_handle *)zalloc(sizeof(struct sharpen_handle));
    } else {
        hdl = g_sharpen_used[channel];
    }
    ASSERT(hdl);

    if (hdl->state != PLUGIN_UNINIT) {
        /* log_info("%s %s skipped. cur state: %s\r\n", plugin->name, __func__, plugin_state_str(hdl->state)); */
        ASSERT(plugin->private_data, "cur plugin used by other pipeline.");
        return 0;
    }

    hdl->state = PLUGIN_INITED;

    spin_lock_init(&hdl->lock);

    hdl->channel = channel;
    hdl->source_channel = (u8) - 1;
    INIT_LIST_HEAD(&hdl->info_head);

    /* log_info("sharpen init"); */

    hdl->input_format = FORMAT_YUV420P;
    hdl->line = 16;

    plugin->private_data = hdl;

    g_sharpen_used[hdl->channel] = hdl;

    return 0;
}

static int sharpen_message_callback(pipe_plugin_t *plugin, int cmd, void *arg)
{
    int ret = PIPE_MESSAGE_OK;
    struct sharpen_handle *hdl = plugin->private_data;
    int type = cmd & ~MESSAGE_ALL;
    u8 prev = (cmd & MESSAGE_PREV) ? 1 : 0;

    switch (type) {
    case GET_DATA_INFO:
        pipe_common_t *info = (pipe_common_t *)arg;
        struct info_handle *info_hdl = NULL;
        list_for_each_entry(info_hdl, &hdl->info_head, entry) {
            if (info_hdl->channel == info->channel) {
                if (prev) {
                    info->format = info_hdl->dst_format;
                    info->width = info_hdl->dst_width;
                    info->height = info_hdl->dst_height;
                    info->fps = info_hdl->dst_fps;
                } else {
                    info->format = info_hdl->src_format;
                    info->width = info_hdl->src_width;
                    info->height = info_hdl->src_height;
                    info->fps = info_hdl->src_fps;
                }
                return PIPE_MESSAGE_OK;
            }
        }
        ret = PIPE_MESSAGE_CONTINUE;
        break;
    default:
        ret = message_request(plugin->port, cmd, arg);
        break;
    }

    return ret;
}

static u8 *image_buf = NULL;
static pipe_core_t *pipe_core;
#define TEST_SHP
void sharpen_base_test(void)
{
    char *source = "csi0";
    pipe_core = pipeline_init(NULL, NULL);
    ASSERT(pipe_core);
    pipe_core->channel = plugin_source_to_channel(source);
    pipe_filter_t *isc_filter = pipeline_filter_add(pipe_core, source);
    pipe_filter_t *isp_filter = pipeline_filter_add(pipe_core, "isp0");
    pipe_filter_t *imc_filter = pipeline_filter_add(pipe_core, "imc0");
    pipe_filter_t *jpeg_enc_filter = pipeline_filter_add(pipe_core, plugin_factory_find("jpeg_enc"));

#ifdef TEST_SHP
    pipe_filter_t *shp_filter = pipeline_filter_add(pipe_core, "shp0");
#endif
    pipe_filter_t *imagesink_filter = pipeline_filter_add(pipe_core, "imagesink0");
    struct video_format f = {0};
    f.online = 1;
    f.pixelformat = VIDEO_PIX_FMT_JPEG | VIDEO_PIX_FMT_YUV420;
    f.type = VIDEO_BUF_TYPE_IMAGE_CAPTURE;
    f.win.width = 1280;
    f.win.height = 720;
    pipeline_param_set(pipe_core, NULL, QQ, 0);
    pipeline_param_set(pipe_core, NULL, PIPELINE_SET_FORMAT, (int)&f);
    int line_cnt = 16;
    pipeline_param_set(pipe_core, NULL, PIPELINE_SET_BUFFER_LINE, (int)&line_cnt);
    struct video_image_capture icap = {0};
    image_buf = malloc(1280 * 720 * 2); //720*2
    ASSERT(image_buf);
    icap.baddr = image_buf;
    icap.size = 1280 * 720 * 2;
    icap.width = 1280;
    icap.height = 720;

    icap.linear_scale = 16;

    pipeline_param_set(pipe_core, NULL, PIPELINE_SET_EXTERN_BUFFER, (int)&icap);
    pipeline_param_set(pipe_core, NULL, PIPELINE_SET_IMAGE_PHOTO, 0);
    pipeline_filter_link(isc_filter, isp_filter);
    pipeline_filter_link(isp_filter, imc_filter);
#ifdef TEST_SHP
    pipeline_filter_link(imc_filter, shp_filter);
    pipeline_filter_link(shp_filter, jpeg_enc_filter);
    pipeline_filter_link(jpeg_enc_filter, imagesink_filter);
#else
    pipeline_filter_link(imc_filter, jpeg_enc_filter);
    pipeline_filter_link(jpeg_enc_filter, imagesink_filter);
#endif
    pipeline_prepare(pipe_core);
    pipeline_start(pipe_core);
    os_time_dly(1000);
    FILE *fp = fopen(CONFIG_ROOT_PATH"9.jpg", "w+");
    if (fp) {
        fwrite(image_buf, 1280 * 720 * 2, 1, fp); //1280*720*2
        fclose(fp);
        fp = NULL;
    }
    pipeline_stop(pipe_core);

    pipeline_reset(pipe_core);

    pipeline_uninit(pipe_core);
    pipe_core = NULL;
    if (image_buf) {
        free(image_buf);
        image_buf = NULL;
    }
    printf("xzpin sharpen end \n");

}

REGISTER_PLUGIN(sharpen0) = {
    .name           = "shp0",
    .type           = PLUGIN_FILTER,
    .init           = sharpen_init,
    .connect        = sharpen_connect,
    .prepare        = sharpen_prepare,
    .start          = sharpen_start,
    .stop           = sharpen_stop,
    .reset          = sharpen_reset,
    .get_parameter  = sharpen_get_parameter,
    .set_parameter  = sharpen_set_parameter,
    .msg_cb         = sharpen_message_callback,
};

