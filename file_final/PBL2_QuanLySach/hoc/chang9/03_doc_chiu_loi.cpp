// =====================================================================
//  BT9.3 - Tep co dong rac va dong trong: bo qua, DEM va BAO so dong loi
//          So sanh try/catch TRONG vong lap vs NGOAI vong lap
//
//  Bien dich:  g++ -std=c++17 -Wall -Wextra 03_doc_chiu_loi.cpp -o 03.exe  &  03.exe
// =====================================================================
#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <string>
#include <vector>
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

class SinhVien {
    string maSV, hoTen, lop;
    double diemTB = 0;
public:
    SinhVien() {}
    SinhVien(string ma, string ten, string l, double d)
        : maSV(ma), hoTen(ten), lop(l), diemTB(d) {}
    string toCSV() const {
        ostringstream os; os << fixed << setprecision(2);
        os << maSV << '|' << hoTen << '|' << lop << '|' << diemTB;
        return os.str();
    }
    void fromCSV(const vector<string>& p) {
        if (p.size() < 4) throw runtime_error("thieu truong (can 4, co "
                                              + to_string(p.size()) + ")");
        maSV = chuanHoa(p[0]); hoTen = chuanHoa(p[1]); lop = chuanHoa(p[2]);
        string sd = chuanHoa(p[3]);
        try { diemTB = stod(sd); }                       // stod NEM LOI neu khong phai so
        catch (const exception&) { throw runtime_error("diem khong phai so: \"" + sd + "\""); }
        if (diemTB < 0 || diemTB > 10) throw runtime_error("diem ngoai khoang 0-10");
    }
    void xuatDong() const {
        cout << "     " << left << setw(12) << maSV << setw(18) << hoTen
             << setw(8) << lop << right << setw(6)
             << fixed << setprecision(2) << diemTB << '\n';
    }
};

// ================= CACH SAI: try NGOAI vong lap =================
int docSai(const string& tep) {
    vector<SinhVien> ds;
    ifstream f(tep.c_str());
    if (!f) return -1;
    string dong;
    try {
        while (getline(f, dong)) {                      // vong lap NAM TRONG try
            if (chuanHoa(dong).empty()) continue;
            SinhVien x; x.fromCSV(tachChuoi(dong, '|')); ds.push_back(x);
        }
    } catch (const exception&) { }                       // nhay ra day -> VONG LAP CHET
    return (int)ds.size();
}

// ================= CACH DUNG: try TRONG vong lap =================
bool docDung(vector<SinhVien>& ds, const string& tep, int& soDongLoi) {
    soDongLoi = 0;
    ifstream f(tep.c_str());
    if (!f) return false;                                // chua co tep: BINH THUONG
    ds.clear();                                          // xoa du lieu cu trong RAM
    string dong;
    int soThuTu = 0;
    while (getline(f, dong)) {
        ++soThuTu;
        if (chuanHoa(dong).empty()) continue;            // bo dong trong (khong tinh la loi)
        try {                                            // try NAM TRONG vong lap
            SinhVien x;
            x.fromCSV(tachChuoi(dong, '|'));
            ds.push_back(x);
        } catch (const exception& e) {
            ++soDongLoi;
            cout << "     [bo qua dong " << soThuTu << "] \"" << dong
                 << "\"  -> " << e.what() << '\n';
        }
    }
    return true;
}

int main() {
    // ---------- tao tep co du loai rac ----------
    {
        ofstream f("sv_loi.txt");
        f << "102210001|Nguyen Van A|25T1|8.25\n"      // 1 OK
          << "abc\n"                                    // 2 rac hoan toan
          << "\n"                                       // 3 dong trong
          << "102210002|Tran Thi B|25T2|7.50\n"         // 4 OK
          << "102210003|Le Van C|25T1\n"                // 5 thieu truong
          << "   \n"                                    // 6 chi co khoang trang
          << "102210004|Pham Thi D|25T3|abc\n"          // 7 diem khong phai so
          << "102210005|Hoang Van E|25T2|15.0\n"        // 8 diem ngoai khoang
          << "102210006|Vo Thi F|25T1|9.00\n";          // 9 OK
    }

    cout << "\n=== TEP sv_loi.txt (9 dong, chi 3 dong hop le) ===\n";
    { ifstream g("sv_loi.txt"); string d; int i = 0;
      while (getline(g, d)) cout << "   " << ++i << ": \"" << d << "\"\n"; }

    cout << "\n=== CACH SAI: try NGOAI vong lap ===\n";
    cout << "   Doc duoc " << docSai("sv_loi.txt") << "/3 sinh vien hop le\n";
    cout << "   ^^ Dung ngay o dong 2, mat het phan sau. MOT dong rac = MAT CA TEP.\n";

    cout << "\n=== CACH DUNG: try TRONG vong lap ===\n";
    vector<SinhVien> ds;
    int loi = 0;
    docDung(ds, "sv_loi.txt", loi);
    cout << "\n   Ket qua:\n";
    for (size_t i = 0; i < ds.size(); ++i) ds[i].xuatDong();
    cout << "\n   >> Canh bao: bo qua " << loi << " dong sai dinh dang trong tep du lieu.\n";
    cout << "   ^^ Doc duoc " << ds.size() << "/3 sinh vien hop le. Khong mat gi ca.\n";

    cout << "\n=== GHI NHO ===\n"
         << "  try/catch phai nam TRONG vong lap -> vong lap song sot\n"
         << "  Dong TRONG: bo qua bang continue, KHONG tinh la loi\n"
         << "  Dong RAC  : bat ngoai le, DEM lai, doc tiep\n"
         << "  Cuoi cung PHAI BAO so dong loi - im lang la nguoi dung tuong du lieu day du\n"
         << "  Dung stod/stoi thay atof/atoi: chung NEM LOI thay vi tra ve 0 am tham\n\n";
    return 0;
}
