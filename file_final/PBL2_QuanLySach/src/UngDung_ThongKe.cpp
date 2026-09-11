// =====================================================================
//  UngDung_ThongKe.cpp - Tim kiem / Sap xep / Loc  va  Thong ke - Bao cao
// =====================================================================
#include "UngDung.h"
#include "ThuatToan.h"
#include "TienIch.h"
#include "NgoaiLe.h"

#include <iostream>
#include <iomanip>
#include <ctime>

using namespace std;

// =====================================================================
//                        TIM KIEM - SAP XEP - LOC
// =====================================================================
void UngDung::timTheoMaBangBam() {
    Man::tieuDe("TIM SACH THEO MA - DUNG BANG BAM (O(1) trung binh)");
    string ma = Nhap::chuoi("  Ma sach: ");
    Sach*  s  = cuaHang.sach().timTheoMa(ma);
    if (s == 0) { cout << "\n  (Khong tim thay sach " << ma << ")\n"; return; }
    inMotSach(s);
    cout << "  [Thong tin ky thuat] So o bang bam: "
         << cuaHang.sach().soOBangBam()
         << "   |   Chuoi noi ket dai nhat: "
         << cuaHang.sach().chuoiBamDaiNhat() << '\n';
}

void UngDung::timTheoMaNhiPhan() {
    Man::tieuDe("TIM SACH THEO MA - TIM KIEM NHI PHAN (O(log n))");
    cout << "  (Danh sach sach luon duoc giu sap xep tang theo ma sach)\n";
    string ma = Nhap::chuoi("  Ma sach: ");
    long   vt = cuaHang.sach().timNhiPhanTheoMa(ma);
    if (vt < 0) { cout << "\n  (Khong tim thay sach " << ma << ")\n"; return; }
    cout << "\n  Tim thay tai vi tri " << vt << " trong danh sach.\n";
    inMotSach(cuaHang.sach().tatCa()[static_cast<size_t>(vt)]);
}

void UngDung::timTheoTenSach() {
    Man::tieuDe("TIM SACH THEO TEN (tim gan dung theo chuoi con)");
    string tk = Nhap::chuoi("  Tu khoa ten sach: ");
    inBangSach(cuaHang.sach().timTheoTen(tk));
}

void UngDung::timTheoTacGiaSach() {
    Man::tieuDe("TIM SACH THEO TAC GIA");
    inBangTacGia();
    string tk = Nhap::chuoi("\n  Ma tac gia (hoac mot phan ma): ");
    inBangSach(cuaHang.sach().timTheoTacGia(tk));
}

void UngDung::timTheoTheLoaiSach() {
    Man::tieuDe("TIM SACH THEO THE LOAI");
    inBangTheLoai();
    string tk = Nhap::chuoi("\n  Ma the loai: ");
    inBangSach(cuaHang.sach().timTheoTheLoai(tk));
}

void UngDung::timTheoNXBSach() {
    Man::tieuDe("TIM SACH THEO NHA XUAT BAN");
    inBangNXB();
    string tk = Nhap::chuoi("\n  Ma nha xuat ban: ");
    inBangSach(cuaHang.sach().timTheoNXB(tk));
}

void UngDung::locTheoKhoangGia() {
    Man::tieuDe("LOC SACH THEO KHOANG GIA (theo gia sau giam)");
    double tu  = Nhap::soThuc("  Gia tu (VND)  : ", 0, 1e9);
    double den = Nhap::soThuc("  Gia den (VND) : ", tu, 1e9);
    inBangSach(cuaHang.sach().locTheoKhoangGia(tu, den));
}

void UngDung::locTheoTinhTrang() {
    Man::tieuDe("LOC SACH THEO TINH TRANG HANG");
    cout << "    1. Chi hien sach CON HANG\n";
    cout << "    2. Chi hien sach HET HANG\n";
    int c = Nhap::soNguyen("  Chon: ", 1, 2);
    inBangSach(cuaHang.sach().locTheoTinhTrang(c == 1));
}

