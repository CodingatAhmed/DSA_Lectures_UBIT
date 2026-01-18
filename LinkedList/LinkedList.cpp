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
    }
};
void DeletefromEnd()
{
    if (List == NULL)
    {
        cout << "Linked List is Empty, Please Enter Nodes" << endl;
    }
    else
    {
        Node *CurrentNode = List;
        while (CurrentNode->Next->Next != NULL)
        {
            CurrentNode = CurrentNode->Next;
        }
        CurrentNode->Next = NULL;
    }
};
void InsertAtStart(int DataValue)
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
        Node *MainList = List;
        List = Temp;
        Temp->Next = MainList;
    }
};
void DeletefromStart()
{
    if (List == NULL)
    {
        cout << "Linked List is Empty, Please Enter Nodes" << endl;
    }
    else
    {
        Node *CurrentNode = List->Next;
        List = CurrentNode;
        // while (CurrentNode->Next->Next != NULL)
        // {
        //     CurrentNode = CurrentNode->Next;
        // }
        // CurrentNode->Next = NULL;
    }
};

void InsertAtIndex(int DataValue, int Position)
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
        int Index = 1;
        Node *CurrentNode = List;
        while (Index < Position - 1)
        {
            CurrentNode = CurrentNode->Next;
            Index = Index + 1;
        }
        Node *NextNode = CurrentNode->Next;
        Temp->Next = NextNode;
        CurrentNode->Next = Temp;
    }
};

void DeletefromIndex(int Position)
{
    if (List == NULL)
    {
        cout << "Linked List is Empty, Please Enter Nodes" << endl;
    }
    else
    {
        if (Position == 1)
        {
            DeletefromStart();
        }
        else
        {
            int Index = 1;
            Node *CurrentNode = List;
            while (Index < Position - 1)
            {
                CurrentNode = CurrentNode->Next;
            }
            if (CurrentNode->Next->Next == NULL)
            {
                CurrentNode->Next = NULL;
            }
            else
            {
                CurrentNode->Next = CurrentNode->Next->Next;
            }
        }
        // while (CurrentNode->Next->Next != NULL)
        // {
        // }
        // CurrentNode->Next = NULL;
    }
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
    while (CurrentNode->Next != NULL)
    {
        cout << CurrentNode->Data << endl;
        CurrentNode = CurrentNode->Next;
    }
    cout << CurrentNode->Data << endl;
}

int main()
{
    InsertAtStart(40);
    InsertAtEnd(10);
    InsertAtEnd(20);
    InsertAtEnd(30);
    DeletefromEnd();
    Display();
    Search(30);
}