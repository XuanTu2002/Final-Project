#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "bst.h"

/**
 * Tạo một node mới cho cây BST
 */
BookNode* createNode(Book book) {
    BookNode* newNode = (BookNode*)malloc(sizeof(BookNode));
    if (newNode == NULL) {
        printf("Lỗi: Không thể cấp phát bộ nhớ cho node mới\n");
        return NULL;
    }
    
    newNode->book = book;
    newNode->left = NULL;
    newNode->right = NULL;
    
    return newNode;
}

/**
 * So sánh hai tiêu đề sách (không phân biệt hoa thường)
 * Trả về: < 0 nếu title1 < title2, 0 nếu bằng nhau, > 0 nếu title1 > title2
 */
int compareTitle(const char* title1, const char* title2) {
    char t1[100], t2[100];
    strcpy(t1, title1);
    strcpy(t2, title2);
    
    // Chuyển đổi thành chữ thường để so sánh không phân biệt hoa thường
    for (int i = 0; t1[i]; i++) {
        if (t1[i] >= 'A' && t1[i] <= 'Z') {
            t1[i] = t1[i] + 32;
        }
    }
    
    for (int i = 0; t2[i]; i++) {
        if (t2[i] >= 'A' && t2[i] <= 'Z') {
            t2[i] = t2[i] + 32;
        }
    }
    
    return strcmp(t1, t2);
}

/**
 * Thêm một sách vào cây BST
 */
BookNode* insertBook(BookNode* root, Book book) {
    // Nếu cây rỗng, tạo node mới làm gốc
    if (root == NULL) {
        return createNode(book);
    }
    
    // So sánh tiêu đề sách để quyết định thêm vào nhánh trái hay phải
    int comparison = compareTitle(book.title, root->book.title);
    
    if (comparison < 0) {
        // Tiêu đề nhỏ hơn, thêm vào nhánh trái
        root->left = insertBook(root->left, book);
    } else if (comparison > 0) {
        // Tiêu đề lớn hơn, thêm vào nhánh phải
        root->right = insertBook(root->right, book);
    } else {
        // Tiêu đề trùng nhau, kiểm tra mã sách
        if (strcmp(book.id, root->book.id) != 0) {
            // Nếu mã sách khác nhau, thêm vào nhánh phải
            root->right = insertBook(root->right, book);
        } else {
            // Nếu mã sách giống nhau, không thêm (tránh trùng lặp)
            printf("Sách có mã %s đã tồn tại trong cây BST\n", book.id);
        }
    }
    
    return root;
}

/**
 * Tìm kiếm sách trong cây BST theo tiêu đề
 */
BookNode* searchBookByTitle(BookNode* root, const char* title) {
    // Nếu cây rỗng hoặc tìm thấy sách có tiêu đề trùng khớp
    if (root == NULL || compareTitle(root->book.title, title) == 0) {
        return root;
    }
    
    // Nếu tiêu đề cần tìm nhỏ hơn tiêu đề của node hiện tại, tìm trong nhánh trái
    if (compareTitle(title, root->book.title) < 0) {
        return searchBookByTitle(root->left, title);
    }
    
    // Ngược lại, tìm trong nhánh phải
    return searchBookByTitle(root->right, title);
}

/**
 * Tìm kiếm sách trong cây BST theo mã sách
 */
BookNode* searchBookById(BookNode* root, const char* id) {
    if (root == NULL) {
        return NULL;
    }
    
    // Kiểm tra node hiện tại
    if (strcmp(root->book.id, id) == 0) {
        return root;
    }
    
    // Tìm kiếm trong cả hai nhánh vì mã sách không tuân theo thứ tự của cây
    BookNode* leftResult = searchBookById(root->left, id);
    if (leftResult != NULL) {
        return leftResult;
    }
    
    return searchBookById(root->right, id);
}

/**
 * Tìm node có giá trị nhỏ nhất trong cây con
 */
BookNode* findMinValueNode(BookNode* node) {
    BookNode* current = node;
    
    // Tìm node ngoài cùng bên trái
    while (current && current->left != NULL) {
        current = current->left;
    }
    
    return current;
}

/**
 * Xóa một sách khỏi cây BST
 */
