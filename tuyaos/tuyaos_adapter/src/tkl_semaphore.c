#include "tkl_semaphore.h"

#include "jieli_tkl_os.h"
#include "tuya_error_code.h"

#include <stdlib.h>

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
    result = os_sem_pend(&sem->sem, jieli_tkl_timeout_to_ticks(timeout));
    if (result == -2) {
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
