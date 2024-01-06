#include<iostream>
using namespace std;

class Node {
private:
    int data;
    Node* next;

public:
    Node(int value) : data(value), next(nullptr) {}
    Node*& getNext() {  // Corrected naming
        return next;
    }
    int getData() const {
        return data;
    }
};

class LinkedList {
private:
    Node* head;

public:
    LinkedList() : head(nullptr) {}
    void append(int value);
    void appendAtBeg(int value);  // Append at the beginning
    void appendAtPosition(int position, int value);  // Append at a specific position
    void deleteAtBeg();
    void deleteAtEnd();
    void deleteAt(int position);
    void display() const;  // Updated to const

    ~LinkedList() {
        while (head != nullptr) {
            Node* temp = head;
            head = head->getNext();
            delete temp;
        }
    }
};

void LinkedList::append(int value) {
    Node* newNode = new Node(value);

    if (head == nullptr) {
        head = newNode;
    } else {
        Node* current = head;
        while (current->getNext() != nullptr) {
            current = current->getNext();
        }
        current->getNext() = newNode;
    }
}

void LinkedList::appendAtBeg(int value) {
    Node* newNode = new Node(value);
    newNode->getNext() = head;
    head = newNode;
}

void LinkedList::appendAtPosition(int position, int value) {
    if (position < 1) {
        cout << "Invalid position. Position should be greater than or equal to 1.\n";
        return;
    }

    Node* newNode = new Node(value);

    if (position == 1) {
        newNode->getNext() = head;
        head = newNode;
        return;
    }

    Node* temp = head;
    for (int i = 1; i < position - 1 && temp != nullptr; i++) {
        temp = temp->getNext();
    }

    if (temp == nullptr) {
        cout << "Invalid position. Position exceeds the size of the list.\n";
        return;
    }

    newNode->getNext() = temp->getNext();
    temp->getNext() = newNode;
}

// ... (unchanged code)

int main() {
    LinkedList mylist;
    int choice;

    do {
        cout << "1. Append Element\n";
        cout << "2. Append at Beginning\n";
        cout << "3. Append at Position\n";
        cout << "4. Display\n";
        cout << "5. Exit\n";
        cout << "6. Delete at Beginning\n";
        cout << "7. Delete at End\n";
        cout << "8. Delete at Position\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                int value;
                cout << "Enter the value to append: ";
                cin >> value;
                mylist.append(value);
                break;
            case 2:
                int begValue;
                cout << "Enter the value to append at the beginning: ";
                cin >> begValue;
                mylist.appendAtBeg(begValue);
                break;
            case 3:
                int position, posValue;
                cout << "Enter the position to append: ";
                cin >> position;
                cout << "Enter the value to append at position " << position << ": ";
                cin >> posValue;
                mylist.appendAtPosition(position, posValue);
                break;
            case 4:
                mylist.display();
                break;
            case 5:
                cout << "Exiting program.\n";
                break;
            case 6:
                mylist.deleteAtBeg();
                break;
            case 7:
                mylist.deleteAtEnd();
                break;
            case 8:
                int deletePosition;
                cout << "Enter the position to delete: ";
                cin >> deletePosition;
                mylist.deleteAt(deletePosition);
                break;
            default:
                cout << "Invalid choice. Please try again.\n";
        }

    } while (choice != 5);

    return 0;
}
