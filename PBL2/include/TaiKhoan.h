#ifndef TAIKHOAN_H
#define TAIKHOAN_H

#include <string>
#include <vector>

using namespace std;

class TaiKhoan {
private:
    int id;
    string tenDangNhap;
    string matKhauHash;
    string salt;
    string vaiTro;
    string ngayTao;

public:
    TaiKhoan();
    TaiKhoan(int id, const string& tenDangNhap, const string& matKhauHash,
             const string& salt, const string& vaiTro, const string& ngayTao);

    int getId() const { return id; }
    const string& getTenDangNhap() const { return tenDangNhap; }
    const string& getMatKhauHash() const { return matKhauHash; }
    const string& getSalt() const { return salt; }
    const string& getVaiTro() const { return vaiTro; }
    const string& getNgayTao() const { return ngayTao; }

    bool fromChuoi(const string& dong);
    string toChuoi() const;
};

vector<TaiKhoan> docTaiKhoan(const string& tenFile);

#endif
