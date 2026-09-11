# Đặc tả chức năng — Hệ thống Quản lý sách trong cửa hàng chuyên về sách

> PBL2 · Khoa CNTT · Trường Đại học Bách khoa – Đại học Đà Nẵng
> Phiên bản console (C++17), 23 tệp `.h` + 23 tệp `.cpp`, ~5.900 dòng.
> Tài liệu này liệt kê **những gì chương trình làm được** sau khi hoàn thành lộ trình 14 chặng.

---

## 1. Tổng quan

| Chỉ tiêu | Giá trị |
|---|---|
| Số lớp | 31 lớp + 2 struct |
| Cây kế thừa | 4 cây: `Sach`, `Nguoi`, `DanhMuc`, `ChungTu` |
| Lớp template tự cài | `Vector<T>`, `DanhSachLienKet<T>`, `BangBam<V>`, `KhoDuLieu<T>` |
| Thuật toán tự cài | Tìm tuyến tính, tìm nhị phân, Quick Sort, Merge Sort |
| Nhóm menu | 10 nhóm — **73 chức năng con** |
| Tệp dữ liệu | 9 tệp `.txt` + thư mục sao lưu + tệp báo cáo |
| Mức quyền | 2 (ADMIN / NHANVIEN), mật khẩu được băm |
| Biên dịch | `g++ -std=c++17 -Wall -Wextra -Iinclude src/*.cpp -o QuanLySach.exe` |

Kiến trúc 3 tầng, luật một chiều (trên gọi xuống dưới):

```
TẦNG GIAO DIỆN   UngDung, UngDung_Sach, UngDung_DanhMuc,
                 UngDung_DoiTac, UngDung_GiaoDich, UngDung_ThongKe
                          | chỉ gọi xuống
TẦNG NGHIỆP VỤ   CuaHang, QuanLySach, ThongKe
                          |
TẦNG DỮ LIỆU     Sach, Nguoi, DanhMuc, ChungTu + Vector,
                 DanhSachLienKet, BangBam, KhoDuLieu
```

Tầng nghiệp vụ và tầng dữ liệu **không có một dòng `cin`/`cout` nào** — khi chuyển sang Qt chỉ phải viết lại 6 tệp `UngDung*.cpp`.

---

## 2. Danh sách chức năng theo menu

### Nhóm 1 — Quản lý sách (`UngDung_Sach.cpp`)

| # | Chức năng | Quyền |
|---|---|---|
| 1 | Xem toàn bộ danh sách sách (bảng thẳng cột) | mọi người |
| 2 | Xem chi tiết một đầu sách | mọi người |
| 3 | Thêm đầu sách mới (chọn 1 trong 3 loại) | admin |
| 4 | Sửa thông tin đầu sách | admin |
| 5 | Xoá đầu sách | admin |
| 6 | Cập nhật số lượng tồn / giá | admin |

- Mã sách **sinh tự động**: `GK001`, `VH002`, `TN003`…
- Khi thêm: hàm xưởng `taoSachTheoMaLoai()` tạo đúng lớp con; kiểm tra mã tác giả / thể loại / NXB có tồn tại trước khi lưu.
- Ba loại sách có mức giảm giá riêng nhờ đa hình: Giáo khoa −10%, Văn học −5%, Thiếu nhi −15%.

### Nhóm 2 — Quản lý danh mục (`UngDung_DanhMuc.cpp`) — admin

Ba danh mục **Thể loại / Tác giả / Nhà xuất bản** dùng chung một hàm template `menuDanhMucChung<T>`, mỗi danh mục 6 chức năng (**18 chức năng**):

1. Xem danh sách
2. Thêm mới
3. Sửa thông tin
4. Xoá — có kiểm tra ràng buộc toàn vẹn
5. Tìm theo tên
6. Xem các đầu sách thuộc mục này

### Nhóm 3 — Quản lý nhà cung cấp (`UngDung_DoiTac.cpp`) — admin

