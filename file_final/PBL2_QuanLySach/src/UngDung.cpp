// =====================================================================
//  UngDung.cpp - Vong lap chinh, dang nhap, phan quyen, cac menu
// =====================================================================
#include "UngDung.h"
#include "TienIch.h"
#include "NgoaiLe.h"

#include <iostream>
#include <iomanip>

using namespace std;

UngDung::UngDung()
    : cuaHang("NHA SACH BACH KHOA", "data"), dangChay(true) {}

UngDung::~UngDung() {}

// Luon tra cuu lai theo ten dang nhap (an toan hon giu con tro)
TaiKhoan* UngDung::nguoiDung() {
    if (maNguoiDung.empty()) return 0;
    return cuaHang.taiKhoan().timTheoMa(maNguoiDung);
}

// =====================  Ho tro chung  =====================
void UngDung::inLogo() const {
    Man::duong('*', 100);
    cout << "*" << setw(99) << "*" << '\n';
    cout << "*        PHAN MEM QUAN LY SACH TRONG CUA HANG CHUYEN VE SACH"
         << setw(41) << "*" << '\n';
    cout << "*        PBL2 - Du an co so lap trinh - Khoa CNTT - DUT"
         << setw(45) << "*" << '\n';
    cout << "*        Phien ban console (chua dung Qt)"
         << setw(59) << "*" << '\n';
    cout << "*" << setw(99) << "*" << '\n';
    Man::duong('*', 100);
}

void UngDung::inThanhTrangThai() {
    TaiKhoan* tk = nguoiDung();
    cout << "  Cua hang: " << cuaHang.getTen();
    if (tk != 0)
        cout << "   |   Dang nhap: " << tk->getTen()
             << " (" << tk->vaiTro() << ")";
    cout << "   |   Ngay: " << ngayHomNay() << '\n';
    cout << "  So dau sach: " << cuaHang.sach().soDauSach()
         << "   |   Ton kho: " << cuaHang.sach().tongSoCuonTon() << " cuon"
         << "   |   Hoa don: " << cuaHang.hoaDon().soLuong() << '\n';
}

bool UngDung::laAdmin() {
    TaiKhoan* tk = nguoiDung();
    return tk != 0 && tk->laAdmin();
}

void UngDung::batBuocAdmin() {
    if (!laAdmin())
        throw LoiPhanQuyen("Chuc nang nay chi danh cho quan tri vien.");
}

int UngDung::chonMuc(const string& nhac, int nhoNhat, int lonNhat) const {
    return Nhap::soNguyen(nhac, nhoNhat, lonNhat);
}

// =====================  Dang nhap / dang xuat  =====================
bool UngDung::dangNhap() {
    Man::tieuDe("DANG NHAP HE THONG");
    cout << "  (Tai khoan mac dinh: admin / admin123  hoac  nv01 / nv123)\n\n";

    for (int lan = 1; lan <= 3; ++lan) {
        string ten = Nhap::chuoi("  Ten dang nhap : ");
        string mk   = Nhap::matKhau("  Mat khau      : ");

        TaiKhoan* tk = cuaHang.taiKhoan().timTheoMa(ten);
        if (tk != 0 && tk->kiemTraMatKhau(mk)) {
            maNguoiDung = tk->getMa();
            cout << "\n  >> Xin chao " << tk->getTen()
                 << " - " << tk->vaiTro() << "!\n";
            Man::dungCho();
            return true;
        }
        cout << "  >> Sai ten dang nhap hoac mat khau. Con "
             << (3 - lan) << " lan thu.\n\n";
    }
    cout << "  >> Dang nhap that bai 3 lan. Chuong trinh ket thuc.\n";
    return false;
}

void UngDung::dangXuat() {
    if (!maNguoiDung.empty())
        cout << "  >> Da dang xuat khoi tai khoan " << maNguoiDung << ".\n";
    maNguoiDung.clear();
}

