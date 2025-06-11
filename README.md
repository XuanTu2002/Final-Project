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

Dự án áp dụng các cấu trúc dữ liệu sau để tối ưu hiệu suất và tổ chức dữ liệu:

1. **Struct**: Định nghĩa cấu trúc dữ liệu cho `Book`, `Reader`, `Reservation`
2. **Mảng tĩnh**: 
   - Lưu trữ danh sách sách (`books[]`) với kích thước cố định
   - Lưu trữ danh sách bạn đọc (`readers[]`) với kích thước cố định
   - Mỗi bạn đọc có một mảng `borrowedBookIDs` để lưu trữ các sách đang mượn
3. **Cây nhị phân tìm kiếm (BST)**: 
   - Sử dụng để sắp xếp và tìm kiếm sách theo tiêu đề
   - Cài đặt các thao tác cơ bản: thêm, xóa, tìm kiếm, duyệt in-order
4. **Hàng đợi ưu tiên (Priority Queue)**:
   - Sử dụng trong module đặt chỗ sách
   - Được cài đặt bằng danh sách liên kết đơn với các thao tác:
     - Thêm vào hàng đợi theo độ ưu tiên
     - Xóa khỏi hàng đợi
     - Hiển thị danh sách đặt chỗ
5. **Danh sách liên kết đơn (Singly Linked List)**:
   - Sử dụng để cài đặt hàng đợi ưu tiên trong module đặt chỗ
   - Mỗi nút chứa thông tin đặt chỗ và con trỏ đến nút kế tiếp

## 🔧 Hướng dẫn cài đặt và chạy

### Yêu cầu
- Trình biên dịch GCC (MinGW trên Windows)
- Hệ điều hành: Windows/Linux/macOS
- Hỗ trợ Unicode UTF-8 (tiếng Việt)

### Cách chạy chương trình

#### Trên Windows
1. Mở Command Prompt (cmd) hoặc PowerShell
2. Di chuyển đến thư mục chứa dự án
3. Chạy file `run.bat`:
   ```bash
   run.bat
   ```
   - Lần đầu tiên chạy, chương trình sẽ tự động biên dịch
   - Các lần chạy sau sẽ khởi động nhanh hơn

#### Trên Linux/macOS
1. Mở Terminal
2. Cài đặt gcc nếu chưa có:
   ```bash
   sudo apt-get install gcc   # Ubuntu/Debian
   brew install gcc           # macOS (với Homebrew)
   ```
3. Biên dịch thủ công:
   ```bash
   gcc scr/main.c scr/modules/book/book.c scr/modules/reader/reader.c \
   scr/modules/borrow/borrow_return.c scr/modules/statistic/statistic.c \
   scr/modules/reservation/reservation.c scr/utils/data_io/data_io.c \
   scr/utils/bst/bst.c scr/utils/bst/bst_stat.c -o library
   ```
4. Chạy chương trình:
   ```bash
   ./library
   ```

### Lưu ý
- Chương trình tự động tạo thư mục `scr/data` nếu chưa tồn tại
- Dữ liệu được lưu tự động vào các file `books.txt` và `readers.txt` trong thư mục `scr/data`

## 📁 Cấu trúc dữ liệu và mã nguồn

### Cấu trúc dữ liệu chính

1. **Sách (Book)**
   - `id[10]` - Mã sách (ví dụ: "MS001")
   - `title[100]` - Tiêu đề sách
   - `author[100]` - Tác giả
   - `category[50]` - Thể loại sách (ví dụ: "Khoa học", "Tiểu thuyết")
   - `price` - Giá tiền (số nguyên)
   - `available` - Trạng thái sách (1: còn sách, 0: đang được mượn)

2. **Bạn đọc (Reader)**
   - `id[10]` - Mã bạn đọc (ví dụ: "BD012")
   - `name[100]` - Họ tên
   - `studentID[20]` - Mã sinh viên (duy nhất cho mỗi sinh viên)
   - `department[100]` - Khoa/đơn vị công tác
   - `borrowedCount` - Số sách đang mượn hiện tại
   - `borrowedBookIDs[MAX_BORROWED][10]` - Danh sách mã sách đang mượn (tối đa 10 cuốn)

