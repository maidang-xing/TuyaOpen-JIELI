# Jieli wl82 平台（AC7916A 开发板）

当前平台适配的第一个里程碑是 `jieli_uart_hello`：使用 TuyaOpen 的
`tos.py config/build/flash/monitor` 入口，最终链接仍由 AC79 SDK 的
`apps/demo/demo_hello/board/wl82/Makefile` 完成。

## 环境变量

默认会使用当前目录下的 `AC79_AIoT_SDK`（该目录为本地厂商 SDK，已在仓库中排除）。
如 SDK 放在其他位置，再设置 `JIELI_SDK_ROOT`：

```sh
export JIELI_SDK_ROOT=/path/to/AC79_AIoT_SDK
export JIELI_TOOL_DIR=/path/to/pi32v2/bin
```

`JIELI_TOOL_DIR` 至少需要包含 `clang`、`lto-wrapper`、`lto-ar`、`objdump`
和 `objsizedump`。Linux 主机没有杰理 `host-client` 时，构建适配会使用
杰理 `objcopy` 从 `sdk.elf` 生成原始 `app.bin`；这不是完整 UFW 包。

## 构建

```sh
cd examples/get-started/jieli_uart_hello
tos.py config set CONFIG_BOARD_CHOICE=AC7916A
tos.py build
```

Windows PowerShell 也可以直接使用仓库虚拟环境：

```powershell
$env:JIELI_TOOL_DIR = 'C:\JL\pi32\bin'
& .venv\Scripts\python.exe tos.py build
```

输出文件为：

```text
dist/jieli_uart_hello_1.0.0/jieli_uart_hello_QIO_1.0.0.bin
```

## 烧录和串口

Windows 下如果 `platform/JIELI/AC79_AIoT_SDK/cpu/wl82/tools` 中的官方
`isd_download.exe`、`isd_config.ini`、`uboot.boot` 和 `cfg_tool.bin` 均存在，
`tos.py flash` 会自动使用 SDK 的 WL82 USB 下载参数。板卡需要先进入下载模式。
如果使用其他烧录器，可以配置命令覆盖默认行为：

```sh
export JIELI_FLASH_CMD='my-jieli-uploader --file "{binfile}" --port "{port}" --baud "{baud}"'
tos.py flash -p /dev/ttyUSB0 -b 115200
tos.py monitor -p /dev/ttyUSB0 -b 115200
```

使用 SDK 官方 USB 下载器时无需设置 `JIELI_FLASH_CMD`：

```powershell
& .venv\Scripts\python.exe tos.py flash
& .venv\Scripts\python.exe tos.py monitor -p COM11 -b 115200
```

`JIELI_FLASH_CMD` 中支持 `{binfile}`、`{port}`、`{baud}`、`{chip}` 和
`{board}` 占位符。Linux 或 SDK 下载器文件不完整时，必须配置外部烧录器；
平台不会退回通用 `tyutool`。

预期串口输出包含：

```text
TuyaOpen Jieli AC7916A
UART Hello World
```
