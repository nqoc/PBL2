#ifndef CHITIETHOADON_H
#define CHITIETHOADON_H

#include <string>
#include "Vector.h"
using namespace std;

class ChiTietHoaDon {
    string maHoaDon;
    string maSach;
    int soLuong;
    double donGia;
    double thanhTien;
public:
    ChiTietHoaDon();
    ChiTietHoaDon(const string& maHoaDon, const string& maSach, int soLuong,
                  double donGia, double thanhTien);
    string getMaHoaDon() const { return maHoaDon; }
    string getMaSach() const { return maSach; }
    int getSoLuong() const { return soLuong; }
    double getDonGia() const { return donGia; }
    double getThanhTien() const { return thanhTien; }
    bool setMaHoaDon(const string& s);
    bool setMaSach(const string& s);
    bool setSoLuong(int value);
    bool setDonGia(double value);
    bool setThanhTien(double value);
    bool fromChuoi(const string& dong);
    string toChuoi() const;
};

Vector<ChiTietHoaDon> docChiTietHoaDon(const string& tenFile);

#endif
