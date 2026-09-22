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

static inline int jieli_tkl_timeout_to_ticks(uint32_t timeout_ms)
{
    if (timeout_ms == 0xFFFFFFFFu || timeout_ms == 0u) {
        return 0;
    }
    return (int)((timeout_ms + 9u) / 10u);
}

#endif
