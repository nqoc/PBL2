// =====================================================================
//  ThuatToan.h - Cac thuat toan tim kiem / sap xep tu cai dat
//  Tat ca deu la ham template -> dung cho moi kieu du lieu
//  Do phuc tap:
//     timTuyenTinh : O(n)
//     timNhiPhan   : O(log n)   (yeu cau day da sap xep)
//     quickSort    : O(n log n) trung binh, O(n^2) xau nhat
//     mergeSort    : O(n log n) moi truong hop, can O(n) bo nho phu
// =====================================================================
#ifndef THUATTOAN_H
#define THUATTOAN_H

#include <cstddef>
#include "Vector.h"

// ---------------------------------------------------------------------
// 1) TIM KIEM TUYEN TINH: tra ve chi so phan tu dau tien thoa dieu kien
//    dk la mot vi tu (functor / con tro ham) nhan T va tra ve bool
// ---------------------------------------------------------------------
template <class T, class DieuKien>
long timTuyenTinh(const Vector<T>& a, DieuKien dk) {
    for (std::size_t i = 0; i < a.kichThuoc(); ++i)
        if (dk(a[i])) return static_cast<long>(i);
    return -1;
}

// ---------------------------------------------------------------------
// 2) TIM KIEM NHI PHAN tren Vector da sap xep tang theo khoa
//    layKhoa(T) -> K ;  so sanh bang toan tu < va ==
// ---------------------------------------------------------------------
template <class T, class K, class LayKhoa>
long timNhiPhan(const Vector<T>& a, const K& khoa, LayKhoa layKhoa) {
    long tra  = 0;
    long phai = static_cast<long>(a.kichThuoc()) - 1;
    while (tra <= phai) {
        long giua = tra + (phai - tra) / 2;
        K    kg   = layKhoa(a[static_cast<std::size_t>(giua)]);
        if (kg == khoa)     return giua;
        else if (kg < khoa) tra  = giua + 1;
        else                phai = giua - 1;
    }
    return -1;
}

// ---------------------------------------------------------------------
// 3) QUICK SORT (sap xep nhanh) - chon phan tu giua lam moc
//    cmp(x, y) tra ve true neu x phai dung truoc y
// ---------------------------------------------------------------------
template <class T, class SoSanh>
void quickSortDeQuy(Vector<T>& a, long tra, long phai, SoSanh cmp) {
    if (tra >= phai) return;
    T    moc = a[static_cast<std::size_t>(tra + (phai - tra) / 2)];
    long i = tra, j = phai;
    while (i <= j) {
        while (cmp(a[static_cast<std::size_t>(i)], moc)) ++i;
        while (cmp(moc, a[static_cast<std::size_t>(j)])) --j;
        if (i <= j) {
            a.doCho(static_cast<std::size_t>(i), static_cast<std::size_t>(j));
            ++i; --j;
        }
    }
    quickSortDeQuy(a, tra, j, cmp);
    quickSortDeQuy(a, i, phai, cmp);
}

template <class T, class SoSanh>
void quickSort(Vector<T>& a, SoSanh cmp) {
    if (a.kichThuoc() > 1)
        quickSortDeQuy(a, 0, static_cast<long>(a.kichThuoc()) - 1, cmp);
}

// ---------------------------------------------------------------------
// 4) MERGE SORT (sap xep tron) - on dinh, luon O(n log n)
// ---------------------------------------------------------------------
template <class T, class SoSanh>
void tron(Vector<T>& a, std::size_t tra, std::size_t giua, std::size_t phai,
          Vector<T>& tam, SoSanh cmp) {
    std::size_t i = tra, j = giua + 1, k = tra;
    while (i <= giua && j <= phai) {
        if (cmp(a[j], a[i])) tam.datLai(k++, a[j++]);
        else                 tam.datLai(k++, a[i++]);
    }
    while (i <= giua) tam.datLai(k++, a[i++]);
    while (j <= phai) tam.datLai(k++, a[j++]);
    for (std::size_t t = tra; t <= phai; ++t) a.datLai(t, tam[t]);
}

template <class T, class SoSanh>
void mergeSortDeQuy(Vector<T>& a, std::size_t tra, std::size_t phai,
                    Vector<T>& tam, SoSanh cmp) {
    if (tra >= phai) return;
    std::size_t giua = tra + (phai - tra) / 2;
    mergeSortDeQuy(a, tra, giua, tam, cmp);
    mergeSortDeQuy(a, giua + 1, phai, tam, cmp);
    tron(a, tra, giua, phai, tam, cmp);
}

template <class T, class SoSanh>
void mergeSort(Vector<T>& a, SoSanh cmp) {
    if (a.kichThuoc() < 2) return;
    Vector<T> tam(a);            // ban sao lam vung nho phu
    mergeSortDeQuy(a, 0, a.kichThuoc() - 1, tam, cmp);
}

#endif // THUATTOAN_H
