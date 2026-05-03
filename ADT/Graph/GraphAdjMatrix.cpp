#include <iostream>
#include <cstdlib>
#include <cstdint>
#include <exception>
#include <queue>
#include <stack>

using namespace std;

struct InvalidVertice : public std::exception {
    const char* what() const throw() {
        return "check your destination and source vertice again, enter valid vertices";
    }
};

int** CreateGraph(int Vertices) {
    int** Graph = new int*[Vertices];
    for (int k = 0; k < Vertices; k++) {
        Graph[k] = new int[Vertices];       
        for (int j = 0; j < Vertices; j++) {
            Graph[k][j] = 0;
        }
    }
        return Graph;
}

void addEdge(int** graph, int noOfVertices, int src, int dest) {
    if (!graph || src < 0 || dest < 0 ) {
        throw InvalidVertice();
    }
    graph[src][dest] = 1;
    graph[dest][src] = 1;

}

void BFSTraversal(int** graph, int noOfVertices, int startVertex) {
    bool* visitedNodes = new bool[noOfVertices];
    for (int i = 0; i < noOfVertices ; i++) {
        visitedNodes[i] = false;
    }
    visitedNodes[startVertex] = true;
    queue<int> VerticesToVisit;
    cout << "BFS Traversal ADJ Matrix" << endl;
    VerticesToVisit.push(startVertex);
    while (VerticesToVisit.size() > 0) {
        int frontVertex = VerticesToVisit.front();
        VerticesToVisit.pop();
        cout << frontVertex << endl;
        for (int j = 0; j < noOfVertices; j++) {
            if (visitedNodes[j] == false && graph[frontVertex][j] == 1) {
                visitedNodes[j] = true;
                VerticesToVisit.push(j);   
            }
        }
    }
}

bool* GraphConnectionRecursion(int** Graph, int NoOfVertices ,int startVertex , bool* Visited) {
    if (Visited[startVertex] == true) {
        return Visited;
    }
    else {
        Visited[startVertex] = true;
        for (int i = 0; i < NoOfVertices; i++) {
            if (Graph[startVertex][i] == 1 && startVertex != i && Visited[i] == false) {
                GraphConnectionRecursion(Graph, NoOfVertices, i, Visited);
            }
        }
        
    }
    return Visited;
    // bool* VisitedNodes = new bool[NoOfVertices];
    // bool AllVisited = true;
    // for (int i = 0; i < NoOfVertices; i++) {
    //     VisitedNodes[i] = false;
    // }
    // VisitedNodes[startVertex] = true;
    // queue<int> VertexToVisit;
    // VertexToVisit.push(startVertex);
    // while (VertexToVisit.size() > 0 && AllVisited == true) {
    //     int frontVertex = VertexToVisit.front();
    //     VertexToVisit.pop();
    //     for (int k = 0; k < NoOfVertices ; k++) {
    //         if (Graph[frontVertex][k] == 0 && frontVertex != k) {
    //             AllVisited = false;
    //         }
    //     }
    //     VisitedNodes[frontVertex] = AllVisited;
    //     AllVisited = true;
    // }
    // for (int j = 0;j < NoOfVertices; j++) {
    //     if (VisitedNodes[j] == false) {
    //         AllVisited = false;
    //     }
    // }
    // if (AllVisited == false) {
    //     cout << "Graph is not connected" << endl;
    // }
    // else {
    //     cout << "Graph is connected" << endl;
    // }

}

void GraphConnectionTraversal(int** Graph, int NoOfVertices, int startVertex) {
    bool* VisitVertex = new bool[NoOfVertices];
    bool AllVisited = true;
    for (int j = 0; j < NoOfVertices; j++) {
        VisitVertex[j] = false;
    }
    bool* IsConnected = GraphConnectionRecursion(Graph, NoOfVertices, startVertex, VisitVertex);
    for (int i = 0;i < NoOfVertices; i++) {
        if (IsConnected[i] == false) {
            AllVisited = false;
        }
    }
    if (AllVisited) {
        cout << "Graph connected" << endl;
    }
    else {
        cout << "Graph not connected" << endl;
    }
}
 

bool GraphCylicCheck(int** Graph, int NoOfVertices, int StartVertex, int ParentVertex, bool* VerticeVisit) {
    if (VerticeVisit[StartVertex] == true) {
        return true;
    }                                   
    VerticeVisit[StartVertex] = true;
    for (int i = 0; i < NoOfVertices; i++) {
        if (Graph[StartVertex][i] == 1 && i != ParentVertex) {
            return GraphCylicCheck(Graph, NoOfVertices, Graph[StartVertex][i], StartVertex, VerticeVisit);
        }
    }
    return false;
}

void GraphCyclicTraversal(int** Graph, int NoOfVertices, int startVertex) {
    bool* VisitVertex = new bool[NoOfVertices];
    for (int j = 0; j < NoOfVertices; j++) {
        VisitVertex[j] = false;
    }
    bool IsConnected = GraphCylicCheck(Graph, NoOfVertices, startVertex, -1, VisitVertex);
    if (IsConnected) {
        cout << "Graph Cylic" << endl;
    }
    else {
        cout << "Graph not Cyclic" << endl;
    }
}
// DFSRecursion()
// DFSStack()

int main() {
    int** MainGraph = CreateGraph(5);
    int sizeOfGraph = sizeof(MainGraph) / 2;
    addEdge(MainGraph, sizeOfGraph, 0,1);
    addEdge(MainGraph, sizeOfGraph, 0,2);
    addEdge(MainGraph, sizeOfGraph, 0,3);
    // addEdge(MainGraph, sizeOfGraph, 1,3);
    // addEdge(MainGraph, sizeOfGraph, 1,3);
    // addEdge(MainGraph, sizeOfGraph, 2,3);
    // addEdge(MainGraph, sizeOfGraph, 3,4);
    // addEdge(MainGraph, sizeOfGraph, 4,2);
    // addEdge(MainGraph, sizeOfGraph, 1,3);
    
    GraphConnectionTraversal(MainGraph, sizeOfGraph, 0);
    // GraphCyclicTraversal(MainGraph, sizeOfGraph, 4);
    // BFSTraversal(MainGraph, 4, 0);
}