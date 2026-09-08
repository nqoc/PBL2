#include<iostream>
#include"TienIch.h"
#include"Sach.h"
#include<string>
#include<iomanip>


using namespace std ;

// gia tri cho toan bo
const int Sach::NAM_MIN = 1900;
const int Sach::NAM_MAX = 2100;


Sach::Sach() : maSach(""), tenSach(""), maTacGia(""), maTheLoai(""), maNXB(""),
      namXuatBan(2024), giaNhap(0), giaBan(0), soLuongTon(0),
      viTriKe(""), moTa("") {}

      
Sach::Sach(const string& maSach_, const string& tenSach_,
           const string& maTacGia_, const string& maTheLoai_,
           const string& maNXB_, int namXuatBan_,
           double giaNhap_, double giaBan_, int soLuongTon_,
           const string& viTriKe_, const string& moTa_)
    : maSach(""), tenSach(""), maTacGia(""), maTheLoai(""), maNXB(""),
      namXuatBan(2024), giaNhap(0), giaBan(0), soLuongTon(0),
      viTriKe(""), moTa("")

      // gan truoc roi moi check ham trong , neu true thi gan , false thi out 
{
    setMaSach(maSach_);          setTenSach(tenSach_);
    setMaTacGia(maTacGia_);  setMaTheLoai(maTheLoai_);
    setMaNXB(maNXB_);        setNamXuatBan(namXuatBan_);
    setGiaNhap(giaNhap_);    setGiaBan(giaBan_);
    setSoLuongTon(soLuongTon_); setViTriKe(viTriKe_);
    setMoTa(moTa_);
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
         << "  Gia tri ton  : " << ChuyenSo(giaTriTonKho()) << " VND\n";
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




