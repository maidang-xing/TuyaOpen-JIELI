"""Host-side helpers for the TuyaOpen Jieli wl82 build bridge."""

from __future__ import annotations

import os
import shutil
import subprocess
from pathlib import Path
from typing import Mapping, Optional


MODULE_ROOT = Path(__file__).resolve().parent
BOARD_BUILD_RELATIVE = Path("apps/demo/demo_hello/board/wl82")
TOOLS_RELATIVE = Path("cpu/wl82/tools")


TOOL_ALIASES = {
    "clang": ("clang", "clang.exe"),
    "lto-wrapper": (
        "lto-wrapper",
        "lto-wrapper.exe",
        "pi32v2-lto-wrapper",
        "pi32v2-lto-wrapper.exe",
    ),
    "lto-ar": ("lto-ar", "lto-ar.exe", "pi32v2-lto-ar", "pi32v2-lto-ar.exe"),
    "objcopy": ("objcopy", "objcopy.exe", "llvm-objcopy", "llvm-objcopy.exe"),
    "objdump": ("objdump", "objdump.exe", "llvm-objdump", "llvm-objdump.exe"),
    "objsizedump": (
        "objsizedump",
        "objsizedump.exe",
        "llvm-objsizedump",
        "llvm-objsizedump.exe",
    ),
}


class BuildError(RuntimeError):
    """Raised when a required Jieli build input is unavailable."""


def resolve_tool_path(tool_dir: Path, logical_name: str) -> Path:
    for name in TOOL_ALIASES[logical_name]:
        candidate = tool_dir / name
        if candidate.is_file():
            return candidate
    return tool_dir / TOOL_ALIASES[logical_name][0]


def link_directory(link: Path, target: Path) -> None:
    try:
        link.symlink_to(target, target_is_directory=True)
        return
    except OSError:
        if os.name != "nt":
            raise

    result = subprocess.run(
        ["cmd.exe", "/c", "mklink", "/J", str(link), str(target)],
        check=False,
        capture_output=True,
        text=True,
    )
    if result.returncode != 0:
        detail = (result.stderr or result.stdout).strip()
        raise OSError(result.returncode, f"cannot link {link} to {target}: {detail}")


def configure_reference_log_uart(board_file: Path) -> None:
    """Match the reference IPC_AC7916A UART2 logging configuration."""
    if not board_file.is_file():
        return

    content = board_file.read_text(encoding="utf-8")
    begin = "UART2_PLATFORM_DATA_BEGIN(uart2_data)"
    end = "UART2_PLATFORM_DATA_END();"
    start = content.find(begin)
    if start < 0:
        raise BuildError(f"Jieli board file has no UART2 block: {board_file}")
    finish = content.find(end, start)
    if finish < 0:
        raise BuildError(f"Jieli board file has an incomplete UART2 block: {board_file}")
    finish += len(end)

    uart_block = content[start:finish]
    for old, new in (
        (".baudrate = 1000000,", ".baudrate = 115200,"),
        (".port = PORT_REMAP,", ".port = PORTB_6_7,"),
        (".tx_pin = IO_PORTB_03,", ".tx_pin = IO_PORTB_06,"),
    ):
        uart_block = uart_block.replace(old, new, 1)
    board_file.write_text(content[:start] + uart_block + content[finish:], encoding="utf-8")


