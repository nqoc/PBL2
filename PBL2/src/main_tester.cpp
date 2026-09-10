#include<iostream>
#include "TaiKhoan.h"
#include"TienIch.h"

using namespace std ; 

void show_Chuoi ( vector<string> s ) {
    for ( string::size_type i = 0 ; i < s.size() ; i++ ) {
        cout << s[i] << endl; 
    }
}

int main () {


    // check tach chuoi :
    string s = "3|J.K. Rowling|Harry Potter" ;
    cout<<"===Tach Chuoi==="<<endl ; 
    show_Chuoi(TachChuoi(s,'|'))  ; 
    cout<<endl;

    
    // check tim kiem tu nhap :
    if (CheckTuNhap("Giai Tich Cao Cap" , "giai tich")) cout << " Found " <<endl ;  // found
    else cout << "Not Found" <<endl;
    if (CheckTuNhap("Giai Tich Cao Cap" , "vat ly")) cout << " Found " <<endl ;  // not found
    else cout << "Not Found" <<endl;




    // check in ra so : 10000 -> 10.000 .
    cout << ChuyenSo(10000000000) << endl ;

    vector<TaiKhoan> taiKhoan = docTaiKhoan("data/users.txt");
    cout << "Da doc " << taiKhoan.size() << " tai khoan.\n";
    for (const TaiKhoan& tk : taiKhoan)
        cout << tk.getId() << " | " << tk.getTenDangNhap()
             << " | " << tk.getVaiTro() << "\n";
    
    
    // check ham nhap 
    string ten = Nhap::Chuoi(" Nhap Ten Mot Cuon Sach ") ; 
    cout << ten ; 


}