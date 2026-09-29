set(JIELI_ADAPTER_NAME jieli_tuya_adapter)

if(CONFIG_CHIP_CHOICE STREQUAL "wl82")
    set(JIELI_SELECTED_CHIP_DEFINE JIELI_SELECTED_CHIP_WL82)
elseif(CONFIG_CHIP_CHOICE STREQUAL "wl83")
    set(JIELI_SELECTED_CHIP_DEFINE JIELI_SELECTED_CHIP_WL83)
else()
    message(FATAL_ERROR "JIELI requires CONFIG_CHIP_CHOICE to be wl82 or wl83")
endif()

file(STRINGS "${CMAKE_CURRENT_LIST_DIR}/adapter_sources.txt" JIELI_ADAPTER_RELATIVE_SRC
    REGEX "^[^#].*\\.c$")
set(JIELI_ADAPTER_SRC)
foreach(source IN LISTS JIELI_ADAPTER_RELATIVE_SRC)
    if(source MATCHES "^src/chip/(wl82|wl83)/")
        set(source_chip "${CMAKE_MATCH_1}")
        if(NOT source_chip STREQUAL "${CONFIG_CHIP_CHOICE}")
            continue()
        endif()
    endif()
    list(APPEND JIELI_ADAPTER_SRC "${CMAKE_CURRENT_LIST_DIR}/${source}")
endforeach()

file(GLOB JIELI_ADAPTER_INCLUDE_ENTRIES LIST_DIRECTORIES true
    "${CMAKE_CURRENT_LIST_DIR}/include/*")
set(JIELI_ADAPTER_INCLUDE_DIRS)
foreach(include_entry IN LISTS JIELI_ADAPTER_INCLUDE_ENTRIES)
    if(IS_DIRECTORY "${include_entry}")
        list(APPEND JIELI_ADAPTER_INCLUDE_DIRS "${include_entry}")
    endif()
endforeach()
list(APPEND JIELI_ADAPTER_INCLUDE_DIRS "${CMAKE_CURRENT_LIST_DIR}/include/init/include")

add_library(${JIELI_ADAPTER_NAME} STATIC ${JIELI_ADAPTER_SRC})
target_compile_definitions(${JIELI_ADAPTER_NAME} PRIVATE "${JIELI_SELECTED_CHIP_DEFINE}=1")
target_include_directories(${JIELI_ADAPTER_NAME}
    PUBLIC
        ${CMAKE_CURRENT_LIST_DIR}/include
        ${JIELI_ADAPTER_INCLUDE_DIRS}
        ${TOP_SOURCE_DIR}/tools/porting/adapter/system
        ${TOP_SOURCE_DIR}/tools/porting/adapter/uart
        ${TOP_SOURCE_DIR}/tools/porting/adapter/init/include
        ${TOP_SOURCE_DIR}/tools/porting/adapter/utilities/include
        ${TOP_SOURCE_DIR}/tools/porting/adapter/security
        ${TOP_SOURCE_DIR}/tools/porting/adapter/flash
        ${TOP_SOURCE_DIR}/tools/porting/adapter/network
        ${TOP_SOURCE_DIR}/tools/porting/adapter/wifi
        ${TOP_SOURCE_DIR}/tools/porting/adapter/bluetooth
        ${TOP_SOURCE_DIR}/tools/porting/adapter/timer
        ${TOP_SOURCE_DIR}/src/common/include
        ${JIELI_SDK_ROOT}/include_lib
        ${JIELI_SDK_ROOT}/include_lib/btstack
        ${JIELI_SDK_ROOT}/include_lib/btstack/le
        ${JIELI_SDK_ROOT}/include_lib/btctrler
        ${JIELI_SDK_ROOT}/include_lib/btctrler/port/${JIELI_CPU}
        ${JIELI_SDK_ROOT}/include_lib/net
        ${JIELI_SDK_ROOT}/include_lib/driver
        ${JIELI_SDK_ROOT}/include_lib/driver/device
        ${JIELI_SDK_ROOT}/include_lib/driver/cpu/${JIELI_CPU}
        ${JIELI_SDK_ROOT}/include_lib/system
        ${JIELI_SDK_ROOT}/include_lib/utils
        ${JIELI_SDK_ROOT}/include_lib/utils/syscfg
        ${JIELI_SDK_ROOT}/include_lib/utils/event
        ${JIELI_SDK_ROOT}/include_lib/net/lwip_2_2_0
        ${JIELI_SDK_ROOT}/include_lib/net/lwip_2_2_0/lwip/src/include
        ${JIELI_SDK_ROOT}/include_lib/net/lwip_2_2_0/lwip/src/include/compat
        ${JIELI_SDK_ROOT}/include_lib/net/lwip_2_2_0/lwip/port
)
