#include <stdio.h>
#include <stdlib.h>

struct Node {
    int coefficient; // He so cua hang tu
    int exponent;    // Bac cua hang tu
    struct Node* next; 
};

// Ham tao node moi
struct Node* createNode(int coefficient, int exponent) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->coefficient = coefficient;
    newNode->exponent = exponent;
    newNode->next = NULL;
    return newNode;
}

// Ham them node vao dau danh sach
void insertAtHead(struct Node** poly, int coefficient, int exponent) {
    struct Node* newNode = createNode(coefficient, exponent);
    newNode->next = *poly;
    *poly = newNode;
}

// Ham them node vao danh sach chi dinh boi con tro previous
void insertAfter(struct Node* previous, int coefficient, int exponent) {
    if (previous == NULL) return;
    struct Node* newNode = createNode(coefficient, exponent);
    newNode->next = previous->next;
    previous->next = newNode;
}

// Ham xoa node tai vi tri chi dinh boi con tro current
void deleteNode(struct Node** poly, struct Node* current) {
    if (current == NULL) return;

    if (*poly == current) {
        *poly = current->next; // Xoa node dau
    } else {
        struct Node* prev = *poly;
        while (prev->next != current) {
            prev = prev->next;
        }
        prev->next = current->next; // Bo qua node hien tai
    }
    free(current);
}

// Ham them node vao danh sach da thuc theo thu tu bac giam dan
void insertTerm(struct Node** poly, int coefficient, int exponent) {
    // Neu he so la 0, khong them node vao danh sach
    if (coefficient == 0) return;

    // Truong hop danh sach rong hoac can chen o dau
    if (*poly == NULL || (*poly)->exponent < exponent) {
        insertAtHead(poly, coefficient, exponent);
        return;
    }

    struct Node* current = *poly;
    struct Node* previous = NULL;

    // Tim vi tri chen node moi
    while (current != NULL && current->exponent > exponent) {
        previous = current;
        current = current->next;
    }

    // Neu da co hang tu voi cung bac, cong he so lai
    if (current != NULL && current->exponent == exponent) {
        current->coefficient += coefficient;

        // Neu he so tro thanh 0, xoa hang tu nay
        if (current->coefficient == 0) {
            deleteNode(poly, current);
        }
        return;
    }

    // Chen node moi vao danh sach
    if (previous == NULL) {
        insertAtHead(poly, coefficient, exponent); // Neu them o dau
    } else {
        // Chen vao giua hoac cuoi danh sach
        insertAfter(previous, coefficient, exponent);
    }
}

// Ham nhap da thuc tu nguoi dung
void inputPolynomial(struct Node** poly) {
    int coefficient, exponent;
    printf("Nhap cac he so va bac cua tung hang tu (nhap he so 0 de ket thuc):\n");
    while (1) {
        printf("Nhap he so: ");
        scanf("%d", &coefficient);
        if (coefficient == 0) break; // Ket thuc khi he so la 0
        printf("Nhap bac cua x: ");
        scanf("%d", &exponent);
        insertTerm(poly, coefficient, exponent);
    }
}

// Ham in da thuc
void printPolynomial(struct Node* poly) {
    struct Node* current = poly;
    if (current == NULL) {
        printf("0\n");
        return;
    }
    while (current != NULL) {
        if (current->coefficient > 0 && current != poly) {
            printf("+");
        }
        printf("%dx^%d ", current->coefficient, current->exponent);
        current = current->next;
    }
    printf("\n");
}

// Ham cong hai da thuc
struct Node* addPolynomials(struct Node* poly1, struct Node* poly2) {
    struct Node* result = NULL;

    // Duyet ca hai da thuc
    while (poly1 != NULL || poly2 != NULL) {
        int coefficient = 0;
        int exponent;

        if (poly1 != NULL && (poly2 == NULL || poly1->exponent > poly2->exponent)) {
            coefficient = poly1->coefficient;
            exponent = poly1->exponent;
            poly1 = poly1->next; // Di chuyen den hang tu tiep theo
        } else if (poly2 != NULL && (poly1 == NULL || poly2->exponent > poly1->exponent)) {
            coefficient = poly2->coefficient;
            exponent = poly2->exponent;
            poly2 = poly2->next; // Di chuyen den hang tu tiep theo
        } else {
            // Cong he so cua cac hang tu cung bac
            coefficient = poly1->coefficient + poly2->coefficient;
            exponent = poly1->exponent;
            poly1 = poly1->next; // Di chuyen den hang tu tiep theo
            poly2 = poly2->next; // Di chuyen den hang tu tiep theo
        }

        // Them vao ket qua
        insertTerm(&result, coefficient, exponent);
    }

    return result;
}

// Ham chinh
int main() {
    struct Node* poly1 = NULL;
    struct Node* poly2 = NULL;

    printf("Nhap da thuc f(x):\n");
    inputPolynomial(&poly1);
    
    printf("Nhap da thuc g(x):\n");
    inputPolynomial(&poly2);

    // In ra cac da thuc
    printf("f(x) = ");
    printPolynomial(poly1);
    printf("g(x) = ");
    printPolynomial(poly2);
    
    // Cong hai da thuc
    struct Node* polySum = addPolynomials(poly1, poly2);
    printf("h(x) = f(x) + g(x) = ");
    printPolynomial(polySum);
    
    return 0;
}
