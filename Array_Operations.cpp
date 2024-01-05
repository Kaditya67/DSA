#include<iostream>

using namespace std;

class MyArray {
private:
    int size;
    int* arr;

public:
    MyArray(int size) : size(size) {
        arr = new int[size];
    }
    ~MyArray() {
        delete[] arr;
    }    
    void enter_array_elements(){
        for (int i = 0; i < size; i++)
        {
            cout<<"Element "<<i+1<<" : ";
            cin>>arr[i];
        }
        
    }
    void display();
    void Insertion(int element, int index);
    void Deletion(int index);
    int search(int element);
};

void MyArray::display() {
    cout << "Array elements: ";
    for (int i = 0; i < size; i++) {
        cout << arr[i] << " ";
    }
    cout << endl;
}

void MyArray::Insertion(int element, int index) {
    for (int i = size-1 ; i >= index; i--)
    {
        arr[i+1]=arr[i];
    }
    arr[index]=element;
    size++;
    cout<<"Size of Array Increased !"<<endl;
}

void MyArray::Deletion(int index) {
    for (int i = index; i < size-1 ; i++)
    {
        arr[i]=arr[i+1];
    }
    size--;
    cout<<"Size of Array Reduced !"<<endl;
}

int MyArray::search(int element){
    for (int i = 0; i < size; i++)
    {
        if(arr[i]==element){
            cout<<"Element Found at Index : "<<i<<endl;
            return 1;
        }
    }
    return 0;
    
}

int main() {

    int size;
    int choice;

    cout << "Enter the size for the array to be created: ";
    cin >> size;

    MyArray arr(size);
    cout<<"\nEnter array Elements : "<<endl;
    arr.enter_array_elements();
    
    do {
        cout << "Menu:\n1. Display Array\n2. Insert Element\n3. Delete Element\n4. Search Element\n5. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;
                
        switch (choice) {
            case 1:
                arr.display();
                break;
            case 2:
                int element, index;
                cout << "Enter the element to insert: ";
                cin >> element;
                cout << "Enter the index for insertion: ";
                cin >> index;
                if(index>size || index < 0){
                    cout<<"!Error : Index is out of Range"<<endl;
                    exit(1);
                }
                arr.Insertion(element, index);
                arr.display();
                break;
            case 3:
                cout << "Enter the index for deletion: ";
                cin >> index;
                if(index>size || index < 0){
                    cout<<"!Error : Index is out of Range"<<endl;
                    exit(1);
                }
                arr.Deletion(index);
                arr.display();
                break;
            case 4:
                cout<<"Enter the element to search : ";
                cin>>element;
                if (arr.search(element) == 0) {
                    cout << "Element Not Found" << endl;
                }
            case 5:
                cout << "Exiting program.\n";
                break;
            default:
                cout << "Invalid choice. Please try again.\n";
        }

    } while (choice != 5);

    return 0;
}
