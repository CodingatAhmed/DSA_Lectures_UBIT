#include <iostream>
#include <cstdlib>
#include <cstdint>

using namespace std;

int QueueArray[] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
int TailPointer = 0;
int HeadPointer = 0;
int SizeOfQueue = 0;

void Enqueue(int DataValue)
{
    if (SizeOfQueue < 10)
    {
        if (TailPointer == 10) {
            TailPointer = 0;
        }
        QueueArray[TailPointer] = DataValue;
        TailPointer += 1;
        SizeOfQueue += 1;
        cout << "Data added in queue" << endl;
    }
    else
    {
        cout << "Queue is full" << endl;
    }
}

void Dequeue()
{
    if (SizeOfQueue > 0)
    {
        if (HeadPointer == 10) {
            HeadPointer = 0;
        }
        int ReturnValue;
        ReturnValue = QueueArray[HeadPointer];
        HeadPointer += 1;
        SizeOfQueue -= 1;
        cout << ReturnValue << endl;
        cout << "Data value " << ReturnValue << " Removed Successfully" << endl;
    }
    else
    {
        cout << "Queue is empty" << endl;
        // return -1;
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

int main() {
    int Arraysize = sizeof(QueueArray)/ sizeof(int);
    Enqueue(10);
    Enqueue(200);
    Enqueue(250);
    Enqueue(350);
    Dequeue();
    Dequeue();
    Dequeue();
    Dequeue();
    Dequeue();
    DisplayArray(QueueArray, Arraysize);
    return 0;
}