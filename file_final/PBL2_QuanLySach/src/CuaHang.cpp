// =====================================================================
//  CuaHang.cpp - Cai dat tang nghiep vu
// =====================================================================
#include "CuaHang.h"
#include "SachGiaoKhoa.h"
#include "SachVanHoc.h"
#include "SachThieuNhi.h"
#include "TienIch.h"
#include "NgoaiLe.h"

#include <fstream>
#include <sstream>
#include <cstdlib>

using namespace std;

// Tao thu muc du lieu neu chua co
static void baoDamThuMuc(const string& d) {
#ifdef _WIN32
    string lenh = "if not exist \"" + d + "\" mkdir \"" + d + "\" >nul 2>nul";
#else
    string lenh = "mkdir -p \"" + d + "\" 2>/dev/null";
#endif
    if (system(lenh.c_str()) != 0) { /* bo qua: thu muc co the da ton tai */ }
}

CuaHang::CuaHang(const string& ten, const string& thuMucDuLieu)
    : tenCuaHang(ten), thuMuc(thuMucDuLieu), nguongCanhBao(10),
      khoTheLoai("the loai"), khoTacGia("tac gia"), khoNXB("nha xuat ban"),
      khoKhachHang("khach hang"), khoNhaCungCap("nha cung cap"),
      khoTaiKhoan("tai khoan"), khoHoaDon("hoa don"),
      khoPhieuNhap("phieu nhap") {
    baoDamThuMuc(thuMuc);
}

void CuaHang::setNguongCanhBao(int n) {
    if (n < 0) throw LoiDuLieu("Nguong canh bao khong duoc am.");
    nguongCanhBao = n;
}

string CuaHang::duongDan(const string& tenTep) const {
    return thuMuc + "/" + tenTep;
}

// =====================  Doi ma -> ten  =====================
string CuaHang::tenTheLoai(const string& ma) const {
    const TheLoai* p = khoTheLoai.timTheoMa(ma);
    return p ? p->getTen() : string("(khong ro)");
}

string CuaHang::tenTacGia(const string& ma) const {
    const TacGia* p = khoTacGia.timTheoMa(ma);
    return p ? p->getTen() : string("(khong ro)");
}

string CuaHang::tenNXB(const string& ma) const {
    const NhaXuatBan* p = khoNXB.timTheoMa(ma);
    return p ? p->getTen() : string("(khong ro)");
}

string CuaHang::tenKhachHang(const string& ma) const {
    if (ma.empty()) return "Khach le";
    const KhachHang* p = khoKhachHang.timTheoMa(ma);
    return p ? p->getTen() : string("(khong ro)");
}

string CuaHang::tenNhaCungCap(const string& ma) const {
    const NhaCungCap* p = khoNhaCungCap.timTheoMa(ma);
    return p ? p->getTen() : string("(khong ro)");
}

// =====================  Rang buoc toan ven  =====================
void CuaHang::kiemTraMaDanhMucTonTai(const string& maTG, const string& maTL,
                                     const string& maNXB) const {
    if (!khoTacGia.coMa(maTG))
        throw LoiRangBuoc("Khong co tac gia voi ma " + maTG);
    if (!khoTheLoai.coMa(maTL))
        throw LoiRangBuoc("Khong co the loai voi ma " + maTL);
    if (!khoNXB.coMa(maNXB))
        throw LoiRangBuoc("Khong co nha xuat ban voi ma " + maNXB);
}

void CuaHang::xoaTheLoaiAnToan(const string& ma) {
    size_t n = khoSach.demThamChieuTheLoai(ma);
    if (n > 0) {
        ostringstream os;
        os << "The loai " << ma << " dang duoc " << n
           << " dau sach su dung, khong the xoa.";
        throw LoiRangBuoc(os.str());
    }
    if (!khoTheLoai.xoa(ma)) throw LoiKhongTimThay("The loai " + ma);
}

void CuaHang::xoaTacGiaAnToan(const string& ma) {
    size_t n = khoSach.demThamChieuTacGia(ma);
    if (n > 0) {
        ostringstream os;
        os << "Tac gia " << ma << " dang duoc " << n
           << " dau sach su dung, khong the xoa.";
        throw LoiRangBuoc(os.str());
    }
    if (!khoTacGia.xoa(ma)) throw LoiKhongTimThay("Tac gia " + ma);
}

