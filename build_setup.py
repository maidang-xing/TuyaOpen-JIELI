#!/usr/bin/env python3
"""Validate the host inputs needed by the Jieli wl82 build bridge."""

from __future__ import annotations

import shutil
import sys

from jieli_build import BuildError, resolve_sdk_root, resolve_tool_dir


def main() -> int:
    try:
        sdk_root = resolve_sdk_root()
        tool_dir = resolve_tool_dir(sdk_root)
    except BuildError as exc:
        print(f"[JIELI] build setup failed: {exc}", file=sys.stderr)
        return 1

    make = shutil.which("make")
    if not make:
        print("[JIELI] build setup failed: make not found", file=sys.stderr)
        return 1

    # The postbuild script is (re)generated from download.c by make pre_build
    # on every build, so a fresh checkout only carries the source.  Validate
    # the source plus whatever generated variant exists.
    tools = sdk_root / "cpu/wl82/tools"
    postbuild = next(
        (name for name in ("download.sh", "download.bat") if (tools / name).is_file()),
        "download.c",
    )
    if not (tools / postbuild).is_file():
        print(f"[JIELI] build setup failed: postbuild source not found: {tools}", file=sys.stderr)
        return 1

    print(f"[JIELI] SDK: {sdk_root}")
    print(f"[JIELI] toolchain: {tool_dir}")
    print(f"[JIELI] make: {make}")
    print(f"[JIELI] postbuild: {tools / postbuild}")
    return 0


if __name__ == "__main__":
    sys.exit(main())
