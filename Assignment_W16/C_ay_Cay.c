#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node {
    char title[100];        // Tên chương/mục
    int pages;              // Số trang của chương/mục
    int child_count;        // Số lượng con
    struct Node** children; // Con trỏ tới danh sách các node con
} Node;
Node* create_node(const char* title, int pages) {
    Node* new_node = (Node*)malloc(sizeof(Node));
    strcpy(new_node->title, title);
    new_node->pages = pages;
    new_node->child_count = 0;
    new_node->children = NULL; // Chưa có con
    return new_node;
}
void add_child(Node* parent, Node* child) {
    parent->child_count++;
    parent->children = (Node**)realloc(parent->children, parent->child_count * sizeof(Node*));
    parent->children[parent->child_count - 1] = child;
}
int count_chapters(Node* root) {
    if (root == NULL) return 0;
    int count = (strstr(root->title, "Chapter") != NULL) ? 1 : 0;
    for (int i = 0; i < root->child_count; i++) {
        count += count_chapters(root->children[i]);
    }
    return count;
}
int calculate_total_pages(Node* node) {
    if (node == NULL) return 0;
    // Nếu node không có con, trả về số trang của chính nó
    if (node->child_count == 0) return node->pages;
    // Tính tổng số trang của node dựa trên các node con
    int total_pages = 0;
    for (int i = 0; i < node->child_count; i++) {
        total_pages += calculate_total_pages(node->children[i]);
    }
    return total_pages;
}
void find_longest_chapter(Node* root, Node** longest, int* max_pages) {
    if (root == NULL) return;
    if (strstr(root->title, "Chapter") != NULL && root->pages > *max_pages) {
        *longest = root;
        *max_pages = root->pages;
    }
    for (int i = 0; i < root->child_count; i++) {
        find_longest_chapter(root->children[i], longest, max_pages);
    }
}
int find_and_delete(Node* root, const char* title_to_delete) {
    if (root == NULL) return 0;
    for (int i = 0; i < root->child_count; i++) {
        if (strcmp(root->children[i]->title, title_to_delete) == 0) {
            int removed_pages = root->children[i]->pages;
            // Giải phóng node bị xoá
            free(root->children[i]);
            // Dịch chuyển danh sách con
            for (int j = i; j < root->child_count - 1; j++) {
                root->children[j] = root->children[j + 1];
            }
            root->child_count--;
            root->pages -= removed_pages;
            return removed_pages;
        } else {
            int removed_pages = find_and_delete(root->children[i], title_to_delete);
            if (removed_pages > 0) {
                root->pages -= removed_pages;
                return removed_pages;
            }
        }
    }
    return 0;
}
void display_toc(Node* node, int level, int start_page) {
    if (node == NULL) return;
    int end_page = start_page + node->pages - 1;
    // In tiêu đề với khoảng cách trang
    for (int i = 0; i < level; i++) {
        printf("    "); // Thụt lề theo cấp độ
    }
    printf("- %s (%d-%d)\n", node->title, start_page, end_page);
    // Duyệt qua các node con
    int current_page = start_page;
    for (int i = 0; i < node->child_count; i++) {
        display_toc(node->children[i], level + 1, current_page);
        current_page += calculate_total_pages(node->children[i]);
    }
}
int main() {
    Node* root = create_node("Electronic Devices and Circuit Theory", 0);

    Node* chapter1 = create_node("Chapter 1: Introduction", 30);
    add_child(chapter1, create_node("Section 1.1", 10));
    add_child(chapter1, create_node("Section 1.2", 20));

    Node* chapter2 = create_node("Chapter 2: BJT", 50);
    add_child(chapter2, create_node("Section 2.1", 25));
    add_child(chapter2, create_node("Section 2.2", 25));

    Node* chapter3 = create_node("Chapter 3: FET", 30);
    add_child(chapter3, create_node("Section 3.1", 20));
    add_child(chapter3, create_node("Section 3.2", 5));
    add_child(chapter3, create_node("Section 3.3", 5));

    add_child(root, chapter1);
    add_child(root, chapter2);
    add_child(root, chapter3);
    // Tính toán lại số trang cho node gốc
    root->pages = calculate_total_pages(root);
    // Hiển thị mục lục
    printf("Table of Contents:\n");
    display_toc(root, 0, 1);
    // Đếm số chương
    printf("Number of chapters: %d\n", count_chapters(root));
    // Tìm chương dài nhất
    Node* longest = NULL;
    int max_pages = 0;
    find_longest_chapter(root, &longest, &max_pages);
    if (longest != NULL) {
        printf("\nLongest chapter: %s with %d pages\n", longest->title, max_pages);
    }
    // Xoá mục và cập nhật số trang
    find_and_delete(root, "Section 2.2");
    printf("\nDeleted Section 2.2\n");
    printf("Updated root pages: %d\n", root->pages);
    printf("Table of Contents:\n");
    display_toc(root, 0, 1);
    // Tìm chương dài nhất sau khi xoá
    longest = NULL;
    max_pages = 0;
    find_longest_chapter(root, &longest, &max_pages);
    if (longest != NULL) {
        printf("\nLongest chapter: %s with %d pages\n", longest->title, max_pages);
    }
    return 0;
}
