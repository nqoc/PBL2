// =====================================================================
//  UngDung.h - Tang GIAO DIEN dong lenh (console) cua chuong trinh
//
//  Kien truc 3 tang:
//      UngDung   (giao dien)  ->  CuaHang (nghiep vu)  ->  cac lop du lieu
//  Tang giao dien KHONG chua logic nghiep vu, chi hoi - hien thi.
// =====================================================================
#ifndef UNGDUNG_H
#define UNGDUNG_H

#include <string>
#include "CuaHang.h"

class UngDung {
private:
    CuaHang     cuaHang;
    std::string maNguoiDung;    // ten dang nhap cua nguoi dung hien tai
    bool        dangChay;

    // Luon tra cuu lai tai khoan theo ten dang nhap:
    // KHONG luu con tro lau dai vi Vector co the cap phat lai bo nho
    TaiKhoan* nguoiDung();

    // ---------- Ho tro chung ----------
    void inLogo() const;
    void inThanhTrangThai();
    bool laAdmin();
    void batBuocAdmin();                       // nem LoiPhanQuyen neu khong phai admin
    bool dangNhap();
    void dangXuat();
    int  chonMuc(const std::string& nhac, int nhoNhat, int lonNhat) const;

    // ---------- Menu ----------
    void menuChinh();
    void menuQuanLySach();
    void menuDanhMuc();
    void menuNhaCungCap();
    void menuKhachHang();
    void menuNhapKho();
    void menuBanHang();
    void menuTimKiemSapXep();
    void menuThongKe();
    void menuDuLieu();
    void menuTaiKhoan();

    // ---------- Nhom chuc nang: SACH  (UngDung_Sach.cpp) ----------
    void inBangSach(const Vector<Sach*>& ds);
    void inMotSach(const Sach* s);
    void xemTatCaSach();
    void xemChiTietSach();
    void themSach();
    void suaSach();
    void xoaSach();
    void capNhatTonVaGia();
    Sach* hoiChonSach(const std::string& nhac);

    // ---------- Nhom chuc nang: DANH MUC  (UngDung_DanhMuc.cpp) ----------
    void quanLyTheLoai();
    void quanLyTacGia();
    void quanLyNhaXuatBan();
    void inBangTheLoai();
    void inBangTacGia();
    void inBangNXB();

    // ---------- Nhom chuc nang: DOI TAC  (UngDung_DoiTac.cpp) ----------
    void inBangNhaCungCap();
    void themNhaCungCap();
    void suaNhaCungCap();
    void xoaNhaCungCap();
    void timNhaCungCap();
    void lichSuNhapTheoNCC();

    void inBangKhachHang();
    void themKhachHang();
    void suaKhachHang();
    void xoaKhachHang();
    void timKhachHang();
    void lichSuMuaHang();

    // ---------- Nhom chuc nang: GIAO DICH  (UngDung_GiaoDich.cpp) ----------
    void lapPhieuNhap();
    void xemDanhSachPhieuNhap();
    void traCuuPhieuNhapTheoNgay();
    void xemChiTietPhieuNhap();
    void lapHoaDon();
    void xemDanhSachHoaDon();
    void traCuuHoaDonTheoNgay();
    void traCuuHoaDonTheoKhach();
    void inLaiHoaDon();

    // ---------- Nhom chuc nang: TIM KIEM & THONG KE  (UngDung_ThongKe.cpp) ----------
    void timTheoMaBangBam();
    void timTheoMaNhiPhan();
    void timTheoTenSach();
    void timTheoTacGiaSach();
    void timTheoTheLoaiSach();
    void timTheoNXBSach();
    void locTheoKhoangGia();
    void locTheoTinhTrang();
    void sapXepDanhSach();
    void soSanhHieuNangTimKiem();

    void thongKeTonKho();
    void thongKeDoanhThuNgay();
    void thongKeDoanhThuThang();
    void thongKeDoanhThuKhoang();
    void thongKeSachBanChay();
    void thongKeTheLoai();
    void canhBaoSapHet();
    void xuatBaoCao();

public:
    UngDung();
    ~UngDung();
    void chay();      // vong lap chinh cua chuong trinh
};

#endif // UNGDUNG_H
