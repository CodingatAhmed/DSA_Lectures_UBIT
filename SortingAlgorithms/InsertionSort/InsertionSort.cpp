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

void InsertionSort(int UnsortedArray[], int ArraySize)
{
    cout << "Insertion Sort: Before Sorting" << endl;
    PrintArray(UnsortedArray, ArraySize);
    int temp = 0;
    int j;
    for (int i = 1; i < ArraySize; i++)
    {
        j = i - 1;
        while (j >= 0 && UnsortedArray[j] > UnsortedArray[j + 1])
        {
            temp = UnsortedArray[j];
            UnsortedArray[j] = UnsortedArray[j + 1];
            UnsortedArray[j + 1] = temp;
            j -= 1;
        }
    }
    cout << "Insertion Sort: After Sorting" << endl;
    PrintArray(UnsortedArray, ArraySize);
}

int main()
{
    int UnsortArray[] = {2, 9, 11, 1, 0, -1, 15};
    int UnsortArraysize = (sizeof(UnsortArray) / sizeof(int));
    InsertionSort(UnsortArray, UnsortArraysize);
    return 0;
}