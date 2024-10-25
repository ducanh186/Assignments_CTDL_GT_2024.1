#include <stdio.h>
#include <stdlib.h>

// Cấu trúc Ngày
struct Ngay {
    int ngay, thang, nam;
};

// Cấu trúc SinhVien
struct SinhVien {
    char maSV[8];
    char hoTen[50];
    int gioiTinh;  // 0: Nữ, 1: Nam
    struct Ngay ngaySinh;
    char diaChi[100];
    char lop[12];
    char khoa[7];
};

// Cấu trúc Node cho danh sách liên kết
struct Node {
    struct SinhVien data;
    struct Node* link;
};

// Cấu trúc List quản lý đầu và cuối danh sách
struct List {
    struct Node* first;
    struct Node* last;
};

// Khởi tạo danh sách
void initList(struct List* list) {
    list->first = list->last = NULL;
}

// Sao chép chuỗi thủ công
void copyString(char* dest, const char* src) {
    while (*src) {
        *dest = *src;
        dest++;
        src++;
    }
    *dest = '\0';
}

// So sánh chuỗi thủ công
int compareString(const char* str1, const char* str2) {
    while (*str1 && (*str1 == *str2)) {
        str1++;
        str2++;
    }
    return *str1 - *str2;
}

// Tạo Node mới
struct Node* createNode(struct SinhVien sv) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = sv;
    newNode->link = NULL;
    return newNode;
}

// Thêm sinh viên vào danh sách theo thứ tự mã
void insertSorted(struct List* list, struct SinhVien sv) {
    struct Node* newNode = createNode(sv);
    if (list->first == NULL || compareString(sv.maSV, list->first->data.maSV) < 0) {
        newNode->link = list->first;
        list->first = newNode;
    } else {
        struct Node* temp = list->first;
        while (temp->link != NULL && compareString(temp->link->data.maSV, sv.maSV) < 0) {
            temp = temp->link;
        }
        newNode->link = temp->link;
        temp->link = newNode;
    }
}

// In danh sách sinh viên
void printList(struct List list) {
    struct Node* temp = list.first;
    while (temp != NULL) {
        printf("MaSV: %s, HoTen: %s, Lop: %s\n", 
               temp->data.maSV, temp->data.hoTen, temp->data.lop);
        temp = temp->link;
    }
}

// Tìm sinh viên có cùng ngày sinh
void findSameBirthday(struct List list, struct Ngay ngaySinh) {
    struct Node* temp = list.first;
    int found = 0;
    while (temp != NULL) {
        if (temp->data.ngaySinh.ngay == ngaySinh.ngay &&
            temp->data.ngaySinh.thang == ngaySinh.thang &&
            temp->data.ngaySinh.nam == ngaySinh.nam) {
            printf("MaSV: %s, HoTen: %s\n", 
                   temp->data.maSV, temp->data.hoTen);
            found = 1;
        }
        temp = temp->link;
    }
    if (!found) {
        printf("Không tìm thấy sinh viên cùng ngày sinh\n");
    }
}

// Loại bỏ sinh viên có cùng ngày sinh
void removeSameBirthday(struct List* list, struct Ngay ngaySinh) {
    struct Node *temp = list->first, *prev = NULL;
    while (temp != NULL) {
        if (temp->data.ngaySinh.ngay == ngaySinh.ngay &&
            temp->data.ngaySinh.thang == ngaySinh.thang &&
            temp->data.ngaySinh.nam == ngaySinh.nam) {
            if (prev == NULL) {
                list->first = temp->link;
            } else {
                prev->link = temp->link;
            }
            struct Node* toDelete = temp;
            temp = temp->link;
            free(toDelete);
        } else {
            prev = temp;
            temp = temp->link;
        }
    }
}
void addSinhVien(struct List* list) {
    struct SinhVien sv;

    // Nhập thông tin sinh viên mới
    printf("Nhap ma sinh vien: ");
    scanf("%7s", sv.maSV);  // Giới hạn 7 ký tự + 1 ký tự '\0'
    
    printf("Nhap ho ten: ");
    getchar();  // Loại bỏ ký tự '\n' còn lại từ lần nhập trước
    fgets(sv.hoTen, 50, stdin);  // Đọc chuỗi, cho phép khoảng trắng
    sv.hoTen[strcspn(sv.hoTen, "\n")] = '\0';  // Xóa ký tự '\n' nếu có

    printf("Nhap gioi tinh (0: Nu, 1: Nam): ");
    scanf("%d", &sv.gioiTinh);

    printf("Nhap ngay sinh (dd mm yyyy): ");
    scanf("%d %d %d", &sv.ngaySinh.ngay, &sv.ngaySinh.thang, &sv.ngaySinh.nam);

    printf("Nhap dia chi: ");
    getchar();  // Loại bỏ ký tự '\n'
    fgets(sv.diaChi, 100, stdin);
    sv.diaChi[strcspn(sv.diaChi, "\n")] = '\0';

    printf("Nhap lop: ");
    scanf("%11s", sv.lop);

    printf("Nhap khoa: ");
    scanf("%6s", sv.khoa);

    // Thêm sinh viên mới vào danh sách đã sắp xếp
    insertSorted(list, sv);

    printf("Da them sinh vien thanh cong!\n");
}

int main() {
    struct List list;
    initList(&list);

    // Thêm sinh viên vào danh sách
    struct SinhVien sv1 = {"001", "Nguyen Van Long", 1, {10, 1,2004}, "Hanoi", "ETE9", "K67"};
    struct SinhVien sv2 = {"002", "Tran Thi Thuy", 0, {20, 6, 2004}, "Hai Phong", "ETE9", "K67"};
    struct SinhVien sv3 = {"003", "Le Van Hanh", 1, {10, 12,2004}, "Da Nang", "ETE9", "K67"};

    insertSorted(&list, sv1);
    insertSorted(&list, sv2);
    insertSorted(&list, sv3);

    printf("Danh sách sinh viên:\n");
    printList(list);
     
     printf("\nNhap sinh vien moi:\n");
    addSinhVien(&list);

    // In lại danh sách sau khi thêm sinh viên mới
    printf("\nDanh sach sau khi them sinh vien moi:\n");
    printList(list);
    // Tìm sinh viên có cùng ngày sinh
    printf("\nTìm sinh viên có cùng ngày sinh 10/01/2004:\n");
    findSameBirthday(list, (struct Ngay){10, 01,2004});

    // Loại bỏ sinh viên có cùng ngày sinh
    printf("\nLoại bỏ sinh viên có cùng ngày sinh 10/01/2004:\n");
    removeSameBirthday(&list, (struct Ngay){10, 01,2004});
    printList(list);

    return 0;
}
