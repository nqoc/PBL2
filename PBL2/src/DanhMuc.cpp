#include<iostream>
#include<iomanip>   // them tinh nang setw()
#include"DanhMuc.h"
#include"TienIch.h"

using namespace std ; 


TheLoai::TheLoai() {
    ma = "" ; 
    ten = "" ; 
    moTa="" ; 
}

//TheLoai::TheLoai() : ma(""), ten(""), moTa("") {}

TheLoai::TheLoai(const string& ma1 , const string& ten1 ,const string& moTa1 ) {
    setMa(ma1) ; 
    setTen(ten1) ; 
    setMoTa(moTa1) ; 
}

bool TheLoai::setMa(const string& s) {
    string t = ChuanHoa(s);
    if (t.empty()) return false;             
    if (CoKyTuNganCach(t)) return false;    // '|' '#' se lam vo record khi ghi file
    this->ma = t;
    return true;
}

bool TheLoai::setTen(const string& s) {
    string t = ChuanHoa(s);
    if (t.empty()) return false;
    if (CoKyTuNganCach(t)) return false;
    this->ten = t;
    return true;
}

bool TheLoai::setMoTa(const string& s) {
    string t = ChuanHoa(s);                       
    if (CoKyTuNganCach(t)) return false;
    this->moTa = t;                     // moTa duoc phep RONG , nhung khong duoc co '|' '#'
    return true;
}

void TheLoai::nhap() {
    // Nhap::HetInput() : loi thoat khi cin dong , neu khong thi lap VO HAN
    while (!setMa(Nhap::Chuoi("  Ma the loai   : "))) {
        if (Nhap::HetInput()) return;
        cout << "  !! Ma khong duoc rong / khong chua '|' '#'.\n";
    }
    while (!setTen(Nhap::Chuoi("  Ten the loai  : "))) {
        if (Nhap::HetInput()) return;
        cout << "  !! Ten khong duoc rong / khong chua '|' '#'.\n";
    }
    while (!setMoTa(Nhap::Chuoi("  Mo ta         : ", true))) {  // true = cho phep rong
        if (Nhap::HetInput()) return;
        cout << "  !! Mo ta khong duoc chua '|' hoac '#'.\n";
    }
}

void TheLoai::inBang() {
    cout << " " << left  << setw(10) << "MA"
         << left  << setw(28) << "TEN THE LOAI"
         << left  << setw(40) << "MO TA" << "\n";
    cout << " " << string(78, '-') << "\n";
}

void TheLoai::xuatDong() const {
    // CanTrai thay cho setw : setw dem BYTE nen tieng Viet lam lech cot
    cout << " " << CanTrai(CatBot(ma,   9), 10)   // rong 10 ,toi da 9 dong
         << CanTrai(CatBot(ten,  27), 28)
         << CanTrai(CatBot(moTa, 39), 40) << "\n";
}






