// =====================================================================
//  Sach.cpp - Cai dat lop co so Sach + ham xuong taoSachTheoMaLoai()
// =====================================================================
#include "Sach.h"
#include "SachGiaoKhoa.h"
#include "SachVanHoc.h"
#include "SachThieuNhi.h"
#include "TienIch.h"
#include "NgoaiLe.h"

#include <iomanip>
#include <sstream>
#include <cstdlib>

using namespace std;

Sach::Sach()
    : namXuatBan(2024), giaNhap(0), giaBan(0), soLuongTon(0) {}

Sach::Sach(const string& ma, const string& ten, const string& maTG,
           const string& maTL, const string& maNXB_, int nam,
           double giaNhap_, double giaBan_, int soLuong,
           const string& viTriKe_, const string& moTa_)
    : maSach(ma), tenSach(ten), maTacGia(maTG), maTheLoai(maTL),
      maNXB(maNXB_), namXuatBan(nam), giaNhap(giaNhap_), giaBan(giaBan_),
      soLuongTon(soLuong), viTriKe(viTriKe_), moTa(moTa_) {}

Sach::~Sach() {}

// ---------------------- Setter co kiem tra ----------------------
void Sach::setTen(const string& s) {
    if (chuanHoa(s).empty()) throw LoiDuLieu("Ten sach khong duoc de trong.");
    tenSach = s;
}

void Sach::setNamXB(int n) {
    if (n < 1900 || n > 2100)
        throw LoiDuLieu("Nam xuat ban phai trong khoang 1900..2100.");
    namXuatBan = n;
}

void Sach::setGiaNhap(double g) {
    if (g < 0) throw LoiDuLieu("Gia nhap khong duoc am.");
    giaNhap = g;
}

void Sach::setGiaBan(double g) {
    if (g < 0) throw LoiDuLieu("Gia ban khong duoc am.");
    giaBan = g;
}

void Sach::setSoLuong(int sl) {
    if (sl < 0) throw LoiDuLieu("So luong ton khong duoc am.");
    soLuongTon = sl;
}

// ---------------------- Nghiep vu ----------------------
void Sach::nhapThemKho(int sl) {
    if (sl <= 0) throw LoiDuLieu("So luong nhap phai lon hon 0.");
    soLuongTon += sl;
}

void Sach::banBotKho(int sl) {
    if (sl <= 0) throw LoiDuLieu("So luong ban phai lon hon 0.");
    if (sl > soLuongTon) {
        ostringstream os;
        os << "Sach " << maSach << " chi con " << soLuongTon
           << " cuon, khong the ban " << sl << " cuon.";
        throw LoiTonKho(os.str());
    }
    soLuongTon -= sl;
}

double Sach::giaTriTonKho()    const { return giaNhap * soLuongTon; }
double Sach::loiNhuanMotCuon() const { return giaSauGiam() - giaNhap; }

// ---------------------- Ham ao mac dinh ----------------------
double Sach::tiLeGiamGia() const { return 0.0; }

double Sach::giaSauGiam() const { return giaBan * (1.0 - tiLeGiamGia()); }

string Sach::moTaThem() const { return ""; }

void Sach::nhap() {
    setTen(Nhap::chuoi("  Ten sach          : "));
    maTacGia  = Nhap::chuoi("  Ma tac gia        : ");
    maTheLoai = Nhap::chuoi("  Ma the loai       : ");
    maNXB     = Nhap::chuoi("  Ma nha xuat ban   : ");
    setNamXB(Nhap::soNguyen("  Nam xuat ban      : ", 1900, 2100));
    setGiaNhap(Nhap::soThuc("  Gia nhap (VND)    : ", 0, 1e9));
    while (true) {
        double g = Nhap::soThuc("  Gia ban (VND)     : ", 0, 1e9);
        if (g < giaNhap) {
            if (!Nhap::xacNhan("  Gia ban thap hon gia nhap. Van tiep tuc?"))
                continue;
        }
        setGiaBan(g);
        break;
    }
    setSoLuong(Nhap::soNguyen("  So luong ton      : ", 0, 1000000));
    viTriKe = Nhap::chuoi("  Vi tri ke (A1-01) : ", true);
    moTa    = Nhap::chuoi("  Mo ta (co the bo) : ", true);
}

