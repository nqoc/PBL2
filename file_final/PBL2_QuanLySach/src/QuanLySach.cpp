// =====================================================================
//  QuanLySach.cpp
// =====================================================================
#include "QuanLySach.h"
#include "ThuatToan.h"
#include "TienIch.h"
#include "NgoaiLe.h"

#include <fstream>
#include <sstream>
#include <iomanip>
#include <cstdlib>

using namespace std;

// =====================  Ham so sanh  =====================
bool sxTheoMaTang(Sach* a, Sach* b)   { return veThuong(a->getMa())  < veThuong(b->getMa()); }
bool sxTheoMaGiam(Sach* a, Sach* b)   { return veThuong(a->getMa())  > veThuong(b->getMa()); }
bool sxTheoTenTang(Sach* a, Sach* b)  { return veThuong(a->getTen()) < veThuong(b->getTen()); }
bool sxTheoTenGiam(Sach* a, Sach* b)  { return veThuong(a->getTen()) > veThuong(b->getTen()); }
bool sxTheoGiaTang(Sach* a, Sach* b)  { return a->giaSauGiam() < b->giaSauGiam(); }
bool sxTheoGiaGiam(Sach* a, Sach* b)  { return a->giaSauGiam() > b->giaSauGiam(); }
bool sxTheoTonTang(Sach* a, Sach* b)  { return a->getSoLuong() < b->getSoLuong(); }
bool sxTheoTonGiam(Sach* a, Sach* b)  { return a->getSoLuong() > b->getSoLuong(); }
bool sxTheoNamTang(Sach* a, Sach* b)  { return a->getNamXB() < b->getNamXB(); }
bool sxTheoNamGiam(Sach* a, Sach* b)  { return a->getNamXB() > b->getNamXB(); }

// =====================  Khoi tao / huy  =====================
QuanLySach::QuanLySach() : chiMuc(211), soDongLoi(0) {}

QuanLySach::~QuanLySach() { xoaHet(); }

void QuanLySach::xoaHet() {
    for (size_t i = 0; i < ds.kichThuoc(); ++i) delete ds[i];
    ds.xoaHet();
    chiMuc.xoaHet();
}

void QuanLySach::xayLaiChiMuc() {
    chiMuc.xoaHet();
    for (size_t i = 0; i < ds.kichThuoc(); ++i)
        chiMuc.dat(veThuong(ds[i]->getMa()), static_cast<int>(i));
}

// =====================  Them / xoa  =====================
void QuanLySach::them(Sach* s) {
    if (s == 0) throw LoiDuLieu("Con tro sach rong.");
    if (chiMuc.co(veThuong(s->getMa())))
        throw LoiTrungMa("Ma sach " + s->getMa() + " da ton tai.");

    // Chen vao dung vi tri de danh sach luon sap xep theo ma
    size_t vt = 0;
    while (vt < ds.kichThuoc()
           && veThuong(ds[vt]->getMa()) < veThuong(s->getMa())) ++vt;
    ds.chen(vt, s);
    xayLaiChiMuc();
}

QuanLySach& QuanLySach::operator+=(Sach* s) { them(s); return *this; }

bool QuanLySach::xoa(const string& ma) {
    int vt;
    if (!chiMuc.lay(veThuong(ma), vt)) return false;
    delete ds[static_cast<size_t>(vt)];
    ds.xoaTaiViTri(static_cast<size_t>(vt));
    xayLaiChiMuc();
    return true;
}

// =====================  Tim kiem  =====================
Sach* QuanLySach::timTheoMa(const string& ma) const {
    int vt;
    if (chiMuc.lay(veThuong(ma), vt)) return ds[static_cast<size_t>(vt)];
    return 0;
}

// Ham lay khoa dung cho tim kiem nhi phan
static string layKhoaMa(Sach* s) { return veThuong(s->getMa()); }

long QuanLySach::timNhiPhanTheoMa(const string& ma) const {
    return timNhiPhan<Sach*, string>(ds, veThuong(ma), layKhoaMa);
}

Vector<Sach*> QuanLySach::timTheoTen(const string& tuKhoa) const {
    Vector<Sach*> kq;
    for (size_t i = 0; i < ds.kichThuoc(); ++i)
        if (chuaChuoiCon(ds[i]->getTen(), tuKhoa)) kq.them(ds[i]);
    return kq;
}

Vector<Sach*> QuanLySach::timTheoTacGia(const string& maTG) const {
    Vector<Sach*> kq;
    for (size_t i = 0; i < ds.kichThuoc(); ++i)
        if (chuaChuoiCon(ds[i]->getMaTacGia(), maTG)) kq.them(ds[i]);
    return kq;
}

Vector<Sach*> QuanLySach::timTheoTheLoai(const string& maTL) const {
    Vector<Sach*> kq;
    for (size_t i = 0; i < ds.kichThuoc(); ++i)
        if (chuaChuoiCon(ds[i]->getMaTheLoai(), maTL)) kq.them(ds[i]);
    return kq;
}

Vector<Sach*> QuanLySach::timTheoNXB(const string& maNXB) const {
    Vector<Sach*> kq;
    for (size_t i = 0; i < ds.kichThuoc(); ++i)
        if (chuaChuoiCon(ds[i]->getMaNXB(), maNXB)) kq.them(ds[i]);
    return kq;
}

// =====================  Loc  =====================
Vector<Sach*> QuanLySach::locTheoKhoangGia(double tu, double den) const {
    Vector<Sach*> kq;
    for (size_t i = 0; i < ds.kichThuoc(); ++i) {
        double g = ds[i]->giaSauGiam();
        if (g >= tu && g <= den) kq.them(ds[i]);
    }
    return kq;
}