void CuaHang::xoaNXBAnToan(const string& ma) {
    size_t n = khoSach.demThamChieuNXB(ma);
    if (n > 0) {
        ostringstream os;
        os << "Nha xuat ban " << ma << " dang duoc " << n
           << " dau sach su dung, khong the xoa.";
        throw LoiRangBuoc(os.str());
    }
    if (!khoNXB.xoa(ma)) throw LoiKhongTimThay("Nha xuat ban " + ma);
}

// =====================  Sinh ma chung tu  =====================
string CuaHang::sinhMaHoaDon()    const { return khoHoaDon.sinhMa("HD", 5); }
string CuaHang::sinhMaPhieuNhap() const { return khoPhieuNhap.sinhMa("PN", 5); }

// =====================  Ghi nhan hoa don ban hang  =====================
void CuaHang::ghiNhanHoaDon(HoaDon& hd) {
    if (hd.soDong() == 0)
        throw LoiDuLieu("Hoa don chua co dong hang nao.");

    // BUOC 1: kiem tra TOAN BO rang buoc truoc khi thay doi du lieu
    const Vector<DongChiTiet>& dong = hd.cacDong();
    for (size_t i = 0; i < dong.kichThuoc(); ++i) {
        Sach* s = khoSach.timTheoMa(dong[i].getMaSach());
        if (s == 0)
            throw LoiKhongTimThay("Sach " + dong[i].getMaSach() + " trong hoa don.");
        if (dong[i].getSoLuong() > s->getSoLuong()) {
            ostringstream os;
            os << "Sach " << s->getMa() << " (" << s->getTen() << ") chi con "
               << s->getSoLuong() << " cuon.";
            throw LoiTonKho(os.str());
        }
    }

    // BUOC 2: moi thu hop le -> tru ton kho
    for (size_t i = 0; i < dong.kichThuoc(); ++i) {
        Sach* s = khoSach.timTheoMa(dong[i].getMaSach());
        s->banBotKho(dong[i].getSoLuong());
    }

    // BUOC 3: cong diem tich luy cho khach hang thanh vien
    if (!hd.getMaKhachHang().empty()) {
        KhachHang* kh = khoKhachHang.timTheoMa(hd.getMaKhachHang());
        if (kh != 0) kh->congDiemTheoHoaDon(hd.thanhToan());
    }

    // BUOC 4: luu hoa don
    if (hd.getMa().empty()) hd.setMa(sinhMaHoaDon());
    khoHoaDon.them(hd);
}

// =====================  Ghi nhan phieu nhap  =====================
void CuaHang::ghiNhanPhieuNhap(PhieuNhap& pn) {
    if (pn.soDong() == 0)
        throw LoiDuLieu("Phieu nhap chua co dong hang nao.");
    if (!khoNhaCungCap.coMa(pn.getMaNhaCungCap()))
        throw LoiKhongTimThay("Nha cung cap " + pn.getMaNhaCungCap());

    const Vector<DongChiTiet>& dong = pn.cacDong();
    for (size_t i = 0; i < dong.kichThuoc(); ++i)
        if (khoSach.timTheoMa(dong[i].getMaSach()) == 0)
            throw LoiKhongTimThay("Sach " + dong[i].getMaSach() + " trong phieu nhap.");

    for (size_t i = 0; i < dong.kichThuoc(); ++i) {
        Sach* s = khoSach.timTheoMa(dong[i].getMaSach());
        s->nhapThemKho(dong[i].getSoLuong());
        s->setGiaNhap(dong[i].getDonGia());     // cap nhat gia nhap moi nhat
    }

    if (pn.getMa().empty()) pn.setMa(sinhMaPhieuNhap());
    khoPhieuNhap.them(pn);
}

