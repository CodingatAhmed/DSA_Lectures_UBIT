#include <iostream>
#include <vector>
using namespace std;

int Int_BinarySearch(int DataArray[], int ArraySize, int dataFind)
{
    int countDuplicates = 0;
    int low = 0;
    int high = ArraySize - 1;
    int mid;
    while (low <= high)
    {
        mid = ((low + (high - low)) / 2);
        if (DataArray[mid] == dataFind)
        {
            cout << "Int_LinearSearch: Value " << dataFind << " is found at index " << mid << endl;
            return mid;
        }
        else if (DataArray[mid] < dataFind)
        {
            low = mid + 1;
        }
        else
        {
            high = mid - 1;
        }
    }
    // cout << "Value " << dataFind << " found at index " << i << endl;
    cout << "Int_DuplicateLinearSearch: Value " << dataFind << " is not found in the array" << endl;
    return -1;
    // return countDuplicates;
}
bool Bool_BinarySearch(int DataArray[], int ArraySize, int dataFind)
{
    int low = 0;
    int high = ArraySize - 1;
    int mid;
    while (low <= high)
    {
        mid = low + (high - low) / 2;
        if (DataArray[mid] == dataFind)
        {
            return mid;
        }
        else if (DataArray[mid] < dataFind)
        {
            low = mid + 1;
        }
        else
        {
            high = mid - 1;
        }
    }
    for (int i = 0; i < ArraySize; i++)
    {
        if (DataArray[i] == dataFind)
        {
            cout << "Value " << dataFind << " found at index " << i << endl;
            return true;
        }
    }
    return false;
}

int Int_DuplicateBinarySearch(int DataArray[], int ArraySize, int dataFind)
{
    bool Found;
    int countDuplicates = 0;
    int low = 0;
    int high = ArraySize - 1;
    int mid;
    while (low <= high && Found == false)
    {
        mid = low + (high - low) / 2;
        if (DataArray[mid] == dataFind)
        {
            cout << "Value " << dataFind << " found at index " << mid << endl;
            countDuplicates += 1;
            Found = true;
        }
        else if (DataArray[mid] < dataFind)
        {
            low = mid + 1;
        }
        else
        {
            high = mid - 1;
        }
    }
    if (Found == true)
    {
        int i = mid - 1;
        int j = mid + 1;
        while (i > -1 && DataArray[i] == dataFind)
        {
            cout << "Value " << dataFind << " found at index " << i << endl;
            countDuplicates += 1;
            i -= 1;
        }
        while (j < ArraySize - 1 && DataArray[j] == dataFind)
        {
            cout << "Value " << dataFind << " found at index " << j << endl;
            countDuplicates += 1;
            j += 1;
        }
    }
    if (countDuplicates > 0)
    {
        cout << "Int_DuplicateBinarySearch: Value " << dataFind << " is repeated " << countDuplicates << " times" << endl;
        return countDuplicates;
    }
    else
    {
        cout << "Value " << dataFind << " is not found in the array" << endl;
        return -1;
    }
}

int main()
{
    int DataArray[] = {1, 3, 5, 6, 6, 6, 6, 6, 6, 7, 7, 7, 8};
    int Arraysize = (sizeof(DataArray) / sizeof(int));
    Int_DuplicateBinarySearch(DataArray, Arraysize, 6);
    return 0;
}