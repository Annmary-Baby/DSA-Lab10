#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define V 5 // Number of vertices

// Function to find the vertex with the minimum key value
int minKey(int key[], int mstSet[]) {
    int min = INT_MAX, min_index;

    for (int v = 0; v < V; v++) {
        if (mstSet[v] == 0 && key[v] < min) {
            min = key[v];
            min_index = v;
        }
    }

    return min_index;
}

// Function to print the MST using Prim's algorithm
void primMST(int graph[V][V]) {
    int parent[V]; // Array to store constructed MST
    int key[V];    // Key values used to pick minimum weight edge in cut
    int mstSet[V]; // To represent set of vertices included in MST

    // Initialize key values and mstSet
    for (int i = 0; i < V; i++) {
        key[i] = INT_MAX;
        mstSet[i] = 0;
    }

    // Always include the first vertex in MST
    key[0] = 0;
    parent[0] = -1; // First node is always the root of MST

    // Construct MST
    for (int count = 0; count < V - 1; count++) {
        int u = minKey(key, mstSet);

        mstSet[u] = 1;

        // Update key value and parent index of adjacent vertices
        for (int v = 0; v < V; v++) {
            if (graph[u][v] && mstSet[v] == 0 && graph[u][v] < key[v]) {
                parent[v] = u;
                key[v] = graph[u][v];
            }
        }
    }

    // Print the constructed MST
    printf("Prim's MST:\n");
    for (int i = 1; i < V; i++)
        printf("%d - %d\n", parent[i], i);
}

// Structure to represent an edge in the graph
struct Edge {
    int src, dest, weight;
};

// Function to find the set of an element i
int find(int parent[], int i) {
    if (parent[i] == -1)
        return i;
    return find(parent, parent[i]);
}

// Function to perform union of two sets
void unionSets(int parent[], int x, int y) {
    int xset = find(parent, x);
    int yset = find(parent, y);
    parent[xset] = yset;
}

// Function to compare edges for sorting
int compareEdges(const void* a, const void* b) {
    return ((struct Edge*)a)->weight - ((struct Edge*)b)->weight;
}

// Function to print the MST using Kruskal's algorithm
void kruskalMST(struct Edge edges[]) {
    struct Edge result[V - 1]; // To store the result MST
    int parent[V];             // Array for union-find

    // Initialize parent array
    for (int i = 0; i < V; i++)
        parent[i] = -1;

    // Sort all the edges in non-decreasing order of their weight
    qsort(edges, V - 1, sizeof(edges[0]), compareEdges);

    printf("Kruskal's MST:\n");

    // Iterate through all edges in the sorted order
    for (int i = 0, j = 0; i < V - 1; i++) {
        int x = find(parent, edges[i].src);
        int y = find(parent, edges[i].dest);

        // Include the edge if it doesn't create a cycle
        if (x != y) {
            result[j++] = edges[i];
            unionSets(parent, x, y);
        }
    }

    // Print the constructed MST
    for (int i = 0; i < V - 1; i++)
        printf("%d - %d\n", result[i].src, result[i].dest);
}

int main() {
    int graph[V][V] = {
        {0, 2, 0, 6, 0},
        {2, 0, 3, 8, 5},
        {0, 3, 0, 0, 7},
        {6, 8, 0, 0, 9},
        {0, 5, 7, 9, 0}
    };

    struct Edge edges[V - 1] = {
        {0, 1, 2},
        {0, 3, 6},
        {1, 2, 3},
        {1, 4, 5},
        {2, 3, 4}  // Corrected the last edge
    };

    primMST(graph);
    kruskalMST(edges);

    return 0;
}
