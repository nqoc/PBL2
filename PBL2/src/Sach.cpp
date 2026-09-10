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
    if( CoKyTuNganCach(tmp) ) return false ;    // '|' '#' se lam vo record khi ghi file
    if( !tmp.empty() ) {
        this->maSach = tmp ; 
        return true ; 
    }
    return false ; 
}

bool Sach::setTenSach( const string& s) {
    string tmp = ChuanHoa(s) ; 
    if( CoKyTuNganCach(tmp) ) return false ; 
    if( !tmp.empty() ) {
        this->tenSach = tmp ; 
        return true ; 
    }
    return false ; 
}

bool Sach::setMaTacGia(const string& s) {
    string t = ChuanHoa(s);
    if (t.empty()) return false;    
    if (CoKyTuNganCach(t)) return false;
    maTacGia = t;                   
    return true;
}

bool Sach::setMaTheLoai(const string& s) {
    string t = ChuanHoa(s);
    if (t.empty()) return false;
    if (CoKyTuNganCach(t)) return false;
    maTheLoai = t;
    return true;
}

bool Sach::setMaNXB(const string& s) {
    string t = ChuanHoa(s);
    if (t.empty()) return false;
    if (CoKyTuNganCach(t)) return false;
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
    string t = ChuanHoa(s);         //  duoc phep rong
    if (CoKyTuNganCach(t)) return false;
    viTriKe = t;
    return true;
}

bool Sach::setMoTa(const string& s) {
    string t = ChuanHoa(s);        // duoc phep rong
    if (CoKyTuNganCach(t)) return false;
    moTa = t;
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
    // Moi vong lap deu phai co loi thoat khi cin dong ( Ctrl+Z , hoac chay
    // main.exe < test.txt ) , neu khong Nhap::Chuoi() tra "" mai mai -> treo vo han.

    while (!setMaSach(Nhap::Chuoi("  Ma sach       : "))) {
        if (Nhap::HetInput()) return;
        cout << "  !! Ma khong duoc rong / khong chua '|' '#'.\n";
    }
    while (!setTenSach(Nhap::Chuoi("  Ten sach      : "))) {
        if (Nhap::HetInput()) return;
        cout << "  !! Ten khong duoc rong / khong chua '|' '#'.\n";
    }
    while (!setMaTacGia(Nhap::Chuoi("  Ma tac gia    : "))) {
        if (Nhap::HetInput()) return;
        cout << "  !! Ma tac gia khong duoc rong.\n";
    }
    while (!setMaTheLoai(Nhap::Chuoi("  Ma the loai   : "))) {
        if (Nhap::HetInput()) return;
        cout << "  !! Ma the loai khong duoc rong.\n";
    }
    while (!setMaNXB(Nhap::Chuoi("  Ma NXB        : "))) {
        if (Nhap::HetInput()) return;
        cout << "  !! Ma NXB khong duoc rong.\n";
    }
    
    // neu dung , goi ham set , set-> truyen gia tri vao thuoc tinh

    setNamXuatBan(Nhap::SoNguyen("  Nam xuat ban  : ", NAM_MIN, NAM_MAX));
    setGiaNhap    (Nhap::SoThuc  ("  Gia nhap      : ", 0, 1e9));
    setGiaBan     (Nhap::SoThuc  ("  Gia ban       : ", 0, 1e9));
    setSoLuongTon    (Nhap::SoNguyen("  So luong ton  : ", 0, 1000000));
    while (!setViTriKe(Nhap::Chuoi("  Vi tri ke     : ", true))) {
        if (Nhap::HetInput()) return;
        cout << "  !! Vi tri ke khong duoc chua '|' hoac '#'.\n";
    }
    while (!setMoTa(Nhap::Chuoi("  Mo ta         : ", true))) {
        if (Nhap::HetInput()) return;
        cout << "  !! Mo ta khong duoc chua '|' hoac '#'.\n";
    }

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
    cout << " " << string(81, '-') << "\n";    // 9+30+8+8+6+13+7 = 81
}

void Sach::xuatDong() const {

    // xuat tren 1 dong
    // Cot CHU dung CanTrai (dem ky tu) , cot SO van dung setw duoc vi chi co ASCII
    cout << " " << CanTrai(CatBot(maSach,    8),  9)
         << CanTrai(CatBot(tenSach,  29), 30)
         << CanTrai(CatBot(maTacGia,  7),  8)
         << CanTrai(CatBot(maTheLoai, 7),  8)
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




