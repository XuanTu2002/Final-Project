#include <stdio.h>
#include <string.h>
#include "common.h"

// ==============================
// HÀM TIỆN ÍCH
// ==============================
int timViTriSachTheoMa(char ma[]) {
    for (int i = 0; i < bookCount; i++) {
        if (strcmp(books[i].id, ma) == 0)
            return i;
    }
    return -1;
}

// ==============================
// 1. THÊM SÁCH MỚI
// ==============================
void themSach() {
    if (bookCount >= MAX_BOOKS) {
        printf("⚠️ Danh sách sách đã đầy!\n");
        return;
    }

    Book b;
    printf("📚 Nhập mã sách: ");
    scanf("%s", b.id);

    if (timViTriSachTheoMa(b.id) != -1) {
        printf("❌ Mã sách đã tồn tại!\n");
        return;
    }

    getchar(); // clear buffer
    printf("📖 Nhập tiêu đề: ");
    fgets(b.title, sizeof(b.title), stdin);
    b.title[strcspn(b.title, "\n")] = '\0';

    printf("✍️  Nhập tác giả: ");
    fgets(b.author, sizeof(b.author), stdin);
    b.author[strcspn(b.author, "\n")] = '\0';

    printf("📂 Nhập thể loại: ");
    fgets(b.category, sizeof(b.category), stdin);
    b.category[strcspn(b.category, "\n")] = '\0';

    printf("💲 Nhập giá: ");
    scanf("%d", &b.price);

    b.available = 1; // còn trong kho
    books[bookCount++] = b;

    printf("✅ Đã thêm sách thành công!\n");
}

// ==============================
// 2. HIỂN THỊ DANH SÁCH SÁCH
// ==============================
void hienThiDanhSachSach() {
    if (bookCount == 0) {
        printf("📭 Không có sách nào trong thư viện.\n");
        return;
    }

    printf("\n%-10s %-25s %-20s %-15s %-8s %-10s\n", "Mã", "Tiêu đề", "Tác giả", "Thể loại", "Giá", "Trạng thái");
    printf("----------------------------------------------------------------------------------------\n");

    for (int i = 0; i < bookCount; i++) {
        printf("%-10s %-25s %-20s %-15s %-8d %-10s\n",
            books[i].id, books[i].title, books[i].author, books[i].category,
            books[i].price, books[i].available ? "Còn" : "Đã mượn");
    }
}

// ==============================
// 3. TÌM SÁCH THEO TIÊU ĐỀ
// ==============================
void timKiemTheoTieuDe() {
    char keyword[100];
    printf("🔍 Nhập từ khoá tiêu đề: ");
    getchar();
    fgets(keyword, sizeof(keyword), stdin);
    keyword[strcspn(keyword, "\n")] = '\0';

    int found = 0;
    for (int i = 0; i < bookCount; i++) {
        if (strstr(books[i].title, keyword) != NULL) {
            printf("🔎 %s - %s - %s\n", books[i].id, books[i].title, books[i].author);
            found = 1;
        }
    }

    if (!found) printf("❌ Không tìm thấy sách phù hợp.\n");
}

// ==============================
// 4. XOÁ SÁCH THEO MÃ
// ==============================
void xoaSachTheoMa() {
    char ma[10];
    printf("🗑️  Nhập mã sách cần xoá: ");
    scanf("%s", ma);

    int pos = timViTriSachTheoMa(ma);
    if (pos == -1) {
        printf("❌ Không tìm thấy mã sách.\n");
        return;
    }

    if (books[pos].available == 0) {
        printf("⚠️ Sách đang được mượn. Không thể xoá.\n");
        return;
    }

    for (int i = pos; i < bookCount - 1; i++) {
        books[i] = books[i + 1];
    }
    bookCount--;
    printf("✅ Đã xoá sách thành công.\n");
}

// ==============================
// ĐIỂM VÀO MODULE: HÀM GỌI TỪ MAIN
// ==============================
void runBookModule() {
    int ch;
    do {
        printf("\n======== 📚 QUẢN LÝ DANH MỤC SÁCH ========\n");
        printf("1. Thêm sách mới\n");
        printf("2. Hiển thị danh sách sách\n");
        printf("3. Tìm sách theo tiêu đề\n");
        printf("4. Xoá sách theo mã\n");
        printf("0. Quay lại menu chính\n");
        printf("=========================================\n");
        printf("Nhập lựa chọn: ");
        scanf("%d", &ch);

        switch (ch) {
            case 1: themSach(); break;
            case 2: hienThiDanhSachSach(); break;
            case 3: timKiemTheoTieuDe(); break;
            case 4: xoaSachTheoMa(); break;
            case 0: printf("↩️  Trở về menu chính...\n"); break;
            default: printf("❌ Lựa chọn không hợp lệ.\n");
        }

    } while (ch != 0);
}
