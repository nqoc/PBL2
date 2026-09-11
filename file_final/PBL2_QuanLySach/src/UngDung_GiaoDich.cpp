// =====================================================================
//  UngDung_GiaoDich.cpp - Lap PHIEU NHAP va HOA DON ban hang
// =====================================================================
#include "UngDung.h"
#include "TienIch.h"
#include "NgoaiLe.h"

#include <iostream>
#include <iomanip>

using namespace std;

// =====================================================================
//                          PHIEU NHAP HANG
// =====================================================================
void UngDung::lapPhieuNhap() {
    Man::tieuDe("LAP PHIEU NHAP HANG MOI");

    if (cuaHang.nhaCungCap().rong())
        throw LoiRangBuoc("Chua co nha cung cap nao. Hay them nha cung cap truoc.");
    if (cuaHang.sach().rong())
        throw LoiRangBuoc("Chua co dau sach nao trong he thong.");

    inBangNhaCungCap();
    string maNCC = Nhap::chuoi("\n  Ma nha cung cap: ");
    if (!cuaHang.nhaCungCap().coMa(maNCC))
        throw LoiKhongTimThay("Nha cung cap " + maNCC);

    string ngay = Nhap::ngay("  Ngay nhap");
    TaiKhoan* tk = nguoiDung();
    PhieuNhap pn(cuaHang.sinhMaPhieuNhap(), ngay,
                 tk != 0 ? tk->getMa() : string("?"), maNCC);

    cout << "\n  --- Them cac dong hang vao phieu (nhap ma sach rong de ket thuc) ---\n";
    while (true) {
        cout << "\n  [Dong " << (pn.soDong() + 1) << "]\n";
        string maSach = Nhap::chuoi("  Ma sach (Enter de ket thuc): ", true);
        if (maSach.empty()) break;

        Sach* s = cuaHang.sach().timTheoMa(maSach);
        if (s == 0) {
            cout << "  !! Khong tim thay sach " << maSach << '\n';
            continue;
        }
        cout << "     -> " << *s << "  |  ton hien tai: " << s->getSoLuong()
             << "  |  gia nhap cu: " << dinhDangTien(s->getGiaNhap()) << " VND\n";

        int    sl  = Nhap::soNguyen("  So luong nhap    : ", 1, 100000);
        double gia = Nhap::soThuc("  Gia nhap (VND)   : ", 0, 1e9);
        pn.themDong(DongChiTiet(s->getMa(), s->getTen(), sl, gia));
        cout << "  >> Da them. Tong tien tam tinh: "
             << dinhDangTien(pn.tongTienHang()) << " VND\n";
    }

    if (pn.soDong() == 0) { cout << "\n  >> Phieu trong, da huy.\n"; return; }

    cout << '\n';
    pn.inChungTu();
    if (!Nhap::xacNhan("\n  Xac nhan luu phieu nhap (ton kho se tang)?")) {
        cout << "  >> Da huy phieu nhap.\n";
        return;
    }

    cuaHang.ghiNhanPhieuNhap(pn);          // tang ton kho + luu
    cuaHang.luuTatCa();
    cout << "\n  >> Da luu phieu nhap " << pn.getMa()
         << " va cap nhat ton kho.\n";
}

void UngDung::xemDanhSachPhieuNhap() {
    Man::tieuDe("DANH SACH PHIEU NHAP");
    Vector<PhieuNhap>& ds = cuaHang.phieuNhap().duLieu();
    if (ds.rong()) { cout << "\n  (Chua co phieu nhap nao)\n"; return; }

    PhieuNhap::inTieuDeBang();
    double tong = 0;
    for (size_t i = 0; i < ds.kichThuoc(); ++i) {
        ds[i].xuatDong();
        cout << '\n';
        tong += ds[i].thanhToan();
    }
    Man::duong('-', 88);
    cout << "  Tong " << ds.kichThuoc() << " phieu   |   Tong chi nhap hang: "
         << dinhDangTien(tong) << " VND\n";
}

