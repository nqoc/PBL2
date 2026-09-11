# Ví dụ Chặng 3 — Nạp chồng toán tử

5 chương trình nhỏ, mỗi file chạy độc lập. Đã biên dịch thử bằng `g++ 13` với `-Wall -Wextra`, không cảnh báo.

```bat
g++ -std=c++17 -Wall -Wextra 01_khong_viet.cpp -o 01.exe  &  01.exe
```

| File | Nội dung | Kết quả mong đợi |
|---|---|---|
| `01_khong_viet.cpp` | Lớp có `new` nhưng **không** viết quy tắc ba | **Chương trình đổ** — `free(): double free detected` |
| `02_co_viet.cpp` | Viết đủ 3 hàm: huỷ, tạo sao chép, gán | Chạy sạch, mỗi đối tượng một vùng nhớ riêng |
| `03_cam_han.cpp` | Cấm sao chép (khai báo `private`, không định nghĩa) | Chạy tốt; bỏ `//` một dòng → **lỗi lúc biên dịch** |
| `04_toantu_sach.cpp` | 5 toán tử `== != < += <<` trên lớp `Sach` | In bảng minh hoạ từng toán tử |
| `05_toantu_vector.cpp` | `[]` `+=` `=` + `BoDuyet` (`* ++ !=`) cho `for` phạm vi | Minh hoạ sao chép sâu và tăng gấp đôi dung lượng |

## Ba trường hợp của toán tử `=`

**1. Không viết** — `01_khong_viet.cpp`

Trình biên dịch tự sinh bản sao chép nông. Hai đối tượng dùng chung vùng nhớ. Chạy sẽ thấy:

```
  [+] cap phat  0x5622f9a1d2c0        <- chi cap phat MOT lan
   a[0] = 99   <-- a BI DOI THEO
  [-] giai phong 0x5622f9a1d2c0
  [-] giai phong 0x5622f9a1d2c0       <- xoa lan hai CUNG dia chi
free(): double free detected in tcache 2
Aborted
```

Hai dòng "giai phong" in ra **cùng một địa chỉ** — đó là bằng chứng.

**2. Có viết** — `02_co_viet.cpp`

```
  [+] cap phat  0x55ca634cb2c0
  [c] sao chep sau -> vung moi 0x55ca634cb300      <- dia chi KHAC
   a[0] = 10   <-- a KHONG doi
  [-] giai phong 0x55ca634cb300
  [-] giai phong 0x55ca634cb2c0                    <- ba dia chi khac nhau
```

**3. Cấm hẳn** — `03_cam_han.cpp`

Bỏ `//` ở dòng `KhoSach ban = kho;` rồi biên dịch lại:

```
error: 'KhoSach::KhoSach(const KhoSach&)' is private within this context
note: declared private here
```

Lỗi hiện **lúc biên dịch**, không đợi đến lúc chạy mới sập. Đây là cách `QuanLySach` và `CuaHang` trong dự án đang dùng.

## Bẫy trong `04_toantu_sach.cpp`

`a += 5 += 3;` **không biên dịch được**, vì `+=` kết hợp từ phải sang trái nên bị hiểu là `a += (5 += 3)` mà `5` thì không gán được. Phải viết `(a += 5) += 3;`.

Nạp chồng toán tử không đổi được độ ưu tiên và thứ tự kết hợp của ngôn ngữ — chỉ đổi được *việc toán tử làm gì*.
