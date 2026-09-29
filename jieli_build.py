"""Compatibility imports for older Jieli build hooks.

New build code should import the focused helpers from tools.jieli_build.
"""

from tools.jieli_build.errors import BuildError
from tools.jieli_build.chip_profiles import JIELI_CHIPS, JielichipConfig, resolve_chip, resolve_sdk_root
from tools.jieli_build.toolchain import (
    TOOL_ALIASES,
    WINDOWS_TOOLCHAIN_INSTALLER_NAME,
    WINDOWS_TOOLCHAIN_INSTALLER_SHA256,
    _sha256_of,
    _verify_installer,
    download_windows_toolchain_installer,
    resolve_tool_dir,
    resolve_tool_path,
)
from tools.jieli_build.board_config import (
    configure_ac79_devkit_memory, configure_ac79_log_uart, configure_ac792_devkit_memory,
    configure_ac792_log_uart, configure_full_stack_app_config, configure_full_stack_board,
    configure_full_stack_wifi, configure_service_uart,
)
from tools.jieli_build.sdk_overlay import build_make_command, create_staging_tree, link_directory
from tools.jieli_build.packaging import find_qio_artifact, tuya_qio_name

MODULE_ROOT = __import__("tools.jieli_build.chip_profiles", fromlist=["PLATFORM_ROOT"]).PLATFORM_ROOT
BOARD_BUILD_RELATIVE = JIELI_CHIPS["wl82"].board_build_relative
TOOLS_RELATIVE = JIELI_CHIPS["wl82"].tools_relative
