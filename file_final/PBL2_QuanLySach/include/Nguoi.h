// =====================================================================
//  Nguoi.h - Lop co so truu tuong cho moi doi tuong "la con nguoi"
//  Cay ke thua:  Nguoi  ->  KhachHang / NhaCungCap / TaiKhoan
// =====================================================================
#ifndef NGUOI_H
#define NGUOI_H

#include <string>
#include <vector>

class Nguoi {
protected:
    std::string ma;             // ma dinh danh (duy nhat)
    std::string hoTen;
    std::string soDienThoai;
    std::string diaChi;
    std::string email;

public:
    Nguoi();
    Nguoi(const std::string& ma, const std::string& hoTen,
          const std::string& sdt, const std::string& diaChi,
          const std::string& email);
    virtual ~Nguoi() ; 
    // ---------- Getter / Setter (dong goi) ----------
    std::string getMa()    const { return ma; }
    std::string getTen()   const { return hoTen; }
    std::string getSDT()   const { return soDienThoai; }
    std::string getDiaChi() const { return diaChi; }
    std::string getEmail() const { return email; }

    void setMa(const std::string& s)    { ma = s; }
    void setTen(const std::string& s)   { hoTen = s; }
    void setSDT(const std::string& s);          // kiem tra so dien thoai
    void setDiaChi(const std::string& s) { diaChi = s; }
    void setEmail(const std::string& s);        // kiem tra dinh dang email

    // ---------- Ham thuan ao: lop con BUOC PHAI dinh nghia ----------
    virtual std::string vaiTro() const = 0;

    // ---------- Ham ao: lop con CO THE ghi de (override) ----------
    virtual void        nhap();
    virtual void        xuatChiTiet() const;
    virtual void        xuatDong()    const;
    virtual std::string toCSV()       const;
    virtual void        fromCSV(const std::vector<std::string>& p);
};

#endif // NGUOI_H
