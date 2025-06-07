#ifndef BST_STAT_H
#define BST_STAT_H

#include "../../../include/common.h"

/**
 * Thêm một thống kê sách vào cây BST theo số lần mượn
 * @param root  Gốc của cây
 * @param stat  Thông tin thống kê sách
 * @return Con trỏ đến gốc sau khi chèn
 */
BookStatNode* insertBookStat(BookStatNode* root, BookStat stat);

/**
 * Duyệt cây theo thứ tự giảm dần số lần mượn và in ra tối đa N kết quả
 * @param root     Gốc của cây
 * @param printed  Biến đếm số lượng đã in
 * @param N        Số lượng cần in
 */
void reverseInorder(BookStatNode* root, int* printed, int N);

/**
 * Giải phóng bộ nhớ của cây BST thống kê sách
 */
void freeBookStatBST(BookStatNode* root);

#endif /* BST_STAT_H */
