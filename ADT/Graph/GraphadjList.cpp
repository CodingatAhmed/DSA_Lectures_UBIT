#include <iostream>
#include <cstdlib>
#include <cstdint>
#include <exception>
#include <queue>
#include <stack>

using namespace std;

struct Node {
    int vertice;
    Node* NextNode;
};

struct Graph {
    int NoVertices;
    Node** listOfVertices;
};


Graph* CreateGraph(int Vertices) {
    Graph *graph = new Graph;
    graph->NoVertices = Vertices;
    graph->listOfVertices = new Node*[Vertices];

    for (int i = 0; i < Vertices; i++) {
        graph->listOfVertices[i] = nullptr;
    }
    return graph;
}

Node* createNode(int vertice) {
    Node *newNode = new Node;
    newNode->vertice = vertice;
    newNode->NextNode = nullptr;
    return newNode;
}

struct InvalidVertice : public std::exception {
    const char* what() const throw() {
        return "check your destination and source vertice again, enter valid vertices";
    }
};

void addEdge(Graph* graph, int src, int dest)  {
    if (!graph || src < 0 || dest < 0 || src >= graph->NoVertices || dest >= graph->NoVertices ) {
        throw InvalidVertice();
    }
    Node* destNode = createNode(dest);
    destNode->NextNode = graph->listOfVertices[src];
    graph->listOfVertices[src] = destNode;
    Node* srcNode = createNode(src);
    srcNode->NextNode = graph->listOfVertices[dest];
    graph->listOfVertices[dest] = srcNode;
}

void BFSTraversal(Graph* graph, int StartVertex) {
    if (!graph || StartVertex >= graph->NoVertices || StartVertex < 0) {
        throw InvalidVertice();
    }
    bool* VisitedNodes = new bool[graph->NoVertices];
    for (int i = 0; i < graph->NoVertices ; i++) {
        VisitedNodes[i] = false;
    }
    VisitedNodes[StartVertex] = true;

    queue<int> verticesToPush;
    verticesToPush.push(StartVertex);
    cout << "BFS Traversal" << endl;
    while (verticesToPush.size() > 0) {
        int frontVertex = verticesToPush.front();
        Node* frontNode = graph->listOfVertices[frontVertex];
        verticesToPush.pop();
        VisitedNodes[frontVertex] = true;
        cout << frontVertex << endl;
        while (frontNode != nullptr) {
            if (VisitedNodes[frontNode->vertice] == false) {
                VisitedNodes[frontNode->vertice] = true;
                verticesToPush.push(frontNode->vertice);
            } 
            frontNode = frontNode->NextNode;
        }
    }
}

void DFSRecursion(Graph* graph, int vertex, bool* Visited) {

    Visited[vertex] = true;
    cout << vertex << endl;


    Node* depthNode = graph->listOfVertices[vertex];
    while (depthNode != nullptr) {
        if (!Visited[depthNode->vertice]) {
            DFSRecursion(graph, depthNode->vertice, Visited);
        }
        depthNode = depthNode->NextNode;
    }
}

void DFSTraversal(Graph* graph, int StartVertex) {
    if (!graph || StartVertex < 0 || StartVertex >= graph->NoVertices) {
        throw InvalidVertice();
    }
    bool* VisitedNodes = new bool[graph->NoVertices];
    DFSRecursion(graph, StartVertex, VisitedNodes);
}

void DFSStack(Graph* graph, int vertex) {
    bool* Visited = new bool[graph->NoVertices];
    for (int i = 0; i < graph->NoVertices; i++) {
        Visited[i] = false;
    }
    
    stack<int> VertexToVisit;
    VertexToVisit.push(vertex);
    while (VertexToVisit.size() > 0) {
        int lastVertexIndex = VertexToVisit.top();
        VertexToVisit.pop();
        if (Visited[lastVertexIndex] == false) {
            cout << lastVertexIndex << endl;
            Visited[lastVertexIndex] = true;
        }
        Node *depthNode = graph->listOfVertices[lastVertexIndex];
        stack<int> ReverseVertex;

        // Visited[depthNode->vertice]
        while (depthNode != nullptr) {
            if (Visited[depthNode->vertice] == false) {
                ReverseVertex.push(depthNode->vertice);
            }
            depthNode = depthNode->NextNode;
        }
        while (!ReverseVertex.empty()) {
                VertexToVisit.push(ReverseVertex.top());
                ReverseVertex.pop();

            }
    }
}


void printGraph(Graph* graph) {
    for (int i = 0; i < graph->NoVertices; i++){
        Node *currentVertice = graph->listOfVertices[i];
        cout << "Vertex : " << i << " -> ";
        while (currentVertice != nullptr) {
            cout << "Vertex : " << currentVertice->vertice << " ->";
            currentVertice = currentVertice->NextNode;
        }
        cout << endl;
    }
}

int main() {
    Graph* MainGraph = CreateGraph(4);
    // bool* VisitedVertices = new bool[MainGraph->];
    addEdge(MainGraph, 0,3);
    addEdge(MainGraph, 0,2);
    addEdge(MainGraph, 0,1);
    addEdge(MainGraph, 1,3);
    addEdge(MainGraph, 1,2);
    addEdge(MainGraph, 2,3);

    printGraph(MainGraph);
    BFSTraversal(MainGraph, 0);
    // DFSTraversal(MainGraph, 0);
    // DFSStack(MainGraph, 0);
}