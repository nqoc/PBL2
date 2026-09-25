#include<iostream>
#include"TienIch.h"
#include"Sach.h"
#include<string>
#include<iomanip>
#include<ctime>
#include<cstdio>
#include<fstream>
#include<sstream>

#define vector Vector

#define vector Vector


using namespace std ;

namespace {
bool laNgayHopLe(const string& ngay) {
    int ngayTrongThang, thang, nam;
    char dau1, dau2;

    if (ngay.size() != 10 || sscanf(ngay.c_str(), "%d%c%d%c%d", &ngayTrongThang, &dau1,
               &thang, &dau2, &nam) != 5 || dau1 != '/' || dau2 != '/') {
        return false;
    }

    tm ngayLich = {};
    ngayLich.tm_mday = ngayTrongThang;
    ngayLich.tm_mon = thang - 1;
    ngayLich.tm_year = nam - 1900;
    ngayLich.tm_isdst = -1;
    mktime(&ngayLich);

    return ngayTrongThang >= 1 && thang >= 1 && thang <= 12 && nam >= 1 &&
           ngayLich.tm_mday == ngayTrongThang &&
           ngayLich.tm_mon == thang - 1 && ngayLich.tm_year == nam - 1900;
}
}

// gia tri cho toan bo
const int Sach::NAM_MIN = 1900;
const int Sach::NAM_MAX = 2100;


Sach::Sach() : maSach(""), tenSach(""), maTacGia(""), maTheLoai(""), maNXB(""),
      namXuatBan(2024), giaNhap(0), giaBan(0), soLuongTon(0),
      viTriKe(""), moTa(""), ngayTao("") {}

      
Sach::Sach(const string& maSach_, const string& tenSach_,
           const string& maTacGia_, const string& maTheLoai_,
           const string& maNXB_, int namXuatBan_,
           double giaNhap_, double giaBan_, int soLuongTon_,
           const string& viTriKe_, const string& moTa_, const string& ngayTao_)
    : maSach(""), tenSach(""), maTacGia(""), maTheLoai(""), maNXB(""),
      namXuatBan(2024), giaNhap(0), giaBan(0), soLuongTon(0),
      viTriKe(""), moTa(""), ngayTao("") 

      // gan truoc roi moi check ham trong , neu true thi gan , false thi out 
{
    setMaSach(maSach_);          setTenSach(tenSach_);
    setMaTacGia(maTacGia_);  setMaTheLoai(maTheLoai_);
    setMaNXB(maNXB_);        setNamXuatBan(namXuatBan_);
    setGiaNhap(giaNhap_);    setGiaBan(giaBan_);
    setSoLuongTon(soLuongTon_); setViTriKe(viTriKe_);
    setMoTa(moTa_); setNgayTao(ngayTao_);
}


Sach::~Sach() {}  

// dinh nghia ham set

bool Sach::setMaSach( const string& s) {
    string tmp = ChuanHoa(s) ; 
    if( !tmp.empty() ) {
        this->maSach = tmp ; 
        return true ; 
    }
    return false ; 
}

bool Sach::setTenSach( const string& s) {
    string tmp = ChuanHoa(s) ; 
    if( !tmp.empty() ) {
        this->tenSach = tmp ; 
        return true ; 
    }
    return false ; 
}

bool Sach::setMaTacGia(const string& s) {
    string t = ChuanHoa(s);
    if (t.empty()) return false;    
    maTacGia = t;                   
    return true;
}

bool Sach::setMaTheLoai(const string& s) {
    string t = ChuanHoa(s);
    if (t.empty()) return false;
    maTheLoai = t;
    return true;
}

bool Sach::setMaNXB(const string& s) {
    string t = ChuanHoa(s);
    if (t.empty()) return false;
    maNXB = t;
    return true;
}

bool Sach::setNamXuatBan(int nam) {
    if (nam < NAM_MIN || nam > NAM_MAX) return false;
    namXuatBan = nam;
    return true;
}

bool Sach::setGiaNhap(double v) {
    if (v < 0) return false;
    giaNhap = v;
    return true;
}

bool Sach::setGiaBan(double v) {
    if (v < 0) return false;
    giaBan = v;
    return true;
}

bool Sach::setSoLuongTon(int a) {
    if (a < 0) return false;
    soLuongTon = a;
    return true;
}

bool Sach::setViTriKe(const string& s) {
    viTriKe = ChuanHoa(s);          //  duoc phep rong
    return true;
}

