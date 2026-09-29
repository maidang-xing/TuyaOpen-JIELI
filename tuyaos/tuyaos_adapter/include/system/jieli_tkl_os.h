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

/* TKL's timeout sentinels, so call sites do not pass bare 0 / 0xFFFFFFFF. */
#define JIELI_TKL_NO_WAIT 0u
#define JIELI_TKL_WAIT_FOREVER 0xFFFFFFFFu

/*
 * The AC792N build stores a pend timeout in the u16 OSTCBDly field of the task
 * control block, so a larger tick count truncates silently - 0x7FFFFFFF would
 * become 65535. Cap finite waits at 65535 ticks, about 11 minutes.
 */
#define JIELI_TKL_MAX_TICKS 65535u

/*
 * Convert a TKL millisecond timeout into the tick count os_*_pend() expects.
 *
 * Do not pass TKL's 0 or 0xFFFFFFFF through here. On BOTH SDKs a 0 tick timeout
 * means "wait forever" (os_api.h: "取0时无限等待") and a -1 tick timeout means
 * "do not wait", so jieli_tkl_sem_wait()/jieli_tkl_mutex_pend() handle those two
 * cases themselves. Call this only for a finite, non-zero timeout.
 *
 * The division avoids the overflow that "timeout_ms + TICK_MS - 1" would hit for
 * timeout_ms close to UINT32_MAX.
 */
static inline int jieli_tkl_timeout_to_ticks(uint32_t timeout_ms)
{
    uint32_t ticks = timeout_ms / JIELI_TKL_TICK_MS + (timeout_ms % JIELI_TKL_TICK_MS != 0u ? 1u : 0u);

    return (int)(ticks > JIELI_TKL_MAX_TICKS ? JIELI_TKL_MAX_TICKS : ticks);
}

/*
 * Non-blocking semaphore take, normalised to 0 on success / OS_TIMEOUT on
 * failure on both SDKs.
 *
 * Neither vendor call is usable on its own:
 *   - os_sem_accept() returns 0/OS_TIMEOUT on AC79NN, but on AC792N it is a bare
 *     tail call to uCOS-II OSSemAccept(), which returns the PRE-decrement count:
 *     0 when the semaphore was empty, >= 1 when a token was taken. Opposite
 *     sense, and the token is consumed either way.
 *   - os_sem_pend(sem, -1) is normalised on AC792N, but on AC79NN it logs
 *     "<Error>: [OS] [Serious Warning for os_sem_pend]For blocking, please set
 *     timeout to 0" on every call, and the non-blocking path is hot.
 *
 * The two SDKs cannot be told apart by a header-level #if. The same adapter
 * sources are compiled twice: the staged vendor Makefile defines
 * -DCONFIG_CPU_WL83 for the AC792N build (plus -DCONFIG_UCOS_ENABLE), while the
 * CMake adapter target hardcodes -DCONFIG_CPU_WL82 even for that build, so an
 * #if here would be correct only in whichever copy the linker happens to pick.
 * Probe the convention once instead, which asks the OS that is actually linked:
 * a scratch semaphore created at count 1 - AC79NN reports success as 0, AC792N
 * as the pre-decrement count of 1.
 */
static inline int jieli_tkl_sem_accept(OS_SEM *sem)
{
    static int accept_returns_count = -1;
    int result;

    if (accept_returns_count < 0) {
        OS_SEM probe;

        /* Fall back to the AC79NN convention if the probe cannot be created. */
        accept_returns_count = 0;
        if (os_sem_create(&probe, 1) == 0) {
            accept_returns_count = (os_sem_accept(&probe) != 0);
            (void)os_sem_del(&probe, OS_DEL_ALWAYS);
        }
    }

    result = os_sem_accept(sem);
    if (accept_returns_count) {
        return (result > 0) ? 0 : OS_TIMEOUT;
    }
    return result;
}

/*
 * Wait on a Jieli semaphore, honouring TKL's timeout contract: 0 means "do not
 * wait" and 0xFFFFFFFF means "wait forever".
 *
 * Both SDKs read a 0 tick timeout as "wait forever" (os_api.h: "取0时无限等待"),
 * so TKL's 0 must never reach os_sem_pend(); the non-blocking case goes through
 * the normalised os_sem_accept() above instead.
 */
static inline int jieli_tkl_sem_wait(OS_SEM *sem, uint32_t timeout_ms)
{
    if (timeout_ms == JIELI_TKL_NO_WAIT) {
        return jieli_tkl_sem_accept(sem);
    }
    if (timeout_ms == JIELI_TKL_WAIT_FOREVER) {
        return os_sem_pend(sem, 0);
    }
    return os_sem_pend(sem, jieli_tkl_timeout_to_ticks(timeout_ms));
}

#endif
