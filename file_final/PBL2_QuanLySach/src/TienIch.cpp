// =====================================================================
//  TienIch.cpp - Cai dat cac ham tien ich
// =====================================================================
#include "TienIch.h"

#include <iostream>
#include <sstream>
#include <iomanip>
#include <cstdlib>
#include <cctype>
#include <ctime>

#ifdef _WIN32
#include <conio.h>
#include <io.h>          // _isatty
#endif

using namespace std;

// =====================  NHAP LIEU  =====================
namespace Nhap {

string chuoi(const string& thongBao, bool choPhepRong) {
    string s;
    while (true) {
        cout << thongBao;
        getline(cin, s);
        s = chuanHoa(s);
        if (!s.empty() || choPhepRong) return locKyTu(s);
        cout << "  >> Khong duoc de trong, vui long nhap lai.\n";
    }
}

int soNguyen(const string& thongBao, int nhoNhat, int lonNhat) {
    string s;
    while (true) {
        cout << thongBao;
        getline(cin, s);
        s = chuanHoa(s);
        istringstream is(s);
        int  v;
        char thua;
        if (!(is >> v) || (is >> thua)) {
            cout << "  >> Phai la so nguyen. Nhap lai.\n";
            continue;
        }
        if (v < nhoNhat || v > lonNhat) {
            cout << "  >> Gia tri phai tu " << nhoNhat << " den " << lonNhat
                 << ". Nhap lai.\n";
            continue;
        }
        return v;
    }
}

double soThuc(const string& thongBao, double nhoNhat, double lonNhat) {
    string s;
    while (true) {
        cout << thongBao;
        getline(cin, s);
        s = chuanHoa(s);
        istringstream is(s);
        double v;
        char   thua;
        if (!(is >> v) || (is >> thua)) {
            cout << "  >> Phai la so. Nhap lai.\n";
            continue;
        }
        if (v < nhoNhat || v > lonNhat) {
            cout << "  >> Gia tri phai tu " << nhoNhat << " den " << lonNhat
                 << ". Nhap lai.\n";
            continue;
        }
        return v;
    }
}

bool xacNhan(const string& thongBao) {
    string s;
    while (true) {
        cout << thongBao << " (c/k): ";
        getline(cin, s);
        s = veThuong(chuanHoa(s));
        if (s == "c" || s == "co" || s == "y" || s == "yes")   return true;
        if (s == "k" || s == "khong" || s == "n" || s == "no") return false;
        cout << "  >> Chi nhap c (co) hoac k (khong).\n";
    }
}

string ngay(const string& thongBao) {
    string s;
    while (true) {
        cout << thongBao << " [dd/mm/yyyy, Enter = " << ngayHomNay() << "]: ";
        getline(cin, s);
        s = chuanHoa(s);
        if (s.empty())    return ngayHomNay();
        if (ngayHopLe(s)) return s;
        cout << "  >> Ngay khong hop le. Vi du dung: 05/09/2026\n";
    }
}

string matKhau(const string& thongBao) {
    cout << thongBao;
#ifdef _WIN32
    // Neu du lieu vao khong phai ban phim (bi chuyen huong tu tep khi kiem thu)
    // thi doc binh thuong bang getline
    if (!_isatty(_fileno(stdin))) {
        string s;
        getline(cin, s);
        return chuanHoa(s);
    }
    string s;
    int c;
    while ((c = _getch()) != 13 && c != 10) {      // 13 = Enter
        if (c == 8 || c == 127) {                  // Backspace
            if (!s.empty()) { s.erase(s.size() - 1); cout << "\b \b"; }
        } else if (c == 0 || c == 224) {
            _getch();                              // bo qua phim mo rong
        } else {
            s += static_cast<char>(c);
            cout << "*";
        }
    }
    cout << "\n";
    return s;
#else
    string s;
    getline(cin, s);
    return s;
#endif
}

} // namespace Nhap

// =====================  XU LY CHUOI  =====================

vector<string> tachChuoi(const string& s, char nganCach) {
    vector<string> kq;
    string         tam;
    istringstream  is(s);
    while (getline(is, tam, nganCach)) kq.push_back(tam);
    return kq;
}

string veThuong(string s) {
    for (size_t i = 0; i < s.size(); ++i)
        s[i] = static_cast<char>(tolower(static_cast<unsigned char>(s[i])));
    return s;
}

string chuanHoa(const string& s) {
    size_t dau = 0, cuoi = s.size();
    while (dau < cuoi && isspace(static_cast<unsigned char>(s[dau])))      ++dau;
    while (cuoi > dau && isspace(static_cast<unsigned char>(s[cuoi - 1]))) --cuoi;
    return s.substr(dau, cuoi - dau);
}

string catBot(const string& s, size_t n) {
    if (s.size() <= n) return s;
    if (n <= 3)        return s.substr(0, n);
    return s.substr(0, n - 3) + "...";
}

