// =====================================================================
//  DanhMuc.cpp - Cai dat DanhMuc, TheLoai, TacGia, NhaXuatBan
// =====================================================================
#include "DanhMuc.h"
#include "TienIch.h"
#include "NgoaiLe.h"

#include <iostream>
#include <iomanip>

using namespace std;

// =====================  DanhMuc  =====================
DanhMuc::DanhMuc() {}

DanhMuc::DanhMuc(const string& ma_, const string& ten_, const string& moTa_)
    : ma(ma_), ten(ten_), moTa(moTa_) {}

DanhMuc::~DanhMuc() {}

void DanhMuc::nhap() {
    ten  = Nhap::chuoi("  Ten               : ");
    moTa = Nhap::chuoi("  Mo ta (co the bo) : ", true);
}

void DanhMuc::xuatChiTiet() const {
    cout << "  Ma      : " << ma << '\n'
         << "  Loai    : " << loai() << '\n'
         << "  Ten     : " << ten << '\n'
         << "  Mo ta   : " << moTa << '\n';
}

void DanhMuc::xuatDong() const {
    cout << left << setw(10) << ma
         << left << setw(30) << catBot(ten, 29)
         << left << setw(50) << catBot(moTa, 49);
}

string DanhMuc::toCSV() const { return ma + "|" + ten + "|" + moTa; }

void DanhMuc::fromCSV(const vector<string>& p) {
    if (p.size() < 3) throw LoiFile("Dong du lieu DanhMuc thieu truong.");
    ma   = p[0];
    ten  = p[1];
    moTa = p[2];
}

// =====================  TheLoai  =====================
TheLoai::TheLoai() {}

TheLoai::TheLoai(const string& ma_, const string& ten_, const string& moTa_)
    : DanhMuc(ma_, ten_, moTa_) {}

string TheLoai::loai() const { return "The loai"; }

// =====================  TacGia  =====================
TacGia::TacGia() {}

TacGia::TacGia(const string& ma_, const string& ten_, const string& qt,
               const string& moTa_)
    : DanhMuc(ma_, ten_, moTa_), quocTich(qt) {}

string TacGia::loai() const { return "Tac gia"; }

void TacGia::nhap() {
    DanhMuc::nhap();
    quocTich = Nhap::chuoi("  Quoc tich         : ");
}

void TacGia::xuatChiTiet() const {
    DanhMuc::xuatChiTiet();
    cout << "  Quoc tich: " << quocTich << '\n';
}

void TacGia::xuatDong() const {
    cout << left << setw(10) << ma
         << left << setw(30) << catBot(ten, 29)
         << left << setw(18) << catBot(quocTich, 17)
         << left << setw(40) << catBot(moTa, 39);
}

string TacGia::toCSV() const { return DanhMuc::toCSV() + "|" + quocTich; }

void TacGia::fromCSV(const vector<string>& p) {
    if (p.size() < 4) throw LoiFile("Dong du lieu TacGia thieu truong.");
    DanhMuc::fromCSV(p);
    quocTich = p[3];
}

// =====================  NhaXuatBan  =====================
NhaXuatBan::NhaXuatBan() {}

NhaXuatBan::NhaXuatBan(const string& ma_, const string& ten_, const string& dc,
                       const string& dt, const string& moTa_)
    : DanhMuc(ma_, ten_, moTa_), diaChi(dc), dienThoai(dt) {}

string NhaXuatBan::loai() const { return "Nha xuat ban"; }

void NhaXuatBan::nhap() {
    DanhMuc::nhap();
    diaChi    = Nhap::chuoi("  Dia chi           : ", true);
    dienThoai = Nhap::chuoi("  Dien thoai        : ", true);
}

void NhaXuatBan::xuatChiTiet() const {
    DanhMuc::xuatChiTiet();
    cout << "  Dia chi  : " << diaChi << '\n'
         << "  Dien thoai: " << dienThoai << '\n';
}

void NhaXuatBan::xuatDong() const {
    cout << left << setw(10) << ma
         << left << setw(28) << catBot(ten, 27)
         << left << setw(30) << catBot(diaChi, 29)
         << left << setw(14) << catBot(dienThoai, 13);
}

string NhaXuatBan::toCSV() const {
    return DanhMuc::toCSV() + "|" + diaChi + "|" + dienThoai;
}

void NhaXuatBan::fromCSV(const vector<string>& p) {
    if (p.size() < 5) throw LoiFile("Dong du lieu NhaXuatBan thieu truong.");
    DanhMuc::fromCSV(p);
    diaChi    = p[3];
    dienThoai = p[4];
}
