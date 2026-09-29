# JieLi 平台：AC79_DevKitBoard 与 AC792N_Develop_Board

| 统一板名 | 芯片/平台 | 状态 | SDK |
| --- | --- | --- | --- |
| `AC79_DevKitBoard` | AC791 / WL82 | 完整 TuyaOpen `switch_demo` 构建入口已验证；历史别名 `AC7916A` 保留 | `chip/wl82/AC79_AIoT_SDK`（`release/AC79NN_SDK_V1.2.0`，tag `AC79NN_SDK_V1.2.13_2026-04-20`）|
| `AC792N_Develop_Board` | AC792N / WL83 | 完整 `switch_demo` 已在 Windows 构建并 USB 烧录；此前实板日志验证 Wi-Fi、Tuya 激活与 DP 收发，最新 UART0/115200 固件需补抓启动日志 | `chip/wl83/AC792_SDK`（`release/AC792N_SDK_V3`，tag `AC792N_SDK_BETA_V3.1.7_2026-08-25`）|

所有工程均从 TuyaOpen 仓库根目录或示例目录使用 `tos.py`。Windows 是当前支持的烧录环境。AC79 与 AC792 SDK 源码直接纳入 JieLi 平台仓库的 `chip/` 目录，不使用 Git submodule；AC79 SDK 中当前未使用的 `libmatter.a` 按项目约定忽略，不提交。本地工具链默认从 `C:\\JL\\pi32\\bin` 查找，也可设置 `JIELI_TOOL_DIR`。

## 选择板卡与构建

AC79 完整应用（例如 `apps/tuya_cloud/switch_demo`）：

```powershell
tos.py config set CONFIG_BOARD_CHOICE_AC79_DEVKITBOARD=y CONFIG_JIELI_UART_LOG_PORT=1 CONFIG_JIELI_UART_LOG_BAUDRATE=115200
tos.py build
```

AC792 完整 Tuya `switch_demo`：

```powershell
tos.py config set CONFIG_BOARD_CHOICE_AC792N_DEVELOP_BOARD=y CONFIG_JIELI_UART_LOG_PORT=0 CONFIG_JIELI_UART_LOG_BAUDRATE=115200
tos.py build
```

该镜像包含 Tuya TKL Wi-Fi/BLE、BLE 配网、Tuya IoT 和 `switch_demo` DP 业务。AC792 SDK 的 WPA/SAE 还需链接 `libcrypto_mbedtls.a`。2026-09-24 已完成完整镜像构建，并由 `tos.py flash` 通过 USB 烧录成功；此前实板日志已有联网、云端激活及 DP 收发记录。UART 改为共用 UART0/115200 后已重新烧录，仍需抓取新日志核对本次串口配置。

## TKL 头文件兼容基线

`tuyaos/tuyaos_adapter/include/<域>/tkl_*.h` 是 Jieli 平台随仓维护的兼容快照，构建时优先于 TuyaOpen 公共 include 路径。当前 15 个头文件按内容（忽略 Git 换行差异）与 TuyaOpen 提交 `66e4c7000d2137e31f26433d01d1c92ac399c814` 的 `tools/porting/adapter/` 对应接口一致；`tkl_init.h` 对应 `tools/porting/adapter/init/include/tkl_init.h`。

TuyaOpen 更新 TKL 接口时，以集成所用 TuyaOpen 提交中的 `tools/porting/adapter/` 为同步来源，逐项比较并更新本地快照，再检查 WL82、WL83 的构建。若 Jieli 为兼容性需要保留差异，应在改动处说明原因并更新本基线记录。不要从 T5AI 复制可能已分叉的头文件，也不要在 `include/` 中加入 Jieli 私有实现声明。

## 板级串口与内存参考

| 板卡 | UART 日志配置 | Flash / RAM 参考 |
| --- | --- | --- |
| `AC79_DevKitBoard` | 日志：UART1、TX=PB3、115200 baud；TAL CLI：UART0、TX=PA5、RX=PA6、115200 baud | **实测 Flash ID `5E4017`、8 MiB；2026-09-23 官方 SDK USB 下载成功**。标准 DevKit 资料为 8 MiB SDRAM、片上 SRAM 578 KB。Tuya 构建 staging 配置为 8 MiB Flash / 8 MiB SDRAM；启动日志的 `SDRAM_SIZE` 是链接配置值，不是实板容量探测。板上 SDRAM 仍待丝印/完整内存测试确认 |
| `AC792N_Develop_Board` | TuyaOpen WL83 staging：UART0 日志与 Tuya CLI 共用，TX=PD1、RX=PE11、115200 baud；上游 SDK `board_demo.h` 默认 1 Mbps，构建按 Kconfig 覆盖 | **实板日志识别 Flash ID `5E4017`、8 MiB**。SDK 原始 `chip_cfg.h` 为 1 MiB Flash / 2 MiB SDRAM；平台构建脚本只改 staging 副本，当前构建值为 8 MiB Flash / 16 MiB DDR1，日志 `DDR_SIZE=16777216` 是链接配置值。官方封装支持 8/16 MiB，实板容量仍待芯片完整丝印/内存测试确认。片上 SRAM 资料不一致：板卡概述 256 KB，AC7926A Datasheet V1.5 为 352 KB |

