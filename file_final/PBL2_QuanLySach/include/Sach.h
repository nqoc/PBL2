// =====================================================================
//  Sach.h - Lop co so TRUU TUONG cho moi loai sach trong cua hang
//  Cay ke thua: Sach -> SachGiaoKhoa / SachVanHoc / SachThieuNhi
//
//  Moi dau sach tham chieu den 3 danh muc bang MA:
//      maTacGia  -> TacGia
//      maTheLoai -> TheLoai
//      maNXB     -> NhaXuatBan
// =====================================================================
#ifndef SACH_H
#define SACH_H

#include <string>
#include <vector>
#include <iostream>

class Sach {
protected:
    std::string maSach;
    std::string tenSach;
    std::string maTacGia;
    std::string maTheLoai;
    std::string maNXB;
    int         namXuatBan;
    double      giaNhap;      // gia mua vao tu nha cung cap
    double      giaBan;       // gia niem yet
    int         soLuongTon;
    std::string viTriKe;      // vi tri tren ke, vi du "A1-03"
    std::string moTa;

public:
    Sach();
    Sach(const std::string& ma, const std::string& ten,
         const std::string& maTG, const std::string& maTL,
         const std::string& maNXB, int nam,
         double giaNhap, double giaBan, int soLuong,
         const std::string& viTriKe = "", const std::string& moTa = "");
    virtual ~Sach();

    // ---------- Getter ----------
    std::string getMa()        const { return maSach; }
    std::string getTen()       const { return tenSach; }
    std::string getMaTacGia()  const { return maTacGia; }
    std::string getMaTheLoai() const { return maTheLoai; }
    std::string getMaNXB()     const { return maNXB; }
    int         getNamXB()     const { return namXuatBan; }
    double      getGiaNhap()   const { return giaNhap; }
    double      getGiaBan()    const { return giaBan; }
    int         getSoLuong()   const { return soLuongTon; }
    std::string getViTriKe()   const { return viTriKe; }
    std::string getMoTa()      const { return moTa; }

    // ---------- Setter co kiem tra rang buoc ----------
    void setMa(const std::string& s)        { maSach = s; }
    void setTen(const std::string& s);
    void setMaTacGia(const std::string& s)  { maTacGia = s; }
    void setMaTheLoai(const std::string& s) { maTheLoai = s; }
    void setMaNXB(const std::string& s)     { maNXB = s; }
    void setNamXB(int n);
    void setGiaNhap(double g);
    void setGiaBan(double g);
    void setSoLuong(int sl);
    void setViTriKe(const std::string& s)   { viTriKe = s; }
    void setMoTa(const std::string& s)      { moTa = s; }

    // ---------- Nghiep vu chung cho moi loai sach ----------
    void   nhapThemKho(int sl);            // cong ton kho khi nhap hang
    void   banBotKho(int sl);              // tru ton kho khi ban (nem LoiTonKho)
    double giaTriTonKho() const;           // giaNhap * soLuongTon
    double loiNhuanMotCuon() const;        // giaSauGiam - giaNhap
    bool   sapHetHang(int nguong) const { return soLuongTon <= nguong; }

    // ---------- Ham THUAN AO: lop con bat buoc dinh nghia ----------
    virtual std::string loaiSach() const = 0;   // ten loai de hien thi
    virtual std::string maLoai()   const = 0;   // "GK" / "VH" / "TN"
    virtual Sach*       nhanBan()  const = 0;   // tao ban sao (clone)

    // ---------- Ham AO: lop con co the ghi de ----------
    virtual double      tiLeGiamGia() const;    // % giam theo loai sach
    virtual double      giaSauGiam()  const;    // gia thuc te khi ban
    virtual std::string moTaThem()    const;    // thong tin rieng cua lop con
    virtual void        nhap();
    virtual void        xuatChiTiet() const;
    virtual void        xuatDong()    const;

    // ---------- Ghi / doc file van ban (cac truong cach nhau bang '|') ----------
    virtual std::string toCSV() const;                     // khong gom ma loai
    virtual void        fromCSV(const std::vector<std::string>& p);

    // ---------- Nap chong toan tu ----------
    bool  operator==(const Sach& k) const;      // bang nhau khi cung ma sach
    bool  operator<(const Sach& k)  const;      // so sanh theo gia ban
    Sach& operator+=(int sl);                   // nhap them hang
    friend std::ostream& operator<<(std::ostream& os, const Sach& s);

    // ---------- In tieu de bang danh sach ----------
    static void inTieuDeBang();
};

// Ham xuong (factory): tao doi tuong sach dung loai tu ma loai
Sach* taoSachTheoMaLoai(const std::string& maLoai);

#endif // SACH_H
