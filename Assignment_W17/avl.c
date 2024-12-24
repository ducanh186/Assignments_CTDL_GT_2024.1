#include <stdio.h>
#include <stdlib.h>

// Cấu trúc của một node trong cây AVL
typedef struct AVLNode {
    int key;
    struct AVLNode *left;
    struct AVLNode *right;
    int height;
} AVLNode;

// Hàm tạo một node mới
AVLNode* createNode(int key) {
    AVLNode* node = (AVLNode*)malloc(sizeof(AVLNode));
    node->key = key;
    node->left = node->right = NULL;
    node->height = 1;
    return node;
}

// Hàm lấy chiều cao của một node
int height(AVLNode *N) {
    if (N == NULL)
        return 0;
    return N->height;
}

// Hàm lấy giá trị lớn hơn
int max(int a, int b) {
    return (a > b) ? a : b;
}

// Hàm xoay phải
AVLNode *rightRotate(AVLNode *y) {
    AVLNode *x = y->left;
    AVLNode *T2 = x->right;

    // Thực hiện xoay
    x->right = y;
    y->left = T2;

    // Cập nhật chiều cao
    y->height = max(height(y->left), height(y->right)) + 1;
    x->height = max(height(x->left), height(x->right)) + 1;

    // Trả về node mới
    return x;
}

// Hàm xoay trái
AVLNode *leftRotate(AVLNode *x) {
    AVLNode *y = x->right;
    AVLNode *T2 = y->left;

    // Thực hiện xoay
    y->left = x;
    x->right = T2;

    // Cập nhật chiều cao
    x->height = max(height(x->left), height(x->right)) + 1;
    y->height = max(height(y->left), height(y->right)) + 1;

    // Trả về node mới
    return y;
}

// Hàm lấy hệ số cân bằng của một node
int getBalance(AVLNode *N) {
    if (N == NULL)
        return 0;
    return height(N->left) - height(N->right);
}

// Hàm thêm một node mới vào cây AVL
AVLNode* insertNode(AVLNode* node, int key) {
    // 1. Thực hiện chèn bình thường
    if (node == NULL)
        return createNode(key);

    if (key < node->key)
        node->left = insertNode(node->left, key);
    else if (key > node->key)
        node->right = insertNode(node->right, key);
    else // Trùng khóa không được phép trong cây AVL
        return node;

    // 2. Cập nhật chiều cao của node tổ tiên này
    node->height = 1 + max(height(node->left), height(node->right));

    // 3. Lấy hệ số cân bằng của node tổ tiên này để kiểm tra xem node này có mất cân bằng không
    int balance = getBalance(node);

    // Nếu node này mất cân bằng, có 4 trường hợp cần xử lý

    // Trường hợp Left Left
    if (balance > 1 && key < node->left->key)
        return rightRotate(node);

    // Trường hợp Right Right
    if (balance < -1 && key > node->right->key)
        return leftRotate(node);

    // Trường hợp Left Right
    if (balance > 1 && key > node->left->key) {
        node->left = leftRotate(node->left);
        return rightRotate(node);
    }

    // Trường hợp Right Left
    if (balance < -1 && key < node->right->key) {
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }

    // Trả về node (không thay đổi)
    return node;
}

// Hàm duyệt cây theo thứ tự trước
void preOrder(AVLNode *root) {
    if (root != NULL) {
        printf("%d ", root->key);
        preOrder(root->left);
        preOrder(root->right);
    }
}

// Hàm duyệt cây theo thứ tự giữa
void inOrder(AVLNode *root) {
    if (root != NULL) {
        inOrder(root->left);
        printf("%d ", root->key);
        inOrder(root->right);
    }
}

// Hàm duyệt cây theo thứ tự sau
void postOrder(AVLNode *root) {
    if (root != NULL) {
        postOrder(root->left);
        postOrder(root->right);
        printf("%d ", root->key);
    }
}

// Hàm chính để kiểm tra
int main() {
    AVLNode *root = NULL;

    // Mảng đầu vào
    int arr[] = {10, 20, 30, 40, 50, 25};
    int n = sizeof(arr) / sizeof(arr[0]);

    // Thêm từng phần tử vào cây AVL và in cây theo từng bước
    for (int i = 0; i < n; i++) {
        root = insertNode(root, arr[i]);
        printf("Cây AVL sau khi thêm %d:\n", arr[i]);
        printf("Duyệt cây theo thứ tự trước: ");
        preOrder(root);
        printf("\nDuyệt cây theo thứ tự giữa: ");
        inOrder(root);
        printf("\nDuyệt cây theo thứ tự sau: ");
        postOrder(root);
        printf("\n\n");
    }

    return 0;
}