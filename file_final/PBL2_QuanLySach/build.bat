@echo off
REM =====================================================================
REM  build.bat - Bien dich chuong trinh khi may KHONG co "make"
REM  Cach dung: mo Command Prompt tai thu muc PBL2 roi go:  build.bat
REM =====================================================================
setlocal

echo === Dang bien dich chuong trinh QUAN LY SACH ===
g++ -std=c++11 -Wall -Wextra -Iinclude src\*.cpp -o QuanLySach.exe

if errorlevel 1 (
    echo.
    echo === BIEN DICH THAT BAI - hay doc thong bao loi o tren ===
    pause
    exit /b 1
)

echo.
echo === Bien dich thanh cong: QuanLySach.exe ===
echo === Dang chay chuong trinh... ===
echo.
QuanLySach.exe

endlocal