// =====================  Vong lap chinh  =====================
void UngDung::chay() {
    Man::xoaManHinh();
    inLogo();

    // Nap du lieu; neu chua co du lieu thi hoi tao du lieu mau
    try {
        cuaHang.napTatCa();
        cout << "\n  >> Da nap du lieu tu thu muc data/\n";
        if (cuaHang.tongSoDongLoi() > 0)
            cout << "  >> Canh bao: bo qua " << cuaHang.tongSoDongLoi()
                 << " dong sai dinh dang trong cac tep du lieu.\n";
    } catch (const exception& e) {
        cout << "\n  >> Loi khi nap du lieu: " << e.what() << '\n';
    }

    if (cuaHang.sach().rong() && cuaHang.theLoai().rong()) {
        cout << "\n  Chua co du lieu nao trong he thong.\n";
        if (Nhap::xacNhan("  Tao bo du lieu mau de thu nghiem?")) {
            try {
                cuaHang.taoDuLieuMau();
                cuaHang.luuTatCa();
                cout << "  >> Da tao va luu du lieu mau.\n";
            } catch (const exception& e) {
                cout << "  >> Khong tao duoc du lieu mau: " << e.what() << '\n';
            }
        }
    }

    if (!dangNhap()) return;

    while (dangChay) {
        try {
            menuChinh();
        } catch (const LoiUngDung& e) {
            cout << "\n  !! " << e.what() << '\n';
            Man::dungCho();
        } catch (const exception& e) {
            cout << "\n  !! Loi khong mong doi: " << e.what() << '\n';
            Man::dungCho();
        }
    }

    // Luu du lieu truoc khi thoat
    try {
        cuaHang.luuTatCa();
        cout << "\n  >> Da luu toan bo du lieu. Tam biet!\n";
    } catch (const exception& e) {
        cout << "\n  >> Loi khi luu du lieu: " << e.what() << '\n';
    }
}

// =====================  MENU CHINH  =====================
void UngDung::menuChinh() {
    Man::xoaManHinh();
    Man::tieuDe("MENU CHINH");
    inThanhTrangThai();
    Man::duong('-', 100);
    cout << "   1. Quan ly sach                        6. Ban hang - Hoa don\n";
    cout << "   2. Quan ly danh muc         [admin]    7. Tim kiem - Sap xep - Loc\n";
    cout << "   3. Quan ly nha cung cap     [admin]    8. Thong ke - Bao cao      [admin]\n";
    cout << "   4. Quan ly khach hang                  9. Du lieu (luu/nap/sao luu)\n";
    cout << "   5. Nhap kho - Phieu nhap    [admin]   10. Tai khoan - Doi mat khau\n";
    cout << "\n   0. Dang xuat va thoat chuong trinh\n";
    Man::duong('-', 100);

    int c = chonMuc("  Chon chuc nang: ", 0, 10);
    switch (c) {
        case 1:  menuQuanLySach();     break;
        case 2:  batBuocAdmin(); menuDanhMuc();      break;
        case 3:  batBuocAdmin(); menuNhaCungCap();   break;
        case 4:  menuKhachHang();      break;
        case 5:  batBuocAdmin(); menuNhapKho();      break;
        case 6:  menuBanHang();        break;
        case 7:  menuTimKiemSapXep();  break;
        case 8:  batBuocAdmin(); menuThongKe();      break;
        case 9:  menuDuLieu();         break;
        case 10: menuTaiKhoan();       break;
        case 0:
            if (Nhap::xacNhan("  Ban co chac muon thoat?")) {
                dangXuat();
                dangChay = false;
            }
            break;
        default: break;
    }
}

