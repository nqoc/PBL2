// =====================================================================
//  SachGiaoKhoa.cpp
// =====================================================================
#include "SachGiaoKhoa.h"
#include "TienIch.h"
#include "NgoaiLe.h"

#include <sstream>
#include <cstdlib>

using namespace std;

SachGiaoKhoa::SachGiaoKhoa() : khoiLop(1) {}

SachGiaoKhoa::SachGiaoKhoa(const string& ma, const string& ten,
                           const string& maTG, const string& maTL,
                           const string& maNXB_, int nam,
                           double giaNhap_, double giaBan_, int soLuong,
                           const string& monHoc_, int khoiLop_,
                           const string& viTriKe_, const string& moTa_)
    : Sach(ma, ten, maTG, maTL, maNXB_, nam, giaNhap_, giaBan_, soLuong,
           viTriKe_, moTa_),
      monHoc(monHoc_), khoiLop(khoiLop_) {}

void SachGiaoKhoa::setKhoiLop(int l) {
    if (l < 1 || l > 12) throw LoiDuLieu("Khoi lop phai tu 1 den 12.");
    khoiLop = l;
}

string SachGiaoKhoa::loaiSach() const { return "Giao khoa"; }
string SachGiaoKhoa::maLoai()   const { return "GK"; }

Sach* SachGiaoKhoa::nhanBan() const { return new SachGiaoKhoa(*this); }

double SachGiaoKhoa::tiLeGiamGia() const { return 0.10; }

string SachGiaoKhoa::moTaThem() const {
    ostringstream os;
    os << "Mon " << monHoc << ", lop " << khoiLop;
    return os.str();
}

void SachGiaoKhoa::nhap() {
    Sach::nhap();                    // tai su dung phan nhap cua lop cha
    monHoc = Nhap::chuoi("  Mon hoc           : ");
    setKhoiLop(Nhap::soNguyen("  Khoi lop (1-12)   : ", 1, 12));
}

string SachGiaoKhoa::toCSV() const {
    ostringstream os;
    os << maLoai() << '|' << Sach::toCSV() << '|' << monHoc << '|' << khoiLop;
    return os.str();
}

void SachGiaoKhoa::fromCSV(const vector<string>& p) {
    if (p.size() < 14) throw LoiFile("Dong du lieu SachGiaoKhoa thieu truong.");
    Sach::fromCSV(p);
    monHoc  = p[12];
    khoiLop = atoi(p[13].c_str());
}
