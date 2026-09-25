#include <cmath>
#include <iostream>
#include <string>
#define vector Vector
#define vector Vector

#include "ChungTu.h"
#include "ChiTietHoaDon.h"
#include "DanhMuc.h"
#include "HoaDon.h"
#include "Nguoi.h"
#include "PhieuNhap.h"
#include "Sach.h"
#include "TaiKhoan.h"
#include "TienIch.h"

using namespace std;

namespace {
int soTest = 0;
int soDat = 0;

void kiemTra(bool dieuKien, const string& ten) {
    ++soTest;
    if (dieuKien) {
        ++soDat;
        cout << "[DAT] " << ten << '\n';
    } else {
        cout << "[LOI] " << ten << '\n';
    }
}

void testTienIch() {
    vector<string> phanTu = TachChuoi("3|J.K. Rowling|Harry Potter", '|');
    kiemTra(phanTu.size() == 3 && phanTu[1] == "J.K. Rowling", "TachChuoi");
    kiemTra(TachChuoi("a|", '|').size() == 2, "TachChuoi giu cot rong cuoi");
    kiemTra(ToLower("AbC") == "abc", "ToLower");
    kiemTra(ChuanHoa("  xin chao\t") == "xin chao", "ChuanHoa");
    kiemTra(CheckTuNhap("Giai Tich Cao Cap", "giai tich"), "CheckTuNhap co ket qua");
    kiemTra(!CheckTuNhap("Giai Tich Cao Cap", "vat ly"), "CheckTuNhap khong co ket qua");
    kiemTra(ChuyenSo(10000000000.0) == "10.000.000.000", "ChuyenSo");

    int soNguyen = 0;
    double soThuc = 0;
    kiemTra(ChuoiSangInt(" -12 ", soNguyen) && soNguyen == -12, "ChuoiSangInt");
    kiemTra(!ChuoiSangInt("12x", soNguyen), "ChuoiSangInt tu choi ky tu thua");
    kiemTra(ChuoiSangDouble("3.5", soThuc) && soThuc == 3.5, "ChuoiSangDouble");
    kiemTra(CoKyTuNganCach("a#b"), "CoKyTuNganCach");
    kiemTra(CatBot("abcdefgh", 5) == "ab...", "CatBot");
}

void testNguoiVaDanhMuc() {
    TaiKhoan nguoi;
    kiemTra(nguoi.setMa(" N01 ") && nguoi.getMa() == "N01", "Nguoi::setMa");
    kiemTra(nguoi.setHoTen(" Nguyen Van A "), "Nguoi::setHoTen");
    kiemTra(nguoi.setSoDienThoai("0912345678"), "Nguoi::setSoDienThoai");
    kiemTra(!nguoi.setSoDienThoai("09abc"), "Nguoi tu choi so dien thoai sai");
    kiemTra(nguoi.setEmail(" A@Example.COM ") && nguoi.getEmail() == "a@example.com", "Nguoi::setEmail");
    kiemTra(!Nguoi::checkEmail("a@example.com@x.com"), "checkEmail tu choi hai @");

    TheLoai theLoai("TL01", "Van hoc", "Mo ta");
    kiemTra(theLoai.getMa() == "TL01" && theLoai.getTen() == "Van hoc", "TheLoai constructor");
    kiemTra(!theLoai.setTen("Ten|Sai"), "TheLoai tu choi ky tu ngan cach");

        TacGia tacGia("1", "Nguyen Nhat Anh", "Nha van");
        kiemTra(tacGia.fromChuoi("1|Nguyen Nhat Anh|Nha van"), "TacGia doc chuoi");
        NhaXuatBan nhaXuatBan("1", "NXB Tre", "Q3", "02839391234", "nxb@tre.vn");
        kiemTra(nhaXuatBan.fromChuoi("1|NXB Tre|Q3|02839391234|nxb@tre.vn"), "NhaXuatBan doc chuoi");
        NhaCungCap nhaCungCap;
        kiemTra(nhaCungCap.fromChuoi("NCC001|Fahasa|02838225796|Q1|contact@fahasa.vn|0300445655"),
            "NhaCungCap doc chuoi");
        KhachHang khachHang;
        kiemTra(khachHang.fromChuoi("1|Tran Van An|0909123456|Q1|100") && khachHang.getDiem() == 100,
            "KhachHang doc chuoi");
        kiemTra(docTheLoai("data/theloai.txt").size() == 30, "Doc file the loai");
        kiemTra(docTacGia("data/tacgia.txt").size() == 30, "Doc file tac gia");
        kiemTra(docNhaXuatBan("data/nhaxuatban.txt").size() == 30, "Doc file nha xuat ban");
        kiemTra(docNhaCungCap("data/nhacungcap.txt").size() == 15, "Doc file nha cung cap");
        kiemTra(docKhachHang("data/khachhang.txt").size() == 30, "Doc file khach hang");
}

void testSach() {
    SachGiaoKhoa sach("S01", "Sach mau", "TG01", "TL01", "NXB01", 2024,
                      50000, 75000, 3, "A01", "Mo ta", "05/09/2024", "Toan", "12", 10);
    kiemTra(sach.getMaSach() == "S01" && sach.getSoLuongTon() == 3, "Sach constructor");
    kiemTra(!sach.setNamXuatBan(1899) && sach.getNamXuatBan() == 2024, "Sach gioi han nam");
    kiemTra(sach.nhapThemKho(2) && sach.getSoLuongTon() == 5, "Sach::nhapThemKho");
    kiemTra(sach.banBotKho(1) && sach.getSoLuongTon() == 4, "Sach::banBotKho");
    kiemTra(!sach.banBotKho(10), "Sach khong ban qua ton kho");
    kiemTra(sach.giaTriTonKho() == 200000 && sach.loiNhuanMotCuon() == 25000,
            "Sach tinh gia tri va loi nhuan");
    kiemTra(sach.loaiSach() == "Giao khoa" && sach.giaSauGiam() == 67500,
            "SachGiaoKhoa giam gia");
    kiemTra(!sach.setNgayTao("31/02/2024"), "Sach tu choi ngay khong hop le");
    string dong = sach.toCSV();
    SachGiaoKhoa sachDoc;
    kiemTra(sachDoc.fromCSV(dong) && sachDoc.getMaSach() == "S01", "Sach ghi doc CSV");
    vector<shared_ptr<Sach> > sachMau = docSach("data/sach.txt");
    kiemTra(sachMau.size() == 30, "Doc file sach");
}

void testChungTu() {
    kiemTra(ChungTu::laNgayHopLe("29/02/2024"), "ChungTu ngay nam nhuan");
    kiemTra(!ChungTu::laNgayHopLe("29/02/2023"), "ChungTu ngay sai nam thuong");
    kiemTra(ChungTu::soHoaNgay("05/09/2026") == 20260905, "ChungTu soHoaNgay");
        kiemTra(ChungTu::soHoaNgay("31/02/2024") == 0,
            "ChungTu soHoaNgay tu choi ngay khong ton tai");

    DongChiTiet dong("S01", "Sach mau", 2, 75000);
    kiemTra(dong.fromChuoi("S02#Sach khac#3#120000") && dong.getSoLuong() == 3,
            "DongChiTiet::fromChuoi");
    kiemTra(!dong.fromChuoi("S02#Sai#0#120000"), "DongChiTiet tu choi so luong 0");

    ChungTu chungTu("HD01", "05/09/2026", "admin");
    chungTu.themDong(DongChiTiet("S01", "Sach mau", 2, 75000));
    chungTu.themDong(DongChiTiet("S01", "Sach mau", 1, 75000));
    chungTu.themDong(DongChiTiet("S02", "Sach khac", 2, 100000));
    kiemTra(chungTu.soDong() == 2 && chungTu.tongSoLuong() == 5,
            "ChungTu gom dong trung ma");
    kiemTra(chungTu.tongTienHang() == 425000 && chungTu.thanhToan() == 425000,
            "ChungTu tinh tong tien");
    vector<string> dongDaGhi = TachChuoi(chungTu.chuoiChiTiet(), '|');
    ChungTu chungTuDoc;
    chungTuDoc.docChiTiet(dongDaGhi, 0);
    kiemTra(chungTuDoc.soDong() == 2 && chungTuDoc.tongSoLuong() == 5,
            "ChungTu ghi doc chi tiet");
    kiemTra(chungTu.xoaDong(0) && chungTu.soDong() == 1 && !chungTu.xoaDong(5),
            "ChungTu xoa dong");
}

void testTaiKhoan() {
    TaiKhoan admin("admin", "e3b0c", "ADMIN");
    TaiKhoan nhanVien;
    kiemTra(admin.laAdmin() && !admin.laNhanVien(), "TaiKhoan admin");
    kiemTra(nhanVien.fromChuoi("employee1|a665a|employee") && nhanVien.laEmployee(),
            "TaiKhoan doc employee");
    kiemTra(nhanVien.toChuoi() == "employee1|a665a|employee", "TaiKhoan ghi chuoi");
    kiemTra(!nhanVien.fromChuoi("thieu|cot"), "TaiKhoan tu choi dong thieu cot");
    vector<TaiKhoan> danhSach = docTaiKhoan("data/taikhoan.txt");
    kiemTra(danhSach.size() == 2, "TaiKhoan doc file du lieu");
}

