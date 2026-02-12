#include <iostream>
#include <cstdlib>
#include <cstdint>
using namespace std;

int StackArray[] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
int TopPointer = 0;

void Push(int DataValue)
{
    if (TopPointer < 10)
    {
        StackArray[TopPointer] = DataValue;
        TopPointer += 1;
    }
    else
    {
        cout << "Stack is full" << endl;
    }
}

int Pop(int DataValue)
{
    if (TopPointer > 1)
    {
        int ReturnValue;
        TopPointer -= 1;
        ReturnValue = StackArray[TopPointer];
        return ReturnValue;
    }
    else
    {
        cout << "Stack is empty" << endl;
        return -1;
    }
}

void DisplayArray(int Array[], int ArraySize)
{
    cout << "{";
    for (int i = 0; i < ArraySize; i++)
    {
        cout << Array[i];
        if (i != ArraySize - 1)
            cout << ", ";
    }
    cout << "}";
}

int main()
{
    int StackArraySize = sizeof(StackArray) / sizeof(int);
    DisplayArray(StackArray, StackArraySize);
    Push(10);
    DisplayArray(StackArray, StackArraySize);
    return 0;
}