#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "../../../include/common.h"
#include "../../utils/bst/bst.h"

// Biến toàn cục cho cây BST
BookNode* bookTree = NULL;

// ==============================
// 1. THÊM SÁCH MỚI
// ==============================
void themSach() {
    if (bookCount >= MAX_BOOKS) {
        printf("Danh sách sách đã đầy!\n");
        return;
    }

    Book b;

    printf("📚 Nhập mã sách: ");
    scanf("%s", b.id);
    while(getchar() != '\n'); // Xoá '\n'

    if (timViTriSach(b.id) != -1) {
        printf("❌ Mã sách đã tồn tại!\n");
        return;
    }

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
    if (scanf("%d", &b.price) != 1) {
        printf("❌ Lỗi: Giá sách phải là số nguyên.\n");
        while (getchar() != '\n'); // Xoá rác khỏi buffer
        return;
    }
    while(getchar() != '\n'); // Xoá '\n'

    b.available = 1;
    books[bookCount++] = b;
    bookTree = insertBook(bookTree, b);

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

    // Tìm kiếm sách trong cây BST
    Book results[MAX_BOOKS];
    int count = 0;
    
    searchBooksByKeyword(bookTree, keyword, results, &count);
    
    if (count > 0) {
        printf("\n%-10s %-25s %-20s %-15s %-8s %-10s\n", "Mã", "Tiêu đề", "Tác giả", "Thể loại", "Giá", "Trạng thái");
        printf("----------------------------------------------------------------------------------------\n");
        
        for (int i = 0; i < count; i++) {
            printf("%-10s %-25s %-20s %-15s %-8d %-10s\n",
                results[i].id, results[i].title, results[i].author, results[i].category,
                results[i].price, results[i].available ? "Còn" : "Đã mượn");
        }
    } else {
        printf("❌ Không tìm thấy sách phù hợp.\n");
    }
}

// ==============================
// 4. XOÁ SÁCH THEO MÃ
// ==============================
void xoaSachTheoMa() {
    char ma[10];
    printf("🗑️  Nhập mã sách cần xoá: ");
    scanf("%s", ma);

    int pos = timViTriSach(ma);
    if (pos == -1) {
        printf("❌ Không tìm thấy mã sách.\n");
        return;
    }

    if (books[pos].available == 0) {
        printf("⚠️ Sách đang được mượn. Không thể xoá.\n");
        return;
    }

    // Xóa sách khỏi cây BST
    bookTree = deleteBookFromBST(bookTree, ma);

    // Xóa sách khỏi mảng
    for (int i = pos; i < bookCount - 1; i++) {
        books[i] = books[i + 1];
    }
    bookCount--;
    printf("✅ Đã xoá sách thành công.\n");
}

// ==============================
// 5. HIỂN THỊ SÁCH THEO THỨ TỰ TIÊU ĐỀ (BST)
// ==============================
void hienThiSachTheoThuTu() {
    if (bookCount == 0) {
        printf("📭 Không có sách nào trong thư viện.\n");
        return;
    }
    
    printf("\n📚 DANH SÁCH SÁCH THEO THỨ TỰ TIÊU ĐỀ:\n");
    printf("----------------------------------------------------------------------------------------\n");
    
    // Duyệt cây BST theo thứ tự trung tố (inorder) để hiển thị sách theo thứ tự tiêu đề
    inorderTraversal(bookTree);
}

// ==============================
// 6. XÂY DỰNG LẠI CÂY BST TỪ MẢNG SÁCH
// ==============================
void xayDungLaiCayBST() {
    // Giải phóng cây BST cũ nếu có
    if (bookTree != NULL) {
        freeBST(bookTree);
        bookTree = NULL;
    }
    
    // Xây dựng lại cây BST từ mảng sách
    bookTree = buildBSTFromArray(books, bookCount);
    
    printf("✅ Đã xây dựng lại cây BST thành công!\n");
}

// ==============================
// ĐIỂM VÀO MODULE: HÀM GỌI TỪ MAIN
// ==============================
void runBookModule() {
    // Xây dựng cây BST từ mảng sách nếu chưa có
    if (bookTree == NULL && bookCount > 0) {
        xayDungLaiCayBST();
    }
    
    int ch;
    do {
        printf("\n======== 📚 QUẢN LÝ DANH MỤC SÁCH ========\n");
        printf("1. Thêm sách mới\n");
        printf("2. Hiển thị danh sách sách\n");
        printf("3. Tìm sách theo tiêu đề\n");
        printf("4. Xoá sách theo mã\n");
        printf("5. Hiển thị sách theo thứ tự tiêu đề (BST)\n");
        printf("6. Xây dựng lại cây BST\n");
        printf("0. Quay lại menu chính\n");
        printf("=========================================\n");
        printf("Nhập lựa chọn: ");
        scanf("%d", &ch);

        switch (ch) {
            case 1: themSach(); break;
            case 2: hienThiDanhSachSach(); break;
            case 3: timKiemTheoTieuDe(); break;
            case 4: xoaSachTheoMa(); break;
            case 5: hienThiSachTheoThuTu(); break;
            case 6: xayDungLaiCayBST(); break;
            case 0: 
                // Giải phóng bộ nhớ cây BST khi thoát
                if (bookTree != NULL) {
                    freeBST(bookTree);
                    bookTree = NULL;
                }
                printf("↩️  Trở về menu chính...\n"); 
                break;
            default: printf("❌ Lựa chọn không hợp lệ.\n");
        }

    } while (ch != 0);
}
