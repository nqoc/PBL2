#ifndef NGUOI_H
#define NGUOI_H

#include<iostream>
#include<string>


using namespace std ; 


class Nguoi {

    protected : 
    string ma ; 
    string hoTen ; 
    string soDienThoai ; 
    string diaChi ; 
    string email ; 

    public :
    
    // Khoi tao
    Nguoi() ; 
    Nguoi(  const string& ma ,const string& hoTen ,const string& soDienThoai ,const string& diaChi , const string& email );
    virtual ~Nguoi() ;   

    // Getter 
    string getMa() const {return ma ; }  
    string getHoTen() const {return hoTen ; }
    string getSoDienThoai() const { return soDienThoai ;}
    string getDiaChi() const { return diaChi ;}
    string getEmail() const { return email ;}

    // Setter 
    bool setMa(const string& s )   ;
    bool setHoTen ( const string& s ) ;
    bool setSoDienThoai ( const string& s ) ;
    bool setDiaChi ( const string& s ) ;
    bool setEmail ( const string& s ) ;

    
    // check email 
    static bool checkEmail ( const string& s ) ;
    static bool checkSoDienThoai ( const string& s ) ; 

};










#endif