def configure_service_uart(board_file: Path) -> None:
    """Add the separate Jieli UART used by Tuya logical UART0/CLI."""
    if not board_file.is_file():
        return

    content = board_file.read_text(encoding="utf-8")
    if "UART1_PLATFORM_DATA_BEGIN(uart1_data)" not in content:
        marker = "UART2_PLATFORM_DATA_BEGIN(uart2_data)"
        uart_block = (
            "UART1_PLATFORM_DATA_BEGIN(uart1_data)\n"
            "    .baudrate = 115200,\n"
            "    .port = PORTB_3_4,\n"
            "    .tx_pin = IO_PORTB_03,\n"
            "    .rx_pin = IO_PORTB_04,\n"
            "    .max_continue_recv_cnt = 1024,\n"
            "    .idle_sys_clk_cnt = 500000,\n"
            "    .clk_src = PLL_48M,\n"
            "    .flags = UART_DEBUG,\n"
            "UART1_PLATFORM_DATA_END();\n\n"
        )
        if marker not in content:
            raise BuildError(f"Jieli board file has no UART2 block: {board_file}")
        content = content.replace(marker, uart_block + marker, 1)

    device_marker = '{"uart2", &uart_dev_ops, (void *)&uart2_data },'
    device_entry = '\t{"uart1", &uart_dev_ops, (void *)&uart1_data },\n'
    if '{"uart1", &uart_dev_ops, (void *)&uart1_data },' not in content:
        if device_marker not in content:
            raise BuildError(f"Jieli board file has no uart2 device entry: {board_file}")
        content = content.replace(device_marker, device_entry + device_marker, 1)

    board_file.write_text(content, encoding="utf-8")


def configure_full_stack_wifi(board_file: Path) -> None:
    """Add the AC7916A RF calibration required by the WiFi SDK libraries."""
    if not board_file.is_file():
        return

    content = board_file.read_text(encoding="utf-8")
    if "wifi_calibration_param wifi_calibration_param" in content:
        return

    marker = "/**************************  POWER config ****************************/"
    calibration = (
        "#if defined CONFIG_BT_ENABLE || defined CONFIG_WIFI_ENABLE\n"
        "#include \"wifi/wifi_connect.h\"\n"
        "const struct wifi_calibration_param wifi_calibration_param = {\n"
        "    .xosc_l = 0xb,\n"
        "    .xosc_r = 0xb,\n"
        "    .pa_trim_data = {1, 7, 4, 7, 11, 1, 7},\n"
        "    .mcs_dgain = {45, 45, 45, 42, 60, 60, 75, 70,\n"
        "                   62, 52, 50, 38, 62, 80, 70, 62,\n"
        "                   50, 48, 40, 36},\n"
        "};\n"
        "#endif\n\n"
    )
    if marker not in content:
        raise BuildError(f"Jieli board file has no power config marker: {board_file}")
    board_file.write_text(content.replace(marker, calibration + marker, 1), encoding="utf-8")


def configure_full_stack_app_config(app_config_file: Path) -> None:
    """Enable the vendor Wi-Fi/BLE pieces used by the Tuya full-stack image."""
    if not app_config_file.is_file():
        return

    content = app_config_file.read_text(encoding="utf-8")
    marker = "/* TuyaOpen Jieli full-stack network/BLE configuration. */"
    if marker in content:
        return

    config = """/* TuyaOpen Jieli full-stack network/BLE configuration. */
#define CONFIG_NET_ENABLE                  1
#define CONFIG_WIFI_ENABLE

#ifdef CONFIG_BT_ENABLE
#define CONFIG_BT_RX_BUFF_SIZE              0
#define CONFIG_BT_TX_BUFF_SIZE              0
#define TCFG_USER_BLE_ENABLE                1
#define TCFG_USER_BT_CLASSIC_ENABLE         0
#define BT_NET_CFG_EN                       0
#define BT_NET_HID_EN                       0
#define TCFG_BLE_SECURITY_EN                0
#endif

"""
    insert_at = content.rfind("#endif")
    if insert_at < 0:
        raise BuildError(f"Jieli app_config.h has no final #endif: {app_config_file}")
    app_config_file.write_text(content[:insert_at] + config + content[insert_at:], encoding="utf-8")


def configure_full_stack_board(board_file: Path) -> None:
    """Apply the vendor board initialization needed before Tuya starts networking."""
    configure_full_stack_wifi(board_file)
    content = board_file.read_text(encoding="utf-8")
    if "cfg_file_parse();" in content:
        return

    marker = "void board_init()\n{\n\tboard_power_init();"
    replacement = marker + "\n#ifdef CONFIG_BT_ENABLE\n    void cfg_file_parse(void);\n    cfg_file_parse();\n#endif"
    if marker not in content:
        raise BuildError(f"Jieli board file has no board_init power init: {board_file}")
    board_file.write_text(content.replace(marker, replacement, 1), encoding="utf-8")


