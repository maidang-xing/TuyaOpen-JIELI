#include "tkl_thread.h"

#include "jieli_tkl_os.h"
#include "tuya_error_code.h"

#include <stdlib.h>
#include <string.h>

static JIELI_TKL_THREAD s_current_thread;

static u8 jieli_tkl_map_priority(uint32_t priority)
{
    if (priority > 5u) {
        priority = 5u;
    }
    return (u8)(10u + (5u - priority));
}

static void jieli_tkl_thread_entry(void *arg)
{
    JIELI_TKL_THREAD *thread = (JIELI_TKL_THREAD *)arg;
    if (thread != NULL && thread->func != NULL) {
        thread->func(thread->arg);
    }
    os_task_del_res(OS_TASK_SELF);
}

OPERATE_RET tkl_thread_create(TKL_THREAD_HANDLE *thread, const char *name, uint32_t stack_size,
                              uint32_t priority, const THREAD_FUNC_T func, void *const arg)
{
    JIELI_TKL_THREAD *jieli_thread;
    if (thread == NULL || func == NULL) {
        return OPRT_INVALID_PARM;
    }
    jieli_thread = calloc(1, sizeof(*jieli_thread));
    if (jieli_thread == NULL) {
        return OPRT_OS_ADAPTER_THRD_CREAT_FAILED;
    }
    jieli_thread->magic = JIELI_TKL_THREAD_MAGIC;
    jieli_thread->func = func;
    jieli_thread->arg = arg;
    strncpy(jieli_thread->name, (name != NULL && name[0] != '\0') ? name : "tuya",
            sizeof(jieli_thread->name) - 1u);
    if (os_task_create(jieli_tkl_thread_entry, jieli_thread, jieli_tkl_map_priority(priority),
                       (stack_size + 3u) / 4u, 0, jieli_thread->name) != 0) {
        free(jieli_thread);
        return OPRT_OS_ADAPTER_THRD_CREAT_FAILED;
    }
    *thread = (TKL_THREAD_HANDLE)jieli_thread;
    return OPRT_OK;
}

OPERATE_RET tkl_thread_release(const TKL_THREAD_HANDLE thread)
{
    JIELI_TKL_THREAD *jieli_thread = (JIELI_TKL_THREAD *)thread;
    int result;
    if (jieli_thread == NULL || jieli_thread->magic != JIELI_TKL_THREAD_MAGIC) {
        return OPRT_INVALID_PARM;
    }
    if (jieli_thread == &s_current_thread) {
        return os_task_del_req(jieli_thread->name) == 0 ? OPRT_OK : OPRT_OS_ADAPTER_THRD_RELEASE_FAILED;
    }
    result = os_task_del_req(jieli_thread->name);
    free(jieli_thread);
    return result == 0 ? OPRT_OK : OPRT_OS_ADAPTER_THRD_RELEASE_FAILED;
}

OPERATE_RET tkl_thread_get_watermark(const TKL_THREAD_HANDLE thread, uint32_t *watermark)
{
    (void)thread;
    if (watermark == NULL) {
        return OPRT_INVALID_PARM;
    }
    *watermark = 0;
    return OPRT_NOT_SUPPORTED;
}

OPERATE_RET tkl_thread_get_id(TKL_THREAD_HANDLE *thread)
{
    if (thread == NULL) {
        return OPRT_INVALID_PARM;
    }
    const char *name = os_current_task();
    if (name == NULL) {
        return OPRT_OS_ADAPTER_THRD_JUDGE_SELF_FAILED;
    }
    memset(&s_current_thread, 0, sizeof(s_current_thread));
    s_current_thread.magic = JIELI_TKL_THREAD_MAGIC;
    strncpy(s_current_thread.name, name, sizeof(s_current_thread.name) - 1u);
    *thread = (TKL_THREAD_HANDLE)&s_current_thread;
    return OPRT_OK;
}

OPERATE_RET tkl_thread_set_self_name(const char *name)
{
    (void)name;
    return name == NULL ? OPRT_INVALID_PARM : OPRT_NOT_SUPPORTED;
}

OPERATE_RET tkl_thread_is_self(TKL_THREAD_HANDLE thread, BOOL_T *is_self)
{
    if (thread == NULL || is_self == NULL) {
        return OPRT_INVALID_PARM;
    }
    JIELI_TKL_THREAD *jieli_thread = (JIELI_TKL_THREAD *)thread;
    const char *current = os_current_task();
    if (jieli_thread->magic != JIELI_TKL_THREAD_MAGIC || current == NULL) {
        return OPRT_INVALID_PARM;
    }
    *is_self = strcmp(jieli_thread->name, current) == 0 ? TRUE : FALSE;
    return OPRT_OK;
}

OPERATE_RET tkl_thread_get_priority(TKL_THREAD_HANDLE thread, int *priority)
{
    (void)thread;
    (void)priority;
    return OPRT_NOT_SUPPORTED;
}

OPERATE_RET tkl_thread_set_priority(TKL_THREAD_HANDLE thread, int priority)
{
    (void)thread;
    (void)priority;
    return OPRT_NOT_SUPPORTED;
}

OPERATE_RET tkl_thread_diagnose(TKL_THREAD_HANDLE thread)
{
    (void)thread;
    return OPRT_NOT_SUPPORTED;
}
