@echo off

set gen_dir="gen"
set src_dir="src"
set build_dir="build"

if not exit %gen_dir% (mkdir %gen_dir%)
if not exit %build_dir% (mkdir %build_dir%)

if "%~1" == "--clear" (
  echo "[i] Cleaning build files..."
  rd /S /Q "%gen_dir%"
  exit /B
)

gcc %src_dir%/client/*.c -o %build_dir%/gce_windows_client.exe -lws2_32