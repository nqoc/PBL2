// =====================================================================
//  KhachHang.h - Lop dan xuat tu Nguoi: khach hang cua cua hang
//  Diem tich luy: 1 diem cho moi 10.000 VND mua hang
// =====================================================================
#ifndef KHACHHANG_H
#define KHACHHANG_H

#include "Nguoi.h"

class KhachHang : public Nguoi {
private:
    int diemTichLuy;

public:
    KhachHang();
    KhachHang(const std::string& ma, const std::string& hoTen,
              const std::string& sdt, const std::string& diaChi,
              const std::string& email, int diem = 0);

    int  getDiem() const { return diemTichLuy; }
    void setDiem(int d);

    // Nghiep vu the thanh vien
    void   congDiemTheoHoaDon(double soTienMua);
    double tiLeGiamThanhVien() const;    // 0 / 0.02 / 0.05 / 0.08
    std::string capThanhVien()   const;  // Thuong / Bac / Vang / Kim cuong

    // Ghi de cac ham ao cua lop co so
    std::string vaiTro() const;
    void        nhap();
    void        xuatChiTiet() const;
    void        xuatDong()    const;
    std::string toCSV()       const;
    void        fromCSV(const std::vector<std::string>& p);
};

#endif // KHACHHANG_H