// =====================  Tep du lieu  =====================
void CuaHang::napTatCa() {
    khoSach.docFile(duongDan("sach.txt"));
    khoTheLoai.docFile(duongDan("theloai.txt"));
    khoTacGia.docFile(duongDan("tacgia.txt"));
    khoNXB.docFile(duongDan("nhaxuatban.txt"));
    khoKhachHang.docFile(duongDan("khachhang.txt"));
    khoNhaCungCap.docFile(duongDan("nhacungcap.txt"));
    khoTaiKhoan.docFile(duongDan("taikhoan.txt"));
    khoHoaDon.docFile(duongDan("hoadon.txt"));
    khoPhieuNhap.docFile(duongDan("phieunhap.txt"));
    if (khoTaiKhoan.rong()) taoTaiKhoanMacDinh();
}

void CuaHang::luuTatCa() const {
    baoDamThuMuc(thuMuc);
    khoSach.luuFile(duongDan("sach.txt"));
    khoTheLoai.luuFile(duongDan("theloai.txt"));
    khoTacGia.luuFile(duongDan("tacgia.txt"));
    khoNXB.luuFile(duongDan("nhaxuatban.txt"));
    khoKhachHang.luuFile(duongDan("khachhang.txt"));
    khoNhaCungCap.luuFile(duongDan("nhacungcap.txt"));
    khoTaiKhoan.luuFile(duongDan("taikhoan.txt"));
    khoHoaDon.luuFile(duongDan("hoadon.txt"));
    khoPhieuNhap.luuFile(duongDan("phieunhap.txt"));
}

void CuaHang::saoLuu() const {
    string thuMucSao = thuMuc + "/backup";
    baoDamThuMuc(thuMucSao);
    const char* ten[9] = {"sach.txt", "theloai.txt", "tacgia.txt",
                          "nhaxuatban.txt", "khachhang.txt", "nhacungcap.txt",
                          "taikhoan.txt", "hoadon.txt", "phieunhap.txt"};
    for (int i = 0; i < 9; ++i) {
        ifstream vao(duongDan(ten[i]).c_str(), ios::binary);
        if (!vao) continue;
        ofstream ra((thuMucSao + "/" + ten[i]).c_str(), ios::binary);
        if (!ra) throw LoiFile("Khong ghi duoc ban sao luu.");
        ra << vao.rdbuf();
    }
}

int CuaHang::tongSoDongLoi() const {
    return khoSach.loiDoc() + khoTheLoai.loiDoc() + khoTacGia.loiDoc()
         + khoNXB.loiDoc() + khoKhachHang.loiDoc() + khoNhaCungCap.loiDoc()
         + khoTaiKhoan.loiDoc() + khoHoaDon.loiDoc() + khoPhieuNhap.loiDoc();
}

void CuaHang::taoTaiKhoanMacDinh() {
    if (!khoTaiKhoan.coMa("admin"))
        khoTaiKhoan.them(TaiKhoan("admin", "Quan tri he thong", "admin123",
                                  TaiKhoan::QUYEN_ADMIN));
    if (!khoTaiKhoan.coMa("nv01"))
        khoTaiKhoan.them(TaiKhoan("nv01", "Nguyen Van Nhan Vien", "nv123",
                                  TaiKhoan::QUYEN_NHANVIEN));
}

