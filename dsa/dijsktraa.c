#include <stdio.h>
#include <limits.h>
#include <stdbool.h>

#define MAX_V 10  // Maximum number of vertices (change as needed)

// Function to find the vertex with the minimum distance value
int minDistance(int dist[], bool sptSet[], int V) {
    int min = INT_MAX, min_index;
    
    for (int v = 0; v < V; v++)
        if (!sptSet[v] && dist[v] <= min) {
            min = dist[v];
            min_index = v;
        }
    
    return min_index;
}

// Function to print the shortest path distance from source to each vertex
void printSolution(int dist[], int V) {
    printf("Vertex \t Distance from Source\n");
    for (int i = 0; i < V; i++)
        printf("%d \t\t %d\n", i, dist[i]);
}

// Function that implements Dijkstra's single-source shortest path algorithm
void dijkstra(int graph[MAX_V][MAX_V], int src, int V) {
    int dist[V];  // Output array. dist[i] will hold the shortest distance from src to i
    bool sptSet[V];  // sptSet[i] will be true if vertex i is included in the shortest path tree
    
    // Initialize all distances as INFINITE and sptSet[] as false
    for (int i = 0; i < V; i++) {
        dist[i] = INT_MAX;
        sptSet[i] = false;
    }
    
    // Distance of source vertex from itself is always 0
    dist[src] = 0;
    
    // Find the shortest path for all vertices
    for (int count = 0; count < V - 1; count++) {
        // Pick the minimum distance vertex from the set of vertices not yet processed
        int u = minDistance(dist, sptSet, V);
        
        // Mark the picked vertex as processed
        sptSet[u] = true;
        
        // Update dist[v] only if it is not in sptSet, there is an edge from u to v,
        // and total weight of path from src to v through u is smaller than current value of dist[v]
        for (int v = 0; v < V; v++)
            if (!sptSet[v] && graph[u][v] && dist[u] != INT_MAX && dist[u] + graph[u][v] < dist[v])
                dist[v] = dist[u] + graph[u][v];
    }
    
    // Print the constructed distance array
    printSolution(dist, V);
}

int main() {
    int V;
    
    printf("Enter the number of vertices: ");
    scanf("%d", &V);
    
    if (V > MAX_V) {
        printf("The maximum number of vertices allowed is %d\n", MAX_V);
        return 1;
    }
    
    int graph[MAX_V][MAX_V];
    
    // Initialize the graph with 0 (no edges)
    for (int i = 0; i < V; i++)
        for (int j = 0; j < V; j++)
            graph[i][j] = 0;
    
    printf("Enter the adjacency matrix (enter 0 if there's no direct edge)\n");
    for (int i = 0; i < V; i++) {
        for (int j = 0; j < V; j++) {
            printf("Enter weight for edge from vertex %d to vertex %d: ", i, j);
            scanf("%d", &graph[i][j]);
        }
    }
    
    int source;
    printf("Enter the source vertex: ");
    scanf("%d", &source);
    
    if (source < 0 || source >= V) {
        printf("Invalid source vertex.\n");
        return 1;
    }
    
    dijkstra(graph, source, V);
    
    return 0;
}