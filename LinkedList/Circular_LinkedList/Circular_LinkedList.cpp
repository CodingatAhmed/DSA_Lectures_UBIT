#include <iostream>
#include <cstdlib>
#include <cstdint>

using namespace std;

struct Node
{
    int Data;
    Node *Next;
};

Node *List = NULL;

void InsertAtEnd(int DataValue)
{
    Node *Temp = (Node *)std::malloc(sizeof(Node));
    Temp->Data = DataValue;
    Temp->Next = NULL;
    if (List == NULL)
    {
        List = Temp;
    }
    else
    {
        Node *CurrentNode = List;
        while (CurrentNode->Next != NULL)
        {
            CurrentNode = CurrentNode->Next;
        }
        CurrentNode->Next = Temp;
        Temp->Next = List;
    }
}
void DeletefromEnd() {

};

void Search(int FindValue)
{
    Node *CurrentNode = List;
    int Position = 1;
    while (CurrentNode != NULL && CurrentNode->Data != FindValue)
    {
        CurrentNode = CurrentNode->Next;
        Position += 1;
    }
    if (CurrentNode == NULL)
    {
        cout << FindValue << " is not Found in this List " << endl;
    }
    else
    {
        cout << FindValue << " Found in this List at Index " << Position << endl;
    }
}
void Display()
{
    Node *CurrentNode = List;
    while (CurrentNode->Next != NULL && CurrentNode->Next != List)
    {
        cout << CurrentNode->Data << endl;
        CurrentNode = CurrentNode->Next;
    }
    cout << CurrentNode->Data << endl;
    // cout << CurrentNode->Data << endl;
}

int main()
{
    // InsertAtStart(40);
    InsertAtEnd(10);
    InsertAtEnd(20);
    Search(20);
    Display();
    // InsertAtEnd(30);
    // DeletefromEnd();
    // Display();
    // Search(30);
}