#include "PhieuNhap.h"
#include "TienIch.h"
#include <fstream>
#include <sstream>

#define vector Vector

#define vector Vector

using namespace std;

PhieuNhap::PhieuNhap() : ChungTu(), maNhaCungCap("") {}

PhieuNhap::PhieuNhap(const string& ma_, const string& ngay_, const string& nguoiLap_,
                     const string& maNhaCungCap_)
    : ChungTu(ma_, ngay_, nguoiLap_), maNhaCungCap("") {
    setMaNhaCungCap(maNhaCungCap_);
}

bool PhieuNhap::setMaNhaCungCap(const string& s) {
    string t = ChuanHoa(s);
    if (t.empty() || CoKyTuNganCach(t)) return false;
    maNhaCungCap = t;
    return true;
}

bool PhieuNhap::fromChuoi(const string& dong) {
    vector<string> p = TachChuoi(dong, '|');
    if (p.size() != 5 || !setMa(p[0]) || !setNgay(p[1]) ||
        !setNguoiLap(p[2]) || !setMaNhaCungCap(p[3])) return false;

    vector<string> tokens = TachChuoi(p[4], '#');
    int soDong = 0;
    if (tokens.empty() || !ChuoiSangInt(tokens[0], soDong) || soDong < 0 ||
        tokens.size() != 1 + static_cast<size_t>(soDong) * 4) return false;

    vector<DongChiTiet> tam;
    for (int i = 0; i < soDong; ++i) {
        size_t viTri = 1 + static_cast<size_t>(i) * 4;
        DongChiTiet dongChiTiet;
        string chiTiet = tokens[viTri] + "#" + tokens[viTri + 1] + "#" +
                         tokens[viTri + 2] + "#" + tokens[viTri + 3];
        if (!dongChiTiet.fromChuoi(chiTiet)) return false;
        tam.push_back(dongChiTiet);
    }
    chiTiet = tam;
    return true;
}

string PhieuNhap::toChuoi() const {
    ostringstream os;
    os << ma << '|' << ngay << '|' << nguoiLap << '|' << maNhaCungCap << '|'
       << chiTiet.size();
    for (const DongChiTiet& dong : chiTiet) {
        os << '#' << dong.getMaSach() << '#' << dong.getTenSach()
           << '#' << dong.getSoLuong() << '#' << dong.getDonGia();
    }
    return os.str();
}

vector<PhieuNhap> docPhieuNhap(const string& tenFile) {
    vector<PhieuNhap> danhSach;
    ifstream file(tenFile);
    if (!file.is_open()) return danhSach;
    string dong;
    while (getline(file, dong)) {
        if (ChuanHoa(dong).empty()) continue;
        PhieuNhap phieuNhap;
        if (phieuNhap.fromChuoi(dong)) danhSach.push_back(phieuNhap);
    }
    return danhSach;
}
