# Jieli TKL 适配层结构重构方案

> 状态：方案已确认并实施。逐项执行与构建验证记录见 `docs/superpowers/plans/2026-09-29-jieli-tkl-adapter-refactor.md`。

## 目标

AC791（WL82）与 AC792（WL83）共用一个 `platform/JIELI`。TuyaOpen 通过按域组织的 TKL 头文件调用适配层；每个 `tkl_*.c` 负责该接口的状态、参数和行为。WL82/WL83 的少量 SDK 差异在 TKL 源文件中用编译期芯片选择处理；只有直接调用厂商 SDK 的代码确实不同且不适合放在共用 TKL 文件时，才保留芯片专属 `.c`。

本次迁移私有实现细节，不改变公开 TKL API、MAC 生成规则、UART 端口映射、联网行为、芯片选择或 SDK 调用时序。统一 `app_main()` 和构建工具重构不在范围内。

## 参考结论

- T5AI 按 `include/<域>/tkl_*.h` 组织 TKL 接口；队列、信号量的实现结构以及 UART 的私有辅助逻辑定义在各自 `tkl_*.c` 中。
- TuyaOpen-esp32 也把 Wi-Fi 状态、UART 配置、队列和信号量实现放在对应 `tkl_*.c`。
- 因此 Jieli 不保留实现私有头文件。类型、宏和单文件辅助函数留在所属 `.c`；一个 TKL 域需要另一个域的功能时，优先调用已声明的 TKL 接口，避免新增无共同声明的私有跨文件函数。

