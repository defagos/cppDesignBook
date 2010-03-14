@echo off

set BAT_FILE_DIR=%~dp0

"%BAT_FILE_DIR%\common\generator.bat" MSVC9x64 "%BAT_FILE_DIR%\.." "%BAT_FILE_DIR%"

set BAT_FILE_DIR=