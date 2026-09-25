#include<iostream>
#include<iomanip>   // them tinh nang setw()
#include"DanhMuc.h"
#include"TienIch.h"
#include"Nguoi.h"
#include<fstream>
#include<sstream>

#define vector Vector

#define vector Vector

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

namespace {
bool hopLeText(const string& s, bool rong = false) {
    string t = ChuanHoa(s);
    return (rong || !t.empty()) && !CoKyTuNganCach(t);
}

template<class T>
vector<T> docDanhMuc(const string& tenFile) {
    vector<T> ds;
    ifstream file(tenFile);
    string dong;
    while (getline(file, dong)) {
        if (ChuanHoa(dong).empty()) continue;
        T item;
        if (item.fromChuoi(dong)) ds.push_back(item);
    }
    return ds;
}
}

TacGia::TacGia() : ma(""), ten(""), moTa("") {}
TacGia::TacGia(const string& m, const string& t, const string& d) : TacGia() { setMa(m); setTen(t); setMoTa(d); }
bool TacGia::setMa(const string& s) { string t=ChuanHoa(s); if (!hopLeText(t)) return false; ma=t; return true; }
bool TacGia::setTen(const string& s) { string t=ChuanHoa(s); if (!hopLeText(t)) return false; ten=t; return true; }
bool TacGia::setMoTa(const string& s) { string t=ChuanHoa(s); if (!hopLeText(t,true)) return false; moTa=t; return true; }
string TacGia::toChuoi() const { return ma + "|" + ten + "|" + moTa; }
bool TacGia::fromChuoi(const string& s) { vector<string> p=TachChuoi(s,'|'); if (p.size()!=2 && p.size()!=3) return false; return setMa(p[0]) && setTen(p[1]) && setMoTa(p.size()==3?p[2]:""); }

NhaXuatBan::NhaXuatBan() : ma(""), ten(""), diaChi(""), soDienThoai(""), email("") {}
NhaXuatBan::NhaXuatBan(const string& m,const string& t,const string& d,const string& s,const string& e) : NhaXuatBan() { setMa(m); setTen(t); setDiaChi(d); setSoDienThoai(s); setEmail(e); }
bool NhaXuatBan::setMa(const string& s) { string t=ChuanHoa(s); if (!hopLeText(t)) return false; ma=t; return true; }
bool NhaXuatBan::setTen(const string& s) { string t=ChuanHoa(s); if (!hopLeText(t)) return false; ten=t; return true; }
bool NhaXuatBan::setDiaChi(const string& s) { string t=ChuanHoa(s); if (!hopLeText(t,true)) return false; diaChi=t; return true; }
bool NhaXuatBan::setSoDienThoai(const string& s) { string t=ChuanHoa(s); if (!Nguoi::checkSoDienThoai(t)) return false; soDienThoai=t; return true; }
bool NhaXuatBan::setEmail(const string& s) { string t=ChuanHoa(ToLower(s)); if (!Nguoi::checkEmail(t)) return false; email=t; return true; }
string NhaXuatBan::toChuoi() const { return ma+"|"+ten+"|"+diaChi+"|"+soDienThoai+"|"+email; }
bool NhaXuatBan::fromChuoi(const string& s) { vector<string> p=TachChuoi(s,'|'); return p.size()==5 && setMa(p[0]) && setTen(p[1]) && setDiaChi(p[2]) && setSoDienThoai(p[3]) && setEmail(p[4]); }

