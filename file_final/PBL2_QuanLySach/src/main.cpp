// =====================================================================
//  main.cpp - Diem bat dau chuong trinh
//
//  Bien dich:  make            (hoac: g++ -std=c++11 -Iinclude src/*.cpp -o QuanLySach)
//  Chay     :  make run        (hoac: ./QuanLySach)
// =====================================================================
#include <iostream>
#include <exception>

#include "UngDung.h"

#ifdef _WIN32
#include <windows.h>
#endif

int main() {
#ifdef _WIN32
    // Mo rong cua so console de bang bieu khong bi xuong dong
    if (system("mode con: cols=112 lines=45 >nul 2>nul") != 0) { /* bo qua */ }
#endif

    try {
        UngDung app;
        app.chay();
    } catch (const std::exception& e) {
        std::cerr << "\nLOI NGHIEM TRONG: " << e.what() << "\n";
        return 1;
    } catch (...) {
        std::cerr << "\nLOI KHONG XAC DINH.\n";
        return 2;
    }
    return 0;
}
