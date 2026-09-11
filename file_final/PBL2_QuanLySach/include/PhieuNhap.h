// =====================================================================
//  PhieuNhap.h - Phieu nhap hang tu nha cung cap (ke thua ChungTu)
//  Thanh toan = tong tien hang (khong co chiet khau)
// =====================================================================
#ifndef PHIEUNHAP_H
#define PHIEUNHAP_H

#include "ChungTu.h"

class PhieuNhap : public ChungTu {
private:
    std::string maNhaCungCap;

public:
    PhieuNhap();
    PhieuNhap(const std::string& ma, const std::string& ngay,
              const std::string& nguoiLap, const std::string& maNCC);

    std::string getMaNhaCungCap() const { return maNhaCungCap; }
    void        setMaNhaCungCap(const std::string& s) { maNhaCungCap = s; }

    std::string loaiChungTu() const;
    double      thanhToan()   const;

    void        inChungTu()   const;
    void        xuatDong()    const;
    std::string toCSV()       const;
    void        fromCSV(const std::vector<std::string>& p);

    static void inTieuDeBang();
};

#endif // PHIEUNHAP_H