3. **Đặt chỗ (Reservation)**
   - `bookID[10]` - Mã sách được đặt
   - `readerID[10]` - Mã bạn đọc đã đặt
   - `priority` - Mức độ ưu tiên (1: cán bộ, 2: sinh viên)

### Cấu trúc thư mục

```
thuvien/
├── scr/
│   ├── modules/           # Các module chức năng
│   │   ├── book/         # Quản lý sách (thêm, xóa, tìm kiếm)
│   │   ├── reader/       # Quản lý bạn đọc
│   │   ├── borrow/       # Xử lý mượn/trả sách
│   │   ├── reservation/  # Quản lý đặt chỗ (hàng đợi ưu tiên)
│   │   └── statistic/    # Thống kê và báo cáo
│   ├── utils/            # Tiện ích hỗ trợ
│   │   ├── bst/         # Cài đặt cây nhị phân tìm kiếm
│   │   │   ├── bst.[ch]      # BST cơ bản cho sách
│   │   │   └── bst_stat.[ch] # BST cho thống kê
│   │   └── data_io/     # Xử lý đọc/ghi file
│   ├── data/            # Thư mục dữ liệu
│   │   ├── books.txt    # Danh sách sách
│   │   └── readers.txt  # Danh sách bạn đọc
│   └── main.c           # Chương trình chính
├── include/             # Header files
│   └── common.h         # Khai báo chung
├── run.bat             # Chạy chương trình (Windows)
└── README.md           # Hướng dẫn sử dụng
```

### Mô tả các module chính

| Module | Chức năng | Cấu trúc dữ liệu |
|--------|-----------|------------------|
| **Book** | Quản lý sách, tìm kiếm, hiển thị | Mảng tĩnh `books[]` và BST sắp xếp theo tiêu đề |
| **Reader** | Quản lý thông tin bạn đọc | Mảng tĩnh `readers[]` |
| **Borrow** | Xử lý mượn/trả sách | Mảng tĩnh `borrowedBookIDs[]` trong struct Reader |
| **Reservation** | Đặt chỗ sách | Danh sách liên kết đơn (hàng đợi ưu tiên) |
| **Statistic** | Thống kê, báo cáo | BST cho thống kê sách mượn nhiều |

### Luồng dữ liệu
1. Khởi động: Đọc dữ liệu từ file → Mảng/BST
2. Xử lý: Tương tác qua menu → Cập nhật dữ liệu
3. Kết thúc: Lưu dữ liệu từ bộ nhớ → File

## 🌟 Tính năng nổi bật

1. **Tìm kiếm hiệu quả**: Sử dụng cây nhị phân tìm kiếm (BST) để tối ưu việc tìm kiếm sách theo tiêu đề
2. **Đặt chỗ thông minh**: Hệ thống hàng đợi ưu tiên cho phép quản lý đặt chỗ theo mức độ ưu tiên của bạn đọc
3. **Giao diện thân thiện**: Menu trực quan, dễ sử dụng với các biểu tượng emoji
4. **Kiểm tra dữ liệu**: Kiểm tra tính hợp lệ của dữ liệu đầu vào để đảm bảo tính nhất quán

## 👥 Nhóm phát triển (5 thành viên )

- Nguyễn Xuân Tự ( Trưởng nhóm)
- Nguyễn Đình Mạnh
- Lê Văn Lương
- Hoàng Minh 
- Dương Ngọc Ninh

## 📝 Ghi chú

- Dự án được viết hoàn toàn bằng ngôn ngữ C chuẩn, không sử dụng thư viện ngoài
- Khi khởi động, chương trình tự động đọc dữ liệu từ `books.txt` và `readers.txt` nếu có.
- Trước khi thoát, dữ liệu hiện có được lưu trở lại các file này.
- Được phát triển như một phần của khóa học Cấu trúc dữ liệu và Giải thuật
