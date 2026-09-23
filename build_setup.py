#!/usr/bin/env python3
"""Validate the host inputs needed by the Jieli wl82 build bridge."""

from __future__ import annotations

import os
import shutil
import sys

from jieli_build import (
    BuildError,
    resolve_chip,
    resolve_sdk_root,
    resolve_tool_dir,
    resolve_tool_path,
)


def main(argv: list[str] | None = None) -> int:
    args = sys.argv if argv is None else argv
    try:
        requested_chip = args[4].strip() if len(args) > 4 else ""
        chip_name = requested_chip or resolve_chip().name
        if chip_name not in ("wl82", "wl83"):
            raise BuildError(f"unsupported Jieli chip '{chip_name}'")
        os.environ["JIELI_CHIP"] = chip_name
        chip = resolve_chip()
        sdk_root = resolve_sdk_root()
        tool_dir = resolve_tool_dir(sdk_root)
    except BuildError as exc:
        print(f"[JIELI] build setup failed: {exc}", file=sys.stderr)
        return 1

    make = shutil.which("make")
    if not make:
        print("[JIELI] build setup failed: make not found", file=sys.stderr)
        return 1

    vendor_source_root = sdk_root / chip.sdk_source_relative
    postbuild = vendor_source_root / chip.tools_relative / "download.sh"
    host_client = shutil.which("host-client")
    if host_client and chip.name == "wl82" and not postbuild.is_file():
        print(f"[JIELI] build setup failed: postbuild script not found: {postbuild}", file=sys.stderr)
        return 1
    if not host_client:
        objcopy = resolve_tool_path(tool_dir, "objcopy")
        if not objcopy.is_file():
            print(
                "[JIELI] build setup failed: host-client is unavailable and "
                f"Jieli objcopy was not found: {objcopy}",
                file=sys.stderr,
            )
            return 1

    print(f"[JIELI] SDK: {vendor_source_root}")
    print(f"[JIELI] toolchain: {tool_dir}")
    print(f"[JIELI] make: {make}")
    print(f"[JIELI] postbuild: {postbuild if host_client else 'raw app.bin via objcopy'}")
    return 0


if __name__ == "__main__":
    sys.exit(main())
