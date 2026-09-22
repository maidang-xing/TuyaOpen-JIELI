"""TuyaOpen flash bridge for Jieli AC79x boards.

On Windows, use the downloader shipped with the local AC79 SDK by default.
JIELI_FLASH_CMD remains available for board-specific uploader overrides.
The chip is selected via the JIELI_CHIP environment variable (default: wl82)
and falls back to probing the per-chip SDK directories on disk, including the
legacy wl82 layout where the SDK sat at the module root.
"""

from __future__ import annotations

import os
import shlex
import shutil
import subprocess
import tempfile
from pathlib import Path
from typing import Any


MODULE_ROOT = Path(__file__).resolve().parent

# (sdk_subdir, tools_subdir, isd -dev argument, boot address)
_FLASH_CHIPS = {
    "wl82": ("chip/wl82/AC79_AIoT_SDK", "cpu/wl82/tools", "wl82", "0x1c02000"),
    # wl83 (AC792N): entry kept for the bring-up; verify -dev/-boot against the
    # vendor docs before first use (chip/wl83/README.md).
    "wl83": ("chip/wl83/AC792_SDK", "sdk/cpu/wl83/tools", "wl83", "0x1c02000"),
}


def _resolve_flash_chip() -> tuple[str, Path, str, str] | None:
    name = os.environ.get("JIELI_CHIP", "wl82").strip() or "wl82"
    entry = _FLASH_CHIPS.get(name)
    if entry is None:
        return None
    sdk_dir, tools_subdir, dev, boot = entry
    candidates = [MODULE_ROOT / sdk_dir / tools_subdir]
    if name == "wl82":
        # Legacy layout fallback for checkouts predating the chip/ split.
        candidates.append(MODULE_ROOT / "AC79_AIoT_SDK" / "cpu/wl82" / "tools")
    for tools_dir in candidates:
        if (tools_dir / "isd_download.exe").is_file():
            return dev, tools_dir, dev, boot
    return None


def _split_command(command_text: str) -> list[str]:
    """Split a configured uploader command without corrupting Windows paths."""
    if os.name != "nt":
        return shlex.split(command_text)

    # POSIX mode treats backslashes in ``C:\\path`` as escape characters.  The
    # non-POSIX mode preserves them; remove only the quote characters that were
    # used to keep paths containing spaces together.
    tokens = shlex.split(command_text, posix=False)
    return [
        token[1:-1]
        if len(token) >= 2 and token[0] == token[-1] and token[0] in ("'", '"')
        else token
        for token in tokens
    ]


def _default_flash_command(image: Path) -> tuple[list[str], Path] | None:
    """Return the SDK's Windows USB downloader command when it is available."""
    if os.name != "nt":
        return None

    resolved = _resolve_flash_chip()
    if resolved is None:
        return None
    dev, tools_dir, _, boot_addr = resolved
    executable = tools_dir / "isd_download.exe"
    config = tools_dir / "isd_config.ini"
    uboot = tools_dir / "uboot.boot"
    cfg_tool = tools_dir / "cfg_tool.bin"
    if not all(path.is_file() for path in (executable, config, uboot, cfg_tool)):
        return None

    # The vendor tool erases the entire VM reserved area (0x10e000-0x3fd000,
    # ~3MB) on every flash by default, which includes the TuyaOpen KV
    # partition at 0x311000. Generate a copy of isd_config.ini with
    # VM_OPT=1 ("do not operate on the VM area when downloading code",
    # per isd_config_rule.c) so provisioning data survives re-flashing.
    # Set JIELI_FLASH_ERASE_VM=1 to restore the stock erase behaviour.
    if os.environ.get("JIELI_FLASH_ERASE_VM", "").strip() != "1":
        keepvm_config = tools_dir / "isd_config_keepvm.ini"
        try:
            content = config.read_text(encoding="utf-8", errors="replace")
            if "VM_OPT=0" in content:
                keepvm_config.write_text(
                    content.replace("VM_OPT=0", "VM_OPT=1", 1),
                    encoding="utf-8",
                )
                config = keepvm_config
        except OSError:
            pass  # fall back to the stock config

    return (
        [
            str(executable),
            str(config),
            "-gen2",
            "-tonorflash",
            "-dev",
            dev,
            "-boot",
            boot_addr,
            "-div1",
            "-wait",
            "300",
            "-uboot",
            str(uboot),
            "-app",
            str(image),
            str(cfg_tool),
            "-res",
            "cfg",
            "-reboot",
            "500",
            "-extend-bin",
        ],
        tools_dir,
    )


def platform_flash(
    *,
    using_data: dict[str, str],
    binfile: str,
    port: str,
    baud: int,
    boards_root: str,
    logger: Any,
) -> dict[str, object]:
    del boards_root

    image = Path(binfile)
    if not image.is_file() or image.stat().st_size == 0:
        return {"success": False, "message": f"firmware image not found: {image}"}

    values = {
        "binfile": str(image),
        "port": port,
        "baud": str(baud or 0),
        "chip": using_data.get("CONFIG_CHIP_CHOICE", "wl82"),
        "board": using_data.get("CONFIG_BOARD_CHOICE", "AC7916A"),
    }
    command_text = os.environ.get("JIELI_FLASH_CMD", "").strip()
    staged_dir = None
    working_dir = None
    if command_text:
        try:
            command = _split_command(command_text.format(**values))
        except (KeyError, ValueError) as exc:
            return {"success": False, "message": f"invalid JIELI_FLASH_CMD: {exc}"}
        if not command:
            return {"success": False, "message": "JIELI_FLASH_CMD is empty"}
    else:
        # isd_download packages the input by basename and rejects names longer
        # than 15 characters.  Keep the user-facing artifact name unchanged,
        # but stage long project outputs under the SDK's conventional app.bin.
        upload_image = image
        if len(image.name) > 15:
            staged_dir = tempfile.TemporaryDirectory(prefix="jieli_flash_")
            upload_image = Path(staged_dir.name) / "app.bin"
            shutil.copyfile(image, upload_image)

        default = _default_flash_command(upload_image)
        if default is None:
            if staged_dir is not None:
                staged_dir.cleanup()
            return {
                "success": False,
                "message": (
                    "Jieli SDK downloader is unavailable; set JIELI_FLASH_CMD to a "
                    "Jieli uploader command using {binfile}, {port}, and {baud} "
                    "placeholders"
                ),
            }
        command, working_dir = default

    logger.info(f"Jieli flash command: {shlex.join(command)}")
    try:
        try:
            result = subprocess.run(command, cwd=working_dir, check=False)
        except OSError as exc:
            return {"success": False, "message": f"cannot start Jieli uploader: {exc}"}
    finally:
        if staged_dir is not None:
            staged_dir.cleanup()
    if result.returncode != 0:
        return {"success": False, "message": f"uploader exited with {result.returncode}"}
    return {"success": True, "message": "Jieli uploader completed"}
