#ifndef TIENICH_H
#define TIENICH_H

#include <iostream>
#include <string>
#include <vector>

using namespace std ; 

// XU LI CHUOI

vector<string> TachChuoi (const string& s , char NganCach) ; 
string ToLower ( string s ) ; // GK01 = gk01 = Gk01
string ChuanHoa ( const string& s ) ; 
string CatBot ( const string& s , string::size_type n ) ; 

// DO RONG THEO KY TU (khong phai byte)
// Tieng Viet co dau la UTF-8 : 1 ky tu chiem 2-3 byte.
// s.size() va setw() dem BYTE nen bang bi lech cot -> dung cac ham duoi.

size_t DoDaiHienThi ( const string& s ) ;              // dem so KY TU
string CanTrai ( const string& s , size_t n ) ;        // chen space ben phai cho du n ky tu
string CanPhai ( const string& s , size_t n ) ;        // chen space ben trai

// '|' va '#' la ky tu ngan cach khi ghi file -> khong duoc nam trong du lieu
bool CoKyTuNganCach ( const string& s ) ;

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
    bool HetInput () ;      // true khi cin da dong (EOF / Ctrl+Z) -> thoat vong lap nhap

}


#endif 
