# AC792N_Develop_Board / WL83

The AC792N board builds the full TuyaOpen `switch_demo` image using the official `fw-AC792_SDK` checkout at `chip/wl83/AC792_SDK`.

- Local reference checkout: branch `release/AC792N_SDK_V3`, commit `5abd533ffe108c35e3232d581f064b58f1983341`.
- The upstream SDK's raw `demo_hello/board/wl83/chip_cfg.h` defaults to 1 MiB Flash / 2 MiB SDRAM. TuyaOpen's platform build hook rewrites only the staging copy to the AC7926A DevKit profile: 8 MiB Flash / 16 MiB DDR1.
- In the TuyaOpen WL83 staging build, UART0 carries both logs and Tuya CLI at 115,200 baud (TX PD1, RX PE11). The upstream `demo_hello/board/wl83/board_demo.h` defaults to 1,000,000 baud; the platform build hook applies the Kconfig baud rate in the staging copy.
- Full-stack build command (from `apps/tuya_cloud/switch_demo`): `tos.py config set CONFIG_BOARD_CHOICE_AC792N_DEVELOP_BOARD=y CONFIG_JIELI_MINIMAL_HELLO=n CONFIG_JIELI_UART_LOG_PORT=0 CONFIG_JIELI_UART_LOG_BAUDRATE=115200`, then `tos.py build` on Windows.
- The full image includes the shared Tuya TKL Wi-Fi and BLE adapters, BLE provisioning, Tuya IoT, and switch DP code. WL83-specific differences include the Wi-Fi connection-state enum and BLE address lookup; its WPA/SAE path links `libcrypto_mbedtls.a`.
- Verified on 2026-09-24: full `switch_demo` image built and USB-flashed for `wl83 / AC792N_Develop_Board`; the downloader detected Flash ID `5E4017`, 8 MiB, and completed the download/reboot sequence. The binary is generated under the project's `dist/` directory.
- Flash command: `tos.py flash` selects WL83 SDK tools, `-dev wl83`, and boot address `0x103000`. Enter USB loader mode by holding `UPDATE` while cycling board power.
- Monitor command: `tos.py monitor -p COMx`; baud defaults to the board's configured `CONFIG_JIELI_UART_LOG_BAUDRATE`.

Earlier hardware logs recorded Wi-Fi, Tuya activation, and DP send/receive on this board. The latest UART0/115200 image has been flashed; capture a new serial log to confirm the shared log/CLI UART setting after this build.

The vendor SDK source is included directly at `chip/wl83/AC792_SDK` (release `AC792N_SDK_V3`, upstream commit `5abd533ffe108c35e3232d581f064b58f1983341`). Its `doc/` directory contains board schematic and layout references.

Official documentation: https://doc.zh-jieli.com/AC792/zh-cn/wifi_video_master/index.html
