// =====================================================================
//  KhoDuLieu.h - LOP TEMPLATE quan ly mot danh sach doi tuong cung loai
//  Dung chung cho: TheLoai, TacGia, NhaXuatBan, KhachHang,
//                  NhaCungCap, TaiKhoan, HoaDon, PhieuNhap
//
//  Kieu T phai co: T()            - ham tao khong tham so
//                  getMa()        - tra ve ma (chuoi, duy nhat)
//                  getTen()       - tra ve ten de tim kiem
//                  toCSV()        - ghi ra 1 dong van ban
//                  fromCSV(vector<string>) - doc lai tu 1 dong
// =====================================================================
#ifndef KHODULIEU_H
#define KHODULIEU_H

#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <cstdlib>

#include "Vector.h"
#include "TienIch.h"
#include "NgoaiLe.h"

template <class T>
class KhoDuLieu {
private:
    Vector<T>   ds;
    std::string tenKho;      // dung trong thong bao loi
    int         soDongLoi;   // so dong sai dinh dang khi doc file

public:
    explicit KhoDuLieu(const std::string& ten = "kho du lieu")
        : tenKho(ten), soDongLoi(0) {}

    // ---------- Truy van ----------
    std::size_t soLuong() const { return ds.kichThuoc(); }
    bool        rong()    const { return ds.rong(); }
    int         loiDoc()  const { return soDongLoi; }
    std::string ten()     const { return tenKho; }

    Vector<T>&       duLieu()       { return ds; }
    const Vector<T>& duLieu() const { return ds; }

    // ---------- Tim kiem ----------
    T* timTheoMa(const std::string& ma) {
        for (std::size_t i = 0; i < ds.kichThuoc(); ++i)
            if (veThuong(ds[i].getMa()) == veThuong(ma)) return &ds[i];
        return 0;
    }

    const T* timTheoMa(const std::string& ma) const {
        for (std::size_t i = 0; i < ds.kichThuoc(); ++i)
            if (veThuong(ds[i].getMa()) == veThuong(ma)) return &ds[i];
        return 0;
    }

    bool coMa(const std::string& ma) const { return timTheoMa(ma) != 0; }

    // Tra ve ban sao cac phan tu co ten chua tu khoa
    Vector<T> timTheoTen(const std::string& tuKhoa) const {
        Vector<T> kq;
        for (std::size_t i = 0; i < ds.kichThuoc(); ++i)
            if (chuaChuoiCon(ds[i].getTen(), tuKhoa)) kq.them(ds[i]);
        return kq;
    }

    // ---------- Them / sua / xoa ----------
    void them(const T& x) {
        if (coMa(x.getMa()))
            throw LoiTrungMa("Ma " + x.getMa() + " da ton tai trong " + tenKho + ".");
        ds.them(x);
    }

    bool sua(const T& x) {
        for (std::size_t i = 0; i < ds.kichThuoc(); ++i)
            if (veThuong(ds[i].getMa()) == veThuong(x.getMa())) {
                ds.datLai(i, x);
                return true;
            }
        return false;
    }

    bool xoa(const std::string& ma) {
        for (std::size_t i = 0; i < ds.kichThuoc(); ++i)
            if (veThuong(ds[i].getMa()) == veThuong(ma)) {
                ds.xoaTaiViTri(i);
                return true;
            }
        return false;
    }

    void xoaHet() { ds.xoaHet(); }

    // ---------- Sinh ma tu dong: tienTo + so thu tu ----------
    // Vi du: sinhMa("KH", 3) -> "KH001", "KH002", ...
    std::string sinhMa(const std::string& tienTo, int soChuSo = 3) const {
        long lonNhat = 0;
        for (std::size_t i = 0; i < ds.kichThuoc(); ++i) {
            std::string m = ds[i].getMa();
            if (m.size() > tienTo.size()
                && veThuong(m.substr(0, tienTo.size())) == veThuong(tienTo)) {
                long v = atol(m.substr(tienTo.size()).c_str());
                if (v > lonNhat) lonNhat = v;
            }
        }
        std::ostringstream os;
        os << tienTo << std::setw(soChuSo) << std::setfill('0') << (lonNhat + 1);
        return os.str();
    }

    // ---------- Doc / ghi file van ban ----------
    void luuFile(const std::string& tenTep) const {
        std::ofstream f(tenTep.c_str());
        if (!f) throw LoiFile("Khong ghi duoc tep " + tenTep);
        for (std::size_t i = 0; i < ds.kichThuoc(); ++i)
            f << ds[i].toCSV() << "\n";
        f.close();
    }

    // Tra ve false neu tep chua ton tai (lan chay dau tien - khong phai loi)
    bool docFile(const std::string& tenTep) {
        soDongLoi = 0;
        std::ifstream f(tenTep.c_str());
        if (!f) return false;
        ds.xoaHet();
        std::string dong;
        while (std::getline(f, dong)) {
            if (chuanHoa(dong).empty()) continue;
            try {
                std::vector<std::string> p = tachChuoi(dong, '|');
                T x;
                x.fromCSV(p);
                ds.them(x);
            } catch (const std::exception&) {
                ++soDongLoi;               // bo qua dong loi, van doc tiep
            }
        }
        f.close();
        return true;
    }
};

#endif // KHODULIEU_H
