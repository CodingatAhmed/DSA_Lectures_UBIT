#include <iostream>
#include <cstdlib>
#include <cstdint>
#include <queue>
#include <stack>

using namespace std;

struct Root {
    int Data;
    Root *Left;
    Root *Right;
};

Root *MainRoot = (Root *)malloc(sizeof(Root));
// LEFT -> ROOT -> RIGHT
void InOrder(Root *MainRoot) {
    if (MainRoot->Left != NULL) {
        InOrder(MainRoot->Left);
    }
    cout << MainRoot->Data << endl;
    if (MainRoot->Right != NULL) {
        InOrder(MainRoot->Right);
    }
}

// ROOT -> LEFT -> RIGHT
void PreOrder(Root *MainRoot) {
    cout << MainRoot->Data << endl;
    if (MainRoot->Left != NULL) {
        PreOrder(MainRoot->Left);
    }
    if (MainRoot->Right != NULL) {
        PreOrder(MainRoot->Right);
    }
    
}

// LEFT -> RIGHT -> ROOT
void PostOrder(Root *MainRoot) {
    if (MainRoot->Left != NULL) {
        PostOrder(MainRoot->Left);
    }
    if (MainRoot->Right != NULL) {
        PostOrder(MainRoot->Right);
    }
    cout << MainRoot->Data << endl;
}

Root *Search(Root *MainRoot ,int searchValue) {
    if (MainRoot == NULL) {
        return NULL;
    }
    else {
        if (MainRoot->Data == searchValue) {
            return MainRoot;
        }
        else {
            if (MainRoot->Data > searchValue) {
                return Search(MainRoot->Left, searchValue);
            }
            else {
                return Search(MainRoot->Right, searchValue);
            }
        }
    }
}

Root* FindMinimum(Root *MainRoot) {
    if (MainRoot->Left == NULL) {
        return MainRoot;
                
    }
    else {
        Root* FoundNode = FindMinimum(MainRoot->Left);
        MainRoot->Left = NULL;
        return FoundNode;
    }

}

Root* Delete(Root *MainRoot, int deleteNodeValue) {
    if (MainRoot == NULL) {
        return MainRoot;
    }
    
    if (MainRoot->Data > deleteNodeValue) {
        MainRoot->Left = Delete(MainRoot->Left, deleteNodeValue);
    }
    if (MainRoot->Data < deleteNodeValue) {
        MainRoot->Right = Delete(MainRoot->Right, deleteNodeValue);
    }

    if (MainRoot->Data == deleteNodeValue) {
        if (MainRoot->Left == NULL && MainRoot->Right == NULL) {
            return NULL;
        }
        else {
            if (MainRoot->Left != NULL && MainRoot->Right == NULL) {
                return MainRoot->Left;
            }
            else {
                if (MainRoot->Left == NULL && MainRoot->Right != NULL) {
                    return MainRoot->Right;
                }
                else {
                    if (MainRoot->Left != NULL && MainRoot->Right != NULL) {
                            MainRoot->Data = FindMinimum(MainRoot->Right)->Data;
                            return MainRoot;
                            
                        }
                }
            }
        }

        
    }
    return MainRoot;
}


// void InfixToPostFix() {
    
// }
// void InfixToPreFix() {

// }

vector<Root*> MaxHeap(Root* BST) {
    vector<Root*> HeapValues;
    queue<Root*> HeapValToUse;
    HeapValToUse.push(BST);
    while (HeapValToUse.size() > 0)
    {
        Root* frontNode = HeapValToUse.front();
        HeapValToUse.pop();
        HeapValues.push_back(frontNode);
        if (frontNode->Left != NULL) {
            HeapValToUse.push(frontNode->Left);
        }
        if (frontNode->Right != NULL) {
            HeapValToUse.push(frontNode->Right);
        }
    }
    int sizeArray = HeapValues.size();
    int initialIndex = (sizeArray/2) - 1;
    while (initialIndex >= 0) {
        int parentIndex = initialIndex;
        int leftIndex = (2*initialIndex) + 1;
        int rightIndex = (2* initialIndex) + 2;
        if (rightIndex >= sizeArray) {
            if (HeapValues[leftIndex]->Data > HeapValues[parentIndex]->Data) {
                Root* temp = HeapValues[parentIndex];
                HeapValues[parentIndex] = HeapValues[leftIndex];
                HeapValues[leftIndex] = temp;
            }
        }
        else if (rightIndex < sizeArray) {
            if (HeapValues[leftIndex]->Data > HeapValues[rightIndex]->Data) {
                Root* temp = HeapValues[parentIndex];
                HeapValues[parentIndex] = HeapValues[leftIndex];
                HeapValues[leftIndex] = temp;

            }
            if (HeapValues[leftIndex]->Data < HeapValues[rightIndex]->Data) {
                Root* temp = HeapValues[parentIndex];
                HeapValues[parentIndex] = HeapValues[rightIndex];
                HeapValues[rightIndex] = temp;

            }
        }
        initialIndex -= 1;
    }
    return HeapValues;
}


