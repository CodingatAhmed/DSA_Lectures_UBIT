#include <iostream>

using namespace std;

// A single node in a linked list representing a connection
struct Node {
    int vertex;
    Node* next;
};

// The Graph structure
struct Graph {
    int numVertices;
    Node** adjLists; // An array of pointers to Nodes
};

// Function to create a new node
Node* createNode(int v) {
    Node* newNode = new Node;
    newNode->vertex = v;
    newNode->next = nullptr;
    return newNode;
}

// Function to create a graph with V vertices
Graph* createGraph(int vertices) {
    Graph* graph = new Graph;
    graph->numVertices = vertices;

    // Create an array of head pointers for each vertex
    graph->adjLists = new Node*[vertices];

    // Initialize all heads to NULL (meaning no connections yet)
    for (int i = 0; i < vertices; i++) {
        graph->adjLists[i] = nullptr;
    }

    return graph;
}

// Function to add an edge (Undirected)
void addEdge(Graph* graph, int src, int dest) {
    
    if (!graph || src < 0 || dest < 0 || src >= graph->numVertices || dest >= graph->numVertices) {
        cout << "Error: Invalid vertex index (" << src << ", " << dest << ")" << endl;
        return; 
    }
    // Add edge from src to dest
    Node* newNode = createNode(dest);
    newNode->next = graph->adjLists[src];
    graph->adjLists[src] = newNode;

    // Add edge from dest to src (because it's undirected)
    newNode = createNode(src);
    newNode->next = graph->adjLists[dest];
    graph->adjLists[dest] = newNode;
}

// Function to print the graph
void printGraph(Graph* graph) {
    for (int i = 0; i < graph->numVertices; i++) {
        Node* temp = graph->adjLists[i];
        cout << "Vertex " << i << ":";
        while (temp) {
            cout << " -> " << temp->vertex;
            temp = temp->next;
        }
        cout << endl;
    }
}

// Main function to demonstrate usage
int main() {
    int totalVertices = 4;
    Graph* graph = createGraph(totalVertices);

    // addEdge(graph, 0, 1);
    // addEdge(graph, 0, 2);
    // addEdge(graph, 1, 2);
    // addEdge(graph, 2, 3);
    addEdge(graph, 0,1);
    addEdge(graph, 0,2);
    addEdge(graph, 0,3);
    addEdge(graph, 1,2);
    addEdge(graph, 1,3);
    addEdge(graph, 2,3);

    printGraph(graph);

    return 0;
}