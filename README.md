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
- Trình biên dịch GCC trên Windows
- Hỗ trợ Unicode UTF-8 (tiếng Việt)

### Biên dịch

#### Windows
```bash
# Sử dụng build.bat để biên dịch
build.bat
```

#### Khi chạy
```bash
# Bật hỗ trợ UTF-8 trước khi chạy chương trình
chcp 65001
library.exe
```

### Chạy chương trình
```bash
# Windows
library.exe

# Unix/Linux
./library
```

## 📁 Cấu trúc mã nguồn

Dự án được tổ chức theo cấu trúc module như sau:

```
thuvien/
├── scr/
│   ├── modules/           # Các module chức năng
│   │   ├── book/         # Module quản lý sách
│   │   ├── reader/       # Module quản lý bạn đọc
│   │   ├── borrow/       # Module quản lý mượn trả
│   │   ├── reservation/  # Module quản lý đặt chỗ
│   │   └── statistic/    # Module báo cáo thống kê
│   ├── utils/            # Các module tiện ích
│   │   ├── bst/         # Cây nhị phân tìm kiếm
│   │   └── data_io/      # Module đọc/ghi dữ liệu
│   ├── data/            # Thư mục chứa dữ liệu
│   │   ├── books.txt    # Dữ liệu sách
│   │   └── readers.txt  # Dữ liệu bạn đọc
│   └── main.c           # Điểm vào chương trình
├── include/             # Thư mục chứa header files
│   └── common.h         # Định nghĩa cấu trúc dữ liệu, biến toàn cục
├── build.bat            # Script biên dịch cho Windows
└── README.md           # Tài liệu hướng dẫn
```

### Các file chính:

| File | Mô tả |
|------|-------|
| `scr/main.c` | Điểm vào chương trình, hiển thị menu chính và gọi các module |
| `include/common.h` | Định nghĩa các cấu trúc dữ liệu chung, biến toàn cục và hàm tiện ích |
| `build.bat` | Script dùng để biên dịch chương trình trên Windows |
| `scr/data/*.txt` | Các file dữ liệu lưu trữ thông tin sách và bạn đọc |

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
