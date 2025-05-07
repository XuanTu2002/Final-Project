#include <stdio.h>
#include <string.h>
#include "common.h"

#define MAX_ID 10

// ==============================
// 1. THÊM BẠN ĐỌC MỚI
// ==============================
void themBanDoc() {
    if (readerCount >= MAX_READERS) {
        printf("⚠️ Danh sách bạn đọc đã đầy!\n");
        return;
    }

    Reader r;
    printf("📘 Nhập mã bạn đọc: ");
    scanf("%s", r.id);

    if (timViTriBanDoc(r.id) != -1) {
        printf("❌ Mã bạn đọc đã tồn tại!\n");
        return;
    }

    getchar(); // xoá \n
    printf("📝 Nhập họ tên: ");
    fgets(r.name, sizeof(r.name), stdin);
    r.name[strcspn(r.name, "\n")] = '\0';

    printf("🏫 Nhập khoa/đơn vị: ");
    fgets(r.department, sizeof(r.department), stdin);
    r.department[strcspn(r.department, "\n")] = '\0';

    r.borrowedCount = 0;

    readers[readerCount++] = r;
    printf("✅ Đã thêm bạn đọc thành công!\n");
}

// ==============================
// 2. HIỂN THỊ DANH SÁCH BẠN ĐỌC
// ==============================
void hienThiDanhSachBanDoc() {
    if (readerCount == 0) {
        printf("📭 Không có bạn đọc nào trong hệ thống.\n");
        return;
    }

    printf("\n%-10s %-25s %-25s %-10s\n", "Mã", "Họ tên", "Khoa/Đơn vị", "Sách mượn");
    printf("--------------------------------------------------------------------------\n");

    for (int i = 0; i < readerCount; i++) {
        printf("%s\t%s\t%s\t%d\n",
            readers[i].id, readers[i].name, readers[i].department, readers[i].borrowedCount);     
    }
}

// ==============================
// 3. TÌM KIẾM BẠN ĐỌC
// ==============================
void timKiemBanDoc() {
    char keyword[100];
    getchar();
    printf("🔍 Nhập từ khoá tên hoặc mã bạn đọc: ");
    fgets(keyword, sizeof(keyword), stdin);
    keyword[strcspn(keyword, "\n")] = '\0';

    int found = 0;
    for (int i = 0; i < readerCount; i++) {
        if (strstr(readers[i].id, keyword) || strstr(readers[i].name, keyword)) {
            printf("👤 %s - %s - %s (%d sách)\n",
                readers[i].id, readers[i].name, readers[i].department, readers[i].borrowedCount);
            found = 1;
        }
    }

    if (!found)
        printf("❌ Không tìm thấy bạn đọc phù hợp.\n");
}

// ==============================
// 4. XOÁ BẠN ĐỌC
// ==============================
void xoaBanDoc() {
    char readerID[MAX_ID];
    printf("🗑️ Nhập mã bạn đọc cần xoá: ");
    scanf("%s", readerID);

    int pos = timViTriBanDoc(readerID);
    if (pos == -1) {
        printf("❌ Không tìm thấy bạn đọc!\n");
        return;
    }

    if (readers[pos].borrowedCount > 0) {
        printf("⚠️ Bạn đọc đang giữ sách, không thể xoá.\n");
        return;
    }

    for (int i = pos; i < readerCount - 1; i++) {
        readers[i] = readers[i + 1];
    }
    readerCount--;

    printf("✅ Đã xoá bạn đọc thành công!\n");
}

// ==============================
// MENU MODULE QUẢN LÝ BẠN ĐỌC
// ==============================
void runReaderModule() {
    int ch;
    do {
        printf("\n======= 👤 QUẢN LÝ BẠN ĐỌC =======\n");
        printf("1. Thêm bạn đọc\n");
        printf("2. Hiển thị danh sách bạn đọc\n");
        printf("3. Tìm kiếm bạn đọc\n");
        printf("4. Xoá bạn đọc\n");
        printf("0. Quay lại menu chính\n");
        printf("==================================\n");
        printf("Nhập lựa chọn: ");
        scanf("%d", &ch);

        switch (ch) {
            case 1: themBanDoc(); break;
            case 2: hienThiDanhSachBanDoc(); break;
            case 3: timKiemBanDoc(); break;
            case 4: xoaBanDoc(); break;
            case 0: printf("↩️  Quay lại menu chính...\n"); break;
            default: printf("❌ Lựa chọn không hợp lệ!\n");
        }

    } while (ch != 0);
}