bool Sach::setMoTa(const string& s) {
    moTa = ChuanHoa(s);            // duoc phep rong
    return true;
}
bool Sach::setNgayTao(const string& s) {
    string t = ChuanHoa(s);
    if (!laNgayHopLe(t)) return false;
    ngayTao = t;
    return true;
}
// ham tinh nang

bool  Sach::nhapThemKho(int sl) {
    if ( sl < 0 ) return false ; 
    soLuongTon += sl ; 
    return true ; 
}      
  
bool  Sach::banBotKho(int sl) {
    if ( sl < 0 ) return false ; 
    if ( sl > soLuongTon ) return false ; 
    soLuongTon -= sl ; 
    return true ; 
}     

double  Sach::giaTriTonKho() const {
    return giaNhap * (double)soLuongTon ; // ep kieu : int -> double
}     

double Sach::loiNhuanMotCuon() const {
    return giaBan-giaNhap ;
}

void Sach::nhap() {
    
    // neu sai : 
    while (!setMaSach(Nhap::Chuoi("  Ma sach       : ")))
        cout << "  !! Ma khong duoc rong.\n";
    while (!setTenSach(Nhap::Chuoi("  Ten sach      : ")))
        cout << "  !! Ten khong duoc rong.\n";
    while (!setMaTacGia(Nhap::Chuoi("  Ma tac gia    : ")))
        cout << "  !! Ma tac gia khong duoc rong.\n";
    while (!setMaTheLoai(Nhap::Chuoi("  Ma the loai   : ")))
        cout << "  !! Ma the loai khong duoc rong.\n";
    while (!setMaNXB(Nhap::Chuoi("  Ma NXB        : ")))
        cout << "  !! Ma NXB khong duoc rong.\n";
    while (!setNgayTao(Nhap::Chuoi("  Ngay tao      : ")))
        cout << "  !! Ngay tao khong hop le.\n";
    
    // neu dung , goi ham set , set-> truyen gia tri vao thuoc tinh

    setNamXuatBan(Nhap::SoNguyen("  Nam xuat ban  : ", NAM_MIN, NAM_MAX));
    setGiaNhap    (Nhap::SoThuc  ("  Gia nhap      : ", 0, 1e9));
    setGiaBan     (Nhap::SoThuc  ("  Gia ban       : ", 0, 1e9));
    setSoLuongTon    (Nhap::SoNguyen("  So luong ton  : ", 0, 1000000));
    setViTriKe(Nhap::Chuoi("  Vi tri ke     : ", true));
    setMoTa   (Nhap::Chuoi("  Mo ta         : ", true));

}

void Sach::inTieuDeBang() {

    // in tieu de dau dong

    cout << " " << left  << setw(9)  << "MA"    // trong 9 o thi MA xep o mep trai
         << left  << setw(30) << "TEN SACH"
         << left  << setw(8)  << "TG"
         << left  << setw(8)  << "TL"
         << right << setw(6)  << "NAM"
         << right << setw(13) << "GIA BAN"
         << right << setw(7)  << "TON" << "\n";  // trong 7 o thi TON xep o mep phai
    cout << " " << string(80, '-') << "\n";
}

void Sach::xuatDong() const {

    // xuat tren 1 dong
    cout << " " << left  << setw(9)  << CatBot(maSach, 8)
         << left  << setw(30) << CatBot(tenSach, 29)
         << left  << setw(8)  << CatBot(maTacGia, 7)
         << left  << setw(8)  << CatBot(maTheLoai, 7)
         << right << setw(6)  << namXuatBan
         << right << setw(13) << ChuyenSo(giaBan)
         << right << setw(7)  << soLuongTon << "\n";
}       

void Sach::xuatChiTiet() const {

        // xuat ra danh sach 
    cout << "  Ma sach      : " << maSach     << "\n"
         << "  Ten sach     : " << tenSach    << "\n"
         << "  Ma tac gia   : " << maTacGia   << "\n"
         << "  Ma the loai  : " << maTheLoai  << "\n"
         << "  Ma NXB       : " << maNXB      << "\n"
         << "  Nam xuat ban : " << namXuatBan << "\n"
         << "  Gia nhap     : " << ChuyenSo(giaNhap) << " VND\n"
         << "  Gia ban      : " << ChuyenSo(giaBan)  << " VND\n"
         << "  So luong ton : " << soLuongTon << "\n"
         << "  Vi tri ke    : " << viTriKe    << "\n"
         << "  Mo ta        : " << moTa       << "\n"
         << "  Gia tri ton  : " << ChuyenSo(giaTriTonKho()) << " VND\n"
         << "  Ngay tao    : " << ngayTao    << "\n";
}

