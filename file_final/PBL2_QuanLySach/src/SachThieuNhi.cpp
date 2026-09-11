// =====================================================================
//  SachThieuNhi.cpp
// =====================================================================
#include "SachThieuNhi.h"
#include "TienIch.h"
#include "NgoaiLe.h"

#include <sstream>
#include <cstdlib>

using namespace std;

SachThieuNhi::SachThieuNhi() : doTuoiToiThieu(3), coTranhMinhHoa(true) {}

SachThieuNhi::SachThieuNhi(const string& ma, const string& ten,
                           const string& maTG, const string& maTL,
                           const string& maNXB_, int nam,
                           double giaNhap_, double giaBan_, int soLuong,
                           int doTuoi, bool coTranh,
                           const string& viTriKe_, const string& moTa_)
    : Sach(ma, ten, maTG, maTL, maNXB_, nam, giaNhap_, giaBan_, soLuong,
           viTriKe_, moTa_),
      doTuoiToiThieu(doTuoi), coTranhMinhHoa(coTranh) {}

void SachThieuNhi::setDoTuoi(int t) {
    if (t < 0 || t > 18) throw LoiDuLieu("Do tuoi toi thieu phai tu 0 den 18.");
    doTuoiToiThieu = t;
}

string SachThieuNhi::loaiSach() const { return "Thieu nhi"; }
string SachThieuNhi::maLoai()   const { return "TN"; }

Sach* SachThieuNhi::nhanBan() const { return new SachThieuNhi(*this); }

double SachThieuNhi::tiLeGiamGia() const { return 0.15; }

string SachThieuNhi::moTaThem() const {
    ostringstream os;
    os << "Tu " << doTuoiToiThieu << " tuoi, "
       << (coTranhMinhHoa ? "co tranh minh hoa" : "khong co tranh");
    return os.str();
}

void SachThieuNhi::nhap() {
    Sach::nhap();
    setDoTuoi(Nhap::soNguyen("  Do tuoi toi thieu : ", 0, 18));
    coTranhMinhHoa = Nhap::xacNhan("  Co tranh minh hoa?");
}

string SachThieuNhi::toCSV() const {
    ostringstream os;
    os << maLoai() << '|' << Sach::toCSV() << '|' << doTuoiToiThieu
       << '|' << (coTranhMinhHoa ? 1 : 0);
    return os.str();
}

void SachThieuNhi::fromCSV(const vector<string>& p) {
    if (p.size() < 14) throw LoiFile("Dong du lieu SachThieuNhi thieu truong.");
    Sach::fromCSV(p);
    doTuoiToiThieu = atoi(p[12].c_str());
    coTranhMinhHoa = (atoi(p[13].c_str()) != 0);
}
