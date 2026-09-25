#ifndef PHIEUNHAP_H
#define PHIEUNHAP_H

#include "ChungTu.h"

class PhieuNhap : public ChungTu {
    string maNhaCungCap;
public:
    PhieuNhap();
    PhieuNhap(const string& ma, const string& ngay, const string& nguoiLap,
              const string& maNhaCungCap);
    string getMaNhaCungCap() const { return maNhaCungCap; }
    bool setMaNhaCungCap(const string& s);
    double thanhToan() const override { return tongTienHang(); }
    bool fromChuoi(const string& dong);
    string toChuoi() const;
};

Vector<PhieuNhap> docPhieuNhap(const string& tenFile);

#endif