void UngDung::sapXepDanhSach() {
    Man::tieuDe("SAP XEP DANH SACH SACH");
    cout << "  Tieu chi sap xep:\n";
    cout << "    1. Theo ma sach       (Quick Sort)\n";
    cout << "    2. Theo ten sach      (Merge Sort - on dinh)\n";
    cout << "    3. Theo gia ban       (Quick Sort)\n";
    cout << "    4. Theo so luong ton  (Quick Sort)\n";
    cout << "    5. Theo nam xuat ban  (Merge Sort)\n";
    int tc = Nhap::soNguyen("  Chon tieu chi: ", 1, 5);
    cout << "    1. Tang dan\n    2. Giam dan\n";
    bool tang = (Nhap::soNguyen("  Chon thu tu: ", 1, 2) == 1);

    QuanLySach::TieuChi t = static_cast<QuanLySach::TieuChi>(tc);
    Vector<Sach*> kq = cuaHang.sach().sapXepTheo(t, tang);
    cout << "\n  Ket qua sau khi sap xep:\n";
    inBangSach(kq);
    cout << "  Do phuc tap: Quick Sort O(n log n) trung binh, "
         << "Merge Sort O(n log n) moi truong hop.\n";
}

// So sanh so phep so sanh giua tim tuyen tinh va tim nhi phan
void UngDung::soSanhHieuNangTimKiem() {
    Man::tieuDe("SO SANH HIEU NANG CAC CACH TIM KIEM THEO MA");
    const Vector<Sach*>& ds = cuaHang.sach().tatCa();
    if (ds.rong()) { cout << "\n  (Chua co du lieu)\n"; return; }

    string ma = Nhap::chuoi("  Ma sach can tim: ");
    string maT = veThuong(ma);

    // 1) Tuyen tinh: dem so lan so sanh
    long demTuyenTinh = 0;
    long viTriTT = -1;
    for (size_t i = 0; i < ds.kichThuoc(); ++i) {
        ++demTuyenTinh;
        if (veThuong(ds[i]->getMa()) == maT) { viTriTT = static_cast<long>(i); break; }
    }

    // 2) Nhi phan: dem so lan so sanh
    long demNhiPhan = 0;
    long tra = 0, phai = static_cast<long>(ds.kichThuoc()) - 1, viTriNP = -1;
    while (tra <= phai) {
        long giua = tra + (phai - tra) / 2;
        ++demNhiPhan;
        string kg = veThuong(ds[static_cast<size_t>(giua)]->getMa());
        if (kg == maT)      { viTriNP = giua; break; }
        else if (kg < maT)  tra  = giua + 1;
        else                phai = giua - 1;
    }

    // 3) Bang bam: mot lan bam + duyet chuoi noi ket
    Sach* sBam = cuaHang.sach().timTheoMa(ma);

    Man::duong('-', 78);
    cout << left << setw(28) << "PHUONG PHAP"
         << left << setw(14) << "KET QUA"
         << left << setw(20) << "SO PHEP SO SANH"
         << left << setw(16) << "DO PHUC TAP" << '\n';
    Man::duong('-', 78);
    cout << left << setw(28) << "Tim tuyen tinh"
         << left << setw(14) << (viTriTT >= 0 ? "Tim thay" : "Khong co")
         << left << setw(20) << demTuyenTinh
         << left << setw(16) << "O(n)" << '\n';
    cout << left << setw(28) << "Tim nhi phan"
         << left << setw(14) << (viTriNP >= 0 ? "Tim thay" : "Khong co")
         << left << setw(20) << demNhiPhan
         << left << setw(16) << "O(log n)" << '\n';
    cout << left << setw(28) << "Bang bam (hash table)"
         << left << setw(14) << (sBam != 0 ? "Tim thay" : "Khong co")
         << left << setw(20) << "~1"
         << left << setw(16) << "O(1) tr.binh" << '\n';
    Man::duong('-', 78);
    cout << "  So dau sach hien co: " << ds.kichThuoc() << '\n';
    cout << "  Nhan xet: du lieu cang lon, khoang cach giua O(n) va O(log n) cang ro.\n";
}

