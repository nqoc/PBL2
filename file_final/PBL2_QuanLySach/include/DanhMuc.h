// =====================================================================
//  DanhMuc.h - Cay ke thua thu hai cua he thong:
//      DanhMuc (truu tuong)  ->  TheLoai / TacGia / NhaXuatBan
//  Day la cac "danh muc" ma moi dau sach se tham chieu den.
// =====================================================================
#ifndef DANHMUC_H
#define DANHMUC_H

#include <string>
#include <vector>

// ---------------------------------------------------------------------
//  Lop co so truu tuong
// ---------------------------------------------------------------------
class DanhMuc {
protected:
    std::string ma;
    std::string ten;
    std::string moTa;

public:
    DanhMuc();
    DanhMuc(const std::string& ma, const std::string& ten,
            const std::string& moTa = "");
    virtual ~DanhMuc();

    std::string getMa()   const { return ma; }
    std::string getTen()  const { return ten; }
    std::string getMoTa() const { return moTa; }

    void setMa(const std::string& s)   { ma = s; }
    void setTen(const std::string& s)  { ten = s; }
    void setMoTa(const std::string& s) { moTa = s; }

    // Ham thuan ao -> DanhMuc la lop truu tuong, khong tao doi tuong duoc
    virtual std::string loai() const = 0;

    virtual void        nhap();
    virtual void        xuatChiTiet() const;
    virtual void        xuatDong()    const;
    virtual std::string toCSV()       const;
    virtual void        fromCSV(const std::vector<std::string>& p);
};

// ---------------------------------------------------------------------
//  1) The loai sach - lop con khong them du lieu, chi dinh nghia loai()
// ---------------------------------------------------------------------
class TheLoai : public DanhMuc {
public:
    TheLoai();
    TheLoai(const std::string& ma, const std::string& ten,
            const std::string& moTa = "");
    std::string loai() const;
};

// ---------------------------------------------------------------------
//  2) Tac gia - them thuoc tinh quoc tich
// ---------------------------------------------------------------------
class TacGia : public DanhMuc {
private:
    std::string quocTich;

public:
    TacGia();
    TacGia(const std::string& ma, const std::string& ten,
           const std::string& quocTich, const std::string& moTa = "");

    std::string getQuocTich() const { return quocTich; }
    void        setQuocTich(const std::string& s) { quocTich = s; }

    std::string loai() const;
    void        nhap();
    void        xuatChiTiet() const;
    void        xuatDong()    const;
    std::string toCSV()       const;
    void        fromCSV(const std::vector<std::string>& p);
};

// ---------------------------------------------------------------------
//  3) Nha xuat ban - them dia chi va dien thoai
// ---------------------------------------------------------------------
class NhaXuatBan : public DanhMuc {
private:
    std::string diaChi;
    std::string dienThoai;

public:
    NhaXuatBan();
    NhaXuatBan(const std::string& ma, const std::string& ten,
               const std::string& diaChi, const std::string& dienThoai,
               const std::string& moTa = "");

    std::string getDiaChi()    const { return diaChi; }
    std::string getDienThoai() const { return dienThoai; }
    void        setDiaChi(const std::string& s)    { diaChi = s; }
    void        setDienThoai(const std::string& s) { dienThoai = s; }

    std::string loai() const;
    void        nhap();
    void        xuatChiTiet() const;
    void        xuatDong()    const;
    std::string toCSV()       const;
    void        fromCSV(const std::vector<std::string>& p);
};

#endif // DANHMUC_H