BookNode* deleteBookFromBST(BookNode* root, const char* id) {
    // Trường hợp cơ sở: cây rỗng
    if (root == NULL) {
        return root;
    }
    
    // Tìm node cần xóa
    BookNode* nodeToDelete = searchBookById(root, id);
    if (nodeToDelete == NULL) {
        printf("Không tìm thấy sách có mã %s để xóa\n", id);
        return root;
    }
    
    // So sánh tiêu đề để quyết định đi xuống nhánh nào
    int comparison = compareTitle(nodeToDelete->book.title, root->book.title);
    
    if (comparison < 0) {
        // Node cần xóa nằm ở nhánh trái
        root->left = deleteBookFromBST(root->left, id);
    } else if (comparison > 0) {
        // Node cần xóa nằm ở nhánh phải
        root->right = deleteBookFromBST(root->right, id);
    } else if (strcmp(root->book.id, id) == 0) {
        // Đây là node cần xóa
        
        // Trường hợp 1: Node lá hoặc có một con
        if (root->left == NULL) {
            BookNode* temp = root->right;
            free(root);
            return temp;
        } else if (root->right == NULL) {
            BookNode* temp = root->left;
            free(root);
            return temp;
        }
        
        // Trường hợp 2: Node có hai con
        // Tìm node kế thừa (node nhỏ nhất ở nhánh phải)
        BookNode* temp = findMinValueNode(root->right);
        
        // Sao chép thông tin từ node kế thừa
        root->book = temp->book;
        
        // Xóa node kế thừa
        root->right = deleteBookFromBST(root->right, temp->book.id);
    } else {
        // Tiêu đề trùng nhưng mã sách khác, tiếp tục tìm ở cả hai nhánh
        BookNode* found = searchBookById(root->left, id);
        if (found != NULL) {
            root->left = deleteBookFromBST(root->left, id);
        } else {
            root->right = deleteBookFromBST(root->right, id);
        }
    }
    
    return root;
}

/**
 * Duyệt cây BST theo thứ tự trung tố (Inorder Traversal)
 */
void inorderTraversal(BookNode* root) {
    if (root != NULL) {
        inorderTraversal(root->left);
        printf("Mã: %-10s | Tiêu đề: %-50s | Tác giả: %-30s | Thể loại: %-20s | Giá: %d\n",
               root->book.id, root->book.title, root->book.author, root->book.category, root->book.price);
        inorderTraversal(root->right);
    }
}

/**
 * Giải phóng bộ nhớ của cây BST
 */
void freeBST(BookNode* root) {
    if (root != NULL) {
        freeBST(root->left);
        freeBST(root->right);
        free(root);
    }
}

/**
 * Xây dựng cây BST từ mảng sách hiện có
 */
BookNode* buildBSTFromArray(Book books[], int count) {
    BookNode* root = NULL;
    
    for (int i = 0; i < count; i++) {
        root = insertBook(root, books[i]);
    }
    
    return root;
}

/**
 * Kiểm tra xem một chuỗi có chứa từ khóa không (không phân biệt hoa thường)
 */
int containsKeyword(const char* str, const char* keyword) {
    char s1[256], s2[256];
    strcpy(s1, str);
    strcpy(s2, keyword);
    
    // Chuyển đổi thành chữ thường
    for (int i = 0; s1[i]; i++) {
        if (s1[i] >= 'A' && s1[i] <= 'Z') {
            s1[i] = s1[i] + 32;
        }
    }
    
    for (int i = 0; s2[i]; i++) {
        if (s2[i] >= 'A' && s2[i] <= 'Z') {
            s2[i] = s2[i] + 32;
        }
    }
    
    return strstr(s1, s2) != NULL;
}

/**
 * Tìm kiếm sách trong cây BST theo từ khóa (tìm kiếm mờ)
 */
void searchBooksByKeyword(BookNode* root, const char* keyword, Book results[], int* count) {
    if (root == NULL) {
        return;
    }
    
    // Duyệt cây theo thứ tự trung tố
    searchBooksByKeyword(root->left, keyword, results, count);
    
    // Kiểm tra xem sách có chứa từ khóa trong tiêu đề, tác giả hoặc thể loại không
    if (containsKeyword(root->book.title, keyword) || 
        containsKeyword(root->book.author, keyword) || 
        containsKeyword(root->book.category, keyword)) {
        
        // Thêm sách vào mảng kết quả
        if (*count < MAX_BOOKS) {
            results[*count] = root->book;
            (*count)++;
        }
    }
    
    searchBooksByKeyword(root->right, keyword, results, count);
}
