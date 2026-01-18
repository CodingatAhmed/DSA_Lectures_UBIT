#include <iostream>
#include <vector>
#include <cstdlib>
#include <stdlib.h>
#include <cstdint>

using namespace std;

// struct DoublyNode
// {
//     int Data;

// }

struct Node
{
    int Data;
    Node *Next;
};

Node *List = NULL;

void InsertAtEnd(int DataValue)
{
    Node *Temp = (Node *)std::malloc(sizeof(Node));
    Temp->Data = DataValue;
    Temp->Next = NULL;
    if (List == NULL)
    {
        List = Temp;
    }
    else
    {
        Node *CurrentNode = List;
        while (CurrentNode->Next != NULL)
        {
            CurrentNode = CurrentNode->Next;
        }
        CurrentNode->Next = Temp;
    }
};
void DeletefromEnd()
{
    if (List == NULL)
    {
        cout << "Linked List is Empty, Please Enter Nodes" << endl;
    }
    else
    {
        Node *CurrentNode = List;
        while (CurrentNode->Next->Next != NULL)
        {
            CurrentNode = CurrentNode->Next;
        }
        CurrentNode->Next = NULL;
    }
};
void InsertAtStart(int DataValue)
{
    Node *Temp = (Node *)std::malloc(sizeof(Node));
    Temp->Data = DataValue;
    Temp->Next = NULL;
    if (List == NULL)
    {
        List = Temp;
    }
    else
    {
        Node *MainList = List;
        List = Temp;
        Temp->Next = MainList;
    }
};
void DeletefromStart()
{
    if (List == NULL)
    {
        cout << "Linked List is Empty, Please Enter Nodes" << endl;
    }
    else
    {
        Node *CurrentNode = List->Next;
        List = CurrentNode;
        // while (CurrentNode->Next->Next != NULL)
        // {
        //     CurrentNode = CurrentNode->Next;
        // }
        // CurrentNode->Next = NULL;
    }
};

void InsertAtIndex(int DataValue, int Position)
{
    Node *Temp = (Node *)std::malloc(sizeof(Node));
    Temp->Data = DataValue;
    Temp->Next = NULL;
    if (List == NULL)
    {
        List = Temp;
    }
    else
    {
        int Index = 1;
        Node *CurrentNode = List;
        while (Index < Position - 1)
        {
            CurrentNode = CurrentNode->Next;
            Index = Index + 1;
        }
        Node *NextNode = CurrentNode->Next;
        Temp->Next = NextNode;
        CurrentNode->Next = Temp;
    }
};

void DeletefromIndex(int Position)
{
    if (List == NULL)
    {
        cout << "Linked List is Empty, Please Enter Nodes" << endl;
    }
    else
    {
        if (Position == 1)
        {
            DeletefromStart();
        }
        else
        {
            int Index = 1;
            Node *CurrentNode = List;
            while (Index < Position - 1)
            {
                CurrentNode = CurrentNode->Next;
            }
            if (CurrentNode->Next->Next == NULL)
            {
                CurrentNode->Next = NULL;
            }
            else
            {
                CurrentNode->Next = CurrentNode->Next->Next;
            }
        }
        // while (CurrentNode->Next->Next != NULL)
        // {
        // }
        // CurrentNode->Next = NULL;
    }
};
void Display()
{
    Node *CurrentNode = List;
    while (CurrentNode->Next != NULL)
    {
        cout << CurrentNode->Data << endl;
        CurrentNode = CurrentNode->Next;
    }
    cout << CurrentNode->Data << endl;
}

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

void BubbleSort(int UnsortedArray[], int ArraySize)
{
    cout << "Before Sorting" << endl;
    cout << UnsortedArray << endl;
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
    cout << UnsortedArray << endl;
}

void InsertionSort(int UnsortedArray[], int ArraySize)
{
    cout << "Before Sorting" << endl;
    cout << UnsortedArray << endl;
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
        // for (int j = 0; j < ArraySize - i; j++) {
        //     if (UnsortedArray[j] > UnsortedArray[j + 1]) {
        //         temp = UnsortedArray[j];
        //         UnsortedArray[j] = UnsortedArray[j + 1];
        //         UnsortedArray[j + 1] = temp;
        //     }
        // }
    }
    cout << "After Sorting" << endl;
    cout << UnsortedArray << endl;
}

int main()
{
    int DataArray[] = {1, 3, 5, 6, 6, 6, 6, 7, 7, 7, 7, 7, 8};
    int UnsortArray[] = {2, 9, 11, 1, 0, -1, 15};
    int Arraysize = (sizeof(DataArray) / sizeof(int));
    int UnsortArraysize = (sizeof(UnsortArray) / sizeof(int));
    cout << "{ ";
    for (int i = 0; i < UnsortArraysize; i++)
    {
        cout << UnsortArray[i];
        if (i != UnsortArraysize - 1)
            cout << ", ";
    }
    cout << " }";
    // Int_LinearSearch(DataArray, Arraysize, 6);
    // Int_DuplicateLinearSearch(DataArray, Arraysize, 6);
    // Bool_LinearSearch(DataArray, Arraysize, 6);
    // Int_BinarySearch(DataArray, Arraysize, 6);
    // Int_DuplicateBinarySearch(DataArray, Arraysize, 6);
    InsertionSort(UnsortArray, UnsortArraysize);
    cout << "{ ";
    for (int i = 0; i < UnsortArraysize; i++)
    {
        cout << UnsortArray[i];
        if (i != UnsortArraysize - 1)
            cout << ", ";
    }
    cout << " }" << endl;
    InsertAtStart(40);
    InsertAtEnd(10);
    InsertAtEnd(20);
    InsertAtEnd(30);
    DeletefromEnd();
    // DeletefromIndex(2);
    // DeletefromStart();
    // DeletefromIndex(1);
    Display();
    // Bool_BinarySearch(DataArray, Arraysize, 6);

    // cout << "Numbers in the vector: ";
    // // for (const auto &num : numbers)
    // {
    //     // cout << num << " ";
    // }
    // cout << endl;

    return 0;
}