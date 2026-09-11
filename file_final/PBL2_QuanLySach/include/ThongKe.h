// =====================================================================
//  ThongKe.h - Cac cau truc ket qua thong ke
// =====================================================================
#ifndef THONGKE_H
#define THONGKE_H

#include <string>

// Mot dong trong bang "sach ban chay" / "the loai ua chuong"
struct MucBanChay {
    std::string ma;
    std::string ten;
    int         soLuongBan;
    double      doanhThu;

    MucBanChay() : soLuongBan(0), doanhThu(0) {}
    MucBanChay(const std::string& ma_, const std::string& ten_)
        : ma(ma_), ten(ten_), soLuongBan(0), doanhThu(0) {}
};

// Mot dong trong bang doanh thu theo ngay / theo thang
struct MucDoanhThu {
    std::string moc;         // "05/09/2026" hoac "09/2026"
    int         soHoaDon;
    double      doanhThu;

    MucDoanhThu() : soHoaDon(0), doanhThu(0) {}
    MucDoanhThu(const std::string& m) : moc(m), soHoaDon(0), doanhThu(0) {}
};

// Ham so sanh de sap xep giam dan theo so luong ban
bool bcTheoSoLuongGiam(const MucBanChay& a, const MucBanChay& b);
bool bcTheoDoanhThuGiam(const MucBanChay& a, const MucBanChay& b);
bool dtTheoMocTang(const MucDoanhThu& a, const MucDoanhThu& b);

#endif // THONGKE_H
