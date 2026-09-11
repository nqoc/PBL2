// =====================================================================
//  BT9.2 - Lop SinhVien co toCSV()/fromCSV(); ghi 3 SV xuong sv.txt,
//          doc lai vao Vector<SinhVien>, in ra va DOI CHIEU
//
//  Bien dich:  g++ -std=c++17 -Wall -Wextra 02_sinhvien.cpp -o 02.exe  &  02.exe
// =====================================================================
#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <string>
#include <vector>
#include <stdexcept>
using namespace std;

// --------------------------------------------- Vector<T> rut gon (chang 7)
template <class T>
class Vector {
private:
    T*     duLieu;
    size_t soPhanTu, dungLuong;
    void moRong() {
        dungLuong *= 2;
        T* moi = new T[dungLuong];
        for (size_t i = 0; i < soPhanTu; ++i) moi[i] = duLieu[i];
        delete[] duLieu; duLieu = moi;
    }
public:
    Vector() : duLieu(new T[2]), soPhanTu(0), dungLuong(2) {}
    ~Vector() { delete[] duLieu; }
    Vector(const Vector& k) : duLieu(new T[k.dungLuong]),
                              soPhanTu(k.soPhanTu), dungLuong(k.dungLuong) {
        for (size_t i = 0; i < soPhanTu; ++i) duLieu[i] = k.duLieu[i];
    }
    Vector& operator=(const Vector& k) {
        if (this == &k) return *this;
        delete[] duLieu;
        dungLuong = k.dungLuong; soPhanTu = k.soPhanTu;
        duLieu = new T[dungLuong];
        for (size_t i = 0; i < soPhanTu; ++i) duLieu[i] = k.duLieu[i];
        return *this;
    }
    void   them(const T& x) { if (soPhanTu == dungLuong) moRong(); duLieu[soPhanTu++] = x; }
    void   xoaHet() { soPhanTu = 0; }
    size_t kichThuoc() const { return soPhanTu; }
    T&       operator[](size_t i)       { return duLieu[i]; }
    const T& operator[](size_t i) const { return duLieu[i]; }
};

// --------------------------------------------- ham phu tro
vector<string> tachChuoi(const string& dong, char nc) {
    vector<string> kq; stringstream ss(dong); string ph;
    while (getline(ss, ph, nc)) kq.push_back(ph);
    return kq;
}
string chuanHoa(const string& s) {            // cat khoang trang VA ky tu \r cua Windows
    size_t d = 0, c = s.size();
    while (d < c && (s[d]==' '||s[d]=='\t'||s[d]=='\r'||s[d]=='\n')) ++d;
    while (c > d && (s[c-1]==' '||s[c-1]=='\t'||s[c-1]=='\r'||s[c-1]=='\n')) --c;
    return s.substr(d, c - d);
}
string locKyTu(const string& s) {             // bo ky tu phan cach khoi du lieu nguoi dung
    string kq;
    for (size_t i = 0; i < s.size(); ++i)
        if (s[i] != '|' && s[i] != '#') kq += s[i];
    return kq;
}

// =====================================================================
class SinhVien {
private:
    string maSV, hoTen, lop;
    double diemTB;
public:
    SinhVien() : diemTB(0) {}                                    // T() - bat buoc cho Vector<T>
    SinhVien(string ma, string ten, string l, double d)
        : maSV(locKyTu(ma)), hoTen(locKyTu(ten)), lop(locKyTu(l)), diemTB(d) {}

    string getMa()  const { return maSV; }
    string getTen() const { return hoTen; }
    double getDiem() const { return diemTB; }

    // ---------- Object -> chuoi ----------
    string toCSV() const {
        ostringstream os;
        os << fixed << setprecision(2);          // diem: 2 chu so thap phan
        os << maSV << '|' << hoTen << '|' << lop << '|' << diemTB;
        return os.str();
    }

    // ---------- chuoi -> Object ----------
    void fromCSV(const vector<string>& p) {
        if (p.size() < 4) throw runtime_error("Dong SinhVien thieu truong");
        maSV   = chuanHoa(p[0]);
        hoTen  = chuanHoa(p[1]);
        lop    = chuanHoa(p[2]);
        diemTB = atof(chuanHoa(p[3]).c_str());
    }

