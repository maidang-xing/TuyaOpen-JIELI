# JieLi 平台：AC79_DevKitBoard 与 AC792N_Develop_Board

| 统一板名 | 芯片/平台 | 状态 | SDK |
| --- | --- | --- | --- |
| `AC79_DevKitBoard` | AC791 / WL82 | 完整 TuyaOpen `switch_demo` 构建入口已验证；历史别名 `AC7916A` 保留 | `chip/wl82/AC79_AIoT_SDK` |
| `AC792N_Develop_Board` | AC792N / WL83 | 完整 `switch_demo` 镜像已在 Windows 上构建、链接；实板烧录、Wi-Fi/BLE 配网及云端 DP 验证待做 | `chip/wl83/AC792_SDK` |

所有工程均从 TuyaOpen 仓库根目录或示例目录使用 `tos.py`。Windows 是当前支持的烧录环境。AC79 与 AC792 SDK 源码直接纳入 JieLi 平台仓库的 `chip/` 目录，不使用 Git submodule；AC79 SDK 中当前未使用的 `libmatter.a` 按项目约定忽略，不提交。本地工具链默认从 `C:\\JL\\pi32\\bin` 查找，也可设置 `JIELI_TOOL_DIR`。

## 选择板卡与构建

AC79 完整应用（例如 `apps/tuya_cloud/switch_demo`）：

```powershell
tos.py config set CONFIG_BOARD_CHOICE_AC79_DEVKITBOARD=y CONFIG_JIELI_MINIMAL_HELLO=n CONFIG_JIELI_UART_LOG_PORT=1 CONFIG_JIELI_UART_LOG_BAUDRATE=1000000
tos.py build
```

AC792 完整 Tuya `switch_demo`：

```powershell
tos.py config set CONFIG_BOARD_CHOICE_AC792N_DEVELOP_BOARD=y CONFIG_JIELI_MINIMAL_HELLO=n CONFIG_JIELI_UART_LOG_PORT=0 CONFIG_JIELI_UART_LOG_BAUDRATE=1000000
tos.py build
```

该镜像包含 Tuya TKL Wi-Fi/BLE、BLE 配网、Tuya IoT 和 `switch_demo` DP 业务。AC792 SDK 的 WPA/SAE 还需链接 `libcrypto_mbedtls.a`。2026-09-23 已完成完整镜像的软件构建和链接；本次未将最新镜像烧录到 AC792 实板，Wi-Fi、BLE 配网、云端激活与 DP 上报/下发尚未按本次构建结果进行硬件验证。

## 板级串口与内存参考

| 板卡 | UART 日志配置 | Flash / RAM 参考 |
| --- | --- | --- |
| `AC79_DevKitBoard` | 按官方 `demo_DevKitBoard`：UART1、TX=PB3、RX 未使用、1,000,000 baud | **实测 Flash ID `5E4017`、8 MiB；2026-09-23 官方 SDK USB 下载成功**。片上 SRAM 578 KB；本次 switch_demo 启动日志报告 SDRAM 2 MiB，官方 DevKit 示例配置 8 MiB，需核对板卡与 SDK 内存配置 |
| `AC792N_Develop_Board` | WL83 SDK `demo_hello`：UART0、TX=PD1、RX=PE11、1,000,000 baud。bring-up 默认采用此值 | AC7926A SDK 开发板 profile：8 MiB Flash、16 MiB DDR1；芯片片上 SRAM 256 KB |

UART 与 RAM 参数是 SDK/历史工程软件配置参考，须结合实板进一步确认。AC79 Flash ID/容量已由 2026-09-23 USB 下载器读取确认；用户连接串口时仍需核对开发板硬件版本、跳线、TX/RX/GND、COM 号及波特率。`tos.py monitor` 默认波特率从当前 Kconfig 配置读取；AC79 与 AC792 当前均为 1,000,000 baud。2026-09-23 的 AC791 `switch_demo` 实板日志已保存于 `apps/tuya_cloud/switch_demo/src/monitor.log`：固件正常启动，但未观察到 BLE 配网完成、Wi-Fi 连接、Tuya 云激活或 DP 通信；详见项目 guide 中的测试记录。

## 烧录与串口日志

Windows 上构建完成后运行：

```powershell
tos.py flash
tos.py monitor -p COM3
```

`tos.py flash` 根据当前 `CHIP_CHOICE` 选择对应 SDK 的 `isd_download.exe` 和配置文件。AC792 USB 烧录按官方流程按住 `UPDATE` 键并重新上电，确认设备枚举为 `WL83 UBOOT1.00 USB Device` 后执行下载。AC79 使用其 WL82 USB 下载模式。烧录桥不负责识别日志 COM 口；`tos.py monitor` 需要指定设备管理器中的日志 COM 号。

也可以显式覆盖波特率：

```powershell
tos.py monitor -p COM3 -b 1000000
```

AC792 bring-up 固件预期打印 `TuyaOpen Jieli AC792N_Develop_Board (wl83)` 和周期性的 `TuyaOpen Jieli UART heartbeat`。只有连接实板抓取到这些日志，才能确认硬件日志链路已跑通。

## 历史 AC7916A 工程

`D:\\tuya_proj\\jieli\\ipc_ac7916a` 曾使用 AC7916A，映射到当前统一板名 `AC79_DevKitBoard`。项目保留用于历史参考，不作为当前调试工程；其中 UART2/PB6/115200 是历史工程配置。当前固件按官方 DevKit 示例使用 UART1/PB3/1 Mbps，实际硬件接线仍需实板确认。

完整项目和官方资料索引见 [`docs/jieli_ac791x_ac792x_project_guide.md`](../../docs/jieli_ac791x_ac792x_project_guide.md)。