// nap chong toan tu 


bool Sach::operator == ( const Sach& s ) const {
    if( ToLower(maSach) != ToLower(s.maSach) ) return false ; 
    return true ;
}
// p1 == p2  :  p1.operator==(p2) 
// nen con tro this se tro vao p1 va p2 la tham so

bool Sach::operator < ( const Sach& s ) const {
    return giaSauGiam() < s.giaSauGiam();
} 

Sach& Sach::operator += ( int a ) {
    nhapThemKho(a) ; 
    return *this ; 
}

 ostream& operator << ( ostream& os , const Sach& s )  {
    os << s.maSach << " - " << s.tenSach ; 
    return os ; 
}
// ham main : cout << s1 
// tbd : operator<<( cout , s1 ) 
// in ra : s1.maSach + s1.tenSach 

double Sach::giaSauGiam() const {
    return giaBan * (1.0 - tiLeGiamGia());
}

namespace {
bool ganSachCoBan(Sach& sach, const vector<string>& p) {
    if (p.size() != 12) return false;
    int nam = 0, ton = 0;
    double giaNhap = 0, giaBan = 0;
    if (!ChuoiSangInt(p[5], nam) || !ChuoiSangDouble(p[6], giaNhap) ||
        !ChuoiSangDouble(p[7], giaBan) || !ChuoiSangInt(p[8], ton)) return false;
    return sach.setMaSach(p[0]) && sach.setTenSach(p[1]) &&
           sach.setMaTacGia(p[2]) && sach.setMaTheLoai(p[3]) &&
           sach.setMaNXB(p[4]) && sach.setNamXuatBan(nam) &&
           sach.setGiaNhap(giaNhap) && sach.setGiaBan(giaBan) &&
           sach.setSoLuongTon(ton) && sach.setViTriKe(p[9]) &&
           sach.setMoTa(p[10]) && sach.setNgayTao(p[11]);
}

string csvCoBan(const Sach& sach) {
    ostringstream os;
    os << sach.getMaSach() << '|' << sach.getTenSach() << '|'
       << sach.getMaTacGia() << '|' << sach.getMaTheLoai() << '|'
       << sach.getMaNXB() << '|' << sach.getNamXuatBan() << '|'
       << sach.getGiaNhap() << '|' << sach.getGiaBan() << '|'
       << sach.getSoLuongTon() << '|' << sach.getViTriKe() << '|'
       << sach.getMoTa() << '|' << sach.getNgayTao();
    return os.str();
}
}

string Sach::toCSV() const { return csvCoBan(*this); }

bool Sach::fromCSV(const string& dong) {
    return ganSachCoBan(*this, TachChuoi(dong, '|'));
}

SachGiaoKhoa::SachGiaoKhoa() : Sach(), monHoc(""), capHoc(""), phanTramGiam(0) {}

SachGiaoKhoa::SachGiaoKhoa(const string& a, const string& b, const string& c,
                           const string& d, const string& e, int f, double g,
                           double h, int i, const string& j, const string& k,
                           const string& l, const string& m, const string& n, double o)
    : Sach(a,b,c,d,e,f,g,h,i,j,k,l), monHoc(m), capHoc(n), phanTramGiam(0) {
    setPhanTramGiam(o);
}

bool SachGiaoKhoa::setMonHoc(const string& s) { monHoc = ChuanHoa(s); return !monHoc.empty() && !CoKyTuNganCach(monHoc); }
bool SachGiaoKhoa::setCapHoc(const string& s) { capHoc = ChuanHoa(s); return !CoKyTuNganCach(capHoc); }
bool SachGiaoKhoa::setPhanTramGiam(double v) { if (v < 0 || v > 100) return false; phanTramGiam = v; return true; }

string SachGiaoKhoa::toCSV() const {
    return csvCoBan(*this) + "|" + monHoc + "|" + capHoc + "|" + ChuyenSo(phanTramGiam);
}

bool SachGiaoKhoa::fromCSV(const string& dong) {
    vector<string> p = TachChuoi(dong, '|');
    if (p.size() != 15 || !ganSachCoBan(*this, vector<string>(p.begin(), p.begin() + 12))) return false;
    double g = 0;
    if (!ChuoiSangDouble(p[14], g) || !setMonHoc(p[12]) || !setCapHoc(p[13]) || !setPhanTramGiam(g)) return false;
    return true;
}

SachVanHoc::SachVanHoc() : Sach(), phongCach(""), phanTramGiam(0) {}

