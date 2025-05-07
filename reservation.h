#ifndef RESERVATION_H
#define RESERVATION_H

#include "common.h"

/**
 * Cấu trúc node cho hàng đợi ưu tiên đặt chỗ sách
 * Mỗi node chứa thông tin về một đặt chỗ và con trỏ đến node tiếp theo
 */
typedef struct ReservationNode {
    char bookID[10];                 // Mã sách được đặt
    char readerID[10];               // Mã bạn đọc đã đặt
    int priority;                    // Ưu tiên (ví dụ: 1 = cán bộ/giảng viên, 2 = sinh viên)
    struct ReservationNode* next;    // Con trỏ đến node tiếp theo
} ReservationNode;

/**
 * Cấu trúc hàng đợi ưu tiên cho đặt chỗ sách
 * Mỗi sách có một hàng đợi riêng
 */
typedef struct {
    char bookID[10];                 // Mã sách
    ReservationNode* front;          // Con trỏ đến node đầu tiên trong hàng đợi
    int count;                       // Số lượng đặt chỗ trong hàng đợi
} ReservationQueue;

/**
 * Đặt chỗ sách
 * Thêm một bạn đọc vào hàng đợi đặt chỗ của sách
 */
void datChoSach();

/**
 * Hiển thị danh sách đặt chỗ
 * Hiển thị tất cả các đặt chỗ theo từng sách
 */
void hienThiDanhSachDatCho();

/**
 * Hủy đặt chỗ
 * Xóa một bạn đọc khỏi hàng đợi đặt chỗ của sách
 */
void huyDatCho();

/**
 * Chạy module đặt chỗ sách
 * Hiển thị menu và xử lý lựa chọn của người dùng
 */
void runReservationModule();

#endif /* RESERVATION_H */
