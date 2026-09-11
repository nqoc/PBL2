// =====================================================================
//  BT9.1 - Ghi 5 so nguyen xuong tep roi doc lai, tinh tong
//
//  Bien dich:  g++ -std=c++17 -Wall -Wextra 01_ghi_doc_so.cpp -o 01.exe  &  01.exe
// =====================================================================
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

int main() {
    const int N = 5;
    int so[N] = {12, 45, 7, 89, 23};

    // ================= GHI =================
    cout << "\n=== 1. GHI xuong so.txt ===\n";
    {
        ofstream f("so.txt");                 // mo de GHI -> xoa sach noi dung cu
        if (!f) { cout << "  Khong ghi duoc tep!\n"; return 1; }
        for (int i = 0; i < N; ++i)
            f << so[i] << '\n';               // moi so mot dong
        cout << "  Da ghi " << N << " so.\n";
    }                                          // ra khoi khoi { } -> tep tu dong dong

    // ================= DOC LAI =================
    cout << "\n=== 2. DOC LAI bang >> (kieu don gian) ===\n";
    {
        ifstream f("so.txt");
        if (!f) { cout << "  Chua co tep so.txt\n"; return 1; }
        int x, tong = 0, dem = 0;
        while (f >> x) {                      // >> doc tung so, tu bo qua khoang trang
            cout << "  doc duoc: " << x << '\n';
            tong += x; ++dem;
        }
        cout << "  -> Doc " << dem << " so, TONG = " << tong << '\n';
    }
    ifstream g("so.txt") ; 
    if(!g) cout << " LOI" ; 
   


    // ================= DOC LAI kieu getline =================
    cout << "\n=== 3. DOC LAI bang getline + stoi (linh hoat hon) ===\n";
    {
        ifstream f("so.txt");
        string dong;
        int tong = 0, dem = 0, loi = 0;
        while (getline(f, dong)) {
            if (dong.empty()) continue;        // bo dong trong
            try {
                tong += stoi(dong);            // stoi NEM LOI neu khong phai so
                ++dem;
            } catch (const exception&) {
                ++loi;
            }
        }
        cout << "  Doc " << dem << " so, " << loi << " dong loi, TONG = " << tong << '\n';
    }

    // ================= THU VOI TEP CO RAC =================
    cout << "\n=== 4. Tep co dong rac: >> vs getline+stoi ===\n";
    { ofstream f("so_rac.txt"); f << "12\n45\nabc\n\n89\n"; }

    {
        ifstream f("so_rac.txt");
        int x, tong = 0, dem = 0;
        while (f >> x) { tong += x; ++dem; }
        cout << "  Cach >>          : doc duoc " << dem << " so, tong = " << tong
             << "   <- DUNG NGAY o 'abc', mat so 89\n";
    }
    {
        ifstream f("so_rac.txt");
        string dong; int tong = 0, dem = 0, loi = 0;
        while (getline(f, dong)) {
            if (dong.empty()) continue;
            try { tong += stoi(dong); ++dem; }
            catch (const exception&) { ++loi; }
        }
        cout << "  Cach getline+stoi: doc duoc " << dem << " so, tong = " << tong
             << ", bo qua " << loi << " dong sai   <- DOC HET\n";
    }

    cout << "\n=== GHI NHO ===\n"
         << "  f << x << '\\n';        ghi (dung y het cout)\n"
         << "  while (f >> x)         doc so - nhanh gon nhung DUNG khi gap rac\n"
         << "  while (getline(f, d))  doc dong - cham hon nhung CHIU LOI duoc\n"
         << "  PBL2 luon dung getline vi du lieu that co the co dong hong.\n\n";
    return 0;
}
