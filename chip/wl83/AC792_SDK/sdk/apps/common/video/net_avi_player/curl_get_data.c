#include <curl/curl.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "curl_get_data.h"


struct curl_session {
    char *url;                     // 文件URL
    uint32_t file_size;            // 文件总大小
    uint32_t current_pos;          // 当前读取位置
    CURL *curl;                    // curl句柄 (可复用)
    int initialized;               // 是否已初始化
};

struct mem_write_ctx {
    uint8_t *buffer;
    uint32_t buf_size;
    uint32_t received;
    cbuffer_t *cbuf;
};


static size_t write_to_memory_callback(void *contents, size_t size, size_t nmemb, void *userp)
{
    struct mem_write_ctx *ctx = (struct mem_write_ctx *)userp;
    size_t realsize = size * nmemb;

    uint32_t copy_size = realsize;
    if (ctx->received + copy_size > ctx->buf_size) {
        copy_size = ctx->buf_size - ctx->received;
    }

    if (copy_size > 0) {
        memcpy(ctx->buffer + ctx->received, contents, copy_size);
        ctx->received += copy_size;
    }

    return realsize;
}

static size_t write_to_cbuf_callback(void *contents, size_t size, size_t nmemb, void *userp)
{
    struct mem_write_ctx *ctx = (struct mem_write_ctx *)userp;
    size_t realsize = size * nmemb;
    cbuffer_t *cbuf = ctx->cbuf;

    uint32_t write_size = realsize;
    uint32_t free_space = cbuf->total_len - cbuf_get_data_size(cbuf);
    if (write_size > free_space) {
        printf("cbuf overflow, write_size=%u, free_space=%u\n", write_size, free_space);
        write_size = free_space;
    }

    if (write_size > 0) {
        ctx->received += cbuf_write(cbuf, (uint8_t *)contents, write_size);
    }
    return realsize;
}

static size_t write_null_callback(void *contents, size_t size, size_t nmemb, void *userp)
{
    (void)contents;
    (void)userp;
    return size * nmemb;
}

void *curl_session_create(const char *url)
{
    if (!url || strlen(url) == 0) {
        printf("invalid url\n");
        return NULL;
    }

    struct curl_session *session = malloc(sizeof(struct curl_session));
    if (!session) {
        printf("malloc session failed\n");
        return NULL;
    }
    memset(session, 0, sizeof(*session));

    session->url = strdup(url);
    if (!session->url) {
        printf("strdup url failed\n");
        free(session);
        return NULL;
    }

    printf("curl session created: %s", url);
    return (void *)session;
}

void curl_session_destroy(void *sess)
{
    if (!sess) {
        return;
    }
    struct curl_session *session = (struct curl_session *)sess;

    if (session->url) {
        free(session->url);
        session->url = NULL;
    }

    if (session->curl) {
        curl_easy_cleanup(session->curl);
        session->curl = NULL;
    }

    free(session);
    printf("curl session destroyed\n");
}


int curl_session_init(void *sess)
{
    if (!sess) {
        return -1;
    }
    struct curl_session *session = (struct curl_session *)sess;

    CURL *curl = curl_easy_init();
    if (!curl) {
        printf("curl_easy_init failed\n");
        return -2;
    }

    curl_easy_setopt(curl, CURLOPT_URL, session->url);
    curl_easy_setopt(curl, CURLOPT_NOBODY, 1L);  // HEAD请求
    curl_easy_setopt(curl, CURLOPT_HEADER, 0L);
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_null_callback);
    curl_easy_setopt(curl, CURLOPT_TIMEOUT, 30L);

    // 关闭SSL证书验证
    curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0L);
    curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, 0L);
    // 超时设置
    curl_easy_setopt(curl, CURLOPT_CONNECTTIMEOUT, 10L);
    curl_easy_setopt(curl, CURLOPT_LOW_SPEED_LIMIT, 1000L);  // 最低1KB/s
    curl_easy_setopt(curl, CURLOPT_LOW_SPEED_TIME, 30L);     // 持续30秒
    // 跟随重定向
    curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);
    curl_easy_setopt(curl, CURLOPT_MAXREDIRS, 5L);

    // 启用TCP keep-alive
    curl_easy_setopt(curl, CURLOPT_TCP_KEEPALIVE, 1L);


    CURLcode res = curl_easy_perform(curl);
    if (res != CURLE_OK) {
        printf("HEAD request failed: %s\n", curl_easy_strerror(res));
        curl_easy_cleanup(curl);
        return -3;
    }

    double content_length = 0;
    curl_easy_getinfo(curl, CURLINFO_CONTENT_LENGTH_DOWNLOAD, &content_length);

    if (content_length <= 0) {
        printf("invalid content length: %.0f\n", content_length);
        return -4;
    }

    session->file_size = (uint32_t)content_length;
    session->current_pos = 0;
    session->initialized = 1;
    session->curl = curl;

    printf("session init ok, file_size=%u\n", session->file_size);
    return 0;
}


