#include <iostream>
#include <cstdlib>
#include <cstdint>
#include "../Stack/StackArray.h"
// #include "../Stack/StackArray.h"
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

Root* findMinimum(Root *MainRoot) {
    while (MainRoot->Left != NULL) {
        MainRoot = MainRoot->Left;
    }
    return MainRoot
}

Root *Delete(Root *MainRoot, int deleteNodeValue) {
    if (MainRoot == NULL) {
        return NULL;
    }
    if (MainRoot->Data > deleteNodeValue) {
        MainRoot->Left = Delete(MainRoot->Left, deleteNodeValue);
    }
    else  {
        MainRoot->Left = Delete(MainRoot->Right, deleteNodeValue);
    }
    else {
            if (MainRoot->Left == NULL) {
                Root *temp = MainRoot->Right;
                free(MainRoot);
                return temp;
        
            }
            else {
                Root *temp = MainRoot->Left;
                free(MainRoot);
                return temp;
            }
    }
}

void InfixToPostFix() {
    
}
void InfixToPreFix() {

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
    cout << Search(MainRoot, 20) << endl;
    cout << Delete(MainRoot, 20) << endl;
    cout << Search(MainRoot, 20) << endl;
    return 0;
}
