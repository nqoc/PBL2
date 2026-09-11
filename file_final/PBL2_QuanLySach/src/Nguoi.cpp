// =====================================================================
//  Nguoi.cpp - Cai dat lop co so Nguoi
// =====================================================================
#include "Nguoi.h"
#include "TienIch.h"
#include "NgoaiLe.h"

#include <iostream>
#include <iomanip>
#include <cctype>

using namespace std;

Nguoi::Nguoi() {}

Nguoi::Nguoi(const string& ma_, const string& hoTen_, const string& sdt_,
             const string& diaChi_, const string& email_)
    : ma(ma_), hoTen(hoTen_), soDienThoai(sdt_), diaChi(diaChi_), email(email_) {}

Nguoi::~Nguoi() {}

void Nguoi::setSDT(const string& s) {
    // So dien thoai: chi gom chu so, dai 9..11
    if (s.size() < 9 || s.size() > 11)
        throw LoiDuLieu("So dien thoai phai co 9 den 11 chu so.");
    for (size_t i = 0; i < s.size(); ++i)
        if (!isdigit(static_cast<unsigned char>(s[i])))
            throw LoiDuLieu("So dien thoai chi duoc chua chu so.");
    soDienThoai = s;
}

void Nguoi::setEmail(const string& s) {
    if (s.empty()) { email = ""; return; }         // cho phep bo trong
    size_t at  = s.find('@');
    size_t dot = s.rfind('.');
    if (at == string::npos || dot == string::npos || at == 0 || dot < at + 2
        || dot + 2 > s.size())
        throw LoiDuLieu("Email khong dung dinh dang (vi du: ten@mail.com).");
    email = s;
}

void Nguoi::nhap() {
    hoTen = Nhap::chuoi("  Ho ten            : ");
    while (true) {
        try { setSDT(Nhap::chuoi("  So dien thoai     : ")); break; }
        catch (const LoiDuLieu& e) { cout << "  >> " << e.what() << "\n"; }
    }
    diaChi = Nhap::chuoi("  Dia chi           : ", true);
    while (true) {
        try { setEmail(Nhap::chuoi("  Email (co the bo) : ", true)); break; }
        catch (const LoiDuLieu& e) { cout << "  >> " << e.what() << "\n"; }
    }
}

void Nguoi::xuatChiTiet() const {
    cout << "  Ma            : " << ma << '\n'
         << "  Ho ten        : " << hoTen << '\n'
         << "  Vai tro       : " << vaiTro() << '\n'
         << "  So dien thoai : " << soDienThoai << '\n'
         << "  Dia chi       : " << diaChi << '\n'
         << "  Email         : " << email << '\n';
}

void Nguoi::xuatDong() const {
    cout << left << setw(10) << ma
         << left << setw(26) << catBot(hoTen, 25)
         << left << setw(14) << soDienThoai
         << left << setw(24) << catBot(diaChi, 23)
         << left << setw(24) << catBot(email, 23);
}

string Nguoi::toCSV() const {
    return ma + "|" + hoTen + "|" + soDienThoai + "|" + diaChi + "|" + email;
}

void Nguoi::fromCSV(const vector<string>& p) {
    if (p.size() < 5) throw LoiFile("Dong du lieu Nguoi thieu truong.");
    ma          = p[0];
    hoTen       = p[1];
    soDienThoai = p[2];
    diaChi      = p[3];
    email       = p[4];
}
