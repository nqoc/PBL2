# Ví dụ Chặng 9 — Đọc/ghi tệp, lưu trữ bền vững

6 bài (BT9.1 → BT9.6), mỗi file chạy độc lập, tự tạo dữ liệu thử. Đã biên dịch bằng `g++` với `-Wall -Wextra`: **không một cảnh báo**.

```bat
g++ -std=c++17 -Wall -Wextra 01_ghi_doc_so.cpp -o 01.exe  &  01.exe
```

| File | Bài | Nội dung | Điểm nhấn |
|---|---|---|---|
| `01_ghi_doc_so.cpp` | BT9.1 | Ghi 5 số, đọc lại, tính tổng | So sánh `>>` vs `getline` khi gặp rác |
| `02_sinhvien.cpp` | BT9.2 | `SinhVien` + `Vector<SinhVien>` | Đối chiếu từng bản ghi trước/sau |
| `03_doc_chiu_loi.cpp` | BT9.3 | Tệp 9 dòng, chỉ 3 dòng hợp lệ | `try` trong vs ngoài vòng lặp |
| `04_hinhhoc_file.cpp` | BT9.4 | Cây `HinhHoc` + mã loại + hàm xưởng | Chặng 6 gặp chặng 9 |
| `05_hoadon.cpp` | BT9.5 | Hóa đơn nhiều dòng, phân cách `#` | Đối chiếu tổng tiền |
| `06_saoluu.cpp` | BT9.6 | `saoLuu()` bằng `rdbuf()` | Chứng minh mất dữ liệu rồi khôi phục |

---

## BT9.1 — `>>` hay `getline`?

Tệp sạch thì cả hai đều ra `TONG = 176`. Nhưng tệp có dòng rác:

```
Cach >>          : doc duoc 2 so, tong = 57    <- DỪNG NGAY ở 'abc', mất số 89
Cach getline+stoi: doc duoc 3 so, tong = 146, bo qua 1 dong sai   <- ĐỌC HẾT
```

`f >> x` gặp chữ là luồng chuyển sang trạng thái hỏng, vòng lặp dừng luôn. `getline` đọc từng dòng nên hỏng dòng nào chỉ mất dòng đó.

**PBL2 luôn dùng `getline`** vì dữ liệu thật có thể có dòng hỏng.

## BT9.2 — Vòng tròn ghi–đọc

```
=== DU LIEU GOC ===
   102210001   Nguyen Van A     25T1    8.25
   102210002   Tran Thi B       25T2    7.50
   102210003   Le Van CDung     25T1    9.00     <- nhập "Le Van C|Dung", dấu | đã bị lọc

=== GHI xuong sv.txt ===
   102210001|Nguyen Van A|25T1|8.25
   102210002|Tran Thi B|25T2|7.50
   102210003|Le Van CDung|25T1|9.00

=== DOI CHIEU ===
   SV 1 (102210001): KHOP
   SV 2 (102210002): KHOP
   SV 3 (102210003): KHOP
   >> VONG TRON GHI-DOC HOAN HAO
```

Bốn thứ cần chú ý trong file này:

1. `toCSV()` / `fromCSV()` là **một cặp** — thứ tự trường phải giống hệt
2. `if (p.size() < 4) throw` — kiểm tra trước khi truy cập `p[i]`, tránh crash
3. `locKyTu()` gọi ở **hàm tạo** (tức lúc nhập), không phải lúc ghi
4. `chuanHoa()` cắt cả ký tự `\r` của Windows

## BT9.3 — `try` trong hay ngoài vòng lặp

Tệp 9 dòng: 3 dòng hợp lệ, 4 dòng rác, 2 dòng trống.

```
CACH SAI  (try NGOAI vong lap): doc duoc 1/3 sinh vien
CACH DUNG (try TRONG vong lap): doc duoc 3/3 sinh vien
```

Cách đúng in ra từng dòng bị bỏ, kèm lý do:

```
[bo qua dong 2] "abc"                            -> thieu truong (can 4, co 1)
[bo qua dong 5] "102210003|Le Van C|25T1"        -> thieu truong (can 4, co 3)
[bo qua dong 7] "102210004|Pham Thi D|25T3|abc"  -> diem khong phai so: "abc"
[bo qua dong 8] "102210005|Hoang Van E|25T2|15.0"-> diem ngoai khoang 0-10
>> Canh bao: bo qua 4 dong sai dinh dang trong tep du lieu.
```

**Vì sao?** `catch` ở đâu thì chương trình nhảy tới đó. `catch` ngoài vòng lặp → nhảy ra là ra khỏi vòng lặp luôn.

Chú ý thêm: file này dùng `stod` thay `atof`. `atof("abc")` trả về `0` **âm thầm**, còn `stod("abc")` **ném ngoại lệ** — nên bắt được dòng lỗi.

## BT9.4 — Cây kế thừa vào tệp

Cấu trúc mỗi dòng: `[MÃ LOẠI] | [dữ liệu lớp CHA] | [dữ liệu riêng lớp CON]`

```
TRON|Banh xe|5.00
CHUNHAT|Cua so|3.00|4.00
TAMGIAC|Mai nha|3.00|4.00|5.00
TRON|Dong xu|2.00
CHUNHAT|Ban hoc|10.00|1.00
```

Đọc lại: tổng diện tích **119.11** ở cả hai bảng — đúng loại, đúng công thức.

Ba chặng phối hợp trong 3 dòng:

```cpp
vector<string> p = tachChuoi(dong, '|');    // chặng 9
h = taoHinh(chuanHoa(p[0]));                 // chặng 6: HÀM XƯỞNG
h->fromCSV(p);                                // chặng 6: ĐA HÌNH
```

Với tệp hỏng:
```
[bo qua] "NGUSAC|Hinh la|7"      -> Ma loai hinh khong hop le: "NGUSAC"
[bo qua] "CHUNHAT|Cua so|3.00"   -> HinhChuNhat thieu truong (can 4)
```

Chú ý `docFile` có `delete h;` trong `catch` — mẫu chống rò rỉ của chặng 8, vì `taoHinh` đã `new` mà `fromCSV` có thể ném lỗi giữa chừng.

> **Quy tắc:** `maLoai()` và hàm xưởng phải khớp chuỗi. Lệch nhau thì ghi ra được nhưng đọc lại không được — và bạn chỉ phát hiện sau khi tắt chương trình.

## BT9.5 — Hóa đơn nhiều dòng con

Mẫu `ma|ngay|soDong|dong1|dong2`, mỗi dòng chi tiết dùng `#`:

```
HD00001|04/09/2026|3|VH002#Nha Gia Kim#2#75050|TN001#Doraemon T1#5#21250|GK001#Toan 12#1#35000
```

Đọc lại và đối chiếu:
```
Goc = 291350, doc lai = 291350  ->  KHOP
Goc = 267000, doc lai = 267000  ->  KHOP
```

**Phải ghi số dòng trước.** Không có nó thì lúc đọc không biết còn bao nhiêu ô là chi tiết.

Với tệp hỏng, dòng phòng thủ `if (vt >= p.size())` cứu bạn:
```
[bo qua] Bao co 3 dong nhung tep chi co 1
[bo qua] DongChiTiet thieu truong (can 4, co 2)
```

Không có nó thì đọc ngoài mảng → crash.

**Đối chiếu tổng tiền là cách kiểm tra vòng tròn nhanh nhất** — một con số sai là biết ngay có gì đó lệch.

## BT9.6 — Sao lưu

```cpp
bool saoLuu(const string& nguon, const string& dich) {
    ifstream vao(nguon.c_str(), ios::binary);
    if (!vao) return false;
    ofstream ra(dich.c_str(), ios::binary);
    if (!ra) return false;
    ra << vao.rdbuf();          // chép CẢ TỆP bằng một dòng
    return ra.good();
}
```

Kết quả:
```
sach.txt co 77 byte
Da sao luu -> sach_backup.txt (77 byte)
Hai tep giong het nhau tung byte? CO
```

