// =====================================================================
//  ChungTu.cpp - Cai dat DongChiTiet va lop co so ChungTu
// =====================================================================
#include "ChungTu.h"
#include "TienIch.h"
#include "NgoaiLe.h"

#include <iostream>
#include <iomanip>
#include <sstream>
#include <cstdlib>

using namespace std;

// =====================  DongChiTiet  =====================
DongChiTiet::DongChiTiet() : soLuong(0), donGia(0) {}

DongChiTiet::DongChiTiet(const string& maSach_, const string& tenSach_,
                         int soLuong_, double donGia_)
    : maSach(maSach_), tenSach(tenSach_), soLuong(soLuong_), donGia(donGia_) {}

void DongChiTiet::setSoLuong(int sl) {
    if (sl <= 0) throw LoiDuLieu("So luong tren mot dong phai lon hon 0.");
    soLuong = sl;
}

void DongChiTiet::setDonGia(double g) {
    if (g < 0) throw LoiDuLieu("Don gia khong duoc am.");
    donGia = g;
}

string DongChiTiet::toChuoi() const {
    ostringstream os;
    os << fixed << setprecision(0);
    os << maSach << '#' << tenSach << '#' << soLuong << '#' << donGia;
    return os.str();
}

void DongChiTiet::fromChuoi(const string& s) {
    vector<string> p = tachChuoi(s, '#');
    if (p.size() < 4) throw LoiFile("Dong chi tiet chung tu sai dinh dang.");
    maSach  = p[0];
    tenSach = p[1];
    soLuong = atoi(p[2].c_str());
    donGia  = atof(p[3].c_str());
}

// =====================  ChungTu  =====================
ChungTu::ChungTu() : ngayLap(ngayHomNay()) {}

ChungTu::ChungTu(const string& ma_, const string& ngay_, const string& nguoiLap_)
    : ma(ma_), ngayLap(ngay_), nguoiLap(nguoiLap_) {}

ChungTu::~ChungTu() {}

void ChungTu::setNgay(const string& s) {
    if (!ngayHopLe(s)) throw LoiDuLieu("Ngay chung tu khong hop le: " + s);
    ngayLap = s;
}

void ChungTu::themDong(const DongChiTiet& d) {
    // Neu sach da co trong chung tu thi cong don so luong
    for (size_t i = 0; i < chiTiet.kichThuoc(); ++i) {
        if (chiTiet[i].getMaSach() == d.getMaSach()) {
            chiTiet[i].setSoLuong(chiTiet[i].getSoLuong() + d.getSoLuong());
            return;
        }
    }
    chiTiet.them(d);
}

bool ChungTu::xoaDong(size_t i) {
    if (i >= chiTiet.kichThuoc()) return false;
    chiTiet.xoaTaiViTri(i);
    return true;
}

double ChungTu::tongTienHang() const {
    double t = 0;
    for (size_t i = 0; i < chiTiet.kichThuoc(); ++i) t += chiTiet[i].thanhTien();
    return t;
}

int ChungTu::tongSoLuong() const {
    int t = 0;
    for (size_t i = 0; i < chiTiet.kichThuoc(); ++i) t += chiTiet[i].getSoLuong();
    return t;
}

string ChungTu::chuoiChiTiet() const {
    ostringstream os;
    os << chiTiet.kichThuoc();
    for (size_t i = 0; i < chiTiet.kichThuoc(); ++i)
        os << '|' << chiTiet[i].toChuoi();
    return os.str();
}

void ChungTu::docChiTiet(const vector<string>& p, size_t batDau) {
    chiTiet.xoaHet();
    if (batDau >= p.size()) return;
    int n = atoi(p[batDau].c_str());
    for (int i = 0; i < n; ++i) {
        size_t vt = batDau + 1 + static_cast<size_t>(i);
        if (vt >= p.size()) break;
        DongChiTiet d;
        d.fromChuoi(p[vt]);
        chiTiet.them(d);
    }
}

void ChungTu::inChungTu() const {
    Man::duong('=', 78);
    cout << "  " << loaiChungTu() << "   So: " << ma << "\n";
    cout << "  Ngay lap : " << ngayLap << "        Nguoi lap: " << nguoiLap << "\n";
    Man::duong('-', 78);
    cout << left  << setw(4)  << "TT"
         << left  << setw(10) << "MA SACH"
         << left  << setw(32) << "TEN SACH"
         << right << setw(5)  << "SL"
         << right << setw(13) << "DON GIA"
         << right << setw(14) << "THANH TIEN" << "\n";
    Man::duong('-', 78);
    for (size_t i = 0; i < chiTiet.kichThuoc(); ++i) {
        cout << left  << setw(4)  << (i + 1)
             << left  << setw(10) << catBot(chiTiet[i].getMaSach(), 9)
             << left  << setw(32) << catBot(chiTiet[i].getTenSach(), 31)
             << right << setw(5)  << chiTiet[i].getSoLuong()
             << right << setw(13) << dinhDangTien(chiTiet[i].getDonGia())
             << right << setw(14) << dinhDangTien(chiTiet[i].thanhTien()) << "\n";
    }
    Man::duong('-', 78);
    cout << right << setw(64) << "Tong tien hang: "
         << right << setw(14) << dinhDangTien(tongTienHang()) << "\n";
}

void ChungTu::xuatDong() const {
    cout << left  << setw(12) << ma
         << left  << setw(13) << ngayLap
         << left  << setw(16) << catBot(nguoiLap, 15)
         << right << setw(6)  << chiTiet.kichThuoc()
         << right << setw(8)  << tongSoLuong()
         << right << setw(16) << dinhDangTien(thanhToan());
}

string ChungTu::toCSV() const { return ma + "|" + ngayLap + "|" + nguoiLap; }

void ChungTu::fromCSV(const vector<string>& p) {
    if (p.size() < 3) throw LoiFile("Dong du lieu ChungTu thieu truong.");
    ma       = p[0];
    ngayLap  = p[1];
    nguoiLap = p[2];
}
