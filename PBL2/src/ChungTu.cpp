#include <iostream>
#include <iomanip>
#include <sstream>
#include "ChungTu.h"
#include "TienIch.h"

using namespace std ;

// ==================================================================
//                          DongChiTiet


DongChiTiet::DongChiTiet()
    : maSach(""), tenSach(""), soLuong(0), donGia(0) {}

DongChiTiet::DongChiTiet(const string& maSach_, const string& tenSach_,
                         int soLuong_, double donGia_)
    : maSach(""), tenSach(""), soLuong(0), donGia(0)
{
    setMaSach(maSach_);
    setTenSach(tenSach_);
    setSoLuong(soLuong_);
    setDonGia(donGia_);
}

bool DongChiTiet::setMaSach(const string& s) {
    string t = ChuanHoa(s);
    if (t.empty()) return false;
    if (CoKyTuNganCach(t)) return false;    // '|' hay '#' se lam vo record khi ghi file
    maSach = t;
    return true;
}

bool DongChiTiet::setTenSach(const string& s) {
    string t = ChuanHoa(s);
    if (t.empty()) return false;
    if (CoKyTuNganCach(t)) return false;
    tenSach = t;
    return true;
}

bool DongChiTiet::setSoLuong(int sl) {
    if (sl <= 0) return false;              // mot dong hang phai co it nhat 1 cuon
    soLuong = sl;
    return true;
}

bool DongChiTiet::setDonGia(double dg) {
    if (dg < 0) return false;
    donGia = dg;
    return true;
}

void DongChiTiet::congThemSoLuong(int sl) {
    if (sl > 0) soLuong += sl;
}

double DongChiTiet::thanhTien() const {
    return soLuong * donGia;
}


// "VH002#Nha Gia Kim#2#75050"
// dong goi ghi xuong data 

// QUAN TRONG : phai dung '#' , KHONG dung '|'.
// Vi ChungTu::chuoiChiTiet() noi cac dong lai bang '|' , va file txt cung
// ngan cot bang '|'. Neu o day cung dung '|' thi khi doc len TachChuoi(...,'|')
// se be vun tung dong ra 4 manh -> fromChuoi() that bai -> MAT SACH chi tiet.

string DongChiTiet::toChuoi() const {
    ostringstream os;
    os << fixed << setprecision(0);     // khong lay phan thap phan
                                        // fixed de chan TH in ra dang 1.23457e+06

    os << maSach << '#' << tenSach << '#' << soLuong << '#' << donGia;
    return os.str();
}

// lay tu data ra de ghi vao thuoc tinh 

bool DongChiTiet::fromChuoi(const string& dong) {
    vector<string> p = TachChuoi(dong, '#');    // '#' , khop voi toChuoi()
    if (p.size() != 4) return false;

    int    sl = 0 ;
    double dg = 0 ;
    if (!ChuoiSangInt(p[2], sl))    return false;
    if (!ChuoiSangDouble(p[3], dg)) return false;

    // Ghi vao BAN NHAP truoc. Neu bat ky field nao hong thi *this van con
    // nguyen ven , khong bi sua nua chung roi tra ve false.

    DongChiTiet tam ;
    if (!tam.setMaSach(p[0]))  return false;
    if (!tam.setTenSach(p[1])) return false;
    if (!tam.setSoLuong(sl))   return false;    // setter da chan sl <= 0
    if (!tam.setDonGia(dg))    return false;    // va dg < 0

    *this = tam ;
    return true;
}

void DongChiTiet::inTieuDeBang() {
    cout << "  " << left  << setw(9)  << "MA SACH"
         << left  << setw(28) << "TEN SACH"
         << right << setw(5)  << "SL"
         << right << setw(13) << "DON GIA"
         << right << setw(15) << "THANH TIEN" << "\n";
    cout << "  " << string(70, '-') << "\n";
}

void DongChiTiet::xuatDong() const {
    cout << "  " << CanTrai(CatBot(maSach,  8),  9)     // CanTrai thay cho setw :
         << CanTrai(CatBot(tenSach, 27), 28)            // setw dem byte -> lech cot
         << right << setw(5)  << soLuong
         << right << setw(13) << ChuyenSo(donGia)
         << right << setw(15) << ChuyenSo(thanhTien()) << "\n";
}

// ==================================================================
//                            ChungTu
// ==================================================================

ChungTu::ChungTu() : ma(""), ngay(""), nguoiLap("") {}

ChungTu::ChungTu(const string& ma_, const string& ngay_, const string& nguoiLap_)
    : ma(""), ngay(""), nguoiLap("")
{
    setMa(ma_);
    setNgay(ngay_);
    setNguoiLap(nguoiLap_);
}

ChungTu::~ChungTu() {}

bool ChungTu::setMa(const string& s) {
    string t = ChuanHoa(s);
    if (t.empty()) return false;
    if (CoKyTuNganCach(t)) return false;
    ma = t;
    return true;
}

bool ChungTu::setNgay(const string& s) {
    string t = ChuanHoa(s);
    if (!laNgayHopLe(t)) return false;
    ngay = t;
    return true;
}

bool ChungTu::setNguoiLap(const string& s) {
    string t = ChuanHoa(s);
    if (t.empty()) return false;
    if (CoKyTuNganCach(t)) return false;
    nguoiLap = t;
    return true;
}

