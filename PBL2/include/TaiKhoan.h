#ifndef TAIKHOAN_H
#define TAIKHOAN_H

#include "Nguoi.h"
#include <string>
#include "Vector.h"

using namespace std;

class TaiKhoan : public Nguoi {
private:
    string tenDangNhap;
    string matKhauHash;
    string quyen;

public:
    static const string QUYEN_ADMIN;
    static const string QUYEN_NHANVIEN;

    TaiKhoan();
    TaiKhoan(
             const string& ma,
             const string& hoTen,
             const string& soDienThoai,
             const string& diaChi,
             const string& email,
             const string& tenDangNhap,
             const string& matKhauHash,
             const string& quyen);
    TaiKhoan(
             const string& tenDangNhap_,
             const string& matKhauHash_,
             const string& quyen_);

    string getTenDangNhap() const { return tenDangNhap; }
    string getMatKhauHash() const { return matKhauHash; }
    string getQuyen() const { return quyen; }

    bool setTenDangNhap(const string& s);
    bool setMatKhauHash(const string& s);
    bool setQuyen(const string& s);

    bool laAdmin() const;
    bool laNhanVien() const;
    bool laEmployee() const;
    string valiRet() const override { return "TaiKhoan"; }

    bool fromChuoi(const string& dong);
    string toChuoi() const;
};

Vector<TaiKhoan> docTaiKhoan(const string& tenFile);

#endif