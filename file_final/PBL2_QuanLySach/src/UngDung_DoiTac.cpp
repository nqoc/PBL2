// =====================================================================
//  UngDung_DoiTac.cpp - Quan ly NHA CUNG CAP va KHACH HANG
// =====================================================================
#include "UngDung.h"
#include "TienIch.h"
#include "NgoaiLe.h"

#include <iostream>
#include <iomanip>

using namespace std;

// =====================================================================
//                          NHA CUNG CAP
// =====================================================================
void UngDung::inBangNhaCungCap() {
    Man::tieuDe("DANH SACH NHA CUNG CAP");
    Vector<NhaCungCap>& ds = cuaHang.nhaCungCap().duLieu();
    if (ds.rong()) { cout << "\n  (Chua co nha cung cap nao)\n"; return; }

    Man::duong('-', 95);
    cout << left << setw(10) << "MA"
         << left << setw(28) << "TEN CONG TY"
         << left << setw(13) << "DIEN THOAI"
         << left << setw(26) << "DIA CHI"
         << left << setw(16) << "MA SO THUE" << '\n';
    Man::duong('-', 95);
    for (size_t i = 0; i < ds.kichThuoc(); ++i) {
        ds[i].xuatDong();
        cout << '\n';
    }
    Man::duong('-', 95);
    cout << "  Tong: " << ds.kichThuoc() << " nha cung cap\n";
}

void UngDung::themNhaCungCap() {
    Man::tieuDe("THEM NHA CUNG CAP");
    NhaCungCap ncc;
    ncc.nhap();
    ncc.setMa(cuaHang.nhaCungCap().sinhMa("NCC"));
    cuaHang.nhaCungCap().them(ncc);
    cout << "\n  >> Da them nha cung cap, ma tu sinh: " << ncc.getMa() << '\n';
}

void UngDung::suaNhaCungCap() {
    Man::tieuDe("SUA THONG TIN NHA CUNG CAP");
    string ma = Nhap::chuoi("  Nhap ma nha cung cap: ");
    NhaCungCap* p = cuaHang.nhaCungCap().timTheoMa(ma);
    if (p == 0) throw LoiKhongTimThay("Nha cung cap " + ma);

    p->xuatChiTiet();
    cout << "\n  --- Nhap lai thong tin ---\n";
    string maCu = p->getMa();
    p->nhap();
    p->setMa(maCu);
    cout << "\n  >> Da cap nhat nha cung cap " << maCu << '\n';
}

void UngDung::xoaNhaCungCap() {
    Man::tieuDe("XOA NHA CUNG CAP");
    string ma = Nhap::chuoi("  Nhap ma nha cung cap can xoa: ");
    NhaCungCap* p = cuaHang.nhaCungCap().timTheoMa(ma);
    if (p == 0) throw LoiKhongTimThay("Nha cung cap " + ma);
    p->xuatChiTiet();

    // Rang buoc toan ven: khong xoa NCC da co phieu nhap
    Vector<PhieuNhap> pn = cuaHang.phieuNhapTheoNCC(ma);
    if (!pn.rong()) {
        cout << "\n  !! Nha cung cap nay co " << pn.kichThuoc()
             << " phieu nhap trong lich su.\n";
        throw LoiRangBuoc("Khong the xoa nha cung cap da phat sinh giao dich.");
    }
    if (!Nhap::xacNhan("  Xac nhan xoa?")) { cout << "  >> Da huy.\n"; return; }
    cuaHang.nhaCungCap().xoa(ma);
    cout << "\n  >> Da xoa nha cung cap " << ma << '\n';
}

void UngDung::timNhaCungCap() {
    Man::tieuDe("TIM NHA CUNG CAP THEO TEN");
    string tk = Nhap::chuoi("  Tu khoa: ");
    Vector<NhaCungCap> kq = cuaHang.nhaCungCap().timTheoTen(tk);
    if (kq.rong()) { cout << "\n  (Khong tim thay)\n"; return; }
    Man::duong('-', 95);
    for (size_t i = 0; i < kq.kichThuoc(); ++i) {
        kq[i].xuatDong();
        cout << '\n';
    }
    Man::duong('-', 95);
    cout << "  Tim thay " << kq.kichThuoc() << " ket qua.\n";
}

void UngDung::lichSuNhapTheoNCC() {
    Man::tieuDe("LICH SU NHAP HANG THEO NHA CUNG CAP");
    string ma = Nhap::chuoi("  Nhap ma nha cung cap: ");
    if (!cuaHang.nhaCungCap().coMa(ma))
        throw LoiKhongTimThay("Nha cung cap " + ma);

    Vector<PhieuNhap> ds = cuaHang.phieuNhapTheoNCC(ma);
    cout << "\n  Nha cung cap: " << ma << " - " << cuaHang.tenNhaCungCap(ma) << '\n';
    if (ds.rong()) { cout << "\n  (Chua co phieu nhap nao)\n"; return; }

    PhieuNhap::inTieuDeBang();
    double tong = 0;
    for (size_t i = 0; i < ds.kichThuoc(); ++i) {
        ds[i].xuatDong();
        cout << '\n';
        tong += ds[i].thanhToan();
    }
    Man::duong('-', 88);
    cout << "  Tong so phieu: " << ds.kichThuoc()
         << "   |   Tong tien da nhap: " << dinhDangTien(tong) << " VND\n";
}

