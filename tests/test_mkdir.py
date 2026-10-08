import subprocess
import sys
import tempfile
import unittest
from pathlib import Path
from types import SimpleNamespace
from unittest.mock import patch

from tools.jieli_build import sdk_overlay
from tools.jieli_build.chip_profiles import JIELI_CHIPS
from tools.jieli_build.sdk_overlay import build_make_command


class JieliMkdirTest(unittest.TestCase):
    def test_windows_helper_creates_nested_directory_idempotently(self):
        helper = Path(sdk_overlay.__file__).resolve().parent / "mkdir.py"
        with tempfile.TemporaryDirectory() as temp_dir:
            target = Path(temp_dir) / "one" / "two"
            command = [sys.executable, str(helper), "-p", str(target)]
            self.assertEqual(subprocess.run(command, check=False).returncode, 0)
            self.assertTrue(target.is_dir())
            self.assertEqual(subprocess.run(command, check=False).returncode, 0)

    def test_windows_make_command_uses_quoted_sdk_python_helper(self):
        with tempfile.TemporaryDirectory() as temp_dir:
            sdk_root = Path(temp_dir) / "sdk root"
            tool_dir = Path(temp_dir) / "tool dir"
            helper = (Path(sdk_overlay.__file__).resolve().parent / "mkdir.py").as_posix()
            python = "C:/SDK Tools/Python/python.exe"
            with patch.object(sdk_overlay, "os", SimpleNamespace(name="nt")):
                with patch.object(sdk_overlay, "sys", SimpleNamespace(executable=python)):
                    command = build_make_command(sdk_root, tool_dir, jobs=2, chip=JIELI_CHIPS["wl83"])

        self.assertIn("LINK_AT=0", command)
        self.assertIn(f'MKDIR="{python}" "{helper}" -p', command)
        self.assertIn("-j2", command)


if __name__ == "__main__":
    unittest.main()
