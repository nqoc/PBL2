// =====================================================================
//  TienIch.h - Cac ham tien ich dung chung:
//              nhap lieu an toan, xu ly chuoi, xu ly ngay, dinh dang
// =====================================================================
#ifndef TIENICH_H
#define TIENICH_H

#include <string>
#include <vector>

// ---------- Nhap lieu an toan: lap lai cho den khi hop le ----------
namespace Nhap {
    std::string chuoi(const std::string& thongBao, bool choPhepRong = false);
    int         soNguyen(const std::string& thongBao, int nhoNhat, int lonNhat);
    double      soThuc(const std::string& thongBao, double nhoNhat, double lonNhat);
    bool        xacNhan(const std::string& thongBao);
    // Nhap ngay dd/mm/yyyy; go Enter de lay ngay hom nay
    std::string ngay(const std::string& thongBao);
    // Nhap mat khau (khong hien thi ky tu tren Windows)
    std::string matKhau(const std::string& thongBao);
}

// ---------- Xu ly chuoi ----------
std::vector<std::string> tachChuoi(const std::string& s, char nganCach);
std::string veThuong(std::string s);
std::string chuanHoa(const std::string& s);                 // cat khoang trang 2 dau
std::string catBot(const std::string& s, std::size_t n);    // cat cho vua o bang
std::string locKyTu(const std::string& s);                  // bo ky tu | va # (de an toan file)
bool        chuaChuoiCon(const std::string& nguon, const std::string& tuKhoa);
std::string bamMatKhau(const std::string& mk);              // bam mat khau (khong the giai)

// ---------- Xu ly so / ngay ----------
std::string dinhDangTien(double v);            // 1234567 -> "1.234.567"
std::string ngayHomNay();                      // "dd/mm/yyyy"
bool        ngayHopLe(const std::string& d);
long        soHoaNgay(const std::string& d);   // dd/mm/yyyy -> yyyymmdd (de so sanh)
std::string thangCuaNgay(const std::string& d);// "mm/yyyy"
std::string doiSangChuoi(int v);
std::string doiSangChuoi(double v, int soLeThapPhan = 0);

// ---------- Trinh bay man hinh ----------
namespace Man {
    void duong(char c = '-', int n = 100);
    void tieuDe(const std::string& tieuDe);
    void dungCho();                            // "Nhan Enter de tiep tuc"
    void xoaManHinh();
    void bieuDoCot(const std::string& nhan, double giaTri, double giaTriLonNhat,
                   int doDaiToiDa = 40);
}

#endif // TIENICH_H
