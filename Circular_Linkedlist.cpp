#include<iostream>
using namespace std;

// Node class representing each element in the circular linked list
class Node {
private:
    int data;
    Node* next;

public:
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

// LinkedList class managing the circular linked list operations
class LinkedList {
private:
    Node* head;  // Head of the circular linked list

public:
    LinkedList() : head(nullptr) {}

    // Function to append an element at the end of the circular linked list
    void append(int value);

    // Function to append an element at the beginning of the circular linked list
    void appendAtBeg(int value);

    // Function to append an element at a specific position in the circular linked list
    void appendAtPosition(int position, int value);

    // Function to delete the first element of the circular linked list
    void deleteAtBeg();

    // Function to delete the last element of the circular linked list
    void deleteAtEnd();

    // Function to delete an element at a specific position in the circular linked list
    void deleteAt(int position);

    // Function to display the elements of the circular linked list
    void display() const;

    // Destructor to free memory allocated for nodes
    ~LinkedList();
};

// Function to append an element at the end of the circular linked list
void LinkedList::append(int value) {
    Node* newNode = new Node(value);

    if (head == nullptr) {
        // If the list is empty, make the new node the head and link it to itself
        head = newNode;
        newNode->getNext() = head;
    } else {
        // Traverse to the end and link the last node to the new node
        Node* current = head;
        while (current->getNext() != head) {
            current = current->getNext();
        }
        current->getNext() = newNode;
        newNode->getNext() = head;
    }
}

// Function to append an element at the beginning of the circular linked list
void LinkedList::appendAtBeg(int value) {
    Node* newNode = new Node(value);
    newNode->getNext() = head;
    head = newNode;

    // Make it circular by linking the last node to the head
    Node* current = head;
    while (current->getNext() != nullptr) {
        current = current->getNext();
    }
    current->getNext() = head;
}

// Function to append an element at a specific position in the circular linked list
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
        // Make it circular by linking the last node to the head
        Node* current = head;
        while (current->getNext() != nullptr) {
            current = current->getNext();
        }
        current->getNext() = head;
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

// Function to display the elements of the circular linked list
void LinkedList::display() const {
    if (head == nullptr) {
        cout << "Circular Linked List is empty.\n";
        return;
    }

    // Traverse and display each element in the circular linked list
    Node* current = head;
    do {
        cout << current->getData() << " ";
        current = current->getNext();
    } while (current != head);
    cout << endl;
}

// Function to delete the first element of the circular linked list
void LinkedList::deleteAtBeg() {
    if (head == nullptr) {
        cout << "Circular Linked List is empty. Nothing to delete.\n";
        return;
    }

    // Move head to the next node and update the circular link
    Node* temp = head;
    head = head->getNext();

    // Delete the first node
    delete temp;
}

// Function to delete the last element of the circular linked list
void LinkedList::deleteAtEnd() {
    if (head == nullptr) {
        cout << "Circular Linked List is empty. Nothing to delete.\n";
        return;
    }

    // If there is only one node, delete it and set head to null
    if (head->getNext() == head) {
        delete head;
        head = nullptr;
        return;
    }

    // Traverse to the second-to-last node
    Node* current = head;
    while (current->getNext()->getNext() != head) {
        current = current->getNext();
    }

    // Delete the last node and update the circular link
    delete current->getNext();
    current->getNext() = head;
}

// Function to delete an element at a specific position in the circular linked list
void LinkedList::deleteAt(int position) {
    if (head == nullptr) {
        cout << "Circular Linked List is empty. Nothing to delete.\n";
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

    if (temp == nullptr || temp->getNext() == head) {
        cout << "Invalid position. Position exceeds the size of the list.\n";
        return;
    }

    // Delete the node at the specified position and update the link
    Node* toDelete = temp->getNext();
    temp->getNext() = toDelete->getNext();
    delete toDelete;
}

// Destructor to free memory allocated for nodes
LinkedList::~LinkedList() {
    Node* current = head;
    if (head != nullptr) {
        // Traverse and delete each node in the circular linked list
        do {
            Node* temp = current;
            current = current->getNext();
            delete temp;
        } while (current != head);
    }
}

// Main function for user interaction
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
