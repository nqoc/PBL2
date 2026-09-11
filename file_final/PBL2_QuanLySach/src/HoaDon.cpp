// =====================================================================
//  HoaDon.cpp
// =====================================================================
#include "HoaDon.h"
#include "TienIch.h"
#include "NgoaiLe.h"

#include <iostream>
#include <iomanip>
#include <sstream>
#include <cstdlib>

using namespace std;

HoaDon::HoaDon() : tiLeChietKhau(0.0) {}

HoaDon::HoaDon(const string& ma_, const string& ngay_, const string& nguoiLap_,
               const string& maKH, double tiLeCK)
    : ChungTu(ma_, ngay_, nguoiLap_), maKhachHang(maKH), tiLeChietKhau(tiLeCK) {}

void HoaDon::setTiLeChietKhau(double t) {
    if (t < 0.0 || t > 0.5)
        throw LoiDuLieu("Ti le chiet khau phai tu 0% den 50%.");
    tiLeChietKhau = t;
}

double HoaDon::tienChietKhau() const { return tongTienHang() * tiLeChietKhau; }

string HoaDon::loaiChungTu() const { return "HOA DON BAN HANG"; }

double HoaDon::thanhToan() const { return tongTienHang() - tienChietKhau(); }

void HoaDon::inChungTu() const {
    ChungTu::inChungTu();                       // in phan chung
    cout << right << setw(64) << "Chiet khau: "
         << right << setw(14)
         << (dinhDangTien(tienChietKhau()) + "  ("
             + doiSangChuoi(tiLeChietKhau * 100, 1) + "%)") << "\n";
    cout << right << setw(64) << "PHAI THANH TOAN: "
         << right << setw(14) << dinhDangTien(thanhToan()) << "\n";
    cout << "  Khach hang: "
         << (maKhachHang.empty() ? string("Khach le") : maKhachHang) << "\n";
    Man::duong('=', 78);
}

void HoaDon::inTieuDeBang() {
    Man::duong('-', 96);
    cout << left  << setw(12) << "MA HD"
         << left  << setw(13) << "NGAY"
         << left  << setw(12) << "KHACH"
         << left  << setw(16) << "NGUOI LAP"
         << right << setw(6)  << "DONG"
         << right << setw(8)  << "SL"
         << right << setw(14) << "TIEN HANG"
         << right << setw(15) << "THANH TOAN" << "\n";
    Man::duong('-', 96);
}

void HoaDon::xuatDong() const {
    cout << left  << setw(12) << ma
         << left  << setw(13) << ngayLap
         << left  << setw(12) << (maKhachHang.empty() ? string("(le)") : maKhachHang)
         << left  << setw(16) << catBot(nguoiLap, 15)
         << right << setw(6)  << chiTiet.kichThuoc()
         << right << setw(8)  << tongSoLuong()
         << right << setw(14) << dinhDangTien(tongTienHang())
         << right << setw(15) << dinhDangTien(thanhToan());
}

string HoaDon::toCSV() const {
    ostringstream os;
    os << ChungTu::toCSV() << '|' << maKhachHang << '|'
       << fixed << setprecision(4) << tiLeChietKhau << '|' << chuoiChiTiet();
    return os.str();
}

void HoaDon::fromCSV(const vector<string>& p) {
    if (p.size() < 6) throw LoiFile("Dong du lieu HoaDon thieu truong.");
    ChungTu::fromCSV(p);
    maKhachHang   = p[3];
    tiLeChietKhau = atof(p[4].c_str());
    docChiTiet(p, 5);
}
