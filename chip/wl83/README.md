# wl83 / AC792N bring-up slot

This directory hosts the AC792N (wl83) vendor SDK once its port starts. The
SDK is intentionally **not** a git submodule yet so a plain
`git clone --recursive` of the platform stays lightweight (wl82 remains the
default and only supported chip today).

## Fetching the vendor SDK (when the port begins)

```bash
cd platform/JIELI/chip/wl83
git clone https://gitee.com/Jieli-Tech/fw-AC792_SDK.git
# pin after validating, then promote to a submodule:
#   git submodule add https://gitee.com/Jieli-Tech/fw-AC792_SDK.git AC792_SDK
```

Docs: https://doc.zh-jieli.com/AC792/zh-cn/wifi_video_master/index.html

## Known porting deltas vs wl82 (measured 2026-09, see tuyaos_adapter/include/chip_conf.h)

- Vendor API surface is 58/59 identical; `bt_get_mac_addr()` is absent —
  derive the BLE address from `le_controller_get_mac()` instead.
- WiFi event enum: values 0..21 identical; >=22 shift because 792 inserts
  five new events at 22. Never hand-copy extended values.
- SDK layout differs (`sdk/` root, `cpu/wl83`), toolchain installs under
  `/opt/jieli/common/bin` (pkgman.jieliapp.com), Windows IDE is Code::Blocks.
- `jieli_build.py` carries a wl83 placeholder config (`JIELI_CHIP=wl83`);
  its layout entries are unvalidated and must be pinned to the first
  successful build.
