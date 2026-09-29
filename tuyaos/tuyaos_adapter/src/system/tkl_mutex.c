#include "tkl_mutex.h"

#include "system/os/os_api.h"
#include "tuya_error_code.h"

#include <stdlib.h>

typedef struct {
    OS_MUTEX mutex;
} JIELI_TKL_MUTEX;

OPERATE_RET tkl_mutex_create_init(TKL_MUTEX_HANDLE *handle)
{
    if (handle == NULL) {
        return OPRT_INVALID_PARM;
    }
    JIELI_TKL_MUTEX *mutex = calloc(1, sizeof(*mutex));
    if (mutex == NULL || os_mutex_create(&mutex->mutex) != 0) {
        free(mutex);
        return OPRT_OS_ADAPTER_MUTEX_CREAT_FAILED;
    }
    *handle = (TKL_MUTEX_HANDLE)mutex;
    return OPRT_OK;
}

OPERATE_RET tkl_mutex_lock(const TKL_MUTEX_HANDLE handle)
{
    JIELI_TKL_MUTEX *mutex = (JIELI_TKL_MUTEX *)handle;
    /* 0 ticks means "wait forever" on both SDKs, which is what a lock wants. */
    return mutex == NULL ? OPRT_INVALID_PARM :
           (os_mutex_pend(&mutex->mutex, 0) == 0 ? OPRT_OK : OPRT_OS_ADAPTER_MUTEX_LOCK_FAILED);
}

OPERATE_RET tkl_mutex_trylock(const TKL_MUTEX_HANDLE handle)
{
    JIELI_TKL_MUTEX *mutex = (JIELI_TKL_MUTEX *)handle;
    /* KNOWN ISSUE - nothing in-tree calls tal_mutex_trylock() today, so this is
     * latent. os_mutex_accept() is not portable: on AC79NN it returns 0 on
     * success and OS_TIMEOUT on failure, but on AC792N it is a tail call to
     * uCOS-II OSMutexAccept(), whose non-zero-means-success sense is inverted -
     * so a held lock would be reported free and vice versa.
     *
     * Unlike the semaphore case, os_mutex_pend(m, -1) is NOT a non-blocking
     * alternative: it still blocks on AC792N. Fixing this needs the same
     * one-time runtime probe jieli_tkl_sem_accept() uses, applied to
     * os_mutex_accept(). Deferred until something actually needs trylock. */
    return mutex == NULL ? OPRT_INVALID_PARM :
           (os_mutex_accept(&mutex->mutex) == 0 ? OPRT_OK : OPRT_OS_ADAPTER_MUTEX_LOCK_FAILED);
}

OPERATE_RET tkl_mutex_unlock(const TKL_MUTEX_HANDLE handle)
{
    JIELI_TKL_MUTEX *mutex = (JIELI_TKL_MUTEX *)handle;
    return mutex == NULL ? OPRT_INVALID_PARM :
           (os_mutex_post(&mutex->mutex) == 0 ? OPRT_OK : OPRT_OS_ADAPTER_MUTEX_UNLOCK_FAILED);
}

OPERATE_RET tkl_mutex_release(const TKL_MUTEX_HANDLE handle)
{
    JIELI_TKL_MUTEX *mutex = (JIELI_TKL_MUTEX *)handle;
    int result;
    if (mutex == NULL) {
        return OPRT_INVALID_PARM;
    }
    result = os_mutex_del(&mutex->mutex, OS_DEL_ALWAYS);
    free(mutex);
    return result == 0 ? OPRT_OK : OPRT_OS_ADAPTER_MUTEX_RELEASE_FAILED;
}
