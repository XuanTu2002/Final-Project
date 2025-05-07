# 📚 CD4 – Hệ thống Quản lý Thư viện
## Môn học: Cơ sở dữ liệu và giải thuật

---

## 🎯 Mục tiêu dự án

Phát triển một chương trình quản lý thư viện chạy bằng dòng lệnh (console) sử dụng ngôn ngữ lập trình C. Hệ thống này hỗ trợ:

- Quản lý danh mục sách: thêm, xoá, tìm kiếm, hiển thị
- Quản lý mượn – trả sách cho bạn đọc
- Quản lý thông tin bạn đọc
- Quản lý đặt chỗ sách
- Thống kê sách và bạn đọc theo các tiêu chí

---

## 🧱 Kiến trúc hệ thống

Hệ thống được tách thành 6 module chính + 1 module tiện ích:

| Module            | File                | Chức năng chính                               |
|-------------------|---------------------|-----------------------------------------------|
| Giao diện chính   | `main.c`            | Menu lựa chọn, gọi các module con             |
| Quản lý sách      | `book.c`            | Thêm, xoá, hiển thị, tìm kiếm sách            |
| Mượn – trả sách   | `borrow_return.c`   | Mượn sách, trả sách, hiển thị sách đang mượn  |
| Quản lý bạn đọc   | `reader.c`          | Thêm, xoá, tìm kiếm bạn đọc                   |
| Đặt chỗ sách      | `reservation.c`     | Đặt chỗ, huỷ đặt chỗ, hiển thị danh sách đặt  |
| Thống kê báo cáo  | `statistic.c`       | Sách mượn nhiều, bạn đọc mượn nhiều, trạng thái sách |
| Tiện ích chung    | `utils.c`, `utils.h`| Tìm vị trí sách và bạn đọc qua mã             |
| Cấu hình chung    | `common.h`          | Struct `Book`, `Reader`, `Reservation`, biến toàn cục |

---

## 💾 Cấu trúc dữ liệu đang sử dụng

| Dữ liệu           | Kiểu dữ liệu chính | Ghi chú                                           |
|-------------------|---------------------|---------------------------------------------------|
| Danh sách sách     | `Book books[]`       | Mảng tĩnh, tối đa 1000 sách                      |
| Danh sách bạn đọc  | `Reader readers[]`   | Mảng tĩnh, tối đa 500 bạn đọc                    |
| Đặt chỗ            | `Reservation[]`      | Mảng tĩnh, chưa có cấu trúc ưu tiên nâng cao     |
| Thống kê           | Tạm thời qua vòng lặp| Chưa dùng cấu trúc dữ liệu thống kê riêng        |
| Cây BST (chưa có)  | ❌                  | Chưa tích hợp cây nhị phân tìm kiếm cho sách     |
| Hàng đợi (chưa có) | ❌                  | Đặt chỗ chỉ dùng mảng thường, chưa có priority queue |

---

## 🧠 Logic xử lý chính

### Quản lý sách (`book.c`)
- Dùng mảng `books[]`
- Tìm kiếm theo tiêu đề bằng `strstr`
- Không dùng BST, không sắp xếp danh sách khi hiển thị

### Mượn – trả sách (`borrow_return.c`)
- Kiểm tra tình trạng sách và bạn đọc trước khi thao tác
- Cập nhật trạng thái `available` và `borrowedCount`

### Đặt chỗ (`reservation.c`)
- Lưu thông tin đặt chỗ vào mảng
- Kiểm tra trùng lặp đặt chỗ trước khi thêm
- `priority` hiện chưa được dùng để sắp xếp

### Bạn đọc (`reader.c`)
- Kiểm tra trùng mã khi thêm
- Không xoá bạn đọc nếu còn sách đang mượn

### Thống kê (`statistic.c`)
- Duyệt qua mảng để tìm sách/bạn đọc mượn nhiều nhất
- Thống kê tổng số sách còn và đã mượn

---

## ⚠️ Hạn chế hiện tại (gợi ý AI hỗ trợ tiếp)

1. Chưa tích hợp **cây nhị phân tìm kiếm (BST)** cho sách
    - Có thể dùng để tìm sách theo tiêu đề nhanh hơn
2. Chưa có **cấu trúc hàng đợi hoặc ưu tiên cho đặt chỗ**
3. Không có cơ chế lưu – đọc dữ liệu từ file (`*.txt`)
4. Chưa có hàm `update` sách hoặc bạn đọc
5. Toàn bộ dữ liệu bị mất sau khi tắt chương trình

---

## ✅ Đầu vào/ra chính của chương trình

- Giao diện dòng lệnh (menu rõ ràng, nhập số chọn chức năng)
- Không dùng GUI, không dùng thư viện ngoài
- Các hàm sử dụng `printf()`, `scanf()`, `fgets()`


---

## 📦 Cấu trúc file dự án

📁 project/
├── main.c
├── common.h
├── book.c
├── borrow_return.c
├── reader.c
├── reservation.c
├── statistic.c
├── utils.c
├── utils.h
└── context.md 👈 (Bạn đang đọc file này)