def resolve_sdk_root(
    environ: Optional[Mapping[str, str]] = None,
    module_root: Path = MODULE_ROOT,
) -> Path:
    env = os.environ if environ is None else environ
    configured = env.get("JIELI_SDK_ROOT", "").strip()
    candidates = []
    if configured:
        candidates.append(Path(configured).expanduser())
    candidates.append((module_root / "AC79_AIoT_SDK").resolve())
    candidates.append((module_root / "../../../AC79_AIoT_SDK").resolve())

    for candidate in candidates:
        if (candidate / "apps/demo/demo_hello/board/wl82/Makefile").is_file():
            return candidate

    searched = ", ".join(str(path) for path in candidates)
    raise BuildError(
        "AC79 SDK not found; set JIELI_SDK_ROOT to a fw-AC79_AIoT_SDK checkout. "
        f"Searched: {searched}"
    )


def resolve_tool_dir(
    sdk_root: Path,
    environ: Optional[Mapping[str, str]] = None,
    module_root: Path = MODULE_ROOT,
) -> Path:
    env = os.environ if environ is None else environ
    configured = env.get("JIELI_TOOL_DIR", "").strip()
    candidates = []
    if configured:
        candidates.append(Path(configured).expanduser())
    candidates.extend(
        [
            (sdk_root.parent / "ipc_ac7916a/toolchain/jieli-linux-toolchains/pi32v2/bin").resolve(),
            Path("C:/JL/pi32/bin"),
            Path("/opt/jieli/pi32v2/bin"),
            (module_root.parents[2] / "ipc_ac7916a/toolchain/jieli-linux-toolchains/pi32v2/bin").resolve(),
            (module_root.parents[3] / "ipc_ac7916a/toolchain/jieli-linux-toolchains/pi32v2/bin").resolve(),
        ]
    )

    required = ("clang", "lto-wrapper", "lto-ar", "objdump", "objsizedump")
    for candidate in candidates:
        if candidate.is_dir() and all(resolve_tool_path(candidate, name).is_file() for name in required):
            return candidate

    searched = ", ".join(str(path) for path in candidates)
    raise BuildError(
        "Jieli pi32v2 toolchain not found; set JIELI_TOOL_DIR to pi32v2/bin. "
        f"Required tools: {', '.join(required)}. Searched: {searched}"
    )


def build_make_command(sdk_root: Path, tool_dir: Path, jobs: int = 1) -> list[str]:
    if jobs < 1:
        raise ValueError("jobs must be at least 1")
    board_dir = sdk_root / BOARD_BUILD_RELATIVE
    command = [
        "make",
        "-C",
        str(board_dir),
        f"TOOL_DIR={tool_dir}",
        f"-j{jobs}",
        "pre_build",
        "../../../../../cpu/wl82/tools/sdk.elf",
    ]
    if os.name == "nt":
        command.insert(4, "LINK_AT=0")
    return command


