#include "HoaDon.h"
#include "TienIch.h"
#include <fstream>
#include <iomanip>
#include <sstream>

#define vector Vector

#define vector Vector

using namespace std;

HoaDon::HoaDon() : ChungTu(), maKhachHang(""), tiLeChietKhau(0), thanhToanDaLuu(0) {}

HoaDon::HoaDon(const string& ma_, const string& ngay_, const string& nguoiLap_,
               const string& maKhachHang_, double tiLeChietKhau_, double thanhToan_)
    : ChungTu(ma_, ngay_, nguoiLap_), maKhachHang(""), tiLeChietKhau(0), thanhToanDaLuu(0) {
    setMaKhachHang(maKhachHang_);
    setTiLeChietKhau(tiLeChietKhau_);
    setThanhToan(thanhToan_);
}

bool HoaDon::setMaKhachHang(const string& s) {
    string t = ChuanHoa(s);
    if (t.empty() || CoKyTuNganCach(t)) return false;
    maKhachHang = t;
    return true;
}

bool HoaDon::setTiLeChietKhau(double value) {
    if (value < 0 || value > 1) return false;
    tiLeChietKhau = value;
    return true;
}

bool HoaDon::setThanhToan(double value) {
    if (value < 0) return false;
    thanhToanDaLuu = value;
    return true;
}

double HoaDon::thanhToan() const {
    return thanhToanDaLuu > 0 ? thanhToanDaLuu : tongTienHang() * (1 - tiLeChietKhau);
}

bool HoaDon::fromChuoi(const string& dong) {
    vector<string> p = TachChuoi(dong, '|');
    if (p.size() != 6) return false;
    double chietKhau = 0;
    double thanhToanLuu = 0;
    if (!ChuoiSangDouble(p[3], chietKhau) || !ChuoiSangDouble(p[4], thanhToanLuu)) return false;
    if (!setMa(p[0]) || !setNgay(p[1]) || !setMaKhachHang(p[2]) ||
        !setTiLeChietKhau(chietKhau / 100.0) || !setThanhToan(thanhToanLuu) ||
        !ChungTu::laNgayHopLe(p[5])) return false;
    return true;
}

string HoaDon::toChuoi() const {
    ostringstream os;
    os << ma << '|' << ngay << '|' << maKhachHang << '|'
       << fixed << setprecision(1) << tiLeChietKhau * 100 << '|'
       << setprecision(0) << thanhToan() << '|' << ngay;
    return os.str();
}

vector<HoaDon> docHoaDon(const string& tenFile) {
    vector<HoaDon> danhSach;
    ifstream file(tenFile);
    if (!file.is_open()) return danhSach;
    string dong;
    while (getline(file, dong)) {
        if (ChuanHoa(dong).empty()) continue;
        HoaDon hoaDon;
        if (hoaDon.fromChuoi(dong)) danhSach.push_back(hoaDon);
    }
    return danhSach;
}
