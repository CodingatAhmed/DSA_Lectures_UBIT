#include <iostream>
#include <cstdlib>
#include <cstdint>
#include <string>
#ifndef MATH_UTILS_H  // Header guards to prevent double inclusion
#define MATH_UTILS_H
using namespace std;

char StackArray[100];
int TopPointer = 0;

void Push(int DataValue)
{
    if (TopPointer < 10)
    {
        StackArray[TopPointer] = DataValue;
        TopPointer += 1;
    }
    else
    {
        cout << "Stack is full" << endl;
    }
}

int Pop(int DataValue)
{
    if (TopPointer > 1)
    {
        int ReturnValue;
        TopPointer -= 1;
        ReturnValue = StackArray[TopPointer];
        return ReturnValue;
    }
    else
    {
        cout << "Stack is empty" << endl;
        return -1;
    }
}

void DisplayArray(int Array[], int ArraySize)
{
    cout << "{";
    for (int i = 0; i < ArraySize; i++)
    {
        cout << Array[i];
        if (i != ArraySize - 1)
            cout << ", ";
    }
    cout << "}";
}

int precedence(char c) {
        if (c == '/' || c == '*') {
            return 1;
        }
        else if (c == '+' || c == '-') {
            return 2;
        }
        else if (c == "<" || c == ">" || c == "<=" || c == ">=" || c == "") {
            return 3;
        }
        else if (c == "!=" || c == "==") {
            return 4;
        }
        else if (c == "&&") {
            return 5;
            
        }
        else if (c = "||") {
            return 6;
            
        }
        else if (c == "(") {
            return 7;
        }
        else if (c == ")") {
            return 8;
        }
        else {
            return 9;
        }
    }

void InfixToPostfix(string infixExpression) {
    string PostFix = "";
    for (int i = 0; i < infixExpression.length(); i++) {
        char PickChar = infixExpression[i];
        int precedenceValue = precedence(PickChar);
        if (precedenceValue == 9) {
            PostFix = PostFix + PickChar;
        }
        else {
            if (TopPointer == 0) {
                Push(PickChar);
            }   
            else {
                while (TopPointer < 0 && precedence(Pop()) <= precedenceValue) {
                    PostFix = PostFix + precedence(Pop());
                }
                Push(PickChar)
            }   
        }

    }
    for (int j = 0; j < TopPointer; j++) {
        PostFix = PostFix + Push(StackArray[j]);
    }
}

int main()
{
    int StackArraySize = sizeof(StackArray) / sizeof(int);
    DisplayArray(StackArray, StackArraySize);
    Push(10);
    DisplayArray(StackArray, StackArraySize);
    return 0;
}
#endif