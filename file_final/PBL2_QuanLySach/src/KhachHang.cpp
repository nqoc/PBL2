// =====================================================================
//  KhachHang.cpp
// =====================================================================
#include "KhachHang.h"
#include "TienIch.h"
#include "NgoaiLe.h"

#include <iostream>
#include <iomanip>
#include <cstdlib>

using namespace std;

KhachHang::KhachHang() : diemTichLuy(0) {}

KhachHang::KhachHang(const string& ma_, const string& hoTen_, const string& sdt_,
                     const string& diaChi_, const string& email_, int diem)
    : Nguoi(ma_, hoTen_, sdt_, diaChi_, email_), diemTichLuy(diem) {}

void KhachHang::setDiem(int d) {
    if (d < 0) throw LoiDuLieu("Diem tich luy khong duoc am.");
    diemTichLuy = d;
}

void KhachHang::congDiemTheoHoaDon(double soTienMua) {
    if (soTienMua <= 0) return;
    diemTichLuy += static_cast<int>(soTienMua / 10000.0);
}

double KhachHang::tiLeGiamThanhVien() const {
    if (diemTichLuy >= 1000) return 0.08;
    if (diemTichLuy >= 500)  return 0.05;
    if (diemTichLuy >= 200)  return 0.02;
    return 0.0;
}

string KhachHang::capThanhVien() const {
    if (diemTichLuy >= 1000) return "Kim cuong";
    if (diemTichLuy >= 500)  return "Vang";
    if (diemTichLuy >= 200)  return "Bac";
    return "Thuong";
}

string KhachHang::vaiTro() const { return "Khach hang"; }

void KhachHang::nhap() {
    Nguoi::nhap();                 // goi lai ham cua lop cha (tai su dung)
    diemTichLuy = 0;
}

void KhachHang::xuatChiTiet() const {
    Nguoi::xuatChiTiet();
    cout << "  Diem tich luy : " << diemTichLuy << '\n'
         << "  Cap thanh vien: " << capThanhVien()
         << "  (giam " << tiLeGiamThanhVien() * 100 << "%)\n";
}

void KhachHang::xuatDong() const {
    cout << left  << setw(10) << ma
         << left  << setw(24) << catBot(hoTen, 23)
         << left  << setw(13) << soDienThoai
         << left  << setw(24) << catBot(diaChi, 23)
         << right << setw(8)  << diemTichLuy
         << "   " << left << setw(11) << capThanhVien();
}

string KhachHang::toCSV() const {
    return Nguoi::toCSV() + "|" + doiSangChuoi(diemTichLuy);
}

void KhachHang::fromCSV(const vector<string>& p) {
    if (p.size() < 6) throw LoiFile("Dong du lieu KhachHang thieu truong.");
    Nguoi::fromCSV(p);
    diemTichLuy = atoi(p[5].c_str());
}
