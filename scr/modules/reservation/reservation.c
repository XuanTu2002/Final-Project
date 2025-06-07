#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "../../../include/common.h"
#include "reservation.h"

#define MAX_BOOKS_WITH_RESERVATIONS 1000

// Mảng các hàng đợi ưu tiên, mỗi sách có một hàng đợi
ReservationQueue *bookQueues[MAX_BOOKS_WITH_RESERVATIONS];
int queueCount = 0;

/**
 * Tìm vị trí của hàng đợi đặt chỗ cho một sách trong mảng bookQueues
 * @param bookID Mã sách cần tìm
 * @return Vị trí của hàng đợi trong mảng, -1 nếu không tìm thấy
 */
int timViTriHangDoi(const char *bookID)
{
    for (int i = 0; i < queueCount; i++)
    {
        if (strcmp(bookQueues[i]->bookID, bookID) == 0)
        {
            return i;
        }
    }
    return -1;
}

/**
 * Tạo một node mới cho hàng đợi đặt chỗ
 * @param bookID Mã sách
 * @param readerID Mã bạn đọc
 * @param priority Mức độ ưu tiên
 * @return Con trỏ đến node mới được tạo
 */
ReservationNode *taoNodeDatCho(const char *bookID, const char *readerID, int priority)
{
    ReservationNode *newNode = (ReservationNode *)malloc(sizeof(ReservationNode));
    if (newNode == NULL)
    {
        printf("Lỗi: Không thể cấp phát bộ nhớ cho node đặt chỗ mới\n");
        return NULL;
    }

    strcpy(newNode->bookID, bookID);
    strcpy(newNode->readerID, readerID);
    newNode->priority = priority;
    newNode->next = NULL;

    return newNode;
}

/**
 * Tạo một hàng đợi mới cho sách
 * @param bookID Mã sách
 * @return Con trỏ đến hàng đợi mới được tạo
 */
ReservationQueue *taoHangDoiMoi(const char *bookID)
{
    ReservationQueue *newQueue = (ReservationQueue *)malloc(sizeof(ReservationQueue));
    if (newQueue == NULL)
    {
        printf("Lỗi: Không thể cấp phát bộ nhớ cho hàng đợi mới\n");
        return NULL;
    }

    strcpy(newQueue->bookID, bookID);
    newQueue->front = NULL;
    newQueue->count = 0;

    return newQueue;
}

/**
 * Thêm một đặt chỗ vào hàng đợi ưu tiên
 * @param queue Con trỏ đến hàng đợi
 * @param bookID Mã sách
 * @param readerID Mã bạn đọc
 * @param priority Mức độ ưu tiên
 * @return 1 nếu thành công, 0 nếu thất bại
 */
int themVaoHangDoi(ReservationQueue *queue, const char *bookID, const char *readerID, int priority)
{
    // Kiểm tra xem bạn đọc đã đặt chỗ cho sách này chưa
    ReservationNode *current = queue->front;
    while (current != NULL)
    {
        if (strcmp(current->readerID, readerID) == 0)
        {
            return 0; // Bạn đọc đã đặt chỗ rồi
        }
        current = current->next;
    }

    // Tạo node mới
    ReservationNode *newNode = taoNodeDatCho(bookID, readerID, priority);
    if (newNode == NULL)
    {
        return 0;
    }

    // Nếu hàng đợi rỗng hoặc node mới có ưu tiên cao hơn node đầu tiên
    if (queue->front == NULL || priority < queue->front->priority)
    {
        newNode->next = queue->front;
        queue->front = newNode;
    }
    else
    {
        // Tìm vị trí thích hợp để chèn node mới theo thứ tự ưu tiên
        current = queue->front;
        while (current->next != NULL && current->next->priority <= priority)
        {
            current = current->next;
        }

        newNode->next = current->next;
        current->next = newNode;
    }

    queue->count++;
    return 1;
}

/**
 * Xóa một đặt chỗ khỏi hàng đợi ưu tiên
 * @param queue Con trỏ đến hàng đợi
 * @param readerID Mã bạn đọc cần xóa
 * @return 1 nếu thành công, 0 nếu không tìm thấy
 */
int xoaKhoiHangDoi(ReservationQueue *queue, const char *readerID)
{
    if (queue->front == NULL)
    {
        return 0; // Hàng đợi rỗng
    }

    // Nếu node đầu tiên là node cần xóa
    if (strcmp(queue->front->readerID, readerID) == 0)
    {
        ReservationNode *temp = queue->front;
        queue->front = queue->front->next;
        free(temp);
        queue->count--;
        return 1;
    }

    // Tìm node cần xóa
    ReservationNode *current = queue->front;
    while (current->next != NULL && strcmp(current->next->readerID, readerID) != 0)
    {
        current = current->next;
    }

    // Nếu tìm thấy node cần xóa
    if (current->next != NULL)
    {
        ReservationNode *temp = current->next;
        current->next = temp->next;
        free(temp);
        queue->count--;
        return 1;
    }

    return 0; // Không tìm thấy
}

