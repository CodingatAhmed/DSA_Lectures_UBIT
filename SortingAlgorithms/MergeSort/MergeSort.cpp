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
void merge(int array[], int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;

    int* L = new int[n1];
    int* R = new int[n2];

    for (int i = 0; i < n1; i++)
        L[i] = array[left + i];
    for (int j = 0; j < n2; j++)
        R[j] = array[mid + 1 + j];

    int i = 0, j = 0, k = left;

    while (i < n1 && j < n2) {
        if (L[i] <= R[j])
            array[k++] = L[i++];
        else
            array[k++] = R[j++];
    }

    while (i < n1)
        array[k++] = L[i++];

    while (j < n2)
        array[k++] = R[j++];

    delete[] L;
    delete[] R;
}

void MergeSort(int array[], int left, int right) {
    if (left >= right) {
        return;
    }
        int mid = (left + ((right - left) / 2));
        MergeSort(array, left, mid);
        MergeSort(array, mid + 1, right);
        merge(array, left, mid, right);
}



int main() {
    int PassArray[] = {12,3,78,4,56}; //3,4,12,56,78
    int ArraySize = sizeof(PassArray)/ sizeof(int);
    MergeSort(PassArray, 0, ArraySize - 1);
    PrintArray(PassArray, ArraySize);
    return 0;
}