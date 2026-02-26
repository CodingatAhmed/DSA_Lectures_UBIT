#include <iostream>
#include <vector>
using namespace std;

void QuickSort(int Array[], int ArraySize) {
    int pivotIndex = ArraySize - 1;
    int i = -1;
    int j = 0;
    int temp;
    while (j < pivotIndex) {
        if (Array[j] < Array[pivotIndex]) {
            i += 1;
            temp = Array[i];
            Array[i] = Array[j];
            Array[j] = temp;
        }
        j += 1;
    }
    temp = Array[i + 1];
    Array[i + 1] = Array[pivotIndex];
    Array[pivotIndex] = temp;
}

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

int main() {
    int PassArray[] = {10, 80, 30, 90, 40}; //3,4,12,56,78
    int ArraySize = sizeof(PassArray)/ sizeof(int);
    QuickSort(PassArray, ArraySize);
    PrintArray(PassArray, ArraySize);
    return 0;
}