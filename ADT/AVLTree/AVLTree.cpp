#include <iostream>
#include <cstdlib>
#include <cstdint>

using namespace std;


struct AVLNode {
    int Data;
    AVLNode * Left = NULL;
    AVLNode * Right = NULL;
    int Height = 1;
};

AVLNode *MainAVLNode = (AVLNode *)malloc(sizeof(AVLNode));

int getHeight(AVLNode *MainAVLNode) {
    if (MainAVLNode == NULL) {
        return 0;
    }
    else {
        return MainAVLNode->Height;
    }
}

int max(int LeftHeight, int RightHeight) {
    if (LeftHeight > RightHeight) {
        return LeftHeight;
    }
    else {
        return RightHeight;
    }
}

int getBalance(AVLNode* Node) {
    if (Node == NULL) {
     return 0;
    }
    else {
        return getHeight(Node->Left) - getHeight(Node->Right);
    }    
}

AVLNode* RightRotate(AVLNode* MainNode) {
    AVLNode* LeftNode = MainNode->Left;
    AVLNode* LRNode = LeftNode->Right;

    LeftNode->Right = MainNode;
    MainNode->Left = LRNode;

    // Update heights using max and getHeight
    MainNode->Height = max(getHeight(MainNode->Left), getHeight(MainNode->Right)) + 1;
    LRNode->Height = max(getHeight(LeftNode->Left), getHeight(LeftNode->Right)) + 1;

    return LeftNode;
}

AVLNode* LeftRotate(AVLNode* MainNode) {
    AVLNode* RightNode = MainNode->Right;
    AVLNode* RLNode = RightNode->Left;

    RightNode->Left = MainNode;
    MainNode->Right = RLNode;

    // Update heights using max and getHeight
    MainNode->Height = max(getHeight(MainNode->Left), getHeight(MainNode->Right)) + 1;
    RLNode->Height = max(getHeight(RightNode->Left), getHeight(RightNode->Right)) + 1;

    return RightNode;
}

AVLNode* InsertNode(AVLNode* Node, int dataValue) {
    if (Node == NULL) {
        AVLNode *newNode = (AVLNode *)malloc(sizeof(AVLNode));
        newNode->Data = dataValue;
        return newNode;
    }

    if (dataValue < Node->Data) {
        Node->Left = InsertNode(Node->Left, dataValue);
    } else if (dataValue > Node->Data) {
        Node->Right = InsertNode(Node->Right, dataValue);
    } else {
        // Duplicate keys are generally not allowed in AVL trees
        return Node;
    }

    // 2. UPDATE HEIGHT OF THIS ANCESTOR NODE
    Node->Height = 1 + max(getHeight(Node->Left), getHeight(Node->Right));

    // 3. GET THE BALANCE FACTOR 
    int balance = getBalance(Node);

    // 4. REBALANCE THE NODE IF IT BECAME UNBALANCED
    // Case 1: Left Left (LL)
    if (balance > 1 && dataValue < Node->Left->Data) {
        return RightRotate(Node);
    }

    // Case 2: Right Right (RR)
    if (balance < -1 && dataValue > Node->Right->Data) {
        return LeftRotate(Node);
    }

    // Case 3: Left Right (LR)
    if (balance > 1 && dataValue > Node->Left->Data) {
        Node->Right = LeftRotate(Node->Left);
        return RightRotate(Node);
    }

    // Case 4: Right Left (RL)
    if (balance < -1 && dataValue < Node->Right->Data) {
        Node->Right = RightRotate(Node->Right);
        return LeftRotate(Node);
    }

    return Node;
}

AVLNode* minValueNode(AVLNode* Node) {
    AVLNode* currentNode = Node;
    while (currentNode->Left != NULL) {
        currentNode = currentNode->Left;
    } 
    return currentNode;
}

AVLNode* deleteNode(AVLNode* root, int dataValue) {
    if (root == NULL) {
        return root;
    }

    if (dataValue < root->Data) {
        root->Left = deleteNode(root->Left, dataValue);
    } else if (dataValue > root->Data) {
        root->Right = deleteNode(root->Right, dataValue);
    } else {
        
        // Case A: One child or No child
        if ((root->Left == NULL) || (root->Right == NULL)) {
            AVLNode* temp = root->Left ? root->Left : root->Right;

            if (temp == NULL) { // No child case
                temp = root;
                root = NULL;
            } else { // One child case
                *root = *temp; // Copy the contents of the non-empty child
            }
            free(temp);
        } else {
            // Case B: Two children
            // Get the inorder successor (smallest in the right subtree)
            AVLNode* temp = minValueNode(root->Right);

            // Copy the successor's data to this node
            root->Data = temp->Data;

            // Delete the successor
            root->Right = deleteNode(root->Right, temp->Data);
        }
    }

    // If the tree had only one node, return
    if (root == NULL) {
        return root;
    } 

    // 2. UPDATE HEIGHT
    root->Height = 1 + max(getHeight(root->Left), getHeight(root->Right));

    // 3. REBALANCE
    int balance = getBalance(root);

    // Left Heavy (Case 1 & 3)
    if (balance > 1 && getBalance(root->Left) >= 0) {
        return RightRotate(root);
    }
    if (balance > 1 && getBalance(root->Left) < 0) {
        root->Left = LeftRotate(root->Left);
        return RightRotate(root);
    }

    // Right Heavy (Case 2 & 4)
    if (balance < -1 && getBalance(root->Right) <= 0) {
        return LeftRotate(root);
    }
    if (balance < -1 && getBalance(root->Right) > 0) {
        root->Right = RightRotate(root->Right);
        return LeftRotate(root);
    }

    return root;
}

AVLNode* SearchNode(AVLNode* root, int dataValue) {
    if (root == NULL || root->Data == dataValue) {
        return root;
    }

    if (dataValue > root->Data) {
        return SearchNode(root->Right, dataValue);
    }

    return SearchNode(root->Left, dataValue);
}

int main() {
    AVLNode* MainNode = NULL;
    int AVLTreeData[] = {120, 110, 150, 130, 140, 146, 136, 134, 138, 160, 154, 156, 132, 125, 128};
    int TreeSize = sizeof(AVLTreeData) / sizeof(int);
    for (int i = 0 ; i < TreeSize ; i++) {
        InsertNode(MainNode, AVLTreeData[i]);
    }
    return 0;
}