import tempfile
import unittest
from pathlib import Path

from jieli_build import BuildError, configure_ac79_devkit_memory


class Ac79DevkitMemoryConfigTest(unittest.TestCase):
    def test_configures_flash_and_sdram_sizes_for_devkit(self):
        with tempfile.TemporaryDirectory() as temp_dir:
            app_config = Path(temp_dir) / "app_config.h"
            app_config.write_text(
                "#define __FLASH_SIZE__    (4 * 1024 * 1024)\n"
                "#define __SDRAM_SIZE__    (2 * 1024 * 1024)\n",
                encoding="utf-8",
            )

            configure_ac79_devkit_memory(app_config)

            content = app_config.read_text(encoding="utf-8")
            self.assertIn("#define __FLASH_SIZE__    (8 * 1024 * 1024)", content)
            self.assertIn("#define __SDRAM_SIZE__    (8 * 1024 * 1024)", content)

    def test_rejects_app_config_missing_a_memory_macro(self):
        with tempfile.TemporaryDirectory() as temp_dir:
            app_config = Path(temp_dir) / "app_config.h"
            app_config.write_text("#define __FLASH_SIZE__ (4 * 1024 * 1024)\n", encoding="utf-8")

            with self.assertRaises(BuildError):
                configure_ac79_devkit_memory(app_config)


if __name__ == "__main__":
    unittest.main()
