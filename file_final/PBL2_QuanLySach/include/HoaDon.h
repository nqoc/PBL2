// =====================================================================
//  HoaDon.h - Hoa don ban hang (ke thua ChungTu)
//  Thanh toan = tong tien hang - chiet khau
// =====================================================================
#ifndef HOADON_H
#define HOADON_H

#include "ChungTu.h"

class HoaDon : public ChungTu {
private:
    std::string maKhachHang;      // rong = khach le
    double      tiLeChietKhau;    // 0.00 .. 0.50

public:
    HoaDon();
    HoaDon(const std::string& ma, const std::string& ngay,
           const std::string& nguoiLap, const std::string& maKH,
           double tiLeChietKhau = 0.0);

    std::string getMaKhachHang() const { return maKhachHang; }
    double      getTiLeChietKhau() const { return tiLeChietKhau; }
    void        setMaKhachHang(const std::string& s) { maKhachHang = s; }
    void        setTiLeChietKhau(double t);

    double tienChietKhau() const;

    // Ghi de ham thuan ao cua ChungTu
    std::string loaiChungTu() const;
    double      thanhToan()   const;

    void        inChungTu()   const;
    void        xuatDong()    const;
    std::string toCSV()       const;
    void        fromCSV(const std::vector<std::string>& p);

    static void inTieuDeBang();
};

#endif // HOADON_H
