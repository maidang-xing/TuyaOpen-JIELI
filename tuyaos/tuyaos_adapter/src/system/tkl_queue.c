#include "tkl_queue.h"
#include "tkl_semaphore.h"

#include "system/os/os_api.h"
#include "tuya_error_code.h"

#include <stdlib.h>
#include <string.h>

typedef struct {
    uint8_t *slots;
    uint32_t message_size;
    uint32_t msgcount;
    uint32_t head;
    uint32_t tail;
    OS_MUTEX mutex;
    TKL_SEM_HANDLE free_slots;
    TKL_SEM_HANDLE filled;
} JIELI_TKL_QUEUE;

/*
 * TKL queues are built on local storage rather than the vendor os_q_* API.
 *
 * The vendor queue cannot be used portably. Disassembly of the two SDKs shows
 * that os_q_post_to_back() interprets its message argument differently: the
 * AC79NN (FreeRTOS) build copies the word stored *at* the address it is given,
 * while the AC792N build forwards the argument to OSQPost() and queues the
 * value. Handing the AC79NN build a payload pointer therefore queues the
 * payload's first word, which the fetch side then dereferences as a pointer.
 * The two SDKs also disagree on the timeout encoding of os_q_pend(), and
 * os_q_post() - the one post API they do agree on - cannot block, so it cannot
 * honour TKL's post timeout.
 *
 * The ring buffer below is portable and honours both the finite-timeout and
 * the wait-forever forms of the TKL contract.
 */

OPERATE_RET tkl_queue_create_init(TKL_QUEUE_HANDLE *queue, int msgsize, int msgcount)
{
    JIELI_TKL_QUEUE *jieli_queue;
    unsigned int created = 0;

    if (queue == NULL || msgsize <= 0 || msgcount <= 0) {
        return OPRT_INVALID_PARM;
    }

    jieli_queue = calloc(1, sizeof(*jieli_queue));
    if (jieli_queue == NULL) {
        return OPRT_MALLOC_FAILED;
    }

    jieli_queue->slots = malloc((size_t)msgsize * (size_t)msgcount);
    if (jieli_queue->slots == NULL) {
        free(jieli_queue);
        return OPRT_MALLOC_FAILED;
    }
    jieli_queue->message_size = (uint32_t)msgsize;
    jieli_queue->msgcount = (uint32_t)msgcount;

    /* free_slots starts full and filled starts empty, so the two counters
     * always add up to msgcount and neither can overrun the ring. */
    if (os_mutex_create(&jieli_queue->mutex) != 0) {
        goto err;
    }
    created |= 1u;
    if (tkl_semaphore_create_init(&jieli_queue->free_slots, (uint32_t)msgcount, (uint32_t)msgcount) != OPRT_OK) {
        goto err;
    }
    created |= 2u;
    if (tkl_semaphore_create_init(&jieli_queue->filled, 0, (uint32_t)msgcount) != OPRT_OK) {
        goto err;
    }
    created |= 4u;

    *queue = (TKL_QUEUE_HANDLE)jieli_queue;
    return OPRT_OK;

err:
    if (created & 4u) {
        (void)tkl_semaphore_release(jieli_queue->filled);
    }
    if (created & 2u) {
        (void)tkl_semaphore_release(jieli_queue->free_slots);
    }
    if (created & 1u) {
        (void)os_mutex_del(&jieli_queue->mutex, OS_DEL_ALWAYS);
    }
    free(jieli_queue->slots);
    free(jieli_queue);
    return OPRT_OS_ADAPTER_QUEUE_CREAT_FAILED;
}

OPERATE_RET tkl_queue_post(const TKL_QUEUE_HANDLE queue, void *data, uint32_t timeout)
{
    JIELI_TKL_QUEUE *jieli_queue = (JIELI_TKL_QUEUE *)queue;
    uint32_t slot;

    if (queue == NULL || data == NULL) {
        return OPRT_INVALID_PARM;
    }

    /* Reserve a slot before taking the mutex: waiting while holding it would
     * stop the consumer from releasing one. */
    if (tkl_semaphore_wait(jieli_queue->free_slots, timeout) != OPRT_OK) {
        return OPRT_OS_ADAPTER_QUEUE_SEND_FAIL;
    }

    if (os_mutex_pend(&jieli_queue->mutex, 0) != 0) {
        (void)tkl_semaphore_post(jieli_queue->free_slots);
        return OPRT_OS_ADAPTER_QUEUE_SEND_FAIL;
    }
    slot = jieli_queue->head;
    memcpy(jieli_queue->slots + (size_t)slot * jieli_queue->message_size, data, jieli_queue->message_size);
    jieli_queue->head = (slot + 1u) % jieli_queue->msgcount;
    (void)os_mutex_post(&jieli_queue->mutex);

    (void)tkl_semaphore_post(jieli_queue->filled);
    return OPRT_OK;
}

OPERATE_RET tkl_queue_fetch(const TKL_QUEUE_HANDLE queue, void *msg, uint32_t timeout)
{
    JIELI_TKL_QUEUE *jieli_queue = (JIELI_TKL_QUEUE *)queue;
    uint32_t slot;

    if (queue == NULL || msg == NULL) {
        return OPRT_INVALID_PARM;
    }

    if (tkl_semaphore_wait(jieli_queue->filled, timeout) != OPRT_OK) {
        return OPRT_OS_ADAPTER_QUEUE_RECV_FAIL;
    }

    if (os_mutex_pend(&jieli_queue->mutex, 0) != 0) {
        (void)tkl_semaphore_post(jieli_queue->filled);
        return OPRT_OS_ADAPTER_QUEUE_RECV_FAIL;
    }
    slot = jieli_queue->tail;
    memcpy(msg, jieli_queue->slots + (size_t)slot * jieli_queue->message_size, jieli_queue->message_size);
    jieli_queue->tail = (slot + 1u) % jieli_queue->msgcount;
    (void)os_mutex_post(&jieli_queue->mutex);

    (void)tkl_semaphore_post(jieli_queue->free_slots);
    return OPRT_OK;
}

void tkl_queue_free(const TKL_QUEUE_HANDLE queue)
{
    JIELI_TKL_QUEUE *jieli_queue = (JIELI_TKL_QUEUE *)queue;

    if (jieli_queue == NULL) {
        return;
    }

    /* Messages live in the queue's own storage, so there is nothing to drain.
     * Callers must stop queue users before freeing the handle. */
    (void)tkl_semaphore_release(jieli_queue->filled);
    (void)tkl_semaphore_release(jieli_queue->free_slots);
    (void)os_mutex_del(&jieli_queue->mutex, OS_DEL_ALWAYS);
    free(jieli_queue->slots);
    free(jieli_queue);
}
