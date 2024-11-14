#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// Khai bao cau truc cua mot node trong danh sach
typedef struct Node {
    char word[6];   // Tu
    struct Node* next; // Con tro toi node tiep theo
} Node;

// Cau truc cua danh sach lien ket
typedef struct LinkedList {
    Node* head; // Con tro toi dau danh sach
} LinkedList;

// Ham khoi tao danh sach lien ket
void initialize_list(LinkedList* list) {
    list->head = NULL;
}

// Ham tao mot node moi voi tu
Node* create_node(const char* word) {
    Node* new_node = (Node*)malloc(sizeof(Node));
    strcpy(new_node->word, word);
    new_node->next = NULL;
    return new_node;
}

// Ham them tu vao danh sach theo thu tu
void insert_word(LinkedList* list, const char* word) {
    Node* new_node = create_node(word);
    if (list->head == NULL) {
        list->head = new_node;
    } else {
        Node* current = list->head;
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = new_node;
    }
}

// Ham tach cau thanh cac tu va chen vao danh sach lien ket
void split_words(char* sentence, LinkedList* list) {
    char word[100];
    int i = 0, j = 0;

    while (sentence[i] != '\0') {
        if (isalnum(sentence[i])) {  // Kiem tra xem ky tu co phai la chu hoac so
            word[j++] = tolower(sentence[i]);  // Chuyen ky tu thanh chu thuong
        } else if (j > 0) {  // Neu gap dau cach hoac ky tu khong phai chu so, va tu da co
            word[j] = '\0';  // Ket thuc tu
            insert_word(list, word);
            j = 0;  // Dat lai chi so
        }
        i++;
    }

    if (j > 0) {  // Neu cau ket thuc ma con tu chua duoc them
        word[j] = '\0';
        insert_word(list, word);
    }
}

// Ham dem so luong tu trong danh sach
int count_words(LinkedList* list) {
    int count = 0;
    Node* current = list->head;

    while (current != NULL) {
        count++;
        current = current->next;
    }
    return count;
}

// Ham in danh sach cac tu trong cau
void print_words(LinkedList* list) {
    Node* current = list->head;
    while (current != NULL) {
        printf("%s ", current->word);
        current = current->next;
    }
    printf("\n");
}

// Ham liet ke cac tu khac nhau trong cau va dem so lan xuat hien cua chung
void print_list_and_count_word(LinkedList* list) {
    Node* current = list->head;
    
    while (current != NULL) {
        int count = 0;
        Node* temp = list->head;

        // Dem so lan xuat hien cua tu hien tai trong danh sach
        while (temp != NULL) {
            if (strcmp(current->word, temp->word) == 0) {
                count++;
            }
            temp = temp->next;
        }

        // In tu va so lan xuat hien neu chua in tu nay
        Node* check = list->head;
        int printed = 0;
        while (check != current) {
            if (strcmp(current->word, check->word) == 0) {
                printed = 1;
                break;
            }
            check = check->next;
        }

        if (!printed) {
            printf("Tu '%s' xuat hien %d lan.\n", current->word, count);
        }
        
        current = current->next;
    }
}


// Ham tim tu xuat hien nhieu nhat trong danh sach
void find_most_frequent_word(LinkedList* list) {
    Node* current = list->head;
    Node* most_frequent = NULL;
    int max_count = 0;

    while (current != NULL) {
        int count = 0;
        Node* temp = list->head;
        // Dem so lan xuat hien cua tu nay trong danh sach
        while (temp != NULL) {
            if (strcmp(current->word, temp->word) == 0) {
                count++;
            }
            temp = temp->next;
        }

        if (count > max_count) {
            max_count = count;
            most_frequent = current;
        }
        current = current->next;
    }

    if (most_frequent != NULL) {
        printf("Tu xuat hien nhieu nhat: '%s',xuat hien %d lan.\n", most_frequent->word, max_count);
    }
}

// Ham loai bo tu lap lai lien tiep trong danh sach lien ket
void remove_redundant_repeated_words(LinkedList* list) {
    Node* current = list->head;

    while (current != NULL && current->next != NULL) {
        if (strcmp(current->word, current->next->word) == 0) {
            Node* temp = current->next;
            current->next = temp->next;
            free(temp);
        } else {
            current = current->next;
        }
    }
}

// Ham in lai cau sau khi loai bo tu lap lai
void print_sentence_after_removal(LinkedList* list) {
    Node* current = list->head;
    int first = 1;  // De khong in khoang trang truoc tu dau tien

    while (current != NULL) {
        if (first) {
            printf("%s", current->word);
            first = 0;
        } else {
            printf(" %s", current->word);
        }
        current = current->next;
    }
    printf("\n");
}

int main() {
    LinkedList sentence;
    initialize_list(&sentence);

    // Nhap vao mot cau tu nguoi dung
    char input[500];
    printf("Nhap cau: ");
    fgets(input, 500, stdin);

    // Tach cau thanh cac tu va chen vao danh sach lien ket
    split_words(input, &sentence);

    // Dem so luong tu trong danh sach
    printf("\nSo tu trong cau: %d\n", count_words(&sentence));
    // In danh sach cac tu trong cau
    printf("Danh sach cac tu trong cau:\n");

    print_list_and_count_word(&sentence);

    // Tim tu xuat hien nhieu nhat
    find_most_frequent_word(&sentence);

    // Loai bo tu lap lai lien tiep
    remove_redundant_repeated_words(&sentence);

    // In lai cau sau khi loai bo tu lap lai
    printf("\nCau sau khi loai bo tu lap lai:(chi loai bo 2 tu giong nhau lien nhau)\n");
    print_sentence_after_removal(&sentence);

    // Dem so luong tu trong danh sach
    printf("\nSo tu trong cau: %d\n", count_words(&sentence));

    return 0;
}