string locKyTu(const string& s) {
    string kq;
    for (size_t i = 0; i < s.size(); ++i)
        if (s[i] != '|' && s[i] != '#') kq += s[i];
    return kq;
}

bool chuaChuoiCon(const string& nguon, const string& tuKhoa) {
    if (tuKhoa.empty()) return true;
    return veThuong(nguon).find(veThuong(tuKhoa)) != string::npos;
}

string bamMatKhau(const string& mk) {
    // Ham bam don gian kieu djb2, in ra dang hex -> khong giai nguoc duoc
    unsigned long h = 5381;
    for (size_t i = 0; i < mk.size(); ++i)
        h = ((h << 5) + h) + static_cast<unsigned char>(mk[i]);
    ostringstream os;
    os << hex << h;
    return os.str();
}

// =====================  SO / NGAY  =====================

string dinhDangTien(double v) {
    bool am = v < 0;
    if (am) v = -v;
    ostringstream os;
    os << fixed << setprecision(0) << v;
    string s = os.str();
    string kq;
    int    dem = 0;
    for (int i = static_cast<int>(s.size()) - 1; i >= 0; --i) {
        kq += s[static_cast<size_t>(i)];
        if (++dem % 3 == 0 && i > 0) kq += '.';
    }
    string dao(kq.rbegin(), kq.rend());
    return am ? ("-" + dao) : dao;
}

string ngayHomNay() {
    time_t     t  = time(0);
    struct tm* lt = localtime(&t);
    ostringstream os;
    os << setw(2) << setfill('0') << lt->tm_mday << '/'
       << setw(2) << setfill('0') << (lt->tm_mon + 1) << '/'
       << (lt->tm_year + 1900);
    return os.str();
}

bool ngayHopLe(const string& d) {
    vector<string> p = tachChuoi(d, '/');
    if (p.size() != 3) return false;
    if (p[0].size() > 2 || p[1].size() > 2 || p[2].size() != 4) return false;
    for (size_t i = 0; i < p.size(); ++i)
        for (size_t j = 0; j < p[i].size(); ++j)
            if (!isdigit(static_cast<unsigned char>(p[i][j]))) return false;
    int ng = atoi(p[0].c_str());
    int th = atoi(p[1].c_str());
    int nm = atoi(p[2].c_str());
    if (th < 1 || th > 12)      return false;
    if (nm < 1900 || nm > 2200) return false;
    int  soNgay[13] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    bool namNhuan   = (nm % 4 == 0 && nm % 100 != 0) || (nm % 400 == 0);
    if (th == 2 && namNhuan) soNgay[2] = 29;
    return ng >= 1 && ng <= soNgay[th];
}

long soHoaNgay(const string& d) {
    vector<string> p = tachChuoi(d, '/');
    if (p.size() != 3) return 0;
    return atol(p[2].c_str()) * 10000L + atol(p[1].c_str()) * 100L
         + atol(p[0].c_str());
}

string thangCuaNgay(const string& d) {
    vector<string> p = tachChuoi(d, '/');
    if (p.size() != 3) return "";
    ostringstream os;
    os << setw(2) << setfill('0') << atoi(p[1].c_str()) << '/' << p[2];
    return os.str();
}

string doiSangChuoi(int v) {
    ostringstream os;
    os << v;
    return os.str();
}

string doiSangChuoi(double v, int soLeThapPhan) {
    ostringstream os;
    os << fixed << setprecision(soLeThapPhan) << v;
    return os.str();
}

// =====================  MAN HINH  =====================
namespace Man {

void duong(char c, int n) {
    for (int i = 0; i < n; ++i) cout << c;
    cout << '\n';
}

void tieuDe(const string& t) {
    cout << '\n';
    duong('=', 100);
    int le = (100 - static_cast<int>(t.size())) / 2;
    if (le < 0) le = 0;
    for (int i = 0; i < le; ++i) cout << ' ';
    cout << t << '\n';
    duong('=', 100);
}

void dungCho() {
    cout << "\n  Nhan Enter de tiep tuc...";
    string s;
    getline(cin, s);
}

void xoaManHinh() {
#ifdef _WIN32
    if (system("cls") != 0) cout << "\n\n";
#else
    if (system("clear") != 0) cout << "\n\n";
#endif
}

void bieuDoCot(const string& nhan, double giaTri, double giaTriLonNhat,
               int doDaiToiDa) {
    int soO = 0;
    if (giaTriLonNhat > 0)
        soO = static_cast<int>((giaTri / giaTriLonNhat) * doDaiToiDa + 0.5);
    cout << "  " << left << setw(24) << catBot(nhan, 23) << "| ";
    for (int i = 0; i < soO; ++i) cout << '#';
    cout << "  " << dinhDangTien(giaTri) << '\n';
}

} // namespace Man
