#include <stdio.h>
#include <string.h>
#include "../../../include/common.h"

#define MAX_ID_LEN 10

// =========================
// 1. MƯỢN SÁCH
// =========================
void muonSach() {
    char readerID[MAX_ID_LEN];
    char bookID[MAX_ID_LEN];

    printf("Nhập mã bạn đọc: ");
    scanf("%s", readerID);
    int rIndex = timViTriBanDoc(readerID);
    if (rIndex == -1) {
        printf("❌ Không tìm thấy bạn đọc!\n");
        return;
    }

    if (readers[rIndex].borrowedCount >= MAX_BORROWED) {
        printf("⚠️ Bạn đọc đã mượn tối đa số lượng sách cho phép!\n");
        return;
    }

    printf("Nhập mã sách cần mượn: ");
    scanf("%s", bookID);
    int bIndex = timViTriSach(bookID);
    if (bIndex == -1) {
        printf("❌ Không tìm thấy sách!\n");
        return;
    }

    if (books[bIndex].available == 0) {
        printf("⚠️ Sách này hiện đang được mượn!\n");
        return;
    }

    // Cập nhật trạng thái
    strcpy(readers[rIndex].borrowedBookIDs[readers[rIndex].borrowedCount], bookID);
    readers[rIndex].borrowedCount++;
    books[bIndex].available = 0;

    printf("✅ Mượn sách thành công!\n");
}

// =========================
// 2. TRẢ SÁCH
// =========================
void traSach() {
    char readerID[MAX_ID_LEN];
    char bookID[MAX_ID_LEN];

    printf("Nhập mã bạn đọc: ");
    scanf("%s", readerID);
    int rIndex = timViTriBanDoc(readerID);
    if (rIndex == -1) {
        printf("❌ Không tìm thấy bạn đọc!\n");
        return;
    }

    printf("Nhập mã sách cần trả: ");
    scanf("%s", bookID);
    int bIndex = timViTriSach(bookID);
    if (bIndex == -1) {
        printf("❌ Không tìm thấy sách!\n");
        return;
    }

    int found = 0;
    for (int i = 0; i < readers[rIndex].borrowedCount; i++) {
        if (strcmp(readers[rIndex].borrowedBookIDs[i], bookID) == 0) {
            found = 1;
            // Dịch mảng xóa sách khỏi danh sách mượn
            for (int j = i; j < readers[rIndex].borrowedCount - 1; j++) {
                strcpy(readers[rIndex].borrowedBookIDs[j], readers[rIndex].borrowedBookIDs[j + 1]);
            }
            readers[rIndex].borrowedCount--;
            break;
        }
    }

    if (!found) {
        printf("⚠️ Bạn đọc không mượn sách này!\n");
        return;
    }

    books[bIndex].available = 1;
    printf("✅ Trả sách thành công!\n");
}

// =========================
// 3. DANH SÁCH SÁCH ĐANG ĐƯỢC MƯỢN
// =========================
void hienThiSachDangMuon() {
    printf("\n📋 DANH SÁCH SÁCH ĐANG ĐƯỢC MƯỢN:\n");

    int found = 0;
    for (int i = 0; i < readerCount; i++) {
        for (int j = 0; j < readers[i].borrowedCount; j++) {
            printf("👤 %s mượn sách 📚 %s\n", readers[i].name, readers[i].borrowedBookIDs[j]);
            found = 1;
        }
    }

    if (!found) {
        printf("✅ Không có sách nào đang được mượn.\n");
    }
}

// =========================
// MENU MODULE  – TRẢ
// =========================
void runBorrowReturnModule() {
    int ch;
    do {
        printf("\n===== 📚 MƯỢN – TRẢ SÁCH =====\n");
        printf("1. Mượn sách\n");
        printf("2. Trả sách\n");
        printf("3. Hiển thị sách đang mượn\n");
        printf("0. Quay lại menu chính\n");
        printf("================================\n");
        printf("Nhập lựa chọn: ");
        scanf("%d", &ch);

        switch (ch) {
            case 1: muonSach(); break;
            case 2: traSach(); break;
            case 3: hienThiSachDangMuon(); break;
            case 0: printf("↩️  Quay lại menu chính...\n"); break;
            default: printf("❌ Lựa chọn không hợp lệ!\n");
        }

    } while (ch != 0);
}
