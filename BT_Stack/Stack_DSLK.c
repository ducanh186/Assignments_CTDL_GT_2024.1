#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node *next;
} Node;

typedef struct {
    Node *top;
} Stack;

void initialize(Stack *stack) { stack->top = NULL; }
int isEmpty(Stack *stack) { return stack->top == NULL; }

void push(Stack *stack, int value) {
    Node *newNode = (Node *)malloc(sizeof(Node));
    if (newNode == NULL) {
        printf("Khong the cap phat bo nho!\n");
        return;
    }
    newNode->data = value;
    newNode->next = stack->top;
    stack->top = newNode;
}

int pop(Stack *stack) {
    if (isEmpty(stack)) {
        printf("Stack rong!\n");
        return -1;
    } else {
        Node *temp = stack->top;
        int poppedValue = temp->data;
        stack->top = stack->top->next;
        free(temp);
        return poppedValue;
    }
}

int peek(Stack *stack) {
    if (isEmpty(stack)) {
        printf("Stack rong!\n");
        return -1;
    } else {
        return stack->top->data;
    }
}

void printStack(Stack *stack) {
    if (isEmpty(stack)) {
        printf("Stack rong!\n");
    } else {
        Node *current = stack->top;
        printf("Cac phan tu trong stack: ");
        while (current != NULL) {
            printf("%d ", current->data);
            current = current->next;
        }
        printf("\n");
    }
}

int main() {
    Stack stack;
    initialize(&stack);

    push(&stack, 10);
    push(&stack, 20);
    push(&stack, 30);
    push(&stack, 40);
    push(&stack, 5);

    printf("Phan tu tren dinh: %d\n", peek(&stack));

    printStack(&stack);

    printf("Lay phan tu ra khoi stack: %d\n", pop(&stack));

    printStack(&stack);

    return 0;
}