vector<Root*> heapify(vector<Root*> minHeapArray, int size, int startIndex) {
    int sizeMinHeap = minHeapArray.size();
    int parentIndex = startIndex;
    int leftIndex = (2*startIndex) + 1;
    int rightIndex = (2*startIndex) + 2;
    if (minHeapArray[parentIndex] > minHeapArray[leftIndex] && minHeapArray[parentIndex] > minHeapArray[rightIndex] || leftIndex >= sizeMinHeap && rightIndex >= sizeMinHeap) {
        return minHeapArray;
    }
    if (rightIndex >= sizeMinHeap) {
            if (minHeapArray[leftIndex]->Data > minHeapArray[parentIndex]->Data) {
                Root* temp = minHeapArray[parentIndex];
                minHeapArray[parentIndex] = minHeapArray[leftIndex];
                minHeapArray[leftIndex] = temp;
                return heapify(minHeapArray, size, leftIndex);
            }
            else {
                return minHeapArray;
            }
    }
    else if (rightIndex < sizeMinHeap) {
            if (minHeapArray[leftIndex]->Data > minHeapArray[rightIndex]->Data) {
                Root* temp = minHeapArray[parentIndex];
                minHeapArray[parentIndex] = minHeapArray[leftIndex];
                minHeapArray[leftIndex] = temp;
                return heapify(minHeapArray, size, leftIndex);
                
            }
            if (minHeapArray[leftIndex]->Data < minHeapArray[rightIndex]->Data) {
                Root* temp = minHeapArray[parentIndex];
                minHeapArray[parentIndex] = minHeapArray[rightIndex];
                minHeapArray[rightIndex] = temp;
                return heapify(minHeapArray, size, rightIndex);

            }
    }
    return minHeapArray;
}

vector<Root*> HeapSort(vector<Root*> Array) {
    vector<Root*> maxHeapArray = MaxHeap(MainRoot);
    int sizeMaxHeap = maxHeapArray.size();
    if (sizeMaxHeap > 1) {
        return Array;
    }
    else {
        Root* temp = maxHeapArray[0];
        maxHeapArray[0] = maxHeapArray[sizeMaxHeap - 1];
        maxHeapArray[sizeMaxHeap - 1] = temp;
        vector<Root*> heapifyArray = heapify(maxHeapArray, sizeMaxHeap - 1, 0);
        return HeapSort(heapifyArray);
    }
}

void printTreeWithVertices(Root* root, int space) {
    if (root == NULL) return;

    // Increase distance between levels
    space += 8;

    // Process Right child first (Top of the screen)
    printTreeWithVertices(root->Right, space);

    // Print current node
    printf("\n");
    for (int i = 8; i < space; i++) printf(" ");
    
    // Print the vertex connector
    if (space > 8) printf("|---"); 
    
    printf("[%d]\n", root->Data);

    // Process Left child (Bottom of the screen)
    printTreeWithVertices(root->Left, space);
}

void BFSTraversalBST(Root* MainRoot) {
    queue<Root*> NodesToVisit;
    NodesToVisit.push(MainRoot);
    while (NodesToVisit.size() > 0) {
        Root* FrontNode = NodesToVisit.front();
        NodesToVisit.pop();
        cout << FrontNode->Data << endl;
        if (FrontNode->Left != NULL) {
            NodesToVisit.push(FrontNode->Left);
        }
        if (FrontNode->Right != NULL) {
            NodesToVisit.push(FrontNode->Right);
        }
    }
}

void DisplayArray(vector<Root*> Array)
{
    cout << "{";
    for (int i = 0; i < Array.size(); i++)
    {
        cout << Array[i]->Data;
        if (i != Array.size() - 1)
            cout << ", ";
    }
    cout << "}";
}

int main() {
    MainRoot->Data = 50;
    MainRoot->Left = (Root *)malloc(sizeof(Root));
    MainRoot->Left->Data = 30;
    MainRoot->Left->Left = (Root *)malloc(sizeof(Root));
    MainRoot->Left->Left->Data = 20;
    MainRoot->Left->Left->Left = NULL;
    MainRoot->Left->Left->Right = NULL;
    MainRoot->Left->Right = (Root *)malloc(sizeof(Root));
    MainRoot->Left->Right->Data = 40;
    MainRoot->Left->Right->Left = NULL;
    MainRoot->Left->Right->Right = NULL;
    MainRoot->Right = (Root *)malloc(sizeof(Root));
    MainRoot->Right->Data = 70;
    MainRoot->Right->Left = (Root *)malloc(sizeof(Root));
    MainRoot->Right->Left->Left = NULL;
    MainRoot->Right->Left->Right = NULL;
    MainRoot->Right->Left->Data = 60;
    MainRoot->Right->Right = (Root *)malloc(sizeof(Root));
    MainRoot->Right->Right->Left = NULL;
    MainRoot->Right->Right->Right = NULL;
    MainRoot->Right->Right->Data = 80;
    
    // InOrder(MainRoot);
    // cout << Search(MainRoot, 20) << endl;
    // cout << Delete(MainRoot, 20) << endl;
    // cout << Search(MainRoot, 20) << endl;
    // Delete(MainRoot);
    // printTreeWithVertices(MainRoot,0);
    // Delete(MainRoot, 20);
    printTreeWithVertices(MainRoot,0);
    vector<Root*> maxHeapArray = MaxHeap(MainRoot);
    DisplayArray(maxHeapArray);
    // BFSTraversalBST(MainRoot);
    // Delete(MainRoot, 30);
    // printTreeWithVertices(MainRoot,0);
    // Delete(MainRoot, 50);
    // printTreeWithVertices(MainRoot,0);
    return 0;
}