1. Xem danh sách nhà cung cấp
2. Thêm nhà cung cấp
3. Sửa thông tin
4. Xoá nhà cung cấp
5. Tìm kiếm theo tên
6. Lịch sử nhập hàng theo nhà cung cấp

### Nhóm 4 — Quản lý khách hàng (`UngDung_DoiTac.cpp`)

1. Xem danh sách khách hàng (kèm điểm tích luỹ và cấp thẻ)
2. Thêm khách hàng
3. Sửa thông tin khách hàng
4. Xoá khách hàng — *admin*
5. Tìm kiếm theo tên
6. Xem lịch sử mua hàng

Điểm tích luỹ: 1 điểm cho mỗi 10.000đ mua hàng.
Cấp thẻ: Thường (0%) · Bạc ≥200đ (2%) · Vàng ≥500đ (5%) · Kim cương ≥1000đ (8%).

### Nhóm 5 — Nhập kho, phiếu nhập (`UngDung_GiaoDich.cpp`) — admin

1. Lập phiếu nhập mới
2. Xem danh sách phiếu nhập
3. Tra cứu phiếu nhập theo ngày
4. Xem chi tiết một phiếu nhập

`CuaHang::ghiNhanPhieuNhap()` kiểm tra hết mọi dòng hàng rồi mới cộng tồn kho và cập nhật giá nhập mới nhất; mã phiếu sinh tự động.

### Nhóm 6 — Bán hàng, hoá đơn (`UngDung_GiaoDich.cpp`)

1. Lập hoá đơn bán hàng mới
2. Xem danh sách hoá đơn
3. Tra cứu hoá đơn theo ngày
4. Tra cứu hoá đơn theo khách hàng
5. In lại một hoá đơn theo mã

Chiết khấu ba lớp:

| Mức giảm | Do đâu quyết định | Cài đặt |
|---|---|---|
| Theo loại sách (10/5/15%) | đa hình — mỗi lớp con | `Sach::giaSauGiam()` |
| Theo cấp thành viên (0/2/5/8%) | điểm tích luỹ của khách | `KhachHang::tiLeGiamThanhVien()` |
| Nhân viên nhập tay (tối đa 50%) | khuyến mãi đặc biệt | `HoaDon::setTiLeChietKhau()` |

`CuaHang::ghiNhanHoaDon()` chạy nguyên tử 4 bước: kiểm tra tồn toàn bộ → trừ kho → cộng điểm khách → lưu hoá đơn. Lỗi ở bất kỳ bước kiểm tra nào thì dữ liệu vẫn nguyên vẹn.

### Nhóm 7 — Tìm kiếm, sắp xếp, lọc (`UngDung_ThongKe.cpp`)

| # | Chức năng | Độ phức tạp |
|---|---|---|
| 1 | Tìm sách theo mã — bảng băm | O(1) trung bình |
| 2 | Tìm sách theo mã — tìm nhị phân | O(log n) |
| 3 | Tìm theo tên (gần đúng, không phân biệt hoa/thường) | O(n) |
| 4 | Tìm theo tác giả | O(n) |
| 5 | Tìm theo thể loại | O(n) |
| 6 | Tìm theo nhà xuất bản | O(n) |
| 7 | Lọc theo khoảng giá | O(n) |
| 8 | Lọc còn hàng / hết hàng | O(n) |
| 9 | Sắp xếp danh sách (5 tiêu chí × 2 chiều) | O(n log n) |
| 10 | So sánh hiệu năng ba cách tìm kiếm | — |

Sắp xếp theo mã / giá / tồn dùng Quick Sort; theo tên / năm dùng Merge Sort vì cần **tính ổn định**. Luôn sắp trên **bản sao** để không phá thứ tự theo mã mà tìm nhị phân phụ thuộc vào.

### Nhóm 8 — Thống kê, báo cáo (`ThongKe.cpp`, `UngDung_ThongKe.cpp`) — admin

