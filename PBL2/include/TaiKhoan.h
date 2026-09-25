#ifndef TAIKHOAN_H
#define TAIKHOAN_H

#include "Nguoi.h"
#include <string>
#include <vector>

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

    bool fromChuoi(const string& dong);
    string toChuoi() const;
};

vector<TaiKhoan> docTaiKhoan(const string& tenFile);

#endif