#ifndef CHUNGTU_H
#define CHUNGTU_H

#include <string>
#include <vector>

using namespace std ;

//  DongChiTiet : mot dong hang trong chung tu

class DongChiTiet {

    private :
        string maSach ;
        string tenSach ;    // BAN CHEP tai thoi diem lap chung tu
        int    soLuong ;
        double donGia ;     // gia LUC BAN, khong phai gia hien tai

    public :
        DongChiTiet() ;
        DongChiTiet( const string& maSach , const string& tenSach ,
                     int soLuong , double donGia ) ;

        // ----- Getter -----
        string getMaSach()  const { return maSach ; }
        string getTenSach() const { return tenSach ; }
        int    getSoLuong() const { return soLuong ; }
        double getDonGia()  const { return donGia ; }

        // ----- Setter -----
        bool setMaSach( const string& s ) ;
        bool setTenSach( const string& s ) ;
        bool setSoLuong( int sl ) ;
        bool setDonGia( double dg ) ;

        void   congThemSoLuong( int sl ) ;
        double thanhTien() const ;          // soLuong * donGia


        string toChuoi() const ;                    
        bool   fromChuoi( const string& dong ) ;

        void xuatDong() const ;
        static void inTieuDeBang() ;
};



//  ChungTu : lop CHA cua HoaDon va PhieuNhap 
// ===========================================================


class ChungTu {

    protected :
        string ma ;
        string ngay ;                       // "dd/mm/yyyy"
        string nguoiLap ;                   // ma tai khoan nguoi lap
        vector<DongChiTiet> chiTiet ;         

    public :
        ChungTu() ;
        ChungTu( const string& ma , const string& ngay , const string& nguoiLap ) ;
        virtual ~ChungTu() ;                

        // ----- Getter -----
        string getMa()       const { return ma ; }
        string getNgay()     const { return ngay ; }
        string getNguoiLap() const { return nguoiLap ; }

        size_t soDong()      const { return chiTiet.size() ; }      // bao nhieu dong
       
        const vector<DongChiTiet>& cacDong() const { return chiTiet ; }
        // kieu tra ve : chi doc ( tiet kiem bo nho )

        // ----- Setter -----
        bool setMa( const string& s ) ;
        bool setNgay( const string& s ) ;
        bool setNguoiLap( const string& s ) ;

        // ----- Nghiep vu tren danh sach dong -----
        void   themDong( const DongChiTiet& d ) ;   // GOP neu trung ma sach
        bool   xoaDong( size_t viTri ) ;
        void   xoaHetDong() ;
        double tongTienHang() const ;               // cong thanhTien() moi dong
        int    tongSoLuong() const ;

        // Chuong 6 se cho thanh ham THUAN AO:
        // HoaDon tru chiet khau, PhieuNhap thi khong
        
        virtual double thanhToan() const ;

        // ----- Kiem tra ngay -----
        static bool laNgayHopLe( const string& s ) ;    // dd/mm/yyyy, co nam nhuan
        static long soHoaNgay( const string& s ) ;      // "05/09/2026" -> 20260905

        // ----- Tuan tu hoa (Chuong 9) -----
        string chuoiChiTiet() const ;                       // "2|dong1|dong2"
        void   docChiTiet( const vector<string>& p , size_t batDau ) ;

        virtual void inChungTu() const ;
};

#endif // CHUNGTU_H