/**
 * Giải phóng bộ nhớ của một hàng đợi
 * @param queue Con trỏ đến hàng đợi cần giải phóng
 */
void giaiPhongHangDoi(ReservationQueue *queue)
{
    if (queue == NULL)
    {
        return;
    }

    ReservationNode *current = queue->front;
    ReservationNode *next;

    while (current != NULL)
    {
        next = current->next;
        free(current);
        current = next;
    }

    free(queue);
}

// ==============================
// 1. ĐẶT CHỖ SÁCH
// ==============================
void datChoSach()
{
    char bookID[10], readerID[10];
    int priority;

    printf("📚 Nhập mã sách cần đặt chỗ: ");
    scanf("%s", bookID);
    int bIndex = timViTriSach(bookID);
    if (bIndex == -1)
    {
        printf("❌ Không tìm thấy sách!\n");
        return;
    }

    if (books[bIndex].available == 1)
    {
        printf("✅ Sách hiện đang có sẵn. Bạn có thể mượn trực tiếp.\n");
        // Tiếp tục cho người dùng đặt chỗ mặc dù sách có sẵn
        char choice;
        printf("Bạn vẫn muốn đặt chỗ không? (y/n): ");
        scanf(" %c", &choice);
        if (choice != 'y' && choice != 'Y')
        {
            return;
        }
    }

    printf("👤 Nhập mã bạn đọc: ");
    scanf("%s", readerID);
    int rIndex = timViTriBanDoc(readerID);
    if (rIndex == -1)
    {
        printf("❌ Không tìm thấy bạn đọc!\n");
        return;
    }

    printf("🔢 Nhập mức độ ưu tiên (1: Giảng viên/Cán bộ, 2: Sinh viên): ");
    scanf("%d", &priority);
    if (priority < 1 || priority > 2)
    {
        printf("⚠️ Mức độ ưu tiên không hợp lệ. Sử dụng mức mặc định (2).\n");
        priority = 2;
    }

    // Tìm hoặc tạo hàng đợi cho sách
    int qIndex = timViTriHangDoi(bookID);
    ReservationQueue *queue;

    if (qIndex == -1)
    {
        // Tạo hàng đợi mới nếu chưa có
        queue = taoHangDoiMoi(bookID);
        if (queue == NULL)
        {
            printf("❌ Không thể tạo hàng đợi đặt chỗ!\n");
            return;
        }
        bookQueues[queueCount++] = queue;
    }
    else
    {
        queue = bookQueues[qIndex];
    }

    // Thêm đặt chỗ vào hàng đợi
    if (themVaoHangDoi(queue, bookID, readerID, priority))
    {
        printf("✅ Đặt chỗ thành công! Bạn đã được thêm vào hàng đợi với mức ưu tiên %d.\n", priority);
    }
    else
    {
        printf("⚠️ Bạn đã đặt chỗ cho sách này rồi!\n");
    }
}

// ==============================
// 2. HIỂN THỊ DANH SÁCH ĐẶT CHỖ
// ==============================
void hienThiDanhSachDatCho()
{
    if (queueCount == 0)
    {
        printf("📭 Không có yêu cầu đặt chỗ nào.\n");
        return;
    }

    printf("\n📋 DANH SÁCH ĐẶT CHỖ THEO TỪNG SÁCH:\n");
    printf("=========================================\n");

    int totalReservations = 0;

    for (int i = 0; i < queueCount; i++)
    {
        ReservationQueue *queue = bookQueues[i];

        if (queue->count > 0)
        {
            // Tìm thông tin sách để hiển thị
            int bookIndex = timViTriSach(queue->bookID);
            if (bookIndex != -1)
            {
                printf("\n📚 SÁCH: %s - %s\n", queue->bookID, books[bookIndex].title);
                printf("  Hàng đợi (%d người đặt):\n", queue->count);

                // Hiển thị danh sách đặt chỗ theo thứ tự ưu tiên
                ReservationNode *current = queue->front;
                int position = 1;

                while (current != NULL)
                {
                    // Tìm thông tin bạn đọc để hiển thị
                    int readerIndex = timViTriBanDoc(current->readerID);
                    printf("  %d. Mã: %s", position, current->readerID);

                    if (readerIndex != -1)
                    {
                        printf(" - Tên: %s", readers[readerIndex].name);
                    }

                    printf(" - Ưu tiên: %d (%s)\n",
                           current->priority,
                           current->priority == 1 ? "Giảng viên/Cán bộ" : "Sinh viên");

                    current = current->next;
                    position++;
                    totalReservations++;
                }
            }
        }
    }

    printf("\n🔢 TỔNG SỐ ĐẶT CHỖ: %d\n", totalReservations);
    printf("=========================================\n");
}