void UngDung::traCuuPhieuNhapTheoNgay() {
    Man::tieuDe("TRA CUU PHIEU NHAP THEO NGAY");
    string ngay = Nhap::ngay("  Ngay can tra cuu");
    Vector<PhieuNhap> ds = cuaHang.phieuNhapTheoNgay(ngay);
    if (ds.rong()) {
        cout << "\n  (Khong co phieu nhap nao ngay " << ngay << ")\n";
        return;
    }
    PhieuNhap::inTieuDeBang();
    double tong = 0;
    for (size_t i = 0; i < ds.kichThuoc(); ++i) {
        ds[i].xuatDong();
        cout << '\n';
        tong += ds[i].thanhToan();
    }
    Man::duong('-', 88);
    cout << "  Ngay " << ngay << ": " << ds.kichThuoc() << " phieu, tong "
         << dinhDangTien(tong) << " VND\n";
}

void UngDung::xemChiTietPhieuNhap() {
    Man::tieuDe("CHI TIET PHIEU NHAP");
    string ma = Nhap::chuoi("  Nhap ma phieu nhap: ");
    PhieuNhap* pn = cuaHang.phieuNhap().timTheoMa(ma);
    if (pn == 0) throw LoiKhongTimThay("Phieu nhap " + ma);
    cout << '\n';
    pn->inChungTu();
    cout << "  Ten nha cung cap: "
         << cuaHang.tenNhaCungCap(pn->getMaNhaCungCap()) << '\n';
}

// =====================================================================
//                        HOA DON BAN HANG
// =====================================================================
void UngDung::lapHoaDon() {
    Man::tieuDe("LAP HOA DON BAN HANG");

    if (cuaHang.sach().rong())
        throw LoiRangBuoc("Chua co dau sach nao de ban.");

    // ---- Chon khach hang ----
    string maKH;
    cout << "  Khach hang:\n";
    cout << "    1. Khach le (khong tich diem)\n";
    cout << "    2. Khach hang thanh vien (co ma)\n";
    int loaiKH = Nhap::soNguyen("  Chon: ", 1, 2);

    double tiLeCK = 0.0;
    if (loaiKH == 2) {
        maKH = Nhap::chuoi("  Ma khach hang: ");
        KhachHang* kh = cuaHang.khachHang().timTheoMa(maKH);
        if (kh == 0) throw LoiKhongTimThay("Khach hang " + maKH);
        cout << "     -> " << kh->getTen() << "  |  diem: " << kh->getDiem()
             << "  |  cap: " << kh->capThanhVien()
             << "  |  chiet khau thanh vien: "
             << (kh->tiLeGiamThanhVien() * 100) << "%\n";
        tiLeCK = kh->tiLeGiamThanhVien();
        maKH   = kh->getMa();
    }

    string ngay = Nhap::ngay("  Ngay lap hoa don");
    TaiKhoan* tk = nguoiDung();
    HoaDon hd(cuaHang.sinhMaHoaDon(), ngay,
              tk != 0 ? tk->getMa() : string("?"), maKH, tiLeCK);

    // ---- Them cac dong hang ----
    cout << "\n  --- Them sach vao hoa don (Enter de ket thuc) ---\n";
    while (true) {
        cout << "\n  [Dong " << (hd.soDong() + 1) << "]\n";
        string maSach = Nhap::chuoi("  Ma sach (Enter de ket thuc): ", true);
        if (maSach.empty()) break;

        Sach* s = cuaHang.sach().timTheoMa(maSach);
        if (s == 0) {
            cout << "  !! Khong tim thay sach " << maSach << '\n';
            continue;
        }
        if (s->getSoLuong() <= 0) {
            cout << "  !! Sach " << s->getTen() << " da HET HANG.\n";
            continue;
        }
        cout << "     -> " << *s << "\n"
             << "        Gia niem yet: " << dinhDangTien(s->getGiaBan())
             << " VND   |   Giam loai " << (s->tiLeGiamGia() * 100) << "%"
             << "   |   Gia ban thuc: " << dinhDangTien(s->giaSauGiam())
             << " VND   |   Ton: " << s->getSoLuong() << '\n';

        int sl = Nhap::soNguyen("  So luong ban     : ", 1, s->getSoLuong());
        hd.themDong(DongChiTiet(s->getMa(), s->getTen(), sl, s->giaSauGiam()));
        cout << "  >> Da them. Tong tien hang tam tinh: "
             << dinhDangTien(hd.tongTienHang()) << " VND\n";
    }

    if (hd.soDong() == 0) { cout << "\n  >> Hoa don trong, da huy.\n"; return; }

    // ---- Chiet khau ----
    cout << "\n  Chiet khau thanh vien hien tai: " << (tiLeCK * 100) << "%\n";
    if (Nhap::xacNhan("  Muon nhap ti le chiet khau khac?")) {
        double t = Nhap::soThuc("  Ti le chiet khau (%): ", 0, 50);
        hd.setTiLeChietKhau(t / 100.0);
    }

    cout << '\n';
    hd.inChungTu();
    if (!Nhap::xacNhan("\n  Xac nhan luu hoa don (ton kho se giam)?")) {
        cout << "  >> Da huy hoa don.\n";
        return;
    }

    cuaHang.ghiNhanHoaDon(hd);             // kiem tra ton -> tru kho -> tich diem
    cuaHang.luuTatCa();

    cout << "\n  >> Da luu hoa don " << hd.getMa() << " thanh cong.\n";
    if (!maKH.empty()) {
        KhachHang* kh = cuaHang.khachHang().timTheoMa(maKH);
        if (kh != 0)
            cout << "  >> Diem tich luy cua " << kh->getTen() << " hien la "
                 << kh->getDiem() << " (cap " << kh->capThanhVien() << ")\n";
    }
    cout << '\n';
    hd.inChungTu();
}

