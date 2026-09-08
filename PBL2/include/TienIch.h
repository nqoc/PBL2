#ifndef TIENICH_H
#define TIENICH_H

#include <iostream>
#include <string>
#include <vector>

using namespace std ; 

// XU LI CHUOI

vector<string> TachChuoi (const string& s , char NganCach) ; 
string ToLower ( string s ) ; // GK01 = gk01 = Gk01
string ChuanHoa ( const string s ) ; 
string CatBot ( const string& s , string::size_type n ) ; 
bool CheckTuNhap (const string& Ten , const string& TuNhap) ;
string ChuyenSo ( double x ) ; 


// DOI CHUOI SANG SO  (thay cho atoi/atof/atol cua <cstdlib>)
// Tra ve false neu chuoi khong phai so -> phan biet duoc "abc" voi "0".
// Ket qua di ra qua tham so 'kq'.

bool ChuoiSangInt    ( const string& s , int& kq ) ;
bool ChuoiSangLong   ( const string& s , long& kq ) ;
bool ChuoiSangDouble ( const string& s , double& kq ) ;


// XU LI NHAP XUAT 

namespace Nhap {

    string Chuoi ( const string& ThongBao , bool ChoPhepRong = false );
    int SoNguyen ( const string& ThongBao , int min , int max ) ; 
    double SoThuc ( const string& ThongBao , double min , double max ) ; 
    bool XacNhan ( const string& ThongBao ) ; 

}


#endif 
