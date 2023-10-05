@echo off

set gen_dir="gen"
set src_dir="src"
set build_dir="build"

if not exit %gen_dir% (mkdir %gen_dir%)
if not exit %build_dir% (mkdir %build_dir%)

if "%~1" == "--clear" (
  echo "[i] Cleaning build files..."
  rd /S /Q "%gen_dir%"
  rd /S /Q "%build_dir%"
  exit /B
)


cmake -G "MinGW Makefiles" -H"%src_dir%" -B"%gen_dir%" -DPICO_BOARD=pico_w
mingw32-make --directory="%gen_dir%" gce_pico_w_server

move "%gen_dir%\*.hex" "%build_dir%"
