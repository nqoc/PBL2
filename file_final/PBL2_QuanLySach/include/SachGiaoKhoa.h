// =====================================================================
//  SachGiaoKhoa.h - Sach giao khoa (giam gia 10% theo chinh sach truong hoc)
// =====================================================================
#ifndef SACHGIAOKHOA_H
#define SACHGIAOKHOA_H

#include "Sach.h"

class SachGiaoKhoa : public Sach {
private:
    std::string monHoc;
    int         khoiLop;      // 1..12

public:
    SachGiaoKhoa();
    SachGiaoKhoa(const std::string& ma, const std::string& ten,
                 const std::string& maTG, const std::string& maTL,
                 const std::string& maNXB, int nam,
                 double giaNhap, double giaBan, int soLuong,
                 const std::string& monHoc, int khoiLop,
                 const std::string& viTriKe = "", const std::string& moTa = "");

    std::string getMonHoc()  const { return monHoc; }
    int         getKhoiLop() const { return khoiLop; }
    void        setMonHoc(const std::string& s) { monHoc = s; }
    void        setKhoiLop(int l);

    // Ghi de cac ham ao / thuan ao
    std::string loaiSach()    const;
    std::string maLoai()      const;
    Sach*       nhanBan()     const;
    double      tiLeGiamGia() const;      // 10%
    std::string moTaThem()    const;
    void        nhap();
    std::string toCSV()       const;
    void        fromCSV(const std::vector<std::string>& p);
};

#endif // SACHGIAOKHOA_H
