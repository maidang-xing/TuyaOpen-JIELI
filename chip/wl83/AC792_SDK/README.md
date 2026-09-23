# AC792N_AIoT_SDK

<div align="center">
**杰理 AC792N 系列 VIDEO & AUDIO & WiFi & 蓝牙 AIoT 多媒体 SoC 通用 SDK 固件程序**

[English](./README-en.md) · [文档中心](https://doc.zh-jieli.com/AC792/zh-cn/wifi_video_master/index.html) · [SDK 版本历史](https://doc.zh-jieli.com/AC792/zh-cn/wifi_video_master/other/version/index.html) · [代码仓库](https://gitlab.zh-jieli.com/video/ac792)

</div>

---

## 📋 目录

- [一、概述](#一概述)
- [二、支持的芯片与平台](#二支持的芯片与平台)
- [三、芯片软硬件能力总览](#三芯片软硬件能力总览)
- [四、环境搭建](#四环境搭建)
- [五、快速开始](#五快速开始)
- [六、工程结构](#六工程结构)
- [七、应用与示例指南](#七应用与示例指南)
- [八、编译指南](#八编译指南)
- [九、烧录与升级](#九烧录与升级)
- [十、配置说明](#十配置说明)
- [十一、常见问题](#十一常见问题)
- [十二、社区与支持](#十二社区与支持)
- [十三、协议与认证](#十三协议与认证)
- [十四、版本与分支说明](#十四版本与分支说明)
- [十五、免责声明](#十五免责声明)

---

## 一、概述

`AC792N_AIoT_SDK` 是杰理科技为 **AC792N 系列 AIoT 多媒体 SoC** 提供的通用 SDK 固件开发包。AC792N 是一款低成本、高集成度的 **WiFi 802.11b/g/n + 双模蓝牙 V5.4** 音视频多媒体系统级芯片，内部集成主频高达 **320MHz 的双核浮点 DSP**，并完整集成音频（ADC/DAC）、视频（DVP/MIPI 摄像头 + ISP）、显示（MIPI/RGB 推屏 + LVGL/AWTK + GPU2.5D）与丰富外设资源，可一站式实现各类高性能音视频物联网方案。

本 SDK 提供完整的协议栈、媒体框架与丰富的应用示例，支持以下典型应用场景：

| 应用类型 | 典型产品 |
|---------|---------|
| **WiFi 视频方案** | WiFi 监控摄像头 IP Camera、可视门铃/视频门锁/楼宇智能、行车记录、婴儿监护器 |
| **大屏音视频方案** | 大屏智能音箱、带屏绘本故事机、可视美容仪 |
| **WiFi 音频方案** | WiFi/蓝牙智能音箱、儿童故事机、点读笔/扫描笔/翻译笔 |
| **智能家居/物联网** | 智能门锁、宠物喂食机、扫码枪、各类 AIoT 联网设备 |

本仓库为 SDK 代码及示例工程，需配合对应平台的库文件（`*.a`）进行编译，并引用了 lwIP、mbedTLS、LVGL、AWTK 等开源项目。SDK 固件包不含开发文档，开发前请详细阅读 [SDK 在线开发文档](https://doc.zh-jieli.com/AC792/zh-cn/wifi_video_master/index.html)。

---

## 二、支持的芯片与平台

### 2.1 芯片系列

| 芯片平台 | 芯片型号 | 内核 | 适用方案 |
|---------|---------|------|---------|
| **wl83** | AC7921A / AC7922A / AC7922C / AC7923A / AC7923B / AC7923C / AC7925A / AC7925B / AC7925C / AC7926A | 双核浮点 DSP @ 320MHz | wifi_camera / wifi_soundbox / wifi_bbm / demo |

### 2.2 内核与片上资源

| 项目 | 规格 |
|------|------|
| **CPU** | 双核 DSP，最高主频 320MHz，支持单精度浮点及数学运算加速引擎 |
| **缓存** | 带 I-Cache、D-Cache |
| **片上 SRAM** | 共 384 KB |
| **外扩内存** | 封装支持 8 / 16 MB DDR1（部分型号 SDRAM） |
| **供电** | 内置 PMU，支持 LDO / DCDC 供电与多种低功耗模式 |
| **无线共存** | 内部集成 PTA 共存分时模块，WiFi / 蓝牙 V2.1 / 蓝牙 V5.4 可同时工作 |

> 芯片型号后缀规则：①不同封装；②不同存储容量（0 无内存、2/4/8 Mbit Flash、6 16Mbit、3 32Mbit、5 64Mbit、7 128Mbit、A 1M×16 SDRAM、B 4M×16 SDRAM、E 4M×16 DDR1、F 8M×16 DDR1、G 16M×16 DDR1）；③不同内存厂商。

---

## 三、芯片软硬件能力总览

AC792N 作为高性能 AIoT 多媒体 SoC，集无线、音频、视频、显示、AI 于一体。以下为各子系统能力一览。

### 3.1 外设接口

GPIO、IIC、SPI、SDIO、PWM、MCPWM、UART、CAN、USB 1.1、USB 2.0、ADC、TIMER、IR 接收、电容触摸按键、旋转编码器、GPCNT、RTC、Ethernet、LEDC。

### 3.2 MATH 硬件加速

| 能力 | 说明 |
|------|------|
| 数字信号 | 硬件 FFT、IFFT、矩阵运算 |
| 加解密 | 硬件 AES 128/192/256（ECB/CBC/CTR/CFB128/OFB/GCM/GMAC/CCM/XTS）、SHA128/256 |
| 其他 | 硬件随机数；硬件 CRC（7/8/16/32 位多项式，支持位反转与端序翻转） |

### 3.3 蓝牙

- 双模蓝牙 **V5.4** 规范
- 支持 **AoA / AoD** 测向
- 支持 **LE Audio BIS / CIS**
- 最大 **+19 dBm** 发射功率
- 接收灵敏度：BR -97dBm，EDR π/4 DQPSK -96dBm，EDR 8DPSK -88dBm

### 3.4 WiFi

- 支持 IEEE **802.11b/g/n**，802.11n 支持 MCS0~MCS7、20MHz/40MHz 带宽，800ns / 400ns 保护间隔
- 支持 **AP / STA / Monitor（配网）** 模式；AP 多站接入；STA 多网络记忆、择优连接、冷启动快连
- 支持 Power Save 省电模式；支持 **WPA / WPA2 / WPA3-Personal** 及其混合模式
- 支持脱离 802.11 协议直接收发底层 RF 数据包，可对接 CMW270 / 极致汇仪等测试仪测试 RF 性能
- 发射功率：DSSS 1M/s 19dBm / MCS0 17dBm / MCS7 13dBm
- 接收灵敏度：DSSS 1M/s -96dBm / MCS0 -93dBm / MCS7 -74dBm

### 3.5 音频

- 集成 DAC（需外挂功放）、MIC、LINEIN、IIS、PDM 硬件模块；IIS 支持 4 通道（可独立配置输入/输出，16/24bit）；PDMLINK 支持 2 路 16bit 数字麦；ADC 2 通道（每通道可配 MIC 或 LINEIN）
- **编码**：SBC、MSBC、CVSD、AAC、MP2、MP3、ADPCM、AMR、OPUS、OGG、SPX、WAV、PCM
- **解码**：SBC、MSBC、CVSD、AAC、ADPCM、AMR、APE、DTS、FLAC、M4A、MP1/2/3、OPUS、OGG、SPX、WAV、WMA、PCM；数据源支持 FLASH/SD卡/U盘/LINEIN/外挂FM/网络URL/经典蓝牙等
- **音效**：混响、回声、电音、变声变调、变速、移频、啸叫抑制、EQ、DRC、回声消除、传统降噪、神经网络降噪
- **语音**：活动语音检测 VAD、单/双 MIC 的打断唤醒 ASR；部分格式支持断点/快进快退/定点/AB 复读

### 3.6 视频

- 支持 **2 路 DVP-1/2/4/8bit、BT656** 图像传感器接口的 YUV sensor，最大 720P
- 支持 **MIPI 1 LANE** sensor，最大 720P
- JPEG 编码流最大 **720P@30fps@AVI**；JPEG 单张最大编解分辨率 **16384×16384**
- 支持最大三路组合：MIPI+DVP+UVC、MIPI+DVP+DVP
- 支持四路缩放（最大 720P，其中 2 路支持 OSD）
- 支持图像信号处理（**ISP**）：黑电平校正、去坏点、2D/色度降噪、锐化、亮度对比度、颜色矩阵、白平衡、自动曝光、伽马曲线、镜头阴影校正

### 3.7 显示

- 推屏接口支持 **MIPI DSI（1~4 Lane）**、并行（8/16bit）、RGB888/YUV888/RGB666/RGB565/YUV422/RGB333，最高 **1280×800@30+fps**
- 支持屏触摸、竖屏横显、UI 与摄像头图像合成叠加显示；颜色/亮度/饱和度/对比度增强
- 支持开源 UI 框架 **LVGL**（v8 / v9）与 **AWTK**，适配 DMA2D / GPU2.5D 图形加速器；支持杰理 LVGL 可视化 UI 编辑工具自动生成代码
- 支持 GPU2.5D 矢量绘图、图像 2.5D 变换

### 3.8 网络协议栈与 AI 云平台

- **基础协议**：lwIP、mbedTLS、HTTP/HTTPS、WebSocket、CoAP、nopoll、cURL、MQTT、FTP、uIP、iperf、PJSIP
- **AI 云平台**：图灵、百度云、腾讯云、中国电信智能家居、涂鸦、阿里云、华为 HiLink、天猫精灵、亚马逊、思必驰、玩瞳，以及火山大模型（LLM）

### 3.9 固件升级

- 支持不备份升级与备份升级
- 不备份升级：通过 SD卡 / U盘 等存储设备升级
- 备份升级：通过 SD卡 / U盘 与无线网络（WiFi / 蓝牙）升级，支持 UBOOT 备份升级

### 3.10 SDK 中间件

FAT 文件系统、数据存储记忆、Pthread API、循环缓冲 CBUF、帧缓冲 LBUF、屏镜像（screen_mirror）。

---

## 四、环境搭建

### 4.1 前提条件

| 系统 | 说明 |
|------|------|
| **Windows** | ✅ 推荐使用 Code::Blocks IDE 编译 |
| **Linux** | ✅ 支持 Makefile 命令行编译 |
| **macOS** | ⚠️ 需自行配置交叉编译工具链 |

### 4.2 安装编译工具链

1. 下载并安装 **杰理编译工具链**：[开发环境文档](https://doc.zh-jieli.com/Tools/zh-cn/dev_tools/dev_env/index.html)
2. Linux 用户可从 [pkgman.jieliapp.com](http://pkgman.jieliapp.com/doc/all) 下载：
   - 解压到 `/opt/jieli` 目录
   - 确保 `/opt/jieli/common/bin/clang` 存在
3. 安装完成后验证：

```bash
# 验证工具链是否安装成功
clang --version
```

### 4.3 安装烧录与测试工具

| 工具 | 用途 | 获取方式 |
|------|------|---------|
| **USB 升级工具** | 将固件烧录到目标板 | [使用文档](https://doc.zh-jieli.com/Tools/zh-cn/dev_tools/forced_upgrade/index.html) |
| **生产烧写工具** | 量产/裸片烧写 | [使用文档](https://doc.zh-jieli.com/Tools/zh-cn/mass_prod_tools/burner_1tuo2/index.html) |

---

## 五、快速开始

### 5.1 克隆仓库

```bash
git clone git@gitlab.zh-jieli.com:video/ac792.git
cd ac792
```

### 5.2 选择合适的工程

SDK 实际工程位于 `sdk/` 目录，根据产品需求选择应用工程：

```
sdk/
├── apps/wifi_camera/      # WiFi 摄像头方案
├── apps/wifi_soundbox/    # WiFi 智能音箱方案
├── apps/wifi_bbm/         # 婴儿监护器 / 带屏视频监护方案
└── apps/demo/             # 7 个功能 demo（ble/wifi/wifi_ext/edr/ui/hello/audio）
```

### 5.3 选择板级配置

每个应用目录下都有 `board/wl83/` 子目录，包含：

- `Makefile` - 编译脚本
- `AC792N_*.cbp` - Code::Blocks 工程文件
- `board_develop_AC79xx.h` - 板级配置（引脚、外设等，按芯片型号区分，如 `board_develop_AC7926A.h`）
- `board_develop.c` / `sdk_config.h` - 板级初始化与全局配置

### 5.4 编译并烧录

**方式一：Code::Blocks（推荐 Windows 用户）**

```bash
# 1. 进入对应的板级目录
cd sdk/apps/wifi_camera/board/wl83/

# 2. 双击打开 .cbp 工程文件（如 AC792N_WIFI_CAMERA.cbp）
# 3. 在 Code::Blocks 中点击 Build → Build (Ctrl+F9)
# 4. 编译成功后，使用 USB 升级工具烧录生成的固件文件
```

**方式二：Makefile 命令行**

```bash
# Windows 用户：双击 sdk/make_prompt.bat 打开命令行环境

# Linux 用户：在 sdk 目录执行
cd sdk
make ac792n_wifi_camera
```

> **💡 提示**：所有支持的 target 名称见 [sdk/Makefile](sdk/Makefile) 开头的注释。

---

## 六、工程结构

```
ac792（仓库根）/
├── sdk/                      # SDK 主体
│   ├── apps/                 # 应用层代码
│   │   ├── common/           # 公共模块（asr/audio_music/camera/eth/lcd/lvgl_v8/
│   │   │                     #   lvgl_v9/dma2d_gpu/pjsip/jlttf/screen_mirror/video/LLM…）
│   │   ├── wifi_camera/      # 📌 WiFi 摄像头方案
│   │   ├── wifi_soundbox/    # 📌 WiFi 智能音箱方案
│   │   ├── wifi_bbm/         # 📌 婴儿监护器方案
│   │   └── demo/             # 📌 7 个功能 demo
│   ├── cpu/wl83/             # CPU 平台代码 + 预编译库(liba) + 烧录工具(tools)
│   ├── include_lib/          # 头文件（btctrler/btstack/driver/media/net/system/update…）
│   ├── lib/                  # 预编译库
│   ├── audio/                # 音频中间件
│   ├── tools/                # 编译工具
│   ├── Makefile              # SDK 顶层统一编译入口
│   └── make_prompt.bat       # Windows 编译命令行入口
├── src/                      # 项目配置（板级/功能/蓝牙/网络/音频 JSON 配置）
├── ui_prj/                   # 杰理 UI 工程资源
├── doc/                      # 数据手册、硬件资料与文档
│   └── 硬件资料/datasheet/    #   各型号 datasheet + 选型表
├── docs/                     # 在线文档源
├── sdk_tools/                # SDK 工具
└── project.jlproj            # 杰理工程文件
```

### 6.1 关键目录说明

| 目录 | 作用 |
|------|------|
| `sdk/apps/*/board/wl83/` | **板级配置**：引脚定义、外设初始化、编译选项、`.cbp` 工程 |
| `sdk/apps/common/` | **公共模块**：跨工程共享的音频、视频、显示、LVGL、AI 等中间件 |
| `sdk/apps/common/config/` | **库配置**：蓝牙 Profile、用户配置、授权码、日志等 |
| `sdk/apps/demo/` | **功能示例**：7 个可直接参考或修改的最小 demo 工程 |
| `sdk/cpu/wl83/liba/` | **预编译库**：`*.a` 静态库文件 |
| `sdk/include_lib/` | **头文件**：协议栈、驱动、媒体、系统、网络等模块接口 |
| `doc/硬件资料/datasheet/` | **数据手册**：各型号 datasheet 与选型表 |

---

## 七、应用与示例指南

### 7.1 方案工程

| 方案 | 路径 | 适用场景 | make target |
|------|------|---------|-------------|
| **WiFi 摄像头** | `sdk/apps/wifi_camera/` | WiFi 监控摄像头、可视门铃、行车记录、图传 | `ac792n_wifi_camera` |
| **WiFi 智能音箱** | `sdk/apps/wifi_soundbox/` | 大屏智能音箱、网络音频、带屏故事机 | `ac792n_wifi_soundbox` |
| **婴儿监护器** | `sdk/apps/wifi_bbm/` | 带屏触控婴儿监护、音视频远程看护 | `ac792n_wifi_bbm` |

### 7.2 功能 Demo 矩阵

| Demo | 路径 | 演示功能 | make target |
|------|------|---------|-------------|
| demo_ble | `sdk/apps/demo/demo_ble/` | BLE 低功耗蓝牙数传 | `ac792n_demo_demo_ble` |
| demo_edr | `sdk/apps/demo/demo_edr/` | 经典蓝牙 EDR（音乐/SPP/发射器/解码） | `ac792n_demo_demo_edr` |
| demo_wifi | `sdk/apps/demo/demo_wifi/` | WiFi STA/AP 联网 | `ac792n_demo_demo_wifi` |
| demo_wifi_ext | `sdk/apps/demo/demo_wifi_ext/` | 外置 WiFi 扩展联网 | `ac792n_demo_demo_wifi_ext` |
| demo_audio | `sdk/apps/demo/demo_audio/` | 音频采集/播放/编解码 | `ac792n_demo_demo_audio` |
| demo_ui | `sdk/apps/demo/demo_ui/` | LVGL UI 显示/图层/触摸 | `ac792n_demo_demo_ui` |
| demo_hello | `sdk/apps/demo/demo_hello/` | 最小启动工程（入门骨架） | `ac792n_demo_demo_hello` |

> **参考文档**：各模块详细开发说明见 [AC792 模块示例文档](https://doc.zh-jieli.com/AC792/zh-cn/wifi_video_master/index.html)。

---

## 八、编译指南

### 8.1 编译命令速查表

以下命令在 `sdk/` 目录下执行：

| 目标 | 应用 | 命令 |
|------|------|------|
| WiFi 摄像头 | wifi_camera | `make ac792n_wifi_camera` |
| WiFi 智能音箱 | wifi_soundbox | `make ac792n_wifi_soundbox` |
| 婴儿监护器 | wifi_bbm | `make ac792n_wifi_bbm` |
| BLE Demo | demo_ble | `make ac792n_demo_demo_ble` |
| EDR Demo | demo_edr | `make ac792n_demo_demo_edr` |
| WiFi Demo | demo_wifi | `make ac792n_demo_demo_wifi` |
| 扩展 WiFi Demo | demo_wifi_ext | `make ac792n_demo_demo_wifi_ext` |
| 音频 Demo | demo_audio | `make ac792n_demo_demo_audio` |
| UI Demo | demo_ui | `make ac792n_demo_demo_ui` |
| Hello Demo | demo_hello | `make ac792n_demo_demo_hello` |
| **全部** | 全部 | `make all` |
| **清理全部** | 全部 | `make clean` |

### 8.2 清理单个工程

```bash
make clean_ac792n_wifi_camera     # 清理 wifi_camera 编译产物
make clean_ac792n_demo_demo_ble   # 清理 demo_ble 编译产物
```

### 8.3 Linux 编译注意事项

```bash
# 1. 确保文件描述符限制足够大（链接阶段需要打开大量文件）
ulimit -n 8096

# 2. 进入 sdk 目录并行编译
make ac792n_wifi_camera -j`nproc`
```

### 8.4 常见编译错误

| 错误提示 | 解决方法 |
|---------|---------|
| `clang: command not found` | 未安装杰理编译工具链，或环境变量未配置 |
| `Too many open files` | Linux 下执行 `ulimit -n 8096` 增加文件描述符限制 |
| `cannot find -lxxx` | 缺少对应的 `.a` 库文件，检查 `sdk/cpu/wl83/liba/` 与 `sdk/lib/` 目录 |
| `undefined reference to ...` | 功能裁剪配置未包含对应模块，检查 `sdk/apps/common/config/` 下的配置 |

---

## 九、烧录与升级

### 9.1 首次烧录

1. **连接硬件**：将开发板通过 USB 或 UART 连接到 PC
2. **进入编程模式**：按住开发板上的烧录按键，然后复位或重新上电
3. **打开 USB 升级工具**：启动烧录上位机
4. **选择固件**：选择编译生成的固件文件
5. **开始烧录**：点击下载按钮，等待烧录完成

> **⚠️ 注意**：烧录前请确保 USB 升级工具正确连接且目标板已进入编程模式。

### 9.2 固件升级

AC792N 支持多种升级方式，详见 [系统升级文档](https://doc.zh-jieli.com/AC792/zh-cn/wifi_video_master/index.html)：

- **不备份升级**：通过 SD卡 / U盘 等存储设备升级
- **备份升级**：通过 SD卡 / U盘 与无线网络（WiFi / 蓝牙）升级（更安全，失败可回滚）
- **UBOOT 备份升级**：支持 UBOOT 层备份升级

---

## 十、配置说明

### 10.1 功能裁剪配置

在 `sdk/apps/common/config/` 目录下，通过以下配置可灵活裁剪 SDK 功能、减小固件体积：

```bash
sdk/apps/common/config/
├── bt_profile_config.c     # 蓝牙 Profile 配置
├── user_cfg.c              # 用户参数配置
├── auth_code_cfg.c         # 授权码配置
├── new_cfg_tool.c          # 配置工具
├── ci_transport_uart.c     # 串口通信传输配置
└── log_config/             # 日志输出配置
```

### 10.2 板级与项目配置

- 板级配置：`sdk/apps/*/board/wl83/board_develop_AC79xx.h`（按芯片型号区分，含引脚映射、外设使能、时钟、内存配置）
- 项目配置：仓库根 `src/` 下的 JSON 配置（板级配置 / 功能配置 / 蓝牙配置 / 网络配置 / 音频配置 / LE_AUDIO 配置），由杰理工程工具 `project.jlproj` 管理

---

## 十一、常见问题

### 11.1 开发流程相关

**Q: 如何创建自己的工程？**
A: 复制 `sdk/apps/` 下最接近的方案工程，进入其 `board/wl83/` 目录，复制并修改与目标芯片型号最接近的 `board_develop_AC79xx.h`，调整引脚和外设配置即可。

**Q: 不同芯片型号怎么选？**
A: 参考 `doc/硬件资料/AC792N系列芯片选型表`，按封装、内存（DDR1/SDRAM/Flash）、摄像头路数、屏接口（MIPI/RGB）、以太网等需求选型。

### 11.2 编译相关

**Q: Windows 下编译报错 `make` 不是有效命令？**
A: 使用 `sdk/make_prompt.bat` 进入预配置的命令行环境，该脚本已设置好 `make` 路径和环境变量。

**Q: 如何加快编译速度？**
A: 使用 `-j` 参数并行编译，如 `make ac792n_wifi_camera -j4`。

### 11.3 调试技巧

- **串口日志**：通过 `sdk/apps/common/config/log_config/` 配置日志输出等级和通道
- **GPIO Debug**：利用空闲 GPIO 输出调试波形，测量时序
- **更多问题**：请参考 [在线 FAQ 文档](https://doc.zh-jieli.com/AC792/zh-cn/wifi_video_master/index.html)

---

## 十二、社区与支持

### 技术交流

| 平台 | 群号 |
|------|------|
| **钉钉技术支持群** | `91050006452` |

### 资源链接

| 资源 | 链接 |
|------|------|
| 📖 **在线文档中心** | [doc.zh-jieli.com/AC792](https://doc.zh-jieli.com/AC792/zh-cn/wifi_video_master/index.html) |
| 📄 **芯片数据手册** | [AC792N 规格书）](./doc/硬件资料/datasheet) |
| 📚 **SDK 版本历史** | [版本发布记录](https://doc.zh-jieli.com/AC792/zh-cn/wifi_video_master/other/version/index.html) |
| 💻 **代码仓库** | [Gitee/ac792](https://gitee.com/Jieli-Tech/fw-AC792_SDK) |

---

## 十三、协议与认证

AC792N 支持的无线协议如下；具体认证编号请以官方发布与对应芯片认证文件为准。

| 类别 | 规范 | 说明 |
|------|------|------|
| 蓝牙 | Core **v5.4** | 双模 BR/EDR + BLE，支持 AoA/AoD 测向、LE Audio BIS/CIS |
| WiFi | IEEE **802.11b/g/n** | 支持 WPA / WPA2 / **WPA3**-Personal 安全模式 |

---

## 十四、版本与分支说明

> AC792 内部 GitLab 仓库时常更新，特别是用于开发新特性的 `wifi_video_master` 主线分支。
> 如需测试/研发/尝试最新特性，建议跟随主线分支；如有量产用途，建议使用对应的稳定发布版本。

### 14.1 分支与文档

| 分支 | 用途 | 配套文档 |
|------|------|---------|
| `AC792N_SDK_V3` | 主线开发分支 | [AC792N_SDK_V3 文档](https://doc.zh-jieli.com/AC792/zh-cn/wifi_video_master/index.html) |

### 14.2 版本号规则（major.minor.patch）

- **major**：主版本号，结构发生重大变化、无法与旧版本兼容
- **minor**：次版本号，反映较大更改（如 API 增加），但不影响源码与二进制兼容性
- **patch**：补丁版本，仅修改内部实现、不影响 API 接口

---

## 十五、免责声明

`AC792N_AIoT_SDK` 支持 AC792N 系列芯片开发。AC792N 系列芯片支持 WiFi、蓝牙、音频、视频、显示等 AIoT 多媒体常见应用，可作为开发、评估、样品及量产使用。本仓库为杰理内部 GitLab 项目，对应 SDK 版本以仓库分支与 [版本发布记录](https://doc.zh-jieli.com/AC792/zh-cn/wifi_video_master/other/version/index.html) 为准。

---

<div align="center">
  <sub>Copyright © 2024-2026 珠海杰理科技股份有限公司. All rights reserved.</sub>
</div>
