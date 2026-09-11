# PBL2 — Quản lý sách trong cửa hàng chuyên về sách (bản console)

Chương trình C++ hướng đối tượng thực hiện **toàn bộ** các chức năng trong bản
*Kế hoạch thực hiện đề tài PBL2*, chạy ở chế độ dòng lệnh (console).
Chưa dùng Qt — phần giao diện Qt sẽ được bọc lên trên tầng nghiệp vụ này ở bước sau.

---

## 1. Biên dịch và chạy

### Cách 1 — không cần `make` (khuyến nghị trên Windows)

```
cd PBL2
build.bat
```

### Cách 2 — gọi g++ trực tiếp

```
g++ -std=c++11 -Wall -Wextra -Iinclude src/*.cpp -o QuanLySach.exe
QuanLySach.exe
```

### Cách 3 — dùng Makefile (nếu máy đã có make / mingw32-make)

```
make        # biên dịch
make run    # biên dịch rồi chạy
make clean  # xoá file tạm
```

**Tài khoản mặc định:** `admin / admin123` (quản trị viên) và `nv01 / nv123` (nhân viên bán hàng).

Lần chạy đầu tiên chương trình sẽ hỏi có tạo bộ dữ liệu mẫu hay không — chọn `c` để có
sẵn 6 đầu sách, 4 thể loại, 5 tác giả, 4 NXB, 2 nhà cung cấp, 3 khách hàng,
1 phiếu nhập và 2 hoá đơn để thử nghiệm ngay.

---

## 2. Cấu trúc thư mục

```
PBL2/
├── include/            (khai báo lớp - file .h)
│   ├── NgoaiLe.h            cây lớp ngoại lệ (exception)
│   ├── TienIch.h            nhập liệu an toàn, xử lý chuỗi / ngày / định dạng
│   ├── Vector.h             MẢNG ĐỘNG tự cài (template)
│   ├── DanhSachLienKet.h    DANH SÁCH LIÊN KẾT tự cài (template)
│   ├── BangBam.h            BẢNG BĂM tự cài (template)
│   ├── ThuatToan.h          tìm tuyến tính / nhị phân, Quick Sort, Merge Sort
│   ├── KhoDuLieu.h          LỚP TEMPLATE quản lý một danh sách đối tượng
│   ├── Nguoi.h              lớp cơ sở trừu tượng  (cây kế thừa 1)
│   ├── KhachHang.h  NhaCungCap.h  TaiKhoan.h
│   ├── DanhMuc.h            lớp cơ sở trừu tượng + TheLoai/TacGia/NhaXuatBan (cây 2)
│   ├── Sach.h               lớp cơ sở trừu tượng  (cây kế thừa 3)
│   ├── SachGiaoKhoa.h  SachVanHoc.h  SachThieuNhi.h
│   ├── ChungTu.h            lớp cơ sở trừu tượng + DongChiTiet (cây kế thừa 4)
│   ├── HoaDon.h  PhieuNhap.h
│   ├── QuanLySach.h         quản lý danh sách Sach* (đa hình + băm + nhị phân)
│   ├── ThongKe.h            các cấu trúc kết quả thống kê
│   ├── CuaHang.h            TẦNG NGHIỆP VỤ (tổng hợp mọi kho dữ liệu)
│   └── UngDung.h            TẦNG GIAO DIỆN dòng lệnh
├── src/                (định nghĩa hàm - file .cpp)
├── data/               (các tệp .txt lưu dữ liệu, tự sinh khi chạy)
│   └── backup/         (bản sao lưu)
├── build.bat  Makefile
└── README.md
```

Kiến trúc 3 tầng: `UngDung` (giao diện) → `CuaHang` (nghiệp vụ) → các lớp dữ liệu.
Tầng giao diện không chứa logic nghiệp vụ, nên khi thay bằng Qt chỉ cần viết lại tầng trên cùng.

---

## 3. Bốn cây kế thừa trong chương trình

```
        Nguoi (abstract)                 DanhMuc (abstract)
       /      |       \                 /     |       \
KhachHang NhaCungCap TaiKhoan     TheLoai  TacGia  NhaXuatBan

         Sach (abstract)                ChungTu (abstract)
        /      |       \                 /            \
SachGiaoKhoa SachVanHoc SachThieuNhi  HoaDon        PhieuNhap
   (-10%)      (-5%)      (-15%)
```

