# AC792N_Develop_Board / WL83

The AC792N board builds the full TuyaOpen `switch_demo` image using the official `fw-AC792_SDK` checkout at `chip/wl83/AC792_SDK`.

- Local reference checkout: branch `release/AC792N_SDK_V3`, commit `5abd533ffe108c35e3232d581f064b58f1983341`.
- Board profile: AC7926A reference configuration, 8 MiB Flash and 16 MiB DDR1.
- UART log profile: UART0, TX PD1, RX PE11, 1,000,000 baud (`demo_hello/board/wl83/board_demo.h`).
- Full-stack build command (from `apps/tuya_cloud/switch_demo`): `tos.py config set CONFIG_BOARD_CHOICE_AC792N_DEVELOP_BOARD=y CONFIG_JIELI_MINIMAL_HELLO=n CONFIG_JIELI_UART_LOG_PORT=0 CONFIG_JIELI_UART_LOG_BAUDRATE=1000000`, then `tos.py build` on Windows.
- The full image includes the shared Tuya TKL Wi-Fi and BLE adapters, BLE provisioning, Tuya IoT, and switch DP code. WL83-specific differences include the Wi-Fi connection-state enum and BLE address lookup; its WPA/SAE path links `libcrypto_mbedtls.a`.
- Verified on 2026-09-23: full `switch_demo` image built and linked for `wl83 / AC792N_Develop_Board`. The binary is generated under the project's `dist/` directory.
- Flash command: `tos.py flash` selects WL83 SDK tools, `-dev wl83`, and boot address `0x103000`. Enter USB loader mode by holding `UPDATE` while cycling board power.
- Monitor command: `tos.py monitor -p COMx`; baud defaults to the board's configured `CONFIG_JIELI_UART_LOG_BAUDRATE`.

The AC792 board was not connected to the host during this verification, so firmware was not flashed and Wi-Fi, BLE provisioning, cloud activation, DP reporting, and DP control have not yet been exercised on hardware. Serial wiring and UART capture also remain to be confirmed on the board.

The vendor SDK source is included directly at `chip/wl83/AC792_SDK` (release `AC792N_SDK_V3`, upstream commit `5abd533ffe108c35e3232d581f064b58f1983341`). Its `doc/` directory contains board schematic and layout references.

Official documentation: https://doc.zh-jieli.com/AC792/zh-cn/wifi_video_master/index.html
