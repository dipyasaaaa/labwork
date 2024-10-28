#include <stdio.h>
#include <stdlib.h>

#define MAX 100

int adjMatrix[MAX][MAX];
int visited[MAX];

// Function to initialize the adjacency matrix with 0s
void initializeMatrix(int vertices) {
    for (int i = 0; i < vertices; i++) {
        for (int j = 0; j < vertices; j++) {
            adjMatrix[i][j] = 0;
        }
    }
}

// Function to reset the visited array
void resetVisited(int vertices) {
    for (int i = 0; i < vertices; i++) {
        visited[i] = 0;
    }
}

// Function to add an edge to the adjacency matrix
void addEdge(int u, int v) {
    adjMatrix[u][v] = 1;
    adjMatrix[v][u] = 1;  // For undirected graph
    printf("Edge added between %d and %d\n", u, v);
}

// Function to display the adjacency matrix
void displayMatrix(int vertices) {
    printf("Adjacency Matrix:\n");
    for (int i = 0; i < vertices; i++) {
        for (int j = 0; j < vertices; j++) {
            printf("%d ", adjMatrix[i][j]);
        }
        printf("\n");
    }
}

// Function to perform Breadth-First Search (BFS)
void BFS(int start, int vertices) {
    int queue[MAX], front = 0, rear = 0;
    resetVisited(vertices);
    
    queue[rear++] = start;
    visited[start] = 1;
    
    printf("BFS Traversal starting from vertex %d: ", start);
    while (front < rear) {
        int current = queue[front++];
        printf("%d ", current);
        
        for (int i = 0; i < vertices; i++) {
            if (adjMatrix[current][i] == 1 && !visited[i]) {
                queue[rear++] = i;
                visited[i] = 1;
            }
        }
    }
    printf("\n");
}

// Display the menu options
void displayMenu() {
    printf("\n--- Graph Operations Menu ---\n");
    printf("1. Add Edge\n");
    printf("2. Display Adjacency Matrix\n");
    printf("3. BFS Traversal\n");
    printf("4. Exit\n");
    printf("Choose an option: ");
}

int main() {
    int vertices, choice, u, v, start;
    
    printf("Enter the number of vertices: ");
    scanf("%d", &vertices);
    
    initializeMatrix(vertices);
    
    while (1) {
        displayMenu();
        scanf("%d", &choice);
        
        switch (choice) {
            case 1:
                printf("Enter edge (u v): ");
                scanf("%d %d", &u, &v);
                if (u < vertices && v < vertices) {
                    addEdge(u, v);
                } else {
                    printf("Invalid vertices. Please try again.\n");
                }
                break;
                
            case 2:
                displayMatrix(vertices);
                break;
                
            case 3:
                printf("Enter starting vertex for BFS: ");
                scanf("%d", &start);
                if (start < vertices) {
                    BFS(start, vertices);
                } else {
                    printf("Invalid starting vertex. Please try again.\n");
                }
                break;
                
            case 4:
                printf("Exiting...\n");
                exit(0);
                break;
                
            default:
                printf("Invalid option. Please choose again.\n");
        }
    }
    
    return 0;
}
