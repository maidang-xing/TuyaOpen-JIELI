#include "tkl_queue.h"

#include "jieli_tkl_os.h"
#include "tuya_error_code.h"

#include <stdlib.h>
#include <string.h>

OPERATE_RET tkl_queue_create_init(TKL_QUEUE_HANDLE *queue, int msgsize, int msgcount)
{
    if (queue == NULL || msgsize <= 0 || msgcount <= 0) {
        return OPRT_INVALID_PARM;
    }
    JIELI_TKL_QUEUE *jieli_queue = calloc(1, sizeof(*jieli_queue));
    if (jieli_queue == NULL || os_q_create(&jieli_queue->queue, (QS)msgcount) != 0) {
        free(jieli_queue);
        return OPRT_OS_ADAPTER_QUEUE_CREAT_FAILED;
    }
    jieli_queue->message_size = (uint32_t)msgsize;
    *queue = (TKL_QUEUE_HANDLE)jieli_queue;
    return OPRT_OK;
}

OPERATE_RET tkl_queue_post(const TKL_QUEUE_HANDLE queue, void *data, uint32_t timeout)
{
    if (queue == NULL || data == NULL) {
        return OPRT_INVALID_PARM;
    }
    JIELI_TKL_QUEUE *jieli_queue = (JIELI_TKL_QUEUE *)queue;
    void *copy = malloc(jieli_queue->message_size);
    int result;
    if (copy == NULL) {
        return OPRT_MALLOC_FAILED;
    }
    memcpy(copy, data, jieli_queue->message_size);

    /* os_q_post() is the only post API whose pointer convention is identical on
     * both vendor SDKs: it queues the pointer value itself, which is exactly
     * what os_q_pend()/os_q_accept() hand back to tkl_queue_fetch().
     *
     * os_q_post_to_back() is NOT portable. Disassembly of the two SDKs shows the
     * AC79NN (FreeRTOS) build copies the word stored *at* the address it is
     * given, while the AC792N build forwards its argument to OSQPost() and
     * queues the value. Handing the AC79NN build a payload pointer therefore
     * queues the payload's first word -- for sloop_sock_t that is the socket fd
     * -- which tkl_queue_fetch() then dereferences as a pointer.
     *
     * os_q_post() does not block, and the two SDKs do not agree on a portable
     * way to wait for space, so `timeout` is accepted but not honoured: posting
     * to a full queue fails immediately. */
    (void)timeout;
    result = os_q_post(&jieli_queue->queue, copy);
    if (result != 0) {
        free(copy);
        return OPRT_OS_ADAPTER_QUEUE_SEND_FAIL;
    }

    return OPRT_OK;
}

OPERATE_RET tkl_queue_fetch(const TKL_QUEUE_HANDLE queue, void *msg, uint32_t timeout)
{
    if (queue == NULL || msg == NULL) {
        return OPRT_INVALID_PARM;
    }
    JIELI_TKL_QUEUE *jieli_queue = (JIELI_TKL_QUEUE *)queue;
    void *copy = NULL;
    int result;

    /* TKL treats timeout 0 as "do not wait", but os_q_pend() maps a 0 timeout
     * to portMAX_DELAY ("取0时无限等待"). A non-blocking fetch therefore has to
     * use os_q_accept(), which is the SDK's documented non-blocking receive. */
    if (timeout == 0) {
        result = os_q_accept(&jieli_queue->queue, &copy);
    } else {
        result = os_q_pend(&jieli_queue->queue, jieli_tkl_timeout_to_ticks(timeout), &copy);
    }
    if (result != 0) {
        return OPRT_OS_ADAPTER_QUEUE_RECV_FAIL;
    }
    if (copy != NULL) {
        memcpy(msg, copy, jieli_queue->message_size);
        free(copy);
    }
    return OPRT_OK;
}

void tkl_queue_free(const TKL_QUEUE_HANDLE queue)
{
    if (queue != NULL) {
        JIELI_TKL_QUEUE *jieli_queue = (JIELI_TKL_QUEUE *)queue;
        void *copy = NULL;

        /* The queue owns a heap copy for each posted message. Drain pending
         * messages before deleting the OS queue so their allocations are not
         * leaked. Callers must stop queue users before freeing the handle. */
        while (os_q_accept(&jieli_queue->queue, &copy) == 0) {
            free(copy);
            copy = NULL;
        }
        (void)os_q_del(&jieli_queue->queue, OS_DEL_ALWAYS);
        free(jieli_queue);
    }
}
