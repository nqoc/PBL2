// =====================================================================
//  NAP CHONG TOAN TU tren lop SACH
//  Dung 5 toan tu giong het lop Sach that cua PBL2:
//      ==   !=   <   +=   <<
//
//  Bien dich:  g++ -std=c++17 -Wall -Wextra 04_toantu_sach.cpp -o 04.exe
// =====================================================================
#include <iostream>
#include <iomanip>
#include <string>
using namespace std;

// Doi chuoi ve chu thuong de so sanh khong phan biet hoa/thuong
static string veThuong(const string& s) {
    string kq = s;
    for (size_t i = 0; i < kq.size(); ++i)
        if (kq[i] >= 'A' && kq[i] <= 'Z') kq[i] = char(kq[i] - 'A' + 'a');
    return kq;
}

class Sach {
private:
    string maSach, tenSach;
    double giaBan;
    int    soLuongTon;

public:
    Sach(const string& ma, const string& ten, double gia, int sl)
        : maSach(ma), tenSach(ten), giaBan(gia), soLuongTon(sl) {}

    string getMa()  const { return maSach; }
    int    getTon() const { return soLuongTon; }
    double giaSauGiam() const { return giaBan * 0.95; }   // gia sau chiet khau 5%

    void nhapThemKho(int sl) {
        if (sl <= 0) return;               // moi kiem tra nam O DAY, khong nam trong toan tu
        soLuongTon += sl;
    }

    // ============ 1) == : hai cuon la MOT khi cung ma sach ============
    // Toan hang trai la Sach  -> ham THANH VIEN
    // const o cuoi            -> cam kem khong sua doi tuong, goi duoc tren const Sach&
    bool operator==(const Sach& k) const {
        return veThuong(maSach) == veThuong(k.maSach);
    }

    // ============ 2) != : viet lai bang == cho khoi lech nhau ============
    bool operator!=(const Sach& k) const { return !(*this == k); }

    // ============ 3) <  : "nho hon" = re hon ============
    bool operator<(const Sach& k) const {
        return giaSauGiam() < k.giaSauGiam();
    }

    // ============ 4) += : nhap them n cuon vao kho ============
    // Tra ve THAM CHIEU chinh minh -> cho phep  s += 5 += 3
    Sach& operator+=(int sl) {
        nhapThemKho(sl);            // goi lai ham nghiep vu, KHONG tu cong tay
        return *this;
    }

    // ============ 5) << : in gon mot cuon ============
    // Toan hang trai la ostream (khong phai Sach) -> KHONG the la ham thanh vien
    // -> khai bao ham BAN de duoc doc thuoc tinh private
    friend ostream& operator<<(ostream& os, const Sach& s);
};

// Tra ve ostream& -> cho phep  cout << a << b << '\n';
ostream& operator<<(ostream& os, const Sach& s) {
    os << s.maSach << " - " << s.tenSach
       << " (" << fixed << setprecision(0) << s.giaBan << "d, ton " << s.soLuongTon << ")";
    return os;
}

int main() {
    Sach a("GK001", "Toan 12", 35000, 147);
    Sach b("gk001", "Toan 12 - ban moi", 40000, 10);   // CUNG ma, khac ten
    Sach c("VH001", "So Do", 89000, 23);

    cout << "--- 1. Toan tu <<  (in truc tiep doi tuong) ---\n";
    cout << "a = " << a << '\n';
    cout << "c = " << c << "\n\n";

    cout << "--- 2. Toan tu ==  (bang nhau = cung ma sach) ---\n";
    cout << "a == b ? " << (a == b ? "dung" : "sai")
         << "   <-- cung ma gk001/GK001, du ten va gia khac nhau\n";
    cout << "a == c ? " << (a == c ? "dung" : "sai") << '\n';
    cout << "a != c ? " << (a != c ? "dung" : "sai") << "\n\n";

    cout << "--- 3. Toan tu <   (re hon, theo gia sau giam) ---\n";
    cout << "a < c ? " << (a < c ? "dung" : "sai") << "   (33250 < 84550)\n\n";

    cout << "--- 4. Toan tu +=  (nhap them kho) ---\n";
    cout << "truoc:  ton = " << a.getTon() << '\n';
    a += 20;
    cout << "a += 20 ton = " << a.getTon() << '\n';
    // Vi += tra ve Sach& nen ket qua van la mot doi tuong -> cong tiep duoc.
    // PHAI co ngoac: toan tu += ket hop tu PHAI sang TRAI, nen
    //     a += 5 += 3   bi hieu la   a += (5 += 3)   -> loi bien dich (5 khong gan duoc)
    // Nap chong toan tu KHONG doi duoc thu tu ket hop cua ngon ngu.
    (a += 5) += 3;
    cout << "(a += 5) += 3  ton = " << a.getTon() << "   (cong 5 roi cong tiep 3)\n";
    a += -100;
    cout << "a += -100    ton = " << a.getTon() << "   <-- bi nhapThemKho() chan\n\n";

    cout << "--- 5. Vi sao tien loi: so sanh hai cach viet ---\n";
    cout << "  khong nap chong:  if (a.bangNhau(c)) ... ; a.nhapThemKho(20); a.inRa();\n";
    cout << "  co  nap chong  :  if (a == c) ...        ; a += 20;           cout << a;\n";
    return 0;
}
