#ifndef CURL_GET_DATA_H
#define CURL_GET_DATA_H

#include <stdint.h>
#include "generic/circular_buf.h"

void *curl_session_create(const char *url);
void curl_session_destroy(void *sess);
int curl_session_init(void *sess);
uint32_t curl_session_get_file_size(void *sess);
uint32_t curl_session_get_position(void *sess);
int curl_session_seek(void *sess, uint32_t position);
int curl_session_read_at(void *sess, uint32_t offset,
                         uint8_t *buffer, uint32_t length, uint32_t *received);
int curl_session_read(void *sess, uint8_t *buffer, uint32_t length, uint32_t *received);
int curl_session_read_at_cbuf(void *sess, uint32_t offset,
                              cbuffer_t *cbuf, uint32_t length, uint32_t *received);
int curl_session_read_cbuf(void *sess,
                           cbuffer_t *cbuf, uint32_t length, uint32_t *received);

#endif /* CURL_GET_DATA_H */