// =====================================================================
//                          THONG KE - BAO CAO
// =====================================================================
void UngDung::thongKeTonKho() {
    Man::tieuDe("THONG KE TON KHO");
    const QuanLySach& q = cuaHang.sach();

    cout << "  Tong so dau sach            : " << q.soDauSach() << '\n';
    cout << "  Tong so cuon dang ton       : " << q.tongSoCuonTon() << '\n';
    cout << "  Gia tri ton kho (gia nhap)  : "
         << dinhDangTien(q.tongGiaTriTonKho()) << " VND\n";
    cout << "  Tong doanh thu ban hang     : "
         << dinhDangTien(cuaHang.tongDoanhThu()) << " VND\n";
    cout << "  Tong chi nhap hang          : "
         << dinhDangTien(cuaHang.tongChiNhapHang()) << " VND\n";
    cout << "  Chenh lech (thu - chi)      : "
         << dinhDangTien(cuaHang.tongDoanhThu() - cuaHang.tongChiNhapHang())
         << " VND\n";

    Man::duong('-', 60);
    cout << "  So dau sach theo tung loai (da hinh):\n";
    size_t gk = q.demTheoLoai("GK");
    size_t vh = q.demTheoLoai("VH");
    size_t tn = q.demTheoLoai("TN");
    double lonNhat = static_cast<double>(gk > vh ? (gk > tn ? gk : tn)
                                                 : (vh > tn ? vh : tn));
    Man::bieuDoCot("Sach giao khoa", static_cast<double>(gk), lonNhat, 30);
    Man::bieuDoCot("Sach van hoc",   static_cast<double>(vh), lonNhat, 30);
    Man::bieuDoCot("Sach thieu nhi", static_cast<double>(tn), lonNhat, 30);

    Sach* dat = q.sachDatNhat();
    if (dat != 0) {
        Man::duong('-', 60);
        cout << "  Dau sach dat nhat: " << *dat << "  -  "
             << dinhDangTien(dat->giaSauGiam()) << " VND\n";
    }
}

void UngDung::thongKeDoanhThuNgay() {
    Man::tieuDe("DOANH THU THEO NGAY");
    Vector<MucDoanhThu> ds = cuaHang.bangDoanhThuTheoNgay();
    if (ds.rong()) { cout << "\n  (Chua co hoa don nao)\n"; return; }

    Man::duong('-', 60);
    cout << left  << setw(16) << "NGAY"
         << right << setw(10) << "SO HD"
         << right << setw(22) << "DOANH THU (VND)" << '\n';
    Man::duong('-', 60);
    double lonNhat = 0, tong = 0;
    for (size_t i = 0; i < ds.kichThuoc(); ++i) {
        cout << left  << setw(16) << ds[i].moc
             << right << setw(10) << ds[i].soHoaDon
             << right << setw(22) << dinhDangTien(ds[i].doanhThu) << '\n';
        if (ds[i].doanhThu > lonNhat) lonNhat = ds[i].doanhThu;
        tong += ds[i].doanhThu;
    }
    Man::duong('-', 60);
    cout << "  Tong cong: " << dinhDangTien(tong) << " VND\n\n";
    cout << "  BIEU DO DOANH THU THEO NGAY:\n";
    for (size_t i = 0; i < ds.kichThuoc(); ++i)
        Man::bieuDoCot(ds[i].moc, ds[i].doanhThu, lonNhat, 40);
}

void UngDung::thongKeDoanhThuThang() {
    Man::tieuDe("DOANH THU THEO THANG");
    Vector<MucDoanhThu> ds = cuaHang.bangDoanhThuTheoThang();
    if (ds.rong()) { cout << "\n  (Chua co hoa don nao)\n"; return; }

    Man::duong('-', 60);
    cout << left  << setw(16) << "THANG"
         << right << setw(10) << "SO HD"
         << right << setw(22) << "DOANH THU (VND)" << '\n';
    Man::duong('-', 60);
    double lonNhat = 0, tong = 0;
    for (size_t i = 0; i < ds.kichThuoc(); ++i) {
        cout << left  << setw(16) << ds[i].moc
             << right << setw(10) << ds[i].soHoaDon
             << right << setw(22) << dinhDangTien(ds[i].doanhThu) << '\n';
        if (ds[i].doanhThu > lonNhat) lonNhat = ds[i].doanhThu;
        tong += ds[i].doanhThu;
    }
    Man::duong('-', 60);
    cout << "  Tong cong: " << dinhDangTien(tong) << " VND\n\n";
    cout << "  BIEU DO DOANH THU THEO THANG:\n";
    for (size_t i = 0; i < ds.kichThuoc(); ++i)
        Man::bieuDoCot(ds[i].moc, ds[i].doanhThu, lonNhat, 40);
}

