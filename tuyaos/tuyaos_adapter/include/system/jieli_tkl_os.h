#ifndef JIELI_TKL_OS_H
#define JIELI_TKL_OS_H

#include <stdint.h>

#include "system/os/os_api.h"

typedef struct {
    OS_MUTEX mutex;
} JIELI_TKL_MUTEX;

typedef struct {
    OS_SEM sem;
} JIELI_TKL_SEM;

/*
 * TKL queues keep their messages in local storage instead of using the
 * vendor's os_q_* API. That API is not portable across the two SDKs: the
 * AC79NN (FreeRTOS) build and the AC792N build disagree both on how
 * os_q_post_to_back() interprets its message argument and on how a timeout is
 * encoded. A ring buffer guarded by a mutex and two counting semaphores is
 * portable, and it can honour TKL's finite-timeout and wait-forever post
 * semantics, which os_q_post() cannot.
 */
typedef struct {
    uint8_t *slots;    /* msgcount * message_size bytes */
    uint32_t message_size;
    uint32_t msgcount;
    uint32_t head;     /* next slot to write, guarded by mutex */
    uint32_t tail;     /* next slot to read, guarded by mutex */
    OS_MUTEX mutex;
    OS_SEM free_slots; /* counts empty slots, starts at msgcount */
    OS_SEM filled;     /* counts queued messages, starts at 0 */
} JIELI_TKL_QUEUE;

typedef struct {
    uint32_t magic;
    char name[configMAX_TASK_NAME_LEN];
    void (*func)(void *arg);
    void *arg;
} JIELI_TKL_THREAD;

#define JIELI_TKL_THREAD_MAGIC 0x4A544852u

/* One FreeRTOS/OS tick, used to convert TKL millisecond timeouts. */
#define JIELI_TKL_TICK_MS 10u

/*
 * Convert a TKL millisecond timeout into the tick count os_*_pend() expects.
 *
 * TKL uses 0 for "do not wait" and 0xFFFFFFFF for "wait forever". The two SDKs
 * disagree on what 0 ticks means - AC79NN maps it to portMAX_DELAY while
 * AC792N reads it as "do not wait" - so WAIT_FOREVER is expressed as a large
 * positive tick count, which both treat as a long finite wait. A TKL timeout
 * of 0 is returned as 0 and must be handled by the caller through the matching
 * os_*_accept() call, never passed to os_*_pend().
 *
 * The division is written to avoid the overflow that "timeout_ms + TICK_MS - 1"
 * would hit for timeout_ms close to UINT32_MAX.
 */
static inline int jieli_tkl_timeout_to_ticks(uint32_t timeout_ms)
{
    if (timeout_ms == 0u) {
        return 0;
    }
    if (timeout_ms == 0xFFFFFFFFu) {
        return 0x7FFFFFFF;
    }
    return (int)(timeout_ms / JIELI_TKL_TICK_MS + (timeout_ms % JIELI_TKL_TICK_MS != 0u ? 1u : 0u));
}

/* Wait on a Jieli semaphore, honouring TKL's timeout contract. */
static inline int jieli_tkl_sem_wait(OS_SEM *sem, uint32_t timeout_ms)
{
    if (timeout_ms == 0u) {
        return os_sem_accept(sem);
    }
    return os_sem_pend(sem, jieli_tkl_timeout_to_ticks(timeout_ms));
}

#endif
