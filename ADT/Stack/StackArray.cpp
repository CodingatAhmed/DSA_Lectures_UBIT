#include <stack>
#include <vector>
#include <string>
#include <iostream>
using namespace std;





// void Push(char DataValue)
// {
//     if (TopPointer < 10)
//     {
//         StackArray[TopPointer] = DataValue;
//         TopPointer += 1;
//     }
//     else
//     {
//         cout << "Stack is full" << endl;
//     }
// }

// int Pop()
// {
//     if (TopPointer > 1)
//     {
//         int ReturnValue;
//         TopPointer -= 1;
//         ReturnValue = StackArray[TopPointer];
//         return ReturnValue;
//     }
//     else
//     {
//         cout << "Stack is empty" << endl;
//         return -1;
//     }
// }

void DisplayArray(vector<string>& Array)
{
    cout << "{";
    for (int i = 0; i < Array.size(); i++)
    {
        cout << Array[i];
        if (i != Array.size() - 1)
            cout << ", ";
    }
    cout << "}";
}


// void InfixToPostfix(string infixExpression) {
    //     string PostFix = "";
    //     for (int i = 0; i < infixExpression.length(); i++) {
//         char PickChar = infixExpression[i];
//         int precedenceValue = precedence(PickChar);
//         if (precedenceValue == 9) {
//             PostFix = PostFix + PickChar;
//         }
//         else {
//             if (TopPointer == 0) {
//                 Push(PickChar);
//             }   
//             else {
//                 while (TopPointer > 0 && precedence(Pop()) <= precedenceValue) {
//                     PostFix = PostFix + Pop();
//                 }
//                 Push(PickChar)
//             }   
//         }
//     }
//     for (int j = 0; j < TopPointer; j++) {
    //         PostFix = PostFix + Pop();
    //     }
    //     cout << PostFix << endl;
    // }
int precedence(string c) {
        if (c == "/" || c == "*" || c == "%") {
            return 9;
        }
        else if (c == "+" || c == "-") {
            return 8;
        }
        else if (c.size() > 0 && (c[0] == '<' || c[0] == '>')) {
        if (c.size() > 1 && c[1] == '=') {
            return 7;
        }
        else {
            return 6;
        }
        }
        else if (c == "!" || c == "=") {
            return 5;
        }
        else if (c == "&") {
            return 4;
        }
        else if (c == "|") {
            return 3;
        }
        else if (c == "(") {
            return 2;
        }
        else if (c == ")") {
            return 1;
        }
        else {
            return 0;
        }
    
    }

vector<string> Tokenize(string InfixExp) {
    vector<string> ExpressionDivision;
    int i = 0;
    while (i < InfixExp.size()) {
        string priority1(1,InfixExp[i]);
        if (precedence(priority1) > 7 || precedence(priority1) < 3) {
            ExpressionDivision.push_back(priority1);
        }
        else if (precedence(priority1) < 6 && precedence(priority1) > 2 && i + 1 <= InfixExp.size()) {
            string priority2(1,InfixExp[i + 1]);
            string combinedPriority = priority1 + priority2;
            ExpressionDivision.push_back(combinedPriority);
            i += 1;  
        }
        else if (precedence(priority1) == 6) {
            string priority2(1,InfixExp[i + 1]);
            string combinedPriority = priority1 + priority2;
            if (precedence(combinedPriority) == 7) {
                ExpressionDivision.push_back(combinedPriority);
                i += 1;  
            }
            else {
                ExpressionDivision.push_back(priority1);
            }
        }
        i += 1;  
    }
    DisplayArray(ExpressionDivision);
    return ExpressionDivision;
}

void InfixToPostfix(vector<string> InfixExpressionArray) {
    stack<string> RPNEval;
    string PostFixExpression = "";
    for (int i = 0; i < InfixExpressionArray.size(); i++) {
        string Check = InfixExpressionArray[i].substr(0,1);
    if (precedence(Check) == 1) {
        while (RPNEval.size() > 0 && RPNEval.top() != "(") {
            PostFixExpression += RPNEval.top();
            RPNEval.pop();
        }
        RPNEval.pop();
    }
    else if (precedence(Check) == 2) {
            RPNEval.push(Check);
    }
    else if (precedence(Check) == 0) {
            PostFixExpression += InfixExpressionArray[i];
    }
    else if (precedence(Check) > 2 && precedence(Check) < 10) {
        if (InfixExpressionArray[i].size() > 1) {
            
        }
        while (RPNEval.size() > 0 && precedence(RPNEval.top()) >= precedence(Check)) {
            PostFixExpression += RPNEval.top();
            RPNEval.pop();
        } 
        // PostFixExpression += RPNEval.top();
        // RPNEval.pop();
        RPNEval.push(InfixExpressionArray[i]);

    }
    }
    while (RPNEval.size() > 0 ) {
        PostFixExpression += RPNEval.top();
        RPNEval.pop();
    }
    cout << PostFixExpression << endl;
    
}
int main()
{
    // char StackArray[100];
    // int TopPointer = 0;
    // int StackArraySize = sizeof(StackArray) / sizeof(int);
    // DisplayArray(StackArray, StackArraySize);
    // Push(10);
    // vector<string> TokenizedArray = Tokenize("A>B&&C<D");
    vector<string> TokenizedArray = Tokenize("A + B * C == D / E");
    // vector<string> TokenizedArray = Tokenize("A+B*C==D/E");
    InfixToPostfix(TokenizedArray);
    // DisplayArray(StackArray, StackArraySize);
    return 0;
}