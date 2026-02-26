#include <iostream>

using namespace std;

struct Queue {
    int DataValue;
    Queue *next;
};

Queue *FrontPointer = nullptr;
Queue *TailPointer = nullptr;

void Enqueue(int value) {
  
    Queue *newNode = new Queue;
    newNode->DataValue = value;
    newNode->next = nullptr;

    if (TailPointer == nullptr) {
        FrontPointer = newNode;
        TailPointer = newNode;
    }
    else {
        TailPointer->next = newNode;
        TailPointer = newNode;
    }

    
    cout << "Enqueued: " << value << endl;
}

int Dequeue() {
  
    if (FrontPointer == nullptr) {
        cout << "Queue is empty!" << endl;
        return -1;
    }

    Queue *temp = FrontPointer;
    int data = temp->DataValue;
    FrontPointer = FrontPointer->next;
    return data;
};

void DisplayQueue() {

    if (FrontPointer == nullptr) {
        cout << "Queue is empty!" << endl;
        return;
    }

    Queue *temp = FrontPointer;

    cout << "Front -> ";
    while (temp != nullptr) {
        cout << "[" << temp->DataValue << "]";
        
        temp = temp->next;

        if (temp != nullptr) {
            cout << " -> ";
        }
    }
    cout << " <- Tail" << endl;
}

int main(){
    Enqueue(7);
    Enqueue(8);
    DisplayQueue();
    Enqueue(87);
    Enqueue(93);
    Enqueue(56);
    DisplayQueue();
    Dequeue();
    Dequeue();
    DisplayQueue();
}