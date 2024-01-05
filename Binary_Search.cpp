#include<iostream>

using namespace std;

class MyArray{
    private:
    int size;
    int *arr;
    public :
    MyArray(int size):size(size){
        arr=new int[size];
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
    int binarySearch(int element);
};

int MyArray::binarySearch(int element){
    
    int low=0;
    int high=size-1;
    int mid;
    int count=0;

    while(low<=high){
        count++;
        mid = (low + high)/2;
        if(arr[mid] == element){
            return count;
        }
        if(arr[mid]<element){
            low = mid+1;
        }
        else{
            high = mid -1;
        }
    }
    return count;
}
int main() {
    int size, element;
    cout << "Enter the size of Array: ";
    cin >> size;
    MyArray arr(size);
    cout << "\nEnter the Elements of Array" << endl;
    arr.enter_array_elements();
    cout << "Enter the element to search: ";
    cin >> element;

    int result = arr.binarySearch(element);

    if (result == 0) {
        cout << "Element not found!" << endl;
    } else {
        cout << "Element found!" << endl;
        cout<<"It took "<<result<<" iterations !"<<endl;
    }

    return 0;
}
