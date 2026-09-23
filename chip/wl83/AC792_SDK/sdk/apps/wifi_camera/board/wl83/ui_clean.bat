
@echo off

set target_dir=..\/..\/..\/..\/apps\/wifi_camera\/board\/wl83
set make_file=Makefile
set orig_make_file=Makefile_orig


if not exist %orig_make_file% (
    exit /b 0
) 

del "%target_dir%\%orig_make_file%"

cd ../../../../
SET SCRIPT_PATH=tools
set PATH=%SCRIPT_PATH%\utils
make "clean_ac792n_wifi_camera"
exit /b 0
