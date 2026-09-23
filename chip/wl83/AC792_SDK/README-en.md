# AC792N_AIoT_SDK

<div align="center">

**Jieli AC792N Series VIDEO & AUDIO & WiFi & Bluetooth AIoT Multimedia SoC General-Purpose SDK Firmware**

[中文](./README.md) · [Documentation](https://doc.zh-jieli.com/AC792/zh-cn/wifi_video_master/index.html) · [Release Notes](https://doc.zh-jieli.com/AC792/zh-cn/wifi_video_master/other/version/index.html) · [Repository](https://gitlab.zh-jieli.com/video/ac792)

</div>

---

## 📋 Table of Contents

- [1. Overview](#1-overview)
- [2. Supported Chips & Platforms](#2-supported-chips--platforms)
- [3. Hardware & Software Capabilities](#3-hardware--software-capabilities)
- [4. Environment Setup](#4-environment-setup)
- [5. Quick Start](#5-quick-start)
- [6. Project Structure](#6-project-structure)
- [7. Application & Example Guide](#7-application--example-guide)
- [8. Build Guide](#8-build-guide)
- [9. Flashing & Upgrade](#9-flashing--upgrade)
- [10. Configuration](#10-configuration)
- [11. FAQ](#11-faq)
- [12. Community & Support](#12-community--support)
- [13. Protocols & Certification](#13-protocols--certification)
- [14. Versions & Branches](#14-versions--branches)
- [15. Disclaimer](#15-disclaimer)

---

## 1. Overview

`AC792N_AIoT_SDK` is the general-purpose SDK firmware development package provided by Jieli Technology for the **AC792N series AIoT multimedia SoC**. The AC792N is a low-cost, highly integrated audio/video multimedia system-on-chip combining **WiFi 802.11b/g/n + dual-mode Bluetooth V5.4**. It integrates a **dual-core floating-point DSP running up to 320MHz**, together with audio (ADC/DAC), video (DVP/MIPI camera + ISP), display (MIPI/RGB panel + LVGL/AWTK + GPU2.5D) and rich peripheral resources, enabling one-stop implementation of high-performance audio/video IoT solutions.

This SDK provides a complete protocol stack, media framework, and a rich set of application examples, supporting the following typical use cases:

| Application Type | Typical Products |
|------------------|------------------|
| **WiFi Video Solutions** | WiFi IP cameras, video doorbells/door locks/building intercom, dash cams, baby monitors |
| **Large-Screen A/V Solutions** | Large-screen smart speakers, screen-based story machines, visual beauty devices |
| **WiFi Audio Solutions** | WiFi/Bluetooth smart speakers, children's story machines, reading/scanning/translation pens |
| **Smart Home / IoT** | Smart door locks, pet feeders, barcode scanners, various AIoT connected devices |

This repository contains the SDK source code and example projects. It must be built together with the matching platform library files (`*.a`), and references open-source projects such as lwIP, mbedTLS, LVGL, and AWTK. The firmware package does not include development documentation — please read the [online SDK documentation](https://doc.zh-jieli.com/AC792/zh-cn/wifi_video_master/index.html) before development.

---

## 2. Supported Chips & Platforms

### 2.1 Chip Series

| Platform | Chip Models | Core | Applicable Solutions |
|----------|-------------|------|----------------------|
| **wl83** | AC7921A / AC7922A / AC7922C / AC7923A / AC7923B / AC7923C / AC7925A / AC7925B / AC7925C / AC7926A | Dual-core floating-point DSP @ 320MHz | wifi_camera / wifi_soundbox / wifi_bbm / demo |

### 2.2 Core & On-Chip Resources

| Item | Specification |
|------|---------------|
| **CPU** | Dual-core DSP, up to 320MHz, with single-precision floating point and math acceleration engine |
| **Cache** | I-Cache, D-Cache |
| **On-chip SRAM** | 384 KB total |
| **External Memory** | 8 / 16 MB DDR1 supported by package (SDRAM on selected models) |
| **Power** | Built-in PMU, LDO / DCDC supply modes and multiple low-power modes |
| **Wireless Coexistence** | Built-in PTA time-sharing coexistence module; WiFi / Bluetooth V2.1 / Bluetooth V5.4 can operate simultaneously |

> Model suffix rules: ① different packages; ② different memory sizes (0 none, 2/4/8 Mbit Flash, 6 16Mbit, 3 32Mbit, 5 64Mbit, 7 128Mbit, A 1M×16 SDRAM, B 4M×16 SDRAM, E 4M×16 DDR1, F 8M×16 DDR1, G 16M×16 DDR1); ③ different memory vendors.

---

## 3. Hardware & Software Capabilities

As a high-performance AIoT multimedia SoC, the AC792N integrates wireless, audio, video, display and AI in a single chip. The following is an overview of each subsystem.

### 3.1 Peripheral Interfaces

GPIO, IIC, SPI, SDIO, PWM, MCPWM, UART, CAN, USB 1.1, USB 2.0, ADC, TIMER, IR receiver, capacitive touch keys, rotary encoder, GPCNT, RTC, Ethernet, LEDC.

### 3.2 MATH Hardware Acceleration

| Capability | Description |
|------------|-------------|
| Digital signal | Hardware FFT, IFFT, matrix operations |
| Cryptography | Hardware AES 128/192/256 (ECB/CBC/CTR/CFB128/OFB/GCM/GMAC/CCM/XTS), SHA128/256 |
| Others | Hardware RNG; hardware CRC (7/8/16/32-bit polynomials, with bit reversal and endian swap) |

### 3.3 Bluetooth

- Dual-mode Bluetooth **V5.4** specification
- Supports **AoA / AoD** direction finding
- Supports **LE Audio BIS / CIS**
- Up to **+19 dBm** transmit power
- Receive sensitivity: BR -97dBm, EDR π/4 DQPSK -96dBm, EDR 8DPSK -88dBm

### 3.4 WiFi

- Supports IEEE **802.11b/g/n**; 802.11n supports MCS0–MCS7, 20MHz/40MHz bandwidth, 800ns / 400ns guard intervals
- Supports **AP / STA / Monitor (provisioning)** modes; multi-station access in AP mode; STA multi-network memory, best-signal selection, cold-start fast connect
- Supports Power Save mode; supports **WPA / WPA2 / WPA3-Personal** and mixed modes
- Supports raw RF packet TX/RX bypassing the 802.11 protocol; can connect to instruments such as CMW270 / Jizhi for RF performance testing
- Transmit power: DSSS 1M/s 19dBm / MCS0 17dBm / MCS7 13dBm
- Receive sensitivity: DSSS 1M/s -96dBm / MCS0 -93dBm / MCS7 -74dBm

### 3.5 Audio

- Integrated DAC (external PA required), MIC, LINEIN, IIS, PDM hardware modules; IIS supports 4 channels (independently configurable as input/output, 16/24-bit); PDMLINK supports 2 channels of 16-bit digital MICs; ADC supports 2 channels (each configurable as MIC or LINEIN)
- **Encoding**: SBC, MSBC, CVSD, AAC, MP2, MP3, ADPCM, AMR, OPUS, OGG, SPX, WAV, PCM
- **Decoding**: SBC, MSBC, CVSD, AAC, ADPCM, AMR, APE, DTS, FLAC, M4A, MP1/2/3, OPUS, OGG, SPX, WAV, WMA, PCM; sources include FLASH/SD card/USB drive/LINEIN/external FM/network URL/classic Bluetooth, etc.
- **Audio effects**: reverb, echo, electric voice, voice change/pitch shift, time stretch, frequency shift, howling suppression, EQ, DRC, echo cancellation, conventional noise reduction, neural-network noise reduction
- **Voice**: Voice Activity Detection (VAD), single/dual-MIC barge-in wakeup ASR; selected formats support breakpoint resume / fast-forward & rewind / fixed-point playback / A-B repeat

### 3.6 Video

- Supports **2× DVP-1/2/4/8bit, BT656** image sensor interfaces for YUV sensors, up to 720P
- Supports **MIPI 1 LANE** sensor, up to 720P
- JPEG encoding stream up to **720P@30fps@AVI**; single-frame JPEG encode/decode up to **16384×16384**
- Supports up to three-way combinations: MIPI+DVP+UVC, MIPI+DVP+DVP
- Supports four-way scaling (up to 720P, 2 of which support OSD)
- Supports Image Signal Processing (**ISP**): black-level correction, dead-pixel removal, 2D/chroma denoise, sharpening, brightness/contrast, color matrix, white balance, auto exposure, gamma curve, lens shading correction

### 3.7 Display

- Panel interfaces support **MIPI DSI (1–4 Lane)**, parallel (8/16bit), RGB888/YUV888/RGB666/RGB565/YUV422/RGB333, up to **1280×800@30+fps**
- Supports touch screen, portrait-to-landscape, composited overlay of UI and camera image; color/brightness/saturation/contrast enhancement
- Supports open-source UI frameworks **LVGL** (v8 / v9) and **AWTK**, adapted to DMA2D / GPU2.5D graphics accelerators; supports the Jieli LVGL visual UI editor for auto code generation
- Supports GPU2.5D vector drawing and 2.5D image transforms

### 3.8 Network Stack & AI Cloud Platforms

- **Base protocols**: lwIP, mbedTLS, HTTP/HTTPS, WebSocket, CoAP, nopoll, cURL, MQTT, FTP, uIP, iperf, PJSIP
- **AI cloud platforms**: Turing, Baidu Cloud, Tencent Cloud, China Telecom Smart Home, Tuya, Alibaba Cloud, Huawei HiLink, Tmall Genie, Amazon, AISpeech, Wonders, plus Volcano LLM (large language model)

### 3.9 Firmware Upgrade

- Supports non-backup and backup upgrades
- Non-backup upgrade: via storage devices such as SD card / USB drive
- Backup upgrade: via storage devices (SD card / USB drive) and wireless networks (WiFi / Bluetooth), with UBOOT backup upgrade support

### 3.10 SDK Middleware

FAT file system, persistent data storage, Pthread API, circular buffer (CBUF), frame buffer (LBUF), screen mirroring.

---

## 4. Environment Setup

### 4.1 Prerequisites

| OS | Notes |
|----|-------|
| **Windows** | ✅ Code::Blocks IDE recommended |
| **Linux** | ✅ Makefile command-line build supported |
| **macOS** | ⚠️ Cross-compilation toolchain must be configured manually |

### 4.2 Install the Toolchain

1. Download and install the **Jieli compilation toolchain**: [Dev Environment Docs](https://doc.zh-jieli.com/Tools/zh-cn/dev_tools/dev_env/index.html)
2. Linux users can download from [pkgman.jieliapp.com](http://pkgman.jieliapp.com/doc/all):
   - Extract to the `/opt/jieli` directory
   - Make sure `/opt/jieli/common/bin/clang` exists
3. Verify after installation:

```bash
# Verify the toolchain is installed
clang --version
```

### 4.3 Install Flashing & Test Tools

| Tool | Purpose | Access |
|------|---------|--------|
| **USB Upgrade Tool** | Flash firmware to the target board | [User Guide](https://doc.zh-jieli.com/Tools/zh-cn/dev_tools/forced_upgrade/index.html) |
| **Production Burner** | Mass production / bare-die programming | [User Guide](https://doc.zh-jieli.com/Tools/zh-cn/mass_prod_tools/burner_1tuo2/index.html) |

---

## 5. Quick Start

### 5.1 Clone the Repository

```bash
git clone git@gitlab.zh-jieli.com:video/ac792.git
cd ac792
```

### 5.2 Choose a Project

The actual SDK projects live under the `sdk/` directory. Select an application project based on your product requirements:

```
sdk/
├── apps/wifi_camera/      # WiFi camera solution
├── apps/wifi_soundbox/    # WiFi smart speaker solution
├── apps/wifi_bbm/         # Baby monitor / screen-based video monitor solution
└── apps/demo/             # 7 functional demos (ble/wifi/wifi_ext/edr/ui/hello/audio)
```

### 5.3 Choose a Board Configuration

Each application directory contains a `board/wl83/` subdirectory with:

- `Makefile` - build script
- `AC792N_*.cbp` - Code::Blocks project file
- `board_develop_AC79xx.h` - board configuration (pins, peripherals, etc., per chip model, e.g. `board_develop_AC7926A.h`)
- `board_develop.c` / `sdk_config.h` - board initialization and global configuration

### 5.4 Build and Flash

**Option 1: Code::Blocks (recommended for Windows users)**

```bash
# 1. Enter the corresponding board directory
cd sdk/apps/wifi_camera/board/wl83/

# 2. Double-click the .cbp project file (e.g. AC792N_WIFI_CAMERA.cbp)
# 3. In Code::Blocks, click Build → Build (Ctrl+F9)
# 4. After a successful build, flash the generated firmware with the USB upgrade tool
```

**Option 2: Makefile command line**

```bash
# Windows users: double-click sdk/make_prompt.bat to open the build console

# Linux users: run from the sdk directory
cd sdk
make ac792n_wifi_camera
```

> **💡 Tip**: All supported target names are listed in the comments at the top of [sdk/Makefile](sdk/Makefile).

---

## 6. Project Structure

```
ac792 (repo root)/
├── sdk/                      # SDK main body
│   ├── apps/                 # Application-layer code
│   │   ├── common/           # Common modules (asr/audio_music/camera/eth/lcd/lvgl_v8/
│   │   │                     #   lvgl_v9/dma2d_gpu/pjsip/jlttf/screen_mirror/video/LLM…)
│   │   ├── wifi_camera/      # 📌 WiFi camera solution
│   │   ├── wifi_soundbox/    # 📌 WiFi smart speaker solution
│   │   ├── wifi_bbm/         # 📌 Baby monitor solution
│   │   └── demo/             # 📌 7 functional demos
│   ├── cpu/wl83/             # CPU platform code + prebuilt libraries (liba) + flashing tools (tools)
│   ├── include_lib/          # Header files (btctrler/btstack/driver/media/net/system/update…)
│   ├── lib/                  # Prebuilt libraries
│   ├── audio/                # Audio middleware
│   ├── tools/                # Build tools
│   ├── Makefile              # SDK top-level unified build entry
│   └── make_prompt.bat       # Windows build console entry
├── src/                      # Project config (board/feature/Bluetooth/network/audio JSON config)
├── ui_prj/                   # Jieli UI project resources
├── doc/                      # Datasheets, hardware materials and documentation
│   └── 硬件资料/datasheet/    #   per-model datasheets + selection table
├── docs/                     # Online documentation source
├── sdk_tools/                # SDK tools
└── project.jlproj            # Jieli project file
```

### 6.1 Key Directories

| Directory | Role |
|-----------|------|
| `sdk/apps/*/board/wl83/` | **Board configuration**: pin definitions, peripheral init, build options, `.cbp` projects |
| `sdk/apps/common/` | **Common modules**: cross-project audio, video, display, LVGL, AI middleware |
| `sdk/apps/common/config/` | **Library config**: Bluetooth Profile, user config, auth code, logging |
| `sdk/apps/demo/` | **Functional examples**: 7 minimal demo projects to reference or modify |
| `sdk/cpu/wl83/liba/` | **Prebuilt libraries**: `*.a` static library files |
| `sdk/include_lib/` | **Header files**: protocol stack, driver, media, system, network module interfaces |
| `doc/硬件资料/datasheet/` | **Datasheets**: per-model datasheets and selection table |

---

## 7. Application & Example Guide

### 7.1 Solution Projects

| Solution | Path | Use Cases | make target |
|----------|------|-----------|-------------|
| **WiFi Camera** | `sdk/apps/wifi_camera/` | WiFi surveillance camera, video doorbell, dash cam, image transmission | `ac792n_wifi_camera` |
| **WiFi Smart Speaker** | `sdk/apps/wifi_soundbox/` | Large-screen smart speaker, network audio, screen-based story machine | `ac792n_wifi_soundbox` |
| **Baby Monitor** | `sdk/apps/wifi_bbm/` | Screen-based touch baby monitor, remote A/V monitoring | `ac792n_wifi_bbm` |

### 7.2 Functional Demo Matrix

| Demo | Path | Demonstrated Feature | make target |
|------|------|----------------------|-------------|
| demo_ble | `sdk/apps/demo/demo_ble/` | BLE low-energy data transfer | `ac792n_demo_demo_ble` |
| demo_edr | `sdk/apps/demo/demo_edr/` | Classic Bluetooth EDR (music/SPP/emitter/decode) | `ac792n_demo_demo_edr` |
| demo_wifi | `sdk/apps/demo/demo_wifi/` | WiFi STA/AP networking | `ac792n_demo_demo_wifi` |
| demo_wifi_ext | `sdk/apps/demo/demo_wifi_ext/` | External WiFi extended networking | `ac792n_demo_demo_wifi_ext` |
| demo_audio | `sdk/apps/demo/demo_audio/` | Audio capture/playback/codec | `ac792n_demo_demo_audio` |
| demo_ui | `sdk/apps/demo/demo_ui/` | LVGL UI display/layers/touch | `ac792n_demo_demo_ui` |
| demo_hello | `sdk/apps/demo/demo_hello/` | Minimal boot project (getting-started skeleton) | `ac792n_demo_demo_hello` |

> **Reference**: See the [AC792 module example documentation](https://doc.zh-jieli.com/AC792/zh-cn/wifi_video_master/index.html) for detailed per-module development notes.

---

## 8. Build Guide

### 8.1 Build Command Cheat Sheet

Run the following commands from the `sdk/` directory:

| Target | Application | Command |
|--------|-------------|---------|
| WiFi Camera | wifi_camera | `make ac792n_wifi_camera` |
| WiFi Smart Speaker | wifi_soundbox | `make ac792n_wifi_soundbox` |
| Baby Monitor | wifi_bbm | `make ac792n_wifi_bbm` |
| BLE Demo | demo_ble | `make ac792n_demo_demo_ble` |
| EDR Demo | demo_edr | `make ac792n_demo_demo_edr` |
| WiFi Demo | demo_wifi | `make ac792n_demo_demo_wifi` |
| Extended WiFi Demo | demo_wifi_ext | `make ac792n_demo_demo_wifi_ext` |
| Audio Demo | demo_audio | `make ac792n_demo_demo_audio` |
| UI Demo | demo_ui | `make ac792n_demo_demo_ui` |
| Hello Demo | demo_hello | `make ac792n_demo_demo_hello` |
| **All** | all | `make all` |
| **Clean all** | all | `make clean` |

### 8.2 Clean a Single Project

```bash
make clean_ac792n_wifi_camera     # Clean wifi_camera build artifacts
make clean_ac792n_demo_demo_ble   # Clean demo_ble build artifacts
```

### 8.3 Linux Build Notes

```bash
# 1. Ensure a large enough file-descriptor limit (linking opens many files)
ulimit -n 8096

# 2. Run a parallel build from the sdk directory
make ac792n_wifi_camera -j`nproc`
```

### 8.4 Common Build Errors

| Error Message | Solution |
|---------------|----------|
| `clang: command not found` | Toolchain not installed, or environment variables not configured |
| `Too many open files` | On Linux, run `ulimit -n 8096` to raise the file-descriptor limit |
| `cannot find -lxxx` | Missing `.a` library; check the `sdk/cpu/wl83/liba/` and `sdk/lib/` directories |
| `undefined reference to ...` | Tailoring config does not include the module; check the configs under `sdk/apps/common/config/` |

---

## 9. Flashing & Upgrade

### 9.1 First-Time Flashing

1. **Connect the hardware**: connect the board to the PC via USB or UART
2. **Enter programming mode**: hold the flash button on the board, then reset or re-power
3. **Open the USB upgrade tool**: launch the flashing host software
4. **Select firmware**: choose the firmware file generated by the build
5. **Start flashing**: click the download button and wait for completion

> **⚠️ Note**: Before flashing, make sure the USB upgrade tool is properly connected and the target board is in programming mode.

### 9.2 Firmware Upgrade

The AC792N supports multiple upgrade methods — see the [system upgrade documentation](https://doc.zh-jieli.com/AC792/zh-cn/wifi_video_master/index.html):

- **Non-backup upgrade**: via storage devices such as SD card / USB drive
- **Backup upgrade**: via SD card / USB drive and wireless networks (WiFi / Bluetooth) — safer, supports rollback on failure
- **UBOOT backup upgrade**: supports backup upgrade at the UBOOT layer

---

## 10. Configuration

### 10.1 Feature Tailoring

Under the `sdk/apps/common/config/` directory, the following files let you flexibly tailor SDK features and reduce firmware size:

```bash
sdk/apps/common/config/
├── bt_profile_config.c     # Bluetooth Profile configuration
├── user_cfg.c              # User parameter configuration
├── auth_code_cfg.c         # Authorization code configuration
├── new_cfg_tool.c          # Configuration tool
├── ci_transport_uart.c     # UART transport configuration
└── log_config/             # Log output configuration
```

### 10.2 Board & Project Configuration

- Board configuration: `sdk/apps/*/board/wl83/board_develop_AC79xx.h` (per chip model; includes pin mapping, peripheral enables, clocks, memory config)
- Project configuration: JSON config under the repo-root `src/` (board / feature / Bluetooth / network / audio / LE Audio config), managed by the Jieli project tool `project.jlproj`

---

## 11. FAQ

### 11.1 Development Workflow

**Q: How do I create my own project?**
A: Copy the closest solution project under `sdk/apps/`, enter its `board/wl83/` directory, copy and modify the `board_develop_AC79xx.h` closest to your target chip model, and adjust the pin and peripheral configuration.

**Q: How do I choose between chip models?**
A: Refer to `doc/硬件资料/AC792N系列芯片选型表`, and select by package, memory (DDR1/SDRAM/Flash), number of camera lanes, display interface (MIPI/RGB), Ethernet and other requirements.

### 11.2 Build

**Q: On Windows, `make` is reported as an invalid command — what now?**
A: Use `sdk/make_prompt.bat` to open the preconfigured build console, which sets the `make` path and environment variables for you.

**Q: How can I speed up builds?**
A: Use the `-j` flag for parallel builds, e.g. `make ac792n_wifi_camera -j4`.

### 11.3 Debugging Tips

- **Serial log**: configure log output level and channel via `sdk/apps/common/config/log_config/`
- **GPIO debug**: use a spare GPIO to output debug waveforms and measure timing
- **More issues**: see the [online FAQ documentation](https://doc.zh-jieli.com/AC792/zh-cn/wifi_video_master/index.html)

---

## 12. Community & Support

### Technical Exchange

| Platform | Group ID |
|----------|----------|
| **DingTalk Support Group** | `91050006452` |

### Resource Links

| Resource | Link |
|----------|------|
| 📖 **Online Documentation** | [doc.zh-jieli.com/AC792](https://doc.zh-jieli.com/AC792/zh-cn/wifi_video_master/index.html) |
| 📄 **Chip Datasheet** | [AC792N Datasheet (local)](./doc/硬件资料/datasheet) |
| 📚 **Release Notes** | [Version history](https://doc.zh-jieli.com/AC792/zh-cn/wifi_video_master/other/version/index.html) |
| 💻 **Repository** | [GitLab · video/ac792](https://gitlab.zh-jieli.com/video/ac792) |

---

## 13. Protocols & Certification

The AC792N supports the following wireless protocols. Specific certification IDs are subject to official releases and the certification files of each chip.

| Category | Specification | Notes |
|----------|---------------|-------|
| Bluetooth | Core **v5.4** | Dual-mode BR/EDR + BLE, supports AoA/AoD direction finding, LE Audio BIS/CIS |
| WiFi | IEEE **802.11b/g/n** | Supports WPA / WPA2 / **WPA3**-Personal security modes |

---

## 14. Versions & Branches

> The AC792 internal GitLab repository is updated frequently, especially the `wifi_video_master` mainline branch used for developing new features.
> For testing / R&D / trying the latest features, follow the mainline branch; for mass production, use the corresponding stable release.

### 14.1 Branches & Documentation

| Branch | Purpose | Documentation |
|--------|---------|---------------|
| `wifi_video_master` | Video mainline development branch | [wifi_video_master docs](https://doc.zh-jieli.com/AC792/zh-cn/wifi_video_master/index.html) |

### 14.2 Versioning (major.minor.patch)

- **major**: major version; significant changes, structure not backward-compatible
- **minor**: minor version; larger changes (e.g. API additions) without breaking source/binary compatibility
- **patch**: patch version; internal changes only, no API impact

---

## 15. Disclaimer

`AC792N_AIoT_SDK` supports development on the AC792N series chips. The AC792N series supports common AIoT multimedia applications such as WiFi, Bluetooth, audio, video, and display, and can be used for development, evaluation, sampling, and mass production. This repository is an internal Jieli GitLab project; the corresponding SDK versions are subject to the repository branches and the [release notes](https://doc.zh-jieli.com/AC792/zh-cn/wifi_video_master/other/version/index.html).

---

<div align="center">
  <sub>Copyright © 2024-2026 Zhuhai Jieli Technology Co., Ltd. All rights reserved.</sub>
</div>
