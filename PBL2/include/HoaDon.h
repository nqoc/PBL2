#ifndef HOADON_H
#define HOADON_H

#include "ChungTu.h"

class HoaDon : public ChungTu {
    string maKhachHang;
    double tiLeChietKhau;
    double thanhToanDaLuu;
public:
    HoaDon();
    HoaDon(const string& ma, const string& ngay, const string& nguoiLap,
           const string& maKhachHang, double tiLeChietKhau, double thanhToan);
    string getMaKhachHang() const { return maKhachHang; }
    double getTiLeChietKhau() const { return tiLeChietKhau; }
    bool setMaKhachHang(const string& s);
    bool setTiLeChietKhau(double value);
    bool setThanhToan(double value);
    double thanhToan() const override;
    bool fromChuoi(const string& dong);
    string toChuoi() const;
};

Vector<HoaDon> docHoaDon(const string& tenFile);

#endif
