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
        NodeP *newNode = (NodeP *)malloc(sizeof(NodeP));
        newNode->Data = Value;
        newNode->NextNode = NULL;
        HashPointer[HashIndex] = newNode;
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
        if(Array[i]==NULL)
        cout<< "NULL ";
        else
        {
        cout << Array[i]->Data;
        if (i != Arraysize - 1)
            cout << ", ";
        }
    }
    cout << " }" << endl;
}

int main() {
    // int HashSize = sizeof(Hash)/sizeof(int);
    int HashPSize = sizeof(HashPointer)/sizeof(HashPointer[0]);
    int HashSize = sizeof(Hash)/sizeof(Hash[0]);
    HashPInsertion(1, HashPSize);
    HashPInsertion(2, HashPSize);
    HashPInsertion(3, HashPSize);
    HashPInsertion(4, HashPSize);
    HashPInsertion(5, HashPSize);
    HashPInsertion(6, HashPSize);
    HashPInsertion(7, HashPSize);
    HashPInsertion(8, HashPSize);
    HashPInsertion(9, HashPSize);
    HashPInsertion(10, HashPSize);
    HashInsertion(1, HashPSize);
    HashInsertion(2, HashSize);
    HashInsertion(3, HashSize);
    HashInsertion(4, HashSize);
    HashInsertion(5, HashSize);
    HashInsertion(6, HashSize);
    HashInsertion(7, HashSize);
    HashInsertion(8, HashSize);
    HashInsertion(9, HashSize);
    HashInsertion(10, HashSize);
    // PrintHashArray(Hash, HashSize);//ashPointer[0]
    PrintHashPArray(HashPointer, HashPSize);
    PrintHashArray(Hash, HashSize);
    return 0;
}