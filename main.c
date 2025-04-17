#include <stdio.h>
#include <stdlib.h>
#include "common.h"

// =======================
// NGUYÊN MẪU MODULE CẦN GỌI (được định nghĩa trong các file .c khác)
// =======================
void runBookModule();           // Quản lý sách
void runBorrowReturnModule();   // Mượn – trả sách
void runReaderModule();         // Quản lý bạn đọc
void runStatisticModule();      // Thống kê – Báo cáo
void runReservationModule();    // Đặt chỗ sách

// =======================
// BIẾN TOÀN CỤC ĐƯỢC ĐỊNH NGHĨA Ở ĐÂY
// =======================
Book books[MAX_BOOKS];
int bookCount = 0;

Reader readers[MAX_READERS];
int readerCount = 0;

// =======================
// HÀM HIỂN THỊ MENU CHÍNH
// =======================
void hienThiMenuChinh() {
    printf("\n");
    printf("=============================================\n");
    printf("      CHƯƠNG TRÌNH QUẢN LÝ THƯ VIỆN         \n");
    printf("=============================================\n");
    printf("1. Quản lý danh mục sách\n");
    printf("2. Quản lý mượn – trả sách\n");
    printf("3. Quản lý bạn đọc\n");
    printf("4. Thống kê – báo cáo\n");
    printf("5. Đặt chỗ sách\n");
    printf("0. Thoát chương trình\n");
    printf("=============================================\n");
    printf("Nhập lựa chọn của bạn: ");
}

// =======================
// HÀM MAIN
// =======================
int main() {
    int choice;
    do {
        hienThiMenuChinh();
        if (scanf("%d", &choice) != 1) {
            printf("Lỗi nhập liệu. Vui lòng nhập số!\n");
            while (getchar() != '\n'); // Xóa bộ đệm
            continue;
        }

        switch (choice) {
            case 1:
                runBookModule();
                break;
            case 2:
                runBorrowReturnModule();
                break;
            case 3:
                runReaderModule();
                break;
            case 4:
                runStatisticModule();
                break;
            case 5:
                runReservationModule();
                break;
            case 0:
                printf("Đang thoát chương trình...\n");
                break;
            default:
                printf("Lựa chọn không hợp lệ. Vui lòng thử lại.\n");
        }

    } while (choice != 0);

    return 0;
}
