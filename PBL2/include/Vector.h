#ifndef VECTOR_TU_TAO_H
#define VECTOR_TU_TAO_H

#include <cstddef>
#include <utility>

// Mang dong don gian: tu quan ly bo nho, khong dung std::vector.
template<class T>
class Vector {
public:
    using size_type = std::size_t;
    using iterator = T*;
    using const_iterator = const T*;

private:
    T* duLieu;
    size_type soLuong;
    size_type sucChua;

    void moRong(size_type sucChuaMoi) {
        if (sucChuaMoi <= sucChua) return;
        T* moi = new T[sucChuaMoi];
        for (size_type i = 0; i < soLuong; ++i) moi[i] = duLieu[i];
        delete[] duLieu;
        duLieu = moi;
        sucChua = sucChuaMoi;
    }

public:
    Vector() : duLieu(nullptr), soLuong(0), sucChua(0) {}

    Vector(const Vector& other) : duLieu(nullptr), soLuong(0), sucChua(0) {
        moRong(other.soLuong);
        for (size_type i = 0; i < other.soLuong; ++i) duLieu[i] = other.duLieu[i];
        soLuong = other.soLuong;
    }

    Vector(Vector&& other) noexcept
        : duLieu(other.duLieu), soLuong(other.soLuong), sucChua(other.sucChua) {
        other.duLieu = nullptr;
        other.soLuong = 0;
        other.sucChua = 0;
    }

    template<class Iterator>
    Vector(Iterator dau, Iterator cuoi) : Vector() {
        for (; dau != cuoi; ++dau) push_back(*dau);
    }

    ~Vector() { delete[] duLieu; }

    Vector& operator=(const Vector& other) {
        if (this == &other) return *this;
        Vector tam(other);
        swap(tam);
        return *this;
    }

    Vector& operator=(Vector&& other) noexcept {
        if (this == &other) return *this;
        delete[] duLieu;
        duLieu = other.duLieu;
        soLuong = other.soLuong;
        sucChua = other.sucChua;
        other.duLieu = nullptr;
        other.soLuong = 0;
        other.sucChua = 0;
        return *this;
    }

    void swap(Vector& other) noexcept {
        std::swap(duLieu, other.duLieu);
        std::swap(soLuong, other.soLuong);
        std::swap(sucChua, other.sucChua);
    }

    size_type size() const { return soLuong; }
    bool empty() const { return soLuong == 0; }

    T& operator[](size_type viTri) { return duLieu[viTri]; }
    const T& operator[](size_type viTri) const { return duLieu[viTri]; }

    void push_back(const T& giaTri) {
        if (soLuong == sucChua) moRong(sucChua == 0 ? 4 : sucChua * 2);
        duLieu[soLuong++] = giaTri;
    }

    void push_back(T&& giaTri) {
        if (soLuong == sucChua) moRong(sucChua == 0 ? 4 : sucChua * 2);
        duLieu[soLuong++] = std::move(giaTri);
    }

    void clear() { soLuong = 0; }

    iterator begin() { return duLieu; }
    iterator end() { return duLieu + soLuong; }
    const_iterator begin() const { return duLieu; }
    const_iterator end() const { return duLieu + soLuong; }

    iterator erase(iterator viTri) {
        if (viTri < begin() || viTri >= end()) return end();
        size_type chiSo = static_cast<size_type>(viTri - begin());
        for (size_type i = chiSo + 1; i < soLuong; ++i) duLieu[i - 1] = std::move(duLieu[i]);
        --soLuong;
        return begin() + chiSo;
    }
};

#endif
