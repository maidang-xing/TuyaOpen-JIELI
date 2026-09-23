#ifndef __PJ_CONFIG_SITE_H__
#define __PJ_CONFIG_SITE_H__

/*
 * pj/config_site.h is included after pj/config.h has already selected the
 * generic PJ_LINUX/PJ_M_I386 compatibility headers. Undefine any defaults we
 * intentionally override so Clang doesn't emit -Wmacro-redefined warnings.
 */
#ifdef PJ_OS_NAME
#undef PJ_OS_NAME
#endif
#ifdef PJ_M_NAME
#undef PJ_M_NAME
#endif
#ifdef PJ_IS_LITTLE_ENDIAN
#undef PJ_IS_LITTLE_ENDIAN
#endif
#ifdef PJ_IS_BIG_ENDIAN
#undef PJ_IS_BIG_ENDIAN
#endif
#ifdef PJ_HAS_HIGH_RES_TIMER
#undef PJ_HAS_HIGH_RES_TIMER
#endif
#ifdef PJ_HAS_PENTIUM
#undef PJ_HAS_PENTIUM
#endif
#ifdef PJ_HAS_THREADS
#undef PJ_HAS_THREADS
#endif
#ifdef PJ_HAS_SEMAPHORE
#undef PJ_HAS_SEMAPHORE
#endif
#ifdef PJ_EMULATE_RWMUTEX
#undef PJ_EMULATE_RWMUTEX
#endif
#ifdef PJ_THREAD_SET_STACK_SIZE
#undef PJ_THREAD_SET_STACK_SIZE
#endif
#ifdef PJ_THREAD_ALLOCATE_STACK
#undef PJ_THREAD_ALLOCATE_STACK
#endif
#ifdef PJ_HAS_MALLOC
#undef PJ_HAS_MALLOC
#endif
#ifdef PJ_HAS_STRING_H
#undef PJ_HAS_STRING_H
#endif
#ifdef PJ_HAS_STDIO_H
#undef PJ_HAS_STDIO_H
#endif
#ifdef PJ_HAS_STDARG_H
#undef PJ_HAS_STDARG_H
#endif
#ifdef PJ_HAS_LIMITS_H
#undef PJ_HAS_LIMITS_H
#endif
#ifdef PJ_HAS_STDLIB_H
#undef PJ_HAS_STDLIB_H
#endif
#ifdef PJ_ATOMIC_VALUE_TYPE
#undef PJ_ATOMIC_VALUE_TYPE
#endif
#ifdef PJ_NATIVE_ERR_POSITIVE
#undef PJ_NATIVE_ERR_POSITIVE
#endif
#ifdef pj_get_native_os_error
#undef pj_get_native_os_error
#endif
#ifdef pj_get_native_netos_error
#undef pj_get_native_netos_error
#endif
#ifdef PJ_HAS_SOCKLEN_T
#undef PJ_HAS_SOCKLEN_T
#endif
#ifdef PJ_SOCKADDR_HAS_LEN
#undef PJ_SOCKADDR_HAS_LEN
#endif
#ifdef PJ_SOCK_HAS_INET_ATON
#undef PJ_SOCK_HAS_INET_ATON
#endif
#ifdef PJ_SOCK_HAS_INET_PTON
#undef PJ_SOCK_HAS_INET_PTON
#endif
#ifdef PJ_SOCK_HAS_INET_NTOP
#undef PJ_SOCK_HAS_INET_NTOP
#endif
#ifdef PJ_SOCK_HAS_GETADDRINFO
#undef PJ_SOCK_HAS_GETADDRINFO
#endif
#ifdef PJ_HAS_SYS_TYPES_H
#undef PJ_HAS_SYS_TYPES_H
#endif
#ifdef PJ_HAS_SYS_SOCKET_H
#undef PJ_HAS_SYS_SOCKET_H
#endif
#ifdef PJ_HAS_LINUX_SOCKET_H
#undef PJ_HAS_LINUX_SOCKET_H
#endif
#ifdef PJ_HAS_SYS_SELECT_H
#undef PJ_HAS_SYS_SELECT_H
#endif
#ifdef PJ_HAS_NETINET_IN_H
#undef PJ_HAS_NETINET_IN_H
#endif
#ifdef PJ_HAS_NETINET_IN_SYSTM_H
#undef PJ_HAS_NETINET_IN_SYSTM_H
#endif
#ifdef PJ_HAS_NETINET_IP_H
#undef PJ_HAS_NETINET_IP_H
#endif
#ifdef PJ_HAS_NETINET_TCP_H
#undef PJ_HAS_NETINET_TCP_H
#endif
#ifdef PJ_HAS_NET_IF_H
#undef PJ_HAS_NET_IF_H
#endif
#ifdef PJ_HAS_IFADDRS_H
#undef PJ_HAS_IFADDRS_H
#endif
#ifdef PJ_HAS_ARPA_INET_H
#undef PJ_HAS_ARPA_INET_H
#endif
#ifdef PJ_HAS_SYS_IOCTL_H
#undef PJ_HAS_SYS_IOCTL_H
#endif
#ifdef PJ_HAS_NETDB_H
#undef PJ_HAS_NETDB_H
#endif
#ifdef PJ_HAS_UNISTD_H
#undef PJ_HAS_UNISTD_H
#endif
#ifdef PJ_HAS_SYS_FILIO_H
#undef PJ_HAS_SYS_FILIO_H
#endif
#ifdef PJ_HAS_SYS_SOCKIO_H
#undef PJ_HAS_SYS_SOCKIO_H
#endif


