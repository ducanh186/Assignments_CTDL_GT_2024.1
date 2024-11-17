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

// Insert a file into the list in ascending order by file size
void insert_file_sorted(LinkedList* list, char* file_name, long long size, char* date) {
    Node* new_node = (Node*)malloc(sizeof(Node));
    strcpy(new_node->file_name, file_name);
    new_node->size = size;
    strcpy(new_node->date, date);
    new_node->next = NULL;

    // Insert in increasing order of size, and if size is the same, keep the insertion order
    if (list->head == NULL || list->head->size > size) {
        new_node->next = list->head;
        list->head = new_node;
    } else {
        Node* current = list->head;
        while (current->next != NULL && current->next->size <= size) {
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

// Remove the smallest file by size, and if files are equal in size, remove the oldest one
void remove_smallest_file(LinkedList* list) {
    if (list->head == NULL) return;

    Node *current = list->head, *smallest = list->head, *prev_smallest = NULL, *prev = NULL;

    // Find smallest file by size, and if tied, find the oldest by date
    while (current != NULL) {
        if (current->size < smallest->size || 
           (current->size == smallest->size && compare_dates(current->date, smallest->date) < 0)) {
            smallest = current;
            prev_smallest = prev;
        }
        prev = current;
        current = current->next;
    }

    // Remove smallest node
    if (smallest == list->head) {
        list->head = list->head->next;
    } else if (prev_smallest != NULL) {
        prev_smallest->next = smallest->next;
    }
    free(smallest);
}

// Print the list of files (size in MB)
void print_files(LinkedList* list) {
    Node* current = list->head;
    printf("Files sorted by size in ascending order:\n");
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
    insert_file_sorted(&folder, "file4.txt", 20300000000, "11/11/2023"); 
    insert_file_sorted(&folder, "file5.txt", 1000000000, "12/04/2023"); 
    insert_file_sorted(&folder, "file6.txt", 200000000, "18/01/2023");  
    insert_file_sorted(&folder, "file7.txt", 1000000000, "12/03/2023");
    // Print list of files
    print_files(&folder);
    printf("Total size: %.2f GB\n\n", calculate_total_size(&folder) / (1024.0 * 1024.0 * 1024.0));

    // Remove smallest files until under 32GB
    long long max_usb_size = 26LL * 1024 * 1024 * 1024;
    while (calculate_total_size(&folder) > max_usb_size) {
        remove_smallest_file(&folder);
    }

    // Print list of files after cleanup
    printf("Files after removing the smallest:\n");
    print_files(&folder);
    printf("Total size: %.2f GB\n", calculate_total_size(&folder) / (1024.0 * 1024.0 * 1024.0));

    return 0;
}
