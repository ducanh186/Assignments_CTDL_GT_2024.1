#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

// Cấu trúc của một node trong cây biểu thức
typedef struct Node {
    char data;  // Lưu toán tử hoặc toán hạng
    struct Node* left;
    struct Node* right;
} Node;

// Hàm tạo một node mới
Node* createNode(char data) {
    Node* node = (Node*)malloc(sizeof(Node));
    node->data = data;
    node->left = NULL;
    node->right = NULL;
    return node;
}

// Stack để lưu các node cây
typedef struct Stack {
    Node* nodes[100];
    int top;
} Stack;

// Hàm khởi tạo stack
void initStack(Stack* stack) {
    stack->top = -1;
}

// Kiểm tra stack rỗng
int isEmpty(Stack* stack) {
    return stack->top == -1;
}

// Thêm phần tử vào stack
void push(Stack* stack, Node* node) {
    stack->nodes[++(stack->top)] = node;
}

// Lấy phần tử ra khỏi stack
Node* pop(Stack* stack) {
    return stack->nodes[(stack->top)--];
}

// Kiểm tra xem ký tự có phải là toán tử không
int isOperator(char c) {
    return c == '+' || c == '-' || c == '*' || c == '/' || c == '^';
}

// Hàm dựng cây biểu thức từ biểu thức hậu tố
Node* buildExpressionTreeFromPostfix(char* expression) {
    Stack stack;
    initStack(&stack);

    for (int i = 0; i < strlen(expression); i++) {
        char token = expression[i];

        if (isspace(token)) continue; // Bỏ qua khoảng trắng

        if (isdigit(token) || isalpha(token)) {
            // Nếu là toán hạng, tạo node và đẩy vào stack
            push(&stack, createNode(token));
        } else if (isOperator(token)) {
            // Nếu là toán tử, lấy 2 toán hạng từ stack và tạo node mới
            Node* operatorNode = createNode(token);
            operatorNode->right = pop(&stack);
            operatorNode->left = pop(&stack);
            push(&stack, operatorNode);
        }
    }

    // Node cuối cùng là gốc của cây
    return pop(&stack);
}

// Hàm duyệt cây theo thứ tự trung tố
void inorderTraversal(Node* root) {
    if (root) {
        inorderTraversal(root->left);
        printf("%c ", root->data);
        inorderTraversal(root->right);
    }
}

// Hàm đọc biểu thức hậu tố từ đầu vào và loại bỏ khoảng trắng
void readPostfixExpression(char* expression) {
    printf("Nhap bieu thuc hau to: ");
    fgets(expression, 100, stdin);
    expression[strcspn(expression, "\n")] = '\0'; // Loại bỏ ký tự xuống dòng

    // Loại bỏ khoảng trắng thừa
    char cleanedExpression[100];
    int j = 0;
    for (int i = 0; expression[i] != '\0'; i++) {
        if (!isspace(expression[i])) {
            cleanedExpression[j++] = expression[i];
        }
    }
    cleanedExpression[j] = '\0';
    strcpy(expression, cleanedExpression);
}

int main() {
    char expression[100];

    // Nhập biểu thức hậu tố từ người dùng
    readPostfixExpression(expression);

    // Dựng cây biểu thức từ hậu tố
    Node* root = buildExpressionTreeFromPostfix(expression);

    // Duyệt cây theo thứ tự trung tố để kiểm tra
    printf("Bieu thuc trung to: ");
    inorderTraversal(root);
    printf("\n");

    return 0;
}
