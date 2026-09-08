#include<iostream>
#include<sstream>
#include "TienIch.h"

using namespace std ; 


// CAC HAM CHUC NANG 

static bool LaKhoangTrang (char c) {   // ham rieng cho chuan hoa
    return c==' ' || c=='\n' || c=='\t' ; 
}

vector<string> TachChuoi (const string& s , char NganCach) {

        vector<string> chuoi; 
        istringstream is(s) ;  // bien s thanh cin 
        string tmp ; 
        while ( getline(is,tmp,NganCach) ) { // == geline ( cin , string , "\n")
            chuoi.push_back(tmp) ;
        }

        // check truong hop a|b|

        if ( !s.empty() && s[s.size()-1] == NganCach ) { // khac voi sizeof(s) = so byte
            chuoi.push_back("") ; 
        }
        return chuoi ; 
}

string ToLower ( string s ) {
    for ( char& c : s ) {    // string::size_type i = 0 : unsigned int khac int 
        if ( c >= 'A' && c <= 'Z' ) {
            c += 32 ; 
        }
    }
    return s ; 
}

string ChuanHoa ( string s ) {
    string::size_type dau = 0 ; 
    string::size_type cuoi = s.size() ; 
    while(dau < cuoi && LaKhoangTrang(s[dau])) ++dau ; 
    while(cuoi > dau && LaKhoangTrang(s[cuoi-1])) --cuoi ; 
    return s.substr(dau , cuoi-dau) ; // tao string moi , bat dau tu dau lay cuoi-dau phan tu
}

string CatBot( const string& s , string::size_type n ) {
    if(s.size() <= n ) return s ; 
    if(n<=3) return s.substr(0,n) ; 
    return s.substr(0,n-3) +"..." ; 
}
 
bool CheckTuNhap (const string& Ten , const string& TuNhap) {
    if (TuNhap.empty()) return true ; 
    string a = ToLower(Ten)  ; 
    string b = ToLower(TuNhap) ; 
    size_t tmp = a.find(b) ;         // kieu du lieu db size_t
    if ( tmp != string::npos ) return true ;     // gia tri db so sanh voi size_t
    else return false ; 
}


string ChuyenSo(double x ) {
    bool check = x < 0 ; 
    if ( check ) x = - x  ;  // chuyen am sang duong 
    long long n = (long long )(x+0.5) ; // lam tron

    ostringstream os ; 
    os << n ;           // day n vao os 
    string tmp = os.str() ;    // tra ve kieu ban sao

    string res="" ; 
    int cnt = 0 ; 
    for ( int i = (int)tmp.size()-1 ; i >=0 ; i--  ) {
        res = tmp[i] + res ; 
        if( ++cnt%3==0 && i > 0 ) res = "." + res ; 
    }
    if(check) return "-" + res ; 
    return res ; 
}
//1234567 -> 1.234.567


// CAC HAM NHAP XUAT

namespace Nhap {
    
    string Chuoi ( const string& ThongBao , bool ChoPhepRong ) {
        while(true) {
        cout << ThongBao ; 
        string s ; 
        if(!getline(cin,s)) return "" ; 
        s = ChuanHoa(s) ; 
        if( !s.empty() || ChoPhepRong ) return s ; 
        cout << "KHONG HOP LE , VUI LONG NHAP LAI" ; 
        }
    }

    int SoNguyen ( const string& ThongBao , int min , int max ) {
        while(true) {
        cout << ThongBao ; 
        string s ; 
        getline(cin,s) ; 
        if(!cin) return min ; 
        istringstream is(ChuanHoa(s)) ; 
        int check1 = 0 ; 
        char check2 = 'a' ; 
        if ( !(is >> check1) || (is >> check2 ) ) {  // quet tung vi tri 1 , neu gap dau cach thi out
            cout << "Khong phai so nguyen , vui long nhap lai" ; 
            continue;
        } 
        if ( check1 < min || check1 > max ) {
            cout << "Khong hop le , nam trong : " << min << " - " << max ; 
            continue ; 
        }
        return check1 ; 
        }
    }

    double SoThuc ( const string& ThongBao , double min , double max ) {
        while ( true ) {
            cout << ThongBao ; 
            string s ;
            getline(cin , s ) ; 
            if(!cin) return min ; 
            istringstream is(ChuanHoa(s)) ; 
            double check1 = 0 ; 
            char check2 = 'a' ; 
            if ( !( is >> check1 ) || (is>>check2) ) {
                cout << "Khong phai so nguyen , vui long nhap lai" ; 
                continue;
            } 
            if ( check1 < min || check1 > max ) {
                cout << "Khong hop le , nam trong : " << min << " - " << max ; 
                continue ; 
             }
        return check1 ; 
        }
    }


    bool XacNhan ( const string& ThongBao ) {
        while (true) {
        cout << ThongBao << "y/n" ; 
            string c ; 
            getline(cin,c ) ; 
            if ( c == "y" ) return true ;  // dung cin se de lai enter 
            if ( c == "n") return false ; 
            cout << "Vui long nhap lai " << "y : yes , n : no " ; 
        }
    }


}

// ================== DOI CHUOI SANG SO ==================

bool ChuoiSangInt ( const string& s , int& kq ) {
    istringstream is(ChuanHoa(s)) ;
    int v ; char thua ;
    if ( !(is >> v) ) return false ;      // khong doc duoc so nao
    if ( is >> thua ) return false ;      // con ky tu thua phia sau
    kq = v ;
    return true ;
}

bool ChuoiSangLong ( const string& s , long& kq ) {
    istringstream is(ChuanHoa(s)) ;
    long v ; char thua ;
    if ( !(is >> v) ) return false ;
    if ( is >> thua ) return false ;
    kq = v ;
    return true ;
}

bool ChuoiSangDouble ( const string& s , double& kq ) {
    istringstream is(ChuanHoa(s)) ;
    double v ; char thua ;
    if ( !(is >> v) ) return false ;
    if ( is >> thua ) return false ;
    kq = v ;
    return true ;
}