参考源码：TuyaOpen 的 `platform/T5AI/tuyaos/tuyaos_adapter/src/{system,driver}/tkl_*.c`；[TuyaOpen-esp32 `tkl_uart.c`](https://github.com/tuya/TuyaOpen-esp32/blob/master/tuya_open_sdk/tuyaos_adapter/src/drivers/tkl_uart.c)、[`tkl_wifi.c`](https://github.com/tuya/TuyaOpen-esp32/blob/master/tuya_open_sdk/tuyaos_adapter/src/drivers/tkl_wifi.c)、[`tkl_queue.c`](https://github.com/tuya/TuyaOpen-esp32/blob/master/tuya_open_sdk/tuyaos_adapter/src/system/tkl_queue.c)。

## 重构前仓库状态与实施后结构

重构前，`tuyaos/tuyaos_adapter/include/` 只有 `tuyaopen_license.h` 和 Jieli 私有辅助头文件，没有本地 TKL 接口头文件。当前实现保留授权扩展头文件，维护 15 个按域组织的 TKL 兼容头文件，并删除 Jieli 私有辅助头文件。

```text
tuyaos/tuyaos_adapter/
├── include/
│   ├── bluetooth/tkl_bluetooth.h       # 与 TuyaOpen 公共接口同步的兼容快照
│   ├── flash/tkl_flash.h
│   ├── init/include/tkl_init.h         # 沿用 T5AI 的 init 目录布局
│   ├── network/tkl_network.h
│   ├── system/
│   │   ├── tkl_memory.h
│   │   ├── tkl_mutex.h
│   │   ├── tkl_ota.h
│   │   ├── tkl_output.h
│   │   ├── tkl_queue.h
│   │   ├── tkl_semaphore.h
│   │   ├── tkl_sleep.h
│   │   └── tkl_thread.h
│   ├── system/tkl_system.h
│   ├── uart/tkl_uart.h
│   ├── wifi/tkl_wifi.h
│   └── tuyaopen_license.h              # 已有：保留，供主仓授权代码调用
├── src/
│   ├── driver/                          # tkl_bluetooth/flash/network/ota/uart/wifi.c
│   ├── system/                          # tkl_assert/mutex/output/queue/semaphore/sleep/system/thread.c
│   │                                    # tuyaopen_license.c 保留
├── CMakeLists.txt
└── adapter_sources.txt
```

迁移后不保留实现私有头文件。`src/misc/jieli_dev_mac.c` 的逻辑并入 Wi-Fi/Bluetooth TKL 实现；`src/driver/jieli_bluetooth_backend.c` 并入 `tkl_bluetooth.c`；Wi-Fi 状态映射并入 `tkl_wifi.c`；UART 端口和 ioctl 映射并入 `tkl_uart.c`。Flash UID 的 WL82/WL83 调用共用同一 SDK 头文件和 UID 类型，仅调用参数不同，因此用已选芯片宏在 `tkl_wifi.c` 内选择调用，不再为它保留跨文件私有符号。

调用链固定为：`TuyaOpen → include/<域>/tkl_*.h → 对应 tkl_*.c → 杰理 SDK`。WL82/WL83 共享 TKL 行为；小型 SDK 差异在 TKL `.c` 编译期分支，复杂且不适合放入共用 TKL 文件的差异才单独拆芯片源文件。

## 实施规则

1. **TKL 头文件来源**：从配套 TuyaOpen 分支的 `tools/porting/adapter/` 同步当前公共接口头文件；不能直接复制 T5AI 上可能已分叉的版本。只新增本仓适配源实际包含或 TuyaOpen 适配构建实际需要的接口。
2. **公开头文件**：`include/<域>/` 只放 `tkl_*.h`；现有 `include/tuyaopen_license.h` 保留为主仓授权模块使用的 Jieli 扩展，不改名、不移动。
3. **私有实现**：OS 对象结构、MAC 状态、UART 端口上限、芯片宏判断、状态转换和辅助函数放在负责该行为的 `tkl_*.c`。不为这些实现细节新建 `.h`。
4. **芯片差异**：Kconfig/CMake 的 `CONFIG_CHIP_CHOICE` 是 WL82/WL83 的唯一选择来源。端口号、ioctl 常量、状态枚举及 Flash UID 调用等小型差异在相应 TKL `.c` 内使用编译期分支；只有厂商 SDK 调用较大或 API 类型不同、不适合放在共用 TKL 文件时，才留在 `src/chip/wl82/`、`src/chip/wl83/`。跨域系统功能通过公开 TKL 接口组合，不新增无共同声明的私有 helper。
5. **MAC**：Wi-Fi MAC 派生、缓存和覆盖由 `tkl_wifi.c` 管理；Bluetooth 使用 TKL Wi-Fi MAC 作为派生基址，按当前算法产生 BLE static-random 地址。保持现有地址规则和初始化时序。
6. **构建包含路径**：CMake 和 SDK staging 构建都优先搜索 Jieli 本地 TKL 头文件，再搜索 TuyaOpen 通用头文件。CMake 还要显式加入 `include/init/include/`；公共 include 路径中不得出现实现私有目录。
7. **源码清单**：把迁入 TKL 文件的 helper 从 `adapter_sources.txt` 移除。当前 WL82/WL83 使用相同的共享 TKL 源码清单，芯片选择用于确定 SDK 和 TKL 源码中的编译期分支；当前没有 `src/chip/` 专属 helper 源文件。若后续新增无法放入共享 TKL 文件的芯片专属实现，才按选择加入对应源码。

## 实施步骤

1. 以当前 TuyaOpen 公共 TKL 头文件为基线，新增上面列出的按域接口头文件并核对声明一致。
2. 调整 CMake 与 SDK staging 的头文件搜索顺序，确认两种构建路径都解析到 Jieli 本地 TKL 头文件。
3. 将私有类型、宏和小型 helper 移入所属 TKL `.c`；合并 MAC、Bluetooth、Wi-Fi 状态和 UART 映射实现，保留必要的芯片专属 SDK 调用。
4. 删除 Jieli 私有辅助头文件及已合并的 helper `.c`，更新 `adapter_sources.txt` 和相关构建文件。
5. 分别使用 AC791（WL82）和 AC792（WL83）配置构建 switch demo，检查编译源清单和 include 解析路径。

## 验收标准

- `include/` 中只有按域组织的 TKL 接口头文件和现有 `tuyaopen_license.h`；没有 Jieli 私有辅助头文件。
- MAC、UART、Wi-Fi 状态映射等公共 TKL 行为由各自 `tkl_*.c` 实现；当前源码清单没有芯片专属 helper 源文件。
- 队列通过 TKL semaphore 接口复用等待/释放行为；Flash UID 的小型 SDK 差异在 `tkl_wifi.c` 内分支，不留无共同声明的私有跨文件 helper。
- CMake 与 SDK staging 均优先解析本地 TKL 头文件；WL82/WL83 使用相同的共享 TKL 源码清单，并分别选择对应的 SDK 和编译期分支。
- AC791 与 AC792 的 switch demo 均能编译；日志、MAC、Wi-Fi/BLE、配网和授权行为与迁移前一致。
- 本次不修改 TuyaOpen 公共 TKL API，不改 SDK，不改业务联网逻辑或 `app_main()`。
