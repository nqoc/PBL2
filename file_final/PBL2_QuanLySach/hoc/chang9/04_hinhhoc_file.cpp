// =====================================================================
//  BT9.4 - Cay HinhHoc (BT6.1) + toCSV()/fromCSV() voi truong dau la MA LOAI
//          Ghi 5 hinh lan loai xuong tep roi doc lai bang HAM XUONG
//
//  Day la cho CHANG 6 (da hinh + ham xuong) va CHANG 9 (doc/ghi tep) gap nhau.
//
//  Bien dich:  g++ -std=c++17 -Wall -Wextra 04_hinhhoc_file.cpp -o 04.exe  &  04.exe
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

// ===================================================================== LOP CHA
class HinhHoc {
protected:
    string ten;                                   // truong CHUNG cua moi hinh
public:
    virtual ~HinhHoc() {}
    virtual double dienTich() const = 0;
    virtual string maLoai()   const = 0;          // "TRON" / "CHUNHAT" / "TAMGIAC"
    virtual string moTa()     const = 0;

    // Cha ghi phan CHUNG:  p[1]
    virtual string toCSV() const { return ten; }
    virtual void   fromCSV(const vector<string>& p) {
        if (p.size() < 2) throw runtime_error("HinhHoc thieu truong");
        ten = chuanHoa(p[1]);
    }
    string getTen() const { return ten; }
    void   setTen(const string& t) { ten = t; }
};

// ===================================================================== LOP CON
class HinhTron : public HinhHoc {
    double r = 0;
public:
    HinhTron() {}
    HinhTron(string t, double r) : r(r) { ten = t; }
    double dienTich() const override { return 3.14159265358979 * r * r; }
    string maLoai()   const override { return "TRON"; }
    string moTa()     const override { return "r = " + to_string((int)r); }

    // MA LOAI | phan cua CHA | phan RIENG cua con
    string toCSV() const override {
        ostringstream os;
        os << maLoai() << '|' << HinhHoc::toCSV() << '|' << fixed << setprecision(2) << r;
        return os.str();
    }
    void fromCSV(const vector<string>& p) override {
        if (p.size() < 3) throw runtime_error("HinhTron thieu truong (can 3)");
        HinhHoc::fromCSV(p);                       // cha doc p[1]
        r = atof(chuanHoa(p[2]).c_str());          // con doc p[2]
    }
};

class HinhChuNhat : public HinhHoc {
    double a = 0, b = 0;
public:
    HinhChuNhat() {}
    HinhChuNhat(string t, double a, double b) : a(a), b(b) { ten = t; }
    double dienTich() const override { return a * b; }
    string maLoai()   const override { return "CHUNHAT"; }
    string moTa()     const override { return to_string((int)a) + " x " + to_string((int)b); }

    string toCSV() const override {
        ostringstream os;
        os << maLoai() << '|' << HinhHoc::toCSV() << '|' << fixed << setprecision(2)
           << a << '|' << b;
        return os.str();
    }
    void fromCSV(const vector<string>& p) override {
        if (p.size() < 4) throw runtime_error("HinhChuNhat thieu truong (can 4)");
        HinhHoc::fromCSV(p);                       // cha doc p[1]
        a = atof(chuanHoa(p[2]).c_str());          // con doc p[2], p[3]
        b = atof(chuanHoa(p[3]).c_str());
    }
};

class HinhTamGiac : public HinhHoc {
    double a = 0, b = 0, c = 0;
public:
    HinhTamGiac() {}
    HinhTamGiac(string t, double a, double b, double c) : a(a), b(b), c(c) { ten = t; }
    double dienTich() const override {
        double p = (a + b + c) / 2.0, t = p * (p - a) * (p - b) * (p - c);
        return (t <= 0) ? 0.0 : sqrt(t);
    }
    string maLoai() const override { return "TAMGIAC"; }
    string moTa()   const override {
        return to_string((int)a) + "," + to_string((int)b) + "," + to_string((int)c);
    }
    string toCSV() const override {
        ostringstream os;
        os << maLoai() << '|' << HinhHoc::toCSV() << '|' << fixed << setprecision(2)
           << a << '|' << b << '|' << c;
        return os.str();
    }
    void fromCSV(const vector<string>& p) override {
        if (p.size() < 5) throw runtime_error("HinhTamGiac thieu truong (can 5)");
        HinhHoc::fromCSV(p);
        a = atof(chuanHoa(p[2]).c_str());
        b = atof(chuanHoa(p[3]).c_str());
        c = atof(chuanHoa(p[4]).c_str());
    }
};

// ============================================================ HAM XUONG (chang 6)
// maLoai() cua lop con VA ham xuong PHAI khop chuoi - day la mot CAP
HinhHoc* taoHinh(const string& maLoai) {
    if (maLoai == "TRON")    return new HinhTron();
    if (maLoai == "CHUNHAT") return new HinhChuNhat();
    if (maLoai == "TAMGIAC") return new HinhTamGiac();
    throw runtime_error("Ma loai hinh khong hop le: \"" + maLoai + "\"");
}

