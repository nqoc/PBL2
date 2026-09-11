// =====================================================================
//  ChungTu.h - Cay ke thua thu ba: chung tu cua cua hang
//      ChungTu (truu tuong)  ->  HoaDon (ban) / PhieuNhap (nhap)
//
//  Moi chung tu la mot vi du cua quan he KET HOP (composition):
//  ChungTu "chua" nhieu DongChiTiet.
// =====================================================================
#ifndef CHUNGTU_H
#define CHUNGTU_H

#include <string>
#include <vector>
#include "Vector.h"

// ---------------------------------------------------------------------
//  Mot dong chi tiet: mot dau sach trong hoa don / phieu nhap
// ---------------------------------------------------------------------
class DongChiTiet {
private:
    std::string maSach;
    std::string tenSach;     // luu lai ten tai thoi diem lap chung tu
    int         soLuong;
    double      donGia;

public:
    DongChiTiet();
    DongChiTiet(const std::string& maSach, const std::string& tenSach,
                int soLuong, double donGia);

    std::string getMaSach()  const { return maSach; }
    std::string getTenSach() const { return tenSach; }
    int         getSoLuong() const { return soLuong; }
    double      getDonGia()  const { return donGia; }

    void setSoLuong(int sl);
    void setDonGia(double g);

    double thanhTien() const { return soLuong * donGia; }

    // Trong 1 dong file, cac truong con cach nhau bang ky tu '#'
    std::string toChuoi() const;
    void        fromChuoi(const std::string& s);
};

// ---------------------------------------------------------------------
//  Lop co so truu tuong cho moi chung tu
// ---------------------------------------------------------------------
class ChungTu {
protected:
    std::string          ma;
    std::string          ngayLap;      // dd/mm/yyyy
    std::string          nguoiLap;     // ten dang nhap cua nhan vien
    Vector<DongChiTiet>  chiTiet;

    std::string chuoiChiTiet() const;                       // "n|dong1|dong2..."
    void        docChiTiet(const std::vector<std::string>& p, std::size_t batDau);

public:
    ChungTu();
    ChungTu(const std::string& ma, const std::string& ngay,
            const std::string& nguoiLap);
    virtual ~ChungTu();

    std::string getMa()       const { return ma; }
    std::string getTen()      const { return ngayLap; }   // dung cho KhoDuLieu
    std::string getNgay()     const { return ngayLap; }
    std::string getNguoiLap() const { return nguoiLap; }

    void setMa(const std::string& s)       { ma = s; }
    void setNgay(const std::string& s);
    void setNguoiLap(const std::string& s) { nguoiLap = s; }

    // Lam viec voi cac dong chi tiet
    std::size_t soDong() const { return chiTiet.kichThuoc(); }
    const Vector<DongChiTiet>& cacDong() const { return chiTiet; }
    void themDong(const DongChiTiet& d);      // gop neu trung ma sach
    bool xoaDong(std::size_t i);
    void xoaHetDong() { chiTiet.xoaHet(); }

    // Tong tien hang (chua chiet khau)
    double tongTienHang() const;
    int    tongSoLuong()  const;

    // ---------- Ham thuan ao ----------
    virtual std::string loaiChungTu() const = 0;   // "HOA DON" / "PHIEU NHAP"
    virtual double      thanhToan()   const = 0;   // so tien phai tra/thu

    // ---------- Ham ao ----------
    virtual void        inChungTu()   const;
    virtual void        xuatDong()    const;
    virtual std::string toCSV()       const;
    virtual void        fromCSV(const std::vector<std::string>& p);
};

#endif // CHUNGTU_H
