#!/usr/bin/env python3
"""Build and package a TuyaOpen example with a Jieli chip SDK."""

from __future__ import annotations

import os
import shlex
import shutil
import subprocess
import sys
from pathlib import Path

from jieli_build import (
    BuildError,
    build_make_command,
    create_staging_tree,
    find_qio_artifact,
    resolve_chip,
    resolve_sdk_root,
    resolve_tool_path,
    resolve_tool_dir,
    tuya_qio_name,
)


def parse_build_params(path: Path) -> dict[str, str]:
    params: dict[str, str] = {}
    for raw_line in path.read_text(encoding="utf-8").splitlines():
        line = raw_line.strip()
        if not line or line.startswith("#") or "=" not in line:
            continue
        key, value = line.split("=", 1)
        params[key.strip()] = value.strip().strip('"')
    return params


def _run(command: list[str], cwd: Path, env: dict[str, str]) -> None:
    print(f"[JIELI] run: {shlex.join(command)}")
    result = subprocess.run(command, cwd=cwd, env=env, check=False)
    if result.returncode != 0:
        raise BuildError(f"command failed with exit code {result.returncode}: {command[0]}")


def _generate_raw_app_bin(elf: Path, tools_dir: Path, tool_dir: Path) -> Path:
    """Generate the raw image with the section layout of the selected SDK."""
    sections = resolve_chip().raw_app_sections
    objcopy = resolve_tool_path(tool_dir, "objcopy")
    if not objcopy.is_file():
        raise BuildError(f"Jieli objcopy not found: {objcopy}")

    chunks: list[bytes] = []
    for section in sections:
        extracted = tools_dir / f".jieli{section.replace('.', '_')}.bin"
        result = subprocess.run(
            [str(objcopy), "-O", "binary", "-j", section, str(elf), str(extracted)],
            cwd=tools_dir,
            check=False,
        )
        if result.returncode != 0:
            raise BuildError(f"objcopy failed for ELF section {section}")
        if extracted.is_file():
            chunks.append(extracted.read_bytes())
            extracted.unlink()

    output = tools_dir / "app.bin"
    output.write_bytes(b"".join(chunks))
    if output.stat().st_size == 0:
        raise BuildError(f"Jieli ELF contains no application sections: {elf}")
    print(f"[JIELI] raw artifact: {output}")
    return output


def _run_postbuild(sdk_root: Path, tool_dir: Path, env: dict[str, str]) -> None:
    chip = resolve_chip()
    tools_dir = sdk_root / chip.sdk_source_relative / chip.tools_relative
    command_text = env.get("JIELI_POSTBUILD_CMD", "").strip()
    if command_text:
        _run(shlex.split(command_text), tools_dir, env)
        return

    elf = tools_dir / "sdk.elf"
    if shutil.which("host-client", path=env.get("PATH")) is None:
        _generate_raw_app_bin(elf, tools_dir, tool_dir)
        return

    script = tools_dir / "download.sh"
    if not script.is_file():
        raise BuildError(f"Jieli postbuild script not found: {script}")
    _run(["bash", str(script), "sdk"], tools_dir, env)


def build(params: dict[str, str]) -> Path:
    chip = params.get("CONFIG_CHIP_CHOICE", "wl82").strip() or "wl82"
    if chip not in ("wl82", "wl83"):
        raise BuildError(f"unsupported Jieli chip '{chip}'")
    os.environ["JIELI_CHIP"] = chip
    full_stack = params.get("CONFIG_JIELI_MINIMAL_HELLO") != "y"
    sdk_root = resolve_sdk_root()
    tool_dir = resolve_tool_dir(sdk_root)
    tuyaopen_root = Path(params.get("OPEN_ROOT", ""))
    if not tuyaopen_root.is_dir():
        raise BuildError("OPEN_ROOT is missing from build parameters")
    output_dir = Path(params.get("BIN_OUTPUT_DIR", ""))
    if not output_dir:
        raise BuildError("BIN_OUTPUT_DIR is missing from build parameters")
    staging_root = output_dir.parent / "jieli-staging"
    header_dir_text = params.get("OPEN_HEADER_DIR", "").split()
    header_dir = Path(header_dir_text[0]) if header_dir_text else None
    tuya_lib_dir = Path(params.get("OPEN_LIBS_DIR", "")) if full_stack else None
    build_root = create_staging_tree(
        sdk_root,
        staging_root,
        tuyaopen_root,
        header_dir,
        full_stack=full_stack,
        tuya_lib_dir=tuya_lib_dir,
        uart_log_port=int(params.get("CONFIG_JIELI_UART_LOG_PORT", "1" if chip == "wl82" else "0")),
        uart_log_baudrate=int(params.get("CONFIG_JIELI_UART_LOG_BAUDRATE", "1000000")),
    )
    jobs = max(1, int(os.environ.get("JIELI_BUILD_JOBS", "1")))
    env = os.environ.copy()
    vendor_source_root = sdk_root / resolve_chip().sdk_source_relative
    env["PATH"] = os.pathsep.join(
        (str(tool_dir), str(vendor_source_root / "tools/utils"), env.get("PATH", ""))
    )
    env["OBJDUMP"] = str(resolve_tool_path(tool_dir, "objdump"))
    env["OBJSIZEDUMP"] = str(resolve_tool_path(tool_dir, "objsizedump"))

    command = build_make_command(build_root, tool_dir, jobs)
    _run(command, build_root, env)

    profile = resolve_chip()
    tools_dir = build_root / profile.sdk_source_relative / profile.tools_relative
    elf = build_root / profile.sdk_source_relative / profile.elf_relative
    if not elf.is_file() or elf.stat().st_size == 0:
        raise BuildError(f"Jieli linker did not produce {elf}")

    _run_postbuild(build_root, tool_dir, env)
    package = find_qio_artifact(tools_dir)

    output_dir.mkdir(parents=True, exist_ok=True)
    output = output_dir / tuya_qio_name(params)
    shutil.copy2(package, output)
    print(f"[JIELI] artifact: {output}")
    return output


def clean(param_dir: Path, params: dict[str, str]) -> None:
    """Remove only generated bridge outputs, without shelling into the SDK."""
    chip_name = params.get("CONFIG_CHIP_CHOICE", "wl82").strip() or "wl82"
    if chip_name not in ("wl82", "wl83"):
        raise BuildError(f"unsupported Jieli chip '{chip_name}'")
    os.environ["JIELI_CHIP"] = chip_name
    chip = resolve_chip()
    sdk_root = resolve_sdk_root()
    for relative_path in (
        chip.sdk_source_relative / chip.elf_relative,
        chip.sdk_source_relative / chip.tools_relative / "app.bin",
    ):
        artifact = sdk_root / relative_path
        if artifact.is_file():
            artifact.unlink()
            print(f"[JIELI] removed generated artifact: {artifact}")

    staging_root = param_dir.parent / "jieli-staging"
    if staging_root.is_dir():
        shutil.rmtree(staging_root)
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
