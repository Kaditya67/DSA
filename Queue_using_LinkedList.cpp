#include <iostream>

class Node {
public:
    int data;
    Node* next;
};

Node* f = nullptr;
Node* r = nullptr;

void linkedListTraversal(Node* ptr) {
    std::cout << "Printing the elements of this linked list" << std::endl;
    while (ptr != nullptr) {
        std::cout << "Element: " << ptr->data << std::endl;
        ptr = ptr->next;
    }
}

// SImilar to : Inserting to the end in LinkedList
void enqueue(int val) {
    Node* n = new Node();
    if (n == nullptr) {
        std::cout << "Queue is Full" << std::endl;
    } else {
        n->data = val;
        n->next = nullptr;
        if (f == nullptr) {
            f = r = n;
        } else {
            r->next = n;
            r = n;
        }
    }
}

// Similar to : Deleting head node in the Linked List
int dequeue() {
    int val = -1;
    Node* ptr = f;
    if (f == nullptr) {
        std::cout << "Queue is Empty" << std::endl;
    } else {
        f = f->next;
        val = ptr->data;
        delete ptr;
    }
    return val;
}

int main() {
    int choice, element;

    do {
        std::cout << "\nMenu:\n";
        std::cout << "1. Enqueue\n";
        std::cout << "2. Dequeue\n";
        std::cout << "3. Display\n";
        std::cout << "4. Exit\n";

        std::cout << "Enter your choice: ";
        std::cin >> choice;

        switch (choice) {
            case 1:
                std::cout << "Enter the element to enqueue: ";
                std::cin >> element;
                enqueue(element);
                break;
            case 2:
                std::cout << "Dequeuing element " << dequeue() << std::endl;
                break;
            case 3:
                linkedListTraversal(f);
                break;
            case 4:
                std::cout << "Exiting the program." << std::endl;
                break;
            default:
                std::cout << "Invalid choice. Please enter a valid option." << std::endl;
        }

    } while (choice != 4);

    return 0;
}
