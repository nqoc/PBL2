// =====================================================================
//  TRUONG HOP 2 - CO VIET du quy tac ba
//      (1) ham huy       (2) ham tao sao chep      (3) toan tu gan
//  Ket qua: sao chep SAU -> moi doi tuong co vung nho rieng -> an toan
//
//  Bien dich:  g++ -std=c++17 -Wall -Wextra 02_co_viet.cpp -o 02.exe
// =====================================================================
#include <iostream>
using namespace std;

class MangSo {
private:
    int* duLieu;
    int  soPhanTu;

public:
    MangSo(int n) : duLieu(new int[n]), soPhanTu(n) {
        for (int i = 0; i < n; ++i) duLieu[i] = 0;
        cout << "  [+] cap phat  " << duLieu << '\n';
    }

    // ---------- (1) HAM HUY ----------
    ~MangSo() {
        cout << "  [-] giai phong " << duLieu << '\n';
        delete[] duLieu;
    }

    // ---------- (2) HAM TAO SAO CHEP ----------
    // Doi tuong CHUA ton tai -> khong co gi de giai phong, chi cap moi va chep.
    MangSo(const MangSo& khac) : duLieu(new int[khac.soPhanTu]),
                                 soPhanTu(khac.soPhanTu) {
        for (int i = 0; i < soPhanTu; ++i)
            duLieu[i] = khac.duLieu[i];          // chep TUNG PHAN TU (sao chep sau)
        cout << "  [c] sao chep sau -> vung moi " << duLieu << '\n';
    }

    // ---------- (3) TOAN TU GAN ----------
    // Doi tuong DA ton tai va dang giu vung nho cu -> phai giai phong truoc.
    MangSo& operator=(const MangSo& khac) {
        if (this == &khac) return *this;         // BAT BUOC: chan  a = a;

        delete[] duLieu;                         // bo vung CU
        soPhanTu = khac.soPhanTu;
        duLieu   = new int[soPhanTu];            // cap vung MOI
        for (int i = 0; i < soPhanTu; ++i)
            duLieu[i] = khac.duLieu[i];          // chep sau

        cout << "  [=] gan sau    -> vung moi " << duLieu << '\n';
        return *this;                            // cho phep  a = b = c;
    }

    void dat(int i, int v) { duLieu[i] = v; }
    int  lay(int i) const  { return duLieu[i]; }
};

int main() {
    cout << "1. Tao a va c:\n";
    MangSo a(3);
    a.dat(0, 10);
    MangSo c(3);

    cout << "\n2. Sao chep  b = a;  (ham tao sao chep CUA TA)\n";
    MangSo b = a;

    cout << "\n3. Sua b: b[0] = 99\n";
    b.dat(0, 99);
    cout << "   a[0] = " << a.lay(0) << "   <-- a KHONG doi. Dung nhu mong doi.\n";

    cout << "\n4. Gan  c = a;  (toan tu gan CUA TA)\n";
    c = a;
    cout << "   c[0] = " << c.lay(0) << '\n';

    cout << "\n5. Thu tu gan cho chinh minh  a = a;\n";
    a = a;
    cout << "   a[0] = " << a.lay(0) << "   <-- van con nguyen nho dong  if (this == &khac)\n";

    cout << "\n6. Ket thuc main -> huy c, b, a (nguoc thu tu tao):\n";
    return 0;
}