void UngDung::thongKeDoanhThuKhoang() {
    Man::tieuDe("DOANH THU THEO KHOANG THOI GIAN");
    string tu  = Nhap::ngay("  Tu ngay");
    string den = Nhap::ngay("  Den ngay");
    int soHD = 0;
    double dt = cuaHang.doanhThuTheoKhoang(tu, den, soHD);

    Man::duong('-', 60);
    cout << "  Khoang thoi gian : " << tu << "  ->  " << den << '\n';
    cout << "  So hoa don       : " << soHD << '\n';
    cout << "  Tong doanh thu   : " << dinhDangTien(dt) << " VND\n";
    if (soHD > 0)
        cout << "  Trung binh 1 HD  : " << dinhDangTien(dt / soHD) << " VND\n";
    Man::duong('-', 60);
}

void UngDung::thongKeSachBanChay() {
    Man::tieuDe("TOP SACH BAN CHAY");
    Vector<MucBanChay> ds = cuaHang.bangSachBanChay();
    if (ds.rong()) { cout << "\n  (Chua ban duoc cuon nao)\n"; return; }

    Man::duong('-', 84);
    cout << left  << setw(5)  << "TT"
         << left  << setw(11) << "MA SACH"
         << left  << setw(34) << "TEN SACH"
         << right << setw(10) << "DA BAN"
         << right << setw(20) << "DOANH THU" << '\n';
    Man::duong('-', 84);
    size_t n = ds.kichThuoc() < 10 ? ds.kichThuoc() : 10;
    double lonNhat = ds[0].soLuongBan;
    for (size_t i = 0; i < n; ++i)
        cout << left  << setw(5)  << (i + 1)
             << left  << setw(11) << ds[i].ma
             << left  << setw(34) << catBot(ds[i].ten, 33)
             << right << setw(10) << ds[i].soLuongBan
             << right << setw(20) << dinhDangTien(ds[i].doanhThu) << '\n';
    Man::duong('-', 84);
    cout << "\n  BIEU DO SO LUONG BAN:\n";
    for (size_t i = 0; i < n; ++i)
        Man::bieuDoCot(ds[i].ten, ds[i].soLuongBan, lonNhat, 40);
}

void UngDung::thongKeTheLoai() {
    Man::tieuDe("THE LOAI DUOC MUA NHIEU NHAT");
    Vector<MucBanChay> ds = cuaHang.bangTheLoaiUaChuong();
    if (ds.rong()) { cout << "\n  (Chua co du lieu ban hang)\n"; return; }

    Man::duong('-', 78);
    cout << left  << setw(12) << "MA TL"
         << left  << setw(32) << "TEN THE LOAI"
         << right << setw(12) << "DA BAN"
         << right << setw(20) << "DOANH THU" << '\n';
    Man::duong('-', 78);
    double lonNhat = ds[0].soLuongBan;
    for (size_t i = 0; i < ds.kichThuoc(); ++i)
        cout << left  << setw(12) << ds[i].ma
             << left  << setw(32) << catBot(ds[i].ten, 31)
             << right << setw(12) << ds[i].soLuongBan
             << right << setw(20) << dinhDangTien(ds[i].doanhThu) << '\n';
    Man::duong('-', 78);
    cout << "\n  BIEU DO:\n";
    for (size_t i = 0; i < ds.kichThuoc(); ++i)
        Man::bieuDoCot(ds[i].ten, ds[i].soLuongBan, lonNhat, 40);
}

void UngDung::canhBaoSapHet() {
    Man::tieuDe("CANH BAO SACH SAP HET HANG");
    int nguong = cuaHang.getNguongCanhBao();
    cout << "  Nguong canh bao hien tai: ton <= " << nguong << " cuon\n";
    Vector<Sach*> ds = cuaHang.sach().sachSapHet(nguong);
    if (ds.rong()) {
        cout << "\n  >> Tot! Khong co dau sach nao duoi nguong canh bao.\n";
        return;
    }
    inBangSach(ds);
    cout << "\n  >> Can lien he nha cung cap de nhap them "
         << ds.kichThuoc() << " dau sach tren.\n";
}

void UngDung::xuatBaoCao() {
    Man::tieuDe("XUAT BAO CAO THONG KE RA TEP");
    string ten = Nhap::chuoi("  Ten tep bao cao (Enter = data/baocao.txt): ", true);
    if (ten.empty()) ten = "data/baocao.txt";
    cuaHang.xuatBaoCaoRaTep(ten);
    cout << "\n  >> Da xuat bao cao ra tep: " << ten << '\n';
    cout << "  >> Mo tep bang Notepad de xem noi dung day du.\n";
}
