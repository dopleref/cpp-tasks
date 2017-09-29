#include <iostream>
#include <map>
#include <stack>
#include <cctype>

using namespace std;

void printStack(stack<char> st) {
    cout << "stack is ";
    while (!st.empty()) {
        cout << ' ' << st.top();
        st.pop();
    }
    cout << endl;
}

string infixToPostfix(string infixExpr) {
    string postfixExpr;
    map<char, int> prec;
    prec['*'] = 3;
    prec['/'] = 3;
    prec['+'] = 2;
    prec['-'] = 2;
    prec['('] = 1;
    stack<char> opStack;

    for (char token : infixExpr) {
        if (isalpha(token) || isdigit(token)) {
            postfixExpr +=token;
        }
        else if (token == '(') {
            opStack.push(token);
        }
        else if (token == ')') {
            char topToken = opStack.top();
            opStack.pop();
            while (topToken != '(') {
                postfixExpr += topToken;
                topToken = opStack.top();
                opStack.pop();
            }
        }
        else if (token != ' ') {
            while (!opStack.empty() && (prec[opStack.top()] >= prec[token])) {
                postfixExpr += opStack.top();
                opStack.pop();
            }
            opStack.push(token);
        }
    }

    while (!opStack.empty()) {
        postfixExpr += opStack.top();
        opStack.pop();
    }

    return postfixExpr;
}

int main() {
    cout << infixToPostfix("A * B + C * D") << endl;
    cout << infixToPostfix("(A + B) * C - (D - E) * (F + G)") << endl;
    cout << infixToPostfix("(A + A*B + B)*C") << endl;
    return 0;
}

