#include <iostream>
#include <vector>
using namespace std;

void PrintArray(int Array[], int Arraysize)
{
    cout << "{ ";
    for (int i = 0; i < Arraysize; i++)
    {
        cout << Array[i];
        if (i != Arraysize - 1)
            cout << ", ";
    }
    cout << " }" << endl;
}

void BubbleSort(int UnsortedArray[], int ArraySize)
{
    cout << "Before Sorting" << endl;
    PrintArray(UnsortedArray, ArraySize);
    int temp = 0;
    for (int i = 0; i < ArraySize; i++)
    {
        for (int j = 0; j < ArraySize - i; j++)
        {
            if (UnsortedArray[j] > UnsortedArray[j + 1])
            {
                temp = UnsortedArray[j];
                UnsortedArray[j] = UnsortedArray[j + 1];
                UnsortedArray[j + 1] = temp;
            }
        }
    }
    cout << "After Sorting" << endl;
    PrintArray(UnsortedArray, ArraySize);
}

int main()
{
    int UnsortArray[] = {2, 9, 11, 1, 0, -1, 15};
    int UnsortArraysize = (sizeof(UnsortArray) / sizeof(int));
    BubbleSort(UnsortArray, UnsortArraysize);
    return 0;
}