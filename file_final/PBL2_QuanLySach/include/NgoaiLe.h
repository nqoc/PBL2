// =====================================================================
//  NgoaiLe.h - Cay lop ngoai le (exception) cua chuong trinh
//  Tat ca ke thua tu std::runtime_error -> dung duoc e.what()
// =====================================================================
#ifndef NGOAILE_H
#define NGOAILE_H

#include <stdexcept>
#include <string>

// Lop goc cho moi loi cua ung dung
class LoiUngDung : public std::runtime_error {
public:
    explicit LoiUngDung(const std::string& tb) : std::runtime_error(tb) {}
};

// Du lieu nhap khong hop le (so am, nam sai, chuoi rong...)
class LoiDuLieu : public LoiUngDung {
public:
    explicit LoiDuLieu(const std::string& tb) : LoiUngDung("[DU LIEU] " + tb) {}
};

// Khong tim thay doi tuong theo ma
class LoiKhongTimThay : public LoiUngDung {
public:
    explicit LoiKhongTimThay(const std::string& tb) : LoiUngDung("[KHONG TIM THAY] " + tb) {}
};

// Ma bi trung khi them moi
class LoiTrungMa : public LoiUngDung {
public:
    explicit LoiTrungMa(const std::string& tb) : LoiUngDung("[TRUNG MA] " + tb) {}
};

// Vi pham rang buoc ton kho (ban nhieu hon so luong con)
class LoiTonKho : public LoiUngDung {
public:
    explicit LoiTonKho(const std::string& tb) : LoiUngDung("[TON KHO] " + tb) {}
};

// Vi pham rang buoc toan ven (xoa danh muc dang duoc tham chieu)
class LoiRangBuoc : public LoiUngDung {
public:
    explicit LoiRangBuoc(const std::string& tb) : LoiUngDung("[RANG BUOC] " + tb) {}
};

// Loi doc/ghi file
class LoiFile : public LoiUngDung {
public:
    explicit LoiFile(const std::string& tb) : LoiUngDung("[FILE] " + tb) {}
};

// Nguoi dung khong du quyen
class LoiPhanQuyen : public LoiUngDung {
public:
    explicit LoiPhanQuyen(const std::string& tb) : LoiUngDung("[PHAN QUYEN] " + tb) {}
};

#endif // NGOAILE_H
