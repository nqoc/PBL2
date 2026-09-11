// =====================================================================
//  SachVanHoc.h - Sach van hoc (giam gia 5%)
// =====================================================================
#ifndef SACHVANHOC_H
#define SACHVANHOC_H

#include "Sach.h"

class SachVanHoc : public Sach {
private:
    std::string theLoaiVanHoc;   // tieu thuyet, tho, truyen ngan, tan van...
    std::string dichGia;         // "Khong" neu la tac pham trong nuoc

public:
    SachVanHoc();
    SachVanHoc(const std::string& ma, const std::string& ten,
               const std::string& maTG, const std::string& maTL,
               const std::string& maNXB, int nam,
               double giaNhap, double giaBan, int soLuong,
               const std::string& theLoaiVH, const std::string& dichGia,
               const std::string& viTriKe = "", const std::string& moTa = "");

    std::string getTheLoaiVanHoc() const { return theLoaiVanHoc; }
    std::string getDichGia()       const { return dichGia; }
    void        setTheLoaiVanHoc(const std::string& s) { theLoaiVanHoc = s; }
    void        setDichGia(const std::string& s)       { dichGia = s; }
    bool        laSachDich() const;

    std::string loaiSach()    const;
    std::string maLoai()      const;
    Sach*       nhanBan()     const;
    double      tiLeGiamGia() const;      // 5%
    std::string moTaThem()    const;
    void        nhap();
    std::string toCSV()       const;
    void        fromCSV(const std::vector<std::string>& p);
};

#endif // SACHVANHOC_H
