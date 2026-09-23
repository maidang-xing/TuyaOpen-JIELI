#ifndef SYS_INIT_H
#define SYS_INIT_H







typedef int (*initcall_t)(void);

struct initcall_entry {
    initcall_t func;
    const char *name;
};

#define __initcall(fn)  \
	const struct initcall_entry __initcall_##fn SEC_USED(.initcall) = {fn, #fn}

#define early_initcall(fn)  \
	const struct initcall_entry __initcall_##fn SEC_USED(.early.initcall) = {fn, #fn}

#define late_initcall(fn)  \
	const struct initcall_entry __initcall_##fn SEC_USED(.late.initcall) = {fn, #fn}

#define platform_initcall(fn) \
	const struct initcall_entry __initcall_##fn SEC_USED(.platform.initcall) = {fn, #fn}

#define module_initcall(fn) \
	const struct initcall_entry __initcall_##fn SEC_USED(.module.initcall) = {fn, #fn}



extern const int config_initcall_echo_fun_name;

#define __do_initcall(prefix) \
    do { \
        struct initcall_entry *init; \
        extern struct initcall_entry prefix##_begin[], prefix##_end[]; \
        for (init=prefix##_begin; init<prefix##_end; init++) { \
            if (config_initcall_echo_fun_name) { \
                printf("%s: %s\n", #prefix, init->name); \
            } \
            (init->func)(); \
        } \
    }while(0)







#endif