// =====================================================================
//                            KHACH HANG
// =====================================================================
void UngDung::inBangKhachHang() {
    Man::tieuDe("DANH SACH KHACH HANG");
    Vector<KhachHang>& ds = cuaHang.khachHang().duLieu();
    if (ds.rong()) { cout << "\n  (Chua co khach hang nao)\n"; return; }

    Man::duong('-', 93);
    cout << left  << setw(10) << "MA"
         << left  << setw(24) << "HO TEN"
         << left  << setw(13) << "DIEN THOAI"
         << left  << setw(24) << "DIA CHI"
         << right << setw(8)  << "DIEM"
         << "   " << left << setw(11) << "CAP" << '\n';
    Man::duong('-', 93);
    for (size_t i = 0; i < ds.kichThuoc(); ++i) {
        ds[i].xuatDong();
        cout << '\n';
    }
    Man::duong('-', 93);
    cout << "  Tong: " << ds.kichThuoc() << " khach hang\n";
}

void UngDung::themKhachHang() {
    Man::tieuDe("THEM KHACH HANG");
    KhachHang kh;
    kh.nhap();
    kh.setMa(cuaHang.khachHang().sinhMa("KH"));
    cuaHang.khachHang().them(kh);
    cout << "\n  >> Da them khach hang, ma tu sinh: " << kh.getMa() << '\n';
}

void UngDung::suaKhachHang() {
    Man::tieuDe("SUA THONG TIN KHACH HANG");
    string ma = Nhap::chuoi("  Nhap ma khach hang: ");
    KhachHang* p = cuaHang.khachHang().timTheoMa(ma);
    if (p == 0) throw LoiKhongTimThay("Khach hang " + ma);

    p->xuatChiTiet();
    cout << "\n    1. Nhap lai toan bo thong tin\n";
    cout << "    2. Chinh sua diem tich luy   [admin]\n";
    cout << "    0. Huy\n";
    int c = Nhap::soNguyen("  Chon: ", 0, 2);
    if (c == 0) { cout << "  >> Da huy.\n"; return; }

    if (c == 1) {
        string maCu = p->getMa();
        int    diem = p->getDiem();
        p->nhap();
        p->setMa(maCu);
        p->setDiem(diem);
    } else {
        batBuocAdmin();
        p->setDiem(Nhap::soNguyen("  Diem tich luy moi: ", 0, 1000000));
    }
    cout << "\n  >> Da cap nhat khach hang " << ma
         << " (cap " << p->capThanhVien() << ")\n";
}

void UngDung::xoaKhachHang() {
    Man::tieuDe("XOA KHACH HANG");
    string ma = Nhap::chuoi("  Nhap ma khach hang can xoa: ");
    KhachHang* p = cuaHang.khachHang().timTheoMa(ma);
    if (p == 0) throw LoiKhongTimThay("Khach hang " + ma);
    p->xuatChiTiet();

    Vector<HoaDon> hd = cuaHang.hoaDonTheoKhach(ma);
    if (!hd.rong()) {
        cout << "\n  !! Khach hang nay co " << hd.kichThuoc()
             << " hoa don trong lich su.\n";
        throw LoiRangBuoc("Khong the xoa khach hang da phat sinh giao dich.");
    }
    if (!Nhap::xacNhan("  Xac nhan xoa?")) { cout << "  >> Da huy.\n"; return; }
    cuaHang.khachHang().xoa(ma);
    cout << "\n  >> Da xoa khach hang " << ma << '\n';
}

void UngDung::timKhachHang() {
    Man::tieuDe("TIM KHACH HANG THEO TEN");
    string tk = Nhap::chuoi("  Tu khoa: ");
    Vector<KhachHang> kq = cuaHang.khachHang().timTheoTen(tk);
    if (kq.rong()) { cout << "\n  (Khong tim thay)\n"; return; }
    Man::duong('-', 93);
    for (size_t i = 0; i < kq.kichThuoc(); ++i) {
        kq[i].xuatDong();
        cout << '\n';
    }
    Man::duong('-', 93);
    cout << "  Tim thay " << kq.kichThuoc() << " ket qua.\n";
}

void UngDung::lichSuMuaHang() {
    Man::tieuDe("LICH SU MUA HANG CUA KHACH HANG");
    string ma = Nhap::chuoi("  Nhap ma khach hang: ");
    KhachHang* kh = cuaHang.khachHang().timTheoMa(ma);
    if (kh == 0) throw LoiKhongTimThay("Khach hang " + ma);

    kh->xuatChiTiet();
    Vector<HoaDon> ds = cuaHang.hoaDonTheoKhach(ma);
    if (ds.rong()) { cout << "\n  (Khach hang chua mua hang lan nao)\n"; return; }

    HoaDon::inTieuDeBang();
    double tong = 0;
    int    soCuon = 0;
    for (size_t i = 0; i < ds.kichThuoc(); ++i) {
        ds[i].xuatDong();
        cout << '\n';
        tong   += ds[i].thanhToan();
        soCuon += ds[i].tongSoLuong();
    }
    Man::duong('-', 96);
    cout << "  So hoa don: " << ds.kichThuoc()
         << "   |   Tong so cuon: " << soCuon
         << "   |   Tong chi tieu: " << dinhDangTien(tong) << " VND\n";
}
