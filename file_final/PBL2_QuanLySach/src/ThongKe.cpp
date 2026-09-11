// =====================================================================
//  ThongKe.cpp - Cai dat cac ham thong ke / bao cao cua CuaHang
// =====================================================================
#include "CuaHang.h"
#include "ThuatToan.h"
#include "TienIch.h"
#include "NgoaiLe.h"
#include "BangBam.h"

#include <fstream>
#include <sstream>
#include <iomanip>
#include <cstdlib>

using namespace std;

// =====================  Ham so sanh  =====================
bool bcTheoSoLuongGiam(const MucBanChay& a, const MucBanChay& b) {
    if (a.soLuongBan != b.soLuongBan) return a.soLuongBan > b.soLuongBan;
    return a.doanhThu > b.doanhThu;
}

bool bcTheoDoanhThuGiam(const MucBanChay& a, const MucBanChay& b) {
    return a.doanhThu > b.doanhThu;
}

// Doi mot "moc" thanh so de so sanh: "dd/mm/yyyy" hoac "mm/yyyy"
static long soHoaMoc(const string& moc) {
    vector<string> p = tachChuoi(moc, '/');
    if (p.size() == 3) return soHoaNgay(moc);
    if (p.size() == 2) return atol(p[1].c_str()) * 100L + atol(p[0].c_str());
    return 0;
}

bool dtTheoMocTang(const MucDoanhThu& a, const MucDoanhThu& b) {
    return soHoaMoc(a.moc) < soHoaMoc(b.moc);
}

// =====================  Doanh thu  =====================
double CuaHang::doanhThuTheoNgay(const string& ngay) const {
    double t = 0;
    const Vector<HoaDon>& ds = khoHoaDon.duLieu();
    for (size_t i = 0; i < ds.kichThuoc(); ++i)
        if (ds[i].getNgay() == ngay) t += ds[i].thanhToan();
    return t;
}

double CuaHang::doanhThuTheoThang(const string& thang) const {
    double t = 0;
    const Vector<HoaDon>& ds = khoHoaDon.duLieu();
    for (size_t i = 0; i < ds.kichThuoc(); ++i)
        if (thangCuaNgay(ds[i].getNgay()) == thang) t += ds[i].thanhToan();
    return t;
}

double CuaHang::doanhThuTheoKhoang(const string& tu, const string& den,
                                   int& soHoaDon) const {
    long a = soHoaNgay(tu), b = soHoaNgay(den);
    if (a > b) { long t = a; a = b; b = t; }
    double tong = 0;
    soHoaDon = 0;
    const Vector<HoaDon>& ds = khoHoaDon.duLieu();
    for (size_t i = 0; i < ds.kichThuoc(); ++i) {
        long n = soHoaNgay(ds[i].getNgay());
        if (n >= a && n <= b) { tong += ds[i].thanhToan(); ++soHoaDon; }
    }
    return tong;
}

double CuaHang::tongDoanhThu() const {
    double t = 0;
    const Vector<HoaDon>& ds = khoHoaDon.duLieu();
    for (size_t i = 0; i < ds.kichThuoc(); ++i) t += ds[i].thanhToan();
    return t;
}

double CuaHang::tongChiNhapHang() const {
    double t = 0;
    const Vector<PhieuNhap>& ds = khoPhieuNhap.duLieu();
    for (size_t i = 0; i < ds.kichThuoc(); ++i) t += ds[i].thanhToan();
    return t;
}

// =====================  Bang doanh thu theo moc thoi gian  =====================
Vector<MucDoanhThu> CuaHang::bangDoanhThuTheoNgay() const {
    Vector<MucDoanhThu> kq;
    BangBam<int>        viTri;             // moc -> chi so trong kq
    const Vector<HoaDon>& ds = khoHoaDon.duLieu();
    for (size_t i = 0; i < ds.kichThuoc(); ++i) {
        string moc = ds[i].getNgay();
        int    vt;
        if (!viTri.lay(moc, vt)) {
            kq.them(MucDoanhThu(moc));
            vt = static_cast<int>(kq.kichThuoc()) - 1;
            viTri.dat(moc, vt);
        }
        kq[static_cast<size_t>(vt)].soHoaDon += 1;
        kq[static_cast<size_t>(vt)].doanhThu += ds[i].thanhToan();
    }
    quickSort(kq, dtTheoMocTang);
    return kq;
}

