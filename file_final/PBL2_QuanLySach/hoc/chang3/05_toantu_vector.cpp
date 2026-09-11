// =====================================================================
//  NAP CHONG TOAN TU tren lop TEMPLATE - ban rut gon cua Vector.h
//  Gom:  []  (hai ban)   +=   =   (quy tac ba)
//        va lop BoDuyet voi  *  ++  !=   de dung duoc  for pham vi
//
//  Bien dich:  g++ -std=c++17 -Wall -Wextra 05_toantu_vector.cpp -o 05.exe
// =====================================================================
#include <iostream>
#include <string>
using namespace std;

template <class T>
class Vector {
private:
    T*     duLieu;
    size_t soPhanTu, dungLuong;

    void baoDamChua(size_t canCo) {
        if (canCo <= dungLuong) return;
        size_t moi = (dungLuong == 0) ? 4 : dungLuong * 2;   // TANG GAP DOI
        while (moi < canCo) moi *= 2;
        T* vungMoi = new T[moi];
        for (size_t i = 0; i < soPhanTu; ++i) vungMoi[i] = duLieu[i];
        delete[] duLieu;
        duLieu = vungMoi;
        dungLuong = moi;
    }

public:
    Vector() : duLieu(0), soPhanTu(0), dungLuong(0) {}

    // ---------------- QUY TAC BA ----------------
    ~Vector() { delete[] duLieu; }

    Vector(const Vector<T>& khac) : duLieu(0), soPhanTu(0), dungLuong(0) {
        baoDamChua(khac.soPhanTu);
        for (size_t i = 0; i < khac.soPhanTu; ++i) duLieu[i] = khac.duLieu[i];
        soPhanTu = khac.soPhanTu;
    }

    Vector<T>& operator=(const Vector<T>& khac) {
        if (this == &khac) return *this;          // chan tu gan cho chinh minh
        delete[] duLieu;                          // bo vung cu
        duLieu = 0; soPhanTu = 0; dungLuong = 0;
        baoDamChua(khac.soPhanTu);                // cap vung moi
        for (size_t i = 0; i < khac.soPhanTu; ++i) duLieu[i] = khac.duLieu[i];
        soPhanTu = khac.soPhanTu;
        return *this;
    }

    size_t kichThuoc() const { return soPhanTu; }
    size_t sucChua()   const { return dungLuong; }

    // ---------------- [] : hai ban, khac nhau o const ----------------
    // ban khong const -> tra T&      -> cho phep  ds[0] = x;
    T&       operator[](size_t i)       { return duLieu[i]; }
    // ban co const    -> tra const T& -> goi duoc tren  const Vector<T>&
    const T& operator[](size_t i) const { return duLieu[i]; }

    void them(const T& x) { baoDamChua(soPhanTu + 1); duLieu[soPhanTu++] = x; }

    // ---------------- += : them phan tu vao cuoi ----------------
    Vector<T>& operator+=(const T& x) { them(x); return *this; }

    // ---------------- BoDuyet: de dung duoc  for (x : ds) ----------------
    // Trinh bien dich dich vong for pham vi thanh vong while goi dung 3 toan tu:
    //     *   de lay gia tri
    //     ++  de di toi phan tu sau
    //     !=  de biet da het chua
    class BoDuyet {
        T* hienTai;
    public:
        BoDuyet(T* p) : hienTai(p) {}
        T&       operator*()  const { return *hienTai; }
        BoDuyet& operator++()       { ++hienTai; return *this; }
        bool     operator!=(const BoDuyet& k) const { return hienTai != k.hienTai; }
    };
    BoDuyet begin() const { return BoDuyet(duLieu); }
    BoDuyet end()   const { return BoDuyet(duLieu + soPhanTu); }
};

// Nhan const& -> BAT BUOC phai co ban operator[] const, neu khong se loi bien dich
template <class T>
void inRa(const string& nhan, const Vector<T>& ds) {
    cout << nhan;
    for (size_t i = 0; i < ds.kichThuoc(); ++i) cout << ' ' << ds[i];
    cout << "   (kichThuoc=" << ds.kichThuoc() << ", sucChua=" << ds.sucChua() << ")\n";
}

int main() {
    Vector<int> a;

    cout << "--- 1. Toan tu += : them phan tu ---\n";
    a += 10; a += 20; a += 30;
    inRa("a:", a);

    cout << "\n--- 2. Toan tu [] : dung nhu mang thuong ---\n";
    a[0] = 99;                       // can ban KHONG const, tra ve T&
    cout << "a[0] sau khi gan = " << a[0] << '\n';

    cout << "\n--- 3. for pham vi nho *  ++  != cua BoDuyet ---\n";
    cout << "a:";
    for (int v : a) cout << ' ' << v;
    cout << '\n';

    cout << "\n--- 4. Quy tac ba: sao chep SAU ---\n";
    Vector<int> b = a;               // ham tao sao chep
    b[0] = -1;
    inRa("a:", a);
    inRa("b:", b);
    cout << "   a khong doi khi sua b -> sao chep sau dung.\n";

    Vector<int> c;
    c += 7;
    c = a;                           // toan tu gan
    inRa("c sau khi  c = a :", c);

    cout << "\n--- 5. Dung voi kieu khac (template) ---\n";
    Vector<string> ds;
    ds += "Toan 12"; ds += "So Do"; ds += "Doraemon";
    inRa("ds:", ds);

    cout << "\n--- 6. Tang gap doi dung luong ---\n";
    Vector<int> d;
    for (int i = 1; i <= 9; ++i) {
        d += i;
        cout << "   them " << i << " -> kichThuoc=" << d.kichThuoc()
             << ", sucChua=" << d.sucChua() << '\n';
    }
    return 0;
}
