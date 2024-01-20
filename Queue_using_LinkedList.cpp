#include <iostream>

class Node {
public:
    int data;
    Node* next;
};

class Queue{
    public:
    // Moving pointers
    Node* f;
    Node* r;
    Queue(){
        r=nullptr;
        f=nullptr;
    }
    // Functions
    void linkedListTraversal();
    void enqueue(int val);
    int dequeue();
};


void Queue :: linkedListTraversal() {
    Node *ptr=f;
    std::cout << "Printing the elements of this linked list" << std::endl;
    while (ptr != nullptr) {
        std::cout << "Element: " << ptr->data << std::endl;
        ptr = ptr->next;
    }
}

// Similar to : Inserting to the end in LinkedList
void Queue::enqueue(int val) {
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
int Queue :: dequeue() {
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
    Queue q;

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
                q.enqueue(element);
                break;
            case 2:
                std::cout << "Dequeuing element " << q.dequeue() << std::endl;
                break;
            case 3:
                q.linkedListTraversal();
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