    void testHoaDonVaPhieuNhap() {
        HoaDon hoaDon;
        kiemTra(hoaDon.fromChuoi("1|01/03/2026|1|0.0|75000|01/03/2026") &&
            hoaDon.getMaKhachHang() == "1", "HoaDon doc chuoi");
        kiemTra(docHoaDon("data/hoadon.txt").size() == 30, "Doc file hoa don");

        PhieuNhap phieuNhap;
        kiemTra(phieuNhap.fromChuoi("PN0001|05/01/2026|admin|NCC007|3#GK001#Toan 12#50#26000#GK002#Toan 11#40#24000#GK003#Toan 10#40#23000") &&
            phieuNhap.soDong() == 3, "PhieuNhap doc chi tiet nen");
        kiemTra(docPhieuNhap("data/phieunhap.txt").size() == 15, "Doc file phieu nhap");

        ChiTietHoaDon chiTiet;
        kiemTra(chiTiet.fromChuoi("1|1|1|75000|75000") && chiTiet.getSoLuong() == 1,
            "ChiTietHoaDon doc chuoi");
        kiemTra(docChiTietHoaDon("data/chitiethoadon.txt").size() == 30,
            "Doc file chi tiet hoa don");
    }
}

int main() {
    cout << "=== KIEM THU PBL2 ===\n";
    testTienIch();
    testNguoiVaDanhMuc();
    testSach();
    testChungTu();
    testTaiKhoan();
    testHoaDonVaPhieuNhap();
    cout << "=== KET QUA: " << soDat << "/" << soTest << " TEST DAT ===\n";
    return soDat == soTest ? 0 : 1;
}