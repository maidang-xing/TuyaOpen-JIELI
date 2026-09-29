# Jieli TKL Adapter Refactor Implementation Plan

> **For agentic workers:** Implement this plan inline, task by task. The design spec is authoritative.

**Goal:** Align Jieli's TKL header ownership and private implementation with the approved domain-based design for WL82 and WL83.

**Architecture:** Keep one TKL implementation per interface domain. Sync compatible public TKL headers into Jieli's `include/<domain>/`; keep implementation details in the owning TKL `.c`; retain chip-specific `.c` only for SDK calls that differ materially.

**Tech Stack:** C, CMake, TuyaOpen `tos.py`, JieLi AC79/AC792 SDKs.

**Spec:** `docs/superpowers/specs/2026-09-29-jieli-tkl-header-ownership-design.md`

## Global Constraints

- Do not change public TKL API, MAC rules, UART mapping, network behavior, selected chip, or SDK call ordering.
- Use `tools/porting/adapter/` from the paired TuyaOpen revision as the public TKL header baseline; do not copy potentially divergent T5AI headers.
- Keep `include/tuyaopen_license.h` and `src/system/tuyaopen_license.c` for TuyaOpen authorization.
- Do not add implementation-private headers.
- Do not change SDK sources, app entry points, or build tool responsibilities.

## Review Focus

- `tkl_wifi.c` selects the correct Flash UID SDK call for WL82/WL83; the adapter manifest has no standalone UID helper source.
- MAC getter/setter and BLE derivation preserve the current values and initialization behavior.
- Both CMake and SDK staging resolve local TKL headers before shared TuyaOpen headers.
- `include/init/include/tkl_init.h` is reachable despite its nested T5-style directory.
- Removing wrapper sources leaves no unresolved private symbols in either build.

---

### Task 1: Add compatible public TKL headers and search paths

**Files:**
- Create the headers listed in the design spec under `tuyaos/tuyaos_adapter/include/`.
- Modify `tuyaos/tuyaos_adapter/CMakeLists.txt` and platform staging/build include setup.

**Interfaces:**
- Consumes: paired TuyaOpen headers in `tools/porting/adapter/`.
- Produces: domain-based Jieli TKL headers selected before shared headers in both build paths.

- [x] Add only TKL headers used by current adapter sources or required by those interfaces.
- [x] Add `include/init/include/` to the local include search path.
- [x] Check that signatures match the paired TuyaOpen baseline.
- [x] Verify header resolution in the adapter CMake compile configuration.

### Task 2: Move private helpers into owning TKL sources

**Files:**
- Modify: `tuyaos/tuyaos_adapter/src/driver/tkl_bluetooth.c`, `tkl_wifi.c`, `tkl_uart.c`.
- Modify: `tuyaos/tuyaos_adapter/src/system/tkl_mutex.c`, `tkl_queue.c`, `tkl_semaphore.c`, `tkl_thread.c`.
- Delete private headers and helper sources superseded by the TKL implementations.
- Modify: `tuyaos/tuyaos_adapter/adapter_sources.txt`.

**Interfaces:**
- Consumes: domain TKL headers and selected-chip compile definition from Task 1.
- Produces: one TKL owner for MAC, BLE address setup, Wi-Fi status mapping, UART mapping, and OS wrapper types.

- [x] Move each OS object type and local constant/helper into its owning TKL `.c`.
- [x] Move MAC generation/cache/override into `tkl_wifi.c`; derive BLE MAC in `tkl_bluetooth.c` from the TKL Wi-Fi MAC using current rules.
- [x] Fold Bluetooth address setup into `tkl_bluetooth.c`.
- [x] Fold Wi-Fi status and UART port/ioctl mappings into their TKL `.c` compile-time chip branches.
- [x] Keep the small Flash UID call-signature difference in `tkl_wifi.c` behind the selected-chip compile definition; avoid a private cross-file symbol.
- [x] Remove obsolete helper source entries and private headers; retain the license extension unchanged.

### Task 3: Build and review both chip configurations

**Files:** No additional source files expected.

**Interfaces:** Consumes the resulting adapter sources and headers from Tasks 1–2.

- [x] Build `apps/tuya_cloud/switch_demo` with AC791/WL82 selected.
- [x] Build `apps/tuya_cloud/switch_demo` with AC792/WL83 selected.
- [x] Confirm each build selects the correct chip API and resolves local TKL headers first.
- [x] Run `git diff --check` and review the final diff for unintended runtime or SDK changes.

## 实施验证记录

- WL82/AC791 全量 switch demo 构建成功，产物：`switch_demo_QIO_1.0.0.bin`。
- WL83/AC792 全量 switch demo 构建成功，产物：`switch_demo_QIO_1.0.0.bin`。
- 两个 SDK staging 的依赖文件均解析到 `tuyaos_adapter/include/wifi/tkl_wifi.h`；未解析到 TuyaOpen 公共目录中的同名头文件。
- Review follow-up 后，使用 `switch_demo` 的构建参数/头文件/库，分别将芯片选择为 WL82 和 WL83 执行 platform `build_example.py`；两种 SDK 均重新编译了修改过的 TKL 源并生成 `switch_demo_QIO_1.0.0.bin`。这验证了平台 SDK 编译与打包，不代表运行时实板验证。
- 15 个新增 TKL 头文件的 SHA256 均与配套 TuyaOpen `tools/porting/adapter/` 基线相同。
- 构建使用隔离的临时配置与输出目录；未烧录，未修改 TuyaOpen 业务仓库或 SDK。

## Review follow-up

- 父仓库 `tests/platform/test_jieli_tal_contracts.py` 更新到本次重构后的入口、MAC 实现和队列语义；已验证的基线修改也同步校正。
- 队列改用 `tkl_semaphore_*` 公共接口，不再依赖无共同声明的 `jieli_tkl_sem_wait`。
- Flash UID 小型签名差异收回 `tkl_wifi.c` 芯片选择分支，不再依赖无共同声明的 `jieli_chip_get_flash_uid`。
- README 记录 15 个兼容 TKL 头文件与 TuyaOpen 提交 `66e4c7000d2137e31f26433d01d1c92ac399c814` 的来源及同步规则。
- 恢复 semaphore 的超时语义注释；后续回归检查结果以本 PR 更新记录为准。
