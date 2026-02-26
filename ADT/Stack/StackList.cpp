#include <iostream>
#include <cstdlib>
#include <cstdint>
using namespace std;

struct Stack
{
    int DataValue;
    Stack *StackData;
};

// Stack *StackList = (Stack *)malloc(sizeof(Stack));
Stack *StackList = NULL;

// StackList->TopPointer = 0;
// StackList->StackData = NULL;
// StackList->DataValue = 0;

void Push(int Datavalue)
{
    Stack *NewData = (Stack *)malloc(sizeof(Stack));
    NewData->DataValue = Datavalue;
    if (StackList == NULL)
    {
        NewData->StackData = NULL;
        StackList = NewData;
    }
    else
    {
        NewData->StackData = StackList;
        StackList = NewData;
    }
    cout << "Data Value " << Datavalue << " Added Successfully" << endl;
    }

int Pop()
{
    if (StackList == NULL)
    {
        cout << "Stack is empty" << endl;
        return -1;
    }
    else
    {
        int ReturnData;
        ReturnData = StackList->DataValue;
        StackList = StackList->StackData;
        cout << "Data Value " << ReturnData << " Removed Successfully" << endl;
        return ReturnData;
    }
}

int main()
{
    Push(10);
    Push(20);
    Push(40);
    Pop();
    Push(30);
    Push(59);
    Pop();
    Pop();
    Pop();
    return 0;
    // return 123;
}