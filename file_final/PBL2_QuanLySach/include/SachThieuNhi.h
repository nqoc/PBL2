// =====================================================================
//  SachThieuNhi.h - Sach thieu nhi (giam gia 15%)
// =====================================================================
#ifndef SACHTHIEUNHI_H
#define SACHTHIEUNHI_H

#include "Sach.h"

class SachThieuNhi : public Sach {
private:
    int  doTuoiToiThieu;
    bool coTranhMinhHoa;

public:
    SachThieuNhi();
    SachThieuNhi(const std::string& ma, const std::string& ten,
                 const std::string& maTG, const std::string& maTL,
                 const std::string& maNXB, int nam,
                 double giaNhap, double giaBan, int soLuong,
                 int doTuoi, bool coTranh,
                 const std::string& viTriKe = "", const std::string& moTa = "");

    int  getDoTuoi()  const { return doTuoiToiThieu; }
    bool getCoTranh() const { return coTranhMinhHoa; }
    void setDoTuoi(int t);
    void setCoTranh(bool b) { coTranhMinhHoa = b; }

    std::string loaiSach()    const;
    std::string maLoai()      const;
    Sach*       nhanBan()     const;
    double      tiLeGiamGia() const;      // 15%
    std::string moTaThem()    const;
    void        nhap();
    std::string toCSV()       const;
    void        fromCSV(const std::vector<std::string>& p);
};

#endif // SACHTHIEUNHI_H
