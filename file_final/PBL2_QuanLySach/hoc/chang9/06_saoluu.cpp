// =====================================================================
//  BT9.6 - Ham saoLuu(nguon, dich) dung rdbuf()
//
//  Bien dich:  g++ -std=c++17 -Wall -Wextra 06_saoluu.cpp -o 06.exe  &  06.exe
// =====================================================================
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <stdexcept>
#include <filesystem>          // C++17: tao thu muc
using namespace std;
namespace fs = std::filesystem;

// =====================================================================
//  Chep MOT tep. Tra ve true neu thanh cong.
//  ios::binary = chep nguyen xi tung byte, khong cho C++ tu sua ky tu xuong dong
// =====================================================================
bool saoLuu(const string& nguon, const string& dich) {
    ifstream vao(nguon.c_str(), ios::binary);
    if (!vao) return false;                        // khong co tep nguon
    ofstream ra(dich.c_str(), ios::binary);
    if (!ra) return false;                         // khong ghi duoc (thu muc chua ton tai?)
    ra << vao.rdbuf();                             // CHEP CA TEP bang MOT dong
    return ra.good();                              // kiem tra ghi co tron ven khong
}

// Ban nem ngoai le - hop voi chuong trinh dung cay LoiUngDung cua chang 8
void saoLuuHoacNem(const string& nguon, const string& dich) {
    if (!saoLuu(nguon, dich))
        throw runtime_error("Khong sao luu duoc: " + nguon + " -> " + dich);
}

// Sao luu NHIEU tep - dung nhu CuaHang::saoLuu() trong PBL2
int saoLuuTatCa(const vector<string>& tenTep,
                const string& thuMucNguon, const string& thuMucSao) {
    int thanhCong = 0;
    for (size_t i = 0; i < tenTep.size(); ++i) {
        string n = thuMucNguon + "/" + tenTep[i];
        string d = thuMucSao   + "/" + tenTep[i];
        if (saoLuu(n, d)) { ++thanhCong; cout << "     OK   " << n << " -> " << d << '\n'; }
        else                cout << "     BO QUA " << n << " (khong co hoac khong ghi duoc)\n";
    }
    return thanhCong;
}

// ---- ham phu tro de kiem tra ----
long demByte(const string& tep) {
    ifstream f(tep.c_str(), ios::binary | ios::ate);   // ate = nhay ngay toi CUOI tep
    if (!f) return -1;
    return (long)f.tellg();                            // vi tri cuoi = kich thuoc
}
bool giongNhau(const string& a, const string& b) {
    ifstream f1(a.c_str(), ios::binary), f2(b.c_str(), ios::binary);
    if (!f1 || !f2) return false;
    char c1, c2;
    while (f1.get(c1)) { if (!f2.get(c2) || c1 != c2) return false; }
    return !f2.get(c2);                                // f2 cung phai het
}

int main() {
    // ---------- tao tep goc ----------
    { ofstream f("sach.txt");
      f << "GK|GK001|Toan 12|150000|20\n"
        << "VH|VH001|So Do|85000|15\n"
        << "TN|TN001|Doremon|45000|30\n"; }
    { ofstream f("theloai.txt");
      f << "TL001|Tieu thuyet\nTL002|Giao khoa\n"; }

    cout << "\n=== 1. SAO LUU MOT TEP ===\n";
    cout << "   sach.txt co " << demByte("sach.txt") << " byte\n";
    if (saoLuu("sach.txt", "sach_backup.txt"))
        cout << "   Da sao luu -> sach_backup.txt (" << demByte("sach_backup.txt") << " byte)\n";
    cout << "   Hai tep giong het nhau tung byte? "
         << (giongNhau("sach.txt", "sach_backup.txt") ? "CO" : "KHONG") << '\n';

    cout << "\n=== 2. TEP NGUON KHONG TON TAI ===\n";
    cout << "   saoLuu(\"khongco.txt\", \"x.txt\") -> "
         << (saoLuu("khongco.txt", "x.txt") ? "true" : "false  (tra ve false, khong crash)") << '\n';

    cout << "\n=== 3. Ban NEM NGOAI LE (chang 8) ===\n";
    try { saoLuuHoacNem("khongco.txt", "x.txt"); }
    catch (const exception& e) { cout << "   Bat duoc: " << e.what() << '\n'; }

    cout << "\n=== 4. SAO LUU NHIEU TEP (nhu CuaHang::saoLuu) ===\n";
    // ofstream KHONG tu tao thu muc -> phai tao truoc, neu khong moi lan ghi deu that bai
    fs::create_directories("backup");               // C++17 - khong loi neu da co
    cout << "   Da tao thu muc backup/ (ofstream KHONG tu tao thu muc!)\n";

    vector<string> tep;
    tep.push_back("sach.txt");
    tep.push_back("theloai.txt");
    tep.push_back("khachhang.txt");                 // co tinh chua ton tai
    int n = saoLuuTatCa(tep, ".", "backup");
    cout << "   >> Sao luu duoc " << n << "/" << tep.size() << " tep\n";
    cout << "   ^^ Tep chua ton tai thi BO QUA, khong lam dung ca qua trinh\n";
    cout << "   ^^ LUU Y: nguon va dich phai KHAC nhau. Chep tep len chinh no\n"
         << "      se lam ofstream xoa sach tep nguon TRUOC khi ifstream kip doc.\n";

    cout << "\n=== 5. VI SAO CAN SAO LUU? ===\n";
    cout << "   ofstream mo tep la XOA SACH noi dung cu. Thu ngay:\n";
    { ofstream f("sach.txt"); }                     // mo roi dong ngay, KHONG ghi gi
    cout << "   Sau khi mo ofstream ma khong ghi gi: sach.txt con "
         << demByte("sach.txt") << " byte  <- MAT TRANG\n";
    cout << "   Khoi phuc tu ban sao luu...\n";
    saoLuu("sach_backup.txt", "sach.txt");
    cout << "   sach.txt gio co " << demByte("sach.txt") << " byte  <- DA CUU DUOC\n";
    { ifstream g("sach.txt"); string d;
      while (getline(g, d)) cout << "      " << d << '\n'; }

    cout << "\n=== GHI NHO ===\n"
         << "  ra << vao.rdbuf();   chep CA TEP bang mot dong, khong can vong lap\n"
         << "  ios::binary          chep nguyen xi, khong cho C++ sua \\n thanh \\r\\n\n"
         << "  Trong PBL2: goi saoLuu() TRUOC luuTatCa(), vi luu la GHI DE\n"
         << "  Tep nguon khong co -> tra ve false, DUNG nem loi (co the la lan chay dau)\n\n";
    return 0;
}
