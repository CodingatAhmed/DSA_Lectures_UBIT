#include <iostream>
#include <vector>
#include <cstdlib>
#include <stdlib.h>
#include <cstdint>

using namespace std;

struct Node
{
    Node *previousNode;
    int Data;
    Node *nextNode;
};

Node *List = NULL;

void InsertAtStart(int newData)
{
    Node *NewNode = (Node *)std::malloc(sizeof(Node));
    NewNode->Data = newData;
    NewNode->nextNode = NULL;
    NewNode->previousNode = NULL;
    if (List == NULL)
    {
        List = NewNode;
    }
    else
    {
        Node *MainNode = List;
        List = NewNode;
        MainNode->previousNode = NewNode;
        NewNode->nextNode = MainNode;
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
        Node *CurrentNode = List->nextNode;
        List = CurrentNode;
        List->previousNode = NULL;
    }
};

void InsertAtIndex(int DataEnter, int Position)
{
    Node *NewNode = (Node *)std::malloc(sizeof(Node));
    NewNode->Data = DataEnter;
    NewNode->nextNode = NULL;
    if (List == NULL)
    {
        List = NewNode;
    }
    else
    {
        int Index = 1;
        Node *CurrentNode = List;
        while (Index < Position - 1)
        {
            CurrentNode = CurrentNode->nextNode;
            Index = Index + 1;
        }
        Node *NextNode = CurrentNode->nextNode;
        NewNode->previousNode = CurrentNode;
        NextNode->previousNode = NewNode;
        NewNode->nextNode = NextNode;
        CurrentNode->nextNode = NewNode;
    }
}

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
                CurrentNode = CurrentNode->nextNode;
                Index += 1;
            }
            if (CurrentNode->nextNode->nextNode == NULL)
            {
                CurrentNode->nextNode = NULL;
            }
            else
            {
                CurrentNode->nextNode = CurrentNode->nextNode->nextNode;
            }
        }
        // while (CurrentNode->Next->Next != NULL)
        // {
        // }
        // CurrentNode->Next = NULL;
    }
};

void InsertAtEnd(int newData)
{
    Node *NewNode = (Node *)std::malloc(sizeof(Node));
    NewNode->Data = newData;
    NewNode->nextNode = NULL;
    NewNode->previousNode = NULL;
    if (List == NULL)
    {
        List = NewNode;
    }
    else
    {
        Node *CurrentNode = List;
        while (CurrentNode->nextNode != NULL)
        {
            CurrentNode = CurrentNode->nextNode;
        }
        NewNode->previousNode = CurrentNode;
        CurrentNode->nextNode = NewNode;
    }
};
void DeleteAtEnd()
{
    if (List == NULL)
    {
        cout << "Linked List is Empty, Please Enter Nodes" << endl;
    }
    else
    {
        Node *CurrentNode = List;
        while (CurrentNode->nextNode != NULL)
        {
            CurrentNode = CurrentNode->nextNode;
        }
        CurrentNode->nextNode = NULL;
    }
};

Node *Display()
{
    Node *CurrentNode = List;
    while (CurrentNode->nextNode != NULL)
    {
        cout << CurrentNode->Data << endl;
        CurrentNode = CurrentNode->nextNode;
    }
    cout << CurrentNode->Data << endl;
    return CurrentNode;
}

void ReverseDisplay()
{
    Node *CurrentNode = List;
    while (CurrentNode->nextNode != NULL)
    {
        CurrentNode = CurrentNode->nextNode;
    }
    while (CurrentNode->previousNode != NULL)
    {
        cout << CurrentNode->Data << endl;
        CurrentNode = CurrentNode->previousNode;
    }
    cout << CurrentNode->Data << endl;
}

int main()
{
    InsertAtStart(6);
    InsertAtStart(10);
    InsertAtEnd(4);
    InsertAtEnd(3);
    DeletefromStart();
    InsertAtIndex(18, 3);
    DeletefromIndex(4);
    Display();
    ReverseDisplay();
}