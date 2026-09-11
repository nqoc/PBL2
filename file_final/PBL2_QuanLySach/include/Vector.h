// =====================================================================
//  Vector.h - Mang dong tu cai dat (thay cho std::vector)
//  Minh hoa: class template, quan ly bo nho dong, "quy tac ba"
//            (destructor - copy constructor - toan tu gan)
// =====================================================================
#ifndef VECTOR_H
#define VECTOR_H

#include <cstddef>
#include <sstream>
#include "NgoaiLe.h"

template <class T>
class Vector {
private:
    T*          duLieu;      // vung nho dong chua cac phan tu
    std::size_t soPhanTu;    // so phan tu dang su dung  (size)
    std::size_t dungLuong;   // so o da cap phat          (capacity)

    void baoDamChua(std::size_t canCo);   // cap phat lai khi thieu cho

public:
    // ---------- Khoi tao / huy ----------
    Vector();
    Vector(const Vector<T>& khac);              // copy constructor
    Vector<T>& operator=(const Vector<T>& khac); // toan tu gan
    ~Vector();

    // ---------- Truy van ----------
    std::size_t kichThuoc() const { return soPhanTu; }
    std::size_t sucChua()   const { return dungLuong; }
    bool        rong()      const { return soPhanTu == 0; }

    // ---------- Truy cap ----------
    T&       operator[](std::size_t i)       { return duLieu[i]; }
    const T& operator[](std::size_t i) const { return duLieu[i]; }
    T&       tai(std::size_t i);              // co kiem tra chi so
    const T& tai(std::size_t i) const;

    // ---------- Thay doi noi dung ----------
    void them(const T& x);                    // them vao cuoi
    Vector<T>& operator+=(const T& x);        // them vao cuoi (dang toan tu)
    void chen(std::size_t i, const T& x);     // chen tai vi tri i
    void xoaTaiViTri(std::size_t i);
    void xoaCuoi();
    void xoaHet();
    void doCho(std::size_t i, std::size_t j);
    void datLai(std::size_t i, const T& x)    { duLieu[i] = x; }

    // ---------- Ho tro vong lap for-range ----------
    T*       begin()       { return duLieu; }
    T*       end()         { return duLieu + soPhanTu; }
    const T* begin() const { return duLieu; }
    const T* end()   const { return duLieu + soPhanTu; }
};

// =====================  CAI DAT  =====================

template <class T>
Vector<T>::Vector() : duLieu(0), soPhanTu(0), dungLuong(0) {}

template <class T>
Vector<T>::Vector(const Vector<T>& khac)
    : duLieu(0), soPhanTu(0), dungLuong(0) {
    baoDamChua(khac.soPhanTu);
    for (std::size_t i = 0; i < khac.soPhanTu; ++i) duLieu[i] = khac.duLieu[i];
    soPhanTu = khac.soPhanTu;
}

template <class T>
Vector<T>& Vector<T>::operator=(const Vector<T>& khac) {
    if (this == &khac) return *this;            // tu gan cho chinh minh
    delete[] duLieu;
    duLieu = 0; soPhanTu = 0; dungLuong = 0;
    baoDamChua(khac.soPhanTu);
    for (std::size_t i = 0; i < khac.soPhanTu; ++i) duLieu[i] = khac.duLieu[i];
    soPhanTu = khac.soPhanTu;
    return *this;
}

template <class T>
Vector<T>::~Vector() { delete[] duLieu; }

template <class T>
void Vector<T>::baoDamChua(std::size_t canCo) {
    if (canCo <= dungLuong) return;
    std::size_t moi = (dungLuong == 0) ? 4 : dungLuong * 2;
    while (moi < canCo) moi *= 2;
    T* vungMoi = new T[moi];
    for (std::size_t i = 0; i < soPhanTu; ++i) vungMoi[i] = duLieu[i];
    delete[] duLieu;
    duLieu    = vungMoi;
    dungLuong = moi;
}

template <class T>
T& Vector<T>::tai(std::size_t i) {
    if (i >= soPhanTu) {
        std::ostringstream os; os << "Chi so " << i << " vuot ngoai mang.";
        throw LoiDuLieu(os.str());
    }
    return duLieu[i];
}

template <class T>
const T& Vector<T>::tai(std::size_t i) const {
    if (i >= soPhanTu) {
        std::ostringstream os; os << "Chi so " << i << " vuot ngoai mang.";
        throw LoiDuLieu(os.str());
    }
    return duLieu[i];
}

template <class T>
void Vector<T>::them(const T& x) {
    baoDamChua(soPhanTu + 1);
    duLieu[soPhanTu++] = x;
}

template <class T>
Vector<T>& Vector<T>::operator+=(const T& x) { them(x); return *this; }

template <class T>
void Vector<T>::chen(std::size_t i, const T& x) {
    if (i > soPhanTu) throw LoiDuLieu("Vi tri chen khong hop le.");
    baoDamChua(soPhanTu + 1);
    for (std::size_t j = soPhanTu; j > i; --j) duLieu[j] = duLieu[j - 1];
    duLieu[i] = x;
    ++soPhanTu;
}

template <class T>
void Vector<T>::xoaTaiViTri(std::size_t i) {
    if (i >= soPhanTu) throw LoiDuLieu("Vi tri xoa khong hop le.");
    for (std::size_t j = i; j + 1 < soPhanTu; ++j) duLieu[j] = duLieu[j + 1];
    --soPhanTu;
}

template <class T>
void Vector<T>::xoaCuoi() { if (soPhanTu > 0) --soPhanTu; }

template <class T>
void Vector<T>::xoaHet() { soPhanTu = 0; }

template <class T>
void Vector<T>::doCho(std::size_t i, std::size_t j) {
    T tam = duLieu[i]; duLieu[i] = duLieu[j]; duLieu[j] = tam;
}

#endif // VECTOR_H