Vector<MucDoanhThu> CuaHang::bangDoanhThuTheoThang() const {
    Vector<MucDoanhThu> kq;
    BangBam<int>        viTri;
    const Vector<HoaDon>& ds = khoHoaDon.duLieu();
    for (size_t i = 0; i < ds.kichThuoc(); ++i) {
        string moc = thangCuaNgay(ds[i].getNgay());
        int    vt;
        if (!viTri.lay(moc, vt)) {
            kq.them(MucDoanhThu(moc));
            vt = static_cast<int>(kq.kichThuoc()) - 1;
            viTri.dat(moc, vt);
        }
        kq[static_cast<size_t>(vt)].soHoaDon += 1;
        kq[static_cast<size_t>(vt)].doanhThu += ds[i].thanhToan();
    }
    quickSort(kq, dtTheoMocTang);
    return kq;
}

// =====================  Sach ban chay  =====================
Vector<MucBanChay> CuaHang::bangSachBanChay() const {
    Vector<MucBanChay> kq;
    BangBam<int>       viTri;
    const Vector<HoaDon>& ds = khoHoaDon.duLieu();
    for (size_t i = 0; i < ds.kichThuoc(); ++i) {
        const Vector<DongChiTiet>& dong = ds[i].cacDong();
        for (size_t j = 0; j < dong.kichThuoc(); ++j) {
            string ma = dong[j].getMaSach();
            int    vt;
            if (!viTri.lay(ma, vt)) {
                kq.them(MucBanChay(ma, dong[j].getTenSach()));
                vt = static_cast<int>(kq.kichThuoc()) - 1;
                viTri.dat(ma, vt);
            }
            kq[static_cast<size_t>(vt)].soLuongBan += dong[j].getSoLuong();
            kq[static_cast<size_t>(vt)].doanhThu   += dong[j].thanhTien();
        }
    }
    quickSort(kq, bcTheoSoLuongGiam);
    return kq;
}

// =====================  The loai ua chuong  =====================
Vector<MucBanChay> CuaHang::bangTheLoaiUaChuong() const {
    Vector<MucBanChay> kq;
    BangBam<int>       viTri;
    const Vector<HoaDon>& ds = khoHoaDon.duLieu();
    for (size_t i = 0; i < ds.kichThuoc(); ++i) {
        const Vector<DongChiTiet>& dong = ds[i].cacDong();
        for (size_t j = 0; j < dong.kichThuoc(); ++j) {
            Sach* s = khoSach.timTheoMa(dong[j].getMaSach());
            string maTL = (s != 0) ? s->getMaTheLoai() : string("(khong ro)");
            int    vt;
            if (!viTri.lay(maTL, vt)) {
                kq.them(MucBanChay(maTL, tenTheLoai(maTL)));
                vt = static_cast<int>(kq.kichThuoc()) - 1;
                viTri.dat(maTL, vt);
            }
            kq[static_cast<size_t>(vt)].soLuongBan += dong[j].getSoLuong();
            kq[static_cast<size_t>(vt)].doanhThu   += dong[j].thanhTien();
        }
    }
    quickSort(kq, bcTheoSoLuongGiam);
    return kq;
}

// =====================  Tra cuu chung tu  =====================
Vector<HoaDon> CuaHang::hoaDonTheoNgay(const string& ngay) const {
    Vector<HoaDon> kq;
    const Vector<HoaDon>& ds = khoHoaDon.duLieu();
    for (size_t i = 0; i < ds.kichThuoc(); ++i)
        if (ds[i].getNgay() == ngay) kq.them(ds[i]);
    return kq;
}

Vector<HoaDon> CuaHang::hoaDonTheoKhach(const string& maKH) const {
    Vector<HoaDon> kq;
    const Vector<HoaDon>& ds = khoHoaDon.duLieu();
    for (size_t i = 0; i < ds.kichThuoc(); ++i)
        if (veThuong(ds[i].getMaKhachHang()) == veThuong(maKH)) kq.them(ds[i]);
    return kq;
}

Vector<PhieuNhap> CuaHang::phieuNhapTheoNgay(const string& ngay) const {
    Vector<PhieuNhap> kq;
    const Vector<PhieuNhap>& ds = khoPhieuNhap.duLieu();
    for (size_t i = 0; i < ds.kichThuoc(); ++i)
        if (ds[i].getNgay() == ngay) kq.them(ds[i]);
    return kq;
}

Vector<PhieuNhap> CuaHang::phieuNhapTheoNCC(const string& maNCC) const {
    Vector<PhieuNhap> kq;
    const Vector<PhieuNhap>& ds = khoPhieuNhap.duLieu();
    for (size_t i = 0; i < ds.kichThuoc(); ++i)
        if (veThuong(ds[i].getMaNhaCungCap()) == veThuong(maNCC)) kq.them(ds[i]);
    return kq;
}

