#include<iostream>
using namespace std;

class Stack
{
private:
    int size;
    int top;
    int *arr;

public:
    Stack(int size) : size(size), top(-1) {
        arr = new int[size];
    }

    ~Stack() {
        delete[] arr;
    }

    int getTop() {
        return top;
    }

    void setTop(int i) {
        top += i;
    }

    void push(int element);
    void pop();
    void display();
};

void Stack::push(int element) {
    if (getTop() == size - 1) {
        cout << "Stack overflow" << endl;
    } else {
        setTop(1);
        arr[getTop()] = element;
    }
}

void Stack::pop() {
    if (getTop() == -1) {
        cout << "Stack is Empty" << endl;
    } else {
        setTop(-1);
    }
}

void Stack::display() {
    if (getTop() == -1) {
        cout << "Stack is Empty, Nothing to display" << endl;
    } else {
        for (int i = 0; i <= getTop(); i++) {
            cout << arr[i] << endl;
        }
    }
}

int main() {
    int choice, element;
    Stack stack(5);

    do {
        cout << "1. Push\n2. Pop\n3. Display\n4. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "Enter element to push: ";
                cin >> element;
                stack.push(element);
                break;
            case 2:
                stack.pop();
                break;
            case 3:
                stack.display();
                break;
            case 4:
                cout << "Exiting program." << endl;
                break;
            default:
                cout << "Invalid choice. Try again." << endl;
        }
    } while (choice != 4);

    return 0;
}
