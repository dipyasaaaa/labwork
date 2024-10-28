#include <stdio.h>
#include <stdlib.h>

#define MAX 100

// Define a structure for the adjacency list node
struct Node {
    int vertex;
    struct Node* next;
};

// Array of adjacency lists
struct Node* adjList[MAX];
int visited[MAX];

// Function to create a new node
struct Node* createNode(int v) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->vertex = v;
    newNode->next = NULL;
    return newNode;
}

// Initialize the adjacency list
void initializeList(int vertices) {
    for (int i = 0; i < vertices; i++) {
        adjList[i] = NULL;
    }
}

// Function to reset visited array
void resetVisited(int vertices) {
    for (int i = 0; i < vertices; i++) {
        visited[i] = 0;
    }
}

// Function to add an edge
void addEdge(int u, int v) {
    // Add an edge from u to v
    struct Node* newNode = createNode(v);
    newNode->next = adjList[u];
    adjList[u] = newNode;

    // Add an edge from v to u (since the graph is undirected)
    newNode = createNode(u);
    newNode->next = adjList[v];
    adjList[v] = newNode;

    printf("Edge added between %d and %d\n", u, v);
}

// Function to display the adjacency list
void displayList(int vertices) {
    printf("Adjacency List:\n");
    for (int i = 0; i < vertices; i++) {
        struct Node* temp = adjList[i];
        printf("%d: ", i);
        while (temp) {
            printf("%d -> ", temp->vertex);
            temp = temp->next;
        }
        printf("NULL\n");
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
        
        struct Node* temp = adjList[current];
        while (temp) {
            int adjVertex = temp->vertex;
            if (!visited[adjVertex]) {
                queue[rear++] = adjVertex;
                visited[adjVertex] = 1;
            }
            temp = temp->next;
        }
    }
    printf("\n");
}

// Display the menu options
void displayMenu() {
    printf("\n--- Graph Operations Menu ---\n");
    printf("1. Add Edge\n");
    printf("2. Display Adjacency List\n");
    printf("3. BFS Traversal\n");
    printf("4. Exit\n");
    printf("Choose an option: ");
}

int main() {
    int vertices, choice, u, v, start;
    
    printf("Enter the number of vertices: ");
    scanf("%d", &vertices);
    
    initializeList(vertices);
    
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
                displayList(vertices);
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
