@echo off
setlocal

if not defined JIELI_TOOL_DIR set "JIELI_TOOL_DIR=C:\JL\pi32\bin"
if not exist "%JIELI_TOOL_DIR%\lto-ar.exe" (
    echo Jieli lto-ar not found in "%JIELI_TOOL_DIR%" 1>&2
    exit /b 1
)

"%JIELI_TOOL_DIR%\lto-ar.exe" s %*
exit /b %ERRORLEVEL%
