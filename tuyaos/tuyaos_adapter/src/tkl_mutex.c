#include "tkl_mutex.h"

#include "jieli_tkl_os.h"
#include "tuya_error_code.h"

#include <stdlib.h>

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
    return mutex == NULL ? OPRT_INVALID_PARM :
           (os_mutex_pend(&mutex->mutex, 0) == 0 ? OPRT_OK : OPRT_OS_ADAPTER_MUTEX_LOCK_FAILED);
}

OPERATE_RET tkl_mutex_trylock(const TKL_MUTEX_HANDLE handle)
{
    JIELI_TKL_MUTEX *mutex = (JIELI_TKL_MUTEX *)handle;
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
