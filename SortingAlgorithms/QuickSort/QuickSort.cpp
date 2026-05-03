#include <iostream>
#include <vector>
using namespace std;

void swap(int &a, int &b) {
    int temp = a;
    a = b;
    b = temp;
}

int partition(int Array[], int low , int high) {
    int pivot = Array[high];
    int i = (low - 1);   

    for (int j = low; j < high; j++) {
        if (Array[j] <= pivot) {
            i++; 
            swap(Array[i], Array[j]);
        }
    }
    swap(Array[i + 1], Array[high]);
    return (i + 1);
}

void QuickSort(int Array[], int low, int high) {
    if (low < high) {
        int PartitionIndex = partition(Array, low, high);

        QuickSort(Array, PartitionIndex + 1, high);
        QuickSort(Array, low, PartitionIndex - 1);
    }

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
    QuickSort(PassArray, 0, ArraySize - 1);
    PrintArray(PassArray, ArraySize);
    return 0;
}