// ==============================
// 3. HỦY ĐẶT CHỖ
// ==============================
void huyDatCho()
{
    char bookID[10], readerID[10];

    printf("📚 Nhập mã sách cần huỷ đặt chỗ: ");
    scanf("%s", bookID);
    printf("👤 Nhập mã bạn đọc: ");
    scanf("%s", readerID);

    // Tìm hàng đợi của sách
    int qIndex = timViTriHangDoi(bookID);
    if (qIndex == -1)
    {
        printf("❌ Không tìm thấy sách có yêu cầu đặt chỗ nào.\n");
        return;
    }

    // Xóa đặt chỗ khỏi hàng đợi
    ReservationQueue *queue = bookQueues[qIndex];
    if (xoaKhoiHangDoi(queue, readerID))
    {
        printf("✅ Đã huỷ đặt chỗ thành công!\n");

        // Nếu hàng đợi rỗng, xóa hàng đợi khỏi mảng
        if (queue->count == 0)
        {
            giaiPhongHangDoi(queue);
            for (int i = qIndex; i < queueCount - 1; i++)
            {
                bookQueues[i] = bookQueues[i + 1];
            }
            queueCount--;
        }
    }
    else
    {
        printf("❌ Không tìm thấy thông tin đặt chỗ.\n");
    }
}

// ==============================
// 4. HIỂN THỊ NGƯỜI TIẾP THEO ĐƯỢC MƯỢN SÁCH
// ==============================
void hienThiNguoiTiepTheo()
{
    char bookID[10];

    printf("📚 Nhập mã sách cần xem hàng đợi: ");
    scanf("%s", bookID);

    // Tìm hàng đợi của sách
    int qIndex = timViTriHangDoi(bookID);
    if (qIndex == -1)
    {
        printf("❌ Không có ai đang đặt chỗ cho sách này.\n");
        return;
    }

    ReservationQueue *queue = bookQueues[qIndex];
    if (queue->front == NULL)
    {
        printf("❌ Hàng đợi rỗng.\n");
        return;
    }

    // Hiển thị người đầu tiên trong hàng đợi
    ReservationNode *next = queue->front;
    int readerIndex = timViTriBanDoc(next->readerID);

    printf("\n🔜 NGƯỜI TIẾP THEO ĐƯỢC MƯỢN SÁCH:\n");
    printf("  Mã sách: %s\n", bookID);

    int bookIndex = timViTriSach(bookID);
    if (bookIndex != -1)
    {
        printf("  Tên sách: %s\n", books[bookIndex].title);
    }

    printf("  Mã bạn đọc: %s\n", next->readerID);

    if (readerIndex != -1)
    {
        printf("  Tên bạn đọc: %s\n", readers[readerIndex].name);
    }

    printf("  Mức ưu tiên: %d (%s)\n",
           next->priority,
           next->priority == 1 ? "Giảng viên/Cán bộ" : "Sinh viên");
}

// ==============================
// MENU MODULE ĐẶT CHỖ SÁCH
// ==============================
void runReservationModule()
{
    int ch;
    do
    {
        printf("\n======= 📌 ĐẶT CHỖ SÁCH (PRIORITY QUEUE) =======\n");
        printf("1. Đặt chỗ sách\n");
        printf("2. Hiển thị danh sách đặt chỗ\n");
        printf("3. Huỷ đặt chỗ\n");
        printf("4. Xem người tiếp theo được mượn sách\n");
        printf("0. Quay lại menu chính\n");
        printf("=============================================\n");
        printf("Nhập lựa chọn: ");
        scanf("%d", &ch);

        switch (ch)
        {
        case 1:
            datChoSach();
            break;
        case 2:
            hienThiDanhSachDatCho();
            break;
        case 3:
            huyDatCho();
            break;
        case 4:
            hienThiNguoiTiepTheo();
            break;
        case 0:
            // Giải phóng bộ nhớ trước khi thoát
            for (int i = 0; i < queueCount; i++)
            {
                giaiPhongHangDoi(bookQueues[i]);
            }
            queueCount = 0;
            printf("↩️  Quay lại menu chính...\n");
            break;
        default:
            printf("❌ Lựa chọn không hợp lệ!\n");
        }

    } while (ch != 0);
}
