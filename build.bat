@echo off

if "%~1"=="" (
  echo "[E] No target given"
  exit /B
)

if exist "%~1/build.bat" (
  echo "[i] Building for %1..."
  cd "%~1"
  .\build.bat %2 %3
  cd ..
  exit /B
) else (
  echo "[E] No build script found for %1"
  exit /B
)