uint32_t curl_session_get_file_size(void *sess)
{
    if (!sess) {
        return 0;
    }
    struct curl_session *session = (struct curl_session *)sess;
    if (!session->initialized) {
        return 0;
    }

    return session->file_size;
}

uint32_t curl_session_get_position(void *sess)
{
    if (!sess) {
        return 0;
    }
    struct curl_session *session = (struct curl_session *)sess;
    return session->current_pos;
}

int curl_session_seek(void *sess, uint32_t position)
{
    if (!sess) {
        return -1;
    }

    struct curl_session *session = (struct curl_session *)sess;
    if (!session->initialized) {
        return -1;
    }

    if (position > session->file_size) {
        position = session->file_size;
    }

    session->current_pos = position;
    return 0;
}


int curl_session_read_at(void *sess, uint32_t offset, uint8_t *buffer, uint32_t length, uint32_t *received)
{
    if (!sess || !buffer || length == 0) {
        return -1;
    }

    struct curl_session *session = (struct curl_session *)sess;
    CURL *curl = session->curl;
    if (offset + length >= session->file_size) {
        length = session->file_size - offset;
    }
    struct mem_write_ctx ctx = {
        .buffer = buffer,
        .buf_size = length,
        .received = 0
    };
    // 边界检查
    if (session->initialized && offset >= session->file_size) {
        if (received) {
            *received = 0;
        }
        return 0;  // EOF
    }


    // 设置Range
    char range_str[64];
    snprintf(range_str, sizeof(range_str), "%u-%u", offset, offset + length - 1);

    curl_easy_setopt(curl, CURLOPT_RANGE, range_str);
    curl_easy_setopt(curl, CURLOPT_NOBODY, 0L);
    curl_easy_setopt(curl, CURLOPT_HTTPGET, 1L);
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_to_memory_callback);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &ctx);


    CURLcode res = curl_easy_perform(curl);
    if (res != CURLE_OK) {
        printf("GET range failed: %s\n", curl_easy_strerror(res));
        return -3;
    }

    if (received) {
        *received = ctx.received;
    }

    return 0;
}

int curl_session_read_at_cbuf(void *sess, uint32_t offset, cbuffer_t *cbuf, uint32_t length, uint32_t *received)
{
    if (!sess || !cbuf || length == 0) {
        return -1;
    }

    struct curl_session *session = (struct curl_session *)sess;
    CURL *curl = session->curl;
    struct mem_write_ctx ctx = {
        .cbuf = cbuf,
        .buf_size = length,
        .received = 0
    };
    // 边界检查
    if (session->initialized && offset >= session->file_size) {
        if (received) {
            *received = 0;
        }
        return 0;  // EOF
    }


    // 设置Range
    char range_str[64];
    snprintf(range_str, sizeof(range_str), "%u-%u", offset, offset + length - 1);

    curl_easy_setopt(curl, CURLOPT_RANGE, range_str);
    curl_easy_setopt(curl, CURLOPT_NOBODY, 0L);
    curl_easy_setopt(curl, CURLOPT_HTTPGET, 1L);
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_to_cbuf_callback);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &ctx);


    CURLcode res = curl_easy_perform(curl);
    if (res != CURLE_OK) {
        printf("GET range failed: %s\n", curl_easy_strerror(res));
        return -3;
    }

    if (received) {
        *received = ctx.received;
    }

    return 0;
}


int curl_session_read(void *sess, uint8_t *buffer, uint32_t length, uint32_t *received)
{
    if (!sess) {
        return -1;
    }

    struct curl_session *session = (struct curl_session *)sess;
    int ret = curl_session_read_at(session, session->current_pos, buffer, length, received);
    if (ret == 0 && received) {
        session->current_pos += *received;
    }

    return ret;
}

int curl_session_read_cbuf(void *sess, cbuffer_t *cbuf, uint32_t length, uint32_t *received)
{
    if (!sess) {
        return -1;
    }
    //printf("curl_session_read_cbuf length=%u\n", length);

    struct curl_session *session = (struct curl_session *)sess;
    int ret = curl_session_read_at_cbuf(session, session->current_pos, cbuf, length, received);
    if (ret == 0 && received) {
        session->current_pos += *received;
    }

    return ret;
}
