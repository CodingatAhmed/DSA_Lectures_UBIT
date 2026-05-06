#include <iostream>
#include <vector>
#include <cstdlib>
#include <stdlib.h>
#include <cstdint>

using namespace std;

// struct Node {
//     int Data;
//     Node* nextNode;
// }

// struct Graph {
//     int NumOfVertices;
//     Node** GraphNodes;
// }

// void InitialiseGraph(Graph* graph, int Vertices) {
//     graph->GraphNodes = Node*[Vertices];
    
// }
int Factorial(int Num) {
    if (Num == 0) {
        return 1;
    }

    else {
        return Factorial(Num - 1);
    }
}
int main() {
    cout << Factorial(5) << endl;
}

