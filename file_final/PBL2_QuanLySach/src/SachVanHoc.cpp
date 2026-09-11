// =====================================================================
//  SachVanHoc.cpp
// =====================================================================
#include "SachVanHoc.h"
#include "TienIch.h"
#include "NgoaiLe.h"

#include <sstream>

using namespace std;

SachVanHoc::SachVanHoc() : dichGia("Khong") {}

SachVanHoc::SachVanHoc(const string& ma, const string& ten,
                       const string& maTG, const string& maTL,
                       const string& maNXB_, int nam,
                       double giaNhap_, double giaBan_, int soLuong,
                       const string& theLoaiVH, const string& dichGia_,
                       const string& viTriKe_, const string& moTa_)
    : Sach(ma, ten, maTG, maTL, maNXB_, nam, giaNhap_, giaBan_, soLuong,
           viTriKe_, moTa_),
      theLoaiVanHoc(theLoaiVH), dichGia(dichGia_) {}

bool SachVanHoc::laSachDich() const {
    string d = veThuong(chuanHoa(dichGia));
    return !(d.empty() || d == "khong" || d == "none" || d == "-");
}

string SachVanHoc::loaiSach() const { return "Van hoc"; }
string SachVanHoc::maLoai()   const { return "VH"; }

Sach* SachVanHoc::nhanBan() const { return new SachVanHoc(*this); }

double SachVanHoc::tiLeGiamGia() const { return 0.05; }

string SachVanHoc::moTaThem() const {
    ostringstream os;
    os << theLoaiVanHoc;
    if (laSachDich()) os << ", dich gia: " << dichGia;
    else              os << ", tac pham trong nuoc";
    return os.str();
}

void SachVanHoc::nhap() {
    Sach::nhap();
    theLoaiVanHoc = Nhap::chuoi("  The loai van hoc  : ");
    dichGia       = Nhap::chuoi("  Dich gia (Khong)  : ");
}

string SachVanHoc::toCSV() const {
    ostringstream os;
    os << maLoai() << '|' << Sach::toCSV() << '|' << theLoaiVanHoc
       << '|' << dichGia;
    return os.str();
}

void SachVanHoc::fromCSV(const vector<string>& p) {
    if (p.size() < 14) throw LoiFile("Dong du lieu SachVanHoc thieu truong.");
    Sach::fromCSV(p);
    theLoaiVanHoc = p[12];
    dichGia       = p[13];
}
