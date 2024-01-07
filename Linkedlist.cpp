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

// LinkedList class managing the linked list operations
class LinkedList {
private:
    Node* head;  // Head of the linked list

public:
    // Constructor to initialize an empty linked list
    LinkedList() : head(nullptr) {}

    // Function to append an element at the end of the linked list
    void append(int value);

    // Function to append an element at the beginning of the linked list
    void appendAtBeg(int value);

    // Function to append an element at a specific position in the linked list
    void appendAtPosition(int position, int value);

    // Function to delete the first element of the linked list
    void deleteAtBeg();

    // Function to delete the last element of the linked list
    void deleteAtEnd();

    // Function to delete an element at a specific position in the linked list
    void deleteAt(int position);

    // Function to display the elements of the linked list
    void display() const;

    // Destructor to free memory allocated for nodes
    ~LinkedList();
};

// Function to append an element at the end of the linked list
void LinkedList::append(int value) {
    Node* newNode = new Node(value);

    if (head == nullptr) {
        // If the list is empty, make the new node the head
        head = newNode;
    } else {
        // Traverse to the end and link the last node to the new node
        Node* current = head;
        while (current->getNext() != nullptr) {
            current = current->getNext();
        }
        current->getNext() = newNode;
    }
}

// Function to append an element at the beginning of the linked list
void LinkedList::appendAtBeg(int value) {
    Node* newNode = new Node(value);
    newNode->getNext() = head;
    head = newNode;
}

// Function to append an element at a specific position in the linked list
void LinkedList::appendAtPosition(int position, int value) {
    if (position < 1) {
        cout << "Invalid position. Position should be greater than or equal to 1.\n";
        return;
    }

    Node* newNode = new Node(value);

    if (position == 1) {
        // If position is 1, insert at the beginning
        newNode->getNext() = head;
        head = newNode;
        return;
    }

    // Traverse to the position - 1 and insert the new node
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

// Function to display the elements of the linked list
void LinkedList::display() const {
    if (head == nullptr) {
        cout << "Linked List is empty.\n";
        return;
    }

    // Traverse and display each element in the linked list
    Node* current = head;
    while (current != nullptr) {
        cout << current->getData() << " ";
        current = current->getNext();
    }
    cout << endl;
}

// Function to delete the first element of the linked list
void LinkedList::deleteAtBeg() {
    if (head == nullptr) {
        cout << "Linked List is empty. Nothing to delete.\n";
        return;
    }

    // Move head to the next node and delete the previous head
    Node* temp = head;
    head = head->getNext();
    delete temp;
}

// Function to delete the last element of the linked list
void LinkedList::deleteAtEnd() {
    if (head == nullptr) {
        cout << "Linked List is empty. Nothing to delete.\n";
        return;
    }

    // If there is only one node, delete it and set head to null
    if (head->getNext() == nullptr) {
        delete head;
        head = nullptr;
        return;
    }

    // Traverse to the second-to-last node
    Node* current = head;
    while (current->getNext()->getNext() != nullptr) {
        current = current->getNext();
    }

    // Delete the last node and update the link
    delete current->getNext();
    current->getNext() = nullptr;
}

// Function to delete an element at a specific position in the linked list
void LinkedList::deleteAt(int position) {
    if (head == nullptr) {
        cout << "Linked List is empty. Nothing to delete.\n";
        return;
    }

    if (position == 1) {
        // If position is 1, delete at the beginning
        Node* temp = head;
        head = head->getNext();
        delete temp;
        return;
    }

    // Traverse to the position - 1
    Node* temp = head;
    for (int i = 1; i < position - 1 && temp != nullptr; i++) {
        temp = temp->getNext();
    }

    if (temp == nullptr || temp->getNext() == nullptr) {
        cout << "Invalid position. Position exceeds the size of the list.\n";
        return;
    }

    // Delete the node at the specified position and update the link
    Node* deleteNode = temp->getNext();
    temp->getNext() = deleteNode->getNext();
    delete deleteNode;
}

// Destructor to free memory allocated for nodes
LinkedList::~LinkedList() {
    while (head != nullptr) {
        Node* temp = head;
        head = head->getNext();
        delete temp;
    }
}

// Main function for user interaction
int main() {
    LinkedList mylist;
    int choice;

    // Menu-driven program
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