Flash 容量与 RAM 容量的证据类型不同：AC79 Flash 由下载器读取确认，AC792 Flash ID/容量由 `apps/tuya_cloud/switch_demo/monitor.log` 读取确认；启动日志的 `SDRAM_SIZE`/`DDR_SIZE` 是链接器配置值，不代表自动测出的物理容量。AC79 SDK 原始 `demo_hello/app_config.h` 为 4 MiB Flash / 2 MiB SDRAM，平台构建只在 staging 副本中覆盖为 8 MiB / 8 MiB；AC792 SDK 原始配置与平台 staging 覆盖值也需区分。两块板 RAM 的精确物理容量仍需核对芯片完整丝印或执行覆盖全地址范围的内存测试。AC792 片上 SRAM 的板卡概述与 Datasheet V1.5 数值不一致，暂分别保留来源。`tos.py monitor` 默认波特率从当前 Kconfig 配置读取；AC79 与 AC792 默认日志波特率均为 115,200 baud。AC79 使用 UART1 输出日志、UART0 承载 TAL CLI；AC792 继续通过 UART0 承载日志和 CLI。官方容量资料直达链接见[项目 guide](../../docs/jieli_ac791x_ac792x_project_guide.md)。

## 烧录与串口日志

Windows 上构建完成后运行：

```powershell
tos.py flash
tos.py monitor -p COM3
```

`tos.py flash` 根据当前 `CHIP_CHOICE` 选择对应 SDK 的 `isd_download.exe` 和配置文件。AC792 USB 烧录按官方流程按住 `UPDATE` 键并重新上电，确认设备枚举为 `WL83 UBOOT1.00 USB Device` 后执行下载。AC79 使用其 WL82 USB 下载模式。烧录桥不负责识别日志 COM 口；`tos.py monitor` 需要指定设备管理器中的日志 COM 号。

也可以显式覆盖波特率：

```powershell
# AC792
tos.py monitor -p COM3 -b 115200
```

通用 Jieli 入口调用所选 TuyaOpen 应用的 `tuya_app_main()`。日志内容由应用和 TKL 实现输出。

## 已知限制

**AC792N 当前不支持 WPA3。** 原因是在 STA 关联阶段 CPU1 的 MbedTLS 会触发故障，作为规避，
AC792 SDK 源码中的 `CONFIG_WPA3_SUPPORT` 被置为 0：

```c
// chip/wl83/AC792_SDK/sdk/apps/common/net/wifi_conf.c
const u8 CONFIG_WPA3_SUPPORT = 0;  // 原值为 1
```

影响范围：AC792 无法加入**仅支持 WPA3/SAE** 的 AP；WPA2 及以下不受影响。这是有意保留的临时规避，
不是配置遗漏。恢复 WPA3 需要有一个仅支持 WPA3 的 AP 来复现该故障，先定位 CPU1 MbedTLS 路径，
再把该值改回 1；在具备该验证条件之前不要改回。

**两块板的 RAM 物理容量仍未在实板上完整验证**，证据与现状见上一节。

**工具链校验闸门拦住了你？** 自动下载的安装器会按固定 SHA-256 校验（`tools/jieli_build/toolchain.py` 的
`WINDOWS_TOOLCHAIN_INSTALLER_SHA256`）。如果 Jieli 重新上传了同版本号的安装器导致校验不通过，
手动安装工具链并把 `JIELI_TOOL_DIR` 指向其 `pi32v2/bin` 即可跳过自动下载。

## 历史 AC7916A 工程

`D:\\tuya_proj\\jieli\\ipc_ac7916a` 曾使用 AC7916A，映射到当前统一板名 `AC79_DevKitBoard`。项目保留用于历史参考，不作为当前调试工程；其中 UART2/PB6/115200 是历史工程配置。当前 AC79 固件使用 UART1/PB3/115200 输出日志，UART0/PA5-PA6/115200 承载 TAL CLI。AC792 使用 UART0，日志与 Tuya CLI 共用，PD1/PE11，115200 baud。

完整项目和官方资料索引见 [`docs/jieli_ac791x_ac792x_project_guide.md`](../../docs/jieli_ac791x_ac792x_project_guide.md)。
