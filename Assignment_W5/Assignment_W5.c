#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>

#define MAX 100 // Giới hạn mảng tối đa
// Bài 1:  Nhập vào n đối tượng có màu đỏ (red), trắng (white) và xanh (blue), sắp xếp theo trật tự như sau: các đối tượng cùng mầu nằm kế tiếp nhau và theo thứ tự đỏ, trắng, xanh.
// Input {xanh, đỏ, xanh, đỏ, đỏ, trắng, đỏ, xanh, trắng}
// Output {đỏ, đỏ, đỏ, đỏ, trắng, trắng, xanh, xanh, xanh}
// Gợi ý:
// Có thể mã hóa các mầu bằng các số nguyên 0, 1, 2 để biểu diễn lần lượt mầu đỏ, trắng và xanh tương ứng.
// Chú ý: Không sử dụng các thư viện hàm sắp xếp có sẵn để giải quyết bài toán trên khi cài đặt chương trình

//Hàm đổi vị trí 2 phần tử cho nhau sử dụng con trỏ
void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}
 // Hàm in mảng
void printArray(int arr[], int n) {
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}
void sorting_function(int arr[],int n){
    int low=0, mid=0,high=n-1;
    while (mid<=high)
    {
        if(arr[mid]==0){
            swap(&arr[mid],&arr[low]);
            low++;
            mid++;
        }
        //else if tránh sự kiểm tra lại??
        else if(arr[mid]==1){
            mid++;
        }
        else { 
            swap(&arr[mid],&arr[high]);
            high--;
        }
    }
    

}

// Bài 2: Thiết kế giải thuật và cài đặt để tạo ra một mảng số nửa nguyên tố (Blum) nhỏ hơn một số N cho trước và thực hiện hai yêu cầu sau
// - Tìm ra tất cả các cặp số Blum có tổng cũng là một số Blum nhỏ hơn N
// - Kiểm tra xem một số Blum M có tồn tại trong dãy số Blum được tạo ra hay không.

// Hàm kiểm tra số nguyên tố
bool isPrime(int n) {
    if (n <= 1) return false;
    for (int i = 2; i <= sqrt(n); i++) {
        if (n % i == 0) return false;
    }
    return true;
}

// Hàm tạo mảng số Blum
int* generateBlumNumbers(int N, int* size) {
    int* primes = malloc(MAX * sizeof(int)); // Mảng lưu số nguyên tố
    *size = 0;

    // Tìm tất cả số nguyên tố nhỏ hơn sqrt(N)
    for (int i = 2; i < sqrt(N); i++) {
        if (isPrime(i)) {
            primes[(*size)++] = i;
        }
    }

    int* blumNumbers = malloc(MAX * sizeof(int));//Mảng lưu số Blum
    int blumIndex = 0;

    // Tạo số Blum từ các cặp số nguyên tố
    for (int i = 0; i < *size; i++) {
        for (int j = i + 1; j < *size; j++) {
            int blumNumber = primes[i] * primes[j];
            if (blumNumber < N) {
                blumNumbers[blumIndex++] = blumNumber;
            }
        }
    }

    free(primes);
    *size = blumIndex; // Cập nhật kích thước mảng số Blum
    return blumNumbers;
}

// Hàm tìm cặp số Blum có tổng cũng là số Blum
void findBlumPairs(int* blumNumbers, int size) {
    printf("The pairs of Blum numbers whose sum is also a Blum number:\n");
    for (int i = 0; i < size; i++) {
        for (int j = i; j < size; j++) {
            int sum = blumNumbers[i] + blumNumbers[j];
            for (int k = 0; k < size; k++) {
                if (blumNumbers[k] == sum) {
                    printf("(%d, %d) -> Sum = %d\n", blumNumbers[i], blumNumbers[j], sum);
                    break;
                }
            }
        }
    }
}

// Hàm kiểm tra sự tồn tại của số Blum
bool checkBlumExist(int* blumNumbers, int size, int M) {
    for (int i = 0; i < size; i++) {
        if (blumNumbers[i] == M) {
            return true;
        }
    }
    return false;
}
int main() {
    //Bai 1
    int arr[] = {1,1,2,0,1,1,2,2,0,2, 0, 2, 0, 0, 1, 0, 2, 1};
    int n = sizeof(arr) / sizeof(arr[0]);
    printf("In_put_array:\n");
    printArray(arr, n);
    sorting_function(arr, n);
    printf("Array_ after_sorting:\n");
    printArray(arr, n);
    //Bai2
    int N;
    printf("Enter N: ");
    scanf("%d", &N);

    int size;
    int* blumNumbers = generateBlumNumbers(N, &size);
    printf("All the Blum Numbers are smaller than %d:\n", N);
    for (int i = 0; i < size; i++) {
        printf("%d ", blumNumbers[i]);
    }
    printf("\n");

    // Tìm các cặp số Blum
    findBlumPairs(blumNumbers, size);

    // Kiểm tra số Blum M
    int M;
        
     while(1)
     {  printf("Enter Blum number M (or press 0 to exit): "); 
        scanf("%d", &M);
        if (M == 0) {
            printf("Exiting the program.\n");
            break; // Thoát khỏi vòng lặp
        }
        // Kiểm tra số Blum M
        if (checkBlumExist(blumNumbers, size, M)) {
            printf("The number %d exists in the Blum array.\n", M); 
        } else {
            printf("The number %d does not exist in the Blum array.\n", M); 
        }
    }

    free(blumNumbers); // Giải phóng bộ nhớ
    return 0;
}
