// =====================================================================
//  CuaHang.h - Lop TONG HOP toan bo du lieu va nghiep vu cua cua hang
//
//  Day la vi du ro nhat cua quan he KET HOP (aggregation/composition):
//  mot CuaHang "co" nhieu kho du lieu con.
//  Lop nay dong vai tro tang NGHIEP VU, khong lam giao dien.
// =====================================================================
#ifndef CUAHANG_H
#define CUAHANG_H

#include <string>

#include "QuanLySach.h"
#include "KhoDuLieu.h"
#include "DanhMuc.h"
#include "KhachHang.h"
#include "NhaCungCap.h"
#include "TaiKhoan.h"
#include "HoaDon.h"
#include "PhieuNhap.h"
#include "ThongKe.h"

class CuaHang {
private:
    std::string tenCuaHang;
    std::string thuMuc;               // thu muc chua cac tep du lieu
    int         nguongCanhBao;        // ton kho <= nguong -> canh bao

    QuanLySach            khoSach;
    KhoDuLieu<TheLoai>    khoTheLoai;
    KhoDuLieu<TacGia>     khoTacGia;
    KhoDuLieu<NhaXuatBan> khoNXB;
    KhoDuLieu<KhachHang>  khoKhachHang;
    KhoDuLieu<NhaCungCap> khoNhaCungCap;
    KhoDuLieu<TaiKhoan>   khoTaiKhoan;
    KhoDuLieu<HoaDon>     khoHoaDon;
    KhoDuLieu<PhieuNhap>  khoPhieuNhap;

    std::string duongDan(const std::string& tenTep) const;

    // Cam sao chep (vi khoSach so huu con tro)
    CuaHang(const CuaHang&);
    CuaHang& operator=(const CuaHang&);

public:
    CuaHang(const std::string& ten = "NHA SACH BACH KHOA",
            const std::string& thuMucDuLieu = "data");

    // ---------- Truy cap cac kho ----------
    std::string getTen() const { return tenCuaHang; }
    int  getNguongCanhBao() const { return nguongCanhBao; }
    void setNguongCanhBao(int n);

    QuanLySach&            sach()        { return khoSach; }
    KhoDuLieu<TheLoai>&    theLoai()     { return khoTheLoai; }
    KhoDuLieu<TacGia>&     tacGia()      { return khoTacGia; }
    KhoDuLieu<NhaXuatBan>& nxb()         { return khoNXB; }
    KhoDuLieu<KhachHang>&  khachHang()   { return khoKhachHang; }
    KhoDuLieu<NhaCungCap>& nhaCungCap()  { return khoNhaCungCap; }
    KhoDuLieu<TaiKhoan>&   taiKhoan()    { return khoTaiKhoan; }
    KhoDuLieu<HoaDon>&     hoaDon()      { return khoHoaDon; }
    KhoDuLieu<PhieuNhap>&  phieuNhap()   { return khoPhieuNhap; }

    const QuanLySach& sach() const { return khoSach; }

    // ---------- Doi ma -> ten (dung khi hien thi) ----------
    std::string tenTheLoai(const std::string& ma)    const;
    std::string tenTacGia(const std::string& ma)     const;
    std::string tenNXB(const std::string& ma)        const;
    std::string tenKhachHang(const std::string& ma)  const;
    std::string tenNhaCungCap(const std::string& ma) const;

    // ---------- Kiem tra rang buoc toan ven ----------
    void kiemTraMaDanhMucTonTai(const std::string& maTG,
                                const std::string& maTL,
                                const std::string& maNXB) const;
    void xoaTheLoaiAnToan(const std::string& ma);
    void xoaTacGiaAnToan(const std::string& ma);
    void xoaNXBAnToan(const std::string& ma);

    // ---------- Nghiep vu chinh ----------
    std::string sinhMaHoaDon()   const;
    std::string sinhMaPhieuNhap() const;

    // Kiem tra ton kho -> tru kho -> cong diem khach -> luu hoa don
    void ghiNhanHoaDon(HoaDon& hd);
    // Cong ton kho -> cap nhat gia nhap -> luu phieu nhap
    void ghiNhanPhieuNhap(PhieuNhap& pn);

    // ---------- Tep du lieu ----------
    void napTatCa();
    void luuTatCa() const;
    void saoLuu() const;
    void taoDuLieuMau();
    void taoTaiKhoanMacDinh();
    int  tongSoDongLoi() const;

    // ---------- Thong ke (cai dat trong ThongKe.cpp) ----------
    double doanhThuTheoNgay(const std::string& ngay) const;
    double doanhThuTheoThang(const std::string& thang) const;
    double doanhThuTheoKhoang(const std::string& tu, const std::string& den,
                              int& soHoaDon) const;
    double tongDoanhThu() const;
    double tongChiNhapHang() const;

    Vector<MucDoanhThu> bangDoanhThuTheoNgay()  const;
    Vector<MucDoanhThu> bangDoanhThuTheoThang() const;
    Vector<MucBanChay>  bangSachBanChay()       const;
    Vector<MucBanChay>  bangTheLoaiUaChuong()   const;

    Vector<HoaDon>    hoaDonTheoNgay(const std::string& ngay) const;
    Vector<HoaDon>    hoaDonTheoKhach(const std::string& maKH) const;
    Vector<PhieuNhap> phieuNhapTheoNgay(const std::string& ngay) const;
    Vector<PhieuNhap> phieuNhapTheoNCC(const std::string& maNCC) const;

    void xuatBaoCaoRaTep(const std::string& tenTep) const;
};

#endif // CUAHANG_H