void Sach::xuatChiTiet() const {
    cout << "  Ma sach       : " << maSach << '\n'
         << "  Ten sach      : " << tenSach << '\n'
         << "  Loai sach     : " << loaiSach() << " (" << maLoai() << ")\n"
         << "  Ma tac gia    : " << maTacGia << '\n'
         << "  Ma the loai   : " << maTheLoai << '\n'
         << "  Ma NXB        : " << maNXB << '\n'
         << "  Nam xuat ban  : " << namXuatBan << '\n'
         << "  Gia nhap      : " << dinhDangTien(giaNhap) << " VND\n"
         << "  Gia ban       : " << dinhDangTien(giaBan) << " VND\n"
         << "  Giam gia loai : " << (tiLeGiamGia() * 100) << " %\n"
         << "  Gia sau giam  : " << dinhDangTien(giaSauGiam()) << " VND\n"
         << "  So luong ton  : " << soLuongTon << '\n'
         << "  Vi tri ke     : " << viTriKe << '\n';
    string them = moTaThem();
    if (!them.empty()) cout << "  Thong tin rieng: " << them << '\n';
    if (!moTa.empty()) cout << "  Mo ta         : " << moTa << '\n';
}

void Sach::inTieuDeBang() {
    Man::duong('-', 108);
    cout << left  << setw(9)  << "MA"
         << left  << setw(30) << "TEN SACH"
         << left  << setw(12) << "LOAI"
         << left  << setw(9)  << "TACGIA"
         << left  << setw(9)  << "THELOAI"
         << right << setw(6)  << "NAM"
         << right << setw(13) << "GIA BAN"
         << right << setw(13) << "SAU GIAM"
         << right << setw(7)  << "TON" << '\n';
    Man::duong('-', 108);
}

void Sach::xuatDong() const {
    cout << left  << setw(9)  << catBot(maSach, 8)
         << left  << setw(30) << catBot(tenSach, 29)
         << left  << setw(12) << catBot(loaiSach(), 11)
         << left  << setw(9)  << catBot(maTacGia, 8)
         << left  << setw(9)  << catBot(maTheLoai, 8)
         << right << setw(6)  << namXuatBan
         << right << setw(13) << dinhDangTien(giaBan)
         << right << setw(13) << dinhDangTien(giaSauGiam())
         << right << setw(7)  << soLuongTon;
}

// ---------------------- File ----------------------
// Thu tu truong (lop co so):
//   maSach|tenSach|maTacGia|maTheLoai|maNXB|namXB|giaNhap|giaBan|ton|viTriKe|moTa
string Sach::toCSV() const {
    ostringstream os;
    os << fixed << setprecision(0);
    os << maSach   << '|' << tenSach << '|' << maTacGia << '|' << maTheLoai
       << '|' << maNXB << '|' << namXuatBan << '|' << giaNhap << '|' << giaBan
       << '|' << soLuongTon << '|' << viTriKe << '|' << moTa;
    return os.str();
}

// p[0] la MA LOAI, du lieu lop co so nam tu p[1] den p[11]
void Sach::fromCSV(const vector<string>& p) {
    if (p.size() < 12) throw LoiFile("Dong du lieu Sach thieu truong.");
    maSach     = p[1];
    tenSach    = p[2];
    maTacGia   = p[3];
    maTheLoai  = p[4];
    maNXB      = p[5];
    namXuatBan = atoi(p[6].c_str());
    giaNhap    = atof(p[7].c_str());
    giaBan     = atof(p[8].c_str());
    soLuongTon = atoi(p[9].c_str());
    viTriKe    = p[10];
    moTa       = p[11];
}

// ---------------------- Toan tu ----------------------
bool Sach::operator==(const Sach& k) const {
    return veThuong(maSach) == veThuong(k.maSach);
}

bool Sach::operator<(const Sach& k) const {
    return giaSauGiam() < k.giaSauGiam();
}

Sach& Sach::operator+=(int sl) { nhapThemKho(sl); return *this; }

ostream& operator<<(ostream& os, const Sach& s) {
    os << s.maSach << " - " << s.tenSach << " (" << s.loaiSach() << ")";
    return os;
}

// ---------------------- Factory ----------------------
Sach* taoSachTheoMaLoai(const string& maLoai) {
    if (maLoai == "GK") return new SachGiaoKhoa();
    if (maLoai == "VH") return new SachVanHoc();
    if (maLoai == "TN") return new SachThieuNhi();
    throw LoiDuLieu("Ma loai sach khong hop le (chi GK / VH / TN): " + maLoai);
}
