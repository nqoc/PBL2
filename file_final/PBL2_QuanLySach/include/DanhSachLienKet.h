// =====================================================================
//  DanhSachLienKet.h - Danh sach lien ket don tu cai dat
//  Dung cho: lich su thao tac, cac chuoi noi ket, hang doi...
// =====================================================================
#ifndef DANHSACHLIENKET_H
#define DANHSACHLIENKET_H

#include <cstddef>
#include "NgoaiLe.h"

template <class T>
class DanhSachLienKet {
private:
    struct Nut {
        T    duLieu;
        Nut* tiep;
        Nut(const T& x) : duLieu(x), tiep(0) {}
    };

    Nut*        dau;
    Nut*        cuoi;
    std::size_t soPhanTu;

public:
    DanhSachLienKet();
    DanhSachLienKet(const DanhSachLienKet<T>& khac);
    DanhSachLienKet<T>& operator=(const DanhSachLienKet<T>& khac);
    ~DanhSachLienKet();

    std::size_t kichThuoc() const { return soPhanTu; }
    bool        rong()      const { return soPhanTu == 0; }

    void themCuoi(const T& x);
    void themDau(const T& x);
    bool xoaDau();
    bool xoaTaiViTri(std::size_t i);
    void xoaHet();

    T&       tai(std::size_t i);
    const T& tai(std::size_t i) const;

    // Lop bo duyet don gian de dung duoc vong for-range
    class BoDuyet {
        Nut* hienTai;
    public:
        BoDuyet(Nut* p) : hienTai(p) {}
        T&       operator*()  const { return hienTai->duLieu; }
        BoDuyet& operator++()       { hienTai = hienTai->tiep; return *this; }
        bool operator!=(const BoDuyet& k) const { return hienTai != k.hienTai; }
    };
    BoDuyet begin() const { return BoDuyet(dau); }
    BoDuyet end()   const { return BoDuyet(0); }
};

// =====================  CAI DAT  =====================

template <class T>
DanhSachLienKet<T>::DanhSachLienKet() : dau(0), cuoi(0), soPhanTu(0) {}

template <class T>
DanhSachLienKet<T>::DanhSachLienKet(const DanhSachLienKet<T>& khac)
    : dau(0), cuoi(0), soPhanTu(0) {
    for (Nut* p = khac.dau; p != 0; p = p->tiep) themCuoi(p->duLieu);
}

template <class T>
DanhSachLienKet<T>& DanhSachLienKet<T>::operator=(const DanhSachLienKet<T>& khac) {
    if (this == &khac) return *this;
    xoaHet();
    for (Nut* p = khac.dau; p != 0; p = p->tiep) themCuoi(p->duLieu);
    return *this;
}

template <class T>
DanhSachLienKet<T>::~DanhSachLienKet() { xoaHet(); }

template <class T>
void DanhSachLienKet<T>::themCuoi(const T& x) {
    Nut* moi = new Nut(x);
    if (dau == 0) { dau = moi; cuoi = moi; }
    else          { cuoi->tiep = moi; cuoi = moi; }
    ++soPhanTu;
}

template <class T>
void DanhSachLienKet<T>::themDau(const T& x) {
    Nut* moi = new Nut(x);
    moi->tiep = dau;
    dau = moi;
    if (cuoi == 0) cuoi = moi;
    ++soPhanTu;
}

template <class T>
bool DanhSachLienKet<T>::xoaDau() {
    if (dau == 0) return false;
    Nut* bo = dau;
    dau = dau->tiep;
    if (dau == 0) cuoi = 0;
    delete bo;
    --soPhanTu;
    return true;
}

template <class T>
bool DanhSachLienKet<T>::xoaTaiViTri(std::size_t i) {
    if (i >= soPhanTu) return false;
    if (i == 0) return xoaDau();
    Nut* truoc = dau;
    for (std::size_t k = 0; k + 1 < i; ++k) truoc = truoc->tiep;
    Nut* bo = truoc->tiep;
    truoc->tiep = bo->tiep;
    if (bo == cuoi) cuoi = truoc;
    delete bo;
    --soPhanTu;
    return true;
}

template <class T>
void DanhSachLienKet<T>::xoaHet() {
    Nut* p = dau;
    while (p != 0) { Nut* t = p->tiep; delete p; p = t; }
    dau = 0; cuoi = 0; soPhanTu = 0;
}

template <class T>
T& DanhSachLienKet<T>::tai(std::size_t i) {
    if (i >= soPhanTu) throw LoiDuLieu("Chi so vuot ngoai danh sach lien ket.");
    Nut* p = dau;
    for (std::size_t k = 0; k < i; ++k) p = p->tiep;
    return p->duLieu;
}

template <class T>
const T& DanhSachLienKet<T>::tai(std::size_t i) const {
    if (i >= soPhanTu) throw LoiDuLieu("Chi so vuot ngoai danh sach lien ket.");
    Nut* p = dau;
    for (std::size_t k = 0; k < i; ++k) p = p->tiep;
    return p->duLieu;
}

#endif // DANHSACHLIENKET_H
