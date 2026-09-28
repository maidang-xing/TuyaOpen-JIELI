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

typedef struct {
    OS_QUEUE queue;
    uint32_t message_size;
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
 * The two vendor SDKs do not agree on the "wait forever" encoding of
 * os_q_pend()/os_sem_pend(). The AC79NN (FreeRTOS) build maps a 0 tick timeout
 * to portMAX_DELAY, while the AC792N build treats -1 as infinite and 0 as "do
 * not wait". A large positive tick count is read as a long finite wait by both,
 * so use it for TKL's WAIT_FOREVER.
 *
 * A TKL timeout of 0 means "do not wait" and is passed through as 0 ticks.
 * Because the two SDKs disagree on what 0 ticks means, callers that need
 * non-blocking behaviour must use the *_accept() receive variants instead of
 * relying on the value returned here.
 */
static inline int jieli_tkl_timeout_to_ticks(uint32_t timeout_ms)
{
    if (timeout_ms == 0u) {
        return 0;
    }
    if (timeout_ms == 0xFFFFFFFFu) {
        return 0x7FFFFFFF;
    }
    return (int)((timeout_ms + JIELI_TKL_TICK_MS - 1u) / JIELI_TKL_TICK_MS);
}

#endif
