#ifndef SACH_H
#define SACH_H

#include<iostream>
#include<string>

using namespace std ; 


class Sach {

    protected :
        string maSach ; 
        string tenSach ; 
        string maTacGia ; 
        string maTheLoai ; 
        string maNXB ; 
        int namXuatBan ;     
        double giaNhap ; 
        double giaBan ; 
        int soLuongTon ; 
        string viTriKe ; 
        string moTa ; 
// ctrl D  : xoa dong bo 
// alt Click : them click
// string s : khi duoc goi thi cap phat rat nang khong giong int a , double b 
        
    public : 
        static const int NAM_MIN ;          
        static const int NAM_MAX ;

        Sach() ;
        Sach(   const string& maSach , 
                const string& tenSach , 
                const string& maTacGia ,
                const string& maTheLoai ,
                const string& maNXB ,
                int namXuatBan ,
                double giaNhap , 
                double giaBan , 
                int soLuongTon ,
                const string& viTriKe ,
                const string& moTa 
        );
        virtual ~Sach() ; 
        // Getter
        string getMaSach()  const  {return maSach ; } 
        string getTenSach() const  {return tenSach ; } 
        string getMaTacGia() const  {return maTacGia ; } 
        string getMaTheLoai()  const {return maTheLoai ;  } 
        string getMaNXB() const  {return maNXB  ; } 
        int getNamXuatBan() const  {return namXuatBan ; }     
        double getGiaNhap() const  {return giaNhap ;  } 
        double getGiaBan()  const {return giaBan ; }   
        int getSoLuongTon() const  {return soLuongTon  ; } 
        string getViTriKe() const  {return viTriKe ;  } 
        string getMoTa()  const {return moTa ; } 
        
        // Setter 
        bool setMaSach( const string& s) ; 
        bool setTenSach( const string& s) ; 
        bool setMaTacGia( const string& s) ; 
        bool setMaTheLoai( const string& s) ; 
        bool setMaNXB( const string& s) ; 
        bool setNamXuatBan( int a ) ;     
        bool setGiaNhap ( double a ) ; 
        bool setGiaBan ( double a) ; 
        bool setSoLuongTon ( int a ) ; 
        bool setViTriKe( const string& s) ; 
        bool setMoTa( const string& s) ;

        bool   nhapThemKho(int sl);        
        bool   banBotKho(int sl);        
        double giaTriTonKho() const;       
        double loiNhuanMotCuon() const;
        

        void nhap();
        void xuatDong() const;
        void xuatChiTiet() const;
        static void inTieuDeBang();
        

        // Nap chong Toan Tu
        bool operator == ( const Sach& s ) const ; 
        bool operator < ( const Sach& s ) const ; 
        Sach& operator += ( int a ) ; 
        friend ostream& operator << ( ostream& os , const Sach& s ) ; 

// ostream la kieu du lieu giong int , double , char 
// friend vi khong co thuoc tinh cout 

        double tiLeGiamGia() const { return 0.0; }
        double giaSauGiam()  const;



};





#endif