void UngDung::xemDanhSachHoaDon() {
    Man::tieuDe("DANH SACH HOA DON");
    Vector<HoaDon>& ds = cuaHang.hoaDon().duLieu();
    if (ds.rong()) { cout << "\n  (Chua co hoa don nao)\n"; return; }

    HoaDon::inTieuDeBang();
    double tong = 0;
    for (size_t i = 0; i < ds.kichThuoc(); ++i) {
        ds[i].xuatDong();
        cout << '\n';
        tong += ds[i].thanhToan();
    }
    Man::duong('-', 96);
    cout << "  Tong " << ds.kichThuoc() << " hoa don   |   Tong doanh thu: "
         << dinhDangTien(tong) << " VND\n";
}

void UngDung::traCuuHoaDonTheoNgay() {
    Man::tieuDe("TRA CUU HOA DON THEO NGAY");
    string ngay = Nhap::ngay("  Ngay can tra cuu");
    Vector<HoaDon> ds = cuaHang.hoaDonTheoNgay(ngay);
    if (ds.rong()) {
        cout << "\n  (Khong co hoa don nao ngay " << ngay << ")\n";
        return;
    }
    HoaDon::inTieuDeBang();
    double tong = 0;
    for (size_t i = 0; i < ds.kichThuoc(); ++i) {
        ds[i].xuatDong();
        cout << '\n';
        tong += ds[i].thanhToan();
    }
    Man::duong('-', 96);
    cout << "  Ngay " << ngay << ": " << ds.kichThuoc() << " hoa don, doanh thu "
         << dinhDangTien(tong) << " VND\n";
}

void UngDung::traCuuHoaDonTheoKhach() {
    Man::tieuDe("TRA CUU HOA DON THEO KHACH HANG");
    string ma = Nhap::chuoi("  Ma khach hang: ");
    Vector<HoaDon> ds = cuaHang.hoaDonTheoKhach(ma);
    cout << "  Khach hang: " << cuaHang.tenKhachHang(ma) << '\n';
    if (ds.rong()) { cout << "\n  (Khong co hoa don nao)\n"; return; }

    HoaDon::inTieuDeBang();
    double tong = 0;
    for (size_t i = 0; i < ds.kichThuoc(); ++i) {
        ds[i].xuatDong();
        cout << '\n';
        tong += ds[i].thanhToan();
    }
    Man::duong('-', 96);
    cout << "  Tong " << ds.kichThuoc() << " hoa don, tong tien "
         << dinhDangTien(tong) << " VND\n";
}

void UngDung::inLaiHoaDon() {
    Man::tieuDe("IN LAI HOA DON");
    string ma = Nhap::chuoi("  Nhap ma hoa don: ");
    HoaDon* hd = cuaHang.hoaDon().timTheoMa(ma);
    if (hd == 0) throw LoiKhongTimThay("Hoa don " + ma);
    cout << '\n';
    hd->inChungTu();
    cout << "  Ten khach hang: " << cuaHang.tenKhachHang(hd->getMaKhachHang())
         << '\n';
}
