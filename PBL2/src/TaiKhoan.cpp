#include "TaiKhoan.h"

#include <fstream>
#include <iostream>
#include <sstream>

#include "ChungTu.h"
#include "TienIch.h"   

using namespace std;

TaiKhoan::TaiKhoan()
    : id(0), tenDangNhap(""), matKhauHash(""), salt(""), vaiTro(""), ngayTao("") {}

TaiKhoan::TaiKhoan(int id_, const string& tenDangNhap_, const string& matKhauHash_,
                   const string& salt_, const string& vaiTro_, const string& ngayTao_)
    : id(0), tenDangNhap(""), matKhauHash(""), salt(""), vaiTro(""), ngayTao("")
{
    id = id_;
    tenDangNhap = ChuanHoa(tenDangNhap_);
    matKhauHash = ChuanHoa(matKhauHash_);
    salt = ChuanHoa(salt_);
    vaiTro = ChuanHoa(vaiTro_);
    ngayTao = ChuanHoa(ngayTao_);
}

bool TaiKhoan::fromChuoi(const string& dong) {
    vector<string> p = TachChuoi(dong, '|');
    if (p.size() != 6) return false;

    int idMoi;
    if (!ChuoiSangInt(p[0], idMoi) || idMoi <= 0) return false;
    if (ChuanHoa(p[1]).empty() || ChuanHoa(p[2]).empty()) return false;
    if (ChuanHoa(p[3]).empty()) return false;

    string vaiTroMoi = ChuanHoa(ToLower(p[4]));
    if (vaiTroMoi != "admin" && vaiTroMoi != "employee") return false;

    string ngayMoi = ChuanHoa(p[5]);
    if (!ChungTu::laNgayHopLe(ngayMoi)) return false;

    id = idMoi;
    tenDangNhap = ChuanHoa(p[1]);
    matKhauHash = ChuanHoa(p[2]);
    salt = ChuanHoa(p[3]);
    vaiTro = vaiTroMoi;
    ngayTao = ngayMoi;
    return true;
}

string TaiKhoan::toChuoi() const {
    ostringstream os;
    os << id << '|' << tenDangNhap << '|' << matKhauHash << '|'
       << salt << '|' << vaiTro << '|' << ngayTao;
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
            cerr << "Dong users.txt khong hop le: " << soDong << "\n";
            continue;
        }
        danhSach.push_back(taiKhoan);
    }
    return danhSach;
}
