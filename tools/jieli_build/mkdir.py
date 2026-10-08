"""Small Windows replacement for the JieLi SDK's missing mkdir_win tool."""

from __future__ import annotations

import sys
from pathlib import Path


def main(argv: list[str] | None = None) -> int:
    args = list(sys.argv[1:] if argv is None else argv)
    if args and args[0] == "-p":
        args.pop(0)
    if len(args) != 1:
        print("usage: mkdir.py [-p] DIRECTORY", file=sys.stderr)
        return 2
    Path(args[0]).mkdir(parents=True, exist_ok=True)
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
