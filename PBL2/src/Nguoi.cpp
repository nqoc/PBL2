#include<iostream>
#include<string>
#include"Nguoi.h"
#include"TienIch.h"


using namespace std ; 

Nguoi::Nguoi() :  ma(""), hoTen(""), soDienThoai(""), diaChi(""), email("") {}

Nguoi::Nguoi(const string& ma_, const string& hoTen_, const string& sdt_,
             const string& diaChi_, const string& email_)
    : ma(""), hoTen(""), soDienThoai(""), diaChi(""), email("")
{
    setMa(ma_);
    setHoTen(hoTen_);
    setSoDienThoai(sdt_);
    setDiaChi(diaChi_);
    setEmail(email_);
}

Nguoi::~Nguoi() {}


bool Nguoi::setMa(const string& s )   {
    string t = ChuanHoa(s) ; 
    if( t.empty() ) return false ; 
    this->ma = t ; 
    return true ; 
}

bool Nguoi::setHoTen ( const string& s ) {
    string t = ChuanHoa(s) ;
    if(t.empty()) return false ; 
    this->hoTen = t ; 
    return true ; 
}

bool Nguoi::setDiaChi ( const string& s ) {
    diaChi = ChuanHoa(s) ;      // dia chi co the rong 
    return true ; 
}

// check mail 
bool Nguoi::checkEmail ( const string& s ) {
    //  1.check @
    size_t pos1 = s.find( '@' ) ;      // tim vi tri dau tien co @
    if ( pos1 == string::npos ) return false ; 
    if ( pos1 == 0 ) return false ; 
    if ( pos1+1 == s.size() ) return false ; 
    if ( s.find( '@' , pos1 + 1 ) != string :: npos ) return false ; // tim tu vi tri @ + 1
   
    //  2.check dau cham '.'
    size_t pos2 = s.find( '.' , pos1 ) ; 
    if ( pos2 == string :: npos ) return false ; 
    if ( pos2 == pos1 + 1 ) return false ; 
    if ( pos2 + 1 == s.size()) return false ;

    return true ; 
}


bool Nguoi::setEmail ( const string& s ) {
    string t = ChuanHoa(ToLower(s)) ; 
    if(checkEmail(t)) {
        this->email = t ; 
        return true ; 
    }
    return false ; 
}

// check sdt : 0932abc4242

bool Nguoi::checkSoDienThoai ( const string& s ) {
    if ( s.size() < 9 && s.size() > 11 ) return false ; 
    for ( size_t i = 0 ; i < s.size() ; i ++ ) {
        if ( s[i] < 48 || s[i] > 57 ) return false ;
    }
    return true ; 
}

bool Nguoi::setSoDienThoai ( const string& s ) {
    string t = ChuanHoa(s) ; 
    if ( checkSoDienThoai(t) ) {
        this->soDienThoai = t ; 
        return true ; 
    }
    return false ; 
}