Hàm thuần ảo tiêu biểu: `Nguoi::vaiTro()`, `DanhMuc::loai()`,
`Sach::loaiSach() / maLoai() / nhanBan()`, `ChungTu::loaiChungTu() / thanhToan()`.

---

## 4. Chức năng đã hoàn thành (đối chiếu bản kế hoạch)

| Mục kế hoạch | Chức năng | Trạng thái |
|---|---|---|
| 2.1 | Đăng nhập, phân quyền admin / nhân viên, đổi mật khẩu, quản lý tài khoản | Xong |
| 2.2 | Thêm / sửa / xoá / hiển thị sách, sinh mã tự động, cập nhật tồn & giá | Xong |
| 2.3 | Quản lý thể loại, tác giả, NXB + ràng buộc toàn vẹn khi xoá | Xong |
| 2.4 | Quản lý nhà cung cấp, lập phiếu nhập, tự cộng tồn kho, tra cứu lịch sử nhập | Xong |
| 2.5 | Quản lý khách hàng, điểm tích luỹ & cấp thành viên, lịch sử mua hàng | Xong |
| 2.6 | Lập hoá đơn, tính thành tiền / chiết khấu, kiểm tra & trừ tồn kho, in lại hoá đơn | Xong |
| 2.7 | Tìm theo mã (băm + nhị phân), theo tên/tác giả/thể loại/NXB, lọc giá & tình trạng, sắp xếp 5 tiêu chí | Xong |
| 2.8 | Doanh thu ngày/tháng/khoảng, sách bán chạy, thể loại ưa chuộng, tồn kho, cảnh báo, xuất báo cáo, **biểu đồ cột ASCII** | Xong |
| 2.9 | Đọc/ghi file văn bản, xử lý ngoại lệ dữ liệu sai, sao lưu ra `data/backup/` | Xong |

Cấu trúc dữ liệu và thuật toán **tự cài đặt** (không dùng STL container):
`Vector<T>`, `DanhSachLienKet<T>`, `BangBam<V>`, tìm tuyến tính, tìm nhị phân,
Quick Sort, Merge Sort. Menu *Tìm kiếm → mục 10* in bảng so sánh số phép so sánh
giữa ba cách tìm kiếm để phục vụ phần "đánh giá độ phức tạp" của báo cáo.

---

## 5. Định dạng tệp dữ liệu

Các trường cách nhau bởi ký tự `|`. Với chứng từ, mỗi dòng chi tiết dùng thêm ký tự `#`.

```
sach.txt        maLoai|maSach|tenSach|maTacGia|maTheLoai|maNXB|namXB|giaNhap|giaBan|ton|viTriKe|moTa|<2 trường riêng>
theloai.txt     ma|ten|moTa
tacgia.txt      ma|ten|moTa|quocTich
nhaxuatban.txt  ma|ten|moTa|diaChi|dienThoai
khachhang.txt   ma|hoTen|sdt|diaChi|email|diemTichLuy
nhacungcap.txt  ma|tenCongTy|sdt|diaChi|email|maSoThue
taikhoan.txt    tenDangNhap|hoTen|sdt|diaChi|email|matKhauĐãBăm|quyen
hoadon.txt      maHD|ngay|nguoiLap|maKH|tiLeCK|soDong|maSach#ten#sl#donGia|...
phieunhap.txt   maPN|ngay|nguoiLap|maNCC|soDong|maSach#ten#sl#giaNhap|...
```

Mật khẩu **không** lưu bản rõ — chỉ lưu chuỗi băm (hàm djb2 trong `TienIch.cpp`).

---

## 6. Ghi chú

* Toàn bộ chữ hiển thị dùng tiếng Việt **không dấu** để bảng biểu thẳng cột trên
  console Windows (`setw` đếm theo byte nên chữ có dấu UTF-8 sẽ làm lệch cột).
  Khi chuyển sang Qt sẽ dùng tiếng Việt có dấu bình thường.
* Chương trình tự lưu dữ liệu khi thoát và sau mỗi lần lập hoá đơn / phiếu nhập.
* Biên dịch sạch với `-Wall -Wextra`, không còn cảnh báo.
