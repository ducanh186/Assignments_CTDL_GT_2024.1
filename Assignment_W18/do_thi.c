#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define SIZE 8

int adjacencyMatrix[SIZE][SIZE] = {0}; // Adjacency matrix
char nodes[SIZE] = {'a', 'b', 'c', 'd', 'e', 'g', 'h'}; // Graph vertices
bool visitedNodes[SIZE]; // Array to track visited nodes

// Get the index of a vertex
int findNodeIndex(char node) {
    for (int i = 0; i < SIZE; i++) {
        if (nodes[i] == node) return i;
    }
    return -1;
}

// Add an edge between two vertices
void connectNodes(char startNode, char endNode) {
    int startIdx = findNodeIndex(startNode);
    int endIdx = findNodeIndex(endNode);
    if (startIdx != -1 && endIdx != -1) {
        adjacencyMatrix[startIdx][endIdx] = 1;
        adjacencyMatrix[endIdx][startIdx] = 1; // Undirected graph
    }
}

// Initialize the graph with edges
void initializeGraph() {
    char edges[][2] = {
        {'a', 'b'}, {'a', 'c'}, {'a', 'e'}, {'a', 'g'},
        {'b', 'c'}, {'b', 'e'}, {'c', 'd'}, {'d', 'e'},
        {'d', 'g'}, {'e', 'h'}, {'g', 'h'}
    };

    int numEdges = sizeof(edges) / sizeof(edges[0]);
    for (int i = 0; i < numEdges; i++) {
        connectNodes(edges[i][0], edges[i][1]);
    }
}

// Perform BFS
void breadthFirstTraversal(char startNode) {
    int queue[SIZE], front = 0, rear = 0; // Queue
    for (int i = 0; i < SIZE; i++) visitedNodes[i] = false; // Reset visited nodes

    int startIdx = findNodeIndex(startNode);
    if (startIdx == -1) return;

    queue[rear++] = startIdx; // Add the start node to the queue
    visitedNodes[startIdx] = true;

    printf("BFS Traversal: ");
    while (front < rear) {
        int currentNode = queue[front++]; // Dequeue
        printf("%c ", nodes[currentNode]);

        // Traverse neighbors and add to queue if not visited
        for (int i = 0; i < SIZE; i++) {
            if (adjacencyMatrix[currentNode][i] == 1 && !visitedNodes[i]) {
                queue[rear++] = i;
                visitedNodes[i] = true;
            }
        }
    }
    printf("\n");
}

// Perform DFS
void depthFirstTraversal(char startNode) {
    int stack[SIZE], top = -1; // Stack
    for (int i = 0; i < SIZE; i++) visitedNodes[i] = false; // Reset visited nodes

    int startIdx = findNodeIndex(startNode);
    if (startIdx == -1) return;

    stack[++top] = startIdx; // Push the start node onto the stack

    printf("DFS Traversal: ");
    while (top >= 0) {
        int currentNode = stack[top--]; // Pop the stack
        if (!visitedNodes[currentNode]) {
            visitedNodes[currentNode] = true;
            printf("%c ", nodes[currentNode]);
        }

        // Push neighbors onto the stack (in reverse order to maintain expected output)
        for (int i = SIZE - 1; i >= 0; i--) {
            if (adjacencyMatrix[currentNode][i] == 1 && !visitedNodes[i]) {
                stack[++top] = i;
            }
        }
    }
    printf("\n");
}

int main() {
    initializeGraph(); // Set up the graph with all edges

    char start = 'a'; // Start traversal from vertex 'a'
    breadthFirstTraversal(start);
    depthFirstTraversal(start);

    return 0;
}
