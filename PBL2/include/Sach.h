#ifndef SACH_H
#define SACH_H

#include<iostream>
#include<string>
#include "Vector.h"
#include<memory>

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
        string ngayTao ;
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
                const string& moTa ,
                const string& ngayTao
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
        string getNgayTao() const { return ngayTao ; }
        
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
        bool setNgayTao( const string& s) ;

        bool   nhapThemKho(int sl);        
        bool   banBotKho(int sl);        
        double giaTriTonKho() const;       
        double loiNhuanMotCuon() const;
        

        // virtual : de lop con ( SachGiamGia , SachNhapKhau ... ) ghi de duoc.
        // Goi qua con tro Sach* se chay dung ban cua lop con.
        virtual void nhap();
        virtual void xuatDong() const;
        virtual void xuatChiTiet() const;
        static void inTieuDeBang();     // static thi KHONG virtual duoc
        

        // Nap chong Toan Tu
        bool operator == ( const Sach& s ) const ; 
        bool operator < ( const Sach& s ) const ; 
        Sach& operator += ( int a ) ; 
        friend ostream& operator << ( ostream& os , const Sach& s ) ; 

// ostream la kieu du lieu giong int , double , char 
// friend vi khong co thuoc tinh cout 

        // PHAI la virtual : giaSauGiam() goi tiLeGiamGia() , va operator<
        // lai goi giaSauGiam(). Neu khong virtual thi khi upcast ve Sach*
        // ban cua LOP CHA (0.0) van duoc goi -> lop con giam gia bi bo qua.
                virtual string loaiSach() const = 0;
                virtual double tienGiamGia() const = 0;
                virtual string nhaBan() const = 0;
                virtual double tiLeGiamGia() const { return tienGiamGia(); }
                double giaSauGiam() const;
                virtual string toCSV() const;
                virtual bool fromCSV(const string& dong);
};

class SachGiaoKhoa : public Sach {
        string monHoc;
        string capHoc;
        double phanTramGiam;
public:
        SachGiaoKhoa();
        SachGiaoKhoa(const string&, const string&, const string&, const string&, const string&, int,
                                 double, double, int, const string&, const string&, const string&,
                                 const string& = "", const string& = "", double = 0.0);
        string loaiSach() const override { return "Giao khoa"; }
        double tienGiamGia() const override { return phanTramGiam / 100.0; }
        string nhaBan() const override { return "Nha sach"; }
        string getMonHoc() const { return monHoc; }
        string getCapHoc() const { return capHoc; }
        double getPhanTramGiam() const { return phanTramGiam; }
        bool setMonHoc(const string&);
        bool setCapHoc(const string&);
        bool setPhanTramGiam(double);
        string toCSV() const override;
        bool fromCSV(const string&) override;
};

class SachVanHoc : public Sach {
        string phongCach;
        double phanTramGiam;
public:
        SachVanHoc();
        SachVanHoc(const string&, const string&, const string&, const string&, const string&, int,
                           double, double, int, const string&, const string&, const string&,
                           const string& = "", double = 0.0);
        string loaiSach() const override { return "Van hoc"; }
        double tienGiamGia() const override { return phanTramGiam / 100.0; }
        string nhaBan() const override { return "Nha sach"; }
        string getPhongCach() const { return phongCach; }
        double getPhanTramGiam() const { return phanTramGiam; }
        bool setPhanTramGiam(double);
        string toCSV() const override;
        bool fromCSV(const string&) override;
};

class SachThieuNhi : public Sach {
        int doTuoi;
        double phanTramGiam;
public:
        SachThieuNhi();
        SachThieuNhi(const string&, const string&, const string&, const string&, const string&, int,
                                 double, double, int, const string&, const string&, const string&,
                                 int = 0, double = 0.0);
        string loaiSach() const override { return "Thieu nhi"; }
        double tienGiamGia() const override { return phanTramGiam / 100.0; }
        string nhaBan() const override { return "Nha sach"; }
        int getDoTuoi() const { return doTuoi; }
        double getPhanTramGiam() const { return phanTramGiam; }
        bool setPhanTramGiam(double);
        string toCSV() const override;
        bool fromCSV(const string&) override;
};

Vector<shared_ptr<Sach> > docSach(const string& tenFile);








#endif