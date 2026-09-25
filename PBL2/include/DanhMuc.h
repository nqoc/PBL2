#ifndef DANHMUC_H
#define DANHMUC_H

#include<iostream> 
#include<string>
#include "Vector.h"

using namespace std ; 



class TheLoai {

    protected :

        string ma ; 
        string ten ; 
        string moTa ; 

    public : 

        TheLoai() ; 
        TheLoai( const string& ma , const string& ten ,  const string& moTa) ; 
        // string ma : ton bo nho 
        // string& ma : khong truyen dc "abcccc" , khong lam thay doi gia tri goc
        // const string& ma : toi uu : chi doc khong lam thay doi gia tri goc

        string getMa()      const   { return ma ;}  
        string getTen()     const   {return ten ; } 
        string getMoTa()    const   { return moTa ; }

        bool setMoTa   (const string& moTa) ;
        bool setMa     ( const string& ma ) ;
        bool setTen    ( const string& ten) ;

        void nhap() ; 
        void xuatDong() const ; 
        static void inBang() ; 

};

class TacGia {
    string ma;
    string ten;
    string moTa;
public:
    TacGia();
    TacGia(const string&, const string&, const string& = "");
    string getMa() const { return ma; }
    string getTen() const { return ten; }
    string getMoTa() const { return moTa; }
    bool setMa(const string&);
    bool setTen(const string&);
    bool setMoTa(const string&);
    string toChuoi() const;
    bool fromChuoi(const string&);
};

class NhaXuatBan {
    string ma;
    string ten;
    string diaChi;
    string soDienThoai;
    string email;
public:
    NhaXuatBan();
    NhaXuatBan(const string&, const string&, const string&, const string&, const string&);
    string getMa() const { return ma; }
    string getTen() const { return ten; }
    string getDiaChi() const { return diaChi; }
    string getSoDienThoai() const { return soDienThoai; }
    string getEmail() const { return email; }
    bool setMa(const string&);
    bool setTen(const string&);
    bool setDiaChi(const string&);
    bool setSoDienThoai(const string&);
    bool setEmail(const string&);
    string toChuoi() const;
    bool fromChuoi(const string&);
};

class NhaCungCap {
    string ma, ten, soDienThoai, diaChi, email, maSoThue;
public:
    NhaCungCap();
    NhaCungCap(const string&, const string&, const string&, const string&, const string&, const string&);
    string getMa() const { return ma; }
    string getTen() const { return ten; }
    string getSoDienThoai() const { return soDienThoai; }
    string getDiaChi() const { return diaChi; }
    string getEmail() const { return email; }
    string getMaSoThue() const { return maSoThue; }
    bool setMa(const string&);
    bool setTen(const string&);
    bool setSoDienThoai(const string&);
    bool setDiaChi(const string&);
    bool setEmail(const string&);
    bool setMaSoThue(const string&);
    string toChuoi() const;
    bool fromChuoi(const string&);
};

class KhachHang {
    string ma, hoTen, soDienThoai, diaChi;
    int diem;
public:
    KhachHang();
    KhachHang(const string&, const string&, const string&, const string&, int);
    string getMa() const { return ma; }
    string getHoTen() const { return hoTen; }
    string getSoDienThoai() const { return soDienThoai; }
    string getDiaChi() const { return diaChi; }
    int getDiem() const { return diem; }
    bool setMa(const string&);
    bool setHoTen(const string&);
    bool setSoDienThoai(const string&);
    bool setDiaChi(const string&);
    bool setDiem(int);
    string toChuoi() const;
    bool fromChuoi(const string&);
};

Vector<TacGia> docTacGia(const string&);
Vector<TheLoai> docTheLoai(const string&);
Vector<NhaXuatBan> docNhaXuatBan(const string&);
Vector<NhaCungCap> docNhaCungCap(const string&);
Vector<KhachHang> docKhachHang(const string&);

#endif