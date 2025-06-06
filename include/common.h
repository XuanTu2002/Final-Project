#ifndef COMMON_H
#define COMMON_H

#include <string.h>

// ========================
// THÔNG TIN CẤU HÌNH CHUNG
// ========================
#define MAX_BOOKS 1000        // Số lượng sách tối đa
#define MAX_READERS 500       // Số lượng bạn đọc tối đa
#define MAX_BORROWED 10       // Số lượng sách mượn tối đa cho mỗi bạn đọc

// ========================
// KHAI BÁO CẤU TRÚC DỮ LIỆU CHUNG
// ========================

/*
 * Cấu trúc Book - Đại diện cho một cuốn sách trong thư viện
 */
typedef struct {
    char id[10];         // Mã sách duy nhất (ví dụ: "MS001")
    char title[100];     // Tiêu đề sách
    char author[100];    // Tác giả
    char category[50];   // Thể loại sách (ví dụ: "Khoa học", "Tiểu thuyết")
    int price;           // Giá tiền
    int available;       // 1: còn sách trong kho, 0: đang được mượn
} Book;

/*
 * Cấu trúc Reader - Đại diện cho một bạn đọc
 */
typedef struct {
    char id[10];              // Mã bạn đọc (ví dụ: "BD012")
    char name[100];           // Họ tên
    char studentID[20];       // Mã sinh viên (ví dụ: "20227271") - duy nhất cho mỗi sinh viên
    char department[100];     // Khoa / đơn vị công tác
    int borrowedCount;        // Số sách đang mượn hiện tại
    char borrowedBookIDs[MAX_BORROWED][10]; // Danh sách mã sách đang mượn
} Reader;

/*
 * Cấu trúc Reservation - Thông tin đặt chỗ sách
 */
typedef struct {
    char bookID[10];           // Mã sách được đặt
    char readerID[10];         // Mã bạn đọc đã đặt
    int priority;              // Ưu tiên (ví dụ: 1 = cán bộ, 2 = sinh viên)
} Reservation;

/*
 * Cấu trúc thống kê cơ bản (ví dụ: top sách mượn nhiều)
 */
typedef struct {
    char bookID[10];      // Mã sách
    int borrowCount;      // Số lần sách này đã được mượn
} BookStat;

// ========================
// BIẾN TOÀN CỤC CHO TOÀN DỰ ÁN
// ========================

extern Book books[MAX_BOOKS];           // Danh sách tất cả sách
extern int bookCount;                   // Số lượng sách hiện tại

extern Reader readers[MAX_READERS];     // Danh sách tất cả bạn đọc
extern int readerCount;                 // Số lượng bạn đọc hiện tại

// Dữ liệu đặt chỗ, thống kê, báo cáo có thể khai báo thêm tùy module

// ========================
// CÁC HÀM TIỆN ÍCH CHUNG (từ utils.h và utils.c)
// ========================

/**
 * Tìm vị trí của sách trong mảng books dựa vào mã sách
 * @param bookID Mã sách cần tìm
 * @return Vị trí của sách trong mảng (0-based index), -1 nếu không tìm thấy
 */
static inline int timViTriSach(const char bookID[]) {
    for (int i = 0; i < bookCount; i++) {
        if (strcmp(books[i].id, bookID) == 0) return i;
    }
    return -1;
}

/**
 * Tìm vị trí của bạn đọc trong mảng readers dựa vào mã bạn đọc
 * @param readerID Mã bạn đọc cần tìm
 * @return Vị trí của bạn đọc trong mảng (0-based index), -1 nếu không tìm thấy
 */
static inline int timViTriBanDoc(const char readerID[]) {
    for (int i = 0; i < readerCount; i++) {
        if (strcmp(readers[i].id, readerID) == 0) return i;
    }
    return -1;
}

// ========================
// KHAI BÁO NGUYÊN MẪU HÀM (chỉ cần nếu gọi chéo)
// ========================

// Ví dụ: void themSach(); → nếu cần gọi hàm giữa các file

#endif