// =====================  MENU QUAN LY SACH  =====================
void UngDung::menuQuanLySach() {
    while (true) {
        Man::xoaManHinh();
        Man::tieuDe("QUAN LY SACH");
        cout << "   1. Xem toan bo danh sach sach\n";
        cout << "   2. Xem chi tiet mot dau sach\n";
        cout << "   3. Them dau sach moi              [admin]\n";
        cout << "   4. Sua thong tin dau sach         [admin]\n";
        cout << "   5. Xoa dau sach                   [admin]\n";
        cout << "   6. Cap nhat so luong ton / gia    [admin]\n";
        cout << "\n   0. Quay lai menu chinh\n";
        Man::duong('-', 100);

        int c = chonMuc("  Chon: ", 0, 6);
        if (c == 0) return;
        try {
            switch (c) {
                case 1: xemTatCaSach();     break;
                case 2: xemChiTietSach();   break;
                case 3: batBuocAdmin(); themSach();        break;
                case 4: batBuocAdmin(); suaSach();         break;
                case 5: batBuocAdmin(); xoaSach();         break;
                case 6: batBuocAdmin(); capNhatTonVaGia(); break;
                default: break;
            }
        } catch (const LoiUngDung& e) {
            cout << "\n  !! " << e.what() << '\n';
        }
        Man::dungCho();
    }
}

// =====================  MENU DANH MUC  =====================
void UngDung::menuDanhMuc() {
    while (true) {
        Man::xoaManHinh();
        Man::tieuDe("QUAN LY DANH MUC");
        cout << "   1. The loai sach     (hien co: "
             << cuaHang.theLoai().soLuong() << ")\n";
        cout << "   2. Tac gia           (hien co: "
             << cuaHang.tacGia().soLuong() << ")\n";
        cout << "   3. Nha xuat ban      (hien co: "
             << cuaHang.nxb().soLuong() << ")\n";
        cout << "\n   0. Quay lai\n";
        Man::duong('-', 100);

        int c = chonMuc("  Chon: ", 0, 3);
        if (c == 0) return;
        try {
            switch (c) {
                case 1: quanLyTheLoai();      break;
                case 2: quanLyTacGia();       break;
                case 3: quanLyNhaXuatBan();   break;
                default: break;
            }
        } catch (const LoiUngDung& e) {
            cout << "\n  !! " << e.what() << '\n';
            Man::dungCho();
        }
    }
}

// =====================  MENU NHA CUNG CAP  =====================
void UngDung::menuNhaCungCap() {
    while (true) {
        Man::xoaManHinh();
        Man::tieuDe("QUAN LY NHA CUNG CAP");
        cout << "   1. Xem danh sach nha cung cap\n";
        cout << "   2. Them nha cung cap\n";
        cout << "   3. Sua thong tin nha cung cap\n";
        cout << "   4. Xoa nha cung cap\n";
        cout << "   5. Tim kiem theo ten\n";
        cout << "   6. Lich su nhap hang theo nha cung cap\n";
        cout << "\n   0. Quay lai\n";
        Man::duong('-', 100);

        int c = chonMuc("  Chon: ", 0, 6);
        if (c == 0) return;
        try {
            switch (c) {
                case 1: inBangNhaCungCap();  break;
                case 2: themNhaCungCap();    break;
                case 3: suaNhaCungCap();     break;
                case 4: xoaNhaCungCap();     break;
                case 5: timNhaCungCap();     break;
                case 6: lichSuNhapTheoNCC(); break;
                default: break;
            }
        } catch (const LoiUngDung& e) {
            cout << "\n  !! " << e.what() << '\n';
        }
        Man::dungCho();
    }
}

// =====================  MENU KHACH HANG  =====================
void UngDung::menuKhachHang() {
    while (true) {
        Man::xoaManHinh();
        Man::tieuDe("QUAN LY KHACH HANG");
        cout << "   1. Xem danh sach khach hang\n";
        cout << "   2. Them khach hang\n";
        cout << "   3. Sua thong tin khach hang\n";
        cout << "   4. Xoa khach hang                 [admin]\n";
        cout << "   5. Tim kiem theo ten\n";
        cout << "   6. Xem lich su mua hang\n";
        cout << "\n   0. Quay lai\n";
        Man::duong('-', 100);

        int c = chonMuc("  Chon: ", 0, 6);
        if (c == 0) return;
        try {
            switch (c) {
                case 1: inBangKhachHang(); break;
                case 2: themKhachHang();   break;
                case 3: suaKhachHang();    break;
                case 4: batBuocAdmin(); xoaKhachHang(); break;
                case 5: timKhachHang();    break;
                case 6: lichSuMuaHang();   break;
                default: break;
            }
        } catch (const LoiUngDung& e) {
            cout << "\n  !! " << e.what() << '\n';
        }
        Man::dungCho();
    }
}

