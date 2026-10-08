#!/usr/bin/env python3
"""Build and package a TuyaOpen example with a Jieli chip SDK."""

from __future__ import annotations

import os
import shlex
import shutil
import subprocess
import sys
from pathlib import Path

from tools.jieli_build.chip_profiles import PLATFORM_ROOT, resolve_chip, resolve_sdk_root
from tools.jieli_build.errors import BuildError
from tools.jieli_build.packaging import find_qio_artifact, run_postbuild, tuya_qio_name
from tools.jieli_build.sdk_overlay import build_make_command, clean_staging_tree, create_staging_tree
from tools.jieli_build.toolchain import resolve_tool_dir, resolve_tool_path


def parse_build_params(path: Path) -> dict[str, str]:
    params: dict[str, str] = {}
    for raw_line in path.read_text(encoding="utf-8").splitlines():
        line = raw_line.strip()
        if not line or line.startswith("#") or "=" not in line:
            continue
        key, value = line.split("=", 1)
        params[key.strip()] = value.strip().strip('"')
    return params


def resolve_board_name(params: dict[str, str]) -> str | None:
    """Return the selected Jieli board profile used by the staging hooks."""
    if params.get("CONFIG_BOARD_CHOICE_AC792N_DEVELOP_BOARD") in ("y", "true", "True"):
        return "AC792N_Develop_Board"
    return None


def _run(command: list[str], cwd: Path, env: dict[str, str]) -> None:
    print(f"[JIELI] run: {shlex.join(command)}")
    result = subprocess.run(command, cwd=cwd, env=env, check=False)
    if result.returncode != 0:
        raise BuildError(f"command failed with exit code {result.returncode}: {command[0]}")


def build(params: dict[str, str]) -> Path:
    chip_choice = params.get("CONFIG_CHIP_CHOICE", "").strip()
    if not chip_choice:
        raise BuildError("CONFIG_CHIP_CHOICE is missing; select the board in TuyaOpen Kconfig")
    chip = resolve_chip(chip_name=chip_choice)
    os.environ["JIELI_CHIP"] = chip.name
    sdk_root = resolve_sdk_root(chip_name=chip.name)
    tool_dir = resolve_tool_dir(sdk_root)
    tuyaopen_root = Path(params.get("OPEN_ROOT", ""))
    if not tuyaopen_root.is_dir():
        raise BuildError("OPEN_ROOT is missing from build parameters")
    output_dir_text = params.get("BIN_OUTPUT_DIR", "").strip()
    if not output_dir_text:
        raise BuildError("BIN_OUTPUT_DIR is missing from build parameters")
    output_dir = Path(output_dir_text)
    staging_root = output_dir.parent / "jieli-staging"
    header_dir_text = params.get("OPEN_HEADER_DIR", "").split()
    header_dir = Path(header_dir_text[0]) if header_dir_text else None
    tuya_lib_dir = Path(params.get("OPEN_LIBS_DIR", ""))
    build_root = create_staging_tree(
        sdk_root,
        staging_root,
        tuyaopen_root,
        header_dir,
        tuya_lib_dir=tuya_lib_dir,
        uart_log_port=int(params.get("CONFIG_JIELI_UART_LOG_PORT", "1" if chip.name == "wl82" else "0")),
        uart_log_baudrate=int(params.get("CONFIG_JIELI_UART_LOG_BAUDRATE", "115200")),
        platform_root=PLATFORM_ROOT,
        chip=chip,
        board_name=resolve_board_name(params),
    )
    jobs = max(1, int(os.environ.get("JIELI_BUILD_JOBS", "1")))
    env = os.environ.copy()
    vendor_source_root = sdk_root / chip.sdk_source_relative
    inherited_path = env.get("PATH", "").split(os.pathsep)
    if os.name == "nt":
        # GnuWin32 make picks sh.exe as its recipe shell when one is on PATH.
        # That shell mangles the Windows paths interpolated by the vendor
        # Makefile; remove those entries so make falls back to cmd.exe.
        inherited_path = [
            entry
            for entry in inherited_path
            if entry and not os.path.exists(os.path.join(entry, "sh.exe"))
        ]
    env["PATH"] = os.pathsep.join(
        (str(tool_dir), str(vendor_source_root / "tools/utils"), *inherited_path)
    )
    env["OBJDUMP"] = str(resolve_tool_path(tool_dir, "objdump"))
    env["OBJSIZEDUMP"] = str(resolve_tool_path(tool_dir, "objsizedump"))

    command = build_make_command(build_root, tool_dir, jobs, chip)
    _run(command, build_root, env)

    tools_dir = build_root / chip.sdk_source_relative / chip.tools_relative
    elf = build_root / chip.sdk_source_relative / chip.elf_relative
    if not elf.is_file() or elf.stat().st_size == 0:
        raise BuildError(f"Jieli linker did not produce {elf}")

    run_postbuild(build_root, tool_dir, env, chip)
    package = find_qio_artifact(tools_dir)

    output_dir.mkdir(parents=True, exist_ok=True)
    output = output_dir / tuya_qio_name(params)
    shutil.copy2(package, output)
    print(f"[JIELI] artifact: {output}")
    return output


def clean(param_dir: Path, params: dict[str, str]) -> None:
    """Remove only generated bridge outputs, without shelling into the SDK."""
    del params
    staging_root = param_dir.parent / "jieli-staging"
    if staging_root.is_dir():
        clean_staging_tree(staging_root)
        print(f"[JIELI] removed staging tree: {staging_root}")


def main(argv: list[str]) -> int:
    if len(argv) != 3 or argv[2] not in ("build", "clean"):
        print(f"usage: {argv[0]} <build-param-dir> <build|clean>", file=sys.stderr)
        return 2
    try:
        param_dir = Path(argv[1])
        param_file = param_dir / "build_param.config"
        params = parse_build_params(param_file)
        if argv[2] == "clean":
            clean(param_dir, params)
        else:
            build(params)
    except (BuildError, OSError, ValueError) as exc:
        print(f"[JIELI] build failed: {exc}", file=sys.stderr)
        return 1
    return 0


if __name__ == "__main__":
    sys.exit(main(sys.argv))
