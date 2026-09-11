// =====================================================================
//  TRUONG HOP 1 - KHONG VIET quy tac ba
//  Ket qua: sao chep NONG -> hai doi tuong dung chung vung nho
//           -> giai phong hai lan -> CHUONG TRINH DO
//
//  Bien dich:  g++ -std=c++17 -Wall -Wextra 01_khong_viet.cpp -o 01.exe
// =====================================================================
#include <iostream>
using namespace std;

class MangSo {
private:
    int* duLieu;        // <-- CO con tro -> lop nay TU QUAN LY BO NHO
    int  soPhanTu;

public:
    MangSo(int n) : duLieu(new int[n]), soPhanTu(n) {
        for (int i = 0; i < n; ++i) duLieu[i] = 0;
        cout << "  [+] cap phat  " << duLieu << '\n';
    }

    ~MangSo() {
        cout << "  [-] giai phong " << duLieu << '\n';
        delete[] duLieu;
    }

    // KHONG viet ham tao sao chep
    // KHONG viet toan tu gan
    // -> trinh bien dich TU SINH ca hai, va ca hai deu chep DIA CHI

    void dat(int i, int v) { duLieu[i] = v; }
    int  lay(int i) const  { return duLieu[i]; }
};

int main() {
    cout << "1. Tao a:\n";
    MangSo a(3);
    a.dat(0, 10);

    cout << "\n2. Sao chep  b = a;  (goi ham tao sao chep MAC DINH)\n";
    MangSo b = a;

    cout << "\n3. Sua b: b[0] = 99\n";
    b.dat(0, 99);
    cout << "   a[0] = " << a.lay(0) << "   <-- a BI DOI THEO, du ta khong dung toi a\n";

    cout << "\n4. Ket thuc main -> huy b, roi huy a:\n";
    return 0;
    // Hai lan giai phong CUNG mot dia chi -> chuong trinh do o day.
}
