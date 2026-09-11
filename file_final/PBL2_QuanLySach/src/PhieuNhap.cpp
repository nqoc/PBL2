// =====================================================================
//  PhieuNhap.cpp
// =====================================================================
#include "PhieuNhap.h"
#include "TienIch.h"
#include "NgoaiLe.h"

#include <iostream>
#include <iomanip>
#include <sstream>

using namespace std;

PhieuNhap::PhieuNhap() {}

PhieuNhap::PhieuNhap(const string& ma_, const string& ngay_,
                     const string& nguoiLap_, const string& maNCC)
    : ChungTu(ma_, ngay_, nguoiLap_), maNhaCungCap(maNCC) {}

string PhieuNhap::loaiChungTu() const { return "PHIEU NHAP HANG"; }

double PhieuNhap::thanhToan() const { return tongTienHang(); }

void PhieuNhap::inChungTu() const {
    ChungTu::inChungTu();
    cout << right << setw(64) << "TONG PHAI TRA NCC: "
         << right << setw(14) << dinhDangTien(thanhToan()) << "\n";
    cout << "  Nha cung cap: " << maNhaCungCap << "\n";
    Man::duong('=', 78);
}

void PhieuNhap::inTieuDeBang() {
    Man::duong('-', 88);
    cout << left  << setw(12) << "MA PN"
         << left  << setw(13) << "NGAY"
         << left  << setw(12) << "NCC"
         << left  << setw(16) << "NGUOI LAP"
         << right << setw(6)  << "DONG"
         << right << setw(8)  << "SL"
         << right << setw(18) << "TONG TIEN" << "\n";
    Man::duong('-', 88);
}

void PhieuNhap::xuatDong() const {
    cout << left  << setw(12) << ma
         << left  << setw(13) << ngayLap
         << left  << setw(12) << maNhaCungCap
         << left  << setw(16) << catBot(nguoiLap, 15)
         << right << setw(6)  << chiTiet.kichThuoc()
         << right << setw(8)  << tongSoLuong()
         << right << setw(18) << dinhDangTien(thanhToan());
}

string PhieuNhap::toCSV() const {
    ostringstream os;
    os << ChungTu::toCSV() << '|' << maNhaCungCap << '|' << chuoiChiTiet();
    return os.str();
}

void PhieuNhap::fromCSV(const vector<string>& p) {
    if (p.size() < 5) throw LoiFile("Dong du lieu PhieuNhap thieu truong.");
    ChungTu::fromCSV(p);
    maNhaCungCap = p[3];
    docChiTiet(p, 4);
}