    void xuatDong() const {
        cout << "   " << left << setw(12) << maSV << setw(20) << hoTen
             << setw(10) << lop << right << setw(6)
             << fixed << setprecision(2) << diemTB << '\n';
    }
    // de DOI CHIEU truoc/sau khi ghi-doc
    bool giongVoi(const SinhVien& k) const {
        return maSV == k.maSV && hoTen == k.hoTen && lop == k.lop
            && (diemTB - k.diemTB < 0.001) && (k.diemTB - diemTB < 0.001);
    }
};

// =====================================================================
bool luuFile(const Vector<SinhVien>& ds, const string& tep) {
    ofstream f(tep.c_str());
    if (!f) return false;                        // ghi khong duoc -> LOI that
    for (size_t i = 0; i < ds.kichThuoc(); ++i)
        f << ds[i].toCSV() << '\n';
    return true;
}

bool docFile(Vector<SinhVien>& ds, const string& tep, int& soDongLoi) {
    soDongLoi = 0;
    ifstream f(tep.c_str());
    if (!f) return false;                        // chua co tep -> BINH THUONG
    ds.xoaHet();                                 // xoa du lieu cu TRONG RAM
    string dong;
    while (getline(f, dong)) {
        if (chuanHoa(dong).empty()) continue;
        try {
            SinhVien x;
            x.fromCSV(tachChuoi(dong, '|'));
            ds.them(x);
        } catch (const exception&) { ++soDongLoi; }
    }
    return true;
}

int main() {
    // ---------- tao du lieu goc ----------
    Vector<SinhVien> goc;
    goc.them(SinhVien("102210001", "Nguyen Van A",  "25T1", 8.25));
    goc.them(SinhVien("102210002", "Tran Thi B",    "25T2", 7.50));
    goc.them(SinhVien("102210003", "Le Van C|Dung", "25T1", 9.00));  // ten co dau |

    cout << "\n=== 1. DU LIEU GOC (trong RAM) ===\n";
    cout << "   " << left << setw(12) << "MA" << setw(20) << "HO TEN"
         << setw(10) << "LOP" << right << setw(6) << "DIEM" << '\n';
    for (size_t i = 0; i < goc.kichThuoc(); ++i) goc[i].xuatDong();
    cout << "   ^^ SV thu 3 nhap ten \"Le Van C|Dung\" nhung dau | da bi LOC bo\n";

    cout << "\n=== 2. GHI xuong sv.txt ===\n";
    if (!luuFile(goc, "sv.txt")) { cout << "   Khong ghi duoc!\n"; return 1; }
    { ifstream g("sv.txt"); string d;
      while (getline(g, d)) cout << "   " << d << '\n'; }

    cout << "\n=== 3. DOC LAI vao Vector<SinhVien> ===\n";
    Vector<SinhVien> docLai;
    int loi = 0;
    if (!docFile(docLai, "sv.txt", loi)) { cout << "   Chua co tep\n"; return 1; }
    for (size_t i = 0; i < docLai.kichThuoc(); ++i) docLai[i].xuatDong();

    cout << "\n=== 4. DOI CHIEU goc vs doc lai ===\n";
    if (goc.kichThuoc() != docLai.kichThuoc()) {
        cout << "   SAI: so luong khac nhau\n";
    } else {
        bool tatCaKhop = true;
        for (size_t i = 0; i < goc.kichThuoc(); ++i) {
            bool k = goc[i].giongVoi(docLai[i]);
            cout << "   SV " << (i + 1) << " (" << goc[i].getMa() << "): "
                 << (k ? "KHOP" : "KHAC NHAU") << '\n';
            if (!k) tatCaKhop = false;
        }
        cout << "\n   >> " << (tatCaKhop ? "VONG TRON GHI-DOC HOAN HAO"
                                         : "CO SAI SOT, kiem tra lai toCSV/fromCSV") << '\n';
    }

    cout << "\n=== GHI NHO ===\n"
         << "  toCSV() va fromCSV() la MOT CAP: thu tu truong phai giong het nhau\n"
         << "  Kiem tra p.size() truoc khi truy cap p[i] -> tranh crash\n"
         << "  Loc | va # NGAY LUC NHAP -> du lieu nhat quan o RAM va tep\n"
         << "  chuanHoa() cat ca ky tu \\r cua Windows -> tranh loi so sanh chuoi\n\n";
    return 0;
}
