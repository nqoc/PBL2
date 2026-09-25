#include "ChiTietHoaDon.h"
#include "TienIch.h"
#include <fstream>
#include <sstream>

#define vector Vector

#define vector Vector

using namespace std;

ChiTietHoaDon::ChiTietHoaDon()
    : maHoaDon(""), maSach(""), soLuong(0), donGia(0), thanhTien(0) {}

ChiTietHoaDon::ChiTietHoaDon(const string& maHoaDon_, const string& maSach_, int soLuong_,
                             double donGia_, double thanhTien_)
    : ChiTietHoaDon() {
    setMaHoaDon(maHoaDon_);
    setMaSach(maSach_);
    setSoLuong(soLuong_);
    setDonGia(donGia_);
    setThanhTien(thanhTien_);
}

bool ChiTietHoaDon::setMaHoaDon(const string& s) {
    string t = ChuanHoa(s);
    if (t.empty() || CoKyTuNganCach(t)) return false;
    maHoaDon = t;
    return true;
}

bool ChiTietHoaDon::setMaSach(const string& s) {
    string t = ChuanHoa(s);
    if (t.empty() || CoKyTuNganCach(t)) return false;
    maSach = t;
    return true;
}

bool ChiTietHoaDon::setSoLuong(int value) {
    if (value <= 0) return false;
    soLuong = value;
    return true;
}

bool ChiTietHoaDon::setDonGia(double value) {
    if (value < 0) return false;
    donGia = value;
    return true;
}

bool ChiTietHoaDon::setThanhTien(double value) {
    if (value < 0) return false;
    thanhTien = value;
    return true;
}

bool ChiTietHoaDon::fromChuoi(const string& dong) {
    vector<string> p = TachChuoi(dong, '|');
    int soLuongValue = 0;
    double donGiaValue = 0;
    double thanhTienValue = 0;
    if (p.size() != 5 || !ChuoiSangInt(p[2], soLuongValue) ||
        !ChuoiSangDouble(p[3], donGiaValue) || !ChuoiSangDouble(p[4], thanhTienValue)) return false;
    return setMaHoaDon(p[0]) && setMaSach(p[1]) && setSoLuong(soLuongValue) &&
           setDonGia(donGiaValue) && setThanhTien(thanhTienValue);
}

string ChiTietHoaDon::toChuoi() const {
    ostringstream os;
    os << maHoaDon << '|' << maSach << '|' << soLuong << '|'
       << donGia << '|' << thanhTien;
    return os.str();
}

vector<ChiTietHoaDon> docChiTietHoaDon(const string& tenFile) {
    vector<ChiTietHoaDon> danhSach;
    ifstream file(tenFile);
    if (!file.is_open()) return danhSach;
    string dong;
    while (getline(file, dong)) {
        if (ChuanHoa(dong).empty()) continue;
        ChiTietHoaDon chiTiet;
        if (chiTiet.fromChuoi(dong)) danhSach.push_back(chiTiet);
    }
    return danhSach;
}
