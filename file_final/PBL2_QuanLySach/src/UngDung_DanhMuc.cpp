// =====================================================================
//  UngDung_DanhMuc.cpp - Quan ly The loai / Tac gia / Nha xuat ban
//
//  Diem dang chu y: ba loai danh muc co cung nghiep vu (them/sua/xoa/tim)
//  nen ta viet MOT HAM TEMPLATE dung chung cho ca ba -> tranh lap code.
// =====================================================================
#include "UngDung.h"
#include "TienIch.h"
#include "NgoaiLe.h"

#include <iostream>
#include <iomanip>

using namespace std;

// Ma loai danh muc dung cho buoc xoa co kiem tra rang buoc
enum LoaiDanhMuc { DM_THELOAI = 1, DM_TACGIA, DM_NXB };

// ---------------------------------------------------------------------
//  HAM TEMPLATE dung chung cho moi kho danh muc
//  (dinh nghia ngay trong tep .cpp vi chi dung o day)
// ---------------------------------------------------------------------
template <class T>
static void menuDanhMucChung(CuaHang& cuaHang, KhoDuLieu<T>& kho,
                             const string& tienTo, const string& tenLoai,
                             int loaiDM) {
    while (true) {
        Man::xoaManHinh();
        Man::tieuDe("QUAN LY " + tenLoai);
        cout << "   1. Xem danh sach          (hien co: " << kho.soLuong() << ")\n";
        cout << "   2. Them moi\n";
        cout << "   3. Sua thong tin\n";
        cout << "   4. Xoa (co kiem tra rang buoc)\n";
        cout << "   5. Tim theo ten\n";
        cout << "   6. Xem cac dau sach thuoc muc nay\n";
        cout << "\n   0. Quay lai\n";
        Man::duong('-', 100);

        int c = Nhap::soNguyen("  Chon: ", 0, 6);
        if (c == 0) return;

        try {
            if (c == 1) {
                Vector<T>& ds = kho.duLieu();
                if (ds.rong()) cout << "\n  (Chua co du lieu)\n";
                else {
                    Man::duong('-', 92);
                    for (size_t i = 0; i < ds.kichThuoc(); ++i) {
                        ds[i].xuatDong();
                        cout << '\n';
                    }
                    Man::duong('-', 92);
                    cout << "  Tong: " << ds.kichThuoc() << " " << veThuong(tenLoai) << '\n';
                }
            } else if (c == 2) {
                T x;
                x.nhap();
                x.setMa(kho.sinhMa(tienTo));
                kho.them(x);
                cout << "\n  >> Da them, ma tu sinh: " << x.getMa() << '\n';
            } else if (c == 3) {
                string ma = Nhap::chuoi("  Nhap ma can sua: ");
                T* p = kho.timTheoMa(ma);
                if (p == 0) throw LoiKhongTimThay(tenLoai + " " + ma);
                p->xuatChiTiet();
                cout << "  --- Nhap lai thong tin ---\n";
                string maCu = p->getMa();
                p->nhap();
                p->setMa(maCu);            // giu nguyen ma
                cout << "\n  >> Da cap nhat " << maCu << '\n';
            } else if (c == 4) {
                string ma = Nhap::chuoi("  Nhap ma can xoa: ");
                const T* p = kho.timTheoMa(ma);
                if (p == 0) throw LoiKhongTimThay(tenLoai + " " + ma);
                if (!Nhap::xacNhan("  Xac nhan xoa " + ma + " (" + p->getTen() + ")?"))
                    continue;
                switch (loaiDM) {
                    case DM_THELOAI: cuaHang.xoaTheLoaiAnToan(ma); break;
                    case DM_TACGIA:  cuaHang.xoaTacGiaAnToan(ma);  break;
                    case DM_NXB:     cuaHang.xoaNXBAnToan(ma);     break;
                    default: break;
                }
                cout << "\n  >> Da xoa " << ma << '\n';
            } else if (c == 5) {
                string tk = Nhap::chuoi("  Tu khoa ten: ");
                Vector<T> kq = kho.timTheoTen(tk);
                if (kq.rong()) cout << "\n  (Khong tim thay)\n";
                else {
                    Man::duong('-', 92);
                    for (size_t i = 0; i < kq.kichThuoc(); ++i) {
                        kq[i].xuatDong();
                        cout << '\n';
                    }
                    Man::duong('-', 92);
                    cout << "  Tim thay " << kq.kichThuoc() << " ket qua.\n";
                }
            } else if (c == 6) {
                string ma = Nhap::chuoi("  Nhap ma danh muc: ");
                Vector<Sach*> kq;
                switch (loaiDM) {
                    case DM_THELOAI: kq = cuaHang.sach().timTheoTheLoai(ma); break;
                    case DM_TACGIA:  kq = cuaHang.sach().timTheoTacGia(ma);  break;
                    case DM_NXB:     kq = cuaHang.sach().timTheoNXB(ma);     break;
                    default: break;
                }
                if (kq.rong()) cout << "\n  (Khong co dau sach nao thuoc muc nay)\n";
                else {
                    Sach::inTieuDeBang();
                    for (size_t i = 0; i < kq.kichThuoc(); ++i) {
                        kq[i]->xuatDong();
                        cout << '\n';
                    }
                    Man::duong('-', 108);
                    cout << "  Co " << kq.kichThuoc() << " dau sach.\n";
                }
            }
        } catch (const LoiUngDung& e) {
            cout << "\n  !! " << e.what() << '\n';
        }
        Man::dungCho();
    }
}

