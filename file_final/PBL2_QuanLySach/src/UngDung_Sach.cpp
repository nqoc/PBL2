// =====================================================================
//  UngDung_Sach.cpp - Cac chuc nang giao dien lien quan den SACH
// =====================================================================
#include "UngDung.h"
#include "SachGiaoKhoa.h"
#include "SachVanHoc.h"
#include "SachThieuNhi.h"
#include "TienIch.h"
#include "NgoaiLe.h"

#include <iostream>
#include <iomanip>

using namespace std;

// ---------------------------------------------------------------------
//  In mot bang danh sach sach (nhan vao danh sach con tro -> DA HINH)
// ---------------------------------------------------------------------
void UngDung::inBangSach(const Vector<Sach*>& ds) {
    if (ds.rong()) {
        cout << "\n  (Khong co dau sach nao)\n";
        return;
    }
    Sach::inTieuDeBang();
    double tongTon = 0;
    for (size_t i = 0; i < ds.kichThuoc(); ++i) {
        ds[i]->xuatDong();                 // goi dung phien ban cua lop con
        cout << '\n';
        tongTon += ds[i]->giaTriTonKho();
    }
    Man::duong('-', 108);
    cout << "  Tong: " << ds.kichThuoc() << " dau sach"
         << "   |   Gia tri ton kho (theo gia nhap): "
         << dinhDangTien(tongTon) << " VND\n";
}

// In chi tiet mot dau sach kem TEN cua cac danh muc
void UngDung::inMotSach(const Sach* s) {
    if (s == 0) { cout << "\n  (Khong co du lieu)\n"; return; }
    Man::duong('-', 60);
    s->xuatChiTiet();
    cout << "  Tac gia       : " << cuaHang.tenTacGia(s->getMaTacGia()) << '\n'
         << "  The loai      : " << cuaHang.tenTheLoai(s->getMaTheLoai()) << '\n'
         << "  Nha xuat ban  : " << cuaHang.tenNXB(s->getMaNXB()) << '\n'
         << "  Gia tri ton   : " << dinhDangTien(s->giaTriTonKho()) << " VND\n"
         << "  Loi nhuan/cuon: " << dinhDangTien(s->loiNhuanMotCuon()) << " VND\n";
    if (s->sapHetHang(cuaHang.getNguongCanhBao()))
        cout << "  *** CANH BAO: sach sap het hang! ***\n";
    Man::duong('-', 60);
}

void UngDung::xemTatCaSach() {
    Man::tieuDe("DANH SACH TOAN BO SACH");
    inBangSach(cuaHang.sach().tatCa());
}

// Hoi nguoi dung mot ma sach va tra ve con tro toi sach do
Sach* UngDung::hoiChonSach(const string& nhac) {
    string ma = Nhap::chuoi(nhac);
    Sach*  s  = cuaHang.sach().timTheoMa(ma);
    if (s == 0) throw LoiKhongTimThay("Khong co dau sach nao co ma " + ma);
    return s;
}

void UngDung::xemChiTietSach() {
    Man::tieuDe("CHI TIET MOT DAU SACH");
    Sach* s = hoiChonSach("  Nhap ma sach: ");
    inMotSach(s);
}

// ---------------------------------------------------------------------
//  THEM SACH MOI
// ---------------------------------------------------------------------
void UngDung::themSach() {
    Man::tieuDe("THEM DAU SACH MOI");

    if (cuaHang.theLoai().rong() || cuaHang.tacGia().rong() || cuaHang.nxb().rong())
        throw LoiRangBuoc("Can co it nhat 1 the loai, 1 tac gia va 1 NXB "
                          "truoc khi them sach.");

    cout << "  Chon loai sach:\n";
    cout << "    1. Sach giao khoa (giam 10%)\n";
    cout << "    2. Sach van hoc   (giam 5%)\n";
    cout << "    3. Sach thieu nhi (giam 15%)\n";
    int loai = Nhap::soNguyen("  Loai: ", 1, 3);
    string maLoai = (loai == 1) ? "GK" : (loai == 2 ? "VH" : "TN");

    cout << "\n  --- Danh muc dang co de tham chieu ---\n";
    inBangTacGia();
    inBangTheLoai();
    inBangNXB();

    Sach* s = taoSachTheoMaLoai(maLoai);      // ham xuong
    try {
        cout << "\n  --- Nhap thong tin sach ---\n";
        s->nhap();

        // Kiem tra rang buoc toan ven: 3 ma danh muc phai ton tai
        while (true) {
            try {
                cuaHang.kiemTraMaDanhMucTonTai(s->getMaTacGia(),
                                               s->getMaTheLoai(),
                                               s->getMaNXB());
                break;
            } catch (const LoiRangBuoc& e) {
                cout << "  !! " << e.what() << "\n  Nhap lai 3 ma danh muc:\n";
                s->setMaTacGia(Nhap::chuoi("  Ma tac gia      : "));
                s->setMaTheLoai(Nhap::chuoi("  Ma the loai     : "));
                s->setMaNXB(Nhap::chuoi("  Ma nha xuat ban : "));
            }
        }

        s->setMa(cuaHang.sach().sinhMa(maLoai));   // sinh ma tu dong
        cuaHang.sach().them(s);                    // tu day CuaHang so huu s
        cout << "\n  >> Da them sach thanh cong voi ma " << s->getMa() << '\n';
        inMotSach(s);
    } catch (...) {
        delete s;                                  // tranh ro ri bo nho
        throw;
    }
}

