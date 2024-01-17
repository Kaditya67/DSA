#include <iostream>
#include <cstring>

class Stack {
private:
    int size;
    int top;
    char* arr;

public:
    Stack(int maxSize) : size(maxSize), top(-1) {
        arr = new char[size];
    }

    ~Stack() {
        delete[] arr;
    }

    int stackTop() const {
        return arr[top];
    }

    bool isEmpty() const {
        return top == -1;
    }

    bool isFull() const {
        return top == size - 1;
    }

    void push(char val) {
        if (isFull()) {
            std::cout << "Stack Overflow! Cannot push " << val << " to the stack\n";
        } else {
            top++;
            arr[top] = val;
        }
    }

    char pop() {
        if (isEmpty()) {
            std::cout << "Stack Underflow! Cannot pop from the stack\n";
            return -1;
        } else {
            char val = arr[top];
            top--;
            return val;
        }
    }
};

class ExpressionConverter {
public:
    static int precedence(char ch) {
        if (ch == '*' || ch == '/')
            return 3;
        else if (ch == '+' || ch == '-')
            return 2;
        else
            return 0;
    }

    static bool isOperator(char ch) {
        return (ch == '+' || ch == '-' || ch == '*' || ch == '/');
    }

    static char* infixToPostfix(const char* infix) {
        int infixLength = strlen(infix);
        char* postfix = new char[infixLength + 1];
        int j = 0; // Track postfix addition

        Stack sp(infixLength);

        for (int i = 0; i < infixLength; ++i) {
            if (!isOperator(infix[i])) {
                postfix[j++] = infix[i];
            } else {
                while (!sp.isEmpty() && precedence(infix[i]) <= precedence(sp.stackTop())) {
                    postfix[j++] = sp.pop();
                }
                sp.push(infix[i]);
            }
        }

        while (!sp.isEmpty()) {
            postfix[j++] = sp.pop();
        }

        postfix[j] = '\0';
        return postfix;
    }
};

int main() {
    std::cout << "Enter an infix expression: ";
    std::string infix;
    std::getline(std::cin, infix);

    char* postfix = ExpressionConverter::infixToPostfix(infix.c_str());

    std::cout << "Postfix expression is: " << postfix << std::endl;

    delete[] postfix;

    return 0;
}
