#include "tkl_semaphore.h"

#include "system/os/os_api.h"
#include "tuya_error_code.h"

#include <stdlib.h>

typedef struct {
    OS_SEM sem;
} JIELI_TKL_SEM;

#define JIELI_TKL_TICK_MS 10u
#define JIELI_TKL_NO_WAIT 0u
#define JIELI_TKL_WAIT_FOREVER 0xFFFFFFFFu
#define JIELI_TKL_MAX_TICKS 65535u

static int jieli_tkl_timeout_to_ticks(uint32_t timeout_ms)
{
    uint32_t ticks = timeout_ms / JIELI_TKL_TICK_MS +
                     (timeout_ms % JIELI_TKL_TICK_MS != 0u ? 1u : 0u);

    /* AC792 stores the timeout in a u16 task-control-block field. */
    return (int)(ticks > JIELI_TKL_MAX_TICKS ? JIELI_TKL_MAX_TICKS : ticks);
}

/*
 * The two SDKs return opposite success values from os_sem_accept(). Detect the
 * linked OS convention once with a count-one semaphore, then normalise both to
 * 0 on success and OS_TIMEOUT on failure. Use OS_TIMEOUT itself: the vendor
 * timeout sentinel is not a portable literal such as -2. Build flags are not
 * reliable here: both chip variants compile the same adapter source through
 * different staged vendor Makefiles, so a chip #if can select the wrong OS
 * convention.
 */
static int jieli_tkl_sem_accept(OS_SEM *sem)
{
    static int accept_returns_count = -1;
    int result;

    if (accept_returns_count < 0) {
        OS_SEM probe;

        /* Fall back to the AC79 convention if the probe cannot be created. */
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

/* Normalize vendor semaphore behavior for the public TKL wait API. */
static int jieli_tkl_sem_wait(OS_SEM *sem, uint32_t timeout_ms)
{
    /*
     * TKL timeout 0 means "do not wait". Both vendor os_sem_pend() APIs use
     * zero ticks for wait-forever, so passing 0 here would block forever.
     * The lwIP sys_mutex_trylock path relies on this non-blocking behavior.
     * Do not substitute -1: AC79 treats it as an invalid timeout and emits an
     * OS warning. os_sem_accept() is the actual try-wait API.
     */
    if (timeout_ms == JIELI_TKL_NO_WAIT) {
        return jieli_tkl_sem_accept(sem);
    }
    if (timeout_ms == JIELI_TKL_WAIT_FOREVER) {
        return os_sem_pend(sem, 0);
    }
    /* Finite, non-zero waits are rounded up and capped to AC792's u16 range. */
    return os_sem_pend(sem, jieli_tkl_timeout_to_ticks(timeout_ms));
}

OPERATE_RET tkl_semaphore_create_init(TKL_SEM_HANDLE *handle, uint32_t sem_cnt, uint32_t sem_max)
{
    (void)sem_max;
    if (handle == NULL) {
        return OPRT_INVALID_PARM;
    }
    JIELI_TKL_SEM *sem = calloc(1, sizeof(*sem));
    if (sem == NULL || os_sem_create(&sem->sem, (int)sem_cnt) != 0) {
        free(sem);
        return OPRT_OS_ADAPTER_SEM_CREAT_FAILED;
    }
    *handle = (TKL_SEM_HANDLE)sem;
    return OPRT_OK;
}

OPERATE_RET tkl_semaphore_wait(const TKL_SEM_HANDLE handle, uint32_t timeout)
{
    JIELI_TKL_SEM *sem = (JIELI_TKL_SEM *)handle;
    int result;
    if (handle == NULL) {
        return OPRT_INVALID_PARM;
    }
    result = jieli_tkl_sem_wait(&sem->sem, timeout);
    /* jieli_tkl_sem_wait() normalizes a timeout to the SDK's OS_TIMEOUT value. */
    if (result == OS_TIMEOUT) {
        return OPRT_OS_ADAPTER_SEM_WAIT_TIMEOUT;
    }
    return result == 0 ? OPRT_OK : OPRT_OS_ADAPTER_SEM_WAIT_FAILED;
}

OPERATE_RET tkl_semaphore_post(const TKL_SEM_HANDLE handle)
{
    return handle == NULL ? OPRT_INVALID_PARM :
           (os_sem_post(&((JIELI_TKL_SEM *)handle)->sem) == 0 ? OPRT_OK : OPRT_OS_ADAPTER_SEM_POST_FAILED);
}

OPERATE_RET tkl_semaphore_release(const TKL_SEM_HANDLE handle)
{
    JIELI_TKL_SEM *sem = (JIELI_TKL_SEM *)handle;
    int result;
    if (sem == NULL) {
        return OPRT_INVALID_PARM;
    }
    result = os_sem_del(&sem->sem, OS_DEL_ALWAYS);
    free(sem);
    return result == 0 ? OPRT_OK : OPRT_OS_ADAPTER_SEM_RELEASE_FAILED;
}