Phần 5 của file chứng minh vì sao cần sao lưu:
```
Sau khi mo ofstream ma khong ghi gi: sach.txt con 0 byte  <- MẤT TRẮNG
Khoi phuc tu ban sao luu...
sach.txt gio co 77 byte  <- ĐÃ CỨU ĐƯỢC
```

**Chỉ cần mở `ofstream` là tệp đã bị xóa sạch**, chưa cần ghi gì. Nên `luuTatCa()` phải gọi `saoLuu()` trước.

Hai bẫy được xử lý trong file:

- **`ofstream` không tự tạo thư mục.** File dùng `fs::create_directories("backup")` (C++17) để tạo trước. Áp dụng luôn cho `data/` trong PBL2.
- **Nguồn và đích phải khác nhau.** Chép tệp lên chính nó thì `ofstream` xóa sạch nguồn trước khi `ifstream` kịp đọc.

---

## Ghi nhớ chung của chặng 9

**Ba dòng phòng thủ — không bao giờ tin dữ liệu từ tệp**

```cpp
if (p.size() < 12) throw LoiFile(...);   // fromCSV: đủ trường chưa?
if (vt >= p.size()) break;                // docChiTiet: còn ô không?
if (chuanHoa(dong).empty()) continue;     // docFile: dòng trống thì bỏ
```

**Bảng quyết định**

| Tình huống | Xử lý |
|---|---|
| Mở để **đọc**, tệp chưa có | `return false` — lần chạy đầu, bình thường |
| Mở để **ghi**, không ghi được | `throw LoiFile` — sự cố thật |
| Dòng **trống** | `continue` — không tính là lỗi |
| Dòng **rác** | `catch` → `++soDongLoi` → đọc tiếp |
| Đọc số từ chuỗi | `stoi`/`stod` (ném lỗi) thay vì `atoi`/`atof` (trả 0 âm thầm) |

**Bốn quy tắc để không hỏng tệp**

1. `toCSV` và `fromCSV` sửa **cùng lúc**, thứ tự trường giống hệt
2. Trường rỗng **vẫn phải có dấu `|`**
3. `maLoai()` và hàm xưởng phải khớp chuỗi
4. Lọc `|` và `#` **ngay lúc nhập**, không phải lúc ghi

**Bẫy `\r` của Windows**

`getline` chỉ cắt ở `\n`, nên `\r` dính lại cuối dòng. Trường cuối sẽ dài hơn 1 ký tự và **so sánh chuỗi trả về `false`** — `timTheoMa("GK001")` không tìm thấy dù mã đó có trong tệp. Luôn gọi `chuanHoa()` cho từng trường sau khi tách.

## Mốc PBL tuần 6–7

1. Cài `toCSV()` / `fromCSV()` cho **cả 12 lớp** dữ liệu
2. Cài `KhoDuLieu::luuFile()` / `docFile()` và `QuanLySach::luuFile()` / `docFile()` (bản này dùng hàm xưởng)
3. Cài `CuaHang::napTatCa()`, `luuTatCa()`, `saoLuu()`, `tongSoDongLoi()`

**Kiểm thử vòng tròn — mốc bắt buộc, không đạt thì không đi tiếp:**
```
tạo dữ liệu → lưu → thoát → chạy lại → dữ liệu phải GIỐNG HỆT
```

Rồi thử ba trường hợp biên: tệp rỗng, tệp có dòng rác, thư mục `data/` chưa tồn tại.

**Khung để mở rộng:** `02_sinhvien.cpp` → `KhoDuLieu::luuFile/docFile`; `04_hinhhoc_file.cpp` → `QuanLySach::docFile`; `05_hoadon.cpp` → `HoaDon::toCSV/fromCSV`; `06_saoluu.cpp` → `CuaHang::saoLuu`.

## Bảng tự kiểm tra

- ☐ Dữ liệu tồn nguyên sau khi tắt và mở lại chương trình
- ☐ Tệp có dòng rác vẫn đọc được phần còn lại
- ☐ Đọc lại đúng loại sách nhờ hàm xưởng
- ☐ Tên sách chứa `|` không phá vỡ tệp