// =====================  Xuat bao cao ra tep  =====================
void CuaHang::xuatBaoCaoRaTep(const string& tenTep) const {
    ofstream f(tenTep.c_str());
    if (!f) throw LoiFile("Khong ghi duoc tep bao cao " + tenTep);

    f << "==============================================================\n";
    f << "                BAO CAO KINH DOANH - " << tenCuaHang << "\n";
    f << "                Ngay lap bao cao: " << ngayHomNay() << "\n";
    f << "==============================================================\n\n";

    f << "1. TONG QUAN\n";
    f << "   - So dau sach            : " << khoSach.soDauSach() << "\n";
    f << "   - Tong so cuon ton kho   : " << khoSach.tongSoCuonTon() << "\n";
    f << "   - Gia tri hang ton kho   : "
      << dinhDangTien(khoSach.tongGiaTriTonKho()) << " VND\n";
    f << "   - So the loai / tac gia / NXB : " << khoTheLoai.soLuong() << " / "
      << khoTacGia.soLuong() << " / " << khoNXB.soLuong() << "\n";
    f << "   - So khach hang          : " << khoKhachHang.soLuong() << "\n";
    f << "   - So nha cung cap        : " << khoNhaCungCap.soLuong() << "\n";
    f << "   - So hoa don             : " << khoHoaDon.soLuong() << "\n";
    f << "   - So phieu nhap          : " << khoPhieuNhap.soLuong() << "\n";
    f << "   - Tong doanh thu         : " << dinhDangTien(tongDoanhThu())
      << " VND\n";
    f << "   - Tong chi nhap hang     : " << dinhDangTien(tongChiNhapHang())
      << " VND\n";
    f << "   - Chenh lech (thu - chi) : "
      << dinhDangTien(tongDoanhThu() - tongChiNhapHang()) << " VND\n\n";

    f << "2. DOANH THU THEO NGAY\n";
    Vector<MucDoanhThu> theoNgay = bangDoanhThuTheoNgay();
    f << "   " << left << setw(14) << "NGAY" << right << setw(10) << "SO HD"
      << right << setw(20) << "DOANH THU" << "\n";
    for (size_t i = 0; i < theoNgay.kichThuoc(); ++i)
        f << "   " << left << setw(14) << theoNgay[i].moc
          << right << setw(10) << theoNgay[i].soHoaDon
          << right << setw(20) << dinhDangTien(theoNgay[i].doanhThu) << "\n";
    f << "\n";

    f << "3. DOANH THU THEO THANG\n";
    Vector<MucDoanhThu> theoThang = bangDoanhThuTheoThang();
    f << "   " << left << setw(14) << "THANG" << right << setw(10) << "SO HD"
      << right << setw(20) << "DOANH THU" << "\n";
    for (size_t i = 0; i < theoThang.kichThuoc(); ++i)
        f << "   " << left << setw(14) << theoThang[i].moc
          << right << setw(10) << theoThang[i].soHoaDon
          << right << setw(20) << dinhDangTien(theoThang[i].doanhThu) << "\n";
    f << "\n";

    f << "4. TOP SACH BAN CHAY\n";
    Vector<MucBanChay> banChay = bangSachBanChay();
    f << "   " << left << setw(10) << "MA" << left << setw(34) << "TEN SACH"
      << right << setw(8) << "SL" << right << setw(18) << "DOANH THU" << "\n";
    for (size_t i = 0; i < banChay.kichThuoc() && i < 10; ++i)
        f << "   " << left << setw(10) << banChay[i].ma
          << left << setw(34) << catBot(banChay[i].ten, 33)
          << right << setw(8) << banChay[i].soLuongBan
          << right << setw(18) << dinhDangTien(banChay[i].doanhThu) << "\n";
    f << "\n";

    f << "5. THE LOAI DUOC MUA NHIEU NHAT\n";
    Vector<MucBanChay> theLoaiTop = bangTheLoaiUaChuong();
    for (size_t i = 0; i < theLoaiTop.kichThuoc(); ++i)
        f << "   " << left << setw(10) << theLoaiTop[i].ma
          << left << setw(30) << catBot(theLoaiTop[i].ten, 29)
          << right << setw(8) << theLoaiTop[i].soLuongBan << " cuon"
          << right << setw(18) << dinhDangTien(theLoaiTop[i].doanhThu) << "\n";
    f << "\n";

    f << "6. CANH BAO SACH SAP HET (ton <= " << nguongCanhBao << ")\n";
    Vector<Sach*> sapHet = khoSach.sachSapHet(nguongCanhBao);
    if (sapHet.rong()) f << "   Khong co dau sach nao duoi nguong.\n";
    for (size_t i = 0; i < sapHet.kichThuoc(); ++i)
        f << "   " << left << setw(10) << sapHet[i]->getMa()
          << left << setw(36) << catBot(sapHet[i]->getTen(), 35)
          << right << setw(6) << sapHet[i]->getSoLuong() << " cuon\n";

    f << "\n=========== HET BAO CAO ===========\n";
    f.close();
}
