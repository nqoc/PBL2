// =====================================================================
//  BangBam.h - Bang bam (hash table), khoa la chuoi.
//  Xu ly va cham bang phuong phap noi ket (separate chaining).
//  Muc dich: tra cuu sach theo ma voi do phuc tap trung binh O(1).
// =====================================================================
#ifndef BANGBAM_H
#define BANGBAM_H

#include <string>
#include <cstddef>

template <class V>
class BangBam {
private:
    struct Nut {
        std::string khoa;
        V           giaTri;
        Nut*        tiep;
        Nut(const std::string& k, const V& v) : khoa(k), giaTri(v), tiep(0) {}
    };

    Nut**       bang;       // mang con tro tro den dau moi chuoi noi ket
    std::size_t soBucket;
    std::size_t demSo;

    // Ham bam chuoi theo so do Horner voi co so 31
    std::size_t bam(const std::string& khoa) const {
        unsigned long h = 0;
        for (std::size_t i = 0; i < khoa.size(); ++i)
            h = h * 31u + static_cast<unsigned char>(khoa[i]);
        return static_cast<std::size_t>(h % soBucket);
    }

    void saoChepTu(const BangBam<V>& khac);

public:
    explicit BangBam(std::size_t n = 211);
    BangBam(const BangBam<V>& khac);
    BangBam<V>& operator=(const BangBam<V>& khac);
    ~BangBam();

    std::size_t kichThuoc() const { return demSo; }
    std::size_t soO()       const { return soBucket; }

    void dat(const std::string& khoa, const V& gt);   // them moi hoac cap nhat
    bool co(const std::string& khoa) const;
    bool lay(const std::string& khoa, V& ketQua) const;
    bool xoa(const std::string& khoa);
    void xoaHet();

    std::size_t chuoiDaiNhat() const;   // danh gia chat luong ham bam
};

// =====================  CAI DAT  =====================

template <class V>
BangBam<V>::BangBam(std::size_t n)
    : bang(0), soBucket(n < 8 ? 8 : n), demSo(0) {
    bang = new Nut*[soBucket];
    for (std::size_t i = 0; i < soBucket; ++i) bang[i] = 0;
}

template <class V>
void BangBam<V>::saoChepTu(const BangBam<V>& khac) {
    soBucket = khac.soBucket;
    demSo    = 0;
    bang     = new Nut*[soBucket];
    for (std::size_t i = 0; i < soBucket; ++i) bang[i] = 0;
    for (std::size_t i = 0; i < khac.soBucket; ++i)
        for (Nut* p = khac.bang[i]; p != 0; p = p->tiep) dat(p->khoa, p->giaTri);
}

template <class V>
BangBam<V>::BangBam(const BangBam<V>& khac) : bang(0), soBucket(8), demSo(0) {
    saoChepTu(khac);
}

template <class V>
BangBam<V>& BangBam<V>::operator=(const BangBam<V>& khac) {
    if (this == &khac) return *this;
    xoaHet();
    delete[] bang;
    bang = 0;
    saoChepTu(khac);
    return *this;
}

template <class V>
BangBam<V>::~BangBam() { xoaHet(); delete[] bang; }

template <class V>
void BangBam<V>::dat(const std::string& khoa, const V& gt) {
    std::size_t i = bam(khoa);
    for (Nut* p = bang[i]; p != 0; p = p->tiep)
        if (p->khoa == khoa) { p->giaTri = gt; return; }
    Nut* moi  = new Nut(khoa, gt);
    moi->tiep = bang[i];
    bang[i]   = moi;
    ++demSo;
}

template <class V>
bool BangBam<V>::co(const std::string& khoa) const {
    for (Nut* p = bang[bam(khoa)]; p != 0; p = p->tiep)
        if (p->khoa == khoa) return true;
    return false;
}

template <class V>
bool BangBam<V>::lay(const std::string& khoa, V& ketQua) const {
    for (Nut* p = bang[bam(khoa)]; p != 0; p = p->tiep)
        if (p->khoa == khoa) { ketQua = p->giaTri; return true; }
    return false;
}

template <class V>
bool BangBam<V>::xoa(const std::string& khoa) {
    std::size_t i = bam(khoa);
    Nut* truoc = 0;
    Nut* p     = bang[i];
    while (p != 0) {
        if (p->khoa == khoa) {
            if (truoc == 0) bang[i]     = p->tiep;
            else            truoc->tiep = p->tiep;
            delete p;
            --demSo;
            return true;
        }
        truoc = p;
        p     = p->tiep;
    }
    return false;
}

template <class V>
void BangBam<V>::xoaHet() {
    if (bang == 0) return;
    for (std::size_t i = 0; i < soBucket; ++i) {
        Nut* p = bang[i];
        while (p != 0) { Nut* t = p->tiep; delete p; p = t; }
        bang[i] = 0;
    }
    demSo = 0;
}

template <class V>
std::size_t BangBam<V>::chuoiDaiNhat() const {
    std::size_t maxLen = 0;
    for (std::size_t i = 0; i < soBucket; ++i) {
        std::size_t d = 0;
        for (Nut* p = bang[i]; p != 0; p = p->tiep) ++d;
        if (d > maxLen) maxLen = d;
    }
    return maxLen;
}

#endif // BANGBAM_H
