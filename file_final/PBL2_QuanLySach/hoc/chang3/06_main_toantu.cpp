// =====================================================================
//  06_main_toantu.cpp  -  Thu 4 toan tu cua Sach + toan tu cua Vector
//  Dung CHINH cac lop that trong du an (include/ va src/).
//
//  Bien dich (bo qua src/main.cpp de khong trung ham main):
//    g++ -std=c++17 -Wall -Wextra -Iinclude
//        hoc/chang3/06_main_toantu.cpp
//        src/Sach.cpp src/SachGiaoKhoa.cpp src/SachVanHoc.cpp
//        src/SachThieuNhi.cpp src/TienIch.cpp -o thu_toantu.exe
// =====================================================================
#include <iostream>
#include <string>
#include "Sach.h"
#include "SachGiaoKhoa.h"
#include "SachVanHoc.h"
#include "SachThieuNhi.h"
#include "Vector.h"
#include "NgoaiLe.h"

using namespace std;

int main() {
    cout << "===== 1. TOAN TU <<  : in truc tiep doi tuong =====\n";

    SachGiaoKhoa gk("GK001", "Toan 12 - Tap 1", "TG001", "TL001", "NX001",
                    2023, 26000, 35000, 147, "Toan", 12, "A1-01");
    SachVanHoc   vh("VH001", "So Do", "TG002", "TL002", "NX003",
                    2020, 62000, 89000, 23, "Tieu thuyet", "Khong", "B2-05");
    SachThieuNhi tn("TN001", "Doraemon Tap 1", "TG004", "TL003", "NX002",
                    2019, 18000, 25000, 240, 6, true, "C1-01");

    // cout << doi tuong  ->  goi operator<< (ham ban)
    // Noi duoc vao chuoi << vi operator<< tra ve ostream&
    cout << "  gk = " << gk << '\n';
    cout << "  vh = " << vh << '\n';
    cout << "  tn = " << tn << "\n\n";


    cout << "===== 2. TOAN TU ==  : bang nhau khi CUNG MA SACH =====\n";

    SachGiaoKhoa trung("gk001", "Ten khac han", "TG009", "TL009", "NX009",
                       2024, 1000, 2000, 5, "Ly", 11);

    // So sanh qua tham chieu lop cha -> van goi dung operator== cua Sach
    cout << "  gk == trung ? " << (gk == trung ? "dung" : "sai")
         << "   <-- cung ma GK001/gk001, du ten va gia khac\n";
    cout << "  gk == vh    ? " << (gk == vh ? "dung" : "sai") << "\n\n";


    cout << "===== 3. TOAN TU <   : re hon (theo gia SAU giam) =====\n";

    // gk giam 10% -> 31500 ; vh giam 5% -> 84550 ; tn giam 15% -> 21250
    cout << "  gia sau giam:  gk=" << gk.giaSauGiam()
         << "  vh=" << vh.giaSauGiam()
         << "  tn=" << tn.giaSauGiam() << '\n';
    cout << "  gk < vh ? " << (gk < vh ? "dung" : "sai") << '\n';
    cout << "  vh < tn ? " << (vh < tn ? "dung" : "sai") << "\n\n";


    cout << "===== 4. TOAN TU +=  : nhap them vao kho =====\n";

    cout << "  ton truoc      = " << gk.getSoLuong() << '\n';
    gk += 20;                                   // = gk.operator+=(20)
    cout << "  gk += 20   ton = " << gk.getSoLuong() << '\n';
    (gk += 5) += 3;                             // chay duoc vi += tra ve Sach&
    cout << "  (gk+=5)+=3 ton = " << gk.getSoLuong() << '\n';
    // Toan tu goi nhapThemKho(), ma ham do NEM NGOAI LE khi so luong <= 0.
    // Vay ngoai le xuyen qua toan tu ra ngoai -> phai boc try/catch.
    try {
        gk += -100;
    } catch (const LoiUngDung& e) {
        cout << "  gk += -100  ->  !! " << e.what() << '\n';
    }
    cout << "  ton sau do     = " << gk.getSoLuong()
         << "   <-- khong doi, du lieu van nguyen ven\n\n";


    cout << "===== 5. TOAN TU CUA Vector<T> : += va [] =====\n";

    Vector<Sach*> ds;
    ds += &gk;                                  // operator+= : them vao cuoi
    ds += &vh;
    ds += &tn;
    cout << "  so phan tu = " << ds.kichThuoc() << '\n';

    for (size_t i = 0; i < ds.kichThuoc(); ++i)
        cout << "    [" << i << "] " << *ds[i] << '\n';   // [] roi << : hai toan tu long nhau
    cout << '\n';


    cout << "===== 6. TIM SACH RE NHAT bang toan tu <  =====\n";

    Sach* reNhat = ds[0];
    for (size_t i = 1; i < ds.kichThuoc(); ++i)
        if (*ds[i] < *reNhat) reNhat = ds[i];    // *ds[i] de lay DOI TUONG, khong phai con tro
    cout << "  re nhat: " << *reNhat << "\n\n";


    cout << "===== 7. TOAN TU =  cua Vector : sao chep SAU =====\n";

    Vector<int> a;
    a += 10; a += 20; a += 30;

    Vector<int> b = a;          // ham tao sao chep
    b[0] = 99;                  // sua ban sao

    cout << "  a[0] = " << a[0] << "   <-- KHONG doi\n";
    cout << "  b[0] = " << b[0] << "   <-- chi ban sao doi\n";

    Vector<int> c;
    c += 7;
    c = a;                      // toan tu gan
    cout << "  c sau khi c = a :";
    for (size_t i = 0; i < c.kichThuoc(); ++i) cout << ' ' << c[i];
    cout << "\n\n";


    cout << "===== 8. NEU KHONG CO NAP CHONG THI PHAI VIET THE NAY =====\n";
    cout << "  co  nap chong:  if (gk == vh)      gk += 20;      cout << gk;\n";
    cout << "  khong nap chong: if (gk.bangNhau(vh)) gk.nhapThemKho(20); gk.xuatDong();\n";

    return 0;
}