// =====================  MENU NHAP KHO  =====================
void UngDung::menuNhapKho() {
    while (true) {
        Man::xoaManHinh();
        Man::tieuDe("NHAP KHO - PHIEU NHAP HANG");
        cout << "   1. Lap phieu nhap moi\n";
        cout << "   2. Xem danh sach phieu nhap\n";
        cout << "   3. Tra cuu phieu nhap theo ngay\n";
        cout << "   4. Xem chi tiet mot phieu nhap\n";
        cout << "\n   0. Quay lai\n";
        Man::duong('-', 100);

        int c = chonMuc("  Chon: ", 0, 4);
        if (c == 0) return;
        try {
            switch (c) {
                case 1: lapPhieuNhap();             break;
                case 2: xemDanhSachPhieuNhap();     break;
                case 3: traCuuPhieuNhapTheoNgay();  break;
                case 4: xemChiTietPhieuNhap();      break;
                default: break;
            }
        } catch (const LoiUngDung& e) {
            cout << "\n  !! " << e.what() << '\n';
        }
        Man::dungCho();
    }
}

// =====================  MENU BAN HANG  =====================
void UngDung::menuBanHang() {
    while (true) {
        Man::xoaManHinh();
        Man::tieuDe("BAN HANG - HOA DON");
        cout << "   1. Lap hoa don ban hang moi\n";
        cout << "   2. Xem danh sach hoa don\n";
        cout << "   3. Tra cuu hoa don theo ngay\n";
        cout << "   4. Tra cuu hoa don theo khach hang\n";
        cout << "   5. In lai mot hoa don theo ma\n";
        cout << "\n   0. Quay lai\n";
        Man::duong('-', 100);

        int c = chonMuc("  Chon: ", 0, 5);
        if (c == 0) return;
        try {
            switch (c) {
                case 1: lapHoaDon();              break;
                case 2: xemDanhSachHoaDon();      break;
                case 3: traCuuHoaDonTheoNgay();   break;
                case 4: traCuuHoaDonTheoKhach();  break;
                case 5: inLaiHoaDon();            break;
                default: break;
            }
        } catch (const LoiUngDung& e) {
            cout << "\n  !! " << e.what() << '\n';
        }
        Man::dungCho();
    }
}

// =====================  MENU TIM KIEM - SAP XEP  =====================
void UngDung::menuTimKiemSapXep() {
    while (true) {
        Man::xoaManHinh();
        Man::tieuDe("TIM KIEM - SAP XEP - LOC DU LIEU");
        cout << "   1. Tim sach theo ma  (bang bam - O(1))\n";
        cout << "   2. Tim sach theo ma  (tim kiem nhi phan - O(log n))\n";
        cout << "   3. Tim sach theo ten (tim gan dung)\n";
        cout << "   4. Tim sach theo tac gia\n";
        cout << "   5. Tim sach theo the loai\n";
        cout << "   6. Tim sach theo nha xuat ban\n";
        cout << "   7. Loc theo khoang gia\n";
        cout << "   8. Loc theo tinh trang con hang / het hang\n";
        cout << "   9. Sap xep danh sach sach\n";
        cout << "  10. So sanh hieu nang cac cach tim kiem\n";
        cout << "\n   0. Quay lai\n";
        Man::duong('-', 100);

        int c = chonMuc("  Chon: ", 0, 10);
        if (c == 0) return;
        try {
            switch (c) {
                case 1:  timTheoMaBangBam();      break;
                case 2:  timTheoMaNhiPhan();      break;
                case 3:  timTheoTenSach();        break;
                case 4:  timTheoTacGiaSach();     break;
                case 5:  timTheoTheLoaiSach();    break;
                case 6:  timTheoNXBSach();        break;
                case 7:  locTheoKhoangGia();      break;
                case 8:  locTheoTinhTrang();      break;
                case 9:  sapXepDanhSach();        break;
                case 10: soSanhHieuNangTimKiem(); break;
                default: break;
            }
        } catch (const LoiUngDung& e) {
            cout << "\n  !! " << e.what() << '\n';
        }
        Man::dungCho();
    }
}

