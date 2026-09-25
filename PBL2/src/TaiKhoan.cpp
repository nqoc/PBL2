#include "TaiKhoan.h"

#include <fstream>
#include <iostream>
#include <sstream>

#include "ChungTu.h"
#include "TienIch.h"

#define vector Vector

#define vector Vector

using namespace std;

const string TaiKhoan::QUYEN_ADMIN = "admin";
const string TaiKhoan::QUYEN_NHANVIEN = "nhanvien";

TaiKhoan::TaiKhoan()
    : Nguoi(),tenDangNhap(""), matKhauHash(""), quyen("") {}

TaiKhoan::TaiKhoan(const string& ma,
                   const string& hoTen,
                   const string& soDienThoai,
                   const string& diaChi,
                   const string& email,
                   const string& tenDangNhap_,
                   const string& matKhauHash_,
                   const string& quyen_)
    : Nguoi(ma, hoTen, soDienThoai, diaChi, email),
      tenDangNhap(""),
      matKhauHash(""),
      quyen("")
{
    setTenDangNhap(tenDangNhap_);
    setMatKhauHash(matKhauHash_);
    setQuyen(quyen_);
}

TaiKhoan::TaiKhoan(const string& tenDangNhap_, const string& matKhauHash_, const string& quyen_)
    : Nguoi(), tenDangNhap(tenDangNhap_), matKhauHash(matKhauHash_), quyen(quyen_)
{
    setTenDangNhap(tenDangNhap_);
    setMatKhauHash(matKhauHash_);
    setQuyen(quyen_);
}


bool TaiKhoan::setTenDangNhap(const string& s) {
    string t = ChuanHoa(s);
    if (t.empty()) return false;
    if (CoKyTuNganCach(t)) return false;
    tenDangNhap = t;
    return true;
}

bool TaiKhoan::setMatKhauHash(const string& s) {
    string t = ChuanHoa(s);
    if (t.empty()) return false;
    matKhauHash = t;
    return true;
}

bool TaiKhoan::setQuyen(const string& s) {
    string t = ChuanHoa(ToLower(s));
    if (t == QUYEN_ADMIN || t == QUYEN_NHANVIEN || t == "employee") {
        quyen = t;
        return true;
    }
    return false;
}

bool TaiKhoan::laAdmin() const {
    return quyen == QUYEN_ADMIN;
}

bool TaiKhoan::laNhanVien() const {
    return quyen == QUYEN_NHANVIEN || quyen == "employee";
}

bool TaiKhoan::laEmployee() const {
    return laNhanVien();
}

bool TaiKhoan::fromChuoi(const string& dong) {
    vector<string> p = TachChuoi(dong, '|');
    if (p.size() != 3) return false;

    string user = ChuanHoa(p[0]);
    string hash = ChuanHoa(p[1]);
    string role = ChuanHoa(ToLower(p[2]));

    if (user.empty() || hash.empty()) return false;
    if (role != "admin" && role != "employee" && role != "nhanvien") return false;

    tenDangNhap = user;
    matKhauHash = hash;
    quyen = role;
    return true;
}

string TaiKhoan::toChuoi() const {
    ostringstream os;
    os << tenDangNhap << '|' << matKhauHash << '|' << quyen;
    return os.str();
}

vector<TaiKhoan> docTaiKhoan(const string& tenFile) {
    vector<TaiKhoan> danhSach;
    ifstream file(tenFile);
    if (!file.is_open()) {
        cerr << "Khong mo duoc file: " << tenFile << "\n";
        return danhSach;
    }

    string dong;
    int soDong = 0;
    while (getline(file, dong)) {
        ++soDong;
        if (ChuanHoa(dong).empty()) continue;

        TaiKhoan taiKhoan;
        if (!taiKhoan.fromChuoi(dong)) {
            cerr << "Dong taikhoan.txt khong hop le: " << soDong << "\n";
            continue;
        }
        danhSach.push_back(taiKhoan);
    }

    return danhSach;
}
