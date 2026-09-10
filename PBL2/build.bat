@echo off 
echo. 
echo === Dang bien dich PBL2 ===
g++ -std=c++17 -Wall -Wextra -Iinclude src\*.cpp -o main.exe
echo.

if errorlevel 1 (
    echo === LOI BIEN DICH ===
    echo.
    pause 
    exit /b 1 
)

echo === OK ===
main.exe
echo.
pause