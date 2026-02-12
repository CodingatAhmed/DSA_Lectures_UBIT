#include <iostream>
#include <cstdlib>
#include <cstdint>

using namespace std;


struct NodeP {
    int Data;
    NodeP *NextNode;
};
struct Node {
    int Data;
    Node *NextNode;
    bool flag;
};

// Open Hashing with array without pointer, Making methods suitably
Node Hash[10];

void HashInsertion(int Value, int HashSize) {
    int HashIndex;
    HashIndex = Value % HashSize;
    if (Hash[HashIndex].flag == false) {
        Hash[HashIndex].Data = Value;
        Hash[HashIndex].flag = true;
        Hash[HashIndex].NextNode = NULL;
    }
    else {
        Node CurrentNode = Hash[HashIndex];
        Node *CurrentNextNode = CurrentNode.NextNode;
        while (CurrentNextNode->NextNode != NULL) {
            CurrentNextNode = CurrentNextNode->NextNode;
        }
        Node *newNode = (Node *)malloc(sizeof(Node));
        newNode->Data = Value;
        newNode->flag = false;
        newNode->NextNode = NULL;
        CurrentNextNode->NextNode = newNode;
    }
}


// Open Hashing with array with pointer
NodeP *HashPointer[10];
void HashPInsertion(int Value, int HashPSize) {
    int HashIndex;
    HashIndex = Value % HashPSize;
    if (HashPointer[HashIndex] == NULL) {
        HashPointer[HashIndex]->Data = Value;
        HashPointer[HashIndex]->NextNode = NULL;
    }
    else {
        NodeP *CurrentNode = HashPointer[HashIndex];
        while (CurrentNode->NextNode != NULL) {
            CurrentNode = CurrentNode->NextNode;
        }
        NodeP *newNode = (NodeP *)malloc(sizeof(NodeP));
        newNode->Data = Value;
        newNode->NextNode = NULL;
        CurrentNode->NextNode = newNode;
    }
}

void PrintHashArray(Node Array[], int Arraysize)
{
    cout << "{ ";
    for (int i = 0; i < Arraysize; i++)
    {
        cout << Array[i].Data;
        if (i != Arraysize - 1)
            cout << ", ";
    }
    cout << " }" << endl;
}

void PrintHashPArray(NodeP *Array[], int Arraysize)
{
    cout << "{ ";
    for (int i = 0; i < Arraysize; i++)
    {
        cout << Array[i]->Data;
        if (i != Arraysize - 1)
            cout << ", ";
    }
    cout << " }" << endl;
}

int main() {
    // int HashSize = sizeof(Hash)/sizeof(int);
    int HashPSize = sizeof(HashPointer)/sizeof(HashPointer[0]->NextNode);
    // HashInsertion(10, HashSize);
    // PrintHashArray(Hash, HashSize);
    PrintHashPArray(HashPointer, HashPSize);
    return 0;
}