// =====================  MENU THONG KE  =====================
void UngDung::menuThongKe() {
    while (true) {
        Man::xoaManHinh();
        Man::tieuDe("THONG KE - BAO CAO");
        cout << "   1. Tong quan ton kho\n";
        cout << "   2. Doanh thu theo ngay      (co bieu do)\n";
        cout << "   3. Doanh thu theo thang     (co bieu do)\n";
        cout << "   4. Doanh thu theo khoang thoi gian\n";
        cout << "   5. Top sach ban chay        (co bieu do)\n";
        cout << "   6. The loai duoc mua nhieu nhat\n";
        cout << "   7. Canh bao sach sap het hang\n";
        cout << "   8. Xuat bao cao ra tep van ban\n";
        cout << "\n   0. Quay lai\n";
        Man::duong('-', 100);

        int c = chonMuc("  Chon: ", 0, 8);
        if (c == 0) return;
        try {
            switch (c) {
                case 1: thongKeTonKho();        break;
                case 2: thongKeDoanhThuNgay();  break;
                case 3: thongKeDoanhThuThang(); break;
                case 4: thongKeDoanhThuKhoang();break;
                case 5: thongKeSachBanChay();   break;
                case 6: thongKeTheLoai();       break;
                case 7: canhBaoSapHet();        break;
                case 8: xuatBaoCao();           break;
                default: break;
            }
        } catch (const LoiUngDung& e) {
            cout << "\n  !! " << e.what() << '\n';
        }
        Man::dungCho();
    }
}

// =====================  MENU DU LIEU  =====================
void UngDung::menuDuLieu() {
    while (true) {
        Man::xoaManHinh();
        Man::tieuDe("QUAN LY TEP DU LIEU");
        cout << "   1. Luu toan bo du lieu xuong tep\n";
        cout << "   2. Nap lai du lieu tu tep (huy thay doi chua luu)\n";
        cout << "   3. Sao luu du lieu ra thu muc data/backup   [admin]\n";
        cout << "   4. Tao bo du lieu mau                       [admin]\n";
        cout << "   5. Dat nguong canh bao ton kho (hien tai: "
             << cuaHang.getNguongCanhBao() << ")            [admin]\n";
        cout << "\n   0. Quay lai\n";
        Man::duong('-', 100);

        int c = chonMuc("  Chon: ", 0, 5);
        if (c == 0) return;
        try {
            switch (c) {
                case 1:
                    cuaHang.luuTatCa();
                    cout << "\n  >> Da luu toan bo du lieu xuong thu muc data/\n";
                    break;
                case 2:
                    if (Nhap::xacNhan("  Moi thay doi chua luu se bi mat. Tiep tuc?")) {
                        cuaHang.napTatCa();
                        cout << "\n  >> Da nap lai du lieu tu tep.\n";
                        if (nguoiDung() == 0) {
                            cout << "  >> Tai khoan hien tai khong con, buoc dang xuat.\n";
                            dangChay = false;
                        }
                    }
                    break;
                case 3:
                    batBuocAdmin();
                    cuaHang.saoLuu();
                    cout << "\n  >> Da sao luu vao data/backup/\n";
                    break;
                case 4:
                    batBuocAdmin();
                    if (Nhap::xacNhan("  Them du lieu mau vao he thong hien tai?")) {
                        cuaHang.taoDuLieuMau();
                        cout << "\n  >> Da tao du lieu mau.\n";
                    }
                    break;
                case 5:
                    batBuocAdmin();
                    cuaHang.setNguongCanhBao(
                        Nhap::soNguyen("  Nguong canh bao ton kho: ", 0, 100000));
                    cout << "\n  >> Da cap nhat nguong canh bao.\n";
                    break;
                default: break;
            }
        } catch (const LoiUngDung& e) {
            cout << "\n  !! " << e.what() << '\n';
        }
        Man::dungCho();
    }
}

