@echo off
setlocal
cmake -S "%~dp0." -B "%~dp0build" || exit /b 1
cmake --build "%~dp0build" --parallel
