// =====================================================================
//  QuanLySach.h - Quan ly danh sach cac dau sach (da hinh: Sach*)
//
//  Diem quan trong:
//   * Danh sach LUON duoc sap xep tang theo ma sach
//     -> co the tim kiem nhi phan O(log n)
//   * Ngoai ra con co bang bam (ma sach -> vi tri) -> tim kiem O(1)
//   * Lop nay SO HUU cac con tro Sach* nen phai tu giai phong bo nho
// =====================================================================
#ifndef QUANLYSACH_H
#define QUANLYSACH_H

#include <string>
#include "Sach.h"
#include "Vector.h"
#include "BangBam.h"

class QuanLySach {
public:
    // Tieu chi sap xep
    enum TieuChi { THEO_MA = 1, THEO_TEN, THEO_GIA, THEO_TON, THEO_NAM };

private:
    Vector<Sach*>  ds;        // sap xep tang theo ma sach
    BangBam<int>   chiMuc;    // ma sach (chu thuong) -> vi tri trong ds
    int            soDongLoi;

    void xayLaiChiMuc();

    // Cam sao chep de tranh giai phong bo nho hai lan
    QuanLySach(const QuanLySach&);
    QuanLySach& operator=(const QuanLySach&);

public:
    QuanLySach();
    ~QuanLySach();

    // ---------- Truy van ----------
    std::size_t soDauSach() const { return ds.kichThuoc(); }
    bool        rong()      const { return ds.rong(); }
    int         loiDoc()    const { return soDongLoi; }
    const Vector<Sach*>& tatCa() const { return ds; }

    // ---------- Them / xoa / sua ----------
    void them(Sach* s);                       // nem LoiTrungMa neu ma da co
    QuanLySach& operator+=(Sach* s);
    bool xoa(const std::string& ma);
    void xoaHet();

    // ---------- Tim kiem ----------
    Sach* timTheoMa(const std::string& ma) const;          // dung bang bam
    long  timNhiPhanTheoMa(const std::string& ma) const;   // tim kiem nhi phan
    Vector<Sach*> timTheoTen(const std::string& tuKhoa) const;
    Vector<Sach*> timTheoTacGia(const std::string& maTG) const;
    Vector<Sach*> timTheoTheLoai(const std::string& maTL) const;
    Vector<Sach*> timTheoNXB(const std::string& maNXB) const;

    // ---------- Loc ----------
    Vector<Sach*> locTheoKhoangGia(double tu, double den) const;
    Vector<Sach*> locTheoTinhTrang(bool conHang) const;
    Vector<Sach*> locTheoLoai(const std::string& maLoai) const;

    // ---------- Sap xep (tra ve BAN SAO danh sach con tro) ----------
    Vector<Sach*> sapXepTheo(TieuChi tc, bool tangDan) const;

    // ---------- Thong ke ----------
    double        tongGiaTriTonKho() const;
    int           tongSoCuonTon()    const;
    std::size_t   demTheoLoai(const std::string& maLoai) const;
    Vector<Sach*> sachSapHet(int nguong) const;
    Sach*         sachDatNhat() const;
    std::size_t   demThamChieuTacGia(const std::string& maTG)  const;
    std::size_t   demThamChieuTheLoai(const std::string& maTL) const;
    std::size_t   demThamChieuNXB(const std::string& maNXB)    const;

    // ---------- Sinh ma tu dong: GK001, VH002, TN003... ----------
    std::string sinhMa(const std::string& maLoai) const;

    // ---------- File ----------
    void luuFile(const std::string& tenTep) const;
    bool docFile(const std::string& tenTep);

    // ---------- Thong tin bang bam (danh gia thuat toan) ----------
    std::size_t soOBangBam()     const { return chiMuc.soO(); }
    std::size_t chuoiBamDaiNhat() const { return chiMuc.chuoiDaiNhat(); }
};

// Cac ham so sanh dung cho thuat toan sap xep
bool sxTheoMaTang(Sach* a, Sach* b);
bool sxTheoMaGiam(Sach* a, Sach* b);
bool sxTheoTenTang(Sach* a, Sach* b);
bool sxTheoTenGiam(Sach* a, Sach* b);
bool sxTheoGiaTang(Sach* a, Sach* b);
bool sxTheoGiaGiam(Sach* a, Sach* b);
bool sxTheoTonTang(Sach* a, Sach* b);
bool sxTheoTonGiam(Sach* a, Sach* b);
bool sxTheoNamTang(Sach* a, Sach* b);
bool sxTheoNamGiam(Sach* a, Sach* b);

#endif // QUANLYSACH_H
