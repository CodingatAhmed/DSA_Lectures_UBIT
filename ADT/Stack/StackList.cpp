#include <iostream>
#include <cstdlib>
#include <cstdint>
using namespace std;

struct Stack
{
    int DataValue;
    Stack *StackData;
    int TopPointer;
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
        NewData->TopPointer = 1;
        NewData->StackData = NULL;
        StackList = NewData;
        cout << "Data Added Successfully at index" << NewData->TopPointer << endl;
    }
    else
    {
        Stack *CurrentStackData = StackList;
        if (CurrentStackData->TopPointer < 5)
        {
            CurrentStackData->DataValue = Datavalue;
            CurrentStackData->StackData = StackList;
            CurrentStackData->TopPointer += 1;
            StackList = CurrentStackData;
            cout << "Data Added Successfully at index" << CurrentStackData->TopPointer << endl;
        }
        else
        {
            cout << "Stack is full" << endl;
        }
    }
}

int Pop()
{
    Stack *NewData = (Stack *)malloc(sizeof(Stack));
    if (StackList == NULL)
    {
        return -1;
        // cout << "Stack is empty" << endl;
    }
    else
    {
        Stack *CurrentStackData = StackList;
        int ReturnData;
        if (CurrentStackData->TopPointer > 0)
        {
            ReturnData = CurrentStackData->DataValue;
            CurrentStackData = CurrentStackData->StackData;
            StackList = CurrentStackData;
            CurrentStackData->TopPointer -= 1;
            StackList = CurrentStackData;
            // cout << ReturnData << endl;
            return ReturnData;
            // cout << "Data Added Successfully at index" << CurrentStackData->TopPointer << endl;
        }
        return ReturnData;
        // else {
        //     cout << "Stack is full" << endl;
        // }
    }
}

int main()
{
    Push(10);
    Push(20);
    Push(40);
    Push(30);
    Push(59);
    cout << Pop() << endl;
    Push(19);
    cout << Pop() << endl;
    // cout << Pop() << endl;
    // Push(30);
    // Pop();
    Pop();
    return 0;
    // return 123;
}