NhaCungCap::NhaCungCap() : ma(""), ten(""), soDienThoai(""), diaChi(""), email(""), maSoThue("") {}
NhaCungCap::NhaCungCap(const string& m,const string& t,const string& s,const string& d,const string& e,const string& mst) : NhaCungCap() { setMa(m); setTen(t); setSoDienThoai(s); setDiaChi(d); setEmail(e); setMaSoThue(mst); }
bool NhaCungCap::setMa(const string& s) { string t=ChuanHoa(s); if (!hopLeText(t)) return false; ma=t; return true; }
bool NhaCungCap::setTen(const string& s) { string t=ChuanHoa(s); if (!hopLeText(t)) return false; ten=t; return true; }
bool NhaCungCap::setSoDienThoai(const string& s) { string t=ChuanHoa(s); if (!Nguoi::checkSoDienThoai(t)) return false; soDienThoai=t; return true; }
bool NhaCungCap::setDiaChi(const string& s) { string t=ChuanHoa(s); if (!hopLeText(t,true)) return false; diaChi=t; return true; }
bool NhaCungCap::setEmail(const string& s) { string t=ChuanHoa(ToLower(s)); if (!Nguoi::checkEmail(t)) return false; email=t; return true; }
bool NhaCungCap::setMaSoThue(const string& s) { string t=ChuanHoa(s); if (!hopLeText(t)) return false; maSoThue=t; return true; }
string NhaCungCap::toChuoi() const { return ma+"|"+ten+"|"+soDienThoai+"|"+diaChi+"|"+email+"|"+maSoThue; }
bool NhaCungCap::fromChuoi(const string& s) { vector<string> p=TachChuoi(s,'|'); return p.size()==6 && setMa(p[0]) && setTen(p[1]) && setSoDienThoai(p[2]) && setDiaChi(p[3]) && setEmail(p[4]) && setMaSoThue(p[5]); }

KhachHang::KhachHang() : ma(""), hoTen(""), soDienThoai(""), diaChi(""), diem(0) {}
KhachHang::KhachHang(const string& m,const string& h,const string& s,const string& d,int p) : KhachHang() { setMa(m); setHoTen(h); setSoDienThoai(s); setDiaChi(d); setDiem(p); }
bool KhachHang::setMa(const string& s) { string t=ChuanHoa(s); if (!hopLeText(t)) return false; ma=t; return true; }
bool KhachHang::setHoTen(const string& s) { string t=ChuanHoa(s); if (!hopLeText(t)) return false; hoTen=t; return true; }
bool KhachHang::setSoDienThoai(const string& s) { string t=ChuanHoa(s); if (!Nguoi::checkSoDienThoai(t)) return false; soDienThoai=t; return true; }
bool KhachHang::setDiaChi(const string& s) { string t=ChuanHoa(s); if (!hopLeText(t,true)) return false; diaChi=t; return true; }
bool KhachHang::setDiem(int p) { if (p<0) return false; diem=p; return true; }
string KhachHang::toChuoi() const { ostringstream os; os << ma << '|' << hoTen << '|' << soDienThoai << '|' << diaChi << '|' << diem; return os.str(); }
bool KhachHang::fromChuoi(const string& s) { vector<string> p=TachChuoi(s,'|'); int d=0; return p.size()==5 && ChuoiSangInt(p[4],d) && setMa(p[0]) && setHoTen(p[1]) && setSoDienThoai(p[2]) && setDiaChi(p[3]) && setDiem(d); }

vector<TacGia> docTacGia(const string& f) { return docDanhMuc<TacGia>(f); }
vector<TheLoai> docTheLoai(const string& f) {
    vector<TheLoai> ds;
    ifstream file(f);
    string dong;
    while (getline(file, dong)) {
        if (ChuanHoa(dong).empty()) continue;
        vector<string> p = TachChuoi(dong, '|');
        if (p.size() != 3) continue;
        TheLoai item;
        if (item.setMa(p[0]) && item.setTen(p[1]) && item.setMoTa(p[2])) ds.push_back(item);
    }
    return ds;
}
vector<NhaXuatBan> docNhaXuatBan(const string& f) { return docDanhMuc<NhaXuatBan>(f); }
vector<NhaCungCap> docNhaCungCap(const string& f) { return docDanhMuc<NhaCungCap>(f); }
vector<KhachHang> docKhachHang(const string& f) { return docDanhMuc<KhachHang>(f); }