// ===================================================================== GHI / DOC
bool luuFile(const vector<HinhHoc*>& ds, const string& tep) {
    ofstream f(tep.c_str());
    if (!f) return false;
    for (size_t i = 0; i < ds.size(); ++i)
        f << ds[i]->toCSV() << '\n';               // da hinh: goi toCSV cua DUNG lop con
    return true;
}

bool docFile(vector<HinhHoc*>& ds, const string& tep, int& soDongLoi) {
    soDongLoi = 0;
    ifstream f(tep.c_str());
    if (!f) return false;
    for (size_t i = 0; i < ds.size(); ++i) delete ds[i];   // don sach cu
    ds.clear();
    string dong;
    while (getline(f, dong)) {
        if (chuanHoa(dong).empty()) continue;
        HinhHoc* h = nullptr;
        try {
            vector<string> p = tachChuoi(dong, '|');
            h = taoHinh(chuanHoa(p[0]));           // <-- HAM XUONG doc p[0]
            h->fromCSV(p);                          // <-- DA HINH: fromCSV dung lop con
            ds.push_back(h);
            h = nullptr;                            // da giao quyen so huu cho ds
        } catch (const exception& e) {
            delete h;                               // chang 8: don rac neu da new
            ++soDongLoi;
            cout << "     [bo qua] \"" << dong << "\"  -> " << e.what() << '\n';
        }
    }
    return true;
}

void inBang(const vector<HinhHoc*>& ds, const string& nhan) {
    cout << "   " << nhan << '\n';
    cout << "     " << left << setw(10) << "LOAI" << setw(16) << "TEN"
         << setw(16) << "KICH THUOC" << right << setw(10) << "DIEN TICH" << '\n';
    double tong = 0;
    for (size_t i = 0; i < ds.size(); ++i) {
        cout << "     " << left << setw(10) << ds[i]->maLoai()
             << setw(16) << ds[i]->getTen() << setw(16) << ds[i]->moTa()
             << right << setw(10) << fixed << setprecision(2) << ds[i]->dienTich() << '\n';
        tong += ds[i]->dienTich();
    }
    cout << "     " << left << setw(42) << "TONG" << right << setw(10)
         << fixed << setprecision(2) << tong << '\n';
}

int main() {
    // ---------- 5 hinh LAN LOAI ----------
    vector<HinhHoc*> goc;
    goc.push_back(new HinhTron   ("Banh xe",   5));
    goc.push_back(new HinhChuNhat("Cua so",    3, 4));
    goc.push_back(new HinhTamGiac("Mai nha",   3, 4, 5));
    goc.push_back(new HinhTron   ("Dong xu",   2));
    goc.push_back(new HinhChuNhat("Ban hoc",  10, 1));

    cout << "\n=== 1. DU LIEU GOC ===\n";
    inBang(goc, "");

    cout << "\n=== 2. GHI xuong hinh.txt ===\n";
    luuFile(goc, "hinh.txt");
    { ifstream g("hinh.txt"); string d;
      while (getline(g, d)) cout << "   " << d << '\n'; }
    cout << "   ^^ truong dau la MA LOAI -> luc doc biet phai new lop nao\n";

    cout << "\n=== 3. DOC LAI bang HAM XUONG ===\n";
    vector<HinhHoc*> docLai;
    int loi = 0;
    docFile(docLai, "hinh.txt", loi);
    inBang(docLai, "");
    cout << "   >> Doc " << docLai.size() << " hinh, " << loi << " dong loi\n";
    cout << "   ^^ DUNG LOAI, DUNG cong thuc dien tich, DUNG tong\n";

    cout << "\n=== 4. Tep co dong hong ===\n";
    { ofstream f("hinh_loi.txt");
      f << "TRON|Banh xe|5.00\n"
        << "NGUSAC|Hinh la|7\n"                    // ma loai khong ton tai
        << "CHUNHAT|Cua so|3.00\n"                 // thieu 1 truong
        << "\n"
        << "TAMGIAC|Mai nha|3.00|4.00|5.00\n"; }
    vector<HinhHoc*> ds2;
    docFile(ds2, "hinh_loi.txt", loi);
    cout << "   >> Doc duoc " << ds2.size() << " hinh, bo qua " << loi << " dong sai\n";

    for (size_t i = 0; i < goc.size(); ++i)    delete goc[i];
    for (size_t i = 0; i < docLai.size(); ++i) delete docLai[i];
    for (size_t i = 0; i < ds2.size(); ++i)    delete ds2[i];

    cout << "\n=== GHI NHO ===\n"
         << "  Cau truc dong:  [MA LOAI] | [du lieu lop CHA] | [du lieu rieng lop CON]\n"
         << "  Ghi : lop con goi HinhHoc::toCSV() roi noi them phan cua minh\n"
         << "  Doc : taoHinh(p[0]) tao dung lop -> h->fromCSV(p) da hinh doc dung truong\n"
         << "  maLoai() va ham xuong PHAI khop chuoi - lech la ghi duoc ma doc khong duoc\n\n";
    return 0;
}