// =====================  MENU TAI KHOAN  =====================
void UngDung::menuTaiKhoan() {
    while (true) {
        Man::xoaManHinh();
        Man::tieuDe("TAI KHOAN NGUOI DUNG");
        if (nguoiDung() != 0) nguoiDung()->xuatChiTiet();
        Man::duong('-', 100);
        cout << "   1. Doi mat khau cua toi\n";
        cout << "   2. Xem danh sach tai khoan        [admin]\n";
        cout << "   3. Them tai khoan moi             [admin]\n";
        cout << "   4. Doi quyen mot tai khoan        [admin]\n";
        cout << "   5. Xoa tai khoan                  [admin]\n";
        cout << "\n   0. Quay lai\n";
        Man::duong('-', 100);

        int c = chonMuc("  Chon: ", 0, 5);
        if (c == 0) return;
        try {
            if (c == 1) {
                string cu = Nhap::matKhau("  Mat khau hien tai : ");
                TaiKhoan* tk = nguoiDung();
                if (tk == 0 || !tk->kiemTraMatKhau(cu))
                    throw LoiDuLieu("Mat khau hien tai khong dung.");
                string moi  = Nhap::matKhau("  Mat khau moi      : ");
                string moi2 = Nhap::matKhau("  Nhap lai mat khau : ");
                if (moi != moi2) throw LoiDuLieu("Hai mat khau khong giong nhau.");
                tk->datMatKhau(moi);
                cout << "\n  >> Doi mat khau thanh cong.\n";
            } else {
                batBuocAdmin();
                Vector<TaiKhoan>& ds = cuaHang.taiKhoan().duLieu();
                if (c == 2) {
                    Man::duong('-', 82);
                    cout << left << setw(18) << "TEN DANG NHAP"
                         << left << setw(28) << "HO TEN"
                         << left << setw(12) << "QUYEN"
                         << left << setw(24) << "VAI TRO" << '\n';
                    Man::duong('-', 82);
                    for (size_t i = 0; i < ds.kichThuoc(); ++i) {
                        ds[i].xuatDong();
                        cout << '\n';
                    }
                    Man::duong('-', 82);
                    cout << "  Tong: " << ds.kichThuoc() << " tai khoan\n";
                } else if (c == 3) {
                    TaiKhoan tk;
                    tk.nhap();
                    cuaHang.taiKhoan().them(tk);
                    cout << "\n  >> Da them tai khoan " << tk.getMa() << '\n';
                } else if (c == 4) {
                    string ten = Nhap::chuoi("  Ten dang nhap can doi quyen: ");
                    TaiKhoan* tk = cuaHang.taiKhoan().timTheoMa(ten);
                    if (tk == 0) throw LoiKhongTimThay("Tai khoan " + ten);
                    int q = chonMuc("  Quyen moi (1=Admin, 2=Nhan vien): ", 1, 2);
                    tk->setQuyen(q == 1 ? TaiKhoan::QUYEN_ADMIN
                                        : TaiKhoan::QUYEN_NHANVIEN);
                    cout << "\n  >> Da doi quyen cho " << ten << '\n';
                } else if (c == 5) {
                    string ten = Nhap::chuoi("  Ten dang nhap can xoa: ");
                    if (veThuong(ten) == veThuong(maNguoiDung))
                        throw LoiRangBuoc("Khong the xoa tai khoan dang dang nhap.");
                    if (!Nhap::xacNhan("  Xac nhan xoa tai khoan " + ten + "?")) continue;
                    if (!cuaHang.taiKhoan().xoa(ten))
                        throw LoiKhongTimThay("Tai khoan " + ten);
                    cout << "\n  >> Da xoa tai khoan " << ten << '\n';
                }
            }
        } catch (const LoiUngDung& e) {
            cout << "\n  !! " << e.what() << '\n';
        }
        Man::dungCho();
    }
}
