// =====================================================================
//  NhaCungCap.h - Lop dan xuat tu Nguoi: nha cung cap sach
// =====================================================================
#ifndef NHACUNGCAP_H
#define NHACUNGCAP_H

#include "Nguoi.h"

class NhaCungCap : public Nguoi {
private:
    std::string maSoThue;

public:
    NhaCungCap();
    NhaCungCap(const std::string& ma, const std::string& tenCongTy,
               const std::string& sdt, const std::string& diaChi,
               const std::string& email, const std::string& mst = "");

    std::string getMaSoThue() const { return maSoThue; }
    void        setMaSoThue(const std::string& s) { maSoThue = s; }

    std::string vaiTro() const;
    void        nhap();
    void        xuatChiTiet() const;
    void        xuatDong()    const;
    std::string toCSV()       const;
    void        fromCSV(const std::vector<std::string>& p);
};

#endif // NHACUNGCAP_H
