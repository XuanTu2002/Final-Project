# 📚 Hệ thống Quản lý Thư viện

Một hệ thống quản lý thư viện chạy trên dòng lệnh được phát triển trong khuôn khổ môn học **Cấu trúc dữ liệu và Giải thuật**. Dự án này cung cấp các chức năng quản lý cơ bản của một thư viện, bao gồm quản lý sách, bạn đọc, mượn-trả sách và thống kê.

## 🎯 Mục tiêu

Dự án nhằm ứng dụng các cấu trúc dữ liệu và giải thuật đã học vào việc xây dựng một hệ thống quản lý thực tế. Hệ thống được thiết kế để:
- Quản lý thông tin sách và bạn đọc một cách hiệu quả
- Theo dõi quá trình mượn và trả sách
- Hỗ trợ đặt chỗ sách với cơ chế ưu tiên
- Cung cấp các báo cáo thống kê hữu ích

## ✨ Chức năng chính

### 1. Quản lý sách
- Thêm sách mới vào thư viện
- Hiển thị danh sách sách
- Tìm kiếm sách theo tiêu đề
- Xóa sách theo mã
- Hiển thị sách theo thứ tự tiêu đề (sử dụng BST)

### 2. Quản lý bạn đọc
- Thêm bạn đọc mới
- Hiển thị danh sách bạn đọc
- Tìm kiếm bạn đọc theo tên
- Xóa bạn đọc theo mã

### 3. Mượn - trả sách
- Đăng ký mượn sách cho bạn đọc
- Ghi nhận trả sách
- Hiển thị danh sách sách đang được mượn

### 4. Đặt chỗ sách
- Đặt chỗ sách (khi sách đã được mượn)
- Quản lý hàng đợi đặt chỗ theo mức độ ưu tiên
- Hiển thị danh sách đặt chỗ
- Hủy đặt chỗ

### 5. Thống kê
- Thống kê sách được mượn nhiều nhất
- Thống kê bạn đọc mượn nhiều sách nhất
- Thống kê tình trạng sách (có sẵn/đang mượn)

## 🧱 Cấu trúc dữ liệu đã áp dụng

Dự án áp dụng nhiều cấu trúc dữ liệu khác nhau để tối ưu hiệu suất và tổ chức dữ liệu:

1. **Struct**: Định nghĩa cấu trúc dữ liệu cho `Book`, `Reader`, `Reservation`
2. **Mảng**: Lưu trữ danh sách sách và bạn đọc
3. **Cây nhị phân tìm kiếm (BST)**: Tối ưu việc tìm kiếm và sắp xếp sách theo tiêu đề
4. **Hàng đợi ưu tiên (Priority Queue)**: Quản lý đặt chỗ sách theo thứ tự ưu tiên
5. **Linked List**: Cài đặt hàng đợi ưu tiên cho module đặt chỗ

## 🔧 Hướng dẫn biên dịch và chạy

### Yêu cầu
- Trình biên dịch GCC
- Môi trường Windows hoặc Unix/Linux

### Biên dịch

#### Windows
```bash
gcc -o library main.c book.c borrow_return.c reader.c reservation.c statistic.c bst.c data_io.c
```

#### Unix/Linux
```bash
gcc -o library main.c book.c borrow_return.c reader.c reservation.c statistic.c bst.c data_io.c
```

### Chạy chương trình
```bash
# Windows
library.exe

# Unix/Linux
./library
```

## 📁 Cấu trúc mã nguồn

| File | Mô tả |
|------|-------|
| `main.c` | Điểm vào chương trình, hiển thị menu chính và gọi các module |
| `common.h` | Định nghĩa các cấu trúc dữ liệu chung, biến toàn cục và hàm tiện ích |
| `book.c` | Module quản lý sách (thêm, xóa, tìm kiếm, hiển thị) |
| `reader.c` | Module quản lý bạn đọc (thêm, xóa, tìm kiếm, hiển thị) |
| `borrow_return.c` | Module quản lý mượn và trả sách |
| `reservation.c` | Module quản lý đặt chỗ sách với hàng đợi ưu tiên |
| `reservation.h` | Định nghĩa cấu trúc dữ liệu cho hàng đợi ưu tiên đặt chỗ |
| `statistic.c` | Module thống kê và báo cáo |
| `bst.c` | Cài đặt cây nhị phân tìm kiếm cho sách |
| `bst.h` | Định nghĩa cấu trúc dữ liệu và nguyên mẫu hàm cho BST |
| `data_io.c` / `data_io.h` | Nạp và lưu dữ liệu sách, bạn đọc vào file |

## 🌟 Tính năng nổi bật

1. **Tìm kiếm hiệu quả**: Sử dụng cây nhị phân tìm kiếm (BST) để tối ưu việc tìm kiếm sách theo tiêu đề
2. **Đặt chỗ thông minh**: Hệ thống hàng đợi ưu tiên cho phép quản lý đặt chỗ theo mức độ ưu tiên của bạn đọc
3. **Giao diện thân thiện**: Menu trực quan, dễ sử dụng với các biểu tượng emoji
4. **Kiểm tra dữ liệu**: Kiểm tra tính hợp lệ của dữ liệu đầu vào để đảm bảo tính nhất quán

## 👥 Nhóm phát triển

- [Thành viên 1]
- [Thành viên 2]
- [Thành viên 3]
- [Thành viên 4]

## 📝 Ghi chú

- Dự án được viết hoàn toàn bằng ngôn ngữ C chuẩn, không sử dụng thư viện ngoài
- Khi khởi động, chương trình tự động đọc dữ liệu từ `books.txt` và `readers.txt` nếu có.
- Trước khi thoát, dữ liệu hiện có được lưu trở lại các file này.
- Được phát triển như một phần của khóa học Cấu trúc dữ liệu và Giải thuật