1. Tổng quan tồn kho (số đầu sách, tổng số cuốn, tổng giá trị tồn)
2. Doanh thu theo ngày — **có biểu đồ cột**
3. Doanh thu theo tháng — **có biểu đồ cột**
4. Doanh thu theo khoảng thời gian
5. Top sách bán chạy — **có biểu đồ cột**
6. Thể loại được mua nhiều nhất
7. Cảnh báo sách sắp hết hàng (theo ngưỡng đặt được)
8. Xuất báo cáo tổng hợp ra tệp văn bản (6 phần)

Kỹ thuật: gộp theo khoá bằng bảng băm — tổng độ phức tạp O(số dòng chi tiết) thay vì O(n·m) hai vòng lồng nhau.

### Nhóm 9 — Dữ liệu: lưu / nạp / sao lưu (`CuaHang.cpp`)

1. Lưu toàn bộ dữ liệu xuống tệp
2. Nạp lại dữ liệu từ tệp (huỷ thay đổi chưa lưu)
3. Sao lưu ra `data/backup/` — *admin*
4. Tạo bộ dữ liệu mẫu — *admin*
5. Đặt ngưỡng cảnh báo tồn kho

9 tệp `.txt`, các trường cách nhau bởi `|`, dòng chi tiết chứng từ dùng thêm `#`.
Đọc **chịu lỗi**: một dòng sai định dạng chỉ bị đếm và bỏ qua, phần còn lại vẫn nạp được — chương trình báo *“Canh bao: bo qua N dong sai dinh dang”*.

### Nhóm 10 — Tài khoản, đổi mật khẩu (`UngDung.cpp`, `TaiKhoan.cpp`)

1. Đổi mật khẩu của tôi
2. Xem danh sách tài khoản — *admin*
3. Thêm tài khoản mới — *admin*
4. Đổi quyền một tài khoản — *admin*
5. Xoá tài khoản — *admin*

Đăng nhập tối đa 3 lần rồi thoát. Mật khẩu lưu dạng **chuỗi băm (djb2)**, không bao giờ lưu bản rõ.
Tài khoản mặc định: `admin / admin123` và `nv01 / nv123`.

---

## 3. Ràng buộc chương trình tự chặn

| Tình huống | Chương trình phản ứng |
|---|---|
| Bán nhiều hơn số lượng tồn | Chặn ở cả hai tầng · `LoiTonKho` kèm số còn lại |
| Xoá thể loại / tác giả / NXB đang có sách tham chiếu | Chặn kèm số đầu sách đang dùng · `LoiRangBuoc` |
| Thêm sách với mã danh mục không tồn tại | Bắt nhập lại cả 3 mã · `LoiKhongTimThay` |
| Thêm đối tượng trùng mã | Chặn tại `KhoDuLieu::them()` · `LoiTrungMa` |
| Giá âm, năm 1800, SĐT có chữ, ngày 31/02 | Setter từ chối và hỏi lại · `LoiDuLieu` |
| Tên sách chứa `\|` hoặc `#` | Lọc bằng `locKyTu()` — tệp dữ liệu không hỏng |
| Gõ chữ khi chương trình chờ số | Hỏi lại, không treo, không thoát đột ngột |
| Nhân viên chọn mục dành cho admin | Quay lại menu · `LoiPhanQuyen` |
| Hoá đơn cũ khi sách đã đổi tên / tăng giá | In lại vẫn đúng tên và giá lúc bán (chứng từ lưu bản chụp) |
| Lỗi giữa chừng khi ghi nhận chứng từ | Kiểm tra toàn bộ trước, chỉ sửa kho khi mọi dòng hợp lệ |

---

## 4. Chương trình chưa làm được

- Không có giao diện đồ hoạ — bản Qt là học kỳ sau; khi đó chỉ viết lại 6 tệp `UngDung*.cpp`, toàn bộ tầng nghiệp vụ và dữ liệu giữ nguyên.
- Không dùng cơ sở dữ liệu, không có mạng, một người dùng tại một thời điểm.
- Không có hoàn tác (undo) và nhật ký thao tác.
- Băm mật khẩu djb2 chỉ đủ cho bài tập; hệ thống thật dùng bcrypt/argon2 có thêm “muối”.