// ------------------ nghiep vu tren danh sach dong ------------------

void ChungTu::themDong(const DongChiTiet& d) {
    for (size_t i = 0; i < chiTiet.size(); ++i) {
        if (ToLower(chiTiet[i].getMaSach()) == ToLower(d.getMaSach())) {
            chiTiet[i].congThemSoLuong(d.getSoLuong());   // GOP, khong tao dong moi
            return;
        }
    }
    chiTiet.push_back(d);
}

bool ChungTu::xoaDong(size_t viTri) {
    if (viTri >= chiTiet.size()) return false;
    chiTiet.erase(chiTiet.begin() + (long)viTri);       // xoa trong vector
    return true;
}

void ChungTu::xoaHetDong() {
    chiTiet.clear();
}

double ChungTu::tongTienHang() const {
    double t = 0;
    for (size_t i = 0; i < chiTiet.size(); ++i) t += chiTiet[i].thanhTien();
    return t;
}

int ChungTu::tongSoLuong() const {
    int t = 0;
    for (size_t i = 0; i < chiTiet.size(); ++i) t += chiTiet[i].getSoLuong();
    return t;
}

// Chuong 6: thanh ham THUAN AO.
// HoaDon se tru chiet khau, PhieuNhap giu nguyen tong tien hang.

double ChungTu::thanhToan() const {
    return this->tongTienHang();
}

// ------------------------- kiem tra ngay -------------------------

static int soNgayTrongThang(int thang, int nam) {
    static const int bang[12] = { 31,28,31,30,31,30,31,31,30,31,30,31 };
    if (thang < 1 || thang > 12) return 0;
    if (thang == 2) {
        bool nhuan = (nam % 4 == 0 && nam % 100 != 0) || (nam % 400 == 0);
        return nhuan ? 29 : 28;
    }
    return bang[thang - 1];
}

bool ChungTu::laNgayHopLe(const string& s) {
    vector<string> p = TachChuoi(s, '/');
    if (p.size() != 3) return false;
    if (p[0].size() != 2 || p[1].size() != 2 || p[2].size() != 4) return false;

    for (size_t i = 0; i < p.size(); ++i)
        for (size_t j = 0; j < p[i].size(); ++j)
            if (p[i][j] < '0' || p[i][j] > '9') return false;

    int ngay, thang, nam;
    if (!ChuoiSangInt(p[0], ngay))  return false;
    if (!ChuoiSangInt(p[1], thang)) return false;
    if (!ChuoiSangInt(p[2], nam))   return false;

    if (nam < 1900 || nam > 2100) return false;
    if (thang < 1 || thang > 12)  return false;
    if (ngay < 1 || ngay > soNgayTrongThang(thang, nam)) return false;  // cho nay dung dinh dang dd/mm/yyyy, nen sua lai ben hoadon.txt thanh dd/mm/yyyy
    return true;
}

// "05/09/2026" -> 20260905  ->  so sanh ngay chi con so sanh hai so nguyen
long ChungTu::soHoaNgay(const string& s) {
    vector<string> p = TachChuoi(s, '/');
    if (p.size() != 3) return 0;
    long ngay, thang, nam;
    if (!ChuoiSangLong(p[0], ngay))  return 0;
    if (!ChuoiSangLong(p[1], thang)) return 0;
    if (!ChuoiSangLong(p[2], nam))   return 0;
    return nam * 10000 + thang * 100 + ngay;
}

// ------------------------- tuan tu hoa -------------------------

// Ghi SO DONG truoc, roi tung dong ngan cach bang '|'
// viet vao txt : so dong sau do day tung dong vao 

//      d hieu gi *

string ChungTu::chuoiChiTiet() const {
    ostringstream os;
    os << chiTiet.size();
    for (size_t i = 0; i < chiTiet.size(); ++i)
        os << '|' << chiTiet[i].toChuoi();
    return os.str();
}

void ChungTu::docChiTiet(const vector<string>& p, size_t batDau) {
    chiTiet.clear();
    if (batDau >= p.size()) return;
    int n;
    if (!ChuoiSangInt(p[batDau], n) || n < 0) return;
    if (p.size() - batDau - 1 < static_cast<size_t>(n)) return;
    for (int i = 0; i < n; ++i) {
        size_t vt = batDau + 1 + (size_t)i;
        if (vt >= p.size()) break;
        DongChiTiet d;
        if (!d.fromChuoi(p[vt])) {
            chiTiet.clear();
            return;
        }
        chiTiet.push_back(d);
    }
}


//      * d hieu gi 


void ChungTu::inChungTu() const {
    cout << "\n  +" << string(70, '-') << "+\n";
    cout << "  | So chung tu : " << left << setw(20) << ma
         << "Ngay: " << left << setw(14) << ngay
         << "Nguoi lap: " << nguoiLap << "\n";
    cout << "  +" << string(70, '-') << "+\n";
    DongChiTiet::inTieuDeBang();
    for (size_t i = 0; i < chiTiet.size(); ++i) chiTiet[i].xuatDong();
    cout << "  " << string(70, '-') << "\n";
    cout << "  " << right << setw(55) << "TONG TIEN HANG: "
         << setw(15) << ChuyenSo(tongTienHang()) << "\n";
    cout << "  " << right << setw(55) << "PHAI THANH TOAN: "
         << setw(15) << ChuyenSo(thanhToan()) << "\n";
}