// ---------------------------------------------------------------------
//  SUA SACH
// ---------------------------------------------------------------------
void UngDung::suaSach() {
    Man::tieuDe("SUA THONG TIN DAU SACH");
    Sach* s = hoiChonSach("  Nhap ma sach can sua: ");
    inMotSach(s);

    cout << "\n  Chon truong can sua:\n";
    cout << "    1. Ten sach            5. Gia nhap\n";
    cout << "    2. Ma tac gia          6. Gia ban\n";
    cout << "    3. Ma the loai         7. Vi tri ke\n";
    cout << "    4. Ma nha xuat ban     8. Mo ta\n";
    cout << "                           9. Nam xuat ban\n";
    cout << "    0. Huy\n";
    int c = Nhap::soNguyen("  Chon: ", 0, 9);

    switch (c) {
        case 0: cout << "  >> Da huy.\n"; return;
        case 1: s->setTen(Nhap::chuoi("  Ten sach moi     : ")); break;
        case 2: {
            string m = Nhap::chuoi("  Ma tac gia moi   : ");
            if (!cuaHang.tacGia().coMa(m)) throw LoiRangBuoc("Ma tac gia khong ton tai.");
            s->setMaTacGia(m);
            break;
        }
        case 3: {
            string m = Nhap::chuoi("  Ma the loai moi  : ");
            if (!cuaHang.theLoai().coMa(m)) throw LoiRangBuoc("Ma the loai khong ton tai.");
            s->setMaTheLoai(m);
            break;
        }
        case 4: {
            string m = Nhap::chuoi("  Ma NXB moi       : ");
            if (!cuaHang.nxb().coMa(m)) throw LoiRangBuoc("Ma NXB khong ton tai.");
            s->setMaNXB(m);
            break;
        }
        case 5: s->setGiaNhap(Nhap::soThuc("  Gia nhap moi     : ", 0, 1e9)); break;
        case 6: s->setGiaBan(Nhap::soThuc("  Gia ban moi      : ", 0, 1e9));  break;
        case 7: s->setViTriKe(Nhap::chuoi("  Vi tri ke moi    : ", true));    break;
        case 8: s->setMoTa(Nhap::chuoi("  Mo ta moi        : ", true));       break;
        case 9: s->setNamXB(Nhap::soNguyen("  Nam xuat ban moi : ", 1900, 2100)); break;
        default: break;
    }
    cout << "\n  >> Da cap nhat.\n";
    inMotSach(s);
}

// ---------------------------------------------------------------------
//  XOA SACH
// ---------------------------------------------------------------------
void UngDung::xoaSach() {
    Man::tieuDe("XOA DAU SACH");
    Sach* s = hoiChonSach("  Nhap ma sach can xoa: ");
    inMotSach(s);

    if (s->getSoLuong() > 0) {
        cout << "  Luu y: sach nay con " << s->getSoLuong() << " cuon trong kho.\n";
        if (!Nhap::xacNhan("  Van muon xoa?")) { cout << "  >> Da huy.\n"; return; }
    } else if (!Nhap::xacNhan("  Xac nhan xoa dau sach nay?")) {
        cout << "  >> Da huy.\n";
        return;
    }

    string ma = s->getMa();
    if (cuaHang.sach().xoa(ma)) cout << "\n  >> Da xoa dau sach " << ma << '\n';
    else                        cout << "\n  >> Khong xoa duoc.\n";
}

// ---------------------------------------------------------------------
//  CAP NHAT TON KHO / GIA BAN NHANH
// ---------------------------------------------------------------------
void UngDung::capNhatTonVaGia() {
    Man::tieuDe("CAP NHAT SO LUONG TON / GIA BAN");
    Sach* s = hoiChonSach("  Nhap ma sach: ");
    inMotSach(s);

    cout << "\n    1. Dat lai so luong ton\n";
    cout << "    2. Cong them vao ton kho\n";
    cout << "    3. Dat lai gia ban\n";
    cout << "    0. Huy\n";
    int c = Nhap::soNguyen("  Chon: ", 0, 3);
    switch (c) {
        case 1: s->setSoLuong(Nhap::soNguyen("  So luong ton moi : ", 0, 1000000)); break;
        case 2: (*s) += Nhap::soNguyen("  So luong them    : ", 1, 100000); break;
        case 3: s->setGiaBan(Nhap::soThuc("  Gia ban moi      : ", 0, 1e9)); break;
        default: cout << "  >> Da huy.\n"; return;
    }
    cout << "\n  >> Da cap nhat: " << *s
         << "  |  ton = " << s->getSoLuong()
         << "  |  gia ban = " << dinhDangTien(s->getGiaBan()) << " VND\n";
}
