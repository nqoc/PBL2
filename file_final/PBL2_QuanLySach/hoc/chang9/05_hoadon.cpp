// =====================================================================
//  BT9.5 - HoaDonDonGian::toCSV() theo mau  ma|ngay|soDong|dong1|dong2
//          Moi dong chi tiet dung dau #. Doc lai va KIEM TRA tong tien khop.
//
//  Bien dich:  g++ -std=c++17 -Wall -Wextra 05_hoadon.cpp -o 05.exe  &  05.exe
// =====================================================================
#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <string>
#include <vector>
#include <cmath>
#include <stdexcept>
using namespace std;

vector<string> tachChuoi(const string& dong, char nc) {
    vector<string> kq; stringstream ss(dong); string ph;
    while (getline(ss, ph, nc)) kq.push_back(ph);
    return kq;
}
string chuanHoa(const string& s) {
    size_t d = 0, c = s.size();
    while (d < c && (s[d]==' '||s[d]=='\t'||s[d]=='\r'||s[d]=='\n')) ++d;
    while (c > d && (s[c-1]==' '||s[c-1]=='\t'||s[c-1]=='\r'||s[c-1]=='\n')) --c;
    return s.substr(d, c - d);
}
string locKyTu(const string& s) {
    string kq;
    for (size_t i = 0; i < s.size(); ++i)
        if (s[i] != '|' && s[i] != '#') kq += s[i];
    return kq;
}

// ===================================================== DONG CHI TIET
// Dung dau # ben trong: maSach#tenSach#soLuong#donGia
class DongChiTiet {
private:
    string maSach, tenSach;
    int    soLuong;
    double donGia;
public:
    DongChiTiet() : soLuong(0), donGia(0) {}
    DongChiTiet(string ma, string ten, int sl, double dg)
        : maSach(locKyTu(ma)), tenSach(locKyTu(ten)), soLuong(sl), donGia(dg) {}

    double thanhTien() const { return soLuong * donGia; }

    string toChuoi() const {                       // dung dau # (KHONG dung |)
        ostringstream os;
        os << fixed << setprecision(0);
        os << maSach << '#' << tenSach << '#' << soLuong << '#' << donGia;
        return os.str();
    }
    void fromChuoi(const string& s) {
        vector<string> q = tachChuoi(s, '#');      // cat lan HAI, theo dau #
        if (q.size() < 4) throw runtime_error("DongChiTiet thieu truong (can 4, co "
                                              + to_string(q.size()) + ")");
        maSach  = chuanHoa(q[0]);
        tenSach = chuanHoa(q[1]);
        soLuong = atoi(chuanHoa(q[2]).c_str());
        donGia  = atof(chuanHoa(q[3]).c_str());
    }
    void xuatDong() const {
        cout << "        " << left << setw(10) << maSach << setw(18) << tenSach
             << right << setw(4) << soLuong << setw(10) << (long)donGia
             << setw(12) << (long)thanhTien() << '\n';
    }
};

// ===================================================== HOA DON
// Mau:  ma | ngay | soDong | dong1 | dong2 | ...
class HoaDonDonGian {
private:
    string              ma, ngay;
    vector<DongChiTiet> chiTiet;
public:
    HoaDonDonGian() {}
    HoaDonDonGian(string m, string n) : ma(locKyTu(m)), ngay(locKyTu(n)) {}

    void themDong(const DongChiTiet& d) { chiTiet.push_back(d); }
    string getMa() const { return ma; }
    size_t soDong() const { return chiTiet.size(); }

    double tongTien() const {
        double t = 0;
        for (size_t i = 0; i < chiTiet.size(); ++i) t += chiTiet[i].thanhTien();
        return t;
    }

    // ---------- GHI ----------
    string toCSV() const {
        ostringstream os;
        os << ma << '|' << ngay << '|' << chiTiet.size();   // GHI SO DONG TRUOC
        for (size_t i = 0; i < chiTiet.size(); ++i)
            os << '|' << chiTiet[i].toChuoi();               // roi tung dong chi tiet
        return os.str();
    }

    // ---------- DOC ----------
    void fromCSV(const vector<string>& p) {
        if (p.size() < 3) throw runtime_error("HoaDon thieu truong co ban");
        ma   = chuanHoa(p[0]);
        ngay = chuanHoa(p[1]);

        chiTiet.clear();                                     // xoa chi tiet cu
        int n = atoi(chuanHoa(p[2]).c_str());                // DOC SO DONG
        if (n < 0) throw runtime_error("So dong am");
        for (int i = 0; i < n; ++i) {
            size_t vt = 3 + (size_t)i;                       // p[3], p[4], ...
            if (vt >= p.size())                              // DONG PHONG THU
                throw runtime_error("Bao co " + to_string(n)
                                    + " dong nhung tep chi co " + to_string(p.size() - 3));
            DongChiTiet d;
            d.fromChuoi(p[vt]);
            chiTiet.push_back(d);
        }
    }

