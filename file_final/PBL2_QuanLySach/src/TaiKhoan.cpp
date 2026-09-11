// =====================================================================
//  TaiKhoan.cpp
// =====================================================================
#include "TaiKhoan.h"
#include "TienIch.h"
#include "NgoaiLe.h"

#include <iostream>
#include <iomanip>

using namespace std;

// Khoi tao thanh vien static (hang so cua lop)
const string TaiKhoan::QUYEN_ADMIN    = "ADMIN";
const string TaiKhoan::QUYEN_NHANVIEN = "NHANVIEN";

TaiKhoan::TaiKhoan() : quyen(QUYEN_NHANVIEN) {}

TaiKhoan::TaiKhoan(const string& tenDangNhap, const string& hoTen_,
                   const string& matKhauRo, const string& quyen_)
    : Nguoi(tenDangNhap, hoTen_, "", "", ""), quyen(quyen_) {
    matKhauBam = bamMatKhau(matKhauRo);
}

void TaiKhoan::setQuyen(const string& q) {
    if (q != QUYEN_ADMIN && q != QUYEN_NHANVIEN)
        throw LoiDuLieu("Quyen chi duoc la ADMIN hoac NHANVIEN.");
    quyen = q;
}

void TaiKhoan::datMatKhau(const string& matKhauRo) {
    if (matKhauRo.size() < 4)
        throw LoiDuLieu("Mat khau phai co it nhat 4 ky tu.");
    matKhauBam = bamMatKhau(matKhauRo);
}

bool TaiKhoan::kiemTraMatKhau(const string& matKhauRo) const {
    return bamMatKhau(matKhauRo) == matKhauBam;
}

string TaiKhoan::vaiTro() const {
    return laAdmin() ? "Quan tri vien" : "Nhan vien ban hang";
}

void TaiKhoan::nhap() {
    ma    = Nhap::chuoi("  Ten dang nhap     : ");
    hoTen = Nhap::chuoi("  Ho ten            : ");
    while (true) {
        try { datMatKhau(Nhap::matKhau("  Mat khau          : ")); break; }
        catch (const LoiDuLieu& e) { cout << "  >> " << e.what() << "\n"; }
    }
    int c = Nhap::soNguyen("  Quyen (1=Admin, 2=Nhan vien): ", 1, 2);
    quyen = (c == 1) ? QUYEN_ADMIN : QUYEN_NHANVIEN;
}

void TaiKhoan::xuatChiTiet() const {
    cout << "  Ten dang nhap : " << ma << '\n'
         << "  Ho ten        : " << hoTen << '\n'
         << "  Quyen         : " << quyen << " (" << vaiTro() << ")\n";
}

void TaiKhoan::xuatDong() const {
    cout << left << setw(18) << ma
         << left << setw(28) << catBot(hoTen, 27)
         << left << setw(12) << quyen
         << left << setw(24) << vaiTro();
}

string TaiKhoan::toCSV() const {
    return ma + "|" + hoTen + "|" + soDienThoai + "|" + diaChi + "|" + email
         + "|" + matKhauBam + "|" + quyen;
}

void TaiKhoan::fromCSV(const vector<string>& p) {
    if (p.size() < 7) throw LoiFile("Dong du lieu TaiKhoan thieu truong.");
    Nguoi::fromCSV(p);
    matKhauBam = p[5];
    quyen      = p[6];
}
