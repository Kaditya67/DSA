#include<iostream>
using namespace std;

// Node class representing each element in the linked list
class Node {
private:
    int data;
    Node* next;

public:
    // Constructor to initialize a node with a given value
    Node(int value) : data(value), next(nullptr) {}

    // Getter for the next pointer
    Node*& getNext() {
        return next;
    }

    // Getter for the data value
    int getData() const {
        return data;
    }
};

class Stack {
private:
    Node *top;

public:
    Stack() : top(nullptr) {}
    ~Stack() {
        while (!isEmpty()) {
            pop();
        }
    }
    bool isEmpty() const {
        return top == nullptr;
    }
    void push(int value);
    void pop();
    int peek();
    void printMenu();
    void processChoice();
};

void Stack::push(int value) {
    Node* newNode = new Node(value);
    newNode->next = top;
    top = newNode;
}

void Stack::pop() {
    if (isEmpty()) {
        cerr << "Error: Stack is Empty, Cannot Pop" << endl;
        return;
    }
    Node* temp = top;
    top = top->next;
    delete temp;
}

int Stack::peek() {
    if (isEmpty()) {
        cerr << "Error: Stack is Empty, Cannot Peek" << endl;
        return 0;
    }
    return top->getData();
}

void Stack::printMenu() {
    cout << "Stack Menu:" << endl;
    cout << "1. Push" << endl;
    cout << "2. Pop" << endl;
    cout << "3. Peek" << endl;
    cout << "4. Exit" << endl;
}

void Stack::processChoice() {
    int choice;
    cout << "Enter your choice: ";
    cin >> choice;

    switch (choice) {
        case 1: {
            int value;
            cout << "Enter value to push: ";
            cin >> value;
            push(value);
            break;
        }
        case 2:
            pop();
            break;
        case 3:
            cout << "Top element: " << peek() << endl;
            break;
        case 4:
            cout << "Exiting program." << endl;
            exit(0);
        default:
            cerr << "Invalid choice. Please try again." << endl;
    }
}

int main() {
    Stack myStack;

    while (true) {
        myStack.printMenu();
        myStack.processChoice();
    }

    return 0;
}
