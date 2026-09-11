// =====================================================================
//  NhaCungCap.cpp
// =====================================================================
#include "NhaCungCap.h"
#include "TienIch.h"
#include "NgoaiLe.h"

#include <iostream>
#include <iomanip>

using namespace std;

NhaCungCap::NhaCungCap() {}

NhaCungCap::NhaCungCap(const string& ma_, const string& tenCongTy,
                       const string& sdt_, const string& diaChi_,
                       const string& email_, const string& mst)
    : Nguoi(ma_, tenCongTy, sdt_, diaChi_, email_), maSoThue(mst) {}

string NhaCungCap::vaiTro() const { return "Nha cung cap"; }

void NhaCungCap::nhap() {
    Nguoi::nhap();
    maSoThue = Nhap::chuoi("  Ma so thue        : ", true);
}

void NhaCungCap::xuatChiTiet() const {
    Nguoi::xuatChiTiet();
    cout << "  Ma so thue    : " << maSoThue << '\n';
}

void NhaCungCap::xuatDong() const {
    cout << left << setw(10) << ma
         << left << setw(28) << catBot(hoTen, 27)
         << left << setw(13) << soDienThoai
         << left << setw(26) << catBot(diaChi, 25)
         << left << setw(16) << catBot(maSoThue, 15);
}

string NhaCungCap::toCSV() const {
    return Nguoi::toCSV() + "|" + maSoThue;
}

void NhaCungCap::fromCSV(const vector<string>& p) {
    if (p.size() < 6) throw LoiFile("Dong du lieu NhaCungCap thieu truong.");
    Nguoi::fromCSV(p);
    maSoThue = p[5];
}
