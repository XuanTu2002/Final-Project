#include <stdio.h>
#include <string.h>
#include "../../../include/common.h"

// ===============================
// 1. SÁCH ĐƯỢC MƯỢN NHIỀU NHẤT
// ===============================

int demSoLanMuon(char bookID[]) {
    int count = 0;
    for (int i = 0; i < readerCount; i++) {
        for (int j = 0; j < readers[i].borrowedCount; j++) {
            if (strcmp(readers[i].borrowedBookIDs[j], bookID) == 0)
                count++;
        }
    }
    return count;
}

void thongKeSachMuonNhieuNhat() {
    if (bookCount == 0) {
        printf("📭 Không có sách nào trong thư viện.\n");
        return;
    }

    int maxCount = 0;
    for (int i = 0; i < bookCount; i++) {
        int c = demSoLanMuon(books[i].id);
        if (c > maxCount)
            maxCount = c;
    }

    if (maxCount == 0) {
        printf("📘 Chưa có sách nào được mượn.\n");
        return;
    }

    printf("\n📊 Các sách được mượn nhiều nhất (%d lần):\n", maxCount);
    for (int i = 0; i < bookCount; i++) {
        if (demSoLanMuon(books[i].id) == maxCount) {
            printf("📚 %s - %s\n", books[i].id, books[i].title);
        }
    }
}

// ===============================
// 2. BẠN ĐỌC MƯỢN NHIỀU NHẤT
// ===============================
void thongKeBanDocMuonNhieuNhat() {
    if (readerCount == 0) {
        printf("📭 Chưa có bạn đọc nào.\n");
        return;
    }

    int max = 0;
    for (int i = 0; i < readerCount; i++) {
        if (readers[i].borrowedCount > max)
            max = readers[i].borrowedCount;
    }

    if (max == 0) {
        printf("📘 Không có bạn đọc nào đang mượn sách.\n");
        return;
    }

    printf("\n📊 Các bạn đọc đang mượn nhiều sách nhất (%d quyển):\n", max);
    for (int i = 0; i < readerCount; i++) {
        if (readers[i].borrowedCount == max) {
            printf("👤 %s - %s\n", readers[i].id, readers[i].name);
        }
    }
}

// ===============================
// 3. THỐNG KÊ SÁCH CÒN / ĐANG MƯỢN
// ===============================
void thongKeTinhTrangSach() {
    int con = 0, muon = 0;
    for (int i = 0; i < bookCount; i++) {
        if (books[i].available == 1) con++;
        else muon++;
    }

    printf("\n📚 Tổng số sách: %d\n", bookCount);
    printf("✅ Sách còn trong thư viện: %d\n", con);
    printf("📦 Sách đang được mượn: %d\n", muon);
}

// ===============================
// MENU MODULE BÁO CÁO – THỐNG KÊ
// ===============================
void runStatisticModule() {
    int ch;
    do {
        printf("\n======= 📈 BÁO CÁO – THỐNG KÊ =======\n");
        printf("1. Sách được mượn nhiều nhất\n");
        printf("2. Bạn đọc mượn nhiều nhất\n");
        printf("3. Thống kê sách còn và sách mượn\n");
        printf("0. Quay lại menu chính\n");
        printf("=====================================\n");
        printf("Nhập lựa chọn: ");
        scanf("%d", &ch);

        switch (ch) {
            case 1: thongKeSachMuonNhieuNhat(); break;
            case 2: thongKeBanDocMuonNhieuNhat(); break;
            case 3: thongKeTinhTrangSach(); break;
            case 0: printf("↩️  Quay lại menu chính...\n"); break;
            default: printf("❌ Lựa chọn không hợp lệ!\n");
        }

    } while (ch != 0);
}
