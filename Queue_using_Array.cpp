#include<iostream>
using namespace std;

class Queue {
private:
    int left;
    int right;
    int size;
    int *arr;
public:
    Queue(int size) : size(size) {
        arr = new int[size];
        right = left = -1;
    }

    ~Queue() {
        delete[] arr;
    }

    void Enqueue(int data);
    void Dequeue();
    void peek(int p);
    void display();
};

void Queue::Enqueue(int data) {
    if (left == -1) {
        left = right = 0;
        arr[left] = data;
    }
    else if (right == size - 1) {
        cout << "Queue is Full" << endl;
    }
    else {
        right++;
        arr[right] = data;
    }
}

void Queue::Dequeue() {
    if (left == -1) {
        cout << "Queue is Empty" << endl;
    }
    else {
        int dequeuedElement = arr[left];
        if (left == right) {
            // If there was only one element in the queue
            left = right = -1;
        }
        else {
            left++;
        }
        cout << "Dequeued Element: " << dequeuedElement << endl;
    }
}


void Queue::peek(int p) {
    if (left == -1) {
        cout << "Queue is Empty" << endl;
    }
    else if (p < 1 || p > (right - left + 1)) {
        cout << "Out of Range" << endl;
    }
    else {
        cout << "Element at position " << p << " is : " << arr[left + p - 1] << endl;
    }
}

void Queue::display() {
    for (int i = left; i < right+1; i++) {
        cout <<arr[i] << endl;
    }
}

int main() {
    int size;
    cout<<"Please Enter the size of queue : ";
    cin>>size;
    int choice, element;
    Queue queue(size);

    do {
        cout << "1. Enqueue\n2. Dequeue\n3. Peek\n4. Display\n5. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "Enter element to push: ";
                cin >> element;
                queue.Enqueue(element);
                break;
            case 2:
                queue.Dequeue();
                break;
            case 3:
                int position;
                cout<<"Enter the position to peek : ";
                cin>>position;
                queue.peek(position);
                break;
            case 4:
                queue.display();
                break;
            case 5:
                cout << "Exiting program." << endl;
                break;
            default:
                cout << "Invalid choice. Try again." << endl;
        }
    } while (choice != 5);

    return 0;
}

