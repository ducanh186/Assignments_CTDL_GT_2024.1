#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Cau truc du lieu cho moi thanh go
typedef struct Wood {
    char type[20];
    int size;
    int age;
    struct Wood *next;
} Wood;

// Cau truc stack
typedef struct {
    Wood *top;
} Stack;

// Khoi tao stack
void initialize(Stack *stack) { stack->top = NULL; }

// Kiem tra xem stack co rong khong
int isEmpty(Stack *stack) { return stack->top == NULL; }

// Dua mot thanh go vao stack
void push(Stack *stack, char *type, int size, int age) {
    Wood *newWood = (Wood *)malloc(sizeof(Wood));
    if (newWood == NULL) {
        printf("Khong the cap phat bo nho!\n");
        return;
    }
    strcpy(newWood->type, type);
    newWood->size = size;
    newWood->age = age;
    newWood->next = stack->top;
    stack->top = newWood;
}

// Lay mot thanh go ra khoi stack
Wood* pop(Stack *stack) {
    if (isEmpty(stack)) {
        printf("Kho go rong!\n");
        return NULL;
    } else {
        Wood *temp = stack->top;
        stack->top = stack->top->next;
        return temp;
    }
}

// Dem so luong thanh go co cung tuoi go
int countByAge(Stack *stack, int age) {
    int count = 0;
    Wood *current = stack->top;
    while (current != NULL) {
        if (current->age == age) {
            count++;
        }
        current = current->next;
    }
    return count;
}

// In tat ca cac thanh go trong kho
void printStack(Stack *stack) {
    if (isEmpty(stack)) {
        printf("Kho go rong!\n");
    } else {
        Wood *current = stack->top;
        printf("Cac thanh go trong kho:\n");
        while (current != NULL) {
            printf("Loai: %s, Kich thuoc: %d, Tuoi: %d\n", current->type, current->size, current->age);
            current = current->next;
        }
    }
}

int main() {
    Stack stack;
    initialize(&stack);

    // Dua go vao kho
    push(&stack, "Cam xe", 20, 10);
    push(&stack, "Tram", 15, 5);
    push(&stack, "Teak", 25, 10);
    push(&stack, "Lim", 30, 15);
    push(&stack, "Teak", 20, 10);

    // In tat ca cac thanh go trong kho
    printStack(&stack);

    // Dem so luong thanh go co tuoi go la 10
    int ageToCount = 10;
    int count = countByAge(&stack, ageToCount);
    printf("So luong thanh go co tuoi %d: %d\n", ageToCount, count);

    return 0;
}
