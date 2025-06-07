#include <stdio.h>
#include <stdlib.h>
#include "bst_stat.h"

static BookStatNode* createBookStatNode(BookStat stat) {
    BookStatNode* node = (BookStatNode*)malloc(sizeof(BookStatNode));
    if (node == NULL) {
        printf("Lỗi: Không thể cấp phát bộ nhớ cho node thống kê\n");
        return NULL;
    }
    node->stat = stat;
    node->left = node->right = NULL;
    return node;
}

BookStatNode* insertBookStat(BookStatNode* root, BookStat stat) {
    if (root == NULL) {
        return createBookStatNode(stat);
    }
    if (stat.borrowCount < root->stat.borrowCount) {
        root->left = insertBookStat(root->left, stat);
    } else {
        root->right = insertBookStat(root->right, stat);
    }
    return root;
}

void reverseInorder(BookStatNode* root, int* printed, int N) {
    if (root == NULL || *printed >= N) return;
    reverseInorder(root->right, printed, N);
    if (*printed < N && root->stat.borrowCount > 0) {
        int index = timViTriSach(root->stat.bookID);
        if (index != -1) {
            printf("📚 %s - %s (%d lần)\n", root->stat.bookID, books[index].title, root->stat.borrowCount);
        } else {
            printf("📚 %s (%d lần)\n", root->stat.bookID, root->stat.borrowCount);
        }
        (*printed)++;
    }
    reverseInorder(root->left, printed, N);
}

void freeBookStatBST(BookStatNode* root) {
    if (root != NULL) {
        freeBookStatBST(root->left);
        freeBookStatBST(root->right);
        free(root);
    }
}
