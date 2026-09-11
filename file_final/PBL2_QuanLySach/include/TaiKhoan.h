// =====================================================================
//  TaiKhoan.h - Lop dan xuat tu Nguoi: tai khoan dang nhap he thong
//  Mat khau duoc luu duoi dang chuoi bam (hash), khong luu ban ro
// =====================================================================
#ifndef TAIKHOAN_H
#define TAIKHOAN_H

#include "Nguoi.h"

class TaiKhoan : public Nguoi {
public:
    // Hai muc quyen cua he thong
    static const std::string QUYEN_ADMIN;      // "ADMIN"
    static const std::string QUYEN_NHANVIEN;   // "NHANVIEN"

private:
    std::string matKhauBam;
    std::string quyen;

public:
    TaiKhoan();
    TaiKhoan(const std::string& tenDangNhap, const std::string& hoTen,
             const std::string& matKhauRo, const std::string& quyen);

    std::string getTenDangNhap() const { return ma; }
    std::string getQuyen()       const { return quyen; }
    bool        laAdmin()        const { return quyen == QUYEN_ADMIN; }

    void setQuyen(const std::string& q);
    void datMatKhau(const std::string& matKhauRo);      // bam roi luu
    bool kiemTraMatKhau(const std::string& matKhauRo) const;

    std::string vaiTro() const;
    void        nhap();
    void        xuatChiTiet() const;
    void        xuatDong()    const;
    std::string toCSV()       const;
    void        fromCSV(const std::vector<std::string>& p);
};

#endif // TAIKHOAN_H
