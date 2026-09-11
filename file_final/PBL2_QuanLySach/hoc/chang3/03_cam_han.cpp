// =====================================================================
//  TRUONG HOP 3 - CAM HAN sao chep
//  Dung khi: sao chep doi tuong vua vo nghia vua nguy hiem.
//  Vi du that trong PBL2: QuanLySach (so huu mang Sach*) va CuaHang.
//
//  Cach lam (kieu C++98, dung trong du an):
//      khai bao ham tao sao chep + toan tu gan o vung private
//      va KHONG dinh nghia chung.
//      -> ben ngoai goi: loi luc BIEN DICH
//      -> ben trong lo goi: loi luc LIEN KET
//
//  Bien dich:  g++ -std=c++17 -Wall -Wextra 03_cam_han.cpp -o 03.exe
// =====================================================================
#include <iostream>
using namespace std;

class KhoSach {
private:
    int* soLuong;
    int  soDauSach;

    // ---------- CAM SAO CHEP ----------
    KhoSach(const KhoSach&);              // khai bao ma KHONG dinh nghia
    KhoSach& operator=(const KhoSach&);   // khai bao ma KHONG dinh nghia

public:
    KhoSach(int n) : soLuong(new int[n]), soDauSach(n) {
        for (int i = 0; i < n; ++i) soLuong[i] = 0;
        cout << "  [+] cap phat  " << soLuong << '\n';
    }
    ~KhoSach() {
        cout << "  [-] giai phong " << soLuong << '\n';
        delete[] soLuong;
    }

    void nhapThem(int i, int sl) { soLuong[i] += sl; }
    int  tonKho(int i) const     { return soLuong[i]; }
    int  soDau() const           { return soDauSach; }
};

// Truyen bang THAM CHIEU HANG -> khong sao chep -> van dung duoc binh thuong
void inTonKho(const KhoSach& kho) {
    cout << "   ton kho:";
    for (int i = 0; i < kho.soDau(); ++i) cout << ' ' << kho.tonKho(i);
    cout << '\n';
}

int main() {
    cout << "1. Tao kho:\n";
    KhoSach kho(3);
    kho.nhapThem(0, 50);
    kho.nhapThem(1, 20);

    cout << "\n2. Truyen bang const& -> KHONG sao chep, chay tot:\n";
    inTonKho(kho);

    cout << "\n3. Thu sao chep -> bi chan ngay luc bien dich.\n";
    cout << "   Bo dau // o mot trong hai dong duoi roi bien dich lai de xem loi:\n\n";

    // KhoSach ban = kho;          // loi: 'KhoSach::KhoSach(const KhoSach&)' is private
    // KhoSach khac(5); khac = kho; // loi: 'KhoSach& KhoSach::operator=(const KhoSach&)' is private

    // void inSaiCach(KhoSach kho);   <-- truyen theo GIA TRI cung bi chan,
    //                                    vi no can ham tao sao chep.

    cout << "   Uu diem: loi hien ngay khi bien dich, khong doi den luc chay moi sap.\n";

    cout << "\n4. Ket thuc main:\n";
    return 0;
}