Vector<Sach*> QuanLySach::locTheoTinhTrang(bool conHang) const {
    Vector<Sach*> kq;
    for (size_t i = 0; i < ds.kichThuoc(); ++i) {
        bool con = ds[i]->getSoLuong() > 0;
        if (con == conHang) kq.them(ds[i]);
    }
    return kq;
}

Vector<Sach*> QuanLySach::locTheoLoai(const string& maLoai) const {
    Vector<Sach*> kq;
    for (size_t i = 0; i < ds.kichThuoc(); ++i)
        if (ds[i]->maLoai() == maLoai) kq.them(ds[i]);
    return kq;
}

// =====================  Sap xep  =====================
Vector<Sach*> QuanLySach::sapXepTheo(TieuChi tc, bool tangDan) const {
    Vector<Sach*> ban(ds);          // sao chep danh sach con tro
    switch (tc) {
        case THEO_MA:
            quickSort(ban, tangDan ? sxTheoMaTang : sxTheoMaGiam);   break;
        case THEO_TEN:
            // mergeSort on dinh -> giu nguyen thu tu cac sach cung ten
            mergeSort(ban, tangDan ? sxTheoTenTang : sxTheoTenGiam); break;
        case THEO_GIA:
            quickSort(ban, tangDan ? sxTheoGiaTang : sxTheoGiaGiam); break;
        case THEO_TON:
            quickSort(ban, tangDan ? sxTheoTonTang : sxTheoTonGiam); break;
        case THEO_NAM:
            mergeSort(ban, tangDan ? sxTheoNamTang : sxTheoNamGiam); break;
    }
    return ban;
}

// =====================  Thong ke  =====================
double QuanLySach::tongGiaTriTonKho() const {
    double t = 0;
    for (size_t i = 0; i < ds.kichThuoc(); ++i) t += ds[i]->giaTriTonKho();
    return t;
}

int QuanLySach::tongSoCuonTon() const {
    int t = 0;
    for (size_t i = 0; i < ds.kichThuoc(); ++i) t += ds[i]->getSoLuong();
    return t;
}

size_t QuanLySach::demTheoLoai(const string& maLoai) const {
    size_t d = 0;
    for (size_t i = 0; i < ds.kichThuoc(); ++i)
        if (ds[i]->maLoai() == maLoai) ++d;
    return d;
}

Vector<Sach*> QuanLySach::sachSapHet(int nguong) const {
    Vector<Sach*> kq;
    for (size_t i = 0; i < ds.kichThuoc(); ++i)
        if (ds[i]->sapHetHang(nguong)) kq.them(ds[i]);
    return kq;
}

Sach* QuanLySach::sachDatNhat() const {
    if (ds.rong()) return 0;
    Sach* kq = ds[0];
    for (size_t i = 1; i < ds.kichThuoc(); ++i)
        if (*kq < *ds[i]) kq = ds[i];      // dung toan tu < da nap chong
    return kq;
}

size_t QuanLySach::demThamChieuTacGia(const string& maTG) const {
    size_t d = 0;
    for (size_t i = 0; i < ds.kichThuoc(); ++i)
        if (veThuong(ds[i]->getMaTacGia()) == veThuong(maTG)) ++d;
    return d;
}

size_t QuanLySach::demThamChieuTheLoai(const string& maTL) const {
    size_t d = 0;
    for (size_t i = 0; i < ds.kichThuoc(); ++i)
        if (veThuong(ds[i]->getMaTheLoai()) == veThuong(maTL)) ++d;
    return d;
}

size_t QuanLySach::demThamChieuNXB(const string& maNXB) const {
    size_t d = 0;
    for (size_t i = 0; i < ds.kichThuoc(); ++i)
        if (veThuong(ds[i]->getMaNXB()) == veThuong(maNXB)) ++d;
    return d;
}

// =====================  Sinh ma  =====================
string QuanLySach::sinhMa(const string& maLoai) const {
    long lonNhat = 0;
    for (size_t i = 0; i < ds.kichThuoc(); ++i) {
        string m = ds[i]->getMa();
        if (m.size() > maLoai.size()
            && veThuong(m.substr(0, maLoai.size())) == veThuong(maLoai)) {
            long v = atol(m.substr(maLoai.size()).c_str());
            if (v > lonNhat) lonNhat = v;
        }
    }
    ostringstream os;
    os << maLoai << setw(3) << setfill('0') << (lonNhat + 1);
    return os.str();
}

// =====================  File  =====================
void QuanLySach::luuFile(const string& tenTep) const {
    ofstream f(tenTep.c_str());
    if (!f) throw LoiFile("Khong ghi duoc tep " + tenTep);
    for (size_t i = 0; i < ds.kichThuoc(); ++i) f << ds[i]->toCSV() << "\n";
    f.close();
}

bool QuanLySach::docFile(const string& tenTep) {
    soDongLoi = 0;
    ifstream f(tenTep.c_str());
    if (!f) return false;
    xoaHet();
    string dong;
    while (getline(f, dong)) {
        if (chuanHoa(dong).empty()) continue;
        Sach* s = 0;
        try {
            vector<string> p = tachChuoi(dong, '|');
            if (p.empty()) throw LoiFile("Dong rong.");
            s = taoSachTheoMaLoai(p[0]);      // ham xuong -> da hinh
            s->fromCSV(p);
            them(s);
        } catch (const std::exception&) {
            delete s;                          // tranh ro ri bo nho
            ++soDongLoi;
        }
    }
    f.close();
    return true;
}
