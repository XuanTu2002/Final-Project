#include <stdio.h>
#include <stdlib.h>
#include "common.h"

// ==========================
// KHAI BÁO NGUYÊN MẪU CỦA MODULE
// ==========================
void runBookModule();           // Thành viên 1
void runBorrowReturnModule();   // Thành viên 2
void runReaderModule();         // Thành viên 3
void runStatisticModule();      // Thành viên 4
void runReservationModule();    // Thành viên 5

// ==========================
// BIẾN TOÀN CỤC
// ==========================
Book books[MAX_BOOKS];
int bookCount = 0;

Reader readers[MAX_READERS];
int readerCount = 0;

// ==========================
// HÀM HIỂN THỊ MENU CHÍNH
// ==========================
void hienThiMenuChinh() {
    printf("\n");
    printf("=============================================\n");
    printf("        HỆ THỐNG QUẢN LÝ THƯ VIỆN\n");
    printf("=============================================\n");
    printf("1. Quản lý danh mục sách\n");
    printf("2. Quản lý mượn – trả sách\n");
    printf("3. Quản lý bạn đọc\n");
    printf("4. Báo cáo – thống kê\n");
    printf("5. Đặt chỗ sách\n");
    printf("0. Thoát chương trình\n");
    printf("=============================================\n");
    printf("Nhập lựa chọn của bạn: ");
}

// ==========================
// HÀM MAIN
// ==========================
int main() {
    int choice;

    do {
        hienThiMenuChinh();
        if (scanf("%d", &choice) != 1) {
            printf("⚠️  Lỗi: Bạn phải nhập một số!\n");
            while (getchar() != '\n'); // Xóa bộ đệm nhập
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
                printf("👋 Cảm ơn bạn đã sử dụng hệ thống. Hẹn gặp lại!\n");
                break;
            default:
                printf("❌ Lựa chọn không hợp lệ. Vui lòng thử lại!\n");
        }

    } while (choice != 0);

    return 0;
}
