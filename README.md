# wat1learn
OOP + PBL2

Thành viên: Nguyen Nhu Ngoc ([@nqoc](https://github.com/nqoc)) và Kiet Nguyen ([@kietnguyen1060-commits](https://github.com/kietnguyen1060-commits)).

## Cách chạy

Cần `g++` hỗ trợ C++17 (ví dụ MinGW-w64). Mọi lệnh chạy trong thư mục `PBL2/`.

- Bấm đúp `build.bat`: biên dịch toàn bộ `src/*.cpp` thành `main.exe` rồi chạy luôn; lỗi biên dịch thì dừng lại để xem.
- Hoặc dùng `make` (`mingw32-make` trên Windows):
  - `make`: biên dịch, file `.o` nằm trong `build/`
  - `make run`: biên dịch rồi chạy
  - `make clean`, `make rebuild`: xoá bản build cũ / build lại từ đầu

## Thư mục

- `include/`: khai báo lớp (`Sach.h`, `HoaDon.h`, `PhieuNhap.h`, `TaiKhoan.h`…) và cấu trúc tự viết (`Vector.h`, `Chuoi.h`)
- `src/`: phần cài đặt tương ứng
- `data/`: dữ liệu mẫu dạng `.txt` (sách, tác giả, thể loại, khách hàng, hoá đơn…)