def create_staging_tree(
    sdk_root: Path,
    staging_root: Path,
    tuyaopen_root: Path,
    header_dir: Optional[Path] = None,
    full_stack: bool = False,
    tuya_lib_dir: Optional[Path] = None,
) -> Path:
    """Create a small overlay tree without modifying the vendor checkout."""
    if staging_root.exists():
        shutil.rmtree(staging_root)

    build_root = staging_root / "build"
    build_root.mkdir(parents=True)
    for name in ("cpu", "include_lib", "lib", "tools"):
        link_directory(build_root / name, sdk_root / name)

    apps_root = build_root / "apps"
    apps_root.mkdir()
    link_directory(apps_root / "common", sdk_root / "apps/common")
    shutil.copytree(
        sdk_root / "apps/demo/demo_hello",
        apps_root / "demo/demo_hello",
    )
    configure_reference_log_uart(apps_root / "demo/demo_hello/board/wl82/board.c")
    configure_service_uart(apps_root / "demo/demo_hello/board/wl82/board.c")
    if full_stack:
        configure_full_stack_board(apps_root / "demo/demo_hello/board/wl82/board.c")
        configure_full_stack_app_config(apps_root / "demo/demo_hello/include/app_config.h")
    platform_root = tuyaopen_root / "platform/JIELI"
    entry_source = "tuyaos_switch_app_main.c" if full_stack else "tuyaos_app_main.c"
    shutil.copy2(platform_root / entry_source, build_root / "tuyaos_app_main.c")
    if not full_stack:
        shutil.copy2(
            tuyaopen_root / "examples/get-started/jieli_uart_hello/src/example_jieli_uart_hello.c",
            build_root / "tuyaopen_uart_hello.c",
        )
    shutil.copytree(
        platform_root / "tuyaos/tuyaos_adapter",
        build_root / "tuyaos_adapter",
    )
    utilities_root = tuyaopen_root / "tools/porting/adapter/utilities"
    if utilities_root.is_dir():
        shutil.copytree(utilities_root, build_root / "tuya_utilities")

    makefile = apps_root / "demo/demo_hello/board/wl82/Makefile"
    content = makefile.read_text(encoding="utf-8")
    vendor_main = "../../../../../apps/demo/demo_hello/app_main.c"
    if vendor_main not in content:
        raise BuildError(f"AC79 demo Makefile has no app_main source: {makefile}")
    content = content.replace(vendor_main, "../../../../../tuyaos_app_main.c")
    extra_sources = "c_SRC_FILES += \\\n"
    if not full_stack:
        extra_sources += "    ../../../../../tuyaopen_uart_hello.c \\\n"
    extra_sources += (
        "    ../../../../../tuyaos_adapter/src/tkl_output.c \\\n"
        "    ../../../../../tuyaos_adapter/src/tkl_system.c \\\n"
        "    ../../../../../tuyaos_adapter/src/tkl_uart.c \\\n"
        "    ../../../../../tuyaos_adapter/src/tkl_thread.c \\\n"
        "    ../../../../../tuyaos_adapter/src/tkl_mutex.c \\\n"
        "    ../../../../../tuyaos_adapter/src/tkl_semaphore.c \\\n"
        "    ../../../../../tuyaos_adapter/src/tkl_queue.c \\\n"
        "    ../../../../../tuyaos_adapter/src/tkl_sleep.c \\\n"
        "    ../../../../../tuyaos_adapter/src/tkl_flash.c \\\n"
        "    ../../../../../tuyaos_adapter/src/tkl_ota.c \\\n"
        "    ../../../../../tuyaos_adapter/src/tkl_assert.c \\\n"
        "    ../../../../../tuyaos_adapter/src/tkl_bluetooth.c \\\n"
        "    ../../../../../tuyaos_adapter/src/tkl_network.c \\\n"
        "    ../../../../../tuyaos_adapter/src/tkl_wifi.c \\\n"
        "    ../../../../../tuyaos_adapter/src/tuyaopen_license.c \\\n"
        "    ../../../../../tuya_utilities/src/tuya_hashmap.c \\\n"
        "    ../../../../../tuya_utilities/src/tuya_list.c \\\n"
        "    ../../../../../tuya_utilities/src/tuya_mem_heap.c \\\n"
        "    ../../../../../tuya_utilities/src/tuya_queue.c \\\n"
        "    ../../../../../tuya_utilities/src/tuya_ringbuf.c \\\n"
        "    ../../../../../tuya_utilities/src/tuya_smartpointer.c \\\n"
        "    ../../../../../tuya_utilities/src/tuya_tools.c\n"
    )
    if full_stack:
        extra_sources = extra_sources.rstrip("\n") + " \\\n"
        extra_sources += (
            "    ../../../../../apps/common/config/bt_profile_config.c \\\n"
            "    ../../../../../apps/common/config/log_config/app_config.c \\\n"
            "    ../../../../../apps/common/config/log_config/lib_btctrler_config.c \\\n"
            "    ../../../../../apps/common/config/log_config/lib_btstack_config.c \\\n"
            "    ../../../../../apps/common/net/assign_macaddr.c \\\n"
            "    ../../../../../apps/common/net/config_network.c \\\n"
            "    ../../../../../apps/common/net/platform_cfg.c \\\n"
            "    ../../../../../apps/common/net/wifi_conf.c\n"
        )
    marker = "c_OBJS    :="
    if marker not in content:
        raise BuildError(f"AC79 demo Makefile has no object list marker: {makefile}")
    content = content.replace(marker, extra_sources + "\n" + marker, 1)
    if full_stack:
        # The TuyaOpen hello template is a no-SDRAM image by default.  The
        # AC7916A Wi-Fi/BLE SDK libraries use the SDRAM linker layout (the
        # vendor demo_wifi image is configured this way as well), so remove
        # the template-only no-SDRAM define from the staging Makefile.
        content = content.replace("\t-DCONFIG_NO_SDRAM_ENABLE \\\n", "", 1)
    content += "\n"
    content += "INCLUDES += \\\n"
    content += f"    -I{tuyaopen_root}/tools/porting/adapter/system \\\n"
    content += f"    -I{tuyaopen_root}/tools/porting/adapter/uart \\\n"
    content += f"    -I{tuyaopen_root}/tools/porting/adapter/init/include \\\n"
    content += f"    -I{tuyaopen_root}/tools/porting/adapter/utilities/include \\\n"
    content += f"    -I{tuyaopen_root}/tools/porting/adapter/flash \\\n"
    content += f"    -I{tuyaopen_root}/tools/porting/adapter/network \\\n"
    content += f"    -I{tuyaopen_root}/tools/porting/adapter/wifi \\\n"
    content += f"    -I{tuyaopen_root}/tools/porting/adapter/bluetooth \\\n"
    content += f"    -I{tuyaopen_root}/tools/porting/adapter/timer \\\n"
    content += f"    -I{tuyaopen_root}/tools/porting/adapter/security \\\n"
    content += "    -I../../../../../apps/common/include \\\n"
    content += "    -I../../../../../apps/common/config/include \\\n"
    content += "    -I../../../../../include_lib/btstack \\\n"
    content += "    -I../../../../../include_lib/btstack/le \\\n"
    content += "    -I../../../../../include_lib/btctrler \\\n"
    content += "    -I../../../../../include_lib/btctrler/port/wl82 \\\n"
    content += f"    -I{tuyaopen_root}/src/common/include\n"
    content += "INCLUDES += \\\n"
    content += "    -I../../../../../tuyaos_adapter/include \\\n"
    content += "    -I../../../../../include_lib/driver/device \\\n"
    content += "    -I../../../../../include_lib/driver/cpu/wl82 \\\n"
    content += "    -I../../../../../include_lib/net/lwip_2_2_0 \\\n"
    content += "    -I../../../../../include_lib/net/lwip_2_2_0/lwip/src/include \\\n"
    content += "    -I../../../../../include_lib/net/lwip_2_2_0/lwip/src/include/compat \\\n"
    content += "    -I../../../../../include_lib/net/lwip_2_2_0/lwip/port \\\n"
    content += "    -I../../../../../include_lib/system \\\n"
    content += "    -I../../../../../include_lib/system/generic \\\n"
    content += "    -I../../../../../include_lib/net \\\n"
    content += "    -I../../../../../include_lib/utils \\\n"
    content += "    -I../../../../../include_lib/utils/syscfg \\\n"
    content += "    -I../../../../../include_lib/utils/event \\\n"
    content += "    -I../../../../../include_lib\n"
    content += "INCLUDES += -I../../../../../include_lib/net\n"
    content += "CFLAGS += -include stdbool.h -DBOOL_DEFINE_CONFLICT\n"
    if full_stack:
        content += "DEFINES += -DCONFIG_NET_ENABLE=1 -DCONFIG_BT_ENABLE=1 -DCONFIG_TWS_ENABLE -DCONFIG_BTCTRLER_TASK_DEL_ENABLE -DCONFIG_LMP_CONN_SUSPEND_ENABLE -DCONFIG_LMP_REFRESH_ENCRYPTION_KEY_ENABLE\n"
        if tuya_lib_dir is None:
            raise BuildError("TuyaOpen library directory is required for the full wl82 image")
        content += "LFLAGS += \\\n"
        # The vendor LTO used-symbol list does not reference wlc_main when
        # Wi-Fi is entered through the Tuya TKL layer.  Force-retain the
        # vendor entry point so cpu.a[wlc.c.o] is extracted by the linker.
        content += "    -u wlc_main \\\n"
        content += f"    --start-group {tuya_lib_dir}/libtuyaapp.a {tuya_lib_dir}/libtuyaos.a \\\n"
        # The vendor base Makefile links cpu.a/system.a before this Tuya
        # library group.  BLE/Wi-Fi archives introduce aes/SDRAM allocator
        # references later, so repeat these provider archives inside the
        # group to let the linker rescan them and resolve those symbols.
        content += "    ../../../../../cpu/wl82/liba/cpu.a \\\n"
        content += "    ../../../../../cpu/wl82/liba/system.a \\\n"
        content += "    ../../../../../cpu/wl82/liba/hsm.a \\\n"
        content += "    ../../../../../cpu/wl82/liba/event.a \\\n"
        content += "    ../../../../../cpu/wl82/liba/common_lib.a \\\n"
        content += "    ../../../../../cpu/wl82/liba/wpasupplicant.a \\\n"
        content += "    ../../../../../cpu/wl82/liba/http_cli.a \\\n"
        content += "    ../../../../../cpu/wl82/liba/https_cli.a \\\n"
        content += "    ../../../../../cpu/wl82/liba/json.a \\\n"
        content += "    ../../../../../cpu/wl82/liba/libmbedtls_3_4_0.a \\\n"
        content += "    ../../../../../cpu/wl82/liba/lwip_2_2_0.a \\\n"
        content += "    ../../../../../cpu/wl82/liba/wl_wifi_sta.a \\\n"
        content += "    ../../../../../cpu/wl82/liba/net_server.a \\\n"
        content += "    ../../../../../cpu/wl82/liba/wl_rf_common.a \\\n"
        content += "    ../../../../../cpu/wl82/liba/btctrler.a \\\n"
        content += "    ../../../../../cpu/wl82/liba/btstack.a \\\n"
        content += "    ../../../../../cpu/wl82/liba/crypto_toolbox_Osize.a \\\n"
        content += "    ../../../../../cpu/wl82/liba/lib_ccm_aes.a \\\n"
        content += "    --end-group\n"
    if header_dir is not None:
        content += f"INCLUDES += -I{header_dir}\n"
    makefile.write_text(content, encoding="utf-8")
    return build_root


def find_qio_artifact(tools_dir: Path) -> Path:
    # Without the vendor host-client, app.bin is the artifact generated by the
    # current build. Prefer it over stale packages kept in the SDK checkout.
    for name in ("app.bin", "jl_isd.ufw", "jl_isd.fw"):
        candidate = tools_dir / name
        if candidate.is_file() and candidate.stat().st_size > 0:
            return candidate
    raise BuildError(
        f"Jieli postbuild produced no flash package in {tools_dir}; "
        "expected jl_isd.ufw, jl_isd.fw, or app.bin"
    )


def tuya_qio_name(params: Mapping[str, str]) -> str:
    project = params.get("CONFIG_PROJECT_NAME", "jieli_uart_hello")
    version = params.get("CONFIG_PROJECT_VERSION", "1.0.0")
    return f"{project}_QIO_{version}.bin"