    void xuatChiTiet() const {
        cout << "     Hoa don " << ma << "   ngay " << ngay
             << "   (" << chiTiet.size() << " dong)\n";
        cout << "        " << left << setw(10) << "MA" << setw(18) << "TEN SACH"
             << right << setw(4) << "SL" << setw(10) << "DON GIA" << setw(12) << "THANH TIEN" << '\n';
        for (size_t i = 0; i < chiTiet.size(); ++i) chiTiet[i].xuatDong();
        cout << "        " << left << setw(42) << "TONG TIEN"
             << right << setw(12) << (long)tongTien() << '\n';
    }
};

int main() {
    // ---------- tao 2 hoa don ----------
    HoaDonDonGian hd1("HD00001", "04/09/2026");
    hd1.themDong(DongChiTiet("VH002", "Nha Gia Kim",  2, 75050));
    hd1.themDong(DongChiTiet("TN001", "Doraemon T1",  5, 21250));
    hd1.themDong(DongChiTiet("GK001", "Toan 12",      1, 35000));

    HoaDonDonGian hd2("HD00002", "05/09/2026");
    hd2.themDong(DongChiTiet("VH001", "So Do",        3, 89000));

    cout << "\n=== 1. HOA DON GOC ===\n";
    hd1.xuatChiTiet(); cout << '\n'; hd2.xuatChiTiet();

    // ---------- GHI ----------
    cout << "\n=== 2. GHI xuong hoadon.txt ===\n";
    { ofstream f("hoadon.txt");
      f << hd1.toCSV() << '\n' << hd2.toCSV() << '\n'; }
    { ifstream g("hoadon.txt"); string d;
      while (getline(g, d)) cout << "   " << d << '\n'; }
    cout << "\n   Cau truc:  ma | ngay | soDong | dong1 | dong2 | dong3\n"
         << "              moi dongN dung dau #:  maSach#tenSach#soLuong#donGia\n";

    // ---------- DOC LAI ----------
    cout << "\n=== 3. DOC LAI va DOI CHIEU TONG TIEN ===\n";
    vector<HoaDonDonGian> ds;
    int loi = 0;
    { ifstream f("hoadon.txt"); string dong;
      while (getline(f, dong)) {
          if (chuanHoa(dong).empty()) continue;
          try { HoaDonDonGian h; h.fromCSV(tachChuoi(dong, '|')); ds.push_back(h); }
          catch (const exception& e) { ++loi; cout << "   [bo qua] " << e.what() << '\n'; }
      } }

    double tongGoc[2] = { hd1.tongTien(), hd2.tongTien() };
    for (size_t i = 0; i < ds.size(); ++i) {
        ds[i].xuatChiTiet();
        double sai = fabs(ds[i].tongTien() - tongGoc[i]);
        cout << "        Goc = " << (long)tongGoc[i]
             << ", doc lai = " << (long)ds[i].tongTien()
             << "  ->  " << (sai < 0.01 ? "KHOP" : "LECH!") << "\n\n";
    }

    // ---------- TEP HONG ----------
    cout << "=== 4. Tep hong: bao 3 dong nhung chi co 1 ===\n";
    { ofstream f("hd_loi.txt");
      f << "HD00003|06/09/2026|3|VH001#So Do#1#89000\n"        // thieu 2 dong
        << "HD00004|07/09/2026|1|thieu#truong\n"                // dong chi tiet thieu
        << "HD00005|08/09/2026|2|GK001#Toan#2#35000|TN001#Doremon#1#25000\n"; }
    { ifstream f("hd_loi.txt"); string dong; int ok = 0, l = 0;
      while (getline(f, dong)) {
          if (chuanHoa(dong).empty()) continue;
          try { HoaDonDonGian h; h.fromCSV(tachChuoi(dong, '|')); ++ok; }
          catch (const exception& e) { ++l; cout << "   [bo qua] " << e.what() << '\n'; }
      }
      cout << "   >> Doc duoc " << ok << " hoa don, bo qua " << l << " dong sai\n"; }

    cout << "\n=== GHI NHO ===\n"
         << "  Object chua DANH SACH ben trong -> dung PHAN CACH HAI CAP: | roi #\n"
         << "  PHAI ghi SO DONG truoc -> luc doc moi biet con bao nhieu o la chi tiet\n"
         << "  if (vt >= p.size()) -> dong phong thu, tep cut cung khong crash\n"
         << "  Doi chieu TONG TIEN truoc/sau la cach kiem tra vong tron nhanh nhat\n\n";
    return 0;
}
