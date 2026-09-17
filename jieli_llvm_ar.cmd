@echo off
setlocal
powershell.exe -NoProfile -ExecutionPolicy Bypass -File "%~dp0jieli_llvm_ar.ps1" %*
exit /b %ERRORLEVEL%
