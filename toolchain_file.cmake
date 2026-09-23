set(CMAKE_SYSTEM_NAME Generic)
set(CMAKE_SYSTEM_PROCESSOR pi32v2)

if(DEFINED ENV{JIELI_SDK_ROOT})
    set(JIELI_SDK_ROOT "$ENV{JIELI_SDK_ROOT}")
elseif(CONFIG_CHIP_WL83 AND EXISTS "${PLATFORM_PATH}/chip/wl83/AC792_SDK/sdk/Makefile")
    set(JIELI_SDK_ROOT "${PLATFORM_PATH}/chip/wl83/AC792_SDK/sdk")
elseif(EXISTS "${PLATFORM_PATH}/chip/wl82/AC79_AIoT_SDK")
    set(JIELI_SDK_ROOT "${PLATFORM_PATH}/chip/wl82/AC79_AIoT_SDK")
elseif(EXISTS "${PLATFORM_PATH}/AC79_AIoT_SDK")
    set(JIELI_SDK_ROOT "${PLATFORM_PATH}/AC79_AIoT_SDK")
else()
    set(JIELI_SDK_ROOT "${PLATFORM_PATH}/../../../AC79_AIoT_SDK")
endif()
if(CONFIG_CHIP_WL83 OR CONFIG_CHIP_CHOICE STREQUAL "wl83")
    set(JIELI_CPU wl83)
else()
    set(JIELI_CPU wl82)
endif()
string(TOUPPER "${JIELI_CPU}" JIELI_CPU_DEFINE)
file(TO_CMAKE_PATH "${JIELI_SDK_ROOT}" JIELI_SDK_ROOT)
set(JIELI_SDK_ROOT "${JIELI_SDK_ROOT}" CACHE PATH "JieLi SDK root" FORCE)

if(DEFINED ENV{JIELI_TOOL_DIR})
    set(JIELI_TOOL_DIR "$ENV{JIELI_TOOL_DIR}")
elseif(EXISTS "C:/JL/pi32/bin/clang.exe")
    # Match jieli_build.py's Windows toolchain discovery.
    set(JIELI_TOOL_DIR "C:/JL/pi32/bin")
elseif(EXISTS "${JIELI_SDK_ROOT}/../ipc_ac7916a/toolchain/jieli-linux-toolchains/pi32v2/bin/clang.exe")
    set(JIELI_TOOL_DIR "${JIELI_SDK_ROOT}/../ipc_ac7916a/toolchain/jieli-linux-toolchains/pi32v2/bin")
else()
    set(JIELI_TOOL_DIR "${PLATFORM_PATH}/../../jieli-toolchain/pi32v2/bin")
endif()
file(TO_CMAKE_PATH "${JIELI_TOOL_DIR}" JIELI_TOOL_DIR)

if(CMAKE_HOST_WIN32)
    set(CMAKE_C_COMPILER "${JIELI_TOOL_DIR}/clang.exe")
    set(CMAKE_CXX_COMPILER "${JIELI_TOOL_DIR}/clang.exe")
    set(CMAKE_AR "${PLATFORM_PATH}/jieli_llvm_ar.cmd")
    set(CMAKE_RANLIB "${PLATFORM_PATH}/jieli_ranlib.cmd")
else()
    set(CMAKE_C_COMPILER "${JIELI_TOOL_DIR}/clang")
    set(CMAKE_CXX_COMPILER "${JIELI_TOOL_DIR}/clang")
    set(CMAKE_AR "${JIELI_TOOL_DIR}/lto-ar")
    set(CMAKE_RANLIB "${PLATFORM_PATH}/jieli_ranlib.sh")
endif()

set(JIELI_NEWLIB_INCLUDE "${JIELI_SDK_ROOT}/include_lib/newlib/include")
set(JIELI_CPP_INCLUDE "${JIELI_SDK_ROOT}/include_lib/c++/include")
set(JIELI_C_INCLUDE_FLAGS "-isystem${JIELI_NEWLIB_INCLUDE}")
set(JIELI_CXX_INCLUDE_FLAGS
    "-isystem${JIELI_NEWLIB_INCLUDE} -isystem${JIELI_CPP_INCLUDE}")
set(JIELI_COMMON_DEFINES
    "-DCONFIG_CPU_${JIELI_CPU_DEFINE} -DCONFIG_FREE_RTOS_ENABLE -DCONFIG_THREAD_ENABLE -DBOOL_DEFINE_CONFLICT -DMBEDTLS_TCPIP_LWIP -D_GNU_SOURCE -D_XOPEN_SOURCE=700 -D__ELF__")

set(CMAKE_C_FLAGS
    "-target pi32v2 -integrated-as -mcpu=r3 -mfprev1 -Oz -flto -fno-common -ffunction-sections -fdata-sections -fno-unwind-tables -include stdbool.h -D__GCC_PI32V2__ ${JIELI_COMMON_DEFINES} ${JIELI_C_INCLUDE_FLAGS}")
set(CMAKE_CXX_FLAGS
    "-target pi32v2 -integrated-as -mcpu=r3 -mfprev1 -Oz -flto -fno-common -ffunction-sections -fdata-sections -fno-unwind-tables -fno-exceptions -fno-rtti -std=gnu++14 -D__GCC_PI32V2__ ${JIELI_COMMON_DEFINES} ${JIELI_CXX_INCLUDE_FLAGS}")

if(NOT EXISTS "${CMAKE_C_COMPILER}")
    message(FATAL_ERROR
        "Jieli clang not found: ${CMAKE_C_COMPILER}. "
        "Set JIELI_TOOL_DIR to pi32v2/bin before building.")
endif()

set(CMAKE_C_COMPILER_WORKS 1)
set(CMAKE_CXX_COMPILER_WORKS 1)
