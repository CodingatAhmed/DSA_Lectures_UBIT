#include <iostream>
#include <cstdlib>
#include <cstdint>

using namespace std;

int ClosedHash[10];

void PrintHashPArray(int Array[], int Arraysize)
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

void LinearProbing(int DataValue, int HashSize) {
    int baseIndex = DataValue % HashSize;
    int findIndex = baseIndex;
    int stopIndex;
    if (baseIndex == 0) {
        stopIndex = HashSize - 1;
    }
    else {
        stopIndex = baseIndex - 1;
    }
    while (ClosedHash[findIndex] != 0 && findIndex != stopIndex) {
            if (findIndex == HashSize - 1) {
                findIndex = 0;
            }
            else {
                findIndex +=1;
            }
    }
    if (findIndex == stopIndex) {
        cout << "No spaces left" << endl;
    }
    else {

        ClosedHash[findIndex] = DataValue;
        cout << findIndex << endl;
        cout << stopIndex << endl;
        cout << "Data Value" << DataValue << " Added at Index " << findIndex << endl;
    }
}

void QuadraticProbing(int DataValue, int HashSize) {
    int increment = 0;
    int baseIndex = DataValue % HashSize;
    int findIndex = baseIndex;
    int stopIndex;
    if (baseIndex == 0) {
        stopIndex = HashSize - 1;
    }
    else {
        stopIndex = baseIndex - 1;
    }
    while (ClosedHash[findIndex] != 0 && findIndex < stopIndex) {
        if (findIndex == stopIndex) {
            cout << "No spaces left" << endl;
        }
        else {
            if (findIndex == HashSize - 1) {
                findIndex = 0;
            }
            else {
                findIndex = baseIndex + (increment + 1)*(increment + 1);
                increment += 1;
            }
        }
    }
    
    ClosedHash[findIndex] = DataValue;
    cout << "Data Value" << DataValue << " Added at Index " << findIndex << endl;
}

int main() {
    int HashSize = sizeof(ClosedHash) / sizeof(int);
    QuadraticProbing(10, HashSize);
    QuadraticProbing(20, HashSize);
    QuadraticProbing(30, HashSize);
    // LinearProbing(10, HashSize);
    // LinearProbing(20, HashSize);
    // LinearProbing(45, HashSize);
    // LinearProbing(46, HashSize);
    // LinearProbing(47, HashSize);
    // LinearProbing(48, HashSize);
    // LinearProbing(49, HashSize);
    // LinearProbing(59, HashSize);
    // LinearProbing(69, HashSize);
    // LinearProbing(79, HashSize);
    // LinearProbing(89, HashSize);
    PrintHashPArray(ClosedHash, HashSize);
    return 0;
}