SachVanHoc::SachVanHoc(const string& a, const string& b, const string& c,
                       const string& d, const string& e, int f, double g,
                       double h, int i, const string& j, const string& k,
                       const string& l, const string& m, double n)
    : Sach(a,b,c,d,e,f,g,h,i,j,k,l), phongCach(m), phanTramGiam(0) { setPhanTramGiam(n); }

bool SachVanHoc::setPhanTramGiam(double v) {
    if (v < 0 || v > 100) return false;
    phanTramGiam = v;
    return true;
}

string SachVanHoc::toCSV() const { return csvCoBan(*this) + "|" + phongCach + "|" + ChuyenSo(phanTramGiam); }
bool SachVanHoc::fromCSV(const string& dong) {
    vector<string> p = TachChuoi(dong, '|');
    if (p.size() != 14 || !ganSachCoBan(*this, vector<string>(p.begin(), p.begin() + 12))) return false;
    double g = 0;
    if (!ChuoiSangDouble(p[13], g) || CoKyTuNganCach(p[12]) || !setPhanTramGiam(g)) return false;
    phongCach = ChuanHoa(p[12]);
    return true;
}

SachThieuNhi::SachThieuNhi() : Sach(), doTuoi(0), phanTramGiam(0) {}

SachThieuNhi::SachThieuNhi(const string& a, const string& b, const string& c,
                           const string& d, const string& e, int f, double g,
                           double h, int i, const string& j, const string& k,
                           const string& l, int m, double n)
    : Sach(a,b,c,d,e,f,g,h,i,j,k,l), doTuoi(0), phanTramGiam(0) { doTuoi = m; setPhanTramGiam(n); }

bool SachThieuNhi::setPhanTramGiam(double v) {
    if (v < 0 || v > 100) return false;
    phanTramGiam = v;
    return true;
}

string SachThieuNhi::toCSV() const { return csvCoBan(*this) + "|" + to_string(doTuoi) + "|" + ChuyenSo(phanTramGiam); }
bool SachThieuNhi::fromCSV(const string& dong) {
    vector<string> p = TachChuoi(dong, '|');
    if (p.size() != 14 || !ganSachCoBan(*this, vector<string>(p.begin(), p.begin() + 12))) return false;
    int tuoi = 0; double g = 0;
    if (!ChuoiSangInt(p[12], tuoi) || tuoi < 0 || !ChuoiSangDouble(p[13], g) || !setPhanTramGiam(g)) return false;
    doTuoi = tuoi;
    return true;
}

vector<shared_ptr<Sach> > docSach(const string& tenFile) {
    vector<shared_ptr<Sach> > ds;
    ifstream file(tenFile);
    string dong;
    while (getline(file, dong)) {
        if (ChuanHoa(dong).empty()) continue;
        vector<string> p = TachChuoi(dong, '|');
        shared_ptr<Sach> sach;
        if (!p.empty() && p[0].find("GK") == 0) sach = make_shared<SachGiaoKhoa>();
        else if (!p.empty() && p[0].find("VH") == 0) sach = make_shared<SachVanHoc>();
        else if (!p.empty() && p[0].find("TN") == 0) sach = make_shared<SachThieuNhi>();
        if (!sach && p.size() == 12) {
            int nam = 0, ton = 0;
            double giaNhap = 0, giaBan = 0;
            if (!ChuoiSangInt(p[5], nam) || !ChuoiSangDouble(p[6], giaNhap) ||
                !ChuoiSangDouble(p[7], giaBan) || !ChuoiSangInt(p[8], ton)) continue;
            if (p[3] == "1" || p[3] == "23" || p[3] == "24")
                sach = make_shared<SachThieuNhi>(p[0], p[1], p[2], p[3], p[4], nam,
                                                 giaNhap, giaBan, ton, p[9], p[10], p[11]);
            else if (p[3] == "10" || p[3] == "11" || p[3] == "12" ||
                     p[3] == "13" || p[3] == "14")
                sach = make_shared<SachGiaoKhoa>(p[0], p[1], p[2], p[3], p[4], nam,
                                                 giaNhap, giaBan, ton, p[9], p[10], p[11]);
            else
                sach = make_shared<SachVanHoc>(p[0], p[1], p[2], p[3], p[4], nam,
                                               giaNhap, giaBan, ton, p[9], p[10], p[11]);
            ds.push_back(sach);
        } else if (sach && sach->fromCSV(dong)) {
            ds.push_back(sach);
        }
    }
    return ds;
}




