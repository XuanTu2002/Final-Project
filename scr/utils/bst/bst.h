#ifndef BST_H
#define BST_H

#include "../../../include/common.h"

/**
 * Cấu trúc node cho cây nhị phân tìm kiếm (BST)
 * Mỗi node chứa thông tin về một cuốn sách và con trỏ đến các node con
 */
typedef struct BookNode {
    Book book;                  // Thông tin sách
    struct BookNode* left;      // Con trỏ đến node con bên trái
    struct BookNode* right;     // Con trỏ đến node con bên phải
} BookNode;

/**
 * Tạo một node mới cho cây BST
 * @param book Thông tin sách cần thêm vào node
 * @return Con trỏ đến node mới được tạo
 */
BookNode* createNode(Book book);

/**
 * Thêm một sách vào cây BST
 * @param root Con trỏ đến node gốc của cây
 * @param book Thông tin sách cần thêm vào cây
 * @return Con trỏ đến node gốc của cây sau khi thêm
 */
BookNode* insertBook(BookNode* root, Book book);

/**
 * Tìm kiếm sách trong cây BST theo tiêu đề
 * @param root Con trỏ đến node gốc của cây
 * @param title Tiêu đề sách cần tìm
 * @return Con trỏ đến node chứa sách cần tìm, NULL nếu không tìm thấy
 */
BookNode* searchBookByTitle(BookNode* root, const char* title);

/**
 * Tìm kiếm sách trong cây BST theo mã sách
 * @param root Con trỏ đến node gốc của cây
 * @param id Mã sách cần tìm
 * @return Con trỏ đến node chứa sách cần tìm, NULL nếu không tìm thấy
 */
BookNode* searchBookById(BookNode* root, const char* id);

/**
 * Tìm node có giá trị nhỏ nhất trong cây con
 * @param node Con trỏ đến node gốc của cây con
 * @return Con trỏ đến node có giá trị nhỏ nhất
 */
BookNode* findMinValueNode(BookNode* node);

/**
 * Xóa một sách khỏi cây BST
 * @param root Con trỏ đến node gốc của cây
 * @param id Mã sách cần xóa
 * @return Con trỏ đến node gốc của cây sau khi xóa
 */
BookNode* deleteBookFromBST(BookNode* root, const char* id);

/**
 * Duyệt cây BST theo thứ tự trung tố (Inorder Traversal)
 * @param root Con trỏ đến node gốc của cây
 */
void inorderTraversal(BookNode* root);

/**
 * Giải phóng bộ nhớ của cây BST
 * @param root Con trỏ đến node gốc của cây
 */
void freeBST(BookNode* root);

/**
 * Xây dựng cây BST từ mảng sách hiện có
 * @param books Mảng sách
 * @param count Số lượng sách trong mảng
 * @return Con trỏ đến node gốc của cây BST
 */
BookNode* buildBSTFromArray(Book books[], int count);

/**
 * Tìm kiếm sách trong cây BST theo từ khóa (tìm kiếm mờ)
 * @param root Con trỏ đến node gốc của cây
 * @param keyword Từ khóa tìm kiếm
 * @param results Mảng kết quả tìm kiếm
 * @param count Con trỏ đến biến đếm số lượng kết quả
 */
void searchBooksByKeyword(BookNode* root, const char* keyword, Book results[], int* count);

#endif /* BST_H */