/* Platform identification */
#define PJ_OS_NAME "wl83"
#define PJ_M_NAME "pi32v2"

/* Endianness */
#define PJ_IS_LITTLE_ENDIAN 1
#define PJ_IS_BIG_ENDIAN 0

/* High resolution timer */
#define PJ_HAS_HIGH_RES_TIMER 1
#define PJ_HAS_PENTIUM 0

/* Threading and synchronization */
#define PJ_HAS_THREADS 1
#define PJ_HAS_SEMAPHORE 1
#define PJ_EMULATE_RWMUTEX 1
#define PJ_THREAD_SET_STACK_SIZE 0
#define PJ_THREAD_ALLOCATE_STACK 0

/* Standard library features */
#define PJ_HAS_MALLOC 1
#define PJ_HAS_STRING_H 1
#define PJ_HAS_LIMITS_H 1
#define PJ_HAS_STDIO_H 1
#define PJ_HAS_STDARG_H 1
#define PJ_HAS_STDLIB_H 1

/* Atomic operations */
#define PJ_ATOMIC_VALUE_TYPE long

/* Error handling */
#define PJ_NATIVE_ERR_POSITIVE 1
#define pj_get_native_os_error() (errno)
#define pj_get_native_netos_error() (errno)

/* Socket features */
#define PJ_HAS_SOCKLEN_T 1
#define PJ_SOCKADDR_HAS_LEN 1
#define PJ_SOCK_HAS_INET_ATON 0
#define PJ_SOCK_HAS_INET_PTON 0
#define PJ_SOCK_HAS_INET_NTOP 0
#define PJ_SOCK_HAS_GETADDRINFO 0

/* Disable standard POSIX socket headers (use WL83's lwip instead) */
#define PJ_HAS_SYS_TYPES_H 0
#define PJ_HAS_SYS_SOCKET_H 0
#define PJ_HAS_LINUX_SOCKET_H 0
#define PJ_HAS_SYS_SELECT_H 0
#define PJ_HAS_NETINET_IN_H 0
#define PJ_HAS_NETINET_IN_SYSTM_H 0
#define PJ_HAS_NETINET_IP_H 0
#define PJ_HAS_NETINET_TCP_H 0
#define PJ_HAS_NET_IF_H 0
#define PJ_HAS_IFADDRS_H 0
#define PJ_HAS_ARPA_INET_H 0
#define PJ_HAS_SYS_IOCTL_H 0
#define PJ_HAS_NETDB_H 0
#define PJ_HAS_UNISTD_H 0
#define PJ_HAS_SYS_FILIO_H 0
#define PJ_HAS_SYS_SOCKIO_H 0

/* Use WL83's lwip socket headers */
#include "lwip/sockets.h"
#include "lwip/netdb.h"

/* Disable features not needed */
#define PJ_HAS_SSL_SOCK 0
#define PJMEDIA_HAS_VIDEO 0
#define PJMEDIA_HAS_SRTP 0
#define PJSIP_HAS_TLS_TRANSPORT 0
#define PJ_HAS_IPV6 0
#define PJMEDIA_AUDIO_DEV_HAS_WMME 0
#define PJMEDIA_AUDIO_DEV_HAS_WASAPI 0
#define PJMEDIA_AUDIO_DEV_HAS_WL83 1

/* Memory optimization */
#define PJ_LOG_MAX_LEVEL 5
#define PJSIP_MAX_TSX_COUNT 4
#define PJSIP_MAX_DIALOG_COUNT 2
#define PJMEDIA_SOUND_BUFFER_COUNT 4
#define PJ_IOQUEUE_MAX_HANDLES 16
#define PJ_LOG_MAX_SIZE 2048

/* Pool configuration */
#define PJ_POOL_ALIGNMENT 4

/* Maximum object name length */
#define PJ_MAX_OBJ_NAME 32

#endif
