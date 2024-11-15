#include <stdio.h>
#include <stdlib.h>


typedef struct {
    int items[50]; // stack co toi da 50 stack
    int top;
} Stack;

void initialize(Stack *stack) { stack->top = -1; }
// Theo phan tu moi vao stack
void push(Stack *stack, int value) {
    if (stack->top == 50 - 1) {// check stack xem da day chua
        printf("Stack day!\n");
    } else {
        stack->items[++stack->top] = value;
    }
}
int pop(Stack *stack) {
    if (stack->top == -1) {
        printf("Stack rong!\n");
        return -1;
    } else {
        return stack->items[stack->top--];
    }
}

int peek(Stack *stack) {
    if (stack->top == -1) {
        printf("Stack rong!\n");
        return -1;
    } else {
        return stack->items[stack->top];
    }
}

// Ham in cac phan tu trong stack
void printStack(Stack *stack) {
    if (stack->top == -1) {
        printf("Stack rong!\n");
    } else {
        printf("Cac phan tu trong stack: ");
        for (int i = stack->top; i >= 0; i--) {
            printf("%d ", stack->items[i]);
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
