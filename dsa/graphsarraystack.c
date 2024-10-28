#include <stdio.h>
#include <stdlib.h>

#define MAX 100

// Stack Node for storing adjacency list items
struct StackNode {
    int vertex;
    struct StackNode* next;
};

// Array of stack heads (each vertex has a stack of neighbors)
struct StackNode* adjList[MAX];
int visited[MAX];

// Function to create a new stack node
struct StackNode* createNode(int v) {
    struct StackNode* newNode = (struct StackNode*)malloc(sizeof(struct StackNode));
    newNode->vertex = v;
    newNode->next = NULL;
    return newNode;
}

// Initialize each vertex's stack in the adjacency list
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

// Function to push a vertex to a given vertex's adjacency stack
void push(int u, int v) {
    struct StackNode* newNode = createNode(v);
    newNode->next = adjList[u];
    adjList[u] = newNode;
}

// Function to add an edge (undirected graph)
void addEdge(int u, int v) {
    push(u, v); // Add v to u's list
    push(v, u); // Add u to v's list
    printf("Edge added between %d and %d\n", u, v);
}

// Function to display the adjacency list using stacks
void displayList(int vertices) {
    printf("Adjacency List (Array of Stacks):\n");
    for (int i = 0; i < vertices; i++) {
        struct StackNode* temp = adjList[i];
        printf("%d: ", i);
        while (temp) {
            printf("%d -> ", temp->vertex);
            temp = temp->next;
        }
        printf("NULL\n");
    }
}

// Stack functions for DFS traversal
struct StackNode* DFSstack = NULL;  // Stack for DFS traversal

void DFS_push(int vertex) {
    struct StackNode* newNode = createNode(vertex);
    newNode->next = DFSstack;
    DFSstack = newNode;
}

int DFS_pop() {
    if (DFSstack == NULL) return -1;
    struct StackNode* temp = DFSstack;
    int vertex = temp->vertex;
    DFSstack = DFSstack->next;
    free(temp);
    return vertex;
}

// DFS Traversal using stack-based adjacency list
void DFS(int start, int vertices) {
    resetVisited(vertices);   // Reset visited nodes
    DFS_push(start);          // Start DFS from the starting vertex

    printf("DFS Traversal starting from vertex %d: ", start);
    while (DFSstack) {
        int current = DFS_pop();
        if (!visited[current]) {
            printf("%d ", current);
            visited[current] = 1;

            struct StackNode* temp = adjList[current];
            while (temp) {
                if (!visited[temp->vertex]) {
                    DFS_push(temp->vertex); // Push unvisited neighbors
                }
                temp = temp->next;
            }
        }
    }
    printf("\n");
}

// Display the menu options
void displayMenu() {
    printf("\n--- Graph Operations Menu ---\n");
    printf("1. Add Edge\n");
    printf("2. Display Adjacency List\n");
    printf("3. DFS Traversal\n");
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
                printf("Enter starting vertex for DFS: ");
                scanf("%d", &start);
                if (start < vertices) {
                    DFS(start, vertices);
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