// ---------------------------------------------------------------------
//  Ba ham goi lai ham template ben tren voi kieu du lieu tuong ung
// ---------------------------------------------------------------------
void UngDung::quanLyTheLoai() {
    menuDanhMucChung<TheLoai>(cuaHang, cuaHang.theLoai(), "TL",
                              "THE LOAI SACH", DM_THELOAI);
}

void UngDung::quanLyTacGia() {
    menuDanhMucChung<TacGia>(cuaHang, cuaHang.tacGia(), "TG",
                             "TAC GIA", DM_TACGIA);
}

void UngDung::quanLyNhaXuatBan() {
    menuDanhMucChung<NhaXuatBan>(cuaHang, cuaHang.nxb(), "NX",
                                 "NHA XUAT BAN", DM_NXB);
}

// ---------------------------------------------------------------------
//  Cac ham in bang danh muc (dung khi them sach can tra ma)
// ---------------------------------------------------------------------
void UngDung::inBangTheLoai() {
    Vector<TheLoai>& ds = cuaHang.theLoai().duLieu();
    cout << "\n  THE LOAI:\n";
    for (size_t i = 0; i < ds.kichThuoc(); ++i)
        cout << "    " << left << setw(8) << ds[i].getMa()
             << catBot(ds[i].getTen(), 40) << '\n';
    if (ds.rong()) cout << "    (chua co)\n";
}

void UngDung::inBangTacGia() {
    Vector<TacGia>& ds = cuaHang.tacGia().duLieu();
    cout << "\n  TAC GIA:\n";
    for (size_t i = 0; i < ds.kichThuoc(); ++i)
        cout << "    " << left << setw(8) << ds[i].getMa()
             << left << setw(32) << catBot(ds[i].getTen(), 31)
             << ds[i].getQuocTich() << '\n';
    if (ds.rong()) cout << "    (chua co)\n";
}

void UngDung::inBangNXB() {
    Vector<NhaXuatBan>& ds = cuaHang.nxb().duLieu();
    cout << "\n  NHA XUAT BAN:\n";
    for (size_t i = 0; i < ds.kichThuoc(); ++i)
        cout << "    " << left << setw(8) << ds[i].getMa()
             << left << setw(32) << catBot(ds[i].getTen(), 31)
             << ds[i].getDiaChi() << '\n';
    if (ds.rong()) cout << "    (chua co)\n";
}
