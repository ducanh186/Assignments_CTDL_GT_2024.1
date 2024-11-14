#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Define structure for a node in the list
typedef struct Node {
    char file_name[100];    // File name
    long long size;         // File size in bytes
    char date[20];          // File creation or modification date, format "DD/MM/YYYY"
    struct Node* next;      // Pointer to the next node
} Node;

// Define structure for the linked list
typedef struct LinkedList {
    Node* head;             // Pointer to the head of the list
} LinkedList;

// Initialize the linked list
void initialize_list(LinkedList* list) {
    list->head = NULL;
}

// Compare two dates in the format "DD/MM/YYYY"
int compare_dates(const char* date1, const char* date2) {
    int day1, month1, year1;
    int day2, month2, year2;

    sscanf(date1, "%d/%d/%d", &day1, &month1, &year1);
    sscanf(date2, "%d/%d/%d", &day2, &month2, &year2);
    
    if (year1 != year2) return year1 - year2;
    if (month1 != month2) return month1 - month2;
    return day1 - day2;
}

// Insert a file into the list in chronological order
void insert_file_sorted(LinkedList* list, char* file_name, long long size, char* date) {
    Node* new_node = (Node*)malloc(sizeof(Node));
    strcpy(new_node->file_name, file_name);
    new_node->size = size;
    strcpy(new_node->date, date);
    new_node->next = NULL;
    
    if (list->head == NULL || compare_dates(list->head->date, date) < 0) {
        new_node->next = list->head;
        list->head = new_node;
    } else {
        Node* current = list->head;
        while (current->next != NULL && compare_dates(current->next->date, date) >= 0) {
            current = current->next;
        }
        new_node->next = current->next;
        current->next = new_node;
    }
}

// Calculate the total size of all files in the list
long long calculate_total_size(LinkedList* list) {
    long long total_size = 0;
    Node* current = list->head;
    while (current != NULL) {
        total_size += current->size;
        current = current->next;
    }
    return total_size;
}

// Remove the smallest file
void remove_smallest_file(LinkedList* list) {
    if (list->head == NULL) return;

    Node *current = list->head, *smallest = list->head, *prev_smallest = NULL, *prev = NULL;

    while (current != NULL) {
        if (current->size < smallest->size) {
            smallest = current;
            prev_smallest = prev;
        }
        prev = current;
        current = current->next;
    }

    if (smallest == list->head) {
        list->head = list->head->next;
    } else if (prev_smallest != NULL) {
        prev_smallest->next = smallest->next;
    }
    free(smallest);
}

// Backup files to USB, optimizing for a maximum size of 32GB
void backup_files_to_usb(LinkedList* list) {
    long long max_usb_size = 32LL * 1024 * 1024 * 1024; // 32GB
    long long current_size = calculate_total_size(list);

    while (current_size > max_usb_size) {
        remove_smallest_file(list);
        current_size = calculate_total_size(list);
    }
}

// Print the list of files (size in MB)
void print_files(LinkedList* list) {
    Node* current = list->head;
    printf("Newest file on top of the list!!!\n");
    printf("File name |  Size(MB) |Date(DD/MM/YYYY)|\n");
    while (current != NULL) {

        printf("%10s|%8.2f MB|%16s|\n", current->file_name, 1.0 * current->size / (1024 * 1024), current->date);
        current = current->next;
    }
}

int main() {
    LinkedList folder;
    initialize_list(&folder);

    // Add files to the list
    insert_file_sorted(&folder, "file1.txt", 5000000000, "15/06/2023");
    insert_file_sorted(&folder, "file2.txt", 1200000000, "18/02/2023"); 
    insert_file_sorted(&folder, "file3.txt", 200000000, "18/06/2023");  
    insert_file_sorted(&folder, "file4.txt", 28000000000, "11/11/2023"); 
    insert_file_sorted(&folder, "file5.txt", 1000000000, "12/04/2023"); 

    // Print list of files before backup
    printf("List of files on D:/Documents\n");
    print_files(&folder);
    printf("Total size: %.2f GB\n\n", calculate_total_size(&folder) / (1024.0 * 1024.0 * 1024.0));

    //Copy and paste files to D:/Documents
    printf("Copy and paste files 'file6.txt' and 'file10.txt' to D:/Documents\n");
    insert_file_sorted(&folder, "file6.txt", 80000000, "01/12/2024");
    insert_file_sorted(&folder, "file10.txt", 1250000000, "15/06/2022");
    print_files(&folder);
    printf("Total size: %.2f GB\n\n", calculate_total_size(&folder) / (1024.0 * 1024.0 * 1024.0));
    // Backup files to USB
    backup_files_to_usb(&folder);

    // Print list of files after backup
    printf("List of files on USB (32GB):\n");
    print_files(&folder);
    printf("Total size: %.2f GB\n", calculate_total_size(&folder) / (1024.0 * 1024.0 * 1024.0));
    
    return 0;
}
