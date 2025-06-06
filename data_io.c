#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "common.h"
#include "data_io.h"

void saveBooks(const char* filename) {
    FILE* f = fopen(filename, "w");
    if (!f) {
        printf("⚠️  Không thể mở %s để ghi\n", filename);
        return;
    }
    for (int i = 0; i < bookCount; i++) {
        fprintf(f, "%s|%s|%s|%s|%d|%d\n", books[i].id, books[i].title, books[i].author,
                books[i].category, books[i].price, books[i].available);
    }
    fclose(f);
}

void loadBooks(const char* filename) {
    FILE* f = fopen(filename, "r");
    if (!f) return; // Không có file thì bỏ qua

    char line[512];
    bookCount = 0;
    while (fgets(line, sizeof(line), f) && bookCount < MAX_BOOKS) {
        line[strcspn(line, "\n")] = '\0';
        char* token = strtok(line, "|");
        if (!token) continue;
        strcpy(books[bookCount].id, token);
        token = strtok(NULL, "|");
        if (!token) continue;
        strcpy(books[bookCount].title, token);
        token = strtok(NULL, "|");
        if (!token) continue;
        strcpy(books[bookCount].author, token);
        token = strtok(NULL, "|");
        if (!token) continue;
        strcpy(books[bookCount].category, token);
        token = strtok(NULL, "|");
        if (!token) continue;
        books[bookCount].price = atoi(token);
        token = strtok(NULL, "|");
        books[bookCount].available = token ? atoi(token) : 1;
        bookCount++;
    }
    fclose(f);
}

void saveReaders(const char* filename) {
    FILE* f = fopen(filename, "w");
    if (!f) {
        printf("⚠️  Không thể mở %s để ghi\n", filename);
        return;
    }
    for (int i = 0; i < readerCount; i++) {
        fprintf(f, "%s|%s|%s|%d|", readers[i].id, readers[i].name,
                readers[i].department, readers[i].borrowedCount);
        for (int j = 0; j < readers[i].borrowedCount; j++) {
            fprintf(f, "%s", readers[i].borrowedBookIDs[j]);
            if (j < readers[i].borrowedCount - 1) fprintf(f, ",");
        }
        fprintf(f, "\n");
    }
    fclose(f);
}

void loadReaders(const char* filename) {
    FILE* f = fopen(filename, "r");
    if (!f) return;

    char line[512];
    readerCount = 0;
    while (fgets(line, sizeof(line), f) && readerCount < MAX_READERS) {
        line[strcspn(line, "\n")] = '\0';
        char* token = strtok(line, "|");
        if (!token) continue;
        strcpy(readers[readerCount].id, token);
        token = strtok(NULL, "|");
        if (!token) continue;
        strcpy(readers[readerCount].name, token);
        token = strtok(NULL, "|");
        if (!token) continue;
        strcpy(readers[readerCount].department, token);
        token = strtok(NULL, "|");
        if (!token) continue;
        readers[readerCount].borrowedCount = atoi(token);
        token = strtok(NULL, "|");
        int count = 0;
        if (token) {
            char* bid = strtok(token, ",");
            while (bid && count < MAX_BORROWED) {
                strcpy(readers[readerCount].borrowedBookIDs[count], bid);
                bid = strtok(NULL, ",");
                count++;
            }
        }
        readers[readerCount].borrowedCount = count;
        readerCount++;
    }
    fclose(f);
}
