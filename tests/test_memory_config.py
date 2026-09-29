import tempfile
import unittest
from pathlib import Path

from jieli_build import (
    BuildError,
    configure_ac79_devkit_memory,
    configure_ac792_devkit_memory,
)


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


class Ac792DevkitMemoryConfigTest(unittest.TestCase):
    CHIP = (
        "#define __FLASH_SIZE__    (1 * 1024 * 1024)\n"
        "#define __SDRAM_SIZE__    (2 * 1024 * 1024)\n"
    )
    BOARD = "#define CONFIG_NO_SDRAM_ENABLE\n"

    def _write(self, temp_dir, chip_content=CHIP, board_content=BOARD):
        chip = Path(temp_dir) / "chip_cfg.h"
        board = Path(temp_dir) / "board_demo.h"
        chip.write_text(chip_content, encoding="utf-8")
        board.write_text(board_content, encoding="utf-8")
        return chip, board

    def test_configures_flash_and_sdram_for_the_reference_sku(self):
        with tempfile.TemporaryDirectory() as temp_dir:
            chip, board = self._write(temp_dir)

            configure_ac792_devkit_memory(chip, board)

            content = chip.read_text(encoding="utf-8")
            self.assertIn("#define __FLASH_SIZE__    (8 * 1024 * 1024)", content)
            self.assertIn("#define __SDRAM_SIZE__    (16 * 1024 * 1024)", content)

    def test_targets_macros_by_name_not_by_first_occurrence(self):
        # A decoy carries the same literal before __FLASH_SIZE__. Rewriting the
        # first "(1 * 1024 * 1024)" would resize the decoy and leave flash alone.
        with tempfile.TemporaryDirectory() as temp_dir:
            chip, board = self._write(
                temp_dir,
                "#define __DECOY_SIZE__    (1 * 1024 * 1024)\n"
                "#define __FLASH_SIZE__    (1 * 1024 * 1024)\n"
                "#define __SDRAM_SIZE__    (2 * 1024 * 1024)\n",
            )

            configure_ac792_devkit_memory(chip, board)

            content = chip.read_text(encoding="utf-8")
            self.assertIn("#define __DECOY_SIZE__    (1 * 1024 * 1024)", content)
            self.assertIn("#define __FLASH_SIZE__    (8 * 1024 * 1024)", content)
            self.assertIn("#define __SDRAM_SIZE__    (16 * 1024 * 1024)", content)

    def test_enables_external_ddr_on_the_board_config(self):
        with tempfile.TemporaryDirectory() as temp_dir:
            chip, board = self._write(temp_dir)

            configure_ac792_devkit_memory(chip, board)

            content = board.read_text(encoding="utf-8")
            self.assertNotIn("CONFIG_NO_SDRAM_ENABLE", content)
            self.assertIn("External DDR is enabled", content)

    def test_rejects_a_chip_config_missing_a_memory_macro(self):
        with tempfile.TemporaryDirectory() as temp_dir:
            chip, board = self._write(temp_dir, chip_content="#define __FLASH_SIZE__ (1 * 1024 * 1024)\n")

            with self.assertRaises(BuildError):
                configure_ac792_devkit_memory(chip, board)

    def test_rejects_a_board_config_without_the_sdram_switch(self):
        with tempfile.TemporaryDirectory() as temp_dir:
            chip, board = self._write(temp_dir, board_content="/* no switch here */\n")

            with self.assertRaises(BuildError):
                configure_ac792_devkit_memory(chip, board)

    def test_rejects_a_duplicate_macro_definition(self):
        with tempfile.TemporaryDirectory() as temp_dir:
            chip, board = self._write(
                temp_dir,
                "#define __FLASH_SIZE__    (1 * 1024 * 1024)\n"
                "#define __FLASH_SIZE__    (1 * 1024 * 1024)\n"
                "#define __SDRAM_SIZE__    (2 * 1024 * 1024)\n",
            )

            with self.assertRaises(BuildError):
                configure_ac792_devkit_memory(chip, board)

    def test_accepts_crlf_line_endings(self):
        with tempfile.TemporaryDirectory() as temp_dir:
            chip = Path(temp_dir) / "chip_cfg.h"
            board = Path(temp_dir) / "board_demo.h"
            # write_bytes, because write_text would translate the newlines away.
            chip.write_bytes(
                b"#define __FLASH_SIZE__    (1 * 1024 * 1024)\r\n"
                b"#define __SDRAM_SIZE__    (2 * 1024 * 1024)\r\n"
            )
            board.write_bytes(b"#define CONFIG_NO_SDRAM_ENABLE\r\n")

            configure_ac792_devkit_memory(chip, board)

            content = chip.read_text(encoding="utf-8")
            self.assertIn("#define __FLASH_SIZE__    (8 * 1024 * 1024)", content)
            self.assertIn("#define __SDRAM_SIZE__    (16 * 1024 * 1024)", content)
            self.assertNotIn("CONFIG_NO_SDRAM_ENABLE", board.read_text(encoding="utf-8"))


if __name__ == "__main__":
    unittest.main()