// =====================  Du lieu mau  =====================
void CuaHang::taoDuLieuMau() {
    // ---- The loai ----
    khoTheLoai.them(TheLoai("TL001", "Giao khoa",   "Sach hoc trong nha truong"));
    khoTheLoai.them(TheLoai("TL002", "Tieu thuyet", "Van hoc dai"));
    khoTheLoai.them(TheLoai("TL003", "Truyen tranh", "Danh cho thieu nhi"));
    khoTheLoai.them(TheLoai("TL004", "Ky nang song", "Sach phat trien ban than"));

    // ---- Tac gia ----
    khoTacGia.them(TacGia("TG001", "Bo Giao duc va Dao tao", "Viet Nam"));
    khoTacGia.them(TacGia("TG002", "Vu Trong Phung",         "Viet Nam"));
    khoTacGia.them(TacGia("TG003", "Paulo Coelho",           "Brazil"));
    khoTacGia.them(TacGia("TG004", "Fujiko F. Fujio",        "Nhat Ban"));
    khoTacGia.them(TacGia("TG005", "Antoine de Saint-Exupery", "Phap"));

    // ---- Nha xuat ban ----
    khoNXB.them(NhaXuatBan("NX001", "NXB Giao Duc",   "Ha Noi",  "02438220801"));
    khoNXB.them(NhaXuatBan("NX002", "NXB Kim Dong",   "Ha Noi",  "02439434730"));
    khoNXB.them(NhaXuatBan("NX003", "NXB Van Hoc",    "Ha Noi",  "02438294685"));
    khoNXB.them(NhaXuatBan("NX004", "NXB Hoi Nha Van", "Ha Noi", "02438222135"));

    // ---- Nha cung cap ----
    khoNhaCungCap.them(NhaCungCap("NCC001", "Cong ty Sach Fahasa", "0283822455",
                                  "60-62 Le Loi, TP HCM", "sales@fahasa.vn",
                                  "0301442379"));
    khoNhaCungCap.them(NhaCungCap("NCC002", "Nha sach Tien Tho", "0243876554",
                                  "175 Giang Vo, Ha Noi", "cskh@tientho.vn",
                                  "0100233445"));

    // ---- Khach hang ----
    khoKhachHang.them(KhachHang("KH001", "Nguyen Anh Kiet", "0905123456",
                                "54 Nguyen Luong Bang, Da Nang",
                                "kiet@example.com", 250));
    khoKhachHang.them(KhachHang("KH002", "Tran Thi Mai", "0912345678",
                                "12 Le Duan, Da Nang", "mai@example.com", 620));
    khoKhachHang.them(KhachHang("KH003", "Le Van Hung", "0987654321",
                                "88 Hai Phong, Da Nang", "", 0));

    // ---- Sach (dung ham xuong + da hinh) ----
    khoSach.them(new SachGiaoKhoa("GK001", "Toan 12 - Tap 1", "TG001", "TL001",
                                  "NX001", 2023, 26000, 35000, 120,
                                  "Toan", 12, "A1-01", "Sach chinh thuc"));
    khoSach.them(new SachGiaoKhoa("GK002", "Vat Ly 11", "TG001", "TL001",
                                  "NX001", 2022, 24000, 32000, 8,
                                  "Vat Ly", 11, "A1-02", ""));
    khoSach.them(new SachVanHoc("VH001", "So Do", "TG002", "TL002", "NX003",
                                2020, 62000, 89000, 25,
                                "Tieu thuyet", "Khong", "B2-05", ""));
    khoSach.them(new SachVanHoc("VH002", "Nha Gia Kim", "TG003", "TL002",
                                "NX004", 2021, 55000, 79000, 40,
                                "Tieu thuyet", "Le Chu Cau", "B2-06", ""));
    khoSach.them(new SachThieuNhi("TN001", "Doraemon Tap 1", "TG004", "TL003",
                                  "NX002", 2019, 18000, 25000, 195,
                                  6, true, "C1-01", ""));
    khoSach.them(new SachThieuNhi("TN002", "Hoang Tu Be", "TG005", "TL003",
                                  "NX002", 2021, 38000, 55000, 6,
                                  8, true, "C1-02", "Ban dich moi"));

    taoTaiKhoanMacDinh();

    // ---- Mot phieu nhap va hai hoa don mau ----
    PhieuNhap pn(sinhMaPhieuNhap(), ngayHomNay(), "admin", "NCC001");
    pn.themDong(DongChiTiet("GK001", "Toan 12 - Tap 1", 30, 26000));
    pn.themDong(DongChiTiet("TN001", "Doraemon Tap 1", 50, 18000));
    ghiNhanPhieuNhap(pn);

    HoaDon hd1(sinhMaHoaDon(), ngayHomNay(), "admin", "KH001", 0.02);
    hd1.themDong(DongChiTiet("VH002", "Nha Gia Kim", 2, 79000 * 0.95));
    hd1.themDong(DongChiTiet("TN001", "Doraemon Tap 1", 5, 25000 * 0.85));
    ghiNhanHoaDon(hd1);

    HoaDon hd2(sinhMaHoaDon(), ngayHomNay(), "nv01", "", 0.0);
    hd2.themDong(DongChiTiet("GK001", "Toan 12 - Tap 1", 3, 35000 * 0.90));
    ghiNhanHoaDon(hd2);
}
