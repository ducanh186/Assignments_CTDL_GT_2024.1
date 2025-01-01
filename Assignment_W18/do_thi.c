#include <stdio.h>
#include <stdlib.h>

#define MAX 100

int graph[MAX][MAX]; // Ma trận kề
int visited[MAX];    // Mảng đánh dấu đã thăm
int n;               // Số lượng đỉnh

// Hàm nhập đồ thị dưới dạng ma trận kề
void inputGraph() {
    int edges = 7; // Số đỉnh
int connections = 12; // Tổng số liên kết (theo ma trận kề)

int graph[7][7] = {
    {0, 1, 0, 1, 1, 1, 1}, // a
    {0, 0, 1, 1, 0, 1, 0}, // b
    {0, 1, 0, 1, 0, 1, 1}, // c
    {1, 0, 1, 0, 0, 1, 1}, // d
    {0, 1, 0, 1, 0, 1, 1}, // e
    {1, 1, 1, 0, 1, 0, 1}, // g
    {0, 0, 0, 0, 1, 0, 0}  // h
};
}

// Hàm duyệt DFS
void DFS(int v) {
    int i;
    printf("%d ", v);
    visited[v] = 1;

    for (i = 0; i < n; i++) {
        if (graph[v][i] == 1 && !visited[i]) {
            DFS(i);
        }
    }
}

// Hàm duyệt BFS
void BFS(int start) {
    int queue[MAX], front = 0, rear = 0;
    int i, current;

    queue[rear++] = start;
    visited[start] = 1;

    while (front < rear) {
        current = queue[front++];
        printf("%d ", current);

        for (i = 0; i < n; i++) {
            if (graph[current][i] == 1 && !visited[i]) {
                queue[rear++] = i;
                visited[i] = 1;
            }
        }
    }
}

// Hàm reset mảng visited
void resetVisited() {
    for (int i = 0; i < n; i++) {
        visited[i] = 0;
    }
}

int main() {
    int start;

    inputGraph();

    printf("\nNhập đỉnh bắt đầu duyệt: ");
    scanf("%d", &start);

    printf("\nDuyệt đồ thị theo DFS: ");
    resetVisited();
    DFS(start);

    printf("\nDuyệt đồ thị theo BFS: ");
    resetVisited();
    BFS(start);

    return 0;
}
