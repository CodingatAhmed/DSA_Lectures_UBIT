#include <iostream>
#include <vector>
using namespace std;

int Int_LinearSearch(int DataArray[], int ArraySize, int dataFind)
{
    for (int i = 0; i < ArraySize; i++)
    {
        if (DataArray[i] == dataFind)
        {
            cout << "Int_LinearSearch: Value " << dataFind << " found at index " << i << endl;
            return i;
        }
    }
    cout << "Int_LinearSearch: Value " << dataFind << " not found in the array " << endl;
    return -1;
}
bool Bool_LinearSearch(int DataArray[], int ArraySize, int dataFind)
{
    for (int i = 0; i < ArraySize; i++)
    {
        if (DataArray[i] == dataFind)
        {
            cout << "Bool_LinearSearch: Value " << dataFind << " found at index " << i << endl;
            return true;
        }
    }
    cout << "Bool_LinearSearch: Value " << dataFind << "not found in the array" << endl;
    return false;
}

int Int_DuplicateLinearSearch(int DataArray[], int ArraySize, int dataFind)
{
    int countDuplicates = 0;
    for (int i = 0; i < ArraySize; i++)
    {
        if (DataArray[i] == dataFind)
        {
            cout << "Int_DuplicateLinearSearch: Value " << dataFind << " found at index " << i << endl;
            countDuplicates += 1;
        }
    }
    if (countDuplicates == 0)
    {
        // cout << "Value " << dataFind << " found at index " << i << endl;
        cout << "Int_DuplicateLinearSearch: Value " << dataFind << " is not found in the array" << endl;
        return -1;
    }
    else
    {
        cout << "Int_DuplicateLinearSearch: Value " << dataFind << " is repeated " << countDuplicates << " times" << endl;
        return countDuplicates;
    }
}

int main()
{
    int DataArray[] = {1, 3, 5, 6, 6, 6, 6, 7, 7, 7, 7, 7, 8};
    int Arraysize = (sizeof(DataArray) / sizeof(int));
    Int_LinearSearch(DataArray, Arraysize, 6);
    return 0;
}