/*

Cài đặt môi trường debugging 

thực hiện debugging để in ra các vị trí lưu trữ phần tử 2 đa thức nhập và đa thức tổng 
-> in local variables  */

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h> 

struct Node {
    int data; // Du lieu cua node
    struct Node* next; // Con tro den node tiep theo
};

// Ham chen node moi sau node T
void insert(struct Node* T, int newData) {
    if (T == NULL) {
        printf("Node truoc do khong the la NULL\n");
        return;
    } else {
        // Cap phat bo nho cho node moi
        struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
        newNode->data = newData;
        newNode->next = T->next;
        T->next = newNode;
    }
}

// Ham in danh sach lien ket
void printList(struct Node* head) {
    struct Node* current = head;
    while (current != NULL) {
        // Lay 3 ky tu cuoi cua dia chi bo nho
        uintptr_t address = (uintptr_t)current->next;
        printf("Du lieu: %d, Tiep theo: %03lX -> ", current->data, address & 0xFFF); // Hien thi 3 ky hex cuoi
        current = current->next;
    }
    printf("NULL\n");
}

// Ham tao node moi
struct Node* createNode(int data) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}

// Ham xoa node cuoi
void deleteLastNode(struct Node** head_ref) {
    // Neu danh sach rong
    if (*head_ref == NULL) return;

    struct Node* temp = *head_ref;

    // Neu chi co 1 node
    if (temp->next == NULL) {
        free(temp);
        *head_ref = NULL;
        return;
    }

    // Duyet den node thu hai cuoi
    while (temp->next->next != NULL) {
        temp = temp->next;
    }

    // Xoa node cuoi
    free(temp->next);
    temp->next = NULL;
}

// Ham xoa mot node cho truoc
void deleteNode(struct Node** head_ref, struct Node* T) {
    // Neu danh sach rong hoac T la NULL
    if (*head_ref == NULL || T == NULL) return;

    // Neu node can xoa la node dau
    if (*head_ref == T) {
        *head_ref = T->next;
        free(T);
        return;
    }

    // Tim node truoc T
    struct Node* temp = *head_ref;
    while (temp != NULL && temp->next != T) {
        temp = temp->next;
    }

    // Neu node khong duoc tim thay
    if (temp == NULL) return;

    // Ngat lien ket node
    temp->next = T->next;
    free(T);
}

int main() {
    // Tao danh sach lien ket 1 -> 2 -> 3 -> NULL
    struct Node* head = createNode(1);
    head->next = createNode(2);
    head->next->next = createNode(3);

    printf("Danh sach goc: ");
    printList(head);

    // Chen node 4 sau node dau
    insert(head, 4);
    printf("Sau khi chen 4 sau node dau: ");
    printList(head);

    // Xoa node cuoi
    deleteLastNode(&head);
    printf("Sau khi xoa node cuoi: ");
    printList(head);

    // Xoa mot node cu the (node thu hai trong truong hop nay)
    deleteNode(&head, head->next);
    printf("Sau khi xoa node thu hai: ");
    printList(head);

    return 0;
}
